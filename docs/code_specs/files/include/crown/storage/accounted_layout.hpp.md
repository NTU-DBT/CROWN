# `include/crown/storage/accounted_layout.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_layout.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `d9e030c149078ebbb41d404c0b124f0219e121f88e1f83ae40f4fe97e982ec7a`. 151 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/storage/accounted_layout.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/storage/accounted_layout.hpp#L16) | Type/record definition: enum class TupleProblem |  · [reviewed contract](#b0002) |
| [B0003 · 17–21](../../../../../../include/crown/storage/accounted_layout.hpp#L17) | Type/record definition: struct TupleValidationIssue | returns problem == TupleProblem::none · [reviewed contract](#b0003) |
| [B0004 · 22–23](../../../../../../include/crown/storage/accounted_layout.hpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Fixed diagnostics for an internal validation boundary. Formatting a detailed · [reviewed contract](#b0004) |
| [B0005 · 24–32](../../../../../../include/crown/storage/accounted_layout.hpp#L24) | Type/record definition: class TupleValidationFailure final : public std::exception | returns issue_; source comment (unverified): // Fixed diagnostics for an internal validation boundary. Formatting a detailed · [reviewed contract](#b0005) |
| [B0006 · 33–50](../../../../../../include/crown/storage/accounted_layout.hpp#L33) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // S05 immutable metadata copy. Only flat fields, compiled equalities · [reviewed contract](#b0006) |
| [B0007 · 51–51](../../../../../../include/crown/storage/accounted_layout.hpp#L51) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0007) |
| [B0008 · 52–83](../../../../../../include/crown/storage/accounted_layout.hpp#L52) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A read-only descriptor handle sharing this funded metadata and token. · [reviewed contract](#b0008) |
| [B0009 · 84–84](../../../../../../include/crown/storage/accounted_layout.hpp#L84) | Callable definition: explicit AccountedLayout(std::shared_ptr&lt;const Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0009) |
| [B0010 · 85–96](../../../../../../include/crown/storage/accounted_layout.hpp#L85) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 97–97](../../../../../../include/crown/storage/accounted_layout.hpp#L97) | Callable definition: \[\[nodiscard\]\] const AccountedLayout& layout() const & noexcept | calls ; returns layout_ · [reviewed contract](#b0011) |
| [B0012 · 98–98](../../../../../../include/crown/storage/accounted_layout.hpp#L98) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 99–99](../../../../../../include/crown/storage/accounted_layout.hpp#L99) | Callable definition: \[\[nodiscard\]\] RowView values() const & noexcept | calls view; returns values_.view() · [reviewed contract](#b0013) |
| [B0014 · 100–102](../../../../../../include/crown/storage/accounted_layout.hpp#L100) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Hash/equality visit actual cells and string bytes; the layout token · [reviewed contract](#b0014) |
| [B0015 · 103–103](../../../../../../include/crown/storage/accounted_layout.hpp#L103) | Callable definition: \[\[nodiscard\]\] std::uint64_t hash() const noexcept | calls view; returns values_.view().hash(); source comment (unverified): // Hash/equality visit actual cells and string bytes; the layout token · [reviewed contract](#b0015) |
| [B0016 · 104–104](../../../../../../include/crown/storage/accounted_layout.hpp#L104) | Callable definition: \[\[nodiscard\]\] resource::MemoryAttribution attribution() const | calls ; returns values_.attribution() · [reviewed contract](#b0016) |
| [B0017 · 105–105](../../../../../../include/crown/storage/accounted_layout.hpp#L105) | Callable definition: \[\[nodiscard\]\] resource::MemoryUsage memory_usage() const noexcept | calls ; returns values_.memory_usage() · [reviewed contract](#b0017) |
| [B0018 · 106–107](../../../../../../include/crown/storage/accounted_layout.hpp#L106) | Explanatory comments or spacing. | source comment (unverified): // An explicit deep clone uses the metadata's existing query account. Moving · [reviewed contract](#b0018) |
| [B0019 · 108–108](../../../../../../include/crown/storage/accounted_layout.hpp#L108) | Callable definition: \[\[nodiscard\]\] AccountedTuple clone() const | calls tuple, view, attribution; returns layout_.tuple(values_.view(), values_.attribution()); growth clone; source comment (unverified): // An explicit deep clone uses the metadata's existing query account. Moving · [reviewed contract](#b0019) |
| [B0020 · 109–111](../../../../../../include/crown/storage/accounted_layout.hpp#L109) | Callable definition: \[\[nodiscard\]\] bool operator==(const AccountedTuple& other) const noexcept | calls view; returns layout_.same_token(other.layout_) && values_.view() == other.values_.view() · [reviewed contract](#b0020) |
| [B0021 · 112–117](../../../../../../include/crown/storage/accounted_layout.hpp#L112) | declares types or opens a type body. |  · [reviewed contract](#b0021) |
| [B0022 · 118–118](../../../../../../include/crown/storage/accounted_layout.hpp#L118) | Callable definition: void set_lifetime(resource::AllocationLifetime lifetime) | calls  · [reviewed contract](#b0022) |
| [B0023 · 119–120](../../../../../../include/crown/storage/accounted_layout.hpp#L119) | Callable definition: AccountedTuple(AccountedLayout layout, AccountedRow values) noexcept : layout_(std::move(layout)), values_(std::move(values)) | calls layout_, std::move, values_ · [reviewed contract](#b0023) |
| [B0024 · 121–123](../../../../../../include/crown/storage/accounted_layout.hpp#L121) | Member/declaration region. |  · [reviewed contract](#b0024) |
| [B0025 · 124–127](../../../../../../include/crown/storage/accounted_layout.hpp#L124) | Callable definition: template&lt;class Values&gt; requires std::is_same_v&lt;std::remove_cvref_t&lt;Values&gt;,TupleValuesView&gt; AccountedTuple AccountedLayout::tuple… | calls tuple_view; returns tuple_view(std::forward&lt;Values&gt;(values),attribution) · [reviewed contract](#b0025) |
| [B0026 · 128–133](../../../../../../include/crown/storage/accounted_layout.hpp#L128) | Explanatory comments or spacing. | source comment (unverified): // A construction-only token registry. The source span/objects are borrowed and · [reviewed contract](#b0026) |
| [B0027 · 134–149](../../../../../../include/crown/storage/accounted_layout.hpp#L134) | Type/record definition: class LayoutFreezeRegistry | source comment (unverified): // A construction-only token registry. The source span/objects are borrowed and · [reviewed contract](#b0027) |
| [B0028 · 150–151](../../../../../../include/crown/storage/accounted_layout.hpp#L150) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0028) |

## B0001

[Lines 1–15](../../../../../../include/crown/storage/accounted_layout.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:3d87089a04c02cc7221a1fd8dbf3ac8204382e2d7acbddefb29bea26e73fa63d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_layout.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/accounted_row.hpp"\`, \`"crown/storage/layout.hpp"\`, \`"crown/resource/allocator.hpp"\`, \`&lt;exception&gt;\`, \`&lt;memory&gt;\`, \`&lt;optional&gt;\`, \`&lt;span&gt;\`, \`&lt;string_view&gt;\`, \`&lt;utility&gt;\`, \`&lt;vector&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 16–16](../../../../../../include/crown/storage/accounted_layout.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class TupleProblem { none, invalid_layout, arity, scalar_kind, decimal_domain, repeated_variable };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the first native tuple-validation issue without owning diagnostic text. |
| inputs / outputs | Tags distinguish no issue, invalid layout, arity, scalar kind, decimal domain and repeated-variable failure. |
| invariants | A field number is meaningful only with the accompanying TupleValidationIssue; arbitrary enum casts are not validated here. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The enum declaration performs no runtime action. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 17–21](../../../../../../include/crown/storage/accounted_layout.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleValidationIssue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return native validation status without failure-path string ownership. |
| inputs / outputs | Problem enum and field index identify success or first rejected condition. |
| invariants | ok means problem==none; field is meaningful for the relevant issue and is not a row owner. |
| ownership | Two inline metadata fields only. |
| failure | Status construction/access do not throw or allocate. |
| cost | O(1). |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

## B0004

[Lines 22–23](../../../../../../include/crown/storage/accounted_layout.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:0574c4511e78c6a9e652bee167a5c000056e6b577d6c599684c775c6cb28eb6b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class TupleValidationFailure final : public std::exception\`: Fixed diagnostics for an internal validation boundary. Formatting a detailed external message is separate; no owning string is built while unwinding. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/accounted_layout.hpp:L24; use that declaration for the actual input/output shape. |
| invariants | The source note states: Fixed diagnostics for an internal validation boundary. Formatting a detailed external message is separate; no owning string is built while unwinding. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Fixed diagnostics for an internal validation boundary. Formatting a detailed external message is separate; no owning string is built while unwinding. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0005

[Lines 24–32](../../../../../../include/crown/storage/accounted_layout.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TupleValidationFailure final
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed native tuple issue across exception boundaries. |
| inputs / outputs | Wraps TupleValidationIssue and exposes static code/what plus the original field index. |
| invariants | Native presentation is separate from formatted public Error messages. |
| ownership | No owning dynamic diagnostic text inside the native failure. |
| failure | Noexcept construction/access/destruction; throwing still uses the C++ exception runtime. |
| cost | Fixed-size issue and static enum mapping; not a general recovery framework. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

## B0006

[Lines 33–50](../../../../../../include/crown/storage/accounted_layout.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedLayout {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable checked native fields, equalities and context in one query account. |
| inputs / outputs | make/freeze/clone produce owned tokens; descriptor shares a read-only public token; tuple factories validate/import values. |
| invariants | Only flat admitted metadata and binary binding bytes survive. Token identity is distinct from descriptor equality; default/moved handles are not valid descriptors. |
| ownership | Original account funds metadata block and shared owner/control; spans/context views borrow that shared lifetime. |
| failure | Native issue statuses/fixed failures distinguish bad tuples from memory admission; public callbacks separately translate diagnostics. |
| cost | Construction visits metadata with accounted scratch; token/view access fixed; validation/copy costs follow actual fields/deep bytes. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] static AccountedLayout make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and fund a fresh immutable native layout descriptor. |
| inputs / outputs | make copies LayoutId, fields, binary context binding and optional origin into the supplied account; freeze imports the same descriptor values from TupleLayout. |
| invariants | Checks positive versions, scalar/decimal domains and repeated-variable type consistency; fresh make/freeze creates a new token even for equal values. |
| ownership | Owns a funded block with fields/equality capacity/binding plus funded shared Data/control; it retains no original layout or field/binding span. |
| failure | Fixed tuple-validation, arithmetic-overflow, account-admission and allocation failures propagate before any owner is returned. |
| cost | Visits all fields/binding bytes; repeated-variable std::map scratch gives O(fields log fields) admission, funded by the same account. Equality capacity is conservatively reserved for every field, including unused tail. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 51–51](../../../../../../include/crown/storage/accounted_layout.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether an immutable funded layout handle is present. |
| inputs / outputs | Returns bool(data_); false for default or moved-from layouts. |
| invariants | Presence does not establish descriptor equality with another token. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 52–83](../../../../../../include/crown/storage/accounted_layout.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] TupleLayout descriptor() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a public descriptor sharing the funded layout token. |
| inputs / outputs | descriptor returns a TupleLayout whose field/context ranges and native tuple factory refer to the existing immutable Data. |
| invariants | No ordinary legacy field vector, binding string or new independent token is reconstructed. |
| ownership | Returned descriptor shares funded immutable ownership and can outlive this AccountedLayout wrapper. |
| failure | Empty layouts reject through required(); no allocation fallback is attempted. |
| cost | Fixed shared-handle copy and validation; no field/string copy or new control block. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedLayout clone_to(const resource::MemoryAccount&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly copy immutable metadata to a chosen account. |
| inputs / outputs | Both clone_to overloads reserve the same payload capacity, copy fields/live equalities/binding, preserve descriptor values, and optionally replace attribution. |
| invariants | A clone owns a fresh token; callers must preserve/rebind all intended aliases explicitly. This method is not an automatic runtime account migration. |
| ownership | New block and shared Data/control belong to the destination account; source owner remains independent. |
| failure | Invalid source/account, overflow, cap or allocation failures propagate without changing source. |
| cost | Copies fields/live equalities/binding and reserves the source payload capacity; one metadata block plus real funded shared owner. No source-token scan is needed. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] TupleValidationIssue validation_issue(const Row&) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check borrowed values against frozen scalar domains and compiled equalities. |
| inputs / outputs | Row/RowView/TupleValuesView variants return the first TupleValidationIssue; tuple variants throw that issue before copying a valid row under the layout's account. |
| invariants | Validation uses exact scalar kinds, decimal fit and repeated-variable equality; it does not convert/round/coerce. TupleValuesView selects its active representation without exporting an owning Row. |
| ownership | Input rows/cells/string bytes are borrowed synchronously. Successful tuple construction retains the layout and owns copied payload. |
| failure | validation_issue variants are noexcept fixed status; tuple factories can throw TupleValidationFailure or account/allocation failures. |
| cost | Field and compiled-equality traversal including compared string bytes; successful tuple additionally sizes/copies descriptors/strings into a funded row block. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 84–84](../../../../../../include/crown/storage/accounted_layout.hpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AccountedLayout(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt funded immutable layout metadata. |
| inputs / outputs | Private constructor moves an existing shared_ptr&lt;const Data&gt;. |
| invariants | It creates no independently validated descriptor, account or identity; it retains the supplied token. |
| ownership | Shared ownership retains the original account-funded Data and metadata block. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 85–96](../../../../../../include/crown/storage/accounted_layout.hpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedTuple {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one validated compact row together with its exact immutable layout token. |
| inputs / outputs | Layout factories/projections create move-only tuples; values borrows cells, clone explicitly deep-copies in the existing layout account. |
| invariants | No implicit copy or token substitution. Moved tuple is destructible and has empty row/invalid layout; block-dependent attribution/clone require owned valid state. |
| ownership | AccountedLayout shared owner plus one AccountedRow block; returned RowView retains neither independently. |
| failure | Moves are noexcept; explicit clone can validate/fund and fail before returning. |
| cost | Moves/token checks fixed; hashing/equality visit actual cells and clone copies actual bytes. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

## B0011

[Lines 97–97](../../../../../../include/crown/storage/accounted_layout.hpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const AccountedLayout& layout() const & noexcept { return layout_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact token that validated this native tuple. |
| inputs / outputs | Lvalue layout() returns the tuple's AccountedLayout by const reference; rvalue borrowing is deleted. |
| invariants | No descriptor reconstruction or source token substitution occurs. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 98–98](../../../../../../include/crown/storage/accounted_layout.hpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& layout() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent borrowing AccountedTuple layout metadata through a temporary tuple. |
| inputs / outputs | An lvalue AccountedTuple returns its layout by const reference; an rvalue call is rejected. |
| invariants | The returned reference remains tied to the tuple's AccountedLayout member. |
| ownership | The tuple retains the layout handle; callers must retain that tuple while using the reference. |
| failure | Rvalue use is a compile-time error; the lvalue accessor is noexcept. |
| cost | No allocation; the deleted overload is compile-time only. |
| Design | [include/crown/storage/accounted_layout.hpp §AccountedTuple](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp §AccountedLayout::tuple](../../../../../../src/storage/accounted_layout.cpp), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |

## B0013

[Lines 99–99](../../../../../../include/crown/storage/accounted_layout.hpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] RowView values() const & noexcept { return values_.view(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the tuple's compact scalar descriptors and deep string bytes. |
| inputs / outputs | Lvalue values() returns AccountedRow::view(); rvalue borrowing is deleted. |
| invariants | The view itself does not keep the move-only tuple or row block alive. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 100–102](../../../../../../include/crown/storage/accounted_layout.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowView values() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent returning AccountedTuple's borrowed row view from a temporary tuple. |
| inputs / outputs | The lvalue accessor returns a RowView over its AccountedRow; rvalue use is rejected. |
| invariants | The view's scalar descriptors and string bytes remain inside the tuple's owned block. |
| ownership | Keep the AccountedTuple alive for every use of the RowView. |
| failure | Rvalue use is a compile-time error; creating an lvalue view does not validate or copy cells. |
| cost | The view is a pointer/size borrow; hashing or equality later visits cells and string bytes. |
| Design | [include/crown/storage/accounted_layout.hpp §AccountedTuple](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_row.cpp §AccountedRow::view](../../../../../../src/storage/accounted_row.cpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0015

[Lines 103–103](../../../../../../include/crown/storage/accounted_layout.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t hash() const noexcept { return values_.view().hash(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact native values rather than layout identity. |
| inputs / outputs | Delegates to the row view hash, incorporating arity, scalar tags, framing and value bytes. |
| invariants | Equal hashes are not membership evidence; tuple equality also checks layout token and exact values. |
| ownership | Reads the existing owned row; returned uint64_t retains nothing. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Visits every scalar and string byte, with bounded inline-decimal render work; no heap allocation in the native hashing path. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 104–104](../../../../../../include/crown/storage/accounted_layout.hpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryAttribution attribution() const { return values_.attribution(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the row allocation attribution attached to a tuple. |
| inputs / outputs | Delegates to AccountedRow::attribution(). |
| invariants | Attribution describes an existing allocation; it is not a new memory grant. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | MemoryBlock rejects an empty/moved-from row with MemoryFailure(memory_contract); no translation here. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 105–105](../../../../../../include/crown/storage/accounted_layout.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryUsage memory_usage() const noexcept { return values_.memory_usage(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the real row block charge of a native tuple. |
| inputs / outputs | Returns AccountedRow::memory_usage(), including real request framing. |
| invariants | This row usage excludes separately shared immutable layout metadata and account control. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 106–107](../../../../../../include/crown/storage/accounted_layout.hpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L107:sha256:2edf8415ffc8c9a0bf830689fb55f03634e55714387fe19994ed0b7dd2100d70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] AccountedTuple clone() const\`: An explicit deep clone uses the metadata's existing query account. Moving a tuple transfers its complete layout+row ownership without allocation. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/accounted_layout.hpp:L108; use that declaration for the actual input/output shape. |
| invariants | The source note states: An explicit deep clone uses the metadata's existing query account. Moving a tuple transfers its complete layout+row ownership without allocation. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: An explicit deep clone uses the metadata's existing query account. Moving a tuple transfers its complete layout+row ownership without allocation. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: An explicit deep clone uses the metadata's existing query account. Moving a tuple transfers its complete layout+row ownership without allocation. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0019

[Lines 108–108](../../../../../../include/crown/storage/accounted_layout.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedTuple clone() const { return layout_.tuple(values_.view(), values_.attribution()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a validated tuple under its existing metadata account. |
| inputs / outputs | clone revalidates values through layout_.tuple and preserves the row attribution. |
| invariants | It does not select a fresh account, transfer the source token, or rely on implicit native copying. |
| ownership | The result shares immutable layout metadata but owns a separately funded row block and copied strings. |
| failure | TupleValidationFailure or account/allocator failure propagates before any result escapes; source ownership remains intact. |
| cost | Validation visits fields and compiled equalities/deep comparisons; payload sizing/copy visits all scalar descriptors and string bytes, plus one funded row allocation. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 109–111](../../../../../../include/crown/storage/accounted_layout.hpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const AccountedTuple& other) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native tuple identity and exact values. |
| inputs / outputs | Returns false unless immutable layout tokens match; then compares compact row values. |
| invariants | Equal descriptor contents from independently created tokens do not make tuples equal. |
| ownership | Only reads the two tuple owners; no result storage is retained. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Constant token comparison followed, only on a match, by scalar and lexicographic deep-byte comparisons through the first difference. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 112–117](../../../../../../include/crown/storage/accounted_layout.hpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend class AccountedLayout;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant the listed storage constructors private access to AccountedTuple. |
| inputs / outputs | Compile-time access is granted to AccountedLayout, AccountedProjection, AccountedTupleArena, AccountedReferenceTable, and AccountedIndexedTable. |
| invariants | Only those named classes gain access to AccountedTuple's private constructor and lifetime setter. |
| ownership | Friendship creates no object and transfers no tuple or row ownership. |
| failure | The access declaration has no runtime failure path. |
| cost | Compile-time access control only; no runtime work or allocation. |
| Design | [include/crown/storage/accounted_layout.hpp §AccountedTuple](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp §AccountedLayout::tuple](../../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp §AccountedProjection::apply](../../../../../../src/storage/accounted_projection.cpp) |

## B0022

[Lines 118–118](../../../../../../include/crown/storage/accounted_layout.hpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_lifetime(resource::AllocationLifetime lifetime) { values_.set_lifetime(lifetime); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify an existing tuple row allocation for native ownership reporting. |
| inputs / outputs | Friends forward the requested AllocationLifetime to the existing AccountedRow. |
| invariants | Only allocation classification changes; row bytes, logical membership and account limits are unchanged. |
| ownership | The row block remains owned by the same tuple/account. |
| failure | The underlying block rejects invalid/empty state or invalid lifetime; allocation reentrancy may throw bad_alloc. Native noexcept callers must establish the internal preconditions. |
| cost | Fixed ledger-counter reclassification; no new allocation, ledger scan or allowance refill. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 119–120](../../../../../../include/crown/storage/accounted_layout.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTuple(AccountedLayout layout, AccountedRow values) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a tuple from already admitted layout and row owners. |
| inputs / outputs | Private constructor moves both AccountedLayout and AccountedRow into the result. |
| invariants | Validation and allocation must have finished in the friend factory before this construction. |
| ownership | Transfers the row allocation and shared layout handle; retains no caller row reference. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 121–123](../../../../../../include/crown/storage/accounted_layout.hpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedLayout layout_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose an AccountedTuple from its immutable layout handle and AccountedRow payload. |
| inputs / outputs | AccountedTuple retains one layout descriptor and one row owner. |
| invariants | AccountedTuple is move-only; layout and row values stay paired for validation, hashing, and projection. |
| ownership | The layout handle shares immutable metadata; AccountedRow owns its funded block. |
| failure | The field declarations do not fail; tuple construction can fail during validation or account allocation. |
| cost | The declarations do no work; moving transfers handles, while destruction releases layout and row ownership. |
| Design | [include/crown/storage/accounted_layout.hpp §AccountedTuple](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp §AccountedLayout::tuple](../../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_row.cpp §copy_cells](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |

## B0025

[Lines 124–127](../../../../../../include/crown/storage/accounted_layout.hpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
AccountedTuple AccountedLayout::tuple(Values&& values,resource::MemoryAttribution attribution) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a public-values view to the native tuple-view boundary. |
| inputs / outputs | The constrained forwarding overload accepts exactly TupleValuesView and passes its attribution to tuple_view. |
| invariants | It creates no implicit owning Row and does not accept arbitrary container conversions. |
| ownership | The argument view is used synchronously; the returned tuple owns copied native payload and retained layout. |
| failure | The called validation/account-allocation failures propagate unchanged. |
| cost | Forwarding itself is fixed; tuple_view validates the active representation and copies actual row/string bytes into one funded block. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 128–133](../../../../../../include/crown/storage/accounted_layout.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L133:sha256:a7f60f7ea1cd5b8b64d32f01cad51714c3f55fdf7965bdaa2caf6c83b82806f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class LayoutFreezeRegistry\`: A construction-only token registry. The source span/objects are borrowed and must stay alive and unmoved until registry destruction. Returned layouts retain no source reference and survive both registry and source destruction. Copy aliases share exactly one newly frozen token; descriptor-equal source layouts with different tokens remain different. Registry storage is charged. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/accounted_layout.hpp:L134; use that declaration for the actual input/output shape. |
| invariants | The source note states: A construction-only token registry. The source span/objects are borrowed and must stay alive and unmoved until registry destruction. Returned layouts retain no source reference and survive both registry and source destruction. Copy aliases share exactly one newly frozen token; descriptor-equal source layouts with different tokens remain different. Registry storage is charged. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: A construction-only token registry. The source span/objects are borrowed and must stay alive and unmoved until registry destruction. Returned layouts retain no source reference and survive both registry and source destruction. Copy aliases share exactly one newly frozen token; descriptor-equal source layouts with different tokens remain different. Registry storage is charged. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: A construction-only token registry. The source span/objects are borrowed and must stay alive and unmoved until registry destruction. Returned layouts retain no source reference and survive both registry and source destruction. Copy aliases share exactly one newly frozen token; descriptor-equal source layouts with different tokens remain different. Registry storage is charged. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0027

[Lines 134–149](../../../../../../include/crown/storage/accounted_layout.hpp#L134); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class LayoutFreezeRegistry {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use temporary construction slots to preserve source-token aliasing during import. |
| inputs / outputs | Borrowed source descriptors plus destination account provide lazy get(index) frozen layouts. |
| invariants | Source objects stay alive/unmoved throughout registry use; aliases share a copied token, not merely equal descriptors. |
| ownership | Registry scratch is accounted; returned layouts survive independently and do not retain the source span. |
| failure | Construction/lazy funding can fail; no query execution or global cache is published. |
| cost | O(n) slot storage and linear-prefix get scans; construction-only, not a runtime lookup registry. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] AccountedLayout get(std::size_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze source aliases once while importing immutable layout metadata. |
| inputs / outputs | get(index) scans the source prefix for the first matching token, fills that one optional slot lazily, and returns a shared AccountedLayout handle. |
| invariants | Equal descriptors with distinct original tokens remain distinct; copies sharing a source token share one newly frozen token. |
| ownership | The construction-only registry borrows stable source span/objects; slots are accounted scratch. Returned layouts own their metadata independently of registry/source lifetime. |
| failure | Out-of-range index throws memory_contract; lazy freeze/account/allocation failures propagate and leave no completed slot at that key. |
| cost | O(index+1) token scan per get, plus one make/freeze only on first use of that source token; n repeated gets can do O(n²) prefix comparisons. Not a hot lookup registry. |
| Design | [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0028

[Lines 150–151](../../../../../../include/crown/storage/accounted_layout.hpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L151:sha256:7089e9cc52c39a53c28433397476fe0fa1e71e49e678f867277ec88cc7e152ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/accounted_layout.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
