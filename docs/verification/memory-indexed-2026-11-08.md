# Native accounted optimized storage checkpoint — 8 November 2026

This is the historical frozen optimized-backend checkpoint. The successor
[native accounted dispatch record](memory-dispatch-2026-11-08.md) covers later
implementation. Statements below apply to this packet's own source and runs.

S05 is **in progress**. The actual `crown_accounted_indexed` production target
now builds account-aware optimized rows, keys, memberships, indices, directories,
cursors, collections and journals. It shares the existing query account and
native owner authorities with `crown_core`'s accounted reference backend. The
runtime facade, complete plan/query ownership and full native suite remain open.

Frozen input is `build/verification/s05-accounted-indexed-source-attempt-2/`
(875 files). Each selected build compiles 58 actual C++ commands from 51 distinct
sources into seven native production/testing libraries and 13 test executables.
The main memory fixture and two collision variants each execute all 36 checks;
ten earlier layout/arena/reference/journal/facade regressions are also selected.
All 31 previous native checks and the 26 earlier foundation checks are retained.

All four runs and their source/command/object/archive/link/test audits pass:

| Mode | Actual build seconds | CTest real seconds | Selected tests |
| --- | ---: | ---: | ---: |
| GCC Debug | 103.300 | 29.40 | 13/13 |
| GCC Release | 138.796 | 2.95 | 13/13 |
| Clang Debug | 89.847 | 21.62 | 13/13 |
| GCC ASan+UBSan/leaks | 181.295 | 108.61 | 13/13 |

All compiler/test handles are closed. The accepted matrix is
`build/verification/s05-accounted-indexed-matrix-accepted-v1.json`; current jobs
and continuation are in `build/verification/s05-accounted-indexed-jobs.json`.

All four modes agree on the following optimized allocation samples:

| Operation | Observed allocation positions |
| --- | ---: |
| Insert | 10 |
| Add secondary index | 9 |
| Erase handle | 0 |
| Erase key, including lookup-key construction | 2 |
| Journal insert | 13 |
| Journal erase | 3 |
| Owning snapshot | 3 |
| Same-account table copy | 31 |
| Owning keys | 2 |
| Owning bucket handles, including lookup key | 2 |
| Live cursor | 1 |
| Journal/control | 2 |
| Another table State/control and arena | 2 |
| Bucket cursor, including lookup key | 2 |
| Key cursor | 1 |
| Journal live cursor | 1 |
| Journal bucket cursor, including lookup key | 2 |
| Journal key cursor | 1 |
| Owning shared work handle | 1 |
| Journal insert with entry-array growth | 13 |
| Journal erase with entry-array growth | 3 |
| Drop index | 0 |
| Clear | 0 |

Each of the **104** observed positions is failed persistently. Failure releases
temporary ownership and preserves previous row addresses/hashes, logical IDs,
index membership, journal size and current purpose/lifetime byte partitions;
retry then succeeds. Zero-allocation operations have no synthetic failure
positions. Private journal-growth preparation keeps published capacity unchanged
on failure. Rollback/final teardown allocate no bookkeeping.

Actual simultaneous fixture peak is **40,753 requested bytes** in the production
profile and **40,761** in each testing profile, whose State includes an additional
testing field. Exact-limit success, one-byte-under denial and a smaller-row retry
pass. The earlier reference fixture still fails all 91 positions across its 13
operations in each profile, with its 38,972-byte measured fixture peak.

Optimized tests cover **44** positive work boundaries across all five domains
and all **nine** finite component limits. Private testing variants also force
tuple-ID, index-ID and revision exhaustion; fixed errors allocate no ordinary
new storage and no counter wraps. Grant copies share the same remaining work;
foreign owning grants and replacement journal-cursor grants are rejected.

A 256-step independent legacy-table model checks rows, keys and rollback. Sparse
cursor checks leave eight live rows after populations of eight and 64: startup
uses eight pointer words in both, and eight rows plus end detection consume nine
live-link steps without allocation, hashing, ID lookup or payload copies. A
zero-work denial does not advance the cursor. Replacement chains, independent
committed histories, pins/outputs/weak controls and an active writer outliving
its table facade are covered.

Root audits compare actual commands with configured dependencies and exact
strict flags/include roots, then bind fresh objects, archive member bytes and
final links. Production libraries have no allocating global new/delete hooks
or private accounted-index testing entry points. All 20 test-only allocation
hooks are present in each memory fixture object and executable. Legacy/new
testing defines remain separate. Each selected sanitizer test requires the
actual address/undefined/leak-check environment.

CTest truncates each memory profile's JUnit output after 1,024 bytes. Auditor v3
matches every successful JUnit identity with its actual verbose command, checks
the retained output prefix and reads each complete profile by its own CTest
number. The failed v2 audit is preserved. Tests and frozen source did not change
for this report-parser correction. Source1's strict compiler failure is likewise
preserved; source2 names borrowed row views before range iteration to satisfy
GCC's dangling-reference warning without weakening flags or ownership.

Measurements are actual ordinary-new requests including controlled headers and
alignment. They do not establish allocator usable size, RSS, exception-runtime
storage or complete query byte enforcement. The nested-string coverage-gap
witness remains explicit. No runtime speedup is asserted by these test timings.

Evidence uses the `s05-accounted-indexed-` prefix under `build/verification/`:
execution freeze attempt2, source attempt2, per-mode records, auditor-v3 summaries,
actual terminal closures and preserved preimages/failures. The historical
[reference checkpoint](memory-storage-2026-11-08.md) and S04 source/matrix seals
remain as-of evidence for their own frozen sources. Never compare their old
input hashes with successor implementation bytes.

Root implemented/reviewed the native code and owns each run. No new Astra was
used. See the [memory contract](../memory_accounts.md) and [handoff](../handoff.md)
for remaining runtime integration and the unchanged full 78-card objective.
