# `tools/run_baseline_evaluation.py` — block usage map

[Source](../../../../tools/run_baseline_evaluation.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `d74da2e7037ffb8ac41f8c487378169aef4901cf4e1cba58ac279a13b707c540`. 268 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../tools/run_baseline_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–52](../../../../tools/run_baseline_evaluation.py#L26) | Callable definition: def legacy_actual(actual, family): | calls require, fullmatch, int, split; guard require(re.fullmatch(r'(0\|\[1-9\]\[0-9\]*)\.0000\n',text) is not None, 'invalid legacy cardinality text…; returns int(text.split('.')\[0\]); groups; 5 loop sites · [reviewed contract](#b0002) |
| [B0003 · 53–54](../../../../tools/run_baseline_evaluation.py#L53) | Explanatory comments or spacing. |  |
| [B0004 · 55–89](../../../../tools/run_baseline_evaluation.py#L55) | Callable definition: def check_observations(report, arm, request, oracle, verify, reference=None): | calls require, all, in, len; guard require(report\['implementation'\] == implementation and all(report\[key\] == request\[key\]; returns {'identity':identity,'counts':count_signature(report\['passes'\]\[-1\]),'checked_prefixes':checked}; 6 loop sites · [reviewed contract](#b0004) |
| [B0005 · 90–91](../../../../tools/run_baseline_evaluation.py#L90) | Explanatory comments or spacing. |  |
| [B0006 · 92–241](../../../../tools/run_baseline_evaluation.py#L92) | Callable definition: def run(args): | calls vars, items, isinstance, setattr; guard require(sys.platform.startswith('linux') and hasattr(os,'wait4'), 'study requires Linux wait4'); returns \[native\[adapter\],path\]; \[args.legacy_cpp.resolve(),path\]; growth new; 37 loop sites; source comment (unverified): # Bind actual immutable executable/JAR/class bytes. Existing qualification · [reviewed contract](#b0006) |
| [B0007 · 242–243](../../../../tools/run_baseline_evaluation.py#L242) | Explanatory comments or spacing. |  |
| [B0008 · 244–264](../../../../tools/run_baseline_evaluation.py#L244) | Callable definition: def main(): | calls ArgumentParser, in, add_argument, parse_args; returns 1; 0; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 265–268](../../../../tools/run_baseline_evaluation.py#L265) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–25](../../../../tools/run_baseline_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:76cc25f3991f56bc6cfdd58e959220bfa4bfcf16ac6a5bccdab6188cf629b99d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a correctness-gated whole-implementation baseline/native/SQLite study. |
| inputs / outputs | Imports exact fixed cohort/query/catalog/oracle definitions, rational summaries and established process/provenance/check helpers. |
| invariants | Import performs no experiment. Whole implementations retain scalar/parser/formatting/framework/JVM differences; no pure-dispatch attribution is implied. |
| ownership | Module objects are parent Python memory; actual query state belongs to later child adapters. |
| failure | Missing dependencies fail import, without fallback engine or oracle. |
| cost | Cold import/analysis support is outside child query accounts and API timers. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [docs/component_evaluation.md](../../../component_evaluation.md), [tools/component_workloads.py](../../../../tools/component_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [Refactor.md §14.4](../../../../Refactor.md) |

## B0002

[Lines 26–52](../../../../tools/run_baseline_evaluation.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L52:sha256:81c32fd016969ccc01adfa9939b2b5bdecf86124f391bbea83ecfa065ecc9c4a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode actual original scalar/group output and Scala named signed tuples for independent verification. |
| inputs / outputs | Raw component text plus fixed family produces cardinality, full grouped counts or rows with signed A/B/C/D values. |
| invariants | Scalar/group formats require exact integral .0000 output in the finite positive baseline domain. Group keys are unique. Scala payload is exactly four comma-separated A-D named pairs with unique names; field order normalizes but unknown fields/garbage reject. |
| ownership | Owns parent parsed verification records; no parsing or result graph is retained inside measured legacy children by this function. |
| failure | Malformed text, duplicates or invalid named tuples reject the correctness gate rather than repairing published output. |
| cost | Parsing is proportional to actual output text and occurs during preflight. Intrinsic baseline formatting remains charged in the actual child API path. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [tools/support/ComponentReplay.scala](../../../../tools/support/ComponentReplay.scala), [examples/component-runtime/legacy_cpp.cpp](../../../../examples/component-runtime/legacy_cpp.cpp), [tests/integration/baseline_evaluation.py](../../../../tests/integration/baseline_evaluation.py) |

## B0004

[Lines 55–89](../../../../tools/run_baseline_evaluation.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L89:sha256:2822185d21730915fed200cec77d13d1c382f8d4df040044ff2316400997ee96
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate external verification output or any measured implementation against its completed strong gate. |
| inputs / outputs | Report/arm/request plus full oracle during external verification or frozen reference during measurement returns identity/counts/checked-prefix count. |
| invariants | Native verification separately uses unchanged strong check_report. Every pass preserves warmup, physical order, phase and clock/null contracts. External preflight compares exact decoded records to independent SQL; measure captures remain null and actual count_signature/identity equal the verified gate. Measurement never needs fake compact oracle frames. |
| ownership | Reads parent decoded metadata and optional verification frames; holds no engine owner. Releasing oracle graphs after the true gate does not release the retained raw report or binding. |
| failure | A wrong implementation, order, frame, count, identity or clock fails receiving. Frozen counts have authority only through earlier exact observation checks. |
| cost | Verification is output-sensitive; measurement validation scans scalar/report metadata and avoids retaining million-row oracle graphs across arms. No formal total-CPU claim. |
| Design | [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py), [tools/component_workloads.py](../../../../tools/component_workloads.py), [docs/component_evaluation.md](../../../component_evaluation.md), [docs/legacy_baselines.md](../../../legacy_baselines.md) |

## B0006

[Lines 92–241](../../../../tools/run_baseline_evaluation.py#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L241:sha256:ff198869920dd3ebb8fd6199763ccb4e5c726ddedde6817192313e804fc20716
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a finite matched fixed-query study with all independent gates before timing. |
| inputs / outputs | CLI paths/cohort manifest produce new requests, raw process/resource outputs, qualified external pins, gates, seeded repeated fresh-process runs and exact ratio summaries. |
| invariants | Locks original SQL/output and complete fixed physical catalog; native adapter/one-transaction/one-observation/delta-fold or ordinary-aggregate controls are explicit. Comparisons are legacy-to-native or SQLite-to-native with identical source/program/output. Native preflight is strong; external preflight checks exact physical prefixes. All gates complete before measure; only frozen counts/identity validate measured paths. Every invocation has identical fresh-owner warmups and one measured pass. B04 acceptance remains false. |
| ownership | Owns only a new study directory, parent oracle/report DTOs and new Java home/tmp. Published binaries/classes/JARs remain read-only, qualified by supplied expected pin inventories and unchanged directory listings. Actual child query accounts are separate from process RSS. One full oracle graph is released after each verified gate. |
| failure | Cold mismatch, absent/wrong external qualification, real child failure, oracle discrepancy or final input drift stops receiving and retains evidence. No rebuild of immutable prefixes, native bypass, retry stack or synthetic success is added. |
| cost | Provenance/SQL/gate/checkpoint work is parent preparation/analysis. Actual child phase clocks include genuine API/format/parse work; process wall/RSS include startup, all passes and teardown. SQLite remains full recomputation with Python. JVM/JIT/cache/layout/scalar/framework differences preclude pure-dispatch or steady-state attribution. |
| Design | [Refactor.md §14.4](../../../../Refactor.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [docs/component_evaluation.md](../../../component_evaluation.md), [tools/component_workloads.py](../../../../tools/component_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py) |

## B0008

[Lines 244–264](../../../../tools/run_baseline_evaluation.py#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L244-L264:sha256:6882f141786974056fc3bf4dac6753572c6a0218c17cef49df4458708c49fad5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose finite matched-study controls with one diagnostic error boundary. |
| inputs / outputs | Required current source/build/native/cohort/output paths and optional legacy Java/classpath/qualification paths call run with explicit CPU/warmup/repetition/byte grants. |
| invariants | Optional legacy arguments are required only for actual legacy arms. The created-output marker permits failure writes only to this invocation, preserving rejected existing output. |
| ownership | Owns ordinary argparse values and the newly created process working directory; it does not own old baseline prefixes. |
| failure | Execution errors print a failure and mark an owned progress file failed; diagnostic I/O errors may propagate. No general exception/recovery framework. |
| cost | Cold CLI/boundary work, outside native updates. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [tests/integration/baseline_evaluation.py](../../../../tests/integration/baseline_evaluation.py) |

## B0009

[Lines 265–268](../../../../tools/run_baseline_evaluation.py#L265); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L268:sha256:8a794f2c6b77bf5133b639a55d99eb34900b5c835e6fff07e6a511fd4502719a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the study only when directly executed. |
| inputs / outputs | Module-name guard calls main and exposes its exit code. |
| invariants | Importing the decoder/checker starts no native jobs. |
| ownership | Only interpreter globals exist at this boundary. |
| failure | Preserves main success/failure status. |
| cost | Constant dispatch; no engine work. |
| Design | [tools/run_baseline_evaluation.py](../../../../tools/run_baseline_evaluation.py) |
