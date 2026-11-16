# Compact logical support adoption — 8 November 2026

S05 remains in progress. Full Refactor.md counts remain 41 verified, three in
progress (A02/S05/O06), 34 not started; all 78 cards remain in scope.

## Maintained implementation

Actual SupportRuntime state uses AccountedPlanStorage and compact native tables
for the reference and indexed backends. Frozen node/edge/enumeration programs,
logical propagation values, metadata/undo and retained journal tuple pins use the
existing query account. A bounded construction-only projection memo preserves
canonical projection aliases. Node/edge/program arrays and memo reservation admit
metadata word work under the original finite native grant. No source projection
pointer memo survives construction.

SupportJournal records retain AccountedTupleArena::Pin; tuple() borrows a native
AccountedTuple. relation_layout(node,role) exposes its authoritative borrowed
frozen token. The journal record/writer arrays, pending/transaction controls,
cursor/frame/condition/lookup buffers, probe child arrays and view controls/patch
arrays also use the same account. Explicit row/scalar exports support existing
get/result/snapshot/trace/delta/report boundaries. Native direct lookup assembles
borrowed scalar views in funded scratch and creates a compact owning key.

## Resource and failure checks

A pre-existing rollback assertion required exact total requested bytes after
failure. Native arenas/directories intentionally retain admitted reusable
capacity. The preserved diagnostic shows exact canonical state restoration with
23,088 bytes before and 25,186 afterward. The revised assertions require exact
prior canonical state, unchanged compact tuple payload ownership, no leaked
retained records/pins and a stable warmed footprint through 40 churn cycles.
Rollback under fail-every-allocation still requires zero allocation calls.

The final direct Debug memory run passes both backends. Fixture support peaks
are 45,896/51,106 bytes, cursor peaks 35,445/39,244, and physical-source peaks
37,565/41,065 (reference/indexed). Exact and one-byte-under boundaries pass;
failed cursor startup preserves all existing read leases and releases partial
control/frame allocations, and a smaller retry succeeds. The support sweeps fail
all 110/124 allocation positions and physical integration all 126/142 positions,
then preserve the prior state and admit valid retry. Retained owners release to
the account controller after the final journal/cursor/pin is dropped. These are
specific testing-runtime fixtures, not full query or production peak estimates.

Journal test images now use explicit exported rows and retained native layout
handles. Each runtime validates its native relation token; separate runtimes
compare native descriptors and values. Existing independent membership/join/
rollback oracles and trace assertions remain active.

## Scoped verification

All **48 selected tests** pass GCC Debug/Release, Clang18 Debug, and GCC
ASan+UBSan with leak detection. The original sanitizer timeout remains unchanged.
All final builds have zero compiler warnings. These are incremental live-source
checks, not fresh frozen-source or full compiler/native acceptance gates.

| Configuration | Selected tests | Elapsed seconds |
|---|---:|---:|
| GCC Debug | 48/48 | 117.50 |
| GCC Release | 48/48 | 14.96 |
| Clang18 Debug | 48/48 | 91.26 |
| GCC ASan+UBSan/leaks | 48/48 | 503.52 |

The selection includes native memory contracts, direct runtime byte limits,
independent support models, journals, prepared epochs, result/fragment/epoch
cursors and failures, indexed budgets and all selected delta schedules, physical
updates, initialization/scale/failures, sessions, observation, owner statistics,
original strict report checks, and physical/support CLI fixtures. Nine focused
Debug tests first passed in 2.15 seconds before the final metadata-word tightening;
the complete final matrix includes those names and the final cursor-cap test.

All raw failed and successful attempts and source preimages v1–v7 remain under
build/verification with the s05-compact-support prefix. Current records are
checkpoint/matrix/root-review/inputs/current-source-audit v1, the immutable seal
helper, full per-test output, mutable jobs v1 and continuation next-plan v9. The
selected-tests-v1 file records exact names/targets. All native processes are
closed. Original executed checkers and pinned report baselines were not edited.
The actual native implementation stayed unchanged through the final matrix;
documentation was finalized afterward.

Root implemented, reviewed and executed this cohort. A bounded read-only Luna Max
inventory was the only delegation. No Astra was used. A separate next-step overlay/
binding draft passed strict C++23 syntax-only, is unapplied, and has no runtime
acceptance; its manifest records the exact base hash and required further work.

## Remaining ownership and acceptance

Original PhysicalPlan/catalog/query/SQL metadata, metadata/output descriptors,
public get/result/snapshot/trace and child-flag exports, view overlay map nodes/
Row keys, fixed binding maps, initialization scratch, delta/session/queues,
captures and output/rebuild buffers remain open. Standard map lifetime
classification retains its O(outstanding account allocations) diagnostic cost.
The unused legacy work alias remains in the context implementation; actual
support and physical operations now select the canonical native grant directly.
Full compiled-operator reconciliation and native/source/compiler acceptance are
still required. This step does not establish a complete query memory cap or a
uniform runtime delay bound.
