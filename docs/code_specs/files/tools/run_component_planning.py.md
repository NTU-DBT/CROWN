# `tools/run_component_planning.py` — block usage map

[Source](../../../../tools/run_component_planning.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `fe516d0e31a1e89ce638e6be1edecc8b81d6ed02603d2a83db25c93cb5715c92`. 333 lines partitioned into 17 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../tools/run_component_planning.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../tools/run_component_planning.py#L22) | Callable definition: def save(path, value, exclusive=False): | calls open, write, dumps · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../tools/run_component_planning.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–36](../../../../tools/run_component_planning.py#L27) | Callable definition: def training_demand(catalog, events): | calls enumerate, Counter, require, range; guard require(event\['table'\] in tables and event\['operation'\] in \['insert', 'delete'\], 'unknown training …; returns \[{'table': index, 'operation': operation, 'inputs': counts\[index, operation\]}; growth insert; 4 loop sites · [reviewed contract](#b0004) |
| [B0005 · 37–38](../../../../tools/run_component_planning.py#L37) | Explanatory comments or spacing. |  |
| [B0006 · 39–56](../../../../tools/run_component_planning.py#L39) | Callable definition: def retained(exported): | calls require, append, enumerate; guard require(candidate\['height'\] == exported\['proved_height'\], 'minimum family contains taller candidate…; returns rows; 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 57–58](../../../../tools/run_component_planning.py#L57) | Explanatory comments or spacing. |  |
| [B0008 · 59–70](../../../../tools/run_component_planning.py#L59) | Callable definition: def retained_identity(exported): | calls ; returns {'source': exported\['source_sha256'\], 'catalog': exported\['catalog_sha256'\],; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 71–72](../../../../tools/run_component_planning.py#L71) | Explanatory comments or spacing. |  |
| [B0010 · 73–88](../../../../tools/run_component_planning.py#L73) | Callable definition: def check_report(report, request, artifact, artifact_path, trace, backend): | calls require, digest, len; guard require(report\['request'\] == request and report\['backend'\] == backend, 'collector request/backend d… · [reviewed contract](#b0010) |
| [B0011 · 89–90](../../../../tools/run_component_planning.py#L89) | Explanatory comments or spacing. |  |
| [B0012 · 91–131](../../../../tools/run_component_planning.py#L91) | Callable definition: def analyze(exported, frozen, samples, traces, repetitions): | calls items, require, len, sum; guard require(len(values) == repetitions, 'missing measured candidate repetition'); returns result; 15 loop sites · [reviewed contract](#b0012) |
| [B0013 · 132–133](../../../../tools/run_component_planning.py#L132) | Explanatory comments or spacing. |  |
| [B0014 · 134–315](../../../../tools/run_component_planning.py#L134) | Callable definition: def run(args): | calls resolve, require, startswith, hasattr; guard require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linu…; 45 loop sites · [reviewed contract](#b0014) |
| [B0015 · 316–317](../../../../tools/run_component_planning.py#L316) | Explanatory comments or spacing. |  |
| [B0016 · 318–328](../../../../tools/run_component_planning.py#L318) | Callable definition: def main(): | calls ArgumentParser, add_argument, run, parse_args; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 329–333](../../../../tools/run_component_planning.py#L329) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |

## B0001

[Lines 1–21](../../../../tools/run_component_planning.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:fc4b8a54d7ab414fe4ca3802c3faece2fc433adff3730c300123110a5c48fb0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce the offline B04 dependency runner and reuse existing provenance, scheduling and exact analysis primitives. |
| inputs / outputs | Imports CLI/file/time helpers, exact Fraction, root-owned freeze_choices and existing C07/B03 helpers. |
| invariants | No engine command runs during import. This module neither installs plans nor enables C05 maintenance_cost; the full ten-axis B04 gate remains open. |
| ownership | Only Python module definitions and immutable references are retained here; native owners exist solely in later child processes. |
| failure | Required import failure stops the script; no dependency fallback or partial native result is manufactured. |
| cost | Cold Python import/setup. Native work, model collection and file I/O occur only in explicit driver functions. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0002

[Lines 22–24](../../../../tools/run_component_planning.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:cf75089366ab9fe3212384eefc8c2b06625217b1e4d4779a4be8e428707b7020
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a packet/checkpoint or create a frozen/request document exclusively. |
| inputs / outputs | Takes a Path, JSON-compatible value and exclusive flag; writes sorted UTF-8-preserving indented JSON. |
| invariants | Frozen/request files use exclusive creation, while experiment progress intentionally rewrites only its new task-local checkpoint. |
| ownership | The caller owns the Path/value; a local file context owns the stream until write/close completes. |
| failure | Existing exclusive paths, serialization, disk or close errors propagate and stop the experiment. |
| cost | Visits/sorts/serializes the document; host output storage is separate from native account bytes and RSS measurements. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0004

[Lines 27–36](../../../../tools/run_component_planning.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L36:sha256:87b89911a85c2129c719898e43888cfe3bb7145c4fe3391355b6d409f10fceb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the forecast input demand from the TRAIN physical input mix only. |
| inputs / outputs | Canonical catalog table order and TRAIN events produce one insert/erase row per physical table, including explicit zero counts. |
| invariants | Delete maps to native erase. Every training input counts once, including no-ops; neither evaluation trace length nor output rows determine demand. Canonical catalog uniqueness was already validated by the native CLI. |
| ownership | Returns fresh scalar dictionaries and a new list; input catalog/events are borrowed and unchanged. |
| failure | Unknown table/op and empty training input reject before exporting a model request. |
| cost | One pass over training events plus two rows per table; no per-update engine hook, row ledger or evaluation-data model fitting. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0006

[Lines 39–56](../../../../tools/run_component_planning.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L56:sha256:f21a1ca8d3c6810abbda28da0884a2b6c0ecc8132aa37f0aeee73284ee5a9f7f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain every native minimum-family and ordinary-upper origin without granting JSON proof authority. |
| inputs / outputs | Consumes the genuine source-bound export and returns all candidate/control records augmented with family/key/provenance or ordinary-root origin. |
| invariants | Minimum-family height equals independently reported h*, ordinary height is at least h*, all artifacts retain the unchanged original certificate and advertised physical/actual-height bindings. Real authority is independently re-established by collector preflight. |
| ownership | Returns new row dictionaries containing borrowed immutable export payload references; the export remains alive through setup. No CandidateCache or cross-family native handle is reused. |
| failure | Inconsistent producer metadata aborts; candidates are never silently removed to recover a passing subset. |
| cost | Visits each retained record and compares its existing JSON proof; copying container headers and later serialization are cold tool costs. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0008

[Lines 59–70](../../../../tools/run_component_planning.py#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L70:sha256:609d9501145d8ea321088a9c4fe555ba6b65edd2e773aa522d2466f9284a8fb8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the strict source/proof/family/artifact/control identity boundary between preliminary and qualified exports. |
| inputs / outputs | Returns original source/train/calibration hashes, proved height/certificate, complete candidates and family coverage identities, plus ordinary candidates/rejections/exhaustion. |
| invariants | Timing, collected profile stamps and fitted coefficients may differ between passes; every actual physical artifact, original proof, key/provenance and retained ordinary control must agree exactly. |
| ownership | The returned structure borrows nested export JSON until the immediate equality comparison; it is never exposed as a persistent frozen choice. |
| failure | Missing required exporter fields raises before qualified choices can be frozen; mismatches abort the caller. |
| cost | Cold dictionary/list construction and complete JSON equality can scale with proof and candidate payload size. It is not a constant-time identity or cryptographic build-lineage proof. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0010

[Lines 73–88](../../../../tools/run_component_planning.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L88:sha256:ada1a20d12b84e2f35dd1a7da1d5bc23dd33974e8bc6c7d0a5d57926881725df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join each real collector report to its exact request, artifact, source horizon and backend. |
| inputs / outputs | Receives parsed report, original request/document/paths, trace metadata and backend; returns only after all context checks pass. |
| invariants | Physical/artifact/input hashes, full request, final sequence/source positions and zero-output maintenance mode must match. V3 requires exact checked-upper-only original/actual/gap metadata; old minimum reports omit that field. |
| ownership | Borrows caller-owned JSON and Paths; hash reads return temporary strings and retain no runtime owner. |
| failure | Any mislabeled binding, horizon, output demand or height metadata aborts; report flags do not waive native preflight. |
| cost | Cold file hashing and finite metadata comparisons per completed child run; no measured native work is inserted by this helper. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0012

[Lines 91–131](../../../../tools/run_component_planning.py#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L131:sha256:606a60e5ea5d7f1086052fb961ee3a7a2d7198d48a2753e5a2642c44cb08d6ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare frozen C02/C03 decisions with actual held-out measured native costs without refitting. |
| inputs / outputs | Final export/frozen choices, per-physical trace repetitions and evaluation traces produce per-family/statistics/policy regret, C03 prediction/error and C02 ordering rows. |
| invariants | Actual cost is prepare/commit plus epoch release nanoseconds per physical input. C03 total forecast divides by TRAIN demand count; unknown or known-budget-excluded scores are omitted rather than set to zero. C02 keeps native structural units and no nanosecond prediction error. Regret compares retained verified family candidates, excluding explicit C03 as-of memory exclusions; future memory remains unknown. |
| ownership | Creates fresh analysis JSON; reads original/frozen reports and exact Fraction samples without mutating a choice or model. All four statistics variants use the same final calibration fit. |
| failure | Missing repetitions, foreign selected keys or malformed exact ratios reject analysis. Unavailable choices/errors remain null, not fabricated successful scores. |
| cost | Exact rational aggregation/error operations and pairwise ordering are cold evaluation work. No native query installation, new model fitting or global cost theorem occurs. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0014

[Lines 134–315](../../../../tools/run_component_planning.py#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L315:sha256:c9ab62bed7f6937f53b2a548a132a4ef7ad6422d959d1db86bb9b97039458b50
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the complete bounded two-pass, all-retained-plan correctness and held-out measurement protocol. |
| inputs / outputs | CLI paths/grants and the deterministic C07 split produce a new experiment directory with raw commands, artifacts, frozen choices/calibration, runs, summaries and explicit unavailable groups. |
| invariants | Verify source/build/split provenance first. Demand comes only from TRAIN. Preliminary calibration is unqualified preparation; every retained V2/V3 envelope and every split oracle is preflighted before final export/calibration. Complete identities must persist before freezing. Missing/empty exact/residual/meta families retain raw stop evidence and receive no heldout timing. Every ordinary control is retained; only actual run physical SHA is deduplicated. All available groups finish correctness before the balanced heldout schedule. |
| ownership | One fresh directory owns request/report/evidence files. Experiment owns each subprocess until wait completes. Runtime groups retain final exports, genuinely frozen deep-owning choices and samples; native owners exist in child invocations and are torn down there. |
| failure | Refuse overwrite, stale build inputs, unsupported Linux/grants/affinity, wrong source/identity, failed preflight, resource/output failures or freeze changes. Save failed progress and propagate once; never retry by dropping an artifact or changing a policy. Unproved/budget-limited groups are explicit unavailable results, not full B04 acceptance. |
| cost | Charge both setup passes once and retain all raw stdout/stderr/process RSS; preliminary model timings are excluded from eligible comparisons. Fixed maintenance/off/full-counters/none/discard demand matches native C03 calibration. Warmups are retained/excluded; summaries preserve actual integer totals and cumulative requested-byte peaks. All ten axes remain open and no fixed speedup, global optimum or confidence is claimed. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0016

[Lines 318–328](../../../../tools/run_component_planning.py#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L318-L328:sha256:13d14db469184329cce444d3e13d43d3e6d7c9c99fa809d4a814b1c5a0adbb07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the bounded public experiment CLI while keeping its measured context fixed. |
| inputs / outputs | Parses six required source/build/executable/output paths plus optional C07 query/backend/resource/repetition/preflight flags, then calls run. |
| invariants | Backend choices are the two native storage contracts. There is no caller flag to replace maintenance/off/full-counters/none/discard, inject evaluation-derived demand or enable a production cost policy. |
| ownership | ArgumentParser owns parsed scalar/Path/list DTOs. run records requested paths/flags and resolved query/backend selection; absolute execution paths are separately bound by actual build/command provenance. |
| failure | Unknown/malformed options fail argparse; semantic numeric/affinity/source checks occur before creating the experiment directory. |
| cost | Cold argument parsing only; actual time/resource scopes are explicit in run. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0017

[Lines 329–333](../../../../tools/run_component_planning.py#L329); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L329-L333:sha256:99025478942c46f325bf8114f0d45136a820f63852bc71866692e539612e5150
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one script-level error exit without wrapping native work in additional retry machinery. |
| inputs / outputs | __main__ invokes main; a propagated exception prints a B04 dependency diagnostic and exits one. |
| invariants | Importing the module never invokes the driver; a success message is printed only after terminal packet state is saved. |
| ownership | No process/query owner is retained by this guard; run and Experiment own those lifetimes. |
| failure | Errors remain failures with retained command/progress files where available; no success flag, fallback artifact or modified baseline is synthesized. |
| cost | One cold application boundary, with ordinary stderr formatting only on failure. |
| Design | [docs/measurement.md](../../../measurement.md), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../maintenance_cost.md), [docs/statistics.md](../../../statistics.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |
