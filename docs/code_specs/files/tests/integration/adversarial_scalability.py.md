# `tests/integration/adversarial_scalability.py` — block usage map

[Source](../../../../../tests/integration/adversarial_scalability.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a4ad78df844e03ad1f854a987f0e564d8d8f3efc8ad981ef9efbd1e03f915f3c`. 167 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/adversarial_scalability.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tests/integration/adversarial_scalability.py#L17) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../../tests/integration/adversarial_scalability.py#L20) | Explanatory comments or spacing. |  |
| [B0004 · 22–59](../../../../../tests/integration/adversarial_scalability.py#L22) | Callable definition: def free_connex_controls(source): | calls insert, str, check_labels, loads; guard require(\[a\['variables'\] for a in query\['structure'\]\['atoms'\]\] == scopes and query\['head'\] == head,; returns spec, events, {'family': family, 'scale_selector': scale, 'axis': 'source_rows',; growth insert; 4 loop sites; source comment (unverified): # The full-head triangle's universal head edge makes H+F acyclic; · [reviewed contract](#b0004) |
| [B0005 · 60–61](../../../../../tests/integration/adversarial_scalability.py#L60) | Explanatory comments or spacing. |  |
| [B0006 · 62–163](../../../../../tests/integration/adversarial_scalability.py#L62) | Callable definition: def main(): | calls Path, resolve, require, free_connex_controls; guard require(crown == build / 'crown' and collector == build / 'crown_measure_workload', 'test binaries …; returns result; growth insert; 9 loop sites · [reviewed contract](#b0006) |
| [B0007 · 164–167](../../../../../tests/integration/adversarial_scalability.py#L164) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–16](../../../../../tests/integration/adversarial_scalability.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sys.dont_write_bytecode = True
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable bytecode writes in the B05 CTest process. |
| inputs / outputs | Sets current interpreter flag before main imports repository modules. |
| invariants | Only normal .pyc writes are suppressed; test artifacts and child outputs remain enabled. |
| ownership | Process-local interpreter state. |
| failure | Assignment has no local catch. |
| cost | One assignment. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0002

[Lines 17–19](../../../../../tests/integration/adversarial_scalability.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise RuntimeError on a failed B05 fixture assertion. |
| inputs / outputs | Predicate/message in; None on true, RuntimeError otherwise. |
| invariants | Checks cover finite fixtures only. |
| ownership | Borrows arguments. |
| failure | False predicate raises RuntimeError. |
| cost | One truth check. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0004

[Lines 22–59](../../../../../tests/integration/adversarial_scalability.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L59:sha256:b15aa0757282c9ab00bdfa72a00bb087ca0c48524ee07b189a247ab9c095f394
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check both corpus producers against independent literal free-connex labels. |
| inputs / outputs | Construct cyclic triangle, acyclic nonfree path and free full-head path; compare exact shapes and literal body/free booleans for B02 and B05. |
| invariants | Expected booleans do not call the producer acyclicity predicate. B05 case substitution is scoped to unittest.mock.patch and restores the original function. |
| ownership | Ordinary temporary Python corpora and patched module binding; no maintained workload is written. |
| failure | Unexpected shape/label raises RuntimeError; import/generator/oracle failures propagate. |
| cost | Six tiny generated examples with their normal finite oracle/provenance costs; offline test only. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [tools/generate_workloads.py](../../../../../tools/generate_workloads.py), [tools/generate_adversarial_workloads.py](../../../../../tools/generate_adversarial_workloads.py), [docs/workloads.md](../../../../workloads.md) |

## B0006

[Lines 62–163](../../../../../tests/integration/adversarial_scalability.py#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise B05 generation, static checks, six churn shapes, scaling, native matrix, analyzer linkage, raw-v2/legacy-v1 compatibility and failure preservation. |
| inputs / outputs | CTest supplies crown, collector, source and build, plus optional artifact root; writes packs, subprocess ledgers, B05/B03 packets and analysis. |
| invariants | Requires binaries equal named build outputs. Checks 19 scale-1 families, selected scale-2 axes, live/high-water churn references, tamper rejection, generator allowlist, 12 points × two backends × three modes, raw-v2 storage and legacy shape after explicit transform, no-overwrite and failed fake-build child. Does not accept B05 trends. Before generating the real packs, six literal body/free-connex controls exercise both producers without using their predicate to calculate expectations. |
| ownership | Owns pack/report copies and subprocess captures. Explicit artifacts persist; otherwise TemporaryDirectory owns the tree with normal cleanup. |
| failure | Assertion failures raise RuntimeError; delegated parsing, schema, IO and subprocess exceptions propagate. Nested commands timeout at 600 seconds; persistent artifacts can be partial. |
| cost | Generates finite packs and setup/helper plans, then executes 72 configurations with one correctness preflight and one measured collector run each: 72 preflights plus 72 measurements, zero warmups. Also analyzes results and runs failure/preservation controls. CTest timeout is 1200 seconds. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../../tools/generate_adversarial_workloads.py), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [tools/run_adversarial_scalability.py](../../../../../tools/run_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../../tools/analyze_adversarial_scalability.py), [schemas/workload-measurement-v1.schema.json](../../../../../schemas/workload-measurement-v1.schema.json), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
    def invoke(arguments, success=True):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one B05 test subprocess and retain its streams and status before asserting expected success. |
| inputs / outputs | Argument sequence and expected-success flag in; CompletedProcess out. Writes numbered stdout/stderr files and rewrites commands.json first. |
| invariants | A failed child is retained before the expected-status predicate; each nested call has a 600-second timeout. |
| ownership | Borrows arguments; subprocess owns child; test directory retains stream and command-ledger files. |
| failure | Timeout/launch/file errors propagate; unexpected status raises RuntimeError after raw outputs are recorded. |
| cost | One child launch, capture, hash of each captured stream, and full command-ledger rewrite per call. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [tools/run_adversarial_scalability.py](../../../../../tools/run_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0007

[Lines 164–167](../../../../../tests/integration/adversarial_scalability.py#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run integration checks only when CTest executes the script. |
| inputs / outputs | Guard calls main() directly; it adds no catch or failure formatter. |
| invariants | Import does not generate packs or start subprocesses; bytecode flag/jsonschema import still occur. |
| ownership | Process owns argv/streams; main owns test artifacts. |
| failure | Unhandled errors use normal traceback/nonzero exit. |
| cost | One guard and call. |
| Design | [tests/integration/adversarial_scalability.py](../../../../../tests/integration/adversarial_scalability.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |
