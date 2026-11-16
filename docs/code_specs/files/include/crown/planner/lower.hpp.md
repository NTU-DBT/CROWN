# `include/crown/planner/lower.hpp` — block usage map

[Source](../../../../../../include/crown/planner/lower.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `7bca1c628c9fc68b43ff467517b42d940ae1ab84aee646e65b5a63ed419829a6`. 16 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../../include/crown/planner/lower.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Limits count selected checkpoints; replay, validation, copies, JSON/hash · [reviewed contract](#b0001) |

## B0001

[Lines 1–16](../../../../../../include/crown/planner/lower.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] PhysicalPlan lower_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Public factory for a validated physical upper plan from actual CQ/tree inputs. |
| inputs / outputs | Catalog/query/tree, producer PhysicalOptions and optional host ceilings return immutable PhysicalPlan. |
| invariants | Independently checks actual inputs; no editable report/boolean or supplied height authorizes construction. Chooses no minimum-height/cost policy. |
| ownership | Borrows arguments during copying; returned ordinary compiler artifact owns source/graph and descriptor handles. |
| failure | Validation, work/identity, JSON/hash, layout and allocation failures propagate as existing exceptions; no partial artifact. |
| cost | Source/tree copies plus full validation/identity/construction/serialization. PhysicalLimits count selected checkpoints, not all CPU or allocator bytes. |
| Design | [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/physical_plans.md](../../../../../physical_plans.md), [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp) |

```text
[[nodiscard]] PhysicalPlan lower_normalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Public factory that replays normalized SQL before lowering its grounded core tree. |
| inputs / outputs | NormalizedSql/tree, options, program replay limits and optional host physical ceilings return immutable PhysicalPlan. |
| invariants | Legacy v1 is grounded to v2 before tree validation. Supplied tree must match grounded core; explicit contradiction requires empty canonical tree. Validity is upper/constant-operator authority only. |
| ownership | Returned plan owns replayed source/adapters and copied core/graph; caller arguments may expire. |
| failure | Serialization/replay/upgrade/copy and lowering failures propagate with no partial artifact. Independent program/host ceilings cannot be raised by producer data. |
| cost | Full serialization/read/replay and optional grounding before private lowering, outside any claim of hard time/byte bounds. |
| Design | [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/physical_plans.md](../../../../../physical_plans.md), [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp) |
