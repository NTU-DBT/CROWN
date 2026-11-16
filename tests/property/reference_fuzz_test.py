#!/usr/bin/env python3
"""Bounded seeded semantic comparison and shrinker fault-injection test."""

from __future__ import annotations

import argparse
import json
import sys
from collections import Counter
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))

from tools import reference_fuzz as fuzz  # noqa: E402


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("executable", help="path to the crown CLI executable")
    parser.add_argument("--seeds", type=int, default=12)
    parser.add_argument("--updates", type=int, default=12)
    parser.add_argument("--seed-start", type=int, default=0)
    args = parser.parse_args()
    if args.seeds <= 0 or args.updates < 0:
        raise fuzz.FuzzError("--seeds must be positive and --updates nonnegative")

    shape_counts: Counter[str] = Counter()
    scalar_types: set[str] = set()
    compared = 0
    for seed in range(args.seed_start, args.seed_start + args.seeds):
        document = fuzz.generate_case(seed, args.updates)
        shape_counts[fuzz.SHAPES[seed % len(fuzz.SHAPES)]] += 1
        scalar_types.update(
            item["type"] for item in document["query"]["variables"]
        )
        try:
            fuzz.validate_generated_document(document)
            fuzz.compare_case(args.executable, document)
        except fuzz.Mismatch as mismatch:
            packet = fuzz.make_failure_packet(seed, document, mismatch)

            def reproduces(candidate: dict[str, Any]) -> bool:
                try:
                    fuzz.validate_with_cli(args.executable, candidate)
                    actual = fuzz.cli_reference(args.executable, candidate)
                    expected, _ = fuzz.sqlite_reference(candidate)
                except fuzz.FuzzError:
                    return False
                return fuzz.first_difference(actual, expected) is not None

            minimized = fuzz.shrink_trace(document, reproduces)
            minimized_expected, minimized_plan = fuzz.sqlite_reference(minimized)
            minimized_actual = fuzz.cli_reference(args.executable, minimized)
            packet["minimized"] = {
                "document": minimized,
                "normalized_cq": minimized["query"],
                "trace": {
                    "initial": minimized.get("initial", []),
                    "updates": minimized.get("updates", []),
                },
                "sql": minimized_plan.statement,
                "sql_parameters": list(minimized_plan.parameters),
                "actual": minimized_actual,
                "expected": minimized_expected,
            }
            print(json.dumps(packet, indent=2, ensure_ascii=False), file=sys.stderr)
            return 1
        except fuzz.FuzzError as error:
            packet = fuzz.make_error_packet(seed, document, error)
            print(json.dumps(packet, indent=2, ensure_ascii=False), file=sys.stderr)
            return 1
        compared += 1

    if args.seeds >= len(fuzz.SHAPES):
        missing_shapes = set(fuzz.SHAPES) - set(shape_counts)
        if missing_shapes:
            raise fuzz.FuzzError(f"bounded seeds missed query shapes: {sorted(missing_shapes)}")
    if not {"int64", "string", "bool"}.issubset(scalar_types) and args.seeds >= 12:
        raise fuzz.FuzzError(
            f"bounded seeds missed scalar types: {sorted(scalar_types)}"
        )

    invalid_document = fuzz.generate_case(args.seed_start, max(args.updates, 1))
    try:
        fuzz.validate_generated_document(invalid_document)
        invalid_rejected = fuzz.check_invalid_variants(args.executable, invalid_document)
    except fuzz.FuzzError as error:
        packet = fuzz.make_error_packet(args.seed_start, invalid_document, error)
        print(json.dumps(packet, indent=2, ensure_ascii=False), file=sys.stderr)
        return 1

    fault_seed = 0
    fault_document = fuzz.generate_case(fault_seed, 12)
    try:
        fault_packet = fuzz.shrinker_fault_case(args.executable, fault_seed, 12)
    except fuzz.FuzzError as error:
        packet = fuzz.make_error_packet(fault_seed, fault_document, error)
        print(json.dumps(packet, indent=2, ensure_ascii=False), file=sys.stderr)
        return 1
    if fault_packet["update_count"] != 1:
        raise fuzz.FuzzError("shrinker fault packet must contain exactly one update")
    required_packet_fields = {
        "seed", "normalized_cq", "sql", "sql_parameters", "trace", "document",
    }
    if not required_packet_fields.issubset(fault_packet):
        raise fuzz.FuzzError("shrinker packet omitted reproducible failure context")
    if not fuzz.json_equal(fault_packet["normalized_cq"], fault_packet["document"]["query"]):
        raise fuzz.FuzzError("shrinker packet CQ differs from the minimized document")
    if fault_packet["initial_row_count"] != 0:
        raise fuzz.FuzzError("singleton fault shrink retained unnecessary initial rows")
    if fault_packet["trace"]["updates"][0]["op"] != "insert":
        raise fuzz.FuzzError("singleton fault shrink did not retain its relevant insertion")

    print(
        f"data-shape generation: {args.seeds} documents passed local validation "
        f"({', '.join(f'{shape}={shape_counts[shape]}' for shape in fuzz.SHAPES)})"
    )
    print(
        f"semantic comparison: {compared} seeds x {args.updates} updates matched "
        f"the independent SQLite SELECT DISTINCT oracle"
    )
    print(
        f"scalar types covered: {', '.join(sorted(scalar_types))}; "
        f"invalid variants rejected: {invalid_rejected}"
    )
    print(
        "test-wrapper duplicate-delta fault detected and shrunk to "
        f"{fault_packet['update_count']} event(s), "
        f"{fault_packet['initial_row_count']} initial row(s)"
    )
    print(
        "shrinker failure packet fields: seed, normalized_cq, SQL, SQL parameters, "
        "minimal trace, and full document"
    )
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except fuzz.FuzzError as error:
        print(f"reference fuzz failure: {error}", file=sys.stderr)
        raise SystemExit(1)
