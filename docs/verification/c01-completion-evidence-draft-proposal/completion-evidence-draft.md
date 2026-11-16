# C01 statistics — native integration evidence (draft)

**Draft evidence only. C01 is in progress and is not verified.** The C01
implementation is integrated in native sources and frozen for its acceptance
matrix. Four native configurations have passed all 131 tests. The fifth,
ASan/UBSan/leak run in session `63700`, is still active. Do not treat this draft,
the earlier isolated results, or a preliminary audit as final C01 acceptance.
The matrix status snapshot included with this draft records the four terminal
passes and the still-active sanitizer as of the snapshot time. Root must refresh
mutable status when preparing the final packet.
The links below resolve from this excluded draft directory. Before copying this
body to `docs/verification/statistics-2026-11-07.md`, rebase its repository links
from `../../../` to `../../`; change the local status-snapshot link to
`c01-completion-evidence-draft-proposal/matrix-status-as-read-2026-11-07.json`
or copy that snapshot beside the final record.

## Current native matrix

| Configuration | Result | Test time | Root record |
| --- | --- | ---: | --- |
| GCC Debug | 131/131 passed | 1493.12 s | [summary](../../../build/verification/statistics-debug-summary.json) |
| GCC Release | 131/131 passed | 274.90 s | [summary](../../../build/verification/statistics-release-summary.json) |
| Clang Debug | 131/131 passed | 1207.95 s | [summary](../../../build/verification/statistics-clang-summary.json) |
| Fresh source-only Release | 131/131 passed | 276.48 s | [summary](../../../build/verification/statistics-clean-source-summary.json) |
| ASan + UBSan + leak checking | **Pending:** session `63700` was running in the preserved status snapshot; terminal test result not recorded there | Pending | [as-of matrix status](matrix-status-as-read-2026-11-07.json) |

The execution freeze pins 131 named tests and records 195 compile-command
entries. Its native source inventory is 623 files with SHA-256
`25f7143860cf28f6c7ba0e89a5b40708d3fb71fec979408bf1135f0fa45b1ef0`; the
execution-input inventory is 676 files with SHA-256
`70916b45f3105b21d281f49c12c0455c9de8f3b2d76daa74bf252f2bb2144f4d`. The
freeze binds the input inventories; the separate matrix jobs record and the
four immutable summaries report four terminal passes and one active sanitizer
row. The as-of jobs snapshot is preserved in this proposal directory. The earlier
691-entry O07 seal is historical pre-integration evidence; its old entry list
must not be rechecked against this C01 source tree.

The 131-test registration preserves the 99 previous tests and adds 32 C01
tests. It separates production and `CROWN_RUNTIME_TESTING` consumers and keeps
runtime libraries independent of report/observability objects. The guarded
native integration start record documents the pre-application O07 baseline,
the 62 mapped destinations, and the accepted publication candidate. That
publication preflight passed its format, legacy, and allocation checks before
native application; it is not a substitute for the current full matrix.

## What the accepted C01 evidence covers

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

## Remaining closure fields — root only

The preliminary source audit attempt 3 reports zero errors, but explicitly
leaves full matrix acceptance and the final metadata transition pending. It is
not the final source audit. Independent matrix evidence audit attempt 1 and its
launch preflight are retained historical failures. Root accepted the revised
auditor for this frozen evidence under
[the audit authority](../../../build/verification/statistics-matrix-audit-authority.json).
[Audit attempt 2](../../../build/verification/statistics-matrix-evidence-audit-attempt-2.json)
reports zero errors and allocation differences while auditing Debug, Release,
Clang, and clean-source: 1,047 observed numeric rows per configuration, 195
compile entries, six archive roles, and cross-configuration comparisons. Its
overall matrix acceptance remains false because sanitizer evidence and semantic
symbol gates are pending. This partial audit does not complete C01.

| Final evidence field | Required root entry |
| --- | --- |
| Sanitizer session `63700` terminal result | **PENDING ROOT** — record result, duration, exit status, and final input identity. |
| Final matrix acceptance | **PENDING ROOT** — close only after all five configurations and exact test inventory are reconciled. |
| Independent matrix evidence audit | **PARTIAL, FINAL PENDING ROOT** — attempt 2 audited four configurations; record sanitizer and semantic-symbol closure plus final disposition. |
| Final source/schema/documentation audit | **PENDING ROOT** — include its terminal report and findings. |
| Official 733-source seal SHA-256 | **PENDING ROOT FILL** — do not copy the preliminary inventory candidate as the final seal. |
| C01 metadata transition | **PENDING ROOT** — reconcile status only after terminal matrix and audit evidence. |

Until those entries are filled and accepted together, C01 remains `in_progress`,
not verified. C02 ranking and C03 maintenance-cost modeling are not implemented
by this evidence. S05 total/peak allocator memory is not established. The C01
component accounts disclosed payload only; there is no C02, C03, or S05
acceptance claim here.
