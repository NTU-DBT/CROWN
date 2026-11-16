#!/usr/bin/env python3
"""Optional jsonschema check of actual frontend and identity CLI artifacts.

This audit and the registered report-schema tests require installed jsonschema
with Draft 2020-12 support; see docs/native_build.md for build requirements.
"""
from __future__ import annotations

import json
import hashlib
import subprocess
import sys
import tempfile
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    from jsonschema import Draft202012Validator, RefResolver

    require(len(sys.argv) == 2, "usage: verify_schemas.py EXECUTABLE")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(__file__).resolve().parent.parent
    schemas = {path.name: json.loads(path.read_text()) for path in (root / "schemas").glob("*.schema.json")}
    store = {(root / "schemas" / name).as_uri(): value for name, value in schemas.items()}
    for value in schemas.values():
        Draft202012Validator.check_schema(value)
        if "$id" in value:
            store[value["$id"]] = value
    # The local store covers current references; no explicit deny-network handlers are set.
    validators = {
        name: Draft202012Validator(value, resolver=RefResolver(
            base_uri=(root / "schemas" / name).as_uri(), referrer=value, store=store,
        )) for name, value in schemas.items()
    }

    def invoke(arguments: list[str], code: int = 0) -> dict:
        result = subprocess.run([executable, *arguments], capture_output=True, text=True, timeout=30)
        require(result.returncode == code and not result.stderr, f"CLI rejected {arguments[0]}: {result.stderr}")
        return json.loads(result.stdout)

    base = root / "tests/frontend/normalization"
    manifest = json.loads((base / "manifest.json").read_text())
    programs = identities = physicals = certificates = 0
    legacy_certificate_checked = False
    with tempfile.TemporaryDirectory(prefix="crown-schema-validation-") as directory:
        path = Path(directory) / "program.json"
        for case in manifest["success_cases"] + manifest["failure_cases"]:
            arguments = ["normalize-sql", str(base / case["sql"]), str(base / manifest["catalog"])]
            if "parameter_types" in case:
                arguments.append(str(base / case["parameter_types"]))
            if "parameter_values" in case:
                arguments.append(str(base / case["parameter_values"]))
            program = invoke(arguments, 1 if "code" in case else 0)
            validators[f"sql-normalization-v{program['schema_version']}.schema.json"].validate(program)
            programs += 1
            if not program["normalization_valid"]:
                continue
            path.write_text(json.dumps(program, ensure_ascii=False), encoding="utf-8")
            identity = invoke(["fingerprint-normalized", str(path)])
            validators["query-identity-v1.schema.json"].validate(identity)
            identities += 1
            core_path, tree_path = Path(directory) / "core.json", Path(directory) / "tree.json"
            core_path.write_text(json.dumps(program["core"], ensure_ascii=False), encoding="utf-8")
            if program["core"]["query"].get("contradiction", False):
                tree = {"schema_version": 1, "catalog_version": 1, "semantics": "set", "root": None, "nodes": []}
            else:
                optimum = invoke(["tree-oracle", str(core_path)])
                proof = optimum["certificate"]
                validators[f"height-certificate-v{proof['schema_version']}.schema.json"].validate(proof)
                certificates += 1
                if not legacy_certificate_checked and proof["minimum_height"] == 1:
                    # This independently valid v1 universal-bound proof keeps
                    # the old reader/schema/replay exercised, not merely parsed.
                    legacy = json.loads(json.dumps(proof))
                    legacy["schema_version"] = 1
                    legacy["algorithm"] = "crown_partition_exact_v1"
                    legacy["lower_bounds"] = [{"occurrences": list(range(len(program["core"]["query"]["atoms"]))),
                                               "generalized_allowed": True, "connex_reachable": True, "bound": 1}]
                    validators["height-certificate-v1.schema.json"].validate(legacy)
                    legacy_path = Path(directory) / "legacy-height.json"
                    legacy_path.write_text(json.dumps(legacy), encoding="utf-8")
                    require(invoke(["verify-height", str(core_path), str(legacy_path)])["certificate_valid"],
                            "legacy v1 height proof no longer replays")
                    legacy_certificate_checked = True
                    certificates += 1
                tree = optimum["tree"]
            tree_path.write_text(json.dumps(tree), encoding="utf-8")
            physical = invoke(["lower-normalized", str(path), str(tree_path)])
            validators["physical-plan-v1.schema.json"].validate(physical)
            validators["physical-plan-options-v1.schema.json"].validate(physical["options"])
            physicals += 1
        stopped = invoke(["fingerprint-normalized", str(path), "0"], 1)
        validators["query-identity-v1.schema.json"].validate(stopped)
        identity = invoke(["fingerprint-cq", str(root / "tests/regression/projection_collision.json")])
        validators["query-identity-v1.schema.json"].validate(identity)
        identities += 2
    for name in ("normalized-v1.json", "normalized-v1-fixed-head.json"):
        frozen = json.loads((root / "tests/frontend/schema" / name).read_text())
        validators["sql-normalization-v1.schema.json"].validate(frozen)
        programs += 1
    admission_base = root / "tests/frontend/admission"
    matrix = json.loads((admission_base / "manifest.json").read_text())
    admissions = 0
    for case in matrix["cases"]:
        arguments = ["admit-sql", str(admission_base / case["sql"]), str(admission_base / matrix["catalog"])]
        if "options" in case:
            options_path = admission_base / case["options"]
            option_schema = {"$ref": (root / "schemas/sql-admission-v1.schema.json").as_uri() + "#/$defs/options_document"}
            Draft202012Validator(option_schema, resolver=validators["sql-admission-v1.schema.json"].resolver).validate(json.loads(options_path.read_text()))
            arguments.append(str(options_path))
        report = invoke(arguments, 0 if case["status"] == "admitted" else 1)
        validators["sql-admission-v1.schema.json"].validate(report)
        admissions += 1
    layout_test = str(Path(executable).parent / "crown_layout_test")
    layout_output = subprocess.run([layout_test, "--artifacts"], check=True, capture_output=True, text=True, timeout=30)
    layouts = json.loads(layout_output.stdout)
    validators["tuple-layout-v1.schema.json"].validate(layouts["layout"])
    validators["key-projection-v1.schema.json"].validate(layouts["projection"])
    physical_cases = json.loads((root / "tests/structural/lowering/manifest.json").read_text())
    for case in physical_cases["cases"]:
        if case["expected"]["valid"]:
            physical = invoke(["lower-plan", str(root / case["query"]), str(root / case["tree"])])
            validators["physical-plan-v1.schema.json"].validate(physical)
            validators["physical-plan-options-v1.schema.json"].validate(physical["options"])
            physicals += 1
    support_base = root / "tests/runtime/support"
    support_cases = json.loads((support_base / "manifest.json").read_text())
    support_report_validator = Draft202012Validator({"$ref": (root / "schemas/support-report-v2.schema.json").as_uri() + "#/$defs/report"},
                                                   resolver=validators["support-report-v2.schema.json"].resolver)
    supports = rejected_supports = 0
    with tempfile.TemporaryDirectory(prefix="crown-support-schema-") as directory:
        plan_path, trace_path = Path(directory) / "plan.json", Path(directory) / "trace.json"
        for case in support_cases["cases"]:
            plan = invoke(["lower-plan", str(root / case["query"]), str(root / case["tree"])])
            plan_path.write_text(json.dumps(plan), encoding="utf-8")
            trace = {"schema_version": 1, "options": {"capture_transitions": True},
                     "updates": [{name: value for name, value in event.items() if name != "expected"} for event in case["events"]]}
            validators["support-trace-v1.schema.json"].validate(trace)
            trace_path.write_text(json.dumps(trace), encoding="utf-8")
            support_report_validator.validate(invoke(["support-trace", str(plan_path), str(trace_path)]))
            supports += 1
            if supports == 1:
                for cap in ({"support_limit": 1}, {"work_limit": 0}):
                    limited = dict(trace, options=dict(trace["options"], **cap))
                    validators["support-trace-v1.schema.json"].validate(limited)
                    trace_path.write_text(json.dumps(limited), encoding="utf-8")
                    support_report_validator.validate(invoke(["support-trace", str(plan_path), str(trace_path)], 1))
                    rejected_supports += 1
    input_events = 0
    with tempfile.TemporaryDirectory(prefix="crown-input-schema-") as directory:
        catalog_path, input_path = Path(directory) / "catalog.json", Path(directory) / "events.jsonl"
        catalog = {"schema_version": 1, "catalog": {"version": 71, "tables": [{
            "name": "R", "source_schema_version": 5,
            "columns": [{"name": name, "type": kind} for name, kind in
                        [("id", "int64"), ("text", "string"), ("enabled", "bool"),
                         ("day", "date"), ("amount", "decimal")]]}]}}
        catalog_path.write_text(json.dumps(catalog), encoding="utf-8")
        canonical = invoke(["canonicalize-catalog", str(catalog_path)])
        fingerprint = hashlib.sha256(json.dumps(canonical, sort_keys=True, ensure_ascii=False,
                                                separators=(",", ":")).encode("utf-8")).hexdigest()
        events = []
        for sequence, operation in [(1, "insert"), (2, "delete")]:
            event = {"schema_version": 1, "catalog_version": 71, "source_schema_version": 5,
                     "catalog_sha256": fingerprint, "sequence": sequence, "table": "R",
                     "operation": operation, "values": [-(2**63), "雪\0text", True,
                     {"date": "2024-02-29"}, {"decimal": "1.25"}],
                     "source_position": {"source": "file", "offset": sequence - 1}}
            validators["physical-update-v1.schema.json"].validate(event)
            events.append(event)
            input_events += 1
        input_path.write_text("".join(json.dumps(event, ensure_ascii=False) + "\n" for event in events), encoding="utf-8")
        report = invoke(["validate-input", str(catalog_path), "jsonl", str(input_path)])
        require(report["input_valid"] and report["sequence"] == 2 and report["records"] == 2,
                "native physical input validation disagreed with schema-valid events")
    diagnostics = 0
    inspection_test = str(Path(executable).parent / "crown_runtime_inspection_test")
    for argument in ["--dump-physical", "--dump-delta", "--dump-report"]:
        result = subprocess.run([inspection_test, argument], check=True, capture_output=True, text=True, timeout=30)
        require(not result.stderr, f"runtime diagnostic emitter rejected {argument}: {result.stderr}")
        artifact = json.loads(result.stdout)
        validators["runtime-diagnostic-v1.schema.json"].validate(artifact)
        if argument == "--dump-report":
            require(artifact["complete"] and not artifact["valid"] and artifact["issues"],
                    "inspection diagnostic failed to retain the actual counter-corruption issue")
        diagnostics += 1
    require(legacy_certificate_checked, "schema corpus did not exercise a valid v1 height proof")
    print(f"{len(schemas)} schema meta-checks, {programs} normalized artifacts, {identities} identity artifacts, {certificates} height certificates, {admissions} admission artifacts, 2 layout/projection artifacts, {physicals} physical artifacts, {supports} support traces/reports, {rejected_supports} rejected-update reports, {input_events} physical input events and {diagnostics} runtime diagnostics PASS")


if __name__ == "__main__":
    try:
        main()
    except (ImportError, RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as error:
        print(f"schema audit failed: {error}", file=sys.stderr)
        raise SystemExit(1)
