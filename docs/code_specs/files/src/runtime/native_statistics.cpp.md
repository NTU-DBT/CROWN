# `src/runtime/native_statistics.cpp` — block usage map

[Source](../../../../../src/runtime/native_statistics.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Build bounded native distributions using borrowed compact rows and shared storage work.

Snapshot SHA-256: `80675f8a5f8621e48d0d3057a77132274fd4d220d37b98d34550de8727970d11`. 178 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/runtime/native_statistics.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–10](../../../../../src/runtime/native_statistics.cpp#L9) | Callable definition: CapturedKey::CapturedKey(const resource::MemoryAccount& account,storage::AccountedRow row) :account_(account),row_(std::move(row)) | calls account_, row_, std::move · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../src/runtime/native_statistics.cpp#L11) | Explanatory comments or spacing. | source comment (unverified): // Retained value copies deep-clone compact bytes on the source query account. · [reviewed contract](#b0003) |
| [B0004 · 12–13](../../../../../src/runtime/native_statistics.cpp#L12) | Callable definition: CapturedKey::CapturedKey(const CapturedKey& other) :account_(other.account_),row_(account_?other.row_.clone(account_):storage::Ac… | calls account_, row_, clone; growth clone; source comment (unverified): // Retained value copies deep-clone compact bytes on the source query account. · [reviewed contract](#b0004) |
| [B0005 · 14–16](../../../../../src/runtime/native_statistics.cpp#L14) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 17–19](../../../../../src/runtime/native_statistics.cpp#L17) | Callable definition: Groups groups_for(const resource::MemoryAccount& account) | calls Groups; returns Groups(resource::MemoryAllocator&lt;CapturedHeavyKey&gt;(account,resource::MemoryPurpose::scratch,detail:… · [reviewed contract](#b0006) |
| [B0007 · 20–24](../../../../../src/runtime/native_statistics.cpp#L20) | Callable definition: std::uint64_t payload_bytes(std::size_t count,std::size_t width) | calls max; returns static_cast&lt;std::uint64_t&gt;(count)*static_cast&lt;std::uint64_t&gt;(width) · [reviewed contract](#b0007) |
| [B0008 · 25–26](../../../../../src/runtime/native_statistics.cpp#L25) | Explanatory comments or spacing. | source comment (unverified): // The same charged scalar/unsigned-byte ordering as the standalone reference · [reviewed contract](#b0008) |
| [B0009 · 27–45](../../../../../src/runtime/native_statistics.cpp#L27) | Callable definition: int compare(storage::RowView a,storage::RowView b,Budget& budget) | calls std::min, size, work, index; returns a\[i\].index()&lt;b\[i\].index()?-1:1; left&lt;right?-1:1; 2 loop sites; source comment (unverified): // The same charged scalar/unsigned-byte ordering as the standalone reference · [reviewed contract](#b0009) |
| [B0010 · 46–46](../../../../../src/runtime/native_statistics.cpp#L46) | Explanatory comments or spacing. | source comment (unverified): // C01 logical DTO payload charges differ from real native allocation requests. · [reviewed contract](#b0010) |
| [B0011 · 47–54](../../../../../src/runtime/native_statistics.cpp#L47) | Callable definition: void account_value(const storage::ScalarView& value,Budget& budget) | calls work, bytes, size; source comment (unverified): // C01 logical DTO payload charges differ from real native allocation requests. · [reviewed contract](#b0011) |
| [B0012 · 55–59](../../../../../src/runtime/native_statistics.cpp#L55) | Callable definition: CapturedKey copy(storage::RowView values,Budget& budget,const resource::MemoryAccount& account) | calls cells, account_value, observe_capacities, size; returns {account,storage::AccountedRow::copy_of(account,values,detail::owner_capture_memory)}; growth copy_of; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 60–63](../../../../../src/runtime/native_statistics.cpp#L60) | Callable definition: void admit(Groups& groups,CapturedKey key,std::uint64_t count,Budget& budget) | calls key, bytes, push_back, std::move; growth push_back · [reviewed contract](#b0013) |
| [B0014 · 64–65](../../../../../src/runtime/native_statistics.cpp#L64) | Explanatory comments or spacing. | source comment (unverified): // Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative · [reviewed contract](#b0014) |
| [B0015 · 66–96](../../../../../src/runtime/native_statistics.cpp#L66) | Callable definition: void finish(CapturedDistribution& out,Groups& groups,Budget& budget,const resource::MemoryAccount& account) | calls sort, work, compare, view; returns a.count!=b.count?a.count&gt;b.count:compare(a.key.view(),b.key.view(),budget)&lt;0; a.first&lt;b.first; growth emplace_back, push_back, reserve; 2 loop sites; source comment (unverified): // Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative · [reviewed contract](#b0015) |
| [B0016 · 97–99](../../../../../src/runtime/native_statistics.cpp#L97) | Closes surrounding scope/type. | source comment (unverified): // Each row projection is copied before linear distinct-key lookup, including duplicates. · [reviewed contract](#b0016) |
| [B0017 · 100–128](../../../../../src/runtime/native_statistics.cpp#L100) | Callable definition: CapturedDistribution detail::native_projected_fields(const storage::AccountedStorageTable& table, std::span&lt;const FieldId&gt; fields… | calls result, live, work, bytes; returns result; 4 loop sites; source comment (unverified): // Each row projection is copied before linear distinct-key lookup, including duplicates. · [reviewed contract](#b0017) |
| [B0018 · 129–145](../../../../../src/runtime/native_statistics.cpp#L129) | Callable definition: CapturedDistribution detail::native_index(const storage::AccountedStorageTable& table,IndexId id, const storage::Projection& proj… | calls index_keys, result, work, bytes; returns result; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 146–147](../../../../../src/runtime/native_statistics.cpp#L146) | declares namespace scope. |  · [reviewed contract](#b0019) |
| [B0020 · 148–155](../../../../../src/runtime/native_statistics.cpp#L148) | Type/record definition: struct WeightedBuilder::Data |  · [reviewed contract](#b0020) |
| [B0021 · 156–159](../../../../../src/runtime/native_statistics.cpp#L156) | Callable definition: WeightedBuilder::WeightedBuilder(Budget& budget,const resource::MemoryAccount& account) | calls work, bytes; growth make_accounted_unique · [reviewed contract](#b0021) |
| [B0022 · 160–161](../../../../../src/runtime/native_statistics.cpp#L160) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owner maps supply distinct positive weighted keys; add does not deduplicate. · [reviewed contract](#b0022) |
| [B0023 · 162–170](../../../../../src/runtime/native_statistics.cpp#L162) | Callable definition: bool WeightedBuilder::add(storage::RowView key,std::uint64_t count) | calls Error, work, row, size; returns false; true; source comment (unverified): // Owner maps supply distinct positive weighted keys; add does not deduplicate. · [reviewed contract](#b0023) |
| [B0024 · 171–171](../../../../../src/runtime/native_statistics.cpp#L171) | Callable definition: void WeightedBuilder::stop() noexcept | calls  · [reviewed contract](#b0024) |
| [B0025 · 172–176](../../../../../src/runtime/native_statistics.cpp#L172) | Callable definition: CapturedDistribution WeightedBuilder::finish() | calls statistics::finish, std::move; returns std::move(d.output) · [reviewed contract](#b0025) |
| [B0026 · 177–178](../../../../../src/runtime/native_statistics.cpp#L177) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |

## B0001

[Lines 1–8](../../../../../src/runtime/native_statistics.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:e8fab16241e1022126983978d84e5884b8b4d1e3981ba051bb84a728980f2c02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/native_statistics.cpp: imports \`"crown/runtime/statistics.hpp"\`, \`"crown/api/error.hpp"\`, \`"crown/storage/accounted_table.hpp"\`, \`&lt;algorithm&gt;\`, \`&lt;list&gt;\`, \`&lt;limits&gt;\` for compilation; opens namespace \`crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 9–10](../../../../../src/runtime/native_statistics.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedKey::CapturedKey(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already funded compact row into an owning captured key. |
| inputs / outputs | Copies the supplied account handle and moves the AccountedRow. |
| invariants | Internal capture callers supply the same original account that funds the row; this constructor does not validate allocator identity or clone/rehome bytes. |
| ownership | row_ owns compact values and account_ records the account used for later deep copies. view() borrows this row, not the source table or runtime. |
| failure | Row/account moves add no explicit failure translation; prior row construction already paid allocation/admission. |
| cost | Fixed handle/owner transfer, no second row copy or field scan; releasing the key later releases its real row block. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 11–11](../../../../../src/runtime/native_statistics.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L11:sha256:0854fbe2aa2cc07d1b208c9e61fc2be1478e9e7196d14d2700da91dfb76c3a1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`CapturedKey::CapturedKey(const CapturedKey& other) :account_(other.account_),row_(account_?other.row_.clone(account_):storage::AccountedRow\`: Retained value copies deep-clone compact bytes on the source query account. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/native_statistics.cpp:L12; use that declaration for the actual input/output shape. |
| invariants | The source note states: Retained value copies deep-clone compact bytes on the source query account. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Retained value copies deep-clone compact bytes on the source query account. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 12–13](../../../../../src/runtime/native_statistics.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedKey::CapturedKey(const CapturedKey& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy retained capture values on their original query account. |
| inputs / outputs | Copies account_; a nonempty account clones other.row_ on that same account, otherwise initializes an empty row for the valid empty/unbound case. |
| invariants | Copying a key is independent ownership, not a borrowed view or cross-query rehome. Caller must preserve the valid account/row pairing established by native producers. |
| ownership | New compact block owns copied text/native cells; source remains valid and unchanged. Actual query allowance funds both old/new blocks while retained. |
| failure | Memory/overflow/allocation failures propagate before a copied key escapes; ordinary assignment uses private copy then move for its prior-value guarantee. |
| cost | Visits/copies field metadata and text bytes plus actual compact allocation/control; nonempty copy is not O(1) or allocation-free. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 14–16](../../../../../src/runtime/native_statistics.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Groups=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use an owning funded scratch list of distinct captured keys and their positive multiplicities. |
| inputs / outputs | Each CapturedHeavyKey owns a compact key and count; list nodes use the original-account scratch allocator. |
| invariants | Native projected scan explicitly deduplicates before admit; index and weighted callers already provide distinct keys. The list itself performs no deduplication or count validation. |
| ownership | Groups own key blocks and list nodes until moved to heavy output or scratch teardown; list sort relinks existing nodes. |
| failure | Node/key allocation failures propagate; RAII cleans the private graph. A sort comparator can throw bounded-work Exhausted. |
| cost | One actual node allocation per admitted key plus compact row blocks. List traversal and sort costs remain; no new index/cache is introduced. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 17–19](../../../../../src/runtime/native_statistics.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Groups groups_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty funded grouping scratch for one distribution. |
| inputs / outputs | Returns a list whose allocator is bound to account, scratch and owner_capture_memory. |
| invariants | It creates no distinct-key directory and does not reserve all later nodes. |
| ownership | List allocator retains original account; subsequent nodes/keys own actual requested bytes. |
| failure | Empty setup introduces no handler; later allocations retain their precise failure path. |
| cost | Fixed empty list/allocator setup, with actual per-node allocation paid later. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 20–24](../../../../../src/runtime/native_statistics.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t payload_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard a count-times-width logical payload product before narrowing/multiplying. |
| inputs / outputs | Returns uint64 count*width after checking both host-size and uint64 multiplication domains. |
| invariants | Private callers pass positive sizeof widths; width==0 is outside this helper contract because its guards divide by width. These are logical report charges, not allocator-size assertions. |
| ownership | Inline numeric inputs/output only. |
| failure | Oversized product throws fixed Exhausted; no dynamic error string or clamp. |
| cost | Two bounded division/comparison checks and multiplication, independent of payload byte copying. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 25–26](../../../../../src/runtime/native_statistics.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:29ac89f46d0e958dea70daa420fe4e906ca859eaa740c1176eb5aa1403ec5eb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`int compare(storage::RowView a,storage::RowView b,Budget& budget)\`: The same charged scalar/unsigned-byte ordering as the standalone reference scan, operating directly on compact native cells without a Row/string export. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/native_statistics.cpp:L27; use that declaration for the actual input/output shape. |
| invariants | The source note states: The same charged scalar/unsigned-byte ordering as the standalone reference scan, operating directly on compact native cells without a Row/string export. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: The same charged scalar/unsigned-byte ordering as the standalone reference scan, operating directly on compact native cells without a Row/string export. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0009

[Lines 27–45](../../../../../src/runtime/native_statistics.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int compare(storage::RowView a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply charged native row ordering without exporting owning scalar DTOs. |
| inputs / outputs | Compares each tag/value; strings use unsigned-byte lexicographic order and length, InlineDecimal comparisons get the named conservative 256-unit debit, final arity is charged. |
| invariants | Equality/order agree with compact key semantics; empty rows compare normally. Budget charges are abstract units for actual inspected fields/bytes, not clock/allocator measurements. |
| ownership | Borrows both rows and Budget for the call; string_view/InlineDecimal cells remain source-owned and are not copied into an ordinary Row. |
| failure | Budget Exhausted propagates to the distribution boundary; valid scalar views need no allocation or recovery. Source dangling views are a caller error. |
| cost | Short-circuit O(compared fields plus compared text-prefix bytes), bounded Decimal arithmetic and corresponding work debits; successful comparison allocates no row/string. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 46–46](../../../../../src/runtime/native_statistics.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:9badca88350d21b19fd850d561d69e4b05c7cbeac022fab9816015fce80db9f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void account_value(const storage::ScalarView& value,Budget& budget)\`: C01 logical DTO payload charges differ from real native allocation requests. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/native_statistics.cpp:L47; use that declaration for the actual input/output shape. |
| invariants | The source note states: C01 logical DTO payload charges differ from real native allocation requests. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: C01 logical DTO payload charges differ from real native allocation requests. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: C01 logical DTO payload charges differ from real native allocation requests. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 47–54](../../../../../src/runtime/native_statistics.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void account_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge one captured native scalar according to C01's named ordinary payload model. |
| inputs / outputs | Charges one work and sizeof(Value); text additionally charges length work and length+1 logical bytes; InlineDecimal adds 38 work/bytes. |
| invariants | The model intentionally names Value/Decimal report payload, not native cell/block/control sizes. Actual MemoryAccount allocation requests are charged separately and not added twice here. |
| ownership | ScalarView and Budget are borrowed; no string, Decimal coefficient or row is created. |
| failure | Exhausted can occur partway through sequential charges; earlier work/model bytes remain spent and no scalar copy has yet happened. |
| cost | Fixed arithmetic plus length reads and aggregate work debits; this helper does not actually loop over text bytes or allocate them. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 55–59](../../../../../src/runtime/native_statistics.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedKey copy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit modeled key payload then deep-copy a native row for capture. |
| inputs / outputs | Precharges every scalar, records row capacity as values.size(), and returns CapturedKey with AccountedRow::copy_of(account,...). |
| invariants | Source bytes must remain stable until copy completes; observed capacity is reporting metadata, not a reserve or allocator-byte measurement. |
| ownership | Result owns compact text/native cells funded under owner_capture_memory on the original account; source row is not retained or pinned. |
| failure | Logical budget exhaustion occurs before the actual row copy. Memory/account/overflow failure can still occur in copy_of and propagates separately. |
| cost | O(key fields plus copied text bytes) plus compact block/control allocation; fixed Decimal payload copying is not ordinary coefficient-string allocation. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 60–63](../../../../../src/runtime/native_statistics.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void admit(Groups& groups,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account and insert one already copied distinct positive weighted key. |
| inputs / outputs | Debits one distinct-key unit and sizeof(HeavyKey)+two pointers in the logical model, then moves key/count into a funded list node. |
| invariants | Caller establishes distinctness and positive count; this helper neither searches existing groups nor coalesces duplicates. |
| ownership | By-value key transfers its compact owner to the list; failed insertion destroys the private moved/copy candidate. List allocation uses groups' original account. |
| failure | Exhausted or actual node allocation failure propagates; prior logical charges are retained. |
| cost | Fixed admission/owner moves plus one node allocation; key copying before the call is a separate field/byte cost. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 64–65](../../../../../src/runtime/native_statistics.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:2bff5331ed27867cbb8ef8b021c23978105bc245f363b202adae25abfd5473dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void finish(CapturedDistribution& out,Groups& groups,Budget& budget,const resource::MemoryAccount& account)\`: Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative logical payload growth remain costs. Exact facts publish only after preparation. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/native_statistics.cpp:L66; use that declaration for the actual input/output shape. |
| invariants | The source note states: Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative logical payload growth remain costs. Exact facts publish only after preparation. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative logical payload growth remain costs. Exact facts publish only after preparation. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0015

[Lines 66–96](../../../../../src/runtime/native_statistics.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(CapturedDistribution& out,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately compute exact NDV, multiplicity bins and ordered top-K before publishing distribution facts. |
| inputs / outputs | Sorts groups descending count then native key; each next count can match only the last histogram bin or starts a new smaller class. Checks only that last bin, builds exact counts, sorts histogram ascending multiplicity and moves top-K before assigning exact output fields. |
| invariants | Descending count sort makes equal multiplicities contiguous; key ordering only breaks ties. Last-bin induction preserves one exact bin per count class. No NDV/top-K/histogram prefix is assigned until every charged preparation succeeds. List sort relinks nodes; failed comparator leaves valid private scratch for cleanup. |
| ownership | Histogram/heavy arrays use original-account capture allocators; heavy keys transfer compact owners from scratch, remaining groups release afterward. Result retains no source cursor/row pointer. |
| failure | Exhausted leaves out's default incomplete facts and visited prefix; actual allocation failure propagates. Callers own precise exhaustion translations; no broad catch here. |
| cost | O(K log K) charged group comparisons plus native tie-key field/text costs; exactly max(K-1,0) histogram lookup work, one per actual nonempty back comparison. New-bin reserve(size+1), potential moves and cumulative H(H+1)/2 logical work/pair payload remain, followed by O(H log H) histogram sort and top-K moves. Only lookup becomes O(K); no whole-operation linearity, allocator-byte or timing claim. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 97–99](../../../../../src/runtime/native_statistics.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L99:sha256:75e3e37a30e2aa2a47892ae5bc4a39b57eb50ea5f24658430d55f3171bf36136
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/native_statistics.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/native_statistics.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/native_statistics.cpp\` at its lexical source position in src/runtime/native_statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/native_statistics.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0017

[Lines 100–128](../../../../../src/runtime/native_statistics.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedDistribution detail::native_projected_fields(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a distribution of an exact ordered field projection from committed native table rows. |
| inputs / outputs | Checks projection width/field bounds, creates live cursor, visits rows and copies each projected native key, linearly deduplicates groups by charged compare, increments multiplicities/visited and calls finish. |
| invariants | Empty/repeated field lists are valid ordered projections. Every row, including a duplicate key, is copied before group lookup. On bounded exhaustion only visited survives; NDV/top-K remain absent and histogram empty. |
| ownership | Cursor borrows stable table facade and owns its native cursor pin/control as required by storage; local scratch/output use original account. Result owns captured bytes, not table views or new projection metadata. |
| failure | Catches only Exhausted and IndexFailure/Error whose exact code is storage_work_limit, mapping them to incomplete distribution. Invalid field/request, corruption/ownership and actual allocation failures propagate. Cursor creation is inside this try. |
| cost | Full row/cursor scan; O(rows*distinct) charged native key comparisons in the worst case, with compared text bytes. Per-row projected block copies, distinct list nodes, final histogram/top-K allocations and independent native IndexWork costs remain. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 129–145](../../../../../src/runtime/native_statistics.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedDistribution detail::native_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture existing nonempty native index buckets as distinct keys weighted by degree. |
| inputs / outputs | Creates index-key cursor, checks width, copies each native key and degree, admits one group per bucket, increments visited and calls finish. |
| invariants | Index cursor provides distinct positive bucket keys; capture does not build/register an index or deduplicate keys. Named logical startup charge is sizeof(Capture) as implemented, separate from actual native object sizes. |
| ownership | Local cursor/control, compact key blocks/list nodes and output arrays use original query/account contracts; output retains copied values without a live bucket pointer. |
| failure | Cursor factory runs before the local try, allowing its storage-work failure to reach OwnerBuilder::index. Within try only Exhausted and IndexFailure(storage_work_limit) become incomplete; other failures propagate. |
| cost | One native bucket walk and deep key copy per bucket, plus scalar bytes/work and finish sorting/current histogram scans. Independent storage grant and actual account allocations remain; no new key index is built. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 146–147](../../../../../src/runtime/native_statistics.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L147:sha256:2fb1ccd015c87682509518c26fbecd92ee36bceb2639519b495621d9e1628745
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/native_statistics.cpp: opens namespace \`detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0020

[Lines 148–155](../../../../../src/runtime/native_statistics.cpp#L148); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WeightedBuilder::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold private positive-weight native population capture state across owner iteration. |
| inputs / outputs | budget is a borrowed shared capture Budget; account is retained original account; groups owns scratch keys/nodes; output starts incomplete; exhausted is a sticky stop flag. |
| invariants | Each supplied key must already be distinct in its owner map. Data records no source owner pointer, mutable map iterator or recovery state. |
| ownership | Budget must outlive WeightedBuilder. Account funds Data/control, group nodes/keys and output vectors; RAII releases all private scratch on any failure. |
| failure | Logical Exhausted is handled by add/finish or outer callers. Actual allocation failures propagate and destroy the private graph. |
| cost | Fixed initial state/empty containers; actual populated storage scales with distinct keys, text bytes and final histogram/heavy arrays. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 156–159](../../../../../src/runtime/native_statistics.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WeightedBuilder::WeightedBuilder(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate the weighted-capture state after its explicit logical admission. |
| inputs / outputs | Debits one work and sizeof(Data), then make_accounted_unique funds Data under scratch owner_capture_memory. |
| invariants | Borrowed Budget is reused, never copied/refilled; the supplied account is the owner's original account. |
| ownership | Builder exclusively owns Data, which retains account and borrows Budget. |
| failure | Logical exhaustion precedes actual allocation; MemoryFailure/bad_alloc can still fail actual construction and propagates. |
| cost | One actual funded unique/control request plus fixed empty allocator setup; no row iteration yet. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 160–161](../../../../../src/runtime/native_statistics.cpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WeightedBuilder::~WeightedBuilder()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release private weighted capture scratch through its concrete owning Data. |
| inputs / outputs | Default out-of-line destruction destroys AccountedUnique&lt;Data&gt;, list/key owners and any remaining output arrays. |
| invariants | Destruction performs no retry, budget refill or source owner mutation. |
| ownership | Last key/control owners release actual original-account requests; retained moved output is independent. |
| failure | Ordinary nonthrowing RAII teardown; no manual catch or recovery layer. |
| cost | O(remaining list nodes and owning keys/arrays) actual destruction/deallocation; it allocates no replacement storage. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 162–170](../../../../../src/runtime/native_statistics.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool WeightedBuilder::add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one distinct native map key with its stored positive multiplicity. |
| inputs / outputs | Returns false immediately once exhausted; rejects zero count; otherwise charges row/work/width, deep-copies/admit key and increments visited, returning true. |
| invariants | No duplicate lookup/coalescing occurs: Physical derivation and Support parent/visible maps supply distinct keys. Positive multiplicity represents actual stored counts rather than repeated-row expansion. |
| ownership | Input RowView borrows caller map/table only during copy; builder retains independent compact owners. |
| failure | Only Exhausted inside the capture body becomes sticky false. Zero count throws statistics_contract; real allocation/corruption failures propagate. Caller loops stop on false. |
| cost | O(key fields and text-byte copy) plus list node allocation and fixed charge; no work proportional to count and no extra grouping scan in add(). |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 171–171](../../../../../src/runtime/native_statistics.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WeightedBuilder::stop()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark an externally exhausted native weighted scan as incomplete. |
| inputs / outputs | Sets the sticky exhausted flag; finish then skips exact distribution construction. |
| invariants | Used after outer shared-budget/storage-work exhaustion; existing visited progress is retained, no prefix facts become exact. |
| ownership | No ownership or allowance changes; private accumulated keys remain until teardown. |
| failure | Noexcept, no allocation or error translation. |
| cost | One boolean store; accumulated scratch destruction remains a later cost. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 172–176](../../../../../src/runtime/native_statistics.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedDistribution WeightedBuilder::finish()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume weighted-builder output, producing exact facts only if preparation completes. |
| inputs / outputs | If not stopped, invokes native finish and absorbs only Exhausted; moves out the owning CapturedDistribution. |
| invariants | Caller uses the builder once for one population. After a stop/finalization exhaustion, output remains incomplete with only visited progress; repeated add/finish after consumption is not a supported producer protocol. |
| ownership | Result transfers funded arrays/compact keys; list scratch is released with Builder and Budget remains caller-owned. |
| failure | Logical Exhausted becomes incomplete; actual allocation/corruption failures propagate. No generic recovery. |
| cost | Full native finish sort/histogram/top-K work when active, then owner moves; stopped path skips that work but retains eventual scratch teardown costs. |
| Design | [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 177–178](../../../../../src/runtime/native_statistics.cpp#L177); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L178:sha256:285577568ac35d60830cf925beb22babfffdf80c35bfd45a12e88fdba305694d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/native_statistics.cpp: closes \`namespace detail\`, \`namespace crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
