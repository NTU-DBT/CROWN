# `apps/crown/aggregate.hpp` — block usage map

[Source](../../../../../apps/crown/aggregate.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `2b1eeb56732d2f4dac4a17f120e32e60e9c3d34db3503eb574cfc94952141c9f`. 5 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../apps/crown/aggregate.hpp#L1) | guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // Separate R2 command family; the original set workflow keeps its formats. · [reviewed contract](#b0001) |

## B0001

[Lines 1–5](../../../../../apps/crown/aggregate.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace crown::cli {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the separate R2 CLI entry point. |
| inputs / outputs | main passes argc/argv to aggregate_main; the definition owns dispatch and leaves the existing final process boundary in control. |
| invariants | This header adds no native runtime/session data field. |
| ownership | Arguments are borrowed for the synchronous invocation. |
| failure | The function may propagate process-boundary diagnostics. |
| cost | Declaration/include work only; one explicit dispatch call when selected. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md) |
