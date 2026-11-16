# `src/storage/accounted_indexed.cpp` — block usage map

[Source](../../../../../src/storage/accounted_indexed.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `b8e87f0af2a87dd9f52ac104843f35cde33b68931fb85b0d367bdb032ffd9e44`. 825 lines partitioned into 97 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/storage/accounted_indexed.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. | source comment (unverified): // Source-private definition with namespace linkage, like the existing S02 · [reviewed contract](#b0001) |
| [B0002 · 17–23](../../../../../src/storage/accounted_indexed.cpp#L17) | Type/record definition: struct AccountedIndexedJournalReader | source comment (unverified): // Source-private definition with namespace linkage, like the existing S02 · [reviewed contract](#b0002) |
| [B0003 · 24–37](../../../../../src/storage/accounted_indexed.cpp#L24) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0003) |
| [B0004 · 38–40](../../../../../src/storage/accounted_indexed.cpp#L38) | Callable definition: void contract(bool value, const char* /*message*/) | calls IndexFailure; source comment (unverified): /*message*/ · [reviewed contract](#b0004) |
| [B0005 · 41–44](../../../../../src/storage/accounted_indexed.cpp#L41) | Callable definition: void room(std::size_t current, std::size_t extra, std::size_t maximum) | calls IndexFailure · [reviewed contract](#b0005) |
| [B0006 · 45–48](../../../../../src/storage/accounted_indexed.cpp#L45) | Callable definition: void counter_room(std::uint64_t current, std::uint64_t extra = 1) | calls max, IndexFailure · [reviewed contract](#b0006) |
| [B0007 · 49–54](../../../../../src/storage/accounted_indexed.cpp#L49) | Callable definition: std::uint64_t work_product(std::size_t count, std::uint64_t cost) | calls max, IndexFailure; returns value * cost · [reviewed contract](#b0007) |
| [B0008 · 55–58](../../../../../src/storage/accounted_indexed.cpp#L55) | Callable definition: void start(IndexWorkAllowance& work) | calls fixed_diagnostics, IndexFailure, admit · [reviewed contract](#b0008) |
| [B0009 · 59–65](../../../../../src/storage/accounted_indexed.cpp#L59) | Callable definition: template &lt;class T&gt; void reserve_records(AccountedVector&lt;T&gt;& records, std::size_t count, IndexWorkAllowance& work) | calls max_size, IndexFailure, admit, work_product; growth reserve · [reviewed contract](#b0009) |
| [B0010 · 66–93](../../../../../src/storage/accounted_indexed.cpp#L66) | controls preprocessing; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 94–98](../../../../../src/storage/accounted_indexed.cpp#L94) | Callable definition: State(const MemoryAccount& query, StorageOwnerId identity, RelationId value, AccountedLayout schema, IndexedLimits configuration)… | calls account, owner, relation, layout · [reviewed contract](#b0011) |
| [B0012 · 99–101](../../../../../src/storage/accounted_indexed.cpp#L99) | Callable definition: template&lt;class T&gt; AccountedVector&lt;T&gt; vector(MemoryPurpose purpose = MemoryPurpose::scratch) const | calls ; returns AccountedVector&lt;T&gt;(MemoryAllocator&lt;T&gt;(account, purpose, tag)) · [reviewed contract](#b0012) |
| [B0013 · 102–102](../../../../../src/storage/accounted_indexed.cpp#L102) | Callable definition: MemoryAttribution output_tag() const noexcept | calls ; returns {resource::MemoryOwnerKind::output, owner.value} · [reviewed contract](#b0013) |
| [B0014 · 103–105](../../../../../src/storage/accounted_indexed.cpp#L103) | Callable definition: template&lt;class T&gt; AccountedVector&lt;T&gt; output() const | calls output_tag; returns AccountedVector&lt;T&gt;(MemoryAllocator&lt;T&gt;(account, MemoryPurpose::output_buffer, output_tag())) · [reviewed contract](#b0014) |
| [B0015 · 106–111](../../../../../src/storage/accounted_indexed.cpp#L106) | Callable definition: ~State() | calls first_resident, destroy_indexed_node; 2 loop sites; source comment (unverified): // Destroy nodes while all actual hook owners are still alive. Neither · [reviewed contract](#b0015) |
| [B0016 · 112–115](../../../../../src/storage/accounted_indexed.cpp#L112) | Callable definition: void input(const AccountedTuple& tuple) const | calls same_token, layout, IndexFailure · [reviewed contract](#b0016) |
| [B0017 · 116–119](../../../../../src/storage/accounted_indexed.cpp#L116) | Callable definition: void owned(TupleHandle handle) const | calls IndexFailure · [reviewed contract](#b0017) |
| [B0018 · 120–120](../../../../../src/storage/accounted_indexed.cpp#L120) | Callable definition: void mutable_revision() const | calls counter_room · [reviewed contract](#b0018) |
| [B0019 · 121–123](../../../../../src/storage/accounted_indexed.cpp#L121) | Callable definition: void unlocked() const | calls IndexFailure · [reviewed contract](#b0019) |
| [B0020 · 124–124](../../../../../src/storage/accounted_indexed.cpp#L124) | Callable definition: TupleHandle handle(const AccountedIndexedRow& row) const noexcept | calls ; returns {owner, relation, row.id} · [reviewed contract](#b0020) |
| [B0021 · 125–131](../../../../../src/storage/accounted_indexed.cpp#L125) | Callable definition: std::uint64_t transform_hash(std::uint64_t value) const noexcept | calls ; returns 0; value & ~std::uint64_t{0xffff} · [reviewed contract](#b0021) |
| [B0022 · 132–134](../../../../../src/storage/accounted_indexed.cpp#L132) | Callable definition: std::uint64_t hash(const AccountedTuple& value, IndexWorkAllowance& work) const | calls transform_hash, detail::accounted_admitted_hash; returns transform_hash(detail::accounted_admitted_hash(value, work)) · [reviewed contract](#b0022) |
| [B0023 · 135–135](../../../../../src/storage/accounted_indexed.cpp#L135) | Callable definition: std::uint64_t diagnostic_hash(const AccountedTuple& value) const | calls transform_hash, hash; returns transform_hash(value.hash()) · [reviewed contract](#b0023) |
| [B0024 · 136–141](../../../../../src/storage/accounted_indexed.cpp#L136) | Callable definition: AccountedIndexedRow* row(TupleHandle value, IndexWorkAllowance& work) const | calls owned, find; returns by_id.find(value.tuple.value, \[&\](const AccountedIndexedRow& candidate, IndexWorkAllowance&) {; can… · [reviewed contract](#b0024) |
| [B0025 · 142–147](../../../../../src/storage/accounted_indexed.cpp#L142) | Callable definition: AccountedIndexedRow* row(const AccountedTuple& value, IndexWorkAllowance& work) const | calls input, hash, find, detail::accounted_admitted_equal; returns primary.find(value_hash, \[&\](const AccountedIndexedRow& candidate, IndexWorkAllowance& allowance) {… · [reviewed contract](#b0025) |
| [B0026 · 148–152](../../../../../src/storage/accounted_indexed.cpp#L148) | Callable definition: AccountedIndexedIndex* maybe_index(IndexId id, IndexWorkAllowance& work) const | calls find; returns indices.find(id.value, \[&\](const AccountedIndexedIndex& candidate, IndexWorkAllowance&) {; candidat… · [reviewed contract](#b0026) |
| [B0027 · 153–157](../../../../../src/storage/accounted_indexed.cpp#L153) | Callable definition: AccountedIndexedIndex& index(IndexId id, IndexWorkAllowance& work) const | calls maybe_index, IndexFailure; returns *found · [reviewed contract](#b0027) |
| [B0028 · 158–165](../../../../../src/storage/accounted_indexed.cpp#L158) | Callable definition: AccountedIndexedKey* key(AccountedIndexedIndex& index, const AccountedTuple& value, IndexWorkAllowance& work) const | calls target, same_token, layout, IndexFailure; returns index.keys.find(value_hash, \[&\](const AccountedIndexedKey& candidate, IndexWorkAllowance& allowance… · [reviewed contract](#b0028) |
| [B0029 · 166–169](../../../../../src/storage/accounted_indexed.cpp#L166) | Callable definition: std::size_t slot_room(std::size_t pending = 0) const | calls room; returns limits.directory_slots - directory_slots - pending · [reviewed contract](#b0029) |
| [B0030 · 170–173](../../../../../src/storage/accounted_indexed.cpp#L170) | Callable definition: void arena_insert_room() const | calls statistics, room · [reviewed contract](#b0030) |
| [B0031 · 174–180](../../../../../src/storage/accounted_indexed.cpp#L174) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 181–181](../../../../../src/storage/accounted_indexed.cpp#L181) | Callable definition: MemoryAccount AccountedIndexedTable::account_for(const AccountedLayout& layout) | calls query_account; returns layout.query_account() · [reviewed contract](#b0032) |
| [B0033 · 182–182](../../../../../src/storage/accounted_indexed.cpp#L182) | Callable definition: void AccountedIndexedTable::classify(AccountedTuple& tuple, AllocationLifetime lifetime) noexcept | calls set_lifetime · [reviewed contract](#b0033) |
| [B0034 · 183–189](../../../../../src/storage/accounted_indexed.cpp#L183) | Callable definition: AccountedIndexedTable::AccountedIndexedTable(RelationId relation, AccountedLayout layout, IndexedLimits limits) | calls IndexFailure, account_for, detail::try_new_storage_owner, std::move; growth make_accounted_shared · [reviewed contract](#b0034) |
| [B0035 · 190–190](../../../../../src/storage/accounted_indexed.cpp#L190) | Callable definition: AccountedIndexedTable::~AccountedIndexedTable() | calls  · [reviewed contract](#b0035) |
| [B0036 · 191–191](../../../../../src/storage/accounted_indexed.cpp#L191) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0036) |
| [B0037 · 192–194](../../../../../src/storage/accounted_indexed.cpp#L192) | Callable definition: AccountedIndexedTable& AccountedIndexedTable::operator=(AccountedIndexedTable&& other) noexcept | calls ; returns *this · [reviewed contract](#b0037) |
| [B0038 · 195–198](../../../../../src/storage/accounted_indexed.cpp#L195) | Callable definition: AccountedIndexedTable::State& AccountedIndexedTable::state() const | calls IndexFailure; returns *state_ · [reviewed contract](#b0038) |
| [B0039 · 199–199](../../../../../src/storage/accounted_indexed.cpp#L199) | Callable definition: StorageOwnerId AccountedIndexedTable::owner() const | calls state; returns state().owner · [reviewed contract](#b0039) |
| [B0040 · 200–200](../../../../../src/storage/accounted_indexed.cpp#L200) | Callable definition: RelationId AccountedIndexedTable::relation() const | calls state; returns state().relation · [reviewed contract](#b0040) |
| [B0041 · 201–201](../../../../../src/storage/accounted_indexed.cpp#L201) | Callable definition: const AccountedLayout& AccountedIndexedTable::layout() const & | calls state; returns state().layout · [reviewed contract](#b0041) |
| [B0042 · 202–202](../../../../../src/storage/accounted_indexed.cpp#L202) | Callable definition: const IndexedLimits& AccountedIndexedTable::limits() const & | calls state; returns state().limits · [reviewed contract](#b0042) |
| [B0043 · 203–203](../../../../../src/storage/accounted_indexed.cpp#L203) | Callable definition: std::size_t AccountedIndexedTable::size() const | calls state, size; returns state().primary.size() · [reviewed contract](#b0043) |
| [B0044 · 204–204](../../../../../src/storage/accounted_indexed.cpp#L204) | Callable definition: std::uint64_t AccountedIndexedTable::revision() const | calls state; returns state().revision · [reviewed contract](#b0044) |
| [B0045 · 205–205](../../../../../src/storage/accounted_indexed.cpp#L205) | Callable definition: ArenaStatistics AccountedIndexedTable::arena_statistics() const | calls state, statistics; returns state().arena.statistics() · [reviewed contract](#b0045) |
| [B0046 · 206–212](../../../../../src/storage/accounted_indexed.cpp#L206) | Callable definition: IndexedStatistics AccountedIndexedTable::statistics() const | calls state, size, statistics; returns {s.primary.size(), s.indices.size(), s.key_nodes, s.live_key_nodes, · [reviewed contract](#b0046) |
| [B0047 · 213–214](../../../../../src/storage/accounted_indexed.cpp#L213) | Explanatory comments or spacing. | source comment (unverified): // Explicit report: table/arena attribution scans the account ledger, arena · [reviewed contract](#b0047) |
| [B0048 · 215–226](../../../../../src/storage/accounted_indexed.cpp#L215) | Callable definition: AccountedIndexedMemoryStatistics AccountedIndexedTable::memory_statistics() const | calls state, statistics, statistics_for, memory_statistics; returns result; 2 loop sites; source comment (unverified): // Explicit report: table/arena attribution scans the account ledger, arena · [reviewed contract](#b0048) |
| [B0049 · 227–227](../../../../../src/storage/accounted_indexed.cpp#L227) | Explanatory comments or spacing. |  |
| [B0050 · 228–230](../../../../../src/storage/accounted_indexed.cpp#L228) | Callable definition: InsertResult AccountedIndexedTable::insert(const AccountedTuple& tuple, IndexWorkAllowance& work) | calls insert_impl; returns insert_impl(state_, tuple, work, nullptr); growth insert · [reviewed contract](#b0050) |
| [B0051 · 231–337](../../../../../src/storage/accounted_indexed.cpp#L231) | Callable definition: InsertResult AccountedIndexedTable::insert_impl(const std::shared_ptr&lt;State&gt;& owner, const AccountedTuple& tuple, IndexWorkAllowa… | calls IndexFailure, unlocked, start, input; returns detail::accounted_admitted_equal(*candidate.tuple, tuple, grant); {false, s.handle(*found)}; growth emplace, insert, push_back; 3 loop sites; source comment (unverified): // A new key's cached hash is set while private; publication never hashes. · [reviewed contract](#b0051) |
| [B0052 · 338–341](../../../../../src/storage/accounted_indexed.cpp#L338) | Explanatory comments or spacing. | source comment (unverified): // Low-level probes may see tentative rows. Callers supply any read lease · [reviewed contract](#b0052) |
| [B0053 · 342–346](../../../../../src/storage/accounted_indexed.cpp#L342) | Callable definition: std::optional&lt;TupleHandle&gt; AccountedIndexedTable::find(const AccountedTuple& tuple, IndexWorkAllowance& work) const | calls state, start, row, handle; returns {}; s.handle(*row); source comment (unverified): // Low-level probes may see tentative rows. Callers supply any read lease · [reviewed contract](#b0053) |
| [B0054 · 347–350](../../../../../src/storage/accounted_indexed.cpp#L347) | Callable definition: const AccountedTuple* AccountedIndexedTable::get(TupleHandle handle, IndexWorkAllowance& work) const & | calls state, start, row; returns row == nullptr ? nullptr : row-&gt;tuple · [reviewed contract](#b0054) |
| [B0055 · 351–356](../../../../../src/storage/accounted_indexed.cpp#L351) | Callable definition: AccountedTupleArena::Pin AccountedIndexedTable::pin(TupleHandle handle, IndexWorkAllowance& work) const | calls state, start, row, IndexFailure; returns s.arena.pin(row-&gt;allocation) · [reviewed contract](#b0055) |
| [B0056 · 357–357](../../../../../src/storage/accounted_indexed.cpp#L357) | Explanatory comments or spacing. |  |
| [B0057 · 358–369](../../../../../src/storage/accounted_indexed.cpp#L358) | Callable definition: void AccountedIndexedTable::State::prepare_erase(const AccountedIndexedRow& row, IndexWorkAllowance& work) const | calls start, admit, detail::accounted_admit_tuple_copy, first; 1 loop sites; source comment (unverified): // Conservative retirement allowance. · [reviewed contract](#b0057) |
| [B0058 · 370–379](../../../../../src/storage/accounted_indexed.cpp#L370) | Callable definition: void AccountedIndexedTable::State::erase_prepaid(AccountedIndexedRow& row) noexcept | calls first, destroy_indexed_node, size, erase; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 380–383](../../../../../src/storage/accounted_indexed.cpp#L380) | Callable definition: void AccountedIndexedTable::State::erase_one(AccountedIndexedRow& row, IndexWorkAllowance& work) | calls mutable_revision, counter_room, prepare_erase, erase_prepaid · [reviewed contract](#b0059) |
| [B0060 · 384–388](../../../../../src/storage/accounted_indexed.cpp#L384) | Callable definition: bool AccountedIndexedTable::erase(const AccountedTuple& tuple, IndexWorkAllowance& work) | calls state, unlocked, start, row; returns false; true · [reviewed contract](#b0060) |
| [B0061 · 389–393](../../../../../src/storage/accounted_indexed.cpp#L389) | Callable definition: bool AccountedIndexedTable::erase(TupleHandle handle, IndexWorkAllowance& work) | calls state, unlocked, start, row; returns false; true · [reviewed contract](#b0061) |
| [B0062 · 394–394](../../../../../src/storage/accounted_indexed.cpp#L394) | Explanatory comments or spacing. |  |
| [B0063 · 395–451](../../../../../src/storage/accounted_indexed.cpp#L395) | Callable definition: IndexId AccountedIndexedTable::add_index(AccountedProjection projection, IndexWorkAllowance& work) | calls state, unlocked, start, same_token; returns existing-&gt;id; detail::accounted_admitted_equal(candidate.tuple, projected, grant); growth push_back; 3 loop sites; source comment (unverified): // The complete index and all bucket links are private. Only these row links · [reviewed contract](#b0063) |
| [B0064 · 452–452](../../../../../src/storage/accounted_indexed.cpp#L452) | Explanatory comments or spacing. |  |
| [B0065 · 453–473](../../../../../src/storage/accounted_indexed.cpp#L453) | Callable definition: bool AccountedIndexedTable::drop_index(IndexId id, IndexWorkAllowance& work) | calls state, unlocked, start, maybe_index; returns false; true; 2 loop sites · [reviewed contract](#b0065) |
| [B0066 · 474–481](../../../../../src/storage/accounted_indexed.cpp#L474) | Callable definition: AccountedVector&lt;IndexId&gt; AccountedIndexedTable::indices(IndexWorkAllowance& work) const | calls state, start, reserve_records, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 482–484](../../../../../src/storage/accounted_indexed.cpp#L482) | Callable definition: AccountedProjection AccountedIndexedTable::projection(IndexId id, IndexWorkAllowance& work) const | calls state, start, index; returns s.index(id, work).projection · [reviewed contract](#b0067) |
| [B0068 · 485–487](../../../../../src/storage/accounted_indexed.cpp#L485) | Callable definition: std::size_t AccountedIndexedTable::key_count(IndexId id, IndexWorkAllowance& work) const | calls state, start, index, size; returns s.index(id, work).live_keys.size() · [reviewed contract](#b0068) |
| [B0069 · 488–495](../../../../../src/storage/accounted_indexed.cpp#L488) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedIndexedTable::keys(IndexId id, IndexWorkAllowance& work) const | calls state, start, index, reserve_records; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0069) |
| [B0070 · 496–505](../../../../../src/storage/accounted_indexed.cpp#L496) | Callable definition: AccountedVector&lt;TupleHandle&gt; AccountedIndexedTable::bucket(IndexId id, const AccountedTuple& value, IndexWorkAllowance& work) con… | calls state, start, index, key; returns result; result; growth push_back; 1 loop sites · [reviewed contract](#b0070) |
| [B0071 · 506–516](../../../../../src/storage/accounted_indexed.cpp#L506) | Callable definition: std::size_t AccountedIndexedTable::erase_key(IndexId id, const AccountedTuple& value, IndexWorkAllowance& work) | calls state, unlocked, start, index; returns 0; rows.size(); growth push_back; 2 loop sites · [reviewed contract](#b0071) |
| [B0072 · 517–526](../../../../../src/storage/accounted_indexed.cpp#L517) | Callable definition: void AccountedIndexedTable::clear(IndexWorkAllowance& work) | calls state, unlocked, start, size; 2 loop sites · [reviewed contract](#b0072) |
| [B0073 · 527–534](../../../../../src/storage/accounted_indexed.cpp#L527) | Callable definition: AccountedVector&lt;AccountedTuple&gt; AccountedIndexedTable::snapshot(IndexWorkAllowance& work) const | calls state, start, reserve_records, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0073) |
| [B0074 · 535–535](../../../../../src/storage/accounted_indexed.cpp#L535) | Explanatory comments or spacing. |  |
| [B0075 · 536–544](../../../../../src/storage/accounted_indexed.cpp#L536) | Type/record definition: struct AccountedIndexedTable::Cursor::Data |  · [reviewed contract](#b0075) |
| [B0076 · 545–545](../../../../../src/storage/accounted_indexed.cpp#L545) | Callable definition: AccountedIndexedTable::Cursor::Cursor(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0076) |
| [B0077 · 546–548](../../../../../src/storage/accounted_indexed.cpp#L546) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0077) |
| [B0078 · 549–572](../../../../../src/storage/accounted_indexed.cpp#L549) | Callable definition: std::optional&lt;AccountedIndexedTable::Cursor::Entry&gt; AccountedIndexedTable::Cursor::next(IndexWorkAllowance& work) & | calls IndexFailure, lock, get, unlocked; returns {}; {}; source comment (unverified): // A denial leaves both the cursor position and owner unchanged. · [reviewed contract](#b0078) |
| [B0079 · 573–579](../../../../../src/storage/accounted_indexed.cpp#L573) | Callable definition: AccountedIndexedTable::Cursor AccountedIndexedTable::live(IndexWorkAllowance& work) const | calls state, unlocked, start, admit; returns Cursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0079) |
| [B0080 · 580–587](../../../../../src/storage/accounted_indexed.cpp#L580) | Callable definition: AccountedIndexedTable::Cursor AccountedIndexedTable::bucket_cursor(IndexId id, const AccountedTuple& value, IndexWorkAllowance& w… | calls state, unlocked, start, index; returns Cursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0080) |
| [B0081 · 588–594](../../../../../src/storage/accounted_indexed.cpp#L588) | Type/record definition: struct AccountedIndexedTable::IndexKeyCursor::Data |  · [reviewed contract](#b0081) |
| [B0082 · 595–595](../../../../../src/storage/accounted_indexed.cpp#L595) | Callable definition: AccountedIndexedTable::IndexKeyCursor::IndexKeyCursor(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0082) |
| [B0083 · 596–598](../../../../../src/storage/accounted_indexed.cpp#L596) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0083) |
| [B0084 · 599–615](../../../../../src/storage/accounted_indexed.cpp#L599) | Callable definition: std::optional&lt;AccountedIndexedTable::IndexKeyCursor::Entry&gt; AccountedIndexedTable::IndexKeyCursor::next(IndexWorkAllowance& work)… | calls IndexFailure, lock, get, unlocked; returns {}; Entry{key-&gt;tuple, key-&gt;members.size()} · [reviewed contract](#b0084) |
| [B0085 · 616–622](../../../../../src/storage/accounted_indexed.cpp#L616) | Callable definition: AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::index_keys(IndexId id, IndexWorkAllowance& work) const | calls state, unlocked, start, index; returns IndexKeyCursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0085) |
| [B0086 · 623–623](../../../../../src/storage/accounted_indexed.cpp#L623) | Explanatory comments or spacing. |  |
| [B0087 · 624–631](../../../../../src/storage/accounted_indexed.cpp#L624) | Callable definition: AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::live() const | calls IndexFailure, active, start, admit; returns Cursor(std::move(cursor)); growth make_accounted_unique · [reviewed contract](#b0087) |
| [B0088 · 632–641](../../../../../src/storage/accounted_indexed.cpp#L632) | Callable definition: AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::bucket_cursor(IndexId id, const AccountedTuple& value) const | calls IndexFailure, active, start, index; returns Cursor(std::move(cursor)); growth make_accounted_unique · [reviewed contract](#b0088) |
| [B0089 · 642–649](../../../../../src/storage/accounted_indexed.cpp#L642) | Callable definition: AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::Journal::index_keys(IndexId id) const | calls IndexFailure, active, start, index; returns IndexKeyCursor(std::move(cursor)); growth make_accounted_unique · [reviewed contract](#b0089) |
| [B0090 · 650–650](../../../../../src/storage/accounted_indexed.cpp#L650) | Explanatory comments or spacing. |  |
| [B0091 · 651–694](../../../../../src/storage/accounted_indexed.cpp#L651) | Callable definition: AccountedIndexedTable AccountedIndexedTable::snapshot_copy(IndexWorkAllowance& work) const | calls state, unlocked, start, admit; returns result; growth insert, push_back; 5 loop sites; source comment (unverified): // This is a private checked builder, not a public raw-ID constructor. · [reviewed contract](#b0091) |
| [B0092 · 695–695](../../../../../src/storage/accounted_indexed.cpp#L695) | Explanatory comments or spacing. |  |
| [B0093 · 696–802](../../../../../src/storage/accounted_indexed.cpp#L696) | Callable definition: void AccountedIndexedTable::check_invariants() const | calls state, check_invariants_noalloc, check_invariants, source; returns false; false; 16 loop sites · [reviewed contract](#b0093) |
| [B0094 · 803–804](../../../../../src/storage/accounted_indexed.cpp#L803) | controls preprocessing. |  · [reviewed contract](#b0094) |
| [B0095 · 805–814](../../../../../src/storage/accounted_indexed.cpp#L805) | Callable definition: void detail::AccountedIndexedTesting::collisions(AccountedIndexedTable& table, AccountedCollisionMode mode) | calls state, unlocked, contract, size · [reviewed contract](#b0095) |
| [B0096 · 815–822](../../../../../src/storage/accounted_indexed.cpp#L815) | Callable definition: void detail::AccountedIndexedTesting::exhaust(AccountedIndexedTable& table, Exhausted which) | calls state, unlocked, max · [reviewed contract](#b0096) |
| [B0097 · 823–825](../../../../../src/storage/accounted_indexed.cpp#L823) | controls preprocessing. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0097) |

## B0001

[Lines 1–16](../../../../../src/storage/accounted_indexed.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:88dce7933cc1e83e93d598f2be03eb3681a213cc0ad1f939f57c13383d45217c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp: imports \`"crown/storage/accounted_indexed.hpp"\`, \`"accounted_indexed_nodes.hpp"\`, \`"accounted_index_scalar_work.hpp"\`, \`"owner.hpp"\`, \`"accounted_indexed_testing.hpp"\`, \`&lt;algorithm&gt;\`, \`&lt;exception&gt;\`, \`&lt;limits&gt;\`, \`&lt;utility&gt;\` for compilation; opens/branches compile-time guard \`#ifdef CROWN_ACCOUNTED_INDEXED_TESTING\`; closes the matching compile-time guard; opens namespace \`crown::storage\`. Source comment: Source-private definition with namespace linkage, like the existing S02 reader. Externally linked nested Data types must not embed an anonymous type. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. The source note says: Source-private definition with namespace linkage, like the existing S02 reader. Externally linked nested Data types must not embed an anonymous type. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 17–23](../../../../../src/storage/accounted_indexed.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedJournalReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain journal phase authority and the exact composed native work grant. |
| inputs / outputs | An owning AccountedIndexWork produces active/committed/aborted phase state shared with journal cursors. |
| invariants | Commit keeps authority valid at the unchanged revision; rollback marks it aborted before any inverse pointer restoration. |
| ownership | Original-account shared reader retains the same allowance/control, not a copied budget or table owner. |
| failure | Reader construction failure installs no journal authority. |
| cost | Fixed phase/owner metadata and one accounted shared control; resumed operations do not allocate a new allowance. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0003

[Lines 24–37](../../../../../src/storage/accounted_indexed.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L37:sha256:17768ad7ec6189d59bafc78125bddaa0b34d951b3e74a609cb092ac768ded626
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp: opens anonymous namespace with translation-unit-local linkage; imports or aliases \`detail::AccountedIndexedIndex\`, \`resource::MemoryAccount\`, \`resource::MemoryAllocator\`, \`resource::MemoryAttribution\`, \`resource::MemoryPurpose\`, \`resource::AllocationLifetime\`, \`detail::destroy_indexed_node\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 38–40](../../../../../src/storage/accounted_indexed.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contract(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a violated internal indexed-table invariant using fixed native diagnostics. |
| inputs / outputs | Boolean predicate returns normally or raises IndexFailure(contract). |
| invariants | The descriptive source argument is intentionally not dynamically formatted on the native path. |
| ownership | Borrows the predicate; no error-string ownership on success. |
| failure | Fixed IndexFailure on false; it does not repair state. |
| cost | O(1) branch; no ordinary-new allocation for diagnostic message construction. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0005

[Lines 41–44](../../../../../src/storage/accounted_indexed.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void room(std::size_t current,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a component population increment without overflow-prone addition. |
| inputs / outputs | Current, extra and maximum are checked by subtraction; no mutation or reservation is performed. |
| invariants | current must not exceed maximum and extra must fit the remainder; zero is a real finite limit. |
| ownership | Inline count values only. |
| failure | Raises IndexFailure(capacity) before publication. |
| cost | O(1) scalar comparisons/subtraction; allocator-byte admission remains separate. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0006

[Lines 45–48](../../../../../src/storage/accounted_indexed.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counter_room(std::uint64_t current,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove room in an exact action/revision/identity counter. |
| inputs / outputs | Current counter and optional increment reject a uint64 overflow before the later addition. |
| invariants | Identity and action counters cannot wrap into an earlier valid value. |
| ownership | No counter is changed by this helper. |
| failure | Raises IndexFailure(overflow). |
| cost | O(1), allocation-free success. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0007

[Lines 49–54](../../../../../src/storage/accounted_indexed.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t work_product(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an exact count-times-cost native work amount. |
| inputs / outputs | size_t population and uint64 per-item charge produce a checked uint64 product. |
| invariants | Supporting scalar-work code asserts size_t width is at most64; zero cost returns zero without division. |
| ownership | Inline arithmetic only. |
| failure | Raises IndexFailure(overflow) before work admission. |
| cost | O(1), no traversal or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0008

[Lines 55–58](../../../../../src/storage/accounted_indexed.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void start(IndexWorkAllowance& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one indexed operation/advance with fixed native diagnostic policy. |
| inputs / outputs | Allowance must use fixed diagnostics, then spends one structural step. |
| invariants | End detection also uses this step; invalid owner/revision checks may reject before reaching start. |
| ownership | The caller supplies the finite native allowance; operations debit it and never refill or refund spent work. |
| failure | Wrong diagnostic mode raises contract; depleted allowance raises the native work failure without advancing a cursor. |
| cost | Fixed policy check plus one admission; this is not a whole-operation constant-time assertion. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0009

[Lines 59–65](../../../../../src/storage/accounted_indexed.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reserve_records(AccountedVector<T>& records,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a native metadata/output vector capacity before it can be used. |
| inputs / outputs | Original-account vector, requested count and allowance admit count times pointer-sized words, then reserve. |
| invariants | Size overflow and work admission precede allocation; reservation can conservatively exceed newly initialized slots. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Fixed arithmetic computes and debits count*ceil(sizeof(T)/sizeof(void*)) pointer units even when capacity is already sufficient. reserve then does no allocation if it fits, otherwise allocates capacity and relocates existing elements according to concrete T. The helper does not clone tuple payload or materialize an owning Row. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0010

[Lines 66–93](../../../../../src/storage/accounted_indexed.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedTable::State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own live indexed rows, secondary memberships, finite capacities and journal authority. |
| inputs / outputs | One relation/layout, account, identity and IndexedLimits initialize arena and three empty intrusive directories. |
| invariants | Cached hashes, row/ID resident order, per-key live lists and member hooks must agree. Limits include retained undo-owned nodes; byte quota and work bounds are separate. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | An unpublished State releases constructed members; ordinary use validates owner/layout and exclusive journal state at its entry boundaries. |
| cost | State/control metadata is fixed; rows/keys/members/directories grow explicitly with admitted populations, not logical ID high-water. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0011

[Lines 94–98](../../../../../src/storage/accounted_indexed.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(const MemoryAccount& query,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the original-account arena and empty indexed directories. |
| inputs / outputs | Account, storage owner, relation, schema and limits construct State without resident rows or indices. |
| invariants | All three directory allocators carry this table attribution; no per-owner registry is introduced. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Constructor failure destroys already constructed members and publishes no facade. |
| cost | Fixed state/arena control cost; directory payload capacity is deferred until growth. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0012

[Lines 99–101](../../../../../src/storage/accounted_indexed.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> AccountedVector<T> vector(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty table-attributed native scratch/undo container. |
| inputs / outputs | Optional memory purpose produces a vector allocator using the original account and table tag. |
| invariants | Empty vector creation does not reserve payload capacity. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Later reserve/allocation can fail; this helper adds no recovery layer. |
| cost | Fixed allocator-handle retention; no row scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0013

[Lines 102–102](../../../../../src/storage/accounted_indexed.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAttribution output_tag() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify caller-retained table output separately from table state. |
| inputs / outputs | Returns output owner-kind with this storage owner ID. |
| invariants | Output attribution is distinct from storage-table attribution but shares the query account. |
| ownership | Copies two inline identifiers. |
| failure | Noexcept. |
| cost | O(1), no allocation or owner registry. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0014

[Lines 103–105](../../../../../src/storage/accounted_indexed.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> AccountedVector<T> output() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an empty owning output collection under the original account. |
| inputs / outputs | Returns vector using output_buffer purpose and output_tag attribution. |
| invariants | Only explicit collection APIs call this; lazy cursors do not materialize these vectors. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Actual later reserve/payload copy may fail while table state remains unchanged. |
| cost | Fixed empty container setup; collection population costs belong to its caller. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0015

[Lines 106–111](../../../../../src/storage/accounted_indexed.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~State() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy resident row/index nodes while their hook owners still exist. |
| inputs / outputs | Final State release destroys all live primary rows, then all resident index trees. |
| invariants | Row destruction unlinks its memberships before index/key owners disappear. Retained journal state cannot outlive an active journal owner incorrectly. |
| ownership | Native raw node ownership ends through each embedded allocator; the arena releases remaining payloads afterward. |
| failure | Destruction is nonallocating; impossible link/account invariant failures terminate. |
| cost | O(resident row/index/key/member destruction), not a scan of directory capacity or logical ID high-water; final arena teardown has its own slot-high-water cost. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0016

[Lines 112–115](../../../../../src/storage/accounted_indexed.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input(const AccountedTuple& tuple) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require this table immutable row-layout token. |
| inputs / outputs | Accounted tuple with another token is rejected before primary probing. |
| invariants | Native tuples were schema-validated when constructed; this is an identity check, not full scalar revalidation. |
| ownership | Borrows tuple/layout. |
| failure | Raises IndexFailure(layout_mismatch). |
| cost | O(1) token comparison; no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0017

[Lines 116–119](../../../../../src/storage/accounted_indexed.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(TupleHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a foreign table/relation handle before logical-ID lookup. |
| inputs / outputs | Owner and relation must match this State; ID presence is checked separately. |
| invariants | Same numeric tuple ID from another owner is not interchangeable. |
| ownership | Inline handle values only. |
| failure | Raises IndexFailure(foreign_handle). |
| cost | O(1), no row lookup or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0018

[Lines 120–120](../../../../../src/storage/accounted_indexed.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mutable_revision() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent a mutation from exhausting revision identity. |
| inputs / outputs | Checks room for one revision increment without changing it. |
| invariants | A real mutation invalidates ordinary and matching journal cursors; rollback does not resurrect their old revision. |
| ownership | Inline state access. |
| failure | Raises IndexFailure(overflow) before mutation. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0019

[Lines 121–123](../../../../../src/storage/accounted_indexed.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlocked() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exclude ordinary mutation/cursor creation while a table journal is active. |
| inputs / outputs | Returns only when journal_active is false. |
| invariants | This is a single-caller authority guard, not concurrent-reader isolation or a mutex. |
| ownership | Inline flag only. |
| failure | Raises IndexFailure(busy). |
| cost | O(1), no allocation on success. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0020

[Lines 124–124](../../../../../src/storage/accounted_indexed.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleHandle handle(const AccountedIndexedRow& row) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct this table logical handle for an existing row. |
| inputs / outputs | Returns owner/relation/row-ID triple. |
| invariants | It does not validate row liveness; caller already has an admitted resident or retained row. |
| ownership | Copies inline identifiers, not an arena pin. |
| failure | Noexcept under caller row-lifetime precondition. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0021

[Lines 125–131](../../../../../src/storage/accounted_indexed.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t transform_hash(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply optional test-only collision shaping to a cached hash. |
| inputs / outputs | Production returns its input; testing modes force full-hash or low-bucket collisions. |
| invariants | Mode is configured only on a fresh empty testing owner; it is not a production hash policy override. |
| ownership | Inline scalar transformation. |
| failure | Noexcept. |
| cost | O(1), no payload read or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0022

[Lines 132–134](../../../../../src/storage/accounted_indexed.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t hash(const AccountedTuple& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit scalar hashing before computing and optionally shaping a native row hash. |
| inputs / outputs | Computes the admitted exact native tuple hash, applies the optional testing transformation, and returns the value that callers later cache in directory hooks. |
| invariants | Framing/field/payload allowances precede opaque row hash work; mutation publication and undo use cached hashes instead. |
| ownership | Borrows immutable native values under the original grant. |
| failure | Work or native validation failure happens before any membership publication. |
| cost | O(tuple fields and actual deep payload hashing); bounded inline-decimal stack formatting is not a heap export. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0023

[Lines 135–135](../../../../../src/storage/accounted_indexed.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t diagnostic_hash(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute a hash only for explicit invariant inspection. |
| inputs / outputs | Immutable native tuple hash receives the same test transformation as operational hashing. |
| invariants | This path intentionally uses no operational work grant; do not substitute it into probes. |
| ownership | Borrows tuple values. |
| failure | Requires valid immutable tuple state. |
| cost | Actual fields/deep-byte hash cost; diagnostic only. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0024

[Lines 136–141](../../../../../src/storage/accounted_indexed.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedRow* row(TupleHandle value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe the logical-ID directory for one owner-checked handle. |
| inputs / outputs | Foreign handle rejects; absent logical ID returns null. |
| invariants | ID directory hash is numeric ID; exact equality still checks the candidate ID. |
| ownership | Returns a borrowed native row pointer. |
| failure | Foreign/work failures precede returned access. |
| cost | Numeric ID-directory probe visits actual colliding ID nodes with fixed scalar equality and admitted structural steps; no row payload hash, equality scan or copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0025

[Lines 142–147](../../../../../src/storage/accounted_indexed.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedRow* row(const AccountedTuple& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe exact primary membership using typed hash and equality. |
| inputs / outputs | Layout-checked native tuple returns matching row or null. |
| invariants | Hash equality alone never establishes membership; exact typed equality decides collisions. |
| ownership | Borrowed input and returned resident row. |
| failure | Work/layout failure changes no membership. |
| cost | Hashes actual tuple fields/deep bytes, then exact-compares visited collision candidates. Complete-payload equality admission can exceed short-circuit comparison. Expected short chains require distributed hashes; worst-case chain visits are linear. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0026

[Lines 148–152](../../../../../src/storage/accounted_indexed.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedIndex* maybe_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an index identity without requiring it to exist. |
| inputs / outputs | IndexId and allowance return borrowed index node or null. |
| invariants | Exact numeric identity resolves hash collisions. |
| ownership | Borrows directory nodes. |
| failure | Work failure propagates without mutation. |
| cost | Numeric index-ID directory probe visits actual colliding ID nodes with fixed equality; no tuple payload lookup or allocation. Worst-case chain length remains explicit admitted work. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0027

[Lines 153–157](../../../../../src/storage/accounted_indexed.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedIndex& index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an existing indexed projection identity. |
| inputs / outputs | IndexId delegates to maybe_index and returns its node by reference. |
| invariants | Unknown index is distinct from an empty known bucket. |
| ownership | Borrowed index reference. |
| failure | Raises IndexFailure(unknown_index) on miss; work failure remains typed. |
| cost | The numeric directory probe visits actual ID collision nodes; this wrapper adds one null check and returns a borrow, without payload hashing, copying or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0028

[Lines 158–165](../../../../../src/storage/accounted_indexed.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedKey* key(AccountedIndexedIndex& index,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe one secondary key with its compiled target-layout identity. |
| inputs / outputs | Index node, typed key and allowance produce matching key node or null. |
| invariants | Directory may contain an empty undo-retained key; liveness is determined by members/live_keys, not mere residency. |
| ownership | Returns borrowed key under State/journal lifetime. |
| failure | Wrong layout/work failure changes no key or membership. |
| cost | Hashes actual key fields/deep bytes and exact-compares visited collision candidates. Expected short chains require distributed hashes; adversarial collision visits and conservative scalar admissions remain charged. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0029

[Lines 166–169](../../../../../src/storage/accounted_indexed.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t slot_room(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute remaining aggregate directory-slot capacity, including pending growth. |
| inputs / outputs | Optional pending slot count returns limits.directory_slots - current - pending after checked admission. |
| invariants | The limit covers all table directories, not a separate full budget for each index. |
| ownership | Inline capacity accounting. |
| failure | Raises IndexFailure(capacity). |
| cost | O(1), no rehash or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0030

[Lines 170–173](../../../../../src/storage/accounted_indexed.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arena_insert_room() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a new row can obtain an arena slot under finite limits. |
| inputs / outputs | Existing free slot permits reuse; otherwise room for another high-water slot is required. |
| invariants | Live, retained, free and exhausted arena metadata differ; a pinned retired allocation is not reusable. |
| ownership | Reads fixed arena statistics. |
| failure | Raises IndexFailure(capacity) before row publication. |
| cost | O(1), no arena scan or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0031

[Lines 174–180](../../../../../src/storage/accounted_indexed.cpp#L174); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L174-L180:sha256:5a57be74b0bf0ad507e82a0a7097a4d58622c4e1ca211c307e9740eef7d7281b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp: imports \`"accounted_indexed_journal.inc"\` for compilation; closes \`struct AccountedIndexedTable::State\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0032

[Lines 181–181](../../../../../src/storage/accounted_indexed.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount AccountedIndexedTable::account_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the layout original query account for this table. |
| inputs / outputs | AccountedLayout returns its query account handle. |
| invariants | It does not create or substitute a new account. |
| ownership | Copy retains the original controller. |
| failure | Requires a valid layout. |
| cost | O(1) account-handle retention. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0033

[Lines 182–182](../../../../../src/storage/accounted_indexed.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::classify(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify existing tuple storage as active/retained under its original allocator framing. |
| inputs / outputs | Native tuple and AllocationLifetime update accounting metadata. |
| invariants | Caller supplies a valid nonreentrant native allocation; publication/undo already funded it. |
| ownership | No payload copy or transfer. |
| failure | Noexcept internal contract; impossible allocator misuse terminates. |
| cost | Direct tuple/header classifications; no whole-account containing-pointer search here. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0034

[Lines 183–189](../../../../../src/storage/accounted_indexed.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::AccountedIndexedTable(RelationId relation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty indexed table in the layout account. |
| inputs / outputs | Relation, valid native layout and IndexedLimits yield fresh storage/arena identities and empty state. |
| invariants | Fresh storage ownership is distinct from shared immutable layout/account identity. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Invalid layout, identity exhaustion or funding failure publishes no table. |
| cost | Fixed State/arena controls; directory/node storage grows on later admitted operations. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0035

[Lines 190–190](../../../../../src/storage/accounted_indexed.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::~AccountedIndexedTable()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invalidate weak low-level cursors when the owning facade disappears. |
| inputs / outputs | Live facade destruction marks facade_alive false, then releases its shared State. |
| invariants | An active journal may retain State while facade loss still invalidates its cursors. Pins retain values independently. |
| ownership | Final State destruction may release all native members; no global owner registry. |
| failure | Nonallocating destructor. |
| cost | Fixed invalidation plus possible full native State/arena release. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0036

[Lines 191–191](../../../../../src/storage/accounted_indexed.cpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L191-L191:sha256:b259b0251c53f99b800373ba4fba0fc7583e8388ee9d68a594298d6272c92a71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0037

[Lines 192–194](../../../../../src/storage/accounted_indexed.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable& AccountedIndexedTable::operator=(AccountedIndexedTable&& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a facade by moving ownership without cloning storage. |
| inputs / outputs | Self move is ignored; destination old facade authority is invalidated before adopting source State. |
| invariants | Cursors tied to replaced State cannot remain usable merely because a journal retained it. |
| ownership | Shared owner is transferred; source becomes moved-from. |
| failure | Noexcept. |
| cost | Fixed owner moves plus actual destruction of the replaced state if last-owned. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0038

[Lines 195–198](../../../../../src/storage/accounted_indexed.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::State& AccountedIndexedTable::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow State after checking facade presence. |
| inputs / outputs | Non-moved table returns its underlying State reference. |
| invariants | This does not itself assert journal quiescence. |
| ownership | Borrowed reference, no owner allocation. |
| failure | Moved-from access raises IndexFailure(invalid_storage). |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0039

[Lines 199–199](../../../../../src/storage/accounted_indexed.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId AccountedIndexedTable::owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect this table storage-owner identity. |
| inputs / outputs | Returns owner ID. |
| invariants | Owner differs for an owning snapshot copy. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0040

[Lines 200–200](../../../../../src/storage/accounted_indexed.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId AccountedIndexedTable::relation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the relation identity bound to this table. |
| inputs / outputs | Returns RelationId. |
| invariants | Same relation number does not make foreign owners interchangeable. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0041

[Lines 201–201](../../../../../src/storage/accounted_indexed.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedIndexedTable::layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable native row layout. |
| inputs / outputs | Returns a const lvalue reference. |
| invariants | Reference requires its retained State/layout owner; it does not pin mutable rows. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0042

[Lines 202–202](../../../../../src/storage/accounted_indexed.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const IndexedLimits& AccountedIndexedTable::limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect all finite component limits. |
| inputs / outputs | Returns const limits reference. |
| invariants | Component limits do not substitute for byte quota or per-operation work. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0043

[Lines 203–203](../../../../../src/storage/accounted_indexed.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedIndexedTable::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read live primary membership population. |
| inputs / outputs | Returns primary resident row count. |
| invariants | Undo-retained erased rows do not contribute to live size. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0044

[Lines 204–204](../../../../../src/storage/accounted_indexed.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t AccountedIndexedTable::revision()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect mutation revision used by borrowed cursors. |
| inputs / outputs | Returns current revision. |
| invariants | Real mutations advance it; rollback does not restore prior cursor validity. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0045

[Lines 205–205](../../../../../src/storage/accounted_indexed.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics AccountedIndexedTable::arena_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read live/retained/free/exhausted arena counts. |
| inputs / outputs | Copies fixed statistics. |
| invariants | Arena slot high-water differs from live table rows. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | O(1), no slot scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0046

[Lines 206–212](../../../../../src/storage/accounted_indexed.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedStatistics AccountedIndexedTable::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read maintained populations and committed/pending action counts. |
| inputs / outputs | Copies maintained directory/node/arena/action counters. |
| invariants | Copied baseline rows/indices and pending journal actions remain separately labeled. |
| ownership | Scalars/statistics copy inline; reference results borrow the underlying State. |
| failure | Moved-from facade raises invalid_storage. |
| cost | Fixed-size copy; no directory population scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0047

[Lines 213–214](../../../../../src/storage/accounted_indexed.cpp#L213); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L214:sha256:2a4b3c875219a4fcc3b47f9ae1d4e02515f309741bfeac9e62488ec5f867d6c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`AccountedIndexedMemoryStatistics AccountedIndexedTable::memory_statistics() const\`: Explicit report: table/arena attribution scans the account ledger, arena reporting visits slot high-water, and directory totals visit resident indices. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_indexed.cpp:L215; use that declaration for the actual input/output shape. |
| invariants | The source note states: Explicit report: table/arena attribution scans the account ledger, arena reporting visits slot high-water, and directory totals visit resident indices. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Explicit report: table/arena attribution scans the account ledger, arena reporting visits slot high-water, and directory totals visit resident indices. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Explicit report: table/arena attribution scans the account ledger, arena reporting visits slot high-water, and directory totals visit resident indices. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0048

[Lines 215–226](../../../../../src/storage/accounted_indexed.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedMemoryStatistics AccountedIndexedTable::memory_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an explicit ownership/capacity memory report. |
| inputs / outputs | Returns maintained populations, table attribution totals, arena high-water report, directory block usage and their owned-byte sum. |
| invariants | Directory usage includes retained capacity; shared immutable layout metadata is not recounted as exclusive table bytes. |
| ownership | Read-only report; no owning row snapshot or ordinary-new scratch is introduced. |
| failure | Requires valid stable State/account; no state repair. |
| cost | O(account allocation ledger + arena slot high-water + resident indices): attribution/arena scans plus each index key-directory header, not a hot O(1) statistics call. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0050

[Lines 228–230](../../../../../src/storage/accounted_indexed.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedIndexedTable::insert(const AccountedTuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert one native tuple using ordinary table authority. |
| inputs / outputs | Tuple/allowance delegate to insert_impl with no journal, returning inserted flag and logical handle. |
| invariants | Active table journal excludes this ordinary writer; exact duplicate returns existing handle without mutation. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Underlying hash/projection/index preparation/publication costs only; wrapper adds no second insertion pass. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0051

[Lines 231–337](../../../../../src/storage/accounted_indexed.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedIndexedTable::insert_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and atomically publish a complete native row and all index memberships. |
| inputs / outputs | Shared State, typed tuple, allowance and optional active journal produce one membership result. |
| invariants | All capacity/counter/growth/node/key/member/undo/pin admissions finish before pointer publication. Cached hashes are used afterward; arena insert is the last potentially allocating payload step. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. Private RAII row/key/member/growth owners transfer only after full preparation; journal retains compact inverse pointers and a tuple pin. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. A duplicate probes and returns before counters/revisions grow. |
| cost | Actual hash/equality, one projection/key probe per index, new node/deep payload allocations and possible O(existing residents) rehash. One row scalar payload copy; undo metadata is O(indices), not a whole-state copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0052

[Lines 338–341](../../../../../src/storage/accounted_indexed.cpp#L338); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L338-L341:sha256:11b4e46fcd3ea6d6202b947434a234077ab5191478354034b76ba2f3bf096022
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`std::optional&lt;TupleHandle&gt; AccountedIndexedTable::find(const AccountedTuple& tuple, IndexWorkAllowance& work) const\`: Low-level probes may see tentative rows. Callers supply any read lease or isolation boundary; ordinary writers and cursor factories enforce the exclusive-journal guard separately. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_indexed.cpp:L342; use that declaration for the actual input/output shape. |
| invariants | The source note states: Low-level probes may see tentative rows. Callers supply any read lease or isolation boundary; ordinary writers and cursor factories enforce the exclusive-journal guard separately. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Low-level probes may see tentative rows. Callers supply any read lease or isolation boundary; ordinary writers and cursor factories enforce the exclusive-journal guard separately. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0053

[Lines 342–346](../../../../../src/storage/accounted_indexed.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> AccountedIndexedTable::find(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find exact native membership without taking ownership. |
| inputs / outputs | Tuple and allowance return an optional logical handle. |
| invariants | Schema token and exact equality are checked through State::row. |
| ownership | Returned handle is not a retaining pin; tentative handles remain internal. |
| failure | Layout/work/invalid-storage failures preserve table state. |
| cost | One structural start plus actual tuple hash and exact collision-candidate comparisons; expected short chains require distributed hashes and worst-case visited-chain work is linear. No payload copy or pin. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0054

[Lines 347–350](../../../../../src/storage/accounted_indexed.cpp#L347); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedTuple* AccountedIndexedTable::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the payload of one owner-checked logical handle. |
| inputs / outputs | Handle and allowance return tuple pointer, or null for an absent ID. |
| invariants | Owner/relation mismatch rejects; success does not clone or pin payload. |
| ownership | Borrow expires with removal/owner loss unless a separate pin preserves storage. |
| failure | Foreign/work/invalid-storage failures are typed. |
| cost | One structural start plus numeric ID-directory probe over actual collision nodes, with fixed ID equality. No tuple payload hash/copy or pin; worst-case chain visits remain admitted work. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0055

[Lines 351–356](../../../../../src/storage/accounted_indexed.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin AccountedIndexedTable::pin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one live table tuple payload independently of membership. |
| inputs / outputs | Handle and allowance produce an arena pin after ID lookup and total-pin capacity admission. |
| invariants | Stale ID rejects; a pin keeps value storage alive but does not preserve table membership. |
| ownership | Pin owns the arena/slot lifetime under the original account. |
| failure | Foreign/stale/work/pin-limit failures occur before pin publication. |
| cost | One structural start and numeric ID collision-chain probe, then fixed pin-count/shared-owner work after capacity checks. No tuple payload clone or independently allocated pin object. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0057

[Lines 358–369](../../../../../src/storage/accounted_indexed.cpp#L358); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::State::prepare_erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pre-admit every destructive link action before an ordinary/bulk erase. |
| inputs / outputs | Known live row and allowance fund primary/ID removal and each membership/key cleanup possibility. |
| invariants | Bulk erasure conservatively reserves final-key cleanup for every member, even when another row currently keeps that key live. |
| ownership | The caller supplies the finite native allowance; operations debit it and never refill or refund spent work. |
| failure | Admission failure occurs before destructive mutation. |
| cost | O(row memberships + row/key scalar-field admission). Tuple-copy allowances are conservative retirement budgets here, not actual deep payload copies. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0058

[Lines 370–379](../../../../../src/storage/accounted_indexed.cpp#L370); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::State::erase_prepaid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one already-admitted live row without throwing work/allocation. |
| inputs / outputs | Known row releases memberships/empty keys, arena liveness and row directories, updating owned populations. |
| invariants | Caller has admitted all work and population/action counter room; node destructors unlink their exact hooks. |
| ownership | Actual nodes/tuple payloads are released; external pins may retain erased arena payloads. |
| failure | Noexcept; impossible arena/link mismatch terminates. |
| cost | O(row memberships) unlink/destruction plus actual last-owned payload release; no key hash, equality probe or allowance refill. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0059

[Lines 380–383](../../../../../src/storage/accounted_indexed.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::State::erase_one(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine single-row ordinary erase admission and publication. |
| inputs / outputs | Known live row and allowance prepare erase, destroy it, then advance revision/committed erase count. |
| invariants | All throwing checks precede erase_prepaid. |
| ownership | Uses existing State/allowance and releases actual membership ownership. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Actual per-index admission/destruction cost; no journal owner or global state copy is required. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0060

[Lines 384–388](../../../../../src/storage/accounted_indexed.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedIndexedTable::erase(const AccountedTuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase one committed/ordinary membership after complete preparation. |
| inputs / outputs | Typed row and allowance return true only for a removed exact member. |
| invariants | A miss is a no-op; active journal excludes this ordinary writer. |
| ownership | Borrowed input; actual erased payload may remain through external pins. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Actual tuple hash/equality over visited collision candidates, followed by per-membership conservative retirement admission and concrete unlink/destruction. Expected probe cost depends on hash distribution; no whole-table snapshot. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0061

[Lines 389–393](../../../../../src/storage/accounted_indexed.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedIndexedTable::erase(TupleHandle handle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase one committed/ordinary membership after complete preparation. |
| inputs / outputs | Owner-checked logical handle and allowance return true only if present. |
| invariants | Foreign owner rejects while a stale same-owner ID returns false. |
| ownership | Borrowed input; actual erased payload may remain through external pins. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Numeric ID-directory collision probe followed by actual per-membership retirement admission/unlink/destruction. Numeric probing does not hash deep payload; row/key retirement units remain conservative rather than hidden clones. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0063

[Lines 395–451](../../../../../src/storage/accounted_indexed.cpp#L395); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId AccountedIndexedTable::add_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a complete secondary projection privately before linking it to rows. |
| inputs / outputs | AccountedProjection and allowance return existing identical-token index or fresh IndexId. |
| invariants | Existing projections are checked first. New key directory/members are private until every row projection and growth succeeds; only row hooks/index identity publish at the end. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. Private index and member RAII owners clean up failed construction. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | O(existing indices) duplicate-token scan plus every live row projection/key hash/equality, member/key allocation and possible key-directory rehash. No high-water row-ID scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0065

[Lines 453–473](../../../../../src/storage/accounted_indexed.cpp#L453); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedIndexedTable::drop_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a complete existing secondary index after funding its destruction. |
| inputs / outputs | IndexId/allowance return false on miss or destroy all resident keys/members and advance revision/action count. |
| invariants | Ordinary mutation requires no active journal. All member unlink/deep-retirement allowances are admitted before destroying the index. |
| ownership | Releases the index key directory, keys and memberships; row payload ownership remains. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Actual index lookup, O(resident keys+members) admission/destruction and their scalar-field allowances; no whole-table row scan beyond those memberships. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0066

[Lines 474–481](../../../../../src/storage/accounted_indexed.cpp#L474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<IndexId> AccountedIndexedTable::indices(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the current index identities as owning native output. |
| inputs / outputs | Allowance produces original-account vector of resident IndexIds. |
| invariants | Enumerates resident links rather than sparse ID high-water. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Work/output allocation failure leaves table unchanged. |
| cost | O(live indices) output allocation/admitted traversal; not a lazy cursor. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0067

[Lines 482–484](../../../../../src/storage/accounted_indexed.cpp#L482); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedProjection AccountedIndexedTable::projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one existing immutable projection descriptor. |
| inputs / outputs | IndexId and allowance return its AccountedProjection handle. |
| invariants | Unknown index rejects; copying the descriptor handle does not clone compiled fields. |
| ownership | Result retains immutable shared descriptor/account, independent of index membership. |
| failure | Invalid index/work/storage failure before return. |
| cost | Numeric index-ID collision probe followed by fixed shared immutable descriptor retention. It does not clone the field map or scan rows/keys. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0068

[Lines 485–487](../../../../../src/storage/accounted_indexed.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedIndexedTable::key_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read live secondary-key population for one known index. |
| inputs / outputs | IndexId/allowance return live_keys.size(), excluding empty undo-retained residents. |
| invariants | Key presence follows member nonemptiness, not zero numeric annotation or nullary-key sentinel. |
| ownership | Copies one inline count. |
| failure | Unknown index/work/storage failure. |
| cost | Numeric index-ID collision probe followed by one maintained live-key count read. No key/payload/directory-capacity scan or output allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0069

[Lines 488–495](../../../../../src/storage/accounted_indexed.cpp#L488); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedIndexedTable::keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy live secondary-key tuples into owning native output. |
| inputs / outputs | IndexId/allowance produce one deep owning key per live-key link. |
| invariants | Empty journal-retained key nodes are omitted; output order follows current first-live-key order. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Work/allocation failure discards partial output without mutation. |
| cost | O(live keys) traversal plus all key fields/deep bytes copied and admitted; no directory-capacity scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0070

[Lines 496–505](../../../../../src/storage/accounted_indexed.cpp#L496); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<TupleHandle> AccountedIndexedTable::bucket(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize handles in one exact secondary key bucket. |
| inputs / outputs | IndexId, typed key and allowance return original-account vector of matching row handles; absent key returns empty. |
| invariants | This API copies O(matches) handles; bucket_cursor is the separate lazy borrowed alternative. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Unknown index/layout/work/output failure changes no membership. |
| cost | Index-ID and actual typed key hash/equality probe over visited collision candidates, plus O(matches) admitted member traversal/handle output storage. No row payload clone; bucket_cursor is the separate lazy alternative. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0071

[Lines 506–516](../../../../../src/storage/accounted_indexed.cpp#L506); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedIndexedTable::erase_key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically erase all rows matching one secondary key. |
| inputs / outputs | Known index/key/allowance return removed population, or zero on key miss. |
| invariants | Collect borrowed row pointers and prepare every row erase before the first destructive step. Revision increments once for the bulk operation. |
| ownership | Original-account temporary O(matches) pointer vector; no result row copy. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Key lookup plus O(matches * per-row memberships/field admission), temporary pointers and actual destruction; possible final-key cleanup is conservatively prepaid. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0072

[Lines 517–526](../../../../../src/storage/accounted_indexed.cpp#L517); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::clear(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove all ordinary live rows after complete bulk admission. |
| inputs / outputs | Allowance prepares each resident row, then erases all; an already empty table is a no-op. |
| invariants | No active journal; all work/counter room is checked before destruction; index descriptors/capacities may remain. |
| ownership | Releases row/member/live-key ownership while external pins retain payloads as needed. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | O(live rows and their memberships/field allowances), no sparse tuple-ID scan; one revision/clear action update. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0073

[Lines 527–534](../../../../../src/storage/accounted_indexed.cpp#L527); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedVector<AccountedTuple> AccountedIndexedTable::snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current live row relation as owning native values. |
| inputs / outputs | Allowance returns original-account deep row vector in resident insertion order. |
| invariants | Explicit materialization, not a current-result iterator or transaction-isolation authority. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Work/allocation failure discards the partial vector and changes no table. |
| cost | O(live rows and row fields/deep bytes) copy/admission; does not scan primary directory capacity or logical ID high-water. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0075

[Lines 536–544](../../../../../src/storage/accounted_indexed.cpp#L536); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedTable::Cursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep minimal weak-owner state for a live-row or bucket cursor. |
| inputs / outputs | Captures State weak owner and revision, optional journal authority and next resident/member pointer. |
| invariants | Data owns neither a result history nor the table facade. Validity checks must precede pointer dereference. |
| ownership | Original-account cursor object owns metadata; journal cursor additionally retains phase/grant authority. |
| failure | Funding failure returns no cursor and publishes no table state. |
| cost | Fixed metadata per cursor; no row/handle vector or directory-capacity scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0076

[Lines 545–545](../../../../../src/storage/accounted_indexed.cpp#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Cursor::Cursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt already funded Cursor traversal metadata without another allocation. |
| inputs / outputs | Private constructor moves AccountedUnique&lt;Data&gt; into data_; its factory has already admitted/funded the metadata. |
| invariants | The constructor does not validate owner/revision/grant or advance traversal; next performs those fences before saved-pointer use. |
| ownership | Unique metadata ownership is transferred. Data has weak State ownership and optional shared reader/grant; a weak control may remain funded after the State object dies. |
| failure | The move is noexcept; factory allocation/admission failures occur before calling this constructor. |
| cost | Fixed unique/deleter/account-handle transfer; no row scan, payload copy, new work grant or heap allocation. |
| Design | [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0077

[Lines 546–548](../../../../../src/storage/accounted_indexed.cpp#L546); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L546-L548:sha256:63b6eca3ec0e6a761f468f7e5fd581d789967099e672fc514b9d26e0fcfff653
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0078

[Lines 549–572](../../../../../src/storage/accounted_indexed.cpp#L549); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedIndexedTable::Cursor::Entry> AccountedIndexedTable::Cursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance exactly one native live row/member link and borrow its tuple. |
| inputs / outputs | Caller allowance returns Entry(handle, const tuple&) or nullopt at end. |
| invariants | Validate Data, facade, journal phase/exact grant, active authority and revision before dereferencing pointers. start debits even end detection; a denial does not advance position. |
| ownership | Entry borrows the table/arena payload and is not a pin; low-level cursor has weak table ownership. |
| failure | Moved/owner-lost/aborted/revision-stale cursor raises invalid_cursor; a different journal grant raises contract; another active journal raises busy. |
| cost | Fixed owner/authority checks and one admitted link/end step, no row hash, ID lookup, payload copy or ordinary-new success allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0079

[Lines 573–579](../../../../../src/storage/accounted_indexed.cpp#L573); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Cursor AccountedIndexedTable::live(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a lazy ordinary live-row cursor. |
| inputs / outputs | Allowance funds Cursor::Data and starts at primary first_resident. |
| invariants | Creation is excluded by an active journal; no rows are enumerated at startup. |
| ownership | Original-account metadata with weak State owner, not a strong table/read-isolation lease. |
| failure | Busy/work/allocation failure returns no cursor. |
| cost | One structural admission, fixed cursor metadata reservation/allocation and first-pointer read; no capacity or row scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0080

[Lines 580–587](../../../../../src/storage/accounted_indexed.cpp#L580); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Cursor AccountedIndexedTable::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a lazy ordinary cursor for one exact secondary bucket. |
| inputs / outputs | IndexId, typed key and allowance fund cursor metadata and select first member, or an empty cursor on key miss. |
| invariants | Known index and matching target layout required; no active journal for this factory. |
| ownership | Key input is borrowed only during probe; returned cursor keeps native member pointer under weak State/revision validity. |
| failure | Unknown index/layout/busy/work/allocation failure leaves state unchanged. |
| cost | Actual index/key hash/equality lookup plus fixed cursor owner cost; no O(matches) handle materialization. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0081

[Lines 588–594](../../../../../src/storage/accounted_indexed.cpp#L588); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedTable::IndexKeyCursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain minimal traversal state for live secondary keys. |
| inputs / outputs | Captures weak State owner, revision, optional journal authority and next live-key pointer. |
| invariants | Only nonempty bucket keys belong to the live-key list; empty undo-retained keys are omitted. |
| ownership | Original-account cursor Data; no copied key collection or strong table owner. |
| failure | Preparation failure installs no externally usable cursor. |
| cost | Fixed metadata independent of key count/capacity. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0082

[Lines 595–595](../../../../../src/storage/accounted_indexed.cpp#L595); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::IndexKeyCursor::IndexKeyCursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt already funded IndexKeyCursor traversal metadata without another allocation. |
| inputs / outputs | Private constructor moves AccountedUnique&lt;Data&gt; into data_; its factory has already admitted/funded the metadata. |
| invariants | The constructor does not validate owner/revision/grant or advance traversal; next performs those fences before saved-pointer use. |
| ownership | Unique metadata ownership is transferred. Data has weak State ownership and optional shared reader/grant; a weak control may remain funded after the State object dies. |
| failure | The move is noexcept; factory allocation/admission failures occur before calling this constructor. |
| cost | Fixed unique/deleter/account-handle transfer; no row scan, payload copy, new work grant or heap allocation. |
| Design | [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed_nodes.hpp](../../../../../src/storage/accounted_indexed_nodes.hpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0083

[Lines 596–598](../../../../../src/storage/accounted_indexed.cpp#L596); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L596-L598:sha256:f0dc5f96495f917c1c3413ae9adc27cc824e0c562778b97fa0ab2497a7e3cd8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0084

[Lines 599–615](../../../../../src/storage/accounted_indexed.cpp#L599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<AccountedIndexedTable::IndexKeyCursor::Entry> AccountedIndexedTable::IndexKeyCursor::next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the next live key and its current bucket degree. |
| inputs / outputs | Allowance produces Entry(const key&, size) or nullopt. |
| invariants | Owner/facade/journal/exact-grant/revision checks precede the live pointer. Every call reaching start spends an end/advance step, including repeated null results. |
| ownership | Borrowed key/inline degree; no retaining pin or owned tuple copy. |
| failure | Invalid owner/phase/revision or work/authority rejection does not traverse stale pointers. |
| cost | Fixed checks plus one live-link/end step and O(1) bucket-size read; no hash or key payload copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0085

[Lines 616–622](../../../../../src/storage/accounted_indexed.cpp#L616); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an ordinary lazy live-key cursor for a known index. |
| inputs / outputs | IndexId/allowance produce weak-owner cursor at the first live key. |
| invariants | Requires no active journal; empty undo-retained directory residents are never yielded. |
| ownership | One original-account cursor object; borrowed table/key lifetime remains caller responsibility. |
| failure | Busy/unknown-index/work/allocation failure leaves state unchanged. |
| cost | Actual index lookup and fixed cursor preparation, no key-vector or directory scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0087

[Lines 624–631](../../../../../src/storage/accounted_indexed.cpp#L624); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::live() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open an owner-authorized tentative live-row cursor. |
| inputs / outputs | Active journal produces cursor sharing its phase reader and exact AccountedIndexWork. |
| invariants | Journal factory, cursor next and composed updates use one allowance. Rollback aborts authority before undo; a future mutation invalidates by revision. |
| ownership | Cursor retains reader/grant but only weak table State; active journal owns State separately. |
| failure | Closed/moved journal or work/allocation failure rejects without mutation. |
| cost | Fixed cursor owner/metadata admission, no relation materialization or new grant. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0088

[Lines 632–641](../../../../../src/storage/accounted_indexed.cpp#L632); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::bucket_cursor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a tentative secondary bucket cursor under the active journal authority. |
| inputs / outputs | IndexId and native key use the journal retained allowance and return a lazy matching/empty cursor. |
| invariants | Only this active journal may bypass ordinary busy exclusion; cursor requires the exact same grant on next. |
| ownership | Metadata owns shared reader, not copied key rows or State. |
| failure | Closed journal, wrong index/layout or work/allocation failure changes no state. |
| cost | Actual index/key probe plus fixed cursor allocation; no O(matches) scratch vector. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0089

[Lines 642–649](../../../../../src/storage/accounted_indexed.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::Journal::index_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a tentative live-key traversal under the active journal reader. |
| inputs / outputs | Known IndexId returns a lazy key cursor sharing journal phase/remainder. |
| invariants | Commit can preserve a valid cursor until further mutation; rollback or owner/facade loss invalidates it before traversal. |
| ownership | Original-account Data and shared phase/grant owner; table ownership remains weak. |
| failure | Closed journal/index/work/allocation failure rejects before cursor publication. |
| cost | Index lookup and fixed metadata preparation, not a key collection or budget refill. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0091

[Lines 651–694](../../../../../src/storage/accounted_indexed.cpp#L651); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable AccountedIndexedTable::snapshot_copy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a new owning table from current live sparse state. |
| inputs / outputs | Allowance copies live rows and indices to fresh storage/arena owners while retaining layout/account/limits. |
| invariants | Reject active source journal. Preserve sparse row/index IDs, their high-water counters, revision and row/live-key order. Reset action history to copied_rows/copied_indices baseline; external pins/retired rows/history are not copied. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. Destination owns fresh payloads/nodes; source remains unchanged and original account must fund both live tables. |
| failure | Any preparation/probe/contract/work/allocation failure destroys partial destination; source remains untouched. |
| cost | Actual live-row copy plus complete per-index rebuild/projections/hash work, O(live keys) temporary ordering pointers and prepaid list restoration. No logical high-water scan; not O(1) clone. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0093

[Lines 696–802](../../../../../src/storage/accounted_indexed.cpp#L696); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect full native directory/arena/member/journal consistency without scratch allocation. |
| inputs / outputs | Stable State is checked for owner/ID/hash/projection/liveness/finite-limit and action-census agreement. |
| invariants | Diagnostic may inspect tentative journal entries; it must not stand in for an operational grant or routine cursor/probe implementation. |
| ownership | Borrows all native populations; no new result, hash sets or history owner. |
| failure | Fixed contract failures stop inspection; it does not mutate or repair the table. |
| cost | Scans capacities, arena high-water and account ledger, with collision-heavy directory scans, row uniqueness/identity, key-residency and active-journal reference cross-products. Nonallocating is not a linear-time guarantee. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0094

[Lines 803–804](../../../../../src/storage/accounted_indexed.cpp#L803); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L803-L804:sha256:689e8a4ac7d0424f792575ba6c59462e7fc0cf052b1cbbd63635e02bd33623ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp: opens/branches compile-time guard \`#ifdef CROWN_ACCOUNTED_INDEXED_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0095

[Lines 805–814](../../../../../src/storage/accounted_indexed.cpp#L805); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::AccountedIndexedTesting::collisions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure deterministic collision stress on a fresh testing-only owner. |
| inputs / outputs | Empty table and declared collision mode set the hash transformation. |
| invariants | No rows/indices or prior IDs may exist; same-bucket mode restricts directory-mask domain. This entry is absent from production builds. |
| ownership | Changes one testing-only scalar, no native owner/layout replacement. |
| failure | Invalid population/mode/domain raises contract before assignment. |
| cost | O(1) testing metadata, not a production fast-path policy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0096

[Lines 815–822](../../../../../src/storage/accounted_indexed.cpp#L815); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::AccountedIndexedTesting::exhaust(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set one identity/revision counter to its maximum for rejection tests. |
| inputs / outputs | Unlocked testing owner and exhausted enum choose tuple ID, index ID or revision max. |
| invariants | Testing-only synthetic state drives next-operation overflow controls; no capability is exposed in production. |
| ownership | Inline counter assignment. |
| failure | Moved/busy owner still rejects. |
| cost | O(1), no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0097

[Lines 823–825](../../../../../src/storage/accounted_indexed.cpp#L823); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L823-L825:sha256:291eba6d80cb43bae7faf70bdb11f50856adc53444b79a59b5277f805c2e4acf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed.cpp: closes the matching compile-time guard; closes \`namespace crown::storage\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
