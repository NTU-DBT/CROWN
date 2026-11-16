# `tests/integration/component_planning.py` — block usage map

[Source](../../../../../tests/integration/component_planning.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d2fe447be7af5171bb5c4912ff81dcfebb12246862140eb74631d8bef5d23388`. 128 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/integration/component_planning.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/integration/component_planning.py#L14) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../tests/integration/component_planning.py#L17) | Explanatory comments or spacing. |  |
| [B0004 · 19–20](../../../../../tests/integration/component_planning.py#L19) | Callable definition: def digest(path): | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 21–22](../../../../../tests/integration/component_planning.py#L21) | Explanatory comments or spacing. |  |
| [B0006 · 23–120](../../../../../tests/integration/component_planning.py#L23) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv) in \[6, 7\], 'usage: component_planning.py CROWN COLLECTOR EXPORTER SOURCE BUIL…; returns result; growth insert; 18 loop sites · [reviewed contract](#b0006) |
| [B0007 · 121–128](../../../../../tests/integration/component_planning.py#L121) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–13](../../../../../tests/integration/component_planning.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:6521c32e9af24e2ad474821801efbb0debd72b95879a4cb441e9732a78f62b0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce a real native-driver correctness receiving test with no held-out timing. |
| inputs / outputs | Imports standard process/file/hash/JSON helpers and defines module state. |
| invariants | The tested driver will use --preflight-only; real native calibration belongs to explicit qualified/preliminary setup, not a held-out performance sample. |
| ownership | Module setup owns no active process, runtime or evidence directory. |
| failure | Required Python import errors fail startup; no fallback fake exporter/collector is supplied. |
| cost | Python setup only; real commands run later under main. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/statistics.md](../../../../statistics.md), [Refactor.md §14.1–14.4](../../../../../Refactor.md) |

## B0002

[Lines 14–16](../../../../../tests/integration/component_planning.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L16:sha256:8b14f7d5eb0d9a9cafc6d1aaa990a73bad9c261d2c3c97d6713ed7fa789c829b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep receiving assertions active in every C++ build configuration. |
| inputs / outputs | A false condition raises RuntimeError with the supplied receiving message. |
| invariants | The checks use runtime branches, rather than C++ Release-disabled assertions. |
| ownership | Arguments are borrowed for the call; failure owns its diagnostic according to Python. |
| failure | False reaches the one script failure handler and nonzero exit. |
| cost | One host test branch; no engine hook. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/statistics.md](../../../../statistics.md), [Refactor.md §14.1–14.4](../../../../../Refactor.md) |

## B0004

[Lines 19–20](../../../../../tests/integration/component_planning.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:95beae8c9f09cce808f6a74942c19e4fd3a0bc3c8f1f30deb9f8e7225f49a322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind retained evidence to exact file bytes. |
| inputs / outputs | Receives one Path and returns its SHA256 hexadecimal digest. |
| invariants | A digest identifies bytes, not correctness or unaltered compiler/build history. |
| ownership | Reads a temporary owning byte string and returns an independent digest string. |
| failure | Missing/unreadable files abort receiving. |
| cost | Linear file read/hash, outside measured native phases. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/statistics.md](../../../../statistics.md), [Refactor.md §14.1–14.4](../../../../../Refactor.md) |

## B0006

[Lines 23–120](../../../../../tests/integration/component_planning.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L120:sha256:0a9a0a41a7a2e00d5728be3bbf39d0a0be07f65586b4c393189c5fd931fd652e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the real one-query preflight protocol and verify its semantic, provenance and negative-control boundaries. |
| inputs / outputs | Receives CROWN COLLECTOR EXPORTER SOURCE BUILD and optional fresh artifacts; retains test-command stdout/stderr and verifies resulting driver packets. |
| invariants | Use genuine full_star_3 with h*=1 and all taller ordinary controls, reference storage and four candidates. Require two explicit export passes bracketing every V2/V3 envelope × five split correctness checks, no heldout commands, one final frozen pooled calibration for full/sampled/stale/absent variants and TRAIN-only demand. Preserve every origin after physical dedup. Real zero-search must retain unavailable status with no timings, rerun must not overwrite, and invalid grants must not create a packet. |
| ownership | Owns one new temporary/evidence directory and each completed driver subprocess capture. Native execution/provenance remains the real driver rather than a mocked successful response. |
| failure | Unexpected status, missing evidence, wrong ordering/labels/hash/demand or negative-control acceptance fails immediately. Root owns building and running this test; this authored source does not claim its execution. |
| cost | Finite setup/native correctness calls under 900-second driver process bounds; no heldout performance repetitions, speedup threshold or full B04 completion criterion. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/statistics.md](../../../../statistics.md), [Refactor.md §14.1–14.4](../../../../../Refactor.md) |

## B0007

[Lines 121–128](../../../../../tests/integration/component_planning.py#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L128:sha256:c8741399534ddf50a5997d92c9ea3a7cc224150ed5a0b245616e28787f4949ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the receiving test as a script with one conventional diagnostic exit. |
| inputs / outputs | The module guard invokes main and maps an exception to stderr plus exit one. |
| invariants | Imports execute no native commands; success output occurs only after the real receiving and negative controls finish. |
| ownership | No native handle survives here; main owns temporary/process resources. |
| failure | The error is reported without retrying or weakening a test. |
| cost | Cold CLI boundary only. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/statistics.md](../../../../statistics.md), [Refactor.md §14.1–14.4](../../../../../Refactor.md) |
