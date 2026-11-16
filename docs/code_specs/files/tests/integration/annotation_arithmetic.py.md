# `tests/integration/annotation_arithmetic.py` — block usage map

[Source](../../../../../tests/integration/annotation_arithmetic.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5b4a3f566f9d6a13b862fc1c861fec2ed7cdf42129fae55811d21b775c8bad5d`. 145 lines partitioned into 14 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/annotation_arithmetic.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites · [reviewed contract](#b0001) |
| [B0002 · 17–20](../../../../../tests/integration/annotation_arithmetic.py#L17) | Callable definition: def record(line, expected): | calls append, split, get · [reviewed contract](#b0002) |
| [B0003 · 21–22](../../../../../tests/integration/annotation_arithmetic.py#L21) | Explanatory comments or spacing. |  |
| [B0004 · 23–26](../../../../../tests/integration/annotation_arithmetic.py#L23) | Callable definition: def operation(op, a, b, c): | calls ; returns {"add": lambda: a + b, "multiply": lambda: a * b, · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../../tests/integration/annotation_arithmetic.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–31](../../../../../tests/integration/annotation_arithmetic.py#L29) | Callable definition: def integer(op, a, b, c=0): | calls operation, record · [reviewed contract](#b0006) |
| [B0007 · 32–48](../../../../../tests/integration/annotation_arithmetic.py#L32) | declares values/defaults or compile-time conditions. | 6 loop sites · [reviewed contract](#b0007) |
| [B0008 · 49–61](../../../../../tests/integration/annotation_arithmetic.py#L49) | Callable definition: def unsigned(op, limit, a, b, c=0): | calls max, in, operation, record; growth new; source comment (unverified): # Retraction is validated before the new contribution, matching the · [reviewed contract](#b0008) |
| [B0009 · 62–76](../../../../../tests/integration/annotation_arithmetic.py#L62) | declares values/defaults or compile-time conditions. | 5 loop sites · [reviewed contract](#b0009) |
| [B0010 · 77–84](../../../../../tests/integration/annotation_arithmetic.py#L77) | Callable definition: def spelling(coefficient, scale): | calls str, abs, zfill, rstrip; returns sign + digits if coefficient else "0" · [reviewed contract](#b0010) |
| [B0011 · 85–86](../../../../../tests/integration/annotation_arithmetic.py#L85) | Explanatory comments or spacing. |  |
| [B0012 · 87–101](../../../../../tests/integration/annotation_arithmetic.py#L87) | Callable definition: def decimal(op, p, s, a, b, c="0"): | calls Fraction, fits, abs, all; returns scaled.denominator == 1 and abs(scaled.numerator) &lt; bound; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 102–137](../../../../../tests/integration/annotation_arithmetic.py#L102) | declares values/defaults or compile-time conditions. | 12 loop sites; source comment (unverified): # Mixed scales, exact removable zeros, final-only replacement, invalid operands, · [reviewed contract](#b0013) |
| [B0014 · 138–145](../../../../../tests/integration/annotation_arithmetic.py#L138) | declares values/defaults or compile-time conditions. | 2 loop sites · [reviewed contract](#b0014) |

## B0001

[Lines 1–16](../../../../../tests/integration/annotation_arithmetic.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IMIN, IMAX = -(2**63), 2**63 - 1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the deterministic W01 oracle module state before its finite case-generation blocks run. |
| inputs / outputs | No CLI input in this span; binds RNG seed 49153, empty cases/counts/outcomes accumulators, and int64/uint64 bounds for later module-level loops. |
| invariants | This unguarded module setup also runs on import. It does not launch the CROWN arithmetic driver until B0014. |
| ownership | The module owns the RNG and mutable expected-case/count containers until process exit; no CROWN runtime state is retained. |
| failure | Python import/allocation errors propagate; this span installs no catch or cleanup. |
| cost | Module imports, fixed RNG/container initialization and literal integer bounds; later blocks grow cases through their finite loops. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), CMakeLists.txt:966, [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), tests/integration/annotation_arithmetic.py:1-16 |

## B0002

[Lines 17–20](../../../../../tests/integration/annotation_arithmetic.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def record(line, expected):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one native arithmetic request and its independently computed expected response to module state. |
| inputs / outputs | Takes line and expected text; appends their pair to cases, increments the domain count indexed by line\[0\] and outcome count indexed by expected first word. Returns None. |
| invariants | The caller must supply a nonempty line whose first character is u/i/d and a nonempty expected response; counters describe appended requests rather than native execution. |
| ownership | Retains references to the supplied strings in global cases and mutates global counts/outcomes; repeated calls accumulate and no reset is performed. |
| failure | Empty/malformed text or unknown domain can raise IndexError/KeyError after the pair was already appended, so failure is not transactional. |
| cost | Amortized list append plus dictionary updates and expected.split() allocation proportional to response length; the global list retains all cases until process exit. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0004

[Lines 23–26](../../../../../tests/integration/annotation_arithmetic.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def operation(op, a, b, c):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the unbounded arithmetic expression chosen by a bounded-policy test request. |
| inputs / outputs | Accepts one of add/multiply/remove/replace/scale and arithmetic operands; returns a+b, a*b, a-b, a-b+c or a*b respectively. |
| invariants | Evaluates only the selected lambda; no overflow, operand-domain or result-range check occurs here. Replace has one final arithmetic result, not intermediate bounded rejection. |
| ownership | Borrows immutable numeric operands and returns their arithmetic result; the dispatch dictionary/lambdas are newly created per call. |
| failure | Unknown op raises KeyError; unsupported operands propagate their arithmetic exceptions. |
| cost | Constant-size dispatch allocation; Python integer/Fraction addition, multiplication and reduction cost grows with operand bit lengths. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0006

[Lines 29–31](../../../../../tests/integration/annotation_arithmetic.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer(op, a, b, c=0):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate an int64-policy expected result from an exact Python-integer expression. |
| inputs / outputs | Takes op,a,b and optional c=0; records an i request and either ok decimal result or annotation_overflow. Returns None. |
| invariants | Checks the final result inclusively against IMIN/IMAX; it does not independently reject out-of-range inputs or intermediate arithmetic. Callers generate signed operands and unsigned scale weights. |
| ownership | Numeric inputs are borrowed; formatted request/result strings are retained by record in global case/counter state. |
| failure | Unknown operation/arithmetic/formatting failures propagate before recording; record can partially mutate globals on malformed domain/outcome. |
| cost | Unbounded integer arithmetic plus decimal rendering of every operand/result, followed by retained per-case text; not fixed machine-integer work. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0007

[Lines 32–48](../../../../../tests/integration/annotation_arithmetic.py#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rng.randint(IMIN, IMAX))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the finite signed-integer W01 boundary and seeded random cases to the module oracle corpus. |
| inputs / outputs | Uses the fixed signed endpoints and RNG prepared in B0001; appends encoded requests and Python-integer expectations through integer(). |
| invariants | This is unguarded module-level code: importing the file runs these finite loops as well as direct execution. The input family is the literal boundary set plus the explicitly bounded 1,600 random draws; it is not a universal arithmetic proof. |
| ownership | The module retains request strings, expected strings, and counters for the later subprocess comparison. |
| failure | A helper/assertion/allocation error aborts script execution; this block has no local catch or rollback of appended cases. |
| cost | Finite Cartesian/boundary loops and 1,600 draws; retained case storage grows with produced requests. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), CMakeLists.txt:966, tests/integration/annotation_arithmetic.py:32-48 |

## B0008

[Lines 49–61](../../../../../tests/integration/annotation_arithmetic.py#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def unsigned(op, limit, a, b, c=0):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate bounded unsigned-policy expectations including replacement/retraction error priority. |
| inputs / outputs | Takes operation, limit,a,b,c=0 and records a u request. Checks max(a,b)&gt;limit first, then remove/replace b&gt;a, then replace c&gt;limit, otherwise computes and tests 0&lt;=value&lt;=limit. |
| invariants | Retraction underflow is tested before the replacement contribution; no unsigned wrap is used. Negative operands/limits and unsupported ops are outside generated input preconditions and not comprehensively validated. |
| ownership | Creates retained text through record and changes global counters; caller numeric inputs remain unchanged. |
| failure | The generated error is protocol text rather than a Python exception; unknown operation or incompatible arithmetic/formatting can still raise. |
| cost | A few arbitrary-precision comparisons plus selected arithmetic and decimal formatting; global memory grows with total recorded cases and digit lengths. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0009

[Lines 62–76](../../../../../tests/integration/annotation_arithmetic.py#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rng.randint(0, limit), rng.randint(0, limit), rng.randint(0, limit))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append finite unsigned-policy limit, boundary, and seeded random requests to the W01 oracle corpus. |
| inputs / outputs | Uses explicit limits 3, 2^53+1 and UINT64_MAX, generated edge values, and 1,000 seeded random requests; calls unsigned(). |
| invariants | This is unguarded module-level code: importing the file runs these finite loops too. Only the literal limit/edge family and fixed random count are covered; no claim extends to arbitrary limits or all arithmetic inputs. |
| ownership | Mutates the same module-owned cases/counts/outcomes used by B0014. |
| failure | Helper, assertion or allocation errors propagate without restoring prior corpus entries. |
| cost | Finite edge cross-products plus 1,000 draws; memory is proportional to accumulated cases. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), CMakeLists.txt:966, tests/integration/annotation_arithmetic.py:62-76 |

## B0010

[Lines 77–84](../../../../../tests/integration/annotation_arithmetic.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def spelling(coefficient, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render an integer coefficient and nonnegative decimal scale in canonical fixture spelling. |
| inputs / outputs | Takes coefficient and scale; returns str with a sign for negative nonzero values, a decimal point when needed, no removable fractional zeros, and exactly 0 for zero. |
| invariants | zfill(scale+1) preserves fractional leading zeros; stripping affects only the fractional suffix. Assumes integer coefficient and nonnegative integer scale; it is not a parser or declared-precision validator. |
| ownership | Allocates intermediate digit/padded/sliced strings and returns new text; no input or global mutation. |
| failure | Invalid scale/coefficient types can raise in comparisons, zfill or slicing; huge scale may exhaust memory. |
| cost | Decimal integer conversion and O(max(digits,scale)) padding/slicing; scale can determine allocation even for small coefficients. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0012

[Lines 87–101](../../../../../tests/integration/annotation_arithmetic.py#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal(op, p, s, a, b, c="0"):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate a fixed-decimal arithmetic expectation using exact Fraction arithmetic. |
| inputs / outputs | Parses a,b,c as Fraction; takes precision p, scale s and op, then records a d request with a canonical exact result or annotation_overflow. |
| invariants | An operand fits only when value*10**s is integral and its coefficient magnitude is &lt;10**p; scale checks a alone, replace checks all three, others a/b. The final result must fit too; scale weight b is not checked as a decimal operand. |
| ownership | Owns local rational/intermediate values and formatted strings; record retains the request/outcome and mutates module counters. Input strings remain unchanged. |
| failure | Malformed Fraction spellings, bad exponents/types or unknown operation raise before record; policy rejection is recorded as text. No native checked-decimal implementation is called by this helper. |
| cost | Fraction parsing/reduction, powers of ten and exact arithmetic have digit/bit-dependent cost; repeated fits multiplies/rational reductions and canonical rendering allocates full strings. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md) |

## B0013

[Lines 102–137](../../../../../tests/integration/annotation_arithmetic.py#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
decimal(op, 38, s, a, b, a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append fixed-precision decimal boundary and seeded requests to the W01 oracle corpus. |
| inputs / outputs | Uses the literal precision/scale pairs, edge spellings, explicit special cases, and bounded loops over scales/random values; calls decimal(). |
| invariants | This is unguarded module-level code: importing the file runs these finite loops too. Expectations come from the test’s exact Python Fraction/integer helpers; cases are finite and do not establish every supported decimal behavior. |
| ownership | The module retains generated lines and expected outputs until B0014 finishes. |
| failure | Assertions/helper/Decimal/allocation errors propagate and may leave the in-memory corpus partially appended. |
| cost | Fixed finite precision/scale loops and bounded random draws; case storage grows with the enumerated requests. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), CMakeLists.txt:966, tests/integration/annotation_arithmetic.py:102-137 |

## B0014

[Lines 138–145](../../../../../tests/integration/annotation_arithmetic.py#L138); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print(f"Independent arbitrary-precision oracle: {len(cases)} cases; domains={counts}; outcomes={outcomes}")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the W01 native arithmetic driver once and compare its complete line output with the finite Python oracle corpus. |
| inputs / outputs | Reads executable path from sys.argv\[1\], sends newline-delimited cases, captures text stdout/stderr, and expects one exact output line per case. |
| invariants | Importing this unguarded block launches the child. Nonzero exit and the 45-second timeout fail through check=True; with Python assertions enabled, wrong line count, answer mismatch or stderr also fail. |
| ownership | The Python process owns all request/expected/output strings; the child process is owned by subprocess.run; this span writes no fixture files. |
| failure | CalledProcessError and TimeoutExpired propagate. With Python assertions enabled, count/answer/stderr mismatches raise AssertionError. No retry or partial-result record is made. |
| cost | One child with a 45-second timeout. The whole input and captured stdout/stderr are retained; this wrapper sets no captured-output byte quota. |
| Design | [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), CMakeLists.txt:966, [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), tests/integration/annotation_arithmetic.py:138-145 |
