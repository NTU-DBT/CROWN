#!/usr/bin/env python3
"""Validate actual typed planner progress artifacts against local schemas."""
from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path
from typing import Any


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    from jsonschema import Draft202012Validator, RefResolver
    from jsonschema.exceptions import ValidationError

    require(len(sys.argv) == 3,
            "usage: verify_search_progress.py FIXTURE_EXECUTABLE REPOSITORY_ROOT")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(sys.argv[2]).resolve()
    schema_dir = root / "schemas"
    schemas = {path.name: json.loads(path.read_text(encoding="utf-8"))
               for path in schema_dir.glob("*.schema.json")}
    require("search-progress-v1.schema.json" in schemas,
            "search-progress-v1.schema.json is missing")

    store: dict[str, dict[str, Any]] = {}
    for name, schema in schemas.items():
        path = schema_dir / name
        store[path.as_uri()] = schema
        if "$id" in schema:
            store[schema["$id"]] = schema

    def local_file(uri: str) -> dict[str, Any]:
        if uri not in store:
            raise RuntimeError(f"schema reference is not in the local schema set: {uri}")
        return store[uri]

    def deny_network(uri: str) -> dict[str, Any]:
        raise RuntimeError(f"schema resolver attempted network access: {uri}")

    validators: dict[str, Draft202012Validator] = {}
    for name, schema in schemas.items():
        Draft202012Validator.check_schema(schema)
        resolver = RefResolver(
            base_uri=(schema_dir / name).as_uri(),
            referrer=schema,
            store=store,
            handlers={"file": local_file, "http": deny_network, "https": deny_network},
        )
        validators[name] = Draft202012Validator(schema, resolver=resolver)

    result = subprocess.run([executable, "--emit"], capture_output=True, text=True,
                            timeout=120, check=False)
    require(result.returncode == 0, f"fixture executable failed: {result.stderr.strip()}")
    require(not result.stderr, f"fixture executable wrote to stderr: {result.stderr.strip()}")
    records = json.loads(result.stdout)
    require(isinstance(records, list) and records, "fixture emitted no artifact records")

    by_name: dict[str, dict[str, Any]] = {}
    binding_versions: set[int] = set()
    for record in records:
        require(isinstance(record, dict) and
                set(record) == {"name", "schema", "document"},
                "artifact record must contain exactly name, schema, and document")
        name = record["name"]
        schema_name = record["schema"]
        document = record["document"]
        require(isinstance(name, str) and name not in by_name,
                f"artifact name is missing or duplicated: {name!r}")
        require(schema_name in validators, f"no local validator for {schema_name!r}")
        validators[schema_name].validate(document)
        by_name[name] = record
        binding = document.get("query_binding") if isinstance(document, dict) else None
        if isinstance(binding, dict):
            binding_versions.add(binding.get("schema_version"))
        if record["schema"] == "search-progress-v1.schema.json":
            require(document.get("certificate") is None,
                    f"progress artifact {name} exposed a certificate")

    required_names = {
        "strict_admitted", "strict_suspended", "best_found_before_proof",
        "validated_incumbent_upper", "search_complete", "verified_optimum",
        "replay_v1_paused", "replay_v1_complete", "replay_v2_paused",
        "replay_v2_complete", "replay_corrupt", "verified_infeasible",
        "date_v2_optimum", "metadata_v3_optimum",
    }
    require(required_names <= by_name.keys(),
            f"fixture omitted required artifacts: {sorted(required_names - by_name.keys())}")
    require({1, 2, 3} <= binding_versions,
            f"primitive/date/metadata binding versions missing: {sorted(binding_versions)}")

    strict_progress = by_name["search_complete"]["document"]
    upper = by_name["validated_incumbent_upper"]["document"]
    require(strict_progress["policy"] == "strict" and
            strict_progress["incumbent"] is None and strict_progress["certificate"] is None,
            "strict completed progress carried upper or proof authority")
    require(upper["artifact"] == "validated_incumbent" and
            "minimum_height" not in upper and upper["certificate"] is None,
            "validated upper artifact claimed a minimum or carried a certificate")
    for name in ("replay_v1_paused", "replay_v2_paused"):
        progress = by_name[name]["document"]
        require(not progress["complete"] and not progress["valid"] and
                progress["certificate"] is None,
                f"partial replay {name} exposed completed proof status")
    for name in ("replay_v1_complete", "replay_v2_complete"):
        progress = by_name[name]["document"]
        require(progress["complete"] and progress["valid"] and
                progress["certificate"] is None,
                f"completed replay {name} serialized a certificate payload")
    corrupt = by_name["replay_corrupt"]["document"]
    require(corrupt["phase"] == "failed" and corrupt["complete"] and
            not corrupt["valid"] and corrupt["certificate"] is None,
            "corrupt replay progress did not report failure without authority")

    # Progress remains uncertified even after valid replay; these are schema negatives.
    def rejected(document: dict[str, Any], label: str) -> None:
        try:
            validators["search-progress-v1.schema.json"].validate(document)
        except ValidationError:
            return
        raise RuntimeError(f"schema accepted invalid progress mutation: {label}")

    progress_schema = validators["search-progress-v1.schema.json"]
    in_progress = by_name["strict_suspended"]["document"]
    forged_certificate = json.loads(json.dumps(in_progress))
    forged_certificate["certificate"] = by_name["verified_optimum"]["document"]
    rejected(forged_certificate, "premature certificate")

    forged_height = json.loads(json.dumps(in_progress))
    forged_height["minimum_height"] = 2
    rejected(forged_height, "forged minimum_height")

    forged_status = json.loads(json.dumps(in_progress))
    forged_status["height_status"] = "verified_minimum"
    rejected(forged_status, "forged height_status")

    forged_incumbent = json.loads(json.dumps(in_progress))
    forged_incumbent["incumbent"] = upper
    rejected(forged_incumbent, "incumbent in strict policy")

    forged_limit = json.loads(json.dumps(in_progress))
    forged_limit["limits"]["producer"]["work"] = True
    rejected(forged_limit, "Boolean producer work ceiling")

    replay_progress = by_name["replay_v1_paused"]["document"]
    forged_replay_certificate = json.loads(json.dumps(replay_progress))
    forged_replay_certificate["certificate"] = by_name["verified_optimum"]["document"]
    rejected(forged_replay_certificate, "premature replay certificate")

    del progress_schema
    print(f"{len(records)} typed planner progress/certificate artifacts validated; "
          "6 authority and limit mutations rejected")


if __name__ == "__main__":
    try:
        main()
    except (ImportError, RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as error:
        print(f"planner progress schema audit failed: {error}", file=sys.stderr)
        raise SystemExit(1)
