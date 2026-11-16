# `apps/crown/explain.hpp` — block usage map

[Source](../../../../../apps/crown/explain.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `29cf9661aac780e70332fc7a1e8d5df6407ac7bc9e20b51ab3f63b36dd4b9350`. 6 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../apps/crown/explain.hpp#L1) | guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // Private application dispatcher. argv\[0\] is "explain", argv\[1\] its subcommand. · [reviewed contract](#b0001) |

## B0001

[Lines 1–6](../../../../../apps/crown/explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int explain_main(int argc,char** argv);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private shifted-argv EXPLAIN application dispatcher. |
| inputs / outputs | Main passes argc-1,argv+1 so argv0 is explain and argv1 is its subcommand; returns command-specific process status. |
| invariants | Private executable boundary, not a public query API. Handler/format rules differ from legacy main and compiled workflow dispatch. |
| ownership | Borrows process argv for synchronous call. |
| failure | Implementation owns EXPLAIN diagnostics; declaration creates no handler or resource. |
| cost | Declaration only; actual parse/read/proof/capture/export costs belong to implementation. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |
