# `tests/integration/weighted_messages.py` — block usage map

[Source](../../../../../tests/integration/weighted_messages.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4194e57fce84e2628f5789a0e23fd3b279d61c61b542bd34bf4330a7174bf0b4`. 129 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/weighted_messages.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–26](../../../../../tests/integration/weighted_messages.py#L21) | Callable definition: def canonical(actual): | calls dumps; returns actual\['root_count'\], rows, messages; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 27–28](../../../../../tests/integration/weighted_messages.py#L27) | Explanatory comments or spacing. |  |
| [B0004 · 29–34](../../../../../tests/integration/weighted_messages.py#L29) | Callable definition: def expected_state(result): | calls dumps, int; returns result\['root_count'\], rows, messages; 4 loop sites · [reviewed contract](#b0004) |
| [B0005 · 35–36](../../../../../tests/integration/weighted_messages.py#L35) | Explanatory comments or spacing. |  |
| [B0006 · 37–76](../../../../../tests/integration/weighted_messages.py#L37) | Callable definition: def check_case(driver, fixture, updates, indexed, limit=(1 &lt;&lt; 64)-1): | calls dict, str, run, dumps; returns len(updates); 11 loop sites · [reviewed contract](#b0006) |
| [B0007 · 77–78](../../../../../tests/integration/weighted_messages.py#L77) | Explanatory comments or spacing. |  |
| [B0008 · 79–104](../../../../../tests/integration/weighted_messages.py#L79) | Callable definition: def updates_for(fixture, count): | calls Random, range, choice, randrange; returns result; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 105–106](../../../../../tests/integration/weighted_messages.py#L105) | Explanatory comments or spacing. |  |
| [B0010 · 107–125](../../../../../tests/integration/weighted_messages.py#L107) | Callable definition: def main(): | calls in, check_case, updates_for, dict; 2 loop sites; source comment (unverified): # Exceed both binary64 precision and the declared u64 domain; the · [reviewed contract](#b0010) |
| [B0011 · 126–129](../../../../../tests/integration/weighted_messages.py#L126) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–20](../../../../../tests/integration/weighted_messages.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
spec.loader.exec_module(oracle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the independent weighted reference module before the W02 integration driver runs. |
| inputs / outputs | Resolves the repository root from __file__, creates a spec for tests/reference/weighted_oracle.py, creates a module object, and executes its module body with exec_module. |
| invariants | The outer integration script’s __main__ guard controls its test driver; exec_module loads the reference module under the name weighted_oracle, so that reference file’s own guarded main is not invoked. |
| ownership | The imported module namespace is retained in global oracle; Python owns its definitions/data for this process. |
| failure | Path/spec/compile/exec errors propagate; no exception translation or unload occurs. |
| cost | Loads/compiles and initializes the Python reference module. Import machinery can read/write bytecode caches; no CROWN child or explicit fixture write is requested here. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), CMakeLists.txt:963,966, tests/integration/weighted_messages.py:1-20 |

## B0002

[Lines 21–26](../../../../../tests/integration/weighted_messages.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(actual):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove runtime storage iteration order from a weighted snapshot comparison. |
| inputs / outputs | Takes actual nodes/messages/root_count and returns root count, node-row mapping and message mapping; each node row key is JSON text. |
| invariants | Retains local/subtree/children/supported values exactly and keeps typed JSON row/key spellings. Duplicate node/row/message keys overwrite rather than being independently rejected. |
| ownership | Creates outer dictionaries/tuples/JSON keys; row children objects and other count values are shared references from actual. No deep copy or mutation. |
| failure | Missing fields/JSON encoding errors propagate; this helper does not schema-check or normalize count strings. |
| cost | Traverses and serializes every row/key; new maps use O(number of rows/messages+encoded keys) storage. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |

## B0004

[Lines 29–34](../../../../../tests/integration/weighted_messages.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected_state(result):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt independent oracle snapshot fields to the runtime snapshot comparison shape. |
| inputs / outputs | Takes result with cached_child_messages and supported_count; returns root count plus node-row/message mappings matching canonical. |
| invariants | Preserves local/subtree count text and child order, extracts child.value and converts supported_count to int; duplicate keys collapse in dictionary comprehensions. |
| ownership | New maps/tuples/child-value lists are allocated; their scalar/count values are shared references. Source oracle result is not changed. |
| failure | Missing/malformed fields, invalid int conversion or JSON serialization errors propagate. |
| cost | Full traversal and row/key serialization plus one child list per row; costs scale with snapshot/message/child-cache size. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |

## B0006

[Lines 37–76](../../../../../tests/integration/weighted_messages.py#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_case(driver, fixture, updates, indexed, limit=(1 << 64)-1):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate every weighted-driver snapshot against an unbounded full-assignment oracle with conflict and overflow rollback. |
| inputs / outputs | Runs one driver with fixture/updates/backend/decimal limit; parses shape and one line per update, computes expected snapshot and returns number of updates. |
| invariants | Uses exact before matching; tentative weights are restored if any root/local/subtree/message count exceeds limit; sequence advances only for success and entire canonical state must match. All semantic comparisons use assert and require assertions enabled. |
| ownership | Mutates only private per-node tuple-weight maps, rebuilding new oracle inputs each step and after rollback. Caller update row lists are converted to tuple keys. Driver process buffers/pipes are owned/waited by subprocess.run. |
| failure | CalledProcessError on nonzero child; no timeout or stderr-empty check is present. Malformed output/oracle errors propagate; mismatches raise AssertionError. |
| cost | One full child trace plus a complete unbounded join-oracle evaluation per step and an additional evaluation after overflow; snapshot/JSON materialization and big-int products can dominate or grow combinatorially. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |

## B0008

[Lines 79–104](../../../../../tests/integration/weighted_messages.py#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def updates_for(fixture, count):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate deterministic fixture-shaped weighted replacements and matching generated before weights. |
| inputs / outputs | Takes fixture,count; uses seed 720200+count and returns update dictionaries with row lists and decimal before/after values. |
| invariants | Private current map tracks all generated replacements; it does not model later native rejection. generalized/fanout use explicit node shapes, all other names use the default three-node path. |
| ownership | New RNG/map/list/dictionaries own the trace; row lists are retained directly in updates and tuple keys copy their scalar sequence. No caller mutation. |
| failure | Invalid count/types can raise; a negative integer count yields an empty list. Fixture validity is not checked. |
| cost | Linear in generated count with bounded random draws, map operations and small decimal strings; retains trace and distinct tuple weights. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |

## B0010

[Lines 107–125](../../../../../tests/integration/weighted_messages.py#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run finite randomized and overflow/conflict snapshot regressions on ordered and indexed native backends. |
| inputs / outputs | Reads driver from argv\[1\]; runs path/generalized/fanout 250-update traces and unary/nullary edges, totals checked updates and prints success. |
| invariants | Exercises exact counts beyond binary64 precision, u64-bound overflow, rollback/retry and conflicting before weights against a nonincremental oracle. It is a semantic regression rather than a performance benchmark. |
| ownership | Owns local request lists; global oracle module is loaded before main. Does not mutate repository fixtures or create output files. |
| failure | Missing argv, driver/JSON/oracle errors and assertion mismatches propagate uncaught; -O removes the check_case assertions. |
| cost | Several full driver traces plus fresh full-assignment joins and full snapshot comparison after each update on both backends; no bounded-machine arithmetic cost is assumed for Python oracle counts. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |

## B0011

[Lines 126–129](../../../../../tests/integration/weighted_messages.py#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run finite randomized and overflow/conflict snapshot regressions on ordered and indexed native backends. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [docs/development.md](../../../../development.md), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py) |
