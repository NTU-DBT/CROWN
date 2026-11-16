# D05 anchored completion component, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
The anchored candidate component is implemented and verified. All 61 tests
pass the final five-configuration matrix. **D05 remains in progress**, with
26 verified cards, six in progress and 46 not started.
The [59-test live checkpoint](incremental-live-2026-11-06.md) and its 476-input
manifest describe the preceding snapshot.

Contract/proof: [anchored completion](../anchored_delta.md),
[live coupling](../incremental_live.md), [delta owner](../delta_runtime.md).
Sources: [delta.hpp](../../include/crown/runtime/delta.hpp),
[delta.cpp](../../src/runtime/delta.cpp), and
[support.cpp](../../src/runtime/support.cpp).

## Requirement audit

| Obligation | Evidence and qualification |
| --- | --- |
| Avoid unrelated root scans for a deep full-key witness | Default delta traversal starts at that E key, uses current/before live-parent indexes upward and indexed target E buckets downward. The root-first reference strategy remains available. |
| Complete duplicate-free candidate traversal | Running intersection, downward totality and live-anchor eligibility make every selected partial assignment extend. An iterative carry/reset traverses the rerooted product and original output slots preserve ordered/repeated typed heads. Nullary and one-factor Boolean cases remain covered. |
| Stable deletion traversal under output-coupled mutation | Upward frames own their selected key and separator. Fresh current/restored `upper_bound` searches read an invariant before-bucket union; no iterator/reference into an extracted node crosses the mutation callback. Alias scratch resets after each route. |
| Exact live-parent index and bounded affected retention | Buckets own full distinct parent keys with matching counts. Bootstrap/invariant rebuilding checks both. Every non-eager oracle event reconciles degree-weighted index changes, copied fields, deletion cleanup, final row count and peak lower bound; no-op epochs report existing index rows. Peak metrics include extracted entries and stage copies, or eager old/new images. |
| Preserve exact projected deltas and prefixes | All three live policies run the same 2,712-event A04 corpus with 1,408 raw records and 2,504 exhaustive toggles. A fourth root-first invocation preserves the comparison path. Raw cardinality, signed sets, stage intervals, source state, L and index invariants match after each event. |
| First/result/last candidate accounting | Aggregate phases and separate maximum individual phase work are recorded. Reroot/index/copy actions, downward cursor work and descriptor lookup steps are charged. Ordered dictionary comparison/successor costs, scalar widths and query-dependent construction remain explicit. |
| Atomic failures | All three policies pass persistent allocation sweeps, including positive-count→extracted-bucket undo, bootstrap, output/quota failure and clean same-sequence retry. Cursor teardown precedes physical/L/index rollback; no throwing work follows publication. |
| Full D05 accepted-output guarantee | **Open.** Canonical rejection can still create long accepted-output gaps or a final rejected tail. K/M preparation, index scratch/undo cleanup and atomic public spooling remain separate costs. A stronger ordered replay scheduler is proposed, not implemented by these sources. |

## Phase and failure evidence

Independent `R(a,x)→S(x,z)` fixtures use a reordered/repeated head and N=1/64
existing root matches, then insert/delete one S key. Indexed candidate phase
counts and individual maxima remain equal at both N values:

| Operation | Anchored startup/result/termination | Root-first result work, N=1→64 |
| --- | --- | --- |
| Insert | 5 / 14 / 4 | 22→274 |
| Erase | 5 / 15 / 5 | 24→339 |

These are abstract indexed actions, not elapsed time or dictionary-comparison
counts. Another original-head fixture records result work 13→13. Independent
cases reverse a two-edge ancestor path with multiple parents and sibling
products, remove selected parent keys, reopen buckets, handle nullary edges
and retain exact alias prefixes across maintenance/rebootstrap. The existing
four-level shared-parent fixture and typed date/decimal/string/Boolean cases
also run under the default anchor.

Final GCC Debug persistent allocation positions:

| Live policy | Insert | Erase | Shared-separator erase | Bootstrap |
| --- | --- | --- | --- | --- |
| `on_output` | 208 | 181 | 224 | 44 |
| `incremental` | 202 | 173 | 233 | 44 |
| `eager` | 284 | 242 | 214 | 44 |

Failure remains armed throughout rollback. Counts are implementation evidence,
not a stable public format. The 2,504-toggle finite scope is unchanged from
the D04 packet and does not replace the conditional arbitrary-query proof.

## Independent review

The root implemented the production index/cursor integration and counter/space
audits. Luna Max authored the independent anchor/reference oracle fixture and
the bucket descriptor-work counter. A fresh-context Astra agent reviewed the
actual cursor, stable deletion union, count/inner/outer-node undo, output
mapping, totality and image selection read-only; it ran no builds/tests.

Review identified two accounting obligations: charge cleanup for the final
stage and report retained parent-index space. Both are implemented. The root
also checked final no-op metrics and added independent expected-row assertions.
Astra identified uncharged bucket descriptor search; the explicit
`CursorWork::descriptor_steps` loop now records it. Fixed-query candidate
indexed-action bounds retain query descriptor/layout and logarithmic/value
cost qualifications. No correctness/rollback blocker remained in this source
review. External G2/V02 review and release gates remain unsigned.

## Verification

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 61/61 pass | 95.75 s |
| GCC 13.3 Release | 61/61 pass | 11.57 s |
| ASan/UBSan including parser C | 61/61 pass | 442.09 s |
| Clang 18.1.3 C/C++ Debug | 61/61 pass | 73.79 s |
| Fresh source-only Release | 61/61 pass | 11.08 s |

The clean run took 285.70 s and removed its temporary source/build tree.
Every final process handle is terminal/successful. All four in-place jobs
share unchanged before/after native/build/test inputs:
`77121a3168af5533f746f56e93a507a372bd150d207802ad8d305df3378aca66`.
Final targeted preflight passed 12/12 tests in 30.50 s. The expanded suite adds
one anchor executable and one root-first semantic invocation to the previous
59 tests. Warnings remain errors.

The Release CLI passes 25 support checks/34 manual logical states under
Python `-O`. The optional schema audit passes 18 meta-checks, 26 normalized,
19 identity, 59 admission, two layout/projection, 31 physical, three support
trace/report and two rejected-update artifacts. Frozen schemas/trace formats
are unchanged; no new CLI delta protocol is inferred.

The [478-input manifest](anchored-delta-sources.sha256) extends the preceding
476 inputs with the anchor contract/proof and independent fixture. All hashes
pass; Refactor.md retains its original hash. Verification packets/manifests
and mutable handoff/ledger are excluded. Ignored
`build/verification/anchored-delta-*` logs retain the actual commands, full
successful CTest output and CLI/schema results. The four per-job summaries
and `anchored-delta-summary.json` record exact source stability and outcomes.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/anchored-delta-clean-source.log
sha256sum -c docs/verification/anchored-delta-sources.sha256
```

## Continuation

The live argument's earlier residual-join investigation left an insertion
initialization problem. A new read-only Astra investigation proposes monotone
E-key replay (bottom-up insert/top-down delete), child-side current-L buckets,
and productive witness queues. The [proposal](../anchored_delta.md) records
the invariant and exact code changes still required. These frozen sources
retain canonical rejection; no replay bound is claimed here. Complete that
implementation and its separate proof/oracle/fault review, including honest
first/last preparation and cleanup accounting, before closing D05.
