# R04 affected-record runtime journal verification, 2026-11-05

Historical checkpoint. The later [prepared logical epoch foundation](prepared-epochs-2026-11-06.md)
extends the same journal across several stages. Its source manifest describes
the current checkpoint; the manifest below describes this R04 snapshot.

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. **R04 is verified for logical
native updates.** The full 78-card goal remains active: 21 verified, three in
progress and 54 not started. Physical SQL/alias epochs, initialization,
enumeration/deltas, recovery and release gates remain open.

Contracts: [runtime support](../runtime_support.md),
[conditional invariants](../support_invariants.md),
[decision 0013](../decisions/0013-support-journals.md),
[storage undo](../storage_journal.md). The new runtime replaces the whole-state
working-copy path from the historical R01–R03 checkpoint.
The current [source manifest](runtime-journal-sources.sha256) contains 447
native source/build/test/fixture/dependency/ordinary-contract inputs; all
fingerprints pass verification. Verification packets/manifests and mutable
handoff/ledger files are excluded. Historical manifests describe their earlier
checkpoints.

## Acceptance audit

| R04 requirement | Implementation and authoritative evidence |
| --- | --- |
| Deterministic queue/stack without plan-depth recursion | A local deque selects FIFO or LIFO explicitly. Event IDs are assigned on enqueue and applied ordinals record drain order. Independent causal replay reconstructs the selected queue discipline and its peak across all generated families. A 128-node insertion/deletion cascade and multiple reverse-bucket matches pass. |
| Explicit before/after values and causal identity | Each real input has native event 1/cause 0; child P crossings identify source node/role/tuple, target/child slot, epoch, cause, key and polarity. Affected-record entries have mutation ordinals, causes, pinned typed values and before/after membership/flags/counts, including positive support changes. Each captured event/cause is validated against its edge/source and application order. |
| Exactly-once internal application | Applied-ID flags reject repeated application and the drain checks all enqueued IDs and equal counters. For every real update, enqueued=applied=1+child-key events; no-ops have no events/journal and zero metrics. Independent replay checks ID/ordinal permutations, causal parents, actual FIFO/LIFO order and queue peaks. Local membership events equal independent role-wise before/after differences without duplicates. |
| Affected-record journal replaces copying | Lazy table journals plus prepared metadata insert/change/extract undo touch affected records and support keys. `State::CopyTag` and per-update snapshot copying are removed. Historical copied_* metrics are zero. A targeted 32-row unrelated-state case visits/logs only the matching parent record plus its native input source; retaining one update journal does not retain all unrelated values or table state. |
| Alternate valid schedules yield the same committed state | An independent full-subtree assignment-join/raw-projection oracle and occurrence-expanded A04 check every node's records/flags/S/P/E/counts and the E join. Across 14 structural families, two seeds generate 1,064 input/cleanup steps under both FIFO and LIFO: 2,128 runtime applications. Both match the same mathematical state. All 34 manual fixture updates remain verified. Newly allocated local IDs may differ between schedules. |
| Replayable before/after descriptions | Every generated update replays journal entries from the verified before snapshot to the independently verified after state, checking exact handles, metadata, membership, state shapes, record ordinals and metadata/saved-flag counts. The separate `support_journal` target covers native/G3/Boolean/nullary/projected-count cases, nesting/cascades, trace-on/off equality and retained-value lifetime. Generalized birth/retirement microsteps are explicitly distinguished from complete-epoch invariants. |
| Failures preserve recoverable previous state | All potentially throwing propagation/artifact construction finishes before a noexcept commit barrier. Abort restores metadata in reverse, then storage nodes/IDs/generations without allocating. Exhaustive bad_alloc sweeps cover 118 last-child insert, 72 supported-child erase, 34 redundant-child-support erase and 64 final-candidate reclaim positions. Later allocations remain disabled during undo. Complete snapshots, truth, sequence, public handles and live/retired/pin counts remain unchanged; same-sequence retry equals a clean epoch, including causes/ordinals/work. |
| Deleted rows remain alive while required | Public journal record pins retain inserted/deleted values through later updates, runtime moves and destruction. Before/after metadata owns its flags/counts. Pending event keys own values too. After all table commits, private undo nodes/scopes/extra pins are released; the returned journal retains affected pins/metadata and optional trace, with container capacity/arena metadata accounted separately. The engine keeps no history. |
| Bounded, optional diagnostic payloads | `capture_transitions` controls membership/event trace payloads; exact event accounting and affected-value retention remain active. Trace-on/off results, journal states and all 20 counters match semantically. Work caps are abstract per-update limits, not byte/time quotas. Retained caller history, snapshots, JSON and cleanup have separate costs. No unbounded append-only string log is introduced into runtime state. |

The root reviewed the implementation and conditional failure/maintenance
argument. Luna Max supplied API/journal tests, expanded allocation tests,
versioned IO/schema integration, contracts and a separate read-only source/proof
consistency review. No concrete rollback/queue defect or source/contract
contradiction was found in that review. This is internal review and finite
evidence, not the outstanding external G2/V02 mathematical signoff.

## Matrix and artifact checks

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 39/39 pass | 51.17 s |
| GCC 13.3 Release | 39/39 pass | 7.43 s |
| ASan/UBSan including parser C | 39/39 pass | 264.08 s |
| Clang 18.1.3 C/C++ Debug | 39/39 pass | 38.35 s |
| Fresh source-only Release | 39/39 pass | 7.19 s |

The fresh configure/build/test took 203.84 s and removed its temporary source/
build tree. All verification handles finished successfully. All 38 earlier
tests remain, with the new `support_journal` target. Native warnings remain
errors; sanitizers enable leak detection and halt on ASan/UBSan errors.

CLI: 25 checks/34 manual states pass normally and under Python `-O`. Optional
schema audit passes 18 schema meta-checks, 26 normalized artifacts, 19 identity
artifacts, 59 admission artifacts, two layout/projection artifacts, 31 physical
artifacts, three support input/v2 report cases and two rejected-update reports.
The v1 trace/report schema is byte-for-byte unchanged against the previous
source manifest; v2 has a separate strict report schema/backend label. Neither
report is a checkpoint or state importer.

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
python3 -O tests/integration/support.py build/debug/crown .
python3 tools/verify_schemas.py build/debug/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/runtime-journal-clean-source.log
sha256sum -c docs/verification/runtime-journal-sources.sha256
```

Logs are under ignored `build/verification/runtime-journal-*.log`.

## Limits and continuation

One call handles one complete logical native set row, not a physical base-row
or SQL alias epoch. R05 must integrate adapters, physical set identity,
derivation counts, deterministic multi-alias fan-out and staged publication.
The journal pins affected values; it does not freeze unrelated outside context
or provide a D01/D02 snapshot cursor. Local membership transitions are not full
answer deltas. Initialization, witness partition/live views, recovery and
output delivery retain their separate acceptance criteria.

The backend still uses ordered standard containers. Work/record/queue counters
are abstract cardinalities, not complete allocator/byte/CPU measurements or a
CROWN update/delay proof. Rollback preserves logical state while revisions and
free high-water metadata/private generations can advance. Caller-held journals
can prolong payload/arena metadata lifetime. S04/S05 must supply optimized
indexes and budgets/accounting. Counter/generation exhaustions are guarded but
tests do not traverse the uint64/size_t range. No R1 release is claimed.
