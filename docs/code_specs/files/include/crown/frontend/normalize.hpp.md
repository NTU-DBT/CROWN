# `include/crown/frontend/normalize.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/normalize.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ.

Snapshot SHA-256: `64a7237d3cf2f7ea44c6157e4e29fcb242a6a5338414efd9215ae251d63461f5`. 64 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/frontend/normalize.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // NULL stays outside the classical core. · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../../include/crown/frontend/normalize.hpp#L9) | Type/record definition: struct NormalizeLimits | source comment (unverified): // Counts selected compiler steps; catalog validation, copies and allocations · [reviewed contract](#b0002) |
| [B0003 · 10–16](../../../../../../include/crown/frontend/normalize.hpp#L10) | Type/record definition: struct NormalizeOptions | source comment (unverified): // Parameter specialization is part of this normalized program's identity. · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../../include/crown/frontend/normalize.hpp#L17) | Type/record definition: struct AdapterProjection |  · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../../include/crown/frontend/normalize.hpp#L18) | Type/record definition: struct ColumnEquality |  · [reviewed contract](#b0005) |
| [B0006 · 19–19](../../../../../../include/crown/frontend/normalize.hpp#L19) | Type/record definition: struct ColumnConstant |  · [reviewed contract](#b0006) |
| [B0007 · 20–31](../../../../../../include/crown/frontend/normalize.hpp#L20) | Type/record definition: struct OccurrenceAdapter | source comment (unverified): // Topologically ordered resolved expressions needed by this adapter. · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../../include/crown/frontend/normalize.hpp#L32) | Type/record definition: struct CoreOutput |  · [reviewed contract](#b0008) |
| [B0009 · 33–33](../../../../../../include/crown/frontend/normalize.hpp#L33) | Type/record definition: struct ConstantOutput |  · [reviewed contract](#b0009) |
| [B0010 · 34–38](../../../../../../include/crown/frontend/normalize.hpp#L34) | Type/record definition: struct NormalizedOutput |  · [reviewed contract](#b0010) |
| [B0011 · 39–53](../../../../../../include/crown/frontend/normalize.hpp#L39) | Type/record definition: struct NormalizedSql | source comment (unverified): // Query-wide folded values, including SQL NULL. Nonconstant slots also hold · [reviewed contract](#b0011) |
| [B0012 · 54–64](../../../../../../include/crown/frontend/normalize.hpp#L54) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Equality normalization and executable input adapters, before structural · [reviewed contract](#b0012) |

## B0001

[Lines 1–8](../../../../../../include/crown/frontend/normalize.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SqlValue = std::optional<Value>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a nullable SQL scalar at the frontend boundary without adding NULL to the classical core value type. |
| inputs / outputs | \`SqlValue\` is \`optional&lt;Value&gt;\`; a disengaged value denotes SQL NULL in parameter and normalized-value slots. |
| invariants | \`Value\` remains the non-null scalar variant. NULL-aware SQL evaluation/output rules are handled by normalization, not by this alias. |
| ownership | A present \`Value\` owns its scalar payload, including string bytes; the optional owns its contained value. |
| failure | The alias accepts empty or any \`Value\` regardless of SQL type/domain; binding/normalization and catalog checks perform those validations. |
| cost | No separate representation wrapper is added beyond \`optional\` and \`Value\`; copying a present string or decimal follows its payload type. |
| Design | [include/crown/frontend/normalize.hpp §SqlValue alias](../../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp §parameter and constant specialization](../../../../../../src/frontend/normalize.cpp), [docs/sql_normalization.md §NULLs](../../../../../sql_normalization.md), [docs/scalars.md §typed values](../../../../../scalars.md) |

## B0002

[Lines 9–9](../../../../../../include/crown/frontend/normalize.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizeLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the selected-step normalization allowance. |
| inputs / outputs | Optional uint64 work_limit defaults to one million; nullopt removes the configured finite cap. |
| invariants | Counter overflow still rejects; allowance is not a total CPU or allocation bound. |
| ownership | Value-owned options metadata. |
| failure | Admission fails before the next selected charged step. |
| cost | Fixed metadata; underlying compiler work includes uncharged copies/validation. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0003

[Lines 10–16](../../../../../../include/crown/frontend/normalize.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizeOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify exact parameter specialization, work allowance and program format. |
| inputs / outputs | One optional Value per declared parameter; schema defaults to2. |
| invariants | Disengaged parameter value is SQL NULL, never an unbound hole; accepted formats1/2 are checked at normalize_sql. |
| ownership | Owns parameter values and copies into the normalized program. |
| failure | Arity/type/nullability/version errors are reported at normalization boundary. |
| cost | Parameter payload copies plus fixed option metadata; no retained caller reference. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0004

[Lines 17–17](../../../../../../include/crown/frontend/normalize.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdapterProjection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one resolved expression for a core atom variable. |
| inputs / outputs | VariableId/expression ID pair in ordered adapter projection. |
| invariants | Variable and expression IDs belong to this normalized program. |
| ownership | Stores IDs only. |
| failure | Program construction/replay validates coherence; not a self-validating descriptor. |
| cost | Fixed pair storage; actual cell evaluation/copy happens in adapt_row. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0005

[Lines 18–18](../../../../../../include/crown/frontend/normalize.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColumnEquality {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard two physical columns merged into one occurrence variable. |
| inputs / outputs | Left/right ColumnIds within one full physical row. |
| invariants | Equal core variable never permits unequal physical repeated columns. |
| ownership | Stores indices only. |
| failure | Row checking evaluates this guard before local program output. |
| cost | Fixed metadata; comparison visits actual scalar payload as needed. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0006

[Lines 19–19](../../../../../../include/crown/frontend/normalize.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColumnConstant {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a grounded equality-class value as an input guard. |
| inputs / outputs | Physical column ID and exact Value. |
| invariants | Format2 fixed classes remain guarded even when absent from core/head. |
| ownership | Owns the constant payload. |
| failure | Invalid artifacts are rejected by coherent program construction/replay. |
| cost | Value storage/copy follows payload size; no implicit numeric conversion. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0007

[Lines 20–31](../../../../../../include/crown/frontend/normalize.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceAdapter {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one physical occurrence's local filter and projection. |
| inputs / outputs | Base/occurrence IDs, guard lists, optional column classes, projection and topological program IDs. |
| invariants | Occurrence identity survives same-table aliases; only local expressions are executable here. |
| ownership | Owns vectors/constants; IDs refer into its owning NormalizedSql. |
| failure | Requires producer/replay coherence; adapt_row validates incoming base row and guards. |
| cost | Descriptor construction/copy allocates; applying it also copies query-wide constant scratch. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0008

[Lines 32–32](../../../../../../include/crown/frontend/normalize.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CoreOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify one position in a classical result row. |
| inputs / outputs | Zero-based output column position. |
| invariants | Position is in query.core.head, including repeated positions as emitted. |
| ownership | Index only. |
| failure | Mapping uses bounds-checked core access. |
| cost | Fixed metadata; selected Value copying is done by mapper. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0009

[Lines 33–33](../../../../../../include/crown/frontend/normalize.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstantOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a non-NULL specialized SQL output value. |
| inputs / outputs | Exact Value, separate from core variables. |
| invariants | SQL NULL outputs are rejected before this descriptor is emitted. |
| ownership | Owns scalar/string/decimal payload. |
| failure | Copy allocation may fail during program/result construction. |
| cost | Storage/copy scales with owned payload bytes. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0010

[Lines 34–38](../../../../../../include/crown/frontend/normalize.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizedOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve one ordered SQL result column's name, type and source. |
| inputs / outputs | Name/SqlType plus core-position or constant descriptor. |
| invariants | Select-list order, names and repeated outputs survive equality merging. |
| ownership | Owns label and constant payload, stores core index by value. |
| failure | Must be coherent with normalized head and non-null result boundary. |
| cost | Name/value copies allocate as needed; row mapping visits every descriptor. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0011

[Lines 39–53](../../../../../../include/crown/frontend/normalize.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizedSql {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the specialized frontend artifact before structural admission. |
| inputs / outputs | Binding, parameters/constants, core/catalog, adapters/routes/output mapping and work/format metadata. |
| invariants | All occurrence atoms remain; core has no NULL; artifact alone proves neither admissibility nor maintained runtime execution. |
| ownership | Owns ordinary vectors/strings/maps through members; no live parser or native query account is retained. |
| failure | Use producer/complete reader for coherence; mutable public fields are not individually self-validating. |
| cost | Deep artifact copies include full binding/catalog/source and constant values; selected work is separate from byte/RSS budgets. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0012

[Lines 54–64](../../../../../../include/crown/frontend/normalize.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SqlNormalizeResult = std::variant<NormalizedSql, BindingDiagnostic>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose normalization success/failure and the row/result mapping operations. |
| inputs / outputs | \`normalize_sql\` consumes a \`BoundSql\` plus options and returns \`NormalizedSql\` or a phase-tagged diagnostic; \`adapt_row\` filters/projects a full physical row; \`map_sql_result\` restores ordered SQL outputs or EXISTS. |
| invariants | Normalization only admits schema versions 1 and 2 and builds a direct equality CQ with local adapters. It does not perform structural admission or start execution. |
| ownership | The normalized success owns a copy of its binding and all query/adapter/output vectors. Row and result mapping allocate returned ordinary rows/relations. |
| failure | Normalizer \`Failure\` becomes a diagnostic; unsupported schema versions and other errors may throw. \`adapt_row\` validates physical row shape/domain and may throw on malformed program contracts. |
| cost | The normalization work counter covers selected compiler steps, not catalog validation, copies, ordinary allocations, or elapsed time. \`adapt_row\` copies query-wide constant slots for each call. |
| Design | [include/crown/frontend/normalize.hpp §result and functions](../../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp §normalize_sql/adapt_row/map_sql_result](../../../../../../src/frontend/normalize.cpp), [docs/sql_normalization.md §implementation and cost](../../../../../sql_normalization.md) |
