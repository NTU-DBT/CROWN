# `include/crown/storage/layout.hpp` — block usage map

[Source](../../../../../../include/crown/storage/layout.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `0b268fc7056719b8299bbc9fc2ee20aaf4b47b47836ffa09b06ef0e76cc601ca`. 118 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/storage/layout.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../../include/crown/storage/layout.hpp#L12) | Type/record definition: struct Field |  · [reviewed contract](#b0002) |
| [B0003 · 18–22](../../../../../../include/crown/storage/layout.hpp#L18) | Type/record definition: struct LayoutContext | source comment (unverified): // Optional owning query/schema binding, never a field name. · [reviewed contract](#b0003) |
| [B0004 · 23–27](../../../../../../include/crown/storage/layout.hpp#L23) | Type/record definition: struct LayoutContextView |  · [reviewed contract](#b0004) |
| [B0005 · 28–30](../../../../../../include/crown/storage/layout.hpp#L28) | Callable definition: \[\[nodiscard\]\] inline bool operator==(LayoutContextView view,const LayoutContext& owner) noexcept | returns view.catalog_version==owner.catalog_version && view.binding==owner.binding · [reviewed contract](#b0005) |
| [B0006 · 31–35](../../../../../../include/crown/storage/layout.hpp#L31) | Type/record definition: struct LayoutOrigin |  · [reviewed contract](#b0006) |
| [B0007 · 36–60](../../../../../../include/crown/storage/layout.hpp#L36) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Copies share an immutable runtime token. Deserialized/equal descriptors do · [reviewed contract](#b0007) |
| [B0008 · 61–62](../../../../../../include/crown/storage/layout.hpp#L61) | Callable definition: template&lt;class Values&gt; requires std::is_same_v&lt;std::remove_cvref_t&lt;Values&gt;,TupleValuesView&gt; void validate(Values&& values) const | calls validate_view · [reviewed contract](#b0008) |
| [B0009 · 63–64](../../../../../../include/crown/storage/layout.hpp#L63) | declares types or opens a type body. |  · [reviewed contract](#b0009) |
| [B0010 · 65–65](../../../../../../include/crown/storage/layout.hpp#L65) | Callable definition: explicit TupleLayout(std::shared_ptr&lt;const detail::LayoutDescriptor&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 66–70](../../../../../../include/crown/storage/layout.hpp#L66) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Legacy payload copies own deep Row/string copies; native payload copies · [reviewed contract](#b0011) |
| [B0012 · 71–93](../../../../../../include/crown/storage/layout.hpp#L71) | Type/record definition: class Tuple | returns layout_; TupleValuesView(payload_); source comment (unverified): // Legacy payload copies own deep Row/string copies; native payload copies · [reviewed contract](#b0012) |
| [B0013 · 94–95](../../../../../../include/crown/storage/layout.hpp#L94) | Callable definition: template&lt;class Values&gt; requires std::is_same_v&lt;std::remove_cvref_t&lt;Values&gt;,TupleValuesView&gt; Tuple TupleLayout::tuple(Values&& val… | calls tuple_view; returns tuple_view(std::forward&lt;Values&gt;(values)) · [reviewed contract](#b0013) |
| [B0014 · 96–114](../../../../../../include/crown/storage/layout.hpp#L96) | Type/record definition: class Projection | source comment (unverified): // Checks the input token before gathering selected fields. Native-backed · [reviewed contract](#b0014) |
| [B0015 · 115–118](../../../../../../include/crown/storage/layout.hpp#L115) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0015) |

## B0001

[Lines 1–11](../../../../../../include/crown/storage/layout.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:f6bad7360c2494441d664864cd51c7f660c0351abd38dd653872a94aa519bbd7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/layout.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/model.hpp"\`, \`"crown/storage/tuple_values.hpp"\`, \`&lt;memory&gt;\`, \`&lt;span&gt;\`, \`&lt;string_view&gt;\`, \`&lt;utility&gt;\`, \`&lt;type_traits&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 12–17](../../../../../../include/crown/storage/layout.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Field {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one ordered typed field and optional logical identity/domain. |
| inputs / outputs | Field stores ScalarType, optional exact DecimalSpec, and optional VariableId; default comparison includes all three. |
| invariants | The record itself accepts arbitrary values; TupleLayout/AccountedLayout constructors check legal decimal domains and repeated-variable consistency. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 18–22](../../../../../../include/crown/storage/layout.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LayoutContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own catalog/query binding bytes used in a layout context. |
| inputs / outputs | LayoutContext stores positive-by-default catalog_version and optional owning binary binding string. |
| invariants | Binding is a query/schema identity, never a field name; positive versions are enforced by layout construction, not this aggregate. |
| ownership | std::string owns its bytes; copying this context may allocate independently of native account storage. |
| failure | String construction/copy may throw; comparisons do not validate or mint a layout token. |
| cost | Copy/construction and comparison depend on binding byte length; move generally transfers the existing string representation. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 23–27](../../../../../../include/crown/storage/layout.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LayoutContextView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow catalog/query binding bytes without an owning context copy. |
| inputs / outputs | LayoutContextView carries catalog_version and string_view binding. |
| invariants | Equal bytes/version do not imply shared immutable layout token or account identity. |
| ownership | The binding owner must outlive all uses of the view; copying the view retains no bytes. |
| failure | Value construction/copy does not validate the version or buffer lifetime. |
| cost | Fixed-size view copy; equality/order may compare all binding bytes through the first difference. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 28–30](../../../../../../include/crown/storage/layout.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline bool operator==(LayoutContextView view,const LayoutContext& owner) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a borrowed layout context against an owning context. |
| inputs / outputs | Returns version equality and exact string_view/string binding byte equality. |
| invariants | Both contexts must have stable live backing; it does not compare layout fields or immutable tokens. |
| ownership | Reads existing contexts and retains no owner. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed version comparison then up to the binding byte length; no dynamic string or allocation. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 31–35](../../../../../../include/crown/storage/layout.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LayoutOrigin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record physical table and source-schema provenance for a layout. |
| inputs / outputs | Carries TableId and source_schema_version with default comparison. |
| invariants | Layout construction rejects zero source version; this plain aggregate is descriptive rather than admission authority. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 36–60](../../../../../../include/crown/storage/layout.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TupleLayout {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own or share a checked immutable ordered layout token. |
| inputs / outputs | The public constructor accepts fields, catalog/binding context and optional table origin; accessors borrow immutable descriptor ranges and same_token/same_descriptor distinguish identity from equal values. |
| invariants | Positive context/source versions, legal scalar/decimal domains and repeated-variable type consistency are established before publication. Serialization/equal contents do not acquire another token. |
| ownership | Standalone construction owns vector/string/equality metadata and shared control; an accounted descriptor handle instead shares funded native Data through the same immutable interface. Returned references/ranges need a surviving descriptor owner. |
| failure | Invalid layout, moved-from descriptor and ordinary allocation failures propagate. The constructor does not install a native memory account automatically. |
| cost | Admission visits fields and binary binding and uses a variable map; same_token is fixed, descriptor comparison visits fields/binding. Shared-handle copy does not clone metadata; later tuple creation has explicit validation/payload costs. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Tuple tuple(const Row& values) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owning public tuple after exact descriptor validation. |
| inputs / outputs | tuple(const Row&) copies caller values; tuple(Row&&) can move a standalone Row; tuple_view adapts a retaining/borrowed public values representation. |
| invariants | No scalar conversion/rounding occurs. Public native-backed descriptors currently run public validation and the native factory validation; direct AccountedLayout has its separate native boundary. |
| ownership | Standalone output owns a Row and ordinary shared payload; native-backed output owns a funded AccountedTuple and funded shared payload under its retained original account. Caller bytes are not retained as borrows. |
| failure | Invalid arity/type/decimal/equality, account or allocator failures propagate; input ownership remains governed by copy versus explicit rvalue move. |
| cost | Validation visits fields/compiled equalities including deep comparisons. Standalone const input copies rows/strings, standalone rvalue transfers its admitted Row, and native factories size/copy compact payload plus allocate output ownership. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 61–62](../../../../../../include/crown/storage/layout.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
  void validate(Values&& values) const {validate_view(std::forward<Values>(values));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward an exact public-values view through descriptor validation. |
| inputs / outputs | Constrained validate(Values&&) accepts TupleValuesView and invokes validate_view. |
| invariants | The wrapper creates no temporary owning Row or new immutable token. |
| ownership | The argument view is used synchronously; it retains payload only if it was tuple-derived. |
| failure | Legacy validation Error or view/descriptor failure propagates; no catch, fallback or retry. |
| cost | Fixed forwarding plus full field/domain/compiled-equality validation, including actual scalar/string comparison work. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 63–64](../../../../../../include/crown/storage/layout.hpp#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend class AccountedLayout;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow AccountedLayout to construct a TupleLayout view over its frozen descriptor. |
| inputs / outputs | Compile-time access is granted to TupleLayout's private shared-descriptor constructor. |
| invariants | This access does not copy or rewrite layout data; descriptor() passes the same token. |
| ownership | AccountedLayout and the resulting TupleLayout share immutable descriptor ownership. |
| failure | The friend declaration itself has no runtime failure path. |
| cost | Compile-time access only; wrapping an existing descriptor does not create a separate layout payload. |
| Design | [include/crown/storage/layout.hpp §TupleLayout](../../../../../../include/crown/storage/layout.hpp), [src/storage/accounted_layout.cpp §AccountedLayout::descriptor](../../../../../../src/storage/accounted_layout.cpp), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |

## B0010

[Lines 65–65](../../../../../../include/crown/storage/layout.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit TupleLayout(std::shared_ptr<const detail::LayoutDescriptor> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an existing native or standalone immutable descriptor handle. |
| inputs / outputs | Private constructor moves shared_ptr&lt;const LayoutDescriptor&gt; into a public TupleLayout. |
| invariants | It preserves the same descriptor/token and factory callbacks; it is not deserialization or new validation. |
| ownership | The shared descriptor retains its actual ordinary or account-funded backing owner; no field/binding copy occurs. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 66–70](../../../../../../include/crown/storage/layout.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const detail::LayoutDescriptor> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable type-erased descriptor and identity token for TupleLayout. |
| inputs / outputs | Construction supplies a descriptor; getters expose its fields/context/origin through borrowed views. |
| invariants | same_token uses shared descriptor identity; same_descriptor compares values separately. |
| ownership | Copies share the descriptor; AccountedLayout::descriptor wraps the same descriptor owner. |
| failure | An empty/moved-from layout is rejected by id()/view accessors. |
| cost | The member declaration does nothing; copies share ownership and last release destroys descriptor storage. |
| Design | [src/storage/layout.cpp §TupleLayout::Data and same_token](../../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp §AccountedLayout::descriptor](../../../../../../src/storage/accounted_layout.cpp), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |

## B0012

[Lines 71–93](../../../../../../include/crown/storage/layout.hpp#L71); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Tuple {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an immutable public tuple whose payload representation controls copy cost. |
| inputs / outputs | Tuple keeps its TupleLayout and immutable TuplePayload; values() returns a retaining TupleValuesView, while layout() returns a reference. |
| invariants | Tuple equality requires the same token before value comparison. Standalone tuple copies deep-copy Row/string values; native tuple copies share funded immutable payload. |
| ownership | Legacy payload owns a standard Row/control; native payload owns AccountedTuple and its funded output owner. from_accounted moves row ownership and allocates its real shared owner under the original account. |
| failure | Legacy copy and from_accounted may fail allocation; copy assignment constructs a complete replacement before swapping. Moves are noexcept; empty/account-mismatch diagnostics stay with their specific accessors. |
| cost | Legacy copy is O(fields + deep bytes) with ordinary allocation; native copy is shared-handle work. Hash/equality visit actual scalar/deep bytes; final release destroys the retained payload rather than being universally O(1). |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 94–95](../../../../../../include/crown/storage/layout.hpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
Tuple TupleLayout::tuple(Values&& values) const{return tuple_view(std::forward<Values>(values));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a public owning tuple from an explicit values view. |
| inputs / outputs | The constrained overload forwards TupleValuesView to tuple_view. |
| invariants | Owning output is explicit; no implicit Row conversion or token rebinding is introduced. |
| ownership | tuple_view owns the returned payload: standalone descriptors export a Row; native descriptors use their retained original-account factory. |
| failure | Full validation and output allocation failures propagate; the input view remains owned/borrowed according to its existing representation. |
| cost | Validation scans fields/equalities. Standalone export copies deep values; native public factories currently validate again and allocate native row/output owner, so this is not a free view conversion. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 96–114](../../../../../../include/crown/storage/layout.hpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Projection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a compiled field selection between explicit immutable layout tokens. |
| inputs / outputs | Projection constructs from source, target and ordered FieldIds, exposing retained source/target/fields and apply(tuple). |
| invariants | Construction checks context, arity, bounds, scalar/domain inclusion, variable identity and justified target equalities. Apply checks exact source token; descriptor equality alone is insufficient. |
| ownership | The shared descriptor owns ordinary field-vector storage or shares an accounted field block, plus source/target layout handles. Returned spans/references borrow this descriptor. |
| failure | Invalid construction/input token or allocation failures propagate. Native descriptor public adapters translate fixed validation failures into public Error diagnostics; no rollback mechanism is introduced here. |
| cost | Admission uses field checks and a repeated-variable map. Apply copies selected scalar/string bytes; standalone output validates target, native public output validates source and funds row/output owner. Token access is fixed, apply is not. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 115–118](../../../../../../include/crown/storage/layout.hpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] TupleLayout table_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build explicit standalone descriptors for tables, variable scopes or projections. |
| inputs / outputs | table_layout validates the Catalog/table and rejects nullable classical columns; scope_layout selects numeric Query VariableIds; projected_layout copies selected source fields and binary context. |
| invariants | Each constructor returns a fresh token. Source-variable/table/field positions must exist; projected_layout does not preserve physical table origin implicitly. |
| ownership | Owns ordinary selected-field/context metadata via TupleLayout; input catalog/query/spans are borrowed for construction and not retained. |
| failure | Invalid catalog/layout/projection/nullability and allocation failures propagate; no schema coercion or fallback descriptor. |
| cost | Table construction includes full catalog validation plus selected columns; scope/projected construction visits selected fields and copies binding bytes, then runs TupleLayout admission/map work. |
| Design | [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |
