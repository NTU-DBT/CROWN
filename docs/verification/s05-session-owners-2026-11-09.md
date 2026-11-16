# S05 native session and snapshot ownership — 9 November 2026

Status: **in progress**. The full78-card Refactor.md goal remains active at
41 verified /3 in progress /34 not started. Root implemented this checkpoint;
one Luna Max agent performed a read-only caller/test audit. No Astra agent was
used. Artifacts live in `build/verification/s05-session-owners-*`.

## Implemented ownership

Actual session factories establish the runtime's original account before
allocating the QuerySession facade and stable implementation. They return
`QuerySession::Owner`, an AccountedUnique whose stored allocator/deleter retains
that account through final object destruction/deallocation. No additional query
allowance is created. Native run-context and session statistics-context outer
shared objects/controls also use the same account.

`SessionSnapshot::rows` is now a read-only SessionRows collection, with an actual
funded shared object/control and allocator-backed tuple capacity. Native tuple
payloads remain under their original account. The reported retained bytes are
the actual collection/control/capacity and native tuple requests, including
account framing. Shared metadata is charged once to the query account outside
this snapshot sublimit. Transient old/new capacity blocks during growth also
consume the original query budget. Empty rows allocate no collection/control or
capacity block. Nullary output still owns real tuple and collection requests.

Row-collection copies/assignments share immutable owners without allocation;
assignment across queries transfers the source owner rather than copying a
vector through a different allocator. Iterators/references borrow from a live
collection handle. Copies of the full snapshot can still allocate their ordinary
progress maps. Held rows retain values, layout tokens and charged ownership
after session drop/destruction. Release and existing publication/commit/stop/drop
paths remain nonallocating.

Window controllers retain their required stable address. The native construction
path borrows the already compiled catalog and funds the window facade and
implementation controls under the session's original account. Its nested
maps/sets/options/rows and prepared control are still migration work.

These public API changes replace ordinary explicit unique session pointers with
`QuerySession::Owner` and mutable snapshot vectors with read-only SessionRows.
Existing `auto`/read-only callers continue to work. Seven existing test files
receive exactly15 owner type substitutions; a whole-file equality audit proves
all other algorithms, expected results and assertions are unchanged.

## Current verification scope

Source3 freezes920 paths and is the tested C++ implementation. Final source4 adds
only current documentation. Immutable progress-v2 binds the completed scopes and
hashes; all commands/handles are closed. Debug build4
passes all targets with strict warnings enabled. The actual new memory test
passes and checks exact retained allocation reconciliation, original-account
controls, exact/one-under snapshot and query budgets, immutable owner assignment,
post-facade lifetime, empty/nullary results, persistent failures and final release.

| Configuration | Observed scope |
| --- | --- |
| GCC Debug |57/57 related integration tests,130.09s |
| GCC Release |14/14 selected integration/failure tests,15.27s |
| Clang18 Debug |14/14 selected integration/failure tests,97.18s |
| ASan+UBSan/leaks |14/14 selected integration/failure tests,519.43s |

The Debug cohort includes session/window/transport/ingest, initialization,
observation, statistics and strict report checks. Selected compiler cohorts
include the new session memory test and actual initialization, session and window
failure sweeps. These are incremental selected scopes; full current209-test,
full compiler/sanitizer and fresh-source acceptance remain open. Prior public
tuple source7's full208-test result is historical evidence of that source.

Detailed current Debug stdout records retained-snapshot exact/one-under peaks
968527 reference /972668 indexed and23/25 persistent snapshot failure positions.
These are fixture-specific measurements of13 rows with8192-byte string bodies,
under testing-runtime ownership; they are not universal production peaks.

Raw failures remain: the first implementation attempted to move a nonmovable
window controller; two build attempts used an unregistered or wrongly prefixed
target; and the first new byte-boundary fixture changed its row cap, legitimately
reducing final vector capacity. Source3 corrects only that fixture from source2
by preserving the measured growth schedule. Original exact byte, lifetime,
rollback and fault assertions remain. No frozen CLI/schema/verifier or executed
proof helper was changed.

## Remaining S05 work

Published SupportJournal event, SupportEpoch transition and PhysicalPreview
derivation arrays still have ordinary outer capacity. Input/run-context nested
members, source progress, transport/reader bodies, window maps/sets/rows/prepared
controls and capture/diagnostic/asynchronous graphs also need funding. The
next-owner inventory records131 candidates across9 selected files and distinguishes
funded aliases and borrowed parameters; it is not an exhaustive ownership audit.
Physical/Delta pending preparation borrows the input update and retains native
source/journal ownership rather than another whole standard input Row.

Authentic operator record/byte reconciliation, complete overflow/churn/byte-limit
acceptance and full native compiler/sanitizer/fresh-source matrices remain open.
Whole-query memory-budget completion and S05 acceptance are **false**. See the
[handoff](../handoff.md), [memory contract](../memory_accounts.md) and
[session guide](../session_lifecycle.md).
