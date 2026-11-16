# `tests/integration/difference_oracle.py` — block usage map

[Source](../../../../../tests/integration/difference_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3b754a35010b50159a0a5d50f7e11c1d7e74004f665e17966b9bb9d473a74181`. 508 lines partitioned into 43 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/integration/difference_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 23–50](../../../../../tests/integration/difference_oracle.py#L23) | Callable definition: def python_operand(doc, state): | calls get, Counter, enumerate, values; returns {}, Counter(); rows, counts; 7 loop sites · [reviewed contract](#b0002) |
| [B0003 · 51–52](../../../../../tests/integration/difference_oracle.py#L51) | Explanatory comments or spacing. |  |
| [B0004 · 53–61](../../../../../tests/integration/difference_oracle.py#L53) | Callable definition: def python_difference(left, right, state, mode): | calls python_operand, Counter, items, int; returns rows, counts; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 62–66](../../../../../tests/integration/difference_oracle.py#L62) | Module statements. | source comment (unverified): # Raw CQ SELECTs deliberately omit DISTINCT. Grouped counts and the residual · [reviewed contract](#b0005) |
| [B0006 · 67–90](../../../../../tests/integration/difference_oracle.py#L67) | Callable definition: def operand_sql(doc): | calls enumerate, append, quote, str; returns sql, parameters; 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 91–92](../../../../../tests/integration/difference_oracle.py#L91) | Explanatory comments or spacing. |  |
| [B0008 · 93–100](../../../../../tests/integration/difference_oracle.py#L93) | Callable definition: def decode_row(doc, raw): | calls zip, append, bool; returns result; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 101–104](../../../../../tests/integration/difference_oracle.py#L101) | Module statements. | source comment (unverified): # Complete original sources and constraints are materialized independently. · [reviewed contract](#b0009) |
| [B0010 · 105–160](../../../../../tests/integration/difference_oracle.py#L105) | Callable definition: def sqlite_difference(left, right, state, mode): | calls connect, zip, join, quote; returns valid, rows, counts, operands; 14 loop sites; source comment (unverified): # Verify both raw operand bags independently before checking difference. · [reviewed contract](#b0010) |
| [B0011 · 161–162](../../../../../tests/integration/difference_oracle.py#L161) | Explanatory comments or spacing. |  |
| [B0012 · 163–167](../../../../../tests/integration/difference_oracle.py#L163) | Callable definition: def document_pair(request): | calls deepcopy; returns left, right · [reviewed contract](#b0012) |
| [B0013 · 168–169](../../../../../tests/integration/difference_oracle.py#L168) | Explanatory comments or spacing. |  |
| [B0014 · 170–197](../../../../../tests/integration/difference_oracle.py#L170) | Callable definition: def make_case(name, tables, left, right, operations, seed): | calls deepcopy, Random, shuffle, enumerate; returns {"id": name, "document": ldoc, "right_query": rdoc\["query"\], "events": events}; growth insert; 9 loop sites · [reviewed contract](#b0014) |
| [B0015 · 198–199](../../../../../tests/integration/difference_oracle.py#L198) | Explanatory comments or spacing. |  |
| [B0016 · 200–312](../../../../../tests/integration/difference_oracle.py#L200) | Callable definition: def corpus(): | calls add, append, make_case, len; returns cases; growth insert; 11 loop sites · [reviewed contract](#b0016) |
| [B0017 · 313–314](../../../../../tests/integration/difference_oracle.py#L313) | Explanatory comments or spacing. |  |
| [B0018 · 315–325](../../../../../tests/integration/difference_oracle.py#L315) | Callable definition: def expected_profile(left, right, mode): | calls ; returns {"mode": mode, "backend": "exact_difference_recompute_v1", · [reviewed contract](#b0018) |
| [B0019 · 326–327](../../../../../tests/integration/difference_oracle.py#L326) | Explanatory comments or spacing. |  |
| [B0020 · 328–336](../../../../../tests/integration/difference_oracle.py#L328) | Callable definition: def operand_estimates(doc, counts): | calls enumerate, get, sum; returns {"source_rows": sum(counts), "assignments_upper": product, "output_rows_upper": outputs,; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 337–338](../../../../../tests/integration/difference_oracle.py#L337) | Explanatory comments or spacing. |  |
| [B0022 · 339–346](../../../../../tests/integration/difference_oracle.py#L339) | Callable definition: def expected_estimates(left, right, counts, mode): | calls operand_estimates, sum; returns {"left": lbound, "right": rbound, "source_rows": sum(counts),; 1 loop sites; source comment (unverified): # Bag Boolean projection retains every witness even though its one empty · [reviewed contract](#b0022) |
| [B0023 · 347–348](../../../../../tests/integration/difference_oracle.py#L347) | Explanatory comments or spacing. |  |
| [B0024 · 349–356](../../../../../tests/integration/difference_oracle.py#L349) | Callable definition: def cartesian(doc, counts): | calls enumerate; returns product, prefix; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 357–358](../../../../../tests/integration/difference_oracle.py#L357) | Explanatory comments or spacing. |  |
| [B0026 · 359–360](../../../../../tests/integration/difference_oracle.py#L359) | Callable definition: def entries(rows, counts): | calls sorted; returns \[{"values": rows\[key\], "multiplicity": counts\[key\]} for key in sorted(counts)\]; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 361–362](../../../../../tests/integration/difference_oracle.py#L361) | Explanatory comments or spacing. |  |
| [B0028 · 363–379](../../../../../tests/integration/difference_oracle.py#L363) | Callable definition: def snapshot(request, state, sequence): | calls document_pair, python_difference, sqlite_difference, all; returns {"sequence": sequence, "runtime_sequence": sequence, "ready": True, "rows": entries(rows, counts),; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 380–381](../../../../../tests/integration/difference_oracle.py#L380) | Explanatory comments or spacing. |  |
| [B0030 · 382–411](../../../../../tests/integration/difference_oracle.py#L382) | Callable definition: def reference(request): | calls document_pair, snapshot, get, canonical; returns {"profile": expected_profile(left, right, request\["mode"\]), "initial": initial, "frames": frames}; growth insert; 7 loop sites · [reviewed contract](#b0030) |
| [B0031 · 412–413](../../../../../tests/integration/difference_oracle.py#L412) | Explanatory comments or spacing. |  |
| [B0032 · 414–417](../../../../../tests/integration/difference_oracle.py#L414) | Callable definition: def normalized_rows(rows): | calls row_key, canonical, len, ordered; returns relational.ordered(result); 2 loop sites · [reviewed contract](#b0032) |
| [B0033 · 418–419](../../../../../tests/integration/difference_oracle.py#L418) | Explanatory comments or spacing. |  |
| [B0034 · 420–432](../../../../../tests/integration/difference_oracle.py#L420) | Callable definition: def normalized_entries(values, change=False): | calls canonical, row_key, ordered; returns relational.ordered(result); 2 loop sites · [reviewed contract](#b0034) |
| [B0035 · 433–434](../../../../../tests/integration/difference_oracle.py#L433) | Explanatory comments or spacing. |  |
| [B0036 · 435–439](../../../../../tests/integration/difference_oracle.py#L435) | Callable definition: def check_snapshot(actual, expected): | calls deepcopy, normalized_entries, normalized_rows; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 440–441](../../../../../tests/integration/difference_oracle.py#L440) | Explanatory comments or spacing. |  |
| [B0038 · 442–457](../../../../../tests/integration/difference_oracle.py#L442) | Callable definition: def check_output(actual, expected, case_id): | calls check_snapshot, len, enumerate, zip; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 458–459](../../../../../tests/integration/difference_oracle.py#L458) | Explanatory comments or spacing. |  |
| [B0040 · 460–467](../../../../../tests/integration/difference_oracle.py#L460) | Callable definition: def requests_and_models(): | calls corpus, deepcopy, append, reference; returns cases, requests, models; 2 loop sites · [reviewed contract](#b0040) |
| [B0041 · 468–469](../../../../../tests/integration/difference_oracle.py#L468) | Explanatory comments or spacing. |  |
| [B0042 · 470–504](../../../../../tests/integration/difference_oracle.py#L470) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, requests_and_models; 9 loop sites · [reviewed contract](#b0042) |
| [B0043 · 505–508](../../../../../tests/integration/difference_oracle.py#L505) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |

## B0001

[Lines 1–22](../../../../../tests/integration/difference_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:315c71bdfa2d811f71d5d8a96f89164328b0ea72fb685204d93a871a31809142
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import test-only relational/scalar/structural helpers and fixed corpus state. |
| inputs / outputs | Python standard-library modules, existing cold fixture helpers, seed and uint64 maximum define offline verification context. |
| invariants | The Counter evaluator and SQLite difference CTE below do not call native maintenance. Reused helpers supply scalar canonicalization, fixture DTOs, source constraints and independent GYO labels. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Module import and fixed metadata construction. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 23–50](../../../../../tests/integration/difference_oracle.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L50:sha256:26aaa8da819cd0094a538be57a364ff84ac44f1606c33cff66c4756e9c75976c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the full original positive-CQ operand bag independently. |
| inputs / outputs | Original document plus full physical source sets become projected row representatives and a Counter of complete-assignment multiplicities. |
| invariants | Every self-alias chooses its own row. Hidden and ignored fields can multiply witnesses; constants/repeated variables filter before projection. Contradiction yields an empty bag and a true empty body yields one empty tuple. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Materializes all join prefixes/assignments, copies candidate bindings and counts every complete witness; deliberately slow finite reference work. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 53–61](../../../../../tests/integration/difference_oracle.py#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L61:sha256:66c5b567c6bec885af191d4c757e46d60822e4bee169cf839d7e317786b56da7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define set EXCEPT and bag EXCEPT ALL from independent operand bags. |
| inputs / outputs | Two original Counter bags become positive residual counts and left-side row representatives. |
| invariants | Set mode keeps a left key exactly when the right key is absent. Bag mode computes max(left_count-right_count,0), with arbitrary-precision Python integers. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Two full operand joins plus linear projected-key count subtraction; no native helper is consulted. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 62–66](../../../../../tests/integration/difference_oracle.py#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L66:sha256:b109da175ef6e10087ffb9c6b3afcfbfffd696d19c54d9f782fd299221b2964b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the independent SQLite count-difference construction. |
| inputs / outputs | The note states that raw operands omit DISTINCT and residuals use grouped counts plus LEFT JOIN. |
| invariants | SQLite EXCEPT ALL is not assumed. This note is design context; successful SQL/native execution is separate evidence. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | No executable work. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 67–90](../../../../../tests/integration/difference_oracle.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L90:sha256:678134087fee5125c558b2065315c8414a985899f3157e1d504bd1f7abfdc00d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate one original positive CQ into a raw SQLite SELECT. |
| inputs / outputs | Atoms, exact constants and ordered/repeated head positions yield SQL text and bound parameters. |
| invariants | Raw output preserves all witnesses. main-qualified physical tables avoid CTE-name shadowing; equality tests precede projection and contradiction adds a false condition. Nullary projection uses one synthetic c0 field. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear metadata/string translation; SQL execution occurs in the caller. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 93–100](../../../../../tests/integration/difference_oracle.py#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L100:sha256:b6ae8b73e3203aa1494b232fc53c465a86024051310e50dc1daa99fdc20434f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode SQLite head cells back to exact typed oracle scalars. |
| inputs / outputs | Original head/variable kinds and a raw SQL row become Decimal/Date wrappers, Boolean or scalar values. |
| invariants | Nullary synthetic fields are discarded; Decimal/Date text is not converted to floating point. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear in original output width and ordinary Python container creation. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 101–104](../../../../../tests/integration/difference_oracle.py#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L104:sha256:204ee018d4c88666db30fed529b6099dbbfa42cfdc95fb22703220315683bc14
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe independent full-source SQL and exact-type boundaries. |
| inputs / outputs | The adjacent note names source/constraint materialization and canonical Decimal/Date TEXT equality. |
| invariants | The corpus uses no ordered or arithmetic Decimal SQL comparison; this is not general SQLite/native scalar equivalence. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | No executable work. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 105–160](../../../../../tests/integration/difference_oracle.py#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L160:sha256:ae5f4f03a2874799acb112ae521cbcf202e9c5ba8967eb5b9e25f72cca4f53d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate original operand bags and residual difference with independent SQLite SQL. |
| inputs / outputs | Full source sets are loaded into an in-memory database; complete UNIQUE/FK checks, grouped raw operand counts and a LEFT JOIN count-difference CTE produce validity and residual bags. |
| invariants | Source tables remain sets because input dictionaries contain full-row identities. Nullary tables get a dummy field; nullary head gets a dummy grouping key. SQL computes residual counts itself, rather than receiving Python residuals. Canonical text equality avoids decimal float loss. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Creates/loads all sources and runs full constraints, two grouped operand queries and the residual CTE for every checked state; finite oracle work, not native overhead. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 163–167](../../../../../tests/integration/difference_oracle.py#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L167:sha256:8ada0d6883a3b138eaabb46972482079c7545959593af2ca83b633b4890bc014
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover both original operand documents from one request. |
| inputs / outputs | The original left document is borrowed; a deep copy replaces only query with right_query. |
| invariants | Both operands use byte-equivalent original catalog/source metadata; the right query is not derived from native recognition or result state. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Deep ordinary Python document copy plus query assignment. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 170–197](../../../../../tests/integration/difference_oracle.py#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L197:sha256:f9b69ca3f435efe8239e826dcd325b05ef14463366c5141bef2f4ce0ea4d3271
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a reproducible original query-pair and contiguous source-event trace. |
| inputs / outputs | Named tables/operand specs/operations plus a seed become shuffled catalog/atom/variable DTOs and events. |
| invariants | Physical and variable declaration order are independently permuted. Sequence advances in the fixture only after full-source Python constraint acceptance; invalid events reuse the next uncommitted sequence. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Cold fixture copying/shuffling and full reference constraint checks per operation. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 200–312](../../../../../tests/integration/difference_oracle.py#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L312:sha256:6369aeb89fbdb5255bb7ff81dbc293df1b9ae384ebe1f51fa118e43180d8bea2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define finite held-out difference fixtures and seeded source prefixes. |
| inputs / outputs | Twenty-eight base cases cover numeric collisions/right-only changes, Boolean/nullary/empty/contradictory operands, aliases, repeated/ignored/constant terms, cyclic/non-free-connex/disconnected bodies, exact types and full-source constraints. |
| invariants | Both modes/backends are applied later. Physical inserts remain sets; bag multiplicity comes from original complete row assignments. Typed Decimal/date cases use exact equality, including NUL/UTF8 and integer/date bounds. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Finite test data construction and seeded traces; no algorithm registration, native execution or performance certification. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 315–325](../../../../../tests/integration/difference_oracle.py#L315); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L315-L325:sha256:75eaa78337af9772722cfd7508f2665ca106a82641eabca968d237f5d81ff70d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define expected explicit difference profile labels from original query structure. |
| inputs / outputs | Independent GYO labels/reasons, selected mode and literal public semantic/cost descriptors, including exact endpoint multiplicity replacements, become an expected JSON profile. |
| invariants | Original operand classes/reasons are not borrowed from native output or the source-only empty query. Bag semantics name physical-set witness counts. Delta metadata describes nonnegative before/after replacements; signed magnitude remains a separate derived Change::delta diagnostic. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Independent finite hypergraph reductions and fixed dictionary construction. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0020

[Lines 328–336](../../../../../tests/integration/difference_oracle.py#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L328-L336:sha256:541d4c787d7aaf3e056a4189c4d07f01b0c7a72befc35b9bbcd069790a72e2af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute original operand advisory Cartesian/row bounds. |
| inputs / outputs | Full table cardinalities and original query atoms/head produce exact fixture assignment, output-key and committed-state upper bounds. |
| invariants | Contradiction yields assignment zero; Boolean compressed output is at most one while witness multiplicity remains separate. Fixtures assert no uint64 overflow instead of silently wrapping. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear atom/cardinality visits with Python exact arithmetic. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0022

[Lines 339–346](../../../../../tests/integration/difference_oracle.py#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L339-L346:sha256:1762e86cfd599361ef1fde083a55cbc0221b022a576acbbb19d1d99aa8bb507b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute conservative combined residual bounds independently. |
| inputs / outputs | Both original operand bounds and mode produce source rows, left key bound, left witness/mass bound and committed logical state rows. |
| invariants | Never subtract operand upper bounds. Bag Boolean residual mass uses left assignment count even though it has one compressed key. Private images/journals and peak bytes are excluded. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Two cold operand-bound calculations plus fixed exact arithmetic. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0024

[Lines 349–356](../../../../../tests/integration/difference_oracle.py#L349); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L349-L356:sha256:3ff448157ea974f752a8d76abacf17fccfa25d7931295d60b4f9ecc354b4f48c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute full Cartesian and intermediate-prefix diagnostics from original atoms. |
| inputs / outputs | Ordered occurrence cardinalities produce an exact product and sum of prefix products. |
| invariants | These diagnostics do not apply equality selectivity or contradiction filtering. Fixtures keep both values within uint64; a large prefix is not equated with final answer count. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear atom visits and arbitrary-precision arithmetic. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0026

[Lines 359–360](../../../../../tests/integration/difference_oracle.py#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L359-L360:sha256:e659f1f106899a17ef4a437c5c4a24cd19e189c80201d46a36af141a2503373c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a positive compressed expected bag deterministically. |
| inputs / outputs | Row representatives and Counter entries become sorted values/multiplicity records. |
| invariants | Only keys already retained by the residual Counter are emitted; no expanded copies are materialized. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear compressed-key record construction plus key sorting. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0028

[Lines 363–379](../../../../../tests/integration/difference_oracle.py#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L363-L379:sha256:828378cfc5911caa738966a501b5b5c3afda8d9ffefd69f338ce04bd0f1e98c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check independent original-pair models and define a complete expected checkpoint. |
| inputs / outputs | Python residual/operand bags, separately computed SQLite bags, full sources and source sequence produce exact compressed results, profiles, diagnostics and bounds. |
| invariants | The two difference definitions and both raw operand bags must agree before any native comparison. Original sources, owning-account expectations and both sequence views remain observable. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Full Python/SQLite recomputation, source serialization, profile classification and bounds at every checkpoint. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0030

[Lines 382–411](../../../../../tests/integration/difference_oracle.py#L382); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L382-L411:sha256:4a7612e1b4435248335025231a8eb210c7f0021608452e0e974f5b2c2d85edbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define every original source prefix and numeric endpoint replacement. |
| inputs / outputs | A request starts with empty physical sets; valid updates advance sequence, invalid constraints preserve state; before/after residual counters determine exact changes. |
| invariants | Changed positive counts remain visible even without membership change. Signed magnitude uses exact Python arithmetic. Recompute eligibility uses changed physical membership and table use by a noncontradictory original operand. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Per-event full-source proposal/constraint checks, before/after operand joins, exact numeric differences and complete checkpoint recomputation. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0032

[Lines 414–417](../../../../../tests/integration/difference_oracle.py#L414); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L414-L417:sha256:19e64ae0cb59e82c5b51cba3f956c416e3ffdd8598cd87e19fa1c68ac773071a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize and reject duplicate actual physical source exports. |
| inputs / outputs | Native row arrays become canonical scalar rows sorted by independent JSON identity. |
| invariants | Two identical full rows are an error; canonical Decimal forms are normalized before comparison. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear scalar canonicalization and ordered-key sorting. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0034

[Lines 420–432](../../../../../tests/integration/difference_oracle.py#L420); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L420-L432:sha256:c3f4d10549ddb86af958687dae25f84b9e8114836c9b5bee19c6a73ad13cb168
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize actual compressed snapshots or numeric endpoint changes. |
| inputs / outputs | Actual value/count records are keyed canonically and sorted; malformed duplicate/nonpositive/unchanged records fail. |
| invariants | Counts stay uint64-sized Python integers without expanded copies. Before/after plus actual delta sign/magnitude remain independently compared, rather than collapsing changes to presence. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear record checks/canonicalization and compressed-key sorting. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0036

[Lines 435–439](../../../../../tests/integration/difference_oracle.py#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L435-L439:sha256:bdefbe7d3a3ac95d0a715becb16d46bb3aced2b8a851ece381deab16a7019e35
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one complete actual checkpoint with its independently defined state. |
| inputs / outputs | A copied actual snapshot normalizes output entries/source rows, then exact dictionary equality checks every field. |
| invariants | Missing, extra or wrong source/result/sequence/profile/account/bound fields fail; output ordering is not mistaken for source-backend semantics. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Full checkpoint copy/normalization and equality comparison. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0038

[Lines 442–457](../../../../../tests/integration/difference_oracle.py#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L442-L457:sha256:df14c2c8873a7a3c7f1eaf805ae51776596621aa00bf28e8d5bc4720b1fe437e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual native transport with the independent event-by-event model. |
| inputs / outputs | ID/profile/initial checkpoint and every actual event/error/change/metrics/checkpoint are verified against the model. |
| invariants | Constraint errors cannot advance committed source state. Successful events must have zero source alias routes, exact numeric changes and expected recomputation/change-count metrics. Assertion context identifies request/event only. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Linear transport traversal plus complete per-checkpoint comparison; assertion exception wrapping is test diagnostics, not runtime error handling. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0040

[Lines 460–467](../../../../../tests/integration/difference_oracle.py#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L460-L467:sha256:cb147f33e2406f8cbc79212a18d4570082f1b9bcf769f4ada2a84a1e188b46b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand every base fixture into both exact difference modes and independent models. |
| inputs / outputs | Deep-copied cases receive set_except/bag_except_all and unique IDs; reference() computes expected original-pair behavior. |
| invariants | No native process runs here. Each mode keeps the same original source trace and a separate model. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | All finite fixture model computations in both modes. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0042

[Lines 470–504](../../../../../tests/integration/difference_oracle.py#L470); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L470-L504:sha256:39c4d0edff075cd4f4081793853e9857eb1177b66fbdf64eea9b238f5d069bd0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the actual native driver and retain raw request/output evidence when requested. |
| inputs / outputs | --driver and optional --artifacts select one subprocess over both backend/mode corpus variants; all outputs are independently checked before actual counts are reported. |
| invariants | Only completed native return code, request/output cardinality and model comparisons permit PASS. Artifacts preserve request and raw stdout/stderr even on later comparison failure. Summary counts derive from actual requests; they are not predicted unit checks or timing claims. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Full independent models, one actual driver process, raw I/O/materialization and per-event verification; two backends multiply the finite corpus. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0043

[Lines 505–508](../../../../../tests/integration/difference_oracle.py#L505); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L505-L508:sha256:dbad1e561b8500581a5b41ca030f5807d6ea0299228aac9e07fddf40b3aa12b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the oracle only as an executable script. |
| inputs / outputs | The __name__ guard calls main(). |
| invariants | Normal imports permit Python/SQLite model-only checks without executing a native driver. |
| ownership | Test-owned ordinary Python documents, dictionaries, Counter bags, SQLite connection and subprocess/artifact buffers. Native internal ownership is observed through explicit driver exports, never shared with expected state. |
| failure | Invalid fixtures, model disagreements, SQL/process/I/O failures or assertions propagate to the oracle process; the per-event checker adds request/index context only. No native recovery/retry path is introduced. |
| cost | Fixed guard plus selected entry-point work. |
| Design | [tests/integration/difference_oracle.py](../../../../../tests/integration/difference_oracle.py), [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |
