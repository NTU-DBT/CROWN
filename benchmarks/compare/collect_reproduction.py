#!/usr/bin/env python3
"""Audit and collect the comparison campaign, archived Flink p1 and final C++ replay."""

import argparse
from collections import Counter, defaultdict
import csv
from functools import cache
import hashlib
import json
from pathlib import Path
import statistics

import plan
from report import CXX_CONFIGS, accumulate_s


def read_json(path):
    return json.loads(path.read_text())


@cache
def digest(path):
    with path.open("rb") as source:
        return hashlib.file_digest(source, "sha256").hexdigest()


def demand(condition, message):
    if not condition:
        raise ValueError(message)


def load_jobs(directory):
    entries = [json.loads(line) for line in (directory / "jobs.jsonl").read_text().splitlines()]
    jobs = {job["id"]: job for job in entries}
    demand(len(jobs) == len(entries), f"duplicate job IDs in {directory}")
    return jobs


def input_identity(receipt, arguments):
    source = arguments[arguments.index("--input") + 1]
    return receipt["input_sha256"][source]


def flink_metrics(path, parallelism, mode, expected_input):
    evidence = read_json(path / "run-receipt.json")
    demand(evidence["status"] == "complete" and evidence["exit_code"] == 0
           and evidence["timed_out"] is False and evidence["input_bytes_unchanged"] is True
           and evidence["purpose"] == "measurement" and evidence["original_job_code_modified"] is False
           and evidence["custom_baseline_observer_used"] is False, "Flink receipt did not qualify")
    demand(evidence["parallelism"] == parallelism and evidence["mode"] == mode
           and len(evidence["cpus"]) == parallelism, "Flink protocol or affinity mismatch")
    demand(expected_input in evidence["input_sha256"].values(), "Flink input fingerprint mismatch")
    for name, key in (("stdout", "stdout_sha256"), ("stderr", "stderr_sha256"),
                      ("target-maxrss.txt", "resource_file_sha256")):
        demand(digest(path / name) == evidence[key], f"Flink {name} fingerprint mismatch")
    timer = accumulate_s(path / "stdout")
    rss = int((path / "target-maxrss.txt").read_text())
    demand(timer is not None and timer > 0 and rss == evidence["process_maxrss_KiB"],
           "Flink timing or RSS is incomplete")
    return {"wall_s": evidence["wall_ns"] / 1e9, "accumulate_s": timer,
            "rss_kib": rss, "cores": parallelism, "engine": "original-flink",
            "cpus": ",".join(map(str, evidence["cpus"])),
            "input_sha256": expected_input}


def time_metrics(path, receipt):
    wall, user, system, rss = (path / "time.txt").read_text().split()
    demand((float(wall), float(user), float(system), int(rss)) ==
           tuple(receipt[key] for key in ("time_wall_s", "user_s", "sys_s", "maxrss_kib")),
           "GNU time values differ from the scheduler receipt")
    return {"wall_s": float(wall), "cpu_s": float(user) + float(system), "rss_kib": int(rss)}


def row_signature(report):
    return (
        *(report[key] for key in ("physical_inputs", "relation_updates", "enumeration_markers",
                                   "snapshot_rows", "delta_rows")),
        tuple((frame["sequence"], frame.get("rows", frame.get("groups")))
              for frame in report["snapshots"]),
    )


def native_metrics(path, job, receipt, group):
    report = read_json(path / "stdout")
    command = read_json(path / "command.json")
    meta = job["meta"]
    demand(command["command"][-3:] == job["cmd"] and command["env"] == job["env"]
           and command["cpus"] == receipt["cpus"], "C++ executable, request or affinity differs")
    gc = report["gc"]
    pool = {"64M": 64 * 2**20, "256M": 256 * 2**20, "4G": 4 * 2**30,
            "unlimited": 2**64 - 1}[meta["pool"]]
    demand(report["status"] == "complete" and report["output_mode"] == meta["mode"]
           and report["threads"] == job["cores"] and report["physical_inputs"] == group["physical_events"]
           and gc["mode"] == meta["gc"] and gc["pool_bytes"] == pool, "C++ protocol mismatch")
    return {**time_metrics(path, receipt), "engine": report["engine"], "threads": report["threads"],
            "algorithm": report.get("cyclic_algorithm"), "fused": report.get("fused"),
            "gc_collections": gc["collections"], "loop_s": report["loop_wall_ns"] / 1e9,
            "apply_s": report["apply_ns"] / 1e9, "output_s": report["output_ns"] / 1e9,
            "binary_sha256": digest(Path(job["cmd"][0])),
            "request_sha256": digest(Path(job["cmd"][1])),
            "input_sha256": group["input"].get("sha256"),
            **{key: report[key] for key in ("physical_inputs", "relation_updates", "snapshot_rows", "delta_rows")}}


def fivm_metrics(path, mode, peer):
    result = read_json(path / "out/result.json")
    oracle = read_json(plan.ROOT / "benchmarks/fivm_replay/oracle" / f"{result['query']}.json")
    demand(result["ok"] is True and result["mode"] == mode and result["exit_status"] == 0
           and result["timed_out"] is False and result["validation"]["matched"] is True
           and result["final_rows"] == 0 and digest(Path(result["binary"])) == result["binary_sha256"],
           "F-IVM success, validation or binary identity mismatch")
    wall, user, system, rss = (path / "out/time.txt").read_text().split()
    demand((float(wall), float(user), float(system), int(rss)) ==
           tuple(result[key] for key in ("wall_s", "user_s", "sys_s", "maxrss_kib")),
           "F-IVM raw timing differs from the run result")
    for key in ("physical_inputs", "relation_updates", "enumeration_markers"):
        demand(result[key] == oracle[key], f"F-IVM oracle mismatch for {key}")
    keys = ("physical_inputs", "relation_updates", "enumeration_markers", "snapshot_rows")
    demand(tuple(result[key] for key in keys) == row_signature(peer)[:4],
           "F-IVM and C++ CROWN produced different input or snapshot counts")
    if mode == "full":
        actual = [(f["sequence"], f["rows"]) for f in result["snapshots"]]
        expected = [(f["sequence"], f["rows"]) for f in oracle["snapshots"]]
        demand(actual == expected and result["snapshot_rows"] == oracle["snapshot_rows"],
               "F-IVM snapshot counts differ from the archived oracle")
        demand(tuple(actual) == row_signature(peer)[-1], "F-IVM marker counts differ from C++ CROWN")
    return {"wall_s": result["wall_s"], "cpu_s": result["user_s"] + result["sys_s"],
            "rss_kib": result["maxrss_kib"], "loop_s": result["loop_s"],
            "output_s": result["output_s"], "engine": result["engine"],
            **{key: result[key] for key in ("binary_sha256", "physical_inputs",
                                           "relation_updates", "snapshot_rows")}}


def track_campaign(directory, cohort, jobs, groups, flink_points, history_signatures, samples, issues):
    counts = Counter()
    for job_id, job in jobs.items():
        directory_for_job = directory / "runs" / job_id
        receipt_path = directory_for_job / "job.json"
        kind = job["kind"]
        meta = job["meta"]
        if not receipt_path.exists():
            counts[kind, "unfinished"] += 1
            continue
        try:
            receipt = read_json(receipt_path)
            demand(receipt["id"] == job_id and receipt["status"] == "ok"
                   and receipt["exit"] == 0 and not receipt["timed_out"], "job did not exit successfully")
            demand(len(set(receipt["cpus"])) == receipt["cores"] == job["cores"], "CPU count mismatch")
            case = meta.get("case")
            mode = meta.get("mode") or (groups[case]["mode"] if case else None)
            sample = {"cohort": cohort, "system": kind, "case": case, "mode": mode,
                      "configuration": meta.get("config"), "repetition": meta.get("rep"),
                      "cores": receipt["cores"], "cpus": ",".join(map(str, receipt["cpus"])),
                      "evidence": str(directory_for_job.relative_to(plan.ROOT))}
            if kind == "cxx":
                sample.update(native_metrics(directory_for_job, job, receipt, groups[case]))
                signature = row_signature(read_json(directory_for_job / "stdout"))
                other = history_signatures.setdefault(case, signature)
                demand(other == signature, "input counts, delta total or snapshot frames differ from campaign")
            elif kind == "flink":
                parallelism = meta["parallelism"]
                point = flink_points[meta["flink_point"]]
                expected_input = point["run_trials"][0]["input_sha256"]
                inputs = read_json(directory_for_job / "run/run-inputs.json")
                demand(input_identity(inputs, job["cmd"]) == expected_input, "Flink source differs from the paper binding")
                sample.update(flink_metrics(directory_for_job / "run", parallelism, point["driver_mode"], expected_input),
                              configuration=f"p{parallelism}", cpu_s=time_metrics(directory_for_job, receipt)["cpu_s"])
            elif kind == "fivm":
                peer_case = case.removesuffix("-delta") + "-none" if mode == "none" else case
                peer = read_json(directory / "runs/cxx" / peer_case / "blocking-64M/r1/stdout")
                sample.update(fivm_metrics(directory_for_job, mode, peer),
                              case=peer_case, configuration="patched-native")
            else:
                verify_summary(directory_for_job / "out/summary.json")
            if kind != "verify":
                samples.append(sample)
            counts[kind, "accepted"] += 1
        except (OSError, ValueError, TypeError, KeyError) as error:
            counts[kind, "invalid"] += 1
            issues.append({"cohort": cohort, "job": job_id, "reason": str(error)})
    return {kind: {state: counts[kind, state] for state in ("accepted", "unfinished", "invalid")}
            for kind in sorted({job["kind"] for job in jobs.values()})}


def archive_flink(groups, points, samples, issues):
    recorded = read_json(plan.FLINK_MEDIANS)
    for case, group in groups.items():
        if group["mode"] == "none":
            continue
        median_record = recorded[plan.flink_key(case)]
        point = points[median_record["flink_point"]]
        paths = sorted(plan.ORIGINAL.glob(f"original-campaign-v*/runs/{point['point_id']}/rep-*/run-receipt.json"))
        try:
            demand(len(paths) == median_record["n"] == 10 and len({path.parent.name for path in paths}) == 10,
                   "archive does not have ten distinct repetitions")
            rows = []
            for path in paths:
                rep = int(path.parent.name.removeprefix("rep-"))
                trial = point["run_trials"][rep - 1]
                info = flink_metrics(path.parent, 1, point["driver_mode"], trial["input_sha256"])
                rows.append({"cohort": "archived-p1", "system": "flink", "case": case, "mode": group["mode"],
                             "configuration": "p1", "repetition": rep, **info,
                             "evidence": str(path.parent.relative_to(plan.ROOT))})
            for column, legacy_column in (("wall_s", "flink_wall_median_s"), ("accumulate_s", "flink_accumulate_median_s")):
                demand(abs(statistics.median(row[column] for row in rows) - median_record[legacy_column]) <= .0051,
                       f"archived p1 median mismatch for {column}")
            samples.extend(rows)
        except (OSError, ValueError, TypeError, KeyError) as error:
            issues.append({"cohort": "archived-p1", "job": case, "reason": str(error)})


def verify_summary(path):
    rows = read_json(path)
    demand(rows and all(row["identical"] and row["reference_status"] == row["flat_status"] == 0 for row in rows),
           f"exact row verification failed: {path}")
    by_case = {row["case"]: row for row in rows}
    demand(len(by_case) == len(rows), f"duplicate cases in {path}")
    return by_case


def larger_pools(rss_kib):
    return [name for name, threshold in (("blocking-256M", 256 * 1024), ("blocking-4G", 4 * 1024**2))
            if rss_kib > threshold]


def audit_matrix(historical, jobs, groups):
    """Check the intended plan independently of scheduler completion counts."""
    expected = {"verify/window", "verify/long"}
    for case, group in groups.items():
        prefix = f"cxx/{case}"
        configs = ["blocking-64M"]
        if group["mode"] != "none":
            configs += ["background-64M", "blocking-unlimited"]
            rss = read_json(historical / "runs" / prefix / "blocking-64M/r1/job.json")["maxrss_kib"]
            configs += larger_pools(rss)
            for p in (4, 16):
                expected.update(f"flink/{case}/p{p}/r{rep}" for rep in (1, 2, 3))
        if case.startswith("runtime-") and group["mode"] != "none":
            mode = "full" if group["mode"] == "full" else "none"
            expected.update(f"fivm/{case}/{mode}/r{rep}" for rep in (1, 2, 3))
        expected.update(f"{prefix}/{config}/r{rep}" for config in configs for rep in (1, 2, 3))
    campaign_p1 = {key for key, job in jobs.items()
                   if job["kind"] == "flink" and job["meta"]["parallelism"] == 1}
    actual = set(jobs) - campaign_p1
    return {"missing": sorted(expected - actual), "extra": sorted(actual - expected),
            "campaign_p1_trials": len(campaign_p1)}


def audit_replay_matrix(replay, jobs, final_jobs):
    manifest = read_json(replay / "reproduction.json")
    baseline = {key for key, job in jobs.items() if job["kind"] == "cxx"}
    build = Path(manifest["build"])
    demand(manifest["initial_job_count"] == len(baseline), "native replay staging count differs")
    for name, expected in manifest["binaries"].items():
        demand(digest(build / name) == expected, f"native replay build fingerprint changed: {name}")
    for key, job in final_jobs.items():
        if key in jobs:
            original = jobs[key]
            demand(job["cmd"][1:] == original["cmd"][1:] and job["meta"] == original["meta"]
                   and job["env"] == original["env"] and job["cores"] == original["cores"],
                   f"native replay request or protocol changed: {key}")
        exe = Path(job["cmd"][0])
        demand(job["kind"] == "cxx" and exe.parent == build and exe.name in manifest["binaries"],
               f"unexpected native replay executable: {exe}")
    expected = set(baseline)
    for key, job in final_jobs.items():
        meta = job["meta"]
        if meta["config"] != "blocking-64M" or meta["rep"] != 1 or meta["mode"] == "none":
            continue
        path = replay / "runs" / key / "job.json"
        if path.exists():
            receipt = read_json(path)
            if receipt["status"] == "ok":
                for config in larger_pools(receipt["maxrss_kib"]):
                    expected.update(f"cxx/{meta['case']}/{config}/r{rep}" for rep in (1, 2, 3))
    return {"missing": sorted(expected - set(final_jobs)),
            "extra": sorted(set(final_jobs) - expected), "binaries": manifest["binaries"]}


def audit_inputs(groups):
    evidence = {}
    for group in groups.values():
        source = group["input"]
        path = Path(source["path"])
        measured = digest(path)
        demand(measured == source["sha256"] and path.stat().st_size == source["bytes"],
               f"campaign input changed: {path}")
        evidence[str(path.relative_to(plan.ROOT))] = {"sha256": measured, "bytes": source["bytes"]}
    return evidence


def audit_verification(historical, groups):
    result = []
    for shape in ("window", "long"):
        cases = {case for case, group in groups.items() if group["mode"] != "none"
                 and (shape == "window" or not any(word in case for word in ("TwoComb", "length4_filter")))}
        original = historical / "runs/verify" / shape / "out/summary.json"
        final_base = historical / "verify-fivm2" / shape / "summary.json"
        final_cyclic = historical / "verify-fivm3" / shape / "summary.json"
        old, base, cyclic = [verify_summary(path) for path in (original, final_base, final_cyclic)]
        demand(set(old) == set(base) == cases and set(cyclic) == {case for case in cases if "dumbbell" in case},
               f"incomplete {shape} row verification")
        for build, path, proofs in (("campaign", original, old), ("bin-fivm2", final_base, base),
                                    ("bin-fivm3", final_cyclic, cyclic)):
            for case, proof in proofs.items():
                result.append({"build": build, "shape": shape, **proof,
                               "source": str(path.relative_to(plan.ROOT))})
    for harness in ("routed", "snb", "aggregate"):
        name = f"paper_native_{harness}"
        demand(digest(historical / "bin-fivm2" / name) == digest(historical / "bin-fivm3" / name),
               f"cannot reuse final row verification for {name}")
    return result


def write_csv(path, rows):
    if not rows:
        return
    fields = list(dict.fromkeys(key for row in rows for key in row))
    with path.open("w", newline="") as destination:
        writer = csv.DictWriter(destination, fieldnames=fields, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


METRICS = ("wall_s", "cpu_s", "rss_kib", "accumulate_s", "loop_s", "apply_s",
           "output_s", "gc_collections", "physical_inputs", "relation_updates", "snapshot_rows", "delta_rows")


def summaries(samples, groups):
    arms = defaultdict(list)
    for row in samples:
        key = tuple(row[column] for column in ("case", "cohort", "system", "configuration"))
        arms[key].append(row)
    overview, detailed = [], []
    for case, group in groups.items():
        row = {"case": case, "mode": group["mode"]}
        for cohort, system, config, column in [
            ("campaign", "cxx", "blocking-64M", "campaign_cxx"),
            ("final-cxx", "cxx", "blocking-64M", "final_cxx"),
            *(("final-cxx", "cxx", config, f"final_cxx_{config}") for config in CXX_CONFIGS[1:]),
            ("campaign", "fivm", "patched-native", "campaign_fivm"),
            ("archived-p1", "flink", "p1", "archived_flink_p1"),
            *(("campaign", "flink", f"p{p}", f"campaign_flink_p{p}") for p in (1, 4, 16)),
        ]:
            selected = arms[case, cohort, system, config]
            row[f"{column}_n"] = len(selected)
            for metric in ("wall_s", "rss_kib", "accumulate_s"):
                values = [sample[metric] for sample in selected if sample.get(metric) is not None]
                row[f"{column}_{metric}"] = statistics.median(values) if values else None
        overview.append(row)
    for (case, cohort, system, config), chosen in sorted(arms.items()):
        row = {"case": case, "cohort": cohort, "system": system, "configuration": config, "n": len(chosen)}
        for metric in METRICS:
            values = [sample[metric] for sample in chosen if sample.get(metric) is not None]
            if values:
                row[metric] = statistics.median(values)
        detailed.append(row)
    return overview, detailed


def gather_followups(historical):
    rows = []
    for stem in ("ab", "ab-fivm2", "ab-fivm3"):
        path = historical / f"{stem}.log"
        for line in path.read_text().splitlines():
            if line.startswith("{"):
                row = json.loads(line)
                demand(row["status"] == 0, f"failed A/B run in {path}")
                row["snapshot_rows"], row["delta_rows"] = row.pop("rows")
                raw = historical / stem / row["build"] / row["case"] / f"r{row['rep']}"
                wall, rss = (raw / "time.txt").read_text().split()
                report = read_json(raw / "stdout")
                demand(float(wall) == row["wall"] and int(rss) // 1024 == row["rss_mib"]
                       and report["snapshot_rows"] == row["snapshot_rows"]
                       and report["delta_rows"] == row["delta_rows"], f"A/B receipt mismatch: {raw}")
                rows.append({"experiment": stem, **row, "source": str(raw.relative_to(plan.ROOT))})
    for stem in ("fivm2-idle", "fivm3-idle"):
        path = historical / stem / "results.json"
        for row in read_json(path):
            demand(row["status"] == 0, f"failed focused run in {path}")
            row["snapshot_rows"] = row.pop("rows")
            raw = historical / stem / row["system"] / row["query"] / row["mode"] / f"r{row['rep']}"
            wall, user, system, rss = (raw / "time.txt").read_text().split()
            report = read_json(raw / "stdout")
            demand(float(wall) == row["wall"] and int(rss) // 1024 == row["rss_mib"]
                   and abs(float(user) + float(system) - row["cpu"]) < 1e-6
                   and report["snapshot_rows"] == row["snapshot_rows"]
                   and report.get("delta_rows") == row["delta_rows"], f"focused receipt mismatch: {raw}")
            rows.append({"experiment": stem, **row, "source": str(raw.relative_to(plan.ROOT))})
    return rows


def fivm_fixtures(historical, groups):
    directory = historical.parent / "fivm-crown/row-checks"
    queries = {case.removeprefix("runtime-").removesuffix("-full")
               for case, group in groups.items() if case.startswith("runtime-") and group["mode"] == "full"}
    paths = sorted(directory.glob("*/summary.json"))
    demand(queries <= {path.parent.name for path in paths}, "missing F-IVM row checks")
    rows = []
    for path in paths:
        report = read_json(path)
        control = path.parent.name == "negative-control-stock-ring"
        failures = sum(not row["ok"] for row in report["fixtures"])
        demand(report["query"] in queries and bool(failures) == control and report["ok"] != control,
               f"unexpected F-IVM fixture result: {path}")
        for fixture in report["fixtures"]:
            rows.append({"query": report["query"], "cohort": path.parent.name,
                         "negative_control": control, **fixture,
                         "source": str(path.relative_to(plan.ROOT))})
    return rows


def gather_surveys(directory, history_signatures, output):
    """Keep exploratory runs, including timeouts, outside the timing cohorts."""
    rows = []
    for path in sorted(directory.glob("runs-*/*/result.json")):
        result = read_json(path)
        case = path.parent.name
        status = "timeout" if result["timed_out"] else ("ok" if result["status"] == 0 else "failed")
        rows.append({"survey": path.parent.parent.name, **result, "outcome": status,
                     "case_completed_in_campaign": case in history_signatures,
                     "source": str(path)})
    write_csv(output / "historical-surveys.csv", rows)
    return dict(Counter(row["outcome"] for row in rows))


def write_wall_report(path, overview, audit):
    columns = ("campaign_cxx", "final_cxx", "campaign_fivm",
               "archived_flink_p1", "campaign_flink_p4", "campaign_flink_p16")
    labels = ("CROWN old", "CROWN final", "F-IVM", "Flink p1", "Flink p4", "Flink p16")
    names = ("Case", *labels)
    widths = (max(len(row["case"]) for row in overview), *(12 for _ in labels))

    def line(cells):
        return f"{cells[0]:<{widths[0]}}" + "".join(
            f"  {cell:>{width}}" for cell, width in zip(cells[1:], widths[1:]))

    def value(row, column):
        wall = row[f"{column}_wall_s"]
        return f"{wall:.2f}" if wall is not None else "-"

    accepted = audit["final_cxx"]["cxx"]["accepted"]
    unfinished = audit["final_cxx"]["cxx"]["unfinished"]
    invalid = audit["final_cxx"]["cxx"]["invalid"]
    lines = [
        "CROWN, Flink and F-IVM comparison",
        "Median end-to-end process wall seconds",
        "",
        f"Final C++ replay: {accepted} accepted, {unfinished} unfinished, {invalid} invalid",
        "CROWN columns use blocking GC and the 64 MiB pool. The systems were",
        "measured in the distinct cohorts documented in record.txt.",
        "F-IVM entries are present for full snapshots and maintenance only.",
        "Sample counts, RSS, CPU time and Flink internal timers are in the CSVs.",
        "",
        line(names),
        line(tuple("-" * len(name) for name in names)),
    ]
    lines.extend(line((row["case"], *(value(row, column) for column in columns))) for row in overview)
    path.write_text("\n".join(lines) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("historical", type=Path)
    parser.add_argument("replay", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--verify-inputs", action="store_true", help="re-hash the native campaign inputs")
    parser.add_argument("--allow-unfinished", action="store_true", help="produce an interim report while jobs run")
    parser.add_argument("--surveys-dir", type=Path, default=plan.PREVIOUS.parent,
                        help="optional Claude scratch directory containing earlier runs")
    args = parser.parse_args()
    historical, replay, output = (path.resolve() for path in (args.historical, args.replay, args.output))
    output.mkdir(parents=True, exist_ok=True)
    groups = {row["case_id"].removesuffix("-reference_ordered_v1"): row for row in plan.paper.cases()}
    groups.update({key.removesuffix("-full") + "-none": dict(row, mode="none")
                   for key, row in groups.items() if key.startswith("runtime-") and row["mode"] == "full"})
    jobs, final_jobs = load_jobs(historical), load_jobs(replay)
    samples, issues, history_signatures = [], [], {}
    flink_points = {row["point_id"]: row for row in read_json(plan.MANIFEST)["points"]}
    matrix = audit_matrix(historical, jobs, groups)
    final_matrix = audit_replay_matrix(replay, jobs, final_jobs)
    verify = audit_verification(historical, groups)
    counts = track_campaign(historical, "campaign", jobs, groups, flink_points,
                            history_signatures, samples, issues)
    final_counts = track_campaign(replay, "final-cxx", final_jobs, groups, flink_points,
                                  history_signatures, samples, issues)
    archive_flink(groups, flink_points, samples, issues)
    overview, detailed = summaries(samples, groups)
    followups = gather_followups(historical)
    fixtures = fivm_fixtures(historical, groups)
    write_csv(output / "comparison.csv", overview)
    write_csv(output / "medians.csv", detailed)
    write_csv(output / "samples.csv", samples)
    write_csv(output / "row-verification.csv", verify)
    write_csv(output / "followups.csv", followups)
    write_csv(output / "fivm-fixtures.csv", fixtures)
    complete = not any(group["unfinished"] or group["invalid"]
                       for group in (*counts.values(), *final_counts.values()))
    audit = {"complete": complete and not issues and not any(
                 cohort["missing"] or cohort["extra"] for cohort in (matrix, final_matrix)),
             "historical": str(historical), "replay": str(replay), "historical_matrix": matrix,
             "final_cxx_matrix": final_matrix,
             "campaign": counts, "final_cxx": final_counts, "verification_rows": len(verify),
             "archived_flink_p1_samples": sum(row["cohort"] == "archived-p1" for row in samples),
             "followup_samples": len(followups), "issues": issues,
             "fivm_fixtures": len(fixtures),
             "historical_surveys": gather_surveys(args.surveys_dir, history_signatures, output),
             "native_inputs": audit_inputs(groups) if args.verify_inputs else None}
    write_wall_report(output / "report.txt", overview, audit)
    (output / "audit.json").write_text(json.dumps(audit, indent=2) + "\n")
    print(json.dumps({**audit, "issues": len(issues)}, indent=2))
    if not audit["complete"] and (issues or matrix["missing"] or matrix["extra"] or not args.allow_unfinished):
        raise SystemExit(1)


if __name__ == "__main__":
    main()
