# `tests/integration/input_specialization.py` — block usage map

[Source](../../../../../tests/integration/input_specialization.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `baf2000af7f2ef0c69c30d34a77b24e0b3ea88d4363a150c16410804d93d0575`. 145 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/input_specialization.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–18](../../../../../tests/integration/input_specialization.py#L17) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/input_specialization.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–22](../../../../../tests/integration/input_specialization.py#L21) | Callable definition: def digest(path): | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../tests/integration/input_specialization.py#L23) | Explanatory comments or spacing. |  |
| [B0006 · 25–140](../../../../../tests/integration/input_specialization.py#L25) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv) in \[6, 7\], 'usage: input_specialization.py CROWN COLLECTOR CLIENT SOURCE BUIL…; returns child; growth insert; 24 loop sites; source comment (unverified): # Shape-only receiver controls: convert a real verified capture to a · [reviewed contract](#b0006) |
| [B0007 · 141–145](../../../../../tests/integration/input_specialization.py#L141) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–16](../../../../../tests/integration/input_specialization.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:f5d5f51a82c696371035bffa573a0ad029c894ddf18bd6f2de010ded1199856d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the Release-active integration to real matched binaries and independent receiver mutation controls. |
| inputs / outputs | Standard Python filesystem/subprocess/deepcopy/mock helpers. |
| invariants | Import starts no native job; test invokes actual source-final runner later. No optional dependency substitutes for correctness. |
| ownership | Module constants/imports own no native state. |
| failure | Import errors fail test. |
| cost | Cold test setup only. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0002

[Lines 17–18](../../../../../tests/integration/input_specialization.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:37412754f02a72501fae4b0fde18cf4501f7f11d74b3dd141a9a6c0b30c1a09e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep integration checks active in all build profiles. |
| inputs / outputs | Condition/message; RuntimeError when false. |
| invariants | No assert/NDEBUG dependence. |
| ownership | Borrowed message becomes exception diagnostic. |
| failure | False raises to outer test failure. |
| cost | Constant branch, test only. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0004

[Lines 21–22](../../../../../tests/integration/input_specialization.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:95beae8c9f09cce808f6a74942c19e4fd3a0bc3c8f1f30deb9f8e7225f49a322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact retained raw/source bytes for test receiving. |
| inputs / outputs | Path; SHA256 hex digest. |
| invariants | Pins byte identity, not semantic acceptance or build reproducibility. |
| ownership | Temporary byte buffer local; returns owned text. |
| failure | Filesystem/hash failures fail test. |
| cost | Linear file bytes outside measured native scope. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0006

[Lines 25–140](../../../../../tests/integration/input_specialization.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L140:sha256:173ff20708c0ba38892fdacabeb9b9b3b88fccfbea05f794348d5be6e42e5fe1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise genuine matched preflight, request failures and receiver tamper controls. |
| inputs / outputs | CROWN COLLECTOR CLIENT SOURCE BUILD \[NEW_ARTIFACT_DIRECTORY\]; runs width2 both modes/backends before checking retained 28 gates/244 prefixes. |
| invariants | No timing children are requested. Requires full gate/end closure/no omitted variant, actual threaded tables except constant false and precise count protocol. Native bool-version/unknown-mode/extra-field/zero-prep/catalog-binding failures emit no success. Seven actual-capture mutations must reject, including work/phase/mode/duplicates/wrong delta. No-overwrite leaves study bytes unchanged; mocked CPU guards cannot inspect build or launch native. Nine additional measured-clock/capture shape negatives derive from a genuine verified report converted to zero-clock measure shape; these pure receiver controls do not claim a native measured execution. |
| ownership | Fresh exclusive retained directory or temporary directory owns logs/requests; every child stdout/stderr/status is hashed. Completed study is read-only during negative rerun. |
| failure | Child timeout/nonzero/success-shape mismatch or missing receiver denial fails test with retained command log. Outer main emits one diagnostic/nonzero. |
| cost | Finite real correctness calls plus pure mutation checks; not a timing or full-B04 acceptance test. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0007

[Lines 141–145](../../../../../tests/integration/input_specialization.py#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L145:sha256:c7d539840ea99d64c99892d0b3e2a1af326a7545da3341d38a5e35cb56e1b245
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map integration outcome to a direct process exit. |
| inputs / outputs | __main__ invokes test; exceptions emit stderr and exit one. |
| invariants | Success line names finite actual coverage and explicitly excludes timing/full-B04 acceptance. |
| ownership | Temporary directory cleanup follows successful test; caller-supplied task evidence remains retained. |
| failure | Any test exception is nonzero. |
| cost | One outer boundary only. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |
