#!/usr/bin/env python3
"""Independent offline black-box acceptance for the frozen native EXPLAIN CLI.

The harness only launches the caller-supplied native CROWN binary and stores
every call beneath --outputdir. It does not build or edit repository sources.
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


ARTIFACT_DIR = Path(__file__).resolve().parent
NATIVE_CLI_SHA256 = "399b83154aa16c1a12e946729d60e5d5fd3c2f9844aaffac3d58468c9f56e9ff"
MANIFEST = Path("manifest.json")
SCHEMA_HASHES = {
    "report": "c4aa8c7c62e0608d7b035128a9bd9b561387c0c16491efa704d8b95b469c9f74",
    "tree": "608154cd56f807a283d4a86e58b20af1cce6605b8a77a2727ff084d7a7967335",
    "query": "b843e905e9a2a5c201847c2db8cd93fed85a836b56d6faa8d4319c70cd02979d",
    "witness": "1e2121a6c7ce98f8e68650cf1bf54733db6eec0b4a254695dbafa84c10688f7e",
}
FORMATS = ("json", "text", "dot", "tree-json")


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
    def __init__(self, repo: Path, native_cli: Path, schema_dir: Path,
                 fixture_dir: Path, outputdir: Path):
        self.repo = repo.resolve()
        self.native_cli = native_cli.resolve()
        self.schema_dir = schema_dir.resolve()
        self.fixture_dir = fixture_dir.resolve()
        self.outputdir = outputdir.resolve()
        self.run_dir: Path | None = None
        self.checks: list[dict[str, Any]] = []
        self.invocations: list[Invocation] = []
        self.hash_record: dict[str, Any] = {}
        self.schemas: dict[str, dict[str, Any]] = {}
        self.validators: dict[str, Any] = {}

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
        self.run_dir = self.outputdir / f"o07-native-explain-{stamp}-{os.getpid()}-{uuid.uuid4().hex[:8]}"
        self.run_dir.mkdir()

    @property
    def out(self) -> Path:
        if self.run_dir is None:
            raise RuntimeError("output directory is not initialized")
        return self.run_dir

    def verify_frozen_inputs(self) -> dict[str, Path]:
        readiness_path = ARTIFACT_DIR / "readiness.json"
        readiness = read_json(readiness_path)
        files = readiness.get("files")
        self.check(isinstance(files, dict) and bool(files), "test readiness has a closed file-hash map")
        actual_files: dict[str, str] = {}
        for relative, expected in sorted(files.items()):
            actual = sha256_file(ARTIFACT_DIR / relative)
            self.check(actual == expected, f"frozen test package file: {relative}")
            actual_files[relative] = actual
            if relative.startswith("fixtures/p08/"):
                external = self.fixture_dir / relative[len("fixtures/p08/"):]
                self.check(sha256_file(external) == expected, f"selected fixture copy matches package: {external.name}")
        canonical_package = json.dumps(files, sort_keys=True, separators=(",", ":")).encode("utf-8")
        package_hash = sha256_bytes(canonical_package)
        self.check(readiness.get("package_sha256") == package_hash, "canonical portable test package hash")

        schema_paths = {
            "report": self.schema_dir / "explain-report-v2.schema.json",
            "tree": self.schema_dir / "explain-tree-v2.schema.json",
            "query": self.schema_dir / "query-explain-v1.schema.json",
            "witness": self.schema_dir / "query-witness-v1.schema.json",
        }
        schema_hashes: dict[str, str] = {}
        for name, path in schema_paths.items():
            digest = sha256_file(path)
            self.check(digest == SCHEMA_HASHES[name], f"frozen {name} schema SHA-256")
            self.check(digest == files.get(f"schemas/{path.name}"),
                       f"{name} schema copy matches the self-contained package")
            schema_hashes[name] = digest

        binary_hash = sha256_file(self.native_cli)
        self.check(binary_hash == NATIVE_CLI_SHA256, "selected native CLI matches compile/link readiness binary", binary_hash)
        self.check(readiness.get("native_cli_sha256") == binary_hash,
                   "native CLI hash is pinned by test readiness")
        manifest_path = self.fixture_dir / MANIFEST
        manifest_hash = sha256_file(manifest_path)
        self.hash_record = {
            "readiness_json_sha256": sha256_file(readiness_path),
            "package_sha256": package_hash,
            "native_cli_sha256": binary_hash,
            "native_package_files": actual_files,
            "schema_sha256": schema_hashes,
            "manifest_path": str(manifest_path),
            "manifest_sha256": manifest_hash,
        }
        return schema_paths

    def prepare_schemas(self, schema_paths: dict[str, Path]) -> None:
        try:
            with warnings.catch_warnings():
                warnings.simplefilter("ignore", DeprecationWarning)
                from jsonschema import Draft202012Validator, RefResolver
        except ImportError as error:
            raise RuntimeError("Python jsonschema>=4 is needed; schema resolution is local and offline") from error

        store: dict[str, Any] = {}
        for name, path in schema_paths.items():
            schema = read_json(path)
            Draft202012Validator.check_schema(schema)
            self.schemas[name] = schema
            store[path.resolve().as_uri()] = schema
            if "$id" in schema:
                store[schema["$id"]] = schema

        def local_file(uri: str) -> Any:
            if uri not in store:
                raise RuntimeError("schema reference outside the four pinned local schemas: " + uri)
            return store[uri]

        def deny_network(uri: str) -> Any:
            raise RuntimeError("offline schema validation attempted network access: " + uri)

        for name, path in schema_paths.items():
            schema = self.schemas[name]
            resolver = RefResolver(path.resolve().as_uri(), schema, store=store,
                                   handlers={"file": local_file, "http": deny_network, "https": deny_network})
            self.validators[name] = Draft202012Validator(schema, resolver=resolver)
        self.check(set(self.validators) == {"report", "tree", "query", "witness"},
                   "four frozen Draft 2020-12 schemas load with offline-only resolution")

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
            completed = subprocess.run(argv, cwd=self.repo, stdout=subprocess.PIPE,
                                       stderr=subprocess.PIPE, check=False, timeout=timeout)
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
        (folder / "result.json").write_bytes(json_bytes({
            "stdout_bytes": len(stdout), "stdout_sha256": sha256_bytes(stdout),
            "stderr_bytes": len(stderr), "stderr_sha256": sha256_bytes(stderr),
            "json_output_requested": json_output, "parsed_json": parsed, "json_parse_error": parse_error,
        }))
        (folder / "invocation.json").write_bytes(json_bytes({
            "argv": argv, "cwd": str(self.repo), "expected_returncode": expected_rc,
            "returncode": returncode, "timed_out": returncode == 124,
        }))
        invocation = Invocation(name, folder, returncode, stdout, stderr, parsed)
        self.invocations.append(invocation)
        self.check(returncode == expected_rc, f"CLI exit status: {name}", f"expected {expected_rc}, got {returncode}")
        if json_output and expected_rc == 0:
            self.check(parsed is not None, f"CLI produced parseable JSON: {name}", parse_error or "")
        return invocation

    def generated(self, relative: str, data: Any) -> Path:
        path = self.out / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(json_bytes(data))
        return path

    def report_schema(self, report: Any, label: str) -> None:
        errors = list(self.validators["report"].iter_errors(report))
        if errors:
            first = errors[0]
            raise AssertionError(f"V2 report schema rejects {label} at {list(first.absolute_path)}: {first.message}")
        self.check(True, f"offline V2 report schema accepts {label}")
        if report.get("kind") in {"physical", "runtime", "session"}:
            self.check("native_integration_and_acceptance" not in report["open_gates"],
                       f"{label}: stale native integration gate is absent")
        if report.get("kind") == "query":
            nested = report["query_explanation"]
            self.validators["query"].validate(nested)
            self.check(True, f"standalone V1 query schema accepts {label}")

    def tree_schema(self, tree: Any, label: str) -> None:
        errors = list(self.validators["tree"].iter_errors(tree))
        if errors:
            first = errors[0]
            raise AssertionError(f"V2 tree schema rejects {label} at {list(first.absolute_path)}: {first.message}")
        self.check(True, f"offline V2 tree schema accepts {label}")
        if tree.get("kind") == "query":
            self.validators["witness"].validate(tree["witness"])
            self.check(True, f"standalone V1 witness schema accepts {label}")

    def validate_export(self, format_name: str, invocation: Invocation, label: str) -> Any:
        if format_name == "json":
            if not isinstance(invocation.parsed_json, dict):
                raise AssertionError(f"{label}: JSON export is not an object")
            self.report_schema(invocation.parsed_json, label)
            return invocation.parsed_json
        if format_name == "tree-json":
            if not isinstance(invocation.parsed_json, dict):
                raise AssertionError(f"{label}: tree-json export is not an object")
            self.tree_schema(invocation.parsed_json, label)
            return invocation.parsed_json
        text = invocation.stdout.decode("utf-8", errors="strict")
        self.check(bool(text), f"{label}: {format_name} export is nonempty")
        self.check(all(byte >= 32 or byte == 10 for byte in invocation.stdout),
                   f"{label}: {format_name} export contains no raw control bytes")
        if format_name == "dot":
            self.check(text.startswith("digraph crown {\n") and text.endswith("}\n"),
                       f"{label}: DOT has complete lexical boundaries")
        return text

    @staticmethod
    def variable_ids(document: dict[str, Any]) -> dict[str, int]:
        return {entry["name"]: index for index, entry in enumerate(document["query"]["variables"])}

    @staticmethod
    def occurrence_ids(document: dict[str, Any]) -> dict[str, int]:
        return {entry["id"]: index for index, entry in enumerate(document["query"]["atoms"])}

    def compare_tree(self, report: dict[str, Any], plan: dict[str, Any], case: dict[str, Any]) -> None:
        case_id = case["id"]
        expected = case["expected"]
        source_document = plan["source"]["document"]
        var_ids = self.variable_ids(source_document)
        occurrence_ids = self.occurrence_ids(source_document)
        raw_nodes = plan["tree"]["nodes"]
        physical_nodes = plan["nodes"]
        selected = report["structure"]["selected_tree"]
        selected_nodes = selected["nodes"]
        node_ids = {node["id"]: index for index, node in enumerate(raw_nodes)}
        layouts = {layout["layout_id"]: layout for layout in plan["layouts"]}
        parent_by_id: dict[str, str] = {}
        for node in raw_nodes:
            for child in node["children"]:
                self.check(child not in parent_by_id, f"{case_id}: actual P08 tree has at most one parent", child)
                parent_by_id[child] = node["id"]
        c_star = set(plan["verification"]["maximal_connex"])
        expected_roots = [label for label, node in expected["nodes"].items() if node["parent"] is None]
        expected_root = expected_roots[0] if len(expected_roots) == 1 else None
        actual_root_id = plan["tree"]["root"]
        expected_root_index = node_ids.get(actual_root_id) if actual_root_id is not None else None
        self.check(selected["root"] == expected_root_index, f"{case_id}: EXPLAIN root matches actual P08 tree")
        self.check(actual_root_id == expected_root, f"{case_id}: P08 root matches manifest")
        self.check(len(raw_nodes) == len(physical_nodes) == len(selected_nodes),
                   f"{case_id}: selected tree and physical node counts match P08")
        self.check(set(expected["nodes"]) == set(node_ids), f"{case_id}: manifest covers actual P08 nodes")

        for index, raw in enumerate(raw_nodes):
            label = raw["id"]
            selected_node = selected_nodes[index]
            physical = physical_nodes[index]
            fixture = expected["nodes"][label]
            parent_label = parent_by_id.get(label)
            parent_index = node_ids[parent_label] if parent_label is not None else None
            scope_ids = sorted(var_ids[name] for name in raw["scope"])
            child_ids = [node_ids[name] for name in raw["children"]]
            parent_scope = next((node["scope"] for node in raw_nodes if node["id"] == parent_label), [])
            separator_names = sorted(set(raw["scope"]) & set(parent_scope), key=var_ids.__getitem__)
            separator_ids = [var_ids[name] for name in separator_names]
            projection = physical["parent_key"]
            layout = layouts[projection["source_layout"]]
            physical_separator = [layout["fields"][field]["variable"] for field in projection["fields"]]
            occurrence = occurrence_ids[raw["occurrence"]] if raw["kind"] == "native" else None
            visible_ids = physical["visible_scope"]
            connex = index in c_star
            self.check(selected_node["id"] == index and selected_node["label"] == label,
                       f"{case_id}/{label}: V2 node ID and native label")
            self.check(selected_node["kind"] == raw["kind"] == physical["kind"],
                       f"{case_id}/{label}: native/generalized kind agrees")
            self.check(selected_node["occurrence"] == occurrence == physical["occurrence"],
                       f"{case_id}/{label}: native occurrence ID agrees")
            self.check(selected_node["scope"] == scope_ids == physical["scope"],
                       f"{case_id}/{label}: scope IDs agree")
            self.check(selected_node["children"] == child_ids == physical["children"],
                       f"{case_id}/{label}: child IDs agree")
            self.check(selected_node["separator"] == separator_ids == physical_separator,
                       f"{case_id}/{label}: separator agrees with parent scope and physical projection")
            self.check(selected_node["connex"] == connex == physical["connex"],
                       f"{case_id}/{label}: C* membership agrees with P08 verification")
            self.check(physical["parent"] == parent_index, f"{case_id}/{label}: parent index matches P08")
            self.check(visible_ids == sorted(visible_ids) and all(isinstance(value, int) for value in visible_ids),
                       f"{case_id}/{label}: P08 visible scope uses ordered numeric IDs")
            self.check(visible_ids == [var_ids[name] for name in fixture["visible"]],
                       f"{case_id}/{label}: visible scope matches fixture")
            self.check(scope_ids == [var_ids[name] for name in fixture["scope"]],
                       f"{case_id}/{label}: scope matches fixture")
            expected_parent = node_ids[fixture["parent"]] if fixture["parent"] is not None else None
            self.check(parent_index == expected_parent, f"{case_id}/{label}: parent matches fixture")
            self.check(child_ids == [node_ids[name] for name in fixture["children"]],
                       f"{case_id}/{label}: children match fixture")
            self.check(separator_ids == [var_ids[name] for name in fixture["separator"]],
                       f"{case_id}/{label}: separator matches fixture")
            self.check(connex == fixture["connex"], f"{case_id}/{label}: C* matches fixture")

    def compare_physical_report(self, report: dict[str, Any], plan: dict[str, Any], case: dict[str, Any]) -> None:
        case_id = case["id"]
        expected = case["expected"]
        identity = plan["binding"]["identity"]
        verification = plan["verification"]
        self.check(report["schema_version"] == 2 and report["artifact"] == "crown_explain" and
                   report["kind"] == "physical", f"{case_id}: V2 physical artifact identity")
        self.check(report["authority"] == "diagnostic_export_only", f"{case_id}: export remains diagnostic-only")
        self.check(report["route"] == plan["route"] == expected["route"],
                   f"{case_id}: route agrees with native P08 and fixture")
        self.check(report["identity"]["physical_sha256"] == plan["binding"]["physical_sha256"],
                   f"{case_id}: physical plan binding matches P08")
        for key in ("semantic_sha256", "output_contract_sha256", "cost_inputs_sha256", "plan_cache_sha256"):
            self.check(report["identity"][key] == identity[key], f"{case_id}: {key} matches P08")
        height = verification["native_height"]
        evidence = report["height_evidence"]
        self.check(report["structure"]["native_height"] == height == evidence["selected_height"],
                   f"{case_id}: selected and native P08 height agree")
        self.check(report["structure"]["edge_depth"] == verification["edge_depth"],
                   f"{case_id}: tree edge depth agrees with P08")
        if plan["route"] == "constant_false":
            self.check(evidence["status"] == "checked_constant_operator" and
                       evidence["source"] == "p08_checked_constant_operator" and
                       evidence["original_upper"] is None,
                       f"{case_id}: constant-false operator does not claim original CQ tree height")
        else:
            self.check(evidence["status"] == "checked_upper" and evidence["source"] == "p08_checked_upper_only" and
                       evidence["original_upper"] == height,
                       f"{case_id}: P08 plan stays checked-upper without proof")
        self.check(evidence["original_minimum"] is None and evidence["algorithm"] is None and
                   evidence["original_witness"] is None and evidence["lower_bound_claims"] is None,
                   f"{case_id}: no original minimum proof is inferred from a P08 plan")
        self.check(report["mode"]["runtime_presence"] == "compile_only" and report["mode"]["runtime"] is None,
                   f"{case_id}: physical report stays compile-only")
        self.check(report["cost"] == {"selection": "not_implemented", "statistics": "unavailable",
                                      "estimated_state": "unavailable", "global_optimality": False},
                   f"{case_id}: no cost-optimality or estimate is invented")
        self.check("native_integration_and_acceptance" not in report["open_gates"],
                   f"{case_id}: stale native integration gate is absent")
        self.check("native_integration_and_acceptance" not in " ".join(report["open_gates"]),
                   f"{case_id}: no stale gate text remains in the open-gate list")
        self.check(report["observations"]["availability"] == "unavailable" and
                   report["observations"]["current"] is None and report["observations"]["last"] is None and
                   report["observations"]["lifetime"] is None,
                   f"{case_id}: physical-only observation payload is unavailable")
        self.check(report["committed_gauges"]["availability"] == "compile_only" and
                   report["committed_gauges"]["value"] is None,
                   f"{case_id}: physical-only committed gauges are compile-only")
        registry = report["observations"]["registry"]
        self.check([item["id"] for item in registry] == list(range(len(registry))),
                   f"{case_id}: observation registry IDs are contiguous")
        names = [item["name"] for item in registry]
        self.check(len(names) == len(set(names)), f"{case_id}: observation registry names are unique")
        for descriptor in registry:
            self.check(bool(descriptor["unit"]) and bool(descriptor["scope"]) and bool(descriptor["includes"]),
                       f"{case_id}: registry unit and scopes are explicit", descriptor["name"])
        self.compare_tree(report, plan, case)

    def run_physical_families(self) -> list[dict[str, Any]]:
        manifest = read_json(self.fixture_dir / MANIFEST)
        cases = [case for case in manifest["cases"] if case["expected"]["valid"]]
        self.check(bool(cases), "lowering manifest contains valid physical plan cases")
        results: list[dict[str, Any]] = []
        for case in cases:
            case_dir = self.out / "fixtures" / safe_name(case["id"])
            case_dir.mkdir(parents=True)
            query = self.fixture_dir / case["query"]
            tree = self.fixture_dir / case["tree"]
            plan_call = self.invoke(
                f"{case['id']}-lower-plan",
                [str(self.native_cli), "lower-plan", str(query), str(tree)],
                {"native_cli": self.native_cli, "query": query, "tree": tree}, 0, json_output=True,
            )
            if not isinstance(plan_call.parsed_json, dict):
                raise AssertionError(f"{case['id']}: native lower-plan output is not a plan object")
            plan = plan_call.parsed_json
            plan_path = plan_call.directory / "stdout.bin"
            self.check(plan.get("route") == case["expected"]["route"],
                       f"{case['id']}: actual P08 plan route matches fixture")
            argv = [str(self.native_cli), "explain", "physical", str(plan_path)]
            base_inputs = {"native_cli": self.native_cli, "physical_plan": plan_path,
                           "report_schema": self.schema_dir / "explain-report-v2.schema.json"}
            report_call = self.invoke(f"{case['id']}-explain-json", argv + ["--format", "json"],
                                      base_inputs, 0, json_output=True)
            report = report_call.parsed_json
            if not isinstance(report, dict):
                raise AssertionError(f"{case['id']}: native EXPLAIN JSON is not an object")
            self.report_schema(report, case["id"])
            self.compare_physical_report(report, plan, case)

            text_call = self.invoke(f"{case['id']}-explain-text", argv + ["--format", "text"], base_inputs, 0)
            text = self.validate_export("text", text_call, f"{case['id']} human export")
            self.check("CROWN EXPLAIN v2" in text and "diagnostic" in text,
                       f"{case['id']}: human export labels diagnostic scope")
            self.check("native_integration_and_acceptance" not in text,
                       f"{case['id']}: human export omits stale native integration gate")
            self.check(f"Height: {report['structure']['native_height']}" in text,
                       f"{case['id']}: human height matches JSON")

            dot_call = self.invoke(f"{case['id']}-explain-dot", argv + ["--format", "dot"], base_inputs, 0)
            dot = self.validate_export("dot", dot_call, f"{case['id']} DOT export")
            declared_nodes = re.findall(r"^\s*n[0-9]+\s+\[", dot, flags=re.MULTILINE)
            self.check(len(declared_nodes) == len(report["structure"]["selected_tree"]["nodes"]),
                       f"{case['id']}: DOT node count matches selected tree")
            if not report["structure"]["selected_tree"]["nodes"]:
                self.check("constant [shape=plaintext,label=" in dot,
                           f"{case['id']}: empty-operator route has explicit DOT marker")

            tree_call = self.invoke(f"{case['id']}-explain-tree-json", argv + ["--format", "tree-json"],
                                    {**base_inputs, "tree_schema": self.schema_dir / "explain-tree-v2.schema.json"},
                                    0, json_output=True)
            tree_export = tree_call.parsed_json
            if not isinstance(tree_export, dict):
                raise AssertionError(f"{case['id']}: native tree-json is not an object")
            self.tree_schema(tree_export, f"{case['id']} physical tree")
            self.check(tree_export["kind"] == "physical" and
                       tree_export["tree"] == report["structure"]["selected_tree"] and
                       tree_export["native_height"] == report["structure"]["native_height"],
                       f"{case['id']}: tree-json agrees with report tree and height")
            results.append({"case": case, "plan_path": plan_path, "plan": plan, "report": report,
                            "base_argv": argv, "base_inputs": base_inputs, "query_path": query})
        self.hash_record["valid_physical_fixture_count"] = len(results)
        return results

    def schema_mutations(self, physical: dict[str, Any], session: dict[str, Any], query: dict[str, Any],
                         witness: dict[str, Any] | None) -> dict[str, int]:
        validator = self.validators["report"]
        mutations: list[tuple[str, dict[str, Any]]] = []

        def mutate(base: dict[str, Any], label: str, path: tuple[str | int, ...], value: Any) -> None:
            result = copy.deepcopy(base)
            target: Any = result
            for key in path[:-1]:
                target = target[key]
            target[path[-1]] = value
            mutations.append((label, result))

        mutate(physical, "wrong schema version", ("schema_version",), 3)
        mutate(physical, "wrong authority", ("authority",), "proof_input")
        mutate(physical, "wrong route enum", ("route",), "global_optimum")
        mutate(physical, "wrong height-status enum", ("height_evidence", "status"), "minimum_without_proof")
        mutate(physical, "wrong runtime-presence enum", ("mode", "runtime_presence"), "estimated")
        mutate(physical, "unknown top-level field", ("surprise_claim",), True)
        mutate(physical, "extra global cost claim", ("cost", "global_cost_optimal"), True)
        owner_type = copy.deepcopy(session)
        owner_type["mode"]["runtime"]["owner"] = "owner-zero"
        mutations.append(("runtime owner ID with string type", owner_type))
        for label, document in mutations:
            self.check(not validator.is_valid(document), f"V2 schema rejects {label}")

        mismatched = copy.deepcopy(physical)
        mismatched["height_evidence"]["selected_height"] += 1
        self.check(validator.is_valid(mismatched),
                   "schema limitation recorded: cross-field height equality requires semantic checking")

        observation_mutations = 0
        summary_key = "last" if isinstance(session["observations"]["last"], dict) else "current"
        observed_summary = session["observations"][summary_key]
        if not isinstance(observed_summary, dict) or not observed_summary["values"]:
            raise AssertionError("successful owned-stream report did not retain an observation summary")
        available_index = next((index for index, value in enumerate(observed_summary["values"])
                                if value["availability"] == "available"), None)
        if available_index is None:
            raise AssertionError("counters-mode session contains no available observation metric")
        descriptor = session["observations"]["registry"][available_index]
        malformed_metric = copy.deepcopy(session)
        metric = malformed_metric["observations"][summary_key]["values"][available_index]
        metric["availability"] = "unavailable"
        self.check(not validator.is_valid(malformed_metric),
                   "V2 schema rejects unavailable observation metric with a numeric payload")
        observation_mutations += 1
        bad_enum = copy.deepcopy(session)
        bad_enum["observations"][summary_key]["values"][available_index]["availability"] = "estimated"
        self.check(not validator.is_valid(bad_enum), "V2 schema rejects unknown observation availability enum")
        observation_mutations += 1
        bad_unit = copy.deepcopy(session)
        bad_unit["observations"]["registry"][available_index]["unit"] = "parsecs"
        self.check(not validator.is_valid(bad_unit), "V2 schema rejects unknown metric unit")
        observation_mutations += 1
        bad_owner = copy.deepcopy(session)
        bad_owner["observations"]["current_configuration"]["support_owner"] = "owner-zero"
        self.check(not validator.is_valid(bad_owner), "V2 schema rejects nonnumeric support-owner identifier")
        observation_mutations += 1
        bad_runtime_owner = copy.deepcopy(session)
        bad_runtime_owner["mode"]["runtime"]["owner"] = "owner-zero"
        self.check(not validator.is_valid(bad_runtime_owner), "V2 schema rejects runtime owner ID with wrong type")
        observation_mutations += 1
        self.check(descriptor["id"] == observed_summary["values"][available_index]["id"],
                   "actual session metric values bind to contiguous registry IDs")
        for value in observed_summary["values"]:
            self.check((value["availability"] == "available" and isinstance(value["value"], int) and
                        isinstance(value["saturated"], bool)) or
                       (value["availability"] in {"unavailable", "disabled"} and
                        value["value"] is None and value["saturated"] is None),
                       "actual report exposes unavailable metric numbers only as null", str(value["id"]))

        query_mutations = 0
        q_validator = self.validators["query"]
        q_mutant = copy.deepcopy(query)
        q_mutant["height"]["status"] = "unsupported_status"
        self.check(not q_validator.is_valid(q_mutant), "standalone V1 query schema rejects invalid height enum")
        query_mutations += 1
        q_mutant = copy.deepcopy(query)
        q_mutant["unexpected"] = True
        self.check(not q_validator.is_valid(q_mutant), "standalone V1 query schema rejects unknown fields")
        query_mutations += 1
        witness_mutations = 0
        if witness is not None:
            w_validator = self.validators["witness"]
            w_mutant = copy.deepcopy(witness)
            w_mutant["binding"]["catalog"]["version"] = -1
            self.check(not w_validator.is_valid(w_mutant), "standalone V1 witness schema rejects malformed binding")
            witness_mutations += 1
            w_mutant = copy.deepcopy(witness)
            w_mutant["extra"] = 1
            self.check(not w_validator.is_valid(w_mutant), "standalone V1 witness schema rejects unknown fields")
            witness_mutations += 1
        return {"v2_report_rejected": len(mutations) + observation_mutations,
                "query_v1_rejected": query_mutations,
                "witness_v1_rejected": witness_mutations, "cross_field_schema_limitation_accepted": 1}

    def proof_cases(self, fixture: dict[str, Any], other_fixture: dict[str, Any]) -> dict[str, Any]:
        query = fixture["query_path"]
        oracle = self.invoke("matching-tree-oracle",
                             [str(self.native_cli), "tree-oracle", str(query)],
                             {"native_cli": self.native_cli, "query": query}, 0, json_output=True)
        if not isinstance(oracle.parsed_json, dict) or oracle.parsed_json.get("certificate") is None:
            raise AssertionError("native tree-oracle did not return a certificate")
        certificate = self.generated("certificates/matching.json", oracle.parsed_json["certificate"])
        args = fixture["base_argv"] + ["--format", "json", "--certificate", str(certificate), "--proof-work", "10000000"]
        proved = self.invoke("physical-matching-certificate", args,
                             {**fixture["base_inputs"], "certificate": certificate}, 0, json_output=True)
        report = proved.parsed_json
        if not isinstance(report, dict):
            raise AssertionError("matching certificate did not produce a report")
        self.report_schema(report, "physical matching certificate")
        self.check(report["height_evidence"]["status"] == "verified_original_minimum",
                   "exact matching P06 certificate proves original minimum")
        self.check(report["height_evidence"]["original_minimum"] ==
                   report["height_evidence"]["selected_height"] == report["structure"]["native_height"],
                   "matching certificate minimum binds to checked native height")

        other_query = other_fixture["query_path"]
        wrong_oracle = self.invoke("wrong-query-tree-oracle",
                                   [str(self.native_cli), "tree-oracle", str(other_query)],
                                   {"native_cli": self.native_cli, "query": other_query}, 0, json_output=True)
        wrong_cert = self.generated("certificates/wrong-query.json", wrong_oracle.parsed_json["certificate"])
        wrong_query = self.invoke("wrong-query-certificate", fixture["base_argv"] +
                                  ["--format", "json", "--certificate", str(wrong_cert), "--proof-work", "10000000"],
                                  {**fixture["base_inputs"], "certificate": wrong_cert}, 1)
        self.check(wrong_query.stdout == b"", "wrong-query certificate cannot emit partial authority")

        wrong_height_data = copy.deepcopy(oracle.parsed_json["certificate"])
        wrong_height_data["minimum_height"] += 1
        wrong_height = self.generated("certificates/wrong-height.json", wrong_height_data)
        wrong_height_call = self.invoke("wrong-height-certificate", fixture["base_argv"] +
                                        ["--format", "json", "--certificate", str(wrong_height), "--proof-work", "10000000"],
                                        {**fixture["base_inputs"], "certificate": wrong_height}, 1)
        self.check(wrong_height_call.stdout == b"", "wrong-height certificate cannot emit partial authority")

        corrupt_data = copy.deepcopy(oracle.parsed_json["certificate"])
        if corrupt_data.get("lower_bounds"):
            bound = corrupt_data["lower_bounds"][0].get("bound")
            corrupt_data["lower_bounds"][0]["bound"] = (bound if isinstance(bound, int) else 0) + 1000000
        else:
            corrupt_data["algorithm"] = "corrupted"
        corrupt = self.generated("certificates/corrupted.json", corrupt_data)
        corrupt_call = self.invoke("corrupted-certificate", fixture["base_argv"] +
                                   ["--format", "json", "--certificate", str(corrupt), "--proof-work", "10000000"],
                                   {**fixture["base_inputs"], "certificate": corrupt}, 1)
        self.check(corrupt_call.stdout == b"", "corrupted certificate cannot emit partial authority")

        orphan = self.invoke("orphan-proof-work", fixture["base_argv"] +
                             ["--format", "json", "--proof-work", "10"], fixture["base_inputs"], 2)
        self.check(orphan.stdout == b"", "--proof-work without --certificate is a usage error with empty stdout")
        return {"matching": "verified_original_minimum", "wrong_query": "rejected",
                "wrong_height": "rejected", "corrupted": "rejected", "orphan_proof_work": "usage_empty_stdout"}

    def session_input(self, plan: dict[str, Any]) -> Path:
        source = plan["source"]["document"]
        catalog = source["catalog"]
        payload_tables = []
        for table in catalog["tables"]:
            columns = []
            for column in table["columns"]:
                value: dict[str, Any] = {}
                if column["type"] == "string":
                    value["collation"] = column.get("collation", "binary")
                if column.get("decimal") is not None:
                    value["decimal"] = column["decimal"]
                value["name"] = column["name"]
                value["nullable"] = column.get("nullable", True)
                value["type"] = column["type"]
                columns.append(value)
            constraints = []
            for constraint in table.get("constraints", []):
                item = {"columns": constraint["columns"], "kind": constraint["kind"], "name": constraint["name"]}
                if "references" in constraint:
                    item["references"] = constraint["references"]
                item["status"] = constraint.get("status", "untrusted")
                constraints.append(item)
            statistics = {"distinct_counts": table.get("statistics", {}).get("distinct_counts", [])}
            if table.get("statistics", {}).get("row_count") is not None:
                statistics["row_count"] = table["statistics"]["row_count"]
            payload_tables.append({"columns": columns, "constraints": constraints,
                                   "key_hints": table.get("key_hints", []), "name": table["name"],
                                   "source_schema_version": table.get("source_schema_version", 1),
                                   "statistics": statistics})
        canonical = {"catalog": {"tables": payload_tables, "version": catalog["version"]}}
        catalog_fingerprint = sha256_bytes(json.dumps(canonical, ensure_ascii=False, separators=(",", ":")).encode("utf-8"))
        table = catalog["tables"][0]
        values: list[Any] = []
        for column in table["columns"]:
            kind = column["type"]
            values.append({"int64": 7, "string": "alpha", "bool": True, "date": "2024-02-29", "decimal": "1.00"}[kind])
        event = {
            "catalog_sha256": catalog_fingerprint,
            "catalog_version": catalog["version"],
            "operation": "insert",
            "schema_version": 1,
            "sequence": 1,
            "source_schema_version": table.get("source_schema_version", 1),
            "table": table["name"],
            "values": values,
            "version": 1,
        }
        path = self.out / "session" / "events.jsonl"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(json.dumps(event, ensure_ascii=False, separators=(",", ":")).encode("utf-8") + b"\n")
        return path

    def run_runtime_and_sessions(self, fixture: dict[str, Any]) -> dict[str, Any]:
        plan = fixture["plan_path"]
        physical_args = [str(self.native_cli), "explain", "runtime", str(plan), "--format", "json",
                         "--mode", "delta", "--observe", "counters", "--live", "incremental",
                         "--completion", "ordered_replay", "--view", "core", "--work-limit", "17",
                         "--spool-rows", "23", "--run-label", "run-α", "--adapter-label", "jsonl",
                         "--codec-label", "utf8", "--sink-label", "test"]
        runtime_call = self.invoke("runtime-owner-configuration", physical_args,
                                   {"native_cli": self.native_cli, "physical_plan": plan}, 0, json_output=True)
        runtime = runtime_call.parsed_json
        if not isinstance(runtime, dict):
            raise AssertionError("runtime report is not an object")
        self.report_schema(runtime, "runtime owner report")
        self.check(runtime["kind"] == "runtime" and runtime["mode"]["runtime_presence"] == "live",
                   "runtime command captures a live owner")
        current = runtime["mode"]["runtime"]
        self.check(current["mode"] == "delta" and current["observation"] == "counters" and
                   current["live_maintenance"] == "incremental" and
                   current["requested_completion"] == "ordered_replay" and current["result_view"] == "core",
                   "runtime report preserves requested mode/live/completion/view/observation identifiers")
        self.check(runtime["run_context"]["current_declared_benchmark"]["run"] == "run-α",
                   "runtime report preserves caller-declared unmeasured label")
        configuration = runtime["observations"]["current_configuration"]
        self.check(configuration["support_owner"] == current["owner"],
                   "live runtime and observation configuration bind the same owner ID")
        requested = configuration["requested_options"]
        self.check(requested["work_limit"] == 17 and requested["mode"] == "delta" and
                   requested["live_maintenance"] == "incremental" and requested["completion"] == "ordered_replay" and
                   requested["view"] == "core",
                   "runtime report preserves complete requested mode/view/limit configuration")

        off_args = [str(self.native_cli), "explain", "runtime", str(plan), "--format", "json",
                    "--mode", "maintenance", "--observe", "off", "--live", "eager",
                    "--completion", "anchored", "--view", "core"]
        off_call = self.invoke("runtime-observation-off", off_args,
                               {"native_cli": self.native_cli, "physical_plan": plan}, 0, json_output=True)
        off = off_call.parsed_json
        self.report_schema(off, "runtime observation-off report")
        self.check(off["mode"]["runtime"]["requested_initial_mode"] == "maintenance" and
                   off["mode"]["runtime"]["live_maintenance"] == "eager" and
                   off["mode"]["runtime"]["resolved_completion"] == "anchored" and
                   off["mode"]["runtime"]["observation"] == "off",
                   "runtime report exposes explicit off/maintenance/eager/anchored configuration")
        self.check(off["observations"]["availability"] == "disabled" and
                   off["observations"]["lifetime"] is None,
                   "explicit observation-off is distinct from default timed collection")

        default_call = self.invoke("runtime-default-observation",
                                    [str(self.native_cli), "explain", "runtime", str(plan), "--format", "json"],
                                    {"native_cli": self.native_cli, "physical_plan": plan}, 0, json_output=True)
        default_report = default_call.parsed_json
        self.report_schema(default_report, "runtime default-observation report")
        self.check(default_report["mode"]["runtime"]["observation"] == "timed",
                   "omitting --observe preserves the native timed observation default")

        event = self.session_input(fixture["plan"])
        session_prefix = [str(self.native_cli), "explain", "session", str(plan), "--format", "json",
                          "--input", str(event), "--input-format", "jsonl", "--events", "1",
                          "--mode", "delta", "--observe", "counters", "--live", "incremental",
                          "--completion", "ordered_replay", "--view", "core"]
        session_inputs = {"native_cli": self.native_cli, "physical_plan": plan, "events": event}
        pending = self.invoke("session-pending", session_prefix + ["--steps", "0", "--consume", "retain",
                                   "--lifecycle", "preserve"], session_inputs, 0, json_output=True)
        pending_report = pending.parsed_json
        self.report_schema(pending_report, "pending owned-stream session")
        self.check(pending_report["kind"] == "session" and
                   pending_report["session"]["phase"] in {"pending", "paused_pending"} and
                   pending_report["session"]["pending_sequence"] == 1,
                   "zero-step session report retains its real pending input record")
        context = pending_report["run_context"]["session"]
        self.check(context["input_kind"] == "owned_stream" and
                   context["wire_format_scope"] == "applied_to_owned_stream" and
                   context["input_options"]["format"] == "jsonl",
                   "pending report binds actual owned-stream and JSONL input configuration")

        completed_reports: dict[str, dict[str, Any]] = {}
        for disposition in ("retain", "discard", "transfer"):
            call = self.invoke(f"session-{disposition}-preserve", session_prefix +
                               ["--steps", "1000000", "--consume", disposition, "--lifecycle", "preserve"],
                               session_inputs, 0, json_output=True)
            report = call.parsed_json
            self.report_schema(report, f"session {disposition} report")
            self.check(report["kind"] == "session" and report["session"]["committed_sequence"] == 1,
                       f"session {disposition}: one real input event is committed")
            self.check(report["mode"]["runtime_presence"] == "live" and
                       report["session"]["state"] not in {"stopped", "dropped"},
                       f"session {disposition}: preserve lifecycle retains the live owner")
            self.check(report["run_context"]["session"]["input_kind"] == "owned_stream",
                       f"session {disposition}: session report retains input owner binding")
            output = report["run_context"]["last_attempt"]["output"]
            self.check(isinstance(output, dict), f"session {disposition}: output action snapshot exists")
            if disposition == "retain":
                self.check(report["session"]["output_remaining"] >= 1 and output["initial_retention"] == "retain",
                           "retain disposition keeps output owned by session")
            elif disposition == "discard":
                self.check(output["discard_drain_requested"] and not output["transferred"],
                           "discard disposition records an actual drain without transfer")
            else:
                self.check(output["transferred"], "transfer disposition records actual output transfer")
            completed_reports[disposition] = report

        for lifecycle, expected_state in (("stop", "stopped"), ("drop", "dropped")):
            call = self.invoke(f"session-discard-{lifecycle}", session_prefix +
                               ["--steps", "1000000", "--consume", "discard", "--lifecycle", lifecycle],
                               session_inputs, 0, json_output=True)
            report = call.parsed_json
            self.report_schema(report, f"session {lifecycle} report")
            self.check(report["session"]["state"] == expected_state,
                       f"session lifecycle {lifecycle} is visible in owning-session status")
            expected_presence = "stopped_retained" if lifecycle == "stop" else "released"
            self.check(report["mode"]["runtime_presence"] == expected_presence,
                       f"session lifecycle {lifecycle} is reflected in runtime presence")

        sample = completed_reports["discard"]
        summary_key = "last" if isinstance(sample["observations"]["last"], dict) else "current"
        summary = sample["observations"][summary_key]
        if not isinstance(summary, dict):
            raise AssertionError("successful counter-mode session omitted its actual observation summary")
        self.check(sample["observations"]["availability"] == "available" and
                   sample["observations"]["lifetime"]["commits"] == 1,
                   "successful wire event produces a real committed observation summary")
        for value in summary["values"]:
            self.check((value["availability"] == "available" and isinstance(value["value"], int) and
                        isinstance(value["saturated"], bool)) or
                       (value["availability"] in {"unavailable", "disabled"} and
                        value["value"] is None and value["saturated"] is None),
                       "live report emits numeric values only for available metrics", str(value["id"]))
        return {"runtime_reports": 3, "session_pending_reports": 1,
                "session_dispositions": sorted(completed_reports), "session_lifecycles": ["preserve", "stop", "drop"],
                "events_sha256": sha256_file(event), "byte_test_session_report": completed_reports["discard"]}

    def triangle_infeasible(self) -> Path:
        tables = [{"name": f"T{i}", "columns": [{"name": "a", "type": "int64"},
                   {"name": "b", "type": "int64"}]} for i in range(3)]
        document = {"schema_version": 1, "semantics": "set", "catalog": {"version": 1, "tables": tables},
                    "query": {"variables": [{"name": name, "type": "int64"} for name in ("x", "y", "z")],
                              "atoms": [{"id": "xy", "table": "T0", "terms": [{"var": "x"}, {"var": "y"}]},
                                        {"id": "yz", "table": "T1", "terms": [{"var": "y"}, {"var": "z"}]},
                                        {"id": "xz", "table": "T2", "terms": [{"var": "x"}, {"var": "z"}]}],
                              "head": [{"var": name} for name in ("x", "y", "z")]}}
        return self.generated("query/triangle-full-head-infeasible.cq.json", document)

    def run_query_forms(self, fixture: dict[str, Any], progress_fixture: dict[str, Any]) -> dict[str, Any]:
        query_path = fixture["query_path"]
        inputs = {"native_cli": self.native_cli, "query_document": query_path,
                  "report_schema": self.schema_dir / "explain-report-v2.schema.json"}
        query_call = self.invoke("query-admitted", [str(self.native_cli), "explain", "query", str(query_path),
                                  "--work", "0", "--format", "json"], inputs, 0, json_output=True)
        admitted = query_call.parsed_json
        self.report_schema(admitted, "query admitted report")
        self.check(admitted["kind"] == "query" and admitted["query_explanation"]["source"] == "exact_search",
                   "query command reports its actual exact-search owner")
        self.check(admitted["query_explanation"]["height"]["status"] in {"unknown", "owner_checked_upper_unpublished"},
                   "zero-work admitted query does not claim a verified minimum")

        progress_path = progress_fixture["query_path"]
        progress_inputs = {"native_cli": self.native_cli, "query_document": progress_path,
                           "report_schema": self.schema_dir / "explain-report-v2.schema.json"}
        progress_call = self.invoke("progress-partial", [str(self.native_cli), "explain", "progress", str(progress_path),
                                     "--work", "1", "--format", "json"], progress_inputs, 0, json_output=True)
        partial = progress_call.parsed_json
        self.report_schema(partial, "query progress report")
        search = partial["query_explanation"]["search"]
        self.check(search is not None and search["result_kind"] == "unfinished" and not search["producer_complete"],
                   "progress form exposes a genuine partial search owner")

        optimum_call = self.invoke("query-optimum", [str(self.native_cli), "explain", "query", str(query_path),
                                    "--work", "10000000", "--format", "json"], inputs, 0, json_output=True)
        optimum = optimum_call.parsed_json
        self.report_schema(optimum, "query optimum report")
        qopt = optimum["query_explanation"]
        self.check(qopt["height"]["status"] == "verified_optimum" and
                   qopt["height"]["minimum_proven"] and qopt["witness"] is not None and
                   qopt["certificate"] is not None,
                   "completed exact search publishes only its typed checked original-query optimum")

        infeasible_path = self.triangle_infeasible()
        infeasible_inputs = {"native_cli": self.native_cli, "query_document": infeasible_path}
        infeasible_call = self.invoke("query-verified-infeasible", [str(self.native_cli), "explain", "query",
                                           str(infeasible_path), "--work", "10000000", "--format", "json"],
                                      infeasible_inputs, 0, json_output=True)
        impossible = infeasible_call.parsed_json
        self.report_schema(impossible, "verified-infeasible query report")
        qbad = impossible["query_explanation"]
        self.check(qbad["height"]["status"] == "verified_infeasible" and
                   qbad["height"]["infeasible_proven"] and qbad["certificate"] is not None and
                   qbad["witness"] is None,
                   "cyclic full-head fixture produces checked empty-family infeasibility")

        oracle_call = self.invoke("query-replay-tree-oracle", [str(self.native_cli), "tree-oracle", str(query_path)],
                                  {"native_cli": self.native_cli, "query_document": query_path}, 0, json_output=True)
        oracle = oracle_call.parsed_json
        certificate = self.generated("query/replay-certificate.json", oracle["certificate"])
        replay_inputs = {"native_cli": self.native_cli, "query_document": query_path, "certificate": certificate}
        replay_call = self.invoke("query-certificate-replay", [str(self.native_cli), "explain", "replay",
                                       str(query_path), "--certificate", str(certificate), "--work", "10000000",
                                       "--format", "json"], replay_inputs, 0, json_output=True)
        replay = replay_call.parsed_json
        self.report_schema(replay, "query certificate replay")
        replay_body = replay["query_explanation"]
        self.check(replay_body["source"] == "certificate_replay" and
                   replay_body["height"]["status"] == "verified_optimum" and
                   replay_body["certificate"] is not None,
                   "replay command exposes independently checked certificate authority")

        return {"admitted": admitted, "partial": partial, "optimum": optimum, "infeasible": impossible,
                "replay": replay, "fixture": query_path, "infeasible_fixture": infeasible_path}

    def invalid_cli_cases(self, fixture: dict[str, Any]) -> int:
        plan = fixture["plan_path"]
        malformed = self.out / "invalid/malformed-plan.json"
        malformed.parent.mkdir(parents=True, exist_ok=True)
        malformed.write_bytes(b"{\"schema_version\":")
        missing = self.out / "invalid/missing-plan.json"
        base = [str(self.native_cli), "explain", "physical", str(plan)]
        good_inputs = {"native_cli": self.native_cli, "physical_plan": plan}
        cases = [
            ("unknown-format", base + ["--format", "xml"], good_inputs, 2),
            ("unknown-flag", base + ["--mystery", "value"], good_inputs, 2),
            ("duplicate-format", base + ["--format", "json", "--format", "dot"], good_inputs, 2),
            ("dangling-option", base + ["--max-bytes"], good_inputs, 2),
            ("invalid-byte-limit", base + ["--max-bytes", "not-a-number"], good_inputs, 2),
            ("inapplicable-runtime-option", base + ["--mode", "delta"], good_inputs, 2),
            ("missing-plan", [str(self.native_cli), "explain", "physical", str(missing), "--format", "json"],
             {"native_cli": self.native_cli, "physical_plan": missing}, 1),
            ("malformed-plan", [str(self.native_cli), "explain", "physical", str(malformed), "--format", "json"],
             {"native_cli": self.native_cli, "physical_plan": malformed}, 1),
        ]
        for name, argv, inputs, expected in cases:
            call = self.invoke(name, argv, inputs, expected)
            self.check(call.stdout == b"", f"invalid CLI invocation has empty stdout: {name}")
        return len(cases)

    def format_byte_limits(self, artifacts: dict[str, tuple[list[str] | dict[str, list[str]],
                                                          dict[str, Path], dict[str, Any] | None]]) -> dict[str, Any]:
        result: dict[str, Any] = {}
        for artifact_name, (prefix, inputs, report) in artifacts.items():
            lengths: dict[str, int] = {}
            for fmt in FORMATS:
                selected_prefix = prefix[fmt] if isinstance(prefix, dict) else prefix
                base = selected_prefix + ["--format", fmt]
                baseline = self.invoke(f"{artifact_name}-{fmt}-bytes-baseline", base, inputs, 0,
                                       json_output=fmt in {"json", "tree-json"})
                if fmt in {"json", "tree-json"}:
                    self.validate_export(fmt, baseline, f"{artifact_name} {fmt} byte baseline")
                length = len(baseline.stdout)
                self.check(length > 0, f"{artifact_name}/{fmt}: baseline encoding is nonempty")
                exact = self.invoke(f"{artifact_name}-{fmt}-bytes-exact", base + ["--max-bytes", str(length)],
                                    inputs, 0, json_output=fmt in {"json", "tree-json"})
                self.check(len(exact.stdout) <= length, f"{artifact_name}/{fmt}: exact byte ceiling accepts output")
                below = self.invoke(f"{artifact_name}-{fmt}-bytes-minus-one", base +
                                    ["--max-bytes", str(length - 1)], inputs, 4)
                self.check(below.stdout == b"", f"{artifact_name}/{fmt}: N-1 ceiling has no partial output")
                zero = self.invoke(f"{artifact_name}-{fmt}-bytes-zero", base + ["--max-bytes", "0"], inputs, 4)
                self.check(zero.stdout == b"", f"{artifact_name}/{fmt}: zero ceiling has no partial output")
                lengths[fmt] = length
            result[artifact_name] = lengths
        return result

    def escaped_label_fixture(self) -> dict[str, Any]:
        variable = "v\x00雪\x01"
        occurrence = "occ\t\x00é"
        node_label = "root\x00雪\x01é\t\n"
        document = {"schema_version": 1, "semantics": "set",
                    "catalog": {"version": 1, "tables": [{"name": "Table雪",
                      "columns": [{"name": "column", "type": "string"}]}]},
                    "query": {"variables": [{"name": variable, "type": "string"}],
                              "atoms": [{"id": occurrence, "table": "Table雪", "terms": [{"var": variable}]}],
                              "head": [{"var": variable}]}}
        tree = {"schema_version": 1, "catalog_version": 1, "semantics": "set", "root": node_label,
                "nodes": [{"id": node_label, "kind": "native", "scope": [variable],
                           "children": [], "occurrence": occurrence}]}
        query_path = self.generated("escaped/query.json", document)
        tree_path = self.generated("escaped/tree.json", tree)
        native = self.invoke("escaped-labels-lower-plan", [str(self.native_cli), "lower-plan",
                               str(query_path), str(tree_path)],
                             {"native_cli": self.native_cli, "query": query_path, "tree": tree_path},
                             0, json_output=True)
        plan_path = native.directory / "stdout.bin"
        prefix = [str(self.native_cli), "explain", "physical", str(plan_path)]
        inputs = {"native_cli": self.native_cli, "physical_plan": plan_path}
        json_call = self.invoke("escaped-labels-json", prefix + ["--format", "json"], inputs, 0, json_output=True)
        report = json_call.parsed_json
        self.report_schema(report, "escaped label report")
        self.check(report["structure"]["selected_tree"]["nodes"][0]["label"] == node_label,
                   "P08-admitted NUL/control/non-ASCII node label survives JSON export")
        self.check(report["query"]["occurrences"][0]["name"] == occurrence,
                   "P08-admitted NUL/control/non-ASCII occurrence survives JSON export")
        self.check("雪".encode("utf-8") in json_call.stdout and b"\\u0000" in json_call.stdout and
                   b"\\u0001" in json_call.stdout and b"\x00" not in json_call.stdout and b"\x01" not in json_call.stdout,
                   "JSON keeps valid UTF-8 while escaping embedded controls")
        for fmt in ("text", "dot"):
            call = self.invoke(f"escaped-labels-{fmt}", prefix + ["--format", fmt], inputs, 0)
            self.validate_export(fmt, call, f"escaped label {fmt}")
            for byte in ("雪".encode("utf-8"), "é".encode("utf-8"), b"\\u0000", b"\\u0001", b"\\u0009", b"\\u000a"):
                self.check(byte in call.stdout, f"escaped label {fmt}: expected UTF-8 or escaped token {byte!r}")
            self.check(b"\x00" not in call.stdout and b"\x01" not in call.stdout and b"\x09" not in call.stdout,
                       f"escaped label {fmt}: no raw embedded controls")
        tree_call = self.invoke("escaped-labels-tree-json", prefix + ["--format", "tree-json"],
                                {**inputs, "tree_schema": self.schema_dir / "explain-tree-v2.schema.json"},
                                0, json_output=True)
        self.tree_schema(tree_call.parsed_json, "escaped labels tree export")
        self.check(tree_call.parsed_json["tree"]["nodes"][0]["label"] == node_label,
                   "tree-json preserves P08-admitted node label")
        return {"node_label": node_label, "occurrence": occurrence, "graphviz_render_parse": "not performed"}

    def run(self) -> dict[str, Any]:
        self.setup_output()
        schema_paths = self.verify_frozen_inputs()
        self.prepare_schemas(schema_paths)
        cases = self.run_physical_families()
        progress_case = next((case for case in cases if case["case"]["id"] == "generalized_root_eight_children"),
                             cases[-1])
        runtime_session = self.run_runtime_and_sessions(cases[0])
        query_result = self.run_query_forms(cases[0], progress_case)
        query_body = query_result["optimum"]["query_explanation"]
        query_witness = query_body["witness"]
        self.validators["query"].validate(query_body)
        self.check(True, "standalone V1 query schema accepts emitted exact-search optimum")
        if query_witness is not None:
            self.validators["witness"].validate(query_witness)
            self.check(True, "standalone V1 witness schema accepts emitted optimum witness")

        mutations = self.schema_mutations(cases[0]["report"], runtime_session["byte_test_session_report"],
                                          query_body, query_witness)
        proof = self.proof_cases(cases[0], cases[1])
        invalid_count = self.invalid_cli_cases(cases[0])
        session_report = runtime_session["byte_test_session_report"]
        session_plan = cases[0]["plan_path"]
        session_args = [str(self.native_cli), "explain", "session", str(session_plan), "--input",
                        str(self.out / "session/events.jsonl"), "--input-format", "jsonl", "--events", "1",
                        "--steps", "1000000", "--consume", "discard", "--lifecycle", "preserve",
                        "--mode", "delta", "--observe", "off", "--live", "incremental",
                        "--completion", "ordered_replay", "--view", "core"]
        query_zero_args = [str(self.native_cli), "explain", "query", str(cases[0]["query_path"]), "--work", "0"]
        query_complete_args = [str(self.native_cli), "explain", "query", str(cases[0]["query_path"]),
                               "--work", "10000000"]
        runtime_args = [str(self.native_cli), "explain", "runtime", str(session_plan), "--mode", "delta",
                        "--observe", "off", "--live", "incremental", "--completion", "ordered_replay", "--view", "core"]
        byte_limits = self.format_byte_limits({
            "physical": (cases[0]["base_argv"], cases[0]["base_inputs"], cases[0]["report"]),
            "runtime": (runtime_args, {"native_cli": self.native_cli, "physical_plan": session_plan}, None),
            "session": (session_args, {"native_cli": self.native_cli, "physical_plan": session_plan,
                                       "events": self.out / "session/events.jsonl"}, session_report),
            "query": ({"json": query_zero_args, "text": query_zero_args,
                       "dot": query_complete_args, "tree-json": query_complete_args},
                      {"native_cli": self.native_cli, "query_document": cases[0]["query_path"]}, query_result["optimum"]),
        })
        escaped = self.escaped_label_fixture()
        return {
            "status": "passed", "physical_fixture_count": len(cases),
            "physical_format_exports": len(cases) * len(FORMATS),
            "runtime_session": {k: v for k, v in runtime_session.items() if k != "byte_test_session_report"},
            "query_states": {key: query_result[key]["query_explanation"]["height"]["status"]
                             for key in ("admitted", "partial", "optimum", "infeasible", "replay")},
            "proof_binding": proof, "schema_mutations": mutations,
            "invalid_cli_cases": invalid_count, "byte_limit_outputs": byte_limits,
            "escaped_label_fixture": escaped,
            "graphviz_render_parse": "not performed; DOT checks are lexical only",
        }

    def finish(self, status: str, result: dict[str, Any] | None, error: str | None = None,
               error_traceback: str | None = None) -> None:
        if self.run_dir is None:
            return
        record = {
            "status": status, "result": result, "error": error, "traceback": error_traceback,
            "check_count": len(self.checks),
            "passed_checks": sum(1 for item in self.checks if item["status"] == "passed"),
            "failed_checks": sum(1 for item in self.checks if item["status"] == "failed"),
            "invocation_count": len(self.invocations), "input_hashes": self.hash_record,
            "checks": self.checks,
        }
        (self.out / "run-summary.json").write_bytes(json_bytes(record))
        print(json.dumps({"run_dir": str(self.out), "status": status, "result": result,
                          "check_count": record["check_count"], "invocation_count": record["invocation_count"],
                          "error": error}, ensure_ascii=False, indent=2))


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--crown", required=True, type=Path, help="frozen native CROWN CLI binary")
    parser.add_argument("--repo-root", required=True, type=Path, help="repository root used as CLI working directory")
    parser.add_argument("--schema-dir", required=True, type=Path,
                        help="directory with the four pinned V2/V1 schema files")
    parser.add_argument("--fixture-dir", type=Path, default=ARTIFACT_DIR / "fixtures/p08",
                        help="self-contained fixture package (defaults beside this script)")
    parser.add_argument("--outputdir", required=True, type=Path,
                        help="fresh parent directory under /tmp or repo/build/verification")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    harness = Harness(args.repo_root, args.crown, args.schema_dir, args.fixture_dir, args.outputdir)
    try:
        result = harness.run()
    except Exception as error:
        harness.finish("failed", None, f"{type(error).__name__}: {error}", traceback.format_exc())
        return 1
    harness.finish("passed", result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
