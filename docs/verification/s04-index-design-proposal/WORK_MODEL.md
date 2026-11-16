# Proposed finite operation and traversal model

This is a design recommendation for review, not an implemented API, measured
speedup or accepted default. The native reference backend remains unchanged.
The optimized primitive needs a complete, reviewable charge table before its
implementation is authorized; a generic count of dictionary calls is
insufficient for variable-width keys and collision chains.

## Capacity policy

Require an explicit finite construction configuration. It bounds live rows,
registered indexes, live plus privately retained keys, memberships, row/key/
membership node shells, journal entries and directory pointer slots. A caller
must supply each maximum; this draft does not invent an unlimited or implicit
production default. Zero means that no corresponding object can be admitted.
Every count must fit both its exact public counter and the actual container's
size domain. Checked additions/products precede allocation or state change.

Recommend power-of-two directory lengths, lazy initial allocation of eight
pointer slots, geometric doubling, and an admitted load of at most 3/4.
Capacity tests use checked integer arithmetic, not floating-point division.
If the smallest required power of two exceeds the configured slot maximum,
the operation rejects before allocation; it does not silently exceed the load
rule. The caller can choose a non-power-of-two maximum, but only permitted
power-of-two arrays fit beneath it. Empty tables need no allocated directory.
This policy is a proposed reproducible baseline to benchmark, not a theorem
that it is the best policy for CROWN.

Count every node actually resident in a directory when testing its load.
In particular, journal-retained zero-degree key nodes are not live keys but
still occupy the secondary directory and affect collision work. Unlinked
retired row nodes remain in the separate retention/node-shell count. New arrays
are temporary until commit, while old arrays remain usable; capacity and peak
temporary allocation are different quantities. The component model must not
call its configured pointer-slot count an allocator-byte ceiling.

Logical TupleId and IndexId remain monotonic within their existing owner
semantics. They must not index an ever-growing sparse array. Use the same
bounded chained-directory primitive for logical IDs, with stable row/index
nodes and dedicated live lists. Index-directory lookup and registration work
must be charged as well as primary and secondary lookup work. Compiled
Projection tokens remain the registration authority; an ID hash is only an
exact-match search accelerator.

## Scalar work before opaque native helpers

The existing `row_hash` implementation hashes an eight-byte row length and,
for each field, a one-byte Value alternative followed by its payload framing.
The following conservative admissions can be computed from public typed values
without formatting them first:

| Value | Hash-framing allowance after its tag | Owned-copy or equality allowance |
| --- | --- | --- |
| int64 | 8 octets | fixed scalar work |
| Boolean | 1 octet | fixed scalar work |
| Date | 8 octets for the current epoch-day hash encoding | fixed scalar work |
| byte string | 8 + exact string length | exact string length, plus its field/control record |
| Decimal | 8 + 41 octets | 38 coefficient octets, plus its field/control record |

For Decimal, coefficient precision and scale are each at most 38. Native
`to_string()` produces at most sign + `0.` + 38 fractional digits, or 41
characters; the other formatting branches are shorter. Its internal temporary
strings can allocate. Reserve the bounded formatter admission before calling
it and cache the resulting hash before publication. This 41-character bound
does not count allocator overhead or all transient string allocations.

Do not expose Decimal private fields or manufacture a noncanonical value to
avoid that cost. A copy uses its existing canonical coefficient ownership.
Exact Decimal equality is nonallocating; its 38-digit comparison allowance is
conservative when fewer digits are inspected. A typed-hash optimization later
must retain the same scalar semantics and receive a separate equivalence and
allocation audit.

For strings, charge the exact length before a whole string hash/copy. On a
hash match, admit the worst-case equality work for the pair before invoking
the standard equality helper; use actual lengths and an explicit bounded
Decimal allowance. A different type or length can be rejected after the
corresponding descriptor work. Charge every inspected field and every
collision-chain node independently. A conservative byte allowance and an
actual visited-node counter are labeled separately; neither is elapsed time.

Projection admission walks the numeric field list, charges each selected
Value and its owned string/Decimal body, and accounts for repeated selections
separately. The list's work is finite even for nullary and repeated keys.
The already validated source Tuple and source/target token checks remain the
S01 authority; no inner-loop field-name lookup is introduced.

## Operation phases

| Operation | Throwing preparation and charged work | Nonthrowing publication/finalization |
| --- | --- | --- |
| Value find / bucket startup | Layout/IndexId validation; scalar hash admission; charged directory traversal and exact collision comparison | Publish a borrow or cursor only after successful admission |
| Handle get / pin | Validate actual owner/relation; charged logical-ID traversal and exact ID equality; prepare any pin bookkeeping | Return the existing live payload/pin; no membership change |
| Duplicate insert / absent erase | Complete the necessary bounded lookup | Report a no-op; no rehash, revision increment or committed-operation count |
| Changed insert | Prepare tuple ownership, projected keys, stable nodes, all index members, undo record and growth arrays; reserve all link/counter work | Link every prepared record and assign checked counters; publish the one new logical handle |
| Changed erase | Resolve the row and reverse members; retain pins/nodes/neighbor references; reserve all unlink/undo/finalization work | Remove memberships and live links; retire or retain the original nodes |
| erase_key | Find the bucket; traverse its live members once; prepare the whole affected set and reverse-index work | Remove the complete prepared set atomically; no per-row public commits |
| add_index | Validate Projection; stage one complete new index by walking live rows and projecting/hashing/copying each key; prepare directory/node growth and all reverse links | Install the index and every row's prepared reverse entry together |
| drop_index / clear | Admit all affected live-node/index/arena cleanup and cursor invalidation work before changing state | Unlink and destroy admitted objects without fresh allocation |
| Snapshot / keys / bucket materialization | Admit every copied field/body/vector element; separately admit canonical sorting when requested | Return an owning result only after it is complete |
| Owning table/plan-storage copy | Reject an active journal; admit all live tuple/key/member copies, preserved-ID construction and fresh directory/list rebuilding under one grant | Publish fresh independent owners only after the complete copy passes its invariants; retain no source membership pointers |
| Journal commit / rollback | Each changed operation has already retained its exact inverse and reserved finalization work | Visit affected entries only; use cached hashes and saved links; allocate nothing and never consult a fresh exhausted grant |

The planned reverse-membership representation must not copy an existing
unbounded per-row array during `add_index` after publication begins. Either
stage replacement reverse arrays for all live rows and swap them at commit,
or use stable membership nodes with row-local links. The choice must state
whether erase visits exactly the row's registered index members or searches
unrelated rows. Live iteration must not search hash capacity or arena slots.

Clear and index drop unlink the nodes on the relevant live/owned lists using
their cached hashes and predecessor links. They need not scan or zero a large
retained bucket array: after every resident node is unlinked, the corresponding
heads are already empty. Owner destruction still releases owned arrays, whose
allocator/deallocation cost is outside a live-cursor step. That separation must
be visible in counters and the churn experiment.

A journal receives one finite transaction allowance, not a fresh grant for
every insert/erase. Operation and inverse/finalization reservations consume
that allowance as preparation proceeds. A failed preparation leaves its
published logical state untouched; diagnostic work already attempted is still
reported. A later operation cannot consume resources reserved to undo prior
published tentative operations. This reserve must be represented in exact
checked counters and tested at positive exact/one-under boundaries.

## Complexity claims that follow, and those that do not

For a directory with load at most 3/4, well-distributed hashes and ordinary
successful growth, expected chain-search node work is constant and geometric
growth has amortized linear total relocation over a successful insertion
sequence. Exact scalar hash/equality/copy work is additional. These are
conditional algorithmic claims; FNV collisions can still produce a linear
chain and an honest finite-grant stop. Faulted preparations, retained journal
nodes and explicit index construction must be counted separately rather than
hidden in that successful-sequence amortization.

A live-row or live-key cursor starts at its list head and follows one link per
successful next step, plus end detection. A bucket cursor additionally pays
its one startup lookup, then follows exactly that bucket's live memberships.
No next step triggers rehash, scans empty capacity or sorts a snapshot.
Large retained capacity with zero or one live record is a required traversal
test, not just an informal complexity argument.

These bounds do not remove D05's witness preparation, separate ordered L/P/B
structures, public spool or termination/finalization costs. They do not claim
constant wall time for strings, allocator calls or adversarial inputs. Root
must require a source-to-counter argument and independent actual-operation
measurements before publishing any optimized runtime guarantee.
