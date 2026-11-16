# `src/planner/compiled_source.cpp` — block usage map

[Source](../../../../../src/planner/compiled_source.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `e53b082eb29656814c84f461eef2e4c17ad568eb68b6688c53f399a0177a46a7`. 115 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/planner/compiled_source.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Caller DTO conversion only. Ordinary payload is materialized; accounted · [reviewed contract](#b0001) |
| [B0002 · 10–11](../../../../../src/planner/compiled_source.cpp#L10) | Callable definition: public: std::string copy(std::string_view value) | calls std::string; returns std::string(value) · [reviewed contract](#b0002) |
| [B0003 · 12–33](../../../../../src/planner/compiled_source.cpp#L12) | Callable definition: io::Json copy(program::JsonView value) | calls kind, boolean, integer, unsigned_integer; returns nullptr; value.boolean(); growth push_back; 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 34–34](../../../../../src/planner/compiled_source.cpp#L34) | Callable definition: Value copy(const storage::ScalarView& value) | calls storage::export_scalar; returns storage::export_scalar(value) · [reviewed contract](#b0004) |
| [B0005 · 35–35](../../../../../src/planner/compiled_source.cpp#L35) | Callable definition: Decimal copy(const storage::InlineDecimal& value) | calls storage::export_scalar; returns std::get&lt;Decimal&gt;(storage::export_scalar(storage::ScalarView{value})) · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../src/planner/compiled_source.cpp#L36) | Callable definition: storage::TupleLayout copy(const storage::AccountedLayout& value) | calls descriptor; returns value.descriptor() · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../src/planner/compiled_source.cpp#L37) | Callable definition: storage::Projection copy(const storage::AccountedProjection& value) | calls descriptor; returns value.descriptor() · [reviewed contract](#b0007) |
| [B0008 · 38–42](../../../../../src/planner/compiled_source.cpp#L38) | Callable definition: template&lt;class T&gt; OwnedType&lt;program::Span&lt;T&gt;&gt; copy(program::Span&lt;T&gt; value) | calls reserve, size, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 43–45](../../../../../src/planner/compiled_source.cpp#L43) | Callable definition: template&lt;class T&gt; OwnedType&lt;program::Set&lt;T&gt;&gt; copy(program::Set&lt;T&gt; value) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 46–49](../../../../../src/planner/compiled_source.cpp#L46) | Callable definition: template&lt;class T&gt; OwnedType&lt;std::optional&lt;T&gt;&gt; copy(const std::optional&lt;T&gt;& value) | calls ; returns {}; OwnedType&lt;std::optional&lt;T&gt;&gt;(std::in_place,copy(*value)) · [reviewed contract](#b0010) |
| [B0011 · 50–55](../../../../../src/planner/compiled_source.cpp#L50) | Callable definition: template&lt;std::size_t I=0,class... T&gt; OwnedType&lt;std::variant&lt;T...&gt;&gt; variant(const std::variant&lt;T...&gt;& value) | calls constexpr, index, copy, storage::IndexFailure; returns OwnedType&lt;std::variant&lt;T...&gt;&gt;(std::in_place_index&lt;I&gt;,copy(std::get&lt;I&gt;(value))); variant&lt;I+1&gt;(value) · [reviewed contract](#b0011) |
| [B0012 · 56–56](../../../../../src/planner/compiled_source.cpp#L56) | Callable definition: template&lt;class... T&gt; OwnedType&lt;std::variant&lt;T...&gt;&gt; copy(const std::variant&lt;T...&gt;& value) | calls variant; returns variant(value) · [reviewed contract](#b0012) |
| [B0013 · 57–76](../../../../../src/planner/compiled_source.cpp#L57) | Callable definition: template&lt;class T&gt; OwnedType&lt;T&gt; copy(const T& value) | calls constexpr, static_assert; guard if constexpr(fields==0) {static_assert(std::is_same_v&lt;T,R&gt; && std::is_trivially_copyable_v&lt;T&gt;,"miss…; returns value; R{copy(f0)} · [reviewed contract](#b0013) |
| [B0014 · 77–78](../../../../../src/planner/compiled_source.cpp#L77) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../src/planner/compiled_source.cpp#L79) | Callable definition: Catalog catalog(const program::Catalog& value) | calls copy; returns Copy{}.copy(value) · [reviewed contract](#b0015) |
| [B0016 · 80–80](../../../../../src/planner/compiled_source.cpp#L80) | Callable definition: Query query(const program::Query& value) | calls copy; returns Copy{}.copy(value) · [reviewed contract](#b0016) |
| [B0017 · 81–81](../../../../../src/planner/compiled_source.cpp#L81) | Callable definition: frontend::NormalizedSql normalized(const program::NormalizedSql& value) | calls copy; returns Copy{}.copy(value) · [reviewed contract](#b0017) |
| [B0018 · 82–82](../../../../../src/planner/compiled_source.cpp#L82) | Callable definition: PhysicalOptions options(const program::PhysicalOptions& value) | calls copy; returns Copy{}.copy(value) · [reviewed contract](#b0018) |
| [B0019 · 83–83](../../../../../src/planner/compiled_source.cpp#L83) | Callable definition: FreeConnexTree tree(const program::FreeConnexTree& value) | calls copy; returns Copy{}.copy(value) · [reviewed contract](#b0019) |
| [B0020 · 84–114](../../../../../src/planner/compiled_source.cpp#L84) | Callable definition: ProgramExport export_program(const CompiledProgram& value) | calls route, copy, catalog, query; returns result; source comment (unverified): // Preserve the prepared digest bytes after a width check; this export path · [reviewed contract](#b0020) |
| [B0021 · 115–115](../../../../../src/planner/compiled_source.cpp#L115) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::compiler_source_detail · [reviewed contract](#b0021) |

## B0001

[Lines 1–9](../../../../../src/planner/compiled_source.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Copy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert immutable native program views to public compiler/report DTO values through explicit leaf/record mappings. |
| inputs / outputs | Overloads materialize strings/scalars/JSON/containers/record fields and preserve same-index variant alternatives; accounted descriptors become shared public handles. |
| invariants | Borrow source only during synchronous conversion; fields count/order must match Owned metadata. Conversion is not admission, replay or validation authority. |
| ownership | Result owns ordinary copied bytes/containers. Layout/projection handles retain their original accounted metadata and callbacks, not the entire native program/arena. |
| failure | Nested conversion/allocation/contract failures propagate; no partial DTO is returned. Ordinary JSON cleanup uses the vendored allocation-failure repair. |
| cost | Full ordinary content traversal/allocation with JSON recursion and ordered-set insertion costs; descriptor leaves are fixed validity/refcount work, not deep metadata copies. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [third_party/nlohmann/README.crown.md](../../../../../third_party/nlohmann/README.crown.md) |

## B0002

[Lines 10–11](../../../../../src/planner/compiled_source.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string copy(std::string_view value) {return std::string(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize borrowed text as owning string. |
| inputs / outputs | Returns equal bytes. |
| invariants | Result survives view backing storage. |
| ownership | Borrows only during call; owns characters. |
| failure | Allocation failure propagates. |
| cost | O(byte length). |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0003

[Lines 12–33](../../../../../src/planner/compiled_source.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json copy(program::JsonView value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy native JSON view into owning IO JSON. |
| inputs / outputs | Copies scalar kinds directly and recursively copies array elements and object keys/members. |
| invariants | Preserves JSON values and detaches text; invalid kind is contract failure. |
| ownership | Borrows source tree during call; result owns all nested data. |
| failure | Invalid kind throws IndexFailure(contract); allocation/copy failure propagates. |
| cost | Visits all nodes/bytes; allocation scales with full tree and recursion with nesting. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0004

[Lines 34–34](../../../../../src/planner/compiled_source.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value copy(const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export account-aware scalar view as owning core Value. |
| inputs / outputs | Delegates to export_scalar. |
| invariants | Does not retain view or arena. |
| ownership | Borrows only for conversion. |
| failure | Storage conversion/allocation errors propagate. |
| cost | Variant dispatch plus scalar payload. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0005

[Lines 35–35](../../../../../src/planner/compiled_source.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decimal copy(const storage::InlineDecimal& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert inline storage decimal to public owning Decimal. |
| inputs / outputs | Exports through ScalarView then extracts Decimal alternative. |
| invariants | Assumes InlineDecimal export yields Decimal. |
| ownership | Returns detached Decimal. |
| failure | Storage failure propagates; unexpected alternative throws bad_variant_access. |
| cost | Scales with coefficient payload. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0006

[Lines 36–36](../../../../../src/planner/compiled_source.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::TupleLayout copy(const storage::AccountedLayout& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a public TupleLayout descriptor handle over validated accounted layout data. |
| inputs / outputs | Calls value.descriptor(), which checks required() and constructs TupleLayout from the same shared LayoutDescriptor pointer/control block. |
| invariants | The handle preserves original token, field/context/equality views and make_native_tuple callback; it is not a standalone layout copy. |
| ownership | Shares concrete AccountedLayout::Data control block, MemoryAccount and MemoryBlock for fields/equalities/binding bytes. It can retain this metadata block after AccountedLayout/CompiledProgram destruction, but not a tuple arena or full program object. |
| failure | An empty AccountedLayout throws MemoryFailure(contract) from required(); valid conversion adds no metadata allocation. |
| cost | O(1) required() check and shared_ptr handle/refcount work; no field scan, new control block or metadata copy. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp) |

## B0007

[Lines 37–37](../../../../../src/planner/compiled_source.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Projection copy(const storage::AccountedProjection& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a public Projection descriptor handle over validated accounted projection data. |
| inputs / outputs | Calls value.descriptor(), which checks required() and constructs Projection from the same shared ProjectionDescriptor pointer/control block. |
| invariants | The handle retains source/target layout tokens, projected-field view and apply_native_tuple callback; it is not a standalone deep projection copy. |
| ownership | Shares AccountedProjection::Data, its MemoryAccount/projected FieldId block, plus source/target AccountedLayout handles and tokens. It may retain those metadata blocks after source objects die, but not a tuple arena or full CompiledProgram object. |
| failure | An empty AccountedProjection throws ProjectionValidationFailure(invalid_layout) from required(); valid conversion allocates no descriptor storage/control block. |
| cost | O(1) required() check and shared_ptr handle/refcount work; no field scan or metadata copy. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp) |

## B0008

[Lines 38–42](../../../../../src/planner/compiled_source.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> OwnedType<program::Span<T>> copy(program::Span<T> value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native Span to mapped vector. |
| inputs / outputs | Reserves size, recursively copies and appends each item in input order. |
| invariants | Preserves order/duplicates and detaches the Span container. Ordinary items are recursively copied; accounted descriptor items share their original Data/control blocks. |
| ownership | Borrows Span during traversal; owns vector and mapped wrappers. Accounted descriptor wrappers can retain source account-backed metadata beyond Span-owner lifetime. |
| failure | Reserve/nested copy/push failure propagates; partial local vector dies. |
| cost | O(n) visits plus nested payload copies/vector allocation; descriptor items use fixed handle/refcount work, not a metadata clone. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0009

[Lines 43–45](../../../../../src/planner/compiled_source.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> OwnedType<program::Set<T>> copy(program::Set<T> value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native Set to mapped std::set. |
| inputs / outputs | Maps and inserts each source item. |
| invariants | Destination comparator defines sorted order/uniqueness. |
| ownership | Borrows input; owns destination set nodes and mapped wrappers. Accounted descriptor values share backing Data. |
| failure | Insertion or nested failure propagates. |
| cost | O(n log n) insertion plus nested copy; descriptor-valued items add fixed shared-handle work rather than metadata copying. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0010

[Lines 46–49](../../../../../src/planner/compiled_source.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> OwnedType<std::optional<T>> copy(const std::optional<T>& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an optional payload only when present. |
| inputs / outputs | Returns empty or constructs mapped payload in place. |
| invariants | Preserves presence and creates a new optional wrapper; an AccountedLayout/AccountedProjection payload maps to a shared descriptor handle. |
| ownership | Borrows source; owns mapped optional wrapper. Accounted descriptor payloads retain shared metadata Data. |
| failure | Nested errors propagate. |
| cost | Constant empty check plus payload conversion; descriptor payload uses O(1) validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0011

[Lines 50–55](../../../../../src/planner/compiled_source.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t I=0,class... T> OwnedType<std::variant<T...>> variant(const std::variant<T...>& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select and copy the active alternative at the original variant index. |
| inputs / outputs | Checks active index, constructs same index in mapped variant and recurses. |
| invariants | Correctness requires aligned alternative pack order; a selected accounted descriptor is represented by a shared handle. |
| ownership | Borrows source during dispatch; owns mapped variant wrapper, while descriptor alternatives retain shared Data. |
| failure | Exhaustion throws IndexFailure(contract); nested failures propagate. |
| cost | O(active index) checks plus selected payload copy; a descriptor payload adds fixed handle/refcount work only. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0012

[Lines 56–56](../../../../../src/planner/compiled_source.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class... T> OwnedType<std::variant<T...>> copy(const std::variant<T...>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route generic variant copy through active-index converter. |
| inputs / outputs | Delegates to variant(value). |
| invariants | Only active alternative is copied; index retained. |
| ownership | Returns an owning mapped variant wrapper; a selected accounted descriptor retains shared Data. |
| failure | Propagates selector/conversion errors. |
| cost | Dispatch plus selected payload. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0013

[Lines 57–76](../../../../../src/planner/compiled_source.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> OwnedType<T> copy(const T& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild mapped aggregate recursively from Owned field metadata. |
| inputs / outputs | Structured-binds and copies 1-15 fields; fields zero returns identity only for same trivially-copyable type. |
| invariants | Field count/order must match both aggregates; unsupported arity fails compilation. Fields are recursively converted, but AccountedLayout/Projection members map to shared descriptor handles. |
| ownership | Borrows input and returns an owning mapped record wrapper; nested accounted descriptor handles may keep their original metadata Data alive. |
| failure | Static assertions reject unsupported mapping; nested copies may throw. |
| cost | One recursive call per field plus nested work; each descriptor member adds O(1) handle/refcount work without new metadata storage. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0014

[Lines 77–78](../../../../../src/planner/compiled_source.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L78:sha256:f5914bfa5b00076bc4f021ac522bd4db470a11417b5377ba66c63645bd89d955
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close the current class or struct and its surrounding scope in src/planner/compiled_source.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0015

[Lines 79–79](../../../../../src/planner/compiled_source.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog(const program::Catalog& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach public Catalog from native compiler input. |
| inputs / outputs | Copies catalog records and containers through Copy. |
| invariants | Conversion is not catalog validation. |
| ownership | Borrows source during call; owns result metadata. |
| failure | Nested copy/allocation errors propagate. |
| cost | Scales with tables, constraints, statistics and names. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0016

[Lines 80–80](../../../../../src/planner/compiled_source.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Query query(const program::Query& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach public Query from native compiler input. |
| inputs / outputs | Copies variables, atoms, terms, head and metadata. |
| invariants | IDs remain value IDs, not references to native vectors. |
| ownership | Borrows source during call; owns containers. |
| failure | Nested copy/allocation errors propagate. |
| cost | Scales with variables, terms and outputs. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0017

[Lines 81–81](../../../../../src/planner/compiled_source.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql normalized(const program::NormalizedSql& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach normalized compiler-input record for DTO/report consumers. |
| inputs / outputs | Copies binding, core catalog/query, policies, identity, adapters and metadata. |
| invariants | Does not rerun normalization or verify SQL meaning. |
| ownership | Borrows input during call; result owns nested data. |
| failure | Nested copy/allocation errors propagate. |
| cost | Scales with full normalized object. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0018

[Lines 82–82](../../../../../src/planner/compiled_source.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions options(const program::PhysicalOptions& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach public physical options from native input. |
| inputs / outputs | Recursively copies declared option fields. |
| invariants | Preserves values; performs no admission/lowering policy check. |
| ownership | Borrows input; returns owning value. |
| failure | Nested copy/allocation errors propagate. |
| cost | Fixed member visits plus nested values. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0019

[Lines 83–83](../../../../../src/planner/compiled_source.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree(const program::FreeConnexTree& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the captured FreeConnex tree into the existing owning compiler DTO representation. |
| inputs / outputs | A genuine immutable program tree becomes one owning \`FreeConnexTree\` copy for lower_tree. |
| invariants | The result is only a compiler input, not independent proof, normalized SQL authority or an edited tree. |
| ownership | Copied strings/vectors own their DTO memory during cold lowering; no copy is retained by the runtime. |
| failure | Ordinary compiler allocation/conversion failures propagate. |
| cost | Traversal and DTO allocations are cold compiler costs outside selected source_work counters. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0020

[Lines 84–114](../../../../../src/planner/compiled_source.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProgramExport export_program(const CompiledProgram& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create complete caller-owned serializer/report DTO from immutable CompiledProgram. |
| inputs / outputs | Copies route, source/query/tree/validation/identity/digests/options/guarantees and ordinary containers. Layouts, physical relations/indexes/inputs/nodes/edges/enumeration and result layout recursively contain public TupleLayout/Projection descriptor handles. |
| invariants | physical_source_sha256 must be 64 bytes then is copied; contents are not recomputed. Accounted descriptor fields are shared handles to original Data/control blocks, not deep metadata copies. lower.cpp moves DTO fields into a PhysicalPlan adapter. |
| ownership | Borrows CompiledProgram while building; result owns ordinary copies and descriptor wrappers. Handles can retain specific account-backed layout/projection blocks, account state and projection source/target layouts after source destruction; they do not retain its complete object/ordinary vector graph or tuple/row arena. |
| failure | Wrong digest width throws IndexFailure(contract); invalid descriptors may throw their contract failures; nested allocation/conversion errors propagate, with no partial result. |
| cost | Copies ordinary records/payloads and output containers. Descriptor conversion is O(1) validity/refcount work with no new metadata/control block; records/vectors still allocate wrapper storage. No work/byte cap. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0021

[Lines 115–115](../../../../../src/planner/compiled_source.cpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L115:sha256:302c1b2a71eb42678aaf8414affb961a630fe3525cf891c85665c822faedddfe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::compiler_source_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md) |
