# SQL admission and implementation boundaries

For the current implemented interfaces, use [interfaces and guarantees](guarantees.md)
and the [SQL quickstart](quickstart.md).

The table below contains historical, mixed-stage implementation notes. Its rows
were written at different project checkpoints, so the “Current status” and
“Planned task / boundary” cells are not one current status snapshot. For current
task status, see [task_ledger.md](task_ledger.md). The SQL guides below specify
the implemented parser, binding, normalization, and frontend/structural admission
contracts. Admission reports `execution_status:not_lowered`; it does not claim
maintained SQL execution or allocator/runtime guarantees. Broader R1/R2/R3 goals
remain in [Refactor.md](../Refactor.md) §2.3.

| Feature | Current status | Planned task / boundary |
| --- | --- | --- |
| Direct typed CQ, set semantics | implemented reference path | A03/A04; no optimized runtime |
| Projection, arbitrary arity, disconnected conjunction | reference path | Native runtime/planner still required |
| Empty-head Boolean CQ / empty conjunction | reference path | SQL EXISTS wrapper is separate |
| Repeated variables, typed constants, ignored physical columns | reference path and SQL adapters | Support-counted projection retains full physical identity |
| Equal/contained scopes and self-join occurrences | reference path | No atom elimination |
| int64, binary strings, bool | reference path | Full initial scalar set remains F01 |
| Exact decimal / finite Gregorian date | reference path, CQ format 2/3 and SQL adapters | [Scalar contract](scalars.md); no implicit rounding/conversion |
| Catalog metadata / enforced unique and FK constraints | standalone catalog and CQ format 3 | [Catalog contract](catalog.md); full-state reference enforcement, separate hints/statistics |
| Normalized program schema / executable artifact reader | strict v1/v2 schemas and version-specific complete replay | [Version policy](schema_evolution.md); v2 grounds fixed equality classes; v1 replay is frozen |
| Canonical query / output / cost identities | versioned SHA-256 profiles and explicit ID maps | [Identity contract](query_identity.md); exact colored labeling, no partial hash on resource stop |
| CQ format upgrades | explicit upward migration 1→2→3 | Ordinary writers preserve versions; all downgrades reject |
| SQL name resolution / type and cast checking | `bind-sql`, owned typed IR | [Binding contract](sql_binding.md); source diagnostics, no native admission |
| Timestamp / locale collations / implicit casts | rejected | Separate explicit type/coercion contracts required |
| NULL-bearing inputs | rejected | Non-null classical core; SQL behavior in W05 |
| Duplicate insert / absent delete | no-op, committed epoch | Strict ingestion mode unavailable |
| Plain/bag SELECT, COUNT/SUM/AVG, GROUP BY | unavailable | W01 arithmetic policies are verified; runtime/SQL W02–W06 remains; never silently DISTINCT |
| SQL syntax parsing / source locations | `parse-sql`, syntax only | [F02 wrapper](sql_parser.md); no binding or execution |
| SQL DISTINCT / aliases / equality joins / comma joins | grounded normalization and integrated structural admission | [F06 contract](sql_admission.md); physical lowering/execution remains |
| SQL USING / NATURAL / CROSS JOIN / EXISTS | normalized with ordered output/wrapper mapping | EXISTS maps a nullary core to one false/true scalar row |
| SQL local comparisons / Boolean and NULL predicates / typed parameters | executable bounded local adapters | SQL three-valued filters and concrete parameter specialization; arithmetic/functions rejected |
| CTEs/subqueries | unavailable | Optional carefully checked R1 inlining |
| Cross-relation comparisons | unavailable | X04; not equality CQ admission |
| Outer joins, relational negation, EXCEPT, union, recursion | unavailable | Separate later contracts; local Boolean NOT is supported |
| SQL ORDER BY / LIMIT/OFFSET clauses | rejected by current binders | Never ignore clauses; parser acceptance does not enable execution |
| Explicit snapshot top-k operator | implemented opt-in C++ API | [CROWN::topk](topk.md): exact collect/sort over current SQL row/bag or aggregate outputs; separate from SQL clause admission |
| Body/free-connex recognition | GYO via `classify` | P01; witnesses and failed cores; reference can evaluate other CQs |
| Structural tree validity and checked height | `validate-plan` | P02; valid upper bound only, explicit violation witnesses |
| Exact structural minimum and independent certificate replay | `tree-oracle` / `verify-height` | Complete finite-family search; explicit operational limits; cost not optimized |
| Typed tuple/key layouts and reference storage | `crown_core` library | S01/S02; compiled projections, primary/secondary indexes, live cursors and per-table rollback; [contract](storage.md) |
| Supplied-tree physical lowering | `lower-plan` / `lower-normalized` | P08; immutable typed programs, source bindings and exact replay; [contract](physical_plans.md) |
| Broader planner / CBO policies | partial or unavailable | P04–P07/C tasks remain incomplete; lowering a valid tree does not prove its minimum |
| Logical native/generalized support and exact P/E | reference kernel / `support-trace` | R01–R04; logical rows, affected-record journals, causal accounting and per-update rollback; [contract](runtime_support.md) |
| Physical SQL epochs / initialization / lazy cursors | unavailable | R05–R06 / D01–D06; internal support events are not full-answer deltas |
| Row replacement / atomic net batches | unavailable | Separate update contract, O03/W06 |
| Streaming codecs / windows / CDC row identities | unavailable | O01–O03 |
| Checkpoint / WAL / sink backpressure | unavailable | O04–O06 |

CLI diagnostics are JSON with `error.code` and `error.message` on stderr,
exit 2 for declared input/usage rejection, exit 3 for unexpected internal
failure. `validate-plan` additionally returns exit 1 for a structurally invalid tree,
with its report on stdout. `parse-sql` returns a syntax result on stdout,
exit 0 for one parsed statement and exit 1 for encoding, syntax, statement-count
or resource diagnostics. It never routes SQL to the evaluator.

`bind-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json]` returns exit 0 for a
bound program, exit 1 for syntax/binding/resource diagnostics on stdout and
exit 2 for CLI/configuration/I/O errors on stderr. It preserves plain SELECT
bag requests and never routes a binding to the native set evaluator. The
integrated admission commands distinguish syntax/binding errors, unsupported
semantics, cyclic body, non-free-connex head and resource exhaustion.

`normalize-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json [PARAMETER_VALUES.json]]`
returns exit 0 for a normalized program and exit 1 for syntax, binding,
normalization, unsupported-semantics or resource diagnostics on stdout.
Configuration/I/O errors use stderr and exit 2; internal invariant failures
use exit 3. Nullable referenced source columns are rejected explicitly, even
when unused. NULL literals/parameters can enter local SQL predicates but never
become core values. Changing parameter values requires a new program/state.

`admit-sql INPUT.sql CATALOG.json [OPTIONS.json]` and
`admit-normalized PROGRAM.json [WORK_LIMIT]` report `admitted`, `syntax_error`,
`semantic_error`, `unsupported_semantics`, `cyclic_body`, `non_free_connex`, or
`resource_limit`. Admission success returns exit 0, rejected/incomplete requests
exit 1 on stdout; malformed configuration/artifact/I/O uses exit 2 on stderr.
Every report has `admission_scope:frontend_and_structure` and
`execution_status:not_lowered`. Full body/head witnesses are retained;
recognition exhaustion returns no partial class. A proven contradiction uses
an explicit constant-empty route while retaining its actual shape class.
The [machine-readable SQL matrix](../tests/frontend/admission/manifest.json)
records feature coverage, expected outcomes and manual/SQLite rows.

The structural oracle returns exit 1 for a completed empty admissible family
or a resource stop, with separate `unsupported` and `resource_limit` statuses.
`verify-height` returns exit 1 for an invalid certificate or replay limit and
exit 2 for malformed certificate input. Both commands operate on the supplied
CQ shape; physical data is excluded from the certificate binding.
