# `include/crown/storage/table.hpp` — block usage map

[Source](../../../../../../include/crown/storage/table.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `e3e3d0bc19ef2aeee630bb680be28f4b605738c11839a5f9e91ff7eceaaf0fec`. 129 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../../include/crown/storage/table.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Internal backend dispatch. The two-argument constructor preserves S02; · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../../include/crown/storage/table.hpp#L18) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../../include/crown/storage/table.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Concrete journals retain their own inverse/change pins; dispatch only · [reviewed contract](#b0003) |
| [B0004 · 21–43](../../../../../../include/crown/storage/table.hpp#L21) | Type/record definition: class Journal | growth insert; source comment (unverified): // Concrete journals retain their own inverse/change pins; dispatch only · [reviewed contract](#b0004) |
| [B0005 · 44–65](../../../../../../include/crown/storage/table.hpp#L44) | Type/record definition: class Cursor | source comment (unverified): // Keep the reference bucket-handle next O(1). Borrowed reference bucket · [reviewed contract](#b0005) |
| [B0006 · 66–80](../../../../../../include/crown/storage/table.hpp#L66) | Type/record definition: class IndexKeyCursor |  · [reviewed contract](#b0006) |
| [B0007 · 81–98](../../../../../../include/crown/storage/table.hpp#L81) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 99–129](../../../../../../include/crown/storage/table.hpp#L99) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // An indexed journal requires a nonnull shared grant. All tables of a · [reviewed contract](#b0008) |

## B0001

[Lines 1–17](../../../../../../include/crown/storage/table.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class StorageTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the StorageTable storage representation and its explicit primitive protocol. |
| inputs / outputs | Set-valued insert/find/get/pin/erase, projection index registration/probes, owning snapshots and lazy cursors operate on one relation/layout. |
| invariants | Logical IDs belong to one storage owner; exact layout/projection tokens matter. Journal mutation is exclusive and tentative handles remain internal until commit. |
| ownership | Concrete owners retain rows/indexes/arena. Ordinary std containers/shared controls are a standalone/tool boundary, not native query-account accounting; returned references/cursor entries borrow unless explicitly pinned/copied. |
| failure | Concrete validation, allocation, overflow and journal/cursor failures propagate. Indexed operations additionally require the original finite work grant; facade dispatch creates none. |
| cost | Ordered map/set operations compare actual typed/deep values with logarithmic lookup factors; the mixed facade adds fixed dispatch and retains each concrete backend's costs. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../../include/crown/storage/table.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChangeView { bool inserted; TupleHandle handle; const Tuple& tuple; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one retained journal change without copying its payload. |
| inputs / outputs | ChangeView carries insertion/deletion polarity, a TupleHandle and const Tuple& from journal.change(index). |
| invariants | A change view is not current table membership; commit can remove rows while retained change payload remains readable. Rollback clears history. |
| ownership | The reference requires its original journal-owned pin/history lifetime; copying this struct alone retains nothing. |
| failure | Constructing the view is fixed; change(index) separately validates journal/index state and can reject. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 19–20](../../../../../../include/crown/storage/table.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:d93c4bf80d4122f049131642593e2d9e27bb07930648b22202781ae74e2d3a3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class Journal\`: Concrete journals retain their own inverse/change pins; dispatch only retains the same shared work grant and introduces no second mutation log. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/table.hpp:L21; use that declaration for the actual input/output shape. |
| invariants | The source note states: Concrete journals retain their own inverse/change pins; dispatch only retains the same shared work grant and introduces no second mutation log. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Concrete journals retain their own inverse/change pins; dispatch only retains the same shared work grant and introduces no second mutation log. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Concrete journals retain their own inverse/change pins; dispatch only retains the same shared work grant and introduces no second mutation log. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0004

[Lines 21–43](../../../../../../include/crown/storage/table.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch an exclusive standalone transaction to its concrete backend journal. |
| inputs / outputs | Journal wraps ReferenceTable::Journal or IndexedTable::Journal and exposes change history, insert/erase, tentative cursors and commit/rollback. |
| invariants | All indexed journals in a composed operation retain the same shared IndexWorkAllowance. Throwing preparation and inverse/finalization reservation precede publication; commit/rollback need no new grant. |
| ownership | The variant owns its concrete journal; shared work_ retains the exact original balance. ChangeView borrows journal-retained pin/history storage and does not itself own it. |
| failure | Concrete active-state/capacity/allocation/work failures propagate. Destruction rolls back an active journal; commit/rollback are noexcept. No facade catch/retry is added. |
| cost | Facade dispatch is fixed. Each mutation pays concrete row/index/projection/preparation work and inverse retention; commit/rollback process actual history. Physical capacity may remain grown after logical rollback. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 44–65](../../../../../../include/crown/storage/table.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch lazy row traversal without replacing a work allowance. |
| inputs / outputs | Cursor::next returns a handle; next_entry returns a borrowed Tuple reference, forwarding to the selected concrete cursor. |
| invariants | Indexed calls use the supplied finite grant, or the exact retained journal grant; an alternate nonnull grant on a journal cursor rejects. |
| ownership | The variant owns concrete cursor metadata, not row/table lifetime. Only journal cursors retain a shared allowance; ordinary supplied pointers are borrowed synchronously. |
| failure | Concrete invalid/expired/stale/busy/exhausted/grant mismatch failures propagate; no materialized fallback is created. |
| cost | Fixed variant dispatch. Reference bucket handle next is an iterator step, bucket next_entry adds O(log rows) lookup; indexed next follows one admitted link including end. No successful row copy/pin. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 66–80](../../../../../../include/crown/storage/table.hpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch lazy projected-key/degree traversal. |
| inputs / outputs | IndexKeyCursor::next forwards an optional borrowed key/degree from the selected concrete backend. |
| invariants | Ordinary indexed traversal requires the caller's finite allowance; no grant is retained by this facade key cursor. |
| ownership | Concrete cursor metadata weakly references the table. Returned references retain neither payload nor index membership. |
| failure | Invalid cursor, expired/mutated/busy owner or native work denial propagates; no owning snapshot or retry. |
| cost | Fixed dispatch plus one concrete ordered/live-key step. Factory metadata/probing costs remain with index_keys; no deep key materialization per step. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 81–98](../../../../../../include/crown/storage/table.hpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable(RelationId, TupleLayout);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a move-only facade that selects reference or indexed standalone storage at construction. |
| inputs / outputs | Two arguments select ReferenceTable; an IndexedLimits overload selects IndexedTable; getters report backend metadata. |
| invariants | The selected backend is stored in a variant; reference storage has no indexed limits/statistics value. |
| ownership | The facade owns its backend by value; underlying table state owns rows/indexes. |
| failure | Underlying constructor/allocation errors propagate; copy is rejected at compile time. |
| cost | The variant dispatch adds no separate table state; backend construction and later container operations retain their own costs. |
| Design | [src/storage/table.cpp §StorageTable constructors and backend](../../../../../../src/storage/table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md §Reference table and cursors](../../../../../storage.md) |

## B0008

[Lines 99–129](../../../../../../include/crown/storage/table.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] InsertResult insert(const Tuple&, IndexWorkAllowance* = nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert/probe/remove set rows through StorageTable's concrete storage contract. |
| inputs / outputs | insert returns {inserted,handle}; find returns optional handle, get borrows payload, pin retains payload, and erase(tuple/handle) removes membership. |
| invariants | Duplicate inserts and absent erases are no-ops. Foreign owner/layout tokens reject; stale/missing handles follow concrete contracts. Ordinary mutation is locked while an exclusive journal is active. |
| ownership | The standalone owner funds ordinary containers; get is a borrow, not a pin. An explicit pin retains immutable payload after erase/clear/owner loss without preserving membership. |
| failure | Public Error, component-cap/work and allocator failures propagate; preparation precedes links and failed operations preserve logical state. |
| cost | Indexed probes hash/deep-compare actual values and visit collision chains; insert/erase additionally process each index and admitted directory/undo work. Payload copying and final destruction cost actual selected/string bytes; the facade adds only fixed dispatch. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexId add_index(Projection, IndexWorkAllowance* = nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register and operate explicit projection indexes in StorageTable. |
| inputs / outputs | add_index registers a projection, drop_index removes it, projection exposes its immutable handle, key_count counts distinct keys, keys/bucket materialize owning outputs, and erase_key removes a whole key bucket. |
| invariants | Same projection token registration is idempotent; equal field lists with independent tokens may coexist. Lookup key must have the exact target token. Nullary keys and repeated fields are ordinary values, not sentinels. |
| ownership | Returned vectors are ordinary owning collections; legacy Tuple copies can deep-copy strings. Returned bucket handles do not pin rows; projection handles retain immutable metadata. |
| failure | Invalid index/key/layout, busy state, size/cap/work/account or allocation failures propagate. Adding an index finishes throwing preparation before registration; no catch/retry/refill is added. |
| cost | Index creation visits existing rows and projects each key; removal/erase_key visit actual affected keys/memberships. keys/snapshot copy actual outputs, bucket is O(matches) handle materialization. Hash collisions or ordered comparison costs remain concrete-backend work. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::vector<Tuple> snapshot(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning row collection from StorageTable. |
| inputs / outputs | snapshot returns all live rows in this backend's defined traversal order; keys similarly returns distinct owning projected tuples. |
| invariants | Reference order is lexical; indexed order is insertion/first-live-key order. This is an explicit collection boundary, separate from lazy cursor traversal. |
| ownership | An ordinary vector owns returned tuples; legacy rows deep-copy payload, while already native-backed public tuples may share immutable funded payload. |
| failure | Output allocation, overflow, owner-state and any required indexed work denial propagate; no partially returned collection escapes. |
| cost | Visits/materializes all live rows or keys plus actual deep-byte clone/copy costs; output vector capacity/control is additional. Native index work is finite but is not a total CPU or allocator-byte measurement. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic on StorageTable state. |
| inputs / outputs | check_invariants cross-checks rows, arena, directories, indexes, memberships, ownership/counters and active journal relationships. |
| invariants | This diagnostic is separate from the operational grant and is never a cursor/probe implementation or hot-update prerequisite. |
| ownership | Reads the existing owner; its diagnostic scratch/cost is representation-specific, not output ownership or a new budget. |
| failure | Inconsistent state throws the concrete contract diagnostic; standalone diagnostics can allocate scratch/error text. No recovery is attempted. |
| cost | May allocate and scan arena high-water, rows/indices/keys/memberships, including collision-heavy/quadratic checks. It has no constant operational bound. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Cursor live(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a lazy table-row or key-bucket cursor with explicit lifetime fences. |
| inputs / outputs | live walks current rows; bucket_cursor resolves an index/key then walks only that bucket; index_keys walks distinct projected keys/degrees. |
| invariants | Standalone cursors require live weak State, unchanged revision and a nonaborted journal-reader phase; an active journal can retain State beyond its facade. Ordinary factories reject an exclusive active journal. |
| ownership | Factory owns fixed cursor metadata (account-funded on native route) but keeps only weak table ownership. Entries borrow; the enclosing runtime must supply any read lease. |
| failure | Factory can reject owner/index/key/grant/work/account/allocation state; next separately checks its lifetime fences before dereference. |
| cost | Startup allocates fixed cursor data; bucket startup additionally pays index/key lookup and scalar-byte comparison. Successful traversal avoids full result collection and payload copy/pin; reference bucket next_entry still adds ordered-ID lookup. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] StorageTable snapshot_copy(IndexWorkAllowance* = nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent live storage with fresh backend/arena owners. |
| inputs / outputs | snapshot_copy preserves live logical tuple/index IDs, high-water counters/revision and concrete traversal order while rebinding internal links/iterators. |
| invariants | It rejects an active journal and copies neither external pins nor retired allocations/source action history. The copied population is a new baseline. |
| ownership | Copy owns separate ordinary table/index/arena storage; public native-backed tuple payloads can retain immutable shared native ownership as their representation allows. |
| failure | Allocation, work/cap/account or invalid-state failure discards the private incomplete copy; source logical state remains unchanged. |
| cost | Visits all live rows/indexes/keys/memberships and copies/rebinds their data; native copy clones deep values. Indexed copy borrows one finite aggregate operation allowance, never one new grant per table. |
| Design | [include/crown/storage/table.hpp](../../../../../../include/crown/storage/table.hpp), [src/storage/table.cpp](../../../../../../src/storage/table.cpp), [tests/unit/storage_table_test.cpp](../../../../../../tests/unit/storage_table_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |
