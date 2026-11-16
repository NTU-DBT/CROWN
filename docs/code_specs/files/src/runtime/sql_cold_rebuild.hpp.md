# `src/runtime/sql_cold_rebuild.hpp` — block usage map

[Source](../../../../../src/runtime/sql_cold_rebuild.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Declare the concrete private bridge for unpublished genuine SQL cold reconstruction.

Snapshot SHA-256: `e4bb4db5c498254da0f5d387e711fea593a366f863cecb0d2ff0954b602b20d0`. 27 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/runtime/sql_cold_rebuild.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Concrete closed bridge for fresh SQL owners. No live mutation/bypass port is · [reviewed contract](#b0001) |
| [B0002 · 9–26](../../../../../src/runtime/sql_cold_rebuild.hpp#L9) | Type/record definition: class SqlColdRebuild | source comment (unverified): // Concrete closed bridge for fresh SQL owners. No live mutation/bypass port is · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../src/runtime/sql_cold_rebuild.hpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../src/runtime/sql_cold_rebuild.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once #include "crown/runtime/sql_rows.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the internal bridge in a source-private header with the row runtime definitions available. |
| inputs / outputs | Includes the source runtime declaration and internal StorageWorkContext definitions for static bridge signatures. |
| invariants | Not an installed/public header; only this closed friend can construct private Data and token types. |
| ownership | No state ownership in the declaration. |
| failure | Header/type mismatch fails compilation. |
| cost | No runtime cost. |
| Design | [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp) |

## B0002

[Lines 9–26](../../../../../src/runtime/sql_cold_rebuild.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SqlColdRebuild
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one closed internal bridge for cold owner construction and shutdown. |
| inputs / outputs | Static methods cover actual native freeze/storage, cold work context, empty source, whole-image seed and restoration of normal options. |
| invariants | Methods accept genuine plans/programs/images; the bridge exports no live mutator, logical fact port, bypass bool or durable checkpoint API. |
| ownership | It borrows receiver, snapshot and allowance/context; returned runtime/token own their normal account-backed state. |
| failure | Underlying factories report their existing typed errors; no exception wrapper is declared. |
| cost | A stateless class; no allocation until methods invoke actual factories. |
| Design | [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md) |

## B0003

[Lines 27–27](../../../../../src/runtime/sql_cold_rebuild.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:8006176e29bd8d5a726886f993203bd32a406cbe36d48b563ff6209dd1f31eeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::detail\` at its lexical source position in src/runtime/sql_cold_rebuild.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
