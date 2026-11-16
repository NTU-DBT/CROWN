# P06 resumable exact search preflight, 2026-11-06

Read-only proposal, not implementation or acceptance. P06 remains in progress.
Astra inspected actual P04 producer/checker/budget/IO code and requirements
without edits, builds, tests or status changes while the corrected P04 matrix
ran. The full [Refactor.md](../../Refactor.md) scope remains mandatory.

The central requirement is two real owned continuation machines: producer
search **and independent certificate replay**. Repeatedly invoking the existing
recursive routines from the beginning does not implement resumption.

## Public contract and immutable artifacts

Keep existing minimum_tree and verify_height_certificate strict and compatible
as blocking adapters. An interrupted OracleResult still exposes no selected
tree/minimum/certificate; an interrupted report is never valid. Add a separate
move-only ExactSearch API with create/advance/progress and strict/best_found
policy, plus a standalone CertificateReplay continuation for v1/v2 proofs.

Use privately constructed immutable owning artifacts: ValidatedIncumbent is a
complete P02-checked upper witness only; VerifiedOptimum adds completed matching
independent lower proof; VerifiedInfeasible has completed infinite root proof
and no upper witness. Do not distinguish authority only through a mutable bool
on a common public struct. Strict policy withholds incumbent handles; best_found
may expose validated upper witnesses during interruption. Both continue exact
search and may ultimately produce verified artifacts.

The continuation owns catalog/query/options, scopes, memo, enumeration frames,
witness drafts and replay. Bind exact source metadata, occurrence identities,
constants, ordered head, algorithm/proof version and accounting version once.
Resume accepts no replacement query or caller-edited progress state. Resource
extensions are distinct from immutable semantic options. Factory copying and
initial validation are explicit admission costs outside advance quanta.
In-process continuation state is not O04/O05 durable checkpoint/WAL state.

## Owned producer frames

Replace recursive solve/partitions/build/proof lambdas with owned frames and
explicit stages: metadata, infeasibility check, component children, native root/
symmetry, partition placement, generalized scope, candidate children/dominance,
exact memo publication and return to parent. Each candidate retains its root,
blocks, scope, next child, maximum bound and stable child choices. Advance the
parent's return position only together with a successfully prepared child push.

The producer partition cursor retains dynamic restricted-growth assignment or
placement-stack state: occurrence position, assigned blocks, next alternative,
block counts and whether its last partition was consumed. Resume at the exact
saved position. Publish exact memo values only after alternatives are solved or
safely dominated; a suspension/cutoff is never infeasibility.

Fast paths must also retain scope/incidence/component traversal positions,
laminar checks, node construction and proof normalization. Existing budget-
throwing std::sort/stable_sort comparators cannot save their internal progress.
Replace yielding sorts with an owned incremental ordering cursor (for example
merge positions plus scratch indices); comparators stay pure/nonthrowing.
Meter controlled structural transitions, with scalar/comparison/allocation CPU
remaining separately scoped. Do not restart a whole preprocessing phase on OOM.

## Independent replay and validated incumbents

Replay owns algorithm dispatch, upper validation, independent scopes/classes,
entry validation and duplicate/orbit checks, dependency ordering, current proof
entry, root/partition/child positions and final full-root publication. Keep its
smallest-remaining-occurrence block/complement enumerator independent from the
producer cursor. Convert remaining/select recursion into frames with inclusion
vector, selection position, partial block/complement and child-return stage.
V2 component frontiers and orbit counts also retain exact positions. A claim
enters verified_ only after its complete proof succeeds. Both v1 and v2 semantics
remain unchanged; resumption alone needs no certificate schema change.

A completed root candidate may seed an upper witness before other alternatives
finish. Freeze its complete choice DAG, build its concrete tree incrementally
and run independent P02 validation before publishing a replacement incumbent.
Keep the previous validated handle until the better replacement is ready.
Completed child choices referenced by an incumbent must stay immutable.

For responsive bounded calls, an owned cursor for P02 topology/connectivity/
connex validation is preferable, with validate_tree kept as its blocking
adapter. If an indivisible validation phase is retained, its cost must be
explicit; it cannot be hidden as constant quantum work or a hard time bound.

## Bounds and resource suspension

Start with certified lower zero for empty body, one otherwise. An incumbent
height is only an upper bound. A solved child does not raise the whole bound
while unvisited alternatives may avoid it. General state lower bounds take
the minimum over **all** alternatives, including unexplored ones with universal
bounds. Use independently checked component bounds or completed whole-root
arguments to advance the public lower bound. Coarse universal bounds remain
honest until replay proves more. Never expose a partial table as a valid height
certificate; failed bound attempts do not prove infeasibility.

Separate per-call quantum, cumulative producer/replay ceilings, cumulative active
time and logical frame-depth limit. Preserve separate producer/replay allowances
for strict adapters. advance with zero work performs no transition, allocation,
counter change or proof publication, even in intermediate/completed phases.
Count attempted work on OOM explicitly; do not silently roll resource usage back.

Accumulate monotonic time only inside active advance calls, including exceptions;
user pauses consume no deadline. Time checks occur at safe boundaries, without
hard interruption inside comparisons/allocations. Replace C++ recursion depth
with checked logical frame depth and preserve nonempty depth-limit-zero behavior.
Suspension retains state; resume needs a monotone resource extension or operation
with no cumulative ceiling and bounded grants. Never reset consumed counters or
permit binding/semantic-option replacement through a budget update.

## Persistent OOM and transition publication

Prepare new nodes/capacity/frames privately, then publish with nonthrowing moves,
swaps, scalar changes and node transfers with nonthrowing comparisons. Prepare
a memo node before dropping its completed frame; prepare candidate replacement
before discarding an incumbent. Scratch may remain partial only with an explicit
cursor identifying completed elements. Repeated failure must not advance indices,
lose alternatives, duplicate claims or mark unfinished proof verified.

Return resource reasons as fixed enums/scalars; allocating error strings during
persistent OOM may fail again. Progress access, owning handle copies, move,
cancellation and destruction should not allocate. Keep the old validated
incumbent and certified bound after failure. Invalid proof/binding/internal
invariants are terminal, distinct from recoverable resource suspension.

## File split and acceptance

Suggested ownership: new planner/search.hpp and search_session.cpp for facades,
artifacts and bindings; search_budget.hpp for grants/time/scalars; exact.cpp plus
producer cursor for search; fast_paths for preprocessing/build cursors;
certificate.cpp plus independent replay cursor; verify.cpp/private cursor for
P02; IO for separate progress/best-found serialization. Preserve v1/v2 proof
schemas, the private v1 baseline and frozen P03 oracle. Add progress schema only
if an actual new public artifact needs one.

Force interruption at phase boundaries and interior transitions, not only use
generous budgets. Compare uninterrupted, one-unit and varied schedules against
P03/P04 over feasible small, hierarchy/component/symmetry/pruning, unsupported,
residual and wide/deep cases. Cut replay after search completion: best_found may
return its validated upper witness, strict may not return a minimum, and neither
may return a partial certificate. Resume v1/v2 standalone replay and mutate all
existing proof dimensions. Changing caller-owned input after create must not
change owned state. Reject invalid option/limit updates without mutation.

Inject persistent OOM at every representative transition allocation; recover
and match uninterrupted output. Move/destroy paused handles in every phase,
retain immutable artifacts after facade destruction, reject moved-from access,
and prove repeated zero-work calls inert. Use an injectable internal monotonic
clock to separate active work from pauses. Exercise logical-depth exhaustion
and extension without restarting. Serializer types must not upgrade an incumbent
into a minimum through mutable output fields.

Concrete engineering obstacles are recursive local enumerators, exception-
yielding standard sorts, indivisible validation/export and allocating failure
paths. No new structural theorem is needed. Search-only resumption or replay
that restarts cannot complete P06. This proposal provides no external review or
release signoff.
