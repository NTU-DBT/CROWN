# S04 independent acceptance plan

This is a plan, not executed coverage. There are no claimed operation totals,
benchmark gains, sanitized outcomes or completed native gates.

## Independent semantic oracle

Use three independently owned states for each trace: untouched S02
ReferenceTable, new IndexedTable and a small map-of-sets oracle keyed by an
independent canonical scalar representation. Do not use the new backend's
hash/equality/projection helper to compute expected membership. Compare logical
rows and projected buckets, not owner IDs from distinct instances. Within each
owner, separately verify logical IDs, stable arena addresses/generations and
foreign/stale-handle rejection.

The scalar oracle uses exact signed integers, raw unsigned-byte strings,
Boolean tags, independently checked date values and sign/coefficient/scale
Decimal normalization. Literal cases include int64 extremes, values around
2^53, canonical Decimal equivalent spellings, negative zero, signs/scales and
38-digit boundaries, empty/NUL/high-byte strings, composite/reordered/repeated
fields, nullary keys and wide layouts. Equal independent descriptors must still
fail token admission; shared target tokens must permit legitimate cross-source
probes.

Generated traces cover duplicate insertion, absent row/handle/key erase,
last-member key deletion, new/repeated/dropped indices, erase_key, clear,
snapshot copies and move/destruction. Check every affected bucket and all
live/key/member cardinalities after each step. A successful no-op preserves
revision, cursor validity and all committed structural counters.

For owning plan-storage copies, create gaps in live TupleIds/IndexIds before
copying. Check preserved IDs, last-ID counters, projection tokens and exact
optimized traversal order alongside fresh storage/arena owners and payload
addresses. Old handles must be foreign to the copy; source pins to retired
rows must neither appear in it nor be invalidated. Mutate and destroy each
owner independently. Reject copying an active journal, sweep copy allocations
and positive work boundaries, and require that failure leaves the complete
source, cursors and pins unchanged before a successful retry.

## Collision and traversal oracle

Exercise ordinary typed hashes and a private test-only forced-collision seam
that makes distinct keys share every directory bucket. No unchecked hash or
node pointer becomes a public insertion capability. Separate test variants
must not mix incompatible definitions with production archives.

Under forced collisions, compare every lookup/erase/duplicate with the oracle,
including same-text/different-type values. Visit each live row/key/member once
and no retired entry. Verify empty/first/next/end behavior under large retained
capacity with tiny or empty current membership. Rehash must preserve traversal
order and every payload address/pin. Churn at bounded simultaneous population
must recycle nodes and release key/value payload rather than grow one object
per historical operation. Report retained capacity separately from live state.

Secondary membership must be independent of an external exact payload count.
A test-owned payload driver uses exact uint64 values above 2^53 and at the
uint64 boundary: changing that payload, including to zero, does not itself
change key membership. Only explicit exact insert/erase events do. This is a
storage separation test, not a fabricated valid runtime P/E census or proof of
S05's future counter/allocator implementation. Retain the actual existing
`ProjectionSupportCount`, `increment_support` and `decrement_support` tests in
`tests/unit/support_api_test.cpp`: they check `(1 << 53) + 117`, exact increment
to UINT64_MAX, overflow/zero-limit rejection and exact decrement/underflow.
The optimized index must not add a numeric payload parameter that can become
an occupancy sentinel; its membership remains node existence with exact typed
key equality. These type/source invariants and the scalar-key fixtures are
separate from the checked support arithmetic test.

For an actual runtime integration, retain and extend only reviewed testing
probes on real admitted owners. Native `RuntimeTestProbe::set_projection`
changes an existing key's count, not its row membership; any extreme injected
value must be restored before ordinary invariants or public captures are
claimed. A fault/probe boundary is not a valid observed huge-cardinality epoch.
No public proof or evidence factory is introduced to reach these branches.

## Journals, pins and failure atomicity

Exhaust deterministic short operation sequences that interleave erase/insert
of the same row and same projected key, all members disappearing/reappearing,
different keys colliding, growth between deletes, and neighbor nodes erased
before/after an undo record. Check exact LIFO restoration of IDs, original
payload addresses/generations, live/member order and all index memberships.
Verify private empty-key retention never leaks into live iteration or counts.

Check counter publication separately from row equality. A journal containing
changed insert/erase work may end with its original row set; successful commit
still records that primitive work, while rollback discards its pending
committed-action totals. Attempt/abort diagnostics may differ under their stated
rules. Neither quantity is an inferred C01 root-update or derivation count.

Keep pins through erase, clear, owner moves/destruction, rollback and committed
journal destruction. Check that pins preserve payload only, not membership or
cursors. Test ordinary versus owner-journal cursors, old committed readers
blocked by a new journal, mutation invalidation, rollback invalidation before
inverse links, empty/moved-from cursors and stale/foreign owners in all builds.

Measure each actual operation's allocation positions, then inject persistent
failure at every reached position across key/projection/Decimal copies, arena
allocation, nodes, directory growth, add_index, erase_key preparation, journal
creation/entry growth, snapshots and facade construction. A failed mutation
must preserve complete prior logical state and existing results/pins, with
only the separately disclosed arena/capacity metadata and attempt diagnostics
permitted to differ. Restore fault injection and require successful retry.
Commit/rollback/retirement must run under persistent failure without allocation,
termination, recursion growth or partial publication. Do not sample positions
and call that an exhaustive sweep.

Use private checked-counter boundaries for owner/tuple/index/revision exhaustion
and capacity arithmetic only after their test authority is reviewed. Never
manufacture a public proof, physical plan or accepted owner snapshot to reach
a storage counter branch. A wrapping structural count or ID is a failure.

## Finite work and performance evidence

For each positive measured work/capacity component, test its exact grant and
one-under rejection, separately from zero/disabled cases. Include long strings,
Decimal formatting, collisions, growth-array initialization, relocation,
retained journal empties and finalization. Failures must publish no partial
mutation and must not invoke an implicit alternative backend. Rollback uses
already prepared resources, not a fresh grant that can fail halfway.

Benchmark actual S02 and optimized operations on the same independently checked
trace and compiler profile. Separate lookup, insert, erase, add-index, growth,
live traversal, key traversal, bucket startup/advance/end and churn; expose
row/key width, fan-out, skew, collision population and retained capacity.
Repeat timing samples and report the environment and spread. Include cases
where optimization loses. Operation counters support causal interpretation;
they are not nanoseconds or total allocated bytes. No performance result is
claimed before root executes and accepts these measurements.

## Runtime and native gates

If runtime exposure is included, run unchanged reference-mode cases plus new
backend cases through actual support, physical alias routing, delta replay,
result/epoch cursors, sessions/windows and initialization/rebuild. Compare
canonical committed state and result sets after each trace step, complete
rollback under failure and exact C01 full-capture facts. Test backend/profile/
artifact rejection and cache-binding separation, not just equivalent answers.

Every old test remains registered. Root must run the full applicable Debug,
Release, Clang, ASan/UBSan/leak and fresh clean-source matrix, coherent macro
variants, source/ABI/dependency audit and independent review. A storage-only
success does not accept a later facade, profile, report or runtime migration.
A02 and S05 boundaries remain explicit. No task status changes follow from
this design draft.
