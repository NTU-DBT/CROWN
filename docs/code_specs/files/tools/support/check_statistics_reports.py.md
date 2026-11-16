# `tools/support/check_statistics_reports.py` — block usage map

[Source](../../../../../tools/support/check_statistics_reports.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `8a7ee3191d5e317c26267dfc2b06c605161e11db44d330e50ec4a8261b6f1dd3`. 355 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tools/support/check_statistics_reports.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 15–20](../../../../../tools/support/check_statistics_reports.py#L15) | Callable definition: def pairs(values): | calls ; returns out; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 21–22](../../../../../tools/support/check_statistics_reports.py#L21) | Explanatory comments or spacing. |  |
| [B0004 · 23–25](../../../../../tools/support/check_statistics_reports.py#L23) | Callable definition: def read(path): | calls loads, read_text, in, throw; returns json.loads(path.read_text(encoding="utf-8"), object_pairs_hook=pairs,; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../../tools/support/check_statistics_reports.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–33](../../../../../tools/support/check_statistics_reports.py#L28) | Callable definition: def item_count(value): | calls isinstance, sum, values; returns 1 + sum(item_count(v) for v in value.values()); 1 + sum(item_count(v) for v in value); 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../../tools/support/check_statistics_reports.py#L34) | Explanatory comments or spacing. |  |
| [B0008 · 36–64](../../../../../tools/support/check_statistics_reports.py#L36) | Callable definition: def scalar(value): | calls fullmatch, fromhex, type, fromisoformat; returns bytes.fromhex(raw); raw · [reviewed contract](#b0008) |
| [B0009 · 65–67](../../../../../tools/support/check_statistics_reports.py#L65) | Module statements. | source comment (unverified): # Decoding retains Python classes, but numeric classes can compare equal across kinds. · [reviewed contract](#b0009) |
| [B0010 · 68–69](../../../../../tools/support/check_statistics_reports.py#L68) | Callable definition: def native_row(value): | calls tuple, scalar; returns tuple(scalar(v) for v in value); 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 70–71](../../../../../tools/support/check_statistics_reports.py#L70) | Explanatory comments or spacing. |  |
| [B0012 · 72–85](../../../../../tools/support/check_statistics_reports.py#L72) | Callable definition: def distribution(actual, counts, visited, k): | calls len, Counter, values, sorted; 4 loop sites; source comment (unverified): # Ranked value equality also establishes complete list and key lengths. · [reviewed contract](#b0012) |
| [B0013 · 86–87](../../../../../tools/support/check_statistics_reports.py#L86) | Explanatory comments or spacing. |  |
| [B0014 · 88–112](../../../../../tools/support/check_statistics_reports.py#L88) | Callable definition: def literal(report, supported): | calls Counter, len, zip, distribution; 11 loop sites · [reviewed contract](#b0014) |
| [B0015 · 113–117](../../../../../tools/support/check_statistics_reports.py#L113) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 118–211](../../../../../tools/support/check_statistics_reports.py#L118) | Callable definition: def semantics(report): | calls in, assert, sum, sorted; guard assert (metric\["fact"\]\["value"\] is not None) == known; 16 loop sites · [reviewed contract](#b0016) |
| [B0017 · 212–213](../../../../../tools/support/check_statistics_reports.py#L212) | Explanatory comments or spacing. |  |
| [B0018 · 214–220](../../../../../tools/support/check_statistics_reports.py#L214) | Callable definition: def find_cell(report, role, operation="insert", node=None): | calls len; returns found\[0\]; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 221–222](../../../../../tools/support/check_statistics_reports.py#L221) | Explanatory comments or spacing. |  |
| [B0020 · 223–351](../../../../../tools/support/check_statistics_reports.py#L223) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, read; guard assert (root\["inputs"\], root\["changed"\], root\["noop"\], root\["complete_detail_inputs"\]) == (2, 1, 1,…; returns raise AssertionError("mutated report escaped schema/semantic checks"); 14 loop sites · [reviewed contract](#b0020) |
| [B0021 · 352–355](../../../../../tools/support/check_statistics_reports.py#L352) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–14](../../../../../tools/support/check_statistics_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define offline statistics schema/literal-map/transport/mutation validation. |
| inputs / outputs | Imports jsonschema and stdlib only; guarded main reads native-produced corpus plus frozen legacy bytes. |
| invariants | Never imports engine code. Literal independent maps validate selected finite observations; report DTOs do not grant native/owner/proof authority. Bare asserts require normal Python. |
| ownership | Owns imports and later complete DOMs/mutants/expected counters; no native query account. |
| failure | Import failure before main; validation exceptions propagate to wrapper that retains failure corpus. |
| cost | Fixed imports; all report/schema/key/histogram scans are explicit offline allocating diagnostics. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–20](../../../../../tools/support/check_statistics_reports.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def pairs(values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a JSON object while rejecting duplicate names under enabled assertions. |
| inputs / outputs | Key/value list in; new dict out. |
| invariants | Duplicate-key guard is bare assert; normal CMake invocation enables it. |
| ownership | Owns dict retaining nested parsed values. |
| failure | AssertionError/hash/OOM propagate. |
| cost | Expected O(keys) hash insertion and dict storage. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 23–25](../../../../../tools/support/check_statistics_reports.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read strict UTF8 JSON with duplicate/nonfinite rejection hooks. |
| inputs / outputs | Path in; complete parsed graph out. |
| invariants | Nonfinite constants explicitly raise AssertionError; duplicate guard uses pairs. No resource grant or streaming. |
| ownership | Owns full Unicode file and DOM. |
| failure | IO/Unicode/JSON/assert/OOM errors propagate. |
| cost | O(file bytes) read/parse plus full graph allocation. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 28–33](../../../../../tools/support/check_statistics_reports.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def item_count(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count JSON value nodes using the exported item-count convention. |
| inputs / outputs | Any parsed JSON value in; integer count out. |
| invariants | Counts1 for container and each child value recursively; dictionary keys are not counted. |
| ownership | Borrows graph; recursive frames/scalar sums only, no deep copy. |
| failure | Recursion-limit/OOM errors propagate on extreme nesting. |
| cost | O(value nodes) traversal, O(depth) stack; not byte size or native allocation accounting. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 36–64](../../../../../tools/support/check_statistics_reports.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scalar(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and decode a statistics typed scalar into its Python value. |
| inputs / outputs | Scalar DTO with type/value/encoding in; bytes/int/bool/date/Decimal out. |
| invariants | Checks string lowercase hex, strict int64/bool, canonical ISO date, finite canonical decimal≤38 significant digits/scale. Returned values omit DTO type tags; Python cross-numeric equality may merge int/bool/Decimal. |
| ownership | Owns decoded bytes/date/Decimal and temporary canonical strings; int/bool may reuse immutable input values. |
| failure | Assertion/date/Decimal/hex/lookup/OOM failures propagate; no repair/coercion of noncanonical spelling. |
| cost | O(scalar text bytes) decode/canonicalize; decimal arithmetic/formatting and integer checks depend on digits, no fixed allocation-free claim. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 65–67](../../../../../tools/support/check_statistics_reports.py#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L67:sha256:654a52d31237abad83ac3255c8598c23525d33b5a2a4de3fa713c09f4d6751ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Decoding retains Python classes, but numeric classes can compare equal across kinds. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 68–69](../../../../../tools/support/check_statistics_reports.py#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def native_row(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode all typed scalar positions into an untagged Python tuple. |
| inputs / outputs | Row DTO list in; tuple(scalar(v)...) out. |
| invariants | Scalar validators retain valid Python scalar classes, but untagged tuple value equality alone can equate True/1/Decimal(1). distribution separately requires exact per-position Python types; other native_row consumers, including sorting, retain their actual decoded-value semantics. |
| ownership | Owns tuple and decoded scalar results; source row DTO unchanged. |
| failure | First scalar rejection/allocation error propagates; partial tuple not returned. |
| cost | O(arity+scalar decoding bytes) traversal/allocation. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 72–85](../../../../../tools/support/check_statistics_reports.py#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def distribution(actual, counts, visited, k):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an exact captured distribution to an independent finite expected counter. |
| inputs / outputs | Actual distribution DTO, independent expected typed Python key-&gt;multiplicity Counter, visited count and top-K grant in; asserts completion/NDV/histogram/ranked values, exact per-position scalar classes and unknown reason. |
| invariants | Expected ranking sorts (-multiplicity,key). Ranked value equality first establishes list/key lengths and values. A streamed per-cell predicate requires identical decoded standard Python classes at every position; bool/int/Decimal numeric equality cannot substitute another scalar kind. Expected Counter construction must preserve its admitted key schema. |
| ownership | Borrows actual/counts; owns histogram Counter, sorted expected ranks and decoded observed list. Type comparison holds references through zip/generator iterators with constant auxiliary state; no complete type matrices or report/native mutation. |
| failure | Existing assertions and scalar checks remain; after value equality, a decoded scalar-kind mismatch now raises AssertionError. Lookup/ordering/decode/OOM failures propagate without broad handling. |
| cost | O(distinct keys log distinct keys) expected sorting and O(topK×arity+scalar bytes) decoding. Exact type-identity scan is O(topK×arity), short-circuits on mismatch and uses constant auxiliary iterator storage. Existing rank/decoded-key storage remains; all work is offline, with no native runtime overhead. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 88–112](../../../../../tools/support/check_statistics_reports.py#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def literal(report, supported):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check eight requested statistics components against an independent four-row physical-support example. |
| inputs / outputs | Statistics report and supported-y set in; assertions on cardinalities, six exact distributions and two unrequested reasons. |
| invariants | Separates physical source multiplicity, projected native support, live survivors, nullary parent/visible/reverse counts. Independent finite literal map does not evaluate arbitrary CQ. |
| ownership | Owns fixed physical set/Counters/survivor sets and expected card list; report borrowed. |
| failure | Assertion/distribution/scalar/lookup errors propagate. |
| cost | Fixed four-row construction plus each component ranking/decoding; returned None, no engine execution. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 113–117](../../../../../tools/support/check_statistics_reports.py#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RATIOS = ("input_share", "events_per_input", "crossing_fraction", "adapter_selectivity")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name four workload ratio fields checked for exact/sampled/unavailable observations. |
| inputs / outputs | RATIOS tuple read by semantics and finite assertions. |
| invariants | Availability derives from saturation/sample observations, not a proof of a future cost model. |
| ownership | Module owns immutable tuple/string labels. |
| failure | Import allocation failure only. |
| cost | Fixed four-element setup/iteration. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 118–211](../../../../../tools/support/check_statistics_reports.py#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def semantics(report):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check owner/epoch/configuration, saturation/missingness, limits and workload-population consistency. |
| inputs / outputs | One schema-shaped statistics report in; None after O07/C01/boundary/comparison/session predicates. |
| invariants | Released owners retain no native state values; pending state identified private. Exact/sampled/lower-bound ratios, histogram sums/top-K order, memory component sums and current/foreign owner stamps checked. Scalar equality limits remain as in native_row. |
| ownership | Borrows DOM; owns sorted multiplicity/ordering lists and temporary decoded keys/diagnostics. |
| failure | Bare AssertionError or malformed key/type/scalar/OOM errors propagate; no broad rejection handler here. |
| cost | Scans all summary metrics/components/cells, sorts histogram/top-K order and decodes keys; proportional to exported diagnostic graph, no native source traversal. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 214–220](../../../../../tools/support/check_statistics_reports.py#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def find_cell(report, role, operation="insert", node=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate one exact initiating-table/operation/role/node statistics cell for fixture assertions. |
| inputs / outputs | Report, role, optional operation defaultinsert and node defaultNone in; existing unique cell object out. |
| invariants | Initiating table fixed1; exactly one match required. Lookup does not create/authorize a new cell. |
| ownership | Owns temporary matching-reference list, returns alias to original report cell. |
| failure | AssertionError on zero/multiple matches; key/type/OOM errors propagate. |
| cost | O(all cells) scan and O(matches) temporary references. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 223–351](../../../../../tools/support/check_statistics_reports.py#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate frozen legacy bytes and a finite native statistics corpus with schema/semantic/mutation checks. |
| inputs / outputs | --schema/--fixtures/--legacy and testing variant in; reports finite pass/mutation counts and installed jsonschema version. |
| invariants | Checks current schema with FormatChecker, unchanged legacy payloads, lifecycle/sample/cap/generalized/literal/raw-scalar controls and transport item counts. Negative mutations cover selected fields, not arbitrary schema completeness. |
| ownership | Owns schema validator, full named report map, text/legacy bytes and deep mutation graphs; no native subprocess in checker. |
| failure | IO/schema/assert/decode errors propagate; nested reject counts only expected schema/assert rejection, unexpected failures surface. |
| cost | Full corpus JSON/schema/semantic/literal scans, repeated deep-copy mutations and revalidation, retained report maps; explicit offline memory/CPU cost. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
def reject(original, change):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one deliberate statistics mutation to fail schema or semantic validation. |
| inputs / outputs | Fixture name and mutation callback in; deep-clones chosen report, applies callback and validates; increments captured rejected count on expected failure. |
| invariants | Only jsonschema.ValidationError/AssertionError count as expected rejection; normal success raises AssertionError. Not native fault injection. |
| ownership | Owns full mutant clone; original reports unchanged; callback can allocate/mutate clone. |
| failure | Unexpected mutation/validation errors propagate; accepted mutant explicitly fails checker. |
| cost | O(report graph) deepcopy plus full schema/semantic validation per negative control. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 352–355](../../../../../tools/support/check_statistics_reports.py#L352); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the statistics offline checker only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No outer catch; wrapper retains failed corpus and rethrows. |
| cost | Fixed guard plus full allocating diagnostic main. |
| Design | [tools/support/check_statistics_reports.py](../../../../../tools/support/check_statistics_reports.py), [tools/verify_statistics_reports.py](../../../../../tools/verify_statistics_reports.py), [docs/statistics.md](../../../../statistics.md), [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |
