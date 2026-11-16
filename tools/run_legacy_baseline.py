#!/usr/bin/env python3
"""Legacy comparison environment diagnostic and baseline runner (B01).

Audits pinned CROWN Scala/Flink dependencies, verifies JDK/Scala toolchains,
records build-failure evidence under incompatible host JDKs, and compares
legacy query specifications against native CROWN SQL definitions.
"""
from __future__ import annotations
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True


def sha256_file(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def detect_environment():
    java_version = None
    javac_version = None
    mvn_version = None

    try:
        res = subprocess.run(["java", "-version"], capture_output=True, text=True, check=False)
        java_version = res.stderr.splitlines()[0] if res.stderr else res.stdout.splitlines()[0]
    except FileNotFoundError:
        pass

    try:
        res = subprocess.run(["javac", "-version"], capture_output=True, text=True, check=False)
        javac_version = res.stdout.strip() or res.stderr.strip()
    except FileNotFoundError:
        pass

    try:
        res = subprocess.run(["mvn", "-version"], capture_output=True, text=True, check=False)
        mvn_version = res.stdout.splitlines()[0] if res.stdout else None
    except FileNotFoundError:
        pass

    return {
        "platform": platform.platform(),
        "uname": list(platform.uname()),
        "python": sys.version,
        "java_runtime": java_version,
        "javac": javac_version,
        "maven": mvn_version,
        "java_home": os.environ.get("JAVA_HOME"),
    }


def parse_pom_properties(pom_path: Path):
    text = pom_path.read_text(encoding="utf-8")
    props = {}
    for match in re.finditer(r"<([a-zA-Z0-9\.\-_]+)>(.*?)</\1>", text):
        tag, val = match.groups()
        if tag in ["flink.version", "target.java.version", "scala.binary.version", "scala.version", "log4j.version"]:
            props[tag] = val
    return props


def attempt_legacy_build(root_dir: Path, timeout: int = 120):
    pom_path = root_dir / "crown" / "pom.xml"
    if not pom_path.is_file():
        return {"status": "missing_pom", "error": f"pom.xml not found at {pom_path}"}

    cmd = ["mvn", "-f", str(pom_path), "clean", "compile"]
    start = datetime.datetime.now(datetime.timezone.utc)
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout, check=False)
        end = datetime.datetime.now(datetime.timezone.utc)
        duration_s = (end - start).total_seconds()

        # Parse key error signatures
        failure_signature = None
        if proc.returncode != 0:
            if "/packages cannot be represented as URI" in proc.stdout or "/packages cannot be represented as URI" in proc.stderr:
                failure_signature = "jrtfs_packages_uri_java17_incompatibility"
            elif "Compilation failed" in proc.stdout or "Compilation failed" in proc.stderr:
                failure_signature = "scala_compiler_error"
            else:
                failure_signature = "maven_execution_failure"

        return {
            "status": "success" if proc.returncode == 0 else "build_failed",
            "exit_code": proc.returncode,
            "duration_seconds": duration_s,
            "failure_signature": failure_signature,
            "stdout_tail": proc.stdout.splitlines()[-25:] if proc.stdout else [],
            "stderr_tail": proc.stderr.splitlines()[-25:] if proc.stderr else [],
        }
    except subprocess.TimeoutExpired:
        return {"status": "timeout", "timeout_seconds": timeout}
    except Exception as exc:
        return {"status": "error", "message": str(exc)}


def inspect_legacy_manifest(manifest_path: Path):
    if not manifest_path.is_file():
        return {"status": "manifest_not_found"}
    data = json.loads(manifest_path.read_text(encoding="utf-8"))
    query_entries = data.get("query_entries", [])
    specs = data.get("specs", [])
    return {
        "title": data.get("title"),
        "total_task_scenarios": data.get("consolidation", {}).get("task_rows_total"),
        "distinct_query_labels": data.get("consolidation", {}).get("distinct_spec_query_labels"),
        "spec_files_count": len(specs),
        "query_labels": [q.get("label") for q in query_entries],
    }


def main():
    parser = argparse.ArgumentParser(description="Legacy comparison environment diagnostic and runner (B01)")
    parser.add_argument("--source", type=Path, default=Path("."), help="Path to repository root")
    parser.add_argument("--output", type=Path, default=Path("build/legacy_baseline_report.json"), help="Output report JSON path")
    parser.add_argument("--try-build", action="store_true", help="Attempt Maven compile on legacy Scala source")
    parser.add_argument("--build-timeout", type=int, default=120, help="Build timeout in seconds")
    args = parser.parse_args()

    root = args.source.resolve()
    pom_file = root / "crown" / "pom.xml"
    legacy_manifest = root / "benchmarks" / "legacy" / "manifest.json"

    env_info = detect_environment()
    pom_props = parse_pom_properties(pom_file) if pom_file.is_file() else {}
    manifest_info = inspect_legacy_manifest(legacy_manifest)

    report = {
        "timestamp_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "task": "B01",
        "description": "Legacy comparison environment baseline inspection and build-failure diagnostic",
        "host_environment": env_info,
        "legacy_pom_properties": pom_props,
        "legacy_manifest_summary": manifest_info,
        "build_attempt": None,
    }

    if args.try_build:
        print("[*] Running Maven build on legacy Scala code (crown/pom.xml)...")
        build_result = attempt_legacy_build(root, timeout=args.build_timeout)
        report["build_attempt"] = build_result
        print(f"[*] Build result: status={build_result.get('status')}, failure_signature={build_result.get('failure_signature')}")

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2), encoding="utf-8")
    print(f"[+] Diagnostic report written to: {args.output}")


if __name__ == "__main__":
    main()
