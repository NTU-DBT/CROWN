# `tools/support/check_query_reports.py` — block usage map

[Source](../../../../../tools/support/check_query_reports.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `87de632b93fd78227aeca660f4044f3d77844f175c0ebc72749055953baa66c7`. 194 lines partitioned into 12 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tools/support/check_query_reports.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tools/support/check_query_reports.py#L17) | Callable definition: def require(ok, message): | calls AssertionError; guard def require(ok, message): · [reviewed contract](#b0002) |
| [B0003 · 20–25](../../../../../tools/support/check_query_reports.py#L20) | Callable definition: def pairs(items): | calls require; guard require(key not in out, 'duplicate JSON object key'); returns out; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../tools/support/check_query_reports.py#L26) | Callable definition: def load(path): | calls loads, read_text, in, throw; returns json.loads(path.read_text(encoding='utf-8'), object_pairs_hook=pairs,; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../tools/support/check_query_reports.py#L29) | Callable definition: def maybe(x): | calls int; returns None if x == 'null' else int(x) · [reviewed contract](#b0005) |
| [B0006 · 31–32](../../../../../tools/support/check_query_reports.py#L31) | Callable definition: def texthex(x): | calls fromhex, decode; returns '' if x == '-' else bytes.fromhex(x).decode('utf-8') · [reviewed contract](#b0006) |
| [B0007 · 33–71](../../../../../tools/support/check_query_reports.py#L33) | Callable definition: def native_expected(path, report): | calls iter, read_text, splitlines, next; guard require(report\['height'\]\['status'\] == STATES\[int(first\[1\])\], 'status differs from typed native acce…; 8 loop sites · [reviewed contract](#b0007) |
| [B0008 · 72–109](../../../../../tools/support/check_query_reports.py#L72) | Callable definition: def tree_semantics(t, binding, expected_height): | calls require, type, len, set; guard require(root is None and not atoms and expected_height == 0, 'fabricated empty witness'); returns require(type(root) is int and 0 &lt;= root &lt; len(nodes), 'root out of range'); 9 loop sites; source comment (unverified): # Running intersection is checked independently over the exported graph. · [reviewed contract](#b0008) |
| [B0009 · 110–158](../../../../../tools/support/check_query_reports.py#L110) | Callable definition: def semantics(r, base, tree_validator): | calls require, and, in, with_suffix; guard require(r\['recognized_class'\]\['status'\]=='not_collected' and r\['recognized_class'\]\['diagnostic_work…; 7 loop sites · [reviewed contract](#b0009) |
| [B0010 · 159–159](../../../../../tools/support/check_query_reports.py#L159) | Explanatory comments or spacing. |  |
| [B0011 · 160–193](../../../../../tools/support/check_query_reports.py#L160) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, load; guard paths=sorted(a.corpus.rglob('*.report.json'));require(bool(paths),'empty corpus'); 3 loop sites; source comment (unverified): # Each of 436 JSON-exportable cases runs twice; the raw byte anchor is excluded. · [reviewed contract](#b0011) |
| [B0012 · 194–194](../../../../../tools/support/check_query_reports.py#L194) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |

## B0001

[Lines 1–16](../../../../../tools/support/check_query_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define offline query EXPLAIN schema, native sidecar and independent finite witness checks. |
| inputs / outputs | Imports jsonschema/stdlib, resolves paths and status/source registries; guarded main reads supplied corpus. |
| invariants | No network/subprocess/authority import or producer advancement. Schema/export checks never manufacture typed proof; tree_semantics is a selected structural checker, not full native proof replay. |
| ownership | Owns registry lists/Paths and later parsed DOMs; ordinary Python memory. |
| failure | Import errors propagate; require uses explicit AssertionError, other checks may use bare asserts requiring normal invocation. |
| cost | Fixed import/setup; explicit offline file/schema/graph scans later. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–19](../../../../../tools/support/check_query_reports.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(ok, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, AssertionError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises AssertionError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 20–25](../../../../../tools/support/check_query_reports.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def pairs(items):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct parsed JSON objects while explicitly rejecting duplicate field names. |
| inputs / outputs | Key/value pairs in; new dictionary out. |
| invariants | Uses explicit require, so duplicate rejection remains active under -O. |
| ownership | Owns dict, retains nested parsed values without deep copying. |
| failure | Duplicate AssertionError/hash/OOM errors propagate. |
| cost | Expected O(keys) insertion/storage. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 26–28](../../../../../tools/support/check_query_reports.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse complete UTF8 corpus JSON with duplicate and nonfinite rejection. |
| inputs / outputs | Path in; owning JSON DOM out. |
| invariants | Strict UTF8, pairs hook and explicit parse_constant failure; not a streaming or byte-capped parser. |
| ownership | Owns full text and DOM temporaries. |
| failure | IO/UTF8/JSON/AssertionError/OOM failures propagate. |
| cost | O(file bytes) read/parse with complete graph allocation. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 29–30](../../../../../tools/support/check_query_reports.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def maybe(x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode nullable sidecar integer text. |
| inputs / outputs | null string or decimal integer in; None/int out. |
| invariants | No independent integer range/native authority check. |
| ownership | Owns integer where parsing allocates; input borrowed. |
| failure | ValueError/type/OOM propagate. |
| cost | O(integer digits) parse or fixed sentinel test. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 31–32](../../../../../tools/support/check_query_reports.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def texthex(x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an empty or UTF8 hex-encoded native sidecar string. |
| inputs / outputs | Dash or hex text in; Unicode string out. |
| invariants | Dash is empty, not None; strict UTF8 decode preserves intended label content. |
| ownership | Owns decoded bytes/string. |
| failure | Invalid hex/UTF8/type/OOM propagate. |
| cost | O(hex bytes) decode/allocation. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 33–71](../../../../../tools/support/check_query_reports.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def native_expected(path, report):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare query-report claims/counters exactly with native typed-accessor sidecar records. |
| inputs / outputs | Expected-file Path and report DOM in; None after status/source/bounds/tree/connex/certificate/lower-claim/work comparisons. |
| invariants | Unknown tag fails; counts/node order/claims match producer output. Does not independently certify the lower-bound theorem or replay search/certificate. |
| ownership | Borrows report; owns full sidecar lines/iterators, expected node/claim lists and parsed values. |
| failure | Explicit AssertionError or parse/key/iterator errors propagate; no source mutation. |
| cost | Full sidecar scan plus structural equality over tree/claim arrays; process-only allocations. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 72–109](../../../../../tools/support/check_query_reports.py#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def tree_semantics(t, binding, expected_height):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently check selected exported witness graph and variable-connectivity properties. |
| inputs / outputs | Tree DTO, normalized binding and expected native height in; None after empty/nonempty tree checks. |
| invariants | Checks root reachability/acyclic unique parent, occurrences/native scopes, generalized child count, native height and per-variable connectedness/connex addressability. Not every P1/free-connex guard or lower-certificate verifier is reimplemented. |
| ownership | Borrows tree/binding; owns node/parent/reachability/variable sets and recursion/traversal state. |
| failure | Explicit AssertionError/malformed key/recursion/OOM errors propagate. |
| cost | Graph traversals plus per-variable induced connectivity scans, potentially O(variables×(nodes+edges)); allocates sets/maps, no native incremental update. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 110–158](../../../../../tools/support/check_query_reports.py#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def semantics(r, base, tree_validator):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check query-report publication/status/source/transport invariants beyond schema shape. |
| inputs / outputs | Query report, artifact base Path and tree validator in; selected finite semantic/text/tree/DOT checks. |
| invariants | Verified optimum/infeasible, checked upper and unknown states have distinct witness/certificate/publication flags; no cost/global optimum or hidden recognition authority. Metadata scalar escapes roundtrip through finite cases. |
| ownership | Borrows report; owns parsed text/expected sets/lists and selected witness traversal temporaries. |
| failure | Explicit predicate/lookup/IO/decode failures propagate; no producer replay or report mutation. |
| cost | Selected schema graph checks, tree_semantics and full text/DOT string/regex scans; no native search performed. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 160–193](../../../../../tools/support/check_query_reports.py#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate emitted query reports, sidecars, renderings and the required finite scenario matrix. |
| inputs / outputs | Corpus directory plus --require-all in; schema-validates each report and checks native/independent semantics, prints pass count. |
| invariants | Requires configured status/source/stop/family coverage and872 search plus872 replay reports for strict/best-depth matrix when full mode; schema mutations reject unknown authority. Finite corpus count is not exhaustive proof. |
| ownership | Owns validators, parsed artifacts, status/source/group sets and deep mutation copies; caller wrapper owns files. |
| failure | Schema/assert/parse/IO errors escape to wrapper; no broad masking or native subprocess. |
| cost | Full corpus traversal/read/schema validation plus per-report graph/text checks and mutation validation; repeated DOM copies are offline diagnostic cost. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 194–194](../../../../../tools/support/check_query_reports.py#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the query offline checker only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No outer catch; failures propagate with traceback/nonzero status and wrapper retains corpus. |
| cost | Fixed guard plus full main. |
| Design | [tools/support/check_query_reports.py](../../../../../tools/support/check_query_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |
