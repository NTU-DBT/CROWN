# Owned exact-search and proof-replay continuations

P06 is acceptance-verified. All 86 tests pass GCC Debug/Release, ASan/UBSan,
Clang Debug and a fresh source-only Release build; the verification packet
records the final snapshot and evidence. This contract describes the API. The complete Refactor.md
scope remains active. P04's historical source seal is preserved separately.

`crown/planner/search.hpp` owns a search or an independent certificate replay.
Admission validates and copies/moves the complete catalog, query and claim;
subsequent caller mutations cannot change the owner. Input admission and JSON
IO are allocating operations outside work grants. Resume accepts no replacement
query, policy, algorithm or caller-edited progress. This is an in-process owner,
not a durable checkpoint or WAL.

## Authority and policies

`ValidatedIncumbent` owns a complete independently P02-checked upper witness.
It is not a proof of minimum height. `VerifiedOptimum` additionally owns the
matching completed independent lower proof. `VerifiedInfeasible` owns a completed
infinite root proof and no upper witness. Constructors are private; consumers
cannot upgrade an incumbent by changing a Boolean or an enum. Published immutable
handles outlive moved, cancelled or destroyed facades; copies allocate nothing.

`SearchPolicy::strict` withholds incumbent handles. `best_found` can expose the
last validated incumbent while search or replay remains unfinished. Both policies
continue exact search and produce the same authority when proof completes.
Scalar progress always distinguishes universal lower evidence, validated upper
height and completed independent lower evidence. A nonempty unfinished query
starts at lower one; an empty body starts at zero. A solved branch or incumbent
never raises the certified lower bound. This implementation retains the universal
lower bound until independent whole-root replay completes.

The existing `minimum_tree` remains a strict blocking adapter. Resource stops
return no minimum, tree or partial certificate. `verify_height_certificate`
remains a blocking adapter with independent resource status. V1/v2 certificate
meaning and exact query binding are unchanged; replay dispatch accepts both.
The private unoptimized v1 producer remains a separate testing translation unit;
the literal P03 oracle is unchanged.

## Grants and retained state

```cpp
auto search = crown::planner::ExactSearch::create(catalog, query);
auto update = search.advance({1024, std::chrono::milliseconds{2}});
// The caller may pause here for any duration, then grant more work.
if (auto optimum = search.optimum()) {
  use_checked_tree(optimum->upper().tree());
}
```

A work grant advances saved execution positions: preprocessing, hierarchy,
partition placement, root/child search, exact memo publication, candidate-tree
construction, independent P02 validation, proof export and independent replay.
It does not restart a recursive algorithm with a larger allowance.

Producer coroutine frames are owned explicitly. Every allocating operation runs
outside coroutine resume as a pending retryable operation; code between yields
is nonallocating. Replay uses independently owned manual jobs and its own
smallest-remaining block/complement enumeration. P02 uses saved scans, explicit
reachability frames and independent connectivity/connex checks. Producer and
checker share immutable input and P02 authority, not partition or metadata code.

Completed choices live in a flat arena. Child references do not own their
children, so payload teardown cannot recurse down query depth. Candidates and
witness builders retain arena ownership independently of the producer. Active
coroutine cancellation detaches and destroys frames from leaf to root.

## Resource accounting

`continuation_v1` counts controlled cursor and scheduling transitions, including
preparation, validation and export. The default is ten million attempted
transitions per producer and replay phase. Explicit caller ceilings are exact;
no automatic extension is performed. Finer transition counts are not comparable
to the historical P03/P04 work totals. Structural counters retain their names;
legacy work aliases mirror the new attempted producer/replay counters.

Per-call work/time quanta, cumulative producer/replay work and active-time
ceilings, and logical frame depth are distinct. Work/time/depth stops retain the
same owner for retry after a monotone `raise_limits`. Finite-to-unbounded is an
extension; reductions and unbounded-to-finite changes reject without mutation.
Already consumed counters never reset. Normative counters stop before wrapping;
diagnostic active time and allocation-failure totals saturate.

A zero-work or zero-time grant performs no transition, allocation, clock sample,
phase change or publication, including on completed owners. Its returned stop
reason is ephemeral; stored progress remains unchanged. Negative time grants or
limits reject. Empty-body administrative work needs logical depth zero;
nonempty search and replay stop honestly before exceeding their frame ceiling.

Active time is sampled only within nonzero `advance` calls. Caller pauses,
admission, serialization and explicit cancellation/destruction are excluded.
Clock limits are cooperative checkpoints. Standard container comparisons,
allocator/storage mechanics, scalar/string widths and deallocation costs are
separate costs; a transition is not a hard CPU-time or complete byte bound.
Legacy millisecond limits that cannot be represented as nanoseconds reject
explicitly. These search work/time grants are not allocator-byte caps. S05
separately verifies the post-admission native runtime query account; standalone
search/compiler work and explicit serialization remain boundaries. See the [query memory contract](query_memory.md).

Persistent allocation failure returns a fixed enum without allocating a message.
The pending transition and existing published incumbent survive. Attempt/failure
counters increase; completed transitions and semantic cursor state stay intact.
Removing the failure resumes that same owner. Invalid proofs or internal
invariants are terminal and cannot become feasibility or optimum authority.
Legacy aggregate/error-string conversion may itself throw bad_alloc; it never
returns a partly certified result.

## Lifetime and output

Facades are move-only, exclusive single-caller objects with no callbacks or
background execution. Exclusive ownership may transfer between threads;
concurrent access is outside the contract. `cancel` releases unfinished state,
retains published handles and is terminal. Completed owners remain complete.
Moved-from progress is explicitly marked; advancing reports moved_from and
binding/options access rejects. It establishes no infeasibility claim.

`crown/io/search.hpp` serializes live progress or immutable artifacts. Progress
and validated-incumbent documents use `search-progress-v1.schema.json`, have a
separate artifact tag and always contain `certificate: null`. Strict progress
never includes an incumbent. Typed optimum/infeasibility writers alone export
ordinary height-certificate v1/v2 documents. Neither progress nor an upper
artifact is accepted by the strict certificate reader. IO derives exact CQ
v1/v2/v3 binding from the owned source, including source/catalog metadata.
