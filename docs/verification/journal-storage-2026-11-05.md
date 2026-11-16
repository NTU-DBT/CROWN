# R04 storage undo foundation, 2026-11-05

Historical storage-only checkpoint. R04 runtime integration and current source
fingerprints are in [runtime journal verification](runtime-journal-2026-11-05.md).

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. The reversible table journal is
verified. **R04 remains in progress.**
The support runtime still uses full working copies. This checkpoint proves a
necessary storage undo primitive, not completion of the runtime epoch journal
or the full 78-card refactor.

Contract: [storage journals](../storage_journal.md),
[reference storage](../storage.md), [tuple arenas](../tuple_arenas.md).
The current [source manifest](journal-storage-sources.sha256) includes 444
native source/build/test/fixture/dependency/contract inputs; all fingerprints
pass verification. Verification packets/manifests and mutable handoff/ledger
files are excluded. Earlier manifests describe their historical checkpoints.

## Implemented behavior

- `ReferenceTable::journal()` opens one exclusive writer scope. Regular
  mutators and cursor creation/advance reject with `storage_busy`; internal
  reads can inspect tentative rows. Duplicate/absent operations add no entry.
- Journal insertions retain a pin and precomputed undo keys. Deletions pin the
  allocation and extract primary, ID, secondary-bucket and member nodes. All
  potentially allocating preparation precedes extraction.
- Reverse undo reuses those nodes, restores original primary iterators and
  privately revives the pinned slot. Original row IDs, arena generations,
  addresses and index memberships are restored without replacement values or
  allocation. Bucket lookup uses retained typed keys rather than iterators
  invalidated by later extraction/reinsertion.
- Explicit rollback and active destruction undo in reverse order. Commit
  releases the table state/write lock and retains ordered change views/pins
  until the journal is destroyed. Inserted/deleted payloads remain readable
  after subsequent table clear/destruction. This retention keeps arena metadata,
  not the entire table state/indexes, alive.
- Committed logical IDs remain monotonic. Aborted inserts restore the previous
  ID counter, so tentative handles must never be published. Arena high-water
  metadata/private generations may advance after abort. Revisions remain
  advanced after real tentative changes to invalidate saved cursors safely.

## Independent checks

`storage_journal` uses an independent map-of-sets model and raw positional key
extraction over 12 seeds, 90 scopes per seed and 12 actions per scope:
**12,960 model steps in 1,080 committed/aborted scopes**. A bulk-key step may
perform several row erasures. Every model step and completed scope checks rows,
IDs and all index memberships. Boundary
cases cover shared/nullary buckets, erase/reinsert, absent/duplicate operations,
foreign-owner errors, cursor locks, exact dates/decimals/strings, move assignment,
automatic rollback and committed payload lifetime. Pins check original slot,
generation, address and value after rollback. Allocation-disabled checks cover
commit, rollback and destructor rollback. Separate per-operation sweeps cover
**23 insert and five erase allocation-failure positions**, preserving the
prior tentative state and allowing retry.

`storage_journal_exceptions` fails every allocation before the first complete
mixed transaction succeeds: **178 positions**. The transaction includes earlier
successful inserts, shared-bucket removals, singleton bucket extraction,
repeated absent deletes, erase/reinsert of the same values and deletion of a
newly inserted tuple. Faults after tentative mutations are explicitly required.
The injector remains active through destructor rollback. Every abort restores
the full row/index image, original IDs, pin generations/addresses, live/retired/
pin counts and the next logical ID. Retried operations succeed. Commit and
explicit rollback also run with allocations disabled, and retained payloads
are read after their table has actually been destroyed.

Luna Max supplied the independent tests and contract, then performed a separate
read-only undo/lifecycle review. The review found no defect in the inspected
paths under single-writer/external synchronization assumptions. The root
reviewed integration and models, corrected test setup issues, and ran the full
matrix. This internal review does not close external G2/V02 review.

## Matrix

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 38/38 pass | 50.50 s |
| GCC 13.3 Release | 38/38 pass | 7.43 s |
| ASan/UBSan including parser C | 38/38 pass | 258.64 s |
| Clang 18.1.3 C/C++ Debug | 38/38 pass | 39.45 s |
| Fresh source-only Release | 38/38 pass | 7.14 s |

The fresh configure/build/test took 200.14 s and removed its temporary source/
build tree. All 36 previous tests remain in the suite. No artifact schema or
CLI format changed; runtime diagnostic reports still accurately identify the
full-copy backend. Strict warnings remain enabled as errors. Sanitizers use
leak detection and halt on ASan/UBSan errors. Logs are under ignored
`build/verification/journal-storage-*.log`.
All verification processes have finished successfully.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/journal-storage-clean-source.log
sha256sum -c docs/verification/journal-storage-sources.sha256
```

## Remaining R04 work and limits

Next, wire these storage journals into `SupportRuntime` and add affected
metadata undo for child flags and P/E counters. Prepare all returned artifacts
before an allocation-free multi-table commit. Add causal event IDs, epoch and
parent cause, explicit before/after values and exactly-once queue accounting;
test alternate schedules and faults throughout the new transaction. Replace
full-state copies and expose honest journal/work metrics and diagnostic
versioning. Preserve the R01–R03 independent subtree oracle and failure tests.

The table primitive alone supplies no multi-table visibility boundary, full
before-state query snapshot, answer cursor/delta, physical alias epoch, recovery
or complexity claim. Journals retain affected values/keys/container nodes and
arena high-water metadata; byte quotas/accounting remain S05. Models and fault
sweeps are finite; uint64/size_t exhaustion is guarded but not traversed. The
full ledger remains 20 verified cards, four in progress and 54 not started.
