#include "crown/storage/accounted_reference.hpp"
#include "owner.hpp"
#include <exception>
#include <algorithm>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <utility>

namespace crown::storage {
namespace {
using resource::AllocationLifetime;
using resource::MemoryAccount;
using resource::MemoryAllocator;
using resource::MemoryAttribution;
using resource::MemoryFailure;
using resource::MemoryFault;
using resource::MemoryOwnerKind;
using resource::MemoryPurpose;
constexpr auto maximum = std::numeric_limits<std::uint64_t>::max();
void require(bool value, TableProblem issue = TableProblem::invariant) {
  if (!value) throw TableValidationFailure(issue);
}
StorageOwnerId new_owner() {
  const auto id = detail::try_new_storage_owner();
  if (!id) throw MemoryFailure(MemoryFault::overflow);
  return *id;
}
struct TupleLess {
  using is_transparent = void;
  bool operator()(const AccountedTuple& a, const AccountedTuple& b) const noexcept { return a.values() < b.values(); }
  bool operator()(const AccountedTuple* a, const AccountedTuple* b) const noexcept { return (*this)(*a, *b); }
  bool operator()(const AccountedTuple* a, const AccountedTuple& b) const noexcept { return (*this)(*a, b); }
  bool operator()(const AccountedTuple& a, const AccountedTuple* b) const noexcept { return (*this)(a, *b); }
};
struct Reader { enum class Phase { active, committed, aborted };Phase phase = Phase::active; };
template<class Map, class... Args>
typename Map::node_type prepare_node(const Map& owner, Args&&... args) {
  Map temporary(owner.key_comp(), owner.get_allocator());
  const auto [position, inserted] = temporary.emplace(std::forward<Args>(args)...);
  require(inserted);return temporary.extract(position);
}
template<class Map> auto publish_node(Map& owner, typename Map::node_type node) noexcept {
  auto result = owner.insert(std::move(node));
  if (!result.inserted) std::terminate();
  return result.position;
}
template<class Vector> void reserve(Vector& values, std::size_t size) {
  if (size > values.max_size()) throw MemoryFailure(MemoryFault::overflow);
  values.reserve(size);
}
bool matches(const AccountedProjection& projection, const AccountedTuple& source, const AccountedTuple& key) {
  if (!projection.source().same_token(source.layout()) || !projection.target().same_token(key.layout())) return false;
  const auto fields = projection.fields();
  for (std::size_t i = 0; i < fields.size(); ++i) if (source.values()[fields[i].value] != key.values()[i]) return false;
  return true;
}
}
std::string_view TableValidationFailure::code() const noexcept {
  switch (problem_) {
    case TableProblem::invalid_table: return "invalid_storage";
    case TableProblem::invalid_journal: return "invalid_journal";
    case TableProblem::invalid_cursor: return "invalid_cursor";
    case TableProblem::foreign_handle: return "foreign_handle";
    case TableProblem::stale_handle: return "stale_handle";
    case TableProblem::layout_mismatch: return "layout_mismatch";
    case TableProblem::unknown_index: return "unknown_index";
    case TableProblem::busy: return "storage_busy";
    case TableProblem::invariant: return "storage_contract";
  }
  return "storage_contract";
}
const char* TableValidationFailure::what() const noexcept { return code().data(); }

namespace site {  // Containing-allocation sites, one per element position and layout.
struct PrimaryKey; struct ByIdKey; struct BucketKey; struct Member; struct Entry; struct KeyBuffer; struct JournalData; struct Reader;
}  // namespace site

struct AccountedReferenceTable::State {
  using PrimaryValue = std::pair<const AccountedTuple* const, TupleId>;
  using Primary = std::map<const AccountedTuple*, TupleId, TupleLess, MemoryAllocator<PrimaryValue>>;
  struct Record { Primary::const_iterator primary;ArenaHandle arena; };
  using ById = std::map<TupleId, Record, std::less<TupleId>, MemoryAllocator<std::pair<const TupleId, Record>>>;
  using Members = std::set<TupleId, std::less<TupleId>, MemoryAllocator<TupleId>>;
  using Buckets = std::map<AccountedTuple, Members, TupleLess, MemoryAllocator<std::pair<const AccountedTuple, Members>>>;
  struct Index {
    AccountedProjection projection;
    Buckets buckets;
    Index(AccountedProjection value, const MemoryAccount& account, MemoryAttribution tag)
        : projection(std::move(value)), buckets(TupleLess{}, MemoryAllocator<Buckets::value_type>(account, MemoryPurpose::secondary_node, tag)) {}
  };
  using Indices = std::map<IndexId, Index, std::less<IndexId>, MemoryAllocator<std::pair<const IndexId, Index>>>;
  MemoryAccount account;
  AccountedLayout layout;
  StorageOwnerId owner;
  RelationId relation;
  MemoryAttribution tag{MemoryOwnerKind::storage_table, owner.value};
  AccountedTupleArena arena;
  Primary primary;
  ById by_id;
  Indices indices;
  std::uint64_t last_tuple = 0, last_index = 0, revision = 0;
  std::size_t active_entries = 0, retained_entries = 0;
  bool journal_active = false, facade_alive = true;
  std::weak_ptr<Reader> active_reader;
  State(MemoryAccount value, RelationId id, AccountedLayout descriptor, StorageOwnerId identity)
      : account(std::move(value)), layout(std::move(descriptor)), owner(identity), relation(id), arena(layout),
        primary(TupleLess{}, MemoryAllocator<PrimaryValue>(account, MemoryPurpose::primary_node, tag)),
        by_id(std::less<TupleId>{}, MemoryAllocator<ById::value_type>(account, MemoryPurpose::primary_node, tag)),
        indices(std::less<IndexId>{}, MemoryAllocator<Indices::value_type>(account, MemoryPurpose::secondary_node, tag)) {}
  void unlocked() const { require(!journal_active, TableProblem::busy); }
  void mutable_revision() const { if (revision == maximum) throw MemoryFailure(MemoryFault::overflow); }
  void input(const AccountedTuple& tuple) const { require(layout.same_token(tuple.layout()), TableProblem::layout_mismatch); }
  void owned(TupleHandle handle) const { require(handle.owner == owner && handle.relation == relation, TableProblem::foreign_handle); }
  TupleHandle handle(TupleId id) const noexcept { return {owner, relation, id}; }
  Index& index(IndexId id) {
    const auto found = indices.find(id);require(found != indices.end(), TableProblem::unknown_index);return found->second;
  }
  void key(const Index& index, const AccountedTuple& tuple) const {
    require(index.projection.target().same_token(tuple.layout()), TableProblem::layout_mismatch);
  }
  template<class T> AccountedVector<T> vector(MemoryPurpose purpose = MemoryPurpose::scratch) const {
    return AccountedVector<T>(MemoryAllocator<T>(account, purpose, tag));
  }
  template<class T> AccountedVector<T> output() const {
    return AccountedVector<T>(MemoryAllocator<T>(account, MemoryPurpose::output_buffer, output_tag()));
  }
  MemoryAttribution output_tag() const noexcept { return {MemoryOwnerKind::output, owner.value}; }
  // Site names one element position in one allocation layout (see
  // MemoryAccount::ContainingSite): O(1) after one calibration per site.
  template<class Site, class T> void lifetime(const T& value, MemoryPurpose purpose, AllocationLifetime life) const noexcept {
    static MemoryAccount::ContainingSite site;
    account.set_lifetime_containing(std::addressof(value), site, purpose, tag, life);
  }
  InsertResult insert(const AccountedTuple& tuple) {
    input(tuple);const auto found = primary.find(tuple);
    if (found != primary.end()) return {false, handle(found->second)};
    mutable_revision();if (last_tuple == maximum) throw MemoryFailure(MemoryFault::overflow);
    const TupleId id{last_tuple + 1};
    // Preparation borrows this synchronous input; publication below rebinds
    // the primary key to the stable arena tuple before installing the node.
    auto row_node = prepare_node(primary, &tuple, id);
    auto id_node = prepare_node(by_id, id, Record{});
    struct Prepared { Index* index;Buckets::iterator existing;Buckets::node_type bucket;Members::node_type member; };
    auto prepared = vector<Prepared>();reserve(prepared, indices.size());
    for (auto& [index_id, index] : indices) {
      static_cast<void>(index_id);auto key = index.projection.apply(tuple, tag);
      auto bucket = index.buckets.find(key);
      Members members(std::less<TupleId>{}, MemoryAllocator<TupleId>(account, MemoryPurpose::secondary_node, tag));
      auto member = prepare_node(members, id);
      if (bucket == index.buckets.end()) {
        publish_node(members, std::move(member));
        auto bucket_node = prepare_node(index.buckets, std::move(key), std::move(members));
        prepared.push_back({&index, bucket, std::move(bucket_node), {}});
      } else prepared.push_back({&index, bucket, {}, std::move(member)});
    }
    // The arena is the last throwing preparation. All map nodes are owned and
    // detached already. Publication below changes only links and counters.
    const auto allocated = arena.insert(tuple);
    row_node.key() = &arena.get(allocated);
    const auto row = publish_node(primary, std::move(row_node));
    id_node.mapped() = Record{row, allocated};publish_node(by_id, std::move(id_node));
    for (auto& item : prepared) {
      if (item.bucket) publish_node(item.index->buckets, std::move(item.bucket));
      else publish_node(item.existing->second, std::move(item.member));
    }
    last_tuple = id.value;++revision;return {true, handle(id)};
  }
};

struct AccountedReferenceTable::Journal::Data {
  struct Key {
    State::Index* index;
    AccountedTuple key;
    State::Members::node_type member;
    State::Buckets::node_type bucket;
  };
  struct Undo {
    bool inserted;
    TupleHandle handle{};
    std::uint64_t previous_last = 0;
    std::optional<AccountedTupleArena::Pin> pin;
    AccountedVector<Key> keys;
    State::Primary::node_type primary;
    State::ById::node_type id;
    Undo(bool add, const MemoryAccount& account, MemoryAttribution tag)
        : inserted(add), keys(MemoryAllocator<Key>(account, MemoryPurpose::journal_undo, tag)) {}
  };
  using Entries = std::list<Undo, MemoryAllocator<Undo>>;
  std::shared_ptr<State> owner;
  std::weak_ptr<State> report_owner;
  std::shared_ptr<Reader> reader;
  Entries entries;
  bool committed = false;
  Data(std::shared_ptr<State> state, std::shared_ptr<Reader> authority)
      : owner(std::move(state)), report_owner(owner), reader(std::move(authority)),
        entries(MemoryAllocator<Undo>(owner->account, MemoryPurpose::journal_undo, owner->tag)) {}
  ~Data() {
    rollback();
    if (committed) if (const auto state = report_owner.lock()) {
      if (state->retained_entries < entries.size()) std::terminate();
      state->retained_entries -= entries.size();
    }
  }
  State& active() const { require(bool(owner) && owner->journal_active, TableProblem::invalid_journal);return *owner; }
  Entries prepare(bool inserted, const AccountedTuple& tuple) {
    auto& s = active();
    if (s.active_entries == std::numeric_limits<std::size_t>::max() - s.retained_entries || entries.size() == entries.max_size())
      throw MemoryFailure(MemoryFault::overflow);
    Entries staged(entries.get_allocator());staged.emplace_back(inserted, s.account, s.tag);
    auto& undo = staged.back();reserve(undo.keys, s.indices.size());
    for (auto& [id, index] : s.indices) {
      static_cast<void>(id);auto key = index.projection.apply(tuple, s.tag);
      AccountedReferenceTable::classify(key, AllocationLifetime::retained);
      undo.keys.push_back({&index, std::move(key), {}, {}});
    }
    return staged;
  }
  void publish(Entries& staged) noexcept { entries.splice(entries.end(), staged);++owner->active_entries; }
  void undo_insert(Undo& undo) noexcept {
    auto& s = *owner;
    for (auto& key : undo.keys) {
      const auto bucket = key.index->buckets.find(key.key);
      if (bucket == key.index->buckets.end() || bucket->second.erase(undo.handle.tuple) != 1) std::terminate();
      if (bucket->second.empty()) key.index->buckets.erase(bucket);
    }
    const auto id = s.by_id.find(undo.handle.tuple);if (id == s.by_id.end()) std::terminate();
    const auto row = id->second.primary;const auto arena = id->second.arena;
    s.by_id.erase(id);s.primary.erase(row);
    if (!s.arena.erase(arena)) std::terminate();
    s.last_tuple = undo.previous_last;
  }
  void undo_erase(Undo& undo) noexcept {
    auto& s = *owner;AccountedReferenceTable::revive(s.arena, *undo.pin);
    s.lifetime<site::PrimaryKey>(undo.primary.key(), MemoryPurpose::primary_node, AllocationLifetime::active);
    s.lifetime<site::ByIdKey>(undo.id.key(), MemoryPurpose::primary_node, AllocationLifetime::active);
    const auto row = publish_node(s.primary, std::move(undo.primary));
    undo.id.mapped().primary = row;publish_node(s.by_id, std::move(undo.id));
    for (auto& key : undo.keys) {
      auto bucket = key.index->buckets.end();
      if (key.bucket) {
        s.lifetime<site::BucketKey>(key.bucket.key(), MemoryPurpose::secondary_node, AllocationLifetime::active);
        AccountedReferenceTable::classify(key.bucket.key(), AllocationLifetime::active);
        bucket = publish_node(key.index->buckets, std::move(key.bucket));
      } else bucket = key.index->buckets.find(key.key);
      if (bucket == key.index->buckets.end() || !key.member) std::terminate();
      s.lifetime<site::Member>(key.member.value(), MemoryPurpose::secondary_node, AllocationLifetime::active);
      publish_node(bucket->second, std::move(key.member));
    }
  }
  void rollback() noexcept {
    if (!owner) return;
    reader->phase = Reader::Phase::aborted;
    for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
      if (it->inserted) undo_insert(*it);else undo_erase(*it);
    }
    owner->active_entries = 0;owner->active_reader.reset();owner->journal_active = false;
    entries.clear();owner.reset();
  }
};

MemoryAccount AccountedReferenceTable::account_for(const AccountedLayout& layout) { return layout.query_account(); }
void AccountedReferenceTable::classify(AccountedTuple& tuple, AllocationLifetime lifetime) noexcept { tuple.set_lifetime(lifetime); }
void AccountedReferenceTable::revive(AccountedTupleArena& arena, const AccountedTupleArena::Pin& pin) noexcept { arena.revive(pin); }
AccountedReferenceTable::AccountedReferenceTable(RelationId relation, AccountedLayout layout) {
  require(bool(layout), TableProblem::layout_mismatch);auto account = account_for(layout);const auto owner = new_owner();
  state_ = resource::make_accounted_shared<State>({MemoryOwnerKind::storage_table, owner.value}, account,
      MemoryPurpose::table_state, account, relation, std::move(layout), owner);
}
AccountedReferenceTable::AccountedReferenceTable(std::shared_ptr<State> state) noexcept : state_(std::move(state)) {}
AccountedReferenceTable::~AccountedReferenceTable() { if (state_) state_->facade_alive = false; }
AccountedReferenceTable::AccountedReferenceTable(AccountedReferenceTable&&) noexcept = default;
AccountedReferenceTable& AccountedReferenceTable::operator=(AccountedReferenceTable&& other) noexcept {
  if (this != &other) { if (state_) state_->facade_alive = false;state_ = std::move(other.state_); }return *this;
}
AccountedReferenceTable::State& AccountedReferenceTable::state() const {
  require(bool(state_), TableProblem::invalid_table);return *state_;
}
StorageOwnerId AccountedReferenceTable::owner() const { return state().owner; }
RelationId AccountedReferenceTable::relation() const { return state().relation; }
const AccountedLayout& AccountedReferenceTable::layout() const & { return state().layout; }
std::size_t AccountedReferenceTable::size() const { return state().primary.size(); }
std::uint64_t AccountedReferenceTable::revision() const { return state().revision; }
MemoryAttribution AccountedReferenceTable::attribution() const { return state().tag; }
ArenaStatistics AccountedReferenceTable::arena_statistics() const { return state().arena.statistics(); }
TableMemoryStatistics AccountedReferenceTable::memory_statistics() const {
  const auto& s = state();TableMemoryStatistics result;
  result.live_records = s.primary.size();result.indices = s.indices.size();
  result.active_undo_entries = s.active_entries;result.retained_undo_entries = s.retained_entries;
  for (const auto& [id, index] : s.indices) {
    static_cast<void>(id);result.secondary_keys += index.buckets.size();
    for (const auto& [key, members] : index.buckets) { static_cast<void>(key);result.memberships += members.size(); }
  }
  result.table = s.account.statistics_for(s.tag);result.arena = s.arena.memory_statistics();
  result.owned = result.table.current;
  result.owned.allocations += result.arena.owner.current.allocations;
  result.owned.requested_bytes += result.arena.owner.current.requested_bytes;
  result.owned.payload_bytes += result.arena.owner.current.payload_bytes;return result;
}
InsertResult AccountedReferenceTable::insert(const AccountedTuple& tuple) { auto& s = state();s.unlocked();return s.insert(tuple); }
std::optional<TupleHandle> AccountedReferenceTable::find(const AccountedTuple& tuple) const {
  auto& s = state();s.input(tuple);const auto found = s.primary.find(tuple);
  if (found == s.primary.end()) return {};
  return s.handle(found->second);
}
const AccountedTuple* AccountedReferenceTable::get(TupleHandle handle) const & {
  auto& s = state();s.owned(handle);const auto found = s.by_id.find(handle.tuple);
  return found == s.by_id.end() ? nullptr : &s.arena.get(found->second.arena);
}
AccountedTupleArena::Pin AccountedReferenceTable::pin(TupleHandle handle) const {
  auto& s = state();s.owned(handle);const auto found = s.by_id.find(handle.tuple);
  require(found != s.by_id.end(), TableProblem::stale_handle);return s.arena.pin(found->second.arena);
}
AccountedReferenceTable::Journal::Journal(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedReferenceTable::Journal::Journal(Journal&&) noexcept = default;
AccountedReferenceTable::Journal& AccountedReferenceTable::Journal::operator=(Journal&&) noexcept = default;
AccountedReferenceTable::Journal::~Journal() = default;
bool AccountedReferenceTable::Journal::active() const noexcept { return data_ && data_->owner; }
std::size_t AccountedReferenceTable::Journal::size() const noexcept { return data_ ? data_->entries.size() : 0; }
AccountedReferenceTable::ChangeView AccountedReferenceTable::Journal::change(std::size_t index) const & {
  require(bool(data_) && index < data_->entries.size(), TableProblem::invalid_journal);
  auto it = data_->entries.begin();std::advance(it, static_cast<std::ptrdiff_t>(index));
  return {it->inserted, it->handle, it->pin->get()};
}
void AccountedReferenceTable::Journal::rollback() noexcept { if (data_) data_->rollback(); }
void AccountedReferenceTable::Journal::commit() noexcept {
  if (!active()) return;
  auto& s = *data_->owner;
  for (auto& entry : data_->entries) {
    s.lifetime<site::Entry>(entry, MemoryPurpose::journal_undo, AllocationLifetime::retained);
    if (entry.keys.data()) s.lifetime<site::KeyBuffer>(*entry.keys.data(), MemoryPurpose::journal_undo, AllocationLifetime::retained);
  }
  s.lifetime<site::JournalData>(*data_, MemoryPurpose::journal_undo, AllocationLifetime::retained);
  s.lifetime<site::Reader>(*data_->reader, MemoryPurpose::cursor, AllocationLifetime::retained);
  s.retained_entries += s.active_entries;s.active_entries = 0;
  data_->committed = true;data_->reader->phase = Reader::Phase::committed;
  s.active_reader.reset();s.journal_active = false;data_->owner.reset();
}
AccountedReferenceTable::Journal AccountedReferenceTable::journal() {
  auto& s = state();s.unlocked();
  auto reader = resource::make_accounted_shared<Reader>(s.tag, s.account, MemoryPurpose::cursor);
  auto data = resource::make_accounted_unique<Journal::Data>(s.tag, s.account, MemoryPurpose::journal_undo, state_, std::move(reader));
  s.active_reader = data->reader;s.journal_active = true;return Journal(std::move(data));
}
InsertResult AccountedReferenceTable::Journal::insert(const AccountedTuple& tuple) {
  require(bool(data_), TableProblem::invalid_journal);auto& s = data_->active();s.input(tuple);
  const auto found = s.primary.find(tuple);if (found != s.primary.end()) return {false, s.handle(found->second)};
  // Admit pin room before insertion; pinning the new row then cannot overflow
  // after native membership has been published.
  if (s.arena.statistics().pins == std::numeric_limits<std::size_t>::max()) throw MemoryFailure(MemoryFault::overflow);
  auto staged = data_->prepare(true, tuple);auto& undo = staged.back();undo.previous_last = s.last_tuple;
  const auto result = s.insert(tuple);undo.handle = result.handle;
  undo.pin.emplace(s.arena.pin(s.by_id.find(result.handle.tuple)->second.arena));
  data_->publish(staged);return result;
}
bool AccountedReferenceTable::Journal::erase(TupleHandle handle) {
  require(bool(data_), TableProblem::invalid_journal);auto& s = data_->active();s.owned(handle);
  const auto found = s.by_id.find(handle.tuple);if (found == s.by_id.end()) return false;
  s.mutable_revision();auto staged = data_->prepare(false, s.arena.get(found->second.arena));auto& undo = staged.back();
  undo.handle = handle;undo.pin.emplace(s.arena.pin(found->second.arena));
  for (auto& key : undo.keys) {
    const auto bucket = key.index->buckets.find(key.key);
    if (bucket == key.index->buckets.end()) std::terminate();
    key.member = bucket->second.extract(handle.tuple);if (!key.member) std::terminate();
    s.lifetime<site::Member>(key.member.value(), MemoryPurpose::secondary_node, AllocationLifetime::retained);
    if (bucket->second.empty()) {
      key.bucket = key.index->buckets.extract(bucket);
      s.lifetime<site::BucketKey>(key.bucket.key(), MemoryPurpose::secondary_node, AllocationLifetime::retained);
      AccountedReferenceTable::classify(key.bucket.key(), AllocationLifetime::retained);
    }
  }
  const auto arena = found->second.arena;
  undo.primary = s.primary.extract(found->second.primary);undo.id = s.by_id.extract(found);
  s.lifetime<site::PrimaryKey>(undo.primary.key(), MemoryPurpose::primary_node, AllocationLifetime::retained);
  s.lifetime<site::ByIdKey>(undo.id.key(), MemoryPurpose::primary_node, AllocationLifetime::retained);
  if (!s.arena.erase(arena)) std::terminate();
  ++s.revision;data_->publish(staged);return true;
}
bool AccountedReferenceTable::erase(TupleHandle handle) {
  auto& s = state();s.unlocked();s.owned(handle);if (!s.by_id.contains(handle.tuple)) return false;
  auto transaction = journal();const auto erased = transaction.erase(handle);transaction.commit();return erased;
}
bool AccountedReferenceTable::erase(const AccountedTuple& tuple) {
  state().unlocked();const auto handle = find(tuple);return handle && erase(*handle);
}
IndexId AccountedReferenceTable::add_index(AccountedProjection projection) {
  auto& s = state();s.unlocked();require(s.layout.same_token(projection.source()), TableProblem::layout_mismatch);
  for (const auto& [id, index] : s.indices) if (index.projection.same_token(projection)) return id;
  s.mutable_revision();if (s.last_index == maximum) throw MemoryFailure(MemoryFault::overflow);
  State::Index index(std::move(projection), s.account, s.tag);
  for (const auto& [tuple, id] : s.primary) {
    auto key = index.projection.apply(*tuple, s.tag);auto found = index.buckets.find(key);
    if (found == index.buckets.end()) {
      State::Members members(std::less<TupleId>{}, MemoryAllocator<TupleId>(s.account, MemoryPurpose::secondary_node, s.tag));
      members.insert(id);index.buckets.emplace(std::move(key), std::move(members));
    } else found->second.insert(id);
  }
  const IndexId id{s.last_index + 1};s.indices.emplace(id, std::move(index));s.last_index = id.value;++s.revision;return id;
}
bool AccountedReferenceTable::drop_index(IndexId id) {
  auto& s = state();s.unlocked();const auto found = s.indices.find(id);if (found == s.indices.end()) return false;
  s.mutable_revision();s.indices.erase(found);++s.revision;return true;
}
AccountedVector<IndexId> AccountedReferenceTable::indices() const {
  const auto& s = state();auto result = s.output<IndexId>();reserve(result, s.indices.size());
  for (const auto& [id, index] : s.indices) { static_cast<void>(index);result.push_back(id); }return result;
}
AccountedProjection AccountedReferenceTable::projection(IndexId id) const { return state().index(id).projection; }
std::size_t AccountedReferenceTable::key_count(IndexId id) const { return state().index(id).buckets.size(); }
AccountedVector<AccountedTuple> AccountedReferenceTable::keys(IndexId id) const {
  auto& s = state();auto& index = s.index(id);auto result = s.output<AccountedTuple>();reserve(result, index.buckets.size());
  for (const auto& [key, members] : index.buckets) {
    static_cast<void>(members);result.push_back(key.layout().tuple(key.values(), s.output_tag()));
  }return result;
}
AccountedVector<TupleHandle> AccountedReferenceTable::bucket(IndexId id, const AccountedTuple& key) const {
  auto& s = state();auto& index = s.index(id);s.key(index, key);auto result = s.output<TupleHandle>();
  const auto found = index.buckets.find(key);if (found != index.buckets.end()) {
    reserve(result, found->second.size());for (const auto tuple : found->second) result.push_back(s.handle(tuple));
  }return result;
}
std::size_t AccountedReferenceTable::erase_key(IndexId id, const AccountedTuple& key) {
  state().unlocked();const auto handles = bucket(id, key);if (handles.empty()) return 0;
  auto transaction = journal();for (const auto handle : handles) if (!transaction.erase(handle)) std::terminate();
  transaction.commit();return handles.size();
}
void AccountedReferenceTable::clear() {
  auto& s = state();s.unlocked();if (s.primary.empty()) return;s.mutable_revision();
  for (auto& [id, index] : s.indices) { static_cast<void>(id);index.buckets.clear(); }
  s.by_id.clear();s.primary.clear();s.arena.clear();++s.revision;
}

struct AccountedReferenceTable::Cursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<Reader> journal;
  std::uint64_t revision;
  bool bucket_mode = false, empty = false;
  State::Primary::const_iterator primary, primary_end;
  State::Members::const_iterator member, member_end;
  explicit Data(const std::shared_ptr<State>& value) : owner(value), revision(value->revision) {}
  std::shared_ptr<State> valid() const {
    const auto state = owner.lock();require(bool(state) && state->facade_alive, TableProblem::invalid_cursor);
    require(!journal || journal->phase != Reader::Phase::aborted, TableProblem::invalid_cursor);
    if (!journal || (state->journal_active && state->active_reader.lock() != journal)) state->unlocked();
    require(state->revision == revision, TableProblem::invalid_cursor);return state;
  }
};
AccountedReferenceTable::Cursor::Cursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedReferenceTable::Cursor::Cursor(Cursor&&) noexcept = default;
AccountedReferenceTable::Cursor& AccountedReferenceTable::Cursor::operator=(Cursor&&) noexcept = default;
AccountedReferenceTable::Cursor::~Cursor() = default;
std::optional<TupleHandle> AccountedReferenceTable::Cursor::next() {
  require(bool(data_), TableProblem::invalid_cursor);const auto s = data_->valid();if (data_->empty) return {};
  if (data_->bucket_mode) {
    if (data_->member == data_->member_end) return {};
    return s->handle(*data_->member++);
  }
  if (data_->primary == data_->primary_end) return {};
  return s->handle((data_->primary++)->second);
}
std::optional<AccountedReferenceTable::Cursor::Entry> AccountedReferenceTable::Cursor::next_entry() & {
  require(bool(data_), TableProblem::invalid_cursor);const auto s = data_->valid();if (data_->empty) return {};
  if (data_->bucket_mode) {
    if (data_->member == data_->member_end) return {};
    const auto id = s->by_id.find(*data_->member++);require(id != s->by_id.end());
    return Entry{s->handle(id->first), s->arena.get(id->second.arena)};
  }
  if (data_->primary == data_->primary_end) return {};
  const auto entry = data_->primary++;return Entry{s->handle(entry->second), *entry->first};
}
AccountedReferenceTable::Cursor AccountedReferenceTable::live() const {
  auto& s = state();s.unlocked();auto data = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_);
  data->primary = s.primary.begin();data->primary_end = s.primary.end();return Cursor(std::move(data));
}
AccountedReferenceTable::Cursor AccountedReferenceTable::bucket_cursor(IndexId id, const AccountedTuple& key) const {
  auto& s = state();s.unlocked();auto& index = s.index(id);s.key(index, key);
  auto data = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_);data->bucket_mode = true;
  const auto found = index.buckets.find(key);if (found == index.buckets.end()) data->empty = true;
  else { data->member = found->second.begin();data->member_end = found->second.end(); }return Cursor(std::move(data));
}
AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::live() const {
  require(bool(data_), TableProblem::invalid_journal);auto& s = data_->active();
  auto cursor = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, data_->owner);
  cursor->journal = data_->reader;cursor->primary = s.primary.begin();cursor->primary_end = s.primary.end();return Cursor(std::move(cursor));
}
AccountedReferenceTable::Cursor AccountedReferenceTable::Journal::bucket_cursor(IndexId id, const AccountedTuple& key) const {
  require(bool(data_), TableProblem::invalid_journal);auto& s = data_->active();auto& index = s.index(id);s.key(index, key);
  auto cursor = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, data_->owner);
  cursor->journal = data_->reader;cursor->bucket_mode = true;const auto found = index.buckets.find(key);
  if (found == index.buckets.end()) cursor->empty = true;
  else { cursor->member = found->second.begin();cursor->member_end = found->second.end(); }return Cursor(std::move(cursor));
}
struct AccountedReferenceTable::IndexKeyCursor::Data {
  std::weak_ptr<State> owner;
  std::uint64_t revision;
  State::Buckets::const_iterator current, end;
  Data(const std::shared_ptr<State>& value, const State::Index& index)
      : owner(value), revision(value->revision), current(index.buckets.begin()), end(index.buckets.end()) {}
};
AccountedReferenceTable::IndexKeyCursor::IndexKeyCursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedReferenceTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
AccountedReferenceTable::IndexKeyCursor& AccountedReferenceTable::IndexKeyCursor::operator=(IndexKeyCursor&&) noexcept = default;
AccountedReferenceTable::IndexKeyCursor::~IndexKeyCursor() = default;
std::optional<AccountedReferenceTable::IndexKeyCursor::Entry> AccountedReferenceTable::IndexKeyCursor::next() & {
  require(bool(data_), TableProblem::invalid_cursor);const auto s = data_->owner.lock();
  require(bool(s) && s->facade_alive, TableProblem::invalid_cursor);s->unlocked();
  require(s->revision == data_->revision, TableProblem::invalid_cursor);if (data_->current == data_->end) return {};
  const auto& entry = *data_->current++;return Entry{entry.first, entry.second.size()};
}
AccountedReferenceTable::IndexKeyCursor AccountedReferenceTable::index_keys(IndexId id) const {
  auto& s = state();s.unlocked();auto& index = s.index(id);
  return IndexKeyCursor(resource::make_accounted_unique<IndexKeyCursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_, index));
}
AccountedVector<AccountedTuple> AccountedReferenceTable::snapshot() const {
  const auto& s = state();auto result = s.output<AccountedTuple>();reserve(result, s.primary.size());
  for (const auto& [tuple, id] : s.primary) {
    static_cast<void>(id);result.push_back(s.layout.tuple(tuple->values(), s.output_tag()));
  }return result;
}
AccountedReferenceTable AccountedReferenceTable::snapshot_copy() const {
  const auto& s = state();s.unlocked();AccountedReferenceTable result(s.relation, s.layout);auto& copy = result.state();
  for (const auto& [id, record] : s.by_id) {
    copy.last_tuple = id.value - 1;static_cast<void>(copy.insert(s.arena.get(record.arena)));
  }
  for (const auto& [id, index] : s.indices) { copy.last_index = id.value - 1;static_cast<void>(result.add_index(index.projection)); }
  copy.last_tuple = s.last_tuple;copy.last_index = s.last_index;copy.revision = s.revision;return result;
}
void AccountedReferenceTable::check_invariants() const {
  auto& s = state();s.arena.check_invariants();require(s.primary.size() == s.by_id.size() && s.primary.size() == s.arena.statistics().live_records);
  for (auto row = s.primary.begin(); row != s.primary.end(); ++row) {
    require(row->second.value > 0 && row->second.value <= s.last_tuple);s.input(*row->first);
    require(s.layout.validation_issue(row->first->values()).ok());const auto id = s.by_id.find(row->second);
    require(id != s.by_id.end() && id->second.primary == row && &s.arena.get(id->second.arena) == row->first);
  }
  for (const auto& [id, index] : s.indices) {
    require(id.value > 0 && id.value <= s.last_index && index.projection.source().same_token(s.layout));std::size_t count = 0;
    for (const auto& [key, members] : index.buckets) {
      require(index.projection.target().same_token(key.layout()) && !members.empty());
      for (const auto member : members) {
        const auto row = s.by_id.find(member);require(row != s.by_id.end() && matches(index.projection, *row->second.primary->first, key));
        require(count < s.primary.size());++count;
      }
    }
    require(count == s.primary.size());
  }
  require(s.journal_active || s.active_entries == 0);s.account.check_invariants();
}
}
