# V50: physical-row lifetime FIFO foundation

X01 is **in progress**. Its first runtime foundation now enforces actual
full-row lifetime FIFO in windowed sessions, with precise rejection before
publication. Insertion/mixed declarations, compatible-plan analysis, live
qualified profiles and complete X01 acceptance remain open. See
[usage and cost](../update_patterns.md) and the [ledger](../task_ledger.md).

## Implementation and source boundary

WindowFifoPolicy preserves original label modes 0/1 and appends physical-global
and physical-per-table modes 2/3. Existing count IDs already retain the start
order of live full-row lifetimes, even after their first labels disappear.
Explicit last-reference removal checks that actual order; metadata-only label
removal remains free of an unnecessary label-front condition in physical modes.

Whole-watermark preflight uses one query-account integer-counter vector.
Global counts start sorted; per-table mode sorts by table/birth ID. Zero
counters form a group prefix, so the predecessor check precisely identifies
oldest-live final removals. The complete deadline-order sequence is checked
before any label, row or watermark progress changes. Existing prepared-token
publication and Session failure latching supply the commit/reject boundary.

The new path adds no retained row graph, persistent index, callback, catch or
independent allowance. One physical watermark uses O(D) transient counters,
O(E log D) lookup work and existing label lookups; per-table mode adds O(D log D)
sorting. Explicit per-table final withdrawal can scan D counts. Initialization,
comparisons, processing and future removals are charged before the first effect.
Actual scratch capacity/framing consumes the original query cap; retained
window byte limits and later native/output costs retain their separate scopes.
This is not a whole-session constant-update bound. Legacy modes create no
physical-counter vector, and empty-expiration watermarks skip it.

The policy byte keeps its layout and values 0/1; new readers admit 2/3 and older
readers reject them. Existing birth IDs survive native/Session/image restore.
Human EXPLAIN and run-context JSON share exact names for all four policies;
the v2 report schema admits them. The formatters authenticate no arbitrary DTO.

Ten native-input files change: five production paths (window header/runtime,
Session image codec and two formatters), four unit-test sources and the report
schema. The other 350 production paths and CMake registrations remain V49 bytes.
No plan/certificate authority or default height policy changes.

## Native verification

GCC Debug builds pass. The six targeted groups are window_checkpoint,
session_image, session_checkpoint_window, window, window_memory and
observation_run_context. Their final successful receipts are the initial six-test
run plus the three updated groups from run v2 and the corrected Session group
from run v3. Production code stays identical across these test revisions.

ASan/UBSan with leak detection passes **8/8** on the exact final native inputs:
those six groups plus session_image_grant and session_checkpoint_window_grant.
The production Release build with tests disabled also passes. No whole-current
349-test matrix, Clang build, moved SDK, new benchmark or speedup is claimed.

The independent birth-list/full-state reference exercises 120 proposals per
physical policy/backend: 480 total, 376 accepted and 104 rejected. Rejected
proposals preserve exact window/native canonical state and current query-account
memory; every prefix compares labels, full-row counts, watermark and native
unary query output. Focused controls reject an early-metadata/later-physical
watermark violation before its first effect; allow out-of-label-order duplicate
removal; sweep four persistent preparation allocations per combination and
retry; and check exact/one-under command work without publishing a prefix.

Actual Session controls confirm first window_fifo_violation, then sticky
input_failed on retry, with unchanged source positions, rows and physical epoch.
Native and Session/image matrices now cover all four policies on both backends
and created/running/paused/stopped states. They retain orphaned birth IDs and
exact next updates; the admission-grant variants check original allowance reuse.
Unsupported enum value 4 fails encoder preflight without allocation. Actual
run-context export retains the new policy names after session drop.

All terminal commands/logs are preserved under `build/verification` with prefix
`x01-physical-fifo-`. Three intermediate failures are retained: a requested test
target was absent in the tests-OFF Release directory; one new test's integer
literal list triggered -Wsign-conversion; and the initial sticky test expected
the first FIFO error twice. The first required the testing build; the latter
two were corrected in tests. Their receipts are not passing evidence. No native
input changed during any recorder-wrapped command, and no approval was rejected.

## Review and inspection evidence

The Luna entry audit rechecked all 4,621 current/frozen V49 source paths and
63,984 protected artifacts before edits. The previous turn was concrete progress:
2,148 usage cards were received and V49 sealed/postchecked.

The independent code review is
`build/verification/v50-physical-fifo-code-review-v1`: bounded PASS with all ten
changed files pinned, no open findings, and no native execution by the reviewer.
The Astra Max audit is `build/verification/v50-pattern-proof-audit-v1`, pinned to
24 copied source files from V49 and the exact retrieved P4 author paper. It
confirms the label/physical distinction, the zero-prefix argument, lack of joint
FIFO from per-table declarations, non-injective projection obstruction and
the Refactor §5.3 problem in literal Trim reconstruction. It explicitly excludes
acceptance of changed successor code and broader mixed-pattern theorems.

The current index has **755 files /173,036 lines /19,474 blocks**. Its 19,004
contracts cover all 16,573 nonblank blocks; the original 2,901 blank regions
retain matching content. Twelve new cards cover all new blocks, 17 existing
contracts receive semantic updates, 12 equal-body spans are reanchored, and
362 hash-only changes preserve their original authors. All other old records
are unchanged. Root reviewed the 20 changed-block records, all 13 moved/preamble
span contexts and the twelve new scopes. Map generation/checking passes with
zero stale/unused/duplicate bindings or selected callable/type/inline gaps.
These are scoped usage explanations, not a global semantic proof.

The receiving packet is `build/verification/update-pattern-planning-v50-v1`.
The frozen checkpoint/postcheck are
`build/verification/human-inspection-v50-progress-v1.json` and
`build/verification/human-inspection-v50-postseal-check-v1.json`.
The [handoff](../handoff.md) identifies exact receipts and remaining work.

The ledger remains 60 verified, two in progress (A02/X01), 16 not started,
78 total. V01/V02 and bounded V33 W06 keep their explicit historical/current
premises. B05 stays attached to its accepted finite V48 experiment cohort.
Remaining extensions, A02-dependent work, R2 retirement and release gates keep
the full Refactor goal active.
