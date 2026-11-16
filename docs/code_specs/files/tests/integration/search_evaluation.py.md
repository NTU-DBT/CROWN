# `tests/integration/search_evaluation.py` — block usage map

[Source](../../../../../tests/integration/search_evaluation.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e329bda47b35afefc554f3457602cfb0c70e911f66d7acff0e4cac296becf9c2`. 118 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/search_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tests/integration/search_evaluation.py#L17) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../../tests/integration/search_evaluation.py#L20) | Explanatory comments or spacing. |  |
| [B0004 · 22–23](../../../../../tests/integration/search_evaluation.py#L22) | Callable definition: def digest(path): | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 24–25](../../../../../tests/integration/search_evaluation.py#L24) | Explanatory comments or spacing. |  |
| [B0006 · 26–113](../../../../../tests/integration/search_evaluation.py#L26) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv) in \[6, 7\], 'usage: search_evaluation.py CROWN COLLECTOR SEARCHER SOURCE BUILD…; returns child; growth insert; 16 loop sites; source comment (unverified): # These receiver guards are exercised without allowing a missing guard to · [reviewed contract](#b0006) |
| [B0007 · 114–118](../../../../../tests/integration/search_evaluation.py#L114) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–16](../../../../../tests/integration/search_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:c857301570ac091ab5e0b32dbb160df62d8f9922ed98b8ab7f4aa8a691ec4f04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the standalone active-in-Release native integration and cold boundary test harness. |
| inputs / outputs | Imports exact Fraction, filesystem/hash/JSON/subprocess utilities and mock/SimpleNamespace for non-native CPU guards. |
| invariants | Tests use explicit require rather than Python assert for acceptance. Import does not launch a process. |
| ownership | Module definitions only; per-run temporary or supplied directory ownership is created later. |
| failure | Missing imports stop the test, without skipped-success fallback. |
| cost | Cold test setup; no production engine instrumentation. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0002

[Lines 17–19](../../../../../tests/integration/search_evaluation.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L19:sha256:8b14f7d5eb0d9a9cafc6d1aaa990a73bad9c261d2c3c97d6713ed7fa789c829b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep every regression condition active independently of interpreter optimization flags. |
| inputs / outputs | A condition/message either returns or raises RuntimeError. |
| invariants | False acceptance conditions cannot disappear under python -O. |
| ownership | No retained owner or mutable test state. |
| failure | False terminates the test nonzero through main error boundary. |
| cost | One test-only branch. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0004

[Lines 22–23](../../../../../tests/integration/search_evaluation.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:95beae8c9f09cce808f6a74942c19e4fd3a0bc3c8f1f30deb9f8e7225f49a322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind retained raw files and immutable experiment bytes to SHA256. |
| inputs / outputs | One Path returns the SHA256 of exact bytes. |
| invariants | No canonical JSON conversion hides an output/source byte change. |
| ownership | Local byte buffer is temporary; digest string is returned independently. |
| failure | Read errors propagate; missing output is not accepted as an empty file. |
| cost | Linear read/hash in file size; test-only host cost. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0006

[Lines 26–113](../../../../../tests/integration/search_evaluation.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L113:sha256:4c4c01ff0deb68a360caebac802ce749328a9a59a42d74413c5c1d7e820b02a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real independent-search, proof, normalized-family, C02 and receiver-boundary controls against the built diagnostic. |
| inputs / outputs | CROWN COLLECTOR SEARCHER SOURCE BUILD and optional new artifact directory run43 method/budget/reference preflights plus4 genuine wireproofs; inspect all raw outputs and retain command logs. |
| invariants | No timing run occurs. Zero literal work retains resource/nullheight; four-atom literal family retains cap3; tiny three-plan family has actual scores7/6,9/6,10/6 and selects7/6. Infeasibility remains. All96 frozen manifests/source/requests/proofs and end closure are checked. Rerun cannot overwrite; boolversion/unknownmethod/unknownfield fail. Mocked cold missing-CPU/outside-affinity guards must reject before provenance/native invocation or directory creation. |
| ownership | Owns new artifact files or a local TemporaryDirectory; invoke waits/captures each child. Existing raw experiment remains immutable during no-overwrite negative. Mock context restores the real provenance helper. |
| failure | Any unexpected exit, stderr, success record on rejection, closure/proof/arithmetic/coverage difference aborts with retained logs. Child timeout fails; no retry or candidate omission. |
| cost | Bounded correctness-only processes and JSON checks, separate from any future controlled study. No performance, universal large-query or full B04 acceptance follows. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0007

[Lines 114–118](../../../../../tests/integration/search_evaluation.py#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L118:sha256:c7d539840ea99d64c99892d0b3e2a1af326a7545da3341d38a5e35cb56e1b245
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the standalone integration test command and single diagnostic failure exit. |
| inputs / outputs | __main__ invokes main; propagated errors print to stderr and exit1. |
| invariants | No test runs on import; checks remain explicit and active in Release. |
| ownership | Main owns all temporary/file/process lifetimes; nothing survives this guard except requested artifacts. |
| failure | Failure remains nonzero with previous raw evidence intact. |
| cost | Test process entry/exit only. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |
