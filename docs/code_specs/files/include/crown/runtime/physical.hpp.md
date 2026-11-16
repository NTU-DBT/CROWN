# `include/crown/runtime/physical.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/physical.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Compose one full physical source update across all its aliases into one atomic logical support epoch.

Snapshot SHA-256: `dcfc52f672fef053d0ff477eb3eeba840f25772dd95c5f11411280e54cca281c`. 215 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../../include/crown/runtime/physical.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 15–21](../../../../../../include/crown/runtime/physical.hpp#L15) | Type/record definition: struct PhysicalRuntimeOptions | source comment (unverified): // Abstract coordinator work, including all staged logical support work. · [reviewed contract](#b0002) |
| [B0003 · 22–31](../../../../../../include/crown/runtime/physical.hpp#L22) | Type/record definition: struct PhysicalMetrics |  · [reviewed contract](#b0003) |
| [B0004 · 32–38](../../../../../../include/crown/runtime/physical.hpp#L32) | Type/record definition: struct DerivationChange | source comment (unverified): // Final native scope, not an earlier SQL projection. · [reviewed contract](#b0004) |
| [B0005 · 39–44](../../../../../../include/crown/runtime/physical.hpp#L39) | Type/record definition: struct SourceRowChange | returns retained.get() · [reviewed contract](#b0005) |
| [B0006 · 45–53](../../../../../../include/crown/runtime/physical.hpp#L45) | Type/record definition: struct PhysicalPreview | source comment (unverified): // Compiled occurrence order. · [reviewed contract](#b0006) |
| [B0007 · 54–57](../../../../../../include/crown/runtime/physical.hpp#L54) | Type/record definition: struct PhysicalEpoch | source comment (unverified): // Local changes only; not full-query output deltas. · [reviewed contract](#b0007) |
| [B0008 · 58–61](../../../../../../include/crown/runtime/physical.hpp#L58) | Type/record definition: struct DerivationSnapshot |  · [reviewed contract](#b0008) |
| [B0009 · 62–67](../../../../../../include/crown/runtime/physical.hpp#L62) | Type/record definition: struct PhysicalSnapshot |  · [reviewed contract](#b0009) |
| [B0010 · 68–71](../../../../../../include/crown/runtime/physical.hpp#L68) | Type/record definition: struct PhysicalStorageStatistics |  · [reviewed contract](#b0010) |
| [B0011 · 72–107](../../../../../../include/crown/runtime/physical.hpp#L72) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Full-source-row coordinator over the selected native storage backend. · [reviewed contract](#b0011) |
| [B0012 · 108–143](../../../../../../include/crown/runtime/physical.hpp#L108) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Native allocations routed to this query account, including retained state · [reviewed contract](#b0012) |
| [B0013 · 144–179](../../../../../../include/crown/runtime/physical.hpp#L144) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // SQL plans map ordered/repeated/constant outputs and scalar EXISTS. Direct · [reviewed contract](#b0013) |
| [B0014 · 180–215](../../../../../../include/crown/runtime/physical.hpp#L180) | controls preprocessing; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0014) |

## B0001

[Lines 1–14](../../../../../../include/crown/runtime/physical.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:f134faeada0cf69ef57c615f1563569d82a3c69d6f1c0b4fd09f40a7c8e0b2f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare physical runtime dependencies, now including the owning SourceImage public type, and forward-declare private composition types. |
| inputs / outputs | Header guard, support/update/storage/recovery/source-image includes and unchanged runtime/WindowCheckpoint/ranking/reoptimization/DeltaRuntime declarations. |
| invariants | Imports define compile dependencies, not source-image capture or checkpoint authority. Forward declarations remain incomplete; runtime ownership starts with instances. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md), [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [docs/source_images.md](../../../../../source_images.md) |

## B0002

[Lines 15–21](../../../../../../include/crown/runtime/physical.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRuntimeOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure source-to-occurrence coordinator limits beside logical SupportOptions. |
| inputs / outputs | Support options, optional per-update work limit default1,000,000 and positive uint64 derivation cap. |
| invariants | Physical work includes explicitly charged nested support work across alias prefixes; constraint comparisons/scalar bytes/allocation/observer work have separate costs. Internal projection multiplicity is not SQL bag-result semantics. |
| ownership | Value-owned scalar options; existing query memory cap lives in SupportOptions. |
| failure | Carrier does not validate; constructor rejects zero derivation limit, methods enforce counters/quiescence. |
| cost | Fixed metadata copy; choosing limits does not preallocate rows or create grants. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 22–31](../../../../../../include/crown/runtime/physical.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalMetrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected attempted physical work categories for one input. |
| inputs / outputs | Work, source changes, alias visits/filters, derivation changes, native crossings and complete-constraint row/validation counts. |
| invariants | Metrics are abstract charges, not CPU/byte counts. Physical no-op can have zero metrics after nonzero row validation/probe/owner admission costs. |
| ownership | Inline numeric snapshot in preview/epoch. |
| failure | Counter growth checked through coordinator charge/metric; failed transactions can leave descriptive attempted values. |
| cost | Fixed fields/copy; actual operations can scan/copy/compare much more data than one counter increment. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 32–38](../../../../../../include/crown/runtime/physical.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DerivationChange {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one accepted occurrence projection multiplicity change. |
| inputs / outputs | Occurrence/node, owning final-native tuple, before/after positive/zero counts and Boolean native crossing flag. |
| invariants | Tuple uses complete native-node scope, not intermediate SQL projection; only 0↔1 stages logical support. Record is descriptive, not a checked source update. |
| ownership | Tuple owns funded copied native payload/shared layout metadata; survives later input/source erase. |
| failure | Construction/copy can allocate via tuple representation; valid move is nonthrowing for publication. |
| cost | Tuple copy/deep bytes/output-control storage plus scalar fields; retained output consumes original account. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 39–44](../../../../../../include/crown/runtime/physical.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceRowChange {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the complete changed physical source row through a native arena pin. |
| inputs / outputs | Typed TupleHandle plus move-only AccountedTupleArena::Pin; tuple() borrows retained native tuple. |
| invariants | Pin can keep an erased row/slot alive; original handle need not remain live in source membership. Borrowing from an rvalue wrapper is explicitly deleted. |
| ownership | Move-only pin retains arena/row/account independently of facade; tuple reference requires the pin remain owned. |
| failure | Moved/invalid pin access rejects through native arena contract; no implicit owning row export. |
| cost | Fixed handle/pin move; retained row/slot capacity and last-pin release have real account/cleanup costs. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [src/storage/accounted_arena.cpp](../../../../../../src/storage/accounted_arena.cpp) |

```text
  [[nodiscard]] const storage::AccountedTuple& tuple() const & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow changed source tuple from a live retained pin. |
| inputs / outputs | Return retained.get() on lvalue SourceRowChange. |
| invariants | Reference remains valid while pin retained; it does not assert row is still live source membership. |
| ownership | Borrow only; no tuple clone. |
| failure | Invalid/moved pin throws arena validation failure. |
| cost | Constant pin/state/slot access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/storage/accounted_arena.cpp](../../../../../../src/storage/accounted_arena.cpp) |

```text
  const storage::AccountedTuple& tuple() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent a source-row tuple borrow from a temporary pin wrapper. |
| inputs / outputs | Rvalue-qualified accessor is deleted. |
| invariants | Caller must retain lvalue SourceRowChange/pin before borrowing. |
| ownership | No runtime ownership transfer. |
| failure | Compile-time rejection of dangling-prone access. |
| cost | No runtime overhead. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 45–53](../../../../../../include/crown/runtime/physical.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalPreview {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own tentative physical input identity, metrics and routed derivation/source payload. |
| inputs / outputs | Sequence/table/op, physical_changed, metrics, optional pinned source and account-aware derivation vector in occurrence order. |
| invariants | Tentative until barrier; no-op omits source/alias outputs. Native zero crossing is separate from count-only/source-only change. |
| ownership | Move-only source pin and transferable OwnerAllocator output vector retain original account; references to live preview expire on token close. |
| failure | Preparation can allocate/throw before publication; move construction/assignment are statically required noexcept. |
| cost | Per-route output tuples/vector capacity and retained source slot, not a full database image. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 54–57](../../../../../../include/crown/runtime/physical.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish owning source/alias preview with local logical support changes at one committed sequence. |
| inputs / outputs | PhysicalPreview input plus SupportEpoch support. |
| invariants | Support journal is local change evidence, not full-query output delta or durable sink acknowledgement. |
| ownership | Move output/pin/journal owners into result; source/runtime can later change while held values remain funded. |
| failure | Valid barrier movement is noexcept as asserted in implementation; publication has no new allocation. |
| cost | Fixed ownership movement plus touched journal/inverse cleanup; later final-owned payload destruction is size dependent. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 58–61](../../../../../../include/crown/runtime/physical.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DerivationSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain one current native projected key and multiplicity in an owning diagnostic snapshot. |
| inputs / outputs | Tuple plus uint64 count. |
| invariants | One record per occurrence key; count is projection multiplicity over physical set rows, not result bag weight. |
| ownership | Tuple owns output payload/shared descriptor. |
| failure | Tuple construction/copy/allocation can fail during snapshot; carrier itself establishes no invariant proof. |
| cost | Stored row/deep payload plus count; snapshot creation scans all keys. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 62–67](../../../../../../include/crown/runtime/physical.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold a complete owning diagnostic physical/logical state export. |
| inputs / outputs | Sequence, ordinary physical Database, SupportSnapshot and per-occurrence derivation vectors. |
| invariants | Pending token factory can expose a partially drained alias prefix: source membership is already staged while remaining aliases/support can still be old. Public runtime snapshot requires committed readability. Neither is an import/authority constructor. |
| ownership | Owns ordinary row/vector/set payloads plus funded tuple outputs; explicit export boundary distinct from internal native snapshot. |
| failure | Deep export/allocation failure publishes no snapshot and leaves runtime unchanged. |
| cost | Whole source/support/count copy, sorting/ordered comparisons and overlap memory; not a cheap view. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 68–71](../../../../../../include/crown/runtime/physical.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalStorageStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate source/support arena populations and derivation-key count. |
| inputs / outputs | Two ArenaStatistics plus size_t derivation_keys. |
| invariants | Live/retained/free/slot counts are not bytes/RSS or complete invariant verification. |
| ownership | Fixed value snapshot. |
| failure | Producer checks aggregate overflow; carrier accepts caller values without validation. |
| cost | Fixed record; producer scans table/relation/occurrence metadata. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0011

[Lines 72–107](../../../../../../include/crown/runtime/physical.hpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PhysicalRuntime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Coordinate native full-source set input, alias multiplicity and logical support behind one commit barrier. |
| inputs / outputs | Construct empty or initialize complete database; prepare/apply, committed cursors/views, diagnostics, rebuild/recovery and bounded captures. Explicit source_image() additionally returns a deep original-account full-source image; pending capture requires complete alias routing and retains the same indexed grant. |
| invariants | Exclusive single-owner mutation protocol. Full source rows determine set identity; each occurrence projects independently; only count zero crossings reach support. Physical output is local support/alias change, not the Delta owner full-query stream. Native source images are owning data with row/work bounds, not checkpoint or original-query proof authority. |
| ownership | Facade shares native Impl; pending tokens retain owner/grant across moves/destruction. Actual state/new native allocations use query account; explicit exports have documented ordinary payload. |
| failure | Precondition/resource/storage failures preserve committed state through private journals/RAII; unexpected invalid native provenance can terminate at no-allocation restoration boundaries. |
| cost | State/data-dependent update, scan, output and cleanup costs. Work/slot counters and selected backend assumptions do not by themselves establish hard CPU/byte performance bounds. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/source_images.md](../../../../../source_images.md) |

```text
  class PendingUpdate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the private source/count/logical epoch until commit or whole-update rollback. |
| inputs / outputs | Move-only token exposes tentative previews/views/snapshot, explicit commit/rollback and private alias-stage protocol. Explicit source_image() additionally returns a deep original-account full-source image; pending capture requires complete alias routing and retains the same indexed grant. |
| invariants | No implicit commit. All alias routes must drain and throwing output preparation finish before valid nonallocating barrier. View leases seal prefix until retired. Native source images are owning data with row/work bounds, not checkpoint or original-query proof authority. |
| ownership | Unique Data holds shared runtime owner, source pin/journals, count inverse nodes, output and original operation lease. |
| failure | Destructor/move replacement rolls back unfinished work; active stage failure explicitly closes/restores surviving token. |
| cost | Retains touched state; close/replace/destruction can perform substantial undo/map/ledger/payload work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/source_images.md](../../../../../source_images.md) |

```text
    PendingUpdate(const PendingUpdate&) = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forbid duplicating private transaction ownership. |
| inputs / outputs | Copy constructor/assignment deleted; move lifecycle declared below. |
| invariants | Only one facade owns Data; retaining independent epoch views follows separate group protocol. |
| ownership | No copying or hidden journal duplication. |
| failure | Compile-time rejection. |
| cost | No runtime overhead. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
    PendingUpdate(PendingUpdate&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move pending ownership without moving its native source/count/journal payload. |
| inputs / outputs | Default unique owner move empties source facade. |
| invariants | Borrowed caller update is no longer needed; Data retains imported source pin and owner. |
| ownership | Exclusive Data transfer. |
| failure | Noexcept. |
| cost | Declaration selects the documented body behavior: Constant move construction. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    PendingUpdate& operator=(PendingUpdate&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a pending token while restoring any old destination transaction first. |
| inputs / outputs | Self-check then unique owner move assignment. |
| invariants | Old destination Data destructor rolls back if still active; source facade becomes empty. |
| ownership | Transfers exclusive token/lease; old payload may release final owners. |
| failure | Noexcept with funded destructor/rollback preconditions. |
| cost | Declaration selects the documented body behavior: Fixed handle transfer plus potentially large old rollback/inverse/ledger cleanup. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    ~PendingUpdate();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close pending ownership and automatically rollback an unfinished update. |
| inputs / outputs | Default AccountedUnique destruction invokes Data::~Data. |
| invariants | Committed/rolled-back Data rollback is inert; no implicit commit. |
| ownership | Releases Data/lease/owner and retained capacities. |
| failure | Noexcept native ownership destruction. |
| cost | Declaration selects the documented body behavior: Size-dependent rollback and payload release; no new scratch allocation. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] bool active() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether this facade retains an unclosed logical/physical token. |
| inputs / outputs | Require nonnull Data/owner/logical and logical.active(). |
| invariants | False for moved-from/closed token; does not claim routes complete. |
| ownership | Reads owned pointer/flags only. |
| failure | Noexcept; no diagnostic allocation. |
| cost | Declaration selects the documented body behavior: Constant checks. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] const PhysicalPreview& preview() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the owner-only tentative physical preview. |
| inputs / outputs | Check facade/Data active, return output. |
| invariants | Not externally published epoch; borrow expires on commit/rollback/replacement. |
| ownership | Data owns tuples/pins/vector; returned reference owns nothing. |
| failure | invalid_epoch on moved/closed token. |
| cost | Declaration selects the documented body behavior: Constant checks/reference. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] const SupportEpoch& support() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow tentative local logical changes for this physical input. |
| inputs / outputs | Check active token, return logical preview. |
| invariants | Local support journal changes are not full-query output deltas or committed state. |
| ownership | Borrow expires when pending logical owner closes/changes. |
| failure | invalid_epoch or logical preview contract errors propagate. |
| cost | Declaration selects the documented body behavior: Constant checks/reference. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] PhysicalSnapshot snapshot() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a complete owner-only tentative diagnostic snapshot. |
| inputs / outputs | Rebind retained storage lease, obtain logical snapshot then combine source/count snapshot. |
| invariants | May capture a partially drained alias prefix: source membership is already staged while other alias counts/support can still be old. It is an owner-only diagnostic, not a committed full-query after-state. Snapshot failure leaves token active for caller decision. |
| ownership | Returned diagnostic owns ordinary data and funded tuple payload; retained lease is reused without refill. |
| failure | Native fixed failures present as Error; allocation/snapshot failures propagate without an explicit abort catch here. |
| cost | Declaration selects the documented body behavior: Complete source/support/count export and deep allocation costs, not constant preview access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] SupportRuntime::EpochView view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owner-only before/after logical epoch view of the current private prefix. |
| inputs / outputs | Check active facade, delegate logical.view(side,options). |
| invariants | View/group leases seal pending prefix; caller must retire them before further staging/commit according to support protocol. |
| ownership | Returned owning view retains logical group/native rows; facade itself keeps full physical Data. |
| failure | Invalid token/options/resource/view construction failures propagate; this accessor does not auto-abort. |
| cost | Declaration selects the documented body behavior: Delegated view preparation/retained journal/index work and allocation; no complete database snapshot by this wrapper. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] PhysicalEpoch commit();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish fully prepared source/count/logical state as one physical epoch. |
| inputs / outputs | Open token with all routes drained produces owning PhysicalEpoch and advances the committed sequence. |
| invariants | Logical/source commits, inverse cleanup, output moves and ticket completion allocate nothing after the barrier begins. Partial route preparation is rejected before publication. |
| ownership | Moves owning output/journal handles into the result and clears pending ownership. |
| failure | Closed/not-drained tokens reject before commit; publication relies on funded nonthrowing native operations. |
| cost | Declaration selects the documented body behavior: O(touched journals/inverse destruction/output owner moves); no global validation or output enumeration at commit. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/indexed_storage.md](../../../../../indexed_storage.md) |

```text
    void rollback() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly abort the full pending physical update if owned. |
| inputs / outputs | Delegate Data rollback when data_ exists; moved-from no-op. |
| invariants | Restores every staged alias/source/support edit; idempotent after owner reset. |
| ownership | Keeps facade shell but releases private row/journal/output ownership. |
| failure | Noexcept; no new recovery allocation. |
| cost | Declaration selects the documented body behavior: All inverse/native journal cleanup and possible std::map allocation-ledger classification. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
    [[nodiscard]] bool stage_next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one remaining alias prefix through a retained public token. |
| inputs / outputs | Open PendingUpdate and optional observer/options return true after one route, or false once routes are complete. |
| invariants | The token survives this method, so active-route failure needs an explicit rollback catch. Native fixed failures are presented as public Error only after rollback. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Invalid/closed token rejects access; any active route failure closes and restores the complete physical update. |
| cost | Declaration selects the documented body behavior: One route plus actual observer/support work under original grant; no per-call budget refill or source-row export. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/indexed_storage.md](../../../../../indexed_storage.md) |

```text
@source-span:L72-L107:sha256:55a7384cd073bd0090ffafa85de32935115eab2a9f84bec2f100b26b1dda809a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document pending full after-state capture within the existing single-token publication interface. |
| inputs / outputs | Combined PhysicalRuntime/PendingUpdate declarations from class introduction through rollback; additive source_image is L93-L96. |
| invariants | Inherited move-only token, owner-only preview/support/snapshot and output-before-commit contract remain. New capture requires drained alias routes, resumes retained indexed lease without replenishment and preserves active token on capture refusal; abandoning token still rolls it back. This is serial owner access, not concurrent public reading of unpublished data. |
| ownership | Pending token owns source/logical undo and lease; returned SourceImage deeply owns original-account data beyond token close. Borrowed preview/support expire on close; output images do not. |
| failure | Invalid/closed/moved tokens and undrained routes reject. Source row/work/native resource failure propagates while leaving token active. Valid commit/rollback retain existing nonallocation boundary. |
| cost | Existing staging/journal/publication costs plus explicit full table/row/payload capture and its own selected balance/native lease costs; no zero-copy or constant-time claim. |
| Design | [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp), [docs/source_images.md](../../../../../source_images.md) |

## B0012

[Lines 108–143](../../../../../../include/crown/runtime/physical.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  PhysicalRuntime(const PhysicalRuntime&) = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forbid copying an active runtime facade and its mutable owner contract. |
| inputs / outputs | Copy constructor/assignment deleted; move lifecycle remains supported. |
| invariants | Separate owners must be initialized/rebuilt explicitly under proper account/context. |
| ownership | No implicit state clone or account grant. |
| failure | Compile-time rejection. |
| cost | No runtime overhead. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
    explicit PendingUpdate(resource::AccountedUnique<Data> data) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a completely prepared private physical token. |
| inputs / outputs | Move AccountedUnique&lt;Data&gt; into facade. |
| invariants | Only begin_staged creates valid prepared Data; constructor does not replay admission. |
| ownership | Unique owner/retained grant transfer. |
| failure | Noexcept; no allocation. |
| cost | Declaration selects the documented body behavior: Constant owner move. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
  explicit PhysicalRuntime(PhysicalPlan plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty physical owner from a public compiler artifact. |
| inputs / outputs | Create matching storage context/account with configured memory limit, then delegate PlanSource constructor. |
| invariants | Source artifact is input only; owned native program/state is admitted before publication. Empty source state differs from initialize(database). |
| ownership | New query account funds native metadata/state; caller plan handle is not retained as an unaccounted graph. |
| failure | Context/compiler/storage/option/allocation errors propagate from construction; no runtime escapes. |
| cost | Declaration selects the documented body behavior: Complete native plan admission plus empty support/source/count structures, not constant handle wrapping. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  explicit PhysicalRuntime(CompiledProgram plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a compiler/cache program into a fresh receiving runtime account and empty physical owner. |
| inputs / outputs | Create new_storage_context, open one storage operation, deep freeze native source into receiving account, validate context, construct Impl. |
| invariants | Public new query does not adopt source account as a fresh runtime allowance; internal rebuilds use separate existing-account path. |
| ownership | New metadata/state under receiving account; supplied immutable native source remains external input only. |
| failure | Native Index/Table failures are formatted after constructor unwind; memory/compiler errors propagate. |
| cost | Declaration selects the documented body behavior: Full native metadata/binding clone plus empty state construction and optional observation initialization. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] static PhysicalRuntime initialize(PhysicalPlan plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a ready physical owner from a complete caller database and compiler plan. |
| inputs / outputs | Delegate initialize_at at sequence0 with no public input epoch. |
| invariants | Complete final-state constraint validation precedes both direct/insertion-replay build paths, permitting valid cyclic FKs. |
| ownership | Caller Database borrowed for build; result owns funded native state. |
| failure | Build/schema/constraint/storage/resource/allocation failures return no partial owner. |
| cost | Declaration selects the documented body behavior: Whole database validation/import/adaptation/count/support build; cumulative BuildOptions limit separate from per-update limits. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] static PhysicalRuntime initialize(CompiledProgram plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build from complete caller database after admitting supplied native source into a fresh query account. |
| inputs / outputs | New context/operation, CompiledProgram::freeze then initialize_at at sequence0. |
| invariants | Uses complete final snapshot, no public insertion-prefix constraint artifacts or fabricated external updates. |
| ownership | New native source/state account; caller source/database remain unchanged. |
| failure | Native failures format after unwind; all build/admission/allocation errors propagate before publication. |
| cost | Declaration selects the documented body behavior: Full source freeze plus complete database build; does not merely share compiler/cache metadata. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] PhysicalRuntime rebuilt(BuildOptions build={}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a separate rebuilt owner from a quiescent committed snapshot. |
| inputs / outputs | Require writable source, create compatible existing-account context and delegate private rebuild. |
| invariants | Original owner remains unchanged and committed sequence/options preserved; old/new state coexist under original query cap. |
| ownership | Target and operational source snapshots share original account, not a fresh grant. |
| failure | Busy/context/build/resource/allocation failures leave original usable. |
| cost | Declaration selects the documented body behavior: Whole source snapshot/sort/import and support reconstruction; peak overlap is real funded memory. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  ~PhysicalRuntime();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release facade ownership of physical source/count/kernel state. |
| inputs / outputs | Default shared Impl owner destruction. |
| invariants | Pending tokens can keep Impl alive; logical cursors/outputs can retain their separate kernel/row/account owners. |
| ownership | Final Impl release destroys large source/count/native state; borrowed metadata needs a surviving owner. |
| failure | Noexcept member destruction under native contracts; no implicit commit. |
| cost | Declaration selects the documented body behavior: Fixed shared-owner decrement or complete size-dependent final-state teardown. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  PhysicalRuntime(PhysicalRuntime&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move facade ownership without relocating runtime state. |
| inputs / outputs | Default shared-pointer move empties source facade. |
| invariants | Pending Data and reader/output owners remain valid independently; node/row addresses do not move. |
| ownership | Transfers one Impl shared owner. |
| failure | Noexcept, nonallocating. |
| cost | Declaration selects the documented body behavior: Constant handle movement. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  PhysicalRuntime& operator=(PhysicalRuntime&& other) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace runtime facade ownership while preserving separately retained pending/readers. |
| inputs / outputs | Self-check then move shared Impl; old destination owner released. |
| invariants | Moved-from source rejects impl access; does not force commit/rollback of a token held separately. |
| ownership | Transfers facade owner; old Impl may remain through pending token or lose final owner. |
| failure | Noexcept shared-owner transfer. |
| cost | Declaration selects the documented body behavior: Constant transfer plus potentially full old physical state destruction. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] const CompiledProgram& plan() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable admitted native program. |
| inputs / outputs | Return kernel.plan(). |
| invariants | Program metadata can be observed while physical state is pending; not a DTO export. |
| ownership | Borrow into retained kernel/program. |
| failure | Moved-from facade/kernel access can reject. |
| cost | Declaration selects the documented body behavior: Constant handle/reference access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy actual query-account allocation statistics. |
| inputs / outputs | Return kernel account statistics. |
| invariants | Account totals include held generations/outputs/scratch, distinct from RSS or logical row/slot counts; no quiescent row scan required. |
| ownership | Fixed numeric snapshot. |
| failure | Invalid facade/account contract can reject. |
| cost | Declaration selects the documented body behavior: Constant fixed-category counter copy, no ledger scan. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] ObservationSnapshot observations() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current observation summary. |
| inputs / outputs | Kernel observations with physical initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Fixed summary value; no new observer owner. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Declaration selects the documented body behavior: Fixed metric-registry snapshot copy. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp) |

```text
  void configure_workload_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace workload collector configuration at a quiescent physical boundary. |
| inputs / outputs | Require writable, configure collector from compiled physical program/options/current sequence. |
| invariants | Explicit caller action changes collection interval/configuration; it is not performed implicitly by capture/ranking. |
| ownership | Collector owns native configuration/routes/slabs under existing account. |
| failure | Busy/invalid options/budget/memory/configuration failures propagate per collector contract. |
| cost | Declaration selects the documented body behavior: Potential descriptor/route/configured-slab construction and allocation, not a constant assignment. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
  void reset_workload_statistics();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly reset workload interval at the committed physical sequence. |
| inputs / outputs | Require writable then collector.reset(sequence). |
| invariants | Reset is caller-authorized state change; reset saturation/availability remain explicit collector metadata. |
| ownership | Reuses existing collector ownership/configured storage. |
| failure | Busy/moved-from/collector contract failures propagate. |
| cost | Declaration selects the documented body behavior: Collector reset work depends on configured statistics slabs; no row database scan. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
  [[nodiscard]] workload::Snapshot workload_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture as-of workload evidence with committed stamp and pending flag. |
| inputs / outputs | Collector.snapshot(compiled program,owner,sequence,updating). |
| invariants | Allowed during private update but marked pending; copied statistics do not authorize reading private source state or assert future freshness. |
| ownership | Retains native plan and funded copied configured descriptor/counter slabs; source epoch not advanced. |
| failure | Snapshot allocation/collector/moved-from failures propagate. |
| cost | Declaration selects the documented body behavior: Copies configured workload arrays/slabs even if source table is small; collector bounds and account cap are separate from later rank budget. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last recorded cursor diagnostic. |
| inputs / outputs | Delegate kernel.last_cursor_observation(). |
| invariants | No cursor is executed/restarted; availability remains as recorded. |
| ownership | Value/optional diagnostic copy. |
| failure | Moved-from facade/kernel rejects. |
| cost | Declaration selects the documented body behavior: Fixed diagnostic copy. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export ordinary committed population gauges. |
| inputs / outputs | Require readable; Start kernel committed gauges, overwrite physical base total and append table counts. |
| invariants | Base total saturates at UINT64_MAX with explicit saturated flag; source/support node gauges remain separate. These are current committed counts, not CPU/bytes. |
| ownership | Owns ordinary vectors copied/allocated for caller; no row payloads. |
| failure | Busy/moved-from/allocation failures propagate; no committed state mutation. |
| cost | Declaration selects the documented body behavior: Linear source-table/support-node metadata scans and gauge vector allocations, not all source row scans. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] CapturedStateGauges capture_state_gauges() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture funded committed population gauges. |
| inputs / outputs | Require readable; Start account-backed kernel captured gauges, overwrite physical base total and append table counts. |
| invariants | Base total saturates at UINT64_MAX with explicit saturated flag; source/support node gauges remain separate. These are current committed counts, not CPU/bytes. |
| ownership | Owns account-backed retained vectors/metadata; no row payloads. |
| failure | Busy/moved-from/allocation failures propagate; no committed state mutation. |
| cost | Declaration selects the documented body behavior: Linear source-table/support-node metadata scans and gauge vector allocations, not all source row scans. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] statistics::OwnerCapture capture_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture selected committed physical/support facts from an owning request. |
| inputs / outputs | Delegate request view to capture_statistics_view. |
| invariants | No collector reconfiguration/reset or hidden ranking fallback; pending/partial availability is explicit. |
| ownership | Request borrowed synchronously; returned capture owns funded selected descriptors/facts. |
| failure | Delegated request/schema/storage/allocation failures propagate. |
| cost | Declaration selects the documented body behavior: Fixed view conversion plus complete requested capture cost. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp) |

```text
  [[nodiscard]] statistics::OwnerCapture capture_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build bounded typed source/occurrence/support fact capture at one physical owner stamp. |
| inputs / outputs | Bind operation, initialize OwnerBuilder with pending flag, dispatch source table selections, full-native derivation distributions or logical selections, then finish. |
| invariants | Pending private state returns marked unavailable facts through inactive builder, not a source read. Occurrence distributions require complete native keys, never arbitrary field projections. Exhausted detail remains explicitly partial. |
| ownership | Request views borrowed during call; captured selections/layouts/native distribution data funded by existing program account. |
| failure | Invalid request/occurrence/fields reject. Statistics Exhausted marks component budget_exhausted; native fixed failures format; allocation/other errors propagate. |
| cost | Declaration selects the documented body behavior: Requested component traversal and weighted derivation-map scan, row/key/string comparisons and native capture allocations. Builder may stop early with partial metadata; not a full database snapshot. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/owner_statistics_detail.hpp](../../../../../../src/runtime/owner_statistics_detail.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
  [[nodiscard]] statistics::Freshness statistics_freshness(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare captured owner/layer/sequence stamp to current physical boundary. |
| inputs / outputs | Call compare_freshness(old,{owner,sequence,physical},max_event_lag). |
| invariants | Classifies foreign/layer/future/current/within-lag/stale; does not validate capture completeness, workload interval/mode or private-state availability. |
| ownership | Borrows capture and copies fixed stamps only. |
| failure | Moved-from runtime or capture handle contract errors can reject. |
| cost | Declaration selects the documented body behavior: Constant scalar stamp arithmetic; no row scan or allocation. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp) |

```text
  [[nodiscard]] ObservationTrace observation_trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export ordinary observation trace. |
| inputs / outputs | Kernel trace with snapshot initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Ordinary output trace copies records. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Declaration selects the documented body behavior: Trace-record copy/allocation proportional to retained trace length. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp) |

```text
  [[nodiscard]] CapturedObservationTrace capture_observation_trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture funded observation trace. |
| inputs / outputs | Kernel captured trace with physical initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Account-backed owning output record array. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Declaration selects the documented body behavior: Trace-record copy/accounted allocation proportional to captured length. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp) |

```text
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture matching source/support facts and workload interval from one owning request. |
| inputs / outputs | Delegate request view, capture state then workload, verify owner/sequence/physical hash/pending agreement and retain pair. |
| invariants | Synchronous exclusive-owner boundary; pending/private availability must agree. Does not reset/reconfigure collector or declare future freshness/structural authority. |
| ownership | Returned pair retains native plan and funded state/workload snapshots/control; request views do not escape. |
| failure | Request/capture/storage/allocation failures propagate; mismatch rejects before pair publication. |
| cost | Selected state capture plus configured workload slab copy and pair-control allocation, not constant handle-only packaging. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture matching state/workload pair from borrowed selections. |
| inputs / outputs | Capture_statistics_view then workload_statistics; construct bound CombinedCapture. |
| invariants | Synchronous exclusive-owner boundary; pending/private availability must agree. Does not reset/reconfigure collector or declare future freshness/structural authority. |
| ownership | Returned pair retains native plan and funded state/workload snapshots/control; request views do not escape. |
| failure | Request/capture/storage/allocation failures propagate; mismatch rejects before pair publication. |
| cost | Selected state capture plus configured workload slab copy and pair-control allocation, not constant handle-only packaging. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

## B0013

[Lines 144–179](../../../../../../include/crown/runtime/physical.hpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const PhysicalRuntimeOptions& options() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable configured runtime options. |
| inputs / outputs | Return Impl options. |
| invariants | No live collector reconfiguration or validation occurs. |
| ownership | Borrow requires surviving Impl. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant reference access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] SupportOwnerId owner() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read logical owner identity for physical handles/reports. |
| inputs / outputs | Return kernel.owner(). |
| invariants | Owner ID is not freshness or query equivalence proof. |
| ownership | Scalar value copy. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] std::uint64_t sequence() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last committed physical sequence. |
| inputs / outputs | Return Impl sequence. |
| invariants | Tentative update does not advance this value; no implicit read of pending preview. |
| ownership | Scalar copy. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] bool ready() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a new update may proceed without pending/reader conflict. |
| inputs / outputs | Return !updating && kernel.ready(). |
| invariants | False while private physical token or kernel reader/view leases pin epoch; not a lock or concurrency primitive. |
| ownership | Reads scalar/reader metadata only. |
| failure | Moved-from facade rejects; otherwise bool. |
| cost | Declaration selects the documented body behavior: Constant checks. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] bool has_answer() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed core CQ truth. |
| inputs / outputs | Require physical readable, delegate kernel.has_answer(). |
| invariants | SQL EXISTS still returns a Boolean row even when core truth false; this bool is core truth only. |
| ownership | Scalar result. |
| failure | Busy pending update/moved-from rejects. |
| cost | Declaration selects the documented body behavior: Constant route/root survivor-count access under valid program. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] const storage::TupleLayout& source_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original source-table typed descriptor. |
| inputs / outputs | Range-check source then return shared native descriptor from source_layouts. |
| invariants | Metadata observation does not require readable(); native token is shared with actual source layout. |
| ownership | Borrow into Impl vector; copying descriptor retains metadata independently. |
| failure | Invalid table/moved-from rejects. |
| cost | Declaration selects the documented body behavior: Constant range/descriptor access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] const storage::TupleLayout& result_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow core or SQL mapped result descriptor. |
| inputs / outputs | Delegate kernel.result_layout(view). |
| invariants | Selects valid core/sql domain; metadata can be read without snapshotting result rows. |
| ownership | Borrow into retained kernel metadata. |
| failure | Moved-from or invalid ResultView rejects. |
| cost | Declaration selects the documented body behavior: Constant view/descriptor access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] PendingUpdate prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and fully route one source input without publishing it. |
| inputs / outputs | Call prepare_observed with empty observer/options. |
| invariants | Caller receives active token; source/count/support tentative state remains private until commit. All alias work is drained before return. |
| ownership | Token owns imported row/pin/journals and original account/lease; input borrowed during admission only. |
| failure | Admission or route failure restores complete previous state and returns no active token. |
| cost | Declaration selects the documented body behavior: Complete input validation/import/probe, optional database constraints and all alias/support work; even physical no-op pays admission costs. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
  [[nodiscard]] PhysicalEpoch apply(const PhysicalSetUpdate&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare, route and commit one complete physical set input synchronously. |
| inputs / outputs | prepare(update).commit() returns owning epoch. |
| invariants | No partial alias prefix is published; physical no-op still advances contiguous committed sequence. |
| ownership | Epoch retains source pin/derivation tuples/support journal under original account. |
| failure | Throwing preparation aborts; valid final commit uses prepared nonallocating barrier. |
| cost | Declaration selects the documented body behavior: All prepare/route work plus touched-journal commit cleanup; not full-query delta enumeration. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
  [[nodiscard]] PhysicalEpoch apply_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a borrowed native/ordinary row view without a retained ordinary Row mirror. |
| inputs / outputs | begin_staged(view), drain stage_next with no observer, commit. |
| invariants | Caller row needed only during admission; all later routes use pinned imported source. |
| ownership | Returned epoch owns funded outputs; token/local view does not retain caller storage. |
| failure | Any preparation/stage failure restores whole update before return/formatting. |
| cost | Declaration selects the documented body behavior: Input validation/copy/probe plus full routing/support/constraint costs and commit cleanup. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
  [[nodiscard]] SupportRuntime::ResultCursor results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed SQL-mapped result cursor. |
| inputs / outputs | Require physical readable then delegate kernel.results(options,ResultView::sql). |
| invariants | SQL output order/repetition/constants/EXISTS mapping applies; direct CQ keeps core order. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Declaration selects the documented body behavior: Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] SupportRuntime::ResultCursor core_results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed core-head result cursor. |
| inputs / outputs | Require physical readable then delegate kernel.results(options,ResultView::core). |
| invariants | No SQL final output mapping; ordered/repeated core head preserved. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Declaration selects the documented body behavior: Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] SupportRuntime::EpochView current_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin a committed logical epoch view. |
| inputs / outputs | Require physical readable then delegate kernel.current_view(options). |
| invariants | View leases block future writes; this factory cannot observe a pending physical update. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Declaration selects the documented body behavior: Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] SupportRuntime::ResultCursor completions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed completion cursor under fixed assignments and visible fragment. |
| inputs / outputs | Require physical readable then delegate kernel.completions(fixed,fragment,options). |
| invariants | Uses documented core fragment semantics, not final SQL mapping or a fresh snapshot copy. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Declaration selects the documented body behavior: Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] SupportRuntime::ResultCursor witnesses(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed witness cursor for fixed assignments/factor fragment. |
| inputs / outputs | Require physical readable then delegate kernel.witnesses(fixed,move(fragment),options). |
| invariants | Witness semantics remain distinct from duplicate-free output enumeration. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Declaration selects the documented body behavior: Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] PhysicalSnapshot snapshot() const;  // Owning diagnostic copy.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a complete committed diagnostic snapshot. |
| inputs / outputs | Bind storage operation, require readable, obtain kernel snapshot then combine source/counts. |
| invariants | Owning diagnostic copy, not a cheap view or independent proof. Cannot read private physical state through public facade. |
| ownership | Ordinary database/support export plus funded derivation tuples; native snapshot temporaries consume original account. |
| failure | Native storage failures format after unwind; busy/export/allocation failures propagate without committed mutation. |
| cost | Declaration selects the documented body behavior: Full source/support/count traversal, deep copies and ordered-set work; no constant-time or strict export-temporary byte claim. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] std::uint64_t derivation_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read positive native projection multiplicity for one occurrence/key. |
| inputs / outputs | Require readable, validate native key against compiled node descriptor, heterogeneous std::map lookup; absent returns0. |
| invariants | Value domain is final native-node scope, not physical full row or earlier SQL projection; per-occurrence identity matters. |
| ownership | Borrows ordinary probe synchronously; scalar result only. |
| failure | Busy/invalid occurrence/arity/type/domain or comparison/presentation failures propagate. |
| cost | Declaration selects the documented body behavior: Key validation plus O(log distinct projected keys) variable-width comparisons; successful lookup creates no owned probe. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] std::optional<TupleHandle> find_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find full physical source membership by complete typed row. |
| inputs / outputs | Bind storage operation, require readable/range, validate public descriptor, construct native probe tuple and call source.find. |
| invariants | Handle identity includes source owner/relation/generation; ignored columns still distinguish source rows. |
| ownership | Input borrowed for native copy; returned handle is scalar identity and does not pin row. |
| failure | Busy/schema/native work/memory failures propagate; typed native Index/Table failures present after probe cleanup. |
| cost | Declaration selects the documented body behavior: Public validation plus native tuple validation/copy and backend lookup; temporary key allocation/deep bytes are real costs. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp) |

```text
  [[nodiscard]] std::optional<storage::AccountedTuple> get_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone a live source tuple by its typed generation handle. |
| inputs / outputs | Require readable/table range, source.get(handle); absent returns empty, present clones row under output attribution. |
| invariants | Does not expose a raw table borrow. Foreign/stale handle behavior is delegated to native source validation. |
| ownership | Result uniquely owns a deep copied row and shared layout/account, independent of later source erase/facade destruction. |
| failure | Busy/handle/storage work/validation/allocation failures propagate; public translation after cleanup. |
| cost | Declaration selects the documented body behavior: Backend handle lookup plus complete deep tuple copy/allocation for a present row, not constant owning output. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp) |

```text
  [[nodiscard]] std::optional<SupportHandle> find_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a logical support-role row by typed values. |
| inputs / outputs | Require physical readable then delegate kernel.find(node,role,values). |
| invariants | Returned support handle is owner/node/role/generation qualified and does not pin a tuple. |
| ownership | Probe borrowed; scalar optional handle result. |
| failure | Busy or delegated node/role/layout/storage/resource failures propagate. |
| cost | Declaration selects the documented body behavior: Delegated row validation/native probe construction and backend lookup; wrapper adds constant checks. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] std::optional<storage::Tuple> get_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return immutable owning output for a live logical support handle. |
| inputs / outputs | Require physical readable then delegate kernel.get(handle). |
| invariants | No raw support table/tuple reference is exposed; wrong owner and stale handle are distinguished by kernel/storage. |
| ownership | Present result deep-copies native row into funded tuple/public payload owner; descriptor shares native metadata. |
| failure | Busy/foreign/invalid/resource/allocation failures propagate from kernel. |
| cost | Declaration selects the documented body behavior: Handle lookup plus native deep clone/output control allocation when present. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp) |

```text
  [[nodiscard]] PhysicalStorageStatistics storage_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate committed source/support arena and derivation-key counts. |
| inputs / outputs | Require readable, read kernel storage stats, checked-sum each source arena and count-map size. |
| invariants | Counts reflect allocated/live/retained/free slots and key populations, not allocator byte totals or a captured consistent future epoch. |
| ownership | Fixed aggregate returned by value; no row payload copy. |
| failure | Busy/native stats/checked size overflow failures propagate. |
| cost | Declaration selects the documented body behavior: Linear in source tables, support relation descriptors and occurrence maps; does not traverse all row keys to count them. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] const BuildMetrics& initialization_metrics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cumulative completed construction metrics. |
| inputs / outputs | Return build_metrics. |
| invariants | Abstract build debits separate from per-event metrics, current memory and CPU time. |
| ownership | Borrow into Impl; survives only while owned. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant reference access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] InitializationContext initialization_context() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read how this owner was constructed/rebuilt. |
| inputs / outputs | Return copied initialization route/build options. |
| invariants | Historical setup metadata, not current row state or proof. |
| ownership | Fixed-size value copy. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant field copy. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] CanonicalPhysicalState canonical_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export canonical committed source/derivation/support values for diagnostics/comparison. |
| inputs / outputs | Bind operation, require readable, copy kernel canonical state, sequence, ordinary source database and per-occurrence sorted key/count vectors. |
| invariants | Exact value snapshot is explicit export, not import or runtime-state mutation authority. |
| ownership | Owns ordinary deep row/string/vector/set copies; native source snapshot temporaries stay account funded. |
| failure | Storage fixed failures format after cleanup; export/allocation/busy failures leave state unchanged. |
| cost | Declaration selects the documented body behavior: Whole physical/logical state copies and sorted-set traversal; byte widths/ordered insert comparisons and peak temporaries are additional. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] InvariantReport inspect_invariants(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently recompute committed physical-source/derivation relations into a bounded diagnostic report. |
| inputs / outputs | Inspect support first; charge/check source storage and constraints, build native source snapshots, re-adapt each occurrence into expected counts, compare actual maps and native record sets. |
| invariants | Incomplete support/charge/issue-budget stops retain complete=false. Reports distinguish checked failures from success; they do not establish fresh planner proof or arbitrary memory-corruption safety. |
| ownership | Accounted report/key/expected-map/native snapshot storage uses original report/query account; no ordinary database mirror. |
| failure | InspectionStop yields incomplete report. Recognized source invariant errors become issues; other native failures are translated, allocation/contracts can propagate. Prior committed state unchanged. |
| cost | Declaration selects the documented body behavior: May resnapshot/adapt the same base per alias, sort all sources, perform complete constraints and lexical map/set comparisons. Coarse charges omit comparison/string/capacity overhead; scratch can be large. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp) |

```text
  void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail-fast independently verify complete committed source/count/native consistency. |
| inputs / outputs | Require readable/equal sequences, check logical/source storage, full source constraints, re-adapt every occurrence into expected counts, compare map/native-key populations and values. |
| invariants | Does not rely on stored derivation counts as expected truth; trusted immutable compiled adapters still define semantics. No bounded InvariantReport partial-success wrapper. |
| ownership | Native snapshots/expected AVL maps/record sets allocated in original account; source remains unchanged. |
| failure | Detected mismatch throws runtime_contract; native Index/Table failures format after unwind; resource/allocation failures propagate rather than claiming successful verification. |
| cost | Declaration selects the documented body behavior: Complete support/source scans, repeated per-alias adaptation/snapshots and ordered deep-key comparisons; may sort/copy all rows and consume substantial temporary capacity. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp) |

```text
@source-span:L144-L179:sha256:8eceb39f6184bd199bb1ba1238fd09405b47cf4e233682e280b43ae353c78c7d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare committed native source capture among existing serial physical observation/update APIs. |
| inputs / outputs | Combined public span options() through check_invariants(); additive source_image comments/declaration are L162-L165. |
| invariants | Inherited owner/sequence/result/source/statistics APIs remain. New capture exposes charged source-only compact data, not ordinary Database/string export or source mutation. It has one explicit selected image budget plus the backend operation ceiling; callers cannot use editable images to restore/authenticate state. |
| ownership | Returned image owns original-account nested payloads/program. Existing borrowed getters/cursors keep their existing lifetime/epoch rules; capture adds no shared-query or parallel writer authority. |
| failure | Capture while pending source update is active refuses runtime_busy; row/work/indexed/memory failures propagate without changing source state. Other inherited API failure contracts remain unchanged. |
| cost | Full native source directory/row/payload deep capture and actual cleanup; no result enumeration/delay bound is borrowed from CROWN. |
| Design | [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [docs/source_images.md](../../../../../source_images.md) |

## B0014

[Lines 180–215](../../../../../../include/crown/runtime/physical.hpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  using PlanSource=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name private ordinary/native compiler input alternatives. |
| inputs / outputs | variant&lt;PhysicalPlan,CompiledProgram&gt;. |
| invariants | Variant choice does not bypass native admission or permit foreign-account reuse; private constructors validate receiving context. |
| ownership | Variant owns one immutable source handle; native runtime retains admitted form. |
| failure | Type alias performs no validation; actual construction can fail. |
| cost | No alias runtime overhead; variant value transfer has handle/refcount costs. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  using RouteObserver =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name private synchronous adjacent-prefix output callback. |
| inputs / outputs | std::function receives occurrence/full route ordinal, before/after logical views and borrowed journal span. |
| invariants | Invoked only for a native zero crossing. All observer views/cursors must retire before another prefix; no async callback ownership is retained by PendingUpdate. |
| ownership | Caller owns callable/closure; callback may temporarily own view handles, journal span borrows pending stage storage. |
| failure | Callback can throw, causing stage_next to rollback the complete physical input; closure construction can allocate at its caller. |
| cost | Type-erased call plus arbitrary explicit observer/cursor/output work, separate from simple coordinator category counters. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/epoch_views.md](../../../../../epoch_views.md) |

```text
  std::shared_ptr<Impl> impl_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain facade access to mutable physical implementation. |
| inputs / outputs | Shared pointer moved by public move lifecycle, null after move. |
| invariants | Private pending owner can keep Impl alive after facade destruction; raw metadata borrows need surviving ownership. |
| ownership | One shared owner; kernel/cursor/output have their own independent retained paths. |
| failure | Getters enforce moved-from state through impl(); field itself adds no validation. |
| cost | Fixed handle, potentially complete final-owner teardown on replacement/release. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] bool same_sources(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two quiescent source databases exactly within one reoptimization budget. |
| inputs / outputs | Check sequence/table/population agreement, collect left rows in budgeted lexical set, probe/erase each right row, require set empty. |
| invariants | Full physical row identity including unused fields/tables is compared; equality is not inferred from hashes/counts. Both owners must be writable/quiescent. |
| ownership | Temporary keys from both sides are deep-copied into left account; sets/iterators stay local and source states remain unchanged. |
| failure | Budget row/work or storage/memory/comparison failures propagate; false mismatch is distinct from resource failure. |
| cost | Declaration selects the documented body behavior: Copies all left rows and each right probe, O(R log R) lexical comparisons plus scalar/string byte budget charging. Coexists with both owners and retains no global query result. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp) |

```text
  [[nodiscard]] const CompiledProgram& compiled_program() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native program for trusted internal composition. |
| inputs / outputs | Return kernel.compiled_program(). |
| invariants | No ordinary compiler graph is exported or retained by this getter. |
| ownership | Borrow into retained kernel/program. |
| failure | Moved-from facade/kernel access can reject. |
| cost | Declaration selects the documented body behavior: Constant reference access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] static PhysicalRuntime initialize_at(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward a complete database build with explicit committed sequence, carried metrics and optional existing context. |
| inputs / outputs | Call generic initialize_data on ordinary Database. |
| invariants | Private rebuild/restore composition preserves sequence and aggregate build credits. |
| ownership | Moves source/context; borrows database only during build. |
| failure | Delegated build failures propagate; no local recovery layer. |
| cost | Declaration selects the documented body behavior: Fixed delegation plus complete initialize_data work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] recovery::EncodedImage checkpoint_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete committed physical source rows and epoch into a bound recovery image. |
| inputs / outputs | Require quiescence, precheck table/row/field/zero-work bounds, build sorted native snapshot and RowView table arrays, call encode_image with supplied binding/limits. |
| invariants | Image stores source/epoch, not trusted live derived state. Supplied expected binding is a private recovery protocol input; codec validates its image envelope. |
| ownership | Snapshot, view arrays and encoded output consume existing account; RowViews borrow snapshot until encoding returns. |
| failure | Image/storage/memory errors propagate without mutating runtime. Codec work/byte limits do not cap all earlier snapshot/sort work. |
| cost | Declaration selects the documented body behavior: Deep copies/sorts all sources and builds full view inventory before encoding; live state/snapshot/encoded output can overlap. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp) |

```text
  [[nodiscard]] static PhysicalRuntime restore_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a bound source image, optionally match managed window set membership, and rebuild native state at restored epoch. |
| inputs / outputs | Decode under receiving account/limits; validate managed table IDs, unique window row keys and set equality for managed sources; freeze supplied native source then initialize_data at manifest epoch. |
| invariants | Window matching counts distinct keys, not event multiplicities/time order. Private caller supplies admitted source/context/binding and separately validated window checkpoint; derived support/count state is recomputed. |
| ownership | Decoded rows, matching sets/flags/counts and fresh target all funded under context account; borrowed window RowViews remain local. |
| failure | Corrupt/binding/limit/matching-work or native build/allocation errors return no target; formatted native storage failures occur after unwind. |
| cost | Declaration selects the documented body behavior: Full decode and optional ordered-key set scans with deep variable-width comparisons, plus source clone/full rebuild. Matching charges fields/counts, not all compared string bytes. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp) |

```text
  [[nodiscard]] static PhysicalRuntime initialize_data(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build complete native physical/support state privately from ordinary or native database views. |
| inputs / outputs | Validate method/table count/all rows/enforced constraints; insert full source rows, adapt each route, accumulate positive native counts and first-key seeds, initialize kernel then publish metrics/sequence/context. |
| invariants | Both build methods start from validated full final snapshot. Unique source membership and derivation limits are exact; each occurrence key seeds logical support only once. No externally visible prefix or epoch is committed. |
| ownership | Temporary native seeds and all target state use context account. Source views are borrowed; target rows/count keys are copied into funded ownership. |
| failure | Any work/memory/schema/constraint/duplicate/count/storage/support failure destroys private target; original owner/database untouched. Native Index/Table failures are presented after unwind. |
| cost | Declaration selects the documented body behavior: All row/deep payload import plus per-route adaptation/map lookup; whole-database constraints and support initialization can be large. Seed vector doubles with explicit pointer-slot credits; comparison/capacity costs are additional. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  PhysicalRuntime(PlanSource,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose a private physical owner using an explicitly existing account/backend work context. |
| inputs / outputs | Visit PhysicalPlan/CompiledProgram, validate context/account/backend/limit, bind storage operation and construct accounted Impl. |
| invariants | Nested operations reuse the active grant; native source account must equal context account. |
| ownership | Retains context and admitted source through kernel/Impl; new state is funded there. |
| failure | Native fixed failures format only after private construction unwinds; context/member/allocation errors propagate. |
| cost | Declaration selects the documented body behavior: Variant dispatch plus complete relevant source/kernel/physical admission; no per-helper budget refill. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] PhysicalRuntime rebuilt(BuildOptions,std::shared_ptr<detail::StorageWorkContext>) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild under the supplied original-account context using the current compiled program. |
| inputs / outputs | Delegate rebuilt_with_program(kernel.plan(),build,context). |
| invariants | Source/account/schema policy unchanged; private callee checks quiescence and receiving context. |
| ownership | Retains native source handle; no ordinary export. |
| failure | Native fixed errors format after delegated unwind; other failures propagate. |
| cost | Declaration selects the documented body behavior: Fixed handle/call work plus complete rebuilt_with_program cost. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] PhysicalRuntime rebuilt_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild against one checked minimum-height alternative without an ordinary compiler/source mirror. |
| inputs / outputs | Require quiescence, native replan original program/candidate, then rebuild target with supplied context. |
| invariants | Replan independently compares exact candidate/core binding and aliases admitted SQL/CQ source; this wrapper does not rerun SQL/P02/identity producer passes. |
| ownership | Fresh graph and rebuild state use original account; original runtime/source retained and unchanged. |
| failure | Replan/busy/context/build/resource errors propagate with no replacement publication. |
| cost | Declaration selects the documented body behavior: Full native exact-binding/new graph construction plus sorted source snapshot and target rebuild; immutable source work credits remain separate from actual recomputation. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp), [src/ir/program_replan.inc](../../../../../../src/ir/program_replan.inc) |

```text
  [[nodiscard]] PhysicalRuntime rebuilt_with_program(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct replacement state under the same account while retaining the original committed owner. |
| inputs / outputs | Validate target/context/account equality and build method, precharge snapshot dimensions, native snapshot/sort, initialize target at same sequence, set rebuilt context. |
| invariants | No account-limit reset or ordinary source Row graph. Equivalence/current publication is an outer reoptimization responsibility; this method only builds a candidate owner. |
| ownership | Original and target plus native snapshot coexist under original cap; target retains its program/context. |
| failure | Any admission/snapshot/import/support/observation failure destroys target; original remains untouched. |
| cost | Declaration selects the documented body behavior: All source deep copy/sort, constraint/adaptation/count/support rebuilding and overlap memory; abstract precharges do not bound comparison/allocator CPU. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../../src/runtime/validation_work.hpp) |

```text
  [[nodiscard]] std::shared_ptr<detail::StorageWorkContext> storage_context() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share existing account/backend operation context for nested coordination. |
| inputs / outputs | Return Impl storage_context shared_ptr. |
| invariants | Copying context does not replenish any finite operation lease or memory grant. |
| ownership | Shared owner transfer by copy. |
| failure | Moved-from invalid_runtime. |
| cost | Declaration selects the documented body behavior: Constant refcount work. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] PendingUpdate prepare_observed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain every alias prefix while preserving one private update barrier. |
| inputs / outputs | Owning physical update, observer and options return a completely routed pending token. |
| invariants | Uses begin_staged/stage_next without an alternate routing or error-recovery implementation. |
| ownership | Local token owns all private state until moved to caller. |
| failure | Route failure has already rolled back; local token destruction remains idempotent RAII. |
| cost | Declaration selects the documented body behavior: Sum of actual route work, not full-query result enumeration or a second support pass. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/indexed_storage.md](../../../../../indexed_storage.md) |

```text
  [[nodiscard]] PendingUpdate begin_staged(const PhysicalSetUpdate&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow caller-owned row only for native staged-input admission. |
| inputs / outputs | Convert to PhysicalUpdateView::borrow and delegate view overload. |
| invariants | No caller Row pointer survives successful admission; changed source input is imported/pinned, no-op needs no later row. |
| ownership | Nonowning temporary view then owning pending token. |
| failure | Delegated sequence/schema/busy/resource failures propagate with restoration. |
| cost | Declaration selects the documented body behavior: Constant view wrapping plus complete begin_staged(view) preparation. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../../src/runtime/storage_work.hpp) |

```text
  [[nodiscard]] PendingUpdate begin_staged(const PhysicalUpdateView&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire a private physical update before exposing its alias prefixes. |
| inputs / outputs | Borrowed sequence/table/operation/full row produce an owning prepared PendingUpdate. |
| invariants | Check quiescence, contiguous sequence, operation, typed row and membership first; fully construct Data, then set updating, then prepare under that unique owner. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. Caller row is borrowed only during admission; pending state retains native tuples/pins. |
| failure | Any preparation exception destroys local Data and rolls back before typed public presentation; invalid admission changes no sequence/state. |
| cost | Declaration selects the documented body behavior: Input validation/probe, funded owner/grant, then source/constraint/reserve work; no owning Row export. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/indexed_storage.md](../../../../../indexed_storage.md) |

```text
  [[nodiscard]] std::shared_ptr<detail::ObservationState> observation_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share optional internal observation owner with coordinating layers. |
| inputs / outputs | Return Impl observation shared_ptr copy. |
| invariants | Does not create/configure an observer or snapshot rows. |
| ownership | Adds observer owner, independent of facade lifetime. |
| failure | Moved-from facade rejects. |
| cost | Declaration selects the documented body behavior: Constant refcount copy. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] workload::detail::State& workload_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow kernel-owned internal workload collector. |
| inputs / outputs | Dereference Impl workload pointer. |
| invariants | Only trusted composition uses it; kernel owns the pointed state for Impl lifetime. |
| ownership | Nonowning mutable reference; no fresh collector. |
| failure | Moved-from rejects; retained internal pointer validity assumed. |
| cost | Declaration selects the documented body behavior: Constant access. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
  [[nodiscard]] Impl& impl() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate facade ownership and borrow mutable implementation for controlled const APIs. |
| inputs / outputs | Require impl_ then return Impl&. |
| invariants | Moved-from facade has no implementation; individual methods enforce pending/read isolation separately. |
| ownership | Borrow requires a surviving Impl owner. |
| failure | invalid_runtime Error on moved-from; valid access allocates nothing. |
| cost | Declaration selects the documented body behavior: Constant pointer check. |
| Design | [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant private physical-state access exclusively to the testing probe build. |
| inputs / outputs | Conditional friend declaration agrees with guarded implementation probes. |
| invariants | Production source excludes this friendship and mutable probe body groups; ordinary public clients get no kernel/table reference. |
| ownership | Compile-time access control only. |
| failure | Invalid production private access is a compile error. |
| cost | No runtime state/check overhead. |
| Design | [CMakeLists.txt](../../../../../../CMakeLists.txt), [tests/support/runtime_probe.hpp](../../../../../../tests/support/runtime_probe.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp) |
