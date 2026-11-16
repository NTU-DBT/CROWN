# V66 full-scope correctness review

The current maintained inventory has 863 code/configuration paths: 474 primary
paths, including 391 production files, and 389 test/helper paths. All 389 existing
production files retain their exact [V65 reviewed](full-scope-review-v65-2026-11-16.md)
bytes. The two new production files implement exact snapshot top-k. The
[current inventory](../../build/verification/v66-topk-root-v1/source-inventory-v66-v1.json)
records every path and source hash, with no missing predecessor paths.

## Review scope and correctness arguments

V65's full or targeted semantic inspection covers the unchanged primary code,
including its aggregate recovery diagnostic correction. The V66 implementation,
tests, appended build metadata and offline documentation context receive separate
source inspection and contracts. This preserves actual per-file depth: a fresh
every-line semantic reread of all existing tests is not claimed.

The [Astra monitor](../../build/verification/v66-full-scope-monitor-v1/README.md)
freshly inspects 26 production paths, including both complete new files, and
checks high-risk cross-component paths. Its exact source ranges,
hashes and fresh/inherited distinctions remain in that packet. The monitor
examines producer leases and retained tuple/account ownership, exact aggregate
rendering and group identity, weighted support boundaries, source net-batch
constraints and durable row/aggregate publication/replay. Executed tests have
separate receipts; static inspection is not relabeled as execution.

No confirmed runtime defect or actionable simplification was found. A stale
specification-map observation is closed after reviewed contract adoption,
regeneration and independent rehash of all 861 mapped sources.

The [top-k acceptance](snapshot-topk-v66-2026-11-16.md) checks all eight literal
X05 readiness rows. The operator uses current exact outputs, complete identity
tie-breaking and compressed bag selection. NULL placement is independent of
direction; aggregate rounding precedes ranking. Finite producer and sort grants
retain the original account. Private temporary vectors and existing leases
provide cleanup without adding a catch/retry layer, transaction protocol or
ordinary query-update hook. Full collection/sort costs and retained output
capacity are explicit in the [usage contract](../topk.md).

Existing rollback and uncertain-I/O handling remain at their owning boundaries;
the [error-handling dispositions](../code_specs/error_handling.md) explain their
purpose. No simplification is made by removing a required consistency boundary.
The [paper/design map](../code_review.md) separates exact paper context from local
compiler, allocator, snapshot-sort and durability arguments. No specialized P10
bound, theorem, hardware power-loss result or performance improvement follows
from this review.

## Source-bound human inspection

The regenerated maps cover 861 files, 194,204 lines and 21,538 regions. All 18,320
nonblank regions have scoped usage contracts; 3,218 blank regions retain their
structural descriptions. The registry has 20,798 records, SHA-256
`b4b3cd16bf88b8c4e11beae47cd79dd19a424101f50813ca70412e2bc1db5c77`.
The checker resolves 151,828 generated local links with zero errors.

There are 117 new contracts and 1,732 existing source/anchor rebindings. Two
existing helper contracts amend documentation-routing semantics; all 18,949
unrelated records retain exact identity. The original CMake body is an exact
prefix. Removing only the top-k context, two role labels and routing branch from
the offline helper restores the exact predecessor AST. These are source-lineage
checks, not substitutes for semantic inspection.

The [final independent receiver](../../build/verification/v66-topk-final-independent-v1/receiving.json)
checks all current contract fields/source hashes, all 1,849 new/rebound anchors,
526 distinct changed/new references and all 1,738 nonblank regions in the seven
changed/new code paths. It finds zero coverage gaps or correctness blockers.
The root subsequently adopts those exact candidate bytes and regenerates/checks
the [inspection index](../code_specs/README.md).

## Actual validation and source vintages

The [registration comparison](../../build/verification/v66-full-regression-v1/registration-comparison.json)
receives all 383 prior commands and properties unchanged in both profiles,
ignoring only CTest backtrace metadata. The two added names are `topk` and
`topk_oracle`. Both current complete builds pass. The
[Release suite](../../build/verification/v66-full-regression-v1/release-suite-v2/receiving.json)
and [ASan/UBSan suite](../../build/verification/v66-full-regression-v1/sanitizer-suite-v2/receiving.json)
each pass all 385 tests: **770 executed, zero failures or skips**, with no
source/configuration, build-metadata or registration changes. All 863 current
code/configuration hashes match every accepted stage and the final live source.
The [closed regression packet](../../build/verification/v66-full-regression-v1/receiving.json)
contains 90 sealed payloads; its postseal receives zero mismatches. Release JUnit
retains every case/result with CTest's default bound on verbose passed output;
the original sanitizer CTest log retains all 385 exact names. Auxiliary discovery/
history logs have separate labels. Initial build cancellations merely restart
the same source at higher build concurrency and retain their terminal records.

Targeted Release and ASan/UBSan checks already pass for the new operator. Each
profile reports 50 unit controls, 14,300 ranked snapshots on both storage backends
and 2,480 SQLite ordering crosschecks. The independently received relocated SDK
matches six held-out SQL frames, actual compiler dependencies and all 15 linked
archives. Initial setup/fixture failures and their corrections remain explicit
in the feature acceptance record.

Historical V63 complete suites and V65 independent SQL, integer/Fraction, window
and recovery-fix checks retain their original source vintages. The original
accepted R1/R2 archives remain immutable; current source validation does not
rename an old archive or accept a new release image.
The preserved R2 image predates top-k and retains the cold failure-category
behavior documented in V65; the current source includes the received correction.
The overall implementation goal remains active; X05 has separate feature acceptance,
with 70 verified tasks, one in progress and seven not started. Approximation, shared-query optimization
and parallel/distributed execution remain deferred. Each query remains an
independent serial owner.
