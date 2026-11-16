# `tests/integration/validate_plans.py` — block usage map

[Source](../../../../../tests/integration/validate_plans.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `725e59d9bc7d81cd9a8300089a9d284d36f461d6bf3e9e16a8223a09684892a6`. 250 lines partitioned into 17 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/integration/validate_plans.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–17](../../../../../tests/integration/validate_plans.py#L14) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Keep checks active when this script is invoked with \`\`python -O\`\`. · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../tests/integration/validate_plans.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–24](../../../../../tests/integration/validate_plans.py#L20) | Callable definition: def load_json(path: Path) -&gt; Any: | calls loads, read_text, except, RuntimeError; returns json.loads(path.read_text(encoding="utf-8")) · [reviewed contract](#b0004) |
| [B0005 · 25–26](../../../../../tests/integration/validate_plans.py#L25) | Explanatory comments or spacing. |  |
| [B0006 · 27–28](../../../../../tests/integration/validate_plans.py#L27) | Callable definition: def is_integer(value: Any) -&gt; bool: | calls isinstance; returns isinstance(value, int) and not isinstance(value, bool) · [reviewed contract](#b0006) |
| [B0007 · 29–30](../../../../../tests/integration/validate_plans.py#L29) | Explanatory comments or spacing. |  |
| [B0008 · 31–38](../../../../../tests/integration/validate_plans.py#L31) | Callable definition: def run_cli(executable: str, query: Path, plan: Path) -&gt; subprocess.CompletedProcess\[str\]: | calls run, str; returns subprocess.run( · [reviewed contract](#b0008) |
| [B0009 · 39–40](../../../../../tests/integration/validate_plans.py#L39) | Explanatory comments or spacing. |  |
| [B0010 · 41–103](../../../../../tests/integration/validate_plans.py#L41) | Callable definition: def parse_result(case_name: str, process: subprocess.CompletedProcess\[str\]) -&gt; dict\[str, Any\]: | calls loads, RuntimeError, require, isinstance; guard require(isinstance(result, dict), f"{case_name}: result must be a JSON object"); returns result; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 104–105](../../../../../tests/integration/validate_plans.py#L104) | Explanatory comments or spacing. |  |
| [B0012 · 106–196](../../../../../tests/integration/validate_plans.py#L106) | Callable definition: def check_case(executable: str, fixture_dir: Path, case: Any) -&gt; None: | calls require, isinstance, get, is_file; guard require(isinstance(case, dict), "manifest case must be an object"); 10 loop sites · [reviewed contract](#b0012) |
| [B0013 · 197–198](../../../../../tests/integration/validate_plans.py#L197) | Explanatory comments or spacing. |  |
| [B0014 · 199–219](../../../../../tests/integration/validate_plans.py#L199) | Callable definition: def check_malformed_input(executable: str, fixture_dir: Path, case: Any) -&gt; None: | calls TemporaryDirectory, Path, write_text, run_cli; guard require( · [reviewed contract](#b0014) |
| [B0015 · 220–221](../../../../../tests/integration/validate_plans.py#L220) | Explanatory comments or spacing. |  |
| [B0016 · 222–242](../../../../../tests/integration/validate_plans.py#L222) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, Path, load_json; guard require(isinstance(manifest, dict), f"{manifest_path}: manifest must be an object"); returns 0; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 243–250](../../../../../tests/integration/validate_plans.py#L243) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |

## B0001

[Lines 1–13](../../../../../tests/integration/validate_plans.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:33446f418cc7443025ffcf64ca74661bec0f89d0b744e6864764cf8ba157501a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for validate_plans.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–17](../../../../../tests/integration/validate_plans.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep structural-plan fixture expectations active under python -O. |
| inputs / outputs | Truth-tests condition; returns None or raises RuntimeError(message). |
| invariants | Explicit if is not removed by assertion optimization. |
| ownership | Borrows operands without changing plans, results or files. |
| failure | False condition raises RuntimeError; predicate/truth conversion errors propagate. |
| cost | One truth conversion after caller computation. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 20–24](../../../../../tests/integration/validate_plans.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and decode a UTF-8 structural fixture JSON file. |
| inputs / outputs | Takes Path and returns any json.loads value. |
| invariants | No object/type, duplicate-key or nonfinite-number restrictions are added; main/check_case enforce their own shapes. |
| ownership | Reads full text into new objects and closes file through Path.read_text; input files stay unchanged. |
| failure | OSError and JSONDecodeError become chained RuntimeError with path; UnicodeDecodeError is not included in that catch. |
| cost | Whole-file decode and JSON parse with full text/object allocations. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 27–28](../../../../../tests/integration/validate_plans.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def is_integer(value: Any) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept integer fixture fields while excluding Python Boolean values. |
| inputs / outputs | Returns isinstance(value,int) and not isinstance(value,bool). |
| invariants | Accepts int subclasses and negative values; bounds/sign are separate caller concerns. |
| ownership | No mutation, allocation of containers or retained argument reference. |
| failure | Ordinary object values return False; no conversion/parsing is attempted. |
| cost | Two type tests with constant helper work. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 31–38](../../../../../tests/integration/validate_plans.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_cli(executable: str, query: Path, plan: Path) -> subprocess.CompletedProcess[str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke validate-plan while returning status and channels for explicit fixture checks. |
| inputs / outputs | Takes executable/query/plan Paths; runs command with captured strict UTF-8 text and check=False, returning CompletedProcess. |
| invariants | Does not assert success, suppress stderr or impose a timeout; callers determine valid-tree/invalid-tree/malformed exits. |
| ownership | New argument/result/channel objects; subprocess.run waits and manages/closes communication pipes; path arguments remain borrowed. |
| failure | Launch and UTF-8 decoding errors propagate; a hung child has no helper timeout and a nonzero exit is returned rather than raised. |
| cost | One native structural validation child and complete output buffering; no fixed bound on child time or emitted bytes. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 41–103](../../../../../tests/integration/validate_plans.py#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_result(case_name: str, process: subprocess.CompletedProcess[str]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the documented shape of a validate-plan result object before fixture-specific assertions. |
| inputs / outputs | Takes case label/process; parses stdout and validates version 1, bool tree_valid, nullable integer heights/depth, supported height_status, string-array connex/separators and structured violation fields. Returns same newly decoded dict. |
| invariants | Rejects bool-as-integer via is_integer, but does not enforce nonnegative heights, exact top-level keys or semantic consistency between fields; check_case supplies consistency/manual comparisons. |
| ownership | Creates parsed JSON graph and iterates nested arrays without mutation; borrows CompletedProcess text. |
| failure | Invalid JSON becomes chained RuntimeError including complete channels; checked shape failures RuntimeError and unexpected nested behavior may raise normally. |
| cost | Full stdout parse and linear traversal of separators/violations; error diagnostics may hold complete stdout/stderr. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0012

[Lines 106–196](../../../../../tests/integration/validate_plans.py#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_case(executable: str, fixture_dir: Path, case: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one hand-authored structural fixture’s validity, height, violation rules and optional witnesses/connex set. |
| inputs / outputs | Takes CLI/fixture_dir/case; verifies query/plan files and expected field types, invokes validate-plan and compares expected exit 0/1, tree_valid, native height, upper-bound/invalid status, edge-depth nullability, rule set and optional witness/connex expectations. |
| invariants | Rule equality is set equality, so duplicate same-rule violations are not rejected; each witness needs some matching item. Valid-tree connex output must be unique when expected_maximal_connex is supplied. Paths are joined without containment enforcement and successful stderr need not be empty. |
| ownership | Reads trusted fixture metadata and native result; no files or input containers are changed. Witness match lists and rule/connex sets are temporary. |
| failure | Explicit mismatch raises RuntimeError; file/CLI/JSON/type errors propagate according to helpers. No timeout is applied by run_cli. |
| cost | One validation child plus result parsing and repeated violation scans per expected witness; file existence checks and set construction depend on fixture/output size. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 199–219](../../../../../tests/integration/validate_plans.py#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_malformed_input(executable: str, fixture_dir: Path, case: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a syntactically malformed tree receives the CLI usage/diagnostic channel contract. |
| inputs / outputs | Uses case query path, creates malformed.tree.json in a context-managed temporary directory, runs validate-plan and after cleanup requires exit 2, whitespace-only stdout and stderr object.error code invalid_document plus nonempty message. |
| invariants | Tests malformed document handling, distinct from a parsed structurally invalid tree’s exit 1 report. Does not require exact stderr keys/text or forbid whitespace stdout. |
| ownership | TemporaryDirectory removes malformed file before response assertions and also on subprocess exceptions; parsed diagnostic is private. |
| failure | RuntimeError on contract/parse mismatch; I/O/launch/UTF-8 errors propagate and run_cli has no timeout. |
| cost | One temporary-file write/removal, one native CLI child and full stderr JSON parsing. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 222–242](../../../../../tests/integration/validate_plans.py#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a nonempty version 1 structural-plan fixture matrix and one malformed-tree boundary probe. |
| inputs / outputs | Takes executable/fixture-dir argv, loads manifest, checks integer version/cases list, checks every case, then malformed input using first case; prints count and returns 0. |
| invariants | Uses manual expected structural outcomes and valid_upper_bound, not optimum-height authority; a nonempty cases array ensures the malformed probe has a query. |
| ownership | Manifest/result objects are local; only the delegated malformed probe creates private files, with its own context cleanup. Repository fixtures are read-only. |
| failure | Usage/check errors raise RuntimeError caught at entrypoint for stderr exit 1; helper-wrapped read/JSON errors also arrive there, while Unicode/launch/unexpected-type errors can escape. |
| cost | One full native validate-plan child per fixture plus one malformed child, complete result parses and optional witness scans; there is no overall/per-child timeout here. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0017

[Lines 243–250](../../../../../tests/integration/validate_plans.py#L243); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run a nonempty version 1 structural-plan fixture matrix and one malformed-tree boundary probe. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/validate_plans.py](../../../../../tests/integration/validate_plans.py), [docs/development.md](../../../../development.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
