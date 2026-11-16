# Proposed C02 contract

This is a source-grounded design, not an implemented API. Names introduced here
are provisional names for the implementation plan. Existing type names retain
their current native meanings.

## 1. Structural admission precedes all scoring

The ranker accepts one valid `planner::CandidateSnapshot`. Its
`original_proof()` is the sole required-height authority: a valid
`planner::VerifiedOptimum` for the exact original `Catalog`/`Query` binding.
The required height is `proof.height()`. V1 does not admit a best-found upper
bound, a diagnostic `HeightInterval`, a caller's numeric height, raw trees,
editable report JSON, or a cost-based relaxation of the required height.

Read each `MinimumHeightCandidate` from that snapshot. Before looking at any
score, require a valid handle, the snapshot's original binding/context, and
`candidate.height() == required_height`. P07's private factory already checks
P02 validity and this height before publication. The C02 entry gate preserves
that authority; it does not manufacture a new proof. A broken factory invariant
is an admission error for the whole request, not a cheap candidate to skip.
Moved-from handles are errors. A valid empty snapshot returns `no_candidates`.

The selected result retains the actual `MinimumHeightCandidate` and unchanged
original proof. Its alternative tree remains a checked upper witness at the
proved optimum; it does not replace the original certificate's witness.
Structural admission is independent of statistics availability and provider
exhaustion. C02 does not deploy, rebuild, switch, or cache a physical runtime.

P07's accepted structural context stays unchanged. Ranking has a separate
versioned policy/assumption namespace. Do not place the proposed C02 policy
names in `CandidateContext.cost_model`: current admission rejects them. Do not
install a ranking decision in `CandidateCache`, whose entries are structural
candidate snapshots only.

## 2. Binding observations to this candidate family

The evidence adapter obtains a real `PhysicalRuntime`, `DeltaRuntime`, or
`QuerySession`; it obtains facts through existing native capture methods.
Support-only owners have no physical-source/input census and cannot supply
these statistical policies. Height-only needs no runtime or evidence capture.

Require full equality of the candidate proof's original catalog/query and
`observed_plan.catalog()/query()`, using P07's exact binding-format-v2 semantics.
These include names, ordered occurrences/head, repeated/ignored terms, raw byte
strings, scalar tags, canonical Decimal values, schema versions, constraints,
hints, and catalog statistics. A semantic/physical SHA, equal display names,
matching row values, or an alpha-equivalent query does not substitute for this
check. The existing encoder is private: sharing it safely is an implementation
task, not an available public helper today.

Keep the observed `PhysicalPlan` as the adaptation context. For direct CQ,
`PhysicalInput.base` maps an occurrence to its original physical table. For
SQL normalization it follows the actual normalized adapter/base route; core
`Atom.table` may be a different logical table. Use `PhysicalInput.occurrence`
and `.base` plus the owned source catalog, never names or a guessed ID. Source
table IDs are meaningful only inside this exact owned adaptation context.

When lowering an alternative for the memory proxy, use `lower_tree` for the
same direct binding or `lower_normalized` for the observed plan's actual owned
normalized program, with the same semantic/cache policy and finite lowering
limits. The lowerer replays normalized programs and checks the tree. Check that
the resulting occurrence-to-base mapping matches the observed mapping. Its
node/index/relation IDs are its own local coordinates. Its physical hash is
expected to differ from the observed tree's hash.

Do not write observations into `Catalog::statistics`: that would change the
P07 original binding. Keep evidence in a separate immutable factory-produced
ranking input. Its constructor is not an import authority; no C02 import path
is proposed.

## 3. Current evidence and retained artifacts

A proposed runtime adapter produces an owning `BaselineEvidence` and passes it
to a pure ranker. It retains no owner pointer, cursor, row pin, or lease. Its
recorded observations describe an **as-of boundary**, not permanent freshness.
The proposed live convenience entry captures and ranks synchronously under the
existing exclusive-caller/single-writer contract. Nothing in C02 resets,
reconfigures, enables, advances, drains, or changes modes on the supplied owner.

For Physical/Delta use `capture_combined_statistics`. For a session use its
single-guard `capture_statistics_context` or `capture_combined_statistics`
without assembling independent user-made state/workload/status pairs. A
dropped session has no current facts. A stopped session retaining its runtime
may still supply a quiescent committed capture. Private pending state is
ineligible even though the workload half exposes previously committed cells.
Committed unread output alone is not pending state and does not disqualify a
capture. Uncommitted queued/window work does not enter the committed census.

For a live/reuse check, compare the retained `OwnerCapture` with the **actual**
owner through `statistics_freshness(capture, 0)`. V1 requires `current`, with no
event-lag allowance. Also require the same physical owner layer and actual plan
binding. `foreign_owner`, `future_sequence`, `scope_mismatch`, `stale`, released,
and pending are separate reasons. A storage revision is only invalidation
evidence: rollback may advance it without a committed owner-sequence change.

Workload reuse additionally compares a new snapshot from that same actual
owner: owner, committed epoch, interval-start epoch, reset generation,
configuration generation, segment, format version, `Options`, and current
`ModeFacts` must all match. Reject saturated reset/configuration/segment labels
for reusable workload evidence; equality then cannot prove interval identity.
No sequence subtraction, assumed epoch adjacency, segment-only check, or
caller-supplied stamp declares evidence fresh. The first live capture records
these unsaturated labels too. State-only cardinalities do not become invalid
merely because unrelated workload interval labels are saturated.

The pure ranker can reproduce a decision from retained factory-produced
evidence, explicitly marked `as_of_only`; it cannot call it currently fresh.
Live selection with retained facts must perform the checks above. A later
update, reset, mode change, or drop never rewrites an earlier result. A failed
attempt at the same committed epoch can change diagnostics; a reuse check
must still re-evaluate current workload health, not infer health from epoch
equality. Any newly degraded root census makes current weighted ranking
unavailable.

Only `Snapshot::cells()` and its current interval are used. Never add
`previous_cells`, previous metadata, or previous-mode intervals. Replaced
history remains diagnostic. A new/reset/rotated interval with no committed
inputs is unknown for update weights, even if the previous interval was large.
An unobserved elapsed time with no commits cannot be classified as wall-clock
staleness: C01 has no arrival clock. The design promises committed-boundary
freshness only.

## 4. What facts transfer across alternative trees

| Current C01 fact | Candidate independence under the binding above | C02 use |
| --- | --- | --- |
| Exact physical source row count | Same source store at the captured boundary | Memory proxy |
| Physical table/operation committed input, changed/no-op census | Same committed input stream and current collection interval | Input weights; changed/no-op recorded as diagnostics |
| Exact source-field projection NDV/heavy keys | Reusable only for the identical source layout and ordered field list | Not consumed in V1 |
| Occurrence derivation/adapter facts | Depend on the exact normalized occurrence program/key, not portable by numeric ID | Not consumed in V1; no remapping assumed |
| Native/generalized records, S/P/E counts or multiplicities | Tree-, scope-, and role-dependent | Never transplanted |
| Reverse-index degrees, event transitions, generalized pre-probe presence | Index/edge/event-population dependent | C03 work, not a C02 weight |
| Collector or current-engine component capacity bytes | Describe the observed collector/owner | Never a candidate memory estimate |
| Catalog `TableStatistics` | Caller metadata in original proof binding; not current measured facts | No automatic fallback |

Generalized pre-probe presence is 0/1 prior membership, not a reverse-index
degree. Repeated transitions are not probabilities. C02 has no calibrated
lookup/touch cost, conditional bucket model, output-demand model, confidence
interval, latency prediction, or arrival-Hz estimate.

## 5. Exact depth arithmetic and operation scope

For candidate T and occurrence a, `d_T(a)` is the number of **native** nodes on
the root-to-a path, inclusive. A native root has depth 1; a generalized node
adds 0. This follows P02's checked native path count, not edge depth or
`EnumerationStep::depth`. Empty/constant routes have no routed occurrences.

Let `b(a)` be its physical source table. For every physical source table r,
including unused catalog tables, and o in `{insert, erase}`, obtain
`w(r,o) = committed physical root Cell.inputs` from descriptors satisfying
`Kind::physical`, `Role::input`, `InputScope::physical_table`, and that actual
table/operation. Require exactly one such root per table/op, matched cell
shape, and no duplicate/missing stratum. Other descriptor kinds are ignored.

All root weights must be exact. Require each native `input_share(root)` to have
`Availability::exact`, `DenominatorScope::all_committed_physical_inputs`, the
matching numerator, and the same positive denominator W. Recompute W by exact
wide addition of the root inputs as a consistency check. Root-cell saturation,
denominator overflow, invalid descriptor/protocol/ordinal degradation, disabled
collection, or W = 0 prevents weighted ranking. Missing roots are unknown,
never zero.

Detail sampling, selected-detail truncation, a detail-only saturation, or a
diagnostic-only `Metadata::saturated` does not by itself invalidate an otherwise
exact root `input_share`. Preserve those diagnostics without changing the root
census into a sample. Conversely, do not use a global detail availability flag
to override an unavailable/degraded root share. No inverse sampling expansion
is used.

Define:

```
D_T(r) = sum over occurrences a with b(a) = r of d_T(a)
W      = sum over all physical r and both o of w(r,o)
N_T    = sum over all physical r and both o of w(r,o) * D_T(r)
score  = N_T / W  (record this exact, unreduced pair)
```

All candidates share W, so compare `N_T` directly. No cross-multiplication or
division is needed for ordering. Insert and erase have coefficient 1. A
committed duplicate insert or absent erase contributes one event; an aborted
PK/FK/type/other update contributes none. Every alias contributes its own depth
for that one physical update; the denominator never multiplies by alias count.
An unused source table contributes to W and contributes zero to N.

This is the committed-attempt depth baseline. It intentionally does not model
whether that attempt visits an alias, passes a filter, creates a derivation,
touches a bucket, or emits output. A no-op-heavy relation can influence this
proxy despite having no support transitions. Changed-only, operation-specific
coefficients, selectivity correction, and timed rates require separate named
future policies; they are not hidden settings in V1.

## 6. A concrete simple memory-aware proxy

Use only the exact current row counts `n(r)` for distinct physical bases routed
by this adaptation context. Request `SourceScope{r}` with `fields = nullopt` in
ascending source-table-ID order. All requested components must be present,
available, and have cardinalities; a zero is a known empty source. No NDV scan
is required. The current 256-selection limit is a real V1 admission limit;
do not split captures across epochs to evade it. Memory policy can operate
while workload counters are off.

Lower each admitted candidate using the context in section 2. For field width
k define `P(n,k) = min(n,1)` when k = 0, otherwise n. Projection cannot increase
set cardinality, and all empty tuples share one key. Compute bottom-up:

```
R_v = P(n(b(a)), width(records_v))          if v is native occurrence a
R_v = P(sum over children c of P_c,
        width(records_v))                  if v is generalized
S_v = R_v
P_v = P(R_v, width(parent_support_v))
E_v = P(R_v, width(visible_v))               only if visible_v exists
```

Here R/S/P/E are **bounds derived for this candidate**, not observations copied
from the running plan. Native filtering/projection cannot create more records
than source rows. A generalized record set is the union of its children's
parent-support keys; the lowerer checks each child's parent-key layout equals
that generalized scope. Survivors are a subset of records; P/E are projections
of survivors. These facts establish the stated bound without a join-independence
or selectivity assumption. They do not bound global output size.

For each candidate relation of role `native_records`, `generalized_candidates`,
`survivors`, `parent_support`, or `visible`, let U be the corresponding bound and
k its actual lowered layout width. Add `U * (1 + k)`: one abstract tuple slot
plus one scalar slot per field. For each **unique** `IndexRequirement`, let U
be the bound for its own indexed relation and j its projection width; add
`U * (1 + j)`: one membership slot per possible row plus a worst-case key slot
per field per row. Count a shared requirement once, regardless of how many
`uses` or edges refer to it. No speculative new index is registered.

```
Q_T = sum selected relations U_relation * (1 + layout_width)
    + sum unique indexes    U_indexed_relation * (1 + key_width)
```

`tuple_index_slots_v1` minimizes Q_T. A zero-field relation still costs a tuple
slot; a repeated head column does not inflate an E layout whose actual variables
are deduplicated. Use the candidate's lowerer-selected visible relations, not
all head columns or every tree node by assumption. Constant routes have Q = 0
for these selected components.

Q is an upper bound on these **abstract modeled components** under source-count
bounds. It is not an upper bound on allocated bytes. It assigns each scalar
field one slot irrespective of string/Decimal payload length. It excludes source
storage and native derivation maps (fixed by the adaptation context), support
count/child-flag metadata, allocator/container overhead and capacity, journals,
output buffers, readers, statistics, temporary lowering/capture storage, and
peak coexistence. It can misorder actual memory use. A byte budget must not be
checked against Q; S05 and C05 own that future claim. There is no implicit sum
of Q with N, nanoseconds, or bytes.

## 7. Numeric domain, ordering, and unavailable policy

Native observations remain their exact `uint64_t` values. Convert counts,
depths, widths, and vector sizes into an exact nonnegative wide integer **before**
adding or multiplying, including width-plus-one. A value above `UINT64_MAX` in
a derived numerator, union bound, or memory product is an ordinary exact value,
not unknown statistics. Compare wide integers directly. Record canonical base-10
digits (`0` for zero, otherwise no leading zero/sign/whitespace); keep an exact
unreduced N/W pair. No floating-point or Decimal-value arithmetic, `__int128`,
wrapping, saturation, truncation, or silent rescaling is permitted.

A 512-bit default is sufficient for every score admitted by the current native
domains, rather than merely for the small examples. The existing P07 binding
implementation requires `size_t` to have at most 64 value bits. Put
`U = 2^64 - 1`, let m be the occurrence count, and h the native height:

- `W <= U` follows from the required exact positive native C01 denominator;
  `m <= U`, `h <= m`, and `N <= W*m*h < 2^192`. Native depth is not restricted
  just because `W > U/h`.
- Each native source count is at most U. For a generalized node, its bound is
  the sum over a first-native frontier of disjoint child subtrees, so every
  R/S/P/E bound is at most `m*U < 2^128`. Unary generalized ancestors do not
  multiply that frontier. This relies on P02's actual tree property.
- Each actual relation/index vector has at most U members, and each layout/key
  width is at most U. Thus `Q <= (relation_count + index_count)*m*U*(U+1)
  < 2^257`. The addition of one to a maximum width takes 65 bits; promoting
  after a 64-bit addition would be a defect.

Use an explicitly bounded implementation with 512-bit storage and a configurable
finite `max_score_bits` in 1..512 (default 512). The operation result, not an
overly conservative bit-length estimate, decides whether the configured cap
was exceeded. A lower caller cap may stop an otherwise valid score. Charge
limb operations and output digits to the ranker's work/payload budgets. Bit,
work, or report-payload exhaustion returns a resource stop transactionally,
with no selected result and no height-only fallback. Under the default bit cap,
an arithmetic capacity failure on admitted current-format inputs is an internal
implementation defect, not an ordinary data-unavailable case.

The concrete backend is a private unsigned limb type with 16 base-2^32 limbs,
uint64 intermediates, and a 32-limb scratch product. Schoolbook multiply/add
fits each `uint32*uint32 + limb + carry` in uint64; retain the complete scratch
result, check the configured bit cap, then publish. Exact decimal conversion
uses bounded long division by 10. A separate decimal-digit test oracle checks
values/carries and limit status. Current CMake/source and searched local include
locations contain no Boost integration/header; this plan adds no Boost or other
dependency. See ARITHMETIC.md for the operation/publication contract and bound
derivation. No implementation or dependency installation is performed here.

The native C01 `input_share` denominator rule remains intact. If that API reports
an unavailable/degraded denominator, V1 does not silently rehabilitate it from
lower-bound/capped values. This is separate from exactly representing N and Q
above 64 bits. Any future policy that reconstructs a wider input census from
independently exact raw roots must specify and validate that evidence contract
separately; it is not implied by choosing a wide arithmetic backend.

The total ordering is `(required_height, secondary_score, structural_key)`;
height-only omits secondary score. Compare complete structural-key bytes as
unsigned octets, with a shorter equal prefix first. Never use key hashes,
display IDs, pointer addresses, provider arrival order, or locale collation.
Duplicate keys in a trusted snapshot would be an internal invariant error.
Reordering nodes/children does not change P07's key or these scores. Tie
selection is deterministic for the same retained key set, policy, and evidence.

Default unavailable-data behavior for a requested statistical policy is
`require_evidence`: no selection and exact reason(s). A separate explicit
`height_only` fallback may produce a selection over the **whole same admitted
snapshot**, with requested policy, effective policy, and all fallback reasons
recorded. It does not synthesize uniform weights, use catalog estimates, drop
unscorable candidates, or turn an unknown into zero. It never silently switches
from memory to depth or vice versa.

Unavailable evidence can trigger that configured fallback. Invalid
handles/bindings, broken structural invariants, allocation failure, score-bit
or evaluation budget exhaustion, or timeout cannot; those abort the
request without a new selection. This distinction prevents a resource-limited
prefix of scores from becoming an unadvertised different policy.

## 8. Partial providers, work limits, and publication

C02 never advances a provider, searches for a new proof, or assumes an original
seed is already published. The immutable input snapshot owns its retained
prefix and real `family_exhausted()` bit. Results record its family, retained
count, evaluated count, and exact keys. If exhausted, a completed ranking is
best under the named proxy within that P07 family plus admitted seeds; otherwise
it is best among that retained prefix only. Neither status proves global
minimum maintenance cost, memory, or even coverage of every admissible tree.

`CandidateSnapshot` does not carry the provider's last stop reason. Snapshot-only
ranking therefore reports `provider_stop = unavailable`. A future wrapper may
copy progress from the same actual provider at snapshot admission under exclusive
ownership, labeled diagnostic only. Do not accept a caller's timeout/exhausted
boolean as authority. A time-limited provider can publish different prefixes
across machines; reproducibility means identical recorded retained inputs,
not identical wall-clock cutoffs.

Evaluate all admitted retained candidates before publishing. If evaluation
times out or exhausts a cap after scoring k of n candidates, expose k/n and
the stop reason but no selected result. Any prior separately returned result
remains immutable. A rerun with larger limits starts a new evaluation; no C02
resumable cursor is promised in V1. The provider's independent continuation is
unchanged. Empty snapshots and empty source/observation populations are distinct.

Proposed finite defaults for ranker-owned processing are 128 candidates,
1,000,000 work units, 1,000,000 structural/score cells, 512 score bits, 8 MiB of
examined/copied binding/key bytes, and 16 MiB of modeled ranker payload. Other
limits may be raised explicitly but remain finite in V1; score bits stay within
the declared 512-bit representation. Depth walks, source/descriptor examination,
wide limb arithmetic, decimal digit emission, emitted score terms, key-byte
comparisons, and payload construction must be charged. Internal exact-binding
reuse needs a bounded walk/encoding
path; charging only after serializing an arbitrary binding is insufficient.

Lowering and normalized replay retain their own existing finite limits, also
bounded by a declared aggregate allowance across candidates; expose their
separate work/identity usage. Require finite values, never silently copy an
unlimited owner option into ranking. Source capture uses finite C01 Limits and
one request budget. Existing workload snapshot creation copies the configured
descriptor/cell slabs before C02 processing can inspect them: its allocation
cost is bounded by the owner's admitted collection configuration, **not** by
the ranker's later payload cap. Report that admission cost separately. Do not
claim an end-to-end allocator or peak bound from these component caps.

An optional ranker active-time ceiling is a soft stop checked between charged
units/indivisible native capture or lowering calls. It cannot interrupt an
allocation or promise a hard deadline. Time is not used in any score and does
not supply C01 arrival rates. Zero work/time grants return a resource stop with
no selection. All result construction is transactional; allocation failure
leaves snapshots, evidence, owners, caches, and previous results unchanged.

## 9. Reproduction record and scope

Each successful result must retain enough immutable input to reproduce its
score: original typed binding/proof, P07 context/family/completeness and retained
keys; requested/effective ranking policy and versions; source-plan/adaptation
context; capture owner/epoch/layer and exact current interval/options/modes;
availability and fallback reasons; all root input weights and denominator W
for depth; required source counts and each candidate's own relation/index widths
and derived cardinality terms for Q; native depth per occurrence/base; all exact
integer scores; tie rule; processing/capture/lowering limits and usage. A digest
may label those records but cannot replace full binding or score inputs.

No mutable public aggregate or serialized ranking record can manufacture a
P07 candidate/proof. No new wire import, schema compatibility, statistics model
calibration, physical plan cache/switch, memory-byte enforcement, or global cost
optimality is claimed by this preflight or by the proposed baseline alone.
