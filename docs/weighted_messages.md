# Weighted subtree message maintenance

The public `runtime/weighted.hpp` interface implements W02's verified
logical native-port boundary for direct-CQ structural shapes. W03's
[local factors and projected cursor](weighted_enumeration.md) are verified
on top of these full messages. Implemented [nullable SQL rows/bags](sql_rows_runtime.md),
[SUM/AVG composition](sql_aggregate_runtime.md) and [durable aggregate Sessions](sql_aggregate_session.md)
have separate APIs and contracts; this message kernel alone does not provide them. The frozen
[W02 verification record](verification/w02-human-specs-2026-11-11.md) applies to
its source seal. No Boolean update bound is claimed for numeric values.

## Meaning of the maintained values

For a native node, every distinct logical scope tuple has an exact nonnegative
local multiplicity. A generalized node has unit local weight on each candidate
scope assignment. Zero multiplicity means absence. There are no signed row
weights, epsilon tests or arbitrary-semiring callbacks.

For a native scope tuple `t`, the full subtree value is

```
subtree_v(t) = local_v(t) * product(child_message_c(t[separator_c]))
message_v(k) = sum(subtree_v(t) for t with t[parent_separator] == k)
```

For a generalized candidate `s`, compute the product on its complete scope
first, then sum candidates projecting to the parent separator. For example,
`G(x,z)` above two child scopes containing both variables must sum different
`z` values when sending a message on `x`. Sending just a product per `x` would
lose that hidden-variable summation.

These are the full-subtree equations in Refactor.md §10.2. They describe
multiplicities, not arbitrary SQL expressions. P1's
[corrected arXiv v2 §7.3](https://arxiv.org/pdf/2301.04003v2) supplies the
aggregation context. Its projected local factors and equations(10)–(14) must
be distinguished from these full-subtree values: W03 must not multiply a child
message into a parent factor and explicitly enumerate that same child again.
The [human review guide](code_review.md) records the exact paper version and
separates paper results from the local implementation contracts.

Every tree root has an explicit empty-key summary: sum all its full scope
values. An empty conjunction has summary one; a contradiction has zero. This
summary counts complete witnesses and is not a projected bag result cursor.

The local correctness argument is induction over the checked tree. A leaf
contributes its native tuple weight. Running intersection ensures that sibling
subtrees share variables only through the node scope, so compatible complete
witnesses combine independently once their separator values are fixed. Their
weights multiply; distinct hidden assignments contribute separate summands.
For a generalized node, the guard condition places its complete scope in every
child, making each child key a complete candidate assignment. Summing those
products to a smaller parent key is still necessary. This argument explains the
full-subtree equations here; the separate projected-output factorization is
specified in [W03](weighted_enumeration.md). Neither argument is a maintenance-time theorem.

## Replacement, propagation and ordering

`weighted::Replacement` names a native node, complete scope tuple, expected old
weight and desired new weight. The expected value must match the owner; a
stale replacement fails with `weight_conflict`. Replacing a positive weight
with zero deletes that logical row. Equal weights are valid no-ops that still
consume their logical sequence. Generalized nodes have no external write port.

`PendingEpoch::stage_contribution(node, values, old, next)` is a separate adapter
port. It replaces one share in the current logical total: `total - old + next`.
For example, two source rows contributing 2 and 7 produce total 9; replacing the
first share with 5 produces total 12. The native record lookup supplies the total,
so the adapter needs no second map of aggregate native-row counts. The adapter
must retain and validate exact source-row identity and its own previous weight;
this arithmetic port cannot authenticate which source row owned a share.
Underflow, configured overflow or any later propagation failure aborts all stages.
Absolute and contribution replacements may be mixed in one pending token.

The `TupleValuesView` borrows a complete native scope, in ascending variable-ID
order, only for the call. Admission validates and copies it into the same funded
input-key representation used by ordinary replacement. Strings therefore incur
their real validation/copy/comparison costs; this is not an allocation-free update
claim. The new port adds one charged checked contribution replacement at the
existing lookup. It adds no retained count map, legacy `Row` mirror, larger queue
payload or additional rollback catch. Source-row SQL admission/NULL behavior is
provided by the separate [W05 SQL rows component](sql_rows_runtime.md).

Native rows cache each child's numeric message and their full product. A
changed child message visits the matching native reverse-index bucket. The
runtime recomputes the affected products without division, then replaces each
row's contribution in its parent's separator sum. It enqueues every changed
numeric message, including two-to-three changes whose membership stays positive.

Generalized candidates are the union of positive child-message keys on their
complete scope. A candidate's product is positive only in the intersection.
It is reclaimed when its last child support disappears. Thus an empty
intersection can retain candidates supported by only some children; those
candidates have subtree value zero and produce no parent message.

The work queue is FIFO. Before/after numeric events for the same key are causal:
`0→2` followed by `2→5` must update a cached child in that order. Each stage
drains its queue before another native replacement is staged. Generalized
candidate initialization uses the causing event's after-value, rather than a
possibly newer child-table total, while reading the unchanged sibling messages.
The implementation uses no recursion tied to tree depth.

## Ownership, transaction and identity

`WeightedRuntime` freezes the checked shape into one native query account and
uses existing reference/indexed storage and separator indices. Constructors
create that account from `Options::memory_limit_bytes`.
`create_into(account, shape, options)` instead uses the supplied account for both
frozen metadata and mutable execution. It accepts a physical plan or compiled
program. The receiver's actual limit overrides the options field and is reported
by `options()`; an empty receiver rejects without creating an account. Existing
receiver allocations consume the same cap. A separate compiler account is
unchanged; deliberately sharing one compiler/execution account necessarily makes
execution allocations visible there. No runtime operation refills the limit.
The compiled
source remains available through `structural_program()`. It is a structural
basis; the weighted `Binding` has a separate domain/version/hash and binds the
shape, exact multiplicity policy and configured counter maximum. It cannot be
used as a set-plan execution/cache identity.

`begin_epoch` creates private undo state and one retained indexed work grant.
`stage` accepts one or more ordered native replacements. Each successful stage
has fully maintained messages, but the public committed sequence stays unchanged
until `commit`. Failure of any stage aborts the whole logical epoch. Explicit
rollback, destruction and replacement of a pending token also abort it.

Storage journals retain the affected native table changes. Metadata undo stores
old scalar values and the one changed child slot. Erased records retain their
extracted map nodes, including their original child arrays. Rollback restores
these values/node handles, then native table journals, without allocating. Arithmetic,
allocation, work-limit or expected-value errors preserve the previous epoch.
Commit publishes the prepared sequence and releases undo; it performs no new
arithmetic or allocation. This local atomic epoch is not W06 aggregate batch
consolidation, input routing or recovery.

Live records, queues, table journals, undo, keys and requested captures use that
original account. A live record allocates its child array once. A numeric change
updates the live scalars and one cached child slot; it does not allocate a full
record image or copy the child array. Undo and queue vectors grow amortized.
Products still inspect all child factors of each affected supported row.

`Options::capture_changes` requests owning before/after diagnostic record copies;
it defaults to false. `capture_events` also enables change capture, so event
references remain inspectable. These options add allocations, tuple pins and
child-array copies proportional to the captured changes. Without either option,
`Epoch::journal` is null. Erased keys remain readable through diagnostic arena
pins when requested. The journal phase distinguishes pending, committed and
aborted diagnostics. Committed captures survive later input and facade
destruction; they are not import or proof authority.

Committed native events expose actual logical before/after totals, including
contribution replacements after normalization. An aborted journal is a partial
attempted trace: its failing input can retain requested replacement weights or
contribution shares if failure preceded normalization. `applied_ordinal` marks
entry into execution, not successful completion. Neither an aborted event nor
its ordinal is authority to replay a committed transition.

The facade and pending token have one exclusive caller. A token retains its
actual owner across facade moves/destruction. Ordinary state reads reject while
an epoch is private; pending preview/snapshot are explicit tentative reads.
Owning snapshots retain independent tuple values and immutable record images.
Their row limit and the original query heap bound capture. A private capture
uses the epoch's same indexed grant; it does not refill the allowance.

## Arithmetic and work accounting

W01's checked uint64 policy handles products and contribution replacement.
All stored local, subtree and separator values must fit the configured positive
maximum. A missing child makes a product zero before any multiplication, so an
unrelated large factor cannot spuriously overflow a known-zero product. There
is no division-based deletion, signed wraparound, rounding or approximation.

`weighted::Metrics` counts actual native inputs/changes, affected row visits,
separator probes, copied child slots, products, separator replacements,
membership/value changes, candidates, metadata/table changes, journal entries
and enqueued/applied events. Work admission charges executed operations; it
does not substitute tree height for weighted maintenance. `queue_peak` is the
observed pending queue size. Failed stages retain an aborted attempt's spent
work without retaining a history of old attempts.

The separate `native_grant_consumed` reports the original indexed allowance,
including pre-debited rollback reservations and requested private captures.
It is not a CPU instruction count. Ordered-map comparisons, variable-width
scalar work and lifetime-ledger scans when detaching/restoring map nodes have
additional cost. Ordinary numeric changes do not run those lifetime scans.
Memory statistics include current/peak requests and retained caller-owned
journals/captures. No constant-time numeric update, complete CPU-cost estimate,
or weighted cursor delay follows from these counters.

## Verification

The C++ reference explicitly joins complete descendant assignments before
projecting and summing; it does not use incremental caches or contribution
replacement. Tests compare every row/cache/message after each logical update.
A separate Python oracle uses unbounded integers and checks 1,516 update states
per configuration. Both backends cover native hidden sums, nested generalized
scopes, positive-to-positive changes, candidate birth/reclamation, three typed
disconnected components, empty keys, Boolean/nullary roots and a depth 256 chain.

Resource controls include overflow/stale-input/multi-stage rollback, exact and
one-under executed work and requested-byte heap, one native grant across 64 stages
plus private capture, and 894 actual allocation cuts per configuration. Creation
and deletion run with captures both off and on. Commit/rollback are checked to
allocate nothing; retention/churn and owning snapshots are checked separately.

Final selected gates pass: eight GCC Debug checks, six GCC Release, six Clang
Release and six ASan/UBSan/leak checks. Set annotation admission, selection
diagnostics and scoped support regressions remain passing. A strict external
Clang consumer uses a moved installed SDK, imports a compiler artifact into a
new query account, preserves exact counts/moves/snapshots and rejects weighted
SQL through both constructors. All308 predecessor test commands/properties and
installation declarations are preserved;311 tests are registered. The full311
test suite, a performance speedup and an R1 release are not claimed.

The later [W05 foundation gate](verification/w05-foundations-human-inspection-2026-11-12.md)
adds receiving-account and contribution-port controls to the existing fixtures.
All 23 selected tests pass in strict Debug and ASan/UBSan/leak profiles. Matching
absolute/contribution fixtures have equal allocation-request counts, exact and
one-under limits preserve prior state, and committed captures expose actual
totals. This does not extend the dated W02 acceptance to complete SQL bag/NULL
admission, an installed W05 consumer or a measured runtime speedup.
