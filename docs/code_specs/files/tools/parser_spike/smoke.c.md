# `tools/parser_spike/smoke.c` — block usage map

[Source](../../../../../tools/parser_spike/smoke.c) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `715c3ecc5e76baf8905c569c7de877256cc982869b0798d90778629af947440f`. 41 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tools/parser_spike/smoke.c#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 7–41](../../../../../tools/parser_spike/smoke.c#L7) | Callable definition: int main(void) | calls pg_query_parse, strstr, fputs, fprintf; returns EXIT_FAILURE; EXIT_SUCCESS · [reviewed contract](#b0002) |

## B0001

[Lines 1–6](../../../../../tools/parser_spike/smoke.c#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include <stdio.h>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the libpg_query C API and standard diagnostics/string facilities for the isolated parser spike. |
| inputs / outputs | Compile-time headers; main owns two parser results and returns process success/failure. |
| invariants | Spike is foreign parser syntax evidence, not CROWN admission/query planning, semantic SQL proof or native MemoryAccount instrumentation. |
| ownership | C library owns returned allocated parser buffers until explicit pg_query_free_parse_result; includes do not allocate runtime query state. |
| failure | Missing/incompatible headers fail compilation in separate caller; no runtime handler here. |
| cost | No runtime work from includes; parser allocation/scans occur in main. |
| Design | [tools/parser_spike/smoke.c](../../../../../tools/parser_spike/smoke.c), [tools/parser_spike/run.sh](../../../../../tools/parser_spike/run.sh), [docs/decisions/0002-parser-spike.md](../../../../decisions/0002-parser-spike.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–41](../../../../../tools/parser_spike/smoke.c#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(void) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test one valid SELECT and one malformed SELECT while releasing both foreign parse results. |
| inputs / outputs | No CLI args; calls pg_query_parse twice, checks error/parse_tree and SelectStmt substring, prints status and returns EXIT_SUCCESS or EXIT_FAILURE. |
| invariants | Both cases execute even if first fails. Valid case requires no error plus tree marker; malformed case requires error. Substring is syntax smoke, not full AST/SQL semantic validation. |
| ownership | Owns two PgQueryParseResult values, freeing each once on both observed pass/failure paths; messages/tree borrowed only before corresponding free. |
| failure | Records failures and returns nonzero, retaining safe null diagnostic fallback; foreign catastrophic abort/OOM is not caught by C code. |
| cost | Two full short-SQL parser calls with foreign allocator costs, one strlen-style strstr scan and stdio; frees may traverse parser allocations, all outside CROWN query account. |
| Design | [tools/parser_spike/smoke.c](../../../../../tools/parser_spike/smoke.c), [tools/parser_spike/run.sh](../../../../../tools/parser_spike/run.sh), [docs/decisions/0002-parser-spike.md](../../../../decisions/0002-parser-spike.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |
