# `tests/integration/key_specialization_oracle.py` — block usage map

[Source](../../../../../tests/integration/key_specialization_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5ac7a6ad762d06fcf887a01cb751dc434112eae70039d144fc980966e6ba97d9`. 434 lines partitioned into 45 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/integration/key_specialization_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 15–24](../../../../../tests/integration/key_specialization_oracle.py#L15) | Callable definition: def canonical(value): | calls isinstance, startswith, lstrip, partition; returns {"decimal": ("-" if negative and text != "0" else "") + text}; value · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../../tests/integration/key_specialization_oracle.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–28](../../../../../tests/integration/key_specialization_oracle.py#L27) | Callable definition: def key(value): | calls dumps; returns json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../tests/integration/key_specialization_oracle.py#L29) | Explanatory comments or spacing. |  |
| [B0006 · 31–32](../../../../../tests/integration/key_specialization_oracle.py#L31) | Callable definition: def row_key(row): | calls key, canonical; returns key(\[canonical(value) for value in row\]); 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 33–34](../../../../../tests/integration/key_specialization_oracle.py#L33) | Explanatory comments or spacing. |  |
| [B0008 · 35–36](../../../../../tests/integration/key_specialization_oracle.py#L35) | Callable definition: def ordered(rows): | calls sorted; returns \[rows\[name\] for name in sorted(rows)\]; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 37–38](../../../../../tests/integration/key_specialization_oracle.py#L37) | Explanatory comments or spacing. |  |
| [B0010 · 39–40](../../../../../tests/integration/key_specialization_oracle.py#L39) | Callable definition: def var(name): | calls ; returns {"var": name} · [reviewed contract](#b0010) |
| [B0011 · 41–42](../../../../../tests/integration/key_specialization_oracle.py#L41) | Explanatory comments or spacing. |  |
| [B0012 · 43–44](../../../../../tests/integration/key_specialization_oracle.py#L43) | Callable definition: def const(value): | calls ; returns {"const": value} · [reviewed contract](#b0012) |
| [B0013 · 45–49](../../../../../tests/integration/key_specialization_oracle.py#L45) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 50–52](../../../../../tests/integration/key_specialization_oracle.py#L50) | Callable definition: def table(name, columns): | calls ; returns {"name": name, "columns": \[{"name": column, "type": kind} for column, kind in columns\],; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 53–54](../../../../../tests/integration/key_specialization_oracle.py#L53) | Explanatory comments or spacing. |  |
| [B0016 · 55–56](../../../../../tests/integration/key_specialization_oracle.py#L55) | Callable definition: def unique(name, columns, status="enforced"): | calls ; returns {"kind": "unique", "name": name, "columns": columns, "status": status} · [reviewed contract](#b0016) |
| [B0017 · 57–58](../../../../../tests/integration/key_specialization_oracle.py#L57) | Explanatory comments or spacing. |  |
| [B0018 · 59–61](../../../../../tests/integration/key_specialization_oracle.py#L59) | Callable definition: def foreign(name, columns, target, referenced, status="enforced"): | calls ; returns {"kind": "foreign_key", "name": name, "columns": columns, "status": status, · [reviewed contract](#b0018) |
| [B0019 · 62–63](../../../../../tests/integration/key_specialization_oracle.py#L62) | Explanatory comments or spacing. |  |
| [B0020 · 64–65](../../../../../tests/integration/key_specialization_oracle.py#L64) | Callable definition: def atom(name, source, terms): | calls ; returns {"id": name, "table": source, "terms": terms} · [reviewed contract](#b0020) |
| [B0021 · 66–67](../../../../../tests/integration/key_specialization_oracle.py#L66) | Explanatory comments or spacing. |  |
| [B0022 · 68–81](../../../../../tests/integration/key_specialization_oracle.py#L68) | Callable definition: def document(tables, atoms, head, initial, seed): | calls zip, setdefault, list, Random; returns {"schema_version": 3, "semantics": "set", "catalog": {"version": 1, "tables": tables},; growth new; 6 loop sites; source comment (unverified): # Force nontrivial original/new variable IDs. · [reviewed contract](#b0022) |
| [B0023 · 82–85](../../../../../tests/integration/key_specialization_oracle.py#L82) | Module statements. | source comment (unverified): # These are full source sets. No optimizer/native projection participates in · [reviewed contract](#b0023) |
| [B0024 · 86–104](../../../../../tests/integration/key_specialization_oracle.py#L86) | Callable definition: def python_constraints(tables, state): | calls enumerate, get, tuple, key; returns False; False; 12 loop sites · [reviewed contract](#b0024) |
| [B0025 · 105–106](../../../../../tests/integration/key_specialization_oracle.py#L105) | Explanatory comments or spacing. |  |
| [B0026 · 107–130](../../../../../tests/integration/key_specialization_oracle.py#L107) | Callable definition: def python_query(doc, state): | calls enumerate, values, dict, zip; returns result; 7 loop sites · [reviewed contract](#b0026) |
| [B0027 · 131–132](../../../../../tests/integration/key_specialization_oracle.py#L131) | Explanatory comments or spacing. |  |
| [B0028 · 133–134](../../../../../tests/integration/key_specialization_oracle.py#L133) | Callable definition: def quote(name): | calls replace; returns '"' + name.replace('"', '""') + '"' · [reviewed contract](#b0028) |
| [B0029 · 135–136](../../../../../tests/integration/key_specialization_oracle.py#L135) | Explanatory comments or spacing. |  |
| [B0030 · 137–140](../../../../../tests/integration/key_specialization_oracle.py#L137) | Callable definition: def sql_value(value): | calls isinstance, get; returns value.get("date", value.get("decimal")); value · [reviewed contract](#b0030) |
| [B0031 · 141–145](../../../../../tests/integration/key_specialization_oracle.py#L141) | Module statements. | source comment (unverified): # SQLite evaluates a separately translated original CQ and complete constraints. · [reviewed contract](#b0031) |
| [B0032 · 146–204](../../../../../tests/integration/key_specialization_oracle.py#L146) | Callable definition: def sqlite_state(doc, state): | calls enumerate, connect, zip, join; returns valid, result; 15 loop sites · [reviewed contract](#b0032) |
| [B0033 · 205–206](../../../../../tests/integration/key_specialization_oracle.py#L205) | Explanatory comments or spacing. |  |
| [B0034 · 207–212](../../../../../tests/integration/key_specialization_oracle.py#L207) | Callable definition: def state_snapshot(doc, state, sequence): | calls python_query, sqlite_state, ordered; returns {"sequence": sequence, "ready": True, "rows": ordered(expected),; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 213–214](../../../../../tests/integration/key_specialization_oracle.py#L213) | Explanatory comments or spacing. |  |
| [B0036 · 215–250](../../../../../tests/integration/key_specialization_oracle.py#L215) | Callable definition: def make_case(name, tables, atoms, head, initial, pool, prefix, removed, seed): | calls document, enumerate, items, canonical; returns {"id": name, "document": doc, "events": events, "removed": removed}, {"initial": expected_initial, …; growth insert; 9 loop sites · [reviewed contract](#b0036) |
| [B0037 · 251–252](../../../../../tests/integration/key_specialization_oracle.py#L251) | Explanatory comments or spacing. |  |
| [B0038 · 253–345](../../../../../tests/integration/key_specialization_oracle.py#L253) | Callable definition: def corpus(): | calls add, append, make_case, len; returns \[p, c\]; \[row\[1\], row\[4\], row\[0\], row\[3\], row\[2\], tag\]; growth insert; 3 loop sites · [reviewed contract](#b0038) |
| [B0039 · 346–347](../../../../../tests/integration/key_specialization_oracle.py#L346) | Explanatory comments or spacing. |  |
| [B0040 · 348–353](../../../../../tests/integration/key_specialization_oracle.py#L348) | Callable definition: def compare_snapshot(actual, expected): | calls row_key, len, zip; 5 loop sites · [reviewed contract](#b0040) |
| [B0041 · 354–355](../../../../../tests/integration/key_specialization_oracle.py#L354) | Explanatory comments or spacing. |  |
| [B0042 · 356–390](../../../../../tests/integration/key_specialization_oracle.py#L356) | Callable definition: def receive(actual, request, expected): | calls len, set, range, remove; 11 loop sites · [reviewed contract](#b0042) |
| [B0043 · 391–392](../../../../../tests/integration/key_specialization_oracle.py#L391) | Explanatory comments or spacing. |  |
| [B0044 · 393–430](../../../../../tests/integration/key_specialization_oracle.py#L393) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, corpus; 9 loop sites · [reviewed contract](#b0044) |
| [B0045 · 431–434](../../../../../tests/integration/key_specialization_oracle.py#L431) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0045) |

## B0001

[Lines 1–14](../../../../../tests/integration/key_specialization_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:c8c3a3bd038e84652485bfa34eaeaa1ba6111fe19c1d0df57ada00b379d135b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent original-query oracle and deterministic seed. |
| inputs / outputs | Imports ordinary Python/SQLite/process utilities and fixes the corpus seed. |
| invariants | No production optimizer/adaptation helper is imported for expected results. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0002

[Lines 15–24](../../../../../tests/integration/key_specialization_oracle.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L24:sha256:43a2962c76cd845997144bdb9ad22bbc71ceccd1844cf01f295364002de6843b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize the corpus exact decimal representation. |
| inputs / outputs | Plain decimal fixture JSON becomes numeric canonical text; other typed values pass unchanged. |
| invariants | No floating-point conversion; this helper does not claim arbitrary input-domain validation. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0004

[Lines 27–28](../../../../../tests/integration/key_specialization_oracle.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L28:sha256:bbae3e43a00b1fa6c43701da4a62d99a01899c2cb951fa9a1504aa961911f3ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one typed JSON value deterministically. |
| inputs / outputs | JSON value becomes a compact sorted-key string. |
| invariants | JSON bool/int/string/date/decimal tags remain distinguishable. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0006

[Lines 31–32](../../../../../tests/integration/key_specialization_oracle.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:f54a3281b0ab4e0dde4ce02a0ce611cdefbf796d21f2432beaad4c4a501e997c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give one complete physical row a canonical equality key. |
| inputs / outputs | Canonical scalar sequence becomes deterministic JSON key. |
| invariants | Full row identity is retained before query projection. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0008

[Lines 35–36](../../../../../tests/integration/key_specialization_oracle.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L36:sha256:09a70bf19fc2349bb9ea4f04de65ff8cf8f81afad8af438378bd3725d39b4f1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit a deterministic list from a mathematical keyed set. |
| inputs / outputs | Row-key dictionary becomes ordered caller data. |
| invariants | Order is artifact stability only; result comparison uses set identity. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0010

[Lines 39–40](../../../../../tests/integration/key_specialization_oracle.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L40:sha256:c228db6f619723b8f264a3c5f206beab73f6b9393f67ca9810006b6905ac3210
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a query variable term. |
| inputs / outputs | Name becomes var-tagged test JSON. |
| invariants | This is corpus data, not a native variable or optimizer authority. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0012

[Lines 43–44](../../../../../tests/integration/key_specialization_oracle.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L44:sha256:9042a8533b49c77966c4c649d367a98e90ec884dc80d11706a4870bb02be2c19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a query constant term. |
| inputs / outputs | Typed value becomes const-tagged test JSON. |
| invariants | Constants remain explicit restrictions in the original query. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0013

[Lines 45–49](../../../../../tests/integration/key_specialization_oracle.py#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L49:sha256:d1e2c58fbc0ca8e08289649dd6416ec2e62c2fbe10b11d37f043435a0f2e070c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the independent wildcard term. |
| inputs / outputs | One immutable ignore-tagged fixture value is shared by corpus construction. |
| invariants | Underscore/wildcard is not treated as a join equality. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0014

[Lines 50–52](../../../../../tests/integration/key_specialization_oracle.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L52:sha256:39ec4d5c5c92b315b439866c08a2f04bc170a8ea47b37baab60965dde817fc31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one physical source schema. |
| inputs / outputs | Table/column definitions become ordinary catalog JSON with initially empty constraints. |
| invariants | Every later row is complete for that source schema. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0016

[Lines 55–56](../../../../../tests/integration/key_specialization_oracle.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L56:sha256:21f642ad006b2976c4ac1e8bf671d6e7b986bd39af79b0e9c8fe5b67a6689839
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a declared UNIQUE constraint. |
| inputs / outputs | Name/columns/status become tagged catalog data. |
| invariants | Only enforced status is semantic authority; empty key remains permitted. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0018

[Lines 59–61](../../../../../tests/integration/key_specialization_oracle.py#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L61:sha256:b0f12061463c6cb30c7722ce6a57e5410598b13b5b619c936bfa01d33c9566ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an ordered declared FK mapping. |
| inputs / outputs | Source columns, target and referenced columns/status become catalog JSON. |
| invariants | Correspondence order is explicit and is not replaced by matching set names. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0020

[Lines 64–65](../../../../../tests/integration/key_specialization_oracle.py#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:4b7c7043ca37bf25b140ca406dd291954f3b27054cb3ecf9b5b01bcea4e733e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an original atom occurrence. |
| inputs / outputs | Name/source/terms become one independent occurrence. |
| invariants | Same-table aliases retain separate IDs. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0022

[Lines 68–81](../../../../../tests/integration/key_specialization_oracle.py#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L81:sha256:a0e0360fcf77655d6c47beb981aa7d3bee2f1147f0285ddf1eba5cbf3298a928
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an original document with deliberately permuted variable IDs. |
| inputs / outputs | Infers consistent variable types, shuffles declaration order deterministically and retains original atom/head/source order. |
| invariants | No reduced-query metadata enters this input; all declared variables appear in original atom terms. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0023

[Lines 82–85](../../../../../tests/integration/key_specialization_oracle.py#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L85:sha256:0e9dd9df2bd74fc338de681c975eee50a679c0a13b78323cfb9f201508a118a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the source-state independence boundary. |
| inputs / outputs | Comments state what the two following materializing definitions consume. |
| invariants | No native support/routing or optimizer projection is an expected-answer source. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0024

[Lines 86–104](../../../../../tests/integration/key_specialization_oracle.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L104:sha256:5be4094cd330199a3a2b3f3089a444d4598066563ece6931ac7457e11ec136f2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate complete candidate source constraints independently in Python. |
| inputs / outputs | All enforced UNIQUE/FK projections over exact source sets produce a Boolean acceptance decision. |
| invariants | Unused tables, self/cyclic references and empty unit keys remain included; untrusted metadata is ignored semantically. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0026

[Lines 107–130](../../../../../tests/integration/key_specialization_oracle.py#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L130:sha256:afa3202a3dfcca87abd542c9e0805ec0bbf54f9a3d9a101fa70d5f1db27720f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the full original CQ from physical rows. |
| inputs / outputs | Expands compatible original assignments, constants/repeated variables and final set projection. |
| invariants | No native adapter, reduced query or specialized route is used as the oracle. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0028

[Lines 133–134](../../../../../tests/integration/key_specialization_oracle.py#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L134:sha256:e72f4ba40db5aafa8b7dc88d734e4801b62365b665888bd7861f3a06e7094e8e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote controlled schema identifiers for SQLite. |
| inputs / outputs | Identifier becomes an escaped quoted SQL name. |
| invariants | Values remain bound parameters rather than interpolated SQL. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0030

[Lines 137–140](../../../../../tests/integration/key_specialization_oracle.py#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L140:sha256:ee0158c183ad167d0176715acff41e9fca5b84e308f3fccea5597167adc14193
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind canonical typed fixture scalars to SQLite equality domains. |
| inputs / outputs | Date/decimal tags become exact canonical TEXT; ordinary scalars pass as native bind values. |
| invariants | This corpus uses equality only, so no approximate numeric affinity/arithmetic is introduced. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0031

[Lines 141–145](../../../../../tests/integration/key_specialization_oracle.py#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L145:sha256:0123d16fd9fae9d79cc0ece52db30e49f2b47ca72dbcdccccc2cdcebe92f867c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the exact SQLite crosscheck scope. |
| inputs / outputs | Comments explain canonical TEXT equality and lack of arithmetic/ordering. |
| invariants | These adapters do not claim a general SQL decimal arithmetic implementation. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0032

[Lines 146–204](../../../../../tests/integration/key_specialization_oracle.py#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L204:sha256:3b8f215666b94815a26ec785ad4aea8941795490a83bb1fbe69faf6dd34a8280
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently check constraints and translate the original CQ through SQLite. |
| inputs / outputs | A fresh small in-memory database yields full-state constraint validity and SELECT DISTINCT result set. |
| invariants | All original occurrences/filters/head fields are translated; neither native optimizer decisions nor Python join assignments supply SQL answers. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0034

[Lines 207–212](../../../../../tests/integration/key_specialization_oracle.py#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L212:sha256:a9eaf62ed88b8a3def20498fcf41bc4bec46fbd0c95e31ea67deabc2ec236c1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive an independent committed-state expectation. |
| inputs / outputs | Python original join and SQLite original join must agree on a valid full source state. |
| invariants | Expected snapshot records source rows and sequence, including no-output/unused tables. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0036

[Lines 215–250](../../../../../tests/integration/key_specialization_oracle.py#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L215-L250:sha256:1dd116c252b043ab48a74ab1eb04f8df3b1ddcc65b4656bda56f96d3379d51ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate one bounded deterministic accepted/rejected event trace. |
| inputs / outputs | Explicit prefixes plus 40 sampled physical events derive independent candidate-state decisions and endpoint snapshots. |
| invariants | Rejected updates preserve source/sequence; successful no-ops still advance; native output is not consulted. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0038

[Lines 253–345](../../../../../tests/integration/key_specialization_oracle.py#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L345:sha256:8f638981c5671cc49af2a238c5412c0aac5d579c4fecc9a452fa60e810c3fa66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the discriminating finite key-specialization corpus. |
| inputs / outputs | 22 query families cover real rewrites, ineligible guards, alias/cycle/unit/composite keys and source enforcement. |
| invariants | Expected removals are declared test requirements; output/state expectations remain independent full-state computations. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0040

[Lines 348–353](../../../../../tests/integration/key_specialization_oracle.py#L348); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L348-L353:sha256:4cfffa7f67e298416626fd39bcd440dd313dd23d100636842afbe5a289096b6d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an actual native snapshot to independent state. |
| inputs / outputs | Sequence/readiness and exact result/source sets are checked. |
| invariants | All original catalog tables are compared even when their native routes disappear. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0042

[Lines 356–390](../../../../../tests/integration/key_specialization_oracle.py#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L356-L390:sha256:6ed6101f6a1074b2229b8ef16d7c30ac756fe2cb5bc412101aba60704a2d8b26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive actual rewrite metadata, outcomes and route actions. |
| inputs / outputs | Checks removals/live witnesses, provenance/head/certificate scope, every result/source/error and selected alias/constraint counters. |
| invariants | Output agreement alone cannot certify specialization: physical route reduction and unchanged source enforcement are also required. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0044

[Lines 393–430](../../../../../tests/integration/key_specialization_oracle.py#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L393-L430:sha256:992223523455dedcd6d1f703204e5f49ca1390a10ac337140144ee26ed42dad3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the genuine driver and retain optional complete reproducibility artifacts. |
| inputs / outputs | Builds both-backend requests, runs one native process, receives every frame and emits finite-case summary. |
| invariants | Artifact target must be absent; raw request/expected/stdout/stderr are saved before result assertions. No pass is emitted on process/mismatch failure. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0045

[Lines 431–434](../../../../../tests/integration/key_specialization_oracle.py#L431); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L431-L434:sha256:dbad1e561b8500581a5b41ca030f5807d6ea0299228aac9e07fddf40b3aa12b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the CLI only for direct script execution. |
| inputs / outputs | Main module execution enters main(); imports remain available for model-only preflight. |
| invariants | Importing this file does not run native checks. |
| ownership | Python owns corpus/expected/SQLite/process artifacts outside native query accounts; actual native owners retain their own independent accounts. |
| failure | Assertion, SQLite/process/IO or comparison failure fails this test; candidate constraint refusal is expected data and is checked against unchanged committed state. No production retry is added. |
| cost | Finite offline/test corpus and exact full-state materialization/SQLite work; output/artifact bytes and driver invocation are test costs, not a native maintenance bound. |
| Design | [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |
