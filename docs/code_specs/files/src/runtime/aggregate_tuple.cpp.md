# `src/runtime/aggregate_tuple.cpp` — block usage map

[Source](../../../../../src/runtime/aggregate_tuple.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own nullable aggregate tuple cells and copied text with accounted payloads and borrowed read-only views.

Snapshot SHA-256: `0f99fe322ad0eedd34d2b21bf42204d442c116aff4ff6c0844866e9e35fe54a9`. 78 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/runtime/aggregate_tuple.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_destructible_v&lt;Cell&gt;); · [reviewed contract](#b0001) |
| [B0002 · 13–19](../../../../../src/runtime/aggregate_tuple.cpp#L13) | Type/record definition: struct Tuple::Data |  · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/runtime/aggregate_tuple.cpp#L20) | Explanatory comments or spacing. |  |
| [B0004 · 21–50](../../../../../src/runtime/aggregate_tuple.cpp#L21) | Callable definition: Tuple Tuple::copy_of(const resource::MemoryAccount& account, std::span&lt;const Cell&gt; source, resource::MemoryPurpose purpose) | calls max, size, Error, allocate; returns Tuple(resource::make_accounted_shared&lt;Data&gt;(account, purpose, account, std::move(payload), source.s…; growth allocate, copy_of, make_accounted_shared; 2 loop sites; source comment (unverified): // Cell copies cannot throw and own no child allocations. A failed Data · [reviewed contract](#b0004) |
| [B0005 · 51–51](../../../../../src/runtime/aggregate_tuple.cpp#L51) | Explanatory comments or spacing. |  |
| [B0006 · 52–55](../../../../../src/runtime/aggregate_tuple.cpp#L52) | Callable definition: const Tuple::Data& Tuple::data() const | calls Error; returns *data_ · [reviewed contract](#b0006) |
| [B0007 · 56–56](../../../../../src/runtime/aggregate_tuple.cpp#L56) | Callable definition: std::size_t Tuple::size() const | calls data; returns data().width · [reviewed contract](#b0007) |
| [B0008 · 57–60](../../../../../src/runtime/aggregate_tuple.cpp#L57) | Callable definition: std::span&lt;const Cell&gt; Tuple::view() const & | calls data; returns {static_cast&lt;const Cell*&gt;(value.payload.data()), value.width} · [reviewed contract](#b0008) |
| [B0009 · 61–61](../../../../../src/runtime/aggregate_tuple.cpp#L61) | Callable definition: const resource::MemoryAccount& Tuple::account() const & | calls data; returns data().account · [reviewed contract](#b0009) |
| [B0010 · 62–66](../../../../../src/runtime/aggregate_tuple.cpp#L62) | Callable definition: bool Tuple::operator==(const Tuple& other) const | calls std::equal, begin, end; returns true; std::equal(left.begin(), left.end(), right.begin(), right.end()) · [reviewed contract](#b0010) |
| [B0011 · 67–73](../../../../../src/runtime/aggregate_tuple.cpp#L67) | Callable definition: Row Tuple::export_values() const | calls reserve, size, view, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 74–77](../../../../../src/runtime/aggregate_tuple.cpp#L74) | Callable definition: Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t epoch, frontend::AggregateProgram source) : sequence(epo… | calls sequence, program, std::move, groups · [reviewed contract](#b0012) |
| [B0013 · 78–78](../../../../../src/runtime/aggregate_tuple.cpp#L78) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::aggregate · [reviewed contract](#b0013) |

## B0001

[Lines 1–12](../../../../../src/runtime/aggregate_tuple.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_trivially_destructible_v<Cell>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove that nullable cell payload cleanup requires no per-cell destructor or rollback log. |
| inputs / outputs | Compile-time checks require trivial destruction and nothrow copy construction. |
| invariants | Changing Cell to an owning/throwing alternative must fail this implementation contract. |
| ownership | Cell descriptors own no child allocations; copied string bytes live in the outer block. |
| failure | A violated property fails compilation rather than adding repeated exception machinery. |
| cost | Zero runtime checks. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0002

[Lines 13–19](../../../../../src/runtime/aggregate_tuple.cpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Tuple::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the tuple account, single payload block and descriptor count. |
| inputs / outputs | Noexcept constructor moves account/block and stores width. |
| invariants | Payload layout is exactly the copy_of contract; no secondary string owner is hidden here. |
| ownership | Data and its shared-control allocation retain account; MemoryBlock releases copied cells/bytes together. |
| failure | Member moves are nonthrowing; a partially allocated outer shared object uses ordinary allocator cleanup. |
| cost | Fixed owner fields; final destruction frees payload and shared control. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0004

[Lines 21–50](../../../../../src/runtime/aggregate_tuple.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple Tuple::copy_of(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy nullable scalar descriptors and every string byte into one funded payload. |
| inputs / outputs | Stable borrowed span/account/purpose in; independent immutable Tuple out, including a valid nullary tuple. |
| invariants | Preflight checks size multiplication/addition before allocating. Inline nonstring values are copied without child ownership. |
| ownership | Payload and shared Data/control use the same receiving account/purpose. Source cells and strings need only survive the call. |
| failure | Capacity/account/allocation failures propagate; noexcept cell copying means the single payload owner suffices for cleanup. |
| cost | Two linear field passes plus total string bytes; one payload allocation when nonempty plus accounted shared Data/control construction. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0006

[Lines 52–55](../../../../../src/runtime/aggregate_tuple.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple::Data& Tuple::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid tuple-handle access at one checked boundary. |
| inputs / outputs | Returns const Data reference for nonempty Tuple. |
| invariants | A valid nullary tuple has Data and is distinct from a default empty handle. |
| ownership | Returned reference borrows the shared owner. |
| failure | Empty handle raises invalid_aggregate_tuple. |
| cost | Constant pointer test; no successful allocation. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0007

[Lines 56–56](../../../../../src/runtime/aggregate_tuple.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t Tuple::size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read descriptor width without scanning payload. |
| inputs / outputs | Returns stored size_t width. |
| invariants | Zero width is valid only with nonempty Data. |
| ownership | Inline return value. |
| failure | data() rejects an empty handle. |
| cost | Constant getter. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0008

[Lines 57–60](../../../../../src/runtime/aggregate_tuple.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const Cell> Tuple::view() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable nullable descriptor array. |
| inputs / outputs | Returns payload pointer and stored width; null pointer with zero width represents a valid nullary tuple. |
| invariants | String views point inside this same owned payload; span does not extend its lifetime. |
| ownership | Keep a surviving Tuple owner and externally synchronize account access as required. |
| failure | Empty handle is rejected by data(); no allocation on success. |
| cost | Constant view construction; no string copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0009

[Lines 61–61](../../../../../src/runtime/aggregate_tuple.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& Tuple::account() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the tuple receiving account for explicit inspection. |
| inputs / outputs | Valid Tuple in; const account reference out. |
| invariants | The same grant funds its payload and Data; getter creates no new allowance. |
| ownership | Reference borrows Data, so keep its Tuple owner alive. |
| failure | Empty handle is rejected. |
| cost | Constant getter; full statistics/diagnostics are separate work. |
| Design | [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0010

[Lines 62–66](../../../../../src/runtime/aggregate_tuple.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Tuple::operator==(const Tuple& other) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare immutable nullable tuples by typed cell values. |
| inputs / outputs | Same shared owner returns true; otherwise std::equal checks widths and cells. |
| invariants | NULL differs from any present scalar. Different variant alternatives retain their typed distinction. |
| ownership | Both payloads are borrowed; equality allocates no owning export. |
| failure | Two default handles compare equal; one invalid and one valid handle rejects through view(). |
| cost | Identity fast path is constant; otherwise compared fields and string bytes determine cost. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0011

[Lines 67–73](../../../../../src/runtime/aggregate_tuple.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row Tuple::export_values() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make the explicit ordinary nullable Value DTO export. |
| inputs / outputs | Returns a standard vector with deep scalar/string exports and preserved NULL positions. |
| invariants | Internal cells remain unchanged and no implicit Row conversion is installed. |
| ownership | Caller owns result vector/string/Decimal allocations outside the tuple account. |
| failure | Invalid tuple or caller allocation/export failure propagates; local vector cleans partial export. |
| cost | Linear fields and exported bytes; allocation is explicit output work. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 74–77](../../../../../src/runtime/aggregate_tuple.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot::Snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize snapshot identity, schema ownership and receiving-account result storage. |
| inputs / outputs | Moves supplied AggregateProgram, stores epoch, and constructs an empty OwnerAllocator vector. |
| invariants | Output-vector attribution is output:0 with output_buffer purpose; metadata can retain its original compiler account. |
| ownership | Snapshot owns program handle and allocator account; no groups are copied here. |
| failure | Constructor adds no fallback behavior; later vector growth may fail the receiver grant. |
| cost | Fixed empty-container initialization. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0013

[Lines 78–78](../../../../../src/runtime/aggregate_tuple.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L78:sha256:ca2ab7ea28462d768d859e41aad913af61a31dd1b4f95454269ffc7f4984c810
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::aggregate\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::aggregate\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::aggregate\` at its lexical source position in src/runtime/aggregate_tuple.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::aggregate\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
