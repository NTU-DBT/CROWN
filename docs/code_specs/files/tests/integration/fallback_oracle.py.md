# `tests/integration/fallback_oracle.py` — block usage map

[Source](../../../../../tests/integration/fallback_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `09a306c6b27606779712f54e108c19f980458d4050bef1e43781aaaa9efac922`. 423 lines partitioned into 29 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/fallback_oracle.py#L1) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–24](../../../../../tests/integration/fallback_oracle.py#L21) | Callable definition: def python_query(doc, state): | calls get; returns {}; relational.python_query(doc, state) · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../../tests/integration/fallback_oracle.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–29](../../../../../tests/integration/fallback_oracle.py#L27) | Callable definition: def sql_value(value): | calls canonical, next, iter, values; returns next(iter(value.values())) if isinstance(value, dict) else value · [reviewed contract](#b0004) |
| [B0005 · 30–33](../../../../../tests/integration/fallback_oracle.py#L30) | Module statements. | source comment (unverified): # SQLite stores exact canonical decimal/date text and performs equality only. · [reviewed contract](#b0005) |
| [B0006 · 34–95](../../../../../tests/integration/fallback_oracle.py#L34) | Callable definition: def sqlite_state(doc, state): | calls enumerate, connect, zip, join; returns valid, result; 15 loop sites · [reviewed contract](#b0006) |
| [B0007 · 96–99](../../../../../tests/integration/fallback_oracle.py#L96) | declares types or opens a type body. | source comment (unverified): # Independent set-hypergraph GYO, used only to check the fixture's declared · [reviewed contract](#b0007) |
| [B0008 · 100–119](../../../../../tests/integration/fallback_oracle.py#L100) | Callable definition: def acyclic(edges): | calls set, enumerate, and, add; returns False; True; 11 loop sites · [reviewed contract](#b0008) |
| [B0009 · 120–121](../../../../../tests/integration/fallback_oracle.py#L120) | Explanatory comments or spacing. |  |
| [B0010 · 122–127](../../../../../tests/integration/fallback_oracle.py#L122) | Callable definition: def classify(doc): | calls acyclic; returns "cyclic"; "free_connex" if acyclic(scopes + \[{field\["var"\] for field in doc\["query"\]\["head"\]}\]) els…; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 128–129](../../../../../tests/integration/fallback_oracle.py#L128) | Explanatory comments or spacing. |  |
| [B0012 · 130–155](../../../../../tests/integration/fallback_oracle.py#L130) | Callable definition: def make_case(name, tables, atoms, head, operations, expected_class, seed, contradiction=False): | calls deepcopy, Random, shuffle, enumerate; returns {"id": name, "document": doc, "events": events}; growth insert; 6 loop sites; source comment (unverified): # Occurrence spelling, declaration order and physical table order are all · [reviewed contract](#b0012) |
| [B0013 · 156–157](../../../../../tests/integration/fallback_oracle.py#L156) | Explanatory comments or spacing. |  |
| [B0014 · 158–275](../../../../../tests/integration/fallback_oracle.py#L158) | Callable definition: def corpus(): | calls add, append, make_case, len; returns (\[table(name, \[("a", "int64"), ("b", "int64")\]) for name in ("R", "S", "T")\],; cases; growth insert; 21 loop sites · [reviewed contract](#b0014) |
| [B0015 · 276–277](../../../../../tests/integration/fallback_oracle.py#L276) | Explanatory comments or spacing. |  |
| [B0016 · 278–288](../../../../../tests/integration/fallback_oracle.py#L278) | Callable definition: def expected_profile(doc): | calls classify, get; returns {"backend": "exact_recompute_v1", "semantics": "exact_set", "query_class": query_class, "reason": r… · [reviewed contract](#b0016) |
| [B0017 · 289–290](../../../../../tests/integration/fallback_oracle.py#L289) | Explanatory comments or spacing. |  |
| [B0018 · 291–311](../../../../../tests/integration/fallback_oracle.py#L291) | Callable definition: def snapshot(doc, state, sequence): | calls python_query, sqlite_state, len, enumerate; returns {"sequence": sequence, "ready": True, "rows": relational.ordered(result),; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 312–313](../../../../../tests/integration/fallback_oracle.py#L312) | Explanatory comments or spacing. |  |
| [B0020 · 314–344](../../../../../tests/integration/fallback_oracle.py#L314) | Callable definition: def reference(request): | calls snapshot, canonical, dict, row_key; returns {"profile": expected_profile(doc), "initial": initial, "frames": frames}; growth insert; 7 loop sites · [reviewed contract](#b0020) |
| [B0021 · 345–346](../../../../../tests/integration/fallback_oracle.py#L345) | Explanatory comments or spacing. |  |
| [B0022 · 347–350](../../../../../tests/integration/fallback_oracle.py#L347) | Callable definition: def normalized_rows(rows): | calls row_key, canonical, len, ordered; returns relational.ordered(result); 2 loop sites · [reviewed contract](#b0022) |
| [B0023 · 351–352](../../../../../tests/integration/fallback_oracle.py#L351) | Explanatory comments or spacing. |  |
| [B0024 · 353–357](../../../../../tests/integration/fallback_oracle.py#L353) | Callable definition: def check_snapshot(actual, expected): | calls deepcopy, normalized_rows; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 358–359](../../../../../tests/integration/fallback_oracle.py#L358) | Explanatory comments or spacing. |  |
| [B0026 · 360–380](../../../../../tests/integration/fallback_oracle.py#L360) | Callable definition: def check_output(actual, expected, case_id): | calls check_snapshot, len, enumerate, zip; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 381–382](../../../../../tests/integration/fallback_oracle.py#L381) | Explanatory comments or spacing. |  |
| [B0028 · 383–419](../../../../../tests/integration/fallback_oracle.py#L383) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, corpus; 9 loop sites · [reviewed contract](#b0028) |
| [B0029 · 420–423](../../../../../tests/integration/fallback_oracle.py#L420) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |

## B0001

[Lines 1–20](../../../../../tests/integration/fallback_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:e54915946269ceb9ee05cfe73b9111ec9e0ba06e9cd42a3172fc2cdf2550ab1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import independent original-CQ reference helpers and declare deterministic typed wire conventions. |
| inputs / outputs | Python imports, seed, uint64 ceiling and fixture helper aliases. |
| invariants | No native fallback evaluator or state is imported. Shared helpers supply original relations/scalars/constraints, not native fallback behavior. |
| ownership | Module-level ordinary Python declarations/constants; no native account. |
| failure | Import/setup errors fail normally; no native process starts on import. |
| cost | External oracle setup, excluded from native counter interpretation. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 21–24](../../../../../tests/integration/fallback_oracle.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L24:sha256:623772a161ed71792306235cb29a8a691c4b37e69c6d5f74068204b59a1e13e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define original full-CQ results, including explicit constant-false semantics. |
| inputs / outputs | Original document and complete physical source sets in; canonical distinct projected row map out. |
| invariants | Contradiction returns empty. Otherwise original helper joins all original occurrences with shared/repeated-variable and constant equality before ordered/repeated/Boolean head projection. No source-only query or native result is consulted. |
| ownership | Borrowed request/source maps; helper owns full assignments and result map. |
| failure | Malformed fixture inputs propagate rather than approximating a result. |
| cost | Deliberate full assignment enumeration and projection/deduplication with scalar-width costs; not an incremental mechanism. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0004

[Lines 27–29](../../../../../tests/integration/fallback_oracle.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L29:sha256:649a5e367d3a45c9ba1f3fd3ab32ada7988933099f5fb26d72141baa719fb6c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert exact canonical wire scalars to SQLite equality cells. |
| inputs / outputs | Wire value in; canonical decimal/date text or original integer/bool/string out. |
| invariants | No floating decimal conversion, ordering or arithmetic is used; same-kind scalar equality is exact in the finite corpus. |
| ownership | Owns ordinary normalized scalar payload as needed; no borrowed native data. |
| failure | Malformed scalar encoding fails model operations; no coercion fallback. |
| cost | Canonical decimal parsing proportional to lexical extent; other scalar extraction is bounded or payload-copy work. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0005

[Lines 30–33](../../../../../tests/integration/fallback_oracle.py#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L33:sha256:9a91fca2837291be1c3ffc130e6e06d1bdbc68091e9a2301dada3fc18c7ad17c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State exact SQLite scalar and nullary-source encoding assumptions. |
| inputs / outputs | Comment-only preface to sqlite_state. |
| invariants | Canonical TEXT is used only for equality; nullary physical presence is represented by a dummy column without changing the original zero-width result row. |
| ownership | No owner or runtime state. |
| failure | No executed branch or acceptance receipt. |
| cost | No runtime work from comments. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0006

[Lines 34–95](../../../../../tests/integration/fallback_oracle.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L95:sha256:328f4a6f143d00be558fdee2b8fba7074346a5f9f7cc2fd564bf7ddd12b03496
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently rebuild full source/constraint state and translate the original CQ into SQLite. |
| inputs / outputs | Original document and complete physical row sets in; enforced-constraint validity plus distinct decoded result map out. |
| invariants | Every table including unused sources is materialized; nullary tables receive a dummy cell. Check full UNIQUE/FK including empty keys. Each self occurrence gets an independent SQL alias. Constants, repeated/shared variables and contradiction enter WHERE before DISTINCT projection; ignored fields add no condition. Boolean/no-FROM, repeated heads and type restoration preserve original semantics. Decimal/date TEXT equality and binary strings avoid floating approximation. |
| ownership | Owns temporary SQLite connection, SQL text/bindings/rows and expected result map. Context closes connection on all exits. |
| failure | Constraint false is an explicit returned validity; schema/SQL/model errors propagate. Native output never determines validity or expected rows. |
| cost | Full SQLite table reconstruction, complete constraint queries and SELECT DISTINCT at each observation; external exact reference work, not native timing or complexity. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 96–99](../../../../../tests/integration/fallback_oracle.py#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L99:sha256:8e7cc3333fef0e3204dd5ff23ecdbfc71b67cbdb1b9ae7d59e006bb0b6a2b7e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the independent structural fixture-classification boundary. |
| inputs / outputs | Comment-only preface to acyclic. |
| invariants | Oracle GYO reads set hyperedges only and never native recognition/tree metadata. |
| ownership | No owner or native account. |
| failure | No executed branch. |
| cost | No runtime work from the comment. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0008

[Lines 100–119](../../../../../tests/integration/fallback_oracle.py#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L119:sha256:10d2b6c048030cf7efb4f6e5e249e1a16e6ceaba32dca0245d961000c42cec29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test set-hypergraph acyclicity with an independent literal GYO reduction. |
| inputs / outputs | Variable-set edges in; Boolean acyclic result out. |
| invariants | Copies edges, removes empty/subset/duplicate edges deterministically and removes degree-one variables until empty or unchanged. No query class is borrowed from native Plan. |
| ownership | Owns temporary Python edge sets/degrees; caller inputs remain unchanged. |
| failure | Malformed edge values propagate; irreducible nonempty graph returns false rather than resource exhaustion pretending to be a class. |
| cost | Finite repeated pairwise edge containment and set/degree scans; external fixture recognition, with no claimed optimized recognition bound. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 122–127](../../../../../tests/integration/fallback_oracle.py#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L127:sha256:000e34290a2bbe4b10b15ba7020d31065b4b4fe73b1eac7c903e286de1bc837f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify each original fixture independently as cyclic, non-free-connex or free-connex. |
| inputs / outputs | Document in; one expected class string out. |
| invariants | Scopes use only original atom variables, ignoring constants/ignored columns; first test body, then body plus the head-variable set. Repeated/Boolean heads have their actual set scope. Contradiction does not overwrite structural class. |
| ownership | Owns temporary scopes/head set; borrows document. |
| failure | Malformed fixture fields raise; no native admission state is read. |
| cost | Scope construction plus two independent GYO calls. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [Refactor.md](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0012

[Lines 130–155](../../../../../tests/integration/fallback_oracle.py#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L155:sha256:cdef3f02a1888c07b3e49f18989b0b47a4b1ed1487bf413fd1e3587f747a98fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build deterministic original-query fixtures with nontrivial identifiers and accepted-prefix sequence numbers. |
| inputs / outputs | Literal schemas/atoms/head/actions, declared class, seed and contradiction flag in; empty-initial native request out. |
| invariants | Deep-copy and shuffle tables/atoms, replace occurrence spellings and shuffle variable declaration IDs. Independent classify must match declared fixture class. Proposed complete source state controls constraint acceptance only; refused constraints do not advance sequence. No tree/native fallback result is consulted. |
| ownership | Owns ordinary fixture copies, RNG, provisional source sets and events; no production owner. |
| failure | Class disagreement or malformed fixture references fail immediately. Invalid proposed constraints remain events for actual refusal checks. |
| cost | Full fixture copies and full Python constraint scans per event; deliberately external generator work. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py) |

## B0014

[Lines 158–275](../../../../../tests/integration/fallback_oracle.py#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L275:sha256:ecfb416950e49ac2c96c8ea1cf8e11278958593e24a47f062827a37df94cc2f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare literal cyclic and non-free-connex semantics, projection-witness and source-constraint discriminator traces. |
| inputs / outputs | No input; 28 base cases with 425 serial events before source-backend duplication. |
| invariants | Triangle/cycle4/disconnected cycle+path and endpoint-path classes are explicit; selfalias cycles exercise new-new witnesses. Projection collisions include one-witness and last-witness deletion; repeated/ignored/constants, nullary aliases, empty/contradictory/Boolean queries are retained. Typed cycle5 checks int64 extrema/&gt;2^53, exact 38-digit/scale decimals, dates, bool, binary NUL/nonASCII strings. FK/unused UNIQUE refusal, shuffled IDs, 70-variable one-atom and four seeded traces are included. Wide aliases beyond SQLite join limits remain a separate native unit responsibility. |
| ownership | Owns ordinary literal schemas/actions, source/head metadata and deterministic RNGs. Actual native execution occurs only in main. |
| failure | Corpus construction/model errors propagate; corpus authorship does not claim passing native execution or exhaustive semantics. |
| cost | Finite literal cases plus four 48-event seeded traces; all full model/native work remains additional. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md) |

## B0016

[Lines 278–288](../../../../../tests/integration/fallback_oracle.py#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L278-L288:sha256:05215f52c3e55ca01c406dd7d571accc297346a9c879102825d46afdd022319e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define expected visible guarantee/class/reason strings independently from native serialization. |
| inputs / outputs | Original document in; complete expected profile dictionary out. |
| invariants | Independent GYO determines actual structural class. Contradiction changes reason only; explicit free-connex reference choice is visible. Exact set recomputation/materialization text disclaims constant delay and CROWN/GHD certificate. |
| ownership | Owns ordinary expected strings/dictionary; no native Profile is imported. |
| failure | Invalid fixture class/fields raise; no default acceptance for unknown class. |
| cost | Independent classification and fixed-field dict construction. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0018

[Lines 291–311](../../../../../tests/integration/fallback_oracle.py#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L291-L311:sha256:ccbeff8d5be8898cf22fc0b112eae917711cd2a00d201a94abed2ff731a5b9ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an independently cross-checked committed source/result image and advisory cardinalities. |
| inputs / outputs | Original document, complete sources and committed sequence in; expected full snapshot dictionary out. |
| invariants | Python and SQLite original answers/validity must agree. Original atom/head counts and zero source-only atom count are explicit. Explain products/prefixes follow original occurrence order and raw physical counts even for contradiction; Plan assignment upper instead is zero for contradiction, and Boolean output upper is at most one. Sources count each catalog table once, alias products repeat, and logical state adds source+output upper. Corpus requires exact uint64 products; overflow policy is tested separately by unit tests. |
| ownership | Owns expected maps/counts/JSON-compatible structures; no native state informs results. |
| failure | Independent disagreement, invalid sources or fixture overflow asserts. No unknown estimate is silently replaced by zero. |
| cost | Full Python joins, full SQLite reconstruction/query, table/atom count scans and complete expected-source construction per prefix; not a CPU or memory bound. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp) |

## B0020

[Lines 314–344](../../../../../tests/integration/fallback_oracle.py#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L314-L344:sha256:0411c56c746e30e019193667e12a375ac27309fbe51a02cd419f793974af0faa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate every physical update prefix and exact answer endpoint differences from the original query. |
| inputs / outputs | Request in; independent initial snapshot plus per-event error/physical change/deltas/recompute trigger/current snapshot out. |
| invariants | Contiguous sequence advances only for accepted full source states. Python and SQLite constraint decisions must agree. Invalid constraints retain old sources/results/sequence; accepted noops still advance sequence with no physical change. Before/after set differences preserve projection collisions and aliases. Expected recompute is physical change on an original-used source for noncontradictory query, independent of zero-atom source coordinator routes. |
| ownership | Owns complete current/trial source sets, before/after results and full expected trace; no maintained source or native account is read. |
| failure | Constraint rejection is expected typed evidence, not a committed changed epoch. Sequence/model disagreement asserts without retry. |
| cost | Multiple full joins/SQLite checks and complete trial/snapshot copies per event, deliberately slow and independent. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [Refactor.md](../../../../../Refactor.md) |

## B0022

[Lines 347–350](../../../../../tests/integration/fallback_oracle.py#L347); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L347-L350:sha256:cc3b54892cafe97320274511d6e19ec8e780617945343dd481197a8ca525f414
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize actual endpoint rows while authenticating distinct output. |
| inputs / outputs | Decoded native row list in; deterministically ordered canonical rows out. |
| invariants | Exact decimal lexical variants canonicalize; native row count must equal canonical-map cardinality, so duplicate emissions cannot disappear silently. |
| ownership | Owns ordinary canonical row list/map. |
| failure | Duplicate rows assert; malformed encoding propagates. |
| cost | Complete scalar canonicalization, map insertion and deterministic key sorting. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp) |

## B0024

[Lines 353–357](../../../../../tests/integration/fallback_oracle.py#L353); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L353-L357:sha256:080e0c9ff08d548ba6cb60aa5ead3bdcdadc9a9d53b210cc7332eb5134324e3d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact committed snapshot agreement, including original sources, metadata and guarantee estimates. |
| inputs / outputs | Actual snapshot and expected dictionary in; returns only on complete equality. |
| invariants | Normalize actual answer/source order, then compare all fields including sequence/readiness/existence, original atom/head/account identity, zero-atom coordinator, real Explain and Plan estimates. No subset or result-only check accepts stale source/metadata. |
| ownership | Deep-copies actual wire dictionary for normalization; expected state remains borrowed and unchanged. |
| failure | Any mismatch asserts with actual and expected dictionaries; no repair. |
| cost | Full trace-image deep copy/canonicalization and equality. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp) |

## B0026

[Lines 360–380](../../../../../tests/integration/fallback_oracle.py#L360); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L360-L380:sha256:528eabc39ae7cb07c236203f0fb4d687af3abbc159336e8345b66099cc5f4f08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive every native request/frame against independently computed original-query expectations. |
| inputs / outputs | Actual response, expected model and request ID in; returns only on exact agreement. |
| invariants | Require ID/profile, initial snapshot and exact frame count; compare event errors, physical change, exact added/removed, zero source coordinator aliases, recomputed trigger and output/delta counts on accepted epochs. Compare snapshot after every refusal too. Recompute counts are local protocol observations, not algorithmic proof. |
| ownership | Borrows actual/expected traces; temporary normalized copies are ordinary oracle-owned data. |
| failure | Disagreement is rethrown with case ID/event index; refused event missing success fields is not interpreted as a successful epoch. |
| cost | Complete row/source/frame comparisons; external verification work scales with trace/output size. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0028

[Lines 383–419](../../../../../tests/integration/fallback_oracle.py#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L383-L419:sha256:3c922c601bf8fe1cdf403d87bd5a371d0a17065c9b3692d0305e14921d47405c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run actual fallback requests on both source backends and print PASS only after original-model agreement. |
| inputs / outputs | --driver plus optional --artifacts in; 56 serial native requests, 850 events and 906 images, then actual summary on full success. |
| invariants | Precompute Python/SQLite models for 28 base cases; deep-copy requests separately for reference/indexed native owners. Require native exit zero and exact response count/order before full checks. Capture raw request/stdout/stderr before acceptance assertions when requested. No model-only check is mislabeled native acceptance; no CROWN/GHD or complexity proof is claimed. |
| ownership | Owns full wire, expected traces and subprocess captures; optional artifacts are caller-owned evidence files. Native runtime accounts live only inside the actual driver process. |
| failure | Native failure, malformed output, mismatch or IO error propagates; no retry/substitution. Summary is written only after all observations match. |
| cost | Full external model computation, one actual native subprocess, complete capture/parse and every-prefix comparison; not wall-speedup or whole-suite acceptance evidence. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md) |

## B0029

[Lines 420–423](../../../../../tests/integration/fallback_oracle.py#L420); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L420-L423:sha256:dbad1e561b8500581a5b41ca030f5807d6ea0299228aac9e07fddf40b3aa12b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter native verification only on direct script execution. |
| inputs / outputs | __name__ guard invokes main; importing corpus/reference does not run native code. |
| invariants | Module import can support Python-only model checks independently from native acceptance. |
| ownership | Only declarations/constants exist after import; main owns actual execution arguments/captures. |
| failure | No broad exception wrapper masks failures. |
| cost | Constant guard followed by selected complete oracle workload. |
| Design | [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp) |
