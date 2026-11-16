# P07 design preflight: alternative admissible plans

Status: design only, 2026-11-07. P07 remains `not_started`; native implementation
is not authorized by this preflight. P05 is still in progress. This document
does not claim a successful P05 run, source seal, or verification matrix.
Only this new document is changed. No repository builds or tests were run.

## Recommended implementation boundary

Implement an owning `CandidateProvider` facade with an immutable, privately
constructed `MinimumHeightCandidate` artifact, deterministic structural plan
keys, and an explicitly owned bounded cache. Keep P06's producer and proof
format unchanged. Use its completed **original-query** `VerifiedOptimum` as the
common minimum-height authority. Obtain alternatives from a new resumable
finite normal-form enumerator, optionally preceded by one P05 candidate.

This is the smallest robust route to actual alternatives: P06 currently keeps
one best `Choice` per state and prunes equal-height alternatives; P05 chooses
the first valid reconstruction. Restarting either with the same binding does
not enumerate plans. `src/planner/fast_paths.hpp` exposes no independent
special-case enumeration API: those paths live inside P06. Do not fork the
exact recurrence merely to retain ties, expose its private Choice DAG, call a
test oracle from production, or relabel repeated copies as distinct plans.

The new enumerator can be incomplete when stopped and still satisfy P07. Its
family and exhaustion state must be explicit. Multiple candidates are possible
only when the query actually has multiple distinct minimum-height members;
requesting three cannot guarantee that three exist or fit a budget. CBO's cost
status remains `best_among_examined_minimum_height_candidates` unless a later
cost-specific completeness argument justifies more.

The contract sources are Refactor.md sections 3.3, 5.4–5.6, 9.1 and card P07;
the existing normal-form argument is in `docs/planner_proofs.md`. Relevant
interfaces are `include/crown/planner/{search,residual,verify}.hpp`,
`src/planner/continuation_machine.hpp`, `include/crown/io/identity.hpp`, and
`docs/query_identity.md`.

## Authority and proposed API shape

Use a concrete facade with a declared provider family rather than exposing
virtual callbacks that can manufacture checked status. Internal provider
adapters can implement a common claim-producing protocol. Every adapter's
tree is an untrusted draft at the common acceptance gate.

Suggested public concepts, not final ABI declarations:

- `CandidateContext`: supported semantics/arithmetic, update assumptions and
  versioned planner/optimization/cost inputs; owned, validated at admission.
- `ProviderFamily`: `normal_form_v1`, `residual_single_v1`, or a composed
  profile with a deterministic order. The exact witness is a seed, not an
  all-plans provider. Special-case seeds identify their actual authority and
  remain singleton families until dedicated enumeration exists.
- `CandidateProvider::create(VerifiedOptimum, CandidateContext, Limits)`:
  copies owning handles, validates context, and admits no borrowed inputs.
  A later convenience factory may own an ExactSearch, but must expose its
  pending proof state and may not emit strict candidates before completion.
- `advance(WorkQuantum) noexcept`: stop reasons include candidate ready,
  quantum/total limits, depth/content/candidate capacity, allocation failure,
  terminal counter overflow, family exhausted, cancellation and failure.
- `candidate_count()` and `candidate(index)` return existing immutable
  handles without allocation. CBO requests N by advancing until N are
  available, exhaustion, or a resource stop. Reaching N is not exhaustion.
- `progress()`, monotone `raise_limits()` and `cancel()` follow the established
  P06 ownership and zero-quantum behavior. Progress states the family, whether
  it is exhausted, number proposed/rejected/duplicate/published, and the
  original verified height separately from enumeration completeness.
- `MinimumHeightCandidate` owns its original binding, P02-checked tree and
  report/height, structural key, provenance, and a copy of the same immutable
  `VerifiedOptimum`. Its constructor is private. No public Boolean, mutable
  report, digest, trace or caller-selected integer creates this authority.

For each draft, admission requires an exact binding match, a completed P02
check on that binding, and `actual_native_height == proof.height()`. A greater
height is a valid upper bound but is excluded from this strict provider. A
checked lesser height contradicts the original proof and is an internal
failure, not a new optimum. Binding mismatch is rejected, including an
induced residual whose height happens to be the same. The attached lower
proof remains the original proof with its original witness; never replace
its tree field with the alternative and imply it is an unchanged certificate.
Report the alternative upper check and shared original lower proof separately.

A verified-infeasible input should have its own empty-provider admission
overload, or be handled by the orchestration layer before constructing this
provider. It must not be represented by a missing optimum or an exhausted
heuristic. An empty-body feasible binding has exactly one empty canonical
tree at height zero. Contradiction markers retain the existing structural
search meaning; P07 does not silently substitute SQL constant-false lowering.

## A finite generator that really finds alternatives

Write a fresh production cursor for the literal P03 normal form, without
sharing enumeration helpers with `tests/reference/tree_oracle.cpp`:

1. Publish the checked exact witness through the common key/deduplication
   gate. If a supplied/owned P05 candidate has the exact original binding,
   validate and filter it through the same gate. Do not start another P06
   original proof solely to produce a P05 seed; candidate mode suffices.
2. For m native occurrences, enumerate generalized count g from 0 through
   m−1; assign native labels to original occurrence IDs and temporary labels
   to g generalized nodes. Enumerate each root and parent vector in a fixed
   numeric order. Keep the parent-assignment position, connectivity walk,
   depths and child counts as resumable state.
3. Reject non-trees, generalized leaves/unary generalized nodes, generalized
   descendants below a native, and native path height different from h*.
   These tests do not require generalized scopes. Initially avoid stronger
   pruning that would need another completeness argument.
4. Enumerate each generalized scope from the union of all native-scope power
   sets, including the empty set. Enumerate subsets with dynamic digits, not
   a fixed integer mask or `1 << arity`. Generate the universe lazily or use
   resumable bounded construction. Duplicate subsets may be visited in v1;
   structural deduplication removes duplicate accepted plans. Do not replace
   this universe with pairwise separators without a separate proof.
5. Construct one draft cell at a time, validate with the independent P02
   ValidationMachine, canonicalize, and attempt publication. Resume the exact
   next scope/topology after rejection, duplication or publication.

Generalized labels produce duplicate topologies; that is a performance cost,
not incorrectness. Stable root/parent/subset ordering and deterministic merge
order across providers make fixed-budget runs reproducible. If adapters are
interleaved, specify the round-robin schedule rather than using elapsed-time
completion order to choose the next plan.

Exhaustion establishes coverage only of `normal_form_v1`: all P02-admissible
trees with m native occurrences, at most m−1 generalized nodes, at least two
children per generalized node, scopes in the native power-set union, and
height h*, modulo the stated plan key. The existing contraction argument
establishes existence of a minimum in this family. It does **not** prove that
excluding unary generalized nodes preserves the best maintenance cost over
every otherwise admissible tree. Before exhaustion, report incomplete search
even if h* has long been proved. No exhaustion bit supplies a new P06 proof.

A concrete multi-plan regression is the Boolean query R(x), S(x,y), T(y).
Its native-root tree S→{R,T} has height two; distinct height-two trees have
generalized root {x} with children R and S→T, or generalized root {y} with
children T and S→R. Each satisfies running intersection, guard, above and
the empty-head condition. Height one is impossible: x occurs in {R,S} and
y in {S,T}, which overlap without nesting. The independent oracle must still
confirm this fixture. It exercises meaningful generalized alternatives, not
just node names, child order or symmetric duplicate serialization.

Local rewrites are optional accelerators, not the initial completeness story.
Root changes or detach/reattach proposals can violate Connect, Above, head
reachability or height. Treat them as drafts, with P02 plus the h* filter
deciding acceptance. A narrowly sound rule is grouping at least two siblings
under a new generalized node with the **same scope as their generalized
parent**: existing guards imply the new guards, old paths retain their
variables, native height is unchanged, and the new separator preserves the
old head reachability. Require the old parent to retain at least two children
and keep the normal-form node bound. This can yield distinct grouping plans
but misses many root/scope changes. Even this rule passes P02. Do not promise
that a finite neighborhood supplies N candidates for every query.

## Deterministic plan identity

Canonicalization is for a P02-checked rooted tree. Traverse iteratively in
postorder. A node token contains node kind, original occurrence ID for native
nodes, sorted original variable IDs in its scope, and the lexicographically
sorted complete child tokens with lengths/counts. A versioned framing makes
the encoding unambiguous. The empty tree has its own token. Use an explicit
canonicalization cursor for traversal, comparisons and output cells; a single
recursive serialization/sort is not a bounded transition.

Ignore display node names, node-vector order, child-vector order and derived
claims such as separators/connex/height. P02 must reject false supplied claims
before they are ignored. Preserve the root, node kinds, scopes and original
native identities, including distinct self-join occurrences with equal
scopes. Do not merge variable types or ordered/repeated head outputs: the
plan key is namespaced by the complete exact Catalog/Query binding and context.
Node tokens alone are not a globally reusable key. Do not conflate alternate
generalized grouping with permutation of existing children.

Keep the full canonical token as equality evidence; a hash is only an index.
Hash collisions must perform exact token and binding/context equality. A
deterministic canonical tree with generated display IDs may be exported, but
do not mutate a published tree or a P06 witness. It is sufficient initially
to retain the checked tree and a separate canonical key.

Deduplication occurs across all provider seeds and generated candidates. The
first deterministic producer owns primary provenance. Optional later-source
diagnostics belong to the provider ledger or a new artifact revision; they
must not mutate old candidate handles. A cache hit records the stored original
generation provenance and a separate reuse event.

## Cache identity and the F05 boundary

Start with an explicit **exact-binding cache**, scoped to its owning cache
object, with no hidden process-global state. Cache entries own their complete
Catalog/Query snapshot, context, keys, candidates, original proof, declared
family/profile, generation order and exhaustion status. A source catalog
version alone is insufficient. Compare all source schemas, constraints,
statistics/hints, types, terms/constants/ignored columns, atom positions and
table IDs, variable positions/types/names, ordered/repeated head positions
and aliases, and contradiction state. Whole exact serialization admission may
reuse the existing binding writer's representation, but must not include
runtime rows/updates. Retain exact bytes as well as any digest.

F05 `plan_cache_sha256` already includes semantic, output-contract and
cost-input digests and arithmetic/planner/optimization/cost-model versions.
It does **not** include a concrete update mode. P07 must add a validated
versioned context containing the actual update assumptions, including any
insert-only/FIFO/mixed distinctions and FIFO scope if those profiles are
supported. For the first implementation support the current physical
full-row set-event/mixed-update profile, reject unknown profiles explicitly,
and include the profile anyway. Supporting a cache namespace for an assumption
does not establish a runtime complexity guarantee for it.

Use only the currently supported arithmetic `exact-nonnull-v1`; reject rather
than silently normalize an unsupported arithmetic policy. Include provider
family/rule/canonicalization versions and structural selection policy. A
candidate set cache need not store CBO rankings. If rankings are stored, include
the complete workload/cost inputs and statistics version as well as model
version; a model name alone cannot distinguish changed per-relation rates.
Limits are not semantics, but the entry must retain whether it is only a
partial set. A larger request may reuse entries and continue a retained owner,
or start a new provider and deduplicate; it must not claim that a cached
prefix is the complete family. Restarted enumeration, if chosen, is explicit
new work and never a resumed old cursor.

Choose deterministic FIFO eviction by successful insertion order initially;
cache hits do not change that order. Prepare the replacement before removing
the old entry. Cache capacity zero disables storage and must not discard a
candidate already available to CBO. Expose an insertion failure/resource stop
separately from provider candidate validity. Cache lookup/install APIs may be
explicit allocating admission operations outside provider quanta in v1; do
not hide full binding comparison or bulk copying inside a one-unit advance.

Conservative exact binding means renamed/reordered equivalent queries may
miss the cache. This is correct and meets the initial nonmixing requirement.
F05 canonical reuse is a later optimization with additional obligations:

- Own both source and target canonical-to-original occurrence/variable maps;
  build and verify their inverses. Translate every native occurrence and scope
  variable through canonical coordinates. Preserve physical source table
  identity and the target output contract.
- Recheck the remapped tree with P02 against the actual target binding.
  Equal semantic digests do not authorize transplanting a VerifiedOptimum or
  relabeling its certificate. Obtain/replay exact original-target authority
  through the existing proof boundary, or use a separately proved complete
  certificate-translation implementation. The latter is outside initial P07.
- A selected F05 labeling can leave automorphisms of identical occurrences.
  Mapping through it is semantically safe after validation, but a plan key
  under one chosen labeling is not automatically the unique key over all
  query automorphisms. Accept conservative misses rather than invent a broader
  equivalence guarantee.
- `query_identity` is currently blocking and work-limited; it is not a
  resumable subsearch. Never call it inside each candidate step and advertise
  per-cell time guarantees. Treat optional identity construction as explicit
  admission work, returning no cache identity on its resource stop.

## Resource, retry and lifetime requirements

Retain actual pending topology digits, scope subset positions, draft cells,
P02 frames, canonical comparisons, publication and cache insertion positions.
Use the existing independent P02 resumable machine; do not repeatedly invoke
blocking validate_tree from the beginning after each stop. An existing proof
handle requires no new exact work. A convenience factory that starts P06 or
P05 must retain those owners, pass bounded child grants and expose their
separate work/depth counters without draining or restarting them.

Define cumulative logical record/cell limits for P07-owned drafts, keys,
deduplication metadata and publication records, including discarded proposals.
Define separately the maximum retained candidates/cache entries and explicit
residual/P02/provider depth versus delegated exact depth. Document P02 scratch,
delegated search storage, admission binding/context copies, container capacity,
string widths and caller-retained immutable history as separate costs if not
charged. These are not S05 global allocator byte limits. Check native count
arithmetic such as m+g, counters and index conversions before arithmetic can
wrap. Do not precompute factorial/exponential candidate counts in fixed width.

Prepare allocations and capacity before advancing cursor state or publishing
membership. In particular, reserve candidate vector capacity and prepare the
immutable payload before inserting a dedup key; once the key is inserted,
finish publication using only nonthrowing operations. A failed insertion must
leave the same candidate pending. Alternatively use one authoritative entry
container whose committed membership is publication, with a prepared index.
Never leave a key marked seen when its candidate was lost on OOM. Apply the
same transaction boundary to cache insertion and deterministic eviction.

`advance` is no-throw, failed allocation remains retryable, zero work/time is
inert, limit extensions are monotone, and counter exhaustion is terminal.
Cancellation releases unpublished workers without allocating and retains
published handles and diagnostic history. Handles remain valid after provider
or cache destruction/eviction. Expose immutable owning handles, not spans into
a growing vector or raw pointers to F05 mapping arrays. Individual providers
and cache mutation are single-caller unless a separate concurrency contract
is implemented. Active-time accounting includes admitted child calls, but no
hard deadline claim is made for allocation, cleanup or whole admission work.

## Acceptance plan and resolved design choices

Implement in this order: authority/context and plan-key cursor; finite provider
and P02/height gate; deduplication/publication; exact-binding cache; reports and
independent tests. Use strict minimum height only in the first API, with P06
authority supplied by the caller. Keep best-found and taller-cost policies
outside this artifact type. No new theorem or user clarification is needed
to choose these defaults.

Required independent checks before any P07 verification claim:

1. Compare all emitted small-case keys/heights against the independent frozen
   oracle's admissible normal-form set, not only the production canonicalizer
   against itself. At least one fixture must independently exhibit three
   different minimum-height trees, including generalized alternatives.
   The existing minimum-only oracle adapter may need a separate test-only
   visitor/set collector; do not change its frozen minimum semantics or make
   production depend on that collector.
2. Verify canonical invariance under node renaming/reindexing/child permutation
   and distinction under changed native identity, scope, kind, root or binding.
   Include self-joins, repeated heads, constants, ignored terms and typed values.
3. Run section 5.6 and mandatory P05 height-three fixtures through the common
   filter. Reject malformed claims, induced proofs, wrong catalogs/heads,
   infeasible authority, upper-only artifacts and forged public aggregates.
4. Show budget-limited enumeration with a valid shared proof remains incomplete;
   show request-N pauses preserve the cursor; show fewer-than-N exhaustion is
   honest. Test more than 64 occurrences/variables without exponential drain.
5. Distinguish cache hit/miss for every context component, mutated same-version
   catalogs, alias/head/order changes, statistics and update assumptions; force
   hash collisions in the equality layer. Retained handles survive eviction.
6. Compare unsliced/unit/varied slicing output order, counters and keys; stop and
   extend each grant/depth/content/candidate limit. Persistently fail every
   allocation in generation, P02, canonicalization, dedup publication and cache
   installation, retry twice, then recover to the same baseline without skipped
   candidates, duplicate output or leaked authority. Test zero/cancel/moves
   under allocation failure. Keep exact-original proof unchanged throughout.

No source-level blocker requires redesigning P06 or waiting for C02. The main
implementation risks are factorial finite-family work, incremental canonical
comparison cost, transactional dedup/cache publication, and accidentally
equating F05 semantic identity with exact proof authority. The chosen bounded
cursor, full equality checks and exact-binding cache make those risks explicit.
Complete native tests, report/schema checks and the normal verification matrix
remain future work; this preflight does not change any task ledger status.
