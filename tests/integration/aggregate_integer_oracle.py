#!/usr/bin/env python3
"""Check W04 integer statistics against unbounded Python arithmetic.

The driver reports results after every replacement and forbids heap requests
inside arithmetic/InlineDecimal conversion. This is a primitive gate, not W04
SQL binding, grouping, event or runtime acceptance.
"""
import argparse
from decimal import Decimal, getcontext
import json
import random
import subprocess

MINIMUM = -(1 << 63)
MAXIMUM = (1 << 63) - 1
SCALES = tuple(range(19))


def operation(value, weight=1, erase=False):
    return {"value": value, "weight": weight, "erase": erase}


def fixed_cases():
    for scale in SCALES:
        yield scale, []
        for value in (MINIMUM, MAXIMUM, -1, 0, 1):
            yield scale, [operation(value), operation(value, erase=True)]
            yield scale, [operation(value, MAXIMUM)]
        for total, count in ((1, 2), (-1, 2), (1, 3), (-2, 3),
                             (1, 2 * 10**18), (-1, 2 * 10**18),
                             (1, 2 * 10**18 + 1), (-1, 2 * 10**18 + 1)):
            yield scale, [operation(total), operation(0, count - 1)]
        half = MAXIMUM // 2
        yield scale, [operation(MAXIMUM, half), operation(-MAXIMUM, half),
                      operation(MAXIMUM, half, True), operation(-MAXIMUM, half, True)]
        yield scale, [operation(MAXIMUM, MAXIMUM - 1), operation(MAXIMUM - 1)]
        yield scale, [operation(MINIMUM, MAXIMUM - 1), operation(MINIMUM + 1)]
        for count in ((1 << 53) - 1, 1 << 53, (1 << 53) + 1, MAXIMUM):
            yield scale, [operation(1, count), operation(1, count, True)]


def random_cases(seed, count):
    rng = random.Random(seed)
    for index in range(count):
        remaining = MAXIMUM
        rows = []
        ops = []
        for _ in range(rng.randrange(1, 9)):
            value = rng.choice((MINIMUM, MAXIMUM, -1, 0, 1, rng.randrange(MINIMUM, MAXIMUM + 1)))
            weight = rng.randrange(remaining + 1)
            rows.append((value, weight))
            ops.append(operation(value, weight))
            remaining -= weight
        for value, weight in reversed(rows):
            removed = rng.randrange(weight + 1)
            ops.append(operation(value, removed, True))
            remaining += removed
            added = rng.randrange(remaining + 1)
            ops.append(operation(value, added))
            remaining -= added
        yield SCALES[index % len(SCALES)], ops


def rounded_average(total, count, scale):
    # Divide one exact integer numerator. This deliberately differs from the
    # native quotient/remainder scaling and its two-word representation.
    coefficient, remainder = divmod(abs(total) * 10**scale, count)
    coefficient += 2 * remainder >= count
    if total < 0:
        coefficient = -coefficient
    return Decimal(coefficient).scaleb(-scale)


def check_trace(case, actual):
    assert actual["id"] == case["id"]
    trace = actual["trace"]
    assert len(trace) == len(case["operations"]) + 1
    total = count = 0
    for index, result in enumerate(trace):
        if index:
            op = case["operations"][index - 1]
            sign = -1 if op["erase"] else 1
            total += sign * op["value"] * op["weight"]
            count += sign * op["weight"]
        assert 0 <= count <= MAXIMUM
        fits = MINIMUM <= total <= MAXIMUM
        context = (case["id"], index, case["scale"], total, count, result)
        assert Decimal(result["sum"]) == total, context
        assert result["count"] == count and result["fits_int64"] == fits, context
        assert result["integer"] == (total if fits else None), context
        expected = rounded_average(total, count, case["scale"]) if count else None
        assert (Decimal(result["average"]) if result["average"] is not None else None) == expected, context
        for field in ("sum", "average"):
            value = result[field]
            assert value is None or Decimal(value) != 0 or not value.startswith("-"), context
    return len(trace)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    parser.add_argument("--cases", type=int, default=2048)
    parser.add_argument("--seed", type=int, default=0xA6642026)
    args = parser.parse_args()
    getcontext().prec = 200
    cases = [{"id": i, "scale": scale, "operations": ops}
             for i, (scale, ops) in enumerate([*fixed_cases(), *random_cases(args.seed, args.cases)])]
    encoded = "".join(json.dumps(case, separators=(",", ":")) + "\n" for case in cases)
    run = subprocess.run([args.driver], input=encoded, text=True, capture_output=True)
    assert run.returncode == 0, (run.returncode, run.stderr)
    actual = [json.loads(line) for line in run.stdout.splitlines()]
    assert len(actual) == len(cases), (len(actual), len(cases))
    transitions = sum(check_trace(case, result) for case, result in zip(cases, actual))
    print(f"W04 integer primitive: {len(cases)} cases, {transitions} observations, "
          f"scales={SCALES}, seed={args.seed}; exact sums/rounding and zero-heap native arithmetic passed")


if __name__ == "__main__":
    main()
