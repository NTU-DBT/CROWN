# `include/crown/resource/allocator.hpp` — block usage map

[Source](../../../../../../include/crown/resource/allocator.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `66b9eae19d9a2997a892e12196f0433f42f26c2a04fec6e550aa12aa98972adb`. 96 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../../include/crown/resource/allocator.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_object_v&lt;T&gt; && !std::is_const_v&lt;T&gt;);; growth new; source comment (unverified): // Standard-container allocator used by maintained native state. It charges · [reviewed contract](#b0001) |
| [B0002 · 33–33](../../../../../../include/crown/resource/allocator.hpp#L33) | Type/record definition: template&lt;class U&gt; struct rebind |  · [reviewed contract](#b0002) |
| [B0003 · 34–35](../../../../../../include/crown/resource/allocator.hpp#L34) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 36–42](../../../../../../include/crown/resource/allocator.hpp#L36) | Callable definition: explicit MemoryAllocator(const MemoryAccount& account, MemoryPurpose purpose = MemoryPurpose::scratch, MemoryAttribution attribut… | calls account_, purpose_, attribution_, valid · [reviewed contract](#b0004) |
| [B0005 · 43–46](../../../../../../include/crown/resource/allocator.hpp#L43) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Allocator moves use the copy constructor/assignment, leaving the source · [reviewed contract](#b0005) |
| [B0006 · 47–49](../../../../../../include/crown/resource/allocator.hpp#L47) | Callable definition: template&lt;class U&gt; MemoryAllocator(const MemoryAllocator&lt;U&gt;& other) noexcept : account_(other.account_), purpose_(other.purpose_),… | calls account_, purpose_, attribution_; source comment (unverified): // Allocator moves use the copy constructor/assignment, leaving the source · [reviewed contract](#b0006) |
| [B0007 · 50–50](../../../../../../include/crown/resource/allocator.hpp#L50) | Explanatory comments or spacing. |  |
| [B0008 · 51–55](../../../../../../include/crown/resource/allocator.hpp#L51) | Callable definition: \[\[nodiscard\]\] T* allocate(std::size_t count) | calls max_size, allocate_raw; returns static_cast&lt;T*&gt;(account_.allocate_raw(count * sizeof(T), alignof(T), purpose_, attribution_)); growth allocate, allocate_raw · [reviewed contract](#b0008) |
| [B0009 · 56–60](../../../../../../include/crown/resource/allocator.hpp#L56) | Callable definition: void deallocate(T* pointer, std::size_t count) noexcept | calls max_size, std::terminate, deallocate_raw · [reviewed contract](#b0009) |
| [B0010 · 61–63](../../../../../../include/crown/resource/allocator.hpp#L61) | Callable definition: \[\[nodiscard\]\] constexpr std::size_t max_size() const noexcept | calls max; returns std::numeric_limits&lt;std::size_t&gt;::max() / sizeof(T) · [reviewed contract](#b0010) |
| [B0011 · 64–64](../../../../../../include/crown/resource/allocator.hpp#L64) | Callable definition: \[\[nodiscard\]\] MemoryAllocator select_on_container_copy_construction() const noexcept | calls ; returns *this · [reviewed contract](#b0011) |
| [B0012 · 65–65](../../../../../../include/crown/resource/allocator.hpp#L65) | Callable definition: \[\[nodiscard\]\] const MemoryAccount& account() const noexcept | calls ; returns account_ · [reviewed contract](#b0012) |
| [B0013 · 66–66](../../../../../../include/crown/resource/allocator.hpp#L66) | Callable definition: \[\[nodiscard\]\] MemoryPurpose purpose() const noexcept | calls ; returns purpose_ · [reviewed contract](#b0013) |
| [B0014 · 67–67](../../../../../../include/crown/resource/allocator.hpp#L67) | Callable definition: \[\[nodiscard\]\] MemoryAttribution attribution() const noexcept | calls ; returns attribution_ · [reviewed contract](#b0014) |
| [B0015 · 68–69](../../../../../../include/crown/resource/allocator.hpp#L68) | Explanatory comments or spacing. | source comment (unverified): // Nonallocating diagnostics for a still-live allocation from this allocator, · [reviewed contract](#b0015) |
| [B0016 · 70–74](../../../../../../include/crown/resource/allocator.hpp#L70) | Callable definition: \[\[nodiscard\]\] MemoryUsage allocation_usage(const T* pointer, std::size_t count) const | calls max_size, MemoryFailure, allocation_usage_raw; returns {}; account_.allocation_usage_raw(pointer, count * sizeof(T), alignof(T), purpose_, attribution_); source comment (unverified): // Nonallocating diagnostics for a still-live allocation from this allocator, · [reviewed contract](#b0016) |
| [B0017 · 75–76](../../../../../../include/crown/resource/allocator.hpp#L75) | Explanatory comments or spacing. | source comment (unverified): // O(1) classification for the exact still-live allocation owned by this · [reviewed contract](#b0017) |
| [B0018 · 77–81](../../../../../../include/crown/resource/allocator.hpp#L77) | Callable definition: void set_allocation_lifetime(T* pointer, std::size_t count, AllocationLifetime lifetime) const | calls max_size, MemoryFailure, set_lifetime_raw; source comment (unverified): // O(1) classification for the exact still-live allocation owned by this · [reviewed contract](#b0018) |
| [B0019 · 82–82](../../../../../../include/crown/resource/allocator.hpp#L82) | Explanatory comments or spacing. |  |
| [B0020 · 83–87](../../../../../../include/crown/resource/allocator.hpp#L83) | Callable definition: template&lt;class U&gt; \[\[nodiscard\]\] bool operator==(const MemoryAllocator&lt;U&gt;& other) const noexcept | returns account_.control_ == other.account_.control_ && purpose_ == other.purpose_ && · [reviewed contract](#b0020) |
| [B0021 · 88–89](../../../../../../include/crown/resource/allocator.hpp#L88) | Callable definition: template&lt;class U&gt; \[\[nodiscard\]\] bool operator!=(const MemoryAllocator&lt;U&gt;& other) const noexcept | returns !(*this == other) · [reviewed contract](#b0021) |
| [B0022 · 90–96](../../../../../../include/crown/resource/allocator.hpp#L90) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0022) |

## B0001

[Lines 1–32](../../../../../../include/crown/resource/allocator.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MemoryAllocator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a nonpropagating standard allocator for state bound to one finite query account. |
| inputs / outputs | Object, nonconst T defines value/count/difference types and false propagation/is-always-equal traits; instances store account, purpose and attribution. |
| invariants | Container copy/move assignment retains its destination allocator; standard-container swap requires equal allocators. Rebinding changes the element type without changing storage authority. |
| ownership | The allocator retains its account; it funds container node/array requests but does not redirect arbitrary nested members or their ordinary allocators. |
| failure | Unsupported T is a compile-time error. An unbound default allocator cannot allocate; the validated constructor establishes a usable bound instance. |
| cost | Fixed metadata per allocator, account-reference work on copies, and no separate registry. Container operations retain their own growth, element and nested-allocation costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0002

[Lines 33–33](../../../../../../include/crown/resource/allocator.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class U> struct rebind
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select this same account-aware allocator family for a different standard-library value type. |
| inputs / outputs | rebind&lt;U&gt;::other names MemoryAllocator&lt;U&gt;. |
| invariants | A rebound instance must be constructed from the original allocator so controller, purpose and attribution remain identical; the type alias alone does not create an account. |
| ownership | Compile-time type mapping owns no storage; the converting constructor supplies retained handle metadata. |
| failure | Invalid rebound T remains subject to the allocator object-type static assertion when instantiated. |
| cost | Compile-time only; no allocation, lookup or per-element wrapper. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0003

[Lines 34–35](../../../../../../include/crown/resource/allocator.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAllocator() noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit an empty standard-container allocator without creating an implicit memory allowance. |
| inputs / outputs | Default construction leaves an empty MemoryAccount, scratch purpose and query:0 attribution. |
| invariants | An empty allocator is a valid handle state, but allocate rejects it even for count zero. |
| ownership | No controller or payload ownership is acquired. |
| failure | Noexcept; a later allocation fails with bad_alloc until a bound allocator is supplied according to the container contract. |
| cost | O(1) member initialization; no upstream allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0004

[Lines 36–42](../../../../../../include/crown/resource/allocator.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit MemoryAllocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a standard-container allocator to one account, purpose and immutable operator attribution. |
| inputs / outputs | A valid account/purpose/attribution construct a rebound-compatible allocator. |
| invariants | No control-purpose allocations, invalid category or invalid attribution. Standard-container assignment uses the declared nonpropagating traits and keeps the destination allocator; assigning an allocator object itself copies its stored account/purpose/attribution. |
| ownership | Copies retain the original account and cap; nested members require their own explicit account routing. |
| failure | Invalid configuration raises fixed MemoryFailure(contract). |
| cost | O(1) account-handle retention and validation; no payload allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0005

[Lines 43–46](../../../../../../include/crown/resource/allocator.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAllocator(const MemoryAllocator&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy allocator metadata while retaining the existing controller. |
| inputs / outputs | Default copy construction/assignment copy account, purpose and attribution; implicit use for rvalues leaves the source usable. |
| invariants | These allocator object operations do not themselves impose container propagation; the false propagation traits control container assignment. |
| ownership | Account copies share the original cap. Replacing an allocator object releases its prior handle after retaining the new account. |
| failure | Noexcept under the single mutating-thread lifetime contract; invalid reference-count states terminate in the account primitive. |
| cost | O(1) reference/metadata work; no payload allocation or fresh allowance. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0006

[Lines 47–49](../../../../../../include/crown/resource/allocator.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAllocator(const MemoryAllocator<U>& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebind allocation authority when the standard library requests another internal value type. |
| inputs / outputs | A MemoryAllocator&lt;U&gt; initializes a MemoryAllocator&lt;T&gt; with the same account, purpose and attribution. |
| invariants | Rebinding preserves exact allocator identity across types; node/control-block allocation remains charged to the original owner. |
| ownership | Retains the same controller; neither copies live container storage nor takes an element pointer. |
| failure | Noexcept handle copy; an empty source remains empty. |
| cost | O(1) metadata and reference-count work, with no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0008

[Lines 51–55](../../../../../../include/crown/resource/allocator.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] T* allocate(std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a standard container allocation to the existing memory account. |
| inputs / outputs | Element count in; correctly aligned unconstructed T storage out. |
| invariants | Check count*sizeof(T) overflow before calling account.allocate_raw. Rebind/equality preserve account, purpose and attribution. |
| ownership | Container owns returned storage and must deallocate with the same allocator/count. Nested member payloads need their own explicit account. |
| failure | Empty allocator and oversized counts reject; account failure propagates. This function does not construct T. |
| cost | Fixed count/size validation plus one account allocation; container growth/rebalancing remains the caller cost. |
| Design | [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 56–60](../../../../../../include/crown/resource/allocator.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deallocate(T* pointer,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a container capacity/node allocation using its original element count. |
| inputs / outputs | A live pointer and exact count call the account raw deallocation bridge; null is a no-op. |
| invariants | The pointer/count/allocator triple must match the original allocation, including purpose and attribution. |
| ownership | Consumes that allocation only; other container/member allocations remain independently owned. |
| failure | Impossible count or ownership mismatch terminates under standard allocator preconditions. |
| cost | O(1) framing/debit plus upstream delete; nonallocating and noexcept. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0010

[Lines 61–63](../../../../../../include/crown/resource/allocator.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] constexpr std::size_t max_size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the count domain that cannot overflow count*sizeof(T). |
| inputs / outputs | Returns size_t maximum divided by sizeof(T). |
| invariants | Byte-framing/limit checks still happen in MemoryAccount after this element-domain bound. |
| ownership | Pure allocator metadata. |
| failure | Noexcept. |
| cost | O(1) constant arithmetic. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0011

[Lines 64–64](../../../../../../include/crown/resource/allocator.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryAllocator select_on_container_copy_construction()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep copies of a container under the original account and attribution. |
| inputs / outputs | Returns a copy of this allocator for standard copy construction. |
| invariants | Copying is not a fresh query allowance; container element allocations may still be necessary. |
| ownership | Retains existing account reference only. |
| failure | Noexcept allocator copy. |
| cost | O(1), no allocation by this hook. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0012

[Lines 65–65](../../../../../../include/crown/resource/allocator.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const MemoryAccount& account() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the allocator account for nested account-aware construction and diagnostics. |
| inputs / outputs | Returns a const reference to this allocator's MemoryAccount member, including an empty default handle. |
| invariants | The accessor does not validate emptiness or create an allocation authority. |
| ownership | The reference borrows the allocator object; copying that account explicitly retains the controller. |
| failure | Noexcept; later operations on an empty returned handle retain their own failure rules. |
| cost | O(1) reference return; no account scan or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0013

[Lines 66–66](../../../../../../include/crown/resource/allocator.hpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryPurpose purpose() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable allocation category carried by this allocator. |
| inputs / outputs | Returns its MemoryPurpose value by copy. |
| invariants | Changing a container's allocation ownership requires its actual allocator protocol; this accessor cannot reclassify existing blocks. |
| ownership | Inline enum value only; no lifetime or account reference escapes. |
| failure | Noexcept, including for a default unbound allocator. |
| cost | O(1) scalar read with no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0014

[Lines 67–67](../../../../../../include/crown/resource/allocator.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryAttribution attribution() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the operator owner key preserved by rebinding and allocator equality. |
| inputs / outputs | Returns the stored MemoryAttribution value by copy. |
| invariants | An attribution partitions one account; it does not define an independent limit or unique process-wide component. |
| ownership | Returned scalar key owns no allocation and retains no controller. |
| failure | Noexcept; constructor validation already applies to bound allocators. |
| cost | O(1) fixed value copy, with no ledger lookup. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0015

[Lines 68–69](../../../../../../include/crown/resource/allocator.hpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L69:sha256:944033142dfea16ae470888df9a27861c3fd7e0dd22a717f11126543569e7f31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] MemoryUsage allocation_usage(const T* pointer, std::size_t count) const\`: Nonallocating diagnostics for a still-live allocation from this allocator, using the exact original element count (a vector passes capacity()). |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/allocator.hpp:L70; use that declaration for the actual input/output shape. |
| invariants | The source note states: Nonallocating diagnostics for a still-live allocation from this allocator, using the exact original element count (a vector passes capacity()). It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Nonallocating diagnostics for a still-live allocation from this allocator, using the exact original element count (a vector passes capacity()). Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Nonallocating diagnostics for a still-live allocation from this allocator, using the exact original element count (a vector passes capacity()). Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0016

[Lines 70–74](../../../../../../include/crown/resource/allocator.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryUsage allocation_usage(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the original request for a container allocation. |
| inputs / outputs | Exact live base pointer/count return MemoryUsage; null with zero count returns zero. |
| invariants | A vector passes capacity(), not size(); arbitrary or expired pointers are outside this adapter contract. |
| ownership | No ownership transfer or caller buffer allocation. |
| failure | Invalid count or metadata raises fixed contract failure after live-pointer preconditions. |
| cost | O(1) checked byte conversion and header access; no account-wide scan. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0017

[Lines 75–76](../../../../../../include/crown/resource/allocator.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L76:sha256:a765069979711aef00472dde3cc26587a06baae7e1e012ed9706cd5fb6f1d597
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void set_allocation_lifetime(T* pointer, std::size_t count, AllocationLifetime lifetime) const\`: O(1) classification for the exact still-live allocation owned by this allocator. No ledger scan, allocation or admission refill. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/allocator.hpp:L77; use that declaration for the actual input/output shape. |
| invariants | The source note states: O(1) classification for the exact still-live allocation owned by this allocator. No ledger scan, allocation or admission refill. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: O(1) classification for the exact still-live allocation owned by this allocator. No ledger scan, allocation or admission refill. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: O(1) classification for the exact still-live allocation owned by this allocator. No ledger scan, allocation or admission refill. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0018

[Lines 77–81](../../../../../../include/crown/resource/allocator.hpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_allocation_lifetime(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify one container backing allocation with an exact live pointer/count. |
| inputs / outputs | Pointer, original count and destination lifetime update the account lifetime partition. |
| invariants | Container capacity allocation is classified as a whole; it does not classify individual initialized elements. |
| ownership | Keeps the same allocator/account/purpose/attribution and allocation. |
| failure | Invalid metadata/lifetime raises fixed resource contract failure; null/zero is a no-op. |
| cost | O(1) direct header classification; no admission refill, new allocation or ledger scan. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0020

[Lines 83–87](../../../../../../include/crown/resource/allocator.hpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const MemoryAllocator<U>& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Determine whether standard containers may exchange/reuse allocator-owned storage. |
| inputs / outputs | Compares control identity, purpose and attribution across rebound value types. |
| invariants | Same cap or owner ID text is insufficient: exact controller/purpose/attribution identity is required. |
| ownership | Borrows allocator metadata; no account copy. |
| failure | Noexcept. |
| cost | Three O(1) equality comparisons; no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0021

[Lines 88–89](../../../../../../include/crown/resource/allocator.hpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator!=(const MemoryAllocator<U>& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Express allocator inequality consistently across rebound element types. |
| inputs / outputs | Returns the negation of equality on controller identity, purpose and attribution. |
| invariants | Two independent accounts with identical configured limits are unequal; differing attribution also prevents storage exchange. |
| ownership | Both allocators are borrowed for the comparison. |
| failure | Noexcept; empty allocators compare using their stored metadata. |
| cost | O(1) metadata comparisons; no allocation or element inspection. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0022

[Lines 90–96](../../../../../../include/crown/resource/allocator.hpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the allocator's exact storage authority beside its classification metadata. |
| inputs / outputs | Private account/purpose/attribution members represent one allocator instance; the default purpose is scratch. |
| invariants | All allocate/deallocate/lookup/classification calls use the same tuple of metadata; equality includes every field. |
| ownership | The account member keeps Control alive independently of containers' raw blocks, which also retain it. |
| failure | Member teardown is noexcept; it cannot repair invalid raw-pointer or allocator-transfer usage. |
| cost | Fixed per-allocator storage and O(1) account-handle release; block destruction belongs to the container. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |
