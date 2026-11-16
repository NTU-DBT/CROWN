# `src/runtime/owner_statistics_detail.hpp` — block usage map

[Source](../../../../../src/runtime/owner_statistics_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `1d00ad04efde4c683b6bef9a3d27f070375e729f9aa62e0975bfb0ebb4006d87`. 20 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/runtime/owner_statistics_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Internal synchronous composition: request_ borrows the caller span; output_ owns · [reviewed contract](#b0001) |
| [B0002 · 6–19](../../../../../src/runtime/owner_statistics_detail.hpp#L6) | Type/record definition: class OwnerBuilder | returns request_; budget_; source comment (unverified): // Internal synchronous composition: request_ borrows the caller span; output_ owns · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/runtime/owner_statistics_detail.hpp#L20) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../src/runtime/owner_statistics_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:f1b784f4677c7d70ece2b8f272b2394fd9bbe52c4a6ffbccd3889bef37042812
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/owner_statistics_detail.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/owner_statistics.hpp"\` for compilation; opens namespace \`crown::runtime::statistics::detail\`. Source comment: Internal synchronous composition: request_ borrows the caller span; output_ owns captured values. budget_/account() reuse the existing capture/query allowances. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Internal synchronous composition: request_ borrows the caller span; output_ owns captured values. budget_/account() reuse the existing capture/query allowances. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Internal synchronous composition: request_ borrows the caller span; output_ owns captured values. budget_/account() reuse the existing capture/query allowances. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 6–19](../../../../../src/runtime/owner_statistics_detail.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OwnerBuilder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose owner-only metadata and native distribution capture under one original account. |
| inputs / outputs | request_ borrows OwnerRequestView, budget_ owns shared logical Limits/Usage, output_ owns the eventual OwnerCapture. Population helpers append components then fill actual tables/indexes/maps. |
| invariants | One builder serves a synchronous request; request span and source owners remain stable until finish. No independent per-component budget or query account is minted. |
| ownership | Returned capture owns its copied selections/values and retained program; builder-only request references do not escape. |
| failure | Constructor/append translate only logical Exhausted; table/index map exact work-limit faults; allocation/invalid request/corruption remain actual failures. |
| cost | Metadata reservation/copy plus actual selected population scans and copied-key allocation. Budget arithmetic is not total CPU, and immutable handle sharing is distinct from deep capture copying. |
| Design | [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const OwnerRequestView& request()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original request view during owner-only composition. |
| inputs / outputs | Returns request_ by reference, whose selections span still refers to caller storage. |
| invariants | Internal synchronous composition only; these references are not public report mutation APIs. |
| ownership | Caller request and builder must outlive use; no field-vector clone or span lifetime extension. |
| failure | No explicit failure translation; account() requires the valid plan already retained by constructor. |
| cost | Fixed reference return with no row scan, key copy or capacity allocation. |
| Design | [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  Budget& budget()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the one shared logical capture budget to native/weighted population helpers. |
| inputs / outputs | Returns the same mutable budget_; spent work and prior component usage compose sequentially. |
| invariants | Internal synchronous composition only; these references are not public report mutation APIs. |
| ownership | Reference borrows builder; no allowance copy, refill or independent grant. |
| failure | No explicit failure translation; account() requires the valid plan already retained by constructor. |
| cost | Fixed reference return with no row scan, key copy or capacity allocation. |
| Design | [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const resource::MemoryAccount& account()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable program's original account for every capture allocation. |
| inputs / outputs | Returns output_.plan().account() by reference. |
| invariants | Internal synchronous composition only; these references are not public report mutation APIs. |
| ownership | Capture retains program/account; reference remains valid only with its owning graph. No new account is created. |
| failure | No explicit failure translation; account() requires the valid plan already retained by constructor. |
| cost | Fixed reference return with no row scan, key copy or capacity allocation. |
| Design | [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 20–20](../../../../../src/runtime/owner_statistics_detail.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::statistics::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::statistics::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::statistics::detail\` at its lexical source position in src/runtime/owner_statistics_detail.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::statistics::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
