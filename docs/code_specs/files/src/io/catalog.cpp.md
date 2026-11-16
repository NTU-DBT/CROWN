# `src/io/catalog.cpp` — block usage map

[Source](../../../../../src/io/catalog.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `4543f040e8e61243cda2348f6ea945b845e6ad3e060f99feee4123bc5e32fcdb`. 166 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/catalog.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 11–17](../../../../../src/io/catalog.cpp#L11) | Callable definition: ScalarType scalar_type(const Json& input) | calls string, type_name, Error; returns type; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 18–23](../../../../../src/io/catalog.cpp#L18) | Callable definition: ConstraintStatus status(const Json& input) | calls string, Error; returns ConstraintStatus::enforced; ConstraintStatus::untrusted · [reviewed contract](#b0003) |
| [B0004 · 24–33](../../../../../src/io/catalog.cpp#L24) | Callable definition: std::vector&lt;ColumnId&gt; column_ids(const Table& table, const Json& input) | calls array, string, std::find_if, begin; returns column.name == name; result; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 34–38](../../../../../src/io/catalog.cpp#L34) | Callable definition: Json column_names(const Table& table, const std::vector&lt;ColumnId&gt;& columns) | calls Json::array, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 39–40](../../../../../src/io/catalog.cpp#L39) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 41–119](../../../../../src/io/catalog.cpp#L41) | Callable definition: Catalog read_catalog_payload(const Json& input) | calls fields, unsigned_integer, at, array; returns candidate.name == target_name; catalog; growth emplace_back, push_back; 6 loop sites; source comment (unverified): // Foreign keys may point forward or back to any declared physical relation. · [reviewed contract](#b0007) |
| [B0008 · 120–120](../../../../../src/io/catalog.cpp#L120) | Explanatory comments or spacing. |  |
| [B0009 · 121–155](../../../../../src/io/catalog.cpp#L121) | Callable definition: Json write_catalog_payload(const Catalog& catalog) | calls catalog::validate_catalog, Json::array, type_name, push_back; returns {{@ , catalog.version}, {@ , std::move(tables)}}; growth push_back; 5 loop sites · [reviewed contract](#b0009) |
| [B0010 · 156–156](../../../../../src/io/catalog.cpp#L156) | Explanatory comments or spacing. |  |
| [B0011 · 157–162](../../../../../src/io/catalog.cpp#L157) | Callable definition: Catalog read_catalog(std::string_view text) | calls parse_json, fields, version, at; returns read_catalog_payload(input.at(@ )) · [reviewed contract](#b0011) |
| [B0012 · 163–165](../../../../../src/io/catalog.cpp#L163) | Callable definition: Json write_catalog(const Catalog& catalog) | calls write_catalog_payload; returns {{@ , 1}, {@ , write_catalog_payload(catalog)}} · [reviewed contract](#b0012) |
| [B0013 · 166–166](../../../../../src/io/catalog.cpp#L166) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0013) |

## B0001

[Lines 1–10](../../../../../src/io/catalog.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:d81598b61eea0b2628f9f64fe5f9db28c5d570116960c95e2162c5e9369d8dc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/catalog.hpp, crown/catalog/catalog.hpp, json.hpp, algorithm, string) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/code_specs/files/src/io/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0002

[Lines 11–17](../../../../../src/io/catalog.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType scalar_type(const Json& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one supported catalog scalar type name. |
| inputs / outputs | Matches exact strings for int64, string, boolean, date or decimal; returns ScalarType. |
| invariants | SQL-only unknown/int32 are not catalog scalar kinds and no spelling/case coercion occurs. |
| ownership | Temporary copied type name is ordinary text; result is an inline enum. |
| failure | Wrong JSON type uses invalid_document; unknown name throws unsupported_type. No fallback scalar kind. |
| cost | Five bounded name comparisons over actual bytes and one input string copy; no schema/row traversal. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 18–23](../../../../../src/io/catalog.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ConstraintStatus status(const Json& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read explicit enforced/untrusted constraint status metadata. |
| inputs / outputs | Accepts exact enforced or untrusted text; returns ConstraintStatus. |
| invariants | An enforced schema declaration is a policy for later data enforcement, not evidence that any input row set already satisfies it. |
| ownership | Returns inline enum; temporary copied name is not retained. |
| failure | Wrong JSON type or unknown status rejects with the existing invalid_document/invalid_catalog boundary. |
| cost | Fixed comparisons and string copy; no constraint data evaluation. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 24–33](../../../../../src/io/catalog.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<ColumnId> column_ids(const Table& table, const Json& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve ordered column-name references against one table descriptor. |
| inputs / outputs | For each JSON string, linearly finds an exact column.name and appends its numeric ColumnId. |
| invariants | Order and repetition are preserved for later catalog validation; the helper does not treat names as aliases or silently ignore unknown columns. |
| ownership | Returned ordinary vector owns IDs; input table/name bytes are borrowed synchronously. |
| failure | Malformed array/name, unknown column or allocator failure rejects; no partial Catalog is published. |
| cost | O(reference_count*table_columns) name comparisons in the worst case, including compared bytes, plus copied names and vector growth. No hidden hash index is built. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 34–38](../../../../../src/io/catalog.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json column_names(const Table& table, const std::vector<ColumnId>& columns) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate validated internal ColumnIds back to owned schema names. |
| inputs / outputs | Appends table.columns\[column.value\].name for each ordered ID into JSON. |
| invariants | Caller must supply validated IDs; \[\] is intentionally unchecked here and write_catalog_payload validates the whole Catalog first. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Valid-input serialization/allocation errors propagate; out-of-range internal IDs violate this helper's precondition. |
| cost | Visits selected IDs and copies actual name bytes; no name lookup or row scan. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 39–40](../../../../../src/io/catalog.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L40:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/code_specs/files/src/io/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0007

[Lines 41–119](../../../../../src/io/catalog.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog read_catalog_payload(const Json& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and validate a complete owned catalog in two passes. |
| inputs / outputs | Strictly reads version, tables/columns/domains, then unique/FK constraints, statistics and key hints after all tables exist; finally runs catalog::validate_catalog. |
| invariants | Allows forward/back/self FK targets by declaration order; binary collation only; domain/constraint/index consistency is completed by final schema validation. No database rows are admitted or dependencies used to remove mutable query atoms. |
| ownership | Returns ordinary owned tables/columns/strings/constraints/stats/hints independent of input DOM. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. Specific unsupported type/collation/constraint and invalid_catalog errors retain their distinct codes. |
| cost | Full DOM metadata traversal/copy, linear table/column-name resolution for references, then complete catalog validation. This can include nested name/reference checks; not a constant or byte-accounted operation. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

```text
  // Foreign keys may point forward or back to any declared physical relation.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve relationship metadata only after every table's columns have been constructed. |
| inputs / outputs | Second pass converts FK target table names and both source/target ordered column names to IDs, and attaches statistics/hints. |
| invariants | No single-pass dependency ordering or forward-reference rejection is imposed; final validation still rejects duplicate/invalid domains and inconsistent enforced references. |
| ownership | Modifies only the local owned Catalog under construction; input JSON remains borrowed. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Constraint/estimate/hint iteration with linear table/column-name searches and ordinary container/text allocation. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 121–155](../../../../../src/io/catalog.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_catalog_payload(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a validated full catalog including cost-only metadata. |
| inputs / outputs | Validates first, then emits all tables, scalar/nullability/binary-collation/domain metadata, ordered constraints with target names, statistics, hints and source-schema versions. |
| invariants | The writer preserves enforced/untrusted status but does not enforce a live database. Statistics/key hints remain cost metadata, not logical proof or permission to drop source atoms. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Invalid catalog, scalar type or ordinary allocation/serialization failure propagates before a completed JSON graph is returned. |
| cost | Complete catalog validation plus nested metadata/name/text copying. Includes statistics/hints even when later semantic identity removes them from its local copy. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 157–162](../../../../../src/io/catalog.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog read_catalog(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the standalone versioned catalog envelope. |
| inputs / outputs | Common JSON parser rejects duplicate/unknown fields and unsupported schema version, then read_catalog_payload owns/validates the catalog. |
| invariants | The result is an editable validated descriptor snapshot, not a retained native program source owner or proof token. |
| ownership | Input DOM is temporary; returned ordinary Catalog owns its copied metadata. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Full JSON parse (including key bookkeeping/depth checks) plus the two-pass catalog conversion/validation. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 163–165](../../../../../src/io/catalog.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_catalog(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a complete catalog payload in its independent wire-format version. |
| inputs / outputs | Returns schema_version=1 with write_catalog_payload(catalog). |
| invariants | Wire schema version is distinct from catalog.version/source_schema_version; the envelope does not create source/runtime authority. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Underlying full validation/export plus small envelope construction; no additional data-row pass. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 166–166](../../../../../src/io/catalog.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L166:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/code_specs/files/src/io/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |
