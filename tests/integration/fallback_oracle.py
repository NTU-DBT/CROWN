#!/usr/bin/env python3
"""Original full-CQ and SQLite oracles for the explicit exact fallback owner."""
import argparse
import copy
import json
from pathlib import Path
import random
import sqlite3
import subprocess

import key_specialization_oracle as relational

SEED = 0xC71006
MAX_U64 = (1 << 64) - 1
var, const, table, atom = relational.var, relational.const, relational.table, relational.atom
IGNORE = relational.IGNORE


# Expected rows follow the original atoms, including every self-join alias;
# projection happens only after all equality/constant tests have succeeded.
def python_query(doc, state):
    if doc["query"].get("contradiction", False):
        return {}
    return relational.python_query(doc, state)


def sql_value(value):
    value = relational.canonical(value)
    return next(iter(value.values())) if isinstance(value, dict) else value


# SQLite stores exact canonical decimal/date text and performs equality only.
# A dummy field represents a nullary physical relation's zero or one set row.
def sqlite_state(doc, state):
    tables = doc["catalog"]["tables"]
    ids = {source["name"]: index for index, source in enumerate(tables)}
    quote = relational.quote
    with sqlite3.connect(":memory:") as db:
        for source, rows in zip(tables, state):
            columns = ",".join(quote(column["name"]) +
                               (" INTEGER" if column["type"] in ("int64", "bool") else " TEXT COLLATE BINARY")
                               for column in source["columns"]) or "_nullary INTEGER"
            db.execute("CREATE TABLE " + quote(source["name"]) + "(" + columns + ")")
            width = max(1, len(source["columns"]))
            db.executemany("INSERT INTO " + quote(source["name"]) + " VALUES(" + ",".join("?" for _ in range(width)) + ")",
                           [[sql_value(value) for value in row] if row else [1] for row in rows.values()])
        valid = True
        for source in tables:
            for constraint in source.get("constraints", []):
                if constraint["status"] != "enforced":
                    continue
                name, columns = quote(source["name"]), constraint["columns"]
                if constraint["kind"] == "unique":
                    if columns:
                        query = "SELECT 1 FROM " + name + " GROUP BY " + ",".join(map(quote, columns)) + " HAVING count(*)>1 LIMIT 1"
                        bad = db.execute(query).fetchone() is not None
                    else:
                        bad = db.execute("SELECT count(*) FROM " + name).fetchone()[0] > 1
                else:
                    parent = quote(constraint["references"]["table"])
                    equal = " AND ".join("c." + quote(a) + "=p." + quote(b)
                                         for a, b in zip(columns, constraint["references"]["columns"])) or "1"
                    query = "SELECT 1 FROM " + name + " c WHERE NOT EXISTS(SELECT 1 FROM " + parent + " p WHERE " + equal + ") LIMIT 1"
                    bad = db.execute(query).fetchone() is not None
                valid = valid and not bad
        aliases, conditions, parameters, bound = [], [], [], {}
        for index, occurrence in enumerate(doc["query"]["atoms"]):
            aliases.append(quote(occurrence["table"]) + " AS a" + str(index))
            for term, column in zip(occurrence["terms"], tables[ids[occurrence["table"]]]["columns"]):
                field = "a" + str(index) + "." + quote(column["name"])
                if "const" in term:
                    conditions.append(field + "=?")
                    parameters.append(sql_value(term["const"]))
                elif "var" in term:
                    if term["var"] in bound:
                        conditions.append(field + "=" + bound[term["var"]])
                    else:
                        bound[term["var"]] = field
        if doc["query"].get("contradiction", False):
            conditions.append("0")
        head = doc["query"]["head"]
        select = ",".join(bound[field["var"]] for field in head) if head else "1"
        query = "SELECT DISTINCT " + select + (" FROM " + ",".join(aliases) if aliases else "")
        if conditions:
            query += " WHERE " + " AND ".join(conditions)
        types = {value["name"]: value["type"] for value in doc["query"]["variables"]}
        result = {}
        for raw in db.execute(query, parameters):
            row = []
            for field, value in zip(head, raw):
                kind = types[field["var"]]
                row.append({"decimal": value} if kind == "decimal" else {"date": value} if kind == "date"
                           else bool(value) if kind == "bool" else value)
            result[relational.row_key(row)] = row
        return valid, result


# Independent set-hypergraph GYO, used only to check the fixture's declared
# structural class. It does not consult native recognition or tree metadata.
def acyclic(edges):
    edges = [set(edge) for edge in edges]
    while edges:
        previous = [set(edge) for edge in edges]
        edges = [edge for edge in edges if edge]
        remove = set()
        for i, edge in enumerate(edges):
            for j, other in enumerate(edges):
                if i != j and edge <= other and (edge != other or i < j):
                    remove.add(i)
                    break
        edges = [edge for i, edge in enumerate(edges) if i not in remove]
        degree = {}
        for edge in edges:
            for name in edge:
                degree[name] = degree.get(name, 0) + 1
        edges = [edge - {name for name in edge if degree[name] == 1} for edge in edges]
        if edges == previous:
            return False
    return True


def classify(doc):
    scopes = [{term["var"] for term in occurrence["terms"] if "var" in term}
              for occurrence in doc["query"]["atoms"]]
    if not acyclic(scopes):
        return "cyclic"
    return "free_connex" if acyclic(scopes + [{field["var"] for field in doc["query"]["head"]}]) else "acyclic_non_free_connex"


def make_case(name, tables, atoms, head, operations, expected_class, seed, contradiction=False):
    tables, atoms = copy.deepcopy(tables), copy.deepcopy(atoms)
    rng = random.Random(seed)
    rng.shuffle(tables)
    rng.shuffle(atoms)
    # Occurrence spelling, declaration order and physical table order are all
    # independent of the mathematical variable/alias names in these fixtures.
    for index, occurrence in enumerate(atoms):
        occurrence["id"] = "occ_" + str(seed) + "_" + str(index)
    doc = relational.document(tables, atoms, head, {}, seed)
    if contradiction:
        doc["query"]["contradiction"] = True
    assert classify(doc) == expected_class, (name, classify(doc), expected_class)
    ids = {source["name"]: index for index, source in enumerate(tables)}
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
    return {"id": name, "document": doc, "events": events}


def corpus():
    cases = []

    def add(name, tables, atoms, head, operations, query_class, contradiction=False):
        cases.append(make_case(name, tables, atoms, head, operations, query_class, SEED + len(cases), contradiction))

    def triangle():
        return ([table(name, [("a", "int64"), ("b", "int64")]) for name in ("R", "S", "T")],
                [atom("r", "R", [var("x"), var("y")]), atom("s", "S", [var("y"), var("z")]),
                 atom("t", "T", [var("z"), var("x")])])

    triangle_ops = [("R", "insert", [1, 7]), ("R", "insert", [1, 8]), ("S", "insert", [7, 9]),
                    ("S", "insert", [8, 9]), ("T", "insert", [9, 1]), ("T", "insert", [9, 1]),
                    ("S", "delete", [7, 9]), ("S", "delete", [8, 9]), ("S", "delete", [8, 9]),
                    ("S", "insert", [7, 9]), ("T", "delete", [9, 1]), ("T", "insert", [9, 1])]
    for name, head in (("full", ["x", "y", "z"]), ("projected", ["x"]),
                       ("repeated", ["z", "x", "z"]), ("boolean", [])):
        tables, atoms = triangle()
        add("triangle_" + name, tables, atoms, head, triangle_ops, "cyclic")
    tables, atoms = triangle()
    add("triangle_contradiction", tables, atoms, ["x", "z"], triangle_ops, "cyclic", True)

    tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ("R", "S", "T", "U")]
    atoms = [atom(name.lower(), name, [var(a), var(b)]) for name, a, b in
             (("R", "x", "y"), ("S", "y", "z"), ("T", "z", "w"), ("U", "w", "x"))]
    ops = [(name, "insert", row) for name, row in (("R", [1, 2]), ("S", [2, 3]), ("T", [3, 4]), ("U", [4, 1]),
                                                   ("R", [1, 5]), ("S", [5, 3]))]
    ops += [("S", "delete", [2, 3]), ("S", "delete", [5, 3]), ("S", "insert", [2, 3]), ("U", "delete", [4, 1])]
    add("cycle4_endpoint_collision", tables, atoms, ["x", "z", "x"], ops, "cyclic")
    add("cycle4_boolean", tables, atoms, [], ops, "cyclic")

    tables, atoms = triangle()
    tables += [table(name, [("a", "int64"), ("b", "int64")]) for name in ("A", "B")]
    atoms += [atom("a", "A", [var("u"), var("v")]), atom("b", "B", [var("v"), var("w")])]
    add("disconnected_cycle_path", tables, atoms, ["x", "w"], triangle_ops +
        [("A", "insert", [2, 3]), ("B", "insert", [3, 4]), ("B", "insert", [3, 5]),
         ("A", "delete", [2, 3]), ("A", "insert", [2, 3])], "cyclic")

    path_tables = [table(name, [("a", "int64"), ("b", "int64")]) for name in ("R", "S")]
    path_atoms = [atom("r", "R", [var("x"), var("y")]), atom("s", "S", [var("y"), var("z")])]
    path_ops = [(source, operation, row) for source, operation, row in triangle_ops if source != "T"]
    for name, head, query_class in (("endpoints", ["x", "z"], "acyclic_non_free_connex"),
                                    ("repeated", ["z", "x", "z"], "acyclic_non_free_connex"),
                                    ("all_variables", ["z", "y", "x"], "free_connex"),
                                    ("boolean", [], "free_connex")):
        add("path_" + name, path_tables, path_atoms, head, path_ops, query_class)

    tables = [table("E", [("a", "int64"), ("b", "int64")])]
    atoms = [atom("e1", "E", [var("x"), var("y")]), atom("e2", "E", [var("y"), var("z")]),
             atom("e3", "E", [var("z"), var("x")])]
    ops = [("E", "insert", row) for row in ([1, 1], [1, 2], [2, 3], [3, 1], [2, 2])]
    ops += [("E", "delete", [1, 1]), ("E", "delete", [3, 1]), ("E", "insert", [3, 1]), ("E", "delete", [2, 2])]
    add("selfjoin_cycle_new_new", tables, atoms, ["z", "x", "z"], ops, "cyclic")
    add("selfjoin_cycle_boolean", tables, atoms, [], ops, "cyclic")

    tables = [table("R", [("a", "int64"), ("b", "int64"), ("payload", "string")]), table("S", [("v", "int64")])]
    atoms = [atom("r", "R", [var("x"), var("x"), IGNORE]), atom("s", "S", [const(7)])]
    ops = [("R", "insert", [1, 1, "one"]), ("R", "insert", [1, 1, "two"]), ("R", "insert", [2, 3, "bad"]),
           ("S", "insert", [8]), ("S", "insert", [7]), ("R", "delete", [1, 1, "one"]),
           ("R", "delete", [1, 1, "two"]), ("R", "insert", [4, 4, "a\0é"]), ("S", "delete", [7])]
    add("repeated_ignored_constant", tables, atoms, ["x", "x"], ops, "free_connex")
    add("constant_ignored_boolean", [table("K", [("k", "int64"), ("payload", "string")])],
        [atom("k", "K", [const(3), IGNORE])], [],
        [("K", "insert", [4, "bad"]), ("K", "insert", [3, "one"]), ("K", "insert", [3, "two"]),
         ("K", "delete", [3, "one"]), ("K", "delete", [3, "two"])], "free_connex")
    add("nullary_selfaliases", [table("A", []), table("B", [])],
        [atom("a1", "A", []), atom("a2", "A", []), atom("b", "B", [])], [],
        [("A", "insert", []), ("A", "insert", []), ("B", "insert", []), ("A", "delete", []),
         ("A", "insert", []), ("B", "delete", []), ("B", "delete", [])], "free_connex")
    add("empty_true", [], [], [], [], "free_connex")
    add("empty_false", [], [], [], [], "free_connex", True)
    add("empty_with_unused_source", [table("unused", [("v", "int64")])], [], [],
        [("unused", "insert", [7]), ("unused", "insert", [7]), ("unused", "delete", [7])], "free_connex")

    kinds = ["int64", "string", "decimal", "date", "bool"]
    tables = [table("C" + str(i), [("a", kinds[i]), ("b", kinds[(i + 1) % 5])]) for i in range(5)]
    atoms = [atom("c" + str(i), "C" + str(i), [var("v" + str(i)), var("v" + str((i + 1) % 5))]) for i in range(5)]
    values = [[-(1 << 63), "a\0b", {"decimal": "-99999999999999999999999999999999999999"}, {"date": "0001-01-01"}, False],
              [(1 << 63) - 1, "é", {"decimal": "99999999999999999999999999999999999999"}, {"date": "9999-12-31"}, True],
              [9007199254740993, "a\0b", {"decimal": "0.00000000000000000000000000000000000001"}, {"date": "2000-02-29"}, False],
              [0, "Ω", {"decimal": "0.10"}, {"date": "1970-01-01"}, True]]
    ops = [("C" + str(i), "insert", [row[i], row[(i + 1) % 5]]) for row in values for i in range(5)]
    ops += [("C2", "delete", [values[0][2], values[0][3]]), ("C2", "insert", [values[0][2], values[0][3]]),
            ("C0", "delete", [values[2][0], values[2][1]])]
    add("typed_cycle5_exact", tables, atoms, ["v4", "v1", "v2", "v0", "v3", "v1"], ops, "cyclic")
    add("typed_cycle5_boolean", tables, atoms, [], ops, "cyclic")

    tables, atoms = triangle()
    parent = table("P", [("id", "int64"), ("payload", "string")])
    parent["constraints"] = [relational.unique("parent_id", ["id"])]
    tables[0]["constraints"] = [relational.foreign("r_parent", ["a"], "P", ["id"])]
    unused = table("Unused", [("id", "int64"), ("payload", "string")])
    unused["constraints"] = [relational.unique("unused_id", ["id"])]
    tables += [parent, unused]
    ops = [("R", "insert", [1, 7]), ("P", "insert", [1, "one"]), ("R", "insert", [1, 7]),
           ("S", "insert", [7, 9]), ("T", "insert", [9, 1]), ("P", "delete", [1, "one"]),
           ("P", "insert", [1, "duplicate"]), ("Unused", "insert", [4, "a"]),
           ("Unused", "insert", [4, "b"]), ("Unused", "delete", [4, "a"]),
           ("R", "delete", [1, 7]), ("P", "delete", [1, "one"])]
    add("cycle_constraints_unused_denials", tables, atoms, ["x", "z"], ops, "cyclic")

    names = ["v" + str(i) for i in range(70)]
    wide = table("Wide", [(name, "int64") for name in names])
    row = list(range(70))
    add("wide70_permuted_repeated", [wide], [atom("wide", "Wide", [var(name) for name in names])],
        ["v69", "v0", "v69"], [("Wide", "insert", row), ("Wide", "insert", row),
                                  ("Wide", "insert", [value + 100 for value in row]), ("Wide", "delete", row)], "free_connex")

    for seed in range(4):
        rng = random.Random(SEED + 100 + seed)
        tables, atoms = triangle() if seed % 2 == 0 else (path_tables, path_atoms)
        ops = []
        for _ in range(48):
            source = rng.choice([value["name"] for value in tables])
            ops.append((source, rng.choice(("insert", "delete")), [rng.randrange(3), rng.randrange(3)]))
        add("seeded_" + str(seed), tables, atoms, ["x", "z"], ops,
            "cyclic" if seed % 2 == 0 else "acyclic_non_free_connex")
    return cases


def expected_profile(doc):
    query_class = classify(doc)
    reason = "contradiction" if doc["query"].get("contradiction", False) else {
        "cyclic": "cyclic_body", "acyclic_non_free_connex": "non_free_connex_head",
        "free_connex": "explicit_reference_choice"}[query_class]
    return {"backend": "exact_recompute_v1", "semantics": "exact_set", "query_class": query_class, "reason": reason,
            "update": "physical_full_row_set_events_with_exact_endpoint_deltas",
            "state": "sources_plus_materialized_distinct_answers_and_private_images",
            "startup": "eager_exact_recomputation_and_materialization",
            "delay": "materialized_output_no_constant_delay_claim", "termination": "owned_scratch_and_result_cleanup",
            "height": "no_CROWN_or_GHD_certificate"}


def snapshot(doc, state, sequence):
    result = python_query(doc, state)
    valid, sql = sqlite_state(doc, state)
    assert valid and result == sql, "independent original-CQ evaluators disagree"
    counts = [len(rows) for rows in state]
    ids = {source["name"]: i for i, source in enumerate(doc["catalog"]["tables"])}
    product, prefix = 1, 0
    for occurrence in doc["query"]["atoms"]:
        product *= counts[ids[occurrence["table"]]]
        prefix += product
    assert product <= MAX_U64 and prefix <= MAX_U64, "fixture must keep estimates exact"
    assignments = 0 if doc["query"].get("contradiction", False) else product
    outputs = (0 if assignments == 0 else 1) if not doc["query"]["head"] else assignments
    return {"sequence": sequence, "ready": True, "rows": relational.ordered(result),
            "source": [relational.ordered(rows) for rows in state], "has_answer": bool(result),
            "original_atoms": len(doc["query"]["atoms"]), "original_head": len(doc["query"]["head"]),
            "source_only_atoms": 0, "original_account": True,
            "explain": {"profile": expected_profile(doc), "table_rows": counts,
                        "witness_product": product, "prefix_product_sum": prefix, "result_rows": len(result)},
            "estimates": {"source_rows": sum(counts), "assignments_upper": assignments, "output_rows_upper": outputs,
                          "state_rows_upper": sum(counts) + outputs, "overflow": False, "advisory": True}}


def reference(request):
    doc = request["document"]
    tables = doc["catalog"]["tables"]
    state, sequence = [{} for _ in tables], 0
    initial = snapshot(doc, state, sequence)
    frames = []
    used = {occurrence["table"] for occurrence in doc["query"]["atoms"]}
    for event in request["events"]:
        assert event["sequence"] == sequence + 1
        row = [relational.canonical(value) for value in event["values"]]
        trial = [dict(rows) for rows in state]
        source = trial[event["table"]]
        old_present = relational.row_key(row) in source
        if event["op"] == "insert":
            source[relational.row_key(row)] = row
        else:
            source.pop(relational.row_key(row), None)
        changed = old_present != (event["op"] == "insert")
        valid = relational.python_constraints(tables, trial)
        sql_valid, _ = sqlite_state(doc, trial)
        assert valid == sql_valid, "independent full-source constraint checks disagree"
        before = python_query(doc, state)
        if valid:
            state, sequence = trial, sequence + 1
        after = python_query(doc, state)
        frames.append({"error": None if valid else "constraint_violation", "changed": changed,
                       "added": relational.ordered({key: after[key] for key in after.keys() - before.keys()}),
                       "removed": relational.ordered({key: before[key] for key in before.keys() - after.keys()}),
                       "recomputed": changed and tables[event["table"]]["name"] in used and not doc["query"].get("contradiction", False),
                       "snapshot": snapshot(doc, state, sequence)})
    return {"profile": expected_profile(doc), "initial": initial, "frames": frames}


def normalized_rows(rows):
    result = {relational.row_key(row): [relational.canonical(value) for value in row] for row in rows}
    assert len(result) == len(rows), "native endpoint contains duplicate projected rows"
    return relational.ordered(result)


def check_snapshot(actual, expected):
    actual = copy.deepcopy(actual)
    actual["rows"] = normalized_rows(actual["rows"])
    actual["source"] = [normalized_rows(rows) for rows in actual["source"]]
    assert actual == expected, (actual, expected)


def check_output(actual, expected, case_id):
    assert actual["id"] == case_id
    assert actual["profile"] == expected["profile"]
    check_snapshot(actual["initial"], expected["initial"])
    assert len(actual["trace"]) == len(expected["frames"])
    for index, (frame, want) in enumerate(zip(actual["trace"], expected["frames"])):
        try:
            event = frame["event"]
            assert event["error"] == want["error"]
            if want["error"] is None:
                assert event["changed"] == want["changed"]
                assert normalized_rows(event["added"]) == want["added"]
                assert normalized_rows(event["removed"]) == want["removed"]
                assert event["source_aliases"] == 0, "fallback source coordinator must not route original aliases"
                assert event["metrics"]["recomputed"] == want["recomputed"]
                assert event["metrics"]["added"] == len(want["added"])
                assert event["metrics"]["removed"] == len(want["removed"])
                assert event["metrics"]["outputs"] == len(want["snapshot"]["rows"])
            check_snapshot(frame["snapshot"], want["snapshot"])
        except AssertionError as error:
            raise AssertionError((case_id, "event", index, error.args)) from error


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    parser.add_argument("--artifacts", type=Path)
    args = parser.parse_args()
    cases = corpus()
    models = [reference(request) for request in cases]
    requests = []
    for indexed in (False, True):
        for request in cases:
            request = copy.deepcopy(request)
            request["id"] += "_indexed" if indexed else "_reference"
            request["indexed"] = indexed
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
    assert len(outputs) == len(requests), (len(outputs), len(requests))
    for index, (request, output) in enumerate(zip(requests, outputs)):
        check_output(output, models[index % len(cases)], request["id"])
    summary = {"status": "PASS", "seed": SEED, "cases": len(cases), "native_cases": len(requests),
               "events": sum(len(request["events"]) for request in requests),
               "images": sum(len(request["events"]) + 1 for request in requests),
               "source_backends": ["reference", "indexed"],
               "structural_classes": sorted({model["profile"]["query_class"] for model in models}),
               "oracle": "original full-CQ Python join and independent SQLite equality/constraint translation",
               "decimal": "canonical exact TEXT equality; no floating point or ordered/arithmetic comparison",
               "limits": "finite corpus correctness only; no CROWN/GHD or complexity proof"}
    if args.artifacts:
        (args.artifacts / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))


if __name__ == "__main__":
    main()
