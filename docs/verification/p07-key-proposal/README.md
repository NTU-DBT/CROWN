# P07 structural-key worker proposal

**Proposal only. P07 remains `not_started`.** These files are isolated under
`docs/verification`; they are not part of a repository target and do not change
any P05 sanitizer input. The machine has no binding, P02 checker, minimum-proof
or candidate-publication authority. Isolated compilation checks only that this
proposal is well-formed C++; it is not a P07 verification result.

## API and precondition

`key_machine.hpp` declares `StructuralKeyMachine` in
`crown::planner::alternatives_proposal`. It owns a
`shared_ptr<const FreeConnexTree>` and the generator proposal's shared
`ContentBudget`. The caller must first have P02 checked that tree against the
original binding. The binding and context are not inputs to this worker, so its
token cannot establish validity, minimum height, or globally unique plan
identity.

`step(UnitContext)` exposes `advanced`, `key_ready`, and `stopped` with the
requested depth or a stop reason. It reuses `GeneratorStop` through the shared
`ContentStop` type and adds `cancelled` and `invalid_input` at the key API
boundary. `std::bad_alloc` escapes; the pending producer operation remains
installed for a same-owner retry. `key()` returns an immutable owning
`shared_ptr<const string>`. Repeated ready observations return that same handle
without more work. A completed key survives cancellation and machine
destruction. The machine also exposes scalar step/node/comparison counts,
current traversal depth, cancellation, and noexcept moves. It has no clock or
`WorkQuantum` facade.

The input owner is retained throughout the cursor; no borrowed spans or arrays
escape. Empty input has a separate key. For a nonempty tree, the depth ceiling
must permit the root frame before traversal starts; a zero ceiling therefore
blocks before that push. `current_depth()` counts the actual owned iterative
postorder frames. No recursive tree traversal or recursive child-token
serialization is used.

## Canonical token

The encoding begins with the versioned prefix
`CROWN-STRUCTURAL-KEY;1;`. Empty is followed by `X;`. A nonempty key is followed
by `R`, the decimal byte length of the root token, `:`, and the complete root
token. Each node token contains tagged kind, native occurrence-presence/value,
scope-count and scope values, child-count and child tokens, plus an end marker.
Counts and numeric values are decimal with explicit tag/delimiter framing.
Every child token is framed by its exact byte length before its bytes. This
makes nested token boundaries unambiguous without escaping arbitrary text.
Native occurrence and variable IDs retain their original numeric values.

The root token recursively describes the rooted structure. Per-node scopes are
already sorted `VariableId` sets. Child tokens are sorted lexicographically by
their complete bytes, not by display or vector IDs. The cursor uses iterative
postorder frames and resumable insertion ordering. It retains the insertion
position, compared character offset, token append position, and publication
state in the coroutine frame. Each compared character, order-cell shift, and
output byte is a saved producer operation. A large subtree is never compared,
sorted, or copied in one blocking serialization operation.

The key includes the root, node kind, native occurrence identity, complete
scope, and every child subtree. It ignores display IDs, node-vector order,
child-vector order, and derived claims such as claimed separator, connex set,
and native height. The last three are safe to ignore only because the caller's
P02 check has already rejected false supplied claims. Changing a root, kind,
scope, or native occurrence changes the corresponding framed token. Equal-scope
self-join occurrences stay distinct because their original occurrence IDs are
preserved.

Token equality is structural equality **within an exact binding and context**.
It does not include Catalog/Query binding, ordered or repeated head outputs,
types, update assumptions, arithmetic, planner versions, or selection policy.
Future cache admission must compare and namespace by the exact Catalog, Query,
and validated context. A digest may later be an index only; retain and compare
the complete token and binding/context. This worker supplies no cache identity.

## Cursor and resource costs

Only the generator proposal's `ContentBudget`, `ContentStop`, and shared
continuation `UnitContext` are reused through the relative include. Control
flow uses the generic `producer_cursor` `Engine`, `Task`, and saved `operation`
mechanism. The coroutine frame is created by `step` after budget preparation.
All later allocations happen in saved closures outside coroutine `resume()`:
token slots, traversal frames, per-frame child-order cells, output bytes, and the
final immutable key publication. Each operation prepares the shared record or
cell budget, allocates or appends, then commits. A failed allocation does not
advance its cursor position or mark the key ready. Once the complete root token
has been copied into the final key buffer, token slots are released one per
saved operation before publication. These cleanup transitions do not refund
the cumulative content charges.

The logical content charges are:

| Construction | Records | Cells |
| --- | ---: | ---: |
| Coroutine control frame | 1 | 0 |
| Indexed node-token slot | 1 | 1 |
| Iterative traversal frame | 1 | 1 |
| Temporary child-order position | 0 | 1 |
| Encoded node or root-key byte | 0 | 1 |
| Published immutable key record | 1 | 0 |

Charges accumulate. The root token is copied byte by byte into the final
versioned key, so both token and published-key content are charged. This is a
logical content budget, not S05 allocator-byte accounting. Exclusions are the
input tree storage and shared ownership, inert Pimpl shell, `ContentBudget`
object, vector/string capacity and relocation, allocator metadata, scalar
decimal-conversion buffer width, comparator scalar state, per-slot cleanup
transitions after final-key assembly, and caller-retained immutable key handles.
These exclusions do not imply fixed physical time. Token-slot cleanup has
linear saved-step cost in the node count, while its original construction
charges remain cumulative.

Comparison is deliberately incremental but insertion sort may take quadratic
child-count comparisons, with each comparison proportional to common token
prefix length. Postorder tokens duplicate subtree bytes in ancestors, so total
token storage and key construction can also grow quadratically with tree size.
The full key is retained as equality evidence; no hash is computed here.
Container `max_size`, content counters, step/node/comparison counters, and
requested depth are checked before increments or appends can wrap. String
lengths use `size_t` directly for decimal framing instead of narrowing them.

## Missing gates and future acceptance

This worker does not run P02, confirm a height against `VerifiedOptimum`, admit
or publish `MinimumHeightCandidate`, deduplicate across seeds, or install a
cache entry. The future facade must leave the original proof unchanged, check
each candidate against the exact original binding, and compare checked native
height to the original proved minimum before using this key. It must keep the
full binding and context alongside the token in every cache/equality layer.

Before any integrated P07 verification claim, root-owned checks should compare
the token against separate reference logic; exercise empty and nonempty trees,
node renaming/reindexing and child permutation invariance, root/kind/scope/native
identity distinctions, and self-joins; then test P02-before-key admission and
same-owner depth/content/allocation-failure recovery. Repeated ready calls,
cancellation, moves, and immutable-handle lifetime also require runtime checks.
The independent normal-form set, minimum-height proof boundary, transactional
candidate deduplication/publication, exact-binding cache and full P07 acceptance
suite remain outside these three proposal files.

## Isolated compile check

The source is intended to compile alone with strict C++23 options, without
linking it into repository targets or running repository builds/tests. Compile
objects belong under `/tmp`. Any such compile is source-level evidence only;
root owns runtime checks and all acceptance claims.

Root later ran isolated smoke checks outside repository targets. All11 P02-
validated query/tree cases preserve the expected key equalities under node/
child/display-ID permutations and distinctions for scope and original self-
join identity. Head/type changes intentionally keep the structural token;
the future exact-binding cache must fence those namespaces. Repeated ready
observations, cancellation after completion and retained-key lifetime pass.
Actual key records are under ignored `build/verification/p07-key-preflight.json`.

The separate [fault probe](fault-probe.cpp) covers all17 observed allocations
on a checked three-node tree. Two persistent retries retain the same state,
then the same owner recovers to identical bytes, steps and content counters.
Zero-depth/zero-cell stops and monotone content extension pass. Output is
`build/verification/p07-key-fault-preflight.log`. These small proposal checks
do not constitute integrated P07 or cache/minimum-authority acceptance.
