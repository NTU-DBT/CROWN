#!/usr/bin/env python3
"""W04 SQL sufficient-statistic oracle and separately labelled exact bag model.

SQLite supplies GROUP BY, COUNT and integer SUM for small expanded bags. Its
floating AVG is deliberately unused: the declared NUMERIC(38,s) result is
rounded from SQL SUM/COUNT using Fraction. Compressed large-bag COUNT outputs
also use SQLite weighted-sum identities. Wide SUM/AVG remain independent Python
integer/Fraction checks, distinct from that SQL COUNT evidence.
"""
import argparse
from fractions import Fraction
import json
import random
import sqlite3
import subprocess

SEED = 0xA6640C04
MAXIMUM = (1 << 63) - 1
COLUMNS = {"g": 0, "x": 1, "flag": 2}


def numeric(value, scale=0):
    """Round a rational to a canonical decimal, with exact half ties away."""
    value = Fraction(value)
    coefficient = (2 * abs(value.numerator) * 10**scale + value.denominator) // (2 * value.denominator)
    digits = str(coefficient)
    if scale:
        digits = digits.rjust(scale + 1, "0")
        digits = (digits[:-scale] + "." + digits[-scale:]).rstrip("0").rstrip(".")
    if value < 0 and coefficient:
        digits = "-" + digits
    return {"decimal": digits}


def change(values, before, after):
    return {"values": list(values), "before": before, "after": after}


def make_case(name, outputs, groups=(), updates=(), scale=18, source=True, model=False):
    selections = [arg if kind == "group" else "COUNT(*)" if kind == "all" else
                  f"{kind.upper()}({arg})" for kind, arg in outputs]
    sql = "SELECT " + ",".join(selections)
    if source:
        sql += " FROM r"
    if groups:
        sql += " GROUP BY " + ",".join(groups)
    return {"request": {"id": name, "sql": sql, "average_scale": scale, "updates": list(updates)},
            "outputs": outputs, "groups": tuple(groups), "source": source, "model": model}


def decimal_sum(argument):
    # The test schema declares x bigint; uncast small integer constants are int32.
    return argument == "x" or "BIGINT" in argument


def argument_value(argument, row):
    if argument in COLUMNS:
        return row[COLUMNS[argument]]
    if argument == "NULL" or argument.startswith("CAST(NULL"):
        return None
    if argument.startswith("CAST(1"):
        return 1
    if argument.startswith("'"):
        return argument[1:-1]
    return int(argument)


def sql_snapshot(connection, case, state):
    """Obtain hidden group identity plus each SQL count/sum in one query."""
    connection.execute("DELETE FROM r")
    connection.executemany("INSERT INTO r VALUES (?,?,?)",
                           (row for row, weight in state.items() for _ in range(weight)))
    selections = list(case["groups"])
    for kind, argument in case["outputs"]:
        if kind == "avg":
            selections.extend((f"SUM({argument})", f"COUNT({argument})"))
        else:
            selections.append(argument if kind == "group" else "COUNT(*)" if kind == "all" else
                              f"{kind.upper()}({argument})")
    query = "SELECT " + ",".join(selections)
    if case["source"]:
        query += " FROM r"
    if case["groups"]:
        query += " GROUP BY " + ",".join(case["groups"])
    result = {}
    for record in connection.execute(query):
        key = tuple(bool(record[i]) if name == "flag" else record[i]
                    for i, name in enumerate(case["groups"]))
        position, values = len(key), []
        for kind, argument in case["outputs"]:
            value = record[position]
            position += 1
            if kind == "avg":
                count = record[position]
                position += 1
                value = numeric(Fraction(value, count), case["request"]["average_scale"]) if count else None
            elif kind == "sum" and value is not None and decimal_sum(argument):
                value = numeric(value)
            elif kind == "group" and argument == "flag":
                value = bool(value)
            values.append(value)
        result[key] = values
    return result


def sql_count_check(connection, case, state, observed):
    """Compare large native COUNT positions to compressed-weight SQL identities."""
    positions = [(index, argument if kind == "count" else None)
                 for index, (kind, argument) in enumerate(case["outputs"]) if kind in ("all", "count")]
    connection.execute("DELETE FROM weighted_r")
    connection.executemany("INSERT INTO weighted_r VALUES (?,?,?,?)",
                           ((*row, weight) for row, weight in state.items()))
    selections = list(case["groups"])
    for _, argument in positions:
        term = "weight" if argument is None else f"CASE WHEN {argument} IS NOT NULL THEN weight ELSE 0 END"
        selections.append(f"COALESCE(SUM({term}),0)")
    query = "SELECT " + ",".join(selections) + " FROM weighted_r"
    if case["groups"]:
        query += " GROUP BY " + ",".join(case["groups"])
    expected = {}
    for record in connection.execute(query):
        key = tuple(bool(record[index]) if name == "flag" else record[index]
                    for index, name in enumerate(case["groups"]))
        expected[key] = list(record[len(key):])
    actual = {key: [values[index] for index, _ in positions] for key, values in observed.items()}
    assert all(type(value) is int and 0 <= value <= MAXIMUM for values in actual.values() for value in values)
    assert actual == expected, "compressed-weight SQL COUNT identity"
    return sum(len(values) for values in expected.values())


def model_snapshot(case, state):
    """Exact large-weight reference: no expanded rows, native limbs or floats."""
    grouped = {}
    for row, weight in state.items():
        key = tuple(row[COLUMNS[name]] for name in case["groups"])
        grouped.setdefault(key, []).append((row, weight))
    if not case["groups"]:
        grouped.setdefault((), [])
    if not case["source"]:
        grouped = {(): [((None, None, False), 1)]}
    result = {}
    for key, rows in grouped.items():
        values = []
        for kind, argument in case["outputs"]:
            if kind == "group":
                value = key[case["groups"].index(argument)]
            elif kind == "all":
                value = sum(weight for _, weight in rows)
            else:
                nonnull = [(argument_value(argument, row), weight) for row, weight in rows
                           if argument_value(argument, row) is not None]
                count = sum(weight for _, weight in nonnull)
                if kind == "count":
                    value = count
                else:
                    total = sum(scalar * weight for scalar, weight in nonnull)
                    value = None if not count else (numeric(Fraction(total, count), case["request"]["average_scale"])
                                                    if kind == "avg" else numeric(total)
                                                    if decimal_sum(argument) else total)
            values.append(value)
        result[key] = values
    return result


def observed_groups(snapshot):
    result = {}
    for group in snapshot["groups"]:
        key = tuple(group["key"])
        if key in result:
            raise AssertionError(f"duplicate observed group identity {key}")
        result[key] = group["values"]
    return result


def expected_event(previous, following):
    changed = [key for key in previous.keys() | following.keys() if previous.get(key) != following.get(key)]
    if len(changed) > 1:
        raise AssertionError("one row replacement unexpectedly changed two reference groups")
    if not changed:
        return None
    key = changed[0]
    return {"key": list(key), "before": previous.get(key), "after": following.get(key)}


def verify(case, response, connection):
    state = {}
    oracle = model_snapshot if case["model"] else lambda spec, bag: sql_snapshot(connection, spec, bag)
    previous = oracle(case, state)
    updates = case["request"]["updates"]
    assert response["id"] == case["request"]["id"]
    assert len(response["trace"]) == len(updates) + 1 and len(response["epochs"]) == len(updates)
    assert response["trace"][0]["sequence"] == 0 and observed_groups(response["trace"][0]) == previous, "initial snapshot"
    count_checks = sql_count_check(connection, case, state, observed_groups(response["trace"][0])) if case["model"] else 0
    unchanged = 0
    for sequence, (operation, observed, epoch) in enumerate(zip(updates, response["trace"][1:], response["epochs"]), 1):
        row = tuple(operation["values"])
        assert state.get(row, 0) == operation["before"], "oracle generator prior weight"
        if operation["after"]:
            state[row] = operation["after"]
        else:
            state.pop(row, None)
        following = oracle(case, state)
        assert observed["sequence"] == sequence and observed_groups(observed) == following, f"snapshot epoch {sequence}"
        if case["model"]:
            count_checks += sql_count_check(connection, case, state, observed_groups(observed))
        event = expected_event(previous, following)
        assert epoch["sequence"] == sequence and epoch["captured"] is True, f"event envelope epoch {sequence}"
        changed = operation["before"] != operation["after"]
        assert epoch["changed"] == changed and epoch["output"] == event, f"event values epoch {sequence}"
        assert epoch["metrics"]["input_fields"] == 3 and epoch["metrics"]["row_probes"] == 1
        if not changed:
            assert epoch["metrics"]["group_probes"] == 0 and epoch["metrics"]["output_fields"] == 0
        unchanged += changed and event is None
        previous = following
    return len(updates) + 1, unchanged, count_checks


def cases():
    result = []
    standard = [("all", ""), ("count", "x"), ("sum", "x"), ("avg", "x"),
                ("count", "g"), ("count", "flag"), ("count", "NULL")]
    changes = [change((None, None, False), 0, 2), change((None, -7, True), 0, 3),
               change(("a", 9, False), 0, 2), change(("a", -9, True), 0, 2),
               change(("a", None, True), 0, 1), change(("a", 9, False), 2, 0),
               change(("a", -9, True), 2, 0), change(("a", None, True), 1, 0),
               change((None, -7, True), 3, 0), change((None, None, False), 2, 0)]
    result.append(make_case("global_null_signed_last_delete", standard, updates=changes))
    result.append(make_case("grouped_null_signed_last_delete", [("group", "g")] + standard, ("g",), changes))
    result.append(make_case("hidden_group_identity", [("count", "x")], ("g",),
                            [change(("a", None, False), 0, 1), change(("b", None, False), 0, 1),
                             change(("a", None, False), 1, 0), change(("b", None, False), 1, 0)]))
    result.append(make_case("rounded_output_unchanged", [("avg", "x")], updates=
                            [change(("a", 0, False), 0, 2), change(("b", 1, False), 0, 1),
                             change(("b", 1, False), 1, 0), change(("a", 0, False), 2, 2),
                             change(("a", 0, False), 2, 0)], scale=0))
    for scale in range(19):
        for sign in (-1, 1):
            result.append(make_case(f"half_value_{scale}_{sign}", [("avg", "x")], updates=
                                    [change(("a", 0, False), 0, 1), change(("b", sign, True), 0, 1)], scale=scale))
    constants = [("all", ""), ("count", "NULL"), ("count", "'literal'"), ("sum", "1"),
                 ("avg", "1"), ("sum", "CAST(1 AS BIGINT)"),
                 ("sum", "CAST(NULL AS BIGINT)"), ("avg", "CAST(NULL AS INTEGER)")]
    result.append(make_case("no_from_implicit_singleton", constants, source=False))
    result.append(make_case("constant_named_empty_and_live", constants, updates=changes))
    generator = random.Random(SEED)
    for index in range(128):
        groups = generator.choice([(), ("g",), ("g", "flag"), ("x",), ("g", "x", "flag")])
        outputs = [("group", name) for name in reversed(groups)] + generator.choice(
            [standard, [("avg", "x")], [("sum", "x"), ("count", "NULL")], constants])
        pool = list(dict.fromkeys((generator.choice([None, "", "alpha", "beta", "β", "中"]),
                                  generator.choice([None, -1000, -2, -1, 0, 1, 2, 1000]),
                                  bool(generator.randrange(2))) for _ in range(12)))
        bag, updates = {}, []
        for _ in range(24):
            row = generator.choice(pool)
            before, after = bag.get(row, 0), generator.randrange(5)
            updates.append(change(row, before, after))
            if after:
                bag[row] = after
            else:
                bag.pop(row, None)
        for row, before in sorted(bag.items(), key=lambda item: repr(item[0])):
            updates.append(change(row, before, 0))
        result.append(make_case(f"sqlite_seed_{index}", outputs, groups, updates,
                                generator.randrange(19)))
    large = [("all", ""), ("count", "x"), ("sum", "x"), ("avg", "x")]
    for value in (MAXIMUM, -MAXIMUM - 1, 1, -1, 0):
        updates = [change(("large", value, False), 0, MAXIMUM),
                   change(("large", value, False), MAXIMUM, (1 << 53) + 1),
                   change(("large", value, False), (1 << 53) + 1, 0)]
        result.append(make_case(f"exact_extreme_{value}", large, updates=updates, model=True))
    for scale in range(19):
        for sign in (-1, 1):
            denominator = 2 * 10**scale
            result.append(make_case(f"exact_rounding_tie_{scale}_{sign}", [("all", ""), ("count", "x"), ("avg", "x")], updates=
                                    [change(("zero", 0, False), 0, denominator - 1),
                                     change(("unit", sign, True), 0, 1)], scale=scale, model=True))
    mixed = [change(("a", MAXIMUM, False), 0, MAXIMUM - 2),
             change(("b", -MAXIMUM - 1, True), 0, 2),
             change(("a", MAXIMUM, False), MAXIMUM - 2, 1),
             change(("b", -MAXIMUM - 1, True), 2, 0), change(("a", MAXIMUM, False), 1, 0)]
    result.append(make_case("exact_large_mixed_signs", large, updates=mixed, model=True))
    result.append(make_case("exact_group_count_bound_not_global", [("group", "g")] + large, ("g",),
                            [change(("a", 1, False), 0, MAXIMUM), change(("b", -1, True), 0, MAXIMUM),
                             change(("a", 1, False), MAXIMUM, 0), change(("b", -1, True), MAXIMUM, 0)], model=True))
    result.append(make_case("exact_null_nonnull_separate_counts", large, updates=
                            [change(("n", None, False), 0, MAXIMUM - 1), change(("v", -7, True), 0, 1),
                             change(("n", None, False), MAXIMUM - 1, 0), change(("v", -7, True), 1, 0)], model=True))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--driver", required=True)
    args = parser.parse_args()
    specifications = cases()
    payload = "".join(json.dumps(case["request"], ensure_ascii=False) + "\n" for case in specifications)
    child = subprocess.run([args.driver], input=payload, text=True, encoding="utf-8", capture_output=True, check=False)
    if child.returncode:
        raise AssertionError(f"native driver exited {child.returncode}: {child.stderr[-4000:]}")
    responses = [json.loads(line) for line in child.stdout.splitlines()]
    assert len(responses) == len(specifications), "driver response count"
    observations = {False: 0, True: 0}
    unchanged = sql_count_checks = 0
    with sqlite3.connect(":memory:") as connection:
        connection.execute("CREATE TABLE r(g TEXT,x INTEGER,flag INTEGER NOT NULL)")
        connection.execute("CREATE TABLE weighted_r(g TEXT,x INTEGER,flag INTEGER NOT NULL,weight INTEGER NOT NULL)")
        for case, response in zip(specifications, responses):
            try:
                count, equal_output, count_checks = verify(case, response, connection)
            except AssertionError as error:
                raise AssertionError(f"{case['request']['id']}: {error}") from error
            observations[case["model"]] += count
            unchanged += equal_output
            sql_count_checks += count_checks
    sql_cases = sum(not case["model"] for case in specifications)
    print(f"W04 aggregate oracle: SQLite {sqlite3.sqlite_version}, seed {SEED}; "
          f"{sql_cases} expanded SQL-statistic cases/{observations[False]} snapshots; "
          f"{len(specifications)-sql_cases} compressed-weight SQL COUNT cases/{observations[True]} snapshots/"
          f"{sql_count_checks} scalar checks; same large-bag SUM/AVG use the exact Python model; "
          f"{unchanged} changed-input epochs correctly emitted no value event. "
          "AVG scales 0..18 use exact Fraction rounding of SQL or model SUM/COUNT; SQLite floating AVG is unused.")


if __name__ == "__main__":
    main()
