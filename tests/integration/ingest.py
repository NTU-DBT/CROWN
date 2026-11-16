#!/usr/bin/env python3
"""CLI checks for bounded physical input diagnostics."""
from __future__ import annotations

import hashlib
import json
import struct
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


TIMEOUT_SECONDS = 60
CATALOG_LIMIT = 16 * 1024 * 1024
RECORD_LIMIT = 1024 * 1024
INT64_MIN = -(1 << 63)
INT64_MAX = (1 << 63) - 1


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def json_text(value: Any) -> str:
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":"))


def run(executable: str, arguments: list[str]) -> subprocess.CompletedProcess[str]:
    try:
        return subprocess.run(
            [executable, *arguments],
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            timeout=TIMEOUT_SECONDS,
            check=False,
        )
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(f"{arguments[0]} timed out after {TIMEOUT_SECONDS}s") from error


def expect_summary(
    executable: str,
    catalog_path: Path,
    input_path: Path,
    fmt: str,
    catalog_hash: str,
    records: int,
    data: bytes,
    sequence: int,
    positions: dict[str, int],
    table: str | None = None,
) -> None:
    arguments = ["validate-input", str(catalog_path), fmt, str(input_path)]
    if table is not None:
        arguments.append(table)
    result = run(executable, arguments)
    require(result.returncode == 0, f"{fmt} rejected valid input: {result.stderr} {result.stdout[:300]}")
    require(not result.stderr, f"{fmt} wrote unexpected stderr: {result.stderr!r}")
    try:
        actual = json.loads(result.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(f"{fmt} did not return one JSON summary: {result.stdout[:300]!r}") from error
    expected = {
        "schema_version": 1,
        "input_valid": True,
        "format": fmt,
        "catalog_sha256": catalog_hash,
        "records": records,
        "bytes": len(data),
        "sequence": sequence,
        "source_positions": positions,
    }
    require(actual == expected, f"{fmt} summary mismatch\nexpected: {json_text(expected)}\nactual:   {json_text(actual)}")
    require(result.stdout.endswith("\n"), f"{fmt} summary omitted its final newline")


def expect_rejection(
    executable: str,
    arguments: list[str],
    expected_code: str,
    label: str,
) -> None:
    result = run(executable, arguments)
    require(result.returncode != 0, f"{label}: invalid input unexpectedly succeeded")
    require(not result.stdout, f"{label}: rejected input emitted a partial summary: {result.stdout[:300]!r}")
    try:
        error = json.loads(result.stderr)["error"]
    except (json.JSONDecodeError, KeyError, TypeError) as exception:
        raise RuntimeError(f"{label}: missing structured diagnostic: {result.stderr[:300]!r}") from exception
    require(error.get("code") == expected_code, f"{label}: expected {expected_code}, got {error.get('code')!r}")


def put_string(output: bytearray, value: str) -> None:
    encoded = value.encode("utf-8")
    output.extend(struct.pack("<I", len(encoded)))
    output.extend(encoded)


def binary_value(value: Any) -> bytes:
    if isinstance(value, bool):
        return b"\x02" + (b"\x01" if value else b"\x00")
    if isinstance(value, int):
        return b"\x00" + struct.pack("<q", value)
    if isinstance(value, str):
        encoded = value.encode("utf-8")
        return b"\x01" + struct.pack("<I", len(encoded)) + encoded
    if "date" in value:
        return b"\x03" + value["date"].encode("ascii")
    if "decimal" in value:
        encoded = value["decimal"].encode("ascii")
        return b"\x04" + struct.pack("<I", len(encoded)) + encoded
    raise RuntimeError(f"unsupported fixture scalar: {value!r}")


def binary_frame(
    catalog_version: int,
    source_schema_version: int,
    catalog_hash: str,
    sequence: int,
    table: str,
    operation: str,
    position: tuple[str, int] | None,
    values: list[Any],
) -> bytes:
    payload = bytearray()
    payload.extend(struct.pack("<Q", catalog_version))
    payload.extend(struct.pack("<Q", source_schema_version))
    payload.extend(catalog_hash.encode("ascii"))
    payload.extend(struct.pack("<Q", sequence))
    put_string(payload, table)
    payload.append(1 if operation == "insert" else 2)
    payload.append(1 if position is not None else 0)
    if position is not None:
        put_string(payload, position[0])
        payload.extend(struct.pack("<Q", position[1]))
    payload.extend(struct.pack("<I", len(values)))
    for value in values:
        payload.extend(binary_value(value))
    return b"CROWNUPD" + struct.pack("<HI", 1, len(payload)) + payload


def event(
    catalog_hash: str,
    sequence: int,
    operation: str,
    values: list[Any],
    source: str = "源.csv",
    offset: int = 0,
    version: int = 1,
) -> dict[str, Any]:
    return {
        "schema_version": version,
        "catalog_version": 41,
        "source_schema_version": 7,
        "catalog_sha256": catalog_hash,
        "sequence": sequence,
        "table": "Typed",
        "operation": operation,
        "values": values,
        "source_position": {"source": source, "offset": offset},
    }


def write_jsonl(path: Path, events: list[dict[str, Any]]) -> bytes:
    data = ("".join(json.dumps(item, ensure_ascii=False, separators=(",", ":")) + "\n" for item in events)).encode("utf-8")
    path.write_bytes(data)
    return data


def main() -> int:
    require(len(sys.argv) == 3, "usage: ingest.py CROWN_EXECUTABLE REPOSITORY")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(sys.argv[2]).resolve()
    require((root / "tests/unit/ingest_test.cpp").is_file(), f"repository path does not contain ingestion tests: {root}")
    catalog_document = {
        "schema_version": 1,
        "catalog": {
            "version": 41,
            "tables": [
                {
                    "name": "Typed",
                    "source_schema_version": 7,
                    "columns": [
                        {"name": "id", "type": "int64"},
                        {"name": "text", "type": "string"},
                        {"name": "enabled", "type": "bool"},
                        {"name": "day", "type": "date"},
                        {"name": "amount", "type": "decimal", "decimal": {"precision": 12, "scale": 3}},
                    ],
                    "constraints": [
                        {"kind": "unique", "name": "typed_id", "columns": ["id"], "status": "enforced"}
                    ],
                    "statistics": {
                        "row_count": 2,
                        "distinct_counts": [{"columns": ["id"], "estimate": 2}],
                    },
                    "key_hints": [{"columns": ["id"], "reason": "source key 雪"}],
                }
            ],
        },
    }

    checks = 0
    with tempfile.TemporaryDirectory(prefix="crown-ingest-cli-") as directory:
        temp = Path(directory)
        catalog_path = temp / "catalog.json"
        catalog_path.write_text(json.dumps(catalog_document, ensure_ascii=False), encoding="utf-8")
        canonical = run(executable, ["canonicalize-catalog", str(catalog_path)])
        require(canonical.returncode == 0 and not canonical.stderr, "fixture catalog could not be canonicalized")
        canonical_value = json.loads(canonical.stdout)
        canonical_bytes = json.dumps(
            canonical_value, ensure_ascii=False, sort_keys=True, separators=(",", ":")
        ).encode("utf-8")
        catalog_hash = hashlib.sha256(canonical_bytes).hexdigest()

        # JSONL is hand-authored physical metadata with typed scalars and exact boundaries.
        json_rows = [
            [INT64_MAX, "A\0B雪", True, {"date": "0001-01-01"}, {"decimal": "999999999.999"}],
            [INT64_MIN, "second", False, {"date": "2024-02-29"}, {"decimal": "-999999999.999"}],
        ]
        json_events = [
            event(catalog_hash, 1, "insert", json_rows[0], offset=17),
            event(catalog_hash, 2, "delete", json_rows[1], offset=41),
        ]
        json_path = temp / "typed.jsonl"
        json_data = write_jsonl(json_path, json_events)
        expect_summary(executable, catalog_path, json_path, "jsonl", catalog_hash, 2, json_data, 2, {"源.csv": 41})
        checks += 1

        # Independently assembled public CROWNUPD v1 frames exercise the binary stream path.
        binary_data = b"".join(
            [
                binary_frame(41, 7, catalog_hash, 1, "Typed", "insert", ("源.csv", 17), json_rows[0]),
                binary_frame(41, 7, catalog_hash, 2, "Typed", "delete", ("源.csv", 41), json_rows[1]),
            ]
        )
        binary_path = temp / "typed.bin"
        binary_path.write_bytes(binary_data)
        expect_summary(executable, catalog_path, binary_path, "binary", catalog_hash, 2, binary_data, 2, {"源.csv": 41})
        checks += 1

        # CSV binds a complete, permuted header and preserves the source's full row.
        csv_data = (
            'day,text,amount,id,enabled\n'
            '2024-02-29,"CSV, 雪",123.456,9223372036854775807,true\n'
            '0001-01-01,"embedded ""quote""",0.001,-9223372036854775808,false\n'
        ).encode("utf-8")
        csv_path = temp / "typed.csv"
        csv_path.write_bytes(csv_data)
        expect_summary(executable, catalog_path, csv_path, "csv", catalog_hash, 2, csv_data, 2, {}, "Typed")
        checks += 1

        legacy_inputs = {
            "legacy-signed": (
                '+,9223372036854775807,"signed, 雪",true,2024-03-01,12.345\n'
                '-,-9223372036854775808,negative,false,2024-03-02,-0.001\n'
            ),
            "legacy-insert-only": (
                '9223372036854775807,inserted,true,2024-03-03,12.345\n'
                '-9223372036854775808,again,false,2024-03-04,-0.001\n'
            ),
            "legacy-flags": (
                '1,9223372036854775807,flagged,true,2024-03-05,12.345\n'
                '0,-9223372036854775808,removed,false,2024-03-06,-0.001\n'
            ),
        }
        for fmt, contents in legacy_inputs.items():
            data = contents.encode("utf-8")
            path = temp / f"{fmt}.txt"
            path.write_bytes(data)
            expect_summary(executable, catalog_path, path, fmt, catalog_hash, 2, data, 2, {}, "Typed")
            checks += 1

        # A bad later record must suppress the summary even after earlier events were acknowledged.
        def bad_json(label: str, first: dict[str, Any], later: dict[str, Any], code: str) -> None:
            path = temp / f"{label}.jsonl"
            write_jsonl(path, [first, later])
            expect_rejection(
                executable,
                ["validate-input", str(catalog_path), "jsonl", str(path)],
                code,
                label,
            )

        good_first = event(catalog_hash, 1, "insert", json_rows[0], source="progress", offset=30)
        bad_json("sequence-gap", good_first, event(catalog_hash, 3, "insert", json_rows[1], source="progress", offset=50), "invalid_sequence")
        bad_json("nonincreasing-source-offset", good_first, event(catalog_hash, 2, "delete", json_rows[1], source="progress", offset=30), "invalid_source_position")
        bad_json("unsupported-schema", event(catalog_hash, 1, "insert", json_rows[0], version=2), event(catalog_hash, 2, "delete", json_rows[1]), "unsupported_version")
        bad_json("unknown-operation", good_first, event(catalog_hash, 2, "replace", json_rows[1]), "unsupported_input_operation")
        bad_json("floating-point-scalar", good_first, event(catalog_hash, 2, "insert", [1.5, "x", True, {"date": "2024-01-01"}, {"decimal": "1.000"}]), "invalid_document")
        bad_json("null-scalar", good_first, event(catalog_hash, 2, "insert", [2, None, True, {"date": "2024-01-01"}, {"decimal": "1.000"}]), "invalid_document")
        malformed_path = temp / "malformed.jsonl"
        malformed_path.write_text('{"schema_version":1,\n', encoding="utf-8")
        expect_rejection(executable, ["validate-input", str(catalog_path), "jsonl", str(malformed_path)], "invalid_document", "malformed-jsonl")

        truncated_path = temp / "truncated.bin"
        truncated_path.write_bytes(binary_data[:-1])
        expect_rejection(executable, ["validate-input", str(catalog_path), "binary", str(truncated_path)], "invalid_document", "truncated-binary")

        missing_path = temp / "missing.jsonl"
        expect_rejection(executable, ["validate-input", str(catalog_path), "jsonl", str(missing_path)], "io_error", "missing-input-file")
        expect_rejection(executable, ["validate-input", str(catalog_path), "unknown", str(json_path)], "unsupported_input_format", "unknown-format")
        expect_rejection(executable, ["validate-input", str(catalog_path), "legacy-relations", str(json_path)], "unsupported_input_format", "unsupported-relation-token-cli-profile")
        expect_rejection(executable, ["validate-input", str(catalog_path), "csv", str(csv_path)], "usage", "csv-missing-table")
        expect_rejection(executable, ["validate-input", str(catalog_path), "legacy-flags", str(csv_path)], "usage", "legacy-missing-table")
        expect_rejection(executable, ["validate-input", str(catalog_path), "csv", str(csv_path), "typed"], "unknown_table", "exact-table-name")
        expect_rejection(executable, ["validate-input", str(catalog_path), "jsonl", str(json_path), "Typed"], "usage", "unexpected-table")
        checks += 15

        # The catalog and record bounds are checked before a whole oversized input can be accepted.
        oversized_catalog = temp / "oversized-catalog.json"
        oversized_catalog.write_bytes(b" " * (CATALOG_LIMIT + 1))
        expect_rejection(executable, ["validate-input", str(oversized_catalog), "jsonl", str(json_path)], "resource_limit", "catalog-over-16-mib")
        oversized_input = temp / "oversized.jsonl"
        oversized_input.write_bytes(b"x" * (RECORD_LIMIT + 1))
        expect_rejection(executable, ["validate-input", str(catalog_path), "jsonl", str(oversized_input)], "resource_limit", "record-over-1-mib")
        checks += 2

    print(f"ingest CLI checks passed: {checks} valid-format and rejection checks; catalog SHA-256 computed independently")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"ingest integration failure: {error}", file=sys.stderr)
        raise SystemExit(1)
