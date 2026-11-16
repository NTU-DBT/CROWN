# `tests/reference/weighted_oracle.py` — block usage map

[Source](../../../../../tests/reference/weighted_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d030a43d03467b0eb9330d19886ec978e82facc1902903d1a9815c17e0a6e7e8`. 472 lines partitioned into 20 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../../tests/reference/weighted_oracle.py#L1) | declares callable signatures. | returns root counts 1 and 0 respectively.; 2 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 32–47](../../../../../tests/reference/weighted_oracle.py#L32) | Imports dependencies; declares callable signatures. |  · [reviewed contract](#b0002) |
| [B0003 · 48–54](../../../../../tests/reference/weighted_oracle.py#L48) | Callable definition: def _json_scalar_key(value: Any) -&gt; str: | calls type, in, dumps, isfinite; returns json.dumps(value, ensure_ascii=False, separators=(",", ":")); json.dumps(value, ensure_ascii=False,…; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 55–56](../../../../../tests/reference/weighted_oracle.py#L55) | Explanatory comments or spacing. |  |
| [B0005 · 57–66](../../../../../tests/reference/weighted_oracle.py#L57) | Callable definition: def _parse_weight(value: Any) -&gt; int: | calls type, isinstance, fullmatch, int; returns weight · [reviewed contract](#b0005) |
| [B0006 · 67–68](../../../../../tests/reference/weighted_oracle.py#L67) | Explanatory comments or spacing. |  |
| [B0007 · 69–70](../../../../../tests/reference/weighted_oracle.py#L69) | Callable definition: def _count_text(count: int) -&gt; str: | calls str; returns str(count) · [reviewed contract](#b0007) |
| [B0008 · 71–72](../../../../../tests/reference/weighted_oracle.py#L71) | Explanatory comments or spacing. |  |
| [B0009 · 73–74](../../../../../tests/reference/weighted_oracle.py#L73) | Callable definition: def _row_values(keys: tuple\[str, ...\]) -&gt; list\[Any\]: | calls loads; returns \[json.loads(key) for key in keys\]; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 75–76](../../../../../tests/reference/weighted_oracle.py#L75) | Explanatory comments or spacing. |  |
| [B0011 · 77–86](../../../../../tests/reference/weighted_oracle.py#L77) | Callable definition: def _merge_assignments(left: dict\[int, str\], right: dict\[int, str\]) -&gt; dict\[int, str\] \| None: | calls copy, items, get; returns None; merged; 1 loop sites; source comment (unverified): # JSON null is encoded as the nonempty string "null", so .get() above · [reviewed contract](#b0011) |
| [B0012 · 87–88](../../../../../tests/reference/weighted_oracle.py#L87) | Explanatory comments or spacing. |  |
| [B0013 · 89–187](../../../../../tests/reference/weighted_oracle.py#L89) | Callable definition: def _validate_tree(obj: dict\[str, Any\]) -&gt; tuple\[list\[dict\[str, Any\]\], list\[list\[Any\]\], int \| None, | calls ValueError, isinstance, len, and; returns active.add(node_id); nodes, native_rows, root, parents, separators; 13 loop sites; source comment (unverified): # A zero-weight tuple is absent from the native weighted relation. · [reviewed contract](#b0013) |
| [B0014 · 188–189](../../../../../tests/reference/weighted_oracle.py#L188) | Explanatory comments or spacing. |  |
| [B0015 · 190–331](../../../../../tests/reference/weighted_oracle.py#L190) | Callable definition: def evaluate(obj: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls isinstance, ValueError, get, _validate_tree; returns {; {; 19 loop sites; source comment (unverified): # Complete assignment is (all variable/value keys in this subtree, weight). · [reviewed contract](#b0015) |
| [B0016 · 332–333](../../../../../tests/reference/weighted_oracle.py#L332) | Explanatory comments or spacing. |  |
| [B0017 · 334–447](../../../../../tests/reference/weighted_oracle.py#L334) | Callable definition: def _self_test() -&gt; None: | calls one_native, evaluate, tuple, G; returns {; 8 loop sites; source comment (unverified): # Hand calculation: hidden y contributes 5*13 + 7*17 = 184 for x=0. · [reviewed contract](#b0017) |
| [B0018 · 448–449](../../../../../tests/reference/weighted_oracle.py#L448) | Explanatory comments or spacing. |  |
| [B0019 · 450–468](../../../../../tests/reference/weighted_oracle.py#L450) | Callable definition: def main(argv: list\[str\]) -&gt; int: | calls _self_test, print, enumerate, strip; returns 0; 2; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 469–472](../../../../../tests/reference/weighted_oracle.py#L469) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |

## B0001

[Lines 1–31](../../../../../tests/reference/weighted_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L31:sha256:67e091b386500a6da8e49691ea84be3b14c2b1b87598d6fb41e9ff70458866c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for weighted_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 32–47](../../../../../tests/reference/weighted_oracle.py#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L47:sha256:c756077d29914f9c2af2d89929d64c35311062466d88671ccde5886024641d71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for weighted_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 48–54](../../../../../tests/reference/weighted_oracle.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _json_scalar_key(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a type-sensitive finite JSON scalar key for complete weighted subtree assignments. |
| inputs / outputs | Accepts None/exact bool,int,str or exact finite float and returns compact Unicode JSON text. |
| invariants | Rejects containers, subclasses of accepted numeric/string types and nonfinite floats; true, 1 and 1.0 remain distinct encoded values. |
| ownership | Creates immutable text and borrows the scalar, with no mutable input sharing or mutation. |
| failure | Invalid type/nonfinite value raises ValueError; JSON/large-int rendering errors may propagate. |
| cost | Representation-length string escaping/number rendering and full key allocation. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0005

[Lines 57–66](../../../../../tests/reference/weighted_oracle.py#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _parse_weight(value: Any) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse an exact nonnegative local tuple weight with no u64 truncation. |
| inputs / outputs | Accepts exact int or signed decimal str matching \[+-\]?\[0-9\]+, returning int; bool and float are rejected. |
| invariants | Optional plus/leading zeros and -0 are accepted; negative numeric values are rejected after parsing, and no fixed upper bound is applied. Host integer text limits still matter. |
| ownership | Leaves input unchanged; int input may be reused and text input produces a new integer. |
| failure | ValueError for invalid type/grammar, negative weight or host integer conversion limit. |
| cost | Linear digit grammar scan plus size-dependent decimal big-int conversion/comparison. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0007

[Lines 69–70](../../../../../tests/reference/weighted_oracle.py#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _count_text(count: int) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render an exact computed count for JSON consumers without a float intermediate. |
| inputs / outputs | Takes a count normally produced as a nonnegative Python int and returns str(count). |
| invariants | Does not validate nonnegativity/type or add a width bound; callers provide exact totals/support values. |
| ownership | Returns new decimal text for integers; no caller container or global changes. |
| failure | Unusual __str__ failures or host very-large-int digit limits propagate. |
| cost | Decimal rendering/allocation scales with count digit length, not a fixed machine word. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0009

[Lines 73–74](../../../../../tests/reference/weighted_oracle.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _row_values(keys: tuple[str, ...]) -> list[Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct an ordered row/key from its encoded scalar components. |
| inputs / outputs | Takes tuple of JSON key strings and returns a list via independent json.loads per component. |
| invariants | Order and repeated slots are preserved; no sorting/type validation occurs beyond parsing because internal callers already enforce scalar keys. |
| ownership | Allocates a new list/decoded values; it never modifies encoded tuple or caller rows. |
| failure | JSONDecodeError propagates for malformed external key text; external container JSON can decode because this helper does not recheck scalar form. |
| cost | Parses total encoded bytes with one parser call per slot and retains all decoded values. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0011

[Lines 77–86](../../../../../tests/reference/weighted_oracle.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _merge_assignments(left: dict[int, str], right: dict[int, str]) -> dict[int, str] | None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join two full variable assignments while rejecting incompatible shared encoded values. |
| inputs / outputs | Returns shallow copy of left extended by right, or None at first shared-variable mismatch. |
| invariants | get() uses None as absence sentinel; valid values are encoded strings including null, so actual JSON null is not confused with absence. |
| ownership | Copies left even on eventual conflict and shares immutable keys/value strings in result; inputs remain unchanged. |
| failure | Nonconforming mapping/hash/equality errors propagate; ordinary incompatibility is a None result. |
| cost | Expected O(len(left)+scanned right) dict work plus encoded-string comparisons and copied-map allocation. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0013

[Lines 89–187](../../../../../tests/reference/weighted_oracle.py#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _validate_tree(obj: dict[str, Any]) -> tuple[list[dict[str, Any]], list[list[Any]], int | None,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate subtree-oracle graph/input structure and fold duplicate native rows into positive exact weights. |
| inputs / outputs | Requires nodes/root/inputs; permits empty nodes with root None, otherwise valid integer root. Returns copied nodes, encoded folded rows, root, parents and child-scope-ordered parent separators. |
| invariants | Checks unique integer scope variables (negative IDs are accepted here), child indices/duplicates, one parent, root parentlessness/reachability/cycles and full generalized-parent scope on each child separator. Generalized input must be empty; unlike the bag validator, a generalized leaf is not expressly rejected. No running-intersection/certificate proof is claimed. |
| ownership | Copies scopes/children/separators, creates new row-key/weight tables and does not mutate raw fixture containers. Recursive graph visit owns its private sets. |
| failure | Explicit invalid structure/row/weight raises ValueError; deep DFS can raise RecursionError and numeric/encoding errors propagate. Direct caller must supply a dict-like object. |
| cost | Traverses graph/rows with sets, encodes scalar keys, adds duplicate arbitrary-precision weights and sorts each native table; materializes folded inputs and copied graph before evaluation. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0015

[Lines 190–331](../../../../../tests/reference/weighted_oracle.py#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def evaluate(obj: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently compute weighted subtree states/messages by enumerating complete compatible native derivations. |
| inputs / outputs | Takes object with tree or constant route; returns route/root/root_count plus per-node local/subtree/cached-child/support rows and positive parent-separator messages, all counts decimal strings. Empty tree yields root_count 0; constant routes bypass tree validation and reuse optional root value. |
| invariants | Native local weight contributes once per derivation; generalized local candidates are union of positive child keys with unit local weight. Complete child assignments are natural-joined before summing; different derivations remain separate, and messages aggregate along child-ordered separators. No bounded-u64 arithmetic or incremental state is used. |
| ownership | Owns copied validated graph, all subtree assignment lists, row states and message maps. Result scopes/separators share those private internal lists with result messages, not caller scope lists; decoded rows/keys are newly allocated. Constant-route root is passed through from input. |
| failure | Non-object/unknown route/invalid tree raises ValueError; recursion depth, big-int rendering and allocation failures propagate. No exception-to-zero fallback exists. |
| cost | Can take and retain exponentially many complete assignments across subtrees; each join copies assignment maps and multiplies arbitrary-precision weights. Also builds every cached child entry/message, sorts keys and renders exact decimal counts; it is not an incremental/performance model. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0017

[Lines 334–447](../../../../../tests/reference/weighted_oracle.py#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _self_test() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check independent subtree/message semantics with hand-calculated weighted examples and exact large counts. |
| inputs / outputs | No arguments/result; evaluates fixed native path, generalized union/support, &gt;2**53 and 10**120 weights, zero rows, deletions/replacements and constant routes. |
| invariants | Asserts root 368 and generalized 35, individual subtree/message/cache/support values, duplicate-zero removal and exact count text; calls are fresh evaluations rather than incremental maintenance. All expected-value assertions disappear under -O. |
| ownership | All literal fixtures/results are locally owned; no native runtime, filesystem or global mutable oracle state is changed. |
| failure | AssertionError identifies mismatch when enabled; any evaluate/conversion error propagates. |
| cost | Several small full-assignment evaluations and large-integer string operations; bounded fixture size does not imply fixed-width arithmetic. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0019

[Lines 450–468](../../../../../tests/reference/weighted_oracle.py#L450); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main(argv: list[str]) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the weighted-subtree oracle on JSONL stdin or its fixed self-test. |
| inputs / outputs | Accepts argv list: --self-test prints success after _self_test; any other arguments print usage and return 2. Empty argv skips blank lines and prints one compact JSON result per accepted input, returning 0 at EOF. |
| invariants | Parse/evaluate ValueError stops at the first offending physical line with a stderr line number and no output for that line; previously printed records remain. Output allow_nan=False protects serialization, while fixture validation supplies finite row values. |
| ownership | Borrows process streams without closing them and retains one parsed fixture/result at a time, apart from their potentially large evaluation state. |
| failure | Catches JSONDecodeError/ValueError only inside the line parse/evaluate block; self-test AssertionError, recursion/memory failures and output I/O errors propagate. |
| cost | JSON streaming adds per-line parse/serialize cost to potentially exponential subtree materialization and big-int arithmetic; there is no global row/work bound in this CLI. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0020

[Lines 469–472](../../../../../tests/reference/weighted_oracle.py#L469); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run the weighted-subtree oracle on JSONL stdin or its fixed self-test. |
| inputs / outputs | When __name__ is __main__, invoke main(sys.argv\[1:\]). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [docs/development.md](../../../../development.md), [Refactor.md §10.2](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |
