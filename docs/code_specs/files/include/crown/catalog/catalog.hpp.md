# `include/crown/catalog/catalog.hpp` — block usage map

[Source](../../../../../../include/crown/catalog/catalog.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Validate schema, table/column identity and declared integrity constraints before query or data admission.

Snapshot SHA-256: `b18e5bcff598810d04f2d3e6e956870de7a4326ef0ddc20485bd7469744de068`. 39 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [catalog](../../../../subsystem_contracts.md#catalog). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/catalog.md](../../../../../catalog.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/physical_runtime.md](../../../../../physical_runtime.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../../include/crown/catalog/catalog.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Metadata validation accepts nullable source declarations. A direct-CQ core · [reviewed contract](#b0001) |
| [B0002 · 19–22](../../../../../../include/crown/catalog/catalog.hpp#L19) | Type/record definition: struct RelationBinding |  · [reviewed contract](#b0002) |
| [B0003 · 23–27](../../../../../../include/crown/catalog/catalog.hpp#L23) | Type/record definition: struct ColumnReference |  · [reviewed contract](#b0003) |
| [B0004 · 28–39](../../../../../../include/crown/catalog/catalog.hpp#L28) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Qualifiers are the visible aliases. Self-join bindings remain distinct even · [reviewed contract](#b0004) |

## B0001

[Lines 1–18](../../../../../../include/crown/catalog/catalog.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_catalog(const Catalog& catalog);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare metadata/data validation, format selection, and exact decimal representability APIs. |
| inputs / outputs | Catalog and database references in API calls; decimal value/specification in for exact-fit query; format metadata scan returns bool. |
| invariants | Metadata validation allows nullable source declarations; core SQL normalization has a separate nullable-source admission rule. Constraint validation checks actual database rows. |
| ownership | All APIs borrow their catalog/database/value inputs and retain no state. |
| failure | Each API exposes its implementation’s typed Error failures; declarations do not catch or convert them. |
| cost | Metadata APIs scan declared schema; data constraint validation deliberately full-scans rows and builds projected-key sets; \`decimal_fits\` formats one bounded decimal. |
| Design | [docs/catalog.md](../../../../../catalog.md), [src/catalog/catalog.cpp](../../../../../../src/catalog/catalog.cpp) |

## B0002

[Lines 19–22](../../../../../../include/crown/catalog/catalog.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RelationBinding
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one visible SQL relation qualifier and its physical table id. |
| inputs / outputs | Table id plus owned qualifier string. |
| invariants | \`resolve_column\` requires table id in range and qualifier nonempty/unique within the visible binding set; the record itself is unchecked. |
| ownership | Qualifier string owns its bytes; table id is a scalar. |
| failure | No aggregate validation at construction; lookup reports invalid binding/duplicate alias. |
| cost | One string plus scalar; fixed record overhead. |
| Design | [docs/catalog.md](../../../../../catalog.md), [src/catalog/catalog.cpp](../../../../../../src/catalog/catalog.cpp) |

## B0003

[Lines 23–27](../../../../../../include/crown/catalog/catalog.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColumnReference
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a physical column through its visible relation-binding index. |
| inputs / outputs | Binding index and \`ColumnId\`; defaulted comparison. |
| invariants | Binding index addresses the caller’s \`RelationBinding\` span; \`ColumnId\` addresses the referenced table. The record does not retain the span/catalog. |
| ownership | Scalar indexes only. |
| failure | No construction checks; caller must use a matching live binding/catalog snapshot. |
| cost | Fixed-size comparable value. |
| Design | [docs/catalog.md](../../../../../catalog.md), [src/catalog/catalog.cpp](../../../../../../src/catalog/catalog.cpp) |

## B0004

[Lines 28–39](../../../../../../include/crown/catalog/catalog.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] TableId find_table(const Catalog& catalog, std::string_view name);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare exact table lookup, visible-column resolution, and identity-cast checks. |
| inputs / outputs | Borrowed runtime/program catalog and name; optional qualifier plus bindings; source/target scalar or column metadata. |
| invariants | Table/column names are exact and case-sensitive; explicit aliases define visible qualifiers, self-join positions remain distinct, and only full identity casts are admitted. |
| ownership | All views/spans are borrowed only during the call; results are scalar IDs/references. |
| failure | Unknown/ambiguous names, invalid bindings, incompatible type/nullability/collation/decimal metadata are typed errors. |
| cost | Table lookup includes catalog validation; column lookup includes validation and visible-column scan; cast checks are fixed metadata work. |
| Design | [docs/catalog.md](../../../../../catalog.md), [src/catalog/catalog.cpp](../../../../../../src/catalog/catalog.cpp) |
