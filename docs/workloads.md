# Reproducible query and trace workloads (B02)

B02 is verified; see the [acceptance record](verification/b02-workload-manifest-acceptance-2026-11-11.md).
The finite manifest at
[benchmarks/workloads/manifest.json](../benchmarks/workloads/manifest.json)
contains24 SQL definitions and144 trace cases. Twenty set queries have140
runnable traces; four negative controls exercise cyclic, non-free-connex,
bag and aggregate rejection. This is mechanism coverage, not evidence that a
finite graph suite covers every free-connex query or that any system is faster.
The [local checkpoint](verification/b02-workload-local-corpus-2026-11-11.md)
records four native compiler-mode controls and fresh source-only CMake acceptance.
Pinned DynaGox source definitions are imported/classified separately. All10
selected integrated fresh-source tests pass;277 tests are registered. This is
separate from the full277-test release gate and controlled measurements.

## Inputs and contracts

Each workload references exactly one query definition. That definition records
physical-set input and set/bag/aggregate output semantics, ordered CQ head,
SQL output expressions, atom occurrences, physical table aliases, variable
scopes, independent body/head acyclicity, expected admission, backends and output
modes. A Boolean query has no free CQ head variables and an explicit scalar
EXISTS output; an ungrouped COUNT control has no grouping keys and COUNT(*) as
its output expression. Neither is an ordinary empty SQL SELECT list.

Every trace starts with empty physical tables. Records are ordered atomic
physical set insertions/deletions, including complete self-join alias fanout.
Duplicate insertion and absent deletion still commit a sequence/source position
and can produce an empty delta. Every SQL, catalog, trace and finite oracle file
has a SHA-256 binding. The closed
[version1 schema](../schemas/workload-manifest-v1.schema.json) describes transport;
the verifier also checks references, regeneration and actual trace promises.

The140 admitted cases cover seven regimes per query:

- Insert-only.
- Deletion after an explicit charged loading prefix; the initial state is empty.
- Global FIFO deletion of live inputs.
- Per-relation FIFO, which need not preserve global insertion order.
- Mixed insert/delete with explicit no-ops.
- Repeated churn, including duplicate inserts, absent deletes and witness loss.
- A phase change in the physical relation or key receiving updates. This is
  input-mix evidence, not a measured arrival rate or wall-clock process.

Phase labels and loading counts are part of the manifest. A future measurement
runner must charge loading and distinguish any phase-specific totals from total
input work. FIFO labels describe generated traces; they do not change the
native engine's admitted arbitrary-update guarantee.

## Structural families and generation

Families include full/projected paths, Boolean heads, high-fanout full/projected
stars, many witnesses per visible answer, composite separators, nested/contained
and equal scopes, eight-column relations, wide UTF-8/NUL strings, disconnected
products, repeated-variable local filters and two/three-alias self-joins.
Full-star sizes3/6 and path sizes2/4 provide separate query-size examples.
Hot-key, coherent distinct-key and loop/chain inputs are labeled separately.
Empty/dangling prefixes and small/large result sets remain visible in the raw
oracle counts; data size and query size are distinct experiment axes.

Generate a new pack into an absent directory:

```sh
python3 tools/generate_workloads.py --output build/workloads-reproduced
python3 tools/generate_workloads.py --output build/workloads-reproduced --check
python3 tools/verify_workloads.py --source . --pack build/workloads-reproduced --static-only
```

Defaults are seed20261110 and scale1. SHA-256 ordering avoids interpreter hash
randomization; seed controls mixed/phase ordering. `--scale N` changes rows per
table and string width without changing a selected query. Repeat `--query ID`
to select families, for example `--query hidden_witnesses --query wide_strings
--scale 2 --seed 9`. The generator permits scale1–8 but rejects any case exceeding
its100,000-assignment finite oracle ceiling; high-fanout Cartesian outputs can
reach it quickly. It finishes generation before creating the output directory,
so a failed size request does not leave a partially written pack.

The finite oracle uses a direct assignment join and independently executes the
generated SQL in SQLite after every input. SQLite is used only for generated
non-null integers/text; this does not establish SQLite equivalence for native
exact decimals or every SQL type. Expected current rows and raw signed set
deltas are stored, including Boolean false/true rows and empty epochs.

## Native replay and a runnable workload

The repository tests build `crown_workload_replay_test`, a generic public-API
exporter with no oracle or query-class dispatch. It loads a physical plan,
re-lowers its checked tree for indexed storage when requested, executes each
physical event and exports actual rows/deltas/progress. The verifier compares
every epoch with the independent finite oracle on both `reference_ordered_v1`
and `indexed_chained_v1`, in delta and maintenance modes. Full snapshots are
materialized in both modes for correctness; these checks are not timing runs.

```sh
cmake --build BUILD --target crown crown_workload_replay_test
ctest --test-dir BUILD -R '^workload_(manifest|replay)$' --output-on-failure
```

To use an individual case through the public CLI:

```sh
python3 tools/prepare_workflow_input.py BUILD/crown \
  benchmarks/workloads/queries/composite_separator/catalog.json \
  benchmarks/workloads/traces/composite_separator/mixed/events.template.jsonl \
  build/composite-updates.jsonl
BUILD/crown compile benchmarks/workloads/queries/composite_separator/query.sql \
  benchmarks/workloads/queries/composite_separator/catalog.json > build/composite-plan.json
BUILD/crown verify-trace build/composite-plan.json build/composite-updates.jsonl
```

The preparation helper fills the native canonical catalog binding; the template
hash is distinct from the bound input-file hash. Keep both, along with query/
catalog/plan IDs and actual build/environment/mode records for any later run.
Maintenance, requested full snapshots and consumed per-epoch deltas are separate
output demands. Enumeration performed during validation is not free work in a
benchmark. B03's controlled timing runner remains separate.

## Legacy sources, external data and licensing

The [legacy inventory](../benchmarks/legacy/manifest.json) classifies all116 task
scenarios across five pinned legacy specs into13 query labels. Repeated backend,
dataset and parallelism settings are not extra query families. It records raw
SQL/template/setup/Scala paths, backend-specific heads/semantics, equality
structure, adaptation requirements, output modes and unresolved trace contracts.
All122 local source fingerprints and120 Git blobs at the CROWN pin are checked.

Raw legacy definitions are retained at their original paths. HOP windows,
nullable predicates, cross-relation comparisons, aggregates and implicit bag
SELECT require their own contracts. Some Flink and DBToaster versions have
different predicates or heads. Expanding dumbbell triangle views yields cyclic
raw queries; treating a Triangle relation as input is a declared transformation,
not reproduction of raw triangle maintenance. No legacy executable or timing is
qualified by this inventory, and no generated family inherits its benchmark name.

The [DynaGox source inventory](../benchmarks/legacy/dynagox/manifest.json) imports
all24 definitions from Queries.md at commit
`c6811db68a34ab3b32722968c4e1e821f730c5ac`, retaining original SQL and exact source
Git blobs/checksums. Every original is an aggregate query. Root independently
checks SELECT/GROUP BY text, physical occurrences and equality-body scopes:
22 bodies are acyclic; DUMBBELL and TPCH-Q5 are cyclic. Aggregate expressions
are not set-CQ heads, and body acyclicity does not establish native admission.
Only the two inspected C++ sources supply scoped insertion/milestone evidence;
other runtime update/output contracts remain explicitly unknown.

```sh
python3 tools/verify_imported_workloads.py --source . --crown BUILD/crown
```

This check parses all24 originals and rechecks their equality-body shapes, source
pin, output clauses and ineligible data/native timing states. It rejects source
pin changes, replacement SQL and false dataset/native eligibility. No aggregate
has been rewritten into a set result or enabled for R1 timing. The original
source definitions and their distribution-license status remain explicit.

The [external registry](../benchmarks/external_imports.json) binds classified
sources for DynaGox/CROWN, SNB, LSQB, JOB, CEB, TPC-H and TPC-DS. JOB/CEB/LSQB/
TPC-H/TPC-DS entries describe the pinned DynaGox experiment variants; they do not
qualify the complete official suites. Native catalogs, real source data bytes,
checksums and applicable licenses remain unavailable. Those datasets cannot
enter a runnable comparison until their complete contract is recorded.

Current runnable records are new deterministic synthetic data, with no external
dataset imported. Imported SQL definitions are source inspection inputs.
No separate data license grant or project distribution license
has been chosen; A02 remains open. The manifest records that disposition and
does not authorize redistribution. Source inspection, native correctness,
baseline reproduction, controlled performance and release qualification remain
distinct evidence.
