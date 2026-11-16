#!/usr/bin/env python3
"""Check the bounded SQL normalizer against manual rows and independent oracles."""

from __future__ import annotations

import copy
import datetime as dt
import json
import sqlite3
import subprocess
import sys
import tempfile
from decimal import Decimal
from pathlib import Path
from typing import Any

from binding import (
    FAILURE_FIELDS as BINDING_FAILURE_FIELDS,
    SUCCESS_FIELDS as BINDING_SUCCESS_FIELDS,
    compare,
    decode_output,
    decode_scalar,
    eval_expression,
    invoke,
    json_scalar,
    json_text,
    parse_stdout,
    read_json,
    rows_key,
    sql_truth,
    table_data_rows,
)


TIMEOUT_SECONDS = 20
NORMALIZATION_SUCCESS_FIELDS = {
    "schema_version", "normalization_valid", "admission_status", "binding", "parameter_values",
    "core", "adapters", "base_routes", "outputs", "limits", "work",
}
NORMALIZATION_FAILURE_FIELDS = {
    "schema_version", "normalization_valid", "admission_status", "phase", "diagnostic",
}
KNOWN_KINDS = {"unknown", "int32", "int64", "string", "bool", "date", "decimal"}


def require(condition: bool, message: str) -> None:
    # Fixture checks must stay enabled under ``python -O``.
    if not condition:
        raise RuntimeError(message)


def canonical_decimal(value: Decimal) -> str:
    if value == 0:
        return "0"
    rendered = format(value, "f")
    if "." in rendered:
        rendered = rendered.rstrip("0").rstrip(".")
    return rendered


def canonical_json_scalar(value: Any) -> Any:
    if isinstance(value, Decimal):
        return {"decimal": canonical_decimal(value)}
    if isinstance(value, dt.date):
        return {"date": value.isoformat()}
    if isinstance(value, (list, tuple)):
        return [canonical_json_scalar(item) for item in value]
    if isinstance(value, dict) and set(value) == {"decimal"}:
        return {"decimal": canonical_decimal(Decimal(value["decimal"]))}
    if isinstance(value, dict) and set(value) == {"date"}:
        return {"date": dt.date.fromisoformat(value["date"]).isoformat()}
    return value


def check_success_binding(binding: dict[str, Any], source: str, label: str) -> None:
    require(binding.keys() == BINDING_SUCCESS_FIELDS,
            f"{label}: binding has unexpected fields: {sorted(binding)}")
    compare(f"{label}: binding envelope",
            {key: binding.get(key) for key in ("schema_version", "admission_status", "binding_valid")},
            {"schema_version": 1, "admission_status": "not_checked", "binding_valid": True})
    compare(f"{label}: bound SQL source", binding.get("source"), source)
    require(isinstance(binding.get("catalog_binding"), dict), f"{label}: binding omitted catalog")
    require(isinstance(binding.get("occurrences"), list), f"{label}: binding occurrences must be an array")
    require(isinstance(binding.get("expressions"), list), f"{label}: binding expressions must be an array")
    require(isinstance(binding.get("predicates"), list), f"{label}: binding predicates must be an array")
    require(isinstance(binding.get("outputs"), list), f"{label}: binding outputs must be an array")
    require(isinstance(binding.get("parameters"), list), f"{label}: binding parameters must be an array")
    for index, expression in enumerate(binding["expressions"]):
        require(isinstance(expression, dict), f"{label}: binding expression {index} must be an object")
        require(type(expression.get("id")) is int and expression["id"] == index,
                f"{label}: binding expression IDs must be contiguous")
        sql_type = expression.get("type")
        require(isinstance(sql_type, dict) and sql_type.get("kind") in KNOWN_KINDS
                and type(sql_type.get("nullable")) is bool,
                f"{label}: binding expression {index} has an invalid SQL type")
        kind = expression.get("kind")
        if kind == "column":
            occurrence, column = expression.get("occurrence"), expression.get("column")
            require(type(occurrence) is int and 0 <= occurrence < len(binding["occurrences"]),
                    f"{label}: binding expression {index} references an invalid occurrence")
            columns = binding["occurrences"][occurrence].get("column_names")
            require(isinstance(columns, list) and type(column) is int and 0 <= column < len(columns),
                    f"{label}: binding expression {index} references an invalid column")
        elif kind == "literal":
            require("value" in expression, f"{label}: binding literal {index} has no value")
        elif kind == "parameter":
            number = expression.get("number")
            require(type(number) is int and 1 <= number <= len(binding["parameters"]),
                    f"{label}: binding expression {index} references an invalid parameter")
        elif kind == "operation":
            arguments = expression.get("arguments")
            require(isinstance(arguments, list), f"{label}: operation {index} arguments must be an array")
            for argument in arguments:
                require(type(argument) is int and 0 <= argument < index,
                        f"{label}: binding expression {index} is not topologically ordered")
        else:
            raise RuntimeError(f"{label}: binding expression {index} has unknown kind {kind!r}")


def case_path(base: Path, relative: str, label: str) -> Path:
    result = (base / relative).resolve()
    require(result.is_relative_to(base.resolve()), f"{label}: fixture path escapes fixture directory")
    return result


def invoke_normalize(executable: str, base: Path, catalog: Path, case: dict[str, Any]) -> tuple[dict[str, Any], str]:
    label = case["name"]
    sql_path = case_path(base, case["sql"], label)
    try:
        source = sql_path.read_text(encoding="utf-8")
    except (OSError, UnicodeError) as error:
        raise RuntimeError(f"{label}: cannot read SQL fixture: {error}") from error
    arguments = ["normalize-sql", str(sql_path), str(catalog)]
    type_path = case.get("parameter_types")
    values_path = case.get("parameter_values")
    if values_path:
        require(type_path is not None, f"{label}: parameter values require a parameter type document")
    if type_path:
        arguments.append(str(case_path(base, type_path, label)))
    if values_path:
        arguments.append(str(case_path(base, values_path, label)))
    process = invoke(executable, arguments, label)
    require(not process.stderr,
            f"{label}: normalize-sql wrote stderr: {decode_output(process.stderr, label, 'stderr')}")
    result = parse_stdout(process, label)
    expected_exit = 1 if "code" in case else 0
    require(process.returncode == expected_exit,
            f"{label}: expected exit {expected_exit}, got {process.returncode}")
    return result, source


def validate_routes(result: dict[str, Any], expected_occurrences: list[dict[str, str]],
                    expected: dict[str, Any], label: str) -> None:
    binding = result["binding"]
    actual_occurrences = binding["occurrences"]
    require(len(actual_occurrences) == len(expected_occurrences),
            f"{label}: expected {len(expected_occurrences)} bound occurrences, got {len(actual_occurrences)}")
    for index, (actual, expected_occurrence) in enumerate(zip(actual_occurrences, expected_occurrences, strict=True)):
        compare(f"{label}: bound occurrence {index}",
                {key: actual.get(key) for key in ("table", "alias")}, expected_occurrence)

    routes = result["base_routes"]
    catalog_tables = binding["catalog_binding"]["catalog"]["tables"]
    require(isinstance(routes, list) and len(routes) == len(catalog_tables),
            f"{label}: base_routes must have one entry per physical catalog table")
    expected_routes: list[list[int]] = [[] for _ in catalog_tables]
    for occurrence_id, occurrence in enumerate(actual_occurrences):
        table_id = occurrence.get("table_id")
        require(type(table_id) is int and 0 <= table_id < len(expected_routes),
                f"{label}: occurrence {occurrence_id} has invalid table_id")
        expected_routes[table_id].append(occurrence_id)
    compare(f"{label}: occurrence-to-base routing", routes, expected_routes)

    adapters = result["adapters"]
    require(isinstance(adapters, list) and len(adapters) == len(actual_occurrences),
            f"{label}: one adapter is required for each occurrence")
    core = result["core"]
    atoms = core["query"]["atoms"]
    core_tables = core["catalog"]["tables"]
    require(len(atoms) == len(adapters) == len(core_tables),
            f"{label}: every occurrence must retain one core atom and adapter")
    for index, (adapter, occurrence, atom, table) in enumerate(
        zip(adapters, actual_occurrences, atoms, core_tables, strict=True)
    ):
        require(set(adapter) == {"occurrence", "base", "predicates", "non_null_columns", "equal_columns",
                                "column_classes", "projection", "program", "constant_columns"},
                f"{label}: adapter {index} has unexpected fields")
        compare(f"{label}: adapter {index} identity",
                {"occurrence": adapter.get("occurrence"), "base": adapter.get("base")},
                {"occurrence": index, "base": occurrence.get("table_id")})
        require(atom.get("table") == table.get("name") == f"occurrence_{index}",
                f"{label}: core atom {index} is not routed through its occurrence relation")
        require(adapter.get("predicates") == sorted(set(adapter.get("predicates", []))),
                f"{label}: adapter {index} predicates must be unique and ordered")
        require(adapter.get("program") == sorted(set(adapter.get("program", []))),
                f"{label}: adapter {index} program must be unique and ordered")
        expressions = binding["expressions"]
        for expression_id in adapter["predicates"] + adapter["program"]:
            require(type(expression_id) is int and 0 <= expression_id < len(expressions),
                    f"{label}: adapter {index} references an invalid expression")
        base_schema = binding["catalog_binding"]["catalog"]["tables"][adapter["base"]]
        arity = len(base_schema["columns"])
        classes = adapter["column_classes"]
        require(isinstance(classes, list) and len(classes) == arity,
                f"{label}: adapter {index} column_classes has the wrong arity")
        for var_id in classes:
            require(var_id is None or (type(var_id) is int and var_id >= 0),
                    f"{label}: adapter {index} has invalid variable class {var_id!r}")
        non_null_columns = adapter["non_null_columns"]
        require(non_null_columns == sorted(set(non_null_columns)),
                f"{label}: adapter {index} non-null checks must be unique and ordered")
        for column in non_null_columns:
            require(type(column) is int and 0 <= column < arity,
                    f"{label}: adapter {index} has an invalid non-null check")
        for equality in adapter["equal_columns"]:
            require(set(equality) == {"left", "right"}
                    and type(equality["left"]) is int and type(equality["right"]) is int
                    and 0 <= equality["left"] < arity and 0 <= equality["right"] < arity,
                    f"{label}: adapter {index} has an invalid repeated-column equality")
        projections = adapter["projection"]
        require(isinstance(projections, list), f"{label}: adapter {index} projection must be an array")
        for projection in projections:
            require(set(projection) == {"variable", "expression"}
                    and type(projection["variable"]) is int and projection["variable"] >= 0
                    and type(projection["expression"]) is int
                    and 0 <= projection["expression"] < len(expressions),
                    f"{label}: adapter {index} has an invalid projection")
        term_variables = [term["var"] for term in atom["terms"]]
        variable_names = [variable["name"] for variable in core["query"]["variables"]]
        projected_names = [variable_names[item["variable"]] for item in projections]
        compare(f"{label}: adapter {index} projection matches core atom order", projected_names, term_variables)
        require(len(table["columns"]) == len(projections),
                f"{label}: adapter {index} projected schema and core atom arity differ")
        if "equal_column_pairs" in expected:
            if index == 0:
                compare(f"{label}: repeated physical-column equalities",
                        [[item["left"], item["right"]] for item in adapter["equal_columns"]],
                        expected["equal_column_pairs"])
        if "null_class_columns" in expected:
            if index == 0:
                compare(f"{label}: unprojected physical columns",
                        [[column for column, variable in enumerate(classes) if variable is None]],
                        expected["null_class_columns"])


def validate_core_document(core: dict[str, Any], label: str) -> None:
    require(core.get("schema_version") == 3, f"{label}: normalized core must use CQ document schema version 3")
    compare(f"{label}: normalized core semantics", core.get("semantics"), "set")
    require(isinstance(core.get("catalog"), dict) and isinstance(core.get("query"), dict),
            f"{label}: normalized core omitted catalog or query")
    require(core.get("updates") == [], f"{label}: normalized core must have no updates")
    initial = core.get("initial")
    require(isinstance(initial, list), f"{label}: normalized core initial relations must be an array")
    for item in initial:
        require(isinstance(item, dict) and isinstance(item.get("rows"), list),
                f"{label}: malformed normalized core initial relation")
        require(item["rows"] == [], f"{label}: normalized core must start with empty relations")
    query = core["query"]
    require(isinstance(query.get("variables"), list) and isinstance(query.get("atoms"), list)
            and isinstance(query.get("head"), list), f"{label}: malformed normalized core query")


def run_adapters(result: dict[str, Any], data: dict[str, Any], parameter_values: list[Any], label: str) -> dict[str, list[list[Any]]]:
    binding = result["binding"]
    expressions = binding["expressions"]
    occurrence_count = len(binding["occurrences"])
    adapters = result["adapters"]
    adapted: dict[str, list[list[Any]]] = {}
    for index, adapter in enumerate(adapters):
        occurrence = binding["occurrences"][adapter["occurrence"]]
        base_schema = binding["catalog_binding"]["catalog"]["tables"][adapter["base"]]
        raw_rows = table_data_rows(data, base_schema["name"])
        source_rows = [[decode_scalar(value) for value in row] for row in raw_rows]
        require(all(len(row) == len(base_schema["columns"]) for row in source_rows),
                f"{label}: static rows for {base_schema['name']} have inconsistent arity")
        projected: dict[str, list[Any]] = {}
        for raw in source_rows:
            if any(raw[fixed["column"]] != decode_scalar(fixed["value"])
                   for fixed in adapter["constant_columns"]):
                continue
            if any(raw[column] is None for column in adapter["non_null_columns"]):
                continue
            if any(raw[equality["left"]] is None or raw[equality["right"]] is None
                   or raw[equality["left"]] != raw[equality["right"]]
                   for equality in adapter["equal_columns"]):
                continue
            row_context: list[list[Any]] = [[] for _ in range(occurrence_count)]
            row_context[adapter["occurrence"]] = raw
            memo: dict[int, Any] = {}
            if any(sql_truth(eval_expression(predicate, expressions, row_context, parameter_values, memo)) is not True
                   for predicate in adapter["predicates"]):
                continue
            item = [eval_expression(projection["expression"], expressions, row_context, parameter_values, memo)
                    for projection in adapter["projection"]]
            require(all(value is not None for value in item),
                    f"{label}: adapter {index} projected NULL into the classical core")
            projected.setdefault(json_text(canonical_json_scalar(item)), item)
        relation_name = f"occurrence_{index}"
        adapted[relation_name] = list(projected.values())
    return adapted


def invoke_core_oracle(executable: str, core: dict[str, Any], adapted: dict[str, list[list[Any]]], label: str) -> list[list[Any]]:
    oracle_document = copy.deepcopy(core)
    oracle_document["initial"] = [
        {"table": table["name"], "rows": [json_scalar(row) for row in adapted.get(table["name"], [])]}
        for table in oracle_document["catalog"]["tables"]
    ]
    oracle_document["updates"] = []
    with tempfile.TemporaryDirectory(prefix="crown-normalization-") as temporary:
        path = Path(temporary) / "core.json"
        path.write_text(json.dumps(oracle_document, ensure_ascii=False) + "\n", encoding="utf-8")
        process = invoke(executable, ["oracle", str(path)], f"{label} core oracle")
    require(process.returncode == 0,
            f"{label}: core oracle exited {process.returncode}: {decode_output(process.stderr, label, 'stderr')}")
    require(not process.stderr, f"{label}: core oracle wrote stderr")
    result = parse_stdout(process, f"{label} core oracle")
    require(result.get("semantics") == "set", f"{label}: core oracle did not return set semantics")
    rows = result.get("initial")
    require(isinstance(rows, list), f"{label}: core oracle initial result must be an array")
    return rows


def map_outputs(result: dict[str, Any], core_rows: list[list[Any]], label: str) -> list[list[Any]]:
    binding = result["binding"]
    if binding["result_wrapper"] == "exists":
        require(result["outputs"] == [], f"{label}: EXISTS wrapper must not invent core output columns")
        require(all(row == [] for row in core_rows), f"{label}: EXISTS core result must be nullary")
        return [[bool(core_rows)]]
    outputs = result["outputs"]
    mapped = []
    for row in core_rows:
        visible = []
        for output in outputs:
            if output["kind"] == "core":
                column = output.get("column")
                require(type(column) is int and 0 <= column < len(row),
                        f"{label}: output maps to an invalid core column")
                visible.append(row[column])
            elif output["kind"] == "constant":
                require("value" in output, f"{label}: constant output has no value")
                visible.append(decode_scalar(output["value"]))
            else:
                raise RuntimeError(f"{label}: unknown output kind {output.get('kind')!r}")
        mapped.append(visible)
    return mapped


def sqlite_value(value: Any) -> Any:
    if isinstance(value, Decimal):
        return canonical_decimal(value)
    if isinstance(value, dt.date):
        return value.isoformat()
    if isinstance(value, bool):
        return int(value)
    return value


def sqlite_typed_value(value: Any, kind: str) -> Any:
    if value is None:
        return None
    if kind == "bool":
        return bool(value)
    if kind == "decimal":
        return Decimal(str(value))
    if kind == "date":
        return dt.date.fromisoformat(str(value))
    return value


def quote_identifier(name: str) -> str:
    return '"' + name.replace('"', '""') + '"'


def run_sqlite(case: dict[str, Any], source: str, catalog: dict[str, Any], data: dict[str, Any],
               parameter_values: list[Any], binding: dict[str, Any], normalization: dict[str, Any],
               label: str) -> tuple[list[list[Any]], list[str]]:
    connection = sqlite3.connect(":memory:")
    try:
        used = {occurrence["table"].casefold() for occurrence in binding["occurrences"]}
        type_map = {"int64": "INTEGER", "string": "TEXT", "bool": "BOOLEAN", "date": "TEXT", "decimal": "TEXT"}
        for table in catalog["catalog"]["tables"]:
            if table["name"].casefold() not in used:
                continue
            columns = table["columns"]
            require(bool(columns), f"{label}: SQLite crosscheck does not create zero-column tables")
            declarations = ", ".join(
                f"{quote_identifier(column['name'])} {type_map[column['type']]}" for column in columns
            )
            connection.execute(f"CREATE TABLE {quote_identifier(table['name'])} ({declarations})")
            rows = table_data_rows(data, table["name"])
            placeholders = ", ".join("?" for _ in columns)
            if rows:
                connection.executemany(
                    f"INSERT INTO {quote_identifier(table['name'])} VALUES ({placeholders})",
                    [[sqlite_value(decode_scalar(value)) for value in row] for row in rows],
                )
        try:
            named_parameters = {str(index + 1): sqlite_value(value)
                                for index, value in enumerate(parameter_values)}
            cursor = connection.execute(source, named_parameters)
        except sqlite3.Error as error:
            raise RuntimeError(f"{label}: SQLite rejected fixture SQL: {error}") from error
        names = [column[0] for column in cursor.description or []]
        raw_rows = cursor.fetchall()
        output_types = ([{"kind": "bool"}] if binding["result_wrapper"] == "exists"
                        else [output["type"] for output in normalization["outputs"]])
        rows: list[list[Any]] = []
        for raw in raw_rows:
            rows.append([sqlite_typed_value(value, output_types[index]["kind"])
                         for index, value in enumerate(raw)])
        return rows, names
    finally:
        connection.close()


def validate_success(executable: str, base: Path, catalog_path: Path, catalog: dict[str, Any],
                     data: dict[str, Any], case: dict[str, Any]) -> list[list[Any]]:
    label = case["name"]
    result, source = invoke_normalize(executable, base, catalog_path, case)
    require(result.keys() == NORMALIZATION_SUCCESS_FIELDS,
            f"{label}: unexpected success fields: {sorted(result)}")
    compare(f"{label}: success envelope",
            {key: result.get(key) for key in ("schema_version", "normalization_valid", "admission_status")},
            {"schema_version": 2, "normalization_valid": True, "admission_status": "not_checked"})
    binding = result["binding"]
    check_success_binding(binding, source, label)
    compare(f"{label}: binding occurrence identities", [
        {"table": item["table"], "alias": item["alias"]} for item in binding["occurrences"]
    ], case["expected"]["occurrences"])
    actual_output_names = ([binding["wrapper_alias"]] if binding["result_wrapper"] == "exists"
                           else [item["name"] for item in binding["outputs"]])
    if "output_names" in case["expected"]:
        compare(f"{label}: bound output names", actual_output_names, case["expected"]["output_names"])
    expected_requested = case["expected"].get("requested_semantics", "set")
    compare(f"{label}: bound requested semantics", binding["requested_semantics"], expected_requested)
    compare(f"{label}: normalized parameter values",
            canonical_json_scalar(result["parameter_values"]),
            canonical_json_scalar(case.get("expected_parameter_values", case.get("parameter_values_raw", []))))
    normalized_outputs = result["outputs"]
    require(isinstance(normalized_outputs, list), f"{label}: normalization outputs must be an array")
    if binding["result_wrapper"] == "exists":
        require(not normalized_outputs, f"{label}: EXISTS mapping must use the wrapper around a nullary core")
    else:
        compare(f"{label}: normalized output names",
                [item.get("name") for item in normalized_outputs], actual_output_names)
        for index, output in enumerate(normalized_outputs):
            require(output.get("kind") in {"core", "constant"},
                    f"{label}: output {index} has invalid mapping kind")
            expected_keys = {"name", "type", "kind", "column"} if output["kind"] == "core" else {
                "name", "type", "kind", "value"
            }
            require(set(output) == expected_keys, f"{label}: output {index} has unexpected fields")
            expression = binding["expressions"][binding["outputs"][index]["expression"]]
            expected_type = expression["type"]
            compare(f"{label}: output {index} SQL type", output["type"], expected_type)
            if output["kind"] == "core":
                require(type(output["column"]) is int and output["column"] >= 0,
                        f"{label}: core output {index} has invalid column index")
            else:
                require(output["value"] is not None,
                        f"{label}: NULL must not be emitted as a classical constant output")
    require(isinstance(result["limits"], dict) and "work_limit" in result["limits"],
            f"{label}: normalizer limits omitted work_limit")
    work_limit = result["limits"]["work_limit"]
    require(work_limit is None or (type(work_limit) is int and work_limit > 0),
            f"{label}: invalid work_limit")
    require(type(result["work"]) is int and result["work"] >= 0,
            f"{label}: normalization work must be a nonnegative integer")

    core = result["core"]
    validate_core_document(core, label)
    if "contradiction" in case["expected"]:
        compare(f"{label}: normalized contradiction flag",
                core["query"].get("contradiction"), case["expected"]["contradiction"])
    validate_routes(result, case["expected"]["occurrences"], case["expected"], label)
    expected_atom_count = case["expected"].get("core_atom_count", len(case["expected"]["occurrences"]))
    compare(f"{label}: retained core atom count", len(core["query"]["atoms"]), expected_atom_count)
    if "core_head_variables" in case["expected"]:
        variable_names = [item["name"] for item in core["query"]["variables"]]
        head_names = [item["var"] for item in core["query"]["head"]]
        compare(f"{label}: normalized head variable names",
                [variable_names.index(name) for name in head_names], case["expected"]["core_head_variables"])

    parameter_values = [decode_scalar(value) for value in case.get("parameter_values_raw", [])]
    adapted = run_adapters(result, data, parameter_values, label)
    core_rows = invoke_core_oracle(executable, core, adapted, label)
    mapped_rows = map_outputs(result, core_rows, label)
    expected_rows = [[decode_scalar(value) for value in row] for row in case["expected"]["rows"]]
    compare(f"{label}: independently computed core rows", rows_key([tuple(row) for row in mapped_rows]),
            rows_key([tuple(row) for row in expected_rows]))
    if "exists" in case["expected"]:
        compare(f"{label}: scalar EXISTS result", mapped_rows, [[case["expected"]["exists"]]])

    if case["expected"].get("sqlite_oracle", False):
        sqlite_rows, sqlite_names = run_sqlite(
            case, source, catalog, data, parameter_values, binding, result, label,
        )
        expected_names = case["expected"].get("output_names")
        if expected_names is not None:
            compare(f"{label}: SQLite output names", sqlite_names, expected_names)
        compare(f"{label}: SQLite and manual output multisets",
                rows_key([tuple(row) for row in sqlite_rows]),
                rows_key([tuple(row) for row in expected_rows]))
    return mapped_rows


def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict[str, Any]) -> None:
    label = case["name"]
    result, source = invoke_normalize(executable, base, catalog_path, case)
    require(result.keys() == NORMALIZATION_FAILURE_FIELDS,
            f"{label}: unexpected failure fields: {sorted(result)}")
    compare(f"{label}: failure envelope",
            {key: result.get(key) for key in ("schema_version", "normalization_valid", "admission_status", "phase")},
            {"schema_version": 1, "normalization_valid": False, "admission_status": "not_checked",
             "phase": case["phase"]})
    diagnostic = result.get("diagnostic")
    require(isinstance(diagnostic, dict), f"{label}: diagnostic must be an object")
    require(set(diagnostic) == {"code", "message", "byte_offset", "character_position", "line", "column"},
            f"{label}: diagnostic has unexpected fields")
    compare(f"{label}: diagnostic code", diagnostic.get("code"), case["code"])
    require(isinstance(diagnostic.get("message"), str) and diagnostic["message"],
            f"{label}: diagnostic message must be nonempty")
    for field in ("byte_offset", "character_position", "line", "column"):
        coordinate = diagnostic[field]
        require(coordinate is None or (type(coordinate) is int and coordinate >= 0),
                f"{label}: diagnostic {field} must be null or a nonnegative integer")
    if diagnostic["line"] is not None:
        require(diagnostic["line"] >= 1, f"{label}: diagnostic line numbers are one-based")
    if diagnostic["column"] is not None:
        require(diagnostic["column"] >= 1, f"{label}: diagnostic columns are one-based")
    marker = case.get("location_marker")
    if marker is not None:
        position = source.find(marker)
        require(position >= 0, f"{label}: location marker not found")
        byte_offset = len(source[:position].encode("utf-8"))
        compare(f"{label}: diagnostic location", diagnostic.get("byte_offset"), byte_offset)


def validate_cli_errors(executable: str, base: Path, catalog_path: Path, manifest: dict[str, Any]) -> int:
    count = 0
    for case in manifest.get("cli_error_cases", []):
        label = case["name"]
        arguments = ["normalize-sql"]
        for item in case["args"]:
            if item == "CATALOG":
                arguments.append(str(catalog_path))
            elif item == "MISSING_SQL":
                arguments.append(str(base / "does-not-exist.sql"))
            elif item == "MISSING_CATALOG":
                arguments.append(str(base / "does-not-exist-catalog.json"))
            elif item.startswith("cases/") or item.startswith("parameters/"):
                arguments.append(str(case_path(base, item, label)))
            else:
                arguments.append(item)
        process = invoke(executable, arguments, label)
        compare(f"{label}: CLI error exit", process.returncode, 2)
        require(not process.stdout, f"{label}: CLI error wrote stdout")
        stderr = decode_output(process.stderr, label, "stderr")
        try:
            error = json.loads(stderr)
        except json.JSONDecodeError as exception:
            raise RuntimeError(f"{label}: stderr is not JSON: {stderr!r}") from exception
        require(isinstance(error, dict) and isinstance(error.get("error"), dict),
                f"{label}: missing structured CLI error")
        compare(f"{label}: CLI error code", error["error"].get("code"), case["code"])
        count += 1
    return count


def main() -> int:
    if len(sys.argv) != 3:
        raise RuntimeError("usage: normalization.py EXECUTABLE FIXTURE_DIRECTORY")
    executable = sys.argv[1]
    base = Path(sys.argv[2]).resolve()
    manifest = read_json(base / "manifest.json")
    require(isinstance(manifest, dict) and type(manifest.get("schema_version")) is int
            and manifest["schema_version"] == 1, "normalization manifest must have schema_version 1")
    successes = manifest.get("success_cases")
    failures = manifest.get("failure_cases")
    require(isinstance(successes, list) and successes, "manifest success_cases must be nonempty")
    require(isinstance(failures, list) and failures, "manifest failure_cases must be nonempty")
    catalog_path = case_path(base, manifest["catalog"], "manifest catalog")
    data_path = case_path(base, manifest["data"], "manifest data")
    catalog = read_json(catalog_path)
    data = read_json(data_path)
    require(isinstance(catalog, dict) and isinstance(catalog.get("catalog"), dict),
            "normalization catalog fixture must contain a catalog object")
    require(isinstance(data, dict), "normalization data fixture must be an object")

    names: set[str] = set()
    for case in successes:
        require(isinstance(case, dict), "normalization success case must be an object")
        name = case.get("name")
        require(isinstance(name, str) and name and name not in names, f"duplicate or invalid case name {name!r}")
        names.add(name)
        require(isinstance(case.get("expected"), dict), f"{name}: expected must be an object")
        validate_success(executable, base, catalog_path, catalog, data, case)
    for case in failures:
        require(isinstance(case, dict), "normalization failure case must be an object")
        name = case.get("name")
        require(isinstance(name, str) and name and name not in names, f"duplicate or invalid case name {name!r}")
        names.add(name)
        validate_failure(executable, base, catalog_path, case)
    cli_errors = validate_cli_errors(executable, base, catalog_path, manifest)
    print(f"{len(successes)} normalization success cases, {len(failures)} diagnostics, and {cli_errors} CLI errors passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"SQL normalization fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
