# Indexed storage and runtime integration (S04)

S04 is implemented and verified. Its dated gate ran all 199 native tests in five
complete configurations with exact operation/failure boundaries, actual command/symbol
audits and current source/evidence controls. See the qualified
[verification record](verification/indexed-runtime-2026-11-08.md).
S01–S03 and C05 remain verified historical predecessors.

`PhysicalOptions::indexed_storage` selects the indexed backend explicitly.
An absent value retains the reference backend and version1 physical options,
artifact serialization and physical binding. A present `IndexedBackendSpec`
uses strict version2 options/artifacts and the `crown-lower-v2` binding domain.
The semantic query identity is unchanged. All nine component limits and five
native index work limits participate in the physical/layout and C05 source/cache
bindings. A different backend or limit is a different physical configuration.
The artifact reader rebuilds and compares the complete verified lowering.

```cpp
PhysicalOptions options;
options.indexed_storage = storage::IndexedBackendSpec{
    {4096, 64, 32768, 65536, 131072, 524288, 8192, 32768, 8192},
    {1000000000, 1000000000, 1000000000, 1000000000, 1000000000}};
auto plan = planner::lower_tree(catalog, query, tree, options);
auto owner = runtime::PhysicalRuntime::initialize(plan, initial_database);
```

These example counts are finite configuration values, not a sizing or speed
recommendation. `IndexedLimits` fields, in order, are rows, indices, keys,
memberships, nodes, directory slots, arena slots, arena pins and journal entries.
They apply to each table, including detached undo-owned nodes. Arena slots
include live, retained, free and exhausted metadata; pins include externally
retained change views. Zero permits no population in that component.
They do not bound allocator bytes, peak memory or independent query owners.

`IndexWork` fields are structural steps, scalar fields, scalar payload/framing
bytes, initialized/reserved pointer slots and link actions. These are
conservative native storage admission units, separate from existing logical
support/build/delta/capture counters and allocator or CPU measurements.
Admission checks all domains before decrementing any of them. A failed attempt
keeps work already consumed. An allowance cannot be copied, moved or refilled.

The runtime composes one native storage allowance across an initialization,
physical update and all of its logical table journals, a whole result-cursor
lifetime, or one owner-capture request. Nested calls reuse the allowance.
Prepared update advances, epoch views and result `next()` calls retain their
original lease. Rebuild gives original-owner capture its own finite operation
and uses one target grant across target initialization and live bootstrap.
The immutable plan supplies these grants; there is no per-table or per-step
reset. A bulk diagnostic snapshot may require more work than an individual
update and must fit the same declared per-operation maximum.

Primary, logical-ID and secondary-key directories use stable nodes and cached
hashes. Exact typed equality decides membership, including nullary keys,
decimal aliases, dates and binary strings. Counts and annotations never serve
as empty-key sentinels. Dedicated live lists drive row, key and member
traversal; a borrowed cursor entry avoids a second logical-ID lookup. Rehash
preserves addresses, logical IDs and live order. Rows use insertion order and
keys use first-live-key order. Ordinary mutations invalidate cursors. Active
journal cursors carry a journal lifetime token; owner/revision/token checks
precede dereferencing a borrowed pointer.

Each storage mutation completes throwing preparation and admits its inverse
and finalization work before changing its links. Journal commit and rollback allocate nothing and request no new
grant. Failed multi-table updates preserve the complete prior committed epoch,
including handles and metadata. Physical directory capacity can remain grown.
Unpublished tentative IDs can be reused after rollback; committed IDs are not
reused. External pins and committed change views can retain values after table
or facade destruction without retaining membership.

Standalone `StorageTable` dispatches the ordinary reference and indexed tables;
`PlanStorage` initializes that compiled relation/index program. These interfaces
remain available for primitive tools and differential comparisons. Current
Support, physical sources, delta processing, sessions and C01 owner capture use
`AccountedStorageTable` / `AccountedPlanStorage` with immutable `CompiledProgram`
metadata and their original query account. Their retained rows and metadata use
the native byte-account contracts in [query memory](query_memory.md).

Both routes preserve the shared indexed admission rules. Accounted runtime
operations retain one `AccountedIndexWork` owner; any legacy allowance view aliases
that same balance. Index/journal construction creates no independent grant.
Direct standalone primitive callers supply an `IndexWorkAllowance` themselves.
The explicitly named `ReferencePlanStorage` rejects an indexed plan. Component
count/work limits in the ordinary backend do not independently fund its standard
containers or prove native requested-byte accounting.

Hash-directory expected time assumes distributed hashes. Adversarial collisions
have linear chains whose visited nodes and equality work are admitted. Ordered
support/delta metadata and explicit diagnostic/capture processing retain their
own costs. No whole-runtime constant-time bound or speedup is asserted here.
C02 tuple/index-slot estimates remain relative structural models; allocator
byte/peak prediction and C03 calibration remain separate work. A02 distribution licensing and the remaining release/recovery gates are open. S05
verified the post-admission native query-account cap and operator reconciliation;
see the [query memory contract](query_memory.md) and [S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md).

## Finite primitive measurements

The historical standalone `StorageTable` comparison retains 80 raw samples/40 paired
runs and 136 timing groups: populations 16/256/4096/16384, payloads 2/258 bytes,
fixed secondary-key degree 16 and five alternating repetitions. Complete-row
oracles and paired checksums match. Input materialization, construction, load,
replacement, trim and destruction remain visible in the raw records.

Ratios below are indexed/reference median time across the eight population/
payload cases. The finite fixture shows both improvements and regressions.

| Operation | Indexed/reference ratio | Observation |
| --- | --- | --- |
| Secondary-bucket walk | 0.340–0.818 | Faster |
| Primary hit/miss probes | 1.378–7.647 | Slower |
| Eight-live walk after history | 1.310–1.408 | Slower |

Eight-live traversal admits exactly `{10240,0,0,8192,0}` for all tested histories
and payloads. This includes 1024 cursor startups, eight advances and end per
cursor, plus eight pointer words of startup metadata per cursor. Pointer-word
admission is separate from allocator bytes and CPU time. These observations
establish no universal or whole-runtime speedup. Those samples predate the
verified B03 measurement harness and C03 cost-model work; their scoped evidence
is linked from the [current ledger](task_ledger.md). B05 adversarial scalability
experiments remain open. All slow S04 cases stay in the original evidence packet.
