# CROWN continuation handoff — V66 exact top-k and full-scope review

The Refactor implementation goal remains **ACTIVE**. Ledger state is
**70 verified / 1 in progress (A02) / 7 not started / 78 total**. X05 now has
separate exact snapshot top-k feature acceptance. V03/V04 retain their documented
internal R1/R2 qualification. The [exact V65 handoff](handoff-history-v65-2026-11-16.md)
preserves the predecessor review and source/test vintages; the
[V64 handoff](handoff-history-v64-2026-11-16.md) preserves accepted image details.

## Current implementation and inspection

Read the [top-k usage contract](topk.md),
[feature acceptance](verification/snapshot-topk-v66-2026-11-16.md) and
[current full-scope review](verification/full-scope-review-v66-2026-11-16.md).
The optional `CROWN::topk` library provides exact collect/sort selection over
`SqlRowsRuntime` and `SqlAggregateRuntime`. Requested output fields use explicit
direction and NULL placement, then complete query-scoped identity ASC NULLS FIRST.
Aggregates rank actual rendered outputs, including declared-scale AVG. Bags stay
compressed even at UINT64_MAX; omitted group keys retain result identity.

Each call uses one producer grant and a separate finite sort/selection balance,
with storage on the original account. `k=0` validates readiness/order but opens no
producer and allocates no candidate/result storage. Private vectors and existing
leases provide failure cleanup. Full collection and sort costs are explicit;
selected output retains compact capacity. There is no cached ranking, update
hook, new catch/retry layer or specialized P10 bound. SQL ORDER BY/LIMIT admission
is still separate.

All 863 maintained code/configuration paths have explicit source inventory:
474 primary paths, including 391 production files, and 389 tests/helpers. All
389 previous production files preserve exact V65 bytes and reviewed semantics.
New production files are `include/crown/runtime/topk.hpp` and
`src/runtime/topk.cpp`; the three new tests are unit, genuine-native driver and
independent oracle. Existing CMake changes append the optional target/export/tests;
`tools/code_specs_support.py` adds only offline top-k documentation context.

Current maps cover 861 files / 194,204 lines / 21,538 regions: 18,320 nonblank
regions have scoped contracts, with 3,218 blank regions structurally described.
The 20,798-record registry SHA-256 is
`b4b3cd16bf88b8c4e11beae47cd79dd19a424101f50813ca70412e2bc1db5c77`.
There are 117 new records, 1,732 existing rebindings and two explicit helper
semantic amendments; 18,949 unrelated records remain exact. An independent
receiver accepts all changed/new anchors and blocks before root adoption.
Generation and checking pass, including 151,828 generated local links.

## Actual validation and preserved evidence

Targeted Release and ASan/UBSan native checks pass. Each profile reports 50 unit
controls, 14,300 ranked snapshots across both storage backends and 2,480 SQLite
ordering crosschecks. Inputs, exact independent expectations and raw native
outputs remain under `build/verification/v66-topk-root-v1/*-tests-v2`.
The relocated installed SDK passes six held-out SQL frames. Independent receiving
checks the actual 417 compiler dependencies, all 15 linked archives and all 268
SDK files. Only the exact relocated SDK image is frozen; producer builds and
consumer/build staging remain reusable.

The independent design, oracle author, final contract and SDK packets are closed.
Initial setup/fixture failures remain retained and honestly classified. Source
hashes join current production to V65 full/targeted inspections. The separate
Astra monitor records fresh cross-component ranges and inherited scope. A fresh
every-line semantic review of all existing tests is not claimed.

Both current all-target builds and complete suites pass: **385 Release + 385
ASan/UBSan tests, zero failures or skips**. All 863 code/configuration paths,
build metadata and registrations remain unchanged across the accepted runs.
All prior 383 commands/properties are exact, with only topk/topk_oracle added.
The [closed full-regression receipt](../build/verification/v66-full-regression-v1/receiving.json)
records actual terminal results. Its 90-payload packet seal SHA-256 is
`10496ccbfbcdd738f6f4573246101ec43e9c95b74fbbc2898938f314a8ae3972`;
independent postseal checks find zero mismatches. Release JUnit retains all cases
with CTest's bound on verbose passed output; the original sanitizer CTest log
retains all 385 case names. Auxiliary discovery/history logs have separate labels.
Validation timings make no performance claim. Documentation updates are separate
from the pinned native source/configuration.
Historical V63 complete suites and V65 selected checks retain their actual vintages.

Original R1/R2 archives and accepted decisions are unchanged. The preserved R2
archive is `build/r2-release-v64-v1/candidate-v1/crown-next-0.1.0-r2.tar.gz`,
SHA-256 `a0b1a45bc4feb75d2f9c1387611e2dc67880bfd5f5bec6280bc9a87b1da27889`.
Its decision SHA is
`5fe6e934498eca2ec700b899120be7514f3bacb5c77ac68c15f36c43ed576779`.
Current review adds no accepted successor release image or external publication.
That archive predates top-k and retains its original cold aggregate resource-denial
category. Current source and SDK validation belong to the separate successor.

## Continuation

The V66 source snapshot is `build/verification/human-inspection-v66-source-v1`
(4,898 source paths). Final source/guide receiving and root closure are under
`build/verification/v66-topk-root-v1`. The successor progress and postseal are
`build/verification/human-inspection-v66-progress-v1.json` and
`build/verification/human-inspection-v66-postseal-v1.json`. Preserve those closed
records and the exact relocated SDK image; producer and consumer/build staging
remain reusable. Historical checkpoint notes retain their original pending state;
the final receiving and postseal records are authoritative.

Then follow literal X02/X03/X04/X06/X08 criteria and user priorities for the next
separately reviewed exact extension. Comparisons and difference may use ordinary
propagation or exact recomputation. Each query keeps independent serial state
and budgets. Approximation, shared-query optimization and parallel/distributed
execution remain deferred.

Keep implementation direct and costs explicit. Preserve source-bound specs with
each behavioral change; hash rebinding alone is not semantic review. Use disjoint
parallel readers and own-model reasoning; reserve Astra Max for occasional hard
audits and Luna Max for mechanical work. Git metadata is read-only. Set
PYTHONDONTWRITEBYTECODE=1; use the escalated shell path because default bwrap fails.
Closed evidence/frozen images are immutable; reusable producer builds are not
included by broad build globs.
