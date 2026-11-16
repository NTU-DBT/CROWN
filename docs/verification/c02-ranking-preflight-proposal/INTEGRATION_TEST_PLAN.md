# Implementation and validation plan

All work below is proposed and unexecuted. The native C01 matrix and frozen
inputs must finish their current lifecycle before a separately authorized C02
implementation changes native sources. This preflight leaves C02 `not_started`.

## Staged work

1. **Binding and typed gate.** Implement the internal full-binding sharing seam,
   preserving P07 bytes and existing behavior. Add the pure ranking result and
   finite-limits types, exact bounded-limb helpers, and height-only ordering. Keep
   statistics/report/runtime includes out of the pure layer.
2. **Depth baseline and actual-owner adapter.** Capture only the state metadata
   and current physical input roots needed for depth. Add the exact source
   mapping, current/as-of distinction, interval validation, and explicit
   unavailable/fallback behavior. Do not enable or reset collection implicitly.
3. **Memory proxy.** Request all required source cardinalities in one finite
   request, lower every candidate with bounded existing APIs, and derive the
   relation/index slot terms. Publish the full derivation, not just one opaque
   score. Record proxy component exclusions alongside the result.
4. **Failure and integration coverage.** Add meaningful public-contract traces,
   allocation-failure sweeps, bounds/overflow tests, and clean pure/runtime
   consumers. Freeze the implementation package and exact compiler commands;
   root alone then runs focused tests and the required native matrix. Preserve
   all pre-existing registrations and legacy report guards.
5. **Acceptance packet.** Record exact retained candidate keys, proof height,
   trace inputs/commits, evidence stamps/options/modes, score terms, selected
   key, policy/fallback, and independent result equality. Mark coverage limits
   and unavailable states. Card acceptance requires executed evidence, not
   this design or the model agreeing with its own arithmetic.

## Required independent checks

| Group | Concrete fixture/oracle | Required assertion |
| --- | --- | --- |
| Typed structural gate | P06 `ExactSearch`/`CertificateReplay`, P07 factory snapshot, moved-from handles, compile-time constructibility checks | No raw tree/progress/report can enter as a certified candidate. Selected handle has original proved height; no proof witness substitution. |
| Exact binding | Existing P07 mutation cases plus source runtime with same semantic digest but changed exact names/metadata/typed values | Full binding mismatch rejects before scoring; statistics cannot rewrite `Catalog::statistics`. Existing cache encoder bytes remain identical. |
| Full retained set | Existing R/S/T independent normal-form oracle | Exact expected key set, optimum height 2, and score table from WORKED_EXAMPLES.md. No reliance on provider index or display ID to identify a tree. |
| Hot input reversal | Same-owner duplicate-insert trace, reset, mirror trace; separate changed-row mixed insert/erase trace | Actual current physical census matches an independent commit log; hot R/hot T change selected key, all candidates' result semantics remain equal to direct evaluation. |
| Aliases | Existing three-occurrence self-join and a normalized SQL alias/filter fixture | One physical event gives one denominator input and all actual occurrence depths in numerator; logical table IDs do not replace physical base mapping. Filter selectivity is deliberately unused. |
| Unused source table | Source catalog has a table with no plan input routes | Its commits enter W and have zero numerator contribution; root coverage still includes both operations. |
| Operation/commit scope | Insert, erase, duplicate insert, absent erase, actual public PK/FK failure, rollback | Successful no-ops count; failures/aborts do not change committed weights or state. Attempts/aborts remain diagnostic, not numerator or denominator. |
| Empty/constant cases | Empty body, contradiction route, nullary atom, empty database, no collection events | Required height/empty candidate distinction stays correct; memory Q uses nullary/zero bounds; zero W is unavailable, not a uniform distribution. |
| Shared index accounting | Candidate with repeated use of one actual `IndexRequirement`, plus distinct projections | Each unique requirement contributes once. Key width comes from the indexed relation's own projection; repeated uses do not multiply slots. |
| Memory bound | Tiny set/map oracle over actual source rows and independently evaluated R/S/P/E for every small candidate | Actual abstract modeled tuple/index slots are at most Q; hand-derived positive R/S/T and nullary values match. No assertion about allocator bytes or RSS. |
| Candidate-local scopes | Alternative generalized roots, node-vector/child permutations, distinct scopes and repeated/empty output fields | Recompute each candidate's own bounds/layouts; do not reuse observed node/index IDs. Repeated head positions do not invent extra visible storage fields. |
| Sampling vs census | Period 1 and 64, selected detail budget 0 or truncated detail, no complete detail samples | Equal committed roots yield identical depth score regardless of detail sampling. Sample means remain unused/unavailable as appropriate. |
| Relevant saturation | Independently inject a root-cell flag/count overflow, denominator overflow, unrelated detail saturation, diagnostic-only metadata saturation | Relevant root/denominator failures block weighting; unrelated flags do not override an otherwise exact native input_share. Do not use one fixture that saturates everything to claim all distinctions. |
| Protocol health | Isolated invalid-descriptor, protocol-error, ordinal-exhausted conditions through testing seams | Incomplete root shares cannot rank. Equal owner/epoch alone does not bless a degraded retained workload snapshot. |
| Exact arithmetic | Separate decimal-digit oracle with 0, max U64, max-1, products above 64/128/192 bits, wide union/width sums, and exact/below-bound bit caps | Promote before arithmetic; default 512-bit scoring handles valid wide values. Lower bit/work caps stop transactionally without fallback. Canonical decimal output and comparison stay exact. |
| Deterministic ties | Same key set from different provider slicing/cache paths and structurally permuted trees; equal scores | Full unsigned-byte key order decides ties; no dependence on pointer, hash, locale, child order, or provider arrival order. |
| Partial provider | Stop after 0/1/k candidates, capacity/work/time stop, cancelled provider, exhausted family | Snapshot-only result exposes actual retained count/family bit and unavailable provider stop reason. Partial family remains partial even if score evaluation completes. |
| Evaluation exhaustion | Exact bit/work/cell/key/payload limits, zero grants, stop after k<n scores, injected lowering/replay limit | No new selected result on evaluation resource stop; prior immutable result remains intact. No statistical fallback after bit/budget/time/OOM failure. |
| Fallback uniformity | Missing one table count, one root, stale interval, unavailable native denominator; both fallback configurations | `require_evidence` returns no selection; explicit height-only scores the entire same snapshot and records reasons. No per-candidate dropping/guessing. |
| OOM publication | Allocation failure at binding/evidence copy/lowering/term/result allocations on one owner | Owner state/counters and input snapshot/cache are unchanged; no partial ranked result. Previously returned results survive failed retries. |

Use existing reference evaluation only as an independent semantic oracle,
not as an import/height authority. Tests for scores should calculate expected
depths and small union/projection bounds in separate set/map code. Do not call
production rank helpers on both sides of an assertion. Keep every fixture's
proof search, enumeration, ranking, capture, and lowering limits finite; the
older test helpers that reset some limits to unlimited must not be copied as
the new C02 resource contract.

ARITHMETIC.md specifies additional representation/carry/string/fault checks.
The root snapshot's saturation status must be exercised independently from a
derived score exceeding 64 bits; those are different cases with different
outcomes. No Boost install or assumed external arithmetic dependency is part
of this plan.

## Freshness and lifecycle matrix

These cases need separate assertions for state-only memory and workload depth;
a single global `available` boolean would hide important distinctions.

| Transition on the same actual owner | State evidence | Workload evidence |
| --- | --- | --- |
| New committed insert/erase/no-op | Older owner sequence is stale at lag 0 | Older epoch is stale, even if row values happen to match |
| Failed update/rollback | Committed state can remain current; storage revision may differ | Committed roots unchanged; new health/attempt diagnostics must still be checked |
| Reset without a commit | Same current state may remain usable | Old reset/interval tuple is rejected; current W=0 is unavailable |
| Reconfigure with same options | Same current state may remain usable | Configuration/reset generations identify a new interval; no old-weight reuse |
| Failed reconfigure | State unchanged | Previous configuration/roots remain intact; no spurious new interval |
| Successful semantic mode change | Committed source rows may be unchanged | Current segment/options/modes change; only new current segment is eligible |
| Failed or no-op mode change | State unchanged | No invented segment rotation |
| Saturated interval labels | Exact fresh source counts can remain usable | Reusable workload identity is unavailable; never trust equal capped labels |
| Pending physical/Delta/session/window preparation | Metadata-only, no committed-state ranking capture | Public committed counters are readable but pending live ranking is rejected |
| Committed unread output | Committed capture remains eligible | Committed snapshot remains eligible without draining |
| Stopped session with runtime retained | Quiescent current evidence may be eligible | Same owner/interval checks still apply |
| Drop/rebuild/foreign identical plan | Released/foreign old capture is not current | Old immutable result readable only as historical/as-of evidence |

Test native `statistics_freshness` for current/stale/foreign/future/layer
distinctions where the existing public/testing contract supports construction.
Do not add public stamp setters solely to test negative cases. For workload,
compare reset, configuration, segment, start/end epoch, options, and modes
independently; equality of one field is not sufficient. Confirm previous cells
and replaced-history fields never enter any computed score.

## Build and execution plan

Future root validation should cover the repository's established strict
production and matching testing macro variants, the complete relevant
sanitizer closure, and clean source-only builds. A pure ranking consumer must
link without runtime or explain objects; the actual-owner bridge must link
without report objects. Testing consumers must use only the matching testing
runtime archive. Keep assertions active in optimized tests. Retain all C01 and
older tests and verify the discovered CTest list against an explicit expected
list after registration.

Run the smallest meaningful ranking/adapter/exception tests first; then run
the required native matrix once frozen. Record failure and retry provenance.
No cost-calibration benchmark is needed to prove the deterministic baseline
arithmetic. Claims about speed, regret, total bytes, or runtime-optimal choice
require their own C03/C07/S05 evidence and must not be inferred from these tests.

This author performed source inspection and file-integrity checks only. No
test, checker, executable, benchmark, CMake, CTest, or `nm` was run for C02.
