# `src/storage/accounted_plan.cpp` — block usage map

[Source](../../../../../src/storage/accounted_plan.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `3cf3fc38a1dce40577b1c45f3d3a0f842dd80755112b19985914e5ed406adc22`. 367 lines partitioned into 53 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/storage/accounted_plan.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../src/storage/accounted_plan.cpp#L15) | Callable definition: MemoryAttribution tag(StorageOwnerId owner) | calls ; returns {resource::MemoryOwnerKind::immutable_metadata, owner.value} · [reviewed contract](#b0002) |
| [B0003 · 16–20](../../../../../src/storage/accounted_plan.cpp#L16) | Callable definition: StorageOwnerId next_owner() | calls detail::try_new_storage_owner, IndexFailure; returns *id · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../src/storage/accounted_plan.cpp#L21) | Callable definition: void require(bool value) | calls IndexFailure; guard void require(bool value) { if (!value) throw IndexFailure(IndexFault::contract); } · [reviewed contract](#b0004) |
| [B0005 · 22–26](../../../../../src/storage/accounted_plan.cpp#L22) | Callable definition: std::uint64_t count(std::size_t value) | calls constexpr, max, IndexFailure; returns static_cast&lt;std::uint64_t&gt;(value) · [reviewed contract](#b0005) |
| [B0006 · 27–30](../../../../../src/storage/accounted_plan.cpp#L27) | Callable definition: std::uint64_t add(std::uint64_t a, std::uint64_t b) | calls max, IndexFailure; returns a + b · [reviewed contract](#b0006) |
| [B0007 · 31–42](../../../../../src/storage/accounted_plan.cpp#L31) | Callable definition: IndexWorkAllowance* operation_work(const std::optional&lt;IndexedBackendSpec&gt;& spec, IndexWorkAllowance* work, MetadataWork mode=Met… | calls require, fixed_diagnostics, remaining, admit; guard if(mode==MetadataWork::compiler) {require(work && work-&gt;fixed_diagnostics());return work;}; returns work; nullptr; source comment (unverified): // Borrow existing authority: compiler work is separate; reference execution · [reviewed contract](#b0007) |
| [B0008 · 43–43](../../../../../src/storage/accounted_plan.cpp#L43) | Callable definition: void step(IndexWorkAllowance* work, std::uint64_t n = 1) | calls admit · [reviewed contract](#b0008) |
| [B0009 · 44–50](../../../../../src/storage/accounted_plan.cpp#L44) | Callable definition: template&lt;class T&gt; void prepare_vector(std::size_t n, IndexWorkAllowance* work) | calls count, max, IndexFailure, admit · [reviewed contract](#b0009) |
| [B0010 · 51–52](../../../../../src/storage/accounted_plan.cpp#L51) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 53–70](../../../../../src/storage/accounted_plan.cpp#L53) | Type/record definition: struct AccountedPlanStorage::Metadata |  · [reviewed contract](#b0011) |
| [B0012 · 71–71](../../../../../src/storage/accounted_plan.cpp#L71) | Explanatory comments or spacing. |  |
| [B0013 · 72–110](../../../../../src/storage/accounted_plan.cpp#L72) | Callable definition: AccountedPlanStorage::Binding AccountedPlanStorage::freeze_native_binding( const resource::MemoryAccount& account,PhysicalRoute r… | calls operation_work, require, size, admit; guard require(route==PhysicalRoute::tree \|\| route==PhysicalRoute::constant_true \|\| route==PhysicalRoute::…; returns Binding(std::move(data)); growth make_accounted_shared, push_back, reserve; 4 loop sites · [reviewed contract](#b0013) |
| [B0014 · 111–111](../../../../../src/storage/accounted_plan.cpp#L111) | Explanatory comments or spacing. |  |
| [B0015 · 112–141](../../../../../src/storage/accounted_plan.cpp#L112) | Callable definition: AccountedPlanStorage::Binding AccountedPlanStorage::clone_binding(const resource::MemoryAccount& account, const Binding& source,I… | calls metadata, operation_work, next_owner, size; guard require(from&lt;data-&gt;layouts.size() && to&lt;data-&gt;layouts.size());; returns Binding(std::move(data)); growth make_accounted_shared, push_back, reserve; 4 loop sites; source comment (unverified): // Construction-only token deduplication can scan O(index_count^2) pairs. · [reviewed contract](#b0015) |
| [B0016 · 142–142](../../../../../src/storage/accounted_plan.cpp#L142) | Explanatory comments or spacing. |  |
| [B0017 · 143–228](../../../../../src/storage/accounted_plan.cpp#L143) | Callable definition: AccountedPlanStorage::AccountedPlanStorage(const resource::MemoryAccount& account, const Inputs& input, IndexWorkAllowance* suppl… | calls owner_, next_owner, tables_, tag; guard require(!materialize \|\| mode==MetadataWork::execution);; returns position; growth emplace_back, make_accounted_shared, push_back, reserve; 7 loop sites; source comment (unverified): // Initialization charges explicit token scans, descriptor fields/binding · [reviewed contract](#b0017) |
| [B0018 · 229–229](../../../../../src/storage/accounted_plan.cpp#L229) | Explanatory comments or spacing. |  |
| [B0019 · 230–235](../../../../../src/storage/accounted_plan.cpp#L230) | Callable definition: AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* supplied) :metadata_(std::move(binding.metadata_))… | calls metadata_, std::move, owner_, next_owner · [reviewed contract](#b0019) |
| [B0020 · 236–245](../../../../../src/storage/accounted_plan.cpp#L236) | Callable definition: AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* work,ColdRebuild) :metadata_(std::move(binding.met… | calls metadata_, std::move, owner_, next_owner; guard require(bool(metadata().indexed)==bool(work));; source comment (unverified): // A distinct immutable cold context supplies this finite grant. This private · [reviewed contract](#b0020) |
| [B0021 · 246–261](../../../../../src/storage/accounted_plan.cpp#L246) | Callable definition: void AccountedPlanStorage::materialize(IndexWorkAllowance* work) | calls metadata, size, reserve, step; growth emplace_back, push_back, reserve; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 262–262](../../../../../src/storage/accounted_plan.cpp#L262) | Explanatory comments or spacing. |  |
| [B0023 · 263–266](../../../../../src/storage/accounted_plan.cpp#L263) | Callable definition: const AccountedPlanStorage::Metadata& AccountedPlanStorage::Binding::metadata() const | calls IndexFailure; returns *metadata_ · [reviewed contract](#b0023) |
| [B0024 · 267–267](../../../../../src/storage/accounted_plan.cpp#L267) | Callable definition: const resource::MemoryAccount& AccountedPlanStorage::Binding::account() const & | calls metadata; returns metadata().account · [reviewed contract](#b0024) |
| [B0025 · 268–268](../../../../../src/storage/accounted_plan.cpp#L268) | Callable definition: std::span&lt;const AccountedLayout&gt; AccountedPlanStorage::Binding::layouts() const & | calls metadata; returns metadata().layouts · [reviewed contract](#b0025) |
| [B0026 · 269–272](../../../../../src/storage/accounted_plan.cpp#L269) | Callable definition: const AccountedLayout& AccountedPlanStorage::Binding::layout(LayoutId id) const & | calls metadata, size, IndexFailure; returns data.layouts\[id.value\] · [reviewed contract](#b0026) |
| [B0027 · 273–276](../../../../../src/storage/accounted_plan.cpp#L273) | Callable definition: const AccountedProjection& AccountedPlanStorage::Binding::projection(IndexRequirementId id) const & | calls metadata, size, IndexFailure; returns data.indexes\[id.value\].projection · [reviewed contract](#b0027) |
| [B0028 · 277–277](../../../../../src/storage/accounted_plan.cpp#L277) | Callable definition: PhysicalRoute AccountedPlanStorage::Binding::route() const | calls metadata; returns metadata().route · [reviewed contract](#b0028) |
| [B0029 · 278–280](../../../../../src/storage/accounted_plan.cpp#L278) | Callable definition: std::string_view AccountedPlanStorage::Binding::physical_identity() const & | calls metadata, data, size; returns {identity.data(),identity.size()} · [reviewed contract](#b0029) |
| [B0030 · 281–281](../../../../../src/storage/accounted_plan.cpp#L281) | Callable definition: std::size_t AccountedPlanStorage::Binding::relation_count() const | calls metadata, size; returns metadata().relations.size() · [reviewed contract](#b0030) |
| [B0031 · 282–282](../../../../../src/storage/accounted_plan.cpp#L282) | Callable definition: std::size_t AccountedPlanStorage::Binding::index_count() const | calls metadata, size; returns metadata().indexes.size() · [reviewed contract](#b0031) |
| [B0032 · 283–283](../../../../../src/storage/accounted_plan.cpp#L283) | Callable definition: AccountedPlanStorage::Binding AccountedPlanStorage::binding() const & | calls metadata, Binding; returns Binding(metadata_) · [reviewed contract](#b0032) |
| [B0033 · 284–284](../../../../../src/storage/accounted_plan.cpp#L284) | Explanatory comments or spacing. |  |
| [B0034 · 285–287](../../../../../src/storage/accounted_plan.cpp#L285) | Callable definition: AccountedPlanStorage::AccountedPlanStorage(std::shared_ptr&lt;const Metadata&gt; metadata, StorageOwnerId owner, AccountedVector&lt;Accoun… | calls metadata_, std::move, owner_, tables_ · [reviewed contract](#b0034) |
| [B0035 · 288–291](../../../../../src/storage/accounted_plan.cpp#L288) | Callable definition: AccountedPlanStorage& AccountedPlanStorage::operator=(AccountedPlanStorage&& other) noexcept | calls std::construct_at, std::move; returns *this · [reviewed contract](#b0035) |
| [B0036 · 292–295](../../../../../src/storage/accounted_plan.cpp#L292) | Callable definition: const AccountedPlanStorage::Metadata& AccountedPlanStorage::metadata() const | calls IndexFailure; returns *metadata_ · [reviewed contract](#b0036) |
| [B0037 · 296–296](../../../../../src/storage/accounted_plan.cpp#L296) | Callable definition: StorageOwnerId AccountedPlanStorage::owner() const | calls metadata; returns owner_ · [reviewed contract](#b0037) |
| [B0038 · 297–297](../../../../../src/storage/accounted_plan.cpp#L297) | Callable definition: StorageBackend AccountedPlanStorage::backend() const | calls metadata; returns metadata().indexed ? StorageBackend::indexed_chained_v1 : StorageBackend::reference_ordered_v1 · [reviewed contract](#b0038) |
| [B0039 · 298–298](../../../../../src/storage/accounted_plan.cpp#L298) | Callable definition: PhysicalRoute AccountedPlanStorage::route() const | calls metadata; returns metadata().route · [reviewed contract](#b0039) |
| [B0040 · 299–299](../../../../../src/storage/accounted_plan.cpp#L299) | Callable definition: std::string_view AccountedPlanStorage::physical_identity() const & | calls metadata, data, size; returns {metadata().identity.data(), metadata().identity.size()} · [reviewed contract](#b0040) |
| [B0041 · 300–300](../../../../../src/storage/accounted_plan.cpp#L300) | Callable definition: std::span&lt;const AccountedLayout&gt; AccountedPlanStorage::layouts() const & | calls metadata; returns metadata().layouts · [reviewed contract](#b0041) |
| [B0042 · 301–304](../../../../../src/storage/accounted_plan.cpp#L301) | Callable definition: const AccountedLayout& AccountedPlanStorage::layout(LayoutId id) const & | calls metadata, size, IndexFailure; returns data.layouts\[id.value\] · [reviewed contract](#b0042) |
| [B0043 · 305–308](../../../../../src/storage/accounted_plan.cpp#L305) | Callable definition: const AccountedPlanStorage::RelationBinding& AccountedPlanStorage::relation(RelationId id) const & | calls metadata, size, IndexFailure; returns data.relations\[id.value\] · [reviewed contract](#b0043) |
| [B0044 · 309–312](../../../../../src/storage/accounted_plan.cpp#L309) | Callable definition: const AccountedProjection& AccountedPlanStorage::projection(IndexRequirementId id) const & | calls metadata, size, IndexFailure; returns data.indexes\[id.value\].projection · [reviewed contract](#b0044) |
| [B0045 · 313–316](../../../../../src/storage/accounted_plan.cpp#L313) | Callable definition: AccountedStorageTable& AccountedPlanStorage::table(RelationId id) & | calls metadata, size, IndexFailure; returns tables_\[id.value\] · [reviewed contract](#b0045) |
| [B0046 · 317–320](../../../../../src/storage/accounted_plan.cpp#L317) | Callable definition: const AccountedStorageTable& AccountedPlanStorage::table(RelationId id) const & | calls metadata, size, IndexFailure; returns tables_\[id.value\] · [reviewed contract](#b0046) |
| [B0047 · 321–324](../../../../../src/storage/accounted_plan.cpp#L321) | Callable definition: IndexId AccountedPlanStorage::index(IndexRequirementId id) const | calls metadata, size, IndexFailure; returns indexes_\[id.value\] · [reviewed contract](#b0047) |
| [B0048 · 325–325](../../../../../src/storage/accounted_plan.cpp#L325) | Callable definition: std::size_t AccountedPlanStorage::relation_count() const | calls metadata, size; returns tables_.size() · [reviewed contract](#b0048) |
| [B0049 · 326–326](../../../../../src/storage/accounted_plan.cpp#L326) | Callable definition: std::size_t AccountedPlanStorage::index_count() const | calls metadata, size; returns indexes_.size() · [reviewed contract](#b0049) |
| [B0050 · 327–337](../../../../../src/storage/accounted_plan.cpp#L327) | Callable definition: PlanStorageMemoryStatistics AccountedPlanStorage::memory_statistics() const | calls metadata, size, statistics_for, tag; returns result; source comment (unverified): // Each attribution query scans the account's existing allocation list; it · [reviewed contract](#b0050) |
| [B0051 · 338–350](../../../../../src/storage/accounted_plan.cpp#L338) | Callable definition: AccountedPlanStorage AccountedPlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const | calls metadata, operation_work, size, next_owner; returns {metadata_, id, std::move(tables), std::move(indexes)}; growth push_back, reserve; 2 loop sites; source comment (unverified): // Explicit bulk copy: old and new state overlap under the same account. · [reviewed contract](#b0051) |
| [B0052 · 351–366](../../../../../src/storage/accounted_plan.cpp#L351) | Callable definition: void AccountedPlanStorage::check_invariants(IndexWorkAllowance* supplied) const | calls metadata, operation_work, require, size; guard require(tables_.size() == data.relations.size() && indexes_.size() == data.indexes.size());; 3 loop sites · [reviewed contract](#b0052) |
| [B0053 · 367–367](../../../../../src/storage/accounted_plan.cpp#L367) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0053) |

## B0001

[Lines 1–14](../../../../../src/storage/accounted_plan.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/accounted_plan.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the native immutable binding importer and mutable table facade. |
| inputs / outputs | Uses the shared process owner-ID authority and optionally private collision test hooks. |
| invariants | Production builds admit only collision_profile zero; no duplicate owner authority or native SQL value layer is introduced. |
| ownership | Imports/declarations retain no live state. |
| failure | Compile-time dependency failure only. |
| cost | No runtime work for includes/aliases. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/owner.hpp](../../../../../src/storage/owner.hpp) |

## B0002

[Lines 15–15](../../../../../src/storage/accounted_plan.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAttribution tag(StorageOwnerId owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute physical binding or instance array storage to one existing numeric owner. |
| inputs / outputs | StorageOwnerId in; immutable_metadata-kind attribution out. |
| invariants | The same tag is reused consistently for each owner; it does not indicate all table payloads share that attribution. |
| ownership | Value-only record, no account/block owner. |
| failure | No explicit failing operation. |
| cost | Fixed scalar construction. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0003

[Lines 16–20](../../../../../src/storage/accounted_plan.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId next_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain a fresh process-wide physical storage identity. |
| inputs / outputs | Calls nonthrowing try_new_storage_owner; returns its ID. |
| invariants | Identities are never rolled back or reused after failed construction; shared backend authority remains the source. |
| ownership | Scalar ID only, no table/account allocation. |
| failure | Exhaustion throws fixed IndexFailure(overflow). |
| cost | One bounded owner-authority operation and presence check. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/owner.hpp](../../../../../src/storage/owner.hpp) |

## B0004

[Lines 21–21](../../../../../src/storage/accounted_plan.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a failed internal import/access precondition directly. |
| inputs / outputs | Boolean in; true returns, false throws fixed IndexFailure(contract). |
| invariants | Does not retry, repair state or format an owning error string. |
| ownership | No owned input/state. |
| failure | Only the failed branch throws; caller RAII owns cleanup. |
| cost | One branch; no successful allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0005

[Lines 22–26](../../../../../src/storage/accounted_plan.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t count(std::size_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a collection size to the exact work/counter width. |
| inputs / outputs | size_t in; checked uint64 value out. |
| invariants | Wider size_t targets reject truncation; ordinary &lt;=64-bit targets use direct conversion. |
| ownership | Value only. |
| failure | Fixed overflow failure before invalid admission. |
| cost | Constant compile-time-selected guard/conversion. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0006

[Lines 27–30](../../../../../src/storage/accounted_plan.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t add(std::uint64_t a, std::uint64_t b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add work/statistics quantities without wrapping. |
| inputs / outputs | Two uint64 values in; exact sum out. |
| invariants | Subtraction guard prevents overflow and preserves unit meaning chosen by caller. |
| ownership | Value only. |
| failure | Fixed overflow failure; no partial caller assignment. |
| cost | Constant arithmetic. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0007

[Lines 31–42](../../../../../src/storage/accounted_plan.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance* operation_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select and validate the existing work allowance for this construction/diagnostic operation. |
| inputs / outputs | Optional backend spec, borrowed supplied grant and mode; returns supplied pointer or null. |
| invariants | Compiler mode requires fixed diagnostics but does not compare execution cap or debit startup. Reference execution returns null even when a grant is supplied. Indexed execution checks all five remaining domains &lt;= per_operation and admits one structural startup. |
| ownership | Borrows exactly the caller grant; no allocation, copy, refill or new cap. |
| failure | Missing/nonfixed/over-cap grant throws contract. Startup exhaustion throws work_limit with earlier work preserved. |
| cost | Fixed tests across five work domains plus one indexed admission; not a per-tuple metadata scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0008

[Lines 43–43](../../../../../src/storage/accounted_plan.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step(IndexWorkAllowance* work, std::uint64_t n = 1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit explicit structural metadata work when the chosen operation is metered. |
| inputs / outputs | Nullable borrowed grant and count; admits structural_steps=n. |
| invariants | Null means this reference execution path is intentionally unmetered by IndexWork. No grant is synthesized. |
| ownership | No ownership transfer. |
| failure | Admission failure propagates without refunding prior admissions. |
| cost | Fixed allowance check/subtraction, independent of n. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0009

[Lines 44–50](../../../../../src/storage/accounted_plan.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void prepare_vector(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit conservative pointer-word capacity before an accounted metadata vector reserve. |
| inputs / outputs | Element count and optional existing work grant. |
| invariants | Charges count*ceil(sizeof(T)/sizeof(void*)); this is work metadata, not allocator bytes or a reserve call. Null grant returns immediately. |
| ownership | Owns no vector/capacity; the caller later reserves under its existing account. |
| failure | Width/product overflow or work denial propagates before reserve. |
| cost | Constant arithmetic and one admission; actual reserve/move/allocation cost is separate. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0010

[Lines 51–52](../../../../../src/storage/accounted_plan.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/accounted_plan.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/accounted_plan.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/accounted_plan.cpp\` at its lexical source position in src/storage/accounted_plan.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/accounted_plan.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 53–70](../../../../../src/storage/accounted_plan.cpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedPlanStorage::Metadata
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable storage program shared by bindings and table generations. |
| inputs / outputs | Account/owner/route/spec initialize identity, canonical layout handles, relation records and index bindings. |
| invariants | Arrays use immutable_metadata purpose/tag(owner). identity stores exactly64 bytes without a terminator. collision_profile is private test state. |
| ownership | Retains the same account, owns accounted vectors and projection/layout shared handles; no PhysicalPlan or mutable table graph retained. |
| failure | Constructor/member allocation failures unwind unpublished ownership; final destruction releases vectors and referenced metadata. |
| cost | Fixed empty initialization; populated storage scales with layouts/relations/indexes and unique layout/projection backing. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp) |

## B0013

[Lines 72–110](../../../../../src/storage/accounted_plan.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::Binding AccountedPlanStorage::freeze_native_binding(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze numeric storage bindings while sharing already funded same-account canonical tokens. |
| inputs / outputs | Existing account, route, lowercase64-hex identity, backend guarantee, native layouts/relations/projections, optional spec and grant/mode; returns immutable Binding. |
| invariants | Checks valid route/backend spelling, layout IDs/context/account identity, relation roles/layout bounds, and exact projection endpoint tokens/source relation layout. This is not complete physical-plan/tree revalidation. |
| ownership | Allocates one funded Metadata plus reserved binding arrays; copied layout/projection handles retain their original controls under the same account. Input spans are no longer needed on return. |
| failure | Validation/work/account/allocation/ID failure destroys private data. Earlier grant work and owner IDs remain consumed; no live table is touched. |
| cost | O(64+L+R+I) explicit checks and handle copies, three array reserves plus Metadata control; no payload freezing, row traversal or legacy plan mirror. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0015

[Lines 112–141](../../../../../src/storage/accounted_plan.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::Binding AccountedPlanStorage::clone_binding(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a valid immutable binding into the receiving account. |
| inputs / outputs | Receiver account, source Binding and optional execution grant; returns independently owned binding. |
| invariants | Preserves identity/route/spec/numeric bindings and projection alias equivalence; uses fresh layout/projection tokens even if receiver equals source account. |
| ownership | New owner tags all cloned metadata; source retains its original account/state. Only the immutable output is published after complete construction. |
| failure | Empty source, missing/invalid indexed grant, work/account/allocation/owner failure propagates with local cleanup; source unchanged. |
| cost | Cold O(L + R + I^2) outer work plus copied descriptor/binding bytes and layout/projection validation (including temporary O(F log F) repeated-variable maps); prior-index token scan preserves sharing without a retained lookup map. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0017

[Lines 143–228](../../../../../src/storage/accounted_plan.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::AccountedPlanStorage(const resource::MemoryAccount& account, const Inputs& input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import borrowed physical metadata and optionally materialize its empty native storage instances. |
| inputs / outputs | Existing account, private Inputs, caller grant, materialize flag and mode. |
| invariants | Execution-only materialization; validated route/backend/hex identity and sequential IDs; every borrowed layout/projection is resolved by exact source token. Registry is destroyed before metadata_ publication. |
| ownership | Fresh instance owner funds table/index arrays; separate metadata owner funds native layouts/relations/projections and temporary token registry. No legacy plan survives. |
| failure | All throwing work precedes final metadata_ publication; automatic cleanup destroys partial arrays/tables/indexes. Already consumed work, IDs and successful allocation history are not refunded. |
| cost | Cold import has O(L^2) registry scans and O(I^2) projection alias scans plus layout fields/binding bytes and projection validation; materialization adds all empty tables/indexes. Source rows are not scanned. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0019

[Lines 230–235](../../../../../src/storage/accounted_plan.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* supplied)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve normal immutable-plan cap validation while sharing empty table/index materialization. |
| inputs / outputs | The ordinary constructor still selects \`operation_work(metadata().indexed,supplied)\` then calls the shared materializer. |
| invariants | Public execution continues to reject work beyond immutable per_operation; only the private ColdRebuild constructor accepts its separate fixed diagnostic grant. |
| ownership | The unpublished storage generation owns its new tables/indexes and shares the immutable binding; the allowance is borrowed only during construction. |
| failure | Any normal cap, work, account, table or index failure destroys only unpublished storage. |
| cost | The original loops are moved into \`materialize\`; the ordinary admission call and work behavior stay intact. |
| Design | [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../memory_accounts.md) |

## B0020

[Lines 236–245](../../../../../src/storage/accounted_plan.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* work,ColdRebuild)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit the friend-only cold constructor to materialize under the one cold fixed grant. |
| inputs / outputs | A genuine Binding and active IndexWorkAllowance plus private ColdRebuild tag -&gt; empty tables/indexes through shared materialize. |
| invariants | Grant pointer must match authentic indexed backend and use fixed diagnostics; normal plan.per_operation check remains untouched for public constructor. |
| ownership | Grant is borrowed; resulting tables/metadata do not retain it. |
| failure | Contract/work/account/table/index failure destroys unpublished storage. |
| cost | One selected cold grant pays materialization; no plan option or maximum is rewritten. |
| Design | [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [docs/memory_accounts.md §Native accounted dispatch](../../../../memory_accounts.md) |

## B0021

[Lines 246–261](../../../../../src/storage/accounted_plan.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedPlanStorage::materialize(IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize empty per-relation tables and required indexes from immutable metadata. |
| inputs / outputs | Metadata relations/layouts/index requirements -&gt; reserved table/index vectors and native empty structures. |
| invariants | Uses original ordered/indexed backend and per-table limits; test-only collision hook remains guarded; no rows are copied. |
| ownership | Storage owns only newly made tables/indexes and shared immutable metadata; the work pointer is borrowed during the loop. |
| failure | Any step, allocation or add_index error prevents object publication. |
| cost | Prepares/reserves two arrays, then relation and index passes; complexity is selected by plan relations/indexes and actual index work, not CPU. |
| Design | [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../memory_accounts.md) |

## B0023

[Lines 263–266](../../../../../src/storage/accounted_plan.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedPlanStorage::Metadata& AccountedPlanStorage::Binding::metadata() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a nonempty immutable binding before borrowing its state. |
| inputs / outputs | No arguments; returns const Metadata reference. |
| invariants | Empty/default/moved handle never dereferences null. |
| ownership | Reference borrows this binding or another retaining metadata owner. |
| failure | Empty throws fixed invalid_storage. |
| cost | One pointer test and dereference, no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0024

[Lines 267–267](../../../../../src/storage/accounted_plan.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& AccountedPlanStorage::Binding::account() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the account that funded this immutable binding. |
| inputs / outputs | Returns metadata().account. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Reference requires a live retaining metadata owner; does not create another cap. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0025

[Lines 268–268](../../../../../src/storage/accounted_plan.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const AccountedLayout> AccountedPlanStorage::Binding::layouts() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow all canonical native layout handles. |
| inputs / outputs | Returns the immutable layouts span. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Span and elements borrow retained metadata; copied layout handles can independently retain their controls. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0026

[Lines 269–272](../../../../../src/storage/accounted_plan.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedPlanStorage::Binding::layout(LayoutId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a binding-local layout ID. |
| inputs / outputs | LayoutId array offset in; const AccountedLayout reference out. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Reference borrows immutable metadata. |
| failure | Empty throws invalid_storage; out-of-range throws layout_mismatch. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0027

[Lines 273–276](../../../../../src/storage/accounted_plan.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedProjection& AccountedPlanStorage::Binding::projection(IndexRequirementId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a frozen index requirement to its canonical projection. |
| inputs / outputs | IndexRequirementId array offset in; projection reference out. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Reference borrows the immutable index-binding array. |
| failure | Empty throws invalid_storage; out-of-range throws unknown_index. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0028

[Lines 277–277](../../../../../src/storage/accounted_plan.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRoute AccountedPlanStorage::Binding::route() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the frozen physical route. |
| inputs / outputs | Returns copied tree/constant_true/constant_false tag. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Scalar result owns no graph. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0029

[Lines 278–280](../../../../../src/storage/accounted_plan.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view AccountedPlanStorage::Binding::physical_identity() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact64-byte physical binding digest. |
| inputs / outputs | Returns view over Metadata identity array, without NUL-termination promise. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | View borrows retained immutable metadata. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0030

[Lines 281–281](../../../../../src/storage/accounted_plan.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedPlanStorage::Binding::relation_count() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable number of relation bindings. |
| inputs / outputs | Returns relations.size(), including metadata-only bindings. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Scalar result owns nothing. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0031

[Lines 282–282](../../../../../src/storage/accounted_plan.cpp#L282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedPlanStorage::Binding::index_count() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable number of index requirements. |
| inputs / outputs | Returns indexes.size(), not the number of live keys/members. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Scalar result owns nothing. |
| failure | Empty binding throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, hash, table scan or grant admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0032

[Lines 283–283](../../../../../src/storage/accounted_plan.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::Binding AccountedPlanStorage::binding() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share immutable storage authority without retaining mutable table instances. |
| inputs / outputs | Returns a Binding with the exact metadata_ shared owner. |
| invariants | Read-only immutable metadata access; no planner validation or state mutation occurs. |
| ownership | Returned Binding owns metadata and survives facade destruction. |
| failure | Empty facade throws invalid_storage; shared_ptr copy allocates no new control. |
| cost | Constant guard and shared reference increment, no descriptor clone. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0034

[Lines 285–287](../../../../../src/storage/accounted_plan.cpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage::AccountedPlanStorage(std::shared_ptr<const Metadata> metadata, StorageOwnerId owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt completely prepared immutable metadata and mutable storage arrays. |
| inputs / outputs | Private constructor moves metadata, fresh instance owner and accounted table/index vectors. |
| invariants | Caller has prepared a complete consistent snapshot; this constructor does not validate or allocate. |
| ownership | Transfers vector allocations with their original allocator/account and shares metadata. |
| failure | Noexcept moves under valid private preparation; no rollback code. |
| cost | Fixed vector/shared-owner moves; final old owner cleanup is handled outside this constructor. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0035

[Lines 288–291](../../../../../src/storage/accounted_plan.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage& AccountedPlanStorage::operator=(AccountedPlanStorage&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a facade by transferring all source ownership including nonpropagating allocator state. |
| inputs / outputs | Rvalue facade in; returns *this. |
| invariants | Self-move is a no-op. Destroy/reconstruct transfers complete vectors and metadata rather than cross-account vector element assignment. |
| ownership | Releases old state, then adopts source metadata/tables/indexes/owner; source becomes guarded moved-from state. |
| failure | Noexcept under member destructors/move constructors; private corruption during destruction can terminate. |
| cost | Constant transfers plus possible O(old tables/rows/index metadata) final destruction; no new allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0036

[Lines 292–295](../../../../../src/storage/accounted_plan.cpp#L292); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedPlanStorage::Metadata& AccountedPlanStorage::metadata() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard every facade metadata access against moved-from state. |
| inputs / outputs | Returns const Metadata reference. |
| invariants | metadata_ must be nonempty; no implicit empty replacement is created. |
| ownership | Reference borrows facade/shared binding owner. |
| failure | Empty throws fixed invalid_storage. |
| cost | One pointer test/dereference. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0037

[Lines 296–296](../../../../../src/storage/accounted_plan.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId AccountedPlanStorage::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the mutable instance identity. |
| inputs / outputs | Returns owner_, distinct from the shared metadata owner. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar result does not retain storage. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0038

[Lines 297–297](../../../../../src/storage/accounted_plan.cpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageBackend AccountedPlanStorage::backend() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the established backend selection. |
| inputs / outputs | Returns indexed_chained_v1 iff immutable indexed specification exists. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar result owns no backend instance. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0039

[Lines 298–298](../../../../../src/storage/accounted_plan.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRoute AccountedPlanStorage::route() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the established physical route. |
| inputs / outputs | Returns copied immutable route tag. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar value owns nothing. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0040

[Lines 299–299](../../../../../src/storage/accounted_plan.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view AccountedPlanStorage::physical_identity() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the frozen physical digest from a live facade. |
| inputs / outputs | Returns view of exact64-byte identity array. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | View needs a live metadata owner; no terminating NUL is guaranteed. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0041

[Lines 300–300](../../../../../src/storage/accounted_plan.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const AccountedLayout> AccountedPlanStorage::layouts() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the canonical layout array. |
| inputs / outputs | Returns immutable Metadata layouts span. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Span/reference lifetime follows shared metadata, not a newly allocated export. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0042

[Lines 301–304](../../../../../src/storage/accounted_plan.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedPlanStorage::layout(LayoutId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a layout from the immutable array. |
| inputs / outputs | LayoutId offset in; const native layout reference out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Borrowed metadata element. |
| failure | Empty throws invalid_storage; bad layout ID throws layout_mismatch. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0043

[Lines 305–308](../../../../../src/storage/accounted_plan.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedPlanStorage::RelationBinding& AccountedPlanStorage::relation(RelationId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the frozen role/layout/origin of a relation. |
| inputs / outputs | RelationId offset in; const RelationBinding reference out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Borrowed immutable metadata element. |
| failure | Empty or out-of-range relation throws invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0044

[Lines 309–312](../../../../../src/storage/accounted_plan.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedProjection& AccountedPlanStorage::projection(IndexRequirementId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a compiled index requirement to its canonical projection. |
| inputs / outputs | IndexRequirementId offset in; const projection reference out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Borrowed immutable metadata element. |
| failure | Empty throws invalid_storage; bad requirement throws unknown_index. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0045

[Lines 313–316](../../../../../src/storage/accounted_plan.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable& AccountedPlanStorage::table(RelationId id) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one mutable native relation table for accounted operations. |
| inputs / outputs | RelationId offset in; mutable AccountedStorageTable reference out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Reference requires this instance to remain unmoved/alive; table methods enforce their own journals, limits and work contracts. |
| failure | Empty or out-of-range relation throws invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0046

[Lines 317–320](../../../../../src/storage/accounted_plan.cpp#L317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedStorageTable& AccountedPlanStorage::table(RelationId id) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one native relation table read-only. |
| inputs / outputs | RelationId offset in; const table reference out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Reference borrows the mutable generation, not merely its immutable Binding. |
| failure | Empty or out-of-range relation throws invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0047

[Lines 321–324](../../../../../src/storage/accounted_plan.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId AccountedPlanStorage::index(IndexRequirementId id) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a compiled requirement to this generation's table-local registered index ID. |
| inputs / outputs | Requirement offset in; copied IndexId out. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar ID carries no owning table lifetime; use its matching relation/table. |
| failure | Empty throws invalid_storage; out-of-range requirement throws unknown_index. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0048

[Lines 325–325](../../../../../src/storage/accounted_plan.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedPlanStorage::relation_count() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this generation's materialized relation-table count. |
| inputs / outputs | Returns tables_.size(), not Metadata relation_count for metadata-only imports. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar result owns nothing. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0049

[Lines 326–326](../../../../../src/storage/accounted_plan.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedPlanStorage::index_count() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this generation's registered index binding count. |
| inputs / outputs | Returns indexes_.size(), not key or member population. |
| invariants | Requires nonempty facade; direct current-instance or immutable-metadata access does not copy or validate the full state. |
| ownership | Scalar result owns nothing. |
| failure | Empty facade throws fixed invalid_storage. |
| cost | Constant checked access; no allocation, row traversal or work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0050

[Lines 327–337](../../../../../src/storage/accounted_plan.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanStorageMemoryStatistics AccountedPlanStorage::memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report current allocation usage for the two established physical storage owners. |
| inputs / outputs | Returns descriptor counts plus statistics_for(metadata owner), statistics_for(instance owner), and checked sum of their current usages. |
| invariants | owned is deliberately scoped: it omits table payload owners and any shared layout/projection backing attributed to another owner. Shared metadata is not multiplied by number of tables. |
| ownership | Copied report has no live pointers or retained account allocation. It does not allocate an owner registry or full state snapshot. |
| failure | Empty facade or checked aggregate overflow propagates; no state mutation. |
| cost | Two O(A) scans over all current account allocation blocks via statistics_for; O(1) scalar totals/result. A is account-wide live allocations. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0051

[Lines 338–350](../../../../../src/storage/accounted_plan.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPlanStorage AccountedPlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit owning deep copy of the current mutable table state. |
| inputs / outputs | Optional execution grant; returns independent tables/index-ID arrays under fresh instance owner, sharing immutable Metadata. |
| invariants | Preserves same-account original limits/tokens; composed indexed copies reuse one supplied grant. No hidden grant or new account. It is an explicit bulk operation, not ordinary update rollback. |
| ownership | Private arrays own table snapshots; source unchanged. Returned copy shares metadata and owns independent table nodes/rows/arenas per backend snapshot semantics. |
| failure | Grant/account/allocation/owner or table snapshot failure unwinds private copies; source contents stay unchanged, consumed work remains spent. |
| cost | Visits/copies every table plus backend live rows/indexes/arena storage and index ID array; memory can overlap full source and copy and must fit original account. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp) |

## B0052

[Lines 351–366](../../../../../src/storage/accounted_plan.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedPlanStorage::check_invariants(IndexWorkAllowance* supplied) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic of metadata, table bindings and installed index tokens. |
| inputs / outputs | Optional execution grant; returns only if relation/index counts, layout IDs, backend/relation/layout/spec and projection token links agree. |
| invariants | Each index-binding probe uses the same chosen grant. Full layout/table scans and table.check_invariants() are diagnostic work not wholly charged by IndexWork; do not claim the grant bounds the complete diagnostic. |
| ownership | Borrows immutable metadata and table instances; no runtime state is replaced. Current table diagnostics scan existing structures without a full copied database; any underlying diagnostic failure propagates. |
| failure | Fixed contract/work errors or backend invariant diagnostics propagate; no generic catch, repair, retry or silent success. |
| cost | O(L+R+I) outer checks plus complete per-table diagnostics and indexed lookup costs. Explicitly outside ordinary point-update cost. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0053

[Lines 367–367](../../../../../src/storage/accounted_plan.cpp#L367); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L367-L367:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_plan.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
