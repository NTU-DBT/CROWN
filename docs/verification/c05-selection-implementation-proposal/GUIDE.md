# Choosing a physical plan from a checked candidate snapshot

This excluded C05 implementation accepts a typed P07 CandidateSnapshot and
returns an owning immutable selected PhysicalPlan. Its native publication and
matrix remain separate later gates. A selection does not install a plan in an
owner, migrate state, advance a provider, reoptimize automatically, or create a
new minimum-height certificate.

The public declarations are in
[the pure selection header](overlay/include/crown/planner/selection.hpp) and
[the optional runtime bridge](overlay/include/crown/runtime/selection.hpp).
[The example](overlay/examples/selection_api.cpp) has production and matching
testing compile-only recipes. The pure library links without runtime/report;
the bridge uses the matching C02/runtime variant and never a report target.

Choose the explicit source. `DirectCQ{options}` uses the exact Catalog/Query
from the snapshot's original proof. `PhysicalBasis{plan}` preserves an existing
factory-produced P08 source, including normalized SQL, predicates, parameter
specialization, physical aliases, output order/repetition and producer options.
The basis may use another valid tree; its complete source must agree with the
ranking evidence. A core CQ with similar semantics is not a substitute for a
normalized source record. Preparing a basis before calling C05 is separate
caller work.

Native lowering supports arithmetic policy `exact-nonnull-v1`. C05 preserves
that restriction and the complete supplied PhysicalOptions. Other nonempty
planner, optimization and cost-version strings are cache namespace inputs;
changing one does not enable another planner, arithmetic backend or C03 model.
An unsupported arithmetic value cannot produce or install a selected artifact.

Three baseline policies are supported: minimum-height deterministic key order,
committed-input-weighted native depth, and candidate-local tuple/index slots.
The latter two use the exact C02 definitions. Committed no-ops are included in
input weights; this is an update-attempt proxy, not an event-cost or arrival-Hz
measurement. Physical aliases share their base update count while each native
occurrence contributes its depth. Unused physical tables remain in the census
denominator. Slot bounds use routed physical source cardinalities, not filtered
answer counts or another plan's P/E/degree IDs.

The default is weighted depth with an explicit height fallback. Set
`Fallback::require_evidence` to reject missing policy facts. A mandatory
`TupleIndexSlotLimit{"31"}` first evaluates complete slot scores for every
retained candidate and excludes values above 31. Weighted depth is then
evaluated over the same complete retained set, and C05 chooses its best eligible
member. Consequently the retained C02 primary assessment's winner can differ
from C05's constrained winner. A height fallback never bypasses the mandatory
slot constraint. The cap is canonical decimal in 0..2^512−1.

`AllocatorByteLimit`, including zero, fails with
`unsupported_memory_prediction`. `maintenance_cost` fails with
`unsupported_model`: C03 calibration is not present. Only the existing native
layout and identical-index-sharing policies are recognized. Slots must never
be displayed as allocator bytes or compared to a requested byte budget.

Use pure `select(..., evidence)` for a retained as-of record. Its result retains
that record and makes no current-owner assertion, even if a cached plan is
reused. Use `select_current(..., actual_owner)` for PhysicalRuntime, DeltaRuntime
or QuerySession. It takes a new bounded C02 capture on every call, including
height-only calls, and checks the actual committed boundary. Private pending
state and released/dropped owners reject even height fallback. Stopped sessions
which retain their runtime follow that actual live boundary. After return, the
owning capture remains history; it does not promise the owner stays unchanged.

Keep the actual owner's exclusive synchronous-access contract throughout the
entire call, from capture through selection and publication. The bridge does
not acquire a new concurrent-owner lock. A shared PlanCache likewise requires
exclusive caller access; immutable returned results may outlive that access.

Reset, configuration and mode/segment changes establish a new current interval.
Previous-segment counters are never silently combined. Sampled or truncated
detail does not invalidate an otherwise complete exact root census. Missing,
saturated or degraded required roots do. Exact current physical cardinalities
can still support slots when depth census is off, empty or saturated. A source
capture work/byte limit can produce explicit unavailable evidence and a permitted
primary fallback; C02/C05 processing resource failure never does.

Every successful Selection retains the current snapshot/proof, selected index
and exact candidate, whole plan, request, full C02 assessments, complete
eligibility vector, effective policy/fallback reasons and aggregate accounting.
Read score fields according to each assessment's effective policy. Uncomputed
C02 default `0/1/0` fields are placeholders, not observed zero-cost facts.
`retained_prefix` means best among this complete evaluated prefix.
`require_exhausted_family` additionally requires its real P07 exhaustion bit;
neither choice claims global maintenance-cost optimality. Provider cancellation
or timeout progress remains with the provider.

An optional `PlanCache` is move-only and exclusive to its caller. The default
selection bypasses it. A read-only call may use an existing artifact but never
insert; a read-write miss installs a whole artifact after all work succeeds.
FIFO hits do not reorder. Capacity zero explicitly disables the cache. A single
entry exceeding key or logical plan-payload capacity fails rather than silently
ignoring the requested cache operation. Cache-use mode and retention caps are
recorded separately from artifact equality, so read-only can hit an entry made
by read-write.

Every cache lookup follows fresh full admission, source checking and ranking.
Exact binary keys bind the full ordered family, source/program/options,
requested policies/constraints/caps and current score context. They do not cache
proofs, scores, owner freshness or diagnostic session context. A depth/height
hit can avoid the selected winner's lower. A slot assessment has already lowered
every retained candidate, so a hit cannot erase that work. Keys are diagnostic
bytes, not an import or insertion capability. Clear, move, eviction and cache
destruction preserve prior result lifetimes.

All processing and native work limits are finite aggregate limits. Dual
assessments share the original grant and charge evidence preparation once.
Default calls take no clocks. Optional timing is soft and exposes whether old
preparation was measured; unmeasured historical capture is not invented.
[Accounting](ACCOUNTING.md) specifies exact logical charges and exclusions.

Inspect `Attempt.stop`, `stage`, `resource`, `component_stop`, `reasons` and
evaluated counts when no selection is returned. Unsupported features, unavailable
facts, an unsatisfied complete constraint, and resource/allocation failures are
distinct. Failed calls leave the cache and actual owner unchanged. Retry with
the same inputs after removing a fault, or explicitly choose new facts, a new
policy or a larger finite grant; the implementation does not do so silently.

For a delegated C02 byte stop, its existing `component_stop == byte_limit`
combines key/payload categories; C05 retains that category and does not invent
a finer `Resource` value. Likewise a native error without partial counters
retains its generic lower-work stop and conservative reserved usage.
