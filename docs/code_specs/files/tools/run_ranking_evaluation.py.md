# `tools/run_ranking_evaluation.py` — block usage map

[Source](../../../../tools/run_ranking_evaluation.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `aae58992c79bc2dd5204789ff749d1d879906f2fae07fccc1195ef98d4c68099`. 210 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../tools/run_ranking_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–22](../../../../tools/run_ranking_evaluation.py#L22) | Callable definition: def save_json(path,value):path.write_text(json.dumps(value,ensure_ascii=False,sort_keys=True,indent=2)+'\n') | calls write_text, dumps · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../tools/run_ranking_evaluation.py#L23) | Callable definition: def request_file(path,value): | calls open, write, canonical · [reviewed contract](#b0003) |
| [B0004 · 25–25](../../../../tools/run_ranking_evaluation.py#L25) | Module statements. | source comment (unverified): # Query-account peak is cumulative requested bytes, distinct from process RSS. · [reviewed contract](#b0004) |
| [B0005 · 26–33](../../../../tools/run_ranking_evaluation.py#L26) | Callable definition: def run_costs(report): | calls require, sum, max, Fraction; guard epochs=report\['epochs'\];require(epochs,'empty measured trace'); returns {'event_active_ns_per_input':Fraction(active,len(epochs)),; 3 loop sites · [reviewed contract](#b0005) |
| [B0006 · 34–42](../../../../tools/run_ranking_evaluation.py#L34) | Callable definition: def primary_scores(policy,candidates): | calls get, require, len, str; guard require(len(assessments)==1,'native policy has no unique primary assessment'); returns result; 3 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–200](../../../../tools/run_ranking_evaluation.py#L43) | Callable definition: def main_run(args): | calls resolve, require, startswith, hasattr; guard require(sys.platform.startswith('linux') and hasattr(os,'wait4'),'held-out runner requires Linux wa…; returns sum((row\[objective\] for row in values),Fraction())/len(values); 55 loop sites; source comment (unverified): # Choices stay frozen for both roles; evaluation also rechecks frozen calibration. · [reviewed contract](#b0007) |
| [B0008 · 201–207](../../../../tools/run_ranking_evaluation.py#L201) | Callable definition: def main(): | calls ArgumentParser, add_argument, main_run, parse_args; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 208–210](../../../../tools/run_ranking_evaluation.py#L208) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–21](../../../../tools/run_ranking_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define C07 training/calibration/held-out measurement orchestration and exact analysis dependencies. |
| inputs / outputs | Imports trusted sibling helpers, disables bytecode writes and defines three explicit objective units; guarded CLI only. |
| invariants | Native C05 choices use training only, fit uses calibration only, held-out evaluation cannot refit/select; C03/C04/C06 remain disabled in packet. |
| ownership | Owns module imports and objective dict; subsequent owning packets/Fractions/processes are ordinary Python resources. |
| failure | Import/type/OOM errors propagate before main wrapper. |
| cost | Fixed imports/three-objective setup; no benchmarks at import. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
OBJECTIVES={'event_active_ns_per_input':'nanoseconds_per_physical_input',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name exact observed objectives and their units. |
| inputs / outputs | OBJECTIVES maps two per-input nanosecond costs and one native cumulative requested-byte peak to units. |
| invariants | Units differ from RSS, future-memory prediction or structural height; objective names do not grant eligibility or choose a native plan. |
| ownership | Owning three-entry dict of immutable strings. |
| failure | Import allocation failure only; report lookup errors occur later. |
| cost | Fixed dict setup; no arithmetic/scan/native execution. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 22–22](../../../../tools/run_ranking_evaluation.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def save_json(path,value):path.write_text(json.dumps(value,ensure_ascii=False,sort_keys=True,indent=2)+'\n')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a complete C07 JSON artifact with deterministic formatting. |
| inputs / outputs | Path and JSON graph in; overwrites UTF8 sorted-key pretty text plus newline. |
| invariants | No exclusive create/atomic rename/fsync; caller freezes content by hashing/checking later. |
| ownership | Owns serialized Unicode temporary; graph borrowed, file persists. |
| failure | IO/JSON/encoding/OOM errors propagate; partial file may remain. |
| cost | O(encoded graph bytes) serialization/write plus object-key sorting. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 23–24](../../../../tools/run_ranking_evaluation.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def request_file(path,value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one new compact canonical request without overwriting an existing path. |
| inputs / outputs | Path/value in; exclusive text open x and canonical serialization write. |
| invariants | Existing path fails; exclusive creation does not imply atomic complete content or durability. |
| ownership | Owns file handle/serialized string; captured request graph borrowed. |
| failure | Existing-path/IO/JSON/OOM failure propagates; file context closes but partial file retained. |
| cost | O(request bytes) serialization/write; no native work. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 25–25](../../../../tools/run_ranking_evaluation.py#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:9f602acdcd54c05c1aafb29e7b37ff96cf6d547a8d30cbc6943c0ba0dc74b618
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Query-account peak is cumulative requested bytes, distinct from process RSS. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [docs/ranking.md](../../../ranking.md), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 26–33](../../../../tools/run_ranking_evaluation.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_costs(report):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive exact observed per-input costs and cumulative query-account peak from one collector report. |
| inputs / outputs | Report with nonempty epochs in; objective-&gt;Fraction map plus integer totals out. |
| invariants | Active ns includes declared phase envelope; native objective sums prepare+epoch release. Peak maxes initial/final/all epoch cumulative peaks, not process RSS or predicted future state. |
| ownership | Borrows report; owns Fraction/map results and scalar sums. |
| failure | ValueError on empty epochs; missing/type/arithmetic/OOM errors propagate. |
| cost | O(epochs) three scans/sums and max expansion; per-input exact Fraction normalization uses big integers. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 34–42](../../../../tools/run_ranking_evaluation.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def primary_scores(policy,candidates):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the native exporter's unique primary proxy assessment and bind it to retained candidates. |
| inputs / outputs | Policy assessment DOM and candidate records in; index-string-&gt;exact Fraction proxy map out. |
| invariants | Exactly one purpose0/2 assessment; every scored structural key must be retained and denominator positive; all retained candidate indices covered. Labels/JSON alone do not grant typed/native proof authority. |
| ownership | Owns key/index maps, filtered assessments list and Fractions; input exporter graph borrowed. |
| failure | ValueError on missing/foreign/unavailable/incomplete scores; JSON key/int/arithmetic/OOM errors propagate. |
| cost | O(candidates+score rows) map construction and integer-string parsing/Fraction gcd; duplicate-key handling is actual dict replacement, not an independent uniqueness proof. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 43–200](../../../../tools/run_ranking_evaluation.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main_run(args):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native training choices and calibration before evaluating all verified measured candidates on disjoint traces. |
| inputs / outputs | Parsed explicit binaries/source/split/output/grants in; writes complete/failed C07 packet plus raw command evidence. |
| invariants | Verifies split/provenance; all retained candidates across splits/modes preflight before measurement, failure stops rather than excludes. Original certificate/height/backend bindings checked. Frozen hashes enforced; shared query families are not query-family holdout. |
| ownership | Owns bound trace DOMs/files, exports/candidate artifacts, all oracle snapshots/receipts, samples, exact models and full packet; filesystem retains partial/failed evidence. |
| failure | Inside try, Exception sets failed/error/time, saves and rethrows; save failure may mask original. Earlier argument/provenance errors precede packet; no cleanup/transaction of output pack. |
| cost | Full split regeneration/two-oracle replay, provenance hashes, exporter/preflight subprocess matrix, warm/measured collectors, sink comparisons and O(candidates²) pair analyses; all capture/DOM/model allocations explicit offline work. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def save():save_json(output/'experiment.json',packet)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist current C07 experiment progress/status. |
| inputs / outputs | Captured packet/output in; save_json overwrites experiment.json. |
| invariants | No implicit success from DTO status; hashes/receipts/checks supply only their actual finite authority. |
| ownership | Packet borrowed; serialized full temporary owned; filesystem artifact retained. |
| failure | IO/JSON/OOM errors propagate even in failure branch; no transaction. |
| cost | O(cumulative packet bytes) rewrite each progress point. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def measure_role(role):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect warm/measured repetitions for one split role while rechecking frozen choice/calibration bindings. |
| inputs / outputs | Role calibration/evaluation plus captured combinations/grants in; appends run records and measured-only sample/totals maps. |
| invariants | Deterministic SHA schedule per repetition; evaluation checks frozen calibration too. Verifies binding/request/backend/mode/affinity/row counts and optional JSONL sink content after timed collector work. |
| ownership | Owns selected/sorted combo lists, per-run requests/capture DOMs and retained run/sample records; expected oracles/combos borrowed. |
| failure | Hash/context/sink discrepancy raises and aborts enclosing packet; Experiment retains command files first. No silent discard of failing candidate/run. |
| cost | Repetitions×selected combos native collectors plus repeated frozen-file hashes, full epoch scans and optional sink parse/sort; warmups consume same work/files but excluded from samples. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def mean_cost(case,backend,mode,candidate,objective):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Average the exact observed costs for a fully measured candidate/context. |
| inputs / outputs | Case/backend/mode/candidate/objective in; exact Fraction mean out from captured samples. |
| invariants | Requires exactly requested measured repetitions; warmups are absent from this map. |
| ownership | Borrows sample arrays; owns composite key and Fraction sum/result. |
| failure | Missing/incorrect repetition count ValueError or lookup/arithmetic/OOM propagates. |
| cost | O(repetitions) exact rational additions and division, repeated for policy/objective analyses. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 201–207](../../../../tools/run_ranking_evaluation.py#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse explicit C07 candidate, split, collector and grant options. |
| inputs / outputs | Required source/build/crown/collector/exporter/output plus optional query/backend/mode/reps/family/slot/codec/sink/time/byte arguments in. |
| invariants | Parser limits label choices; main_run enforces numeric/context bounds and never enables C03/C04/C06. |
| ownership | Owns parser/args; main_run owns all benchmark evidence. |
| failure | Usage exits through argparse; operational failures reach guarded script handler. |
| cost | Fixed parser work then full main_run, no native work for --help. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 208–210](../../../../tools/run_ranking_evaluation.py#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the C07 held-out evaluator only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Exception from main prints C07 diagnostic and exits1; SystemExit/KeyboardInterrupt pass through and retained artifacts are not removed. |
| cost | Fixed wrapper work; benchmark cost is in main_run/Experiment. |
| Design | [tools/run_ranking_evaluation.py](../../../../tools/run_ranking_evaluation.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [schemas/ranking-evaluation-v1.schema.json](../../../../schemas/ranking-evaluation-v1.schema.json), [docs/code_review.md](../../../code_review.md) |
