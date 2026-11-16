"""Independent unbounded-integer/fraction oracle for the bounded W01 policies."""
import itertools
import random
import subprocess
import sys
from fractions import Fraction


rng = random.Random(0xC001)
cases = []
counts = {"u": 0, "i": 0, "d": 0}
outcomes = {}
UMIN, UMAX = 0, 2**64 - 1
IMIN, IMAX = -(2**63), 2**63 - 1


def record(line, expected):
    cases.append((line, expected))
    counts[line[0]] += 1
    outcomes[expected.split()[0]] = outcomes.get(expected.split()[0], 0) + 1


def operation(op, a, b, c):
    return {"add": lambda: a + b, "multiply": lambda: a * b,
            "remove": lambda: a - b, "replace": lambda: a - b + c,
            "scale": lambda: a * b}[op]()


def integer(op, a, b, c=0):
    value = operation(op, a, b, c)
    record(f"i {op} {a} {b} {c}", f"ok {value}" if IMIN <= value <= IMAX else "error annotation_overflow")


signed = [IMIN, IMIN + 1, -(2**53 + 1), -1, 0, 1, 2**53 + 1, IMAX - 1, IMAX]
for a, b in itertools.product(signed, repeat=2):
    for op in ("add", "multiply", "remove"):
        integer(op, a, b)
    for c in signed:
        integer("replace", a, b, c)
for a in signed:
    for weight in (0, 1, 2, 2**53 + 1, 2**63, UMAX):
        integer("scale", a, weight)
for _ in range(1600):
    op = rng.choice(("add", "multiply", "remove", "replace", "scale"))
    integer(op, rng.randint(IMIN, IMAX), rng.randint(0, UMAX) if op == "scale" else rng.randint(IMIN, IMAX),
            rng.randint(IMIN, IMAX))


def unsigned(op, limit, a, b, c=0):
    # Retraction is validated before the new contribution, matching the
    # declared replacement contract, not unsigned wraparound.
    if max(a, b) > limit:
        expected = "error annotation_overflow"
    elif op in ("remove", "replace") and b > a:
        expected = "error annotation_underflow"
    elif op == "replace" and c > limit:
        expected = "error annotation_overflow"
    else:
        value = operation(op, a, b, c)
        expected = f"ok {value}" if UMIN <= value <= limit else "error annotation_overflow"
    record(f"u {op} {limit} {a} {b} {c}", expected)


for limit in (3, 2**53 + 1, UMAX):
    values = sorted({0, 1, 2, limit - 1, limit, min(limit + 1, UMAX)})
    for a, b in itertools.product(values, repeat=2):
        for op in ("add", "multiply", "remove"):
            unsigned(op, limit, a, b)
        for c in values:
            unsigned("replace", limit, a, b, c)
for _ in range(1000):
    limit = rng.choice((UMAX, 2**53 + 1, 17))
    unsigned(rng.choice(("add", "multiply", "remove", "replace")), limit,
             rng.randint(0, limit), rng.randint(0, limit), rng.randint(0, limit))


def spelling(coefficient, scale):
    sign = "-" if coefficient < 0 else ""
    digits = str(abs(coefficient))
    if scale:
        digits = digits.zfill(scale + 1)
        digits = digits[:-scale] + "." + digits[-scale:]
        digits = digits.rstrip("0").rstrip(".")
    return sign + digits if coefficient else "0"


def decimal(op, p, s, a, b, c="0"):
    values = [Fraction(a), Fraction(b), Fraction(c)]
    operands = values[:1] if op == "scale" else values[:3] if op == "replace" else values[:2]
    bound = 10**p

    def fits(value):
        scaled = value * 10**s
        return scaled.denominator == 1 and abs(scaled.numerator) < bound

    if not all(fits(value) for value in operands):
        expected = "error annotation_overflow"
    else:
        value = operation(op, *values)
        expected = f"ok {spelling((value * 10**s).numerator, s)}" if fits(value) else "error annotation_overflow"
    record(f"d {op} {p} {s} {a} {b} {c}", expected)


for p, s in ((1, 0), (1, 1), (6, 2), (18, 9), (38, 0), (38, 18), (38, 38)):
    maximum = 10**p - 1
    values = [spelling(value, s) for value in (-maximum, -maximum + 1, -1, 0, 1, maximum - 1, maximum)]
    for a, b in itertools.product(values, repeat=2):
        for op in ("add", "multiply", "remove"):
            decimal(op, p, s, a, b)
        for c in values:
            decimal("replace", p, s, a, b, c)
    for _ in range(220):
        op = rng.choice(("add", "multiply", "remove", "replace", "scale"))
        a, b, c = (spelling(rng.randint(-maximum, maximum), s) for _ in range(3))
        decimal(op, p, s, a, str(rng.randint(0, UMAX)) if op == "scale" else b, c)

# Mixed scales, exact removable zeros, final-only replacement, invalid operands,
# extreme alignment and multiplication reaching scale76 exercise different paths.
for p, s, a, b, c in (
    (38, 38, "0", "0", "0"),
    (38, 18, "99999999999999999999.999999999999999999", "-0.000000000000000001", "-0.000000000000000001"),
    (38, 38, "0.00000000000000000000000000000000000001", "-0.00000000000000000000000000000000000001", "0"),
    (6, 2, "1.2", "2.5", "-0.01"),
    (6, 2, "0.001", "0", "0"),
    (6, 2, "10000", "0", "0"),
    (38, 0, "99999999999999999999999999999999999999", "0.00000000000000000000000000000000000001", "0"),
):
    for op in ("add", "multiply", "remove", "replace"):
        decimal(op, p, s, a, b, c)
for s in range(39):
    # Vary the canonical scale independently of the declared fixed scale.
    for _ in range(40):
        a = spelling(rng.randint(-99999, 99999), rng.randint(0, 38))
        b = spelling(rng.randint(-99999, 99999), rng.randint(0, 38))
        for op in ("add", "multiply", "remove", "replace"):
            decimal(op, 38, s, a, b, a)

result = subprocess.run([sys.argv[1]], input="\n".join(line for line, _ in cases) + "\n",
                        text=True, capture_output=True, timeout=45, check=True)
actual = result.stdout.splitlines()
assert len(actual) == len(cases), (len(actual), len(cases), result.stderr)
for index, ((line, expected), answer) in enumerate(zip(cases, actual)):
    assert answer == expected, (index, line, expected, answer)
assert not result.stderr, result.stderr
print(f"Independent arbitrary-precision oracle: {len(cases)} cases; domains={counts}; outcomes={outcomes}")
