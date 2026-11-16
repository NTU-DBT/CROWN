# `src/runtime/validation_work.hpp` — block usage map

[Source](../../../../../src/runtime/validation_work.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compose one full physical source update across all its aliases into one atomic logical support epoch.

Snapshot SHA-256: `0963c2d17bc30eaa444b30775553a808fe10db56f066a0e4759a1fd4781a55a6`. 55 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/runtime/validation_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Conservative abstract precharges for the reference validator's complete · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../src/runtime/validation_work.hpp#L12) | Callable definition: inline std::uint64_t validation_product(std::size_t count,std::size_t width) | calls max, Error; returns n*w; source comment (unverified): // Conservative abstract precharges for the reference validator's complete · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../src/runtime/validation_work.hpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Actual callers provide ordinary Row or native AccountedTuple values; the result · [reviewed contract](#b0003) |
| [B0004 · 20–23](../../../../../src/runtime/validation_work.hpp#L20) | Callable definition: template&lt;class RowValue&gt; storage::TupleValuesView validation_values(const RowValue& row) | calls constexpr, values, storage::TupleValuesView::borrow; returns storage::TupleValuesView::borrow(row.values()); storage::TupleValuesView::borrow(row); source comment (unverified): // Actual callers provide ordinary Row or native AccountedTuple values; the result · [reviewed contract](#b0004) |
| [B0005 · 24–54](../../../../../src/runtime/validation_work.hpp#L24) | Callable definition: template&lt;class CatalogView,class DatabaseView,class Charge&gt; void charge_database_validation(const CatalogView& catalog,const Data… | calls size, Error, charge, validation_values; 7 loop sites; source comment (unverified): // validate_catalog resolves targets and searches their unique keys. · [reviewed contract](#b0005) |
| [B0006 · 55–55](../../../../../src/runtime/validation_work.hpp#L55) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–11](../../../../../src/runtime/validation_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:a228682328e5f04ba401b6bd2e474f4ce4794fc225bbb15a1c5dea5acedb089b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/validation_work.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/api/error.hpp"\`, \`"crown/ir/model.hpp"\`, \`"crown/storage/tuple_values.hpp"\`, \`&lt;limits&gt;\` for compilation; opens namespace \`crown::runtime::detail\`. Source comment: Conservative abstract precharges for the reference validator's complete metadata, row-shape and repeated enforced-key projection/set passes. Ordered comparisons, scalar payload widths and allocator costs remain explicit. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Conservative abstract precharges for the reference validator's complete metadata, row-shape and repeated enforced-key projection/set passes. Ordered comparisons, scalar payload widths and allocator costs remain explicit. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 12–17](../../../../../src/runtime/validation_work.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t validation_product(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject unsigned overflow when composing a row-count/width validation precharge. |
| inputs / outputs | Converts supported host counts to uint64, tests w!=0 && n&gt;UINT64_MAX/w, then returns n*w; zero width returns zero. |
| invariants | Repository host size_t fits uint64; actual call widths are admitted metadata field counts plus one. This product is an abstract work quantity, not an allocator request or complexity bound. |
| ownership | Inline values only; no row or source owner retained. |
| failure | Overflow throws Error(resource_limit) before caller charge; no wrapping/refund. |
| cost | Fixed arithmetic/checks with no allocation on valid success; failure diagnostic construction can allocate. |
| Design | [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 18–19](../../../../../src/runtime/validation_work.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L19:sha256:dc00abbc3fb47bfa79d30509605d9548ea3b87392735d23bb010a55f57336cbb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class RowValue&gt; storage::TupleValuesView validation_values(const RowValue& row)\`: Actual callers provide ordinary Row or native AccountedTuple values; the result borrows their stable payload and performs no owning row export. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/validation_work.hpp:L20; use that declaration for the actual input/output shape. |
| invariants | The source note states: Actual callers provide ordinary Row or native AccountedTuple values; the result borrows their stable payload and performs no owning row export. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Actual callers provide ordinary Row or native AccountedTuple values; the result borrows their stable payload and performs no owning row export. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 20–23](../../../../../src/runtime/validation_work.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class RowValue> storage::TupleValuesView validation_values(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual supported row representation for physical validation. |
| inputs / outputs | For current AccountedTuple callers uses TupleValuesView::borrow(row.values()), otherwise borrows ordinary Row. Returns a nonowning TupleValuesView. |
| invariants | The requires branch checks values() existence, while overload compatibility still must compile; it is not an unconstrained adapter for any values()-returning type. Actual ordinary/native database callers satisfy it. |
| ownership | Result borrows the supplied row's native block or ordinary vector; caller must keep row and its bytes stable through validation. No owning export/rehome. |
| failure | No custom catch or dynamic type fallback; invalid template shape is a compile-time error. |
| cost | Fixed view/tag construction without copying fields/text or allocating. |
| Design | [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 24–54](../../../../../src/runtime/validation_work.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView,class DatabaseView,class Charge> void charge_database_validation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge conservative complete physical validation work on the caller's current allowance. |
| inputs / outputs | Checks table-count shape, walks metadata names/columns/stats/hints/row widths/constraint definitions; enforced unique charges rows*(key width+1), FK charges target-key resolution plus target/source rows*(respective width+1). |
| invariants | Compiled catalog references/width arithmetic were admitted earlier. Charges model repeated complete validation passes, including named conservative metadata work; they do not replace actual ordered-key comparison, copied-byte or allocator costs. No per-update maintained constraint index is introduced. |
| ownership | Catalog/database are borrowed; Charge is passed by value (actual call sites use light captures) and updates the caller's existing work state. No owning row or catalog copy is made. |
| failure | Shape mismatch throws invalid_database; product overflow/resource denial or charge callback failures propagate with spent units retained. Invalid admitted references are outside normal contract and at() can expose them. |
| cost | Actual loops over all metadata/rows/constraints plus target constraint search; aggregate product debits avoid expanding rows*width solely for charging. Subsequent validation performs real sets, key copies and byte comparisons separately. |
| Design | [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 55–55](../../../../../src/runtime/validation_work.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:8006176e29bd8d5a726886f993203bd32a406cbe36d48b563ff6209dd1f31eeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::detail\` at its lexical source position in src/runtime/validation_work.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
