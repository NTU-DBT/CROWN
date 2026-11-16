# Selection contract, proposed version 1

## 1. Authority and input scope

Selection requires a factory-produced, valid P07 `CandidateSnapshot` whose
`original_proof()` is a valid P06 `VerifiedOptimum`. An incumbent, editable
certificate aggregate, validation Boolean, JSON report or raw tree cannot be
used in its place. Every retained candidate must pass the existing C02 complete
binding/context/height admission before any cost decision. Required height is
exactly the original checked optimum, not a height suggested by statistics.
The original certificate retains its own witness; an alternative selected tree
never replaces it.

The caller supplies an explicit source: direct CQ from that snapshot's exact
binding, or an existing immutable P08 `PhysicalPlan` as source/program/options
basis. The latter supports normalized SQL, aliases, filters, constant outputs
and repeated output positions without accepting mutable normalized IR as proof.
Its actual core Catalog/Query must equal the original proof binding in full.
The whole owned normalized source/program and original physical catalog remain
part of source identity, even when two sources have the same core CQ.

For initial normalized selection, the existing finite P08 `lower_normalized`
call on the original proof's checked upper tree creates the basis first.
Its replay/normalization/lowering work is an explicit prior admission, not free
work hidden in selection. C05 re-lowering also has finite host caps. A raw
NormalizedSql convenience factory is not required to bypass this existing
typed route; adding one later would require the same bounded replay and full
binding gate. Direct CQ needs no preliminary physical basis.

Evidence cannot choose the source semantics implicitly. A supplied C02 Evidence
must have the exact source/program/options basis required by the explicit
source, in addition to the C02 core binding check. No facts from a different
normalized predicate, parameter specialization, source schema or options
namespace may be silently transplanted. Matching semantic or physical digests
alone is insufficient.

## 2. Policies and physical choices

Supported orderings are:

| Request | Ordering after exact required-height admission |
| --- | --- |
| Default: committed-input native depth | Exact C02 N/W, then full structural key |
| Height-only | Full structural key |
| Tuple/index slots | Exact C02 Q, then full structural key |

All candidates have the same proved required height. This is the primary
structural objective in every row. Depth uses the same positive exact W across
the snapshot, so N orders its rational scores. Insert and erase committed
physical inputs, including no-ops, supply the current C01 interval's weights;
aliases contribute separate native depths while a physical input contributes
once to W. Previous segments, attempts and aborts are not accumulated. This is
the C02 baseline proxy, not arrival Hz or actual transition/event cost.

The default request explicitly permits height fallback for unavailable depth
facts. `require_evidence` instead returns no selection. The actual effective
policy and reason bits are always retained. Source-budget exhaustion remains
explicit unavailable evidence; C05 processing, score, lowering, time or
allocation exhaustion is never statistical fallback. Unknown/saturated facts
are not zero. No C03 model or calibrated score is synthesized. An explicit
maintenance-cost request returns `unsupported_model` before capture or cache.

P08 currently has one physical layout policy and one index-sharing rule.
C05 names these `native_layout_v1` and `share_identical_requirements_v1`.
The source lowerer caches scope layouts by full ordered variable vector and
shares an index only for the same relation and ordered projection fields,
with an identical target layout token and merged distinct uses. C05 preserves
that behavior and exposes the chosen plan's actual layouts/indexes. It does
not pretend that alternative hash/arena/back-end layouts already exist;
unsupported physical policy values fail explicitly.

The direct-CQ source owns its PhysicalOptions; a plan basis owns its existing
options. P08's policy strings remain exact input namespace labels. They do
not select C03 or overwrite P07's fixed `no-cost-v1` context. C05's own typed
policy/version is recorded separately. Changing the desired P08 options for
a normalized source requires an explicitly rebuilt matching basis/evidence;
selection does not silently reinterpret the old owner under new options.

## 3. Optional constraints and complete decisions

No state-size constraint is the default. An optional `TupleIndexSlotLimit`
uses canonical unsigned decimal text representing 0..2^512−1 and is explicitly
unitless. C05 evaluates the complete C02 slot assessment, then excludes each
candidate with Q above that cap. It cannot label the result a byte-bounded plan.
Any requested allocator-byte/live-byte/peak-byte prediction is unsupported,
including a zero or UINT64_MAX byte limit: fail before capture/ranking/cache,
never convert bytes to slots or silently discard the request.

When a slot limit is present, exact usable source-cardinality facts are
mandatory. Height fallback cannot bypass an unavailable constraint. If no
candidate fits after all Q values are known, return `constraint_unsatisfied`.
The rejection records that all retained candidates were checked against the
constraint. It does not claim structural infeasibility or a global byte result.

Depth plus a slot limit evaluates slots first, then depth over the entire same
snapshot if any candidate is feasible. It uses two complete C02 assessments;
it does not fabricate a filtered P07 snapshot or score only a convenient prefix.
Among the slot-feasible candidates, compare N and then key. If the depth
assessment explicitly falls back, compare keys within that same feasible set.
Height plus a slot limit needs the complete slot assessment and key comparison;
slot policy plus a slot limit needs one complete slot assessment. No useful
partial winner is returned after any assessment resource stop.

The result owns every assessment used, an eligibility flag for every retained
candidate, the selected candidate from the current call, the request and the
actual effective decision. C02's own selected index can differ from C05's
constraint-filtered index; it remains an assessment result, not the C05 winner.
Uncomputed C02 fields (`0/1/0`) remain placeholders interpreted by their
effective policy, not zero-cost facts. All published score/constraint terms
are reproducible from the retained input and exact C02 arithmetic version.

The default family policy accepts a fully evaluated retained prefix and says
`best_among_retained`. `require_exhausted_family` rejects a nonexhausted snapshot
before scoring. Even an exhausted P07 seed-plus-normal-form family is not every
admissible tree/physical backend or a global maintenance-cost optimum.
Selection neither advances a provider nor changes its limits, cursor or cache.
Provider timeout history cannot be recovered from CandidateSnapshot, which
does not expose it; the caller must retain provider progress separately.

## 4. Pure, as-of and current use

The pure entry point takes no owner and either no evidence or explicit immutable
C02 Evidence. With evidence it is always as-of, even if its epoch happens to
match a live owner. It cannot claim freshness. Old results stay valid history
after commits, reset, reconfiguration, owner replacement, stop/drop or release.

The runtime bridge has actual PhysicalRuntime, DeltaRuntime and QuerySession
overloads. Every call captures new C02 RuntimeEvidence with finite caller
processing/source limits, holding the existing single-writer/exclusive-owner
boundary through capture, scoring, artifact choice and final publication. No
callback, background work or caller-labelled current record is accepted.
The bridge retains the actual runtime capture and optional session context.
Its current-at-capture claim is factory-produced and becomes historical after
return; it is never a permanent freshness promise.

This stricter current-selection path rejects a released owner, private pending
state, inconsistent owner/layer/source boundary or failed boundary read before
cache publication, even when height fallback was requested. A caller wanting
only a structural decision can explicitly use the pure entry point instead.
Disabled/empty workload or invalid depth intervals at a valid committed owner
boundary can take the configured height fallback. A slot constraint still
requires usable exact source facts. Workload reset/configuration/segment changes
do not by themselves make fresh physical cardinalities unavailable.

C02 `revalidate` remains useful to callers, but its present API has fixed
internal processing defaults and no usage output. C05 must not call it and
claim those reads fit the C05 aggregate limit. Fresh bounded capture is the
baseline mechanism. It also avoids recycling old facts or inferring freshness
from identical row values. Captures record owner/epoch, pending state, modes,
interval/reset/configuration/segment and saturation exactly as C02 exposes.

## 5. Compilation, reuse and lifetime

After fresh complete ranking and constraint selection, the exact cache key may
reuse only a P08 compiled artifact. For a height/depth winner on a miss, lower
that selected tree with finite remaining host work/identity and normalized
binding/normalization caps. A lowering failure returns no selection; it does
not silently choose the next candidate or call the failed tree infeasible.

If a complete slot assessment supplied the selected `modeled_plan`, adopt that
already admitted plan rather than re-lower it. Its source, options, selected
tree and P08 descriptors must match the intended source exactly. That lowering
work was already paid by C02, including all losing candidates. A cache lookup
then cannot recover or erase that work; no memory-ranking speedup is claimed.

The selected bundle retains the current snapshot and original proof, the fresh
assessments, source, evidence, chosen candidate and owning PhysicalPlan. The
plan's low-level GuaranteeProfile stays `valid_upper_bound`; the separate typed
original optimum supplies the minimum-height authority. No metadata Boolean
is promoted into proof. The result owns no runtime pointer, mutable table,
cursor, tuple pin or delivery lease. Cache clearing/eviction, provider teardown
and owner release cannot invalidate a retained result.

Layout tokens belong to the complete returned plan. A cache hit may share old
immutable tokens; a cold lower may create distinct equal-descriptor tokens.
Choice/semantics/serialized descriptors are deterministic, not pointer identity.
Never combine tuples or projections from a different basis/cold plan merely
because descriptors compare equal. C05 performs no state migration, deployment,
runtime initialization, plan switch, durable import or reoptimization.
