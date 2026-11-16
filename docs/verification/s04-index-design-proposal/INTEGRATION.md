# S04 source/layer integration decisions

## What exists today

ReferenceTable and ReferencePlanStorage are concrete types, not implementations
of a shared virtual storage API. SupportRuntime's private State owns
ReferencePlanStorage; its journal header also names ReferenceTable::Journal.
PhysicalRuntime owns vector<ReferenceTable> physical sources. C01 storage
capture and OwnerBuilder accept ReferenceTable directly. A new backend therefore
cannot become active merely by adding another library or changing a string.

P08 shares index requirements by relation and ordered FieldIds, then verifies
the target layout token. ReferencePlanStorage instantiates exactly those
requirements. The optimized backend must consume this same logical specification;
it must not infer new equality from sorted/deduplicated fields or merge distinct
projection tokens. Repeated/nullary projections and all current relation roles
remain supported.

ReferencePlanStorage also exposes an owning snapshot_copy utility. Preserve its
fresh storage/arena owners, live sparse logical IDs, index requirement mapping
and last-ID/revision values in a backend-aware copy. The source must be outside
an active journal. An optimized copy rebinds every internal pointer and retains
the new backend's traversal order; it does not copy retired external pins or
silently share mutable membership. This full-state utility remains separately
charged and is not the affected-record update journal.

Physical-plan v1's schema fixes storage_backend to reference_ordered_v1, and
its strict reader rebuilds the entire physical artifact and compares complete
bytes. DeltaRuntimeProfile also names that backend. C02/C05 binding/model
contracts currently assume the native reference layout/index policy. These
are actual integration constraints, not already available extension points.

## Recommended stages

1. Audit and measure the current reference backend on actual typed operations
   before implementing a performance replacement. The existing C01 collection
   benchmark is not evidence that a particular S02 index is the bottleneck.
   Record complete semantic traces, widths, fan-out, degree distributions,
   allocation/collision work and ordinary/sanitized build flags. Timing is a
   measurement, not the justification for weakening invariants.
2. Implement and independently validate IndexedTable as a separate primitive,
   keeping ReferenceTable as the oracle. Share only existing layout, scalar and
   arena authorities and the one storage-owner allocator. Define finite grants,
   exact counters, intrusive undo and the live-only cursor contract before any
   runtime uses it. This is storage-level evidence only.
3. Introduce an explicit backend-neutral internal table/plan-storage facade if
   runtime exposure is authorized. Its owning table, cursor and journal wrappers
   dispatch to exactly one backend and preserve the existing default reference
   route. Runtime state must never contain a reference journal for an optimized
   table or reinterpret a handle as another backend's node pointer. The facade
   must not convert a live cursor into an owning snapshot or full scan.
4. Admit an optimized backend into typed initialization only after the physical
   artifact/profile/binding/report decision below is resolved and tested.
   Rebuild both runtime macro variants and all dependent reports coherently.
   Keep ReferencePlanStorage and public reference operations available for
   comparison. Do not silently switch existing owners or old serialized plans.
5. Run actual Support/Physical/Delta/Session/window and C01 capture consumers on
   the selected optimized route, preserving committed epoch, pending, rollback,
   cursor and pin boundaries. Existing reference-mode native tests remain the
   exact retained baseline; new optimized tests do not replace them.

No stage alone establishes the later stage's claims. Root must decide before
implementation whether S04 is to publish only the independently validated
storage primitive initially or to include the complete opt-in runtime migration
in the same card. This draft does not count an unused new table as an already
integrated production backend or silently narrow the intended scope.

## Required artifact decision before runtime exposure

An optimized owner cannot truthfully use physical-plan v1's fixed reference
backend claim. The recommended direction for actual runtime exposure is a new
explicit backend specification in typed lowering/initialization with a successor
physical artifact version. Reference defaults continue to emit/read the exact
v1 bytes. The successor must bind the backend algorithm/version, traversal
contract, hash/capacity policy and finite configuration in its complete physical
identity; it must replay through the actual producer, not import a JSON claim.
Exact source/query/height proof authority remains unchanged.

This is a proposed versioning direction, not an implemented v2 API. It requires
review of physical IO/schema, GuaranteeProfile, delta/runtime profiles and
observability. Existing closed report schemas must either gain a separately
versioned compatible format or explicitly reject the new artifact; they must
not silently describe hash execution as reference ordered storage.

C02/C05 must fail closed for an unsupported new backend until their complete
binding/capability decisions are reviewed. A new PhysicalOptions field must
not simply be omitted from their exact source/cache encoders. A subsequent
backend-aware format can preserve old reference bytes and bind the new backend
in a distinct version. The existing tuple/index-slot proxy describes logical
source-cardinality populations; it does not count hash arrays, overflow chains,
reserved shells or allocator bytes. Neither a proxy score nor observed C01
facts confer backend, proof or artifact-import authority.

## C01 capture and D05 complexity

C01's exact source cardinality is independent of traversal order. Full NDV,
degree histograms and heavy-key ordering must still use the existing exact
typed semantics and availability rules. A new traversal order can change how
much work fits a finite capture budget; do not claim byte-identical incomplete
captures or fabricate prefix distributions. Storage revision remains an
invalidation stamp; it is not a replacement for actual owner/committed-epoch
freshness or reset/configuration/segment boundaries.

If optimized storage adds directory-capacity or retained-node gauges, publish
them as actual as-of component observations. Rollback may retain admitted
capacity while restoring the same committed data sequence. Consequently the
existing owner-sequence freshness result is not a promise that allocation or
capacity history stayed identical. Take a new actual capture when those gauges
matter; do not turn storage revision into a replacement committed-data epoch
or silently promote a prior capacity sample to an S05 current-byte guarantee.

A backend-neutral capture path should visit borrowed row/key entries directly
under the same synchronous quiescent owner boundary, instead of adding an
unaccounted hash lookup after every cursor handle. Preserve the bounded charged
field/string/Decimal work and exact degree at each live key. Any hash probe
needed by capture must participate in the declared capture/operation work
model; one dictionary action is not automatically one byte comparison.

D05's bounded post-preparation indexed-action theorem is distinct from an
index's per-action cost. Its L/P/B maps and productive anchor queues are separate
ordered structures and do not become hashed merely because S02 tables change.
Existing preparation, per-result, termination, finalization and public-spool
cost distinctions remain. A hash-backed lookup has conditional distribution
assumptions and collision costs; rehash must never be hidden inside cursor
advance. There is no new constant wall-time, constant public startup, global
update-time or S05 memory claim.

The order-sensitive consumers need an explicit audit. SupportRuntime::snapshot
currently inherits table.snapshot order for its row/key vectors, whereas
canonical_state explicitly sorts record/count vectors and uses a set for
survivors. Preserve canonical comparisons through those existing operations;
do not call an insertion-ordered diagnostic vector byte-compatible with the
reference backend. The D05 proof in docs/ordered_delta.md allows arbitrary
complete-key order within one factor while requiring reverse factor order for
insertion and forward factor order for deletion. That supports a proposed
within-bucket ordering change, but does not authorize changing factor ranks,
pending cursor lifetime or any consumer's explicit order promise. Tests must
separately compare result sets, deterministic new-backend traversal and any
published serialized ordering.

## Dependency and ownership boundary

The new primitive belongs below runtime/report code and needs no SQL parser,
report serializer or third-party hash dependency. New operational counters
are owned by the storage state; optional snapshots distinguish committed
structure from attempts/aborts and diagnostic saturation. They must not create
a report dependency from storage or change C01 cells by accidental publication.

The proposal is an original implementation using current native semantics.
No DynaGox source was locally fetched or copied. Any later adaptation would
require its own exact provenance/ownership/arithmetic audit under the open A02
record. This design does not resolve project distribution licensing.
