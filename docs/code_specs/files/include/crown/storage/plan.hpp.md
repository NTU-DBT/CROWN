# `include/crown/storage/plan.hpp` — block usage map

[Source](../../../../../../include/crown/storage/plan.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `b223b0f443fa4350ec1aa3bd9a0b61eb56b71f064f3891f09d6db2e5ab8a916c`. 36 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/storage/plan.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Empty internal storage follows the immutable plan's actual backend choice. · [reviewed contract](#b0001) |
| [B0002 · 14–35](../../../../../../include/crown/storage/plan.hpp#L14) | Type/record definition: class PlanStorage | returns plan_; source comment (unverified): // Empty internal storage follows the immutable plan's actual backend choice. · [reviewed contract](#b0002) |
| [B0003 · 36–36](../../../../../../include/crown/storage/plan.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0003) |

## B0001

[Lines 1–13](../../../../../../include/crown/storage/plan.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:28ec729f902d65570351c0e14fcb40ecb4419a85b949a6b84711feae1acf3d38
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/plan.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/physical.hpp"\`, \`"crown/storage/table.hpp"\`, \`"crown/storage/accounted_plan.hpp"\` for compilation; opens namespace \`crown::storage\`. Source comment: Empty internal storage follows the immutable plan's actual backend choice. Indexed initialization/copy borrows one aggregate grant no larger than the plan's declared operation allowance. No independent per-table grants exist. This is not a public query update/epoch API or a memory-byte guarantee. Standalone vectors/tables own ordinary storage; finite work admission here does not establish native query-account requested-byte accounting. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Empty internal storage follows the immutable plan's actual backend choice. Indexed initialization/copy borrows one aggregate grant no larger than the plan's declared operation allowance. No independent per-table grants exist. This is not a public query update/epoch API or a memory-byte guarantee. Standalone vectors/tables own ordinary storage; finite work admission here does not establish native query-account requested-byte accounting. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Empty internal storage follows the immutable plan's actual backend choice. Indexed initialization/copy borrows one aggregate grant no larger than the plan's declared operation allowance. No independent per-table grants exist. This is not a public query update/epoch API or a memory-byte guarantee. Standalone vectors/tables own ordinary storage; finite work admission here does not establish native query-account requested-byte accounting. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md](../../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 14–35](../../../../../../include/crown/storage/plan.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PlanStorage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Instantiate the backend selected by an immutable standalone physical plan. |
| inputs / outputs | PlanStorage owns concrete StorageTable alternatives plus dense requirement-to-index IDs; indexed initialization/copy receives one borrowed aggregate allowance. |
| invariants | Supplied indexed remaining work must be component-wise no larger than plan.per_operation. No per-table reset, independently funded query account, public epoch API or memory-byte guarantee exists here. |
| ownership | Owns ordinary std::vector/table storage and shares plan metadata. The caller-owned IndexWorkAllowance is used synchronously and not retained by PlanStorage. |
| failure | Missing/oversized/exhausted grant, invalid plan/ID and concrete storage/allocator failures propagate; no retries or new budgets are constructed. |
| cost | Initialization visits relations/indexes and allocates vectors/tables; snapshot_copy visits all live rows/index memberships. check_invariants may scan/allocate; indexed binding probes still consume the supplied finite grant. |
| Design | [include/crown/storage/plan.hpp](../../../../../../include/crown/storage/plan.hpp), [src/storage/plan.cpp](../../../../../../src/storage/plan.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 36–36](../../../../../../include/crown/storage/plan.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/plan.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md](../../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
