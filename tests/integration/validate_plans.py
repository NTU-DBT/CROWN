#!/usr/bin/env python3
"""Run hand-authored structural-plan fixtures through ``crown validate-plan``."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


def require(condition: bool, message: str) -> None:
    # Keep checks active when this script is invoked with ``python -O``.
    if not condition:
        raise RuntimeError(message)


def load_json(path: Path) -> Any:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise RuntimeError(f"{path}: cannot read JSON: {error}") from error


def is_integer(value: Any) -> bool:
    return isinstance(value, int) and not isinstance(value, bool)


def run_cli(executable: str, query: Path, plan: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [executable, "validate-plan", str(query), str(plan)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
    )


def parse_result(case_name: str, process: subprocess.CompletedProcess[str]) -> dict[str, Any]:
    try:
        result = json.loads(process.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(
            f"{case_name}: validate-plan stdout is not JSON: {error}\n"
            f"stdout:\n{process.stdout}\nstderr:\n{process.stderr}"
        ) from error

    require(isinstance(result, dict), f"{case_name}: result must be a JSON object")
    require(
        is_integer(result.get("schema_version")) and result["schema_version"] == 1,
        f"{case_name}: schema_version must be integer 1",
    )
    require(isinstance(result.get("tree_valid"), bool), f"{case_name}: tree_valid must be boolean")

    native_height = result.get("native_height")
    require(
        native_height is None or is_integer(native_height),
        f"{case_name}: native_height must be an integer or null",
    )
    edge_depth = result.get("edge_depth")
    require(
        edge_depth is None or is_integer(edge_depth),
        f"{case_name}: edge_depth must be an integer or null",
    )
    height_status = result.get("height_status")
    require(isinstance(height_status, str), f"{case_name}: height_status must be a string")
    require(
        height_status in {"valid_upper_bound", "invalid"},
        f"{case_name}: height_status has an unsupported value",
    )

    maximal_connex = result.get("maximal_connex")
    require(
        isinstance(maximal_connex, list)
        and all(isinstance(node, str) for node in maximal_connex),
        f"{case_name}: maximal_connex must be an array of node IDs",
    )
    separators = result.get("separators")
    require(isinstance(separators, list), f"{case_name}: separators must be an array")
    for separator in separators:
        require(isinstance(separator, dict), f"{case_name}: each separator must be an object")
        require(isinstance(separator.get("node"), str), f"{case_name}: separator node must be a string")
        variables = separator.get("variables")
        require(
            isinstance(variables, list) and all(isinstance(variable, str) for variable in variables),
            f"{case_name}: separator variables must be an array of strings",
        )

    violations = result.get("violations")
    require(isinstance(violations, list), f"{case_name}: violations must be an array")
    for violation in violations:
        require(isinstance(violation, dict), f"{case_name}: each violation must be an object")
        require(isinstance(violation.get("rule"), str), f"{case_name}: violation rule must be a string")
        require(isinstance(violation.get("message"), str), f"{case_name}: violation message must be a string")
        for field in ("node", "variable", "occurrence", "related_node"):
            if field in violation:
                require(
                    isinstance(violation[field], str),
                    f"{case_name}: violation {field} must be a string when present",
                )
    return result


def check_case(executable: str, fixture_dir: Path, case: Any) -> None:
    require(isinstance(case, dict), "manifest case must be an object")
    name = case.get("name")
    require(isinstance(name, str) and name, "manifest case name must be a non-empty string")
    query_rel = case.get("query")
    plan_rel = case.get("plan")
    require(isinstance(query_rel, str), f"{name}: query path must be a string")
    require(isinstance(plan_rel, str), f"{name}: plan path must be a string")
    query = fixture_dir / query_rel
    plan = fixture_dir / plan_rel
    require(query.is_file(), f"{name}: query file does not exist: {query}")
    require(plan.is_file(), f"{name}: plan file does not exist: {plan}")

    expected_valid = case.get("valid")
    require(isinstance(expected_valid, bool), f"{name}: valid must be boolean")
    expected_height = case.get("expected_native_height")
    require(
        expected_height is None or is_integer(expected_height),
        f"{name}: expected_native_height must be an integer or null",
    )
    expected_rules = case.get("expected_violations")
    require(
        isinstance(expected_rules, list)
        and all(isinstance(rule, str) for rule in expected_rules),
        f"{name}: expected_violations must be an array of rule names",
    )

    process = run_cli(executable, query, plan)
    expected_exit = 0 if expected_valid else 1
    require(
        process.returncode == expected_exit,
        f"{name}: expected exit {expected_exit}, got {process.returncode}\n"
        f"stdout:\n{process.stdout}\nstderr:\n{process.stderr}",
    )
    result = parse_result(name, process)
    require(
        result["tree_valid"] is expected_valid,
        f"{name}: tree_valid expected {expected_valid}, got {result['tree_valid']}",
    )
    require(
        result["native_height"] == expected_height,
        f"{name}: native_height expected {expected_height}, got {result['native_height']}",
    )
    require(
        result["height_status"] == ("valid_upper_bound" if expected_valid else "invalid"),
        f"{name}: height_status is inconsistent with tree_valid",
    )
    require(
        is_integer(result["edge_depth"]) if expected_valid else result["edge_depth"] is None,
        f"{name}: edge_depth must be an integer for a valid tree and null otherwise",
    )

    actual_rules = [violation["rule"] for violation in result["violations"]]
    require(
        set(actual_rules) == set(expected_rules),
        f"{name}: expected violation rules {sorted(set(expected_rules))}, "
        f"got {sorted(set(actual_rules))}",
    )
    if expected_valid:
        require(not actual_rules, f"{name}: valid plan unexpectedly has violations")
    else:
        require(bool(actual_rules), f"{name}: invalid plan must report at least one violation")

    witnesses = case.get("expected_witnesses", [])
    require(isinstance(witnesses, list), f"{name}: expected_witnesses must be an array")
    for expected in witnesses:
        require(isinstance(expected, dict), f"{name}: each expected witness must be an object")
        rule = expected.get("rule")
        require(isinstance(rule, str), f"{name}: expected witness rule must be a string")
        matches = [item for item in result["violations"] if item["rule"] == rule]
        require(bool(matches), f"{name}: missing violation witness for rule {rule}")
        fields = {key: value for key, value in expected.items() if key != "rule"}
        require(
            any(all(item.get(key) == value for key, value in fields.items()) for item in matches),
            f"{name}: no {rule} violation carries expected witness fields {fields}",
        )

    if "expected_maximal_connex" in case:
        expected_connex = case["expected_maximal_connex"]
        require(
            isinstance(expected_connex, list)
            and all(isinstance(node, str) for node in expected_connex),
            f"{name}: expected_maximal_connex must be an array of node IDs",
        )
        actual_connex = result["maximal_connex"]
        require(
            len(actual_connex) == len(set(actual_connex))
            and set(actual_connex) == set(expected_connex),
            f"{name}: expected maximal connex nodes {sorted(expected_connex)}, "
            f"got {sorted(actual_connex)}",
        )


def check_malformed_input(executable: str, fixture_dir: Path, case: Any) -> None:
    query = fixture_dir / case["query"]
    with tempfile.TemporaryDirectory(prefix="crown-invalid-plan-") as temporary:
        malformed_plan = Path(temporary) / "malformed.tree.json"
        malformed_plan.write_text("{\n", encoding="utf-8")
        process = run_cli(executable, query, malformed_plan)
    require(
        process.returncode == 2,
        f"malformed plan: expected exit 2, got {process.returncode}\n"
        f"stdout:\n{process.stdout}\nstderr:\n{process.stderr}",
    )
    require(not process.stdout.strip(), "malformed plan: expected diagnostics on stderr")
    try:
        diagnostic = json.loads(process.stderr)
    except json.JSONDecodeError as error:
        raise RuntimeError(f"malformed plan: stderr must be JSON: {error}\n{process.stderr}") from error
    require(isinstance(diagnostic, dict), "malformed plan: stderr JSON must be an object")
    error = diagnostic.get("error")
    require(isinstance(error, dict), "malformed plan: expected error object")
    require(error.get("code") == "invalid_document", "malformed plan: expected invalid_document diagnostic")
    require(isinstance(error.get("message"), str) and bool(error["message"]), "malformed plan: expected diagnostic message")


def main() -> int:
    if len(sys.argv) != 3:
        raise RuntimeError("usage: validate_plans.py EXECUTABLE FIXTURE_DIRECTORY")

    executable = sys.argv[1]
    fixture_dir = Path(sys.argv[2])
    manifest_path = fixture_dir / "manifest.json"
    manifest = load_json(manifest_path)
    require(isinstance(manifest, dict), f"{manifest_path}: manifest must be an object")
    require(
        is_integer(manifest.get("schema_version")) and manifest["schema_version"] == 1,
        f"{manifest_path}: schema_version must be integer 1",
    )
    cases = manifest.get("cases")
    require(isinstance(cases, list) and bool(cases), f"{manifest_path}: cases must be a non-empty array")

    for case in cases:
        check_case(executable, fixture_dir, case)
    check_malformed_input(executable, fixture_dir, cases[0])
    print(f"{len(cases)} structural plan fixtures and malformed-input check passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"plan fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
