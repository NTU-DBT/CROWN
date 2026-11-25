#!/usr/bin/env python3
"""Stage the complete native comparison matrix against the final saved C++ build."""

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("historical", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--bin", type=Path, help="replay binaries (default: HISTORICAL/bin-fivm3)")
    args = parser.parse_args()
    prior, output = args.historical.resolve(), args.output.resolve()
    binaries = args.bin.resolve() if args.bin else prior / "bin-fivm3"
    jobs = []
    for line in (prior / "jobs.jsonl").read_text().splitlines():
        job = json.loads(line)
        if job["kind"] != "cxx":
            continue
        job["cmd"][0] = str(binaries / Path(job["cmd"][0]).name)
        receipt = json.loads((prior / "runs" / job["id"] / "job.json").read_text())
        job["est_s"] = receipt.get("time_wall_s", receipt["wall_s"])
        jobs.append(job)
    identity = {}
    for binary in sorted({job["cmd"][0] for job in jobs}):
        with open(binary, "rb") as source:
            identity[Path(binary).name] = hashlib.file_digest(source, "sha256").hexdigest()

    output.mkdir()
    (output / "jobs.jsonl").write_text("".join(json.dumps(job) + "\n" for job in jobs))
    (output / "STOP_WHEN_IDLE").touch()
    manifest = {"source": str(prior), "build": str(binaries), "binaries": identity,
                "initial_job_count": len(jobs),
                "kind_counts": dict(Counter(job["meta"]["config"] for job in jobs)),
                "baseline_total_wall_s": sum(job["est_s"] for job in jobs)}
    (output / "reproduction.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Staged {len(jobs)} C++ measurements in {output}")


if __name__ == "__main__":
    main()
