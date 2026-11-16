# `src/storage/accounted_indexed_nodes.hpp` — block usage map

[Source](../../../../../src/storage/accounted_indexed_nodes.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own native indexed nodes using the exact allocator embedded before destruction.

Snapshot SHA-256: `d91035e1566aad3e7b795f214f1804a8cf8c2598ac027e73734f37e22c223bd5`. 117 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/storage/accounted_indexed_nodes.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Each raw intrusive node carries its exact allocator identity. The stateless · [reviewed contract](#b0001) |
| [B0002 · 14–19](../../../../../src/storage/accounted_indexed_nodes.hpp#L14) | Type/record definition: template&lt;class T&gt; struct IndexedNodeDelete | source comment (unverified): // Each raw intrusive node carries its exact allocator identity. The stateless · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/storage/accounted_indexed_nodes.hpp#L20) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 21–28](../../../../../src/storage/accounted_indexed_nodes.hpp#L21) | Callable definition: template&lt;class T, class... Args&gt; IndexedNodeOwner&lt;T&gt; make_indexed_node(const resource::MemoryAccount& account, resource::MemoryAt… | calls allocator, allocate, std::construct_at, deallocate; returns IndexedNodeOwner&lt;T&gt;(node); growth allocate · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/storage/accounted_indexed_nodes.hpp#L29) | Callable definition: template&lt;class T&gt; void destroy_indexed_node(T* node) noexcept | calls  · [reviewed contract](#b0005) |
| [B0006 · 30–32](../../../../../src/storage/accounted_indexed_nodes.hpp#L30) | Callable definition: template&lt;class T&gt; void classify_indexed_node(T& node, resource::AllocationLifetime lifetime) noexcept | calls set_allocation_lifetime · [reviewed contract](#b0006) |
| [B0007 · 33–36](../../../../../src/storage/accounted_indexed_nodes.hpp#L33) | declares types or opens a type body. |  · [reviewed contract](#b0007) |
| [B0008 · 37–47](../../../../../src/storage/accounted_indexed_nodes.hpp#L37) | Type/record definition: struct AccountedIndexedMember |  · [reviewed contract](#b0008) |
| [B0009 · 48–50](../../../../../src/storage/accounted_indexed_nodes.hpp#L48) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 51–61](../../../../../src/storage/accounted_indexed_nodes.hpp#L51) | Type/record definition: struct AccountedIndexedRow |  · [reviewed contract](#b0010) |
| [B0011 · 62–66](../../../../../src/storage/accounted_indexed_nodes.hpp#L62) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 67–77](../../../../../src/storage/accounted_indexed_nodes.hpp#L67) | Type/record definition: struct AccountedIndexedKey |  · [reviewed contract](#b0012) |
| [B0013 · 78–81](../../../../../src/storage/accounted_indexed_nodes.hpp#L78) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 82–95](../../../../../src/storage/accounted_indexed_nodes.hpp#L82) | Type/record definition: struct AccountedIndexedIndex |  · [reviewed contract](#b0014) |
| [B0015 · 96–98](../../../../../src/storage/accounted_indexed_nodes.hpp#L96) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 99–101](../../../../../src/storage/accounted_indexed_nodes.hpp#L99) | Callable definition: inline AccountedIndexedMember::~AccountedIndexedMember() | calls AccountedRowMembers::detach_prepaid, AccountedBucketMembers::detach_prepaid · [reviewed contract](#b0016) |
| [B0017 · 102–105](../../../../../src/storage/accounted_indexed_nodes.hpp#L102) | Callable definition: inline AccountedIndexedRow::~AccountedIndexedRow() | calls AccountedPrimaryDirectory::detach_prepaid, AccountedRowIdDirectory::detach_prepaid, first, destroy_indexed_node; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 106–112](../../../../../src/storage/accounted_indexed_nodes.hpp#L106) | Callable definition: inline AccountedIndexedKey::~AccountedIndexedKey() | calls AccountedKeyDirectory::detach_prepaid, AccountedLiveKeys::detach_prepaid, first, destroy_indexed_node; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 113–116](../../../../../src/storage/accounted_indexed_nodes.hpp#L113) | Callable definition: inline AccountedIndexedIndex::~AccountedIndexedIndex() | calls AccountedIndexIdDirectory::detach_prepaid, first_resident, destroy_indexed_node; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 117–117](../../../../../src/storage/accounted_indexed_nodes.hpp#L117) | Closes surrounding scope/type. |  · [reviewed contract](#b0020) |

## B0001

[Lines 1–13](../../../../../src/storage/accounted_indexed_nodes.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:cb11f4afdc7246b3d813730f40237674ad8e8db3232245c5aa6d93688dc9d335
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"hash_directory.hpp"\`, \`"live_list.hpp"\`, \`"accounted_pointer_array.hpp"\`, \`"crown/storage/accounted_projection.hpp"\`, \`"crown/resource/allocator.hpp"\`, \`&lt;memory&gt;\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: Each raw intrusive node carries its exact allocator identity. The stateless temporary deleter copies that identity before destruction/deallocation; publication transfers ownership to the real table hooks without a ticket. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Each raw intrusive node carries its exact allocator identity. The stateless temporary deleter copies that identity before destruction/deallocation; publication transfers ownership to the real table hooks without a ticket. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Each raw intrusive node carries its exact allocator identity. The stateless temporary deleter copies that identity before destruction/deallocation; publication transfers ownership to the real table hooks without a ticket. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 14–19](../../../../../src/storage/accounted_indexed_nodes.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct IndexedNodeDelete {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy a native intrusive node using its exact embedded allocator. |
| inputs / outputs | Null pointer is a no-op; nonnull node copies its allocator, destroys the node, then deallocates one object. |
| invariants | Allocator identity must be retained before destroying the member that stores it; node destructor detaches its own hooks. |
| ownership | Stateless deleter adds no allocation ticket or per-node ownership registry. |
| failure | Noexcept cleanup; invalid node/allocator is an internal contract violation. |
| cost | T destructor and fixed framed deallocation; nested row/key/index destruction has its own member population cost. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0003

[Lines 20–20](../../../../../src/storage/accounted_indexed_nodes.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:770e47c9c485634b1098d430f06edb49a3522322f1025c8277598af81dfde269
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 21–28](../../../../../src/storage/accounted_indexed_nodes.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedNodeOwner<T> make_indexed_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate and construct one private native node with strong failure cleanup. |
| inputs / outputs | Account/tag/purpose and constructor arguments yield a unique private node owner. |
| invariants | Construction can throw after raw allocator allocation; cleanup must deallocate that exact raw block before propagation. |
| ownership | Embedded allocator identity funds the node; publication later releases the temporary owner into native table hooks. |
| failure | The catch is necessary constructor cleanup, not redundant translation or ordinary-path exception control flow. |
| cost | One node allocation plus T/nested construction; no separate dynamic deleter ticket. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0005

[Lines 29–29](../../../../../src/storage/accounted_indexed_nodes.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void destroy_indexed_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the shared exact-node destruction protocol to a raw owned node. |
| inputs / outputs | Pointer is consumed by IndexedNodeDelete. |
| invariants | Caller owns this node and must not use it afterward. |
| ownership | No replacement owner or allocation. |
| failure | Noexcept cleanup. |
| cost | Actual node/nested destructor cost plus direct framed deallocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0006

[Lines 30–32](../../../../../src/storage/accounted_indexed_nodes.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void classify_indexed_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Change an existing node allocation lifetime through its direct allocator header. |
| inputs / outputs | Valid T reference and AllocationLifetime update original-account accounting. |
| invariants | The node allocator and one-element framing identify the existing block; no containing-pointer search is required. |
| ownership | Payload and hook ownership stay unchanged. |
| failure | Noexcept internal prepared-phase contract. |
| cost | O(1) direct block classification, no ledger scan, allocation or grant refill. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0007

[Lines 33–36](../../../../../src/storage/accounted_indexed_nodes.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L36:sha256:d1c754e5d4aeec9f4814e10572f49d5d2fb8f13de09a4141ff6c2b214b166615
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: forward-declares \`struct AccountedIndexedRow\`, \`struct AccountedIndexedKey\`, \`struct AccountedIndexedIndex\` without defining object layout. |
| inputs / outputs | Compile-time consumers may name \`struct AccountedIndexedRow\`, \`struct AccountedIndexedKey\`, \`struct AccountedIndexedIndex\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 37–47](../../../../../src/storage/accounted_indexed_nodes.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedMember {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one row-to-index/key membership with two independent intrusive hooks. |
| inputs / outputs | Allocator plus row/index/key pointers create an initially detached row-link and bucket-link node. |
| invariants | One member belongs to one row/index/key triple; each hook serves a different list and cannot be substituted. |
| ownership | Table/private preparation owns the node; its raw pointers borrow stable row/index/key nodes. |
| failure | Construction is noexcept after allocator admission; destructor detaches both actual hook owners. |
| cost | Fixed pointer/hook metadata per membership; no duplicated row/key payload. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0009

[Lines 48–50](../../../../../src/storage/accounted_indexed_nodes.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:9b3a55e38a4912a0a3eb9eec9f90c5ac80f239559015faa20e66c42907165cba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: imports or aliases \`AccountedRowMembers = LiveList&lt;AccountedIndexedMember, &AccountedIndexedMember::row_link, FixedIndexErrors&gt;\`, \`AccountedBucketMembers = LiveList&lt;AccountedIndexedMember, &AccountedIndexedMember::bucket_link, FixedIndexErrors&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 51–61](../../../../../src/storage/accounted_indexed_nodes.hpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedRow {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one stable logical-ID row and reverse membership list. |
| inputs / outputs | Allocator, logical ID and maximum indices create detached primary/identity hooks and empty row-members list. |
| invariants | Arena allocation/tuple pointer are populated before public linking; cached primary and numeric-ID directory hashes have separate hooks. |
| ownership | Row node owns its member nodes when linked; arena owns payload and pins may retain it independently. |
| failure | Noexcept metadata construction; destruction detaches both directories before releasing members. |
| cost | Fixed row node plus O(indices) membership nodes; no sparse ID-indexed row array. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0011

[Lines 62–66](../../../../../src/storage/accounted_indexed_nodes.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L66:sha256:950c99bc9ef4027144e53536f1b7d4e48e05200d98ecf2e6d028d08e9421db41
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: imports or aliases \`AccountedPrimaryDirectory = HashDirectory&lt;AccountedIndexedRow, &AccountedIndexedRow::primary_link, resource::MemoryAllocator&lt;AccountedIndexedRow*&gt;, FixedIndexErrors, AccountedPointerArray&lt;AccountedIndexedRow&gt;&gt;\`, \`AccountedRowIdDirectory = HashDirectory&lt;AccountedIndexedRow, &AccountedIndexedRow::identity_link, resource::MemoryAllocator&lt;AccountedIndexedRow*&gt;, FixedIndexErrors, AccountedPointerArray&lt;AccountedIndexedRow&gt;&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0012

[Lines 67–77](../../../../../src/storage/accounted_indexed_nodes.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a stable typed key with resident, live-key and member relationships. |
| inputs / outputs | Allocator, owning native tuple and maximum row population initialize detached key/live hooks and empty bucket members. |
| invariants | Directory residency can persist with zero members while journal_references is positive; live-key membership means members are nonempty. |
| ownership | Key owns its tuple payload; journals retain node authority by reference count, not deep key copies. |
| failure | Noexcept ownership moves after preparation; destructor distinguishes row-owned members from privately owned construction members. |
| cost | Fixed key metadata plus owning key fields/deep bytes and membership nodes; no annotation/zero-key sentinel. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0013

[Lines 78–81](../../../../../src/storage/accounted_indexed_nodes.hpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L81:sha256:d856c46ad95369628a84f940e2d0ff2cf5543ad07fe16b3e0f020e3c91007116
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: imports or aliases \`AccountedKeyDirectory = HashDirectory&lt;AccountedIndexedKey, &AccountedIndexedKey::lookup_link, resource::MemoryAllocator&lt;AccountedIndexedKey*&gt;, FixedIndexErrors, AccountedPointerArray&lt;AccountedIndexedKey&gt;&gt;\`, \`AccountedLiveKeys = LiveList&lt;AccountedIndexedKey, &AccountedIndexedKey::live_link, FixedIndexErrors&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0014

[Lines 82–95](../../../../../src/storage/accounted_indexed_nodes.hpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedIndex {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one projection descriptor and its key directory/live-key order. |
| inputs / outputs | Allocator, IndexId, immutable projection and finite slot/key limits create initially detached index identity. |
| invariants | Resident keys and live-key list serve different populations; projection descriptor can be shared but mutable keys are private to this index. |
| ownership | Index node owns all resident key nodes and native directory capacity under the same account/tag. |
| failure | Noexcept initial metadata moves; later growth/node allocations occur while private or under admitted mutation preparation. |
| cost | Fixed index node plus actual key-directory capacity/key/member population; no second query account. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0015

[Lines 96–98](../../../../../src/storage/accounted_indexed_nodes.hpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L98:sha256:07f092ac020fa38271d0b3ee500b1b36a76cd25e79ce85322aaf0b7101a34c28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_nodes.hpp: imports or aliases \`AccountedIndexIdDirectory = HashDirectory&lt;AccountedIndexedIndex, &AccountedIndexedIndex::identity_link, resource::MemoryAllocator&lt;AccountedIndexedIndex*&gt;, FixedIndexErrors, AccountedPointerArray&lt;AccountedIndexedIndex&gt;&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0016

[Lines 99–101](../../../../../src/storage/accounted_indexed_nodes.hpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AccountedIndexedMember::~AccountedIndexedMember()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach exactly this membership from row and bucket lists before deallocation. |
| inputs / outputs | Existing hook owner pointers select actual list owners; an unlinked hook is a no-op. |
| invariants | It does not search for a key/member or rely on possibly retired row/key payload values. |
| ownership | Enclosing row/index/private owner determines when node destruction is safe. |
| failure | Nonallocating destruction; invalid prepaid link invariants terminate. |
| cost | O(1) pointer unlink operations. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0017

[Lines 102–105](../../../../../src/storage/accounted_indexed_nodes.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AccountedIndexedRow::~AccountedIndexedRow()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unlink row identity and destroy its reverse membership nodes. |
| inputs / outputs | Detach primary/ID hooks then repeatedly destroy first row member. |
| invariants | Hook owners remain alive during table teardown; member destructor removes its bucket hook too. |
| ownership | Releases row-owned member nodes; arena tuple allocation is managed separately. |
| failure | Nonallocating destruction under valid owner graph. |
| cost | O(row memberships), no directory capacity or payload scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0018

[Lines 106–112](../../../../../src/storage/accounted_indexed_nodes.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AccountedIndexedKey::~AccountedIndexedKey()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unlink key residency/liveness and release or detach remaining bucket members. |
| inputs / outputs | Detach key directory/live hooks, then destroy row-owned members or only detach members still owned by private preparation. |
| invariants | A privately owned member must not be deleted twice merely because its temporary key disappears; row_link ownership discriminates this case. |
| ownership | Owning tuple/deep payload releases with key; native member owners remain authoritative. |
| failure | Nonallocating destructor; impossible owner graph is outside user-input recovery. |
| cost | O(bucket members) unlink/destruction plus last-owned key payload release. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0019

[Lines 113–116](../../../../../src/storage/accounted_indexed_nodes.hpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AccountedIndexedIndex::~AccountedIndexedIndex()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach index identity and destroy its resident key graph. |
| inputs / outputs | Remove identity hook and repeatedly destroy first resident key. |
| invariants | Resident traversal avoids scanning directory capacity and includes undo-retained keys when allowed by the surrounding lifetime. |
| ownership | Destroys actual owned key/member/tuple allocations before its directory storage disappears. |
| failure | Nonallocating teardown; callers pre-admit operational drop work before entering this destructor. |
| cost | O(resident keys and affected memberships/deep payload destruction), not logical key-ID high-water. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0020

[Lines 117–117](../../../../../src/storage/accounted_indexed_nodes.hpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L117:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/accounted_indexed_nodes.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
