# Heavy/light star prototype

`CROWN::star` is an opt-in, initially empty, serial exact-set owner for a checked
center-plus-unary-satellite CQ. Include `crown/planner/star.hpp` and
`crown/runtime/star.hpp`. The ordinary general runtime remains available as an
independent comparison owner. This prototype maintains current answers and input
epochs; it does not produce signed query deltas, recover durable sessions, admit
SQL ordering, or automatically select a star plan through C05.

The source implements a real heavy/light partition. A light satellite update
visits that key's center rows. A heavy satellite update visits reverse-indexed
groups and changes their liveness, without walking their center rows or output
projections. Both paths use the original finite query account and an inverse
journal over touched records. Existing complete source validation has its own
cost and allowance.

## Admit the exact family

The caller supplies a genuine direct-CQ `PhysicalPlan` and explicitly chooses
the center occurrence with `planner::star::admit(general, center)`. Admission
requires a nonconstant tree route with exact non-null set semantics:

- The center has positive arity `d`, contains every query variable, and uses a
  different variable in every field. Its physical field order defines coordinates.
- Every other query atom is unary, on one center variable. Satellites use distinct
  coordinates and distinct physical tables, including a table distinct from the
  center. Aliases do not establish self-join freedom.
- Every center variable absent from the head has a satellite. Coordinates without
  satellites are free output variables whose satellite predicate is conceptually
  true.
- Ordered/repeated head positions and aliases survive. `j` is the number of
  **distinct** head variables; it can be smaller than the output tuple width.

Constants, ignored/repeated center terms, binary-spoke stars, payload-bearing
satellites, duplicate satellite coordinates, self-joins, normalized SQL and
constant operators fail admission. Nullable, bag and aggregate APIs retain their
separate boundaries. There is no arbitrary 64-coordinate bit-mask limit.

This is Definition 4.5 of P2, with arbitrary center/head ordering represented by
explicit coordinate maps. Admission's `dimension()` means center arity `d`.
For full heads with fewer than `d` satellites, it can differ from the paper's
structural dimension in Definition 4.2. For example, `R(x,y), S(x)` with full head
is q-hierarchical. No matching lower-bound or optimality assertion follows from
calling its center arity two.

Admission throws `star_admission` for unsupported structure and `star_work_limit`
when its shared selected-work allowance is exhausted. Source-only lowering keeps
its existing independent limits and failure categories. The cold wrapper retains
the original general plan and ordinary compiler-owned maps; it publishes no
partial plan on refusal and supplies no new minimum-height certificate.

```cpp
// general is an already checked direct-CQ PhysicalPlan; center is its occurrence.
auto selected = crown::planner::star::admit(general, center);
crown::runtime::star::Options options;
options.sources.support.memory_limit_bytes = 64 * 1024 * 1024;
crown::runtime::star::Runtime owner(selected, options);

auto epoch = owner.apply(update); // Contiguous original physical source sequence.
auto cursor = owner.results();
while (auto tuple = cursor.next()) {
  // tuple owns its payload. Result order is unspecified.
}
```

The constructor starts with empty sources. There is no bulk initial-state port:
load through serial updates that satisfy enforced constraints after every epoch.
`program()` retains the genuine original answer program as schema/comparison
authority. Its general execution guarantee does not describe this star owner;
use the star candidate/cleanup profile below. The private source
coordinator instead has the complete original catalog/options and an empty
constant-true query, with no generic occurrence routes. Its identity is not the
star answer or an original-query minimum proof.

## One source and view publication

`Options::sources` configures the existing physical coordinator. It retains all
original source tables and validates their full after-state, including updates
to unused tables and enforced UNIQUE/FK targets. `Options::work` is a separate
heavy/light balance shared by the complete `apply()` operation. No per-row,
migration or histogram call mints a new allowance.

`Options::metadata_work` is a separate cold import grant for the retained
original query/schema program. Its structural-step, scalar-field, scalar-byte,
pointer-slot and link-action limits are each capped by the genuine indexed
plan's per-operation policy when that policy exists. This original-account
grant is created once during construction and is never recreated by updates.

A source token prepares the physical update. Derived view edits use one inverse
journal: detached nodes retain erased payloads, insertion undo identifies the
inserted value, and small scalar/link edits save their previous bytes. New map
nodes and journal capacity are funded before mutation. Failure reverses the
touched view edits and abandons the source/H tokens, leaving the prior sources,
answers and sequence valid. This is incremental rollback, without copying the
whole star state or adding a catch/retry framework around the update path.

After all fallible edits and token creation finish, valid source commitment,
histogram commitment and journal publication form one serial barrier. A local
writing guard keeps mutable view/source reads unavailable through all three
commits and private journal retirement, including allocator callbacks.
`Epoch` reports sequence, physical membership change, inherited `PhysicalMetrics`
and selected star `Metrics`; it is not a signed answer-delta object. Duplicate
insertion and absent deletion still commit an input epoch but do not alter the
star view or H. Unused-table updates retain the same source/constraint contract.
`center_visits` counts both passes of a migration; `migrated_rows` counts a row
once per relabeled key. `group_visits` counts heavy-satellite reverse-index
entries, rather than every group dictionary lookup.

The source coordinator and star indexes, metadata, inverse records, cursor
scratch and owning outputs share the coordinator's original finite account.
Ordinary caller input/export DTOs and cold compiler wrapper allocations remain
their declared external boundaries. The original comparison program's metadata
is retained; an additional generic join-maintenance runtime is not hidden inside
the star owner. [Query memory](query_memory.md) describes account versus RSS/work
and the existing compiler/export distinctions.

## Degrees, labels and groups

For each coordinate, degree counts **center rows**, independently of satellites.
The exact generalized H is

`h_i = max { r : at least r positive-degree keys have degree >= r^(d-1) }`.

The empty value is zero and the profile uses `h = max_i h_i`. For `d=1`, every
positive key meets the exponent-zero threshold, so H is the number of positive
keys. It is not maximum degree, `sqrt(N)`, or ordinary graph H for every arity.
A degree-zero key is absent from the histogram; a real satellite's present key
can still be retained with degree zero so future center insertions see it.

`HIndex` maintains occupied degree frequencies plus suffix counts at `h_i^(d-1)`
and `(h_i+1)^(d-1)`. One incidence changes H by at most one. The next suffix is
obtained from the occupied buckets inside the changed integer threshold interval,
with a virtual old/new degree adjustment. Preparation does not mutate H; it funds
a possible destination bucket and returns a private no-allocation commit token.
Commit and ownership moves clear retired iterator dependencies before later
histogram changes can invalidate them.
Checked integer powers use an explicit mathematical-infinity value after overflow.
No floating-point estimate, wraparound or full key census determines H.

Each coordinate stores an epoch scale `s = max(1,h_i)` at reset and threshold
`tau = (s+1)^(d-1)`. Between resets, a light key promotes only above `2*tau` and a
heavy key demotes only below `tau/2`; equality retains its existing label. A reset
occurs when heavy count exceeds `2*s` or `2*h_i < s`. It collects old heavy keys
and old light keys in the relevant degree-bucket band, then migrates only keys
whose label changes. It does not rebuild unrelated low-degree rows or traverse
an enormous unchanged heavy key's row bucket. These are explicit local repairs,
separate from the paper's whole-database rebuild argument.

A center row belongs to one key record per coordinate. Its `missing` count tracks
absent **light** satellites. A row with no missing light predicate contributes to
one group, keyed by the complete dynamic heavy mask and heavy coordinate values.
The encoding stores a flag and value per coordinate, rather than a fixed word.
Each group owns counted distinct full-head projections and a support total. Its
separate missing-heavy count determines whether it belongs to the live-group set.
No eager global union of live-group outputs is maintained.

| Input or internal change | Actual view work |
| --- | --- |
| Center insertion/deletion | One fact and its coordinate memberships/degrees; prepared H changes; affected projections and any required local migrations/resets. |
| Light satellite insertion/deletion | That key's incident center rows; light-missing zero crossings attach/detach their counted group projections. |
| Heavy satellite insertion/deletion | That key's reverse group index; heavy-missing zero crossings change live-group membership. No center-row or projection scan. |
| Label migration | Detach the key's incident VS contributions, change its label, recompute light-missing counts and reattach eligible rows. Real sources/degrees/H remain unchanged. |
| Last support or source key removal | Reclaim empty projections/groups/reverse records and degree buckets. Retain a zero-degree key only for an actually present real satellite. |

For fixed `d`, every committed group/projection has a center-row witness, giving
linear view space with explicit coordinate/index factors. Cursor scratch, source
storage, transient journal/node capacity and retained results are additional
simultaneous uses of the same finite account.

## Projection cursor and costs

`results()` pins one committed view. Each live group supplies its distinct head
projections. For a fixed output, hidden light coordinates have already collapsed
within a group; each hidden heavy coordinate chooses one of its heavy keys.
Therefore an output occurs in at most

`Kdup = product_hidden_coordinates (1 + heavy_keys_i)`

candidate streams. The cursor processes up to
`K = min(max(1, center_rows), Kdup)` candidates before emitting one queued unseen
output. A seen set suppresses repeats across masks/groups. Until exhaustion,
every complete candidate quantum contains enough total distinct outputs to keep
the queue productive. Full heads have `K=1`, including repeated ordered head
positions; `j` still counts distinct variables. Boolean projection uses this
same cursor; `has_answer()` separately tests live-group nonemptiness directly.

Under the label invariant, this is a local bound of
`O_d((h+1)^(d-j))` selected candidates for first/next/end production, with
`O(number of distinct answers)` seen/queue scratch. Cursor construction also scans
the fixed query's coordinates and allocates its control/deque structures. The
budget covers the cursor's complete lifetime, not a fresh grant on each `next()`.

Every dictionary here is an ordered standard container. Its logarithmic
comparison factors, scalar/string widths, tuple copying, actual allocation and
account bookkeeping are additional costs. H tracking visits at most the occupied
buckets of an integer interval of width `O_d((h_i+1)^(d-2))` for `d>=2`; it is not
generally constant-time. Sparse reset and hysteresis provide the local amortized
view argument, with actual map/journal/migration costs retained. Complete source
constraint scans, compiler/lowering work and any output materialization are also
separate from the selected heavy/light counters.

Drain through terminal null or call `cancel()` before updating. Multiple cursors
need external serialization and each consumes its own scratch. Update while a
reader is live fails with `star_busy`. A cursor retains its owner, and returned
tuples retain separately funded row/layout ownership after cursor/runtime release.
Cursor failure cancels it and releases its lease. Exhaustion/cancellation clears
the seen set and queue in `O(cursor scratch)` work; releasing the final owner can
also destroy source/view state. There is no end-to-end constant termination-delay
or wall-clock guarantee hidden in this cleanup.

`state()` returns original-account owning dimension gauges. `key()` probes one
coordinate's exact degree/label/presence. `source_snapshot()` is an explicit
ordinary caller DTO export with full source scan/copy cost. `check_invariants()`
uses a bounded cold inspection grant and original-account scratch to examine
internal fact/group/degree/H links and counts. Independent original-CQ answer and
source agreement remains a separate oracle obligation.

## Paper authority and validation boundary

P2 is Qichen Wang, *Towards Parameterized Hardness on Maintaining Conjunctive
Queries*, [arXiv:2603.14754v1](https://arxiv.org/pdf/2603.14754v1), exact PDF SHA-256
`7caf15377e5cd2b4d38cd207ba8f88e3d4b04debcbe463d8ecab99af2bee4491`.
Definition 4.5 is on PDF p14; Definition 5.1 and Proposition 5.2 are on p16;
partition/view/update discussion is on pp16–18. Theorem 1.4, p3, states linear
space, amortized update `O(h^(d-1))` and delay `O(h^(d-j))` under its premises.

The [primary audit](../build/verification/v68-star-proof-v1/audit.txt) identifies
independent gaps in the whole-source rebuild inequality, distinct-projection
delay argument and histogram suffix mechanism. The per-group support model,
two-suffix H tracker, sparse reset and paced seen/queue scheduler above are local
engineering/proof repairs. This ordered-container, accounted prototype does not
claim the full P2 theorem or a new lower-bound optimum. Its cold compilation,
source validation, atomic rollback and cleanup have their own implementation costs.

The runtime unit/oracle sources describe degree, branch, projection, rebalance,
source, lifetime and refusal checks. Authorship and this guide are not executed
acceptance. Current-source Release and ASan/UBSan receipts, independent A04/oracle
agreement and source-bound contract receiving must be inspected separately before
the X03 ledger is marked verified. No source file, passing fixture or paper
citation alone proves every supported update sequence.
