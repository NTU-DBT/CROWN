# B02 local query/trace corpus checkpoint

The local generated corpus and pinned CROWN source inventory are verified at
this checkpoint. B02 remains in progress: [Refactor.md](../../Refactor.md)
Section14.2 also calls for broader source-grounded workload imports and
classification. Full goal status remains47 verified, A02/B02 in progress,
29 not started;78 total. The working tree is uncommitted on baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`; no release is claimed.

The [workload guide](../workloads.md) and
[manifest](../../benchmarks/workloads/manifest.json) describe24 generated SQL
definitions/144 trace cases. Twenty admitted families have140 runnable cases;
four cyclic/non-free-connex/bag/aggregate controls are explicitly rejected.
Independent assignment joins and SQLite agree on all2507 physical events,
including the controls' finite reference outputs. Admitted cases contain2486
events. Four backend/mode combinations check9944 actual committed epochs per
compiler configuration.

The seven regimes include charged loading/deletion, insertion-only, global and
per-relation FIFO, mixed updates, churn/no-ops and input-mix changes. Every
case references semantics, ordered head/output expressions, occurrence scopes,
expected backend/admission and output mode, update/source/no-op contracts,
licenses and SHA-256-bound SQL/catalog/events/oracles. The schema is closed;
regeneration, reference binding, invalid metadata and FIFO violations are checked.
Selected families also exercise a separate seed/data-size parameter.

Native controls each pass560 replays/644 commands/9944 epochs in GCC Debug,
GCC Release, Clang18 Debug and ASan+UBSan/leaks Debug. Root compiled the new
generic exporter with strict C++23 warnings/errors and enabled test checks,
then linked the exact sealed predecessor production archives. Every actual
signed delta, current result and source/epoch is compared with the independent
oracle on reference/indexed storage and delta/maintenance modes. Full snapshots
are taken for correctness in both modes; these are not timing experiments.

Fresh source-only GCC Release uses exactly1621 input paths and no existing
objects/cache. All9 selected tests have passing evidence: workload manifest/
replay, workflow/install, schema/admission/reference-fuzz and C03/C02 regression
checks. The first invocation passed8/9 in13.52s; installation found root's build
target list had omitted libcrown_selection.a. Building crown_selection_runtime
completed the required package closure, then only the failed install check
reran and passed in9.78s. Raw failure and success records remain. No source,
assertion, option, cap or timeout was weakened. The initial driver retains exit8
and is terminal; repair jobs separately record exit0.

All274 earlier generated test commands/properties are unchanged after path and
backtrace normalization;276 tests are registered. This is selected acceptance,
not a full276-test release run. The audit checks126 fresh compiled C++ units,
five fresh native ELFs,16 CROWN archives (15 production plus the CLI reference
library), parser archive, flags/links/configuration and four controls' linked
archives/raw reports. It pins3320 actual artifacts. Existing runtime code and
tests are unchanged from the [C03 checkpoint](c03-maintenance-cost-acceptance-2026-11-10.md).
Only previously reviewed pinned upstream C/Make warnings appear. The reference
library retains its production flags; executable test checks remain enabled.

The [legacy inventory](../../benchmarks/legacy/manifest.json) classifies all116
scenarios/13 distinct labels across five local specs. Root checked122 local
fingerprints and120 Git blobs against the CROWN pin. Backend head/predicate/
bag/window/aggregate differences and missing dataset/license/trace contracts
remain explicit. Root corrected two stale proposal claims about native SQL
execution. No original benchmark name is attached to a simplified synthetic
query or an unverified timing. Luna Max supplied this bounded inventory; root
implemented/reviewed the generator, schema, verifier, exporter and acceptance.
No Astra was used.

Records under `build/verification/` use prefix `b02-workload-`: predecessor
preimages, development/final manifests, exact fresh copy, four native controls,
phase receipts/archived stdout, `checkpoint-audit-v2.json`, documentation
successor and local seal. All build/test jobs are closed. The audit helper's
first assertion incorrectly treated the production reference library as a test
executable; it was corrected to check executable test flags. Runtime and test
source were unchanged. Original metadata descriptors are preserved before
registry/distribution-label integration; all336 case files and exporter source
are byte-identical across those controls and the fresh build.

Next complete broader imported-source classification and the B02 requirements.
Root fetched pinned DynaGox Queries.md and verified its exact Git blob/SHA-256;
all24 original statements pass syntax parsing. Their aggregate outputs are
preserved; parsing is not native admission or execution. Real input bytes,
licenses, transformations, update contracts and output modes need explicit
records before benchmark use. B03 controlled measurement, A02 licensing and
the remaining cards/release gates stay open. Finite corpus correctness does
not establish all-free-connex coverage, held-out cost accuracy or performance.
