# Using the draft C02 ranker

**Preparation only:** C02 remains `not_started`. The public declarations below
are the current proposal headers, not accepted runtime behavior. They are
included for usage review and compile-only API compatibility.

Each function accepts an existing factory-produced P07 `CandidateSnapshot`.
Its `original_proof()` is the required-height authority; the C02 result keeps
that proof and selects one retained `MinimumHeightCandidate` at that same
height. A selected candidate is an alternative checked tree, not a replacement
proof witness. P07's `CandidateContext` remains unchanged: C02 policies do not
become `cost_model` or optimization values.

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

The revised draft accounts active time cumulatively: `Usage.active_nanoseconds`
includes preparation carried into ranking, and `CaptureAccounting` records the
processing and source-state limits actually applied. `rank_current` supplies
the same request limits to capture and scoring, so its `Limits.active_time` is
one soft ceiling across both phases, not a fresh allowance per phase. With
separate `capture` and `rank` calls, choose matching limits deliberately; the
captured preparation usage is still carried into ranking. A `time_limit` is a
resource stop and does not invoke the height fallback.

## Current source-cardinality tuple/index-slot proxy

The capture adapter can read exact current physical source cardinalities with
`CaptureOptions::source_cardinalities` enabled (the proposal default), then
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
instead captures and ranks synchronously, but its result makes no promise of
future freshness.

The tuple/index-slot score is a candidate-local upper-bound proxy measured in
abstract tuple slots and index-key slots. For each candidate the proposal
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

`capture(snapshot, owner, options)` is the proposal's factory path. Retain its
returned `RuntimeEvidence` by value; there is no fresh evidence import
constructor. `Evidence::sources()` and `source_observations()` report explicit
per-table state, while `capture_accounting()` and `preparation_usage()` expose
capture and processing limits, source-selection bounds, and measured
preparation usage. Missing, incomplete, pending, released, stale,
foreign, saturated, or budget-exhausted facts remain reasons, not zeroes.

The proposal scores only the candidate snapshot supplied by the caller. It
does not prove completeness of an unfinished provider family. It makes no
C03 calibration, arrival-Hz, latency, allocator-byte, total/peak-memory,
deployment, or runtime-optimality claim. See the
[proposed C02 contract](../c02-ranking-preflight-proposal/CONTRACT.md) for the
full binding, scoring domains, freshness distinctions, and limits.
