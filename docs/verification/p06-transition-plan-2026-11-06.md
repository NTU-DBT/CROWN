# P06 temporary API and transition proposal

Design assistance only, 2026-11-06. No native source edits, builds, tests, or
acceptance claims. Companion header: [API proposal](p06-api-proposal-2026-11-06.hpp). This expands
[saved preflight](p06-design-preflight-2026-11-06.md) against current P04 source.

## Public contract decisions embodied in the proposal

1. Existing oracle.hpp strict APIs and IO remain compatible. Production search
   uses v2; standalone replay accepts v1/v2. No new certificate schema version.
2. Owned pimpl continuations are movable, exclusive single-caller objects.
   They have no callbacks and may transfer threads only with exclusive ownership.
3. Distinct immutable upper/optimum/infeasibility handles carry authority through
   private construction. Public legacy aggregate structs remain compatibility
   objects, not authority tokens. Shared immutable payloads outlive continuations.
4. Strict policy withholds incumbent handles; it may report scalar upper bounds.
   Best-found returns only a fully P02-checked incumbent. Policy is immutable.
5. All active phases, including witness validation and proof export, can yield.
   Factories only own/validate inputs; their copies and validation are explicitly
   outside advance quanta. JSON parsing/encoding is separate allocating IO work.
6. Zero-work/zero-time quantum returns an ephemeral stop reason without changing
   any stored phase, last-stop reason, counter, timestamp, allocation, or result.
7. Total resource ceilings can be raised monotonically without resetting usage.
   This does not allow changes to catalog/query/proof algorithm/policy.
8. Persistent OOM is a resumable resource stop with fixed-size status. Unknown
   exceptions or invariant failures are terminal; nothing becomes a proved result.

## Ownership graph

ExactSearch::Impl owns immutable BindingData + fixed SearchOptions, mutable
ResourceLedger, ProducerMachine, optional WitnessMachine, optional ReplayMachine,
and published shared immutable artifacts. There is no user-supplied WorkBudget
reference or borrowed input. ArtifactFactory is private implementation machinery.

ProducerMachine owns FastPathMachine, dynamic scope/component tables, metadata
cache, immutable completed Choice records, frame stack, candidate drafts, and
ProofExportMachine. A Choice references only immutable completed smaller-state
choices, never an active frame. Frozen complete root candidates therefore remain
valid while search continues. WitnessMachine builds a separate concrete tree and
runs the independent P02 ValidationMachine before replacing a published incumbent.

ReplayMachine owns an immutable proof payload and its independent scope/classes,
provided claims, verified claims, dependency order, metadata cache and replay
frames. It does not call producer metadata/partition/hierarchy helpers. Immutable
binding/tree/proof payloads can be shared without sharing mutable algorithm state.

The result control block must be allocated during a preparatory phase. Completion
publication consists only of shared-handle moves and scalars; no allocation follows
the point that sets result=verified_optimum/verified_infeasible.

## Granular producer machine

Top-level phases: admitted -> extract scopes/head -> components -> hierarchy
analysis/construction -> exact search when needed -> witness build/validation ->
proof export -> independent replay -> final publication. A complete improving root
candidate schedules witness validation immediately; afterward producer resumes its
saved position. Final proof creation must not depend on mutable incumbent drafts.

Every nested scan retains an outer and inner index or stable iterator, plus a
small operation stage. Map/set iterators are used only where insertion preserves
them; no vector references survive growth. Frame references use stable owned
nodes or indices and are reacquired after a vector reserve/push.

SearchFrame:

- Key (members, generalized_allowed, connex_reachable), stage.
- Metadata request/return state.
- Best complete choice, next root index, equal-full-scope root representatives.
- Current producer partition cursor; boundary/shared-scope check cursor.
- CandidateFrame: root kind/id/scope, blocks, next child, current max height,
  immutable completed child choices, pending child-return stage.
- Component special-case cursor (only full-query root with both flags true).
- Exact-result publication state.

Stages: memo_lookup -> metadata -> blocked_head_check -> component_child or
native_root -> native_partition -> boundary_check -> candidate_child ->
candidate_finish -> next_partition/root -> generalized_partition -> shared_scope
-> guard_check -> candidate_child -> finalize_exact -> return_to_parent.

Publish a memo value only after all alternatives are considered or safely
dominated. A budget stop, OOM or dominated candidate is never infeasibility.
P04 root-cost/max-child pruning and scope symmetry retain their existing proofs.

ProducerPartitionCursor owns the occurrence list, assignment vector, placement
stack (position, next existing/new block), block counts, and yielded/consumed flag.
Each advance performs one placement, backtrack, element copy or yield transition.
Zero remaining occurrences yields exactly one empty partition. Resuming an already
yielded partition does not invoke its consumer twice.

FastPathMachine owns union/find walk indices, scope and incidence construction,
component grouping, incidence class formation, hierarchy pair/intersection/subset
cursors, least-parent selection, and node/edge construction indices. No stage
restarts from its beginning on a normal quantum stop or allocation failure.

Replace budget-throwing std::sort/stable_sort with owned bottom-up merge cursors:
source/destination index arrays, run width, start/middle/end, two input positions,
output position. Comparators never throw/yield. Stable ties preserve deterministic
P04 order. A merge result is installed only after a complete pass. Copies of
variable-width keys have explicit copy cursors where needed; standard map lookup
is an abstract operation with separately documented comparison/allocator costs.

WitnessMachine owns a frozen root Choice, traversal frames, partially built tree,
scope/node/child copy positions, and P02 ValidationMachine. Freeze is prepared
before altering the producer return stage. A validated replacement improves or
ties only according to the declared deterministic selection policy; old handles
remain immutable and valid. Never export a partly constructed tree.

## Independent validation and replay

Refactor validate_tree into an internal ValidationMachine and a blocking public
adapter. Preserve its independent algorithm: occurrence cover/full scopes;
topology/parent counts; root reachability; separator/guard/Above/height traversal;
per-variable induced connectivity; maximal connex; optional supplied claims.
Each traversal owns its frontier and indices. ValidationReport construction is
private and resumable. Failure diagnostics can initially be fixed-size rule/ID
records, formatted to strings only in the allocating legacy adapter.

Replay phases:

- Dispatch algorithm, establish shape relation between minimum and upper tree.
- Validate upper witness independently; no lower certificate is trusted yet.
- Build scopes/head and v2 full-scope classes independently.
- Read each claim, check sorted unique indices/flags/ranges, normalize orbit key,
  reject duplicate ordinary(v1)/orbit(v2) claims, retain its immutable index.
- Incrementally stable-order claim indices by occurrence count.
- Prove the next claim completely, publish it into verified_, then move forward.
- Check the full-query root key/bound; prepare/publish CheckedCertificate.

ReplayClaimFrame owns current state/target, ports request cursor, native root
index, replay partition cursor, group boundary checks, shared-scope pair/variable
cursors and child-bound maximum. Bound one and blocked exclusive-head claims
use current safe rules; v2 independently recomputes whole-root components.

ReplayPartitionCursor remains independent: choose the block containing the
smallest remaining occurrence, enumerate inclusion choices, build block and
complement, descend on complement. Its stack owns remaining indices, inclusion
vector, select position/next branch, build position, child-return and visit flags.
Do not reuse producer restricted-growth enumeration or its memo metadata.

V2 orbit cursor retains per-class counts and canonical-member copy/sort positions.
V2 component cursor retains independently built incidence, visited variables,
seen occurrences, frontier and current component. Missing claims still supply
one. Provided-but-not-yet-verified dependencies remain invalid as today.

Pause at any point leaves the current claim outside verified_. No partial claim,
root proof or certificate is exposed as checked. V1 stays exhaustive without
component/orbit shortcuts; v2 retains precisely P04 semantics.

## Bound interval and result publication

For a nonempty unresolved family L=1; empty body L=0. U exists only for a complete
P02-validated tree. A solved child does not raise whole-query L. An alternative
has lower=root_cost+max(child lower); a state needs the MINIMUM over all alternatives,
including unseen alternatives at universal bounds. Do not omit unseen choices.

First implementation can retain universal L until independent replay finishes.
For disconnected roots, already independently proved component bounds may raise L
through the existing maximum rule. A general stronger root bound requires a full
independent root-bound pass. Such progress can remain internal; no new public
partial-certificate schema is required. Search-generated values alone never raise
certified L. L=U does not publish an optimum until required upper/root checks and
artifact preparation are complete. Infeasibility requires a complete infinite root
proof and has neither a finite interval nor an incumbent.

ExactSearch snapshots return immutable handles, not references to mutable memo.
Legacy minimum_tree never returns the best-found handle on a resource stop.
Legacy serialization still requires independently verified final results.
Separate progress IO includes exact binding, policy, evidence kind, L/U, phases,
budgets/counters and optional validated tree, with certificate=null while unfinished.

## Resource ledger and clock

Before one machine action: check quantum, cumulative phase ceiling, active-time
ceiling and prospective logical depth; reserve one attempt charge; execute the
action; increment committed-transitions only when its mutation commits. OOM keeps
attempted work charged and increments an allocation-failure counter if representable.
Saturate diagnostic counters; stop explicitly before any normative counter wraps.
Identical no-fault execution must have equal attempted work regardless of slicing.

Producer preprocessing/search/build/validation/export belong to the producer
ledger. Independent replay, including its own upper verification, belongs to the
replay ledger. Strict SearchLimits maps its work/time limits to each independently,
matching current two-budget semantics. literal_scope_limit stays reference-only.

Active time is accumulated with steady_clock only around nonzero advance calls;
time between calls, admission copies, and caller IO are excluded and documented.
At producer-to-replay transition switch ledger timing at that boundary. Time checks
are cooperative, not a hard real-time promise. Tests inject a private fake clock;
the production API has no arbitrary user clock callback.

Logical depth counts owned solve/partition/replay/validation traversal frames,
not C++ stack frames. Define exact accounting in docs and tests. No static bit
width limits are introduced. A depth stop retains the next intended push, so
raising the ceiling resumes it rather than rebuilding the machine.

raise_limits is a scalar, allocation-free validation/publication. All new ceilings
must be monotone (including finite->unbounded); consumed counters never reset.
The options/binding remain immutable. Record a scalar revision. Strict wrappers
never automatically extend a user budget. A zero quantum must check the early
no-op path before obtaining a clock timestamp or initializing a lazy cursor.

## Failure-atomic transitions

Never mutate a program counter before completing potentially throwing work.
Prepare an object/node/capacity privately, then publish with noexcept moves/swaps
and scalars. Larger preparation has its own cursor and immutable committed prefix.

| Transition | Preparation | Nonthrowing publication |
| --- | --- | --- |
| Push search child | Child frame and stack capacity | Install frame and parent return stage |
| Visit input cell | New set/map node or scalar copy | Link node and increment input index |
| Accept candidate | Complete immutable Choice/DAG node | Replace best handle and candidate stage |
| Memoize exact state | Fully prepared map node | Link exact entry, pop child, advance parent |
| Publish proof claim | Prepared verified-map node after all checks | Link and advance claim index |
| Improve incumbent | Complete tree, P02 result, artifact/control block | Swap published handle |
| Finish proof | Checked root, final artifact/control block | Set complete/result authority |

No budget checks/throws in std container comparators. No callback or diagnostic
string construction after publication. advance catches bad_alloc and returns a
fixed-size allocation_failure reason; unexpected exceptions poison the machine
with internal_failure. Malformed proof is terminal invalid_certificate. Binding
and old validated artifacts survive; logical machines cannot continue after an
internal invariant failure. cancel/destruct need no allocation or logging.

Repeated persistent OOM at a transition preserves exactly the same logical next
action. Attempt counters may increase until a resource ceiling; no alternatives
are skipped and no new authority is published. On recovery, retry that action.
Factories can throw before returning an owner. Legacy allocating result conversion
must be assembled privately; conversion failure yields resource status only if
that existing return representation itself can be constructed, otherwise bad_alloc
propagates. Never claim unconditional no-throw legacy string/JSON reporting.

## Nonoverlapping implementation ownership

- search.hpp/search_session.cpp: API, immutable authority, bindings, resource
  extension, top-level scheduling, strict adapters and allocating conversion.
- search_budget.hpp/continuation_budget.cpp: scalar ledgers and active clock only.
- producer_cursor.hpp/exact.cpp: exact frame machine and producer partitions.
- fast_paths.hpp/.cpp: fast analysis/hierarchy cursors and construction.
- replay_cursor.hpp/certificate.cpp: independent replay, partitions and v1/v2 rules.
- validation_cursor.hpp/verify.cpp: P02 cursor and blocking validate_tree adapter.
- io/oracle.hpp + src/io/document.cpp: strict preservation and separate progress IO.
- docs: proofs/lifecycle/resource accounting, not durability claims.

## Acceptance work (not executed)

Compare uninterrupted vs unit/random quanta against frozen P03 and private P04
v1 baseline on existing exhaustive families. Assert final proof validity as well
as height/status. Force every owned stage and multi-level return to suspend.
Capture complete candidate before search ends; verify only best-found exposes it.
Cut proof replay after producer completion and immediately before root publication.
Replay v1/v2 corrupted proofs and exact binding/type mutations. Test >64 variables
and occurrences, nullary/duplicate/disconnected scopes, projected hierarchy misses,
residual counterexamples, infeasible families, and P04 pruning/symmetry branches.

Run allocation sweeps and persistent failures through each transition table row;
after recovery compare completed state and independently checked artifacts. Move
and destroy owners in every phase; retain artifact handles after destruction.
Zero-quanta are byte-for-byte no-ops on progress even at completion. Test monotone
budget extension, invalid reductions, clock pause exclusion, depth suspension,
counter overflow, and serializer refusal to represent partial proof as optimum.

## Explicit root decisions before implementation

1. Approve full incremental P02 ValidationMachine (recommended), rather than an
   indivisible validation phase that defeats fine work/time quanta.
2. Approve exclusive transferable ownership instead of O02-style creator-thread
   affinity. Both are valid, but tests and move behavior must choose one.
3. Approve immutable strict/best-found policy and separate progress IO; do not
   retrofit uncertified trees into OracleResult/write_oracle.
4. Decide whether interim non-universal lower bounds are required in the first
   implementation. Universal intervals until full replay satisfy honesty; the
   existing component rule permits useful early certified improvements.
5. Confirm that compatibility preserves result/limit semantics and proof meaning,
   not exact historic work-counter values. Resumable microsteps and validation
   metering necessarily require a declared accounting revision; keep v1/v2 proof
   acceptance independent of accounting version.
6. Decide whether existing strict wrappers may propagate bad_alloc if even their
   allocating legacy error strings cannot be created. New APIs remain allocation-
   free on reporting; old aggregate/JSON forms cannot honestly promise this.

No theoretical blocker is identified. The substantial work is converting every
yielding loop, sort, traversal and publication to owned state while preserving
independence, not devising a replacement height algorithm.


## Root implementation decisions

These are routine implementation choices within the existing authorized P06
scope; no user approval is pending. They are design decisions, not implemented
or accepted behavior.

- Implement incremental independent P02 validation, including its current rules
  and diagnostic authority. Do not hide whole validation in one work quantum.
- Use exclusive movable planner ownership with no creator-thread affinity.
  Concurrent use remains outside the contract; there are no user callbacks.
- Keep immutable strict/best-found policy and separate progress serialization.
  Preserve existing strict result/reader semantics and v1/v2 proof meaning.
- Universal lower bounds are sufficient initially; final lower evidence still
  requires independent complete replay. Early component lower bounds are useful
  only when independently established. Never use an incumbent as a lower bound.
- Declare a continuation accounting revision. Compatibility covers semantics
  and resource honesty, rather than exact historical internal work totals.
- Keep allocation-free fixed-enum reporting in the new API. Legacy adapters may
  propagate bad_alloc if their allocating error representation cannot be built,
  as current persistent-allocation tests already permit.

The saved header is a proposal to refine during implementation. It is not a
public compiled API and no P06 acceptance is claimed.
