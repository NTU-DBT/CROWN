# `tools/verify_memory_cli.py` — block usage map

[Source](../../../../tools/verify_memory_cli.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `ee3d54806d2ab925dd12464d5c5b24f5eb2f2adcadb2f69f286f3446c9d68c97`. 53 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../tools/verify_memory_cli.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–22](../../../../tools/verify_memory_cli.py#L18) | Callable definition: def run(command,code=0): | calls map, decode; returns value.stdout · [reviewed contract](#b0002) |
| [B0003 · 23–53](../../../../tools/verify_memory_cli.py#L23) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; 3 loop sites · [reviewed contract](#b0003) |

## B0001

[Lines 1–17](../../../../tools/verify_memory_cli.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run real memory EXPLAIN CLI acceptance at module import. |
| inputs / outputs | argparse --crown at top level, resolves frozen p08 fixtures and current memory schema, defines run then immediately executes temporary fixture cases. |
| invariants | No import guard: importing is active native IO. Bare asserts require normal Python. Schema/account identities verify finite reports, not arbitrary runtime memory accuracy from DTO labels alone. |
| ownership | Owns parser/args/schema validator and later temporary files/response DOMs; native process state is separate. |
| failure | Import/usage/file/schema failures propagate; no broad top-level catch. |
| cost | Schema read and native process suite at import; captures full output, no per-process timeout in run. |
| Design | [tools/verify_memory_cli.py](../../../../tools/verify_memory_cli.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 18–22](../../../../tools/verify_memory_cli.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(command,code=0):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the selected crown binary and require an exact CLI exit plus empty failure stdout. |
| inputs / outputs | Command argument sequence and expected code default0 in; raw stdout bytes out. |
| invariants | subprocess check=False captures full stdout/stderr; code assertion enabled by caller normal Python. Nonzero expected cases must emit no partial stdout; stderr content not otherwise checked. |
| ownership | Owns completed child captures and argument list; returns bytes owner. |
| failure | Spawn/IO failures propagate; bare AssertionError for wrong code/nonempty failure stdout; no timeout parameter. |
| cost | One native process per call, uncapped in-memory stdout/stderr, decoding stderr only in failure diagnostic assertion expression. |
| Design | [tools/verify_memory_cli.py](../../../../tools/verify_memory_cli.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 23–53](../../../../tools/verify_memory_cli.py#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
with tempfile.TemporaryDirectory(prefix='crown-memory-cli-') as temporary:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise committed, pending, stopped and dropped memory reports plus output/resource rejection controls. |
| inputs / outputs | Temporary plan/events generated from frozen singleton fixtures; six runtime/session cases and four expected errors in. |
| invariants | Checks availability/sequence/layer, owner requested-byte sum and physical row1; noncommitted tables/operators empty. Catalog digest is hand-built for exact fixture, not a general canonicalizer. |
| ownership | TemporaryDirectory owns/removes generated plan/events on normal/error exit; report/schema DOMs process-owned, native state per subprocess. |
| failure | CLI/schema/bare assert failures propagate through temp cleanup; no retained failure corpus in this script. |
| cost | One lower-plan plus ten explain calls, JSON parsing/full owner/table sums; full captures and temporary file bytes outside native account. |
| Design | [tools/verify_memory_cli.py](../../../../tools/verify_memory_cli.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
