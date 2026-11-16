#!/usr/bin/env python3
"""Slow, independent weighted-subtree oracle for line-oriented JSON fixtures.

Design reference: Refactor.md section 10.2 and docs/weighted_messages.md.

This is a test oracle, not production code. It recursively enumerates complete
compatible assignments of native input tuples for every subtree, multiplying
each native tuple weight once, then aggregates those assignments to node scopes
and parent separators. The explicit Cartesian joins can grow exponentially in
the number of native rows; this implementation has no performance authority.

Usage:
    python3 tests/reference/weighted_oracle.py < cases.jsonl
    python3 tests/reference/weighted_oracle.py --self-test

Input lines contain one JSON object each. `nodes` is indexed by list position;
each node has `kind` (`native` or `generalized`), an ordered integer `scope`,
and child node indices. `inputs` is parallel to `nodes`: a native node gets a
list of `{row: [...], weight: decimal-string-or-integer}` objects, and a
generalized node gets an empty list. `root` is a node index or null. A child's
parent separator is the intersection of its scope with its parent's scope,
ordered as in the child scope. Generalized nodes require every child's parent
separator to equal the generalized node's full scope.

The `tree` route evaluates the supplied tree. `constant_true` and
`constant_false` bypass it and return root counts 1 and 0 respectively.
Counts (`local`, `subtree`, cached values, message values, and `root_count`) are
decimal strings so Python integers remain exact across JSON consumers. Scalar
row values use canonical JSON value equality; JSON booleans, integers, and
floats therefore remain distinct.

Failure contract: an invalid input raises `ValueError` (or JSON decoding
error). In CLI mode the offending line is reported to stderr and the process
exits with status 2; that line produces no output record. Earlier valid lines
may already have been written.
"""

from __future__ import annotations

import json
import math
import re
import sys
from collections import defaultdict
from typing import Any


def _json_scalar_key(value: Any) -> str:
    """Return a stable, type-sensitive key for a JSON scalar value."""
    if value is None or type(value) in (bool, int, str):
        return json.dumps(value, ensure_ascii=False, separators=(",", ":"))
    if type(value) is float and math.isfinite(value):
        return json.dumps(value, ensure_ascii=False, separators=(",", ":"), allow_nan=False)
    raise ValueError(f"row values must be finite JSON scalars, got {value!r}")


def _parse_weight(value: Any) -> int:
    if type(value) is int:
        weight = value
    elif isinstance(value, str) and re.fullmatch(r"[+-]?[0-9]+", value):
        weight = int(value, 10)
    else:
        raise ValueError(f"weight must be an integer or decimal string, got {value!r}")
    if weight < 0:
        raise ValueError(f"weight must be nonnegative, got {weight}")
    return weight


def _count_text(count: int) -> str:
    return str(count)


def _row_values(keys: tuple[str, ...]) -> list[Any]:
    return [json.loads(key) for key in keys]


def _merge_assignments(left: dict[int, str], right: dict[int, str]) -> dict[int, str] | None:
    merged = left.copy()
    for variable, value in right.items():
        previous = merged.get(variable)
        if previous is not None and previous != value:
            return None
        # JSON null is encoded as the nonempty string "null", so .get() above
        # safely distinguishes an absent variable from any present value.
        merged[variable] = value
    return merged


def _validate_tree(obj: dict[str, Any]) -> tuple[list[dict[str, Any]], list[list[Any]], int | None,
                                                  list[int | None], list[list[int]]]:
    if "nodes" not in obj or "root" not in obj or "inputs" not in obj:
        raise ValueError("tree route requires nodes, root, and inputs")
    raw_nodes = obj["nodes"]
    raw_inputs = obj["inputs"]
    root = obj["root"]
    if not isinstance(raw_nodes, list) or not isinstance(raw_inputs, list):
        raise ValueError("nodes and inputs must be arrays")
    if len(raw_inputs) != len(raw_nodes):
        raise ValueError("inputs must have one entry per node, in node-index order")
    n = len(raw_nodes)
    if root is not None and (type(root) is not int or root < 0 or root >= n):
        raise ValueError(f"root must be null or a valid node index, got {root!r}")
    if root is None and n:
        raise ValueError("a nonempty tree must have a root node")

    nodes: list[dict[str, Any]] = []
    parents: list[int | None] = [None] * n
    scopes: list[list[int]] = []
    for node_id, raw in enumerate(raw_nodes):
        if not isinstance(raw, dict):
            raise ValueError(f"node {node_id} must be an object")
        kind = raw.get("kind")
        if kind not in ("native", "generalized"):
            raise ValueError(f"node {node_id} has unknown kind {kind!r}")
        scope = raw.get("scope")
        children = raw.get("children")
        if not isinstance(scope, list) or any(type(v) is not int for v in scope):
            raise ValueError(f"node {node_id} scope must be an array of integer variables")
        if len(set(scope)) != len(scope):
            raise ValueError(f"node {node_id} scope contains duplicate variables")
        if not isinstance(children, list) or any(type(c) is not int for c in children):
            raise ValueError(f"node {node_id} children must be an array of node indices")
        if len(set(children)) != len(children):
            raise ValueError(f"node {node_id} lists a child more than once")
        if any(child < 0 or child >= n for child in children):
            raise ValueError(f"node {node_id} has an out-of-range child index")
        nodes.append({"kind": kind, "scope": scope.copy(), "children": children.copy()})
        scopes.append(scope.copy())
        for child in children:
            if parents[child] is not None:
                raise ValueError(f"node {child} has more than one parent")
            parents[child] = node_id

    if root is not None and parents[root] is not None:
        raise ValueError("root node must not have a parent")
    if root is not None:
        visited: set[int] = set()

        def visit(node_id: int, active: set[int]) -> None:
            if node_id in active:
                raise ValueError("node edges contain a cycle")
            if node_id in visited:
                return
            active.add(node_id)
            visited.add(node_id)
            for child in nodes[node_id]["children"]:
                visit(child, active)
            active.remove(node_id)

        visit(root, set())
        if len(visited) != n:
            raise ValueError("all nodes must be reachable from root")

    separators: list[list[int]] = [[] for _ in range(n)]
    for node_id, parent_id in enumerate(parents):
        if parent_id is not None:
            parent_scope = set(scopes[parent_id])
            separators[node_id] = [v for v in scopes[node_id] if v in parent_scope]
            if nodes[parent_id]["kind"] == "generalized" and set(separators[node_id]) != set(scopes[parent_id]):
                raise ValueError(
                    f"child {node_id} separator must equal generalized parent {parent_id} scope"
                )

    native_rows: list[list[tuple[tuple[str, ...], int]]] = []
    for node_id, node in enumerate(nodes):
        supplied = raw_inputs[node_id]
        if not isinstance(supplied, list):
            raise ValueError(f"inputs[{node_id}] must be an array")
        if node["kind"] == "generalized":
            if supplied:
                raise ValueError(f"generalized node {node_id} must have no local input rows")
            native_rows.append([])
            continue
        aggregate: dict[tuple[str, ...], int] = defaultdict(int)
        for row_index, item in enumerate(supplied):
            if not isinstance(item, dict) or "row" not in item or "weight" not in item:
                raise ValueError(f"inputs[{node_id}][{row_index}] needs row and weight")
            row = item["row"]
            if not isinstance(row, list) or len(row) != len(node["scope"]):
                raise ValueError(f"inputs[{node_id}][{row_index}] row width must match node scope")
            key = tuple(_json_scalar_key(value) for value in row)
            aggregate[key] += _parse_weight(item["weight"])
        # A zero-weight tuple is absent from the native weighted relation.
        # This also removes duplicate zero-weight rows after aggregation.
        native_rows.append(sorted((key, weight) for key, weight in aggregate.items() if weight > 0))

    return nodes, native_rows, root, parents, separators


def evaluate(obj: dict[str, Any]) -> dict[str, Any]:
    """Evaluate one JSON input object by explicit complete-assignment joins."""
    if not isinstance(obj, dict):
        raise ValueError("each input line must be a JSON object")
    route = obj.get("route", "tree")
    if route == "constant_true" or route == "constant_false":
        return {
            "route": route,
            "root": obj.get("root"),
            "root_count": "1" if route == "constant_true" else "0",
            "nodes": [],
            "messages": [],
        }
    if route != "tree":
        raise ValueError(f"unknown route {route!r}")

    nodes, native_rows, root, parents, separators = _validate_tree(obj)
    n = len(nodes)
    if root is None:
        return {
            "route": route,
            "root": None,
            "root_count": "0",
            "nodes": [],
            "messages": [],
        }

    # Complete assignment is (all variable/value keys in this subtree, weight).
    # Keep derivations separate: different native tuple combinations that yield
    # the same assignment each contribute their own product to the exact sum.
    assignments: list[list[tuple[dict[int, str], int]]] = [[] for _ in range(n)]
    row_states: list[list[dict[str, Any]]] = [[] for _ in range(n)]
    outgoing: list[dict[tuple[str, ...], int]] = [{} for _ in range(n)]
    children_first: list[int] = []

    def postorder(node_id: int) -> None:
        for child in nodes[node_id]["children"]:
            postorder(child)
        children_first.append(node_id)

    postorder(root)

    for node_id in children_first:
        node = nodes[node_id]
        scope = node["scope"]
        child_ids = node["children"]
        local_rows: list[tuple[tuple[str, ...], int]]
        if node["kind"] == "native":
            local_rows = native_rows[node_id]
        else:
            # Generalized local rows are the union of positive child messages.
            # The child's separator equals this full scope by validation.
            candidate_keys: set[tuple[str, ...]] = set()
            for child in child_ids:
                edge = separators[child]
                for message_key, count in outgoing[child].items():
                    if count > 0:
                        values_by_variable = dict(zip(edge, message_key))
                        candidate_keys.add(tuple(values_by_variable[v] for v in scope))
            local_rows = [(key, 1) for key in sorted(candidate_keys)]

        generated: list[tuple[dict[int, str], int]] = []
        for local_key, local_weight in local_rows:
            local_assignment = dict(zip(scope, local_key))
            row_complete: list[tuple[dict[int, str], int]] = []
            if local_weight > 0:
                def join_child(position: int, merged: dict[int, str], weight: int) -> None:
                    if position == len(child_ids):
                        row_complete.append((merged, weight))
                        return
                    child_id = child_ids[position]
                    for child_assignment, child_weight in assignments[child_id]:
                        combined = _merge_assignments(merged, child_assignment)
                        if combined is not None:
                            join_child(position + 1, combined, weight * child_weight)

                join_child(0, local_assignment, local_weight)
            generated.extend(row_complete)
            cached: list[dict[str, Any]] = []
            support = 0
            value_by_variable = dict(zip(scope, local_key))
            for child_id in child_ids:
                edge = separators[child_id]
                edge_key = tuple(value_by_variable[v] for v in edge)
                child_value = outgoing[child_id].get(edge_key, 0)
                if child_value > 0:
                    support += 1
                cached.append({
                    "child": child_id,
                    "separator": edge.copy(),
                    "key": _row_values(edge_key),
                    "value": _count_text(child_value),
                })
            row_states[node_id].append({
                "row": _row_values(local_key),
                "local": _count_text(local_weight),
                "subtree": _count_text(sum(weight for _, weight in row_complete)),
                "cached_child_messages": cached,
                "supported_count": _count_text(support),
            })

        assignments[node_id] = generated
        parent_id = parents[node_id]
        edge = separators[node_id] if parent_id is not None else []
        message_totals: dict[tuple[str, ...], int] = defaultdict(int)
        for assignment, weight in generated:
            message_key = tuple(assignment[variable] for variable in edge)
            message_totals[message_key] += weight
        outgoing[node_id] = {
            key: value for key, value in sorted(message_totals.items()) if value > 0
        }

    output_nodes: list[dict[str, Any]] = []
    output_messages: list[dict[str, Any]] = []
    for node_id, node in enumerate(nodes):
        parent_id = parents[node_id]
        edge = separators[node_id] if parent_id is not None else []
        output_nodes.append({
            "id": node_id,
            "kind": node["kind"],
            "scope": node["scope"],
            "parent": parent_id,
            "separator": edge,
            "rows": row_states[node_id],
        })
        for key, count in sorted(outgoing[node_id].items()):
            output_messages.append({
                "node": node_id,
                "parent": parent_id,
                "separator": edge,
                "key": _row_values(key),
                "count": _count_text(count),
            })

    root_count = outgoing[root].get((), 0)
    return {
        "route": route,
        "root": root,
        "root_count": _count_text(root_count),
        "nodes": output_nodes,
        "messages": output_messages,
    }


def _self_test() -> None:
    def one_native(rows: list[dict[str, Any]]) -> dict[str, Any]:
        return {
            "route": "tree",
            "root": 0,
            "nodes": [{"kind": "native", "scope": [0], "children": []}],
            "inputs": [rows],
        }

    # Hand calculation: hidden y contributes 5*13 + 7*17 = 184 for x=0.
    # Root row x=0 then contributes 2*184=368; x=1 has no supported y child.
    native = evaluate({
        "route": "tree",
        "root": 0,
        "nodes": [
            {"kind": "native", "scope": [0], "children": [1]},
            {"kind": "native", "scope": [0, 1], "children": [2]},
            {"kind": "native", "scope": [1], "children": []},
        ],
        "inputs": [
            [{"row": ["x0"], "weight": 2}, {"row": ["x1"], "weight": 3}],
            [
                {"row": ["x0", "a"], "weight": 5},
                {"row": ["x0", "b"], "weight": 7},
                {"row": ["x1", "c"], "weight": 11},
            ],
            [
                {"row": ["a"], "weight": 13},
                {"row": ["b"], "weight": 17},
                {"row": ["d"], "weight": 19},
            ],
        ],
    })
    assert native["root_count"] == "368"
    assert {tuple(row["row"]): row["subtree"] for row in native["nodes"][0]["rows"]} == {
        ("x0",): "368", ("x1",): "0"
    }
    assert {tuple(row["row"]): row["subtree"] for row in native["nodes"][1]["rows"]} == {
        ("x0", "a"): "65", ("x0", "b"): "119", ("x1", "c"): "0"
    }
    assert [(item["key"], item["count"]) for item in native["messages"] if item["node"] == 1] == [
        (["x0"], "184")
    ]

    # G(x,z)->x: R's hidden z sums to 2+3=5 at x=1, then multiplies by
    # S's 7. x=2 is a candidate from R but is missing from S, so subtree=0.
    generalized = evaluate({
        "route": "tree",
        "root": 0,
        "nodes": [
            {"kind": "generalized", "scope": [0], "children": [1, 2]},
            {"kind": "native", "scope": [0, 1], "children": []},
            {"kind": "native", "scope": [0, 2], "children": []},
        ],
        "inputs": [
            [],
            [
                {"row": [1, "a"], "weight": 2},
                {"row": [1, "b"], "weight": 3},
                {"row": [2, "c"], "weight": 5},
            ],
            [{"row": [1, "p"], "weight": 7}],
        ],
    })
    assert generalized["root_count"] == "35"
    assert {tuple(row["row"]): row["subtree"] for row in generalized["nodes"][0]["rows"]} == {
        (1,): "35", (2,): "0"
    }
    generalized_rows = {tuple(row["row"]): row for row in generalized["nodes"][0]["rows"]}
    assert generalized_rows[(1,)]["local"] == "1"
    assert generalized_rows[(2,)]["cached_child_messages"] == [
        {"child": 1, "separator": [0], "key": [2], "value": "5"},
        {"child": 2, "separator": [0], "key": [2], "value": "0"},
    ]
    assert generalized_rows[(2,)]["supported_count"] == "1"

    # Exactness past IEEE-754 and at a much larger magnitude.
    beyond_js = 9_007_199_254_740_993
    huge = 10**120 + 987_654_321
    large = evaluate(one_native([
        {"row": ["a"], "weight": str(beyond_js)},
        {"row": ["b"], "weight": str(huge)},
    ]))
    assert large["root_count"] == str(beyond_js + huge)
    assert {tuple(row["row"]): row["local"] for row in large["nodes"][0]["rows"]} == {
        ("a",): str(beyond_js), ("b",): str(huge)
    }

    # Explicit zero tuples are absent, including duplicate rows whose total is
    # zero; they produce neither row states nor positive messages.
    zero_rows = evaluate(one_native([
        {"row": ["explicit-zero"], "weight": 0},
        {"row": ["duplicate-zero"], "weight": 0},
        {"row": ["duplicate-zero"], "weight": "0"},
        {"row": ["positive"], "weight": 2},
    ]))
    assert zero_rows["root_count"] == "2"
    assert [row["row"] for row in zero_rows["nodes"][0]["rows"]] == [["positive"]]
    assert zero_rows["messages"] == [
        {"node": 0, "parent": None, "separator": [], "key": [], "count": "2"}
    ]

    # Deletion and numeric edits are fresh full-oracle calls, not incremental
    # operations: remove x=2, then change x=1's weight from 5 to 9.
    initial = one_native([
        {"row": [1], "weight": 5},
        {"row": [2], "weight": 7},
    ])
    assert evaluate(initial)["root_count"] == "12"
    assert evaluate(one_native([{"row": [1], "weight": 5}]))["root_count"] == "5"
    assert evaluate(one_native([{"row": [1], "weight": 9}]))["root_count"] == "9"

    assert evaluate({"route": "constant_true", "root": None})["root_count"] == "1"
    assert evaluate({"route": "constant_false", "root": None})["root_count"] == "0"


def main(argv: list[str]) -> int:
    if argv == ["--self-test"]:
        _self_test()
        print("weighted_oracle self-test: ok")
        return 0
    if argv:
        print("usage: weighted_oracle.py [--self-test] < input.jsonl", file=sys.stderr)
        return 2

    for line_number, line in enumerate(sys.stdin, start=1):
        if not line.strip():
            continue
        try:
            result = evaluate(json.loads(line))
        except (json.JSONDecodeError, ValueError) as error:
            print(f"line {line_number}: {error}", file=sys.stderr)
            return 2
        print(json.dumps(result, ensure_ascii=False, separators=(",", ":"), allow_nan=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
