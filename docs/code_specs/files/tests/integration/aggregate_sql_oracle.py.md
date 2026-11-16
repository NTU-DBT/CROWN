# `tests/integration/aggregate_sql_oracle.py` — block usage map

[Source](../../../../../tests/integration/aggregate_sql_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e96d3a712c5f7e1d2291594ec67fee7c9e6a124572cf1eb1ea6feb60ee6e2047`. 326 lines partitioned into 27 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/integration/aggregate_sql_oracle.py#L1) | Imports dependencies; declares aliases; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–32](../../../../../tests/integration/aggregate_sql_oracle.py#L22) | Callable definition: def numeric(value, scale=0): | calls Fraction, abs, str, rjust; returns {"decimal": digits} · [reviewed contract](#b0002) |
| [B0003 · 33–34](../../../../../tests/integration/aggregate_sql_oracle.py#L33) | Explanatory comments or spacing. |  |
| [B0004 · 35–36](../../../../../tests/integration/aggregate_sql_oracle.py#L35) | Callable definition: def change(values, before, after): | calls list; returns {"values": list(values), "before": before, "after": after} · [reviewed contract](#b0004) |
| [B0005 · 37–38](../../../../../tests/integration/aggregate_sql_oracle.py#L37) | Explanatory comments or spacing. |  |
| [B0006 · 39–48](../../../../../tests/integration/aggregate_sql_oracle.py#L39) | Callable definition: def make_case(name, outputs, groups=(), updates=(), scale=18, source=True, model=False): | calls COUNT, upper, join, list; returns {"request": {"id": name, "sql": sql, "average_scale": scale, "updates": list(updates)},; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 49–50](../../../../../tests/integration/aggregate_sql_oracle.py#L49) | Explanatory comments or spacing. |  |
| [B0008 · 51–53](../../../../../tests/integration/aggregate_sql_oracle.py#L51) | Callable definition: def decimal_sum(argument): | calls ; returns argument == "x" or "BIGINT" in argument; source comment (unverified): # The test schema declares x bigint; uncast small integer constants are int32. · [reviewed contract](#b0008) |
| [B0009 · 54–55](../../../../../tests/integration/aggregate_sql_oracle.py#L54) | Explanatory comments or spacing. |  |
| [B0010 · 56–65](../../../../../tests/integration/aggregate_sql_oracle.py#L56) | Callable definition: def argument_value(argument, row): | calls startswith, CAST, int; returns row\[COLUMNS\[argument\]\]; None · [reviewed contract](#b0010) |
| [B0011 · 66–67](../../../../../tests/integration/aggregate_sql_oracle.py#L66) | Explanatory comments or spacing. |  |
| [B0012 · 68–103](../../../../../tests/integration/aggregate_sql_oracle.py#L68) | Callable definition: def sql_snapshot(connection, case, state): | calls execute, executemany, VALUES, items; returns result; 6 loop sites · [reviewed contract](#b0012) |
| [B0013 · 104–105](../../../../../tests/integration/aggregate_sql_oracle.py#L104) | Explanatory comments or spacing. |  |
| [B0014 · 106–128](../../../../../tests/integration/aggregate_sql_oracle.py#L106) | Callable definition: def sql_count_check(connection, case, state, observed): | calls enumerate, in, execute, executemany; returns sum(len(values) for values in expected.values()); 10 loop sites · [reviewed contract](#b0014) |
| [B0015 · 129–130](../../../../../tests/integration/aggregate_sql_oracle.py#L129) | Explanatory comments or spacing. |  |
| [B0016 · 131–162](../../../../../tests/integration/aggregate_sql_oracle.py#L131) | Callable definition: def model_snapshot(case, state): | calls items, tuple, setdefault, append; returns result; 8 loop sites · [reviewed contract](#b0016) |
| [B0017 · 163–164](../../../../../tests/integration/aggregate_sql_oracle.py#L163) | Explanatory comments or spacing. |  |
| [B0018 · 165–172](../../../../../tests/integration/aggregate_sql_oracle.py#L165) | Callable definition: def observed_groups(snapshot): | calls tuple, AssertionError; returns result; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 173–174](../../../../../tests/integration/aggregate_sql_oracle.py#L173) | Explanatory comments or spacing. |  |
| [B0020 · 175–182](../../../../../tests/integration/aggregate_sql_oracle.py#L175) | Callable definition: def expected_event(previous, following): | calls keys, get, len, AssertionError; returns None; {"key": list(key), "before": previous.get(key), "after": following.get(key)}; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 183–184](../../../../../tests/integration/aggregate_sql_oracle.py#L183) | Explanatory comments or spacing. |  |
| [B0022 · 185–215](../../../../../tests/integration/aggregate_sql_oracle.py#L185) | Callable definition: def verify(case, response, connection): | calls sql_snapshot, oracle, len, observed_groups; returns len(updates) + 1, unchanged, count_checks; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 216–217](../../../../../tests/integration/aggregate_sql_oracle.py#L216) | Explanatory comments or spacing. |  |
| [B0024 · 218–289](../../../../../tests/integration/aggregate_sql_oracle.py#L218) | Callable definition: def cases(): | calls change, append, make_case, range; returns result; 10 loop sites · [reviewed contract](#b0024) |
| [B0025 · 290–291](../../../../../tests/integration/aggregate_sql_oracle.py#L290) | Explanatory comments or spacing. |  |
| [B0026 · 292–322](../../../../../tests/integration/aggregate_sql_oracle.py#L292) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, cases; 4 loop sites · [reviewed contract](#b0026) |
| [B0027 · 323–326](../../../../../tests/integration/aggregate_sql_oracle.py#L323) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |

## B0001

[Lines 1–21](../../../../../tests/integration/aggregate_sql_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SEED = 0xA6640C04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare deterministic corpus configuration and the SQL versus exact-model reference boundary. |
| inputs / outputs | Imports provide SQLite, exact Fraction arithmetic and subprocess I/O; seed, signed count bound and column positions guide generated cases. |
| invariants | Expanded small bags use SQL statistics; compressed large COUNT uses SQL weighted-sum identities; wide SUM/AVG remain exact-model checks without floating expected values. |
| ownership | Module constants are immutable scalar/dictionary test metadata; imported facilities create no native runtime state. |
| failure | Import failures stop the checker before native execution. |
| cost | Fixed import/constant initialization outside native updates. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0002

[Lines 22–32](../../../../../tests/integration/aggregate_sql_oracle.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def numeric(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round an exact rational to the declared fixed decimal scale for comparison. |
| inputs / outputs | Integer/Fraction and nonnegative corpus scale in; canonical decimal-text object out. |
| invariants | Integer formula floor((2*abs(n)*10^s+d)/(2*d)) implements exact nearest rounding with ties away; zero has no minus sign. |
| ownership | New Python integers, strings and dict are oracle-owned; no native representation is inspected. |
| failure | Invalid Fraction construction or Python allocation failure propagates; generated scale is any integer 0..18. |
| cost | Arbitrary-precision integer scaling/division plus coefficient text length; this is independent reference cost. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [exact paper reference](https://docs.python.org/3/library/fractions.html) |

## B0004

[Lines 35–36](../../../../../tests/integration/aggregate_sql_oracle.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def change(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one plain row-weight replacement request. |
| inputs / outputs | Row tuple and exact before/after integers in; values list and weight dict out. |
| invariants | Weights remain exact Python integers for JSON serialization. |
| ownership | Returned list copies the row container and borrows immutable scalar objects. |
| failure | Python allocation failures propagate. |
| cost | Fixed three-cell request construction for this corpus. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0006

[Lines 39–48](../../../../../tests/integration/aggregate_sql_oracle.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_case(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build matching SQL and independent fixture descriptors from a small authored output list. |
| inputs / outputs | Case name, output kind/argument tuples, group columns, replacements and mode in; request plus oracle metadata out. |
| invariants | The descriptor grammar is trusted and limited; it is not a second general SQL parser. |
| ownership | Returned case retains its own request/update list and immutable descriptor objects. |
| failure | Malformed author descriptors or allocation errors fail generation. |
| cost | Linear SQL construction in output/group/operation counts; no logical bag expansion. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0008

[Lines 51–53](../../../../../tests/integration/aggregate_sql_oracle.py#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_sum(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify SUM fixtures whose public result type is decimal. |
| inputs / outputs | Authored argument spelling in; true for bigint x or explicit BIGINT cast. |
| invariants | All other generated SUM arguments are small int32 constants, so they retain bigint output. |
| ownership | Argument is borrowed; boolean result owns nothing. |
| failure | No parser validation is attempted; adding new argument types requires updating this fixture rule. |
| cost | Fixed tests plus substring search in a short authored argument. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0010

[Lines 56–65](../../../../../tests/integration/aggregate_sql_oracle.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def argument_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the restricted fixture arguments in the independent compressed-bag model. |
| inputs / outputs | Known column/literal/cast spelling and one row in; scalar or None out. |
| invariants | Only generated arguments are accepted; this helper never uses native aggregate descriptors. |
| ownership | Returned row/literal scalars are immutable Python values. |
| failure | Unexpected spellings fail integer conversion rather than silently emulating SQL. |
| cost | Fixed argument dispatch and bounded literal parsing for corpus expressions. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0012

[Lines 68–103](../../../../../tests/integration/aggregate_sql_oracle.py#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use real SQLite grouping/count/sum execution to compute a small-bag expected snapshot. |
| inputs / outputs | SQLite connection, authored case and compressed Python bag in; group-key to output-value map out. |
| invariants | Only small SQL cases are expanded; AVG derives from exact SQLite integer SUM and COUNT, not SQLite floating AVG. |
| ownership | Connection owns the temporary SQL table; result dict and rounded decimal values are Python-owned. |
| failure | SQLite errors, unexpected descriptor shape or allocation failures abort the test. |
| cost | Expands total small-bag multiplicity, executes GROUP BY/COUNT/SUM and materializes all groups on every observation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [exact paper reference](https://www.sqlite.org/lang_aggfunc.html) |

## B0014

[Lines 106–128](../../../../../tests/integration/aggregate_sql_oracle.py#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_count_check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check native large-bag COUNT results using actual SQLite compressed-weight count identities. |
| inputs / outputs | Connection, authored model case, positive row weights and observed group map in; number of verified count scalar cells out. |
| invariants | Every model case uses a named logical input and has COUNT output positions. Per-group positive weights sum at most INT64_MAX, so integer SQL SUM(weight) and NULL-filtered subsets are exact; global empty coalesces to zero and grouped empty has no row. |
| ownership | weighted_r stores one row per distinct logical input. SQL/native comparison maps are test-owned; no native payload or weight-expanded row is retained. |
| failure | SQLite overflow/query errors propagate; wrong native integer domain, full group identity or COUNT values fail assertions. Argument SQL is trusted fixture spelling, not arbitrary user input. |
| cost | One insert per distinct input row plus one GROUP BY/SUM/CASE query and count-position comparison per model snapshot; independent of expanded multiplicity. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [exact paper reference](https://www.sqlite.org/lang_aggfunc.html) |

## B0016

[Lines 131–162](../../../../../tests/integration/aggregate_sql_oracle.py#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def model_snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact compressed large-bag expected results independently of native arithmetic. |
| inputs / outputs | Authored case and row-to-weight bag in; full group identities and ordered results out. |
| invariants | Group existence follows positive input weight, global empty remains one group, and no-FROM is one implicit nullary contribution. |
| ownership | Temporary grouped lists reference immutable rows; all sums and rounded values are Python-owned. |
| failure | Invalid authored arguments, Fraction/count errors or allocation failures propagate. |
| cost | Linear scans of distinct rows per output with arbitrary-precision sums; weights are never expanded. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0018

[Lines 165–172](../../../../../tests/integration/aggregate_sql_oracle.py#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def observed_groups(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert observed public group arrays to an order-independent identity map. |
| inputs / outputs | Native snapshot JSON in; key-tuple to output-value list mapping out. |
| invariants | Duplicate group identities fail even if their value projections match. |
| ownership | New dict/tuple keys retain references to decoded JSON values. |
| failure | Duplicate keys raise AssertionError; malformed JSON shape propagates. |
| cost | Linear in observed groups and key widths; native map order is not assumed. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0020

[Lines 175–182](../../../../../tests/integration/aggregate_sql_oracle.py#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected_event(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive the single affected group event by comparing complete independent snapshots. |
| inputs / outputs | Previous/following identity maps in; None or key/before/after event out. |
| invariants | One logical row replacement changes at most one group; absent group and NULL-valued output list remain distinct. |
| ownership | New envelope references oracle-owned immutable keys and value lists. |
| failure | More than one changed group fails the oracle invariant. |
| cost | Union/comparison scan over all groups; this is reference work, not a native update cost. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0022

[Lines 185–215](../../../../../tests/integration/aggregate_sql_oracle.py#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native histories to independent snapshots/events and large COUNT positions to compressed-weight SQL. |
| inputs / outputs | Case, decoded response and SQLite connection in; snapshot count, equal-output epoch count and SQL count-cell comparison count out. |
| invariants | Old weights match oracle state, every epoch advances, input changes are separate from value changes, and large COUNT output positions equal exact SQL weighted counts by full group identity. |
| ownership | Compressed reference bag owns row tuples/weights; decoded native JSON, SQL results and oracle snapshots remain caller-owned test values. |
| failure | Assertions reject the first identity/value/event/metric/count mismatch; trusted corpus requires assertions enabled. |
| cost | One full SQL/model snapshot per operation; each large observation also executes a compressed SQL count query, without expanding weights. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0024

[Lines 218–289](../../../../../tests/integration/aggregate_sql_oracle.py#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate deterministic histories spanning every admitted AVG scale and direct SQL checks of large COUNT outputs. |
| inputs / outputs | Fixed seed and numeric bounds in; 218 cases with 4,543 initial/post-update observations out. |
| invariants | 172 cases expand only small SQL bags; all 46 large-model cases expose COUNT outputs for compressed SQL verification. All scales 0..18 have positive/negative true last-place half ties; group counts never exceed INT64_MAX. |
| ownership | Returned descriptors, rows and replacements are ordinary Python test memory. |
| failure | Generation/allocation errors fail before invoking native code. |
| cost | 128 seeded small histories plus fixed numeric/group edge histories; large model weights remain compressed. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0026

[Lines 292–322](../../../../../tests/integration/aggregate_sql_oracle.py#L292); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the public driver and separately report expanded SQL statistics, compressed SQL COUNT and wide exact-model coverage. |
| inputs / outputs | Required --driver path in; terminal summary only after all 218 histories match. |
| invariants | Response counts and per-case checks must match; compressed SQL COUNT evidence never becomes a claim of SQL wide SUM/AVG or floating AVG agreement. |
| ownership | Subprocess buffers, parsed JSON and in-memory databases are ordinary Python test memory; connection is local to main and released on function/process cleanup. |
| failure | Nonzero driver status, malformed JSON or assertion mismatch aborts with a case-qualified error. |
| cost | Buffers the entire trusted corpus and output, then executes all expanded/model/count reference checks; no native timing measurement. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0027

[Lines 323–326](../../../../../tests/integration/aggregate_sql_oracle.py#L323); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the checker when invoked as the CTest script. |
| inputs / outputs | Python module name selects whether main executes. |
| invariants | Importing the module for author consistency checks does not launch a native driver. |
| ownership | No additional owner is created by the entry guard. |
| failure | main failures propagate as nonzero process termination. |
| cost | Constant dispatch before main. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |
