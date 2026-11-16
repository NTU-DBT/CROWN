# `tools/component_workloads.py` — block usage map

[Source](../../../../tools/component_workloads.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `06b5f4b4715bd59e6dccf8e79049ed7ab5b80110651ce089082f2ac6dbd9a032`. 324 lines partitioned into 25 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../tools/component_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–31](../../../../tools/component_workloads.py#L26) | Callable definition: def catalog(tables): | calls items; returns {'schema_version': 1, 'catalog': {'version': 1, 'tables': \[; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 32–33](../../../../tools/component_workloads.py#L32) | Explanatory comments or spacing. |  |
| [B0004 · 34–35](../../../../tools/component_workloads.py#L34) | Callable definition: def event(operation, table, pair, phase='updates'): | calls list; returns {'operation': operation, 'table': table, 'values': list(pair), 'phase': phase} · [reviewed contract](#b0004) |
| [B0005 · 36–37](../../../../tools/component_workloads.py#L36) | Explanatory comments or spacing. |  |
| [B0006 · 38–55](../../../../tools/component_workloads.py#L38) | Callable definition: def layered_events(family, width, cycles=1): | calls require, in, type, range; guard require(family in ('l3_full_rows','l5_distinct_count','l5_group_count'), 'unknown layered cohort fa…; returns events; 9 loop sites · [reviewed contract](#b0006) |
| [B0007 · 56–57](../../../../tools/component_workloads.py#L56) | Explanatory comments or spacing. |  |
| [B0008 · 58–72](../../../../tools/component_workloads.py#L58) | Callable definition: def operational_events(width, cycles): | calls require, type, range, in; guard require(type(width) is int and 1 &lt;= width &lt;= 8 and type(cycles) is int and 1 &lt;= cycles &lt;= 16, 'inva…; returns events; 11 loop sites; source comment (unverified): # Two cancelling edits share a net-batch endpoint; numeric changes keep · [reviewed contract](#b0008) |
| [B0009 · 73–74](../../../../tools/component_workloads.py#L73) | Explanatory comments or spacing. |  |
| [B0010 · 75–87](../../../../tools/component_workloads.py#L75) | Callable definition: def numeric(value, scale=0): | calls require, type, Fraction, abs; guard require(type(scale) is int and 0 &lt;= scale &lt;= 38, 'invalid NUMERIC scale'); returns {'decimal': digits} · [reviewed contract](#b0010) |
| [B0011 · 88–89](../../../../tools/component_workloads.py#L88) | Explanatory comments or spacing. |  |
| [B0012 · 90–91](../../../../tools/component_workloads.py#L90) | Callable definition: def bind_oracle(sql, kind='rows', **mapping): | calls sha256, encode, hexdigest; returns {'kind': kind, 'source_sql_sha256': hashlib.sha256(sql.encode()).hexdigest(), **mapping} · [reviewed contract](#b0012) |
| [B0013 · 92–93](../../../../tools/component_workloads.py#L92) | Explanatory comments or spacing. |  |
| [B0014 · 94–158](../../../../tools/component_workloads.py#L94) | Callable definition: def evaluate_request(request, specification): | calls require, sha256, encode, hexdigest; guard require(specification\['source_sql_sha256'\] == hashlib.sha256(request\['program'\]\['sql'\].encode()).he…; returns frame; {'initial': initial, 'epochs': frames}; 15 loop sites · [reviewed contract](#b0014) |
| [B0015 · 159–160](../../../../tools/component_workloads.py#L159) | Explanatory comments or spacing. |  |
| [B0016 · 161–170](../../../../tools/component_workloads.py#L161) | Callable definition: def base_request(identifier, sql, tables, events, output, backend='reference_ordered_v1'): | calls indexed_options; returns {'schema_version': 1, 'case_id': identifier, 'query_family': identifier, · [reviewed contract](#b0016) |
| [B0017 · 171–172](../../../../tools/component_workloads.py#L171) | Explanatory comments or spacing. |  |
| [B0018 · 173–178](../../../../tools/component_workloads.py#L173) | Callable definition: def cohort_widths(widths): | calls tuple, require, all, type; guard require(result and all(type(width) is int and 1 &lt;= width &lt;= 8 for width in result), 'invalid cohort…; returns result; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 179–180](../../../../tools/component_workloads.py#L179) | Explanatory comments or spacing. |  |
| [B0020 · 181–269](../../../../tools/component_workloads.py#L181) | Callable definition: def build_operational_cohorts(widths=(2,4,8), cycles=2): | calls catalog, cohort_widths, operational_events, in; returns {'schema_version':1,'kind':'b04_operational_cohorts','arms':arms,'comparisons':comparisons,; 5 loop sites; source comment (unverified): # The full head has 2*w^3 loaded rows and a transient peak of · [reviewed contract](#b0020) |
| [B0021 · 270–271](../../../../tools/component_workloads.py#L270) | Explanatory comments or spacing. |  |
| [B0022 · 272–309](../../../../tools/component_workloads.py#L272) | Callable definition: def build_baseline_cohorts(widths=(2,4,8), cycles=2): | calls cohort_widths, catalog, layered_events, base_request; returns {'schema_version':1,'kind':'b04_matched_baseline_cohorts','arms':arms,'comparisons':comparisons,; growth insert; 6 loop sites; source comment (unverified): # Cardinality folds genuine signed changes into one scalar; · [reviewed contract](#b0022) |
| [B0023 · 310–311](../../../../tools/component_workloads.py#L310) | Explanatory comments or spacing. |  |
| [B0024 · 312–320](../../../../tools/component_workloads.py#L312) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, build_operational_cohorts · [reviewed contract](#b0024) |
| [B0025 · 321–324](../../../../tools/component_workloads.py#L321) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |

## B0001

[Lines 1–25](../../../../tools/component_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:4e099895d6931f919b2c123d7f9836a4c961c66177cbd90ea57252621d4a4d6a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define deterministic B04 source cohorts and the independent SQLite prefix oracle. |
| inputs / outputs | Imports standard-library exact arithmetic, SQLite, deterministic shuffling, JSON, and the bounded request helpers; declares fixed L3, L5, and operational SQL strings. |
| invariants | The SQLite oracle does not call native planning or runtime code and computes AVG from exact SUM and COUNT fields. Request option fixtures still come from run_measurements. |
| ownership | The module owns generated event/request dictionaries and each oracle call owns a local in-memory SQLite database. |
| failure | Missing project helpers or invalid SQL/request structures stop import or cohort/oracle construction. |
| cost | The work is bounded by width and cycle caps; oracle evaluation reruns the SQL after every physical input. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0002

[Lines 26–31](../../../../tools/component_workloads.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L31:sha256:d76104b1c14390ee8121280618cd4c435339ab11a29a332a98e5b03b99f17a6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a version-1 catalog from named two-column cohort tables. |
| inputs / outputs | A mapping of table names to column-name pairs returns a catalog with non-null int64 columns and empty constraints, hints, and distinct-count statistics. |
| invariants | The fixture describes only the small generated integer-pair source used by these experiments. |
| ownership | Returns newly allocated dictionaries owned by the caller. |
| failure | Malformed mappings may produce a catalog that SQLite or native request admission rejects. |
| cost | Allocates in proportion to the supplied tables and columns. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0004

[Lines 34–35](../../../../tools/component_workloads.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:97f0f08622bca47a3216bc79e3524a15a9be8613aee78b022a4295ac87948d03
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one physical unit insert or erase for a cohort source. |
| inputs / outputs | Operation, table, value pair, and optional phase produce the exact event dictionary expected by the requests. |
| invariants | Values are copied into a fresh list; event validity is checked when the oracle applies the trace. |
| ownership | The returned event is caller-owned. |
| failure | Invalid operations, tables, duplicates, and absent erases are rejected by evaluate_request. |
| cost | Constant-size dictionary/list construction. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0006

[Lines 38–55](../../../../tools/component_workloads.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L55:sha256:0da31e67b327c3c343b543e825308dff140bd49d09fb28b36c22c4d6d2e15d85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate deterministic adjacent complete graph layers for the three original query families. |
| inputs / outputs | A recognized family, width, and cycle count produce shuffled charged-load events and, except for insert-only L5 distinct count, delete/reinsert update events. |
| invariants | Families are explicitly allow-listed; width and cycles are strict integers in 1..8 and 1..16. Every layer edge is one unique table/value pair. L5 distinct-count ignores update cycles by design. |
| ownership | Owns and returns a new event list; random state is local and seeded from family and width. |
| failure | Unknown families and invalid bounds raise ValueError through require. |
| cost | Creates O(width squared) facts per adjacent layer and O(cycles times width squared) update events. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0008

[Lines 58–72](../../../../tools/component_workloads.py#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L72:sha256:e6a145b6553bd8077615e25f6f26a8ce69a1e32f6ce5683f4d8c087f97b9daa8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate the operational two-table unit-set trace with cancellation and negative edits. |
| inputs / outputs | A strict width/cycle pair returns deterministically shuffled charged-load facts, cancelling r1 insert/erase pairs, a numeric row erase/reinsert, and r0 erase/reinsert endpoints. |
| invariants | Every event is a unique live fact at insertion time; each erase targets an existing fact. The transient r1(100,0) row is intentionally retained for the full-head peak witness. |
| ownership | Returns a fresh list of events; deterministic Random state is local. |
| failure | Non-integer or out-of-range width/cycles raise ValueError. |
| cost | The charged load is O(width squared); update length is O(cycles plus width). |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0010

[Lines 75–87](../../../../tools/component_workloads.py#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L87:sha256:4d59faa284df5b6d0514cecf4f4e090b6cb5efef04a59c3c1c373158f280748e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format an exact Fraction as canonical NUMERIC decimal text. |
| inputs / outputs | An exact numeric value and scale 0..38 return a decimal string rounded half away from zero. |
| invariants | The computation uses integer numerator/denominator arithmetic; trailing fractional zeros and negative zero are removed. |
| ownership | Returns a fresh output dictionary and does not mutate the supplied value. |
| failure | Unsupported scales raise ValueError; Fraction conversion or arithmetic errors propagate. |
| cost | Integer arithmetic scales with numerator and denominator digit lengths and the requested decimal scale. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0012

[Lines 90–91](../../../../tools/component_workloads.py#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L91:sha256:55b4f993b569fe75de9d0a1aa544a6085e02f61596302d05370b98874b8daa90
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an oracle kind and mapping to the exact SQL text. |
| inputs / outputs | SQL, optional oracle kind, and mapping fields return a SHA-256 query binding plus the declared mapping. |
| invariants | The digest is over UTF-8 SQL bytes and mappings do not substitute a different source query. |
| ownership | Returns a new dictionary; mapping values are caller-provided references. |
| failure | Encoding errors propagate; mapping schema is checked when evaluate_request consumes it. |
| cost | Hashes the SQL text once and copies a constant-size outer mapping. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0014

[Lines 94–158](../../../../tools/component_workloads.py#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L158:sha256:b33b33e7267979c206028e6af6975e0b19b4c889cb8c37fa79ec1922ecba036a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute every physical input prefix with an in-memory SQLite database. |
| inputs / outputs | A request and query-bound rows or aggregate specification return initial state plus one frame per event; rows frames contain distinct rows, cardinality, compressed bag counts, and set deltas; aggregate frames contain exact groups and replacements. |
| invariants | The SQL digest must match. Cohort identifiers are constrained, physical rows are two integer values, inserts are unique, erases target live rows, and average output uses exact SUM/COUNT with numeric Fraction formatting. |
| ownership | The function owns its SQLite connection and ordinary result objects; the connection is explicitly closed on successful completion. |
| failure | Invalid binding, duplicate/absent unit facts, unknown oracle kinds/mappings, malformed SQL, or SQLite errors raise and abort evaluation. |
| cost | Executes the declared SQL at offset zero and after every physical event; full output materialization scales with query and prefix result cardinality. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0016

[Lines 161–170](../../../../tools/component_workloads.py#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L170:sha256:bb7708a4e04b3a0344736b4449a1dec307e56a1f0444317c822c40b11b3ca895
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a bounded version-1 request shared by the cohort adapters. |
| inputs / outputs | Identifier, SQL, catalog, events, output, and backend produce a verify request with finite memory/work/output/input caps and backend-specific physical options. |
| invariants | The reference backend removes indexed-storage settings and uses physical-options schema version 1; cohort callers set additional modes/session values explicitly. |
| ownership | Returns a mutable request owned by its caller; input catalog/events are referenced as provided. |
| failure | Missing expected option fields or invalid inputs propagate from the option helper or fail downstream admission. |
| cost | Builds a fixed-shape dictionary plus references to the source objects. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0018

[Lines 173–178](../../../../tools/component_workloads.py#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L173-L178:sha256:c59fa1a04ed4768d9339e4343c97e980bd1f25e26afb108c3182f643d72ca10d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and freeze cohort width strata before arm generation. |
| inputs / outputs | An iterable becomes a tuple of distinct integer widths in 1..8. |
| invariants | Empty, repeated, boolean, non-integer, and out-of-range widths are rejected before identifiers can collide. |
| ownership | Owns the returned tuple and does not mutate the supplied iterable. |
| failure | Invalid widths raise ValueError; a non-iterable raises its normal Python TypeError. |
| cost | Materializes and scans the finite width list once. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0020

[Lines 181–269](../../../../tools/component_workloads.py#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L269:sha256:c03fc6498bac2e9c9b635f5c96bd7e332ae8b0815f9752965b1ad2592ff7bede
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build matched operational session, full-head, net-batch, set, bag, and aggregate arms. |
| inputs / outputs | Widths and cycles produce two backend strata, request/oracle pairs for each operational adapter, and explicit comparisons with dotted changed paths and declared units. |
| invariants | Full discard/serialize arms keep identical SQL, events, and oracle; loaded full-head cardinality is 2*w^3 and the transient zero-valued r1 row raises the exact peak to 2*w^3+w. Net arms differ only in transaction_batch_size and share observation_interval 4. SQL semantics contrasts explicitly vary adapter/mode/output/query as declared. |
| ownership | Deep copies isolate variant requests; each arm owns its request/oracle mapping and local identifier table. |
| failure | Invalid widths/cycles fail before a manifest is returned; request mutation errors propagate. |
| cost | Produces 16 arms and 12 comparisons per width/backend; manifest size scales linearly with width strata. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0022

[Lines 272–309](../../../../tools/component_workloads.py#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L272-L309:sha256:c535631918802b2882679316287fff0acbd28165753b3ab41d1c23131bb2a59e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build matched original L3/L5 legacy, SQLite, and native cohorts, including scalar signed-fold mode for L5 distinct count. |
| inputs / outputs | Each width yields legacy, SQLite, ordered-native, and indexed-native arms for each original query, plus comparisons to legacy and SQLite controls. |
| invariants | The same original SQL, catalog, physical events, output demand, and oracle are shared within a family. L5 distinct count uses cardinality output and native delta mode to fold genuine signed changes into one scalar; it does not force a full snapshot drain. L5 distinct remains insert-only. Full rows and groups are still observed at every physical event. Cross-framework layout/parser/formatting/scalar/JVM costs remain inseparable. |
| ownership | Each arm receives a deep-copied oracle and an independently owned request. |
| failure | Invalid family widths/cycles fail in the layer generator; incompatible query/oracle definitions fail during evaluation or adapter admission. |
| cost | Every original query output is observed after every physical event; total work is finite under the width and cycle grants. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../tests/integration/component_workloads.py) |

## B0024

[Lines 312–320](../../../../tools/component_workloads.py#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L312-L320:sha256:0e4af50318a9afee9ab126ab91d40d2562feea0b612d1fb92795a6e03e89f056
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write an operational cohort manifest from command-line width/cycle choices. |
| inputs / outputs | Required --output and repeated --width values plus --cycles produce a formatted JSON manifest at a new path. |
| invariants | Default widths are 2, 4, and 8 with two cycles; output is opened in exclusive-create mode, so existing files are not overwritten. |
| ownership | The command owns only the newly created output file and generated manifest. |
| failure | Argument, cohort validation, serialization, and filesystem errors propagate to the script wrapper. |
| cost | Builds and serializes the selected finite operational manifest. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py) |

## B0025

[Lines 321–324](../../../../tools/component_workloads.py#L321); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L324:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the helper CLI only when the module is executed directly. |
| inputs / outputs | __main__ calls main and prints an error with exit status 1 on ordinary exceptions. |
| invariants | Importing the module defines helpers without creating manifests or launching native processes. |
| ownership | The process wrapper owns command-line execution and its output file. |
| failure | Catches Exception, writes a diagnostic to stderr, and exits nonzero; BaseException subclasses propagate. |
| cost | Fixed wrapper overhead plus the selected manifest build. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py) |
