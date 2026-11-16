# `tests/integration/legacy_replay_checker.py` — block usage map

[Source](../../../../../tests/integration/legacy_replay_checker.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2c7e84d5330aca8e2d7ac237c553350a929a797cbcb5dc255a62f4ecbb1af749`. 101 lines partitioned into 4 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/integration/legacy_replay_checker.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; 1 loop sites · [reviewed contract](#b0001) |
| [B0002 · 26–34](../../../../../tests/integration/legacy_replay_checker.py#L26) | Callable definition: def invoke(base, baseline, trace, stdout, label, success, optimized=False): | calls str, run, assert, is_file; guard assert (result.returncode == 0) == success, (label, result.stdout, result.stderr\[-1600:\]); returns json.loads(output.read_text()) if success else None · [reviewed contract](#b0002) |
| [B0003 · 35–65](../../../../../tests/integration/legacy_replay_checker.py#L35) | declares values/defaults or compile-time conditions. | 4 loop sites · [reviewed contract](#b0003) |
| [B0004 · 66–101](../../../../../tests/integration/legacy_replay_checker.py#L66) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; 3 loop sites; source comment (unverified): # Preserve the event count so this control reaches duplicate admission. · [reviewed contract](#b0004) |

## B0001

[Lines 1–25](../../../../../tests/integration/legacy_replay_checker.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:0f878ad667cc6420a01e6d309e9ac40305478a8f9e525f4069720c76b1224838
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the offline regression, resolve maintained capture/trace paths, and verify every capture hash before invoking the checker. |
| inputs / outputs | Takes repository root from argv, loads tests/legacy_baselines/captures.json, checks every named capture SHA, and declares four mode/trace/stdout cases. |
| invariants | Only retained captured outputs are consumed; this setup does not launch JDK, Maven, CMake, or an external baseline. |
| ownership | Paths and manifest objects are local; repository fixtures are read-only. |
| failure | Missing arguments/files, malformed manifest, or capture hash mismatch fails the test. |
| cost | Reads capture metadata and hashes each exact capture file once; no baseline work. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tests/legacy_baselines/captures.json](../../../../../tests/legacy_baselines/captures.json), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0002

[Lines 26–34](../../../../../tests/integration/legacy_replay_checker.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L34:sha256:771a469ef53a1ba8527fc3af2a202ad0c2431debe2a9715da9ea60f477f82215
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the checker in a temporary report path and verify process status plus report creation semantics. |
| inputs / outputs | Builds a Python command (optionally adding -O), runs it with a 20-second timeout, requires success/failure to match expectation, requires output existence only on success, and parses successful JSON. |
| invariants | The helper never writes into maintained capture paths; optimized-mode controls specifically ensure explicit checker guards survive -O. |
| ownership | Temporary base path is borrowed; subprocess owns its process; output report belongs to the test temp directory. |
| failure | Unexpected return code, wrong report existence, malformed report, or timeout fails via assertion/subprocess exception. |
| cost | One checker subprocess per invocation, bounded by 20 seconds, with captured stdout/stderr and one JSON report loaded on success. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tools/check_legacy_replay.py](../../../../../tools/check_legacy_replay.py) |

## B0003

[Lines 35–65](../../../../../tests/integration/legacy_replay_checker.py#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L65:sha256:8cefc7437d2e9897828d4c17266a15317267d8696ef8142f0218a0eaa86cef79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run four actual-capture positive cases and eight Scala envelope/delta/snapshot corruption controls within one temporary-directory scope. |
| inputs / outputs | Runs all four capture modes and checks finite event/count/scope expectations, then constructs eight Scala event corruptions (missing/duplicate delta, wrong sign, missing/duplicate/boolean snapshot, wrong sequence and invalid Base64); each corrupted capture must fail without a pass report. |
| invariants | Assertions are finite regression expectations for the retained inputs; they do not qualify any other query, trace, binary, or performance behavior. |
| ownership | TemporaryDirectory owns report and modified-output scratch files and removes them on scope exit. |
| failure | Any checker status, expected result, report semantics, or cleanup exception fails the integration test. |
| cost | Four successful plus eight rejected checker subprocesses over tiny captures; two rejection calls use Python -O. Temporary ownership continues into the following mapped region; no external baseline/compiler runs. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tests/legacy_baselines/captures.json](../../../../../tests/legacy_baselines/captures.json), [benchmarks/legacy/replay/scala-l3-mixed.txt](../../../../../benchmarks/legacy/replay/scala-l3-mixed.txt), [benchmarks/legacy/replay/line5cd-insert-only.txt](../../../../../benchmarks/legacy/replay/line5cd-insert-only.txt), [benchmarks/legacy/replay/line5gc-mixed.txt](../../../../../benchmarks/legacy/replay/line5gc-mixed.txt) |

## B0004

[Lines 66–101](../../../../../tests/integration/legacy_replay_checker.py#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L101:sha256:22d4426e25efb9a5bf5cf43e7f7ed056cd1d2d70ec4909ab4a3cd46159ee349c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove selected corruption, unsupported-operation, unobserved-tail, optimized-guard, and output no-overwrite failures are rejected. |
| inputs / outputs | Continues the same temporary scope with four empty captures, wrong C++ count, lost zero replacements, extra output, four unsupported/duplicate/absent operation cases, three unobserved C++ tails, an isolated Scala 0_1 spelling case, and existing-output preservation. Together with eight prior-region Scala faults the full matrix has24 negative controls. |
| invariants | Each corrupted case must fail and must not create a success report; existing output bytes must remain identical. The underscore input preserves the mathematical value, isolating lexical-domain admission; final-star controls ensure updates after last observed snapshot are not silently ignored. |
| ownership | All altered traces/outputs/reports are temporary; the checked-in captures remain immutable. |
| failure | Unexpected checker acceptance, overwritten output, test assertion failure, or timeout fails the test. |
| cost | Sixteen rejected checker subprocesses in this region, including the direct existing-output attempt; the preceding region supplies eight more. Each call has a20-second timeout and the whole CTest a60-second ceiling; fixtures are tiny. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [tools/check_legacy_replay.py](../../../../../tools/check_legacy_replay.py), [tests/legacy_baselines/captures.json](../../../../../tests/legacy_baselines/captures.json) |
