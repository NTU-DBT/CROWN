#!/usr/bin/env python3
"""Check the bounded SQL binder contract against manual and interpreted fixtures."""

from __future__ import annotations

import collections
import datetime as dt
import itertools
import json
import re
import sqlite3
import subprocess
import sys
import tempfile
from decimal import Decimal
from pathlib import Path
from typing import Any


TIMEOUT_SECONDS = 20
SUCCESS_FIELDS = {
    "schema_version", "admission_status", "binding_valid", "source", "catalog_binding", "catalog_inheritance",
    "requested_semantics", "inner_semantics", "result_wrapper", "wrapper_alias", "parameters",
    "occurrences", "expressions", "predicates", "outputs", "limits", "work",
}
FAILURE_FIELDS = {"schema_version", "admission_status", "binding_valid", "phase", "diagnostic"}
KNOWN_KINDS = {"unknown", "int32", "int64", "string", "bool", "date", "decimal"}
KNOWN_OPERATORS = {
    "equal", "not_equal", "less", "less_equal", "greater", "greater_equal",
    "conjunction", "disjunction", "negation", "is_null", "is_not_null",
    "is_true", "is_not_true", "is_false", "is_not_false", "is_unknown", "is_not_unknown",
    "identity_cast", "literal_cast", "widen_integer", "using_value",
}


def require(condition: bool, message: str) -> None:
    # Keep validation active when invoked with ``python -O``.
    if not condition:
        raise RuntimeError(message)


def read_json(path: Path) -> Any:
    try:
        def reject_constant(value: str) -> Any:
            raise ValueError(f"non-JSON numeric constant {value}")

        return json.loads(path.read_text(encoding="utf-8"), parse_constant=reject_constant)
    except (OSError, UnicodeError, json.JSONDecodeError, ValueError) as error:
        raise RuntimeError(f"{path}: cannot read JSON: {error}") from error


def json_text(value: Any) -> str:
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":"))


def compare(label: str, actual: Any, expected: Any) -> None:
    # JSON encoding makes comparisons type-sensitive (True is not integer 1).
    actual_text = json_text(actual)
    expected_text = json_text(expected)
    if actual_text != expected_text:
        raise RuntimeError(
            f"{label}: mismatch\nexpected: {json.dumps(expected, ensure_ascii=False, sort_keys=True, indent=2)}"
            f"\nactual: {json.dumps(actual, ensure_ascii=False, sort_keys=True, indent=2)}"
        )


def decode_output(data: bytes, label: str, stream: str) -> str:
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError as error:
        raise RuntimeError(f"{label}: {stream} is not UTF-8: {error}") from error


def parse_stdout(process: subprocess.CompletedProcess[bytes], label: str) -> dict[str, Any]:
    stdout = decode_output(process.stdout, label, "stdout")
    try:
        result = json.loads(stdout, parse_constant=lambda value: (_ for _ in ()).throw(
            ValueError(f"non-JSON numeric constant {value}")))
    except (json.JSONDecodeError, ValueError) as error:
        raise RuntimeError(
            f"{label}: stdout was not JSON: {error}\nstdout:\n{stdout}\nstderr:\n"
            f"{decode_output(process.stderr, label, 'stderr')}"
        ) from error
    require(isinstance(result, dict), f"{label}: command result must be an object")
    return result


def invoke(executable: str, arguments: list[str], label: str) -> subprocess.CompletedProcess[bytes]:
    try:
        return subprocess.run(
            [executable, *arguments], check=False, capture_output=True, timeout=TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(f"{label}: command exceeded the {TIMEOUT_SECONDS}s fixture timeout") from error


def decode_scalar(value: Any) -> Any:
    if isinstance(value, dict) and set(value) == {"decimal"}:
        return Decimal(value["decimal"])
    if isinstance(value, dict) and set(value) == {"date"}:
        return dt.date.fromisoformat(value["date"])
    return value


def table_data_rows(data: dict[str, list[list[Any]]], table_name: str) -> list[list[Any]]:
    matches = [rows for name, rows in data.items() if name.casefold() == table_name.casefold()]
    require(len(matches) == 1, f"fixture data must define exactly one entry for table {table_name!r}")
    return matches[0]


def canonical_decimal(value: Decimal) -> str:
    if value == 0:
        return "0"
    rendered = format(value, "f")
    if "." in rendered:
        rendered = rendered.rstrip("0").rstrip(".")
    return rendered


def json_scalar(value: Any) -> Any:
    if isinstance(value, Decimal):
        return {"decimal": canonical_decimal(value)}
    if isinstance(value, dt.date):
        return {"date": value.isoformat()}
    if isinstance(value, (list, tuple)):
        return [json_scalar(item) for item in value]
    return value


def value_key(value: Any) -> str:
    return json_text(json_scalar(value))


def rows_key(rows: list[tuple[Any, ...]]) -> collections.Counter[str]:
    return collections.Counter(value_key(row) for row in rows)


def validate_expression_arena(result: dict[str, Any], label: str, source: str) -> None:
    expressions = result["expressions"]
    occurrences = result["occurrences"]
    parameters = result["parameters"]
    require(isinstance(expressions, list), f"{label}: expressions must be an array")
    require(isinstance(occurrences, list), f"{label}: occurrences must be an array")
    require(isinstance(parameters, list), f"{label}: parameters must be an array")
    for index, expression in enumerate(expressions):
        require(isinstance(expression, dict), f"{label}: expression {index} must be an object")
        require(type(expression.get("id")) is int and expression["id"] == index,
                f"{label}: expression IDs must be contiguous and ordered")
        sql_type = expression.get("type")
        require(isinstance(sql_type, dict) and sql_type.get("kind") in KNOWN_KINDS
                and type(sql_type.get("nullable")) is bool,
                f"{label}: expression {index} has an invalid SQL type")
        location = expression.get("location")
        require(location is None or (type(location) is int and 0 <= location <= len(source.encode("utf-8"))),
                f"{label}: expression {index} location is not a source byte offset")
        kind = expression.get("kind")
        if kind == "column":
            occurrence = expression.get("occurrence")
            column = expression.get("column")
            require(type(occurrence) is int and 0 <= occurrence < len(occurrences),
                    f"{label}: expression {index} references an invalid occurrence")
            require(type(column) is int and 0 <= column < len(occurrences[occurrence]["column_names"]),
                    f"{label}: expression {index} references an invalid column")
        elif kind == "literal":
            require("value" in expression, f"{label}: literal {index} has no value field")
        elif kind == "parameter":
            number = expression.get("number")
            require(type(number) is int and 1 <= number <= len(parameters),
                    f"{label}: expression {index} references an undeclared parameter")
        elif kind == "operation":
            operator = expression.get("operator")
            arguments = expression.get("arguments")
            require(operator in KNOWN_OPERATORS, f"{label}: expression {index} has an unknown operator {operator!r}")
            require(isinstance(arguments, list), f"{label}: operation {index} arguments must be an array")
            for argument in arguments:
                require(type(argument) is int and 0 <= argument < index,
                        f"{label}: expression {index} is not topologically ordered")
        else:
            raise RuntimeError(f"{label}: expression {index} has unknown kind {kind!r}")

    for index, predicate in enumerate(result["predicates"]):
        require(type(predicate) is int and 0 <= predicate < len(expressions),
                f"{label}: predicate {index} references an invalid expression")
    for index, output in enumerate(result["outputs"]):
        require(isinstance(output, dict) and isinstance(output.get("name"), str),
                f"{label}: output {index} has no name")
        expression = output.get("expression")
        require(type(expression) is int and 0 <= expression < len(expressions),
                f"{label}: output {index} references an invalid expression")


def sql_truth(value: Any) -> bool | None:
    if value is None:
        return None
    require(type(value) is bool, f"SQL predicate evaluated to non-Boolean value {value!r}")
    return value


def eval_expression(
    expression_id: int,
    expressions: list[dict[str, Any]],
    row: list[list[Any]],
    parameters: list[Any],
    memo: dict[int, Any],
) -> Any:
    if expression_id in memo:
        return memo[expression_id]
    expression = expressions[expression_id]
    kind = expression["kind"]
    if kind == "column":
        result = row[expression["occurrence"]][expression["column"]]
    elif kind == "literal":
        result = decode_scalar(expression["value"])
    elif kind == "parameter":
        result = parameters[expression["number"] - 1]
    else:
        arguments = [eval_expression(index, expressions, row, parameters, memo)
                     for index in expression["arguments"]]
        operator = expression["operator"]
        left = arguments[0] if arguments else None
        right = arguments[1] if len(arguments) > 1 else None
        if operator in {"equal", "not_equal", "less", "less_equal", "greater", "greater_equal"}:
            if left is None or right is None:
                result = None
            elif operator == "equal":
                result = left == right
            elif operator == "not_equal":
                result = left != right
            elif operator == "less":
                result = left < right
            elif operator == "less_equal":
                result = left <= right
            elif operator == "greater":
                result = left > right
            else:
                result = left >= right
        elif operator == "conjunction":
            truths = [sql_truth(value) for value in arguments]
            result = False if False in truths else None if None in truths else True
        elif operator == "disjunction":
            truths = [sql_truth(value) for value in arguments]
            result = True if True in truths else None if None in truths else False
        elif operator == "negation":
            truth = sql_truth(left)
            result = None if truth is None else not truth
        elif operator == "is_null":
            result = left is None
        elif operator == "is_not_null":
            result = left is not None
        elif operator == "is_true":
            result = sql_truth(left) is True
        elif operator == "is_not_true":
            result = sql_truth(left) is not True
        elif operator == "is_false":
            result = sql_truth(left) is False
        elif operator == "is_not_false":
            result = sql_truth(left) is not False
        elif operator == "is_unknown":
            result = sql_truth(left) is None
        elif operator == "is_not_unknown":
            result = sql_truth(left) is not None
        elif operator in {"identity_cast", "literal_cast", "widen_integer", "using_value"}:
            result = left
        else:
            raise RuntimeError(f"unsupported fixture interpreter operator {operator}")
    memo[expression_id] = result
    return result


def interpret(
    result: dict[str, Any],
    data: dict[str, list[list[Any]]],
    parameter_values: list[Any],
) -> tuple[list[tuple[Any, ...]], bool | None]:
    expressions = result["expressions"]
    occurrence_rows: list[list[list[Any]]] = []
    catalog_tables = result["catalog_binding"]["catalog"]["tables"]
    for occurrence in result["occurrences"]:
        table = catalog_tables[occurrence["table_id"]]
        raw_rows = table_data_rows(data, table["name"])
        converted = [[decode_scalar(value) for value in item] for item in raw_rows]
        require(all(len(item) == len(table["columns"]) for item in converted),
                f"fixture data for {table['name']} has a row with the wrong arity")
        occurrence_rows.append(converted)

    product = itertools.product(*occurrence_rows) if occurrence_rows else [()]
    projected: list[tuple[Any, ...]] = []
    for raw_row in product:
        row = list(raw_row)
        memo: dict[int, Any] = {}
        if any(sql_truth(eval_expression(predicate, expressions, row, parameter_values, memo)) is not True
               for predicate in result["predicates"]):
            continue
        projected.append(tuple(eval_expression(output["expression"], expressions, row, parameter_values, memo)
                               for output in result["outputs"]))

    if result["result_wrapper"] == "exists":
        return [], bool(projected)
    if result["requested_semantics"] == "set":
        unique: dict[str, tuple[Any, ...]] = {}
        for row in projected:
            unique.setdefault(value_key(row), row)
        projected = list(unique.values())
    return projected, None


def expected_rows(case: dict[str, Any], fixture: dict[str, Any]) -> list[tuple[Any, ...]]:
    if "expected_rows" in fixture:
        return [tuple(decode_scalar(value) for value in row) for row in fixture["expected_rows"]]
    return []


def validate_expected_rows(case: dict[str, Any], fixture: dict[str, Any], actual_rows: list[tuple[Any, ...]]) -> None:
    if "expected_rows" not in fixture:
        return
    expected = expected_rows(case, fixture)
    compare(f"{case['name']}: manual output multiset", rows_key(actual_rows), rows_key(expected))


def offset_coordinates(source: str, byte_offset: int) -> tuple[int, int, int]:
    encoded = source.encode("utf-8")
    prefix = encoded[:byte_offset].decode("utf-8")
    line = prefix.count("\n") + 1
    column = len(prefix.rsplit("\n", 1)[-1]) + 1
    character_position = len(prefix) + 1
    return character_position, line, column


def check_location_marker(case: dict[str, Any], diagnostic: dict[str, Any], source: str) -> None:
    marker = case.get("location_marker")
    if marker is None:
        return
    require(isinstance(marker, str) and marker, f"{case['name']}: invalid location marker")
    position = source.find(marker)
    require(position >= 0, f"{case['name']}: location marker {marker!r} not found in SQL source")
    expected_offset = len(source[:position].encode("utf-8"))
    require(diagnostic.get("byte_offset") == expected_offset,
            f"{case['name']}: expected byte offset {expected_offset}, got {diagnostic.get('byte_offset')!r}")
    character_position, line, column = offset_coordinates(source, expected_offset)
    compare(f"{case['name']}: Unicode-aware diagnostic coordinates",
            {key: diagnostic.get(key) for key in ("character_position", "line", "column")},
            {"character_position": character_position, "line": line, "column": column})


def run_binding(executable: str, base: Path, case: dict[str, Any], catalog_path: Path) -> tuple[dict[str, Any], str]:
    source_path = (base / case["sql"]).resolve()
    require(source_path.is_relative_to(base.resolve()), f"{case['name']}: SQL path escapes fixture directory")
    try:
        source = source_path.read_text(encoding="utf-8")
    except (OSError, UnicodeError) as error:
        raise RuntimeError(f"{case['name']}: cannot read SQL fixture: {error}") from error
    arguments = ["bind-sql", str(source_path), str(catalog_path)]
    parameter_path = case.get("parameters")
    if parameter_path:
        resolved_parameter_path = (base / parameter_path).resolve()
        require(resolved_parameter_path.is_relative_to(base.resolve()),
                f"{case['name']}: parameter path escapes fixture directory")
        arguments.append(str(resolved_parameter_path))
    process = invoke(executable, arguments, case["name"])
    require(not process.stderr, f"{case['name']}: bind-sql wrote stderr: {decode_output(process.stderr, case['name'], 'stderr')}")
    return parse_stdout(process, case["name"]), source


def validate_occurrences(result: dict[str, Any], expected: list[dict[str, Any]], label: str) -> None:
    actual = result["occurrences"]
    require(len(actual) == len(expected), f"{label}: expected {len(expected)} occurrences, got {len(actual)}")
    for index, (item, wanted) in enumerate(zip(actual, expected)):
        compare(f"{label}: occurrence {index} table and alias",
                {"table": item.get("table"), "alias": item.get("alias")},
                {"table": wanted.get("table"), "alias": wanted.get("alias")})
        include_descendants = wanted.get("include_descendants", True)
        compare(f"{label}: occurrence {index} inheritance flag", item.get("include_descendants"), include_descendants)
        require(type(item.get("table_id")) is int and item["table_id"] >= 0,
                f"{label}: occurrence {index} table_id must be a nonnegative integer")
        require(isinstance(item.get("column_names"), list)
                and all(isinstance(name, str) for name in item["column_names"]),
                f"{label}: occurrence {index} column_names must be strings")
        location = item.get("location")
        require(location is None or (type(location) is int and location >= 0),
                f"{label}: occurrence {index} has an invalid source location")


def validate_success(
    executable: str,
    base: Path,
    catalog_path: Path,
    canonical_catalog: dict[str, Any],
    data: dict[str, list[list[Any]]],
    case: dict[str, Any],
) -> list[tuple[Any, ...]]:
    label = case["name"]
    result, source = run_binding(executable, base, case, catalog_path)
    require(result.keys() == SUCCESS_FIELDS, f"{label}: unexpected success fields: {sorted(result)}")
    compare(f"{label}: common envelope", {key: result[key] for key in ("schema_version", "admission_status", "binding_valid")},
            {"schema_version": 1, "admission_status": "not_checked", "binding_valid": True})
    compare(f"{label}: preserved source", result.get("source"), source)
    compare(f"{label}: canonical catalog snapshot", result.get("catalog_binding"), canonical_catalog)
    compare(f"{label}: explicit flat catalog policy", result.get("catalog_inheritance"), "none")
    validate_expression_arena(result, label, source)

    expected = case["expected"]
    for field in ("requested_semantics", "inner_semantics", "result_wrapper", "wrapper_alias"):
        if field in expected:
            compare(f"{label}: {field}", result.get(field), expected[field])
    if "wrapper_alias" not in expected:
        compare(f"{label}: default wrapper alias", result.get("wrapper_alias"), "exists")
    validate_occurrences(result, expected.get("occurrences", []), label)
    actual_output_names = [item["name"] for item in result["outputs"]]
    if "output_names" in expected:
        compare(f"{label}: output names", actual_output_names, expected["output_names"])
    if expected.get("output_names_from_table"):
        table_names = {table["name"]: [column["name"] for column in table["columns"]]
                       for table in canonical_catalog["catalog"]["tables"]}
        compare(f"{label}: wildcard column names", actual_output_names,
                table_names[expected["output_names_from_table"]])
    if "parameters" in expected:
        actual_parameters = [{"kind": item.get("kind"), "nullable": item.get("nullable")}
                             for item in result["parameters"]]
        compare(f"{label}: parameter types", actual_parameters, expected["parameters"])

    operators = {item["operator"] for item in result["expressions"] if item["kind"] == "operation"}
    require(set(expected.get("operators", [])).issubset(operators),
            f"{label}: expected operators {sorted(set(expected.get('operators', [])) - operators)}, found {sorted(operators)}")
    if "type_kinds" in expected:
        output_kinds = [result["expressions"][item["expression"]]["type"]["kind"] for item in result["outputs"]]
        compare(f"{label}: output type kinds", output_kinds, expected["type_kinds"])

    rows, exists_value = interpret(result, data, [decode_scalar(value) for value in case.get("parameter_values", [])])
    if result["result_wrapper"] == "exists":
        compare(f"{label}: EXISTS result", exists_value, expected["exists_result"])
    else:
        if "row_count" in expected:
            compare(f"{label}: output row count", len(rows), expected["row_count"])
        validate_expected_rows(case, expected, rows)

    if expected.get("sqlite_oracle", False):
        sqlite_rows, sqlite_names = run_sqlite(case, source, canonical_catalog, data,
                                               [decode_scalar(value) for value in case.get("parameter_values", [])],
                                               result)
        expected_sqlite_names = ([result["wrapper_alias"]] if result["result_wrapper"] == "exists"
                                  else actual_output_names)
        compare(f"{label}: SQLite output column names", sqlite_names, expected_sqlite_names)
        if result["result_wrapper"] == "exists":
            require(len(sqlite_rows) == 1 and len(sqlite_rows[0]) == 1,
                    f"{label}: SQLite EXISTS wrapper did not return one Boolean")
            sqlite_exists = sqlite_rows[0][0]
            compare(f"{label}: SQLite EXISTS result", sqlite_exists, exists_value)
        else:
            compare(f"{label}: independent SQLite row multiset", rows_key(sqlite_rows), rows_key(rows))
    return rows


def sqlite_value(value: Any) -> Any:
    if isinstance(value, Decimal):
        return format(value, "f")
    if isinstance(value, dt.date):
        return value.isoformat()
    if isinstance(value, bool):
        return int(value)
    return value


def sqlite_typed_value(value: Any, sql_type: dict[str, Any]) -> Any:
    if value is None:
        return None
    kind = sql_type["kind"]
    if kind == "bool":
        return bool(value)
    if kind == "decimal":
        return Decimal(str(value))
    if kind == "date":
        return dt.date.fromisoformat(str(value))
    return value


def quote_identifier(name: str) -> str:
    return '"' + name.replace('"', '""') + '"'


def run_sqlite(
    case: dict[str, Any],
    source: str,
    catalog: dict[str, Any],
    data: dict[str, list[list[Any]]],
    parameter_values: list[Any],
    bound: dict[str, Any],
) -> tuple[list[tuple[Any, ...]], list[str]]:
    connection = sqlite3.connect(":memory:")
    try:
        used_table_ids = {item["table_id"] for item in bound["occurrences"]}
        for table_id, table in enumerate(catalog["catalog"]["tables"]):
            if table_id not in used_table_ids:
                continue
            columns = table["columns"]
            require(bool(columns), f"{case['name']}: SQLite oracle cannot create a zero-column table")
            type_map = {"int64": "INTEGER", "string": "TEXT", "bool": "BOOLEAN", "date": "TEXT", "decimal": "TEXT"}
            declarations = ", ".join(f"{quote_identifier(column['name'])} {type_map[column['type']]}" for column in columns)
            connection.execute(f"CREATE TABLE {quote_identifier(table['name'])} ({declarations})")
            raw_rows = table_data_rows(data, table["name"])
            placeholders = ", ".join("?" for _ in columns)
            if raw_rows:
                connection.executemany(
                    f"INSERT INTO {quote_identifier(table['name'])} VALUES ({placeholders})",
                    [[sqlite_value(decode_scalar(value)) for value in row] for row in raw_rows],
                )
        sql = re.sub(r"\$[0-9]+", "?", source)
        try:
            cursor = connection.execute(sql, tuple(sqlite_value(item) for item in parameter_values))
        except sqlite3.Error as error:
            raise RuntimeError(f"{case['name']}: SQLite oracle rejected fixture SQL: {error}") from error
        names = [column[0] for column in cursor.description or []]
        rows = []
        for raw in cursor.fetchall():
            row = []
            for index, value in enumerate(raw):
                if bound["result_wrapper"] == "exists":
                    sql_type = {"kind": "bool"}
                else:
                    sql_type = bound["expressions"][bound["outputs"][index]["expression"]]["type"]
                row.append(sqlite_typed_value(value, sql_type))
            rows.append(tuple(row))
        return rows, names
    finally:
        connection.close()


def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict[str, Any]) -> None:
    label = case["name"]
    result, source = run_binding(executable, base, case, catalog_path)
    require(result.keys() == FAILURE_FIELDS, f"{label}: unexpected failure fields: {sorted(result)}")
    compare(f"{label}: failure envelope",
            {key: result.get(key) for key in ("schema_version", "admission_status", "binding_valid", "phase")},
            {"schema_version": 1, "admission_status": "not_checked", "binding_valid": False,
             "phase": case["phase"]})
    diagnostic = result.get("diagnostic")
    require(isinstance(diagnostic, dict), f"{label}: diagnostic must be an object")
    require(set(diagnostic) == {"code", "message", "byte_offset", "character_position", "line", "column"},
            f"{label}: diagnostic has unexpected fields {sorted(diagnostic)}")
    compare(f"{label}: diagnostic code", diagnostic.get("code"), case["code"])
    require(isinstance(diagnostic.get("message"), str) and diagnostic["message"],
            f"{label}: diagnostic message must be nonempty")
    check_location_marker(case, diagnostic, source)


def validate_cli_errors(executable: str, base: Path, catalog_path: Path,
                        manifest: dict[str, Any]) -> None:
    for case in manifest.get("cli_error_cases", []):
        label = case["name"]
        replacements = case.get("replace", {})
        arguments = []
        for item in case["args"]:
            if item in replacements:
                replacement = replacements[item]
                if replacement == "catalog.json":
                    arguments.append(str(catalog_path))
                elif isinstance(replacement, str) and (replacement.startswith("cases/")
                                                       or replacement.startswith("parameters/")):
                    relative = (base / replacement).resolve()
                    require(relative.is_relative_to(base), f"{label}: fixture path escapes fixture directory")
                    arguments.append(str(relative))
                else:
                    arguments.append(replacement)
            elif item == "MISSING_SQL":
                arguments.append(str(base / "does-not-exist.sql"))
            elif item == "MISSING_CATALOG":
                arguments.append(str(base / "does-not-exist-catalog.json"))
            else:
                arguments.append(item)
        process = invoke(executable, arguments, label)
        require(process.returncode == 2, f"{label}: expected exit 2, got {process.returncode}")
        stdout = decode_output(process.stdout, label, "stdout")
        require(not stdout, f"{label}: CLI usage/file error wrote stdout: {stdout!r}")
        stderr = decode_output(process.stderr, label, "stderr")
        try:
            error_payload = json.loads(stderr)
        except json.JSONDecodeError as error:
            raise RuntimeError(f"{label}: stderr was not structured JSON: {stderr!r}") from error
        require(isinstance(error_payload, dict) and isinstance(error_payload.get("error"), dict),
                f"{label}: missing structured CLI error")
        compare(f"{label}: CLI error code", error_payload["error"].get("code"), case["stderr_code"])


def main() -> int:
    if len(sys.argv) != 3:
        raise RuntimeError("usage: binding.py EXECUTABLE FIXTURE_DIRECTORY")
    executable = sys.argv[1]
    base = Path(sys.argv[2]).resolve()
    manifest = read_json(base / "manifest.json")
    require(isinstance(manifest, dict) and type(manifest.get("schema_version")) is int
            and manifest["schema_version"] == 1, "binding fixture manifest must have schema_version 1")
    successes = manifest.get("success_cases")
    failures = manifest.get("failure_cases")
    require(isinstance(successes, list) and successes, "manifest success_cases must be a nonempty array")
    require(isinstance(failures, list) and failures, "manifest failure_cases must be a nonempty array")
    catalog_path = (base / manifest["catalog"]).resolve()
    require(catalog_path.is_relative_to(base), "catalog path escapes fixture directory")
    canonical_process = invoke(executable, ["canonicalize-catalog", str(catalog_path)], "canonical fixture catalog")
    require(canonical_process.returncode == 0, "canonical fixture catalog was rejected")
    require(not canonical_process.stderr, "canonicalize-catalog wrote unexpected stderr")
    canonical_catalog = parse_stdout(canonical_process, "canonical fixture catalog")
    data = read_json((base / manifest["data"]).resolve())
    require(isinstance(data, dict), "fixture data must be an object")

    names: set[str] = set()
    success_rows: dict[str, list[tuple[Any, ...]]] = {}
    pending_row_equivalence: list[tuple[str, str]] = []
    for case in successes:
        require(isinstance(case, dict), "success case must be an object")
        name = case.get("name")
        require(isinstance(name, str) and name and name not in names, f"duplicate or invalid case name {name!r}")
        names.add(name)
        require(isinstance(case.get("expected"), dict), f"{name}: expected must be an object")
        success_rows[name] = validate_success(executable, base, catalog_path, canonical_catalog, data, case)
        same_rows_as = case["expected"].get("same_rows_as")
        if same_rows_as is not None:
            require(isinstance(same_rows_as, str), f"{name}: same_rows_as must be a case name")
            pending_row_equivalence.append((name, same_rows_as))
    for name, same_rows_as in pending_row_equivalence:
        require(same_rows_as in success_rows, f"{name}: same_rows_as names an unknown success case")
        compare(f"{name}: flat scan row equivalence", rows_key(success_rows[name]),
                rows_key(success_rows[same_rows_as]))
    for case in failures:
        require(isinstance(case, dict), "failure case must be an object")
        name = case.get("name")
        require(isinstance(name, str) and name and name not in names, f"duplicate or invalid case name {name!r}")
        names.add(name)
        validate_failure(executable, base, catalog_path, case)
    validate_cli_errors(executable, base, catalog_path, manifest)
    print(f"{len(successes)} binding success cases, {len(failures)} diagnostics, and "
          f"{len(manifest.get('cli_error_cases', []))} CLI errors passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"SQL binding fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
