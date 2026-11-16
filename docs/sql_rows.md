# SQL nullable rows and bags (W05)

W05 is verified within the [admitted nullable SQL family](sql_rows_runtime.md):
physical source rows, plain SELECT bags, ordinary NULL-sensitive equality joins,
DISTINCT, constants and EXISTS. The [verification packet](verification/w05-sql-rows-human-inspection-2026-11-12.md)
records matching engine types/casts/collation, native resource/fault gates and
unchanged set fixtures. W04's [grouped-aggregate boundary](aggregates.md) remains
separate; [original-SQL aggregate composition](sql_aggregate_runtime.md) and its
[durable Session](sql_aggregate_session.md) provide the W06 coordination path.

## Shared native scalar primitive

[`src/frontend/sql_scalar.hpp`](../src/frontend/sql_scalar.hpp) reuses the existing
native SQL adapter evaluator formerly local to `src/ir/program.cpp`.
[`CompiledProgram::adapt_input`](../src/ir/program.cpp) now calls the shared helper.
The old normalization v1/v2 wire meanings, non-null core rows and SQL source
admission limits are unchanged. The program factory still resolves valid opcode
arity, slot references and compatible types before execution.

A `Cell` is an optional inline `ScalarView`. NULL means no cell; an engaged false
Boolean remains a value. Strings borrow caller/program bytes, while integer,
Boolean, date and bounded decimal alternatives are inline. Copying a returned
Cell does not freeze its string. Retained output still needs an owning boundary.
No private scalar operation creates an account, owns a row buffer or invokes a
catch/rollback framework.

Ordinary comparisons with a NULL operand produce UNKNOWN. Boolean NOT/AND/OR and
Boolean/NULL tests retain SQL three-valued behavior; only TRUE admits a predicate
row. Typed identity/literal/widening operations transfer their already-bound
representation. USING transfers its left value; its mandatory equality predicate
is checked elsewhere. That transfer alone is not an outer join or COALESCE.
These rules follow the [PostgreSQL comparison reference](https://www.postgresql.org/docs/18/functions-comparison.html).
They do not change equality in the classical core or define nullable join
maintenance by themselves.

The caller may pass its existing `IndexWorkAllowance`. Each visited variadic
Boolean operand consumes one structural step. A present comparison admits left,
then right scalar fields/bytes before comparison. NULL comparisons do not debit
scalar payloads. A later failure preserves earlier consumed work; it does not
refund or refill a grant. String/decimal widths are measured without formatting,
but actual comparisons retain their field/byte costs. Slot/type/opcode contract
faults use fixed `IndexFailure` diagnostics. Work exhaustion follows the supplied
allowance's fixed/legacy mode. Malformed private value indices now use the fixed
contract fault rather than an old vector `out_of_range`; imported public programs
are fully validated and cannot rely on malformed private metadata.

## Current primitive and inspection gates

The [progress record](../build/verification/w05-start-v1/scalar-progress-v1.json)
records strict Debug and ASan/UBSan/leak gates on the same 1,117 maintained input
paths. Debug passes a 13-test cohort plus a separately selected `layouts` test;
sanitizer passes the same 14 names in one cohort. Raw LastTest logs are archived.
The first Debug command selected `layout` instead of the registered `layouts`;
the separate receipt closes that selection gap. Native controls cover existing
program adaptation, set binding/normalization/admission, physical execution and
exception handling, constant routes, layouts and arena behavior.

The new `sql_scalar_oracle` checks 3,439 matching-type cases across 20 scalar SQL
opcodes against DuckDB Python 1.5.4. CMake's selected Python interpreter must import
DuckDB; the test does not install it, skip it or fall back. No production library
links DuckDB. The oracle uses explicit BIGINT/INTEGER, BOOLEAN, DATE, VARCHAR with
its default binary collation and fixed DECIMAL(38,s) casts. Native output JSON
kind and value both match, so Boolean and integer results are not conflated.
Native computation runs with replacement-new denied; parsing, JSON output and
explicit rendering lie outside that observed interval. Separate C++ controls
check borrowed string identity, exact/one-under work, earlier debits on later
exhaustion, fixed contract errors and short-circuit reads. USING's left-only
transfer is a native control, not falsely labelled SQL join evidence.

Fixed DECIMAL comparisons are exact within each declared type; DuckDB cannot
represent the whole mixed unconstrained CROWN decimal domain with one fixed
scale. That limit is recorded in the
[engine inventory](../build/verification/w05-sql-oracle-environment-v1/README.md).
A separately extracted, apt-hash-verified PostgreSQL 16.15 toolchain is available
for further matching-type NUMERIC comparisons. An isolated
[engine capability probe](../build/verification/w05-postgres-probe-v1/README.md)
held both a 38-digit integer and 1e-38 exactly in one unconstrained NUMERIC column,
and checked selected NULL/grouping, date, Boolean and C-collation behavior. These
are engine capability observations, not SQL/CROWN agreement or exhaustive domain
coverage. Both temporary server starts were stopped and verified. The toolchain
is temporary test tooling and is not installed globally.
Its [receipt](../build/verification/w05-postgres-toolchain-v1/README.md) records the
exact binaries, libraries, source package hashes and support files.

The human inspection adds 84 storage contracts and three comments with identical
executable tokens, moves 10 scalar helper/branch cards to the shared header,
rechecks the remaining program cards and adds scalar/test/build usage cards.
That foundation had 3,644 contracts. Its 680 maintained files / 156,600 lines /
17,451 blocks are mapped, with 3,098 blocks containing scoped manual contracts.
Individual semantic review then remained open for 2,750 selected production blocks.
The source maps distinguish those gaps from reviewed behavior.

## Receiving-account and contribution foundation

The [weighted runtime](weighted_messages.md) now exposes `create_into` for one
actual receiver account and `PendingEpoch::stage_contribution` for an adapter's
`total - old + next` share replacement. The latter uses the existing native lookup,
transaction, queue and original indexed grant. It freezes a borrowed native-scope
view and adds no second aggregate-count map or abort catch. The source adapter
still has to validate full physical row identity, old weight and SQL semantics.

The [foundation verification](verification/w05-foundations-human-inspection-2026-11-12.md)
records 23 passing selected tests per Debug/sanitizer profile on the same 1,117
input paths. Matched creation/deletion/capture fixtures have equal allocation
request counts through the absolute and contribution ports. Receiving caps,
constructor/update allocation cuts, exact/one-under logical/index work, copied
borrowed scalars and previous-epoch preservation pass. A sixteen-file native
overlay and raw logs preserve these results before later active-build reuse.
Committed captures use actual totals; aborted diagnostics are partial attempts.
These native primitives alone do not implement SQL source routing or bag admission.

## Physical-row implementation

The new [SQL rows runtime guide](sql_rows_runtime.md) describes the opt-in
verified compiler/source/runtime path: nullable payload/presence
encoding, full source-row weights, self-alias routing, enforced UNIQUE/FK indexes,
owning schema/results, receiving accounts and publication. Its unit gates and
review packets extend the sealed foundation. The foundation's source and evidence
remain immutable; final SQL-row acceptance is recorded separately.

## Verified scope and remaining work

DuckDB 1.5.4 covers 55 SQL cases / 3,410 native snapshots; PostgreSQL 16.15 covers
61 / 3,782, including mixed-scale unconstrained NUMERIC and untyped NULL cases.
Both native storage backends are exercised. The final sanitizer cohort passes
54 tests; the changed SQL family also passes its current three-test Debug gate.
See the verification packet for exact source freshness and historical failures.

W04 supplies correct admitted NULL grouping. Bare GROUP BY without an aggregate
rejects; it is not rewritten as DISTINCT. Outer joins, cross-relation computed
predicates/outputs remain outside this family. Joined aggregates and durable
transactions use the separate W06 interfaces linked above; their bounded
[V33 acceptance](verification/human-inspection-v33-2026-11-13.md) is preserved.
Full repository human review and release gates stay
open. Current source-map counts and remaining individual review are in the
[inspection guide](code_review.md).
