# `tests/integration/physical.py` — block usage map

[Source](../../../../../tests/integration/physical.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d7f6cf1bef29d577801e7f1bd77cb9239509952e5354423ace9b312b98bb903e`. 162 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/integration/physical.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/integration/physical.py#L14) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../tests/integration/physical.py#L17) | Explanatory comments or spacing. |  |
| [B0004 · 19–20](../../../../../tests/integration/physical.py#L19) | Callable definition: def canonical(value: object) -&gt; bytes: | calls dumps, encode; returns json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False).encode() · [reviewed contract](#b0004) |
| [B0005 · 21–22](../../../../../tests/integration/physical.py#L21) | Explanatory comments or spacing. |  |
| [B0006 · 23–154](../../../../../tests/integration/physical.py#L23) | Callable definition: def main() -&gt; None: | calls require, len, str, Path; guard require(len(sys.argv) == 3, "usage: physical.py EXECUTABLE REPOSITORY"); returns json.loads(result.stderr); json.loads(result.stdout); 8 loop sites; source comment (unverified): # Initial physical data and update events are outside a compilation · [reviewed contract](#b0006) |
| [B0007 · 155–162](../../../../../tests/integration/physical.py#L155) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–13](../../../../../tests/integration/physical.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:21bccc91ab6e9794580b3322775947ca2be3852708ac315193b38ca71765b5af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for physical.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/physical.py](../../../../../tests/integration/physical.py), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/integration/physical.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a physical lowering/replay test mismatch. |
| inputs / outputs | Truth-tests condition and returns None or raises RuntimeError(message). |
| invariants | Explicit runtime if is unaffected by Python assertion optimization. |
| ownership | Borrows operands, leaving artifacts/files unchanged. |
| failure | RuntimeError for false condition; operand evaluation errors propagate. |
| cost | One truth test after caller comparison/hash work. |
| Design | [tests/integration/physical.py](../../../../../tests/integration/physical.py), [docs/physical_plans.md](../../../../physical_plans.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0004

[Lines 19–20](../../../../../tests/integration/physical.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(value: object) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the exact compact JSON bytes used for independent physical identity hashing. |
| inputs / outputs | Serializes value with sorted keys, compact separators and unescaped Unicode, then default UTF-8 encode(); returns bytes. |
| invariants | Sorts dictionaries but preserves array order and scalar representation; default json nonfinite handling is not tightened. Hash callers supply valid artifacts. |
| ownership | Allocates full intermediate str and full bytes, without mutating value or copying its container graph. |
| failure | JSON serialization and Unicode encoding failures propagate. |
| cost | Full traversal/object-key sorting plus UTF-8 pass; intermediate text and final bytes can overlap in memory. |
| Design | [tests/integration/physical.py](../../../../../tests/integration/physical.py), [docs/physical_plans.md](../../../../physical_plans.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0006

[Lines 23–154](../../../../../tests/integration/physical.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept physical lowering artifacts by independent binding hashes, replay equality and hostile metadata/budget probes. |
| inputs / outputs | Takes CLI/repository paths; checks structural lowering matrix, validates/canonicalizes artifacts, mutates five fields/version/duplicate JSON keys, probes work/identity/policy caps and data-independent compilation, then lowers normalized SQL programs with constructed trees. |
| invariants | Independently hashes source/tree/order/lowerer envelope and checks layout binding; requires valid_upper_bound and lowered_not_started with runtime bounds explicitly unimplemented. Candidate tree-oracle output is construction input, while manual structure/execution are separate tests. No runtime execution or optimum-height proof is inferred here. |
| ownership | TemporaryDirectory owns artifacts/options/core/tree/query files and cleans on all exits; mutations use deepcopy so first artifact/source remain available. Nested invoke buffers child output and counts checked calls. |
| failure | RuntimeError, ValueError, OSError, KeyError and TimeoutExpired reach the entrypoint stderr/exit 1 handler; child status/channel/code checks are explicit with timeout 60 per invocation. Other type errors can remain uncaught. |
| cost | Multiple native lower/validate/canonicalize/normalize/tree-oracle children per fixture plus complete artifact serialization/hash/deepcopy. Stores first artifact and full case outputs; repeated normalization/lowering is genuine cold work, not cheap metadata lookup. |
| Design | [tests/integration/physical.py](../../../../../tests/integration/physical.py), [docs/physical_plans.md](../../../../physical_plans.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0007

[Lines 155–162](../../../../../tests/integration/physical.py#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Accept physical lowering artifacts by independent binding hashes, replay equality and hostile metadata/budget probes. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only (RuntimeError, ValueError, OSError, KeyError, subprocess.TimeoutExpired) to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/physical.py](../../../../../tests/integration/physical.py), [docs/development.md](../../../../development.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
