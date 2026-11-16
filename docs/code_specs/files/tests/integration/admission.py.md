# `tests/integration/admission.py` — block usage map

[Source](../../../../../tests/integration/admission.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7cea0eb0eced76598711b3ae2a38ef0363ce634c8b864d750c5e70d5f90b58b0`. 226 lines partitioned into 15 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/integration/admission.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/integration/admission.py#L16) | Callable definition: def require(value: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(value: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/admission.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–25](../../../../../tests/integration/admission.py#L21) | Callable definition: def invoke(executable: str, arguments: list\[str\], code: int) -&gt; dict: | calls run, require, not, in; guard require(process.returncode == code, f"{arguments\[0\]} exit {process.returncode}, expected {code}: {p…; returns json.loads(process.stdout if code in (0, 1) else process.stderr) · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../../tests/integration/admission.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–45](../../../../../tests/integration/admission.py#L28) | Callable definition: def replay(scopes: list\[set\[str\]\], reduction: dict) -&gt; None: | calls set, enumerate, require, sum; guard require(edge in remaining, "GYO witness uses removed edge"); 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 46–47](../../../../../tests/integration/admission.py#L46) | Explanatory comments or spacing. |  |
| [B0008 · 48–76](../../../../../tests/integration/admission.py#L48) | Callable definition: def validate(result: dict, expected: str) -&gt; None: | calls require, set, isinstance, len; guard require(set(result) == {"schema_version", "admission_scope", "admission_status", "phase", "executio…; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 77–78](../../../../../tests/integration/admission.py#L77) | Explanatory comments or spacing. |  |
| [B0010 · 79–106](../../../../../tests/integration/admission.py#L79) | Callable definition: def join_tree_exists(scopes: list\[set\[int\]\]) -&gt; bool: | calls len, list, combinations, range; returns True; True; 7 loop sites · [reviewed contract](#b0010) |
| [B0011 · 107–108](../../../../../tests/integration/admission.py#L107) | Explanatory comments or spacing. |  |
| [B0012 · 109–144](../../../../../tests/integration/admission.py#L109) | Callable definition: def generated_families(executable: str, temporary: Path) -&gt; int: | calls set, sorted, union, tuple; returns count; 6 loop sites · [reviewed contract](#b0012) |
| [B0013 · 145–146](../../../../../tests/integration/admission.py#L145) | Explanatory comments or spacing. |  |
| [B0014 · 147–218](../../../../../tests/integration/admission.py#L147) | Callable definition: def main() -&gt; None: | calls require, len, Path, resolve; guard require(len(sys.argv) == 3, "usage: admission.py EXECUTABLE SOURCE_ROOT"); 11 loop sites · [reviewed contract](#b0014) |
| [B0015 · 219–226](../../../../../tests/integration/admission.py#L219) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–15](../../../../../tests/integration/admission.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:753a786bdb955c1cfbc3b18e2960e92c90ff2435c92dccef66f3ad76923cb6e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for admission.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/integration/admission.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a SQL admission/witness test expectation. |
| inputs / outputs | Truth-tests value, returning None or raising RuntimeError(message). |
| invariants | Explicit if keeps checks active under -O. |
| ownership | Borrows compared fixture/report values without mutation. |
| failure | False condition becomes RuntimeError; failures computing/truth-testing it propagate. |
| cost | One truth conversion after caller work and message formatting. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 21–25](../../../../../tests/integration/admission.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(executable: str, arguments: list[str], code: int) -> dict:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one admission CLI command and decode its status-dependent JSON channel. |
| inputs / outputs | Takes executable/arguments/expected code; capture_output text timeout 30; returns json.loads(stdout) for expected codes 0/1 and stderr otherwise. |
| invariants | Requires exact exit code and empty opposite channel, but does not require decoded JSON be an object or enforce a schema in this wrapper. |
| ownership | Creates argument/result objects; subprocess.run waits and manages pipes. Parsed JSON is newly owned by caller; command arguments remain unchanged. |
| failure | Mismatch raises RuntimeError; timeout, launch and JSON decode failures propagate. Empty arguments can break diagnostic indexing. |
| cost | One native CLI child with full channel buffering and JSON parse; timeout is per call and child admission work is additional. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 28–45](../../../../../tests/integration/admission.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def replay(scopes: list[set[str]], reduction: dict) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently replay a reported GYO reduction witness and verify its residual/status. |
| inputs / outputs | Takes original list of scopes and reduction with witness,failed_core,acyclic; returns None after simulating removals in a fresh indexed scope map. |
| invariants | Each private variable must occur in exactly one remaining edge; containment needs distinct live anchor/superset; empty removal needs an empty scope. Final residual map must equal failed_core and acyclic must equal emptiness. It checks the supplied witness, not completeness of a search. |
| ownership | Copies every input scope into a new set and mutates only that private map; reduction objects are read. Failed-core scopes are copied for comparison. |
| failure | RuntimeError on invalid witness/status; missing/type fields can raise KeyError/TypeError. Failed-core duplicate edge IDs collapse in its dict comprehension rather than separate duplicate detection. |
| cost | Copies all scopes then for every private-variable step scans all remaining scopes; containment and final-set comparisons depend on scope sizes. No native calls or file I/O. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 48–76](../../../../../tests/integration/admission.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate(result: dict, expected: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admission-envelope scope and independently replay structural classification evidence. |
| inputs / outputs | Accepts result/expected status; returns None after exact envelope-key checks, route/diagnostic checks, normalized occurrence census and body/augmented GYO replay when present. |
| invariants | Requires frontend_and_structure, execution not_lowered and height not_checked; class derives from body and synthetic-head reductions. Free-connex route needs noncontradiction; constant_empty needs contradiction; resource_limit must expose no partial structure. No runtime lowering/height optimality is claimed. |
| ownership | Reads report and creates new scope/head sets; replay copies its own working sets. Does not mutate program/result. |
| failure | RuntimeError for checked mismatches; malformed nested report can raise lookup/type errors rather than a translated diagnostic. |
| cost | Traverses normalized atoms/head and replays both reduction witnesses; cost includes repeated scope scans in replay, not a constant schema check. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 79–106](../../../../../tests/integration/admission.py#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def join_tree_exists(scopes: list[set[int]]) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide tiny scope-family join-tree existence by literal spanning-tree enumeration and running intersection. |
| inputs / outputs | Takes list of scope sets; returns True for fewer than 2 scopes, otherwise tries all n-1-edge subsets of the complete graph and returns whether one is connected with each variable’s occurrence nodes connected. |
| invariants | Uses no GYO algorithm/output as ground truth; connected n-node n-1-edge graphs are trees. Empty variable occurrence sets are trivially reachable. |
| ownership | Creates complete edge list and per-candidate adjacency/reachability containers; borrows scopes without mutating them. |
| failure | Invalid scope/node contents may raise normal set/iteration errors; resource exhaustion propagates. No explicit search budget is applied. |
| cost | Combinatorial choose(n*(n-1)/2,n-1) candidates; each runs graph reachability and per-variable incidence/reachability scans. Intended only for the fixed small generated families. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0012

[Lines 109–144](../../../../../tests/integration/admission.py#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def generated_families(executable: str, temporary: Path) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate finite body/head SQL families and compare admission classes with an independent literal join-tree test. |
| inputs / outputs | Takes CLI and an existing temporary directory; overwrites query.sql/catalog.json for each distinct head of 16 fixed bodies, invokes admit-sql, validates result and returns case count. |
| invariants | Creates equalities tying repeated variables, supports empty/disconnected/duplicate scopes and existential empty heads; expected cyclic_body/non_free_connex/admitted comes from join_tree_exists on body/augmented head. Does not execute generated SQL rows. |
| ownership | Owns generated schema/reference/condition containers and files; borrows directory lifetime from caller, with no local cleanup or rollback of partially written files. |
| failure | File/JSON/CLI errors propagate; RuntimeError on status/evidence mismatch. Each invoke enforces its own 30-second timeout. |
| cost | For every finite body/head recomputes combinatorial join-tree existence, writes two complete files and launches one CLI; total cost includes search plus native parsing/recognition. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 147–218](../../../../../tests/integration/admission.py#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the finite SQL admission matrix, independent structural families and selected manual/SQLite row semantics. |
| inputs / outputs | Takes executable/source root; loads manifest/catalog/data, checks admission status/code/phase/route and Unicode coordinates, reimports normalized programs, compares expected rows via adapters/core oracle and optional SQLite, and probes usage/options/schema upgrades. |
| invariants | Requires exact feature/status coverage and source/artifact structural equality; frozen normalized v1 upgrades to 2 but downgrade/future forms reject. This verifies declared frontend/structural admission and selected rows, not actual physical/runtime durability. |
| ownership | TemporaryDirectory encloses overwritten program/options/generated files and cleans on all exits. Fixture data/manifest are read; local sets/counts accumulate; delegated adapters/oracles own their copies/children/SQL connections. |
| failure | RuntimeError, ValueError, OSError and TimeoutExpired are caught at entrypoint for stderr exit 1; malformed nested lookup/type errors can remain uncaught. Rejected CLI cases require exact 2/channel semantics through invoke. |
| cost | Many CLI normalizations/admissions/reimports plus generated combinatorial join-tree searches; selected cases also perform full core joins and SQLite queries. Loads all fixture data, materializes outputs and serializes temporary programs. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0015

[Lines 219–226](../../../../../tests/integration/admission.py#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Verify the finite SQL admission matrix, independent structural families and selected manual/SQLite row semantics. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only (RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/development.md](../../../../development.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
