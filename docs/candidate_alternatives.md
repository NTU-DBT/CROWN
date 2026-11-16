# Minimum-height alternative plans

P07 provides `CandidateProvider`, `MinimumHeightCandidate`, `CandidateSnapshot`
and `CandidateCache` in `crown/planner/candidates.hpp`. Integration status and
actual acceptance results are in the
[P07 record](verification/candidate-alternatives-2026-11-07.md).

## Original proof and checked alternatives

Creation requires an immutable original-query P06 `VerifiedOptimum`. It does
not run a background exact search or accept an editable height/proof flag.
Each seed and generated tree passes independent original-binding P02 and a
height gate. A taller valid tree is filtered; a checked height below the
proved minimum is an internal contradiction. Only a checked tree at exactly
the supplied original minimum becomes a privately constructed candidate.

A candidate owns its checked upper, full structural key, original binding,
generation provenance and unchanged supplied original proof. An alternative
tree never replaces the original certificate's witness. Original minimum
height remains known independently of enumeration progress or exhaustion.
Cancellation/destruction does not invalidate earlier candidates or snapshots.

The deterministic order is original exact witness, optional full-original
P05 residual seed, optional cached prefix in stored order, then normal-form
generation. Every seed is rechecked and recanonicalized. Duplicate sources
retain the first published generation provenance. Cache reuse preserves that
provenance while attaching this provider's own supplied original proof.

## Finite family and saved execution

For m nonempty native occurrences, enumerate g=0 through m−1 generalized
labels, every root and every parent digit assignment. Connectivity, native
height, generalized branching and Above checks filter topologies. Generalized
scope digits lazily visit subsets of complete native scopes, including the
empty set. Dynamic digits avoid fixed-width masks and eager power sets.
Different native anchors may represent the same subset; key deduplication
handles this and generalized-label permutations after independent P02.

Every normal-form rooted tree has one enumerated root/parent assignment.
Every generalized scope lies in a native power set by the guard condition,
so the dynamic scope digits cover it. Structural filters preserve exactly
the requested-height family before P02 decides Cover/Connect/Guard/Above/Connex.
The contraction argument in [planner_proofs.md](planner_proofs.md) establishes
that some minimum-height representative is in this family. It does not prove
that contraction preserves globally best maintenance cost.

An empty body has one empty tree. A supplied verified witness may contain
unary generalized nodes, so admitted seeds remain an explicit additional
family. Exhaustion covers admitted seeds plus the finite normal form; it
does not cover every conceivable admissible tree or prove globally cheapest
cost. A requested candidate count, resource stop or partial snapshot is not
exhaustion. A fresh provider seeded from a cached prefix starts a new generator
and does not claim to resume the old cursor or inherit its completion bit.

`advance(WorkQuantum)` retains actual generator, validator, key and publication
positions. It returns on a new candidate, a grant/resource stop or actual
exhaustion. Zero work/time grants are inert; negative time grants are rejected.
Monotone limit extensions preserve consumed work and pending operations.
Queries beyond 64 variables/occurrences have no semantic cutoff; bounded work
may stop long before this intentionally exponential family finishes.

## Supplied finite proposals

`CandidateProvider::from_proposals(proof, trees, context, limits)` owns a finite
unchecked tree batch and visits it in input order. It adds no implicit witness,
residual seed, cached prefix or normal-form tail. Empty input exhausts with no
candidates. Invalid and taller trees are filtered; publication still requires
the original P02, proved-height and full-key gates described above.

The family is `finite-proposals-v1`, with source `supplied_proposal`. Exhaustion
means only that the supplied batch was consumed. It says nothing about an
upstream generator's completeness. C02 ranking and C05 selection retain that
family; C05 cache identity includes it. The original `CandidateCache` and cached
prefix factory accept only the original normal-form family, including when the
cache has zero capacity. Typed EXPLAIN rejects a selected candidate paired with
a different reported family. This cold check uses the existing owning provenance
getter; residual provenance may copy an allocating trace outside runtime updates.

Batch production and retained input storage are separate allocating admission
costs, outside `advance` grants. Each draft is moved into its own owner before
checking; a published candidate does not retain the entire batch. Allocation
failure retries the same pending input. Validation, canonicalization, dedup and
publication use the existing budgeted stages. Cancellation releases the
unpublished batch. These additions are cold planning work.

The [meta-decomposition adapter](meta_candidate_adapter.md) uses this admission
bridge after ordinary enumeration and canonical inverse CROWN contractions.
Its separate upstream coverage report must be considered alongside actual
finite-batch admission; batch exhaustion does not imply upstream exhaustion.

## Identity, cache and transactions

Structural tokens preserve root, node kind, complete original-variable scopes,
native occurrence identity and generalized grouping. They ignore display IDs,
node-vector/child order and already-checked derived claims. Incremental
postorder construction sorts complete framed child tokens; full bytes establish
equality. A token alone is not a global query/cache identity or proof.

Cache identity additionally includes complete deterministic catalog/query
encoding and supported context: update profile, arithmetic, planner,
optimization, cost-model and canonicalization versions. This includes types,
source schemas/metadata, constants/ignored terms, ordered/repeated head outputs,
aliases and contradiction. There is no alpha-remapped proof transplant or
digest-only equality. The initial profile supports mixed full-row set updates
and exact non-null arithmetic; unknown profiles/versions are rejected.
Cost rankings/statistics decisions are not cached by this candidate cache.

The private v2 binding encoding directly traverses every native Catalog/Query
field in fixed record order. Record/field/type frames, optional presence,
ordered vector counts, fixed-width integers and raw byte-string lengths make
it injective. Source metadata, typed constraints/references/statistics/hints,
term variants and ordered/repeated outputs are all included. Dates use their
exact day value and decimals their canonical exact text. Embedded NULs and
invalid UTF-8 remain unchanged, preserving P06's native byte-string domain.
No JSON DOM or textual dump is created on admission: ordinary string/vector
cleanup can unwind an allocation failure without allocating another traversal
stack. This is an internal identity token, not an exported checkpoint or new
wire format.

The cache has bounded entry count and deterministic FIFO insertion order.
Hits and replacements do not move entries. New node preparation precedes
eviction; allocation failure preserves existing entries, order and counters.
Capacity zero disables installation. A cache hit supplies an immutable prefix,
not permission to bypass this provider's binding/P02/height/key gates.

Candidate vector capacity and immutable payload are prepared before dedup
membership commits. No throwing operation separates successful membership
insertion and visible publication. Allocation failure therefore retries the
same pending candidate without losing it, marking it seen or changing old
handles. Factory/snapshot/cache admission are separate allocating operations.

The published vector grows geometrically when its capacity is full, clipped to
`max_size()` after the existing overflow check. Over C publications this gives
O(C) total old-handle relocations; one reserve can still move the whole prefix
and allocate spare capacity. The saved reserve stage, logical charges and
publication order are unchanged. Candidate access returns an owning value and
snapshots copy the vector, so relocation invalidates no exported element borrow.
Spare capacity is outside logical cell/count limits. This is an amortized
relocation argument, not a measured speedup or allocator/time bound.

## Resource and report boundaries

Logical work counts attempted/committed transitions. Active nanoseconds are
saturating diagnostics; finite active-time ceilings still apply. Logical
counter overflow is terminal. Depth diagnostics count actual saved active
worker frames, excluding a blocked requested push and unrelated suspended
workers. Nonterminal cancellation allocates nothing and frees unpublished
workers; after failure/exhaustion it is inert and destruction frees scratch.

Generator, key and facade share cumulative logical construction records/cells,
including discarded drafts. Separate candidate and cache-entry caps bound
retained counts. Admission copies/serialization, P02 scratch, allocator capacity,
scalar widths, caller-retained history, snapshots and cache storage are explicit
separate costs. Ordered full-key comparisons, vector relocation, allocation,
cleanup and indivisible admissions have variable execution cost. These are
neither S05 byte/capacity guarantees nor hard CPU deadlines. Each owner requires
one exclusive caller; no operation is concurrency-safe.

Allocating writers in `crown/io/candidates.hpp` accept typed candidates,
snapshots or the live provider, never edited diagnostic aggregates. Reports
retain the unchanged original certificate including its original witness;
an alternative appears separately as `checked_upper_only`. Snapshot entries
repeat proof/binding data for independent extraction. This increases explicit
serialization work/bytes, outside advance quanta.

The strict [report schema](../schemas/candidate-report-v1.schema.json) checks
shape and supported versions. It cannot establish cross-field binding/height
equality, computed-key correctness/uniqueness, provenance truth or actual
exhaustion. A schema-valid edited document creates no checked authority. A
future reader must independently check these and replay original proof and
alternative upper. No new report reader or proof constructor is provided.
Native byte strings outside UTF-8 remain valid for planning and cache identity;
the existing strict JSON text encoder may reject their report serialization.
That transport boundary does not restrict native candidate admission.
