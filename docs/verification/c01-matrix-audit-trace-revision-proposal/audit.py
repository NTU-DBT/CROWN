#!/usr/bin/env python3
"""Evidence-only C01 matrix audit. Never imports/runs project code or subprocesses."""
from __future__ import annotations

import argparse
import collections
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
NATIVE = {"count": 623, "sha256": "25f7143860cf28f6c7ba0e89a5b40708d3fb71fec979408bf1135f0fa45b1ef0"}
EXECUTION = {"count": 676, "sha256": "70916b45f3105b21d281f49c12c0455c9de8f3b2d76daa74bf252f2bb2144f4d"}
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
PREPARATION = {
    "statistics_capture": "c01-statistics-combined-root-attempt-1-strict-production-statistics_capture_test.log",
    "statistics_capture_exceptions": "c01-statistics-combined-root-attempt-1-strict-production-statistics_capture_exception_test.log",
    "statistics_owner": "c01-statistics-combined-root-attempt-1-strict-production-owner_statistics_test.log",
    "statistics_owner_exceptions": "c01-statistics-combined-root-attempt-1-strict-production-owner_statistics_exception_test.log",
    "statistics_collection": "c01-statistics-combined-root-attempt-1-strict-testing-statistics_collection_test.log",
    "statistics_workload": "c01-statistics-combined-root-attempt-1-strict-testing-workload_statistics_test.log",
    "statistics_workload_exceptions": "c01-statistics-combined-root-attempt-1-strict-testing-workload_statistics_exception_test.log",
    "statistics_scalars": "c01-statistics-scalar-root-attempt-1-strict-scalar-statistics.log",
}
for _variant in ("production", "testing"):
    PREPARATION[f"statistics_combined_{_variant}"] = f"c01-statistics-combined-root-attempt-1-strict-{_variant}-combined_statistics_test.log"
    PREPARATION[f"statistics_combined_exceptions_{_variant}"] = f"c01-statistics-combined-root-attempt-1-strict-{_variant}-combined_statistics_exception_test.log"
    PREPARATION[f"statistics_reports_{_variant}"] = f"c01-statistics-native-publication-root-attempt-1-{_variant}-wrapper.log"
    PREPARATION[f"statistics_report_exceptions_{_variant}"] = f"c01-statistics-native-publication-root-attempt-1-{_variant}-faults.log"

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
    READ_PINS[label(path)] = hashlib.sha256(value).hexdigest()
    return value.decode("utf-8")


def digest(path):
    path = Path(path)
    need(path.is_file(), "missing pinned file: " + label(path))
    value = hashlib.sha256(path.read_bytes()).hexdigest()
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
        value = data(path)
    except json.JSONDecodeError:
        PENDING.append(label(path) + ": terminal record incomplete")
        return None
    if required not in value:
        PENDING.append(label(path) + ": not terminal")
        return None
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
    r"same-owner update failures|mode failures))=(?P<value>\d+)"
)


def allocation_only(before, after):
    left, right = list(ALLOCATION_FIELD.finditer(before)), list(ALLOCATION_FIELD.finditer(after))
    if not left or len(left) != len(right):
        return False
    if [m["field"] for m in left] != [m["field"] for m in right]:
        return False
    replace = lambda text: ALLOCATION_FIELD.sub(lambda m: m["field"] + "=<allocation-count>", text)
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


def load_approvals(path):
    if path is None:
        return None
    need(path.parent.resolve() == V and re.fullmatch(r"statistics-allocation-review-[A-Za-z0-9_.-]+\.json", path.name),
         "allocation review must be a new designated statistics-allocation-review-*.json record")
    value = data(path)
    need(value.get("reviewer") == "root" and value.get("decision") == "accepted_allocation_only",
         "allocation review lacks explicit root decision")
    need(value.get("native") == NATIVE and value.get("execution") == EXECUTION, "allocation review is for another freeze")
    for entry in value.get("entries", []):
        change = entry["difference"]
        needed = {"kind", "test", "configuration", "baseline_configuration", "row_index", "before", "after"}
        need(set(change) == needed and allocation_only(change["before"], change["after"]), "allocation review attempts to waive semantic data")
        key = hashlib.sha256(json.dumps(change, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
        need(entry.get("id") == key and key not in APPROVALS and isinstance(entry.get("reason"), str) and entry["reason"].strip(),
             "duplicate, unbound or unexplained allocation approval")
        APPROVALS[key] = entry
    return {"path": label(path), "sha256": digest(path), "entries": len(APPROVALS)}


def input_pins():
    pinned = data(PACKAGE / "PINNED_INPUTS.json")
    for path, expected in pinned.items():
        target = Path(path) if path.startswith("/") else ROOT / path
        need(digest(target) == expected, "immutable audit input changed: " + path)
    return {"count": len(pinned), "manifest": label(PACKAGE / "PINNED_INPUTS.json")}


def freeze_audit():
    freeze = data(V / "statistics-execution-freeze.json")
    need(freeze.get("card") == "C01" and freeze.get("native") == NATIVE and freeze.get("execution") == EXECUTION, "wrong C01 freeze")
    need(freeze.get("configs") == list(CONFIGS) and freeze.get("expected_compile_command_entries") == 195, "wrong config/compiler inventory")
    names = freeze["expected_test_names"]
    old = freeze["old_legacy_test_names_in_order"]
    need(len(names) == len(set(names)) == 131 and names == sorted(names), "freeze does not contain 131 unique sorted names")
    need(len(old) == len(set(old)) == 99 and set(old) <= set(names), "freeze legacy name set invalid")
    history = freeze["historical_manifest_file_hashes"]
    need(set(history) == {"P05", "P06", "P04", "O03", "R06", "O02", "O01", "D06", "P07", "O07"}, "ten historical manifest FILE identities required")
    for name, record in history.items():
        need(digest(ROOT / record["path"]) == record["sha256"], name + ": historical manifest FILE changed")
    # Never parse or check old native manifest entries.
    for kind, expected, directories, extras in (
        ("native", NATIVE, ["include", "src", "apps", "tests", "cmake"], ["CMakeLists.txt", "CMakePresets.json"]),
        ("execution", EXECUTION, ["include", "src", "apps", "tests", "cmake", "schemas", "tools", "third_party"],
         ["CMakeLists.txt", "CMakePresets.json", "dependencies.lock.json"]),
    ):
        paths = set(extras)
        for directory in directories:
            paths.update(p.relative_to(ROOT).as_posix() for p in (ROOT / directory).rglob("*")
                         if p.is_file() and "__pycache__" not in p.parts and p.suffix != ".pyc")
        aggregate = hashlib.sha256()
        actual = {}
        for rel in sorted(paths):
            raw = (ROOT / rel).read_bytes()
            aggregate.update(rel.encode() + b"\0" + raw + b"\0")
            actual[rel] = hashlib.sha256(raw).hexdigest()
        need({"count": len(paths), "sha256": aggregate.hexdigest()} == expected, kind + " current aggregate changed")
        need(actual == freeze[kind + "_file_sha256"], kind + " current per-file map changed")
    need(digest(V / "c01-native-integration-start.json") == freeze["integration_record_sha256"], "integration record changed")
    need(digest(ROOT / "docs/verification/c01-statistics-native-registration-proposal/PACKAGE_SHA256SUMS") ==
         freeze["registration_manifest_sha256"], "registration package identity changed")
    return {"status": "audited_pass", "metadata": {"path": "build/verification/statistics-execution-freeze.json",
            "sha256": digest(V / "statistics-execution-freeze.json")}, "native": NATIVE, "execution": EXECUTION,
            "test_names": names, "legacy_names": old, "historical_manifest_files": history,
            "historical_policy": "Hash the ten manifest files only; no historical entry check against C01 sources."}


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
    old_audit = data(V / "observability-matrix-evidence-audit.json")
    need(old_audit.get("accepted") is True and old_audit.get("audit_state") == "accepted_final_matrix", "O07 baseline was not accepted")
    baseline = records(read(V / "observability-release-ctest-output.log"), 99)
    folder = V / "observability-clean-artifacts"
    cache = cache_values(read(folder / "CMakeCache.txt"))
    source = Path(cache["CMAKE_HOME_DIRECTORY"])
    compile_rows = data(folder / "compile_commands.json")
    old_sources = {source_tuple(row, source) for row in compile_rows}
    need(len(old_sources) == len(compile_rows) == 157, "historical source inventory is not 157 unique entries")
    expected = set(old_sources)
    for target in ("crown_runtime", "crown_runtime_testing"):
        expected.update((target, unit) for unit in RUNTIME_NEW)
    for target in ("crown_explain", "crown_explain_testing"):
        expected.update((target, unit) for unit in REPORT_NEW)
    expected.update((target, "tests/unit/" + item[0] + ".cpp") for target, item in CONSUMERS.items())
    need(len(CONSUMERS) == 24 and len(expected) == 195, "independently derived C01 source inventory differs")
    old_source = ROOT
    old_build = ROOT / "build/release"
    out = {}
    for block in baseline:
        out[block["name"]] = {
            "command": command_normalized(block["argv"], old_source, old_build),
            "rows": output_rows(block["output"], block["name"], old_source, old_build, "O07 release"),
        }
    return {"tests": out, "ordered_names": [b["name"] for b in baseline],
            "expected_sources": expected,
            "note": "All 99 legacy commands and observed numeric rows retained; no fixed C01 row-total expectation."}


def registration(folder, source, build, freeze):
    text = read(folder / "CTestTestfile.cmake")
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
    names = [t["name"] for t in tests]
    need(len(names) == len(set(names)) == 131 and sorted(names) == freeze["test_names"], "generated CTest name inventory differs")
    need([n for n in names if n in freeze["legacy_names"]] == freeze["legacy_names"], "relative legacy CTest registration order changed")
    for test in tests:
        test["command"] = command_normalized(test["argv"], source, build)
        need("docs/verification" not in " ".join(test["argv"]), "proposal path in native test command")
        if test["name"] not in freeze["legacy_names"]:
            prop = properties.get(test["name"], {})
            need(prop.get("LABELS") == "C01" and prop.get("TIMEOUT") == "900", "new CTest label/timeout differs")
    return tests, properties


def compile_audit(name, folder, source, build, expected_sources, make_original, configure_text, build_text):
    rows = data(folder / "compile_commands.json")
    actual = [source_tuple(row, source) for row in rows]
    need(len(rows) == len(set(actual)) == 195 and set(actual) == expected_sources, "actual 195-entry target/source inventory differs")
    cache = cache_values(read(folder / "CMakeCache.txt"))
    need(cache.get("CMAKE_HOME_DIRECTORY") == str(source), "source root/cache binding differs")
    need(cache.get("CROWN_WARNINGS_AS_ERRORS") == "ON", "warnings-as-errors disabled")
    need(cache.get("CROWN_SANITIZERS") == ("ON" if name == "sanitize" else "OFF"), "sanitizer cache mode differs")
    need(cache.get("CMAKE_BUILD_TYPE") == ("Release" if name in {"release", "clean-source"} else "Debug"), "CMake build type differs")
    compiler = cache.get("CMAKE_CXX_COMPILER")
    c_compiler = cache.get("CMAKE_C_COMPILER")
    family = "Clang" if name == "clang" else "GNU"
    need(compiler and (("clang" in Path(compiler).name) == (name == "clang")), "C++ compiler family/path inconsistent")
    need(c_compiler and (("clang" in Path(c_compiler).name) == (name == "clang")), "C compiler family/path inconsistent")
    by_target = collections.defaultdict(list)
    compile_macros = {}
    for row, identity in zip(rows, actual):
        target, unit = identity
        words = row.get("arguments") or shlex.split(row["command"])
        need(words[0] == compiler and FLAGS <= set(words) and "-std=c++23" in words, "compiler/strict C++23 flags differ: " + target)
        need("-w" not in words and not any(w.startswith("-Wno-") for w in words), "project warning suppression: " + target)
        need(not any("docs/verification" in w or "/tmp/crown-c01" in w or "/tmp/crown-o07" in w for w in words),
             "proposal path in native compile command")
        sanitize = {"-fsanitize=address,undefined", "-fno-omit-frame-pointer"}
        need(sanitize <= set(words) if name == "sanitize" else not any(w.startswith("-fsanitize") for w in words),
             "sanitizer instrumentation differs: " + target)
        need(not any(w.startswith("-fno-sanitize") for w in words), "sanitizer suppression in project compilation")
        need(("-O3" in words and "-DNDEBUG" in words) if name in {"release", "clean-source"} else "-g" in words,
             "actual build optimization/debug flags differ: " + target)
        runtime_macro = any(w == "-DCROWN_RUNTIME_TESTING" or w.startswith("-DCROWN_RUNTIME_TESTING=") for w in words)
        compile_macros.setdefault(target, set()).add(runtime_macro)
        if target in CONSUMERS:
            need(runtime_macro == (CONSUMERS[target][1] == "testing"), "C01 consumer macro variant differs: " + target)
            ndebug = [w for w in words if w == "-UNDEBUG" or w == "-DNDEBUG" or w.startswith("-DNDEBUG=")]
            need(ndebug and ndebug[-1] == "-UNDEBUG",
                 "C01 numeric assertions disabled: " + target)
        acceptance = "-DCROWN_STATISTICS_ACCEPTANCE" in words
        lifo = "-DCROWN_STATISTICS_LIFO" in words
        need(acceptance == (target in POLICY_TARGETS) and lifo == (target in POLICY_TARGETS and "_lifo_" in target),
             "statistics acceptance/order macro leaked or absent: " + target)
        by_target[target].append(unit)
    for target, units, testing in (
        ("crown_runtime", RUNTIME_UNITS, False), ("crown_runtime_testing", RUNTIME_UNITS, True),
        ("crown_explain", REPORT_UNITS, False), ("crown_explain_testing", REPORT_UNITS, True),
    ):
        need(set(by_target[target]) == units and len(by_target[target]) == len(units), "runtime/report unit set differs: " + target)
        need(compile_macros[target] == {testing}, "runtime/report macro differs: " + target)
    links = {}
    for target in by_target:
        path = folder / "CMakeFiles" / (target + ".dir") / "link.txt"
        words = shlex.split(read(path))
        libraries = {Path(w).name for w in words if w.endswith(".a")}
        # An archive recipe names its own output; that is not a dependency.
        libraries.discard("lib" + target + ".a")
        need(not {"libcrown_runtime.a", "libcrown_runtime_testing.a"} <= libraries, "mixed runtime linkage: " + target)
        need(not {"libcrown_explain.a", "libcrown_explain_testing.a"} <= libraries, "mixed report linkage: " + target)
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
        # Executables have an -o link; static archive recipes do not.
        if name == "sanitize" and "-o" in words:
            need("-fsanitize=address,undefined" in words, "sanitizer missing on executable link: " + target)
        links[target] = {"libraries": sorted(libraries), "runtime_testing": testing, "runtime_production": production}
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
    return {"raw_cmake_entries": len(rows), "runtime_units_per_variant": 14, "report_units_per_variant": 6,
            "source_inventory": [{"target": t, "source": s} for t, s in sorted(actual)],
            "compiler": compiler, "c_compiler": c_compiler, "compiler_metadata": compiler_metadata,
            "links": links, "vendor": parser_evidence}


def stable(summary):
    need(summary.get("source_stable") is True, "summary source_stable is not true")
    need(summary.get("fingerprint_before") == NATIVE["sha256"] == summary.get("fingerprint_after"), "native before/after differs")
    need(summary.get("execution_inputs_before") == EXECUTION == summary.get("execution_inputs_after"), "execution before/after differs")


def expected_commands(name):
    if name == "clang":
        return [["cmake", "-S", ".", "-B", "build/clang-debug"],
                ["cmake", "--build", "build/clang-debug", "--parallel", "2"],
                ["ctest", "--test-dir", "build/clang-debug", "--output-on-failure", "--verbose"]]
    return [["cmake", "--preset", name], ["cmake", "--build", "--preset", name, "--parallel", "2"],
            ["ctest", "--preset", name, "--output-on-failure", "--verbose"]]


def clean_artifacts(summary, text):
    manifest_path = V / "statistics-clean-artifacts-manifest.json"
    manifest = data(manifest_path)
    need(manifest.get("status") == "passed" and manifest.get("exit_code") == 0 and
         manifest.get("source_stable") is True and manifest.get("temporary_removed") is True, "clean artifact terminal status failed")
    for field in ("source_before", "snapshot_inputs", "source_after"):
        need(manifest.get(field) == {"native": NATIVE, "execution": EXECUTION}, "clean " + field + " changed")
    need(manifest.get("original_helper") == "tools/verify_clean_build.py" and
         manifest.get("original_helper_sha256") == digest(ROOT / "tools/verify_clean_build.py"), "native clean helper changed")
    need(manifest.get("adapter_sha256") == digest(Path("/tmp/crown-statistics-clean-evidence.py")), "clean adapter changed")
    source = Path(manifest["snapshot_source"])
    build = source / "build"
    need(str(source).startswith("/tmp/crown-clean-source-") and source.name == "source", "wrong clean snapshot root")
    need(not source.parent.exists() and summary.get("temporary_path") == str(source.parent) and
         summary.get("temporary_removed") is True, "clean snapshot was not removed")
    expected = [["cmake", "-S", str(source), "-B", str(build), "-DCMAKE_BUILD_TYPE=Release"],
                ["cmake", "--build", str(build), "--parallel", "2"],
                ["ctest", "--test-dir", str(build), "--output-on-failure"]]
    commands = manifest.get("commands", [])
    need(len(commands) == 3, "clean stage count differs")
    for record, original in zip(commands, expected):
        executed = original + (["--verbose"] if "--build" in original or original[0] == "ctest" else [])
        need(record.get("original") == original and record.get("executed") == executed, "clean adapter changed more than verbosity")
        need("$ " + " ".join(executed) in text, "clean actual command not present in preserved log")
    folder = V / "statistics-clean-artifacts"
    retained = manifest.get("retained", [])
    seen = set()
    for item in retained:
        path = ROOT / item["retained"]
        need(path.is_relative_to(folder) and path not in seen, "duplicate or out-of-scope retained artifact")
        seen.add(path)
        need(digest(path) == item["sha256"], "retained clean artifact changed: " + label(path))
        need(Path(item["source"]) == build / path.relative_to(folder), "clean retained/source mapping differs")
    actual = {p for p in folder.rglob("*") if p.is_file()}
    need(actual == seen, "clean retained manifest does not cover exactly its artifact files")
    need(manifest.get("symbols_manifest") == str(V / "statistics-clean-source-symbols.json"), "clean symbol capture path differs")
    return folder, source, build


def numeric_contract(test, output):
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


def audit_configuration(name, freeze, history, vendor):
    summary_path = V / f"statistics-{name}-summary.json"
    summary = terminal(summary_path)
    if summary is None:
        return {"status": "pending"}
    need(summary.get("configuration") == name and summary.get("exit_code") == 0 and summary.get("test_count") == 131,
         "terminal summary failed or has wrong configuration/count")
    stable(summary)
    if name == "clean-source":
        text = read(V / "statistics-clean-source.log")
        expected = ["python3", "/tmp/crown-statistics-clean-evidence.py", "--configuration", "Release",
                    "--parallel", "2", "--log", "build/verification/statistics-clean-source.log"]
        need(summary.get("command") == expected and summary.get("log") == "build/verification/statistics-clean-source.log", "clean wrapper command/log differs")
        need("result: PASS" in text and len(re.findall(r"command completed in [0-9.]+s", text)) == 3, "clean helper did not finish its three stages")
        folder, source, build = clean_artifacts(summary, text)
        configure_text = build_text = text
        last_path = folder / "Testing/Temporary/LastTest.log"
        diagnostics = [line for line in text.splitlines() if re.search(r"\bwarning:\s", line)]
        old_diagnostics = [line for line in read(V / "observability-clean-source.log").splitlines() if re.search(r"\bwarning:\s", line)]
        need(collections.Counter(diagnostics) == collections.Counter(WARNINGS) == collections.Counter(old_diagnostics),
             "clean diagnostics changed, grew, or include a project warning")
        labels = re.findall(r"^compiling (\S+\.c)\s*$", text, re.M)
        need(collections.Counter(labels) == collections.Counter(vendor[0]), "clean vendor 96-unit emitted source inventory differs")
        warning_scope = {"exact_preserved_diagnostics": diagnostics,
                         "not_waived": "No new project/vendor diagnostic; the three historical diagnostics are retained, not called safe or fixed."}
    else:
        folder = ROOT / ("build/clang-debug" if name == "clang" else "build/" + name)
        source, build = ROOT, folder
        stages = summary.get("stages", [])
        need([s.get("phase") for s in stages] == ["configure", "build", "test"], "incomplete/reordered matrix stages")
        texts = {}
        for stage, wanted, phase in zip(stages, expected_commands(name), ("configure", "build", "test")):
            path = V / f"statistics-{name}-{phase}.log"
            need(stage.get("command") == wanted and stage.get("exit_code") == 0 and
                 stage.get("log") == label(path), "terminal stage command/exit/log differs: " + phase)
            texts[phase] = read(path)
            need(not re.search(r"\bwarning:\s", texts[phase]), "new warning in regular " + phase + " evidence")
        configure_text, build_text, text = texts["configure"], texts["build"], texts["test"]
        last_path = V / f"statistics-{name}-ctest-output.log"
        need(summary.get("ctest_output_log") == label(last_path), "wrong preserved LastTest path")
        warning_scope = {"new_warning_diagnostics": 0}
    registered, properties = registration(folder, source, build, freeze)
    blocks = records(read(last_path), 131)
    need([b["name"] for b in blocks] == [t["name"] for t in registered], "LastTest order differs from actual generated CTest registration")
    need("100% tests passed, 0 tests failed out of 131" in text, "missing exact 131/131 verbose summary")
    passed = re.findall(r"^\s*(\d+)/131 Test\s+#\s*(\d+):\s+(\S+)\s+.*?\bPassed\b", text, re.M)
    need(len(passed) == 131 and collections.Counter(x[2] for x in passed) == collections.Counter(freeze["test_names"]),
         "verbose per-test passed names differ")
    need({int(x[0]) for x in passed} == set(range(1, 132)) and {int(x[1]) for x in passed} == set(range(1, 132)),
         "verbose test/pass ordinals incomplete")
    outputs = {}
    for block, registered_test in zip(blocks, registered):
        test = block["name"]
        need(block["argv"] == registered_test["argv"] and block["directory"] == str(build), "executed CTest argv/directory differs: " + test)
        if name == "sanitize":
            env = properties.get(test, {}).get("ENVIRONMENT", "")
            need("ASAN_OPTIONS=detect_leaks=1:halt_on_error=1" in env and
                 "UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1" in env, "sanitizer runtime policy absent: " + test)
        numeric_contract(test, block["output"])
        rows = output_rows(block["output"], test, source, build, name)
        command = registered_test["command"]
        if test in history["tests"]:
            old = history["tests"][test]
            need(command == old["command"], "legacy command changed: " + test)
            compare_rows("O07_legacy", test, name, old["rows"]["comparison"], rows["comparison"], "O07-release")
        if test in PREPARATION:
            prep = V / PREPARATION[test]
            before = output_rows(read(prep), test, ROOT, ROOT / "build/release", label(prep))
            compare_rows("accepted_preparation", test, name, before["comparison"], rows["comparison"], label(prep))
        outputs[test] = {"ordinal": block["ordinal"], "passed": True, "command": command,
                         "raw_command": block["argv"], "rows": rows,
                         "output_sha256": hashlib.sha256(block["output"].encode()).hexdigest()}
    compilation = compile_audit(name, folder, source, build, history["expected_sources"], vendor[1], configure_text, build_text)
    verbose_path = V / ("statistics-clean-source.log" if name == "clean-source" else f"statistics-{name}-test.log")
    return {"status": "audited_pass", "summary": {"path": label(summary_path), "sha256": digest(summary_path)},
            "registration": {"path": label(folder / "CTestTestfile.cmake"), "sha256": digest(folder / "CTestTestfile.cmake")},
            "raw_lasttest": {"path": label(last_path), "sha256": digest(last_path)},
            "raw_verbose": {"path": label(verbose_path), "sha256": digest(verbose_path)},
            "registered_test_names": [t["name"] for t in registered],
            "actual_order": [t["name"] for t in registered], "tests": outputs,
            "test_outcomes": [{"ordinal": b["ordinal"], "name": b["name"], "status": "passed", "command": b["argv"]} for b in blocks],
            "numeric_rows_observed": sum(len(item["rows"]["raw"]) for item in outputs.values()),
            "compilation": compilation, "warning_policy": warning_scope, "source_root": str(source), "build_root": str(build)}


def symbol_audit(name, matrix):
    if matrix.get("status") != "audited_pass":
        PENDING.append(name + ": symbols await a complete audited terminal matrix record")
        return {"status": "pending"}
    path = V / f"statistics-{name}-symbols.json"
    record = terminal(path, "status")
    if record is None:
        return {"status": "pending"}
    need(record.get("configuration") == name and record.get("status") == "captured; independent semantic audit pending",
         "new symbol capture is not terminal/correctly scoped")
    need(record.get("collector_sha256") == digest(Path("/tmp/crown-statistics-symbols.py")), "new symbol collector identity changed")
    roles = {"plan", "planner_testing", "runtime", "runtime_testing", "explain", "explain_testing"}
    if name == "sanitize":
        roles.add("parser_undefined")
    rows = record.get("records", [])
    need(len(rows) == len(roles) and {r.get("role") for r in rows} == roles, "new symbol role set differs")
    build = Path(matrix["build_root"])
    texts, result = {}, {}
    for item in rows:
        role = item["role"]
        archive = build / ("_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" if role == "parser_undefined" else f"libcrown_{role}.a")
        need(item.get("archive") == str(archive) and item.get("exit_code") == 0 and item.get("archive_stable") is True,
             "symbol archive/capture binding differs: " + role)
        expected_command = ["nm", "-C", "--undefined-only" if role == "parser_undefined" else "--defined-only", str(archive)]
        need(item.get("command") == expected_command, "symbol dump used wrong selection/command")
        dump = V / f"statistics-{name}-{role}.nm"
        stderr = V / f"statistics-{name}-{role}.nm.stderr"
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
        result[role] = {"baseline_definitions": baseline_count, "runtime_probe_methods": probes}
    return {"status": "audited_pass", "metadata": label(path), "roles": result,
            "parser_both_sanitizers": name == "sanitize"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--allocation-review", type=Path)
    args = parser.parse_args()
    output = args.output.resolve()
    designated = re.fullmatch(r"statistics-matrix-(?:evidence-audit(?:-[A-Za-z0-9_.-]+)?|audit-[A-Za-z0-9_.-]+)\.json", output.name)
    allowed = (output.parent == V and designated is not None) or str(output).startswith("/tmp/crown-c01-audit-")
    need(allowed and output.suffix == ".json" and not output.exists() and not output.with_suffix(".log").exists(),
         "output must be a new designated statistics audit artifact, never an existing file")
    approvals = guarded("allocation review", lambda: load_approvals(args.allocation_review))
    pins = guarded("immutable input pins", input_pins)
    freeze = guarded("C01 current freeze", freeze_audit)
    history = guarded("O07 historical baseline", historical)
    vendor = guarded("pinned vendor recipe", parser_inventory)
    matrix, symbols = {}, {}
    if not ERRORS and freeze.get("status") == "audited_pass" and "expected_sources" in history and isinstance(vendor, tuple):
        guarded("legacy registration order", lambda: need(history["ordered_names"] == freeze["legacy_names"], "O07 raw order differs from retained freeze order"))
        for name in CONFIGS:
            matrix[name] = guarded(name, lambda name=name: audit_configuration(name, freeze, history, vendor))
        # A fixed reference keeps review identities stable across partial runs.
        reference_name = "release" if matrix["release"].get("status") == "audited_pass" else None
        if reference_name is None:
            PENDING.append("release: cross-configuration command/numeric baseline unavailable")
        for name in CONFIGS:
            if reference_name and matrix[name].get("status") == "audited_pass":
                def compare(name=name):
                    for test, observed in matrix[name]["tests"].items():
                        reference = matrix[reference_name]["tests"][test]
                        need(observed["command"] == reference["command"], "cross-configuration CTest command differs: " + test)
                        compare_rows("cross_configuration", test, name, reference["rows"]["comparison"],
                                     observed["rows"]["comparison"], reference_name)
                    return {"status": "audited_pass"}
                matrix[name]["cross_configuration"] = guarded(name + " rows/commands", compare)
            symbols[name] = guarded(name + " symbols", lambda name=name: symbol_audit(name, matrix[name]))
    unused = set(APPROVALS) - USED_APPROVALS
    raw_matrix_complete = len(matrix) == 5 and all(m.get("status") == "audited_pass" for m in matrix.values())
    if unused and raw_matrix_complete:
        ERRORS.append("unused/stale allocation approvals: " + ", ".join(sorted(unused)))
    unapproved = [item for item in REVIEW if not item["root_approved"]]
    complete = (len(matrix) == len(symbols) == 5 and not ERRORS and not PENDING and not unapproved and
                all(m.get("status") == "audited_pass" for m in matrix.values()) and
                all(s.get("status") == "audited_pass" for s in symbols.values()))
    state = ("accepted_final_matrix" if complete else "matrix_needs_review" if ERRORS else
             "preliminary_pending_matrix" if PENDING else "allocation_review_required")
    if "expected_sources" in history:
        history["expected_sources"] = [{"target": t, "source": s} for t, s in sorted(history["expected_sources"])]
    result = {
        "card": "C01", "audit_state": state, "accepted": complete, "accepted_matrix_evidence": complete,
        "changes_project_status": False, "auditor": {"path": label(Path(__file__)), "sha256": digest(Path(__file__))},
        "input_pin_check": pins, "freeze": freeze, "historical": history,
        "matrix": matrix, "symbols": symbols, "allocation_review_record": approvals,
        "allocation_differences": REVIEW, "normalizations": NORMALIZATIONS,
        "unapplied_allocation_approval_ids": sorted(unused),
        "vendor_source_inventory": sorted(vendor[0]) if isinstance(vendor, tuple) else vendor,
        "read_evidence_sha256": READ_PINS, "errors": ERRORS, "pending": PENDING,
        "policy": "Evidence reads/hashes only. No subprocess, project import, binary, build, test, symbol command or process poll. Ten historical manifest FILE hashes only. No fixed stdout row total or implicit allocation waiver.",
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n")
    lines = [state, "accepted_matrix_evidence=" + str(complete),
             *[name + ": " + item["status"] for name, item in matrix.items()],
             "unapproved_allocation_differences=" + str(len(unapproved)),
             "pending=" + json.dumps(PENDING), "errors=" + json.dumps(ERRORS)]
    output.with_suffix(".log").write_text("\n".join(lines) + "\n")
    print("\n".join(lines))
    return 0 if complete else 1 if ERRORS else 2 if PENDING else 3


if __name__ == "__main__":
    raise SystemExit(main())
