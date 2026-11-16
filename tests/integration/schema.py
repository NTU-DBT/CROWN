#!/usr/bin/env python3
"""Independent SHA-256, CLI replay/migration and canonical-equivalence checks."""
from __future__ import annotations

import copy
import hashlib
import itertools
import json
import random
import subprocess
import sys
import tempfile
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def canonical(value: object) -> str:
    return json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":"))


def digest(domain: str, value: object) -> str:
    payload = {"domain": domain, "version": 1, "value": value}
    return hashlib.sha256(canonical(payload).encode("utf-8")).hexdigest()


def main() -> None:
    require(len(sys.argv) == 3, "usage: schema.py EXECUTABLE SOURCE_ROOT")
    executable, root = sys.argv[1], Path(sys.argv[2]).resolve()
    checks = 0

    def invoke(arguments: list[str], code: int = 0) -> dict:
        nonlocal checks
        process = subprocess.run([executable, *arguments], capture_output=True, text=True, timeout=30)
        require(process.returncode == code, f"{arguments[0]} exit {process.returncode}, expected {code}: {process.stderr}")
        require(not (process.stderr if code in (0, 1) else process.stdout), f"{arguments[0]} used the wrong output channel")
        result = json.loads(process.stdout if code in (0, 1) else process.stderr)
        require(isinstance(result, dict), "CLI result must be an object")
        checks += 1
        return result

    def verify_identity(identity: dict, program: dict | None = None) -> None:
        require(identity["identity_valid"] is True and identity["status"] == "complete", "missing complete identity")
        require(identity["semantic_sha256"] == digest("crown.query.semantic", identity["canonical"]), "native SHA-256 differs from hashlib")
        if program is not None:
            contract = [{"name": item["name"], "type": item["type"]} for item in program["outputs"]]
            if program["binding"]["result_wrapper"] == "exists":
                contract = [{"name": program["binding"]["wrapper_alias"], "type": {"kind": "bool", "nullable": False}}]
            require(identity["output_contract_sha256"] == digest("crown.query.output", contract), "output contract digest differs from hashlib")
            require(identity["cost_inputs_sha256"] == digest("crown.query.cost-inputs", program["binding"]["catalog_binding"]["catalog"]), "catalog/cost digest differs from hashlib")
        cache = {
            "semantic": identity["semantic_sha256"], "output": identity["output_contract_sha256"],
            "cost_inputs": identity["cost_inputs_sha256"], "arithmetic": "exact-nonnull-v1",
            "planner": "crown-tree-v1", "optimization": "structural-height-v1", "cost_model": "no-cost-v1",
        }
        require(identity["plan_cache_sha256"] == digest("crown.plan.cache", cache), "cache digest differs from hashlib")
        atom_count = len(identity["canonical"]["atoms"])
        variable_count = len(identity["canonical"]["variables"])
        require(sorted(identity["occurrence_order"]) == list(range(atom_count)), "occurrence translation is not a permutation")
        require(sorted(identity["variable_order"]) == list(range(variable_count)), "variable translation is not a permutation")
        for table in identity["canonical"]["catalog"]["tables"]:
            require("statistics" not in table and "key_hints" not in table, "semantic payload contains cost-only inputs")

    base = root / "tests/frontend/normalization"
    manifest = json.loads((base / "manifest.json").read_text())
    with tempfile.TemporaryDirectory(prefix="crown-schema-") as directory:
        temporary = Path(directory)
        artifact = temporary / "program.json"
        first = None
        for case in manifest["success_cases"]:
            arguments = ["normalize-sql", str(base / case["sql"]), str(base / manifest["catalog"])]
            if "parameter_types" in case:
                arguments.append(str(base / case["parameter_types"]))
            if "parameter_values" in case:
                arguments.append(str(base / case["parameter_values"]))
            program = invoke(arguments)
            artifact.write_text(json.dumps(program, ensure_ascii=False), encoding="utf-8")
            require(invoke(["validate-normalized", str(artifact)])["admission_status"] == "not_checked", "reader granted admission")
            require(canonical(invoke(["canonicalize-normalized", str(artifact)])) == canonical(program), "full typed program did not round-trip")
            verify_identity(invoke(["fingerprint-normalized", str(artifact)]), program)
            if first is None:
                first = program

        require(first is not None, "empty normalization corpus")
        frozen_path = root / "tests/frontend/schema/normalized-v1.json"
        frozen = json.loads(frozen_path.read_text(encoding="utf-8"))
        require(invoke(["validate-normalized", str(frozen_path)])["program_valid"] is True, "frozen v1 program rejected")
        require(canonical(invoke(["canonicalize-normalized", str(frozen_path)])) == canonical(frozen), "frozen v1 program changed on replay")
        mutations = [
            (lambda p: p.update(unknown_mandatory=1), "invalid_document"),
            (lambda p: p.update(schema_version=999), "unsupported_version"),
            (lambda p: p["binding"].update(schema_version=2), "unsupported_version"),
            (lambda p: p["adapters"][0].update(program=[999999]), "invalid_document"),
            (lambda p: p["adapters"][0].update(extra=True), "invalid_document"),
            (lambda p: p["base_routes"].__setitem__(0, []), "invalid_document"),
            (lambda p: p["core"]["query"].update(contradiction=True), "invalid_document"),
            (lambda p: p["outputs"][0].update(column=999999), "invalid_document"),
            (lambda p: p.update(work=float(p["work"])), "invalid_document"),
        ]
        for mutate, expected in mutations:
            changed = copy.deepcopy(first)
            mutate(changed)
            artifact.write_text(json.dumps(changed), encoding="utf-8")
            require(invoke(["validate-normalized", str(artifact)], 2)["error"]["code"] == expected, "tampered program accepted or misdiagnosed")
        artifact.write_text('{"schema_version":1,"schema_version":1}', encoding="utf-8")
        require(invoke(["validate-normalized", str(artifact)], 2)["error"]["code"] == "invalid_document", "duplicate JSON keys accepted")

        # Raw UTF-8 is part of the specified deterministic byte encoding.
        sql = temporary / "unicode.sql"
        sql.write_text("SELECT DISTINCT '雪' AS 标签", encoding="utf-8")
        catalog = temporary / "catalog.json"
        catalog.write_text('{"schema_version":1,"catalog":{"version":1,"tables":[]}}', encoding="utf-8")
        unicode_program = invoke(["normalize-sql", str(sql), str(catalog)])
        artifact.write_text(json.dumps(unicode_program, ensure_ascii=False), encoding="utf-8")
        verify_identity(invoke(["fingerprint-normalized", str(artifact)]), unicode_program)
        stopped = invoke(["fingerprint-normalized", str(artifact), "0"], 1)
        require(stopped["identity_valid"] is False and stopped["status"] == "resource_limit", "zero work did not stop identity")
        require(not any("sha256" in key for key in stopped), "partial identity leaked after exhaustion")

        source = root / "tests/regression/projection_collision.json"
        before = invoke(["oracle", str(source)])
        for version in (1, 2, 3):
            upgraded = invoke(["upgrade-cq", str(source), str(version)])
            require(upgraded["schema_version"] == version, "wrong explicit upgrade target")
            upgraded_path = temporary / "upgraded.json"
            upgraded_path.write_text(json.dumps(upgraded), encoding="utf-8")
            after = invoke(["oracle", str(upgraded_path)])
            require(before["initial"] == after["initial"] and before["epochs"] == after["epochs"], "CQ migration changed physical-event semantics")
        require(invoke(["upgrade-cq", str(upgraded_path), "2"], 2)["error"]["code"] == "unsupported_version", "downgrade accepted")
        require(invoke(["upgrade-cq", str(source), "4"], 2)["error"]["code"] == "unsupported_version", "future CQ version accepted")

        # All 24 occurrence permutations, each with independent variable/alias
        # renaming, of a same-table four-cycle. The test constructs the equivalent
        # CQs; the CROWN oracle CLI supplies baseline physical result rows.
        cq = {
            "schema_version": 1, "semantics": "set",
            "catalog": {"version": 1, "tables": [{"name": "r", "columns": [{"name": "x", "type": "int64"}, {"name": "y", "type": "int64"}]}]},
            "query": {
                "variables": [{"name": f"v{i}", "type": "int64"} for i in range(4)],
                "atoms": [{"id": f"a{i}", "table": "r", "terms": [{"var": f"v{i}"}, {"var": f"v{(i+1)%4}"}]} for i in range(4)],
                "head": [{"var": "v0", "alias": "first"}, {"var": "v2", "alias": "opposite"}, {"var": "v0", "alias": "again"}],
            },
            "initial": [{"table": "r", "rows": [[0, 0], [0, 1], [1, 0], [1, 1], [2, 2]]}], "updates": [],
        }
        path = temporary / "query.json"
        path.write_text(json.dumps(cq), encoding="utf-8")
        identity = invoke(["fingerprint-cq", str(path)])
        verify_identity(identity)
        expected_rows = invoke(["oracle", str(path)])["initial"]
        randomizer = random.Random(417)
        for permutation in itertools.permutations(range(4)):
            renamed = copy.deepcopy(cq)
            shuffled_names = randomizer.sample(range(4), 4)
            names = {f"v{i}": f"renamed{shuffled_names[i]}" for i in range(4)}
            randomizer.shuffle(renamed["query"]["variables"])
            for variable in renamed["query"]["variables"]:
                variable["name"] = names[variable["name"]]
            renamed["query"]["atoms"] = [renamed["query"]["atoms"][i] for i in permutation]
            for index, atom in enumerate(renamed["query"]["atoms"]):
                atom["id"] = f"alias{index}"
                for term in atom["terms"]:
                    term["var"] = names[term["var"]]
            for output in renamed["query"]["head"]:
                output["var"] = names[output["var"]]
            path.write_text(json.dumps(renamed), encoding="utf-8")
            actual = invoke(["fingerprint-cq", str(path)])
            verify_identity(actual)
            require(actual["canonical"] == identity["canonical"] and actual["plan_cache_sha256"] == identity["plan_cache_sha256"], "canonical identity depends on aliases/order")
            require(invoke(["oracle", str(path)])["initial"] == expected_rows, "independent equivalent-query generator changed semantics")

        empty = {"schema_version": 1, "semantics": "set", "catalog": {"version": 1, "tables": []}, "query": {"variables": [], "atoms": [], "head": []}}
        path.write_text(json.dumps(empty), encoding="utf-8")
        golden = invoke(["fingerprint-cq", str(path)])
        require(golden["canonical"] == {"identity_version": 1, "catalog": {"version": 1, "tables": []}, "semantics": {"profile": "direct-cq-v1", "rows": "set", "arithmetic": "exact-nonnull-v1"}, "variables": [], "atoms": [], "head": [], "contradiction": False}, "empty canonical identity differs from the manual specification")
        verify_identity(golden)
    print(f"{checks} schema/identity CLI checks passed; 17 program round trips, 24 renamed occurrence permutations, independent hashlib and migration semantics")


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as error:
        print(f"schema fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
