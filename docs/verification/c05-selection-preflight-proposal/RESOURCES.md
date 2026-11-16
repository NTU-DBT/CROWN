# Aggregate resource and publication contract

## Accounted domains

The C05 request uses the C02 `ranking::Limits` numeric domains and defaults:
1,000,000 processing work/cells; 8 MiB logical key traffic; 16 MiB modeled
payload; 1,000,000 each lowering, identity, binding-replay and normalization
work; at most 128 retained candidates; score_bits in 1..512; optional active
nanoseconds. These are aggregate per-selection ceilings, not a fresh allowance
for each component. A caller may deliberately raise them. Two complete
assessments can require a larger grant than one; they never silently receive
twice the requested limits. Invalid enum/negative time/score_bits zero or above
512 is rejected before owner capture or cache effects.

Every C05 collection append/retained copy and every variable-width key operation
is admitted before allocation. Work charges field/element visits, byte
comparisons, constraint decimal parsing, candidate selection and FIFO lookup.
The exact implementation charge table must be published with the implementation
and tested at exact/one-under boundaries; this design does not claim a measured
operation count before that implementation exists. Counter arithmetic checks
`amount <= cap - used` before addition. No counter wraps or saturates into
success. C02 score arithmetic remains exact bounded 16-limb base-2^32; no
floating point, approximate ordering, rescaling or silently capped score.

The optional slot cap is canonical decimal in the 512-bit domain. Comparing
valid nonnegative decimal strings by digit count and then unsigned bytes is
exact, and needs no product or narrowing. Depth numerators have a common
positive denominator verified in the retained C02 result. C05 therefore orders
N directly and keeps N/W intact for reproduction. Score_bits applies to C02's
actual intermediate/published values; a resource stop never activates fallback.

Payload remains the documented C02 logical component model, extended to C05
owned request/source/key/decision/cache structures. It includes owned string
lengths, vector element storage and public plan/program components, including
Decimal coefficient allowance and repeated-field equality pairs. It is not
allocator live bytes, capacity, peak temporary memory or an S05 bound. The C02
component-model exclusions continue to apply; every additional exclusion must
be named in implementation accounting documentation, not hidden behind the word
bounded. Pre-existing immutable handles can share ownership; new independently
owned backing data and cache admission are conservatively charged. Shared
prepared evidence data is charged once per selection, not once per handle.

Native blocking P08 lowering/identity/replay may allocate temporary JSON/IR
before an exact compiled-descriptor size can be inspected. Source payload is
pre-admitted, public compiled payload is checked before retention/publication,
and native work is finite. This is not a pre-allocation cap on those private
temporaries. All JSON-using project objects must use the already patched,
exceptions-enabled native header; no mixed inline-definition closure is allowed.

For DirectCQ without an existing plan, there is no owned canonical identity DOM
to inspect before the first lower. The new C05 source walker pre-admits the known
Catalog/Query/tree/options copies; the new identity DOM and compiled public
payload are charged after native lower and before retention. Do not call C02's
basis-dependent source walker with a fabricated plan or claim that unknown DOM
size was pre-admitted. When a real basis is present its known source/identity
can be accounted using the existing model. In both paths finite identity work
limits native construction, while peak native temporary allocation is excluded.

## Preparation charged exactly once

Let L be the caller's additive Usage ceilings, P the Evidence preparation Usage
(zero without evidence), A the C05 work already performed, and U the complete
current aggregate. In a pure as-of call, admission starts by checking P fits L
and initializes U=P. C05 work subsequently adds to U. In a current call, U starts
at zero, admission work A is charged, and capture is passed only the remaining
caps. On successful capture its measured preparation P is added once. Raw
capturing work is then never re-added merely because another C02 Result retains
the same Evidence handle.

The existing `rank` automatically initializes its Usage from P. To delegate
assessment i without double-counting P or granting fresh full caps:

1. Check U <= L for every additive dimension and let R=L−U.
2. Pass rank component ceiling D=P+R, retaining the caller's candidate count
   and score_bits. Since U includes P, D<=L and no addition can overflow.
3. Retain the actual delegated Request and returned Usage V in that Assessment.
   Require V>=P in every additive dimension on successful normal return.
4. Charge exactly V−P into U. On failure preserve the returned/reserved component
   usage and stop the whole selection; no constraint/primary prefix is published.

For a depth-plus-slot request, perform this sequence for complete Q then complete
depth, in that order, on the same full CandidateSnapshot and the same Evidence.
All per-candidate Q artifacts remain charged/retained while depth is assessed.
The C05 result exposes both original delegated Requests/Usages plus its total,
so an auditor can reproduce the complete accounting rather than sum two copies
of P. Separate native work dimensions follow the same equation. The finite
source state capture limits are a separate C01 component budget, not silently
converted into C02 work or bytes.

A failed current capture can have only partial measured processing usage and no
Evidence; add its returned usage once to prior C05 work and fail. Do not invent
a zero-cost Evidence or call a subsequent rank with no facts. On unsupported
byte/model/layout requests, rejection occurs before capture, so no capture cost
is claimed. Admission itself is charged under finite limits; invalid-resource
configuration can produce a zero-usage invalid_request rejection.

## Time is optional and soft

The aggregate active-time ceiling includes carried Evidence preparation time
and this call's active admission, capture, assessments, key work, lowering and
publication preparation. Idle time between a saved as-of capture and a later
call is excluded. Timed implementation must partition nonoverlapping stages:
count delegated elapsed time once, not both in an outer wall-clock interval and
in returned component Usage. The same P/R/D construction applies to carried
active_nanoseconds and the derived rank duration ceiling. Negative duration is
invalid; a carried total at or above the ceiling stops before new work.

C02's active time is measured only when its optional timer is enabled. C05
must likewise avoid new clock reads when timing is off. A C02 capture made with
timing off cannot retrospectively report its old elapsed cost; the result must
retain that configuration and must not label an absent historic measurement as
measured zero. A newly timed current selection enables timing for its capture
and all delegated stages. A timed as-of selection either has a timed preparation
record or reports that its ceiling covers measured current work plus recorded
preparation only, with prior unmeasured capture explicitly excluded. This
distinction must be exposed in accounting, not encoded as false precision.
The proposed `preparation_timing` field explicitly records absent, measured or
unmeasured prior preparation; it is determined from the actual retained capture
configuration, not a caller freshness flag.

The time bound is cooperative, not preemptive: allocator calls, native lowering,
variable-width operations or destruction may finish after a deadline before
the next check. Check before and after blocking stages and before the no-throw
publication commit. Do not claim a hard wall-clock response bound. Optional
time/resource limits can change success versus failure; if two calls both
complete under the same inputs, their selected choice remains deterministic.

## Lowering and source capture

A height/depth miss without a usable selected modeled_plan lowers only the
already chosen exact tree. All four native work allowances are the remaining
aggregate amounts; optional producer work limits are capped by mandatory finite
host values even when the producer stored nullopt. Native calls expose no
partial work on exception, so reserve the full remaining relevant allowances
before entering the call and refund unused work only on successful return,
following the existing C02 convention. Binding expression/recursion limits are
the finite size_t values of the owned normalized basis. C05 does not advertise
an independent override absent from C02's rank API. Physical options are not
mutated to fake remaining limits; host caps are separate.

If a complete Q assessment already owns the selected modeled_plan, adopting
that immutable handle avoids an additional winner lower. It does not refund
any assessment, identity, replay or payload work. A cache hit after a height/
depth decision can skip actual winner lowering; a cache hit after Q cannot
skip the lowering C02 already performed for every candidate. Report actual
work, not a fictitious cold-path charge. Warm/cold resource success can differ
because one actually avoids work, while any successful choice stays the same.

C01 source work/rows/keys/bytes limits retain their advertised component
availability/accounting. For cardinality-only source capture, rows or key
limits can be zero while cardinality remains available; work/byte exhaustion
can instead return explicit source_budget_exhausted with captured metadata.
That evidence-unavailable outcome may trigger a permitted primary-policy
fallback. A mandatory slot constraint cannot use it. C02 processing budget
exhaustion returns no Evidence/Result and is never fallback.

Raw C01 workload snapshots copy their admitted owner descriptors/cells under
that owner's finite max_cells/configuration. Their complete allocator cost is
not bounded by C05's logical payload ceiling; C02 exposes snapshot sizes and
the source accounting exclusions. Runtime evidence retained by CurrentSelection
keeps that raw snapshot/context alive. The implementation must document it as
retained owner-capture storage, not claim the pure-result payload cap covers
every byte in the process.

## Cache and final publication transaction

Cache retention has independent finite caps for entry count, total exact key
bytes and logical public plan payload. Key copies/cache entry cells additionally
consume this selection's aggregate work/payload. A selection never evicts
unrelated entries merely to make temporary construction succeed. On a miss,
prepare a complete candidate entry, eviction list, selected bundle and (for the
bridge) CurrentSelection wrapper off to the side. Precheck all counters and
remaining capacities, run the final time check, then commit with nonallocating
noexcept splice/counter operations. Only that commit can publish a Result and
cache statistics/change together.

No prior cached entry, FIFO order, statistics, returned result, provider state
or runtime owner is changed by failure. Persistent OOM must be survivable during
admission, capture, normalized replay, JSON cleanup, two assessments, key
preparation/lookup, entry staging and final wrapper allocation. A catch around
the final allocation is insufficient; every owned temporary must unwind safely.
There is no resource-to-height or resource-to-next-candidate fallback. A retry
after removing the fault or increasing a cap must produce the same exact choice
for unchanged semantic/evidence inputs. Cache creation and input construction
remain separately reported allocating admission operations outside select.
