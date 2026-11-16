# `src/storage/accounted_pointer_array.hpp` — block usage map

[Source](../../../../../src/storage/accounted_pointer_array.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `da3eb6549658f65c16ccd4f437b119d2df07a32df8cbce52684fbfb0a53c3182`. 52 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/storage/accounted_pointer_array.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Directory slots have trivial lifetimes. Releasing their actual allocation · [reviewed contract](#b0001) |
| [B0002 · 15–16](../../../../../src/storage/accounted_pointer_array.hpp#L15) | Callable definition: public: explicit AccountedPointerArray(const resource::MemoryAllocator&lt;Node*&gt;& allocator) noexcept : allocator_(allocator) | calls allocator_ · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../src/storage/accounted_pointer_array.hpp#L17) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 19–20](../../../../../src/storage/accounted_pointer_array.hpp#L19) | Callable definition: AccountedPointerArray(AccountedPointerArray&& other) noexcept : allocator_(other.allocator_), block_(std::move(other.block_)), si… | calls allocator_, block_, std::move, size_ · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../src/storage/accounted_pointer_array.hpp#L21) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../src/storage/accounted_pointer_array.hpp#L22) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls ; returns size_ == 0 · [reviewed contract](#b0006) |
| [B0007 · 23–23](../../../../../src/storage/accounted_pointer_array.hpp#L23) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns size_ · [reviewed contract](#b0007) |
| [B0008 · 24–24](../../../../../src/storage/accounted_pointer_array.hpp#L24) | Callable definition: \[\[nodiscard\]\] std::size_t capacity() const noexcept | calls ; returns size_ · [reviewed contract](#b0008) |
| [B0009 · 25–25](../../../../../src/storage/accounted_pointer_array.hpp#L25) | Callable definition: \[\[nodiscard\]\] constexpr std::size_t max_size() const noexcept | calls max; returns std::numeric_limits&lt;std::size_t&gt;::max() / sizeof(Node*) · [reviewed contract](#b0009) |
| [B0010 · 26–26](../../../../../src/storage/accounted_pointer_array.hpp#L26) | Callable definition: \[\[nodiscard\]\] Node** data() noexcept | calls ; returns static_cast&lt;Node**&gt;(block_.data()) · [reviewed contract](#b0010) |
| [B0011 · 27–27](../../../../../src/storage/accounted_pointer_array.hpp#L27) | Callable definition: \[\[nodiscard\]\] Node* const* data() const noexcept | calls ; returns static_cast&lt;Node* const*&gt;(block_.data()) · [reviewed contract](#b0011) |
| [B0012 · 28–28](../../../../../src/storage/accounted_pointer_array.hpp#L28) | Callable definition: Node*& operator\[\](std::size_t i) noexcept | calls ; returns data()\[i\] · [reviewed contract](#b0012) |
| [B0013 · 29–29](../../../../../src/storage/accounted_pointer_array.hpp#L29) | Callable definition: Node* const& operator\[\](std::size_t i) const noexcept | calls ; returns data()\[i\] · [reviewed contract](#b0013) |
| [B0014 · 30–30](../../../../../src/storage/accounted_pointer_array.hpp#L30) | Callable definition: \[\[nodiscard\]\] auto get_allocator() const noexcept | calls ; returns allocator_ · [reviewed contract](#b0014) |
| [B0015 · 31–39](../../../../../src/storage/accounted_pointer_array.hpp#L31) | Callable definition: void assign(std::size_t count, Node* value) | calls max_size, resource::MemoryFailure, reset, account; growth allocate; source comment (unverified): // Keep the old block until every replacement slot is initialized; · [reviewed contract](#b0015) |
| [B0016 · 40–41](../../../../../src/storage/accounted_pointer_array.hpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Compatibility includes account, purpose and attribution; slots never · [reviewed contract](#b0016) |
| [B0017 · 42–45](../../../../../src/storage/accounted_pointer_array.hpp#L42) | Callable definition: void swap(AccountedPointerArray& other) noexcept | calls std::terminate, std::swap; source comment (unverified): // Compatibility includes account, purpose and attribution; slots never · [reviewed contract](#b0017) |
| [B0018 · 46–52](../../../../../src/storage/accounted_pointer_array.hpp#L46) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_destructible_v&lt;Node*&gt;); · [reviewed contract](#b0018) |

## B0001

[Lines 1–14](../../../../../src/storage/accounted_pointer_array.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Node> class AccountedPointerArray {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a funded trivial pointer-slot block while borrowing all pointee nodes. |
| inputs / outputs | Provides the small vector-like interface needed by HashDirectory: size/capacity/data/index/get_allocator/assign/swap. |
| invariants | Slot size equals capacity. HashDirectory admits initialization work before assign; capacity is not live population. Copy/move-assignment are deleted so ownership cannot be silently duplicated/rebound. |
| ownership | Allocator retains the original account identity; one MemoryBlock owns slots and its real framing. Node deletion belongs to enclosing row/key/index/State owners. |
| failure | assign may fail before replacement, swap terminates for incompatible allocators, unchecked indexing requires bounds. No per-slot exception or recovery framework exists. |
| cost | Creation/move/release is fixed block metadata work; assign initializes O(count) pointers and peaks with old+new blocks. Releasing trivial slot storage does not walk sparse capacity. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–16](../../../../../src/storage/accounted_pointer_array.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AccountedPointerArray(const resource::MemoryAllocator<Node*>& allocator) noexcept : allocator_(allocator) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a nonowning pointer-slot array to an existing allocation identity. |
| inputs / outputs | Constructor copies MemoryAllocator&lt;Node*&gt;; no slot block is allocated and size_ starts zero. |
| invariants | Account, purpose and attribution are retained exactly; this is not a new memory account or independent grant. |
| ownership | Allocator retains the query controller; the array owns only its later MemoryBlock, never pointed-to nodes. |
| failure | Constructor is noexcept; allocation is deferred to assign. |
| cost | Fixed allocator-handle retention, no pointer initialization, node traversal or heap allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–18](../../../../../src/storage/accounted_pointer_array.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:93035640a8598466c45adbb88a9f1fd50333466b4ade82a193b841014095fde4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_pointer_array.hpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 19–20](../../../../../src/storage/accounted_pointer_array.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedPointerArray(AccountedPointerArray&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move an existing pointer-slot block without walking slots. |
| inputs / outputs | Moves MemoryBlock, copies the allocator identity and exchanges source size_ to zero. |
| invariants | Source keeps a valid allocator handle but no slot block/count; move assignment is deliberately deleted. |
| ownership | Transfers slot-allocation ownership only. Neither array owns Node pointees. |
| failure | Noexcept; no allocator compatibility check is needed for this new-object construction. |
| cost | Fixed block/account-handle moves; no slot or node walk, allocation or deep copy. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 21–21](../../../../../src/storage/accounted_pointer_array.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:028f15143065cb4340c8f576e8baa084c52b35cfe0114b67b39683be423adee8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_pointer_array.hpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0006

[Lines 22–22](../../../../../src/storage/accounted_pointer_array.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept { return size_ == 0; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the initialized pointer-slot array is empty. |
| inputs / outputs | Returns size_==0. |
| invariants | Empty means no slot block after the supported constructors/assign paths; it says nothing about node populations managed elsewhere. |
| ownership | Returns inline metadata only; array/block/controller ownership is unchanged. |
| failure | The operation is noexcept and performs no validation/translation. |
| cost | Fixed scalar read or compile-time constant arithmetic; no scan or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 23–23](../../../../../src/storage/accounted_pointer_array.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t size() const noexcept { return size_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read initialized directory slot count. |
| inputs / outputs | Returns size_. |
| invariants | This size counts allocated/initialized slots, not resident nodes or logical IDs. |
| ownership | Returns inline metadata only; array/block/controller ownership is unchanged. |
| failure | The operation is noexcept and performs no validation/translation. |
| cost | Fixed scalar read or compile-time constant arithmetic; no scan or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 24–24](../../../../../src/storage/accounted_pointer_array.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t capacity() const noexcept { return size_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact retained slot capacity. |
| inputs / outputs | Returns size_; this array has no spare capacity beyond its initialized slot count. |
| invariants | Live node count, slot capacity and real allocator bytes are separate quantities. |
| ownership | Returns inline metadata only; array/block/controller ownership is unchanged. |
| failure | The operation is noexcept and performs no validation/translation. |
| cost | Fixed scalar read or compile-time constant arithmetic; no scan or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 25–25](../../../../../src/storage/accounted_pointer_array.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] constexpr std::size_t max_size() const noexcept { return std::numeric_limits<std::size_t>::max() / sizeof(Node*); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the arithmetic upper bound for representable pointer-slot requests. |
| inputs / outputs | Returns SIZE_MAX/sizeof(Node*). |
| invariants | Actual account framing, host allocation limits and quota can reject smaller requests; max_size is not an admission promise. |
| ownership | Returns inline metadata only; array/block/controller ownership is unchanged. |
| failure | The operation is noexcept and performs no validation/translation. |
| cost | Fixed scalar read or compile-time constant arithmetic; no scan or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 26–26](../../../../../src/storage/accounted_pointer_array.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Node** data() noexcept { return static_cast<Node**>(block_.data()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow mutable access to the actual directory slot block. |
| inputs / outputs | Casts MemoryBlock::data() to the correct Node-pointer array type; empty data is null. |
| invariants | The address is stable for this exact block's lifetime. Move/swap transfers its owner without relocating slots; replacing/freeing that block invalidates its borrows. Pointees remain independently owned. |
| ownership | The returned pointer does not retain block/controller/pointee lifetime. |
| failure | Noexcept pointer access; callers must respect actual size and lifetime. |
| cost | Fixed pointer cast/read, no slot traversal or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 27–27](../../../../../src/storage/accounted_pointer_array.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Node* const* data() const noexcept { return static_cast<Node* const*>(block_.data()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow const access to the actual directory slot block. |
| inputs / outputs | Casts MemoryBlock::data() to the correct Node-pointer array type; empty data is null. |
| invariants | The address is stable for this exact block's lifetime. Move/swap transfers its owner without relocating slots; replacing/freeing that block invalidates its borrows. Pointees remain independently owned. |
| ownership | The returned pointer does not retain block/controller/pointee lifetime. |
| failure | Noexcept pointer access; callers must respect actual size and lifetime. |
| cost | Fixed pointer cast/read, no slot traversal or allocation. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 28–28](../../../../../src/storage/accounted_pointer_array.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Node*& operator[](std::size_t i) noexcept { return data()[i]; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index one existing mutable directory slot without a bounds check. |
| inputs / outputs | Returns data()\[i\] as a Node-pointer reference; valid index is 0&lt;=i&lt;size_. |
| invariants | Caller supplies a live block and in-range index. Reading/writing a slot never transfers ownership of its Node pointee. |
| ownership | The reference borrows this exact slot block. Moves/swaps transfer ownership without relocating bytes; replacing/freeing that block invalidates access. No retaining owner is created. |
| failure | Noexcept; out-of-range or expired access violates its precondition rather than throwing. |
| cost | One direct pointer-slot access; no lookup, scan, allocation or work admission. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 29–29](../../../../../src/storage/accounted_pointer_array.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Node* const& operator[](std::size_t i) const noexcept { return data()[i]; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index one existing const directory slot without a bounds check. |
| inputs / outputs | Returns data()\[i\] as a Node-pointer reference; valid index is 0&lt;=i&lt;size_. |
| invariants | Caller supplies a live block and in-range index. Reading/writing a slot never transfers ownership of its Node pointee. |
| ownership | The reference borrows this exact slot block. Moves/swaps transfer ownership without relocating bytes; replacing/freeing that block invalidates access. No retaining owner is created. |
| failure | Noexcept; out-of-range or expired access violates its precondition rather than throwing. |
| cost | One direct pointer-slot access; no lookup, scan, allocation or work admission. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 30–30](../../../../../src/storage/accounted_pointer_array.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] auto get_allocator() const noexcept { return allocator_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the exact allocator identity for compatible replacement storage. |
| inputs / outputs | get_allocator returns a copy with the same account, purpose and attribution. |
| invariants | Copies do not reserve bytes, change classification or create another query budget. |
| ownership | Returned allocator retains the existing account controller independently of the slot block. |
| failure | Noexcept handle copy; future allocation uses normal account checks. |
| cost | Fixed allocator/shared-controller copy; no block allocation or node traversal. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 31–39](../../../../../src/storage/accounted_pointer_array.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void assign(std::size_t count, Node* value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace initialized pointer slots only after complete funded preparation. |
| inputs / outputs | assign checks count multiplication, releases on count==0, otherwise allocates count*sizeof(Node*) and uninitialized-fills every pointer before replacing block_/size_. |
| invariants | Node* has trivial/nothrow initialization and destruction. Failure before replacement leaves the old block/count intact; no catch is needed after allocation. |
| ownership | Owns the new slot MemoryBlock and releases old slot storage after fill. Old and new requests coexist at peak; neither block owns the pointed-to Nodes. |
| failure | Too-large count throws MemoryFailure(overflow); account/allocator failure propagates. Zero assignment is a direct noexcept block release within this function. |
| cost | O(count) slot initialization plus one real funded request. Old/zero/final slot release does not walk sparse capacity or destroy pointees; HashDirectory separately admits initialization work before calling. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 40–41](../../../../../src/storage/accounted_pointer_array.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L41:sha256:65532174c2271fecd138a6364db930f2f55a6fdd2b98e336f60bb5d155fe45f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void swap(AccountedPointerArray& other) noexcept\`: Compatibility includes account, purpose and attribution; slots never adopt ownership of the Node objects they point to. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_pointer_array.hpp:L42; use that declaration for the actual input/output shape. |
| invariants | The source note states: Compatibility includes account, purpose and attribution; slots never adopt ownership of the Node objects they point to. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Compatibility includes account, purpose and attribution; slots never adopt ownership of the Node objects they point to. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0017

[Lines 42–45](../../../../../src/storage/accounted_pointer_array.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void swap(AccountedPointerArray& other) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Swap only identically funded slot blocks without allocation. |
| inputs / outputs | Requires equal allocator account/purpose/attribution, then swaps block_ and size_. |
| invariants | Swapping different allocation identities terminates, preserving allocator/header ownership assumptions; no silent account migration is permitted. |
| ownership | Each object adopts the other compatible slot block; pointed-to node ownership is untouched. |
| failure | Noexcept; incompatible allocators fail fast with terminate rather than a throwing partial swap. |
| cost | Fixed allocator comparison and block/count moves, with no slot scan, allocation, payload copy or grant reset. |
| Design | [src/storage/accounted_pointer_array.hpp](../../../../../src/storage/accounted_pointer_array.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 46–52](../../../../../src/storage/accounted_pointer_array.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L52:sha256:85eeea74d47eb3b38aed45058f03554986b8a15d0fb5b302a92fad6bfde6d29c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_pointer_array.hpp: closes \`class Node\`, \`namespace crown::storage::detail\` Member/state declarations in this range include \`resource::MemoryAllocator&lt;Node*&gt; allocator_\`; \`resource::MemoryBlock block_\`; \`std::size_t size_ = 0\`. |
| inputs / outputs | This span declares/carries these members or local values: \`resource::MemoryAllocator&lt;Node*&gt; allocator_\`; \`resource::MemoryBlock block_\`; \`std::size_t size_ = 0\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
