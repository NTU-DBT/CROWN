# Projected multiplicities and local visible factors

W03 is verified for the scope in the
[verification record](verification/w03-projected-bags-2026-11-11.md).
This specifies the direct-CQ weighted logical-port extension
to [W02 full subtree messages](weighted_messages.md). The primary output is one
owning core tuple with its exact positive multiplicity. Expanded repeated-row
output is optional and is not the primary representation. SQL bag admission,
physical bag-source routing, aggregate payloads and recovery are later W cards.

## Factor specification

Let `F` be the set of output variables and `C*` the checked maximal root-connected
subtree whose incoming separators contain only variables in `F`. It covers `F`.
Let `V_v = scope(v) ∩ F`. W02 maintains the full-row subtree value `T_v(t)` and
full separator message `A_v(k)`; these include every descendant's weight.

For each `v` in `C*`, define a contribution only for a surviving full row:

```
local_v(t) = 0                                      if T_v(t) = 0
local_v(t) = w_v(t) * product(A_c(t[K_c]) for c outside C*) otherwise
factor_v(u) = sum(local_v(t) for t[V_v] = u)
```

A generalized candidate uses `w_v(t) = 1`. Its candidate scope is not an extra
input relation. Positive factor keys form the existing compiled visible `E_v`
relation. The cursor joins those visible relations on their compiled separators
and emits:

```
(output assignment a, product(factor_v(a[V_v]) for v in C*))
```

An enumerated child's full message is absent from its parent's local factor.
For example, if `R(x,y)` has weight 2 and an enumerated `S(y)` has weight 3,
the row's multiplicity is `2*3=6`. Multiplying R's full subtree 6 by S's factor 3
would incorrectly produce 18. If hidden witnesses give a child total 7, that
total enters either an outside child's message or an explicitly enumerated
child factor, once.

## Why this factorization is correct

Delete edges between nodes of `C*`. Each resulting component contains exactly
one node of `C*`, together with its outside descendants. These components
partition all native occurrences. Running intersection implies that a hidden
variable cannot cross a deleted edge: such an edge's separator is output-only.
Once an output assignment is fixed, hidden choices in distinct components are
independent. Expanding their finite sums and multiplying counts every compatible
complete native witness once, with each native weight included once.

Restricting a node's local contributions to surviving full rows does not discard
a witness of an emitted assignment. For an inside child, its key is determined
entirely by `u`; its support condition is therefore uniform over all full rows
projecting to `u`. If the cursor chooses a complete compatible assignment of
positive visible keys, those inside-child conditions hold. Outside support is
already included in the local product. Conversely, every positive complete
witness contributes a surviving row and visible key at each node of `C*`.

The argument includes generalized nodes. The guard rule puts a generalized
scope inside every child's scope. A surviving candidate represents one scope
assignment, with unit local weight; compatible child witness choices contribute
their ordinary products. When the generalized scope contains hidden variables,
they must be summed before emitting its visible key. When its children are
enumerated inside `C*`, their weights are excluded from its local contribution.

A complete assignment of visible keys determines one output tuple, and that
tuple determines every selected visible key because their scopes lie in `F`.
There is no deduplication history or Cartesian hidden-witness materialization.
Repeated output columns preserve the declared head order; they do not create a
second factor. Empty output uses the same argument and emits at most one empty
tuple with the complete witness count. Constant true/false use unit/zero counts.

This is a local engineering proof for checked exact nonnegative multiplicities,
not a guarantee for arbitrary semirings or a maintenance/delay theorem. It
specializes Refactor.md §10.2 and corrected
[P1 arXiv:2301.04003v2 §7.3, equations(10)–(14)](https://arxiv.org/pdf/2301.04003v2).
The [paper guide](code_review.md) fixes the exact version. P1's projected local
annotations and W02's full subtree messages are different values.

## Maintenance and cost contract

Use the admitted visible tables/indices; store a scalar factor contribution in
each full row and a sum per visible key. Keep undo before mutation, and preserve
the one original account/grant for all stages. A positive-to-positive inside
child change does not change the parent's local contribution. An outside child
change or native-weight change can change it numerically. Support zero crossings
insert/remove affected contributions and visible keys. Generalized partial
candidates still contribute zero.

No global rebuild or witness enumeration belongs in update maintenance. Cache
the row's old contribution so subtraction needs no child-array copy or division.
Compute only the new outside product when required; charge visited factors and
actual table/metadata changes. The new scalar/map costs are explicit native
state, not free instrumentation. W02's full message limits remain in force.
Outside child positions are compiled once into one flat immutable array, with
two range offsets per node. Updating a local factor does not rescan enumerated
siblings, and an all-inside node needs no outside product/list allocation.

The committed result cursor uses one frame per compiled visible enumeration
step. It follows live/bucket cursors, borrows selected tuples under a reader
lease, and caches scalar prefix products for backtracking without division.
It allocates no collection of results and retains no emitted-row history.
Each returned row owns its original-account payload. Multiple readers may
coexist; every writer, including no-ops, is blocked until readers close.

Call `results()` to open a committed cursor, then `next()` until it returns
`nullopt`. Output tuple order is unspecified. A single caller may interleave
multiple cursors; this API does not provide concurrent thread synchronization.
Returning the last tuple still holds its reader lease: a terminal `next()`,
`cancel()`, destruction or failure closes it. Calls after exhaustion or
cancellation return `nullopt`; a call after failure raises `invalid_cursor`.
Previously returned owning `Result` objects remain valid after any of these
closures and after runtime destruction.

Captured `FactorChange` records describe changes to local visible sums. They
are inspection records, not projected answer deltas: a changed local factor
can participate in many joined output tuples.

Cursor startup/next/termination/failure work and native grant consumption must
be reported separately. One finite cursor grant spans all next calls. Native
output allocation, key projection, map/hash costs and cleanup remain explicit;
no constant public delay or CPU-time bound is claimed. Output size is the number
of distinct tuple/multiplicity records; expanded logical size is the sum of
their multiplicities.

The cursor snapshots root existence at startup under the committed reader
contract. It does not re-read the root message for every emitted tuple. Closed
cursors retain their metadata/diagnostics and caller-owned scratch capacities
until destruction; mutable runtime state is released when the reader closes.

## Required verification

Compare projected counts with an independent complete-assignment arbitrary-
precision oracle after every update, including raw duplicate input bags folded
into logical tuple weights. Mandatory cases include the two-level counted path,
hidden summation, deep outside branches, nested generalized nodes with a smaller
parent separator, sole-output-root, empty/disconnected scopes, repeated output
columns and counts above 2^53. Native logical replacements are the public input
boundary at this card; raw physical bag events/SQL are not silently admitted.

Also check factor state, membership versus numeric changes, all-stage rollback,
allocation/work/heap/native-grant limits, reader and move lifetimes, owning rows,
early cancellation/exhaustion/failure and churn. Existing set/W02 behavior and
public installation must remain valid. The executed component acceptance is
linked above; full repository semantic review remains open.


## Explicit support capture

V63 adds `DeltaCapture::support` as a separate opt-in meaning. Numeric
`enabled` capture and its `BagDeltas` handle retain exact uint64 differences.
Support capture publishes a distinct `SupportDeltas` handle of signed unit
membership changes, using the same private accumulator and visible-factor walk.
Positive-to-positive factor changes still perform numeric maintenance; only the
support-output walk is skipped. Changes telescope through private stages.

The [SQL output/recovery guide](sql_rows_session.md#prepared-sql-changes) states
the local Boolean factorization argument and decoding boundary. This adds fixed
policy/handle storage and optional capture work; uncaptured paths allocate no
capture buffer. It does not add a new update/delay theorem or accept V04.
