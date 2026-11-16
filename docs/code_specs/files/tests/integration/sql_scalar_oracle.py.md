# `tests/integration/sql_scalar_oracle.py` — block usage map

[Source](../../../../../tests/integration/sql_scalar_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c1d7863a5ef0ce7488cbee58beaa29ca7ef47dde3dee505163d7d0ab0f6ce3b1`. 152 lines partitioned into 17 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/integration/sql_scalar_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 25–29](../../../../../tests/integration/sql_scalar_oracle.py#L25) | Callable definition: def decimal_text(value): | calls format, Decimal, rstrip; returns "0" if Decimal(text) == 0 else text · [reviewed contract](#b0002) |
| [B0003 · 30–31](../../../../../tests/integration/sql_scalar_oracle.py#L30) | Explanatory comments or spacing. |  |
| [B0004 · 32–35](../../../../../tests/integration/sql_scalar_oracle.py#L32) | Callable definition: def parameter(value): | calls isinstance, next, iter, values; returns next(iter(value.values())); value · [reviewed contract](#b0004) |
| [B0005 · 36–37](../../../../../tests/integration/sql_scalar_oracle.py#L36) | Explanatory comments or spacing. |  |
| [B0006 · 38–43](../../../../../tests/integration/sql_scalar_oracle.py#L38) | Callable definition: def encoded(value): | calls isinstance, decimal_text, isoformat; returns {"decimal": decimal_text(value)}; {"date": value.isoformat()} · [reviewed contract](#b0006) |
| [B0007 · 44–45](../../../../../tests/integration/sql_scalar_oracle.py#L44) | Explanatory comments or spacing. |  |
| [B0008 · 46–52](../../../../../tests/integration/sql_scalar_oracle.py#L46) | Callable definition: def bytes_in(value): | calls isinstance, len, encode, decimal_text; returns len(value.encode("utf-8")); len(digits or "0") · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../../tests/integration/sql_scalar_oracle.py#L53) | Explanatory comments or spacing. |  |
| [B0010 · 55–66](../../../../../tests/integration/sql_scalar_oracle.py#L55) | Callable definition: def expected_work(operation, values): | calls in, all, sum, map; returns {"structural_steps": steps, "scalar_fields": 2 if present_comparison else 0,; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 67–68](../../../../../tests/integration/sql_scalar_oracle.py#L67) | Explanatory comments or spacing. |  |
| [B0012 · 69–84](../../../../../tests/integration/sql_scalar_oracle.py#L69) | Callable definition: def sql_expression(operation, columns): | calls in, join, CAST, AssertionError; returns f"{first} {COMPARISONS\[operation\]} {columns\[1\]}"; f"{first} {PREDICATES\[operation\]}"; source comment (unverified): # Identity/literal casts have already been bound to their native type. · [reviewed contract](#b0012) |
| [B0013 · 85–86](../../../../../tests/integration/sql_scalar_oracle.py#L85) | Explanatory comments or spacing. |  |
| [B0014 · 87–119](../../../../../tests/integration/sql_scalar_oracle.py#L87) | Callable definition: def corpus(): | calls in, startswith, append, DECIMAL; 14 loop sites · [reviewed contract](#b0014) |
| [B0015 · 120–121](../../../../../tests/integration/sql_scalar_oracle.py#L120) | Explanatory comments or spacing. |  |
| [B0016 · 122–148](../../../../../tests/integration/sql_scalar_oracle.py#L122) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, getcontext; 5 loop sites · [reviewed contract](#b0016) |
| [B0017 · 149–152](../../../../../tests/integration/sql_scalar_oracle.py#L149) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |

## B0001

[Lines 1–24](../../../../../tests/integration/sql_scalar_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
COMPARISONS =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent SQL spellings and explicit local-kernel oracle limits. |
| inputs / outputs | Python Decimal/date/iteration/JSON/process support, required duckdb import and comparison/predicate maps guide the corpus. |
| invariants | This gate covers local rules only, not bag source/join admission or W05 completion. Fixed DECIMAL cases are explicit; unconstrained mixed-scale NUMERIC needs separate adequate engine coverage. |
| ownership | Module constants are Python test metadata and create no native query state. |
| failure | Missing DuckDB for the chosen Python interpreter fails import; there is no optional skip or silent model fallback. |
| cost | Test-process module import/configuration only; DuckDB is not linked into the C++ runtime. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0002

[Lines 25–29](../../../../../tests/integration/sql_scalar_oracle.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_text(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize exact Python/DuckDB decimal values for public JSON comparison. |
| inputs / outputs | Exact Decimal-compatible value in; fixed-point canonical text out. |
| invariants | Only fractional trailing zeroes are stripped; negative/positive zero becomes 0, and integer zeroes remain significant. main selects precision 200 before corpus use. |
| ownership | New Python Decimal/string objects belong to the oracle. |
| failure | Invalid authored decimal or Python allocation failures propagate; no floating reference value is used. |
| cost | Exact decimal/string work proportional to bounded authored coefficient/spelling width; outside native allocation scopes. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0004

[Lines 32–35](../../../../../tests/integration/sql_scalar_oracle.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parameter(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unwrap valid authored date/decimal tag values for explicit SQL casts. |
| inputs / outputs | A tagged scalar or ordinary Python/NULL value in; its SQL parameter payload out. |
| invariants | Corpus tagged objects have one date or decimal entry. SQL CAST supplies the intended matching type rather than relying on Python/DuckDB inference. |
| ownership | Returns an existing immutable scalar/string reference; native ownership is unaffected. |
| failure | Malformed empty authored tags would raise; the generator creates only valid one-entry tags. |
| cost | Fixed tag/iterator work, external to the C++ kernel. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0006

[Lines 38–43](../../../../../tests/integration/sql_scalar_oracle.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encoded(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map the mature engine result to the native driver’s observable scalar protocol. |
| inputs / outputs | DuckDB Python result in; tagged canonical Decimal/date or ordinary scalar out. |
| invariants | The comparison preserves bool versus integer kind, NULL, string text and date/decimal tags; main additionally checks exact Python JSON value type. |
| ownership | New tag dictionaries/text are oracle-owned; ordinary immutable values are returned directly. |
| failure | Formatting/type conversion failures propagate rather than become expected values. |
| cost | Exact external result formatting only, not native computation or allocation cost. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0008

[Lines 46–52](../../../../../tests/integration/sql_scalar_oracle.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def bytes_in(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive expected selected scalar-width charges independently from observable values. |
| inputs / outputs | Generated scalar in; UTF-8 byte length for strings, canonical nonleading coefficient digit count for decimals, zero otherwise. |
| invariants | Decimal zero has one coefficient digit. Dates/bools/integers add fields but no variable-byte debit. This predicts existing native logical charges, not memory use. |
| ownership | Python strings and Decimal conversions are temporary oracle objects. |
| failure | Invalid authored text or allocation faults propagate; no native private field is read. |
| cost | UTF-8 encoding/string canonicalization cost belongs to the oracle and can scan text, unlike native stored-length lookup. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0010

[Lines 55–66](../../../../../tests/integration/sql_scalar_oracle.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected_work(operation, values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Predict work for visited Boolean operands and present binary comparisons. |
| inputs / outputs | Generated opcode/values in; five-domain work dictionary out. |
| invariants | AND stops at false, OR at true; NULL itself does not stop traversal. A comparison with any NULL has no scalar debit. Present comparisons use two fields and both logical widths. Other domains remain zero here. |
| ownership | New Python counters/dict are test-owned. |
| failure | This assumes the authored well-typed corpus and sequential argument order; it is not a SQL optimizer cost model. |
| cost | Linear in visited/generated argument count plus expected byte calculations; compared only to selected native counters. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0012

[Lines 69–84](../../../../../tests/integration/sql_scalar_oracle.py#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_expression(operation, columns):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the independent scalar SELECT expression over explicitly typed parameters. |
| inputs / outputs | Recognized opcode and generated CAST parameter expressions in; SQL expression text out. |
| invariants | Comparisons/truth tests/NOT/AND/OR use SQL syntax, widening casts to BIGINT, and already-bound identity/literal casts retain the given type. USING is intentionally absent and tested as a native transfer control. |
| ownership | Returns a new SQL string owned by the oracle. |
| failure | Unknown SQL opcode raises AssertionError; no fallback implementation supplies an expected value. |
| cost | External SQL text construction proportional to argument text; this is not C++ runtime work. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0014

[Lines 87–119](../../../../../tests/integration/sql_scalar_oracle.py#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def corpus():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate deterministic matching-type comparisons, nullable truths and representation transfers. |
| inputs / outputs | Fixed BIGINT/VARCHAR/BOOLEAN/DATE groups, seven DECIMAL(38,s) scales, Boolean products and int32 widening boundaries yield 3439 cases. |
| invariants | Includes signed64/above-2^53 values, binary UTF-8 and embedded NUL strings, finite date endpoints, decimal signs/extremes/unit scales and NULL. AND/OR enumerate all 1..4-operand true/false/NULL combinations. No unsupported generic mixed-scale NUMERIC equivalence is claimed. |
| ownership | Generated Python scalar/list objects are oracle-owned and later encoded before the child process runs. |
| failure | A malformed authored constant fails generation/conversion; native admission is not inferred from corpus generation. |
| cost | Finite pair/product enumeration and strings; no large SQL bag expansion or native mutable database is exercised. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0016

[Lines 122–148](../../../../../tests/integration/sql_scalar_oracle.py#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every native scalar observation with one mature-engine result and exact type/work evidence. |
| inputs / outputs | Required driver path in; complete newline corpus sent to one driver, then one DuckDB SELECT per case; summary stdout on success. |
| invariants | Requires zero child status and exact response count/ID; asserts exact JSON value type and value, zero native new requests and exact selected work. DuckDB must use default binary collation and every parameter is explicitly cast to the matching kind. |
| ownership | Python owns corpus/process buffers and in-memory DuckDB connection; native result encoding is observed only through its public protocol. |
| failure | Process failure, wrong/short output, collation mismatch or any value/type/work disagreement fails the gate. DuckDB import/SQL errors propagate; there is no model fallback. |
| cost | 3439 external engine queries plus parsing/reference formatting; this is oracle execution cost, not a runtime or latency theorem. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0017

[Lines 149–152](../../../../../tests/integration/sql_scalar_oracle.py#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the local scalar oracle only as an executable test script. |
| inputs / outputs | Python module-name condition decides whether to call main(). |
| invariants | Importing definitions does not launch the native driver or engine query loop. |
| ownership | The guard stores no resource owner. |
| failure | main() failures remain visible to the test process. |
| cost | Constant guard work; all substantive work belongs to main(). |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |
