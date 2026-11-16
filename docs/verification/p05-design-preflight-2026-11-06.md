# P05 residual candidate audit: next-card preflight

Design only, 2026-11-06. No P05 implementation or acceptance is claimed. P06 is
still under final verification; its present interfaces were inspected as source,
not declared accepted here. No native sources, ordinary documentation, ledger,
builds or tests were changed/run for this preflight. This file is a design packet.

## Sequencing decision

P05 is enabled by its actual dependencies P02/P03, both verified. P04 is verified;
P06's new continuations improve the proposed fallback but must finish acceptance
before the next native edit. P05 completes the remaining planner prerequisite for
P07 (P04/P05/P06), which in turn enables alternative-plan/CBO work.

S04 depends explicitly on S03 **and A02**. S03 is verified; A02 remains in progress
because the distribution-license/provenance disposition is unresolved. S05 depends
on S03/S04, so switching directly to S05 does not avoid that dependency. Independent
index design and interface review are possible now, but must not relabel A02 or
S04 complete. Prefer P05 as the next implementation card after P06 acceptance;
resolve A02 in parallel at the owner level before committing to adapted indices.

S04 is also a substantially different integration surface: current ReferenceTable
owns arena handles/pins, journal rollback/commit and revision-sensitive live/bucket
cursors. An optimized backend must preserve those behaviors across the existing
runtime, rather than replace a hash container locally. This preflight does not
claim S04 blocked forever or that independently written code needs legacy copying.

## Source audit and provenance boundary

The immutable P2 source inspected for this preflight is
[arXiv 2603.14754v1](https://arxiv.org/html/2603.14754v1), specifically Definition
2.9/2.10, Algorithm 1 and Appendix B. Its algorithm fixes the ear set before a
round; a deletion requires another remaining anchor. The residual retains the
surviving occurrences and their induced head. Appendix B's attachment argument
and one-level height conclusion are the claims to audit, not an accepted
certificate rule. Its stated query setting is self-join-free; a structural
implementation over occurrences must not import its hardness conclusions for
self-joins. This version-specific inspection says nothing about later revisions.

Concrete algorithms below are independently specified from Refactor.md sections
5.1-5.4 and the repository's checked tree semantics. No legacy code is copied or
adapted. Existing provenance pins remain CROWN
e369a623517723b3be3ea3e9806779f3c591e7f9 and DynaGox
c6811db68a34ab3b32722968c4e1e821f730c5ac. docs/source_baselines.md records the
notice inventory and open A02 disposition; neither pin supplies blanket reuse
permission. No additional legacy implementation inspection was needed here.

## Deliverable: audited residual provider with explicit exact fallback

Do not attempt to certify the disproved rounds-plus-one rule. Implement actual
frozen-ear records, induced residuals, candidate reconstruction, a proof-status
report and complete-search fallback. That satisfies P05's explicitly permitted
candidate-provider outcome without substituting a mere wrapper around exact search.

The provider has three independent claims:

- Reduction trace replay: the recorded ears/anchors/deletions obey the declared
  frozen-round definition. This proves trace fidelity, not tree optimality.
- Candidate validation: P02 checks every emitted full-query tree. This proves
  an upper bound, not a minimum or completeness of the reconstruction family.
- Exact authority: only P06 completed independent proof replay supplies a
  VerifiedOptimum/VerifiedInfeasible for the ORIGINAL query.

## Frozen-ear implementation

Use original occurrence and variable IDs as stable identities. At a round start
with live occurrence set M, derive scopes from complete atom terms and compute:

- V(M): union of their scopes.
- F(M): original unique head variables intersected with V(M).
- U(M): variables appearing in exactly one live occurrence (not one distinct
  scope/table; repeated positions within an atom count once).

For every ordered pair e,a in M with e != a, record eligibility under the two
Refactor.md ear conditions: shared part e minus U contained in a with no unique
free variable; or that shared part contained in a intersect F. Record which
condition(s), shared part, unique part, and all eligible anchors. Freeze this
entire relation for the round. Never re-evaluate U/F or discover new ears during
the same round.

Deterministic deletion schedule: repeatedly choose the smallest original ear ID
that has any frozen eligible anchor still live, choose its smallest live anchor,
record the deletion and chosen anchor, then remove ONLY that ear. Stop when no
frozen pair remains live. This makes order reproducible without claiming every
schedule is equivalent. Never delete the last occurrence: anchors differ from
their ears and must remain at that deletion instant. Mutual-ear cycles leave at
least one representative; do not remove an entire strongly connected class.

Each deletion points to an occurrence deleted later or retained at round end, so
reverse deletion order always restores its recorded anchor before its ear.
Store all initial eligible anchors as well, allowing a different compatible
restored anchor without erasing the source trace.

Compute the next induced query/head only after the round. Check q-hierarchy
before starting another round. If a nonhierarchical residual makes no deletion,
record reduction_stalled and invoke fallback; do not loop or infer unsupported.
The original nonempty set decreases on productive rounds, bounding their count
by m-1. Empty body is the existing height-zero special case, not an ear round.

Query views used with P02/P06 require dense local atom/variable IDs: create an
explicit bidirectional map, preserve all surviving atom terms/constants/table
references and retain ordered head positions whose variables survive. Do not
validate a partial tree against a full query missing native occurrences. Retain
original scopes and identities in the trace; never delete mutable atoms from
the actual execution query.

## Terminal residual and current reuse seam

P04's height-one implementation is now owned inside ProducerMachine coroutines;
fast_paths.hpp explicitly has no callable blocking hierarchy helper. Do not
pretend that the old hierarchy_tree function is still available.

Use a small independently implemented incidence-set q-hierarchy recognizer for
round stopping. At the terminal induced query, run owned P06 ExactSearch to obtain
its checked height-one tree via existing P04 machinery. This genuinely reuses the
implementation and avoids exposing producer internals. A residual recognized as
q-hierarchical but independently solved above one is an invariant failure, not a
candidate to accept. Alternatively, extract a common producer-side hierarchy
cursor later; the independent P02/checker must not start sharing its logic.

Map that residual witness back to original occurrence/variable IDs, then restore
deleted occurrences in reverse round and reverse deletion order. Its minimum
certificate applies only to the induced residual; never transport it to the
original query.

## Concrete sound reconstruction rules

For one restoration, let e be its full scope, T the current valid tree, D its
currently restored occurrences, F' the original head intersect U(D union {e}),
and S = e intersect U(D). All drafts are private; validation uses this enlarged
induced query/head. Enumerate deterministic native placements before grafts.

Rule A: attach e as a native leaf below a native node a containing S. Running
intersection holds because all already-present variables of e occur at a.
Cover is extended once, Guard is unchanged and Above is unchanged. Restoring
the head only enlarges F, so old reachable output coverage cannot be lost. If
e introduces new free variables, require a in maximal connex for F' and S
contained in F' so those new variables become reachable. A recorded surviving
anchor contains S: variables frozen unique to e cannot occur in D, and every
other e variable lies in its frozen shared part. Check the conditions explicitly.

Rule B: attach below an existing generalized node g only when S is contained
in scope(g) AND scope(g) is contained in e, with the corresponding new-head
reachability condition. These imply scope(g)=S, preserve Guard and Connect,
and keep the new leaf native. A generalized 'connex anchor' alone is insufficient.

Rule C: add a generalized fork above a subtree rooted at t, with native e as
the other child. Set K=S and require S contained in scope(t). If t has parent p,
require p generalized and scope(p) contained in K; no generalized insertion is
allowed below a native. New edges are p->K, K->t and K->e (or K is the new root).
K is guarded by both children; an old incoming separator is preserved through K
because a generalized parent is contained in K. All existing e variables connect
at t/K. Check output reachability under F' and then P02-check the entire draft.

Rule C directly handles the augmentation fixture P(a,z,x),R(a,z,y),L(x),U(y),
S(a,c), head {a,c}: after the private guards are restored, wrap generalized {a,z}
under a new generalized {a} sibling of S. Do not attach S beneath P/R and assume
new output c remains reachable. Guard-only local checks cannot establish Connex.

These rules are a deliberately incomplete candidate family. Keep a bounded
deterministic frontier of valid partial trees if desired; recording a frontier
limit makes its incompleteness explicit. A one-path greedy choice is also sound
but may need fallback even when another attachment works. Preserve rejected
draft diagnostics for audit, never as public executable candidates.

If no rule produces a valid extension, invoke P06 complete search on the enlarged
induced query, obtaining a restructured checked tree before continuing. At final
level this is full-query fallback. Generalized reconstruction failure must not
return unsupported, and a post-hoc rejection with no fallback is not the specified
repair route. Budget exhaustion retains the exact continuation and an honest
incomplete status; no automatic budget extension is allowed.

If exact repair proves an intermediate induced query infeasible, that certificate
is NOT a certificate about the original query. Abandon that partial reconstruction
and run complete search on the full original binding. Likewise, accepting the
original with P01 does not authorize asserting every arbitrary restoration prefix
admissible without a checked witness. Only full-original-query VerifiedInfeasible
may justify an original-query unsupported result.

Even successful reconstruction establishes no minimum. An exact-required policy
must run full-original-query P06 proof to completion. Candidate policy may return
the P02-checked upper tree without that claim. Exact fallback need not be seeded:
current ExactSearch has no public candidate-seed API. Do not add a hidden seed or
alter its certificate algorithm merely to accelerate P05.

## Proposed types and ownership

New include/crown/planner/residual.hpp, with a move-only owned ResidualSearch and
fixed-enum progress, can follow P06's advance/raise_limits/cancel discipline:

```cpp
enum class ResidualMode { candidates_with_exact_repair, require_exact_original };
enum class CandidateOrigin { hierarchy_seed, leaf_reconstruction,
                             generalized_graft, exact_repair };
enum class ResidualProofStatus { trace_only, checked_upper_only,
                                exact_original_verified };
struct EarWitness { std::size_t ear, anchor; unsigned conditions; };
struct EarDeletion { std::size_t ear, chosen_anchor; };
struct ResidualLayer { /* owned members, F,U, eligibility, deletions, maps */ };
class ResidualCandidate { /* immutable checked full-query tree + provenance */ };
class ResidualSearch {
  // create(Catalog,Query,ResidualOptions); advance(WorkQuantum); progress();
  // candidate(); exact_original(); trace(); raise_limits(); cancel();
};
```

Do not expose partially validated candidates. Candidate payload needs original
exact catalog/query binding, actual checked height, origin/trace version and
explicit incomplete reconstruction-family status. Round count is diagnostic;
it is not a lower bound, upper bound or certification field. Any measured height
gap is reported only against a VerifiedOptimum for the same original binding.

Current ValidatedIncumbent constructors are private and ArtifactFactory lives in
search_session.cpp. Two implementable choices exist: a dedicated privately
constructed ResidualCandidate owning P02 CheckedUpper via internal validation,
or a small public validation facade shared by P05/P07. Prefer dedicated authority
now to avoid widening P06 mid-acceptance; do not reconstruct a fake VerifiedOptimum
or use const_cast/public certification flags. P07 can later define the common
CandidateProvider interface over both validated upper types.

Use current incremental independent ValidationMachine internally to validate
drafts, preserving creator/checker independence. No public mutable report or
CheckedUpper setter. Public candidates are only FULL original-query trees;
partial/residual witnesses remain internal and visibly differently bound.

Frozen-layer metadata can be O(m^2) anchor edges per round and several rounds;
give explicit retained-record/payload and work caps. Candidate frontier/tree copies,
induced-query copies and exact fallback owners are additional charges. Limit
expiration means resource stop, not no reconstruction exists. Allocate draft nodes,
trace records and publication handles before nonthrowing state/index advancement.
Persistent OOM must preserve prior candidates and retry the same deletion/graft;
do not recompute earlier rounds silently. No constant-delay/scalable-minimum claim.

## Audit cases and independent checks

Mandatory exact fixtures: the seven-atom and nine-atom Section 5.3 examples have
one productive frozen round, height-one residual and original minimum THREE.
Assert no rounds+1 exactness field, no emitted invalid height-two tree, and successful
P06 fallback when reconstruction cannot supply a valid full tree. Validate the
known height-three witnesses and exact certificates separately. Preserve the
renamed/permuted fixture; deterministic traces can differ by ID ordering while
height and full-query semantics remain invariant.

Add the wrong-anchor L(x,a),A(x,a,b),B(x,b,c),C(x,c,d),U(x,d),E(x,w) fixture:
restoring E under A with a residual B root must fail output reachability; a
compatible B attachment succeeds when the rest of the tree is restored correctly.
Add the generalized {a,z}->{a} augmentation case and an explicit generalized
parent whose scope is not contained in the proposed ear (Guard rejection).

Independent test reference computes frozen U/F and every eligible pair directly
from sets. Replay each recorded deletion against the frozen relation and current
live set; require chosen anchor distinct/live, eventual round maximality, induced
head equality, stable original identity and no omitted restoration. Enumerate
alternative valid deletion schedules on tiny queries to test mutual anchors;
do not assume schedule-isomorphic traces as an implementation shortcut.

Include a query where deletion creates a NEW ear that must wait for the next
round; duplicate scopes on distinct tables/self-join occurrences; empty/nullary
scopes; Boolean and repeated heads; constants/ignored columns; singleton/empty
body; disconnected components; q-hierarchical zero-round case; stalled/inadmissible
input and >64 variables/occurrences. Synthesize small free-connex bodies/heads,
compare original and residual heights with frozen P03 where feasible and P06
otherwise. Every candidate must independently pass P02; no requirement that an
incomplete candidate family itself always achieve the optimum.

Fault/lifecycle cases: yield inside eligibility scans, layer publication, reverse
restoration, graft copies, validation and fallback replay; repeated zero grants;
same-owner allocation-failure retry; cancelled/destroyed providers with retained
candidate handles; resource stop after a good candidate; corrupted anchor IDs,
induced head/maps, guard scope and fake proof status. Exact-required output cannot
publish a minimum when only original-query proof replay is unfinished.

## File ownership and practical decisions

- Residual producer owner: new residual.hpp/residual.cpp and private layer/graft
  cursors. No changes to exact recurrence or v1/v2 certificate semantics needed.
- Independent audit owner: tests/reference/residual_oracle.* and residual tests;
  do not share eligibility or graft helpers with producer.
- Integration owner: CMake, bounded residual IO/diagnostics if exposed, authority
  bridge to P02, documentation and eventual task evidence. Existing public strict
  CLI need not change; an explicitly named audit command is optional.
- Proof reviewer: source-version audit, soundness arguments, counterexample
  disposition and limitations. Candidate-family completeness is NOT established.

Outstanding implementation choices, not reasons to ask the user again: greedy
versus bounded multi-candidate reconstruction; dedicated candidate authority
versus reusable validation facade; whether to expose a CLI trace now. The actual
blockers to acceptance would be missing frozen trace artifacts, skipped fallback,
failure to restore original identity/head, invalid emitted trees, or uncertified
height claims. A novel complete optimized reconstruction theorem is not required
to complete P05's explicitly allowed audited candidate-provider scope.
