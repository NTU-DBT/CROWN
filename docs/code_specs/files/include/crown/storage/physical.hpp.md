# `include/crown/storage/physical.hpp` — block usage map

[Source](../../../../../../include/crown/storage/physical.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `02c518031b20a10713add793489c1e5d123d89faa4272dd04667259d849859f6`. 30 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/storage/physical.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Empty storage instantiated exclusively from an immutable validated plan. · [reviewed contract](#b0001) |
| [B0002 · 9–29](../../../../../../include/crown/storage/physical.hpp#L9) | Type/record definition: class ReferencePlanStorage | returns plan_; source comment (unverified): // Empty storage instantiated exclusively from an immutable validated plan. · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../../../include/crown/storage/physical.hpp#L30) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../../include/crown/storage/physical.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:4be80f2d0ef5d4fa0f136d50a8c05d79b1830767c0ea450079d4de2e606c27d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/physical.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/physical.hpp"\`, \`"crown/storage/reference.hpp"\` for compilation; opens namespace \`crown::storage\`. Source comment: Empty storage instantiated exclusively from an immutable validated plan. Internal backend access, not a public query-update/epoch API. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Empty storage instantiated exclusively from an immutable validated plan. Internal backend access, not a public query-update/epoch API. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md](../../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 9–29](../../../../../../include/crown/storage/physical.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReferencePlanStorage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Instantiate and copy the standalone ordered-storage realization of a checked physical plan. |
| inputs / outputs | Constructs empty ReferenceTables and registered compiled indexes; table(RelationId) and index(IndexRequirementId) resolve dense plan IDs. |
| invariants | Rejects plans selecting indexed storage. This internal backend interface does not implement public query updates or epoch atomicity. |
| ownership | Owns PhysicalPlan handle and ordinary table/index vectors. snapshot_copy creates fresh table/arena owners while preserving sparse logical IDs and high-water counters. |
| failure | Invalid plan/backend/ID and ordinary allocation failures propagate; construction/copy publishes no partial returned owner. |
| cost | Initialization visits plan relations/indexes and allocates ordinary container metadata. Snapshot cost includes all live rows, deep legacy values and index memberships; full invariant checks may scan and allocate. |
| Design | [include/crown/storage/physical.hpp](../../../../../../include/crown/storage/physical.hpp), [src/storage/physical.cpp](../../../../../../src/storage/physical.cpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 30–30](../../../../../../include/crown/storage/physical.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/physical.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md](../../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
