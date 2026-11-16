# `src/frontend/sql_rows_value.hpp` — block usage map

[Source](../../../../../src/frontend/sql_rows_value.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `2180bbae22c0a230fdc5a6ca95888c905e601b7b2ac2de5f6ba04cc16861bc15`. 75 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/frontend/sql_rows_value.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // The SQL family admits UTF8 TEXT under binary/C comparison, without U+0000. · [reviewed contract](#b0001) |
| [B0002 · 10–26](../../../../../src/frontend/sql_rows_value.hpp#L10) | Callable definition: inline bool text_fits(std::string_view text) noexcept | calls size; returns false; false; 2 loop sites; source comment (unverified): // The SQL family admits UTF8 TEXT under binary/C comparison, without U+0000. · [reviewed contract](#b0002) |
| [B0003 · 27–37](../../../../../src/frontend/sql_rows_value.hpp#L27) | Callable definition: inline ScalarType scalar(SqlKind kind) | calls storage::IndexFailure; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0003) |
| [B0004 · 38–47](../../../../../src/frontend/sql_rows_value.hpp#L38) | Callable definition: inline SqlType sql_type(const Column& column) | calls storage::IndexFailure; returns {SqlKind::int64, column.nullable, column.decimal}; {SqlKind::string, column.nullable, column.decima… · [reviewed contract](#b0004) |
| [B0005 · 48–49](../../../../../src/frontend/sql_rows_value.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Type/spec metadata is factory-validated. Decimal parts are already canonical; · [reviewed contract](#b0005) |
| [B0006 · 50–64](../../../../../src/frontend/sql_rows_value.hpp#L50) | Callable definition: inline bool fits(const SqlRowCell& value, const SqlType& type) | calls storage::type_of, scalar, text_fits, parts; returns type.nullable; false; source comment (unverified): // Type/spec metadata is factory-validated. Decimal parts are already canonical; · [reviewed contract](#b0006) |
| [B0007 · 65–74](../../../../../src/frontend/sql_rows_value.hpp#L65) | Callable definition: inline storage::ScalarView zero(ScalarType type) | calls storage::IndexFailure; returns std::int64_t{0}; std::string_view{} · [reviewed contract](#b0007) |
| [B0008 · 75–75](../../../../../src/frontend/sql_rows_value.hpp#L75) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend::rows_detail · [reviewed contract](#b0008) |

## B0001

[Lines 1–9](../../../../../src/frontend/sql_rows_value.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:b51608a1f1d54f9a1e478604e6a1a8c8b79b6440d6f5d5e487ef09b2859d9bdc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/frontend/sql_rows.hpp, crown/storage/index_failure.hpp) and opens crown::frontend::rows_detail scope for the declarations or definitions that follow. Embedded source note records intended usage: The SQL family admits UTF8 TEXT under binary/C comparison, without U+0000. This is a byte pass at source admission; native core bytes keep their wider existing domain. No locale object, conversion buffer or owning string. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [docs/code_specs/files/src/frontend/sql_rows_value.hpp.md](sql_rows_value.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0002

[Lines 10–26](../../../../../src/frontend/sql_rows_value.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool text_fits(std::string_view text) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit UTF8 bytes without U+0000. |
| inputs / outputs | A string_view is scanned with lead/continuation, truncation, overlong, surrogate and U+10FFFF checks. |
| invariants | Every indexed byte is in range; valid ASCII excluding zero passes. Empty text is valid. |
| ownership | Borrowed input only; no conversion buffer. |
| failure | Returns false, never throws. |
| cost | O(bytes), O(1) storage. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/docs/sql_rows.md §L112-124](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/docs/sql_rows.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0003

[Lines 27–37](../../../../../src/frontend/sql_rows_value.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ScalarType scalar(SqlKind kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map admitted SQL/core scalar kinds and source Column types. |
| inputs / outputs | Integer widths share int64 core representation; nullability/decimal spec copy into SqlType. |
| invariants | Unknown/invalid kind is not executable; catalog has already validated Column metadata. |
| ownership | Value descriptors only. |
| failure | Fixed IndexFailure on invalid enums/kind. |
| cost | O(1). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp §L9-15](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L60-68](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0004

[Lines 38–47](../../../../../src/frontend/sql_rows_value.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline SqlType sql_type(const Column& column)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map an admitted physical column to SQL validation metadata. |
| inputs / outputs | Catalog Column to SqlType. |
| invariants | Physical int64 is SQL bigint; decimal spec and nullable flag are preserved. |
| ownership | Copies inline metadata only. |
| failure | Unsupported enum takes fixed IndexFailure contract path. |
| cost | Constant switch/copies, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0005

[Lines 48–49](../../../../../src/frontend/sql_rows_value.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:0256ba5ecd4136bd7ac50aeb86c60f31c374996b544b6c13f755d07436809e16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Type/spec metadata is factory-validated. Decimal parts are already canonical; inspect widths directly rather than render text during a row update. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/sql_rows_value.hpp lines 46-51; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [docs/code_specs/files/src/frontend/sql_rows_value.hpp.md](sql_rows_value.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0006

[Lines 50–64](../../../../../src/frontend/sql_rows_value.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool fits(const SqlRowCell& value, const SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a nullable input/parameter against an admitted exact type. |
| inputs / outputs | NULL requires nullable; present kind must match; int32 range, UTF8 domain and decimal precision/scale are checked. |
| invariants | Decimal parts are canonical; metadata guarantees decimal spec only for decimal and precision&gt;=scale. Date is already a valid Date object. |
| ownership | Borrows scalar bytes; no rendering/owning string. |
| failure | Returns false for domain mismatch; malformed private metadata may fault. |
| cost | O(text bytes) for text, bounded decimal width inspection, otherwise O(1). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/ir/scalar.hpp §L16-49](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/ir/scalar.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L29-49](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0007

[Lines 65–74](../../../../../src/frontend/sql_rows_value.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline storage::ScalarView zero(ScalarType type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce canonical non-null payload for a NULL field. |
| inputs / outputs | Return typed integer/decimal zero, empty text, false or default date. |
| invariants | Presence bit disambiguates each sentinel from a real SQL value; core always receives a scalar. |
| ownership | All values inline; empty text has no owning allocation. |
| failure | Invalid type throws fixed contract fault. |
| cost | O(1). |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §encoding argument](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0008

[Lines 75–75](../../../../../src/frontend/sql_rows_value.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L75:sha256:685b7aeb8c0c362afd49ed324cf9944a60b9d99d90ee456586559ff86c24670d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend::rows_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [docs/code_specs/files/src/frontend/sql_rows_value.hpp.md](sql_rows_value.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
