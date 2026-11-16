# `tools/run_adversarial_scalability.py` — block usage map

[Source](../../../../tools/run_adversarial_scalability.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `bfe8adfbcbae2779e69b306b7446d2a49c6f98468589e84d129ac0d6d1a60d5c`. 153 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../tools/run_adversarial_scalability.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 32–35](../../../../tools/run_adversarial_scalability.py#L32) | Callable definition: def digest(path): | calls open, file_digest, hexdigest; returns hashlib.file_digest(stream, 'sha256').hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 36–37](../../../../tools/run_adversarial_scalability.py#L36) | Explanatory comments or spacing. |  |
| [B0004 · 38–130](../../../../tools/run_adversarial_scalability.py#L38) | Callable definition: def run(args): | calls resolve, Path, ValueError, len; returns child.returncode; 0; 10 loop sites · [reviewed contract](#b0004) |
| [B0005 · 131–132](../../../../tools/run_adversarial_scalability.py#L131) | Explanatory comments or spacing. |  |
| [B0006 · 133–149](../../../../tools/run_adversarial_scalability.py#L133) | Callable definition: def main(): | calls ArgumentParser, add_argument, Path, resolve; returns run(parser.parse_args()) · [reviewed contract](#b0006) |
| [B0007 · 150–153](../../../../tools/run_adversarial_scalability.py#L150) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–31](../../../../tools/run_adversarial_scalability.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the parameterized B05 batch runner and its explicit CLI, replacing the former fixed wrapper. |
| inputs / outputs | Imports B05 family/pack builder; direct CLI requires explicit build/output and accepts suite/family/scale/backend/mode/repetition/warmup/seed/observation/CPU selectors. |
| invariants | Import sets dont_write_bytecode and imports generator but starts no batch. run() requires this checkout, never searches private build directories, records per-point child receipts, and completes only after child gates/source pins. |
| ownership | Module owns definitions/imports; run owns packet/generated Python values; filesystem owns receipts. No engine account is added. |
| failure | Import errors precede CLI. run exceptions can leave incomplete output; nonzero children are journaled and stop batch. No broad wrapper catch. |
| cost | Imports until direct execution; selected family/scale points each generate a pack and launch a sequential B03 child. No engine instrumentation. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
sys.dont_write_bytecode = True
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable bytecode writes in the batch-runner process. |
| inputs / outputs | Sets the current interpreter flag before generator import. |
| invariants | Suppresses normal .pyc writes only; pack/packet artifacts remain enabled. |
| ownership | Interpreter state is process-local. |
| failure | No local catch; import/run failures are separate. |
| cost | One assignment. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
from generate_adversarial_workloads import FAMILIES, build
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load B05 family names and in-memory pack builder. |
| inputs / outputs | Imports FAMILIES/build; generator root check runs during import, but its CLI does not. |
| invariants | Batch work begins only in run(). |
| ownership | Imported objects stay in module state. |
| failure | Import/loader failures propagate before output creation. |
| cost | One module load and imports. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
SUITES = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map suite names to fixed family tuples. |
| inputs / outputs | Suite string selects a tuple; all names FAMILIES. --family overrides suite. |
| invariants | run() rejects duplicate family selectors; there is no implicit build search. |
| ownership | Module owns a dict whose values are fixed family tuples; the dict itself is mutable Python state. |
| failure | Argparse rejects unknown suite; duplicate check is in run(). |
| cost | Fixed small constant storage. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0002

[Lines 32–35](../../../../tools/run_adversarial_scalability.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact file bytes for source/child receipt binding. |
| inputs / outputs | Path in; lowercase SHA-256 out. |
| invariants | Digest binds bytes, not semantics or build lineage. |
| ownership | File is closed within the call. |
| failure | Open/read/hash errors propagate. |
| cost | Streams and hashes full file. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0004

[Lines 38–130](../../../../tools/run_adversarial_scalability.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(args):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate selected B05 packs and run each B03 child sequentially. |
| inputs / outputs | Parsed source/build/output, families/scales/backends/modes, reps/warmups, seed, observation and CPU in; fresh per-point child packets, logs and experiment.json out. |
| invariants | Requires this source checkout, unique bounded selectors, explicit build inputs and new output. One packet per point, deterministic hashed order, completion only after all requested child gates and source hashes match. |
| ownership | Python owns packet/generated data and one child result; filesystem keeps partial/completed artifacts. No engine state is added. |
| failure | Nonzero child is recorded, marks failed and stops. Other errors may leave running/incomplete output. No runner-level timeout/retry; B03 commands retain their limits. |
| cost | One child per selected family/scale plus pack generation and packet/log writes; points are serial. No engine instrumentation. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0006

[Lines 133–149](../../../../tools/run_adversarial_scalability.py#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse explicit B05 family/scale/backend/mode and resource choices, then delegate to run(). |
| inputs / outputs | Requires --build-dir/--output; source defaults to this checkout. One suite selector plus repeatable family/scale/backend/mode choices; bounded repetitions/warmups, seed, observation and optional CPU. |
| invariants | No default private build discovery remains; parser constrains names and run checks uniqueness/bounds/fresh output. |
| ownership | Argparse owns parsed options; run owns child processes and artifacts. |
| failure | Argparse/run errors propagate; direct-script guard converts returned code with SystemExit. |
| cost | Parse then selected generation, serial child runs and writes. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0007

[Lines 150–153](../../../../tools/run_adversarial_scalability.py#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the parameterized B05 CLI on direct execution. |
| inputs / outputs | Guard calls main() and raises SystemExit with its returned status. |
| invariants | Import does not run a batch; module-level bytecode setting and generator import still occur. |
| ownership | Process owns argv/status; delegated run owns artifacts. |
| failure | Unhandled exceptions use normal Python traceback/exit; no formatter. |
| cost | One guard and delegated CLI. |
| Design | [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |
