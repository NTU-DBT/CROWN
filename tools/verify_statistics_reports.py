#!/usr/bin/env python3
"""Produce and independently validate one native statistics report corpus."""
import argparse
import copy
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

import jsonschema


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--executable", type=Path, required=True)
    parser.add_argument("--repo-root", type=Path, required=True)
    parser.add_argument("--variant", choices=("production", "testing"), required=True)
    args = parser.parse_args()
    root = args.repo_root.resolve()
    executable = args.executable.resolve()
    baseline = root / "tests/statistics/legacy-v2"
    expected_names = {"legacy-runtime.json", "legacy-session.json"}
    seen = set()
    for line in (baseline / "SHA256SUMS").read_text(encoding="ascii").splitlines():
        expected, name = line.split("  ", 1)
        if name not in expected_names or name in seen:
            raise RuntimeError("unexpected or duplicate legacy baseline checksum entry")
        seen.add(name)
        if hashlib.sha256((baseline / name).read_bytes()).hexdigest() != expected:
            raise RuntimeError("legacy baseline checksum mismatch: " + name)
    if seen != expected_names:
        raise RuntimeError("incomplete legacy baseline checksum manifest")

    corpus = Path(tempfile.mkdtemp(prefix="crown-statistics-" + args.variant + "-"))
    schema_path = root / "schemas/statistics-explain-v3.schema.json"
    try:
        print("statistics stage=producer variant=" + args.variant, flush=True)
        subprocess.run([str(executable), str(corpus)], check=True)
        command = [sys.executable, str(root / "tools/support/check_statistics_reports.py"),
                   "--schema", str(schema_path), "--fixtures", str(corpus),
                   "--legacy-baseline", str(baseline),
                   "--legacy-schema", str(root / "schemas/explain-report-v2.schema.json")]
        if args.variant == "testing":
            command.append("--testing")
        print("statistics stage=schema_semantics_legacy_mutations variant=" + args.variant,
              flush=True)
        subprocess.run(command, check=True)

        # Keep repository acceptance fields out of native runtime capability facts.
        validator = jsonschema.Draft202012Validator(
            json.loads(schema_path.read_text(encoding="utf-8")))
        original = json.loads((corpus / "off-state.json").read_text(encoding="utf-8"))
        if "c01_project_gate" in original["capabilities"]:
            raise RuntimeError("runtime report contains repository task acceptance")
        changed = copy.deepcopy(original)
        changed["capabilities"]["c01_project_gate"] = "open"
        try:
            validator.validate(changed)
        except jsonschema.ValidationError:
            pass
        else:
            raise RuntimeError("closed native schema accepted the removed project gate")
        print(json.dumps({"status": "pass", "variant": args.variant,
                          "publication_gate_mutations_rejected": 1}, sort_keys=True))
    except BaseException:
        print("Statistics acceptance artifacts retained at " + str(corpus), file=sys.stderr)
        raise
    else:
        shutil.rmtree(corpus)


if __name__ == "__main__":
    main()
