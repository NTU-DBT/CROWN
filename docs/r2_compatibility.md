# R2 compatibility

This guide describes the current opt-in SQL bag and aggregate interfaces under
[Refactor §0.1, W01–W06 and V04](../Refactor.md). It does not declare an R2 release
or a current full-suite pass. The [accepted R1 archive](releases/r1.md) has its
own frozen byte identity and qualification. For practical changes, read
[R2 migration](r2_migration.md).

## Choose the query family

Each column below describes a separate genuine compiler/runtime boundary.
Successful SQL binding still needs a checked tree for its actual derived core.

| Contract | R1 set workflow | Nullable SQL rows | Original SQL aggregates |
| --- | --- | --- | --- |
| Public entry | [Set CLI/library workflow](cli.md), including `crown compile/run` | [`bind_sql_rows`](../include/crown/frontend/sql_rows.hpp), `SqlRowsRuntime`, `CROWN::sql_rows`; durable `CROWN::sql_rows_recovery` | [`bind_sql_aggregate`](../include/crown/frontend/sql_aggregate.hpp), `SqlAggregateRuntime`, `CROWN::sql_aggregate_runtime`; durable `CROWN::sql_aggregate_recovery` |
| Admitted result | Declared `SELECT DISTINCT` and EXISTS fragment; plain bag SELECT rejects | Plain SELECT bag, nullable DISTINCT and EXISTS within the [row fragment](sql_rows_runtime.md) | Admitted COUNT/SUM/AVG and column GROUP BY over a genuine [source query](sql_aggregate_binding.md) |
| Physical NULLs | Referenced source tables must have non-nullable columns, including unused columns. Local NULL literals/parameters retain their separate filter rules | Optional typed cells; ordinary equality joins only present equal operands; NULLs consolidate for DISTINCT | Same nullable physical source; NULL grouping keys share a group. COUNT(expr), SUM and AVG skip NULL arguments |
| Scalar domain | Existing exact core scalars and native byte-string policy | int64 physical integers/parameters, admitted int32 literals/casts, Boolean, bounded DATE/DECIMAL and UTF8 TEXT without NUL; binary collation | COUNT accepts admitted scalar arguments. SUM/AVG accept integer arguments; DATE/DECIMAL source support does not enable decimal SUM/AVG |
| Unsupported SQL | Unimplemented syntax rejects; parser recognition is not execution admission | Bare GROUP BY, outer joins, cross-occurrence computed expressions/comparisons beyond extracted equalities and other unimplemented clauses reject | Aggregate DISTINCT, computed/cross-relation arguments, argument parameters, HAVING, windows and grouping/ordering extensions reject. Source predicate parameters remain separately admitted |
| Empty result | Empty set or the EXISTS Boolean presentation | Empty named input yields no plain/DISTINCT rows; EXISTS always has one Boolean row, FALSE when empty | Global aggregation has one row: COUNT=0, SUM/AVG=NULL on empty input. GROUP BY has no empty groups; last loss removes the group |

A no-FROM constant SELECT uses the genuine static zero/one source. EXISTS at C0
reflects that actual inner presence, including TRUE for an admitted static true
source. No-FROM aggregation consumes SQL's implicit singleton, distinct from an
empty named relation. Aggregate composition also requires its actual derived source head to
admit a CROWN tree; an aggregate expression cannot bypass that structural check.
Merged unqualified USING/NATURAL grouping references retain the binder's explicit
restrictions. The lower [`CROWN::aggregate`](aggregates.md) API consumes logical
bag rows; it does not replace original joined-SQL source admission.

## Updates, results and numeric limits

| Contract | R1 set workflow | Nullable SQL rows | Original SQL aggregates |
| --- | --- | --- | --- |
| Physical update | Complete set-row insert/delete; duplicate insert/absent delete is a successful no-op | Complete nullable physical row plus exact expected `before` and final `after` uint64 weights | The same physical replacement contract, coordinated with groups |
| Atomic batch | Ordered transport preserves each event/output barrier | Separate [`NetBatch`](sql_rows_batches.md): repeated full-row edits form exact chains, final constraints are validated, then one epoch publishes | Same physical NetBatch; source decreases precede increases and touched groups are consolidated before publication |
| No-op/cancellation | Still advances the event sequence | Empty/no-op/cancelled batch still commits C; source `changed` can be false | Still commits C; source change, group change and visible output change are distinct |
| Native state/root | Set support bookkeeping; read public results for query answers | Checked nonnegative uint64 sums/products. `root_weight()` is the inner full-witness weight before DISTINCT/EXISTS | The source's native root weight is not the aggregate COUNT or number of groups |
| Current output | Duplicate-free SQL rows | `Result` owns one nullable tuple and schema with exact multiplicity; DISTINCT weight is one; EXISTS has one Boolean row | Eager owning snapshot with complete group identities and ordered output values; different groups may render equal selected values |
| Change output | Signed set insertion/deletion rows | `prepare_output_batch`: exact signed uint64 magnitudes for bags, signed units for DISTINCT, or old/new Boolean unit rows for EXISTS | `GroupChange`: complete group key plus optional before/final-after tuples. Absence differs from present all-NULL; rounded equal AVG can produce no visible value event |
| Arithmetic | Existing exact set/runtime contract | Intermediate multiplicities must fit the configured uint64 domain even when DISTINCT/EXISTS output is small | Group input count <= INT64_MAX; COUNT is bigint; SUM(integer) checked bigint; SUM(bigint) NUMERIC(38,0); AVG NUMERIC(38,s), s=0..18, default 18, half ties away from zero |

Retractions above INT64_MAX remain an unsigned magnitude plus a sign. Do not
narrow them to int64, subtract unsigned weights, interpret raw encoded native
`BagDelta` as SQL presentation, or decode a row epoch as `GroupChange`.
`prepare_batch` keeps its native-only default; `prepare_output_batch` explicitly
requests SQL output. Its [row/field allowance](../include/crown/runtime/sql_rows.hpp)
is cumulative across all reads of that token. Group event capture instead uses
aggregate `Options::capture_changes`, default false and required true by the
durable aggregate Session. These are separate controls.

Weights and NULLs remain exact through [physical source validation](sql_rows_runtime.md).
Enforced UNIQUE uses NULLS DISTINCT; FK uses MATCH SIMPLE, exempting any NULL key.
Immediate single-row checks and atomic final-state batch checks intentionally
differ. The complete physical identity includes hidden, filtered and unused
columns/tables; projected answers cannot reconstruct that state.

## Persistence, identity and ownership

| Contract | R1 | Nullable SQL rows | Original SQL aggregates |
| --- | --- | --- | --- |
| Durable owner | Existing native/set Session and CLI | [`recovery::sql_rows::Session`](sql_rows_session.md), installed C++ API; no plain-row CLI command | [`recovery::sql_aggregate::Session`](sql_aggregate_session.md) and [`crown aggregate`](sql_aggregate_input.md) |
| Binding metadata | Frozen normalization v1/v2 meanings and artifact identity retain their [version rules](schema_evolution.md) | `CROWN-SQL-ROWS;1` binds exact SQL/catalog/typed values into `source_sha256`. Default `retain_binding_image=false` leaves `binding_image()` empty; durable codecs require explicit true | `CROWN-SQL-AGGREGATE;2` retains its own binding of original/source/kernel/decoder/parser identity; row retention is not the aggregate capture option |
| Files | Existing CROWNSI1/CROWNRI1 checkpoint, CROWNWAL and CROWNSK1 families keep their own rules | CROWNRD2 descriptor, CROWNRC2 physical checkpoint, CROWNRW2 WAL/sink records with RowEpoch | CROWNAD2 descriptor, CROWNAC2 physical checkpoint, CROWNAG2 WAL/sink records with GroupEpoch |
| Selected root | Existing R1 generation/retirement contract | Plan-bound CROWNGR1 v3 with delivery anchor; retained history floor one | Same root envelope requirement; separately typed descriptor/checkpoint/records |
| Checkpoint state | Existing set/session state | Complete physical rows/weights, C/I, source/reader progress and selected delivery anchor | Complete physical source image and genuine reconstruction of source/groups; no persisted joined-row ledger |
| History | R1 qualified retirement remains separate | Default cap 128 absolute selected generations; reopening does not reset usage; no retirement operation | Same bounded, non-refillable history profile; no aggregate retirement operation |

The new row/aggregate envelopes above have format version 1 despite the `2` in
their magic names. They are separate families, with no automatic R1-to-R2 or
row-to-aggregate file conversion. Sharing root framing, limit DTOs and bounded
POSIX I/O does not merge typed frame, descriptor, file-owner, receipt or Session
authority. Hashes and editable metadata describe bytes; genuine factories and
actual locked file owners establish native state and delivery.

Both R2 Sessions track logged W, disposed I, native committed C and delivered D.
At most one logged head and one committed output spool exist. Another command
requires W=I and D=C. A semantic Reject advances I/source/reader progress while
preserving C/D and source/native/group state. Rows admit only weight mismatch,
source overflow, UNIQUE/FK violation and annotation overflow; aggregates add
aggregate overflow. Resource/contract failures never become semantic Rejects;
they retain the pending head when the owner remains healthy. Uncertain file I/O
requires reopening actual files.

Recovery rebinds genuine metadata, rebuilds the complete physical source and
replays selected decisions/output before any permitted torn-tail repair.
Complete corruption is fatal; the two file repairs are sequential, not pair-atomic.
The [Linux regular-file, cooperating-lock and namespace/fsync premises](sql_aggregate_files.md)
remain explicit. Local duplicate delivery compares actual epoch bytes; no
arbitrary external exactly-once service guarantee follows.

## Resource and compatibility boundaries

Use one matching SDK's headers, libraries and exported CMake targets, then
recompile consumers. Project version 0.1.0 / public API 1 and release label R2 are
separate identifiers. New fixed fields/handle layouts do not promise binary
compatibility with an older SDK; file compatibility remains family-specific.
Ordinary row binding preserves its original large-parameter memory bound and source hash
when recovery metadata is unrequested. Retaining the image explicitly adds cold
accounted bytes/copies without changing that source hash.

Receiving `MemoryAccount` caps cover actual retained native/source/group/output
storage, not total process RSS. Compiler/DOM/DTO workspace has its separate cold
scope. Source/native/index/group/cursor/SQL-preview/codec/replay grants meter
their stated work and are not interchangeable. Final output-row caps do not bound
all intermediate capture or its peak; comparisons, strings, sorting, formatting,
checkpoint/rebuild and last-owner cleanup retain their real costs. Numeric
maintenance does not inherit the Boolean update bound. See
[weighted messages](weighted_messages.md), [enumeration](weighted_enumeration.md)
and the [paper/source boundary](code_review.md).

The default height objective/policy is unchanged. CLI minimum claims still need
independent evidence; library construction with a supplied tree validates an
upper bound. Approximation, shared-query optimization and parallel/distributed
execution remain deferred; independent queries have independent owners/state.
V04 qualification still requires source-bound exact numeric/SQL/recovery checks,
a relocated public-SDK workflow and the extended report, with a separate release
decision. Preserve existing rights/notices; licensing disposition remains deferred.
