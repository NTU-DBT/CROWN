# P07 finite generator proposal

**Proposal only, 2026-11-07. P07 remains `not_started`.** These four files are
isolated under documentation; they are not compiled by repository targets or
integrated with any public planner interface. They change no frozen P05 input.
The direct compilation and fault-injection runs below are proposal-only
preflight evidence, not oracle, P02, P05 or P07 acceptance verification.

Root later ran two isolated smoke checks through the existing independent P02
verifier, outside repository targets. Boolean R/S/T at the frozen-oracle
minimum2 exhausted after51 drafts/26411 steps and produced3 distinct valid
trees under a separate framed recursive reference token. The equal-scope
three-occurrence self-join at minimum1 exhausted after876 drafts/49829 steps
and produced4 distinct valid trees. Repeated ready observations preserved
the draft/counters, and a retained draft stayed unchanged after consumption
and further enumeration. Logs are under ignored
`build/verification/p07-generator-{boolean,selfjoin}-preflight.log`.
These remain small proposal smoke checks, not integrated P07 verification or
an independent full-family, real-OOM, key or cache acceptance suite.

The contract follows [Refactor.md §5.4 and P07](../../../Refactor.md), the
[design preflight](../p07-design-preflight-2026-11-07.md), and the
[implementation seams](../p07-implementation-seams-2026-11-07.md).

## Internal boundary

`machine.hpp` proposes an independent internal API in
`crown::planner::alternatives_proposal`. `NormalFormGenerator` owns a shared,
immutable, already admitted `continuation_detail::BindingData`, a caller-supplied
native height, and a shared `ContentBudget`. The future facade must get that
height from the **original-binding** `VerifiedOptimum`. Neither this integer nor
a generator draft is checked upper or minimum-height authority.

Construction allocates only the inert implementation shell. The first `step`
creates its coroutine frame; all preprocessing is subsequently resumable.
`step(UnitContext)` performs at most one pending logical operation and returns
`advanced`, `draft_ready`, `exhausted`, or `stopped`. A stopped result identifies
`depth_limit`, `record_limit`, `cell_limit`, or terminal `counter_overflow`.
`requested_depth` reports the blocked depth operation. The facade must enforce
its own work/time/zero-grant policy and call this worker at most once per granted
unit. The worker has no clock and no `WorkQuantum` facade.

`draft()` returns an immutable owning handle. The worker drops its mutable
alias before making that handle visible. Repeated `step` calls while it is
pending return `draft_ready` without additional enumeration or accounting.
Only `consume_draft() noexcept` acknowledges it. A future facade must complete
the following work before acknowledgement:

1. Retain this draft and run the independent resumable P02 `ValidationMachine`
   against the same original binding.
2. Reject invalid or taller trees; treat a checked height below the original
   proved minimum as a contradiction. This generator's topology height filter
   is only an optimization, never replacement authority.
3. Build the structural key, check duplicates, and prepare publication. On
   allocation failure keep the same pending draft. Commit key membership and
   candidate visibility together before acknowledgement.

P02, key generation, deduplication, `VerifiedOptimum` ownership, candidate
publication, cache identity and cache eviction are deliberately absent here.
The empty body emits exactly one empty tree even if an erroneous caller supplies
a nonzero target; the future height gate remains mandatory for every draft.

`statistics()` exposes scalar successful step, examined topology, surviving
topology, ready draft and acknowledged draft counts plus peak logical depth.
Failed/blocked calls and repeated ready observations do not increment successful
steps. The future facade separately accounts attempted units and active time.

`cancel()` is allocation-free, terminal and flat: it destroys the control frame,
then clears flat vectors/sets and unpublished tree ownership. A retained draft
handle remains valid. Cancellation reports `stopped/none`, distinguishable by
`cancelled()`; it never masquerades as family exhaustion. Destruction likewise
uses no recursively owned tree nodes or recursive coroutine chain. Cleanup cost
is outside advance accounting. Moved-from owners may be destroyed, assigned or
cancelled; other member access requires a live owner.

## Enumeration order and cursor

Let `m` be the original native occurrence count. Original occurrence index `i`
always labels native node `i`; no projection, synthetic head atom, renumbering
of native occurrences or self-join merging occurs. Variable scopes come from
the trusted atom terms, ignore constants/ignored columns and deduplicate repeated
variable terms. Sets iterate in ascending original variable ID order.

For `m >= 1`, the deterministic order is:

1. Generalized count `g = 0, ..., m-1`, with labels `m, ..., m+g-1`.
2. Root label `0, ..., m+g-1`.
3. Numeric lexicographic parent vectors, lowest indexed nonroot position most
   significant. Each nonroot digit ranges over every node label except its own.
   The root slot stores itself but contributes no edge.
4. For topologies that survive the structural filter, generalized scope tuples,
   with generalized node `m+g-1` least significant. Each tuple digit consists
   of native anchor `0, ..., m-1` and a dynamic binary vector of the anchor's
   deduplicated scope width. Bit 0 represents the lowest variable ID and carries
   first. All-zero bits are the empty subset. Exhausting an anchor's subsets
   advances the anchor; exhausting all anchors carries to the previous node.

An empty native scope contributes one subset representation. Equal native
scopes and subsets contained in several anchors deliberately produce duplicates.
Generalized label permutations can likewise duplicate structural plans. Neither
duplicates nor rejected P02 drafts are mistaken for new distinct candidates.
The future common key gate handles those cases.

Each topology resets per-node child counts/visited flags one node at a time,
derives child counts one edge at a time, and rejects native-parent/generalized-
child edges and generalized nodes with fewer than two children. It then uses
an explicit DFS stack, with one child-label inspection or stack action per
operation. Each frame stores node, next child label and native path depth.
Root reachability of all labels establishes connectedness; visited detection
also rejects a repeated visit. The maximum native path count must equal the
supplied target. Generalized scope contents are not needed for these filters.

The worker stores real parent digits, scope anchors/bits, DFS positions and
draft construction positions. It does not regenerate an earlier prefix after
a pause. One draft node, scope variable or child edge is constructed per
corresponding operation. Scope-universe cardinalities, `n^n`, factorials and
fixed-width subset masks are never calculated. `m+g`, index/depth headroom,
logical content counters and scalar statistics are checked before overflow;
container maximum element counts receive the same terminal overflow stop.

## Family coverage argument and limits

For a fixed `g`, every rooted labeled tree on these `m+g` labels has one root
and one parent for each nonroot label. The root loop and parent digits visit
that assignment. Removing self-parent values cannot remove a tree. Root
reachability removes disconnected cycles, while the child-count and Above
filters remove exactly the unwanted structural forms. For a surviving rooted
tree, DFS computes its native height by adding one precisely at native nodes.

For any generalized scope that is a subset of some native scope, its anchor
and bit representation appears in that digit's finite sequence. The mixed-
radix tuple therefore visits every combination for all generalized nodes.
Every requested-height normal-form member with at most `m-1` generalized
nodes and at least two children at each generalized node is represented.
Every leaf is consequently native. Duplicates change cost, not coverage.

Drafts can violate running intersection, guards or the head/connex condition;
they are **untrusted**. Exhaustion alone establishes only traversal of this
finite proposed family, and any accepted-member completeness statement still
requires the future independent checker and key gate to process every draft.
The normal-form contraction argument in Refactor §5.4 establishes that some
minimum-height tree is in this family. It does not show that the best maintenance
cost over arbitrary admissible trees survives the removal of unary generalized
nodes. No generator state establishes a new lower bound or original-query proof.

This is intentionally expensive. The parent product is exponential, every DFS
may inspect all node pairs, and scope tuple enumeration can be enormous. There
is no query-size cut-off, 64-variable mask limit, symmetry reduction or eager
power-set allocation. Queries above 64 occurrences/variables can enter and
stop honestly on a bounded grant or resource limit; their enumeration may be
impractical. This is a completeness family, not a claim of practical scaling.

## Depth, content and retry semantics

Logical depth is the one owned coroutine control frame plus the number of
currently owned DFS traversal frames. Initialization and draft/scope construction
therefore normally require depth one. Each DFS push requests its next actual
depth **before** allocation/mutation. Input arity/count is not itself used as a
depth ceiling. The future P02 and canonicalization workers own separate depth
accounting. A depth stop retains the pending push; raising the ceiling resumes
it. `current_depth()` is zero before first start, after exhaustion or cancellation.

`ContentBudget` has optional `uint64_t` record/cell ceilings and cumulative
counts. `prepare(r,c)` checks both counts and limits without mutation, throwing
the single internal `ContentStop` type on a cap/overflow. `commit(r,c)` follows
successful preparation and allocation, and is nonthrowing. A shared facade can
charge its other owned artifacts to the same budget using the same protocol.
Owners must be serialized; this is not a concurrently mutable budget.
`raise_limits` accepts monotone extensions, rejects decreases and never resets
consumed counts.

This generator charges:

| Construction | Records | Cells |
| --- | ---: | ---: |
| Coroutine frame | 1 | 0 |
| Native scope container, topology node state, generalized scope digit | 1 each | 1 each |
| New deduplicated native scope variable or generalized dynamic bit | 0 | 1 each |
| Each DFS frame push, including reused vector storage | 1 | 1 |
| Draft tree shell, including empty tree | 1 | 0 |
| Draft tree node | 1 | 1 |
| Draft scope variable or child edge | 0 | 1 each |

Charges accumulate across rejected topologies, consumed/rejected/duplicate
drafts, removed bits and discarded buffers. Existing scalar/bit rewrites are
not new construction. Repeated native variables create only one scope cell.
A failed construction commits no charge. Excluded costs are admission binding
and inert-shell ownership, P02 scratch, future external workers until explicitly
charged, container capacity/relocation, allocator metadata, string widths,
set comparisons and caller-retained immutable history. These are logical
construction caps, **not allocator-byte or hard CPU/deadline caps**. A vector
growth can relocate existing elements inside one operation; one abstract cell
operation is not a fixed physical-time guarantee.

Only the generic `Engine`, `Task` and saved `operation` mechanism from
`producer_cursor.hpp` are reused. No P06 recurrence, choice DAG, pruning,
certificate logic, production candidate or test oracle is consulted. Allocating
operations execute outside coroutine `resume()`. The pending closure remains
installed until it succeeds. Each allocating operation prepares its cap first,
uses a container's strong insertion guarantee or constructs a detached value,
and then commits scalar/cursor changes without further allocation. Coroutine
frame creation itself happens directly in `step`, before `started` is committed.

`std::bad_alloc` escapes to the future facade; it must report allocation failure
and retry this same owner. Record/cell stops likewise retain the same operation.
Counter exhaustion is terminal and latched; it retains state but cannot be
resumed by raising a cap. There is no seen-key state in this worker, and no
publication can skip acknowledgement. The facade's own publication transaction
must preserve the same discipline.

## Isolated compilation and fault-injection evidence

`generator.cpp` and `fault-probe.cpp` were directly compiled with both `-O0`
and `-O3`, using C++23 and the following strict warning options:

```text
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow
    -Iinclude -Isrc/planner -Idocs/verification/p07-generator-proposal
```

The standalone probe uses the allocation counter and persistent `operator new`
fault helper from `tests/unit/residual_exception_test.cpp` by including that
translation unit under a renamed `main`. It links against the existing
`build/release/libcrown_core.a`; it is not a repository target. Compile, link
and run logs are under the ignored
`build/verification/p07-generator-proposal/` directory, with objects and
executables under `/tmp/p07-generator-proposal/`.

For Boolean `R(x), S(x,y), T(y)` at supplied target height 2, the uninterrupted
owner emitted 51 ordered drafts in 26,411 completed steps, examined 1,400
topologies, retained 9 topology survivors, and charged 357 records / 706 cells.
The helper observed 613 allocation positions during this run. At every position,
the probe injected a persistent failure, retried the same pending operation
twice on that owner, released the fault and continued the same owner to
exhaustion. Every complete draft tree in order, generator statistic and content
counter matched the uninterrupted baseline. The same result passed at both
optimization levels.

The probe also checked a zero and then insufficient depth ceiling before
lifting the ceiling, record and cell stops followed by monotone unbounded grants,
two inert observations for every ready draft, caller-retained draft stability,
and cancellation with no observed allocation. The probe consumes actual saved
generator state and checks full draft content; drafts remain untrusted and carry
no minimum-height, candidate or original-query authority. This is proposal-only
failure/resource preflight, not P07 acceptance, an actual OOM test, or a
replacement for independent full-family, P02, key/cache and ordinary P07 gates.
