# `src/storage/indexed.cpp` — block usage map

[Source](../../../../../src/storage/indexed.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `4c8b71bb936e84dfd06749b8ea9662126e1d473411d80ea9afbf340d46fcf182`. 791 lines partitioned into 88 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/storage/indexed.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. | source comment (unverified): // Source-private definition with namespace linkage, like the existing S02 · [reviewed contract](#b0001) |
| [B0002 · 19–25](../../../../../src/storage/indexed.cpp#L19) | Type/record definition: struct IndexedJournalReader | source comment (unverified): // Source-private definition with namespace linkage, like the existing S02 · [reviewed contract](#b0002) |
| [B0003 · 26–31](../../../../../src/storage/indexed.cpp#L26) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0003) |
| [B0004 · 32–34](../../../../../src/storage/indexed.cpp#L32) | Callable definition: void contract(bool value, const char* message) | calls Error · [reviewed contract](#b0004) |
| [B0005 · 35–38](../../../../../src/storage/indexed.cpp#L35) | Callable definition: void room(std::size_t current, std::size_t extra, std::size_t maximum) | calls Error · [reviewed contract](#b0005) |
| [B0006 · 39–42](../../../../../src/storage/indexed.cpp#L39) | Callable definition: void counter_room(std::uint64_t current, std::uint64_t extra = 1) | calls max, Error · [reviewed contract](#b0006) |
| [B0007 · 43–48](../../../../../src/storage/indexed.cpp#L43) | Callable definition: std::uint64_t work_product(std::size_t count, std::uint64_t cost) | calls max, Error; returns value * cost · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../src/storage/indexed.cpp#L49) | Callable definition: void start(IndexWorkAllowance& work) | calls admit · [reviewed contract](#b0008) |
| [B0009 · 50–56](../../../../../src/storage/indexed.cpp#L50) | Callable definition: template &lt;class T&gt; void reserve_records(std::vector&lt;T&gt;& records, std::size_t count, IndexWorkAllowance& work) | calls max_size, Error, admit, work_product; growth reserve · [reviewed contract](#b0009) |
| [B0010 · 57–81](../../../../../src/storage/indexed.cpp#L57) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 82–85](../../../../../src/storage/indexed.cpp#L82) | Callable definition: State(RelationId value, TupleLayout schema, IndexedLimits configuration) : relation(value), layout(std::move(schema)), limits(con… | calls relation, layout, std::move, limits · [reviewed contract](#b0011) |
| [B0012 · 86–91](../../../../../src/storage/indexed.cpp#L86) | Callable definition: ~State() | calls first_resident; 2 loop sites; source comment (unverified): // Destroy nodes while all actual hook owners are still alive. Neither · [reviewed contract](#b0012) |
| [B0013 · 92–95](../../../../../src/storage/indexed.cpp#L92) | Callable definition: void input(const Tuple& tuple) const | calls same_token, layout, Error · [reviewed contract](#b0013) |
| [B0014 · 96–99](../../../../../src/storage/indexed.cpp#L96) | Callable definition: void owned(TupleHandle handle) const | calls Error · [reviewed contract](#b0014) |
| [B0015 · 100–100](../../../../../src/storage/indexed.cpp#L100) | Callable definition: void mutable_revision() const | calls counter_room · [reviewed contract](#b0015) |
| [B0016 · 101–103](../../../../../src/storage/indexed.cpp#L101) | Callable definition: void unlocked() const | calls Error · [reviewed contract](#b0016) |
| [B0017 · 104–104](../../../../../src/storage/indexed.cpp#L104) | Callable definition: TupleHandle handle(const IndexedRow& row) const noexcept | calls ; returns {owner, relation, row.id} · [reviewed contract](#b0017) |
| [B0018 · 105–111](../../../../../src/storage/indexed.cpp#L105) | Callable definition: std::uint64_t transform_hash(std::uint64_t value) const noexcept | calls ; returns 0; value & ~std::uint64_t{0xffff} · [reviewed contract](#b0018) |
| [B0019 · 112–114](../../../../../src/storage/indexed.cpp#L112) | Callable definition: std::uint64_t hash(const Tuple& value, IndexWorkAllowance& work) const | calls transform_hash, detail::admitted_hash; returns transform_hash(detail::admitted_hash(value, work)) · [reviewed contract](#b0019) |
| [B0020 · 115–115](../../../../../src/storage/indexed.cpp#L115) | Callable definition: std::uint64_t diagnostic_hash(const Tuple& value) const | calls transform_hash, hash; returns transform_hash(value.hash()) · [reviewed contract](#b0020) |
| [B0021 · 116–121](../../../../../src/storage/indexed.cpp#L116) | Callable definition: IndexedRow* row(TupleHandle value, IndexWorkAllowance& work) const | calls owned, find; returns by_id.find(value.tuple.value, \[&\](const IndexedRow& candidate, IndexWorkAllowance&) {; candidate.id… · [reviewed contract](#b0021) |
| [B0022 · 122–127](../../../../../src/storage/indexed.cpp#L122) | Callable definition: IndexedRow* row(const Tuple& value, IndexWorkAllowance& work) const | calls input, hash, find, detail::admitted_equal; returns primary.find(value_hash, \[&\](const IndexedRow& candidate, IndexWorkAllowance& allowance) {; detail:… · [reviewed contract](#b0022) |
| [B0023 · 128–132](../../../../../src/storage/indexed.cpp#L128) | Callable definition: IndexedIndex* maybe_index(IndexId id, IndexWorkAllowance& work) const | calls find; returns indices.find(id.value, \[&\](const IndexedIndex& candidate, IndexWorkAllowance&) {; candidate.id == id · [reviewed contract](#b0023) |
| [B0024 · 133–137](../../../../../src/storage/indexed.cpp#L133) | Callable definition: IndexedIndex& index(IndexId id, IndexWorkAllowance& work) const | calls maybe_index, Error; returns *found · [reviewed contract](#b0024) |
| [B0025 · 138–145](../../../../../src/storage/indexed.cpp#L138) | Callable definition: IndexedKey* key(IndexedIndex& index, const Tuple& value, IndexWorkAllowance& work) const | calls target, same_token, layout, Error; returns index.keys.find(value_hash, \[&\](const IndexedKey& candidate, IndexWorkAllowance& allowance) {; deta… · [reviewed contract](#b0025) |
| [B0026 · 146–149](../../../../../src/storage/indexed.cpp#L146) | Callable definition: std::size_t slot_room(std::size_t pending = 0) const | calls room; returns limits.directory_slots - directory_slots - pending · [reviewed contract](#b0026) |
| [B0027 · 150–153](../../../../../src/storage/indexed.cpp#L150) | Callable definition: void arena_insert_room() const | calls statistics, room · [reviewed contract](#b0027) |
| [B0028 · 154–160](../../../../../src/storage/indexed.cpp#L154) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 161–162](../../../../../src/storage/indexed.cpp#L161) | Callable definition: IndexedTable::IndexedTable(RelationId relation, TupleLayout layout, IndexedLimits limits) : state_(std::make_shared&lt;State&gt;(relati… | calls state_, std::move; growth make_shared · [reviewed contract](#b0029) |
| [B0030 · 163–163](../../../../../src/storage/indexed.cpp#L163) | Callable definition: IndexedTable::IndexedTable(std::shared_ptr&lt;State&gt; state) noexcept : state_(std::move(state)) | calls state_, std::move · [reviewed contract](#b0030) |
| [B0031 · 164–166](../../../../../src/storage/indexed.cpp#L164) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 167–170](../../../../../src/storage/indexed.cpp#L167) | Callable definition: IndexedTable::State& IndexedTable::state() const | calls Error; returns *state_ · [reviewed contract](#b0032) |
| [B0033 · 171–171](../../../../../src/storage/indexed.cpp#L171) | Callable definition: StorageOwnerId IndexedTable::owner() const | calls state; returns state().owner · [reviewed contract](#b0033) |
| [B0034 · 172–172](../../../../../src/storage/indexed.cpp#L172) | Callable definition: RelationId IndexedTable::relation() const | calls state; returns state().relation · [reviewed contract](#b0034) |
| [B0035 · 173–173](../../../../../src/storage/indexed.cpp#L173) | Callable definition: const TupleLayout& IndexedTable::layout() const | calls state; returns state().layout · [reviewed contract](#b0035) |
| [B0036 · 174–174](../../../../../src/storage/indexed.cpp#L174) | Callable definition: const IndexedLimits& IndexedTable::limits() const | calls state; returns state().limits · [reviewed contract](#b0036) |
| [B0037 · 175–175](../../../../../src/storage/indexed.cpp#L175) | Callable definition: std::size_t IndexedTable::size() const | calls state, size; returns state().primary.size() · [reviewed contract](#b0037) |
| [B0038 · 176–176](../../../../../src/storage/indexed.cpp#L176) | Callable definition: std::uint64_t IndexedTable::revision() const | calls state; returns state().revision · [reviewed contract](#b0038) |
| [B0039 · 177–177](../../../../../src/storage/indexed.cpp#L177) | Callable definition: ArenaStatistics IndexedTable::arena_statistics() const | calls state, statistics; returns state().arena.statistics() · [reviewed contract](#b0039) |
| [B0040 · 178–184](../../../../../src/storage/indexed.cpp#L178) | Callable definition: IndexedStatistics IndexedTable::statistics() const | calls state, size, statistics; returns {s.primary.size(), s.indices.size(), s.key_nodes, s.live_key_nodes, · [reviewed contract](#b0040) |
| [B0041 · 185–185](../../../../../src/storage/indexed.cpp#L185) | Explanatory comments or spacing. |  |
| [B0042 · 186–188](../../../../../src/storage/indexed.cpp#L186) | Callable definition: InsertResult IndexedTable::insert(const Tuple& tuple, IndexWorkAllowance& work) | calls insert_impl; returns insert_impl(tuple, work, nullptr); growth insert · [reviewed contract](#b0042) |
| [B0043 · 189–291](../../../../../src/storage/indexed.cpp#L189) | Callable definition: InsertResult IndexedTable::insert_impl(const Tuple& tuple, IndexWorkAllowance& work, Journal::Data* journal) | calls state, unlocked, start, input; returns detail::admitted_equal(*candidate.tuple, tuple, grant); {false, s.handle(*found)}; growth emplace, insert, make_unique, push_back; 3 loop sites; source comment (unverified): // A new key's cached hash is set while private; publication never hashes. · [reviewed contract](#b0043) |
| [B0044 · 292–292](../../../../../src/storage/indexed.cpp#L292) | Explanatory comments or spacing. |  |
| [B0045 · 293–297](../../../../../src/storage/indexed.cpp#L293) | Callable definition: std::optional&lt;TupleHandle&gt; IndexedTable::find(const Tuple& tuple, IndexWorkAllowance& work) const | calls state, start, row, handle; returns {}; s.handle(*row) · [reviewed contract](#b0045) |
| [B0046 · 298–301](../../../../../src/storage/indexed.cpp#L298) | Callable definition: const Tuple* IndexedTable::get(TupleHandle handle, IndexWorkAllowance& work) const | calls state, start, row; returns row == nullptr ? nullptr : row-&gt;tuple · [reviewed contract](#b0046) |
| [B0047 · 302–307](../../../../../src/storage/indexed.cpp#L302) | Callable definition: TupleArena::Pin IndexedTable::pin(TupleHandle handle, IndexWorkAllowance& work) const | calls state, start, row, Error; returns s.arena.pin(row-&gt;allocation) · [reviewed contract](#b0047) |
| [B0048 · 308–308](../../../../../src/storage/indexed.cpp#L308) | Explanatory comments or spacing. |  |
| [B0049 · 309–320](../../../../../src/storage/indexed.cpp#L309) | Callable definition: void IndexedTable::State::prepare_erase(const IndexedRow& row, IndexWorkAllowance& work) const | calls start, admit, detail::admit_tuple_copy, first; 1 loop sites; source comment (unverified): // Conservative retirement allowance. · [reviewed contract](#b0049) |
| [B0050 · 321–330](../../../../../src/storage/indexed.cpp#L321) | Callable definition: void IndexedTable::State::erase_prepaid(IndexedRow& row) noexcept | calls first, size, erase, std::terminate; 1 loop sites · [reviewed contract](#b0050) |
| [B0051 · 331–334](../../../../../src/storage/indexed.cpp#L331) | Callable definition: void IndexedTable::State::erase_one(IndexedRow& row, IndexWorkAllowance& work) | calls mutable_revision, counter_room, prepare_erase, erase_prepaid · [reviewed contract](#b0051) |
| [B0052 · 335–339](../../../../../src/storage/indexed.cpp#L335) | Callable definition: bool IndexedTable::erase(const Tuple& tuple, IndexWorkAllowance& work) | calls state, unlocked, start, row; returns false; true · [reviewed contract](#b0052) |
| [B0053 · 340–344](../../../../../src/storage/indexed.cpp#L340) | Callable definition: bool IndexedTable::erase(TupleHandle handle, IndexWorkAllowance& work) | calls state, unlocked, start, row; returns false; true · [reviewed contract](#b0053) |
| [B0054 · 345–345](../../../../../src/storage/indexed.cpp#L345) | Explanatory comments or spacing. |  |
| [B0055 · 346–402](../../../../../src/storage/indexed.cpp#L346) | Callable definition: IndexId IndexedTable::add_index(Projection projection, IndexWorkAllowance& work) | calls state, unlocked, start, same_token; returns existing-&gt;id; detail::admitted_equal(candidate.tuple, projected, grant); growth make_unique, push_back; 3 loop sites; source comment (unverified): // The complete index and all bucket links are private. Only these row links · [reviewed contract](#b0055) |
| [B0056 · 403–403](../../../../../src/storage/indexed.cpp#L403) | Explanatory comments or spacing. |  |
| [B0057 · 404–424](../../../../../src/storage/indexed.cpp#L404) | Callable definition: bool IndexedTable::drop_index(IndexId id, IndexWorkAllowance& work) | calls state, unlocked, start, maybe_index; returns false; true; 2 loop sites · [reviewed contract](#b0057) |
| [B0058 · 425–432](../../../../../src/storage/indexed.cpp#L425) | Callable definition: std::vector&lt;IndexId&gt; IndexedTable::indices(IndexWorkAllowance& work) const | calls state, start, reserve_records, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 433–435](../../../../../src/storage/indexed.cpp#L433) | Callable definition: Projection IndexedTable::projection(IndexId id, IndexWorkAllowance& work) const | calls state, start, index; returns s.index(id, work).projection · [reviewed contract](#b0059) |
| [B0060 · 436–438](../../../../../src/storage/indexed.cpp#L436) | Callable definition: std::size_t IndexedTable::key_count(IndexId id, IndexWorkAllowance& work) const | calls state, start, index, size; returns s.index(id, work).live_keys.size() · [reviewed contract](#b0060) |
| [B0061 · 439–446](../../../../../src/storage/indexed.cpp#L439) | Callable definition: std::vector&lt;Tuple&gt; IndexedTable::keys(IndexId id, IndexWorkAllowance& work) const | calls state, start, index, reserve_records; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 447–456](../../../../../src/storage/indexed.cpp#L447) | Callable definition: std::vector&lt;TupleHandle&gt; IndexedTable::bucket(IndexId id, const Tuple& value, IndexWorkAllowance& work) const | calls state, start, index, key; returns result; result; growth push_back; 1 loop sites · [reviewed contract](#b0062) |
| [B0063 · 457–467](../../../../../src/storage/indexed.cpp#L457) | Callable definition: std::size_t IndexedTable::erase_key(IndexId id, const Tuple& value, IndexWorkAllowance& work) | calls state, unlocked, start, index; returns 0; rows.size(); growth push_back; 2 loop sites · [reviewed contract](#b0063) |
| [B0064 · 468–477](../../../../../src/storage/indexed.cpp#L468) | Callable definition: void IndexedTable::clear(IndexWorkAllowance& work) | calls state, unlocked, start, size; 2 loop sites · [reviewed contract](#b0064) |
| [B0065 · 478–485](../../../../../src/storage/indexed.cpp#L478) | Callable definition: std::vector&lt;Tuple&gt; IndexedTable::snapshot(IndexWorkAllowance& work) const | calls state, start, reserve_records, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0065) |
| [B0066 · 486–486](../../../../../src/storage/indexed.cpp#L486) | Explanatory comments or spacing. |  |
| [B0067 · 487–495](../../../../../src/storage/indexed.cpp#L487) | Type/record definition: struct IndexedTable::Cursor::Data |  · [reviewed contract](#b0067) |
| [B0068 · 496–496](../../../../../src/storage/indexed.cpp#L496) | Callable definition: IndexedTable::Cursor::Cursor(std::unique_ptr&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0068) |
| [B0069 · 497–499](../../../../../src/storage/indexed.cpp#L497) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0069) |
| [B0070 · 500–523](../../../../../src/storage/indexed.cpp#L500) | Callable definition: std::optional&lt;IndexedTable::Cursor::Entry&gt; IndexedTable::Cursor::next(IndexWorkAllowance& work) | calls Error, lock, get, unlocked; returns {}; {}; source comment (unverified): // A denial leaves both the cursor position and owner unchanged. · [reviewed contract](#b0070) |
| [B0071 · 524–530](../../../../../src/storage/indexed.cpp#L524) | Callable definition: IndexedTable::Cursor IndexedTable::live(IndexWorkAllowance& work) const | calls state, unlocked, start, admit; returns Cursor(std::move(data)); growth make_unique · [reviewed contract](#b0071) |
| [B0072 · 531–538](../../../../../src/storage/indexed.cpp#L531) | Callable definition: IndexedTable::Cursor IndexedTable::bucket_cursor(IndexId id, const Tuple& value, IndexWorkAllowance& work) const | calls state, unlocked, start, index; returns Cursor(std::move(data)); growth make_unique · [reviewed contract](#b0072) |
| [B0073 · 539–545](../../../../../src/storage/indexed.cpp#L539) | Type/record definition: struct IndexedTable::IndexKeyCursor::Data |  · [reviewed contract](#b0073) |
| [B0074 · 546–546](../../../../../src/storage/indexed.cpp#L546) | Callable definition: IndexedTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0074) |
| [B0075 · 547–549](../../../../../src/storage/indexed.cpp#L547) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0075) |
| [B0076 · 550–566](../../../../../src/storage/indexed.cpp#L550) | Callable definition: std::optional&lt;IndexedTable::IndexKeyCursor::Entry&gt; IndexedTable::IndexKeyCursor::next(IndexWorkAllowance& work) | calls Error, lock, get, unlocked; returns {}; Entry{key-&gt;tuple, key-&gt;members.size()} · [reviewed contract](#b0076) |
| [B0077 · 567–573](../../../../../src/storage/indexed.cpp#L567) | Callable definition: IndexedTable::IndexKeyCursor IndexedTable::index_keys(IndexId id, IndexWorkAllowance& work) const | calls state, unlocked, start, index; returns IndexKeyCursor(std::move(data)); growth make_unique · [reviewed contract](#b0077) |
| [B0078 · 574–574](../../../../../src/storage/indexed.cpp#L574) | Explanatory comments or spacing. |  |
| [B0079 · 575–582](../../../../../src/storage/indexed.cpp#L575) | Callable definition: IndexedTable::Cursor IndexedTable::Journal::live() const | calls Error, active, start, admit; returns Cursor(std::move(cursor)); growth make_unique · [reviewed contract](#b0079) |
| [B0080 · 583–592](../../../../../src/storage/indexed.cpp#L583) | Callable definition: IndexedTable::Cursor IndexedTable::Journal::bucket_cursor(IndexId id, const Tuple& value) const | calls Error, active, start, index; returns Cursor(std::move(cursor)); growth make_unique · [reviewed contract](#b0080) |
| [B0081 · 593–600](../../../../../src/storage/indexed.cpp#L593) | Callable definition: IndexedTable::IndexKeyCursor IndexedTable::Journal::index_keys(IndexId id) const | calls Error, active, start, index; returns IndexKeyCursor(std::move(cursor)); growth make_unique · [reviewed contract](#b0081) |
| [B0082 · 601–601](../../../../../src/storage/indexed.cpp#L601) | Explanatory comments or spacing. |  |
| [B0083 · 602–645](../../../../../src/storage/indexed.cpp#L602) | Callable definition: IndexedTable IndexedTable::snapshot_copy(IndexWorkAllowance& work) const | calls state, unlocked, start, admit; returns result; growth insert, push_back; 5 loop sites; source comment (unverified): // This is a private checked builder, not a public raw-ID constructor. · [reviewed contract](#b0083) |
| [B0084 · 646–646](../../../../../src/storage/indexed.cpp#L646) | Explanatory comments or spacing. |  |
| [B0085 · 647–776](../../../../../src/storage/indexed.cpp#L647) | Callable definition: void IndexedTable::check_invariants() const | calls state, check_invariants, contract, get; returns current &gt;= base && current - base == inserted - erased; base &gt;= current && base - current == erased…; growth insert; 12 loop sites · [reviewed contract](#b0085) |
| [B0086 · 777–778](../../../../../src/storage/indexed.cpp#L777) | controls preprocessing. |  · [reviewed contract](#b0086) |
| [B0087 · 779–788](../../../../../src/storage/indexed.cpp#L779) | Callable definition: void detail::IndexedTesting::collisions(IndexedTable& table, CollisionMode mode) | calls state, unlocked, contract, size · [reviewed contract](#b0087) |
| [B0088 · 789–791](../../../../../src/storage/indexed.cpp#L789) | controls preprocessing. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0088) |

## B0001

[Lines 1–18](../../../../../src/storage/indexed.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/indexed.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect the standalone indexed set backend to stable nodes, scalar admission, shared owner IDs and diagnostics. |
| inputs / outputs | Imports public indexed types and private directories/lists; opens crown::storage implementation scope. |
| invariants | This public-Tuple backend is separate from AccountedIndexedTable and does not add SQL NULL or bag weights. |
| ownership | Includes own no runtime table/account/grant. |
| failure | Missing/inconsistent declarations fail compilation; no runtime recovery layer is introduced. |
| cost | No runtime work for declarations; component allocations and operation grants belong to later primitives. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 19–25](../../../../../src/storage/indexed.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedJournalReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain journal cursor phase and the exact original work-grant owner. |
| inputs / outputs | Phase starts active; constructor moves a shared IndexWorkAllowance into work. |
| invariants | Commit marks committed; rollback marks aborted before undo. Cursor calls compare grant address, not remaining limits. |
| ownership | Shared reader may survive journal through cursors; it owns the grant but no table State or row. |
| failure | Noexcept construction; shared-token allocation occurs in journal(). |
| cost | Fixed phase/owner metadata and reference counts; no per-row snapshot. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0003

[Lines 26–31](../../../../../src/storage/indexed.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using detail::IndexedIndex;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the four private stable-node types used by this implementation. |
| inputs / outputs | Imports IndexedIndex, IndexedKey, IndexedMember and IndexedRow into the local helper scope. |
| invariants | Aliases preserve the original hook/node types and ownership definitions. |
| ownership | No new wrapper, state owner or allocation. |
| failure | Compile-time name resolution only. |
| cost | Zero runtime work. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

## B0004

[Lines 32–34](../../../../../src/storage/indexed.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contract(bool value, const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a failed private checked-builder or full-diagnostic assertion. |
| inputs / outputs | Boolean and borrowed message in; success returns, false throws storage_contract. |
| invariants | Does not repair or continue after inconsistent state; normal mutation validation has separate boundaries. |
| ownership | Message is borrowed on success; Error may own formatted diagnostic storage on failure. |
| failure | Error construction/allocation can also fail; no exception is swallowed. |
| cost | Constant successful branch, failure-only exception/diagnostic cost. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0005

[Lines 35–38](../../../../../src/storage/indexed.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void room(std::size_t current, std::size_t extra, std::size_t maximum)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an aggregate finite component limit before growth or retention. |
| inputs / outputs | Existing count, added count and maximum in; returns only if current+extra fits. |
| invariants | Subtraction form checks current first and avoids unsigned overflow; zero allows no objects. |
| ownership | Scalar inputs only, no resource reservation/refund. |
| failure | storage_capacity rejects before the caller publishes the affected mutation. |
| cost | Constant integer comparisons; component counts are not allocator bytes. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 39–42](../../../../../src/storage/indexed.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counter_room(std::uint64_t current, std::uint64_t extra = 1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent monotone ID/revision/action counters wrapping. |
| inputs / outputs | Checks extra against uint64 maximum minus current; default increment is one. |
| invariants | Successful future addition cannot reuse a committed ID or silently wrap action history. |
| ownership | Scalar validation only. |
| failure | storage_overflow before mutation; does not reset counters. |
| cost | Constant checked arithmetic. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0007

[Lines 43–48](../../../../../src/storage/indexed.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t work_product(std::size_t count, std::uint64_t cost)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Safely multiply a count by a conservative per-item work charge. |
| inputs / outputs | Returns uint64 count*cost, including zero cost. |
| invariants | Dependency asserts size_t has at most64 bits; division guard prevents product overflow. |
| ownership | Value only; no allowance created or consumed here. |
| failure | storage_overflow before an invalid reservation reaches admit. |
| cost | Constant checked arithmetic, independent of count. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp) |

## B0008

[Lines 49–49](../../../../../src/storage/indexed.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void start(IndexWorkAllowance& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one structural startup, visit or end action against the caller grant. |
| inputs / outputs | Borrows one allowance and admits structural_steps=1. |
| invariants | Nested calls reuse the same decreasing balance; failed attempts do not refill prior consumed work. |
| ownership | Does not own/copy/move the grant. |
| failure | Work-limit failure propagates before its caller advances the protected state. |
| cost | One fixed five-domain admission check/subtraction. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0009

[Lines 50–56](../../../../../src/storage/indexed.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reserve_records(std::vector<T>& records, std::size_t count, IndexWorkAllowance& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a standard-vector capacity after admitting conservative pointer-word metadata. |
| inputs / outputs | Vector, requested element count and caller grant in; reserves at least count capacity. |
| invariants | max_size and count*ceil(sizeof(T)/sizeof(void*)) are checked before reserve. Units are metadata words, not actual allocator requests. |
| ownership | Caller vector owns the resulting allocation; no query MemoryAccount is attached. |
| failure | Overflow/work denial or reserve bad_alloc propagates. Prior charges remain spent; no caller table links change here. |
| cost | Potential O(old size) move/reallocation and O(count*sizeof(T)) requested capacity; reserve can retain/grow implementation-selected capacity. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 57–81](../../../../../src/storage/indexed.cpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId owner = detail::new_storage_owner();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own all standalone indexed table data, finite limits, component counters and journal authority. |
| inputs / outputs | State contains fresh table owner, relation/layout, arena, three directories, population/high-water/action counters and optional journal reader/Data pointer. |
| invariants | Rows form a non-null classical set; members represent exact support independently of numeric payload. revision never rewinds; tentative actions are separate from committed counts. |
| ownership | State owns stable row/index/key nodes and arena; active journal holds it strongly, cursors weakly. Metadata uses ordinary allocation, not a query account. |
| failure | Fresh owner/arena identity or allocation may fail during construction; declarations create no replacement work grant. |
| cost | Retained size follows live plus journal-retired nodes, directory capacity and arena slot high-water; fixed counters avoid scans. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/owner.hpp](../../../../../src/storage/owner.hpp), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 82–85](../../../../../src/storage/indexed.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(RelationId value, TupleLayout schema, IndexedLimits configuration)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty finite table under a fresh storage/arena identity. |
| inputs / outputs | Moves layout, copies relation/limits, creates arena and empty primary/ID/index directories with configured directory maxima. |
| invariants | Directories initially allocate no bucket array; each later growth also checks the shared aggregate slot limit. |
| ownership | Owns one ordinary State and arena; copied immutable layout retains its original token. |
| failure | Owner exhaustion, arena validation/allocation and construction failures propagate with normal member cleanup. |
| cost | Fixed empty-state initialization plus State/arena shared ownership allocations; no row/index scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0012

[Lines 86–91](../../../../../src/storage/indexed.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~State() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy stable row nodes before index/key nodes while every actual hook owner survives. |
| inputs / outputs | Deletes each primary resident row, then each resident index; member destructors detach hooks. |
| invariants | Active journals hold State, so final State destruction has no live detached undo-owned rows. It walks resident lists rather than historical logical IDs. |
| ownership | Releases node/member/key allocations; member destruction later closes arena membership and payloads. Pins may retain the arena metadata/payload after State dies. |
| failure | No throwing recovery; private hook/destructor inconsistency terminates. |
| cost | O(live rows+indices+keys+memberships) explicit node teardown plus payload release and eventual O(arena slot high-water) metadata destruction; no directory-capacity search in these loops. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0013

[Lines 92–95](../../../../../src/storage/indexed.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input(const Tuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact immutable source-layout token before row hashing/equality. |
| inputs / outputs | Borrows Tuple; compares its layout token with State layout. |
| invariants | Descriptor/ID/field equality does not authorize an independently compiled layout token. |
| ownership | No tuple copy, pin or owner change. |
| failure | layout_mismatch rejects incompatible token before row probe. |
| cost | Constant token check; tuple cell validation occurred at construction. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp) |

## B0014

[Lines 96–99](../../../../../src/storage/indexed.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(TupleHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject handles from another storage owner or relation. |
| inputs / outputs | TupleHandle in; checks owner and relation before logical-ID lookup. |
| invariants | TupleId alone is table-scoped and never enough to authorize lookup. Generation identity stays private in the arena handle. |
| ownership | Scalar handle does not pin or own payload. |
| failure | foreign_handle rejects a foreign owner/relation, including a similarly numbered row elsewhere. |
| cost | Constant scalar comparisons. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/table_types.hpp](../../../../../include/crown/storage/table_types.hpp) |

## B0015

[Lines 100–100](../../../../../src/storage/indexed.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mutable_revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the next mutation can advance the monotone cursor revision. |
| inputs / outputs | Validates room for one revision increment. |
| invariants | Does not increment on failure/no-op; rollback deliberately does not rewind real tentative mutation revisions. |
| ownership | No ownership or allocation on success. |
| failure | storage_overflow before mutation if revision exhausted. |
| cost | Constant counter check. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0016

[Lines 101–103](../../../../../src/storage/indexed.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlocked() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce exclusive journal mutation/cursor access at ordinary entry points. |
| inputs / outputs | Reads journal_active and rejects when a journal owns the table scope. |
| invariants | This writer fence is not isolation: point lookups and owning snapshots can still inspect installed tentative contents. |
| ownership | No lock, thread synchronization or retained owner is created. |
| failure | storage_busy before protected ordinary mutation/cursor traversal. |
| cost | One cached Boolean branch; callers still externally synchronize concurrent access. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0017

[Lines 104–104](../../../../../src/storage/indexed.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleHandle handle(const IndexedRow& row) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Form a table-scoped logical handle for an admitted row. |
| inputs / outputs | Combines State owner/relation with row.id. |
| invariants | Does not resolve liveness or pin; tentative handles must remain internal until commit. |
| ownership | Fixed scalar value only. |
| failure | Noexcept under valid row lifetime. |
| cost | Constant construction. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0018

[Lines 105–111](../../../../../src/storage/indexed.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t transform_hash(std::uint64_t value) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the coherent test-only collision profile without changing production hashing. |
| inputs / outputs | Production returns value; testing may zero full hash or its low16 bits. |
| invariants | Testing setter admits same_bucket only within the &lt;=65536 directory domain. No runtime production hash callback exists. |
| ownership | Scalar result, no table graph or grant. |
| failure | Noexcept; invalid mode is rejected by the testing authority before assignment. |
| cost | Constant production passthrough or test branches. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp) |

## B0019

[Lines 112–114](../../../../../src/storage/indexed.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t hash(const Tuple& value, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge full typed-row hash work before computing a cached/probe hash. |
| inputs / outputs | Borrows Tuple and caller allowance; returns possibly test-transformed admitted_hash. |
| invariants | Full typed equality remains authoritative under collisions; no numeric count or empty sentinel decides membership. |
| ownership | Read-only tuple view/borrow, no payload clone; hash is cached by node publication. |
| failure | Work denial or underlying scalar/hash errors propagate during preparation/probe, before publication/undo. |
| cost | Two-pass conservative scalar/framing admission plus actual field/byte hashing; representation-dependent decimal formatting may allocate. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [docs/scalars.md](../../../../scalars.md) |

## B0020

[Lines 115–115](../../../../../src/storage/indexed.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t diagnostic_hash(const Tuple& value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the expected cached hash during the explicit invariant diagnostic. |
| inputs / outputs | Tuple in; returns native tuple hash with the same test collision transformation. |
| invariants | Does not synthesize or debit an operational allowance; diagnostic is separate from live probe/cursor paths. |
| ownership | Only temporary value views/possible formatter output. |
| failure | Underlying value/hash allocation/errors propagate from diagnostic. |
| cost | Full scalar field/byte hashing, with representation-dependent decimal formatting; not constant work. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [docs/scalars.md](../../../../scalars.md) |

## B0021

[Lines 116–121](../../../../../src/storage/indexed.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedRow* row(TupleHandle value, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a table-authorized logical ID to its live stable row. |
| inputs / outputs | Checks handle owner/relation, probes ID directory using numeric ID hash and exact ID comparison; returns row or null. |
| invariants | Absent committed IDs stay absent; journal-retired rows are unlinked even if pinned. |
| ownership | Borrowed raw row pointer; caller keeps State and prevents intervening mutation. |
| failure | Foreign handle/work denial propagates; same-owner absent ID returns null. |
| cost | One directory-start charge plus actual chain visits; expected O(1), worst O(rows) collisions; no tuple hashing/copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0022

[Lines 122–127](../../../../../src/storage/indexed.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedRow* row(const Tuple& value, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an exact typed row value under its compiled token. |
| inputs / outputs | Checks source token, admits row hash and probes primary with admitted full equality; returns stable row or null. |
| invariants | Hash collision cannot merge distinct typed tuples; equality may be conservatively charged beyond actual short-circuit work. |
| ownership | Borrows probe/candidates and returns an unpinned row pointer. |
| failure | Layout/work/scalar failure propagates without changing membership. |
| cost | Hash field/byte cost plus visited hash chain and equality payload admissions; expected lookup depends on hash distribution. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp) |

## B0023

[Lines 128–132](../../../../../src/storage/indexed.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedIndex* maybe_index(IndexId id, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a registered index by table-local logical ID. |
| inputs / outputs | Probes indices directory with id.value; returns borrowed pointer or null. |
| invariants | IndexId contains no owner token; callers use this table's registered IDs. Cached ID hash and exact scalar equality decide hit. |
| ownership | No new index/projection owner or allocation. |
| failure | Work-limit failure propagates; absent ID returns null. |
| cost | Directory startup/visited-chain charges, expected O(1) and worst O(indices). |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0024

[Lines 133–137](../../../../../src/storage/indexed.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedIndex& index(IndexId id, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live index rather than silently accepting a missing one. |
| inputs / outputs | Calls maybe_index and returns borrowed IndexedIndex reference. |
| invariants | A dropped/missing ID cannot alias an arbitrary index through default insertion. |
| ownership | Borrow valid until index drop/State loss; no allocation on successful lookup. |
| failure | unknown_index for absence; work failure propagates. |
| cost | One actual directory lookup plus constant null check. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0025

[Lines 138–145](../../../../../src/storage/indexed.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedKey* key(IndexedIndex& index, const Tuple& value, IndexWorkAllowance& work) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe a secondary key using its projection target token and exact value. |
| inputs / outputs | Index/key in; checks target token, admits key hash/equality and returns key node or null. |
| invariants | A journal may retain an empty resident key; public degree/list operations use live membership separately. |
| ownership | Returns borrowed key; no key projection, copy or pin. |
| failure | layout_mismatch/work/scalar errors before modifying membership. |
| cost | Field/byte hash plus visited key chain/equality admissions; expected O(1) lookup, linear collision worst case. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0026

[Lines 146–149](../../../../../src/storage/indexed.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t slot_room(std::size_t pending = 0) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute remaining aggregate directory slots including privately prepared growth. |
| inputs / outputs | Checks directory_slots+pending against the table limit, returns the remainder. |
| invariants | Multiple independent replacement arrays cannot each spend the same aggregate free slot allowance. |
| ownership | Scalar capacity calculation; physical allocation remains with Growth tokens/directories. |
| failure | storage_capacity before a composing preparation exceeds aggregate limit. |
| cost | Constant arithmetic, no array scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0027

[Lines 150–153](../../../../../src/storage/indexed.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arena_insert_room() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one new arena slot only when no reusable slot already exists. |
| inputs / outputs | Reads fixed ArenaStatistics; checks arena_slots if free_slots is zero. |
| invariants | Retained/exhausted metadata consumes slot capacity; reusing a free slot requires no additional logical slot room. |
| ownership | No allocation or slot mutation here. |
| failure | storage_capacity before arena growth; arena still validates domain/generation in insert. |
| cost | Constant cached-statistics check. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0028

[Lines 154–160](../../../../../src/storage/indexed.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_erase(const IndexedRow& row, IndexWorkAllowance& work) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the split erase preparation and prepaid publication helpers and include the single journal definition. |
| inputs / outputs | State exposes prepare_erase, erase_prepaid and erase_one privately; indexed_journal.inc is included after complete State. |
| invariants | Fallible grants/validation precede nonthrowing removal; the include contributes no second translation unit or owner authority. |
| ownership | Declarations transfer nothing; later bodies and journal record owners define lifetime. |
| failure | Compilation enforces matching bodies/types; no runtime handler here. |
| cost | No declaration/include runtime cost. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc) |

## B0029

[Lines 161–162](../../../../../src/storage/indexed.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexedTable(RelationId relation, TupleLayout layout, IndexedLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate one empty standalone indexed table State. |
| inputs / outputs | Relation/layout/finite limits in; make_shared&lt;State&gt; stored in facade. |
| invariants | No unlimited default or separate per-operation allowance is created. |
| ownership | Facade owns State strongly; layout retains original immutable token. Metadata is ordinary allocation. |
| failure | Construction/owner/arena failures unwind unpublished members. |
| cost | Fixed State/arena ownership allocations plus empty directory construction. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 163–163](../../../../../src/storage/indexed.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexedTable(std::shared_ptr<State> state) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a temporary private facade over the journal's exact State. |
| inputs / outputs | Moves a known valid shared State owner into state_. |
| invariants | Used by journal insert; does not copy the table, replace grant or allocate a fresh owner ID. |
| ownership | Shares State only; temporary destructor releases its reference. |
| failure | Noexcept shared_ptr move under private valid-State precondition. |
| cost | Constant owner transfer; shared owner increment occurs at the call argument. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc) |

## B0031

[Lines 164–166](../../../../../src/storage/indexed.cpp#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::~IndexedTable() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use shared-owner move/destruction for the standalone table facade. |
| inputs / outputs | Default destructor/move constructor/move assignment transfer or release state_. |
| invariants | Moving preserves the same State identity; source becomes moved-from. Move replacement releases old State and can trigger its teardown. |
| ownership | Final State owner destroys resident graph; active journals can extend it, ordinary weak cursors cannot. |
| failure | Noexcept move/destruction relies on private nonthrowing State/node/arena cleanup. |
| cost | Move transfer fixed; release may destroy complete old graph and arena metadata/payloads. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0032

[Lines 167–170](../../../../../src/storage/indexed.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::State& IndexedTable::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject facade use after its State owner has been moved away. |
| inputs / outputs | Returns mutable private State through const facade or throws when state_ is empty. |
| invariants | Constness permits controlled grant/statistics plumbing, not thread-safe concurrent mutation. |
| ownership | Returned reference borrows facade/journal-owned State. |
| failure | invalid_storage for moved-from table. |
| cost | Constant shared pointer check/dereference. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0033

[Lines 171–171](../../../../../src/storage/indexed.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId IndexedTable::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read storage owner identity. |
| inputs / outputs | Returns StorageOwnerId scalar. |
| invariants | Owner scopes logical handles across all tables/relations. |
| ownership | Scalar copy. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant getter, no scan/allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0034

[Lines 172–172](../../../../../src/storage/indexed.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId IndexedTable::relation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the table relation identity. |
| inputs / outputs | Returns RelationId scalar. |
| invariants | Relation alone does not authorize a foreign handle. |
| ownership | Scalar copy. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant getter, no scan/allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0035

[Lines 173–173](../../../../../src/storage/indexed.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& IndexedTable::layout() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the compiled source layout. |
| inputs / outputs | Returns const TupleLayout reference. |
| invariants | No descriptor reconstruction or new immutable token. |
| ownership | Reference requires State lifetime; copy the layout handle to retain it. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant getter, no scan/allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0036

[Lines 174–174](../../../../../src/storage/indexed.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const IndexedLimits& IndexedTable::limits() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow finite component configuration. |
| inputs / outputs | Returns const IndexedLimits reference. |
| invariants | Counts are per table and do not impose allocator-byte/CPU caps. |
| ownership | Reference requires State lifetime. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant getter, no scan/allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0037

[Lines 175–175](../../../../../src/storage/indexed.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t IndexedTable::size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read installed live set cardinality. |
| inputs / outputs | Returns primary resident count. |
| invariants | Excludes journal-retired rows and has no SQL multiplicity semantics. |
| ownership | Scalar copy. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant cached count. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0038

[Lines 176–176](../../../../../src/storage/indexed.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t IndexedTable::revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read monotone cursor invalidation revision. |
| inputs / outputs | Returns current revision. |
| invariants | Real tentative mutations advance it; commit/rollback do not rewind. |
| ownership | Scalar copy. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant cached counter. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0039

[Lines 177–177](../../../../../src/storage/indexed.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics IndexedTable::arena_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read arena slot/pin classifications. |
| inputs / outputs | Returns fixed ArenaStatistics by value. |
| invariants | Live/retained/free/exhausted counts describe allocation states, not bytes or logical action history. |
| ownership | Fixed value copy, no retained payload. |
| failure | Moved-from State rejection propagates; successful getter allocates nothing. |
| cost | Constant cached counter copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0040

[Lines 178–184](../../../../../src/storage/indexed.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedStatistics IndexedTable::statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current populations, historical actions and pending journal counts without traversal. |
| inputs / outputs | Returns fixed IndexedStatistics assembled from cached table/directory/arena counters. |
| invariants | keys includes private retained empties; live_keys excludes them; tentative insert/erase counters are not yet committed. copied baselines reconcile snapshots. |
| ownership | Fixed value copy does not pin payload or own a result graph. |
| failure | Moved-from State rejection only on the normal valid-state path. |
| cost | Constant number of cached reads, no full invariant scan or allocator-byte measurement. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0042

[Lines 186–188](../../../../../src/storage/indexed.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult IndexedTable::insert(const Tuple& tuple, IndexWorkAllowance& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform ordinary set insertion using the caller's existing allowance. |
| inputs / outputs | Forwards Tuple and grant to insert_impl with no journal record owner. |
| invariants | Ordinary journal exclusion, duplicate no-op and publication rules are enforced in the shared implementation. |
| ownership | Input borrowed; successful row arena owns its representation-dependent Tuple copy. |
| failure | All implementation failures propagate; no catch or fresh grant. |
| cost | Shared implementation's probe/preparation/publication cost, plus fixed forwarding. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0043

[Lines 189–291](../../../../../src/storage/indexed.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult IndexedTable::insert_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe then prepare a complete row and all secondary memberships before atomic publication. |
| inputs / outputs | Tuple, borrowed allowance and optional active journal Data in; duplicate returns existing handle, success returns fresh logical handle. |
| invariants | Exact source token/hash/equality checked first. IDs, revision, committed+pending counters, all node/member/arena capacities and journal inverse work are checked before live links change. |
| ownership | Private unique row/member/key owners, Growth tokens and arena copy fund publication; journal optionally retains exact payload pin/Undo. |
| failure | All throwing preparation may spend work yet leaves prior live graph/counters intact. After arena installation valid fresh pin/get and prepaid operations must not fail; corruption terminates. |
| cost | Primary probe plus O(I) projections/key probes/members, scalar payload costs, potential directory rehash/array allocation and arena Tuple copy; expected hash cost assumes distribution. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

```text
auto primary_growth = s.primary.prepare_growth(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare primary/ID replacement arrays and one privately owned row before any publication. |
| inputs / outputs | Requests enough capacity for one row; accounts pending primary slots when preparing ID directory; allocates row and reserves per-index Prepared records. |
| invariants | Aggregate directory slots cannot be spent twice; all Growth tokens retain old owner/capacity metadata for later checked publication. |
| ownership | Growth/unique_ptr/vector own only private allocations, and unwind without reading stale key pointers through member destructors. |
| failure | Capacity/work/allocation failure discards private preparation; existing directories remain unchanged. |
| cost | Possible O(primary capacity+rows+ID capacity) growth work, O(I) preparation metadata and one row node allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

```text
auto projected = detail::admitted_projection(index->projection, tuple, work);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one exact secondary key/member, including conservative journal release work. |
| inputs / outputs | Each registered projection produces a typed key; existing key is reused, missing key receives private node/Growth, one member is linked only into the private row. |
| invariants | Empty retained journal keys may reactivate. New cached key hashes are set privately; journal reference room is checked before publishing the Undo. |
| ownership | Prepared vector owns new keys/Growth, row owns staged members, Undo stores raw pointers/pin later. Bucket/live-key membership is still unchanged. |
| failure | Projection/hash/equality/work/limits/allocation failure cleans private ownership; no key/index row publication occurs. |
| cost | O(projected fields/bytes+visited key chains) per index, one membership allocation and optional key/directory allocation; O(I) fixed records. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

```text
row->allocation = s.arena.insert(tuple);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the final row payload only after all fallible index preparation is complete. |
| inputs / outputs | Admits Tuple-copy scalar work, inserts the public Tuple into arena, resolves its stable address and optionally pins the fresh allocation. |
| invariants | Fresh handle, checked total pin room and same exact layout make following get/pin valid without new allocation/admission. This is the last fallible payload allocation boundary. |
| ownership | Arena owns row Tuple; legacy Tuple copy deep-copies Row bytes while native Tuple copy shares immutable payload; journal pin retains that exact address. |
| failure | Arena allocation/copy failure leaves live table graph intact. After successful insertion the remaining valid-state operations cannot throw. |
| cost | Actual representation-dependent Tuple copy plus arena slot/vector growth or reusable-slot update, then fixed pin bookkeeping. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

```text
s.primary.publish_growth(std::move(primary_growth));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the fully prepared row/index mutations with cached hashes and prepaid pointer writes. |
| inputs / outputs | Swaps prepared arrays, publishes new keys/live keys/bucket members, links row primary+ID, updates component/ID/revision/action counters and optional journal history. |
| invariants | No hash/projection/allocation/new grant is invoked in this phase; prepared ownership is released only after its live links are installed. |
| ownership | Live State assumes row/member/key ownership; obsolete arrays remain in Growth tokens until destruction. Undo owns the retained pin and inverse locations. |
| failure | Noexcept helpers terminate on impossible owner/capacity/hook inconsistencies; catching and continuing would corrupt the prepared transaction boundary. |
| cost | O(rehashed resident nodes+I) prepaid pointer operations, O(I) counters/history references and obsolete-array release. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc) |

## B0045

[Lines 293–297](../../../../../src/storage/indexed.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> IndexedTable::find(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Look up a typed row without returning a payload borrow or new owner. |
| inputs / outputs | Admits startup, resolves row by exact value; returns optional logical handle. |
| invariants | Can observe tentative installed state; caller keeps tentative handles internal until journal commit. |
| ownership | Handle contains no pin; probe remains borrowed. |
| failure | Layout/work/scalar failures propagate; ordinary absence returns empty. |
| cost | Tuple hash/equality and visited primary chain cost; no output collection allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp) |

## B0046

[Lines 298–301](../../../../../src/storage/indexed.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple* IndexedTable::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a live immutable Tuple through an authorized logical handle. |
| inputs / outputs | Admits startup and ID-directory lookup; returns original Tuple address or null. |
| invariants | Foreign owner/relation rejects; retired pinned rows are absent; installed tentative contents remain observable internally. |
| ownership | No copy/pin; caller must keep State alive and avoid invalidating mutation. A retained arena Pin has a separate contract. |
| failure | Foreign/work errors propagate; same-owner absence returns null. |
| cost | Visited ID chain cost, no tuple hash or success allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0047

[Lines 302–307](../../../../../src/storage/indexed.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin IndexedTable::pin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the exact live arena allocation beyond row membership/table-facade lifetime. |
| inputs / outputs | Admits startup/ID lookup, checks total pin component room, returns arena Pin. |
| invariants | Only a current live row can acquire a new public pin; pin does not retain table membership or cursor validity. |
| ownership | Pin strongly owns arena State and payload; its last release can reclaim payload or destroy closed arena metadata. |
| failure | stale_handle on absence, foreign/capacity/work/arena validation errors propagate before successful increment. |
| cost | ID lookup plus constant arena checks/increment; last-release payload/slot-high-water teardown is separate. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0049

[Lines 309–320](../../../../../src/storage/indexed.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::State::prepare_erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit complete row/member/key retirement work without removing any membership. |
| inputs / outputs | Known live row and caller allowance in; charges row startup, directory unlink, member list removals and possible final-key cleanup for each membership. |
| invariants | Bulk erase can empty a key only after earlier rows are removed; charging potential cleanup for every member makes the whole batch safe before first removal. |
| ownership | Borrows live row/key payloads; conservative admit_tuple_copy charges are retirement work, not actual payload clones. |
| failure | Any work/contract failure precedes affected live mutation and keeps earlier consumed work spent. |
| cost | O(I) membership/field/byte admission, with conservative duplicate key-payload charges across bulk rows. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp) |

## B0050

[Lines 321–330](../../../../../src/storage/indexed.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::State::erase_prepaid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one fully prepaid live row and release keys only after their last member. |
| inputs / outputs | Known row in; iterative member deletion detaches both lists, deletes newly empty keys, erases arena membership and deletes row/directory hooks. |
| invariants | Caller excludes journal scope and prepaid all work/counters; each member belongs to exactly one key/index and row. Pins keep payloads without membership. |
| ownership | Deletes row-owned members and empty keys, releases arena membership; unpinned payload may be freed, free/exhausted metadata remains. |
| failure | Noexcept; unexpected arena nonmembership or hook mismatch terminates rather than reporting partial success. |
| cost | O(I) targeted node/list bookkeeping plus actual key/row payload destruction; no projection/hash/ID lookup or unrelated scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0051

[Lines 331–334](../../../../../src/storage/indexed.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::State::erase_one(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine single-row revision/counter checks, retirement admission and prepaid erasure. |
| inputs / outputs | Known row and grant in; real success advances revision and committed erased_rows. |
| invariants | Counter headroom and all deletion charges precede erasure; absence is handled by public callers before this helper. |
| ownership | Releases exactly that row/members and newly empty keys; pins may survive. |
| failure | Preparation failure leaves row unchanged; prepaid corruption terminates. |
| cost | One retirement scan then O(1+I) deletion/payload cleanup; no whole-table pass. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0052

[Lines 335–339](../../../../../src/storage/indexed.cpp#L335); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool IndexedTable::erase(const Tuple&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase one row by typed value. |
| inputs / outputs | Borrowed exact Tuple probe in; returns erased/absent Boolean. |
| invariants | Ordinary mutation rejects an active journal. Absent row is a no-op without revision/counter change; real erase prepares fully first. |
| ownership | Probe/handle does not pin; State/arena release live ownership only after lookup and admission. |
| failure | Layout or foreign-handle errors as applicable, work/counter rejection and allocation in diagnostics propagate before removal. |
| cost | Lookup (value hash/equality or numeric ID chain) plus per-index retirement scan and actual node/payload teardown. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0053

[Lines 340–344](../../../../../src/storage/indexed.cpp#L340); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool IndexedTable::erase(TupleHandle
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase one row by authorized handle. |
| inputs / outputs | Table-scoped logical handle in; returns erased/absent Boolean. |
| invariants | Ordinary mutation rejects an active journal. Absent row is a no-op without revision/counter change; real erase prepares fully first. |
| ownership | Probe/handle does not pin; State/arena release live ownership only after lookup and admission. |
| failure | Layout or foreign-handle errors as applicable, work/counter rejection and allocation in diagnostics propagate before removal. |
| cost | Lookup (value hash/equality or numeric ID chain) plus per-index retirement scan and actual node/payload teardown. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0055

[Lines 346–402](../../../../../src/storage/indexed.cpp#L346); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId IndexedTable::add_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build and publish one compiled-projection index over all live rows. |
| inputs / outputs | Projection and borrowed work grant in; same token returns existing IndexId, otherwise fresh monotone IndexId. |
| invariants | Source-layout token required; independently compiled equivalent projection may be distinct. No live row hook/index identity is published until the complete private key/member graph exists. |
| ownership | Private index owns keys; temporary unique_ptr vector owns members while buckets borrow them. Projection retains immutable compiled program. |
| failure | Grant/capacity/ID/revision/allocation/projection failures leave existing live graph unchanged; staged destructor hook cleanup preserves old row owners. |
| cost | O(I) projection-token scan plus O(N) projected key probes and member allocations, new key/directory capacity and scalar bytes; hash collision worst case can be quadratic in build probes. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

```text
std::vector<std::unique_ptr<IndexedMember>> members;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep privately bucket-linked members uniquely owned until all row/index publication is safe. |
| inputs / outputs | Reserves N member owners; scans live rows to project/hash/probe, creates missing keys and stages member bucket links under the new private index. |
| invariants | Existing row membership capacity is checked before publication; cleanup uses actual hook owners even if raw key pointers have retired. |
| ownership | Vector uniquely owns staged members; private index owns key nodes and only borrows members until final row-link transfer. |
| failure | Allocation/work/scalar failure destroys private graph and member owners without mutating existing row hooks or counters. |
| cost | O(N) pointer-owner scratch plus N member nodes and distinct key values/arrays; actual projection and visited-chain costs remain. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

```text
s.indices.publish_growth(std::move(id_growth));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the completed private index using prepaid row hooks and cached identity. |
| inputs / outputs | Publishes index-ID growth, links every prepared member into its row, links index, then updates exact node/key/member/slot/action counters. |
| invariants | No throwing preparation remains; key/bucket data already complete and all capacity/link work admitted. |
| ownership | Releases member unique owners to rows and index unique owner to State only after their links become live. |
| failure | Noexcept hook/Growth invariants terminate on corruption; no recoverable catch after partial link changes. |
| cost | O(N) row link writes plus ID-directory resident rehash if grown and fixed counters. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0057

[Lines 404–424](../../../../../src/storage/indexed.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool IndexedTable::drop_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pre-admit every membership/key retirement before destroying a registered index. |
| inputs / outputs | IndexId/grant in; missing returns false, success releases index/key/member nodes and updates component/revision/committed drop counts. |
| invariants | Active journal excluded; keys/members are walked before any deletion. Table rows remain live and member destructors detach their row hooks. |
| ownership | Index owns keys; row-owned membership nodes are deleted by key teardown. Per-key directory array is freed; shared indices directory capacity is retained. |
| failure | Lookup/counter/work/contract rejection precedes deletion. Nonthrowing destructor corruption terminates. |
| cost | O(keys+memberships) admission and teardown plus key payload bytes; expected ID lookup, no scan of unrelated rows. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

## B0058

[Lines 425–432](../../../../../src/storage/indexed.cpp#L425); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<IndexId> IndexedTable::indices(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect registered index IDs in resident insertion order. |
| inputs / outputs | Admits startup/vector capacity and each resident step; returns standard owning IndexId vector. |
| invariants | IDs remain local to this State; output may describe installed tentative state but index registration cannot change during journal. |
| ownership | Output owns only scalar handles, not index/payload lifetime. |
| failure | Work/overflow/vector allocation failures propagate without table mutation. |
| cost | O(I) traversal/output storage and possible allocation; not historical-ID scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0059

[Lines 433–435](../../../../../src/storage/indexed.cpp#L433); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection IndexedTable::projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an index's existing compiled projection handle. |
| inputs / outputs | IndexId/grant in; resolves live index and returns Projection copy. |
| invariants | Returns the same immutable token, not a recompiled field-equivalent program. |
| ownership | Shared Projection owner survives index/table drop independently. |
| failure | unknown_index/work/moved-State errors propagate. |
| cost | ID-directory chain lookup plus constant shared-owner copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp) |

## B0060

[Lines 436–438](../../../../../src/storage/indexed.cpp#L436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t IndexedTable::key_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the number of publicly nonempty secondary keys. |
| inputs / outputs | IndexId/grant in; returns index.live_keys.size(). |
| invariants | Excludes journal-retained empty resident keys and is distinct from row/member cardinality. |
| ownership | Scalar copy only. |
| failure | unknown_index/work errors propagate. |
| cost | Index lookup plus cached count; no key list scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0061

[Lines 439–446](../../../../../src/storage/indexed.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> IndexedTable::keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect owning copies of publicly live keys in first-live-key order. |
| inputs / outputs | IndexId/grant in; reserves vector and debits each live key/Tuple copy before push. |
| invariants | No empty journal-retained key or historical directory slot is visited; indexed order is not lexical. |
| ownership | Vector owns Tuple values; legacy payload copies deep, native immutable payload copies share. Caller memory is ordinary output storage. |
| failure | Work/overflow/allocation/Tuple-copy failures discard output without table mutation. |
| cost | O(Klive) visits and representation-dependent key bytes/copies plus vector allocation; conservative scalar admission can exceed actual native sharing. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0062

[Lines 447–456](../../../../../src/storage/indexed.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<TupleHandle> IndexedTable::bucket(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect logical handles from one exact secondary key's live member list. |
| inputs / outputs | Index/key/grant in; returns empty on missing key, otherwise owning vector of handles in member insertion order. |
| invariants | Target-layout token is checked before key probe. Handles do not keep payload or membership alive and tentative observations stay internal. |
| ownership | Only result vector is owned; original rows/keys are borrowed while traversing. |
| failure | Index/layout/work/vector overflow/allocation errors propagate; no table mutation. |
| cost | Key hash/equality chain probe plus O(degree) admitted visits/output words; no per-member ID lookup or tuple copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0063

[Lines 457–467](../../../../../src/storage/indexed.cpp#L457); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t IndexedTable::erase_key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase all rows under one exact key after preparing the whole affected set. |
| inputs / outputs | Index/key/grant in; missing returns0, otherwise returns erased live member count. |
| invariants | Active journal excluded; revision/aggregate erased counter and each affected row's full retirement are checked before first deletion. |
| ownership | Temporary row-pointer vector retains locations, not payload ownership; stable rows survive preparations and no duplicate row appears within a key. |
| failure | Work/vector/allocation/validation failure leaves entire live set unchanged; prepaid deletion has only invariant-termination boundary. |
| cost | Probe plus O(degree) scratch and O(degree*(1+I)) retirement/removal, including conservative key-byte admissions across shared keys. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0064

[Lines 468–477](../../../../../src/storage/indexed.cpp#L468); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::clear(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove every live row while retaining index registrations and historical allocation capacity. |
| inputs / outputs | Borrowed allowance in; empty table returns without revision/counter change. |
| invariants | Pre-admits every live row before first deletion, checks clear/erased/revision counters once, then removes via first-resident links. |
| ownership | Releases rows/members/keys and unpinned payloads; registered empty indexes, directory arrays and arena slots can remain. |
| failure | Any preparation failure preserves all live rows; nonthrowing deletion invariant failure terminates. |
| cost | Two live-population passes, O(N*(1+I)) row/membership retirement/removal plus payload bytes; no historical logical-ID or bucket-array scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0065

[Lines 478–485](../../../../../src/storage/indexed.cpp#L478); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> IndexedTable::snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect owning current-row values in live insertion order. |
| inputs / outputs | Borrows grant; reserves N Tuple slots, admits each visit/copy and returns vector. |
| invariants | Can observe tentative installed contents; caller must keep uncommitted observations internal. No new storage owner/handle identity is created. |
| ownership | Vector owns Tuple values: legacy Row bytes deep-copy, native payload ownership shares; table mutation cannot invalidate the owning result. |
| failure | Work/overflow/allocation/Tuple-copy errors release partial output and preserve table. |
| cost | O(N) visits/vector capacity plus representation-dependent payload copy/retention, not allocation-free cursor work. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0067

[Lines 487–495](../../../../../src/storage/indexed.cpp#L487); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedTable::Cursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a lazy row-or-bucket live traversal with weak State lifetime and revision fence. |
| inputs / outputs | Holds weak owner, optional shared journal reader, captured revision, mode and next row/member pointer; constructor snapshots revision. |
| invariants | Raw next pointers are dereferenced only after owner, journal phase/grant, active-reader and revision checks in next(). |
| ownership | Cursor uniquely owns fixed Data and optionally grant/reader; it does not retain table State or pin returned tuples. |
| failure | Data allocation occurs at factory after metadata admission; declaration itself adds no handler. |
| cost | Fixed state per cursor, independent of rows/directory high-water. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0068

[Lines 496–496](../../../../../src/storage/indexed.cpp#L496); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor::Cursor(std::unique_ptr<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the fully prepared lazy row cursor record. |
| inputs / outputs | Moves unique Data pointer into cursor. |
| invariants | Factory established owner/revision/mode/start pointer; no new validation/grant is invented here. |
| ownership | Sole Data owner moves, reader/grant references travel with it. |
| failure | Noexcept unique_ptr transfer. |
| cost | Constant transfer, no allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0069

[Lines 497–499](../../../../../src/storage/indexed.cpp#L497); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor::Cursor(Cursor&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer/destroy lazy cursor metadata through default unique ownership. |
| inputs / outputs | Default move constructor/assignment and destructor manage Data. |
| invariants | Moved-from next is rejected. Replacing cursor does not mutate rows or reset allowance. |
| ownership | Releases fixed Data and shared reader/grant, never strong table State; final grant destruction is its own owner release. |
| failure | Noexcept valid metadata cleanup; no recovery handler. |
| cost | Fixed metadata/shared-owner release; no row/index/directory scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0070

[Lines 500–523](../../../../../src/storage/indexed.cpp#L500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedTable::Cursor::Entry> IndexedTable::Cursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate borrowed-pointer authority then advance exactly one live link or detect end. |
| inputs / outputs | Caller allowance in; returns handle and const reference to original Tuple, or empty at end. |
| invariants | Checks moved/expired owner, aborted reader, exact journal grant, active-journal fence and captured revision before raw pointer use. start(work) precedes position change, including repeated end. |
| ownership | Temporary locked State lasts through the call only; Entry does not pin. Ordinary caller keeps State alive and borrow ends by mutation/owner loss. |
| failure | Validation/work denial leaves cursor position unchanged; Error diagnostics can allocate. If a newer journal is active, prior committed-reader cursor is blocked. |
| cost | O(1) checks/shared-owner locks and one admitted step; no hashing, ID lookup, projection, payload copy or successful allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0071

[Lines 524–530](../../../../../src/storage/indexed.cpp#L524); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor IndexedTable::live(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordinary lazy live-row cursor. |
| inputs / outputs | Checks no active journal, charges startup and ceil(sizeof(Data)/pointer) metadata, allocates Data at first primary resident. |
| invariants | Captures current revision; future real mutation invalidates even if rollback later restores rows. |
| ownership | Unique fixed Data owns weak State only; caller retains table; no rows copied/pinned. |
| failure | Busy/work/allocation errors preserve table and any prior cursor position. |
| cost | Constant startup/one metadata allocation, independent of live count and historical slots. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0072

[Lines 531–538](../../../../../src/storage/indexed.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor IndexedTable::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordinary lazy cursor over a probed secondary bucket. |
| inputs / outputs | Index/key/grant in; checks journal exclusion, resolves exact typed key and allocates bucket-mode Data at first member or empty. |
| invariants | Index source/target identity and active-state checks are preserved; end traversal still costs one step. |
| ownership | Weak State cursor borrows member nodes, not the probe Tuple; no handle buffer/payload pin. |
| failure | Busy/index/layout/work/allocation failures before cursor publication. |
| cost | Index/key lookup and scalar hash/equality work plus fixed metadata allocation; no degree-sized preparation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0073

[Lines 539–545](../../../../../src/storage/indexed.cpp#L539); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedTable::IndexKeyCursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store lazy first-live-key traversal under owner/revision/journal authority. |
| inputs / outputs | Holds weak State, optional shared reader, captured revision and next_key raw pointer. |
| invariants | Only publicly nonempty live-list keys are traversed; next validates all authority before raw dereference. |
| ownership | Unique fixed Data plus optional owning reader/grant, no index/key/State ownership. |
| failure | Allocation belongs to factories; declaration adds no operational guard. |
| cost | Fixed state, no key/row snapshot. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0074

[Lines 546–546](../../../../../src/storage/indexed.cpp#L546); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared lazy key cursor record. |
| inputs / outputs | Moves unique Data into cursor. |
| invariants | Factories already resolved index and captured live start/revision. |
| ownership | Exclusive metadata owner transfer only. |
| failure | Noexcept move. |
| cost | Constant, no allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0075

[Lines 547–549](../../../../../src/storage/indexed.cpp#L547); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move or release key cursor metadata using unique ownership. |
| inputs / outputs | Default moves/destructor transfer or release Data. |
| invariants | Moved-from next rejects; cursor destruction does not drop index or reset grant. |
| ownership | Weak table ownership remains weak; optional reader retains only original grant authority. |
| failure | Noexcept metadata cleanup. |
| cost | Fixed metadata/reference release, no key/directory traversal. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0076

[Lines 550–566](../../../../../src/storage/indexed.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<IndexedTable::IndexKeyCursor::Entry> IndexedTable::IndexKeyCursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one publicly live key and return its immutable key/degree borrow. |
| inputs / outputs | Caller allowance in; returns const key Tuple reference and cached live degree, or empty. |
| invariants | Owner/reader/grant/busy/revision fences precede pointer use; one startup charge precedes advancing or end. Numeric degree never decides whether key is in the live list. |
| ownership | Entry borrows key node; public contract ends borrow on next traversal, mutation/index drop or owner loss. Cursor keeps only weak State. |
| failure | Validation/work failures do not advance position; diagnostic exceptions may allocate. |
| cost | Constant checks/one link/admission and cached degree; no key hash/copy, bucket walk, ID lookup or successful allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0077

[Lines 567–573](../../../../../src/storage/indexed.cpp#L567); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexKeyCursor IndexedTable::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordinary lazy cursor over nonempty keys. |
| inputs / outputs | IndexId/grant in; rejects active journal, resolves index, admits fixed metadata and allocates Data at live_keys.first(). |
| invariants | Captured revision invalidates on any real table mutation/index drop; order is first-live-key, not lexical. |
| ownership | Unique fixed metadata borrows State/index/key list through weak owner. |
| failure | Busy/unknown_index/work/allocation errors propagate without mutation. |
| cost | Index lookup plus one fixed cursor allocation, independent of key population. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0079

[Lines 575–582](../../../../../src/storage/indexed.cpp#L575); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor IndexedTable::Journal::live() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner-journal traversal of the installed tentative live rows. |
| inputs / outputs | Uses active Data's original grant, admits startup/fixed Cursor metadata and returns first-resident row cursor. |
| invariants | Requires active original journal authority; cursor retains reader and exact grant. Commit keeps reader valid subject to revision; rollback aborts before undo, and a different active journal blocks it. |
| ownership | Cursor owns metadata/reader/grant but weak State only; the active journal itself owns State until close. Returned row entries are borrowed. |
| failure | Moved/closed journal, work/index/layout as applicable or allocation failure propagates before publishing cursor. |
| cost | Fixed metadata allocation and original-grant admissions; no population scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0080

[Lines 583–592](../../../../../src/storage/indexed.cpp#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Cursor IndexedTable::Journal::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner-journal traversal over one exact tentative bucket. |
| inputs / outputs | Index/key in; uses original grant, validates/probes index/key and returns bucket-mode cursor at first member or empty. |
| invariants | Requires active original journal authority; cursor retains reader and exact grant. Commit keeps reader valid subject to revision; rollback aborts before undo, and a different active journal blocks it. |
| ownership | Cursor owns metadata/reader/grant but weak State only; the active journal itself owns State until close. Returned bucket entries are borrowed. |
| failure | Moved/closed journal, work/index/layout as applicable or allocation failure propagates before publishing cursor. |
| cost | Index/key hash/equality lookup plus fixed metadata allocation, not O(degree) collection. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0081

[Lines 593–600](../../../../../src/storage/indexed.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::IndexKeyCursor IndexedTable::Journal::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner-journal traversal over current publicly nonempty keys. |
| inputs / outputs | IndexId in; uses original grant, resolves index and returns key cursor at live_keys.first(). |
| invariants | Requires active original journal authority; cursor retains reader and exact grant. Commit keeps reader valid subject to revision; rollback aborts before undo, and a different active journal blocks it. |
| ownership | Cursor owns metadata/reader/grant but weak State only; the active journal itself owns State until close. Returned key entries are borrowed. |
| failure | Moved/closed journal, work/index/layout as applicable or allocation failure propagates before publishing cursor. |
| cost | Index lookup plus fixed metadata allocation, no key population scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0083

[Lines 602–645](../../../../../src/storage/indexed.cpp#L602); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable IndexedTable::snapshot_copy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a new independent table graph preserving sparse live logical IDs and traversal order. |
| inputs / outputs | Source and caller grant in; rejects journal and returns fresh table/arena owner with same relation/layout/limits, high-water IDs and revision. |
| invariants | Source handles never authorize destination owner; no external pins or retired allocations copied. Destination records copied baselines and clears builder action counts. |
| ownership | New nodes/directories/arena identities are independent; public Tuple copies deep-copy legacy payloads or share native immutable payload. Projection tokens/layout remain shared. |
| failure | Work/allocation/checked-builder failure destroys the private result and leaves source graph unchanged; consumed grant/allocated owner IDs are not refunded. |
| cost | Rebuild N rows then I full indexes: O(N*(1+I)) row/projected-membership visits plus field/byte/probe/growth work and live-key order restoration; collision worst case exceeds linear. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

```text
copy.last_tuple = row->id.value - 1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve each sparse live tuple ID in a checked private snapshot builder. |
| inputs / outputs | For each source resident row, verifies increasing IDs, sets private last_tuple just before source ID and invokes ordinary result.insert. |
| invariants | Only private builder changes high-water; inserted flag and returned tuple ID must match source. No public raw-ID insertion API is added. |
| ownership | New result arena/node owns representation-dependent Tuple copy; source row borrow is read-only. |
| failure | Admission/allocation/contract failure destroys partial result; source is untouched. |
| cost | Per-row insertion with scalar hash/copy and directory growth; no scan through gaps in logical IDs. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

```text
std::vector<IndexedKey*> order;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore true source first-live-key order after rebuilding snapshot memberships. |
| inputs / outputs | For each copied index, probes every source live key, checks degree/population, saves destination pointers, admits list rewrite then rebuilds live-key list in source order. |
| invariants | Rebuilding from today's row order can differ from historical first-live-key order; no pointer into old directory arrays is retained. |
| ownership | Temporary vector owns only borrowed destination key pointers; source and private result outlive all probes/rewrites. |
| failure | Probe/work/allocation/contract failure affects only private result; all rewrite work admitted before removing first list link. |
| cost | O(Klive) pointer scratch and key probes plus two admitted key-list passes; actual scalar/hash-chain costs apply. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp) |

## B0085

[Lines 647–776](../../../../../src/storage/indexed.cpp#L647); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly rebuild expected graph, values and counters to diagnose ownership/layout/membership consistency. |
| inputs / outputs | Checks directories/arena; allocates standard sets/maps of nodes/values and verifies journal authority, cached hashes, projections, populations, limits and action reconciliation. |
| invariants | Diagnostic is separate from operational grants and not used by probes/next. It validates both live and retained rows, not just public cardinalities. |
| ownership | Temporary sets/maps/exported crown::Row copies own scratch; read-only State and original tuples remain borrowed. |
| failure | storage_contract or underlying arena/directory/value/allocation errors propagate; diagnostics are not a transactional repair path. |
| cost | O(directory capacity+arena high-water+node/journal population log population) structural work plus full row/key hashing, exported-value ordering/copies and O(N*I) projections; O(nodes+entries+exported bytes) scratch. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

```text
if (s.journal_active) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct expected active-journal authority, retained rows and key reference counts. |
| inputs / outputs | Walks active Undo entries, verifies exact pinned payload/handle/member pointers, counts inserted/erased actions and records erased rows/reference totals. |
| invariants | Journal reader/Data/State must agree; erased rows are uniquely retired and not live. Closed State may retain no tentative authority/counts. |
| ownership | Temporary sets/map count original row/key pointers; no ownership transfer or new pin. |
| failure | Contract/allocation errors during explicit diagnostic only. |
| cost | O(changes*I) pointer checks/map increments plus log scratch costs, independent of historical logical ID gaps. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc) |

```text
std::size_t expected_keys = 0, expected_live_keys = 0, expected_slots =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate each index's resident/live key separation, cached hash and exact bucket pointer populations. |
| inputs / outputs | Accumulates keys/livekeys/array slots; checks registered IDs/source token, key target token/reference counts and live membership iff nonempty. |
| invariants | Journal-only empty resident keys require positive inverse references; full typed equality remains separate from resident/live list bookkeeping. |
| ownership | Read-only graph plus temporary pointer sets. |
| failure | Diagnostic contract/hash/allocation errors propagate. |
| cost | All index/key/member visits plus directory capacity checks and full key hashing; O(keys+memberships) pointer scratch. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp) |

```text
std::uint64_t previous_id = 0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently verify every live row's set value, arena address, cached hashes and complete reverse index memberships. |
| inputs / outputs | Walks resident rows in increasing sparse ID order; exports values into a uniqueness set, checks source layout and per-index actual projection; cross-checks ID directory rows. |
| invariants | Exactly one membership per registered index; row- and bucket-side member populations equal. Payload arithmetic never substitutes for membership. |
| ownership | Temporary owning exported Rows and pointer/index sets; arena remains original owner. |
| failure | Diagnostic contract/projection/export/hash/allocation failures propagate. |
| cost | O(N*I) projection/member verification plus full value export/comparison/hash and O(population log population) scratch operations. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/scalars.md](../../../../scalars.md) |

```text
std::set<const IndexedMember*> retained_members;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify journal-retired row nodes remain detached yet retain complete original inverse memberships. |
| inputs / outputs | Checks every retired row absent from live directories, detached bucket links, resident referenced key and actual projection; totals retained rows/members. |
| invariants | Retired rows retain one row-owned member per registered index, key journal references prevent premature deletion, and no live member is reused. |
| ownership | Only scratch sets are owned; detached row/member/pin lifetime belongs to active Undo/State. |
| failure | Contract/projection/allocation diagnostic failures propagate. |
| cost | O(retired rows*I) projection/check work and O(retained memberships) pointer scratch. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_journal.inc](../../../../../src/storage/indexed_journal.inc), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

```text
const auto reconcile = [](
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile copied baselines and exact committed/pending action counts with current populations without unsigned sum overflow. |
| inputs / outputs | Lambda compares differences of uint64 counts; checks pending+committed headroom then row/index balance identities. |
| invariants | Rollback clears tentative actions without changing committed totals; snapshot baselines substitute for copied historical mutations. |
| ownership | Scalar comparisons only; no graph/memory ownership. |
| failure | storage_contract if accounting disagrees; diagnostic not a counter repair. |
| cost | Fixed arithmetic after the full graph diagnostic; no payload operations. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md) |

## B0086

[Lines 777–778](../../../../../src/storage/indexed.cpp#L777); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L777-L778:sha256:1834d0ff760d751b62a65a303099aee13ac4eeb3773e3bb9a703e5065d81c348
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/indexed.cpp: opens/branches compile-time guard \`#ifdef CROWN_STORAGE_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0087

[Lines 779–788](../../../../../src/storage/indexed.cpp#L779); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::IndexedTesting::collisions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a deterministic collision profile only through the private testing authority. |
| inputs / outputs | Requires unlocked fresh empty table with zero logical ID history, known enum and &lt;=65536 slots for same_bucket; writes collision_mode. |
| invariants | Cannot change cached hashes on a populated/historical owner. Compiled only in coherent CROWN_STORAGE_TESTING variant, no production callback. |
| ownership | Only scalar test mode changes, no index/grant owner. |
| failure | storage_contract/busy/moved-State rejection before assignment. |
| cost | Constant checks/write, no allocations on successful call. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage.md](../../../../storage.md), [Refactor.md §11.4 S01–S05](../../../../../Refactor.md), [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp) |

## B0088

[Lines 789–791](../../../../../src/storage/indexed.cpp#L789); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L789-L791:sha256:291eba6d80cb43bae7faf70bdb11f50856adc53444b79a59b5277f805c2e4acf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/indexed.cpp: closes the matching compile-time guard; closes \`namespace crown::storage\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
