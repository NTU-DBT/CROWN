# `src/runtime/owner_statistics.cpp` — block usage map

[Source](../../../../../src/runtime/owner_statistics.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture selected table/index distributions with owner/sequence stamps and partial-completion status.

Snapshot SHA-256: `96e1ae6c02bd731ced6edacc298e5c067cb03650a877d91b0fb6d71a8ab88345`. 79 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/runtime/owner_statistics.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–8](../../../../../src/runtime/owner_statistics.cpp#L6) | Callable definition: CapturedSelection::CapturedSelection(const Selection& source,const resource::MemoryAccount& account):scope(source.scope) | calls scope, emplace, begin, end; growth emplace · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../src/runtime/owner_statistics.cpp#L9) | Explanatory comments or spacing. | source comment (unverified): // Stamp freshness excludes configuration/interval, completeness and storage revision. · [reviewed contract](#b0003) |
| [B0004 · 10–16](../../../../../src/runtime/owner_statistics.cpp#L10) | Callable definition: Freshness compare_freshness(const OwnerStamp& old,const OwnerStamp& now,std::uint64_t lag) | calls ; returns Freshness::foreign_owner; Freshness::scope_mismatch; source comment (unverified): // Stamp freshness excludes configuration/interval, completeness and storage revision. · [reviewed contract](#b0004) |
| [B0005 · 17–18](../../../../../src/runtime/owner_statistics.cpp#L17) | declares namespace scope. |  · [reviewed contract](#b0005) |
| [B0006 · 19–23](../../../../../src/runtime/owner_statistics.cpp#L19) | Callable definition: std::uint64_t product(std::size_t count,std::size_t width) | calls max; returns static_cast&lt;std::uint64_t&gt;(count)*static_cast&lt;std::uint64_t&gt;(width) · [reviewed contract](#b0006) |
| [B0007 · 24–26](../../../../../src/runtime/owner_statistics.cpp#L24) | Closes surrounding scope/type. | source comment (unverified): // The request span is borrowed for this synchronous capture; returned selections · [reviewed contract](#b0007) |
| [B0008 · 27–38](../../../../../src/runtime/owner_statistics.cpp#L27) | Callable definition: OwnerBuilder::OwnerBuilder(OwnerStamp stamp,const CompiledProgram& plan,OwnerRequestView request,Limits limits,bool pending) :req… | calls request_, budget_, size, Error; growth reserve; 1 loop sites; source comment (unverified): // The request span is borrowed for this synchronous capture; returned selections · [reviewed contract](#b0008) |
| [B0009 · 39–39](../../../../../src/runtime/owner_statistics.cpp#L39) | Callable definition: bool OwnerBuilder::active() const noexcept | calls ; returns output_.availability_==Availability::available · [reviewed contract](#b0009) |
| [B0010 · 40–48](../../../../../src/runtime/owner_statistics.cpp#L40) | Callable definition: Component* OwnerBuilder::append(const Selection& selection) | calls active, work, size, bytes; returns nullptr; &output_.components_.back(); growth push_back · [reviewed contract](#b0010) |
| [B0011 · 49–58](../../../../../src/runtime/owner_statistics.cpp#L49) | Callable definition: void OwnerBuilder::table(Component& component,const storage::AccountedStorageTable& table, const storage::TupleLayout& legacy_lay… | calls size, owner, relation, revision · [reviewed contract](#b0011) |
| [B0012 · 59–70](../../../../../src/runtime/owner_statistics.cpp#L59) | Callable definition: void OwnerBuilder::index(Component& component,const storage::AccountedStorageTable& table,IndexId id, const storage::Projection& … | calls detail::native_index, account, key_count, target · [reviewed contract](#b0012) |
| [B0013 · 71–77](../../../../../src/runtime/owner_statistics.cpp#L71) | Callable definition: OwnerCapture OwnerBuilder::finish() | calls usage, std::move; returns std::move(output_); 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 78–79](../../../../../src/runtime/owner_statistics.cpp#L78) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |

## B0001

[Lines 1–5](../../../../../src/runtime/owner_statistics.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:dbbd935b40c284259ac8b2b188b4542160a21bf83490ae0cafe70db319571e03
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/owner_statistics.cpp: imports \`"owner_statistics_detail.hpp"\`, \`"crown/api/error.hpp"\`, \`"crown/storage/accounted_table.hpp"\`, \`&lt;limits&gt;\` for compilation; opens namespace \`crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 6–8](../../../../../src/runtime/owner_statistics.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedSelection::CapturedSelection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an immutable account-funded copy of one requested population/projection. |
| inputs / outputs | Copies typed scope; if fields is engaged, constructs a funded ordered FieldId vector even for an explicit empty projection. |
| invariants | nullopt means population's default/cardinality request; engaged empty means nullary projection and must not be collapsed to nullopt. |
| ownership | Scope is inline identity metadata; fields vector owns copied IDs using capture allocator on the original account. Caller request span/DTO may expire afterward. |
| failure | Field-vector actual allocation failures propagate; no layout/ID validation or catch is hidden in this copying constructor. |
| cost | O(field count) ID copying plus vector capacity allocation; empty/default scope copying is fixed. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 9–9](../../../../../src/runtime/owner_statistics.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:5a90bbafbfef705d7537cbd1bfeccc8a82f639ee0050d90d2b1148953c31fa5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`Freshness compare_freshness(const OwnerStamp& old,const OwnerStamp& now,std::uint64_t lag)\`: Stamp freshness excludes configuration/interval, completeness and storage revision. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/owner_statistics.cpp:L10; use that declaration for the actual input/output shape. |
| invariants | The source note states: Stamp freshness excludes configuration/interval, completeness and storage revision. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 10–16](../../../../../src/runtime/owner_statistics.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Freshness compare_freshness(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual owner/layer/committed-sequence stamps with an explicit maximum lag. |
| inputs / outputs | Checks foreign owner, scope mismatch, future sequence, equality, then safely subtracts older sequence to choose within_lag/stale. |
| invariants | This does not check mode/configuration/interval, plan/source binding, capture completeness or storage revision. A current incomplete/pending capture is still incomplete. |
| ownership | Only inline stamps and result; no runtime pointer/row/account retained. |
| failure | Valid enum/stamp comparisons add no throwing operation or catch. |
| cost | Fixed comparisons and guarded subtraction; no capture, row scan or allocation. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 17–18](../../../../../src/runtime/owner_statistics.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:15942a1ef98533a5f8c95849cbc0497e0f8e16726f6d0ccecc350e4a6e610c01
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/owner_statistics.cpp: opens namespace \`detail\`; opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0006

[Lines 19–23](../../../../../src/runtime/owner_statistics.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t product(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check component/requested-field logical payload multiplication. |
| inputs / outputs | Verifies count*positive sizeof width in host-size and uint64 domains before returning uint64 bytes. |
| invariants | All private callers pass nonzero type sizes; this helper is not defined for width==0. Modeled bytes differ from actual allocator framing/capacity. |
| ownership | Inline arguments/result only. |
| failure | Overflow throws fixed Exhausted, preserving prior capture usage. |
| cost | Fixed arithmetic, no copying of the represented payload. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 24–26](../../../../../src/runtime/owner_statistics.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L26:sha256:39478d56b826032d066574911b2b0f793dd46a4eec73a9e0e15ff81165f5c45c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/owner_statistics.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/owner_statistics.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/owner_statistics.cpp\` at its lexical source position in src/runtime/owner_statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/owner_statistics.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 27–38](../../../../../src/runtime/owner_statistics.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerBuilder::OwnerBuilder(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start one owner-state request with one shared logical capture Budget. |
| inputs / outputs | Retains plan/owner stamp/limits/request count, rejects over 256 selections and oversized explicit field lists, then returns metadata-only if pending; otherwise precharges capture/component payload and reserves component vector. |
| invariants | Request shape validation precedes pending classification. Pending reads do not inspect tentative tables. Components share one sequential budget; this constructor creates no replacement query account or native work grant. |
| ownership | OwnerBuilder borrows request span only during capture; output retains immutable program/account and funded component vector. Metadata reservation uses original plan account. |
| failure | Invalid shape throws invalid_statistics_request. Only logical Exhausted becomes top-level budget_exhausted; real allocation/invalid-program failures propagate before publication. |
| cost | O(request count) shape/width-presence checks and O(request count) actual reserved component capacity; no row scan in this constructor. Logical sizeof payload differs from native allocations. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 39–39](../../../../../src/runtime/owner_statistics.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool OwnerBuilder::active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tell owner population loops whether component metadata can still be appended. |
| inputs / outputs | Returns output availability==available. |
| invariants | A prior component may itself be incomplete while later metadata still fits; finish aggregates component exhaustion. Pending/top-level metadata exhaustion is inactive. |
| ownership | Reads local output state only; no owner/cursor access. |
| failure | Noexcept scalar comparison. |
| cost | Fixed check with no allocation or row traversal. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 40–48](../../../../../src/runtime/owner_statistics.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Component* OwnerBuilder::append(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one owning requested-selection component while shared metadata budget remains. |
| inputs / outputs | Returns nullptr if inactive; otherwise charges one work plus explicit field-list work/payload, copies CapturedSelection and pushes a default available Component, returning its address. |
| invariants | Internal callers append at most once per request selection using the reserved request capacity. Returned pointer is used synchronously; it is not a stable external handle across arbitrary extra vector growth. |
| ownership | Component owns copied field IDs and later copied distributions; request DTO/span is borrowed during this call only. |
| failure | Only Exhausted marks top-level budget_exhausted and returns nullptr. Actual field/vector allocation failures propagate; already spent logical work remains consumed. |
| cost | O(field count) copy/charges plus actual vector/node capacity cost; no source population scan until table/index/weighted filling. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 49–58](../../../../../src/runtime/owner_statistics.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void OwnerBuilder::table(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach exact table metadata/cardinality and optionally capture an ordered native projection. |
| inputs / outputs | Records existing layout, table.size and storage invalidation stamp before optional projected scan; absent fields returns cardinality-only metadata. |
| invariants | Storage revision is cursor invalidation, distinct from committed owner freshness. Incomplete distribution may coexist with exact table cardinality; no new projection/layout is built. |
| ownership | Layout metadata is shared; captured distribution owns compact copies on original account. Table/cursor inputs are borrowed only for synchronous scan. |
| failure | Projected logical/storage-work exhaustion sets component budget_exhausted with unknown distribution facts; outer catch handles fixed Exhausted only. Invalid fields/real allocation/corruption failures propagate. |
| cost | Fixed metadata reads when no projection; otherwise native cursor scan, per-row copies, linear group comparisons and finish costs documented in native_projected_fields. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 59–70](../../../../../src/runtime/owner_statistics.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void OwnerBuilder::index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one admitted index degree distribution and its exact nonempty key cardinality. |
| inputs / outputs | Calls native_index then table.key_count under the same storage allowance; after both return records target layout, invalidation stamp, cardinality and moved distribution. |
| invariants | A failed final key_count cannot leave partially installed exact cardinality/distribution. Incomplete scan can still accompany cardinality if that final native read succeeds. |
| ownership | Shares existing projection-target layout; result owns copied keys/arrays and retains no native bucket cursor. |
| failure | Only IndexFailure whose code is storage_work_limit becomes component budget_exhausted/default incomplete distribution. Factory/key-count work exhaustion is covered; all other native faults/allocation errors propagate. |
| cost | Native distinct bucket traversal/copy/sort/histogram plus one key_count read and metadata moves; native work and actual memory remain separate from logical C01 budget. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 71–77](../../../../../src/runtime/owner_statistics.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerCapture OwnerBuilder::finish()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize owner-level availability and return the owning capture. |
| inputs / outputs | Copies final BudgetUsage; if top-level available, scans components for any budget_exhausted availability, then moves output. |
| invariants | Earlier exact components survive later exhaustion; requested_components retains original count even if metadata exhaustion prevented later entries. It does not upgrade incomplete distributions. |
| ownership | Result owns funded components/field lists/copied keys and immutable program/account; no request span is retained in the returned capture. |
| failure | No new handler or allocation in this final aggregation/move; prior failures already have their named disposition. |
| cost | O(returned components), at most requested count, plus owner moves; no rescan of table rows. |
| Design | [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 78–79](../../../../../src/runtime/owner_statistics.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L79:sha256:285577568ac35d60830cf925beb22babfffdf80c35bfd45a12e88fdba305694d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/owner_statistics.cpp: closes \`namespace detail\`, \`namespace crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
