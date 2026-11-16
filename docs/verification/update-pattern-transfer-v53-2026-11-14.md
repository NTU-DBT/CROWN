# V53: source-event transfer and a proved taller condition

This continues the [V52 monitor foundation](update-pattern-runtime-v52-2026-11-14.md).
X01 remains in progress and the implementation goal stays active. The current
user scope permits ordinary
change propagation and exact recomputation for comparisons, top-k and difference;
approximation and parallel/distributed execution are deferred. Multi-query keeps
an interface with independent query maintenance. Licensing checks are deferred
while existing rights/notices are preserved. Those decisions supersede earlier
handoff wording that treated licensing as a technical C04/B01 blocker.

## Implemented result

The conditional analyzer uses actual `CompiledProgram::inputs().base` physical
IDs. An admitted physical event maps through each affected occurrence adapter
to zero or one row. A derivation-count crossing has the same sign as the physical
event. Filters, projection collisions and aliases therefore preserve two useful
cases: insertion-only participating physical sources make all core relations
monotone; arbitrary events on a native-height-at-most-one core have bounded
support propagation. Unused physical tables need no insertion-only declaration.
Public SQL outputs can change nonmonotonically, including synthetic EXISTS
results. No output or whole-session CPU bound follows from source monotonicity.

For other mixed cases the previous direct typed, non-null, no-ignored-column,
self-join-free lifetime transfer gate remains. A native parent/child edge passes
if the entire child subtree is insertion-only, or if the child is a native leaf
sharing the parent's explicit positive raw FIFO scope. Every native edge must
pass. Height-two results retain their prior case; taller success reports
`subtree_edges`. Unknown is an unproved case, with no hardness conclusion.
The [usage guide](../update_patterns.md) connects these cases to the original
paper premises, actual source adapters and generalized-node support propagation.

Taller mixed analysis builds a parent-before-child NodeId order and folds byte
flags in reverse. Checked trees need no recursion or visited set, and IDs need
not be topological. Both vectors use the receiving account's scratch purpose;
the order dies before edge analysis, and flags die before return. Height-one and
all-insertion cases return earlier; height-two uses neither vector. Native leaves
skip a parent-rule lookup. No runtime update implementation, retained row graph,
index, catch or retry layer changes.

Beyond complete binding, Q atoms, C column/term positions, R rules and T checked
nodes require O(C + Q log Q + Q log(R+1) + T) charged visitor/comparison work and
O(Q+T) logical cells in the worst taller case. Source-input scans may stop early.
Allocator framing/capacity, scalar widths and binding bytes have separate caps.
These planning costs are distinct from the proof's amortized support-action
bound, and neither is a constant whole-session CPU or public-delay theorem.

## Proof and counterexample

One Astra Max proof review supplies an analytic sufficient condition and audits
the literal P4 leaf-edge wording. Its sealed proof SHA-256 is
`111e355566f80c2ebac8eaa805e76613e6daef9c026997b496fe8b85876d0a90`;
packet integrity SHA-256 is
`eb79af3ed09f0eebc56317c00158dfbb0efcb3ac30c4fced92042b991267bbf8`.
Root independently received all 18 payloads and 26 source/paper pins and replayed
56 finite parameter pairs from a copy with only its workspace-root path adapted.
The analytic argument bounds actual child-bit/reverse-index visits and generalized
guard propagation, rather than counting only successful survivor changes.

The seven-atom CQ `R(x,y,z,r), S(x,y,z,s), L(r), V(s), T(y,b), B(b), E(x,w)`
has exact minimum native height three. On the specified tree, one global raw
FIFO scope, insertion-only S/L/E/T/B, and mutable R/V admit a full physical trace
with 3n+2m+3 updates and 2mn survivor transitions at internal native node R.
All loading is included; older V lifetimes are withdrawn in birth order. Total
support survivor transitions are 2mn+6n+m+3. This refutes naive local-edge or
ancestor raw-FIFO conditions for that tree. It establishes neither query hardness
nor failure of every alternative plan. The broader component condition in the
proof packet is proof-only and is not implemented.

## Executed verification

Final exact-input Debug checks pass 12/12: reoptimization selection, update
patterns, the existing monitor integration, the new transfer controls, and
selection pattern/pure-link/contract/cache/source/current/binding/resources.
Final ASan/UBSan with leak detection passes 11/11. The full production Release
build with BUILD_TESTING=OFF passes. Native input receipts contain 1,215 paths
and no mid-command changes. Two production paths change; 362 stay V52 bytes.
One test registration is added, for 353 total; predecessor registrations remain.

The new native test uses real compiled normalized SQL with unused physical table
0 and participating physical base 1, while core occurrence IDs differ. Both
backends check filters, projection collisions, aliases, source/native crossing
counters, literal answers, pure/cache/current selection, binary restore and
restored insertion-only erase rejection. Higher mixed ignored-column/self-join
cases remain unknown under FIFO and succeed under all-source insertion-only.
Actual exact search proves the height-three minimum; the retained genuine
candidate prefix does not claim family exhaustion or optimal maintenance cost.

Taller analysis passes exact logical work/cell/payload grants and rejects one
less in each of those dimensions without retained account bytes or partial
reports. All 20 measured persistent C++ new denial points pass. For each backend,
n=m values 1, 4 and 8 produce respectively 8/23/43 source updates, 2/32/128 R
survivor transitions and 12/63/187 total survivor transitions. A monitored window
Session admits the same raw FIFO trace and matches exact native/literal results.
Transition capture is test instrumentation, not a production benchmark.

All intermediate receipts are preserved, including two compile failures: a
renamed shared-fixture table count and a missing explicit recovery-image include.
Final checks use the corrected exact source. The complete 353-test suite,
benchmarks, Clang and moved-SDK matrices were not rerun for V53.

## Human inspection and retained evidence

The static implementation review checks only the implemented sufficient condition,
not the proof-only component theorem. It pins 26 source/context inputs and found
no condition-1 implementation inconsistency. Root separately reviewed later
header clarification and a leaf-lookup skip; final tests include those bytes.
The old review packet remains immutable and does not certify later bytes by
itself. Proof, implementation review, field/link checks and finite executions
retain their different scopes.

The canonical index now covers 769 files, 175,437 lines and 19,693 blocks.
Its 19,220 source-bound contracts cover all 16,787 nonblank blocks; 2,906 blank
regions retain structural facts. V53 receives 24 test-file drafts, adds seven
root-authored helper/registration contracts and amends thirteen semantic cards.
Root corrected an ambiguous enum successor anchor before receipt and describes
R as an internal native node rather than the tree root. Source/anchor/field
checks find zero stale, unused or uncovered nonblank cards. The generated-map
checker passes 140,392 local source/fragment links.

Root packet: `build/verification/update-pattern-transfer-v53-v1`. It retains the
source-event argument, proof receipt and replay adapter, source pins, explicit
successor diffs, card adoption, final native stdout, user scope decisions and
complete command receipts. The V52 parent seal SHA-256 is
`34131e62e5523a64bc4a2a11455aeae3c8817a68a0c4286eb819eab40e5f8b37`.
Final source/evidence acceptance and X01 disposition are recorded in the task
ledger, handoff and V53 progress seal. Broader mixed/SQL FIFO characterization,
whole-session CPU/delay proofs and release acceptance are separate work.

The requirement audit identifies one concrete remaining X01 artifact: a useful
qualified support-action profile connecting the proved source/tree case to
actual enforced premises. Conditional analyzer reports and conservative
`maintenance_bound=not_asserted` diagnostics are useful but do not alone complete
that profile integration. A complete arbitrary-mixed decider or a constant
whole-session CPU/delay theorem is not made an extra X01 requirement. The
stable ledger remains 60 verified, two in progress and sixteen not started;
deferred user-scope cards are retained without being marked complete.
