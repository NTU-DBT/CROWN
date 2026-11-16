# `tests/integration/aggregate_integer_oracle.py` — block usage map

[Source](../../../../../tests/integration/aggregate_integer_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d0615bf714c5b98584edb12afa4c4b424f29345b32696f047d39190a8abe62c0`. 119 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/integration/aggregate_integer_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–20](../../../../../tests/integration/aggregate_integer_oracle.py#L19) | Callable definition: def operation(value, weight=1, erase=False): | calls ; returns {"value": value, "weight": weight, "erase": erase} · [reviewed contract](#b0002) |
| [B0003 · 21–22](../../../../../tests/integration/aggregate_integer_oracle.py#L21) | Explanatory comments or spacing. |  |
| [B0004 · 23–39](../../../../../tests/integration/aggregate_integer_oracle.py#L23) | Callable definition: def fixed_cases(): | calls in, operation; 4 loop sites · [reviewed contract](#b0004) |
| [B0005 · 40–41](../../../../../tests/integration/aggregate_integer_oracle.py#L40) | Explanatory comments or spacing. |  |
| [B0006 · 42–61](../../../../../tests/integration/aggregate_integer_oracle.py#L42) | Callable definition: def random_cases(seed, count): | calls Random, range, randrange, choice; 3 loop sites · [reviewed contract](#b0006) |
| [B0007 · 62–63](../../../../../tests/integration/aggregate_integer_oracle.py#L62) | Explanatory comments or spacing. |  |
| [B0008 · 64–71](../../../../../tests/integration/aggregate_integer_oracle.py#L64) | Callable definition: def rounded_average(total, count, scale): | calls divmod, abs, Decimal, scaleb; returns Decimal(coefficient).scaleb(-scale); source comment (unverified): # Divide one exact integer numerator. This deliberately differs from the · [reviewed contract](#b0008) |
| [B0009 · 72–73](../../../../../tests/integration/aggregate_integer_oracle.py#L72) | Explanatory comments or spacing. |  |
| [B0010 · 74–96](../../../../../tests/integration/aggregate_integer_oracle.py#L74) | Callable definition: def check_trace(case, actual): | calls len, enumerate, Decimal, rounded_average; guard assert (Decimal(result\["average"\]) if result\["average"\] is not None else None) == expected, context; returns len(trace); 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 97–98](../../../../../tests/integration/aggregate_integer_oracle.py#L97) | Explanatory comments or spacing. |  |
| [B0012 · 99–115](../../../../../tests/integration/aggregate_integer_oracle.py#L99) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, getcontext; 4 loop sites · [reviewed contract](#b0012) |
| [B0013 · 116–119](../../../../../tests/integration/aggregate_integer_oracle.py#L116) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–18](../../../../../tests/integration/aggregate_integer_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"""Check W04 integer statistics against unbounded Python arithmetic.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit this independent gate to primitive numeric outputs and guarded native allocation behavior. |
| inputs / outputs | Python generates legal compressed histories and compares all driver prefix observations using unbounded integer arithmetic. |
| invariants | This is a private-primitive gate; it does not bind SQL, form groups, test NULL/group publication, install transaction state or establish W04 completion. |
| ownership | Test process owns Python/JSON/reference values; target heap hooks cover only native marked intervals. |
| failure | Native nonzero exit, malformed/missing output or comparison assertions fail the gate. |
| cost | Reference and orchestration may allocate; no native allocator/whole-process memory bound follows from this script. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

```text
MINIMUM = -(1 << 63)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix the signed64 domain and exercise every admitted AVG scale from zero through eighteen. |
| inputs / outputs | Signed minimum/maximum and tuple(range(19)) feed every explicit scale cohort and the seeded scale cycle. |
| invariants | All nineteen admitted scale values appear; the input/group-count domain stays within signed64 bounds. |
| ownership | Python module owns immutable integer/tuple constants. |
| failure | No runtime source/SQL admission is performed by defining them. |
| cost | Fixed test configuration; Python object creation is outside native heap hooks. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0002

[Lines 19–20](../../../../../tests/integration/aggregate_integer_oracle.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def operation(value, weight=1, erase=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one compressed contribution add/retract for the C++ driver. |
| inputs / outputs | Returns dictionary with value, weight and erase keys. |
| invariants | No repeated-row expansion or validation/coercion occurs here; callers generate in-domain values and valid weight histories. |
| ownership | Returned dictionary is Python-owned and later JSON serialized. |
| failure | Ordinary Python allocation/type errors propagate; numerical preconditions are supplied by case construction. |
| cost | Fixed dictionary assembly, with scalar values retained by Python references. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0004

[Lines 23–39](../../../../../tests/integration/aggregate_integer_oracle.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fixed_cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate explicit numeric boundaries, cancellation, rounding ties and large-count histories. |
| inputs / outputs | Yields26 scale/history cases for each of six scales,156 fixed cases total. |
| invariants | Includes MIN/MAX, zero/one, full admitted multiplicities, signed cancellation/retraction, near-boundary sums, counts around2^53/MAX and exact/below-half fractional cases at very large denominators. Histories keep legal bounded group counts. |
| ownership | Generator yields Python-owned operation lists; it retains no driver/native state. |
| failure | Construction allocation failures propagate; this is valid-input coverage rather than malformed-input testing. |
| cost | Fixed156 histories with at most four operations each; large multiplicities are scalar weights, not row arrays. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0006

[Lines 42–61](../../../../../tests/integration/aggregate_integer_oracle.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def random_cases(seed, count):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate reproducible bounded weighted histories with valid removals and later additions. |
| inputs / outputs | Local seeded Random yields count histories, each with1..8 initial contributions and two operations per reversed original contribution. |
| invariants | remaining+current_count=MAX throughout. Each removal is at most that recorded original component; previously processed components leave nonnegative residual/additions, so duplicate values do not invalidate available multiplicity. Scale cycles through six choices. |
| ownership | Local RNG, component list and operation list are Python-owned; no state is borrowed from the native driver. |
| failure | No independent row-set checker here; generator construction establishes valid histories. Negative requested case counts yield no random cases through range semantics. |
| cost | At most24 compressed operations per random history, with ordinary Python random/int/list work; no weight expansion. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0008

[Lines 64–71](../../../../../tests/integration/aggregate_integer_oracle.py#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rounded_average(total, count, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the reference rounded decimal from one full unbounded scaled numerator. |
| inputs / outputs | Requires positive coherent count; divmod(abs(total)*10**scale,count), ties increment magnitude, sign restored before Decimal scaling. |
| invariants | Using2*remainder&gt;=count implements half away from zero independently of native quotient/remainder splitting. Decimal context must retain all coefficient digits; main sets precision200, sufficient for generated bounded inputs. |
| ownership | Python integers and Decimal result own reference storage independently of native words/output. |
| failure | Zero/invalid divisor and insufficient/altered decimal context are outside the generated-case contract; exceptions propagate. |
| cost | Unbounded integer multiply/divide plus decimal scaling, with bit/precision-dependent Python memory; no fixed native arithmetic cost is claimed. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0010

[Lines 74–96](../../../../../tests/integration/aggregate_integer_oracle.py#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_trace(case, actual):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every native prefix with an independently recomputed exact statistic. |
| inputs / outputs | Checks case ID/trace length, exact SUM, external count, signed64 fit/value, optional rounded AVG and absence of textual negative zero; returns observation count. |
| invariants | Recomputes total/count using Python signed products from original operations; assumes generated legal histories. Decimal comparisons are numerical, so canonical trailing-zero trimming does not masquerade as a fixed padded-scale text test. |
| ownership | Borrows case/response structures; owns local exact reference values and failure context. |
| failure | Any mismatch or malformed response raises assertion/key/type/decimal error; no partial success is reported. Python assertions must be enabled for this gate. |
| cost | One independent exact update and numeric comparison per trace prefix, with Python bigint/Decimal allocation proportional to represented widths. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0012

[Lines 99–115](../../../../../tests/integration/aggregate_integer_oracle.py#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the line driver and require complete independent agreement for every generated observation. |
| inputs / outputs | --driver required, --cases default2048 and fixed seed; sets Decimal precision200, materializes156 fixed plus requested random cases, runs one driver and checks all responses. |
| invariants | Driver returncode must be0 and response count exact. Default input has2204 cases; observed30326 prefix checks belong to the recorded seed/logs. All JSON parsing/serialization and Python reference work lie outside native no_heap scopes. |
| ownership | Owns full case/input/output/parsed response inventories and subprocess buffers; native executable is an explicitly selected test dependency. |
| failure | Argument/subprocess/nonzero exit/output/comparison failures abort. No subprocess timeout is set here; CTest supplies its outer test timeout. This gate needs nonoptimized Python assertions. |
| cost | Memory can hold cases, encoded stdin, complete stdout and parsed traces together; process runtime and byte costs scale with requested cases/observations. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0013

[Lines 116–119](../../../../../tests/integration/aggregate_integer_oracle.py#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the independent primitive gate only when the script is executed directly. |
| inputs / outputs | Direct invocation calls main; importing definitions does not launch the driver. |
| invariants | Provides no SQL/runtime acceptance or native source validation beyond main’s checks. |
| ownership | No additional owner beyond main/local process objects. |
| failure | Uncaught assertion/exception makes direct script execution fail. |
| cost | Fixed entry dispatch; main owns all process/reference costs. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |
