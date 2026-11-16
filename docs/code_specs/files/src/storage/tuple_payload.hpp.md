# `src/storage/tuple_payload.hpp` — block usage map

[Source](../../../../../src/storage/tuple_payload.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `4db5218d7728fa9daaa62549973d4c9118ea02baec2e210c46166979b1c0167d`. 18 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/storage/tuple_payload.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Concrete shared_ptr control blocks destroy the concrete payload. This base · [reviewed contract](#b0001) |
| [B0002 · 9–17](../../../../../src/storage/tuple_payload.hpp#L9) | Type/record definition: struct TuplePayload | source comment (unverified): // Concrete shared_ptr control blocks destroy the concrete payload. This base · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../src/storage/tuple_payload.hpp#L18) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../src/storage/tuple_payload.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:e84b923f6ab3e1d7c813be220fffb1a7f3c13670328231be5ef356968b0e3b3d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/tuple_payload.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/tuple_values.hpp"\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: Concrete shared_ptr control blocks destroy the concrete payload. This base stores views only; the native derived owner retains AccountedTuple, while explicit standalone compiler/tool tuples retain their legacy input Row. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Concrete shared_ptr control blocks destroy the concrete payload. This base stores views only; the native derived owner retains AccountedTuple, while explicit standalone compiler/tool tuples retain their legacy input Row. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Concrete shared_ptr control blocks destroy the concrete payload. This base stores views only; the native derived owner retains AccountedTuple, while explicit standalone compiler/tool tuples retain their legacy input Row. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 9–17](../../../../../src/storage/tuple_payload.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TuplePayload {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable payload views while the concrete shared owner destroys storage. |
| inputs / outputs | Legacy row pointer or compact native range plus optional account/usage describe a concrete public payload. |
| invariants | Base does not own the pointed row directly; native/legacy derived payload owns it and the shared_ptr retains the concrete deleter. |
| ownership | Accounted native payload retains AccountedTuple; standalone legacy payload retains an ordinary Row. |
| failure | Noncopyable base prevents accidental pointer-view copies as independent owners; construction failures release concrete owners. |
| cost | Fixed view/account metadata, no secondary row mirror or virtual-dispatch framework. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 18–18](../../../../../src/storage/tuple_payload.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:8c6e12fd0f642560c35ea21133123e754f7a1816cffadd4adb769a1efe131187
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/tuple_payload.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
