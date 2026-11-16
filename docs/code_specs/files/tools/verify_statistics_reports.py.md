# `tools/verify_statistics_reports.py` — block usage map

[Source](../../../../tools/verify_statistics_reports.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `dd5411eebc0b8bd6c33c3f8a9198c6bed8c164898feb36534838326306aebf5c`. 76 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../tools/verify_statistics_reports.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–72](../../../../tools/verify_statistics_reports.py#L16) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, resolve; 1 loop sites; source comment (unverified): # Keep repository acceptance fields out of native runtime capability facts. · [reviewed contract](#b0002) |
| [B0003 · 73–76](../../../../tools/verify_statistics_reports.py#L73) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–15](../../../../tools/verify_statistics_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the native statistics corpus producer/checker wrapper with retained failure evidence. |
| inputs / outputs | Imports jsonschema/stdlib, guarded main with executable/root/production-or-testing arguments. |
| invariants | Native producer and independent Python checker are distinct stages. Repository project acceptance is excluded from runtime report capabilities. |
| ownership | Owns imports; main owns persistent-on-failure temporary corpus and full schema/DOM mutation. |
| failure | Import errors propagate; broad BaseException handler is for evidence retention/rethrow, not success fallback. |
| cost | Fixed imports; main does native/corpus work only when invoked. |
| Design | [tools/verify_statistics_reports.py](../../../../tools/verify_statistics_reports.py), [tools/support/check_statistics_reports.py](../../../../tools/support/check_statistics_reports.py), [docs/statistics.md](../../../statistics.md), [tests/statistics/legacy-v2/SHA256SUMS](../../../../tests/statistics/legacy-v2/SHA256SUMS), [schemas/statistics-explain-v3.schema.json](../../../../schemas/statistics-explain-v3.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 16–72](../../../../tools/verify_statistics_reports.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify frozen legacy checksums, run native statistics producer/checker and reject removed project-gate capability. |
| inputs / outputs | --executable/--repo-root/--variant in; prints stage/result JSON, removes corpus only on complete success. |
| invariants | Checksum file must list exactly two unique legacy files matching raw hashes. Child processes use check=True; no intrinsic subprocess timeout, CMake outer timeout applies. Native facts cannot contain c01_project_gate, including closed-schema mutation. |
| ownership | Owns mkdtemp corpus, parsed current schema/off-state DOM and mutant clone. except BaseException reports path then rethrows, preserving artifacts even on interrupts; else rmtree on success. |
| failure | Baseline errors before corpus visible; child/assert/schema/IO failure retained/rethrown; expected ValidationError for one mutant counted, other failures not swallowed. Success cleanup failure propagates. |
| cost | Two full legacy hashes, native producer plus separate full offline checker process, one schema/report read/deepcopy/validation; no performance claim. |
| Design | [tools/verify_statistics_reports.py](../../../../tools/verify_statistics_reports.py), [tools/support/check_statistics_reports.py](../../../../tools/support/check_statistics_reports.py), [docs/statistics.md](../../../statistics.md), [tests/statistics/legacy-v2/SHA256SUMS](../../../../tests/statistics/legacy-v2/SHA256SUMS), [schemas/statistics-explain-v3.schema.json](../../../../schemas/statistics-explain-v3.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 73–76](../../../../tools/verify_statistics_reports.py#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the native statistics acceptance wrapper only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No outer catch; main retains failing artifacts and rethrows BaseException. |
| cost | Guard constant plus full wrapper/native checker work. |
| Design | [tools/verify_statistics_reports.py](../../../../tools/verify_statistics_reports.py), [tools/support/check_statistics_reports.py](../../../../tools/support/check_statistics_reports.py), [docs/statistics.md](../../../statistics.md), [tests/statistics/legacy-v2/SHA256SUMS](../../../../tests/statistics/legacy-v2/SHA256SUMS), [schemas/statistics-explain-v3.schema.json](../../../../schemas/statistics-explain-v3.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
