# `tests/integration/support.py` — block usage map

[Source](../../../../../tests/integration/support.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise support CLI diagnostics against independent manual state and transition expectations.

Snapshot SHA-256: `adbd1d6ea5955e380276a312fabf18c331a94e8e87bce92ba56e7118ea17997b`. 198 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/integration/support.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../tests/integration/support.py#L13) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../tests/integration/support.py#L16) | Explanatory comments or spacing. |  |
| [B0004 · 18–19](../../../../../tests/integration/support.py#L18) | Callable definition: def key(values: object) -&gt; str: | calls dumps; returns json.dumps(values, sort_keys=True, ensure_ascii=False, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 20–21](../../../../../tests/integration/support.py#L20) | Explanatory comments or spacing. |  |
| [B0006 · 22–32](../../../../../tests/integration/support.py#L22) | Callable definition: def memberships(state: dict) -&gt; set\[tuple\[int, str, str\]\]: | calls set, add, key, in; returns result; 5 loop sites · [reviewed contract](#b0006) |
| [B0007 · 33–34](../../../../../tests/integration/support.py#L33) | Explanatory comments or spacing. |  |
| [B0008 · 35–41](../../../../../tests/integration/support.py#L35) | Callable definition: def canonical_state(state: dict) -&gt; dict: | calls deepcopy, in, pop; returns result; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 42–43](../../../../../tests/integration/support.py#L42) | Explanatory comments or spacing. |  |
| [B0010 · 44–190](../../../../../tests/integration/support.py#L44) | Callable definition: def main() -&gt; None: | calls require, len, str, Path; guard require(len(sys.argv) == 3, "usage: support.py EXECUTABLE REPOSITORY"); returns json.loads(result.stderr); json.loads(result.stdout); growth insert; 31 loop sites · [reviewed contract](#b0010) |
| [B0011 · 191–198](../../../../../tests/integration/support.py#L191) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–12](../../../../../tests/integration/support.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:b6f5ecd5f729b8b6dd2cbcd2c0a7aa27900bd42ebb84526cc9dbe4ef8f719029
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for support.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–15](../../../../../tests/integration/support.py#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one logical support-trace acceptance predicate. |
| inputs / outputs | Returns None for truthy condition or raises RuntimeError(message). |
| invariants | Uses if, so checks stay active under -O. |
| ownership | Borrows operands and does not modify diagnostic states or files. |
| failure | False condition raises RuntimeError; predicate/truth errors propagate. |
| cost | One truth conversion excluding caller traversal/message construction. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0004

[Lines 18–19](../../../../../tests/integration/support.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(values: object) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode typed support row/key values as compact sorted JSON text for membership comparisons. |
| inputs / outputs | Accepts JSON-serializable values and returns unescaped-Unicode str. |
| invariants | Preserves array order and JSON scalar representation while sorting object keys; does not add a nonfinite-value guard. |
| ownership | New string; source container graph is borrowed without mutation or deep copy. |
| failure | JSON encoding errors/cycles/incompatible key sorting propagate. |
| cost | Traverses/encodes all values with object-key sorting and complete text allocation. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0006

[Lines 22–32](../../../../../tests/integration/support.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def memberships(state: dict) -> set[tuple[int, str, str]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract exact membership identities for support records, survivors and exposed key relations. |
| inputs / outputs | Takes state\[nodes\]; returns a set of (node id, role, encoded values) for records/survivors/parent_support/visible. None parent/visible lists count as empty. |
| invariants | Ignores handles and positive support magnitudes so callers compare zero-crossing membership events; duplicates collapse in the set rather than separate rejection. |
| ownership | Creates new tuples/set/JSON keys; borrows state and never mutates node collections. |
| failure | Missing or malformed fields and JSON serialization errors propagate. |
| cost | Full traversal of all four relations per node with complete row-key encoding; result size is distinct memberships. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0008

[Lines 35–41](../../../../../tests/integration/support.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_state(state: dict) -> dict:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove storage-specific handle fields from a copied support snapshot for FIFO/LIFO comparison. |
| inputs / outputs | Deep-copies state, then pops handle from every records/parent_keys/visible_keys item where the list is present; returns copied state. |
| invariants | Keeps list order, survivors, values, counts and all other metadata unchanged; it normalizes handles only and does not sort storage iteration order. Requires every visited item to have handle. |
| ownership | Recursive deepcopy detaches ordinary nested JSON containers; all removals affect the copy, leaving original state intact. |
| failure | Missing handle/fields raises KeyError after private partial mutation; deepcopy/type errors propagate. |
| cost | Full state deepcopy plus relation traversal/removals, with a second whole snapshot’s memory; not a shallow metadata edit. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0010

[Lines 44–190](../../../../../tests/integration/support.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare logical native-set support traces with manual states, exact membership transitions and retained propagation-journal accounting. |
| inputs / outputs | Takes CLI/repository, loads support manifest, lowers plans and runs capture-enabled FIFO traces plus capture-disabled LIFO traces; probes invalid documents/options, bounded update rejection and constant routes. |
| invariants | Checks manual records/survivors/supports/truth/no-op sequence, exact zero-crossing transitions, stable surviving key handles, journal record/event ordinals and causal IDs, and zero deprecated full-copy metrics. Rejected update final state must equal prior state. These diagnostic/logical checks do not establish file durability or every heap path. |
| ownership | TemporaryDirectory owns overwritten plan/trace files with cleanup on all exits. First trace is saved after local options mutation to LIFO/no capture; rejection probes deepcopy it. State canonicalization deep-copies snapshots; reports/handle maps remain private. |
| failure | RuntimeError, ValueError, KeyError, OSError and TimeoutExpired are caught at entrypoint for stderr exit 1; each nested CLI call has timeout 60 and exact status/channel checks. Other malformed-type errors can escape. |
| cost | Several full native traces per case plus invalid/capped/constant children; Python materializes reports, repeatedly serializes all relation keys, forms membership sets and deep-copies all snapshots for order comparison. Reported zero metrics are observed counters, not independent allocation instrumentation. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0011

[Lines 191–198](../../../../../tests/integration/support.py#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Compare logical native-set support traces with manual states, exact membership transitions and retained propagation-journal accounting. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only (RuntimeError, ValueError, KeyError, OSError, subprocess.TimeoutExpired) to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/support.py](../../../../../tests/integration/support.py), [docs/development.md](../../../../development.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |
