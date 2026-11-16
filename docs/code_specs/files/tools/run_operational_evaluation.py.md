# `tools/run_operational_evaluation.py` — block usage map

[Source](../../../../tools/run_operational_evaluation.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `dce61bc0e2f3ad7366311d277dcd58c19b0eb5435bfbbf1a37522b6937a0308a`. 441 lines partitioned into 31 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../tools/run_operational_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../tools/run_operational_evaluation.py#L21) | Callable definition: def save(path, value, exclusive=False): | calls open, write, dumps · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../tools/run_operational_evaluation.py#L24) | Explanatory comments or spacing. |  |
| [B0004 · 26–28](../../../../tools/run_operational_evaluation.py#L26) | Callable definition: def integer(value, maximum=2**64-1): | calls require, type; guard require(type(value) is int and 0 &lt;= value &lt;= maximum, 'invalid finite nonnegative counter'); returns value · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../tools/run_operational_evaluation.py#L29) | Explanatory comments or spacing. |  |
| [B0006 · 31–42](../../../../tools/run_operational_evaluation.py#L31) | Callable definition: def changed_paths(left, right, prefix=''): | calls isinstance, set, keys, add; returns result; set() if canonical(left) == canonical(right) else {prefix}; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–44](../../../../tools/run_operational_evaluation.py#L43) | Explanatory comments or spacing. |  |
| [B0008 · 45–49](../../../../tools/run_operational_evaluation.py#L45) | Callable definition: def causal_request(arm): | calls deepcopy, pop; returns {'adapter': arm\['adapter'\], **value} · [reviewed contract](#b0008) |
| [B0009 · 50–51](../../../../tools/run_operational_evaluation.py#L50) | Explanatory comments or spacing. |  |
| [B0010 · 52–101](../../../../tools/run_operational_evaluation.py#L52) | Callable definition: def admit_manifest(document, args): | calls require, type, get, isinstance; guard require(type(document.get('schema_version')) is int and document\['schema_version'\] == 1,; returns by_id; 7 loop sites · [reviewed contract](#b0010) |
| [B0011 · 102–103](../../../../tools/run_operational_evaluation.py#L102) | Explanatory comments or spacing. |  |
| [B0012 · 104–114](../../../../tools/run_operational_evaluation.py#L104) | Callable definition: def observation_key(actual, output): | calls canonical, in, else, require; guard require(isinstance(actual, dict) and set(actual) == set(keys), 'wrong set observation shape'); returns canonical(actual); {key: sorted(canonical(row) for row in actual\[key\]) for key in keys}; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 115–116](../../../../tools/run_operational_evaluation.py#L115) | Explanatory comments or spacing. |  |
| [B0014 · 117–124](../../../../tools/run_operational_evaluation.py#L117) | Callable definition: def wanted(frame, output): | calls ; returns frame\['cardinality'\]; {'rows': frame\['rows'\], 'delta': frame\['delta'\]} · [reviewed contract](#b0014) |
| [B0015 · 125–126](../../../../tools/run_operational_evaluation.py#L125) | Explanatory comments or spacing. |  |
| [B0016 · 127–129](../../../../tools/run_operational_evaluation.py#L127) | Callable definition: def plan_identity(report): | calls in; returns {key: report\[key\] for key in ('implementation', 'source_sha256', 'physical_sha256', 'binding_sha256…; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 130–131](../../../../tools/run_operational_evaluation.py#L130) | Explanatory comments or spacing. |  |
| [B0018 · 132–143](../../../../tools/run_operational_evaluation.py#L132) | Callable definition: def count_signature(value): | calls in; returns result; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 144–145](../../../../tools/run_operational_evaluation.py#L144) | Explanatory comments or spacing. |  |
| [B0020 · 146–238](../../../../tools/run_operational_evaluation.py#L146) | Callable definition: def check_report(report, arm, request, oracle, verify, reference=None): | calls get, require, all, in; guard require(report\['implementation'\] == expected\[arm\['adapter'\]\] and report\['command'\] == request\['comm…; returns {'identity': plan_identity(report), 'counts': count_signature(passes\[-1\]), 'checked_prefixes': chec…; 16 loop sites · [reviewed contract](#b0020) |
| [B0021 · 239–240](../../../../tools/run_operational_evaluation.py#L239) | Explanatory comments or spacing. |  |
| [B0022 · 241–251](../../../../tools/run_operational_evaluation.py#L241) | Callable definition: def cross_arm_checks(comparisons, arms, gates): | calls in, get, require; guard require(a == b, item\['id'\] + ': selected source/tree/backend differs'); 5 loop sites · [reviewed contract](#b0022) |
| [B0023 · 252–253](../../../../tools/run_operational_evaluation.py#L252) | Explanatory comments or spacing. |  |
| [B0024 · 254–272](../../../../tools/run_operational_evaluation.py#L254) | Callable definition: def stage_samples(report): | calls in, setdefault, append, integer; returns result; 5 loop sites · [reviewed contract](#b0024) |
| [B0025 · 273–274](../../../../tools/run_operational_evaluation.py#L273) | Explanatory comments or spacing. |  |
| [B0026 · 275–311](../../../../tools/run_operational_evaluation.py#L275) | Callable definition: def summarize(arm, reports, commands): | calls stage_samples, items, setdefault, extend; returns {'arm': arm\['id'\], 'adapter': arm\['adapter'\], 'measured_invocations': len(reports), 'physical_input…; 17 loop sites · [reviewed contract](#b0026) |
| [B0027 · 312–313](../../../../tools/run_operational_evaluation.py#L312) | Explanatory comments or spacing. |  |
| [B0028 · 314–416](../../../../tools/run_operational_evaluation.py#L314) | Callable definition: def run(args): | calls resolve, require, startswith, hasattr; guard require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linu…; growth new; 17 loop sites · [reviewed contract](#b0028) |
| [B0029 · 417–418](../../../../tools/run_operational_evaluation.py#L417) | Explanatory comments or spacing. |  |
| [B0030 · 419–437](../../../../tools/run_operational_evaluation.py#L419) | Callable definition: def main(): | calls ArgumentParser, in, add_argument, parse_args; returns 1; 0; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 438–441](../../../../tools/run_operational_evaluation.py#L438) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |

## B0001

[Lines 1–20](../../../../tools/run_operational_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:b17931fcc0a52885488b6d45b7436d6d36a46b49e0c500d9ceb30f97759175f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the finite operational experiment and reuse established resource/oracle primitives. |
| inputs / outputs | Imports standard Python support, independent cohort evaluation, exact ratios, Experiment, environment/build provenance, distributions and canonical JSON. |
| invariants | Module import starts no engine or timing; bytecode output is disabled. Measurement metadata is not planner/runtime correctness authority. |
| ownership | Names and constants belong to the parent Python process. Only later child adapters own native query state. |
| failure | Missing dependencies fail import; no replacement oracle or runtime is selected. |
| cost | Cold import and Python allocation are outside native query accounts and child API timers. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [tools/component_workloads.py](../../../../tools/component_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [Refactor.md §14.4](../../../../Refactor.md) |

## B0002

[Lines 21–23](../../../../tools/run_operational_evaluation.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:adecb12a6ccd58b9cd87b7c62fb2c4c5e020337ceaf093c1fde84f475089e58c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist inspectable requests and progress/receiving JSON in the new experiment packet. |
| inputs / outputs | Path, JSON-compatible value and optional exclusive creation produce sorted-key UTF-8 JSON with a newline. |
| invariants | Exclusive requests refuse collisions. Progress rewrites only this invocation's open packet; no fsync/atomic-publication contract is implied. |
| ownership | Owns ordinary parent serialization/file resources, separate from every native account. |
| failure | File/encoding/allocation failures propagate; a partial new diagnostic file can remain. |
| cost | Formatting/writing follows complete JSON size. Repeated checkpoints are harness overhead outside native child clocks. |
| Design | [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py), [docs/component_evaluation.md](../../../component_evaluation.md) |

## B0004

[Lines 26–28](../../../../tools/run_operational_evaluation.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:bb3d42379f20e9a61fff69be28c327a6545a91016f66d0aa0a9ac47555a4ed49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate raw counters before exact arithmetic or distribution summaries. |
| inputs / outputs | Returns the same int after requiring a finite nonnegative value no larger than the supplied maximum. |
| invariants | Bool, float, negative and over-limit values reject; nanoseconds/work remain exact integral samples. |
| ownership | Borrows one scalar and retains no query or result ownership. |
| failure | require raises ValueError on invalid data, preventing a completed experiment status. |
| cost | Constant bounded-counter checks in parent analysis; no native per-update hook. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py) |

## B0006

[Lines 31–42](../../../../tools/run_operational_evaluation.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L42:sha256:4e78a9078fb0d64c267d6fa0d4718e0d96c543d1cafb28f6d718dae6a11ed77c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify exact request changes for causal control admission. |
| inputs / outputs | Two JSON values plus dotted prefix return changed dictionary leaf paths; arrays compare as ordered wholes. |
| invariants | Missing entries, empty containers and type distinctions remain visible. Tuple/event order is never sorted away. |
| ownership | Reads input JSON; owns a result path set without mutating either request. |
| failure | Invalid JSON keys or canonicalization errors propagate; there is no fuzzy comparison or ignored arbitrary field. |
| cost | Cold traversal/serialization follows compared JSON, including complete event arrays. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [Refactor.md §14.4](../../../../Refactor.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py) |

## B0008

[Lines 45–49](../../../../tools/run_operational_evaluation.py#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L49:sha256:0ae3874abce195d4598bf1a81b77ee0c7e0641fbe9c4b39ca18ddf559a2aed00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Form the control-comparison view while excluding only fresh Session state paths. |
| inputs / outputs | Deep-copies an arm request, removes session.state_directory and includes actual adapter identity. |
| invariants | SQL/catalog/events/backend/output/grants remain causal inputs. State-directory variation grants no runtime equivalence. |
| ownership | Returns an owned parent JSON copy; frozen original requests remain unchanged. |
| failure | Malformed structure or allocation fails before native timing. |
| cost | One request-size cold copy, with no native row ledger. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../schemas/component-runtime-request-v1.schema.json), [docs/component_evaluation.md](../../../component_evaluation.md) |

## B0010

[Lines 52–101](../../../../tools/run_operational_evaluation.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L101:sha256:339a441649e1b169158b8207fcfc810a0145b742a1308ea83f057ecc9f002e3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit finite explicit arms and permitted one-factor contrasts before child execution. |
| inputs / outputs | Manifest plus CLI grants produce an id-to-arm map; pass counts cold-normalize to declared warmups and one measured pass before freezing. |
| invariants | Unique path-safe ids, verify command, bounded positive physical traces/capture grants, new-state placeholders and next-update-after-recovery are mandatory. Exact actual diff paths equal declared allowed output/update/recovery/SQL controls; events/catalog remain identical. |
| ownership | Parent owns and normalizes the manifest before any query owner exists; no live native object is edited. |
| failure | Malformed limits, duplicates, foreign controls, incorrect declared factors or unsupported axes reject before output/native work. |
| cost | Cold JSON scans/copies scale with requests and comparisons under explicit manifest/arm/event caps. Repeated event comparisons may rescan; no total linear-CPU theorem. |
| Design | [Refactor.md §14.4](../../../../Refactor.md), [docs/component_evaluation.md](../../../component_evaluation.md), [schemas/component-runtime-request-v1.schema.json](../../../../schemas/component-runtime-request-v1.schema.json), [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0012

[Lines 104–114](../../../../tools/run_operational_evaluation.py#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L114:sha256:dbc56534e3c1e273faaecba64bd0a661adf31dfc648fb9178b792b42d69b3b30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize unordered outer result collections without altering tuple semantics. |
| inputs / outputs | Observation plus output mode yields canonical cardinality, row/delta maps or sorted compressed/group records. |
| invariants | Only outer records sort; tuple cell/output order, numeric type, multiplicity and duplicate records remain visible. |
| ownership | Comparison strings/lists are parent verification memory, never measured child state. |
| failure | Wrong output modes or dictionary/vector shapes reject the gate rather than accepting a report flag. |
| cost | Output-sensitive canonicalization/sorting may retain full verification results; it is outside native timing. |
| Design | [docs/semantics.md](../../../semantics.md), [docs/weighted_enumeration.md](../../../weighted_enumeration.md), [docs/aggregates.md](../../../aggregates.md), [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0014

[Lines 117–124](../../../../tools/run_operational_evaluation.py#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L124:sha256:252582a83c59612b524504edbfbbbf4107c36593fdcdaa14cda9978335520823
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the independent oracle port matching the observation obligation. |
| inputs / outputs | Frame and output name select set cardinality/rows/delta, compressed bag, full groups or group replacements. |
| invariants | COUNT DISTINCT, bag multiplicity and group counts never substitute for one another. None service output verifies committed rows. |
| ownership | Borrows a frame owned by the parent independent evaluator. |
| failure | Unknown or missing ports fail instead of synthesizing empty expectations. |
| cost | Constant field selection and tiny dictionary construction; independent SQL computation is separate. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [tools/component_workloads.py](../../../../tools/component_workloads.py), [docs/annotations.md](../../../annotations.md) |

## B0016

[Lines 127–129](../../../../tools/run_operational_evaluation.py#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L129:sha256:83d0f78174165e20db35364a1587ac44b0255e3f2a3c69905ebd191d754d5d70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual exported source/plan/backend/semantics metadata for later equality checks. |
| inputs / outputs | Selects fixed implementation/source/physical/binding/tree/options/semantics/output fields from a report. |
| invariants | Identity is diagnostic binding, not certificate authority; check_report requires each promised adapter field. |
| ownership | Parent dictionary references owned decoded report metadata; no native owner is extended. |
| failure | Surrounding validation rejects missing required fields; no identity is invented. |
| cost | Fixed key projection with shared nested Python values; no re-planning. |
| Design | [docs/query_identity.md](../../../query_identity.md), [docs/component_evaluation.md](../../../component_evaluation.md) |

## B0018

[Lines 132–143](../../../../tools/run_operational_evaluation.py#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L143:sha256:db22f99d48859f2f5bafbecb29f921854fe5c1ffd1400e7cd0a053546b6ae2d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain output/progress obligations independently of clocks and memory. |
| inputs / outputs | Pass yields output/internal-delta/serialized/progress values and selected epoch/transaction/transport scalar counters. |
| invariants | Source offsets, transaction sequence, observation and restart/checkpoint markers stay separate. State paths/account/clocks are excluded. |
| ownership | Owns parent scalar dictionaries and no result tuple ledger. |
| failure | Malformed nested report data raises an error; unequal verified/measured signatures reject the run. |
| cost | One metadata traversal per pass, proportional to epochs/transactions, outside child account/timers. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [examples/component-runtime/native_rows.cpp](../../../../examples/component-runtime/native_rows.cpp), [examples/component-runtime/session.cpp](../../../../examples/component-runtime/session.cpp) |

## B0020

[Lines 146–238](../../../../tools/run_operational_evaluation.py#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L238:sha256:7ea44fe5544ba71b44b966e50849a1021ce24896003df6f8759d3cc8c51b0a39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate actual native observations and lifecycle schedules against independent SQL prefixes. |
| inputs / outputs | Report/arm/request/oracle/reference yield selected identity, count signature and checked-prefix count. |
| invariants | Requires actual source/tree/backend metadata, command/output, fresh-owner warmup markers and null-versus-real clocks. Rows preserve replacement ranges and common endpoints; physical arms preserve every commit. Exact typed records and output counters match SQL; unobserved/measure capture stays null. Session progress, checkpoint/restart, serialization and durable prefix/root must be real. |
| ownership | Comparison/oracle DTOs belong to the parent. Children retain query accounts and exclusive state; files/status supplement exact observation checks. |
| failure | Any content/shape/count/schedule/binding/durable-state or preflight-measure discrepancy fails the gate; no correct=true report authority. |
| cost | Verification is output-sensitive across every prefix and warmup/measured pass; timing validation scans counts/metadata. It neither adds a measured row ledger nor equates account bytes with RSS. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [docs/component_evaluation.md](../../../component_evaluation.md), [docs/session_lifecycle.md](../../../session_lifecycle.md), [docs/aggregates.md](../../../aggregates.md), [docs/weighted_enumeration.md](../../../weighted_enumeration.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0022

[Lines 241–251](../../../../tools/run_operational_evaluation.py#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L251:sha256:d4bc7e2746215a101d43ef7f513e411b69e5f7f15e46097d0579e2462c0668c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require matching selected structures and common physical endpoints for applicable contrasts. |
| inputs / outputs | Declarations, arms and verified gates either accept or report actual source/tree/backend/boundary differences. |
| invariants | Identical-program same-adapter comparisons keep exported ids/tree/options equal. Rows single/net preserve common observation ends. Different SQL-semantic representations are not presumed structurally identical. |
| ownership | Borrows finite metadata and retains no engine owner. |
| failure | Any mismatch stops before timing. |
| cost | Cold traversal of finite comparison/endpoint metadata; no native reanalysis. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [docs/query_identity.md](../../../query_identity.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0024

[Lines 254–272](../../../../tools/run_operational_evaluation.py#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L272:sha256:e2f17a6c25afcfd62228c526d7ca517f144e6bb67a318f39a03fe519e66333ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect native clocks in actual owner, physical, transaction and transport units. |
| inputs / outputs | Measured report yields nonnegative raw stage samples, plus charged-load/update phase subdivisions when exported. |
| invariants | Warmups are excluded. Nested output/wait and duplicated epoch/transaction output clocks remain separately named and cannot be summed as disjoint work; crossing-phase transactions are labelled mixed. |
| ownership | Parent sample vectors retain scalar clocks only. |
| failure | Nonintegral/negative clocks reject; missing/null stages remain unavailable. |
| cost | One report metadata traversal and scalar sample storage, outside child clocks. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/component_evaluation.md](../../../component_evaluation.md), [examples/component-runtime/session.cpp](../../../../examples/component-runtime/session.cpp) |

## B0026

[Lines 275–311](../../../../tools/run_operational_evaluation.py#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L275-L311:sha256:e0012ce0e9becbe7b0eaaafe7e77b8acd19615913fc0c15084d9a2233216e31f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish exact common-input costs and distributions with honest work/memory scopes. |
| inputs / outputs | Arm reports and process records yield rational loop ns/input, stage/shared-setup distributions, real work counters, account samples, output counts and RSS. |
| invariants | Only measured owners contribute pass samples. Actual row native/source work remains per transaction; unavailable counters stay null. Before/after samples identify reconstruction; final-owner peak is not whole-pass peak, and sampled cross-owner maxima are separately labelled. |
| ownership | Analysis arrays are parent memory. Query-account requested bytes exclude compiler/report/caller memory; process RSS includes setup, all passes/owners/report/teardown. |
| failure | Missing/invalid measured clocks or counters prevent a valid summary; no latency/memory fallback is invented. |
| cost | Analysis scales with retained reports/samples. Fraction avoids ratio rounding and distribution retains declared percentile method; measurements prove no asymptotic bound. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/query_memory.md](../../../query_memory.md), [docs/component_evaluation.md](../../../component_evaluation.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0028

[Lines 314–416](../../../../tools/run_operational_evaluation.py#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L314-L416:sha256:706be54c8a0b1b126ae85affa1ae6b1b3a8e73a71b6c64a0ae8fef79e6efc6e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a source-bound finite experiment with a global correctness-before-timing barrier. |
| inputs / outputs | CLI/tool paths and cohorts produce a new packet of frozen requests, real process/resource records, exact gates, measured invocations, summaries and pairwise ratios. |
| invariants | Every arm and unique supplemental signed-service control passes before timing. Supplemental controls change only output/new state, retain physical identity and stay outside measured none-output obligations. Seeded rotations give identical fresh-owner warmups plus one measured pass per fresh process. Manifest/request/input/harness/launcher hashes bind runs; B04 acceptance remains false. |
| ownership | Parent owns oracle snapshots/DTOs/files; actual child adapters alone own native queries, WAL and sinks. Each invocation has an exclusive state path; old SDK/baseline/evidence is untouched. |
| failure | Admission, child/oracle failure or input drift retains diagnostics and prevents completion; no retry, native bypass, substitute engine or rollback framework. |
| cost | Build/provenance/SQLite/checkpoint analysis is separate harness work. Native phase clocks charge actual prepare/consolidation/output/recovery; process wall/RSS include all child work. Raw-byte caps apply after exit and exclude state files. Finite cohorts are not all-ten-axis or pure-dispatch proof. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/component_workloads.py](../../../../tools/component_workloads.py), [schemas/component-runtime-request-v1.schema.json](../../../../schemas/component-runtime-request-v1.schema.json), [docs/component_evaluation.md](../../../component_evaluation.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0030

[Lines 419–437](../../../../tools/run_operational_evaluation.py#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L419-L437:sha256:c715b264248b19945bcc3cf143e5d440be1229605c976e13b65537e4ab179bc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose finite CLI controls and one cold diagnostic failure boundary. |
| inputs / outputs | Required source/build/tool/cohort/new-output paths and affinity/repetition/grant flags invoke run and return an exit code. |
| invariants | Timing requires explicit CPU. Only a successfully created invocation-owned output may receive a failed-progress update; rejected reuse cannot rewrite prior receiving. |
| ownership | Argparse/configuration is parent-owned; the private creation marker is excluded from public configuration. |
| failure | Expected execution errors print a diagnostic and mark an owned packet failed. Diagnostic I/O failure may itself propagate; no exception/retry stack is added. |
| cost | Cold parse/boundary work only; no native per-update handler. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tests/integration/operational_evaluation.py](../../../../tests/integration/operational_evaluation.py) |

## B0031

[Lines 438–441](../../../../tools/run_operational_evaluation.py#L438); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L441:sha256:8a794f2c6b77bf5133b639a55d99eb34900b5c835e6fff07e6a511fd4502719a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the operational command only when executed as a script. |
| inputs / outputs | Module-name guard calls main and exposes its return through SystemExit. |
| invariants | Importing check helpers starts no native or timing jobs. |
| ownership | No additional persistent owner is created. |
| failure | Preserves main exit status. |
| cost | Constant script dispatch. |
| Design | [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py), [tests/integration/operational_evaluation.py](../../../../tests/integration/operational_evaluation.py) |
