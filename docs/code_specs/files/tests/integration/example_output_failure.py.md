# `tests/integration/example_output_failure.py` — block usage map

[Source](../../../../../tests/integration/example_output_failure.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a8e42d840eab1224ffd93779b650edc9168300e343fcdb72b5056505bb3e1e8d`. 196 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/integration/example_output_failure.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../tests/integration/example_output_failure.py#L20) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../tests/integration/example_output_failure.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–26](../../../../../tests/integration/example_output_failure.py#L25) | Callable definition: def encoded(value): | calls dumps; returns json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../../tests/integration/example_output_failure.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–43](../../../../../tests/integration/example_output_failure.py#L29) | Callable definition: def run(command, fail_output=False): | calls str, open, require; guard require(result.returncode == 1,; returns None; result.stdout; 1 loop sites; source comment (unverified): # The existing stream-state exit is silent. A domain/input failure must · [reviewed contract](#b0006) |
| [B0007 · 44–45](../../../../../tests/integration/example_output_failure.py#L44) | Explanatory comments or spacing. |  |
| [B0008 · 46–47](../../../../../tests/integration/example_output_failure.py#L46) | Callable definition: def report(command): | calls loads, run; returns json.loads(run(command)) · [reviewed contract](#b0008) |
| [B0009 · 48–49](../../../../../tests/integration/example_output_failure.py#L48) | Explanatory comments or spacing. |  |
| [B0010 · 50–188](../../../../../tests/integration/example_output_failure.py#L50) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard require(error.errno == errno.ENOSPC, "failing device did not report ENOSPC"); returns 77; \[args.native_workflow, action, query, catalog, updates,; 5 loop sites; source comment (unverified): # A failed report is not a rollback of the two already committed epochs. · [reviewed contract](#b0010) |
| [B0011 · 189–196](../../../../../tests/integration/example_output_failure.py#L189) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–19](../../../../../tests/integration/example_output_failure.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:7dd8ad52195d5d8a8632f7359ae864353f951bdda5fc39ac0bb618669f4cf3f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import example output regression dependencies and state ENOSPC scope. |
| inputs / outputs | Stdlib process/file/hash/JSON/install-client helpers become available. |
| invariants | A functioning /dev/full and actual current example binaries are required; absence is explicit skip77. |
| ownership | Imports retain module objects only; main owns temporary builds and durable fixtures. |
| failure | Import failures propagate before any example execution. |
| cost | Import setup only. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py), [docs/native_build.md](../../../../native_build.md) |

## B0002

[Lines 20–22](../../../../../tests/integration/example_output_failure.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:8b14f7d5eb0d9a9cafc6d1aaa990a73bad9c261d2c3c97d6713ed7fa789c829b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail the output regression on an unmet observed property. |
| inputs / outputs | Boolean and diagnostic message in; normal return or RuntimeError out. |
| invariants | Uses explicit condition checks even when Python assertions are disabled. |
| ownership | Owns no query or fixture. |
| failure | Raises directly, without retry or continued execution. |
| cost | Fixed condition evaluation plus caller-supplied message. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py) |

## B0004

[Lines 25–26](../../../../../tests/integration/example_output_failure.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:d48a47f8620b9f74e812f513bf5b84433fad7f45523eb24b1af5adab927f3fb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode deterministic test request/catalog/event JSON. |
| inputs / outputs | Python value in; sorted compact ensure_ascii=False JSON string out. |
| invariants | Determinism is for fixture hashing, not native proof authority. |
| ownership | Return owns encoded text. |
| failure | Serialization/type/encoding/allocation errors propagate. |
| cost | Linear encoded value traversal and output allocation. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py), [docs/cli.md](../../../../cli.md) |

## B0006

[Lines 29–43](../../../../../tests/integration/example_output_failure.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L43:sha256:37dca8153407a7e1ea1550568a53b65c762fceaee0c1e1f443f6e61cfb5becf7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an actual example against normal output or real ENOSPC. |
| inputs / outputs | Command sequence and failure-output selector in; normal stdout bytes or None out. Each child has240-second timeout. |
| invariants | Failure branch redirects unbuffered stdout to /dev/full and requires silent exit1; stderr would expose an upstream domain failure rather than the intended final report failure. Normal branch requires exit0. |
| ownership | Context-managed device descriptor closes after child; Python owns argument strings and captured byte streams. |
| failure | Launch/timeout/open failures and wrong exit/stderr properties propagate to the top-level test failure. |
| cost | One real child; normal capture allocates stdout/stderr, failing branch captures stderr and discards device output. This is a test, not runtime buffering machinery. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp) |

## B0008

[Lines 46–47](../../../../../tests/integration/example_output_failure.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:0f6d52af266c554c544cf6b811e02bc503e6359272549c8cbebd9fb9c7afce0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a successful example report as JSON. |
| inputs / outputs | Command in; run its normal control and parse returned stdout bytes. |
| invariants | JSON parsing follows successful exit; no error output becomes a report. |
| ownership | Returned Python DOM owns report values. |
| failure | Child/JSON errors propagate. |
| cost | One child plus complete report parse/allocation. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py) |

## B0010

[Lines 50–188](../../../../../tests/integration/example_output_failure.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L188:sha256:3cdb4f5b441198b8473c292ad691d745580cc5e41b8e2d3f6ff06afb46620073
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate all five examples and durable continuity after report failure. |
| inputs / outputs | Parse current binaries/build/compiler/sanitizer options; verify actual /dev/full ENOSPC; stage/move one SDK and build missing native/reoptimization consumers, then run controls and seven real failing reports. |
| invariants | Short collector verify and reoptimization reports force buffered-error coverage. Native workflow and both reoptimization backends must restore/resume already committed state/source/sink progress after exit1. No source or historical evidence is mutated; sanitizer consumers retain the requested instrumentation. |
| ownership | TemporaryDirectory owns staged SDK, two consumer trees, requests/input and durable run directories; built executable paths borrow that scope. |
| failure | Missing /dev/full returns77. Every unexpected child result, ENOSPC code, state/row/progress mismatch or install/build/parse failure aborts; it never promotes a domain failure to a passing report test. |
| cost | One SDK install/move, up to two Release standalone builds with parallel2, finite actual example/control/recovery runs and full reports. No native update overhead; environmental/test setup cost is explicit. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [docs/native_build.md](../../../../native_build.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0011

[Lines 189–196](../../../../../tests/integration/example_output_failure.py#L189); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L189-L196:sha256:9c96421186d57b011a5936b0ec8f55630ebcb8f06751e2e42dccba2777609b95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate the regression process result once at the outer CLI boundary. |
| inputs / outputs | Main guard exits with main status; uncaught Exception emits one stderr diagnostic and exits1. |
| invariants | SystemExit77 is not caught as Exception, preserving CTest environmental skip; no inner recovery or retry is added. |
| ownership | Process scope; main temporary contexts unwind before exit. |
| failure | One outer test-process diagnostic boundary. |
| cost | Fixed dispatch and failure-message output. |
| Design | [tests/integration/example_output_failure.py](../../../../../tests/integration/example_output_failure.py), [CMakeLists.txt](../../../../../CMakeLists.txt) |
