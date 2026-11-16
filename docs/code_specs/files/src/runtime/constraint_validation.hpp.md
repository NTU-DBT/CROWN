# `src/runtime/constraint_validation.hpp` — block usage map

[Source](../../../../../src/runtime/constraint_validation.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Validate complete native proposed source snapshots and enforced constraints under the query account.

Snapshot SHA-256: `3e793cf737b9f3b7817beca2b918565c51b8a17a337505a25e44eccc39c20f79`. 82 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/runtime/constraint_validation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Operational snapshots retain only native compact rows and accounted capacity. · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../src/runtime/constraint_validation.hpp#L12) | Type/record definition: struct NativeDatabase | source comment (unverified): // Operational snapshots retain only native compact rows and accounted capacity. · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../src/runtime/constraint_validation.hpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy. · [reviewed contract](#b0003) |
| [B0004 · 19–24](../../../../../src/runtime/constraint_validation.hpp#L19) | Type/record definition: struct ConstraintKeyLess | returns a.view()&lt;b.view(); a.view()&lt;b; source comment (unverified): // Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy. · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/runtime/constraint_validation.hpp#L25) | Explanatory comments or spacing. |  |
| [B0006 · 26–42](../../../../../src/runtime/constraint_validation.hpp#L26) | Callable definition: inline void validate_native_row(const program::Catalog& catalog,TableId table,storage::TupleValuesView values) | calls size, Error, legacy_row, crown::type_of; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–47](../../../../../src/runtime/constraint_validation.hpp#L43) | Explanatory comments or spacing. | source comment (unverified): // The immutable catalog was validated when its actual CompiledProgram was · [reviewed contract](#b0007) |
| [B0008 · 48–81](../../../../../src/runtime/constraint_validation.hpp#L48) | Callable definition: template&lt;class DatabaseView&gt; void validate_native_database(const program::Catalog& catalog,const DatabaseView& database, const re… | calls size, Error, validate_native_row, validation_values; returns item.status!=ConstraintStatus::enforced; storage::RowView::borrow(cells); growth copy_of, insert, push_back, reserve; 8 loop sites; source comment (unverified): // The immutable catalog was validated when its actual CompiledProgram was · [reviewed contract](#b0008) |
| [B0009 · 82–82](../../../../../src/runtime/constraint_validation.hpp#L82) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0009) |

## B0001

[Lines 1–11](../../../../../src/runtime/constraint_validation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:6d35eee91b827b0bbcef7b91acb1e20f6e22333d16257268f0c5e8dc1cbfbb0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/constraint_validation.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"validation_work.hpp"\`, \`"crown/ir/program_model.hpp"\`, \`"crown/resource/allocator.hpp"\`, \`&lt;set&gt;\` for compilation; opens namespace \`crown::runtime::detail\`. Source comment: Operational snapshots retain only native compact rows and accounted capacity. Public diagnostic Database exports remain a separate external boundary. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Operational snapshots retain only native compact rows and accounted capacity. Public diagnostic Database exports remain a separate external boundary. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Operational snapshots retain only native compact rows and accounted capacity. Public diagnostic Database exports remain a separate external boundary. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 12–17](../../../../../src/runtime/constraint_validation.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeDatabase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an operational database snapshot with native compact tuples and accounted capacities. |
| inputs / outputs | Rows is a funded vector of AccountedTuple; tables is a funded vector of Rows. Constructor binds the outer allocator to scratch and the supplied attribution; callers create each inner vector and clone/import tuple payloads. |
| invariants | Container construction alone does not validate row schemas, enforce constraints or initialize every inner allocator. Physical snapshot callers supply one existing query account throughout. |
| ownership | Outer/inner capacities and tuple blocks have actual owners. Tuples own their row blocks; views borrow those blocks. Moving vectors transfers owners without relocating their existing row blocks. |
| failure | Later resize/clone/funding failures release partial local owners through RAII. This empty constructor adds no catch or new unlimited account. |
| cost | Empty outer allocator setup is fixed; population/snapshot costs include all tuple/byte clones and vector capacities, and old/new database graphs can overlap at peak. |
| Design | [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [tests/unit/physical_runtime_test.cpp](../../../../../tests/unit/physical_runtime_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 18–18](../../../../../src/runtime/constraint_validation.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:fb4fb9893f39684fce888a4b1580988cdd2b430f3ee9d56b69b7a6e9a5a45596
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct ConstraintKeyLess\`: Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/constraint_validation.hpp:L19; use that declaration for the actual input/output shape. |
| invariants | The source note states: Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 19–24](../../../../../src/runtime/constraint_validation.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstraintKeyLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare owned compact keys and borrowed projected views through one transparent strict row ordering. |
| inputs / outputs | Three overloads compare AccountedRow/AccountedRow, AccountedRow/RowView and RowView/AccountedRow using view() and native lexicographic ordering. |
| invariants | Identical ordering for insertion and heterogeneous lookup is required by the ordered set; empty projected keys compare normally. Tags and exact native values, including unsigned string-byte and Decimal ordering, remain significant. |
| ownership | Comparator owns nothing and never copies a key or string. Operands must remain valid for the synchronous comparison. |
| failure | Declared noexcept; invalid/dangling operands are caller bugs rather than recoverable input diagnostics. |
| cost | Short-circuit field comparison with compared string-prefix bytes and bounded Decimal comparison work; no successful allocation or maintained hash/index. |
| Design | [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [tests/unit/physical_runtime_test.cpp](../../../../../tests/unit/physical_runtime_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 26–42](../../../../../src/runtime/constraint_validation.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void validate_native_row(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one complete physical row against the admitted catalog scalar domains. |
| inputs / outputs | Checks table ID, exact column count, each legacy/native scalar tag, then exact precision/scale fit for columns carrying a Decimal specification. |
| invariants | No coercion, Decimal rounding, string UTF-8 scan or SQL expression evaluation occurs. Decimal specification on a nondecimal column is invalid_catalog. The native view accepts binary string bytes used by direct APIs. |
| ownership | Borrows catalog/tuple values synchronously and retains no row or key; only rejection messages copy column names. |
| failure | Bounds/shape/type errors throw invalid_update; bad Decimal metadata throws invalid_catalog; domain overflow throws scalar_overflow. No mutation or catch. |
| cost | Linear field scan plus bounded InlineDecimal parts/fit arithmetic. Failure diagnostics can allocate; normal native validation exports no owning Row/string graph. |
| Design | [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [tests/unit/physical_runtime_test.cpp](../../../../../tests/unit/physical_runtime_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 43–47](../../../../../src/runtime/constraint_validation.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L47:sha256:a3a35e553c4c219297449d4fec79508584b7e195d97e244037a29cd2a58925fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class DatabaseView&gt; void validate_native_database(const program::Catalog& catalog,const DatabaseView& database, const resource::MemoryAccount& account,resource::MemoryAttr\`: The immutable catalog was validated when its actual CompiledProgram was admitted. Rechecking that frozen metadata with ordinary sets/strings is not needed. Validate every row before projecting any constraint, preserving the reference checker's error order and exact scalar/decimal semantics. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/constraint_validation.hpp:L48; use that declaration for the actual input/output shape. |
| invariants | The source note states: The immutable catalog was validated when its actual CompiledProgram was admitted. Rechecking that frozen metadata with ordinary sets/strings is not needed. Validate every row before projecting any constraint, preserving the reference checker's error order and exact scalar/decimal semantics. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | The note describes a failure or stop boundary: The immutable catalog was validated when its actual CompiledProgram was admitted. Rechecking that frozen metadata with ordinary sets/strings is not needed. Validate every row before projecting any constraint, preserving the reference checker's error order and exact scalar/decimal semantics. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 48–81](../../../../../src/runtime/constraint_validation.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_native_database(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate every row first, then enforce admitted unique and foreign-key constraints over the complete candidate database. |
| inputs / outputs | Requires the program catalog already validated at CompiledProgram admission. Checks table count, all row shapes/types/domains, then only constraints with enforced status. |
| invariants | Row validation precedes every constraint to preserve the reference error order. Unique rejects duplicate projected keys; FK builds referenced projected keys then probes each source projection. Nullary keys remain ordinary keys; untrusted constraints are skipped. |
| ownership | Temporary set nodes, compact key copies and reusable ScalarView projection capacity are funded as scratch by the supplied original account/attribution. Lookup projections borrow the reused cells only during contains(). Database/catalog are unchanged. |
| failure | Invalid row/catalog, constraint violations, funding/overflow/allocation failures propagate; RAII destroys private sets/cells. Callers own candidate update rollback and admission work precharges; this validator does not restore spent work. |
| cost | Repeated whole-row scans plus one ordered set build per enforced constraint: O(rows log distinct) key comparisons per build/probe, each comparison can inspect field/text bytes. Actual compact key/node allocations and per-row key copies remain, independent of abstract precharges. |
| Design | [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [tests/unit/physical_runtime_test.cpp](../../../../../tests/unit/physical_runtime_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
    const auto project=[&](const auto& row,const auto& columns) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Form a temporary ordered constraint-key view without a second owning key export. |
| inputs / outputs | Clears/repopulates the reusable funded ScalarView vector using the compiled column IDs and returns RowView::borrow(cells). |
| invariants | Catalog admission has validated projection IDs and widths. Repeated/empty column lists follow the declared ordering; each returned view expires when cells is next changed or destroyed. |
| ownership | ScalarView text/Decimal views borrow row payload; neither clearing cells nor returning the view owns row bytes. Set insertion explicitly copies it before reuse. |
| failure | Vector capacity admission can fail; malformed compiled IDs are outside this trusted metadata precondition. No catch or row mutation. |
| cost | O(projected width) view-cell copies and potential vector allocation when capacity is first admitted; no text-byte clone for FK lookup itself. |
| Design | [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [tests/unit/physical_runtime_test.cpp](../../../../../tests/unit/physical_runtime_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 82–82](../../../../../src/runtime/constraint_validation.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:e39c39ee7071fa62eb75df66509c0b467a6749ca8a3a61a663367890341483eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::detail\` at its lexical source position in src/runtime/constraint_validation.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
