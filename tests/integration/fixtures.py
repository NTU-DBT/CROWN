#!/usr/bin/env python3
"""Run hand-calculated direct-CQ oracle fixtures and canonicalization checks."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


def load_json(path: Path) -> Any:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise RuntimeError(f"{path}: cannot read JSON: {error}") from error


def invoke(executable: str, command: str, document: Path, label: str) -> Any:
    result = subprocess.run(
        [executable, command, str(document)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
    )
    if result.returncode != 0:
        raise RuntimeError(
            f"{label}: {command} exited with status {result.returncode}\n"
            f"stdout:\n{result.stdout}\nstderr:\n{result.stderr}"
        )
    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(
            f"{label}: {command} did not emit valid JSON: {error}\n"
            f"stdout:\n{result.stdout}\nstderr:\n{result.stderr}"
        ) from error


def compare(actual: Any, expected: Any, label: str) -> None:
    actual_text = json.dumps(actual, indent=2, ensure_ascii=False, sort_keys=True)
    expected_text = json.dumps(expected, indent=2, ensure_ascii=False, sort_keys=True)
    # Python equality equates True with 1. Canonical JSON retains value types.
    if actual_text == expected_text:
        return
    raise RuntimeError(
        f"{label}: JSON mismatch\n"
        f"expected:\n{expected_text}\n"
        f"actual:\n{actual_text}"
    )


def main() -> int:
    if len(sys.argv) != 3:
        raise RuntimeError("usage: fixtures.py EXECUTABLE FIXTURE_DIRECTORY")

    executable = sys.argv[1]
    fixture_dir = Path(sys.argv[2])
    inputs = sorted(
        path
        for path in fixture_dir.glob("*.json")
        if not path.name.endswith(".expected.json")
    )
    if not inputs:
        raise RuntimeError(f"{fixture_dir}: no input .json fixtures found")

    passed = 0
    with tempfile.TemporaryDirectory(prefix="crown-fixtures-") as temporary:
        temporary_dir = Path(temporary)
        for document in inputs:
            expected_path = document.with_name(
                f"{document.stem}.expected.json"
            )
            if not expected_path.is_file():
                raise RuntimeError(f"{document}: missing {expected_path.name}")

            expected = load_json(expected_path)
            compare(
                invoke(executable, "oracle", document, document.name),
                expected,
                f"{document.name} oracle",
            )

            canonical = invoke(
                executable, "canonicalize", document, document.name
            )
            canonical_path = temporary_dir / document.name
            canonical_path.write_text(
                json.dumps(canonical, indent=2, ensure_ascii=False) + "\n",
                encoding="utf-8",
            )

            # A canonical document must be a fixed point and preserve the
            # hand-calculated oracle result when parsed again.
            compare(
                invoke(
                    executable,
                    "canonicalize",
                    canonical_path,
                    f"{document.name} canonical roundtrip",
                ),
                canonical,
                f"{document.name} canonical roundtrip",
            )
            compare(
                invoke(
                    executable,
                    "oracle",
                    canonical_path,
                    f"{document.name} canonical roundtrip",
                ),
                expected,
                f"{document.name} canonical roundtrip oracle",
            )
            passed += 1

    print(f"{passed} direct-CQ fixtures passed")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RuntimeError as error:
        print(f"fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
