# `src/storage/accounted_plan_testing.hpp` — block usage map

[Source](../../../../../src/storage/accounted_plan_testing.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `b912d4d2fd2dc2202719c54e73687748c091d5e95aec505c6c8058425989f815`. 24 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/storage/accounted_plan_testing.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Lets the allocation tracer test metadata construction without linking the · [reviewed contract](#b0001) |
| [B0002 · 10–23](../../../../../src/storage/accounted_plan_testing.hpp#L10) | Type/record definition: class AccountedPlanStorageTesting | returns AccountedPlanStorage(account, input, work); source comment (unverified): // Lets the allocation tracer test metadata construction without linking the · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../src/storage/accounted_plan_testing.hpp#L24) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–9](../../../../../src/storage/accounted_plan_testing.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a coherent private testing interface only. |
| inputs / outputs | Compile guard requires CROWN_ACCOUNTED_PLAN_TESTING==1; imports actual backend headers and declares only private test helpers. |
| invariants | Not installed or serialized. Corresponding mutator definitions exist only in their coherent testing variants; this is not a production hash callback or admission API. |
| ownership | Declarations own no live backend; call-specific inputs are borrowed. |
| failure | Mismatched/missing macro triggers compile-time #error; declarations add no runtime exception layer. |
| cost | No runtime work at inclusion; testing definitions/inline construction run only in explicit tests. |
| Design | [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

## B0002

[Lines 10–23](../../../../../src/storage/accounted_plan_testing.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedPlanStorageTesting
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide raw storage-construction access for allocation-tracer tests. |
| inputs / outputs | Private friend creates Inputs from route/identity/layout/relation/index spans and optional indexed spec. |
| invariants | Does not construct/replay a public opaque PhysicalPlan or minimum proof; separate production-constructor tests cover that authority. |
| ownership | Borrows caller metadata during construction; returned AccountedPlanStorage owns actual funded metadata/backends. |
| failure | Private constructor contract/work/account failures propagate; no partial owner returned. |
| cost | Only fixed Inputs packaging before actual storage construction/admission; no SQL compiler dependency. |
| Design | [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

```text
static AccountedPlanStorage create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build actual funded plan storage from explicit test metadata. |
| inputs / outputs | Chooses fixed backend-version literal, forwards optional collision compile profile and calls the private account/Inputs/work constructor. |
| invariants | Metadata spans must stay valid through call; route/spec consistency and actual budgets remain enforced by the constructor. |
| ownership | Inputs borrow caller ranges synchronously; result takes its own real storage/metadata under supplied account. |
| failure | Constructor/finite-work/account failures unwind private preparation; no catch/retry or fabricated proof. |
| cost | Normal metadata/backend construction cost and actual account/work admissions, with no parser/proof work. |
| Design | [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

## B0003

[Lines 24–24](../../../../../src/storage/accounted_plan_testing.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/accounted_plan_testing.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
