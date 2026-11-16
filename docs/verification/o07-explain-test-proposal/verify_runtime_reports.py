#!/usr/bin/env python3
"""Run the separately linked runtime report emitter and validate its real snapshots."""

from __future__ import annotations

import argparse
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
from pathlib import Path
from typing import Any


PACKAGE_SHA256 = "1062120b94a5733506186cb93cd6dac2bc99c7b4b3d3ab95e8c9c1882afbdb93"
SCHEMA_SHA256 = "78c04c2e29d42619de2f05f21e0f8c07fbe4c00d1da3a0aaf536629cfe6a198a"
MODE_CLI_SHA256 = "5187c47b1cb39e3604fe514a36010a647bfcbbb35fdbd90deb81ae1531e7d314"
MODE_ARCHIVE_SHA256 = "3a51a21032690940c3c7c83f05ddd56e275811f61955f2ed438f9487b7bcb2b9"
PROPOSAL = Path("docs/verification/o07-explain-proposal")
EMITTER_SOURCE = Path("docs/verification/o07-explain-test-proposal/runtime_report_emitter.cpp")
EXPECTED_GENERATION = (1 << 64) - 2


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(block)
    return value.hexdigest()


def encode_json(value: Any) -> bytes:
    return (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode("utf-8")


def load_json(path: Path) -> Any:
    with path.open("r", encoding="utf-8") as stream:
        return json.load(stream)


def under(path: Path, root: Path) -> bool:
    try:
        path.relative_to(root)
        return True
    except ValueError:
        return False


class RuntimeReportVerifier:
    def __init__(self, repo: Path, emitter: Path, plan: Path, outputdir: Path, depfile: Path,
                 report_objects: list[Path]):
        self.repo = repo.resolve()
        self.emitter = emitter.resolve()
        self.plan = plan.resolve()
        self.outputdir = outputdir.resolve()
        self.depfile = depfile.resolve()
        self.report_objects = [path.resolve() for path in report_objects]
        self.run_dir: Path | None = None
        self.checks: list[dict[str, str]] = []
        self.validator: Any = None
        self.input_hashes: dict[str, Any] = {}

    @property
    def out(self) -> Path:
        if self.run_dir is None:
            raise RuntimeError("output directory is not initialized")
        return self.run_dir

    def check(self, condition: bool, label: str, detail: str = "") -> None:
        item = {"check": label, "status": "passed" if condition else "failed"}
        if detail:
            item["detail"] = detail
        self.checks.append(item)
        if not condition:
            raise AssertionError(f"{label}: {detail or 'condition was false'}")

    def setup(self) -> None:
        tmp = Path("/tmp").resolve()
        verification = (self.repo / "build/verification").resolve()
        self.check(self.outputdir == tmp or under(self.outputdir, tmp) or under(self.outputdir, verification),
                   "output directory is under /tmp or build/verification", str(self.outputdir))
        self.outputdir.mkdir(parents=True, exist_ok=True)
        stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime())
        self.run_dir = self.outputdir / f"o07-runtime-report-{stamp}-{os.getpid()}-{uuid.uuid4().hex[:8]}"
        self.run_dir.mkdir()

    def package_inputs(self) -> dict[str, Any]:
        proposal = self.repo / PROPOSAL
        readiness_path = proposal / "readiness.json"
        evidence_path = proposal / "compile-evidence-mode-binding.json"
        dependencies_path = proposal / "baseline-dependencies-mode-binding.json"
        schema_path = proposal / "schemas/explain-report-v1.schema.json"
        readiness = load_json(readiness_path)
        evidence = load_json(evidence_path)
        dependencies = load_json(dependencies_path)
        self.check(readiness.get("package_sha256") == PACKAGE_SHA256 and readiness.get("executed") is False,
                   "frozen report package is compiler/link-only")
        self.check(evidence.get("executed") is False and evidence.get("mode_binding_api") is True,
                   "selected report CLI evidence uses the mode-binding API")
        self.check(evidence.get("binary_sha256") == MODE_CLI_SHA256 and
                   readiness.get("mode_binding_binary") == MODE_CLI_SHA256,
                   "matching mode-binding report CLI evidence")
        file_hashes: dict[str, str] = {}
        for relative, expected in sorted(readiness["files"].items()):
            actual = digest(proposal / relative)
            self.check(actual == expected, f"frozen proposal source hash: {relative}")
            file_hashes[relative] = actual
        package = hashlib.sha256(json.dumps(readiness["files"], sort_keys=True,
                                             separators=(",", ":")).encode("utf-8")).hexdigest()
        self.check(package == PACKAGE_SHA256, "canonical report package fingerprint")
        self.check(digest(schema_path) == SCHEMA_SHA256, "frozen report schema hash")

        dependency_hashes: dict[str, str] = {}
        for relative, expected in sorted(dependencies["inputs"].items()):
            actual = digest(self.repo / relative)
            self.check(actual == expected, f"frozen mode-binding source dependency hash: {relative}")
            dependency_hashes[relative] = actual

        archives: dict[str, str] = {}
        for archive_name, expected in sorted(evidence["archives"].items()):
            actual = digest(Path(archive_name))
            self.check(actual == expected, f"linked archive hash: {archive_name}")
            archives[archive_name] = actual
        mode_archive = next(path for path in archives if "libcrown_runtime_o07_mode_binding.a" in path)
        self.check(archives[mode_archive] == MODE_ARCHIVE_SHA256,
                   "complete nine-unit mode-binding runtime archive hash")

        self.check(digest(self.emitter) != "", "runtime report emitter exists")
        self.check(digest(self.plan) != "", "P08 physical plan exists")
        self.check(digest(self.depfile) != "", "emitter compiler dependency file exists")
        for object_path in self.report_objects:
            self.check(digest(object_path) != "", f"matching report object exists: {object_path.name}")
        compiler_inputs = self.parse_depfile(self.depfile)
        compiled_input_hashes: dict[str, str] = {}
        for path in compiler_inputs:
            resolved = path.resolve()
            if resolved.is_file():
                compiled_input_hashes[str(resolved)] = digest(resolved)
        self.input_hashes = {
            "report_source": {str((self.repo / EMITTER_SOURCE).resolve()): digest(self.repo / EMITTER_SOURCE)},
            "report_compiler_inputs": compiled_input_hashes,
            "proposal_files": file_hashes,
            "mode_binding_dependencies": dependency_hashes,
            "linked_archives": archives,
            "readiness_json": {str(readiness_path): digest(readiness_path)},
            "compile_evidence": {str(evidence_path): digest(evidence_path)},
            "dependency_manifest": {str(dependencies_path): digest(dependencies_path)},
            "schema": {str(schema_path): digest(schema_path)},
            "runtime_emitter_binary": {str(self.emitter): digest(self.emitter)},
            "physical_plan": {str(self.plan): digest(self.plan)},
            "report_objects": {str(path): digest(path) for path in self.report_objects},
            "compiler_depfile": {str(self.depfile): digest(self.depfile)},
        }
        return {"schema_path": schema_path, "readiness": readiness, "evidence": evidence}

    @staticmethod
    def parse_depfile(path: Path) -> list[Path]:
        text = path.read_text(encoding="utf-8")
        flattened = re.sub(r"\\\r?\n", " ", text)
        if ":" not in flattened:
            raise ValueError("compiler depfile has no target separator")
        dependencies = flattened.split(":", 1)[1].split()
        return [Path(token.replace("\\ ", " ")) for token in dependencies]

    def setup_schema(self, schema_path: Path) -> None:
        try:
            with warnings.catch_warnings():
                warnings.simplefilter("ignore", DeprecationWarning)
                from jsonschema import Draft202012Validator, RefResolver
        except ImportError as error:
            raise RuntimeError("Python package jsonschema>=4 is required; validation is offline") from error
        schema = load_json(schema_path)
        Draft202012Validator.check_schema(schema)
        store = {schema_path.resolve().as_uri(): schema}
        if "$id" in schema:
            store[schema["$id"]] = schema

        def local_file(uri: str) -> Any:
            if uri not in store:
                raise RuntimeError("schema reference outside the local schema: " + uri)
            return store[uri]

        def deny_network(uri: str) -> Any:
            raise RuntimeError("offline schema validation attempted network access: " + uri)

        resolver = RefResolver(schema_path.resolve().as_uri(), schema, store=store,
                               handlers={"file": local_file, "http": deny_network, "https": deny_network})
        self.validator = Draft202012Validator(schema, resolver=resolver)
        self.check(True, "pinned Draft 2020-12 schema loaded without network resolution")

    def validate_report(self, report: Any, name: str) -> None:
        errors = list(self.validator.iter_errors(report))
        if errors:
            first = errors[0]
            raise AssertionError(f"{name} report schema error at {list(first.absolute_path)}: {first.message}")
        self.check(True, f"offline schema accepts actual runtime report: {name}")

    def verify_report(self, report: dict[str, Any], name: str, expected_mode: str,
                      expected_generation: int, expected_saturated: bool,
                      last_mode: str | None, last_generation: int | None,
                      last_saturated: bool | None, expected_outcome: str | None) -> dict[str, Any]:
        self.validate_report(report, name)
        observations = report["observations"]
        current_config = observations["current_configuration"]
        self.check(observations["availability"] == "available", f"{name}: observation mode is available")
        self.check(current_config is not None, f"{name}: current configuration is attached")
        self.check(current_config["mode"] == expected_mode and current_config["generation"] == expected_generation and
                   current_config["generation_saturated"] is expected_saturated,
                   f"{name}: current mode/generation matches expected transition")
        self.check(report["mode"]["scope"] == "current_runtime_configuration" and
                   report["mode"]["runtime"]["mode"] == expected_mode,
                   f"{name}: report mode descriptor matches current configuration")
        self.check(current_config["support_owner"] == report["mode"]["runtime"]["owner"] == observations["trace"]["support_owner"],
                   f"{name}: report/config/observation owners agree")
        self.check(current_config["guarantee_prose"] == "not_copied_from_current_profile",
                   f"{name}: configuration does not claim copied current guarantee prose")
        self.check(report["height_evidence"]["status"] == "checked_upper" and
                   report["height_evidence"]["original_minimum"] is None,
                   f"{name}: runtime capture without evidence remains checked_upper")

        for summary_name in ("current", "last"):
            summary = observations[summary_name]
            if summary is None:
                continue
            for metric in summary["values"]:
                if metric["availability"] != "available":
                    self.check(metric["value"] is None and metric["saturated"] is None,
                               f"{name}/{summary_name}: unavailable metric payload is null", metric.get("id", ""))

        last = observations["last"]
        if last_mode is None:
            self.check(last is None, f"{name}: no historical summary exists yet")
        else:
            self.check(last is not None, f"{name}: historical summary is retained")
            if last is not None:
                config = last["configuration"]
                self.check(last["mode_binding"] == "exact_begin_configuration" and config is not None,
                           f"{name}: historical summary has begin-time mode binding")
                self.check(config["mode"] == last_mode and config["generation"] == last_generation and
                           config["generation_saturated"] is last_saturated,
                           f"{name}: historical config remains at its original mode/generation")
                self.check(last["outcome"] == expected_outcome,
                           f"{name}: historical attempt outcome", str(last["outcome"]))
                self.check(config["requested_options"] == self.expected_options(),
                           f"{name}: historical requested options preserve all supplied fields")
        if name in {"initial", "pending"}:
            self.check(current_config["requested_options"] == self.expected_options(),
                       f"{name}: current config preserves all supplied option values")
        return current_config

    @staticmethod
    def expected_options() -> dict[str, Any]:
        return {
            "mode": "delta", "view": "core", "live_maintenance": "on_output", "completion": "automatic",
            "work_limit": 200000, "cursor_work_limit": 250000, "view_work_limit": 260000,
            "spool_row_limit": 270000, "spool_byte_limit": 280000,
            "physical": {
                "work_limit": 210000, "derivation_limit": 220000,
                "support": {
                    "work_limit": 230000, "support_limit": 240000, "order": "lifo",
                    "capture_transitions": True,
                    "observation": {"mode": "counters", "trace_capacity": 7, "sample_period": 3,
                                    "sample_offset": 1, "trace_timings": False},
                },
            },
        }

    def verify(self) -> dict[str, Any]:
        self.setup()
        package = self.package_inputs()
        self.setup_schema(package["schema_path"])
        argv = [str(self.emitter), str(self.plan)]
        process = subprocess.run(argv, cwd=self.repo, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                 check=False, timeout=180)
        (self.out / "stdout.bin").write_bytes(process.stdout)
        (self.out / "stderr.bin").write_bytes(process.stderr)
        (self.out / "inputs.json").write_bytes(encode_json(self.input_hashes))
        (self.out / "invocation.json").write_bytes(encode_json({"argv": argv, "cwd": str(self.repo),
                                                                 "returncode": process.returncode,
                                                                 "expected_returncode": 0}))
        self.check(process.returncode == 0 and process.stderr == b"",
                   "runtime emitter exits successfully without stderr", process.stderr.decode("utf-8", "replace"))
        try:
            reports = json.loads(process.stdout.decode("utf-8"))
        except (UnicodeDecodeError, json.JSONDecodeError) as error:
            raise AssertionError(f"runtime emitter output is not JSON: {error}") from error
        (self.out / "runtime-reports.json").write_bytes(encode_json(reports))
        expected_keys = {"initial", "pending", "after_attempt", "after_noop_switch",
                         "after_successful_switch", "after_saturation_and_runtime_drop"}
        self.check(set(reports) == expected_keys, "emitter returns all independently named report snapshots")

        initial = self.verify_report(reports["initial"], "initial", "delta", EXPECTED_GENERATION,
                                     False, None, None, None, None)
        pending = self.verify_report(reports["pending"], "pending", "delta", EXPECTED_GENERATION,
                                     False, None, None, None, None)
        pending_summary = reports["pending"]["observations"]["current"]
        self.check(reports["pending"]["mode"]["runtime"]["state"] == "pending_delta" and
                   pending_summary is not None and pending_summary["outcome"] == "pending",
                   "capture during a public pending epoch retains pending attempt state")
        self.check(pending_summary["mode_binding"] == "exact_begin_configuration" and
                   pending_summary["configuration"] == pending,
                   "pending summary uses the current exact begin configuration")

        attempt = self.verify_report(reports["after_attempt"], "after_attempt", "delta", EXPECTED_GENERATION,
                                     False, "delta", EXPECTED_GENERATION, False, "committed")
        self.check(reports["after_attempt"]["observations"]["current"] is None,
                   "completed attempt leaves no current summary")
        self.check(reports["after_attempt"]["observations"]["last"]["configuration"] == initial,
                   "first historical attempt retains the initial configuration")

        no_op = self.verify_report(reports["after_noop_switch"], "after_noop_switch", "delta", EXPECTED_GENERATION,
                                   False, "delta", EXPECTED_GENERATION, False, "committed")
        self.check(no_op == attempt, "same-mode no-op preserves current configuration exactly")
        self.check(reports["after_noop_switch"]["observations"]["last"]["configuration"] ==
                   reports["after_attempt"]["observations"]["last"]["configuration"],
                   "same-mode no-op leaves the historical binding unchanged")

        switched = self.verify_report(reports["after_successful_switch"], "after_successful_switch", "maintenance",
                                      (1 << 64) - 1, False, "delta", EXPECTED_GENERATION, False, "committed")
        self.check(switched["generation"] == EXPECTED_GENERATION + 1,
                   "successful mode switch increments from maximum-minus-one to maximum")
        self.check(reports["after_successful_switch"]["observations"]["last"]["configuration"] ==
                   reports["after_attempt"]["observations"]["last"]["configuration"],
                   "successful mode switch does not relabel the historical summary")

        saturated = self.verify_report(reports["after_saturation_and_runtime_drop"],
                                       "after_saturation_and_runtime_drop", "delta", (1 << 64) - 1,
                                       True, "delta", EXPECTED_GENERATION, False, "committed")
        self.check(saturated["generation_saturated"] is True,
                   "next successful mode switch saturates generation without changing semantics")
        self.check(reports["after_saturation_and_runtime_drop"]["observations"]["last"]["configuration"] ==
                   reports["after_attempt"]["observations"]["last"]["configuration"],
                   "detached report retains the original attempt configuration after runtime destruction")
        return {
            "status": "passed",
            "report_count": len(reports),
            "snapshots": sorted(reports),
            "observed_transition": "delta(max-1) -> maintenance(max) -> delta(max,saturated)",
            "runtime_destroyed_before_final_serialization": True,
            "check_count": len(self.checks),
        }

    def finish(self, result: dict[str, Any] | None, error: str | None = None,
               traceback_text: str | None = None) -> None:
        if self.run_dir is None:
            return
        status = "passed" if error is None else "failed"
        record = {"status": status, "result": result, "error": error, "traceback": traceback_text,
                  "check_count": len(self.checks),
                  "passed_checks": sum(check["status"] == "passed" for check in self.checks),
                  "failed_checks": sum(check["status"] == "failed" for check in self.checks),
                  "input_hashes": self.input_hashes, "checks": self.checks}
        (self.out / "run-summary.json").write_bytes(encode_json(record))
        print(json.dumps({"run_dir": str(self.out), "status": status, "result": result,
                          "check_count": record["check_count"], "error": error}, ensure_ascii=False, indent=2))


def args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--emitter", required=True, type=Path)
    parser.add_argument("--plan", required=True, type=Path)
    parser.add_argument("--depfile", required=True, type=Path)
    parser.add_argument("--report-object", action="append", required=True, type=Path,
                        help="matching mode-binding report .o file; repeat for both report objects")
    parser.add_argument("--repo", required=True, type=Path)
    parser.add_argument("--outputdir", required=True, type=Path)
    return parser.parse_args()


def main() -> int:
    options = args()
    verifier = RuntimeReportVerifier(options.repo, options.emitter, options.plan, options.outputdir,
                                     options.depfile, options.report_object)
    try:
        result = verifier.verify()
    except Exception as error:
        verifier.finish(None, f"{type(error).__name__}: {error}", traceback.format_exc())
        return 1
    verifier.finish(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
