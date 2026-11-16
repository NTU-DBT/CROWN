# D06 pending lifecycle and delivery, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
D06 is implemented and verified. Independent source/acceptance review and all
66 tests pass the final five-configuration matrix for the frozen sources.
The complete 78-card goal remains active: 28 verified, four in progress
(A02/P04/P06/O06), 46 not started. No blanket G5–G8 or release signoff is claimed.

Contract: [pending lifecycle](../delta_lifecycle.md),
[delta owner](../delta_runtime.md), [D03 states](../delta_transition_spec.md)
and [D05 producer proof/profile](../ordered_delta.md).
Sources: [delta.hpp](../../include/crown/runtime/delta.hpp),
[delta.cpp](../../src/runtime/delta.cpp),
[physical.hpp](../../include/crown/runtime/physical.hpp),
[physical.cpp](../../src/runtime/physical.cpp),
[A04 lifecycle cases](../../tests/unit/delta_lifecycle_test.cpp) and
[persistent fault cases](../../tests/unit/delta_lifecycle_exception_test.cpp).
The [D05 64-test packet](ordered-delta-2026-11-06.md) and its 481-input
manifest are historical; they do not hash these new sources.

## D06 requirement audit

| Obligation | Evidence and scope |
| --- | --- |
| Real pending cursor ownership | `begin` returns before alias/output completion. A heap-stable route owns adjacent-prefix views, C sets, productive queue, extracted witness, cursor position, image and metrics references. `step` yields at most one accepted core row; it does not wrap a precomputed committed artifact. Canonical comparison paths also retain resumable producer state. |
| Pause/resume and sequencing | Pausing after each accepted prefix retains the actual route; resume does not reconstruct it. Public input, reads and mode switches reject while pending. Early commit reports busy without aborting. Invalid pause/resume/paused-step errors preserve ownership. A completed route closes its views/cursors before the next physical alias stages. |
| Required internal draining on discard | `start_drain` disables retention; `discard` continues every L/P/B projection, queue prune, cursor termination and later alias, then commits empty output. Every-prefix tests compare final live/source/current state and a subsequent input to A04. Dropping the unfinished producer is not treated as completed maintenance. |
| Disconnect/abort recovery | Explicit rollback, token destruction and replacement abort unpublished work. Cursors/views close before physical/support/count/source and independent live undo restore state; only then does readiness return. Full snapshots, owners, sequence, pins and invariant checks survive failure and same-sequence retry. Tokens survive runtime facade moves/destruction and own source values independently of caller buffers. |
| Bounded buffers and atomic publication | Finite row/node/value/payload quotas remain enforced before publication. Late spool/work failure after a private prefix aborts the whole input. Output-disabled drain can finish under zero spool quota. Prepared-only commit performs no allocation or throwing preparation after physical publication. No alias fragment becomes ordinary public output early. |
| Recoverable committed sink/codec errors | `deliver_one` retains a borrowed front tuple/ordinal until callback success; serializer failure skips the sink. Failure supports retry or discard, and later input matches clean execution. A strong local data owner protects row lifetime across callback facade moves/replacement/destruction; reentrant consumption rejects, and explicit callback discard defers release until the borrow ends. |
| Distinct maintenance/delta modes | Maintenance stages support without L/P/B or delta enumeration. Mode changes require no pending/output/read ownership. Populated live bootstrap succeeds atomically or preserves the old mode/cache. No-op, projection-count-only, filtered, maintenance/rebootstrap and Boolean EXISTS paths remain distinct. |
| Preserve D05 cost integrity | Exact preparation+first+result+termination+finalization work reconciliation is checked at every discarded core prefix. Existing spool clearing is finalization excluded from the open producer interval; future skipped append is a bounded producer action. Pausing does no producer work. Required preparation and finalization can still make whole API steps data-dependent. |
| Separate timing phases | `timings()` samples physical propagation/commit/abort, internal delta work, native output mapping/spool construction, optional serialization and sink callback CPU/wait separately. Nested phases are excluded from parents, pauses do not accrue work time, and callback failure is timed without acknowledgment. Diagnostic saturating clocks do not enter deterministic work limits or prove mathematical bounds. They are not an exhaustive total wall-clock ledger. |

The D03 state table now explicitly distinguishes an eager prebuilt L image
from D05's in-progress mixed-state row coupling. Exact endpoint L is required
after each route, and before any later route/input/publication. The normative
discard state disables retention; retaining `drain` instead completes pending
preparation without changing that retention policy.

## Targeted evidence and review

The first 18-test regression preflight passed (41.29 s), preserving the five
D04 oracle invocations, D05 phase scale cases, physical/prepared transaction
tests and persistent existing policy sweeps. Both independent new fixtures
then passed after correcting test-only catalog case, cross-runtime owner
normalization, normalized EXISTS source-oracle adaptation and quota setup.
The resumed-cursor fault fixture was strengthened to use two outputs from
one selected child anchor rather than allocation-free route retirement.

Final Debug new lifecycle fault positions:

| Operation | Persistent allocation failures before success |
| --- | --- |
| Begin private physical epoch | 21 |
| First native route setup | 81 |
| Resume selected multirow cursor | 5 |
| Complete paused retaining drain | 130 |
| Complete paused output discard | 127 |

Failure stays armed through rollback. These positions are implementation
evidence, not a stable API/serialization format. Additional no-allocation
checks cover pending rollback/destruction/moves after facade destruction,
prepared commit, callback acknowledgement/move/deferred discard and final
output cleanup. Late quota tests seed in maintenance and calibrate the populated
bootstrap separately so the injected failure occurs after actual private
production, rather than during unrelated setup.

Luna Max authored independent A04-prefix and persistent-failure fixtures.
The root implemented route splitting, resumable producers, pending ownership,
shared callback output lifetime, timing/accounting and integration. An Astra
architecture review checked actual source and identified two contract fixes:
retaining drain must not claim delivery-disabled state, and propagation/drain/
serialization/sink timing must be distinguished. Both were implemented.
A separate fresh-context Astra acceptance/source review found no blocking
finding and approved D06 conditional on this frozen-source final matrix.
Neither reviewer ran tests or claimed external G2/V02/release signoff.

## Matrix and source identity

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 66/66 pass | 113.32 s |
| GCC 13.3 Release | 66/66 pass | 13.49 s |
| ASan/UBSan, including parser C | 66/66 pass | 509.41 s |
| Clang 18.1.3 C/C++ Debug | 66/66 pass | 86.25 s |
| Fresh source-only Release | 66/66 pass | 13.14 s |

Frozen native/test fingerprint:
`1b409ab06628adfffb73c16e517c9436d2d0c01a1ad23c76d8b5616092d0d5ef`
(403 inputs). It uses the D05 sorted-path/NUL/content/NUL definition over
CMake files and include/src/apps/tests/cmake, excluding Python caches.
No native edits are permitted during this final matrix.
The [484-input manifest](delta-lifecycle-sources.sha256) extends D05's
481 inputs with the lifecycle contract and two independent tests. Verification
packets/manifests, handoff and ledger remain excluded. Historical manifests
are preserved. Refactor.md remains byte-identical, SHA-256
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.

Raw successful CTest output, configure/build/test logs and per-configuration
summaries are retained under ignored `build/verification/delta-lifecycle-*`.
All final processes are terminal/successful. Clean verification took
306.87 s overall and removed `/tmp/crown-clean-source-33qm_ozf`. All four
in-place runs have the identical before/after fingerprint above. Each retains
five D04 oracle invocations: 2,712 updates, 1,408 raw records and 2,504 exhaustive
toggles per policy/strategy. D05 maxima remain insert 69/63/10 and erase 62/77/10
at N=2/64, while preparation/finalization grow explicitly.

Optimized-Python CLI checks pass 25 checks/34 states. Schema audit passes
18 meta, 26 normalized, 19 identity, 59 admission, two layout/projection,
31 physical, three support and two rejected-report artifacts. Full CLI/schema
outputs and aggregate `delta-lifecycle-summary.json` are retained beside the
per-configuration logs. Independent `sha256sum -c` passes all 484 inputs; all 194 local links
in the current contracts, packet, ledger and handoff resolve.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/delta-lifecycle-clean-source.log
sha256sum -c docs/verification/delta-lifecycle-sources.sha256
```

Callback retry can duplicate an external side effect if the sink accepts then
throws. Codec scratch is client-owned and needs its own resource policy. No
durable/exactly-once sink, persisted resumable epoch, spill/backpressure transport
or O02 session protocol is inferred. G5–G8 and release gates remain open; the
whole 78-card implementation goal is not complete.
