# `tools/support/CrownReplay.scala` — block usage map

[Source](../../../../../tools/support/CrownReplay.scala) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `1ec5f7e6b528e2a73d63f6f90bd8a4887291790800ca70631893c2293f9c2e11`. 46 lines partitioned into 2 blocks using `script_regions`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tools/support/CrownReplay.scala#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 11–46](../../../../../tools/support/CrownReplay.scala#L11) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(args.length == 1, "expected a relation-keyed replay file"); growth new; 1 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–10](../../../../../tools/support/CrownReplay.scala#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:f3478408fe8d4010d68a7b24ce6e73ed3c125457b624f0f171161981ef279683
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the original Flink payload/process test APIs and Java/Scala helpers used by the standalone verification adapter. |
| inputs / outputs | Imports RelationType payload/schema types, byte capture and UTF-8/file/Base64 utilities, Flink keyed harness/type/key selector classes, and Scala collection conversion. |
| invariants | This Scala file is a verification-only helper compiled beside pinned original sources; imports do not patch or replace the published process function. |
| ownership | Imports and object declarations retain no query or result state. |
| failure | Missing pinned dependencies fail at compile time. |
| cost | Compilation and class loading only; not a runtime or benchmark claim. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/source_baselines.md](../../../../source_baselines.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0002

[Lines 11–46](../../../../../tools/support/CrownReplay.scala#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L46:sha256:ad30e0a921f32515c85f7370dc0be437b54d165a8c658dad3bbcec54c76be4a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed the unchanged Scala L3 process function through a keyed harness, capture raw signed output, and copy its full current-result iterator after every event. |
| inputs / outputs | Requires one trace path; constructs L3ProcessFunctions(2), schema G1(A,B)/G2(B,C)/G3(C,D), reads each +/- relation pair, calls the actual keyed harness, captures raw output bytes, immediately copies fullAttrEnumerate rows to integer vectors, sorts snapshots, and emits event/delta_base64/rows JSON lines. |
| invariants | The harness drains the genuine current-result iterator after every event because the original enumerator can update global-alive markers; this is not delta-only or maintenance-only execution. Duplicate/absent operations are outside this helper's admitted replay contract; Python checker validates the tiny trace independently. The original source is unchanged. |
| ownership | Flink harness owns operator state and is closed in finally; payloads and output buffers are per event; snapshot rows are copied before advancing to avoid borrowed iterator objects escaping. |
| failure | Argument, harness-construction, schema/file-read failures before the try propagate; explicit finally cleanup covers failures during the event loop. The qualified caller supplies a readable trace. Harness.close failures also propagate; stdout is captured by the separate command receipt. |
| cost | For each event, invokes the real Flink process plus full current-result enumeration, copies/sorts rows, buffers signed bytes and Base64/JSON output. Framework harness and full drains add overhead; no timing or production runtime claim. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/source_baselines.md](../../../../source_baselines.md), [Refactor.md §11.11 B01](../../../../../Refactor.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json), [benchmarks/legacy/replay/scala-l3-mixed.txt](../../../../../benchmarks/legacy/replay/scala-l3-mixed.txt) |
