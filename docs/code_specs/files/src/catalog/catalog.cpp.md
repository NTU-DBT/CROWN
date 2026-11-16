# `src/catalog/catalog.cpp` — block usage map

[Source](../../../../../src/catalog/catalog.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Validate schema, table/column identity and declared integrity constraints before query or data admission.

Snapshot SHA-256: `3d1c5e0444fe4fcd10caedf0fc52da818087489de2195b577f8ab5955abc2439`. 225 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [catalog](../../../subsystem_contracts.md#catalog). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/physical_runtime.md](../../../../physical_runtime.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/catalog/catalog.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–13](../../../../../src/catalog/catalog.cpp#L11) | Callable definition: void require(bool condition, const std::string& message) | calls Error; guard void require(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../src/catalog/catalog.cpp#L14) | Callable definition: void unique_name(std::set&lt;std::string&gt;& names, std::string_view name, const std::string& kind) | calls require, empty, insert, std::string; guard require(!name.empty(), kind + " name must not be empty");; growth insert · [reviewed contract](#b0003) |
| [B0004 · 18–25](../../../../../src/catalog/catalog.cpp#L18) | Callable definition: std::set&lt;ColumnId&gt; column_set(const auto& table, const auto& columns) | calls require, size, std::string, insert; guard require(column.value &lt; table.columns.size(), "column ID out of range in table " + std::string(table…; returns seen; growth insert; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../src/catalog/catalog.cpp#L26) | Callable definition: void valid_status(ConstraintStatus status) | calls require; guard require(status == ConstraintStatus::enforced \|\| status == ConstraintStatus::untrusted, "unknown con… · [reviewed contract](#b0005) |
| [B0006 · 29–32](../../../../../src/catalog/catalog.cpp#L29) | Callable definition: void valid_decimal_spec(DecimalSpec specification) | calls require; guard require(specification.precision &gt;= 1 && specification.precision &lt;= 38 && specification.scale &lt;= spe… · [reviewed contract](#b0006) |
| [B0007 · 33–38](../../../../../src/catalog/catalog.cpp#L33) | Callable definition: Row project(const Row& row, const auto& columns) | calls reserve, size, push_back; returns key; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 39–40](../../../../../src/catalog/catalog.cpp#L39) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 41–50](../../../../../src/catalog/catalog.cpp#L41) | Callable definition: bool decimal_fits(const Decimal& value, DecimalSpec specification) | calls valid_decimal_spec, to_string, find, size; returns fractional_digits &lt;= specification.scale && integer_digits + specification.scale &lt;= specification.p… · [reviewed contract](#b0009) |
| [B0010 · 51–51](../../../../../src/catalog/catalog.cpp#L51) | Explanatory comments or spacing. |  |
| [B0011 · 52–112](../../../../../src/catalog/catalog.cpp#L52) | Callable definition: template&lt;class CatalogView&gt; void validate_catalog_impl(const CatalogView& catalog) | calls require, unique_name, std::string, type_name; guard require(catalog.version &gt; 0, "catalog version must be positive");; returns unique && unique-&gt;status == ConstraintStatus::enforced &&; growth insert; 8 loop sites; source comment (unverified): // Resolve foreign targets only after all table declarations have been checked. · [reviewed contract](#b0011) |
| [B0012 · 113–113](../../../../../src/catalog/catalog.cpp#L113) | Callable definition: void validate_catalog(const Catalog& catalog) | calls validate_catalog_impl; returns validate_catalog_impl(catalog) · [reviewed contract](#b0012) |
| [B0013 · 114–114](../../../../../src/catalog/catalog.cpp#L114) | Callable definition: void validate_catalog(const program::Catalog& catalog) | calls validate_catalog_impl; returns validate_catalog_impl(catalog) · [reviewed contract](#b0013) |
| [B0014 · 115–116](../../../../../src/catalog/catalog.cpp#L115) | Explanatory comments or spacing. |  |
| [B0015 · 117–149](../../../../../src/catalog/catalog.cpp#L117) | Callable definition: template&lt;class CatalogView&gt; void validate_constraints_impl(const CatalogView& catalog, const Database& database) | calls validate_catalog, size, Error, validate_row; growth insert; 7 loop sites; source comment (unverified): // This public reference checker validates shape before projecting IDs. It is · [reviewed contract](#b0015) |
| [B0016 · 150–150](../../../../../src/catalog/catalog.cpp#L150) | Callable definition: void validate_constraints(const Catalog& catalog, const Database& database) | calls validate_constraints_impl; returns validate_constraints_impl(catalog,database) · [reviewed contract](#b0016) |
| [B0017 · 151–151](../../../../../src/catalog/catalog.cpp#L151) | Callable definition: void validate_constraints(const program::Catalog& catalog, const Database& database) | calls validate_constraints_impl; returns validate_constraints_impl(catalog,database) · [reviewed contract](#b0017) |
| [B0018 · 152–153](../../../../../src/catalog/catalog.cpp#L152) | Explanatory comments or spacing. |  |
| [B0019 · 154–163](../../../../../src/catalog/catalog.cpp#L154) | Callable definition: template&lt;class CatalogView&gt; bool requires_format3_impl(const CatalogView& catalog) | calls empty; returns true; true; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 164–164](../../../../../src/catalog/catalog.cpp#L164) | Callable definition: bool requires_format3(const Catalog& catalog) | calls requires_format3_impl; returns requires_format3_impl(catalog) · [reviewed contract](#b0020) |
| [B0021 · 165–165](../../../../../src/catalog/catalog.cpp#L165) | Callable definition: bool requires_format3(const program::Catalog& catalog) | calls requires_format3_impl; returns requires_format3_impl(catalog) · [reviewed contract](#b0021) |
| [B0022 · 166–167](../../../../../src/catalog/catalog.cpp#L166) | Explanatory comments or spacing. |  |
| [B0023 · 168–174](../../../../../src/catalog/catalog.cpp#L168) | Callable definition: template&lt;class CatalogView&gt; TableId find_table_impl(const CatalogView& catalog, std::string_view name) | calls validate_catalog, size, Error, std::string; returns TableId{i}; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 175–175](../../../../../src/catalog/catalog.cpp#L175) | Callable definition: TableId find_table(const Catalog& catalog, std::string_view name) | calls find_table_impl; returns find_table_impl(catalog,name) · [reviewed contract](#b0024) |
| [B0025 · 176–176](../../../../../src/catalog/catalog.cpp#L176) | Callable definition: TableId find_table(const program::Catalog& catalog, std::string_view name) | calls find_table_impl; returns find_table_impl(catalog,name) · [reviewed contract](#b0025) |
| [B0026 · 177–178](../../../../../src/catalog/catalog.cpp#L177) | Explanatory comments or spacing. |  |
| [B0027 · 179–204](../../../../../src/catalog/catalog.cpp#L179) | Callable definition: ColumnReference resolve_column(const Catalog& catalog, std::span&lt;const RelationBinding&gt; bindings, std::optional&lt;std::string_view&gt;… | calls validate_catalog, size, empty, Error; returns *found; growth insert; 3 loop sites · [reviewed contract](#b0027) |
| [B0028 · 205–205](../../../../../src/catalog/catalog.cpp#L205) | Explanatory comments or spacing. |  |
| [B0029 · 206–210](../../../../../src/catalog/catalog.cpp#L206) | Callable definition: void require_identity_cast(ScalarType source, ScalarType target) | calls type_name, Error · [reviewed contract](#b0029) |
| [B0030 · 211–224](../../../../../src/catalog/catalog.cpp#L211) | Callable definition: void require_identity_cast(const Column& source, const Column& target) | calls Error, require, valid_decimal_spec; guard require(column-&gt;type == ScalarType::decimal, "decimal specification requires a decimal type");; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 225–225](../../../../../src/catalog/catalog.cpp#L225) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::catalog · [reviewed contract](#b0031) |

## B0001

[Lines 1–10](../../../../../src/catalog/catalog.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:15b7537498ceb461f7b26fbb43785bda7874778df9a2c28385328af49c52e36c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/catalog/catalog.hpp, crown/ir/program_model.hpp, crown/api/error.hpp, algorithm, set, string) and opens crown::catalog scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/code_specs/files/src/catalog/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0002

[Lines 11–13](../../../../../src/catalog/catalog.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the catalog contract error when one validation condition is false. |
| inputs / outputs | Boolean condition and message in; no output. |
| invariants | Callers use this for declared catalog metadata constraints; it is not a data-query theorem or constraint scan. |
| ownership | Borrows the message on success; Error owns/copies message when thrown. |
| failure | False throws \`Error("invalid_catalog", message)\`; true returns normally. |
| cost | One callee branch, but callers prepare std::string messages first: literal conversion and dynamic concatenation can allocate on successful checks. Failure additionally constructs the owned Error/exception. |
| Design | [docs/catalog.md](../../../../catalog.md) |

## B0003

[Lines 14–17](../../../../../src/catalog/catalog.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unique_name(std::set<std::string>& names, std::string_view name, const std::string& kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a nonempty, previously unseen name and record it. |
| inputs / outputs | Mutable set, borrowed name, and kind label in; set gains an owned name on success. |
| invariants | Empty or duplicate names are rejected; callers choose scope-specific table/column/constraint sets. |
| ownership | The set owns copied strings; input views/label remain borrowed. |
| failure | Uses \`require\` for empty/duplicate cases, yielding \`invalid_catalog\`. |
| cost | Ordered-set insertion O(log N) comparisons and O(name bytes) string copy/allocation. |
| Design | [docs/catalog.md](../../../../catalog.md) |

## B0004

[Lines 18–25](../../../../../src/catalog/catalog.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<ColumnId> column_set(const auto& table, const auto& columns)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a key/statistic column list and return its set form. |
| inputs / outputs | Table-like object and column sequence in; unique sorted \`ColumnId\` set out. |
| invariants | Every id is in range and no id is repeated; empty sets are valid. |
| ownership | Reads table and sequence; returned set owns its nodes. |
| failure | Out-of-range/duplicate IDs throw \`invalid_catalog\`. |
| cost | For k listed columns, O(k log k) tree operations and O(k) node allocations. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0005

[Lines 26–28](../../../../../src/catalog/catalog.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid_status(ConstraintStatus status)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept the two declared constraint trust states. |
| inputs / outputs | Constraint status enum in; no output. |
| invariants | Only enforced and untrusted are valid. |
| ownership | Scalar input only. |
| failure | Unknown enum values throw \`invalid_catalog\`. |
| cost | One constant-time comparison pair. |
| Design | [docs/catalog.md](../../../../catalog.md) |

## B0006

[Lines 29–32](../../../../../src/catalog/catalog.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid_decimal_spec(DecimalSpec specification)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate fixed decimal precision and scale metadata. |
| inputs / outputs | Precision/scale pair in; no output. |
| invariants | Precision is 1..38 and scale is 0..precision. |
| ownership | Scalar input only. |
| failure | Invalid bounds throw \`invalid_catalog\`. |
| cost | Constant-time comparisons. |
| Design | [docs/catalog.md](../../../../catalog.md) |

## B0007

[Lines 33–38](../../../../../src/catalog/catalog.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row project(const Row& row, const auto& columns)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy selected physical values into a key row for reference constraint checking. |
| inputs / outputs | Borrowed row plus column-ID sequence in; owning projected \`Row\` out. |
| invariants | Caller validates row shape and column ids first; order and repetition are taken from the sequence (catalog validation rejects repeated key ids). |
| ownership | Reads original values and copies each selected \`Value\`; returned vector and any string payloads own their copies. |
| failure | No local range checks; caller preconditions must hold or vector indexing would be invalid. Allocation/copy failures propagate. |
| cost | Reserves k elements and copies k scalar values; O(k plus copied string bytes), one vector reserve and possible nested string allocations. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0008

[Lines 39–40](../../../../../src/catalog/catalog.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/code_specs/files/src/catalog/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0009

[Lines 41–50](../../../../../src/catalog/catalog.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool decimal_fits(const Decimal& value, DecimalSpec specification)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact decimal representability under a validated fixed precision/scale. |
| inputs / outputs | Decimal value and precision/scale in; Boolean result. |
| invariants | No rounding or truncation: fractional digits must fit scale and integer digits plus scale must fit precision. |
| ownership | Borrows Decimal while producing a temporary text representation. |
| failure | Invalid specification throws \`invalid_catalog\` via \`valid_decimal_spec\`; no semantic rejection is silently converted to false. |
| cost | Creates \`value.to_string()\` and scans digit positions, O(decimal text length) with one temporary string. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0011

[Lines 52–112](../../../../../src/catalog/catalog.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void validate_catalog_impl(const CatalogView& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate catalog metadata and cross-references for either public or program catalog view. |
| inputs / outputs | Borrowed catalog view in; no output. |
| invariants | Checks positive catalog/source versions; unique names; known scalar kinds; binary collation; decimal specs; constraint names and key column ids; distinct estimate column sets; hint columns/reason; foreign targets, arity/types, and enforced unique target-set requirement. Nullable declarations remain valid metadata. |
| ownership | Borrows catalog throughout; temporary ordered sets own duplicate-detection keys only. |
| failure | Declared invalid fields throw \`invalid_catalog\`; nonbinary collation yields \`unsupported_collation\`. Unknown type is translated from \`type_name\` Error to \`invalid_catalog\`; it is not swallowed. |
| cost | Full metadata traversal; ordered-set insertions allocate; cross-reference pass scans foreign keys and target unique declarations, rebuilding column sets during match checks. Cost grows with schema/constraint metadata, not database rows. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0012

[Lines 113–113](../../../../../src/catalog/catalog.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_catalog(const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose metadata validation for the runtime catalog record. |
| inputs / outputs | Borrowed \`Catalog\` in; no output. |
| invariants | Delegates to the shared implementation; accepts nullable source metadata and validates constraints’ declarations only. |
| ownership | Borrows catalog; no mutation or retained state. |
| failure | Propagates \`invalid_catalog\` and \`unsupported_collation\` from validation. |
| cost | Full metadata traversal and temporary validation sets. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0013

[Lines 114–114](../../../../../src/catalog/catalog.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_catalog(const program::Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the same metadata contract for serialized/program catalog records. |
| inputs / outputs | Borrowed \`program::Catalog\` in; no output. |
| invariants | Uses the shared view implementation, keeping catalog and program metadata rules aligned. |
| ownership | Borrows catalog; no mutation or retained state. |
| failure | Propagates the same validation errors. |
| cost | Full metadata traversal and temporary validation sets. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0015

[Lines 117–149](../../../../../src/catalog/catalog.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void validate_constraints_impl(const CatalogView& catalog, const Database& database)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate database shape and all enforced unique/foreign-key declarations against a complete reference database. |
| inputs / outputs | Borrowed catalog and database in; no output. |
| invariants | Revalidates catalog; requires matching table count; validates every row before projecting ids. Only enforced constraints assert data properties; untrusted entries are skipped. Empty unique keys permit at most one row; empty FKs require a target row for each source row. |
| ownership | Borrows both inputs; temporary ordered \`Relation\` sets own projected key rows during each constraint check. Does not mutate database. |
| failure | Shape errors propagate from \`validate_row\`/catalog validation; duplicate unique or missing FK key throws \`constraint_violation\`. |
| cost | Intentionally full-scan reference checker: all rows/cells are validated, then each enforced constraint projects rows and performs ordered-set operations. O(database size × enforced key work, plus set comparison costs); projected rows/sets are copied and allocated. Indexed enforcement is a separate future optimization. |
| Design | [docs/catalog.md](../../../../catalog.md), [docs/semantics.md](../../../../semantics.md), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0016

[Lines 150–150](../../../../../src/catalog/catalog.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_constraints(const Catalog& catalog, const Database& database)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose full reference constraint validation for runtime catalog/database values. |
| inputs / outputs | Borrowed catalog and database in; no output. |
| invariants | Delegates without weakening the full-shape and enforced-constraint checks. |
| ownership | Borrows inputs; no mutation. |
| failure | Propagates invalid catalog/database and constraint-violation errors. |
| cost | Full validation scans and projected-key set construction. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0017

[Lines 151–151](../../../../../src/catalog/catalog.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_constraints(const program::Catalog& catalog, const Database& database)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose full reference constraint validation for program catalog values. |
| inputs / outputs | Borrowed program catalog and database in; no output. |
| invariants | Same constraints and row-shape rules as the runtime catalog overload. |
| ownership | Borrows inputs; no mutation. |
| failure | Propagates invalid catalog/database and constraint-violation errors. |
| cost | Full validation scans and projected-key set construction. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0019

[Lines 154–163](../../../../../src/catalog/catalog.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> bool requires_format3_impl(const CatalogView& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect catalog metadata that a legacy format-1/2 writer cannot preserve. |
| inputs / outputs | Borrowed catalog view in; Boolean out. |
| invariants | Returns true for nondefault schema version, constraints, statistics, key hints, nullable column, nonbinary collation, or fixed decimal metadata; it does not validate the catalog. |
| ownership | Borrows catalog; no mutation or retained state. |
| failure | No declared exception path beyond underlying iteration/comparison behavior. |
| cost | O(tables + columns + metadata-presence checks); no explicit allocation. |
| Design | [docs/catalog.md](../../../../catalog.md) |

## B0020

[Lines 164–164](../../../../../src/catalog/catalog.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool requires_format3(const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose format-3 metadata detection for runtime catalogs. |
| inputs / outputs | Borrowed \`Catalog\` in; Boolean out. |
| invariants | Delegates to metadata-presence scan; does not establish valid metadata or data constraints. |
| ownership | Borrows catalog; no mutation. |
| failure | No domain error is raised by this wrapper. |
| cost | O(tables + columns + metadata checks). |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0021

[Lines 165–165](../../../../../src/catalog/catalog.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool requires_format3(const program::Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose format-3 metadata detection for program catalogs. |
| inputs / outputs | Borrowed \`program::Catalog\` in; Boolean out. |
| invariants | Same metadata-presence policy as the runtime overload. |
| ownership | Borrows catalog; no mutation. |
| failure | No domain error is raised by this wrapper. |
| cost | O(tables + columns + metadata checks). |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0023

[Lines 168–174](../../../../../src/catalog/catalog.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> TableId find_table_impl(const CatalogView& catalog, std::string_view name)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an exact case-sensitive table name after validating the full catalog. |
| inputs / outputs | Borrowed catalog and name in; table index out. |
| invariants | Calls \`validate_catalog\` first; returns the first equal name in declaration order; missing names are \`unknown_table\`. |
| ownership | Borrows catalog/name; returns a scalar typed id. |
| failure | Propagates catalog errors; unknown name throws \`unknown_table\` with owned name text. |
| cost | Whole catalog validation plus O(table count) name scan; repeated calls repeat validation and lookup work. \`bind_sql\` validates once and calls this again per FROM relation, a bounded performance candidate for a prevalidated internal lookup path. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0024

[Lines 175–175](../../../../../src/catalog/catalog.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TableId find_table(const Catalog& catalog, std::string_view name)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact table lookup for runtime catalogs. |
| inputs / outputs | Borrowed catalog/name in; \`TableId\` out. |
| invariants | Delegates to the validated shared lookup. |
| ownership | Borrows inputs; returns scalar id. |
| failure | Propagates \`invalid_catalog\`, \`unsupported_collation\`, or \`unknown_table\`. |
| cost | Full metadata validation plus linear table-name scan. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0025

[Lines 176–176](../../../../../src/catalog/catalog.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TableId find_table(const program::Catalog& catalog, std::string_view name)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact table lookup for program catalogs. |
| inputs / outputs | Borrowed program catalog/name in; \`TableId\` out. |
| invariants | Delegates to the validated shared lookup. |
| ownership | Borrows inputs; returns scalar id. |
| failure | Propagates catalog errors or \`unknown_table\`. |
| cost | Full metadata validation plus linear table-name scan. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0027

[Lines 179–204](../../../../../src/catalog/catalog.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ColumnReference resolve_column(const Catalog& catalog, std::span<const RelationBinding> bindings,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a visible alias-qualified or unique unqualified column in relation bindings. |
| inputs / outputs | Borrowed catalog, relation bindings, optional qualifier, and column name in; binding index plus physical column id out. |
| invariants | Validates catalog and every binding; rejects empty/duplicate qualifiers, unknown qualifier, ambiguous visible column, and missing column. A self-join’s bindings remain distinct. |
| ownership | Borrows span/string views; returns scalar indexes. Candidate text/qualifier set are temporary owned strings. |
| failure | Invalid table binding, duplicate/unknown qualifier, ambiguity, or missing name throws the corresponding Error; catalog validation errors propagate. |
| cost | Full catalog validation, O(bindings) qualifier-set construction, then scan of visible columns; set/string allocations and diagnostic candidates on applicable paths. This public helper is not called by \`Binder\`, which keeps its own scoped name lookup. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0029

[Lines 206–210](../../../../../src/catalog/catalog.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_identity_cast(ScalarType source, ScalarType target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject representation-changing scalar casts at the catalog/type boundary. |
| inputs / outputs | Source and target scalar enums in; no output. |
| invariants | Only identical scalar types are permitted; metadata does not authorize implicit conversion. |
| ownership | Scalar values only. |
| failure | Different kinds throw \`unsupported_cast\`; \`type_name\` errors on invalid enum values propagate. |
| cost | Two type-name conversions and constant-time comparison; strings constructed only for reporting. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0030

[Lines 211–224](../../../../../src/catalog/catalog.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_identity_cast(const Column& source, const Column& target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that an identity cast preserves full column metadata. |
| inputs / outputs | Borrowed source/target columns in; no output. |
| invariants | Requires same scalar type, nullability, binary collation, valid decimal specs only on decimal columns, and identical decimal precision/scale. Identity cast cannot establish non-nullness. |
| ownership | Borrows columns; initializer-list pointers are temporary non-owning addresses. |
| failure | Throws \`unsupported_cast\`, \`unsupported_nullability\`, \`unsupported_collation\`, or \`invalid_catalog\` at the violated boundary. |
| cost | Constant number of scalar checks and at most two fixed decimal-spec checks; no row scan. |
| Design | [docs/catalog.md](../../../../catalog.md), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0031

[Lines 225–225](../../../../../src/catalog/catalog.cpp#L225); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L225-L225:sha256:bd2dbb97e992a8a5ff2da337363d7940e3e1da7837f8651bda1704075341071a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::catalog at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/code_specs/files/src/catalog/catalog.cpp.md](catalog.cpp.md), [docs/catalog.md](../../../../catalog.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |
