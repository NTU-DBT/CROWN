# `src/storage/physical.cpp` — block usage map

[Source](../../../../../src/storage/physical.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `773c228f8b00d2e853ea3e23836a1e8715ddb1aef98e4f5e135c9bb7d5fec922`. 53 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/storage/physical.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–14](../../../../../src/storage/physical.cpp#L7) | Callable definition: ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan) : plan_(std::move(plan)) | calls plan_, std::move, options, Error; growth emplace_back, push_back, reserve; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 15–20](../../../../../src/storage/physical.cpp#L15) | Callable definition: ReferencePlanStorage& ReferencePlanStorage::operator=(ReferencePlanStorage&& other) noexcept | calls ; returns *this; source comment (unverified): // Replacing the destination may release complete old backend/arena · [reviewed contract](#b0003) |
| [B0004 · 21–22](../../../../../src/storage/physical.cpp#L21) | Callable definition: ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan,std::vector&lt;ReferenceTable&gt; tables,std::vector&lt;IndexId&gt; indexes) : p… | calls plan_, std::move, tables_, indexes_ · [reviewed contract](#b0004) |
| [B0005 · 23–28](../../../../../src/storage/physical.cpp#L23) | Callable definition: ReferencePlanStorage ReferencePlanStorage::snapshot_copy() const | calls route, reserve, size, push_back; returns {plan_,std::move(copies),indexes_}; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 29–32](../../../../../src/storage/physical.cpp#L29) | Callable definition: ReferenceTable& ReferencePlanStorage::table(RelationId relation) | calls size, Error; returns tables_\[relation.value\] · [reviewed contract](#b0006) |
| [B0007 · 33–36](../../../../../src/storage/physical.cpp#L33) | Callable definition: const ReferenceTable& ReferencePlanStorage::table(RelationId relation) const | calls size, Error; returns tables_\[relation.value\] · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../src/storage/physical.cpp#L37) | Callable definition: IndexId ReferencePlanStorage::index(IndexRequirementId requirement) const | calls size, Error; returns indexes_\[requirement.value\] · [reviewed contract](#b0008) |
| [B0009 · 41–52](../../../../../src/storage/physical.cpp#L41) | Callable definition: void ReferencePlanStorage::check_invariants() const | calls size, relations, indexes, Error; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../src/storage/physical.cpp#L53) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0010) |

## B0001

[Lines 1–6](../../../../../src/storage/physical.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:04b699b8607b0c746c89dcb6a63ee924c5c52358f6bf4a83b8912c88d7adc05d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/physical.cpp: imports \`"crown/storage/physical.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 7–14](../../../../../src/storage/physical.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan) : plan_(std::move(plan)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build empty ordered-only storage from an admitted immutable physical plan. |
| inputs / outputs | Adopts PhysicalPlan, rejects indexed options, reserves vectors, creates one ReferenceTable per relation and registers each compiled projection index. |
| invariants | Dense relation/requirement IDs and exact layouts/programs come from the checked plan; it is not a raw catalog/query-update API. |
| ownership | Shares plan metadata and owns ordinary table/index vectors and empty backend/arena controls. No native query-account byte guarantee is installed. |
| failure | Unsupported backend, invalid plan/ID, identity exhaustion or allocator failure destroys incomplete construction through member RAII; no partial owner escapes. |
| cost | Visits relations/index requirements and allocates ordinary metadata/control/index registration. Cost is plan size plus concrete empty-table/index setup, not a row population scan. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–20](../../../../../src/storage/physical.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferencePlanStorage& ReferencePlanStorage::operator=(ReferencePlanStorage&& other) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a reference plan-storage owner with a move while releasing prior state. |
| inputs / outputs | Self move does nothing; otherwise moves plan_, tables_ and indexes_ from source. |
| invariants | All incoming relation/index bindings remain those of the moved checked owner; moved-from source is not a second usable storage owner. |
| ownership | Transfers vectors/plan handles. Replaced table owners are released; external pins or active journals can defer some old State/payload destruction. |
| failure | The operation is noexcept with these concrete handle/vector moves; no new validation or catch is introduced. |
| cost | Moves are fixed handle transfers, plus actual destruction of destination's prior tables/indexes/arena metadata when last-owned. It is not universally O(1) cleanup. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–22](../../../../../src/storage/physical.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan,std::vector<ReferenceTable> tables,std::vector<IndexId> indexes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully prepared owning reference snapshot. |
| inputs / outputs | Private constructor moves PhysicalPlan and completed ReferenceTable/IndexId vectors into their members. |
| invariants | Caller already preserved exact plan binding, live IDs/counters and independent backend owners; this constructor does not repeat validation. |
| ownership | Adopts all provided owners without copying row payloads in its body; by-value argument preparation costs belong to caller. |
| failure | Only noexcept member moves occur in this body; earlier caller copy/allocation can fail before entry. |
| cost | Fixed body moves. Snapshot's separate IndexId vector copy and complete table rebuild occur outside this constructor and are not hidden here. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 23–28](../../../../../src/storage/physical.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferencePlanStorage ReferencePlanStorage::snapshot_copy() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy complete live ordered plan storage into fresh backend owners. |
| inputs / outputs | Validates plan presence through route(), reserves a new table vector, calls each ReferenceTable::snapshot_copy and copies requirement-to-index IDs. |
| invariants | Live logical IDs/high-water counters/revision remain bound to the same immutable plan; storage/arena identities are fresh. An active source journal is rejected by each table copy. |
| ownership | Shares plan metadata, owns fresh ordinary vectors/table/index structures. Legacy Tuple payloads deep-copy; native-backed public Tuple copies retain their immutable funded representation. |
| failure | Any validation/identity/allocation failure releases private partial copies and leaves source logical state intact. |
| cost | Visits all tables/live rows/index memberships and copies index-ID vector. It can allocate ordinary deep values/control and is an explicit full owning copy, not a lazy view. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 29–32](../../../../../src/storage/physical.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable& ReferencePlanStorage::table(RelationId relation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a mutable backend table by dense plan-local relation ID. |
| inputs / outputs | Checks relation.value against tables_.size(), then returns the selected table reference. |
| invariants | RelationId is plan-local and is not itself a storage-owner token, payload pin or query-epoch authority. |
| ownership | Returned reference borrows the exact table object in vector storage. Vector moves transfer ownership without relocating its elements; releasing/replacing that storage invalidates the borrow. |
| failure | Out-of-range ID throws public Error(unknown_relation); no fallback table is allocated. |
| cost | Fixed bounds check and direct vector lookup on success; only failure formats an owning diagnostic. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 33–36](../../../../../src/storage/physical.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ReferenceTable& ReferencePlanStorage::table(RelationId relation) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a const backend table by dense plan-local relation ID. |
| inputs / outputs | Checks relation.value against tables_.size(), then returns the selected table reference. |
| invariants | RelationId is plan-local and is not itself a storage-owner token, payload pin or query-epoch authority. |
| ownership | Returned reference borrows the exact table object in vector storage. Vector moves transfer ownership without relocating its elements; releasing/replacing that storage invalidates the borrow. |
| failure | Out-of-range ID throws public Error(unknown_relation); no fallback table is allocated. |
| cost | Fixed bounds check and direct vector lookup on success; only failure formats an owning diagnostic. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 37–40](../../../../../src/storage/physical.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId ReferencePlanStorage::index(IndexRequirementId requirement) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a dense compiled index-requirement ID without an index lookup. |
| inputs / outputs | Checks requirement.value against indexes_.size() and returns the stored concrete IndexId. |
| invariants | This mapping comes from checked construction/copy; the ID does not retain index/table lifetime or authorize foreign-owner use. |
| ownership | Returns an inline IndexId, not a payload or table owner. |
| failure | Out-of-range requirement throws public Error(unknown_index); no search, recovery or alternate index is attempted. |
| cost | Fixed bounds check and vector read; no hash/tree lookup, native grant or allocation on success. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 41–52](../../../../../src/storage/physical.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ReferencePlanStorage::check_invariants() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Diagnose reference plan/backend binding and concrete storage invariants. |
| inputs / outputs | Checks vector shape, relation identity/layout tokens, each ReferenceTable invariant and every compiled index Projection token. |
| invariants | It verifies exact retained plan binding, not query semantics/minimum-height proof or public epoch commit. It does not repair broken storage. |
| ownership | Borrows all current owners; concrete reference diagnostics may allocate temporary visited structures. |
| failure | Shape/token/index/owner inconsistencies and diagnostic allocation failures propagate through existing public errors. |
| cost | Plan-size loops plus concrete table/arena diagnostic scans (including high-water metadata and values), and ordered index lookups. No hot-path or constant-time bound is implied. |
| Design | [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 53–53](../../../../../src/storage/physical.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/physical.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
