# `src/storage/accounted_projection.cpp` — block usage map

[Source](../../../../../src/storage/accounted_projection.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `8e512ec85c15ff01d43f3c7731cf29ec3b9aff66800585827824eb083b683392`. 131 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/storage/accounted_projection.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../src/storage/accounted_projection.cpp#L13) | Callable definition: void require(bool value, ProjectionProblem problem) | calls ProjectionValidationFailure; guard void require(bool value, ProjectionProblem problem) { · [reviewed contract](#b0002) |
| [B0003 · 16–21](../../../../../src/storage/accounted_projection.cpp#L16) | Callable definition: bool fits_domain(const Field& source, const Field& target) noexcept | calls ; returns false; true · [reviewed contract](#b0003) |
| [B0004 · 22–24](../../../../../src/storage/accounted_projection.cpp#L22) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_copy_constructible_v&lt;FieldId&gt; && std::is_trivially_destructible_v&lt;Fie…; source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 25–40](../../../../../src/storage/accounted_projection.cpp#L25) | Type/record definition: struct AccountedProjection::Data:detail::ProjectionDescriptor | returns {static_cast&lt;const FieldId*&gt;(storage.data()), size} · [reviewed contract](#b0005) |
| [B0006 · 41–41](../../../../../src/storage/accounted_projection.cpp#L41) | Explanatory comments or spacing. |  |
| [B0007 · 42–44](../../../../../src/storage/accounted_projection.cpp#L42) | Callable definition: std::string_view ProjectionValidationFailure::code() const noexcept | calls ; returns issue_ == ProjectionProblem::layout_mismatch ? @ : @ · [reviewed contract](#b0007) |
| [B0008 · 45–58](../../../../../src/storage/accounted_projection.cpp#L45) | Callable definition: const char* ProjectionValidationFailure::what() const noexcept | calls ; returns @; @ · [reviewed contract](#b0008) |
| [B0009 · 59–59](../../../../../src/storage/accounted_projection.cpp#L59) | Explanatory comments or spacing. |  |
| [B0010 · 60–95](../../../../../src/storage/accounted_projection.cpp#L60) | Callable definition: AccountedProjection AccountedProjection::freeze(const AccountedLayout& source, const AccountedLayout& target, std::span&lt;const Fie… | calls require, bool, query_account, statistics; guard require(bool(source) && bool(target), ProjectionProblem::invalid_layout);; returns AccountedProjection(std::move(data)); growth allocate, emplace, make_accounted_shared; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 96–99](../../../../../src/storage/accounted_projection.cpp#L96) | Callable definition: const AccountedProjection::Data& AccountedProjection::required() const | calls ProjectionValidationFailure; returns *data_ · [reviewed contract](#b0011) |
| [B0012 · 100–100](../../../../../src/storage/accounted_projection.cpp#L100) | Callable definition: const AccountedLayout& AccountedProjection::source() const & | calls required; returns required().source · [reviewed contract](#b0012) |
| [B0013 · 101–101](../../../../../src/storage/accounted_projection.cpp#L101) | Callable definition: const AccountedLayout& AccountedProjection::target() const & | calls required; returns required().target · [reviewed contract](#b0013) |
| [B0014 · 102–102](../../../../../src/storage/accounted_projection.cpp#L102) | Callable definition: std::span&lt;const FieldId&gt; AccountedProjection::fields() const & | calls required, fields; returns required().fields() · [reviewed contract](#b0014) |
| [B0015 · 103–107](../../../../../src/storage/accounted_projection.cpp#L103) | Callable definition: AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple) const | calls required, require, same_token, layout; guard require(data.source.same_token(tuple.layout()), ProjectionProblem::layout_mismatch);; returns apply(tuple, tuple.attribution()) · [reviewed contract](#b0015) |
| [B0016 · 108–114](../../../../../src/storage/accounted_projection.cpp#L108) | Callable definition: AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple, resource::MemoryAttribution attribution) const | calls required, require, same_token, layout; guard require(data.source.same_token(tuple.layout()), ProjectionProblem::layout_mismatch);; returns AccountedTuple(data.target, AccountedRow::project(data.account, tuple.values(), data.fields(), attr…; source comment (unverified): // Construction already proved the target domains/equalities. No metadata · [reviewed contract](#b0016) |
| [B0017 · 115–115](../../../../../src/storage/accounted_projection.cpp#L115) | Callable definition: Projection AccountedProjection::descriptor() const | calls required, Projection; returns Projection(data_) · [reviewed contract](#b0017) |
| [B0018 · 116–121](../../../../../src/storage/accounted_projection.cpp#L116) | Callable definition: AccountedTuple AccountedProjection::apply(RowView values,resource::MemoryAttribution attribution) const | calls required, validation_issue, ok, TupleValidationFailure; returns AccountedTuple(data.target,AccountedRow::project(data.account,values,data.fields(),attribution)) · [reviewed contract](#b0018) |
| [B0019 · 122–129](../../../../../src/storage/accounted_projection.cpp#L122) | Callable definition: Tuple AccountedProjection::make_public_tuple(const Projection& descriptor,const Tuple& tuple) | calls AccountedProjection, values, native_view, Error; returns Tuple::from_accounted(projection.apply(*native,{resource::MemoryOwnerKind::output,0})) · [reviewed contract](#b0019) |
| [B0020 · 130–131](../../../../../src/storage/accounted_projection.cpp#L130) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0020) |

## B0001

[Lines 1–12](../../../../../src/storage/accounted_projection.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:98063bcd1ef272781e4c92360d00cf78d4945d75520145566deae04713064812
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_projection.cpp: imports \`"crown/storage/accounted_projection.hpp"\`, \`"descriptor.hpp"\`, \`"crown/resource/ownership.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;limits&gt;\`, \`&lt;map&gt;\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\` for compilation; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 13–15](../../../../../src/storage/accounted_projection.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value, ProjectionProblem problem)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the exact fixed native projection issue only on a failed predicate. |
| inputs / outputs | True returns; false throws ProjectionValidationFailure(problem). |
| invariants | No message formatting or allocation is performed by successful checks. |
| ownership | Inline predicate/enum; thrown failure holds no owned string. |
| failure | Fixed native failure on rejection. |
| cost | O(1) success. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 16–21](../../../../../src/storage/accounted_projection.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits_domain(const Field& source, const Field& target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove exact source-domain inclusion before projection admission. |
| inputs / outputs | Matching scalar kinds and optional valid decimal specs return whether target accepts every source value. |
| invariants | Admitted specs satisfy1&lt;=precision&lt;=38 and scale&lt;=precision, so integer-digit subtraction is safe. No narrowing/coercion/rounding. |
| ownership | Borrowed immutable Field metadata. |
| failure | Noexcept under admitted layout specs. |
| cost | Fixed scalar comparisons. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0004

[Lines 22–24](../../../../../src/storage/accounted_projection.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:04d2bee39e7b7d782751efe83a8bcf8cf5b1d3f2217caa315fd319effe8bcc0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_projection.cpp: closes \`anonymous namespace\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 25–40](../../../../../src/storage/accounted_projection.cpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedProjection::Data:detail::ProjectionDescriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the admitted numeric mapping and source/target layout tokens. |
| inputs / outputs | Account, layouts and funded FieldId block initialize public descriptor views/callback. |
| invariants | Each FieldId was validated before publication; Data is immutable and source/target share one account/context. |
| ownership | Same query account funds numeric block/shared owner; layouts share existing funded metadata. |
| failure | Noexcept adoption after funding; no unaccounted Projection/Row mirror. |
| cost | Fixed owner/span setup plus retained O(target arity) field block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0007

[Lines 42–44](../../../../../src/storage/accounted_projection.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view ProjectionValidationFailure::code()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map projection token mismatch separately from admission errors. |
| inputs / outputs | layout_mismatch returns that code; all other projection problems return invalid_projection. |
| invariants | Stable public code categories are separate from native enum detail. |
| ownership | Returns static string_view, owns inline enum only. |
| failure | Noexcept. |
| cost | O(1), no diagnostic string allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0008

[Lines 45–58](../../../../../src/storage/accounted_projection.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* ProjectionValidationFailure::what()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present native projection issue text from static literals. |
| inputs / outputs | Issue enum selects invalid-layout/account/context/arity/field/domain/identity/equality/token wording. |
| invariants | No dynamically formatted user metadata is inserted during native unwinding. |
| ownership | Static literal lifetime. |
| failure | Noexcept, including fallback status. |
| cost | Fixed switch, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0010

[Lines 60–95](../../../../../src/storage/accounted_projection.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedProjection AccountedProjection::freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove and retain one exact immutable source-to-target field mapping. |
| inputs / outputs | Same-account/context frozen layouts and ordered FieldId span produce an owning native projection. |
| invariants | Check valid layouts, target arity, field bounds, domain inclusion and variable identity. Repeated target variables require same input field or already-equal source-variable fields. |
| ownership | Accounted scratch map proves repeated identities; original account retains FieldId block/Data and shared layout tokens. |
| failure | Fixed ProjectionValidationFailure or memory failure releases scratch/partial storage and publishes no projection. |
| cost | O(target arity log distinct bound variables + context-binding comparison), then field-block copy/allocation and actual shared owner/control funding, including zero-field framing. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0011

[Lines 96–99](../../../../../src/storage/accounted_projection.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedProjection::Data& AccountedProjection::required()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty projection handles before borrowing its admitted mapping. |
| inputs / outputs | Valid handle returns const Data. |
| invariants | Default/moved projection is not an executable mapping. |
| ownership | Borrowed Data reference; no new owner/control. |
| failure | Empty handle throws ProjectionValidationFailure(invalid_layout). |
| cost | O(1), no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0012

[Lines 100–100](../../../../../src/storage/accounted_projection.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedProjection::source()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact required input layout token. |
| inputs / outputs | Returns Data source by const reference. |
| invariants | rvalue access is deleted; reference/span must not outlive the retaining projection. |
| ownership | Existing shared Data owns layouts/block; accessor retains no new owner. |
| failure | Empty handle fails through required(). |
| cost | O(1), no copy/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0013

[Lines 101–101](../../../../../src/storage/accounted_projection.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedProjection::target()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the declared output layout token. |
| inputs / outputs | Returns Data target by const reference. |
| invariants | rvalue access is deleted; reference/span must not outlive the retaining projection. |
| ownership | Existing shared Data owns layouts/block; accessor retains no new owner. |
| failure | Empty handle fails through required(). |
| cost | O(1), no copy/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0014

[Lines 102–102](../../../../../src/storage/accounted_projection.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const FieldId> AccountedProjection::fields()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the ordered numeric field selection. |
| inputs / outputs | Returns immutable FieldId span including repetitions/empty selections. |
| invariants | rvalue access is deleted; reference/span must not outlive the retaining projection. |
| ownership | Existing shared Data owns layouts/block; accessor retains no new owner. |
| failure | Empty handle fails through required(). |
| cost | O(1), no copy/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0015

[Lines 103–107](../../../../../src/storage/accounted_projection.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project a validated native tuple while preserving its attribution. |
| inputs / outputs | Require matching source token, read row attribution, delegate to attributed apply. |
| invariants | Current wrapper repeats required/token checking in the delegated overload; initial validation preserves error order before block-dependent tuple.attribution(). |
| ownership | Output owns selected deep bytes in the projection account and retains target layout. |
| failure | Invalid projection/token is rejected before reading a possibly moved tuple block; funding errors publish no result. |
| cost | Two constant token/presence checks plus actual numeric gather/range/preflight/copy; no full source-domain revalidation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0016

[Lines 108–114](../../../../../src/storage/accounted_projection.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather native tuple output with explicit receiving-row attribution. |
| inputs / outputs | Exact source token and admitted FieldId mapping produce owning target AccountedTuple. |
| invariants | Source tuple was validated at construction and frozen mapping proves target domains/equalities. AccountedRow::project still checks numeric field ranges before copy. |
| ownership | Copies selected descriptors/deep strings in projection original account, no temporary Row/vector. |
| failure | Empty projection or token mismatch raises fixed projection failure; row funding failure publishes no tuple. |
| cost | Constant token check plus O(selected fields) range/preflight passes and actual string bytes; no full source schema scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0017

[Lines 115–115](../../../../../src/storage/accounted_projection.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection AccountedProjection::descriptor()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a public descriptor sharing the admitted native mapping. |
| inputs / outputs | Valid native handle returns Projection with same Data/control/callback. |
| invariants | No legacy FieldId vector or independent token is created. |
| ownership | Shared ownership retains mapping/source/target metadata. |
| failure | Empty handle fails through required(). |
| cost | O(1) shared-owner copy, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0018

[Lines 116–121](../../../../../src/storage/accounted_projection.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple AccountedProjection::apply(RowView values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate an external compact source row before projecting it. |
| inputs / outputs | Untyped borrowed cells and output attribution return exact target tuple. |
| invariants | No source tuple token is available, so validate all source fields/domains/repeated equalities before using the proven mapping. |
| ownership | Borrows source only during validation/copy; result owns selected native bytes. |
| failure | Source issues raise TupleValidationFailure; projection presence/memory failures retain their native types. |
| cost | Full source validation plus selected-field range/preflight/copy and deep bytes, unlike the prevalidated AccountedTuple overload. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0019

[Lines 122–129](../../../../../src/storage/accounted_projection.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple AccountedProjection::make_public_tuple(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a native-backed public projection and present native validation failures. |
| inputs / outputs | Public descriptor plus immutable Tuple require native payload, validate its RowView and return owning public native output. |
| invariants | Public Projection::apply already checked source token; this callback still calls external RowView overload, so source fields/equalities are revalidated. |
| ownership | Output tuple owns funded AccountedTuple payload/shared wrapper in original account; input values view retains source during use. |
| failure | Missing native payload raises storage_contract. Projection/TupleValidationFailure are translated to Error; memory failures pass through unchanged. |
| cost | Full source scan plus selected gather/deep copy and public owner allocation; not merely an O(1) token check followed by raw slots. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/scalars.md](../../../../scalars.md) |

## B0020

[Lines 130–131](../../../../../src/storage/accounted_projection.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L131:sha256:7089e9cc52c39a53c28433397476fe0fa1e71e49e678f867277ec88cc7e152ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_projection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
