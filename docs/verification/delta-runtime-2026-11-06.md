# D04 eager-live delta runtime, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
**D04 and integrated R05 output acceptance are verified.** All 53 tests pass
the final five-build matrix. The full 78-card goal remains active: 26 verified,
five in progress and 47 not started. The [D03 packet](delta-spec-2026-11-06.md)
and its 467-input manifest describe the previous checkpoint.

Contract: [eager-live runtime](../delta_runtime.md), based on the
[D03 specification/proof](../delta_transition_spec.md).
API: [delta.hpp](../../include/crown/runtime/delta.hpp).
Implementation: [delta.cpp](../../src/runtime/delta.cpp), with private stage
hooks in support/physical runtime and allocation-free final plan teardown in
[lower.cpp](../../src/planner/lower.cpp).

## Requirement audit

| Acceptance | Evidence |
| --- | --- |
| Exact projected additions/deletions after each event | The maintained runtime's raw signed vector is compared to independent A04 before/after differences after 2,712 checked updates, including 2,504 exhaustive directed membership toggles. Set equality and raw cardinality both must match. |
| Correct physical alias cross terms and contexts | An occurrence-expanded A04 database checks each actual route's before/after answer and its spool interval. Loop insertion has 1+2 route outputs, deletion 2+1; same-scope aliases have 0+1 insertion. Filtered/count-only routes retain full physical prefix ordinals. |
| Actual E changes and canonical ownership | Changed keys come only from visible-role journal membership zero crossings. Root/child deletion produces one accepted and one rejected candidate. Hidden/payload collisions and positive derivation counts emit nothing. Diagnostic transition capture is disabled in the main oracle suite. |
| Live-view updates without answer bootstrap | E-factor scans and parent-L separator sets rebuild a private image. Every event's L sets are compared with A04 global-answer projections; route summaries also check exact live-row counts. Unchanged-root/deeper liveness, dead keys, shared separator support, disconnected/generalized products and nullary factors are covered. |
| Deletion journal retention and public D02 compatibility | Direct factor tests traverse pinned old E rows after erasure/commit, reject writes while leases exist, abort cursors before rollback and preserve whole-epoch `view(before)` semantics over multiple native stages. |
| Mapped SQL deltas | DISTINCT reordering/repetition/constants, different predicates and constant routes use whole-result SQL mapping as the oracle. EXISTS replacements are `-(false),+(true)` and `-(true),+(false)`. Typed date/decimal/string/Boolean repeated-head rows retain exact types and ownership. |
| Atomic source/count/support/L/output publication | Persistent bad_alloc sweeps cover 289 insertion, 227 erasure and 39 bootstrap allocation positions, with exact state/pin/sequence/L preservation and retry. A later-alias row quota and epoch-final EXISTS second-record quota fail without returning partial output. |
| Bounded output and explicit eager cost | Finite row/accounted-byte limits reject atomically; zero budgets accept empty output. Scanning one versus eight globally dead E rows for an empty delta costs 26 versus 89 abstract delta units. Bootstrap, cursor phases, changed keys, candidates/owners, L retention and spool usage are separate metrics. |

The exhaustive runtime cases cover exactly the D03 model's four families:
64 transitions for `Q(x):R(x,z)`, 384 for `Q(x):R(x),S(x,y)`, 2,048 for
`Q(x):R(x,z),S(z,y)`, and eight for Boolean unary R, all over `{0,1}`.
For each tuple position, exhaustive initial masks are XORed with the fixed
preceding toggles, a bijection of all states; every directed one-row toggle
therefore occurs once. Maintenance-mode seed loading is separate from these
2,504 checked toggles. Two 72-event seeded alias traces and manual fixtures
bring the checked total to 2,712, with 1,408 emitted records.

## Independent review and fixes

Luna Max authored the independent semantic/prefix suite and a separate
persistent-allocation suite. A third fresh-context, read-only Luna Max agent
reviewed the implementation against D03; the root authored production code,
factor/cost/type cases, dependency fix, integration and final verification.

| Finding | Disposition |
| --- | --- |
| A final facadeless output release destroys the last plan; nlohmann's canonical JSON destructor allocates a flattening stack. | Prepare a parent-before-child container pointer inventory during lowering and clear descendants first at final teardown. No-allocation final next/discard/artifact destruction and direct native/normalized plan destruction now pass. Partial inventory preparation has an allocation-free leaf-removal fallback. Frozen physical-plan content/work counters and vendored dependencies are unchanged. |
| Exported stage prefixes counted only native crossings, losing preceding filtered/count-only route ordinals. | The physical observer passes the full route ordinal. The oracle explicitly requires prefix 2 when occurrence 0 is filtered and occurrence 1 changes. Internal support checkpoint revisions remain separate from physical route identity. |
| Dropping committed output leaves a subscriber's external result copy incomplete. | Documented that discard/destruction leaves input committed and requires a fresh snapshot before resynchronizing a complete external copy. |

After these corrections the reviewer found no remaining D04 output-correctness
blocker by source inspection. The review did not run builds/tests and does
not replace external G2/V02 review or unsigned release gates.

## Verification

All 50 preceding tests remain alongside the three new D04 tests. Native
warnings remain errors:

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 53/53 pass | 74.03 s |
| GCC 13.3 Release | 53/53 pass | 9.41 s |
| ASan/UBSan including parser C | 53/53 pass | 341.36 s |
| Clang 18.1.3 C/C++ Debug | 53/53 pass | 56.10 s |
| Fresh source-only Release | 53/53 pass | 9.02 s |

Every final process handle is terminal/successful. The four in-place runs
share one unchanged before/after source fingerprint:
`bd612dde877571f88aa60ea0e80a9cabd6326fe2648863c14378621a003341e6`.
The clean configure/build/test took 275.38 s and removed its temporary tree.
Sanitizers include parser C, leak detection and halt on ASan/UBSan errors.
Targeted Debug preflight passed all three new tests in 7.01 s before this matrix.

The support CLI passes 25 checks/34 manual logical states under Python `-O`.
The optional schema audit passes 18 schema meta-checks, 26 normalized artifacts,
19 identity artifacts, 59 admission artifacts, two layout/projection artifacts,
31 physical artifacts, three support traces/reports and two rejected-update
reports. Frozen physical-plan v1, support-trace v1 and support-report v2 formats
remain unchanged; these CLI checks do not add a delta-stream command.

The [473-input manifest](delta-runtime-sources.sha256) covers all ordinary
contracts and prior source/build/test/dependency inputs plus the new runtime
API/source, three tests and runtime contract; all fingerprints pass. Verification
packets/manifests and mutable handoff/ledger are excluded. Logs and per-run
summaries use ignored `build/verification/delta-runtime-*` files. The aggregate
is `delta-runtime-summary.json`; `delta-runtime-oracle.log`,
`delta-runtime-exceptions.log` and `delta-runtime-factor.log` retain actual
final Debug CTest output and mandatory owner/failure/cost traces.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/support.py build/release/crown .
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/delta-runtime-clean-source.log
sha256sum -c docs/verification/delta-runtime-sources.sha256
```

## Scope and continuation

This is the labeled conservative D04 baseline allowed by Refactor.md. It
rebuilds L after each real native route and drains lazy completions into a
bounded private spool before publication. There is no full-answer difference
or historical-output deduplication relation in the production update path.
Standalone `PhysicalRuntime` remains the lower-level transaction API.

Finite spool bounds cover record/value slots and owned scalar payload, with
allocator/fixed-query costs, transient vector growth and cursor/mapping
scratch-row width stated separately.
Kernel state, L images and retained diagnostic journal pins have their own
space costs. A resource-limit rejection preserves the previous input; no
spill or durable delivery is inferred.

D05 still needs optimized lazy scheduling and justified first/result/last
bounds, including discovery/view/scan costs and value/comparison/allocation
accounting. D06/O06 still need the operational unpublished pause/drain and
sink/backpressure/recovery protocols. Existing committed-artifact delivery,
discard and mode barriers are foundations, not proof of those whole cards.
R06 initialization/rebuild, A02 provenance/license disposition, planner
partials and all other Refactor.md cards remain open as recorded in the ledger.
