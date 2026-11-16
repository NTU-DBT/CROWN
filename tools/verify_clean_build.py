#!/usr/bin/env python3
"""Build and test a clean copy of the CROWN source tree."""

from __future__ import annotations

import argparse
import json
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path
from typing import TextIO


SOURCE_FILES = (".gitignore", "CMakeLists.txt", "CMakePresets.json",
                "dependencies.lock.json", "README.md", "Refactor.md")
SOURCE_DIRECTORIES = (
    "include",
    "src",
    "apps",
    "tests",
    "tools",
    "schemas",
    "third_party",
    "cmake",
    "examples",
    "benchmarks",
    "docs",
)
IGNORED_NAMES = {"__pycache__", ".git", "build"}
COMMAND_TIMEOUT_SECONDS = 900


class VerificationError(RuntimeError):
    pass


def positive_int(value: str) -> int:
    try:
        number = int(value)
    except ValueError as error:
        raise argparse.ArgumentTypeError("must be a positive integer") from error
    if number <= 0:
        raise argparse.ArgumentTypeError("must be a positive integer")
    return number


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--configuration",
        choices=("Debug", "Release"),
        default="Release",
        help="CMake build configuration (default: Release)",
    )
    parser.add_argument(
        "--parallel",
        type=positive_int,
        default=2,
        metavar="N",
        help="maximum parallel build jobs (default: 2)",
    )
    parser.add_argument(
        "--log",
        type=Path,
        default=Path("build/verification/clean-source.log"),
        help="command and output log, relative to the repository root by default",
    )
    return parser.parse_args(argv)


def ignore_snapshot_entries(_directory: str, names: list[str]) -> set[str]:
    return {
        name
        for name in names
        if name in IGNORED_NAMES or name.endswith(".pyc")
    }


# Copy only the explicit source inventory and legacy files, excluding build/cache basenames.
def copy_snapshot(repository: Path, source: Path, log: TextIO) -> None:
    def copy_file(name: str) -> None:
        relative = Path(name)
        if relative.is_absolute() or ".." in relative.parts:
            raise VerificationError(f"source manifest path must be repository-relative: {name}")
        original = repository / name
        if not original.is_file():
            raise VerificationError(f"required source file is missing: {original}")
        (source / name).parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(original, source / name)
        log.write(f"copied {name}\n")

    for name in SOURCE_FILES:
        copy_file(name)

    for name in SOURCE_DIRECTORIES:
        original = repository / name
        if not original.is_dir():
            raise VerificationError(f"required source directory is missing: {original}")
        shutil.copytree(
            original,
            source / name,
            ignore=ignore_snapshot_entries,
        )
        log.write(f"copied {name}/ (excluding caches, builds and VCS)\n")

    # B02 checks these exact pinned baseline inputs, not whole legacy projects.
    legacy = json.loads((source / "benchmarks/legacy/manifest.json").read_text())
    for name in legacy["source_sha256_local"]:
        copy_file(name)


def output_text(value: str | bytes | None) -> str:
    if value is None:
        return ""
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return value


def run_command(command: list[str], log: TextIO) -> str:
    log.write(f"\n$ {shlex.join(command)}\n")
    log.flush()
    started = time.monotonic()
    try:
        completed = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace",
            check=True,
            timeout=COMMAND_TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as error:
        output = output_text(error.stdout)
        log.write(output)
        if output and not output.endswith("\n"):
            log.write("\n")
        log.write(f"command timed out after {COMMAND_TIMEOUT_SECONDS} seconds\n")
        log.flush()
        raise VerificationError(
            f"command timed out after {COMMAND_TIMEOUT_SECONDS} seconds: {shlex.join(command)}"
        ) from error
    except subprocess.CalledProcessError as error:
        output = output_text(error.stdout)
        log.write(output)
        if output and not output.endswith("\n"):
            log.write("\n")
        log.write(f"command exited with status {error.returncode}\n")
        log.flush()
        raise VerificationError(
            f"command failed with status {error.returncode}: {shlex.join(command)}"
        ) from error

    output = output_text(completed.stdout)
    log.write(output)
    if output and not output.endswith("\n"):
        log.write("\n")
    log.write(f"command completed in {time.monotonic() - started:.2f}s\n")
    log.flush()
    return output


def test_count(ctest_output: str) -> int | None:
    match = re.search(r"\btests failed out of (\d+)\b", ctest_output)
    return int(match.group(1)) if match else None


def main(argv: list[str] | None = None) -> int:
    arguments = parse_args(argv)
    repository = Path(__file__).resolve().parents[1]
    log_path = arguments.log.expanduser()
    if not log_path.is_absolute():
        log_path = repository / log_path
    log_path.parent.mkdir(parents=True, exist_ok=True)

    temporary_root = Path(tempfile.mkdtemp(prefix="crown-clean-source-"))
    source = temporary_root / "source"
    build = source / "build"
    source.mkdir()
    started = time.monotonic()
    failure: Exception | None = None
    completed_tests: int | None = None

    try:
        with log_path.open("w", encoding="utf-8") as log:
            log.write("CROWN clean-source verification\n")
            log.write(f"repository: {repository}\n")
            log.write(f"temporary source: {source}\n")
            log.write(f"configuration: {arguments.configuration}\n")
            log.write(f"parallel jobs: {arguments.parallel}\n")
            log.write(f"command timeout: {COMMAND_TIMEOUT_SECONDS}s\n")
            copy_snapshot(repository, source, log)

            run_command(
                [
                    "cmake",
                    "-S",
                    str(source),
                    "-B",
                    str(build),
                    f"-DCMAKE_BUILD_TYPE={arguments.configuration}",
                ],
                log,
            )
            run_command(
                ["cmake", "--build", str(build), "--parallel", str(arguments.parallel)],
                log,
            )
            ctest_output = run_command(
                ["ctest", "--test-dir", str(build), "--output-on-failure"],
                log,
            )
            completed_tests = test_count(ctest_output)
            log.write(f"test count: {completed_tests if completed_tests is not None else 'not reported'}\n")
    except Exception as error:
        failure = error
    finally:
        shutil.rmtree(temporary_root, ignore_errors=True)

    elapsed = time.monotonic() - started
    with log_path.open("a", encoding="utf-8") as log:
        if failure is None:
            log.write(f"result: PASS in {elapsed:.2f}s\n")
        else:
            log.write(f"result: FAIL in {elapsed:.2f}s: {failure}\n")
        log.write(f"temporary source/build removed: {not temporary_root.exists()}\n")

    if failure is not None:
        print(f"clean-source verification failed: {failure}", file=sys.stderr)
        print(f"log: {log_path}", file=sys.stderr)
        return 1

    count = f"; {completed_tests} tests" if completed_tests is not None else ""
    print(f"clean-source verification passed in {elapsed:.2f}s{count}")
    print(f"log: {log_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
