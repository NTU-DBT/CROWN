# `include/crown/ir/scalar.hpp` — block usage map

[Source](../../../../../../include/crown/ir/scalar.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Parse, compare, hash and format exact scalar DTO values.

Snapshot SHA-256: `8b3b5a06d1ad9c1d0338e3560e6146c6b3ed98616594f72e66d8c5f17f3ae859`. 51 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/ir/scalar.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Borrowed canonical coefficient, with no formatting/copy allocation. The · [reviewed contract](#b0001) |
| [B0002 · 11–15](../../../../../../include/crown/ir/scalar.hpp#L11) | Type/record definition: struct DecimalParts | source comment (unverified): // Borrowed canonical coefficient, with no formatting/copy allocation. The · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../../include/crown/ir/scalar.hpp#L16) | Explanatory comments or spacing. | source comment (unverified): // Finite Gregorian dates, 0001-01-01 through 9999-12-31. No timezone, · [reviewed contract](#b0003) |
| [B0004 · 18–28](../../../../../../include/crown/ir/scalar.hpp#L18) | Type/record definition: class Date | returns days_; source comment (unverified): // Finite Gregorian dates, 0001-01-01 through 9999-12-31. No timezone, · [reviewed contract](#b0004) |
| [B0005 · 29–32](../../../../../../include/crown/ir/scalar.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // An exact finite decimal. Its canonical coefficient has at most 38 digits, · [reviewed contract](#b0005) |
| [B0006 · 33–50](../../../../../../include/crown/ir/scalar.hpp#L33) | Type/record definition: class Decimal | returns {digits_, scale_, negative_}; source comment (unverified): // An exact finite decimal. Its canonical coefficient has at most 38 digits, · [reviewed contract](#b0006) |
| [B0007 · 51–51](../../../../../../include/crown/ir/scalar.hpp#L51) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0007) |

## B0001

[Lines 1–10](../../../../../../include/crown/ir/scalar.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:26f4111a01bf110c2d192ed23dc9f448d7230907b6518f6b33649679497b8d7f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and comparison/string dependencies, then crown namespace opening for DecimalParts, Date, and Decimal value declarations. Embedded source note records intended usage: Borrowed canonical coefficient, with no formatting/copy allocation. The view remains valid only while its Decimal is alive and unmodified. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/ir/scalar.hpp](../../../../../../include/crown/ir/scalar.hpp), [docs/code_specs/files/include/crown/ir/scalar.hpp.md](scalar.hpp.md), [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0002

[Lines 11–15](../../../../../../include/crown/ir/scalar.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DecimalParts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose borrowed canonical decimal components without formatting. |
| inputs / outputs | parts() returns coefficient string_view, scale and sign. |
| invariants | Digits/scale/sign obey the owning Decimal or InlineDecimal canonical invariant. |
| ownership | Digits borrow their source; moving, mutating or destroying that source can invalidate the view. |
| failure | Caller must retain a valid unchanged source; this view adds no recovery or ownership layer. |
| cost | Fixed view/scalar copy, no allocation. |
| Design | [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0003

[Lines 16–17](../../../../../../include/crown/ir/scalar.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:59f047ac21a8ad5b1244fa45afa9d497d7966291676c79d457e42532886b216f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Finite Gregorian dates, 0001-01-01 through 9999-12-31. No timezone, locale-dependent input, BC dates or PostgreSQL infinity sentinels. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/scalar.hpp lines 14-19; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/scalar.hpp](../../../../../../include/crown/ir/scalar.hpp), [docs/code_specs/files/include/crown/ir/scalar.hpp.md](scalar.hpp.md), [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0004

[Lines 18–28](../../../../../../include/crown/ir/scalar.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Date {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one finite Gregorian day with inline chronological identity. |
| inputs / outputs | Default is1970-01-01; parse admits0001..9999; epoch_days/comparison expose the inline day. |
| invariants | Private epoch constructor prevents ordinary unchecked external epoch values; scalar arithmetic is not provided. |
| ownership | Owns int32 only; copy/move do not retain text. |
| failure | Parsing handles malformed input; normal inline copy/access/comparison need no failure machinery. |
| cost | Fixed-size value; formatting owns a separate standard string. |
| Design | [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0005

[Lines 29–32](../../../../../../include/crown/ir/scalar.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L32:sha256:769c5ab1053d27968bcbdf2950a7585a72ddc5c697f53616eddbada9f9de277d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: An exact finite decimal. Its canonical coefficient has at most 38 digits, and its scale is 0..38. This is a value domain, not SQL DECIMAL(p,s) coercion. Parse never rounds, converts through floating point, or silently overflows. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/scalar.hpp lines 27-34; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/scalar.hpp](../../../../../../include/crown/ir/scalar.hpp), [docs/code_specs/files/include/crown/ir/scalar.hpp.md](scalar.hpp.md), [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0006

[Lines 33–50](../../../../../../include/crown/ir/scalar.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Decimal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one canonical exact bounded decimal scalar. |
| inputs / outputs | Parse produces sign/coefficient/scale; parts borrows components; equality/order compare canonical numeric identity. |
| invariants | Canonical zero is positive with scale0; coefficient&lt;=38digits and scale&lt;=38. Copy operations also serve rvalues to keep both source/destination canonical. |
| ownership | Owns a bounded standard coefficient string; parts does not extend its lifetime. |
| failure | Parsing/ordinary string copy can fail; no decimal SQL arithmetic or annotation admission is implied. |
| cost | Bounded coefficient copy/order work with possible standard allocation; copying an rvalue intentionally does not empty its source. |
| Design | [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |

## B0007

[Lines 51–51](../../../../../../include/crown/ir/scalar.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/scalar.hpp](../../../../../../include/crown/ir/scalar.hpp), [docs/code_specs/files/include/crown/ir/scalar.hpp.md](scalar.hpp.md), [docs/scalars.md](../../../../../scalars.md), [docs/semantics.md](../../../../../semantics.md) |
