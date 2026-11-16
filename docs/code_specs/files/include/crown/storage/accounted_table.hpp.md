# `include/crown/storage/accounted_table.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_table.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `7531fe1d2e2eeb9c6bbee7ffa6e04c4758c8d842922d7e28bb923adde7f95314`. 132 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../../include/crown/storage/accounted_table.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Native dispatch for compact values. The layout supplies the existing query · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../../include/crown/storage/accounted_table.hpp#L17) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0002) |
| [B0003 · 18–43](../../../../../../include/crown/storage/accounted_table.hpp#L18) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Entries borrow native tuples. Ordinary indexed cursors use the caller's · [reviewed contract](#b0003) |
| [B0004 · 44–63](../../../../../../include/crown/storage/accounted_table.hpp#L44) | Type/record definition: class Cursor | source comment (unverified): // Entries borrow native tuples. Ordinary indexed cursors use the caller's · [reviewed contract](#b0004) |
| [B0005 · 64–79](../../../../../../include/crown/storage/accounted_table.hpp#L64) | Type/record definition: class IndexKeyCursor |  · [reviewed contract](#b0005) |
| [B0006 · 80–99](../../../../../../include/crown/storage/accounted_table.hpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 100–132](../../../../../../include/crown/storage/accounted_table.hpp#L100) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Materializes O(matches) handles in an accounted buffer; it pins no rows. · [reviewed contract](#b0007) |

## B0001

[Lines 1–16](../../../../../../include/crown/storage/accounted_table.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedStorageTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define fixed native dispatch between accounted reference and indexed tables. |
| inputs / outputs | One native variant; layout provides query account, raw work pointers are forwarded only where indexed paths need them. |
| invariants | Backend fixed at construction; no new account, owner, per-dispatch allocation, generic transaction layer, or replacement grant. StorageTable remains the separate standalone/tool/differential interface. |
| ownership | Concrete alternative owns rows/indexes/arena; layout/get/cursor entries are borrowed views. Synchronization/read lease is supplied by caller/runtime. |
| failure | Backend work, resource and diagnostic errors propagate; branch-specific null-work behavior is specified per method. |
| cost | Fixed-size variant dispatch only; no new table algorithm. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0002

[Lines 17–17](../../../../../../include/crown/storage/accounted_table.hpp#L17); `type`; `contains_scoped_manual_contract`.

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
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 18–43](../../../../../../include/crown/storage/accounted_table.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the move-only transaction facade over a native table journal. |
| inputs / outputs | Wraps a reference/indexed journal plus optional AccountedIndexWork; exposes change views, journaled writes, commit/rollback and transaction cursors. |
| invariants | Reference may omit work; indexed requires same-account grant and retains that exact Control; preparation/undo semantics are delegated. |
| ownership | Native reader/undo use table account. Change tuple pins survive commit until journal destruction; rollback clears them. |
| failure | Factory/grant/index errors propagate; commit/rollback are noexcept. |
| cost | Facade adds variant/shared handle only, not logs or an account. Read views may see tentative state; ordinary mutation/cursor factories stay locked. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 44–63](../../../../../../include/crown/storage/accounted_table.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the move-only lazy row cursor protocol. |
| inputs / outputs | next returns optional handles; next_entry returns handle plus borrowed AccountedTuple; each accepts optional raw allowance. |
| invariants | Reference ignores work; ordinary indexed cursors borrow per-call grants; indexed journal cursors enforce retained original grant. Rvalue advancement is deleted. |
| ownership | Native cursor data is account-funded and weakly references table; entries do not pin tuples. Caller/runtime supplies synchronization/read lease. |
| failure | Mutation/revision/owner loss/journal abort/missing or replaced grant failures are delegated. |
| cost | Lazy traversal avoids result history; reference bucket next_entry does O(log rows) lookup, indexed follows links and charges even at end. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 64–79](../../../../../../include/crown/storage/accounted_table.hpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define lazy traversal of distinct projected keys and their bucket degrees. |
| inputs / outputs | next yields optional Entry{borrowed key reference, degree}; accepts optional raw work pointer. |
| invariants | Reference ignores work; indexed next requires per-call allowance; no retained grant is stored; rvalue next is deleted. |
| ownership | Native cursor weakly references table; key references are neither copied nor pinned and need source stability/read lease. |
| failure | Owner/revision/journal and indexed-work errors come from concrete cursor. |
| cost | One key at a time; no owning vector or grant control in facade. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 80–99](../../../../../../include/crown/storage/accounted_table.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryStatistics memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect native ownership with an explicit potentially large reporting traversal. |
| inputs / outputs | memory_statistics returns the concrete table's real account attribution, arena slot/ownership, directory charges and retained-history diagnostics. |
| invariants | The returned record is descriptive; it neither reserves a query grant nor turns a logical component count into allocator bytes. Facade alternative matches its actual backend. |
| ownership | Only fixed report values escape; retained ownership stays with native account/table/arena objects, not the report. |
| failure | Invalid owner/account state propagates; no fallback estimate substitutes for missing actual ownership. |
| cost | Indexed report scans account allocation ledger(s), arena high-water slots and resident index directories. Reference reports retain their own ledger/high-water scans; this is separate from cheap cached population statistics and hot probe work. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 100–132](../../../../../../include/crown/storage/accounted_table.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] InsertResult insert(const AccountedTuple&, IndexWorkAllowance* = nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert/probe/remove set rows through AccountedStorageTable's concrete storage contract. |
| inputs / outputs | insert returns {inserted,handle}; find returns optional handle, get borrows payload, pin retains payload, and erase(tuple/handle) removes membership. |
| invariants | Duplicate inserts and absent erases are no-ops. Foreign owner/layout tokens reject; stale/missing handles follow concrete contracts. Ordinary mutation is locked while an exclusive journal is active. |
| ownership | Native rows/nodes/deep values use the layout's existing account; get does not pin. An explicit pin retains immutable payload after erase/clear/owner loss without preserving membership. |
| failure | Fixed native contract/capacity/work/account/allocation failures propagate; throwing preparation completes before link publication. |
| cost | Indexed probes hash/deep-compare actual values and visit collision chains; insert/erase additionally process each index and admitted directory/undo work. Payload copying and final destruction cost actual selected/string bytes; the facade adds only fixed dispatch. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexId add_index(AccountedProjection, IndexWorkAllowance* = nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register and operate explicit projection indexes in AccountedStorageTable. |
| inputs / outputs | add_index registers a projection, drop_index removes it, projection exposes its immutable handle, key_count counts distinct keys, keys/bucket materialize owning outputs, and erase_key removes a whole key bucket. |
| invariants | Same projection token registration is idempotent; equal field lists with independent tokens may coexist. Lookup key must have the exact target token. Nullary keys and repeated fields are ordinary values, not sentinels. |
| ownership | Native key/collection storage and deep copies are funded in the original layout account. Returned bucket handles do not pin rows; projection handles retain immutable metadata. |
| failure | Invalid index/key/layout, busy state, size/cap/work/account or allocation failures propagate. Adding an index finishes throwing preparation before registration; no catch/retry/refill is added. |
| cost | Index creation visits existing rows and projects each key; removal/erase_key visit actual affected keys/memberships. keys/snapshot copy actual outputs, bucket is O(matches) handle materialization. Hash collisions or ordered comparison costs remain concrete-backend work. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedVector<AccountedTuple> snapshot(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning row collection from AccountedStorageTable. |
| inputs / outputs | snapshot returns all live rows in this backend's defined traversal order; keys similarly returns distinct owning projected tuples. |
| invariants | Reference order is lexical; indexed order is insertion/first-live-key order. This is an explicit collection boundary, separate from lazy cursor traversal. |
| ownership | An AccountedVector and every cloned AccountedTuple row are funded by the original account, sharing immutable metadata. |
| failure | Output allocation, overflow, owner-state and any required indexed work denial propagate; no partially returned collection escapes. |
| cost | Visits/materializes all live rows or keys plus actual deep-byte clone/copy costs; output vector capacity/control is additional. Native index work is finite but is not a total CPU or allocator-byte measurement. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic on AccountedStorageTable state. |
| inputs / outputs | check_invariants cross-checks rows, arena, directories, indexes, memberships, ownership/counters and active journal relationships. |
| invariants | This diagnostic is separate from the operational grant and is never a cursor/probe implementation or hot-update prerequisite. |
| ownership | Reads the existing owner; its diagnostic scratch/cost is representation-specific, not output ownership or a new budget. |
| failure | Inconsistent state throws the concrete contract diagnostic; standalone diagnostics can allocate scratch/error text. No recovery is attempted. |
| cost | Native indexed checks are nonallocating but include capacity/high-water and potentially quadratic/cross-population validation; reference checks and mixed facade paths retain their concrete allocation/scan costs. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Cursor live(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a lazy table-row or key-bucket cursor with explicit lifetime fences. |
| inputs / outputs | live walks current rows; bucket_cursor resolves an index/key then walks only that bucket; index_keys walks distinct projected keys/degrees. |
| invariants | Native cursors require both live State and facade_alive, unchanged revision and a nonaborted journal-reader phase. Ordinary factories reject an exclusive active journal. |
| ownership | Factory owns fixed cursor metadata (account-funded on native route) but keeps only weak table ownership. Entries borrow; the enclosing runtime must supply any read lease. |
| failure | Factory can reject owner/index/key/grant/work/account/allocation state; next separately checks its lifetime fences before dereference. |
| cost | Startup allocates fixed cursor data; bucket startup additionally pays index/key lookup and scalar-byte comparison. Successful traversal avoids full result collection and payload copy/pin; reference bucket next_entry still adds ordered-ID lookup. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedStorageTable snapshot_copy(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent live storage with fresh backend/arena owners. |
| inputs / outputs | snapshot_copy preserves live logical tuple/index IDs, high-water counters/revision and concrete traversal order while rebinding internal links/iterators. |
| invariants | It rejects an active journal and copies neither external pins nor retired allocations/source action history. The copied population is a new baseline. |
| ownership | Native copy uses the original query account and shares immutable metadata but owns separately cloned rows/index storage. |
| failure | Allocation, work/cap/account or invalid-state failure discards the private incomplete copy; source logical state remains unchanged. |
| cost | Visits all live rows/indexes/keys/memberships and copies/rebinds their data; native copy clones deep values. Indexed copy borrows one finite aggregate operation allowance, never one new grant per table. |
| Design | [include/crown/storage/accounted_table.hpp](../../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |
