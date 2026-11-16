# Transaction-local projected bag deltas

This is one W06 primitive for admitted logical conjunctive queries. It returns
exact changes to the projected weighted bag across one native PendingEpoch.
Physical SQL source batches, final SQL constraints, grouped aggregate publication
and durable recovery still require their own coordinator. The
[task ledger](task_ledger.md) keeps W06 in progress.

## Calling contract

Use the opt-in overload of WeightedRuntime::begin_epoch with
weighted::DeltaCapture::enabled. Stage the admitted native replacements or
contributions synchronously, inspect bag_delta_preview if needed, and commit.
The existing one-argument overload disables capture. Node IDs still identify
compiled logical occurrences; returned facts do not supply source or proof
admission authority.

A BagDelta contains the complete compiled output AccountedTuple and a sign plus
uint64 magnitude. Its magnitude is always positive. Repeated output fields keep
head order; hidden witnesses are already summed by the local factorization.
Empty output uses the actual empty tuple. Both +UINT64_MAX and -UINT64_MAX are
representable without narrowing to int64.

A pending preview returns nullopt when capture is disabled. An engaged empty
span means the current exact net is zero. The span borrows the pending token and
expires at the next stage, commit, rollback or destruction. The owning
Epoch::bag_deltas field stays empty while the token is pending.

Commit returns an engaged immutable BagDeltas handle when capture is enabled,
including for an empty net. Copying Epoch shares that owner. Entries and metrics
borrow the handle and remain usable after the runtime is updated, moved or
destroyed. Entry order is unspecified. Accessing an empty/default/moved handle
rejects with delta_capture_disabled. A canceled sequence of native edits can
set Epoch::changed while returning an empty net. Full-root before/after totals
remain separate from these projected bag changes.

## What each maintenance block does

The [weighted factor specification](weighted_enumeration.md#factor-specification)
and [factorization argument](weighted_enumeration.md#why-this-factorization-is-correct)
define one local factor E for each selected visible key. A complete compatible
visible assignment contributes the product of those factors. Immediately before
one visible factor changes, the collector computes

    (new E - old E) * product(all other current E factors).

The sign/magnitude pair represents the difference. Other factors are read at
that exact replacement boundary. Summing these coordinate changes telescopes
from the original output bag to the final one. Replaying diagnostic FactorChange
records against final state would lose the intervening cross terms.

DeltaWalk fixes the changed key directly, including before its first insertion.
Other steps use the checked program's current live lists and separator buckets,
consulting pending table journals when present. It shares the existing iterative
backtracking kernel with the committed cursor, using concrete select/close
methods. It opens no public reader or replacement native allowance.

The anchor lookup stops at its unique checked enumeration step. The walker
waits for a complete compatible assignment before multiplying. A
later empty/mismatched bucket must establish zero before an unrelated prefix
can overflow. At limit 100, R(a)=40,S(a)=1,R(b)=1 and S(b):0→50 have root 40→90
and delta(b)=+50. Multiplying 50 by the incompatible R(a)=40 first would wrongly
reject this transition.

BagDeltas::Data probes the borrowed projected output before freezing any payload.
For an existing key it adds equal signs or subtracts opposite magnitudes.
Cancellation removes the lookup key before destroying its payload, moves the
last fact into the vacant slot and repairs that moved key's index. Lookup keys
borrow stable owned payload blocks, rather than vector element addresses.
Only insertion of a new net key freezes descriptors/string bytes and allocates
a lookup node. Geometric vector growth moves owning handles without copying
payloads. Commit drops all lookup nodes and publishes only immutable facts and
metrics; no sorting, seal allocation or complete result copy is needed.

## Arithmetic, failure and ownership

Each native stage drains before the next begins. For one nonnegative native
weight replacement, descendant messages, support indicators and local factors
move monotonically between stage endpoints. Complete telescope terms are bounded
by the larger endpoint output count. Same-sign consolidation uses the admitted
MultiplicityPolicy; opposite signs use unsigned subtraction. A later physical
net-batch coordinator must apply normalized decreases before increases and
validate final source constraints; this port does not normalize physical rows.

All controls, scratch, keys and output payloads use the runtime's original
receiving account. Existing-key consolidation creates no new owning output tuple.
The pending walker closes all borrowed table cursors before mutation or rollback.
Committed output retains its account, rather than the mutable runtime or grant.

Capture setup can fail before an exclusive token is published. After a token is
active, arithmetic, allocation and work failures reach the existing sole stage
abort boundary, which closes private capture and reverses all earlier stages.
No per-row catch or second rollback framework is added. Commit and rollback use
prepared storage; the exact covered-new denial tests are described in the
[verification record](verification/w06-weighted-deltas-2026-11-12.md).

## Actual cost and limits

Capture is opt-in. Disabled capture creates no collector control, frame vector,
row buffer, lookup node or output payload. In the current GCC/Linux before/after
probe, ten ordered/indexed cases retain identical logical work, native grants
and successful/freed/current allocation counts. Pending Data gains 72 payload
bytes and the returned Epoch value gains 16 bytes; the pending facade stays 40
bytes. These are measured object/account facts, not portable ABI sizes or a
latency/global-heap claim.

Enabled capture funds one shared fact owner, one walker, visible-step frames and
output descriptors. It retains one owning payload per current net key and a
borrowed-key ordered index. Lookup costs logarithmic comparisons in current net
keys; comparison fields and actual string-prefix bytes are charged. Only new
keys pay output-copy bytes. Cancellation releases its payload/index immediately;
vector capacity can retain the peak key count until the output handle dies.
Final publication clears the index in linear node-release work, prefunded at
insertion. Frame/output/key preparation and standard allocator bookkeeping are
real work.

The actual 32-step root-anchor probe saves 31 logical work units with the early
exit, preserving allocation facts, outputs and native grants; it measures no
latency.

The collector adds its selected work to the existing cumulative epoch work
limit; native live/bucket operations also spend the original retained indexed
grant. No per-factor or per-stage grant is refilled. BagDeltaMetrics is the
capture subset of those logical admissions, not elapsed CPU, RSS or all allocator
operations.

Traversal starts from the compiled root and fixes the anchor when reached. It
can visit unrelated earlier prefixes and allocate temporary separator keys.
Its cost follows actual visited prefixes and complete compatible assignments,
not just final delta cardinality. This implementation does not establish an
output-only delay bound or a new weighted CROWN theorem. Anchored physical-index
and end-to-end workload costs remain part of the unfinished W06 integration and
performance review.

## Source and paper trace

Inspect [weighted maintenance](code_specs/files/src/runtime/weighted.cpp.md),
[delta state](code_specs/files/src/runtime/weighted_delta_detail.hpp.md),
[shared traversal](code_specs/files/src/runtime/weighted_detail.hpp.md) and
[public carriers](code_specs/files/include/crown/runtime/weighted.hpp.md).
Each scoped card records usage, invariants, ownership, failure and costs.
The [paper guide](code_review.md) pins P1 arXiv:2301.04003v2; its aggregation
context and W03's local factor proof motivate the representation. This
coordinate-telescope, lifetime, budget and transaction protocol is local
engineering. It supplies no paper authority for SQL batch admission or recovery.
