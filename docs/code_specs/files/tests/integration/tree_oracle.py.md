# `tests/integration/tree_oracle.py` — block usage map

[Source](../../../../../tests/integration/tree_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6375abee78ff863128ce7ab230d357200c812a2f7de5d5aa895cb78aa052de73`. 458 lines partitioned into 39 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/integration/tree_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–22](../../../../../tests/integration/tree_oracle.py#L19) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Keep test assertions enabled when this script is invoked with \`\`python -O\`\`. · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../tests/integration/tree_oracle.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–26](../../../../../tests/integration/tree_oracle.py#L25) | Callable definition: def is_integer(value: Any) -&gt; bool: | calls isinstance; returns isinstance(value, int) and not isinstance(value, bool) · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../../tests/integration/tree_oracle.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–34](../../../../../tests/integration/tree_oracle.py#L29) | Callable definition: def short(value: Any, limit: int = 1200) -&gt; str: | calls isinstance, decode, dumps, len; returns value if len(value) &lt;= limit else value\[:limit\] + "…" · [reviewed contract](#b0006) |
| [B0007 · 35–36](../../../../../tests/integration/tree_oracle.py#L35) | Explanatory comments or spacing. |  |
| [B0008 · 37–41](../../../../../tests/integration/tree_oracle.py#L37) | Callable definition: def load_json(path: Path) -&gt; Any: | calls loads, read_text, except, RuntimeError; returns json.loads(path.read_text(encoding="utf-8")) · [reviewed contract](#b0008) |
| [B0009 · 42–43](../../../../../tests/integration/tree_oracle.py#L42) | Explanatory comments or spacing. |  |
| [B0010 · 44–53](../../../../../tests/integration/tree_oracle.py#L44) | Callable definition: def parse_stdout(label: str, process: subprocess.CompletedProcess\[str\]) -&gt; dict\[str, Any\]: | calls loads, RuntimeError, short, require; guard require(isinstance(result, dict), f"{label}: JSON result must be an object"); returns result · [reviewed contract](#b0010) |
| [B0011 · 54–55](../../../../../tests/integration/tree_oracle.py#L54) | Explanatory comments or spacing. |  |
| [B0012 · 56–70](../../../../../tests/integration/tree_oracle.py#L56) | Callable definition: def invoke(executable: str, args: list\[str\], label: str) -&gt; subprocess.CompletedProcess\[str\]: | calls run, RuntimeError, short; returns subprocess.run( · [reviewed contract](#b0012) |
| [B0013 · 71–72](../../../../../tests/integration/tree_oracle.py#L71) | Explanatory comments or spacing. |  |
| [B0014 · 73–103](../../../../../tests/integration/tree_oracle.py#L73) | Callable definition: def checked_status(label: str, result: dict\[str, Any\]) -&gt; None: | calls require, is_integer, get, isinstance; guard require(; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 104–105](../../../../../tests/integration/tree_oracle.py#L104) | Explanatory comments or spacing. |  |
| [B0016 · 106–122](../../../../../tests/integration/tree_oracle.py#L106) | Callable definition: def verify_output(label: str, process: subprocess.CompletedProcess\[str\], *, valid: bool) -&gt; dict\[str, Any\]: | calls require, short, parse_stdout, is_integer; guard require(; returns result · [reviewed contract](#b0016) |
| [B0017 · 123–124](../../../../../tests/integration/tree_oracle.py#L123) | Explanatory comments or spacing. |  |
| [B0018 · 125–129](../../../../../tests/integration/tree_oracle.py#L125) | Callable definition: def atom_signature(query: dict\[str, Any\]) -&gt; dict\[str, tuple\[str, list\[Any\]\]\]: | calls ; returns {; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 130–131](../../../../../tests/integration/tree_oracle.py#L130) | Explanatory comments or spacing. |  |
| [B0020 · 132–136](../../../../../tests/integration/tree_oracle.py#L132) | Callable definition: def catalog_signature(catalog: dict\[str, Any\]) -&gt; dict\[str, list\[tuple\[str, str\]\]\]: | calls ; returns {; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 137–138](../../../../../tests/integration/tree_oracle.py#L137) | Explanatory comments or spacing. |  |
| [B0022 · 139–168](../../../../../tests/integration/tree_oracle.py#L139) | Callable definition: def check_query_binding(label: str, original: dict\[str, Any\], binding: Any) -&gt; None: | calls require, isinstance, get, catalog_signature; guard require(isinstance(binding, dict), f"{label}: certificate query_binding must be an object"); 6 loop sites · [reviewed contract](#b0022) |
| [B0023 · 169–170](../../../../../tests/integration/tree_oracle.py#L169) | Explanatory comments or spacing. |  |
| [B0024 · 171–215](../../../../../tests/integration/tree_oracle.py#L171) | Callable definition: def check_certificate( | calls get, require, isinstance, check_query_binding; guard require(isinstance(certificate, dict), f"{label}: proven minimum must include a certificate"); returns certificate; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 216–217](../../../../../tests/integration/tree_oracle.py#L216) | Explanatory comments or spacing. |  |
| [B0026 · 218–243](../../../../../tests/integration/tree_oracle.py#L218) | Callable definition: def check_tree_with_independent_validator( | calls write_text, dumps, invoke, str; guard require( · [reviewed contract](#b0026) |
| [B0027 · 244–245](../../../../../tests/integration/tree_oracle.py#L244) | Explanatory comments or spacing. |  |
| [B0028 · 246–300](../../../../../tests/integration/tree_oracle.py#L246) | Callable definition: def check_case(executable: str, fixture_dir: Path, temp: Path, case: Any) -&gt; dict\[str, Any\]: | calls require, isinstance, get, resolve; guard require(isinstance(case, dict), "manifest case must be an object"); returns a tree"); result; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 301–302](../../../../../tests/integration/tree_oracle.py#L301) | Explanatory comments or spacing. |  |
| [B0030 · 303–348](../../../../../tests/integration/tree_oracle.py#L303) | Callable definition: def check_mutated_certificate( | calls resolve, deepcopy, require, is_integer; guard require(is_integer(corrupted.get("minimum_height")), "certificate minimum_height must be an integer…; 5 loop sites · [reviewed contract](#b0030) |
| [B0031 · 349–350](../../../../../tests/integration/tree_oracle.py#L349) | Explanatory comments or spacing. |  |
| [B0032 · 351–370](../../../../../tests/integration/tree_oracle.py#L351) | Callable definition: def check_zero_work(executable: str, fixture_dir: Path, temp: Path) -&gt; None: | calls resolve, invoke, str, require; guard require(; returns a tree"); a certificate") · [reviewed contract](#b0032) |
| [B0033 · 371–372](../../../../../tests/integration/tree_oracle.py#L371) | Explanatory comments or spacing. |  |
| [B0034 · 373–379](../../../../../tests/integration/tree_oracle.py#L373) | Callable definition: def check_malformed_usage(executable: str) -&gt; None: | calls invoke, require, short; guard require( · [reviewed contract](#b0034) |
| [B0035 · 380–381](../../../../../tests/integration/tree_oracle.py#L380) | Explanatory comments or spacing. |  |
| [B0036 · 382–397](../../../../../tests/integration/tree_oracle.py#L382) | Callable definition: def check_same_body_head_changes(fixture_dir: Path, cases: list\[Any\]) -&gt; None: | calls get, require, len, load_json; guard require(len(selected) == 3, "manifest must include full, proper, and Boolean disconnected head case…; 3 loop sites · [reviewed contract](#b0036) |
| [B0037 · 398–399](../../../../../tests/integration/tree_oracle.py#L398) | Explanatory comments or spacing. |  |
| [B0038 · 400–450](../../../../../tests/integration/tree_oracle.py#L400) | Callable definition: def main() -&gt; int: | calls len, in, RuntimeError, Path; guard require(isinstance(manifest, dict), f"{manifest_path}: manifest must be an object"); returns 0; 4 loop sites; source comment (unverified): # Query aliases and variable/atom permutations preserve the analytic optimum. · [reviewed contract](#b0038) |
| [B0039 · 451–458](../../../../../tests/integration/tree_oracle.py#L451) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0039) |

## B0001

[Lines 1–18](../../../../../tests/integration/tree_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:541af8899239436f41ef7763576707b0e687663b3f566ffbbff82949b6bb9402
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for tree_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–22](../../../../../tests/integration/tree_oracle.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a structural-oracle fixture expectation independently of Python assert settings. |
| inputs / outputs | Returns None when condition is truthy, otherwise raises RuntimeError(message). |
| invariants | Explicit if remains active under -O. |
| ownership | Borrows operands and changes no tree, proof or file. |
| failure | RuntimeError on false predicate; evaluation/truth-conversion failures propagate. |
| cost | One truth test after caller traversal/diagnostic work. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 25–26](../../../../../tests/integration/tree_oracle.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def is_integer(value: Any) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize integer structural fields while rejecting bool masquerading as int. |
| inputs / outputs | Returns bool from isinstance(value,int) and not isinstance(value,bool). |
| invariants | Accepts int subclasses and negative values; callers apply their own sign constraints where needed. |
| ownership | Does not mutate or retain value. |
| failure | No numeric coercion/parsing; noninteger objects return False. |
| cost | Constant type-test work. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 29–34](../../../../../tests/integration/tree_oracle.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def short(value: Any, limit: int = 1200) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce a bounded-length human diagnostic excerpt after decoding/serializing a value. |
| inputs / outputs | Takes any supported value and limit default 1200; bytes decode UTF-8 with replacement, other nonstr values json.dumps sorted/Unicode, then returns full text or text\[:limit\]+ellipsis. |
| invariants | The output normally has at most limit+1 characters for nonnegative limit; it bounds returned text only, not the preceding complete decode/serialization. Negative limit is not validated. |
| ownership | Allocates decoded/serialized text and possible slice; original buffers/objects are unchanged. |
| failure | JSON serialization/cycle/type errors propagate; bytes decoding replaces malformed sequences instead of raising. |
| cost | Can traverse and allocate the entire value before truncation; slicing/returned excerpt costs up to limit characters under the normal nonnegative precondition. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 37–41](../../../../../tests/integration/tree_oracle.py#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one UTF-8 structural query/manifest document. |
| inputs / outputs | Takes Path, returns decoded JSON value without an object requirement. |
| invariants | Uses json.loads defaults, including nonfinite constants and last-key-wins duplicates; later checks/native loading provide their own restrictions. |
| ownership | Path helper closes its file; new text/JSON graph owned by caller, input file unchanged. |
| failure | OSError/JSONDecodeError are chained into RuntimeError naming path; UnicodeDecodeError is outside the catch. |
| cost | Whole-file read/decode/parse and complete object materialization. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 44–53](../../../../../tests/integration/tree_oracle.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_stdout(label: str, process: subprocess.CompletedProcess[str]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a structural CLI stdout JSON object for subsequent semantic checks. |
| inputs / outputs | Takes label and text CompletedProcess; returns decoded dict after require(isinstance(dict)). |
| invariants | Does not inspect status or stderr emptiness, reject unknown keys or prohibit JSON nonfinite constants itself. |
| ownership | New parsed graph; borrows channel text and leaves process result unchanged. |
| failure | JSONDecodeError becomes chained RuntimeError with short channel excerpts; nonobject gives RuntimeError. Excerpt serialization errors can propagate for abnormal process fields. |
| cost | Full stdout parse; only the diagnostic excerpt is truncated after any needed full decode/serialization. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0012

[Lines 56–70](../../../../../tests/integration/tree_oracle.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(executable: str, args: list[str], label: str) -> subprocess.CompletedProcess[str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a structural CLI command with captured strict UTF-8 channels and a per-call timeout. |
| inputs / outputs | Takes executable,args,label; runs check=False/capture_output/text/encoding UTF-8/timeout 60, returning CompletedProcess for any exit code. |
| invariants | Does not decide success or enforce empty channels; specific check functions own those obligations. |
| ownership | Creates command/result buffers; subprocess.run waits/handles communication-pipe closure and timed-out child cleanup; arguments are unchanged. |
| failure | TimeoutExpired is chained to RuntimeError with partial-channel excerpts; launch/strict decoding failures propagate. |
| cost | One actual child with complete channel buffering; short only truncates error presentation, and 60 seconds applies separately to each invocation. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 73–103](../../../../../tests/integration/tree_oracle.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def checked_status(label: str, result: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check common structural-oracle result field types and supported status vocabulary. |
| inputs / outputs | Takes label/result dict and returns None after version 1, status enum, nullable heights/tree/certificate, Boolean validity/completeness and search-object checks. |
| invariants | Requires cost_search_complete exactly False; does not enforce exact keys, nonnegative heights or relationships among status/bounds/tree. Missing nullable fields can pass via get(None); check_case/zero_work apply scenario-specific constraints. |
| ownership | Reads result without mutation; local references alias report values only during the call. |
| failure | Shape/status mismatches RuntimeError; malformed dict-like behavior/lookup errors can propagate. |
| cost | Fixed field checks plus no traversal of tree/certificate/search contents, so cheap relative to parsing/full proof replay. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 106–122](../../../../../tests/integration/tree_oracle.py#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify_output(label: str, process: subprocess.CompletedProcess[str], *, valid: bool) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a verify-height replay response against expected certificate validity without accepting a resource stop. |
| inputs / outputs | Takes process,label,keyword valid; requires exit 0 when valid else 1, version 1, bool certificate_valid/resource_limit, exact validity and resource_limit False; returns parsed dict. |
| invariants | Invalid proof is distinguished from verification-budget exhaustion. Does not require empty stderr or independently execute certificate mathematics in Python. |
| ownership | Owns newly parsed response, shares no mutable caller graph and leaves CompletedProcess unchanged. |
| failure | RuntimeError for exit/shape/validity/resource mismatch; parse failures are chained by parse_stdout. |
| cost | One response parse and fixed checks; the caller’s native verify-height child performs proof work separately. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0018

[Lines 125–129](../../../../../tests/integration/tree_oracle.py#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def atom_signature(query: dict[str, Any]) -> dict[str, tuple[str, list[Any]]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract occurrence identity/table/ordered terms for query-binding equality. |
| inputs / outputs | Takes query\[atoms\]; returns mapping atom.id to (atom.table,atom.terms). |
| invariants | Ignores atom list order and other metadata while preserving full term list/order; duplicate IDs overwrite rather than fail. |
| ownership | New dictionary and tuple shells; terms lists are the original shared references, so not a deep immutable copy. |
| failure | Missing/malformed fields or unhashable IDs raise lookup/type errors. |
| cost | One pass over atoms with dictionary insertion; it does not traverse/copy every nested term until later equality checks. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0020

[Lines 132–136](../../../../../tests/integration/tree_oracle.py#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def catalog_signature(catalog: dict[str, Any]) -> dict[str, list[tuple[str, str]]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract table names and ordered column name/type pairs for structural query-binding comparison. |
| inputs / outputs | Takes catalog\[tables\]; returns table-name mapping to newly built ordered (column name,type) lists. |
| invariants | Table order and non-name/type metadata are ignored; column order is preserved and duplicate table names overwrite. This is a structural signature, not complete catalog identity. |
| ownership | Allocates mapping/lists/tuples sharing immutable names/types; does not mutate original catalog. |
| failure | Missing fields/type errors propagate; no schema normalization is performed. |
| cost | Linear in table/column count with proportional new signature storage. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0022

[Lines 139–168](../../../../../tests/integration/tree_oracle.py#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_query_binding(label: str, original: dict[str, Any], binding: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check certificate-bound structural source against fixture catalog/query and empty data state. |
| inputs / outputs | Takes label,original document,binding; checks object/version/semantics, catalog signatures, variable name/type maps, occurrence signatures, ordered head variables, empty initial table map and no updates. Returns None. |
| invariants | Comparisons preserve head/column/term order while ignoring table/atom/variable list order and unrelated metadata. Schema_version comparison is equality to 1 rather than bool-excluding is_integer; duplicate mapped IDs/names can collapse, so this helper is not a complete hostile-input/native identity validator. |
| ownership | Builds signatures/maps and reads both documents; atom term lists are temporarily shared but never modified. |
| failure | RuntimeError on checked mismatch; incomplete nested catalog/query shapes can cause uncaught KeyError/TypeError. |
| cost | Traverses declared tables/columns/variables/atoms/head/initial and compares nested terms; no subprocess or certificate proof replay occurs here. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0024

[Lines 171–215](../../../../../tests/integration/tree_oracle.py#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_certificate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check optimized certificate envelope/binding/lower-bound shapes, then require genuine native replay acceptance. |
| inputs / outputs | Takes query path/original/result/temp directory/CLI/expected height; requires schema 2 algorithm crown_partition_exact_v2, equal tree/minimum, structural binding and typed sorted unique lower-bound occurrence arrays; writes &lt;label&gt;.certificate.json and invokes verify-height. Returns the original certificate object from result. |
| invariants | Each bound is positive integer or null and booleans are checked for reachability/generalized flags; Python checks syntax/binding and delegates proof validity to verify-height without a resource stop. expected_height None supports an unsupported-family certificate. |
| ownership | Returned dict aliases result.certificate; no deepcopy. Owns serialized file bytes/response; file lifetime and cleanup belong to caller temp directory. Does not mutate original/certificate. |
| failure | RuntimeError for shape/replay mismatch; file/JSON/child errors propagate. invoke applies 60-second per-child timeout; label filenames rely on trusted callers. |
| cost | Traverses/sorts each lower-bound occurrence list, serializes full certificate to file and launches native verification with complete output capture. Proof replay cost is additional to envelope checking. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0026

[Lines 218–243](../../../../../tests/integration/tree_oracle.py#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_tree_with_independent_validator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the independent validate-plan command to accept an oracle-produced tree at the expected native height. |
| inputs / outputs | Writes supplied tree to &lt;label&gt;.tree.json in temp, invokes validate-plan with original query, requires exit 0/tree_valid True/native_height expected and returns None. |
| invariants | Checks the candidate’s upper-bound structure separately from certificate replay; does not by itself prove optimum or demand empty stderr/all report fields. |
| ownership | Borrows tree, allocates serialized text/parsed result; temp file cleanup is caller-owned and no tree mutation occurs. |
| failure | RuntimeError for status/validity/height mismatch; serialization/I/O/child errors propagate with invoke timeout 60. |
| cost | One complete tree write, native structural validation child and response JSON parse. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0028

[Lines 246–300](../../../../../tests/integration/tree_oracle.py#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_case(executable: str, fixture_dir: Path, temp: Path, case: Any) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a manual minimum/unsupported structural-oracle fixture and independently validate any returned proof/tree. |
| inputs / outputs | Loads query, invokes tree-oracle, validates shared status shape and expected result; proven minimum requires all three heights equal manual value, valid tree, completed search, validate-plan and certificate replay. Unsupported requires no bounds/tree/selection and completed search, replaying optional certificate with expected None. Returns decoded result. |
| invariants | Expected status/height must agree; unsupported absence of family is distinct from resource_limit. Query path is resolved/existence-checked without containment enforcement; no stderr-empty or unique-name check is added. |
| ownership | Owns query/result objects; passes certificate/tree by reference to read-only check helpers. Writes proof/tree files under borrowed temp directory for caller cleanup. |
| failure | RuntimeError for checked mismatches; load/JSON/file/child/type errors follow helper behavior. Each native command is separately limited to 60 seconds. |
| cost | One oracle search child per case plus structural-validator and proof-verifier children for successful minima; full query/tree/certificate materialization, serialization and lower-bound shape traversal. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0030

[Lines 303–348](../../../../../tests/integration/tree_oracle.py#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_mutated_certificate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require native verification to reject one targeted corruption without changing the valid retained certificate. |
| inputs / outputs | Deep-copies certificate; increments minimum_height, removes one nonempty native scope variable, or adds inconsistent tree.native_height; writes corruption file and requires verify-height invalid result with no resource stop. |
| invariants | Only three named mutations are accepted; checks prerequisites for deterministic corruption. Rejection is observed from the genuine verifier rather than fabricated validity bits. |
| ownership | Deepcopy detaches ordinary JSON graph; mutations affect only private copy. Caller owns temp-directory lifetime; original certificate stays reusable for subsequent probes. |
| failure | Unknown mutation/prerequisite/replay mismatch RuntimeError; file/JSON/child errors propagate with per-invoke 60-second timeout. |
| cost | Whole certificate deepcopy and serialization; tree_scope scans nodes to first suitable native node; native proof replay can substantially exceed wrapper work. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0032

[Lines 351–370](../../../../../tests/integration/tree_oracle.py#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_zero_work(executable: str, fixture_dir: Path, temp: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a zero-work structural search reports an incomplete resource stop rather than a proof. |
| inputs / outputs | Runs tree-oracle on fixed empty-body query with work argument 0; requires exit 1, common shape, resource_limit/incomplete search and no selected height/tree/certificate. Returns None; temp argument is unused. |
| invariants | Does not assert lower/upper bound fields are null beyond checked_status typing; it specifically prevents returned selection/tree/certificate or proven/unsupported status at this boundary. |
| ownership | Reads fixed query and newly parsed result; creates no file and does not use/mutate temp. |
| failure | RuntimeError on status/shape mismatch; child/file/decoding errors propagate through invoke/parse helpers. |
| cost | One real zero-budget native search child, full response parse and fixed checks; no search-completeness proof is generated by Python. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0034

[Lines 373–379](../../../../../tests/integration/tree_oracle.py#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_malformed_usage(executable: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check tree-oracle with a missing query uses the CLI usage exit category. |
| inputs / outputs | Invokes executable with only tree-oracle and requires return code 2; returns None. |
| invariants | Checks exit status only; it does not parse stderr, require a diagnostic code or demand empty stdout. |
| ownership | Owns temporary CompletedProcess/channels; no files or caller data are modified. |
| failure | RuntimeError on wrong exit or invoke timeout; launch/decoding errors propagate. |
| cost | One child and complete captured channels even though only status is inspected. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0036

[Lines 382–397](../../../../../tests/integration/tree_oracle.py#L382); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_same_body_head_changes(fixture_dir: Path, cases: list[Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify three named disconnected head-variation fixtures share the same structural body. |
| inputs / outputs | Selects full/proper/boolean names, requires all three, loads their query documents and compares catalog signature, variable list and atom signature with disconnected_full. |
| invariants | Does not itself check that head lists differ or match the names; check_case uses their separately authored minimum/status expectations. Duplicate selected names collapse before the len==3 check. |
| ownership | Owns loaded documents and signatures; variable/term containers are borrowed for equality and never edited. |
| failure | RuntimeError for missing trio/body mismatch; malformed fixture/read errors propagate according to load_json. |
| cost | Reads three complete query files and builds/compares structural signatures; no native child or combinatorial search here. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0038

[Lines 400–450](../../../../../tests/integration/tree_oracle.py#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run finite analytic structural minima/unsupported fixtures with proof replay, renaming invariance and corruption/CLI boundary checks. |
| inputs / outputs | Takes executable and optional fixture directory; checks version 1/nonempty cases/body trio, evaluates all cases in a TemporaryDirectory, checks two renamed/permuted height pairs, three corruptions, zero work and malformed usage; prints count and returns 0. |
| invariants | Retains results keyed by name without independent duplicate-name rejection; fixed named cases/pairs must exist. Optimum assertions are bound to manual fixture values and genuine certificate replay, not inferred from valid_upper_bound alone. |
| ownership | TemporaryDirectory encloses generated trees/certificates/corruptions and cleans on all exits; result map retains all decoded reports through the matrix. Fixtures are read-only and corruptions use deepcopy. |
| failure | Entrypoint catches RuntimeError for stderr exit 1; helpers translate selected errors, but Unicode/KeyError/type/StopIteration and other failures can escape. Invoked children each have 60-second timeout. |
| cost | Multiple oracle/validate-plan/verify-height children per case plus corruption/boundary children; stores all result/proof trees, reads source fixtures and serializes/replays complete certificates. No performance-model guarantee is supplied. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0039

[Lines 451–458](../../../../../tests/integration/tree_oracle.py#L451); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run finite analytic structural minima/unsupported fixtures with proof replay, renaming invariance and corruption/CLI boundary checks. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py), [docs/development.md](../../../../development.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
