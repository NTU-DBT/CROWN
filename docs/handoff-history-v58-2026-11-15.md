# CROWN continuation handoff — V58

The full Refactor implementation goal remains ACTIVE. The added full-scope
correctness review is complete for the implemented scope:
[review report](verification/full-scope-review-v58-2026-11-15.md).
B04 remains IN PROGRESS. Ledger: 63 verified, two in progress (A02/B04),
13 not started, 78 total. Release gates remain open. Licensing checks remain
deferred; preserve notices and rights.

## Current evidence

Parent seal: build/verification/human-inspection-v57-progress-v1.json,
SHA256 7a09a6a2ea9f33bed3d1d918d561079da5e2622eda251229355b609a741805b0.
The exact parent handoff is [preserved](handoff-history-v57-2026-11-15.md).
V58 entry verified 4,718 source pairs, 114,154 protected artifacts, 55,777
external pins and 4,701 private baseline files. Entry integrity:
279e77312e4251316ab0357718d6ed6ebec667ed65b08e3f09f94ddca0733eac.
component-evaluation-v58-v1/entry-receiving-v58-v1.json discloses the premature
initial entry report and its terminal process-check addendum.

Root receiving packet: build/verification/full-scope-review-v58-v1.
All 362 existing checks pass in each Debug and ASan/UBSan profile: 361 main
checks plus the separately coordinated clean_source_snapshot. Terminal
debug-tests-v1.json and sanitizer-tests-v1.json report exit zero and no changed
baseline input. All 1,239 pre-existing inputs matched V57 while those suites ran.
Their source hold is released; no full-suite job remains running. Do not
repeat the costly full suites for these already received changes.

Fresh complete source review closes all 433 primary paths, including all 370
production files. Domain packets: v58-frontend-planner-source-review-v1,
v58-runtime-source-review-v1, v58-io-recovery-source-review-v1,
v58-tooling-source-review-v1, v58-root-storage-resource-review-v1 and
v58-storage-header-review-v1. One Astra Max monitor actually read 17 successor/
new files; all six inherited tool reads have exact spans and pins.
v58-full-source-closure-v1 joins the predecessor inventory with no missing or
unread primary path. Final receiving covers five subsequent source successors.

Two new aggregate-adapter defects were corrected: omitted/empty default options
now select PhysicalOptions{}, and COUNT-source verification now uses the
compiler's source_output/group/field coordinate mapping. Repeated GROUP BY
columns exposed the latter bug. Final aggregate.cpp SHA256:
034720303a4009d95ef6fa4989751930cc0dd9fb7d52d4f808c13384f789754e.
The measurement branch is unchanged; no runtime row ledger or catch layer added.
The old monitor's inference that complete input grouping implies identical
external key coordinates is superseded by the actual counterexample.

Final regression: 48 native commands / 336 SQLite prefix comparisons, including
24 ASan/UBSan commands. Scaled preflight: 32 configurations / 1,952 prefix
comparisons across six cohorts, plus 30 corrected duplicate-group prefixes.
Earlier ten-wrapper/199-prefix, nine minimum-candidate, ten adapter-negative,
three provenance-negative, eight repeated-owner and native/exporter sanitizer
checks remain bounded smoke evidence. No controlled performance claim.

Both offline code-spec tools explicitly inventory ComponentReplay.scala, with
positive/exclusion/missing-map regression. Two public storage-header changes
only document exact grant identity and rollback invalidation; predecessor
noncomment code bytes are identical. All 91 new usage cards are adopted from
v58-b04-design-review-v1 and v58-b04-adapter-spec-proposal-v3. Ninety-four
existing cards are rebound, with six semantic amendments. Final maps:
794 files / 180,992 lines / 20,190 regions / 17,226 nonblank regions /
19,670 cards. The actual checker passes all 143,145 local links.

## Resume B04 implementation

Keep the complete Refactor14.1–14.4 ten-axis matrix: storage, generic/specialized
runtime, ordinary/generalized structure, height/weighted-depth/event-cost,
exact/residual/meta search, statistics, output, batching, recovery and SQL
set/bag/aggregate semantics. The new six maintained source paths are still
unregistered experimental adapters, not accepted B04 integration:

- examples/component-planning/{main.cpp,CMakeLists.txt}: real exact/residual/meta
  export, ordinary controls, frozen calibration and statistics variants.
- examples/component-runtime/{component_request.hpp,aggregate.cpp,legacy_cpp.cpp}:
  actual native/legacy replay adapters and explicit verification/measurement.
- tools/support/ComponentReplay.scala: actual baseline process and full iterator
  drain after every physical input.

Next implement the V3 upper-only artifact consumer in the B03 collector.
Its tag independently_checked_original_lower_actual_upper_v1 is currently
producer-only. Preserve independent original lower proof and actual upper-tree
checks. Existing minimum-only B03 replay already accepts all nine new minimum
candidates. C05 event-cost installation is unsupported; C03 forecast fitting
here is offline and needs honest selection receiving. Add the generic native
set-cardinality/session adapters and CMake/schema/cohort/runner integration,
then complete matched batching, output and recovery controls and all ten axes.
Never substitute COUNT(*) for line5cd COUNT DISTINCT.

Author packets v58-b04-design-review-v1, v58-b04-baseline-design-v1 and final
v58-b04-adapter-spec-proposal-v3 are immutable. v2 is retained as a predecessor.
The v58-b04-cohort-draft-v1 packet retains six SQLite-oracle cohorts; scaled
preflight verifies actual controls but does not accept the experimental matrix.
Its final native Release binary SHA256 is
25dfc2dce20e0243e41889a222734920aa3ae3c41a8cb6f42965c40ec1a31311.

## Workspaces and constraints

New builds/SDK/classes/home/tmp/output belong in new children under
build/component-evaluation-v58-v1. Current reviewed binaries are in
planning-review, planning-review-sanitizer, runtime-review and
runtime-review-sanitizer; Scala classes are in scala-review-classes.
Those reviewed binaries, both review-sdk trees and Scala helper classes are
frozen by the V58 progress seal; future builds must use new directories.
Existing main mutable builds are build/w05-debug, build/w05-sanitizer and
build/inspection-build-scope-off-v1. Coordinate source and performance holds
before any further measurements.

The whole build/legacy-baselines-v57-v1 prefix, old evidence, frozen sources,
private SDKs and dependencies remain immutable. Link the exact sealed C++
archives and Scala classes/JARs. C++ concrete owners avoid the baseline's
nonvirtual base destructor. Legacy GC emits absolute counts (including zero);
CD is insert-only. Preserve the original Scala parser-test failure.
Old baseline archives are not sanitized. Logical-owner passes retain process,
JIT and allocator state. Intrinsic parser/formatter/framework costs are included
where charged; cross-framework clocks do not isolate generic dispatch.

.git is read-only: never stage/reset/commit. All exec_command calls require
require_escalated; Python uses PYTHONDONTWRITEBYTECODE=1. Keep core code direct
with necessary ownership/rollback boundaries only. Maintain exact seven-field
cards for every nonblank region and regenerate/check maps after source changes.
Use parallel workhorses and Luna Max for simple work, Astra Max sparingly.
Comparisons/top-k/difference may use ordinary propagation or exact recomputation.
Approximation/shared-query algorithms/parallel-distributed engine execution
remain deferred; maintain queries independently behind the existing interface.
