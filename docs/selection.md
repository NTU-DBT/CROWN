# Choosing a physical plan from a checked candidate snapshot

This C05 library accepts a typed P07 CandidateSnapshot and returns an owning
immutable selected CompiledProgram. The original C05 registration and its
158-test matrix are recorded in the historical
[verified record](verification/selection-2026-11-07.md). Subsequent S05 ownership
work, the nonempty constant-route repair and their current verification state
are tracked in [the handoff](handoff.md).
A selection does not install a plan in an
owner, migrate state, advance a provider, reoptimize automatically, or create a
new minimum-height certificate.

The public declarations are in
[the pure selection header](../include/crown/planner/selection.hpp) and
[the optional runtime bridge](../include/crown/runtime/selection.hpp).
[The example](../tests/examples/selection_usage.cpp) compiles as production and
testing objects. Link `crown_selection` for pure calls or explicitly opt in to
`crown_selection_runtime` for actual-owner calls. The testing bridge is
`crown_selection_runtime_testing`; never mix runtime variants. The pure library
links without runtime/report; neither bridge has a report dependency.

Choose the explicit source. `DirectCQ{options}` uses the exact Catalog/Query
from the snapshot's original proof. `PhysicalBasis{plan}` preserves an existing
factory-produced P08 source, including normalized SQL, predicates, parameter
specialization, physical aliases, output order/repetition and producer options.
The basis may use another valid tree; its complete source must agree with the
ranking evidence. A core CQ with similar semantics is not a substitute for a
normalized source record. Preparing a basis before calling C05 is separate
caller work.

A nonempty contradiction retains the selected candidate's original body tree,
proof and height. Its compiled artifact uses a separate canonical empty
operator tree/report at height zero. The compiled-input gate derives that
geometry from the admitted query, while the cache key keeps the original
candidate and family. Operator height zero supplies no replacement body proof.

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
[Accounting](selection_accounting.md) specifies exact logical charges and
exclusions. The [cache-key contract](selection_binding.md) defines complete
framing, field order and the artifact-reuse authority boundary.

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

Runtime evidence, score/result arrays and text, selected native programs,
selection source/request text, assessments, decisions, cache keys/nodes and the
CurrentSelection control now allocate under the original query account.
Processing scratch uses that account too. Held results and cache entries keep
their allocating account until their final release; a cache hit can share an
already funded immutable program from another query without allocating in it.

`plan()` returns `const CompiledProgram&`; runtime/session factories accept that
native artifact and deep-admit it into their new query account. `assessments()`
and `decisions()` return SelectionVector references, and retained source/request
fields use CapturedSource/CapturedRequest. `export_source()`, `export_request()`,
PhysicalPlan::from_compiled and physical JSON writing are explicit caller exports.
Reading or sharing native results requires none of those conversions.

Pure DirectCQ without evidence is the initial compiler entry point. Its initial
compiler workspace precedes execution admission. A supplied immutable compiler
basis and proof/family/cache handles remain input boundaries. Runtime selection
uses its admitted native source and compiler limits; constructing a new runtime
separately checks its backend operation allowance, shared across program admission
and initialization. Logical slot/payload limits remain distinct from the verified query allocation
cap. S05 covers post-admission native runtime allocations; initial standalone
compiler/search work, supplied immutable artifacts and explicit exports remain
separate boundaries. See the [query memory contract](query_memory.md) and [S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md).

## Conditional update-pattern admissibility

`Request::update_patterns` optionally adds source-bound rules to the existing
slot and ranking choices. The [update-pattern guide](update_patterns.md#use-the-condition-in-pure-selection)
specifies the conservative transfer gate, sufficient cases and exact costs.
Pure selection remains conditional. The runtime bridges additionally require an
actual QuerySession monitor with matching committed source/rules/sequence; bare
PhysicalRuntime and DeltaRuntime opt-in calls return `unsupported_model`.
See [committed prefix binding](update_patterns.md#read-the-committed-prefix-and-bind-current-selection).
The [V53 source-event and subtree analysis](verification/update-pattern-transfer-v53-2026-11-14.md)
proves supported cases without claiming a complete characterization of mixed
traces or a whole-session CPU/delay bound.
The [qualified support-action profile](update_patterns.md#support-action-guarantee-profile)
connects the proved selected case to its exact source/tree premises. Pure
`Selection::pattern_guarantee()` remains conditional; the current-selection
profile additionally retains the actual Session's as-of enforced premises.
Its explicit `selected_plan_matches_capture()` flag compares complete physical
program hashes, because the winner can differ from the installed plan. A match
does not prove that the whole historical prefix used that program or promise
future freshness. Initialization/rebuild is charged for each plan segment.

The positive `O_Q(I + U)` claim is amortized logical support work for a fixed
query, with I initial physical source rows and U physical source events
including no-ops. Storage lookup/scan/comparison, byte work, adaptation,
allocation, monitor/journal, rollback/retry, output and total CPU/delay remain
separate. Generic `maintenance_bound=not_asserted` status is unchanged; it lacks
the selected proof case supplied by this separate profile. X01 acceptance
remains pending integrated verification and root review.

The opt-in input must be `PhysicalBasis` with a real `CompiledProgram` matching
the declaration. Selection binds it once, copies the validated rules into the
receiving account, and retains one `pattern_analyses()` item per candidate.
Every report keeps its genuine candidate and exact declaration context. A
candidate with no proved sufficient case is `pattern_unproved` unless it already
fails the slot cap. Both outcomes exclude it from winner choice; no eligible
candidate returns `constraint_unsatisfied` before any cache publication.
An all-ineligible request skips primary ranking. Otherwise required C02
assessments still rank the full retained family, including excluded candidates.
No new minimum-height proof or exhaustiveness claim is created.

An absent declaration skips the rule copy and all pattern analysis. Fixed empty
optional/vector storage remains. A present declaration adds a separately
versioned request-byte extension containing source hash/table count and every
canonical rule field; absent requests preserve the previous request bytes.
Failed work or allocation keeps speculative analysis/cache state private. The
existing selection exception boundary is unchanged; there is no new runtime
catch, row mirror or update-path scan.


`CapturedRequest(account, request)` is also publicly constructible as an explicit
raw capture. That constructor stores the limits as metadata and enforces actual
allocator bytes through the account; it does not own an aggregate processing
grant. A direct caller must pre-admit declaration `copy_usage()` and copied cap
text under its own grant. `select()` performs those admissions under
`Request::limits.aggregate` before constructing its retained request. Direct
capture does not validate source binding or confer Selection authority.
