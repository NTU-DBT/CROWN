# `src/storage/index_work_alias.hpp` — block usage map

[Source](../../../../../src/storage/index_work_alias.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Expose different diagnostic policies over the same canonical work balance.

Snapshot SHA-256: `8e1c04cfda48fc97c4d0b11e4206453a72232243699ac083ab87682e47551400`. 17 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/storage/index_work_alias.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Runtime diagnostic bridge: public and compact storage consume one canonical · [reviewed contract](#b0001) |
| [B0002 · 8–16](../../../../../src/storage/index_work_alias.hpp#L8) | Type/record definition: struct IndexWorkAlias | returns IndexWorkAllowance(root,true); IndexWorkAllowance(root,false); source comment (unverified): // Runtime diagnostic bridge: public and compact storage consume one canonical · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../src/storage/index_work_alias.hpp#L17) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–7](../../../../../src/storage/index_work_alias.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:ba942b3dd1e051ac84426d5cd0215fde7d1a7085074834951748929f751c87d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/index_work_alias.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: Runtime diagnostic bridge: public and compact storage consume one canonical balance with their respective diagnostics. Nonmovable view, no allocation. The caller retains a canonical non-alias root for the whole borrow. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Runtime diagnostic bridge: public and compact storage consume one canonical balance with their respective diagnostics. Nonmovable view, no allocation. The caller retains a canonical non-alias root for the whole borrow. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Runtime diagnostic bridge: public and compact storage consume one canonical balance with their respective diagnostics. Nonmovable view, no allocation. The caller retains a canonical non-alias root for the whole borrow. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 8–16](../../../../../src/storage/index_work_alias.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexWorkAlias {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose fixed-diagnostic cold-source and legacy aliases over one canonical indexed-work root. |
| inputs / outputs | \`fixed(root)\` and \`legacy(root)\` each construct the existing nonmovable alias with distinct diagnostic policy over that same balance. |
| invariants | The root must be canonical, not another alias; neither view copies/refills the five counters, and cold fixed diagnostics preserve the indexed source error phase. |
| ownership | The caller keeps the canonical root alive through the whole borrow; the alias has no independent grant or owner. |
| failure | Construction remains noexcept under the root precondition; later allowance exhaustion follows selected diagnostic policy. |
| cost | Inline pointer/tag construction only; no allocation, extra balance, traversal or synchronization. |
| Design | [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md), [docs/sql_source_images.md §Closed cold reconstruction](../../../../sql_source_images.md) |

```text
struct IndexWorkAlias
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the same fixed-diagnostic root for cold source preparation without copying/refilling it. |
| inputs / outputs | A canonical IndexWorkAllowance root -&gt; nonowning alias with fixed diagnostics; existing legacy alias stays available. |
| invariants | Caller keeps canonical root alive for entire borrow; alias accounting subtracts from that same root and carries no independent balance. |
| ownership | Returned alias is a transient view, not root owner; no heap memory. |
| failure | Invalid/moved-root constraints follow IndexWorkAllowance’s existing contract. |
| cost | Constant inline reference-wrapper construction and counter forwarding; no allocation. |
| Design | [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md) |

## B0003

[Lines 17–17](../../../../../src/storage/index_work_alias.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/index_work_alias.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
