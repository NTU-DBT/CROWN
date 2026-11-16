# Independent acceptance plan

These are proposed tests, not executed evidence. C02's accepted tests establish
useful predecessor behavior but do not establish C05 cache, transaction,
constraint or freshness correctness. The implementation author and an independent
author must build separate expected-value traces against the final typed API.
No future test is allowed to create public authority through a private factory.
Root alone owns execution, sanitizer runs and native registration acceptance.

## 1. Literal complete-family selection

Start with the checked Boolean R(x), S(x,y), T(y) corpus under
`tests/candidates/queries/boolean_rst.cq.json` and its native-S,
generalized-x and generalized-y tree fixtures. Obtain the original exact
height-two proof through P06 and the actual three typed P07 members, identifying
them by the fixture trees' structural keys, not relying on enumeration position.
Use one actual physical row per base. Enable current-only committed input census;
drive 90 R, 5 S and 5 T committed no-op operations, not fabricated Evidence.

| Case | Native S | Generalized x | Generalized y | Expected decision |
| --- | ---: | ---: | ---: | --- |
| Hot R depth N, W=100 | 195 | 105 | 190 | generalized x |
| Mirrored hot T depth N, W=100 | 195 | 190 | 105 | generalized y |
| Tuple/index Q | 24 | 32 | 32 | native S |
| Hot R depth with slot cap 31 or 24 | feasible | excluded | excluded | native S, N=195 |
| Hot R depth with slot cap 32 | feasible | feasible | feasible | generalized x, N=105 |
| Any primary with slot cap 23 | excluded | excluded | excluded | constraint_unsatisfied, checked=3 |

Assert every candidate's exact height, N/W, Q and all C02 terms. Reconstruct
native depth from literal node paths and physical alias routing; reconstruct
Q from literal populations and index widths independently of production scoring
helpers. The existing independent C02 fixture has 12 slot terms for native S,
14 for each generalized shape and explicit generalized union bounds. Preserve
these values. Verify every selected PhysicalPlan by actual initialization and
the same independent set-evaluator result. Do not equate proxy ranking with
observed fastest execution or allocator memory.

For ties, use symmetric positive weights and compare full structural-key bytes
as unsigned bytes, independently of the production comparator. Reverse the
retained order where supported by distinct actual providers/seeds; equal scores
still choose the same key. A changed retained family/order/exhaustion namespace
may miss the cache while retaining the deterministic winner. Counter values
whose products exceed UINT64_MAX must preserve exact canonical integer results
and ordering; reuse an independent decimal-digit oracle, not the UInt backend
under test, for new constraint-boundary expectations.

## 2. Physical source and typed output preservation

Rebuild the existing normalized two-alias fixture through public bind/normalize/
P06/P07/P08 APIs: physical table 1 contains two rows, table 0 is unused, two
logical occurrences route to table 1, and a local predicate leaves one result.
Three no-op inserts plus two no-op erases on table 1 and two no-op inserts on
unused table 0 yield exactly N/W=10/7 for both height-one aliases. Physical
source rows are `{1:2}`, not the filtered answer cardinality 1; table 0 affects
W but needs no source-cardinality capture. Selection must retain the complete
normalized adapters, predicate, parameters, output names and route identities.

Use the independent 38-digit Decimal predicate/repeated-head fixture with two
physical rows and one literal answer. Q is 13, including the actual repeated
output layout semantics. Slot cap 13 succeeds and 12 fails. Allocator byte cap
13 fails as unsupported before capture; no units conversion is inferred from
the numeric coincidence. Construct a tuple with unequal repeated values to
verify the returned layout's equality check, not merely a copied descriptor.

Use the native unary/nullary fixture with three physical rows: Q=14 for the
unary query and Q=4 for ignored/nullary scope. Empty physical input gives Q=0;
constant true and constant false height-zero operators also give Q=0 while
retaining their distinct answers. Slot cap zero succeeds only for exact Q=0,
never for missing evidence. Zero committed census is unavailable depth, not
an assumed uniform or zero-cost distribution.

Compare DirectCQ and PhysicalBasis from the same direct CQ/options. A normalized
basis and a core-only physical owner can share a CQ binding yet have different
physical semantics; reject that mismatch even if C02 alone can rank each in
its own context. Change raw SQL comments, alias labels, output labels/order,
constant/parameter values and source options through valid public construction.
Admit matching sources or explicitly reject mismatches; never transfer facts
between them using only the semantic digest. No cache hit may bypass P08's
supported transport/type domain.

## 3. Fresh, stale, as-of and incomplete observations

Run each actual-owner case for PhysicalRuntime, DeltaRuntime and QuerySession
where that public owner supports it. A saved explicit Evidence always produces
an as-of pure Selection. After a hot-input shift/reset/reconfiguration, a new
select_current call captures and ranks the new interval; it cannot claim the old
evidence current because rows or plan hashes match. Compare the entire actual
retained owner/epoch/interval/configuration/reset/segment/mode record.

| Boundary/change | Required behavior |
| --- | --- |
| Fresh unchanged owner | New capture each call; a cache hit may reuse only the plan |
| No-op commit | Epoch and input weights advance; old result stays historical; current key changes |
| Changed insert/erase pair restores rows | Physical row equality cannot restore old epoch/census identity |
| Different owner with same plan/data | Actual new owner identity retained; no old freshness assertion |
| Workload off or zero census | Depth unavailable; explicit primary height fallback or no selection |
| Reset/configuration/segment/mode rotation | Current interval only; old segment never silently added; physical Q can remain usable |
| Sampled/truncated detail with exact root census | Depth remains eligible when its actual required roots are complete |
| Saturated required roots/denominator, degraded protocol or interval-generation flags | Explicit policy reasons; no wrapped/capped ratios |
| Source work/byte cap exhausted | Preserve source_budget_exhausted and capture status; optional primary fallback only |
| Cardinality-only rows/keys cap zero | Exact source cardinalities remain usable when C01 reports them available |
| C02/C05 processing cap zero or OOM | Resource/allocation stop; no evidence fallback |
| Private pending or released/dropped boundary | Current selection rejects even with height fallback; prior history survives |
| Aborted attempt with no committed change | Fresh diagnostic context retained; cache hit allowed only when all key inputs actually remain equal |
| Stopped session retaining runtime, unread batches, window expiration | Follow actual owner contract; do not invent release/current from a session label |

A primary fallback never bypasses a required slot constraint. Require-evidence
and explicit height-fallback outcomes must be distinct. An unavailable memory
record is not Q=0, and uncomputed C02 placeholders are not displayed as actual
zero scores. Use testing-only saturation seams only in the matching testing
runtime bridge; ordinary consumers must link a production-only closure.

## 4. Exact key and structural authority

Build a field-mutation matrix independently from `CACHE_KEY.md` against the
final encoder. Single-field cases must cover Catalog version, source schema
version, every Column field/DecimalSpec, constraint status/ordered columns/
referenced columns, key hints, static statistics, all Query variables/terms/
ordered repeated head/contradiction, all raw TreeNode/claim/order fields,
PhysicalOptions and every supported normalized field. Valid mutations use new
typed public proofs/plans. Invalid or unsupported IR must fail before lookup.
Private byte-visitor tests may construct records to test framing but cannot
publish a Selection or bypass the public authority gate.

Use NUL/high-byte strings, Boolean versus int64, dates versus integer day counts,
Decimal canonical equivalent spellings/sign/scale/boundaries, absent versus
present optionals, empty versus singleton sequences, reordered vectors and
repeated outputs to test injectivity. The expected framing oracle must be a
small independent encoder for the relevant literal records, not a call into
the production visitor. Decimal access must use the existing public canonical
formatter; no access to private coefficient storage is assumed.

The native-S permuted fixture shares a structural key but changes raw ID/order
representation. Its artifact cache must miss or reject the incompatible exact
binding; no alpha-remapped plan/proof is returned. A fresh independently replayed
original proof with unchanged source/context can reuse a plan, but the returned
snapshot/proof must be the current call's handle and certificate witness, not
the entry's historical proof. An editable certificate/OracleResult/validated
incumbent/raw tree cannot substitute for CandidateSnapshot at compile time.
Moved-from handles fail without cache mutation. The low-level PhysicalPlan
height_status remains valid_upper_bound; no JSON optimality field is invented.

Use singleton partial, expanded partial and exhausted provider snapshots. The
default selects best among each fully evaluated retained set and preserves its
real completeness bit. require_exhausted_family rejects partial snapshots.
Equal winner across family expansion must still have a different family key.
Cancellation/timeout progress stays separately with the provider; no invented
timeout field is extracted from the snapshot. Selection never advances it.

## 5. Artifact reuse, layouts and cache lifetime

Cold/read-write then warm/read-only selection with identical semantic request
must hit the same exact key: CacheUse controls effects, not key identity. Verify
fresh rank terms and fresh capture on the hit. Compare the chosen raw tree,
complete physical descriptors, canonical serialization and actual outputs.
Do not compare heap addresses or require a cold plan's token identity to equal
the cached token. Build input/result tuples only with the returned whole plan;
cross-plan projections must enforce their actual token contract.

For depth/height, verify hit lowering work is zero only when lowering really was
avoided; for Q or a slot constraint, verify full candidate lowering work is still
charged and all modeled plans are retained. Unsupported layout/index policy
values fail. The P08 composite/reordered and equal-scope self-join fixtures must
retain one shared requirement for identical `(relation, ordered fields)` and
separate requirements for distinct ordered keys/relations, preserving merged
uses and target tokens. No alternate backend is asserted.

Test cache capacities zero, one and two; FIFO eviction; no reordering on hit;
no insertion for read-only miss; exact key/plan-payload capacity and one-under;
an oversized individual entry; counter overflow; clear/move/destruction. Keep
old Selection handles through all operations and evaluate their plans afterward.
No tests should depend on hash bucket iteration or pointer-based key identity.
All failed attempts preserve prior entries, FIFO order and all cache counters.

## 6. Aggregate boundaries, OOM and retry

For actual successful selections measure complete logical Usage, then reproduce
exact-limit success and one-under stops for every applicable field: processing
work, cells, key traffic, payload, four native work ceilings and score_bits.
Use a positive two-assessment depth-plus-slot case to prove preparation P is
counted once, both complete assessments fit under one total L and a boundary
between them cannot publish the first assessment as a winner. Keep exact
delegated Requests/Usages and reconstruct `U += V−P` independently. Include a
payload-bound long normalized source repeated across candidates and the actual
Decimal/repeated-layout case. A tiny payload remainder must prevent binding/key
allocation even if the key-byte ceiling is still large.

Test no-timer and timed paths, carried active-time limits at/below P, unmeasured
saved preparation explicitly marked unmeasured, and a shared current-call time
ceiling across capture/ranking/compilation. Use deterministic boundary seams
where appropriate; do not assert tight real-time scheduling. No deadline/OOM
stop may enable statistical fallback or choose the next candidate.

Sweep persistent global allocation failure at every observed allocation in
direct and normalized capture/selection, both assessments, source matching,
binary-key construction, linear lookup, native lower/identity/replay, plan
payload admission, entry preparation and late CurrentSelection publication.
Keep failures active through unwinding; merely failing one allocation then
restoring allocation is insufficient. The coherent patched JSON closure is
required. Compare complete actual owner state, all workload stamp/options/modes/
Metadata/descriptors/cells, prior Results/keys/scores, proof validity and cache
order/counters. No attempt may mutate committed runtime state or merge aborted
cells. Remove the fault and require an exact successful retry. Production and
matching testing variants must both pass strict and full sanitizer/leak runs.

## 7. Layering and eventual native gate

Compile/link a pure selection consumer with no runtime/report archive, production
and testing runtime consumers with only their matching bridges, and public guide
examples without private headers. Independent arithmetic/byte-key oracles remain
separate from production implementation. Preserve upstream-vs-patched JSON
controls offline and the current vendor provenance; C05 does not change that
patch or distribution-license status.

After reviewed implementation and excluded root runs, a separate native
publication must preserve all current 143 CTest registrations and existing
commands/order, add the actually authored C05 cases and apply sanitizer settings
to all new tests. Root then verifies the actual complete target/source/macro/link
inventory and five configurations, with exact source guards and independent
review. A preflight cannot forecast a verified final test count or replace those
gates. C03 calibration, C06 switching, C07 measured regret and S05 allocator/peak
accounting require their own evidence; this packet completes none of them.
