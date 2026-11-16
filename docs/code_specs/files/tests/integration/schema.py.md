# `tests/integration/schema.py` — block usage map

[Source](../../../../../tests/integration/schema.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `24600f171b3e04d2b5d0d4daf8704756734209a1bea3cf8677d976e1c436a810`. 187 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/integration/schema.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/integration/schema.py#L16) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/schema.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–22](../../../../../tests/integration/schema.py#L21) | Callable definition: def canonical(value: object) -&gt; str: | calls dumps; returns json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../tests/integration/schema.py#L23) | Explanatory comments or spacing. |  |
| [B0006 · 25–27](../../../../../tests/integration/schema.py#L25) | Callable definition: def digest(domain: str, value: object) -&gt; str: | calls sha256, canonical, encode, hexdigest; returns hashlib.sha256(canonical(payload).encode("utf-8")).hexdigest() · [reviewed contract](#b0006) |
| [B0007 · 28–29](../../../../../tests/integration/schema.py#L28) | Explanatory comments or spacing. |  |
| [B0008 · 30–179](../../../../../tests/integration/schema.py#L30) | Callable definition: def main() -&gt; None: | calls require, len, Path, resolve; guard require(len(sys.argv) == 3, "usage: schema.py EXECUTABLE SOURCE_ROOT"); returns result; 15 loop sites; source comment (unverified): # Raw UTF-8 is part of the specified deterministic byte encoding. · [reviewed contract](#b0008) |
| [B0009 · 180–187](../../../../../tests/integration/schema.py#L180) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–15](../../../../../tests/integration/schema.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:641b9a52c3173d694a21ae40376fe3804a3a6062eea9d26b71dfdc353a27b2cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for schema.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/integration/schema.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep schema-fixture checks active even when Python assertions are optimized away. |
| inputs / outputs | A falsey condition raises RuntimeError with the supplied diagnostic; a truthy condition returns None. |
| invariants | This is an explicit branch, not assert, so python -O does not disable the check. |
| ownership | Borrows condition/message and changes no caller container. |
| failure | Only failed conditions deliberately raise RuntimeError; construction of that exception may allocate. |
| cost | One truth test; callers compute diagnostic arguments before entry, and a failed check additionally constructs an exception. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/query_identity.md](../../../../query_identity.md) |

## B0004

[Lines 21–22](../../../../../tests/integration/schema.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(value: object) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render the deterministic JSON text used in schema equality and hashing. |
| inputs / outputs | Accepts a JSON-serializable value and returns str with sorted keys, compact separators and unescaped Unicode. |
| invariants | The result is text; digest separately UTF-8-encodes it. Python json type/number serialization is preserved. |
| ownership | Builds a fresh string without mutating or deep-copying the caller graph. |
| failure | json TypeError, ValueError or recursion errors propagate for unsupported/cyclic values. |
| cost | Traverses/materializes the complete JSON text and sorts object keys; storage grows with output length. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/query_identity.md](../../../../query_identity.md) |

## B0006

[Lines 25–27](../../../../../tests/integration/schema.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(domain: str, value: object) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an independently framed SHA-256 identity with explicit domain separation. |
| inputs / outputs | Wraps domain/version 1/value, UTF-8-encodes canonical text and returns 64 lowercase hex characters. |
| invariants | Different identity families use different domain strings; version is fixed 1 and Unicode bytes are included exactly. |
| ownership | The new envelope shares the input value while serialization reads it; returned digest is independent text. |
| failure | Serialization/encoding/hash input errors propagate; this helper neither validates native identity nor reads files. |
| cost | Allocates the envelope, full JSON string and UTF-8 bytes, then hashes every byte; key sorting and big numeric rendering add their own costs. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/query_identity.md](../../../../query_identity.md) |

## B0008

[Lines 30–179](../../../../../tests/integration/schema.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check native schema replay/migration and query identities against independently framed hashes and equivalent-query fixtures. |
| inputs / outputs | Requires EXECUTABLE and SOURCE_ROOT; runs normalization roundtrips, hostile artifacts, Unicode/zero-work identities, CQ upgrades and 24 renamed four-cycle permutations, then prints a check count. |
| invariants | Success/failure CLI channels and exit codes are checked; identity translations must be permutations, semantic payload excludes cost hints, and manual empty canonical structure is exact. |
| ownership | TemporaryDirectory owns rewritten artifacts and removes them on exit; mutated programs/CQs use deepcopy while baseline objects remain unchanged. subprocess.run owns each child and captured streams. |
| failure | require failures raise RuntimeError; JSON/file/timeout errors propagate to the script boundary, which catches RuntimeError/ValueError/OSError/TimeoutExpired and exits 1. |
| cost | Multiple 30-second-bounded child invocations, full artifact I/O/JSON/hash passes and 4! query variants dominate; no production timing is measured. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/query_identity.md](../../../../query_identity.md) |

## B0009

[Lines 180–187](../../../../../tests/integration/schema.py#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Check native schema replay/migration and query identities against independently framed hashes and equivalent-query fixtures. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only (RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/schema.py](../../../../../tests/integration/schema.py), [docs/development.md](../../../../development.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/query_identity.md](../../../../query_identity.md) |
