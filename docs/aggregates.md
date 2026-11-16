# SQL aggregation (W04)

This is the implementation contract for W04. The [ledger](task_ledger.md)
records scoped implementation and acceptance as verified;
[the evidence record](verification/w04-aggregates-human-inspection-2026-11-12.md)
sets out the executed gates and limits. The existing row/set SQL
compiler and C05 policies retain their supported semantics. W04 introduces an
explicit aggregate library over typed logical bag rows; W05 covers general SQL
bag/source and NULL/type admission, and W06 covers coordinated aggregate
transactions, batches and recovery.

The separate [prepared logical aggregate net-batch API](aggregate_batches.md)
prepares final touched groups before one publication. It preserves this W04
single-row contract; genuine source composition and durable coordination remain
later W06 work.

## SQL and numeric contract

COUNT returns bigint; COUNT(expr) excludes NULL, while COUNT(*) includes every
input row. SUM and AVG exclude NULL arguments and return NULL without a
non-NULL contribution. Integer SUM widens according to the argument type.
These rules follow the [PostgreSQL 18 aggregate reference](https://www.postgresql.org/docs/18/functions-aggregate.html).
The chosen fixed AVG output uses exact decimal rounding, with half ties away
from zero, consistent with [numeric rounding](https://www.postgresql.org/docs/18/datatype-numeric.html).

The first admitted aggregate syntax has one flat logical input relation,
optional GROUP BY input columns, ordered/repeated group outputs and
COUNT/SUM/AVG outputs. Arguments are resolved columns or supported constants
and exact integer casts. COUNT accepts the declared scalar kinds. SUM/AVG
initially admit integer arguments. All aggregate DISTINCT forms are rejected
explicitly; no unused per-group distinct-value reference tables are installed.
Joins, predicates, HAVING, windows, nested aggregates, grouping extensions and
other functions require separate admission work.

| Expression | Declared result |
| --- | --- |
| COUNT(*) or COUNT(expr) | Non-null signed bigint, 0 through INT64_MAX |
| SUM(integer argument) | Nullable bigint, with checked result range |
| SUM(bigint argument) | Nullable NUMERIC(38,0) |
| AVG(integer/bigint argument) | Nullable NUMERIC(38,s), default s=18; admitted scale 0..18 |

AVG's fixed scale is an explicit local output contract, not a claim that every
SQL engine chooses the same implicit scale. The SQL oracle uses SQLite
GROUP BY, COUNT and integer SUM on small expanded bags, then rounds their
SUM/non-NULL COUNT ratio with exact Fraction arithmetic. SQLite floating AVG
is unused. Large compressed weights compare COUNT outputs directly with SQLite integer
SUM(weight) and conditional SUM(weight) identities, without expansion. Their
wide numeric SUM/AVG use a separately labelled Python integer/Fraction model.
Both oracle cohorts exercise all nineteen admitted AVG scales. Incoming group multiplicity is bounded by INT64_MAX, so COUNT stays
representable and integer sufficient statistics stay bounded.

An ungrouped query always has one aggregate result: empty input yields zero
COUNTs and NULL SUM/AVG. A GROUP BY query has no groups on empty input; removing
a group's last row removes that group. NULL grouping keys form one group per
remaining key combination. Group existence follows total input multiplicity,
independently of signed cancellation or the number of non-NULL arguments.
A no-FROM aggregate consumes SQL's implicit singleton row, distinct from an
empty named input relation. Ordered outputs are preserved; equal output rows
from different groups retain their distinct group identities.

## Logical input and publication

The producer supplies complete typed logical rows and exact before/after
multiplicities. This is the compressed bag boundary established by
[W03](weighted_enumeration.md), rather than a new physical-source bag backend.
A replacement checks the committed prior weight and next epoch. Duplicate
values are one logical row with a multiplicity; no repeated-row expansion is
required. NULL stays at this SQL boundary and does not enter classical core
ScalarView or tree/storage admission.

Compilation resolves input/group/argument positions and output types once.
Updates use those numeric descriptors. Retained row/group keys and temporary
work use the receiving MemoryAccount; incoming DTOs remain borrowed caller
values. New keys are copied only when retained. A component scratch array holds
one affected group's proposed sufficient statistics, avoiding a whole-state
copy or an automatic full-result scan on each update.

An argument cast from a physical bigint column to integer retains the raw input
type and adds one immutable range guard per distinct column. Projection checks
non-NULL values against INT32_MIN..INT32_MAX before group mutation; an inner
integer cast remains checked even when widened back to bigint. COUNT evaluates
these casts too. The final argument type still selects the result rule above.
The guards add no per-row state or allocation; each check spends one selected
work unit. The immutable vector header and empty-loop check have a fixed cost
even for programs without narrowing casts. See the
[composed runtime](sql_aggregate_runtime.md) for physical-source evaluation.

All arithmetic, input admission and requested output preparation precede
publication. A failure preserves the old row weights, group states, epoch and
previous results. Requested change events identify the group and its ordered
before/after output, including creation/removal. Event formatting is explicit
output work. General weighted-runtime transaction coordination and durability
remain W06 acceptance work.

## Bounded integer sufficient statistics

The private [integer primitive](../src/runtime/aggregate_integer.hpp) uses a
signed magnitude with two uint64 words. For admitted group count C and values x,

```text
C <= 2^63 - 1, |x| <= 2^63
|sum(weight * x)| <= C * 2^63 < 2^126
```

The sum therefore needs at most 38 decimal coefficient digits. Add/retract
intermediates fit below 2^127 after the caller admits the group count. The
private helpers use these preconditions instead of repeated generic overflow
handlers. Input/count/output range failures belong at the group publication
boundary. SUM state can be zero while the group remains present.

AVG retains this exact sum and its separate non-NULL count. Quotient and
remainder are scaled separately: multiplying the complete sum by 10^s would
require an unnecessarily wider intermediate. For s<=18, each scaled quotient
or remainder fits 128 bits. Divisors are positive and at most INT64_MAX, so the
long-division remainder can shift one next bit safely in uint64. Rounding uses
the exact final remainder. No floating-point value decides a count, sign,
rounding boundary or group membership.

State arithmetic uses fixed inline words, no allocating big-integer object.
Decimal text uses bounded stack scratch only for requested output; InlineDecimal
owns the resulting coefficient. This is a local bounded-arithmetic argument,
not a paper update-time theorem. Key lookup, variable-width field comparisons,
allocation, group-state work and output demand retain their real costs.

## Public usage and ownership

Link the explicit `crown_aggregate` library and include
[`crown/frontend/aggregate.hpp`](../include/crown/frontend/aggregate.hpp) and
[`crown/runtime/aggregate.hpp`](../include/crown/runtime/aggregate.hpp).
`bind_aggregate_sql` returns either an immutable `AggregateProgram` or a binding
diagnostic. Check that variant before constructing `AggregateRuntime`. Binding
errors are a cold frontend boundary; allocation failures and parser contract
failures propagate. An update has no catch or undo journal in its execution path.

A caller can fund compilation and execution from one existing account using
`bind_aggregate_sql_into(account, sql, catalog)` and
`AggregateRuntime::create_into(account, program, options)`. Neither call creates
another byte allowance. Standalone forms instead create separate finite compiler
and runtime accounts. Retaining an already funded immutable program from another
account is explicit; every new runtime key, node, scratch buffer and requested
output uses the receiving runtime account. Account statistics measure requested
allocation bytes, including framing, rather than resident memory.

`aggregate::Update{sequence, values, before, after}` borrows a nullable logical
row for one synchronous call. Start at sequence 1. For example, replacing a
row's weight from 0 to 3 admits three identical bag contributions without
expansion. The next replacement of that same complete row must supply before=3.
A valid no-op still advances the epoch. `apply_weighted` accepts W03's owning
compressed tuple view directly, with the same weight contract and no owning
nullable DTO conversion. Feeding multiple producer results remains an explicit
caller operation; it does not coordinate a transaction across runtimes.

Capture is off by default. `Epoch.changed` records whether input weight changed.
With `Options.capture_changes=true`, `Epoch.output` contains a group identity and
optional before/after value tuples only when its visible output changes. An absent
group differs from a present tuple of NULL cells. Rounded equal AVG outputs can
therefore accompany changed input without a value event. Events own their key and
value payloads; the event does not independently retain the program schema.
`snapshot()` retains its program metadata, shared group keys and newly copied
output tuples. Results can outlive the runtime. `Tuple::view()` borrows from an
lvalue tuple; `export_values()` creates ordinary caller-owned values explicitly.

Serialize every call on one runtime, including const snapshots and invariant
checks: those operations reuse scratch and the same mutable allocation account.
No locks or concurrent-reader protocol are installed. `check_invariants()` is an
explicit full input/group recomputation and may allocate from the receiving
account. It is not called automatically by an update.

## Costs to inspect

Let F be input fields, K grouping fields, M distinct argument states, O output
fields, R retained distinct input rows and H live groups. An ordinary replacement
validates F fields and their string bytes, looks up one row and one group, and
copies/adjusts M proposed statistics. Ordered map lookup includes O(log R) and
O(log H) comparisons, each with its actual field/string comparison cost. Logical
work counters charge selected operations; they do not meter every comparison,
allocator action or CPU instruction.

New row/group keys copy only their retained fields and bytes. Grouping by every
input field in its original order can share one immutable row/group key. Existing
row updates reuse fixed scratch; a no-op stops after prior-weight validation.
With capture disabled, updates do not render or clear the O-column output buffer.
Repeated output aliases share argument state and add no per-update output pass in
that mode. Construction still reserves the declared output scratch once.

Requested capture renders the affected group's before/after values, when present,
and freezes owned tuples before publication. Its work scales with O and copied
output bytes; exact decimal formatting and AVG division also occur there. A
snapshot visits H groups, copies their outputs and funds its result vector; it
shares the immutable group keys. Destruction costs depend on which payloads lose
their last owner. Neither snapshot, last-owner release nor full invariant checking
is a constant-time primitive. The block contracts in the
[inspection index](code_specs/README.md) identify these ownership and cost
boundaries individually.

## Acceptance boundary

The scoped binder, group-state and event execution passes the independent SQL
statistics and exact arithmetic gates in the evidence record. Covered cases
include empty global/grouped input, NULL and all-NULL arguments, COUNT forms,
signed cancellation, large counts above 2^53, positive/negative AVG rounding,
last-row deletion, no-FROM singleton behavior, declared DISTINCT rejection,
old-weight/epoch/type errors, and arithmetic/allocation failure before
publication. W01/W02/W03 and existing SQL rejection/admission behavior remain
separate regression controls.
