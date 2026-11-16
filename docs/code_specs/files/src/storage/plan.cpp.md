# `src/storage/plan.cpp` — block usage map

[Source](../../../../../src/storage/plan.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `a94cf2381edd6e7c1aa312717003c65f06fc672410facec0ea7037f8b5fc047a`. 95 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/storage/plan.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/storage/plan.cpp#L9) | Callable definition: void require(bool value,const char* message) | calls Error; guard void require(bool value,const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 12–23](../../../../../src/storage/plan.cpp#L12) | Callable definition: IndexWorkAllowance* operation_work(const PhysicalPlan& plan,IndexWorkAllowance* work) | calls options, Error, remaining, require; guard require(left.structural_steps&lt;=cap.structural_steps && left.scalar_fields&lt;=cap.scalar_fields &&; returns nullptr; work; source comment (unverified): // Bound the current canonical remainder in every domain. A · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../src/storage/plan.cpp#L24) | Explanatory comments or spacing. | source comment (unverified): // Pointer-word admission is structural work, not actual allocator bytes. · [reviewed contract](#b0004) |
| [B0005 · 25–32](../../../../../src/storage/plan.cpp#L25) | Callable definition: template&lt;class T&gt; void prepare_vector(std::size_t count,IndexWorkAllowance* work) | calls max, Error, admit; source comment (unverified): // Pointer-word admission is structural work, not actual allocator bytes. · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../src/storage/plan.cpp#L33) | Callable definition: void step(IndexWorkAllowance* work) | calls admit · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../../src/storage/plan.cpp#L34) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 36–50](../../../../../src/storage/plan.cpp#L36) | Callable definition: PlanStorage::PlanStorage(PhysicalPlan plan,IndexWorkAllowance* supplied) : plan_(std::move(plan)) | calls plan_, std::move, route, operation_work; growth emplace_back, push_back, reserve; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 51–52](../../../../../src/storage/plan.cpp#L51) | Callable definition: PlanStorage::PlanStorage(PhysicalPlan plan,std::vector&lt;StorageTable&gt; tables,std::vector&lt;IndexId&gt; indexes) : plan_(std::move(plan)… | calls plan_, std::move, tables_, indexes_ · [reviewed contract](#b0009) |
| [B0010 · 53–55](../../../../../src/storage/plan.cpp#L53) | Callable definition: StorageBackend PlanStorage::backend() const | calls options; returns plan_.options().indexed_storage ? StorageBackend::indexed_chained_v1 : StorageBackend::reference_or… · [reviewed contract](#b0010) |
| [B0011 · 56–59](../../../../../src/storage/plan.cpp#L56) | Callable definition: StorageTable& PlanStorage::table(RelationId relation) | calls size, Error; returns tables_\[relation.value\] · [reviewed contract](#b0011) |
| [B0012 · 60–63](../../../../../src/storage/plan.cpp#L60) | Callable definition: const StorageTable& PlanStorage::table(RelationId relation) const | calls size, Error; returns tables_\[relation.value\] · [reviewed contract](#b0012) |
| [B0013 · 64–67](../../../../../src/storage/plan.cpp#L64) | Callable definition: IndexId PlanStorage::index(IndexRequirementId requirement) const | calls size, Error; returns indexes_\[requirement.value\] · [reviewed contract](#b0013) |
| [B0014 · 68–75](../../../../../src/storage/plan.cpp#L68) | Callable definition: PlanStorage PlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const | calls route, operation_work, size, reserve; returns {plan_,std::move(copies),std::move(indexes)}; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 76–94](../../../../../src/storage/plan.cpp#L76) | Callable definition: void PlanStorage::check_invariants(IndexWorkAllowance* supplied) const | calls operation_work, require, size, relations; guard require(tables_.size()==plan_.relations().size() && indexes_.size()==plan_.indexes().size(),; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 95–95](../../../../../src/storage/plan.cpp#L95) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0016) |

## B0001

[Lines 1–8](../../../../../src/storage/plan.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:eb2f5de90549f084e6749b3a9dc70ffae52dc073d61a6cdc50484518dd694896
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/plan.cpp: imports \`"crown/storage/plan.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;limits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 9–11](../../../../../src/storage/plan.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an internal standalone plan-storage contract without a recovery layer. |
| inputs / outputs | Returns when predicate is true; false throws Error(storage_contract,message). |
| invariants | Caller must run the required checks before publishing an incomplete returned owner; the helper does not mutate or repair state. |
| ownership | Message pointer is borrowed during Error construction; thrown Error owns its diagnostic text. |
| failure | Public Error formatting/allocation failure can propagate instead; no throw/catch conversion or retry is added. |
| cost | One branch on success; diagnostic string/exception construction occurs only on failure. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–23](../../../../../src/storage/plan.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance* operation_work(const PhysicalPlan& plan,IndexWorkAllowance* work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select and validate one aggregate indexed operation grant. |
| inputs / outputs | Reference plans return nullptr and ignore supplied work. Indexed plans require nonnull work, compare all five remaining domains to plan.per_operation, spend one structural step, and return the same pointer. |
| invariants | Checks current remaining work, not the grant's original construction limit. Comparisons are componentwise; default IndexWork lexicographic ordering is not used. No per-table/per-call reset is created. |
| ownership | Returned allowance pointer borrows the caller's root/alias. PlanStorage does not retain or refill it. |
| failure | Missing/excess remaining grant throws public storage_contract; exhaustion follows allowance diagnostic policy. No plan/table state changes here. |
| cost | Fixed option check, five-domain comparisons and one debit for indexed mode; no allocation or population traversal on success. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 24–24](../../../../../src/storage/plan.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:3eb43e3a2ddd6a5b360003a4aed518ec86735a9caccef13188a636048838029d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class T&gt; void prepare_vector(std::size_t count,IndexWorkAllowance* work)\`: Pointer-word admission is structural work, not actual allocator bytes. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/plan.cpp:L25; use that declaration for the actual input/output shape. |
| invariants | The source note states: Pointer-word admission is structural work, not actual allocator bytes. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Pointer-word admission is structural work, not actual allocator bytes. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 25–32](../../../../../src/storage/plan.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void prepare_vector(std::size_t count,IndexWorkAllowance* work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit pointer-word metadata units before vector construction/copy. |
| inputs / outputs | For nonnull work, computes ceil(sizeof(T)/sizeof(void*)) per requested element, checks uint64 multiplication, and debits pointer_slots; null work is a no-op. |
| invariants | These are structural reservation units for the full requested count, not actual allocator bytes, successful allocation or fresh grant. |
| ownership | Borrows an existing allowance; no vector, account owner or element lifetime is retained. |
| failure | Product overflow throws public storage_overflow before debit. Work denial propagates without allocating a vector; earlier work is not refunded. |
| cost | Fixed checked arithmetic and five-domain admission; actual reserve/copy and element moves happen later in caller and can allocate. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 33–33](../../../../../src/storage/plan.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step(IndexWorkAllowance* work) { if (work) work->admit(IndexWork{.structural_steps=1}); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one indexed structural traversal step when work is present. |
| inputs / outputs | Calls work-&gt;admit({structural_steps=1}) only for a nonnull borrowed allowance. |
| invariants | Reference path remains a no-op; it never creates an implicit unlimited allowance or per-iteration grant. |
| ownership | Only the borrowed canonical balance is mutated. |
| failure | Exhaustion propagates under the selected diagnostic policy; no state rollback/refund is attempted by this helper. |
| cost | Fixed null check and optional fixed-dimensional debit; no allocations or scalar scans. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 34–35](../../../../../src/storage/plan.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/plan.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/plan.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/plan.cpp\` at its lexical source position in src/storage/plan.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/plan.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 36–50](../../../../../src/storage/plan.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanStorage::PlanStorage(PhysicalPlan plan,IndexWorkAllowance* supplied) : plan_(std::move(plan)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Instantiate empty concrete backend storage under one checked operation grant. |
| inputs / outputs | Checks plan presence, selects operation_work, pre-admits both metadata vectors, constructs tables according to indexed options, then registers compiled indexes. |
| invariants | Every indexed table sees the same borrowed balance and immutable per_table limits; option choice is not revised after partial construction. Plan relation/index mapping is exact. |
| ownership | Owns ordinary table/index vectors and concrete backend owners, sharing PhysicalPlan metadata. It does not create a query MemoryAccount or retain supplied allowance lifetime. |
| failure | Plan/grant/cap/identity/allocation failures destroy partial private construction through RAII. Already consumed work stays consumed; no partial owner is returned. |
| cost | Visits all relations/index requirements, allocates ordinary container/control/empty-index metadata, and charges structural/pointer units. Per-table grants are never multiplied from the maximum. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 51–52](../../../../../src/storage/plan.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanStorage::PlanStorage(PhysicalPlan plan,std::vector<StorageTable> tables,std::vector<IndexId> indexes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a complete backend-matching snapshot with existing owners. |
| inputs / outputs | Private constructor moves PhysicalPlan, StorageTable vector and requirement-to-index vector into members. |
| invariants | The snapshot caller has completed binding, ID preservation and grant admission; this body does not repeat scans or validation. |
| ownership | Transfers prepared vectors/plan handles and their concrete owners; no borrowed input vector is retained. |
| failure | Only noexcept concrete moves occur in the body; by-value parameter construction may fail before entry when callers copy. |
| cost | Fixed body moves without row copy or new grant. Complete snapshot rebuilding and index-vector copying remain explicit caller costs. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 53–55](../../../../../src/storage/plan.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageBackend PlanStorage::backend() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the backend bound into this immutable physical plan. |
| inputs / outputs | Returns indexed_chained_v1 when indexed_storage is present, otherwise reference_ordered_v1. |
| invariants | Option presence identifies actual construction selection; it does not inspect table populations or certify allocator-byte accounting. |
| ownership | Returns an inline enum; retained plan metadata remains owned by this storage object. |
| failure | Invalid/moved plan options access propagates its existing failure; there is no fallback backend on error. |
| cost | Fixed option lookup and enum selection on a valid plan, without table traversal or allocation. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 56–59](../../../../../src/storage/plan.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable& PlanStorage::table(RelationId relation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a mutable backend table by dense plan-local relation ID. |
| inputs / outputs | Checks relation.value against tables_.size(), then returns the selected table reference. |
| invariants | RelationId is plan-local and is not itself a storage-owner token, payload pin or query-epoch authority. |
| ownership | Returned reference borrows the exact table object in vector storage. Vector moves transfer ownership without relocating its elements; releasing/replacing that storage invalidates the borrow. |
| failure | Out-of-range ID throws public Error(unknown_relation); no fallback table is allocated. |
| cost | Fixed bounds check and direct vector lookup on success; only failure formats an owning diagnostic. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 60–63](../../../../../src/storage/plan.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const StorageTable& PlanStorage::table(RelationId relation) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a const backend table by dense plan-local relation ID. |
| inputs / outputs | Checks relation.value against tables_.size(), then returns the selected table reference. |
| invariants | RelationId is plan-local and is not itself a storage-owner token, payload pin or query-epoch authority. |
| ownership | Returned reference borrows the exact table object in vector storage. Vector moves transfer ownership without relocating its elements; releasing/replacing that storage invalidates the borrow. |
| failure | Out-of-range ID throws public Error(unknown_relation); no fallback table is allocated. |
| cost | Fixed bounds check and direct vector lookup on success; only failure formats an owning diagnostic. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 64–67](../../../../../src/storage/plan.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId PlanStorage::index(IndexRequirementId requirement) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a dense compiled index-requirement ID without an index lookup. |
| inputs / outputs | Checks requirement.value against indexes_.size() and returns the stored concrete IndexId. |
| invariants | This mapping comes from checked construction/copy; the ID does not retain index/table lifetime or authorize foreign-owner use. |
| ownership | Returns an inline IndexId, not a payload or table owner. |
| failure | Out-of-range requirement throws public Error(unknown_index); no search, recovery or alternate index is attempted. |
| cost | Fixed bounds check and vector read; no hash/tree lookup, native grant or allocation on success. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 68–75](../../../../../src/storage/plan.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanStorage PlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an independent complete backend snapshot using the same finite grant. |
| inputs / outputs | Checks plan, validates current aggregate allowance, pre-admits vectors, copies each concrete table, copies index mappings and adopts the completed result. |
| invariants | Each indexed copy borrows the same operation balance. Logical IDs/counters/order are preserved but backend/arena owners are new; active table journals reject copy. |
| ownership | Shares immutable PhysicalPlan and owns new ordinary vectors/concrete tables. Standalone public Tuple copies follow their legacy-deep/native-shared representation. |
| failure | Any work/cap/identity/allocation failure discards partial destination without changing source logical state. Consumed work is not refunded. |
| cost | Visits/copies live rows/indexes/memberships, rebuilds concrete directories and copies dense mappings; peak includes both full owners and copy scratch. No sparse logical-ID scan or O(1) clone is claimed. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 76–94](../../../../../src/storage/plan.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PlanStorage::check_invariants(IndexWorkAllowance* supplied) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Diagnose actual backend/limits/layout/projection bindings under explicit probe work. |
| inputs / outputs | Selects operation_work, checks storage shape and backend guarantee spelling, checks relation/backend/token/limits, runs concrete full diagnostics, then resolves compiled index projection bindings. |
| invariants | Diagnostic table scans are separate from operational admission; indexed projection lookup still debits the same finite caller grant. No unbounded replacement allowance is created. |
| ownership | Borrows current plan/tables and supplied balance; concrete diagnostic scratch can allocate ordinary storage. No new result owner or repair state is retained. |
| failure | Invalid shape/binding/cap/grant or concrete invariant/allocation failures propagate; this function does not roll back, retry or publish an epoch. |
| cost | Plan-size validation loops plus concrete potentially allocating/high-water/quadratic invariant scans and admitted index probes. Passing a finite grant is not a total diagnostic CPU/byte cap. |
| Design | [src/storage/plan.cpp](../../../../../src/storage/plan.cpp), [include/crown/storage/plan.hpp](../../../../../include/crown/storage/plan.hpp), [src/storage/table.cpp](../../../../../src/storage/table.cpp), [tests/unit/physical_backend_plan_test.cpp](../../../../../tests/unit/physical_backend_plan_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 95–95](../../../../../src/storage/plan.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L95:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/plan.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
