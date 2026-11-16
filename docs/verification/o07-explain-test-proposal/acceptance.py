#!/usr/bin/env python3
"""Independent, offline O07 EXPLAIN CLI/schema acceptance harness.

This script is deliberately separate from the native test tree. It runs only
the two caller-supplied CLI binaries, records each process result, and writes
all generated files beneath --outputdir.
"""

from __future__ import annotations

import argparse
import copy
import hashlib
import json
import os
import re
import subprocess
import sys
import time
import traceback
import uuid
import warnings
from dataclasses import dataclass
from pathlib import Path
from typing import Any


READY_PACKAGE_SHA256 = "1062120b94a5733506186cb93cd6dac2bc99c7b4b3d3ab95e8c9c1882afbdb93"
MODE_CLI_SHA256 = "5187c47b1cb39e3604fe514a36010a647bfcbbb35fdbd90deb81ae1531e7d314"
MODE_RUNTIME_ARCHIVE_SHA256 = "3a51a21032690940c3c7c83f05ddd56e275811f61955f2ed438f9487b7bcb2b9"
SCHEMA_SHA256 = "78c04c2e29d42619de2f05f21e0f8c07fbe4c00d1da3a0aaf536629cfe6a198a"
PROPOSAL_DIR = Path("docs/verification/o07-explain-proposal")
MANIFEST_PATH = Path("tests/structural/lowering/manifest.json")


def sha256_bytes(value: bytes) -> str:
    return hashlib.sha256(value).hexdigest()


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def json_bytes(value: Any) -> bytes:
    return (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode("utf-8")


def read_json(path: Path) -> Any:
    with path.open("r", encoding="utf-8") as stream:
        return json.load(stream)


def inside(path: Path, root: Path) -> bool:
    try:
        path.relative_to(root)
        return True
    except ValueError:
        return False


def safe_name(value: str) -> str:
    return re.sub(r"[^A-Za-z0-9_.-]+", "_", value).strip("_") or "item"


@dataclass
class Invocation:
    name: str
    directory: Path
    returncode: int
    stdout: bytes
    stderr: bytes
    parsed_json: Any | None


class Harness:
    def __init__(self, repo: Path, native_cli: Path, explain_cli: Path, outputdir: Path):
        self.repo = repo.resolve()
        self.native_cli = native_cli.resolve()
        self.explain_cli = explain_cli.resolve()
        self.outputdir = outputdir.resolve()
        self.run_dir: Path | None = None
        self.checks: list[dict[str, Any]] = []
        self.invocations: list[Invocation] = []
        self.hash_record: dict[str, Any] = {}
        self.validators: tuple[Any, Any] | None = None
        self.schema: dict[str, Any] | None = None

    def check(self, condition: bool, label: str, detail: str = "") -> None:
        record: dict[str, Any] = {"check": label, "status": "passed" if condition else "failed"}
        if detail:
            record["detail"] = detail
        self.checks.append(record)
        if not condition:
            raise AssertionError(f"{label}: {detail or 'condition was false'}")

    def setup_output(self) -> None:
        tmp_root = Path("/tmp").resolve()
        verification_root = (self.repo / "build/verification").resolve()
        allowed = self.outputdir == tmp_root or inside(self.outputdir, tmp_root) or inside(self.outputdir, verification_root)
        self.check(allowed, "output directory is under /tmp or build/verification", str(self.outputdir))
        self.outputdir.mkdir(parents=True, exist_ok=True)
        stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime())
        self.run_dir = self.outputdir / f"o07-explain-acceptance-{stamp}-{os.getpid()}-{uuid.uuid4().hex[:8]}"
        self.run_dir.mkdir()

    @property
    def out(self) -> Path:
        if self.run_dir is None:
            raise RuntimeError("output directory is not initialized")
        return self.run_dir

    def verify_frozen_inputs(self) -> tuple[Path, Path]:
        proposal = self.repo / PROPOSAL_DIR
        readiness_path = proposal / "readiness.json"
        evidence_path = proposal / "compile-evidence-mode-binding.json"
        dependency_path = proposal / "baseline-dependencies-mode-binding.json"
        schema_path = proposal / "schemas/explain-report-v1.schema.json"

        readiness = read_json(readiness_path)
        evidence = read_json(evidence_path)
        dependencies = read_json(dependency_path)
        self.check(readiness.get("executed") is False, "proposal readiness is compile/link-only")
        self.check(readiness.get("package_sha256") == READY_PACKAGE_SHA256, "frozen proposal package fingerprint")
        self.check(evidence.get("executed") is False and evidence.get("mode_binding_api") is True,
                   "mode-binding CLI evidence is non-executed and uses the mode-binding API")
        self.check(evidence.get("kind") == "compile/link only", "mode-binding evidence kind")

        readiness_files = readiness.get("files")
        self.check(isinstance(readiness_files, dict) and bool(readiness_files), "readiness contains proposal file hashes")
        actual_files: dict[str, str] = {}
        for relative, expected_hash in sorted(readiness_files.items()):
            path = proposal / relative
            actual_hash = sha256_file(path)
            self.check(actual_hash == expected_hash, f"frozen proposal file hash: {relative}")
            actual_files[relative] = actual_hash
        package_hash = sha256_bytes(json.dumps(readiness_files, sort_keys=True, separators=(",", ":")).encode("utf-8"))
        self.check(package_hash == READY_PACKAGE_SHA256, "canonical proposal package hash")

        schema_hash = sha256_file(schema_path)
        self.check(schema_hash == SCHEMA_SHA256, "frozen report schema hash")
        self.check(readiness_files.get("schemas/explain-report-v1.schema.json") == SCHEMA_SHA256,
                   "schema hash is included in the frozen package")

        binary_hash = sha256_file(self.explain_cli)
        self.check(binary_hash == MODE_CLI_SHA256, "selected explain CLI is the frozen mode-binding binary", binary_hash)
        self.check(evidence.get("binary_sha256") == MODE_CLI_SHA256, "compile evidence pins the selected explain CLI")
        self.check(readiness.get("mode_binding_binary") == MODE_CLI_SHA256,
                   "readiness pins the selected explain CLI")

        source_hashes: dict[str, str] = {}
        for relative, expected_hash in sorted(dependencies.get("inputs", {}).items()):
            path = self.repo / relative
            actual_hash = sha256_file(path)
            self.check(actual_hash == expected_hash, f"frozen dependency hash: {relative}")
            source_hashes[relative] = actual_hash

        archive_hashes: dict[str, str] = {}
        archives = evidence.get("archives")
        self.check(isinstance(archives, dict) and bool(archives), "compile evidence records linked archives")
        for archive_name, expected_hash in sorted(archives.items()):
            archive = Path(archive_name)
            actual_hash = sha256_file(archive)
            self.check(actual_hash == expected_hash, f"linked archive hash: {archive_name}")
            archive_hashes[archive_name] = actual_hash
        mode_archive = next((path for path in archive_hashes if "libcrown_runtime_o07_mode_binding.a" in path), None)
        self.check(mode_archive is not None, "complete mode-binding runtime archive is in the link evidence")
        if mode_archive is not None:
            self.check(archive_hashes[mode_archive] == MODE_RUNTIME_ARCHIVE_SHA256,
                       "complete nine-unit mode-binding runtime archive hash", archive_hashes[mode_archive])

        native_hash = sha256_file(self.native_cli)
        self.hash_record = {
            "readiness_json_sha256": sha256_file(readiness_path),
            "compile_evidence_sha256": sha256_file(evidence_path),
            "dependency_manifest_sha256": sha256_file(dependency_path),
            "package_sha256": package_hash,
            "proposal_files": actual_files,
            "mode_binding_dependencies": source_hashes,
            "linked_archives": archive_hashes,
            "schema_sha256": schema_hash,
            "explain_cli_sha256": binary_hash,
            "native_cli_sha256": native_hash,
        }
        return schema_path, proposal / "schemas/explain-report-v1.schema.json"

    def prepare_schema(self, schema_path: Path) -> None:
        try:
            with warnings.catch_warnings():
                warnings.simplefilter("ignore", DeprecationWarning)
                from jsonschema import Draft202012Validator, RefResolver
        except ImportError as error:
            raise RuntimeError("Python package jsonschema>=4 is required; validation itself is fully offline") from error
        self.schema = read_json(schema_path)
        Draft202012Validator.check_schema(self.schema)
        store = {schema_path.resolve().as_uri(): self.schema}
        if "$id" in self.schema:
            store[self.schema["$id"]] = self.schema

        def local_file(uri: str) -> Any:
            if uri not in store:
                raise RuntimeError("schema reference outside the local schema: " + uri)
            return store[uri]

        def deny_network(uri: str) -> Any:
            raise RuntimeError("offline schema validation attempted network access: " + uri)

        resolver = RefResolver(
            schema_path.resolve().as_uri(), self.schema, store=store,
            handlers={"file": local_file, "http": deny_network, "https": deny_network},
        )
        validator = Draft202012Validator(self.schema, resolver=resolver)
        self.validators = (validator, validator)
        self.check(True, "Draft 2020-12 schema is valid and loaded from the pinned local file")

    def input_hashes(self, inputs: dict[str, Path]) -> dict[str, dict[str, Any]]:
        result: dict[str, dict[str, Any]] = {}
        for label, path in sorted(inputs.items()):
            resolved = path.resolve()
            if resolved.is_file():
                result[label] = {"path": str(resolved), "exists": True, "sha256": sha256_file(resolved)}
            else:
                result[label] = {"path": str(resolved), "exists": False, "sha256": None}
        return result

    def invoke(self, name: str, argv: list[str], inputs: dict[str, Path], expected_rc: int,
               json_output: bool = False, timeout: int = 180) -> Invocation:
        folder = self.out / "commands" / f"{len(self.invocations) + 1:04d}-{safe_name(name)}"
        folder.mkdir(parents=True)
        hashes = self.input_hashes(inputs)
        stdout = b""
        stderr = b""
        try:
            completed = subprocess.run(argv, cwd=self.repo, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                       check=False, timeout=timeout)
            returncode = completed.returncode
            stdout, stderr = completed.stdout, completed.stderr
        except subprocess.TimeoutExpired as error:
            returncode = 124
            stdout = error.stdout or b""
            stderr = error.stderr or b""
        (folder / "stdout.bin").write_bytes(stdout)
        (folder / "stderr.bin").write_bytes(stderr)
        (folder / "inputs.json").write_bytes(json_bytes(hashes))
        parsed = None
        parse_error = None
        if json_output:
            try:
                parsed = json.loads(stdout.decode("utf-8"))
            except (UnicodeDecodeError, json.JSONDecodeError) as error:
                parse_error = f"{type(error).__name__}: {error}"
        result_record = {
            "stdout_bytes": len(stdout),
            "stdout_sha256": sha256_bytes(stdout),
            "stderr_bytes": len(stderr),
            "stderr_sha256": sha256_bytes(stderr),
            "json_output_requested": json_output,
            "parsed_json": parsed,
            "json_parse_error": parse_error,
        }
        (folder / "result.json").write_bytes(json_bytes(result_record))
        (folder / "invocation.json").write_bytes(json_bytes({
            "argv": argv,
            "cwd": str(self.repo),
            "expected_returncode": expected_rc,
            "returncode": returncode,
            "timed_out": returncode == 124,
        }))
        invocation = Invocation(name, folder, returncode, stdout, stderr, parsed)
        self.invocations.append(invocation)
        self.check(returncode == expected_rc, f"command exit status: {name}", f"expected {expected_rc}, got {returncode}")
        if json_output and expected_rc == 0:
            self.check(parsed is not None, f"command produced parseable JSON: {name}", parse_error or "")
        return invocation

    def schema_error_count(self, validator: Any, instance: Any) -> int:
        return sum(1 for _ in validator.iter_errors(instance))

    def expect_schema_reject(self, validator: Any, instance: Any, label: str) -> None:
        self.check(self.schema_error_count(validator, instance) > 0, label)

    def validate_report_schema(self, report: Any, label: str) -> None:
        if self.validators is None:
            raise RuntimeError("schema validator is unavailable")
        errors = list(self.validators[0].iter_errors(report))
        if errors:
            first = errors[0]
            raise AssertionError(f"schema rejects {label} at {list(first.absolute_path)}: {first.message}")
        self.check(True, f"offline schema accepts emitted report: {label}")

    @staticmethod
    def variable_ids(source_document: dict[str, Any]) -> dict[str, int]:
        return {variable["name"]: index for index, variable in enumerate(source_document["query"]["variables"])}

    @staticmethod
    def occurrence_ids(source_document: dict[str, Any]) -> dict[str, int]:
        return {atom["id"]: index for index, atom in enumerate(source_document["query"]["atoms"])}

    def compare_tree(self, report: dict[str, Any], plan: dict[str, Any], expected: dict[str, Any], case_id: str) -> None:
        native_tree = plan["tree"]
        source_document = plan["source"]["document"]
        var_ids = self.variable_ids(source_document)
        occurrence_ids = self.occurrence_ids(source_document)
        selected = report["structure"]["selected_tree"]
        tree_nodes = native_tree["nodes"]
        physical_nodes = plan["nodes"]
        selected_nodes = selected["nodes"]
        node_ids = {node["id"]: index for index, node in enumerate(tree_nodes)}
        layouts = {layout["layout_id"]: layout for layout in plan["layouts"]}
        parent_by_id: dict[str, str] = {}
        for node in tree_nodes:
            for child in node["children"]:
                self.check(child not in parent_by_id, f"fixture {case_id}: actual plan tree has at most one parent", child)
                parent_by_id[child] = node["id"]
        c_star = set(plan["verification"]["maximal_connex"])

        self.check(selected["root"] == (node_ids.get(native_tree["root"]) if native_tree["root"] is not None else None),
                   f"fixture {case_id}: selected root matches P08 plan")
        expected_roots = [label for label, node in expected["nodes"].items() if node["parent"] is None]
        expected_root = expected_roots[0] if len(expected_roots) == 1 else None
        self.check(native_tree["root"] == expected_root,
                   f"fixture {case_id}: P08 root matches manifest expectation")
        self.check(len(tree_nodes) == len(physical_nodes) == len(selected_nodes),
                   f"fixture {case_id}: node count matches P08 plan")
        self.check(set(expected["nodes"]) == set(node_ids), f"fixture {case_id}: manifest covers every actual tree node")

        for index, raw in enumerate(tree_nodes):
            label = raw["id"]
            selected_node = selected_nodes[index]
            physical = physical_nodes[index]
            fixture = expected["nodes"][label]
            parent_name = parent_by_id.get(label)
            parent_index = node_ids[parent_name] if parent_name is not None else None
            scope_ids = sorted(var_ids[name] for name in raw["scope"])
            child_ids = [node_ids[name] for name in raw["children"]]
            separator_names = sorted(set(raw["scope"]) & set(next(
                (parent["scope"] for parent in tree_nodes if parent["id"] == parent_name), []
            )), key=var_ids.__getitem__)
            separator_ids = [var_ids[name] for name in separator_names]
            parent_projection = physical["parent_key"]
            source_layout = layouts[parent_projection["source_layout"]]
            physical_separator_ids = [source_layout["fields"][field]["variable"]
                                      for field in parent_projection["fields"]]
            occurrence = occurrence_ids[raw["occurrence"]] if raw["kind"] == "native" else None
            visible_ids = list(physical["visible_scope"])
            connex = index in c_star

            self.check(selected_node["id"] == index and selected_node["label"] == label,
                       f"fixture {case_id}/{label}: selected node ID and label")
            self.check(selected_node["kind"] == raw["kind"] == physical["kind"],
                       f"fixture {case_id}/{label}: selected kind matches P08 plan")
            self.check(selected_node["occurrence"] == occurrence == physical["occurrence"],
                       f"fixture {case_id}/{label}: native occurrence binding")
            self.check(selected_node["scope"] == scope_ids == physical["scope"],
                       f"fixture {case_id}/{label}: scope matches P08 plan")
            self.check(selected_node["children"] == child_ids == physical["children"],
                       f"fixture {case_id}/{label}: children match P08 plan")
            self.check(selected_node["separator"] == separator_ids,
                       f"fixture {case_id}/{label}: separator matches P08 parent intersection")
            self.check(selected_node["separator"] == physical_separator_ids,
                       f"fixture {case_id}/{label}: separator matches P08 physical parent-key projection")
            self.check(selected_node["connex"] == connex == physical["connex"],
                       f"fixture {case_id}/{label}: C* membership matches P08 verification")
            self.check(physical["parent"] == parent_index,
                       f"fixture {case_id}/{label}: parent matches actual plan")
            self.check(visible_ids == sorted(visible_ids) and all(isinstance(value, int) for value in visible_ids),
                       f"fixture {case_id}/{label}: P08 visible scope is an ordered ID list")
            self.check(visible_ids == [var_ids[name] for name in fixture["visible"]],
                       f"fixture {case_id}/{label}: visible scope matches manifest")
            self.check(scope_ids == [var_ids[name] for name in fixture["scope"]],
                       f"fixture {case_id}/{label}: scope matches manifest")
            self.check(parent_index == (node_ids[fixture["parent"]] if fixture["parent"] is not None else None),
                       f"fixture {case_id}/{label}: parent matches manifest")
            self.check(child_ids == [node_ids[name] for name in fixture["children"]],
                       f"fixture {case_id}/{label}: children match manifest")
            self.check(separator_ids == [var_ids[name] for name in fixture["separator"]],
                       f"fixture {case_id}/{label}: separator matches manifest")
            self.check(connex == fixture["connex"], f"fixture {case_id}/{label}: C* matches manifest")

    def compare_report(self, report: dict[str, Any], plan: dict[str, Any], case: dict[str, Any]) -> None:
        case_id = case["id"]
        expected = case["expected"]
        native_verification = plan["verification"]
        height = native_verification["native_height"]
        evidence = report["height_evidence"]
        self.check(report["schema_version"] == 1 and report["artifact"] == "crown_explain",
                   f"fixture {case_id}: report schema/artifact identity")
        self.check(report["authority"] == "diagnostic_export_only", f"fixture {case_id}: report authority is diagnostic")
        self.check(report["route"] == plan["route"] == expected["route"], f"fixture {case_id}: route matches P08 and manifest")
        self.check(report["identity"]["physical_sha256"] == plan["binding"]["physical_sha256"],
                   f"fixture {case_id}: physical plan identity")
        for key in ("semantic_sha256", "output_contract_sha256", "cost_inputs_sha256", "plan_cache_sha256"):
            self.check(report["identity"][key] == plan["binding"]["identity"][key],
                       f"fixture {case_id}: {key} matches P08 binding")
        self.check(report["structure"]["native_height"] == height == evidence["selected_height"],
                   f"fixture {case_id}: selected and native heights agree")
        self.check(report["structure"]["edge_depth"] == native_verification["edge_depth"],
                   f"fixture {case_id}: edge depth matches P08 plan")
        self.check(evidence["status"] == "checked_upper" and evidence["source"] == "p08_checked_upper_only",
                   f"fixture {case_id}: P08 plan remains checked_upper without proof")
        self.check(evidence["original_minimum"] is None and evidence["algorithm"] is None and
                   evidence["original_witness"] is None and evidence["lower_bound_claims"] is None,
                   f"fixture {case_id}: no minimum-height proof is invented")
        self.check(report["mode"]["scope"] == "compile_only" and report["mode"]["runtime"] is None,
                   f"fixture {case_id}: compile-only mode status")
        self.check(report["cost"] == {
            "selection": "not_implemented", "statistics": "unavailable",
            "estimated_state": "unavailable", "global_optimality": False,
        }, f"fixture {case_id}: cost claims stay unavailable")

        observations = report["observations"]
        self.check(observations["availability"] == "unavailable" and observations["current"] is None and
                   observations["last"] is None and observations["lifetime"] is None,
                   f"fixture {case_id}: compile-only observation values are unavailable")
        self.check(observations["current_configuration"] is None,
                   f"fixture {case_id}: compile-only report has no runtime configuration")
        registry = observations["registry"]
        registry_ids = [item["id"] for item in registry]
        registry_names = [item["name"] for item in registry]
        self.check(registry_ids == list(range(len(registry))), f"fixture {case_id}: registry IDs are contiguous")
        self.check(len(registry_names) == len(set(registry_names)), f"fixture {case_id}: registry names are unique")
        for item in registry:
            self.check(item["unit"] in {"nanoseconds", "accounted_bytes", "abstract_actions", "count"} and
                       isinstance(item["scope"], str) and bool(item["scope"].strip()) and
                       isinstance(item["includes"], str),
                       f"fixture {case_id}: registry unit and scope are explicit", item["name"])

        self.compare_tree(report, plan, expected, case_id)

    def check_text(self, output: bytes, report: dict[str, Any], case_id: str) -> None:
        text = output.decode("utf-8", errors="strict")
        status = report["height_evidence"]["status"]
        height = report["height_evidence"]["selected_height"]
        self.check(f"Height: {height} ({status})" in text, f"fixture {case_id}: human height matches JSON")
        self.check("Cost selection: not implemented; statistics and estimated state unavailable." in text,
                   f"fixture {case_id}: human cost meaning matches JSON")
        self.check("Mode descriptor:" in text and "compile_only" in text,
                   f"fixture {case_id}: human mode meaning matches JSON")
        self.check(all(byte >= 32 or byte == 10 for byte in output),
                   f"fixture {case_id}: human output has no unescaped control bytes")

    def check_dot(self, output: bytes, report: dict[str, Any], case_id: str) -> None:
        dot = output.decode("utf-8", errors="strict")
        selected = report["structure"]["selected_tree"]
        node_lines = re.findall(r"^\s*n[0-9]+\s+\[", dot, flags=re.MULTILINE)
        self.check(dot.startswith("digraph crown {\n") and dot.endswith("}\n"),
                   f"fixture {case_id}: DOT graph has complete lexical boundaries")
        self.check(len(node_lines) == len(selected["nodes"]), f"fixture {case_id}: DOT node declarations match report")
        if not selected["nodes"]:
            self.check("constant [shape=plaintext,label=" in dot,
                       f"fixture {case_id}: constant route has an explicit DOT marker")
        self.check(all(byte >= 32 or byte == 10 for byte in output),
                   f"fixture {case_id}: DOT output has no raw label control bytes")

    def run_valid_manifest_cases(self) -> list[tuple[dict[str, Any], Path, dict[str, Any]]]:
        manifest = read_json(self.repo / MANIFEST_PATH)
        cases = [case for case in manifest["cases"] if case["expected"]["valid"]]
        self.check(bool(cases), "lowering manifest contains valid fixtures")
        self.check(len(cases) + sum(1 for case in manifest["cases"] if not case["expected"]["valid"]) == len(manifest["cases"]),
                   "lowering manifest validity partition covers every case")
        results = []
        for case in cases:
            case_dir = self.out / "fixtures" / safe_name(case["id"])
            case_dir.mkdir(parents=True)
            query = self.repo / case["query"]
            tree = self.repo / case["tree"]
            native = self.invoke(
                f"{case['id']}-lower-plan",
                [str(self.native_cli), "lower-plan", str(query), str(tree)],
                {"native_cli": self.native_cli, "query": query, "tree": tree},
                0, json_output=True,
            )
            if not isinstance(native.parsed_json, dict):
                raise AssertionError(f"{case['id']}: lower-plan did not produce a physical plan object")
            plan_path = native.directory / "stdout.bin"
            plan = native.parsed_json
            self.check(plan.get("route") == case["expected"]["route"],
                       f"fixture {case['id']}: native lower-plan route")

            report_invocation = self.invoke(
                f"{case['id']}-explain-json",
                [str(self.explain_cli), str(plan_path), "--format", "json"],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path,
                 "schema": self.repo / PROPOSAL_DIR / "schemas/explain-report-v1.schema.json"},
                0, json_output=True,
            )
            if not isinstance(report_invocation.parsed_json, dict):
                raise AssertionError(f"{case['id']}: explain JSON output is not an object")
            report = report_invocation.parsed_json
            self.validate_report_schema(report, case["id"])
            self.compare_report(report, plan, case)

            text = self.invoke(
                f"{case['id']}-explain-text",
                [str(self.explain_cli), str(plan_path), "--format", "text"],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 0,
            )
            self.check_text(text.stdout, report, case["id"])
            dot = self.invoke(
                f"{case['id']}-explain-dot",
                [str(self.explain_cli), str(plan_path), "--format", "dot"],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 0,
            )
            self.check_dot(dot.stdout, report, case["id"])
            results.append((case, plan_path, report))
        return results

    def run_schema_mutations(self, base_report: dict[str, Any]) -> dict[str, Any]:
        if self.schema is None or self.validators is None:
            raise RuntimeError("schema is not loaded")
        validator = self.validators[0]
        rejected = 0
        for label, path, value in [
            ("wrong schema version", ("schema_version",), 2),
            ("wrong authority", ("authority",), "verified_artifact"),
            ("wrong route enum", ("route",), "global_optimum"),
            ("wrong height status enum", ("height_evidence", "status"), "proved_minimum_without_proof"),
            ("unknown top-level field", ("unexpected_claim",), True),
        ]:
            mutated = copy.deepcopy(base_report)
            target = mutated
            for field in path[:-1]:
                target = target[field]
            target[path[-1]] = value
            self.expect_schema_reject(validator, mutated, f"schema rejects mutation: {label}")
            rejected += 1

        false_minimum = copy.deepcopy(base_report)
        false_minimum["height_evidence"]["status"] = "verified_original_minimum"
        self.expect_schema_reject(validator, false_minimum,
                                  "schema rejects minimum status without a proof-shaped payload")
        rejected += 1

        # Create a shape-valid, synthetic available summary to exercise metric
        # availability rules. It is schema input only and is never authority.
        synthetic = copy.deepcopy(base_report)
        observations = synthetic["observations"]
        descriptors = observations["registry"]
        self.check(bool(descriptors), "observation registry supplies metric mutation fixtures")
        values = [{"id": item["id"], "availability": "available", "value": 0, "saturated": False}
                  for item in descriptors]
        summary = {
            "attempt": 0, "sequence": 0,
            "owner_layer": descriptors[0]["layer"] if descriptors else "delta",
            "outcome": "committed", "mode_binding": "not_recorded", "configuration": None,
            "values": values,
        }
        observations["availability"] = "available"
        observations["current"] = copy.deepcopy(summary)
        observations["last"] = copy.deepcopy(summary)
        observations["lifetime"] = {"attempts": 1, "commits": 1, "aborts": 0, "saturated": False}
        self.check(self.schema_error_count(validator, synthetic) == 0,
                   "schema accepts a structurally valid synthetic summary for mutation checks")

        valid_unavailable_metric = copy.deepcopy(synthetic)
        unavailable_metric = valid_unavailable_metric["observations"]["last"]["values"][0]
        unavailable_metric["availability"] = "unavailable"
        unavailable_metric["value"] = None
        unavailable_metric["saturated"] = None
        self.check(self.schema_error_count(validator, valid_unavailable_metric) == 0,
                   "schema accepts unavailable metrics with null value and saturation payloads")

        malformed_metric = copy.deepcopy(synthetic)
        metric = malformed_metric["observations"]["last"]["values"][0]
        metric["availability"] = "unavailable"
        self.expect_schema_reject(validator, malformed_metric,
                                  "schema rejects unavailable metric with a numeric payload")
        rejected += 1

        bad_metric_enum = copy.deepcopy(synthetic)
        bad_metric_enum["observations"]["current"]["values"][0]["availability"] = "estimated"
        self.expect_schema_reject(validator, bad_metric_enum, "schema rejects unknown metric availability enum")
        rejected += 1

        bad_descriptor = copy.deepcopy(base_report)
        bad_descriptor["observations"]["registry"][0]["unit"] = "parsecs"
        self.expect_schema_reject(validator, bad_descriptor, "schema rejects unknown registry unit enum")
        rejected += 1

        configuration_probe = copy.deepcopy(base_report)
        configuration_probe["observations"]["current_configuration"] = {
            "format_version": 1, "support_owner": 0, "generation": 0, "generation_saturated": False,
            "mode": "delta", "completion": "ordered_replay", "live_maintenance": "on_output", "view": "core",
            "query_factors": 0,
            "requested_options": {
                "mode": "delta", "view": "core", "live_maintenance": "on_output", "completion": "automatic",
                "work_limit": None, "cursor_work_limit": None, "view_work_limit": None,
                "spool_row_limit": 0, "spool_byte_limit": 0,
                "physical": {
                    "work_limit": None, "derivation_limit": 0,
                    "support": {
                        "work_limit": None, "support_limit": 0, "order": "fifo", "capture_transitions": False,
                        "observation": {
                            "mode": "off", "trace_capacity": 0, "sample_period": 1,
                            "sample_offset": 0, "trace_timings": False,
                        },
                    },
                },
            },
            "identity_scope": "process_local_owner_generation; saturated_generation_is_not_unique",
            "guarantee_prose": "not_copied_from_current_profile",
        }
        self.check(self.schema_error_count(validator, configuration_probe) == 0,
                   "schema accepts a structurally valid synthetic configuration for mutation checks")
        bad_owner = copy.deepcopy(configuration_probe)
        bad_owner["observations"]["current_configuration"]["support_owner"] = "owner-zero"
        self.expect_schema_reject(validator, bad_owner, "schema rejects a noninteger owner ID")
        rejected += 1
        bad_option_type = copy.deepcopy(configuration_probe)
        bad_option_type["observations"]["current_configuration"]["requested_options"]["physical"]["support"]["order"] = 1
        self.expect_schema_reject(validator, bad_option_type, "schema rejects the wrong configuration option type")
        rejected += 1

        extra_cost_claim = copy.deepcopy(base_report)
        extra_cost_claim["cost"]["global_cost_optimal"] = True
        self.expect_schema_reject(validator, extra_cost_claim, "schema rejects an extra global-cost-optimal flag")
        rejected += 1

        # JSON Schema intentionally cannot express this semantic equality.
        # The harness checks it for every actual emitted report above.
        cross_field_mismatch = copy.deepcopy(base_report)
        cross_field_mismatch["height_evidence"]["selected_height"] += 1
        self.check(self.schema_error_count(validator, cross_field_mismatch) == 0,
                   "schema limitation: selected-height cross-field mismatch remains structurally valid")

        mutation_record = {"schema_rejected_mutations": rejected,
                           "cross_field_mismatch_schema_accepted": True,
                           "synthetic_summary_used_only_for_schema_shape": True}
        (self.out / "schema-mutations.json").write_bytes(json_bytes(mutation_record))
        return mutation_record

    def write_generated(self, path: Path, data: Any) -> Path:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(json_bytes(data))
        return path

    def run_explain_json(self, name: str, plan_path: Path, certificate: Path | None = None,
                         expected_rc: int = 0) -> Invocation:
        argv = [str(self.explain_cli), str(plan_path), "--format", "json"]
        inputs = {"explain_cli": self.explain_cli, "physical_plan": plan_path}
        if certificate is not None:
            argv.extend(["--certificate", str(certificate)])
            inputs["certificate"] = certificate
        return self.invoke(name, argv, inputs, expected_rc, json_output=expected_rc == 0)

    def run_certificate_cases(self, valid_cases: list[tuple[dict[str, Any], Path, dict[str, Any]]]) -> dict[str, Any]:
        simple_case = next((entry for entry in valid_cases if entry[0]["id"] == "native_singleton_root"), valid_cases[0])
        proof_case = simple_case[0]
        plan_path = simple_case[1]
        query = self.repo / proof_case["query"]
        oracle = self.invoke(
            "matching-query-tree-oracle",
            [str(self.native_cli), "tree-oracle", str(query)],
            {"native_cli": self.native_cli, "query": query}, 0, json_output=True,
        )
        if not isinstance(oracle.parsed_json, dict) or oracle.parsed_json.get("certificate") is None:
            raise AssertionError("tree-oracle did not produce a certificate")
        self.check(oracle.parsed_json.get("height_status") == "proven_minimum",
                   "native tree-oracle certificate reports a proven minimum")
        certificate = oracle.parsed_json["certificate"]
        cert_path = self.write_generated(self.out / "certificates/matching.json", certificate)
        matching = self.run_explain_json("matching-certificate-replay", plan_path, cert_path)
        if not isinstance(matching.parsed_json, dict):
            raise AssertionError("matching certificate replay did not produce JSON")
        report = matching.parsed_json
        self.validate_report_schema(report, "matching-certificate-replay")
        self.check(report["height_evidence"]["status"] == "verified_original_minimum",
                   "matching exact-binding certificate establishes original minimum")
        self.check(report["height_evidence"]["original_minimum"] == report["structure"]["native_height"] ==
                   report["height_evidence"]["selected_height"],
                   "replayed certificate height matches selected P08 height")
        self.check(report["height_evidence"]["source"] == "p06_verified_optimum",
                   "replayed certificate source is the native P06 checked optimum")

        other_case = next((entry for entry in valid_cases if entry[0]["id"] != proof_case["id"]), None)
        if other_case is None:
            raise AssertionError("a second valid query fixture is required for binding mismatch coverage")
        other_query = self.repo / other_case[0]["query"]
        other_oracle = self.invoke(
            "wrong-query-tree-oracle",
            [str(self.native_cli), "tree-oracle", str(other_query)],
            {"native_cli": self.native_cli, "query": other_query}, 0, json_output=True,
        )
        if not isinstance(other_oracle.parsed_json, dict) or other_oracle.parsed_json.get("certificate") is None:
            raise AssertionError("second tree-oracle did not produce a certificate")
        wrong_query_cert = self.write_generated(self.out / "certificates/wrong-query.json", other_oracle.parsed_json["certificate"])
        wrong_query = self.run_explain_json("wrong-query-certificate", plan_path, wrong_query_cert, expected_rc=1)
        self.check(wrong_query.stdout == b"", "wrong-query certificate emits no partial report")

        wrong_height_value = copy.deepcopy(certificate)
        minimum = wrong_height_value.get("minimum_height")
        if not isinstance(minimum, int):
            raise AssertionError("tree-oracle certificate has no integer minimum height")
        wrong_height_value["minimum_height"] = minimum + 1
        wrong_height_cert = self.write_generated(self.out / "certificates/wrong-height.json", wrong_height_value)
        wrong_height = self.run_explain_json("wrong-height-certificate", plan_path, wrong_height_cert, expected_rc=1)
        self.check(wrong_height.stdout == b"", "wrong-height certificate emits no partial report")

        corrupted_value = copy.deepcopy(certificate)
        lower_bounds = corrupted_value.get("lower_bounds", [])
        if lower_bounds:
            old_bound = lower_bounds[0].get("bound")
            lower_bounds[0]["bound"] = (old_bound if isinstance(old_bound, int) else 0) + 1000000
        else:
            corrupted_value["algorithm"] = "corrupted_certificate_algorithm"
        corrupted_cert = self.write_generated(self.out / "certificates/corrupted.json", corrupted_value)
        corrupted = self.run_explain_json("corrupted-certificate", plan_path, corrupted_cert, expected_rc=1)
        self.check(corrupted.stdout == b"", "corrupted certificate emits no partial report")

        malformed_cert = self.out / "certificates/malformed.json"
        malformed_cert.write_bytes(b"{\"schema_version\":")
        malformed = self.run_explain_json("malformed-certificate", plan_path, malformed_cert, expected_rc=1)
        self.check(malformed.stdout == b"", "malformed certificate emits no partial report")
        return {
            "matching_certificate_status": "verified_original_minimum",
            "wrong_query_rejected": wrong_query.returncode != 0,
            "wrong_height_rejected": wrong_height.returncode != 0,
            "corrupted_certificate_rejected": corrupted.returncode != 0,
            "malformed_certificate_rejected": malformed.returncode != 0,
        }

    def run_invalid_cli_cases(self, plan_path: Path) -> int:
        malformed_plan = self.out / "invalid-inputs/malformed-plan.json"
        malformed_plan.parent.mkdir(parents=True, exist_ok=True)
        malformed_plan.write_bytes(b"{\"schema_version\":")
        missing_plan = self.out / "invalid-inputs/missing-plan.json"
        cases = [
            ("unknown-format", [str(self.explain_cli), str(plan_path), "--format", "xml"], {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 2),
            ("unknown-flag", [str(self.explain_cli), str(plan_path), "--unknown", "value"], {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 2),
            ("dangling-flag", [str(self.explain_cli), str(plan_path), "--max-bytes"], {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 2),
            ("invalid-byte-limit", [str(self.explain_cli), str(plan_path), "--max-bytes", "not-a-number"], {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 2),
            ("missing-input", [str(self.explain_cli), str(missing_plan), "--format", "json"], {"explain_cli": self.explain_cli, "physical_plan": missing_plan}, 1),
            ("malformed-input", [str(self.explain_cli), str(malformed_plan), "--format", "json"], {"explain_cli": self.explain_cli, "physical_plan": malformed_plan}, 1),
        ]
        for name, argv, inputs, expected_rc in cases:
            invocation = self.invoke(name, argv, inputs, expected_rc)
            self.check(invocation.stdout == b"", f"invalid CLI case emits no partial output: {name}")
        return len(cases)

    def run_byte_limits(self, plan_path: Path) -> dict[str, int]:
        lengths: dict[str, int] = {}
        for output_format in ("text", "json", "dot"):
            baseline = self.invoke(
                f"byte-limit-{output_format}-baseline",
                [str(self.explain_cli), str(plan_path), "--format", output_format],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path},
                0, json_output=output_format == "json",
            )
            byte_count = len(baseline.stdout)
            self.check(byte_count > 0, f"byte-limit {output_format}: baseline output is nonempty")
            exact = self.invoke(
                f"byte-limit-{output_format}-exact",
                [str(self.explain_cli), str(plan_path), "--format", output_format, "--max-bytes", str(byte_count)],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path},
                0, json_output=output_format == "json",
            )
            self.check(exact.stdout == baseline.stdout, f"byte-limit {output_format}: exact ceiling returns complete identical output")
            below = self.invoke(
                f"byte-limit-{output_format}-below",
                [str(self.explain_cli), str(plan_path), "--format", output_format, "--max-bytes", str(byte_count - 1)],
                {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 4,
            )
            self.check(below.stdout == b"", f"byte-limit {output_format}: N-1 ceiling emits no partial output")
            lengths[output_format] = byte_count
        return lengths

    def run_escaped_label_fixture(self) -> dict[str, Any]:
        var_name = "v\x00雪\x01"
        occurrence = "occ\t\x00é"
        # DOT labels render tree node labels, not occurrence IDs, so place the
        # full UTF-8/control set on the P08-admitted node label as well.
        node_label = "root\x00雪\x01é\t\n"
        document = {
            "schema_version": 1,
            "semantics": "set",
            "catalog": {"version": 1, "tables": [{"name": "Table雪", "columns": [{"name": "column", "type": "string"}]}]},
            "query": {
                "variables": [{"name": var_name, "type": "string"}],
                "atoms": [{"id": occurrence, "table": "Table雪", "terms": [{"var": var_name}]}],
                "head": [{"var": var_name}],
            },
        }
        tree = {
            "schema_version": 1, "catalog_version": 1, "semantics": "set", "root": node_label,
            "nodes": [{"id": node_label, "kind": "native", "scope": [var_name], "children": [], "occurrence": occurrence}],
        }
        case_dir = self.out / "escaped-labels"
        query_path = self.write_generated(case_dir / "query.json", document)
        tree_path = self.write_generated(case_dir / "tree.json", tree)
        native = self.invoke(
            "escaped-labels-lower-plan",
            [str(self.native_cli), "lower-plan", str(query_path), str(tree_path)],
            {"native_cli": self.native_cli, "query": query_path, "tree": tree_path}, 0, json_output=True,
        )
        plan_path = native.directory / "stdout.bin"
        report_call = self.invoke(
            "escaped-labels-explain-json", [str(self.explain_cli), str(plan_path), "--format", "json"],
            {"explain_cli": self.explain_cli, "physical_plan": plan_path,
             "schema": self.repo / PROPOSAL_DIR / "schemas/explain-report-v1.schema.json"},
            0, json_output=True,
        )
        report = report_call.parsed_json
        if not isinstance(report, dict):
            raise AssertionError("escaped-label report did not produce JSON")
        self.validate_report_schema(report, "escaped labels")
        selected = report["structure"]["selected_tree"]["nodes"][0]
        self.check(selected["label"] == node_label, "P08-admitted NUL/control/non-ASCII node label survives JSON export")
        self.check(report["query"]["occurrences"][0]["name"] == occurrence,
                   "P08-admitted NUL/control/non-ASCII occurrence survives JSON export")
        self.check("雪".encode("utf-8") in report_call.stdout and b"\\u0000" in report_call.stdout and
                   b"\\u0001" in report_call.stdout and b"\x00" not in report_call.stdout and b"\x01" not in report_call.stdout,
                   "JSON output keeps UTF-8 and escapes embedded controls")

        text = self.invoke("escaped-labels-explain-text", [str(self.explain_cli), str(plan_path), "--format", "text"],
                           {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 0)
        dot = self.invoke("escaped-labels-explain-dot", [str(self.explain_cli), str(plan_path), "--format", "dot"],
                          {"explain_cli": self.explain_cli, "physical_plan": plan_path}, 0)
        escaped_tokens = (b"\\u0000", b"\\u0001", b"\\u0009", b"\\u000a")
        for label, output in (("text", text.stdout), ("dot", dot.stdout)):
            self.check("雪".encode("utf-8") in output and "é".encode("utf-8") in output,
                       f"escaped-label {label}: valid non-ASCII remains UTF-8")
            self.check(all(token in output for token in escaped_tokens),
                       f"escaped-label {label}: controls are escaped")
            self.check(b"\x00" not in output and b"\x01" not in output and b"\x09" not in output,
                       f"escaped-label {label}: no embedded raw NUL/control bytes")
        self.check(dot.stdout.startswith(b"digraph crown {\n") and dot.stdout.endswith(b"}\n"),
                   "escaped-label DOT remains lexically bounded")
        return {"node_label": node_label, "occurrence": occurrence, "graphviz_render_parse": "not performed"}

    def run(self) -> dict[str, Any]:
        self.setup_output()
        schema_path, _ = self.verify_frozen_inputs()
        self.prepare_schema(schema_path)
        valid_cases = self.run_valid_manifest_cases()
        mutation_result = self.run_schema_mutations(valid_cases[0][2])
        certificate_result = self.run_certificate_cases(valid_cases)
        invalid_cases = self.run_invalid_cli_cases(valid_cases[0][1])
        byte_lengths = self.run_byte_limits(valid_cases[0][1])
        escaped = self.run_escaped_label_fixture()
        return {
            "status": "passed",
            "valid_manifest_cases": len(valid_cases),
            "format_exports": len(valid_cases) * 3,
            "schema_mutations": mutation_result,
            "certificate_cases": certificate_result,
            "invalid_cli_cases": invalid_cases,
            "byte_limit_output_lengths": byte_lengths,
            "escaped_label_fixture": escaped,
            "graphviz_render_parse": "not performed",
        }

    def finish(self, status: str, result: dict[str, Any] | None, error: str | None = None,
               error_traceback: str | None = None) -> None:
        if self.run_dir is None:
            return
        record = {
            "status": status,
            "result": result,
            "error": error,
            "traceback": error_traceback,
            "check_count": len(self.checks),
            "passed_checks": sum(1 for item in self.checks if item["status"] == "passed"),
            "failed_checks": sum(1 for item in self.checks if item["status"] == "failed"),
            "invocation_count": len(self.invocations),
            "input_hashes": self.hash_record,
            "checks": self.checks,
        }
        (self.out / "run-summary.json").write_bytes(json_bytes(record))
        print(json.dumps({"run_dir": str(self.out), "status": status, "result": result,
                          "check_count": record["check_count"], "invocation_count": record["invocation_count"],
                          "error": error}, ensure_ascii=False, indent=2))


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--native-cli", required=True, type=Path, help="path to the frozen native CROWN CLI")
    parser.add_argument("--explain-cli", required=True, type=Path, help="path to the pinned mode-binding EXPLAIN CLI")
    parser.add_argument("--repo", required=True, type=Path, help="repository root containing the manifest and proposal")
    parser.add_argument("--outputdir", required=True, type=Path, help="new output directory under /tmp or repo/build/verification")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    harness = Harness(args.repo, args.native_cli, args.explain_cli, args.outputdir)
    try:
        result = harness.run()
    except Exception as error:  # Preserve a machine-readable failure summary for the root-owned run.
        harness.finish("failed", None, f"{type(error).__name__}: {error}", traceback.format_exc())
        return 1
    harness.finish("passed", result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
