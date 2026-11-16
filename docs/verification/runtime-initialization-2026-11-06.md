# R06 initialization, rebuild and inspection, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
R06 is implemented and verified. Independent source/contract review and all
four targeted suites pass. GCC Debug/Release, ASan/UBSan, Clang and fresh
source-only Release pass all 75 tests with stable native sources. The complete
78-card goal remains active: 31 verified, four in progress
(A02/P04/P06/O06), 43 not started. No recovery/release signoff is claimed.

Contract: [runtime initialization](../runtime_initialization.md).
Sources: [build types](../../include/crown/runtime/initialization.hpp),
[inspection types](../../include/crown/runtime/inspection.hpp),
[support](../../src/runtime/support.cpp), [physical](../../src/runtime/physical.cpp),
[delta](../../src/runtime/delta.cpp), [session](../../src/runtime/session.cpp)
and [diagnostic encoding](../../src/io/inspection.cpp).
The [O02 packet](session-lifecycle-2026-11-06.md) and its 500-input manifest
remain historical and have not been resealed.

## R06 requirement audit

| Obligation | Evidence and scope |
| --- | --- |
| Replay loader | Complete source rows and exact occurrence derivations are constructed in deterministic source/row/alias order; positive native seeds run actual private sequence-zero R04 transactions/queues. Each journal is released immediately. No public epochs or source positions are fabricated. |
| True bottom-up build | Direct records, iterative postorder, generalized child-P union, flags/satisfied counts/S and independent P/E counts use registered tables/indexes without propagation transactions/queues. Destination layout tokens are preserved. Constant routes retain their semantics. |
| Full snapshot constraints | The entire source Database is validated before unpublished construction, including unused tables, unique/FK constraints and valid cyclic FKs for which no public first insert is legal. Ordinary per-event constraints remain enabled. |
| Initialization/rebuild semantics | New initialization owns a nonempty sequence-zero state and first external event one. Rebuild returns a distinct owner preserving committed sequence/mode/options; failure leaves the original and its handles/readiness unchanged. Pending/read/unread-output barriers reject rebuild. |
| Live bootstrap | Actual E factors produce L and both live separator indexes/counts without answer-product materialization or output-spool dependence. Maintenance has no live image. Initialized session progress remains zero independently of its nonempty database. |
| Canonical dump/checker | Typed sorted logical source/alias/node/S/P/E/live/index state excludes owners/handles/history. Inspection reads actual maps/tables safely, checks missing/orphan metadata and independently derives counts/memberships. Real satisfied/P/E/derivation/live bucket/aggregate corruption is localized and restored. |
| State size | Component statistics reconcile arena live records and live/secondary memberships. Direct and replay N-by-N fixtures retain linear records at N=2/16/64 without enumerating answers; churn separates live records from high-water slots and retained history. |
| Failure and capacity behavior | Persistent constructor/replacement/session/writer sweeps, configured support/derivation/build limits, original-owner preservation, final-owner allocation-free cleanup and subsequent suffix checks pass. Build/inspection budgets charge repeated constraints and snapshot copying independently of normal update limits. |

## Independent acceptance and failure disposition

Luna Max authored [semantic/A04 cases](../../tests/unit/initialization_test.cpp),
[persistent failures](../../tests/unit/initialization_exception_test.cpp),
[actual corruption](../../tests/unit/runtime_inspection_test.cpp) and
[record scaling](../../tests/unit/initialization_scale_test.cpp).
Cases include native internal and 3/8-child generalized nodes, projections,
self-join loops/local predicates/repeated variables, disconnected/nullary,
Boolean/SQL EXISTS, typed/constant/repeated outputs, unused tables and exact
suffix deltas after initialization. Canonical equality is checked across
independent owners and build methods, alongside independent answers/adapters.

Astra implemented the support and delta owner portions; root integrated physical
construction, cumulative validation/rebuild accounting, session adoption,
diagnostic encoding/schema and acceptance. A separate read-only Astra audit
found one real budget gap: repeated constraint projections and pre-budget
rebuild source copying were omitted. Checked precharges and cumulative prefix
metrics fixed it, with specific regressions. Source and final contract review
then found no remaining blocker. The review's final-matrix condition is now
satisfied. Reviewers did not provide external mathematical or release signoff.

Initial fixture compile/setup issues were corrected: move-only cursor use,
Database aggregate nesting, expected F01 error names, one missing reciprocal
self-join answer, a forbidden generalized-below-native fixture, and explicit
epoch destruction. No production behavior was weakened to satisfy them.

Observed final targeted Debug persistent allocation positions:

| Operation | Direct | Insertion replay |
| --- | --- | --- |
| Physical initialization | 907 | 1,682 |
| Delta initialization/live bootstrap | 980 | 1,755 |
| Physical rebuild | 1,060 | 1,947 |
| Delta rebuild/live bootstrap | 1,137 | 2,024 |
| Initialized session | 1,005 | 1,780 |

Writer sweeps are physical/delta/report 8/8/5 positions. Failure stays armed
through partial-owner unwinding. These are observed implementation quantities,
not stable API allocation counts. The 64-row/12-unique-constraint regression
stops inspection at 483 work under cap 500. Zero-work rebuild's largest
allocation is 67 bytes versus a 32,768-byte source payload, proving rejection
before payload copying. Tight diagnostic encoding rejects a 32 KiB string
with largest allocation 737 bytes under its 16,838-byte output limit.

The exhaustive suite took 73.42 s targeted Debug and 317.56 s in the final
sanitizer run. Its 900-second CTest cap preserves every fault position under
instrumentation instead of reducing coverage.

`nm -C` confirms zero defined RuntimeTestProbe methods in the production
archive and seven in the separately compiled testing archive. Mutation probes
operate on actual private state; production has no corresponding setter.

## Record-space evidence

Both methods give the same observed counts:

| N per independent relation | Source live | Support live | Derivation keys | L rows | Parent bucket rows | Child bucket rows |
| --- | --- | --- | --- | --- | --- | --- |
| 2 | 4 | 18 | 4 | 5 | 2 | 4 |
| 16 | 32 | 102 | 32 | 33 | 2 | 32 |
| 64 | 128 | 390 | 128 | 129 | 2 | 128 |

For this N-by-N fixture, support live is `6N+6`; generalized records are one,
S/E are each `2N+1`, P keys three, child flags two, and both live bucket-key
counts two. The general `O_Q(1+N)` argument is in the contract: generalized
unions, S/P/E subsets/projections and fixed-degree live/index copies avoid
answer-product storage. Scalar widths, metadata/allocator capacity, scratch,
dual rebuild owners and caller history remain separate.

After churn, source live 32 and old-owner slots 64 become fresh-owner live/
slots 32/32. Retained records after pin release are zero. This does not claim
that ordinary churn shrinks arena high-water metadata or establish S05 bytes.

## Matrix and source identity

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 75/75 pass | 195.85 s |
| GCC 13.3 Release | 75/75 pass | 22.22 s |
| ASan/UBSan, including parser C | 75/75 pass | 837.99 s |
| Clang 18.1.3 C/C++ Debug | 75/75 pass | 145.77 s |
| Fresh source-only Release | 75/75 pass | 21.39 s |

Frozen native/test fingerprint (427 inputs):
`760038353e105181a5a1a0245710316b8dfdef34d904c526f0f95b3773a7949e`.
It uses sorted path/NUL/content/NUL over CMake files and
include/src/apps/tests/cmake, excluding Python caches. No native edits were
made during this matrix. The ordinary inventory has 513 inputs; the
[source manifest](runtime-initialization-sources.sha256) seals the final
native and ordinary documentation state. Verification records, handoff
and ledger are excluded. Manifest SHA-256:
`aad918ee2b93ccc511d7c72c2de47d354c281a285b40c5d2825dd189e03475a4`.
The 13 added inputs comprise 11 native/test files, the diagnostic schema and
the initialization contract. An independent Luna Max audit ran
`sha256sum -c` successfully for all 513 entries and separately rediscovered
exactly the same inventory. It recomputed the native fingerprint above and
confirmed the historical hashes. Full checksum output is retained in
`build/verification/runtime-initialization-audit/runtime-initialization-manifest-audit.log`.
Across 39 documents (README, root-level documentation guides, handoff, ledger
and this packet), 352 local Markdown destinations and 93 other local
destinations resolve; 16 external links were excluded. No stale current
statement was found. Ledger table/footer and handoff agree on 78 unique cards:
31 verified, four in progress, 43 not started, with R06 verified and O03 next.
The reviewer made no source/documentation changes and ran no builds or tests.

Clean verification took 379.25 s overall and removed
`/tmp/crown-clean-source-szjzr6wj`. Raw output and aggregate/per-configuration
logs are retained under ignored `build/verification/runtime-initialization-*`,
including `runtime-initialization-summary.json`. All final processes are
terminal/successful; no timeout or silent process was treated as a pass.
Final Release schema audit passes 20 meta, 26 normalized, 19 identity,
59 admission, two layout/projection, 31 physical, three support, two rejected
reports, two physical input events and three actual runtime diagnostics.
The diagnostics include a real counter corruption report, restored before
emission; their schema checks report-validity consistency, not semantic state.

A separate read-only Luna Max evidence audit confirms every summary has
exit zero and 75 passes, every in-place before/after fingerprint matches,
and each retained test log has 75 passed markers and no failures. Actual CMake
compiler metadata confirms GCC 13.3.0 and Clang 18.1.3. Both production and
testing `src/io/inspection.cpp` compile commands enable address/undefined
sanitizers and frame pointers; the parser C build recipe passes the same
sanitizers through CFLAGS. The reviewer ran no builds or tests.

Each in-place run retains five D04 oracle lines reporting `updates=2712`,
`emitted=1408`, `exhaustive_toggles=2504`, and the four N=2/N=64 profile rows
with first/next/last maxima insert 69/63/10 and erase 62/77/10. The D04 fixture
retains its independent A04 comparisons and raw-emission/prefix checks;
the log labels are D04 updates/emitted. Preparation/finalization costs remain
qualified by the existing D05 contract. O01 faults remain constructor
18/18/18, peek 33/15/10 and physical/delta replay 79/122. O02 faults remain
create/begin/preparation/snapshot/drain 57/48/75/7/14. All R06 allocation
counts in the table and writer counts also agree across the four configurations.

Historical O02 manifest SHA-256 stays
`ed176b672510b915328cda857bd1d7ec8b6c9e58c71de3001b689a9a98896b1a`.
Refactor.md stays
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
O01 manifest remains
`394ea5788f1d2dd41a465f8cc591c6e8d535fdff421c8887f1ca14255119fb6d`;
D06 remains
`3300aa4d412930322bbbeb74fe88b0ec3be78586794616cc226d1d67545e1665`.
O03 transport/windows and S04→S05 memory/backend work are still open;
O04 recovery cannot be inferred from a dump. The separate
[O03 design preflight](o03-design-preflight-2026-11-06.md) is a proposal for
the next operational card, not an implemented feature.

## Reproduction

The existing Clang build directory binds Clang 18.1.3 for both C and C++;
the [native build guide](../native_build.md) records toolchain prerequisites.
The sanitizer preset instruments parser C as well as C++.

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
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/runtime-initialization-clean-source.log
sha256sum -c docs/verification/runtime-initialization-sources.sha256
```

The full 78-card implementation goal remains active. G0's remaining license/
provenance decision, external mathematical review, complete bytes, recovery,
durable delivery and release gates remain open.
