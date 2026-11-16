# Prepared logical aggregate net batches

This primitive extends [W04 aggregation](aggregates.md) with one prepared
multi-group command. Its input authority is the standalone runtime's actual
logical-row ledger. It does not admit physical source rows or install a SQL
source/native/session/recovery coordinator. The separate
[original-SQL runtime](sql_aggregate_runtime.md) and
[Session](sql_aggregate_session.md) provide that W06 composition within the
[bounded V33 acceptance](verification/human-inspection-v33-2026-11-13.md).

## Calling and ownership

Compile a genuine AggregateProgram and construct AggregateRuntime with the
desired capture_changes option. Pass prepare_batch one next contiguous sequence
and a borrowed span of aggregate::RowDelta values. Each delta has a complete
nullable logical row, nonzero unsigned magnitude, and erase sign. Equal complete
row keys must already be consolidated; duplicates and zero magnitudes reject.
This is a net command, separate from an ordered transport stream.

```cpp
namespace ag = crown::runtime::aggregate;
const std::array deltas{ag::RowDelta{old_row, old_weight, true},
                        ag::RowDelta{new_row, new_weight, false}};
auto prepared = runtime.prepare_batch({next_sequence, deltas});
// preview() borrows the active token; copy Tuple/program handles if needed.
auto epoch = prepared.commit();
```

The old row weight comes from the real committed ledger. A retraction cannot
exceed it; an addition checks unsigned overflow and the final row count bound.
No signed narrowing computes a uint64 weight difference. Input cells/text need
survive only through preparation. Existing keys share immutable Tuple handles;
new keys copy their actual fields/text into the receiving account.

An active token retains its owner after facade movement/destruction and excludes
updates, snapshots and invariant diagnostics. Program, committed sequence and
account statistics remain inspectable; memory statistics include private
reservations. A moved/closed token rejects operations except idempotent rollback.
Explicit close destroys its backing Data immediately. Its empty allocator
deleter can still retain a fixed account-controller handle. Serialize owner calls.

Empty batches on a mutable named input advance the epoch with changed=false.
W04 no-FROM programs retain their immutable implicit singleton and reject batch
input, including an empty batch. The original-SQL factory authenticates its
static-source bootstrap against the actual child root before loading it once.

## Preparation and publication

One existing Budget covers the command. Private maps retain only changed row
proposals and one State vector per touched group. Untouched rows/groups are not
copied or scanned. Existing groups copy their sufficient statistics once; new
groups initialize them once. The vector uses the persistent destination's exact
account/purpose allocator so publication can legally swap its buffer.

All retractions precede additions. Each removal prefix is a subbag of the old
group, and each addition prefix is a subbag of the final group. A valid final
group therefore avoids an artificial add-first count overflow. Non-NULL counts
and exact IntegerSum numerators change together. With count at most INT64_MAX,
the numerator magnitude stays below 2^126 and an elementary same-sign temporary
stays below 2^127; the existing two-word representation suffices.

Single-row updates preserve immediate SUM(integer) range checks through the
default compile-time policy. Batch preparation validates each final touched
group once, even when capture is disabled. The exact wide accumulator permits
unpublished intermediate signed sums outside the declared bigint result range.
Int64 SUM coefficients need at most 38 decimal digits. AVG retains W04's exact
sum/count and declared rounding/scale; no floating-point arithmetic is added.

If capture is enabled, committed-before and final-after output are rendered
once per touched group. Equal outputs, including rounded-equal AVG, disappear
from the result. Changes retain the full group key, even when projected value
rows coincide. Absent grouped state differs from present NULL values; a global
empty group remains present. changed describes logical input change, independently
of visible output equality.

All row/group insertion nodes and returned output are funded before the token
becomes active. Commit inserts prepared nodes, erases saved iterators, assigns
scalars, swaps equal-allocator State vectors and publishes one sequence. It
allocates no new storage or arithmetic/output preparation. Unhinted ordered-map
insertion still performs logarithmic typed-key comparisons. Proposal/old-vector
and last-owner teardown also perform real work.

Type, duplicate, underflow, final count/SUM, allocation, account or work failure
destroys only private proposals. The old ledger/groups/sequence stay committed.
The busy flag is latched after successful construction, with no subsequent
throwing step. No new catch, inverse log, retry framework or full-state clone is
needed. Rollback simply discards proposals.

## Costs, inspection and current limits

For D changed rows and G touched groups, work includes actual validation/key
bytes, ordered-map probes, D measure updates, G State preparation/final scans,
and requested output copies. One retained budget accounts selected logical
operations; it is not a CPU bound on every comparison or destructor. Resident
temporary memory follows touched keys, G measure vectors, detached nodes and
requested output. Batch-only counters live in BatchMetrics, preserving the
legacy Metrics/Epoch value layouts.

The receiving ordered Release probe compares the actual v19 installed library
with the new code. Metrics/Epoch remain 72/160 bytes; the facade changes 40→16.
Shared ownership/busy state adds a fixed 56 accounted payload/requested bytes.
Construction and five ordinary single-row cases preserve allocation/free/current
allocation counts, selected work and explicit output expectations. This is
build-specific storage/work evidence, not CPU timing, global-heap coverage or a
portable ABI guarantee.

Physical columns retain their bigint scalar representation. Aggregate argument
casts such as x::integer now carry a deduplicated immutable range guard; the
shared projection checks it before group mutation. This preserves the bigint
SUM(integer) result rule without changing raw grouping or SUM(bigint). Varying
positive/negative contributions use the existing wide numerator and the batch's
final-only check. AVG(integer) keeps its separate wide-numerator rule. The
[composition guide](sql_aggregate_runtime.md) describes the genuine physical
source/native path and its rollback; passing this standalone test alone does
not establish that path or complete W06 acceptance.

Inspect [public interfaces](code_specs/files/include/crown/runtime/aggregate.hpp.md)
and [the preparation/publication blocks](code_specs/files/src/runtime/aggregate.cpp.md).
These transaction rules are local engineering for Refactor W06, not a new CROWN
paper theorem. The original-SQL runtime consumes genuine native contributions
through its private group-only path and keeps no second complete joined-result
ledger. This standalone API retains its own logical-row ledger.
