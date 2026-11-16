# `tests/integration/star_oracle.py` — block usage map

[Source](../../../../../tests/integration/star_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4a462ba9982a438002096c814996572c1770f8f07ce6861619d61d9596c8819d`. 314 lines partitioned into 15 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/integration/star_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–59](../../../../../tests/integration/star_oracle.py#L19) | Callable definition: def sqlite_original(request, state): | calls len, sqlite_state, any, get; returns relational.sqlite_state(doc, state); True, answer; 11 loop sites; source comment (unverified): # SQLite limits a flat join to64 tables. The wide fixture keeps the exact · [reviewed contract](#b0002) |
| [B0003 · 60–61](../../../../../tests/integration/star_oracle.py#L60) | Explanatory comments or spacing. |  |
| [B0004 · 62–100](../../../../../tests/integration/star_oracle.py#L62) | Callable definition: def make_case(name, kinds, head, operations, seed, satellites=None, constraints=None, unused=False): | calls len, list, range, str; returns request; growth insert; 12 loop sites · [reviewed contract](#b0004) |
| [B0005 · 101–102](../../../../../tests/integration/star_oracle.py#L101) | Explanatory comments or spacing. |  |
| [B0006 · 103–185](../../../../../tests/integration/star_oracle.py#L103) | Callable definition: def corpus(): | calls enumerate, list, in, append; returns result; growth insert; 19 loop sites · [reviewed contract](#b0006) |
| [B0007 · 186–187](../../../../../tests/integration/star_oracle.py#L186) | Explanatory comments or spacing. |  |
| [B0008 · 188–208](../../../../../tests/integration/star_oracle.py#L188) | Callable definition: def expected_snapshot(request, state, sequence): | calls sqlite_original, python_query, next, enumerate; returns {"sequence": sequence, "rows": rows, "source": copy.deepcopy(state),; 5 loop sites · [reviewed contract](#b0008) |
| [B0009 · 209–210](../../../../../tests/integration/star_oracle.py#L209) | Explanatory comments or spacing. |  |
| [B0010 · 211–237](../../../../../tests/integration/star_oracle.py#L211) | Callable definition: def reference(request): | calls dict, expected_snapshot, deepcopy, row_key; returns initial, trace; growth insert; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 238–239](../../../../../tests/integration/star_oracle.py#L238) | Explanatory comments or spacing. |  |
| [B0012 · 240–257](../../../../../tests/integration/star_oracle.py#L240) | Callable definition: def compare_snapshot(actual, expected, request): | calls row_key, len, zip, min; 6 loop sites · [reviewed contract](#b0012) |
| [B0013 · 258–259](../../../../../tests/integration/star_oracle.py#L258) | Explanatory comments or spacing. |  |
| [B0014 · 260–310](../../../../../tests/integration/star_oracle.py#L260) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, corpus; 9 loop sites · [reviewed contract](#b0014) |
| [B0015 · 311–314](../../../../../tests/integration/star_oracle.py#L311) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–18](../../../../../tests/integration/star_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:118d9cbce0e1c9c9ae109aa75fa7a252aa5645fd0e8a087b6e74013d5b9eae0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import independent relational reference helpers and define the deterministic star corpus seed. |
| inputs / outputs | Python imports, module docstring and SEED=0x6803C0; no native process or fixture executes at import. |
| invariants | key_specialization_oracle helpers implement complete original CQ/constraints and SQLite translation; they import no star partition/H/group/cursor mechanism. |
| ownership | Ordinary Python module/string/function references outside every native query budget. |
| failure | Missing imports or module parse errors propagate to the Python runner. |
| cost | Cold module loading only. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0002

[Lines 19–59](../../../../../tests/integration/star_oracle.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L59:sha256:f5c9371dbd487169c13cc007efef0d48fd3a66227684ee88cef5d27d69c1b717
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the complete original CQ with SQLite, including the wide-star reference translation. |
| inputs / outputs | Original request and full source-set model in; independent SQLite constraint-validity flag and exact projected set out. |
| invariants | At most60 atoms uses existing arbitrary-CQ SQLite evaluation. Wider fixture requires unconstrained int64 schemas and translates each original unary atom to correlated EXISTS, avoiding SQLite flat-join limits without changing native query or using production heavy/light state. |
| ownership | Owns an in-memory SQLite connection/tables/result dictionary during the call; borrows request/state; all are reference-side resources. |
| failure | Wide-fixture shape/type/constraint assertions and SQLite errors fail the oracle. Connection context closes on every exit. |
| cost | Recreates complete physical tables and evaluates original SQL at each prefix; intentionally slow reference work, not claimed native complexity. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0004

[Lines 62–100](../../../../../tests/integration/star_oracle.py#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L100:sha256:8fb145cb1c724faec0cc31e23d8c8ca294746790a7a3fd2414d291a8fd1c47e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one reproducible original-source request and retain exact sequence behavior across invalid constraints. |
| inputs / outputs | Case name, scalar kinds, ordered/repeated head, physical operations, seed and optional satellite/constraint/unused source choices in; JSON request out. |
| invariants | Shuffles original table, occurrence and variable IDs. Events retain physical table IDs and original center index. Only independently constraint-valid proposed source states advance sequence while constructing subsequent event numbers. |
| ownership | Owns ordinary Python catalog/query/event/model structures and copies; no native artifact or mutable query owner exists here. |
| failure | Malformed fixture lookups/shapes or reference helper errors propagate; this builder does not turn native errors into expected successes. |
| cost | Query-sized construction plus copied full source states and independent constraint checks per supplied operation. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py) |

## B0006

[Lines 103–185](../../../../../tests/integration/star_oracle.py#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L185:sha256:ff1a383d26e4c576996a5cf7b8b2b04c4734fea6f77da28e09442ddd37672fde
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the literal and seeded adversarial star acceptance corpus. |
| inputs / outputs | No arguments; returns independently constructed requests for every-relation/head traces, H cubes, heavy/light skew, cross-mask collisions, constraints, unused sources, exact scalars, churn and70 coordinates. |
| invariants | Heads include Boolean, full, reordered and repeated positions. Explicit expect counters name only real heavy/light branch discriminators. Fixed seeds preserve failures; date/decimal/string/bool values avoid floating conversion. |
| ownership | Owns all case/event lists and dictionaries in Python test memory; no production optimizer or partition data supplies fixtures. |
| failure | Fixture/reference assertions fail construction; no native job is launched by corpus(). |
| cost | Finite fixture enumeration and model construction; this corpus is correctness evidence only when compared with completed native receipts. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0008

[Lines 188–208](../../../../../tests/integration/star_oracle.py#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L208:sha256:e0dec4c18d3ce009f6236c33614f540d37415c7b195509c07039b8bf9af13114
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an exact original-query/source/H expectation for a single committed prefix. |
| inputs / outputs | Original request, complete source model and committed sequence in; expected current set, owned source image, center population and per-coordinate exact H/key counts out. |
| invariants | Direct Python full joins must equal separately translated SQLite results. H uses arbitrary-precision integer r**(d-1) and center physical rows only, independently of maintained histogram/labels/groups. |
| ownership | Borrows model/request, deep-copies source expectation and owns result/count dictionaries outside native accounts. |
| failure | Reference disagreement or invalid original constraints raises AssertionError; reference/SQLite failures propagate. |
| cost | Full joins, full source copy and brute-force degree/H scans per prefix; explicitly test-only recomputation. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0010

[Lines 211–237](../../../../../tests/integration/star_oracle.py#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L237:sha256:634d66502ab16d3d2cac4ee220c2c952b3a6c5e9e864850c1ebbb9448f415347
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay physical set events through a complete independent before/after source model. |
| inputs / outputs | One original request in; initial expected snapshot plus event error/change/current-state expectations out. |
| invariants | Python and SQLite constraint decisions must agree. Invalid sequence or constraints preserve prior source state/sequence. Duplicate insert/absent delete retain exact set no-op behavior; every accepted prefix is recomputed from the original CQ. |
| ownership | Owns ordinary copied proposed states and expected trace; no native result, account or star state is trusted as oracle input. |
| failure | Model disagreements/assertions fail; no native retry or production mutation occurs. |
| cost | Full source copy, constraint checks, SQLite rebuilding and original-query evaluation per event. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py) |

## B0012

[Lines 240–257](../../../../../tests/integration/star_oracle.py#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L257:sha256:b1e86cf0232b71b2fbffa779a3eabaa998726bb09629ce1c44fb0d3a18113765
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one native committed observation with independent original-state expectations. |
| inputs / outputs | Native snapshot JSON, expected model snapshot and original request in; returns only if sequence/source/results/H/count/output/quantum observations agree. |
| invariants | Checks both result identity set and length so duplicates cannot disappear in conversion. H/key counts come from source-model expectations. Candidate quantum is checked against the published local formula using observed heavy-key gauges, not treated as an independent label proof. |
| ownership | Borrows ordinary parsed JSON/model objects; comparison temporaries own Python memory and retain no native lease. |
| failure | Any mismatch raises AssertionError and fails the caller; no tolerance or approximation is used. |
| cost | Visits all exported rows/tables/dimensions and performs exact integer formula checks; reference-side cost only. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0014

[Lines 260–310](../../../../../tests/integration/star_oracle.py#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L310:sha256:519fda0f51f653014ad60452f753fc6a01af7d73dfa067475ca4491302123ddc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both real source backends and receive native trace output against the independent oracle corpus. |
| inputs / outputs | --driver executable and optional --artifacts directory in; JSONL subprocess exchange, exact comparisons, optional evidence files and a PASS summary after successful receipt out. |
| invariants | Each request runs for reference/indexed source storage. Nonzero native status, missing frames, original/source-only metadata mismatch, semantic mismatch or branch-counter mismatch fails. PASS is printed only after every comparison; authoring this code is not a passing receipt. |
| ownership | Owns requests/expectations/subprocess capture/artifact text in the test process; each native input line owns an independent Runtime. |
| failure | CLI/file/process/JSON failures propagate; assertion failures add the case ID and preserve the original failure as cause. |
| cost | Complete two-backend native traces plus intentionally slow reference joins/SQLite/H and artifact serialization; no performance benchmark claim. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/reference/star_driver.cpp](../../../../../tests/reference/star_driver.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/star.md](../../../../star.md) |

## B0015

[Lines 311–314](../../../../../tests/integration/star_oracle.py#L311); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L311-L314:sha256:dbad1e561b8500581a5b41ca030f5807d6ea0299228aac9e07fddf40b3aa12b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the acceptance runner only when executed as the main Python script. |
| inputs / outputs | __name__ guard; calls main() for direct execution and does nothing on import. |
| invariants | Importing reference helpers or this module does not launch the native driver. |
| ownership | No additional ownership beyond main() when invoked. |
| failure | main() errors propagate through normal Python process handling. |
| cost | One name comparison plus main() only for the executable path. |
| Design | [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py) |
