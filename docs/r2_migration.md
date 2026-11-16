# R2 migration

Use [R2 compatibility](r2_compatibility.md) to choose the semantic contract before
moving data or consumers. These instructions describe the implemented interfaces
under V04 qualification; they do not accept an R2 release or relabel historical
checks as current. Keep the [accepted R1 image](releases/r1.md) intact.

## 1. Choose an owner and rebuild the consumer

| Workload | Interface to use |
| --- | --- |
| Existing declared set SQL and ordered insert/delete input | Keep the [R1 CLI/Session](cli.md) and its formats |
| Nullable plain SELECT, DISTINCT or EXISTS in memory | `frontend::bind_sql_rows[_into]`, `runtime::SqlRowsRuntime`, installed `CROWN::sql_rows` |
| The same rows with local WAL/sink/checkpoint recovery | `recovery::sql_rows::Session`, installed `CROWN::sql_rows_recovery` |
| Original admitted COUNT/SUM/AVG with physical source edits | `bind_sql_aggregate[_into]`, `SqlAggregateRuntime`, `CROWN::sql_aggregate_runtime` |
| Durable original aggregates | `recovery::sql_aggregate::Session`, `CROWN::sql_aggregate_recovery`, or `crown aggregate` |

`CROWN::aggregate` is the lower logical-row group kernel. COUNT(*) does not stand
in for a plain SELECT bag and cannot preserve its tuples, NULLs or delta format.
There is no `crown rows` workflow: original `crown compile/run` stays set-oriented,
and the aggregate CLI requires aggregate SQL.

Resolve `CrownConfig.cmake` from one chosen SDK and recompile against its matching
headers/libraries. Do not mix fixed-layout public objects from the frozen R1
SDK with new libraries. Version 0.1.0 / API 1 does not establish mixed-build ABI
compatibility or upgrade an old state file.

## 2. Bind the real query and select its actual plan

For a durable row owner, set the new flag before genuine compilation:

```cpp
crown::frontend::SqlRowsBindOptions binding;
binding.retain_binding_image = true;
auto result = crown::frontend::bind_sql_rows_into(account, sql, catalog, binding);
// Inspect SqlRowsProgram versus BindingDiagnostic before using the program.
```

Default false remains correct for ordinary in-memory output. Its empty
`binding_image()` means metadata was unrequested, not that SQL is invalid.
`source_sha256()` has the same meaning with either retention choice. Durable
record/descriptor admission requires the retained image and rejects absence;
its cold rebind requests retention explicitly. Do not manufacture/import image
bytes to bypass that check.

Export the genuine program's core and choose a tree for that core. Aggregate
programs use their actual `source_program().export_core()`. Runtime/Session
factories check the real immutable program again; an edited export is not an
admission token. A library-supplied tree establishes validity/upper height only.
The existing strict minimum-height CLI policy and evidence requirements remain
unchanged; resource exhaustion does not authorize a heuristic minimum claim.

Preserve exact original SQL, full catalog/schema versions and typed parameter
values: even an SQL alias/comment can change the conservative source identity.
Aggregate composition additionally binds its kernel/decoder, output scale and
parser provenance. SQL/schema/parameter changes require a new genuine program;
operational or output-policy changes require a new owner/descriptor, even when
the source hash is unchanged. Do not relabel an old hash or selected root.

## 3. Rebuild from complete physical facts

Use a fresh root/sink namespace for the chosen family. No automatic set-to-bag,
row-to-aggregate or old-root format migration is provided. Keep old files for
inspection; creation refuses existing destinations and never silently adopts
unselected candidates. Use `recover_into` only for an existing compatible selected
root.

Load/replay original complete physical rows, including unused tables and columns,
filtered rows and hidden witnesses. A projected set answer or aggregate snapshot
cannot recover those facts or their multiplicities. If original facts are sets,
assigning weight one to each complete fact is an explicit application conversion;
the genuine factory/update path must still validate types, constraints and
arithmetic. Do not copy native indexes or group caches into a new owner.

R1 JSONL/binary insert/delete records and CROWNSK1 are not R2 input/sink formats.
The [aggregate JSONL reader](sql_aggregate_input.md) carries the original aggregate
binding hash, source schema, complete nullable rows and before/after weights.
It is not a plain-row input reader. A row-Session caller supplies the typed
`InputView`/`SourceReplacement` API itself. Keep source names distinct from SQL
aliases and preserve actual consumed external input prefixes: a saved byte
offset is not a content hash.

## 4. Translate update and result handling explicitly

| Old assumption | R2 action |
| --- | --- |
| Insert/delete implies weight 0/1 | Supply authenticated full-row `before` and desired uint64 `after`; weight zero means absent |
| A transport batch is one transaction | Choose ordered R1 events or one explicit physical `NetBatch`; do not remove observable barriers |
| Repeated row edits are independent | Chain expected weights exactly, then validate the consolidated final state |
| No output means no commit | Empty/no-op/cancelled commands still commit C; source change may produce no visible output change |
| Root weight is the SQL answer count | Read the proper result cursor/snapshot; native root weight counts inner complete witnesses |
| Every delta fits int64 | Read sign plus uint64 magnitude, including UINT64_MAX retractions |
| Every change is a group event | Rows use nullable SQL tuple changes; aggregates use full group identity with optional before/after tuples |

Final-state UNIQUE/FK checks can accept an atomic swap that immediate row-by-row
updates reject. The same private native epoch applies all alias effects and
rolls back on preparation failure. Group state consumes genuine source facts and
consolidates touched groups; it does not keep an owning joined-row ledger.

For in-memory row deltas call `prepare_output_batch`, then use `output_size()`
and `output_change(index, exact_width_scratch)`. Reads spend one retained row/field
allowance across all passes. Values borrow the active token and scratch; token
closure or scratch reuse ends them. Raw native preview facts precede SQL
DISTINCT/EXISTS presentation. A bag result owns tuple/schema and multiplicity;
a cursor holds its reader lease through the final result until terminal `next`,
`cancel` or destruction. Prepared tokens retain their genuine owner even if the
runtime facade dies. Serialize calls on each owner.

EXISTS has one Boolean at C0 matching actual inner presence: FALSE for an empty
named input, while an admitted static no-FROM source can yield TRUE. Its delta
retracts the old Boolean and inserts the new Boolean only on a truth change;
initialize consumers from the actual C0/current baseline. Aggregate global-empty state similarly contains
COUNT 0 / NULL SUM/AVG. A present all-NULL group is not absent, and a zero SUM does
not remove it. AVG retains exact sum/non-NULL count, uses declared scale 0..18
and half-away rounding, rather than floating-point or averages of prior averages.
Inner integer casts retain range checks even when widened again. See
[aggregate types and empty behavior](aggregates.md).

## 5. Preserve the durable state machine and limits

Create a row Session with the genuine retained program, checked tree, explicit
runtime options and fixed `OutputLimits`; aggregate Session instead requires its
separate `Options::capture_changes=true`. Operational options are descriptor-bound
and preserved by rebind. Receiving/cold limits do not rewrite those policies or
mint another memory account.

Use the [row](sql_rows_session.md) or [aggregate](sql_aggregate_session.md) sequence:

1. `log` owns/funds one complete input and progress before its Input sync.
2. `decide` resolves that same head; Commit sync precedes publication of the
   already prepared native/source/group state. Semantic Reject advances I alone.
3. `deliver` confirms the whole actual local sink epoch before releasing output.
4. Log another command only at W=I and D=C with no head/spool. Checkpoint only at
   that same quiescent boundary.

Resource/contract errors have no semantic Reject tag. Keep a healthy pending
head; do not log it again or skip to later input. Uncertain file I/O or the
owner's `requires_reopen()` requires a fresh owner over actual surviving files.
A missing stdout report does not prove that a decision/delivery failed.
Recovery authenticates selected metadata, physical rebuild, decisions, output
and actual sink coverage before admissible torn-tail repair. Complete corruption
cannot be repaired by truncation. Repairs of the two files are sequential, not
pair-atomic. Local duplicate confirmation does not provide external exactly-once
delivery.

Row and aggregate Sessions retain history from generation one. The default 128
cap checks the absolute selected generation on rotation/recovery; reopening does
not refill it. No R2 retirement is implemented. Plan a finite run or an explicit
new owner/application rebuild at that boundary; do not delete retained files or
claim unbounded operation. No unbounded-history feature is required by this
bounded profile.

Fund actual metadata/source/native/group/spool storage under the chosen receiving
account. Keep source/native/index/group/output/codec/replay grants distinct;
SQL preview count does not cap intermediate capture, and its work counter does
not charge serialized bytes. Record codecs separately charge validation,
comparisons, sorting, copies and hashes. Checkpoint/rebuild, eager snapshots,
rendering and last-owner cleanup are real work. Host compiler/DOM/DTO/RSS
resources remain separately scoped.

The shared bounded POSIX I/O and transport PODs add no cross-family authority.
Use the matching typed Session/file owners under the documented
[local regular-file/lock/fsync premises](sql_aggregate_files.md). R2 file magic,
format versions and compatibility boundaries are listed in
[the compatibility table](r2_compatibility.md#persistence-identity-and-ownership).

## 6. Receive the migrated application

Keep an independent exact/SQL oracle for current tuples, multiplicities and the
appropriate changes, including NULL, cancellation, overflow, last loss and
recovery followed by the next update. Useful assertion sources are
[exact integer/AVG checks](../tests/integration/aggregate_integer_oracle.py),
[original aggregate oracle](../tests/integration/sql_aggregate_runtime_oracle.py),
[row records](../tests/unit/sql_rows_records_test.cpp) and
[row Session checks](../tests/unit/sql_rows_session_test.cpp) and
[durable fault checks](../tests/unit/sql_rows_session_fault_test.cpp).
Assertions are not execution receipts: join the actual chosen SDK/source bytes
to current terminal results and the relocated unseen-query workflow. Keep
extended-report measurements at their original source/machine/output scope;
these guides add no performance or release acceptance claim.

Approximation, shared-query optimization and parallel/distributed execution
remain deferred. Keep each query independently owned. Preserve existing rights
and notices; the user's deferred licensing disposition is unchanged.
