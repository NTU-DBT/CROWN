#!/usr/bin/env python3
"""Independent projected bag oracle for W03 line-oriented JSON fixtures.

Design reference: Refactor.md section 10.2 and docs/weighted_enumeration.md.

This oracle ignores the compiled tree's generalized nodes when evaluating rows:
they add no atom. It enumerates complete compatible choices from every native
occurrence, multiplies their nonnegative weights, then sums by the ordered head
tuple using Python integers. Duplicate input rows for one occurrence are first
folded by addition, which has the same bag meaning and keeps this independent of
the incremental weighted runtime and its factor tables.

The implementation deliberately uses a Cartesian product followed by a natural-
join compatibility check. Its time can grow as the product of native relation
sizes, so fixtures must remain small. It materializes input rows and projected
group counts, but never the full result multiset. It is a correctness oracle,
not a performance or incremental-maintenance model.

Usage:
    python3 tests/reference/weighted_bag_oracle.py < cases.jsonl
    python3 tests/reference/weighted_bag_oracle.py --self-test

Tree input objects contain `nodes`, `root`, `inputs`, `route`, and `head`.
Nodes and inputs are parallel arrays indexed by node ID. A node has `kind`
(`native` or `generalized`), an ordered integer `scope`, and child node IDs. A
native input is a list of `{row: [...], weight: decimal-string-or-integer}`
objects. A generalized input must be empty. `head` is an ordered list of
variable IDs; repeats and the empty list are allowed. Values must be finite JSON
scalars. JSON booleans, integers, and floats have type-sensitive equality.

Output is `{rows: [{row: [...], count: "..."}, ...], total_count: "..."}`.
Rows are ordered by their canonical, type-sensitive JSON scalar keys. Counts
are decimal strings. `total_count` is the sum of the projected multiplicities.
For an empty head, any nonempty complete join emits one empty tuple whose count
is the total witness weight. `constant_true` emits that unit empty tuple;
`constant_false` emits no rows. Both constant routes require an empty head.

Failure contract: an invalid fixture raises ValueError (or JSON decoding error).
CLI mode reports the offending line to stderr and exits with status 2; that line
produces no output. Earlier valid lines may already have been written.
"""

from __future__ import annotations

import itertools
import json
import math
import re
import sys
from collections import defaultdict
from typing import Any


def _json_scalar_key(value: Any) -> str:
    """Return a stable, type-sensitive key for a finite JSON scalar."""
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


def _row_values(keys: tuple[str, ...]) -> list[Any]:
    return [json.loads(key) for key in keys]


def _merge_assignments(left: dict[int, str], right: dict[int, str]) -> dict[int, str] | None:
    merged = left.copy()
    for variable, value in right.items():
        previous = merged.get(variable)
        # Encoded values are nonempty JSON strings, including the key for null.
        if previous is not None and previous != value:
            return None
        merged[variable] = value
    return merged


def _validate(
    obj: dict[str, Any],
) -> tuple[str, list[list[tuple[dict[int, str], int]]], list[int]]:
    route = obj.get("route", "tree")
    if route in ("constant_true", "constant_false"):
        head = obj.get("head", [])
        if not isinstance(head, list) or head:
            raise ValueError("constant routes require an empty head")
        return route, [], []
    if route != "tree":
        raise ValueError(f"unknown route {route!r}")
    for required in ("nodes", "root", "inputs", "head"):
        if required not in obj:
            raise ValueError(f"tree route requires {required}")

    raw_nodes = obj["nodes"]
    raw_inputs = obj["inputs"]
    root = obj["root"]
    raw_head = obj["head"]
    if not isinstance(raw_nodes, list) or not raw_nodes:
        raise ValueError("tree route requires a nonempty nodes array")
    if not isinstance(raw_inputs, list) or len(raw_inputs) != len(raw_nodes):
        raise ValueError("inputs must have one entry per node, in node-index order")
    if type(root) is not int or root < 0 or root >= len(raw_nodes):
        raise ValueError(f"root must be a valid node index, got {root!r}")
    if not isinstance(raw_head, list) or any(type(variable) is not int or variable < 0 for variable in raw_head):
        raise ValueError("head must be an array of nonnegative integer variable IDs")

    nodes: list[dict[str, Any]] = []
    parents: list[int | None] = [None] * len(raw_nodes)
    all_variables: set[int] = set()
    for node_id, raw in enumerate(raw_nodes):
        if not isinstance(raw, dict):
            raise ValueError(f"node {node_id} must be an object")
        kind = raw.get("kind")
        if kind not in ("native", "generalized"):
            raise ValueError(f"node {node_id} has unknown kind {kind!r}")
        scope = raw.get("scope")
        children = raw.get("children")
        if not isinstance(scope, list) or any(type(variable) is not int or variable < 0 for variable in scope):
            raise ValueError(f"node {node_id} scope must contain nonnegative integer variable IDs")
        if len(set(scope)) != len(scope):
            raise ValueError(f"node {node_id} scope contains duplicate variables")
        if not isinstance(children, list) or any(type(child) is not int for child in children):
            raise ValueError(f"node {node_id} children must be an array of node indices")
        if len(set(children)) != len(children):
            raise ValueError(f"node {node_id} lists a child more than once")
        if any(child < 0 or child >= len(raw_nodes) for child in children):
            raise ValueError(f"node {node_id} has an out-of-range child index")
        if kind == "generalized" and not children:
            raise ValueError(f"generalized node {node_id} must have at least one child")
        nodes.append({"kind": kind, "scope": scope.copy(), "children": children.copy()})
        all_variables.update(scope)
        for child in children:
            if parents[child] is not None:
                raise ValueError(f"node {child} has more than one parent")
            parents[child] = node_id

    if parents[root] is not None:
        raise ValueError("root node must not have a parent")
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
    if len(visited) != len(nodes):
        raise ValueError("all nodes must be reachable from root")

    for node_id, parent_id in enumerate(parents):
        if parent_id is None or nodes[parent_id]["kind"] != "generalized":
            continue
        parent_scope = set(nodes[parent_id]["scope"])
        child_scope = set(nodes[node_id]["scope"])
        if not parent_scope <= child_scope:
            raise ValueError(f"child {node_id} separator must contain generalized parent {parent_id} scope")

    native_tables: list[list[tuple[dict[int, str], int]]] = []
    native_variables: set[int] = set()
    for node_id, node in enumerate(nodes):
        supplied = raw_inputs[node_id]
        if not isinstance(supplied, list):
            raise ValueError(f"inputs[{node_id}] must be an array")
        if node["kind"] == "generalized":
            if supplied:
                raise ValueError(f"generalized node {node_id} must have no local input rows")
            continue
        native_variables.update(node["scope"])
        aggregate: dict[tuple[str, ...], int] = defaultdict(int)
        for row_index, item in enumerate(supplied):
            if not isinstance(item, dict) or "row" not in item or "weight" not in item:
                raise ValueError(f"inputs[{node_id}][{row_index}] needs row and weight")
            row = item["row"]
            if not isinstance(row, list) or len(row) != len(node["scope"]):
                raise ValueError(f"inputs[{node_id}][{row_index}] row width must match node scope")
            key = tuple(_json_scalar_key(value) for value in row)
            aggregate[key] += _parse_weight(item["weight"])
        native_tables.append([
            (dict(zip(node["scope"], key)), weight)
            for key, weight in sorted(aggregate.items()) if weight > 0
        ])

    if not native_tables:
        raise ValueError("tree route requires at least one native occurrence")
    if any(variable not in all_variables for variable in raw_head):
        raise ValueError("head contains a variable outside every node scope")
    if any(variable not in native_variables for variable in raw_head):
        raise ValueError("head contains a variable outside every native occurrence scope")
    return route, native_tables, raw_head.copy()


def evaluate(obj: dict[str, Any]) -> dict[str, Any]:
    """Evaluate one fixture by explicit complete-assignment natural joins."""
    if not isinstance(obj, dict):
        raise ValueError("each input line must be a JSON object")
    route, native_tables, head = _validate(obj)
    if route == "constant_false":
        return {"rows": [], "total_count": "0"}
    if route == "constant_true":
        return {"rows": [{"row": [], "count": "1"}], "total_count": "1"}

    totals: dict[tuple[str, ...], int] = defaultdict(int)
    for choices in itertools.product(*native_tables):
        assignment: dict[int, str] = {}
        weight = 1
        for row_assignment, row_weight in choices:
            merged = _merge_assignments(assignment, row_assignment)
            if merged is None:
                break
            assignment = merged
            weight *= row_weight
        else:
            output_key = tuple(assignment[variable] for variable in head)
            totals[output_key] += weight

    rows = [
        {"row": _row_values(key), "count": str(count)}
        for key, count in sorted(totals.items()) if count > 0
    ]
    return {"rows": rows, "total_count": str(sum(totals.values()))}


def _self_test() -> None:
    # R(x,y,u) has hidden-u total 2+3=5. S(y,z) has hidden-z total 5+7=12.
    # The projected bag contains one (x,y) row of weight 60. Multiplying either
    # full subtree into its explicitly joined child would count a witness twice.
    counted_path = evaluate({
        "route": "tree", "root": 0,
        "nodes": [
            {"kind": "native", "scope": [0, 1, 2], "children": [1]},
            {"kind": "native", "scope": [1, 3], "children": []},
        ],
        "inputs": [
            [
                {"row": [1, 10, "u0"], "weight": 2},
                {"row": [1, 10, "u1"], "weight": 3},
            ],
            [
                {"row": [10, "z0"], "weight": 5},
                {"row": [10, "z1"], "weight": 7},
            ],
        ],
        "head": [0, 1],
    })
    assert counted_path == {
        "rows": [{"row": [1, 10], "count": "60"}], "total_count": "60"
    }

    # Nested G(x,z)->G(x) has no input rows of its own. The ordinary join of its
    # two native children yields 2*5 + 3*7 = 31 after hidden z is summed out.
    nested_generalized = evaluate({
        "route": "tree", "root": 0,
        "nodes": [
            {"kind": "generalized", "scope": [0], "children": [1]},
            {"kind": "generalized", "scope": [0, 1], "children": [2, 3]},
            {"kind": "native", "scope": [0, 1], "children": []},
            {"kind": "native", "scope": [0, 1], "children": []},
        ],
        "inputs": [
            [], [],
            [
                {"row": [1, 10], "weight": 2},
                {"row": [1, 20], "weight": 3},
            ],
            [
                {"row": [1, 10], "weight": 5},
                {"row": [1, 20], "weight": 7},
            ],
        ],
        "head": [0],
    })
    assert nested_generalized == {
        "rows": [{"row": [1], "count": "31"}], "total_count": "31"
    }

    # Only the root is output-connex: both incoming branch keys below it are
    # hidden. A complete-assignment oracle still counts each hidden branch once.
    hidden_branch = evaluate({
        "route": "tree", "root": 0,
        "nodes": [
            {"kind": "native", "scope": [0, 1], "children": [1]},
            {"kind": "native", "scope": [1, 2], "children": [2]},
            {"kind": "native", "scope": [2, 3], "children": []},
        ],
        "inputs": [
            [
                {"row": [1, 10], "weight": 2},
                {"row": [1, 20], "weight": 3},
            ],
            [
                {"row": [10, 7], "weight": 5},
                {"row": [20, 8], "weight": 11},
            ],
            [
                {"row": [7, 100], "weight": 13},
                {"row": [8, 200], "weight": 17},
            ],
        ],
        "head": [0],
    })
    assert hidden_branch == {
        "rows": [{"row": [1], "count": "691"}], "total_count": "691"
    }

    # Raw duplicate tuples add their weights; zero is absent. JSON bool and int
    # remain distinct keys and do not match in a natural join.
    duplicates = evaluate({
        "root": 0,
        "nodes": [{"kind": "native", "scope": [0], "children": []}],
        "inputs": [[
            {"row": ["dup"], "weight": 2},
            {"row": ["dup"], "weight": 3},
            {"row": ["zero"], "weight": 0},
            {"row": [True], "weight": 7},
            {"row": [1], "weight": 11},
        ]],
        "head": [0],
    })
    assert duplicates["rows"] == [
        {"row": ["dup"], "count": "5"},
        {"row": [1], "count": "11"},
        {"row": [True], "count": "7"},
    ]
    mismatch = evaluate({
        "root": 0,
        "nodes": [
            {"kind": "native", "scope": [0], "children": [1]},
            {"kind": "native", "scope": [0], "children": []},
        ],
        "inputs": [
            [{"row": [True], "weight": 2}],
            [{"row": [1], "weight": 3}],
        ],
        "head": [0],
    })
    assert mismatch == {"rows": [], "total_count": "0"}

    # Repeated head slots preserve order without changing multiplicity; empty
    # head collapses all complete witnesses to one weighted empty tuple.
    unary = {
        "root": 0,
        "nodes": [{"kind": "native", "scope": [0], "children": []}],
        "inputs": [[{"row": [1], "weight": 2}, {"row": [2], "weight": 3}]],
    }
    repeated = evaluate({**unary, "head": [0, 0]})
    assert repeated == {
        "rows": [
            {"row": [1, 1], "count": "2"},
            {"row": [2, 2], "count": "3"},
        ],
        "total_count": "5",
    }
    empty_head = evaluate({**unary, "head": []})
    assert empty_head == {"rows": [{"row": [], "count": "5"}], "total_count": "5"}

    # Empty-scope native relation and disconnected product remain exact, with
    # totals above IEEE-754 precision and outside u64.
    large = 9_007_199_254_740_993
    beyond_u64 = (1 << 64) + 5
    empty_scope = evaluate({
        "root": 0,
        "nodes": [{"kind": "native", "scope": [], "children": []}],
        "inputs": [[{"row": [], "weight": str(large)}, {"row": [], "weight": str(beyond_u64)}]],
        "head": [],
    })
    assert empty_scope == {
        "rows": [{"row": [], "count": str(large + beyond_u64)}],
        "total_count": str(large + beyond_u64),
    }
    disconnected = evaluate({
        "root": 0,
        "nodes": [
            {"kind": "generalized", "scope": [], "children": [1, 2]},
            {"kind": "native", "scope": [0], "children": []},
            {"kind": "native", "scope": [1], "children": []},
        ],
        "inputs": [
            [],
            [{"row": [4], "weight": 2}, {"row": [4], "weight": 3}],
            [{"row": [9], "weight": 7}],
        ],
        "head": [0],
    })
    assert disconnected == {
        "rows": [{"row": [4], "count": "35"}], "total_count": "35"
    }

    assert evaluate({"route": "constant_true", "head": []}) == {
        "rows": [{"row": [], "count": "1"}], "total_count": "1"
    }
    assert evaluate({"route": "constant_false", "head": []}) == {
        "rows": [], "total_count": "0"
    }

    try:
        evaluate({**unary, "head": [99]})
    except ValueError:
        pass
    else:
        raise AssertionError("out-of-scope head variable was accepted")


def main(argv: list[str]) -> int:
    if argv == ["--self-test"]:
        _self_test()
        print("weighted_bag_oracle self-test: ok")
        return 0
    if argv:
        print("usage: weighted_bag_oracle.py [--self-test] < input.jsonl", file=sys.stderr)
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
