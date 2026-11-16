# Interfaces, semantics and guarantees

## Choose the interface

| Interface | Implemented boundary | Detailed contract |
| --- | --- | --- |
| `crown compile`, `run`, `restore`; `CROWN::runtime` | Non-null supported equality SQL, free-connex set execution or a checked constant-empty route; local durable sessions | [CLI](cli.md), [admission](sql_admission.md), [semantics](semantics.md) |
| `CROWN::sql_rows` | Opt-in nullable physical rows, plain SELECT bags, DISTINCT, constants and EXISTS; caller supplies a genuinely checked tree | [SQL rows](sql_rows_runtime.md) |
| `crown aggregate`; `CROWN::sql_aggregate_recovery` | Admitted nullable COUNT/SUM/AVG, grouping, atomic weight replacements, native checkpoints and local delivery | [Aggregate CLI](sql_aggregate_input.md), [runtime](sql_aggregate_runtime.md), [Session](sql_aggregate_session.md) |
| `CROWN::topk` | Explicit exact snapshot sorting of genuine nullable-row and aggregate owners; compressed bag selection, declared NULL order and stable query-scoped identity | [Snapshot top-k](topk.md) |
| `CROWN::keys` with `CROWN::runtime` | Opt-in cold FK/UNIQUE rewrite of genuine non-null direct-CQ set plans; full source constraint state and general comparison plan retained | [Key-aware plans](key_specialization.md) |
| `CROWN::star` | Opt-in initially empty serial exact-set center/unary CQ owner; real heavy/light routes and projected snapshots, separate source and cleanup costs | [Star prototype](star.md) |
| `CROWN::comparisons` | Explicit non-null public-IR conjunction; ordinary propagation and exact full-assignment recomputation, owning snapshots and atomic endpoint set deltas | [Comparisons](comparisons.md) |
| `CROWN::fallback` | Explicit non-null exact-set general CQ; actual class/reason, conservative full recomputation, owning materialized answers and atomic endpoint deltas; no original-query CROWN/GHD certificate | [Fallback](fallback.md), [source images](source_images.md) |
| `CROWN::difference` | Explicit positive non-null CQ pair; SET EXCEPT or BAG EXCEPT ALL over physical set sources, compressed checked counts and exact endpoint replacements, conservative recomputation | [Difference](difference.md) |

The interfaces use different input/binding formats. Decoding one format does not
admit a program for another. Unsupported constructs fail explicitly; parsing SQL
does not establish executable support. [The older SQL table](sql_support.md) is
historical evidence, not a current feature matrix. R3 proposals do not enable a
default fallback or change the semantics of an admitted query.

## Supported SQL forms

| SQL form | Current execution interface | Admission boundary |
| --- | --- | --- |
| `SELECT DISTINCT` with columns/constants, `*`/`alias.*`, self-join aliases and admitted occurrence-local predicates | Set CLI; nullable-row API | The set CLI requires its supported non-null frontend and completed free-connex admission, or the checked contradiction route. The nullable-row caller supplies a tree that the runtime checks against its actual exported core. Both binders reject unimplemented expressions/casts. |
| Comma/CROSS JOIN, INNER JOIN with ON, USING or NATURAL | Admitted source families in the corresponding interface | Preserve occurrence and merged-column rules; a disconnected product still needs a valid body/head plan. Join syntax alone does not establish free-connexity. |
| Plain row-producing `SELECT` with bag multiplicities | Nullable-row API | The set CLI rejects row bags; it does not insert DISTINCT. Weighted intermediate counts remain bounded even if final output is small. |
| Whole-result `SELECT EXISTS (...)` | Set CLI; nullable-row API | One EXISTS target over an admitted inner source, with no outer FROM or WHERE. Correlated subqueries are not supported. |
| Nullable physical source columns | Nullable-row API; aggregate CLI/API | The original set SQL frontend rejects nullable sources. NULL-sensitive equality and output identity follow the selected component's contract. |
| `COUNT(*)`, `COUNT(column)`, `SUM(column)`, `AVG(column)` with admitted casts and optional column `GROUP BY` | Aggregate CLI/API | Exact bounded arithmetic and declared AVG scale apply. Bare GROUP BY is not a substitute for DISTINCT; computed/cross-relation aggregate arguments reject. |
| DISTINCT aggregates, HAVING, windows and aggregate ordering/grouping extensions | Rejected by the aggregate binder | A parser accepting the syntax does not enable execution. |
| Outer joins and cross-occurrence scalar predicates other than extracted ordinary equality | Rejected by these positive-query source families | The documented local scalar VM is not a general join-predicate or outer-join engine. |
| WITH/CTEs, correlated subqueries, other nested subqueries beyond the whole-result EXISTS wrapper, UNION/INTERSECT/EXCEPT, DISTINCT ON, ORDER BY and LIMIT/OFFSET | Rejected by the current binders | These constructs need separate semantic/runtime contracts; parser acceptance does not make them executable. |

These are supported families, not all combinations of PostgreSQL syntax.
[Set normalization](sql_normalization.md), [nullable-row admission](sql_rows_runtime.md)
and [aggregate binding](sql_aggregate_binding.md) define exact casts, expressions,
parameters, domains and rejection precedence.

The optional [snapshot top-k API](topk.md) ranks already admitted owner outputs.
It collects and sorts the current compressed snapshot on each call. Its C++
interface does not add SQL `ORDER BY` or `LIMIT/OFFSET` admission.

## Rows, updates and ownership

The set interface identifies a row by all typed physical cells, including ignored
columns. Duplicate insertion and absent deletion are no-ops with committed input
epochs. Self-join occurrences remain separate; deleting one physical support need
not delete a projected result. [Semantics](semantics.md) defines scalar equality,
collation and constraints. Nullable bags and aggregates have their own documented
NULL, multiplicity, overflow and output rules.

A result cursor holds a read lease on one committed epoch. Drain its terminal
null or cancel it before an update. Returned owning tuples can outlive the cursor;
views into a tuple still require that tuple's payload. Calls require external
serialization. See [cursor lifecycle and costs](result_cursors.md) and the
[runnable example](cursor_example.md).

## Height evidence and performance

A checked supplied tree is an executable upper bound. A completed independent
height proof establishes the claimed minimum within the defined admissible tree
family. A search/resource stop is not an optimum. The set CLI independently
replays an artifact's proof; a constant-empty CLI artifact instead reports
`checked_constant_operator` with a null certificate. The selection API has its
own original-query proof and binding rules, described in
[selection](selection.md) and [artifact binding](selection_binding.md).

Minimum structural height does not establish minimum CPU, memory or modeled cost.
The [ordered producer argument](ordered_delta.md#bounded-production-and-explicit-finalization)
bounds indexed actions for a fixed verified query after route preparation. It
retains ordered-dictionary comparison, key/payload width, allocator and cleanup
costs. Public atomic startup includes the entire prepared epoch and spool;
finalization and last-owner destruction have separate costs. Neither finite
fixture counters nor a paper citation alone prove constant wall-clock delay.
The [paper/source map](code_review.md#exact-paper-versions) distinguishes exact
paper versions, local engineering arguments and remaining review obligations.

## Resource and recovery limits

Native allocations share the original finite query account. Work, encoded bytes,
spool limits, caller DTOs, compiler scratch and RSS are distinct measurements;
one cap does not bound all of them. Optional observations measure only their
documented scope. [Memory](query_memory.md), [CLI limits](cli.md#limits-and-verification)
and [measurements](measurement.md) explain the boundaries.

Checkpoint/restore and durable local output use the specified journal, binding
and acknowledgement protocol. A report is not a receipt. Uncertain I/O requires
recovery before retry, rather than guessing whether publication occurred.
The [set Session](session_lifecycle.md) and [aggregate Session](sql_aggregate_session.md)
have separate recovery contracts. Aggregate history retirement remains an open
packaging limit. Current interruption tests cover their stated finite profiles;
they do not certify arbitrary hardware power loss or every possible instruction.

The [ledger](task_ledger.md) tracks implementation and release acceptance.
Licensing, independent whole-system review, experiments and release gates remain
separate from local installation and documented feature acceptance.
