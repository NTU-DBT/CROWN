# C02 baseline ranking — excluded implementation proposal

This packet implements the accepted C02 design in an excluded overlay. It does
not change native sources, native CMake registration, the ledger, or the
AntiGravity handoff. C02 remains `not_started`. The parent owns execution and
acceptance; compilation is not runtime verification.

The exact predecessor is `../c02-ranking-preflight-proposal/`: its package
manifest is `ac49d0bd498df1bf9f905346600eb39d3df78c86122813012e28d1645b0d81fa`
and its 58-input manifest is
`06476999071290bac59db3bbebea72ac3f12f24aed262a08ff0c4013dd4c5616`.
`build/verification/c02-ranking-design-root-review-2026-11-07.json` authorizes
excluded implementation only. Native C01 and P07 are inputs, not modified
completion evidence.

## Implemented contract

`planner::ranking::rank` accepts an actual private-factory P07
`CandidateSnapshot`. It preserves the original `VerifiedOptimum`, requires
every retained candidate to have that certified minimum height and original
full binding/context, and finishes this gate before scoring or fallback. The
unchanged P07 structural context remains `no-cost-v1`; observations never
confer proof, certificate import, or deployment authority.

The three policies are:

| Policy | Exact comparison value | Input meaning |
| --- | --- | --- |
| `height_only` | Full unsigned structural-key order among the admitted height | No runtime needed |
| `committed_input_native_depth` | Integer numerator `N`; common positive denominator `W` retained separately | Current committed physical insert/erase attempts, including no-ops, times the sum of native depths of all routed aliases |
| `tuple_index_slots` | Integer `Q` | Exact routed physical source counts and each candidate's own lowered relation/index layouts |

For depth, `N=sum_r((insert_r+erase_r)*sum_{a:base(a)=r}depth_a)` and
`W=sum_r(insert_r+erase_r)`. Each physical event enters W once. Unused physical
tables remain in W with depth contribution zero. Changed/no-op counts remain
diagnostic; aborted attempts are excluded. This is a committed-attempt proxy,
not transition/event cost or an arrival rate.

The memory policy is the accepted unitless tuple/index-slot proxy. With
`P(n,k)=min(n,1)` for width zero and `n` otherwise, native record bounds use
source counts, generalized record bounds use the sum of child parent-support
bounds, survivors use the record bound, and P/E use their own projected
widths. Sum `population*(1+width)` for each modeled relation and each unique
actual index requirement. Full per-node population bounds and every term are
retained, together with the candidate's own lowered plan. Current-plan P/E,
degree, derivation and index IDs are never transplanted between candidates.
This is not a byte count, total memory, a conditional-degree model or global
cost optimality.

All arithmetic is exact portable base-2^32 limbs, with a 512-bit representation
and a finite caller cap from 1 to 512. The admitted-domain bounds remain
`N<2^192` and `Q<2^257`. Decimal reporting is canonical unsigned ASCII, with at
most 155 digits. There is no floating point, wrapping, score saturation,
rescaling, or 64-bit-only product restriction. Fixed-width private arithmetic
can reject a caller's smaller cap; it never changes evidence availability.

All retained members are evaluated or no Result is returned. A resource stop
reports how many members were evaluated and never publishes the best prefix.
Results retain the actual snapshot, requested/effective policy, fallback
reasons, limits/usage, exact scores and complete terms. P07 family exhaustion
is available through the retained snapshot; an unexhausted snapshot is only
its retained prefix. No provider is advanced and no provider stop reason is
invented from a snapshot that does not contain one.

## Evidence and freshness

`runtime::ranking` is a separate adapter for `PhysicalRuntime`, `DeltaRuntime`
and `QuerySession`. It uses native joint capture; sessions use the native
single-guard `SessionStatisticsContext`. It stores no owner pointer, lease,
cursor or row pin. Support-only owners are not evidence providers here.

The pure `Evidence` is always an immutable **as-of** record. `rank_current`
captures and ranks synchronously under the native exclusive-caller contract;
`revalidate` consults the actual owner at zero event lag. `boundary` reports
owner/state freshness, while `usable(Policy)` separately combines the facts
needed by that policy. Fresh state with disabled/empty workload can still
support memory ranking. Reset/configuration/mode/segment changes invalidate
old depth intervals without automatically staling unchanged source counts.
Pending, released, foreign-owner, stale, future-sequence and scope failures
remain separate reasons. A dropped session supplies retained metadata and a
released Evidence, not current facts.

Only the current workload interval contributes. Root input counts, denominator,
protocol health, reset/configuration/segment saturation and exact mode/options
identity are checked. Sampled/truncated detail or unrelated detail saturation
does not invalidate an otherwise exact physical census. Capped roots and
unavailable denominators are not made exact by the wide integer backend.
Committed unread output is distinct from uncommitted pending work.

Source capture requests each distinct routed physical base once, at most 256
components, cardinality-only. It neither substitutes logical/core table IDs
for physical bases nor scans unused source tables. A native C01 state-budget
stop is unavailable evidence with `source_budget_exhausted`, actual top-level
and per-component statuses, and native limits/usage preserved. Zero row/key
scan budgets can still satisfy cardinality-only requests. A C02 processing,
lowering, bit, payload, time or allocation stop is a resource failure and
cannot invoke fallback.

Explicit `Fallback::height_only` applies to evidence unavailability for the
whole admitted set. The default requires evidence. Binding/admission failures
and all processing failures never fallback. Neither path resets, enables,
reconfigures, drains, updates, switches or deploys the actual owner.

## Dependencies and resource model

The pure ranker depends on core/SQL/physical-plan types and lowering, with no
runtime or report archive. The separate runtime adapter depends on the native
runtime and pure ranker. No C02 archive depends on observability/report IO.
The existing P07 encoder is shared through one private helper; the original
unbudgeted path retains its field order, prefix construction and bytes. The
bounded path admits each append against both remaining key and payload caps.

`ACCOUNTING.md` specifies the logical component model, including each retained
candidate plan, Decimal coefficients and repeated-layout equalities. Native
capture/replay/lowering remain bounded blocking calls, not interruptible heap
allocators. `Usage.active_nanoseconds` carries measured preparation into rank;
`rank_current` shares one optional soft active-time ceiling across both phases.
No clocks are read by C02 when that ceiling is absent. Time never affects the
score. Split capture/rank with an untimed earlier capture cannot retroactively
measure that work.

The memory-policy fault path exposed an existing temporary JSON destructor
allocation hazard. `JSON_REPAIR.md` describes the narrow local repair, exact
upstream provenance and coherent rebuilt C++ closure. The original header is
preserved. Only parser C objects may be reused from the pinned matching native
configuration; no cached project C++ archive is mixed with the patched header.

## Evidence boundary

The author has executed no produced binary, Python checker, CMake, CTest, symbol
probe or benchmark. `compile-closure.sh` is compile/link only. It rebuilds the
full linked CROWN C++ closure in production and testing variants, preserves
individual compiler commands/logs/dependencies and uses explicit strict or
matching ASan/UBSan flags. `REPRODUCTION.md` and `BUILD_RESULTS.md` describe the
root-only gates and actual compilation evidence.

Root has independently passed the held ten-consumer strict checkpoint and the
separate current public/arithmetic and JSON cleanup checkpoints. This packet
also supplies a separate real normalized-replay fault consumer in strict and
sanitized form. At this publication cutoff, the full matching sanitizer and
supplemental normalized execution receipts remain separate pending root work;
the completed receipts and exact scope are recorded in `BUILD_RESULTS.md`.

The separately frozen historical integer checkpoint was root-executed before
the active-time ABI revision: three groups, 54 operands, 2,916 ordered pairs,
and all 16 limb boundaries passed. Its retained input snapshot is authoritative
for that checkpoint, not these later live headers or the full public API.
Independent tests and JSON cleanup probes are separate packets owned by their
authors; their results are not silently incorporated as this packet's own
execution evidence.

C03 calibration/conditional degree modeling, C05 plan deployment, S05 allocator
and peak totals, a new serialized ranking import/export contract, native C02
registration, a complete native matrix and general cost optimality remain
separate work. The untouched native JSON checksum guard must be reconciled by
a later explicit native integration; dropping this overlay over native sources
alone is not a claim that native CMake has been updated.
