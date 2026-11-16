# Source-grounded S04 design map

This is a read/impact inventory, not an input freeze or implementation map.
All paths below already exist unless expressly labeled as proposed. No listed
native source has been edited for this design.

| Existing source | Contract or impact |
| --- | --- |
| `Refactor.md`, sections 6.2, S01–S05 and D05 | Exact native membership, live-only iteration, ownership, conditional hash bounds and separate allocator accounting |
| `include/crown/ir/ids.hpp` | StorageOwnerId/RelationId/TupleId public handle shape; separate generational ArenaHandle |
| `include/crown/storage/layout.hpp`, `src/storage/layout.cpp` | Immutable runtime tokens; exact typed/repeated-field validation; numeric projection ownership |
| `include/crown/ir/scalar.hpp`, `src/ir/scalar.cpp`, `src/ir/model.cpp` | Canonical Decimal/date semantics, exact equality/order, existing typed hash and allocating Decimal formatter |
| `include/crown/storage/arena.hpp`, `src/storage/arena.cpp` | Payload ownership, pins, live/free lists, generations and private rollback revival |
| `include/crown/storage/reference.hpp`, `src/storage/reference.cpp` | Independent standard-container oracle; shared owner allocator to factor; revisions, snapshots, live/bucket/key cursor contracts and retained-node journal undo |
| `include/crown/storage/physical.hpp`, `src/storage/physical.cpp` | Concrete reference plan storage, exact logical index requirements and full owning copies with fresh owners and preserved live logical IDs |
| `src/planner/lower.cpp`, `include/crown/ir/physical.hpp` | Relation/index layout sharing, finite native lowering and fixed reference backend profile |
| `src/io/physical.cpp`, `schemas/physical-plan-v1.schema.json` | Strict complete replay and fixed v1 backend; a new backend needs an explicit versioning decision |
| `include/crown/runtime/support.hpp`, `src/runtime/support.cpp` | Concrete table-journal ownership, reverse buckets and enumeration; diagnostic snapshots inherit traversal order while canonical state explicitly sorts |
| `tests/unit/support_api_test.cpp` | Existing exact ProjectionSupportCount boundaries above 2^53 and at uint64 overflow; retain separately from optimized membership tests |
| `src/runtime/physical.cpp` | Concrete physical source tables, key/foreign-key checks, alias atomicity and actual owner boundaries |
| `include/crown/runtime/delta.hpp`, `src/runtime/delta.cpp`, `src/runtime/replay.cpp` | Actual ordered backend profile and separate L/P/B/anchor structures; no automatic complexity upgrade |
| `include/crown/runtime/statistics.hpp`, `src/runtime/statistics.cpp`, `src/runtime/owner_statistics_detail.hpp`, `src/runtime/owner_statistics.cpp` | Reference-specific capture signatures; live key/degree borrows, bounded exact scalar reads and owner freshness separation |
| `src/planner/ranking.cpp`, `src/planner/ranking_payload.cpp`, `src/runtime/ranking_evidence.cpp` | C02 source/model assumptions and candidate-local logical slots, not hash capacity/bytes |
| `docs/verification/c05-selection-implementation-proposal/overlay/src/planner/selection_binding.cpp` | Currently held C05 complete source/cache encoding; new physical backend fields cannot be omitted |
| `docs/storage.md`, `docs/tuple_arenas.md`, `docs/storage_journal.md`, `docs/ordered_delta.md`, `docs/physical_plans.md`, `docs/statistics.md` | Current public lifetime, invalidation, complexity and capture limitations |
| `docs/source_baselines.md` | Existing independent implementation provenance; A02 remains open; no copied DynaGox license assumption |
| Existing storage/arena/layout/journal/epoch/statistics native tests | Retained baseline plus independent new oracle/fault/traversal requirements |

Proposed new locations, subject to root API review, are
`include/crown/storage/indexed.hpp`, `src/storage/indexed.cpp` and private
directory/node/journal helpers under `src/storage/`. A backend-neutral facade,
successor physical format and runtime initialization option are later explicit
design decisions, not existing APIs. Test/oracle/benchmark locations would be
new native paths only after an excluded implementation is reviewed.

No current source hashes or package seal are frozen here. The design still
requires decisions on finite defaults, load/growth policy, runtime exposure
scope, backend-aware artifact/capture contracts and the exact independent
measurement plan before implementation authorization.
