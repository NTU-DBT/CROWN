#!/usr/bin/env python3
"""Validate actual immutable P05 reports with local schemas and mutations."""
from __future__ import annotations

import copy
import json
import subprocess
import sys
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    from jsonschema import Draft202012Validator, RefResolver
    from jsonschema.exceptions import ValidationError

    require(len(sys.argv) == 3,
            "usage: verify_residual_reports.py FIXTURE_EXECUTABLE REPOSITORY_ROOT")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(sys.argv[2]).resolve()
    schema_dir = root / "schemas"
    schemas = {p.name: json.loads(p.read_text(encoding="utf-8"))
               for p in schema_dir.glob("*.schema.json")}
    store = {}
    for name, schema in schemas.items():
        store[(schema_dir / name).as_uri()] = schema
        if "$id" in schema:
            store[schema["$id"]] = schema

    def local_file(uri: str) -> dict:
        require(uri in store, f"schema reference is outside the local set: {uri}")
        return store[uri]

    def deny_network(uri: str) -> dict:
        raise RuntimeError(f"schema resolver attempted network access: {uri}")

    validators = {}
    for name, schema in schemas.items():
        Draft202012Validator.check_schema(schema)
        resolver = RefResolver(base_uri=(schema_dir / name).as_uri(), referrer=schema,
                               store=store, handlers={"file": local_file,
                               "http": deny_network, "https": deny_network})
        validators[name] = Draft202012Validator(schema, resolver=resolver)

    emitted = subprocess.run([executable, "--emit"], capture_output=True, text=True,
                             timeout=180, check=False)
    require(emitted.returncode == 0 and not emitted.stderr,
            f"native report fixtures failed: {emitted.stderr.strip()}")
    records = json.loads(emitted.stdout)
    require(isinstance(records, list) and records, "no native report artifacts")
    by_name = {}
    versions = set()
    for record in records:
        require(isinstance(record, dict) and set(record) == {"name", "schema", "document"},
                "artifact record must contain exactly name, schema and document")
        name, schema_name, document = record["name"], record["schema"], record["document"]
        require(isinstance(name, str) and name not in by_name, "duplicate artifact name")
        require(schema_name in validators, f"no local schema for {schema_name}")
        validators[schema_name].validate(document)
        by_name[name] = document
        versions.add(document.get("query_binding", {}).get("schema_version"))
    expected = {"residual_trace", "admitted", "candidate_upper", "candidate_progress",
                "exact_original_pending", "exact_original_progress", "verified_optimum",
                "metadata_v3_progress", "candidate_after_exact", "exact_infeasible_progress",
                "verified_infeasible", "cancelled"}
    require(expected <= by_name.keys(), f"missing artifacts: {expected - by_name.keys()}")
    require({1, 2, 3} <= versions, "reports did not cover all three query binding formats")

    trace = by_name["residual_trace"]
    require(trace["audit_scope"] == "frozen_residual_trace_only" and
            "minimum_height" not in trace and "certificate" not in trace,
            "trace claimed height or exactness authority")
    for name in ("candidate_upper", "candidate_after_exact"):
        upper = by_name[name]
        require(upper["proof_status"] == "checked_upper_only" and
                upper["height_status"] == "valid_upper_bound" and
                upper["certificate"] is None and "minimum_height" not in upper,
                f"standalone upper report {name} claimed a minimum")
    for name in ("admitted", "exact_original_pending", "candidate_progress", "cancelled"):
        require(by_name[name]["certificate"] is None and
                by_name[name]["proof_status"] != "exact_original_verified",
                f"partial or candidate report {name} exposed an original proof")
    candidate_progress = by_name["candidate_progress"]
    require(candidate_progress["lower_evidence"] == "universal" and
            not candidate_progress["exact_scope_original"] and
            not candidate_progress["exact_diagnostic"]["scope_original"],
            "induced exact diagnostics became original lower-bound evidence")
    for name, certificate in (("exact_original_progress", "verified_optimum"),
                              ("exact_infeasible_progress", "verified_infeasible")):
        document = by_name[name]
        require(document["proof_status"] == "exact_original_verified" and
                document["phase"] == "complete" and document["exact_scope_original"] and
                document["certificate"] == by_name[certificate] and
                document["certificate"]["query_binding"] == document["query_binding"],
                f"completed original report {name} lost its actual binding/proof")

    validator = validators["residual-report-v1.schema.json"]
    rejected_count = 0

    # A schema rejection is the expected negative result; other failures must surface.
    def reject(base: str, path: tuple, value: object, label: str) -> None:
        nonlocal rejected_count
        document = copy.deepcopy(by_name[base])
        target = document
        for key in path[:-1]:
            target = target[key]
        target[path[-1]] = value
        try:
            validator.validate(document)
        except ValidationError:
            rejected_count += 1
            return
        raise RuntimeError(f"schema accepted malformed report: {label}")

    reject("exact_original_pending", ("certificate",), by_name["verified_optimum"], "premature certificate")
    reject("candidate_upper", ("certificate",), by_name["verified_optimum"], "upper promoted to proof")
    reject("candidate_upper", ("minimum_height",), 2, "forged upper minimum")
    reject("residual_trace", ("minimum_height",), 2, "forged trace minimum")
    reject("residual_trace", ("terminal",), "unknown", "unknown terminal enum")
    reject("residual_trace", ("layers", 0, "ears", 0, "anchors", 0, "condition"),
           "unknown", "unknown eligibility condition")
    reject("candidate_upper", ("height_upper_bound",), True, "Boolean height")
    reject("candidate_progress", ("lower_evidence",), "independently_checked", "induced lower authority")
    reject("candidate_progress", ("limits", "record_limit"), True, "Boolean record limit")
    reject("candidate_progress", ("limits", "exact", "producer", "work"), -1, "negative exact work")
    reject("exact_original_progress", ("exact_scope_original",), False, "wrong proof scope")
    reject("exact_infeasible_progress", ("height_upper_bound",), 1, "infeasible upper witness")
    print(f"{len(records)} typed residual reports validated; "
          f"{rejected_count} authority, enum and resource mutations rejected")


if __name__ == "__main__":
    try:
        main()
    except (ImportError, RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as error:
        print(f"residual report schema audit failed: {error}", file=sys.stderr)
        raise SystemExit(1)
