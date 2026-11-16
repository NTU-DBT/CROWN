# `tools/support/check_cursor_reports.py` — block usage map

[Source](../../../../../tools/support/check_cursor_reports.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `696d04fde786f14fc639830a661adeaa7a59cb2537f8272d18974100929afabb`. 261 lines partitioned into 19 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tools/support/check_cursor_reports.py#L1) | Imports dependencies. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 11–46](../../../../../tools/support/check_cursor_reports.py#L11) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 47–55](../../../../../tools/support/check_cursor_reports.py#L47) | Module statements. |  · [reviewed contract](#b0003) |
| [B0004 · 56–57](../../../../../tools/support/check_cursor_reports.py#L56) | Callable definition: def fail(message: str) -&gt; None: | calls ValueError · [reviewed contract](#b0004) |
| [B0005 · 58–59](../../../../../tools/support/check_cursor_reports.py#L58) | Explanatory comments or spacing. |  |
| [B0006 · 60–62](../../../../../tools/support/check_cursor_reports.py#L60) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls fail; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0006) |
| [B0007 · 63–64](../../../../../tools/support/check_cursor_reports.py#L63) | Explanatory comments or spacing. |  |
| [B0008 · 65–66](../../../../../tools/support/check_cursor_reports.py#L65) | Callable definition: def integer(value: object, label: str) -&gt; None: | calls require, type; guard require(type(value) is int and value &gt;= 0, f"{label} must be a nonnegative integer") · [reviewed contract](#b0008) |
| [B0009 · 67–68](../../../../../tools/support/check_cursor_reports.py#L67) | Explanatory comments or spacing. |  |
| [B0010 · 69–80](../../../../../tools/support/check_cursor_reports.py#L69) | Callable definition: def check_metric(metric: object, label: str) -&gt; None: | calls require, isinstance, get, integer; guard require(isinstance(metric, dict), f"{label} must be an object") · [reviewed contract](#b0010) |
| [B0011 · 81–83](../../../../../tools/support/check_cursor_reports.py#L81) | Module statements. | source comment (unverified): # Required counters are a subset check; additional work fields are permitted here. · [reviewed contract](#b0011) |
| [B0012 · 84–96](../../../../../tools/support/check_cursor_reports.py#L84) | Callable definition: def check_work(work: object, label: str) -&gt; None: | calls require, isinstance, keys, integer; guard require(isinstance(work, dict), f"{label} must be an object"); 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 97–98](../../../../../tools/support/check_cursor_reports.py#L97) | Explanatory comments or spacing. |  |
| [B0014 · 99–186](../../../../../tools/support/check_cursor_reports.py#L99) | Callable definition: def check_cursor(report: object, label: str) -&gt; None: | calls require, isinstance, get, integer; guard require(isinstance(report, dict), f"{label} report must be an object"); 5 loop sites · [reviewed contract](#b0014) |
| [B0015 · 187–188](../../../../../tools/support/check_cursor_reports.py#L187) | Explanatory comments or spacing. |  |
| [B0016 · 189–220](../../../../../tools/support/check_cursor_reports.py#L189) | Callable definition: def check_gauge(report: object, label: str) -&gt; None: | calls require, isinstance, get, integer; guard require(isinstance(report, dict), f"{label} report must be an object"); 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 221–222](../../../../../tools/support/check_cursor_reports.py#L221) | Explanatory comments or spacing. |  |
| [B0018 · 223–257](../../../../../tools/support/check_cursor_reports.py#L223) | Callable definition: def main() -&gt; int: | calls len, print, Path, loads; guard require(isinstance(document, dict), "top-level output must be an object"); returns 2; 1; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 258–261](../../../../../tools/support/check_cursor_reports.py#L258) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0019) |

## B0001

[Lines 1–10](../../../../../tools/support/check_cursor_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the offline cursor/committed-gauge fixture checker and fixed protocol registries. |
| inputs / outputs | Imports stdlib and defines package hash, cursor metric/source/state/reason/availability registries; guarded main reads one JSON file. |
| invariants | Checks selected structure/semantics, not a closed JSON schema, native authority factory or full output-spooling account. Package hash is fixture metadata. |
| ownership | Owns lists/sets/strings and parsed DOMs; no native process started. |
| failure | Import errors propagate; explicit ValueError checks remain active under -O. |
| cost | Fixed registry allocation; later scans are explicit offline work. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–46](../../../../../tools/support/check_cursor_reports.py#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PACKAGE_SHA256 = "5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare PACKAGE_SHA256 for cursor fixture validation. |
| inputs / outputs | Expected frozen cursor package identity string. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
CURSOR_NAMES = [
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare CURSOR_NAMES for cursor fixture validation. |
| inputs / outputs | Twelve ordered metric names, first five timing and seven count units. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
CURSOR_SOURCES = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare CURSOR_SOURCES for cursor fixture validation. |
| inputs / outputs | Five admitted native cursor source labels. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
CURSOR_STATES = {"active", "exhausted", "cancelled", "failed"}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare CURSOR_STATES for cursor fixture validation. |
| inputs / outputs | Four recorded cursor lifetime states. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
TERMINAL_REASONS = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare TERMINAL_REASONS for cursor fixture validation. |
| inputs / outputs | Nine admitted explicit terminal reason labels. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
AVAILABILITY = {"unavailable", "disabled", "available"}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare AVAILABILITY for cursor fixture validation. |
| inputs / outputs | Unavailable/disabled/available metric states. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
UNAVAILABLE_GAUGES = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare UNAVAILABLE_GAUGES for cursor fixture validation. |
| inputs / outputs | Six unsupported total/memory/durable gauge labels. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 47–55](../../../../../tools/support/check_cursor_reports.py#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"full_result_count",
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare UNAVAILABLE_GAUGES continuation for cursor fixture validation. |
| inputs / outputs | Complete the same six-element unsupported gauge registry across the saved fixed declaration boundary. Used for exact membership/order checks, not state mutation. |
| invariants | Labels express report protocol only; unavailable totals remain None, not measured zero. |
| ownership | Module owns corresponding list/set/string backing; immutable labels reused. |
| failure | Import allocation failure; unexpected fixture values fail later. |
| cost | Fixed-size registry storage; membership expected O(1) for sets and short list traversal where used. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 56–57](../../../../../tools/support/check_cursor_reports.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fail(message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise an explicit cursor-check failure with caller diagnostic. |
| inputs / outputs | Diagnostic string in; never returns normally. |
| invariants | ValueError signals rejection, not a partial accepted report. |
| ownership | Exception retains diagnostic string. |
| failure | Always raises ValueError; no catch/rollback. |
| cost | Exception allocation/traceback only. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 60–62](../../../../../tools/support/check_cursor_reports.py#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 65–66](../../../../../tools/support/check_cursor_reports.py#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer(value: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a strict nonnegative Python integer, excluding bool. |
| inputs / outputs | Value and field label in; None on type(value)is int and value&gt;=0. |
| invariants | No uint64 upper bound here; this checker is selected semantic structure, not schema substitute. |
| ownership | Borrows value, owns formatted diagnostic. |
| failure | Explicit ValueError on rejection; type conversion is not attempted. |
| cost | Fixed type/sign checks; label formatting proportional to label length. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 69–80](../../../../../tools/support/check_cursor_reports.py#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_metric(metric: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check availability-dependent cursor metric value/saturation shape. |
| inputs / outputs | Metric object and label in; verifies dict, known availability, available nonnegative integer+bool or unavailable/disabled null/null. |
| invariants | Missing/unknown values reject; no native timing collected and no assumption unavailable equals0. |
| ownership | Borrows DOM; only diagnostics/lookup temporaries allocated. |
| failure | Explicit ValueError on stated predicates; unexpected object behavior can propagate. |
| cost | Fixed number of field checks and short label strings. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 81–83](../../../../../tools/support/check_cursor_reports.py#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L83:sha256:65b2b3c9b30012874da96ac4988303b5c6251e6ddc039d466b94de5616ec9cfe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Required counters are a subset check; additional work fields are permitted here. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 84–96](../../../../../tools/support/check_cursor_reports.py#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_work(work: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the24 named nonnegative cursor work counters. |
| inputs / outputs | Work dict and label in; None after required subset and strict integer checks. |
| invariants | Additional fields are permitted by required&lt;=keys; no closed-object claim or sum across overlapping counters. |
| ownership | Owns fixed required-name set each call; work DOM borrowed. |
| failure | ValueError for missing/bad counters; key/type errors propagate. |
| cost | O(24) checks/diagnostic strings and fresh small set; no native update work. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 99–186](../../../../../tools/support/check_cursor_reports.py#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_cursor(report: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one cursor-lifetime report's IDs, configuration, metrics, cleanup and work scopes. |
| inputs / outputs | Report object and case label in; explicit checks for format/version, owner/sequence, source/view/side/state/options and twelve exact metric registry entries. |
| invariants | Off mode keeps ID/config disabled; startup failure has failed unconstructed state/appropriate cleanup unavailability. Total/max/cleanup and five work buckets have declared nonadditive scope; no delta spool attribution. |
| ownership | Borrows nested report; owns expected name/unit lists and diagnostic strings, no state changes. |
| failure | ValueError via explicit checks, ordinary missing/bad object access can propagate; no universal malformed-shape catch here. |
| cost | Bounded configuration/12-metric/five-bucket checks with work scans; allocating offline validation, not hot cursor hooks. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 189–220](../../../../../tools/support/check_cursor_reports.py#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_gauge(report: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate explicit committed per-node/base gauges and unsupported totals. |
| inputs / outputs | Gauge report/case label in; checks owner/sequence/scope, native/generalized node and base counts, six unavailable total/memory/durable fields. |
| invariants | Per-node E counts are not full query result cardinality; unavailable allocations/durable metrics remain null with reasons. |
| ownership | Borrows DOM; owns diagnostic strings and small iteration temporaries. |
| failure | ValueError on check failure; malformed nested types/keys may propagate. |
| cost | O(base+node entries) selected field scans and six unsupported gauges; no native state traversal by checker. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 223–257](../../../../../tools/support/check_cursor_reports.py#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one frozen-package cursor corpus and check all cursor/gauge cases. |
| inputs / outputs | Exactly one JSON path argument; verifies fixture format/revision/package hash, positive check count and nonempty case maps; returns0/1/2. |
| invariants | Does not reject duplicate JSON keys through a hook and is not a full JSONschema checker. No subprocess/network or producer advancement. |
| ownership | Owns complete JSON DOM/case iteration; caller owns corpus file. |
| failure | Catches OSError/UnicodeError/JSONDecodeError/ValueError/KeyError into FAIL return1; usage2, other malformed-type errors may escape. |
| cost | Whole-file read/parse and all selected report/gauge scans; process memory outside native account. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 258–261](../../../../../tools/support/check_cursor_reports.py#L258); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the cursor offline checker only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Returns SystemExit(main result); main handles its declared narrow failure set only. |
| cost | Fixed guard plus whole-corpus validation. |
| Design | [tools/support/check_cursor_reports.py](../../../../../tools/support/check_cursor_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |
