# `include/crown/runtime/program_span.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/program_span.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Expose borrowed spans into immutable native program storage.

Snapshot SHA-256: `2943f60c3222025debf650c2bdca3d3838ff16a5c1d111743019b0ea7f69182a`. 3 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../../include/crown/runtime/program_span.hpp#L1) | Imports dependencies; guards repeated header inclusion. |  · [reviewed contract](#b0001) |

## B0001

[Lines 1–3](../../../../../../include/crown/runtime/program_span.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L3:sha256:2943f60c3222025debf650c2bdca3d3838ff16a5c1d111743019b0ea7f69182a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/runtime/program_span.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/program_span.hpp"\`, \`"crown/runtime/program_aliases.hpp"\` for compilation. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
