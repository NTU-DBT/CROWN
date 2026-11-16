# `tools/support/check_composed_reports.py` — block usage map

[Source](../../../../../tools/support/check_composed_reports.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `40b3016556fe425a29250d2ad1d221812cfc925a27c5492af797a16035fafefd`. 178 lines partitioned into 22 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tools/support/check_composed_reports.py#L1) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 10–13](../../../../../tools/support/check_composed_reports.py#L10) | Callable definition: def artifact_context(path): | calls AssertionError · [reviewed contract](#b0002) |
| [B0003 · 14–19](../../../../../tools/support/check_composed_reports.py#L14) | Callable definition: def unique(pairs): | calls ; returns d; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tools/support/check_composed_reports.py#L20) | Callable definition: def load(p):return json.loads(p.read_text(encoding='utf-8'),object_pairs_hook=unique,parse_constant=lambda x:(_ for _ in ()).thro… | calls loads, read_text, in, throw; returns json.loads(p.read_text(encoding='utf-8'),object_pairs_hook=unique,parse_constant=lambda x:(_ for _ …; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tools/support/check_composed_reports.py#L21) | Callable definition: def eq(a,b):assert a==b,(a,b) | calls  · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../tools/support/check_composed_reports.py#L22) | Callable definition: def val(x):return None if x=='null' else int(x) | calls int; returns None if x=='null' else int(x) · [reviewed contract](#b0006) |
| [B0007 · 23–23](../../../../../tools/support/check_composed_reports.py#L23) | Callable definition: def enum(names,x):return names\[int(x)\] | calls int; returns names\[int(x)\] · [reviewed contract](#b0007) |
| [B0008 · 24–24](../../../../../tools/support/check_composed_reports.py#L24) | Callable definition: def unhex(x):return None if x=='null' else '' if x=='-' else bytes.fromhex(x).decode('utf-8') | calls fromhex, decode; returns None if x=='null' else '' if x=='-' else bytes.fromhex(x).decode('utf-8') · [reviewed contract](#b0008) |
| [B0009 · 25–26](../../../../../tools/support/check_composed_reports.py#L25) | Callable definition: def metric(m,raw): | calls map, eq, bool · [reviewed contract](#b0009) |
| [B0010 · 27–29](../../../../../tools/support/check_composed_reports.py#L27) | Callable definition: def options(x): | calls len, dict, enum, val; returns dict(mode=enum(MODE,x\[0\]),completion=enum(COMP,x\[1\]),live_maintenance=enum(LIVE,x\[2\]),view=enum(VIE… · [reviewed contract](#b0010) |
| [B0011 · 30–31](../../../../../tools/support/check_composed_reports.py#L30) | Callable definition: def flat_options(x): | calls options, dict; returns dict(requested_mode=v\['mode'\],requested_completion=v\['completion'\],live_maintenance=v\['live_mainten… · [reviewed contract](#b0011) |
| [B0012 · 32–38](../../../../../tools/support/check_composed_reports.py#L32) | Callable definition: def configuration(c,x,cursor=False): | calls eq, len, int, bool; returns assert len(x)==28,x · [reviewed contract](#b0012) |
| [B0013 · 39–43](../../../../../tools/support/check_composed_reports.py#L39) | Callable definition: def initialization(c,x): | calls eq, enum, dict, val; returns eq(c\['route'\],enum(\['empty_constructor','initialized_database','rebuilt_snapshot'\],x\[0\])) · [reviewed contract](#b0013) |
| [B0014 · 44–47](../../../../../tools/support/check_composed_reports.py#L44) | Callable definition: def labels(c,x): | calls eq, zip, unhex; returns eq(c\['authority'\],'none'); 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 48–53](../../../../../tools/support/check_composed_reports.py#L48) | Callable definition: def tree_node(x): | calls list, map, range, pop; returns dict(id=int(ident),label=unhex(label),kind=enum(KIND,kind),occurrence=val(occ),scope=arrays\[0\],chil…; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 54–54](../../../../../tools/support/check_composed_reports.py#L54) | Module statements. | source comment (unverified): # Sidecars test native export fidelity; this does not independently replay a height proof. · [reviewed contract](#b0016) |
| [B0017 · 55–138](../../../../../tools/support/check_composed_reports.py#L55) | Callable definition: def check_native(d,tree,lines): | calls split, eq, int, enum; growth insert; 10 loop sites; source comment (unverified): # Native/public shape consistency, without converting unsupported facts to zero. · [reviewed contract](#b0017) |
| [B0018 · 139–139](../../../../../tools/support/check_composed_reports.py#L139) | Explanatory comments or spacing. |  |
| [B0019 · 140–152](../../../../../tools/support/check_composed_reports.py#L140) | Callable definition: def schemas(schema_dir): | calls load, check_schema, closed, isinstance; returns result; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 153–153](../../../../../tools/support/check_composed_reports.py#L153) | Explanatory comments or spacing. |  |
| [B0021 · 154–177](../../../../../tools/support/check_composed_reports.py#L154) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, is_absolute; guard assert (args.directory/'structural-negative.query.json').exists(); 7 loop sites; source comment (unverified): # Each native node/edge appears once in the bounded DOT tree rendering. · [reviewed contract](#b0021) |
| [B0022 · 178–178](../../../../../tools/support/check_composed_reports.py#L178) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0022) |

## B0001

[Lines 1–9](../../../../../tools/support/check_composed_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define offline closed-schema/native-sidecar checks for composed EXPLAIN corpora. |
| inputs / outputs | Imports installed jsonschema and stdlib; defines sidecar enum registries/paths; CLI is guarded and never starts native producers. |
| invariants | Standalone defaults resolve the maintained repository and schemas from this script location, independent of cwd; explicit wrapper overrides remain supported. Synthetic/sidecar transport is finite export evidence, not typed proof manufacture. |
| ownership | Owns module registry lists/strings/Paths; parsed reports/sidecars/mutants are ordinary Python memory. |
| failure | Import failures propagate; most checks use bare assert, requiring normal assertions-enabled invocation as CMake does. |
| cost | Fixed registry/import setup; later validation scans full corpus and DOMs, no runtime hot-hook overhead. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
ROOT=Path(__file__).resolve().parents[2]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the maintained repository for standalone checker defaults. |
| inputs / outputs | ROOT is the repository two parent edges above tools/support/check_composed_reports.py; main defaults repo-root and schema-dir to ROOT and ROOT/schemas. |
| invariants | Path choice follows the script location, not cwd. Explicit absolute schema paths and schema paths relative to supplied repo-root remain accepted. |
| ownership | Module owns Path values; no files opened. |
| failure | Path resolution/OOM failures propagate at import. |
| cost | Fixed path resolution/parent operations, no recursive scan. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
MODE=['maintenance','delta'];COMP=['automatic','ordered_replay','anchored','root_first'];LIVE=['on_output','incremental','eager'];VIEW=['core','sql'];OBS=['off','counters','timed','trace'];AVAIL=['unavailable','disabled','available'];KIND=['native','generalized'];TRACE=['disabled','not_sampled','pending','committed','aborted','released'];TK=['begin','source_change','alias','native_event','child_enqueued','child_applied','journal','reverse_visit','core_result','mapped_record','prepared','drain','commit','abort','transferred','discarded','serialization_attempt','serialization_success','serialization_failure','sink_attempt','sink_success','sink_failure','acknowledged']
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native sidecar enum indices to exact report labels and trace kind order. |
| inputs / outputs | MODE/COMP/LIVE/VIEW/OBS/AVAIL/KIND/TRACE/TK lists retained; enum and dispatch use index order. |
| invariants | Index ordering is a local protocol with the native fixture, not arbitrary DTO authority; enum helper assumes trusted valid indices. |
| ownership | Owning lists and immutable string labels; no native handle. |
| failure | Allocation failure on import; bad sidecar indices fail or Python-negative-index select later. |
| cost | Fixed registry storage, subsequent list index O(1). |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
OUTPUT=['discard_drain_requested','completion_drain_invoked','retention_disabled','prepared','published','released','transferred','serialization_invoked','sink_invoked','unread_discarded']
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | List ten native output-publication/delivery flags in sidecar order. |
| inputs / outputs | OUTPUT labels read in check_native comparisons. |
| invariants | Flags report observed lifecycle, do not authorize IO, sink delivery or durable publication themselves. |
| ownership | Owns list/strings. |
| failure | Import allocation failure only. |
| cost | Fixed ten-element allocation; comparison later visits ten flags. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–13](../../../../../tools/support/check_composed_reports.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def artifact_context(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach the failing artifact path while preserving the original validation cause. |
| inputs / outputs | Contextmanager path in; yields once, returns normally or raises AssertionError(path:error) from caught Exception. |
| invariants | Narrow diagnostic translation around offline per-artifact checks; does not retry, advance producers or undo file writes. |
| ownership | Retains path and exception cause/traceback on failure; wrapped work owns its own data. |
| failure | Catches Exception only, leaving BaseException/SystemExit interrupts unwrapped; str/AssertionError allocation failure may replace diagnostic. |
| cost | Constant context setup, exception formatting only on failure; no report traversal in wrapper. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 14–19](../../../../../tools/support/check_composed_reports.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def unique(pairs):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a JSON object while rejecting duplicate keys. |
| inputs / outputs | object_pairs_hook list of key/value pairs in; new dict out. |
| invariants | Uses assert key not in dict, so duplicate rejection requires assertions enabled. Values remain parsed JSON objects. |
| ownership | Owns dict, aliases already parsed nested values; no deep copy. |
| failure | AssertionError on duplicate; type/hash/OOM failures propagate. |
| cost | Expected O(pairs) hash insertion, O(keys) dict storage. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–20](../../../../../tools/support/check_composed_reports.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load(p):return json.loads(p.read_text(encoding='utf-8'),object_pairs_hook=unique,parse_constant=lambda x:(_ for _ in ()).throw(AssertionError(x)))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a complete UTF8 JSON artifact with duplicate/nonfinite rejection. |
| inputs / outputs | Path in; parsed JSON graph out using unique hook and parse_constant raising AssertionError. |
| invariants | Reads whole file, not a streaming/resource-granted parser; duplicate guard depends on assertions. |
| ownership | Owns full text temporary and complete nested DOM. |
| failure | IO/UTF8/JSON/duplicate/nonfinite/OOM errors propagate into artifact context when called there. |
| cost | O(file bytes) read/parse plus key dictionaries; full DOM allocation. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 21–21](../../../../../tools/support/check_composed_reports.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def eq(a,b):assert a==b,(a,b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert exact Python equality for a native-sidecar/export field pair. |
| inputs / outputs | Two values in; None on equality or AssertionError tuple diagnostic. |
| invariants | Bare assert requires normal Python; Python numeric equality is used, schema supplies additional scalar constraints where applied. |
| ownership | Values borrowed; failure tuple/exception retain them. |
| failure | AssertionError only when enabled and unequal; arbitrary equality errors propagate. |
| cost | O(compared structure) in general; constant for scalar enum/counter cases. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 22–22](../../../../../tools/support/check_composed_reports.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def val(x):return None if x=='null' else int(x)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the sidecar nullable integer spelling. |
| inputs / outputs | String null or integer literal in; None/int out. |
| invariants | No uint64/range check here; producer/schema constrain expected fields. |
| ownership | Owns parsed big integer where needed; input borrowed. |
| failure | ValueError/type/OOM propagate. |
| cost | O(decimal digits) integer parsing; fixed null branch. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 23–23](../../../../../tools/support/check_composed_reports.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def enum(names,x):return names[int(x)]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate one trusted native ordinal through a local enum registry. |
| inputs / outputs | Label list and integer string in; existing label out. |
| invariants | No explicit nonnegative/bounds guard; normal Python index rules apply. Sidecar is trusted fixture output and later expected fields are compared. |
| ownership | Borrows registry; returns retained immutable label. |
| failure | Int parsing/IndexError/type errors propagate; negative indices are not rejected here. |
| cost | O(digits) parse plus O(1) list access. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 24–24](../../../../../tools/support/check_composed_reports.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def unhex(x):return None if x=='null' else '' if x=='-' else bytes.fromhex(x).decode('utf-8')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode nullable/empty/hex UTF8 sidecar label text. |
| inputs / outputs | null -&gt;None, dash -&gt;empty string, otherwise hex bytes decoded UTF8. |
| invariants | Hex encoding preserves labels including embedded bytes until strict UTF8 decode; no arbitrary nonUTF8 string admission. |
| ownership | Owns decoded bytes/string temporaries; sentinel results immutable. |
| failure | Invalid hex/UTF8/type/OOM errors propagate. |
| cost | O(hex text bytes) parse and UTF8 decode with full intermediates. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 25–26](../../../../../tools/support/check_composed_reports.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def metric(m,raw):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a report metric against its sidecar availability/value/saturation triple. |
| inputs / outputs | Metric DOM and exactly three integer strings in; assertions on mapped availability and nullable value/saturation. |
| invariants | Only available index2 exposes value/bool saturation; unavailable/disabled must be None. Protocol/schema, not a measurement taken by checker. |
| ownership | Borrows DOM; owns parsed ints/map iterator only. |
| failure | Unpack/int/index/AssertionError failures propagate. |
| cost | Fixed three-field parsing/comparison; no native clock read. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 27–29](../../../../../tools/support/check_composed_reports.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def options(x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the20-field native requested-options sidecar into nested report-shaped options. |
| inputs / outputs | Exactly20 strings in; owning nested mode/completion/live/view/grants/physical/support/observation dict out. |
| invariants | Assertions check width; null work limits remain None. Requested configuration records are not engine defaults or runtime authority. |
| ownership | Owns nested dicts/ints; labels borrow registry immutable strings. |
| failure | Width assert/int/enum/IndexError/OOM errors propagate. |
| cost | Fixed20 fields and bounded dict allocations, no native validation/process. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 30–31](../../../../../tools/support/check_composed_reports.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def flat_options(x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reshape decoded requested options to the cursor flat configuration field names. |
| inputs / outputs | 20-field raw options in; owning flat dict with nested observation object out. |
| invariants | Preserves requested grants, renames fields for cursor report; no mode resolution or mutation of native state. |
| ownership | Owns decoded options then flat dict; observation nested dict retained from temporary decoded graph. |
| failure | options/type/key/OOM failures propagate. |
| cost | Fixed-width decode plus field assignments, several small owning dictionaries. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 32–38](../../../../../tools/support/check_composed_reports.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def configuration(c,x,cursor=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one retained current/begin configuration to native owner/generation/options fields. |
| inputs / outputs | Report configuration, sidecar list and cursor flag in; checks null or28 fields and appropriate nested/flat request mapping. |
| invariants | Owner/generation/saturated stamps and requested/resolved modes retained from actual producer; guarantee prose must be explicit not copied current profile. |
| ownership | Borrows report; owns decoded temporary options/ints. |
| failure | Assertion/shape/int/lookup failures propagate; no report mutation. |
| cost | Fixed28 fields with options allocations and structural equality proportional to bounded configuration size. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 39–43](../../../../../tools/support/check_composed_reports.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def initialization(c,x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare initialization route and optional applied-build choice against native accessors. |
| inputs / outputs | Report object or None, raw sidecar route/build fields in; checks empty/initialized/rebuilt route and optional direct/replay grant. |
| invariants | Null applied build remains None; does not rebuild data or infer actual build work from label. |
| ownership | Borrows report; owns small expected dict/ints. |
| failure | Assertion/index/int failures propagate. |
| cost | Fixed few-field parsing/comparison. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 44–47](../../../../../tools/support/check_composed_reports.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def labels(c,x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare four caller-declared unmeasured labels without granting authority. |
| inputs / outputs | Report labels or None and raw label strings in; asserts authority none/provenance caller_declared_unmeasured and exact decoded values. |
| invariants | Uses strict zip length; caller labels never become measured source/codec/sink identities by being present. |
| ownership | Borrows report; owns decoded UTF8 strings. |
| failure | Assertion/strict-zip/hex/UTF8 errors propagate. |
| cost | Four label decodes/comparisons, O(total label bytes) allocation. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 48–53](../../../../../tools/support/check_composed_reports.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def tree_node(x):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one sidecar node with three length-prefixed arrays and final connex flag. |
| inputs / outputs | Native node token list in; id/label/kind/occurrence/scope/children/separator/connex dict out. |
| invariants | Requires one remaining flag after consuming arrays; assumes producer lengths are sensible, not a complete hostile stream validator or tree proof. |
| ownership | Owns rest integer list, sliced arrays and result dict; labels decoded independently. |
| failure | Malformed lengths/int/index/assert errors propagate; no native node mutation. |
| cost | O(tokens) parse plus pop(0)/del/slices shifting list elements for three arrays; full node copy allocation. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 54–54](../../../../../tools/support/check_composed_reports.py#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:8a864252fb47ba5a2575d8eb465905d50f94fd3b155c58065daa09cee27852dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Sidecars test native export fidelity; this does not independently replay a height proof. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 55–138](../../../../../tools/support/check_composed_reports.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_native(d,tree,lines):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare composed report/tree exports and lifecycle observations to native fixture sidecar accessors. |
| inputs / outputs | Report/tree DOMs and native .expected lines in; checks all supported tags and final cross-record/tree/trace/gauge/count identities. |
| invariants | Dispatch covers plan/config/runtime/session/window/cursor/output/work/observations and explicit unavailable totals. Unknown tags fail; this checks typed-export fidelity, not independent algorithm replay, exact cost model or durable delivery proof. |
| ownership | Borrows report/tree; owns parsed row/node/base/trace/metric ID arrays and temporary expected dictionaries; no source producer advancement. |
| failure | Assertion/KeyError/ValueError/decode errors propagate; unknown tag explicitly raises. No broad suppression. |
| cost | Full sidecar scan with list/dict construction and repeated structural comparisons, tree/DOT-related exported arrays and registry traversals; no native hot-path cost. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 140–152](../../../../../tools/support/check_composed_reports.py#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def schemas(schema_dir):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load and meta-validate the two current closed EXPLAIN V2 schemas with internal-reference restrictions. |
| inputs / outputs | Schema directory in; report/tree Draft202012Validator pair out. |
| invariants | Recursive closed rejects property-bearing object schemas without additionalProperties False and every noninternal $ref; this is limited structural closure checking, not arbitrary JSONschema semantic certification. |
| ownership | Owns both complete parsed schema DOMs and validator objects retaining them. |
| failure | IO/JSON/metaschema/assert/recursion/OOM errors propagate before report checks. |
| cost | Two full schema reads/meta-validations plus recursive dict/list walk; retains complete schema graphs. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

```text
def closed(v):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce local schema-closure/reference conventions recursively. |
| inputs / outputs | Captured schema name plus any schema subtree in; None or assertion failure. |
| invariants | Only property-bearing object declarations checked; $ref must start #/. This does not validate every possible schema pattern or fetch anything. |
| ownership | Borrows subtree, recursive frames; no mutation. |
| failure | Bare assert failures/recursion limit propagate. |
| cost | O(schema value graph) recursive traversal with depth-proportional stack. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 154–177](../../../../../tools/support/check_composed_reports.py#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete composed EXPLAIN corpus and optional mandatory scenario matrix. |
| inputs / outputs | Directory, --require-all, --schema-dir/--repo-root in; pass count printed after JSON/tree/native sidecar/text/DOT checks. |
| invariants | Standalone defaults and maintained wrapper both use current schemas; relative schema-dir resolves against repo-root. Requires nonempty corpus; closed-schema unknown-field negatives, exact text trace/DOT nodes/edges and infeasible query control; nine runtime scenarios require exactly four observation modes each. |
| ownership | Owns parsed validators/corpus artifacts, names/mode/count sets and regex lists; no subprocess or network. |
| failure | Per-artifact Exception wrapped with path; absent scenarios/assert/schema/parse failures abort. No retained-artifact cleanup here because wrapper owns directory. |
| cost | Glob/sort and full file/DOM/schema/sidecar scans, mutation dict validation and text/DOT regex comparisons; explicit allocating offline diagnostics. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 178–178](../../../../../tools/support/check_composed_reports.py#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the composed offline checker only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No outer catch; path-wrapped or ordinary failures retain traceback/nonzero status; caller wrapper retains failed corpus. |
| cost | Guard fixed, full offline main cost. |
| Design | [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [tools/verify_observability_reports.py](../../../../../tools/verify_observability_reports.py), [docs/observability.md](../../../../observability.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/code_review.md](../../../../code_review.md) |
