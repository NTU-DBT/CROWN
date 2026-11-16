# `tests/reference/weighted_bag_oracle.py` — block usage map

[Source](../../../../../tests/reference/weighted_bag_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `24ff79d5164f06e9c8f4683d9c49c27d96c64ae6a9f2884b25b9db30be3f867b`. 442 lines partitioned into 18 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/reference/weighted_bag_oracle.py#L1) | declares aliases. | 2 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 31–53](../../../../../tests/reference/weighted_bag_oracle.py#L31) | Imports dependencies; declares callable signatures. |  · [reviewed contract](#b0002) |
| [B0003 · 54–60](../../../../../tests/reference/weighted_bag_oracle.py#L54) | Callable definition: def _json_scalar_key(value: Any) -&gt; str: | calls type, in, dumps, isfinite; returns json.dumps(value, ensure_ascii=False, separators=(",", ":")); json.dumps(value, ensure_ascii=False,…; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 61–62](../../../../../tests/reference/weighted_bag_oracle.py#L61) | Explanatory comments or spacing. |  |
| [B0005 · 63–72](../../../../../tests/reference/weighted_bag_oracle.py#L63) | Callable definition: def _parse_weight(value: Any) -&gt; int: | calls type, isinstance, fullmatch, int; returns weight · [reviewed contract](#b0005) |
| [B0006 · 73–74](../../../../../tests/reference/weighted_bag_oracle.py#L73) | Explanatory comments or spacing. |  |
| [B0007 · 75–76](../../../../../tests/reference/weighted_bag_oracle.py#L75) | Callable definition: def _row_values(keys: tuple\[str, ...\]) -&gt; list\[Any\]: | calls loads; returns \[json.loads(key) for key in keys\]; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 77–78](../../../../../tests/reference/weighted_bag_oracle.py#L77) | Explanatory comments or spacing. |  |
| [B0009 · 79–87](../../../../../tests/reference/weighted_bag_oracle.py#L79) | Callable definition: def _merge_assignments(left: dict\[int, str\], right: dict\[int, str\]) -&gt; dict\[int, str\] \| None: | calls copy, items, get; returns None; merged; 2 loop sites; source comment (unverified): # Encoded values are nonempty JSON strings, including the key for null. · [reviewed contract](#b0009) |
| [B0010 · 88–89](../../../../../tests/reference/weighted_bag_oracle.py#L88) | Explanatory comments or spacing. |  |
| [B0011 · 90–206](../../../../../tests/reference/weighted_bag_oracle.py#L90) | Callable definition: def _validate( | calls get, in, isinstance, ValueError; returns route, \[\], \[\]; active.add(node_id); 15 loop sites · [reviewed contract](#b0011) |
| [B0012 · 207–208](../../../../../tests/reference/weighted_bag_oracle.py#L207) | Explanatory comments or spacing. |  |
| [B0013 · 209–237](../../../../../tests/reference/weighted_bag_oracle.py#L209) | Callable definition: def evaluate(obj: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls isinstance, ValueError, _validate, defaultdict; returns {"rows": \[\], "total_count": "0"}; {"rows": \[{"row": \[\], "count": "1"}\], "total_count": "1"}; 4 loop sites · [reviewed contract](#b0013) |
| [B0014 · 238–239](../../../../../tests/reference/weighted_bag_oracle.py#L238) | Explanatory comments or spacing. |  |
| [B0015 · 240–417](../../../../../tests/reference/weighted_bag_oracle.py#L240) | Callable definition: def _self_test() -&gt; None: | calls R, S, one, evaluate; 1 loop sites; source comment (unverified): # R(x,y,u) has hidden-u total 2+3=5. S(y,z) has hidden-z total 5+7=12. · [reviewed contract](#b0015) |
| [B0016 · 418–419](../../../../../tests/reference/weighted_bag_oracle.py#L418) | Explanatory comments or spacing. |  |
| [B0017 · 420–438](../../../../../tests/reference/weighted_bag_oracle.py#L420) | Callable definition: def main(argv: list\[str\]) -&gt; int: | calls _self_test, print, enumerate, strip; returns 0; 2; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 439–442](../../../../../tests/reference/weighted_bag_oracle.py#L439) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |

## B0001

[Lines 1–30](../../../../../tests/reference/weighted_bag_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:6c613e7578e9c05ac96e3c78520f3d7b4f32e853b8f1e9a40890478c6f89f868
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for weighted_bag_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–53](../../../../../tests/reference/weighted_bag_oracle.py#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L53:sha256:0edb0e6fdb7a621f35bb8b26a2314bcfaa1d61aae4f430ab102198841f61354b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for weighted_bag_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 54–60](../../../../../tests/reference/weighted_bag_oracle.py#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _json_scalar_key(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a finite JSON scalar as a stable key that separates bool, int and float representations. |
| inputs / outputs | Accepts None or exact bool/int/str types, or exact finite float; returns compact unescaped-Unicode JSON str. |
| invariants | Rejects arrays, objects, numeric subclasses and NaN/infinities; JSON spellings keep true, 1 and 1.0 distinct. This is encoded-value equality, not Python numeric equality. |
| ownership | Borrows immutable scalar and allocates encoded text; no input mutation or shared mutable result. |
| failure | Raises ValueError for disallowed value/type; json encoding and very-large-int conversion may raise their normal errors. |
| cost | String escaping or integer/float decimal rendering proportional to representation size, with complete key allocation. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0005

[Lines 63–72](../../../../../tests/reference/weighted_bag_oracle.py#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _parse_weight(value: Any) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a nonnegative exact bag multiplicity without float conversion. |
| inputs / outputs | Accepts exact int or str matching \[+-\]?\[0-9\]+ and returns int; bool is rejected. Leading signs/zeros and negative-zero text are accepted when numeric value is nonnegative. |
| invariants | Checks grammar before int(...,10), then rejects weight&lt;0; no u64 upper bound is imposed. Python integer-string conversion limits still apply. |
| ownership | Reuses an int input or creates a new integer from text; supplied strings are not changed. |
| failure | Bad type/spelling or negative value raises ValueError; host integer conversion limits can also raise ValueError. |
| cost | Regex scans all digits and decimal-to-big-int conversion depends on digit count; magnitude comparison is exact. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0007

[Lines 75–76](../../../../../tests/reference/weighted_bag_oracle.py#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _row_values(keys: tuple[str, ...]) -> list[Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one ordered tuple of scalar-key JSON spellings back into output values. |
| inputs / outputs | Takes tuple of JSON strings produced by _json_scalar_key; returns a list of independently decoded values in the same order. |
| invariants | Does not sort, deduplicate or enforce scalar types itself; scalar-only validity comes from its internal callers. |
| ownership | Creates a new list and newly parsed values; it borrows encoded keys and never edits them. |
| failure | Malformed supplied JSON raises JSONDecodeError; arbitrary external JSON strings can decode containers because this helper has no extra validation. |
| cost | One JSON parse per slot plus list allocation, proportional to all key bytes. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0009

[Lines 79–87](../../../../../tests/reference/weighted_bag_oracle.py#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _merge_assignments(left: dict[int, str], right: dict[int, str]) -> dict[int, str] | None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine variable-to-encoded-scalar assignments only when common variables agree. |
| inputs / outputs | Takes two dictionaries with integer variables and encoded-string values; returns a new merged dict or None on the first conflicting shared variable. |
| invariants | Relies on encoded values never being None so get(None sentinel) distinguishes absence; JSON null is stored as string null. Equality compares encoded text, preserving scalar type distinctions. |
| ownership | Shallow-copies left before checking right; result reuses immutable keys/strings. Neither input is mutated even on conflict. |
| failure | Normal dict/hash/equality errors propagate for nonconforming inputs; a join conflict is returned as None rather than raised. |
| cost | Copies all left entries even when the first right entry conflicts, then scans right until conflict/end; expected dictionary work plus encoded-string comparisons. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0011

[Lines 90–206](../../../../../tests/reference/weighted_bag_oracle.py#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _validate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a projected-bag fixture and materialize folded positive native tables for full Cartesian joining. |
| inputs / outputs | Accepts mapping with route; constants need empty list head and return no tables. Tree requires nonempty nodes, valid integer root, parallel inputs, nonnegative unique scope variables, graph and head; returns route, native assignment/weight tables and copied ordered head. |
| invariants | Rejects multiple parents, cycles/unreachable nodes, child duplicates/bounds, generalized leaves/nonempty generalized inputs and missing generalized-parent scope in children. Folds duplicate native rows by addition and removes zero totals; head repeats are allowed but every head variable must occur natively. This is fixture validation, not a certificate of all production tree properties. |
| ownership | Copies node scope/children and head, encodes row scalars into new keys and creates new tables/dicts; no caller container is mutated or retained as a mutable output. Internal recursive visit owns active/visited sets. |
| failure | Explicit invalid fixtures raise ValueError; direct non-dict callers can fail before evaluate’s object check, and excessive graph depth can raise RecursionError. Scalar/weight conversion errors propagate. |
| cost | Traverses graph/scopes/rows with per-node sets and recursive DFS, encodes every scalar, sums arbitrary-precision duplicate weights and sorts each folded table. Retains all positive native tuples but does not yet enumerate complete joins. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0013

[Lines 209–237](../../../../../tests/reference/weighted_bag_oracle.py#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def evaluate(obj: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact projected bag counts by complete native-occurrence Cartesian products and natural-join compatibility. |
| inputs / outputs | Accepts one object fixture; returns new rows of ordered head values/count decimal strings plus total_count. Constants return unit empty row or no rows; empty head groups all witnesses into one weighted empty row. |
| invariants | Each compatible choice multiplies each native occurrence weight once; generalized nodes add no independent atom. Shared-variable encoded values must agree, head order/repeats persist, projected counts are summed and output sorted by encoded scalar tuples; no machine-u64 overflow is applied. |
| ownership | Validation owns folded tables; each choice builds temporary merged assignments and a private grouped-count map. Returned rows are freshly JSON-decoded and do not alias caller row containers; the full expanded multiset is not stored. |
| failure | Non-object/invalid fixtures raise ValueError; integer conversion/memory/recursion failures can propagate. No incremental runtime cache or compiled artifact is consulted. |
| cost | Visits the product of positive native table sizes in the worst case, copying/merging assignments for each choice and doing big-int products/sums; stores folded inputs and distinct projected groups, then sorts groups and renders full exact counts. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0015

[Lines 240–417](../../../../../tests/reference/weighted_bag_oracle.py#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _self_test() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hand-derived bag counts and boundary semantics of the independent projected oracle. |
| inputs / outputs | No arguments/result; evaluates fixed native/generalized/hidden-branch, duplicate/type-sensitive, repeated/empty-head, nullary, disconnected and constant examples. |
| invariants | Asserts explicit 60/31/691 witness totals, duplicate summation/zero removal, bool-versus-int mismatch and exact counts beyond 2**53/u64; separately requires invalid head rejection. Assertions are disabled by -O, while the explicit try/else rejection check remains. |
| ownership | Owns all small literal fixtures/results; shallow expanded unary fixture shells share their read-only nested values. No repository file or native state changes. |
| failure | Unexpected evaluation errors propagate; failed assert or missing invalid-head rejection raises AssertionError. |
| cost | Several complete Cartesian oracle evaluations over tiny fixed inputs, sorting/grouping and arbitrary-precision count rendering; not a performance benchmark. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0017

[Lines 420–438](../../../../../tests/reference/weighted_bag_oracle.py#L420); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main(argv: list[str]) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the projected-bag oracle as a line-oriented JSON tool or fixed self-test. |
| inputs / outputs | Accepts argv list: exactly --self-test runs checks; other nonempty argv prints usage and returns 2. With no args, skips blank stdin lines, evaluates each JSON object and prints compact Unicode JSON; returns 0 at EOF. |
| invariants | A malformed line emits no result for that line, prints its 1-based physical line number to stderr and returns 2; earlier valid outputs remain emitted. Self-test assertions depend on Python optimization mode. |
| ownership | Streams lines but materializes one complete fixture/result at a time; stdout/stderr/stdin are borrowed process streams and not closed. Returned status is used by entrypoint SystemExit. |
| failure | Catches JSONDecodeError/ValueError around parse/evaluate; output encoding/BrokenPipeError, recursion/memory errors and self-test failures propagate. Output uses allow_nan=False. |
| cost | Per line includes JSON parsing, potentially combinatorial exact evaluation and complete result serialization; streaming does not bound a single fixture’s product or result size. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0018

[Lines 439–442](../../../../../tests/reference/weighted_bag_oracle.py#L439); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Expose the projected-bag oracle as a line-oriented JSON tool or fixed self-test. |
| inputs / outputs | When __name__ is __main__, invoke main(sys.argv\[1:\]). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [docs/development.md](../../../../development.md), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |
