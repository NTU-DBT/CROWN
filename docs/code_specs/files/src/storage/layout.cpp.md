# `src/storage/layout.cpp` — block usage map

[Source](../../../../../src/storage/layout.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `c6b6d6cc3b898f2b79f70fc21fa6eb953d414bc8901f35947aaeb69c45b6169b`. 226 lines partitioned into 45 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/storage/layout.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 15–25](../../../../../src/storage/layout.cpp#L15) | Type/record definition: struct TupleLayout::Data:detail::LayoutDescriptor |  · [reviewed contract](#b0002) |
| [B0003 · 26–30](../../../../../src/storage/layout.cpp#L26) | Type/record definition: struct Projection::Data:detail::ProjectionDescriptor |  · [reviewed contract](#b0003) |
| [B0004 · 31–32](../../../../../src/storage/layout.cpp#L31) | declares namespace scope. |  · [reviewed contract](#b0004) |
| [B0005 · 33–36](../../../../../src/storage/layout.cpp#L33) | Type/record definition: struct LegacyTuplePayload:detail::TuplePayload |  · [reviewed contract](#b0005) |
| [B0006 · 37–42](../../../../../src/storage/layout.cpp#L37) | Type/record definition: struct NativeTuplePayload:detail::TuplePayload |  · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../src/storage/layout.cpp#L43) | Callable definition: void require(bool value,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool value,std::string_view code,std::string_view message) { if (!value) throw Error(s… · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../src/storage/layout.cpp#L44) | Explanatory comments or spacing. | source comment (unverified): // Inclusion of exact decimal domains; no conversion/rounding is performed. · [reviewed contract](#b0008) |
| [B0009 · 45–50](../../../../../src/storage/layout.cpp#L45) | Callable definition: bool fits_domain(const Field& source,const Field& target) | calls ; returns false; true; source comment (unverified): // Inclusion of exact decimal domains; no conversion/rounding is performed. · [reviewed contract](#b0009) |
| [B0010 · 51–52](../../../../../src/storage/layout.cpp#L51) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 53–71](../../../../../src/storage/layout.cpp#L53) | Callable definition: TupleLayout::TupleLayout(LayoutId id,std::vector&lt;Field&gt; fields,LayoutContext context,std::optional&lt;LayoutOrigin&gt; origin) | calls require, size, type_name, emplace; guard require(context.catalog_version&gt;0,"invalid_layout","layout catalog version must be positive");; growth emplace, make_shared, push_back; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 72–72](../../../../../src/storage/layout.cpp#L72) | Callable definition: LayoutId TupleLayout::id() const | calls require, bool; guard LayoutId TupleLayout::id() const { require(bool(data_),"invalid_layout","moved-from tuple layout");…; returns data_-&gt;layout_id · [reviewed contract](#b0012) |
| [B0013 · 73–73](../../../../../src/storage/layout.cpp#L73) | Callable definition: const std::span&lt;const Field&gt;& TupleLayout::fields() const | calls id; returns data_-&gt;field_view · [reviewed contract](#b0013) |
| [B0014 · 74–74](../../../../../src/storage/layout.cpp#L74) | Callable definition: const LayoutContextView& TupleLayout::context() const | calls id; returns data_-&gt;context_view · [reviewed contract](#b0014) |
| [B0015 · 75–75](../../../../../src/storage/layout.cpp#L75) | Callable definition: const std::optional&lt;LayoutOrigin&gt;& TupleLayout::origin() const | calls id; returns data_-&gt;origin_value · [reviewed contract](#b0015) |
| [B0016 · 76–76](../../../../../src/storage/layout.cpp#L76) | Callable definition: bool TupleLayout::same_token(const TupleLayout& other) const noexcept | calls ; returns data_ && data_==other.data_ · [reviewed contract](#b0016) |
| [B0017 · 77–77](../../../../../src/storage/layout.cpp#L77) | Callable definition: bool TupleLayout::same_token(const AccountedLayout& other) const noexcept | calls same_token; returns other.same_token(*this) · [reviewed contract](#b0017) |
| [B0018 · 78–80](../../../../../src/storage/layout.cpp#L78) | Callable definition: bool TupleLayout::same_descriptor(const TupleLayout& other) const | calls id, std::ranges::equal, fields, context; returns id()==other.id() && std::ranges::equal(fields(),other.fields()) && context()==other.context() && or… · [reviewed contract](#b0018) |
| [B0019 · 81–89](../../../../../src/storage/layout.cpp#L81) | Callable definition: void TupleLayout::validate(const Row& values) const | calls fields, require, size, type_of; guard require(values.size()==schema.size(),"invalid_tuple","tuple arity differs from compiled layout");; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 90–105](../../../../../src/storage/layout.cpp#L90) | Callable definition: void TupleLayout::validate_view(TupleValuesView values) const | calls legacy_row, validate, fields, require; guard require(values.size()==schema.size(),"invalid_tuple","tuple arity differs from compiled layout");; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 106–108](../../../../../src/storage/layout.cpp#L106) | Explanatory comments or spacing. | source comment (unverified): // Public validation preserves formatted Error diagnostics. Native descriptor · [reviewed contract](#b0021) |
| [B0022 · 109–113](../../../../../src/storage/layout.cpp#L109) | Callable definition: Tuple TupleLayout::tuple(const Row& values) const | calls validate, make_native_tuple, TupleValuesView::borrow, Tuple; returns data_-&gt;make_native_tuple(*this,TupleValuesView::borrow(values)); Tuple(*this,std::make_shared&lt;Legac…; growth make_shared; source comment (unverified): // Public validation preserves formatted Error diagnostics. Native descriptor · [reviewed contract](#b0022) |
| [B0023 · 114–118](../../../../../src/storage/layout.cpp#L114) | Callable definition: Tuple TupleLayout::tuple(Row&& values) const | calls validate, make_native_tuple, TupleValuesView::borrow, Tuple; returns data_-&gt;make_native_tuple(*this,TupleValuesView::borrow(values)); Tuple(*this,std::make_shared&lt;Legac…; growth make_shared · [reviewed contract](#b0023) |
| [B0024 · 119–125](../../../../../src/storage/layout.cpp#L119) | Callable definition: Tuple TupleLayout::tuple_view(TupleValuesView values) const | calls validate_view, make_native_tuple, std::move, Tuple; returns data_-&gt;make_native_tuple(*this,std::move(values)); Tuple(*this,std::make_shared&lt;LegacyTuplePayload&gt;…; growth make_shared; source comment (unverified): // Explicit standalone compiler/tool owning output. Runtime descriptors always · [reviewed contract](#b0024) |
| [B0025 · 126–127](../../../../../src/storage/layout.cpp#L126) | Callable definition: Tuple::Tuple(TupleLayout layout,std::shared_ptr&lt;const detail::TuplePayload&gt; values) noexcept :layout_(std::move(layout)),payload_… | calls layout_, std::move, payload_ · [reviewed contract](#b0025) |
| [B0026 · 128–129](../../../../../src/storage/layout.cpp#L128) | Explanatory comments or spacing. | source comment (unverified): // Standalone rows deep-copy their values; admitted native payloads share their · [reviewed contract](#b0026) |
| [B0027 · 130–133](../../../../../src/storage/layout.cpp#L130) | Callable definition: Tuple::Tuple(const Tuple& other):layout_(other.layout_) | calls layout_; growth make_shared; source comment (unverified): // Standalone rows deep-copy their values; admitted native payloads share their · [reviewed contract](#b0027) |
| [B0028 · 134–148](../../../../../src/storage/layout.cpp#L134) | Callable definition: Tuple Tuple::from_accounted(AccountedTuple row) | calls layout, query_account, attribution, statistics; returns Tuple(std::move(layout),std::move(owner)); growth make_accounted_shared; source comment (unverified): // The constructor only moves an admitted tuple and copies account handles. · [reviewed contract](#b0028) |
| [B0029 · 149–149](../../../../../src/storage/layout.cpp#L149) | Callable definition: bool Tuple::is_accounted() const noexcept | calls bool; returns payload_ && bool(payload_-&gt;account) · [reviewed contract](#b0029) |
| [B0030 · 150–150](../../../../../src/storage/layout.cpp#L150) | Callable definition: resource::MemoryUsage Tuple::memory_usage() const noexcept | calls ; returns payload_?payload_-&gt;usage:resource::MemoryUsage{} · [reviewed contract](#b0030) |
| [B0031 · 151–154](../../../../../src/storage/layout.cpp#L151) | Callable definition: resource::MemoryStatistics Tuple::account_statistics() const | calls is_accounted, resource::MemoryFailure, statistics; returns payload_-&gt;account.statistics() · [reviewed contract](#b0031) |
| [B0032 · 155–161](../../../../../src/storage/layout.cpp#L155) | Callable definition: Tuple& Tuple::operator=(const Tuple& other) | calls std::swap, swap; returns *this · [reviewed contract](#b0032) |
| [B0033 · 162–167](../../../../../src/storage/layout.cpp#L162) | Callable definition: Tuple& Tuple::operator=(Tuple&& other) noexcept | calls ; returns *this · [reviewed contract](#b0033) |
| [B0034 · 168–168](../../../../../src/storage/layout.cpp#L168) | Explanatory comments or spacing. |  |
| [B0035 · 169–187](../../../../../src/storage/layout.cpp#L169) | Callable definition: Projection::Projection(TupleLayout source,TupleLayout target,std::vector&lt;FieldId&gt; fields) | calls require, context, size, fields; guard require(source.context()==target.context(),"invalid_projection","projection layouts belong to diffe…; growth emplace, make_shared; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 188–188](../../../../../src/storage/layout.cpp#L188) | Callable definition: const TupleLayout& Projection::source() const | calls require, bool; guard const TupleLayout& Projection::source() const { require(bool(data_),"invalid_projection","moved-fro…; returns data_-&gt;source · [reviewed contract](#b0036) |
| [B0037 · 189–189](../../../../../src/storage/layout.cpp#L189) | Callable definition: const TupleLayout& Projection::target() const | calls source; returns data_-&gt;target · [reviewed contract](#b0037) |
| [B0038 · 190–190](../../../../../src/storage/layout.cpp#L190) | Callable definition: const std::span&lt;const FieldId&gt;& Projection::fields() const | calls source; returns data_-&gt;field_view · [reviewed contract](#b0038) |
| [B0039 · 191–191](../../../../../src/storage/layout.cpp#L191) | Callable definition: bool Projection::same_token(const Projection& other) const noexcept | calls ; returns data_ && data_==other.data_ · [reviewed contract](#b0039) |
| [B0040 · 192–192](../../../../../src/storage/layout.cpp#L192) | Callable definition: bool Projection::same_token(const AccountedProjection& other) const noexcept | calls same_token, descriptor; returns other && same_token(other.descriptor()) · [reviewed contract](#b0040) |
| [B0041 · 193–199](../../../../../src/storage/layout.cpp#L193) | Callable definition: Tuple Projection::apply(const Tuple& tuple) const | calls require, source, same_token, layout; guard require(source().same_token(tuple.layout()),"layout_mismatch","projection input has a different imm…; returns data_-&gt;apply_native_tuple(*this,tuple); target().tuple(std::move(result)); growth push_back, reserve; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 200–209](../../../../../src/storage/layout.cpp#L200) | Callable definition: TupleLayout table_layout(LayoutId id,const Catalog& schema,TableId table,std::string binding) | calls catalog::validate_catalog, require, size, push_back; guard require(table.value&lt;schema.tables.size(),"invalid_layout","table layout source is out of range");; returns {id,std::move(fields),{schema.version,std::move(binding)},LayoutOrigin{table,input.source_schema_ve…; growth push_back; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 210–217](../../../../../src/storage/layout.cpp#L210) | Callable definition: TupleLayout scope_layout(LayoutId id,const Query& query,std::span&lt;const VariableId&gt; variables,LayoutContext context) | calls require, size, push_back, std::move; guard require(variable.value&lt;query.variables.size(),"invalid_layout","scope variable is out of range");; returns {id,std::move(fields),std::move(context)}; growth push_back; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 218–225](../../../../../src/storage/layout.cpp#L218) | Callable definition: TupleLayout projected_layout(LayoutId id,const TupleLayout& source,std::span&lt;const FieldId&gt; fields) | calls require, fields, size, push_back; guard require(field.value&lt;source.fields().size(),"invalid_projection","projection source field is out of …; returns {id,std::move(selected),{source.context().catalog_version,std::string(source.context().binding)}}; growth push_back; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 226–226](../../../../../src/storage/layout.cpp#L226) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0045) |

## B0001

[Lines 1–14](../../../../../src/storage/layout.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/layout.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect public layout/projection facades to the concrete descriptor and tuple payload implementations. |
| inputs / outputs | Includes public/native ownership interfaces and standard algorithm/map utilities; opens the storage namespace. |
| invariants | This translation unit supplies the concrete standard owners and public bridging paths, not SQL NULL values or name resolution. |
| ownership | Includes and namespace declarations create no per-query owner; following concrete Data types own their backing. |
| failure | Compilation requires matching declarations; this block performs no runtime admission. |
| cost | Compile-time dependencies only; runtime costs are in the constructors and operations below. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0002

[Lines 15–25](../../../../../src/storage/layout.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleLayout::Data:detail::LayoutDescriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a standalone immutable layout descriptor and expose views into that same backing. |
| inputs / outputs | Takes owned field/equality vectors, context, layout ID and optional origin; installs base descriptor spans and views. |
| invariants | The moved vectors/context remain unchanged after construction, keeping field/equality spans and binding text stable. |
| ownership | The concrete shared Data owns standard vectors/string; conversion to the descriptor base preserves the concrete shared control block and deleter. |
| failure | This constructor moves already prepared backing and installs views; caller-side argument preparation and shared allocation may fail before publication. |
| cost | Constant container moves and span assignments after preparation; final-owner destruction traverses/frees retained vectors and context, with no query-account claim. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp) |

## B0003

[Lines 26–30](../../../../../src/storage/layout.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Projection::Data:detail::ProjectionDescriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a compiled standalone field-gather program while retaining its exact source and target layout tokens. |
| inputs / outputs | Source/target handles and an owned ordered FieldId vector in; base field_view borrows the moved vector. |
| invariants | Field order and repetition are preserved; the immutable backing outlives every borrowed field span. |
| ownership | Concrete Data owns standard field storage and shared layout handles; base conversions keep its actual deleter. |
| failure | The constructor itself moves prepared values; allocation occurs in surrounding make_shared/caller preparation. |
| cost | Constant moves after preparation; retained size is proportional to selected fields plus shared handles, and last release includes that backing/layout teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0004

[Lines 31–32](../../../../../src/storage/layout.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:f4f8121dd2388b30f27a1454c1f3bd3ed0db6b42a9f01bb0e4cc53e5a048e339
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/layout.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 33–36](../../../../../src/storage/layout.cpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LegacyTuplePayload:detail::TuplePayload
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an explicit compiler/tool tuple as an owning ordinary Row. |
| inputs / outputs | A prepared Row moves into owned; legacy points at that member. |
| invariants | The payload object is immovable after shared construction, so its row address stays stable; values are non-null core scalars. |
| ownership | The concrete payload owns its row/string/Decimal storage; base legacy is only a view and the original shared deleter destroys the concrete owner. |
| failure | The Row move constructor is noexcept here; allocation/copy preparation belongs to the surrounding tuple factory. |
| cost | Constant Row move; legacy tuple copies elsewhere deep-copy fields/variable bytes and final release destroys the owned row. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/tuple_payload.hpp](../../../../../src/storage/tuple_payload.hpp) |

## B0006

[Lines 37–42](../../../../../src/storage/layout.cpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeTuplePayload:detail::TuplePayload
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an admitted native tuple into a public payload without exporting an ordinary Row. |
| inputs / outputs | Existing MemoryAccount and AccountedTuple in; records the account handle and a native RowView into owned. |
| invariants | The view refers to the moved tuple payload, not caller scratch; this constructor does no admission or account refill. |
| ownership | Owned keeps native row/layout allocations alive; the concrete shared control block and original account fund the public bridge outside this constructor. |
| failure | Noexcept moves/copies of admitted owners; surrounding accounted shared allocation can fail before returning a public tuple. |
| cost | Constant owner transfers and view setup, no deep scalar copy; final release may release the row, layout and account ownership chain. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/tuple_payload.hpp](../../../../../src/storage/tuple_payload.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0007

[Lines 43–43](../../../../../src/storage/layout.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,std::string_view code,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep public layout/projection precondition diagnostics at their existing boundary. |
| inputs / outputs | Condition plus borrowed code/message in; returns on success or throws owning Error on false. |
| invariants | Valid calls construct no diagnostic strings; a rejected public precondition remains an exception rather than an unchecked access. |
| ownership | Borrows code/message until failure formatting; Error owns copied diagnostic text. |
| failure | False constructs Error, and diagnostic allocation can itself fail; no caller state is mutated here. |
| cost | Constant successful condition check; owning string/exception work only on rejection. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0008

[Lines 44–44](../../../../../src/storage/layout.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Inclusion of exact decimal domains; no conversion/rounding is performed.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the proof obligation for the following projection-domain predicate. |
| inputs / outputs | Source comment defines inclusion of complete exact domains, not a test of one observed row. |
| invariants | A permitted mapping changes neither scalar value nor rounding; the following function checks type/precision/scale inclusion. |
| ownership | Documentation only; no extra descriptor or value storage. |
| failure | No executable failure or admission is introduced by this comment. |
| cost | No runtime work; the predicate itself is fixed descriptor arithmetic. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0009

[Lines 45–50](../../../../../src/storage/layout.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits_domain(const Field& source,const Field& target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check conservative exact scalar-domain inclusion before compiling a projection. |
| inputs / outputs | Two previously validated Field descriptors in; true when kinds agree and any fixed target decimal domain contains the full source domain. |
| invariants | Generic target decimal admits fixed/generic sources; fixed target requires a fixed source with no greater scale or integral-digit capacity. |
| ownership | Borrows descriptor fields and returns a scalar Boolean, retaining no value or owner. |
| failure | No throwing path or value conversion; private callers supply valid decimal specifications before precision-minus-scale arithmetic. |
| cost | Constant inline type/optional checks and bounded descriptor arithmetic; no decimal rendering or allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0010

[Lines 51–52](../../../../../src/storage/layout.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/layout.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/layout.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/layout.cpp\` at its lexical source position in src/storage/layout.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/layout.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 53–71](../../../../../src/storage/layout.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout::TupleLayout(LayoutId id,std::vector<Field> fields,LayoutContext context,std::optional<LayoutOrigin> origin)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and freeze a fresh standalone layout token with compiled repeated-variable equalities. |
| inputs / outputs | Owned fields/context and optional source origin in; a shared immutable Data out. Positive catalog/source versions and valid kinds/decimal domains are required. |
| invariants | Repeated variables must have one scalar kind; each repetition gets an equality against its first position. Distinct constructions remain distinct tokens even with equal descriptors. |
| ownership | The completed Data owns moved standard backing; transient first-position map/equality preparation is local. No MemoryAccount is installed by this constructor. |
| failure | Invalid versions/specifications/types or incompatible repeated kinds reject before assigning data_; preparation/shared allocations may throw without publishing a descriptor. |
| cost | For F fields, O(F log F) worst-case first-variable map work and O(F) equality storage, plus kind-name temporary strings and shared allocation; cold descriptor construction, not per-row work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0012

[Lines 72–72](../../../../../src/storage/layout.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LayoutId TupleLayout::id() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the layout ID after checking the facade still owns a descriptor. |
| inputs / outputs | Valid handle in; its stored LayoutId out. |
| invariants | An empty moved-from facade is rejected; the numeric ID alone does not establish token identity. |
| ownership | Returns a scalar copy without retaining a new owner. |
| failure | Empty data_ throws invalid_layout; diagnostic construction may allocate. |
| cost | Constant pointer check and scalar read on success, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0013

[Lines 73–73](../../../../../src/storage/layout.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::span<const Field>& TupleLayout::fields() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable ordered field range from a live descriptor. |
| inputs / outputs | Calls id() for presence validation, then returns a reference to the descriptor span. |
| invariants | This does not validate tuples or extend view lifetime; keep any handle sharing the descriptor alive while using the range. |
| ownership | Returned reference and its Field elements borrow Data backing; no vector copy or new shared owner. |
| failure | Moved-from handle is rejected through id(). |
| cost | Constant checked getter with no field scan or allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0014

[Lines 74–74](../../../../../src/storage/layout.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const LayoutContextView& TupleLayout::context() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the catalog/query binding view stored in a live descriptor. |
| inputs / outputs | Returns catalog version and binary binding string_view after id() presence validation. |
| invariants | Context equality is a value-level compatibility check, distinct from sharing a layout token or allocation account. |
| ownership | The reference and binding bytes require a surviving descriptor owner; this getter retains none. |
| failure | Moved-from handle is rejected through id(). |
| cost | Constant checked getter; later binding-byte comparison/copy has its own length cost. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0015

[Lines 75–75](../../../../../src/storage/layout.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<LayoutOrigin>& TupleLayout::origin() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional physical-source provenance from a live layout. |
| inputs / outputs | Returns the descriptor optional table/source-schema version after id() validation. |
| invariants | An absent origin is allowed for logical or projected layouts; presence alone does not validate an external catalog. |
| ownership | Borrows the optional record from Data; no additional owner. |
| failure | Moved-from handle is rejected through id(). |
| cost | Constant checked access with no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0016

[Lines 76–76](../../../../../src/storage/layout.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleLayout::same_token(const TupleLayout& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact immutable layout ownership identity without inspecting descriptor values. |
| inputs / outputs | Two facade handles in; true only for a nonempty shared Data pointer. |
| invariants | Equal field/ID/context/origin values do not make independently constructed tokens equal; two empty handles are not equal tokens. |
| ownership | Reads shared-pointer identity without making another owner. |
| failure | Noexcept; empty/moved-from handles simply compare false. |
| cost | Constant pointer-presence/equality work, independent of arity and binding length. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0017

[Lines 77–77](../../../../../src/storage/layout.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleLayout::same_token(const AccountedLayout& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a public layout token with its accounted counterpart. |
| inputs / outputs | Delegates to the accounted owner, whose readable descriptor shares its existing Data token. |
| invariants | Representation/funding differs without changing token identity; independently frozen equal descriptors still differ. |
| ownership | The counterpart may form a temporary shared descriptor handle; no field/binding/control-block copy is allocated. |
| failure | Noexcept; an empty accounted layout compares false. |
| cost | Constant handle/refcount and pointer comparison work, not a descriptor scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0018

[Lines 78–80](../../../../../src/storage/layout.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleLayout::same_descriptor(const TupleLayout& other) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare semantic descriptor values when exact runtime token sharing is not required. |
| inputs / outputs | Compares layout IDs, complete ordered Fields, context values and optional origins. |
| invariants | This does not rebind tokens, check physical data or compare allocation accounts/factory callbacks; equal fields imply the same derived repeated-variable facts. |
| ownership | Borrows both descriptors and returns a Boolean; no new owner or deep copy. |
| failure | Any moved-from handle access rejects via the checked getters. |
| cost | O(F+B) worst-case field and binding-byte comparisons with short-circuiting; no allocation on valid comparisons. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0019

[Lines 81–89](../../../../../src/storage/layout.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleLayout::validate(const Row& values) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate an external ordinary core row against the complete layout contract. |
| inputs / outputs | Borrowed Row in; normal return only for matching arity, exact scalar kinds, fixed-decimal bounds and repeated-variable equalities. |
| invariants | Values stay non-null and unchanged; full-row equalities are checked before tuple construction. |
| ownership | Borrows the row/layout. Decimal admission calls catalog::decimal_fits, which renders temporary decimal text rather than retaining a payload. |
| failure | Bad arity/kind/equality rejects with invalid_tuple; decimal overflow rejects with scalar_overflow. Rendering/diagnostic allocation can also throw before any tuple publication. |
| cost | O(F+E) field/equality visits plus actual scalar comparison/rendering costs; valid fixed-decimal legacy validation may allocate text, so it is not an allocation-free native primitive. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp) |

## B0020

[Lines 90–105](../../../../../src/storage/layout.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleLayout::validate_view(TupleValuesView values) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a borrowed or owning public value view without exporting an ordinary row. |
| inputs / outputs | A TupleValuesView in; legacy-row views route to validate(Row), while native views check tagged scalar alternatives and inline decimal parts. |
| invariants | Arity, exact kinds, fixed-decimal domains and every compiled repeated-variable equality are preserved; SQL NULL/coercion is not added. |
| ownership | The view may retain an existing payload, or explicitly borrow caller storage; no new row or deep string copy is made by the native branch. |
| failure | Layout/tuple/domain errors keep public Error diagnostics; legacy decimal rendering and rejected diagnostics can allocate. Private/native valid views require their owners to remain alive. |
| cost | O(F+E) visits plus repeated scalar comparison bytes; native decimal checks use bounded inline parts with no render allocation, whereas the legacy branch retains its own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0021

[Lines 106–108](../../../../../src/storage/layout.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Public validation preserves formatted Error diagnostics.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the extra validation boundary in public native-backed tuple construction. |
| inputs / outputs | This source note distinguishes public formatted diagnostics from direct accounted tuple factories. |
| invariants | The public facade currently validates and then invokes a factory that validates again; direct AccountedLayout avoids this public duplicate pass. |
| ownership | Comment creates no mirror or owner; concrete factory callbacks retain the original account. |
| failure | Documentation does not catch, suppress or weaken either validation boundary. |
| cost | No runtime instrumentation; callers should account for both existing passes when using the public bridge. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0022

[Lines 109–113](../../../../../src/storage/layout.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple TupleLayout::tuple(const Row& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an owning public tuple under the layout chosen by its caller. |
| inputs / outputs | A Row is validated against fields/repeated-variable equalities, then copied into a legacy payload or passed to the native descriptor factory. |
| invariants | Public validation preserves Error diagnostics before dispatch; a native factory independently validates/funds payload. Tokens identify immutable layout ownership, not merely equal descriptors. |
| ownership | Legacy compiler/tool path owns ordinary Row storage; native descriptor path retains the original funded account and shared payload owner. |
| failure | Public invalid-layout/type/arity/repetition/decimal errors occur before tuple publication; native factory translates fixed tuple validation errors to Error, while memory failures propagate. |
| cost | Public validation O(fields + repeated equalities/deep comparisons), then actual copy/allocation. Native descriptor path currently performs a second corresponding validation pass; no speedup is asserted. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0023

[Lines 114–118](../../../../../src/storage/layout.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple TupleLayout::tuple(Row&& values) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a public owning tuple from an rvalue while preserving the same admission boundary. |
| inputs / outputs | Validates the still-live caller Row; native-backed descriptors invoke their existing factory, otherwise move the Row into a legacy payload. |
| invariants | No field/string ownership is stolen before validation. The native branch copies into its accounted payload rather than adopting ordinary Row storage. |
| ownership | Legacy branch moves the row into a new standard shared payload; native branch funds its payload/public owner with the descriptor account. |
| failure | Validation or allocation/factory failure returns no tuple. The legacy shared allocation happens before the payload constructor moves the Row; native path only borrows it during copying. |
| cost | Full validation cost plus shared allocation; legacy success moves row backing, native success pays its additional validation and deep payload copy. Neither branch is universally allocation-free. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0024

[Lines 119–125](../../../../../src/storage/layout.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple TupleLayout::tuple_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct owning output from borrowed legacy or native scalar views. |
| inputs / outputs | TupleValuesView is publicly validated, then routed to native factory or explicitly exported into legacy compiler/tool Row ownership. |
| invariants | Borrowed view must stay valid through validation/copy; no borrowed payload is retained as public owning output. |
| ownership | Native factory owns funded deep payload and control block; legacy path explicitly materializes a Row. |
| failure | Validation/allocation failures publish no tuple; native validation is additionally translated at the public factory boundary. |
| cost | Actual fields/deep-byte copy plus validation; native path currently repeats schema/equality validation. It is not a zero-copy borrowed conversion. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0025

[Lines 126–127](../../../../../src/storage/layout.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple::Tuple(TupleLayout layout,std::shared_ptr<const detail::TuplePayload> values) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared immutable layout/payload pair at the private tuple publication boundary. |
| inputs / outputs | Validated layout handle and complete shared payload in; member owners are moved into the new tuple. |
| invariants | Only friend factories call this constructor and establish compatible layout/value meaning before entry. |
| ownership | Moves both owners without copying scalar/string contents. |
| failure | Noexcept and no local rejection; invalid pair construction would violate the private factory contract. |
| cost | Constant owner moves, no allocation; eventual last-owner release has backing-dependent teardown costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0026

[Lines 128–129](../../../../../src/storage/layout.cpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Standalone rows deep-copy their values;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that public Tuple copy has two representation-dependent ownership costs. |
| inputs / outputs | The source note points to legacy deep-row copy and native shared immutable ownership in the following constructor. |
| invariants | This does not change copying semantics or promise constant cost for legacy values. |
| ownership | Documentation only; concrete payload ownership remains in the following implementation. |
| failure | No new admission, catch or recovery behavior. |
| cost | No runtime work; existing copy/last-owner costs remain explicit. |
| Design | [docs/storage.md](../../../../storage.md), [src/storage/tuple_payload.hpp](../../../../../src/storage/tuple_payload.hpp) |

## B0027

[Lines 130–133](../../../../../src/storage/layout.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple::Tuple(const Tuple& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the tuple according to its explicit legacy or native payload representation. |
| inputs / outputs | Source tuple in; copies the layout handle, deep-copies an ordinary legacy Row, or shares an immutable native payload. |
| invariants | Native copy does not export scalar values; legacy copies own independent row/string bytes while retaining the same layout token. |
| ownership | Legacy creates a new standard shared payload; native merely adds shared ownership. An empty moved-from payload remains empty in the copy. |
| failure | Legacy deep/shared allocation may throw during construction, leaving the source unchanged; no partial tuple is returned. |
| cost | O(F+variable bytes) legacy value copy/allocation versus O(1) native handle copy; final release remains representation/last-owner dependent. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0028

[Lines 134–148](../../../../../src/storage/layout.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple Tuple::from_accounted(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a complete native tuple into public shared owning output without exporting scalars. |
| inputs / outputs | Move-only AccountedTuple becomes Tuple with the same funded immutable layout token and an accounted shared NativeTuplePayload. |
| invariants | Constructor only moves an already admitted row and copies account handles; before/after account delta therefore measures the exact shared-owner allocation(s). |
| ownership | Shared payload owns the transferred native tuple and original account until final release; native Tuple copies share that immutable payload. |
| failure | Shared-owner allocation failure destroys the transferred local row safely and publishes no Tuple. |
| cost | No scalar/deep-byte recopy here; actual shared owner/control allocation plus fixed accounting differences, no allocation-ledger scan. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0029

[Lines 149–149](../../../../../src/storage/layout.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Tuple::is_accounted() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify whether this payload retains a native memory account. |
| inputs / outputs | Returns payload presence combined with account-handle presence. |
| invariants | False for legacy and moved-from tuples; this is representation classification, not a complete memory-footprint query. |
| ownership | Reads existing owners only. |
| failure | Noexcept and nonallocating. |
| cost | Constant handle-presence work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0030

[Lines 150–150](../../../../../src/storage/layout.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage Tuple::memory_usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the payload-local stored accounted usage record. |
| inputs / outputs | Returns cached payload usage, or zero for an empty payload. |
| invariants | Legacy payloads report zero here despite ordinary heap ownership; this excludes other shared layout/query allocations and is not total retained memory. |
| ownership | Returns fixed counters without scanning or retaining an owner. |
| failure | Noexcept; absence is represented by zero counters. |
| cost | Constant counter copy, no ledger scan or allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 151–154](../../../../../src/storage/layout.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics Tuple::account_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the original account statistics for a native public tuple. |
| inputs / outputs | Requires is_accounted(); returns that account aggregate statistics. |
| invariants | The result describes the shared account, not only this tuple or a new allowance. |
| ownership | Reads retained account counters; the tuple keeps the original account alive. |
| failure | Legacy/empty payload rejects with MemoryFailure(contract), without allocating an owning diagnostic string. |
| cost | Constant account-counter snapshot; no attribution/ledger scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0032

[Lines 155–161](../../../../../src/storage/layout.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple& Tuple::operator=(const Tuple& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace tuple ownership with a strong copy-assignment guarantee. |
| inputs / outputs | On non-self assignment, construct a complete temporary copy, then swap layout/payload owners; returns this. |
| invariants | A failing legacy deep copy leaves the destination unchanged. The published layout/payload pair changes together through nonthrowing owner swaps. |
| ownership | Temporary copy acquires the new owners; its destruction releases the old owners after the swap. |
| failure | Only preparation can throw under valid owner contracts; self-assignment performs no copy. |
| cost | Representation-specific copy cost plus old-value/descriptor teardown; native copying is constant but final old-owner release need not be. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0033

[Lines 162–167](../../../../../src/storage/layout.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple& Tuple::operator=(Tuple&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move the complete layout/payload pair while preserving self-move safety. |
| inputs / outputs | For distinct objects, move both owners and return this; self-move does nothing. |
| invariants | The source becomes moved-from and the destination retains the paired immutable owners; no value admission is repeated. |
| ownership | Transfers ownership and releases the destination prior backing. |
| failure | Noexcept; private owner destructors/moves must not throw. |
| cost | Constant transfer plus possible last-owner row/layout/account teardown; no new allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0035

[Lines 169–187](../../../../../src/storage/layout.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection::Projection(TupleLayout source,TupleLayout target,std::vector<FieldId> fields)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile an immutable ordered projection only after proving its type/equality obligations. |
| inputs / outputs | Source/target handles and numeric source positions in; checks equal context, target arity, source ranges, exact domain inclusion and compatible variable identities. |
| invariants | Repeated target variables require the same source slot or already equal source variables. This never admits a scalar conversion, decimal narrowing or name lookup at application time. |
| ownership | Retains both tokens and moves the field vector into a fresh standard Data; a transient map tracks first target-variable assignments. |
| failure | Any invalid mapping rejects with invalid_projection before data_ assignment; temporary/shared allocations can fail without publishing a projection. |
| cost | O(K log K) worst-case variable-map preparation plus actual context-byte comparison and O(K) retained fields. Public context equality is not a same-account assertion. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0036

[Lines 188–188](../../../../../src/storage/layout.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& Projection::source() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact source layout handle from a live compiled projection. |
| inputs / outputs | Returns the stored source after checking Data presence. |
| invariants | Does not construct or rebind a layout; keep the projection or another token owner alive while using the borrowed reference. |
| ownership | No new shared owner is acquired by returning this reference. |
| failure | Moved-from projection throws invalid_projection. |
| cost | Constant checked getter, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0037

[Lines 189–189](../../../../../src/storage/layout.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& Projection::target() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact target layout handle from a live compiled projection. |
| inputs / outputs | Uses source() as presence validation and returns stored target. |
| invariants | Target token determines output/key interoperability independently of equal descriptors. |
| ownership | Returned reference borrows projection Data and retains no extra owner. |
| failure | Moved-from projection rejects through source(). |
| cost | Constant checked getter, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0038

[Lines 190–190](../../../../../src/storage/layout.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::span<const FieldId>& Projection::fields() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the precompiled ordered source-field range. |
| inputs / outputs | Returns field_view after source() presence validation. |
| invariants | Indices/order/repetition were checked during construction; this getter does no row validation or name resolution. |
| ownership | Span reference and numeric backing require a surviving projection Data owner. |
| failure | Moved-from projection rejects through source(). |
| cost | Constant access independent of field count. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0039

[Lines 191–191](../../../../../src/storage/layout.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Projection::same_token(const Projection& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the immutable projection-program token itself. |
| inputs / outputs | True only when this nonempty Data is the same shared Data as other. |
| invariants | Equal source/target/field descriptors constructed independently do not share a program token; empty handles compare false. |
| ownership | Reads existing pointers without retaining or copying field storage. |
| failure | Noexcept and nonallocating. |
| cost | Constant pointer checks. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0040

[Lines 192–192](../../../../../src/storage/layout.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Projection::same_token(const AccountedProjection& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public and accounted handles for one compiled projection token. |
| inputs / outputs | Rejects empty accounted handle as false; otherwise compares its sharing descriptor facade. |
| invariants | Readable native descriptors preserve the concrete token/control block, not a reconstructed field-vector mirror. |
| ownership | Temporary descriptor increments/decrements existing ownership; no separate control/field array is allocated. |
| failure | Noexcept under valid nonempty native owner; emptiness is a false result. |
| cost | Constant handle/refcount work, independent of projection arity. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0041

[Lines 193–199](../../../../../src/storage/layout.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple Projection::apply(const Tuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather selected fields into a tuple carrying the target token after checking source identity. |
| inputs / outputs | An input tuple with source().same_token(layout) in; an owning projected tuple out, preserving field order/repetition. |
| invariants | Token mismatch rejects before gathering. Native-backed programs dispatch to their factory; standalone programs export selected exact scalar values then validate the target tuple. |
| ownership | Native factory retains/funds its prescribed account. Standalone gathering owns a temporary Row and copies variable payload; target may itself construct native backing. |
| failure | Layout mismatch, target/native validation or allocation failure returns no result and does not mutate input/program. |
| cost | O(K+selected variable bytes) gathering plus target/public-native validation, payload and owner allocations; no field-name lookup and no blanket constant-time claim. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0042

[Lines 200–209](../../../../../src/storage/layout.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout table_layout(LayoutId id,const Catalog& schema,TableId table,std::string binding)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a classical full physical-table layout from an admitted catalog. |
| inputs / outputs | Catalog/table ID/query binding in; copies ordered field kinds/decimal domains and attaches catalog/source origin versions. |
| invariants | Validates the complete catalog and source bounds; every source column must declare non-nullness, including unused columns. SQL NULL handling stays outside this core. |
| ownership | New standalone layout owns selected fields/context; borrows catalog only during compilation. |
| failure | Catalog validation, out-of-range source, nullable columns or construction/allocation failures reject before returning a layout. |
| cost | Whole-catalog validation plus O(table arity) field gathering and layout compilation; not just a constant table lookup. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0043

[Lines 210–217](../../../../../src/storage/layout.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout scope_layout(LayoutId id,const Query& query,std::span<const VariableId> variables,LayoutContext context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a logical ordered variable scope into a fresh classical layout. |
| inputs / outputs | Query variable declarations, ordered/repeated VariableIds and context in; fields retain each type and variable ID. |
| invariants | Checks variable ranges and lets TupleLayout validate type/context/repetition. It does not prove the query graph, source admission or physical decimal typmods. |
| ownership | Copies selected scalar/variable descriptors into new standalone backing; caller query/span can expire afterward. |
| failure | Bad variable ID, invalid layout type/context or allocation failure rejects before returning the layout. |
| cost | O(K) gathering plus layout repeated-variable compilation; no name lookup on later tuple/projection operations. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0044

[Lines 218–225](../../../../../src/storage/layout.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout projected_layout(LayoutId id,const TupleLayout& source,std::span<const FieldId> fields)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fresh key/output descriptor by selecting exact source field metadata. |
| inputs / outputs | Source layout, ordered numeric positions and a new ID in; selected Fields plus copied source context out. |
| invariants | Preserves type/decimal/variable metadata and repetition. It creates a new token and omits physical origin for the derived layout; it does not compile a Projection program itself. |
| ownership | Owns copied field vector and binding text; returned descriptor has no borrowed dependency on source lifetime. |
| failure | Out-of-range fields, moved-from source, invalid construction or allocations reject before returning the result. |
| cost | O(K+binding bytes) gathering/copy plus layout compilation; no value projection or tuple allocation here. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [Refactor.md §11.4 S01–S03](../../../../../Refactor.md) |

## B0045

[Lines 226–226](../../../../../src/storage/layout.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L226:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/layout.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
