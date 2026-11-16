"""Seeded direct-CQ traces and an independent SQLite set-semantics oracle.

This module intentionally builds SQL directly from the versioned CQ document.
It does not use the production planner, tree builder, or evaluator.
"""

from __future__ import annotations

import copy
import json
import math
import random
import sqlite3
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable, Iterable


SHAPES = (
    "singleton_projection",
    "two_edge_path",
    "star",
    "disconnected",
    "self_join_supports",
    "repeated_variable_filter",
)
SCALAR_TYPES = ("int64", "string", "bool")
VALUE_DOMAIN = {
    "int64": (-2, -1, 0, 1, 2),
    "string": ("v0", "v1", "v2", "v3", "v4"),
    "bool": (False, True),
}


class FuzzError(RuntimeError):
    """A generation, CLI, oracle, or shrinker failure."""


# Diagnostic graphs are retained by reference; callers must preserve them until serialization.
class Mismatch(FuzzError):
    def __init__(
        self,
        message: str,
        document: dict[str, Any],
        actual: Any,
        expected: Any,
        sql: str,
        parameters: list[Any],
    ) -> None:
        super().__init__(message)
        self.document = document
        self.actual = actual
        self.expected = expected
        self.sql = sql
        self.parameters = parameters


@dataclass(frozen=True)
class SqlPlan:
    statement: str
    parameters: tuple[Any, ...]
    output_types: tuple[str, ...]


def json_type(value: Any) -> str:
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int64"
    if isinstance(value, str):
        return "string"
    raise FuzzError(f"unsupported generated scalar value: {value!r}")


def value_for(type_name: str, index: int) -> Any:
    domain = VALUE_DOMAIN[type_name]
    return domain[index % len(domain)]


def random_value(rng: random.Random, type_name: str) -> Any:
    return rng.choice(VALUE_DOMAIN[type_name])


def unique_rows(rows: Iterable[list[Any]]) -> list[list[Any]]:
    result: list[list[Any]] = []
    seen: set[str] = set()
    for row in rows:
        key = json.dumps(row, separators=(",", ":"), sort_keys=True)
        if key not in seen:
            seen.add(key)
            result.append(row)
    return result


def variable(name: str, type_name: str) -> dict[str, str]:
    return {"name": name, "type": type_name}


def column(name: str, type_name: str) -> dict[str, str]:
    return {"name": name, "type": type_name}


def atom(atom_id: str, table: str, terms: list[dict[str, Any]]) -> dict[str, Any]:
    return {"id": atom_id, "table": table, "terms": terms}


def var_term(name: str) -> dict[str, str]:
    return {"var": name}


def ignore_term() -> dict[str, bool]:
    return {"ignore": True}


def const_term(value: Any) -> dict[str, Any]:
    return {"const": value}


def build_shape(shape: str, type_name: str) -> tuple[list[dict[str, Any]], dict[str, Any], list[dict[str, Any]]]:
    v = lambda index: value_for(type_name, index)
    if shape == "singleton_projection":
        tables = [{
            "name": "R",
            "columns": [column("key", type_name), column("witness", type_name)],
        }]
        query = {
            "variables": [variable("x", type_name), variable("z", type_name)],
            "atoms": [atom("r", "R", [var_term("x"), var_term("z")])],
            "head": [{"var": "x"}],
        }
        initial = [{"table": "R", "rows": unique_rows([
            [v(0), v(1)], [v(0), v(2)], [v(1), v(1)],
        ])}]
    elif shape == "two_edge_path":
        tables = [{
            "name": "Edge",
            "columns": [column("src", type_name), column("dst", type_name)],
        }]
        query = {
            "variables": [variable("a", type_name), variable("b", type_name), variable("c", type_name)],
            "atoms": [
                atom("first", "Edge", [var_term("a"), var_term("b")]),
                atom("second", "Edge", [var_term("b"), var_term("c")]),
            ],
            "head": [{"var": "a"}, {"var": "c"}],
        }
        initial = [{"table": "Edge", "rows": unique_rows([
            [v(0), v(1)], [v(1), v(2)], [v(2), v(3)], [v(0), v(2)],
        ])}]
    elif shape == "star":
        tables = [
            {"name": "R", "columns": [column("center", type_name), column("leaf", type_name)]},
            {"name": "S", "columns": [column("center", type_name), column("leaf", type_name)]},
            {"name": "T", "columns": [column("center", type_name), column("leaf", type_name)]},
        ]
        query = {
            "variables": [
                variable("x", type_name), variable("y", type_name),
                variable("z", type_name), variable("w", type_name),
            ],
            "atoms": [
                atom("r", "R", [var_term("x"), var_term("y")]),
                atom("s", "S", [var_term("x"), var_term("z")]),
                atom("t", "T", [var_term("x"), var_term("w")]),
            ],
            "head": [{"var": "x"}, {"var": "y"}, {"var": "z"}, {"var": "w"}],
        }
        rows = unique_rows([[v(0), v(1)], [v(0), v(2)], [v(1), v(3)]])
        initial = [{"table": name, "rows": copy.deepcopy(rows)} for name in ("R", "S", "T")]
    elif shape == "disconnected":
        tables = [
            {"name": "R", "columns": [column("x", type_name)]},
            {"name": "S", "columns": [column("y", type_name)]},
        ]
        query = {
            "variables": [variable("x", type_name), variable("y", type_name)],
            "atoms": [
                atom("r", "R", [var_term("x")]),
                atom("s", "S", [var_term("y")]),
            ],
            "head": [{"var": "x"}, {"var": "y"}],
        }
        initial = [
            {"table": "R", "rows": unique_rows([[v(0)], [v(1)], [v(2)]])},
            {"table": "S", "rows": unique_rows([[v(1)], [v(2)], [v(3)]])},
        ]
    elif shape == "self_join_supports":
        tables = [{
            "name": "Edge",
            "columns": [
                column("src", type_name), column("dst", type_name),
                column("physical_support", "int64"),
            ],
        }]
        query = {
            "variables": [
                variable("a", type_name), variable("b", type_name), variable("c", type_name),
            ],
            "atoms": [
                atom("left", "Edge", [var_term("a"), var_term("b"), ignore_term()]),
                atom("right", "Edge", [var_term("b"), var_term("c"), ignore_term()]),
            ],
            "head": [{"var": "a"}, {"var": "c"}],
        }
        initial = [{"table": "Edge", "rows": unique_rows([
            [v(0), v(1), 11], [v(1), v(2), 12], [v(0), v(3), 13],
            [v(3), v(2), 14], [v(2), v(0), 15],
        ])}]
    elif shape == "repeated_variable_filter":
        constant = v(0)
        tables = [{
            "name": "Triple",
            "columns": [
                column("first", type_name), column("second", type_name),
                column("kind", type_name),
            ],
        }]
        query = {
            "variables": [variable("x", type_name)],
            "atoms": [atom("triple", "Triple", [
                var_term("x"), var_term("x"), const_term(constant),
            ])],
            "head": [{"var": "x"}],
        }
        initial = [{"table": "Triple", "rows": unique_rows([
            [v(0), v(0), constant], [v(1), v(0), constant],
            [v(1), v(1), v(2)], [v(0), v(0), v(1)],
        ])}]
    else:
        raise FuzzError(f"unknown query shape: {shape}")
    return tables, query, initial


def make_updates(
    rng: random.Random,
    tables: list[dict[str, Any]],
    initial: list[dict[str, Any]],
    count: int,
) -> list[dict[str, Any]]:
    rows_by_table: dict[str, set[tuple[Any, ...]]] = {
        record["table"]: {tuple(row) for row in record["rows"]}
        for record in initial
    }
    columns_by_table = {
        table["name"]: table["columns"] for table in tables
    }

    def random_row(table_name: str) -> list[Any]:
        return [
            random_value(rng, col["type"])
            for col in columns_by_table[table_name]
        ]

    updates: list[dict[str, Any]] = []
    table_names = [table["name"] for table in tables]
    for sequence in range(1, count + 1):
        table_name = rng.choice(table_names)
        current = rows_by_table[table_name]
        operation = rng.choice(("insert", "delete"))
        if operation == "delete" and current and rng.random() < 0.72:
            values = list(rng.choice(sorted(current)))
        elif operation == "insert" and current and rng.random() < 0.2:
            values = list(rng.choice(sorted(current)))
        else:
            values = random_row(table_name)

        row = tuple(values)
        if operation == "insert":
            current.add(row)
        else:
            current.discard(row)
        updates.append({
            "schema_version": 1,
            "sequence": sequence,
            "table": table_name,
            "op": operation,
            "values": values,
        })
    return updates


def generate_case(seed: int, update_count: int = 12) -> dict[str, Any]:
    """Generate one seeded, schema-valid direct-CQ document."""
    if update_count < 0:
        raise FuzzError("update_count must be nonnegative")
    shape = SHAPES[seed % len(SHAPES)]
    type_name = SCALAR_TYPES[(seed % len(SHAPES) + seed // len(SHAPES)) % len(SCALAR_TYPES)]
    tables, query, initial = build_shape(shape, type_name)
    rng = random.Random(seed)
    updates = make_updates(rng, tables, initial, update_count)
    return {
        "schema_version": 1,
        "semantics": "set",
        "catalog": {"version": 1, "tables": tables},
        "query": query,
        "initial": initial,
        "updates": updates,
    }


def _require(condition: bool, message: str) -> None:
    if not condition:
        raise FuzzError(message)


def validate_generated_document(document: dict[str, Any]) -> None:
    """Check generator shape/type/sequence invariants independently of CROWN."""
    _require(document.get("schema_version") == 1, "generator emitted wrong schema version")
    _require(document.get("semantics") == "set", "generator emitted unsupported semantics")
    catalog = document.get("catalog")
    query = document.get("query")
    _require(isinstance(catalog, dict) and isinstance(query, dict), "generator omitted catalog/query")
    tables = catalog.get("tables")
    _require(isinstance(tables, list), "generator catalog tables must be an array")
    table_by_name: dict[str, dict[str, Any]] = {}
    for table in tables:
        _require(table["name"] not in table_by_name, f"duplicate generated table {table['name']}")
        table_by_name[table["name"]] = table
        for col in table["columns"]:
            _require(col["type"] in SCALAR_TYPES, f"unsupported generated column type {col['type']}")

    variables = query.get("variables")
    _require(isinstance(variables, list), "generated variables must be an array")
    variable_types: dict[str, str] = {}
    for item in variables:
        _require(item["name"] not in variable_types, f"duplicate generated variable {item['name']}")
        _require(item["type"] in SCALAR_TYPES, f"unsupported generated variable type {item['type']}")
        variable_types[item["name"]] = item["type"]

    bound: set[str] = set()
    for occurrence in query.get("atoms", []):
        table_name = occurrence["table"]
        _require(table_name in table_by_name, f"generated atom refers to unknown table {table_name}")
        columns = table_by_name[table_name]["columns"]
        terms = occurrence["terms"]
        _require(len(terms) == len(columns), f"generated atom {occurrence['id']} has wrong arity")
        for term, col in zip(terms, columns):
            _require(isinstance(term, dict) and len(term) == 1, "generated term must have one operator")
            if "var" in term:
                name = term["var"]
                _require(name in variable_types, f"generated term refers to unknown variable {name}")
                _require(variable_types[name] == col["type"], f"generated variable type mismatch for {name}")
                bound.add(name)
            elif "const" in term:
                _require(json_type(term["const"]) == col["type"], "generated constant type mismatch")
            else:
                _require(term == {"ignore": True}, "generated ignore term must be true")
    _require(bound == set(variable_types), "every generated variable must be bound by the body")
    for output in query.get("head", []):
        _require(output["var"] in bound, "generated head variable is not body-bound")

    for record in document.get("initial", []):
        _require(record["table"] in table_by_name, "generated initial row refers to unknown table")
        columns = table_by_name[record["table"]]["columns"]
        seen: set[str] = set()
        for row in record["rows"]:
            _require(len(row) == len(columns), "generated initial row has wrong arity")
            _require(
                all(json_type(value) == col["type"] for value, col in zip(row, columns)),
                "generated initial row has a type mismatch",
            )
            encoded = json.dumps(row, separators=(",", ":"), sort_keys=True)
            _require(encoded not in seen, "generator emitted duplicate set row")
            seen.add(encoded)

    updates = document.get("updates", [])
    for expected_sequence, update in enumerate(updates, 1):
        _require(update["sequence"] == expected_sequence, "generated update sequence is not contiguous")
        _require(update["op"] in ("insert", "delete"), "generator emitted unsupported update operation")
        _require(update["table"] in table_by_name, "generated update refers to unknown table")
        columns = table_by_name[update["table"]]["columns"]
        values = update["values"]
        _require(len(values) == len(columns), "generated update has wrong arity")
        _require(
            all(json_type(value) == col["type"] for value, col in zip(values, columns)),
            "generated update has a type mismatch",
        )


def _quote(identifier: str) -> str:
    return '"' + identifier.replace('"', '""') + '"'


def _to_sql_value(value: Any) -> Any:
    if isinstance(value, bool):
        return int(value)
    return value


def build_sql(document: dict[str, Any]) -> SqlPlan:
    """Compile a direct CQ to one SQLite SELECT DISTINCT statement."""
    tables = {table["name"]: table for table in document["catalog"]["tables"]}
    from_parts: list[str] = []
    conditions: list[str] = []
    parameters: list[Any] = []
    bindings: dict[str, str] = {}

    for index, occurrence in enumerate(document["query"]["atoms"]):
        alias = f"a{index}"
        table = tables[occurrence["table"]]
        from_parts.append(f"{_quote(table['name'])} AS {_quote(alias)}")
        for column_index, term in enumerate(occurrence["terms"]):
            expression = f"{_quote(alias)}.{_quote(table['columns'][column_index]['name'])}"
            if "var" in term:
                name = term["var"]
                if name in bindings:
                    conditions.append(f"{expression} = {bindings[name]}")
                else:
                    bindings[name] = expression
            elif "const" in term:
                conditions.append(f"{expression} = ?")
                parameters.append(_to_sql_value(term["const"]))
            elif term != {"ignore": True}:
                raise FuzzError(f"unsupported term while building SQL: {term!r}")

    head = document["query"]["head"]
    variables = {item["name"]: item for item in document["query"]["variables"]}
    if head:
        select = ", ".join(bindings[item["var"]] for item in head)
        output_types = tuple(variables[item["var"]]["type"] for item in head)
    else:
        select = "1"
        output_types = ()
    statement = f"SELECT DISTINCT {select}"
    if from_parts:
        statement += " FROM " + ", ".join(from_parts)
    if conditions:
        statement += " WHERE " + " AND ".join(conditions)
    return SqlPlan(statement, tuple(parameters), output_types)


def _decode_sql_value(value: Any, type_name: str) -> Any:
    if type_name == "bool":
        return bool(value)
    if type_name == "int64":
        return int(value)
    if type_name == "string":
        return str(value)
    raise FuzzError(f"unknown output type {type_name}")


def _sorted_json_rows(rows: Iterable[tuple[Any, ...]]) -> list[list[Any]]:
    return [list(row) for row in sorted(rows)]


def sqlite_reference(document: dict[str, Any]) -> tuple[dict[str, Any], SqlPlan]:
    """Return complete current/delta trace from a fresh in-memory SQLite DB."""
    tables = document["catalog"]["tables"]
    table_by_name = {table["name"]: table for table in tables}
    plan = build_sql(document)
    connection = sqlite3.connect(":memory:")
    try:
        for table in tables:
            declarations = []
            for col in table["columns"]:
                sql_type = "TEXT" if col["type"] == "string" else "INTEGER"
                declarations.append(f"{_quote(col['name'])} {sql_type} NOT NULL")
            connection.execute(
                f"CREATE TABLE {_quote(table['name'])} ({', '.join(declarations)})"
            )

        rows_by_table: dict[str, set[tuple[Any, ...]]] = {
            table["name"]: set() for table in tables
        }
        for record in document.get("initial", []):
            table_name = record["table"]
            table = table_by_name[table_name]
            placeholders = ", ".join("?" for _ in table["columns"])
            insert_sql = f"INSERT INTO {_quote(table_name)} VALUES ({placeholders})"
            for row in record["rows"]:
                physical = tuple(row)
                if physical in rows_by_table[table_name]:
                    continue
                rows_by_table[table_name].add(physical)
                connection.execute(insert_sql, tuple(_to_sql_value(value) for value in row))

        def evaluate() -> set[tuple[Any, ...]]:
            if document["query"].get("contradiction", False):
                return set()
            raw_rows = connection.execute(plan.statement, plan.parameters).fetchall()
            if not plan.output_types:
                return {()} if raw_rows else set()
            return {
                tuple(_decode_sql_value(value, type_name)
                      for value, type_name in zip(row, plan.output_types))
                for row in raw_rows
            }

        before = evaluate()
        initial_answer = _sorted_json_rows(before)
        epochs: list[dict[str, Any]] = []
        for update in document.get("updates", []):
            table_name = update["table"]
            table = table_by_name[table_name]
            values = tuple(update["values"])
            relation = rows_by_table[table_name]
            changed = values not in relation if update["op"] == "insert" else values in relation
            if update["op"] == "insert" and changed:
                relation.add(values)
                placeholders = ", ".join("?" for _ in table["columns"])
                connection.execute(
                    f"INSERT INTO {_quote(table_name)} VALUES ({placeholders})",
                    tuple(_to_sql_value(value) for value in values),
                )
            elif update["op"] == "delete" and changed:
                relation.remove(values)
                predicate = " AND ".join(
                    f"{_quote(col['name'])} = ?" for col in table["columns"]
                )
                connection.execute(
                    f"DELETE FROM {_quote(table_name)} WHERE {predicate}",
                    tuple(_to_sql_value(value) for value in values),
                )
            after = evaluate()
            epochs.append({
                "sequence": update["sequence"],
                "input_changed": changed,
                "current": _sorted_json_rows(after),
                "delta": {
                    "added": _sorted_json_rows(after - before),
                    "removed": _sorted_json_rows(before - after),
                },
            })
            before = after

        return ({
            "schema_version": 1,
            "backend": "reference_recompute",
            "semantics": "set",
            "initial": initial_answer,
            "epochs": epochs,
        }, plan)
    finally:
        connection.close()


def json_equal(left: Any, right: Any) -> bool:
    """Type-sensitive JSON equality; Python otherwise equates True and 1."""
    return json.dumps(
        left, sort_keys=True, separators=(",", ":"), ensure_ascii=False
    ) == json.dumps(
        right, sort_keys=True, separators=(",", ":"), ensure_ascii=False
    )


def first_difference(actual: Any, expected: Any, path: str = "$") -> str | None:
    if type(actual) is not type(expected):
        return f"{path}: type differs ({type(actual).__name__} != {type(expected).__name__})"
    if isinstance(expected, dict):
        if set(actual) != set(expected):
            return f"{path}: object keys differ ({sorted(actual)} != {sorted(expected)})"
        for key in sorted(expected):
            difference = first_difference(actual[key], expected[key], f"{path}.{key}")
            if difference:
                return difference
        return None
    if isinstance(expected, list):
        if len(actual) != len(expected):
            return f"{path}: array length differs ({len(actual)} != {len(expected)})"
        for index, (left, right) in enumerate(zip(actual, expected)):
            difference = first_difference(left, right, f"{path}[{index}]")
            if difference:
                return difference
        return None
    if actual != expected:
        return f"{path}: {actual!r} != {expected!r}"
    return None


def _invoke(executable: str, command: str, document: dict[str, Any]) -> Any:
    try:
        with tempfile.TemporaryDirectory(prefix="crown-reference-fuzz-") as directory:
            document_path = Path(directory) / "document.json"
            document_path.write_text(
                json.dumps(document, ensure_ascii=False, indent=2) + "\n",
                encoding="utf-8",
            )
            result = subprocess.run(
                [executable, command, str(document_path)],
                check=False,
                capture_output=True,
                text=True,
                encoding="utf-8",
                timeout=20,
            )
    except subprocess.TimeoutExpired as error:
        raise FuzzError(
            f"{command} timed out after 20 seconds; "
            f"stdout={error.stdout!r}; stderr={error.stderr!r}"
        ) from error
    except OSError as error:
        raise FuzzError(f"could not run {command}: {error}") from error
    if result.returncode != 0:
        raise FuzzError(
            f"{command} exited {result.returncode}\n"
            f"stdout:\n{result.stdout}\nstderr:\n{result.stderr}"
        )
    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError as error:
        raise FuzzError(
            f"{command} emitted invalid JSON: {error}\n"
            f"stdout:\n{result.stdout}\nstderr:\n{result.stderr}"
        ) from error


def validate_with_cli(executable: str, document: dict[str, Any]) -> None:
    result = _invoke(executable, "validate-cq", document)
    if result.get("cq_valid") is not True or result.get("semantics") != "set":
        raise FuzzError(f"validate-cq returned unexpected result: {result!r}")


def cli_reference(executable: str, document: dict[str, Any]) -> dict[str, Any]:
    result = _invoke(executable, "oracle", document)
    if not isinstance(result, dict):
        raise FuzzError(f"oracle output must be a JSON object: {result!r}")
    return result


def compare_case(executable: str, document: dict[str, Any]) -> tuple[dict[str, Any], dict[str, Any], SqlPlan]:
    validate_generated_document(document)
    validate_with_cli(executable, document)
    actual = cli_reference(executable, document)
    expected, plan = sqlite_reference(document)
    difference = first_difference(actual, expected)
    if difference:
        raise Mismatch(
            difference, document, actual, expected, plan.statement, list(plan.parameters)
        )
    return actual, expected, plan


def resequence(document: dict[str, Any]) -> dict[str, Any]:
    result = copy.deepcopy(document)
    for sequence, update in enumerate(result.get("updates", []), 1):
        update["sequence"] = sequence
    return result


# Deletion-local minimization can rerun native and SQLite oracles many times.
def _ddmin(
    items: list[Any],
    make_candidate: Callable[[list[Any]], dict[str, Any]],
    preserves_failure: Callable[[dict[str, Any]], bool],
) -> list[Any]:
    current = list(items)
    granularity = 2
    while current:
        chunk_size = math.ceil(len(current) / granularity)
        reduced = False
        for start in range(0, len(current), chunk_size):
            keep = current[:start] + current[start + chunk_size:]
            candidate = make_candidate(keep)
            if preserves_failure(candidate):
                current = keep
                granularity = max(2, granularity - 1)
                reduced = True
                break
        if reduced:
            continue
        if granularity >= len(current):
            break
        granularity = min(len(current), granularity * 2)

    changed = True
    while changed:
        changed = False
        for index in range(len(current)):
            keep = current[:index] + current[index + 1:]
            if preserves_failure(make_candidate(keep)):
                current = keep
                changed = True
                break
    return current


def shrink_trace(
    document: dict[str, Any],
    preserves_failure: Callable[[dict[str, Any]], bool],
) -> dict[str, Any]:
    """Remove initial rows and update events while preserving the failure.

    Query, catalog, operators, and update values remain fixed. Every candidate
    gets contiguous update sequence numbers before the predicate sees it.
    """
    current = resequence(document)
    flat_rows: list[tuple[int, int]] = []
    for table_index, record in enumerate(current.get("initial", [])):
        for row_index, _ in enumerate(record["rows"]):
            flat_rows.append((table_index, row_index))

    def with_rows(keep: list[tuple[int, int]]) -> dict[str, Any]:
        candidate = copy.deepcopy(current)
        keep_set = set(keep)
        for table_index, record in enumerate(candidate.get("initial", [])):
            record["rows"] = [
                row for row_index, row in enumerate(record["rows"])
                if (table_index, row_index) in keep_set
            ]
        return resequence(candidate)

    kept_rows = _ddmin(flat_rows, with_rows, preserves_failure)
    current = with_rows(kept_rows)

    update_indexes = list(range(len(current.get("updates", []))))

    def with_updates(keep: list[int]) -> dict[str, Any]:
        candidate = copy.deepcopy(current)
        keep_set = set(keep)
        candidate["updates"] = [
            update for index, update in enumerate(candidate.get("updates", []))
            if index in keep_set
        ]
        return resequence(candidate)

    kept_updates = _ddmin(update_indexes, with_updates, preserves_failure)
    return with_updates(kept_updates)


def inject_duplicate_delta_fault(result: dict[str, Any]) -> dict[str, Any]:
    """Test-only fault wrapper: duplicate one emitted delta row."""
    corrupted = copy.deepcopy(result)
    for epoch in corrupted.get("epochs", []):
        for kind in ("added", "removed"):
            rows = epoch["delta"][kind]
            if rows:
                rows.append(copy.deepcopy(rows[0]))
                return corrupted
    return corrupted


def fault_is_observed(executable: str, document: dict[str, Any]) -> bool:
    actual = cli_reference(executable, document)
    expected, _ = sqlite_reference(document)
    corrupted = inject_duplicate_delta_fault(actual)
    return first_difference(corrupted, expected) is not None


def shrinker_fault_case(executable: str, seed: int = 0, update_count: int = 12) -> dict[str, Any]:
    """Run the test-wrapper duplicate-delta fault and return its minimized packet."""
    original = generate_case(seed, update_count)
    if SHAPES[seed % len(SHAPES)] != "singleton_projection":
        raise FuzzError("shrinker fault demonstration requires a singleton projection seed")

    table = original["catalog"]["tables"][0]
    key_type = table["columns"][0]["type"]
    witness_type = table["columns"][1]["type"]
    focused_insert = {
        "schema_version": 1,
        "sequence": 1,
        "table": table["name"],
        "op": "insert",
        "values": [value_for(key_type, 4), value_for(witness_type, 3)],
    }
    original["updates"].insert(0, focused_insert)
    original = resequence(original)
    validate_generated_document(original)
    validate_with_cli(executable, original)
    if not fault_is_observed(executable, original):
        raise FuzzError("test-wrapper duplicate-delta fault was not detected")

    minimized = shrink_trace(
        original,
        lambda candidate: fault_is_observed(executable, candidate),
    )
    validate_generated_document(minimized)
    if len(minimized.get("updates", [])) != 1:
        raise FuzzError(
            "shrinker did not reduce injected duplicate-delta failure to one event: "
            f"{len(minimized.get('updates', []))} remain"
        )
    if not fault_is_observed(executable, minimized):
        raise FuzzError("shrunk trace no longer reproduces injected duplicate-delta fault")

    _, plan = sqlite_reference(minimized)
    return {
        "seed": seed,
        "shape": SHAPES[seed % len(SHAPES)],
        "failure": "test_wrapper_duplicate_delta",
        "normalized_cq": copy.deepcopy(minimized["query"]),
        "sql": plan.statement,
        "sql_parameters": list(plan.parameters),
        "trace": {
            "initial": copy.deepcopy(minimized.get("initial", [])),
            "updates": copy.deepcopy(minimized.get("updates", [])),
        },
        "document": minimized,
        "initial_row_count": sum(len(item["rows"]) for item in minimized.get("initial", [])),
        "update_count": len(minimized.get("updates", [])),
    }


def _invalid_variant(
    executable: str,
    document: dict[str, Any],
    expected_code: str,
    variant_name: str,
) -> None:
    result_document = copy.deepcopy(document)
    if variant_name == "sequence":
        if not result_document.get("updates"):
            raise FuzzError("cannot make an invalid sequence variant without updates")
        result_document["updates"][0]["sequence"] += 1
    elif variant_name == "type":
        if not result_document.get("updates"):
            raise FuzzError("cannot make an invalid type variant without updates")
        update = result_document["updates"][0]
        table = next(
            table for table in result_document["catalog"]["tables"]
            if table["name"] == update["table"]
        )
        first_type = table["columns"][0]["type"]
        update["values"][0] = {
            "string": 17,
            "int64": "wrong-type",
            "bool": 7,
        }[first_type]
    elif variant_name == "operation":
        if not result_document.get("updates"):
            raise FuzzError("cannot make an invalid operation variant without updates")
        result_document["updates"][0]["op"] = "upsert"
    else:
        raise FuzzError(f"unknown invalid variant {variant_name}")

    try:
        with tempfile.TemporaryDirectory(prefix="crown-invalid-fuzz-") as directory:
            path = Path(directory) / "invalid.json"
            path.write_text(json.dumps(result_document, indent=2), encoding="utf-8")
            result = subprocess.run(
                [executable, "validate-cq", str(path)],
                check=False,
                capture_output=True,
                text=True,
                encoding="utf-8",
                timeout=20,
            )
    except subprocess.TimeoutExpired as error:
        raise FuzzError(
            f"invalid {variant_name} validate-cq timed out after 20 seconds; "
            f"stdout={error.stdout!r}; stderr={error.stderr!r}"
        ) from error
    except OSError as error:
        raise FuzzError(
            f"could not run invalid {variant_name} validate-cq: {error}"
        ) from error
    if result.returncode == 0:
        raise FuzzError(f"invalid {variant_name} document unexpectedly passed validate-cq")
    try:
        error_object = json.loads(result.stderr)
        code = error_object["error"]["code"]
    except (json.JSONDecodeError, KeyError, TypeError) as error:
        raise FuzzError(
            f"invalid {variant_name} document returned no structured error: {result.stderr}"
        ) from error
    if code != expected_code:
        raise FuzzError(
            f"invalid {variant_name} document returned {code!r}, expected {expected_code!r}"
        )


def check_invalid_variants(executable: str, document: dict[str, Any]) -> int:
    _invalid_variant(executable, document, "invalid_sequence", "sequence")
    _invalid_variant(executable, document, "invalid_update", "type")
    _invalid_variant(executable, document, "invalid_document", "operation")
    return 3


def make_failure_packet(
    seed: int,
    document: dict[str, Any],
    mismatch: Mismatch,
) -> dict[str, Any]:
    return {
        "seed": seed,
        "query_shape": SHAPES[seed % len(SHAPES)],
        "failure": str(mismatch),
        "normalized_cq": copy.deepcopy(document["query"]),
        "sql": mismatch.sql,
        "sql_parameters": mismatch.parameters,
        "trace": {
            "initial": copy.deepcopy(document.get("initial", [])),
            "updates": copy.deepcopy(document.get("updates", [])),
        },
        "document": document,
        "actual": mismatch.actual,
        "expected": mismatch.expected,
    }


def make_error_packet(seed: int, document: dict[str, Any], error: BaseException) -> dict[str, Any]:
    try:
        plan = build_sql(document)
        statement = plan.statement
        parameters = list(plan.parameters)
    except (FuzzError, KeyError, TypeError, IndexError):
        statement = None
        parameters = []
    return {
        "seed": seed,
        "query_shape": SHAPES[seed % len(SHAPES)],
        "failure": str(error),
        "normalized_cq": copy.deepcopy(document.get("query")),
        "sql": statement,
        "sql_parameters": parameters,
        "trace": {
            "initial": copy.deepcopy(document.get("initial", [])),
            "updates": copy.deepcopy(document.get("updates", [])),
        },
        "document": document,
    }
