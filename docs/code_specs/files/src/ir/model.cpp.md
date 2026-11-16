# `src/ir/model.cpp` — block usage map

[Source](../../../../../src/ir/model.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define/validate query variables, atom occurrences, scopes and output metadata.

Snapshot SHA-256: `e0d24cc7ad42403c793307fdace5c9d1c25b11c67a138d4b3920adab50ef19bd`. 140 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/ir/model.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/ir/model.cpp#L10) | Callable definition: void require(bool condition, const std::string& message) | calls Error; guard void require(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 13–16](../../../../../src/ir/model.cpp#L13) | Callable definition: void unique_name(std::set&lt;std::string&gt;& names, const std::string& name, const std::string& kind) | calls require, empty, insert; guard require(!name.empty(), kind + " name must not be empty");; growth insert · [reviewed contract](#b0003) |
| [B0004 · 17–18](../../../../../src/ir/model.cpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 19–26](../../../../../src/ir/model.cpp#L19) | Callable definition: ScalarType type_of(const Value& value) | calls Error; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0005) |
| [B0006 · 27–36](../../../../../src/ir/model.cpp#L27) | Callable definition: std::string type_name(ScalarType type) | calls Error; returns @; @ · [reviewed contract](#b0006) |
| [B0007 · 37–40](../../../../../src/ir/model.cpp#L37) | declares namespace scope. | source comment (unverified): // Public-value hashing can allocate while rendering Decimal text. Native · [reviewed contract](#b0007) |
| [B0008 · 41–63](../../../../../src/ir/model.cpp#L41) | Type/record definition: class ValueHasher | returns hash_; 2 loop sites; source comment (unverified): // Public-value hashing can allocate while rendering Decimal text. Native · [reviewed contract](#b0008) |
| [B0009 · 64–64](../../../../../src/ir/model.cpp#L64) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 65–69](../../../../../src/ir/model.cpp#L65) | Callable definition: std::uint64_t value_hash(const Value& value) | calls value, get; returns hasher.get() · [reviewed contract](#b0010) |
| [B0011 · 70–75](../../../../../src/ir/model.cpp#L70) | Callable definition: std::uint64_t row_hash(const Row& row) | calls integer, size, value, get; returns hasher.get(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 76–76](../../../../../src/ir/model.cpp#L76) | Explanatory comments or spacing. |  |
| [B0013 · 77–116](../../../../../src/ir/model.cpp#L77) | Callable definition: void validate(const Catalog& catalog, const Query& query) | calls catalog::validate_catalog, code, Error, what; guard require(atom.table.value &lt; catalog.tables.size(), "atom table ID out of range");; growth insert; 6 loop sites · [reviewed contract](#b0013) |
| [B0014 · 117–118](../../../../../src/ir/model.cpp#L117) | Explanatory comments or spacing. | source comment (unverified): // Shape/type/decimal checks only; collection constraints are a separate call. · [reviewed contract](#b0014) |
| [B0015 · 119–130](../../../../../src/ir/model.cpp#L119) | Callable definition: template&lt;class CatalogView&gt; void validate_row_impl(const CatalogView& catalog, TableId table, const Row& row) | calls size, Error, type_of, std::string; 1 loop sites; source comment (unverified): // Shape/type/decimal checks only; collection constraints are a separate call. · [reviewed contract](#b0015) |
| [B0016 · 131–131](../../../../../src/ir/model.cpp#L131) | Explanatory comments or spacing. |  |
| [B0017 · 132–132](../../../../../src/ir/model.cpp#L132) | Callable definition: void validate_row(const Catalog& catalog,TableId table,const Row& row) | calls validate_row_impl · [reviewed contract](#b0017) |
| [B0018 · 133–133](../../../../../src/ir/model.cpp#L133) | Callable definition: void validate_row(const program::Catalog& catalog,TableId table,const Row& row) | calls validate_row_impl · [reviewed contract](#b0018) |
| [B0019 · 134–134](../../../../../src/ir/model.cpp#L134) | Explanatory comments or spacing. |  |
| [B0020 · 135–137](../../../../../src/ir/model.cpp#L135) | Callable definition: void validate_database(const Catalog& catalog, const Database& database) | calls catalog::validate_constraints · [reviewed contract](#b0020) |
| [B0021 · 138–138](../../../../../src/ir/model.cpp#L138) | Callable definition: void validate_database(const program::Catalog& catalog,const Database& database) | calls catalog::validate_constraints · [reviewed contract](#b0021) |
| [B0022 · 139–140](../../../../../src/ir/model.cpp#L139) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0022) |

## B0001

[Lines 1–9](../../../../../src/ir/model.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7e6610367f1065dc19b8a613a51a4f79ba63b7ffc37060902cbc3cdafe2076ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/ir/model.hpp, crown/api/error.hpp, crown/catalog/catalog.hpp, crown/ir/program_model.hpp, set) and opens crown scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0002

[Lines 10–12](../../../../../src/ir/model.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a failed CQ validation condition. |
| inputs / outputs | False throws invalid_cq with the supplied message; true returns. |
| invariants | Diagnostic arguments are constructed by the caller even on successful conditions. |
| ownership | Borrows message for call; thrown Error owns its diagnostic. |
| failure | Error allocation can fail; no catch or rollback. |
| cost | Constant branch plus caller-paid message construction. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 13–16](../../../../../src/ir/model.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unique_name(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty or repeated variable/occurrence names. |
| inputs / outputs | Checks nonempty name then inserts into the caller set. |
| invariants | Name-domain uniqueness is local to the supplied set. |
| ownership | Temporary validation set owns copied names and ordered nodes. |
| failure | invalid_cq or allocation failure unwinds private validation scratch. |
| cost | Two eager diagnostic strings and logarithmic set insertion/comparisons with name-byte copying. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0004

[Lines 17–18](../../../../../src/ir/model.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0005

[Lines 19–26](../../../../../src/ir/model.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType type_of(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the active public Value alternative. |
| inputs / outputs | Checks int64/string/bool/date/decimal and returns its ScalarType. |
| invariants | No scalar content validation or type coercion; valueless variant rejects. |
| ownership | Borrows Value, returns fixed enum. |
| failure | No matching alternative throws invalid_cq; successful inspection creates no owned payload. |
| cost | Fixed five alternative checks, no successful-path allocation. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0006

[Lines 27–36](../../../../../src/ir/model.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string type_name(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a public scalar-type name. |
| inputs / outputs | Maps enum to a short owning string. |
| invariants | Unknown enum is rejected, not silently labeled. |
| ownership | Returned ordinary string owns its characters. |
| failure | invalid_cq on unknown enum; string construction may allocate. |
| cost | Fixed switch and bounded text construction; no native account/work debit. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0007

[Lines 37–40](../../../../../src/ir/model.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:1a54673ae13c0e4084333d1f85889f0237d56ea616fbe2c323c5d2b8254b94d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens anonymous/internal scope and establishes the local aliases/declarations shown before the next source block. Embedded source note records intended usage: Public-value hashing can allocate while rendering Decimal text. Native compact scalar views have a separate hashing/work path. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0008

[Lines 41–63](../../../../../src/ir/model.cpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ValueHasher
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate a noncryptographic exact public-value hash. |
| inputs / outputs | FNV-style byte accumulator with typed scalar encodings. |
| invariants | Not a persistent binding digest or authority token. Native compact-view hashing is a separate path. |
| ownership | Fixed local state; borrowed inputs; Decimal text is a temporary owner. |
| failure | Valueless Value and Decimal/string allocation failures propagate. |
| cost | Payload-sized work; Decimal to_string may allocate. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
void byte(std::uint8_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fold one byte into the hash accumulator. |
| inputs / outputs | Xor then multiply the uint64 accumulator. |
| invariants | Unsigned arithmetic intentionally wraps. |
| ownership | Mutates only this local hasher. |
| failure | No throwing operation. |
| cost | One fixed byte step. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
void integer(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash eight little-endian bytes of a fixed integer. |
| inputs / outputs | Repeated low-byte fold and right shift. |
| invariants | Signed/date callers first convert to uint64. |
| ownership | Fixed value argument and local hasher. |
| failure | No throwing operation. |
| cost | Exactly eight byte steps. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash a length-framed text payload. |
| inputs / outputs | Hashes length then every byte including NUL/high bytes. |
| invariants | Length framing distinguishes concatenations; no UTF8 validation here. |
| ownership | Borrows text for call. |
| failure | No successful-path ordinary allocation. |
| cost | Eight length steps plus one step per text byte. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
void value(const Value& cell)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash scalar type identity and exact scalar representation. |
| inputs / outputs | Hashes variant tag, then fixed scalar bytes/string bytes/Decimal canonical text. |
| invariants | Different scalar alternatives remain tagged; not source or query admission. |
| ownership | Borrows scalar; Decimal to_string owns temporary text. |
| failure | Valueless Value invalid_cq; Decimal formatting/allocation failures propagate. |
| cost | Fixed tag plus payload work; Decimal rendering allocates ordinary text. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
std::uint64_t get() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current hash accumulator. |
| inputs / outputs | Returns hash_ without finalization. |
| invariants | No independent verification implied. |
| ownership | Returns a fixed value. |
| failure | No throwing operation. |
| cost | Constant read. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

```text
std::uint64_t hash_ =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the local hash seed. |
| inputs / outputs | Stores the initial 64-bit accumulator. |
| invariants | Each public hash call creates a fresh local accumulator. |
| ownership | Inline member, no shared/global state. |
| failure | Fixed initialization. |
| cost | One fixed word per hasher. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0009

[Lines 64–64](../../../../../src/ir/model.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L64:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0010

[Lines 65–69](../../../../../src/ir/model.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t value_hash(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash one public scalar value. |
| inputs / outputs | Fresh hasher invokes value then returns its accumulator. |
| invariants | Same tagged public encoding as row hashing. |
| ownership | Input borrowed; no retained data. |
| failure | Scalar hashing/Decimal formatting failures propagate. |
| cost | Scalar payload work, including possible ordinary Decimal text allocation. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0011

[Lines 70–75](../../../../../src/ir/model.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t row_hash(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash a length-framed public physical row. |
| inputs / outputs | Hashes row length then each typed cell. |
| invariants | Row order and scalar alternatives are part of the encoding. |
| ownership | Borrows row; retains no payload. |
| failure | Scalar hashing/formatting failures propagate. |
| cost | Linear fields and payload bytes; Decimal cells can allocate text separately. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0013

[Lines 77–116](../../../../../src/ir/model.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the direct non-null CQ model against its complete catalog. |
| inputs / outputs | Checks catalog, rejects nullable columns, names/types/atom schemas/terms/decimal literals and bound head/all variables. |
| invariants | Direct CQ admission is separate from explicit SQL nullable/bag adaptation and from native plan/proof construction. |
| ownership | Borrows model; ordinary sets/string diagnostics own temporary validation scratch. |
| failure | Only invalid_catalog is translated to invalid_cq; other catalog/scalar/resource errors propagate. No model mutation. |
| cost | Full catalog/variable/atom/term/head scans, ordered-name/bound sets and eager diagnostic formatting; no native total-work grant. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0014

[Lines 117–118](../../../../../src/ir/model.cpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L118:sha256:6ec9e76ef18a4d1fab20158cda149be3ca383c6f22a35578eb1cb9fbd1c7d41b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Shape/type/decimal checks only; collection constraints are a separate call. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/ir/model.cpp lines 115-120; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0015

[Lines 119–130](../../../../../src/ir/model.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void validate_row_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate row shape, scalar types and decimal fit for either catalog representation. |
| inputs / outputs | Checks table range, arity, each type and declared decimal domain. |
| invariants | Collection-wide key/FK constraints are checked separately; it is not a complete database admission call. |
| ownership | Borrows catalog and ordinary Row; no retained row owner. |
| failure | invalid_update for table/arity/type, invalid_catalog for malformed decimal declaration, scalar_overflow for non-fitting decimal; type_of can report invalid_cq on valueless Value. |
| cost | Linear columns plus decimal-fit work; diagnostic text allocation on failures. No index lookup or native account debit here. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0017

[Lines 132–132](../../../../../src/ir/model.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_row(const Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one ordinary-catalog row through the shared validator. |
| inputs / outputs | Forwards catalog/table/row unchanged. |
| invariants | Does not validate collection constraints. |
| ownership | All inputs borrowed synchronously. |
| failure | Shared validator failures propagate. |
| cost | One forwarding call plus row-validation cost. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0018

[Lines 133–133](../../../../../src/ir/model.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_row(const program::Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one native-metadata-catalog row through the same validator. |
| inputs / outputs | Forwards native catalog view/table/ordinary Row. |
| invariants | Native catalog ownership must survive the borrow. |
| ownership | Borrowed metadata and row, no DTO reconstruction. |
| failure | Shared validator failures propagate. |
| cost | One forwarding call plus row-validation cost; no catalog deep copy. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0020

[Lines 135–137](../../../../../src/ir/model.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_database(const Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate complete ordinary-catalog database constraint validation. |
| inputs / outputs | Passes catalog/database to catalog::validate_constraints. |
| invariants | This collection validation is distinct from a row-shape check or minimum-height proof. |
| ownership | Borrows database/catalog; delegate owns any validation scratch. |
| failure | Delegate constraint/allocation errors propagate. |
| cost | Delegate collection-validation scans/index scratch; no constant-work claim. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0021

[Lines 138–138](../../../../../src/ir/model.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_database(const program::Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate complete database constraint validation over native metadata. |
| inputs / outputs | Passes native catalog/database to catalog::validate_constraints. |
| invariants | Same logical constraint boundary, without rebuilding an ordinary catalog. |
| ownership | Borrows metadata/database; delegate owns validation scratch. |
| failure | Delegate constraint/allocation errors propagate. |
| cost | Delegate collection-validation work/scratch; no native grant or timing claim. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md) |

## B0022

[Lines 139–140](../../../../../src/ir/model.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L140:sha256:016c4f6b4093963ce011309c1848aed7548adf56cce0f782adbe842d3fe1bf9c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/model.cpp](../../../../../src/ir/model.cpp), [docs/code_specs/files/src/ir/model.cpp.md](model.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |
