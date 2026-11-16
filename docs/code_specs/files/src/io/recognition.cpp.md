# `src/io/recognition.cpp` — block usage map

[Source](../../../../../src/io/recognition.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `87f648ff3b3362e343631338c6aa32a5d103f185ad63dbb745537290eb63ae6e`. 29 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/io/recognition.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–21](../../../../../src/io/recognition.cpp#L5) | Callable definition: Json reduction_json(const planner::GyoResult& reduction, const Query& query) | calls Json::array, at, push_back, std::move; returns {{@ ,reduction.acyclic},{@ ,std::move(witness)},{@ ,std::move(core)}}; growth push_back; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../src/io/recognition.cpp#L22) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 23–28](../../../../../src/io/recognition.cpp#L23) | Callable definition: Json write_structural_analysis(const planner::StructuralAnalysis& analysis, const Query& query) | calls reduction_json, size; returns {{@ ,1},{@ ,classification},{@ ,reduction_json(analysis.body,query)},; source comment (unverified): // Report the supplied structural witness; exact minimum height remains unchecked. · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/io/recognition.cpp#L29) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0005) |

## B0001

[Lines 1–4](../../../../../src/io/recognition.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/recognition.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export structural-recognition witnesses/classification as diagnostics without making minimum-height claims. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/recognition.cpp](../../../../../src/io/recognition.cpp), [include/crown/io/recognition.hpp](../../../../../include/crown/io/recognition.hpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 5–21](../../../../../src/io/recognition.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json reduction_json(const planner::GyoResult& reduction, const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one GYO-style reduction witness and failed core using query variable names. |
| inputs / outputs | GyoResult and matching Query in; acyclic/witness/failed_core DOM out. |
| invariants | Query indices must address supplied matching variable graph; .at checks variable range. Kind uses private/contained/else-empty mapping; no independent witness replay here. |
| ownership | Borrowed result/query; DOM deep-copies variable/edge label strings and arrays. |
| failure | Mismatched variable IDs throw out_of_range; DOM OOM propagates; no correction or catch. |
| cost | O(witness steps+failed-core scope entries+name bytes) traversal and ordinary DOM allocations. |
| Design | [src/io/recognition.cpp](../../../../../src/io/recognition.cpp), [include/crown/io/recognition.hpp](../../../../../include/crown/io/recognition.hpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 22–22](../../../../../src/io/recognition.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/recognition.cpp](../../../../../src/io/recognition.cpp), [docs/code_specs/files/src/io/recognition.cpp.md](recognition.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/tree_oracle.md](../../../../tree_oracle.md) |

## B0004

[Lines 23–28](../../../../../src/io/recognition.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_structural_analysis(const planner::StructuralAnalysis& analysis, const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the reported body/augmented structural class with height explicitly unchecked. |
| inputs / outputs | StructuralAnalysis plus matching Query in; classification, two reduction exports and synthetic head edge count out. |
| invariants | free_connex/cyclic/else acyclic_non_free_connex map existing enum; height_status=not_checked. Structural class alone is neither checked tree nor exact minimum-height evidence. |
| ownership | Input analysis/query borrowed; output DOM owns complete copied witnesses. |
| failure | Reduction indexing/DOM failure propagates; no planner/engine mutation. |
| cost | Sum of body and augmented witness/core traversal/copy, not execution of the recognition algorithm. |
| Design | [src/io/recognition.cpp](../../../../../src/io/recognition.cpp), [include/crown/io/recognition.hpp](../../../../../include/crown/io/recognition.hpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 29–29](../../../../../src/io/recognition.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/recognition.cpp](../../../../../src/io/recognition.cpp), [docs/code_specs/files/src/io/recognition.cpp.md](recognition.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/tree_oracle.md](../../../../tree_oracle.md) |
