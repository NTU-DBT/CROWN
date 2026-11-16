#!/usr/bin/env python3
"""Check syntax-only SQL parser fixtures against the pinned AST contract."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


def require(condition: bool, message: str) -> None:
    # Keep validation active when this script is invoked with ``python -O``.
    if not condition:
        raise RuntimeError(message)


def read_json(path: Path) -> Any:
    try:
        def reject_constant(value: str) -> Any:
            raise ValueError(f"non-JSON numeric constant {value}")

        return json.loads(path.read_text(encoding="utf-8"), parse_constant=reject_constant)
    except (OSError, UnicodeError, json.JSONDecodeError, ValueError) as error:
        raise RuntimeError(f"{path}: cannot read JSON: {error}") from error


def canonical_json(value: Any) -> str:
    # JSON serialization preserves scalar types (unlike Python equality, where
    # True == 1) and removes irrelevant object key ordering.
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":"))


def compare(actual: Any, expected: Any, label: str) -> None:
    if canonical_json(actual) == canonical_json(expected):
        return
    actual_text = json.dumps(actual, ensure_ascii=False, sort_keys=True, indent=2)
    expected_text = json.dumps(expected, ensure_ascii=False, sort_keys=True, indent=2)
    raise RuntimeError(f"{label}: JSON mismatch\nexpected:\n{expected_text}\nactual:\n{actual_text}")


def decode_output(data: bytes, case_name: str, stream: str) -> str:
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError as error:
        raise RuntimeError(f"{case_name}: {stream} is not UTF-8: {error}") from error


def parse_output(case_name: str, process: subprocess.CompletedProcess[bytes]) -> dict[str, Any]:
    stdout = decode_output(process.stdout, case_name, "stdout")
    try:
        result = json.loads(stdout, parse_constant=lambda value: (_ for _ in ()).throw(
            ValueError(f"non-JSON numeric constant {value}")))
    except (json.JSONDecodeError, ValueError) as error:
        stderr = decode_output(process.stderr, case_name, "stderr")
        raise RuntimeError(
            f"{case_name}: parse-sql stdout is not JSON: {error}\n"
            f"stdout:\n{stdout}\nstderr:\n{stderr}"
        ) from error
    require(isinstance(result, dict), f"{case_name}: parse-sql result must be an object")
    return result


def input_bytes(base: Path, case: Any) -> bytes:
    require(isinstance(case, dict), "manifest case must be an object")
    if "input" in case:
        relative = case["input"]
        require(isinstance(relative, str), f"{case.get('name', 'case')}: input path must be a string")
        path = (base / relative).resolve()
        require(path.is_relative_to(base.resolve()), f"{case.get('name', 'case')}: input path escapes fixture directory")
        try:
            return path.read_bytes()
        except OSError as error:
            raise RuntimeError(f"{case.get('name', 'case')}: cannot read {path}: {error}") from error

    if "input_hex" in case:
        value = case["input_hex"]
        require(isinstance(value, str), f"{case.get('name', 'case')}: input_hex must be a string")
        try:
            return bytes.fromhex(value)
        except ValueError as error:
            raise RuntimeError(f"{case.get('name', 'case')}: invalid input_hex: {error}") from error

    generated = case.get("generated_input")
    require(isinstance(generated, dict), f"{case.get('name', 'case')}: missing input description")
    if "total_bytes" in generated:
        prefix_hex = generated.get("prefix_hex")
        fill_hex = generated.get("fill_hex")
        total = generated.get("total_bytes")
        require(isinstance(prefix_hex, str), f"{case['name']}: prefix_hex must be a string")
        require(isinstance(fill_hex, str), f"{case['name']}: fill_hex must be a string")
        require(type(total) is int and total >= 0, f"{case['name']}: total_bytes must be a nonnegative integer")
        try:
            prefix = bytes.fromhex(prefix_hex)
            fill = bytes.fromhex(fill_hex)
        except ValueError as error:
            raise RuntimeError(f"{case['name']}: invalid generated hex input: {error}") from error
        require(len(fill) == 1, f"{case['name']}: fill_hex must encode exactly one byte")
        require(len(prefix) <= total, f"{case['name']}: total_bytes is shorter than the prefix")
        return prefix + fill * (total - len(prefix))

    prefix = generated.get("prefix")
    repeat = generated.get("repeat")
    count = generated.get("repeat_count")
    suffix = generated.get("suffix")
    require(isinstance(prefix, str), f"{case['name']}: generated prefix must be a string")
    require(isinstance(repeat, str), f"{case['name']}: generated repeat must be a string")
    require(type(count) is int and count >= 0, f"{case['name']}: repeat_count must be a nonnegative integer")
    require(isinstance(suffix, str), f"{case['name']}: generated suffix must be a string")
    return (prefix + repeat * count + suffix).encode("utf-8")


def run_case(executable: str, base: Path, temporary: Path, case: Any, successful: bool) -> None:
    require(isinstance(case, dict), "manifest case must be an object")
    name = case.get("name")
    require(isinstance(name, str) and name, "case name must be a nonempty string")
    payload = input_bytes(base, case)
    source_path = temporary / f"{name}.sql"
    source_path.write_bytes(payload)
    try:
        process = subprocess.run(
            [executable, "parse-sql", str(source_path)],
            check=False,
            capture_output=True,
            timeout=20,
        )
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(f"{name}: parse-sql exceeded the 20 second fixture timeout") from error

    expected_exit = 0 if successful else 1
    stderr = decode_output(process.stderr, name, "stderr")
    require(
        process.returncode == expected_exit,
        f"{name}: expected exit {expected_exit}, got {process.returncode}\n"
        f"stdout:\n{decode_output(process.stdout, name, 'stdout')}\nstderr:\n{stderr}",
    )
    require(not stderr, f"{name}: parse-sql must emit its JSON result on stdout, got stderr:\n{stderr}")
    actual = parse_output(name, process)
    common = {
        "schema_version": 1,
        "parser": "libpg_query",
        "parser_version": "18.1.0",
        "postgres_version": 180006,
        "admission_status": "not_checked",
    }

    if successful:
        require(set(actual) == set(common) | {"syntax_valid", "source", "statement", "ast"},
                f"{name}: success result has unexpected fields: {sorted(actual)}")
        for key, value in common.items():
            compare(actual.get(key), value, f"{name}: {key}")
        require(actual.get("syntax_valid") is True, f"{name}: syntax_valid must be boolean true")
        try:
            source = payload.decode("utf-8")
        except UnicodeDecodeError as error:
            raise RuntimeError(f"{name}: success fixture input is not valid UTF-8") from error
        compare(actual.get("source"), source, f"{name}: source preservation")
        snapshot_rel = case.get("snapshot")
        require(isinstance(snapshot_rel, str), f"{name}: snapshot path must be a string")
        snapshot_path = (base / snapshot_rel).resolve()
        require(snapshot_path.is_relative_to(base.resolve()), f"{name}: snapshot path escapes fixture directory")
        snapshot = read_json(snapshot_path)
        require(isinstance(snapshot, dict), f"{name}: snapshot must be an object")
        require(set(snapshot) == {"statement", "ast"}, f"{name}: snapshot must contain statement and ast only")
        compare({"statement": actual.get("statement"), "ast": actual.get("ast")}, snapshot,
                f"{name}: upstream AST and byte-range snapshot")
        statement = actual.get("statement")
        require(isinstance(statement, dict) and set(statement) == {"begin", "end"},
                f"{name}: statement must contain begin and end only")
        require(type(statement.get("begin")) is int and statement["begin"] >= 0,
                f"{name}: statement.begin must be a nonnegative integer")
        require(type(statement.get("end")) is int and statement["end"] >= statement["begin"],
                f"{name}: statement.end must be an integer at or after begin")
        ast = actual.get("ast")
        require(isinstance(ast, dict) and type(ast.get("version")) is int and ast["version"] == 180006,
                f"{name}: AST must preserve PostgreSQL parser version 180006")
        require(isinstance(ast.get("stmts"), list) and len(ast["stmts"]) == 1,
                f"{name}: AST must retain exactly one upstream RawStmt")
        return

    require(set(actual) == set(common) | {"syntax_valid", "diagnostic"},
            f"{name}: failure result has unexpected fields: {sorted(actual)}")
    for key, value in common.items():
        compare(actual.get(key), value, f"{name}: {key}")
    require(actual.get("syntax_valid") is False, f"{name}: syntax_valid must be boolean false")
    expected = case.get("expected")
    require(isinstance(expected, dict), f"{name}: expected diagnostic must be an object")
    require(set(expected) == {"code", "message", "byte_offset", "character_position", "line", "column"},
            f"{name}: expected diagnostic has unexpected fields")
    diagnostic = actual.get("diagnostic")
    require(isinstance(diagnostic, dict), f"{name}: diagnostic must be an object")
    require(set(diagnostic) == set(expected), f"{name}: diagnostic fields differ from the contract")
    compare(diagnostic, expected, f"{name}: diagnostic")


def main() -> int:
    if len(sys.argv) != 3:
        raise RuntimeError("usage: parse_sql.py EXECUTABLE FIXTURE_DIRECTORY")
    executable = sys.argv[1]
    base = Path(sys.argv[2]).resolve()
    manifest = read_json(base / "manifest.json")
    require(isinstance(manifest, dict), "manifest must be an object")
    require(type(manifest.get("schema_version")) is int and manifest["schema_version"] == 1,
            "manifest schema_version must be integer 1")
    successes = manifest.get("success_cases")
    failures = manifest.get("failure_cases")
    require(isinstance(successes, list) and successes, "manifest success_cases must be a nonempty array")
    require(isinstance(failures, list) and failures, "manifest failure_cases must be a nonempty array")
    schema = read_json(base.parents[2] / "schemas" / "sql-syntax-v1.schema.json")
    require(isinstance(schema, dict) and schema.get("$schema") == "https://json-schema.org/draft/2020-12/schema",
            "SQL schema must be a JSON Schema 2020-12 document")

    with tempfile.TemporaryDirectory(prefix="crown-parse-sql-") as temporary:
        temp_path = Path(temporary)
        names: set[str] = set()
        for case in successes:
            require(isinstance(case, dict), "success case must be an object")
            name = case.get("name")
            require(isinstance(name, str) and name not in names, f"duplicate or invalid case name: {name}")
            names.add(name)
            run_case(executable, base, temp_path, case, successful=True)
        for case in failures:
            require(isinstance(case, dict), "failure case must be an object")
            name = case.get("name")
            require(isinstance(name, str) and name not in names, f"duplicate or invalid case name: {name}")
            names.add(name)
            run_case(executable, base, temp_path, case, successful=False)
    print(f"{len(successes)} SQL syntax snapshots and {len(failures)} diagnostics passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"SQL parser fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
