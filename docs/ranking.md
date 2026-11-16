# Baseline ranking of minimum-height candidates

The original C02 registration and its 143-test compiler matrix are recorded
in the historical [verified record](verification/ranking-2026-11-07.md).
Current ownership and constant-route verification are tracked in
[the handoff](handoff.md); predecessor compiler results apply to their frozen
inputs. `Evidence::plan()` is the core `CompiledProgram` handle, sharing the
captured owner's metadata and query account. This is a library API with no
ranking CLI or deployment action.
The complete example functions are checked in at `tests/examples/ranking_usage.cpp`
and compiled with both production and testing runtime definitions.

Each function accepts an existing factory-produced P07 `CandidateSnapshot`.
Its `original_proof()` is the required-height authority; the C02 result keeps
that proof and selects one retained `MinimumHeightCandidate` at that same
height. A selected candidate is an alternative checked tree, not a replacement
proof witness. P07's `CandidateContext` remains unchanged: C02 policies do not
become `cost_model` or optimization values.

Use `crown_ranking` for pure ranking and explicitly link `crown_ranking_runtime`
for actual-owner operations. The testing bridge is
`crown_ranking_runtime_testing`; never combine it with the production runtime
or bridge. The pure library and both bridges have no report dependency.

## Height-only

This is a pure ranking call. It needs no runtime or C01 capture:

```cpp
#include "crown/planner/candidates.hpp"
#include "crown/planner/ranking.hpp"

namespace c02_guide {
namespace pr = crown::planner::ranking;

[[nodiscard]] pr::Attempt height_only(
    const crown::planner::CandidateSnapshot& candidates) noexcept {
  pr::Request request{};
  request.policy = pr::Policy::height_only;
  request.fallback = pr::Fallback::require_evidence;
  return pr::rank(candidates, request);
}
}  // namespace c02_guide
```

It orders equal-height retained candidates by the complete stable structural
key. The ranker evaluates every member already present in the snapshot or
publishes no result if a resource limit stops evaluation. It does not resume a
provider or search for more candidates. Check
`attempt.result->snapshot().family_exhausted()` to distinguish an exhausted
candidate family from a complete ranking of only the retained prefix. In the
latter case the winner is only best among that prefix.

Before scoring, the ranker checks every retained typed candidate against the
snapshot's original verified optimum, required certified height and complete
Catalog/Query binding. Statistics cannot supply a proof or authorize an imported
tree. An invalid handle, incompatible binding, empty snapshot or resource stop
returns no selection. The result retains the original snapshot and proof;
it does not update a provider, cache, incumbent proof or live plan.

## Current committed-input/native-depth policy

`rank_current` captures from the supplied physical owner and ranks within that
synchronous call. The fallback below is an explicit caller choice: when
statistical evidence is unavailable, the returned result may use height-only
for the **same whole retained snapshot** and records the fallback reasons.
With `require_evidence`, the same unavailable case returns no selection and an
`evidence_unavailable` stop. Resource stops such as work, lowering, bit, or
allocation limits do not trigger statistical fallback.

```cpp
#include "crown/planner/candidates.hpp"
#include "crown/planner/ranking.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/ranking_evidence.hpp"

namespace c02_guide {
namespace pr = crown::planner::ranking;
namespace rr = crown::runtime::ranking;

[[nodiscard]] pr::Attempt current_native_depth(
    const crown::planner::CandidateSnapshot& candidates,
    const crown::runtime::PhysicalRuntime& owner) noexcept {
  pr::Request request{};
  request.policy = pr::Policy::committed_input_native_depth;
  request.fallback = pr::Fallback::height_only;
  auto attempt = rr::rank_current(candidates, owner, request);

  if (!attempt.result && attempt.stop == pr::Stop::evidence_unavailable) {
    return attempt;  // No selection; preserve stop and reason bits.
  }
  if (attempt.result &&
      attempt.result->effective_policy() == pr::Policy::height_only) {
    const auto fallback_reasons = attempt.result->fallback_reasons();
    (void)fallback_reasons;  // Surface these alongside the selection.
  }
  return attempt;
}
}  // namespace c02_guide
```

The depth score weights **committed physical table insert/erase inputs** in the
current C01 interval, including duplicate inserts and absent erases. An abort
does not count. Each committed event contributes once to the common physical
denominator; each routed occurrence contributes its own candidate-specific
native depth to the numerator. A native root has depth one and generalized
nodes add zero. The denominator covers every physical table/operation root,
including unused catalog tables; an unused table adds denominator weight and
no numerator contribution. This is a deterministic workload proxy: it does not
model filters, derivations, bucket visits, result demand, or time. Sampled
detail is not expanded into a population estimate; required physical roots
must be exact and healthy, with a positive denominator. A zero-event or unavailable
interval is unknown for this policy, not uniform traffic.

`rank_current` reads the owner's current configuration. It does not enable,
reconfigure, reset, or rotate C01 collection. If input counters are off, a
configured height fallback is explicit; callers who want only statistical
ranking should use `require_evidence` and handle no-selection results. Capture
limits passed to the convenience overload bound reads; they are not collector
configuration.

The API accounts active time cumulatively: `Usage.active_nanoseconds`
includes preparation carried into ranking, and `CaptureAccounting` records the
processing and source-state limits actually applied. `rank_current` supplies
the same request limits to capture and scoring, so its `Limits.active_time` is
one soft ceiling across both phases, not a fresh allowance per phase. With
separate `capture` and `rank` calls, choose matching limits deliberately; the
captured preparation usage is still carried into ranking. A `time_limit` is a
resource stop and does not invoke the height fallback.

## Current source-cardinality tuple/index-slot proxy

The capture adapter can read exact current physical source cardinalities with
`CaptureOptions::source_cardinalities` enabled (the default), then
return an owning `RuntimeEvidence`. To reuse it, validate the retained evidence
against the **actual same owner** immediately before ranking. The check below
tests both the owner boundary and the requested policy's facts; it deliberately
uses `usable(tuple_index_slots)`, not `all_facts_usable()`. Thus an unavailable
workload-depth fact need not reject a source-cardinality policy. The caller
must keep the existing exclusive-owner/single-writer boundary across
revalidation and ranking.

```cpp
#include <optional>

#include "crown/planner/candidates.hpp"
#include "crown/planner/ranking.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/ranking_evidence.hpp"

namespace c02_guide {
namespace pr = crown::planner::ranking;
namespace rr = crown::runtime::ranking;

[[nodiscard]] std::optional<pr::Attempt> current_tuple_index_slots(
    const crown::planner::CandidateSnapshot& candidates,
    const crown::runtime::PhysicalRuntime& owner,
    const rr::RuntimeEvidence& retained,
    rr::Revalidation& current_check) noexcept {
  constexpr auto policy = pr::Policy::tuple_index_slots;
  current_check = rr::revalidate(retained, owner);
  if (current_check.boundary != 0 || !current_check.usable(policy)) {
    return std::nullopt;  // Caller can inspect boundary and memory reasons.
  }

  pr::Request request{};
  request.policy = policy;
  request.fallback = pr::Fallback::require_evidence;
  const std::optional<pr::Evidence> as_of{retained.inputs()};
  return std::optional<pr::Attempt>{pr::rank(candidates, request, as_of)};
}
}  // namespace c02_guide
```

`RuntimeEvidence` owns an immutable **as-of** capture; it holds no live owner
pointer, cursor, or lease. Pure `rank` can reproduce that recorded score, but
cannot claim that it is current. `revalidate` compares retained evidence with
the actual owner. Check `boundary` separately from policy usability. After a
commit, reset, mode/interval change, release, or foreign-owner switch, repeat
the check; do not infer freshness from equal row values or an old sequence.
Owner freshness comes from the actual owner/layer/committed-sequence stamp;
storage revision is separate invalidation evidence. Workload facts additionally
depend on the current interval, configuration, options, and modes. `rank_current`
captures and ranks synchronously for evidence-dependent policies, but its
height-only branch obtains the actual account/plan without a currentness capture.
Use C05 `select_current` when every policy must pass an actual-owner boundary.
Returned captures make no promise of future freshness.

The tuple/index-slot score is a candidate-local upper-bound proxy measured in
abstract tuple slots and index-key slots. For each candidate the ranker
projects source row counts through its own lowered layouts: `R` records, `S`
survivors, `P` parent support, and `E` visible rows. It adds one tuple slot
plus one scalar slot per field for selected relation layouts;
each unique index requirement adds one membership slot plus its key-width
slots per bounded row. Repeated index uses are counted once. These are newly
derived bounds, not counts copied from the running plan.

The score is **not bytes**. It excludes source storage, derivation maps, support
metadata, object/container overhead and capacity, journals, output buffers,
readers, statistics, temporary capture/lowering storage, and peak coexistence.
It can misorder actual allocations. It is not an S05 memory bound and must not
be combined with the depth score or compared with a byte budget. This policy
can use current source cardinalities when C01 workload counters are off, as
long as the requested source facts and actual-owner revalidation are usable.

## Evidence and scope

`capture(snapshot, owner, options)` is the factory path. Retain its
returned `RuntimeEvidence` by value; there is no fresh evidence import
constructor. `Evidence::sources()` and `source_observations()` report explicit
per-table state, while `capture_accounting()` and `preparation_usage()` expose
capture and processing limits, source-selection bounds, and measured
preparation usage. Missing, incomplete, pending, released, stale,
foreign, saturated, or budget-exhausted facts remain reasons, not zeroes.

The ranker scores only the candidate snapshot supplied by the caller. It
does not prove completeness of an unfinished provider family. It makes no
C03 calibration, arrival-Hz, latency, allocator-byte, total/peak-memory,
deployment, or runtime-optimality claim. Current statistics are documented in
`docs/statistics.md`; candidate/proof authority remains the P07 contract.

## Exact score reconstruction

Interpret score fields by `Result::effective_policy()`. Height-only uses height
and structural key; depth uses numerator/denominator; slots uses `slots` and its
population/term records. Uncomputed fields retain implementation placeholders
(`0/1/0`), including after height fallback. They are not observed zero costs.

Depth ranking publishes the unreduced integers `numerator` and `denominator`.
For physical table t, let w(t) be current committed inserts plus erases, and
d(t) be the sum of the candidate's native depths over every occurrence routed
to t. Then N = sum(w(t) * d(t)), W = sum(w(t)), and the score is N/W.
All candidates use the same positive exact W, so comparing N is sufficient.
`depths` and `table_depths` retain every occurrence, table, input weight, depth
sum and contribution. Aliases share one physical weight and contribute separate
depths. No-op inputs remain inputs; diagnostic attempts and aborts do not count.
Previous C01 segments are not added to the current interval.

A nonempty contradictory body keeps its original minimum-height proof, while
its physical operator has no native occurrences. With eligible committed-input
evidence, every physical table retains its actual insert/erase weight and has
depth sum and contribution zero. The score is exact `0/W` with the same positive
denominator W and empty occurrence depths. Missing, disabled or zero-total
census facts retain their unavailable/fallback behavior.

For slot ranking define P(n,k) = n for k > 0 and min(n,1) for k = 0.
A native node's record bound is P(physical source rows, record width).
A generalized node uses P(sum of child parent-support bounds, record width).
The survivor bound equals the record bound; parent-support and visible bounds
project that record bound with their own widths. A node without E has no E term.
For each actual relation selected by the model, add population * (1 + width).
For each unique compiled index requirement, add its relation population *
(1 + key width). `populations`, `slot_terms` and `modeled_plan` retain all the
candidate's geometry and intermediate bounds. An empty source stays exact zero;
nullary projection bounds a nonempty population by one.

For a nonempty contradiction, slot modeling still admits complete source
payload, lowers the canonical empty operator under the remaining limits,
checks all four source identities, admits compiled payload and retains
`modeled_plan`. Only then does it publish `slots=0`, with empty population and
slot-term arrays. It skips unused body/source population scratch. Zero slots
do not mean zero compilation work, zero allocator bytes or waived evidence
eligibility.

These inputs are physical source cardinalities and committed physical input
strata. Plan-local P/E, degree, derivation and index identities from the running
owner are never transplanted into other candidates. Each candidate is lowered
under finite remaining limits to derive its own layout/index terms. Ties in
every policy use the full stable structural key, independent of provider order.

Arithmetic uses a portable fixed 512-bit unsigned domain, exact integer
comparison and canonical unsigned decimal strings. It never wraps, saturates,
rescales or uses floating point for a score. The implementation's conservative
bounds for the admitted 64-bit count/index domains are N < 2^192 and Q < 2^257;
512 bits cover these, while a caller's smaller 1..512 bit cap may reject work.
Numeric score text is reproducible; elapsed time and build-specific payload
accounting are diagnostics and are not score terms. Format/arithmetic version 1
describes this owning C++ result; it is not a serialized import format.

## Budgets and availability

Defaults are 128 retained candidates, 1,000,000 C02 work units and cells,
8 MiB of binding/key bytes, 16 MiB of modeled payload, and 1,000,000 units each
of native lowering, identity, binding replay and normalization work. Caps are
aggregate over capture preparation and the complete retained candidate set.
Soft active time is optional; native calls cannot be preempted. See
`docs/ranking_accounting.md` for what each charged component includes.

The payload cap is a cumulative logical admission model. It includes each
candidate's owned source/program and compiled-plan components, repeated SQL
text, Decimal coefficient allowances and repeated-layout equality storage.
It excludes allocator headers, capacity slack, private fixed fields, shared
caller-owned state and temporary/peak native construction. Exact compiled
structure is admitted after a blocking lower call, before publication.
Native workload snapshot copying follows the owner's collector configuration.
Neither this cap nor the slot score bounds S05 total or peak bytes.

Native C01 source-capture budget exhaustion is recorded as unavailable bounded
evidence, with its actual state/usage/component reasons preserved; an explicitly
enabled whole-snapshot height fallback can handle that condition. Exhausted
C02 processing, bit, payload, candidate, lowering or time caps, and allocation
failure, publish no partial winner and never trigger fallback. A failed lowerer
may report `lowering_limit` when its existing API maps allocation failure to a
resource diagnostic. Check `stop`, `reasons`, `effective_policy` and
`fallback_reasons` before consuming a result.

Sampled or truncated detail alone does not invalidate exact physical census
roots. Relevant root/denominator saturation, protocol degradation, interval
generation saturation and incomplete roots do invalidate depth facts. Memory
facts have separate eligibility: fresh source cardinalities can remain usable
with counters off or after a workload-only reset. Pending private state,
released owners and actual owner/epoch mismatches cannot be promoted to fresh
facts. Saved results remain readable as history after any later owner change.

## Runtime evidence allocation ownership

The runtime `capture` path obtains the existing `CompiledProgram::account()`.
Both comparison bindings, the retained binding, input weights, source
cardinalities/observations and the Evidence object/shared control use that
account under capture:9. RuntimeEvidence's object/shared control uses capture:10.
Census seen/root arrays and the source-table bitmap are temporary allocations
under the same account. Native decimal binding formatting uses fixed storage;
the frozen v2 byte format and logical work/key/payload charges are unchanged.

`weights()`, `sources()` and `source_observations()` expose const references to
`EvidenceVector<T>` (a vector with an original-account `OwnerAllocator`). They
remain ordinary indexed/range interfaces; retained handles share immutable
storage without allocation. Source selections generated by capture use a fixed
256-element array and a synchronous borrowed `OwnerRequestView`. Public owning
`OwnerRequest` capture APIs remain available and delegate to the same builder.
No request view escapes the call. Allocation denial returns
`Stop::allocation_failure` without evidence or a partial winner; accepted owner
state and previous evidence remain intact. Retained evidence survives owner
closure and releases its account allocations with its final handle.

Score/result controls, score arrays, decimal/key text and each reproduction-term
array now use the original query account under capture:11. Even empty/SBO text
retains that allocator. Candidate programs are lowered natively into the receiving
account; immutable source/identity data can share the canonical admitted basis.
No ordinary compiler graph is exported inside runtime ranking. Replacing a
program retains no chain of older physical graphs.

`scores()` returns ScoreVector<CandidateScore> and `modeled_plan` contains a
CompiledProgram. `Result::account()` identifies the allocating account. Native
runtime/session factories accept selected programs; explicit PhysicalPlan/JSON
exports are caller operations. Runtime height-only ranking obtains the original
account before admission, even though it takes no statistical capture. Standalone
compiler ranking without runtime evidence uses an explicit component account.
Supplied immutable candidate/proof handles remain caller boundaries. Logical
payload accounting is separate from actual allocation admission. S05 verifies
the documented native query-account ownership, including these runtime ranking
graphs; compiler/caller workspace and process RSS remain separate. See
[the current handoff](handoff.md) and the prior
[native evidence checks](verification/s05-ranking-evidence-native-2026-11-09.md).
