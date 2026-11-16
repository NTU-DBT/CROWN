# `include/crown/storage/indexed.hpp` — block usage map

[Source](../../../../../../include/crown/storage/indexed.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `f9709e083f9ece34842c35e4b6deb482057fd12b61595c5fa70f6476fba31913`. 179 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../../include/crown/storage/indexed.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Explicit finite component counts, not allocator-byte or peak-memory limits. · [reviewed contract](#b0001) |
| [B0002 · 20–27](../../../../../../include/crown/storage/indexed.hpp#L20) | Type/record definition: struct IndexedActions |  · [reviewed contract](#b0002) |
| [B0003 · 28–28](../../../../../../include/crown/storage/indexed.hpp#L28) | Explanatory comments or spacing. | source comment (unverified): // Population/action diagnostics, separate from allocator bytes or CPU time. · [reviewed contract](#b0003) |
| [B0004 · 29–47](../../../../../../include/crown/storage/indexed.hpp#L29) | Type/record definition: struct IndexedStatistics | source comment (unverified): // Population/action diagnostics, separate from allocator bytes or CPU time. · [reviewed contract](#b0004) |
| [B0005 · 48–57](../../../../../../include/crown/storage/indexed.hpp#L48) | declares types or opens a type body. | source comment (unverified): // Standalone indexed storage using public Tuple values and ordinary owners. · [reviewed contract](#b0005) |
| [B0006 · 58–58](../../../../../../include/crown/storage/indexed.hpp#L58) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0006) |
| [B0007 · 59–87](../../../../../../include/crown/storage/indexed.hpp#L59) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Both paths consume work prepaid by each mutation, never a new grant. · [reviewed contract](#b0007) |
| [B0008 · 88–108](../../../../../../include/crown/storage/indexed.hpp#L88) | Type/record definition: class Cursor | source comment (unverified): // Successful next is one admitted live-link step, including end detection. · [reviewed contract](#b0008) |
| [B0009 · 109–127](../../../../../../include/crown/storage/indexed.hpp#L109) | Type/record definition: class IndexKeyCursor | source comment (unverified): // Borrow expires on next traversal, mutation, index drop or owner loss. · [reviewed contract](#b0009) |
| [B0010 · 128–143](../../../../../../include/crown/storage/indexed.hpp#L128) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 144–179](../../../../../../include/crown/storage/indexed.hpp#L144) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Fresh storage/arena owners, exact live sparse IDs/counters and traversal · [reviewed contract](#b0011) |

## B0001

[Lines 1–19](../../../../../../include/crown/storage/indexed.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:904358b83b1008f45bd9eef7140c4dd46fc908d022dd2eba76b6fbc8dc2aa685
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/indexed.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/arena.hpp"\`, \`"crown/storage/backend.hpp"\`, \`"crown/storage/index_work.hpp"\`, \`"crown/storage/table_types.hpp"\`, \`&lt;compare&gt;\`, \`&lt;cstddef&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;memory&gt;\`, \`&lt;optional&gt;\`, \`&lt;vector&gt;\` for compilation; opens namespace \`crown::storage\`; opens namespace \`detail\`; forward-declares \`class IndexedTesting\` without defining object layout; closes \`namespace detail\`. Source comment: Explicit finite component counts, not allocator-byte or peak-memory limits. Zero permits no corresponding objects; there is no unlimited default. |
| inputs / outputs | Compile-time consumers may name \`class IndexedTesting\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: Explicit finite component counts, not allocator-byte or peak-memory limits. Zero permits no corresponding objects; there is no unlimited default. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 20–27](../../../../../../include/crown/storage/indexed.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedActions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report monotonic logical index action counts. |
| inputs / outputs | Counts successful inserted/erased rows, added/dropped indices and clear operations; all fields default to zero. |
| invariants | Committed and tentative actions are kept separate by IndexedStatistics; they are not elapsed time or copied baseline populations. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 28–28](../../../../../../include/crown/storage/indexed.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:5bd44465b42105518b7d86e481c499fa252a0be3a5896e2a459d2cce26353fd7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct IndexedStatistics\`: Population/action diagnostics, separate from allocator bytes or CPU time. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/indexed.hpp:L29; use that declaration for the actual input/output shape. |
| invariants | The source note states: Population/action diagnostics, separate from allocator bytes or CPU time. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Population/action diagnostics, separate from allocator bytes or CPU time. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0004

[Lines 29–47](../../../../../../include/crown/storage/indexed.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report indexed populations, retention and committed/tentative actions. |
| inputs / outputs | Carries row/index/key/live-key/member/node/directory counts, ArenaStatistics, copied baseline, retained rows/members and journal entries. |
| invariants | Copied_rows/copied_indices describe an owning copy's initial live baseline; source history and external pins are not copied. Component totals are not bytes. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 48–57](../../../../../../include/crown/storage/indexed.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexedTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the IndexedTable storage representation and its explicit primitive protocol. |
| inputs / outputs | Set-valued insert/find/get/pin/erase, projection index registration/probes, owning snapshots and lazy cursors operate on one relation/layout. |
| invariants | Logical IDs belong to one storage owner; exact layout/projection tokens matter. Journal mutation is exclusive and tentative handles remain internal until commit. |
| ownership | Concrete owners retain rows/indexes/arena. Ordinary std containers/shared controls are a standalone/tool boundary, not native query-account accounting; returned references/cursor entries borrow unless explicitly pinned/copied. |
| failure | Concrete validation, allocation, overflow and journal/cursor failures propagate. Indexed operations additionally require the original finite work grant; facade dispatch creates none. |
| cost | Expected hash probes depend on distribution; collisions visit admitted chains. Per-index projection/deep bytes/rehash/copy retain actual costs. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 58–58](../../../../../../include/crown/storage/indexed.hpp#L58); `type`; `contains_scoped_manual_contract`.

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
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 59–87](../../../../../../include/crown/storage/indexed.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exclusive standalone IndexedTable mutation journal. |
| inputs / outputs | insert/erase prepare change history and inverse records; live/bucket cursors see internal tentative state; change(index) exposes retained payload; commit/rollback close the mutation scope. |
| invariants | Indexed journals retain the exact shared caller grant and prepay inverse/finalization work. Tentative handles/reads stay internal until commit; destruction rolls an active journal back in reverse order. |
| ownership | An active journal retains table State; completed history retains affected payload pins until destruction. A copied ChangeView is only a reference to that lifetime. |
| failure | Invalid/closed journal, capacity/overflow/work or allocation failures propagate during preparation. commit/rollback/destruction use prepared no-throw cleanup; no catch/retry is added to this header. |
| cost | Per mutation, journal storage and per-index projected keys/membership records are prepared; commit/rollback process actual history and releases. Retained capacity can survive successful tentative operations and logical rollback. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 88–108](../../../../../../include/crown/storage/indexed.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse live indexed rows or bucket members by stable links. |
| inputs / outputs | A move-only Cursor returns optional {TupleHandle,const Tuple&} via next(IndexWorkAllowance&). |
| invariants | State lifetime, revision and journal-reader phase/grant identity are checked before dereferencing. Standalone State can survive its facade while an active journal retains it. Denied work leaves position unchanged; end still debits a step. Journal-created cursors require the identical original IndexWorkAllowance object. Any journal rollback, including an empty rollback, invalidates its cursors and their borrows. |
| ownership | Cursor has ordinary allocated metadata and weak table ownership; journal variants retain reader/grant metadata. Entries borrow, do not pin/copy payloads. |
| failure | Invalid/moved/expired/stale/busy/grant-mismatch states reject; standalone Error diagnostics can allocate. No retry hides exhaustion. |
| cost | Factory allocates fixed cursor metadata (and bucket startup probes its key). Each admitted next uses one live-link/end step with no row hash, ID lookup or successful scalar allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../../../verification/full-scope-review-v58-2026-11-15.md) |

## B0009

[Lines 109–127](../../../../../../include/crown/storage/indexed.hpp#L109); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse first-live-key order and return bucket degrees lazily. |
| inputs / outputs | IndexKeyCursor::next returns an optional borrowed key and current membership count. |
| invariants | Owner/revision/reader/grant checks precede pointer use; mutation, index drop or owner loss invalidates. Empty/end traversal still charges native structural work. Journal-created cursors require the identical original IndexWorkAllowance object. Any journal rollback, including an empty rollback, invalidates its cursors and their borrows. |
| ownership | Ordinary cursor metadata weakly references the table; an entry is not an owning key snapshot or pin. |
| failure | Invalid state, busy owner, wrong grant or work exhaustion reject through standalone diagnostics; no hidden refilling. |
| cost | Startup resolves the index and allocates fixed metadata; next follows one live key link and copies a fixed degree field, without deep key copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../../../verification/full-scope-review-v58-2026-11-15.md) |

## B0010

[Lines 128–143](../../../../../../include/crown/storage/indexed.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable(RelationId relation, TupleLayout layout, IndexedLimits limits);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the standalone indexed table's explicit construction, move-only lifecycle, and population accessors. |
| inputs / outputs | Relation, layout, and finite IndexedLimits in; owner/layout/limit/statistic values out. |
| invariants | Copy is disabled, move transfers the table state, and component limits count logical components rather than bytes. |
| ownership | The table owns a standalone shared State and TupleArena; it is not funded by a query MemoryAccount. |
| failure | Construction may fail on allocation/invalid state; methods on a moved-from table throw invalid_storage. |
| cost | Construction creates State; statistics report populations and do not bound traversal or allocator bytes. |
| Design | [src/storage/indexed.cpp §IndexedTable construction](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |

## B0011

[Lines 144–179](../../../../../../include/crown/storage/indexed.hpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] InsertResult insert(const Tuple&, IndexWorkAllowance&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert/probe/remove set rows through IndexedTable's concrete storage contract. |
| inputs / outputs | insert returns {inserted,handle}; find returns optional handle, get borrows payload, pin retains payload, and erase(tuple/handle) removes membership. |
| invariants | Duplicate inserts and absent erases are no-ops. Foreign owner/layout tokens reject; stale/missing handles follow concrete contracts. Ordinary mutation is locked while an exclusive journal is active. |
| ownership | The standalone owner funds ordinary containers; get is a borrow, not a pin. An explicit pin retains immutable payload after erase/clear/owner loss without preserving membership. |
| failure | Public Error, component-cap/work and allocator failures propagate; preparation precedes links and failed operations preserve logical state. |
| cost | Indexed probes hash/deep-compare actual values and visit collision chains; insert/erase additionally process each index and admitted directory/undo work. Payload copying and final destruction cost actual selected/string bytes; the facade adds only fixed dispatch. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexId add_index(Projection, IndexWorkAllowance&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register and operate explicit projection indexes in IndexedTable. |
| inputs / outputs | add_index registers a projection, drop_index removes it, projection exposes its immutable handle, key_count counts distinct keys, keys/bucket materialize owning outputs, and erase_key removes a whole key bucket. |
| invariants | Same projection token registration is idempotent; equal field lists with independent tokens may coexist. Lookup key must have the exact target token. Nullary keys and repeated fields are ordinary values, not sentinels. |
| ownership | Returned vectors are ordinary owning collections; legacy Tuple copies can deep-copy strings. Returned bucket handles do not pin rows; projection handles retain immutable metadata. |
| failure | Invalid index/key/layout, busy state, size/cap/work/account or allocation failures propagate. Adding an index finishes throwing preparation before registration; no catch/retry/refill is added. |
| cost | Index creation visits existing rows and projects each key; removal/erase_key visit actual affected keys/memberships. keys/snapshot copy actual outputs, bucket is O(matches) handle materialization. Hash collisions or ordered comparison costs remain concrete-backend work. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::vector<Tuple> snapshot(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning row collection from IndexedTable. |
| inputs / outputs | snapshot returns all live rows in this backend's defined traversal order; keys similarly returns distinct owning projected tuples. |
| invariants | Reference order is lexical; indexed order is insertion/first-live-key order. This is an explicit collection boundary, separate from lazy cursor traversal. |
| ownership | An ordinary vector owns returned tuples; legacy rows deep-copy payload, while already native-backed public tuples may share immutable funded payload. |
| failure | Output allocation, overflow, owner-state and any required indexed work denial propagate; no partially returned collection escapes. |
| cost | Visits/materializes all live rows or keys plus actual deep-byte clone/copy costs; output vector capacity/control is additional. Native index work is finite but is not a total CPU or allocator-byte measurement. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic on IndexedTable state. |
| inputs / outputs | check_invariants cross-checks rows, arena, directories, indexes, memberships, ownership/counters and active journal relationships. |
| invariants | This diagnostic is separate from the operational grant and is never a cursor/probe implementation or hot-update prerequisite. |
| ownership | Reads the existing owner; its diagnostic scratch/cost is representation-specific, not output ownership or a new budget. |
| failure | Inconsistent state throws the concrete contract diagnostic; standalone diagnostics can allocate scratch/error text. No recovery is attempted. |
| cost | May allocate and scan arena high-water, rows/indices/keys/memberships, including collision-heavy/quadratic checks. It has no constant operational bound. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Cursor live(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a lazy table-row or key-bucket cursor with explicit lifetime fences. |
| inputs / outputs | live walks current rows; bucket_cursor resolves an index/key then walks only that bucket; index_keys walks distinct projected keys/degrees. |
| invariants | Standalone cursors require live weak State, unchanged revision and a nonaborted journal-reader phase; an active journal can retain State beyond its facade. Ordinary factories reject an exclusive active journal. |
| ownership | Factory owns fixed cursor metadata (account-funded on native route) but keeps only weak table ownership. Entries borrow; the enclosing runtime must supply any read lease. |
| failure | Factory can reject owner/index/key/grant/work/account/allocation state; next separately checks its lifetime fences before dereference. |
| cost | Startup allocates fixed cursor data; bucket startup additionally pays index/key lookup and scalar-byte comparison. Successful traversal avoids full result collection and payload copy/pin; reference bucket next_entry still adds ordered-ID lookup. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexedTable snapshot_copy(IndexWorkAllowance&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent live storage with fresh backend/arena owners. |
| inputs / outputs | snapshot_copy preserves live logical tuple/index IDs, high-water counters/revision and concrete traversal order while rebinding internal links/iterators. |
| invariants | It rejects an active journal and copies neither external pins nor retired allocations/source action history. The copied population is a new baseline. |
| ownership | Copy owns separate ordinary table/index/arena storage; public native-backed tuple payloads can retain immutable shared native ownership as their representation allows. |
| failure | Allocation, work/cap/account or invalid-state failure discards the private incomplete copy; source logical state remains unchanged. |
| cost | Visits all live rows/indexes/keys/memberships and copies/rebinds their data; native copy clones deep values. Indexed copy borrows one finite aggregate operation allowance, never one new grant per table. |
| Design | [include/crown/storage/indexed.hpp](../../../../../../include/crown/storage/indexed.hpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [src/storage/indexed_journal.inc](../../../../../../src/storage/indexed_journal.inc), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |
