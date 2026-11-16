# `src/storage/accounted_reference.cpp` — block usage map

[Source](../../../../../src/storage/accounted_reference.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `59710456fd3f58790c1b54bcf5fcc35e38f832d7ffc23ef060465f48c61c91b4`. 542 lines partitioned into 104 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../src/storage/accounted_reference.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../src/storage/accounted_reference.cpp#L21) | Callable definition: void require(bool value, TableProblem issue = TableProblem::invariant) | calls TableValidationFailure; guard void require(bool value, TableProblem issue = TableProblem::invariant) { · [reviewed contract](#b0002) |
| [B0003 · 24–28](../../../../../src/storage/accounted_reference.cpp#L24) | Callable definition: StorageOwnerId new_owner() | calls detail::try_new_storage_owner, MemoryFailure; returns *id · [reviewed contract](#b0003) |
| [B0004 · 29–35](../../../../../src/storage/accounted_reference.cpp#L29) | Type/record definition: struct TupleLess | returns a.values() &lt; b.values(); (*this)(*a, *b) · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../src/storage/accounted_reference.cpp#L36) | Type/record definition: struct Reader |  · [reviewed contract](#b0005) |
| [B0006 · 37–42](../../../../../src/storage/accounted_reference.cpp#L37) | Callable definition: template&lt;class Map, class... Args&gt; typename Map::node_type prepare_node(const Map& owner, Args&&... args) | calls temporary, key_comp, get_allocator, emplace; guard require(inserted);return temporary.extract(position);; returns temporary.extract(position); growth emplace · [reviewed contract](#b0006) |
| [B0007 · 43–47](../../../../../src/storage/accounted_reference.cpp#L43) | Callable definition: template&lt;class Map&gt; auto publish_node(Map& owner, typename Map::node_type node) noexcept | calls insert, std::move, std::terminate; returns result.position; growth insert · [reviewed contract](#b0007) |
| [B0008 · 48–51](../../../../../src/storage/accounted_reference.cpp#L48) | Callable definition: template&lt;class Vector&gt; void reserve(Vector& values, std::size_t size) | calls max_size, MemoryFailure; growth reserve · [reviewed contract](#b0008) |
| [B0009 · 52–57](../../../../../src/storage/accounted_reference.cpp#L52) | Callable definition: bool matches(const AccountedProjection& projection, const AccountedTuple& source, const AccountedTuple& key) | calls source, same_token, layout, target; returns false; false; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 58–58](../../../../../src/storage/accounted_reference.cpp#L58) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 59–72](../../../../../src/storage/accounted_reference.cpp#L59) | Callable definition: std::string_view TableValidationFailure::code() const noexcept | calls ; returns @; @ · [reviewed contract](#b0011) |
| [B0012 · 73–73](../../../../../src/storage/accounted_reference.cpp#L73) | Callable definition: const char* TableValidationFailure::what() const noexcept | calls code, data; returns code().data() · [reviewed contract](#b0012) |
| [B0013 · 74–77](../../../../../src/storage/accounted_reference.cpp#L74) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 78–78](../../../../../src/storage/accounted_reference.cpp#L78) | Type/record definition: struct Record |  · [reviewed contract](#b0014) |
| [B0015 · 79–81](../../../../../src/storage/accounted_reference.cpp#L79) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 82–87](../../../../../src/storage/accounted_reference.cpp#L82) | Type/record definition: struct Index |  · [reviewed contract](#b0016) |
| [B0017 · 88–101](../../../../../src/storage/accounted_reference.cpp#L88) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 102–106](../../../../../src/storage/accounted_reference.cpp#L102) | Callable definition: State(MemoryAccount value, RelationId id, AccountedLayout descriptor, StorageOwnerId identity) : account(std::move(value)), layou… | calls account, std::move, layout, owner · [reviewed contract](#b0018) |
| [B0019 · 107–107](../../../../../src/storage/accounted_reference.cpp#L107) | Callable definition: void unlocked() const | calls require; guard void unlocked() const { require(!journal_active, TableProblem::busy); } · [reviewed contract](#b0019) |
| [B0020 · 108–108](../../../../../src/storage/accounted_reference.cpp#L108) | Callable definition: void mutable_revision() const | calls MemoryFailure · [reviewed contract](#b0020) |
| [B0021 · 109–109](../../../../../src/storage/accounted_reference.cpp#L109) | Callable definition: void input(const AccountedTuple& tuple) const | calls require, same_token, layout; guard void input(const AccountedTuple& tuple) const { require(layout.same_token(tuple.layout()), TablePro… · [reviewed contract](#b0021) |
| [B0022 · 110–110](../../../../../src/storage/accounted_reference.cpp#L110) | Callable definition: void owned(TupleHandle handle) const | calls require; guard void owned(TupleHandle handle) const { require(handle.owner == owner && handle.relation == relation… · [reviewed contract](#b0022) |
| [B0023 · 111–111](../../../../../src/storage/accounted_reference.cpp#L111) | Callable definition: TupleHandle handle(TupleId id) const noexcept | calls ; returns {owner, relation, id} · [reviewed contract](#b0023) |
| [B0024 · 112–114](../../../../../src/storage/accounted_reference.cpp#L112) | Callable definition: Index& index(IndexId id) | calls find, require, end; guard const auto found = indices.find(id);require(found != indices.end(), TableProblem::unknown_index);re…; returns found-&gt;second · [reviewed contract](#b0024) |
| [B0025 · 115–117](../../../../../src/storage/accounted_reference.cpp#L115) | Callable definition: void key(const Index& index, const AccountedTuple& tuple) const | calls require, target, same_token, layout; guard require(index.projection.target().same_token(tuple.layout()), TableProblem::layout_mismatch); · [reviewed contract](#b0025) |
| [B0026 · 118–120](../../../../../src/storage/accounted_reference.cpp#L118) | Callable definition: template&lt;class T&gt; AccountedVector&lt;T&gt; vector(MemoryPurpose purpose = MemoryPurpose::scratch) const | calls ; returns AccountedVector&lt;T&gt;(MemoryAllocator&lt;T&gt;(account, purpose, tag)) · [reviewed contract](#b0026) |
| [B0027 · 121–123](../../../../../src/storage/accounted_reference.cpp#L121) | Callable definition: template&lt;class T&gt; AccountedVector&lt;T&gt; output() const | calls output_tag; returns AccountedVector&lt;T&gt;(MemoryAllocator&lt;T&gt;(account, MemoryPurpose::output_buffer, output_tag())) · [reviewed contract](#b0027) |
| [B0028 · 124–124](../../../../../src/storage/accounted_reference.cpp#L124) | Callable definition: MemoryAttribution output_tag() const noexcept | calls ; returns {MemoryOwnerKind::output, owner.value} · [reviewed contract](#b0028) |
| [B0029 · 125–127](../../../../../src/storage/accounted_reference.cpp#L125) | Callable definition: template&lt;class T&gt; void lifetime(const T& value, MemoryPurpose purpose, AllocationLifetime life) const noexcept | calls set_lifetime_containing, std::addressof · [reviewed contract](#b0029) |
| [B0030 · 128–161](../../../../../src/storage/accounted_reference.cpp#L128) | Callable definition: InsertResult insert(const AccountedTuple& tuple) | calls input, find, end, handle; returns {false, handle(found-&gt;second)}; {true, handle(id)}; growth insert, push_back, reserve; 2 loop sites; source comment (unverified): // Preparation borrows this synchronous input; publication below rebinds · [reviewed contract](#b0030) |
| [B0031 · 162–164](../../../../../src/storage/accounted_reference.cpp#L162) | declares types or opens a type body. |  · [reviewed contract](#b0031) |
| [B0032 · 165–170](../../../../../src/storage/accounted_reference.cpp#L165) | Type/record definition: struct Key |  · [reviewed contract](#b0032) |
| [B0033 · 171–181](../../../../../src/storage/accounted_reference.cpp#L171) | Type/record definition: struct Undo |  · [reviewed contract](#b0033) |
| [B0034 · 182–187](../../../../../src/storage/accounted_reference.cpp#L182) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0034) |
| [B0035 · 188–190](../../../../../src/storage/accounted_reference.cpp#L188) | Callable definition: Data(std::shared_ptr&lt;State&gt; state, std::shared_ptr&lt;Reader&gt; authority) : owner(std::move(state)), report_owner(owner), reader(std:… | calls owner, std::move, report_owner, reader · [reviewed contract](#b0035) |
| [B0036 · 191–197](../../../../../src/storage/accounted_reference.cpp#L191) | Callable definition: ~Data() | calls rollback, lock, size, std::terminate · [reviewed contract](#b0036) |
| [B0037 · 198–198](../../../../../src/storage/accounted_reference.cpp#L198) | Callable definition: State& active() const | calls require, bool; guard State& active() const { require(bool(owner) && owner-&gt;journal_active, TableProblem::invalid_journal…; returns *owner · [reviewed contract](#b0037) |
| [B0038 · 199–211](../../../../../src/storage/accounted_reference.cpp#L199) | Callable definition: Entries prepare(bool inserted, const AccountedTuple& tuple) | calls active, max, size, max_size; returns staged; growth emplace_back, push_back, reserve; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 212–212](../../../../../src/storage/accounted_reference.cpp#L212) | Callable definition: void publish(Entries& staged) noexcept | calls splice, end · [reviewed contract](#b0039) |
| [B0040 · 213–225](../../../../../src/storage/accounted_reference.cpp#L213) | Callable definition: void undo_insert(Undo& undo) noexcept | calls find, end, erase, std::terminate; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 226–243](../../../../../src/storage/accounted_reference.cpp#L226) | Callable definition: void undo_erase(Undo& undo) noexcept | calls AccountedReferenceTable::revive, lifetime, key, publish_node; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 244–252](../../../../../src/storage/accounted_reference.cpp#L244) | Callable definition: void rollback() noexcept | calls rbegin, rend, undo_insert, undo_erase; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 253–254](../../../../../src/storage/accounted_reference.cpp#L253) | Closes surrounding scope/type. |  · [reviewed contract](#b0043) |
| [B0044 · 255–255](../../../../../src/storage/accounted_reference.cpp#L255) | Callable definition: MemoryAccount AccountedReferenceTable::account_for(const AccountedLayout& layout) | calls query_account; returns layout.query_account() · [reviewed contract](#b0044) |
| [B0045 · 256–256](../../../../../src/storage/accounted_reference.cpp#L256) | Callable definition: void AccountedReferenceTable::classify(AccountedTuple& tuple, AllocationLifetime lifetime) noexcept | calls set_lifetime · [reviewed contract](#b0045) |
| [B0046 · 257–257](../../../../../src/storage/accounted_reference.cpp#L257) | Callable definition: void AccountedReferenceTable::revive(AccountedTupleArena& arena, const AccountedTupleArena::Pin& pin) noexcept | calls revive · [reviewed contract](#b0046) |
| [B0047 · 258–262](../../../../../src/storage/accounted_reference.cpp#L258) | Callable definition: AccountedReferenceTable::AccountedReferenceTable(RelationId relation, AccountedLayout layout) | calls require, bool, account_for, new_owner; guard require(bool(layout), TableProblem::layout_mismatch);auto account = account_for(layout);const auto …; growth make_accounted_shared · [reviewed contract](#b0047) |
| [B0048 · 263–263](../../../../../src/storage/accounted_reference.cpp#L263) | Callable definition: AccountedReferenceTable::AccountedReferenceTable(std::shared_ptr&lt;State&gt; state) noexcept : state_(std::move(state)) | calls state_, std::move · [reviewed contract](#b0048) |
| [B0049 · 264–264](../../../../../src/storage/accounted_reference.cpp#L264) | Callable definition: AccountedReferenceTable::~AccountedReferenceTable() | calls  · [reviewed contract](#b0049) |
| [B0050 · 265–265](../../../../../src/storage/accounted_reference.cpp#L265) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0050) |
| [B0051 · 266–268](../../../../../src/storage/accounted_reference.cpp#L266) | Callable definition: AccountedReferenceTable& AccountedReferenceTable::operator=(AccountedReferenceTable&& other) noexcept | calls ; returns *this · [reviewed contract](#b0051) |
| [B0052 · 269–271](../../../../../src/storage/accounted_reference.cpp#L269) | Callable definition: AccountedReferenceTable::State& AccountedReferenceTable::state() const | calls require, bool; guard require(bool(state_), TableProblem::invalid_table);return *state_;; returns *state_ · [reviewed contract](#b0052) |
| [B0053 · 272–272](../../../../../src/storage/accounted_reference.cpp#L272) | Callable definition: StorageOwnerId AccountedReferenceTable::owner() const | calls state; returns state().owner · [reviewed contract](#b0053) |
| [B0054 · 273–273](../../../../../src/storage/accounted_reference.cpp#L273) | Callable definition: RelationId AccountedReferenceTable::relation() const | calls state; returns state().relation · [reviewed contract](#b0054) |
| [B0055 · 274–274](../../../../../src/storage/accounted_reference.cpp#L274) | Callable definition: const AccountedLayout& AccountedReferenceTable::layout() const & | calls state; returns state().layout · [reviewed contract](#b0055) |
| [B0056 · 275–275](../../../../../src/storage/accounted_reference.cpp#L275) | Callable definition: std::size_t AccountedReferenceTable::size() const | calls state, size; returns state().primary.size() · [reviewed contract](#b0056) |
| [B0057 · 276–276](../../../../../src/storage/accounted_reference.cpp#L276) | Callable definition: std::uint64_t AccountedReferenceTable::revision() const | calls state; returns state().revision · [reviewed contract](#b0057) |
| [B0058 · 277–277](../../../../../src/storage/accounted_reference.cpp#L277) | Callable definition: MemoryAttribution AccountedReferenceTable::attribution() const | calls state; returns state().tag · [reviewed contract](#b0058) |
| [B0059 · 278–278](../../../../../src/storage/accounted_reference.cpp#L278) | Callable definition: ArenaStatistics AccountedReferenceTable::arena_statistics() const | calls state, statistics; returns state().arena.statistics() · [reviewed contract](#b0059) |
| [B0060 · 279–292](../../../../../src/storage/accounted_reference.cpp#L279) | Callable definition: TableMemoryStatistics AccountedReferenceTable::memory_statistics() const | calls state, size, statistics_for, memory_statistics; returns result; 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 293–293](../../../../../src/storage/accounted_reference.cpp#L293) | Callable definition: InsertResult AccountedReferenceTable::insert(const AccountedTuple& tuple) | calls state, unlocked, insert; returns s.insert(tuple); growth insert · [reviewed contract](#b0061) |
| [B0062 · 294–298](../../../../../src/storage/accounted_reference.cpp#L294) | Callable definition: std::optional&lt;TupleHandle&gt; AccountedReferenceTable::find(const AccountedTuple& tuple) const | calls state, input, find, end; returns {}; s.handle(found-&gt;second) · [reviewed contract](#b0062) |
| [B0063 · 299–302](../../../../../src/storage/accounted_reference.cpp#L299) | Callable definition: const AccountedTuple* AccountedReferenceTable::get(TupleHandle handle) const & | calls state, owned, find, end; returns found == s.by_id.end() ? nullptr : &s.arena.get(found-&gt;second.arena) · [reviewed contract](#b0063) |
| [B0064 · 303–306](../../../../../src/storage/accounted_reference.cpp#L303) | Callable definition: AccountedTupleArena::Pin AccountedReferenceTable::pin(TupleHandle handle) const | calls state, owned, find, require; guard require(found != s.by_id.end(), TableProblem::stale_handle);return s.arena.pin(found-&gt;second.arena);; returns s.arena.pin(found-&gt;second.arena) · [reviewed contract](#b0064) |
| [B0065 · 307–307](../../../../../src/storage/accounted_reference.cpp#L307) | Callable definition: AccountedReferenceTable::Journal::Journal(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0065) |
| [B0066 · 308–310](../../../../../src/storage/accounted_reference.cpp#L308) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0066) |
| [B0067 · 311–311](../../../../../src/storage/accounted_reference.cpp#L311) | Callable definition: bool AccountedReferenceTable::Journal::active() const noexcept | calls ; returns data_ && data_-&gt;owner · [reviewed contract](#b0067) |
| [B0068 · 312–312](../../../../../src/storage/accounted_reference.cpp#L312) | Callable definition: std::size_t AccountedReferenceTable::Journal::size() const noexcept | calls size; returns data_ ? data_-&gt;entries.size() : 0 · [reviewed contract](#b0068) |
| [B0069 · 313–317](../../../../../src/storage/accounted_reference.cpp#L313) | Callable definition: AccountedReferenceTable::ChangeView AccountedReferenceTable::Journal::change(std::size_t index) const & | calls require, bool, size, begin; guard require(bool(data_) && index &lt; data_-&gt;entries.size(), TableProblem::invalid_journal);; returns {it-&gt;inserted, it-&gt;handle, it-&gt;pin-&gt;get()} · [reviewed contract](#b0069) |
| [B0070 · 318–318](../../../../../src/storage/accounted_reference.cpp#L318) | Callable definition: void AccountedReferenceTable::Journal::rollback() noexcept | calls rollback · [reviewed contract](#b0070) |
| [B0071 · 319–332](../../../../../src/storage/accounted_reference.cpp#L319) | Callable definition: void AccountedReferenceTable::Journal::commit() noexcept | calls active, lifetime, data, reset; 1 loop sites; source comment (unverified): // Each interior-node classification below searches the account ledger. · [reviewed contract](#b0071) |
| [B0072 · 333–338](../../../../../src/storage/accounted_reference.cpp#L333) | Callable definition: AccountedReferenceTable::Journal AccountedReferenceTable::journal() | calls state, unlocked, std::move, Journal; returns Journal(std::move(data)); growth make_accounted_shared, make_accounted_unique · [reviewed contract](#b0072) |
| [B0073 · 339–349](../../../../../src/storage/accounted_reference.cpp#L339) | Callable definition: InsertResult AccountedReferenceTable::Journal::insert(const AccountedTuple& tuple) | calls require, bool, active, input; guard require(bool(data_), TableProblem::invalid_journal);auto& s = data_-&gt;active();s.input(tuple);; returns {false, s.handle(found-&gt;second)}; result; growth emplace, insert; source comment (unverified): // Admit pin room before insertion; pinning the new row then cannot overflow · [reviewed contract](#b0073) |
| [B0074 · 350–372](../../../../../src/storage/accounted_reference.cpp#L350) | Callable definition: bool AccountedReferenceTable::Journal::erase(TupleHandle handle) | calls require, bool, active, owned; guard require(bool(data_), TableProblem::invalid_journal);auto& s = data_-&gt;active();s.owned(handle);; returns false; true; growth emplace; 1 loop sites · [reviewed contract](#b0074) |
| [B0075 · 373–376](../../../../../src/storage/accounted_reference.cpp#L373) | Callable definition: bool AccountedReferenceTable::erase(TupleHandle handle) | calls state, unlocked, owned, contains; returns false; erased · [reviewed contract](#b0075) |
| [B0076 · 377–379](../../../../../src/storage/accounted_reference.cpp#L377) | Callable definition: bool AccountedReferenceTable::erase(const AccountedTuple& tuple) | calls state, unlocked, find, erase; returns handle && erase(*handle) · [reviewed contract](#b0076) |
| [B0077 · 380–393](../../../../../src/storage/accounted_reference.cpp#L380) | Callable definition: IndexId AccountedReferenceTable::add_index(AccountedProjection projection) | calls state, unlocked, require, same_token; guard auto& s = state();s.unlocked();require(s.layout.same_token(projection.source()), TableProblem::layo…; returns id; id; growth emplace, insert; 2 loop sites · [reviewed contract](#b0077) |
| [B0078 · 394–397](../../../../../src/storage/accounted_reference.cpp#L394) | Callable definition: bool AccountedReferenceTable::drop_index(IndexId id) | calls state, unlocked, find, end; returns false; true · [reviewed contract](#b0078) |
| [B0079 · 398–401](../../../../../src/storage/accounted_reference.cpp#L398) | Callable definition: AccountedVector&lt;IndexId&gt; AccountedReferenceTable::indices() const | calls state, reserve, size, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0079) |
| [B0080 · 402–402](../../../../../src/storage/accounted_reference.cpp#L402) | Callable definition: AccountedProjection AccountedReferenceTable::projection(IndexId id) const | calls state, index; returns state().index(id).projection · [reviewed contract](#b0080) |
| [B0081 · 403–403](../../../../../src/storage/accounted_reference.cpp#L403) | Callable definition: std::size_t AccountedReferenceTable::key_count(IndexId id) const | calls state, index, size; returns state().index(id).buckets.size() · [reviewed contract](#b0081) |
| [B0082 · 404–409](../../../../../src/storage/accounted_reference.cpp#L404) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedReferenceTable::keys(IndexId id) const | calls state, index, reserve, size; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0082) |
| [B0083 · 410–415](../../../../../src/storage/accounted_reference.cpp#L410) | Callable definition: AccountedVector&lt;TupleHandle&gt; AccountedReferenceTable::bucket(IndexId id, const AccountedTuple& key) const | calls state, index, key, find; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0083) |
| [B0084 · 416–420](../../../../../src/storage/accounted_reference.cpp#L416) | Callable definition: std::size_t AccountedReferenceTable::erase_key(IndexId id, const AccountedTuple& key) | calls state, unlocked, bucket, empty; returns 0; handles.size(); 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 421–425](../../../../../src/storage/accounted_reference.cpp#L421) | Callable definition: void AccountedReferenceTable::clear() | calls state, unlocked, empty, mutable_revision; 1 loop sites · [reviewed contract](#b0085) |
| [B0086 · 426–426](../../../../../src/storage/accounted_reference.cpp#L426) | Explanatory comments or spacing. |  |
| [B0087 · 427–441](../../../../../src/storage/accounted_reference.cpp#L427) | Type/record definition: struct AccountedReferenceTable::Cursor::Data | guard const auto state = owner.lock();require(bool(state) && state-&gt;facade_alive, TableProblem::invalid_c…; returns state · [reviewed contract](#b0087) |
| [B0088 · 442–442](../../../../../src/storage/accounted_reference.cpp#L442) | Callable definition: AccountedReferenceTable::Cursor::Cursor(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0088) |
| [B0089 · 443–445](../../../../../src/storage/accounted_reference.cpp#L443) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0089) |
| [B0090 · 446–454](../../../../../src/storage/accounted_reference.cpp#L446) | Callable definition: std::optional&lt;TupleHandle&gt; AccountedReferenceTable::Cursor::next() | calls require, bool, valid, handle; guard require(bool(data_), TableProblem::invalid_cursor);const auto s = data_-&gt;valid();if (data_-&gt;empty) …; returns {}; {} · [reviewed contract](#b0090) |
| [B0091 · 455–464](../../../../../src/storage/accounted_reference.cpp#L455) | Callable definition: std::optional&lt;AccountedReferenceTable::Cursor::Entry&gt; AccountedReferenceTable::Cursor::next_entry() & | calls require, bool, valid, find; guard require(bool(data_), TableProblem::invalid_cursor);const auto s = data_-&gt;valid();if (data_-&gt;empty) …; returns {}; {} · [reviewed contract](#b0091) |
| [B0092 · 465–468](../../../../../src/storage/accounted_reference.cpp#L465) | Callable definition: AccountedReferenceTable::Cursor AccountedReferenceTable::live() const | calls state, unlocked, begin, end; returns Cursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0092) |
| [B0093 · 469–474](../../../../../src/storage/accounted_reference.cpp#L469) | Callable definition: AccountedReferenceTable::Cursor AccountedReferenceTable::bucket_cursor(IndexId id, const AccountedTuple& key) const | calls state, unlocked, index, key; returns Cursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0093) |
| [B0094 · 475–479](../../../../../src/storage/accounted_reference.cpp#L475) | Callable definition: AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::live() const | calls require, bool, active, begin; guard require(bool(data_), TableProblem::invalid_journal);auto& s = data_-&gt;active();; returns Cursor(std::move(cursor)); growth make_accounted_unique · [reviewed contract](#b0094) |
| [B0095 · 480–486](../../../../../src/storage/accounted_reference.cpp#L480) | Callable definition: AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::bucket_cursor(IndexId id, const AccountedTuple& key) const | calls require, bool, active, index; guard require(bool(data_), TableProblem::invalid_journal);auto& s = data_-&gt;active();auto& index = s.index…; returns Cursor(std::move(cursor)); growth make_accounted_unique · [reviewed contract](#b0095) |
| [B0096 · 487–493](../../../../../src/storage/accounted_reference.cpp#L487) | Type/record definition: struct AccountedReferenceTable::IndexKeyCursor::Data |  · [reviewed contract](#b0096) |
| [B0097 · 494–494](../../../../../src/storage/accounted_reference.cpp#L494) | Callable definition: AccountedReferenceTable::IndexKeyCursor::IndexKeyCursor(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0097) |
| [B0098 · 495–497](../../../../../src/storage/accounted_reference.cpp#L495) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0098) |
| [B0099 · 498–503](../../../../../src/storage/accounted_reference.cpp#L498) | Callable definition: std::optional&lt;AccountedReferenceTable::IndexKeyCursor::Entry&gt; AccountedReferenceTable::IndexKeyCursor::next() & | calls require, bool, lock, unlocked; guard require(bool(data_), TableProblem::invalid_cursor);const auto s = data_-&gt;owner.lock();; returns {}; Entry{entry.first, entry.second.size()} · [reviewed contract](#b0099) |
| [B0100 · 504–507](../../../../../src/storage/accounted_reference.cpp#L504) | Callable definition: AccountedReferenceTable::IndexKeyCursor AccountedReferenceTable::index_keys(IndexId id) const | calls state, unlocked, index, IndexKeyCursor; returns IndexKeyCursor(resource::make_accounted_unique&lt;IndexKeyCursor::Data&gt;(s.tag, s.account, MemoryPurpos…; growth make_accounted_unique · [reviewed contract](#b0100) |
| [B0101 · 508–513](../../../../../src/storage/accounted_reference.cpp#L508) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedReferenceTable::snapshot() const | calls state, reserve, size, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0101) |
| [B0102 · 514–521](../../../../../src/storage/accounted_reference.cpp#L514) | Callable definition: AccountedReferenceTable AccountedReferenceTable::snapshot_copy() const | calls state, unlocked, result, insert; returns result; growth insert; 2 loop sites · [reviewed contract](#b0102) |
| [B0103 · 522–541](../../../../../src/storage/accounted_reference.cpp#L522) | Callable definition: void AccountedReferenceTable::check_invariants() const | calls state, check_invariants, require, size; guard auto& s = state();s.arena.check_invariants();require(s.primary.size() == s.by_id.size() && s.primar…; 4 loop sites · [reviewed contract](#b0103) |
| [B0104 · 542–542](../../../../../src/storage/accounted_reference.cpp#L542) | Closes surrounding scope/type. |  · [reviewed contract](#b0104) |

## B0001

[Lines 1–20](../../../../../src/storage/accounted_reference.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:a44ed74887d3b38b94e222b6193b071e57539949f9eead34839a8f7ea351691e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import accounted-reference and standard declarations, open storage/helper namespaces, bind the shown resource names and define the constexpr maximum bound. |
| inputs / outputs | Preprocessor/name lookup and a fixed numeric maximum in; declarations available to following storage definitions out. Including list/map/set headers does not declare container instances here. |
| invariants | The constexpr/static metadata is initialized as a constant expression and has no per-instance owner. |
| ownership | Includes/using directives own no container or query object. maximum is fixed scalar metadata; actual container/account owners are declared in later spans. |
| failure | Missing headers or incompatible declarations fail compilation. This span implements no runtime resource refusal or recovery path. |
| cost | Preprocessing/parsing and constant initialization, with possible fixed constant storage. No list/map/set instance is constructed by these lines; later instances and their constructors/growth have their actual allocation costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 21–23](../../../../../src/storage/accounted_reference.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the fixed native table validation failure only on a failed predicate. |
| inputs / outputs | Boolean predicate and TableProblem select TableValidationFailure. |
| invariants | Success constructs no diagnostic string. Native failures are distinct from public formatted Error presentation. |
| ownership | Copies a small enum only. |
| failure | Throws the selected fixed failure without repairing caller state. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0003

[Lines 24–28](../../../../../src/storage/accounted_reference.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId new_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint a storage owner identity without wrapping into an old owner. |
| inputs / outputs | Shared storage-owner allocator returns a new StorageOwnerId. |
| invariants | Owner identity is independent of relation IDs and arena slot/generation identity. |
| ownership | One process-wide atomic identity source; no per-row registry/history. |
| failure | Exhaustion raises MemoryFailure overflow before publication. |
| cost | Actual atomic owner-ID allocation/retry; no payload allocation here. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0004

[Lines 29–35](../../../../../src/storage/accounted_reference.cpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native primary pointers or owning keys by typed tuple values. |
| inputs / outputs | Transparent overloads accept tuple references/pointers and order their values. |
| invariants | Pointers name live stable arena tuples or still-live preparation input; pointer addresses are not sort keys. |
| ownership | Only borrowed operands; no tuple/string export or copy. |
| failure | Noexcept under valid typed immutable row invariants. |
| cost | Lexicographic field/deep-byte comparisons; not constant in tuple width or string size. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0005

[Lines 36–36](../../../../../src/storage/accounted_reference.cpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Reader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry active/committed/aborted authority for owner-only journal cursors. |
| inputs / outputs | A shared small phase object is created at journal startup and updated on close. |
| invariants | Aborted authority invalidates cursors before undo; committed authority still needs a live facade and matching revision. |
| ownership | Journal/cursors share an account-funded control object; it owns no table rows. |
| failure | Startup allocation failure installs no active writer. |
| cost | One fixed phase plus shared control storage; no per-entry authority objects. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0006

[Lines 37–42](../../../../../src/storage/accounted_reference.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
typename Map::node_type prepare_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate and detach one ordered-container node before mutating its destination. |
| inputs / outputs | Destination comparator/allocator plus construction arguments return an extracted node handle. |
| invariants | A temporary one-element container uses the exact destination allocator; the destination remains unchanged. |
| ownership | Detached node handle owns its allocation until published or destroyed. |
| failure | Allocation/construction failure destroys preparation only. |
| cost | One node construction/allocation, comparator work on one item; no destination rebuild. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0007

[Lines 43–47](../../../../../src/storage/accounted_reference.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto publish_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already owned compatible ordered node without allocating replacement storage. |
| inputs / outputs | Destination and extracted node return its inserted iterator. |
| invariants | Caller proved key absence and allocator/comparator compatibility; failed insertion is an internal invariant violation. |
| ownership | Transfers node ownership into the destination; no value/payload copy. |
| failure | Noexcept publication terminates on an impossible duplicate. |
| cost | Ordered insertion/rebalancing and comparator costs remain; nonallocation does not mean O(1). |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0008

[Lines 48–51](../../../../../src/storage/accounted_reference.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reserve(Vector& values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a requested native vector length before reserve. |
| inputs / outputs | Vector and element count prepare capacity or retain existing sufficient capacity. |
| invariants | Element count must fit vector max_size; nested member ownership remains the element contract. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Overflow or allocation failure leaves vector contents valid. |
| cost | Actual capacity growth/move/initialization cost; no work-grant refill. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0009

[Lines 52–57](../../../../../src/storage/accounted_reference.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool matches(const AccountedProjection&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a secondary key against selected source fields without creating a projected tuple. |
| inputs / outputs | Projection, full source tuple and typed key return exact equality on every selected field. |
| invariants | Both immutable layout tokens must match; failed token checks return false before field access. |
| ownership | Borrows native views and numeric slots only. |
| failure | False for mismatched layouts/fields; no diagnostic or mutation. |
| cost | O(selected fields and compared deep bytes), no row/key allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0010

[Lines 58–58](../../../../../src/storage/accounted_reference.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L58:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/accounted_reference.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/accounted_reference.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/accounted_reference.cpp\` at its lexical source position in src/storage/accounted_reference.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/accounted_reference.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 59–72](../../../../../src/storage/accounted_reference.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view TableValidationFailure::code()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a native table problem enum to its stable diagnostic code. |
| inputs / outputs | Problem selects invalid_storage/journal/cursor/owner/layout/index/busy/contract code. |
| invariants | Codes have static storage; unknown enum falls back to storage_contract. |
| ownership | Returns a borrowed static string_view. |
| failure | Noexcept; no formatted message allocation. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0012

[Lines 73–73](../../../../../src/storage/accounted_reference.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* TableValidationFailure::what()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the fixed native table code as the exception message. |
| inputs / outputs | Returns code().data() from static null-terminated literals. |
| invariants | Presentation is intentionally fixed native text, not a formatted public diagnostic. |
| ownership | Static borrowed bytes; no account/payload retained. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0013

[Lines 74–77](../../../../../src/storage/accounted_reference.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedReferenceTable::State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own ordered primary/ID/index state, stable arena tuples and journal/read authority. |
| inputs / outputs | Account/layout/relation/owner establish empty native table state. |
| invariants | Primary keys borrow arena tuple addresses ordered by values; by-ID records point back to primary nodes. Secondary keys own typed projections; live membership sets agree with primary/arena. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Construction failure publishes no facade; external callers must not mutate concurrently or reenter preparation. |
| cost | State/counters are fixed metadata; maps/arena grow with actual rows, indices, keys, memberships and retained history. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0014

[Lines 78–78](../../../../../src/storage/accounted_reference.cpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Record {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate a logical tuple ID with its primary iterator and generational arena handle. |
| inputs / outputs | Primary iterator plus ArenaHandle locate one row from by_id. |
| invariants | Iterator is rebound after extracted primary nodes are restored; logical TupleId is distinct from arena slot/generation. |
| ownership | Inline borrowed iterator/handle, not an owning tuple duplicate. |
| failure | Caller establishes membership consistency before publication. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0015

[Lines 79–81](../../../../../src/storage/accounted_reference.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L81:sha256:575333e1c1b379d79eb3afc027d566abf70bbe456b01d60a8b65f657c680c7b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp: imports or aliases \`ById = std::map&lt;TupleId, Record, std::less&lt;TupleId&gt;, MemoryAllocator&lt;std::pair&lt;const TupleId, Record&gt;&gt;&gt;\`, \`Members = std::set&lt;TupleId, std::less&lt;TupleId&gt;, MemoryAllocator&lt;TupleId&gt;&gt;\`, \`Buckets = std::map&lt;AccountedTuple, Members, TupleLess, MemoryAllocator&lt;std::pair&lt;const AccountedTuple, Members&gt;&gt;&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. Accounted row/tuple values own compact payload under their associated account. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0016

[Lines 82–87](../../../../../src/storage/accounted_reference.cpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Index {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable projection and its exact ordered key/member directory. |
| inputs / outputs | Projection/account/tag produce an initially empty bucket map. |
| invariants | Every live primary tuple belongs to exactly one bucket per index; empty ordinary buckets are removed. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Allocation/preparation failure destroys unpublished index state. |
| cost | O(secondary keys + row memberships) resident nodes and deep key bytes; no hash assumptions. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0017

[Lines 88–101](../../../../../src/storage/accounted_reference.cpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L101:sha256:7daed09610c5ac4f1020bfe42f24aabdb2a28ff662216048c03a7b70cf331cd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp: imports or aliases \`Indices = std::map&lt;IndexId, Index, std::less&lt;IndexId&gt;, MemoryAllocator&lt;std::pair&lt;const IndexId, Index&gt;&gt;&gt;\`; closes \`block opened at line 93\` Member/state declarations in this range include \`MemoryAccount account\`; \`std::uint64_t last_tuple = 0, last_index = 0, revision = 0\`; \`std::size_t active_entries = 0, retained_entries = 0\`; \`bool journal_active = false, facade_alive = true\`; \`std::weak_ptr&lt;Reader&gt; active_reader\`. |
| inputs / outputs | This span declares/carries these members or local values: \`MemoryAccount account\`; \`std::uint64_t last_tuple = 0, last_index = 0, revision = 0\`; \`std::size_t active_entries = 0, retained_entries = 0\`; \`bool journal_active = false, facade_alive = true\`; \`std::weak_ptr&lt;Reader&gt; active_reader\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | The declared MemoryAccount field/owner shares the query account supplied at construction. Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. weak_ptr members observe state without retaining it. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0018

[Lines 102–106](../../../../../src/storage/accounted_reference.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(MemoryAccount value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the empty ordered backend under a supplied layout account. |
| inputs / outputs | Account, relation, immutable layout and freshly minted owner create arena and native maps. |
| invariants | Stored primary pointers cannot precede arena preparation; IDs/revision start at zero. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Nested allocation failure unwinds empty state members before any facade is published. |
| cost | Empty state/arena owner setup; actual map nodes are deferred until insert/index creation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0019

[Lines 107–107](../../../../../src/storage/accounted_reference.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlocked() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject ordinary mutators/cursor factories while a journal is active. |
| inputs / outputs | Reads journal_active; success permits ordinary mutation. |
| invariants | This is an exclusive-writer guard, not reader synchronization. |
| ownership | Inline validation on borrowed state. |
| failure | storage_busy while journaled. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0020

[Lines 108–108](../../../../../src/storage/accounted_reference.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mutable_revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one real revision advance without wraparound. |
| inputs / outputs | Checks current revision against uint64 maximum. |
| invariants | No-op operations must decide whether a revision is needed before mutation. |
| ownership | Inline validation on borrowed state. |
| failure | MemoryFailure overflow before a real mutation. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0021

[Lines 109–109](../../../../../src/storage/accounted_reference.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input(const AccountedTuple&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact immutable tuple-layout identity for table input. |
| inputs / outputs | Checks the table layout token against the tuple token. |
| invariants | Structurally equal foreign descriptors do not substitute for the admitted native token. |
| ownership | Inline validation on borrowed state. |
| failure | layout_mismatch before key lookup/mutation. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0022

[Lines 110–110](../../../../../src/storage/accounted_reference.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(TupleHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate logical handle owner/relation before ID lookup. |
| inputs / outputs | Checks handle owner and relation; it does not prove the ID is live. |
| invariants | A stale local ID and a foreign handle have different outcomes. |
| ownership | Inline validation on borrowed state. |
| failure | foreign_handle for an incompatible owner/relation. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0023

[Lines 111–111](../../../../../src/storage/accounted_reference.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleHandle handle(TupleId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a logical handle for an ID already admitted by this table. |
| inputs / outputs | TupleId combines with stored owner and relation. |
| invariants | It does not check liveness; callers supply an ID from a valid map entry. |
| ownership | Copies fixed identifiers only. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0024

[Lines 112–114](../../../../../src/storage/accounted_reference.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Index& index(IndexId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a currently installed ordered secondary index. |
| inputs / outputs | IndexId lookup returns its map value by reference. |
| invariants | Index references cannot outlive a drop/table mutation that destroys that entry. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | unknown_index if absent. |
| cost | O(log index count), no index/key copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0025

[Lines 115–117](../../../../../src/storage/accounted_reference.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void key(const Index& index,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the immutable target layout of a secondary probe key. |
| inputs / outputs | Index and AccountedTuple must share its target token. |
| invariants | Field values were validated at tuple construction; no coercion/structural layout fallback. |
| ownership | Borrows descriptors only. |
| failure | layout_mismatch on foreign target token. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0026

[Lines 118–120](../../../../../src/storage/accounted_reference.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<T> vector(MemoryPurpose
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a native temporary vector with table attribution. |
| inputs / outputs | MemoryPurpose selects a same-account allocator for an empty vector. |
| invariants | Nested elements must independently use accounted ownership when retained. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Empty owner construction requires a valid account; later growth can reject. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0027

[Lines 121–123](../../../../../src/storage/accounted_reference.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<T> output() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a native output vector whose lifetime belongs to the caller. |
| inputs / outputs | Creates an empty same-account vector with output purpose/attribution. |
| invariants | Output buffers are distinct from table/arena owner accounting totals. |
| ownership | Returned allocator retains the original account, not table membership. |
| failure | Later reserve/copy failures unwind the partial result. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0028

[Lines 124–124](../../../../../src/storage/accounted_reference.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAttribution output_tag() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label exported native buffers/payloads without retaining the table. |
| inputs / outputs | Returns output owner kind and this table identity. |
| invariants | Attribution does not create a separate memory account or row registry. |
| ownership | Copies two fixed metadata values. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0029

[Lines 125–127](../../../../../src/storage/accounted_reference.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifetime(const T& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify an extracted interior map/list value in its original allocation ledger. |
| inputs / outputs | Interior address, expected purpose and lifetime update native attribution statistics. |
| invariants | The allocation is live and belongs to this table; pointer identifies contained storage, not necessarily its allocation base. |
| ownership | No node/value ownership transfer or copy. |
| failure | Noexcept under funded inverse/account invariants. |
| cost | O(outstanding account allocations) containing-pointer search; distinct from direct allocation-header classification. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0030

[Lines 128–161](../../../../../src/storage/accounted_reference.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult insert(const AccountedTuple& tuple)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare every ordered node/key before publishing a new native row. |
| inputs / outputs | Validated tuple yields existing handle or a newly allocated logical/arena identity. |
| invariants | Duplicate lookup precedes preparation. ID/revision room, detached primary/ID/bucket/member nodes and projections are prepared first; arena insertion is the last throwing step, then the primary key is rebound to its stable arena tuple. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Before publication failure destroys detached preparation and leaves logical membership/ID high-water unchanged. |
| cost | Ordered primary/secondary probes, per-index projected deep-key copies and node allocations plus one arena row copy; no full table clone. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0031

[Lines 162–164](../../../../../src/storage/accounted_reference.cpp#L162); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L164:sha256:6477de4c488991e0ac903fc04a29843d5c53aa0c5f4f3f42c66b66e09007c3c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp: defines/starts \`struct AccountedReferenceTable::Journal::Data\` in this range; closes \`struct AccountedReferenceTable::State\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0032

[Lines 165–170](../../../../../src/storage/accounted_reference.cpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Key {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one secondary-index inverse with its projected key and detached membership/bucket nodes. |
| inputs / outputs | Index pointer, owning typed key and optional extracted nodes identify one undo obligation. |
| invariants | Undo re-finds buckets by the retained key; it never trusts an iterator invalidated by later extraction/reinsertion. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Projection/allocation failure precedes table mutation. |
| cost | One native projected key/entry per current index; deep key bytes and eventual ledger classification are real costs. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0033

[Lines 171–181](../../../../../src/storage/accounted_reference.cpp#L171); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Undo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own exactly the row inverse and pin needed for one journal insertion or erasure. |
| inputs / outputs | Direction, logical handle, previous ID high-water, tuple pin, keys and detached primary/ID nodes describe a successful change. |
| invariants | Insertion undo restores previous last_tuple; erase undo restores exact nodes/arena slot and tuple address. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Preparation failure destroys only unpublished inverse storage; published inverse survives until commit/rollback. |
| cost | One accounted list node plus per-index key vector/payloads; erasure retains existing map nodes rather than copying a row replacement. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0034

[Lines 182–187](../../../../../src/storage/accounted_reference.cpp#L182); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L182-L187:sha256:d250d98891c2cbf6dfa79d2f0310b9d0489d969e126edd97b705d973f3752b8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp: imports or aliases \`Entries = std::list&lt;Undo, MemoryAllocator&lt;Undo&gt;&gt;\` Member/state declarations in this range include \`std::shared_ptr&lt;State&gt; owner\`; \`std::weak_ptr&lt;State&gt; report_owner\`; \`std::shared_ptr&lt;Reader&gt; reader\`; \`bool committed = false\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::shared_ptr&lt;State&gt; owner\`; \`std::weak_ptr&lt;State&gt; report_owner\`; \`std::shared_ptr&lt;Reader&gt; reader\`; \`bool committed = false\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. shared_ptr members retain shared state for the handle lifetime. weak_ptr members observe state without retaining it. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0035

[Lines 188–190](../../../../../src/storage/accounted_reference.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<State> state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a journal owner, weak reporting reference and shared reader phase. |
| inputs / outputs | Shared table state/Reader produce an empty accounted inverse list. |
| invariants | The table journal_active flag is installed only after this Data is completely allocated. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Constructor failure leaves the table unlocked. |
| cost | Fixed owner/control/list metadata; no entry preparation yet. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0036

[Lines 191–197](../../../../../src/storage/accounted_reference.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Roll back an abandoned journal or release its retained committed-history accounting. |
| inputs / outputs | Active owner invokes rollback; committed Data decrements retained_entries if table state still exists. |
| invariants | History accounting is weak: committed history pins payloads without keeping the entire table state alive. |
| ownership | Then releases inverse list, pinned payloads and projected keys through their original account. |
| failure | No allocation during cleanup; impossible retained count underflow terminates. |
| cost | Actual inverse/history destruction and possible final arena/account release; not fixed-time final destruction. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0037

[Lines 198–198](../../../../../src/storage/accounted_reference.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State& active() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the journal exclusive table owner while the token is open. |
| inputs / outputs | Checks owner and active flag, then returns State. |
| invariants | Committed/rolled-back journals retain diagnostic history only, not mutation authority. |
| ownership | Reference borrows Data strong owner. |
| failure | invalid_journal after close. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0038

[Lines 199–211](../../../../../src/storage/accounted_reference.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Entries prepare(bool inserted,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund one complete ordered inverse in a temporary one-entry list. |
| inputs / outputs | Direction and full tuple produce staged Undo plus one owning projected key for every index. |
| invariants | Active/history counter room and list capacity are checked before growth; prepared entries are not yet part of public change history. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Failure leaves table and existing journal entries unchanged. |
| cost | One list allocation, O(indices) vector entries and selected field/deep-byte key copies. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0039

[Lines 212–212](../../../../../src/storage/accounted_reference.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish(Entries& staged)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Splice a completely prepared successful change into journal history. |
| inputs / outputs | One staged list transfers into entries and increments active_entries. |
| invariants | Allocators match and the underlying native mutation already completed; splice needs no replacement node. |
| ownership | Transfers inverse ownership to active Data. |
| failure | Noexcept under preparation/counter-room invariants. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0040

[Lines 213–225](../../../../../src/storage/accounted_reference.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_insert(Undo& undo)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse a journal insertion without allocating replacement storage. |
| inputs / outputs | Retained keys/handle remove memberships, primary/ID records and arena liveness, then restore last_tuple. |
| invariants | Reverse operation order guarantees the inserted logical row still has its expected index population. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Noexcept; missing expected membership is an internal terminate condition. |
| cost | Ordered key/ID lookups and node/payload releases per index; no new tuple/key construction. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0041

[Lines 226–243](../../../../../src/storage/accounted_reference.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_erase(Undo& undo)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an erased row with its exact retained arena and ordered nodes. |
| inputs / outputs | Pin revives the original tuple, then primary/ID and bucket/member node handles are reinserted. |
| invariants | The by-ID primary iterator is rebound; bucket identity is re-found if later journal operations replaced it. Exact logical ID/address survive. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Noexcept; incompatible/missing inverse state is an internal contract violation. |
| cost | Ordered reinsertion/comparison and containing-pointer lifetime scans; no allocation/deep-copy replacement. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0042

[Lines 244–252](../../../../../src/storage/accounted_reference.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort tentative journal reads before restoring every inverse in reverse order. |
| inputs / outputs | Active Data marks Reader aborted, undoes changes, clears active state/history and releases owner. |
| invariants | Closed Data is a no-op. Revision is not restored, so ordinary cursors invalidated by real mutation remain invalid. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Noexcept using retained nodes/pins; returned pre-rollback ChangeView references become invalid when entries clear. |
| cost | Actual inverse and payload cleanup; no full table reconstruction or fresh work/account. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0043

[Lines 253–254](../../../../../src/storage/accounted_reference.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L254:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct AccountedReferenceTable::Journal::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct AccountedReferenceTable::Journal::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct AccountedReferenceTable::Journal::Data\` at its lexical source position in src/storage/accounted_reference.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct AccountedReferenceTable::Journal::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0044

[Lines 255–255](../../../../../src/storage/accounted_reference.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount AccountedReferenceTable::account_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable layout original account for this backend. |
| inputs / outputs | AccountedLayout returns its query_account handle. |
| invariants | Constructing a table does not mint an independent cap/account. |
| ownership | Copies the account owner handle only. |
| failure | Invalid layout is rejected by the facade constructor before this helper. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0045

[Lines 256–256](../../../../../src/storage/accounted_reference.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::classify(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a retained key tuple through its native payload allocation. |
| inputs / outputs | Tuple and active/retained lifetime update existing native accounting. |
| invariants | Original account/purpose/attribution remain unchanged. |
| ownership | No tuple copy or new ownership. |
| failure | Noexcept under internal valid lifetime/nonreentrancy invariants. |
| cost | Direct tuple allocation-header lifetime work; distinct from map interior-pointer scans. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0046

[Lines 257–257](../../../../../src/storage/accounted_reference.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::revive(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a retained arena row using its exact pin. |
| inputs / outputs | Arena plus retained Pin revive the original slot/generation/address. |
| invariants | Private inverse only; not a public raw-ID import or resurrection API. |
| ownership | Pin retains original arena state and native tuple. |
| failure | Noexcept under funded matching-pin invariants. |
| cost | O(1) native arena bookkeeping/classification, no row copy or replacement allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0047

[Lines 258–262](../../../../../src/storage/accounted_reference.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::AccountedReferenceTable(RelationId
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit an empty ordered table with fresh storage identity in the layout account. |
| inputs / outputs | Relation and valid AccountedLayout allocate a new State and arena owner. |
| invariants | Layout token/account is reused, table owner is fresh, logical IDs start empty. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Bad layout/owner exhaustion/allocation failure publishes no table facade. |
| cost | Native state/arena setup allocations; no resident row/index population yet. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0048

[Lines 263–263](../../../../../src/storage/accounted_reference.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::AccountedReferenceTable(std::shared_ptr<State>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a previously constructed state without cloning rows. |
| inputs / outputs | Private shared State moves into a facade. |
| invariants | Used internally with valid ownership/protocol; does not validate/import an external table. |
| ownership | Transfers one shared owner. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0049

[Lines 264–264](../../../../../src/storage/accounted_reference.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::~AccountedReferenceTable()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire facade authority before releasing its shared native state. |
| inputs / outputs | If nonempty, marks facade_alive=false; active journal owners may still keep state for completion/undo. |
| invariants | Low-level cursor borrowing does not authorize traversal after facade loss. |
| ownership | Releases facade shared owner; journal/payload pins have independent retained lifetimes. |
| failure | Destruction requires no new allocation. |
| cost | Flag update plus possible destruction of all owned state; not O(1) final release. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0050

[Lines 265–265](../../../../../src/storage/accounted_reference.cpp#L265); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L265:sha256:d01f2d48a97ecebe4a93eb88faeda30255d6035207af3dbbf04b2552c6fb815e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0051

[Lines 266–268](../../../../../src/storage/accounted_reference.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable& AccountedReferenceTable::operator=(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer table facade ownership and invalidate destination old-facade cursors. |
| inputs / outputs | Move assignment retires any prior destination facade then moves the source state. |
| invariants | Self move is a no-op; old active journals retain their own owner for rollback/commit. |
| ownership | No state clone; release of previous destination follows shared-owner lifetimes. |
| failure | Noexcept. |
| cost | Fixed move plus actual previous-state release; no new allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0052

[Lines 269–271](../../../../../src/storage/accounted_reference.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::State& AccountedReferenceTable::state()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a valid table state after rejecting a moved-from facade. |
| inputs / outputs | Nonempty facade returns State by reference. |
| invariants | State existence is distinct from journal exclusivity and logical handle liveness. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | invalid_storage for moved-from/empty facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0053

[Lines 272–272](../../../../../src/storage/accounted_reference.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId AccountedReferenceTable::owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect storage identity. |
| inputs / outputs | Returns this table owner ID, not arena/account identity. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0054

[Lines 273–273](../../../../../src/storage/accounted_reference.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId AccountedReferenceTable::relation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect relation identity. |
| inputs / outputs | Returns the declared relation ID. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0055

[Lines 274–274](../../../../../src/storage/accounted_reference.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedReferenceTable::layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the table immutable native layout. |
| inputs / outputs | Returns the State layout by const lvalue reference. |
| invariants | The caller keeps the containing table/state alive; no lifetime extension through a temporary facade. |
| ownership | Borrows the retained descriptor handle. |
| failure | invalid_storage when moved-from. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0056

[Lines 275–275](../../../../../src/storage/accounted_reference.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedReferenceTable::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect live primary cardinality. |
| inputs / outputs | Returns primary.size(), excluding erased retained payloads/history. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0057

[Lines 276–276](../../../../../src/storage/accounted_reference.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t AccountedReferenceTable::revision()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect cursor invalidation revision. |
| inputs / outputs | Returns monotone revision; rollback does not restore an old revision. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0058

[Lines 277–277](../../../../../src/storage/accounted_reference.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAttribution AccountedReferenceTable::attribution()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect table allocation attribution. |
| inputs / outputs | Returns storage_table kind and owner identity. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0059

[Lines 278–278](../../../../../src/storage/accounted_reference.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics AccountedReferenceTable::arena_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect maintained arena counters. |
| inputs / outputs | Returns live/retained/free/exhausted slot and pin counts by value. |
| invariants | Metadata can be read without acquiring writer isolation. |
| ownership | Copies fixed metadata; no row/payload owner copy. |
| failure | invalid_storage for a moved-from facade. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0060

[Lines 279–292](../../../../../src/storage/accounted_reference.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TableMemoryStatistics AccountedReferenceTable::memory_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual native table/arena usage and current logical populations. |
| inputs / outputs | Counts live records/index keys/memberships and active/retained undo; adds disjoint table and arena attributed usage. |
| invariants | Shared immutable layouts and caller-tagged output are separate owners, not silently duplicated in owned. This is a diagnostic, not an update primitive. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | Invalid facade/ledger invariant failure propagates; no state repair. |
| cost | O(account allocations + arena slot high-water + index/key population); member set size is read without walking every member. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0061

[Lines 293–293](../../../../../src/storage/accounted_reference.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedReferenceTable::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert through the ordinary exclusive-guarded ordered path. |
| inputs / outputs | Tuple returns InsertResult with changed flag and logical handle. |
| invariants | Even a duplicate insert rejects an active journal before lookup. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | busy/layout/overflow/allocation failure retains the State insert strong guarantee. |
| cost | Fixed facade guard plus actual State::insert lookup, per-index preparation and arena copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0062

[Lines 294–298](../../../../../src/storage/accounted_reference.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> AccountedReferenceTable::find(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe exact typed tuple identity without owning a copy. |
| inputs / outputs | Compatible tuple returns its local logical handle or nullopt. |
| invariants | This low-level read can observe tentative journal state; runtime guards visibility separately. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | Foreign layout throws layout_mismatch; absence returns nullopt. |
| cost | O(log rows) lexicographic comparisons and actual deep bytes; no row copy/allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0063

[Lines 299–302](../../../../../src/storage/accounted_reference.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedTuple* AccountedReferenceTable::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a live native tuple by local logical ID. |
| inputs / outputs | Owned handle returns pointer or nullptr when its ID is absent. |
| invariants | Borrow expires on erasure/table loss; handles never published before commit because tentative IDs may later be reused after rollback. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | foreign_handle for wrong owner/relation; stale local ID returns nullptr. |
| cost | O(log rows) ID lookup and O(1) arena access; no payload copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0064

[Lines 303–306](../../../../../src/storage/accounted_reference.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin AccountedReferenceTable::pin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the original arena payload behind one live local handle. |
| inputs / outputs | Owned live handle returns a pin that survives later membership erasure. |
| invariants | Pin owns payload lifetime, not current table membership or the whole table facade. |
| ownership | Retains original arena/account; no deep tuple copy. |
| failure | foreign/stale handle or pin-counter overflow rejects before increment. |
| cost | O(log rows) ID lookup plus fixed pin ownership/counters; final release can reclaim payload/state. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0065

[Lines 307–307](../../../../../src/storage/accounted_reference.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Journal::Journal(resource::
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt already funded journal Data. |
| inputs / outputs | Unique Data moves into the public Journal token. |
| invariants | Table active flag and reader were installed after preparation by journal(). |
| ownership | Transfers sole Data ownership; no table clone. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0066

[Lines 308–310](../../../../../src/storage/accounted_reference.cpp#L308); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L308-L310:sha256:c5e4c4797fe34b851bbcf13b2cd60192b86c9deda81f33f5315f2b88d92fba78
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0067

[Lines 311–311](../../../../../src/storage/accounted_reference.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedReferenceTable::Journal::active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect whether a journal still owns tentative mutation authority. |
| inputs / outputs | Returns true only with Data and an active table owner. |
| invariants | Moved-from, committed and rolled-back tokens are inactive. |
| ownership | Only inline token/owner checks. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0068

[Lines 312–312](../../../../../src/storage/accounted_reference.cpp#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedReferenceTable::Journal::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect retained change-list length. |
| inputs / outputs | Returns entry count when active/committed, zero for absent/rolled-back history. |
| invariants | Number of changes is distinct from table cardinality and includes repeated operations on one row. |
| ownership | Copies maintained list size. |
| failure | Noexcept, including moved-from token. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0069

[Lines 313–317](../../../../../src/storage/accounted_reference.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::ChangeView AccountedReferenceTable::Journal::change(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one pinned change record by ordinal. |
| inputs / outputs | Index returns operation/handle and original tuple reference. |
| invariants | Lvalue-only access does not extend journal lifetime. After commit pins remain; rollback clears them. |
| ownership | Tuple is borrowed from the entry pin, not a new owning output row. |
| failure | invalid_journal for absent/out-of-range entry. |
| cost | O(index) list traversal, unlike indexed vector history access; no tuple copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0070

[Lines 318–318](../../../../../src/storage/accounted_reference.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::Journal::rollback()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly abandon all active tentative changes. |
| inputs / outputs | Active token reverses journal; closed/moved-from token is a no-op. |
| invariants | Same idempotent path as Data destruction, no sequence publication. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Noexcept under prepared inverse invariants. |
| cost | Actual reverse changes and history/payload cleanup; no new allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0071

[Lines 319–332](../../../../../src/storage/accounted_reference.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::Journal::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep installed table state while retaining owning change history. |
| inputs / outputs | Active token classifies inverse/control storage retained, marks reader committed, unlocks and releases strong table owner. |
| invariants | Commit does not promise constant-time cleanup and does not retain the complete table just for history. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Noexcept using existing allocations; moved/closed token is a no-op. |
| cost | O(entries and containing-pointer account-ledger classifications), potentially entries times outstanding allocations; no new allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0072

[Lines 333–338](../../../../../src/storage/accounted_reference.cpp#L333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Journal AccountedReferenceTable::journal()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one exclusive table journal and reader authority. |
| inputs / outputs | Unlocked table allocates shared Reader and unique Data, then installs journal_active. |
| invariants | No active flag before both owners succeed. Ordinary mutators/cursor factories reject while open; compatible journal cursors use its authority. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Allocation failure leaves table unlocked; nested journal raises storage_busy. |
| cost | Two funded owner/control preparations, no full state snapshot or fresh memory account. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0073

[Lines 339–349](../../../../../src/storage/accounted_reference.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedReferenceTable::Journal::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a captured insertion without disturbing previous journal stages on failure. |
| inputs / outputs | Compatible tuple yields existing handle or a new pinned change entry. |
| invariants | Duplicate probe precedes undo growth. Global pin room is checked before State::insert; new row pin creation is then nonallocating. Publish staged list only after insertion/pin are ready. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Failure before publication destroys staged preparation and leaves prior journal state unchanged. |
| cost | Duplicate lookup plus State insert lookup, per-index inverse projected keys, row/index preparation and one pin; no before-state table copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0074

[Lines 350–372](../../../../../src/storage/accounted_reference.cpp#L350); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedReferenceTable::Journal::erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach one live row after preparing keys, pin and inverse capacity. |
| inputs / outputs | Owned handle erases current membership and publishes one inverse, or returns false if absent. |
| invariants | Primary/ID/member/bucket nodes are extracted rather than rebuilt; last bucket removal retains its owning key. Revision advances, and saved inverse can restore exact identity. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Foreign/invalid journal, overflow or preparation failure rejects before detach; after detach only nonallocating operations remain. |
| cost | O(indices and ordered probes + projected deep bytes), plus containing-pointer lifetime scans; retained payload is not a replacement row copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0075

[Lines 373–376](../../../../../src/storage/accounted_reference.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedReferenceTable::erase(TupleHandle
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase a local live handle as one short committed journal. |
| inputs / outputs | Owned handle returns true if erased, false if absent. |
| invariants | Ordinary erase rejects an open journal; successful standalone erase creates/commits its own inverse scope. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Foreign/busy/preparation failures leave membership unchanged. |
| cost | ID lookup plus journal Reader/Data/list/key/pin preparation and commit cleanup; not a bare constant-time unlink. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0076

[Lines 377–379](../../../../../src/storage/accounted_reference.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedReferenceTable::erase(const AccountedTuple&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase by exact full tuple through the handle/journal path. |
| inputs / outputs | Typed tuple finds current logical handle, then erases or returns false. |
| invariants | Full-row identity, not projection identity; no-op still checks ordinary writer readiness. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Busy/layout/preparation failure leaves membership valid. |
| cost | Ordered tuple probe plus actual handle erase/journal costs; no owning input conversion. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0077

[Lines 380–393](../../../../../src/storage/accounted_reference.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId AccountedReferenceTable::add_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a complete ordered projection index before installing it. |
| inputs / outputs | Same-source native projection returns existing token-identical index or a new IndexId. |
| invariants | Duplicate descriptor reuse does not advance revision. New index/key/member population is local until complete, and ID/revision room is admitted first. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Busy/foreign source/overflow/allocation failure leaves installed indices unchanged. |
| cost | O(rows) projected tuples and ordered key/member insertions with deep key bytes; one complete new index population, not a full table duplicate. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0078

[Lines 394–397](../../../../../src/storage/accounted_reference.cpp#L394); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedReferenceTable::drop_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove an installed secondary index under the ordinary writer guard. |
| inputs / outputs | IndexId returns true if dropped, false if absent. |
| invariants | Real drop advances revision so captured iterators cannot continue into destroyed buckets. |
| ownership | Releases index keys/member nodes/descriptors through original account. |
| failure | Busy/revision overflow rejects before destruction. |
| cost | Index lookup plus actual key/member/payload destruction; absent ID is O(log indices). |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0079

[Lines 398–401](../../../../../src/storage/accounted_reference.cpp#L398); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<IndexId> AccountedReferenceTable::indices()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an owning native vector of current index IDs. |
| inputs / outputs | Returns IDs in ordered-map iteration order. |
| invariants | Vector ownership does not keep any index installed. |
| ownership | Funded output buffer retains account, values are fixed IDs. |
| failure | Growth failure destroys only partial result. |
| cost | O(index count) reserve/copy; no row/key payload scan. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0080

[Lines 402–402](../../../../../src/storage/accounted_reference.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedProjection AccountedReferenceTable::projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an immutable descriptor for one installed index. |
| inputs / outputs | IndexId returns a shared native projection value. |
| invariants | A copied descriptor outlives index drop but does not preserve index membership. |
| ownership | Retains original account/layout/field descriptor; no field-array copy. |
| failure | unknown_index if absent. |
| cost | O(log indices) probe plus fixed descriptor-owner copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0081

[Lines 403–403](../../../../../src/storage/accounted_reference.cpp#L403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedReferenceTable::key_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect distinct live key cardinality for one installed index. |
| inputs / outputs | IndexId returns buckets.size(). |
| invariants | Ordinary bucket map contains no empty live keys; retained inverse nodes are separate. |
| ownership | Copies fixed cardinality. |
| failure | unknown_index if absent. |
| cost | O(log indices), no key iteration. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0082

[Lines 404–409](../../../../../src/storage/accounted_reference.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedReferenceTable::keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy all live typed keys into owning native output. |
| inputs / outputs | IndexId returns an original-account vector of independent key tuples. |
| invariants | This explicit collection copy is different from a borrowed key cursor. |
| ownership | Output vector and deep key payloads survive source index/table destruction. |
| failure | Unknown index/allocation failure leaves source unchanged. |
| cost | O(keys and deep bytes) owning copies plus vector reserve; not constant startup. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0083

[Lines 410–415](../../../../../src/storage/accounted_reference.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<TupleHandle> AccountedReferenceTable::bucket(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize matching logical handles for one typed key. |
| inputs / outputs | IndexId and compatible key return an owning handle vector, empty if absent. |
| invariants | Handles do not pin rows; logical state can be tentative at this low-level read. |
| ownership | Vector retains account only; its elements borrow table identity/liveness. |
| failure | Unknown index/layout/allocation failure changes no table state. |
| cost | Ordered index/key lookup plus O(matches) handle copy and buffer storage. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0084

[Lines 416–420](../../../../../src/storage/accounted_reference.cpp#L416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedReferenceTable::erase_key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically erase a captured bucket through one journal. |
| inputs / outputs | Index/key materialize matching handles; a journal erases them all and commits, returning count. |
| invariants | No matches returns zero. Any later preparation failure unwinds the active journal and restores earlier erasures. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Busy/invalid key/index/allocation failure preserves the complete prior table. |
| cost | O(matches) handle buffer plus per-row/per-index journal work; no lazy constant-space erase stream. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0085

[Lines 421–425](../../../../../src/storage/accounted_reference.cpp#L421); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard every live membership without retaining a new undo history. |
| inputs / outputs | Unlocked nonempty table clears indices/ID/primary/arena and advances revision; empty table is a no-op. |
| invariants | Pinned tuples may remain retained in arena; clear is not forced payload destruction. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Busy/revision overflow rejects before mutation; prepared valid cleanup requires no allocation. |
| cost | O(live rows/indices/memberships and payload release), no scan of old TupleId holes. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0087

[Lines 427–441](../../../../../src/storage/accounted_reference.cpp#L427); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedReferenceTable::Cursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain native iterators plus weak owner, revision and optional journal authority. |
| inputs / outputs | Table state initializes weak reference/revision; factory selects primary or member iterator mode. |
| invariants | valid() checks facade existence, aborted journal, conflicting writer and revision before iterator dereference. |
| ownership | Cursor allocation is accounted; table ownership remains weak. Runtime supplies any stronger read lease. |
| failure | Owner loss/aborted or stale revision raises invalid_cursor; conflicting journal raises storage_busy. |
| cost | Fixed cursor metadata; no snapshot/bucket vector. Bucket next_entry performs by-ID lookup unlike primary next_entry. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0088

[Lines 442–442](../../../../../src/storage/accounted_reference.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Cursor::Cursor(resource::
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a funded low-level ordered cursor. |
| inputs / outputs | Unique Data moves into a noncopyable token. |
| invariants | Factory already captured valid iteration bounds and revision. |
| ownership | Token owns its metadata; State remains weak. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0089

[Lines 443–445](../../../../../src/storage/accounted_reference.cpp#L443); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L443-L445:sha256:d16c97d7b2d9a7e162c4a9c97f89cc9a8bb11a9d31ae4c6677d00a64111e4c92
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0090

[Lines 446–454](../../../../../src/storage/accounted_reference.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> AccountedReferenceTable::Cursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a valid ordered primary/bucket iterator to one logical handle. |
| inputs / outputs | Returns next handle or nullopt; every call validates owner/journal/revision first. |
| invariants | End does not convert to a runtime reader lease; this is low-level borrowed traversal. |
| ownership | No payload copy or pin is created. |
| failure | Moved/expired/revised/aborted cursor rejects before iterator use. |
| cost | Fixed validity/iterator advance for handles; no deep value scan or allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0091

[Lines 455–464](../../../../../src/storage/accounted_reference.cpp#L455); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedReferenceTable::Cursor::Entry> AccountedReferenceTable::Cursor::next_entry()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance to one borrowed native tuple together with its logical handle. |
| inputs / outputs | Primary path dereferences its stable tuple pointer; bucket path resolves the member ID in by_id. |
| invariants | Lvalue cursor required; returned reference expires on mutation/table loss unless separately pinned. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | Invalid authority/revision rejects before traversal; missing bucket ID is an internal invariant failure. |
| cost | Primary fixed iterator work; bucket adds O(log rows) by-ID lookup and O(1) arena access. No owning row copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0092

[Lines 465–468](../../../../../src/storage/accounted_reference.cpp#L465); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Cursor AccountedReferenceTable::live()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open an ordinary ordered live-row iterator. |
| inputs / outputs | Unlocked table returns primary begin/end cursor at current revision. |
| invariants | No active journal; cursor itself does not prevent a later mutator. |
| ownership | One same-account Data allocation, weak table owner. |
| failure | Busy/allocation failure returns no cursor. |
| cost | Fixed iterator startup plus metadata allocation; no row/capacity/history scan. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0093

[Lines 469–474](../../../../../src/storage/accounted_reference.cpp#L469); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Cursor AccountedReferenceTable::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open an ordinary borrowed iterator for one projection key. |
| inputs / outputs | Index/key probe captures member begin/end or empty cursor. |
| invariants | Matching typed key and unlocked table required; later mutation invalidates revision. |
| ownership | Same-account cursor metadata, weak table owner; key argument is not retained as a replacement owning vector. |
| failure | Busy/unknown index/layout/allocation failure leaves source unchanged. |
| cost | Ordered index/key probe and one cursor owner; no O(matches) startup materialization. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0094

[Lines 475–479](../../../../../src/storage/accounted_reference.cpp#L475); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::live()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current tentative primary state under the active journal authority. |
| inputs / outputs | Open journal returns a weak table cursor sharing its Reader. |
| invariants | Abort marks Reader before undo; commit preserves authority only while facade/revision remain valid. |
| ownership | Cursor retains Reader but not complete table/journal inverse list. |
| failure | Closed journal or allocation failure yields no cursor. |
| cost | Fixed iterator startup and one accounted cursor owner; no state snapshot. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0095

[Lines 480–486](../../../../../src/storage/accounted_reference.cpp#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one tentative ordered bucket under journal authority. |
| inputs / outputs | Open journal, index and typed key return a member iterator or empty cursor. |
| invariants | No ordinary-cursor writer bypass: this exact Reader marks the permitted tentative state. |
| ownership | Accounted cursor plus shared Reader; borrowed row/index lifetimes remain revision-bound. |
| failure | Invalid journal/index/layout/allocation failure changes no state. |
| cost | Ordered index/key probe and cursor setup; later tuple entries add by-ID lookups. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0096

[Lines 487–493](../../../../../src/storage/accounted_reference.cpp#L487); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedReferenceTable::IndexKeyCursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture borrowed ordered secondary-key traversal state. |
| inputs / outputs | Weak State, revision and index bucket iterators describe the scan. |
| invariants | Each next checks live facade/unlocked state/revision before dereferencing a key. |
| ownership | One same-account metadata owner, no retained key copies or reader lock. |
| failure | Loss/mutation/drop of source invalidates further traversal. |
| cost | Fixed metadata, no population-sized key snapshot. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0097

[Lines 494–494](../../../../../src/storage/accounted_reference.cpp#L494); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::IndexKeyCursor::IndexKeyCursor(resource::
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a funded ordered key cursor. |
| inputs / outputs | Unique Data moves into the key token. |
| invariants | Factory established current index iterators/revision. |
| ownership | Token owns metadata only. |
| failure | Noexcept. |
| cost | Fixed-size scalar/handle work; no allocation or row traversal. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0098

[Lines 495–497](../../../../../src/storage/accounted_reference.cpp#L495); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L495-L497:sha256:c1326ed4ba6d43b0646864b4b4021ff0a9ee557692b6ce3ef30fed21d244c075
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_reference.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0099

[Lines 498–503](../../../../../src/storage/accounted_reference.cpp#L498); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedReferenceTable::IndexKeyCursor::Entry> AccountedReferenceTable::IndexKeyCursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the next borrowed key and exact bucket degree. |
| inputs / outputs | Lvalue cursor yields key reference/member count or nullopt. |
| invariants | Validity checks precede iterator access; degree is maintained set size, not a row scan. |
| ownership | Key borrows live index storage and must not outlive mutation/drop/owner loss. |
| failure | Invalid cursor/busy/revision failure occurs before dereference. |
| cost | Fixed iterator/size work and weak-owner lock; no deep key copy/allocation. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0100

[Lines 504–507](../../../../../src/storage/accounted_reference.cpp#L504); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable::IndexKeyCursor AccountedReferenceTable::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open an ordinary borrowed key scan for one installed index. |
| inputs / outputs | Unlocked table and IndexId yield current bucket iterators/revision. |
| invariants | No journal-authorized key-scan factory is exposed by this ordered table interface. |
| ownership | Same-account Data allocation, weak State owner. |
| failure | Busy/unknown index/allocation failure returns no cursor. |
| cost | O(log indices) index probe plus cursor setup; no live-key materialization. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0101

[Lines 508–513](../../../../../src/storage/accounted_reference.cpp#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedReferenceTable::snapshot()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current low-level table rows into independent native output. |
| inputs / outputs | Returns primary-ordered owning tuples, including tentative installed rows if called internally during a journal. |
| invariants | This is an explicit inspection/export operation, not a checkpoint or read-isolation authority. |
| ownership | Output vector/deep row payloads retain original account and survive table mutations/destruction. |
| failure | Allocation failure destroys partial output without changing the table. |
| cost | O(live rows and deep bytes), output-sensitive native allocation/copy. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0102

[Lines 514–521](../../../../../src/storage/accounted_reference.cpp#L514); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable AccountedReferenceTable::snapshot_copy()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a separate same-account table preserving sparse logical IDs and revision. |
| inputs / outputs | Quiescent source rows/index descriptors populate a new table/arena owner; logical IDs and high-water marks are restored. |
| invariants | No iteration over missing ID holes. New storage ownership makes old handles foreign; copied tuples do not preserve source arena addresses/generations. |
| ownership | All native containers, detached nodes and tuple payloads retain the layout original account and attribution. |
| failure | Failure destroys unpublished copy and leaves source unchanged. |
| cost | Actual live row copies and per-index rebuild/projection/member costs; memory overlaps source under the same account cap. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0103

[Lines 522–541](../../../../../src/storage/accounted_reference.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedReferenceTable::check_invariants()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ordered primary/ID/arena/index populations and native account consistency. |
| inputs / outputs | Walks live rows/index keys/memberships and arena/account diagnostics, rejecting inconsistency. |
| invariants | Diagnostic only; not a cheap row predicate or a repairing operation. Tentative state must remain internally consistent. |
| ownership | Borrows the valid table state; external synchronization and the runtime epoch/read lease remain caller obligations. |
| failure | Fixed native contract failures report bad state; no scratch expected-state table is created. |
| cost | Arena high-water/account-ledger scans plus live-row and membership ordered probes/typed field comparisons; not constant-time. |
| Design | [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0104

[Lines 542–542](../../../../../src/storage/accounted_reference.cpp#L542); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L542-L542:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_reference.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
