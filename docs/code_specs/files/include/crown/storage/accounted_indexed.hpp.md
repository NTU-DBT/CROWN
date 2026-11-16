# `include/crown/storage/accounted_indexed.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_indexed.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `a38b272e02e202793ff6f09452671a799886a84744303a935d10c982bfa00eb5`. 160 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/storage/accounted_indexed.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 9–17](../../../../../../include/crown/storage/accounted_indexed.hpp#L9) | Type/record definition: struct AccountedIndexedMemoryStatistics |  · [reviewed contract](#b0002) |
| [B0003 · 18–26](../../../../../../include/crown/storage/accounted_indexed.hpp#L18) | declares types or opens a type body. | source comment (unverified): // Native indexed backend selected by AccountedStorageTable. Every node, · [reviewed contract](#b0003) |
| [B0004 · 27–27](../../../../../../include/crown/storage/accounted_indexed.hpp#L27) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0004) |
| [B0005 · 28–57](../../../../../../include/crown/storage/accounted_indexed.hpp#L28) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Both paths consume work prepaid by each mutation, never a new grant. · [reviewed contract](#b0005) |
| [B0006 · 58–80](../../../../../../include/crown/storage/accounted_indexed.hpp#L58) | Type/record definition: class Cursor | source comment (unverified): // Successful next is one admitted live-link step, including end detection. · [reviewed contract](#b0006) |
| [B0007 · 81–100](../../../../../../include/crown/storage/accounted_indexed.hpp#L81) | Type/record definition: class IndexKeyCursor | source comment (unverified): // Borrow expires on next traversal, mutation, index drop or owner loss. · [reviewed contract](#b0007) |
| [B0008 · 101–119](../../../../../../include/crown/storage/accounted_indexed.hpp#L101) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 120–150](../../../../../../include/crown/storage/accounted_indexed.hpp#L120) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Fresh storage/arena owners; preserve live sparse IDs, high-water counters, · [reviewed contract](#b0009) |
| [B0010 · 151–160](../../../../../../include/crown/storage/accounted_indexed.hpp#L151) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0010) |

## B0001

[Lines 1–8](../../../../../../include/crown/storage/accounted_indexed.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:bd3f0a1c9a3320944b67fef7b712e10252e1ac7c040b3ae75d2ae067262c2d7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_indexed.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/indexed.hpp"\`, \`"crown/storage/accounted_reference.hpp"\`, \`"crown/storage/accounted_index_work.hpp"\` for compilation; opens namespace \`crown::storage\`; opens namespace \`detail\`; forward-declares \`class AccountedIndexedTesting\` without defining object layout; closes \`namespace detail\`. |
| inputs / outputs | Compile-time consumers may name \`class AccountedIndexedTesting\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 9–17](../../../../../../include/crown/storage/accounted_indexed.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedMemoryStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe actual indexed-table native ownership separately from logical populations. |
| inputs / outputs | Includes maintained records, attributed table bytes, arena report, directory capacities, owned sum and retained history count. |
| invariants | Requested bytes include framing/control storage and differ from RSS; shared immutable descriptors are separate from exclusive owned bytes. |
| ownership | Value diagnostic structure, not a retained registry of allocations. |
| failure | Produced by explicit stable-state inspection. |
| cost | Fixed result size; constructing its values includes ledger/high-water/index scans described by memory_statistics. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md) |

## B0003

[Lines 18–26](../../../../../../include/crown/storage/accounted_indexed.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedIndexedTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose finite native indexed set storage with explicit caller work and original-account ownership. |
| inputs / outputs | Checked layout/relation/limits support exact rows, indices, pins, copied collections, borrowed cursors and exclusive journals. |
| invariants | Typed exact equality decides membership; component caps include retained nodes. Public fixed native failures differ from formatted higher-layer Error. Single-caller synchronization is external. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. Low-level cursor entries borrow; explicit pins/collections/journal change pins own their stated payload lifetime. |
| failure | Fund growth/inverse work before mutation. Unsupported ownership/layout/limit/grant requests reject; internal prepaid invariant violations terminate. |
| cost | Expected hash behavior assumes distribution; collisions, rehash, per-index projection, deep values and explicit reports retain actual costs. No whole-runtime constant bound. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md) |

## B0004

[Lines 27–27](../../../../../../include/crown/storage/accounted_indexed.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChangeView { bool inserted; TupleHandle handle; const AccountedTuple& tuple; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one retained journal change without copying its payload. |
| inputs / outputs | ChangeView carries insertion/deletion polarity, a TupleHandle and const AccountedTuple& from journal.change(index). |
| invariants | A change view is not current table membership; commit can remove rows while retained change payload remains readable. Rollback clears history. |
| ownership | The reference requires its original journal-owned pin/history lifetime; copying this struct alone retains nothing. |
| failure | Constructing the view is fixed; change(index) separately validates journal/index state and can reject. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 28–57](../../../../../../include/crown/storage/accounted_indexed.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define one move-only indexed-table transaction and retained change-view protocol. |
| inputs / outputs | Insert/erase record successful changes; commit keeps installed membership, rollback reverses it, change(i) borrows a pinned payload. |
| invariants | Exactly one active journal per table. Tentative handles remain private; rollback can reuse unpublished IDs. Commit/rollback/destruction use prepaid work, no new allowance. |
| ownership | Active journal retains State; committed history retains pins/metadata but not whole table. ChangeView reference requires token/pin lifetime. |
| failure | Operation preparation failure preserves its logical table state and prior active history; abandoned active token rolls back. Moved/closed operations reject as documented. |
| cost | Per-change inverse object plus O(indices) pointers and retained payload pins; O(1) vector change lookup, actual inverse/finalization cleanup. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md) |

## B0006

[Lines 58–80](../../../../../../include/crown/storage/accounted_indexed.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define lazy weak-owner live-row or secondary-bucket traversal. |
| inputs / outputs | next(allowance) yields borrowed handle/tuple entries or nullopt; cursor is move-only and lvalue-advanced. |
| invariants | Owner/facade/revision/journal phase checked before native pointers. Journal cursors require the exact retained allowance; ordinary primitive callers supply their allowance explicitly. Journal-created cursors require the identical original IndexWorkAllowance object. Any journal rollback, including an empty rollback, invalidates its cursors and their borrows. |
| ownership | Cursor metadata does not keep table alive; a runtime may separately retain State. Entry is not a pin or owning Tuple. |
| failure | Invalid/busy/wrong-grant/work failures precede advancement. End calls still spend a native step; high-level terminal ResultCursor policy is a separate wrapper. |
| cost | Fixed cursor metadata and admitted link/end steps, with startup key probing for bucket mode; no result collection, ID relookup or payload copy. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../../../verification/full-scope-review-v58-2026-11-15.md) |

## B0007

[Lines 81–100](../../../../../../include/crown/storage/accounted_indexed.hpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define lazy borrowing of live secondary keys and bucket degrees. |
| inputs / outputs | next(allowance) yields a key reference and inline degree, omitting empty undo-retained residents. |
| invariants | Owner/revision/journal/grant rules match row cursor authority; ordinary cursor factories reject active journals. Journal-created cursors require the identical original IndexWorkAllowance object. Any journal rollback, including an empty rollback, invalidates its cursors and their borrows. |
| ownership | Weak table owner and optional shared reader/grant; returned key is borrowed. |
| failure | Stale owner/mutation/aborted journal or grant/busy/work failure rejects before pointer dereference. |
| cost | Fixed cursor state plus startup index lookup and one live-link/end step per admitted call; no deep key output allocation. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../../../verification/full-scope-review-v58-2026-11-15.md) |

## B0008

[Lines 101–119](../../../../../../include/crown/storage/accounted_indexed.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedIndexedMemoryStatistics memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect native ownership with an explicit potentially large reporting traversal. |
| inputs / outputs | memory_statistics returns the concrete table's real account attribution, arena slot/ownership, directory charges and retained-history diagnostics. |
| invariants | The returned record is descriptive; it neither reserves a query grant nor turns a logical component count into allocator bytes. Facade alternative matches its actual backend. |
| ownership | Only fixed report values escape; retained ownership stays with native account/table/arena objects, not the report. |
| failure | Invalid owner/account state propagates; no fallback estimate substitutes for missing actual ownership. |
| cost | Indexed report scans account allocation ledger(s), arena high-water slots and resident index directories. Reference reports retain their own ledger/high-water scans; this is separate from cheap cached population statistics and hot probe work. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 120–150](../../../../../../include/crown/storage/accounted_indexed.hpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] InsertResult insert(const AccountedTuple&, IndexWorkAllowance&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert/probe/remove set rows through AccountedIndexedTable's concrete storage contract. |
| inputs / outputs | insert returns {inserted,handle}; find returns optional handle, get borrows payload, pin retains payload, and erase(tuple/handle) removes membership. |
| invariants | Duplicate inserts and absent erases are no-ops. Foreign owner/layout tokens reject; stale/missing handles follow concrete contracts. Ordinary mutation is locked while an exclusive journal is active. |
| ownership | Native rows/nodes/deep values use the layout's existing account; get does not pin. An explicit pin retains immutable payload after erase/clear/owner loss without preserving membership. |
| failure | Fixed native contract/capacity/work/account/allocation failures propagate; throwing preparation completes before link publication. |
| cost | Indexed probes hash/deep-compare actual values and visit collision chains; insert/erase additionally process each index and admitted directory/undo work. Payload copying and final destruction cost actual selected/string bytes; the facade adds only fixed dispatch. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexId add_index(AccountedProjection, IndexWorkAllowance&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register and operate explicit projection indexes in AccountedIndexedTable. |
| inputs / outputs | add_index registers a projection, drop_index removes it, projection exposes its immutable handle, key_count counts distinct keys, keys/bucket materialize owning outputs, and erase_key removes a whole key bucket. |
| invariants | Same projection token registration is idempotent; equal field lists with independent tokens may coexist. Lookup key must have the exact target token. Nullary keys and repeated fields are ordinary values, not sentinels. |
| ownership | Native key/collection storage and deep copies are funded in the original layout account. Returned bucket handles do not pin rows; projection handles retain immutable metadata. |
| failure | Invalid index/key/layout, busy state, size/cap/work/account or allocation failures propagate. Adding an index finishes throwing preparation before registration; no catch/retry/refill is added. |
| cost | Index creation visits existing rows and projects each key; removal/erase_key visit actual affected keys/memberships. keys/snapshot copy actual outputs, bucket is O(matches) handle materialization. Hash collisions or ordered comparison costs remain concrete-backend work. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedVector<AccountedTuple> snapshot(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning row collection from AccountedIndexedTable. |
| inputs / outputs | snapshot returns all live rows in this backend's defined traversal order; keys similarly returns distinct owning projected tuples. |
| invariants | Reference order is lexical; indexed order is insertion/first-live-key order. This is an explicit collection boundary, separate from lazy cursor traversal. |
| ownership | An AccountedVector and every cloned AccountedTuple row are funded by the original account, sharing immutable metadata. |
| failure | Output allocation, overflow, owner-state and any required indexed work denial propagate; no partially returned collection escapes. |
| cost | Visits/materializes all live rows or keys plus actual deep-byte clone/copy costs; output vector capacity/control is additional. Native index work is finite but is not a total CPU or allocator-byte measurement. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic on AccountedIndexedTable state. |
| inputs / outputs | check_invariants cross-checks rows, arena, directories, indexes, memberships, ownership/counters and active journal relationships. |
| invariants | This diagnostic is separate from the operational grant and is never a cursor/probe implementation or hot-update prerequisite. |
| ownership | Reads the existing owner; its diagnostic scratch/cost is representation-specific, not output ownership or a new budget. |
| failure | Inconsistent state throws the concrete contract diagnostic; standalone diagnostics can allocate scratch/error text. No recovery is attempted. |
| cost | Native indexed checks are nonallocating but include capacity/high-water and potentially quadratic/cross-population validation; reference checks and mixed facade paths retain their concrete allocation/scan costs. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Cursor live(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a lazy table-row or key-bucket cursor with explicit lifetime fences. |
| inputs / outputs | live walks current rows; bucket_cursor resolves an index/key then walks only that bucket; index_keys walks distinct projected keys/degrees. |
| invariants | Native cursors require both live State and facade_alive, unchanged revision and a nonaborted journal-reader phase. Ordinary factories reject an exclusive active journal. |
| ownership | Factory owns fixed cursor metadata (account-funded on native route) but keeps only weak table ownership. Entries borrow; the enclosing runtime must supply any read lease. |
| failure | Factory can reject owner/index/key/grant/work/account/allocation state; next separately checks its lifetime fences before dereference. |
| cost | Startup allocates fixed cursor data; bucket startup additionally pays index/key lookup and scalar-byte comparison. Successful traversal avoids full result collection and payload copy/pin; reference bucket next_entry still adds ordered-ID lookup. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedIndexedTable snapshot_copy(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent live storage with fresh backend/arena owners. |
| inputs / outputs | snapshot_copy preserves live logical tuple/index IDs, high-water counters/revision and concrete traversal order while rebinding internal links/iterators. |
| invariants | It rejects an active journal and copies neither external pins nor retired allocations/source action history. The copied population is a new baseline. |
| ownership | Native copy uses the original query account and shares immutable metadata but owns separately cloned rows/index storage. |
| failure | Allocation, work/cap/account or invalid-state failure discards the private incomplete copy; source logical state remains unchanged. |
| cost | Visits all live rows/indexes/keys/memberships and copies/rebinds their data; native copy clones deep values. Indexed copy borrows one finite aggregate operation allowance, never one new grant per table. |
| Design | [include/crown/storage/accounted_indexed.hpp](../../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 151–160](../../../../../../include/crown/storage/accounted_indexed.hpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<State> state_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the account-backed indexed table's private State behind its facade. |
| inputs / outputs | The constructor binds relation, frozen layout, and limits to the State; methods operate through state_. |
| invariants | State contains the table account/layout, arena, indexes, and journal state; moved-from access rejects. |
| ownership | The facade shares an accounted State; an active journal can retain State while the facade closes. |
| failure | state() throws IndexFailure(invalid_storage) for an empty facade; construction can fail on validation or account admission. |
| cost | State construction allocates funded metadata and directories; final cleanup destroys resident nodes and is not constant-time. |
| Design | [src/storage/accounted_indexed.cpp §AccountedIndexedTable::State](../../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc §journal](../../../../../../src/storage/accounted_indexed_journal.inc), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md), [docs/query_memory.md](../../../../../query_memory.md) |
