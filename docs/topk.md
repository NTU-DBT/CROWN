# Exact snapshot top-k

`CROWN::topk` provides `crown::runtime::snapshot_topk` over a genuine
`SqlRowsRuntime` or `SqlAggregateRuntime`. It collects the current exact snapshot,
sorts compressed tuples/groups, and selects at most `k` logical rows. This is the
ordinary recomputation route permitted by [Refactor X05](../Refactor.md).
P10's specialized algorithm and delay bounds are not selected. SQL `ORDER BY`,
`LIMIT`, `OFFSET` and `WITH TIES` retain their existing parser/admission status;
this library operator is explicitly invoked by its caller.

```cpp
#include <crown/runtime/topk.hpp>
#include <array>

using namespace crown::runtime;
const std::array order{topk::Key{1, topk::Direction::descending,
                                  topk::NullOrder::last}};
auto result = snapshot_topk(owner, order, 10); // owner is a genuine SQL runtime
for (const auto& entry : result.entries) {
  // values and identity are immutable owning Tuple handles.
  // multiplicity counts selected copies; exporting values is separate caller work.
  auto values = entry.values.export_values();
  (void)values;
}
```

## Ranking, ties and identity

Each key names a zero-based output field, direction and explicit NULL placement.
NULLS FIRST/LAST is independent of ASC/DESC. Present values use the existing exact
integer, decimal, date, Boolean and binary TEXT order. SQL TEXT keeps its existing
valid-UTF8, U+0000-free source domain; ranking does not broaden admission.
Decimal order is numeric, not formatted-text order. Aggregate keys compare the already rendered declared
SQL outputs: AVG rounding/scale happens before ranking.

After all requested fields compare equal, identity sorts ascending with NULLS
FIRST. An empty key list selects identity order; repeated keys are permitted.

| Source | Identity | Multiplicity |
| --- | --- | --- |
| Plain SQL bag | Complete nullable output tuple | Exact selected copy count |
| DISTINCT or EXISTS | Complete nullable output tuple | One |
| Aggregate | Complete group key, including omitted output keys | One per group |

Two groups with identical displayed values remain distinct. An empty global
aggregate still has its genuine COUNT=0/SUM=NULL/AVG=NULL row. EXISTS still emits
its Boolean row when the inner query is empty. Root bag weight is not a shortcut
for deciding whether either output exists.

Identities are scoped to the genuine program/query context. Bag copies are
indistinguishable; an entry with multiplicity `m` denotes selected copy ordinals
`[0,m)` for that tuple at this snapshot. It does not expose physical source-row
or witness identity. Group identity remains its complete key when displayed
aggregate values change. The returned program handle and sequence retain that
context after the runtime closes.

`k` counts logical copies. A cutoff inside one bag tuple uses
`min(remaining, multiplicity)`. No expanded bag or sum of all bag multiplicities
is constructed, including at `UINT64_MAX`. Selection is exactly the first
`min(k, snapshot cardinality)` rows under the complete order; it does not include
additional tied rows beyond `k`.

## Admission, ownership and failure

Calls must be serialized with the owner. Both overloads require `ready()`,
including at `k=0`. Rank-field bounds and enum values are checked before producer
creation. Metadata validation consumes one top-k work unit per key; insufficient
work can refuse admission before a later field is examined.

For `k=0`, no cursor or aggregate snapshot is opened and no candidate/result
storage is allocated. An empty order therefore permits all three grants to be
zero. Nonempty order still requires its validation work. The result's candidate
count records actual collection, not an inferred whole-snapshot cardinality.

Candidate vectors, copied SQL tuples, selected handles and retained result arrays
use the original runtime's receiving account. No per-call account or increased
cap is created. Existing ordinary diagnostic/exception-runtime storage remains
separate. Immutable payload sharing preserves output/schema ownership; result
vector copies can allocate from that same original account.

All collection and sorting are private. Failure releases the cursor lease and
incomplete vectors without changing committed source rows, aggregate state or
sequence. Existing cursor observations and cumulative/peak allocation counters
can record attempted work. No new catch/retry, undo log or query-update hook is
introduced. Public result fields are presentation data, not replay or native
admission authority.

## Work, memory and performance

`Limits` has three finite grants:

- `candidates`: retained compressed tuples/groups before sorting. The row cursor
  can decode one additional owned tuple to discover excess; its original account
  and producer-work grant cover that temporary. Aggregate snapshot admission can
  reject excess groups before rendering.
- `producer_work`: one existing native cursor allowance for the entire row scan,
  or one existing aggregate snapshot/render allowance. It is never reset per row.
- `work`: one shared top-k balance across key validation, positive-k entry,
  candidate collection, all sort comparisons/fields/string-byte charges and
  selection. Copies of the sort comparator borrow the same balance.

`Metrics.work` records selected top-k logical units, not producer work, elapsed
CPU, allocator work or every pointer move. Each comparison admits one unit, each
inspected nullable field admits one unit, and present string comparisons admit
both complete byte extents before comparison. `candidates`, `comparisons`,
`fields` and `scalar_bytes` describe those actual phases. Entry selection admits
one unit per selected identity before result allocation/copy.

For `N` compressed rows/groups, full snapshot collection and full sorting have
linear retained candidate space and ordinary comparison-sort cost, with actual
field/string extents included. Aggregate collection also eagerly renders its
existing full group snapshot. This is not constant-delay CROWN enumeration work.
Peak memory includes those existing producer/image costs, candidates and final
output. After selection, a separate compact vector retains only the `M` selected
identities; shared Tuple handles avoid another deep copy of strings. Huge bag
weights do not increase `N` through expansion. No throughput improvement or
specialized incremental top-k bound is claimed.

Invalid rank specifications use `topk_order`; top-k work and candidate denial
use `topk_work_limit` / `topk_result_limit`. Busy owners use `topk_busy`.
The existing producer's aggregate/cursor/resource errors propagate unchanged;
aggregate candidate denial can therefore be `aggregate_result_limit`.

The implementation is in [topk.cpp](../src/runtime/topk.cpp), with the public
[interface](../include/crown/runtime/topk.hpp). The source-bound block maps and
review evidence distinguish implementation, independent expectations and actual
execution. Optional invocation adds no state or work to ordinary query updates.
