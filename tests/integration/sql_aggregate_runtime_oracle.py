#!/usr/bin/env python3
"""SQL recomputation of genuine composed physical NetBatch epochs.

SQL executes joins/predicates/grouping/COUNT/SUM over bounded expanded physical
bags. Fixed-scale AVG alone uses SQL SUM/COUNT and W04's exact Fraction rounding.
No native descriptor/logical fact enters the runtime. Required DuckDB or explicit
private PostgreSQL never falls back and is not installed by this script.
"""
import argparse
from collections import Counter
import csv
import datetime
from decimal import Decimal
from fractions import Fraction
from io import StringIO
import json
import hashlib
import random
import re
import struct
import subprocess

import aggregate_sql_oracle as arithmetic
import sql_rows_oracle as rows

SEED = 0xA6600601
MAX_WEIGHT = 8
MAX_SOURCE_COPIES = 24
REFERENCE = re.compile(r"(?:(?:r|t|a|b)\.)?(id|g|x|flag)\Z")
COLUMN_KIND = {"id": 2, "g": 3, "x": 2, "flag": 4}
# Explicit fixture spellings, independent of the native cast/compiler metadata.
# Keep the raw origin for logical change detection and the final SQL width for
# result typing; the mature SQL engine executes the cast itself.
CAST_ARGUMENTS = {
    "r.x::integer": ("r.x", 1), "CAST(r.x AS INTEGER)": ("r.x", 1),
    "(r.x::integer)::bigint": ("r.x", 2),
    "b.x::integer": ("b.x", 1), "(b.x::integer)::bigint": ("b.x", 2),
    "a.x::integer": ("a.x", 1),
}


def catalog():
    columns = [rows.column("id", "int64"), rows.column("g", "string"),
               rows.column("x", "int64"), rows.column("flag", "boolean")]
    return {"version": 1, "tables": [{"name": name, "columns": columns} for name in ("r", "t")]}


def edit(table, values, before, after):
    return {"table": table, "values": list(values), "before": before, "after": after}


def batch(*edits):
    return {"edits": list(edits)}


def expression(kind, argument):
    return argument if kind == "group" else "COUNT(*)" if kind == "all" else f"{kind.upper()}({argument})"


def sql(case, reference=False):
    selected = list(case["groups"]) if reference else []
    for index, (kind, argument) in enumerate(case["outputs"]):
        if reference and kind == "avg":
            selected.extend((f"SUM({argument})", f"COUNT({argument})"))
        else:
            value = expression(kind, argument)
            alias = case.get("aliases", {}).get(index)
            selected.append(value + f" AS {alias}" if alias and not reference else value)
    if reference:
        selected = [f"{value} AS q{index}" for index, value in enumerate(selected)]
    result = "SELECT " + ",".join(selected) + case["tail"]
    if case["groups"]:
        result += " GROUP BY " + ",".join(case["groups"])
    return result


def logical_references(case):
    # Fixture original columns, independently of native descriptors. Different
    # origins are never merged by equal values. Duplicate spellings are harmless.
    result = []
    for value in [*case["groups"], *(arg for _, arg in case["outputs"] if arg is not None)]:
        value = CAST_ARGUMENTS.get(value, (value, None))[0]
        if REFERENCE.fullmatch(value) and value not in result:
            result.append(value)
    return result


def logical_sql(case):
    # Constant1 represents the nullary row only for the cold SQL Counter.
    return "SELECT " + ",".join(logical_references(case) or ["1"]) + case["tail"]


def argument_kind(argument):
    if argument in CAST_ARGUMENTS:
        return CAST_ARGUMENTS[argument][1]
    matched = REFERENCE.fullmatch(argument)
    if matched:
        return COLUMN_KIND[matched[1]]
    return {"1": 1, "2147483647": 1, "1::bigint": 2, "NULL::bigint": 2,
            "NULL": 0, "'literal'": 3}[argument]


def scalar_type(kind, nullable=True, scale=None):
    return {"kind": kind, "nullable": nullable, "decimal": [38, scale] if scale is not None else None}


def expected_metadata(case):
    types, names = [], []
    for index, (kind, argument) in enumerate(case["outputs"]):
        if kind == "group":
            types.append(scalar_type(argument_kind(argument)))
        elif kind in ("all", "count"):
            types.append(scalar_type(2, False))
        elif kind == "sum":
            types.append(scalar_type(2) if argument_kind(argument) == 1 else scalar_type(6, scale=0))
        else:
            assert kind == "avg"
            types.append(scalar_type(6, scale=case["average_scale"]))
        names.append(case.get("aliases", {}).get(index, argument.split(".")[-1] if kind == "group" else
                                                  "count" if kind == "all" else kind))
    return types, [scalar_type(argument_kind(value)) for value in case["groups"]], names


def make_case(name, outputs, tail, groups=(), batches=(), scale=18, **options):
    result = {"id": name, "catalog": catalog(), "outputs": list(outputs), "tail": tail,
              "groups": list(groups), "batches": list(batches), "average_scale": scale, **options}
    result["sql"] = sql(result)
    return result


def fixed_cases():
    a, b, null = [1, "a", 6, True], [2, None, None, True], [None, "ignored", 9, True]
    hidden = [3, "filtered", 7, False]
    t1, t2, tn = [1, "right", 3, None], [2, "right", None, True], [None, None, 99, True]
    moved = [1, "b", 6, True]
    outputs = [("group", "a.g"), ("all", None), ("count", "b.x"), ("sum", "b.x"),
               ("avg", "b.x"), ("sum", "1"), ("count", "'literal'")]
    yield make_case("joined_separator_hidden", outputs,
                    " FROM r a JOIN t b ON a.id=b.id WHERE a.flag", ("a.id", "a.g"), [
                        batch(edit(1, t1, 0, 3), edit(0, a, 0, 2), edit(1, t2, 0, 2), edit(0, b, 0, 1),
                              edit(0, null, 0, 2), edit(1, tn, 0, 1), edit(0, hidden, 0, 3)),
                        batch(edit(0, moved, 0, 2), edit(0, a, 2, 0), edit(1, t2, 2, 0)),
                        batch(edit(0, hidden, 3, 1)), batch(),
                        batch(edit(0, moved, 2, 0), edit(1, t1, 3, 0))], aliases={0: "label", 3: "total_sum"})
    left, right, duplicate = [7, "a", 6, True], [7, "b", None, True], [7, "a", 6, False]
    yield make_case("self_join_cross_terms", [("all", None), ("count", "a.x"), ("sum", "a.x"), ("avg", "a.x")],
                    " FROM r a JOIN r b ON a.id=b.id", ("a.g",), [
                        batch(edit(0, left, 0, 2), edit(0, right, 0, 3)), batch(edit(0, duplicate, 0, 1)),
                        batch(edit(0, right, 3, 2), edit(0, left, 2, 3)),
                        batch(edit(0, left, 3, 0), edit(0, duplicate, 1, 0), edit(0, right, 2, 0)), batch()])
    same, different, both_null = [1, "a", 1, True], [1, "a", 2, None], [None, None, None, None]
    yield make_case("where_equal_both_origins", [("group", "r.id"), ("group", "r.x"), ("all", None)],
                    " FROM r WHERE r.x=r.id", ("r.id", "r.x"), [
                        batch(edit(0, same, 0, 2), edit(0, different, 0, 3), edit(0, both_null, 0, 2)),
                        batch(edit(0, same, 2, 0)), batch(edit(0, different, 3, 1))])
    yield make_case("shared_null_constants", [("all", None), ("count", "r.x"), ("sum", "r.x"), ("avg", "r.x")],
                    " FROM r WHERE r.x IS NULL AND r.id IS NULL", ("r.id", "r.x"), [
                        batch(edit(0, both_null, 0, 2), edit(0, same, 0, 3)), batch(edit(0, both_null, 2, 0)), batch()])
    yield make_case("self_join_equal_origins", [("group", "a.x"), ("group", "b.x"), ("all", None)],
                    " FROM r a JOIN r b ON a.x=b.x", ("a.x", "b.x"), [
                        batch(edit(0, same, 0, 2), edit(0, different, 0, 1), edit(0, both_null, 0, 3)),
                        batch(edit(0, same, 2, 1)), batch(edit(0, different, 1, 0))])
    yield make_case("qualified_same_origin", [("group", "x"), ("count", "r.x"), ("sum", "x"), ("avg", "r.x")],
                    " FROM r", ("r.x",), [batch(edit(0, same, 0, 2), edit(0, both_null, 0, 1)),
                                          batch(edit(0, same, 2, 0), edit(0, both_null, 1, 0))])
    positive, negative, zero = [1, "g", 1, True], [2, "g", -1, True], [3, "g", 0, None]
    global_outputs = [("all", None), ("count", "r.x"), ("sum", "r.x"), ("avg", "r.x")]
    global_batches = [batch(edit(0, positive, 0, 2), edit(0, negative, 0, 2), edit(0, both_null, 0, 1)),
                      batch(edit(0, positive, 2, 1), edit(0, negative, 2, 0)), batch(edit(0, zero, 0, 1)),
                      batch(edit(0, positive, 1, 0), edit(0, zero, 1, 0), edit(0, both_null, 1, 0)), batch()]
    yield make_case("global_empty_null_cancel", global_outputs, " FROM r", batches=global_batches)
    yield make_case("global_nullable_filter", global_outputs, " FROM r WHERE r.flag", batches=global_batches)
    yield make_case("rounded_avg_only_diff", [("avg", "r.x")], " FROM r", batches=[
                        batch(edit(0, zero, 0, 3)), batch(edit(0, positive, 0, 1)),
                        batch(edit(0, zero, 3, 1)),
                        batch(edit(0, negative, 0, 1), edit(0, positive, 1, 0)),
                        batch(edit(0, zero, 1, 0), edit(0, negative, 1, 0)), batch()], scale=0)
    yield make_case("boolean_group", [("group", "r.flag"), ("all", None), ("avg", "r.x")], " FROM r", ("r.flag",), global_batches)
    yield make_case("nullary_join_count", [("all", None), ("sum", "1"), ("avg", "1")],
                    " FROM r a JOIN t b ON a.id=b.id", batches=[
                        batch(edit(0, a, 0, 2), edit(1, t1, 0, 3)), batch(edit(1, t1, 3, 0)), batch(edit(0, a, 2, 0)), batch()])
    key_a, key_b, key_a_replacement = [1, "a", 1, True], [2, "b", 1, True], [3, "a", 100, None]
    yield make_case("equal_outputs_full_hidden_keys", [("all", None)], " FROM r", ("r.g",), [
                        batch(edit(0, key_a, 0, 2), edit(0, key_b, 0, 2)),
                        batch(edit(0, key_a_replacement, 0, 2), edit(0, key_a, 2, 0)),
                        batch(edit(1, t1, 0, 3)),
                        batch(edit(0, key_a_replacement, 2, 0), edit(0, key_b, 2, 0)), batch()])
    old, new = [1, "same", 9, True], [2, "same", -9, False]
    yield make_case("final_only_small_native_cap", [("group", "r.g"), ("all", None), ("sum", "1")], " FROM r", ("r.g",), [
                        batch(edit(0, old, 0, 2)), batch(edit(0, new, 0, 3), edit(0, old, 2, 0)),
                        batch(edit(0, old, 0, 8), edit(0, old, 8, 1), edit(0, new, 3, 2)),
                        batch(edit(0, old, 1, 0), edit(0, new, 2, 0))], multiplicity_limit=3, count_limit=3)
    constants = [("all", None), ("count", "NULL"), ("sum", "1"), ("sum", "1::bigint"), ("avg", "1"), ("sum", "NULL::bigint")]
    for suffix, tail in (("true", ""), ("false", " WHERE FALSE")):
        yield make_case("static_source_" + suffix, constants, tail,
                        batches=[batch(), batch(edit(0, a, 0, 2)), batch(edit(0, a, 2, 0)), batch()])
    yield make_case("predicate_parameter", global_outputs, " FROM r WHERE r.x>$1", batches=global_batches,
                    parameter_columns=[rows.column("minimum", "int64")], parameters=[0])


def integer_cases():
    minimum, maximum = [1, "edge", -(2**31), True], [2, "edge", 2**31-1, True]
    null, hidden = [3, None, None, True], [4, "hidden", 2**31, False]
    commands = [batch(edit(0, minimum, 0, 2), edit(0, maximum, 0, 2), edit(0, null, 0, 3), edit(0, hidden, 0, 1)),
                batch(edit(0, maximum, 2, 1)), batch(edit(0, minimum, 2, 0)),
                batch(edit(0, maximum, 1, 0), edit(0, null, 3, 0), edit(0, hidden, 1, 0)), batch()]
    outputs = [("all", None), ("count", "(r.x::integer)::bigint"), ("sum", "r.x::integer"),
               ("sum", "r.x"), ("sum", "(r.x::integer)::bigint"), ("avg", "CAST(r.x AS INTEGER)")]
    yield make_case("integer_mixed_global", outputs, " FROM r WHERE r.flag", batches=commands)
    yield make_case("integer_raw_group", [("group", "r.x"), *outputs],
                    " FROM r WHERE r.flag", ("r.x",), commands)
    yield make_case("integer_nested_count", [("count", "(r.x::integer)::bigint")],
                    " FROM r WHERE r.flag", batches=commands)
    left, right = [1, "join", 7, True], [1, "right", -7, True]
    yield make_case("integer_join", [("count", "(b.x::integer)::bigint"), ("sum", "b.x::integer"),
                                     ("sum", "b.x"), ("avg", "b.x::integer")],
                    " FROM r a JOIN t b ON a.id=b.id", ("a.id", "a.g"), [
                        batch(edit(0, left, 0, 2), edit(1, right, 0, 3)),
                        batch(edit(1, right, 3, 1)), batch(edit(0, left, 2, 0))])
    yield make_case("integer_self_join", [("sum", "a.x::integer"), ("avg", "a.x::integer")],
                    " FROM r a JOIN r b ON a.id=b.id", batches=[
                        batch(edit(0, left, 0, 2), edit(0, right, 0, 3)),
                        batch(edit(0, right, 3, 0)), batch(edit(0, left, 2, 0))])


def scale_cases():
    positive_zero, positive_one = [1, "positive", 0, True], [2, "positive", 1, True]
    negative_zero, negative_one = [3, "negative", 0, False], [4, "negative", -1, False]
    null = [5, None, None, None]
    commands = [batch(edit(0, positive_zero, 0, 1), edit(0, positive_one, 0, 1), edit(0, negative_zero, 0, 1),
                      edit(0, negative_one, 0, 1), edit(0, null, 0, 2)),
                batch(edit(0, positive_zero, 1, 2), edit(0, negative_zero, 1, 2)),
                batch(edit(0, positive_zero, 2, 1), edit(0, positive_one, 1, 2),
                      edit(0, negative_zero, 2, 1), edit(0, negative_one, 1, 2)),
                batch(edit(0, positive_one, 2, 0), edit(0, negative_one, 2, 0)),
                batch(edit(0, positive_zero, 1, 0), edit(0, negative_zero, 1, 0), edit(0, null, 2, 0)), batch()]
    for scale in range(19):
        yield make_case(f"average_scale_{scale}", [("group", "r.g"), ("sum", "r.x"), ("avg", "r.x"), ("count", "r.x")],
                        " FROM r", ("r.g",), commands, scale)
        yield make_case(f"integer_average_scale_{scale}", [("group", "r.g"), ("sum", "r.x::integer"),
                        ("avg", "r.x::integer"), ("count", "r.x::integer")],
                        " FROM r", ("r.g",), commands, scale)


def random_cases():
    rng = random.Random(SEED)
    pool = [[None, None, None, None], [1, "a", 1, True], [1, "a", -1, False],
            [2, "quote's", 3, True], [2, "λ", 0, None], [3, "", -3, True]]
    for number in range(64):
        state, commands = [{}, {}], []
        for ordinal in range(24):
            edits = []
            for _ in range(0 if ordinal % 7 == 0 else rng.randrange(1, 4)):
                table = rng.randrange(2); value = rng.choice(pool); identity = rows.key(value)
                before = state[table].get(identity, 0); after = rng.randrange(4)
                edits.append(edit(table, value, before, after)); state[table][identity] = after
            commands.append(batch(*edits))
        if number % 3 == 0:
            outputs, tail, groups = [("group", "a.g"), ("all", None), ("sum", "b.x"), ("avg", "b.x")], \
                " FROM r a JOIN t b ON a.id=b.id WHERE a.flag", ("a.id", "a.g")
        elif number % 3 == 1:
            outputs, tail, groups = [("all", None), ("count", "a.x"), ("sum", "a.x"), ("avg", "a.x")], \
                " FROM r a JOIN r b ON a.id=b.id", ("a.g",)
        else:
            outputs, tail, groups = [("all", None), ("count", "r.x"), ("sum", "r.x"), ("avg", "r.x")], \
                " FROM r WHERE r.flag", ()
        yield make_case(f"seeded_{number}", outputs, tail, groups, commands, number % 19)


def states(case):
    state = [{} for _ in case["catalog"]["tables"]]
    yield 0, [[] for _ in state], False
    for sequence, command in enumerate(case["batches"], 1):
        before = [dict(source) for source in state]
        for change in command["edits"]:
            table, value = change["table"], change["values"]
            assert len(value) == len(case["catalog"]["tables"][table]["columns"])
            assert type(change["before"]) is int and type(change["after"]) is int
            assert 0 <= change["before"] <= MAX_WEIGHT and 0 <= change["after"] <= MAX_WEIGHT
            identity = rows.key(value)
            assert state[table].get(identity, (value, 0))[1] == change["before"]
            if change["after"]:
                state[table][identity] = (value, change["after"])
            else:
                state[table].pop(identity, None)
        assert all(sum(weight for _, weight in source.values()) <= MAX_SOURCE_COPIES for source in state), case["id"]
        expanded = [[value for value, weight in source.values() for _ in range(weight)] for source in state]
        yield sequence, expanded, state != before


def integer(value):
    assert value is not None and type(value) in (int, str, Decimal), ("nonexact SQL integer", value)
    exact = Decimal(str(value)); result = int(exact)
    assert exact == result
    return result


def scalar(value, kind, postgres):
    return rows.pg_value(value, kind) if postgres else rows.canonical(value)


def decode_groups(case, records, postgres):
    result = {}
    for record in records:
        arity = len(case["groups"]) + sum(2 if kind == "avg" else 1 for kind, _ in case["outputs"])
        assert len(record) == arity
        key = [scalar(value, argument_kind(ref), postgres) for value, ref in zip(record, case["groups"])]
        position, values = len(key), []
        for kind, argument in case["outputs"]:
            value = record[position]; position += 1
            if kind == "avg":
                count = integer(record[position]); position += 1
                assert count >= 0 and (value is None) == (count == 0)
                value = arithmetic.numeric(Fraction(integer(value), count), case["average_scale"]) if count else None
            elif kind == "sum":
                value = None if value is None else integer(value) if argument_kind(argument) == 1 else arithmetic.numeric(integer(value))
            elif kind in ("all", "count"):
                value = integer(value); assert value >= 0
            else:
                assert kind == "group"
                value = scalar(value, argument_kind(argument), postgres)
            values.append(value)
        identity = rows.key(key); assert identity not in result, "SQL group identity duplicated"
        result[identity] = {"key": key, "values": values}
    return result


def reference_snapshot(case, sequence, expanded, physical_changed, group_records, logical_records, postgres):
    kinds = [argument_kind(value) for value in logical_references(case)] or [2]
    logical = Counter()
    for record in logical_records:
        assert len(record) == len(kinds)
        logical[rows.key([scalar(value, kind, postgres) for value, kind in zip(record, kinds)])] += 1
    return {"sequence": sequence, "groups": decode_groups(case, group_records, postgres),
            "logical": logical, "changed": physical_changed, "source_copies": [len(source) for source in expanded]}


def duckdb_reference(case):
    import duckdb  # Required; no skip/install/fallback.
    connection = duckdb.connect(":memory:")
    try:
        assert connection.execute("SELECT current_setting('default_collation')").fetchone() == ("",)
        for statement in rows.ddl(case, "duckdb"):
            connection.execute(statement)
        trace = []
        for sequence, expanded, physical_changed in states(case):
            for table, values in zip(case["catalog"]["tables"], expanded):
                connection.execute(f"DELETE FROM {table['name']}")
                if values:
                    marks = ",".join("?" for _ in table["columns"])
                    connection.executemany(f"INSERT INTO {table['name']} VALUES ({marks})",
                                           [[rows.parameter(value) for value in record] for record in values])
            parameters = [rows.parameter(value) for value in case.get("parameters", [])]
            query = connection.execute(sql(case, True), parameters)
            group_records = query.fetchall()
            arity = len(case["groups"]) + sum(2 if kind == "avg" else 1 for kind, _ in case["outputs"])
            assert len(query.description) == arity
            for column, ref in zip(query.description, case["groups"]):
                assert rows.type_info(str(column[1])) == {"kind": argument_kind(ref), "decimal": None}
            logical_records = connection.execute(logical_sql(case), parameters).fetchall()
            trace.append(reference_snapshot(case, sequence, expanded, physical_changed, group_records, logical_records, False))
        return trace
    finally:
        connection.close()


def substitute_parameters(text, case):
    parameters = case.get("parameters", [])
    # Fixture placeholders occur only as predicate expressions, never in quotes.
    return re.sub(r"\$(\d+)", lambda match: rows.literal(parameters[int(match[1]) - 1]), text)


def json_rows(query, arity):
    names = [f"c{index}" for index in range(arity)]
    source = f"({query}) AS q(" + ",".join(names) + ")"
    fields = ",".join(f"{name}::text" for name in names)
    return f"COALESCE((SELECT json_agg(json_build_array({fields})) FROM {source}),'[]'::json)"


def postgres_reference(case, postgres):
    tables = ",".join(table["name"] for table in case["catalog"]["tables"])
    postgres.sql(";\n".join([f"DROP TABLE IF EXISTS {tables}", *rows.ddl(case, "postgres")]) + ";\n")
    aggregate = substitute_parameters(sql(case, True), case)
    logical = substitute_parameters(logical_sql(case), case)
    description = list(csv.reader(StringIO(postgres.sql(aggregate + "\n\\gdesc\n", csv_output=True))))
    assert description[0] == ["Column", "Type"]
    arity = len(case["groups"]) + sum(2 if kind == "avg" else 1 for kind, _ in case["outputs"])
    assert len(description)-1 == arity
    for column, ref in zip(description[1:], case["groups"]):
        assert rows.type_info(column[1]) == {"kind": argument_kind(ref), "decimal": None}
    script, boundaries = [], list(states(case))
    for sequence, expanded, _ in boundaries:
        script.append(f"TRUNCATE {tables}")
        for table, values in zip(case["catalog"]["tables"], expanded):
            if values:
                script.append(f"INSERT INTO {table['name']} VALUES " + ",".join(
                    "(" + ",".join(rows.literal(value) for value in record) + ")" for record in values))
        script.append(f"SELECT json_build_object('sequence',{sequence},'groups',{json_rows(aggregate, arity)},"
                      f"'logical',{json_rows(logical, len(logical_references(case)) or 1)})")
    observed = [json.loads(line) for line in postgres.sql(";\n".join(script) + ";\n").splitlines()]
    assert [item["sequence"] for item in observed] == list(range(len(boundaries)))
    return [reference_snapshot(case, sequence, expanded, changed, result["groups"], result["logical"], True)
            for (sequence, expanded, changed), result in zip(boundaries, observed)]


def group_map(groups):
    result = {}
    for group in groups:
        assert set(group) == {"key", "values"} and type(group["key"]) is list and type(group["values"]) is list
        identity = rows.key(group["key"]); assert identity not in result, "native lost full group identity"
        result[identity] = group
    return result


def output_diff(before, after):
    result = {}
    for identity in before.keys() | after.keys():
        previous, following = before.get(identity), after.get(identity)
        if previous != following:
            key = (following or previous)["key"]
            result[identity] = {"key": key, "before": previous["values"] if previous else None,
                                "after": following["values"] if following else None}
    return result


def session_epoch(encoded):
    """Read actual GroupEpoch bytes independently with Python stdlib.

    This bounded fixture reader owns no native state or durable authority. Full
    frame hashes, nullable tuple boundaries and typed scalars precede SQL checks.
    """
    data = bytes.fromhex(encoded)
    assert 255 <= len(data) <= 128*1024*1024 and data[:8] == b"CROWNAG2"
    assert struct.unpack_from("<HHQ", data, 8) == (1, 0, len(data)-148)
    assert data[20:84] == hashlib.sha256(data[148:]).hexdigest().encode("ascii")
    assert data[84:148] == hashlib.sha256(data[:84]).hexdigest().encode("ascii")
    position = 148

    def take(size):
        nonlocal position
        assert 0 <= size <= len(data)-position
        value = data[position:position+size]; position += size
        return value

    def word():
        return int.from_bytes(take(8), "little")

    def flag():
        value = take(1)[0]; assert value in (0, 1)
        return bool(value)

    def cell():
        if not flag():
            return None
        tag = take(1)[0]
        if tag == 0:
            return int.from_bytes(take(8), "little", signed=True)
        if tag == 1:
            return take(word()).decode("utf8")
        if tag == 2:
            return flag()
        if tag == 3:
            return {"date": str(datetime.date(1970, 1, 1) + datetime.timedelta(days=int.from_bytes(take(4), "little", signed=True)))}
        assert tag == 4
        return {"decimal": take(take(1)[0]).decode("ascii")}

    def row():
        size = word(); assert size <= 1000
        return [cell() for _ in range(size)]

    assert take(1) == b"\x05"
    ordinal, generation, command, sequence = word(), word(), word(), word()
    assert ordinal == sequence and generation > 0 and command >= sequence
    assert re.fullmatch(rb"[0-9a-f]{64}", take(64))
    changed, group_changed = flag(), flag()
    count = word(); assert count <= 100000
    output = []
    for _ in range(count):
        key = row(); before = row() if flag() else None; after = row() if flag() else None
        assert before is not None or after is not None
        output.append({"key": key, "before": before, "after": after})
    assert position == len(data)
    return {"sequence": sequence, "generation": generation, "command": command,
            "changed": changed, "group_changed": group_changed, "output": output}


def compare(case, observed, expected):
    assert observed["original_sql"] == case["sql"] and observed["source_sql"] != case["sql"]
    assert re.fullmatch(r"[0-9a-f]{64}", observed["binding"])
    assert rows.key((observed["types"], observed["key_types"], observed["names"])) == rows.key(expected_metadata(case)), case["id"]
    assert len(observed["trace"]) == len(expected) and len(observed["epochs"]) == len(expected)-1
    for sequence, (native, reference) in enumerate(zip(observed["trace"], expected)):
        assert type(native["sequence"]) is int and native["sequence"] == reference["sequence"] == sequence
        assert rows.key(group_map(native["groups"])) == rows.key(reference["groups"]), (case["id"], sequence, "snapshot", native, reference["groups"])
        if not sequence:
            continue
        epoch = observed["epochs"][sequence-1]
        if "frame_hex" in epoch:
            wire = session_epoch(epoch.pop("frame_hex"))
            assert wire["sequence"] == wire["command"] == wire["generation"] == sequence
            assert wire["changed"] is epoch["changed"] and wire["group_changed"] is epoch["group_changed"]
            epoch["output"] = wire["output"]
        assert type(epoch["sequence"]) is int and type(epoch["native_sequence"]) is int
        assert epoch["sequence"] == epoch["native_sequence"] == sequence and epoch["captured"] is True
        assert epoch["native_bag_retained"] is False
        assert epoch["changed"] is reference["changed"]
        assert epoch["group_changed"] is (reference["logical"] != expected[sequence-1]["logical"])
        actual = {}
        for event in epoch["output"]:
            assert set(event) == {"key", "before", "after"}
            assert event["before"] is None or type(event["before"]) is list
            assert event["after"] is None or type(event["after"]) is list
            identity = rows.key(event["key"]); assert identity not in actual
            actual[identity] = event
        assert rows.key(actual) == rows.key(output_diff(expected[sequence-1]["groups"], reference["groups"])), (case["id"], sequence, "batch_diff", actual)


def native_request(case, backend, rebuild=False, checkpoint=False, session=False):
    # Reference groups/outputs/tail never enter native binding as descriptors.
    result = {name: case[name] for name in ("catalog", "sql", "average_scale", "batches")}
    result.update(id=f"{case['id']}/{backend}", indexed=backend)
    if rebuild:
        result["rebuild_every_epoch"] = True
    if checkpoint:
        result["checkpoint_every_epoch"] = True
    if session:
        result["session_every_epoch"] = True
    for name in ("parameter_columns", "parameters", "multiplicity_limit", "count_limit"):
        if name in case:
            result[name] = case[name]
    return result


def reference_contract():
    # This checks oracle representation only, never native or SQL evaluation.
    assert rows.key([True]) != rows.key([1]) and rows.key([1.0]) != rows.key([1])
    null = {rows.key([None]): {"key": [None], "values": [None]}}
    assert output_diff({}, null) == {rows.key([None]): {"key": [None], "before": None, "after": [None]}}
    equal = {rows.key([name]): {"key": [name], "values": [2]} for name in ("a", "b")}
    assert len(output_diff(equal, {})) == 2
    assert arithmetic.numeric(Fraction(1, 2), 0) == {"decimal": "1"}
    assert arithmetic.numeric(Fraction(-1, 2), 0) == {"decimal": "-1"}


def main():
    if not __debug__:
        raise RuntimeError("independent oracle requires Python assertions enabled")
    reference_contract()
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--rebuild-every-epoch", action="store_true")
    mode.add_argument("--checkpoint-every-epoch", action="store_true")
    mode.add_argument("--session-every-epoch", action="store_true")
    parser.add_argument("--engine", choices=("duckdb", "postgres"), default="duckdb")
    parser.add_argument("--postgres-bin")
    args = parser.parse_args()
    if args.engine == "postgres" and not args.postgres_bin:
        parser.error("--postgres-bin is required; no SQL engine fallback")
    suite = [*fixed_cases(), *integer_cases(), *scale_cases(), *random_cases()]
    assert len({case["id"] for case in suite}) == len(suite)
    for case in suite:
        list(states(case))  # Check chains/bounds before native or mature SQL runs.
    requests = [native_request(case, backend, args.rebuild_every_epoch, args.checkpoint_every_epoch, args.session_every_epoch)
                for case in suite for backend in (False, True)]
    run = subprocess.run([args.driver], input="\n".join(json.dumps(item) for item in requests) + "\n",
                         text=True, capture_output=True, timeout=3600 if args.session_every_epoch else 600)
    assert run.returncode == 0, ("native driver", run.stderr, len(run.stdout.splitlines()))
    native = [json.loads(line) for line in run.stdout.splitlines()]
    assert len(native) == len(requests) and [item["id"] for item in native] == [item["id"] for item in requests]
    postgres = rows.Postgres(args.postgres_bin) if args.engine == "postgres" else None
    snapshots = epochs = 0
    try:
        if postgres:
            postgres.start()
        for index, case in enumerate(suite):
            expected = postgres_reference(case, postgres) if postgres else duckdb_reference(case)
            for backend in (0, 1):
                compare(case, native[2*index+backend], expected)
                assert native[2*index+backend]["rebuilds"] == (len(expected) if args.rebuild_every_epoch else 0)
                assert native[2*index+backend]["checkpoints"] == (len(expected) if args.checkpoint_every_epoch else 0)
                assert native[2*index+backend]["session_reopens"] == (4*(len(expected)-1) if args.session_every_epoch else 0)
                assert native[2*index+backend]["durable_checkpoints"] == (len(expected) if args.session_every_epoch else 0)
                snapshots += len(expected); epochs += len(expected)-1
        version = postgres.sql("SHOW server_version;\n").strip() if postgres else __import__("duckdb").__version__
    finally:
        if postgres:
            postgres.close()
    print(json.dumps({"engine": args.engine, "version": version, "seed": SEED,
                      "cases": len(suite), "native_cases": len(requests), "compared_snapshots": snapshots,
                      "compared_atomic_epochs": epochs, "avg_scales": list(range(19)),
                      "physical_rebuilds": sum(item["rebuilds"] for item in native),
                      "rebuild_after_each_epoch": args.rebuild_every_epoch,
                      "physical_checkpoints": sum(item["checkpoints"] for item in native),
                      "checkpoint_after_each_epoch": args.checkpoint_every_epoch,
                      "session_after_each_epoch": args.session_every_epoch,
                      "session_reopens": sum(item["session_reopens"] for item in native),
                      "durable_session_checkpoints": sum(item["durable_checkpoints"] for item in native),
                      "source_copy_cap_per_table": MAX_SOURCE_COPIES, "weight_cap": MAX_WEIGHT,
                      "expanded_small_physical_bags": True, "avg_from_sql_sum_count": True,
                      "private_postgres_stopped": bool(postgres), "varying_int32_column_excluded": False,
                      "varying_int32_cases": sum(case["id"].startswith("integer_") for case in suite)}))


if __name__ == "__main__":
    main()
