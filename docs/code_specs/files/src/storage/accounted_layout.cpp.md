# `src/storage/accounted_layout.cpp` — block usage map

[Source](../../../../../src/storage/accounted_layout.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `f48cb414e02dd3425d42d0754d2699d36cf729353f6d9cfb68f5669c361f70ab`. 249 lines partitioned into 44 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../src/storage/accounted_layout.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_destructible_v&lt;Field&gt; && std::is_nothrow_copy_constructible_v&lt;Field… · [reviewed contract](#b0001) |
| [B0002 · 22–25](../../../../../src/storage/accounted_layout.cpp#L22) | Callable definition: std::size_t add(std::size_t left, std::size_t right) | calls max, MemoryFailure; returns left + right · [reviewed contract](#b0002) |
| [B0003 · 26–29](../../../../../src/storage/accounted_layout.cpp#L26) | Callable definition: std::size_t multiply(std::size_t left, std::size_t right) | calls max, MemoryFailure; returns left * right · [reviewed contract](#b0003) |
| [B0004 · 30–33](../../../../../src/storage/accounted_layout.cpp#L30) | Callable definition: std::size_t aligned(std::size_t value, std::size_t alignment) | calls add; returns remainder == 0 ? value : add(value, alignment - remainder) · [reviewed contract](#b0004) |
| [B0005 · 34–38](../../../../../src/storage/accounted_layout.cpp#L34) | Callable definition: bool decimal_fits(DecimalParts value, DecimalSpec spec) noexcept | calls size; returns value.scale &lt;= spec.scale && integer_digits + spec.scale &lt;= spec.precision · [reviewed contract](#b0005) |
| [B0006 · 39–42](../../../../../src/storage/accounted_layout.cpp#L39) | Callable definition: bool fits(const Value& value, DecimalSpec spec) noexcept | calls decimal_fits, parts; returns decimal && decimal_fits(decimal-&gt;parts(), spec) · [reviewed contract](#b0006) |
| [B0007 · 43–46](../../../../../src/storage/accounted_layout.cpp#L43) | Callable definition: bool fits(const ScalarView& value, DecimalSpec spec) noexcept | calls decimal_fits, parts; returns decimal && decimal_fits(decimal-&gt;parts(), spec) · [reviewed contract](#b0007) |
| [B0008 · 47–60](../../../../../src/storage/accounted_layout.cpp#L47) | Callable definition: template&lt;class Read&gt; TupleValidationIssue validate(std::span&lt;const Field&gt; fields, std::span&lt;const Equality&gt; equalities, std::size… | calls size, read, index, fits; returns {TupleProblem::arity, FieldId{0}}; {TupleProblem::scalar_kind, FieldId{i}}; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 61–73](../../../../../src/storage/accounted_layout.cpp#L61) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 74–83](../../../../../src/storage/accounted_layout.cpp#L74) | Callable definition: Data(resource::MemoryAccount owner, resource::MemoryBlock block, LayoutId layout_id, std::size_t count, std::size_t equal_count, … | calls account, std::move, storage, id · [reviewed contract](#b0010) |
| [B0011 · 84–86](../../../../../src/storage/accounted_layout.cpp#L84) | Callable definition: \[\[nodiscard\]\] std::span&lt;const Field&gt; fields() const noexcept | calls data; returns {static_cast&lt;const Field*&gt;(storage.data()), arity} · [reviewed contract](#b0011) |
| [B0012 · 87–89](../../../../../src/storage/accounted_layout.cpp#L87) | Callable definition: \[\[nodiscard\]\] std::span&lt;const Equality&gt; equalities() const noexcept | calls data; returns {reinterpret_cast&lt;const Equality*&gt;(static_cast&lt;const std::byte*&gt;(storage.data()) + equality_offset)… · [reviewed contract](#b0012) |
| [B0013 · 90–92](../../../../../src/storage/accounted_layout.cpp#L90) | Callable definition: \[\[nodiscard\]\] LayoutContextView context() const noexcept | calls std::string_view, data; returns {catalog_version, std::string_view(static_cast&lt;const char*&gt;(storage.data()) + binding_offset, bindi… · [reviewed contract](#b0013) |
| [B0014 · 93–94](../../../../../src/storage/accounted_layout.cpp#L93) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 95–99](../../../../../src/storage/accounted_layout.cpp#L95) | Callable definition: std::string_view TupleValidationFailure::code() const noexcept | calls ; returns @; @ · [reviewed contract](#b0015) |
| [B0016 · 100–110](../../../../../src/storage/accounted_layout.cpp#L100) | Callable definition: const char* TupleValidationFailure::what() const noexcept | calls ; returns @; @ · [reviewed contract](#b0016) |
| [B0017 · 111–111](../../../../../src/storage/accounted_layout.cpp#L111) | Explanatory comments or spacing. |  |
| [B0018 · 112–116](../../../../../src/storage/accounted_layout.cpp#L112) | Callable definition: AccountedLayout AccountedLayout::freeze(const resource::MemoryAccount& account, const TupleLayout& source, resource::MemoryAttrib… | calls same_token, TupleValidationFailure, make, id; returns make(account,source.id(),source.fields(),source.context(),source.origin(),attribution) · [reviewed contract](#b0018) |
| [B0019 · 117–159](../../../../../src/storage/accounted_layout.cpp#L117) | Callable definition: AccountedLayout AccountedLayout::make(const resource::MemoryAccount& account,LayoutId id, std::span&lt;const Field&gt; fields,LayoutCon… | calls TupleValidationFailure, aligned, multiply, size; returns AccountedLayout(std::move(data)); growth allocate, emplace, make_accounted_shared; 1 loop sites; source comment (unverified): // At most one first-occurrence equality per field. Reserve this controlled · [reviewed contract](#b0019) |
| [B0020 · 160–163](../../../../../src/storage/accounted_layout.cpp#L160) | Callable definition: const AccountedLayout::Data& AccountedLayout::required() const | calls MemoryFailure; returns *data_ · [reviewed contract](#b0020) |
| [B0021 · 164–164](../../../../../src/storage/accounted_layout.cpp#L164) | Callable definition: LayoutId AccountedLayout::id() const | calls required; returns required().id · [reviewed contract](#b0021) |
| [B0022 · 165–165](../../../../../src/storage/accounted_layout.cpp#L165) | Callable definition: std::span&lt;const Field&gt; AccountedLayout::fields() const & | calls required, fields; returns required().fields() · [reviewed contract](#b0022) |
| [B0023 · 166–166](../../../../../src/storage/accounted_layout.cpp#L166) | Callable definition: LayoutContextView AccountedLayout::context() const & | calls required, context; returns required().context() · [reviewed contract](#b0023) |
| [B0024 · 167–167](../../../../../src/storage/accounted_layout.cpp#L167) | Callable definition: std::optional&lt;LayoutOrigin&gt; AccountedLayout::origin() const | calls required; returns required().origin · [reviewed contract](#b0024) |
| [B0025 · 168–168](../../../../../src/storage/accounted_layout.cpp#L168) | Callable definition: std::size_t AccountedLayout::frozen_payload_bytes() const | calls required, size; returns required().storage.size() · [reviewed contract](#b0025) |
| [B0026 · 169–169](../../../../../src/storage/accounted_layout.cpp#L169) | Callable definition: resource::MemoryStatistics AccountedLayout::account_statistics() const | calls required, statistics; returns required().account.statistics() · [reviewed contract](#b0026) |
| [B0027 · 170–170](../../../../../src/storage/accounted_layout.cpp#L170) | Callable definition: const resource::MemoryAccount& AccountedLayout::query_account() const | calls required; returns required().account · [reviewed contract](#b0027) |
| [B0028 · 171–173](../../../../../src/storage/accounted_layout.cpp#L171) | Callable definition: AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account) const | calls clone_to, required, attribution; returns clone_to(account, required().storage.attribution()) · [reviewed contract](#b0028) |
| [B0029 · 174–190](../../../../../src/storage/accounted_layout.cpp#L174) | Callable definition: AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account, resource::MemoryAttribution attribution) const | calls required, allocate, size, std::max; returns AccountedLayout(std::move(data)); growth allocate, make_accounted_shared; 2 loop sites · [reviewed contract](#b0029) |
| [B0030 · 191–191](../../../../../src/storage/accounted_layout.cpp#L191) | Callable definition: bool AccountedLayout::same_token(const AccountedLayout& other) const noexcept | calls ; returns data_ && data_ == other.data_ · [reviewed contract](#b0030) |
| [B0031 · 192–192](../../../../../src/storage/accounted_layout.cpp#L192) | Callable definition: TupleLayout AccountedLayout::descriptor() const | calls required, TupleLayout; returns TupleLayout(data_) · [reviewed contract](#b0031) |
| [B0032 · 193–193](../../../../../src/storage/accounted_layout.cpp#L193) | Callable definition: bool AccountedLayout::same_token(const TupleLayout& other) const noexcept | calls descriptor, same_token; returns data_ && descriptor().same_token(other) · [reviewed contract](#b0032) |
| [B0033 · 194–198](../../../../../src/storage/accounted_layout.cpp#L194) | Callable definition: bool AccountedLayout::same_descriptor(const AccountedLayout& other) const noexcept | calls context, std::equal, fields, begin; returns data_ && other.data_ && data_-&gt;id == other.data_-&gt;id && data_-&gt;context() == other.data_-&gt;context() … · [reviewed contract](#b0033) |
| [B0034 · 199–202](../../../../../src/storage/accounted_layout.cpp#L199) | Callable definition: TupleValidationIssue AccountedLayout::validation_issue(const Row& values) const noexcept | calls validate, fields, equalities, size; returns {TupleProblem::invalid_layout, FieldId{0}}; validate(data_-&gt;fields(), data_-&gt;equalities(), values.s… · [reviewed contract](#b0034) |
| [B0035 · 203–206](../../../../../src/storage/accounted_layout.cpp#L203) | Callable definition: TupleValidationIssue AccountedLayout::validation_issue(RowView values) const noexcept | calls validate, fields, equalities, size; returns {TupleProblem::invalid_layout, FieldId{0}}; validate(data_-&gt;fields(), data_-&gt;equalities(), values.s… · [reviewed contract](#b0035) |
| [B0036 · 207–211](../../../../../src/storage/accounted_layout.cpp#L207) | Callable definition: AccountedTuple AccountedLayout::tuple(const Row& values, resource::MemoryAttribution attribution) const | calls validation_issue, ok, TupleValidationFailure, AccountedTuple; returns AccountedTuple(*this, AccountedRow::copy_of(required().account, values, attribution)); growth copy_of · [reviewed contract](#b0036) |
| [B0037 · 212–216](../../../../../src/storage/accounted_layout.cpp#L212) | Callable definition: AccountedTuple AccountedLayout::tuple(RowView values, resource::MemoryAttribution attribution) const | calls validation_issue, ok, TupleValidationFailure, AccountedTuple; returns AccountedTuple(*this, AccountedRow::copy_of(required().account, values, attribution)); growth copy_of · [reviewed contract](#b0037) |
| [B0038 · 217–220](../../../../../src/storage/accounted_layout.cpp#L217) | Callable definition: TupleValidationIssue AccountedLayout::validation_issue_view(TupleValuesView values) const noexcept | calls legacy_row, validation_issue, native_view, value_or; returns validation_issue(*legacy); validation_issue(values.native_view().value_or(RowView{})) · [reviewed contract](#b0038) |
| [B0039 · 221–224](../../../../../src/storage/accounted_layout.cpp#L221) | Callable definition: AccountedTuple AccountedLayout::tuple_view(TupleValuesView values,resource::MemoryAttribution attribution) const | calls legacy_row, tuple, native_view, value_or; returns tuple(*legacy,attribution); tuple(values.native_view().value_or(RowView{}),attribution) · [reviewed contract](#b0039) |
| [B0040 · 225–229](../../../../../src/storage/accounted_layout.cpp#L225) | Callable definition: Tuple AccountedLayout::make_public_tuple(const TupleLayout& descriptor,TupleValuesView values) | calls AccountedLayout, Tuple::from_accounted, tuple_view, std::move; returns Tuple::from_accounted(native.tuple_view(std::move(values),{resource::MemoryOwnerKind::output,0})) · [reviewed contract](#b0040) |
| [B0041 · 230–230](../../../../../src/storage/accounted_layout.cpp#L230) | Explanatory comments or spacing. |  |
| [B0042 · 231–238](../../../../../src/storage/accounted_layout.cpp#L231) | Callable definition: LayoutFreezeRegistry::LayoutFreezeRegistry(const resource::MemoryAccount& account, std::span&lt;const TupleLayout&gt; sources, resource… | calls account_, attribution_, sources_, slots_; growth resize; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 239–247](../../../../../src/storage/accounted_layout.cpp#L239) | Callable definition: AccountedLayout LayoutFreezeRegistry::get(std::size_t index) | calls size, MemoryFailure, same_token, emplace; returns *slots_\[i\]; growth emplace; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 248–249](../../../../../src/storage/accounted_layout.cpp#L248) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0044) |

## B0001

[Lines 1–21](../../../../../src/storage/accounted_layout.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:14cb9a3f4dea580faaa45051d4619f33fdae6db6fb554457477dece02addc9c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_layout.cpp: imports \`"crown/storage/accounted_layout.hpp"\`, \`"descriptor.hpp"\`, \`"crown/resource/ownership.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;algorithm&gt;\`, \`&lt;cstring&gt;\`, \`&lt;limits&gt;\`, \`&lt;map&gt;\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage; imports or aliases \`resource::MemoryFailure\`, \`resource::MemoryFault\`, \`Equality=detail::DescriptorEquality\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 22–25](../../../../../src/storage/accounted_layout.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check metadata byte-offset addition. |
| inputs / outputs | Return left+right when representable. |
| invariants | No offset may wrap before allocation. |
| ownership | Inline layout-sizing scalars only. |
| failure | MemoryFailure(overflow) before addition. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 26–29](../../../../../src/storage/accounted_layout.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t multiply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check metadata element-count multiplication. |
| inputs / outputs | Return left*right, including zero, when representable. |
| invariants | Division guard prevents wrap. |
| ownership | Inline layout-sizing scalars only. |
| failure | MemoryFailure(overflow) before multiplication. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0004

[Lines 30–33](../../../../../src/storage/accounted_layout.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t aligned(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round an offset to the requested native alignment. |
| inputs / outputs | Return unchanged aligned value or checked value+padding. |
| invariants | Caller supplies nonzero alignof-derived alignment. |
| ownership | Inline layout-sizing scalars only. |
| failure | Padding overflow propagates from add(). |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0005

[Lines 34–38](../../../../../src/storage/accounted_layout.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool decimal_fits(DecimalParts value, DecimalSpec spec)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact fixed DECIMAL representability from canonical parts. |
| inputs / outputs | Canonical coefficient/scale and valid precision/scale spec return admissibility. |
| invariants | No rounding: source scale&lt;=target scale and integer digits+target scale&lt;=precision; zero has no integer magnitude digits. |
| ownership | Borrows coefficient characters; no formatting or conversion. |
| failure | Noexcept under validated DecimalSpec/canonical parts. |
| cost | O(1) size/signature checks and bounded zero comparison; no digit rescaling/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0006

[Lines 39–42](../../../../../src/storage/accounted_layout.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits(const Value& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch exact decimal-domain checking without constructing text. |
| inputs / outputs | Expected public Decimal returns decimal_fits(parts,spec); another alternative returns false. |
| invariants | No coercion from integer/string to decimal. |
| ownership | Borrowed variant/components only. |
| failure | Noexcept. |
| cost | Fixed type/parts checks, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0007

[Lines 43–46](../../../../../src/storage/accounted_layout.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits(const ScalarView& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch exact decimal-domain checking without constructing text. |
| inputs / outputs | Expected native InlineDecimal returns decimal_fits(parts,spec); another alternative returns false. |
| invariants | No coercion from integer/string to decimal. |
| ownership | Borrowed variant/components only. |
| failure | Noexcept. |
| cost | Fixed type/parts checks, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0008

[Lines 47–60](../../../../../src/storage/accounted_layout.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValidationIssue validate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate row arity, scalar domains and compiled repeated-variable equalities. |
| inputs / outputs | Field/equality spans, arity and borrowed cell reader return the first fixed TupleValidationIssue or success. |
| invariants | Fields/equalities were admitted at layout construction; read is valid and nonthrowing. Scalar-kind precedes decimal-domain checks; repeated equalities follow all fields. |
| ownership | Borrows immutable metadata/cells; creates no owning error text or output row. |
| failure | Noexcept fixed issue result; arity/type/domain/repetition errors do not allocate or throw here. |
| cost | O(fields + equality comparisons/deep string bytes); decimal validation borrows canonical parts rather than rendering. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0009

[Lines 61–73](../../../../../src/storage/accounted_layout.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L73:sha256:8957e23bfc9e0b40b57e1c2910833fcd940a3441706d467c166141d58eb1e279
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace and declare AccountedLayout::Data as LayoutDescriptor backing: account, storage, layout ID, arity/equality/binding dimensions, catalog version and optional origin. |
| inputs / outputs | Data retains account/storage plus id, arity, equality_count/equality_offset, binding_offset/binding_size, catalog_version and origin. Adjacent construction installs descriptor views over that storage. |
| invariants | Identity/version/provenance remain part of the descriptor. field_view, equality_view and context_view borrow bytes from storage and are valid only while the owning Data/backing allocation remains live. |
| ownership | MemoryAccount shares allocation control. MemoryBlock storage owns the transferred field/equality/binding allocation; descriptor views borrow that allocation, while scalar identity/dimension fields and origin are retained metadata. |
| failure | This member declaration adds no validation or handler. The adjacent noexcept constructor transfers already-created account/block state; prior allocation/admission and later method calls retain their own contracts. |
| cost | Fixed Data/descriptor metadata plus the backing block transferred by construction; the views do not copy its field/equality/text payload. Allocation size/work belongs to the factory that creates the block, not a presumed declaration-time allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 74–83](../../../../../src/storage/accounted_layout.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(resource::MemoryAccount owner, resource::MemoryBlock block, LayoutId layout_id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind flat native layout metadata to shared immutable descriptor views. |
| inputs / outputs | Funded fields/equalities/binding block and offsets initialize LayoutDescriptor spans, identity/context/origin and native tuple factory. |
| invariants | Offsets/alignment/counts are validated before this noexcept constructor; spans point only into owned block. |
| ownership | Original account owns block and shared Data/control allocation; no legacy metadata mirror retained. |
| failure | Noexcept adoption; allocation was performed by the factory before entry. |
| cost | Fixed pointer/span/scalar setup, no metadata copy or extra allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0011

[Lines 84–86](../../../../../src/storage/accounted_layout.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::span<const Field> fields() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native field metadata. |
| inputs / outputs | Return arity fields at block start. |
| invariants | Field storage is initialized and aligned. |
| ownership | Borrowed range/string_view requires shared Data/block to survive. |
| failure | Noexcept under admitted offsets. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0012

[Lines 87–89](../../../../../src/storage/accounted_layout.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::span<const Equality> equalities() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow only constructed equality entries. |
| inputs / outputs | Return equality_count records at equality_offset. |
| invariants | Reserved unused equality capacity is not read. |
| ownership | Borrowed range/string_view requires shared Data/block to survive. |
| failure | Noexcept under admitted offsets. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0013

[Lines 90–92](../../../../../src/storage/accounted_layout.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] LayoutContextView context() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable query/catalog context. |
| inputs / outputs | Return catalog version and exact binary binding view. |
| invariants | Binding length is explicit and may include NUL. |
| ownership | Borrowed range/string_view requires shared Data/block to survive. |
| failure | Noexcept under admitted offsets. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0014

[Lines 93–94](../../../../../src/storage/accounted_layout.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L94:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct AccountedLayout::Data:detail::LayoutDescriptor\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct AccountedLayout::Data:detail::LayoutDescriptor\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct AccountedLayout::Data:detail::LayoutDescriptor\` at its lexical source position in src/storage/accounted_layout.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct AccountedLayout::Data:detail::LayoutDescriptor\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0015

[Lines 95–99](../../../../../src/storage/accounted_layout.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view TupleValidationFailure::code()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native tuple validation problems to stable public error-code categories. |
| inputs / outputs | Invalid layout=&gt;invalid_layout; decimal domain=&gt;scalar_overflow; remaining tuple problems=&gt;invalid_tuple. |
| invariants | Mapping preserves the distinction needed by public presentation factories. |
| ownership | Returns static string_view; exception owns only its inline issue. |
| failure | Noexcept. |
| cost | Fixed enum branches, no message allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0016

[Lines 100–110](../../../../../src/storage/accounted_layout.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* TupleValidationFailure::what()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a native tuple issue without allocating during unwinding. |
| inputs / outputs | Problem enum returns a static literal; issue.field remains available separately. |
| invariants | This native wording is intentionally less formatted than public field-index diagnostics. |
| ownership | Returned literal has static lifetime. |
| failure | Noexcept, including fallback status text. |
| cost | Fixed switch, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0018

[Lines 112–116](../../../../../src/storage/accounted_layout.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout AccountedLayout::freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import an existing valid descriptor into native account-owned metadata. |
| inputs / outputs | Account/source descriptor/attribution produce a new immutable layout through make(). |
| invariants | Reject moved/invalid source token first; value-equal descriptors do not automatically share a token. |
| ownership | Copies fields/context/origin into the destination account; retains no source TupleLayout owner. |
| failure | Invalid source raises fixed TupleValidationFailure; make/funding failure publishes no layout. |
| cost | Full native make cost, not a cheap shared descriptor copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0019

[Lines 117–159](../../../../../src/storage/accounted_layout.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout AccountedLayout::make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and build one flat immutable native layout. |
| inputs / outputs | Fields, context, origin and ID produce original-account shared Data plus fields/equality/binding block. |
| invariants | Positive context/origin versions, valid scalar/decimal domains and repeated-variable type consistency. Reserve one equality slot per field; only actual repetitions are exposed. |
| ownership | Metadata block and shared owner are funded by the same account; temporary first-occurrence map uses accounted scratch. |
| failure | Invalid fields or allocation failure release partial block/map through RAII. Fields/equalities are trivial, so no allocating element cleanup. |
| cost | O(fields log distinct variables + binding bytes) admission and O(fields) reserved equality capacity, including unused tail; not hot tuple validation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0020

[Lines 160–163](../../../../../src/storage/accounted_layout.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout::Data& AccountedLayout::required()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate handle presence before accessing native descriptor members. |
| inputs / outputs | Nonempty layout returns Data by const reference. |
| invariants | Default/moved layout has no descriptor to borrow. |
| ownership | Reference borrows this shared Data owner. |
| failure | Empty handle raises MemoryFailure(contract). |
| cost | O(1), allocation-free success. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0021

[Lines 164–164](../../../../../src/storage/accounted_layout.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LayoutId AccountedLayout::id()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read immutable layout ID. |
| inputs / outputs | Copy its numeric ID. |
| invariants | Numeric ID alone is not token identity. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0022

[Lines 165–165](../../../../../src/storage/accounted_layout.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const Field> AccountedLayout::fields()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the admitted native fields. |
| inputs / outputs | Return fields span by value. |
| invariants | Span does not extend Data lifetime; rvalue access is deleted. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0023

[Lines 166–166](../../../../../src/storage/accounted_layout.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LayoutContextView AccountedLayout::context()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native catalog/query context. |
| inputs / outputs | Return version plus binding view. |
| invariants | Binding bytes remain owned by Data; rvalue access is deleted. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0024

[Lines 167–167](../../../../../src/storage/accounted_layout.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<LayoutOrigin> AccountedLayout::origin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect optional physical source provenance. |
| inputs / outputs | Copy table/schema version origin. |
| invariants | Origin is metadata, not mutable database authority. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0025

[Lines 168–168](../../../../../src/storage/accounted_layout.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedLayout::frozen_payload_bytes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure flat retained descriptor payload only. |
| inputs / outputs | Return metadata block logical size. |
| invariants | This excludes Data/control/framing overhead; account_statistics reports real requested usage. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0026

[Lines 169–169](../../../../../src/storage/accounted_layout.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics AccountedLayout::account_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the original query account totals. |
| inputs / outputs | Return account statistics by value. |
| invariants | Statistics cover that account, not solely this descriptor. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0027

[Lines 170–170](../../../../../src/storage/accounted_layout.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& AccountedLayout::query_account()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the account used by tuple/projection factories. |
| inputs / outputs | Return Data account by reference. |
| invariants | Internal borrow retains no independent owner and cannot outlive Data. |
| ownership | Scalars are copied; ranges/references borrow immutable shared Data. |
| failure | Empty/moved handle fails through required(). |
| cost | O(1), no traversal or success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0028

[Lines 171–173](../../../../../src/storage/accounted_layout.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone descriptor bytes while preserving current attribution. |
| inputs / outputs | Destination account produces an independent token through the attributed clone overload. |
| invariants | Same descriptor values do not mean same token; source remains unchanged. |
| ownership | Destination owns its own Data/block; source attribution is copied as a label. |
| failure | Invalid source/funding failure publishes no clone. |
| cost | Underlying complete metadata-copy cost; wrapper adds no second copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0029

[Lines 174–190](../../../../../src/storage/accounted_layout.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone initialized descriptor fields/equalities/binding to another admitted account. |
| inputs / outputs | Destination account/attribution produce independent shared Data preserving ID/context/origin. |
| invariants | Copy only constructed equalities while reserving the original controlled block size; never read unused tail bytes. |
| ownership | Destination account funds block/Data, with no reference to old metadata retained. |
| failure | Allocation failure destroys prepared destination storage and leaves source valid. |
| cost | O(fields + actual equalities + binding bytes), original reserved metadata capacity is charged again. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0030

[Lines 191–191](../../../../../src/storage/accounted_layout.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedLayout::same_token(const AccountedLayout& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact admitted native layout identity. |
| inputs / outputs | True only for nonempty handles sharing the same Data. |
| invariants | Independent/equal descriptor clones remain different tokens. |
| ownership | Reads shared handle addresses only. |
| failure | Noexcept; empty handles compare false. |
| cost | O(1). |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0031

[Lines 192–192](../../../../../src/storage/accounted_layout.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout AccountedLayout::descriptor()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a public read-only handle to the existing funded native descriptor. |
| inputs / outputs | Valid AccountedLayout returns TupleLayout sharing concrete Data/control/deleter. |
| invariants | Public handle keeps the same token and native tuple-factory callback; no legacy field/binding mirror. |
| ownership | Shared immutable ownership extends native metadata lifetime without deep copy. |
| failure | Empty handle fails through required(). |
| cost | O(1) shared-owner copy, no new allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0032

[Lines 193–193](../../../../../src/storage/accounted_layout.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedLayout::same_token(const TupleLayout& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test native/public descriptor token identity. |
| inputs / outputs | Nonempty native handle compares its shared descriptor token to other. |
| invariants | Structural equality cannot authorize token-based native operations. |
| ownership | Temporary public descriptor only shares existing ownership. |
| failure | Noexcept; empty native handle returns false. |
| cost | O(1), no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0033

[Lines 194–198](../../../../../src/storage/accounted_layout.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedLayout::same_descriptor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare immutable descriptor values rather than token identity. |
| inputs / outputs | Both valid layouts compare ID/context/origin/arity and every Field. |
| invariants | Equality records are derived from fields; reserved padding/unused capacity is not compared. |
| ownership | Borrows fields/binding bytes in both Data owners. |
| failure | Noexcept, empty handles return false. |
| cost | O(fields + compared binding bytes); not an O(1) token test. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0034

[Lines 199–202](../../../../../src/storage/accounted_layout.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValidationIssue AccountedLayout::validation_issue(const Row& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate borrowed values without throwing or constructing a tuple. |
| inputs / outputs | legacy Row returns invalid-layout or first arity/type/domain/repetition issue. |
| invariants | Source storage remains live/unchanged and scalar alternatives satisfy their value invariants. |
| ownership | Borrows admitted metadata and input; no account/block is acquired. |
| failure | Noexcept fixed issue result; invalid handle is reported, not dereferenced. |
| cost | O(fields + compiled equality comparisons/deep strings); no formatting/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0035

[Lines 203–206](../../../../../src/storage/accounted_layout.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValidationIssue AccountedLayout::validation_issue(RowView values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate borrowed values without throwing or constructing a tuple. |
| inputs / outputs | compact RowView returns invalid-layout or first arity/type/domain/repetition issue. |
| invariants | Source storage remains live/unchanged and scalar alternatives satisfy their value invariants. |
| ownership | Borrows admitted metadata and input; no account/block is acquired. |
| failure | Noexcept fixed issue result; invalid handle is reported, not dereferenced. |
| cost | O(fields + compiled equality comparisons/deep strings); no formatting/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0036

[Lines 207–211](../../../../../src/storage/accounted_layout.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedLayout::tuple(const Row& values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate then copy one immutable native tuple under this layout account. |
| inputs / outputs | legacy Row and row attribution return layout-retaining AccountedTuple with owned deep bytes. |
| invariants | Reject first issue before row copy; exact repeated-variable and decimal constraints are maintained. |
| ownership | Tuple shares this immutable layout and owns one AccountedRow block in its original account. |
| failure | Validation raises fixed TupleValidationFailure; row funding/copy failure publishes no tuple. |
| cost | Full field/equality validation plus two-pass row sizing/copy and actual deep bytes, one row allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0037

[Lines 212–216](../../../../../src/storage/accounted_layout.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedLayout::tuple(RowView values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate then copy one immutable native tuple under this layout account. |
| inputs / outputs | compact RowView and row attribution return layout-retaining AccountedTuple with owned deep bytes. |
| invariants | Reject first issue before row copy; exact repeated-variable and decimal constraints are maintained. |
| ownership | Tuple shares this immutable layout and owns one AccountedRow block in its original account. |
| failure | Validation raises fixed TupleValidationFailure; row funding/copy failure publishes no tuple. |
| cost | Full field/equality validation plus two-pass row sizing/copy and actual deep bytes, one row allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0038

[Lines 217–220](../../../../../src/storage/accounted_layout.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValidationIssue AccountedLayout::validation_issue_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate public values through its existing legacy/native adapter. |
| inputs / outputs | TupleValuesView dispatches to borrowed Row or RowView; no source represents empty compact row. |
| invariants | Validation does not export ordinary Values or grant ownership to the native adapter. |
| ownership | Tuple-derived view may retain payload for the call; explicit borrowed inputs still need caller lifetime. |
| failure | Noexcept fixed issue result. |
| cost | Representation dispatch plus normal field/equality validation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0039

[Lines 221–224](../../../../../src/storage/accounted_layout.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedLayout::tuple_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import public values without an ordinary Row mirror. |
| inputs / outputs | TupleValuesView and attribution delegate to matching validated tuple factory. |
| invariants | An absent representation is an empty row and is accepted only by matching zero-arity layout. |
| ownership | Output owns copied native bytes; input ownership is not retained as a second payload. |
| failure | Underlying fixed validation/memory failures propagate; no extra catch or translation here. |
| cost | Dispatch plus normal validation/two-pass native row copy, no export/temporary Row. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0040

[Lines 225–229](../../../../../src/storage/accounted_layout.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple AccountedLayout::make_public_tuple(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bridge native fixed tuple-validation failures to the owning public Error boundary. |
| inputs / outputs | A native descriptor and borrowed values produce an original-account public Tuple through native tuple validation/copy and from_accounted transfer. |
| invariants | Descriptor must be the callback-bearing native layout; constructor/data pointer are shared from that same token, not imported from a foreign descriptor. |
| ownership | Retains existing native layout/account; output attribution is output:0 and no legacy Row mirror is stored. |
| failure | Only TupleValidationFailure is caught and translated to Error with its existing code/message. Resource/allocation failures propagate unchanged; this is a real presentation boundary. |
| cost | Actual native validation, row copy and shared output allocation; when dispatched by TupleLayout::tuple, public validation has already run once. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0042

[Lines 231–238](../../../../../src/storage/accounted_layout.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LayoutFreezeRegistry::LayoutFreezeRegistry(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a construction-only alias-token cache for imported descriptors. |
| inputs / outputs | Account, borrowed source span and attribution validate all source handles and allocate optional native slots. |
| invariants | Source objects/span must remain alive and unmoved until registry destruction; identical source tokens share one frozen result. |
| ownership | Slots are accounted scratch; returned native layouts own independent copied metadata, not source handles. |
| failure | Invalid source/funding failure publishes no registry result. |
| cost | O(source count) validation/slot initialization and accounted temporary capacity; no permanent owner registry. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0043

[Lines 239–247](../../../../../src/storage/accounted_layout.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout LayoutFreezeRegistry::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze the first occurrence of one source token and reuse it for aliases. |
| inputs / outputs | Valid source index scans prefix for same token, lazily fills its first slot and returns shared AccountedLayout. |
| invariants | Equal descriptors with distinct source tokens stay distinct; aliases get exactly one destination token. |
| ownership | Registry borrows source objects; result retains no source reference and outlives registry. |
| failure | Bad index or moved source violates registry contract; lazy freeze failure leaves that slot empty/retryable. |
| cost | O(index+1) prefix scan per get plus at most one freeze per distinct token; repeated construction lookups can sum to O(n²). |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0044

[Lines 248–249](../../../../../src/storage/accounted_layout.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L249:sha256:7089e9cc52c39a53c28433397476fe0fa1e71e49e678f867277ec88cc7e152ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_layout.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
