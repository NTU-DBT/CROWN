#!/usr/bin/env python3
"""Independent full-assignment bag/SQLite oracles for exact CQ difference."""
import argparse
from collections import Counter
import copy
import json
from pathlib import Path
import random
import sqlite3
import subprocess

import fallback_oracle as structural
import key_specialization_oracle as relational

SEED = 0xC72008
MAX_U64 = (1 << 64) - 1
var, const, table, atom = relational.var, relational.const, relational.table, relational.atom
IGNORE = relational.IGNORE


# Count every complete physical-row assignment, including hidden/ignored
# witnesses and independent self-join choices, before projecting the head.
def python_operand(doc, state):
    if doc["query"].get("contradiction", False):
        return {}, Counter()
    ids = {source["name"]: i for i, source in enumerate(doc["catalog"]["tables"])}
    assignments = [{}]
    for occurrence in doc["query"]["atoms"]:
        joined = []
        for assignment in assignments:
            for row in state[ids[occurrence["table"]]].values():
                candidate = dict(assignment)
                for term, value in zip(occurrence["terms"], row):
                    if "const" in term and relational.key(relational.canonical(term["const"])) != relational.key(value):
                        break
                    if "var" in term:
                        name = term["var"]
                        if name in candidate and relational.key(candidate[name]) != relational.key(value):
                            break
                        candidate[name] = value
                else:
                    joined.append(candidate)
        assignments = joined
    rows, counts = {}, Counter()
    for assignment in assignments:
        row = [assignment[field["var"]] for field in doc["query"]["head"]]
        key = relational.row_key(row)
        rows[key] = row
        counts[key] += 1
    return rows, counts


def python_difference(left, right, state, mode):
    rows, left_counts = python_operand(left, state)
    _, right_counts = python_operand(right, state)
    counts = Counter()
    for key, count in left_counts.items():
        residual = int(right_counts[key] == 0) if mode == "set_except" else max(count - right_counts[key], 0)
        if residual:
            counts[key] = residual
    return rows, counts


# Raw CQ SELECTs deliberately omit DISTINCT. Grouped counts and the residual
# LEFT JOIN are SQL's independent count-difference definition, not Python's
# Counter calculation or unsupported SQLite EXCEPT ALL syntax.
def operand_sql(doc):
    tables = {source["name"]: source for source in doc["catalog"]["tables"]}
    aliases, conditions, parameters, bound = [], [], [], {}
    quote = relational.quote
    for index, occurrence in enumerate(doc["query"]["atoms"]):
        aliases.append("main." + quote(occurrence["table"]) + " AS a" + str(index))
        for term, column in zip(occurrence["terms"], tables[occurrence["table"]]["columns"]):
            field = "a" + str(index) + "." + quote(column["name"])
            if "const" in term:
                conditions.append(field + "=?")
                parameters.append(structural.sql_value(term["const"]))
            elif "var" in term:
                if term["var"] in bound:
                    conditions.append(field + "=" + bound[term["var"]])
                else:
                    bound[term["var"]] = field
    if doc["query"].get("contradiction", False):
        conditions.append("0")
    head = doc["query"]["head"]
    select = ",".join(bound[field["var"]] + " AS c" + str(i) for i, field in enumerate(head)) if head else "1 AS c0"
    sql = "SELECT " + select + (" FROM " + ",".join(aliases) if aliases else "")
    if conditions:
        sql += " WHERE " + " AND ".join(conditions)
    return sql, parameters


def decode_row(doc, raw):
    types = {variable["name"]: variable["type"] for variable in doc["query"]["variables"]}
    result = []
    for field, value in zip(doc["query"]["head"], raw):
        kind = types[field["var"]]
        result.append({"decimal": value} if kind == "decimal" else {"date": value} if kind == "date"
                      else bool(value) if kind == "bool" else value)
    return result


# Complete original sources and constraints are materialized independently.
# Decimal/date values use canonical exact TEXT equality; no float arithmetic.
def sqlite_difference(left, right, state, mode):
    tables = left["catalog"]["tables"]
    quote = relational.quote
    with sqlite3.connect(":memory:") as db:
        for source, rows in zip(tables, state):
            columns = ",".join(quote(column["name"]) +
                               (" INTEGER" if column["type"] in ("int64", "bool") else " TEXT COLLATE BINARY")
                               for column in source["columns"]) or "_nullary INTEGER"
            db.execute("CREATE TABLE " + quote(source["name"]) + "(" + columns + ")")
            db.executemany("INSERT INTO " + quote(source["name"]) + " VALUES(" +
                           ",".join("?" for _ in range(max(1, len(source["columns"])))) + ")",
                           [[structural.sql_value(value) for value in row] if row else [1] for row in rows.values()])
        valid = True
        for source in tables:
            for constraint in source.get("constraints", []):
                if constraint["status"] != "enforced":
                    continue
                name, columns = quote(source["name"]), constraint["columns"]
                if constraint["kind"] == "unique":
                    check = ("SELECT 1 FROM " + name + " GROUP BY " + ",".join(map(quote, columns)) + " HAVING count(*)>1 LIMIT 1"
                             if columns else "SELECT 1 FROM " + name + " HAVING count(*)>1")
                    if not columns:
                        bad = db.execute("SELECT count(*) FROM " + name).fetchone()[0] > 1
                    else:
                        bad = db.execute(check).fetchone() is not None
                else:
                    parent = quote(constraint["references"]["table"])
                    equal = " AND ".join("c." + quote(a) + "=p." + quote(b)
                                         for a, b in zip(columns, constraint["references"]["columns"])) or "1"
                    bad = db.execute("SELECT 1 FROM " + name + " c WHERE NOT EXISTS(SELECT 1 FROM " +
                                     parent + " p WHERE " + equal + ") LIMIT 1").fetchone() is not None
                valid = valid and not bad
        lsql, largs = operand_sql(left)
        rsql, rargs = operand_sql(right)
        width = max(1, len(left["query"]["head"]))
        columns = ",".join("c" + str(i) for i in range(width))
        group = "SELECT " + columns + ",count(*) AS n FROM {} GROUP BY " + columns
        ctes = "WITH lraw AS (" + lsql + "),rraw AS (" + rsql + "),l AS (" + group.format("lraw") + "),r AS (" + group.format("rraw") + ") "
        # Verify both raw operand bags independently before checking difference.
        operands = []
        for sql, args, doc in [(lsql, largs, left), (rsql, rargs, right)]:
            counts = Counter()
            for raw in db.execute("SELECT " + columns + ",count(*) FROM (" + sql + ") GROUP BY " + columns, args):
                counts[relational.row_key(decode_row(doc, raw[:width]))] = raw[width]
            operands.append(counts)
        equal = " AND ".join("l.c" + str(i) + "=r.c" + str(i) for i in range(width))
        select = ",".join("l.c" + str(i) for i in range(width))
        residual = "1" if mode == "set_except" else "l.n-coalesce(r.n,0)"
        condition = "r.n IS NULL" if mode == "set_except" else "l.n>coalesce(r.n,0)"
        sql = ctes + "SELECT " + select + "," + residual + " FROM l LEFT JOIN r ON " + equal + " WHERE " + condition
        rows, counts = {}, Counter()
        for raw in db.execute(sql, largs + rargs):
            row = decode_row(left, raw[:width]); key = relational.row_key(row)
            assert key not in counts and raw[width] > 0
            rows[key], counts[key] = row, raw[width]
        return valid, rows, counts, operands


def document_pair(request):
    left = request["document"]
    right = copy.deepcopy(left)
    right["query"] = request["right_query"]
    return left, right


def make_case(name, tables, left, right, operations, seed):
    tables, left, right = copy.deepcopy(tables), copy.deepcopy(left), copy.deepcopy(right)
    rng = random.Random(seed)
    rng.shuffle(tables)
    rng.shuffle(left[0]); rng.shuffle(right[0])
    for side, operand in enumerate([left, right]):
        for index, occurrence in enumerate(operand[0]):
            occurrence["id"] = "occ_" + str(seed) + "_" + str(side) + "_" + str(index)
    ldoc = relational.document(tables, left[0], left[1], {}, seed)
    rdoc = relational.document(tables, right[0], right[1], {}, seed + 1000)
    for doc, operand in [(ldoc, left), (rdoc, right)]:
        if len(operand) > 2 and operand[2]:
            doc["query"]["contradiction"] = True
        for index, field in enumerate(doc["query"]["head"]):
            field["alias"] = "out_" + str(seed) + "_" + str(index)
    ids = {source["name"]: i for i, source in enumerate(tables)}
    state, sequence, events = [{} for _ in tables], 0, []
    for source, operation, raw in operations:
        row = [relational.canonical(value) for value in raw]
        trial = [dict(rows) for rows in state]
        if operation == "insert":
            trial[ids[source]][relational.row_key(row)] = row
        else:
            trial[ids[source]].pop(relational.row_key(row), None)
        events.append({"sequence": sequence + 1, "table": ids[source], "op": operation, "values": row})
        if relational.python_constraints(tables, trial):
            state, sequence = trial, sequence + 1
    return {"id": name, "document": ldoc, "right_query": rdoc["query"], "events": events}


def corpus():
    cases = []

    def add(name, tables, left, right, operations):
        cases.append(make_case(name, tables, left, right, operations, SEED + len(cases)))

    tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ["L", "R", "Unused"]]
    left, right = ([atom("l", "L", [var("x"), var("hidden")])], ["x"]), ([atom("r", "R", [var("y"), IGNORE])], ["y"])
    collisions = [("L", "insert", [1, 7]), ("L", "insert", [1, 8]), ("R", "insert", [1, 9]),
                  ("L", "delete", [1, 7]), ("L", "insert", [1, 7]), ("R", "insert", [1, 10]),
                  ("R", "insert", [1, 11]), ("R", "delete", [1, 9]), ("R", "delete", [1, 10]),
                  ("R", "delete", [1, 11]), ("L", "insert", [2, 6]), ("R", "insert", [2, 0]),
                  ("R", "insert", [2, 0]), ("R", "delete", [99, 0]), ("Unused", "insert", [5, 5]),
                  ("Unused", "delete", [5, 5]), ("R", "delete", [2, 0]), ("L", "delete", [1, 8]),
                  ("L", "delete", [1, 7])]
    add("projected_counts_right_only_retractions", tables, left, right, collisions)
    add("same_operand_cancels", tables, left, left, collisions)
    add("boolean_counts_are_not_presence", tables, (left[0], []), (right[0], []), collisions)
    add("repeated_head_positions", tables, (left[0], ["x", "x"]), (right[0], ["y", "y"]), collisions)
    add("contradictory_left", tables, (left[0], ["x"], True), right, collisions)
    add("contradictory_right", tables, left, (right[0], ["y"], True), collisions)

    tables = [table("N", []), table("M", []), table("U", [("v", "int64")])]
    nullary = [("N", "insert", []), ("M", "insert", []), ("M", "delete", []), ("N", "insert", []),
               ("U", "insert", [4]), ("N", "delete", []), ("M", "insert", []), ("M", "delete", [])]
    add("nullary_sources", tables, ([atom("n", "N", [])], []), ([atom("m", "M", [])], []), nullary)
    add("empty_left_body", tables, ([], []), ([atom("n", "N", [])], []), nullary)
    add("empty_right_body", tables, ([atom("n", "N", [])], []), ([], []), nullary)
    add("both_empty_bodies", tables, ([], []), ([], []), nullary)
    add("empty_false_right_body", tables, ([], []), ([], [], True), nullary)

    tables = [table("A", [("a", "int64"), ("b", "int64"), ("c", "int64")]), table("B", [("a", "int64"), ("b", "int64"), ("c", "int64")])]
    left = ([atom("a", "A", [var("x"), var("x"), IGNORE])], ["x", "x"])
    right = ([atom("b", "B", [var("z"), const(7), IGNORE])], ["z", "z"])
    ops = [("A", "insert", [1, 1, 4]), ("A", "insert", [1, 1, 5]), ("A", "insert", [1, 2, 6]),
           ("B", "insert", [1, 8, 0]), ("B", "insert", [1, 7, 0]), ("B", "insert", [1, 7, 1]),
           ("B", "delete", [1, 7, 0]), ("A", "delete", [1, 1, 4]), ("B", "delete", [1, 7, 1])]
    add("repeated_variable_constants_ignored", tables, left, right, ops)

    tables = [table("E", [("a", "int64"), ("b", "int64")])]
    left = ([atom("l1", "E", [var("x"), var("y")]), atom("l2", "E", [var("y"), var("z")])], ["x"])
    right = ([atom("r1", "E", [var("u"), var("v")]), atom("r2", "E", [var("v"), var("u")])], ["u"])
    edges = [(1, 2), (2, 1), (2, 3), (3, 2), (3, 3), (1, 3)]
    ops = [("E", "insert", list(edge)) for edge in edges] + [("E", "delete", list(edge)) for edge in edges[::2]]
    add("two_aliases_same_physical_table", tables, left, right, ops)

    tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ["A", "B", "C", "D", "Filter"]]
    cycle = [atom("a", "A", [var("x"), var("y")]), atom("b", "B", [var("y"), var("z")]),
             atom("c", "C", [var("z"), var("w")]), atom("d", "D", [var("w"), var("x")])]
    right_cycle = [atom("a2", "A", [var("p"), var("q")]), atom("b2", "B", [var("q"), var("r")]),
                   atom("c2", "C", [var("r"), var("s")]), atom("d2", "D", [var("s"), var("p")]),
                   atom("f", "Filter", [var("q"), IGNORE])]
    ops = [("A", "insert", [1, 7]), ("A", "insert", [1, 8]), ("B", "insert", [7, 9]),
           ("B", "insert", [8, 9]), ("C", "insert", [9, 6]), ("D", "insert", [6, 1]),
           ("Filter", "insert", [7, 0]), ("Filter", "insert", [7, 1]), ("Filter", "delete", [7, 0]),
           ("Filter", "delete", [7, 1]), ("B", "delete", [8, 9]), ("D", "delete", [6, 1])]
    add("cyclic_four_with_filtered_operand", tables, (cycle, ["x", "z"]), (right_cycle, ["p", "r"]), ops)
    add("cyclic_four_boolean_counts", tables, (cycle, []), (right_cycle, []), ops)

    tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ["R", "S", "T"]]
    path = [atom("r", "R", [var("x"), var("y")]), atom("s", "S", [var("y"), var("z")])]
    single = [atom("t", "T", [var("p"), var("q")])]
    ops = [("R", "insert", [1, 7]), ("R", "insert", [1, 8]), ("S", "insert", [7, 9]),
           ("S", "insert", [8, 9]), ("T", "insert", [1, 9]), ("S", "delete", [7, 9]),
           ("T", "delete", [1, 9]), ("S", "insert", [7, 9]), ("R", "delete", [1, 8])]
    add("non_free_connex_against_atomic_head", tables, (path, ["x", "z"]), (single, ["p", "q"]), ops)
    tables += [table("U", [("a", "int64")])]
    disconnected = [atom("r", "R", [var("x"), IGNORE]), atom("u", "U", [var("z")])]
    add("disconnected_projected_product", tables, (disconnected, ["x", "z"]), (single, ["p", "q"]),
        ops + [("U", "insert", [9]), ("U", "insert", [10]), ("T", "insert", [1, 10]), ("U", "delete", [9])])

    typed = {
        "int64": [-(1 << 63), (1 << 63) - 1, 9007199254740993, 0],
        "string": ["", "a\0b", "é", "Ω"],
        "decimal": [{"decimal": "-99999999999999999999999999999999999999"},
                    {"decimal": "99999999999999999999999999999999999999"},
                    {"decimal": "0.00000000000000000000000000000000000001"}, {"decimal": "0.10"}],
        "date": [{"date": "0001-01-01"}, {"date": "9999-12-31"}, {"date": "2000-02-29"}, {"date": "1970-01-01"}],
        "bool": [False, True],
    }
    for kind, values in typed.items():
        tables = [table(name, [("value", kind), ("hidden", "int64")]) for name in ["L", "R"]]
        left = ([atom("l", "L", [var("x"), IGNORE])], ["x", "x"])
        right = ([atom("r", "R", [var("a"), IGNORE])], ["a", "a"])
        ops = []
        for value in values:
            ops += [("L", "insert", [value, 0]), ("L", "insert", [value, 1]), ("R", "insert", [value, 5]),
                    ("R", "insert", [value, 6]), ("R", "delete", [value, 5]), ("L", "delete", [value, 0]),
                    ("R", "delete", [value, 6])]
        add("typed_exact_" + kind, tables, left, right, ops)

    tables = [table("P", [("id", "int64")]), table("L", [("id", "int64"), ("hidden", "int64")]),
              table("R", [("id", "int64"), ("hidden", "int64")]), table("Unused", [("id", "int64"), ("value", "string")])]
    tables[0]["constraints"] = [relational.unique("parent_id", ["id"])]
    tables[1]["constraints"] = [relational.foreign("left_parent", ["id"], "P", ["id"])]
    tables[3]["constraints"] = [relational.unique("unused_id", ["id"])]
    left = ([atom("l", "L", [var("x"), IGNORE])], ["x"])
    right = ([atom("r", "R", [var("y"), IGNORE])], ["y"])
    ops = [("L", "insert", [1, 7]), ("P", "insert", [1]), ("L", "insert", [1, 7]),
           ("R", "insert", [1, 8]), ("P", "delete", [1]), ("Unused", "insert", [2, "a"]),
           ("Unused", "insert", [2, "b"]), ("R", "delete", [1, 8]), ("L", "delete", [1, 7]),
           ("P", "delete", [1]), ("Unused", "delete", [2, "a"])]
    add("full_catalog_fk_and_unused_unique_refusals", tables, left, right, ops)

    for seed in range(5):
        rng = random.Random(SEED + 100 + seed)
        tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ["R", "S", "T"]]
        left = ([atom("r", "R", [var("x"), var("h")]), atom("s", "S", [var("h"), var("z")])], ["x"])
        right = ([atom("t", "T", [var("a"), IGNORE])], ["a"])
        ops = [(rng.choice(["R", "S", "T"]), rng.choice(["insert", "delete"]), [rng.randrange(3), rng.randrange(3)])
               for _ in range(48)]
        add("seeded_prefixes_" + str(seed), tables, left, right, ops)
    return cases


def expected_profile(left, right, mode):
    lp, rp = structural.expected_profile(left), structural.expected_profile(right)
    return {"mode": mode, "backend": "exact_difference_recompute_v1",
            "semantics": "exact_set_except" if mode == "set_except" else "exact_bag_except_all_physical_set_witness_counts",
            "input": "physical_full_row_set_events", "arithmetic": "checked-uint64-multiplicity-v1",
            "output": "owning_tuple_and_positive_multiplicity", "delta": "exact_endpoint_multiplicity_replacements_not_aggregate_payload",
            "state": "sources_plus_residual_keys_and_private_operand_images",
            "startup": "eager_two_operand_recomputation_and_materialization",
            "delay": "materialized_output_no_constant_delay_claim", "termination": "owned_scratch_and_result_cleanup",
            "height": "no_CROWN_GHD_or_P11_certificate", "left_class": lp["query_class"], "right_class": rp["query_class"],
            "left_reason": lp["reason"], "right_reason": rp["reason"]}


def operand_estimates(doc, counts):
    ids = {source["name"]: i for i, source in enumerate(doc["catalog"]["tables"])}
    product = 0 if doc["query"].get("contradiction", False) else 1
    for occurrence in doc["query"]["atoms"]:
        product *= counts[ids[occurrence["table"]]]
    assert product <= MAX_U64, "finite oracle fixture product must remain exact"
    outputs = (0 if product == 0 else 1) if not doc["query"]["head"] else product
    return {"source_rows": sum(counts), "assignments_upper": product, "output_rows_upper": outputs,
            "state_rows_upper": sum(counts) + outputs, "overflow": False, "advisory": True}


def expected_estimates(left, right, counts, mode):
    lbound, rbound = operand_estimates(left, counts), operand_estimates(right, counts)
    # Bag Boolean projection retains every witness even though its one empty
    # tuple is a single compressed key; use left assignment bound for mass.
    mass = lbound["output_rows_upper"] if mode == "set_except" else lbound["assignments_upper"]
    return {"left": lbound, "right": rbound, "source_rows": sum(counts),
            "output_rows_upper": lbound["output_rows_upper"], "output_multiplicity_upper": mass,
            "state_rows_upper": sum(counts) + lbound["output_rows_upper"], "overflow": False, "advisory": True}


def cartesian(doc, counts):
    ids = {source["name"]: i for i, source in enumerate(doc["catalog"]["tables"])}
    product, prefix = 1, 0
    for occurrence in doc["query"]["atoms"]:
        product *= counts[ids[occurrence["table"]]]
        prefix += product
    assert product <= MAX_U64 and prefix <= MAX_U64
    return product, prefix


def entries(rows, counts):
    return [{"values": rows[key], "multiplicity": counts[key]} for key in sorted(counts)]


def snapshot(request, state, sequence):
    left, right = document_pair(request); mode = request["mode"]
    rows, counts = python_difference(left, right, state, mode)
    valid, sql_rows, sql_counts, operand_counts = sqlite_difference(left, right, state, mode)
    assert valid and counts == sql_counts and all(rows[key] == sql_rows[key] for key in counts), "independent difference models disagree"
    assert python_operand(left, state)[1] == operand_counts[0] and python_operand(right, state)[1] == operand_counts[1], "independent original operand bags disagree"
    table_counts = [len(source) for source in state]
    return {"sequence": sequence, "runtime_sequence": sequence, "ready": True, "rows": entries(rows, counts),
            "source": [relational.ordered(source) for source in state], "has_answer": bool(counts),
            "original_left_atoms": len(left["query"]["atoms"]), "original_right_atoms": len(right["query"]["atoms"]),
            "original_head": len(left["query"]["head"]), "source_only_atoms": 0, "original_account": True,
            "binding_profile": expected_profile(left, right, mode), "explain_profile": expected_profile(left, right, mode),
            "multiplicity_limit": MAX_U64, "binding_limit": MAX_U64,
            "table_rows": table_counts, "result_rows": len(counts), "result_multiplicity": sum(counts.values()),
            "left_witness_product": cartesian(left, table_counts)[0], "right_witness_product": cartesian(right, table_counts)[0],
            "left_prefix_product_sum": cartesian(left, table_counts)[1], "right_prefix_product_sum": cartesian(right, table_counts)[1],
            "estimates": expected_estimates(left, right, table_counts, mode)}


def reference(request):
    left, right = document_pair(request); tables = left["catalog"]["tables"]
    state, sequence = [{} for _ in tables], 0
    initial = snapshot(request, state, sequence); frames = []
    used = {occurrence["table"] for doc in [left, right] if not doc["query"].get("contradiction", False)
            for occurrence in doc["query"]["atoms"]}
    for event in request["events"]:
        assert event["sequence"] == sequence + 1
        row = [relational.canonical(value) for value in event["values"]]
        trial = [dict(source) for source in state]; source = trial[event["table"]]
        present = relational.row_key(row) in source
        if event["op"] == "insert":
            source[relational.row_key(row)] = row
        else:
            source.pop(relational.row_key(row), None)
        changed = present != (event["op"] == "insert")
        valid = relational.python_constraints(tables, trial)
        sql_valid = sqlite_difference(left, right, trial, request["mode"])[0]
        assert valid == sql_valid, "independent full-source constraint checks disagree"
        old_rows, old_counts = python_difference(left, right, state, request["mode"])
        if valid:
            state, sequence = trial, sequence + 1
        new_rows, new_counts = python_difference(left, right, state, request["mode"])
        changes = [{"values": new_rows.get(key, old_rows.get(key)), "before": old_counts[key], "after": new_counts[key],
                    "negative": new_counts[key] < old_counts[key], "magnitude": abs(new_counts[key] - old_counts[key])}
                   for key in sorted(old_counts.keys() | new_counts.keys()) if old_counts[key] != new_counts[key]]
        frames.append({"error": None if valid else "constraint_violation", "changed": changed,
                       "changes": changes, "recomputed": changed and tables[event["table"]]["name"] in used,
                       "snapshot": snapshot(request, state, sequence)})
    return {"profile": expected_profile(left, right, request["mode"]), "initial": initial, "frames": frames}


def normalized_rows(rows):
    result = {relational.row_key(row): [relational.canonical(value) for value in row] for row in rows}
    assert len(result) == len(rows), "native source export contains duplicate rows"
    return relational.ordered(result)


def normalized_entries(values, change=False):
    result = {}
    for entry in values:
        row = [relational.canonical(value) for value in entry["values"]]
        key = relational.row_key(row); assert key not in result, "duplicate native compressed key"
        if change:
            assert entry["before"] >= 0 and entry["after"] >= 0 and entry["before"] != entry["after"]
            result[key] = {"values": row, "before": entry["before"], "after": entry["after"],
                           "negative": entry["negative"], "magnitude": entry["magnitude"]}
        else:
            assert entry["multiplicity"] > 0
            result[key] = {"values": row, "multiplicity": entry["multiplicity"]}
    return relational.ordered(result)


def check_snapshot(actual, expected):
    actual = copy.deepcopy(actual)
    actual["rows"] = normalized_entries(actual["rows"])
    actual["source"] = [normalized_rows(rows) for rows in actual["source"]]
    assert actual == expected, (actual, expected)


def check_output(actual, expected, case_id):
    assert actual["id"] == case_id and actual["profile"] == expected["profile"]
    check_snapshot(actual["initial"], expected["initial"])
    assert len(actual["trace"]) == len(expected["frames"])
    for index, (frame, want) in enumerate(zip(actual["trace"], expected["frames"])):
        try:
            event = frame["event"]; assert event["error"] == want["error"]
            if want["error"] is None:
                assert event["changed"] == want["changed"]
                assert normalized_entries(event["changes"], True) == want["changes"]
                assert event["source_aliases"] == 0
                assert event["metrics"]["recomputed"] == want["recomputed"]
                assert event["metrics"]["changes"] == len(want["changes"])
            check_snapshot(frame["snapshot"], want["snapshot"])
        except AssertionError as error:
            raise AssertionError((case_id, "event", index, error.args)) from error


def requests_and_models():
    cases = corpus(); requests, models = [], []
    for mode in ["set_except", "bag_except_all"]:
        for case in cases:
            request = copy.deepcopy(case); request["mode"] = mode
            request["id"] += "_" + mode
            models.append(reference(request)); requests.append(request)
    return cases, requests, models


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    parser.add_argument("--artifacts", type=Path)
    args = parser.parse_args()
    cases, originals, models = requests_and_models(); requests = []
    for indexed in [False, True]:
        for request in originals:
            request = copy.deepcopy(request); request["indexed"] = indexed
            request["id"] += "_indexed" if indexed else "_reference"
            requests.append(request)
    wire = "".join(json.dumps(request, ensure_ascii=False, separators=(",", ":")) + "\n" for request in requests)
    native = subprocess.run([args.driver], input=wire, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
    if args.artifacts:
        args.artifacts.mkdir(parents=True, exist_ok=True)
        (args.artifacts / "native-request.jsonl").write_text(wire)
        (args.artifacts / "native.stdout").write_text(native.stdout)
        (args.artifacts / "native.stderr").write_text(native.stderr)
    assert native.returncode == 0, (native.returncode, native.stderr)
    outputs = [json.loads(line) for line in native.stdout.splitlines()]
    assert len(outputs) == len(requests)
    for index, (request, output) in enumerate(zip(requests, outputs)):
        check_output(output, models[index % len(originals)], request["id"])
    summary = {"status": "PASS", "seed": SEED, "cases": len(cases), "native_cases": len(requests),
               "events": sum(len(request["events"]) for request in requests),
               "images": sum(len(request["events"]) + 1 for request in requests),
               "modes": ["set_except", "bag_except_all"], "source_backends": ["reference", "indexed"],
               "left_classes": sorted({model["profile"]["left_class"] for model in models}),
               "right_classes": sorted({model["profile"]["right_class"] for model in models}),
               "oracle": "full original assignment Counter bags and independent SQLite raw operand/grouped count-difference CTE",
               "decimal": "canonical exact TEXT equality; no floating point or ordered/arithmetic decimal comparison",
               "limits": "finite corpus correctness, not CROWN/GHD/P11 bound, weighted source or SQL-NULL admission"}
    if args.artifacts:
        (args.artifacts / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))


if __name__ == "__main__":
    main()
