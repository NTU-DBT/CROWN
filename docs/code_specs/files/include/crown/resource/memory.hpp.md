# `include/crown/resource/memory.hpp` — block usage map

[Source](../../../../../../include/crown/resource/memory.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `270149cc83faee34774d79f0a37250940eee1d9a983f6c0f9018333673249af5`. 190 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/resource/memory.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | growth new; source comment (unverified): // Per-query allocation account used by the native runtime. Owners route every · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/resource/memory.hpp#L16) | Type/record definition: enum class MemoryFault : std::uint8_t |  · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../../include/crown/resource/memory.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // The resource path carries a fixed diagnostic and never constructs owning · [reviewed contract](#b0003) |
| [B0004 · 20–42](../../../../../../include/crown/resource/memory.hpp#L20) | Type/record definition: class MemoryFailure final : public std::bad_alloc | returns fault_; @; source comment (unverified): // The resource path carries a fixed diagnostic and never constructs owning · [reviewed contract](#b0004) |
| [B0005 · 43–43](../../../../../../include/crown/resource/memory.hpp#L43) | Explanatory comments or spacing. |  |
| [B0006 · 44–49](../../../../../../include/crown/resource/memory.hpp#L44) | Type/record definition: enum class MemoryPurpose : std::uint8_t |  · [reviewed contract](#b0006) |
| [B0007 · 50–50](../../../../../../include/crown/resource/memory.hpp#L50) | Type/record definition: enum class AllocationLifetime : std::uint8_t |  · [reviewed contract](#b0007) |
| [B0008 · 51–56](../../../../../../include/crown/resource/memory.hpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // IDs are scoped to this query account and supplied by the owning compiled · [reviewed contract](#b0008) |
| [B0009 · 57–60](../../../../../../include/crown/resource/memory.hpp#L57) | Type/record definition: enum class MemoryOwnerKind : std::uint8_t | source comment (unverified): // IDs are scoped to this query account and supplied by the owning compiled · [reviewed contract](#b0009) |
| [B0010 · 61–69](../../../../../../include/crown/resource/memory.hpp#L61) | Type/record definition: struct MemoryAttribution | returns static_cast&lt;std::size_t&gt;(kind) &lt; static_cast&lt;std::size_t&gt;(MemoryOwnerKind::count) && · [reviewed contract](#b0010) |
| [B0011 · 70–73](../../../../../../include/crown/resource/memory.hpp#L70) | Explanatory comments or spacing. | source comment (unverified): // Requested upstream bytes include this component's own headers, alignment · [reviewed contract](#b0011) |
| [B0012 · 74–79](../../../../../../include/crown/resource/memory.hpp#L74) | Type/record definition: struct MemoryUsage | source comment (unverified): // Requested upstream bytes include this component's own headers, alignment · [reviewed contract](#b0012) |
| [B0013 · 80–90](../../../../../../include/crown/resource/memory.hpp#L80) | Type/record definition: struct MemoryStatistics |  · [reviewed contract](#b0013) |
| [B0014 · 91–98](../../../../../../include/crown/resource/memory.hpp#L91) | Type/record definition: struct AttributedMemoryStatistics |  · [reviewed contract](#b0014) |
| [B0015 · 99–118](../../../../../../include/crown/resource/memory.hpp#L99) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One mutating thread per account; shared handles, blocks and observations · [reviewed contract](#b0015) |
| [B0016 · 119–119](../../../../../../include/crown/resource/memory.hpp#L119) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns control_ != nullptr · [reviewed contract](#b0016) |
| [B0017 · 120–155](../../../../../../include/crown/resource/memory.hpp#L120) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth allocate, allocate_raw; source comment (unverified): // Explicit diagnostic O(outstanding allocations), with no allocation or · [reviewed contract](#b0017) |
| [B0018 · 156–167](../../../../../../include/crown/resource/memory.hpp#L156) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 168–168](../../../../../../include/crown/resource/memory.hpp#L168) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns data_ != nullptr · [reviewed contract](#b0019) |
| [B0020 · 169–190](../../../../../../include/crown/resource/memory.hpp#L169) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact stored request, not a recomputed capacity estimate. Empty/moved · [reviewed contract](#b0020) |

## B0001

[Lines 1–15](../../../../../../include/crown/resource/memory.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:b6024834ed03db575a5733e37b81a68547618a34d696b978a17bfe6aa3fb37a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/resource/memory.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`&lt;array&gt;\`, \`&lt;compare&gt;\`, \`&lt;cstddef&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;new&gt;\`, \`&lt;span&gt;\`, \`&lt;string_view&gt;\` for compilation; opens namespace \`crown::resource\`. Source comment: Per-query allocation account used by the native runtime. Owners route every nested allocation through the same account; allocator propagation is explicit. Usage, ownership and costs: docs/code_specs/primitives.md#memory-account. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Per-query allocation account used by the native runtime. Owners route every nested allocation through the same account; allocator propagation is explicit. Usage, ownership and costs: docs/code_specs/primitives.md#memory-account. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Per-query allocation account used by the native runtime. Owners route every nested allocation through the same account; allocator propagation is explicit. Usage, ownership and costs: docs/code_specs/primitives.md#memory-account. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 16–16](../../../../../../include/crown/resource/memory.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MemoryFault : std::uint8_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish memory admission exhaustion, representational overflow and invalid resource usage. |
| inputs / outputs | The limit/overflow/contract enum values are the fixed fault payload of MemoryFailure. |
| invariants | They identify resource failures without constructing an owning diagnostic or replacing the original exception with a generic recovery mechanism. |
| ownership | A single inline byte-sized enum; no account or buffer ownership. |
| failure | Declaring or copying a value does not throw; public failure presentation is provided by MemoryFailure. |
| cost | Fixed storage and O(1) transfer. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0003

[Lines 17–19](../../../../../../include/crown/resource/memory.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L19:sha256:01df08c61e993cd7b7defc546ef7f1365da41a56591f70c1baf39218cf2821dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class MemoryFailure final : public std::bad_alloc\`: The resource path carries a fixed diagnostic and never constructs owning strings. C++ exception-runtime storage is outside operator-new accounting. An external presentation boundary can format this after the epoch unwinds. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/memory.hpp:L20; use that declaration for the actual input/output shape. |
| invariants | The source note states: The resource path carries a fixed diagnostic and never constructs owning strings. C++ exception-runtime storage is outside operator-new accounting. An external presentation boundary can format this after the epoch unwinds. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: The resource path carries a fixed diagnostic and never constructs owning strings. C++ exception-runtime storage is outside operator-new accounting. An external presentation boundary can format this after the epoch unwinds. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0004

[Lines 20–42](../../../../../../include/crown/resource/memory.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MemoryFailure final : public std::bad_alloc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed, nonowning native memory diagnostic through unwinding. |
| inputs / outputs | Construction stores a MemoryFault; fault() returns it, code() returns a stable string_view and what() a static C string. |
| invariants | All methods are noexcept. An unrecognized enum maps code()/what() to the contract fallback while fault() preserves its stored value. |
| ownership | Message bytes are static; the object owns no diagnostic string. C++ exception-runtime storage is outside operator-new accounting. |
| failure | It is a bad_alloc subtype so normal allocation boundaries can handle it; formatting belongs after native state unwinds. |
| cost | O(1) switches and scalar storage; no explicit heap/string allocation by these methods. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0006

[Lines 44–49](../../../../../../include/crown/resource/memory.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MemoryPurpose : std::uint8_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify each live allocation by the component storage role that requested it. |
| inputs / outputs | Categories include controller, tables, payload, undo, cursor, capture and scratch; count is an array-size sentinel. |
| invariants | A purpose is immutable after allocation. The control category is reserved for the account controller and cannot fund ordinary blocks. |
| ownership | Each category labels blocks in the same account; no separate allowance or per-purpose owner registry is created. |
| failure | Invalid/sentinel categories reject at checked account/allocator entry points. |
| cost | Fixed enum and fixed-size statistics arrays; no dynamic category tracking. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0007

[Lines 50–50](../../../../../../include/crown/resource/memory.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AllocationLifetime : std::uint8_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition allocated storage by active, retained or reusable free-pool status. |
| inputs / outputs | A live block carries one non-sentinel lifetime; reclassification transfers its exact usage between fixed totals. |
| invariants | A lifetime label describes backing allocation state, not how many live elements occupy its capacity. Reclassification does not free or refill bytes. |
| ownership | No ownership transfer occurs when the label changes. |
| failure | Invalid/sentinel destinations reject; cleanup paths must establish valid metadata before calling throwing classification APIs. |
| cost | O(1) classification metadata; retained/free-pool capacity remains charged. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0008

[Lines 51–56](../../../../../../include/crown/resource/memory.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr auto memory_purpose_count
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Size the fixed statistics partitions from the enum sentinels. |
| inputs / outputs | Compile-time size_t constants give the number of purpose and lifetime categories. |
| invariants | The count enum values are bounds, not valid per-allocation categories. |
| ownership | No retained storage beyond fixed arrays in each statistics/controller value. |
| failure | No runtime failure or allocation is introduced by the constants. |
| cost | Compile-time scalar values; category growth increases fixed controller/report size rather than a dynamic registry. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0009

[Lines 57–60](../../../../../../include/crown/resource/memory.hpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MemoryOwnerKind : std::uint8_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the component domain of a query-local allocation attribution. |
| inputs / outputs | Kinds identify query, physical/support/storage/session/cursor/metadata/output/recovery owners; count is the invalid sentinel. |
| invariants | Kind plus numeric ID is scoped to an account. It labels ownership without changing account admission or lifetime category. |
| ownership | The key itself owns no memory; the allocating component supplies its numeric ID. |
| failure | MemoryAttribution::valid rejects the sentinel/unknown kind and reserves query for ID zero. |
| cost | Fixed inline enum; no per-kind registry or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0010

[Lines 61–69](../../../../../../include/crown/resource/memory.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MemoryAttribution {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an immutable query-local owner key for allocation reports and allocator identity. |
| inputs / outputs | Defaults to query:0; valid() checks kind range and the query ID restriction; default comparison orders the two fields. |
| invariants | Only query requires ID zero; other valid kinds may use any uint64 ID. The key does not authenticate an arbitrary owner or provide another limit. |
| ownership | Copied value only; blocks and allocators retain it without an owner map. |
| failure | valid() and comparisons are noexcept value operations; allocation entry points reject invalid values. |
| cost | O(1) checks/comparisons and fixed per-block metadata, with no dynamic registration. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0011

[Lines 70–73](../../../../../../include/crown/resource/memory.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L73:sha256:fc408ac8e750932c3011b222bab01411fb2989e00c78c06453c9e274f6631f4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct MemoryUsage\`: Requested upstream bytes include this component's own headers, alignment allowance and controller. Payload bytes are the caller's requested size. These are not allocator usable-size, resident bytes, or logical tuple bytes. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/memory.hpp:L74; use that declaration for the actual input/output shape. |
| invariants | The source note states: Requested upstream bytes include this component's own headers, alignment allowance and controller. Payload bytes are the caller's requested size. These are not allocator usable-size, resident bytes, or logical tuple bytes. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Requested upstream bytes include this component's own headers, alignment allowance and controller. Payload bytes are the caller's requested size. These are not allocator usable-size, resident bytes, or logical tuple bytes. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0012

[Lines 74–79](../../../../../../include/crown/resource/memory.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MemoryUsage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report exact live allocation count, upstream requested bytes and caller payload bytes. |
| inputs / outputs | Three zero-initialized uint64 counters have default fieldwise comparison. |
| invariants | Requested bytes include headers/alignment/controller where applicable; payload excludes those costs. Neither is allocator usable-size, RSS or logical tuple width. |
| ownership | A self-contained value with no pointers or retained account. |
| failure | The carrier does not perform checked arithmetic; account primitives maintain its totals under their admission invariants. |
| cost | Fixed scalar storage/copy/comparison; no scan or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0013

[Lines 80–90](../../../../../../include/crown/resource/memory.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MemoryStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one account's maintained usage, peak and allocation-history snapshot. |
| inputs / outputs | Owner ID and byte limit accompany current MemoryUsage, peak requested bytes, successful/freed counts, and fixed purpose/lifetime partitions. |
| invariants | Controller bytes appear from creation; purpose and lifetime partitions each reconcile to current usage. History can record successful speculative allocation later freed. |
| ownership | The returned value owns fixed arrays only and does not retain the controller or an address list. |
| failure | Constructing/copying the carrier itself does not allocate; a source account must be externally synchronized while taking a snapshot. |
| cost | Fixed-size copy independent of outstanding block count; report consumers may perform separate scans. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0014

[Lines 91–98](../../../../../../include/crown/resource/memory.hpp#L91); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AttributedMemoryStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry current usage for one owner attribution within a particular account. |
| inputs / outputs | Account owner ID and attribution accompany total usage and fixed purpose/lifetime arrays. |
| invariants | It is a current allocation partition, with no separate cap, peak or historical allocation ledger. query:0 includes controller usage. |
| ownership | The result is self-contained scalar/fixed-array data, not a retained account or live view. |
| failure | Carrier initialization/copy has no allocation path; the account scan that computes it can reject invalid input. |
| cost | Fixed result size; computing it with statistics_for costs O(outstanding allocations). |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md) |

## B0015

[Lines 99–118](../../../../../../include/crown/resource/memory.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MemoryAccount {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own or share one finite native requested-byte authority. |
| inputs / outputs | Default construction is empty; create(limit) allocates a charged controller; copy/move/destruction share, transfer or release its handle. |
| invariants | Exactly one mutating thread per account and external synchronization are required. Upstream allocation must not release/reclassify this account's blocks; nested allocation is rejected before overcommit. |
| ownership | Handles and live blocks independently retain one controller. Copying never creates a new grant; moving empties the source. |
| failure | Empty handles reject account operations; admission uses fixed MemoryFailure/bad_alloc. Noexcept handle cleanup terminates on impossible internal lifetime state. |
| cost | Handle operations are O(1); create has one controller allocation. Whole-account diagnostics are explicit separate scans. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0016

[Lines 119–119](../../../../../../include/crown/resource/memory.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept { return control_ != nullptr; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether an account handle currently retains a controller. |
| inputs / outputs | Returns true for a nonnull control pointer and false after default construction or ownership transfer. |
| invariants | A true handle still obeys its existing cap; this test makes no claim about spare capacity or diagnostic consistency. |
| ownership | It borrows handle metadata and adds no controller reference. |
| failure | Noexcept, including for empty handles. |
| cost | O(1) pointer comparison; no scan or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0017

[Lines 120–155](../../../../../../include/crown/resource/memory.hpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryStatistics statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the account allocation and diagnostic boundary without exposing raw storage authority. |
| inputs / outputs | statistics/statistics_for/copy_attributions inspect usage; allocate owns a new block; containing classification changes a current block label; check_invariants validates the whole ledger. |
| invariants | Fixed statistics are O(1); owner inventory/attribution/containing lookup/invariant checks scan outstanding blocks. Caller inventory capacity includes the controller and must be prepared before copying. |
| ownership | Public diagnostics return copied values or fill caller storage. Private raw bridges are reserved for MemoryAllocator, and all live blocks retain their original controller. |
| failure | Nonempty account, valid categories/attribution, quiescent mutation and live-address preconditions are enforced at their defined boundaries. Diagnostic failure does not repair state. |
| cost | Allocation has one framed upstream request; direct block operations use fixed counters. Whole-account scans are caller-requested work and add no hidden per-row instrumentation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md) |

## B0018

[Lines 156–167](../../../../../../include/crown/resource/memory.hpp#L156); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MemoryBlock {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sole RAII ownership of one aligned account-funded allocation. |
| inputs / outputs | Default construction is empty; copying is deleted; moves transfer the block and empty the source; destruction/reset consume it. |
| invariants | A real zero-payload allocation is nonempty and remains charged for framing. Each block independently retains its controller until deallocation. |
| ownership | The block owns raw storage, not a constructed T or arbitrary nested object graph. Callers manage object destruction before releasing typed storage. |
| failure | Moves/reset/destruction allocate nothing and do not throw; inconsistent internal deallocation state terminates. |
| cost | O(1) ownership transfer/unlink/counter work plus upstream delete; no whole-ledger traversal. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0019

[Lines 168–168](../../../../../../include/crown/resource/memory.hpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept { return data_ != nullptr; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a MemoryBlock owns a real allocation. |
| inputs / outputs | Returns the presence of BlockData, including true for an allocated zero-byte payload. |
| invariants | Default/moved/reset handles are false; payload size zero alone cannot distinguish them from a real zero-payload block. |
| ownership | No transfer, borrow extension or controller copy occurs. |
| failure | Noexcept for all handle states. |
| cost | O(1) pointer comparison; no scan or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0020

[Lines 169–190](../../../../../../include/crown/resource/memory.hpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] void* data() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare borrowed payload/metadata access and direct lifetime classification for a block. |
| inputs / outputs | data/size/usage return null/zero for empty handles; purpose/attribution/lifetime/account_statistics require a live block; set_lifetime classifies that block; reset frees it. |
| invariants | Borrowed pointers require the allocation to remain owned; a move transfers that obligation. Releasing its current owner frees the storage. Exact usage includes stored framing; lifetime changes preserve total requested bytes. |
| ownership | The sole private BlockData pointer anchors storage. account_statistics copies fixed account state without taking a new handle. |
| failure | Required metadata access throws contract on an empty block; classification also validates the target and allocation-reentry rule. reset is noexcept. |
| cost | O(1) direct header/counter operations. No accessor scans the account or recursively reports arbitrary payload members. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |
