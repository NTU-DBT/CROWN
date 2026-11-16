# S05 funded epoch and journal arrays — 9 November 2026

Status: **in progress**. The whole78-card Refactor.md goal remains active at
41 verified /3 in progress /34 not started. Root implemented this checkpoint;
one Luna Max agent performed a read-only caller/test census. No Astra agent was
used. Versioned artifacts live in `build/verification/s05-epoch-arrays-*`.

## Actual ownership

SupportJournal causal events, SupportEpoch membership transitions and
PhysicalPreview derivation capacity now use the original query account through
OwnerAllocator. Retained SupportValueState child flags own a packed bit buffer
under that account too. These are real allocator requests and framing, without
an ordinary uncharged mirror or accounting-only reservation. Pending/no-op result
construction binds its buffers before growth; empty and trace-disabled arrays
allocate no capacity.

OwnerAllocator explicitly propagates the source's existing account, purpose and
attribution on result assignment and swap. Copies fund new capacity under that
same allowance; moves and swaps transfer existing storage without allocating.
Rebinding preserves ownership for packed bit words. Existing maintained tables,
record state and storage keep their nonpropagating MemoryAllocator contract.
The caller-visible vectors have a new allocator specialization; ordinary-vector
DTOs use explicit iterator-range exports. Snapshot/canonical diagnostic flag
types remain separate ordinary DTOs.

Publication and cleanup stay nonallocating. Nothrow moves/assignment are checked
for SupportValueState, SupportEpoch, PhysicalPreview and PhysicalEpoch. Retained
events, transitions, child flags, native tuple values and derivations keep their
original charged ownership after the runtime facade is destroyed. Clearing
tentative arrays can retain capacity until their pending owner closes; those
blocks remain charged. Releasing the last owner frees actual storage and pins.

## Verification scopes

Source2 freezes923 paths and is the tested C++ implementation. Final source3 adds
only current documentation. All14 recorded commands/handles are closed; immutable
progress-v2 binds source hashes, raw receipts, binaries and handoff. The full Debug
build passes all targets with strict warnings enabled. The actual new
`epoch_memory` test passes1/1 in0.28s. The completed integration scopes are:

| Configuration | Observed scope |
| --- | --- |
| GCC Debug |210/210 full registered tests,897.26s |
| GCC Release |18/18 selected checks,16.70s |
| Clang18 Debug |18/18 selected checks,98.49s |
| ASan+UBSan/leaks |18/18 selected checks,538.55s |

The selected18 names cover both storage backends, actual memory ownership,
independent support models, causal journals, prepared/physical/session/Delta
failure paths, initialization and observation. Compiler/fresh-source/full native
acceptance remains separately scoped; no complete S05 matrix is claimed.

Current Debug stdout records retained-history exact/one-under peaks146774
reference /152217 indexed and109/123 persistent allocation-failure positions.
These are two-node binary-string fixture measurements, not universal production
peaks. The new test verifies actual array request lookup, bit-buffer rebind,
account/attribution-preserving copy/move/swap, trace on/off, shared native payloads,
held events/derivations after facade destruction, zero-allocation publication/
teardown, prior-state preservation and same-sequence retry after history release.
Partial failed epochs release their new journal/flag/output allocations.

Independent test models retain ordinary owning reference flags. Eight existing
test files receive explicit DTO/range exports and exact cross-container bit
comparisons. Assertion call counts match preserved preimages; that syntactic
audit alone is not semantic proof. The staged-output allocation-failure probe
still performs an allocating range copy. No frozen schema/CLI checker, old source
map, raw receipt or executed proof helper was changed.

## Remaining S05 acceptance

Constraint validation currently materializes an ordinary Database/Row/string
after-state internally. Operational constraint, bulk initialization and rebuild
temporaries require funding too, independently of retained rollback data.
Transport/reader bodies, nested input/options/progress/window maps/sets/rows and
prepared controls, and capture/diagnostic/asynchronous graphs remain open. The
next-owner inventory distinguishes these from funded aliases and explicit
external exports; it is not exhaustive proof.

Authentic operator record/byte reconciliation, complete overflow/churn/byte-limit
acceptance and full native compiler/sanitizer/fresh-source matrices remain.
Whole-query memory-budget completion and S05 acceptance are **false**. See the
[handoff](../handoff.md), [memory contract](../memory_accounts.md) and
[ledger](../task_ledger.md).
