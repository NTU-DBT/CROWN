#!/usr/bin/env python3
"""Run native observability fixtures and validate a fresh complete corpus."""
import argparse
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

parser = argparse.ArgumentParser()
parser.add_argument("--kind", choices=("query", "cursor", "composed"), required=True)
parser.add_argument("--executable", type=Path, required=True)
parser.add_argument("--repo-root", type=Path, required=True)
args = parser.parse_args()
root = args.repo_root.resolve()
executable = args.executable.resolve()
corpus = Path(tempfile.mkdtemp(prefix="crown-" + args.kind + "-acceptance-"))
checker = root / "tools/support" / ("check_" + args.kind + "_reports.py")
try:
    if args.kind == "cursor":
        output = corpus / "cursor.json"
        with output.open("x", encoding="utf-8") as stream:
            subprocess.run([str(executable)], stdout=stream, check=True)
        command = [sys.executable, str(checker), str(output)]
    else:
        subprocess.run([str(executable), str(corpus), "all"], check=True)
        command = [sys.executable, str(checker), str(corpus), "--require-all"]
        if args.kind == "composed":
            command += ["--repo-root", str(root), "--schema-dir", str(root / "schemas")]
    subprocess.run(command, check=True)
except BaseException:
    print("Acceptance artifacts retained at " + str(corpus), file=sys.stderr)
    raise
else:
    shutil.rmtree(corpus)
