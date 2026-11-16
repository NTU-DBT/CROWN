# `include/crown/ir/model.hpp` — block usage map

[Source](../../../../../../include/crown/ir/model.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Define/validate query variables, atom occurrences, scopes and output metadata.

Snapshot SHA-256: `2bc7df091d4d64899f70502b4e5e5c5705520ea8c0a151270be0bc862316ae62`. 120 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/ir/model.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/ir/model.hpp#L16) | Type/record definition: enum class ScalarType |  · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../../include/crown/ir/model.hpp#L17) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../../include/crown/ir/model.hpp#L21) | Type/record definition: enum class Collation |  · [reviewed contract](#b0004) |
| [B0005 · 22–26](../../../../../../include/crown/ir/model.hpp#L22) | Type/record definition: struct DecimalSpec |  · [reviewed contract](#b0005) |
| [B0006 · 27–33](../../../../../../include/crown/ir/model.hpp#L27) | Type/record definition: struct Column |  · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../../include/crown/ir/model.hpp#L34) | Type/record definition: enum class ConstraintStatus |  · [reviewed contract](#b0007) |
| [B0008 · 35–39](../../../../../../include/crown/ir/model.hpp#L35) | Type/record definition: struct UniqueConstraint |  · [reviewed contract](#b0008) |
| [B0009 · 40–46](../../../../../../include/crown/ir/model.hpp#L40) | Type/record definition: struct ForeignKeyConstraint |  · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../../include/crown/ir/model.hpp#L47) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 48–51](../../../../../../include/crown/ir/model.hpp#L48) | Type/record definition: struct DistinctEstimate |  · [reviewed contract](#b0011) |
| [B0012 · 52–55](../../../../../../include/crown/ir/model.hpp#L52) | Type/record definition: struct TableStatistics |  · [reviewed contract](#b0012) |
| [B0013 · 56–59](../../../../../../include/crown/ir/model.hpp#L56) | Type/record definition: struct KeyHint |  · [reviewed contract](#b0013) |
| [B0014 · 60–67](../../../../../../include/crown/ir/model.hpp#L60) | Type/record definition: struct Table |  · [reviewed contract](#b0014) |
| [B0015 · 68–68](../../../../../../include/crown/ir/model.hpp#L68) | Type/record definition: struct Catalog |  · [reviewed contract](#b0015) |
| [B0016 · 69–69](../../../../../../include/crown/ir/model.hpp#L69) | Type/record definition: struct Variable |  · [reviewed contract](#b0016) |
| [B0017 · 70–70](../../../../../../include/crown/ir/model.hpp#L70) | Type/record definition: struct IgnoredColumn |  · [reviewed contract](#b0017) |
| [B0018 · 71–71](../../../../../../include/crown/ir/model.hpp#L71) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 72–72](../../../../../../include/crown/ir/model.hpp#L72) | Type/record definition: struct Atom |  · [reviewed contract](#b0019) |
| [B0020 · 73–73](../../../../../../include/crown/ir/model.hpp#L73) | Type/record definition: struct Output |  · [reviewed contract](#b0020) |
| [B0021 · 74–79](../../../../../../include/crown/ir/model.hpp#L74) | Type/record definition: struct Query |  · [reviewed contract](#b0021) |
| [B0022 · 80–80](../../../../../../include/crown/ir/model.hpp#L80) | Type/record definition: struct Database |  · [reviewed contract](#b0022) |
| [B0023 · 81–81](../../../../../../include/crown/ir/model.hpp#L81) | Type/record definition: enum class SetOperation | growth insert · [reviewed contract](#b0023) |
| [B0024 · 82–87](../../../../../../include/crown/ir/model.hpp#L82) | Type/record definition: struct PhysicalSetUpdate |  · [reviewed contract](#b0024) |
| [B0025 · 88–88](../../../../../../include/crown/ir/model.hpp#L88) | Type/record definition: struct SetDelta |  · [reviewed contract](#b0025) |
| [B0026 · 89–94](../../../../../../include/crown/ir/model.hpp#L89) | Type/record definition: struct CommittedReferenceEpoch |  · [reviewed contract](#b0026) |
| [B0027 · 95–101](../../../../../../include/crown/ir/model.hpp#L95) | Type/record definition: struct Document |  · [reviewed contract](#b0027) |
| [B0028 · 102–108](../../../../../../include/crown/ir/model.hpp#L102) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Stable FNV-1a over tagged, length-delimited values and fixed little-endian · [reviewed contract](#b0028) |
| [B0029 · 109–111](../../../../../../include/crown/ir/model.hpp#L109) | Type/record definition: struct ValueHash | returns static_cast&lt;std::size_t&gt;(value_hash(value)) · [reviewed contract](#b0029) |
| [B0030 · 112–114](../../../../../../include/crown/ir/model.hpp#L112) | Type/record definition: struct RowHash | returns static_cast&lt;std::size_t&gt;(row_hash(row)) · [reviewed contract](#b0030) |
| [B0031 · 115–120](../../../../../../include/crown/ir/model.hpp#L115) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown · [reviewed contract](#b0031) |

## B0001

[Lines 1–15](../../../../../../include/crown/ir/model.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace program {struct Catalog;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare the immutable native catalog view used by validator overloads without including its full model. |
| inputs / outputs | \`program::Catalog\` is incomplete here; later \`validate_row\` and \`validate_database\` declarations accept it by const reference. |
| invariants | This declaration defines no catalog fields, owner, or conversion and cannot establish native catalog validity. |
| ownership | No object is stored or owned through the forward declaration; callers must provide a live catalog defined by the program model. |
| failure | No runtime check occurs at the declaration. Validator implementations report invalid table/row/database values through \`Error\`. |
| cost | No runtime storage or work; the declared validation overloads traverse supplied data when called. |
| Design | [include/crown/ir/model.hpp §forward declaration and validator overloads](../../../../../../include/crown/ir/model.hpp), [include/crown/ir/program_model.hpp §native Catalog view](../../../../../../include/crown/ir/program_model.hpp), [src/ir/model.cpp §catalog-view validation](../../../../../../src/ir/model.cpp) |

## B0002

[Lines 16–16](../../../../../../include/crown/ir/model.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ScalarType { int64, string, boolean, date, decimal };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag the core scalar value domains. |
| inputs / outputs | Selects int64, string, boolean, date, or decimal, matching the alternatives in Value. |
| invariants | The enum names kinds; conversion and validation are separate functions. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Scalar/tag carriers add no dynamic allocation. |
| Design | [include/crown/ir/model.hpp §L16-16](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L19-35](../../../../../../src/ir/model.cpp) |

## B0003

[Lines 17–20](../../../../../../include/crown/ir/model.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Value = std::variant<std::int64_t, std::string, bool, Date, Decimal>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the owning non-null scalar variant used by reference rows and query literals. |
| inputs / outputs | \`Value\` stores exactly one int64, string, bool, \`Date\`, or exact \`Decimal\`; neighboring aliases define an owning \`Row\` vector and set-valued \`Relation\`. |
| invariants | SQL NULL is not an alternative. Column/type/domain checks are separate; exact typed equality determines row membership. |
| ownership | The variant and its contained string own their storage; rows and relations own copies of values/rows. |
| failure | The alias itself does not validate scalar domain or column type; scalar constructors/parsers and \`validate_row\` enforce those constraints. |
| cost | The alias adds no wrapper beyond \`std::variant\`; row/relation copying and ordered set comparison depend on contained scalar payload. |
| Design | [include/crown/ir/model.hpp §Value/Row/Relation aliases](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §type_of and validation](../../../../../../src/ir/model.cpp), [docs/semantics.md §typed values](../../../../../semantics.md), [docs/scalars.md §scalar domains](../../../../../scalars.md) |

## B0004

[Lines 21–21](../../../../../../include/crown/ir/model.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Collation { binary };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the column string comparison mode. |
| inputs / outputs | Currently exposes binary, which is Column’s default. |
| invariants | Catalog validation accepts binary only. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Scalar/tag carriers add no dynamic allocation. |
| Design | [include/crown/ir/model.hpp §L21-21](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L52-70](../../../../../../src/catalog/catalog.cpp) |

## B0005

[Lines 22–26](../../../../../../include/crown/ir/model.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DecimalSpec {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe decimal precision and scale. |
| inputs / outputs | Carries precision and scale and has defaulted comparison. |
| invariants | Catalog validation requires precision 1..38 and scale &lt;= precision; decimal_fits checks values against it. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Two scalar fields; no dynamic allocation. Decimal checking work is separate. |
| Design | [include/crown/ir/model.hpp §L22-26](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L29-32](../../../../../../src/catalog/catalog.cpp), [src/ir/model.cpp §L104-107,116-125](../../../../../../src/ir/model.cpp) |

## B0006

[Lines 27–33](../../../../../../include/crown/ir/model.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Column {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one named schema column. |
| inputs / outputs | Carries name, scalar type, nullable flag, collation and optional decimal specification. |
| invariants | Defaults to non-null/binary; direct CQ validation separately rejects nullable core columns. |
| ownership | Owns its column-name string; type/nullable/collation/decimal fields are inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying the name may allocate and copies its bytes; other fields have fixed cost. |
| Design | [include/crown/ir/model.hpp §L27-33](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L52-70](../../../../../../src/catalog/catalog.cpp), [src/ir/model.cpp §L75-85](../../../../../../src/ir/model.cpp) |

## B0007

[Lines 34–34](../../../../../../include/crown/ir/model.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ConstraintStatus { enforced, untrusted };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark a constraint declaration enforced or untrusted. |
| inputs / outputs | Used by unique and foreign-key declarations; defaults to untrusted there. |
| invariants | This status alone does not establish data compliance; validate_constraints performs checks only for enforced constraints. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Scalar/tag carriers add no dynamic allocation. |
| Design | [include/crown/ir/model.hpp §L34-34](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L26-28,117-148](../../../../../../src/catalog/catalog.cpp) |

## B0008

[Lines 35–39](../../../../../../include/crown/ir/model.hpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct UniqueConstraint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a named uniqueness declaration over table columns. |
| inputs / outputs | Carries name, ColumnId vector and status. |
| invariants | Status defaults to untrusted; catalog validation checks name/status/column IDs; database checking scans projected keys only when enforced. |
| ownership | Owns the constraint name and ordered ColumnId vector; status is inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying costs name bytes plus the column-ID array and may allocate; enforcement scans are separate. |
| Design | [include/crown/ir/model.hpp §L35-39](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L71-78,117-135](../../../../../../src/catalog/catalog.cpp) |

## B0009

[Lines 40–46](../../../../../../include/crown/ir/model.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ForeignKeyConstraint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe child columns and referenced table/columns. |
| inputs / outputs | Carries name, child columns, referenced TableId/columns and status. |
| invariants | Catalog checks referenced IDs, paired arity/types and column sets; only an enforced FK requires an enforced unique target. Database/source compliance is separately checked; untrusted declarations cannot authorize an elimination. |
| ownership | Owns name and both column-ID vectors; referenced table and status are inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying costs name bytes and both ID arrays and may allocate; catalog/data checks are additional. |
| Design | [include/crown/ir/model.hpp §L40-46](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L89-109,136-145](../../../../../../src/catalog/catalog.cpp) |

## B0010

[Lines 47–47](../../../../../../include/crown/ir/model.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Constraint = std::variant<UniqueConstraint, ForeignKeyConstraint>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a declared catalog constraint as either unique-key or foreign-key metadata. |
| inputs / outputs | The variant holds a \`UniqueConstraint\` or \`ForeignKeyConstraint\`, each with columns and an explicit status. |
| invariants | \`enforced\` and \`untrusted\` are metadata states; only validation against an actual database establishes whether enforced constraints hold for its rows. |
| ownership | Constraint names and column lists are ordinary owning strings/vectors in the catalog. |
| failure | The alias does no reference/type/status validation; catalog and database validation report invalid metadata or violations separately. |
| cost | One variant plus its selected owning metadata; constraint validation cost depends on catalog and row collections. |
| Design | [include/crown/ir/model.hpp §constraint alternatives and alias](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §constraint validation](../../../../../../src/catalog/catalog.cpp), [docs/catalog.md §constraints](../../../../../catalog.md) |

## B0011

[Lines 48–51](../../../../../../include/crown/ir/model.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DistinctEstimate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a distinct-count estimate for a column set. |
| inputs / outputs | Pairs ColumnIds with a uint64 estimate. |
| invariants | It is planner/statistics metadata, not an enforced cardinality fact; catalog validation checks column IDs and duplicate column sets. |
| ownership | Owns its ColumnId vector; the estimate is an inline advisory count. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Building/copying the column list can allocate and visits its IDs; the estimate itself is fixed work. |
| Design | [include/crown/ir/model.hpp §L48-51](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L79-83](../../../../../../src/catalog/catalog.cpp) |

## B0012

[Lines 52–55](../../../../../../include/crown/ir/model.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect optional row count and distinct-count estimates. |
| inputs / outputs | Provides optional row_count and vector of DistinctEstimate. |
| invariants | Statistics are estimates; catalog validation checks referenced columns, not truth against database contents. |
| ownership | Owns its estimate vector and every nested column-ID vector; optional row count is inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying can allocate across the estimate array and nested ID arrays; no data census occurs in this record. |
| Design | [include/crown/ir/model.hpp §L52-55](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L79-83](../../../../../../src/catalog/catalog.cpp) |

## B0013

[Lines 56–59](../../../../../../include/crown/ir/model.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyHint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a planner key hint and its reason. |
| inputs / outputs | Provides ColumnIds plus reason text. |
| invariants | A hint is not an enforced uniqueness constraint; catalog validation checks valid unique IDs and a nonempty reason. |
| ownership | Owns its column-ID vector and reason string; does not retain a validated constraint. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying can allocate and touches ID and reason bytes; consuming the hint is separate. |
| Design | [include/crown/ir/model.hpp §L56-59](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L84-87](../../../../../../src/catalog/catalog.cpp) |

## B0014

[Lines 60–67](../../../../../../include/crown/ir/model.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Table {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one named physical schema and its metadata. |
| inputs / outputs | Groups columns, source schema version, constraints, statistics and key hints. |
| invariants | Version defaults to 1; Catalog validation checks the table and nested metadata. |
| ownership | Owns its name, columns, constraints, statistics and hints recursively through ordinary STL values. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying can allocate through every nested array/name; cost follows metadata and text size, not a fixed tag. |
| Design | [include/crown/ir/model.hpp §L60-67](../../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp §L52-110](../../../../../../src/catalog/catalog.cpp) |

## B0015

[Lines 68–68](../../../../../../include/crown/ir/model.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Catalog { std::uint64_t version = 1; std::vector<Table> tables; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a versioned ordered table catalog. |
| inputs / outputs | Table positions are addressed by TableId. |
| invariants | Version defaults to 1; Catalog validation checks positive version, names and nested references; ID wrappers do not range-check. |
| ownership | Owns the ordered Table vector and all recursively owning schema metadata; IDs are positional labels. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | A populated copy allocates/copies table and nested metadata/text; immutable native import is another explicit operation. |
| Design | [include/crown/ir/model.hpp §L68-68](../../../../../../include/crown/ir/model.hpp), [include/crown/ir/ids.hpp §L8-10](../../../../../../include/crown/ir/ids.hpp), [src/catalog/catalog.cpp §L52-114](../../../../../../src/catalog/catalog.cpp) |

## B0016

[Lines 69–69](../../../../../../include/crown/ir/model.hpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Variable { std::string name; ScalarType type; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a named core query variable and scalar type. |
| inputs / outputs | VariableId refers to its position in Query::variables. |
| invariants | Query validation checks unique names, known types, ID bounds and type compatibility. |
| ownership | Owns its variable-name string; ScalarType is inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying the name may allocate and touches name bytes; no symbol lookup happens inside the carrier. |
| Design | [include/crown/ir/model.hpp §L69-69](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L86-113](../../../../../../src/ir/model.cpp) |

## B0017

[Lines 70–70](../../../../../../include/crown/ir/model.hpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IgnoredColumn {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark an atom term position as intentionally ignored. |
| inputs / outputs | Provides an empty Term alternative alongside variable IDs and literal Values. |
| invariants | Carries no identity/value; enclosing query validation checks atom arity and other term consistency. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Scalar/tag carriers add no dynamic allocation. |
| Design | [include/crown/ir/model.hpp §L70-70](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L93-110](../../../../../../src/ir/model.cpp) |

## B0018

[Lines 71–71](../../../../../../include/crown/ir/model.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Term = std::variant<VariableId, Value, IgnoredColumn>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent the three source-level term forms in an ordinary conjunctive-query atom. |
| inputs / outputs | \`Term\` contains a variable ID, owning typed constant \`Value\`, or \`IgnoredColumn\` marker. |
| invariants | The variant expresses syntax only; \`validate\` checks ID bounds, column arity/type compatibility, and variable binding. Ignored cells remain part of physical row identity. |
| ownership | A variable ID/marker is inline; a literal owns its scalar payload as part of the variant and atom term vector. |
| failure | No validation is performed by this alias; malformed indices/types fail when the query is validated. |
| cost | Variant storage is inline; copying/string-containing literals incurs contained-value copy work. |
| Design | [include/crown/ir/model.hpp §Term and Atom](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §validate](../../../../../../src/ir/model.cpp), [docs/semantics.md §occurrences and values](../../../../../semantics.md) |

## B0019

[Lines 72–72](../../../../../../include/crown/ir/model.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Atom { std::string occurrence; TableId table; std::vector<Term> terms; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a table occurrence and one term per physical column. |
| inputs / outputs | Carries occurrence name, TableId and ordered Term vector. |
| invariants | Query validation checks occurrence uniqueness, table bounds, arity, variable bounds/types and literal type/decimal fit. |
| ownership | Owns occurrence text and ordered Term vector, including any owning literal string/Decimal payload. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying may allocate for occurrence, terms and deep literal payload; validation/join work is separate. |
| Design | [include/crown/ir/model.hpp §L72-72](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L91-110](../../../../../../src/ir/model.cpp) |

## B0020

[Lines 73–73](../../../../../../include/crown/ir/model.hpp#L73); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Output { VariableId variable; std::string alias; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a query variable and assign its output alias. |
| inputs / outputs | Participates in the ordered Query head. |
| invariants | The ID is accepted only when bound by the body; validation is on the enclosing query. |
| ownership | Owns alias text; VariableId is an inline positional label. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Copying/populating alias text may allocate; copying the ID is fixed work. |
| Design | [include/crown/ir/model.hpp §L73-73](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L112-113](../../../../../../src/ir/model.cpp) |

## B0021

[Lines 74–79](../../../../../../include/crown/ir/model.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Query {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the core query variable, atom and head lists. |
| inputs / outputs | The ordered head is the output; contradiction is a stored marker. |
| invariants | The contradiction flag defines an empty source query when set; it is not a proof that an otherwise unmarked body is contradictory. Enclosing validation checks names/IDs/types/arity and variable bindings. No minimum-height or execution authority follows from the record. |
| ownership | Owns variable, atom and ordered output vectors, with nested names/terms/literal values. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying visits and may allocate for complete metadata/text/literals; the contradiction flag is fixed size. |
| Design | [include/crown/ir/model.hpp §L74-79](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L75-113](../../../../../../src/ir/model.cpp) |

## B0022

[Lines 80–80](../../../../../../include/crown/ir/model.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Database { std::vector<Relation> tables; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent catalog tables as set-valued row relations. |
| inputs / outputs | Relation vector positions align with Catalog::tables. |
| invariants | The aggregate does not check table count, row shape or constraints; validate_database delegates those checks. |
| ownership | Owns the table vector, ordered set nodes, row arrays and each owning scalar payload. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Construction/insertion/copy can allocate per table/set node/row/payload; set insertion also performs ordered row/scalar comparisons. |
| Design | [include/crown/ir/model.hpp §L80-80](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L116-135](../../../../../../src/ir/model.cpp) |

## B0023

[Lines 81–81](../../../../../../include/crown/ir/model.hpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SetOperation { insert, erase };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag a physical set event as insert or erase. |
| inputs / outputs | Selected by PhysicalSetUpdate::operation. |
| invariants | The tag alone does not define duplicate/missing-row transition behavior. |
| ownership | No dynamic ownership is introduced by this type. |
| failure | Construction/copy of these inline fields performs no admission; catalog/query/update validators enforce the applicable domain. |
| cost | Scalar/tag carriers add no dynamic allocation. |
| Design | [include/crown/ir/model.hpp §L81-81](../../../../../../include/crown/ir/model.hpp), [include/crown/runtime/physical.hpp §L146-147](../../../../../../include/crown/runtime/physical.hpp) |

## B0024

[Lines 82–87](../../../../../../include/crown/ir/model.hpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalSetUpdate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one sequence-tagged full-row table event. |
| inputs / outputs | Fields are sequence, TableId, insert/erase operation and Row values. |
| invariants | The record does not enforce ordering or state transition; validate_row checks table, arity, scalar type and decimal fit. |
| ownership | Owns the complete Row and its owning scalar payload; sequence/table/sign are inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying can allocate for the row and deep string/Decimal values; retaining a public DTO is not a native-account admission. |
| Design | [include/crown/ir/model.hpp §L82-87](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L116-130](../../../../../../src/ir/model.cpp), [include/crown/runtime/physical.hpp §L146-147](../../../../../../include/crown/runtime/physical.hpp) |

## B0025

[Lines 88–88](../../../../../../include/crown/ir/model.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SetDelta { Relation added; Relation removed; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry added and removed reference result relations. |
| inputs / outputs | Provides two sets of Row values. |
| invariants | No disjointness/current-relation invariant is enforced by the aggregate. |
| ownership | Owns added/removed set nodes, rows and scalar payload independently of the runtime. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Populating/copying can allocate across both relations; ordered insertion/comparison and deep row bytes are real costs. |
| Design | [include/crown/ir/model.hpp §L88-88](../../../../../../include/crown/ir/model.hpp), [tests/reference/evaluator.cpp §L56-75](../../../../../../tests/reference/evaluator.cpp) |

## B0026

[Lines 89–94](../../../../../../include/crown/ir/model.hpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CommittedReferenceEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one reference evaluation result epoch. |
| inputs / outputs | Carries sequence, input_changed, current result and SetDelta. |
| invariants | It is a result carrier; the evaluator constructs its contents and the type does not verify consistency. |
| ownership | Owns complete current/added/removed reference relations; flags/sequence are inline. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Constructing/copying a result can allocate/copy full result and delta populations, not merely a constant epoch descriptor. |
| Design | [include/crown/ir/model.hpp §L89-94](../../../../../../include/crown/ir/model.hpp), [tests/reference/evaluator.cpp §L56-75](../../../../../../tests/reference/evaluator.cpp) |

## B0027

[Lines 95–101](../../../../../../include/crown/ir/model.hpp#L95); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Document {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle schema, query, initial database and input updates. |
| inputs / outputs | Includes document schema_version, defaulting to 1. |
| invariants | Reader/upgrade and validation boundaries own input consistency checks. |
| ownership | Owns catalog, query, initial relations and update DTOs recursively; no runtime owner/account is retained. |
| failure | Populated construction/copy can throw std::bad_alloc or a member-copy error; ordinary member RAII cleans partial construction. The carrier does not validate metadata, row shape, source sequence or relational constraints and does not automatically charge a native query account. |
| cost | Building/copying can allocate for all schema/query/data/update populations; parsing and semantic validation are additional. |
| Design | [include/crown/ir/model.hpp §L95-101](../../../../../../include/crown/ir/model.hpp), [include/crown/io/document.hpp §L13-16](../../../../../../include/crown/io/document.hpp), [src/ir/model.cpp §L75-135](../../../../../../src/ir/model.cpp) |

## B0028

[Lines 102–108](../../../../../../include/crown/ir/model.hpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ScalarType type_of(const Value& value);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare scalar type/name conversion and stable hash helpers for the owning \`Value\` and \`Row\` model. |
| inputs / outputs | \`type_of\` maps one \`Value\` to \`ScalarType\`; \`type_name\` maps one type enum to an owning name string. \`value_hash\` hashes one scalar and \`row_hash\` hashes the ordered cells of one row. |
| invariants | The documented FNV-1a hashes are stable bucket hashes, not cryptographic identities. They preserve scalar tags and row order; they do not validate query, row-domain, or database constraints. |
| ownership | All arguments are borrowed const references; helpers return scalar values or hashes and retain no state. |
| failure | \`type_name\` rejects an unknown scalar enum with \`Error\`; invalid/valueless \`Value\` paths reach the model error guard. Malformed query/row/database failures belong to the separate validation functions. |
| cost | Type conversion dispatches on one variant tag; \`type_name\` returns a string. Hashing visits each value and text byte, and \`row_hash\` also visits row order/length; Decimal hashing renders canonical text and may allocate. No catalog or constraint scan occurs here. |
| Design | [include/crown/ir/model.hpp §type/hash declarations](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §type and FNV hash implementations](../../../../../../src/ir/model.cpp), [docs/scalars.md §stable typed hashes](../../../../../scalars.md) |

## B0029

[Lines 109–111](../../../../../../include/crown/ir/model.hpp#L109); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ValueHash {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt value_hash to callable hash containers. |
| inputs / outputs | Returns value_hash(value) cast to size_t. |
| invariants | Uses the documented tagged, length-delimited FNV-1a utility; it is not cryptographic identity or equality. |
| ownership | Stateless functor; the input remains borrowed. Hashing a public Decimal temporarily owns its rendered string. |
| failure | Decimal rendering can allocate/throw; a valueless scalar variant raises invalid_cq. This operator is not noexcept or a validator. |
| cost | Visits value/row fields and string bytes. Public Decimal hashing calls Decimal::to_string and can allocate for canonical text; this is distinct from the native inline-scalar hash path. |
| Design | [include/crown/ir/model.hpp §L109-111](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L38-67](../../../../../../src/ir/model.cpp) |

## B0030

[Lines 112–114](../../../../../../include/crown/ir/model.hpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowHash {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt row_hash to callable hash containers. |
| inputs / outputs | Returns row_hash(row) cast to size_t. |
| invariants | Hashes the row size and tagged cell values; collisions remain possible and equality is separate. |
| ownership | Stateless functor; the input remains borrowed. Hashing a public Decimal temporarily owns its rendered string. |
| failure | Decimal rendering can allocate/throw; a valueless scalar variant raises invalid_cq. This operator is not noexcept or a validator. |
| cost | Visits value/row fields and string bytes. Public Decimal hashing calls Decimal::to_string and can allocate for canonical text; this is distinct from the native inline-scalar hash path. |
| Design | [include/crown/ir/model.hpp §L112-114](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §L38-73](../../../../../../src/ir/model.cpp) |

## B0031

[Lines 115–120](../../../../../../include/crown/ir/model.hpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const Catalog& catalog, const Query& query);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the owning/native-view overloads that validate CQ structure, row domains, and database constraints. |
| inputs / outputs | \`validate\` checks a catalog/query; \`validate_row\` checks one table row; \`validate_database\` checks all database constraints for either catalog representation. |
| invariants | Direct core validation requires non-null catalog columns and checks IDs, term arity/types, bound variables, and head references. Row checks are shape/type/decimal checks; constraint checks are database-wide. |
| ownership | Functions borrow inputs and return no owned object. They do not normalize frontend SQL or mint checked proof authority. |
| failure | Invalid structure, row shape/type/domain, catalog metadata, or collection constraints throw \`Error\` with a failure code. |
| cost | Query validation scales with catalog/query terms; row validation with cell count; database validation traverses row/key collections and declared constraints. |
| Design | [include/crown/ir/model.hpp §validation overloads](../../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp §validate and validate_row](../../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp §validate_constraints](../../../../../../src/catalog/catalog.cpp), [docs/semantics.md §validation boundary](../../../../../semantics.md) |
