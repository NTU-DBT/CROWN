#!/usr/bin/env python3
"""Exercise real example reports against ENOSPC without undoing durable work.

Reuse existing example binaries and build missing native/reoptimization clients
through their installed standalone CMake projects. No production target is added.
A working /dev/full character device is required (CTest skip code 77 otherwise).
"""
import argparse
import errno
import hashlib
import json
import os
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile


def require(value, message):
    if not value:
        raise RuntimeError(message)


def encoded(value):
    return json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":"))


def run(command, fail_output=False):
    command = [str(item) for item in command]
    if fail_output:
        with open("/dev/full", "wb", buffering=0) as sink:
            result = subprocess.run(command, stdout=sink, stderr=subprocess.PIPE, timeout=240)
        require(result.returncode == 1,
                f"failed report returned {result.returncode}: {command}; {result.stderr[-2000:]!r}")
        # The existing stream-state exit is silent. A domain/input failure must
        # not masquerade as a successfully exercised report-output failure.
        require(not result.stderr, f"example failed before reporting: {command}; {result.stderr[-2000:]!r}")
        return None
    result = subprocess.run(command, capture_output=True, timeout=240)
    require(result.returncode == 0,
            f"normal output failed: {command}; {result.stderr[-2000:]!r}")
    return result.stdout


def report(command):
    return json.loads(run(command))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", required=True, type=Path)
    parser.add_argument("--crown", required=True, type=Path)
    parser.add_argument("--native-workflow", type=Path)
    parser.add_argument("--build", type=Path)
    parser.add_argument("--compiler")
    parser.add_argument("--sanitize", default="OFF")
    parser.add_argument("--workload-measurement", required=True, type=Path)
    parser.add_argument("--ranking-evaluation", required=True, type=Path)
    parser.add_argument("--cost-calibration", required=True, type=Path)
    parser.add_argument("--reoptimization", type=Path)
    args = parser.parse_args()
    if not Path("/dev/full").is_char_device():
        print("SKIP: example-output regression requires /dev/full", file=sys.stderr)
        return 77
    descriptor = os.open("/dev/full", os.O_WRONLY)
    try:
        try:
            os.write(descriptor, b"x")
        except OSError as error:
            require(error.errno == errno.ENOSPC, "failing device did not report ENOSPC")
        else:
            raise RuntimeError("/dev/full unexpectedly accepted output")
    finally:
        os.close(descriptor)

    root = args.source.resolve()
    fixture = root / "tests/workflow/projected_collision"
    query, catalog = fixture / "query.sql", fixture / "catalog.json"
    expected = json.loads((fixture / "expected_oracle.json").read_text())
    with tempfile.TemporaryDirectory(prefix="crown-example-output-") as temporary:
        base = Path(temporary)
        if args.native_workflow is None or args.reoptimization is None:
            require(args.build is not None and args.compiler is not None,
                    "missing public client paths require --build and --compiler")
            stage, prefix = base / "stage", base / "moved prefix"
            run(["cmake", "--install", args.build.resolve(), "--prefix", stage])
            stage.rename(prefix)
            configs = list(prefix.rglob("CrownConfig.cmake"))
            require(len(configs) == 1, "installed SDK package config is ambiguous")
            for example, target, attribute in (
                    ("native-workflow", "crown_native_workflow", "native_workflow"),
                    ("reoptimization", "crown_reoptimization", "reoptimization")):
                if getattr(args, attribute) is not None:
                    continue
                source, consumer = base / (example + "-source"), base / (example + "-build")
                shutil.copytree(prefix / "share/crown/examples" / example, source)
                configure = ["cmake", "-S", source, "-B", consumer, "-DCMAKE_BUILD_TYPE=Release",
                             "-DCMAKE_CXX_COMPILER=" + args.compiler,
                             "-DCrown_DIR=" + str(configs[0].parent), "-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF"]
                if args.sanitize.upper() in ("ON", "TRUE", "1", "YES"):
                    configure += ["-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer"]
                run(configure)
                run(["cmake", "--build", consumer, "--parallel", "2"])
                setattr(args, attribute, consumer / target)
        canonical = report([args.crown, "canonicalize-catalog", catalog])
        digest = hashlib.sha256(encoded(canonical).encode()).hexdigest()
        events = [json.loads(line) for line in (fixture / "events.template.jsonl").read_text().splitlines()]
        for event in events:
            event["catalog_sha256"] = digest
        updates = base / "input.jsonl"
        updates.write_text("".join(encoded(event) + "\n" for event in events))
        compiled = report([args.crown, "compile", query, catalog])
        artifact = base / "compiled.json"
        artifact.write_text(encoded(compiled))

        def workflow(action, directory, count):
            return [args.native_workflow, action, query, catalog, updates,
                    directory / "state.root", directory / "results.sink", count]

        normal, failed = base / "workflow-normal", base / "workflow-failed"
        normal.mkdir()
        failed.mkdir()
        control = report(workflow("run", normal, 2))
        require(control["sequence"] == control["verified_output_sequence"] == 2 and
                control["rows"] == expected["events"][1]["current_rows"], "workflow control differs")
        run(workflow("run", failed, 2), fail_output=True)
        # A failed report is not a rollback of the two already committed epochs.
        resumed = report(workflow("restore", failed, 1))
        position = events[2]["source_position"]
        require(resumed["sequence"] == resumed["verified_output_sequence"] == 3 and
                resumed["rows"] == expected["events"][2]["current_rows"] and
                resumed["source_positions"] == {position["source"]: position["offset"]},
                "workflow stdout failure lost committed state or replay position")

        request = {"schema_version": 1, "command": "verify", "output_mode": "maintenance",
                   "codec": "none", "sink": "discard", "sink_delay_us": 0,
                   "observation": "off", "workload_counters": False,
                   "memory_limit_bytes": 64 * 1024 * 1024, "max_events": len(events),
                   "max_output_calls": 1024, "max_encoded_bytes": 1024 * 1024,
                   "phases": [], "label": "example-output-failure", "preflight_receipt_sha256": None}
        request_path, oracle = base / "collector-request.json", base / "empty-oracle.json"
        request_path.write_text(encoded(request))
        oracle.write_text(encoded({"initial_rows": expected["initial_current_rows"], "epochs": []}))
        empty = base / "empty.jsonl"
        empty.write_text("")
        collector = [args.workload_measurement, artifact, empty, request_path, oracle, base / "unused-sink"]
        short = run(collector)
        require(len(short) < 4096 and json.loads(short)["verified"],
                "collector control must exercise a short buffered verification report")
        run(collector, fail_output=True)
        request["command"] = "measure"
        request["phases"] = ["fixture"] * len(events)
        request_path.write_text(encoded(request))
        collector = [args.workload_measurement, artifact, updates, request_path, "-", base / "unused-sink"]
        require(report(collector)["sequence"] == len(events), "measurement control differs")
        run(collector, fail_output=True)

        ranking_request = {"schema_version": 1, "physical_options": compiled["physical"]["options"],
                           "candidate_limit": 1, "search_work": 10000000, "enumeration_work": 10000000,
                           "memory_limit_bytes": 64 * 1024 * 1024, "max_events": len(events),
                           "require_exhausted_family": False, "fallback": "require_evidence", "slot_limit": None}
        ranking_path = base / "ranking-request.json"
        ranking_path.write_text(encoded(ranking_request))
        ranking = [args.ranking_evaluation, query, catalog, updates, ranking_path]
        require(report(ranking)["training_events"] == len(events), "ranking control differs")
        run(ranking, fail_output=True)
        calibration = [args.cost_calibration, query, catalog, updates, 1, 1, 1]
        control = report(calibration)
        require(control["kind"] == "c03_measured_calibration" and
                control["candidates"][0]["records_per_repetition"] == 1, "calibration control differs")
        run(calibration, fail_output=True)

        for backend in ("reference", "indexed"):
            normal, failed = base / (backend + "-normal"), base / (backend + "-failed")
            control = run([args.reoptimization, "run", normal, backend])
            first = json.loads(control)
            require(len(control) < 512 and first["switched"] and first["sequence"] == 9 and
                    first["sink_sequence"] == 9 and first["exists"] is False,
                    "reoptimization control must exercise a short committed report")
            run([args.reoptimization, "run", failed, backend], fail_output=True)
            resumed = report([args.reoptimization, "resume", failed, backend])
            require(resumed["sequence"] == resumed["sink_sequence"] == 10 and resumed["exists"] is True and
                    resumed["generation"] == resumed["first_generation"] == 3 and
                    resumed["origin_generation"] == 1 and resumed["source_offset"] == 100,
                    "report failure changed durable reoptimization/retirement/sink progress")
    print("PASS: all five actual examples reject failed stdout; short buffered reports and durable recovery preserved")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as error:
        print(str(error), file=sys.stderr)
        raise SystemExit(1)
