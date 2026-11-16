# `src/storage/reference.cpp` — block usage map

[Source](../../../../../src/storage/reference.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `3e8143f38ee488a6ffed809d96e86105f8f2784e18fe83677c15032fb901406b`. 470 lines partitioned into 96 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/storage/reference.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../src/storage/reference.cpp#L13) | Callable definition: StorageOwnerId new_owner() | calls detail::new_storage_owner; returns detail::new_storage_owner() · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/storage/reference.cpp#L14) | Explanatory comments or spacing. |  |
| [B0004 · 15–15](../../../../../src/storage/reference.cpp#L15) | Callable definition: void require(bool value,std::string_view message) | calls Error, std::string; guard void require(bool value,std::string_view message) { if (!value) throw Error("storage_contract",std:… · [reviewed contract](#b0004) |
| [B0005 · 16–22](../../../../../src/storage/reference.cpp#L16) | Type/record definition: struct TupleLess | returns left.values()&lt;right.values(); (*this)(*left,*right) · [reviewed contract](#b0005) |
| [B0006 · 23–26](../../../../../src/storage/reference.cpp#L23) | Type/record definition: struct JournalReader |  · [reviewed contract](#b0006) |
| [B0007 · 27–31](../../../../../src/storage/reference.cpp#L27) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../src/storage/reference.cpp#L32) | Type/record definition: struct Record |  · [reviewed contract](#b0008) |
| [B0009 · 33–34](../../../../../src/storage/reference.cpp#L33) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 35–35](../../../../../src/storage/reference.cpp#L35) | Type/record definition: struct Index |  · [reviewed contract](#b0010) |
| [B0011 · 36–45](../../../../../src/storage/reference.cpp#L36) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 46–46](../../../../../src/storage/reference.cpp#L46) | Callable definition: State(RelationId r,TupleLayout l):relation(r),layout(std::move(l)),arena(layout) | calls relation, layout, std::move, arena · [reviewed contract](#b0012) |
| [B0013 · 47–48](../../../../../src/storage/reference.cpp#L47) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 49–49](../../../../../src/storage/reference.cpp#L49) | Callable definition: void mutable_revision() const | calls max, Error · [reviewed contract](#b0014) |
| [B0015 · 50–50](../../../../../src/storage/reference.cpp#L50) | Callable definition: void unlocked() const | calls Error · [reviewed contract](#b0015) |
| [B0016 · 51–51](../../../../../src/storage/reference.cpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0016) |
| [B0017 · 52–52](../../../../../src/storage/reference.cpp#L52) | Callable definition: void input(const Tuple& tuple) const | calls same_token, layout, Error · [reviewed contract](#b0017) |
| [B0018 · 53–53](../../../../../src/storage/reference.cpp#L53) | Callable definition: void owned(TupleHandle handle) const | calls Error · [reviewed contract](#b0018) |
| [B0019 · 54–54](../../../../../src/storage/reference.cpp#L54) | Callable definition: TupleHandle handle(TupleId id) const | calls ; returns {owner,relation,id} · [reviewed contract](#b0019) |
| [B0020 · 55–57](../../../../../src/storage/reference.cpp#L55) | Callable definition: Index& index(IndexId id) | calls find, end, Error; returns found-&gt;second · [reviewed contract](#b0020) |
| [B0021 · 58–58](../../../../../src/storage/reference.cpp#L58) | Callable definition: void key(Index& index,const Tuple& tuple) const | calls target, same_token, layout, Error · [reviewed contract](#b0021) |
| [B0022 · 59–59](../../../../../src/storage/reference.cpp#L59) | Type/record definition: struct EraseMember |  · [reviewed contract](#b0022) |
| [B0023 · 60–60](../../../../../src/storage/reference.cpp#L60) | Type/record definition: struct EraseRecord |  · [reviewed contract](#b0023) |
| [B0024 · 61–77](../../../../../src/storage/reference.cpp#L61) | Callable definition: std::vector&lt;EraseRecord&gt; prepare_erase(const std::vector&lt;TupleId&gt;& ids) | calls reserve, size, find, require; guard const auto found=by_id.find(id); require(found!=by_id.end(),"missing primary handle during deletion…; returns result; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 78–90](../../../../../src/storage/reference.cpp#L78) | Callable definition: void perform_erase(const std::vector&lt;EraseRecord&gt;& records) | calls erase, empty; 2 loop sites; source comment (unverified): // Allocation, projection and ordered-key lookup finish in prepare_erase. · [reviewed contract](#b0025) |
| [B0026 · 91–92](../../../../../src/storage/reference.cpp#L91) | declares types or opens a type body. |  · [reviewed contract](#b0026) |
| [B0027 · 93–98](../../../../../src/storage/reference.cpp#L93) | Type/record definition: struct Key |  · [reviewed contract](#b0027) |
| [B0028 · 99–108](../../../../../src/storage/reference.cpp#L99) | Type/record definition: struct Undo |  · [reviewed contract](#b0028) |
| [B0029 · 109–111](../../../../../src/storage/reference.cpp#L109) | Member/declaration region. |  · [reviewed contract](#b0029) |
| [B0030 · 112–112](../../../../../src/storage/reference.cpp#L112) | Callable definition: explicit Data(std::shared_ptr&lt;State&gt; value):owner(std::move(value)) | calls owner, std::move · [reviewed contract](#b0030) |
| [B0031 · 113–113](../../../../../src/storage/reference.cpp#L113) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0031) |
| [B0032 · 114–117](../../../../../src/storage/reference.cpp#L114) | Callable definition: State& active() const | calls Error; returns *owner · [reviewed contract](#b0032) |
| [B0033 · 118–130](../../../../../src/storage/reference.cpp#L118) | Callable definition: std::unique_ptr&lt;Undo&gt; prepare(bool inserted,const Tuple& tuple) | calls active, reserve, size, push_back; returns undo; growth make_unique, push_back, reserve; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 131–144](../../../../../src/storage/reference.cpp#L131) | Callable definition: void undo_insert(Undo& undo) noexcept | calls find, end, erase, std::terminate; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 145–161](../../../../../src/storage/reference.cpp#L145) | Callable definition: void undo_erase(Undo& undo) noexcept | calls revive, insert, std::move, std::terminate; growth insert; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 162–170](../../../../../src/storage/reference.cpp#L162) | Callable definition: void rollback() noexcept | calls rbegin, rend, undo_insert, undo_erase; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 171–171](../../../../../src/storage/reference.cpp#L171) | Closes surrounding scope/type. |  · [reviewed contract](#b0037) |
| [B0038 · 172–172](../../../../../src/storage/reference.cpp#L172) | Callable definition: ReferenceTable::Journal::Journal(std::unique_ptr&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0038) |
| [B0039 · 173–173](../../../../../src/storage/reference.cpp#L173) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0039) |
| [B0040 · 174–177](../../../../../src/storage/reference.cpp#L174) | Callable definition: ReferenceTable::Journal& ReferenceTable::Journal::operator=(Journal&& other) noexcept | calls ; returns *this · [reviewed contract](#b0040) |
| [B0041 · 178–178](../../../../../src/storage/reference.cpp#L178) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0041) |
| [B0042 · 179–179](../../../../../src/storage/reference.cpp#L179) | Callable definition: bool ReferenceTable::Journal::active() const noexcept | calls ; returns data_ && data_-&gt;owner · [reviewed contract](#b0042) |
| [B0043 · 180–180](../../../../../src/storage/reference.cpp#L180) | Callable definition: std::size_t ReferenceTable::Journal::size() const noexcept | calls size; returns data_ ? data_-&gt;entries.size() : 0 · [reviewed contract](#b0043) |
| [B0044 · 181–184](../../../../../src/storage/reference.cpp#L181) | Callable definition: ReferenceTable::ChangeView ReferenceTable::Journal::change(std::size_t index) const | calls size, Error, get; returns {entry.inserted,entry.handle,entry.pin-&gt;get()} · [reviewed contract](#b0044) |
| [B0045 · 185–185](../../../../../src/storage/reference.cpp#L185) | Callable definition: void ReferenceTable::Journal::rollback() noexcept | calls rollback · [reviewed contract](#b0045) |
| [B0046 · 186–194](../../../../../src/storage/reference.cpp#L186) | Callable definition: void ReferenceTable::Journal::commit() noexcept | calls active, reset; source comment (unverified): // Change pins survive commit; releasing the last table State may still · [reviewed contract](#b0046) |
| [B0047 · 195–206](../../../../../src/storage/reference.cpp#L195) | Callable definition: InsertResult ReferenceTable::Journal::insert(const Tuple& tuple) | calls Error, active, input, find; returns {false,s.handle(found-&gt;second)}; result; growth emplace, insert, push_back; source comment (unverified): // Undo and ordinary insertion each project the registered indexes; this · [reviewed contract](#b0047) |
| [B0048 · 207–227](../../../../../src/storage/reference.cpp#L207) | Callable definition: bool ReferenceTable::Journal::erase(TupleHandle handle) | calls Error, active, owned, find; returns false; true; growth emplace, push_back; 1 loop sites; source comment (unverified): // All allocations and projected keys precede extraction. Later rollback · [reviewed contract](#b0048) |
| [B0049 · 228–231](../../../../../src/storage/reference.cpp#L228) | Callable definition: ReferenceTable::Journal ReferenceTable::journal() | calls state, unlocked, Journal, std::move; returns Journal(std::move(data)); growth make_unique · [reviewed contract](#b0049) |
| [B0050 · 232–232](../../../../../src/storage/reference.cpp#L232) | Explanatory comments or spacing. |  |
| [B0051 · 233–241](../../../../../src/storage/reference.cpp#L233) | Type/record definition: struct ReferenceTable::Cursor::Data |  · [reviewed contract](#b0051) |
| [B0052 · 242–242](../../../../../src/storage/reference.cpp#L242) | Callable definition: ReferenceTable::Cursor::Cursor(std::unique_ptr&lt;Data&gt; data):data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0052) |
| [B0053 · 243–245](../../../../../src/storage/reference.cpp#L243) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0053) |
| [B0054 · 246–261](../../../../../src/storage/reference.cpp#L246) | Callable definition: std::optional&lt;TupleHandle&gt; ReferenceTable::Cursor::next() | calls Error, lock, unlocked, handle; returns {}; {} · [reviewed contract](#b0054) |
| [B0055 · 262–282](../../../../../src/storage/reference.cpp#L262) | Callable definition: std::optional&lt;ReferenceTable::Cursor::Entry&gt; ReferenceTable::Cursor::next_entry() | calls Error, lock, unlocked, find; guard require(found!=owner-&gt;by_id.end(),"missing reference bucket row during borrowed traversal");; returns {}; {} · [reviewed contract](#b0055) |
| [B0056 · 283–290](../../../../../src/storage/reference.cpp#L283) | Callable definition: ReferenceTable::Cursor ReferenceTable::Journal::live() const | calls Error, active, begin, end; returns Cursor(std::move(cursor)); growth make_shared, make_unique · [reviewed contract](#b0056) |
| [B0057 · 291–300](../../../../../src/storage/reference.cpp#L291) | Callable definition: ReferenceTable::Cursor ReferenceTable::Journal::bucket_cursor(IndexId id,const Tuple& key) const | calls Error, active, index, key; returns Cursor(std::move(cursor)); growth make_shared, make_unique · [reviewed contract](#b0057) |
| [B0058 · 301–301](../../../../../src/storage/reference.cpp#L301) | Callable definition: ReferenceTable::ReferenceTable(RelationId relation,TupleLayout layout):state_(std::make_shared&lt;State&gt;(relation,std::move(layout))) | calls state_, std::move; growth make_shared · [reviewed contract](#b0058) |
| [B0059 · 302–302](../../../../../src/storage/reference.cpp#L302) | Callable definition: ReferenceTable::ReferenceTable(std::shared_ptr&lt;State&gt; state):state_(std::move(state)) | calls state_, std::move · [reviewed contract](#b0059) |
| [B0060 · 303–317](../../../../../src/storage/reference.cpp#L303) | Callable definition: ReferenceTable ReferenceTable::snapshot_copy() const | calls state, unlocked, insert, emplace; returns ReferenceTable(std::move(copy)); growth emplace, insert, make_shared; 1 loop sites; source comment (unverified): // Containers and arena identities are new; Tuple copies still follow their · [reviewed contract](#b0060) |
| [B0061 · 318–320](../../../../../src/storage/reference.cpp#L318) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0061) |
| [B0062 · 321–321](../../../../../src/storage/reference.cpp#L321) | Callable definition: ReferenceTable::State& ReferenceTable::state() const | calls Error; returns *state_ · [reviewed contract](#b0062) |
| [B0063 · 322–322](../../../../../src/storage/reference.cpp#L322) | Callable definition: StorageOwnerId ReferenceTable::owner() const | calls state; returns state().owner · [reviewed contract](#b0063) |
| [B0064 · 323–323](../../../../../src/storage/reference.cpp#L323) | Callable definition: RelationId ReferenceTable::relation() const | calls state; returns state().relation · [reviewed contract](#b0064) |
| [B0065 · 324–324](../../../../../src/storage/reference.cpp#L324) | Callable definition: const TupleLayout& ReferenceTable::layout() const | calls state; returns state().layout · [reviewed contract](#b0065) |
| [B0066 · 325–325](../../../../../src/storage/reference.cpp#L325) | Callable definition: std::size_t ReferenceTable::size() const | calls state, size; returns state().primary.size() · [reviewed contract](#b0066) |
| [B0067 · 326–326](../../../../../src/storage/reference.cpp#L326) | Callable definition: std::uint64_t ReferenceTable::revision() const | calls state; returns state().revision · [reviewed contract](#b0067) |
| [B0068 · 327–327](../../../../../src/storage/reference.cpp#L327) | Explanatory comments or spacing. |  |
| [B0069 · 328–330](../../../../../src/storage/reference.cpp#L328) | Callable definition: InsertResult ReferenceTable::insert(const Tuple& tuple) | calls state, unlocked, insert; returns s.insert(tuple); growth insert · [reviewed contract](#b0069) |
| [B0070 · 331–361](../../../../../src/storage/reference.cpp#L331) | Callable definition: InsertResult ReferenceTable::State::insert(const Tuple& tuple) | calls input, find, end, handle; guard const auto \[entry,inserted\]=s.primary.emplace(&s.arena.get(allocated),id); require(inserted,"new tu…; returns {false,s.handle(found-&gt;second)}; {true,s.handle(id)}; growth emplace, insert, push_back, reserve; 3 loop sites · [reviewed contract](#b0070) |
| [B0071 · 362–364](../../../../../src/storage/reference.cpp#L362) | Callable definition: std::optional&lt;TupleHandle&gt; ReferenceTable::find(const Tuple& tuple) const | calls state, input, find, end; returns {}; s.handle(found-&gt;second) · [reviewed contract](#b0071) |
| [B0072 · 365–367](../../../../../src/storage/reference.cpp#L365) | Callable definition: const Tuple* ReferenceTable::get(TupleHandle handle) const | calls state, owned, find, end; returns found==s.by_id.end() ? nullptr : &s.arena.get(found-&gt;second.arena) · [reviewed contract](#b0072) |
| [B0073 · 368–372](../../../../../src/storage/reference.cpp#L368) | Callable definition: TupleArena::Pin ReferenceTable::pin(TupleHandle handle) const | calls state, owned, find, end; returns s.arena.pin(found-&gt;second.arena) · [reviewed contract](#b0073) |
| [B0074 · 373–373](../../../../../src/storage/reference.cpp#L373) | Callable definition: ArenaStatistics ReferenceTable::arena_statistics() const | calls state, statistics; returns state().arena.statistics() · [reviewed contract](#b0074) |
| [B0075 · 374–374](../../../../../src/storage/reference.cpp#L374) | Callable definition: bool ReferenceTable::erase(const Tuple& tuple) | calls state, unlocked, find, erase; returns handle && erase(*handle) · [reviewed contract](#b0075) |
| [B0076 · 375–378](../../../../../src/storage/reference.cpp#L375) | Callable definition: bool ReferenceTable::erase(TupleHandle handle) | calls state, unlocked, owned, contains; returns false; true · [reviewed contract](#b0076) |
| [B0077 · 379–386](../../../../../src/storage/reference.cpp#L379) | Callable definition: IndexId ReferenceTable::add_index(Projection projection) | calls state, unlocked, same_token, source; returns id; id; growth emplace, insert; 2 loop sites · [reviewed contract](#b0077) |
| [B0078 · 387–390](../../../../../src/storage/reference.cpp#L387) | Callable definition: bool ReferenceTable::drop_index(IndexId index) | calls state, unlocked, find, end; returns false; true · [reviewed contract](#b0078) |
| [B0079 · 391–391](../../../../../src/storage/reference.cpp#L391) | Callable definition: std::vector&lt;IndexId&gt; ReferenceTable::indices() const | calls state, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0079) |
| [B0080 · 392–392](../../../../../src/storage/reference.cpp#L392) | Callable definition: Projection ReferenceTable::projection(IndexId index) const | calls state, index; returns state().index(index).projection · [reviewed contract](#b0080) |
| [B0081 · 393–393](../../../../../src/storage/reference.cpp#L393) | Callable definition: std::size_t ReferenceTable::key_count(IndexId index) const | calls state, index, size; returns state().index(index).buckets.size() · [reviewed contract](#b0081) |
| [B0082 · 394–394](../../../../../src/storage/reference.cpp#L394) | Callable definition: std::vector&lt;Tuple&gt; ReferenceTable::keys(IndexId index) const | calls state, index, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0082) |
| [B0083 · 395–400](../../../../../src/storage/reference.cpp#L395) | Callable definition: std::vector&lt;TupleHandle&gt; ReferenceTable::bucket(IndexId index,const Tuple& key) const | calls state, index, key, find; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0083) |
| [B0084 · 401–406](../../../../../src/storage/reference.cpp#L401) | Callable definition: std::size_t ReferenceTable::erase_key(IndexId index,const Tuple& key) | calls state, unlocked, index, key; returns 0; ids.size() · [reviewed contract](#b0084) |
| [B0085 · 407–411](../../../../../src/storage/reference.cpp#L407) | Callable definition: void ReferenceTable::clear() | calls state, unlocked, empty, mutable_revision; 1 loop sites · [reviewed contract](#b0085) |
| [B0086 · 412–415](../../../../../src/storage/reference.cpp#L412) | Callable definition: ReferenceTable::Cursor ReferenceTable::live() const | calls state, unlocked, begin, end; returns Cursor(std::move(data)); growth make_unique · [reviewed contract](#b0086) |
| [B0087 · 416–422](../../../../../src/storage/reference.cpp#L416) | Callable definition: ReferenceTable::Cursor ReferenceTable::bucket_cursor(IndexId index,const Tuple& key) const | calls state, unlocked, index, key; returns Cursor(std::move(data)); growth make_unique · [reviewed contract](#b0087) |
| [B0088 · 423–423](../../../../../src/storage/reference.cpp#L423) | Callable definition: std::vector&lt;Tuple&gt; ReferenceTable::snapshot() const | calls state, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0088) |
| [B0089 · 424–442](../../../../../src/storage/reference.cpp#L424) | Callable definition: void ReferenceTable::check_invariants() const | calls state, check_invariants, require, size; guard require(s.primary.size()==s.by_id.size() && s.primary.size()==s.arena.statistics().live_records,"pr…; growth insert; 4 loop sites; source comment (unverified): // This explicit diagnostic rebuilds every complete secondary index, · [reviewed contract](#b0089) |
| [B0090 · 443–445](../../../../../src/storage/reference.cpp#L443) | declares namespace scope. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0090) |
| [B0091 · 446–450](../../../../../src/storage/reference.cpp#L446) | Type/record definition: struct ReferenceTable::IndexKeyCursor::Data |  · [reviewed contract](#b0091) |
| [B0092 · 451–451](../../../../../src/storage/reference.cpp#L451) | Callable definition: ReferenceTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr&lt;Data&gt; data):data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0092) |
| [B0093 · 452–454](../../../../../src/storage/reference.cpp#L452) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0093) |
| [B0094 · 455–464](../../../../../src/storage/reference.cpp#L455) | Callable definition: std::optional&lt;ReferenceTable::IndexKeyCursor::Entry&gt; ReferenceTable::IndexKeyCursor::next() | calls Error, lock, unlocked, size; returns {}; Entry{item.first,item.second.size()} · [reviewed contract](#b0094) |
| [B0095 · 465–469](../../../../../src/storage/reference.cpp#L465) | Callable definition: ReferenceTable::IndexKeyCursor ReferenceTable::index_keys(IndexId id) const | calls state, unlocked, index, IndexKeyCursor; returns IndexKeyCursor(std::make_unique&lt;IndexKeyCursor::Data&gt;(IndexKeyCursor::Data{; growth make_unique · [reviewed contract](#b0095) |
| [B0096 · 470–470](../../../../../src/storage/reference.cpp#L470) | Closes surrounding scope/type. |  · [reviewed contract](#b0096) |

## B0001

[Lines 1–12](../../../../../src/storage/reference.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/reference.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect the standard-container set backend to owner IDs, diagnostics and ordered containers. |
| inputs / outputs | Imports the public reference/owner interfaces and algorithm/limit/map/set utilities, then opens implementation scope. |
| invariants | No SQL NULL, multiplicity policy or query grant is added by these declarations. |
| ownership | Includes and namespaces allocate no table or payload. |
| failure | Compile-time dependency only. |
| cost | No runtime work; following primitives own their actual allocations. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0002

[Lines 13–13](../../../../../src/storage/reference.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId new_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire the shared storage-owner authority for one fresh table State. |
| inputs / outputs | Delegates to detail::new_storage_owner and returns its nonzero process-wide owner ID. |
| invariants | Successful owner identities do not wrap/reuse; a later construction failure may consume an unpublished ID. |
| ownership | Returns scalar identity, not a table/account/grant. |
| failure | Owner exhaustion propagates storage_overflow. |
| cost | Cold atomic owner allocation; retries under contention belong to the shared helper. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md), [src/storage/owner.cpp](../../../../../src/storage/owner.cpp) |

## B0004

[Lines 15–15](../../../../../src/storage/reference.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a failed private storage consistency check without formatting on success. |
| inputs / outputs | Condition and borrowed message in; false throws storage_contract Error. |
| invariants | Does not repair state or swallow failures; caller cleanup handles its own publication boundary. |
| ownership | Static text is borrowed; rejected diagnostics own their string. |
| failure | Diagnostic allocation may fail as well as the explicit Error. |
| cost | Constant success-path branch; exception/string cost only on failure. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0005

[Lines 16–22](../../../../../src/storage/reference.cpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order admitted tuples lexicographically while supporting borrowed primary pointer keys. |
| inputs / outputs | Tuple/Tuple-pointer overloads compare their read-only value views; transparent lookup accepts an external Tuple probe. |
| invariants | Container callers establish correct layout/type/lifetime before comparison; layout tokens are checked by separate admission, not by this ordering. |
| ownership | Views temporarily share existing payload owners; no row export or persistent key copy. |
| failure | The noexcept value comparator relies on valid immutable scalar payloads; invalid private objects are outside its contract. |
| cost | Actual lexicographic field/byte comparison plus constant view/refcount work; no hash, name lookup or success-path allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0006

[Lines 23–26](../../../../../src/storage/reference.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JournalReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track journal cursor authority independently of the journal Data lifetime. |
| inputs / outputs | A shared scalar phase begins active and later becomes committed or aborted. |
| invariants | Rollback marks aborted before inverse mutations; commit preserves cursor authority subject to owner/revision fences. |
| ownership | Reader token may outlive the journal through cursors but does not own table rows. |
| failure | Declaration performs no admission; token allocation occurs lazily in journal cursor creation. |
| cost | Fixed token state and comparisons, no per-row history. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0007

[Lines 27–31](../../../../../src/storage/reference.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Primary=std::map
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the primary set index over stable arena-owned tuple addresses. |
| inputs / outputs | Maps borrowed const Tuple pointers to logical TupleIds using transparent exact value ordering. |
| invariants | A borrowed primary key exists only while its corresponding arena membership remains live; deletion removes pointer keys before arena reclaim. |
| ownership | Arena owns tuples; this map owns only node metadata and IDs, not tuple payloads. |
| failure | Declaration has no runtime failure; mutations must preserve pointer/lifetime consistency. |
| cost | Ordered O(log N) lookup/insert comparisons with actual tuple field/byte cost; map nodes allocate separately. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0008

[Lines 32–32](../../../../../src/storage/reference.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Record {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair each logical tuple ID with its primary iterator and exact arena allocation. |
| inputs / outputs | Record stores Primary::const_iterator plus owner/slot/generation ArenaHandle. |
| invariants | Both identify the same live tuple; rollback updates the iterator after reinserting an extracted primary node. |
| ownership | Non-owning references/identity; arena payload retention is separate. |
| failure | No executable admission in the record itself. |
| cost | Fixed metadata per live row, no tuple copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0009

[Lines 33–34](../../../../../src/storage/reference.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using ById=std::map
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define logical-ID lookup and owned secondary key membership maps. |
| inputs / outputs | ById maps TupleId to Record; Buckets maps owned projected Tuples to ordered sets of IDs. |
| invariants | Each nonempty secondary bucket corresponds exactly to projected live rows; IDs are not pins. |
| ownership | Containers own standard nodes and key Tuple handles; arena owns original row objects. |
| failure | Declaration does not allocate or validate. |
| cost | ById O(log N), bucket O(log K) typed comparisons and member O(log degree); allocations/output copying remain explicit. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0010

[Lines 35–35](../../../../../src/storage/reference.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Index {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one compiled projection program and its projected-key memberships. |
| inputs / outputs | Projection token and Buckets container form one secondary index. |
| invariants | Equal fields from independently compiled programs may register as separate indexes; same program token is idempotent. |
| ownership | Owns projection handle, bucket nodes, keys and member sets. |
| failure | No runtime admission in this record; builders prepare it before registration. |
| cost | O(keys+memberships) retained container metadata plus key payload ownership; no per-row expression interpretation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0011

[Lines 36–45](../../../../../src/storage/reference.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId owner=new_owner();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one standard reference table State and its exclusive-journal/cursor fences. |
| inputs / outputs | Stores owner/relation/layout/arena, primary/ID/index containers, monotone counters, revision and weak reader authority. |
| invariants | Table is a classical set with non-null core tuples; revision is monotone and journal authority is separate from payload pins. |
| ownership | State owns ordinary metadata and an arena; active journals may extend State lifetime, ordinary cursors remain weak. |
| failure | Owner acquisition can fail at construction; declarations add no independent memory/work account. |
| cost | Memory scales with live rows, projected keys/memberships and retained arena high-water history; statistics are not allocator bytes. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0012

[Lines 46–46](../../../../../src/storage/reference.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(RelationId r,TupleLayout l)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty table State with a fresh arena sharing its required layout token. |
| inputs / outputs | Moves layout, creates arena and validates layout presence. |
| invariants | Relation/table identity differs from arena allocation identity; later rows must use this token exactly. |
| ownership | State retains layout and arena; containers start empty. |
| failure | Owner/arena allocation or invalid layout can fail before a table facade is returned. |
| cost | Cold shared/arena construction and owner IDs; no initial row/index scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0013

[Lines 47–48](../../../../../src/storage/reference.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(const State&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent copying a mutable table authority and its internal borrowed iterators. |
| inputs / outputs | Deleted copy constructor/assignment require explicit snapshot_copy for independent state. |
| invariants | Sharing State for a journal is distinct from cloning row ownership/index maps. |
| ownership | Compile-time owner constraint only. |
| failure | Copy attempts fail compilation. |
| cost | No runtime checks or allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0014

[Lines 49–49](../../../../../src/storage/reference.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mutable_revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a future real mutation before the revision would wrap. |
| inputs / outputs | Checks revision against uint64 maximum. |
| invariants | Caller calls it only after a no-op has been ruled out; it does not increment the revision itself. |
| ownership | Reads scalar state only. |
| failure | Exhaustion throws storage_overflow before publication. |
| cost | Constant branch, no allocation on success. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0015

[Lines 50–50](../../../../../src/storage/reference.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlocked() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce exclusive journal mutation/cursor authority at ordinary operation boundaries. |
| inputs / outputs | Rejects when journal_active is true. |
| invariants | This is a writer/cursor guard, not isolation for ordinary point reads or snapshots of tentative rows. |
| ownership | No owner or reader lease is created. |
| failure | Active journal throws storage_busy. |
| cost | Constant check, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0016

[Lines 51–51](../../../../../src/storage/reference.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult insert(const Tuple& tuple);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the common insertion body shared by ordinary and journal callers. |
| inputs / outputs | Caller-supplied tuple is admitted in the out-of-line definition; ordinary callers separately enforce unlocked state. |
| invariants | The journal deliberately uses the same core mutation while its exclusive flag is active. |
| ownership | Declaration creates no payload/history owner. |
| failure | No executable work here; definition supplies validation/preparation/cleanup. |
| cost | No runtime cost in the declaration, no extra wrapper state. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0017

[Lines 52–52](../../../../../src/storage/reference.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input(const Tuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact layout token identity for external row probes and mutations. |
| inputs / outputs | Checks table layout against tuple.layout. |
| invariants | Descriptor equality alone is insufficient; immutable tuple construction already established scalar/domain facts. |
| ownership | Borrows tuple/layout without copying data. |
| failure | Foreign/moved layout rejects with layout_mismatch before ordered lookup. |
| cost | Constant token check, independent of row width. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0018

[Lines 53–53](../../../../../src/storage/reference.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(TupleHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a logical handle from another table owner or relation. |
| inputs / outputs | Compares owner and relation fields of TupleHandle with this State. |
| invariants | A matching numeric TupleId is meaningful only inside the same authority. |
| ownership | Scalar identity checks only, no payload retention. |
| failure | Mismatch throws foreign_handle before ID lookup. |
| cost | Constant comparisons. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0019

[Lines 54–54](../../../../../src/storage/reference.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleHandle handle(TupleId id) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach this table authority to a known logical tuple ID. |
| inputs / outputs | Returns owner/relation/id by value. |
| invariants | Caller supplies an appropriate live or deliberately tentative ID; this formatter does not look up membership. |
| ownership | Scalar result only, no pin. |
| failure | No local rejection or allocation. |
| cost | Constant handle construction. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0020

[Lines 55–57](../../../../../src/storage/reference.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Index& index(IndexId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a secondary index ID scoped to this table. |
| inputs / outputs | Looks up indices and returns its Index reference. |
| invariants | IndexId carries no owner token; caller must use IDs from this table, and absent/dropped IDs reject. |
| ownership | Borrowed Index lives until drop/table destruction; journals prevent registration mutations while active. |
| failure | Absent index throws unknown_index. |
| cost | O(log I) scalar-ID map lookup, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0021

[Lines 58–58](../../../../../src/storage/reference.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void key(Index& index,const Tuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact key-layout token before a secondary probe. |
| inputs / outputs | Checks supplied key tuple layout against the projection target. |
| invariants | Equal-looking keys from another independent target token are rejected. |
| ownership | Borrows index/key only. |
| failure | Mismatch throws layout_mismatch before bucket comparison. |
| cost | Constant token comparison. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0022

[Lines 59–59](../../../../../src/storage/reference.cpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EraseMember {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remember one already-resolved secondary membership for allocation-free forward erasure. |
| inputs / outputs | Stores Index pointer, bucket iterator and member iterator. |
| invariants | Prepared iterators remain valid until their own members are erased; caller excludes intervening mutations. |
| ownership | Borrows current containers, does not retain extracted nodes or own a key. |
| failure | Record itself does not validate. |
| cost | Fixed metadata per affected index membership. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0023

[Lines 60–60](../../../../../src/storage/reference.cpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EraseRecord {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain all forward-erasure locations for one known row. |
| inputs / outputs | Stores primary/ID iterators, arena handle and vector of EraseMembers. |
| invariants | Caller prepares unique live IDs; original arena/primary objects must still correspond. |
| ownership | Owns only the temporary member-location vector, not row payload. |
| failure | Record preparation may allocate before any deletion. |
| cost | O(I) temporary metadata per affected row. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0024

[Lines 61–77](../../../../../src/storage/reference.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<EraseRecord> prepare_erase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve every affected row/index membership before deleting any row. |
| inputs / outputs | A private duplicate-free vector of live TupleIds in; prepared primary/ID/arena and per-index member locations out. |
| invariants | Checks row/arena address agreement and existence of every projected bucket/member; serial caller prevents iterator invalidation between phases. |
| ownership | Temporary vectors and projected key tuples are standard preparation storage; live containers/payload remain unchanged. |
| failure | Allocation, projection or consistency failures leave all memberships/counters intact. |
| cost | For D rows and I indexes, O(DI) locations plus ID/bucket/member ordered lookups and projected field/byte copies; not constant-time deletion. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0025

[Lines 78–90](../../../../../src/storage/reference.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform_erase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a fully prepared forward deletion without more projections or allocating comparisons. |
| inputs / outputs | Prepared unique-row records in; erases secondary members/empty buckets, ID/primary nodes, then arena memberships. |
| invariants | Pointer keys are removed before payload reclaim; removing one set member preserves other prepared iterators and a bucket disappears only after its last member. |
| ownership | Releases affected container nodes and unpinned payloads; pinned values/arena metadata can survive. |
| failure | Valid private prepared-state/destructor contracts make this nonallocating; prior phase handles fallible work. |
| cost | O(DI) targeted erase bookkeeping plus actual node/payload teardown; no unrelated-row scan or fresh projected-key copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0026

[Lines 91–92](../../../../../src/storage/reference.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L92:sha256:53d9e6bad10e5f161f0b9ca6a4cdd368b4d3a24e4897092113f7234a1ae213b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/reference.cpp: defines/starts \`struct ReferenceTable::Journal::Data\` in this range; closes \`struct ReferenceTable::State\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0027

[Lines 93–98](../../../../../src/storage/reference.cpp#L93); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Key {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a journal key and detached secondary nodes needed for reverse undo. |
| inputs / outputs | Stores raw Index pointer, typed key, set-member node and possibly an empty bucket map node. |
| invariants | Index registrations stay fixed during the exclusive journal; rollback re-finds buckets instead of trusting possibly invalidated iterators. |
| ownership | Owns key Tuple and extracted node handles; after commit destruction needs no dereference of the raw Index pointer. |
| failure | Record construction/key copies may fail only during preparation. |
| cost | One projected key plus retained node ownership per affected index; standard allocation/field-byte costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0028

[Lines 99–108](../../../../../src/storage/reference.cpp#L99); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Undo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one reversible insert or erase without copying unrelated table state. |
| inputs / outputs | Stores direction, handle, prior tuple-ID high-water, optional pin, projected keys and detached primary/ID nodes. |
| invariants | A completed recorded operation owns a pin; inserted rows need prior ID state, erased rows retain exact original nodes/generation. |
| ownership | Journal owns the unique Undo, its pin and key/node storage. |
| failure | Preparation can allocate; inverse execution relies on already complete records. |
| cost | O(I) key/node metadata plus affected payload retention per change, not a full table snapshot. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0029

[Lines 109–111](../../../../../src/storage/reference.cpp#L109); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<State> owner;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep active journal authority and ordered affected-record storage. |
| inputs / outputs | Data retains table State, optional reader token and a vector of unique Undo owners. |
| invariants | owner nonempty means active; committed history may retain entries after owner is released. |
| ownership | Active State is strong, reader token shared, entries exclusive; entries do not own the whole table after commit. |
| failure | Declarations add no admission; lifecycle methods manage rollback/commit. |
| cost | State lifetime retention plus O(changes) entry pointers and per-entry keys/nodes/pins. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0030

[Lines 112–112](../../../../../src/storage/reference.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Data(std::shared_ptr<State> value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt table State for a prepared exclusive journal Data owner. |
| inputs / outputs | Moves a shared State handle into owner. |
| invariants | The table active flag is set only after surrounding Data allocation succeeds. |
| ownership | Retains State without copying rows or containers. |
| failure | Owner move is nonallocating; surrounding unique allocation can fail. |
| cost | Constant shared owner transfer. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0031

[Lines 113–113](../../../../../src/storage/reference.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make destruction of active journal Data perform reverse undo automatically. |
| inputs / outputs | Calls rollback; afterward normal member destruction releases committed or cleared history. |
| invariants | Committed owner is already empty, so its recorded changes are not undone. |
| ownership | Releases pins, keys/node handles and possibly final table State. |
| failure | Noexcept cleanup relies on prepared inverses and private invariants; violations in undo terminate. |
| cost | Affected reverse-undo work when active, history teardown otherwise, with possible whole-State teardown if last owner. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0032

[Lines 114–117](../../../../../src/storage/reference.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State& active() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an active journal State and reject a closed token. |
| inputs / outputs | Returns *owner only when owner is retained. |
| invariants | Committed/rolled-back Data may still exist for diagnostics but cannot mutate/read tentative State through this accessor. |
| ownership | Borrowed State reference; no new retention. |
| failure | Closed owner throws invalid_journal. |
| cost | Constant pointer test/reference return. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0033

[Lines 118–130](../../../../../src/storage/reference.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<Undo> prepare(bool inserted
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare typed inverse keys and geometric entry capacity before a journal mutation. |
| inputs / outputs | Direction and row in; newly owned Undo with one projected key per current index out. |
| invariants | Ensures a subsequent entries.push_back cannot allocate; this stage changes no table membership. |
| ownership | Owns standard Undo/key preparation; reserves the affected-entry pointer vector geometrically. |
| failure | Projection/allocation/entry-capacity failures leave table state unchanged; successful reserved capacity may remain. |
| cost | O(I) projection/copy/lookup setup plus occasional O(changes) pointer-vector reallocation; not a per-step budget refill. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0034

[Lines 131–144](../../../../../src/storage/reference.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_insert(Undo& undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse one tentative insertion using prepared keys and the current exact installed row. |
| inputs / outputs | Finds/removes its secondary members, ID/primary nodes and arena membership, then restores previous_last. |
| invariants | Runs in reverse journal order; current keys/ID must exist. Revision and arena generation/high-water history are deliberately not rewound. |
| ownership | Releases installed nodes; journal pin retains row until history release. |
| failure | Missing expected state terminates; valid undo allocates no replacement nodes or keys. |
| cost | O(I) ordered bucket/member searches and erasures plus ID lookup and teardown; no whole-table copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0035

[Lines 145–161](../../../../../src/storage/reference.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_erase(Undo& undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an erased allocation and its exact detached nodes without replacement allocation. |
| inputs / outputs | Revives the pinned arena generation, reinserts primary/ID nodes, updates stored primary iterator, then restores bucket/member nodes. |
| invariants | Reverse order and prepared ownership guarantee uniqueness; a bucket not retained as a node is located by its typed key. |
| ownership | Moves extracted nodes back to their original standard containers and keeps the revived payload. |
| failure | Private structural mismatches terminate; compatible node allocators/comparators permit allocation-free valid reinsertion. |
| cost | O(I) ordered reinsertion/lookups/comparisons plus fixed arena revival; key-byte comparison and tree balancing remain real work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0036

[Lines 162–170](../../../../../src/storage/reference.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort reader authority before reversing all active journal entries. |
| inputs / outputs | If owner exists, marks reader aborted, walks entries backward, clears active-reader/flag, history and owner. |
| invariants | Idempotent after owner release; logical rows/IDs restore while revision and arena allocation history remain advanced. |
| ownership | Releases inverse records/pins and the active State owner; facade loss can make final release destroy the table. |
| failure | No new allocation/grant; prepared inverse invariant failures terminate rather than attempt another recovery path. |
| cost | Sum of affected reverse operations plus key/node/payload cleanup and possible O(table+arena/index history) final State teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0037

[Lines 171–171](../../../../../src/storage/reference.cpp#L171); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L171:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct ReferenceTable::Journal::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct ReferenceTable::Journal::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct ReferenceTable::Journal::Data\` at its lexical source position in src/storage/reference.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct ReferenceTable::Journal::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0038

[Lines 172–172](../../../../../src/storage/reference.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal::Journal(std::unique_ptr<Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a fully prepared journal facade by moving its unique Data owner. |
| inputs / outputs | Private constructor accepts Data after table journal flag setup. |
| invariants | Data owns the one active scope; moving it does not duplicate a transaction. |
| ownership | Moves unique ownership only. |
| failure | Noexcept, no admission or allocation. |
| cost | Constant pointer move. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0039

[Lines 173–173](../../../../../src/storage/reference.cpp#L173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal::Journal(Journal&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move one journal obligation without copying history or mutating table contents. |
| inputs / outputs | Default move transfers unique Data, leaving source empty. |
| invariants | Only the destination will later commit/rollback/destroy the transferred scope. |
| ownership | Exclusive Data owner transfers. |
| failure | Noexcept; moved-from mutators later reject. |
| cost | Constant pointer transfer. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0040

[Lines 174–177](../../../../../src/storage/reference.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal& ReferenceTable::Journal::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a journal obligation while cleaning up the destination prior scope. |
| inputs / outputs | Non-self assignment moves unique Data; self-assignment is unchanged. |
| invariants | Destroying old active Data rolls it back before the incoming obligation is retained; committed old history only releases. |
| ownership | Transfers new Data and releases old entries/pins/State as appropriate. |
| failure | Noexcept under inverse/destructor contracts. |
| cost | Constant incoming move plus potentially affected-undo or full old-State/history teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0041

[Lines 178–178](../../../../../src/storage/reference.cpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal::~Journal()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a journal and invoke its Data lifecycle automatically. |
| inputs / outputs | Default destruction destroys unique Data when present. |
| invariants | Active scope rolls back; committed rows remain installed while retained change history releases. |
| ownership | Drops keys, extracted nodes, pins and any final State retention. |
| failure | Cleanup does not allocate; invalid private inverse state terminates. |
| cost | History/undo-sensitive destruction, not a universal constant-time destructor. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0042

[Lines 179–179](../../../../../src/storage/reference.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ReferenceTable::Journal::active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this facade still retains an active State. |
| inputs / outputs | True for nonempty Data with owner, false for moved-from/closed history. |
| invariants | History presence alone does not imply activity. |
| ownership | No new owner or mutation. |
| failure | Noexcept, empty is false. |
| cost | Constant pointer checks. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0043

[Lines 180–180](../../../../../src/storage/reference.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReferenceTable::Journal::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the ordered number of retained journal changes. |
| inputs / outputs | Returns entries.size or zero for empty Data. |
| invariants | Committed changes remain countable until journal destruction; rollback clears them. |
| ownership | Scalar read only. |
| failure | Noexcept, empty facade reports zero. |
| cost | Constant vector-size access. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0044

[Lines 181–184](../../../../../src/storage/reference.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::ChangeView ReferenceTable::Journal::change
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one affected tuple and its logical direction/identity from retained history. |
| inputs / outputs | Valid entry index in; ChangeView from its stored pin out. |
| invariants | Available while active or committed; rollback/history destruction ends the borrow. It is not a copied snapshot or membership promise. |
| ownership | Returned tuple reference borrows the journal-owned Pin; no extra pin/copy. |
| failure | Empty/out-of-range history throws invalid_journal; recorded entry pin is a private invariant. |
| cost | Constant vector indexing and retained slot access; no payload copy or allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0045

[Lines 185–185](../../../../../src/storage/reference.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ReferenceTable::Journal::rollback()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward explicit rollback to nonempty Data, harmless for an empty facade. |
| inputs / outputs | Delegates idempotent active reverse undo. |
| invariants | Aborted reader authority precedes iterator-invalidating inverse changes. |
| ownership | Releases active/history ownership through Data. |
| failure | Noexcept; no new allocation. |
| cost | Underlying affected inverse/teardown cost; wrapper only checks one pointer. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0046

[Lines 186–194](../../../../../src/storage/reference.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ReferenceTable::Journal::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep installed rows while closing exclusive authority and preserving change views. |
| inputs / outputs | If active, marks reader committed, clears State reader/flag and releases owner; entries remain. |
| invariants | Commit is idempotent; revision stays advanced and ordinary operations may resume. |
| ownership | Affected pins/nodes/keys remain journal-owned; dropping final table State can clear its live rows while pins preserve changes. |
| failure | Noexcept; no new allocation or grant. |
| cost | Constant fence updates plus possible full last-State teardown; later history destruction has separate affected-storage cost. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0047

[Lines 195–206](../../../../../src/storage/reference.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult ReferenceTable::Journal::insert
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a set insertion and retain its inverse/view before recording success. |
| inputs / outputs | Checks active scope/layout, returns duplicate no-op immediately, otherwise prepares undo keys/capacity, uses common insert and acquires its pin. |
| invariants | The common insertion prepares its own index keys too. A pin-acquisition failure reverses this insertion/ID high-water; revision/arena history may remain advanced. |
| ownership | Owns one Undo and its row pin; prior successful entries stay intact. |
| failure | Preparation/common insert failures preserve appropriate prior state; catch is required to undo a completed insert when its subsequent pin cannot be acquired. |
| cost | Per-index undo projections plus common forward projections/insertion, pin and geometric history append; no whole-state copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0048

[Lines 207–227](../../../../../src/storage/reference.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ReferenceTable::Journal::erase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage deletion by retaining its payload and extracting all necessary nodes. |
| inputs / outputs | Checks owner/live ID, admits revision, prepares projected inverse keys/capacity and pin, then extracts secondary/primary/ID nodes and erases arena membership. |
| invariants | Absent row is a no-op; all fallible preparation precedes extraction. Revision increments once and detached nodes keep exact original identities for rollback. |
| ownership | Undo owns key/node handles and the retained payload pin. |
| failure | Moved/closed/foreign inputs or preparation failures reject before extraction; impossible missing nodes terminate private consistency. |
| cost | O(I) projected key work and ordered find/extract steps plus ID lookup; affected storage is retained rather than copied unrelated rows. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0049

[Lines 228–231](../../../../../src/storage/reference.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal ReferenceTable::journal()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open one exclusive reference-table journal after preparing its Data allocation. |
| inputs / outputs | Checks table presence/unlocked state, allocates Data retaining State, then sets journal_active. |
| invariants | A failed allocation leaves the active flag false; a second active scope is rejected. |
| ownership | Journal owns active State; no row/index snapshot is constructed. |
| failure | Invalid table/storage_busy/allocation can reject before publication. |
| cost | One unique Data allocation and shared handle retention, no table scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0051

[Lines 233–241](../../../../../src/storage/reference.cpp#L233); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReferenceTable::Cursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cache lazy primary or bucket iterator positions with weak owner and revision/reader fences. |
| inputs / outputs | Stores weak State, optional shared journal phase, captured revision, mode/empty flags and ordered iterators. |
| invariants | No payload pin or row history; authority checks must precede using possibly invalidated iterators. |
| ownership | Cursor owns metadata only and may share a reader token, not table State. |
| failure | Cursor metadata allocation happens in factories; construction snapshots revision. |
| cost | Fixed metadata per cursor independent of rows; iteration costs are in next/next_entry. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0052

[Lines 242–242](../../../../../src/storage/reference.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor::Cursor(std::unique_ptr<Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt prepared lazy cursor metadata. |
| inputs / outputs | Moves unique Data from a factory. |
| invariants | Factory has installed correct iterators/fences before exposing this cursor. |
| ownership | Exclusive metadata owner, weak table lifetime. |
| failure | No local admission; pointer move is nonallocating. |
| cost | Constant move. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0053

[Lines 243–245](../../../../../src/storage/reference.cpp#L243); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor::Cursor(Cursor&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer or destroy lazy cursor metadata without retaining table rows. |
| inputs / outputs | Default move constructor/assignment transfer Data; default destructor releases it. |
| invariants | Moved-from traversal rejects; moves do not alter backend revision/membership. |
| ownership | Old Data release drops weak State/shared reader token but no payload pin. |
| failure | Noexcept moves/destruction under owner contracts. |
| cost | Constant metadata transfer/release; no table traversal or tuple copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0054

[Lines 246–261](../../../../../src/storage/reference.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> ReferenceTable::Cursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a lazy live handle stream after owner/reader/revision fences. |
| inputs / outputs | Returns next primary ID or direct set-member ID, or empty at end. |
| invariants | Aborted/foreign active journal/revision changes reject before iterator access. Reference bucket handle advance does not resolve ById. |
| ownership | Returns scalar handle only; local weak lock is temporary and no row pin is created. |
| failure | Moved/expired/aborted/blocked/stale cursor rejects; valid end/advance allocates no output storage. |
| cost | Constant owner/phase checks plus amortized ordered-iterator increment; direct bucket handles avoid O(log N) ID resolution. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0055

[Lines 262–282](../../../../../src/storage/reference.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ReferenceTable::Cursor::Entry> ReferenceTable::Cursor::next_entry()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a borrowed row stream with the same mutation/lifetime fences. |
| inputs / outputs | Primary path returns its borrowed tuple directly; bucket path resolves member ID through ById and arena. |
| invariants | Checks authority/revision before touching iterators; advances position only after bucket row resolution. |
| ownership | Entry borrows table payload and does not copy/pin it; keep owner alive and respect mutation fence. |
| failure | Moved/expired/aborted/blocked/stale cursors reject; impossible missing ById row reports storage_contract. |
| cost | Primary step is direct/amortized iterator work; bucket entry adds O(log N) ID lookup and constant arena resolution, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0056

[Lines 283–290](../../../../../src/storage/reference.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor ReferenceTable::Journal::live()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owner-authorized tentative primary cursor for the current journal revision. |
| inputs / outputs | Active journal in; lazily allocates a shared reader token and unique Cursor Data with current begin/end. |
| invariants | Later real mutation invalidates by revision; commit preserves authority, rollback aborts it. |
| ownership | Cursor weakly references table and shares phase token; active journal supplies State retention. |
| failure | Moved/closed scope or allocation failure rejects before returning a cursor; token/capacity preparation may remain. |
| cost | Fixed reader-token allocation on first read plus cursor allocation/setup, no row scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0057

[Lines 291–300](../../../../../src/storage/reference.cpp#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor ReferenceTable::Journal::bucket_cursor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a tentative bucket cursor using the active journal reader authority. |
| inputs / outputs | Checks active scope/index/key token; prepares reader/cursor and locates bucket or marks empty. |
| invariants | Index registration is fixed during the journal; future real mutation/rollback fences invalidate traversal. |
| ownership | Weak State plus shared phase token; borrowed set iterators do not pin rows. |
| failure | Scope/index/layout/allocation errors reject; lookup does not mutate memberships. |
| cost | O(log I+log K) lookup with actual key comparisons plus fixed metadata allocations. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0058

[Lines 301–301](../../../../../src/storage/reference.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::ReferenceTable(RelationId relation,TupleLayout layout)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fresh standalone standard-container set table owner. |
| inputs / outputs | Relation/layout in; make_shared constructs empty State and its arena. |
| invariants | Layout token establishes classical non-null row shape; new table owner is distinct even with equal descriptors. |
| ownership | Facade strongly owns State; ordinary metadata uses standard allocation, not a query-account cap. |
| failure | Allocation/owner/layout construction failures return no table. |
| cost | Cold State/arena construction, no population or index scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0059

[Lines 302–302](../../../../../src/storage/reference.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::ReferenceTable(std::shared_ptr<State> state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the complete State prepared by private snapshot copying. |
| inputs / outputs | Moves a shared State into a new facade. |
| invariants | Only private callers supply a fully constructed consistent independent State. |
| ownership | Transfers ownership without cloning again. |
| failure | No local rejection or allocation. |
| cost | Constant pointer move. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0060

[Lines 303–317](../../../../../src/storage/reference.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable ReferenceTable::snapshot_copy() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an independent table/arena authority with only current live memberships. |
| inputs / outputs | Requires unlocked source; reconstructs arena/primary/ById using original logical IDs, copies indexes, then high-water counters/revision. |
| invariants | New storage/arena owners make old handles foreign; logical sparse IDs and projection tokens remain. Retired slots/pins are not copied. |
| ownership | Owns new containers and arena Slots; Tuple payload copies follow legacy-deep or native-shared immutable representation. |
| failure | Any construction/copy/allocation failure releases private destination and leaves source unchanged. |
| cost | O(N log N) row reconstruction plus all index/key/member copying and payload-dependent bytes; explicit whole-state copy, not update maintenance. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0061

[Lines 318–320](../../../../../src/storage/reference.cpp#L318); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::~ReferenceTable()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer or release the facade State using default shared ownership. |
| inputs / outputs | Default destruction/move construction/move assignment drop or transfer state_. |
| invariants | An active journal may keep State alive after facade loss; ordinary weak cursors do not. Moved-from ordinary access rejects. |
| ownership | Last State release destroys indexes/maps before arena payloads; pins may retain arena payload/metadata independently. |
| failure | Noexcept default moves/destruction under owner contracts. |
| cost | Constant transfer plus possible O(rows+index memberships+arena history) final old-State destruction on assignment/destruction. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0062

[Lines 321–321](../../../../../src/storage/reference.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::State& ReferenceTable::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve mutable shared State behind an ordinary const facade. |
| inputs / outputs | Returns *state_ or rejects empty moved-from table. |
| invariants | Const access is not a concurrency/read-isolation guarantee; callers serialize access. |
| ownership | Borrowed State, no new retention. |
| failure | Empty facade throws invalid_storage. |
| cost | Constant pointer test/reference return. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0063

[Lines 322–322](../../../../../src/storage/reference.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId ReferenceTable::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the logical storage-owner identity. |
| inputs / outputs | Returns State owner through checked state(). |
| invariants | Distinct from relation, tuple and arena owner IDs. |
| ownership | Scalar copy. |
| failure | Moved-from table rejects. |
| cost | Constant checked read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0064

[Lines 323–323](../../../../../src/storage/reference.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId ReferenceTable::relation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the relation ID attached to this table owner. |
| inputs / outputs | Returns State relation. |
| invariants | Relation ID alone does not authorize a foreign TupleHandle. |
| ownership | Scalar copy. |
| failure | Moved-from table rejects. |
| cost | Constant checked read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0065

[Lines 324–324](../../../../../src/storage/reference.cpp#L324); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& ReferenceTable::layout() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the required exact row-layout token. |
| inputs / outputs | Returns State layout reference. |
| invariants | Keep State alive while using the borrowed handle/reference. |
| ownership | No token copy or field mirror. |
| failure | Moved-from table rejects. |
| cost | Constant checked reference access. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0066

[Lines 325–325](../../../../../src/storage/reference.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReferenceTable::size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current installed set cardinality. |
| inputs / outputs | Returns primary.size(). |
| invariants | Can include internal tentative contents during an active journal; no bag multiplicity sum. |
| ownership | Scalar copy, no snapshot. |
| failure | Moved-from table rejects. |
| cost | Constant container size read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0067

[Lines 326–326](../../../../../src/storage/reference.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ReferenceTable::revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current cursor invalidation revision. |
| inputs / outputs | Returns State revision. |
| invariants | Real tentative mutations advance it; rollback/commit do not rewind it. |
| ownership | Scalar copy. |
| failure | Moved-from table rejects. |
| cost | Constant checked read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0069

[Lines 328–330](../../../../../src/storage/reference.cpp#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult ReferenceTable::insert(const Tuple& tuple)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the ordinary unlocked set insertion boundary. |
| inputs / outputs | Checks facade and exclusive journal guard, then common State insertion. |
| invariants | Duplicates preserve existing handle/revision; there is no multiplicity increment. |
| ownership | Successful new row obtains arena/container ownership in the underlying implementation. |
| failure | Moved/busy/input/preparation failures propagate, preserving the core insertion guarantees. |
| cost | Constant wrapper plus full common insertion work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0070

[Lines 331–361](../../../../../src/storage/reference.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult ReferenceTable::State::insert
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert a distinct admitted tuple with staged partial-container cleanup. |
| inputs / outputs | Checks layout/duplicate, admits ID/revision, projects every index, allocates arena row, then installs primary/ById/bucket/member nodes. |
| invariants | Publishes last_tuple/revision only after all memberships succeed; failed insertion removes any partial nodes and arena membership, though arena high-water/generation history can grow. |
| ownership | Arena owns row; primary borrows it; ID/secondary nodes and prepared keys own their standard metadata. |
| failure | The catch is required to reverse allocations/container mutations already installed. It erases map pointer keys before arena reclaim and rethrows the original failure. |
| cost | O(log N) duplicate probe, per-index projection/ordered insertion and payload allocations; cleanup scales with attempted indexes, not full table size. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0071

[Lines 362–364](../../../../../src/storage/reference.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> ReferenceTable::find
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe current installed row membership by exact tuple values. |
| inputs / outputs | Admits layout token and performs transparent primary lookup; returns handle or absence. |
| invariants | Allowed to observe tentative rows; result does not make them publishable before commit. |
| ownership | Borrowed input, scalar optional handle output; no payload copy. |
| failure | Invalid table/layout rejects. |
| cost | O(log N) typed tuple comparisons with actual field/byte cost, no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0072

[Lines 365–367](../../../../../src/storage/reference.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple* ReferenceTable::get
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a current installed row by logical owner/relation/ID. |
| inputs / outputs | Checks owner, looks up ById and resolves exact arena allocation, or returns nullptr if absent. |
| invariants | Same-owner absent ID differs from a foreign handle; tentative reads stay internal. |
| ownership | Pointer borrows stable arena Tuple until erase/clear/State loss; no pin. |
| failure | Foreign/moved owner rejects; private arena mismatch propagates. |
| cost | O(log N) scalar-ID lookup plus constant arena check, no payload copy/allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0073

[Lines 368–372](../../../../../src/storage/reference.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin ReferenceTable::pin
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a currently live row payload independently of membership. |
| inputs / outputs | Checks handle ownership/ID then pins its exact arena allocation. |
| invariants | Absent same-owner ID is stale; pin keeps payload, not primary/index membership or cursor authority. |
| ownership | Returns arena State/payload retention without copying row bytes. |
| failure | Moved/foreign/stale/pin-count exhaustion can reject before acquisition. |
| cost | O(log N) ID lookup plus constant arena pin bookkeeping; last-pin release has separate teardown cost. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0074

[Lines 373–373](../../../../../src/storage/reference.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics ReferenceTable::arena_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current logical arena slot/pin classifications. |
| inputs / outputs | Returns arena statistics through checked State. |
| invariants | Counts are not byte/allocator/capacity measurements and may retain tentative allocation history after rollback. |
| ownership | Fixed counter copy. |
| failure | Moved-from table rejects. |
| cost | Constant checked read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0075

[Lines 374–374](../../../../../src/storage/reference.cpp#L374); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ReferenceTable::erase(const Tuple& tuple)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase ordinary set membership by row value. |
| inputs / outputs | Checks unlocked, finds an exact-layout row and, if present, forwards its handle to erase. |
| invariants | Absent is a no-op; does not convert duplicate bag counts or SQL NULL semantics. |
| ownership | Borrowed row; underlying handle erase manages prepared deletion ownership. |
| failure | Busy/layout/validation/preparation failures propagate. |
| cost | Primary O(log N) probe plus handle-deletion preparation/commit cost. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0076

[Lines 375–378](../../../../../src/storage/reference.cpp#L375); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ReferenceTable::erase(TupleHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delete one ordinary live row after complete per-index preparation. |
| inputs / outputs | Checks unlocked/owner/ID, admits revision, prepares one unique live row and erases it, then increments revision. |
| invariants | Absent same-owner ID returns false; fallible work precedes removal and pointer keys disappear before payload reclaim. |
| ownership | Temporary prepared-location vectors release after mutation; pinned payloads may survive. |
| failure | Foreign/busy/revision/preparation errors leave logical state unchanged. |
| cost | O(log N) ID probes plus per-index projections/lookups and targeted node/payload teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0077

[Lines 379–386](../../../../../src/storage/reference.cpp#L379); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId ReferenceTable::add_index
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and publish a secondary projection index over every current live row. |
| inputs / outputs | Checks source token, returns existing same-program token ID, otherwise admits ID/revision and builds a private index before registration. |
| invariants | No descriptor-equivalence deduplication; an independently compiled identical mapping may coexist. |
| ownership | State owns registered projection, key Tuples, member sets and map node. |
| failure | Busy/layout/counter/allocation/projection failures before publication leave existing indexes/counters unchanged. |
| cost | O(I) token scan plus N projections and ordered bucket/member insertions; complete index construction is population-sensitive. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0078

[Lines 387–390](../../../../../src/storage/reference.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ReferenceTable::drop_index
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a registered secondary program and its memberships. |
| inputs / outputs | Returns false if absent; otherwise admits revision, erases index node and increments revision. |
| invariants | Real drop invalidates cursors; no-op drop leaves revision unchanged. |
| ownership | Destroys all affected buckets, keys, members and projection ownership. |
| failure | Busy/moved/revision errors reject before erase. |
| cost | O(log I) lookup plus O(keys+memberships) destruction and possible last-key/projection teardown. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0079

[Lines 391–391](../../../../../src/storage/reference.cpp#L391); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<IndexId> ReferenceTable::indices() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export current index IDs in ordered map traversal. |
| inputs / outputs | Builds a standard vector of registered IDs. |
| invariants | Reads installed metadata without a journal isolation promise; IDs remain scoped to this table. |
| ownership | Caller owns output vector; no payload pins. |
| failure | Invalid table or allocation failure propagates without mutation. |
| cost | O(I) traversal/output and vector growth; not an allocation-free getter. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0080

[Lines 392–392](../../../../../src/storage/reference.cpp#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection ReferenceTable::projection
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the compiled program for one existing index. |
| inputs / outputs | Resolves scoped IndexId and returns its Projection handle copy. |
| invariants | Keeps exact program/source/target tokens, not a deep field-vector recompile. |
| ownership | Output retains shared projection Data after table drop. |
| failure | Unknown index/moved table rejects. |
| cost | O(log I) lookup plus constant handle/refcount copy. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0081

[Lines 393–393](../../../../../src/storage/reference.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReferenceTable::key_count
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read number of currently nonempty keys for an index. |
| inputs / outputs | Resolves index and returns buckets.size(). |
| invariants | Not row count or expanded bag cardinality; bucket empties are removed by mutation. |
| ownership | Scalar output, no copied keys. |
| failure | Unknown/moved table rejects. |
| cost | O(log I) index lookup and constant size read. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0082

[Lines 394–394](../../../../../src/storage/reference.cpp#L394); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> ReferenceTable::keys
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export owning copies/handles of current projected keys. |
| inputs / outputs | Traverses one index Buckets map into a standard vector. |
| invariants | Ordering is typed lexical key order; equal-looking target layouts still require correct token admission for probes. |
| ownership | Caller owns Tuple copies: legacy key bytes deep-copy, native immutable payloads share ownership. |
| failure | Unknown index or copy/allocation failure returns no partial vector and leaves index unchanged. |
| cost | O(log I+K) traversal plus payload-dependent copy/byte/allocation and vector growth. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0083

[Lines 395–400](../../../../../src/storage/reference.cpp#L395); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<TupleHandle> ReferenceTable::bucket
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect logical handles matching an admitted projected key. |
| inputs / outputs | Checks index/key token, finds a bucket and builds a vector of IDs decorated with table authority. |
| invariants | Handles do not pin payload or imply committed visibility during a journal. |
| ownership | Caller owns ordinary handle vector; input key is borrowed. |
| failure | Unknown index/layout/allocation errors leave table unchanged. |
| cost | O(log I+log K) typed probe plus O(degree) output/allocation; member iteration is ordered. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0084

[Lines 401–406](../../../../../src/storage/reference.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReferenceTable::erase_key
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delete all rows in one admitted secondary bucket atomically at the ordinary table level. |
| inputs / outputs | Checks unlocked/index/key; absent returns zero, otherwise copies unique member IDs, prepares all erasures, applies them, increments revision once. |
| invariants | All affected rows and every other index membership are prepared before first deletion; registration remains. |
| ownership | Owns temporary ID/location arrays; pins retain erased payloads where needed. |
| failure | Preparation/projection/allocation/revision failures leave logical rows/indexes unchanged. |
| cost | O(degree*I) preparation plus ordered lookups/projections and targeted erasures; output-sensitive scratch, not constant bulk erase. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0085

[Lines 407–411](../../../../../src/storage/reference.cpp#L407); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ReferenceTable::clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove all ordinary live rows and bucket contents while preserving index registrations and ID history. |
| inputs / outputs | After unlocked/nonempty/revision checks, clears secondary buckets, ById/primary, then arena and increments revision. |
| invariants | Empty clear is a no-op; pointer keys disappear before arena reclaim; last_tuple/last_index do not reset. |
| ownership | Releases live container nodes/keys/payloads; pins and arena metadata can survive. |
| failure | Busy/revision rejection precedes mutation; valid destruction allocates nothing. |
| cost | O(rows+all key/member nodes) teardown plus arena live traversal; not O(1). |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0086

[Lines 412–415](../../../../../src/storage/reference.cpp#L412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor ReferenceTable::live()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordinary weak-owner primary cursor at current revision. |
| inputs / outputs | Checks unlocked and allocates Cursor Data with primary begin/end. |
| invariants | Active journal blocks factory creation; cursor does not retain table or records. |
| ownership | Owns metadata only, weak State. |
| failure | Moved/busy/allocation can reject before a cursor is returned. |
| cost | Fixed metadata allocation/setup; no row scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0087

[Lines 416–422](../../../../../src/storage/reference.cpp#L416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Cursor ReferenceTable::bucket_cursor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordinary lazy bucket iterator for an admitted key. |
| inputs / outputs | Checks unlocked/index/key token, allocates metadata and stores member iterators or empty state. |
| invariants | Later real mutations/index drops invalidate by revision before use; an absent bucket is a valid empty cursor. |
| ownership | Weak State and borrowed iterators, no row/key pin. |
| failure | Busy/moved/unknown/layout/allocation rejection propagates. |
| cost | O(log I+log K) probe plus fixed metadata allocation, no member collection. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0088

[Lines 423–423](../../../../../src/storage/reference.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Tuple> ReferenceTable::snapshot() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export owning current row values independently of later membership changes. |
| inputs / outputs | Copies each primary Tuple into a standard vector. |
| invariants | May observe tentative installed contents; caller must not publish before commit. This is not a cursor or independent table owner. |
| ownership | Output Tuple copies deep-copy legacy payloads or share native immutable owners; no arena membership retention. |
| failure | Copy/vector allocation failure leaves table unchanged. |
| cost | O(N) traversal plus representation-dependent field/byte copies and allocation; no indexed-work grant applies to this reference utility. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0089

[Lines 424–442](../../../../../src/storage/reference.cpp#L424); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ReferenceTable::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute arena/primary/ID consistency and every complete secondary projection index. |
| inputs / outputs | Calls arena diagnostic, verifies tokens/IDs/addresses, rebuilds expected Buckets per index and compares exact maps/sets. |
| invariants | Explicit diagnostic of current installed state, including tentative rows; not automatic mutation work or arbitrary memory-corruption safety. |
| ownership | Temporary standard maps/sets/projected Tuples and arena visited arrays are released afterward. |
| failure | Invalid ownership/membership/value facts or diagnostic allocations throw without changing table state. |
| cost | Full arena-history scan plus N row validations and I complete ordered projection rebuilds; output/string/node allocation costs are real. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0090

[Lines 443–445](../../../../../src/storage/reference.cpp#L443); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L443-L445:sha256:1e515d6bde13b41857a7d2bff7b508f639a80c1288c22bd1e9531ed5f31ed648
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/reference.cpp: opens namespace \`crown::storage\`; closes \`namespace crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0091

[Lines 446–450](../../../../../src/storage/reference.cpp#L446); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReferenceTable::IndexKeyCursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cache one secondary-key traversal with weak owner and revision fencing. |
| inputs / outputs | Stores weak State, captured revision and Buckets begin/end. |
| invariants | Does not retain keys/members or journal authority; ordinary unlocked cursor only. |
| ownership | Unique cursor metadata with borrowed map iterators. |
| failure | Factory allocation separate; later advance validates fences. |
| cost | Fixed metadata independent of key count. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0092

[Lines 451–451](../../../../../src/storage/reference.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr<Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared key cursor without collecting keys. |
| inputs / outputs | Moves unique Data into facade. |
| invariants | Factory installed valid owner/revision/iterators. |
| ownership | Metadata ownership only. |
| failure | No local validation/allocation. |
| cost | Constant move. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0093

[Lines 452–454](../../../../../src/storage/reference.cpp#L452); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move or release key-cursor metadata without copying backend keys. |
| inputs / outputs | Default moves transfer unique Data; destructor releases it. |
| invariants | Moved-from traversal rejects; ownership remains weak. |
| ownership | Drops only weak/iterator metadata, not payload pins. |
| failure | Noexcept default lifecycle. |
| cost | Constant transfer/release with no table traversal. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0094

[Lines 455–464](../../../../../src/storage/reference.cpp#L455); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ReferenceTable::IndexKeyCursor::Entry> ReferenceTable::IndexKeyCursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the next live projected key and its exact member degree. |
| inputs / outputs | Locks weak owner, checks unlocked/revision, then returns key reference/set size or end. |
| invariants | Fences precede iterator dereference; key borrow expires on mutation/drop/owner loss or next traversal per API. |
| ownership | Returns no copied Tuple or pin; temporary strong lock lasts only through call. |
| failure | Moved/expired/busy/stale cursor rejects. |
| cost | Constant checks, amortized map iterator step and set-size read; no success allocation. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0095

[Lines 465–469](../../../../../src/storage/reference.cpp#L465); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::IndexKeyCursor ReferenceTable::index_keys
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ordinary live-key traversal without materializing a vector. |
| inputs / outputs | Checks unlocked/index and allocates Data with current bucket iterators/revision. |
| invariants | Cannot create during an exclusive journal; future real mutation invalidates. |
| ownership | Weak State, unique fixed metadata, borrowed keys. |
| failure | Invalid table/busy/unknown index/allocation rejection propagates. |
| cost | O(log I) lookup plus one metadata allocation/setup, no key scan. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [Refactor.md §11.4 S02–S03](../../../../../Refactor.md) |

## B0096

[Lines 470–470](../../../../../src/storage/reference.cpp#L470); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L470-L470:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/reference.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
