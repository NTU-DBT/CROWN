# Counter cancellation, histogram lookup and runtime/IO inspection

This continuation adds 335 contracts after v9, reaching 5,635 contracts in 5,017
mapped blocks across 691 maintained files / 159,119 lines / 17,774 blocks.
Another 1,185 selected production blocks need individual cards (482 include,
646 src, 57 apps). Test/tool/example gaps remain separate. Full Refactor work and
release review remain active; this is a scoped source and regression checkpoint.

Start with the [block index](../code_specs/README.md) and [primitive contracts](../code_specs/primitives.md).
New scopes cover ranking evidence, statistics collection/reoptimization,
batch/residual/cursor IO, runtime observation/statistics/memory reports, the
private candidate header and the new regression/build boundary. Every meaningful
assigned region has an individual card. Mutable labels/DTOs and model forecasts
remain distinct from typed proof, native-source and durable authority.

## Reproduced counter lifecycle defect

At clock_reads==UINT64_MAX, State::time cancels the private candidate and clears
its target/ledger. Staging previously continued allocating afterward; verification
could dereference the cleared target. A real-State regression first fails with
"cancelled clock continued allocating candidate work". It constructs a checked
candidate through actual P06/P07 factories and a nonempty old runtime, then seeds
only the private diagnostic counter in the internal test build.

The fix adds one activity check immediately after time in stage and verify.
Both cases now stop before candidate work, preserve terminal counter status and
account successful-allocation count, retain old rows/owner/epoch and permit the
old owner's next input. Test source uses no fabricated target/proof or mock
equivalence outcome. The test friend adds no production field, public API or ABI.
The test does not measure every global allocator attempt.

Root also traced all other callers: advance skips a cleared head; elapsed uses
stable State/status fields; publication obtains its target through the checked
accessor and skips publication after preparation failure; the old-owner drain
can continue its own admitted quantum without reading the cancelled target.
The [ranking review](../../build/verification/ranking-reoptimization-human-review-v1/report.md),
root caller trace and failed/current receipts retain this causal proof. Existing
diagnostic/durable handlers remain; no recovery wrapper is added.

## Simpler histogram lookup with actual budget debits

The standalone diagnostic already sorts groups by descending multiplicity.
Equal counts are contiguous, so only the last histogram bin can match the next
group. One last-bin test replaces the repeated full-bin search, without a new
container, cache or helper layer. Empty histogram spends no lookup debit;
nonempty lookup spends one work unit. Fewer actual probes can make a capture
complete within the same allowance where the previous search exhausted it.

Repeated reserve and cumulative modeled H² growth remain, along with sorting,
grouping, payload and top-K costs. This is not an overall linear or timing claim.
The [observation/memory review](../../build/verification/runtime-observation-memory-human-review-v1/report.md)
retains a Python Counter comparison over 6,435 sorted-count cases and the
1,000-distinct-count lookup observation (499,500 versus 999 probes). Current
native capture/exhaustion/scalar/combined/report tests verify the actual C++ path.

## Contracts made inspectable

| Boundary | Actual behavior/cost |
| --- | --- |
| Ranking/equivalence | Same-source data and typed original evidence are distinct from metadata keys and cost estimates. Full scans, ordered result retention, replay and dual-state peaks remain explicit. |
| Observation | Hot hooks use preallocated state; trace/capture export and memory attribution scans are explicit diagnostics. Sequence sampling and outer/nested attempt bindings do not measure all CPU. |
| Memory reports | Ledger sorting/per-owner scans can cost O(U*A). A fixed nonallocating report instant is distinct from the allocating complete report. |
| Typed queue | Funded graph admission preserves caller data on full/OOM. Private replay may retain its imported head if later peek fails; accepted progress stays old and failed restoration discards that owner. |
| Residual/cursor IO | Residual JSON DOM export has no final byte/item cap and constructs/copies full binding/query data. Capped cursor/gauge DTO encoders describe caller data; they do not authenticate it. |

See the [batch/residual/cursor review](../../build/verification/batch-residual-cursor-io-human-review-v1/report.md).
The vendored JSON bad_alloc cleanup repair already exists and remains pinned.
Root also qualifies all forty native IR-view cards: integer/Boolean/date/inline
decimal ScalarView alternatives are inline; only text borrows bytes. Native
headers are unchanged by that documentation correction.

Paper versions/local proof links remain in [the review guide](../code_review.md).
C++ ownership, counters, codec/resource behavior and process/durable boundaries
are local contracts, not additional paper theorems.

## Verification and preservation

Both strict 30-target builds pass. Debug passes 30/30 in 71.38 s; ASan/UBSan/leaks
passes the same 30 in 103.22 s, on identical 1,128 maintained input pins with no
drift. Cohort includes the new counter case, normal candidate/rebuild/policy/
installation/recovery/resource/generation paths, capture/owner/combined/scalar
statistics, observation/cursor reports, queue/residual IO and cost-owner controls.
No full 324-test or release/compiler matrix is claimed.

All 323 earlier test definitions remain, with one appended regression. The
[registration audit](../../build/verification/inspection-counter-registration-v1/README.md)
checks exact source prefixes, all SAN323 command/property/backtrace records and
the W04 Debug319 prefix. The new test keeps assertions, the testing macro,
strict C++23 and explicit sanitizer environment. Root rechecks all 92 old CMake
contract commands byte for byte before rebasing their file hashes.

Final receipts: `build/verification/inspection-counter-{build,test}-{debug,sanitizer}-v1.json`.
Raw terminal LastTest logs are archived. The missing-target-before-configure,
test API spelling correction, expected pre-fix failure and failed private
integration attempt remain with exact source/preimage evidence. Current gates
pass; documentation checks reconcile hashes/anchors/attachments/references.

Seal: `build/verification/human-inspection-v10-progress-v1.json`; frozen source:
`build/verification/human-inspection-v10-source-v1`. Root recipes/proofs/native
inventory are in `build/verification/inspection-counter-v1`. Earlier seals remain
immutable, and main build paths remain active/reusable after preservation.

CLI, observation/cost-header and recovery-codec/retirement drafts remain outside
these counts. CLI output/diagnostic failures are reproduced separately against
the unchanged v9 CLI binary and await their own fix/verification. The full
individual human review and W06 work remain open.
