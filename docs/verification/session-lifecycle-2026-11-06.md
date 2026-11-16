# O02 query/session lifecycle, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
O02 is implemented and verified. Both independent suites, fresh Astra source
acceptance and all 71 tests pass the final five-configuration matrix for frozen
sources. The entire 78-card goal remains active: 30 verified, four in progress
(A02/P04/P06/O06), 44 not started. No broader operational, recovery or release
gate is inferred.

Contract: [session lifecycle](../session_lifecycle.md),
[D06 private/output ownership](../delta_lifecycle.md) and
[O01 source acceptance](../ingestion.md).
Sources: [session API](../../include/crown/runtime/session.hpp),
[session coordinator](../../src/runtime/session.cpp),
[reader close API](../../include/crown/io/ingest.hpp),
[reader implementation](../../src/io/ingest.cpp),
[semantic/state cases](../../tests/unit/session_test.cpp) and
[persistent failure cases](../../tests/unit/session_exception_test.cpp).
The [O01 69-test packet](physical-input-2026-11-06.md) and its 495-input
manifest remain historical and have not been resealed.

## Requirement audit

| O02 obligation | Implementation and acceptance scope |
| --- | --- |
| Create/start | Factory owns a verified plan and input stream, initializes the actual empty-database epoch zero, and returns a noncopyable/nonmovable session. Start opens admission; it is idempotent while running and resumes paused private work. Initial-state restore and SQL compilation are separate upstream/R06/O04 contracts. |
| One writer/resource owner | All public operations check immutable creator-thread identity before mutable state and reject nested calls through a guard. Runtime, reader, private pending token and committed output artifact never escape. The stream outlives its reader, including construction failure. Destruction requires exclusive ownership and keeps the implementation alive/guarded through cleanup. |
| Precise API/state behavior | Separate control states and work phases have complete documented API tables and error precedence. Created, paused, stopped and dropped calls have distinct diagnostics; ready/pending/draining/prepared/output errors preserve valid work. Repeated stop/drop, EOF, prepared step and ready drain have explicit idempotence. |
| Real pause/resume | `begin_next` peeks and begins a genuine D06 epoch without completing it. `step` drives actual private production. Pause/resume retains its cursor; control-only pause covers draining/prepared/output without illegal D06 transitions or background work. Pending snapshots/output/new input reject. |
| Drain/cancellation | One-epoch drain disables retention, completes every internal row and alias, commits and acknowledges exactly one input, then destroys the empty output artifact. Paused control remains paused. Committed drain discards output only. It never reads the next event or treats cursor abandonment as completed maintenance. |
| Atomic input/progress publication | Prepared-only commit first publishes the whole engine epoch, then performs nonallocating reader acknowledgement, epoch/token moves/cleanup and scalar updates. Parse failure stays sticky; engine failure resets aborted private ownership while preserving the cached input and old accepted progress for retry. |
| Coherent owning snapshots | A local D01 cursor materializes bounded committed results with sequence, progress and layout. Snapshot is legal during unread committed output and after stop; it does not silently drain private input. Returned rows/layout/progress own their values and do not retain runtime read leases. Epoch-zero SQL EXISTS false and native Boolean/nullary results use actual runtime semantics. |
| Terminal stop/drop | Stop rolls back/destroys private work, discards and destroys output, moves final accepted progress out through `EventReader::close`, then releases reader/stream buffers. Committed runtime remains for stopped snapshots. Drop also destroys runtime/plan/progress, retaining a scalar tombstone status. Neither operation acknowledges unfinished input. |

Snapshot limits bound accepted retained row storage: vector slots, Value
capacity, string capacity plus one and D06's 64-byte decimal coefficient
allowance. Progress/layout metadata, allocator overhead, one cursor-produced
row and transient old/new vector allocations are additional; this is not a
peak-memory or S05 complete allocator cap. Materialization is output-sensitive.

## Independent tests and review

Luna Max authored separate semantic/state/oracle and persistent-allocation
fixtures. Root implemented the coordinator, close helper, integration and
contract. Astra architecture and fresh actual-source reviews found no
production blocker in the publication, ownership, error or cleanup paths.
The fresh reviewer confirmed all reported fixture blockers resolved in the
actual source. Its final-matrix condition is now satisfied;
reviewers ran no builds or tests and did not provide external release signoff.

Initial fixture drafts had test-only setup/state mistakes: pointer use, empty
database width, missing starts, incomplete trace length, reopening an already
pending event and beginning new input before consuming output. Compile/run
diagnostics and fresh source review identified these; they were corrected
without weakening the state/oracle assertions or changing production behavior.
The reentry stream fixture was changed to actually invoke its callback during
guarded input, and quota injection was moved from constructor bootstrap to
private output production.

The persistent-failure fixture passes with allocation failure armed through
unwinding. Observed targeted Debug failure positions:

| Operation | Failures before success |
| --- | --- |
| Session construction, including ownership cleanup | 57 |
| Begin next input, parser / engine begin | 27 / 21 (48 total) |
| Retaining private step/preparation | 75 |
| Owning snapshot, including progress copy/cursor | 7 |
| Start-drain / required no-retention drain | 14 |

It also tests no-allocation prepared commitment/new and existing source
positions, output transfer, stop/drop/destruction at private prefixes, direct
reader close, late quota/alias rollback and same-cached-input retry. Returned
snapshot/output values survive deletion and drop. Fault positions are observed
implementation evidence, not stable API quantities or general complexity bounds.

## Matrix and source identity

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 71/71 pass | 113.62 s |
| GCC 13.3 Release | 71/71 pass | 13.85 s |
| ASan/UBSan, including parser C | 71/71 pass | 515.78 s |
| Clang 18.1.3 C/C++ Debug | 71/71 pass | 83.59 s |
| Fresh source-only Release | 71/71 pass | 13.33 s |

Frozen native/test fingerprint:
`bc273e13906f7e7c9464167d1466058bd5f2f31730e7d91584bc06679ff26864`
(416 inputs). It uses the prior sorted-path/NUL/content/NUL definition over
CMake files and include/src/apps/tests/cmake, excluding Python caches. No
native source changed during the final matrix. The
[500-input manifest](session-lifecycle-sources.sha256) adds the session API/
implementation, two independent tests and lifecycle contract to O01's 495.
Verification records, handoff and ledger are excluded. Local-link/ledger and
independent manifest validation are recorded after the source seal.
Manifest SHA-256:
`ed176b672510b915328cda857bd1d7ec8b6c9e58c71de3001b689a9a98896b1a`.
Independent `sha256sum -c` passes all 500 inputs; all 166 checked local
Markdown destinations resolve (81 unique targets). The audit found three
stale cross-references to pre-O02 status; those were corrected and the current
manifest resealed after the documentation-only input-guide change. Native
sources/fingerprints and historical manifests stayed unchanged. The ledger
table and trailing prose both retain 78 cards with 30/4/44 status counts.

All final processes are terminal/successful. Clean verification took 329.51 s
overall and removed `/tmp/crown-clean-source-kl6tun9q`. All four in-place jobs
record the identical before/after fingerprint above. Raw successful CTest
output, configuration/build/test logs and aggregate/per-configuration summaries
are under ignored `build/verification/session-lifecycle-*`.

The O01 manifest retains SHA-256
`394ea5788f1d2dd41a465f8cc591c6e8d535fdff421c8887f1ca14255119fb6d`.
Refactor.md remains unchanged, SHA-256
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
The historical D06 manifest also remains unchanged.

Each in-place run retains five D04 oracle invocations, each with 2,712 events,
1,408 raw records and 2,504 exhaustive toggles. D05 first/next/last maxima remain
insert 69/63/10 and erase 62/77/10 at N=2/64, with growing preparation/
finalization costs. O01 constructor/peek/replay failure counts are preserved.
The schema audit passes 19 meta, 26 normalized, 19 identity, 59 admission,
two layout/projection, 31 physical, three support, two rejected-report and
two physical-input artifacts. Actual GCC 13.3 and Clang 18.1.3 compilers and
ASan/UBSan instrumentation for session code and both new fixtures were checked;
the upstream parser C sanitizer recipe remains enabled.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/session-lifecycle-clean-source.log
sha256sum -c docs/verification/session-lifecycle-sources.sha256
```

O03 batching/windows, R06 build/rebuild, S05 complete byte accounting,
O04 checkpoints, O05 WAL/recovery, O06 durable sinks/backpressure and O08 public
CLI release remain separate work. This C++ session is not a checkpoint or a
durable delivery protocol. The complete implementation goal remains active.
