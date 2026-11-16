#!/usr/bin/env python3
"""Independent date/decimal oracle and document-contract checks for F01."""

from __future__ import annotations

import copy
import datetime as dt
import json
import random
import re
import subprocess
import sys
import tempfile
from decimal import Decimal, InvalidOperation
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[2]
TIMEOUT_SECONDS = 20
DECIMAL_GRAMMAR = re.compile(r"^[+-]?[0-9]+(?:\.[0-9]+)?$")


def require(condition: bool, message: str) -> None:
    # Avoid assert: this runner must keep checking when invoked with python -O.
    if not condition:
        raise RuntimeError(message)


def json_text(value: Any) -> str:
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":"))


def compare(label: str, actual: Any, expected: Any) -> None:
    # JSON text comparison preserves distinctions such as true versus 1.
    actual_text = json_text(actual)
    expected_text = json_text(expected)
    if actual_text != expected_text:
        raise RuntimeError(
            f"{label}: mismatch\nexpected: {expected_text}\nactual:   {actual_text}"
        )


def short(value: str, limit: int = 1000) -> str:
    return value if len(value) <= limit else value[:limit] + "…"


def encode_value(kind: str, value: Any) -> Any:
    if kind == "date":
        return {"date": canonical_spelling(kind, value)}
    if kind == "decimal":
        return {"decimal": canonical_spelling(kind, value)}
    return value


def decimal_key(spelling: Any) -> Decimal:
    if isinstance(spelling, Decimal):
        if not spelling.is_finite():
            raise RuntimeError(f"test generator produced non-finite decimal: {spelling!r}")
        return spelling
    spelling = str(spelling)
    if not DECIMAL_GRAMMAR.fullmatch(spelling):
        raise RuntimeError(f"test generator produced invalid decimal spelling {spelling!r}")
    try:
        value = Decimal(spelling)
    except InvalidOperation as error:
        raise RuntimeError(f"test generator produced invalid decimal: {spelling!r}") from error
    if not value.is_finite():
        raise RuntimeError(f"test generator produced non-finite decimal: {spelling!r}")
    return value


def canonical_decimal(spelling: str) -> str:
    """Canonicalize decimal text independently of the C++ scalar parser."""
    if not DECIMAL_GRAMMAR.fullmatch(spelling):
        raise RuntimeError(f"test generator produced invalid decimal spelling {spelling!r}")
    negative = spelling.startswith("-")
    unsigned = spelling[1:] if spelling[:1] in {"+", "-"} else spelling
    whole, separator, fraction = unsigned.partition(".")
    whole = whole.lstrip("0") or "0"
    fraction = fraction.rstrip("0") if separator else ""
    canonical = whole + ("." + fraction if fraction else "")
    if Decimal(canonical) == 0:
        return "0"
    return ("-" if negative else "") + canonical


def typed_key(kind: str, spelling: Any) -> Any:
    if kind == "date":
        try:
            return dt.date.fromisoformat(str(spelling))
        except ValueError as error:
            raise RuntimeError(f"test generator produced invalid date {spelling!r}") from error
    if kind == "decimal":
        return decimal_key(spelling)
    return spelling


def canonical_spelling(kind: str, spelling: Any) -> Any:
    if kind == "date":
        return typed_key(kind, spelling).isoformat()
    if kind == "decimal":
        text = format(spelling, "f") if isinstance(spelling, Decimal) else str(spelling)
        return canonical_decimal(text)
    return spelling


def scalar_sort_key(kind: str, spelling: Any) -> Any:
    if kind in {"date", "decimal"}:
        return typed_key(kind, spelling)
    return spelling


def relation_json(kind: str, values: set[Any]) -> list[list[Any]]:
    ordered = sorted(values, key=lambda value: scalar_sort_key(kind, value))
    return [[encode_value(kind, canonical_spelling(kind, value))] for value in ordered]


def base_document(kind: str, version: int = 2) -> dict[str, Any]:
    return {
        "schema_version": version,
        "semantics": "set",
        "catalog": {
            "version": 1,
            "tables": [{"name": "T", "columns": [{"name": "v", "type": kind}]}],
        },
        "query": {
            "variables": [{"name": "x", "type": kind}],
            "atoms": [{"id": "t", "table": "T", "terms": [{"var": "x"}]}],
            "head": [{"var": "x"}],
        },
        "initial": [{"table": "T", "rows": []}],
        "updates": [],
    }


def single_document(kind: str, initial: list[Any], updates: list[tuple[str, Any]]) -> dict[str, Any]:
    document = base_document(kind)
    # Preserve raw spellings at the input boundary; the independent model alone
    # canonicalizes expected values. Otherwise aliases would be normalized by
    # this generator before the native parser ever sees them.
    document["initial"][0]["rows"] = [[{kind: value}] for value in initial]
    document["updates"] = [
        {
            "schema_version": 2,
            "sequence": sequence,
            "table": "T",
            "op": operation,
            "values": [{kind: value}],
        }
        for sequence, (operation, value) in enumerate(updates, 1)
    ]
    return document


def model_single(kind: str, initial: list[Any], updates: list[tuple[str, Any]]) -> dict[str, Any]:
    values: set[Any] = {typed_key(kind, value) for value in initial}
    result: dict[str, Any] = {
        "schema_version": 2,
        "backend": "reference_recompute",
        "semantics": "set",
        "initial": relation_json(kind, values),
        "epochs": [],
    }
    for sequence, (operation, spelling) in enumerate(updates, 1):
        value = typed_key(kind, spelling)
        before = set(values)
        if operation == "insert":
            values.add(value)
        else:
            values.discard(value)
        added = values - before
        removed = before - values
        result["epochs"].append(
            {
                "sequence": sequence,
                "input_changed": values != before,
                "current": relation_json(kind, values),
                "delta": {
                    "added": relation_json(kind, added),
                    "removed": relation_json(kind, removed),
                },
            }
        )
    return result


def random_decimal(rng: random.Random, index: int) -> str:
    digits = str(rng.randrange(1, 10**9))
    scale = rng.randrange(0, min(9, len(digits)) + 1)
    if scale:
        spelling = digits[:-scale] + "." + digits[-scale:] if len(digits) > scale else "0." + "0" * (scale - len(digits)) + digits
    else:
        spelling = digits
    if index % 2:
        spelling = "-" + spelling
    # Add harmless leading and fractional zeroes to exercise aliases.
    whole, separator, fraction = spelling.lstrip("-").partition(".")
    whole = "00" + whole
    if separator:
        fraction += "00"
    return ("-" if index % 2 else "+") + whole + ("." + fraction if separator else "")


def generated_scalars(kind: str, seed: int) -> tuple[list[Any], list[tuple[str, Any]]]:
    rng = random.Random(seed)
    if kind == "date":
        picks = [
            "0001-01-01",
            "1900-02-28",
            "2000-02-29",
            "2000-03-01",
            "9999-12-31",
        ]
        for _ in range(8):
            ordinal = rng.randrange(1, dt.date.max.toordinal() + 1)
            picks.append(dt.date.fromordinal(ordinal).isoformat())
        initial = picks + ["2000-02-29", "0001-01-01"]
        candidates = list(dict.fromkeys(picks))
    else:
        precision38 = "12345678901234567890123456789012345678"
        max_scale = "0." + "0" * 37 + "1"
        picks = [
            "0",
            "-0.000",
            "+001.2300",
            "-123.4500",
            "1" + "0" * 37,
            precision38,
            max_scale,
            "-0.00000000000000000000000000000000000001",
        ]
        picks.extend(random_decimal(rng, index) for index in range(10))
        initial = picks + ["1.23", "0000", "-123.45"]
        candidates = list(dict.fromkeys(picks))

    # A fixed trace includes fresh inserts, aliases, effective deletes, and no-ops.
    updates: list[tuple[str, Any]] = []
    first_unseen = next(
        (candidate for candidate in candidates if typed_key(kind, candidate) not in {typed_key(kind, value) for value in initial}),
        None,
    )
    if first_unseen is None:
        if kind == "date":
            first_unseen = "1984-06-07"
        else:
            first_unseen = "+00000000000000000000000000000000000005.000"
    updates.extend(
        [
            ("insert", first_unseen),
            ("insert", canonical_spelling(kind, first_unseen)),
            ("delete", initial[0]),
            ("delete", initial[0]),
        ]
    )
    for _ in range(10):
        operation = "insert" if rng.randrange(2) else "delete"
        updates.append((operation, rng.choice(candidates)))
    return initial, updates


def decimal_schema_document_check() -> None:
    schema_path = ROOT / "schemas" / "cq-v2.schema.json"
    try:
        schema = json.loads(schema_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise RuntimeError(f"{schema_path}: invalid or unreadable schema: {error}") from error
    require(schema.get("properties", {}).get("schema_version", {}).get("const") == 2, "v2 schema root version is not 2")
    require(schema.get("$defs", {}).get("scalar_type", {}).get("enum") == ["int64", "string", "bool", "date", "decimal"], "v2 schema scalar type enum differs from the F01 contract")
    require(schema.get("$defs", {}).get("update", {}).get("properties", {}).get("schema_version", {}).get("const") == 2, "v2 schema update version is not 2")


def call(executable: str, command: str, document: dict[str, Any], temp: Path, label: str) -> tuple[int, Any, str, str]:
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
            f"{label}: {command} stdout was not JSON: {error}; stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}"
        ) from error
    return process.returncode, payload, process.stdout, process.stderr


def canonical_document(document: dict[str, Any]) -> dict[str, Any]:
    canonical = copy.deepcopy(document)
    schemas = {
        table["name"]: [column["type"] for column in table["columns"]]
        for table in canonical["catalog"]["tables"]
    }
    initial_by_table = {entry["table"]: entry["rows"] for entry in canonical.get("initial", [])}

    def canonical_row(table_name: str, row: list[Any]) -> tuple[tuple[Any, ...], list[Any]]:
        row_types = schemas[table_name]
        values: list[Any] = []
        keys: list[Any] = []
        for kind, value in zip(row_types, row, strict=True):
            spelling = value[kind] if kind in {"date", "decimal"} else value
            normalized = canonical_spelling(kind, spelling)
            values.append(encode_value(kind, normalized))
            keys.append(typed_key(kind, normalized))
        return tuple(keys), values

    canonical["initial"] = []
    for table in canonical["catalog"]["tables"]:
        name = table["name"]
        normalized_rows = {canonical_row(name, row)[0]: canonical_row(name, row)[1] for row in initial_by_table.get(name, [])}
        canonical["initial"].append({"table": name, "rows": [normalized_rows[key] for key in sorted(normalized_rows)]})
    for update in canonical.get("updates", []):
        row_types = schemas[update["table"]]
        normalized = []
        for kind, value in zip(row_types, update["values"], strict=True):
            spelling = value[kind] if kind in {"date", "decimal"} else value
            normalized.append(encode_value(kind, canonical_spelling(kind, spelling)))
        update["values"] = normalized
    canonical["query"]["contradiction"] = canonical["query"].get("contradiction", False)
    for output in canonical["query"]["head"]:
        output.setdefault("alias", output["var"])
    return canonical


def check_valid_document(
    executable: str,
    document: dict[str, Any],
    expected: dict[str, Any],
    temp: Path,
    label: str,
) -> None:
    status, actual, stdout, stderr = call(executable, "oracle", document, temp, label + "-oracle")
    require(status == 0, f"{label}: oracle exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " oracle", actual, expected)

    status, canonical, stdout, stderr = call(executable, "canonicalize", document, temp, label + "-canonical")
    require(status == 0, f"{label}: canonicalize exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " canonical document", canonical, canonical_document(document))

    status, repeated, stdout, stderr = call(executable, "canonicalize", canonical, temp, label + "-canonical-again")
    require(status == 0, f"{label}: second canonicalize exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " canonical fixed point", repeated, canonical)
    status, roundtrip, stdout, stderr = call(executable, "oracle", canonical, temp, label + "-roundtrip")
    require(status == 0, f"{label}: canonical oracle exit {status}; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare(label + " canonical oracle", roundtrip, expected)


def error_payload(stderr: str, label: str) -> dict[str, Any]:
    try:
        result = json.loads(stderr)
    except json.JSONDecodeError as error:
        raise RuntimeError(f"{label}: stderr was not structured JSON: {short(stderr)!r}") from error
    require(isinstance(result, dict) and isinstance(result.get("error"), dict), f"{label}: stderr lacks error object: {result!r}")
    return result["error"]


def check_rejected(
    executable: str,
    document: dict[str, Any],
    temp: Path,
    label: str,
    expected_code: str | None = None,
) -> None:
    status, payload, stdout, stderr = call(executable, "oracle", document, temp, label)
    require(status != 0, f"{label}: invalid document unexpectedly succeeded: {stdout!r}")
    error = error_payload(stderr, label)
    if expected_code is not None:
        require(error.get("code") == expected_code, f"{label}: expected error code {expected_code}, got {error.get('code')!r}")


def single_invalid(kind: str, value: Any) -> dict[str, Any]:
    document = base_document(kind)
    document["initial"][0]["rows"] = [[value]]
    return document


def check_invalid_documents(executable: str, temp: Path) -> int:
    cases: list[tuple[str, dict[str, Any], str | None]] = []
    cases.append(("raw-float", single_invalid("decimal", 1.0), None))
    cases.append(("null-cell", single_invalid("decimal", None), None))
    cases.append(("decimal-date-tag-mismatch", single_invalid("decimal", {"date": "2024-01-01"}), None))
    cases.append(("date-decimal-tag-mismatch", single_invalid("date", {"decimal": "1"}), None))
    cases.append(("unknown-tag-field", single_invalid("decimal", {"decimal": "1", "extra": "x"}), None))
    cases.append(("invalid-decimal-empty", single_invalid("decimal", {"decimal": ""}), "invalid_scalar"))
    for label, spelling in (
        ("decimal-no-integer", ".5"),
        ("decimal-no-fraction", "5."),
        ("decimal-exponent", "1e3"),
        ("decimal-whitespace", " 1"),
        ("decimal-unicode-digit", "١"),
    ):
        cases.append((label, single_invalid("decimal", {"decimal": spelling}), "invalid_scalar"))
    cases.append(("decimal-coefficient-overflow", single_invalid("decimal", {"decimal": "9" * 39}), "scalar_overflow"))
    cases.append(("decimal-scale-overflow", single_invalid("decimal", {"decimal": "0." + "0" * 38 + "1"}), "scalar_overflow"))
    for label, spelling in (
        ("date-year-zero", "0000-01-01"),
        ("date-non-leap-century", "1900-02-29"),
        ("date-invalid-month", "2000-13-01"),
        ("date-invalid-day", "2000-04-31"),
        ("date-timestamp", "2000-02-29T00:00:00Z"),
        ("date-infinity", "infinity"),
        ("date-ascii-width", "20٢0-01-01"),
    ):
        cases.append((label, single_invalid("date", {"date": spelling}), "invalid_scalar"))

    bad_version = base_document("decimal")
    bad_version["updates"] = [{
        "schema_version": 1,
        "sequence": 1,
        "table": "T",
        "op": "insert",
        "values": [{"decimal": "1"}],
    }]
    cases.append(("update-version-mismatch", bad_version, "unsupported_version"))
    unsupported_root_version = base_document("int64")
    unsupported_root_version["schema_version"] = 4
    cases.append(("unsupported-root-version", unsupported_root_version, "unsupported_version"))

    unknown_collation = base_document("string")
    unknown_collation["catalog"]["tables"][0]["columns"][0]["collation"] = "case_insensitive"
    cases.append(("unknown-collation", unknown_collation, None))

    version_one_extended = base_document("decimal", version=1)
    version_one_extended["initial"][0]["rows"] = [[{"decimal": "1"}]]
    cases.append(("v1-rejects-decimal", version_one_extended, "unsupported_type"))

    for label, document, expected_code in cases:
        check_rejected(executable, document, temp, label, expected_code)
    return len(cases)


def model_crossjoin(
    initial_dates: list[tuple[int, str]],
    initial_decimals: list[tuple[int, str]],
    updates: list[tuple[str, int, int, Any]],
) -> dict[str, Any]:
    dates = {(row_id, typed_key("date", value)) for row_id, value in initial_dates}
    decimals = {(row_id, typed_key("decimal", value)) for row_id, value in initial_decimals}

    def result_rows() -> list[list[Any]]:
        projected = {(date_value, decimal_value) for _, date_value in dates for _, decimal_value in decimals}
        ordered = sorted(projected, key=lambda pair: (pair[0], pair[1]))
        return [
            [
                encode_value("date", date_value.isoformat()),
                encode_value("decimal", canonical_spelling("decimal", decimal_value)),
            ]
            for date_value, decimal_value in ordered
        ]

    output: dict[str, Any] = {
        "schema_version": 2,
        "backend": "reference_recompute",
        "semantics": "set",
        "initial": result_rows(),
        "epochs": [],
    }
    for sequence, (operation_sign, table, row_id, raw_value) in enumerate(updates, 1):
        before = result_rows()
        before_dates = set(dates)
        before_decimals = set(decimals)
        target = dates if table == 0 else decimals
        kind = "date" if table == 0 else "decimal"
        row = (row_id, typed_key(kind, raw_value))
        if operation_sign == "insert":
            target.add(row)
        else:
            target.discard(row)
        after = result_rows()
        before_set = {json_text(row) for row in before}
        after_set = {json_text(row) for row in after}
        added = [row for row in after if json_text(row) in after_set - before_set]
        removed = [row for row in before if json_text(row) in before_set - after_set]
        output["epochs"].append({
            "sequence": sequence,
            "input_changed": dates != before_dates or decimals != before_decimals,
            "current": after,
            "delta": {"added": added, "removed": removed},
        })
    return output


def crossjoin_document(
    initial_dates: list[tuple[int, str]],
    initial_decimals: list[tuple[int, str]],
    updates: list[tuple[str, int, int, Any]],
) -> dict[str, Any]:
    return {
        "schema_version": 2,
        "semantics": "set",
        "catalog": {"version": 1, "tables": [
            {"name": "D", "columns": [{"name": "id", "type": "int64"}, {"name": "d", "type": "date"}]},
            {"name": "N", "columns": [{"name": "id", "type": "int64"}, {"name": "n", "type": "decimal"}]},
        ]},
        "query": {
            "variables": [{"name": "d", "type": "date"}, {"name": "n", "type": "decimal"}],
            "atoms": [
                {"id": "date_witness", "table": "D", "terms": [{"ignore": True}, {"var": "d"}]},
                {"id": "number_witness", "table": "N", "terms": [{"ignore": True}, {"var": "n"}]},
            ],
            "head": [{"var": "d"}, {"var": "n"}],
        },
        "initial": [
            {"table": "D", "rows": [[row_id, {"date": value}] for row_id, value in initial_dates]},
            {"table": "N", "rows": [[row_id, {"decimal": value}] for row_id, value in initial_decimals]},
        ],
        "updates": [
            {
                "schema_version": 2,
                "sequence": sequence,
                "table": "D" if table == 0 else "N",
                "op": operation,
                "values": [row_id, encode_value("date" if table == 0 else "decimal", value)],
            }
            for sequence, (operation, table, row_id, value) in enumerate(updates, 1)
        ],
    }


def check_crossjoin(executable: str, temp: Path) -> None:
    initial_dates = [(1, "2000-02-29"), (2, "2000-02-29"), (3, "1900-02-28")]
    initial_decimals = [(10, "1.0"), (11, "1.00"), (12, "-0.000"), (13, "2.0")]
    updates = [
        ("delete", 0, 1, "2000-02-29"),
        ("delete", 0, 2, "2000-02-29"),
        ("delete", 1, 11, "1.0000"),
        ("delete", 1, 10, "1"),
        ("insert", 1, 20, "+0001.000"),
        ("delete", 0, 3, "1900-02-28"),
    ]
    document = crossjoin_document(initial_dates, initial_decimals, updates)
    expected = model_crossjoin(initial_dates, initial_decimals, updates)
    check_valid_document(executable, document, expected, temp, "date-decimal-crossjoin")


def check_v1(executable: str, temp: Path) -> None:
    document = base_document("int64", version=1)
    document["initial"][0]["rows"] = [[-2], [0], [4], [4]]
    status, result, stdout, stderr = call(executable, "oracle", document, temp, "version-one-legacy-types")
    require(status == 0, f"version-one legacy document rejected; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare("version-one result schema version", result.get("schema_version"), 1)
    compare("version-one initial relation", result.get("initial"), [[-2], [0], [4]])
    canonical_status, canonical, stdout, stderr = call(executable, "canonicalize", document, temp, "version-one-canonical")
    require(canonical_status == 0, f"version-one canonicalize failed; stdout={short(stdout)!r}; stderr={short(stderr)!r}")
    compare("version-one canonical root version", canonical.get("schema_version"), 1)


def main() -> int:
    if len(sys.argv) != 2:
        raise RuntimeError("usage: scalars.py CROWN_EXECUTABLE")
    executable = sys.argv[1]
    decimal_schema_document_check()
    valid_documents = 0
    with tempfile.TemporaryDirectory(prefix="crown-scalars-") as temporary:
        temp = Path(temporary)
        for kind, seed in (("date", 1701), ("decimal", 4207)):
            initial, updates = generated_scalars(kind, seed)
            document = single_document(kind, initial, updates)
            expected = model_single(kind, initial, updates)
            check_valid_document(executable, document, expected, temp, f"{kind}-seed-{seed}")
            valid_documents += 1
        check_crossjoin(executable, temp)
        valid_documents += 1
        rejected = check_invalid_documents(executable, temp)
        check_v1(executable, temp)
    print(f"F01 scalar checks passed: {valid_documents} valid documents, {rejected} invalid documents, and v1 compatibility")
    print("Independent oracle uses datetime.date and decimal.Decimal; deterministic seeds: date=1701, decimal=4207")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"scalar integration failure: {error}", file=sys.stderr)
        raise SystemExit(1)
