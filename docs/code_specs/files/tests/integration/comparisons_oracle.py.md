# `tests/integration/comparisons_oracle.py` — block usage map

[Source](../../../../../tests/integration/comparisons_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c88c02be0dbc90bffae87d7e331540cb5385b9d4e6e83d1b47429e339b3819a2`. 378 lines partitioned into 29 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/comparisons_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–24](../../../../../tests/integration/comparisons_oracle.py#L21) | Callable definition: def scalar(value): | calls isinstance, Fraction, encode; returns Fraction(value\["decimal"\]) if "decimal" in value else value\["date"\]; value.encode("utf-8") if isins… · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../../tests/integration/comparisons_oracle.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–43](../../../../../tests/integration/comparisons_oracle.py#L27) | Callable definition: def holds(predicate, assignment): | calls operand, scalar; returns scalar(assignment\[value\["var"\]\] if "var" in value else value\["value"\]); left == right · [reviewed contract](#b0004) |
| [B0005 · 44–45](../../../../../tests/integration/comparisons_oracle.py#L44) | Explanatory comments or spacing. |  |
| [B0006 · 46–74](../../../../../tests/integration/comparisons_oracle.py#L46) | Callable definition: def python_query(request, state): | calls get, enumerate, values, dict; returns {}; result; 8 loop sites; source comment (unverified): # Keep hidden comparands and all witnesses until predicates finish. · [reviewed contract](#b0006) |
| [B0007 · 75–76](../../../../../tests/integration/comparisons_oracle.py#L75) | Explanatory comments or spacing. |  |
| [B0008 · 77–86](../../../../../tests/integration/comparisons_oracle.py#L77) | Callable definition: def sql_scalar(value): | calls isinstance, Fraction, str, zfill; returns str(encoded).zfill(77); value\["date"\] if isinstance(value, dict) else value; source comment (unverified): # Exact monotone integer bias encoded as fixed-width BINARY TEXT. This · [reviewed contract](#b0008) |
| [B0009 · 87–88](../../../../../tests/integration/comparisons_oracle.py#L87) | Explanatory comments or spacing. |  |
| [B0010 · 89–98](../../../../../tests/integration/comparisons_oracle.py#L89) | Callable definition: def sql_decode(value, kind): | calls int, divmod, abs, str; returns relational.canonical({"decimal": text}); {"date": value} · [reviewed contract](#b0010) |
| [B0011 · 99–100](../../../../../tests/integration/comparisons_oracle.py#L99) | Explanatory comments or spacing. |  |
| [B0012 · 101–168](../../../../../tests/integration/comparisons_oracle.py#L101) | Callable definition: def sqlite_query(request, state): | calls enumerate, connect, zip, join; returns bound\[value\["var"\]\]; "?"; 16 loop sites · [reviewed contract](#b0012) |
| [B0013 · 169–170](../../../../../tests/integration/comparisons_oracle.py#L169) | Explanatory comments or spacing. |  |
| [B0014 · 171–173](../../../../../tests/integration/comparisons_oracle.py#L171) | Callable definition: def predicate(left, op, right): | calls isinstance; returns {"left": {"var": left} if isinstance(left, str) else {"value": left}, "op": op, · [reviewed contract](#b0014) |
| [B0015 · 174–175](../../../../../tests/integration/comparisons_oracle.py#L174) | Explanatory comments or spacing. |  |
| [B0016 · 176–197](../../../../../tests/integration/comparisons_oracle.py#L176) | Callable definition: def case(name, tables, atoms, head, predicates, operations, seed, contradiction=False): | calls deepcopy, Random, shuffle, document; returns {"id": name, "document": document, "predicates": predicates, "events": events}; growth insert; 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 198–199](../../../../../tests/integration/comparisons_oracle.py#L198) | Explanatory comments or spacing. |  |
| [B0018 · 200–270](../../../../../tests/integration/comparisons_oracle.py#L200) | Callable definition: def corpus(): | calls table, atom, var, enumerate; returns cases; growth insert; 20 loop sites; source comment (unverified): # Constant comparison uses exact typed values, including string · [reviewed contract](#b0018) |
| [B0019 · 271–272](../../../../../tests/integration/comparisons_oracle.py#L271) | Explanatory comments or spacing. |  |
| [B0020 · 273–277](../../../../../tests/integration/comparisons_oracle.py#L273) | Callable definition: def expected_snapshot(request, state, sequence): | calls python_query, sqlite_query, deepcopy; returns {"sequence": sequence, "rows": expected, "source": copy.deepcopy(state)} · [reviewed contract](#b0020) |
| [B0021 · 278–279](../../../../../tests/integration/comparisons_oracle.py#L278) | Explanatory comments or spacing. |  |
| [B0022 · 280–307](../../../../../tests/integration/comparisons_oracle.py#L280) | Callable definition: def reference(request): | calls expected_snapshot, python_query, deepcopy, row_key; returns initial, trace; growth insert; 4 loop sites · [reviewed contract](#b0022) |
| [B0023 · 308–309](../../../../../tests/integration/comparisons_oracle.py#L308) | Explanatory comments or spacing. |  |
| [B0024 · 310–313](../../../../../tests/integration/comparisons_oracle.py#L310) | Callable definition: def rows(value): | calls row_key, canonical, len; returns result; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 314–315](../../../../../tests/integration/comparisons_oracle.py#L314) | Explanatory comments or spacing. |  |
| [B0026 · 316–321](../../../../../tests/integration/comparisons_oracle.py#L316) | Callable definition: def compare_snapshot(actual, expected, request): | calls len, rows, bool; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 322–323](../../../../../tests/integration/comparisons_oracle.py#L322) | Explanatory comments or spacing. |  |
| [B0028 · 324–374](../../../../../tests/integration/comparisons_oracle.py#L324) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, corpus; 7 loop sites · [reviewed contract](#b0028) |
| [B0029 · 375–378](../../../../../tests/integration/comparisons_oracle.py#L375) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |

## B0001

[Lines 1–20](../../../../../tests/integration/comparisons_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:e986bab8c786960cb962d14451efe00ecd469b03fa179c954d972301244728d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import independent full-state reference tools and declare the exact operator/decimal wire conventions. |
| inputs / outputs | Python imports, deterministic seed, six SQL spellings and integer encoding constants. |
| invariants | Imports no native comparison evaluator or maintenance state. Fraction and SQLite provide distinct exact reference mechanisms; no float conversion. |
| ownership | Module-level ordinary oracle constants; no native runtime/account. |
| failure | Import errors fail the script; authoring is not native acceptance. |
| cost | Import/setup cost outside native measurements. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 21–24](../../../../../tests/integration/comparisons_oracle.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L24:sha256:5fd28c3bb2aa75df798fee1d8dcacd33ddf82913fda513a3b608bf218c8cfc1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an exact wire scalar to the Python predicate-order domain. |
| inputs / outputs | Canonical JSON scalar in; Fraction for decimals, ISO date string, UTF8 bytes for text or inline int/bool out. |
| invariants | Input cases are non-null same-kind direct-CQ values. UTF8 bytes model binary text including NUL; Fraction preserves complete decimal precision. |
| ownership | Owns ordinary Python converted reference values. |
| failure | Malformed expected scalars propagate errors; no approximation fallback. |
| cost | Exact Fraction parsing or UTF8 conversion proportional to scalar extent. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0004

[Lines 27–43](../../../../../tests/integration/comparisons_oracle.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L43:sha256:21529ead5a15d48b82293ff56ea2461cd93ac2692298065f0de42ad1db75e7c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate one explicit predicate on a complete original assignment. |
| inputs / outputs | Predicate and variable-name assignment in; exact Boolean out. |
| invariants | Nested operand resolver reads full assignment or typed literal before projection. All six branches preserve operand order; no CQ equality folding. |
| ownership | Borrows request/assignment; temporary exact Python scalar conversions are oracle-owned. |
| failure | Missing variable/bad scalar/unknown op fails; no native comparison helper is reused. |
| cost | Two exact scalar conversions/comparison per predicate, with Python big-int/byte-width costs. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 46–74](../../../../../tests/integration/comparisons_oracle.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L74:sha256:f96248c7b9c35a0f8eb053b3ae77672eb079205597a6c95fba0edac006b4ede1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the original comparison CQ by full physical joins then predicate filtering then head projection. |
| inputs / outputs | Request and complete original source sets in; canonical distinct result map out. |
| invariants | Original contradiction is empty; no atoms starts with one empty assignment. Constants and shared variables match at full-row level. All hidden comparands/witnesses remain until every predicate passes; only afterward are repeated/Boolean heads projected and deduplicated. |
| ownership | Owns ordinary full assignment copies and result map; no native plan/group/cursor state participates. |
| failure | Malformed original model data raises; assertions are not replaced by production output. |
| cost | Deliberately full intermediate Cartesian joins, assignment copying, predicates and result-set materialization; no native or dynamic bound claim. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 77–86](../../../../../tests/integration/comparisons_oracle.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L86:sha256:5dbfa1f45c09c7633b90cddd974d351331ad30e68fdc78268b93fdca821fd464
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode exact decimals in SQLite BINARY TEXT with monotone complete-domain order. |
| inputs / outputs | Wire value in; 77-character biased scaled integer for decimal, ISO text for date, or original scalar out. |
| invariants | Decimal times 10^38 is integral over the 38-digit/38-scale domain; adding 10^76 and zero-padding to 77 preserves signed numeric order and equality. No SQLite numeric affinity/float approximation is used. |
| ownership | Owns arbitrary-precision integer/string reference encoding. |
| failure | Nonintegral/out-of-domain encoding asserts; malformed values raise. |
| cost | Big-rational/integer arithmetic and fixed 77-character decimal presentation. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0010

[Lines 89–98](../../../../../tests/integration/comparisons_oracle.py#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L98:sha256:59b242bce771d19f597391224e81c323b1ad320c002100a012a0bc4166321a0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode exact SQLite projected values back into canonical typed wire scalars. |
| inputs / outputs | SQLite cell and original head ScalarType name in; canonical decimal/date/bool/other value out. |
| invariants | Decimal bias is reversed with integer divmod by 10^38 and canonicalized, preserving sign/scale without float. Type restoration follows original head variable types. |
| ownership | Owns ordinary decoded expected JSON scalars. |
| failure | Bad encoded text/type data fails rather than weakening equality. |
| cost | Exact big-integer parse/divmod and bounded decimal string rendering. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py) |

## B0012

[Lines 101–168](../../../../../tests/integration/comparisons_oracle.py#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L168:sha256:c662cc75e5ff596f2c34ae002715685332cb1d08bb3ed6fe49d85df473f77e15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently translate the complete original comparison CQ and enforced constraints into SQLite. |
| inputs / outputs | Request plus full original source sets in; independent after-state validity and distinct answer map out. |
| invariants | Creates each physical table and alias separately; checks UNIQUE/FK including unused tables. Original constants/shared variables and explicit comparison predicates become SQL WHERE clauses. Nested operand closure binds constants in exact placeholder order. Contradiction, Boolean head and no-FROM SQL remain exact; types are restored independently on output. |
| ownership | Owns temporary in-memory SQLite connection, ordinary encoded rows/SQL/bindings and decoded expected output; context closes connection on every exit. |
| failure | SQL/schema/encoding errors and malformed model input propagate. A failing constraint returns validity false; no native admission decision is consulted. |
| cost | Rebuilds full SQLite state, executes full constraint queries and SELECT DISTINCT per observation; deliberately external full recomputation, not native runtime timing. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 171–173](../../../../../tests/integration/comparisons_oracle.py#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L173:sha256:9021742e71fef6fc375cc64a77165199ff1e35c8c4aaeca79c29d7fbb82dd28f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct concise literal predicate fixtures without altering execution semantics. |
| inputs / outputs | Variable-name strings or nonstring literal scalars plus op in; wire predicate object out. |
| invariants | Strings mean variable references in this convenience helper. Typed string constants are built explicitly by corpus(), avoiding ambiguity. |
| ownership | Owns new ordinary fixture dicts. |
| failure | Operation/type validity is established by fixtures and independently checked native admission, not silently coerced here. |
| cost | Small dict construction. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |

## B0016

[Lines 176–197](../../../../../tests/integration/comparisons_oracle.py#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L197:sha256:d6445ccb6a4cacbfae0f6bab4bde337307c903d75e4bfe44892957d9144c966a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build deterministic original catalog/query requests with nontrivial IDs and valid retry sequence numbers. |
| inputs / outputs | Schemas/atoms/head/predicates/actions/seed/contradiction flag in; empty-initial request with physical events out. |
| invariants | Copies and shuffles table/atom order; relational.document shuffles declared variable IDs. Sequence advances only for a valid proposed full after-state. Predicate truth does not determine source acceptance; constraint failures retry the same next sequence. |
| ownership | Owns ordinary copied source fixtures, full temporary source sets and wire events; no native owner. |
| failure | Invalid fixture references or unsupported actions fail normal model operations; no maintained source is edited. |
| cost | Full fixture copies and constraint scans per event; deterministic external oracle generation. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py) |

## B0018

[Lines 200–270](../../../../../tests/integration/comparisons_oracle.py#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L270:sha256:7f0a08c185666be647edb021922d65b03bc5dfe610a9ce0fdd519e9902f845a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare held-out comparison semantics and exact-delta discriminator traces. |
| inputs / outputs | No input; 43 base requests cover six operators, hidden/projection witnesses, typed boundaries, aliases, constraints, constants and seeded updates. |
| invariants | Tests INT64 extrema/&gt;2^53, TEXT NUL/nonASCII binary order, exact full-domain decimals, finite dates and bools; typed constants compare before projection. Includes self-source aliases with equality, repeated/Boolean heads, unused UNIQUE/FK targets, contradiction and no-FROM empty/true/false conjunctions. Source/atom/variable IDs are shuffled, not native physical IDs assumed fixed. |
| ownership | Owns literal ordinary fixture/action collections and deterministic RNGs; native execution occurs only through main later. |
| failure | Fixture construction errors propagate; corpus authorship is not a passing native receipt. |
| cost | Finite literal construction and 4x45 randomized source actions; full models/native work remain additional. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0020

[Lines 273–277](../../../../../tests/integration/comparisons_oracle.py#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L273-L277:sha256:346ef47398020462a5e9e9816db7d1bda4859a133b60f51717ef04b5bcef9b1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require two independent original predicate-aware definitions to agree at a committed snapshot. |
| inputs / outputs | Request, full source state and sequence in; expected sequence/rows/deep-copied source image out. |
| invariants | Python filters complete assignments before projection; independent SQLite predicates/constraints must produce the same canonical answers and valid sources. |
| ownership | Owns complete expected source copy and ordinary result maps. |
| failure | Any independent disagreement asserts with case identity; no native result can redefine expected rows. |
| cost | Full Python joins plus full SQLite reconstruction/query and source copy per prefix. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0022

[Lines 280–307](../../../../../tests/integration/comparisons_oracle.py#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L280-L307:sha256:be2b081241b61db2b4eb87507792118f1f11ef4d7178b0a81b298bef5ade1d46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute every accepted/refused source prefix and exact endpoint set difference. |
| inputs / outputs | One request in; initial expected image and per-event error/change/added/removed/current images out. |
| invariants | Before/after answers use original complete sources. Both constraint definitions agree; invalid sequence or constraints retain previous sources/sequence. Deltas are exact after-minus-before and before-minus-after, preserving projection collisions and no-op epochs. |
| ownership | Owns ordinary current/proposed source copies and full expected trace; no production state is imported. |
| failure | Model disagreement raises. Source rejection is expected evidence, not a successful changed epoch. |
| cost | Multiple complete model/SQLite evaluations and source copies per event; not incremental algorithm evidence. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md) |

## B0024

[Lines 310–313](../../../../../tests/integration/comparisons_oracle.py#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L310-L313:sha256:199caf3289506985a6a155a2c4927e87d03bc5698e5a3b8576cf743daa4de2c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize actual native rows and reject duplicate endpoint emissions. |
| inputs / outputs | Decoded row list in; canonical-keyed row map out. |
| invariants | Decimal scales normalize for exact identity; input list length must equal map cardinality, so native duplicates are not silently discarded. |
| ownership | Owns ordinary Python canonical copies. |
| failure | Duplicate rows assert; malformed encodings raise. |
| cost | Full row/scalar canonicalization and map construction. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp) |

## B0026

[Lines 316–321](../../../../../tests/integration/comparisons_oracle.py#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L316-L321:sha256:516a61bd17f847bb84189b0550d6391389d2452480040cc4f9396c5d5f3fb80e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual committed snapshots with full original-query expected images. |
| inputs / outputs | Actual wire snapshot, expected image and request in; returns only on exact agreement. |
| invariants | Checks sequence/readiness, original-account binding, predicate count, full answer set/existence and every original physical table. Comparison never uses only the projected equality answer. |
| ownership | Borrows decoded observations and expected images; temporary canonical maps are oracle-owned. |
| failure | Any mismatch asserts; no result repair or relaxed comparison. |
| cost | Full answer and source-map equality/canonicalization. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp) |

## B0028

[Lines 324–374](../../../../../tests/integration/comparisons_oracle.py#L324); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L324-L374:sha256:c1eb47949c5baa3d9b6d571c807a1ee51d9d9ec505bc28c7e6f2754ff5794822
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the actual native comparison driver on both source backends and receive its original-model trace. |
| inputs / outputs | --driver and optional --artifacts in; 86 native requests, 1528 source events and pass summary only after full agreement. |
| invariants | Precomputes independent Python/SQLite expectations once per base case; creates independent native requests for both backends. Requires native exit zero and exact response count/order, original plan invariance, every snapshot/refusal/physical-change observation and exact added/removed sets plus their counts. Artifacts retain actual requests/stdout/stderr before assertion checking. |
| ownership | Owns complete wire, expected traces and captured subprocess output; explicit artifact directory retains caller-owned evidence. Native runtimes own their own accounts inside the driver. |
| failure | Native nonzero, malformed output or discrepancy raises; case mismatches are rethrown with ID. No retry, synthetic pass or automatic native acceptance from earlier Python-only model execution. |
| cost | All independent full-state model work plus one native subprocess executing all serial cases and complete output capture/parse. No wall-clock or CQC complexity claim. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md) |

## B0029

[Lines 375–378](../../../../../tests/integration/comparisons_oracle.py#L375); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L375-L378:sha256:dbad1e561b8500581a5b41ca030f5807d6ea0299228aac9e07fddf40b3aa12b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the comparison oracle only for direct script execution. |
| inputs / outputs | __name__ guard invokes main; importing the corpus/reference for model-only checks does not run a native process. |
| invariants | No top-level native side effects on import; actual main success is required to print PASS. |
| ownership | Entry point owns its arguments/captures; module import owns only declarations/constants. |
| failure | No broad exception wrapper masks main failures; assertions/IO/native errors remain process failures. |
| cost | Constant guard then the complete selected oracle workload. |
| Design | [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py), [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp) |
