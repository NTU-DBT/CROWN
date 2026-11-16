# `src/planner/compiled_source.hpp` — block usage map

[Source](../../../../../src/planner/compiled_source.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `6213656b2f8b2e63d756f988068e0667f838235f9bc23ecb0cab9279e1eac2f5`. 102 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/compiled_source.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Compile-time positional DTO map. Keep every fields count/order aligned · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../src/planner/compiled_source.hpp#L14) | Type/record definition: template&lt;class T&gt; struct Owned | source comment (unverified): // Compile-time positional DTO map. Keep every fields count/order aligned · [reviewed contract](#b0002) |
| [B0003 · 15–50](../../../../../src/planner/compiled_source.hpp#L15) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 51–57](../../../../../src/planner/compiled_source.hpp#L51) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 58–58](../../../../../src/planner/compiled_source.hpp#L58) | Type/record definition: template&lt;class T&gt; struct Owned&lt;program::Span&lt;T&gt;&gt; |  · [reviewed contract](#b0005) |
| [B0006 · 59–59](../../../../../src/planner/compiled_source.hpp#L59) | Type/record definition: template&lt;class T&gt; struct Owned&lt;program::Set&lt;T&gt;&gt; |  · [reviewed contract](#b0006) |
| [B0007 · 60–60](../../../../../src/planner/compiled_source.hpp#L60) | Type/record definition: template&lt;class T&gt; struct Owned&lt;std::optional&lt;T&gt;&gt; |  · [reviewed contract](#b0007) |
| [B0008 · 61–61](../../../../../src/planner/compiled_source.hpp#L61) | Type/record definition: template&lt;class... T&gt; struct Owned&lt;std::variant&lt;T...&gt;&gt; |  · [reviewed contract](#b0008) |
| [B0009 · 62–67](../../../../../src/planner/compiled_source.hpp#L62) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Type alias only: conversion and ownership live in Copy overloads. · [reviewed contract](#b0009) |
| [B0010 · 68–90](../../../../../src/planner/compiled_source.hpp#L68) | Type/record definition: struct ProgramExport | source comment (unverified): // Caller-owned DTO export of the immutable native compiler artifact. Ordinary · [reviewed contract](#b0010) |
| [B0011 · 91–102](../../../../../src/planner/compiled_source.hpp#L91) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // These copies are compiler inputs, admitted before explicit candidate lowering. · [reviewed contract](#b0011) |

## B0001

[Lines 1–13](../../../../../src/planner/compiled_source.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:39e621607041091fc1e5004aa5b6e93e0089b2f4f5d93baa6c87426bc63d0bf6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/ir/program.hpp", #include &lt;array&gt;, #include &lt;cstdint&gt;, #include &lt;optional&gt;, #include &lt;set&gt;, #include &lt;string&gt;, #include &lt;type_traits&gt;, #include &lt;vector&gt; available to src/planner/compiled_source.hpp; open crown::planner::compiler_source_detail. Attached note: Compile-time positional DTO map. Keep every fields count/order aligned with both aggregates; descriptor leaves use explicit sharing overloads. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0002

[Lines 14–14](../../../../../src/planner/compiled_source.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Owned {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide default identity-mapping metadata for native-to-public DTO conversion. |
| inputs / outputs | Unspecialized T maps Result=T and fields=0; specializations change Result/arity. |
| invariants | Generic copier accepts fields zero only for identical trivially-copyable types; model and storage leaves need explicit mappings. |
| ownership | Compile-time trait owns no object or source reference. |
| failure | Unsafe identity/arity over fifteen fails compilation. |
| cost | No runtime cost. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0003

[Lines 15–50](../../../../../src/planner/compiled_source.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Owned<::crown::program::Column> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native program records to detached planner/frontend/physical DTO record families. |
| inputs / outputs | Explicit mappings cover Column, constraints, estimates/statistics/hints, Table/Catalog, Variable/Atom/Output/Query/tree, planner reports, binding/normalized records, cache/options/guarantee/identity, and physical records through PhysicalNode; each field count matches the aggregate fields used by Copy::copy. Several physical records contain AccountedLayout or AccountedProjection fields, which map to shared descriptor handles rather than deep copies. |
| invariants | Mappings are positional; count/order must stay aligned on both source and destination. Ordinary strings, spans, scalar views and containers are recursively materialized, but accounted layout/projection fields preserve their shared Data/control blocks. |
| ownership | Traits have no runtime storage. Mapped records own copied ordinary payloads; records containing accounted descriptors own shared handles that can retain their account-backed metadata after CompiledProgram expires. |
| failure | Arity errors are compile-time failures; copy/allocation errors occur at use. |
| cost | Trait lookup is compile-time; applying mappings recursively copies ordinary fields and incurs fixed handle/refcount work for each accounted descriptor field, with no new descriptor control block or metadata allocation. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

```text
template<> struct Owned<::crown::program::UniqueConstraint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy declared uniqueness metadata, including trust status; conversion grants no uniqueness proof. |
| inputs / outputs | Compile-time Result maps native UniqueConstraint to its public counterpart; fields=3 selects positional conversion of name, columns, status. |
| invariants | Both aggregates must retain exactly this field count/order. Constraint column IDs remain local numeric values. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 3 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::ForeignKeyConstraint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy complete referenced-key metadata without proving or enforcing referential integrity. |
| inputs / outputs | Compile-time Result maps native ForeignKeyConstraint to its public counterpart; fields=5 selects positional conversion of name, columns, referenced_table, referenced_columns, status. |
| invariants | Both aggregates must retain exactly this field count/order. Both local/referenced ordered column vectors and trust status must remain aligned. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 5 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::DistinctEstimate> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one cost-input distinct-count estimate with its ordered column selector. |
| inputs / outputs | Compile-time Result maps native DistinctEstimate to its public counterpart; fields=2 selects positional conversion of columns, estimate. |
| invariants | Both aggregates must retain exactly this field count/order. An estimate is metadata, not runtime observation or mathematical authority. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::TableStatistics> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy optional row count and all declared distinct estimates. |
| inputs / outputs | Compile-time Result maps native TableStatistics to its public counterpart; fields=2 selects positional conversion of row_count, distinct_counts. |
| invariants | Both aggregates must retain exactly this field count/order. Absent row count and estimate vector order are preserved. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::KeyHint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an advisory key hint and its explanatory text. |
| inputs / outputs | Compile-time Result maps native KeyHint to its public counterpart; fields=2 selects positional conversion of columns, reason. |
| invariants | Both aggregates must retain exactly this field count/order. Hint status does not become a verified constraint or index. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Table> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize complete physical table metadata for compiler/report consumers. |
| inputs / outputs | Compile-time Result maps native Table to its public counterpart; fields=6 selects positional conversion of name, columns, source_schema_version, constraints, statistics, key_hints. |
| invariants | Both aggregates must retain exactly this field count/order. Includes source schema identity, constraints, statistics and hints; it is not a table-data copy. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 6 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Catalog> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a complete native catalog view into owning public catalog records. |
| inputs / outputs | Compile-time Result maps native Catalog to its public counterpart; fields=2 selects positional conversion of version, tables. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves table order/local TableId domain and catalog version; does not validate catalog. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Variable> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a core variable display name and exact scalar type. |
| inputs / outputs | Compile-time Result maps native Variable to its public counterpart; fields=2 selects positional conversion of name, type. |
| invariants | Both aggregates must retain exactly this field count/order. Variable numeric position remains supplied by its enclosing vector. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Atom> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one native occurrence and its ordered term variants. |
| inputs / outputs | Compile-time Result maps native Atom to its public counterpart; fields=3 selects positional conversion of occurrence, table, terms. |
| invariants | Both aggregates must retain exactly this field count/order. Repeated/ignored/constant terms and table ID are preserved; equal base tables do not merge occurrences. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 3 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Output> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one ordered core-head reference and output alias. |
| inputs / outputs | Compile-time Result maps native Output to its public counterpart; fields=2 selects positional conversion of variable, alias. |
| invariants | Both aggregates must retain exactly this field count/order. Duplicate outputs and aliases remain separate positions in the enclosing head. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::Query> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize native core query structure and explicit contradiction flag. |
| inputs / outputs | Compile-time Result maps native Query to its public counterpart; fields=4 selects positional conversion of variables, atoms, head, contradiction. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves all occurrences/ordered terms/outputs; it does not admit or prove the query. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 4 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::TreeNode> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one structural tree record including supplied display ID and claims. |
| inputs / outputs | Compile-time Result maps native TreeNode to its public counterpart; fields=6 selects positional conversion of id, kind, scope, children, occurrence, claimed_separator. |
| invariants | Both aggregates must retain exactly this field count/order. Child order, native occurrence and optional separator are copied, not recomputed or checked. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 6 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::FreeConnexTree> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a complete supplied tree and its optional derived claims. |
| inputs / outputs | Compile-time Result maps native FreeConnexTree to its public counterpart; fields=4 selects positional conversion of root, nodes, claimed_connex, claimed_native_height. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves node index domain and claims; an owning tree DTO is not checked-upper authority. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 4 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::PlanViolation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one diagnostic record with all optional numeric locations. |
| inputs / outputs | Compile-time Result maps native PlanViolation to its public counterpart; fields=6 selects positional conversion of rule, message, node, variable, occurrence, related_node. |
| invariants | Both aggregates must retain exactly this field count/order. Diagnostic strings and positions are descriptive; conversion does not run verification. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 6 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::ValidationReport> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the existing validation diagnostic graph for report/adapter consumers. |
| inputs / outputs | Compile-time Result maps native ValidationReport to its public counterpart; fields=6 selects positional conversion of valid, native_height, edge_depth, maximal_connex, separators, violations. |
| invariants | Both aggregates must retain exactly this field count/order. Copied valid/height fields do not authorize importing a plan or manufacture a checked handle. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 6 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundLiteral> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one optional native scalar literal to an owning SQL literal. |
| inputs / outputs | Compile-time Result maps native BoundLiteral to its public counterpart; fields=1 selects positional conversion of value. |
| invariants | Both aggregates must retain exactly this field count/order. SQL NULL remains absent optional, outside classical core Value. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 1 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundOperation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy resolved operator and ordered expression dependency IDs. |
| inputs / outputs | Compile-time Result maps native BoundOperation to its public counterpart; fields=2 selects positional conversion of operation, arguments. |
| invariants | Both aggregates must retain exactly this field count/order. Argument order and operator enum remain unchanged; no SQL evaluation occurs. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundExpression> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy typed expression variant and optional source location. |
| inputs / outputs | Compile-time Result maps native BoundExpression to its public counterpart; fields=3 selects positional conversion of type, node, location. |
| invariants | Both aggregates must retain exactly this field count/order. Same variant index is retained; dependency IDs are local to the enclosing expression vector. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 3 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundOccurrence> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one resolved SQL scan occurrence including visible column names and scan flag. |
| inputs / outputs | Compile-time Result maps native BoundOccurrence to its public counterpart; fields=5 selects positional conversion of table, alias, column_names, location, include_descendants. |
| invariants | Both aggregates must retain exactly this field count/order. Aliases/column order and include_descendants are preserved without introducing catalog inheritance semantics. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 5 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one named resolved SELECT output expression reference. |
| inputs / outputs | Compile-time Result maps native BoundOutput to its public counterpart; fields=2 selects positional conversion of name, expression. |
| invariants | Both aggregates must retain exactly this field count/order. Ordered enclosing output positions are retained, including repeats. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::BoundSql> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the complete bound SQL source/binding and its operational metadata. |
| inputs / outputs | Compile-time Result maps native BoundSql to its public counterpart; fields=13 selects positional conversion of source, catalog, parameters, semantics, inner_semantics, wrapper, wrapper_alias, occurrences, expressions, predicates, outputs, limits, work. |
| invariants | Both aggregates must retain exactly this field count/order. Copies wrappers/semantics/parameter declarations and all resolved graph IDs; does not parse/rebind or validate source correspondence. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 13 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::ColumnConstant> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one normalized physical-column constant guard with owning scalar. |
| inputs / outputs | Compile-time Result maps native ColumnConstant to its public counterpart; fields=2 selects positional conversion of column, value. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves exact scalar kind/value and local column ID; no row is tested here. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::OccurrenceAdapter> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the full resolved per-occurrence F04 adapter. |
| inputs / outputs | Compile-time Result maps native OccurrenceAdapter to its public counterpart; fields=9 selects positional conversion of occurrence, base, predicates, non_null_columns, equal_columns, column_classes, projection, program, constant_columns. |
| invariants | Both aggregates must retain exactly this field count/order. Includes executable expression order, equality/NULL/constant guards and projection; no adapter execution or proof occurs. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 9 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::ConstantOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one normalized constant SQL output scalar. |
| inputs / outputs | Compile-time Result maps native ConstantOutput to its public counterpart; fields=1 selects positional conversion of value. |
| invariants | Both aggregates must retain exactly this field count/order. Result owns scalar payload; its presence does not add a classical core variable. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 1 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::NormalizedOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one ordered SQL result mapping to core column or constant. |
| inputs / outputs | Compile-time Result maps native NormalizedOutput to its public counterpart; fields=3 selects positional conversion of name, type, value. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves same variant alternative and declared SQL type/name; does not map live result rows. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 3 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::NormalizedSql> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the complete retained normalized SQL artifact for caller DTO use. |
| inputs / outputs | Compile-time Result maps native NormalizedSql to its public counterpart; fields=11 selects positional conversion of binding, parameters, constants, core_catalog, core, adapters, base_routes, outputs, limits, work, schema_version. |
| invariants | Both aggregates must retain exactly this field count/order. Keeps parameter/NULL specialization, core, adapters, routes, SQL outputs, limits/work and schema version; it does not replay normalization. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 11 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::CachePolicy> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy versioned identity policy strings to public physical options. |
| inputs / outputs | Compile-time Result maps native CachePolicy to its public counterpart; fields=4 selects positional conversion of arithmetic, planner, optimization, cost_model. |
| invariants | Both aggregates must retain exactly this field count/order. Accepted policy labels must be validated elsewhere; copying does not authorize unsupported semantics. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 4 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::PhysicalOptions> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy physical policy, producer work ceilings and optional indexed storage specification. |
| inputs / outputs | Compile-time Result maps native PhysicalOptions to its public counterpart; fields=3 selects positional conversion of policy, limits, indexed_storage. |
| invariants | Both aggregates must retain exactly this field count/order. Absent backend preserves legacy reference format; stored producer limits do not override host caps. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 3 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::GuaranteeProfile> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy explicit stage/backend/assumption/guarantee labels for report consumers. |
| inputs / outputs | Compile-time Result maps native GuaranteeProfile to its public counterpart; fields=15 selects positional conversion of semantics, query_class, update_contract, arithmetic, storage_backend, execution_status, height_status, state_bound, maintenance_bound, cursor_startup_bound, cursor_delay_bound, cursor_termination_bound, operation_modes, assumptions, output_accounting. |
| invariants | Both aggregates must retain exactly this field count/order. Labels are retained metadata, not a new theorem, measured performance result or runtime activation. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 15 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::QueryIdentity> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy canonical JSON, all identity namespaces and canonical-to-local ID maps. |
| inputs / outputs | Compile-time Result maps native QueryIdentity to its public counterpart; fields=8 selects positional conversion of canonical, semantic_sha256, output_contract_sha256, cost_inputs_sha256, plan_cache_sha256, occurrence_order, variable_order, work. |
| invariants | Both aggregates must retain exactly this field count/order. Existing digests/work are copied rather than recomputed; matching hashes do not authorize unchecked imports. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 8 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::PhysicalRelation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one role-specific relation record with a shared public layout descriptor. |
| inputs / outputs | Compile-time Result maps native PhysicalRelation to its public counterpart; fields=5 selects positional conversion of id, role, layout, node, base. |
| invariants | Both aggregates must retain exactly this field count/order. Relation ID/owner role remain distinct even when layout token matches another relation. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 5 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::IndexRequirement> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one index descriptor with shared public projection and copied use vector. |
| inputs / outputs | Compile-time Result maps native IndexRequirement to its public counterpart; fields=4 selects positional conversion of id, relation, projection, uses. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves exact projection token, relation ID and declared uses; creates no live index. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 4 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::InputConstant> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one numeric input constant guard with an owning scalar. |
| inputs / outputs | Compile-time Result maps native InputConstant to its public counterpart; fields=2 selects positional conversion of field, value. |
| invariants | Both aggregates must retain exactly this field count/order. Local field identity and scalar kind/value remain unchanged; this is not row adaptation. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 2 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::PhysicalInput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one compiled native occurrence adapter into public descriptor form. |
| inputs / outputs | Compile-time Result maps native PhysicalInput to its public counterpart; fields=8 selects positional conversion of occurrence, node, base, logical_table, physical_layout, projection, equalities, constants. |
| invariants | Both aggregates must retain exactly this field count/order. Physical/logical table domains and independent occurrence IDs remain intact; descriptors share metadata rather than clone it. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 8 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::PhysicalNode> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export all S/P/E node wiring and projections as a public record. |
| inputs / outputs | Compile-time Result maps native PhysicalNode to its public counterpart; fields=15 selects positional conversion of id, kind, occurrence, parent, children, scope, visible_scope, connex, layout, parent_key, visible_projection, records, survivors, parent_support, visible_relation. |
| invariants | Both aggregates must retain exactly this field count/order. Preserves optional visibility/occurrence/parent, exact tokens and separate relation roles; no maintained state is copied or created. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 15 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

## B0004

[Lines 51–57](../../../../../src/planner/compiled_source.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Owned<::crown::program::PhysicalEdge> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map final native program records and scalar/storage leaves to public DTO types, including shared descriptor handle conversions. |
| inputs / outputs | PhysicalEdge, EnumerationStep and EnumerationProgram map to public records with 5, 6 and 4 fields. string_view becomes owning string and InlineDecimal becomes Decimal. AccountedLayout becomes TupleLayout by sharing its LayoutDescriptor Data/control block; AccountedProjection becomes Projection by sharing its ProjectionDescriptor Data/control block. |
| invariants | Record mapping is positional. String/decimal leaves detach their payloads, while layout/projection handles retain account-backed data and native callbacks; they are not deep descriptor copies. |
| ownership | Traits hold no runtime value. Applied layout handles retain the original AccountedLayout::Data, memory block/account and metadata. Projection handles retain AccountedProjection::Data, its projected-field block/account, source/target accounted-layout handles and tokens. |
| failure | Missing mappings fail at compile time or conversion. Empty layout/projection handles fail required() checks; valid descriptor construction allocates no metadata/control block. Other allocation/storage failures propagate. |
| cost | Each descriptor uses O(1) validity/refcount work, with no field scan, new control block or metadata allocation. String/decimal copies scale with payload; containing records/vectors still allocate their own wrappers. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

```text
template<> struct Owned<::crown::program::EnumerationStep> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one parent-before-child visible enumeration instruction. |
| inputs / outputs | Compile-time Result maps native EnumerationStep to its public counterpart; fields=6 selects positional conversion of node, relation, depth, parent_step, parent_key, bucket_index. |
| invariants | Both aggregates must retain exactly this field count/order. Optional parent/projection/index and local numeric IDs are preserved; shared projection metadata is retained. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 6 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<::crown::program::EnumerationProgram> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export visible traversal instructions, ordered output reads and cross-assignment checks. |
| inputs / outputs | Compile-time Result maps native EnumerationProgram to its public counterpart; fields=4 selects positional conversion of steps, output, equalities, depth. |
| invariants | Both aggregates must retain exactly this field count/order. Copies program vectors, preserving repeated output positions; does not enumerate result tuples. |
| ownership | Trait has no object ownership. Applying Copy materializes ordinary text/containers/scalars; any accounted layout/projection fields retain shared metadata Data/control blocks. |
| failure | Trait performs no runtime check. Source arity or incompatible mapped construction can fail compilation; destination order/default-compatible changes still require manual review. Actual nested conversion/allocation failures propagate. |
| cost | No runtime trait cost. Conversion visits 4 fields plus their payloads; ordinary output wrappers may allocate, while descriptor leaves use fixed validation/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<std::string_view> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize native borrowed text as public owning bytes. |
| inputs / outputs | Result=std::string; explicit non-aggregate Copy overload implements conversion of std::string_view. |
| invariants | Copy string_view bytes without UTF-8 reinterpretation or normalization. This leaf omits fields metadata, so the generic aggregate copier is not its conversion path. |
| ownership | Result owns characters and outlives native backing storage. |
| failure | String allocation/length failures propagate. |
| cost | Trait lookup is compile-time only. O(byte width) copy plus ordinary string allocation. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<storage::InlineDecimal> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select explicit export of fixed native inline decimal into public owning exact Decimal. |
| inputs / outputs | Result=Decimal; explicit non-aggregate Copy overload implements conversion of storage::InlineDecimal. |
| invariants | Copy overload exports through ScalarView and extracts Decimal alternative; no aggregate fields metadata is provided. This leaf omits fields metadata, so the generic aggregate copier is not its conversion path. |
| ownership | Public Decimal owns its representation and retains no inline view/arena. |
| failure | Scalar conversion/allocation errors propagate; unexpected variant is bad_variant_access. |
| cost | Trait lookup is compile-time only. Native bounded decimal payload conversion; ordinary owning Decimal representation may allocate. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

```text
template<> struct Owned<storage::AccountedLayout> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a public descriptor handle over the same accounted layout metadata. |
| inputs / outputs | Result=storage::TupleLayout; explicit non-aggregate Copy overload implements conversion of storage::AccountedLayout. |
| invariants | Explicit Copy overload calls descriptor(); it does not recursively materialize layout fields. This leaf omits fields metadata, so the generic aggregate copier is not its conversion path. |
| ownership | Shares original Data/control block, MemoryAccount, field/context/equality metadata and native tuple callback; does not retain complete CompiledProgram or tuple arena. |
| failure | Empty layout contract failure propagates; valid conversion adds no descriptor metadata/control-block allocation. |
| cost | Trait lookup is compile-time only. O(1) validity and shared-handle/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

```text
template<> struct Owned<storage::AccountedProjection> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a public descriptor handle over the same accounted projection metadata. |
| inputs / outputs | Result=storage::Projection; explicit non-aggregate Copy overload implements conversion of storage::AccountedProjection. |
| invariants | Explicit Copy overload calls descriptor(); source/target layout handles and numeric field view remain attached to Data. This leaf omits fields metadata, so the generic aggregate copier is not its conversion path. |
| ownership | Shares projection Data/account and source/target layout owners plus native apply callback; retains selected metadata, not whole program/tuple arena. |
| failure | Empty projection contract failure propagates; valid conversion creates no descriptor metadata/control block. |
| cost | Trait lookup is compile-time only. O(1) validity and shared-handle/refcount work. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0005

[Lines 58–58](../../../../../src/planner/compiled_source.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Owned<program::Span<T>> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map ordered native Span into owning vector of mapped elements. |
| inputs / outputs | Result is vector&lt;Owned&lt;T&gt;::Result&gt;; copier reserves and appends in source order. |
| invariants | Preserves order/duplicates and copies the Span container lifetime. Ordinary items are recursively materialized; AccountedLayout/AccountedProjection items remain shared handles to their original Data. |
| ownership | Owns destination vector storage and mapped value wrappers; accounted descriptor items can keep their account-backed metadata/control blocks alive beyond the source Span owner. |
| failure | Reserve/element failure propagates; partial local vector is destroyed. |
| cost | One reserve and O(n) visits plus nested copies; accounted descriptor items add fixed handle/refcount work and no metadata allocation. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0006

[Lines 59–59](../../../../../src/planner/compiled_source.hpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Owned<program::Set<T>> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native Set to owning standard set. |
| inputs / outputs | Result is set&lt;Owned&lt;T&gt;::Result&gt;; copier maps and inserts each member. |
| invariants | Destination comparator defines order/uniqueness, not source positions. |
| ownership | Owns destination set nodes and mapped value wrappers; mapped accounted descriptors share their original Data. |
| failure | Allocation/conversion failure propagates; no partial result escapes. |
| cost | O(n log n) inserts plus nested copies. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0007

[Lines 60–60](../../../../../src/planner/compiled_source.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Owned<std::optional<T>> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve optional presence while mapping payload. |
| inputs / outputs | Empty remains empty; engaged value recursively maps to Owned&lt;T&gt;::Result. |
| invariants | The optional wrapper is newly constructed. An accounted descriptor payload is a shared handle, not a detached metadata copy. |
| ownership | Owns optional and mapped payload wrapper; descriptor payload can retain shared account-backed data. |
| failure | Nested conversion/allocation failure propagates. |
| cost | Presence check plus payload copy. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0008

[Lines 61–61](../../../../../src/planner/compiled_source.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class... T> struct Owned<std::variant<T...>> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native variant alternatives to same-index owning alternatives. |
| inputs / outputs | Result is variant&lt;Owned&lt;T&gt;::Result...&gt;; copier preserves active index. |
| invariants | Source/destination alternative order must align. A selected accounted descriptor remains a shared handle. |
| ownership | Owns active mapped value wrapper; descriptor alternatives can retain original shared Data. |
| failure | Invalid selector exhaustion is contract failure; nested errors propagate. |
| cost | Checks through active index plus payload copy. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0009

[Lines 62–67](../../../../../src/planner/compiled_source.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using OwnedType=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the mapped public DTO type for generic copy and container/variant reconstruction. |
| inputs / outputs | Alias resolves typename Owned&lt;T&gt;::Result at compile time. |
| invariants | Requires explicit or default Owned mapping; adds no wrapper, runtime dispatch or ownership by itself. |
| ownership | Type alias only; actual destination ownership follows the selected leaf/container/record Copy overload. |
| failure | Missing mapping/type mismatch is compilation failure, not runtime exception machinery. |
| cost | No runtime storage or execution overhead. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

## B0010

[Lines 68–90](../../../../../src/planner/compiled_source.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProgramExport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold caller-owned DTO fields plus descriptor handles exported from one immutable compiled physical program. |
| inputs / outputs | Carries route, catalog/query/tree, normalized source, validation/identity/digests/options/guarantees, layouts/relations/indexes/inputs/routes/nodes/edges/enumeration, result layout and work. Layout/projection fields are public descriptor handle types. |
| invariants | Ordinary DTO fields are copied; AccountedLayout/AccountedProjection fields and result layout are handles sharing backing Data/control blocks. It is not an import path or internal lowering intermediate; validation proves upper feasibility only. |
| ownership | Owns copied ordinary fields and wrapper containers. Shared descriptors can retain specific account-backed layout/projection metadata and account state after CompiledProgram destruction; they do not retain the CompiledProgram object or a tuple/row arena. |
| failure | Aggregate checks nothing; export can fail on digest width, descriptor contract or nested copy. |
| cost | Copies ordinary graph payloads and container storage. Descriptor entries add O(1) required()/refcount work without new metadata/control-block allocation; no byte/work ceiling applies. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0011

[Lines 91–102](../../../../../src/planner/compiled_source.hpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog(const program::Catalog&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native catalog view into owning public compiler input. |
| inputs / outputs | Catalog preserving complete native metadata/local IDs. |
| invariants | Copies all catalog strings/containers; source needs to remain valid only during call. Conversion does not independently validate/rebind/recompute proof or digest. |
| ownership | Borrow source during call only; ordinary return payload owns copies, with exported descriptor exceptions documented above. |
| failure | Conversion/allocation/contract failures propagate directly; no partial result is returned. |
| cost | Full catalog content copy/allocation. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

```text
Query query(const program::Query&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native query view into owning public compiler input. |
| inputs / outputs | Query preserving variables/occurrences/terms/head/contradiction. |
| invariants | Owns returned ordinary containers/scalars; source needs to remain valid only during call. Conversion does not independently validate/rebind/recompute proof or digest. |
| ownership | Borrow source during call only; ordinary return payload owns copies, with exported descriptor exceptions documented above. |
| failure | Conversion/allocation/contract failures propagate directly; no partial result is returned. |
| cost | Full query content copy/allocation. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

```text
frontend::NormalizedSql normalized(const program::NormalizedSql&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy retained normalized SQL view for caller input/report consumers. |
| inputs / outputs | Complete owning normalized artifact including binding, specialization, core and adapters. |
| invariants | Ordinary source/core/adapter payload is copied; no normalization replay occurs. Conversion does not independently validate/rebind/recompute proof or digest. |
| ownership | Borrow source during call only; ordinary return payload owns copies, with exported descriptor exceptions documented above. |
| failure | Conversion/allocation/contract failures propagate directly; no partial result is returned. |
| cost | Full nested normalized content copy/allocation. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

```text
PhysicalOptions options(const program::PhysicalOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy native physical policy/limit/backend record into public options. |
| inputs / outputs | Owning public options with equal declared values. |
| invariants | Copies policy strings and scalar/optional backend metadata; does not impose host admission. Conversion does not independently validate/rebind/recompute proof or digest. |
| ownership | Borrow source during call only; ordinary return payload owns copies, with exported descriptor exceptions documented above. |
| failure | Conversion/allocation/contract failures propagate directly; no partial result is returned. |
| cost | Fixed record members plus policy text allocation. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

```text
ProgramExport export_program(const CompiledProgram&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an immutable native program solely to a caller-owned serializer/report DTO. |
| inputs / outputs | Complete ProgramExport with copied ordinary data and shared layout/projection handles. |
| invariants | Not an internal lowering intermediate or import authority. Descriptor Data/account may outlive source program through returned handles. Conversion does not independently validate/rebind/recompute proof or digest. |
| ownership | Borrow source during call only; ordinary return payload owns copies, with exported descriptor exceptions documented above. |
| failure | Conversion/allocation/contract failures propagate directly; no partial result is returned. |
| cost | Whole ordinary graph/source/JSON/container copy, constant descriptor refcount work per handle and no work/byte ceiling. |
| Design | [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

```text
// These copies are compiler inputs, admitted before explicit candidate lowering. // Runtime owners retain only the native program; no compiler graph is cached.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the existing compiler-source copier entry used for authentic cold replay. |
| inputs / outputs | The internal declaration accepts only the actual immutable native tree and returns owning compiler DTO. |
| invariants | It adds no public API or proof authority; callers still use real \`lower_tree\`. |
| ownership | DTO lifetime is bounded by the lowering call. |
| failure | Missing/invalid declaration fails the compile; copier errors propagate. |
| cost | No runtime cost beyond the converter implementation. |
| Design | [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |
