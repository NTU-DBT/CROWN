#!/usr/bin/env python3
"""Physical lowering CLI/replay checks; standard library only."""
from __future__ import annotations

import copy
import hashlib
import json
import subprocess
import sys
import tempfile
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def canonical(value: object) -> bytes:
    return json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False).encode()


def main() -> None:
    require(len(sys.argv) == 3, "usage: physical.py EXECUTABLE REPOSITORY")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(sys.argv[2]).resolve()
    checks = 0

    def invoke(arguments: list[str], code: int = 0, stderr_code: str | None = None) -> dict:
        nonlocal checks
        result = subprocess.run([executable, *arguments], capture_output=True, text=True, timeout=60)
        require(result.returncode == code, f"{arguments[0]} exit {result.returncode}: {result.stderr} {result.stdout[:300]}")
        if stderr_code:
            require(not result.stdout and json.loads(result.stderr)["error"]["code"] == stderr_code,
                    f"wrong rejection for {arguments[0]}: {result.stderr}")
            checks += 1
            return json.loads(result.stderr)
        require(not result.stderr, f"unexpected stderr: {result.stderr}")
        checks += 1
        return json.loads(result.stdout)

    def verify_binding(artifact: dict) -> None:
        identity = artifact["binding"]["identity"]
        envelope = {"domain": "crown-physical-plan", "version": 1, "lowerer": "crown-lower-v1",
                    "source_sha256": hashlib.sha256(canonical(artifact["source"])).hexdigest(),
                    "plan_cache_sha256": identity["plan_cache_sha256"],
                    "occurrence_order": identity["occurrence_order"], "variable_order": identity["variable_order"],
                    "tree": artifact["tree"]}
        digest = hashlib.sha256(canonical(envelope)).hexdigest()
        require(artifact["binding"]["physical_sha256"] == digest, "independent physical SHA-256 mismatch")
        require(all(layout["context"]["binding"] == digest for layout in artifact["layouts"]),
                "layout context was not bound to the actual physical instructions")
        profile = artifact["guarantee"]
        require(profile["execution_status"] == "lowered_not_started" and profile["height_status"] == "valid_upper_bound",
                "lowering claimed execution or an unproved optimum")
        for field in ("state_bound", "maintenance_bound", "cursor_startup_bound", "cursor_delay_bound", "cursor_termination_bound"):
            require(profile[field] == "runtime_not_implemented", "lowering claimed an unimplemented runtime bound")

    matrix = json.loads((root / "tests/structural/lowering/manifest.json").read_text())
    with tempfile.TemporaryDirectory(prefix="crown-physical-cli-") as directory:
        temporary = Path(directory)
        artifact_path = temporary / "physical.json"
        options_path = temporary / "options.json"
        first = None
        first_case = None
        for case in matrix["cases"]:
            arguments = ["lower-plan", str(root / case["query"]), str(root / case["tree"])]
            if not case["expected"]["valid"]:
                failed = invoke(arguments, 1)
                require(failed["status"] == "invalid_plan" and not failed["physical_lowered"] and "layouts" not in failed,
                        "invalid tree published a partial physical program")
                continue
            artifact = invoke(arguments)
            require(artifact["route"] == case["expected"]["route"], "route differs from manual fixture")
            verify_binding(artifact)
            artifact_path.write_text(json.dumps(artifact, ensure_ascii=False))
            valid = invoke(["validate-physical", str(artifact_path)])
            require(valid["physical_valid"] and valid["physical_sha256"] == artifact["binding"]["physical_sha256"], "replay identity changed")
            require(invoke(["canonicalize-physical", str(artifact_path)]) == artifact, "complete physical round trip changed")
            if first is None:
                first, first_case = artifact, case
        require(first is not None and first_case is not None, "no valid physical fixtures")

        for location, replacement in ((["binding", "physical_sha256"], "0" * 64),
                                      (["guarantee", "state_bound"], "O(1)"),
                                      (["verification", "valid"], False),
                                      (["enumeration", "result_layout"], 999999),
                                      (["work"], first["work"] + 1)):
            corrupt = copy.deepcopy(first)
            parent = corrupt
            for field in location[:-1]:
                parent = parent[field]
            parent[location[-1]] = replacement
            artifact_path.write_text(json.dumps(corrupt))
            invoke(["validate-physical", str(artifact_path)], 2, "physical_binding")
        corrupt = copy.deepcopy(first)
        corrupt["schema_version"] = 2
        artifact_path.write_text(json.dumps(corrupt))
        invoke(["validate-physical", str(artifact_path)], 2, "unsupported_version")
        artifact_path.write_text('{"schema_version":1,"schema_version":1}')
        invoke(["validate-physical", str(artifact_path)], 2, "invalid_document")

        options = copy.deepcopy(first["options"])
        options["limits"]["work"] = 0
        options_path.write_text(json.dumps(options))
        failed = invoke(["lower-plan", str(root / first_case["query"]), str(root / first_case["tree"]), str(options_path)], 1)
        require(failed["status"] == "resource_limit" and "binding" not in failed, "work stop published a digest/program")
        options = copy.deepcopy(first["options"])
        options["limits"]["identity_work"] = 0
        options_path.write_text(json.dumps(options))
        require(invoke(["lower-plan", str(root / first_case["query"]), str(root / first_case["tree"]), str(options_path)], 1)["status"] == "resource_limit",
                "identity budget was bypassed")
        options["policy"]["arithmetic"] = "floating"
        options_path.write_text(json.dumps(options))
        invoke(["lower-plan", str(root / first_case["query"]), str(root / first_case["tree"]), str(options_path)], 2, "invalid_policy")

        # Initial physical data and update events are outside a compilation
        # binding. The same query/tree lowers to the same empty source artifact.
        query_path = temporary / "data-changed.json"
        query = copy.deepcopy(first["source"]["document"])
        query["initial"][0]["rows"] = [["data-only"]]
        query_path.write_text(json.dumps(query))
        require(invoke(["lower-plan", str(query_path), str(root / first_case["tree"])]) == first,
                "physical data changed a query compilation identity")

        normalization_base = root / "tests/frontend/normalization"
        normalization = json.loads((normalization_base / "manifest.json").read_text())
        normalized_count = 0
        for case in normalization["success_cases"]:
            arguments = ["normalize-sql", str(normalization_base / case["sql"]), str(normalization_base / normalization["catalog"])]
            if "parameter_types" in case:
                arguments.append(str(normalization_base / case["parameter_types"]))
            if "parameter_values" in case:
                arguments.append(str(normalization_base / case["parameter_values"]))
            program = invoke(arguments)
            program_path, core_path, tree_path = (temporary / name for name in ("program.json", "core.json", "tree.json"))
            program_path.write_text(json.dumps(program, ensure_ascii=False))
            core_path.write_text(json.dumps(program["core"], ensure_ascii=False))
            if program["core"]["query"].get("contradiction", False):
                tree = {"schema_version": 1, "catalog_version": 1, "semantics": "set", "root": None, "nodes": []}
            else:
                # The exact constructor supplies a candidate; manual structural
                # expectations and independent execution are tested separately.
                oracle = invoke(["tree-oracle", str(core_path)])
                tree = oracle["tree"]
            tree_path.write_text(json.dumps(tree))
            artifact = invoke(["lower-normalized", str(program_path), str(tree_path)])
            require(artifact["source"]["kind"] == "normalized_sql" and artifact["source"]["program"]["schema_version"] == 2,
                    "normalized physical source was not grounded/owned")
            verify_binding(artifact)
            artifact_path.write_text(json.dumps(artifact, ensure_ascii=False))
            require(invoke(["canonicalize-physical", str(artifact_path)]) == artifact, "normalized physical replay changed typed adapters")
            normalized_count += 1
    print(f"{checks} physical CLI checks, 14 manual valid families, 5 invalid trees and {normalized_count} normalized programs PASS")


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, ValueError, OSError, KeyError, subprocess.TimeoutExpired) as error:
        print(f"physical integration failed: {error}", file=sys.stderr)
        raise SystemExit(1)
