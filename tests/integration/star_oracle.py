#!/usr/bin/env python3
"""Literal star snapshots against original-CQ full joins and independent SQLite."""
import argparse
import copy
import itertools
import json
from pathlib import Path
import random
import sqlite3
import subprocess

# These existing reference helpers evaluate arbitrary complete original CQs and
# constraints. They import no native planner, star partition or cursor logic.
import key_specialization_oracle as relational

SEED = 0x6803C0


def sqlite_original(request, state):
    doc = request["document"]
    if len(doc["query"]["atoms"]) <= 60:
        return relational.sqlite_state(doc, state)
    # SQLite limits a flat join to64 tables. The wide fixture keeps the exact
    # original center/unary CQ but translates each unary atom as an existential
    # subquery. This uses no production partition/H/group state and avoids
    # weakening the admitted native family to fit the reference engine's cap.
    tables = doc["catalog"]["tables"]
    assert not any(source.get("constraints", []) for source in tables)
    assert all(column["type"] == "int64" for source in tables for column in source["columns"])
    ids = {source["name"]: i for i, source in enumerate(tables)}
    center = doc["query"]["atoms"][request["center"]]
    central_schema = tables[ids[center["table"]]]
    bound = {term["var"]: "c." + relational.quote(column["name"])
             for term, column in zip(center["terms"], central_schema["columns"])}
    with sqlite3.connect(":memory:") as database:
        for source, rows in zip(tables, state):
            database.execute("CREATE TABLE " + relational.quote(source["name"]) + "(" +
                             ",".join(relational.quote(column["name"]) + " INTEGER" for column in source["columns"]) + ")")
            if rows:
                database.executemany("INSERT INTO " + relational.quote(source["name"]) + " VALUES (" +
                                     ",".join("?" for _ in source["columns"]) + ")", rows.values())
        predicates = []
        for index, occurrence in enumerate(doc["query"]["atoms"]):
            if index == request["center"]:
                continue
            source = tables[ids[occurrence["table"]]]
            assert len(source["columns"]) == len(occurrence["terms"]) == 1
            predicates.append("EXISTS(SELECT 1 FROM " + relational.quote(source["name"]) + " s WHERE s." +
                              relational.quote(source["columns"][0]["name"]) + "=" + bound[occurrence["terms"][0]["var"]] + ")")
        head = doc["query"]["head"]
        sql = "SELECT DISTINCT " + (",".join(bound[field["var"]] for field in head) if head else "1")
        sql += " FROM " + relational.quote(center["table"]) + " c"
        if predicates:
            sql += " WHERE " + " AND ".join(predicates)
        answer = {}
        for record in database.execute(sql):
            row = list(record) if head else []
            answer[relational.row_key(row)] = row
        return True, answer


def make_case(name, kinds, head, operations, seed, satellites=None, constraints=None, unused=False):
    d = len(kinds)
    satellites = list(range(d)) if satellites is None else satellites
    names = ["x" + str(i) for i in range(d)]
    tables = [relational.table("central", [(names[i], kinds[i]) for i in range(d)])]
    atoms = [relational.atom("central_occurrence", "central", [relational.var(value) for value in names])]
    for i in satellites:
        source = "filter" + str(i)
        tables.append(relational.table(source, [("key", kinds[i])]))
        atoms.append(relational.atom("filter_occurrence" + str(i), source, [relational.var(names[i])]))
    if unused:
        tables.append(relational.table("unused", [("key", "int64")]))
    for source, items in (constraints or {}).items():
        next(value for value in tables if value["name"] == source)["constraints"] = items
    rng = random.Random(seed)
    rng.shuffle(tables)
    rng.shuffle(atoms)
    doc = relational.document(tables, atoms, [names[i] for i in head], {}, seed)
    source_ids = {source["name"]: i for i, source in enumerate(tables)}
    center = next(i for i, atom in enumerate(atoms) if atom["table"] == "central")
    request = {"id": name, "document": doc, "center": center, "events": []}
    sequence = 0
    state = [dict() for _ in tables]
    for operation in operations:
        source, sign, values = operation[:3]
        event = {"sequence": sequence + 1, "table": source_ids[source], "op": sign, "values": values}
        if len(operation) == 4:
            event["expect"] = operation[3]
        proposed = copy.deepcopy(state)
        identity = relational.row_key(values)
        if sign == "insert":
            proposed[source_ids[source]][identity] = [relational.canonical(value) for value in values]
        else:
            proposed[source_ids[source]].pop(identity, None)
        if relational.python_constraints(tables, proposed):
            state = proposed
            sequence += 1
        request["events"].append(event)
    return request


def corpus():
    result = []
    for index, head in enumerate(([2], [1, 2], [0, 1, 2], [], [2, 2], [2, 0])):
        operations = [("central", "insert", list(row)) for row in
                      ((1, 10, 100), (2, 10, 100), (2, 20, 200), (3, 30, 300))]
        operations += [("filter0", "insert", [x]) for x in (1, 2)]
        operations += [("filter1", "insert", [x]) for x in (10, 20)]
        operations += [("filter2", "insert", [x]) for x in (100, 200)]
        operations += [("central", "insert", [4, 40, 400]), ("filter0", "insert", [4]),
                       ("filter1", "insert", [40]), ("filter2", "insert", [400]),
                       ("central", "delete", [1, 10, 100]), ("filter0", "delete", [2]),
                       ("filter0", "insert", [3]), ("filter1", "insert", [30]),
                       ("filter2", "insert", [300]), ("filter1", "delete", [40]),
                       ("filter2", "delete", [300]), ("filter0", "insert", [2]),
                       ("central", "delete", [2, 10, 100]), ("central", "insert", [2, 20, 200]),
                       ("filter2", "delete", [999]), ("filter1", "insert", [40]),
                       ("filter0", "delete", [4]), ("filter1", "delete", [20])]
        result.append(make_case("every-relation-head-" + str(index), ["int64"] * 3, head,
                                operations, SEED + index))
    cube = [("filter" + str(i), "insert", [value]) for i in range(3) for value in (1, 2, 3)]
    for side in (1, 2, 3):
        cube += [("central", "insert", list(value)) for value in itertools.product(range(1, side + 1), repeat=3)
                 if max(value) == side]
    cube += [("central", "delete", [3, 3, 3]), ("central", "insert", [3, 3, 3])]
    cube += [("central", "delete", list(value)) for value in itertools.product((1, 2, 3), repeat=3) if max(value) == 3]
    cube += [("central", "delete", [2, 2, 2]), ("central", "insert", [2, 2, 2])]
    result.append(make_case("generalized-h-cubes", ["int64"] * 3, [2], cube, SEED + 10))
    heavy = [("filter0", "insert", [7])]
    for i in range(1, 65):
        heavy += [("filter1", "insert", [i]), ("filter2", "insert", [i]), ("central", "insert", [7, i, i])]
    heavy += [("filter0", "delete", [7], {"center_visits": 0, "group_visits": 1}),
              ("filter0", "insert", [7], {"center_visits": 0, "group_visits": 1}),
              ("filter1", "delete", [8], {"center_visits": 1}), ("filter1", "insert", [8], {"center_visits": 1})]
    heavy += [("central", "delete", [7, i, i]) for i in range(64, 0, -1)]
    result.append(make_case("sparse-high-degree-heavy-light", ["int64"] * 3, [], heavy, SEED + 11))
    cross = [("filter0", "insert", [7]), ("filter0", "insert", [8]), ("filter2", "insert", [0])]
    for i in range(1, 17):
        cross += [("filter1", "insert", [i]), ("central", "insert", [7, i, 0])]
    cross += [("filter1", "insert", [999]), ("central", "insert", [8, 999, 0]),
              ("filter0", "delete", [7]), ("filter0", "delete", [8]),
              ("filter0", "insert", [8]), ("filter0", "insert", [7]),
              ("central", "delete", [8, 999, 0]), ("filter0", "delete", [7]),
              ("central", "insert", [8, 999, 0]), ("filter0", "insert", [7])]
    result.append(make_case("cross-mask-last-witness", ["int64"] * 3, [2, 2], cross, SEED + 12))
    no_filter = [("filter0", "insert", [1]), ("filter1", "insert", [2]),
                 ("central", "insert", [1, 2, 3]), ("central", "insert", [1, 2, 4]),
                 ("unused", "insert", [88]), ("unused", "delete", [88]), ("filter0", "delete", [1])]
    result.append(make_case("free-unfiltered-coordinate-unused-source", ["int64"] * 3, [2], no_filter,
                            SEED + 13, satellites=[0, 1], unused=True))
    constraints = {"filter0": [relational.unique("pk", ["key"])],
                   "central": [relational.foreign("fk", ["x0"], "filter0", ["key"])]}
    constrained = [("central", "insert", [7, 8]), ("filter0", "insert", [7]),
                   ("central", "insert", [7, 8]), ("filter0", "delete", [7]),
                   ("filter1", "insert", [8]), ("central", "delete", [7, 8]),
                   ("filter0", "delete", [7])]
    result.append(make_case("source-constraint-rejection", ["int64"] * 2, [1], constrained, SEED + 14,
                            constraints=constraints))
    typed_rows = [(-(1 << 63), "a\0b", {"decimal": "0.10"}, {"date": "0001-01-01"}, False),
                  ((1 << 63)-1, "é", {"decimal": "0.00000000000000000001"}, {"date": "9999-12-31"}, True),
                  (9007199254740993, "a\0b", {"decimal": "0.1"}, {"date": "0001-01-01"}, False)]
    typed = []
    for values in typed_rows:
        typed.extend(("filter" + str(i), "insert", [value]) for i, value in enumerate(values))
        typed.append(("central", "insert", list(values)))
    typed += [("central", "delete", list(typed_rows[0])), ("filter1", "delete", ["a\0b"]),
              ("filter1", "insert", ["a\0b"])]
    result.append(make_case("exact-scalar-and-projection-collisions", ["int64", "string", "decimal", "date", "bool"],
                            [4, 1, 2, 1], typed, SEED + 15))
    for run, d in enumerate((2, 3, 4)):
        rng = random.Random(SEED + 30 + run)
        operations = []
        for _ in range(90):
            source = rng.randrange(d + 1)
            values = [rng.randrange(5) for _ in range(d if source == 0 else 1)]
            operations.append(("central" if source == 0 else "filter" + str(source-1),
                               "insert" if rng.randrange(2) else "delete", values))
        result.append(make_case("seeded-original-cq-" + str(d), ["int64"] * d, [d-1, 0, d-1], operations,
                                SEED + 30 + run))
    wide = [("filter" + str(i), "insert", [i]) for i in range(70)]
    wide += [("central", "insert", list(range(70))), ("filter69", "delete", [69]),
             ("filter69", "insert", [69]), ("central", "delete", list(range(70)))]
    result.append(make_case("seventy-coordinate-star", ["int64"] * 70, [69, 0, 69], wide, SEED + 99))
    return result


def expected_snapshot(request, state, sequence):
    doc = request["document"]
    valid, sqlite_rows = sqlite_original(request, state)
    assert valid
    rows = relational.python_query(doc, state)
    assert rows == sqlite_rows, (request["id"], "independent reference disagreement")
    tables = doc["catalog"]["tables"]
    center_atom = doc["query"]["atoms"][request["center"]]
    center = next(i for i, source in enumerate(tables) if source["name"] == center_atom["table"])
    degrees = []
    for coordinate in range(len(center_atom["terms"])):
        frequency = {}
        for row in state[center].values():
            identity = relational.key(row[coordinate])
            frequency[identity] = frequency.get(identity, 0) + 1
        d = len(center_atom["terms"])
        h = max((r for r in range(1, len(frequency)+1)
                 if sum(count >= r ** (d-1) for count in frequency.values()) >= r), default=0)
        degrees.append({"h": h, "keys": len(frequency)})
    return {"sequence": sequence, "rows": rows, "source": copy.deepcopy(state),
            "center_rows": len(state[center]), "dimensions": degrees}


def reference(request):
    tables = request["document"]["catalog"]["tables"]
    state = [dict() for _ in tables]
    sequence = 0
    initial = expected_snapshot(request, state, sequence)
    trace = []
    for event in request["events"]:
        proposed = copy.deepcopy(state)
        key = relational.row_key(event["values"])
        changed = key not in proposed[event["table"]] if event["op"] == "insert" else key in proposed[event["table"]]
        if event["op"] == "insert":
            proposed[event["table"]][key] = [relational.canonical(value) for value in event["values"]]
        else:
            proposed[event["table"]].pop(key, None)
        python_valid = relational.python_constraints(tables, proposed)
        sqlite_valid, _ = sqlite_original(request, proposed)
        assert python_valid == sqlite_valid
        error = None
        if event["sequence"] != sequence + 1:
            error = "invalid_sequence"
        elif not python_valid:
            error = "constraint_violation"
        if error is None:
            sequence += 1
            state = proposed
        trace.append({"error": error, "changed": changed, "snapshot": expected_snapshot(request, state, sequence)})
    return initial, trace


def compare_snapshot(actual, expected, request):
    assert actual["ready"] and actual["sequence"] == expected["sequence"]
    assert {relational.row_key(row): row for row in actual["rows"]} == expected["rows"]
    assert len(actual["rows"]) == len(expected["rows"])
    assert [{relational.row_key(row): row for row in table} for table in actual["source"]] == expected["source"]
    assert actual["center_rows"] == expected["center_rows"]
    for actual_dimension, expected_dimension in zip(actual["dimensions"], expected["dimensions"]):
        assert actual_dimension["h"] == expected_dimension["h"]
        assert actual_dimension["keys"] == expected_dimension["keys"]
    center = request["document"]["query"]["atoms"][request["center"]]
    free = {field["var"] for field in request["document"]["query"]["head"]}
    quantum = 1
    for term, dimension in zip(center["terms"], actual["dimensions"]):
        if term["var"] not in free:
            quantum *= 1 + dimension["heavy_keys"]
    quantum = min(actual["center_rows"], quantum) if actual["center_rows"] else 1
    assert actual["cursor"]["candidate_quantum"] == quantum
    assert actual["cursor"]["outputs"] == len(expected["rows"])


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True, type=Path)
    parser.add_argument("--artifacts", type=Path)
    args = parser.parse_args()
    requests, expected = [], []
    for request in corpus():
        want = reference(request)
        for indexed in (False, True):
            item = copy.deepcopy(request)
            item["indexed"] = indexed
            item["id"] += "-indexed" if indexed else "-reference"
            requests.append(item)
            expected.append(want)
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
            doc = request["document"]
            assert actual["dimension"] == len(doc["query"]["atoms"][request["center"]]["terms"])
            assert actual["distinct_head"] == len({field["var"] for field in doc["query"]["head"]})
            assert actual["original_atoms"] == len(doc["query"]["atoms"]) and actual["source_only_atoms"] == 0
            compare_snapshot(actual["initial"], initial, request)
            assert len(actual["trace"]) == len(trace)
            for event, frame, want in zip(request["events"], actual["trace"], trace):
                assert frame["event"]["error"] == want["error"]
                compare_snapshot(frame["snapshot"], want["snapshot"], request)
                if want["error"] is None:
                    assert frame["event"]["changed"] == want["changed"]
                    assert frame["event"]["metrics"]["generic_aliases"] == 0
                    assert frame["event"]["metrics"]["generic_crossings"] == 0
                    for metric, value in event.get("expect", {}).items():
                        assert frame["event"]["metrics"][metric] == value
        except AssertionError as failure:
            raise AssertionError(request["id"]) from failure
    summary = {"status": "PASS_literal_star_original_CQ_A04_independent_models", "native_cases": len(requests),
               "source_events": sum(len(request["events"]) for request in requests), "backends": 2,
               "oracle": "original full-state CQ joins and constraints, independently translated SQLite, exact integer generalized H",
               "sqlite_version": sqlite3.sqlite_version}
    if args.artifacts:
        (args.artifacts / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))


if __name__ == "__main__":
    main()
