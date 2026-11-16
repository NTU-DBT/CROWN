# Delta, session, cost, EXPLAIN and native arena inspection

This continuation adds 711 individual usage contracts after the sealed W05 SQL
checkpoint. The current index has 4,808 contracts in 4,228 mapped blocks across
690 maintained files / 158,899 lines / 17,733 blocks. Another 1,916 selected
production callable/type blocks still lack individual contracts; structural maps
are not semantic certification. Test/tool/example gaps are separately inventoried.
The full Refactor goal and release reviews remain active.

Start with the [block index](../code_specs/README.md), [primitive contracts](../code_specs/primitives.md)
and [error-handling dispositions](../code_specs/error_handling.md). Every selected
callable/type region in the six assigned Delta/session/cost/EXPLAIN implementations
has an individual card. Root also reviewed the Delta header's types/API boundaries,
three changed replay-test scopes and the remaining accounted-arena implementation
and public type boundaries. Old unrelated contracts are preserved.

## Two direct code corrections

`DeltaRuntime::profile()` previously defaulted its backend to the reference
label for indexed plans as well. The new regression first failed on that actual
indexed owner. The correction selects one of two static labels from the admitted
immutable plan before either mode-specific return. It changes no update-path
state or allocation. Reference and indexed profiles now agree with their plan in
maintenance and delta modes; detached profile text survives facade destruction.
Private EXPLAIN probes independently check both outer and nested backend labels.

`QuerySession::local_sink_impl()` previously caught every exception only to set
`sink.failed=true` again. That flag is already set before replacement file
acquisition, coverage checks, prefix verification and tail repair. No callee can
clear it. Header/options assignments and the funded File move cannot throw;
`failed=false` is the final success statement. Removing that catch preserves
ordinary File unwinding and the failed attachment latch. Durable uncertainty,
selection locks, journal authority and other required cleanup catches remain.

The [Delta packet](../../build/verification/w05-delta-human-review-v1/report.md)
and [session packet](../../build/verification/w05-session-human-review-v1/report.md)
contain source/caller proofs and separate proposals. Root applied and verified
the two changes; the packet's original unapplied status is historical evidence.
The session restore contract now distinguishes later retirement resumption,
which can fail after native reconstruction/repair, from admission before repair.

## Useful costs and ownership distinctions

| Boundary | Contract made explicit |
| --- | --- |
| Delta output | Public eager startup prepares the complete physical epoch and finite spool. Replay's bounded accepted transitions apply after route preparation; candidate bounds do not bound rejected runs. Finalization and owner teardown remain separate. |
| Cost capture/evaluation | Explicit capture, revalidation, fitting and report operations allocate/scan. Model assumptions and floating fits are separate from exact published integer ratios. |
| Workload hooks | Dense routes are preallocated, but root admit/finish clears or merges whole descriptor slabs: O(D) epoch overhead remains even when sampling is enabled. Snapshot/with-pending copies arrays. |
| EXPLAIN | Serialization is diagnostic work. Nested encoders/temporary labels can overlap final buffers; encoded-byte caps are not peak-heap caps. Per-descriptor ratio lookup can make a full export O(K²). |
| Native arena | Direct handle checks address one owner/slot/generation. Insert copies actual fields/bytes and may grow the directory; memory reports scan the account ledger and high-water slots. Clear visits live rows; final State release can visit every high-water slot. |
| Retained pin | Pin.get reads a retained tuple after deletion without requiring current membership. Ordinary get requires a live handle. Reclaim in unpin is distinct from the caller's later final State release. |

The [cost/statistics review](../../build/verification/cost-stats-human-review-v1/report.md),
[EXPLAIN serializer review](../../build/verification/explain-io-human-review-v1/report.md)
and [root arena review](../../build/verification/arena-accounted-human-review-root-v1/report.md)
pin the detailed contracts and exact source. The arena contribution is static
documentation only; it edits no native implementation or adds a runtime handler.
Existing native arena behavior remains the separately verified baseline.

These ownership, byte-accounting, serialization and failure-phase rules are local
engineering contracts. Exact paper versions and algorithm references remain in
[the review guide](../code_review.md). Paper support/enumeration results do not
prove C++ allocation costs, callbacks, durable publication or every public delay.

## Verification and preserved compatibility failure

| Current gate | Result |
| --- | --- |
| Strict GCC Debug, 18 selected targets | Build passes; 24/24 tests, 89.06 s. |
| ASan/UBSan/leaks, same targets | Build passes; 24/24 tests, 201.87 s. |
| Direct EXPLAIN probes, both profiles | Reference/indexed × maintenance/delta: outer and nested backend labels agree. |
| Source freshness | Final builds, tests and probes use the same 1,127 current maintained input pins, with no recorded input drift. |
| Documentation checker | Source-pinned maps/anchors/references pass; counts apply to the current map, not unintegrated drafts. |

The 24-test cohort covers replay/backend provenance, all five indexed Delta
strategies, session/exception cases, local sink normal/fault/crash/replay paths,
composed EXPLAIN, production/testing statistics exports and allocation failures,
workload statistics, cost capture and fitting. It is a selected regression cohort,
not a full 323-test release matrix or latency experiment.

Receipts are `build/verification/inspection-v8-{build,test}-{debug,sanitizer}-v2.json`
and `inspection-v8-explain-probe-{debug,sanitizer}-v2.json`. Terminal raw LastTest
logs are archived before build-directory reuse. The pre-fix indexed-profile
failure, first build cohort and first 22/24 Debug cohort remain preserved.

The initial quota-prose correction changed one frozen v2 JSON field. Both legacy
byte checks caught it; four retained runtime/session JSON comparisons differ
only at `/mode/runtime/guarantee/output_accounting`. Root restored that literal,
then both full selected cohorts passed. The header/runtime guide now explain
that legacy text is retained for byte compatibility while the actual spool quota
includes account framing. No golden fixture or schema was weakened or rewritten.
See [the spool contract](../delta_runtime.md) and [EXPLAIN compatibility](../observability.md).

Current generation/sink/journal guides also reconcile their old pending-status
prose with the dated verified O04–O06 scope. Next-candidate cleanup names all three
`.ckpt`/`.wal`/`.plan` files; root work uses the actual versioned encoded length,
not one fixed v1 size. This updates current explanations without changing the
older frozen evidence or introducing new recovery behavior.

## Checkpoint and remaining work

Final seal: `build/verification/human-inspection-v8-progress-v1.json`.
Frozen project source: `build/verification/human-inspection-v8-source-v1`.
The implementation/failed-preimage/integration/native-inventory packet is
`build/verification/human-inspection-v8-v1`. The [W05 SQL seal](w05-sql-rows-human-inspection-2026-11-12.md)
and every predecessor snapshot remain unchanged. Active W05 build paths remain
reusable; recorded native hashes identify observed bytes, not immutable paths.

Input-reader and recovery-file drafts are queued separately, including an
unapplied proposal to remove an unreachable final integer-parser guard. They
are excluded from these counts and gates. Further typed-capture/query and
window/image reviews remain independent drafts. W06 integration and the full
individual repository inspection are still open.
