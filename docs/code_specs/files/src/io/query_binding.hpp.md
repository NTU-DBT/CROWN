# `src/io/query_binding.hpp` — block usage map

[Source](../../../../../src/io/query_binding.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `6e6e27c04dd9e2ad782a25203f32753efbb224b374ffac6ce43a0a96ed0175f6`. 17 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/io/query_binding.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–16](../../../../../src/io/query_binding.hpp#L6) | Callable definition: inline Json query_binding(const Catalog& catalog, const Query& query) | calls size, catalog::requires_format3, write_document; returns write_document(document); 2 loop sites; source comment (unverified): // This explicit export copies the owning catalog/query and allocates an ordinary DOM. · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../src/io/query_binding.hpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../src/io/query_binding.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an explicit catalog/query binding artifact with no runtime rows. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–16](../../../../../src/io/query_binding.hpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Json query_binding(const Catalog& catalog, const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a complete query binding into an independently owned strict document. |
| inputs / outputs | Catalog/query in; Document copy with catalog-size empty initial tables and no updates converted to Json out. |
| invariants | Starts format1, raises to2 for date/decimal, to3 for catalog::requires_format3. Identity includes schema/policy fields; output labels never substitute for SearchBinding typed authority. |
| ownership | Aggregate construction deep-copies ordinary catalog/query and allocates Relation vector; write_document owns DOM copies. Input owners stay untouched. |
| failure | Document validation/scalar/DOM/OOM failures propagate; no live query/native state publication. |
| cost | Catalog column scan for version plus requires_format3 scan, full document validation/serialization, ordinary graph+DOM copies; cold IO outside advance quanta. |
| Design | [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–17](../../../../../src/io/query_binding.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:e75574b225d635cb469e050a484ebdf6a963046faaad8e8dda0e77c4f871ec43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [docs/code_specs/files/src/io/query_binding.hpp.md](query_binding.hpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/semantics.md](../../../../semantics.md) |
