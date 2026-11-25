#!/usr/bin/env python3
"""Compare native C++ F-IVM and CROWN on Epinions filtered 3-Hop."""

import argparse
from collections import Counter, deque
import csv
import hashlib
import json
import os
from pathlib import Path
import random
import signal
import sqlite3
import statistics
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "benchmarks/paper_replay"))
import run as paper  # noqa: E402

CASE = "runtime-length3_filter-full-reference_ordered_v1"
ORACLE = (ROOT / "build/experiments/paper-completion-audit-20261116-v1"
          / "epinions-marker-cardinality-oracle.json")
ENGINES = ("crown", "numeric", "signed")


def write_json(path, data):
    path.write_text(json.dumps(data, indent=2) + "\n")


def sha256(path):
    with path.open("rb") as source:
        return hashlib.file_digest(source, "sha256").hexdigest()


def build_fixture(path):
    lines = [
        "+,1,2", "+,4,2", "+,2,3", "+,3,32684", "*",
        "+,3,40000", "+,3,40001", "*", "-,3,40000", "*",
        "-,3,40001", "*", "+,3,40000", "*", "-,2,3", "*",
        "+,2,3", "*", "-,4,2", "*", "-,1,2", "-,2,3",
        "-,3,32684", "-,3,40000", "*",
    ]
    rng = random.Random(20261123)
    vertices = list(range(1, 11)) + list(range(32679, 32695))
    edges = [(left, right) for left in vertices for right in vertices]
    active = set()
    for i in range(800):
        if active and (len(active) == 100 or rng.random() < 0.45):
            edge = rng.choice(sorted(active))
            active.remove(edge)
            operation = "-"
        else:
            edge = rng.choice([edge for edge in edges if edge not in active])
            active.add(edge)
            operation = "+"
        lines.append(f"{operation},{edge[0]},{edge[1]}")
        if i % 5 == 0:
            lines.append("*")
    lines.extend(f"-,{left},{right}" for left, right in sorted(active))
    lines.append("*")
    path.write_text("\n".join(lines) + "\n")


def fixture_oracle(path):
    with sqlite3.connect(":memory:") as db:
        db.execute("CREATE TABLE edge (src INTEGER, dst INTEGER, PRIMARY KEY (src, dst))")
        sql = """SELECT g1.src, g1.dst, g2.dst, g3.dst
                 FROM edge g1 JOIN edge g2 ON g1.dst = g2.src
                 JOIN edge g3 ON g2.dst = g3.src WHERE g3.dst > 32684"""
        frames = []
        sequence = 0
        for line in path.read_text().splitlines():
            if line == "*":
                frames.append((sequence, sorted(db.execute(sql))))
                continue
            sign, left, right = line.split(",")
            statement = ("INSERT INTO edge VALUES (?, ?)" if sign == "+"
                         else "DELETE FROM edge WHERE src = ? AND dst = ?")
            if db.execute(statement, (int(left), int(right))).rowcount != 1:
                raise ValueError(f"invalid fixture edit {line}")
            sequence += 1
        frames.append((sequence, sorted(db.execute(sql))))
    return frames


def bounded_epinions(source, destination):
    """Keep the first 25,000 inserts, with a 4,096-edge sliding window."""
    active = deque()
    frames = []
    insertions = sequence = 0
    with source.open() as raw, destination.open("w") as stream:
        for line in raw:
            if not line.startswith("+,"):
                continue
            if len(active) == 4096:
                left, right = active.popleft()
                stream.write(f"-,{left},{right}\n")
                sequence += 1
            _, left, right = line.strip().split(",")
            active.append((int(left), int(right)))
            stream.write(line)
            insertions += 1
            sequence += 1
            if insertions % 2048 == 0 or insertions == 25_000:
                stream.write("*\n")
                incoming = Counter(right for _, right in active)
                outgoing = Counter(left for left, right in active if right > 32684)
                count = sum(incoming[left] * outgoing[right] for left, right in active)
                frames.append({"sequence": sequence, "counts": {"32684": {"l3-full": count}}})
            if insertions == 25_000:
                break
        if insertions != 25_000:
            raise ValueError("bounded input ended early")
        for left, right in active:
            stream.write(f"-,{left},{right}\n")
            sequence += 1
    return {"source_sha256": sha256(destination), "physical_edits": sequence,
            "final_empty": True, "frames": frames}


def capture_frames(path, engine):
    frames = []
    with path.open() as source:
        for line in source:
            if engine == "crown":
                record = json.loads(line)
                if record["kind"] in ("snapshot_begin", "final_begin"):
                    frames.append((record["sequence"], []))
                elif record["kind"] in ("snapshot_row", "final_row"):
                    frames[-1][1].append(tuple(record["values"]))
            else:
                marker, *cells = line.strip().split(",")
                if marker == "*":
                    frames.append((int(cells[0]), []))
                else:
                    frames[-1][1].append(tuple(map(int, (marker, *cells))))
    return [(sequence, sorted(rows)) for sequence, rows in frames]


def replay(args, binaries, route, directory, engine, mode, source, verify=False):
    directory.mkdir()
    capture = directory / "capture"
    overrides = {"CROWN_ENGINE": "flat", "CROWN_OBS_OFF": "1", "CROWN_GC": "blocking"}
    env = {key: value for key, value in os.environ.items() if not key.startswith("CROWN_")}
    env.update(overrides)
    binary = str(binaries[engine])
    if engine == "crown":
        request = dict(route, command="verify" if verify else "measure",
                       output_mode=mode, full_at_markers=mode == "full")
        if verify:
            request["capture_file"] = str(capture)
        request_file = directory / "request.json"
        write_json(request_file, request)
        command = [binary, str(request_file), str(source)]
    else:
        command = [binary, str(source), mode]
        if verify:
            command.append(str(capture))
    command = ["/usr/bin/time", "-f", "%e %M %x", "-o", str(directory / "time"),
               "taskset", "-c", str(args.cpu), *command]
    write_json(directory / "command.json", {"argv": command, "environment": overrides})
    with (directory / "stdout.json").open("w") as stdout, (directory / "stderr").open("w") as stderr:
        process = subprocess.Popen(command, env=env, stdout=stdout, stderr=stderr,
                                   start_new_session=True)
        try:
            status = process.wait(timeout=args.timeout)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()
            raise
    if status:
        raise RuntimeError(f"{engine}/{mode} exited {status}: {directory / 'stderr'}")
    return json.loads((directory / "stdout.json").read_text())


def check_fixture(args, binaries, route, out):
    source = out / "fixture.csv"
    build_fixture(source)
    expected = fixture_oracle(source)
    write_json(out / "fixture-oracle.json", expected)
    checks = {}
    for engine in (*ENGINES, "factorized"):
        directory = out / f"verify-{engine}"
        replay(args, binaries, route, directory, engine, "full", source, verify=True)
        actual = capture_frames(directory / "capture", engine)
        mismatch = next((i for i, (left, right) in enumerate(zip(expected, actual))
                         if left != right), None)
        if mismatch is None and len(expected) != len(actual):
            mismatch = min(len(expected), len(actual))
        checks[engine] = {"expected_frames": len(expected), "actual_frames": len(actual),
                          "expected_rows": sum(len(rows) for _, rows in expected),
                          "first_mismatch_index": mismatch}
        if mismatch is not None and mismatch < min(len(expected), len(actual)):
            sequence, expected_rows = expected[mismatch]
            _, actual_rows = actual[mismatch]
            checks[engine].update(sequence=sequence, expected=expected_rows, actual=actual_rows)
    write_json(out / "fixture-checks.json", checks)
    if any(checks[engine]["first_mismatch_index"] is not None for engine in ENGINES):
        raise RuntimeError("a timed engine failed the exact SQLite fixture comparison")


def check_paper(report, oracle, mode, relation_updates):
    expected = [(frame["sequence"], frame["counts"]["32684"]["l3-full"])
                for frame in oracle["frames"]] if mode == "full" else []
    actual = [(frame["sequence"], frame["rows"]) for frame in report["snapshots"]]
    if (actual != expected or report["physical_inputs"] != oracle["physical_edits"]
            or report["relation_updates"] != relation_updates
            or report["enumeration_markers"] != len(oracle["frames"])
            or report["snapshot_rows"] != sum(rows for _, rows in expected)
            or report.get("final_rows") not in (0, None)
            or report.get("threads", 1) != 1):
        raise RuntimeError(f"campaign replay mismatch: expected frames {expected}, report {report}")


def write_csv(path, records):
    with path.open("w", newline="") as destination:
        writer = csv.DictWriter(destination, fieldnames=tuple(records[0]))
        writer.writeheader()
        writer.writerows(records)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--work", type=Path, required=True)
    parser.add_argument("--crown", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--cpu", type=int, required=True)
    parser.add_argument("--repetitions", type=int, default=3)
    parser.add_argument("--timeout", type=int, default=300)
    parser.add_argument("--engines", nargs="+", choices=ENGINES, default=ENGINES)
    parser.add_argument("--bounded", action="store_true", help="use the derived 25k-insert workload")
    args = parser.parse_args()
    if args.repetitions < 1 or args.cpu not in os.sched_getaffinity(0):
        parser.error("select a permitted CPU and at least one repetition")
    if len(set(args.engines)) != len(args.engines):
        parser.error("select each engine at most once")
    args.work, args.crown, out = (path.resolve() for path in (args.work, args.crown, args.out))
    out.mkdir()
    group = next(group for group in paper.cases() if group["case_id"] == CASE)
    _, route = paper.request_for(group)
    campaign_source = Path(group["input"]["path"])
    campaign_hash = sha256(campaign_source)
    campaign_oracle = json.loads(ORACLE.read_text())
    if campaign_oracle["source_sha256"] != campaign_hash or not campaign_oracle["final_empty"]:
        raise ValueError("unexpected campaign input or oracle")
    source, oracle_path, oracle = campaign_source, ORACLE, campaign_oracle
    if args.bounded:
        source, oracle_path = out / "bounded.csv", out / "bounded-oracle.json"
        oracle = bounded_epinions(campaign_source, source)
        write_json(oracle_path, oracle)
    live_edges = set()
    relation_updates = 0
    with source.open() as stream:
        for line in stream:
            if line == "*\n":
                continue
            operation, left, right = line.strip().split(",")
            edge = int(left), int(right)
            if operation == "+" and edge not in live_edges:
                live_edges.add(edge)
            elif operation == "-" and edge in live_edges:
                live_edges.remove(edge)
            else:
                raise ValueError(f"campaign is not a valid set stream: {line!r}")
            relation_updates += 2 + (edge[1] > 32684)
    if live_edges:
        raise ValueError("campaign stream failed to drain")
    binaries = {name: args.work / "native" / name / "replay"
                for name in ("numeric", "factorized", "signed")}
    binaries["crown"] = args.crown
    write_json(out / "manifest.json", {
        "case": CASE, "source": str(source), "source_sha256": oracle["source_sha256"],
        "campaign_source_sha256": campaign_hash, "oracle": str(oracle_path),
        "oracle_sha256": sha256(oracle_path), "bounded": args.bounded,
        "binding": group["binding"], "binding_sha256": sha256(Path(group["binding"])),
        "cpu": args.cpu, "repetitions": args.repetitions, "engines": args.engines,
        "relation_updates": relation_updates,
        "binaries": {name: {"path": str(path), "sha256": sha256(path)}
                     for name, path in binaries.items()},
    })
    check_fixture(args, binaries, route, out)
    print("Exact fixture checks recorded", flush=True)
    samples = []
    for mode in ("none", "full"):
        for iteration in range(args.repetitions + 1):
            offset = iteration % len(args.engines)
            order = args.engines[offset:] + args.engines[:offset]
            for engine in order:
                directory = out / f"{mode}-{iteration}-{engine}"
                report = replay(args, binaries, route, directory, engine, mode, source)
                check_paper(report, oracle, mode, relation_updates)
                wall, rss, _ = (directory / "time").read_text().split()
                print(f"{mode} {iteration} {engine}: {wall}s {rss} KiB", flush=True)
                if iteration:
                    samples.append({
                        "mode": mode, "engine": engine, "repetition": iteration,
                        "wall_s": float(wall), "loop_s": report["loop_wall_ns"] / 1e9,
                        "output_s": report["output_ns"] / 1e9, "maxrss_kib": int(rss),
                        "physical_inputs": report["physical_inputs"],
                        "relation_updates": report["relation_updates"],
                        "snapshot_rows": report["snapshot_rows"],
                    })
                    write_csv(out / "samples.csv", samples)
    summary = []
    for mode in ("none", "full"):
        for engine in args.engines:
            selected = [row for row in samples if row["mode"] == mode and row["engine"] == engine]
            summary.append({"mode": mode, "engine": engine, "repetitions": len(selected),
                            **{f"median_{key}": statistics.median(row[key] for row in selected)
                               for key in ("wall_s", "loop_s", "output_s", "maxrss_kib")}})
    write_csv(out / "summary.csv", summary)


if __name__ == "__main__":
    main()
