#!/usr/bin/env python3
"""Independent catalog validation and SQLite-backed v3 trace checks."""

from __future__ import annotations

import copy
import datetime as dt
import json
import re
import sqlite3
import subprocess
import sys
import tempfile
from decimal import Decimal, localcontext
from pathlib import Path
from typing import Any


TIMEOUT_SECONDS = 20
DECIMAL_GRAMMAR = re.compile(r"^[+-]?[0-9]+(?:\.[0-9]+)?$")


def require(condition: bool, message: str) -> None:
    # Keep all checks active under python -O.
    if not condition:
        raise RuntimeError(message)


def json_text(value: Any) -> str:
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":"))


def compare(label: str, actual: Any, expected: Any) -> None:
    actual_text = json_text(actual)
    expected_text = json_text(expected)
    if actual_text != expected_text:
        raise RuntimeError(f"{label}: mismatch\nexpected: {expected_text}\nactual:   {actual_text}")


def short(value: str, limit: int = 1000) -> str:
    return value if len(value) <= limit else value[:limit] + "…"


def quote_identifier(name: str) -> str:
    return '"' + name.replace('"', '""') + '"'


def invoke(
    executable: str,
    command: str,
    document: dict[str, Any],
    temp: Path,
    label: str,
) -> tuple[int, Any, str, str]:
    path = temp / f"{label}.json"
    path.write_text(json.dumps(document, ensure_ascii=False, separators=(",", ":")) + "\n", encoding="utf-8")
    try:
        process = subprocess.run(
            [executable, command, str(path)],
            check=False,
            capture_output=True,
            text=True,
            encoding="utf-8",
            timeout=TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(f"{label}: {command} timed out after {TIMEOUT_SECONDS}s") from error
    try:
        payload = json.loads(process.stdout) if process.stdout.strip() else None
    except json.JSONDecodeError as error:
        raise RuntimeError(
            f"{label}: stdout was not JSON: {error}; stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}"
        ) from error
    return process.returncode, payload, process.stdout, process.stderr


def error_payload(stderr: str, label: str) -> dict[str, Any]:
    try:
        payload = json.loads(stderr)
    except json.JSONDecodeError as error:
        raise RuntimeError(f"{label}: stderr was not structured JSON: {short(stderr)!r}") from error
    require(isinstance(payload, dict) and isinstance(payload.get("error"), dict), f"{label}: missing structured error: {payload!r}")
    return payload["error"]


def rejected(
    executable: str,
    command: str,
    document: dict[str, Any],
    temp: Path,
    label: str,
    expected_code: str | None = None,
) -> None:
    status, _, stdout, stderr = invoke(executable, command, document, temp, label)
    require(status != 0, f"{label}: invalid input unexpectedly succeeded: {stdout!r}")
    error = error_payload(stderr, label)
    require(not stdout.strip(), f"{label}: rejected input wrote partial stdout: {short(stdout)!r}")
    if expected_code is not None:
        require(error.get("code") == expected_code, f"{label}: expected {expected_code}, got {error.get('code')!r}")


def standalone(payload: dict[str, Any], version: int = 1) -> dict[str, Any]:
    return {"schema_version": version, "catalog": payload}


def rich_catalog() -> dict[str, Any]:
    return {
        "version": 9,
        "tables": [
            {
                "name": "Parent",
                "source_schema_version": 7,
                "columns": [
                    {"name": "a", "type": "int64"},
                    {"name": "b", "type": "string", "collation": "binary"},
                    {"name": "amount", "type": "decimal", "decimal": {"precision": 9, "scale": 2}},
                ],
                "constraints": [
                    {"kind": "unique", "name": "parent_ab", "columns": ["a", "b"], "status": "enforced"},
                    {"kind": "unique", "name": "parent_ba", "columns": ["b", "a"], "status": "enforced"},
                ],
                "statistics": {
                    "row_count": 12,
                    "distinct_counts": [{"columns": ["a", "b"], "estimate": 11}],
                },
                "key_hints": [{"columns": ["a", "b"], "reason": "source system advertises this key"}],
            },
            {
                "name": "Child",
                "columns": [
                    {"name": "witness_id", "type": "int64"},
                    {"name": "parent_b", "type": "string"},
                    {"name": "parent_a", "type": "int64"},
                ],
                "constraints": [
                    {
                        "kind": "foreign_key",
                        "name": "child_parent",
                        "columns": ["parent_b", "parent_a"],
                        "status": "enforced",
                        "references": {"table": "Parent", "columns": ["b", "a"]},
                    }
                ],
                "statistics": {"distinct_counts": [{"columns": ["witness_id"], "estimate": 5}]},
            },
            {
                "name": "NullableSource",
                "source_schema_version": 1,
                "columns": [{"name": "note", "type": "string", "nullable": True}],
            },
            {"name": "Defaults", "columns": [{"name": "x", "type": "bool"}]},
        ],
    }


def canonical_catalog_payload(payload: dict[str, Any]) -> dict[str, Any]:
    """Expected JSON form after materializing catalog metadata defaults."""
    result = copy.deepcopy(payload)
    for table in result["tables"]:
        table.setdefault("source_schema_version", 1)
        table.setdefault("constraints", [])
        table.setdefault("statistics", {})
        table["statistics"].setdefault("distinct_counts", [])
        table.setdefault("key_hints", [])
        for column in table["columns"]:
            column.setdefault("nullable", False)
            if column["type"] == "string":
                column.setdefault("collation", "binary")
    return result


def check_standalone_catalog(executable: str, temp: Path) -> None:
    payload = rich_catalog()
    document = standalone(payload)
    status, result, stdout, stderr = invoke(executable, "validate-catalog", document, temp, "catalog-valid")
    require(status == 0, f"validate-catalog rejected valid metadata; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare("validate-catalog result", result, {"schema_version": 1, "catalog_valid": True, "catalog_version": 9})

    status, canonical, stdout, stderr = invoke(executable, "canonicalize-catalog", document, temp, "catalog-canonicalize")
    require(status == 0, f"canonicalize-catalog rejected valid metadata; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    require(isinstance(canonical, dict), "canonicalize-catalog did not return an object")
    compare("standalone catalog version", canonical.get("schema_version"), 1)
    catalog = canonical.get("catalog")
    require(isinstance(catalog, dict), "canonicalize-catalog omitted catalog payload")
    compare("standalone catalog canonical payload", catalog, canonical_catalog_payload(payload))
    compare("standalone catalog identity", catalog.get("version"), 9)
    tables = {table.get("name"): table for table in catalog.get("tables", []) if isinstance(table, dict)}
    require(set(tables) == {"Parent", "Child", "NullableSource", "Defaults"}, "canonicalize-catalog changed table names")

    # New defaulted metadata is materialized, so a v1/v2 document can never
    # silently hide details during canonicalization.
    for table_name, table in tables.items():
        for field in ("source_schema_version", "constraints", "statistics", "key_hints"):
            require(field in table, f"canonical table {table_name} omitted defaulted field {field}")
        for column in table.get("columns", []):
            require("nullable" in column, f"canonical column {table_name}.{column.get('name')} omitted nullable")
            if column.get("type") == "string":
                require("collation" in column, f"canonical string column {table_name}.{column.get('name')} omitted collation")
                compare(f"{table_name}.{column.get('name')} default collation", column["collation"], "binary")
            else:
                require("collation" not in column, f"canonical non-string column {table_name}.{column.get('name')} has collation")
    compare("source schema version default", tables["Defaults"]["source_schema_version"], 1)
    compare("default table constraints", tables["Defaults"]["constraints"], [])
    compare("default key hints", tables["Defaults"]["key_hints"], [])
    compare("default nullability", tables["Defaults"]["columns"][0]["nullable"], False)
    compare("nullable source retained", tables["NullableSource"]["columns"][0]["nullable"], True)
    compare("decimal specification retained", tables["Parent"]["columns"][2].get("decimal"), {"precision": 9, "scale": 2})

    status, repeated, stdout, stderr = invoke(executable, "canonicalize-catalog", canonical, temp, "catalog-canonicalize-again")
    require(status == 0, f"canonicalize-catalog rejected its output; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare("standalone catalog canonical fixed point", repeated, canonical)


def check_bad_catalogs(executable: str, temp: Path) -> int:
    cases: list[tuple[str, dict[str, Any], str | None]] = []

    def mutate(label: str, edit: Any, code: str | None = "invalid_catalog") -> None:
        changed = copy.deepcopy(rich_catalog())
        edit(changed)
        cases.append((label, standalone(changed), code))

    cases.append(("catalog-root-version", standalone(rich_catalog(), version=2), "unsupported_version"))
    mutate("catalog-zero-version", lambda value: value.update(version=0))
    mutate("catalog-unknown-scalar", lambda value: value["tables"][0]["columns"][0].update(type="money"), "unsupported_type")
    mutate("catalog-nonbinary-collation", lambda value: value["tables"][0]["columns"][1].update(collation="nocase"), "unsupported_collation")
    mutate("catalog-nonstring-collation", lambda value: value["tables"][0]["columns"][1].update(collation=4), "invalid_document")
    mutate("catalog-nullability-not-bool", lambda value: value["tables"][0]["columns"][0].update(nullable="true"), "invalid_document")
    mutate("catalog-source-version-zero", lambda value: value["tables"][0].update(source_schema_version=0))
    mutate("catalog-decimal-on-integer", lambda value: value["tables"][0]["columns"][0].update(decimal={"precision": 4, "scale": 2}))
    mutate("catalog-decimal-zero-precision", lambda value: value["tables"][0]["columns"][2].update(decimal={"precision": 0, "scale": 0}))
    mutate("catalog-decimal-scale-over-precision", lambda value: value["tables"][0]["columns"][2].update(decimal={"precision": 3, "scale": 4}))
    mutate("catalog-invalid-constraint-status", lambda value: value["tables"][0]["constraints"][0].update(status="trusted"))
    mutate("catalog-empty-constraint-name", lambda value: value["tables"][0]["constraints"][0].update(name=""))
    mutate("catalog-unknown-key-column", lambda value: value["tables"][0]["constraints"][0].update(columns=["missing"]))
    mutate("catalog-unknown-fk-table", lambda value: value["tables"][1]["constraints"][0]["references"].update(table="missing"))
    mutate("catalog-unknown-fk-column", lambda value: value["tables"][1]["constraints"][0]["references"].update(columns=["missing", "a"]))
    mutate("catalog-fk-arity", lambda value: value["tables"][1]["constraints"][0]["references"].update(columns=["b"]))
    mutate("catalog-fk-type-mismatch", lambda value: value["tables"][1]["columns"][2].update(type="string"))
    def remove_target_keys(value: dict[str, Any]) -> None:
        for constraint in value["tables"][0]["constraints"]:
            constraint["status"] = "untrusted"
    mutate("catalog-enforced-fk-without-enforced-key", remove_target_keys)
    mutate("catalog-empty-hint-reason", lambda value: value["tables"][0]["key_hints"][0].update(reason=""))
    mutate("catalog-hint-unknown-column", lambda value: value["tables"][0]["key_hints"][0].update(columns=["missing"]))
    mutate("catalog-stats-unknown-column", lambda value: value["tables"][0]["statistics"]["distinct_counts"][0].update(columns=["missing"]))

    for label, document, expected_code in cases:
        rejected(executable, "validate-catalog", document, temp, label, expected_code)
    return len(cases)


def catalog_payload(tables: list[dict[str, Any]], version: int = 1) -> dict[str, Any]:
    return {"version": version, "tables": tables}


def cq_document(
    catalog: dict[str, Any],
    variables: list[dict[str, Any]],
    atoms: list[dict[str, Any]],
    head: list[dict[str, Any]],
    initial: list[dict[str, Any]],
    updates: list[dict[str, Any]],
    version: int = 3,
) -> dict[str, Any]:
    return {
        "schema_version": version,
        "semantics": "set",
        "catalog": catalog,
        "query": {"variables": variables, "atoms": atoms, "head": head},
        "initial": initial,
        "updates": [dict(item, schema_version=version, sequence=index) for index, item in enumerate(updates, 1)],
    }


def normalize_decimal(text: str) -> str:
    require(DECIMAL_GRAMMAR.fullmatch(text) is not None, f"test input has malformed decimal {text!r}")
    negative = text.startswith("-")
    unsigned = text[1:] if text[:1] in {"+", "-"} else text
    whole, separator, fraction = unsigned.partition(".")
    whole = whole.lstrip("0") or "0"
    fraction = fraction.rstrip("0") if separator else ""
    canonical = whole + ("." + fraction if fraction else "")
    if Decimal(canonical) == 0:
        return "0"
    return ("-" if negative else "") + canonical


def normalize_value(kind: str, value: Any, decimal_spec: dict[str, int] | None = None) -> Any:
    if kind == "date":
        require(isinstance(value, dict) and set(value) == {"date"} and isinstance(value["date"], str), "date fixture value must be one tagged string")
        try:
            canonical = dt.date.fromisoformat(value["date"]).isoformat()
        except ValueError as error:
            raise RuntimeError(f"invalid date fixture value: {value!r}") from error
        require(canonical == value["date"], f"date fixture is not fixed-width canonical: {value!r}")
        return canonical
    if kind == "decimal":
        require(isinstance(value, dict) and set(value) == {"decimal"} and isinstance(value["decimal"], str), "decimal fixture value must be one tagged string")
        canonical = normalize_decimal(value["decimal"])
        if decimal_spec is not None:
            precision = decimal_spec["precision"]
            scale = decimal_spec["scale"]
            with localcontext() as context:
                context.prec = 128
                scaled = Decimal(canonical).scaleb(scale)
                limit = Decimal(10) ** precision
                require(
                    scaled == scaled.to_integral_value() and abs(scaled) < limit,
                    f"decimal {canonical} does not fit ({precision},{scale}) exactly",
                )
        return canonical
    if kind == "bool":
        require(isinstance(value, bool), f"expected boolean fixture value, got {value!r}")
        return value
    if kind == "int64":
        require(isinstance(value, int) and not isinstance(value, bool), f"expected integer fixture value, got {value!r}")
        require(-(1 << 63) <= value < (1 << 63), f"int64 fixture value out of range: {value!r}")
        return value
    if kind == "string":
        require(isinstance(value, str), f"expected string fixture value, got {value!r}")
        return value
    raise RuntimeError(f"unknown fixture type {kind!r}")


def sql_value(kind: str, value: Any, decimal_spec: dict[str, int] | None = None) -> Any:
    normalized = normalize_value(kind, value, decimal_spec)
    if kind == "date" or kind == "decimal" or kind == "string":
        return normalized
    if kind == "bool":
        return int(normalized)
    return normalized


def output_value(kind: str, value: Any) -> Any:
    if kind == "date":
        return {"date": str(value)}
    if kind == "decimal":
        return {"decimal": normalize_decimal(str(value))}
    if kind == "bool":
        return bool(value)
    return value


def output_sort_key(kind: str, value: Any) -> Any:
    if kind == "date":
        return dt.date.fromisoformat(value["date"])
    if kind == "decimal":
        return Decimal(value["decimal"])
    if kind == "string":
        return value.encode("utf-8")
    if kind == "bool":
        return value
    return value


class SQLiteTrace:
    """Finite SQLite trace using declared types/nullability/constraints and typed ordering."""

    def __init__(self, document: dict[str, Any]):
        self.document = document
        self.catalog = document["catalog"]
        self.tables = {table["name"]: table for table in self.catalog["tables"]}
        self.conn = sqlite3.connect(":memory:")
        self.conn.execute("PRAGMA foreign_keys = ON")
        self.rows: dict[str, set[tuple[Any, ...]]] = {name: set() for name in self.tables}
        self._create_tables()
        self._load_initial()
        check = self.conn.execute("PRAGMA foreign_key_check").fetchall()
        require(not check, f"valid fixture has SQLite foreign-key violations: {check!r}")

    def _create_tables(self) -> None:
        sql_type = {"int64": "INTEGER", "bool": "INTEGER", "string": "TEXT COLLATE BINARY", "date": "TEXT COLLATE BINARY", "decimal": "TEXT COLLATE BINARY"}
        for table in self.catalog["tables"]:
            definitions = []
            for column in table["columns"]:
                nullability = "" if column.get("nullable", False) else " NOT NULL"
                definitions.append(f"{quote_identifier(column['name'])} {sql_type[column['type']]}{nullability}")
            for constraint in table.get("constraints", []):
                if constraint["status"] != "enforced":
                    continue
                local_columns = ", ".join(quote_identifier(name) for name in constraint["columns"])
                if constraint["kind"] == "unique":
                    definitions.append(f"UNIQUE ({local_columns})")
                else:
                    reference = constraint["references"]
                    target_columns = ", ".join(quote_identifier(name) for name in reference["columns"])
                    definitions.append(
                        f"FOREIGN KEY ({local_columns}) REFERENCES {quote_identifier(reference['table'])} ({target_columns})"
                    )
            columns_sql = ", ".join(definitions)
            self.conn.execute(f"CREATE TABLE {quote_identifier(table['name'])} ({columns_sql})")
        self.conn.commit()

    def _table_types(self, table_name: str) -> list[tuple[str, dict[str, int] | None]]:
        return [(column["type"], column.get("decimal")) for column in self.tables[table_name]["columns"]]

    def normalize_row(self, table_name: str, raw_row: list[Any]) -> tuple[Any, ...]:
        types = self._table_types(table_name)
        require(len(raw_row) == len(types), f"fixture row arity mismatch in {table_name}: {raw_row!r}")
        return tuple(normalize_value(kind, value, spec) for (kind, spec), value in zip(types, raw_row))

    def sql_row(self, table_name: str, raw_row: list[Any]) -> tuple[Any, ...]:
        types = self._table_types(table_name)
        require(len(raw_row) == len(types), f"fixture row arity mismatch in {table_name}: {raw_row!r}")
        return tuple(sql_value(kind, value, spec) for (kind, spec), value in zip(types, raw_row))

    def _has_row(self, table_name: str, normalized: tuple[Any, ...]) -> bool:
        if not normalized:
            return normalized in self.rows[table_name]
        columns = [column["name"] for column in self.tables[table_name]["columns"]]
        where = " AND ".join(f"{quote_identifier(name)} IS ?" for name in columns)
        found = self.conn.execute(
            f"SELECT 1 FROM {quote_identifier(table_name)} WHERE {where} LIMIT 1",
            self.sql_row(table_name, list(normalized)),
        ).fetchone()
        return found is not None

    def _insert(self, table_name: str, raw_row: list[Any]) -> bool:
        normalized = self.normalize_row(table_name, raw_row)
        if normalized in self.rows[table_name]:
            return False
        columns = [column["name"] for column in self.tables[table_name]["columns"]]
        values = self.sql_row(table_name, raw_row)
        if columns:
            names_sql = ", ".join(quote_identifier(name) for name in columns)
            placeholders = ", ".join("?" for _ in columns)
            self.conn.execute(
                f"INSERT INTO {quote_identifier(table_name)} ({names_sql}) VALUES ({placeholders})", values
            )
        else:
            self.conn.execute(f"INSERT INTO {quote_identifier(table_name)} DEFAULT VALUES")
        self.rows[table_name].add(normalized)
        return True

    def _delete(self, table_name: str, raw_row: list[Any]) -> bool:
        normalized = self.normalize_row(table_name, raw_row)
        if normalized not in self.rows[table_name]:
            return False
        columns = [column["name"] for column in self.tables[table_name]["columns"]]
        where = " AND ".join(f"{quote_identifier(name)} IS ?" for name in columns)
        self.conn.execute(
            f"DELETE FROM {quote_identifier(table_name)} WHERE {where}", self.sql_row(table_name, raw_row)
        )
        self.rows[table_name].remove(normalized)
        return True

    def _load_initial(self) -> None:
        for initial in self.document.get("initial", []):
            for row in initial["rows"]:
                # CROWN's exact full-row duplicate is a set no-op. For all
                # different rows use ordinary INSERT so SQLite constraints
                # remain visible (never INSERT OR IGNORE).
                self._insert(initial["table"], row)
        self.conn.commit()

    def relation(self) -> list[list[Any]]:
        query = self.document["query"]
        atoms = query["atoms"]
        bindings: dict[str, tuple[str, str]] = {}
        from_parts: list[str] = []
        predicates: list[str] = []
        parameters: list[Any] = []
        for atom_index, atom in enumerate(atoms):
            alias = f"q{atom_index}"
            table_name = atom["table"]
            from_parts.append(f"{quote_identifier(table_name)} AS {quote_identifier(alias)}")
            table = self.tables[table_name]
            require(len(atom["terms"]) == len(table["columns"]), f"atom arity mismatch in oracle fixture {atom['id']}")
            for column, term in zip(table["columns"], atom["terms"]):
                expression = f"{quote_identifier(alias)}.{quote_identifier(column['name'])}"
                kind = column["type"]
                if "var" in term:
                    variable = term["var"]
                    if variable in bindings:
                        predicates.append(f"{expression} = {bindings[variable][0]}")
                    else:
                        bindings[variable] = (expression, kind)
                elif "const" in term:
                    constant = term["const"]
                    value = sql_value(kind, constant, column.get("decimal"))
                    predicates.append(f"{expression} = ?")
                    parameters.append(value)

        select = []
        result_types = []
        for output_index, output in enumerate(query["head"]):
            expression, kind = bindings[output["var"]]
            select.append(f"{expression} AS {quote_identifier(f'out{output_index}')}")
            result_types.append(kind)
        sql = "SELECT DISTINCT " + ", ".join(select)
        if from_parts:
            sql += " FROM " + ", ".join(from_parts)
        else:
            sql += " WHERE 1=1"
        if predicates:
            sql += " WHERE " + " AND ".join(predicates)
        raw_rows = self.conn.execute(sql, parameters).fetchall()
        result: list[list[Any]] = []
        for row in raw_rows:
            result.append([output_value(kind, value) for kind, value in zip(result_types, row)])
        result.sort(key=lambda row: tuple(output_sort_key(kind, value) for kind, value in zip(result_types, row)))
        return result

    def trace(self) -> dict[str, Any]:
        output = {
            "schema_version": self.document["schema_version"],
            "backend": "reference_recompute",
            "semantics": "set",
            "initial": self.relation(),
            "epochs": [],
        }
        for update in self.document.get("updates", []):
            before = self.relation()
            before_keys = {json_text(row) for row in before}
            self.conn.execute("SAVEPOINT crown_event")
            try:
                if update["op"] == "insert":
                    changed = self._insert(update["table"], update["values"])
                else:
                    changed = self._delete(update["table"], update["values"])
                self.conn.execute("RELEASE crown_event")
            except sqlite3.IntegrityError:
                self.conn.execute("ROLLBACK TO crown_event")
                self.conn.execute("RELEASE crown_event")
                raise
            current = self.relation()
            current_keys = {json_text(row) for row in current}
            added = [row for row in current if json_text(row) in current_keys - before_keys]
            removed = [row for row in before if json_text(row) in before_keys - current_keys]
            output["epochs"].append({
                "sequence": update["sequence"],
                "input_changed": changed,
                "current": current,
                "delta": {"added": added, "removed": removed},
            })
        return output


def check_valid_document(executable: str, document: dict[str, Any], temp: Path, label: str) -> None:
    expected = SQLiteTrace(document).trace()
    status, actual, stdout, stderr = invoke(executable, "oracle", document, temp, label + "-oracle")
    require(status == 0, f"{label}: oracle exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " SQLite oracle", actual, expected)

    status, canonical, stdout, stderr = invoke(executable, "canonicalize", document, temp, label + "-canonical")
    require(status == 0, f"{label}: canonicalize exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    require(isinstance(canonical, dict), f"{label}: canonicalize did not return an object")
    compare(label + " canonical root version", canonical.get("schema_version"), document["schema_version"])
    canonical_catalog = canonical.get("catalog")
    require(isinstance(canonical_catalog, dict), f"{label}: canonicalize omitted catalog")
    compare(label + " canonical metadata", canonical_catalog, canonical_catalog_payload(document["catalog"]))
    for table in canonical_catalog.get("tables", []):
        for field in ("source_schema_version", "constraints", "statistics", "key_hints"):
            require(field in table, f"{label}: canonical table {table.get('name')} omitted {field}")
        for column in table.get("columns", []):
            require("nullable" in column, f"{label}: canonical column {table.get('name')}.{column.get('name')} omitted nullability default")
            if column.get("type") == "string":
                require("collation" in column, f"{label}: canonical string column {table.get('name')}.{column.get('name')} omitted collation")
            else:
                require("collation" not in column, f"{label}: canonical non-string column {table.get('name')}.{column.get('name')} has collation")
    status, repeated, stdout, stderr = invoke(executable, "canonicalize", canonical, temp, label + "-canonical-again")
    require(status == 0, f"{label}: canonicalize fixed point failed; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " canonical fixed point", repeated, canonical)
    status, roundtrip, stdout, stderr = invoke(executable, "oracle", canonical, temp, label + "-roundtrip")
    require(status == 0, f"{label}: canonical oracle failed; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " canonical SQLite trace", roundtrip, expected)


def check_query_binding(executable: str, document: dict[str, Any], temp: Path, label: str, expected_version: int) -> None:
    status, result, stdout, stderr = invoke(executable, "tree-oracle", document, temp, label + "-tree-oracle")
    require(status == 0, f"{label}: tree-oracle failed; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " tree-oracle envelope version", result.get("schema_version"), 1)
    certificate = result.get("certificate")
    require(isinstance(certificate, dict), f"{label}: tree-oracle omitted its minimum certificate")
    compare(label + " certificate envelope version", certificate.get("schema_version"), 2)
    binding = certificate.get("query_binding")
    require(isinstance(binding, dict), f"{label}: certificate omitted query binding")
    compare(label + " query binding version", binding.get("schema_version"), expected_version)
    if expected_version == 3:
        child = next(table for table in binding["catalog"]["tables"] if table["name"] == "Child")
        compare(label + " binding retained FK kind", child["constraints"][0].get("kind"), "foreign_key")
        compare(label + " binding retained FK target order", child["constraints"][0]["references"]["columns"], ["b", "a"])


def join_catalog() -> dict[str, Any]:
    return {
        "version": 3,
        "tables": [
            {
                "name": "Parent",
                "source_schema_version": 4,
                "columns": [{"name": "a", "type": "int64"}, {"name": "b", "type": "string"}],
                "constraints": [
                    {"kind": "unique", "name": "parent_ab", "columns": ["a", "b"], "status": "enforced"},
                    {"kind": "unique", "name": "parent_ba", "columns": ["b", "a"], "status": "enforced"},
                ],
                "statistics": {"row_count": 3, "distinct_counts": [{"columns": ["a", "b"], "estimate": 2}]},
            },
            {
                "name": "Child",
                "columns": [
                    {"name": "witness", "type": "int64"},
                    {"name": "parent_b", "type": "string"},
                    {"name": "parent_a", "type": "int64"},
                ],
                "constraints": [
                    {"kind": "foreign_key", "name": "child_parent", "columns": ["parent_b", "parent_a"],
                     "status": "enforced", "references": {"table": "Parent", "columns": ["b", "a"]}}
                ],
                "key_hints": [{"columns": ["witness"], "reason": "witness identifier"}],
            },
        ],
    }


def join_document() -> dict[str, Any]:
    catalog = join_catalog()
    return cq_document(
        catalog,
        [{"name": "a", "type": "int64"}, {"name": "b", "type": "string"}],
        [
            {"id": "p", "table": "Parent", "terms": [{"var": "a"}, {"var": "b"}]},
            {"id": "c", "table": "Child", "terms": [{"ignore": True}, {"var": "b"}, {"var": "a"}]},
        ],
        [{"var": "a"}, {"var": "b"}],
        [
            {"table": "Parent", "rows": [[1, "alpha"], [1, "alpha"], [2, "beta"]]},
            {"table": "Child", "rows": [[10, "alpha", 1], [11, "alpha", 1], [20, "beta", 2]]},
        ],
        [
            {"table": "Child", "op": "insert", "values": [12, "alpha", 1]},
            {"table": "Child", "op": "delete", "values": [10, "alpha", 1]},
            {"table": "Child", "op": "delete", "values": [11, "alpha", 1]},
            {"table": "Child", "op": "delete", "values": [12, "alpha", 1]},
            {"table": "Child", "op": "insert", "values": [30, "beta", 2]},
            {"table": "Parent", "op": "delete", "values": [1, "alpha"]},
            {"table": "Parent", "op": "insert", "values": [3, "gamma"]},
            {"table": "Child", "op": "insert", "values": [31, "gamma", 3]},
            {"table": "Child", "op": "delete", "values": [31, "gamma", 3]},
        ],
    )


def self_reference_document() -> dict[str, Any]:
    catalog = catalog_payload([{
        "name": "Node",
        "columns": [{"name": "id", "type": "int64"}, {"name": "parent_id", "type": "int64"}],
        "constraints": [
            {"kind": "unique", "name": "node_id", "columns": ["id"], "status": "enforced"},
            {"kind": "foreign_key", "name": "node_parent", "columns": ["parent_id"], "status": "enforced",
             "references": {"table": "Node", "columns": ["id"]}},
        ],
    }], version=5)
    return cq_document(
        catalog,
        [{"name": "id", "type": "int64"}],
        [{"id": "node", "table": "Node", "terms": [{"var": "id"}, {"ignore": True}]}],
        [{"var": "id"}],
        [{"table": "Node", "rows": []}],
        [
            {"table": "Node", "op": "insert", "values": [1, 1]},
            {"table": "Node", "op": "insert", "values": [1, 1]},
            {"table": "Node", "op": "delete", "values": [1, 1]},
            {"table": "Node", "op": "delete", "values": [1, 1]},
        ],
    )


def untrusted_metadata_document() -> dict[str, Any]:
    catalog = catalog_payload([
        {
            "name": "R",
            "columns": [{"name": "x", "type": "int64"}],
            "constraints": [
                {"kind": "unique", "name": "claimed_unique", "columns": ["x"], "status": "untrusted"},
                {"kind": "foreign_key", "name": "claimed_fk", "columns": ["x"], "status": "untrusted",
                 "references": {"table": "S", "columns": ["x"]}},
            ],
            "statistics": {"row_count": 0, "distinct_counts": [{"columns": ["x"], "estimate": 999}]},
            "key_hints": [{"columns": ["x"], "reason": "known to be false in this fixture"}],
        },
        {
            "name": "S",
            "columns": [{"name": "x", "type": "int64"}, {"name": "payload", "type": "string"}],
            "constraints": [{"kind": "unique", "name": "also_untrusted", "columns": ["x"], "status": "untrusted"}],
            "statistics": {"row_count": 400, "distinct_counts": [{"columns": ["x"], "estimate": 0}]},
            "key_hints": [{"columns": ["x"], "reason": "intentionally inaccurate hint"}],
        },
    ])
    return cq_document(
        catalog,
        [{"name": "x", "type": "int64"}],
        [
            {"id": "r", "table": "R", "terms": [{"var": "x"}]},
            {"id": "s", "table": "S", "terms": [{"var": "x"}, {"ignore": True}]},
        ],
        [{"var": "x"}],
        [{"table": "R", "rows": [[1], [2]]}, {"table": "S", "rows": [[1, "a"], [1, "b"]]}],
        [],
    )


def decimal_spec_document() -> dict[str, Any]:
    catalog = catalog_payload([{
        "name": "Amounts",
        "columns": [{"name": "amount", "type": "decimal", "decimal": {"precision": 5, "scale": 2}}],
    }], version=2)
    return cq_document(
        catalog,
        [{"name": "amount", "type": "decimal"}],
        [{"id": "a", "table": "Amounts", "terms": [{"var": "amount"}]}],
        [{"var": "amount"}],
        [{"table": "Amounts", "rows": [[{"decimal": "1.200"}], [{"decimal": "-999.99"}], [{"decimal": "0.00"}]]}],
        [
            {"table": "Amounts", "op": "insert", "values": [{"decimal": "123.45"}]},
            {"table": "Amounts", "op": "insert", "values": [{"decimal": "1.2"}]},
            {"table": "Amounts", "op": "delete", "values": [{"decimal": "-999.99"}]},
        ],
    )


def check_format_compatibility(executable: str, temp: Path) -> None:
    # Legacy documents omit all metadata and continue using their own format
    # and update versions; catalog defaults do not upgrade them implicitly.
    for version in (1, 2):
        document = cq_document(
            catalog_payload([{"name": "T", "columns": [{"name": "x", "type": "int64"}]}]),
            [{"name": "x", "type": "int64"}],
            [{"id": "t", "table": "T", "terms": [{"var": "x"}]}],
            [{"var": "x"}],
            [{"table": "T", "rows": [[-1], [2]]}],
            [{"table": "T", "op": "insert", "values": [3]}],
            version=version,
        )
        status, result, stdout, stderr = invoke(executable, "oracle", document, temp, f"format-{version}-oracle")
        require(status == 0, f"format {version} document rejected; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
        compare(f"format {version} SQLite oracle", result, SQLiteTrace(document).trace())
        check_query_binding(executable, document, temp, f"format-{version}-binding", expected_version=1)
        status, canonical, stdout, stderr = invoke(executable, "canonicalize", document, temp, f"format-{version}-canonical")
        require(status == 0, f"format {version} canonicalization rejected; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
        compare(f"format {version} canonical version", canonical.get("schema_version"), version)

    old_with_metadata = cq_document(
        catalog_payload([{
            "name": "T", "source_schema_version": 2,
            "columns": [{"name": "x", "type": "int64"}],
        }]),
        [{"name": "x", "type": "int64"}],
        [{"id": "t", "table": "T", "terms": [{"var": "x"}]}],
        [{"var": "x"}],
        [{"table": "T", "rows": [[1]]}],
        [],
        version=2,
    )
    rejected(executable, "oracle", old_with_metadata, temp, "format-2-metadata-rejected")


def check_constraint_rejections(executable: str, temp: Path) -> int:
    catalog = catalog_payload([
        {"name": "P", "columns": [{"name": "id", "type": "int64"}, {"name": "label", "type": "string"}],
         "constraints": [{"kind": "unique", "name": "p_id", "columns": ["id"], "status": "enforced"}]},
        {"name": "C", "columns": [{"name": "id", "type": "int64"}, {"name": "parent_id", "type": "int64"}],
         "constraints": [{"kind": "foreign_key", "name": "c_parent", "columns": ["parent_id"], "status": "enforced",
                          "references": {"table": "P", "columns": ["id"]}}]},
    ])
    p_query = [{"id": "p", "table": "P", "terms": [{"var": "id"}, {"ignore": True}]}]
    c_query = [{"id": "c", "table": "C", "terms": [{"var": "id"}, {"ignore": True}]}]
    variables = [{"name": "id", "type": "int64"}]
    head = [{"var": "id"}]
    cases = [
        (
            "unique-initial-conflict",
            cq_document(catalog, variables, p_query, head,
                        [{"table": "P", "rows": [[1, "a"], [1, "b"]]}, {"table": "C", "rows": []}], []),
        ),
        (
            "foreign-key-initial-orphan",
            cq_document(catalog, variables, c_query, head,
                        [{"table": "P", "rows": [[1, "a"]]}, {"table": "C", "rows": [[10, 99]]}], []),
        ),
        (
            "unique-update-conflict-atomic-output",
            cq_document(catalog, variables, p_query, head,
                        [{"table": "P", "rows": [[1, "a"]]}, {"table": "C", "rows": []}],
                        [{"table": "P", "op": "insert", "values": [2, "b"]},
                         {"table": "P", "op": "insert", "values": [1, "other"]}]),
        ),
        (
            "foreign-key-update-orphan",
            cq_document(catalog, variables, c_query, head,
                        [{"table": "P", "rows": [[1, "a"]]}, {"table": "C", "rows": []}],
                        [{"table": "C", "op": "insert", "values": [11, 99]}]),
        ),
        (
            "referenced-key-delete-rejected",
            cq_document(catalog, variables, p_query, head,
                        [{"table": "P", "rows": [[1, "a"]]}, {"table": "C", "rows": [[10, 1]]}],
                        [{"table": "P", "op": "delete", "values": [1, "a"]}]),
        ),
    ]
    for label, document in cases:
        rejected(executable, "oracle", document, temp, label, "constraint_violation")

    nullable = cq_document(
        catalog_payload([
            {"name": "Used", "columns": [{"name": "x", "type": "int64"}]},
            {"name": "Unused", "columns": [{"name": "note", "type": "string", "nullable": True}]},
        ]),
        [{"name": "x", "type": "int64"}],
        [{"id": "n", "table": "Used", "terms": [{"var": "x"}]}],
        [{"var": "x"}],
        [{"table": "Used", "rows": [[1]]}, {"table": "Unused", "rows": []}],
        [],
    )
    rejected(executable, "oracle", nullable, temp, "cq-catalog-wide-nullability-rejected", "unsupported_nullability")

    overflow = decimal_spec_document()
    overflow["initial"][0]["rows"].append([{"decimal": "1.001"}])
    rejected(executable, "oracle", overflow, temp, "fixed-decimal-scale-overflow", "scalar_overflow")
    overflow_precision = decimal_spec_document()
    overflow_precision["initial"][0]["rows"].append([{"decimal": "1234.56"}])
    rejected(executable, "oracle", overflow_precision, temp, "fixed-decimal-precision-overflow", "scalar_overflow")
    return len(cases) + 3


def main() -> int:
    if len(sys.argv) != 2:
        raise RuntimeError("usage: catalog.py CROWN_EXECUTABLE")
    executable = sys.argv[1]
    with tempfile.TemporaryDirectory(prefix="crown-catalog-") as directory:
        temp = Path(directory)
        check_standalone_catalog(executable, temp)
        bad_catalogs = check_bad_catalogs(executable, temp)

        valid_documents = [
            ("composite-reordered-fk-witnesses", join_document()),
            ("self-referencing-set-trace", self_reference_document()),
            ("untrusted-metadata-does-not-rewrite", untrusted_metadata_document()),
            ("fixed-decimal-spec", decimal_spec_document()),
        ]
        for label, document in valid_documents:
            check_valid_document(executable, document, temp, label)
        check_query_binding(executable, valid_documents[0][1], temp, "catalog-v3-binding", expected_version=3)
        check_format_compatibility(executable, temp)
        rejected_traces = check_constraint_rejections(executable, temp)

    print(
        f"catalog checks passed: 1 standalone catalog, {bad_catalogs} invalid catalogs, "
        f"{len(valid_documents)} v3 SQLite traces, 2 legacy document versions, {rejected_traces} rejected traces"
    )
    print("SQLite oracle used PRAGMA foreign_keys=ON, ordinary INSERT constraints, and full-row duplicate prechecks")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"catalog integration failure: {error}", file=sys.stderr)
        raise SystemExit(1)
