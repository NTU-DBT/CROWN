# `apps/crown/workflow.hpp` — block usage map

[Source](../../../../../apps/crown/workflow.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `fc59dd4690edea38bdd5d1e38152aca454b1a2f5ed2d22b185728f48b2b73367`. 2 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–2](../../../../../apps/crown/workflow.hpp#L1) | guards repeated header inclusion; declares namespace scope; declares callable signatures. |  · [reviewed contract](#b0001) |

## B0001

[Lines 1–2](../../../../../apps/crown/workflow.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int workflow_main(int,char**);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private full-argv file workflow dispatcher. |
| inputs / outputs | Main forwards argc/argv unchanged for known file workflow commands and compiled explain/validation. |
| invariants | Not a server or weighted/nullable SQL API; command and durable phase admission occurs inside implementation. |
| ownership | Borrows argv; implementation owns tool/native/file handles. |
| failure | Workflow implementation translates typed failures and returns status; no declaration-side effects. |
| cost | Declaration only. |
| Design | [docs/cli.md](../../../../cli.md) |
