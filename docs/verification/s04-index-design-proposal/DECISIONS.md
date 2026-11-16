# Decisions required before S04 implementation

These recommendations are source-grounded design choices, not an approved API
or a permission to change native code. The reference backend and all frozen
C05 evidence remain untouched.

| Decision | Recommended first implementation | Reason and remaining obligation |
| --- | --- | --- |
| Native provenance | Independently implement the stable-node directory; copy no legacy or external hash implementation | Avoid inventing an audited adaptation or resolved A02 distribution license; retain an exact source/provenance review |
| Storage placement | Separate `IndexedTable` plus a shared internal owner allocator | ReferenceTable remains the S02 oracle; duplicate StorageOwnerId allocators would break cross-backend handle rejection |
| Collision strategy | Chained stable nodes with exact equality and explicit work limits | Rehash does not move tuple payloads; live links do not scan tombstones; adversarial chains still have honest linear cost |
| Node deletion | Nonowning predecessor links plus independent row/key/member live lists | Known-node erase and undo need no chain search or stale pointer into a retired array |
| Capacity | Required finite maxima, lazy eight-slot arrays, doubling and 3/4 load as the initial measured policy | Admission counts privately retained directory nodes; no unlimited default, floating-point load test or S05 byte claim |
| Index registration | Existing Projection token identity, independent IndexId for independently constructed programs | Preserve current S01/P08 authority and identical-index-sharing semantics |
| Traversal | Explicit deterministic insertion/first-live-key order for the new backend | Preserve live-only steps without hidden sorting; retain canonical owning snapshots as separately charged work |
| Hashing | Initially preserve the exact native typed hash bytes and pre-admit its Decimal formatter | The current formatter can allocate even on a lookup; do not claim allocation-free Decimal probing or a speedup before measurement |
| Mutation resources | One finite aggregate grant for a transaction, including reserved inverse/finalization work | Per-operation fresh grants cannot bound a long journal; rollback cannot be stopped halfway by resource exhaustion |
| Runtime publication | Explicit opt-in backend and complete profile/artifact/capture/cache review before any owner uses it | Existing owners are concrete reference storage and physical v1 says reference ordered; an unused primitive alone does not complete a production integration claim |

The operation interface should preserve existing Tuple/Layout/Projection,
TupleHandle, InsertResult and TupleArena::Pin authorities. A new raw pointer,
unchecked owner constructor or payload-count sentinel is unnecessary. The
exact finite-budget token and cursor-budget signatures need root review before
implementation, because existing ReferenceTable has no such parameter and
runtime journals currently name its concrete Journal type. A proposed facade
must specify how one actual owner transaction passes the same remaining grant
through all table/index operations; it must not silently translate an absent
legacy runtime work limit into unlimited storage work.

Do not promise allocation-free construction or gaps-free global owner IDs.
Existing owner construction can consume a unique owner ID before a later
allocation fails. The shared authority must never recycle that ID or change
reference-only behavior. Failure atomicity concerns already published state,
logical table counters and handles; unique process-wide owner allocation is a
separate lifetime boundary.

The first measured policy should keep reference storage as the default. A
future change of default requires its own actual-workload evidence and an
explicit artifact/profile compatibility decision; an observed microbenchmark
win does not authorize changing existing serialized plans, owners or caches.

## Conditions for authorizing an excluded implementation

Root should settle the exact operation-budget shape, capacity-policy version,
test-only collision/counter authority and native integration extent before code
is written. The implementation plan must cover all chosen stages, including
complete rollback, index construction/drop, clear, snapshots, cursor ownership
and abandoned-journal destruction. No placeholder method or unbounded fallback
may be silently omitted to make the primary lookup benchmark pass.

The scalar formatter choice is a visible performance tradeoff. An allocation-
free scalar hash visitor may be reviewed later, but would need exact equality
and old-hash-byte proofs, exhaustive scalar boundaries and coherent dependent
rebuilds. It must not be treated as an already available public Decimal API or
introduced through an unchecked view of private storage.

Before native verification, resolve how optimized plans are represented and
reported, how C01 visits the actual backend, and how C02/C05 either bind every
new physical option or fail closed. The S05 allocator/peak budget, C03 event
model and automatic plan deployment remain separate cards. This draft makes
no card-status or completeness assertion while these decisions are open.
