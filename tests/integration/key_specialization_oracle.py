#!/usr/bin/env python3
"""Full original-CQ recomputation, independent of native key rewrite decisions."""
import argparse
from collections import Counter
import copy
import json
from pathlib import Path
import random
import sqlite3
import subprocess

SEED = 0xC70A02


def canonical(value):
    if isinstance(value, dict) and "decimal" in value:
        text = value["decimal"]
        negative = text.startswith("-")
        whole, _, fraction = text.lstrip("+-").partition(".")
        whole = whole.lstrip("0") or "0"
        fraction = fraction.rstrip("0")
        text = whole + ("." + fraction if fraction else "")
        return {"decimal": ("-" if negative and text != "0" else "") + text}
    return value


def key(value):
    return json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":"))


def row_key(row):
    return key([canonical(value) for value in row])


def ordered(rows):
    return [rows[name] for name in sorted(rows)]


def var(name):
    return {"var": name}


def const(value):
    return {"const": value}


IGNORE = {"ignore": True}


def table(name, columns):
    return {"name": name, "columns": [{"name": column, "type": kind} for column, kind in columns],
            "constraints": []}


def unique(name, columns, status="enforced"):
    return {"kind": "unique", "name": name, "columns": columns, "status": status}


def foreign(name, columns, target, referenced, status="enforced"):
    return {"kind": "foreign_key", "name": name, "columns": columns, "status": status,
            "references": {"table": target, "columns": referenced}}


def atom(name, source, terms):
    return {"id": name, "table": source, "terms": terms}


def document(tables, atoms, head, initial, seed):
    types = {}
    by_name = {value["name"]: value for value in tables}
    for occurrence in atoms:
        for term, column in zip(occurrence["terms"], by_name[occurrence["table"]]["columns"]):
            if "var" in term:
                old = types.setdefault(term["var"], column["type"])
                assert old == column["type"]
    names = list(types)
    random.Random(seed).shuffle(names)  # Force nontrivial original/new variable IDs.
    return {"schema_version": 3, "semantics": "set", "catalog": {"version": 1, "tables": tables},
            "query": {"variables": [{"name": name, "type": types[name]} for name in names],
                      "atoms": atoms, "head": [{"var": name} for name in head]},
            "initial": [{"table": name, "rows": rows} for name, rows in initial.items()]}


# These are full source sets. No optimizer/native projection participates in
# constraint acceptance or the materializing original-query definition below.
def python_constraints(tables, state):
    ids = {value["name"]: i for i, value in enumerate(tables)}
    positions = [{column["name"]: i for i, column in enumerate(value["columns"])} for value in tables]
    for table_id, source in enumerate(tables):
        for constraint in source.get("constraints", []):
            if constraint["status"] != "enforced":
                continue
            columns = [positions[table_id][name] for name in constraint["columns"]]
            projected = [tuple(key(row[column]) for column in columns) for row in state[table_id].values()]
            if constraint["kind"] == "unique":
                if len(projected) != len(set(projected)):
                    return False
            else:
                parent = ids[constraint["references"]["table"]]
                target = [positions[parent][name] for name in constraint["references"]["columns"]]
                keys = {tuple(key(row[column]) for column in target) for row in state[parent].values()}
                if any(value not in keys for value in projected):
                    return False
    return True


def python_query(doc, state):
    ids = {value["name"]: i for i, value in enumerate(doc["catalog"]["tables"])}
    assignments = [{}]
    for occurrence in doc["query"]["atoms"]:
        joined = []
        for assignment in assignments:
            for row in state[ids[occurrence["table"]]].values():
                candidate = dict(assignment)
                for term, value in zip(occurrence["terms"], row):
                    if "const" in term and key(canonical(term["const"])) != key(value):
                        break
                    if "var" in term:
                        name = term["var"]
                        if name in candidate and key(candidate[name]) != key(value):
                            break
                        candidate[name] = value
                else:
                    joined.append(candidate)
        assignments = joined
    result = {}
    for assignment in assignments:
        row = [assignment[field["var"]] for field in doc["query"]["head"]]
        result[row_key(row)] = row
    return result


def quote(name):
    return '"' + name.replace('"', '""') + '"'


def sql_value(value):
    if isinstance(value, dict):
        return value.get("date", value.get("decimal"))
    return value


# SQLite evaluates a separately translated original CQ and complete constraints.
# Decimal/date cells use canonical exact TEXT equality; this corpus performs no
# SQL arithmetic or ordering, so no floating conversion or affinity is needed.
def sqlite_state(doc, state):
    tables = doc["catalog"]["tables"]
    ids = {value["name"]: i for i, value in enumerate(tables)}
    with sqlite3.connect(":memory:") as db:
        for source, rows in zip(tables, state):
            columns = ",".join(quote(column["name"]) + (" INTEGER" if column["type"] in ("int64", "bool") else " TEXT COLLATE BINARY")
                               for column in source["columns"])
            db.execute("CREATE TABLE " + quote(source["name"]) + "(" + columns + ")")
            if rows:
                db.executemany("INSERT INTO " + quote(source["name"]) + " VALUES (" + ",".join("?" for _ in source["columns"]) + ")",
                               [[sql_value(value) for value in row] for row in rows.values()])
        valid = True
        for source in tables:
            for constraint in source.get("constraints", []):
                if constraint["status"] != "enforced":
                    continue
                name = quote(source["name"])
                columns = constraint["columns"]
                if constraint["kind"] == "unique":
                    if columns:
                        sql = "SELECT 1 FROM " + name + " GROUP BY " + ",".join(map(quote, columns)) + " HAVING count(*)>1 LIMIT 1"
                        bad = db.execute(sql).fetchone() is not None
                    else:
                        bad = db.execute("SELECT count(*) FROM " + name).fetchone()[0] > 1
                else:
                    parent = quote(constraint["references"]["table"])
                    equal = " AND ".join("c." + quote(a) + "=p." + quote(b)
                                         for a, b in zip(columns, constraint["references"]["columns"])) or "1"
                    sql = "SELECT 1 FROM " + name + " c WHERE NOT EXISTS (SELECT 1 FROM " + parent + " p WHERE " + equal + ") LIMIT 1"
                    bad = db.execute(sql).fetchone() is not None
                valid = valid and not bad
        aliases, conditions, parameters, bound = [], [], [], {}
        for index, occurrence in enumerate(doc["query"]["atoms"]):
            aliases.append(quote(occurrence["table"]) + " AS a" + str(index))
            source = tables[ids[occurrence["table"]]]
            for term, column in zip(occurrence["terms"], source["columns"]):
                field = "a" + str(index) + "." + quote(column["name"])
                if "const" in term:
                    conditions.append(field + "=?")
                    parameters.append(sql_value(canonical(term["const"])))
                elif "var" in term:
                    if term["var"] in bound:
                        conditions.append(field + "=" + bound[term["var"]])
                    else:
                        bound[term["var"]] = field
        head = doc["query"]["head"]
        select = ",".join(bound[value["var"]] for value in head) if head else "1"
        sql = "SELECT DISTINCT " + select + (" FROM " + ",".join(aliases) if aliases else "")
        if conditions:
            sql += " WHERE " + " AND ".join(conditions)
        types = {value["name"]: value["type"] for value in doc["query"]["variables"]}
        result = {}
        for raw in db.execute(sql, parameters):
            row = []
            for field, value in zip(head, raw):
                kind = types[field["var"]]
                row.append({"decimal": value} if kind == "decimal" else {"date": value} if kind == "date" else bool(value) if kind == "bool" else value)
            result[row_key(row)] = row
        return valid, result


def state_snapshot(doc, state, sequence):
    expected = python_query(doc, state)
    valid, sql = sqlite_state(doc, state)
    assert valid and expected == sql, "independent original-query definitions disagree"
    return {"sequence": sequence, "ready": True, "rows": ordered(expected),
            "source": [ordered(rows) for rows in state]}


def make_case(name, tables, atoms, head, initial, pool, prefix, removed, seed):
    doc = document(tables, atoms, head, initial, seed)
    ids = {value["name"]: i for i, value in enumerate(tables)}
    state = [{} for _ in tables]
    for source, rows in initial.items():
        for raw in rows:
            row = [canonical(value) for value in raw]
            state[ids[source]][row_key(row)] = row
    assert python_constraints(tables, state)
    expected_initial = state_snapshot(doc, state, 0)
    events, frames, sequence = [], [], 0
    rng = random.Random(seed)
    actions = list(prefix)
    for _ in range(40):
        source = rng.randrange(len(tables))
        actions.append((source, rng.choice(("insert", "delete")), copy.deepcopy(rng.choice(pool[source]))))
    for source, operation, raw in actions:
        row = [canonical(value) for value in raw]
        next_state = [dict(value) for value in state]
        present = row_key(row) in next_state[source]
        if operation == "insert":
            next_state[source][row_key(row)] = row
        else:
            next_state[source].pop(row_key(row), None)
        valid = python_constraints(tables, next_state)
        sql_valid, _ = sqlite_state(doc, next_state)
        assert valid == sql_valid, "independent constraint checks disagree"
        events.append({"sequence": sequence + 1, "table": source, "op": operation, "values": row})
        changed = present != (operation == "insert")
        error = None if valid else "constraint_violation"
        if valid:
            state = next_state
            sequence += 1
        frames.append({"error": error, "changed": changed and valid,
                       "snapshot": state_snapshot(doc, state, sequence)})
    return {"id": name, "document": doc, "events": events, "removed": removed}, {"initial": expected_initial, "frames": frames}


def corpus():
    result = []
    def add(name, tables, atoms, head, initial, pool, prefix=(), removed=1):
        result.append(make_case(name, tables, atoms, head, initial, pool, prefix, removed, SEED + len(result)))
    def base():
        p = table("p", [("id", "int64"), ("payload", "int64")])
        c = table("c", [("cid", "int64"), ("pid", "int64"), ("tag", "int64")])
        p["constraints"] = [unique("pk", ["id"])]
        c["constraints"] = [foreign("fk", ["pid"], "p", ["id"])]
        return [p, c]
    common = [atom("parent", "p", [var("pid"), var("private")]), atom("child", "c", [var("cid"), var("pid"), var("tag")])]
    pool = [[[7, 70], [7, 80], [8, 80]], [[1, 7, 9], [2, 7, 9], [3, 8, 10]]]
    prefix = [(0, "insert", [7, 70]), (1, "insert", [1, 7, 9]), (1, "insert", [1, 7, 9]),
              (1, "insert", [2, 7, 9]), (0, "delete", [7, 70]), (0, "insert", [7, 80]),
              (1, "delete", [1, 7, 9]), (0, "delete", [7, 70]), (1, "delete", [2, 7, 9]), (0, "delete", [7, 70])]
    add("private-payload-and-repeated-head", base(), common, ["tag", "pid", "tag"], {}, pool, prefix)
    add("boolean-head", base(), common, [], {}, pool, prefix)
    ignored = copy.deepcopy(common);ignored[0]["terms"][1] = IGNORE
    add("contained-scope", base(), ignored, ["tag"], {}, pool, prefix)
    untrusted = base();untrusted[1]["constraints"][0]["status"] = "untrusted"
    add("untrusted-dangling", untrusted, common, ["tag"], {}, pool, [(1, "insert", [1, 7, 9])], 0)
    hints = base();hints[1]["constraints"] = []
    hints[1]["key_hints"] = [{"columns": ["pid"], "reason": "guess"}]
    hints[1]["statistics"] = {"row_count": 1, "distinct_counts": [{"columns": ["pid"], "estimate": 1}]}
    add("statistics-and-hints", hints, common, ["tag"], {}, pool, [(1, "insert", [1, 7, 9])], 0)
    filtered = copy.deepcopy(common);filtered[0]["terms"][1] = const(70)
    add("parent-nonkey-constant", base(), filtered, ["tag"], {"p": [[7, 80]], "c": [[1, 7, 9]]}, pool, removed=0)
    add("parent-output", base(), common, ["tag", "pid", "private"], {}, pool, prefix, 0)
    literal = [atom("parent", "p", [const(7), IGNORE]), atom("child", "c", [IGNORE, const(7), var("tag")])]
    add("matching-key-literals", base(), literal, ["tag"], {"p": [[8, 80]], "c": [[3, 8, 10]]}, pool)
    mismatch = copy.deepcopy(literal);mismatch[1]["terms"][1] = var("pid")
    add("mismatched-key-literal", base(), mismatch, ["tag"], {"p": [[8, 80]], "c": [[3, 8, 10]]}, pool, removed=0)
    wildcard = [atom("parent", "p", [var("x"), IGNORE]), atom("child", "c", [var("x"), IGNORE, var("tag")])]
    add("wildcard-is-not-equality", base(), wildcard, ["tag"], {"p": [[7, 70]], "c": [[1, 7, 9]]}, pool, removed=0)
    repeated = base();repeated[0]["columns"].append({"name": "other", "type": "int64"})
    repeat_atoms = [atom("parent", "p", [var("pid"), var("z"), var("z")]), common[1]]
    repeat_pool = [[[7, 70, 80], [7, 70, 70], [8, 80, 80]], pool[1]]
    add("repeated-private-target", repeated, repeat_atoms, ["tag"], {"p": [[7, 70, 80]], "c": [[1, 7, 9]]}, repeat_pool, removed=0)
    external = base() + [table("t", [("value", "int64")])]
    external_atoms = common + [atom("filter", "t", [var("private")])]
    add("target-payload-joins-other-atom", external, external_atoms, ["tag"],
        {"p": [[7, 70]], "c": [[1, 7, 9]], "t": [[99]]}, pool + [[[70], [80], [99]]], removed=0)
    equal = [table("p", [("a", "int64"), ("b", "int64")]), table("c", [("a", "int64"), ("b", "int64")])]
    equal[0]["constraints"] = [unique("pk", ["b", "a"])]
    equal[1]["constraints"] = [foreign("fk", ["b", "a"], "p", ["b", "a"])]
    equal_atoms = [atom("parent", "p", [var("x"), var("y")]), atom("child", "c", [var("x"), var("y")])]
    add("equal-scopes", equal, equal_atoms, ["x", "y"], {}, [[[1, 2], [3, 3]], [[1, 2], [3, 3]]])
    repeat_keys = copy.deepcopy(equal_atoms)
    for item in repeat_keys:item["terms"][1] = var("x")
    add("matching-repeated-key", equal, repeat_keys, ["x"], {"p": [[1, 2]], "c": [[1, 2]]}, [[[1, 2], [3, 3]], [[1, 2], [3, 3]]])
    bad_repeat = copy.deepcopy(repeat_keys);bad_repeat[1]["terms"][1] = var("y")
    add("unproved-key-repeat", equal, bad_repeat, ["x"], {"p": [[1, 2]], "c": [[1, 2]]}, [[[1, 2], [3, 3]], [[1, 2], [3, 3]]], removed=0)
    unit = [table("p", [("payload", "int64")]), table("c", [("tag", "int64")])]
    unit[0]["constraints"] = [unique("unit", [])];unit[1]["constraints"] = [foreign("unit_fk", [], "p", [])]
    add("empty-key-unit", unit, [atom("parent", "p", [IGNORE]), atom("child", "c", [var("t")])], ["t"], {}, [[[7], [8]], [[9], [10]]], [(1, "insert", [9]), (0, "insert", [7])])
    self_table = table("e", [("id", "int64"), ("parent", "int64")])
    self_table["constraints"] = [unique("pk", ["id"]), foreign("self", ["parent"], "e", ["id"])]
    self_atoms = [atom("parent", "e", [var("p"), IGNORE]), atom("child", "e", [var("id"), var("p")])]
    add("self-fk-alias", [self_table], self_atoms, ["id"], {}, [[[1, 1], [2, 1], [2, 2]]], [(0, "insert", [1, 1]), (0, "insert", [2, 1]), (0, "delete", [1, 1])])
    cycle = base();cycle[1]["constraints"].append(unique("cid", ["cid"]))
    cycle[0]["constraints"].append(foreign("back", ["payload"], "c", ["cid"]))
    add("cyclic-fk-catalog", cycle, common, ["tag"], {"p": [[7, 1]], "c": [[1, 7, 9]]},
        [[[7, 1], [8, 1], [9, 2]], [[1, 7, 9], [2, 7, 10], [2, 8, 10]]], [(0, "delete", [7, 1]), (1, "delete", [1, 7, 9])])
    chain = base() + [table("g", [("id", "int64"), ("payload", "int64")])]
    chain[0]["constraints"].append(foreign("to_g", ["payload"], "g", ["id"]))
    chain[2]["constraints"] = [unique("g_pk", ["id"])]
    chain_atoms = [atom("g", "g", [var("z"), var("g_private")]),
                   atom("p", "p", [var("pid"), var("z")]), common[1]]
    add("chain-live-anchor-and-compaction", chain, chain_atoms, ["tag", "pid", "tag"],
        {"g": [[100, 70]], "p": [[7, 100]], "c": [[1, 7, 9]]},
        [[[7, 100], [8, 101]], pool[1], [[100, 70], [101, 80]]],
        [(2, "insert", [101, 80]), (0, "insert", [8, 101]), (2, "delete", [101, 80]), (0, "delete", [8, 101])], 2)
    unused = base() + [table("unused", [("id", "int64")])]
    unused[2]["constraints"] = [foreign("unused_fk", ["id"], "p", ["id"])]
    add("unused-source-enforcement", unused, common, ["tag"], {}, pool + [[[7], [8]]],
        [(0, "insert", [7, 70]), (2, "insert", [7]), (0, "delete", [7, 70]), (2, "delete", [7]), (0, "delete", [7, 70])])
    aliases = base();aliases[1]["columns"] = [{"name": "left", "type": "int64"}, {"name": "right", "type": "int64"}, {"name": "tag", "type": "int64"}]
    aliases[1]["constraints"] = [foreign("left", ["left"], "p", ["id"]), foreign("right", ["right"], "p", ["id"])]
    alias_atoms = [atom("left", "p", [var("a"), IGNORE]), atom("right", "p", [var("b"), IGNORE]), atom("child", "c", [var("a"), var("b"), var("t")])]
    add("same-table-parent-aliases", aliases, alias_atoms, ["t"], {"p": [[7, 70], [8, 80]], "c": [[7, 8, 9]]},
        [pool[0], [[7, 8, 9], [7, 7, 10], [8, 8, 11]]], removed=2)
    typed = [table("p", [("a", "int64"), ("b", "string"), ("c", "bool"), ("d", "date"), ("e", "decimal")]),
             table("c", [("b", "string"), ("e", "decimal"), ("a", "int64"), ("d", "date"), ("c", "bool"), ("tag", "int64")])]
    typed[0]["constraints"] = [unique("pk", ["e", "a", "b", "d", "c"])]
    typed[1]["constraints"] = [foreign("fk", ["b", "e", "a", "d", "c"], "p", ["b", "e", "a", "d", "c"])]
    p1 = [-(1 << 63), "a\0z", False, {"date": "2000-02-29"}, {"decimal": "1.00"}]
    p2 = [(1 << 63) - 1, "é😀", True, {"date": "9999-12-31"}, {"decimal": "-99999999999999999999999999999999999999"}]
    def child(row, tag):return [row[1], row[4], row[0], row[3], row[2], tag]
    typed_atoms = [atom("parent", "p", [var(name) for name in ("a", "b", "c", "d", "e")]),
                   atom("child", "c", [var(name) for name in ("b", "e", "a", "d", "c", "tag")])]
    add("mixed-reordered-exact-keys", typed, typed_atoms, ["tag", "a", "b", "c", "d", "e"], {}, [[p1, p2], [child(p1, 9), child(p2, 10)]],
        [(0, "insert", p1), (1, "insert", child(p1, 9)), (0, "insert", p2), (1, "insert", child(p2, 10))])
    return result


def compare_snapshot(actual, expected):
    assert actual["sequence"] == expected["sequence"] and actual["ready"]
    assert {row_key(row) for row in actual["rows"]} == {row_key(row) for row in expected["rows"]}
    assert len(actual["source"]) == len(expected["source"])
    for a, b in zip(actual["source"], expected["source"]):
        assert {row_key(row) for row in a} == {row_key(row) for row in b}


def receive(actual, request, expected):
    doc = request["document"]
    assert actual["id"] == request["id"] and actual["source_catalog_preserved"] and actual["general_unchanged"]
    assert len(actual["eliminations"]) == request["removed"]
    assert actual["specialized"] == (request["removed"] > 0)
    assert actual["general_atoms"] - actual["execution_atoms"] == request["removed"]
    live = set(range(len(doc["query"]["atoms"])))
    for rule in actual["eliminations"]:
        assert rule["removed"] in live and rule["witness"] in live and rule["removed"] != rule["witness"]
        live.remove(rule["removed"])
    assert set(actual["occurrences"]) == live and len(actual["occurrences"]) == len(live)
    variables = doc["query"]["variables"]
    assert len(set(actual["variables"])) == len(actual["variables"])
    assert all(0 <= old < len(variables) for old in actual["variables"])
    original_ids = {value["name"]: index for index, value in enumerate(variables)}
    assert actual["head_original"] == [original_ids[value["var"]] for value in doc["query"]["head"]]
    assert actual["reduced_certificate_valid"] == actual["specialized"]
    assert not actual["original_certificate_valid"]
    for route in ("general", "execution"):compare_snapshot(actual["initial"][route], expected["initial"])
    assert len(actual["trace"]) == len(expected["frames"])
    tables = doc["catalog"]["tables"]
    table_ids = {value["name"]: index for index, value in enumerate(tables)}
    constraints = any(value["status"] == "enforced" for source in tables for value in source.get("constraints", []))
    for event, frame, want in zip(request["events"], actual["trace"], expected["frames"]):
        for route in ("general", "execution"):
            outcome = frame[route + "_event"]
            assert outcome["error"] == want["error"]
            compare_snapshot(frame[route], want["snapshot"])
            if outcome["error"] is None:
                metrics = outcome["metrics"]
                occurrences = range(len(doc["query"]["atoms"])) if route == "general" else actual["occurrences"]
                visits = sum(table_ids[doc["query"]["atoms"][old]["table"]] == event["table"] for old in occurrences)
                assert metrics["source_changes"] == int(want["changed"])
                assert metrics["aliases_visited"] == (visits if want["changed"] else 0)
                assert metrics["constraint_validations"] == int(want["changed"] and constraints)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True, type=Path)
    parser.add_argument("--artifacts", type=Path)
    args = parser.parse_args()
    cases = corpus()
    requests, expected = [], []
    for request, want in cases:
        for indexed in (False, True):
            item = copy.deepcopy(request)
            item["id"] += "-indexed" if indexed else "-reference"
            item["indexed"] = indexed
            requests.append(item);expected.append(want)
    wire = "".join(key(request) + "\n" for request in requests)
    if args.artifacts:
        args.artifacts.mkdir(parents=True)
        (args.artifacts / "native-request.jsonl").write_text(wire)
        (args.artifacts / "expected.json").write_text(json.dumps(expected, ensure_ascii=False, indent=2) + "\n")
        (args.artifacts / "case-catalog.json").write_text(json.dumps([{"id": request["id"], "removed": request["removed"], "document": request["document"]} for request in requests], ensure_ascii=False, indent=2) + "\n")
    native = subprocess.run([str(args.driver.resolve())], input=wire, text=True, capture_output=True, check=False)
    if args.artifacts:
        (args.artifacts / "native.stdout").write_text(native.stdout)
        (args.artifacts / "native.stderr").write_text(native.stderr)
    assert native.returncode == 0, (native.returncode, native.stderr)
    outputs = [json.loads(line) for line in native.stdout.splitlines()]
    assert len(outputs) == len(requests)
    for actual, request, want in zip(outputs, requests, expected):
        try:receive(actual, request, want)
        except AssertionError as failure:raise AssertionError(request["id"]) from failure
    frames = sum(len(value["frames"]) for value in expected)
    rejections = sum(frame["error"] is not None for value in expected for frame in value["frames"])
    summary = {"status": "PASS_independent_original_CQ_constraints_and_key_routes", "queries": len(cases),
               "native_cases": len(requests), "source_events": frames, "snapshots_per_route": frames + len(requests),
               "expected_constraint_rejections": rejections, "storage_backends": 2,
               "oracle": "original-CQ Python full-state joins plus independent SQLite query/constraint checks",
               "sqlite_version": sqlite3.sqlite_version, "semantics": "non-null exact physical sets"}
    if args.artifacts:(args.artifacts / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))


if __name__ == "__main__":
    main()
