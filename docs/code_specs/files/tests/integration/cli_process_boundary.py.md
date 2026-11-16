# `tests/integration/cli_process_boundary.py` — block usage map

[Source](../../../../../tests/integration/cli_process_boundary.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `27090acd900737e31619eec1695e44f0a847f0d3e549628249a75d86de77a020`. 46 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/integration/cli_process_boundary.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../tests/integration/cli_process_boundary.py#L10) | Callable definition: def no_core_dump(): | calls setrlimit · [reviewed contract](#b0002) |
| [B0003 · 13–14](../../../../../tests/integration/cli_process_boundary.py#L13) | Explanatory comments or spacing. |  |
| [B0004 · 15–18](../../../../../tests/integration/cli_process_boundary.py#L15) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0004) |
| [B0005 · 19–20](../../../../../tests/integration/cli_process_boundary.py#L19) | Explanatory comments or spacing. |  |
| [B0006 · 21–42](../../../../../tests/integration/cli_process_boundary.py#L21) | Callable definition: def main(): | calls str, Path, resolve, in; guard require(normal.returncode == 0 and normal.stdout and not normal.stderr,; 1 loop sites; source comment (unverified): # These short writes can fit in stdout's buffer. Exit must check flush. · [reviewed contract](#b0006) |
| [B0007 · 43–46](../../../../../tests/integration/cli_process_boundary.py#L43) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–9](../../../../../tests/integration/cli_process_boundary.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a Linux/POSIX real-process CLI regression using only the Python standard library. |
| inputs / outputs | Imports subprocess, JSON, resource and path helpers; expects the built CLI path as argv1. |
| invariants | Exercises actual process I/O/exit behavior rather than a mocked dispatcher; /dev/full is the deterministic buffered-output failure device. |
| ownership | Python process owns helper imports and later subprocess output buffers. |
| failure | Missing platform facilities or imports fail test setup; no production fallback is introduced. |
| cost | Test-only import/interpreter overhead; no production code runs at module inclusion. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md) |

## B0002

[Lines 10–12](../../../../../tests/integration/cli_process_boundary.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def no_core_dump():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Suppress crash artifacts for each regression child. |
| inputs / outputs | subprocess preexec_fn sets the child core-size soft and hard limits to0 before exec. |
| invariants | Only RLIMIT_CORE changes; address-space, native work and query account limits are unchanged. The regression still observes a negative return code if an old child aborts. |
| ownership | Child process owns its resource limit; parent state is unchanged. |
| failure | setrlimit errors fail child setup/test. This is test isolation, not recovery. |
| cost | One setrlimit syscall per child, solely in this Python test. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md) |

## B0004

[Lines 15–18](../../../../../tests/integration/cli_process_boundary.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a failed externally observed CLI expectation. |
| inputs / outputs | Truthy condition returns; false condition raises RuntimeError with the captured child observation. |
| invariants | A failed assertion makes the test fail rather than treating missing or malformed output as success. |
| ownership | Borrows condition/message for the call; Python exception retains a failure message. |
| failure | The deliberate RuntimeError propagates to the test process. |
| cost | Constant conditional; diagnostic formatting/storage is test-only. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md) |

## B0006

[Lines 21–42](../../../../../tests/integration/cli_process_boundary.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify final stdout flush failure and catch-body diagnostic encoding through five real CLI children. |
| inputs / outputs | For version/help, require normal exit0/nonempty stdout/empty stderr and /dev/full exit2/io_error JSON. A raw ff argument must return3/internal_error JSON with no stdout. |
| invariants | Checks exact statuses and parsed UTF8 JSON. Small writes expose buffering; invalid POSIX argv exposes strict JSON failure from an active handler. No assumption of durable rollback or command retry. |
| ownership | Parent owns captured output and /dev/full context; subprocess.run waits for each child. Core limits change in children only; no temporary durable query files are created. |
| failure | Nonzero unexpected statuses, aborts, invalid JSON and timeouts fail the test. The context manager closes /dev/full on all paths. This does not simulate general system OOM; the private allocation harness separately covers persistent C++ new failure. |
| cost | Five serial subprocess launches, bounded child timeouts and small fixed-command output. Test-only cost; no query pipeline instrumentation. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md) |

## B0007

[Lines 43–46](../../../../../tests/integration/cli_process_boundary.py#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the process regression when CTest launches this file. |
| inputs / outputs | Calls main only for direct execution, then returns the interpreter status. |
| invariants | Importing the module does not spawn CLI children. |
| ownership | Python launcher owns the call stack and propagating exception. |
| failure | Any uncaught regression failure gives a failing interpreter exit. |
| cost | One test entry check and call, no production overhead. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md) |
