# `src/storage/table.cpp` — block usage map

[Source](../../../../../src/storage/table.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `de95102c73412a1e29efb8657753a5bb803e5a924a60fd9ae69ec62a7ecaa67e`. 211 lines partitioned into 62 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/storage/table.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../src/storage/table.cpp#L11) | Callable definition: IndexWorkAllowance& required(IndexWorkAllowance* work) | calls Error; returns *work · [reviewed contract](#b0002) |
| [B0003 · 15–19](../../../../../src/storage/table.cpp#L15) | Callable definition: IndexWorkAllowance& cursor_work(IndexWorkAllowance* requested, const std::shared_ptr&lt;IndexWorkAllowance&gt;& owned) | calls get, Error, required; returns required(requested ? requested : owned.get()) · [reviewed contract](#b0003) |
| [B0004 · 20–21](../../../../../src/storage/table.cpp#L20) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../src/storage/table.cpp#L22) | Callable definition: StorageTable::StorageTable(RelationId relation, TupleLayout layout) : native_(std::in_place_type&lt;ReferenceTable&gt;, relation, std::… | calls native_, std::move · [reviewed contract](#b0005) |
| [B0006 · 24–25](../../../../../src/storage/table.cpp#L24) | Callable definition: StorageTable::StorageTable(RelationId relation, TupleLayout layout, IndexedLimits limits) : native_(std::in_place_type&lt;IndexedTab… | calls native_, std::move · [reviewed contract](#b0006) |
| [B0007 · 26–27](../../../../../src/storage/table.cpp#L26) | Callable definition: StorageTable::StorageTable(ReferenceTable&& table) noexcept : native_(std::in_place_type&lt;ReferenceTable&gt;, std::move(table)) | calls native_, std::move · [reviewed contract](#b0007) |
| [B0008 · 28–29](../../../../../src/storage/table.cpp#L28) | Callable definition: StorageTable::StorageTable(IndexedTable&& table) noexcept : native_(std::in_place_type&lt;IndexedTable&gt;, std::move(table)) | calls native_, std::move · [reviewed contract](#b0008) |
| [B0009 · 30–32](../../../../../src/storage/table.cpp#L30) | Callable definition: StorageBackend StorageTable::backend() const noexcept | calls index; returns native_.index() == 0 ? StorageBackend::reference_ordered_v1 : StorageBackend::indexed_chained_v1 · [reviewed contract](#b0009) |
| [B0010 · 33–33](../../../../../src/storage/table.cpp#L33) | Callable definition: StorageOwnerId StorageTable::owner() const | calls std::visit, owner; returns std::visit(\[\](const auto& table) { return table.owner() · [reviewed contract](#b0010) |
| [B0011 · 34–34](../../../../../src/storage/table.cpp#L34) | Callable definition: RelationId StorageTable::relation() const | calls std::visit, relation; returns std::visit(\[\](const auto& table) { return table.relation() · [reviewed contract](#b0011) |
| [B0012 · 35–37](../../../../../src/storage/table.cpp#L35) | Callable definition: const TupleLayout& StorageTable::layout() const | calls std::visit, layout; returns std::visit(\[\](const auto& table) -&gt; const TupleLayout& { return table.layout() · [reviewed contract](#b0012) |
| [B0013 · 38–38](../../../../../src/storage/table.cpp#L38) | Callable definition: std::size_t StorageTable::size() const | calls std::visit, size; returns std::visit(\[\](const auto& table) { return table.size() · [reviewed contract](#b0013) |
| [B0014 · 39–39](../../../../../src/storage/table.cpp#L39) | Callable definition: std::uint64_t StorageTable::revision() const | calls std::visit, revision; returns std::visit(\[\](const auto& table) { return table.revision() · [reviewed contract](#b0014) |
| [B0015 · 40–42](../../../../../src/storage/table.cpp#L40) | Callable definition: ArenaStatistics StorageTable::arena_statistics() const | calls std::visit, arena_statistics; returns std::visit(\[\](const auto& table) { return table.arena_statistics() · [reviewed contract](#b0015) |
| [B0016 · 43–46](../../../../../src/storage/table.cpp#L43) | Callable definition: std::optional&lt;IndexedLimits&gt; StorageTable::indexed_limits() const | calls limits; returns table-&gt;limits(); {} · [reviewed contract](#b0016) |
| [B0017 · 47–50](../../../../../src/storage/table.cpp#L47) | Callable definition: std::optional&lt;IndexedStatistics&gt; StorageTable::indexed_statistics() const | calls statistics; returns table-&gt;statistics(); {} · [reviewed contract](#b0017) |
| [B0018 · 51–54](../../../../../src/storage/table.cpp#L51) | Callable definition: InsertResult StorageTable::insert(const Tuple& tuple, IndexWorkAllowance* work) | calls insert, required; returns table-&gt;insert(tuple); std::get&lt;IndexedTable&gt;(native_).insert(tuple, required(work)); growth insert · [reviewed contract](#b0018) |
| [B0019 · 55–58](../../../../../src/storage/table.cpp#L55) | Callable definition: std::optional&lt;TupleHandle&gt; StorageTable::find(const Tuple& tuple, IndexWorkAllowance* work) const | calls find, required; returns table-&gt;find(tuple); std::get&lt;IndexedTable&gt;(native_).find(tuple, required(work)) · [reviewed contract](#b0019) |
| [B0020 · 59–62](../../../../../src/storage/table.cpp#L59) | Callable definition: const Tuple* StorageTable::get(TupleHandle handle, IndexWorkAllowance* work) const | calls get, required; returns table-&gt;get(handle); std::get&lt;IndexedTable&gt;(native_).get(handle, required(work)) · [reviewed contract](#b0020) |
| [B0021 · 63–66](../../../../../src/storage/table.cpp#L63) | Callable definition: TupleArena::Pin StorageTable::pin(TupleHandle handle, IndexWorkAllowance* work) const | calls pin, required; returns table-&gt;pin(handle); std::get&lt;IndexedTable&gt;(native_).pin(handle, required(work)) · [reviewed contract](#b0021) |
| [B0022 · 67–70](../../../../../src/storage/table.cpp#L67) | Callable definition: bool StorageTable::erase(const Tuple& tuple, IndexWorkAllowance* work) | calls erase, required; returns table-&gt;erase(tuple); std::get&lt;IndexedTable&gt;(native_).erase(tuple, required(work)) · [reviewed contract](#b0022) |
| [B0023 · 71–74](../../../../../src/storage/table.cpp#L71) | Callable definition: bool StorageTable::erase(TupleHandle handle, IndexWorkAllowance* work) | calls erase, required; returns table-&gt;erase(handle); std::get&lt;IndexedTable&gt;(native_).erase(handle, required(work)) · [reviewed contract](#b0023) |
| [B0024 · 75–79](../../../../../src/storage/table.cpp#L75) | Callable definition: IndexId StorageTable::add_index(Projection projection, IndexWorkAllowance* work) | calls add_index, std::move, required; returns table-&gt;add_index(std::move(projection)); std::get&lt;IndexedTable&gt;(native_).add_index(std::move(projec… · [reviewed contract](#b0024) |
| [B0025 · 80–83](../../../../../src/storage/table.cpp#L80) | Callable definition: bool StorageTable::drop_index(IndexId index, IndexWorkAllowance* work) | calls drop_index, required; returns table-&gt;drop_index(index); std::get&lt;IndexedTable&gt;(native_).drop_index(index, required(work)) · [reviewed contract](#b0025) |
| [B0026 · 84–87](../../../../../src/storage/table.cpp#L84) | Callable definition: std::vector&lt;IndexId&gt; StorageTable::indices(IndexWorkAllowance* work) const | calls indices, required; returns table-&gt;indices(); std::get&lt;IndexedTable&gt;(native_).indices(required(work)) · [reviewed contract](#b0026) |
| [B0027 · 88–91](../../../../../src/storage/table.cpp#L88) | Callable definition: Projection StorageTable::projection(IndexId index, IndexWorkAllowance* work) const | calls projection, required; returns table-&gt;projection(index); std::get&lt;IndexedTable&gt;(native_).projection(index, required(work)) · [reviewed contract](#b0027) |
| [B0028 · 92–95](../../../../../src/storage/table.cpp#L92) | Callable definition: std::size_t StorageTable::key_count(IndexId index, IndexWorkAllowance* work) const | calls key_count, required; returns table-&gt;key_count(index); std::get&lt;IndexedTable&gt;(native_).key_count(index, required(work)) · [reviewed contract](#b0028) |
| [B0029 · 96–99](../../../../../src/storage/table.cpp#L96) | Callable definition: std::vector&lt;Tuple&gt; StorageTable::keys(IndexId index, IndexWorkAllowance* work) const | calls keys, required; returns table-&gt;keys(index); std::get&lt;IndexedTable&gt;(native_).keys(index, required(work)) · [reviewed contract](#b0029) |
| [B0030 · 100–103](../../../../../src/storage/table.cpp#L100) | Callable definition: std::vector&lt;TupleHandle&gt; StorageTable::bucket(IndexId index, const Tuple& key, IndexWorkAllowance* work) const | calls bucket, required; returns table-&gt;bucket(index, key); std::get&lt;IndexedTable&gt;(native_).bucket(index, key, required(work)) · [reviewed contract](#b0030) |
| [B0031 · 104–107](../../../../../src/storage/table.cpp#L104) | Callable definition: std::size_t StorageTable::erase_key(IndexId index, const Tuple& key, IndexWorkAllowance* work) | calls erase_key, required; returns table-&gt;erase_key(index, key); std::get&lt;IndexedTable&gt;(native_).erase_key(index, key, required(work)) · [reviewed contract](#b0031) |
| [B0032 · 108–111](../../../../../src/storage/table.cpp#L108) | Callable definition: void StorageTable::clear(IndexWorkAllowance* work) | calls clear, required · [reviewed contract](#b0032) |
| [B0033 · 112–115](../../../../../src/storage/table.cpp#L112) | Callable definition: std::vector&lt;Tuple&gt; StorageTable::snapshot(IndexWorkAllowance* work) const | calls snapshot, required; returns table-&gt;snapshot(); std::get&lt;IndexedTable&gt;(native_).snapshot(required(work)) · [reviewed contract](#b0033) |
| [B0034 · 116–119](../../../../../src/storage/table.cpp#L116) | Callable definition: StorageTable StorageTable::snapshot_copy(IndexWorkAllowance* work) const | calls StorageTable, snapshot_copy, required; returns StorageTable(table-&gt;snapshot_copy()); StorageTable(std::get&lt;IndexedTable&gt;(native_).snapshot_copy(re… · [reviewed contract](#b0034) |
| [B0035 · 120–120](../../../../../src/storage/table.cpp#L120) | Callable definition: void StorageTable::check_invariants() const | calls std::visit, check_invariants · [reviewed contract](#b0035) |
| [B0036 · 121–121](../../../../../src/storage/table.cpp#L121) | Explanatory comments or spacing. |  |
| [B0037 · 122–123](../../../../../src/storage/table.cpp#L122) | Callable definition: StorageTable::Cursor::Cursor(ReferenceTable::Cursor&& cursor, std::shared_ptr&lt;IndexWorkAllowance&gt; work) : native_(std::in_place_t… | calls native_, std::move, work_ · [reviewed contract](#b0037) |
| [B0038 · 124–125](../../../../../src/storage/table.cpp#L124) | Callable definition: StorageTable::Cursor::Cursor(IndexedTable::Cursor&& cursor, std::shared_ptr&lt;IndexWorkAllowance&gt; work) : native_(std::in_place_typ… | calls native_, std::move, work_ · [reviewed contract](#b0038) |
| [B0039 · 126–133](../../../../../src/storage/table.cpp#L126) | Callable definition: std::optional&lt;TupleHandle&gt; StorageTable::Cursor::next(IndexWorkAllowance* work) | calls next, cursor_work; returns cursor-&gt;next(); {}; source comment (unverified): // Keep the ordered backend on its direct handle walk; next_entry() would · [reviewed contract](#b0039) |
| [B0040 · 134–142](../../../../../src/storage/table.cpp#L134) | Callable definition: std::optional&lt;StorageTable::Cursor::Entry&gt; StorageTable::Cursor::next_entry(IndexWorkAllowance* work) | calls next_entry, next, cursor_work; returns {}; Entry{entry-&gt;handle, entry-&gt;tuple} · [reviewed contract](#b0040) |
| [B0041 · 143–146](../../../../../src/storage/table.cpp#L143) | Callable definition: StorageTable::Cursor StorageTable::live(IndexWorkAllowance* work) const | calls Cursor, live, required; returns Cursor(table-&gt;live()); Cursor(std::get&lt;IndexedTable&gt;(native_).live(required(work))) · [reviewed contract](#b0041) |
| [B0042 · 147–150](../../../../../src/storage/table.cpp#L147) | Callable definition: StorageTable::Cursor StorageTable::bucket_cursor(IndexId index, const Tuple& key, IndexWorkAllowance* work) const | calls Cursor, bucket_cursor, required; returns Cursor(table-&gt;bucket_cursor(index, key)); Cursor(std::get&lt;IndexedTable&gt;(native_).bucket_cursor(inde… · [reviewed contract](#b0042) |
| [B0043 · 151–152](../../../../../src/storage/table.cpp#L151) | Callable definition: StorageTable::IndexKeyCursor::IndexKeyCursor(ReferenceTable::IndexKeyCursor&& cursor) : native_(std::in_place_type&lt;ReferenceTable… | calls native_, std::move · [reviewed contract](#b0043) |
| [B0044 · 153–154](../../../../../src/storage/table.cpp#L153) | Callable definition: StorageTable::IndexKeyCursor::IndexKeyCursor(IndexedTable::IndexKeyCursor&& cursor) : native_(std::in_place_type&lt;IndexedTable::In… | calls native_, std::move · [reviewed contract](#b0044) |
| [B0045 · 155–163](../../../../../src/storage/table.cpp#L155) | Callable definition: std::optional&lt;StorageTable::IndexKeyCursor::Entry&gt; StorageTable::IndexKeyCursor::next(IndexWorkAllowance* work) | calls next, required; returns {}; Entry{entry-&gt;key, entry-&gt;degree} · [reviewed contract](#b0045) |
| [B0046 · 164–167](../../../../../src/storage/table.cpp#L164) | Callable definition: StorageTable::IndexKeyCursor StorageTable::index_keys(IndexId index, IndexWorkAllowance* work) const | calls IndexKeyCursor, index_keys, required; returns IndexKeyCursor(table-&gt;index_keys(index)); IndexKeyCursor(std::get&lt;IndexedTable&gt;(native_).index_keys… · [reviewed contract](#b0046) |
| [B0047 · 168–168](../../../../../src/storage/table.cpp#L168) | Explanatory comments or spacing. |  |
| [B0048 · 169–170](../../../../../src/storage/table.cpp#L169) | Callable definition: StorageTable::Journal::Journal(ReferenceTable::Journal&& journal, std::shared_ptr&lt;IndexWorkAllowance&gt; work) : native_(std::in_pla… | calls native_, std::move, work_ · [reviewed contract](#b0048) |
| [B0049 · 171–172](../../../../../src/storage/table.cpp#L171) | Callable definition: StorageTable::Journal::Journal(IndexedTable::Journal&& journal, std::shared_ptr&lt;IndexWorkAllowance&gt; work) : native_(std::in_place… | calls native_, std::move, work_ · [reviewed contract](#b0049) |
| [B0050 · 173–175](../../../../../src/storage/table.cpp#L173) | Callable definition: bool StorageTable::Journal::active() const noexcept | calls std::visit, active; returns std::visit(\[\](const auto& journal) { return journal.active() · [reviewed contract](#b0050) |
| [B0051 · 176–178](../../../../../src/storage/table.cpp#L176) | Callable definition: std::size_t StorageTable::Journal::size() const noexcept | calls std::visit, size; returns std::visit(\[\](const auto& journal) { return journal.size() · [reviewed contract](#b0051) |
| [B0052 · 179–183](../../../../../src/storage/table.cpp#L179) | Callable definition: StorageTable::ChangeView StorageTable::Journal::change(std::size_t index) const | calls std::visit, change; returns std::visit(\[&\](const auto& journal) -&gt; ChangeView {; {value.inserted, value.handle, value.tuple} · [reviewed contract](#b0052) |
| [B0053 · 184–186](../../../../../src/storage/table.cpp#L184) | Callable definition: InsertResult StorageTable::Journal::insert(const Tuple& tuple) | calls std::visit, insert; returns std::visit(\[&\](auto& journal) { return journal.insert(tuple); growth insert · [reviewed contract](#b0053) |
| [B0054 · 187–189](../../../../../src/storage/table.cpp#L187) | Callable definition: bool StorageTable::Journal::erase(TupleHandle handle) | calls std::visit, erase; returns std::visit(\[&\](auto& journal) { return journal.erase(handle) · [reviewed contract](#b0054) |
| [B0055 · 190–190](../../../../../src/storage/table.cpp#L190) | Callable definition: void StorageTable::Journal::commit() noexcept | calls std::visit, commit · [reviewed contract](#b0055) |
| [B0056 · 191–191](../../../../../src/storage/table.cpp#L191) | Callable definition: void StorageTable::Journal::rollback() noexcept | calls std::visit, rollback · [reviewed contract](#b0056) |
| [B0057 · 192–194](../../../../../src/storage/table.cpp#L192) | Callable definition: StorageTable::Cursor StorageTable::Journal::live() const | calls std::visit, Cursor, live; returns std::visit(\[&\](const auto& journal) { return Cursor(journal.live(), work_) · [reviewed contract](#b0057) |
| [B0058 · 195–197](../../../../../src/storage/table.cpp#L195) | Callable definition: StorageTable::Cursor StorageTable::Journal::bucket_cursor(IndexId index, const Tuple& key) const | calls std::visit, Cursor, bucket_cursor; returns std::visit(\[&\](const auto& journal) { return Cursor(journal.bucket_cursor(index, key), work_) · [reviewed contract](#b0058) |
| [B0059 · 198–202](../../../../../src/storage/table.cpp#L198) | Callable definition: StorageTable::Journal StorageTable::journal(std::shared_ptr&lt;IndexWorkAllowance&gt; work) | calls Journal, journal, std::move; returns Journal(table-&gt;journal(), std::move(work)); Journal(std::move(journal), std::move(work)) · [reviewed contract](#b0059) |
| [B0060 · 203–204](../../../../../src/storage/table.cpp#L203) | controls preprocessing. |  · [reviewed contract](#b0060) |
| [B0061 · 205–209](../../../../../src/storage/table.cpp#L205) | Callable definition: void detail::StorageTableTesting::collisions(StorageTable& table, CollisionMode mode) | calls Error, IndexedTesting::collisions · [reviewed contract](#b0061) |
| [B0062 · 210–211](../../../../../src/storage/table.cpp#L210) | controls preprocessing. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0062) |

## B0001

[Lines 1–10](../../../../../src/storage/table.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/table.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect the fixed two-backend facade and optional testing hook. |
| inputs / outputs | Includes public table/errors; testing-only collision helper is conditional on CROWN_STORAGE_TESTING. |
| invariants | Production dispatch adds no state mirror, SQL NULL or multiplicity semantics. |
| ownership | Declarations allocate no table/grant. |
| failure | Compile-time dependency only. |
| cost | No runtime work from scaffold. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0002

[Lines 11–14](../../../../../src/storage/table.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance& required(IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the caller to supply an indexed-operation allowance object. |
| inputs / outputs | Rejects null and returns the same borrowed allowance reference. |
| invariants | Does not construct, copy, reset or refill a grant; allowance fields are finite uint64 balances. |
| ownership | Caller keeps the object alive for the synchronous backend call. |
| failure | Null throws storage_contract before backend mutation. |
| cost | Constant pointer check, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0003

[Lines 15–19](../../../../../src/storage/table.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance& cursor_work
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve an indexed journal cursor original shared grant. |
| inputs / outputs | If an owned grant exists, an explicit requested pointer must be that exact object; otherwise selects requested or owned pointer and checks nonnull. |
| invariants | No equivalent-limit replacement or per-next refill is allowed. Ordinary cursors borrow their explicitly requested grant. |
| ownership | Borrowed returned reference; work_ retains journal grant outside the call. |
| failure | Replacement/null grant rejects before cursor advance. |
| cost | Constant identity checks, no grant allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0004

[Lines 20–21](../../../../../src/storage/table.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/table.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/table.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/table.cpp\` at its lexical source position in src/storage/table.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/table.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 22–23](../../../../../src/storage/table.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::StorageTable(RelationId relation, TupleLayout layout)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the facade with the reference backend. |
| inputs / outputs | Relation/layout create ReferenceTable directly in the variant. |
| invariants | Default selects ordered set storage; no adaptive backend choice. |
| ownership | Variant owns exactly the selected backend; no second State is allocated by dispatch. |
| failure | Backend allocation/layout/owner errors propagate. |
| cost | Underlying empty reference State/arena construction; facade allocates no separate mirror. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0006

[Lines 24–25](../../../../../src/storage/table.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::StorageTable(RelationId relation, TupleLayout layout, IndexedLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the facade with the indexed backend. |
| inputs / outputs | Relation/layout/component limits create IndexedTable directly in the variant. |
| invariants | Explicit limits select indexed storage for this owner; work is supplied later per operation. |
| ownership | Variant owns exactly the selected backend; no second State is allocated by dispatch. |
| failure | Backend limit/layout/allocation errors propagate. |
| cost | Underlying indexed construction; variant adds fixed selection/setup. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0007

[Lines 26–27](../../../../../src/storage/table.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::StorageTable(ReferenceTable&& table)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the facade with the reference backend. |
| inputs / outputs | Moves a fully constructed ReferenceTable into its variant alternative. |
| invariants | Preserves existing owner, layout, contents and revision. |
| ownership | Variant owns exactly the selected backend; no second State is allocated by dispatch. |
| failure | Noexcept owner transfer. |
| cost | Constant transfer, no new backend or payload copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0008

[Lines 28–29](../../../../../src/storage/table.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::StorageTable(IndexedTable&& table)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the facade with the indexed backend. |
| inputs / outputs | Moves a fully constructed IndexedTable into its variant alternative. |
| invariants | Preserves existing owner, limits, contents and revision. |
| ownership | Variant owns exactly the selected backend; no second State is allocated by dispatch. |
| failure | Noexcept owner transfer. |
| cost | Constant transfer, no new grant or payload copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0009

[Lines 30–32](../../../../../src/storage/table.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageBackend StorageTable::backend() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the selected backend tag without probing or rebuilding storage. |
| inputs / outputs | Maps variant alternative 0 to reference, otherwise indexed. |
| invariants | Tag persists in a moved-from alternative; this is not a live-State validity check. Explicit move replacement can replace the owned backend. |
| ownership | Scalar output only. |
| failure | Noexcept under private valid-variant invariant. |
| cost | Constant tag read, no traversal/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0010

[Lines 33–33](../../../../../src/storage/table.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId StorageTable::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the storage owner getter. |
| inputs / outputs | Returns underlying StorageOwnerId. |
| invariants | Owner identity scopes logical handles. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0011

[Lines 34–34](../../../../../src/storage/table.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId StorageTable::relation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the relation ID getter. |
| inputs / outputs | Returns underlying RelationId. |
| invariants | Relation alone does not authorize a foreign handle. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0012

[Lines 35–37](../../../../../src/storage/table.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& StorageTable::layout() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the required layout getter. |
| inputs / outputs | Returns underlying layout by const reference. |
| invariants | Borrow requires a surviving backend State; no independent token is created. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0013

[Lines 38–38](../../../../../src/storage/table.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t StorageTable::size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the installed row count getter. |
| inputs / outputs | Returns underlying set row count. |
| invariants | Not an expanded SQL bag count or query-account usage. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0014

[Lines 39–39](../../../../../src/storage/table.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t StorageTable::revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the cursor revision getter. |
| inputs / outputs | Returns underlying mutation revision. |
| invariants | Tentative changes may advance it and rollback does not rewind it. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0015

[Lines 40–42](../../../../../src/storage/table.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics StorageTable::arena_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the arena classifications getter. |
| inputs / outputs | Returns underlying fixed ArenaStatistics. |
| invariants | Counts are not bytes/capacity/CPU time. |
| ownership | Forwards a scalar copy or borrowed layout reference; no State mirror or row copy. |
| failure | Underlying moved-from/contract rejection propagates. |
| cost | Fixed variant visit plus constant backend getter, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0016

[Lines 43–46](../../../../../src/storage/table.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedLimits> StorageTable::indexed_limits() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose indexed component limits only for the selected indexed backend. |
| inputs / outputs | Indexed returns limits in an optional; reference returns empty. |
| invariants | Does not select a backend or modify configured limits. |
| ownership | Fixed value copy. |
| failure | Underlying indexed invalid-State rejection propagates; reference branch does no grant check. |
| cost | Constant variant check/getter, no allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0017

[Lines 47–50](../../../../../src/storage/table.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedStatistics> StorageTable::indexed_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixed indexed counters without inventing reference measurements. |
| inputs / outputs | Indexed returns its current statistics; reference returns empty. |
| invariants | Counters are selected component/history counts, not a full allocator/latency report. |
| ownership | Fixed value copy, no scan or snapshot. |
| failure | Underlying invalid-State rejection propagates. |
| cost | Constant variant check/cached-counter snapshot; no row traversal. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0018

[Lines 51–54](../../../../../src/storage/table.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult StorageTable::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch set insertion without adding another ownership or budget layer. |
| inputs / outputs | Tuple probe in; InsertResult out. |
| invariants | Duplicate remains no-op; no bag weight is added. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference ordered insertion/preparation; indexed admitted hash/equality/growth and mutation work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0019

[Lines 55–58](../../../../../src/storage/table.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> StorageTable::find(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch exact row lookup without adding another ownership or budget layer. |
| inputs / outputs | Tuple probe in; optional logical handle out. |
| invariants | Layout admission and tentative visibility follow the selected backend. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference O(log N) typed comparison lookup; indexed visited hash-chain/scalar work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0020

[Lines 59–62](../../../../../src/storage/table.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple* StorageTable::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch borrowed handle lookup without adding another ownership or budget layer. |
| inputs / outputs | Logical handle in; borrowed Tuple pointer or absence out. |
| invariants | Foreign ownership rejects; output is not a pin and respects backend mutation/lifetime fences. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference O(log N) ID lookup; indexed admitted ID-directory lookup. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0021

[Lines 63–66](../../../../../src/storage/table.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin StorageTable::pin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch payload retention without adding another ownership or budget layer. |
| inputs / outputs | Logical live handle in; arena Pin out. |
| invariants | Retention does not keep row membership or cursor validity. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Backend ID/arena lookup and pin admission; final release has its own lifetime cost. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0022

[Lines 67–70](../../../../../src/storage/table.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StorageTable::erase(const Tuple&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch row-value erasure without adding another ownership or budget layer. |
| inputs / outputs | Exact row tuple in; erased/absent Boolean out. |
| invariants | No-op/revision and partial-failure guarantees remain backend-defined. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference lookup/per-index deletion preparation; indexed admitted lookup/preparation and erasure. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0023

[Lines 71–74](../../../../../src/storage/table.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StorageTable::erase(TupleHandle
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch handle erasure without adding another ownership or budget layer. |
| inputs / outputs | Logical handle in; erased/absent Boolean out. |
| invariants | Owner checks precede mutation; no weakening of rollback contracts. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference ID/per-index preparation; indexed admitted directory/inverse/storage work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0024

[Lines 75–79](../../../../../src/storage/table.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId StorageTable::add_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch index registration without adding another ownership or budget layer. |
| inputs / outputs | Projection moves to selected backend; IndexId out. |
| invariants | Same-program token idempotency and complete source/layout admission remain backend obligations. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Complete backend population/projection/index preparation, not a constant metadata insertion. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0025

[Lines 80–83](../../../../../src/storage/table.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StorageTable::drop_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch index removal without adding another ownership or budget layer. |
| inputs / outputs | IndexId in; removed/absent Boolean out. |
| invariants | Real drop invalidates relevant cursors and releases memberships. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Lookup plus key/member/node teardown and any admitted indexed retirement work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0026

[Lines 84–87](../../../../../src/storage/table.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<IndexId> StorageTable::indices(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch index-ID collection without adding another ownership or budget layer. |
| inputs / outputs | Returns an owning standard vector of registered IndexIds. |
| invariants | Output IDs stay backend/table scoped. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus O(I) output/traversal and backend admission/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0027

[Lines 88–91](../../../../../src/storage/table.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection StorageTable::projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch projection-handle lookup without adding another ownership or budget layer. |
| inputs / outputs | IndexId in; shared Projection handle out. |
| invariants | Exact immutable program token is retained, not reconstructed by field equality. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Reference O(log I) or admitted indexed lookup plus handle copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0028

[Lines 92–95](../../../../../src/storage/table.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t StorageTable::key_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch nonempty-key count without adding another ownership or budget layer. |
| inputs / outputs | IndexId in; number of live keys out. |
| invariants | Not member/bag cardinality or allocator usage. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Backend index lookup plus cached count/admission. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0029

[Lines 96–99](../../../../../src/storage/table.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> StorageTable::keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch owning key collection without adding another ownership or budget layer. |
| inputs / outputs | IndexId in; owning key Tuple vector out. |
| invariants | Backend ordering differs; callers must not assume lexical indexed order. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Key traversal plus representation-dependent Tuple copies/bytes and output allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0030

[Lines 100–103](../../../../../src/storage/table.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<TupleHandle> StorageTable::bucket(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch bucket-handle collection without adding another ownership or budget layer. |
| inputs / outputs | Index/key in; owning handle vector out. |
| invariants | Key token checks and tentative read rules remain; handles do not pin payload. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Backend key probe plus O(degree) output/allocation/admitted visits. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0031

[Lines 104–107](../../../../../src/storage/table.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t StorageTable::erase_key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch bulk key erasure without adding another ownership or budget layer. |
| inputs / outputs | Index/key in; affected row count out. |
| invariants | Whole affected membership preparation/undo guarantees stay with backend. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Output-sensitive per-row/index preparation, removal and teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0032

[Lines 108–111](../../../../../src/storage/table.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void StorageTable::clear(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch live-table clear without adding another ownership or budget layer. |
| inputs / outputs | Clears rows/buckets while retaining backend registrations/history per contract. |
| invariants | Empty/no-op and cursor revision rules are unchanged. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Population/membership teardown and underlying admitted work, not O(1). |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0033

[Lines 112–115](../../../../../src/storage/table.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> StorageTable::snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch owning row snapshot without adding another ownership or budget layer. |
| inputs / outputs | Returns ordinary vector of current Tuple values. |
| invariants | May inspect internal tentative contents; this is neither isolation nor a lazy cursor. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus O(rows) traversal plus payload-dependent copies/bytes and output allocation/admission. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0034

[Lines 116–119](../../../../../src/storage/table.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable StorageTable::snapshot_copy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch independent backend copy without adding another ownership or budget layer. |
| inputs / outputs | Returns a facade owning the backend snapshot_copy result. |
| invariants | Preserves selected backend, logical IDs/configuration and row semantics, but creates new owner/arena identities. |
| ownership | Reference ignores the optional work pointer; indexed borrows the exact required caller allowance. Result ownership follows the underlying API. |
| failure | Missing indexed grant rejects before call; backend layout/handle/busy/capacity/work/allocation errors propagate without a wrapper catch. |
| cost | Fixed branch/forwarding overhead plus Whole-state row/index reconstruction and representation-dependent payload copies/admission. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0035

[Lines 120–120](../../../../../src/storage/table.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void StorageTable::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the selected backend full diagnostic directly. |
| inputs / outputs | Variant-visits check_invariants with no synthesized operation grant. |
| invariants | This is explicit inspection, not automatic mutation validation or a work-bounded probe. |
| ownership | Temporary diagnostic containers belong to the underlying backend. |
| failure | Invariant/allocation failures propagate. |
| cost | Full backend table/arena/index scan/rebuild cost; dispatch adds only a fixed visit. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0037

[Lines 122–123](../../../../../src/storage/table.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor::Cursor(ReferenceTable::Cursor&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared reference row cursor with optional retained journal grant. |
| inputs / outputs | Moves underlying cursor and shared work handle into facade. |
| invariants | Ordinary cursors typically have no owned grant; journal cursors retain their original object. |
| ownership | Owns cursor metadata and optional shared grant, not a payload pin/State mirror. |
| failure | No new backend traversal/admission; moves preserve prepared cursor. |
| cost | Fixed owner moves; no new grant/control block or row scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0038

[Lines 124–125](../../../../../src/storage/table.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor::Cursor(IndexedTable::Cursor&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared indexed row cursor with optional retained journal grant. |
| inputs / outputs | Moves underlying cursor and shared work handle into facade. |
| invariants | Ordinary cursors typically have no owned grant; journal cursors retain their original object. |
| ownership | Owns cursor metadata and optional shared grant, not a payload pin/State mirror. |
| failure | No new backend traversal/admission; moves preserve prepared cursor. |
| cost | Fixed owner moves; no new grant/control block or row scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0039

[Lines 126–133](../../../../../src/storage/table.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> StorageTable::Cursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a handle cursor while preserving the reference direct-member path. |
| inputs / outputs | Reference calls next(); indexed calls next with selected original/requested work and extracts its handle. |
| invariants | Does not route reference buckets through next_entry, which would add a ById lookup. Indexed journal grant replacement is rejected. |
| ownership | Scalar optional result, no payload copy/pin; journal grant may remain shared. |
| failure | Backend owner/revision/journal/end/work errors propagate; no wrapper recovery. |
| cost | Reference direct handle step; indexed one admitted live-link/end step plus fixed dispatch, no output allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0040

[Lines 134–142](../../../../../src/storage/table.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<StorageTable::Cursor::Entry> StorageTable::Cursor::next_entry(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward a borrowed row entry without copying its underlying Tuple. |
| inputs / outputs | Reference/Indexed Entry maps to facade handle/reference fields; empty remains empty. |
| invariants | The returned reference is to backend payload, not the temporary optional Entry; original lifetime/revision fences still apply. |
| ownership | No new pin, Tuple copy or row owner; optional shared journal grant is retained independently. |
| failure | Indexed replacement/missing work and backend invalidation/admission errors propagate. |
| cost | Reference primary direct step or bucket O(log N) ID resolution; indexed admitted live-link step; fixed wrapper copies scalar/reference fields only. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0041

[Lines 143–146](../../../../../src/storage/table.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor StorageTable::live(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a selected-backend ordinary live cursor. |
| inputs / outputs | Reference factory needs no work; indexed receives required borrowed grant, then wrapper adopts cursor. |
| invariants | No implicit grant retention for ordinary cursors; later indexed next calls supply their operation allowance. |
| ownership | Prepared cursor metadata owns only underlying weak traversal state. |
| failure | Missing indexed grant/busy/allocation/owner failures propagate. |
| cost | Backend cursor setup/allocation/admission plus fixed move, no materialized rows. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0042

[Lines 147–150](../../../../../src/storage/table.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor StorageTable::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a lazy matching-row cursor for one admitted key. |
| inputs / outputs | Forwards index/key and, for indexed, the required grant. |
| invariants | Preserves backend key-token and revision/journal fences, including valid empty results. |
| ownership | Weak borrowed traversal metadata, no row collection/pinning. |
| failure | Missing grant/layout/index/busy/allocation errors propagate. |
| cost | Backend index/key probe plus cursor setup; no O(degree) collection at this wrapper. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0043

[Lines 151–152](../../../../../src/storage/table.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::IndexKeyCursor::IndexKeyCursor(ReferenceTable::IndexKeyCursor&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared reference projected-key cursor. |
| inputs / outputs | Moves underlying key cursor into the selected alternative. |
| invariants | No backend switch, key copy or table lifetime extension. |
| ownership | Owns metadata only; underlying key references remain borrowed. |
| failure | No local admission or allocation from owner move. |
| cost | Constant transfer. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0044

[Lines 153–154](../../../../../src/storage/table.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::IndexKeyCursor::IndexKeyCursor(IndexedTable::IndexKeyCursor&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared indexed projected-key cursor. |
| inputs / outputs | Moves underlying key cursor into the selected alternative. |
| invariants | No backend switch, key copy or table lifetime extension. |
| ownership | Owns metadata only; underlying key references remain borrowed. |
| failure | No local admission or allocation from owner move. |
| cost | Constant transfer. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0045

[Lines 155–163](../../../../../src/storage/table.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<StorageTable::IndexKeyCursor::Entry> StorageTable::IndexKeyCursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward the next borrowed projected key and degree. |
| inputs / outputs | Reference advances directly; indexed requires the explicit work pointer and forwards it. |
| invariants | Preserves backend ordering/fences; returned key reference is not to the temporary optional result. |
| ownership | No key Tuple copy/pin or new grant; caller respects next/mutation/owner lifetime. |
| failure | Missing indexed grant or backend invalidation/work errors propagate. |
| cost | Fixed dispatch plus backend iterator/live-link/end admission, not a key collection. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0046

[Lines 164–167](../../../../../src/storage/table.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::IndexKeyCursor StorageTable::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the selected ordinary live-key traversal. |
| inputs / outputs | Reference uses scoped index; indexed additionally borrows required work. |
| invariants | No journal key-cursor wrapper or grant refill is installed here. |
| ownership | Adopts backend weak cursor metadata, no copied key vector. |
| failure | Missing work/index/busy/allocation errors propagate. |
| cost | Backend index lookup/setup/admission plus fixed move. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0048

[Lines 169–170](../../../../../src/storage/table.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Journal::Journal(ReferenceTable::Journal&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt one prepared reference journal and its optional shared allowance. |
| inputs / outputs | Moves backend journal into variant and retains work handle. |
| invariants | Does not open another journal, create a grant or duplicate inverse history. |
| ownership | Exclusive journal obligation plus existing shared grant owner. |
| failure | Owner moves do not add a failing backend operation. |
| cost | Constant transfer; later reset/destruction may perform underlying undo/history teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0049

[Lines 171–172](../../../../../src/storage/table.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Journal::Journal(IndexedTable::Journal&&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt one prepared indexed journal and its optional shared allowance. |
| inputs / outputs | Moves backend journal into variant and retains work handle. |
| invariants | Does not open another journal, create a grant or duplicate inverse history. |
| ownership | Exclusive journal obligation plus existing shared grant owner. |
| failure | Owner moves do not add a failing backend operation. |
| cost | Constant transfer; later reset/destruction may perform underlying undo/history teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0050

[Lines 173–175](../../../../../src/storage/table.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StorageTable::Journal::active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal active-state predicate directly. |
| inputs / outputs | Returns backend journal.active(). |
| invariants | History presence differs from an active mutation obligation. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Constant backend predicate. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0051

[Lines 176–178](../../../../../src/storage/table.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t StorageTable::Journal::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal retained change count directly. |
| inputs / outputs | Returns backend journal.size(). |
| invariants | Committed history remains until release; rollback clears it. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Constant backend count. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0052

[Lines 179–183](../../../../../src/storage/table.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::ChangeView StorageTable::Journal::change(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal borrowed change view directly. |
| inputs / outputs | Maps backend direction/handle/tuple reference to facade ChangeView. |
| invariants | Borrow is backed by backend journal retention, not the temporary view object. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Backend history lookup plus fixed scalar/reference forwarding. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0053

[Lines 184–186](../../../../../src/storage/table.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult StorageTable::Journal::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal tentative insertion directly. |
| inputs / outputs | Delegates tuple to the existing backend journal. |
| invariants | Uses its prepared inverse protocol and original indexed grant; duplicate semantics unchanged. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Backend affected projection/insertion/undo preparation and admission. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0054

[Lines 187–189](../../../../../src/storage/table.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StorageTable::Journal::erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal tentative handle deletion directly. |
| inputs / outputs | Delegates logical handle to backend journal. |
| invariants | Ownership/absence/revision/inverse guarantees stay with backend. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Backend affected deletion preparation/extraction/admission. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0055

[Lines 190–190](../../../../../src/storage/table.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void StorageTable::Journal::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal commit directly. |
| inputs / outputs | Visits backend commit with no new grant. |
| invariants | Keeps installed changes and retained view pins; idempotence preserved. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Underlying finalization/release cost, potentially including last-State teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0056

[Lines 191–191](../../../../../src/storage/table.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void StorageTable::Journal::rollback()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward journal rollback directly. |
| inputs / outputs | Visits backend rollback with no new grant. |
| invariants | Aborts reader authority and applies prepared inverses; logical state restored, allocation/revision history may persist. |
| ownership | Existing backend journal owns State/history; wrapper does not mirror entries or copy payload. |
| failure | No wrapper catch or second rollback; noexcept predicates/finalizers retain backend contracts, other backend rejection propagates. |
| cost | Fixed variant visit plus Underlying affected reverse-undo and release costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0057

[Lines 192–194](../../../../../src/storage/table.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor StorageTable::Journal::live() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a tentative row cursor sharing its journal original grant. |
| inputs / outputs | Delegates to backend Journal::live and moves resulting cursor with work_. |
| invariants | Commit/rollback/revision authority is preserved; indexed next may omit work because original shared object is retained. |
| ownership | Cursor shares grant ownership and underlying phase token, not extra payload pins. |
| failure | Inactive scope/metadata/work failures propagate. |
| cost | Backend reader/cursor preparation plus fixed moves/shared-handle copy, no row scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0058

[Lines 195–197](../../../../../src/storage/table.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Cursor StorageTable::Journal::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a tentative bucket cursor sharing journal work authority. |
| inputs / outputs | Delegates index/key lookup and wraps cursor with work_. |
| invariants | Indexed cursor must continue using the exact retained grant; reference operations ignore work while preserving their own guard. |
| ownership | Grant/token ownership only; borrowed membership traversal is not a snapshot. |
| failure | Closed/index/layout/preparation errors propagate. |
| cost | Backend key probe and cursor preparation/admission plus fixed forwarding. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0059

[Lines 198–202](../../../../../src/storage/table.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable::Journal StorageTable::journal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open exactly one backend journal using the caller shared grant. |
| inputs / outputs | Reference opens its ordinary scope and wrapper retains supplied handle; indexed validates/retains the same shared work object before wrapping. |
| invariants | Composed callers must pass one shared object across tables; wrapper never manufactures per-table balances. |
| ownership | Owns backend journal and existing grant; active State retention stays in backend. |
| failure | Busy/invalid/missing indexed grant/capacity/work/allocation errors propagate without wrapper catch. |
| cost | Backend journal preparation/metadata allocation/admission plus constant moves; no full-state clone. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0060

[Lines 203–204](../../../../../src/storage/table.cpp#L203); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#ifdef CROWN_STORAGE_TESTING
void detail::StorageTableTesting::collisions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the explicit collision-injection seam only for testing builds. |
| inputs / outputs | Conditional guard exposes a friend testing definition below. |
| invariants | Production target without the macro has no collision-injection operation here. |
| ownership | Compile-time declaration guard, no owner. |
| failure | No runtime failure in the guard itself. |
| cost | No production runtime work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0061

[Lines 205–209](../../../../../src/storage/table.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::StorageTableTesting::collisions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward testing collision mode only to an indexed testing table. |
| inputs / outputs | Gets indexed variant or rejects reference; invokes IndexedTesting hook. |
| invariants | No production backend policy switch or silent collision mode is selected by ordinary calls. |
| ownership | Mutates only the explicit testing backend through its friend seam. |
| failure | Reference backend throws storage_contract; hook contract failures propagate. |
| cost | Testing-only hook work; not a normal query operation or performance guarantee. |
| Design | [docs/storage.md](../../../../storage.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S02–S04](../../../../../Refactor.md) |

## B0062

[Lines 210–211](../../../../../src/storage/table.cpp#L210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L211:sha256:e69049b524a02d7eeb8d11027b43769fdf0ea8960e5f62e9ca52f2e8eb24d184
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/table.cpp: closes the matching compile-time guard; closes \`namespace crown::storage\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
