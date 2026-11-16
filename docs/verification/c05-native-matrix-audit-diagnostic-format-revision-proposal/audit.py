#!/usr/bin/env python3
"""Evidence-only C05 matrix audit. Never imports/runs project code or subprocesses."""
from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
import re
import shlex
import tarfile
from pathlib import Path

ROOT = Path("/home/userroot/Codex/CROWN")
V = ROOT / "build/verification"
PACKAGE = Path(__file__).resolve().parent
CONFIGS = ("debug", "release", "sanitize", "clang", "clean-source")
NATIVE = {"count": 676, "sha256": "d963498ffa4d0ebcfa650f2a958258c2bf18a352022c264549dc3cbbab79b733"}
EXECUTION = {"count": 733, "sha256": "fc12d2bd82756946a3a5bcdec910df400481b7af1bc4199254040e59730c2445"}
FREEZE_SHA = "affcb8fa29b193e57f9501c5a88054eaba9467b7040273f36f28c507f3146711"
PUBLICATION = ROOT / "docs/verification/c05-native-registration-proposal"
RETAINED_C02 = V / "c05-c02-predecessor-build-evidence"
JSON_ACTIVE = "f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406"
JSON_UPSTREAM = "aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63"
RANKING_UNITS = {"src/planner/ranking.cpp", "src/planner/ranking_integer.cpp", "src/planner/ranking_payload.cpp"}
BRIDGE_UNIT = "src/runtime/ranking_evidence.cpp"
OLD_C02_TESTS = ("ranking_binding", "ranking_pure_link", "ranking_contract", "ranking_empty",
             "ranking_payload_time", "ranking_census", "ranking_exceptions", "ranking_normalized_exceptions",
             "ranking_public_independent", "ranking_integer_independent", "json_cleanup", "json_patch_compatibility")
SELECTION_UNITS = {"src/planner/selection.cpp", "src/planner/selection_budget.cpp",
                   "src/planner/selection_binding.cpp", "src/planner/selection_payload.cpp", "src/planner/selection_cache.cpp"}
SELECTION_BRIDGE = "src/runtime/selection.cpp"
NEW_TESTS = ("selection_pure_link", "selection_contract", "selection_cache", "selection_source", "selection_current",
             "selection_binding", "selection_resources", "selection_census", "selection_exception",
             "selection_normalized_exception", "selection_public_independent", "selection_cache_independent",
             "selection_resources_independent", "selection_binding_independent", "selection_publication_fault_independent")
NEW_OBJECT_TARGETS = {"crown_selection_usage_production", "crown_selection_usage_testing"}
OBJECT_TARGETS = {"crown_ranking_usage_production", "crown_ranking_usage_testing"} | NEW_OBJECT_TARGETS
PREDECESSOR_CAPTURE_SHA = "b21d69747ea69f0a7d7d86ffd9c372dc47eee5020ee4f0e386a5b45cc1616561"
PREDECESSOR_MATRIX_SHA = "08c543cecf784e466e8fc2a8cafd52ded7c51b57e06d50634bd0059515b9c5fd"
PREPARATION_SHA = "43b420248cb77e1c6c9ba72fe6f29e3de80498740d19d53b0cafbad935d5f0c9"
FLAGS = {"-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wsign-conversion", "-Werror"}
RUNTIME_NEW = {
    "src/runtime/statistics.cpp", "src/runtime/owner_statistics.cpp",
    "src/runtime/statistics_collection.cpp", "src/runtime/workload_statistics.cpp",
    "src/runtime/combined_statistics.cpp",
}
REPORT_NEW = {"src/observability/statistics_explain.cpp", "src/io/statistics_explain.cpp"}
RUNTIME_UNITS = RUNTIME_NEW | {
    "src/runtime/support.cpp", "src/runtime/physical.cpp", "src/runtime/delta.cpp",
    "src/runtime/replay.cpp", "src/runtime/session.cpp", "src/runtime/window.cpp",
    "src/runtime/observation.cpp", "src/io/support.cpp", "src/io/inspection.cpp",
}
REPORT_UNITS = REPORT_NEW | {
    "src/observability/explain.cpp", "src/io/explain.cpp",
    "src/io/run_context.cpp", "src/io/cursor_observation.cpp",
}
CONSUMERS = {
    "crown_statistics_capture_test": ("statistics_capture_test", "production"),
    "crown_statistics_capture_exceptions_test": ("statistics_capture_exception_test", "production"),
    "crown_statistics_owner_test": ("owner_statistics_test", "production"),
    "crown_statistics_owner_exceptions_test": ("owner_statistics_exception_test", "production"),
    "crown_statistics_collection_test": ("statistics_collection_test", "testing"),
    "crown_statistics_workload_test": ("workload_statistics_test", "testing"),
    "crown_statistics_workload_exceptions_test": ("workload_statistics_exception_test", "testing"),
    "crown_statistics_scalars_test": ("scalar_statistics_test", "production"),
}
for _variant in ("production", "testing"):
    for _label, _source in (
        ("combined", "combined_statistics_test"),
        ("combined_exceptions", "combined_statistics_exception_test"),
        ("report_exceptions", "statistics_explain_exception_test"),
        ("runtime_only", "statistics_runtime_only_test"),
        ("report", "statistics_explain_test"),
    ):
        CONSUMERS[f"crown_statistics_{_label}_{_variant}_test"] = (_source, _variant)
for _order in ("fifo", "lifo"):
    for _fixture in ("delta_runtime", "delta_replay", "window"):
        CONSUMERS[f"crown_statistics_{_fixture}_{_order}_test"] = (_fixture + "_test", "production")
POLICY_TARGETS = {name for name in CONSUMERS if name.endswith(("_fifo_test", "_lifo_test"))}
C02_CONSUMERS = {
    "crown_ranking_binding_test": ("ranking_binding_test", "pure"),
    "crown_ranking_pure_link_test": ("ranking_pure_link_test", "pure"),
    "crown_ranking_contract_test": ("ranking_contract_test", "production"),
    "crown_ranking_empty_test": ("ranking_empty_test", "production"),
    "crown_ranking_payload_time_test": ("ranking_payload_time_test", "production"),
    "crown_ranking_census_test": ("ranking_census_test", "testing"),
    "crown_ranking_exceptions_test": ("ranking_exception_test", "production"),
    "crown_ranking_normalized_exceptions_test": ("ranking_normalized_exception_test", "production"),
    "crown_ranking_public_independent_test": ("ranking_public_independent_test", "production"),
    "crown_ranking_integer_independent_test": ("ranking_integer_independent_test", "pure"),
    "crown_json_cleanup_test": ("json_cleanup_test", "json_active"),
    "crown_json_upstream_control_test": ("json_cleanup_test", "json_original"),
}
CONSUMERS.update(C02_CONSUMERS)
C05_CONSUMERS = {
    "crown_" + name + "_test": (name + "_test",
        "pure" if name in {"selection_pure_link", "selection_binding_independent"} else
        "testing" if name == "selection_census" else "production")
    for name in NEW_TESTS
}
CONSUMERS.update(C05_CONSUMERS)
SIGNED_TRACE_TESTS = {
    "delta_runtime", "delta_runtime_eager", "delta_runtime_incremental",
    "delta_runtime_root_first", "delta_runtime_anchored",
}
for _trace_order in ("fifo", "lifo"):
    for _trace_policy in ("", "_eager", "_incremental", "_root_first", "_anchored"):
        SIGNED_TRACE_TESTS.add("statistics_delta_" + _trace_order + _trace_policy)
PROBES = {
    "set_satisfied", "set_projection", "seed_window_sequence", "seed_session_physical_sequence",
    "seed_delta_sequence", "physical", "set_live_bucket", "set_live_total",
    "seed_c01_report_saturation", "seed_physical_sequence", "support", "set_derivation",
}
WARNINGS = [
    "gmake[3]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.",
    "vendor/upb/upb.c:8245:8: warning: ‘sv.data’ may be used uninitialized [-Wmaybe-uninitialized]",
    "vendor/upb/upb.c:9206:6: warning: ‘sv.size’ may be used uninitialized [-Wmaybe-uninitialized]",
]
PARSER_SHA = "2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d"
PREPARATION = {}
HISTORICAL_RECORDS = {}
CLEAN_MANIFESTS = {}


ERRORS: list[str] = []
PENDING: list[str] = []
REVIEW: list[dict] = []
APPROVALS: dict[str, dict] = {}
USED_APPROVALS: set[str] = set()
READ_PINS: dict[str, str] = {}
NORMALIZATIONS: list[dict] = []


class AuditError(Exception):
    pass


def need(condition, message):
    if not condition:
        raise AuditError(message)


def label(path):
    path = Path(path)
    return str(path.relative_to(ROOT)) if path.is_relative_to(ROOT) else str(path)


def read(path):
    path = Path(path)
    need(path.is_file(), "missing required evidence: " + label(path))
    value = path.read_bytes()
    pin = hashlib.sha256(value).hexdigest()
    need(label(path) not in READ_PINS or READ_PINS[label(path)] == pin, "evidence changed during audit: " + label(path))
    READ_PINS[label(path)] = pin
    return value.decode("utf-8")


def digest(path):
    path = Path(path)
    need(path.is_file(), "missing pinned file: " + label(path))
    hasher = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            hasher.update(chunk)
    value = hasher.hexdigest()
    need(label(path) not in READ_PINS or READ_PINS[label(path)] == value, "evidence changed during audit: " + label(path))
    READ_PINS[label(path)] = value
    return value


def pairs(values):
    result = {}
    for key, value in values:
        need(key not in result, "duplicate JSON key: " + key)
        result[key] = value
    return result


def data(path):
    return json.loads(read(path), object_pairs_hook=pairs)


def terminal(path, required="exit_code"):
    path = Path(path)
    if not path.is_file():
        PENDING.append(label(path) + ": terminal record absent")
        return None
    try:
        raw = path.read_bytes()
        value = json.loads(raw.decode("utf-8"), object_pairs_hook=pairs)
    except (json.JSONDecodeError, UnicodeDecodeError):
        PENDING.append(label(path) + ": terminal record incomplete")
        return None
    if not isinstance(value, dict) or value.get("terminal") is not True or required not in value:
        PENDING.append(label(path) + ": not terminal")
        return None
    pin = hashlib.sha256(raw).hexdigest()
    need(label(path) not in READ_PINS or READ_PINS[label(path)] == pin, "terminal evidence changed during audit")
    READ_PINS[label(path)] = pin
    return value

def guarded(name, action):
    try:
        return action()
    except (AuditError, OSError, ValueError, KeyError, TypeError, IndexError, AttributeError, tarfile.TarError) as error:
        ERRORS.append(name + ": " + str(error))
        return {"status": "audit_error", "error": str(error)}


def cache_values(text):
    values = {}
    for line in text.splitlines():
        match = re.match(r"^([^#/:][^:=]*):[^=]+=(.*)$", line)
        if match:
            values[match[1]] = match[2]
    return values


def normalized(value, source, build):
    # Replace only exact known directory prefixes, never arbitrary numeric data.
    value = value.replace(str(build) + "/", "$BUILD/").replace(str(source) + "/", "$SOURCE/")
    if value == str(build):
        return "$BUILD"
    if value == str(source):
        return "$SOURCE"
    return value


def command_normalized(words, source, build):
    return [normalized(word, source, build) for word in words]


def records(text, total):
    matches = list(re.finditer(r"^\s*(\d+)/(\d+) Testing:\s+(\S+)\s*$", text, re.M))
    need(len(matches) == total, f"LastTest contains {len(matches)} records, expected {total}")
    result = []
    for index, match in enumerate(matches):
        need(int(match[2]) == total, "LastTest denominator changed")
        section = text[match.end():matches[index + 1].start() if index + 1 < len(matches) else len(text)]
        output = re.findall(r"^Output:\s*\n-+\n(.*?)^<end of output>\s*$", section, re.M | re.S)
        commands = re.findall(r"^Command: (.*)$", section, re.M)
        directories = re.findall(r"^Directory: (.*)$", section, re.M)
        need(len(output) == len(commands) == len(directories) == 1, "ambiguous/missing LastTest output, command or directory")
        need(len(re.findall(r"^Test Passed\.$", section, re.M)) == 1, "LastTest does not contain exactly one passed outcome")
        need(not re.search(r"^Test (?:Failed|Not Run|Timeout)", section, re.M), "LastTest contains nonpassing outcome")
        result.append({"ordinal": int(match[1]), "name": match[3], "argv": shlex.split(commands[0]),
                       "directory": directories[0], "output": output[0]})
    need([x["ordinal"] for x in result] == list(range(1, total + 1)), "LastTest ordinals are not exact ordered 1..N")
    need(len({x["name"] for x in result}) == total, "LastTest duplicate test name")
    return result


def output_rows(text, test, source, build, evidence):
    """Keep numeric/boolean rows and every trace, with source-bound trace grammar."""
    raw, comparable = [], []
    for line in text.splitlines():
        if not line.startswith("trace "):
            line = line.rstrip()
        if not (line.startswith("trace ") or re.search(r"\d", line) or re.search(r"=\s*(?:yes|no|true|false)\b", line)):
            continue
        raw.append(line)
        changed = normalized(line, source, build)
        if test == "explain_cli" and re.match(r'^\s*"run_dir": ', changed):
            match = re.fullmatch(r'(\s*"run_dir": )"(/tmp/crown-native-explain-acceptance/o07-native-explain-[A-Za-z0-9_.-]+)",', changed)
            need(match is not None, "unexpected CLI output-location encoding")
            changed = match[1] + '"$CLI_ARTIFACT_DIRECTORY",'
        if line.startswith("trace "):
            match = re.fullmatch(r"(trace .+ seq=\d+ outputs=)(.*)", changed)
            if match is not None:
                need(test in SIGNED_TRACE_TESTS, "signed trace outside its source-supported producer")
                items = re.findall(r"[+-]\([^()]*\)", match[2])
                need(items and ",".join(items) == match[2], "signed trace tokenization loses bytes or has no records")
                # D04 fixture checks signed-key sets; enumeration order is not its contract.
                # Preserve multiplicity, signs, row fields and sequence; never deduplicate.
                changed = match[1] + ",".join(sorted(items))
            else:
                need(test not in SIGNED_TRACE_TESTS and
                     re.search(r"\b(?:seq|outputs)\b", changed) is None,
                     "malformed signed-output trace row")
                # Other numeric traces, including delta_spec's owner_factor/key/output
                # row, retain their complete bytes after directory normalization.
        if changed != line:
            NORMALIZATIONS.append({"evidence": evidence, "test": test, "row": len(raw) - 1,
                                   "raw": line, "comparison": changed})
        comparable.append(changed)
    return {"raw": raw, "comparison": comparable}


ALLOCATION_FIELD = re.compile(
    r"(?P<field>\b(?:[A-Za-z_.-]*(?:fault_positions|failure_points|successful_allocation_calls|"
    r"final_attempt_allocation_calls|max_faulted_calls|allocations)|"
    r"(?:[A-Za-z_-]+ )*allocation failures|injected failures|configure failures|"
    r"same-owner update failures|mode failures|allocation positions|normal-new-points|normal-free-calls|"
    r"persistent-fault-points|fault-new-attempts|fault-free-calls|injected-failures|fault-points))=(?P<value>\d+)"
)


def allocation_only(before, after):
    # Only the C05 source-supported fault rows admit these extra count names.
    c05 = (before.startswith("C05 ") and after.startswith("C05 ") and
           (" allocation_positions=" in before or before.startswith(("C05 persistent positions=",
             "C05 normalized persistent positions=", "C05 focused atomic OOM groups=2 positions="))))
    pattern = re.compile(r"(?P<field>\b(?:allocation_positions|positions|publication_failures))=(?P<value>\d+)") if c05 else ALLOCATION_FIELD
    left, right = list(pattern.finditer(before)), list(pattern.finditer(after))
    if not left or len(left) != len(right) or [m["field"] for m in left] != [m["field"] for m in right]:
        return False
    replace = lambda text: pattern.sub(lambda m: m["field"] + "=<allocation-count>", text)
    return replace(before) == replace(after) and before != after

def compare_rows(kind, test, configuration, baseline, current, baseline_configuration):
    need(len(baseline) == len(current), f"{configuration}/{test}: numeric row count changed ({kind})")
    for index, (before, after) in enumerate(zip(baseline, current)):
        if before == after:
            continue
        change = {"kind": kind, "test": test, "configuration": configuration,
                  "baseline_configuration": baseline_configuration, "row_index": index,
                  "before": before, "after": after}
        need(allocation_only(before, after), "non-allocation numeric difference: " + json.dumps(change, sort_keys=True))
        key = hashlib.sha256(json.dumps(change, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
        approval = APPROVALS.get(key)
        if approval:
            need(approval.get("difference") == change, "allocation approval identity collision")
            USED_APPROVALS.add(key)
        REVIEW.append({**change, "id": key, "root_approved": approval is not None,
                       "root_reason": approval.get("reason") if approval else None})


def load_approvals(path, expected_sha):
    need((path is None) == (expected_sha is None), "allocation review path and SHA must be supplied together")
    if path is None:
        return None
    path = path.resolve()
    need(path.parent == V and re.fullmatch(r"selection-allocation-review-[A-Za-z0-9_.-]+\.json", path.name),
         "allocation review must be a designated selection-allocation-review-*.json FILE")
    need(re.fullmatch(r"[0-9a-f]{64}", expected_sha) and digest(path) == expected_sha, "allocation authority FILE differs")
    value = data(path)
    need(value.get("reviewer") == "root" and value.get("decision") == "accepted_allocation_only",
         "allocation review lacks explicit root decision")
    need(value.get("card") == "C05" and value.get("freeze_sha256") == FREEZE_SHA and
         value.get("native") == NATIVE and value.get("execution") == EXECUTION, "allocation review belongs to another freeze")
    for entry in value.get("entries", []):
        change = entry["difference"]
        fields = {"kind", "test", "configuration", "baseline_configuration", "row_index", "before", "after"}
        need(set(change) == fields and allocation_only(change["before"], change["after"]), "allocation review waives semantic data")
        key = hashlib.sha256(json.dumps(change, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
        need(entry.get("id") == key and key not in APPROVALS and isinstance(entry.get("reason"), str) and entry["reason"].strip(),
             "duplicate, unbound or unexplained allocation approval")
        APPROVALS[key] = entry
    return {"path": label(path), "sha256": expected_sha, "entries": len(APPROVALS)}


def load_authority(path, expected_sha):
    path = path.resolve()
    need(path.parent == V and re.fullmatch(r"selection-matrix-audit-authority-[A-Za-z0-9_.-]+\.json", path.name),
         "execution authority requires a distinct suffixed immutable FILE; the unsuffixed final source authority is reserved")
    need(re.fullmatch(r"[0-9a-f]{64}", expected_sha) and digest(path) == expected_sha, "root auditor authority FILE differs")
    value = data(path)
    need(value.get("reviewer") == "root" and value.get("decision") == "accepted_evidence_only_auditor" and value.get("card") == "C05",
         "root did not accept this evidence-only auditor")
    need(value.get("native") == NATIVE and value.get("execution") == EXECUTION and value.get("freeze_sha256") == FREEZE_SHA,
         "auditor authority scope differs")
    need(value.get("auditor") == {"path":label(PACKAGE/"audit.py"),"sha256":digest(PACKAGE/"audit.py")} and
         value.get("package") == {"path":label(PACKAGE/"PACKAGE_SHA256SUMS"),"sha256":digest(PACKAGE/"PACKAGE_SHA256SUMS")},
         "auditor/package authority binding differs")
    return {"path":label(path),"sha256":expected_sha,"decision":value["decision"]}

def input_pins():
    pinned = data(PACKAGE / "PINNED_INPUTS.json")
    for path, expected in pinned.items():
        target = Path(path) if path.startswith("/") else ROOT / path
        need(digest(target) == expected, "immutable audit input changed: " + path)
    return {"count": len(pinned), "manifest": label(PACKAGE / "PINNED_INPUTS.json")}


def preparation_authority():
    path = V/"c05-preparation-execution-completion.json"
    need(digest(path) == PREPARATION_SHA, "C05 preparation aggregation FILE changed")
    completion = data(path)
    need(completion.get("status") == "accepted_excluded_preparation_execution" and completion.get("reviewer") == "root",
         "C05 preparation was not root accepted")
    need(completion["producer"]["strict_consumers"] == completion["producer"]["sanitize_consumers"] == 10 and
         completion["independent"]["strict_final_consumers"] == completion["independent"]["sanitize_consumers"] == 5,
         "accepted preparation population differs")
    receipts = {entry["path"]:entry["sha256"] for entry in completion["terminal_receipts"]}
    need(len(receipts) == 7, "accepted receipt population differs")
    # These are immutable receipt FILEs only, never replay their old native/input-entry guards.
    for name, expected in receipts.items():
        need(digest(ROOT/name) == expected, "accepted preparation receipt FILE changed")
    for filename, prefix, expected in (
        ("c05-producer-sanitize-root-attempt-1.json","selection_",10),
        ("c05-independent-sanitize-root-attempt-1.json","",5),
    ):
        receipt = data(V/filename)
        need(receipt.get("status") == "passed" and receipt.get("source_stable") is True and
             receipt.get("expected_consumers") == len(receipt["tests"]) == expected, "matching final SAN reference is incomplete")
        for test in receipt["tests"]:
            name = prefix+test["name"]
            need(name in NEW_TESTS and name not in PREPARATION and test.get("exit_code") == 0, "reference consumer duplicate/failed")
            stdout, stderr = ROOT/test["stdout"]["path"], ROOT/test["stderr"]["path"]
            need(stdout.parent == stderr.parent == V and digest(stdout) == test["stdout"]["sha256"] and
                 digest(stderr) == test["stderr"]["sha256"] and not read(stderr), "reference output pin/diagnostic differs")
            PREPARATION[name] = stdout
    need(set(PREPARATION) == set(NEW_TESTS), "reference outputs do not cover the fifteen new consumers")
    return {"status":"accepted_scoped_preparation","completion":label(path),"receipt_count":len(receipts),
            "output_references":{name:{"path":label(p),"sha256":digest(p)} for name,p in PREPARATION.items()},
            "scope":"Excluded source/assertion lineage only; current native outcomes and allocation profiles remain separately audited."}

def final_stability():
    for path, expected in list(READ_PINS.items()):
        target = Path(path) if Path(path).is_absolute() else ROOT / path
        need(digest(target) == expected, "read evidence changed before publication: " + path)
    return freeze_audit()


def freeze_audit():
    path = V/"selection-execution-freeze.json"
    need(digest(path) == FREEZE_SHA, "C05 freeze FILE changed")
    freeze = data(path)
    need(freeze.get("card") == "C05" and freeze.get("native") == NATIVE and freeze.get("execution") == EXECUTION, "wrong C05 freeze")
    need(freeze.get("configs") == list(CONFIGS) and freeze.get("expected_compile_command_entries") == 238, "wrong config/unit inventory")
    names,old,ordered = freeze["expected_test_names"],freeze["old_legacy_test_names_in_order"],freeze["expected_test_names_in_order"]
    need(len(names) == len(set(names)) == 158 and names == sorted(names), "freeze unique sorted names differ")
    need(len(old) == len(set(old)) == 143 and ordered == old+list(NEW_TESTS) and sorted(ordered) == names,
         "old143/new15 ordered population differs")
    history = freeze["historical_manifest_file_hashes"]
    need(set(history) == {"P05","P06","P04","O03","R06","O02","O01","D06","P07","O07","C01","C02"}, "twelve historical FILEs required")
    for name,item in history.items():
        need(digest(ROOT/item["path"]) == item["sha256"], "historical manifest FILE drift: "+name)
    for kind,expected,roots,extras in (
        ("native",NATIVE,["include","src","apps","tests","cmake"],["CMakeLists.txt","CMakePresets.json"]),
        ("execution",EXECUTION,["include","src","apps","tests","cmake","schemas","tools","third_party"],
         ["CMakeLists.txt","CMakePresets.json","dependencies.lock.json"]),
    ):
        paths = set(extras)
        for directory in roots:
            paths.update(p.relative_to(ROOT).as_posix() for p in (ROOT/directory).rglob("*")
                         if p.is_file() and "__pycache__" not in p.parts and p.suffix not in {".pyc",".pyo"})
        aggregate = hashlib.sha256(); actual = {}
        for rel in sorted(paths):
            raw = (ROOT/rel).read_bytes(); aggregate.update(rel.encode()+b"\0"+raw+b"\0")
            actual[rel] = hashlib.sha256(raw).hexdigest()
            need(rel not in READ_PINS or READ_PINS[rel] == actual[rel], "current frozen source changed during audit: "+rel)
            READ_PINS[rel] = actual[rel]
        need({"count":len(paths),"sha256":aggregate.hexdigest()} == expected and actual == freeze[kind+"_file_sha256"],
             kind+" current frozen bytes/path set changed")
    integration_path = V/"c05-native-integration-start.json"
    need(digest(integration_path) == freeze["integration_record_sha256"], "integration FILE changed")
    integration = data(integration_path)
    need(integration.get("applied") is True and integration.get("phase") == "guarded_native_application_applied" and
         len(integration["mappings"]) == 34, "integration is not applied exact34")
    need(digest(ROOT/"Refactor.md") == "bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce", "original Refactor FILE changed")
    mapped = {row["destination"]:row for row in integration["mappings"]}
    need(len(mapped) == 34, "duplicate integration destination")
    for rel,item in mapped.items():
        if rel in freeze["execution_file_sha256"]:
            need(digest(ROOT/rel) == item["after"] == digest(ROOT/item["source"]), "mapped execution byte drift: "+rel)
    baseline = {}
    for name,expected in integration["baseline_entry_pins"].items():
        canonical = str((Path(name) if Path(name).is_absolute() else ROOT/name).resolve())
        need(canonical not in baseline or baseline[canonical] == expected, "conflicting fresh baseline alias")
        baseline[canonical] = expected
    for rel,expected in freeze["execution_file_sha256"].items():
        if rel not in mapped:
            need(baseline.get(str((ROOT/rel).resolve())) == expected, "unmapped byte differs from fresh integration baseline: "+rel)
    need(digest(PUBLICATION/"PACKAGE_SHA256SUMS") == freeze["registration_manifest_sha256"], "publication package changed")
    need(digest(ROOT/"docs/verification/c05-native-registration-independent-review-proposal/PACKAGE_SHA256SUMS") ==
         freeze["independent_review_manifest_sha256"], "registration review package changed")
    for field in ("manifest_file_pins","immutable_publication_file_pins"):
        for name,expected in freeze[field].items():
            target = Path(name) if Path(name).is_absolute() else ROOT/name
            need(digest(target) == expected, "immutable publication/manifest FILE drift: "+name)
    stage_path = V/"c05-publication-stage-build-attempt-1.json"
    need(digest(stage_path) == freeze["stage_receipt_sha256"], "stage receipt FILE changed")
    stage = data(stage_path)
    need(stage.get("status") == "passed_staged_registration_and_new_consumers" and stage.get("source_stable") is True
         and stage.get("registered_tests") == 158 and stage.get("old_test_prefix_preserved") == 143, "accepted stage scope differs")
    wanted_helpers = {"/tmp/crown-selection-"+name+".py" for name in
                      ("matrix","symbols","clean-evidence","clean-matrix","execution-freeze")}
    wanted_helpers.add("/tmp/crown-c05-native-integrate-v2.py")
    need(set(freeze["root_execution_helpers"]) == wanted_helpers, "six root helper FILEs differ")
    for name,expected in freeze["root_execution_helpers"].items():
        need(digest(Path(name)) == expected, "held helper changed: "+name)
    need(digest(V/"ranking-matrix-evidence-audit.json") == PREDECESSOR_MATRIX_SHA, "accepted C02 matrix FILE changed")
    accepted = data(V/"ranking-matrix-evidence-audit.json")
    accepted_compilers = {}
    for cache in accepted["closing_source_guard"]["toolchains"].values():
        for name,expected in cache["compiler_files"].items():
            key = str(Path(name).resolve())
            need(key not in accepted_compilers or accepted_compilers[key] == expected, "accepted compiler aliases conflict")
            accepted_compilers[key] = expected
    need(freeze["canonical_compiler_files"] == accepted_compilers, "new freeze silently admits changed compiler identities")
    for name,expected in accepted_compilers.items():
        need(digest(Path(name)) == expected, "canonical compiler bytes changed")
    for config,cache in freeze["predecessor_toolchain_caches"].items():
        need(cache["values"] == accepted["closing_source_guard"]["toolchains"][config]["values"], "held compiler/cache choices changed")
        need(digest(ROOT/cache["path"]) == cache["sha256"], "retained cache FILE drift")
        for name,expected in cache["compiler_files"].items():
            need(digest(Path(name)) == expected == accepted_compilers.get(str(Path(name).resolve())), "compiler alias bytes/resolution changed")
    registry = freeze["immutable_preparation_registry"]
    need(digest(ROOT/registry["path"]) == registry["sha256"], "immutable preparation registry changed")
    need(freeze["incremental_partition_expectation"] == {"fresh":24,"cached":214,"actual_partition":"must_be_observed_and_audited"} and
         freeze["clean_partition_expectation"] == {"fresh":238,"cached":0}, "compile partition expectations changed")
    return {"status":"audited_pass","metadata":{"path":label(path),"sha256":FREEZE_SHA},"native":NATIVE,"execution":EXECUTION,
            "test_names":names,"ordered_names":ordered,"legacy_names":old,"historical_manifest_files":history,
            "expected_compile_units":freeze["expected_compile_units"],"added_compile_units":freeze["added_compile_units"],
            "toolchains":freeze["predecessor_toolchain_caches"],"root_helpers":freeze["root_execution_helpers"],
            "stage_receipt_sha256":freeze["stage_receipt_sha256"],"sanitizer_schedule":freeze["sanitizer_schedule"],
            "wrapper_timeout_seconds":freeze["wrapper_timeout_seconds"],
            "historical_policy":"Twelve manifest FILEs only; current execution binds the new freeze and fresh captured application bytes."}

def parser_inventory():
    archive = ROOT / "third_party/libpg_query/libpg_query-18.1.0.tar.gz"
    need(digest(archive) == PARSER_SHA, "parser source archive changed")
    with tarfile.open(archive) as stream:
        names = {m.name.split("/", 1)[1] for m in stream.getmembers() if m.isfile() and "/" in m.name}
        make = stream.extractfile("libpg_query-18.1.0/Makefile").read().decode()
    need("SRC_FILES := $(wildcard src/*.c src/postgres/*.c) vendor/xxhash/xxhash.c $(UPB_SRC_FILES)" in make,
         "pinned upstream source recipe changed")
    wanted = {n for n in names if n.endswith(".c") and Path(n).parent.as_posix() in {"src", "src/postgres"}}
    wanted.update({"vendor/xxhash/xxhash.c", "vendor/upb/upb.c", "vendor/upb/third_party/utf8_range/utf8_range.c",
                   "protobuf/pg_query.upb_minitable.c"})
    need(len(wanted) == 96 and wanted <= names, "upstream recipe does not derive exactly 96 C units")
    need(PARSER_SHA in read(ROOT / "cmake/LibPgQuery.cmake") and PARSER_SHA in read(ROOT / "dependencies.lock.json"),
         "native recipe/lock no longer enforce archive identity")
    return wanted, make


def source_tuple(row, source):
    match = re.search(r"CMakeFiles/([^/]+)\.dir/", row.get("output", "") or row.get("command", ""))
    need(match is not None, "compile entry has no target identity")
    path = Path(row["file"])
    need(path.is_absolute() and path.is_relative_to(source), "compile source is outside actual source root")
    return match[1], path.relative_to(source).as_posix()


def historical():
    path = V/"ranking-matrix-evidence-audit.json"
    need(digest(path) == PREDECESSOR_MATRIX_SHA, "accepted C02 matrix FILE changed")
    old_audit = data(path)
    need(old_audit.get("accepted") is True and old_audit.get("audit_state") == "accepted_final_matrix" and
         old_audit.get("card") == "C02" and not old_audit.get("errors") and not old_audit.get("pending"), "C02 was not finally accepted")
    need(old_audit["auditor"]["sha256"] == digest(ROOT/old_audit["auditor"]["path"]), "accepted C02 auditor FILE changed")
    capture = V/"c05-c02-predecessor-build-evidence.json"
    need(digest(capture) == PREDECESSOR_CAPTURE_SHA, "C02 retained capture FILE changed")
    retained = data(capture)
    need(retained.get("status") == "captured_pass" and retained.get("predecessor") == "C02verified" and
         retained.get("matrix_sha256") == PREDECESSOR_MATRIX_SHA and retained.get("accepted_generated_files") == 1433
         and retained.get("current_objects") == 856, "retained predecessor scope differs")
    for item in retained["records"]:
        prior = item["original"]; destination = ROOT/item["retained"]
        need(prior not in HISTORICAL_RECORDS and destination == RETAINED_C02/prior, "duplicate/out-of-scope retained mapping")
        if item["accepted_raw_pin"] is True:
            need(item["sha256"] == old_audit["read_evidence_sha256"].get(prior), "retained generated pin lacks accepted raw authority")
        else:
            need(item.get("current_compiled_object") is True and prior.endswith(".o"), "unclassified retained current object")
        HISTORICAL_RECORDS[prior] = item
    need(len(HISTORICAL_RECORDS) == 1433+856 and
         sum(item["accepted_raw_pin"] is True for item in HISTORICAL_RECORDS.values()) == 1433, "retained record population differs")
    folder = RETAINED_C02/"build/release"
    cache = cache_values(read(retained_file("build/release/CMakeCache.txt")))
    need(cache["CMAKE_HOME_DIRECTORY"] == str(ROOT), "retained source root differs")
    old_rows = data(retained_file("build/release/compile_commands.json"))
    old_sources = {source_tuple(row,ROOT) for row in old_rows}
    need(len(old_rows) == len(old_sources) == 214, "retained source inventory is not214")
    additions = {("crown_selection",unit) for unit in SELECTION_UNITS}
    additions.update((target,SELECTION_BRIDGE) for target in ("crown_selection_runtime","crown_selection_runtime_testing"))
    additions.update((target,"tests/unit/"+value[0]+".cpp") for target,value in C05_CONSUMERS.items())
    additions.update((target,"tests/examples/selection_usage.cpp") for target in NEW_OBJECT_TARGETS)
    declared = [(row["target"],row["source"]) for row in csv.DictReader(read(PUBLICATION/"target-inventory.tsv").splitlines(),delimiter="\t")]
    need(len(declared) == len(additions) == 24 and set(declared) == additions and not additions & old_sources,
         "independent24 additions differ from publication")
    expected = old_sources|additions; need(len(expected) == 238, "derived238 inventory differs")
    authority = old_audit["matrix"]["release"]; raw = authority["raw_lasttest"]
    need(raw["path"] == "build/verification/ranking-release-ctest-output.log" and digest(ROOT/raw["path"]) == raw["sha256"],
         "immutable accepted C02 Release LastTest differs")
    baseline = records(read(ROOT/raw["path"]),143)
    reg,props = generated_registration(read(retained_file("build/release/CTestTestfile.cmake")))
    registered = [row["name"] for row in reg]
    need(registered == authority["registered_test_names"] == [row["name"] for row in baseline], "old143 registration/outcome order differs")
    out = {}
    for block in baseline:
        out[block["name"]] = {"command":command_normalized(block["argv"],ROOT,ROOT/"build/release"),
                             "rows":output_rows(block["output"],block["name"],ROOT,ROOT/"build/release","C02 release")}
        need(out[block["name"]]["rows"]["comparison"] == authority["tests"][block["name"]]["rows"]["comparison"],
             "old numeric parser disagrees with accepted C02 authority")
    properties = {}
    for name in CONFIGS:
        prior_folder = "clang-debug" if name == "clang" else "release" if name == "clean-source" else name
        tests,props = generated_registration(read(retained_file("build/"+prior_folder+"/CTestTestfile.cmake")))
        need([t["name"] for t in tests] == registered, "old configuration registration order differs")
        properties[name] = {test:{k:v for k,v in values.items() if k != "_BACKTRACE_TRIPLES"} for test,values in props.items()}
    old_approval = old_audit["allocation_review_record"]
    need(old_approval["sha256"] == "612f174cf314ab5a64629d91f35049bd0ccc6440b60da7ab483c3211a9aee175" and
         digest(ROOT/old_approval["path"]) == old_approval["sha256"], "historical narrow Clang approval FILE changed")
    return {"tests":out,"ordered_names":registered,"properties":properties,"expected_sources":expected,
            "retained_artifacts":len(HISTORICAL_RECORDS),"source_inventory_additions":sorted(additions),
            "predecessor_capture":{"path":label(capture),"sha256":PREDECESSOR_CAPTURE_SHA},
            "raw_lasttest":raw,"historical_allocation_approval":{**old_approval,"applies_to_current_differences":False},
            "note":"All143 prior commands/settings/numeric rows retained. Immutable accepted LastTest is bound separately from retained build metadata. No old source-manifest entries are checked."}


def retained_file(original):
    need(original in HISTORICAL_RECORDS, "required retained predecessor artifact absent: "+original)
    item = HISTORICAL_RECORDS[original]; path = ROOT/item["retained"]
    need(digest(path) == item["sha256"] and path.stat().st_size == item["bytes"], "retained predecessor bytes changed: "+original)
    return path

def generated_registration(text):
    tests, properties = [], {}
    for line in text.splitlines():
        if line.startswith("add_test("):
            match = re.fullmatch(r"add_test\(\[=\[(\S+)\]=\] (.*)\)", line)
            need(match is not None, "unrecognized generated CTest registration line")
            tests.append({"name": match[1], "argv": shlex.split(match[2])})
        elif line.startswith("set_tests_properties("):
            match = re.fullmatch(r"set_tests_properties\(\[=\[(\S+)\]=\] PROPERTIES\s+(.*)\)", line)
            need(match is not None, "unrecognized generated CTest property line")
            words = shlex.split(match[2])
            need(len(words) % 2 == 0 and match[1] not in properties, "duplicate/invalid CTest properties")
            properties[match[1]] = dict(zip(words[::2], words[1::2]))
    return tests, properties


def registration(folder, source, build, freeze):
    tests,properties = generated_registration(read(folder/"CTestTestfile.cmake"))
    names = [t["name"] for t in tests]
    need(len(names) == len(set(names)) == 158 and sorted(names) == freeze["test_names"] and names == freeze["ordered_names"],
         "generated158 names/order differ")
    for test in tests:
        test["command"] = command_normalized(test["argv"],source,build)
        need("docs/verification" not in " ".join(test["argv"]), "proposal path in native test argv")
        if test["name"] in NEW_TESTS:
            props = properties.get(test["name"],{})
            timeout = "7200" if test["name"] in {"selection_exception","selection_normalized_exception","selection_publication_fault_independent"} else "900"
            need(props.get("LABELS") == "C05" and props.get("TIMEOUT") == timeout, "new C05 timeout/label differs")
            wanted = [str(build/("crown_"+test["name"]+"_test"))]
            if test["name"] in {"selection_public_independent","selection_cache_independent","selection_resources_independent","selection_publication_fault_independent"}:
                wanted.append(str(source))
            need(test["argv"] == wanted, "new C05 test argv differs")
    return tests,properties

def include_arguments(words, build):
    result = []
    index = 1
    while index < len(words):
        word = words[index]
        if word in {"-I", "-isystem", "-iquote", "-idirafter"}:
            need(index + 1 < len(words), "truncated include argument")
            value = words[index + 1]
            index += 2
        elif word.startswith("-I") and len(word) > 2:
            value = word[2:]
            index += 1
        elif any(word.startswith(flag) for flag in ("-isystem", "-iquote", "-idirafter")):
            raise AuditError("unsupported concatenated include spelling: " + word)
        else:
            index += 1
            continue
        path = Path(value)
        result.append(path if path.is_absolute() else build / path)
    return result


def clean_dependency_folder(source, build, expected_sources, compile_database):
    manifest = CLEAN_MANIFESTS.get("clean-source")
    need(manifest is not None and manifest.get("dependency_capture_complete") is True and
         manifest.get("dependency_inputs_stable_before_cleanup") is True and
         manifest.get("dependency_capture_phase") == "after_successful_build_before_ctest", "direct clean dependency capture incomplete")
    rows = manifest["dependency_records"]
    need(len(rows) == 238 and {(r["target"],r["source"]) for r in rows} == expected_sources, "clean direct row population differs")
    root = V/"selection-clean-artifacts"
    db = manifest["compile_database_pin"]
    need(db["source"] == str(build/"compile_commands.json") and db["retained"] == label(root/"compile_commands.json")
         and db["sha256"] == digest(compile_database), "clean dependency/database binding differs")
    return root

def dependency_audit(name, folder, source, build, expected_sources, build_text, compile_rows):
    dependency_root = clean_dependency_folder(source,build,expected_sources,folder/"compile_commands.json") if name == "clean-source" else folder
    commands = {source_tuple(row,source):row.get("arguments") or shlex.split(row["command"]) for row in compile_rows}
    compiled = {}
    for line in build_text.splitlines():
        if " -c " not in line or "CMakeFiles/" not in line or " -o " not in line:
            continue
        words = shlex.split(line)
        if "-c" not in words or "-o" not in words:
            continue
        unit = Path(words[words.index("-c")+1]); out = Path(words[words.index("-o")+1])
        out = out if out.is_absolute() else build/out
        if not unit.is_relative_to(source) or not out.is_relative_to(build):
            continue
        match = re.fullmatch(r"CMakeFiles/([^/]+)\.dir/(.+)\.o",out.relative_to(build).as_posix())
        if match is None:
            continue
        identity = (match[1],unit.relative_to(source).as_posix())
        need(identity in expected_sources and match[2] == identity[1] and identity not in compiled, "unexpected/repeated actual C++ compile")
        stripped, switches = [], {}
        index = 0
        while index < len(words):
            word = words[index]
            if word in {"-MD","-MT","-MF"}:
                need(word not in switches, "duplicate compiler dependency switch")
                if word == "-MD":
                    switches[word] = True; index += 1
                else:
                    need(index+1 < len(words), "truncated compiler dependency switch")
                    switches[word] = words[index+1]; index += 2
            else:
                stripped.append(word); index += 1
        rel = out.relative_to(build).as_posix()
        need(switches == {"-MD":True,"-MT":rel,"-MF":rel+".d"} and stripped == commands[identity],
             "actual compiler argv/dependency switches differ from database")
        compiled[identity] = line
    additions = {(r["target"],r["source"]) for r in data(V/"selection-execution-freeze.json")["added_compile_units"]}
    wanted_fresh = expected_sources if name == "clean-source" else additions
    need(set(compiled) == wanted_fresh and len(compiled) == (238 if name == "clean-source" else 24),
         "observed fresh compiler population differs from expected238/24")
    cached = expected_sources-set(compiled)
    need(len(cached) == (0 if name == "clean-source" else 214), "observed unchanged population differs")
    frozen = data(V/"selection-execution-freeze.json")["execution_file_sha256"]
    clean = CLEAN_MANIFESTS.get("clean-source") if name == "clean-source" else None
    clean_rows = {(r["target"],r["source"]):r for r in clean["dependency_records"]} if clean else {}
    clean_inputs = clean["dependency_inputs"] if clean else {}
    observed_clean_inputs = set()
    actual_inputs = {}; files = []; project_scopes = {}; aliases = {}
    for target,unit in sorted(expected_sources):
        identity = (target,unit); rel = f"CMakeFiles/{target}.dir/{unit}.o.d"
        raw = read(dependency_root/rel); text = raw.replace("\\\n"," ")
        need(text.count(":") == 1, "unsupported/ambiguous Make dependency rule: "+rel)
        left,right = text.split(":",1); lhs = shlex.split(left)
        need(len(lhs) == 1, "dependency target population differs")
        output = Path(lhs[0]); output = output if output.is_absolute() else build/output
        need(output == build/rel.removesuffix(".d"), "dependency target differs from target/source")
        words = shlex.split(right)
        row = clean_rows.get(identity)
        if row:
            need(row["dependency"] == str(build/rel) and row["retained"] == label(dependency_root/rel) and
                 row["sha256"] == digest(dependency_root/rel) and row["arguments"] == commands[identity] and
                 row["directory"] == str(build) and row["object"] == str(output) and
                 re.fullmatch(r"[0-9a-f]{64}",row["object_sha256"]), "clean per-unit dependency/argv/object binding differs")
            need([item["compiler_spelling"] for item in row["included_inputs"]] == words, "clean included-input spelling population differs")
        project = []; spellings = []; canonical_deps = []
        for index,word in enumerate(words):
            observed = Path(word); observed = observed if observed.is_absolute() else build/observed
            if row:
                mapping = row["included_inputs"][index]
                canonical = Path(mapping["canonical_input"])
                need(mapping["observed_path"] == str(observed) and canonical.is_absolute(), "clean raw dependency spelling mapping differs")
                if not canonical.is_relative_to(source):
                    need(canonical == observed.resolve(), "external clean dependency canonical alias changed")
                else:
                    need(canonical == observed.resolve(), "clean lexical source/generated alias differs")
                need(str(canonical) in clean_inputs, "clean dependency input missing unique map")
                pin = clean_inputs[str(canonical)]; observed_clean_inputs.add(str(canonical))
            else:
                canonical = observed.resolve(); pin = None
            need(observed.is_relative_to(source) == canonical.is_relative_to(source.resolve()), "dependency crosses source boundary")
            need(not any(part in str(observed) or part in str(canonical) for part in
                         ("docs/verification","/tmp/crown-c01-","/tmp/crown-c02-","/tmp/crown-c05-")),
                 "proposal/cache dependency in native compilation")
            key = str(canonical)
            need(str(observed) not in aliases or aliases[str(observed)] == key, "contradictory canonical dependency alias")
            aliases[str(observed)] = key
            if canonical.is_relative_to(build):
                scope = "generated_build"; current = folder/canonical.relative_to(build)
                if pin:
                    need(pin.get("scope") == scope and pin.get("build_relative") == canonical.relative_to(build).as_posix() and
                         pin.get("retained") == label(current), "clean generated include scope/retention differs")
                expected = pin["sha256"] if pin else None
            elif canonical.is_relative_to(source.resolve()) and not canonical.relative_to(source.resolve()).as_posix().startswith("build/"):
                scope = "snapshot_source" if clean else "project_source"
                relative = canonical.relative_to(source.resolve()).as_posix()
                expected = frozen.get(relative); need(expected is not None, "source dependency outside frozen execution: "+relative)
                current = ROOT/relative
                if pin:
                    need(pin.get("scope") == "snapshot_source" and pin.get("source_relative") == relative and
                         pin.get("sha256") == pin.get("frozen_sha256") == expected, "clean source include differs from freeze")
                else:
                    need((ROOT/observed.relative_to(source)).resolve() == current.resolve(), "project alias canonicalization differs")
                project.append(relative)
            else:
                scope = "external_system"
                need(not clean or not canonical.is_relative_to(ROOT), "working-tree dependency leaked into clean source")
                need(not canonical.is_relative_to(ROOT) or canonical.is_relative_to(ROOT/"build/toolchains"), "unclassified cached dependency")
                current = canonical; expected = pin["sha256"] if pin else None
                if pin: need(pin.get("scope") == scope, "clean system include scope differs")
            actual_hash = digest(current)
            need(expected is None or actual_hash == expected, "actual include bytes differ from recorded/frozen identity: "+key)
            item = {"scope":scope,"path":label(current),"sha256":actual_hash}
            if scope in {"snapshot_source","project_source"}: item["source_relative"] = project[-1]
            need(key not in actual_inputs or actual_inputs[key] == item, "canonical included input has conflicting identity")
            actual_inputs[key] = item; canonical_deps.append(canonical)
            spellings.append({"compiler_spelling":word,"canonical_input":key,"scope":scope,"sha256":actual_hash})
        need(source/unit in canonical_deps, "dependency rule omits its source")
        json_headers = [p for word,p in zip(words,canonical_deps) if "nlohmann" in Path(word).parts or "nlohmann" in p.parts]
        wanted_json = source/("third_party/nlohmann/upstream/nlohmann/json.hpp" if target == "crown_json_upstream_control_test" else "third_party/nlohmann/json.hpp")
        need(not json_headers or set(json_headers) == {wanted_json}, "wrong/mixed active/upstream JSON dependency")
        if target in {"crown_json_cleanup_test","crown_json_upstream_control_test"}:
            need(json_headers and set(project) == {unit,wanted_json.relative_to(source).as_posix()}, "isolated JSON probe include graph differs")
        project_scopes[identity] = sorted(set(project))
        files.append({"target":target,"source":unit,"dependency_file":label(dependency_root/rel),
                      "dependency_sha256":digest(dependency_root/rel),"source_dependencies":sorted(set(project)),
                      "included_inputs":spellings,"dependency_count":len(words)})
    if clean:
        need(observed_clean_inputs == set(clean_inputs), "clean included-input map has extra or missing records")
    unchanged = []
    if cached:
        old_folder_name = "clang-debug" if name == "clang" else name
        prefix = "build/"+old_folder_name
        old_rows = data(retained_file(prefix+"/compile_commands.json"))
        prior = {source_tuple(row,ROOT):row.get("arguments") or shlex.split(row["command"]) for row in old_rows}
        captured = data(V/"c05-native-integration-start.json")["baseline_entry_pins"]
        canonical_baseline = {}
        for path,expected in captured.items():
            absolute = Path(path) if Path(path).is_absolute() else ROOT/path
            key = str(absolute.resolve())
            need(key not in canonical_baseline or canonical_baseline[key] == expected, "fresh baseline canonical alias conflict")
            canonical_baseline[key] = expected
        for identity in sorted(cached):
            target,unit = identity
            need(identity in prior and command_normalized(prior[identity],ROOT,ROOT/prefix) ==
                 command_normalized(commands[identity],source,build), "unchanged unit compile argv changed")
            obj_rel = f"CMakeFiles/{target}.dir/{unit}.o"; dep_rel = obj_rel+".d"
            old_object = retained_file(prefix+"/"+obj_rel); old_dep = retained_file(prefix+"/"+dep_rel)
            current_object = build/obj_rel
            need(digest(current_object) == digest(old_object), "unchanged unit object bytes differ from captured C02 object")
            need(digest(folder/dep_rel) == digest(old_dep), "unchanged unit compiler dependency rule changed")
            for rel in project_scopes[identity]:
                need(digest(ROOT/rel) == frozen[rel] == canonical_baseline.get(str((ROOT/rel).resolve())),
                     "unchanged unit has changed project dependency: "+rel)
            unchanged.append({"target":target,"source":unit,
                              "object":{"path":label(current_object),"sha256":digest(current_object)},
                              "retained_object":{"path":label(old_object),"sha256":digest(old_object)},
                              "retained_dependency":{"path":label(old_dep),"sha256":digest(old_dep)},
                              "normalized_compile_argv_equal":True,"project_dependencies":project_scopes[identity],
                              "historical_system_header_bytes_compared":False,"historical_generated_header_bytes_compared":False})
    provenance = {"status":"audited_pass","unit_count":len(cached),
                  "capture":{"path":"build/verification/c05-c02-predecessor-build-evidence.json","sha256":PREDECESSOR_CAPTURE_SHA},
                  "object_bytes_equal_to_capture":True if cached else None,
                  "normalized_compile_argv_equal":True if cached else None,
                  "frozen_project_dependency_bytes_equal":True if cached else None,
                  "historical_system_header_bytes_compared":False,"historical_generated_header_bytes_compared":False}
    return {"status":"audited_pass","direct_dependency_rows":True,"files":files,"actual_inputs":actual_inputs,
            "actual_recompiled_units":[list(unit) for unit in sorted(compiled)],
            "actual_compile_argv_matches_database":True,
            "actual_compile_commands":[{"target":t,"source":u,"command":compiled[t,u]} for t,u in sorted(compiled)],
            "unchanged_units_not_recompiled":unchanged,"cached_predecessor_provenance":provenance,
            "current_system_inputs":{k:v for k,v in actual_inputs.items() if v["scope"] == "external_system"},
            "current_generated_inputs":{k:v for k,v in actual_inputs.items() if v["scope"] == "generated_build"},
            "scope":"All direct rules and actual input hashes checked; 24fresh/214unchanged or238fresh observed. Historical generated/system bytes unavailable; current observations do not fill that gap."}

def compile_audit(name, folder, source, build, expected_sources, make_original, configure_text, build_text, freeze):
    rows = data(folder / "compile_commands.json")
    actual = [source_tuple(row, source) for row in rows]
    need(len(rows) == len(set(actual)) == 238 and set(actual) == expected_sources, "actual 238-entry target/source inventory differs")
    need({(item["target"], item["source"]) for item in freeze["expected_compile_units"]} == expected_sources,
         "freeze and independently derived 238-entry inventory disagree")
    cache = cache_values(read(folder / "CMakeCache.txt"))
    need(cache.get("CMAKE_HOME_DIRECTORY") == str(source), "source root/cache binding differs")
    need(cache.get("CROWN_WARNINGS_AS_ERRORS") == "ON", "warnings-as-errors disabled")
    need(cache.get("CROWN_SANITIZERS") == ("ON" if name == "sanitize" else "OFF"), "sanitizer cache mode differs")
    need(cache.get("CMAKE_BUILD_TYPE") == ("Release" if name in {"release", "clean-source"} else "Debug"), "CMake build type differs")
    compiler = cache.get("CMAKE_CXX_COMPILER")
    c_compiler = cache.get("CMAKE_C_COMPILER")
    held = freeze["toolchains"]["release" if name == "clean-source" else name]["values"]
    need(compiler == held["CMAKE_CXX_COMPILER"] and c_compiler == held["CMAKE_C_COMPILER"],
         "actual compilers differ from held toolchain cache")
    family = "Clang" if name == "clang" else "GNU"
    need(compiler and (("clang" in Path(compiler).name) == (name == "clang")), "C++ compiler family/path inconsistent")
    need(c_compiler and (("clang" in Path(c_compiler).name) == (name == "clang")), "C compiler family/path inconsistent")
    by_target = collections.defaultdict(list)
    compile_macros = {}
    includes_by_target = {}
    old_release_rows = data(retained_file("build/release/compile_commands.json"))
    planner_macro_targets = {source_tuple(row, ROOT)[0] for row in old_release_rows
                             if "-DCROWN_PLANNER_TESTING" in (row.get("arguments") or shlex.split(row["command"]))}
    for row, identity in zip(rows, actual):
        target, unit = identity
        words = row.get("arguments") or shlex.split(row["command"])
        need(row.get("directory") == str(build) and not any(w.startswith("@") for w in words), "compile directory/response-file differs")
        need(words[0] == compiler and FLAGS <= set(words) and "-std=c++23" in words, "compiler/strict C++23 flags differ: " + target)
        need([w for w in words if w.startswith("-std=")] == ["-std=c++23"], "C++ standard overridden")
        definitions = {word for word in words if word.startswith("-D")}
        need(definitions <= {"-DNDEBUG", "-DCROWN_RUNTIME_TESTING", "-DCROWN_PLANNER_TESTING",
                             "-DCROWN_STATISTICS_ACCEPTANCE", "-DCROWN_STATISTICS_LIFO"}, "unreviewed compile macro: " + target)
        need("-w" not in words and not any(w.startswith("-Wno-") for w in words), "project warning suppression: " + target)
        need(not any("docs/verification" in w or "/tmp/crown-c01" in w or "/tmp/crown-c02" in w or "/tmp/crown-c05" in w or "/tmp/crown-o07" in w for w in words),
             "proposal path in native compile command")
        sanitize = {"-fsanitize=address,undefined", "-fno-omit-frame-pointer"}
        need(sanitize <= set(words) if name == "sanitize" else not any(w.startswith("-fsanitize") for w in words),
             "sanitizer instrumentation differs: " + target)
        need(not any(w.startswith("-fno-sanitize") for w in words), "sanitizer suppression in project compilation")
        need(("-O3" in words and "-DNDEBUG" in words) if name in {"release", "clean-source"} else "-g" in words,
             "actual build optimization/debug flags differ: " + target)
        optimization = [word for word in words if re.fullmatch(r"-O(?:[0-9]+|g|s|z|fast)", word)]
        need(optimization == ["-O3"] if name in {"release", "clean-source"} else optimization in ([], ["-O0"]),
             "unexpected optimization override: " + target)
        includes = include_arguments(words, build)
        includes_by_target.setdefault(target, []).append([str(p) for p in includes])
        original_root = source / "third_party/nlohmann/upstream"
        active_root = source / "third_party"
        if target == "crown_json_upstream_control_test":
            need(includes == [original_root], "upstream control include root is not isolated")
        else:
            need(active_root in includes and not any(p.is_relative_to(original_root) for p in includes),
                 "active JSON include missing or upstream header root leaked: " + target)
        runtime_macro = any(w == "-DCROWN_RUNTIME_TESTING" or w.startswith("-DCROWN_RUNTIME_TESTING=") for w in words)
        need(("-DCROWN_PLANNER_TESTING" in words) == (target in planner_macro_targets), "planner testing macro propagation changed")
        compile_macros.setdefault(target, set()).add(runtime_macro)
        if target in CONSUMERS:
            need(runtime_macro == (CONSUMERS[target][1] == "testing"), "consumer macro variant differs: " + target)
            ndebug = [w for w in words if w == "-UNDEBUG" or w == "-DNDEBUG" or w.startswith("-DNDEBUG=")]
            need(ndebug and ndebug[-1] == "-UNDEBUG",
                 "numeric assertions disabled: " + target)
        acceptance = "-DCROWN_STATISTICS_ACCEPTANCE" in words
        lifo = "-DCROWN_STATISTICS_LIFO" in words
        need(acceptance == (target in POLICY_TARGETS) and lifo == (target in POLICY_TARGETS and "_lifo_" in target),
             "statistics acceptance/order macro leaked or absent: " + target)
        by_target[target].append(unit)
    for target, units, testing in (
        ("crown_runtime", RUNTIME_UNITS, False), ("crown_runtime_testing", RUNTIME_UNITS, True),
        ("crown_explain", REPORT_UNITS, False), ("crown_explain_testing", REPORT_UNITS, True),
        ("crown_ranking", RANKING_UNITS, False),
        ("crown_ranking_runtime", {BRIDGE_UNIT}, False), ("crown_ranking_runtime_testing", {BRIDGE_UNIT}, True),
        ("crown_ranking_usage_production", {"tests/examples/ranking_usage.cpp"}, False),
        ("crown_ranking_usage_testing", {"tests/examples/ranking_usage.cpp"}, True),
        ("crown_selection", SELECTION_UNITS, False),
        ("crown_selection_runtime", {SELECTION_BRIDGE}, False),
        ("crown_selection_runtime_testing", {SELECTION_BRIDGE}, True),
        ("crown_selection_usage_production", {"tests/examples/selection_usage.cpp"}, False),
        ("crown_selection_usage_testing", {"tests/examples/selection_usage.cpp"}, True),
    ):
        need(set(by_target[target]) == units and len(by_target[target]) == len(units), "runtime/report unit set differs: " + target)
        need(compile_macros[target] == {testing}, "runtime/report macro differs: " + target)
    links = {}
    for target in by_target:
        path = folder / "CMakeFiles" / (target + ".dir") / "link.txt"
        if target in OBJECT_TARGETS:
            need(not path.exists(), "compile-only guide acquired link recipe")
            links[target] = {"kind": "object_library", "libraries": [], "runtime_testing": compile_macros[target] == {True}}
            continue
        words = shlex.split(read(path))
        objects = [Path(w) if Path(w).is_absolute() else build / w for w in words if w.endswith(".o")]
        need(len(objects) == len(by_target[target]) and set(objects) == {
            build / f"CMakeFiles/{target}.dir/{unit}.o" for unit in by_target[target]}, "link/archive object inventory differs: " + target)
        for word in words:
            if word.endswith(".a"):
                archive = Path(word) if Path(word).is_absolute() else build / word
                allowed = build / archive.name if archive.name.startswith("libcrown_") else build / "_deps/libpg_query/libpg_query-18.1.0/libpg_query.a"
                need(archive == allowed, "cached/external C++ archive in native link recipe: " + target)
            need("docs/verification" not in word and "/tmp/crown-c02" not in word and "/tmp/crown-c05" not in word, "proposal path in native link")
        libraries = {Path(w).name for w in words if w.endswith(".a")}
        # An archive recipe names its own output; that is not a dependency.
        libraries.discard("lib" + target + ".a")
        need(not {"libcrown_runtime.a", "libcrown_runtime_testing.a"} <= libraries, "mixed runtime linkage: " + target)
        need(not {"libcrown_explain.a", "libcrown_explain_testing.a"} <= libraries, "mixed report linkage: " + target)
        need(not {"libcrown_ranking_runtime.a", "libcrown_ranking_runtime_testing.a"} <= libraries, "mixed ranking bridge linkage")
        need(not {"libcrown_selection_runtime.a","libcrown_selection_runtime_testing.a"} <= libraries, "mixed selection bridge linkage")
        testing = "libcrown_runtime_testing.a" in libraries
        production = "libcrown_runtime.a" in libraries
        if testing or production:
            need(compile_macros[target] == {testing}, "consumer compile/link ABI mismatch: " + target)
        if "libcrown_explain_testing.a" in libraries:
            need(testing and not production, "testing report linked wrong runtime")
        if "libcrown_explain.a" in libraries:
            need(production and not testing, "production report linked wrong runtime")
        if target.startswith("crown_statistics_runtime_only_"):
            need((testing or production) and not libraries & {"libcrown_explain.a", "libcrown_explain_testing.a",
                  "libcrown_query_explain.a", "libcrown_reference.a"}, "runtime-only link gained forbidden library")
        if target == "crown":
            need({"libcrown_runtime.a", "libcrown_explain.a"} <= libraries and not testing, "production CLI linkage differs")
        if target == "crown_query_explain_test":
            need("libcrown_query_explain.a" in libraries and not testing and not production, "query-only test gained runtime dependency")
        ranking_archives = {"libcrown_ranking.a", "libcrown_ranking_runtime.a", "libcrown_ranking_runtime_testing.a"}
        if not target.startswith(("crown_ranking","crown_selection")):
            need(not libraries & ranking_archives, "existing native target gained unsolicited ranker dependency: " + target)
        if target in C02_CONSUMERS:
            variant = C02_CONSUMERS[target][1]
            need(not libraries & {"libcrown_explain.a", "libcrown_explain_testing.a", "libcrown_query_explain.a", "libcrown_reference.a"},
                 "ranking/JSON consumer acquired report/reference linkage")
            if variant in {"production", "testing"}:
                bridge = "libcrown_ranking_runtime_testing.a" if variant == "testing" else "libcrown_ranking_runtime.a"
                need(bridge in libraries and "libcrown_ranking.a" in libraries and (testing if variant == "testing" else production),
                     "ranker consumer lacks matching opt-in bridge/runtime")
            elif variant == "pure":
                need("libcrown_ranking.a" in libraries and not production and not testing and
                     not libraries & {"libcrown_ranking_runtime.a", "libcrown_ranking_runtime_testing.a"}, "pure consumer gained runtime")
            else:
                need(not libraries, "header-only JSON control links a project/parser archive")
        selection_archives = {"libcrown_selection.a","libcrown_selection_runtime.a","libcrown_selection_runtime_testing.a"}
        if not target.startswith("crown_selection"):
            need(not libraries & selection_archives, "prior target gained unsolicited selection dependency: "+target)
        if target in C05_CONSUMERS:
            variant = C05_CONSUMERS[target][1]
            need(not libraries & {"libcrown_explain.a","libcrown_explain_testing.a","libcrown_query_explain.a","libcrown_reference.a"},
                 "selection consumer gained report/reference dependency")
            need({"libcrown_selection.a","libcrown_ranking.a"} <= libraries, "selection/ranking pure closure absent")
            if variant in {"production","testing"}:
                suffix = "_testing" if variant == "testing" else ""
                need({"libcrown_selection_runtime"+suffix+".a","libcrown_ranking_runtime"+suffix+".a"} <= libraries
                     and (testing if variant == "testing" else production), "selection bridge/runtime ABI mismatch")
            else:
                need(not production and not testing and not libraries & {
                    "libcrown_selection_runtime.a","libcrown_selection_runtime_testing.a",
                    "libcrown_ranking_runtime.a","libcrown_ranking_runtime_testing.a"}, "pure selection consumer gained runtime")
        # Executables have an -o link; static archive recipes do not.
        if name == "sanitize" and "-o" in words:
            need("-fsanitize=address,undefined" in words, "sanitizer missing on executable link: " + target)
        links[target] = {"libraries": sorted(libraries), "runtime_testing": testing, "runtime_production": production,
                         "object_sources": sorted(by_target[target]), "recipe": label(path)}
    make_path = folder / "_deps/libpg_query/libpg_query-18.1.0/Makefile"
    need(read(make_path) == make_original, "retained vendor Makefile changed")
    need("-Wall -Wno-unused-function -Wno-unused-value -Wno-unused-variable" in make_original and
         "@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<" in make_original, "upstream vendor warning/compile policy changed")
    if name == "clean-source":
        need(f"The C compiler identification is {family} " in configure_text and
             f"The CXX compiler identification is {family} " in configure_text, "clean compiler identification missing")
        parser_commands = [line for line in build_text.splitlines()
                           if re.search(r"/(?:gmake|make) -C .*libpg_query-18\.1\.0 build CC=", line)]
        need(len(parser_commands) == 1, "clean actual vendor make invocation absent/ambiguous")
        parser_words = shlex.split(parser_commands[0])
        need("CC=" + c_compiler in parser_words and not any("fsanitize" in x for x in parser_words),
             "clean vendor compiler/instrumentation differs")
        parser_evidence = {"actual_make_command": parser_commands[0],
                           "generated_config_retained": False, "expanded_per_C_unit_argv_retained": False}
        identities = re.findall(r"^-- The (C|CXX) compiler identification is (\S+) (\S+)$", configure_text, re.M)
        need(len(identities) == 2 and {entry[0] for entry in identities} == {"C", "CXX"},
             "clean compiler version identity missing or duplicated")
        compiler_metadata = {language: {"id": identifier, "version": version} for language, identifier, version in identities}
    else:
        cfg = dict(line.split("=", 1) for line in read(folder / "_deps/libpg_query-build-config.txt").splitlines() if "=" in line)
        need(cfg.get("compiler") == c_compiler and cfg.get("compiler_id") == family and cfg.get("compiler_version"),
             "vendor C compiler binding differs")
        need(cfg.get("sanitizers") == ("ON" if name == "sanitize" else "OFF"), "vendor sanitizer configuration differs")
        recipe = read(folder / "CMakeFiles/_crown_pg_query_build.dir/build.make")
        need("CC=" + c_compiler in recipe and "libpg_query-18.1.0 build" in recipe, "generated vendor source-build recipe missing")
        need(("-fsanitize=address,undefined" in recipe and "-fno-omit-frame-pointer" in recipe) if name == "sanitize"
             else "-fsanitize=" not in recipe, "generated vendor instrumentation recipe differs")
        parser_evidence = {"configuration": cfg, "generated_config_retained": True,
                           "expanded_per_C_unit_argv_retained": False}
        compiler_metadata = {}
        for language, executable in (("C", c_compiler), ("CXX", compiler)):
            candidates = list((folder / "CMakeFiles").glob("*/CMake" + language + "Compiler.cmake"))
            need(len(candidates) == 1, "compiler metadata path absent/ambiguous: " + language)
            metadata = read(candidates[0])
            fields = {}
            for suffix in ("", "_ID", "_VERSION"):
                matches = re.findall(r'set\(CMAKE_' + language + r'_COMPILER' + suffix + r' "([^"]*)"\)', metadata)
                need(len(matches) == 1, "compiler metadata field absent/ambiguous: " + language + suffix)
                fields[suffix or "_PATH"] = matches[0]
            need(fields["_PATH"] == executable and fields["_ID"] == family and fields["_VERSION"],
                 "compiler metadata differs from actual compile/cache identity")
            compiler_metadata[language] = {"id": fields["_ID"], "version": fields["_VERSION"], "path": fields["_PATH"]}
    old_folder = RETAINED_C02 / "build" / ("clang-debug" if name == "clang" else "release" if name == "clean-source" else name)
    for language in ("C", "CXX"):
        old_metadata = list((old_folder / "CMakeFiles").glob("*/CMake" + language + "Compiler.cmake"))
        need(len(old_metadata) == 1, "held compiler metadata missing/ambiguous")
        old_text = read(retained_file(old_metadata[0].relative_to(RETAINED_C02).as_posix()))
        for suffix, field in (("_ID", "id"), ("_VERSION", "version")):
            values = re.findall(r'set\(CMAKE_' + language + r'_COMPILER' + suffix + r' "([^"]*)"\)', old_text)
            need(len(values) == 1 and compiler_metadata[language][field] == values[0], "actual compiler version changed")
    dependencies = dependency_audit(name, folder, source, build, expected_sources, build_text, rows)
    return {"raw_cmake_entries": len(rows), "runtime_units_per_variant": 14, "report_units_per_variant": 6,
            "source_inventory": [{"target": t, "source": s} for t, s in sorted(actual)],
            "compiler": compiler, "c_compiler": c_compiler, "compiler_metadata": compiler_metadata,
            "ranking_units": 3, "bridge_units_per_variant": 1, "selection_units": 5, "selection_bridge_units_per_variant": 1,
            "include_arguments": includes_by_target, "dependencies": dependencies,
            "links": links, "vendor": parser_evidence}

def stable(summary):
    need(summary.get("terminal") is True and summary.get("status") == "passed" and
         summary.get("freeze_sha256") == FREEZE_SHA and summary.get("identity_guards_stable") is True,
         "terminal status/freeze/identity guards differ")
    need(summary.get("source_stable") is True and
         summary.get("fingerprint_before") == NATIVE["sha256"] == summary.get("fingerprint_after") and
         summary.get("native_inputs_before") == NATIVE == summary.get("native_inputs_after") and
         summary.get("execution_inputs_before") == EXECUTION == summary.get("execution_inputs_after"), "source before/after changed")

def expected_commands(name):
    if name == "clang":
        return [["cmake", "-S", ".", "-B", "build/clang-debug"],
                ["cmake", "--build", "build/clang-debug", "--parallel", "2", "--verbose"],
                ["ctest", "--test-dir", "build/clang-debug", "--output-on-failure", "--verbose"]]
    return [["cmake", "--preset", name], ["cmake", "--build", "--preset", name, "--parallel", "2", "--verbose"],
            ["ctest", "--preset", name, "--output-on-failure", "--verbose"]]


def clean_artifacts(summary, text):
    path = V/"selection-clean-artifacts-manifest.json"
    need(summary.get("clean_artifacts_manifest") == label(path) and
         summary.get("clean_artifacts_manifest_sha256") == digest(path), "outer clean manifest binding differs")
    manifest = data(path)
    need(manifest.get("terminal") is True and manifest.get("status") == "passed" and manifest.get("exit_code") == 0 and
         manifest.get("freeze_sha256") == FREEZE_SHA and manifest.get("source_stable") is True and
         manifest.get("temporary_removed") is True and manifest.get("identity_guards_stable") is True, "clean artifact terminal status failed")
    for field in ("source_before","snapshot_inputs","snapshot_inputs_after_tests","source_after"):
        need(manifest.get(field) == {"native":NATIVE,"execution":EXECUTION}, "clean "+field+" differs")
    need(manifest.get("original_helper") == "tools/verify_clean_build.py" and
         manifest.get("original_helper_sha256") == digest(ROOT/"tools/verify_clean_build.py") and
         manifest.get("adapter_sha256") == digest(Path("/tmp/crown-selection-clean-evidence.py")), "clean helper identity differs")
    source = Path(manifest["snapshot_source"]); build = source/"build"
    need(str(source).startswith("/tmp/crown-clean-source-") and source.name == "source" and
         not source.parent.exists() and summary.get("temporary_path") == str(source.parent) and summary.get("temporary_removed") is True,
         "clean temporary source scope/removal differs")
    expected = [["cmake","-S",str(source),"-B",str(build),"-DCMAKE_BUILD_TYPE=Release"],
                ["cmake","--build",str(build),"--parallel","2"],["ctest","--test-dir",str(build),"--output-on-failure"]]
    commands = manifest["commands"]; need(len(commands) == 3, "clean three stages absent")
    for item,original,phase,ceiling in zip(commands,expected,("configure","build","test"),(7200,7200,86400)):
        executed = original+([] if phase == "configure" else ["--verbose"])
        need(item.get("original") == original and item.get("executed") == executed and item.get("phase") == phase and
             item.get("status") == "passed" and item.get("exit_code") == 0 and item.get("timeout_seconds") == ceiling,
             "clean actual command/status/ceiling differs")
        need("$ "+shlex.join(executed) in text, "clean actual command absent from raw log")
    folder = V/"selection-clean-artifacts"; seen = set()
    for item in manifest["retained"]:
        retained = ROOT/item["retained"]
        need(retained.is_relative_to(folder) and retained not in seen and
             Path(item["source"]) == build/retained.relative_to(folder), "clean retained mapping/duplicate differs")
        need(digest(retained) == item["sha256"], "retained clean artifact changed")
        seen.add(retained)
    need(seen == {p for p in folder.rglob("*") if p.is_file()}, "clean manifest does not cover exact retained files")
    symbols = V/"selection-clean-source-symbols.json"
    need(manifest.get("symbols_manifest") == label(symbols) and manifest.get("symbols_manifest_sha256") == digest(symbols), "clean symbol manifest binding differs")
    CLEAN_MANIFESTS["clean-source"] = manifest
    return folder,source,build

def legacy_numeric_contract(test, output):
    fixed = {
        "ranking_binding": "C02 binding: exact predecessor bytes and pre-allocation caps passed\n",
        "ranking_pure_link": "C02 pure link: no runtime/report archive\n",
        "ranking_contract": "C02 contract: typed complete-set policies, terms, current/as-of, caps passed\n",
        "ranking_empty": "C02 nullary/unary/empty/constant and capture-vs-processing budgets passed\n",
        "ranking_payload_time": "C02 per-candidate owned payload and aggregate active-time boundaries passed\n",
        "ranking_census": "C02 census: 11 isolated classifier boundaries, wide score pipeline, actual-owner saturation passed\n",
        "ranking_public_independent": "independent public ranking groups=8 boolean_candidates=3 hot_inputs=200 slot_scores=24,32,32 decimal_repeated_slots=13\n",
        "ranking_integer_independent": "independent decimal arithmetic values=54 ordered_pairs=2916\nindependent integer groups=3 boundaries=16\n",
        "json_patch_compatibility": "JSON compatibility: 254162 identical bytes, SHA-256 80ac5ebf394ee05c966339df63394915de66fe156efcba675c15e6b9681aa318; upstream bad_alloc abort reproduced\n",
    }
    if test in fixed:
        need(output == fixed[test], "C02 source-supported exact output contract differs: " + test)
    if test in {"ranking_exceptions", "ranking_normalized_exceptions"}:
        prefix = "transactional" if test == "ranking_exceptions" else "normalized replay"
        suffix = ("all policies/complete workload/canonical owner stable; P07 prefix allocation profile preserved"
                  if test == "ranking_exceptions" else "complete owner/workload/result preserved")
        match = re.fullmatch("C02 " + prefix + r" allocation positions=([1-9][0-9]*) recovered_cleanup_positions=0; " + re.escape(suffix) + r"\n", output)
        need(match is not None, "allocation fixture lost full scope or changed recovery behavior")
    if test == "json_cleanup":
        shapes = ["empty", "scalar", "string", "binary", "wide-array", "long-key-object", "growth-array", "growth-object", "mixed-nested", "deep-chain"]
        names = [kind + "/" + shape for kind in ("json", "ordered_json", "custom_vector_json") for shape in shapes]
        lines = output.splitlines()
        need(len(lines) == 31, "JSON cleanup corpus lost/gained a case")
        points = 0
        for expected, line in zip(names, lines[:-1]):
            match = re.fullmatch(r"cleanup-case (\S+) normal-new-points=(\d+) normal-free-calls=(\d+) normal-live-restored=yes "
                                 r"persistent-fault-points=([1-9][0-9]*) fault-new-attempts=(\d+) fault-successful-allocations=(\d+) "
                                 r"fault-free-calls=(\d+) injected-failures=(\d+) fault-live-restored=yes result=pass", line)
            need(match is not None and match[1] == expected, "JSON cleanup shape/lifetime/result contract differs")
            points += int(match[4])
        need(lines[-1] == f"cleanup-summary cases=30 fault-points={points} result=pass", "JSON cleanup totals do not reconcile")
    if test.startswith("statistics_runtime_only_") or test == "statistics_collection":
        need(not output.strip(), "silent assertion consumer produced unexpected output")
    if test.startswith("statistics_reports_"):
        variant = test.removeprefix("statistics_reports_")
        testing = variant == "testing"
        lines = [line for line in output.splitlines() if line.strip()]
        need(lines[:3] == ["statistics stage=producer variant=" + variant,
             "statistics report lifecycle, literal facts, scalar and export-boundary fixtures produced",
             "statistics stage=schema_semantics_legacy_mutations variant=" + variant], "report producer/checker stages differ")
        need(len(lines) == 5, "report output lost or gained an acceptance stage")
        check = json.loads(lines[3], object_pairs_hook=pairs)
        expected = {"status": "pass", "reports": 32 if testing else 31, "legacy_byte_comparisons": 2,
                    "mutations_rejected": 17 if testing else 15, "testing": testing, "jsonschema_version": "4.10.3"}
        need(check == expected, "report independent checker counts/status differ")
        need(json.loads(lines[4], object_pairs_hook=pairs) ==
             {"status": "pass", "variant": variant, "publication_gate_mutations_rejected": 1}, "publication schema-gate rejection absent")
    policy = re.fullmatch(r"statistics_(delta|replay|window)_(fifo|lifo)(?:_(eager|incremental|root_first|anchored))?", test)
    if policy:
        fixture, order, selected = policy.groups()
        need(output.splitlines().count("C01 propagation=" + order) == 1, "actual policy-order marker absent/duplicate")
        values = (2712, 2691, 5278, 0) if fixture == "delta" else ((58, 60, 131, 0) if fixture == "replay" else (37, 0, 61, 13))
        expected = "C01 enabled acceptance physical_events=%d derivation_events=%d source_components=%d metadata_only_steps=%d" % values
        need(output.splitlines().count(expected) == 1, "independent policy census counts differ")
        if fixture == "delta":
            live = selected if selected in {"eager", "incremental"} else "on_output"
            completion = selected if selected in {"root_first", "anchored"} else "automatic"
            need(output.splitlines()[:2] == ["live_policy=" + live, "completion_request=" + completion], "actual delta policy identity differs")
            need("D04 DeltaRuntime acceptance passed updates=2712 emitted=1408 exhaustive_toggles=2504" in output, "retained A04 coverage differs")

def numeric_contract(test, output):
    legacy_numeric_contract(test,output)
    fixed = {
        "selection_pure_link":"C05 pure selection link without runtime/report passed\n",
        "selection_contract":"C05 literal depth/slots, four constraints, typed proof and complete-family contracts passed\n",
        "selection_cache":"C05 whole-artifact FIFO, read-only reuse, lifetime, counter/capacity and exact-family/proof cache cases passed\n",
        "selection_source":"C05 normalized alias10/7, full source mismatch, Decimal repeated13, unary/nullary/empty/constant cases passed\n",
        "selection_current":"C05 current/as-of, pending/abort/reset/configuration/source budget and actual Physical/Delta/Session boundaries passed\n",
        "selection_binding":"C05 independent byte framing and record/key mutations=143; diagnostic records create no selection authority\n",
        "selection_resources":"C05 aggregate exact/one-under, first-source admission, finite native work and optional timing contracts passed\n",
        "selection_census":"C05 actual-owner simultaneous saturation rejects depth and preserves exact source-only slot constraints\n",
        "selection_public_independent":"C05 independent public groups=7 depth=195/105/190 slots=24/32/32 caps=23/24/31/32 alias=10/7 decimal=13 zero=0\n",
        "selection_cache_independent":"C05 independent cache groups=5 request_fields=13 physical_options_supported=5 physical_options_rejected=1 FIFO=2 raw_tree_aliases=2\n",
        "selection_resources_independent":"C05 independent resources groups=3 additive_dimensions=8 literal_aggregate=40 cap=24 source_rows=0\n",
        "selection_binding_independent":"C05 independent normalized byte mutations=79\nC05 independent byte groups=5 scalar_types=5 tree_mutations=17 core_mutations=38\n",
    }
    if test in fixed:
        need(output == fixed[test], "C05 literal/source-supported output changed: "+test)
    if test in {"selection_exception","selection_normalized_exception"}:
        labels = (["C05 pure policy"]*3+["C05 pure dual assessment","C05 warm pure artifact",
                  "C05 current height late wrapper","C05 current dual assessment late wrapper"] if test == "selection_exception" else
                  ["C05 normalized winner replay/identity","C05 normalized two assessments","C05 normalized actual current publication"])
        lines = output.splitlines(); need(len(lines) == len(labels)+1, "persistent fault profile population differs")
        total = 0
        for label_,line in zip(labels,lines[:-1]):
            match = re.fullmatch(re.escape(label_)+r" allocation_positions=([1-9][0-9]*)",line)
            need(match is not None, "fault policy/profile ordering or positive coverage differs")
            total += int(match[1])
        if test == "selection_exception":
            match = re.fullmatch(r"C05 persistent positions=([1-9][0-9]*) recovered_cleanup_positions=0 publication_failures=([1-9][0-9]*); complete owner/workload/cache/old results preserved",lines[-1])
        else:
            match = re.fullmatch(r"C05 normalized persistent positions=([1-9][0-9]*) recovered_cleanup_positions=0; owned replay/source/identity/cache/late wrapper preserved",lines[-1])
        need(match is not None and int(match[1]) == total, "fault totals/recovery/complete-state contract differs")
    if test == "selection_publication_fault_independent":
        need(re.fullmatch(r"C05 focused atomic OOM groups=2 positions=([1-9][0-9]*) publication_failures=2 completed_fault_positions=0\n",output),
             "focused late-publication fault population/recovery contract differs")


def vendor_diagnostic_format(diagnostics, log):
    review_path = V/"selection-vendor-diagnostic-format-review-v1.json"
    review_sha = "f422c9fcdf30b77ee749fbcdd05e16cfb1dc0023f33f1ded803cdf411a9c6d79"
    need(digest(review_path) == review_sha, "vendor diagnostic format review FILE changed")
    review = data(review_path)
    need(review.get("reviewer") == "root" and review.get("decision") == "accepted_exact_diagnostic_quote_normalization" and
         review.get("card") == "C05" and review.get("native") == NATIVE and review.get("execution") == EXECUTION and
         review.get("freeze_sha256") == FREEZE_SHA, "vendor diagnostic format review has wrong authority/scope")
    exact_pairs = [
        {"current":"vendor/upb/upb.c:8245:8: warning: 'sv.data' may be used uninitialized [-Wmaybe-uninitialized]",
         "accepted_historical":WARNINGS[1]},
        {"current":"vendor/upb/upb.c:9206:6: warning: 'sv.size' may be used uninitialized [-Wmaybe-uninitialized]",
         "accepted_historical":WARNINGS[2]},
    ]
    need(review.get("exact_quote_pairs") == exact_pairs and review.get("warning_count") == 3 and
         review.get("unchanged_warning") == WARNINGS[0], "vendor diagnostic exact mapping/count changed")
    need(log == V/"selection-clean-source.log" and
         review.get("current_log") == {"path":label(log),"sha256":digest(log)},
         "vendor diagnostic review does not bind this exact current log")
    historical = review.get("accepted_historical_logs",[])
    need([row.get("path") for row in historical] == ["build/verification/ranking-clean-source.log",
         "build/verification/observability-clean-source.log"], "vendor diagnostic historical FILE population changed")
    for pin in historical:
        path = ROOT/pin["path"]
        need(digest(path) == pin["sha256"], "vendor diagnostic historical log FILE changed")
        observed = [line for line in read(path).splitlines() if re.search(r"\bwarning:\s",line)]
        need(collections.Counter(observed) == collections.Counter(WARNINGS),
             "historical exact three-warning multiset changed")
    failure = review.get("first_audit_failure")
    need(failure == {"path":"build/verification/selection-matrix-evidence-audit-preliminary-1.json",
         "sha256":"80e88d36453b5b1df9c74d3de5ffe3003dc2354c2d39eb713842357e9beafc99"},
         "vendor diagnostic first-failure lineage changed")
    need(digest(ROOT/failure["path"]) == failure["sha256"], "preserved first audit failure FILE changed")
    mapping = {row["current"]:row["accepted_historical"] for row in exact_pairs}
    normalized = [mapping.get(line,line) for line in diagnostics]
    need(all(diagnostics.count(line) == 1 for line in mapping) and
         collections.Counter(normalized) == collections.Counter(WARNINGS),
         "clean exact three-warning multiset differs after the two reviewed whole-line mappings")
    review_pin = {"path":label(review_path),"sha256":review_sha}
    changes = [{"kind":"vendor_diagnostic_format","evidence":label(log),"warning_index":index,
                "raw":line,"comparison":mapping[line],"review":review_pin}
               for index,line in enumerate(diagnostics) if line in mapping]
    NORMALIZATIONS.extend(changes)
    return {"exact_preserved_diagnostics":normalized,"raw_observed_diagnostics":diagnostics,
            "format_review":review_pin,"diagnostic_normalizations":changes,
            "not_waived":"Only the two reviewed whole-line quote formats change for comparison. All three warnings remain; none is called safe/fixed or suppressed."}


def audit_configuration(name, freeze, history, vendor):
    summary_path = V/f"selection-{name}-summary.json"
    summary = terminal(summary_path)
    if summary is None:
        return {"status":"pending"}
    need(summary.get("configuration") == name and summary.get("exit_code") == 0 and summary.get("test_count") == 158,
         "terminal summary failed or has wrong158 population")
    stable(summary)
    driver = Path("/tmp/crown-selection-clean-matrix.py" if name == "clean-source" else "/tmp/crown-selection-matrix.py")
    need(summary.get("driver_sha256") == digest(driver), "actual wrapper identity differs")
    if name == "clean-source":
        log = V/"selection-clean-source.log"; text = read(log)
        wanted = ["python3","/tmp/crown-selection-clean-evidence.py","--freeze-sha256",FREEZE_SHA,
                  "--configuration","Release","--parallel","2","--log",label(log)]
        need(summary.get("command") == wanted and summary.get("log") == label(log) and summary.get("log_sha256") == digest(log)
             and summary.get("wrapper_timeout_seconds") == 108000, "clean outer argv/log/ceiling differs")
        need("result: PASS" in text and len(re.findall(r"command completed in [0-9.]+s",text)) == 3, "clean three stages incomplete")
        folder,source,build = clean_artifacts(summary,text)
        configure_text = build_text = text; last_path = folder/"Testing/Temporary/LastTest.log"
        diagnostics = [line for line in text.splitlines() if re.search(r"\bwarning:\s",line)]
        warning_scope = vendor_diagnostic_format(diagnostics,log)
        emitted = re.findall(r"^compiling (\S+\.c)\s*$",text,re.M)
        need(collections.Counter(emitted) == collections.Counter(vendor[0]), "clean independent96C source recipe inventory differs")
    else:
        folder = ROOT/("build/clang-debug" if name == "clang" else "build/"+name)
        source,build = ROOT,folder
        stages = summary.get("stages",[])
        need([row.get("phase") for row in stages] == ["configure","build","test"], "terminal phase ordering incomplete")
        texts = {}
        for stage,wanted,phase,ceiling in zip(stages,expected_commands(name),("configure","build","test"),(7200,7200,86400)):
            path = V/f"selection-{name}-{phase}.log"
            need(stage.get("command") == wanted and stage.get("exit_code") == 0 and stage.get("log") == label(path) and
                 stage.get("log_sha256") == digest(path) and stage.get("timeout_seconds") == ceiling and not stage.get("timed_out"),
                 "actual phase argv/result/log/ceiling differs")
            texts[phase] = read(path)
            need(not re.search(r"\bwarning:\s",texts[phase]), "new warning in ordinary "+phase)
        configure_text,build_text,text = texts["configure"],texts["build"],texts["test"]
        last_path = V/f"selection-{name}-ctest-output.log"
        need(summary.get("ctest_output_log") == label(last_path) and summary.get("ctest_output_sha256") == digest(last_path),
             "preserved LastTest binding differs")
        warning_scope = {"new_warning_diagnostics":0}
        if name == "sanitize":
            quiet = summary.get("quiescence"); need(isinstance(quiet,dict), "SAN lacks explicit root quiescence")
            path = V/"selection-sanitize-quiescence.json"
            need(quiet.get("path") == label(path) and quiet.get("sha256") == digest(path), "quiescence FILE binding differs")
            value = data(path)
            need(value.get("reviewer") == "root" and value.get("decision") == "accepted_quiescent_sanitizer_window" and
                 value.get("no_other_expensive_work") is True and value.get("freeze_sha256") == FREEZE_SHA,
                 "SAN scheduling decision absent/wrong scope")
            others = value["other_terminal_summaries"]
            need(set(others) == {"debug","release","clang","clean-source"} and quiet.get("other_terminal_summaries") == others,
                 "quiescence prior-leg population differs")
            for other,pin in others.items():
                other_path = V/f"selection-{other}-summary.json"
                need(pin["path"] == label(other_path) and pin["sha256"] == digest(other_path), "quiescence prior summary FILE changed")
                prior = data(other_path)
                need(prior.get("terminal") is True and prior.get("freeze_sha256") == FREEZE_SHA, "SAN started without prior terminal record")
    registered,properties = registration(folder,source,build,freeze)
    for test,expected in history["properties"][name].items():
        current = {k:v for k,v in properties.get(test,{}).items() if k != "_BACKTRACE_TRIPLES"}
        need(current == expected, "old143 test execution properties changed: "+test)
    blocks = records(read(last_path),158)
    need([b["name"] for b in blocks] == [t["name"] for t in registered], "actual LastTest order/registration differs")
    need("100% tests passed, 0 tests failed out of 158" in text, "exact158/158 verbose terminal result missing")
    passed = re.findall(r"^\s*(\d+)/158 Test\s+#\s*(\d+):\s+(\S+)\s+.*?\bPassed\b",text,re.M)
    need(len(passed) == 158 and collections.Counter(x[2] for x in passed) == collections.Counter(freeze["test_names"]) and
         {int(x[0]) for x in passed} == set(range(1,159)) and {int(x[1]) for x in passed} == set(range(1,159)),
         "verbose passed-name/ordinal population differs")
    outputs = {}
    for block,test_registration in zip(blocks,registered):
        test = block["name"]
        need(block["argv"] == test_registration["argv"] and block["directory"] == str(build), "actual CTest argv/directory differs")
        if name == "sanitize":
            env = properties.get(test,{}).get("ENVIRONMENT","")
            need("ASAN_OPTIONS=detect_leaks=1:halt_on_error=1" in env and "UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1" in env,
                 "SAN runtime/leak policy absent")
        numeric_contract(test,block["output"])
        rows = output_rows(block["output"],test,source,build,name); command = test_registration["command"]
        if test in history["tests"]:
            old = history["tests"][test]; need(command == old["command"], "legacy actual command changed")
            compare_rows("C02_legacy",test,name,old["rows"]["comparison"],rows["comparison"],"C02-release")
        if test in PREPARATION:
            path = PREPARATION[test]
            before = output_rows(read(path),test,ROOT,ROOT/"build/release",label(path))
            compare_rows("accepted_preparation",test,name,before["comparison"],rows["comparison"],label(path))
        outputs[test] = {"ordinal":block["ordinal"],"passed":True,"command":command,"raw_command":block["argv"],
                         "rows":rows,"output_sha256":hashlib.sha256(block["output"].encode()).hexdigest()}
    compilation = compile_audit(name,folder,source,build,history["expected_sources"],vendor[1],configure_text,build_text,freeze)
    verbose = V/("selection-clean-source.log" if name == "clean-source" else f"selection-{name}-test.log")
    return {"status":"audited_pass","summary":{"path":label(summary_path),"sha256":digest(summary_path)},
            "registration":{"path":label(folder/"CTestTestfile.cmake"),"sha256":digest(folder/"CTestTestfile.cmake")},
            "raw_lasttest":{"path":label(last_path),"sha256":digest(last_path)},
            "raw_verbose":{"path":label(verbose),"sha256":digest(verbose)},
            "registered_test_names":[t["name"] for t in registered],"actual_order":[t["name"] for t in registered],
            "tests":outputs,"test_outcomes":[{"ordinal":b["ordinal"],"name":b["name"],"status":"passed","command":b["argv"]} for b in blocks],
            "numeric_rows_observed":sum(len(item["rows"]["raw"]) for item in outputs.values()),
            "compilation":compilation,"warning_policy":warning_scope,"source_root":str(source),"build_root":str(build)}

def symbol_audit(name, matrix):
    if matrix.get("status") != "audited_pass":
        PENDING.append(name + ": symbols await a complete audited terminal matrix record")
        return {"status": "pending"}
    path = V / f"selection-{name}-symbols.json"
    record = terminal(path, "status")
    if record is None:
        return {"status": "pending"}
    need(record.get("configuration") == name and record.get("status") == "captured" and record.get("exit_code") == 0 and record.get("freeze_sha256") == FREEZE_SHA,
         "new symbol capture is not terminal/correctly scoped")
    need(record.get("collector_sha256") == digest(Path("/tmp/crown-selection-symbols.py")), "new symbol collector identity changed")
    roles = {"plan", "ranking", "ranking_runtime", "ranking_runtime_testing", "planner_testing",
             "runtime", "runtime_testing", "explain", "explain_testing", "selection", "selection_runtime", "selection_runtime_testing"}
    if name == "sanitize":
        roles.add("parser_undefined")
    rows = record.get("records", [])
    need(len(rows) == len(roles) and {r.get("role") for r in rows} == roles, "new symbol role set differs")
    build = Path(matrix["build_root"])
    texts, result = {}, {}
    for item in rows:
        role = item["role"]
        archive = build / ("_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" if role == "parser_undefined" else f"libcrown_{role}.a")
        need(item.get("archive") == str(archive) and item.get("exit_code") == 0 and item.get("archive_stable") is True and item.get("archive_sha256_after") == item.get("archive_sha256"),
             "symbol archive/capture binding differs: " + role)
        expected_command = ["nm", "-C", "--undefined-only" if role == "parser_undefined" else "--defined-only", str(archive)]
        need(item.get("command") == expected_command, "symbol dump used wrong selection/command")
        dump = V / f"selection-{name}-{role}.nm"
        stderr = V / f"selection-{name}-{role}.nm.stderr"
        need(item.get("dump") == label(dump) and item.get("stderr") == label(stderr), "symbol dump path differs")
        need(digest(dump) == item.get("dump_sha256") and digest(stderr) == item.get("stderr_sha256") and not read(stderr),
             "symbol dump pin/stderr differs")
        if name == "clean-source":
            need(not archive.exists() and re.fullmatch(r"[0-9a-f]{64}", item.get("archive_sha256", "")), "clean removed archive identity missing")
        else:
            need(digest(archive) == item.get("archive_sha256"), "archive changed since symbol capture")
        texts[role] = read(dump)
    for role, text in texts.items():
        if role == "parser_undefined":
            need("__asan_" in text and "__ubsan_" in text, "parser archive lacks both sanitizer runtime references")
            continue
        expected_members = collections.Counter(Path(item["source"]).name + ".o" for item in matrix["compilation"]["source_inventory"]
                                               if item["target"] == "crown_" + role)
        members = re.findall(r"^([^\s:]+\.o):\s*$", text, re.M)
        need(expected_members and collections.Counter(members) == expected_members,
             "symbol archive member inventory differs: " + role)
        baseline_count = len(re.findall(r"^.*\b[BDGRTVW]\b.*minimum_tree_baseline\(", text, re.M))
        need(baseline_count == (1 if role == "planner_testing" else 0), "planner baseline export leaked/missing: " + role)
        probes = re.findall(r"^.*\bT\b.*RuntimeTestProbe::([A-Za-z_]\w*)\(", text, re.M)
        if role == "runtime_testing":
            need(collections.Counter(probes) == collections.Counter(PROBES), "testing probe export set differs from source's 12 methods")
        else:
            need("RuntimeTestProbe::" not in text and "seed_report_saturation" not in text and
                 "seed_c01_report_saturation" not in text, "testing statistics seam leaked: " + role)
        for hook in ("set_observation_clock_for_testing", "set_observation_initial_generation_for_testing"):
            count = len(re.findall(r"^.*\bT\b.*" + hook + r"\(", text, re.M))
            need(count == (1 if role == "runtime_testing" else 0), "O07 hook export scope differs: " + role + "/" + hook)
        pure = len(re.findall(r"^.*\bT\s+crown::planner::ranking::rank\(", text, re.M))
        need(pure == (1 if role == "ranking" else 0), "pure rank implementation leaked or absent: " + role)
        bridge_counts = {}
        for function in ("capture", "revalidate", "rank_current"):
            count = len(re.findall(r"^.*\bT\s+crown::runtime::ranking::" + function + r"\(", text, re.M))
            need(count == (3 if role in {"ranking_runtime", "ranking_runtime_testing"} else 0),
                 "runtime ranking bridge export scope differs: " + role + "/" + function)
            bridge_counts[function] = count
        selected = len(re.findall(r"^.*\bT\s+crown::planner::selection::select\(",text,re.M))
        current = len(re.findall(r"^.*\bT\s+crown::runtime::selection::select_current\(",text,re.M))
        need(selected == (1 if role == "selection" else 0), "pure selection export leaked/absent")
        need(current == (3 if role in {"selection_runtime","selection_runtime_testing"} else 0), "selection current bridge overload scope differs")
        result[role] = {"selection_definitions":selected,"selection_current_definitions":current,
                        "baseline_definitions": baseline_count, "runtime_probe_methods": probes,
                        "archive_members": members, "pure_rank_definitions": pure, "bridge_definitions": bridge_counts}
    return {"status": "audited_pass", "metadata": label(path), "roles": result,
            "parser_both_sanitizers": name == "sanitize"}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output",type=Path,required=True)
    parser.add_argument("--authority",type=Path,required=True)
    parser.add_argument("--authority-sha256",required=True)
    parser.add_argument("--allocation-review",type=Path)
    parser.add_argument("--allocation-review-sha256")
    args = parser.parse_args()
    output = args.output.resolve()
    designated = re.fullmatch(r"selection-matrix-(?:evidence-audit(?:-[A-Za-z0-9_.-]+)?|audit-[A-Za-z0-9_.-]+)\.json",output.name)
    allowed = (output.parent == V and designated is not None) or str(output).startswith("/tmp/crown-c05-matrix-audit-")
    need(allowed and output.suffix == ".json" and not output.exists() and not output.with_suffix(".log").exists(),
         "output must be a new designated C05 artifact")
    authority = guarded("root auditor authority",lambda:load_authority(args.authority,args.authority_sha256))
    approvals = guarded("allocation review",lambda:load_approvals(args.allocation_review,args.allocation_review_sha256))
    pins = guarded("immutable input FILE pins",input_pins)
    digest(Path(__file__))
    preparation = guarded("accepted C05 preparation",preparation_authority)
    freeze = guarded("C05 current execution freeze",freeze_audit)
    history = guarded("retained C02 historical baseline",historical)
    vendor = guarded("independent96C vendor recipe",parser_inventory)
    matrix,symbols = {},{}
    if not ERRORS and freeze.get("status") == "audited_pass" and "expected_sources" in history and isinstance(vendor,tuple):
        guarded("old143 order",lambda:need(history["ordered_names"] == freeze["legacy_names"],"retained143 order differs from freeze"))
        for name in CONFIGS:
            matrix[name] = guarded(name,lambda name=name:audit_configuration(name,freeze,history,vendor))
        reference_name = "release" if matrix["release"].get("status") == "audited_pass" else None
        if reference_name is None:
            PENDING.append("release: fixed cross-configuration numeric/command baseline unavailable")
        for name in CONFIGS:
            if reference_name and matrix[name].get("status") == "audited_pass":
                def compare(name=name):
                    for test,observed in matrix[name]["tests"].items():
                        reference = matrix[reference_name]["tests"][test]
                        need(observed["command"] == reference["command"],"cross-configuration argv differs: "+test)
                        compare_rows("cross_configuration",test,name,reference["rows"]["comparison"],observed["rows"]["comparison"],reference_name)
                    return {"status":"audited_pass"}
                matrix[name]["cross_configuration"] = guarded(name+" rows/commands",compare)
            symbols[name] = guarded(name+" symbols",lambda name=name:symbol_audit(name,matrix[name]))
    closing = guarded("final input/source stability",final_stability)
    unused = set(APPROVALS)-USED_APPROVALS
    raw_complete = len(matrix) == 5 and all(m.get("status") == "audited_pass" for m in matrix.values())
    if unused and raw_complete:
        ERRORS.append("unused/stale allocation approvals: "+", ".join(sorted(unused)))
    unapproved = [row for row in REVIEW if not row["root_approved"]]
    complete = (len(matrix) == len(symbols) == 5 and not ERRORS and not PENDING and not unapproved and
                all(m.get("status") == "audited_pass" for m in matrix.values()) and
                all(m.get("status") == "audited_pass" for m in symbols.values()))
    state = ("accepted_final_matrix" if complete else "matrix_needs_review" if ERRORS else
             "preliminary_pending_matrix" if PENDING else "allocation_review_required")
    if "expected_sources" in history:
        history["expected_sources"] = [{"target":t,"source":u} for t,u in sorted(history["expected_sources"])]
    result = {
        "card":"C05","audit_state":state,"accepted":complete,"accepted_matrix_evidence":complete,"changes_project_status":False,
        "auditor":{"path":label(Path(__file__)),"sha256":digest(Path(__file__))},
        "auditor_execution_authority":authority,"input_pin_check":pins,"freeze":freeze,"closing_source_guard":closing,
        "historical":history,"preparation_authority":preparation,"matrix":matrix,"symbols":symbols,
        "allocation_review_record":approvals,"allocation_differences":REVIEW,"normalizations":NORMALIZATIONS,
        "unapplied_allocation_approval_ids":sorted(unused),
        "vendor_source_inventory":sorted(vendor[0]) if isinstance(vendor,tuple) else vendor,
        "read_evidence_sha256":READ_PINS,"errors":ERRORS,"pending":PENDING,
        "policy":"Read/hash only; no subprocess/project imports or execution. Twelve historical manifest FILE identities only. All observed numeric rows retained with narrow trace/directory normalization; no automatic allocation waiver.",
        "reviewer_lineage":"This author wrote the C05 independent five-consumer/22-group fixtures and prior C02 independent oracles, not the selection/ranking implementations. This audits evidence/registration, not a new independent authorship claim for those fixtures.",
        "historical_dependency_scope":"Retained object bytes, normalized argv and frozen project dependencies can be compared. Historical system/generated header bytes were not recorded; current observations and fresh clean238 evidence remain separate.",
    }
    output.parent.mkdir(parents=True,exist_ok=True)
    with output.open("x",encoding="utf-8") as handle: handle.write(json.dumps(result,indent=2,sort_keys=True)+"\n")
    lines = [state,"accepted_matrix_evidence="+str(complete),*[name+": "+item["status"] for name,item in matrix.items()],
             "unapproved_allocation_differences="+str(len(unapproved)),"pending="+json.dumps(PENDING),"errors="+json.dumps(ERRORS)]
    with output.with_suffix(".log").open("x",encoding="utf-8") as handle: handle.write("\n".join(lines)+"\n")
    print("\n".join(lines))
    return 0 if complete else 1 if ERRORS else 2 if PENDING else 3

if __name__ == "__main__":
    raise SystemExit(main())

