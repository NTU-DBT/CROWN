# `tests/integration/installed_independent_queries.py` — block usage map

[Source](../../../../../tests/integration/installed_independent_queries.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `70f7d4cce502b07690b1d944ff7b3dd98859ac5a9bd7d8818147d8449e77a70f`. 115 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/integration/installed_independent_queries.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/integration/installed_independent_queries.py#L15) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../tests/integration/installed_independent_queries.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–34](../../../../../tests/integration/installed_independent_queries.py#L20) | Callable definition: def expected(sql,events): | calls connect, execute, r, s; returns rows; 3 loop sites · [reviewed contract](#b0004) |
| [B0005 · 35–36](../../../../../tests/integration/installed_independent_queries.py#L35) | Explanatory comments or spacing. |  |
| [B0006 · 37–111](../../../../../tests/integration/installed_independent_queries.py#L37) | Callable definition: def main(): | calls require, len, in, Path; guard require(len(sys.argv) in (5,6), 'usage: installed_independent_queries.py SOURCE BUILD COMPILER SANI…; returns child.stdout; growth insert; 8 loop sites · [reviewed contract](#b0006) |
| [B0007 · 112–115](../../../../../tests/integration/installed_independent_queries.py#L112) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–14](../../../../../tests/integration/installed_independent_queries.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:a3cc17ba94c33ff77456851ab0e24ad5b3f251ddd6434e345cd1e1e796b2dcb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define an offline relocated-consumer and independent SQLite acceptance script. |
| inputs / outputs | Standard-library hashing/JSON/filesystem/SQLite/process modules; bytecode writes disabled. |
| invariants | No private engine model is used as expected-result authority. |
| ownership | Script owns only its new temporary/explicit evidence directory. |
| failure | Missing tool/module propagates as test failure. |
| cost | Test-only imports; no engine dependency. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 15–17](../../../../../tests/integration/installed_independent_queries.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L17:sha256:51e1acfa31154d199aeb62997c128756b7841b4f95b1c385a0704998059a72fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn one acceptance condition into a clear test failure. |
| inputs / outputs | Condition and message in; returns only on truth. |
| invariants | A failed check cannot silently count as pass. |
| ownership | No resource ownership. |
| failure | RuntimeError on false. |
| cost | O(1) excluding message already formed. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 20–34](../../../../../tests/integration/installed_independent_queries.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L34:sha256:263073fc9faea42ead71a1ca002bde6112c19ee079221909d4cd7176057f1488
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute final SQL rows through an independent SQLite pair-table execution. |
| inputs / outputs | Supplied SQL and concrete insert/delete events in; canonical sorted rows out. |
| invariants | Apply physical events directly; translate SQLite EXISTS integer to Boolean for typed comparison. |
| ownership | Local SQLite connection owns temporary state and closes after query. |
| failure | SQL/IO/allocation failures propagate; test has no retry or alternate expected-result fallback. |
| cost | O(event processing plus SQL execution/result size), test-only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 37–111](../../../../../tests/integration/installed_independent_queries.py#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L111:sha256:23dc590a8d8eac35cb072404327159fca17454102809efcb6d121329604bf7e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install, relocate, build and run an external public consumer on four unseen SQL/input pairs. |
| inputs / outputs | SOURCE BUILD COMPILER SANITIZE and optional fresh evidence directory; actual commands/logs/hashes and PASS output. |
| invariants | Install prefix is moved; compile flags exclude producer include/build/old-stage paths; link excludes reference/testing; canonical catalog uses actual relocated CLI; exact typed JSON rows and sequence match SQLite. |
| ownership | Exclusive evidence prefix or temporary directory owns all outputs; SDK copied from current built producer; session owners erased by consumer. |
| failure | Command nonzero/timeout, install leakage, wrong account identity, result/progress mismatch fail. A single failed subprocess never produces an accepted result. |
| cost | Two consumer executions cover four arbitrary SQL streams; configure/build/install are correctness checks, not controlled benchmark timing. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 112–115](../../../../../tests/integration/installed_independent_queries.py#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L115:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke acceptance only when executed as a script. |
| inputs / outputs | Python module entry condition. |
| invariants | Importing does not launch install/build/native work. |
| ownership | main owns its scoped artifacts. |
| failure | main failures propagate to nonzero process exit. |
| cost | No cost on import beyond definitions. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |
