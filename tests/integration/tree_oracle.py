#!/usr/bin/env python3
"""Check exact structural minima and independently replay their certificates."""

from __future__ import annotations

import copy
import json
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


TIMEOUT_SECONDS = 60
DEFAULT_FIXTURES = Path(__file__).resolve().parents[1] / "structural" / "oracle"


def require(condition: bool, message: str) -> None:
    # Keep test assertions enabled when this script is invoked with ``python -O``.
    if not condition:
        raise RuntimeError(message)


def is_integer(value: Any) -> bool:
    return isinstance(value, int) and not isinstance(value, bool)


def short(value: Any, limit: int = 1200) -> str:
    if isinstance(value, bytes):
        value = value.decode("utf-8", errors="replace")
    if not isinstance(value, str):
        value = json.dumps(value, ensure_ascii=False, sort_keys=True)
    return value if len(value) <= limit else value[:limit] + "…"


def load_json(path: Path) -> Any:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise RuntimeError(f"{path}: cannot read JSON: {error}") from error


def parse_stdout(label: str, process: subprocess.CompletedProcess[str]) -> dict[str, Any]:
    try:
        result = json.loads(process.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(
            f"{label}: stdout is not JSON: {error}; stdout={short(process.stdout)!r}; "
            f"stderr={short(process.stderr)!r}"
        ) from error
    require(isinstance(result, dict), f"{label}: JSON result must be an object")
    return result


def invoke(executable: str, args: list[str], label: str) -> subprocess.CompletedProcess[str]:
    try:
        return subprocess.run(
            [executable, *args],
            check=False,
            capture_output=True,
            text=True,
            encoding="utf-8",
            timeout=TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(
            f"{label}: timed out after {TIMEOUT_SECONDS}s; "
            f"stdout={short(error.stdout)!r}; stderr={short(error.stderr)!r}"
        ) from error


def checked_status(label: str, result: dict[str, Any]) -> None:
    require(
        is_integer(result.get("schema_version")) and result["schema_version"] == 1,
        f"{label}: schema_version must be integer 1",
    )
    require(
        isinstance(result.get("height_status"), str),
        f"{label}: height_status must be a string",
    )
    require(
        result["height_status"] in {"proven_minimum", "resource_limit", "unsupported"},
        f"{label}: unsupported height_status {result['height_status']!r}",
    )
    for field in ("selected_height", "height_lower_bound", "height_upper_bound"):
        value = result.get(field)
        require(value is None or is_integer(value), f"{label}: {field} must be an integer or null")
    require(isinstance(result.get("tree_valid"), bool), f"{label}: tree_valid must be boolean")
    require(
        isinstance(result.get("height_search_complete"), bool),
        f"{label}: height_search_complete must be boolean",
    )
    require(
        result.get("cost_search_complete") is False,
        f"{label}: cost_search_complete must be false for the structural oracle",
    )
    require(isinstance(result.get("tree"), (dict, type(None))), f"{label}: tree must be an object or null")
    require(
        isinstance(result.get("certificate"), (dict, type(None))),
        f"{label}: certificate must be an object or null",
    )
    require(isinstance(result.get("search"), dict), f"{label}: search must be an object")


def verify_output(label: str, process: subprocess.CompletedProcess[str], *, valid: bool) -> dict[str, Any]:
    expected_exit = 0 if valid else 1
    require(
        process.returncode == expected_exit,
        f"{label}: expected exit {expected_exit}, got {process.returncode}; "
        f"stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}",
    )
    result = parse_stdout(label, process)
    require(
        is_integer(result.get("schema_version")) and result["schema_version"] == 1,
        f"{label}: schema_version must be integer 1",
    )
    require(isinstance(result.get("certificate_valid"), bool), f"{label}: certificate_valid must be boolean")
    require(isinstance(result.get("resource_limit"), bool), f"{label}: resource_limit must be boolean")
    require(result["certificate_valid"] is valid, f"{label}: certificate_valid expected {valid}")
    require(result["resource_limit"] is False, f"{label}: verification unexpectedly hit its work limit")
    return result


def atom_signature(query: dict[str, Any]) -> dict[str, tuple[str, list[Any]]]:
    return {
        atom["id"]: (atom["table"], atom["terms"])
        for atom in query["atoms"]
    }


def catalog_signature(catalog: dict[str, Any]) -> dict[str, list[tuple[str, str]]]:
    return {
        table["name"]: [(column["name"], column["type"]) for column in table["columns"]]
        for table in catalog["tables"]
    }


def check_query_binding(label: str, original: dict[str, Any], binding: Any) -> None:
    require(isinstance(binding, dict), f"{label}: certificate query_binding must be an object")
    require(binding.get("schema_version") == 1, f"{label}: query_binding schema_version must be 1")
    require(binding.get("semantics") == original.get("semantics"), f"{label}: query_binding semantics changed")
    require(
        catalog_signature(binding.get("catalog", {})) == catalog_signature(original["catalog"]),
        f"{label}: certificate is bound to a different catalog",
    )
    bound_query = binding.get("query")
    require(isinstance(bound_query, dict), f"{label}: query_binding.query must be an object")
    original_query = original["query"]
    bound_variables = {item["name"]: item["type"] for item in bound_query.get("variables", [])}
    original_variables = {item["name"]: item["type"] for item in original_query["variables"]}
    require(bound_variables == original_variables, f"{label}: certificate is bound to different variables")
    require(
        atom_signature(bound_query) == atom_signature(original_query),
        f"{label}: certificate is bound to different atom occurrences or terms",
    )
    require(
        [item["var"] for item in bound_query.get("head", [])]
        == [item["var"] for item in original_query["head"]],
        f"{label}: certificate is bound to a different head",
    )
    require(isinstance(binding.get("initial"), list), f"{label}: query_binding.initial must be an array")
    require(
        {item.get("table"): item.get("rows") for item in binding["initial"]}
        == {table["name"]: [] for table in original["catalog"]["tables"]},
        f"{label}: query_binding must have empty initial relations",
    )
    require(binding.get("updates") == [], f"{label}: query_binding must have no updates")


def check_certificate(
    label: str,
    query_path: Path,
    original: dict[str, Any],
    result: dict[str, Any],
    temp: Path,
    executable: str,
    expected_height: int | None,
) -> dict[str, Any]:
    certificate = result.get("certificate")
    require(isinstance(certificate, dict), f"{label}: proven minimum must include a certificate")
    require(certificate.get("schema_version") == 2, f"{label}: optimized certificate schema_version must be 2")
    require(
        certificate.get("algorithm") == "crown_partition_exact_v2",
        f"{label}: unexpected certificate algorithm",
    )
    require(certificate.get("minimum_height") == expected_height, f"{label}: certificate minimum_height is incorrect")
    require(certificate.get("tree") == result["tree"], f"{label}: certificate tree differs from result tree")
    check_query_binding(label, original, certificate.get("query_binding"))
    lower_bounds = certificate.get("lower_bounds")
    require(isinstance(lower_bounds, list), f"{label}: certificate lower_bounds must be an array")
    for index, item in enumerate(lower_bounds):
        require(isinstance(item, dict), f"{label}: lower_bounds[{index}] must be an object")
        occurrences = item.get("occurrences")
        require(
            isinstance(occurrences, list) and all(is_integer(value) and value >= 0 for value in occurrences),
            f"{label}: lower_bounds[{index}].occurrences must be nonnegative integer indices",
        )
        require(
            occurrences == sorted(set(occurrences)),
            f"{label}: lower_bounds[{index}].occurrences must be sorted and unique",
        )
        require(isinstance(item.get("generalized_allowed"), bool), f"{label}: generalized_allowed must be boolean")
        require(isinstance(item.get("connex_reachable"), bool), f"{label}: connex_reachable must be boolean")
        bound = item.get("bound")
        require(bound is None or (is_integer(bound) and bound > 0), f"{label}: lower bound must be positive or null")

    certificate_path = temp / f"{label}.certificate.json"
    certificate_path.write_text(json.dumps(certificate, ensure_ascii=False) + "\n", encoding="utf-8")
    verify_output(
        f"{label} certificate replay",
        invoke(executable, ["verify-height", str(query_path), str(certificate_path)], f"{label} certificate replay"),
        valid=True,
    )
    return certificate


def check_tree_with_independent_validator(
    label: str,
    executable: str,
    query_path: Path,
    tree: dict[str, Any],
    expected_height: int,
    temp: Path,
) -> None:
    tree_path = temp / f"{label}.tree.json"
    tree_path.write_text(json.dumps(tree, ensure_ascii=False) + "\n", encoding="utf-8")
    process = invoke(
        executable,
        ["validate-plan", str(query_path), str(tree_path)],
        f"{label} validate-plan",
    )
    require(
        process.returncode == 0,
        f"{label}: validate-plan rejected oracle tree; stdout={short(process.stdout)!r}; "
        f"stderr={short(process.stderr)!r}",
    )
    validated = parse_stdout(f"{label} validate-plan", process)
    require(validated.get("tree_valid") is True, f"{label}: validate-plan did not mark the tree valid")
    require(
        validated.get("native_height") == expected_height,
        f"{label}: validate-plan native_height expected {expected_height}, got {validated.get('native_height')!r}",
    )


def check_case(executable: str, fixture_dir: Path, temp: Path, case: Any) -> dict[str, Any]:
    require(isinstance(case, dict), "manifest case must be an object")
    name = case.get("name")
    require(isinstance(name, str) and name, "case name must be a nonempty string")
    query_rel = case.get("query")
    require(isinstance(query_rel, str), f"{name}: query path must be a string")
    query_path = (fixture_dir / query_rel).resolve()
    require(query_path.is_file(), f"{name}: query file does not exist: {query_path}")
    original = load_json(query_path)
    require(isinstance(original, dict), f"{name}: query document must be an object")

    expected_status = case.get("height_status")
    expected_height = case.get("minimum_height")
    require(expected_status in {"proven_minimum", "unsupported"}, f"{name}: invalid expected height_status")
    require(
        expected_height is None or is_integer(expected_height),
        f"{name}: minimum_height must be an integer or null",
    )
    require(
        (expected_status == "proven_minimum") == (expected_height is not None),
        f"{name}: status and expected minimum_height disagree",
    )

    process = invoke(executable, ["tree-oracle", str(query_path)], f"{name} tree-oracle")
    expected_exit = 0 if expected_status == "proven_minimum" else 1
    require(
        process.returncode == expected_exit,
        f"{name}: expected tree-oracle exit {expected_exit}, got {process.returncode}; "
        f"stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}",
    )
    result = parse_stdout(f"{name} tree-oracle", process)
    checked_status(name, result)
    require(result["height_status"] == expected_status, f"{name}: wrong height_status")

    if expected_status == "unsupported":
        require(result["tree_valid"] is False, f"{name}: unsupported query cannot have a valid tree")
        require(result["tree"] is None, f"{name}: unsupported query must not return a tree")
        require(result["selected_height"] is None, f"{name}: unsupported query must not select a height")
        require(result["height_lower_bound"] is None, f"{name}: unsupported query must not claim a lower bound")
        require(result["height_upper_bound"] is None, f"{name}: unsupported query must not claim an upper bound")
        require(result["height_search_complete"] is True, f"{name}: empty admissible family requires complete search")
        if result["certificate"] is not None:
            check_certificate(name, query_path, original, result, temp, executable, None)
        return result

    require(result["tree_valid"] is True, f"{name}: proven minimum requires a valid tree")
    require(result["height_search_complete"] is True, f"{name}: proven minimum requires complete height search")
    for field in ("selected_height", "height_lower_bound", "height_upper_bound"):
        require(result[field] == expected_height, f"{name}: {field} expected {expected_height}, got {result[field]!r}")
    tree = result.get("tree")
    require(isinstance(tree, dict), f"{name}: proven minimum requires a version-1 tree object")
    require(tree.get("schema_version") == 1, f"{name}: tree schema_version must be 1")
    check_tree_with_independent_validator(name, executable, query_path, tree, expected_height, temp)
    check_certificate(name, query_path, original, result, temp, executable, expected_height)
    return result


def check_mutated_certificate(
    executable: str,
    fixture_dir: Path,
    temp: Path,
    query_rel: str,
    certificate: dict[str, Any],
    mutation: str,
) -> None:
    query_path = (fixture_dir / query_rel).resolve()
    corrupted = copy.deepcopy(certificate)
    if mutation == "minimum_height":
        require(is_integer(corrupted.get("minimum_height")), "certificate minimum_height must be an integer for corruption test")
        corrupted["minimum_height"] += 1
    elif mutation == "tree_scope":
        tree = corrupted.get("tree")
        require(isinstance(tree, dict), "certificate tree must be an object for scope corruption test")
        target = next(
            (
                node
                for node in tree.get("nodes", [])
                if node.get("kind") == "native" and isinstance(node.get("scope"), list) and node["scope"]
            ),
            None,
        )
        require(target is not None, "chosen certificate has no nonempty native scope to corrupt")
        target["scope"].pop()
    elif mutation == "tree_height":
        tree = corrupted.get("tree")
        require(isinstance(tree, dict), "certificate tree must be an object for height corruption test")
        height = corrupted.get("minimum_height")
        require(is_integer(height), "certificate minimum_height must be an integer for tree-height corruption")
        tree["native_height"] = height + 1
    else:
        raise RuntimeError(f"unknown certificate mutation {mutation}")

    certificate_path = temp / f"corrupt-{mutation}.certificate.json"
    certificate_path.write_text(json.dumps(corrupted, ensure_ascii=False) + "\n", encoding="utf-8")
    verify_output(
        f"corrupted {mutation} certificate",
        invoke(
            executable,
            ["verify-height", str(query_path), str(certificate_path)],
            f"corrupted {mutation} certificate",
        ),
        valid=False,
    )


def check_zero_work(executable: str, fixture_dir: Path, temp: Path) -> None:
    query_path = (fixture_dir / "../plans/queries/empty_body.cq.json").resolve()
    process = invoke(
        executable,
        ["tree-oracle", str(query_path), "0"],
        "zero-work tree-oracle",
    )
    require(
        process.returncode == 1,
        f"zero-work tree-oracle: expected exit 1, got {process.returncode}; "
        f"stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}",
    )
    result = parse_stdout("zero-work tree-oracle", process)
    checked_status("zero-work tree-oracle", result)
    require(result["height_status"] == "resource_limit", "zero-work search must report resource_limit")
    require(result["height_search_complete"] is False, "zero-work search must report incomplete height search")
    require(result["height_status"] not in {"unsupported", "proven_minimum"}, "zero work cannot prove feasibility or infeasibility")
    require(result["selected_height"] is None, "zero-work search must not select a height")
    require(result["tree"] is None, "zero-work search must not return a tree")
    require(result["certificate"] is None, "zero-work search must not return a certificate")


def check_malformed_usage(executable: str) -> None:
    process = invoke(executable, ["tree-oracle"], "malformed tree-oracle usage")
    require(
        process.returncode == 2,
        f"malformed tree-oracle usage: expected exit 2, got {process.returncode}; "
        f"stdout={short(process.stdout)!r}; stderr={short(process.stderr)!r}",
    )


def check_same_body_head_changes(fixture_dir: Path, cases: list[Any]) -> None:
    selected = {case["name"]: case for case in cases if case.get("name") in {
        "disconnected_full", "disconnected_proper", "disconnected_boolean"
    }}
    require(len(selected) == 3, "manifest must include full, proper, and Boolean disconnected head cases")
    documents = {
        name: load_json((fixture_dir / case["query"]).resolve())
        for name, case in selected.items()
    }
    first = documents["disconnected_full"]
    body = (catalog_signature(first["catalog"]), first["query"]["variables"], atom_signature(first["query"]))
    for name, document in documents.items():
        require(
            (catalog_signature(document["catalog"]), document["query"]["variables"], atom_signature(document["query"])) == body,
            f"{name}: head-variation fixture changed the disconnected body",
        )


def main() -> int:
    if len(sys.argv) not in (2, 3):
        raise RuntimeError("usage: tree_oracle.py EXECUTABLE [FIXTURE_DIRECTORY]")
    executable = sys.argv[1]
    fixture_dir = Path(sys.argv[2]).resolve() if len(sys.argv) == 3 else DEFAULT_FIXTURES
    manifest_path = fixture_dir / "manifest.json"
    manifest = load_json(manifest_path)
    require(isinstance(manifest, dict), f"{manifest_path}: manifest must be an object")
    require(
        is_integer(manifest.get("schema_version")) and manifest["schema_version"] == 1,
        f"{manifest_path}: schema_version must be integer 1",
    )
    cases = manifest.get("cases")
    require(isinstance(cases, list) and bool(cases), f"{manifest_path}: cases must be a nonempty array")
    check_same_body_head_changes(fixture_dir, cases)

    results: dict[str, dict[str, Any]] = {}
    with tempfile.TemporaryDirectory(prefix="crown-tree-oracle-") as temporary:
        temp = Path(temporary)
        for case in cases:
            result = check_case(executable, fixture_dir, temp, case)
            results[case["name"]] = result

        # Query aliases and variable/atom permutations preserve the analytic optimum.
        invariants = (
            ("full_two_edge_generalized_root", "full_two_edge_renamed_permuted"),
            ("residual_counterexample_7", "residual_7_renamed_permuted"),
        )
        for first, second in invariants:
            require(first in results and second in results, f"manifest is missing invariance pair {first}/{second}")
            require(
                results[first]["selected_height"] == results[second]["selected_height"],
                f"renaming/permutation changed minimum height for {first}/{second}",
            )

        min_case = next(case for case in cases if case.get("name") == "full_two_edge_generalized_root")
        min_certificate = results[min_case["name"]]["certificate"]
        check_mutated_certificate(
            executable, fixture_dir, temp, min_case["query"], min_certificate, "minimum_height"
        )
        check_mutated_certificate(
            executable, fixture_dir, temp, min_case["query"], min_certificate, "tree_scope"
        )
        check_mutated_certificate(
            executable, fixture_dir, temp, min_case["query"], min_certificate, "tree_height"
        )
        check_zero_work(executable, fixture_dir, temp)
        check_malformed_usage(executable)

    print(f"{len(cases)} structural oracle fixtures, certificate replays, corruption checks, and CLI boundary checks passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"tree-oracle fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
