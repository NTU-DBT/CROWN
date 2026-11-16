# `include/crown/runtime/program_aliases.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/program_aliases.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `074326605617004cdb76e49417c739fbe0ce9e49649e904f69596f7b14ec6913`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/runtime/program_aliases.hpp#L1) | guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../../include/crown/runtime/program_aliases.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using ::crown::CompiledProgram;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose CompiledProgram and the crown::program namespace under crown::runtime. |
| inputs / outputs | Compile-time names resolve to the canonical crown-level type and namespace. |
| invariants | The declarations are aliases, not wrapper types or separate program objects. |
| ownership | No additional ownership is introduced; lifetime follows the aliased objects. |
| failure | Alias use has no runtime failure path. |
| cost | Compile-time name aliases only; no runtime work or allocation. |
| Design | [include/crown/runtime/program_aliases.hpp](../../../../../../include/crown/runtime/program_aliases.hpp), [include/crown/ir/program.hpp §CompiledProgram](../../../../../../include/crown/ir/program.hpp), [include/crown/runtime/physical.hpp §PhysicalRuntime](../../../../../../include/crown/runtime/physical.hpp) |
