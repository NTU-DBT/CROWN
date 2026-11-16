# `include/crown/planner/verify.hpp` — block usage map

[Source](../../../../../../include/crown/planner/verify.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims.

Snapshot SHA-256: `2143677a4140df2990027e27a28b32a3995003496ba531e16358731da9804899`. 26 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/planner/verify.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–13](../../../../../../include/crown/planner/verify.hpp#L6) | Type/record definition: struct PlanViolation |  · [reviewed contract](#b0002) |
| [B0003 · 14–21](../../../../../../include/crown/planner/verify.hpp#L14) | Type/record definition: struct ValidationReport |  · [reviewed contract](#b0003) |
| [B0004 · 22–26](../../../../../../include/crown/planner/verify.hpp#L22) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Independent of tree constructors, GYO, search pruning and runtime helpers. · [reviewed contract](#b0004) |

## B0001

[Lines 1–5](../../../../../../include/crown/planner/verify.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:5c05c486f3da928dc14bdcb97d472a6197b325d596c49f1d29e8e95f213dfc7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/ir/tree.hpp" available to include/crown/planner/verify.hpp; open crown::planner. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0002

[Lines 6–13](../../../../../../include/crown/planner/verify.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanViolation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one failed validation rule with typed location context. |
| inputs / outputs | Stores rule/message and optional node, variable, occurrence and related-node IDs. |
| invariants | IDs are local to input query/tree and retain neither; global failures may omit locations. |
| ownership | Owns strings and scalar IDs. |
| failure | Does not validate rule spelling or ID ranges; checker determines diagnostics. |
| cost | String copy linear in text length and may allocate. |
| Design | [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [src/planner/continuation_machine.hpp](../../../../../../src/planner/continuation_machine.hpp) |

## B0003

[Lines 14–21](../../../../../../include/crown/planner/verify.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ValidationReport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked validity, computed metrics, output-connected region, separators and failures. |
| inputs / outputs | valid summarizes checks; native_height/edge_depth are separate maxima; maximal_connex is C*; separators are actual edge intersections; violations records failures. |
| invariants | Missing metrics mean not established, not zero. Empty-body constant has height/depth zero. Valid report proves an upper bound only, not minimum. |
| ownership | Owns vectors/diagnostics; retains no input. |
| failure | Aggregate does not enforce field consistency; blocking validate_tree may propagate admission/copy/allocation failures. |
| cost | Storage/copy scales with tree nodes/edges, scopes and violation strings. |
| Design | [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [src/planner/continuation_machine.hpp](../../../../../../src/planner/continuation_machine.hpp) |

## B0004

[Lines 22–26](../../../../../../include/crown/planner/verify.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ValidationReport validate_tree(const Catalog& catalog, const Query& query, const FreeConnexTree& tree);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an independent validation report for a proposed tree against its Catalog and Query. |
| inputs / outputs | Catalog, Query, and FreeConnexTree in; owned validity, height, separator, and violation data out. |
| invariants | A valid report establishes a checked upper bound, not minimum height. |
| ownership | The blocking adapter copies binding/tree into ValidationMachine; the returned report owns its vectors. |
| failure | Malformed inputs may throw; a valid or invalid tree is reported after complete validation, and admission can allocate. |
| cost | Validation traversals plus input copies; this declaration promises no fixed runtime bound. |
| Design | [src/planner/verify.cpp §validate_tree](../../../../../../src/planner/verify.cpp), [docs/planner_proofs.md §Independent tree verification (P02)](../../../../../planner_proofs.md), [include/crown/planner/verify.hpp §ValidationReport](../../../../../../include/crown/planner/verify.hpp) |
