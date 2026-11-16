# `tests/integration/sql_aggregate_transaction_crash.py` — block usage map

[Source](../../../../../tests/integration/sql_aggregate_transaction_crash.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `53681b2cfb79a4b734c5bd98ebbc5c009191117b3135a0e041b7bc07e5234854`. 100 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–40](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L22) | Callable definition: def frames(encoded): | calls fromhex, len, unpack_from, sha256; returns \[session_epoch(frame.hex()) for frame in result\[1:\]\]; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 41–42](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L41) | Explanatory comments or spacing. |  |
| [B0004 · 43–49](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L43) | Callable definition: def row(kind): | calls int; returns \["next", 2, 2, 1, {"decimal": "1"}, {"decimal": "0.5"}\]; \[None if kind == "seed" else "next", MAX-1… · [reviewed contract](#b0004) |
| [B0005 · 50–51](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L50) | Explanatory comments or spacing. |  |
| [B0006 · 52–53](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L52) | Callable definition: def change(key, before, after): | calls ; returns {"key": \[7, key\], "before": before, "after": after} · [reviewed contract](#b0006) |
| [B0007 · 54–55](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L54) | Explanatory comments or spacing. |  |
| [B0008 · 56–72](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L56) | Callable definition: def check_tape(case, probe): | calls frames, change, row, append; 1 loop sites; source comment (unverified): # JSON text equality preserves bool/int and decimal/int distinctions. · [reviewed contract](#b0008) |
| [B0009 · 73–74](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L73) | Explanatory comments or spacing. |  |
| [B0010 · 75–96](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L75) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; 6 loop sites · [reviewed contract](#b0010) |
| [B0011 · 97–100](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L97) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–21](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MAX = 2**63-1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the independent exact count boundary and import the existing byte decoder. |
| inputs / outputs | Python arbitrary-precision MAX and session_epoch decoder support fourteen fixture cases. |
| invariants | No native descriptor, source state or native expected row is used to calculate Python payloads. |
| ownership | Module owns constants and ordinary Python workspace. |
| failure | Import failure aborts test setup. |
| cost | Fixed setup; Python integers do not expand the compressed bag. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 22–40](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def frames(encoded):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate retained tape framing/checksums/header identity before decoding epochs. |
| inputs / outputs | Hex tape -&gt; list of independently decoded GroupEpoch dictionaries. |
| invariants | Checks complete lengths, magic/version, both SHA fields, SinkHeader kind/ordinal/query/sink/base and total header size; session_epoch parses each subsequent frame. |
| ownership | Python owns decoded bytes/list; input string remains caller-owned. |
| failure | Malformed or mismatched tape asserts; hex/struct/decoder errors propagate. |
| cost | Linear in tape bytes with temporary frame copies; no native runtime allocation or bag expansion. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0004

[Lines 43–49](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def row(kind):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the independent typed six-cell expected aggregate output. |
| inputs / outputs | seed/mixed/probe/small -&gt; Python scalar/NULL cells and tagged decimal dictionaries. |
| invariants | Count uses exact MAX arithmetic; decimal and bigint remain distinct. Small AVG is 0.5; heavy AVG rounds to 0 at scale 18. |
| ownership | Returned small list/dictionaries are ordinary Python values. |
| failure | Callers use only four known fixture labels. |
| cost | Constant-size expected row construction. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 52–53](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def change(key, before, after):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one full-key before/final group change for the independent oracle. |
| inputs / outputs | Nullable selected key and optional rows -&gt; {key:\[7,key\],before,after}. |
| invariants | None for an absent row is distinct from a row containing nullable cells. |
| ownership | New dictionary borrows its row values during comparison. |
| failure | No special recovery branch. |
| cost | Constant-size dictionary construction. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 56–72](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_tape(case, probe):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare each retained baseline/probe tape to manually calculated typed epochs. |
| inputs / outputs | One native metadata record and probe flag -&gt; assertions over every epoch, output cell, command, sequence and generation. |
| invariants | Always seed/mixed epochs; recover additionally erases at W5/gen3; follow-up uses small new group or heavy same group. JSON text equality distinguishes bool/int and decimal/int. |
| ownership | Expected and decoded Python objects live only for this comparison. |
| failure | Any frame/payload/order/identity mismatch asserts. |
| cost | Two to four small epochs per retained tape. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 75–96](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the actual native fault matrix, retain its artifact and independently check all healthy/probe payloads. |
| inputs / outputs | Required driver/output-root -&gt; unique run directory, native process with a timeout of 1500 seconds, fourteen cases covering both backends/seven actions, twenty-eight decoded tapes and JSON summary/hash. |
| invariants | Assertions must be enabled; native exit must succeed; every case has EIO/process cuts. Per-fault native byte equality precedes export; Python decodes healthy baseline/probe tapes, not each fault tape separately. |
| ownership | Unique output remains available for audit; subprocess output is captured; Python owns decoder workspace. |
| failure | Nonzero exit, timeout, missing/wrong JSON or mismatch fails directly. Summary explicitly declines host power-loss inference. |
| cost | One native matrix invocation plus twenty-eight finite tape decodes; no production overhead. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 97–100](../../../../../tests/integration/sql_aggregate_transaction_crash.py#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run the actual native fault matrix, retain its artifact and independently check all healthy/probe payloads. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/sql_aggregate_transaction_crash.py](../../../../../tests/integration/sql_aggregate_transaction_crash.py), [docs/development.md](../../../../development.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |
