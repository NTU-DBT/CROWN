# `tests/integration/weighted_bag.py` — block usage map

[Source](../../../../../tests/integration/weighted_bag.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6910997ad1f003ddb46f4bd77703d1d657955b4e62b7a295c0543239edc68461`. 137 lines partitioned into 15 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/integration/weighted_bag.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–22](../../../../../tests/integration/weighted_bag.py#L18) | Callable definition: def load(name): | calls spec_from_file_location, module_from_spec, exec_module; returns module · [reviewed contract](#b0002) |
| [B0003 · 23–28](../../../../../tests/integration/weighted_bag.py#L23) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 29–32](../../../../../tests/integration/weighted_bag.py#L29) | Callable definition: def normalize(rows): | calls dumps, len; returns result; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 33–34](../../../../../tests/integration/weighted_bag.py#L33) | Explanatory comments or spacing. |  |
| [B0006 · 35–48](../../../../../tests/integration/weighted_bag.py#L35) | Callable definition: def payload(description,inputs): | calls items, loads, extend, dict; returns dict(description,inputs=tables); 2 loop sites; source comment (unverified): # Explicit duplicates in the independent oracle: representation · [reviewed contract](#b0006) |
| [B0007 · 49–50](../../../../../tests/integration/weighted_bag.py#L49) | Explanatory comments or spacing. |  |
| [B0008 · 51–84](../../../../../tests/integration/weighted_bag.py#L51) | Callable definition: def check_case(driver,fixture,indexed,updates,limit=(1&lt;&lt;64)-1): | calls dict, str, run, dumps; returns len(updates)+1; 7 loop sites · [reviewed contract](#b0008) |
| [B0009 · 85–86](../../../../../tests/integration/weighted_bag.py#L85) | Explanatory comments or spacing. |  |
| [B0010 · 87–105](../../../../../tests/integration/weighted_bag.py#L87) | Callable definition: def random_updates(fixture,count): | calls Random, range, choice, randrange; returns result; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 106–107](../../../../../tests/integration/weighted_bag.py#L106) | Explanatory comments or spacing. |  |
| [B0012 · 108–109](../../../../../tests/integration/weighted_bag.py#L108) | Callable definition: def update(node,row,before,after): | calls dict, str; returns dict(node=node,row=row,before=str(before),after=str(after)) · [reviewed contract](#b0012) |
| [B0013 · 110–111](../../../../../tests/integration/weighted_bag.py#L110) | Explanatory comments or spacing. |  |
| [B0014 · 112–133](../../../../../tests/integration/weighted_bag.py#L112) | Callable definition: def main(): | calls in, check_case, random_updates, update; 4 loop sites · [reviewed contract](#b0014) |
| [B0015 · 134–137](../../../../../tests/integration/weighted_bag.py#L134) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–17](../../../../../tests/integration/weighted_bag.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ROOT=pathlib.Path(__file__).resolve().parents[2]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the repository root used by the W03 bag-oracle loader. |
| inputs / outputs | Derives ROOT from this script’s path; it is later used by load() to find tests/reference modules. |
| invariants | Path is anchored to __file__, not the process working directory; this assignment does not run the oracle main routines. |
| ownership | The Python module owns one Path value; no native state or file handle is retained. |
| failure | Path resolution errors propagate during script import; no local catch. |
| cost | Module imports and a source-relative path calculation; no explicit test, subprocess or fixture-write call in this block. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), CMakeLists.txt:968, tests/integration/weighted_bag.py:1-17 |

## B0002

[Lines 18–22](../../../../../tests/integration/weighted_bag.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load(name):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load an independent reference oracle Python module from the repository by explicit file path. |
| inputs / outputs | Takes module base name and returns the module created from tests/reference/&lt;name&gt;.py under ROOT. |
| invariants | Uses spec_from_file_location plus exec_module, so loading executes module top-level code; it does not resolve through the normal import cache or validate name as a safe external path. Names are fixed internal callers. |
| ownership | Creates a fresh module object; caller retains it and its globals. The loader may read source/create bytecode according to Python settings. |
| failure | Missing/invalid files, loader/spec failures and module execution exceptions propagate; no fallback oracle is used. |
| cost | Module read/compile/execute and allocations, rather than a constant-time reference lookup. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0003

[Lines 23–28](../../../../../tests/integration/weighted_bag.py#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
subtree=load('weighted_oracle')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the two independent W03 oracle modules into this integration process. |
| inputs / outputs | Calls load() for weighted_bag_oracle and weighted_oracle; stores returned module objects in bag and subtree globals. |
| invariants | These are source modules loaded under their oracle names; importing/running this outer module executes both loads, while the referenced modules’ guarded CLI mains are not called by exec_module. |
| ownership | The Python process retains both module namespaces until exit; it owns no native runtime state here. |
| failure | Source lookup/compile/import errors propagate; partial first-module load remains in process if the second load fails. |
| cost | Reads and initializes two Python modules once; the native driver is only invoked by later test code. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), CMakeLists.txt:968, tests/integration/weighted_bag.py:23-28 |

## B0004

[Lines 29–32](../../../../../tests/integration/weighted_bag.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def normalize(rows):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare projected bag cursor rows independently of storage iteration order. |
| inputs / outputs | Accepts rows with row and count; returns mapping from compact JSON row text to the supplied count values. |
| invariants | Asserts mapping length equals input length to reject duplicate projected rows; counts are not normalized/parsed and Python -O disables duplicate detection. |
| ownership | New dictionary/string keys are created; count objects are shared references from row entries and no input row is changed. |
| failure | Missing fields/JSON serialization errors propagate; duplicate rows raise AssertionError only with assertions enabled. |
| cost | Serializes every projected row and retains all encoded keys/count references; O(total row encoding) plus average dictionary work. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0006

[Lines 35–48](../../../../../tests/integration/weighted_bag.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def payload(description,inputs):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand logical native weights into an independently represented bag-oracle input. |
| inputs / outputs | Takes description and per-table mapping of encoded row to integer weight; returns shallow dict(description,inputs=new tables). A weight&gt;1 is split into two entries of weights 1 and weight-1. |
| invariants | The two duplicate entries sum exactly to the logical weight; zero/nonpositive weights take the one-entry branch and are not filtered here. Relies on oracle validation for accepted weights. |
| ownership | Copies only the description dictionary shell; other metadata values are shared. Each encoded row is decoded freshly, and split entries share that same row list with each other. |
| failure | json.loads/type/arithmetic/conversion errors propagate; malformed description is not validated here. |
| cost | Visits all logical rows, decodes each row text and formats exact weights; adds at most two entries per logical row, not weight-many rows. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0008

[Lines 51–84](../../../../../tests/integration/weighted_bag.py#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_case(driver,fixture,indexed,updates,limit=(1<<64)-1):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one projected weighted driver trace with full-join oracle states and explicit conflict/overflow rollback. |
| inputs / outputs | Runs driver with fixture/indexed/updates/decimal limit JSON, reads description and initial rows then one result per update; returns len(updates)+1 states. |
| invariants | Checks before-weight conflicts, all relevant local/subtree/message/root counts and proposed after against limit, restores local proposed inputs on overflow, advances sequence only on success, and compares projected rows/total_count/record count. Checks use assert and are disabled by -O. |
| ownership | Owns the decoded driver output and local per-node weight maps; update/fixture arguments are read. Proposed payloads/oracle states are rematerialized each step; subtree and bag oracles receive fresh input representations. subprocess.run waits/closes pipes. |
| failure | Nonzero child raises CalledProcessError; no timeout is supplied. Malformed JSON/output shape raises normally; semantic mismatches raise AssertionError. No stderr-empty requirement is enforced. |
| cost | One driver child and full buffering, then repeated complete unbounded subtree and bag joins per update (including a new post-rollback bag evaluation); work can grow combinatorially with join assignments and integer sizes. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0010

[Lines 87–105](../../../../../tests/integration/weighted_bag.py#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def random_updates(fixture,count):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a reproducible fixture-shaped weighted replacement trace. |
| inputs / outputs | Takes fixture name/count; returns count update dicts with node, newly built row, and decimal before/after strings, seeded by 730300+count. |
| invariants | Maintains an internal weight map so generated before equals the preceding generated after; this is generation history, not a model of runtime overflow rejection. Unrecognized fixture names use path-like shape. |
| ownership | Owns RNG, current-weight map and result containers; each row list is retained in its update, while tuple copies are keys. No caller state changes. |
| failure | Invalid count/type can raise; negative integer count returns an empty trace. It does not query driver schema or validate fixture spelling. |
| cost | O(count) bounded-range RNG/dictionary work with O(distinct generated tuples+count) retained state; weight strings are small in these generated domains. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0012

[Lines 108–109](../../../../../tests/integration/weighted_bag.py#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def update(node,row,before,after):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one exact weighted replacement request without validating it. |
| inputs / outputs | Takes node,row,before,after and returns dict with before/after converted to str. |
| invariants | Preserves node/row exactly; allows intentionally conflicting/large values needed by tests. |
| ownership | New dictionary owns references to node and caller row; row is shared, not copied. before/after strings are freshly converted or reused by str. |
| failure | str conversion can raise for unusual inputs; no range/schema/weight-conflict checks occur here. |
| cost | Constant-size dictionary allocation plus decimal rendering proportional to input digit count. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0014

[Lines 112–133](../../../../../tests/integration/weighted_bag.py#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise projected bag semantics across both storage backends and a finite randomized/edge-case matrix. |
| inputs / outputs | Reads driver from argv\[1\]; runs six 220-update families plus counted/unary/overflow/boolean/nullary/true/false and deep-hidden traces, accumulates checked state counts and prints success. |
| invariants | Uses the independent bag/subtree oracles through check_case, including &gt;2**53/u64 edges, conflict retry and a 96-node hidden tail; this tests logical weighted enumeration, not physical bag routing or SQL normalization. |
| ownership | Builds local update lists and passes them read-only to check_case; independent oracle modules are loaded globally before main. No temporary files are created here. |
| failure | Missing argv, child/oracle/JSON failures or AssertionError propagate uncaught at entrypoint. Assertions throughout must be enabled for semantic acceptance. |
| cost | Multiple complete driver replays and full unbounded joins after every update on both backends; output and oracle materialization dominate the finite trace construction. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |

## B0015

[Lines 134–137](../../../../../tests/integration/weighted_bag.py#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Exercise projected bag semantics across both storage backends and a finite randomized/edge-case matrix. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/development.md](../../../../development.md), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py) |
