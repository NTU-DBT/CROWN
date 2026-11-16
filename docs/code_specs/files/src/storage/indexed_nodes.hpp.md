# `src/storage/indexed_nodes.hpp` — block usage map

[Source](../../../../../src/storage/indexed_nodes.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define separately owned row/key/member nodes and their directory/live-list hooks.

Snapshot SHA-256: `9b9eb13ba492f17a32dd08c8543b9026f516af08eaed38f907f5efab83f07e97`. 108 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/storage/indexed_nodes.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Parent pointers and hooks borrow; the row or a private prepared owner · [reviewed contract](#b0001) |
| [B0002 · 17–27](../../../../../src/storage/indexed_nodes.hpp#L17) | Type/record definition: struct IndexedMember | source comment (unverified): // Parent pointers and hooks borrow; the row or a private prepared owner · [reviewed contract](#b0002) |
| [B0003 · 28–30](../../../../../src/storage/indexed_nodes.hpp#L28) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 31–41](../../../../../src/storage/indexed_nodes.hpp#L31) | Type/record definition: struct IndexedRow | source comment (unverified): // Installed only after tuple-arena preparation. · [reviewed contract](#b0004) |
| [B0005 · 42–44](../../../../../src/storage/indexed_nodes.hpp#L42) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 45–54](../../../../../src/storage/indexed_nodes.hpp#L45) | Type/record definition: struct IndexedKey | source comment (unverified): // Borrows row-owned or privately staged nodes. · [reviewed contract](#b0006) |
| [B0007 · 55–57](../../../../../src/storage/indexed_nodes.hpp#L55) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 58–69](../../../../../src/storage/indexed_nodes.hpp#L58) | Type/record definition: struct IndexedIndex | source comment (unverified): // Owns every resident key, including private empty keys. · [reviewed contract](#b0008) |
| [B0009 · 70–71](../../../../../src/storage/indexed_nodes.hpp#L70) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 72–77](../../../../../src/storage/indexed_nodes.hpp#L72) | Callable definition: inline IndexedMember::~IndexedMember() | calls RowMembers::detach_prepaid, BucketMembers::detach_prepaid; source comment (unverified): // Use each hook's actual surviving owner. key/index pointers may already be · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../src/storage/indexed_nodes.hpp#L78) | Explanatory comments or spacing. |  |
| [B0012 · 79–85](../../../../../src/storage/indexed_nodes.hpp#L79) | Callable definition: inline IndexedRow::~IndexedRow() | calls PrimaryDirectory::detach_prepaid, RowIdDirectory::detach_prepaid, first; 1 loop sites; source comment (unverified): // The table's arena owns tuple payloads; this never copies/frees a borrowed · [reviewed contract](#b0012) |
| [B0013 · 86–86](../../../../../src/storage/indexed_nodes.hpp#L86) | Explanatory comments or spacing. |  |
| [B0014 · 87–101](../../../../../src/storage/indexed_nodes.hpp#L87) | Callable definition: inline IndexedKey::~IndexedKey() | calls KeyDirectory::detach_prepaid, LiveKeys::detach_prepaid, first, erase_prepaid; 1 loop sites; source comment (unverified): // Row-owned members are released and removed from both lists. No row or · [reviewed contract](#b0014) |
| [B0015 · 102–102](../../../../../src/storage/indexed_nodes.hpp#L102) | Explanatory comments or spacing. |  |
| [B0016 · 103–106](../../../../../src/storage/indexed_nodes.hpp#L103) | Callable definition: inline IndexedIndex::~IndexedIndex() | calls IndexIdDirectory::detach_prepaid, first_resident; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 107–108](../../../../../src/storage/indexed_nodes.hpp#L107) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0017) |

## B0001

[Lines 1–16](../../../../../src/storage/indexed_nodes.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:a95d2db762e831adb2d5cc8a345f252ebf3feafbfdf36eef796297d6c0506bf7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/indexed_nodes.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"hash_directory.hpp"\`, \`"live_list.hpp"\`, \`"crown/storage/layout.hpp"\`, \`&lt;cstddef&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage::detail\`; forward-declares \`struct IndexedRow\`, \`struct IndexedKey\`, \`struct IndexedIndex\` without defining object layout. Source comment: Parent pointers and hooks borrow; the row or a private prepared owner controls deletion. Hooks retain their actual surviving list owner. |
| inputs / outputs | Compile-time consumers may name \`struct IndexedRow\`, \`struct IndexedKey\`, \`struct IndexedIndex\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. The source note says: Parent pointers and hooks borrow; the row or a private prepared owner controls deletion. Hooks retain their actual surviving list owner. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Parent pointers and hooks borrow; the row or a private prepared owner controls deletion. Hooks retain their actual surviving list owner. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 17–27](../../../../../src/storage/indexed_nodes.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedMember {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect one row to one secondary bucket through two independent hooks. |
| inputs / outputs | IndexedMember stores row/index/key pointers and row_link/bucket_link; constructor binds pointers and destructor detaches the actual hook owners. |
| invariants | The pointers are borrows. Privately staged members can be uniquely owned before row publication and can outlive a detached key pointer during failed-build cleanup. |
| ownership | Once published, the enclosing row owns member deletion. A key bucket only borrows membership; neither hook owns a row/index/key. |
| failure | Constructor is noexcept; callers fund/prepare allocation and links first. Destructor performs prepaid no-throw detachment, never parent-pointer-based ownership recovery. |
| cost | Fixed pointer/hook record; actual new/delete occurs at enclosing builders/destructors. Detachment has at most two fixed hook operations, not a node registry lookup. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  IndexedRow* row;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the three parent identities of one membership node. |
| inputs / outputs | row/index/key identify the enclosing logical row, compiled index and projected key; constructor binds all three before links publish. |
| invariants | These raw pointers do not supply deletion authority and may not be dereferenced to find surviving hook owners during failed private-build cleanup. |
| ownership | Each pointer borrows its parent while used; a row or independent prepared unique owner controls this member's deletion. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Three pointer fields and fixed initialization/read; no owning reference count, registry lookup or payload copy. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  LiveListHook<IndexedMember> row_link;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep row ownership membership separate from the key's bucket borrow. |
| inputs / outputs | row_link records membership in IndexedRow::members and bucket_link records membership in IndexedKey::members. |
| invariants | Each hook stores its own actual owner/neighbors. A null row_link with a bucket link denotes a privately staged borrow whose independent unique owner must not be deleted by the key. |
| ownership | Hooks own links only. The enclosing row deletes published members; a bucket independently borrows the same node. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Fixed inline hook state; caller-admitted attach/detach updates a bounded set of pointers. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 28–30](../../../../../src/storage/indexed_nodes.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using RowMembers =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a row's nonowning hook list whose enclosing row deletes its members. |
| inputs / outputs | Binds LiveList to IndexedMember::row_link; destructor ownership is enforced by IndexedRow, not by the LiveList template itself. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | The list owns link metadata only; its enclosing row performs actual node deletion. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
using BucketMembers =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a projected key's borrowed member-hook list. |
| inputs / outputs | Binds LiveList to IndexedMember::bucket_link; members may be row-owned or privately staged. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | Bucket links retain no independent member owner and must be detached before that owner disappears. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 31–41](../../../../../src/storage/indexed_nodes.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedRow {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a logical row's membership nodes while borrowing arena payload. |
| inputs / outputs | IndexedRow holds TupleId, generational ArenaHandle, borrowed const Tuple*, two directory hooks and a row member list. |
| invariants | Arena allocation/tuple pointer are installed after preparation; the row does not free/copy the borrowed Tuple or modify arena membership in its destructor. |
| ownership | The State owns row-node deletion, the arena owns tuple payload, and the row destructor iteratively deletes linked member nodes. Directory hooks remain nonowning. |
| failure | Constructor is noexcept; caller validates/prepares IDs/limits/payload. Destruction must occur while hook owners remain valid. |
| cost | Fixed metadata construction; destruction costs actual member unlink/deletion plus nonowning directory detachment, without scanning logical tuple-ID high-water. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  ArenaHandle allocation{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record arena identity and a stable borrowed payload address on a row node. |
| inputs / outputs | allocation and tuple are installed after arena preparation; tuple points to the immutable arena Tuple associated with that generational handle. |
| invariants | A row-node destructor must not delete tuple or erase arena membership. Table publication/rollback handles the arena boundary separately. |
| ownership | The arena owns payload; row stores only a generational handle and borrowed pointer. Explicit pins, not these fields, retain erased payload. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Fixed fields; no deep value copy, pin acquisition or arena traversal when reading them. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  HashDirectoryHook<IndexedRow> primary_link;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use independent hooks for row-value lookup and logical-ID lookup. |
| inputs / outputs | primary_link caches row-value hash and resident order; identity_link uses numeric TupleId hash/identity on the same stable node. |
| invariants | Detaching one directory membership does not authorize destroying the other directory or replacing the node address. Cached hash survives detachment for undo. |
| ownership | Both directory hooks borrow their actual directory owners; State owns row deletion and the arena owns payload. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Fixed inline metadata; successful prepaid detach is bounded pointer work and never rehashes payload. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  RowMembers members;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the member nodes explicitly owned by a row. |
| inputs / outputs | The row member list reaches exactly this row's memberships, which its destructor deletes iteratively. |
| invariants | LiveList itself has a default nonowning destructor; deletion authority comes from IndexedRow's explicit loop, not the alias or hook type. |
| ownership | The row owns linked member nodes. Each corresponding key bucket is a borrow and is detached by the member destructor. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | A first-link read is fixed; complete row cleanup costs the actual number of member nodes and their releases. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 42–44](../../../../../src/storage/indexed_nodes.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using PrimaryDirectory =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the row-value hash-directory hook without owning row deletion. |
| inputs / outputs | Binds HashDirectory to IndexedRow::primary_link; cached hashes and exact tuple equality resolve membership. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | Directory owns pointer-slot storage, while table State owns row nodes and the arena owns payload. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
using RowIdDirectory =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name independent numeric logical-row lookup membership. |
| inputs / outputs | Binds HashDirectory to IndexedRow::identity_link; same node can be in both directories. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | ID directory hook is independent and nonowning; row destructor detaches both memberships. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 45–54](../../../../../src/storage/indexed_nodes.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one projected key value and borrow its member bucket. |
| inputs / outputs | IndexedKey adopts a Tuple, stores lookup/live hooks, journal_references and a bounded BucketMembers list. |
| invariants | Zero numeric key/hash is valid. Public liveness follows nonempty membership/live hook; journal references can retain empty key residency. |
| ownership | Index owner deletes the key. The key owns its Tuple payload/descriptor; bucket links borrow row-owned or privately staged members rather than adopting every linked raw pointer. |
| failure | The constructor body is noexcept after by-value Tuple preparation; an lvalue argument copy can fail before entry. Destructor distinguishes row-owned members from staged borrows. |
| cost | Fixed metadata and Tuple move in construction. Key release destroys its owned payload as representation requires; bucket cleanup visits actual members, without recursively deleting rows/neighboring keys. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  Tuple tuple;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a projected key's immutable value payload. |
| inputs / outputs | The key adopts an already constructed Tuple whose layout is the exact projection target token. |
| invariants | The value/hash/annotation zero is never an empty-key sentinel; residency/liveness are separate hook/member facts. |
| ownership | Tuple owns ordinary legacy payload or shares its existing native-funded immutable payload and metadata according to representation. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Construction moves an existing owner; explicit earlier projection/copy and final payload release retain actual scalar/string/control costs. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  std::size_t journal_references = 0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain empty projected keys for exact journal inverse history. |
| inputs / outputs | Counts active undo references to this key while member population may be zero. |
| invariants | Counter room is checked before publication; zero references and zero members allow actual key release. The count is not row multiplicity or public key liveness. |
| ownership | Inline count alone owns nothing; journal undo records and index residency provide actual owner lifetimes. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Fixed count reads/updates with externally prepared overflow/capacity checks; no per-reference owner registry. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  BucketMembers members;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow row-owned or privately staged members from one projected key. |
| inputs / outputs | This list maintains bucket order and current degree while row hooks independently represent published ownership. |
| invariants | Key destruction deletes row-linked owned members but only detaches bucket links for independently staged nodes. |
| ownership | The bucket does not unconditionally own every linked member. Its pointers require the real member owners to outlive traversal/detachment. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Stored degree/first-link access is fixed; bucket traversal/destruction costs actual members, without O(table rows) lookup. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 55–57](../../../../../src/storage/indexed_nodes.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using KeyDirectory =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name resident projected-key hash lookup including retained empty keys. |
| inputs / outputs | Binds HashDirectory to IndexedKey::lookup_link; residency alone does not imply public live membership. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | Pointer slots/hooks do not delete keys automatically; IndexedIndex destructor explicitly releases resident keys. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
using LiveKeys =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a separate first-live-key traversal without directory scans. |
| inputs / outputs | Binds LiveList to IndexedKey::live_link and includes only keys with current public members. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | This list borrows key nodes already resident under index ownership. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 58–69](../../../../../src/storage/indexed_nodes.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedIndex {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an index's resident keys while borrowing its live-key list. |
| inputs / outputs | IndexedIndex stores logical IndexId, immutable Projection handle, identity hook, key directory and live-key list. |
| invariants | Resident keys include private/undo-retained empty keys; live_keys includes only publicly nonempty buckets. Directory slot pointers themselves do not automatically own Node deletion. |
| ownership | State owns index-node deletion; its explicit destructor deletes resident keys. Projection retains immutable source/target metadata, and live list hooks borrow those key nodes. |
| failure | The constructor body moves checked handles and initializes empty directories/lists noexcept; allocation/growth is prepared by enclosing builders. |
| cost | Fixed metadata construction with deferred slot capacity. Destruction visits resident keys/members and releases actual directory storage, not sparse index-ID high-water. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  Projection projection;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable field-selection token associated with an index. |
| inputs / outputs | Projection stores the exact source/target layout tokens and selected field mapping shared by every key in this index. |
| invariants | Equal independent field lists do not make projection tokens equal; idempotent registration checks this exact program identity. |
| ownership | Shared descriptor ownership keeps source/target metadata alive; it owns neither table rows nor key memberships. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Shared-handle move/copy is fixed; projection execution separately validates/gathers/allocates according to representation. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  KeyDirectory keys;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track all resident keys whose deletion is owned by the enclosing index. |
| inputs / outputs | Includes public nonempty keys and any private/undo-retained empty residents; IndexedIndex destructor explicitly deletes first_resident keys. |
| invariants | HashDirectory owns slot storage and hooks, not automatic Node deletion. Resident iteration differs from sparse slot/counter scanning. |
| ownership | Index explicitly owns key nodes; each key owns its Tuple and borrows membership links under the documented destructor protocol. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Slot growth/probe work belongs to HashDirectory; owner cleanup visits resident keys and members before releasing directory storage. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

```text
  LiveKeys live_keys;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose only publicly live keys in first-live-key order. |
| inputs / outputs | The separate live list includes a resident key exactly when its bucket has public members. |
| invariants | Empty undo-retained residents are omitted; no payload numeric value, cached hash or annotation acts as liveness marker. |
| ownership | The list borrows resident key nodes and does not create another key owner or snapshot. |
| failure | These fields do not validate or catch errors themselves; builders/destructors enforce the stated lifetime, capacity and prepared-link preconditions. |
| cost | Fixed link/degree metadata and one admitted link step per traversal; no hash, directory-capacity scan or deep key copy. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 70–71](../../../../../src/storage/indexed_nodes.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using IndexIdDirectory =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name numeric index lookup independent of index lifetime ownership. |
| inputs / outputs | Binds HashDirectory to IndexedIndex::identity_link. |
| invariants | Typed hook selection prevents accidental reuse of one membership as another; enclosing owners preserve pointer stability and prepare link work before mutation. |
| ownership | State explicitly owns/deletes index nodes; slot pointers and identity hooks borrow them. |
| failure | The alias declaration performs no runtime work; concrete operations retain their existing guard/work failures. |
| cost | Compile-time type binding adds no runtime indirection/registry. Concrete directory/list capacity, lookup, linking and destruction costs remain visible in their owners. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 72–77](../../../../../src/storage/indexed_nodes.hpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline IndexedMember::~IndexedMember() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach a member through each hook's actual surviving owner. |
| inputs / outputs | Destructor calls RowMembers::detach_prepaid and BucketMembers::detach_prepaid on this member. |
| invariants | It must not dereference row/index/key pointers to discover owners: failed private index preparation can retire those parent objects after detaching their bucket hook. |
| ownership | Only this node's two memberships are removed. No row/index/key is owned or recursively destroyed. |
| failure | No throwing allocation/admission or recovery branch; prepaid hook contract inconsistencies terminate in the low-level helper. |
| cost | At most two constant hook unlink operations, no parent lookup, hash, pointer-array capacity scan or heap allocation. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 79–85](../../../../../src/storage/indexed_nodes.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline IndexedRow::~IndexedRow() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a row node and its actual owned memberships iteratively. |
| inputs / outputs | Detaches primary/identity directory hooks and repeatedly deletes the first member until its row list is empty. |
| invariants | Member destruction removes its bucket borrow too. Tuple/arena allocation stays with the arena and is not erased through this borrowed pointer. |
| ownership | Deletes row-owned membership nodes only; the table publication/rollback path separately controls arena membership/payload retention. |
| failure | No allocation/admission while unwinding; actual hook-owner validity is a caller invariant. |
| cost | O(actual row memberships) detach/delete operations plus two directory unlinks. It does not scan a directory capacity or tuple-ID range and does not deep-copy/release the borrowed Tuple. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 87–101](../../../../../src/storage/indexed_nodes.hpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline IndexedKey::~IndexedKey() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release owned bucket members while severing independent staged borrows. |
| inputs / outputs | Detaches key lookup/live hooks; for each bucket member, deletes it when row_link.owner is nonnull, otherwise erases only this bucket borrow. |
| invariants | A row hook establishes published row ownership. A staged unlinked member can still have its own unique_ptr; deleting it here would double-free during failed-build unwinding. |
| ownership | Deletes row-owned member nodes and lets their destructors unlink both lists. Independently prepared member owners remain responsible after borrow detachment. |
| failure | No new allocation, grant or catch is needed during destruction. Member detach uses actual surviving hooks; rows and neighboring keys are never recursively deleted. |
| cost | O(actual bucket members) fixed hook work and owned-node deletion, followed by normal owned Tuple release. No sparse row-ID or directory-capacity scan. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 103–106](../../../../../src/storage/indexed_nodes.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline IndexedIndex::~IndexedIndex() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy an index by its resident-key ownership list. |
| inputs / outputs | Detaches the index identity hook, then deletes first_resident keys until the key directory is empty. |
| invariants | Key destructors detach their own lookup/live hooks and clean up members, so saved next pointers into freed nodes are not reused. |
| ownership | Explicitly deletes resident key owners; the live-key list is a nonowning view, and table rows remain independently owned. |
| failure | No throwing work admission/allocation; valid hook-owner and prepaid cleanup invariants are required. |
| cost | Visits resident keys and their actual member cleanup, then releases directory capacity through its storage type; no sparse logical index-ID scan or recursive row graph teardown. |
| Design | [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 107–108](../../../../../src/storage/indexed_nodes.hpp#L107); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L108:sha256:05825db20eae5643716749fd9f1dad1a40400e47f28da6432edfadc3bbd3864e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/indexed_nodes.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
