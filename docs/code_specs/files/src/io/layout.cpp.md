# `src/io/layout.cpp` — block usage map

[Source](../../../../../src/io/layout.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `fb049555e882bcac3aee73c2a799e13e9608259bf3dc37c2a6789ffbd0e0b707`. 74 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/layout.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–12](../../../../../src/io/layout.cpp#L8) | Callable definition: std::size_t index(const Json& value,std::string_view path) | calls detail::unsigned_integer, std::string, max, detail::fail; returns static_cast&lt;std::size_t&gt;(number) · [reviewed contract](#b0002) |
| [B0003 · 13–21](../../../../../src/io/layout.cpp#L13) | Callable definition: ScalarType scalar(const Json& value) | calls detail::string, Error; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../src/io/layout.cpp#L22) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 23–33](../../../../../src/io/layout.cpp#L23) | Callable definition: Json write_layout(const storage::TupleLayout& layout) | calls Json::array, fields, type_name, Json; returns {{@ ,1},{@ ,layout.id().value},{@ ,@ },; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 34–60](../../../../../src/io/layout.cpp#L34) | Callable definition: storage::TupleLayout read_layout(std::string_view text) | calls detail::parse_json, detail::fields, detail::version, at; returns {LayoutId{index(input.at(@ ),@ )},std::move(fields),std::move(bound),origin}; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 61–64](../../../../../src/io/layout.cpp#L61) | Callable definition: Json write_projection(const storage::Projection& projection) | calls Json::array, fields, push_back, write_layout; returns {{@ ,1},{@ ,write_layout(projection.source())},{@ ,write_layout(projection.target())},{@ ,std::move…; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 65–73](../../../../../src/io/layout.cpp#L65) | Callable definition: storage::Projection read_projection(std::string_view text,const storage::TupleLayout& source,const storage::TupleLayout& target) | calls detail::parse_json, detail::fields, detail::version, at; returns {source,target,std::move(fields)}; growth push_back; 1 loop sites; source comment (unverified): // Reparse both descriptors, then retain the supplied actual layout handles on success. · [reviewed contract](#b0008) |
| [B0009 · 74–74](../../../../../src/io/layout.cpp#L74) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0009) |

## B0001

[Lines 1–7](../../../../../src/io/layout.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/layout.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read/write explicit tuple-layout and projection descriptors with constructor-enforced local schema contracts. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–12](../../../../../src/io/layout.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t index(const Json& value,std::string_view path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a strict unsigned JSON ID into this host size domain. |
| inputs / outputs | Json/path view in; size_t out. |
| invariants | Rejects above-size_t values before narrowing; does not prove that the resulting ID names a catalog entry. |
| ownership | Scalar only; converting path view to std::string at the call can allocate even on success. |
| failure | Strict numeric/type/range errors preserve invalid_document; ordinary path allocation can fail. |
| cost | O(path bytes) temporary copy plus O(1) numeric conversion. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–21](../../../../../src/io/layout.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType scalar(const Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize one supported layout scalar type label. |
| inputs / outputs | DOM string in; ScalarType out for int64/string/bool/date/decimal. |
| invariants | No coercion or unknown fallback; decimal domain parameters checked by caller/constructor. |
| ownership | Local name is an ordinary string copy of DOM text. |
| failure | Wrong DOM type rejects; unsupported name throws unsupported_type with copied label. |
| cost | O(label bytes) copy/compare; ordinary allocation possible. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 22–22](../../../../../src/io/layout.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [docs/code_specs/files/src/io/layout.cpp.md](layout.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/semantics.md](../../../../semantics.md) |

## B0005

[Lines 23–33](../../../../../src/io/layout.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_layout(const storage::TupleLayout& layout) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one layout descriptor as an independently owned JSON object. |
| inputs / outputs | Valid TupleLayout in; schema/context/origin/field descriptors out in supplied order. |
| invariants | Shared descriptor metadata is read, not cloned into another native descriptor; emitted layout_id/binding fields do not grant token identity. |
| ownership | Borrows layout; DOM deep-copies binding/text and field records using ordinary allocation. |
| failure | Moved-from layout accessor/type_name or DOM allocation failure propagates before public return. |
| cost | O(fields+context binding bytes) DOM construction; result owns ordinary nodes/strings. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 34–60](../../../../../src/io/layout.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::TupleLayout read_layout(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a standalone owning layout and run TupleLayout constructor validation. |
| inputs / outputs | Text in; exact version1/nonnull_exact_binary descriptor and field/origin/context values reconstructed. |
| invariants | Decimal precision1..38 and scale&lt;=precision checked before narrowing; constructor additionally checks positive versions, scalar/domain consistency and repeated-variable type equality. Descriptor equality is not native token authority. |
| ownership | Ordinary input DOM, vector&lt;Field&gt;, binding string and shared descriptor Data are owned; constructor builds ordinary map/equality-vector scratch. |
| failure | Parsing/shape/type/unsupported semantics/domain/constructor/OOM failures abort private construction and leave caller unchanged. |
| cost | Full DOM parse; O(F log F) repeated-variable map construction plus binding/field copies and equality storage; output not funded by an arbitrary query account. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 61–64](../../../../../src/io/layout.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_projection(const storage::Projection& projection) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize projection indices together with complete source and target descriptors. |
| inputs / outputs | Valid Projection in; owning version1 JSON object out. |
| invariants | Indices and descriptors are exported; this does not create native projection token identity. |
| ownership | DOM owns field array and both descriptor exports; original metadata borrowed. |
| failure | Moved-from accessor/descriptor/DOM OOM failure propagates. |
| cost | O(projection width+source fields+target fields+binding bytes) DOM construction. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 65–73](../../../../../src/io/layout.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Projection read_projection(std::string_view text,const storage::TupleLayout& source,const storage::TupleLayout& target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct a projection bound to the caller supplied actual layouts. |
| inputs / outputs | Text plus valid source/target in; exported descriptors must exactly same_descriptor the supplied metadata, then field IDs form a Projection. |
| invariants | Nested descriptors are dumped and reparsed; Projection constructor checks width/range/domain/variable invariants. Equal labels/IDs alone are insufficient. |
| ownership | Result retains supplied actual layout handles, owns ordinary projection metadata; temporary parsed descriptors/DOM/text are separately owned and released. |
| failure | Mismatch rejects before Projection construction; parser/constructor/OOM failure publishes no result. |
| cost | Outer parse plus two subtree dump+parse/layout-construction passes, full descriptor comparisons and Projection validation; all are cold explicit IO work. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [include/crown/io/layout.hpp](../../../../../include/crown/io/layout.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 74–74](../../../../../src/io/layout.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L74:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/layout.cpp](../../../../../src/io/layout.cpp), [docs/code_specs/files/src/io/layout.cpp.md](layout.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/semantics.md](../../../../semantics.md) |
