#!/usr/bin/env python3
"""Check the shared native SQL scalar kernel against matching DuckDB types.

This tests local scalar rules only. It does not establish nullable physical SQL
admission, bag maintenance, join NULL handling or W05 completion. Fixed-scale
DECIMAL cases stay within DuckDB's exact 38-digit domain; unconstrained mixed
scale NUMERIC needs separate full-engine coverage for the eventual W05 gate.
"""
import argparse
import datetime
from decimal import Decimal, getcontext
import itertools
import json
import subprocess

import duckdb

COMPARISONS = {"equal": "=", "not_equal": "<>", "less": "<", "less_equal": "<=",
               "greater": ">", "greater_equal": ">="}
PREDICATES = {"is_null": "IS NULL", "is_not_null": "IS NOT NULL", "is_true": "IS TRUE",
              "is_not_true": "IS NOT TRUE", "is_false": "IS FALSE", "is_not_false": "IS NOT FALSE",
              "is_unknown": "IS UNKNOWN", "is_not_unknown": "IS NOT UNKNOWN"}


def decimal_text(value):
    text = format(Decimal(value), "f")
    if "." in text:
        text = text.rstrip("0").rstrip(".")
    return "0" if Decimal(text) == 0 else text


def parameter(value):
    if isinstance(value, dict):
        return next(iter(value.values()))
    return value


def encoded(value):
    if isinstance(value, Decimal):
        return {"decimal": decimal_text(value)}
    if isinstance(value, datetime.date):
        return {"date": value.isoformat()}
    return value


def bytes_in(value):
    if isinstance(value, str):
        return len(value.encode("utf-8"))
    if isinstance(value, dict) and "decimal" in value:
        digits = decimal_text(value["decimal"]).lstrip("-").replace(".", "").lstrip("0")
        return len(digits or "0")
    return 0


def expected_work(operation, values):
    steps = 0
    if operation in ("conjunction", "disjunction"):
        stop = operation == "disjunction"
        for value in values:
            steps += 1
            if value is stop:
                break
    present_comparison = operation in COMPARISONS and all(value is not None for value in values)
    return {"structural_steps": steps, "scalar_fields": 2 if present_comparison else 0,
            "scalar_bytes": sum(map(bytes_in, values)) if present_comparison else 0,
            "pointer_slots": 0, "link_actions": 0}


def sql_expression(operation, columns):
    first = columns[0]
    if operation in COMPARISONS:
        return f"{first} {COMPARISONS[operation]} {columns[1]}"
    if operation in PREDICATES:
        return f"{first} {PREDICATES[operation]}"
    if operation == "negation":
        return f"NOT {first}"
    if operation in ("conjunction", "disjunction"):
        return (" AND " if operation == "conjunction" else " OR ").join(columns)
    if operation == "widen_integer":
        return f"CAST({first} AS BIGINT)"
    # Identity/literal casts have already been bound to their native type.
    if operation in ("identity_cast", "literal_cast"):
        return first
    raise AssertionError(f"unknown independent SQL opcode {operation}")


def corpus():
    groups = [
        ("BIGINT", [None, -(1 << 63), -(1 << 53) - 1, -1, 0, 1, (1 << 53) + 1, (1 << 63) - 1]),
        ("VARCHAR", [None, "", "a", "B", "a\x00b", "a\x00c", "alpha", "α", "中", "🙂", "x" * 256]),
        ("BOOLEAN", [None, False, True]),
        ("DATE", [None] + [{"date": value} for value in
                           ("0001-01-01", "1900-02-28", "1970-01-01", "2000-02-29", "9999-12-31")]),
    ]
    for scale in (0, 1, 2, 6, 18, 37, 38):
        maximum = "9" * 38
        if scale:
            maximum = maximum[:-scale] + "." + maximum[-scale:]
            if maximum.startswith("."):
                maximum = "0" + maximum
        unit = "1" if not scale else "0." + "0" * (scale - 1) + "1"
        groups.append((f"DECIMAL(38,{scale})", [None] + [{"decimal": value} for value in
                                                     ("0", maximum, "-" + maximum, unit, "-" + unit)]))
    for kind, values in groups:
        for operation in COMPARISONS:
            for pair in itertools.product(values, repeat=2):
                yield kind, operation, list(pair)
        for value in values:
            for operation in ("identity_cast", "literal_cast", "is_null", "is_not_null"):
                yield kind, operation, [value]
    for length in range(1, 5):
        for values in itertools.product((None, False, True), repeat=length):
            for operation in ("conjunction", "disjunction"):
                yield "BOOLEAN", operation, list(values)
    for value in (None, False, True):
        for operation in ("negation", "is_true", "is_not_true", "is_false", "is_not_false", "is_unknown", "is_not_unknown"):
            yield "BOOLEAN", operation, [value]
    for value in (None, -(1 << 31), -1, 0, 1, (1 << 31) - 1):
        yield "INTEGER", "widen_integer", [value]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--driver", required=True)
    args = parser.parse_args()
    getcontext().prec = 200
    cases = list(corpus())
    requests = [{"id": index, "operation": operation, "values": values}
                for index, (_, operation, values) in enumerate(cases)]
    child = subprocess.run([args.driver], input="".join(json.dumps(case, ensure_ascii=False) + "\n" for case in requests),
                           encoding="utf-8", capture_output=True, check=False)
    assert child.returncode == 0, (child.returncode, child.stderr[-4000:])
    observations = [json.loads(line) for line in child.stdout.splitlines()]
    assert len(observations) == len(cases)
    with duckdb.connect(":memory:") as connection:
        assert connection.execute("SELECT current_setting('default_collation')").fetchone()[0] == "", "requires default binary collation"
        for index, ((kind, operation, values), actual) in enumerate(zip(cases, observations)):
            names = [f"CAST(? AS {kind})" for _ in values]
            query = "SELECT " + sql_expression(operation, names)
            expected = encoded(connection.execute(query, list(map(parameter, values))).fetchone()[0])
            context = (index, kind, operation, values, actual, expected)
            assert actual["id"] == index and type(actual["value"]) is type(expected) and actual["value"] == expected, context
            assert actual["allocations"] == 0 and actual["work"] == expected_work(operation, values), context
    print(f"W05 shared SQL scalar: DuckDB Python {duckdb.__version__}, {len(cases)} matching-type cases; "
          "all Boolean truth tables, nullable comparisons, binary UTF-8/NUL strings, signed integer boundaries, "
          "finite dates and fixed DECIMAL(38,s) passed with zero-heap native evaluation and exact selected work. "
          "This primitive gate does not complete W05 or generic mixed-scale NUMERIC coverage.")
    print(child.stderr.strip())


if __name__ == "__main__":
    main()
