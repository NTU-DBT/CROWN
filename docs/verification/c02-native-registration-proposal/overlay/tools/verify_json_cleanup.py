#!/usr/bin/env python3
"""Compare isolated upstream/patched JSON serialization and the failure control."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import resource
import shutil
import signal
import subprocess
import sys
import tempfile


class VerificationError(RuntimeError):
    pass


def run(executable: Path, mode: str, label: str, output: Path) -> int:
    command = [str(executable), mode]
    status: dict[str, object] = {"command": command, "timeout_seconds": 120}
    try:
        with (output / f"{label}.stdout").open("wb") as stdout, (
            output / f"{label}.stderr"
        ).open("wb") as stderr:
            result = subprocess.run(
                command, stdin=subprocess.DEVNULL, stdout=stdout, stderr=stderr,
                timeout=120, check=False,
            )
        status["returncode"] = result.returncode
        return result.returncode
    except subprocess.TimeoutExpired as error:
        status["error"] = "timeout"
        raise VerificationError(f"{label} exceeded 120 seconds") from error
    except OSError as error:
        status["error"] = str(error)
        raise VerificationError(f"{label} could not start: {error}") from error
    finally:
        (output / f"{label}.status.json").write_text(
            json.dumps(status, indent=2) + "\n", encoding="utf-8"
        )


def verify(original: Path, patched: Path, output: Path) -> None:
    for label, executable in (("original-serialize", original), ("patched-serialize", patched)):
        code = run(executable, "--serialize", label, output)
        if code != 0 or (output / f"{label}.stderr").stat().st_size != 0:
            raise VerificationError(f"{label} failed or emitted diagnostics (exit {code})")
    before = (output / "original-serialize.stdout").read_bytes()
    after = (output / "patched-serialize.stdout").read_bytes()
    if not before or before != after:
        raise VerificationError("upstream/patched sizeof and serialized outputs differ or are empty")

    # This control is intentionally a separate process. Its upstream destructor
    # is noexcept and cannot recover from the first persistent cleanup failure.
    # Require the observed failure kind, never accept an arbitrary nonzero exit.
    code = run(original, "--cleanup", "original-cleanup", output)
    diagnostics = (output / "original-cleanup.stderr").read_bytes()
    if any(marker in diagnostics for marker in (
        b"ERROR: AddressSanitizer", b"LeakSanitizer", b"runtime error:"
    )):
        raise VerificationError("upstream control emitted an unrelated sanitizer diagnostic")
    if code != -signal.SIGABRT or b"bad_alloc" not in diagnostics:
        raise VerificationError(
            f"upstream cleanup did not reproduce SIGABRT with bad_alloc (exit {code})"
        )
    print(
        f"JSON compatibility: {len(before)} identical bytes, "
        f"SHA-256 {hashlib.sha256(before).hexdigest()}; upstream bad_alloc abort reproduced"
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", required=True, type=Path)
    parser.add_argument("--patched", required=True, type=Path)
    args = parser.parse_args()
    original, patched = args.original.resolve(), args.patched.resolve()
    if not original.is_file() or not patched.is_file() or original == patched:
        parser.error("two distinct existing executable paths are required")
    output = Path(tempfile.mkdtemp(prefix="crown-json-cleanup-"))
    try:
        # CROWN's native build supports Linux. Disable core files for the
        # expected abort in this wrapper and its child processes only.
        resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
        verify(original, patched, output)
    except (VerificationError, OSError, ValueError) as error:
        print(f"JSON compatibility failed: {error}\nEvidence retained at {output}", file=sys.stderr)
        return 1
    try:
        shutil.rmtree(output)
    except OSError as error:
        print(f"JSON compatibility cleanup failed: {error}\nDirectory: {output}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
