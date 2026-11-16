# `tools/verify_observability_reports.py` — block usage map

[Source](../../../../tools/verify_observability_reports.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `e2566da2d1161f30a3b27505dd8847579412a80d00f89b1d8bc1bad2b840f726`. 35 lines partitioned into 1 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–35](../../../../tools/verify_observability_reports.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |

## B0001

[Lines 1–35](../../../../tools/verify_observability_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
shutil.rmtree(corpus)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one native observability exporter and checker through a fresh corpus directory. |
| inputs / outputs | Parses --kind/--executable/--repo-root at module import; cursor writes child stdout to cursor.json, query/composed ask the child to write corpus files, then invoke the matching checker; composed passes root/schema paths. |
| invariants | Import consumes argv and executes the driver. Exceptions inside the exporter/checker try block attempt a retained-path diagnostic and re-raise. After successful checking, the else branch removes the corpus; setup and cleanup failures are outside that catch. |
| ownership | The script owns the mkdtemp path and requests deletion after exporter/checker success. A cleanup error can leave a partly removed tree; protected execution failures retain existing partial artifacts. |
| failure | Argparse/path/setup errors propagate before the protected block. Inside it, exporter/checker errors attempt to print the retained path then re-raise; rmtree errors occur outside that catch and can follow partial deletion. |
| cost | One exporter plus one checker; output file count/size is controlled by the selected native fixture, with no capture-size cap in this wrapper. |
| Design | [tools/verify_observability_reports.py](../../../../tools/verify_observability_reports.py), [tools/support/check_cursor_reports.py](../../../../tools/support/check_cursor_reports.py), [tools/support/check_query_reports.py](../../../../tools/support/check_query_reports.py), [tools/support/check_composed_reports.py](../../../../tools/support/check_composed_reports.py), CMakeLists.txt:989-991, tools/verify_observability_reports.py:1-35 |
