# `tests/property/reference_fuzz_test.py` — block usage map

[Source](../../../../../tests/property/reference_fuzz_test.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c398cf746500c5b3259f8e31060e82c3f83d571ccccd911b0bb8fc61234b83fc`. 145 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/property/reference_fuzz_test.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–137](../../../../../tests/property/reference_fuzz_test.py#L19) | Callable definition: def main() -&gt; int: | calls ArgumentParser, add_argument, parse_args, FuzzError; returns False; fuzz.first_difference(actual, expected) is not None; growth insert; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 138–145](../../../../../tests/property/reference_fuzz_test.py#L138) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–18](../../../../../tests/property/reference_fuzz_test.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
from tools import reference_fuzz as fuzz  # noqa: E402
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the reference fuzz script’s repository import root before its guarded CLI driver runs. |
| inputs / outputs | Derives ROOT from __file__, inserts its string form at the front of sys.path, then imports tools.reference_fuzz. |
| invariants | This is process-local import-path mutation followed by module import; the fuzz CLI main is guarded separately and receives the executable/seeds from CTest. |
| ownership | The process owns sys.path and retains the imported module. This block creates no explicit fixture/output file; ordinary import machinery may cache bytecode. |
| failure | Path conversion/import errors propagate; no restoration of the prior sys.path is performed before process exit. |
| cost | One path computation/list insertion and one Python module import/initialization. |
| Design | [tests/property/reference_fuzz_test.py](../../../../../tests/property/reference_fuzz_test.py), CMakeLists.txt:1008, [tools/reference_fuzz.py](../../../../../tools/reference_fuzz.py), tests/property/reference_fuzz_test.py:1-18 |

## B0002

[Lines 19–137](../../../../../tests/property/reference_fuzz_test.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run bounded seeded CLI-versus-SQLite semantics and verify a fault packet shrinks to the relevant singleton insertion. |
| inputs / outputs | Parses executable, positive seeds, nonnegative updates and seed-start; generates/validates each case and compares references. On mismatch builds a packet, shrinks with a predicate that rejects FuzzError candidates, adds actual/expected/SQL context, writes stderr and returns 1; success prints coverage and returns 0. |
| invariants | Requires shape coverage when seeds span SHAPES and int64/string/bool coverage at &gt;=12 seeds, explicitly checks invalid variants, and checks the injected fault packet has one insert/no initial rows and self-consistent CQ/context fields. This is bounded coverage, not exhaustive fuzz correctness. |
| ownership | Owns generated documents, counters and packets; nested reproduces borrows candidate documents for delegated CLI/SQLite calls. Packet fields can reference minimized document/query/trace containers; no independent deep-copy promise is made. Resource lifetimes inside CLI/SQL/shrinker helpers remain those helpers’ contracts. |
| failure | Argparse exits for syntax; invalid bounds/checks raise fuzz.FuzzError handled by entrypoint. Per-seed Mismatch/FuzzError have distinct failure-packet paths; errors during mismatch minimization or unrelated I/O/JSON failures are not broadly caught here. |
| cost | Runs generation plus CLI and SQLite work per seed; mismatch minimization repeatedly validates/executes candidates, then executes minimized references again. Materializes full JSON failure packets and uses deterministic finite random traces; runtime is dominated by delegated child/SQL/search work, not Counter updates. |
| Design | [tests/property/reference_fuzz_test.py](../../../../../tests/property/reference_fuzz_test.py), [docs/semantics.md](../../../../semantics.md), [tools/reference_fuzz.py](../../../../../tools/reference_fuzz.py) |

## B0003

[Lines 138–145](../../../../../tests/property/reference_fuzz_test.py#L138); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run bounded seeded CLI-versus-SQLite semantics and verify a fault packet shrinks to the relevant singleton insertion. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only fuzz.FuzzError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/property/reference_fuzz_test.py](../../../../../tests/property/reference_fuzz_test.py), [docs/development.md](../../../../development.md), [docs/semantics.md](../../../../semantics.md), [tools/reference_fuzz.py](../../../../../tools/reference_fuzz.py) |
