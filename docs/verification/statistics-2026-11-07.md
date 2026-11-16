# C01 bounded statistics — verified

**C01 is verified.** All 131 native tests pass in all five configurations on one
frozen execution revision. The full goal remains active: **38 verified, two in
progress (A02/O06), 38 not started, 78 total**. No release gate is claimed.

| Configuration | Tests | CTest seconds |
| --- | --- | ---: |
| GCC Debug | 131/131 | 1493.12 |
| GCC Release | 131/131 | 274.90 |
| ASan + UBSan + leak checking | 131/131 | 6245.75 |
| Clang Debug | 131/131 | 1207.95 |
| Fresh source-only Release | 131/131 | 276.48 |

The registration preserves all 99 previous tests and adds 32 C01 cases. Runtime
and report production/testing closures remain separate; runtime-only consumers
link without report objects. The clean snapshot matches the native/execution
freeze and its temporary tree has been removed. All native sessions are closed.

Native623 fingerprint: `25f7143860cf28f6c7ba0e89a5b40708d3fb71fec979408bf1135f0fa45b1ef0`.
Execution676 fingerprint: `70916b45f3105b21d281f49c12c0455c9de8f3b2d76daa74bf252f2bb2144f4d`.
The [freeze](../../build/verification/statistics-execution-freeze.json) retains
all file maps and before/after identities.

## Accepted state, workload and report scope


Owner-state capture reads selected actual populations from an initialized
owner: physical source rows (including unused catalog tables), native
occurrence derivations, native or generalized node records and S/P/E support,
and already-admitted index degrees. A successful exact distribution describes
that selected local population; it is not the global query answer count.
Unknown, budget-exhausted, pending, unavailable, and not-applicable facts remain
distinct. Owner freshness uses the actual owner, layer, and committed sequence;
storage revision is separate invalidation evidence.

Transactional workload collection starts off or uses bounded counters. The
physical input census records committed input, changed, and no-op counts by
physical table and operation, independent of detailed sampling. Census (`period
1`) selects every attempt for detail; larger periods use the deterministic
attempt ordinal and are reported as sampled, without population extrapolation.
Detailed-event means use completed, selected, untruncated input denominators
from the matching table/operation stratum. Selected no-ops count in those
denominators; aborts and truncated attempts do not. Saturated raw counts remain
lower bounds, and ratios using clipped counters are unavailable. C01 reads no
clocks; arrival-per-second remains unavailable. O07 observation settings are
independent, and O07's default-timed mode may still read O07 clocks.

The v3 statistics report captures actual owner, plan, modes, and separate state
and workload interval domains in an immutable value. Unrequested state is
`not_requested`, not zero. Unknown and incomplete values have explicit nulls
and reasons; the report adds no proof authority or silent whole-state scan.
With C01 off, the prior EXPLAIN v2 output remains byte-compatible; the legacy
full-report path rejects enabled C01 rather than silently omitting it.

Root preparation packets add independent literal state/event references,
typed scalar and constraint cases, selected FIFO/LIFO policy/window cases,
and targeted report schema/semantic checks. They strengthen the native tests,
but remain scoped suites rather than an exhaustive option Cartesian product.
The combined and report independent reviews found no blocking defect in the
reviewed scopes; both reserve final acceptance to root. Report coverage remains
bounded: legacy byte comparisons cover one runtime and one session fixture;
the report producer uses only O07 off/counters; timed/trace combinations,
complete lifecycle/reset combinations, exhaustive Decimal JSON boundaries,
and all allocator paths are not established by that review. The accepted
publication wrapper/schema checks also reject reintroducing the removed
`c01_project_gate` field; this field guard is not a C01 completion claim. Review
limits and historical scope remain in the pinned source documents.

## Measured collection cost and scope

The standalone component benchmark replays 50,000 synthetic events. Its median
times were 2.062 ms with no instrumentation calls, 2.341 ms with off-collector
calls, 31.863 ms for census counters, and 19.956 ms for period-64 sampled
counters. These are collector-component measurements, not engine throughput.

The actual-engine benchmark used 5,000 prebuilt events, two warmups, and nine
measured repetitions with fresh production owners. Median stream times were:

| Actual path | C01 off | Census | Period 64, offset 0 |
| --- | ---: | ---: | ---: |
| Physical apply | 26.488 ms | 54.699 ms | 43.542 ms |
| Delta maintenance | 36.288 ms | 64.639 ms | 53.900 ms |

These are substantial measured costs for the stated synthetic trace. C01
sampling reduces detailed collection work while still paying guard, physical
census, and scratch/merge costs. The timer excludes input construction,
initialization, plan lowering, configuration, capture/export, sinks, and other
maintenance/output policies. Delta measures maintenance with pull-draining,
not signed output delivery. The off profile is the integrated candidate's
disabled collector path, not a build without C01; it establishes no zero-off-
overhead claim. Raw timings, dispersion, owner profiles, and root records are
preserved in the accepted benchmark packet.

The engine benchmark reports 126,608 bytes of descriptor/route/slab vector
capacity plus a 624-byte State object when enabled; off retains zero of those
vector capacities but the same State object. These are component capacity
figures, not total or peak allocator memory. Neither benchmark sets a
performance threshold, predicts production behavior, estimates arrival rate,
or supplies a cost model.

## Preserved failures and oracle corrections

The accepted evidence keeps the failed attempts and explains each correction:

- The collector's first strict build caught a signed `bit_width` array index.
  The accepted warning-only revision adds the safe `size_t` conversion; the
  header, assertions, and numerical expectations remain unchanged.
- The first generalized owner fixture assumed hidden `x` made R outside C*.
  Verifier/lowerer geometry showed the `{y}` separator crosses C*, so the
  present E populations were retained and checked; adding T under R supplied
  the intended hidden `{x}` separator case. Counts and collector behavior were
  not weakened.
- Literal-reference attempts preserved a JSON syntax repair, an omitted
  explicit no-op crossing expectation, and a missing existing-index key
  projection. The final packet carries explicit fixture metadata and unchanged
  numeric expectations.
- Policy/window revisions corrected an assumed session accessor and an
  incorrect extra-admission expectation. The accepted window case keeps the
  one root already opened by `begin_next_result()`.
- Report review resolved a runtime-to-observability dependency and changed a
  generalized pre-probe presence label so it is not confused with native
  reverse-index degree. No failing fixture was discarded.
- The first actual-engine benchmark stopped before timing because expected
  child P was incorrectly grouped from the global join answer. The corrected
  oracle groups local child survivors by the parent separator. A later
  preflight stopped before execution on one 63-character object digest; the
  separate metadata revision records the corrected digest and strict checksum
  parsing. Original sources, failed records, and packages remain preserved.


## Native execution and source closure

The [independent matrix audit](../../build/verification/statistics-matrix-evidence-audit.json)
accepts all five exact 131-name outcomes/commands, 1047 observed numeric rows per
configuration, 195 CMake compile entries, 14 runtime and six report units per
variant, compiler/warning/link boundaries and all six archive symbol roles.
There are no allocation differences or waivers. Sanitized parser C has both
ASan and UBSan references; its pinned recipe covers 96 C units. The clean build
retains exactly the historical jobserver note and two upb diagnostics; they
are not declared fixed or harmless, and no new project warning is accepted.

The first auditor attempt misclassified an existing non-signed trace row. Its
separate frozen revision keeps that row byte-exact, normalizes only the
source-supported signed-result order and CLI artifact-directory suffix, and
changes no test, numeric expectation or raw execution record. All failed
preflights/attempts and accepted precursor packages remain preserved as-of.

The [733-source seal](statistics-sources.sha256), SHA-256
`95eda9c8b4b6e631a9b85bc0d1c84315c1577aa0dbcb84801d570c9217ce070e`, is regenerated from current files after the two native guide
status updates. It is the old 691-path inventory plus 42 additions, with no
removals. Original Refactor.md and all ten historical manifest FILE identities
remain unchanged. Their old native entry checksums describe historical snapshots
and are never rechecked against this later source tree.

The final read-only source audit is recorded as
`build/verification/statistics-source-evidence-audit.json`. It verifies this
seal, final metadata, documentation/schema links, exact native/execution maps,
the reviewed auditor authority and every raw matrix-evidence pin. This completion
transaction is retained only when that audit accepts with no errors or pending
gates; otherwise its metadata is restored and the failed attempt is preserved.

The source-only checks complement executed native tests and independent reviews.
C02 ranking, C03 calibrated cost, S05 total/peak allocator memory, O04/O05 recovery,
O06 durable delivery and O08 public workflow remain separate. The full 78-card
goal remains active. See the [statistics guide](../statistics.md),
[native build guide](../native_build.md) and [handoff](../handoff.md).
