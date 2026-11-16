#!/usr/bin/env python3
"""Original full-assignment comparison CQ and independent exact SQLite oracle."""
import argparse
import copy
from fractions import Fraction
import json
from pathlib import Path
import random
import sqlite3
import subprocess

import key_specialization_oracle as relational

SEED = 0x7004C0
OPS = {"equal": "=", "not_equal": "<>", "less": "<", "less_equal": "<=",
       "greater": ">", "greater_equal": ">="}
DECIMAL_SCALE = 38
DECIMAL_BIAS = 10 ** 76


def scalar(value):
    if isinstance(value, dict):
        return Fraction(value["decimal"]) if "decimal" in value else value["date"]
    return value.encode("utf-8") if isinstance(value, str) else value


def holds(predicate, assignment):
    def operand(value):
        return scalar(assignment[value["var"]] if "var" in value else value["value"])
    left, right = operand(predicate["left"]), operand(predicate["right"])
    op = predicate["op"]
    if op == "equal":
        return left == right
    if op == "not_equal":
        return left != right
    if op == "less":
        return left < right
    if op == "less_equal":
        return left <= right
    if op == "greater":
        return left > right
    assert op == "greater_equal"
    return left >= right


def python_query(request, state):
    doc = request["document"]
    if doc["query"].get("contradiction", False):
        return {}
    ids = {source["name"]: i for i, source in enumerate(doc["catalog"]["tables"])}
    assignments = [{}]
    for atom in doc["query"]["atoms"]:
        joined = []
        for assignment in assignments:
            for row in state[ids[atom["table"]]].values():
                candidate = dict(assignment)
                for term, value in zip(atom["terms"], row):
                    if "const" in term and scalar(term["const"]) != scalar(value):
                        break
                    if "var" in term:
                        name = term["var"]
                        if name in candidate and scalar(candidate[name]) != scalar(value):
                            break
                        candidate[name] = value
                else:
                    joined.append(candidate)
        assignments = joined
    result = {}
    for assignment in assignments:
        # Keep hidden comparands and all witnesses until predicates finish.
        if all(holds(predicate, assignment) for predicate in request["predicates"]):
            row = [assignment[field["var"]] for field in doc["query"]["head"]]
            result[relational.row_key(row)] = row
    return result


def sql_scalar(value):
    if isinstance(value, dict) and "decimal" in value:
        # Exact monotone integer bias encoded as fixed-width BINARY TEXT. This
        # handles the complete finite 38-digit/38-scale domain without floats.
        scaled = Fraction(value["decimal"]) * 10 ** DECIMAL_SCALE
        assert scaled.denominator == 1
        encoded = scaled.numerator + DECIMAL_BIAS
        assert 0 <= encoded < 10 ** 77
        return str(encoded).zfill(77)
    return value["date"] if isinstance(value, dict) else value


def sql_decode(value, kind):
    if kind == "decimal":
        number = int(value) - DECIMAL_BIAS
        sign = "-" if number < 0 else ""
        whole, fraction = divmod(abs(number), 10 ** DECIMAL_SCALE)
        text = sign + str(whole) + "." + str(fraction).zfill(DECIMAL_SCALE)
        return relational.canonical({"decimal": text})
    if kind == "date":
        return {"date": value}
    return bool(value) if kind == "bool" else value


def sqlite_query(request, state):
    doc = request["document"]
    tables = doc["catalog"]["tables"]
    ids = {source["name"]: i for i, source in enumerate(tables)}
    quote = relational.quote
    with sqlite3.connect(":memory:") as database:
        for source, rows in zip(tables, state):
            schema = ",".join(quote(column["name"]) +
                              (" INTEGER" if column["type"] in ("int64", "bool") else " TEXT COLLATE BINARY")
                              for column in source["columns"])
            database.execute("CREATE TABLE " + quote(source["name"]) + "(" + schema + ")")
            if rows:
                database.executemany("INSERT INTO " + quote(source["name"]) + " VALUES (" +
                                     ",".join("?" for _ in source["columns"]) + ")",
                                     [[sql_scalar(value) for value in row] for row in rows.values()])
        valid = True
        for source in tables:
            for constraint in source.get("constraints", []):
                if constraint["status"] != "enforced":
                    continue
                name = quote(source["name"])
                if constraint["kind"] == "unique":
                    columns = constraint["columns"]
                    sql = ("SELECT 1 FROM " + name + " GROUP BY " + ",".join(map(quote, columns)) +
                           " HAVING count(*)>1 LIMIT 1") if columns else "SELECT 1 WHERE (SELECT count(*) FROM " + name + ")>1"
                else:
                    parent = quote(constraint["references"]["table"])
                    equal = " AND ".join("c." + quote(a) + "=p." + quote(b) for a, b in
                                         zip(constraint["columns"], constraint["references"]["columns"])) or "1"
                    sql = "SELECT 1 FROM " + name + " c WHERE NOT EXISTS (SELECT 1 FROM " + parent + " p WHERE " + equal + ") LIMIT 1"
                valid = valid and database.execute(sql).fetchone() is None
        aliases, conditions, parameters, bound = [], [], [], {}
        for index, atom in enumerate(doc["query"]["atoms"]):
            alias = "a" + str(index)
            aliases.append(quote(atom["table"]) + " " + alias)
            source = tables[ids[atom["table"]]]
            for term, column in zip(atom["terms"], source["columns"]):
                field = alias + "." + quote(column["name"])
                if "const" in term:
                    conditions.append(field + "=?")
                    parameters.append(sql_scalar(term["const"]))
                elif "var" in term:
                    if term["var"] in bound:
                        conditions.append(field + "=" + bound[term["var"]])
                    else:
                        bound[term["var"]] = field
        def operand(value):
            if "var" in value:
                return bound[value["var"]]
            parameters.append(sql_scalar(value["value"]))
            return "?"
        for predicate in request["predicates"]:
            left = operand(predicate["left"])
            right = operand(predicate["right"])
            conditions.append("(" + left + OPS[predicate["op"]] + right + ")")
        if doc["query"].get("contradiction", False):
            conditions.append("0")
        head = doc["query"]["head"]
        sql = "SELECT DISTINCT " + (",".join(bound[field["var"]] for field in head) if head else "1")
        sql += " FROM " + ",".join(aliases) if aliases else ""
        if conditions:
            sql += " WHERE " + " AND ".join(conditions)
        types = {variable["name"]: variable["type"] for variable in doc["query"]["variables"]}
        result = {}
        for raw in database.execute(sql, parameters):
            row = [sql_decode(value, types[field["var"]]) for field, value in zip(head, raw)]
            result[relational.row_key(row)] = row
        return valid, result


def predicate(left, op, right):
    return {"left": {"var": left} if isinstance(left, str) else {"value": left}, "op": op,
            "right": {"var": right} if isinstance(right, str) else {"value": right}}


def case(name, tables, atoms, head, predicates, operations, seed, contradiction=False):
    tables, atoms = copy.deepcopy(tables), copy.deepcopy(atoms)
    rng = random.Random(seed)
    rng.shuffle(tables)
    rng.shuffle(atoms)
    document = relational.document(tables, atoms, head, {}, seed)
    if contradiction:
        document["query"]["contradiction"] = True
    ids = {source["name"]: i for i, source in enumerate(tables)}
    state, sequence, events = [{} for _ in tables], 0, []
    for source, op, raw in operations:
        row = [relational.canonical(value) for value in raw]
        event = {"sequence": sequence + 1, "table": ids[source], "op": op, "values": row}
        proposed = copy.deepcopy(state)
        if op == "insert":
            proposed[ids[source]][relational.row_key(row)] = row
        else:
            proposed[ids[source]].pop(relational.row_key(row), None)
        if relational.python_constraints(tables, proposed):
            state, sequence = proposed, sequence + 1
        events.append(event)
    return {"id": name, "document": document, "predicates": predicates, "events": events}


def corpus():
    cases = []
    tables = [relational.table("r", [("id", "int64"), ("x", "int64")]), relational.table("s", [("y", "int64")])]
    atoms = [relational.atom("r0", "r", [relational.var("id"), relational.var("x")]),
             relational.atom("s0", "s", [relational.var("y")])]
    extreme = [-(1 << 63), 0, 1, 9007199254740993, (1 << 63) - 1]
    operations = [("r", "insert", [i, value]) for i, value in enumerate(extreme)]
    operations += [("s", "insert", [value]) for value in extreme]
    operations += [("s", "delete", [value]) for value in extreme]
    operations += [("s", "insert", [9007199254740992]), ("r", "delete", [3, 9007199254740993]),
                   ("s", "insert", [9007199254740992]), ("s", "delete", [999])]
    for index, op in enumerate(OPS):
        cases.append(case("all-six-hidden-" + op, tables, atoms, ["id"], [predicate("x", op, "y")], operations, SEED + index))
    collision = [("r", "insert", [1, 3]), ("r", "insert", [1, 4]), ("s", "insert", [5]),
                 ("s", "insert", [6]), ("r", "delete", [1, 3]), ("r", "insert", [1, 3]),
                 ("s", "delete", [5]), ("s", "insert", [5]), ("r", "delete", [1, 4]),
                 ("r", "delete", [1, 3])]
    for head in (["id", "id"], []):
        cases.append(case("collision-last-witness-" + str(len(head)), tables, atoms, head,
                          [predicate("x", "less", "y"), predicate("y", "less", 6)], collision, SEED + 10 + len(head)))
    typed = {
        "string": ["", "a", "a\0", "a\0b", "a\0c", "z", "é", "Ω", "😀"],
        "date": [{"date": value} for value in ("0001-01-01", "1970-01-01", "2000-02-29", "9999-12-31")],
        "decimal": [{"decimal": value} for value in ("-99999999999999999999999999999999999999", "-0.1", "0",
                    "0.00000000000000000000000000000000000001", "0.10", "0.1", "1.001", "99999999999999999999999999999999999999")],
        "bool": [False, True]}
    for number, (kind, values) in enumerate(typed.items()):
        sources = [relational.table("r", [("id", "int64"), ("x", kind)]), relational.table("s", [("y", kind)])]
        actions = [("r", "insert", [i, value]) for i, value in enumerate(values)]
        actions += [("s", "insert", [value]) for value in values]
        actions += [("s", "delete", [value]) for value in values]
        for index, op in enumerate(OPS):
            clauses = [predicate("x", op, "y")]
            # Constant comparison uses exact typed values, including string
            # constants which cannot use the variable-name convenience above.
            clauses.append({"left": {"var": "x"}, "op": "greater_equal", "right": {"value": values[0]}})
            cases.append(case("typed-" + kind + "-" + op, sources, atoms, ["id", "x", "id"], clauses,
                              actions, SEED + 100 + number * 10 + index))
    alias_table = [relational.table("r", [("k", "int64"), ("v", "int64")])]
    aliases = [relational.atom("left", "r", [relational.var("k"), relational.var("x")]),
               relational.atom("right", "r", [relational.var("k"), relational.var("y")])]
    aliases_ops = [("r", "insert", [1, value]) for value in (1, 2, 3)]
    aliases_ops += [("r", "delete", [1, 1]), ("r", "delete", [1, 2]), ("r", "insert", [1, 1])]
    cases.append(case("same-source-aliases-with-equality", alias_table, aliases, ["k", "k"],
                      [predicate("x", "less", "y")], aliases_ops, SEED + 200))
    constrained = copy.deepcopy(tables)
    constrained += [relational.table("parent", [("id", "int64"), ("payload", "int64")]),
                    relational.table("unused", [("id", "int64"), ("payload", "int64")])]
    constrained[0]["constraints"] = [relational.foreign("fk", ["id"], "parent", ["id"])]
    constrained[2]["constraints"] = [relational.unique("pk", ["id"])]
    constrained[3]["constraints"] = [relational.unique("u", ["id"])]
    actions = [("r", "insert", [7, 1]), ("parent", "insert", [7, 8]), ("r", "insert", [7, 1]),
               ("s", "insert", [2]), ("parent", "delete", [7, 8]), ("parent", "insert", [7, 9]),
               ("unused", "insert", [3, 1]), ("unused", "insert", [3, 2]), ("r", "delete", [7, 1]),
               ("parent", "delete", [7, 8])]
    cases.append(case("complete-source-fk-and-unused-unique", constrained, atoms, ["id"],
                      [predicate("x", "less", "y")], actions, SEED + 201))
    for index, predicates in enumerate(([], [predicate(1, "less", 2)], [predicate(1, "greater", 2)])):
        cases.append(case("constant-empty-conjunction-" + str(index), [], [], [], predicates, [], SEED + 210 + index))
    cases.append(case("contradictory-original-query", tables, atoms, [], [predicate("x", "less", "y")],
                      collision, SEED + 214, contradiction=True))
    cases.append(case("empty-conjunction-with-sources", tables, atoms, ["id"], [], collision, SEED + 215))
    for run in range(4):
        rng = random.Random(SEED + 300 + run)
        pool = {"r": [[identity, value] for identity in range(3) for value in range(-2, 3)],
                "s": [[value] for value in range(-2, 3)]}
        actions = [(source, rng.choice(("insert", "delete")), copy.deepcopy(rng.choice(pool[source])))
                   for source in (rng.choice(("r", "s")) for _ in range(45))]
        cases.append(case("seeded-hidden-prefixes-" + str(run), tables, atoms, ["id", "id"],
                          [predicate("x", "less_equal", "y"), predicate("y", "not_equal", 0)], actions, SEED + 300 + run))
    return cases


def expected_snapshot(request, state, sequence):
    expected = python_query(request, state)
    valid, sql = sqlite_query(request, state)
    assert valid and expected == sql, (request["id"], "independent predicate/CQ definitions disagree", expected, sql)
    return {"sequence": sequence, "rows": expected, "source": copy.deepcopy(state)}


def reference(request):
    tables = request["document"]["catalog"]["tables"]
    state, sequence = [{} for _ in tables], 0
    initial = expected_snapshot(request, state, sequence)
    trace = []
    for event in request["events"]:
        before = python_query(request, state)
        proposed = copy.deepcopy(state)
        identity = relational.row_key(event["values"])
        present = identity in proposed[event["table"]]
        if event["op"] == "insert":
            proposed[event["table"]][identity] = event["values"]
        else:
            proposed[event["table"]].pop(identity, None)
        python_valid = relational.python_constraints(tables, proposed)
        sqlite_valid, _ = sqlite_query(request, proposed)
        assert python_valid == sqlite_valid
        error = "invalid_sequence" if event["sequence"] != sequence + 1 else None
        if error is None and not python_valid:
            error = "constraint_violation"
        if error is None:
            state, sequence = proposed, sequence + 1
        after = python_query(request, state)
        trace.append({"error": error, "changed": present != (event["op"] == "insert"),
                      "added": {key: after[key] for key in after.keys() - before.keys()},
                      "removed": {key: before[key] for key in before.keys() - after.keys()},
                      "snapshot": expected_snapshot(request, state, sequence)})
    return initial, trace


def rows(value):
    result = {relational.row_key(row): [relational.canonical(cell) for cell in row] for row in value}
    assert len(result) == len(value), "duplicate native endpoint output"
    return result


def compare_snapshot(actual, expected, request):
    assert actual["ready"] and actual["sequence"] == expected["sequence"]
    assert actual["original_account"] and actual["predicate_count"] == len(request["predicates"])
    assert rows(actual["rows"]) == expected["rows"]
    assert actual["has_answer"] == bool(expected["rows"])
    assert [rows(table) for table in actual["source"]] == expected["source"]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True, type=Path)
    parser.add_argument("--artifacts", type=Path)
    args = parser.parse_args()
    requests, expected = [], []
    for request in corpus():
        model = reference(request)
        for indexed in (False, True):
            item = copy.deepcopy(request)
            item["indexed"] = indexed
            item["id"] += "-indexed" if indexed else "-reference"
            requests.append(item)
            expected.append(model)
    wire = "".join(relational.key(request) + "\n" for request in requests)
    if args.artifacts:
        args.artifacts.mkdir(parents=True)
        (args.artifacts / "native-request.jsonl").write_text(wire)
    native = subprocess.run([str(args.driver.resolve())], input=wire, text=True, capture_output=True, check=False)
    if args.artifacts:
        (args.artifacts / "native.stdout").write_text(native.stdout)
        (args.artifacts / "native.stderr").write_text(native.stderr)
    assert native.returncode == 0, (native.returncode, native.stderr)
    outputs = [json.loads(line) for line in native.stdout.splitlines()]
    assert len(outputs) == len(requests)
    for actual, request, (initial, trace) in zip(outputs, requests, expected):
        try:
            assert actual["id"] == request["id"] and actual["general_unchanged"]
            assert actual["original_atoms"] == len(request["document"]["query"]["atoms"])
            assert actual["predicates"] == len(request["predicates"])
            compare_snapshot(actual["initial"], initial, request)
            assert len(actual["trace"]) == len(trace)
            for frame, want in zip(actual["trace"], trace):
                event = frame["event"]
                assert event["error"] == want["error"]
                compare_snapshot(frame["snapshot"], want["snapshot"], request)
                if want["error"] is None:
                    assert event["changed"] == want["changed"]
                    assert rows(event["added"]) == want["added"] and rows(event["removed"]) == want["removed"]
                    assert event["metrics"]["added"] == len(want["added"])
                    assert event["metrics"]["removed"] == len(want["removed"])
        except AssertionError as failure:
            raise AssertionError(request["id"]) from failure
    summary = {"status": "PASS_original_CQ_predicates_before_projection_and_exact_deltas", "native_cases": len(requests),
               "source_events": sum(len(request["events"]) for request in requests), "backends": 2,
               "oracle": "original full assignments, exact Python Fraction/UTF8 order, independent SQLite predicates/constraints",
               "sqlite_decimal_order": "77-digit biased fixed-width exact scaled integer TEXT, no floating point",
               "sqlite_version": sqlite3.sqlite_version}
    if args.artifacts:
        (args.artifacts / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))


if __name__ == "__main__":
    main()
