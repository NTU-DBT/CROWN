# `tests/integration/installed_reoptimization.py` — block usage map

[Source](../../../../../tests/integration/installed_reoptimization.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dba3170c0cbb88639a0f9cd8faab3333fdf722225680010d9c5acca92081d3bd`. 76 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/integration/installed_reoptimization.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 11–13](../../../../../tests/integration/installed_reoptimization.py#L11) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 14–15](../../../../../tests/integration/installed_reoptimization.py#L14) | Explanatory comments or spacing. |  |
| [B0004 · 16–72](../../../../../tests/integration/installed_reoptimization.py#L16) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard require(result.returncode == 0, f'{command}: {result.stderr\[-2500:\]} {result.stdout\[-2500:\]}'); returns result.stdout; 3 loop sites · [reviewed contract](#b0004) |
| [B0005 · 73–76](../../../../../tests/integration/installed_reoptimization.py#L73) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–10](../../../../../tests/integration/installed_reoptimization.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:28cd7dbd74e140edc10852617d456dc5dfecb3ecc6b0524a47f9526af14ce496
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for installed_reoptimization.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/installed_reoptimization.py](../../../../../tests/integration/installed_reoptimization.py), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–13](../../../../../tests/integration/installed_reoptimization.py#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an external reoptimization consumer mismatch. |
| inputs / outputs | Returns None for truthy value; false value raises RuntimeError using message. |
| invariants | An explicit if preserves checking with optimized Python. |
| ownership | Borrows operands without modifying parsed status or SDK files. |
| failure | RuntimeError reports a failed supplied condition; truth conversion errors propagate. |
| cost | One truth conversion after the caller performs comparisons. |
| Design | [tests/integration/installed_reoptimization.py](../../../../../tests/integration/installed_reoptimization.py), [docs/reoptimization.md](../../../../reoptimization.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0004

[Lines 16–72](../../../../../tests/integration/installed_reoptimization.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a moved public reoptimization example and verify switch/retire/fresh-process resume boundaries on both backends. |
| inputs / outputs | Parses source/build/compiler/sanitize; installs and relocates the SDK, builds copied example, then calls run and resume in separate child processes for reference/indexed directories. Prints backend and total-command success lines. |
| invariants | Requires C++23/public headers/no old prefix or test archive; checks observed sequence=sink 9 then 10, source offsets 90/100, generation/first_generation 3 and immutable sink origin 1, plus positive selection/compiler timings. The checks observe these finite example boundaries. |
| ownership | TemporaryDirectory encloses install/build/durable example directories and cleans on all exits. Nested run retains only command/exit records and returns a newly captured stdout str; Python does not mutate source/build inputs. |
| failure | Argparse errors exit; subprocess timeout 240, launch, JSON/file failures and RuntimeError checks propagate uncaught by the module entrypoint. Nonzero child status is translated with captured channel suffixes. |
| cost | Install/configure/-j2 build plus four actual consumer runs; each may perform native selection, compilation, file writes and recovery. Reads compiler/link files and buffers complete child streams; no claim of power-loss testing. |
| Design | [tests/integration/installed_reoptimization.py](../../../../../tests/integration/installed_reoptimization.py), [docs/reoptimization.md](../../../../reoptimization.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0005

[Lines 73–76](../../../../../tests/integration/installed_reoptimization.py#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Build a moved public reoptimization example and verify switch/retire/fresh-process resume boundaries on both backends. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/installed_reoptimization.py](../../../../../tests/integration/installed_reoptimization.py), [docs/development.md](../../../../development.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/local-sink.md](../../../../local-sink.md) |
