# `tools/generate_workloads.py` — block usage map

[Source](../../../../tools/generate_workloads.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `b3a7dcc0df3a5ec44a6e88cacbfa41379e77e63315a64e969c48a8d17a5cc598`. 358 lines partitioned into 29 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../tools/generate_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–21](../../../../tools/generate_workloads.py#L20) | Callable definition: def canonical(value): | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(',', ':')) · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../tools/generate_workloads.py#L22) | Explanatory comments or spacing. |  |
| [B0004 · 24–25](../../../../tools/generate_workloads.py#L24) | Callable definition: def sha(data): | calls sha256, hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../tools/generate_workloads.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–29](../../../../tools/generate_workloads.py#L28) | Callable definition: def quote(identifier): | calls replace; returns '"' + identifier.replace('"', '""') + '"' · [reviewed contract](#b0006) |
| [B0007 · 30–31](../../../../tools/generate_workloads.py#L30) | Explanatory comments or spacing. |  |
| [B0008 · 32–33](../../../../tools/generate_workloads.py#L32) | Callable definition: def ordered(values): | calls sorted; returns sorted(values, key=canonical) · [reviewed contract](#b0008) |
| [B0009 · 34–35](../../../../tools/generate_workloads.py#L34) | Explanatory comments or spacing. |  |
| [B0010 · 36–51](../../../../tools/generate_workloads.py#L36) | Callable definition: def acyclic(edges): | calls set, next, enumerate, any; returns False; True; 9 loop sites · [reviewed contract](#b0010) |
| [B0011 · 52–53](../../../../tools/generate_workloads.py#L52) | Explanatory comments or spacing. |  |
| [B0012 · 54–95](../../../../tools/generate_workloads.py#L54) | Callable definition: def query(identifier, scopes, head=None, *, tables=None, tags=(), hot=(), text=False, | calls list, fromkeys, range, len; returns {'id': identifier, 'atoms': atoms, 'variables': variables, 'head': list(head),; 11 loop sites; source comment (unverified): # No grouping keys; the output expression is recorded below. · [reviewed contract](#b0012) |
| [B0013 · 96–97](../../../../tools/generate_workloads.py#L96) | Explanatory comments or spacing. |  |
| [B0014 · 98–126](../../../../tools/generate_workloads.py#L98) | Callable definition: def specifications(): | calls range, query, path, star; returns \[; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 127–128](../../../../tools/generate_workloads.py#L127) | Explanatory comments or spacing. |  |
| [B0016 · 129–148](../../../../tools/generate_workloads.py#L129) | Callable definition: def pool(spec, scale): | calls range, index, append, tuple; returns result; 4 loop sites; source comment (unverified): # One physical loop reaches every alias in the same epoch. · [reviewed contract](#b0016) |
| [B0017 · 149–150](../../../../tools/generate_workloads.py#L149) | Explanatory comments or spacing. |  |
| [B0018 · 151–191](../../../../tools/generate_workloads.py#L151) | Callable definition: def trace(spec, regime, seed, scale): | calls pool, items, sorted, index; returns events; growth insert; 17 loop sites; source comment (unverified): # Interleave physical tables so prefixes exercise empty/dangling branches. · [reviewed contract](#b0018) |
| [B0019 · 192–193](../../../../tools/generate_workloads.py#L192) | Explanatory comments or spacing. |  |
| [B0020 · 194–213](../../../../tools/generate_workloads.py#L194) | Callable definition: def relational(spec, database): | calls dict, zip, append, len; returns \[(len(assignments),)\]; \[(bool(assignments),)\]; 6 loop sites · [reviewed contract](#b0020) |
| [B0021 · 214–215](../../../../tools/generate_workloads.py#L214) | Explanatory comments or spacing. |  |
| [B0022 · 216–248](../../../../tools/generate_workloads.py#L216) | Callable definition: def oracle(spec, events): | calls set, connect, join, quote; returns ordered(expected); {'schema_version': 1, 'query': spec\['id'\], 'oracle': 'independent_relational_and…; growth insert; 9 loop sites · [reviewed contract](#b0022) |
| [B0023 · 249–250](../../../../tools/generate_workloads.py#L249) | Explanatory comments or spacing. |  |
| [B0024 · 251–264](../../../../tools/generate_workloads.py#L251) | Callable definition: def verify_regime(events, regime): | calls defaultdict, deque, tuple, ValueError; growth insert; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 265–266](../../../../tools/generate_workloads.py#L265) | Explanatory comments or spacing. |  |
| [B0026 · 267–335](../../../../tools/generate_workloads.py#L267) | Callable definition: def build(seed=20261110, scale=1, selected=None): | calls ValueError, put, dumps, encode; returns {'path': path, 'sha256': sha(files\[path\])}; files; 13 loop sites · [reviewed contract](#b0026) |
| [B0027 · 336–337](../../../../tools/generate_workloads.py#L336) | Explanatory comments or spacing. |  |
| [B0028 · 338–354](../../../../tools/generate_workloads.py#L338) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, build; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 355–358](../../../../tools/generate_workloads.py#L355) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |

## B0001

[Lines 1–19](../../../../tools/generate_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the deterministic B02 finite workload corpus, regime/output registries and independent oracle implementation. |
| inputs / outputs | Imports stdlib including SQLite, defines seven regimes/two backends/three modes, and guarded main. |
| invariants | Generated queries/data are local finite mechanism coverage; legacy/external metadata does not authorize licenses or claim dataset reproduction. |
| ownership | Module owns registries and imported modules; later files/DOMs/SQLite state use ordinary process memory. |
| failure | Import/allocation failures precede main; no broad top-level recovery. |
| cost | Fixed import/registry allocation; importing does not generate workloads or start native processes. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 20–21](../../../../tools/generate_workloads.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordinary JSON-compatible value deterministically for this packet format. |
| inputs / outputs | JSON graph in; ensure_ascii=False, sorted-key, compact-separator Unicode JSON string out. |
| invariants | Preserves array order and JSON scalar kinds; standard json.dumps defaults still apply to unsupported/nonfinite values unless caller checks them. No native canonicalization authority. |
| ownership | Input graph borrowed; returned full serialization and encoder temporaries owned. |
| failure | JSON/type/encoding-memory errors propagate; no source mutation. |
| cost | O(serialized graph bytes) plus per-object key sorting and full output allocation. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 24–25](../../../../tools/generate_workloads.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha(data):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute SHA256 for supplied encoded bytes. |
| inputs / outputs | Bytes-compatible input; lowercase SHA256 hex output; no file IO here. |
| invariants | Digest binds exact bytes supplied, including line endings and literal spelling; it does not attest semantic correctness or build lineage. |
| ownership | Input borrowed during hashing; hash state and hex result owned. |
| failure | Invalid input/type/OOM failure propagates. |
| cost | O(input bytes) hash and fixed-size result allocation. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 28–29](../../../../tools/generate_workloads.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def quote(identifier):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote a trusted generated SQL identifier using SQLite/PostgreSQL double-quote escaping. |
| inputs / outputs | String identifier in; double-quoted string with embedded quotes doubled out. |
| invariants | Quotes identifiers, not values or complete SQL; values in oracle use parameters. |
| ownership | Owns replacement/result strings; input unchanged. |
| failure | Nonstring/type/OOM errors propagate. |
| cost | O(identifier bytes) replacement and output allocation. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 32–33](../../../../tools/generate_workloads.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ordered(values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize deterministic output order without relying on mixed-type Python tuple ordering. |
| inputs / outputs | Iterable of rows/items in; list sorted by canonical JSON encoding out. |
| invariants | Array order is deterministic by JSON spelling; canonical scalar kinds remain visible. Does not deduplicate. |
| ownership | Owns sorted list and transient key strings; contained row objects borrowed unless caller constructed them. |
| failure | JSON/comparison/OOM errors propagate. |
| cost | O(N log N) comparisons plus O(total encoded items) sort-key allocation. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 36–51](../../../../tools/generate_workloads.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def acyclic(edges):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently classify a finite hyperedge family by GYO-style reduction. |
| inputs / outputs | Iterable of variable scopes in; Boolean empty-reduction outcome out. |
| invariants | Copies scopes to sets, removes contained/equal edges and degree-one vertices until empty/fixed point. This finite classifier does not provide native P1 certificates or a complexity theorem. |
| ownership | Owns all mutable edge sets, Counters and reduced lists; input scopes unchanged. |
| failure | Unhashable/bad input/OOM errors propagate; irreducibility returns False. |
| cost | Repeated subset comparisons can be quadratic in edges per round plus set/degree scans; no constant-time or update-cost claim. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0012

[Lines 54–95](../../../../tools/generate_workloads.py#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def query(identifier, scopes, head=None, *, tables=None, tags=(), hot=(), text=False,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a catalog, direct-CQ-like spec and SQL text for one finite query family. |
| inputs / outputs | Name, variable scopes/head, optional scalar/semantics/admission/table-layout attributes in; owning spec dict out. |
| invariants | Set mode uses DISTINCT, empty head EXISTS, bag/count controls retain their semantics; repeated physical tables must have identical layouts. zip-based construction assumes matching scope/table lengths from fixed callers. |
| ownership | Owns catalog/variable/atom/SQL lists/dicts and strings; caller scopes/head may also be stored in returned records, not an arbitrary deep-clone boundary. |
| failure | Self-join layout mismatch raises ValueError; malformed fixed-input shapes/JSON/OOM propagate before files exist. |
| cost | O(atoms×arity+SQL bytes) construction, list searches/dedup and sorting; no native query admission or execution here. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0014

[Lines 98–126](../../../../tools/generate_workloads.py#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def specifications():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the24 fixed positive and negative B02 query families. |
| inputs / outputs | No arguments; fresh list of specs built by query and local path/star constructors. |
| invariants | Includes disconnected/selfjoin/repeated-variable/wide/text and cyclic/non-free/bag/count controls; finite catalog does not establish all-query or scalability coverage. |
| ownership | Owns returned nested records; path/star lambdas allocate fresh scopes/heads for each case. |
| failure | Construction errors propagate; no IO or cleanup boundary. |
| cost | Fixed24 query constructions, including up to six-arm star/eight-column scope; ordinary Python graph/string allocations. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0016

[Lines 129–148](../../../../tools/generate_workloads.py#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def pool(spec, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create small deterministic physical row domains for a selected spec and scale. |
| inputs / outputs | Spec, bounded scale and seed in; table-&gt;deduplicated row-list dict out. |
| invariants | Hot variables share0, other positions vary; text includes UTF8 snow/NUL and wide payload; self-join table overrides and repeated-variable filtered row are intentional controls. |
| ownership | Owns dict, candidate row tuples/lists and dedup keys; spec borrowed. |
| failure | Bad variable/scalar structure or OOM propagates; no file IO. |
| cost | O(atoms×fanout×arity) row creation, variable index searches, JSON/set dedup and potentially wide text copies; bounded scale is checked by build. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0018

[Lines 151–191](../../../../tools/generate_workloads.py#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def trace(spec, regime, seed, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate physical set-operation attempts for one explicit update regime. |
| inputs / outputs | Spec/regime/seed/scale in; ordered events with operation/table/row/phase out. |
| invariants | Initial loads charged; duplicate insert/absent delete attempts retained. Global/per-relation FIFO promises are different; rate_shift changes relation mix, not arrival Hz. |
| ownership | Owns row pools, interleaved entries, queues/lists and event row-list copies; no native owner binding. |
| failure | Unknown fixed regime/invalid structure errors propagate; no publication until build encodes returned data. |
| cost | Pool cost plus deterministic sorting/churn loops; list/deque removal/search can be linear per event, encoded data size scales with attempts×arity. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def emit(operation, item, phase='workload'):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one copied physical attempt with a local phase label. |
| inputs / outputs | Captured events list and operation/table/row/phase in; mutates list, returns None. |
| invariants | Does not deduplicate/no-op filter or validate regime itself; caller orders all attempts. |
| ownership | Owns new event tuple and list(row); scalar members borrowed/immutable in admitted generator. |
| failure | Type/OOM error aborts local trace construction, no disk change. |
| cost | O(row arity) shallow row-list copy plus amortized list append. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0020

[Lines 194–213](../../../../tools/generate_workloads.py#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def relational(spec, database):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate one fixed CQ spec by explicit independent assignment joins. |
| inputs / outputs | Spec and table-&gt;set-of-rows database in; ordered set/bag/count/Boolean result rows out. |
| invariants | Enforces repeated-variable equality during extension. 100000-assignment cap is checked after finishing each atom's next_assignments, so transient construction can exceed the cap. |
| ownership | Owns assignment dicts copied per successful extension and result/dedup/sort buffers; database/spec borrowed. |
| failure | Cap violation raises ValueError after work/allocation; malformed cells/types/OOM propagate. |
| cost | Nested current-assignment×table-row×arity scans per atom with potentially Cartesian intermediate size; full result construction/sort on every call, not native incremental update cost. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0022

[Lines 216–248](../../../../tools/generate_workloads.py#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle(spec, events):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare explicit relational and SQLite answers after every physical input attempt. |
| inputs / outputs | Spec and ordered events in; owning initial_rows and per-epoch current/added/removed result packet out. |
| invariants | Maintains exact physical sets and NOTNULL SQLite tables, checks both complete answers each event including no-ops; fixture scalar domain is limited, not arbitrary SQL semantics. |
| ownership | Owns Python membership sets, in-memory SQLite connection/results, all repeated snapshot/delta arrays; connection.close is at normal end, not a finally boundary. |
| failure | Mismatch/SQL/encoding/OOM propagates; normal path closes SQLite explicitly, exceptional path has no guaranteed immediate explicit close. |
| cost | Full query evaluation in both engines each event, set differences and result sorting; retains O(sum per-epoch result/delta bytes), with full join intermediates. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def evaluate():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute and compare the current explicit and SQLite complete answers for the enclosing oracle. |
| inputs / outputs | Captures spec/database/connection; returns relational result after equality against fetched SQLite rows. |
| invariants | Both answers use ordered canonical representation; mismatch raises rather than accepting an oracle majority. |
| ownership | Borrows captured owners; owns both result collections and sorting keys during comparison. |
| failure | SQLite/relational/ValueError/OOM failure escapes oracle; helper does not close the captured connection. |
| cost | Full relational join plus SQL execution/fetchall and both output orderings per call. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0024

[Lines 251–264](../../../../tools/generate_workloads.py#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify_regime(events, regime):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently check the generated trace obeys its named insertion/deletion/FIFO promise. |
| inputs / outputs | Events and regime in; returns None after replaying membership and arrival queues. |
| invariants | Distinguishes committed no-op attempts from effective membership changes; per-relation FIFO does not assert global FIFO. |
| ownership | Owns membership sets and global/per-table queues, borrows event rows. |
| failure | Promise violation raises ValueError at offending attempt; no source or output mutation. |
| cost | Full event replay with tuple creation; queue/list remove/search may cost current active rows per deletion. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0026

[Lines 267–335](../../../../tools/generate_workloads.py#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build(seed=20261110, scale=1, selected=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the deterministic B02 corpus, independent expected epochs and provenance manifest. |
| inputs / outputs | Seed in0..2**64-1, scale1..8 and optional unique spec IDs in; owning relative-path-&gt;encoded bytes out. |
| invariants | CLI supplies ints; build range predicates alone do not reject bool/subclass numeric inputs. Positive admitted families get seven regimes, negative controls one; legacy/license facts remain explicit. free_connex requires both body alpha-acyclicity and augmented H+F alpha-acyclicity; the full-head triangle remains false despite an acyclic augmentation. |
| ownership | Owns all specs, manifest objects, traces/oracles and encoded file bytes concurrently; no filesystem output here apart from reading provenance inputs. |
| failure | Selection/range/regime/oracle/IO failures propagate before main output creation; no fallback invalid pack. |
| cost | Regenerates every selected trace and full two-oracle result after every event, hashes source/legacy metadata, retains entire corpus; scale is a finite grant, not asymptotic evidence. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def put(path, value, raw=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize and retain one B02 member plus exact-byte metadata. |
| inputs / outputs | Trusted relative path/value/raw flag in; captured files\[path\] bytes mutated and path/hash dict returned. |
| invariants | JSON sorts/indents and ends newline; raw text encoded directly; same path would replace prior captured value. |
| ownership | Owns full UTF8 bytes and metadata; value graph borrowed during encoding. |
| failure | JSON/UTF8/type/OOM failure propagates before main writes. |
| cost | O(member encoded bytes) serialization/hash and retained full-member allocation. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0028

[Lines 338–354](../../../../tools/generate_workloads.py#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Regenerate B02 bytes for an exact check or fresh-directory publication. |
| inputs / outputs | --output plus seed/scale/queries and optional --check; prints finite file/query/trace result. |
| invariants | Check reads every existing output file and rejects extras; generation uses new root exist_ok=False and direct sequential writes, no transaction/fsync. |
| ownership | Owns complete expected/actual byte dicts when checking; filesystem owns created partial/success outputs. |
| failure | Argparse/IO/build errors propagate through unwrapped main; failed sequential writes can leave partial new root. |
| cost | Complete build/oracle cost plus full recursive actual-file reads or O(total output bytes) writes. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0029

[Lines 355–358](../../../../tools/generate_workloads.py#L355); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the B02 workload generator only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No catch wrapper; main failures retain traceback/nonzero exit and any partial output root. |
| cost | Same complete main work; guard itself constant cost. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
