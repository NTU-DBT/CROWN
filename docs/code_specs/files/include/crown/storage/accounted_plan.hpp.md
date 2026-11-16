# `include/crown/storage/accounted_plan.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_plan.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `bd1abe8afb05615c4167e9d25ef0a448df17ed7f13a93fb140868d2c737ffe35`. 148 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/storage/accounted_plan.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Immutable compilation borrows its own fixed-diagnostic work grant. Indexed · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../../include/crown/storage/accounted_plan.hpp#L12) | Type/record definition: enum class MetadataWork | source comment (unverified): // Immutable compilation borrows its own fixed-diagnostic work grant. Indexed · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../../include/crown/storage/accounted_plan.hpp#L13) | declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0003) |
| [B0004 · 14–23](../../../../../../include/crown/storage/accounted_plan.hpp#L14) | Type/record definition: struct PlanStorageMemoryStatistics | source comment (unverified): // Sum of these two attribution owners, once each. Table payloads and shared · [reviewed contract](#b0004) |
| [B0005 · 24–30](../../../../../../include/crown/storage/accounted_plan.hpp#L24) | declares types or opens a type body. | source comment (unverified): // Native storage binding. Constructor spans are borrowed only during import; · [reviewed contract](#b0005) |
| [B0006 · 31–39](../../../../../../include/crown/storage/accounted_plan.hpp#L31) | Type/record definition: struct Inputs | source comment (unverified): // Test shim only; public plan constructor always uses zero. · [reviewed contract](#b0006) |
| [B0007 · 40–46](../../../../../../include/crown/storage/accounted_plan.hpp#L40) | Type/record definition: public: struct RelationBinding |  · [reviewed contract](#b0007) |
| [B0008 · 47–47](../../../../../../include/crown/storage/accounted_plan.hpp#L47) | Type/record definition: struct FrozenIndexBinding |  · [reviewed contract](#b0008) |
| [B0009 · 48–49](../../../../../../include/crown/storage/accounted_plan.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Immutable binding ownership without retaining any mutable table instance. · [reviewed contract](#b0009) |
| [B0010 · 50–72](../../../../../../include/crown/storage/accounted_plan.hpp#L50) | Type/record definition: class Binding | returns bool(metadata_); source comment (unverified): // Immutable binding ownership without retaining any mutable table instance. · [reviewed contract](#b0010) |
| [B0011 · 73–73](../../../../../../include/crown/storage/accounted_plan.hpp#L73) | Explanatory comments or spacing. | source comment (unverified): // The source and its spans are borrowed only for this constructor call. · [reviewed contract](#b0011) |
| [B0012 · 74–78](../../../../../../include/crown/storage/accounted_plan.hpp#L74) | Callable definition: AccountedPlanStorage(const resource::MemoryAccount& account, const PhysicalPlan& plan, IndexWorkAllowance* work = nullptr) : Acco… | calls route, physical_sha256, guarantee, layouts; source comment (unverified): // The source and its spans are borrowed only for this constructor call. · [reviewed contract](#b0012) |
| [B0013 · 79–85](../../../../../../include/crown/storage/accounted_plan.hpp#L79) | Callable definition: \[\[nodiscard\]\] static Binding freeze_binding(const resource::MemoryAccount& account, const PhysicalPlan& plan,IndexWorkAllowance* … | calls metadata, route, physical_sha256, guarantee; returns metadata.binding() · [reviewed contract](#b0013) |
| [B0014 · 86–104](../../../../../../include/crown/storage/accounted_plan.hpp#L86) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Native compiler metadata already owns these tokens under this account. · [reviewed contract](#b0014) |
| [B0015 · 105–134](../../../../../../include/crown/storage/accounted_plan.hpp#L105) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Full diagnostic: only index-binding probes debit this grant; table/layout scans are not wholly IndexWork-metered. · [reviewed contract](#b0015) |
| [B0016 · 135–135](../../../../../../include/crown/storage/accounted_plan.hpp#L135) | Type/record definition: struct ColdRebuild | source comment (unverified): // Only the closed unpublished SQL rebuild can materialize under a separate · [reviewed contract](#b0016) |
| [B0017 · 136–148](../../../../../../include/crown/storage/accounted_plan.hpp#L136) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0017) |

## B0001

[Lines 1–11](../../../../../../include/crown/storage/accounted_plan.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the native accounted plan-storage facade and its immutable binding view. |
| inputs / outputs | Imports physical-plan and native table types; opens storage namespace. |
| invariants | This is a non-null classical storage binding, not a nullable SQL evaluator or weighted annotation implementation. |
| ownership | Declarations own no live account, source plan or table. |
| failure | Compilation enforces referenced types; no runtime recovery path. |
| cost | No runtime work for includes/declarations. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp) |

```text
#pragma once #include "crown/ir/physical.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give only the cold source bridge access to the private storage admission tag. |
| inputs / outputs | The forward declaration/friend resolves the closed internal type from AccountedPlanStorage. |
| invariants | No public larger-than-per_operation storage constructor is added. |
| ownership | Friend relation only. |
| failure | Compilation enforces name/access. |
| cost | No runtime cost. |
| Design | [include/crown/storage/accounted_plan.hpp](../../../../../../include/crown/storage/accounted_plan.hpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../../src/runtime/sql_cold_rebuild.hpp) |

## B0002

[Lines 12–12](../../../../../../include/crown/storage/accounted_plan.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MetadataWork
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose which existing work authority applies to immutable metadata construction. |
| inputs / outputs | execution uses indexed per-operation admission; compiler requires a supplied fixed-diagnostic grant without that execution-cap comparison. |
| invariants | Compiler mode is permitted only for metadata-only import; mutable table materialization requires execution mode. |
| ownership | Enumeration contains no grant and creates no new allowance. |
| failure | Invalid combinations are rejected in constructor/helper; the enum itself cannot fail. |
| cost | One tag branch at construction, absent from tuple operations. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0003

[Lines 13–13](../../../../../../include/crown/storage/accounted_plan.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace detail { class AccountedPlanStorageTesting; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare the private plan-storage test authority. |
| inputs / outputs | Names the friend used by conditional collision-profile fixtures. |
| invariants | The declaration adds no public setter, alternate production hash function or runtime owner. |
| ownership | Type name only; no instance or retained resource. |
| failure | Compile-time friendship resolution only. |
| cost | Zero runtime work. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table_testing.hpp](../../../../../../src/storage/accounted_table_testing.hpp) |

## B0004

[Lines 14–23](../../../../../../include/crown/storage/accounted_plan.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanStorageMemoryStatistics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report native binding/instance allocation-owner totals and current descriptor counts. |
| inputs / outputs | Counts plus two attributed memory snapshots; owned sums their current usage. |
| invariants | The two distinct metadata/instance owner tags are counted once; table payloads and tokens charged to another sharing owner are outside owned. |
| ownership | Plain copied statistics retain no plan, row, allocator block or account authority. |
| failure | Default comparison is value comparison; collection/checked totals can fail in memory_statistics(). |
| cost | Fixed result storage; obtaining the result requires two scans of all live account allocations. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp) |

## B0005

[Lines 24–30](../../../../../../include/crown/storage/accounted_plan.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Native storage binding. Constructor spans are borrowed only during import;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate immutable physical storage bindings from mutable relation tables. |
| inputs / outputs | Public constructors import a PhysicalPlan or already frozen Binding; accessors expose checked native objects. |
| invariants | No borrowed PhysicalPlan graph is retained. CompiledProgram owns executable instructions separately; this object owns only its storage program and tables. |
| ownership | metadata_ shares immutable native metadata; tables_/indexes_ own instance arrays. |
| failure | Fallible construction uses member/local RAII, with no generic catch/repair framework. |
| cost | Import/materialization visits plan metadata and can allocate; established accessors are direct indexed views. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp) |

## B0006

[Lines 31–39](../../../../../../include/crown/storage/accounted_plan.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Inputs
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact storage-relevant fields for one private plan import. |
| inputs / outputs | Route, 64-character identity, backend guarantee, layouts/relations/indexes and optional indexed specification. |
| invariants | All source spans survive the importing call. collision_profile is zero in production; nonzero modes require the private test build. |
| ownership | Owns only scalar tags and an optional copied backend specification; strings/spans borrow the caller. |
| failure | Constructor validates route, identity, backend and token relationships before publishing metadata. |
| cost | Fixed borrowed descriptor; later import costs follow arrays and fields. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp) |

## B0007

[Lines 40–46](../../../../../../include/crown/storage/accounted_plan.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
public:
  struct RelationBinding
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the numeric relation-to-layout/origin binding after import. |
| inputs / outputs | Role, LayoutId and optional logical node/base IDs. |
| invariants | layout identifies an imported canonical layout; role is validated at freeze/import. This record does not re-prove the complete planner tree. |
| ownership | Owns scalar identifiers; layout payload remains in the enclosing Metadata layouts array. |
| failure | No allocation or throwing record behavior; range/token checks belong to import/access. |
| cost | Fixed-size copied metadata. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp) |

## B0008

[Lines 47–47](../../../../../../include/crown/storage/accounted_plan.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FrozenIndexBinding
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass an already owned canonical projection with its source relation. |
| inputs / outputs | RelationId and AccountedProjection input to freeze_native_binding. |
| invariants | Projection source/target tokens must be those of the supplied layouts, and its source layout must match the relation binding. |
| ownership | Projection handle retains funded immutable metadata; no row/index instance is retained. |
| failure | Validation occurs during import; copying a valid handle does not allocate a descriptor mirror. |
| cost | Fixed shared-owner copy; freeze validates each index once. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp) |

## B0009

[Lines 48–49](../../../../../../include/crown/storage/accounted_plan.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Immutable binding ownership without retaining any mutable table instance.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the lifetime boundary between shared immutable binding and rebuildable mutable state. |
| inputs / outputs | Binding returned from import, binding(), or clone can outlive table instances. |
| invariants | Constructing new tables from a binding retains its original canonical layout/projection tokens and account. |
| ownership | Shared metadata is strongly owned; tables and rows are not captured. |
| failure | Empty/moved Binding is permitted as a value but guarded access throws invalid_storage. |
| cost | Retain/release uses shared ownership, with possible final metadata destruction. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp) |

## B0010

[Lines 50–72](../../../../../../include/crown/storage/accounted_plan.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Binding {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain and inspect the funded immutable storage binding. |
| inputs / outputs | Default empty handle, Boolean validity, checked account/layout/projection/route/identity/count accessors. |
| invariants | Borrowing accessors are lvalue-only; returned spans/references/string_view require a live retaining binding or another metadata owner. IDs are array offsets, not independent authorization. |
| ownership | One shared_ptr&lt;const Metadata&gt;; private constructor moves an existing owner. No mutable table is retained. |
| failure | metadata() rejects empty state; layout/projection reject out-of-range IDs with fixed IndexFailure. |
| cost | Successful handle/accessor work is fixed plus shared reference counting; final release can destroy all owned metadata. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp) |

## B0011

[Lines 73–73](../../../../../../include/crown/storage/accounted_plan.hpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The source and its spans are borrowed only for this constructor call.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the public PhysicalPlan constructor import lifetime. |
| inputs / outputs | The following delegating constructor borrows the plan only during construction. |
| invariants | The plan may be destroyed after import; retained fields/tokens are native account-funded values. |
| ownership | No source span escapes construction. |
| failure | Any import/materialization failure unwinds unpublished native ownership. |
| cost | No comment/runtime cost; actual import and table construction are explicit below. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp) |

## B0012

[Lines 74–78](../../../../../../include/crown/storage/accounted_plan.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage(const resource::MemoryAccount& account, const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import a checked physical storage program and create its empty mutable relation/index instances. |
| inputs / outputs | Existing receiving account, borrowed PhysicalPlan and optional caller grant. |
| invariants | Uses execution mode. Indexed plans require a fixed grant whose remaining domains do not exceed the declared operation cap; reference execution ignores a supplied grant. |
| ownership | Owns copied native metadata and newly created tables under the existing account; retains no legacy plan. |
| failure | Validation, work/account/allocator/owner failures propagate through ordinary RAII before publication. |
| cost | Cold O(layout token scans + layout fields/bytes + relation/index processing + empty table/index construction), with potentially quadratic projection deduplication. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0013

[Lines 79–85](../../../../../../include/crown/storage/accounted_plan.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static Binding freeze_binding(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import immutable bindings without constructing mutable tables. |
| inputs / outputs | Account/plan/grant/mode in; Binding retaining imported metadata out. |
| invariants | Passes materialize=false. Compiler mode uses the caller compiler grant; execution mode checks indexed cap. No replacement grant/account is created. |
| ownership | Temporary facade releases empty instance arrays; returned Binding owns metadata/layout/projection backing. |
| failure | Unpublished construction unwinds; work already consumed and monotone owner IDs are not refunded. |
| cost | Cold import only: descriptor/token traversal and funded metadata allocation, no source rows or mutable table instance. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0014

[Lines 86–104](../../../../../../include/crown/storage/accounted_plan.hpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Native compiler metadata already owns these tokens under this account.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe explicit frozen-binding import, cross-account clone and materialization factories. |
| inputs / outputs | freeze_native_binding aliases same-account tokens; clone_binding creates new tokens in the receiver; Binding constructor creates empty mutable tables. |
| invariants | Use native import only with already owned compatible tokens. Cross-account import is a deep clone, not an uncharged alias. Copies of AccountedPlanStorage are disabled. |
| ownership | Move transfers complete instance ownership; immutable Binding copies share metadata. |
| failure | Factories propagate fixed validation/work/memory failures and rely on RAII; no fallback/retry layer is added. |
| cost | Native alias import is linear in binding arrays; clone may scan prior projections quadratically; materialization visits relations/indexes. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0015

[Lines 105–134](../../../../../../include/crown/storage/accounted_plan.hpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] StorageOwnerId owner() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify checked instance inspection, explicit snapshots and explicit full diagnostics. |
| inputs / outputs | Owner/backend/route/binding/layout/relation/projection/table/index/count/statistics access; snapshot_copy and check_invariants optionally borrow a caller grant. |
| invariants | Views borrow a live facade/shared metadata. Table references additionally require their instance to survive. binding() shares immutable metadata; snapshot_copy is an explicit deep table copy, never an implicit ordinary-update primitive. |
| ownership | Facade owns metadata_ plus tables_/indexes_. Internal adoption constructor moves already prepared owners; no borrowed source state is kept. |
| failure | Empty metadata and bad IDs produce fixed IndexFailure. Mutating through table references follows that table API; diagnostic/snapshot allocation failures propagate. |
| cost | Accessors are direct. Statistics scan all live account allocations twice; snapshots visit/copy full table state; check_invariants scans all layouts/tables/index bindings. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp), [docs/code_specs/primitives.md](../../../../primitives.md) |

```text
[[nodiscard]] StorageOwnerId owner() const; [[nodiscard]] Binding binding() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain existing public accounted-plan inspection and operation APIs around a private constructor. |
| inputs / outputs | The surrounding public owner/binding/table methods stay the ordinary access route. |
| invariants | Cold tag/materializer are private and do not change current table/layout/backend identity contracts. |
| ownership | Returned references keep existing AccountedPlanStorage lifetime requirements. |
| failure | Existing storage contract errors remain the only public failure boundary. |
| cost | No public API/record addition. |
| Design | [include/crown/storage/accounted_plan.hpp](../../../../../../include/crown/storage/accounted_plan.hpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../../memory_accounts.md) |

## B0016

[Lines 135–135](../../../../../../include/crown/storage/accounted_plan.hpp#L135); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColdRebuild
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use an unconstructible-to-callers tag to select cold materialization internally. |
| inputs / outputs | The nested private \`ColdRebuild\` type distinguishes the private cold constructor from normal execution construction. |
| invariants | It does not turn a supplied large work cap into plan.per_operation or alter physical identity. |
| ownership | Stateless private tag. |
| failure | Only source-private friend can construct/select it. |
| cost | No runtime allocation or plan field. |
| Design | [include/crown/storage/accounted_plan.hpp](../../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0017

[Lines 136–148](../../../../../../include/crown/storage/accounted_plan.hpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage(Binding, IndexWorkAllowance*, ColdRebuild); void materialize(IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one storage materialization body across normal and closed cold constructors. |
| inputs / outputs | Private cold constructor and \`materialize\` take the existing immutable Binding and a selected grant. |
| invariants | Normal constructor still calls operation_work with plan cap validation; cold path requires backend/grant agreement and fixed diagnostics; original per-table limits/tests remain. |
| ownership | Unpublished AccountedPlanStorage owns new table/index nodes; allowances are borrowed only during construction. |
| failure | Any table/index/work/account failure destroys the unpublished owner. |
| cost | Shared relation/index loops and vector capacity admissions; cold does not mutate the immutable plan cap. |
| Design | [include/crown/storage/accounted_plan.hpp](../../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp), [docs/memory_accounts.md §Native accounted dispatch](../../../../../memory_accounts.md) |
