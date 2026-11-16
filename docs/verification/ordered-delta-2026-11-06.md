# D05 ordered replay and guarantee profile, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
D05 is implemented and verified for the qualified internal production
contract below. All 64 tests pass the final five-configuration matrix.
The full 78-card goal remains active: 27 verified, five in progress
(A02/P04/P06/D06/O06), 46 not started. No release or blanket G5–G8 approval
is claimed.

Contract/proof: [ordered replay](../ordered_delta.md),
[delta owner](../delta_runtime.md), [D03 partition](../delta_transition_spec.md).
Sources: [delta.hpp](../../include/crown/runtime/delta.hpp),
[delta.cpp](../../src/runtime/delta.cpp),
[runtime oracle](../../tests/unit/delta_runtime_test.cpp),
[replay fixtures](../../tests/unit/delta_replay_test.cpp) and
[scale fixture](../../tests/unit/delta_replay_scale_test.cpp).
The [61-test anchor packet](anchored-delta-2026-11-06.md) and its 478-input
manifest are historical and are not hashes of these sources.

## Requirement audit

| D05 obligation | Evidence and qualification |
| --- | --- |
| Optimized scheduling without rejected/dead tails | Replay visits insertion factors in reverse rank order and deletion factors forward. Preparation tests all K E crossings once; insertion filters initial dead keys and deletion prunes future anchors on actual L erasure. Every remaining queue head is productive. Candidates equal accepted core rows, with zero canonical rejects/earlier-owner probes. |
| Exact disjoint witness ownership and live state | Mixed E states remain downward-total, including skipped crossings. Endpoint E supplies the anchor's original subtree; exact current parent/child live buckets supply unchanged outside branches. Every row belongs to its single-key crossing, preserving D03's minimum-factor owner and physical alias order. Anchor-specific deletion plus the fresh ancestor-path certificate gives exact L at each fragment boundary. |
| Bounded first/next/last transitions | After route preparation, a successful producer transition performs a fixed-query bounded number of cursor/queue/L/P/B/mapping/spool actions. It includes cursor exhaustion/frame closure, head release and empty factor scans. Separate maxima stay equal as D grows from 2 to 64. Ordered dictionaries retain logarithmic comparison costs, widths and allocation costs. This is an internal indexed-action bound, not constant wall time or constant public startup. |
| Charge discovery, live state and journal work | Preparation records M/K view/journal/changed-key and queue work. Exact J L crossings, degree-weighted U parent-index changes and V nonroot child-index changes reconcile with independent A04 projections, fields/copies and undo entries. Default replay has no per-route full L rebuild or stage-before live copies. Bootstrap/invariant scans and eager reference full images remain explicit. |
| Charge finalization and retained state | Conservative view/kernel/driver cleanup bounds, cleared C keys and exact live undo length are charged before physical publication. Eager mode additionally charges full retired L/P/B images even at D=0. Undo and FIFO spool use one prepared owning node per change/record with iterative teardown, avoiding result-dependent buffer moves during production and deep recursive destruction. Per-node allocator metadata, pins, returned rows and arena high-water metadata remain additional. |
| Expose an honest guarantee profile | Detached `DeltaRuntimeProfile` identifies effective mode/strategies/view, typed candidate/accepted bounds, publication, caps, backend/domain assumptions, scans, preparation/maintenance/finalization and public-startup costs. Only active replay claims bounded accepted indexed actions; canonical paths do not inherit it. Enforced source constraints can scan/copy DB. Physical-plan v1 remains compile-only. |
| Preserve D04 under the same traces | Five invocations each compare 2,712 events, 1,408 raw output records and 2,504 exhaustive toggles against A04: default replay/on-output, canonical eager, canonical incremental, root-first and explicit canonical anchored. They check raw cardinality/signed sets, physical endpoints, alias-prefix intervals, SQL mapping, L and index invariants after each event. |
| Failure and ownership safety | All three live policies pass persistent allocation sweeps, including shared-separator deletion and bootstrap. Row/byte/work failures, late SQL EXISTS failure, same-sequence retry and no-allocation final delivery/discard/destruction pass. Readers close before rollback; prepared node/scalar undo restores physical/support/L/P/B before readiness. All throwing checks precede publication. |

The 2,504-toggle finite scope is unchanged from D04 (64+384+2,048+8
transitions). It supplements, rather than replaces, the conditional
arbitrary-query proof. Source-free constant/contradictory and nullary cases,
ordered/repeated typed heads, hidden projection collisions, products, aliases
and maintenance/rebootstrap remain covered.

## Transition and failure evidence

The independent R(a,x)→S(x,y) scale fixture seeds N roots with no matching S,
then inserts/erases one S key. Preparation and finalization grow with affected
work; post-preparation transition maxima remain equal:

| Operation / N | First / next / last indexed work | Preparation | Finalization |
| --- | --- | --- | --- |
| Insert / 2 | 69 / 63 / 10 | 62 | 74 |
| Insert / 64 | 69 / 63 / 10 | 1,116 | 632 |
| Erase / 2 | 62 / 77 / 10 | 91 | 101 |
| Erase / 64 | 62 / 77 / 10 | 1,579 | 1,031 |

Replay emits N candidates/N accepted rows. The canonical incremental
comparison emits 2N candidates with N rejections, demonstrating the removed
tail. Deletion starts with N+1 queued keys and prunes the child anchor after
its L removal. These action counts are implementation evidence, not a stable
serialized format or elapsed-time estimate.

The canonical repeated-head comparison remains flat at 5/14/6 insert and
5/15/7 erase candidate phases for N=1/64; root-first result work grows
22→274 and 24→339. Termination now includes explicit frame closure, so the
historical anchor packet's 4/5 termination counts are not reused. The original
head remains 13→13. Current eager empty-delta scan work grows 29→92; canonical
incremental stays 8→8 for 1→64 dead E rows.

Final GCC Debug persistent allocation positions:

| Policy / effective strategy | Insert | Erase | Shared-separator erase | Bootstrap |
| --- | --- | --- | --- | --- |
| `on_output` / replay | 215 | 179 | 210 | 53 |
| `eager` / anchored | 305 | 263 | 215 | 53 |
| `incremental` / anchored | 203 | 172 | 231 | 53 |

Failure stays armed throughout rollback. Snapshots, sequences, exact index
invariants, previous pins and clean retry are checked. Quota failure exposes
no partial epoch, including later aliases and final two-sign EXISTS mapping.

## Review and disposition

The root implemented mixed-state replay, child indexes, productive queues,
intrusive undo/spool, accounting and the profile. Luna Max supplied independent
A04 replay cases, canonical-tail/phase scaling cases, detached profile and
option checks, and a separate evidence audit. An Astra reviewer independently
traced the mixed-state totality/ownership/freshness proof and actual source,
without running builds or changing files. Its eager-state/full-image
finalization finding and outdated header wording were corrected before the
final matrix. A fresh-context Astra gate review found no remaining D05
source/proof/profile blocker and confirmed that D06/O06 are separate gates.

Public `apply` still prepares all aliases and the complete bounded atomic
spool before returning output. Its first record includes physical constraint
validation/maintenance, all preparation, production and finalization. D06
unpublished pause/resume/draining/sink-error acceptance and O06 operational
sink/spill/backpressure/delivery/recovery remain open. Internal review does
not replace external G2/V02 review, a complete G5 packet or release signoff.

## Final matrix and source identity

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 64/64 pass | 100.20 s |
| GCC 13.3 Release | 64/64 pass | 11.89 s |
| ASan/UBSan, including parser C | 64/64 pass | 468.97 s |
| Clang 18.1.3 C/C++ Debug | 64/64 pass | 75.42 s |
| Fresh source-only Release | 64/64 pass | 11.94 s |

All final processes are terminal/successful. The clean build took 288.71 s
overall; `/tmp/crown-clean-source-px0tfhv3` was removed. Final optimized-Python
support CLI checks pass 25 checks/34 states. Schema audit passes 18 meta-checks,
26 normalized, 19 identity, 59 admission, two layout/projection, 31 physical,
three support trace/report and two rejected-update report artifacts.

The native/test fingerprint is
`c85161c7781243c70d25b304b2f144f0796fd9f74a69b4fdd9dccb738d2e2c2a`.
All four in-place matrix jobs recorded this identical before/after value;
no native source changed during verification. It hashes sorted paths, NUL,
contents, NUL for CMakeLists/CMakePresets and files under include/src/apps/
tests/cmake, excluding Python caches. The
[481-input manifest](ordered-delta-sources.sha256) adds the replay argument and
two independent tests to the previous 478 inputs. It covers ordinary sources,
fixtures and contracts; verification packets/manifests and handoff/ledger are
excluded to avoid circular evidence. Historical manifests remain unchanged.
Independent `sha256sum -c` verification passes all 481 inputs; all 170 local
links in the current contracts, packet, ledger and handoff resolve.
Original `Refactor.md` remains byte-identical (SHA-256
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`).

Full outputs/summaries are retained in ignored
`build/verification/ordered-delta-*-{configure,build,test}.log`,
`ordered-delta-*-ctest-output.log`, `ordered-delta-*-summary.json`,
`ordered-delta-summary.json` and `ordered-delta-clean-source.log`.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/ordered-delta-clean-source.log
sha256sum -c docs/verification/ordered-delta-sources.sha256
```

Next: D06 lifecycle/recoverable-state acceptance, followed by operational
interfaces. Preserve the whole 78-card scope and all D04 oracle/fault traces.
