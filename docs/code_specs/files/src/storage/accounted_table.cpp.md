# `src/storage/accounted_table.cpp` — block usage map

[Source](../../../../../src/storage/accounted_table.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `e84eedc7db96b5aabec35f98a02eb47ceccb6a497b88dfd42f1b61af4f78e626`. 220 lines partitioned into 63 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/storage/accounted_table.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–13](../../../../../src/storage/accounted_table.cpp#L10) | Callable definition: IndexWorkAllowance& required(IndexWorkAllowance* work) | calls IndexFailure; returns *work · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../src/storage/accounted_table.cpp#L14) | Callable definition: IndexWorkAllowance& cursor_work(IndexWorkAllowance* requested, const AccountedIndexWork& owned) | calls get, IndexFailure, required; returns required(requested ? requested : owned.get()) · [reviewed contract](#b0003) |
| [B0004 · 18–19](../../../../../src/storage/accounted_table.cpp#L18) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 20–21](../../../../../src/storage/accounted_table.cpp#L20) | Callable definition: AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout) : native_(std::in_place_type&lt;AccountedR… | calls native_, std::move · [reviewed contract](#b0005) |
| [B0006 · 22–23](../../../../../src/storage/accounted_table.cpp#L22) | Callable definition: AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout, IndexedLimits limits) : native_(std::in… | calls native_, std::move · [reviewed contract](#b0006) |
| [B0007 · 24–25](../../../../../src/storage/accounted_table.cpp#L24) | Callable definition: AccountedStorageTable::AccountedStorageTable(AccountedReferenceTable&& table) noexcept : native_(std::in_place_type&lt;AccountedRefe… | calls native_, std::move · [reviewed contract](#b0007) |
| [B0008 · 26–27](../../../../../src/storage/accounted_table.cpp#L26) | Callable definition: AccountedStorageTable::AccountedStorageTable(AccountedIndexedTable&& table) noexcept : native_(std::in_place_type&lt;AccountedIndexe… | calls native_, std::move · [reviewed contract](#b0008) |
| [B0009 · 28–30](../../../../../src/storage/accounted_table.cpp#L28) | Callable definition: StorageBackend AccountedStorageTable::backend() const noexcept | calls index; returns native_.index() == 0 ? StorageBackend::reference_ordered_v1 : StorageBackend::indexed_chained_v1 · [reviewed contract](#b0009) |
| [B0010 · 31–31](../../../../../src/storage/accounted_table.cpp#L31) | Callable definition: StorageOwnerId AccountedStorageTable::owner() const | calls std::visit, owner; returns std::visit(\[\](const auto& table) { return table.owner() · [reviewed contract](#b0010) |
| [B0011 · 32–32](../../../../../src/storage/accounted_table.cpp#L32) | Callable definition: RelationId AccountedStorageTable::relation() const | calls std::visit, relation; returns std::visit(\[\](const auto& table) { return table.relation() · [reviewed contract](#b0011) |
| [B0012 · 33–35](../../../../../src/storage/accounted_table.cpp#L33) | Callable definition: const AccountedLayout& AccountedStorageTable::layout() const & | calls std::visit, layout; returns std::visit(\[\](const auto& table) -&gt; const AccountedLayout& { return table.layout() · [reviewed contract](#b0012) |
| [B0013 · 36–36](../../../../../src/storage/accounted_table.cpp#L36) | Callable definition: std::size_t AccountedStorageTable::size() const | calls std::visit, size; returns std::visit(\[\](const auto& table) { return table.size() · [reviewed contract](#b0013) |
| [B0014 · 37–37](../../../../../src/storage/accounted_table.cpp#L37) | Callable definition: std::uint64_t AccountedStorageTable::revision() const | calls std::visit, revision; returns std::visit(\[\](const auto& table) { return table.revision() · [reviewed contract](#b0014) |
| [B0015 · 38–40](../../../../../src/storage/accounted_table.cpp#L38) | Callable definition: ArenaStatistics AccountedStorageTable::arena_statistics() const | calls std::visit, arena_statistics; returns std::visit(\[\](const auto& table) { return table.arena_statistics() · [reviewed contract](#b0015) |
| [B0016 · 41–44](../../../../../src/storage/accounted_table.cpp#L41) | Callable definition: std::optional&lt;IndexedLimits&gt; AccountedStorageTable::indexed_limits() const | calls limits; returns table-&gt;limits(); {} · [reviewed contract](#b0016) |
| [B0017 · 45–48](../../../../../src/storage/accounted_table.cpp#L45) | Callable definition: std::optional&lt;IndexedStatistics&gt; AccountedStorageTable::indexed_statistics() const | calls statistics; returns table-&gt;statistics(); {} · [reviewed contract](#b0017) |
| [B0018 · 49–51](../../../../../src/storage/accounted_table.cpp#L49) | Callable definition: AccountedStorageTable::MemoryStatistics AccountedStorageTable::memory_statistics() const | calls std::visit, memory_statistics; returns std::visit(\[\](const auto& table) -&gt; MemoryStatistics { return table.memory_statistics() · [reviewed contract](#b0018) |
| [B0019 · 52–55](../../../../../src/storage/accounted_table.cpp#L52) | Callable definition: InsertResult AccountedStorageTable::insert(const AccountedTuple& tuple, IndexWorkAllowance* work) | calls insert, required; returns table-&gt;insert(tuple); std::get&lt;AccountedIndexedTable&gt;(native_).insert(tuple, required(work)); growth insert · [reviewed contract](#b0019) |
| [B0020 · 56–59](../../../../../src/storage/accounted_table.cpp#L56) | Callable definition: std::optional&lt;TupleHandle&gt; AccountedStorageTable::find(const AccountedTuple& tuple, IndexWorkAllowance* work) const | calls find, required; returns table-&gt;find(tuple); std::get&lt;AccountedIndexedTable&gt;(native_).find(tuple, required(work)) · [reviewed contract](#b0020) |
| [B0021 · 60–63](../../../../../src/storage/accounted_table.cpp#L60) | Callable definition: const AccountedTuple* AccountedStorageTable::get(TupleHandle handle, IndexWorkAllowance* work) const & | calls get, required; returns table-&gt;get(handle); std::get&lt;AccountedIndexedTable&gt;(native_).get(handle, required(work)) · [reviewed contract](#b0021) |
| [B0022 · 64–67](../../../../../src/storage/accounted_table.cpp#L64) | Callable definition: AccountedTupleArena::Pin AccountedStorageTable::pin(TupleHandle handle, IndexWorkAllowance* work) const | calls pin, required; returns table-&gt;pin(handle); std::get&lt;AccountedIndexedTable&gt;(native_).pin(handle, required(work)) · [reviewed contract](#b0022) |
| [B0023 · 68–71](../../../../../src/storage/accounted_table.cpp#L68) | Callable definition: bool AccountedStorageTable::erase(const AccountedTuple& tuple, IndexWorkAllowance* work) | calls erase, required; returns table-&gt;erase(tuple); std::get&lt;AccountedIndexedTable&gt;(native_).erase(tuple, required(work)) · [reviewed contract](#b0023) |
| [B0024 · 72–75](../../../../../src/storage/accounted_table.cpp#L72) | Callable definition: bool AccountedStorageTable::erase(TupleHandle handle, IndexWorkAllowance* work) | calls erase, required; returns table-&gt;erase(handle); std::get&lt;AccountedIndexedTable&gt;(native_).erase(handle, required(work)) · [reviewed contract](#b0024) |
| [B0025 · 76–80](../../../../../src/storage/accounted_table.cpp#L76) | Callable definition: IndexId AccountedStorageTable::add_index(AccountedProjection projection, IndexWorkAllowance* work) | calls add_index, std::move, required; returns table-&gt;add_index(std::move(projection)); std::get&lt;AccountedIndexedTable&gt;(native_).add_index(std::mo… · [reviewed contract](#b0025) |
| [B0026 · 81–84](../../../../../src/storage/accounted_table.cpp#L81) | Callable definition: bool AccountedStorageTable::drop_index(IndexId index, IndexWorkAllowance* work) | calls drop_index, required; returns table-&gt;drop_index(index); std::get&lt;AccountedIndexedTable&gt;(native_).drop_index(index, required(work)) · [reviewed contract](#b0026) |
| [B0027 · 85–88](../../../../../src/storage/accounted_table.cpp#L85) | Callable definition: AccountedVector&lt;IndexId&gt; AccountedStorageTable::indices(IndexWorkAllowance* work) const | calls indices, required; returns table-&gt;indices(); std::get&lt;AccountedIndexedTable&gt;(native_).indices(required(work)) · [reviewed contract](#b0027) |
| [B0028 · 89–92](../../../../../src/storage/accounted_table.cpp#L89) | Callable definition: AccountedProjection AccountedStorageTable::projection(IndexId index, IndexWorkAllowance* work) const | calls projection, required; returns table-&gt;projection(index); std::get&lt;AccountedIndexedTable&gt;(native_).projection(index, required(work)) · [reviewed contract](#b0028) |
| [B0029 · 93–96](../../../../../src/storage/accounted_table.cpp#L93) | Callable definition: std::size_t AccountedStorageTable::key_count(IndexId index, IndexWorkAllowance* work) const | calls key_count, required; returns table-&gt;key_count(index); std::get&lt;AccountedIndexedTable&gt;(native_).key_count(index, required(work)) · [reviewed contract](#b0029) |
| [B0030 · 97–100](../../../../../src/storage/accounted_table.cpp#L97) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedStorageTable::keys(IndexId index, IndexWorkAllowance* work) const | calls keys, required; returns table-&gt;keys(index); std::get&lt;AccountedIndexedTable&gt;(native_).keys(index, required(work)) · [reviewed contract](#b0030) |
| [B0031 · 101–104](../../../../../src/storage/accounted_table.cpp#L101) | Callable definition: AccountedVector&lt;TupleHandle&gt; AccountedStorageTable::bucket(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) co… | calls bucket, required; returns table-&gt;bucket(index, key); std::get&lt;AccountedIndexedTable&gt;(native_).bucket(index, key, required(wor… · [reviewed contract](#b0031) |
| [B0032 · 105–108](../../../../../src/storage/accounted_table.cpp#L105) | Callable definition: std::size_t AccountedStorageTable::erase_key(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) | calls erase_key, required; returns table-&gt;erase_key(index, key); std::get&lt;AccountedIndexedTable&gt;(native_).erase_key(index, key, requir… · [reviewed contract](#b0032) |
| [B0033 · 109–112](../../../../../src/storage/accounted_table.cpp#L109) | Callable definition: void AccountedStorageTable::clear(IndexWorkAllowance* work) | calls clear, required · [reviewed contract](#b0033) |
| [B0034 · 113–116](../../../../../src/storage/accounted_table.cpp#L113) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedStorageTable::snapshot(IndexWorkAllowance* work) const | calls snapshot, required; returns table-&gt;snapshot(); std::get&lt;AccountedIndexedTable&gt;(native_).snapshot(required(work)) · [reviewed contract](#b0034) |
| [B0035 · 117–120](../../../../../src/storage/accounted_table.cpp#L117) | Callable definition: AccountedStorageTable AccountedStorageTable::snapshot_copy(IndexWorkAllowance* work) const | calls AccountedStorageTable, snapshot_copy, required; returns AccountedStorageTable(table-&gt;snapshot_copy()); AccountedStorageTable(std::get&lt;AccountedIndexedTable… · [reviewed contract](#b0035) |
| [B0036 · 121–123](../../../../../src/storage/accounted_table.cpp#L121) | Callable definition: void AccountedStorageTable::check_invariants() const | calls std::visit, check_invariants · [reviewed contract](#b0036) |
| [B0037 · 124–124](../../../../../src/storage/accounted_table.cpp#L124) | Explanatory comments or spacing. |  |
| [B0038 · 125–126](../../../../../src/storage/accounted_table.cpp#L125) | Callable definition: AccountedStorageTable::Cursor::Cursor(AccountedReferenceTable::Cursor&& cursor, AccountedIndexWork work) : native_(std::in_place_… | calls native_, std::move, work_ · [reviewed contract](#b0038) |
| [B0039 · 127–128](../../../../../src/storage/accounted_table.cpp#L127) | Callable definition: AccountedStorageTable::Cursor::Cursor(AccountedIndexedTable::Cursor&& cursor, AccountedIndexWork work) : native_(std::in_place_ty… | calls native_, std::move, work_ · [reviewed contract](#b0039) |
| [B0040 · 129–134](../../../../../src/storage/accounted_table.cpp#L129) | Callable definition: std::optional&lt;TupleHandle&gt; AccountedStorageTable::Cursor::next(IndexWorkAllowance* work) & | calls next, cursor_work; returns cursor-&gt;next(); {} · [reviewed contract](#b0040) |
| [B0041 · 135–144](../../../../../src/storage/accounted_table.cpp#L135) | Callable definition: std::optional&lt;AccountedStorageTable::Cursor::Entry&gt; AccountedStorageTable::Cursor::next_entry(IndexWorkAllowance* work) & | calls next_entry, next, cursor_work; returns {}; Entry{entry-&gt;handle, entry-&gt;tuple} · [reviewed contract](#b0041) |
| [B0042 · 145–148](../../../../../src/storage/accounted_table.cpp#L145) | Callable definition: AccountedStorageTable::Cursor AccountedStorageTable::live(IndexWorkAllowance* work) const | calls Cursor, live, required; returns Cursor(table-&gt;live()); Cursor(std::get&lt;AccountedIndexedTable&gt;(native_).live(required(work))) · [reviewed contract](#b0042) |
| [B0043 · 149–152](../../../../../src/storage/accounted_table.cpp#L149) | Callable definition: AccountedStorageTable::Cursor AccountedStorageTable::bucket_cursor(IndexId index, const AccountedTuple& key, IndexWorkAllowance* … | calls Cursor, bucket_cursor, required; returns Cursor(table-&gt;bucket_cursor(index, key)); Cursor(std::get&lt;AccountedIndexedTable&gt;(native_).bucket_cu… · [reviewed contract](#b0043) |
| [B0044 · 153–154](../../../../../src/storage/accounted_table.cpp#L153) | Callable definition: AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedReferenceTable::IndexKeyCursor&& cursor) : native_(std::in_place_t… | calls native_, std::move · [reviewed contract](#b0044) |
| [B0045 · 155–156](../../../../../src/storage/accounted_table.cpp#L155) | Callable definition: AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedIndexedTable::IndexKeyCursor&& cursor) : native_(std::in_place_typ… | calls native_, std::move · [reviewed contract](#b0045) |
| [B0046 · 157–166](../../../../../src/storage/accounted_table.cpp#L157) | Callable definition: std::optional&lt;AccountedStorageTable::IndexKeyCursor::Entry&gt; AccountedStorageTable::IndexKeyCursor::next(IndexWorkAllowance* work)… | calls next, required; returns {}; Entry{entry-&gt;key, entry-&gt;degree} · [reviewed contract](#b0046) |
| [B0047 · 167–170](../../../../../src/storage/accounted_table.cpp#L167) | Callable definition: AccountedStorageTable::IndexKeyCursor AccountedStorageTable::index_keys(IndexId index, IndexWorkAllowance* work) const | calls IndexKeyCursor, index_keys, required; returns IndexKeyCursor(table-&gt;index_keys(index)); IndexKeyCursor(std::get&lt;AccountedIndexedTable&gt;(native_).i… · [reviewed contract](#b0047) |
| [B0048 · 171–171](../../../../../src/storage/accounted_table.cpp#L171) | Explanatory comments or spacing. |  |
| [B0049 · 172–173](../../../../../src/storage/accounted_table.cpp#L172) | Callable definition: AccountedStorageTable::Journal::Journal(AccountedReferenceTable::Journal&& journal, AccountedIndexWork work) : native_(std::in_pl… | calls native_, std::move, work_ · [reviewed contract](#b0049) |
| [B0050 · 174–175](../../../../../src/storage/accounted_table.cpp#L174) | Callable definition: AccountedStorageTable::Journal::Journal(AccountedIndexedTable::Journal&& journal, AccountedIndexWork work) : native_(std::in_plac… | calls native_, std::move, work_ · [reviewed contract](#b0050) |
| [B0051 · 176–178](../../../../../src/storage/accounted_table.cpp#L176) | Callable definition: bool AccountedStorageTable::Journal::active() const noexcept | calls std::visit, active; returns std::visit(\[\](const auto& journal) { return journal.active() · [reviewed contract](#b0051) |
| [B0052 · 179–181](../../../../../src/storage/accounted_table.cpp#L179) | Callable definition: std::size_t AccountedStorageTable::Journal::size() const noexcept | calls std::visit, size; returns std::visit(\[\](const auto& journal) { return journal.size() · [reviewed contract](#b0052) |
| [B0053 · 182–187](../../../../../src/storage/accounted_table.cpp#L182) | Callable definition: AccountedStorageTable::ChangeView AccountedStorageTable::Journal::change(std::size_t index) const & | calls std::visit, change; returns std::visit(\[&\](const auto& journal) -&gt; ChangeView {; {value.inserted, value.handle, value.tuple} · [reviewed contract](#b0053) |
| [B0054 · 188–190](../../../../../src/storage/accounted_table.cpp#L188) | Callable definition: InsertResult AccountedStorageTable::Journal::insert(const AccountedTuple& tuple) | calls std::visit, insert; returns std::visit(\[&\](auto& journal) { return journal.insert(tuple); growth insert · [reviewed contract](#b0054) |
| [B0055 · 191–193](../../../../../src/storage/accounted_table.cpp#L191) | Callable definition: bool AccountedStorageTable::Journal::erase(TupleHandle handle) | calls std::visit, erase; returns std::visit(\[&\](auto& journal) { return journal.erase(handle) · [reviewed contract](#b0055) |
| [B0056 · 194–196](../../../../../src/storage/accounted_table.cpp#L194) | Callable definition: void AccountedStorageTable::Journal::commit() noexcept | calls std::visit, commit · [reviewed contract](#b0056) |
| [B0057 · 197–199](../../../../../src/storage/accounted_table.cpp#L197) | Callable definition: void AccountedStorageTable::Journal::rollback() noexcept | calls std::visit, rollback · [reviewed contract](#b0057) |
| [B0058 · 200–202](../../../../../src/storage/accounted_table.cpp#L200) | Callable definition: AccountedStorageTable::Cursor AccountedStorageTable::Journal::live() const | calls std::visit, Cursor, live; returns std::visit(\[&\](const auto& journal) { return Cursor(journal.live(), work_) · [reviewed contract](#b0058) |
| [B0059 · 203–205](../../../../../src/storage/accounted_table.cpp#L203) | Callable definition: AccountedStorageTable::Cursor AccountedStorageTable::Journal::bucket_cursor(IndexId index, const AccountedTuple& key) const | calls std::visit, Cursor, bucket_cursor; returns std::visit(\[&\](const auto& journal) { return Cursor(journal.bucket_cursor(index, key), work_) · [reviewed contract](#b0059) |
| [B0060 · 206–211](../../../../../src/storage/accounted_table.cpp#L206) | Callable definition: AccountedStorageTable::Journal AccountedStorageTable::journal(AccountedIndexWork work) | calls same_account, layout, query_account, IndexFailure; returns Journal(table-&gt;journal(), std::move(work)); Journal(std::move(journal), std::move(work)) · [reviewed contract](#b0060) |
| [B0061 · 212–213](../../../../../src/storage/accounted_table.cpp#L212) | controls preprocessing. |  · [reviewed contract](#b0061) |
| [B0062 · 214–218](../../../../../src/storage/accounted_table.cpp#L214) | Callable definition: void detail::AccountedStorageTableTesting::collisions(AccountedStorageTable& table, AccountedCollisionMode mode) | calls IndexFailure, AccountedIndexedTesting::collisions · [reviewed contract](#b0062) |
| [B0063 · 219–220](../../../../../src/storage/accounted_table.cpp#L219) | controls preprocessing. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0063) |

## B0001

[Lines 1–9](../../../../../src/storage/accounted_table.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:2cb045c7bab1bf3457019b738886de3ed7048f7016a359afd86020673e21294e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_table.cpp: imports \`"crown/storage/accounted_table.hpp"\`, \`"accounted_table_testing.hpp"\`, \`&lt;utility&gt;\` for compilation; opens/branches compile-time guard \`#ifdef CROWN_ACCOUNTED_INDEXED_TESTING\`; closes the matching compile-time guard; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 10–13](../../../../../src/storage/accounted_table.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance& required(IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the raw allowance for an indexed-only operation. |
| inputs / outputs | Optional IndexWorkAllowance* in; the same allowance is returned by reference. |
| invariants | A non-null pointer is the caller's current operation allowance; no copy, refill, or account check is performed. |
| ownership | The returned reference borrows the caller's allowance. |
| failure | Null throws IndexFailure(IndexFault::contract) before indexed dispatch. |
| cost | One pointer test and reference return; no allocation or admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 14–17](../../../../../src/storage/accounted_table.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance& cursor_work(IndexWorkAllowance* requested, const AccountedIndexWork& owned)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose an indexed cursor allowance without allowing a journal grant to be replaced. |
| inputs / outputs | Per-call pointer plus optional retained AccountedIndexWork in; chosen IndexWorkAllowance returned by reference. |
| invariants | If both grants exist, requested must equal owned.get(); ordinary cursors supply per-call work, journal cursors may use the retained grant. |
| ownership | No grant is copied or refilled; the retained shared Control remains the same object. |
| failure | Different pointers or no available grant throw IndexFailure(contract). |
| cost | Constant pointer checks and selection; no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 18–19](../../../../../src/storage/accounted_table.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L19:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/accounted_table.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/accounted_table.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/accounted_table.cpp\` at its lexical source position in src/storage/accounted_table.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/accounted_table.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 20–21](../../../../../src/storage/accounted_table.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the reference-ordered table alternative. |
| inputs / outputs | RelationId and AccountedLayout by value; layout moves into AccountedReferenceTable. |
| invariants | Selects reference_ordered_v1; account comes from layout.query_account(), with no operation grant. |
| ownership | Concrete table owns account-backed state; facade adds no owner/allocation domain. |
| failure | Invalid layout/owner setup or account allocation failures propagate. |
| cost | Variant emplacement plus delegated state/control setup under the existing account. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 22–23](../../../../../src/storage/accounted_table.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout, IndexedLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the indexed-chained alternative with supplied limits. |
| inputs / outputs | RelationId, layout and IndexedLimits by value; the latter two pass to AccountedIndexedTable. |
| invariants | Selects indexed_chained_v1; limits neither create an account nor a work grant. |
| ownership | Concrete indexed table owns query-account state; facade stores the selected variant. |
| failure | Invalid layout, owner exhaustion, limits or account allocation can reject construction. |
| cost | Variant emplacement and delegated table-state/control allocations. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 24–25](../../../../../src/storage/accounted_table.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::AccountedStorageTable(AccountedReferenceTable&& table) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an existing reference table without rebuilding rows. |
| inputs / outputs | AccountedReferenceTable rvalue moves into the reference alternative. |
| invariants | Backend, owner, layout, rows and revision move with the native object. |
| ownership | Transfers the existing account-backed state; no row or owner copy. |
| failure | Noexcept transfer; moved-from use follows native invalid-table behavior. |
| cost | Constant-time variant/native move; no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 26–27](../../../../../src/storage/accounted_table.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::AccountedStorageTable(AccountedIndexedTable&& table) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an existing indexed table without rebuilding directories. |
| inputs / outputs | AccountedIndexedTable rvalue moves into the indexed alternative. |
| invariants | Backend, limits, owner, rows, indexes and revision move with native state. |
| ownership | Transfers the existing account-backed state and work context is not minted. |
| failure | Noexcept transfer; moved-from use follows native invalid-storage behavior. |
| cost | Constant-time variant/native move; no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 28–30](../../../../../src/storage/accounted_table.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageBackend AccountedStorageTable::backend() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report which fixed native alternative the facade holds. |
| inputs / outputs | No input; returns reference_ordered_v1 for variant index zero, indexed_chained_v1 otherwise. |
| invariants | Backend is determined by construction, not inferred from rows or limits. |
| ownership | Scalar enum copy; no table data retained. |
| failure | No throwing path under noexcept. |
| cost | One variant-index read and branch. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 31–31](../../../../../src/storage/accounted_table.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId AccountedStorageTable::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the selected table’s owner identity. |
| inputs / outputs | No input; visits the alternative and returns StorageOwnerId. |
| invariants | Identifies existing storage ownership; it is not a new account or owner. |
| ownership | Scalar copy does not keep the table alive. |
| failure | Moved-from/invalid native state errors propagate. |
| cost | One variant visit and scalar read. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 32–32](../../../../../src/storage/accounted_table.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId AccountedStorageTable::relation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the relation ID recorded by the native table. |
| inputs / outputs | No input; returns RelationId by value. |
| invariants | Relation identity is metadata independent of index and row counts. |
| ownership | Fixed-size value copy retains no table/layout. |
| failure | Moved-from/invalid native state errors propagate. |
| cost | One variant visit and scalar read. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 33–35](../../../../../src/storage/accounted_table.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedStorageTable::layout() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the active table’s layout as a borrowed reference. |
| inputs / outputs | No input; returns const AccountedLayout&; rvalue overload is deleted. |
| invariants | The ref is tied to table lifetime and move state; it is not an exported copy. |
| ownership | Table/layout ownership remains under the original query account. |
| failure | Invalid or moved-from state errors propagate. |
| cost | One variant visit and reference return. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 36–36](../../../../../src/storage/accounted_table.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedStorageTable::size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the number of currently installed live rows. |
| inputs / outputs | No input; returns native primary-set size. |
| invariants | Reads current installed state and may reflect tentative journal changes; not a committed snapshot. |
| ownership | Scalar result owns no rows. |
| failure | Invalid native state errors propagate. |
| cost | Constant-time size read. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 37–37](../../../../../src/storage/accounted_table.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t AccountedStorageTable::revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current native mutation revision. |
| inputs / outputs | No input; returns revision counter by value. |
| invariants | Revision may advance during journal staging before commit. |
| ownership | Scalar result has no table lifetime dependency. |
| failure | Invalid native state errors propagate. |
| cost | Constant-time counter read. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 38–40](../../../../../src/storage/accounted_table.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics AccountedStorageTable::arena_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return fixed-size counters for the selected row arena. |
| inputs / outputs | No input; returns ArenaStatistics by value. |
| invariants | Describes arena slot/pin state, not process RSS or whole-account attribution. |
| ownership | Copied counters do not retain arena or tuple payloads. |
| failure | Invalid native state errors propagate. |
| cost | Fixed-size counter copy; no ledger or row scan. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 41–44](../../../../../src/storage/accounted_table.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedLimits> AccountedStorageTable::indexed_limits() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose configured limits only for indexed storage. |
| inputs / outputs | No input; returns a fixed-size optional copy or nullopt for reference storage. |
| invariants | Does not construct/switch backend; reference storage has no indexed limits. |
| ownership | Copied value retains no table state. |
| failure | No work grant; state errors propagate. |
| cost | Variant test and constant-size copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 45–48](../../../../../src/storage/accounted_table.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedStatistics> AccountedStorageTable::indexed_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the indexed backend’s current fixed-size statistics, if present. |
| inputs / outputs | No input; optional IndexedStatistics by value; reference backend returns empty. |
| invariants | Indexed counts may include pending journal actions; this accessor copies counters rather than recounting rows. |
| ownership | Copied values retain no directories or tuples. |
| failure | State errors propagate; no work allowance is accepted. |
| cost | Variant test and constant-size statistics copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 49–51](../../../../../src/storage/accounted_table.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::MemoryStatistics AccountedStorageTable::memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build account-attributed memory diagnostics for the selected backend. |
| inputs / outputs | No input; returns the variant of reference/indexed memory-statistics records. |
| invariants | Explicit diagnostic read, not hot-probe work or process-RSS accounting; observes current installed state. |
| ownership | Fixed-size report copy; resident table/arena storage remains in the original query account. |
| failure | Account/statistics errors propagate; this API accepts no operation work grant. |
| cost | Diagnostic account-ledger and arena scans; indexed mode also totals resident directories/indexes. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 52–55](../../../../../src/storage/accounted_table.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedStorageTable::insert(const AccountedTuple& tuple, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert a row and report whether it was new plus its handle. |
| inputs / outputs | Borrowed tuple and optional raw grant in; duplicate returns inserted=false with existing handle, otherwise true with new handle. |
| invariants | Reference ignores work; indexed requires the caller’s current grant. Ordinary mutation rejects an active journal. |
| ownership | Native table copies/owns row payload under layout account; tuple is not retained by reference. |
| failure | Indexed null grant throws contract; layout, work, limit and allocation errors propagate. |
| cost | Reference ordered insertion; indexed probe/copy/link admissions. Facade creates no owner or undo framework. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 56–59](../../../../../src/storage/accounted_table.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> AccountedStorageTable::find(const AccountedTuple& tuple, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an equal tuple and return its handle. |
| inputs / outputs | Borrowed tuple and optional raw grant in; empty optional on miss. |
| invariants | Reference ignores work; indexed requires/consumes it. Read may observe tentative journal-installed rows. |
| ownership | Input key borrowed only during lookup; handle does not pin payload. |
| failure | Indexed null grant and layout/account/state/work failures propagate. |
| cost | Ordered lookup or indexed probe/equality work delegated to backend. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 60–63](../../../../../src/storage/accounted_table.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedTuple* AccountedStorageTable::get(TupleHandle handle, IndexWorkAllowance* work) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a handle to a borrowed stored tuple pointer. |
| inputs / outputs | Handle and optional raw grant in; returns const pointer or nullptr for local staleness. |
| invariants | Reference ignores work; indexed requires it. Foreign owner is invalid; local stale is nullptr, unlike pin(). |
| ownership | Pointer expires on source mutation, tentative rollback, or table loss; caller/runtime supplies sync/read lease. |
| failure | Indexed null grant and foreign/invalid handles fail; stale local handle returns nullptr. |
| cost | Handle lookup; no tuple copy or pin. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 64–67](../../../../../src/storage/accounted_table.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin AccountedStorageTable::pin(TupleHandle handle, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire an arena pin for a live row. |
| inputs / outputs | Handle and optional raw grant in; returns AccountedTupleArena::Pin. |
| invariants | Reference ignores work; indexed requires it. A stale local handle is an error because pin requires a live row. |
| ownership | Pin independently retains tuple payload/account through row retirement and table facade loss. |
| failure | Stale handle, foreign owner, pin limit, indexed work or allocation failures propagate. |
| cost | Handle lookup and pin admission; no tuple-value copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 68–71](../../../../../src/storage/accounted_table.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedStorageTable::erase(const AccountedTuple& tuple, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase a matching row by tuple value. |
| inputs / outputs | Borrowed tuple and optional raw grant in; true if removed, false on miss. |
| invariants | Reference ignores work; indexed requires it. Ordinary erase is rejected during active journal. |
| ownership | Key is borrowed; native backend owns any retirement/undo payload. |
| failure | Indexed null grant and native layout/work/limit/resource errors propagate; guarantees delegated. |
| cost | Reference lookup/handle-erasure path; indexed keyed removal with admitted work. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 72–75](../../../../../src/storage/accounted_table.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedStorageTable::erase(TupleHandle handle, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase a row by handle. |
| inputs / outputs | Handle and optional raw grant in; false for local missing/stale, true on removal. |
| invariants | Reference ignores work; indexed requires it. Foreign handles are invalid; ordinary mutator requires unlocked table. |
| ownership | Native backend owns retired tuple/index state and pins. |
| failure | Indexed null grant, foreign handle, limit/work/resource or invariant errors propagate. |
| cost | Handle resolution plus row/index retirement; indexed path consumes its grant. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 76–80](../../../../../src/storage/accounted_table.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId AccountedStorageTable::add_index(AccountedProjection projection, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a projection index or reuse an identical registered projection. |
| inputs / outputs | Projection moved in and optional raw grant; returns existing or new IndexId. |
| invariants | Reference ignores work; indexed requires it. Source layout must match; same-token projection reuses existing ID. |
| ownership | Frozen projection remains query-account owned; table owns new index/key/member nodes. |
| failure | Indexed null grant, layout mismatch, ID/limit/work/allocation failures propagate. |
| cost | New reference index builds buckets from live rows; indexed admits projection/equality/directory/link work. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 81–84](../../../../../src/storage/accounted_table.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedStorageTable::drop_index(IndexId index, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove the identified secondary index if present. |
| inputs / outputs | IndexId and optional raw grant in; false if absent, true after removal. |
| invariants | Reference ignores work; indexed requires it. Revision advances only for successful removal; mutation rejects active journal. |
| ownership | Native backend releases/retire nodes; no projection copy escapes. |
| failure | Indexed null grant and native work/contract/resource errors propagate. |
| cost | Index lookup plus key/member retirement; indexed work is charged. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 85–88](../../../../../src/storage/accounted_table.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<IndexId> AccountedStorageTable::indices(IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an owning list of current index IDs. |
| inputs / outputs | Optional raw grant in; returns AccountedVector&lt;IndexId&gt;. |
| invariants | Reference ignores work; indexed requires it while traversing the resident index directory. |
| ownership | Result buffer is under the original account; scalar IDs do not pin indexes. |
| failure | Indexed null work, account allocation and state failures propagate. |
| cost | O(index count) visits and output capacity. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 89–92](../../../../../src/storage/accounted_table.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedProjection AccountedStorageTable::projection(IndexId index, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the frozen projection associated with an index. |
| inputs / outputs | IndexId and optional raw grant in; AccountedProjection by value. |
| invariants | Reference ignores work; indexed requires it; missing index is rejected by backend. |
| ownership | Value shares immutable projection data/layout tokens rather than rebuilding a descriptor. |
| failure | Indexed null work and invalid-index/state failures propagate. |
| cost | Index lookup and fixed-size shared-handle copy; no row/key scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 93–96](../../../../../src/storage/accounted_table.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedStorageTable::key_count(IndexId index, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the number of distinct live keys in one index. |
| inputs / outputs | IndexId and optional raw grant in; returns count. |
| invariants | Reference ignores work; indexed requires it. Count is distinct keys, not row memberships. |
| ownership | Scalar result owns/pins no keys. |
| failure | Indexed null work and invalid index fail through backend. |
| cost | Index resolution and fixed-size counter read. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 97–100](../../../../../src/storage/accounted_table.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedStorageTable::keys(IndexId index, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return owning copies of an index’s distinct key tuples. |
| inputs / outputs | IndexId and optional grant in; returns AccountedVector&lt;AccountedTuple&gt;. |
| invariants | Reference ignores work; indexed requires it and visits each live key; values are copies, not borrowed keys. |
| ownership | Vector and tuple payloads use original account and outlive later table/index mutation independently; no source pins. |
| failure | Indexed null work, invalid index, tuple validation or account allocation failure propagates. |
| cost | O(distinct keys plus copied scalar bytes); indexed path admits visits/copies. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 101–104](../../../../../src/storage/accounted_table.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<TupleHandle> AccountedStorageTable::bucket(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize handles whose rows match one projected key. |
| inputs / outputs | IndexId, borrowed key and optional raw grant in; account-backed handle vector, empty on miss. |
| invariants | Reference ignores work; indexed requires it. Handles do not pin rows or create a read lease. |
| ownership | O(matches) result buffer belongs to original account; source rows/key are neither copied nor pinned. |
| failure | Indexed null work, invalid index/key, work exhaustion or buffer allocation fails. |
| cost | Index/key lookup plus O(matches) traversal and handle materialization. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 105–108](../../../../../src/storage/accounted_table.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedStorageTable::erase_key(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase all rows in one projected bucket and report the count. |
| inputs / outputs | IndexId, borrowed key, optional grant in; zero on empty/missing bucket. |
| invariants | Reference ignores work; indexed requires it. Ordinary operation requires unlocked table; bulk prepare/undo is delegated. |
| ownership | Native backend owns rows and rollback data during mutation; key borrowed only while selecting. |
| failure | Indexed null work and native limit/resource/contract errors propagate; facade adds no transaction framework. |
| cost | Reference materializes handles and erases through a native journal; indexed prepares affected rows and retires them with admitted work. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0033

[Lines 109–112](../../../../../src/storage/accounted_table.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedStorageTable::clear(IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove all live rows and projected memberships. |
| inputs / outputs | Optional raw grant in; no return value. |
| invariants | Reference ignores work; indexed requires it even when empty. Empty table is a no-op; nonempty ordinary mutation rejects active journal. |
| ownership | Native table/arena capacity remains under original account; facade owns no clear buffer. |
| failure | Indexed null grant and delegated overflow/work/limit errors propagate. |
| cost | Empty path reads size; nonempty path visits rows/index memberships, with indexed admissions. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 113–116](../../../../../src/storage/accounted_table.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedStorageTable::snapshot(IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the rows currently installed into an owning vector. |
| inputs / outputs | Optional raw grant in; returns AccountedVector&lt;AccountedTuple&gt; with one copied tuple per live row. |
| invariants | Reference ignores work; indexed requires it. Read can observe tentative journal state; no committed snapshot is implied. |
| ownership | Result vector and tuple payloads use original query account and survive source mutation independently; no source pins. |
| failure | Indexed null work, tuple validation, output allocation and state failures propagate. |
| cost | O(rows plus scalar-copy width); both branches materialize, indexed additionally admits traversal/copies. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 117–120](../../../../../src/storage/accounted_table.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable AccountedStorageTable::snapshot_copy(IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a separately owned copy of the table on the same layout/account. |
| inputs / outputs | Optional raw grant in; returns a new facade with same backend. |
| invariants | Reference ignores work; indexed requires it. Preserves sparse live IDs, high-water counters, revision, layout and indexed limits; history resets to copied baseline. |
| ownership | Creates a new storage/arena owner under the original MemoryAccount; does not copy external pins or retired source allocations. |
| failure | Active journal is rejected; indexed work/limit and account-allocation failures propagate without modifying source. |
| cost | Rebuilds rows, indexes, keys and memberships; cost and allocations scale with copied state. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 121–123](../../../../../src/storage/accounted_table.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedStorageTable::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the selected backend’s explicit ownership/structure diagnostic. |
| inputs / outputs | No input or operation grant; returns only if checks accept state. |
| invariants | Diagnostic inspects current native structures and does not mutate or replace operational validation. |
| ownership | Borrows resident rows/indexes/arena/account records; returns no owned graph. |
| failure | Broken invariants, invalid state or account inconsistencies fail through backend diagnostics. |
| cost | Explicit scans; indexed collision-heavy cross-checks may be quadratic/population cross-products. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 125–126](../../../../../src/storage/accounted_table.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor::Cursor(AccountedReferenceTable::Cursor&& cursor, AccountedIndexWork work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap reference traversal and optionally retain a journal grant handle. |
| inputs / outputs | Native reference Cursor and AccountedIndexWork move in. |
| invariants | Reference next ignores raw work; a journal cursor may still retain the original shared Control. |
| ownership | Native cursor record is account-funded and weakly refers to table state; retained grant shares, not recreates, its allowance. |
| failure | Factory failures precede construction; move itself is a transfer. |
| cost | Variant construction and handle move; no facade allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 127–128](../../../../../src/storage/accounted_table.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor::Cursor(AccountedIndexedTable::Cursor&& cursor, AccountedIndexWork work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap indexed traversal with its optional retained journal grant. |
| inputs / outputs | Native indexed Cursor and AccountedIndexWork move in. |
| invariants | Ordinary indexed cursor stores no grant and takes per-call work; journal cursor retains exact original Control. |
| ownership | Native cursor data is account-funded/weak-owner; shared work handle is not a refill. |
| failure | Factory-time grant/allocation errors are delegated before wrapping. |
| cost | Variant construction and handle move only. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0040

[Lines 129–134](../../../../../src/storage/accounted_table.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> AccountedStorageTable::Cursor::next(IndexWorkAllowance* work) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance row traversal and return only a tuple handle. |
| inputs / outputs | Optional raw allowance in; handle or empty at end. |
| invariants | Reference ignores pointer; indexed resolves per-call or retained journal grant and rejects replacing a journal grant. |
| ownership | Handle does not pin row. Cursor weakly owns table state; caller/runtime supplies synchronization/read lease. |
| failure | Owner loss, revision change, aborted journal, invalid cursor or indexed grant errors propagate. |
| cost | Lazy one-row traversal; indexed charges pointer/link work even at end; reference handle-only path avoids tuple-ID remap. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0041

[Lines 135–144](../../../../../src/storage/accounted_table.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedStorageTable::Cursor::Entry> AccountedStorageTable::Cursor::next_entry(IndexWorkAllowance* work) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance traversal and expose the next handle with a borrowed tuple reference. |
| inputs / outputs | Optional raw allowance in; Entry{handle, tuple-ref} or empty. |
| invariants | Reference ignores pointer; indexed requires per-call or retained journal grant. Entry is neither copied nor pinned. |
| ownership | Tuple reference expires on source mutation/loss; caller/runtime supplies synchronization/read lease. |
| failure | Cursor/revision/journal validity and indexed grant errors propagate. |
| cost | Lazy next; reference bucket mode adds O(log rows) ID lookup, indexed follows row/member links and charges even at end. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0042

[Lines 145–148](../../../../../src/storage/accounted_table.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor AccountedStorageTable::live(IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create lazy iteration over current live rows. |
| inputs / outputs | Optional raw grant in; returns move-only Cursor. |
| invariants | Reference ignores grant; indexed requires it and admits startup. Ordinary factory rejects active journal and captures revision. |
| ownership | Native cursor state is account-funded and weakly references table; it neither owns rows nor a read lease. |
| failure | Indexed missing work, startup limit/allocation, active journal and invalid state propagate. |
| cost | Constant startup plus native cursor record; visits are lazy, not copied. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0043

[Lines 149–152](../../../../../src/storage/accounted_table.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor AccountedStorageTable::bucket_cursor(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create lazy traversal over one projected bucket. |
| inputs / outputs | IndexId, borrowed key and optional raw grant in; cursor returned, including for no matches. |
| invariants | Reference ignores grant; indexed requires it for index/key lookup and startup. Ordinary factory requires unlocked table and captures revision. |
| ownership | Cursor metadata is account-funded; key is borrowed at creation; rows are not materialized/pinned. |
| failure | Missing indexed work, invalid index/key, active journal, allocation/work or state errors propagate. |
| cost | Lookup plus fixed-size setup; traversal is lazy in matches, unlike bucket(). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0044

[Lines 153–154](../../../../../src/storage/accounted_table.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedReferenceTable::IndexKeyCursor&& cursor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap reference backend’s ordered distinct-key cursor. |
| inputs / outputs | Native reference IndexKeyCursor moves in. |
| invariants | No grant is stored; reference next ignores its optional raw work pointer. |
| ownership | Native account-funded cursor has weak table ownership; yielded key tuples are borrowed. |
| failure | Factory errors occur before wrapping; move adds no failure path. |
| cost | Variant emplacement and native move only. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0045

[Lines 155–156](../../../../../src/storage/accounted_table.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedIndexedTable::IndexKeyCursor&& cursor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap indexed backend’s live-key cursor. |
| inputs / outputs | Native indexed IndexKeyCursor moves in. |
| invariants | No AccountedIndexWork is retained; indexed next requires per-call raw work. |
| ownership | Native cursor state is account-funded/weak-owner; keys are borrowed, not retained. |
| failure | Factory errors occur before wrapping; later validity/work failures are delegated. |
| cost | Variant emplacement and native move only. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0046

[Lines 157–166](../../../../../src/storage/accounted_table.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedStorageTable::IndexKeyCursor::Entry> AccountedStorageTable::IndexKeyCursor::next(IndexWorkAllowance* work) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the next distinct projected key and its bucket degree. |
| inputs / outputs | Optional raw grant in; Entry{borrowed key, degree} or empty. |
| invariants | Reference ignores grant; indexed requires it. Key is neither copied nor pinned. |
| ownership | Cursor weakly references table; key reference needs source stability and caller/runtime synchronization/read lease. |
| failure | Owner/revision/journal invalidity and indexed work exhaustion propagate. |
| cost | Lazy key traversal; indexed admits one native call step even on end, reference advances the ordered bucket map. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0047

[Lines 167–170](../../../../../src/storage/accounted_table.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::IndexKeyCursor AccountedStorageTable::index_keys(IndexId index, IndexWorkAllowance* work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create lazy traversal of distinct keys and their degrees. |
| inputs / outputs | IndexId and optional raw grant in; move-only IndexKeyCursor out. |
| invariants | Reference ignores grant; indexed requires it for index lookup/startup; ordinary creation rejects active journal. |
| ownership | Only traversal state is account-funded; keys are not copied into a vector. |
| failure | Indexed missing work, bad index, active-journal, allocation/work/state errors propagate. |
| cost | Fixed-size setup plus index lookup; keys are visited one at a time. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0049

[Lines 172–173](../../../../../src/storage/accounted_table.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Journal::Journal(AccountedReferenceTable::Journal&& journal, AccountedIndexWork work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a native reference journal with an optional retained grant handle. |
| inputs / outputs | Native reference Journal and AccountedIndexWork move in. |
| invariants | Reference journal may omit work; supplied same-account grant is retained but not consumed by reference forwarding. |
| ownership | Native undo/reader are table-account owned; facade shares the existing work Control if supplied. |
| failure | Factory setup failures occur before wrapping; move itself adds no transaction failure. |
| cost | Variant and shared-handle move; no new journal or account. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0050

[Lines 174–175](../../../../../src/storage/accounted_table.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Journal::Journal(AccountedIndexedTable::Journal&& journal, AccountedIndexWork work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap the indexed journal with its required shared work Control. |
| inputs / outputs | Native indexed Journal and AccountedIndexWork move in. |
| invariants | Indexed journal cursor/mutation work stays bound to this exact grant. |
| ownership | Native undo/reader use table account; work_ shares the original grant and does not refill it. |
| failure | Missing/mismatched grant and native setup failures are raised by factory. |
| cost | Variant/handle move only; transaction log remains in native implementation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0051

[Lines 176–178](../../../../../src/storage/accounted_table.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedStorageTable::Journal::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report backend journal phase. |
| inputs / outputs | No input; returns bool from active native journal. |
| invariants | Phase is authoritative; facade does not infer from table revision or change count. |
| ownership | Scalar result retains no journal state. |
| failure | No throwing path under noexcept. |
| cost | Variant visit and flag read. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0052

[Lines 179–181](../../../../../src/storage/accounted_table.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedStorageTable::Journal::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report number of journal change/undo entries, not live table rows. |
| inputs / outputs | No input; returns entry count. |
| invariants | After commit entries/pins may remain until Journal destruction; count is not active row count. |
| ownership | Scalar copy; native entries and pins retain their own lifetime. |
| failure | No throwing path under noexcept. |
| cost | Variant visit and size read. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0053

[Lines 182–187](../../../../../src/storage/accounted_table.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::ChangeView AccountedStorageTable::Journal::change(std::size_t index) const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one journal record as insert/erase flag, handle and borrowed tuple. |
| inputs / outputs | Zero-based index in; ChangeView with const tuple reference out. |
| invariants | Rvalue overload is deleted. Reference list lookup is O(index); indexed vector lookup is O(1). |
| ownership | Change pin survives commit through Journal destruction; rollback clears pins. Returned ref follows record/journal lifetime. |
| failure | Invalid journal/index throws delegated invalid_journal error. |
| cost | Reference advances list; indexed indexes vector; neither copies tuple bytes. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0054

[Lines 188–190](../../../../../src/storage/accounted_table.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedStorageTable::Journal::insert(const AccountedTuple& tuple)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage insertion through the active native journal. |
| inputs / outputs | Borrowed tuple in; duplicate returns false/existing handle, new row returns true/new handle. |
| invariants | Journal must be active; indexed consumes its retained original grant, reference uses native transaction without raw work. |
| ownership | Native table owns copied row and undo pin under query account. |
| failure | Inactive journal, layout/work/limit/allocation failure propagates; preparation/undo guarantees delegated. |
| cost | Native insertion plus change/pin and backend index work; facade only dispatches. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0055

[Lines 191–193](../../../../../src/storage/accounted_table.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedStorageTable::Journal::erase(TupleHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage removal of a row by handle. |
| inputs / outputs | Handle in; false when local row is absent, true on staged removal. |
| invariants | Journal must be active; foreign owner invalid. Indexed work comes from retained grant, not a new per-call pointer. |
| ownership | Native journal retains payload/undo pin for rollback and change view under original account. |
| failure | Inactive/foreign-handle/work/limit/resource failures propagate; inverse logic delegated. |
| cost | Handle lookup, unlink and journal-record work; indexed dimensions consume work_. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0056

[Lines 194–196](../../../../../src/storage/accounted_table.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedStorageTable::Journal::commit() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize backend journal and clear active transaction lock. |
| inputs / outputs | No input/output; delegates commit to selected journal. |
| invariants | Native commit/classification is authoritative; facade does not reapply staged rows. |
| ownership | Native change pins remain until Journal destruction; retained work Control lives as long as held. |
| failure | No throwing path under noexcept; native commit is noexcept. |
| cost | Variant dispatch and native finalization; no new grant or facade allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0057

[Lines 197–199](../../../../../src/storage/accounted_table.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedStorageTable::Journal::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate restoration of pre-journal state and release the active lock. |
| inputs / outputs | No input/output; invokes selected native rollback. |
| invariants | Rollback and allocation-free inverse guarantees are native behavior, not a facade algorithm. |
| ownership | Native undo/change pins are cleared or retired; change tuple views do not survive rollback. |
| failure | No throwing path under noexcept; native rollback is noexcept. |
| cost | Variant dispatch and reverse application; no new allocation/grant. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0058

[Lines 200–202](../../../../../src/storage/accounted_table.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor AccountedStorageTable::Journal::live() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create lazy traversal over the journal’s currently installed image. |
| inputs / outputs | No input; returns a move-only Cursor. |
| invariants | Unlike ordinary factory, journal reader may see tentative changes; indexed cursor is bound to retained original grant. |
| ownership | Native cursor shares journal reader; facade cursor retains work_ and weak table ownership. |
| failure | Inactive/aborted journal, indexed work or cursor allocation failures propagate. |
| cost | Account-funded cursor setup plus native startup admission; rows remain lazy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0059

[Lines 203–205](../../../../../src/storage/accounted_table.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Cursor AccountedStorageTable::Journal::bucket_cursor(IndexId index, const AccountedTuple& key) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create lazy traversal over a projected bucket in current journal state. |
| inputs / outputs | IndexId and borrowed key in; returns move-only Cursor, possibly empty. |
| invariants | Journal reader sees tentative image; indexed traversal uses retained grant and cannot substitute another. |
| ownership | Native reader/cursor own account-funded control; yielded tuple refs remain borrowed. |
| failure | Inactive journal, bad index/key, work/allocation/state errors propagate. |
| cost | Bucket lookup and cursor setup; no O(matches) handle vector. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0060

[Lines 206–211](../../../../../src/storage/accounted_table.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedStorageTable::Journal AccountedStorageTable::journal(AccountedIndexWork work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a journal after validating any supplied grant against the layout account. |
| inputs / outputs | Optional AccountedIndexWork by value in; move-only Journal out. |
| invariants | Any nonempty grant must match layout.query_account(); reference permits empty, indexed requires nonempty. Ordinary mutation/cursor factories then reject; selected reads can see tentative state. |
| ownership | Native reader/undo use the original query account; retained grant is shared unchanged. |
| failure | Mismatched nonempty grant throws contract; indexed empty grant and native active/work/allocation errors propagate. |
| cost | Account check and native journal/reader setup; indexed admits setup slots, reference may retain optional grant without consuming it. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0061

[Lines 212–213](../../../../../src/storage/accounted_table.cpp#L212); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L213:sha256:689e8a4ac7d0424f792575ba6c59462e7fc0cf052b1cbbd63635e02bd33623ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_table.cpp: opens/branches compile-time guard \`#ifdef CROWN_ACCOUNTED_INDEXED_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0062

[Lines 214–218](../../../../../src/storage/accounted_table.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::AccountedStorageTableTesting::collisions(AccountedStorageTable& table, AccountedCollisionMode mode)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a deterministic hash-collision mode through the private indexed test seam. |
| inputs / outputs | Mutable table and mode in; no result. |
| invariants | Only compiled for CROWN_ACCOUNTED_INDEXED_TESTING. Requires indexed fresh-empty state: no rows/indexes and zero tuple/index high-water; same_bucket needs directory_slots &lt;= 65536. |
| ownership | Changes only indexed testing state; no production API/account/work grant is created. |
| failure | Reference backend, nonfresh state, invalid mode, or unsupported mask throws IndexFailure(contract). |
| cost | Variant check and delegated fixture/mode validation; no allocation or table scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0063

[Lines 219–220](../../../../../src/storage/accounted_table.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L219-L220:sha256:e69049b524a02d7eeb8d11027b43769fdf0ea8960e5f62e9ca52f2e8eb24d184
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_table.cpp: closes the matching compile-time guard; closes \`namespace crown::storage\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
