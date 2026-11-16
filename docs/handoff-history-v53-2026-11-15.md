# CROWN continuation handoff — V53

The implementation goal is active. X01 remains in progress; the stable ledger
has 60 verified, two in progress (A02/X01) and sixteen not started. V53 is useful
bounded progress, not full Refactor/release acceptance. The exact V52 handoff
is preserved in [history](handoff-history-v52-2026-11-14.md).

Current seal: `build/verification/human-inspection-v53-progress-v1.json`.
Its checksum and final integrity result are in
`build/verification/human-inspection-v53-postseal-check-v1.json`; verify both on
entry before edits. Frozen source: `build/verification/human-inspection-v53-source-v1`.
Root packet: `build/verification/update-pattern-transfer-v53-v1`.
The [V53 record](verification/update-pattern-transfer-v53-2026-11-14.md) and
[usage guide](update_patterns.md) explain the proof, costs and evidence limits.
Parent V52 seal SHA-256:
`34131e62e5523a64bc4a2a11455aeae3c8817a68a0c4286eb819eab40e5f8b37`.

The current user decisions in Refactor.md take precedence over earlier research
scope. Comparisons/top-k/difference use ordinary change propagation, with exact
recomputation permitted and actual costs exposed. Approximation is not required.
Keep a multi-query interface with independent query state/results/progress/budgets;
shared algorithms wait until clear. Parallel/distributed execution is deferred.
Licensing checks are deferred while existing rights/notices are preserved; do
not let A02 disposition block C04/B01 technical work. Deferred cards retain stable
IDs without being marked verified. No rights/license files were changed.

The analyzer now checks actual participating PhysicalInput.base IDs for the
all-source-insertion-only case. Bounded zero/one sign-preserving occurrence
crossings also justify arbitrary native-height-at-most-one cores, including
normalized SQL, aliases, filters and projection collisions. Unused physical
tables impose no insertion rule. Public SQL output monotonicity is not implied.
Other mixed cases keep the direct typed/non-null/no-ignored-column/self-join-free
lifetime gate. Every native edge then needs a wholly insertion-only child
subtree, or a native-leaf child sharing its parent's positive raw FIFO scope.
Taller success is subtree_edges; unknown never means impossibility.

Two receiving-account scratch vectors compute taller subtree flags without
recursion or a visited set, and die before the analysis returns. Height-one and
all-insertion return earlier; height-two allocates neither. Runtime/recovery
code is unchanged. No retained row graph, index, catch or retry layer was added.
Actual planning work/cell/byte costs and monitor/journal/output costs remain
separate from amortized support-action proofs and total CPU/delay claims.

One Astra Max proof packet analytically proves the implemented sufficient
condition and gives a genuine minimum-height-three oscillator. All seven
physical tables can share one FIFO scope while 3n+2m+3 full-source updates cause
2mn survivor transitions at internal native R (not the tree root). The other
condition in the proof packet remains proof-only. Root independently replayed
56 parameter pairs. Luna reviewed the implementation and supplied24 usage-card
drafts; root reviewed later target successors, corrected an ambiguous enum
anchor, added7 cards and amended13 existing semantic cards. Packet scope matters:
a copied file is not automatically semantically reviewed.

Current maps cover 769 files /175,437 lines /19,693 blocks:19,220 contracts on
all16,787 nonblank blocks,2,906 blank regions, zero stale/unused/gapped cards.
Generated-map links pass140,392 checks. Final exact-input Debug passes12/12,
ASan/UBSan/leaks11/11, and the production Release/tests-OFF build passes.
All20 persistent analyzer C++ new denials and exact/one-less work/cell/payload
controls pass. The native oscillator matches its closed forms on both backends
for n=m1/4/8. There are353 CTest registrations; the complete suite, benchmarks,
Clang and moved-SDK matrices were not rerun. Final receipts pin1,215 native
inputs;2 production paths change and362 stay V52 bytes. Source snapshot has
4,658 paths. Two earlier compile failures are retained and corrected.

Next X01 acceptance work is concrete: expose a useful qualified support-action
profile connecting the proved source/tree case to actual enforced premises.
Conditional Analysis reports and maintenance_bound=not_asserted diagnostics do
not alone complete that artifact. Keep this a bounded metadata integration;
avoid per-update reanalysis or new runtime dependency on ranking. Do not require
a complete arbitrary-mixed/SQL FIFO decider or relabel the support bound as
constant total CPU/delay. Preserve trusted_restored_checkpoint history wording,
command-vs-physical progress, genuine candidate/height authority, exact source
binding, current-selection monitor checks and replacement continuity. See the
requirement receiving record in the root packet before deciding X01 status.

Keep completed packets, frozen sources, private SDKs and dependency prefixes
immutable. Git is read-only at e369a623517723b3be3ea3e9806779f3c591e7f9; do not
stage/reset/commit. No applicable AGENTS.md was found. Every exec_command needs
sandbox_permissions=require_escalated because the default launcher is broken.
Use PYTHONDONTWRITEBYTECODE=1 for helper imports. Reusable mutable builds:
build/w05-debug, build/w05-sanitizer, build/inspection-build-scope-off-v1.
No native input edits during recorder jobs; every receipt must have unchanged
inputs. User prefers direct code, explicit per-block usage/paper/cost references,
few error boundaries, own-model work and sparing Astra Max use. Simple tasks
may reuse Luna Max. The broader goal stays active after this checkpoint.
