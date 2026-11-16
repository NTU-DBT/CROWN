# `tools/support/ComponentReplay.scala` — block usage map

[Source](../../../../../tools/support/ComponentReplay.scala) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `d0ecfc6afbeaea885d56abb3469a1bf24cd5dfbbdcfce2244b160ba7a707fb0d`. 211 lines partitioned into 8 blocks using `script_regions`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tools/support/ComponentReplay.scala#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 12–37](../../../../../tools/support/ComponentReplay.scala#L12) | declares types or opens a type body; declares values/defaults or compile-time conditions. | guard require(found != null, "missing component field " + name); growth new · [reviewed contract](#b0002) |
| [B0003 · 38–61](../../../../../tools/support/ComponentReplay.scala#L38) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard require(bytes &lt; maximum, "component output-byte limit exceeded"); growth new; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 62–97](../../../../../tools/support/ComponentReplay.scala#L62) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(args.length == 1, "usage: ComponentReplay REQUEST.json") · [reviewed contract](#b0004) |
| [B0005 · 98–133](../../../../../tools/support/ComponentReplay.scala#L98) | declares callable signatures; declares values/defaults or compile-time conditions. | guard else { require(operation == "-", "component operation must be + or -");; growth new; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 134–169](../../../../../tools/support/ComponentReplay.scala#L134) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(!output.checkError(), "Scala component delta output failed"); 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 170–205](../../../../../tools/support/ComponentReplay.scala#L170) | declares callable signatures; declares values/defaults or compile-time conditions. | 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 206–211](../../../../../tools/support/ComponentReplay.scala#L206) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |

## B0001

[Lines 1–11](../../../../../tools/support/ComponentReplay.scala#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:10a6668bd0b3129b013bbe77860504740b23f4e026d615869f9ff17c89ec9abb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import pinned original payload/harness APIs and the already available shaded Jackson observer dependencies. |
| inputs / outputs | Imports Java streams/UTF8/files, original RelationType classes, Flink key/type/harness APIs, Scala collection conversion and Jackson tree types. |
| invariants | The new helper is compiled beside immutable original classes. It adds no Maven dependency or replacement propagation algorithm. |
| ownership | Imports retain no query owner or result graph. |
| failure | Missing or mismatched pinned classpath fails compilation/class loading; no alternate runtime is substituted. |
| cost | Compile/class-load/startup work, not a measured update bound. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tools/support/CrownReplay.scala](../../../../../tools/support/CrownReplay.scala), [docs/measurement.md](../../../../measurement.md) |

## B0002

[Lines 12–37](../../../../../tools/support/ComponentReplay.scala#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L37:sha256:0902dc311dd1aff1cac90b1e9ab8796a4cd6cfad50c5b075294faea0aa22cea9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the Scala observer's metadata, exact JSON accessors and unavailable-versus-measured timing export. |
| inputs / outputs | Creates the ObjectMapper and Event DTO; member/text/number reject missing/wrong types and invalid nonnegative Long ranges; timed writes null for verification or a real supplied duration. |
| invariants | These helpers supply transport preconditions only. Family/mode and query correctness are not inferred from JSON flags. Scala/Jackson object initialization can precede run's read clock and belongs to outer JVM startup. |
| ownership | The object owns one mapper; Event owns Strings/int values. JsonNode accessors borrow the caller's retained request tree; timing nodes are report-owned. |
| failure | Illegal arguments/JSON operations propagate to the sole main catch; no runtime rollback is implemented. |
| cost | Selected tree access/type/range checks, scalar timing export and ordinary JSON allocation; no total parse/CPU or account bound is claimed. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md), [tools/support/ComponentReplay.scala](../../../../../tools/support/ComponentReplay.scala) |

## B0003

[Lines 38–61](../../../../../tools/support/ComponentReplay.scala#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L61:sha256:e4c0c8b378d364e250369ec8d50dd4cb220be48329a44bdb856473c7cfe38b68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe genuine Scala Console bytes with a finite cumulative allowance and optional raw event capture. |
| inputs / outputs | TextSink counts bytes/newlines for single/bulk writes, resets only the raw frame and exports UTF8 text in verify. |
| invariants | Measure mode retains no payload frame. Counters and byte cap are pass-wide; newline count is raw emission multiplicity and no deduplication/parsing occurs. |
| ownership | Owns one optional ByteArrayOutputStream, its retained current-frame capacity and counters. PrintStream borrows the sink; captured String export copies bytes. |
| failure | Invalid slices, cap excess or allocation failures propagate. Published process state may already have changed; no rollback is added. |
| cost | Bulk writes scan/copy O(bytes); one-byte writes do constant selected work. Verification String extraction copies a frame; intrinsic PrintStream/formatter/sink work is part of baseline API observation, not free instrumentation. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md) |

## B0004

[Lines 62–97](../../../../../tools/support/ComponentReplay.scala#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L97:sha256:c0bbfe7c2fb5728664ed864fe80dc36323fc5b68ceec98de674e35a01f694c1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin Scala cold request admission and the valid unit-set event projection through its insertion branch. |
| inputs / outputs | Checks request pathname/content size, parses JSON, enforces fixed L3/full-drain mode, caps/pass counts, begins a temporary-set mapping of g1/g2/g3 int32 pairs and verifies absent inserts. Deletion and vector completion continue in the next source region. |
| invariants | This is a generic 36-line source span cutting across run/map control flow, not a Scala method/AST boundary. The input must remain immutable during launch: size is sampled before readAllBytes and content checked after reading. verify means capture, not correctness authority. |
| ownership | Request bytes/tree and eventual Event vector are caller-owned; the temporary validation set leaves scope before owner creation. No engine owner exists yet. |
| failure | File/JSON/type/range/size/mode/duplicate errors abort through main. File growth between size/read can allocate before the second content check; no concurrent-input or global allocator bound is supplied. |
| cost | O(content) parsing plus complete-trace validation/DTO work, outside owner/API clocks. Caller/JVM input allocations are separate from native accounts and external RSS observations. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md), [tools/support/CrownReplay.scala](../../../../../tools/support/CrownReplay.scala) |

## B0005

[Lines 98–133](../../../../../tools/support/ComponentReplay.scala#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L133:sha256:bbaeb0e50d8066d6d2d0119cbd98c3c1d49bfc3bb66d8624a116cbecf82dd004
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish cold event admission, create fresh original Flink owners/sinks per pass and enter the matched loop. |
| inputs / outputs | Completes valid-delete checks and Event vector, defines published schema/name mapping, records read time, constructs bounded result/diagnostic streams and the keyed L3ProcessFunctions(2) harness, then starts event iteration. |
| invariants | The span continues a mapping begun earlier and opens a try/finally completed later. Every pass has fresh logical state; JVM/JIT/allocator state can persist. Harness construction precedes the explicit finally; no universal cleanup of a factory that fails before return is claimed. |
| ownership | Cold validation set is out of scope. Each successful factory result, original function and streams belong to one pass; harness.close is owned by the later finally. Schema arrays/names are immutable shared transport metadata. |
| failure | Bad delete/admission/factory/allocation errors propagate. Before the factory returns, its own failure cleanup is delegated to Flink/process termination, not this not-yet-entered finally. |
| cost | Read/admission and mapper/name setup are recorded once; streams/harness initialization is timed per pass. New JVM startup is external; fresh-owner warmups are not steady-state qualification. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tools/support/CrownReplay.scala](../../../../../tools/support/CrownReplay.scala), [crown/src/main/scala/L3ProcessFunctions.scala](../../../../../crown/src/main/scala/L3ProcessFunctions.scala), [docs/measurement.md](../../../../measurement.md) |

## B0006

[Lines 134–169](../../../../../tools/support/ComponentReplay.scala#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L169:sha256:b291fe7fdb4fa1d88acd1c283e7e1bac64e7dd73f61be0750cc9b0d6fc2aa58a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one published L3 event and unconditionally consume its real full result iterator. |
| inputs / outputs | Builds fresh Attributes/Payload, records transport time, invokes harness.processElement and stream flush/check, drains fullAttrEnumerate(null) once, enforces combined delta/snapshot counts, and builds bounded actual delta-text/row capture in verify. Epoch metadata begins here and completes next region. |
| invariants | Full drain occurs after EVERY event in verify and measure because the original enumerator can change global-alive state. No delta-only qualification is implied. Verify reads A/B/C/D immediately and preserves duplicates; measure retrieves/counts/discards rows without allocating per-row JSON. |
| ownership | Payload values/keys live through the synchronous harness call. Iterator rows are consumed before advancing; verification vectors/Strings/JSON own copied observations, while measure retains no result history. |
| failure | Published process/iterator errors, stream failures, record/byte caps and allocation failures propagate; later finally closes a returned harness. Already-mutated baseline state is not rolled back. |
| cost | Transport allocation is separate. Apply includes keyed harness, intrinsic named-pair formatting, writes and flush/check. Output includes real iterator setup/next/termination; verify-only row copying/JSON is unmeasured and final captured encoding follows the output clock. This is not maintenance-only or pure-dispatch timing. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tools/support/CrownReplay.scala](../../../../../tools/support/CrownReplay.scala), [crown/src/main/scala/RelationType/Relation.scala](../../../../../crown/src/main/scala/RelationType/Relation.scala), [docs/measurement.md](../../../../measurement.md) |

## B0007

[Lines 170–205](../../../../../tools/support/ComponentReplay.scala#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L205:sha256:7faa97d6814f44fb63552cffc0fff6661200b78c67204c9dff767e65a4ed6ba1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete per-event records, close the original harness in finally and publish pass/final observer metadata. |
| inputs / outputs | Finishes timings/counts/actual rows, stores epochs and loop wall, diverts the original close footer to a diagnostic sink, closes streams, records pass totals, assembles the report and writes/flushed JSON with stdout error checking. |
| invariants | Delta/snapshot channels retain raw multiplicity; close diagnostics are not result records or accepted timing samples. Native-account and shared-program fields are null when unavailable. A fresh logical owner does not establish a fresh JVM or steady state, and no correctness verdict is emitted. |
| ownership | The finally owns cleanup after successful harness construction. Report trees retain verification copies and per-event metadata outside the baseline; sinks/harness are pass-local. No extra live query-row index is installed. |
| failure | During loop failure finally attempts normal close; a close failure may propagate by normal language semantics. Final reporting/stream failure stops the process after query work; no retry or rollback transaction exists. |
| cost | Per-event report bookkeeping is outside selected apply/output clocks but inside loop wall. Harness close/stream release is teardown; final JSON serialization/flush is outside service. Captured-result memory grows only in verify, latency metadata remains O(events×passes), and JVM/process peaks can include all passes/report data. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md), [tools/support/ComponentReplay.scala](../../../../../tools/support/ComponentReplay.scala) |

## B0008

[Lines 206–211](../../../../../tools/support/ComponentReplay.scala#L206); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L206-L211:sha256:6e852bbb47a6f5b790c8b4fd5a7533903e09251bc1e210bf0c2c83a7099fd0d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close run and provide the Scala helper's sole CLI exception/exit boundary. |
| inputs / outputs | Main forwards a failed run status to System.exit(1); standard Exceptions print one message and exit nonzero. |
| invariants | This structural source span is not an independent Scala method inventory. Success means completed capture/measurement transport, not oracle or performance acceptance. |
| ownership | Normal language scope/unwinding and the preceding finally own pass resources; external runner owns process logs/artifacts. |
| failure | Exception failures become nonzero; fatal Errors/signals retain ordinary JVM behavior. No second error framework or retry is introduced. |
| cost | Normal call/status handling, with failure-only stderr work. JVM startup/shutdown are external process costs. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md) |
