# P07 implementation dispositions

Design only. P05 verification is still running; P07 remains `not_started`.
This supplements the [Astra preflight](p07-design-preflight-2026-11-07.md)
with routine choices for the next implementation. It changes no native input
to the frozen P05 matrix and supplies no new acceptance result.

## Authority and first scope

Start with a caller-supplied, immutable original-query `VerifiedOptimum`.
The provider owns its handle and an admitted binding/context snapshot. No
background exact search or best-found policy is needed for the first API.
An infeasible query is handled by orchestration before this feasible-provider
factory. Reject moved-from proof and seed handles at admission.

Emit a privately constructed `MinimumHeightCandidate` containing its checked
upper tree/report, binding, structural identity, source provenance and the
unchanged original minimum proof. A different upper tree must never replace
the tree inside the original certificate. Public report writers show the
alternative upper check and the shared original proof separately.

Use one deterministic composed profile: exact witness seed, optional P05
candidate seed, then the finite normal-form generator. A seed still passes
the common binding/P02/height/key gate. Reject taller valid uppers from this
strict provider; a checked height below the proved minimum is an internal
contradiction. An induced residual proof or a different original binding
cannot satisfy admission merely because its height agrees.

The exact witness is a singleton seed family, not proof that every admissible
tree is in the enumerated normal form. External verified certificates can
have valid upper witnesses with unary generalized nodes. The composed profile
therefore distinguishes its seed members from normal-form coverage. Family
exhaustion covers all generated normal-form members plus the accepted seeds;
it does not imply global minimum maintenance cost over every tree family.

## Provider, cursor and publication

`advance(WorkQuantum)` stops when a new candidate becomes ready, at a grant
or resource stop, or at exhaustion. `candidate_count()` and `candidate(i)`
return existing immutable owning handles without allocation. Repeated
requests for more candidates continue the same cursor. Reaching the requested
count is not exhaustion; fewer distinct minimum plans may exist.

Keep separate workers for finite topology/scope enumeration, independent
P02 checking, canonical-key construction and transactional publication. Reuse
the generic pending-operation mechanism, not the exact-search recurrence or
its private Choice graph. Root should own the facade and common acceptance
boundary; a complex worker can own the new finite generator. Focused workers
can independently own literal reference collection and adversarial fixtures.

For m nonempty native occurrences, use g=0..m-1 generalized labels, explicit
root/parent digits, and dynamic scope-subset digits. Validate topology,
generalized branching, Above and native height before scope enumeration.
Enumerate generalized scopes through subsets of complete native scopes;
duplicate subset representations are allowed and deduplicated after checking.
Do not materialize a power-set universe or compute its cardinality in a
fixed-width integer. The empty body emits its one empty tree and exhausts.

Topology digits, connectivity walks, native-depth propagation, child counts,
scope digits, draft cells, P02 frames and key comparisons all retain their
actual positions across stops. Construct each draft one cell at a time.
More than64 occurrences/variables must admit and stop honestly without
draining exponential enumeration.

Canonical tokens preserve root, kind, complete original-variable scopes and
original native occurrence IDs. They ignore display IDs, node-vector order,
child order and already-checked derived claims. Use framed lengths/counts and
sorted complete child tokens; distinct generalized grouping remains distinct.
An iterative postorder cursor and incremental lexicographic ordering make
the work explicit. Variable-width token storage and comparisons need their
own construction charges. Retaining full tokens avoids reliance on a digest
for equality.

Prepare immutable candidate data and candidate-vector capacity before
inserting a dedup key. The final key insertion and candidate publication must
leave no throwing operation between committed membership and visibility.
On failure the same candidate stays pending, without being marked seen or
skipped. Preserve the first producer's provenance under deterministic order;
later duplicate sources may add ledger diagnostics, not mutate old handles.
P05's origin enum describes only its last construction step, so identify the
provider source as residual separately; do not infer absence of earlier
grafting or exact repair from a native last-step origin.

## Conservative cache

Use a bounded, explicit exact-binding cache first. It owns immutable candidate
set snapshots, the original proof and full context, family/version/order and
exhaustion scope. A cache snapshot cannot be manufactured from caller-edited
progress. Capacity zero disables storage. Handles survive eviction.

Lookup and installation may be explicit allocating admission operations
outside provider quanta in v1. Compare complete deterministic Catalog/Query
binding bytes and all context fields. Current core query/document writers
are available without introducing a dependency from `crown_core` back to
`crown_sql`, where F05 identity lives. No runtime rows/updates belong in these
binding bytes. Keep actual source metadata, statistics/hints, variable/table
positions, ordered/repeated outputs and contradiction state.

F05 semantic hashes are not exact proof bindings and currently omit concrete
update assumptions. Do not remap/reuse proofs through those hashes in this
first cache. Conservative misses for renamed or reordered equivalent queries
are acceptable. Include arithmetic/planner/optimization/cost versions and the
supported update-assumption profile explicitly; reject unknown profiles.
Accepting a cache namespace does not establish a runtime complexity guarantee.

For a small entry cap, linear exact lookup is acceptable as an explicit
admission cost. This avoids a digest-only equality layer. If a digest index
is added, retain full equality and test collisions. Deterministic FIFO
eviction must prepare a replacement before removing the old entry. Replacing
an existing exact entry may preserve its original FIFO position, provided
this policy is documented. A failed insertion does not invalidate a provider
candidate already available to CBO.

Store immutable candidate prefixes, not a mutable provider borrowed through
the cache. A new provider can reuse such a prefix, then begin a new generator
and deduplicate; call that explicit new enumeration work. Only a retained
provider owner resumes its previous cursor. A cached prefix is never promoted
to exhausted merely because a larger request arrived.

## Accounting and acceptance

Use independent total work/active-time, provider/P02 logical depth, cumulative
logical record/cell and retained-candidate limits. Count discarded drafts,
tokens and dedup/publication records. State the excluded admission copies,
P02 scratch, container capacity/string widths and caller-retained history;
these are not S05 allocator byte caps. Counter exhaustion is terminal. All
limit changes are monotone, zero grants inert, and allocation/depth stops
retain the pending operation. Cancel/move/getters/handle copies allocate no
memory and published artifacts outlive provider/cache destruction.

Independent tests must collect the actual small normal-form minimum-plan set
with separate logic, rather than compare the producer key routine to itself.
Preserve the frozen minimum-only P03 oracle. Validate at least three meaningful
height-two plans for Boolean R(x), S(x,y), T(y), then canonical permutation,
native identity, scope/root and full cache-fence mutations. Test seed dedup,
request-N continuation, honest exhaustion, mandatory P05 minimum-three filters,
every observed allocation in generation/key/P02/dedup/cache publication and
same-owner recovery. Follow the ordinary source review, report/schema and
five-configuration acceptance gates before changing P07 to verified.
