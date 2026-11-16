# `apps/crown/workflow_verify.hpp` — block usage map

[Source](../../../../../apps/crown/workflow_verify.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `4ea4da7f30b7f5df423efb5a7ae95f5fb71531f206575cb3db0cb9f29bc69eda`. 12 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../apps/crown/workflow_verify.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Diagnostic input/event caps and modeled reference work/bytes are separate · [reviewed contract](#b0001) |

## B0001

[Lines 1–12](../../../../../apps/crown/workflow_verify.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string verify_workflow_trace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the bounded modeled relational workflow diagnostic. |
| inputs / outputs | Admitted normalized plan, input path/profile, optional native memory, modeled reference work/bytes, event and output limits yield owning JSON text. |
| invariants | Independent relational join enumeration shares validated SQL adapters/mapping; reference estimates are not a total heap/CPU cap or durable restart proof. |
| ownership | Returned text owns bytes; references to plan/path are borrowed during call. |
| failure | Model/input/native/output resource or mismatch errors propagate; no partially returned report. |
| cost | Declaration only; synchronous implementation scans/recomputes complete small state. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |
