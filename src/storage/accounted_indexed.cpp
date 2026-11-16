#include "crown/storage/accounted_indexed.hpp"

#include "accounted_indexed_nodes.hpp"
#include "accounted_index_scalar_work.hpp"
#include "owner.hpp"
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
#include "accounted_indexed_testing.hpp"
#endif
#include <algorithm>
#include <exception>
#include <limits>
#include <utility>

namespace crown::storage {
// Source-private definition with namespace linkage, like the existing S02
// reader. Externally linked nested Data types must not embed an anonymous type.
struct AccountedIndexedJournalReader {
  enum class Phase { active, committed, aborted };
  Phase phase = Phase::active;
  AccountedIndexWork work;
  explicit AccountedIndexedJournalReader(AccountedIndexWork grant) noexcept
      : work(std::move(grant)) {}
};
namespace {
using detail::AccountedIndexedIndex;
using resource::MemoryAccount;
using resource::MemoryAllocator;
using resource::MemoryAttribution;
using resource::MemoryPurpose;
using resource::AllocationLifetime;
using detail::destroy_indexed_node;
using detail::classify_indexed_node;
using detail::IndexedNodeOwner;
using detail::AccountedIndexedKey;
using detail::AccountedIndexedMember;
using detail::AccountedIndexedRow;

void contract(bool value, const char* /*message*/) {
  if (!value) throw IndexFailure(IndexFault::contract);
}
void room(std::size_t current, std::size_t extra, std::size_t maximum) {
  if (current > maximum || extra > maximum - current)
    throw IndexFailure(IndexFault::capacity);
}
void counter_room(std::uint64_t current, std::uint64_t extra = 1) {
  if (extra > std::numeric_limits<std::uint64_t>::max() - current)
    throw IndexFailure(IndexFault::overflow);
}
std::uint64_t work_product(std::size_t count, std::uint64_t cost) {
  const auto value = static_cast<std::uint64_t>(count);
  if (cost != 0 && value > std::numeric_limits<std::uint64_t>::max() / cost)
    throw IndexFailure(IndexFault::overflow);
  return value * cost;
}
void start(IndexWorkAllowance& work) {
  if (!work.fixed_diagnostics()) throw IndexFailure(IndexFault::contract);
  work.admit(IndexWork{.structural_steps = 1});
}
template <class T>
void reserve_records(AccountedVector<T>& records, std::size_t count, IndexWorkAllowance& work) {
  if (count > records.max_size()) throw IndexFailure(IndexFault::overflow);
  constexpr auto words = static_cast<std::uint64_t>(sizeof(T) / sizeof(void*) + (sizeof(T) % sizeof(void*) != 0));
  work.admit(IndexWork{.pointer_slots = work_product(count, words)});
  records.reserve(count);
}
}  // namespace

struct AccountedIndexedTable::State {
  MemoryAccount account;
  StorageOwnerId owner;
  MemoryAttribution tag{resource::MemoryOwnerKind::storage_table, owner.value};
  RelationId relation;
  AccountedLayout layout;
  IndexedLimits limits;
  AccountedTupleArena arena;
  detail::AccountedPrimaryDirectory primary;
  detail::AccountedRowIdDirectory by_id;
  detail::AccountedIndexIdDirectory indices;
  std::size_t key_nodes = 0, live_key_nodes = 0, member_nodes = 0;
  std::size_t nodes = 0, directory_slots = 0;
  std::uint64_t last_tuple = 0, last_index = 0, revision = 0;
  IndexedActions committed;
  std::size_t copied_rows = 0, copied_indices = 0;
  bool journal_active = false, facade_alive = true;
  std::size_t retained_history = 0;
  std::weak_ptr<AccountedIndexedJournalReader> active_reader;
  Journal::Data* active_journal = nullptr;
  std::size_t retained_rows = 0, retained_members = 0, journal_entries = 0;
  std::uint64_t pending_inserted = 0, pending_erased = 0;
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
  detail::AccountedCollisionMode collision_mode = detail::AccountedCollisionMode::native;
#endif

  State(const MemoryAccount& query, StorageOwnerId identity, RelationId value, AccountedLayout schema, IndexedLimits configuration)
      : account(query), owner(identity), relation(value), layout(std::move(schema)), limits(configuration), arena(layout),
        primary(limits.directory_slots, MemoryAllocator<AccountedIndexedRow*>(account, MemoryPurpose::directory, tag)),
        by_id(limits.directory_slots, MemoryAllocator<AccountedIndexedRow*>(account, MemoryPurpose::directory, tag)),
        indices(limits.directory_slots, MemoryAllocator<AccountedIndexedIndex*>(account, MemoryPurpose::directory, tag)) {}
  template<class T> AccountedVector<T> vector(MemoryPurpose purpose = MemoryPurpose::scratch) const {
    return AccountedVector<T>(MemoryAllocator<T>(account, purpose, tag));
  }
  MemoryAttribution output_tag() const noexcept { return {resource::MemoryOwnerKind::output, owner.value}; }
  template<class T> AccountedVector<T> output() const {
    return AccountedVector<T>(MemoryAllocator<T>(account, MemoryPurpose::output_buffer, output_tag()));
  }
  ~State() {
    // Destroy nodes while all actual hook owners are still alive. Neither
    // directory capacity nor historical logical IDs are scanned here.
    while (auto* row = primary.first_resident()) destroy_indexed_node(row);
    while (auto* index = indices.first_resident()) destroy_indexed_node(index);
  }
  void input(const AccountedTuple& tuple) const {
    if (!layout.same_token(tuple.layout()))
      throw IndexFailure(IndexFault::layout_mismatch);
  }
  void owned(TupleHandle handle) const {
    if (handle.owner != owner || handle.relation != relation)
      throw IndexFailure(IndexFault::foreign_handle);
  }
  void mutable_revision() const { counter_room(revision); }
  void unlocked() const {
    if (journal_active) throw IndexFailure(IndexFault::busy);
  }
  TupleHandle handle(const AccountedIndexedRow& row) const noexcept { return {owner, relation, row.id}; }
  std::uint64_t transform_hash(std::uint64_t value) const noexcept {
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
    if (collision_mode == detail::AccountedCollisionMode::same_full_hash) return 0;
    if (collision_mode == detail::AccountedCollisionMode::same_bucket) return value & ~std::uint64_t{0xffff};
#endif
    return value;
  }
  std::uint64_t hash(const AccountedTuple& value, IndexWorkAllowance& work) const {
    return transform_hash(detail::accounted_admitted_hash(value, work));
  }
  std::uint64_t diagnostic_hash(const AccountedTuple& value) const { return transform_hash(value.hash()); }
  AccountedIndexedRow* row(TupleHandle value, IndexWorkAllowance& work) const {
    owned(value);
    return by_id.find(value.tuple.value, [&](const AccountedIndexedRow& candidate, IndexWorkAllowance&) {
      return candidate.id == value.tuple;
    }, work);
  }
  AccountedIndexedRow* row(const AccountedTuple& value, IndexWorkAllowance& work) const {
    input(value);const auto value_hash = hash(value, work);
    return primary.find(value_hash, [&](const AccountedIndexedRow& candidate, IndexWorkAllowance& allowance) {
      return detail::accounted_admitted_equal(*candidate.tuple, value, allowance);
    }, work);
  }
  AccountedIndexedIndex* maybe_index(IndexId id, IndexWorkAllowance& work) const {
    return indices.find(id.value, [&](const AccountedIndexedIndex& candidate, IndexWorkAllowance&) {
      return candidate.id == id;
    }, work);
  }
  AccountedIndexedIndex& index(IndexId id, IndexWorkAllowance& work) const {
    auto* found = maybe_index(id, work);
    if (found == nullptr) throw IndexFailure(IndexFault::unknown_index);
    return *found;
  }
  AccountedIndexedKey* key(AccountedIndexedIndex& index, const AccountedTuple& value, IndexWorkAllowance& work) const {
    if (!index.projection.target().same_token(value.layout()))
      throw IndexFailure(IndexFault::layout_mismatch);
    const auto value_hash = hash(value, work);
    return index.keys.find(value_hash, [&](const AccountedIndexedKey& candidate, IndexWorkAllowance& allowance) {
      return detail::accounted_admitted_equal(candidate.tuple, value, allowance);
    }, work);
  }
  std::size_t slot_room(std::size_t pending = 0) const {
    room(directory_slots, pending, limits.directory_slots);
    return limits.directory_slots - directory_slots - pending;
  }
  void arena_insert_room() const {
    const auto counts = arena.statistics();
    if (counts.free_slots == 0) room(counts.slots, 1, limits.arena_slots);
  }
  void prepare_erase(const AccountedIndexedRow& row, IndexWorkAllowance& work) const;
  void erase_prepaid(AccountedIndexedRow& row) noexcept;
  void erase_one(AccountedIndexedRow& row, IndexWorkAllowance& work);
};

#include "accounted_indexed_journal.inc"

MemoryAccount AccountedIndexedTable::account_for(const AccountedLayout& layout) { return layout.query_account(); }
void AccountedIndexedTable::classify(AccountedTuple& tuple, AllocationLifetime lifetime) noexcept { tuple.set_lifetime(lifetime); }
AccountedIndexedTable::AccountedIndexedTable(RelationId relation, AccountedLayout layout, IndexedLimits limits) {
  if (!layout) throw IndexFailure(IndexFault::layout_mismatch);
  auto account = account_for(layout);const auto owner = detail::try_new_storage_owner();
  if (!owner) throw IndexFailure(IndexFault::overflow);
  state_ = resource::make_accounted_shared<State>({resource::MemoryOwnerKind::storage_table, owner->value}, account,
      MemoryPurpose::table_state, account, *owner, relation, std::move(layout), limits);
}
AccountedIndexedTable::~AccountedIndexedTable() { if (state_) state_->facade_alive = false; }
AccountedIndexedTable::AccountedIndexedTable(AccountedIndexedTable&&) noexcept = default;
AccountedIndexedTable& AccountedIndexedTable::operator=(AccountedIndexedTable&& other) noexcept {
  if (this != &other) { if (state_) state_->facade_alive = false;state_ = std::move(other.state_); }return *this;
}
AccountedIndexedTable::State& AccountedIndexedTable::state() const {
  if (!state_) throw IndexFailure(IndexFault::invalid_storage);
  return *state_;
}
StorageOwnerId AccountedIndexedTable::owner() const { return state().owner; }
RelationId AccountedIndexedTable::relation() const { return state().relation; }
const AccountedLayout& AccountedIndexedTable::layout() const & { return state().layout; }
const IndexedLimits& AccountedIndexedTable::limits() const & { return state().limits; }
std::size_t AccountedIndexedTable::size() const { return state().primary.size(); }
std::uint64_t AccountedIndexedTable::revision() const { return state().revision; }
ArenaStatistics AccountedIndexedTable::arena_statistics() const { return state().arena.statistics(); }
IndexedStatistics AccountedIndexedTable::statistics() const {
  const auto& s = state();
  return {s.primary.size(), s.indices.size(), s.key_nodes, s.live_key_nodes,
          s.member_nodes, s.nodes, s.directory_slots, s.arena.statistics(), s.committed,
          s.copied_rows, s.copied_indices, s.retained_rows, s.retained_members,
          s.journal_entries, IndexedActions{s.pending_inserted, s.pending_erased}};
}
// Explicit report: table/arena attribution scans the account ledger, arena
// reporting visits slot high-water, and directory totals visit resident indices.
AccountedIndexedMemoryStatistics AccountedIndexedTable::memory_statistics() const {
  const auto& s = state();AccountedIndexedMemoryStatistics result;
  result.records = statistics();result.table = s.account.statistics_for(s.tag);
  result.arena = s.arena.memory_statistics();result.retained_history_entries = s.retained_history;
  const auto add = [](resource::MemoryUsage& to, resource::MemoryUsage value) {
    to.allocations += value.allocations;to.requested_bytes += value.requested_bytes;to.payload_bytes += value.payload_bytes;
  };
  for (const auto usage : {s.primary.allocation_usage(), s.by_id.allocation_usage(), s.indices.allocation_usage()}) add(result.directories, usage);
  for (auto* index = s.indices.first_resident(); index; index = detail::AccountedIndexIdDirectory::next_resident(*index))
    add(result.directories, index->keys.allocation_usage());
  result.owned = result.table.current;add(result.owned, result.arena.owner.current);return result;
}

InsertResult AccountedIndexedTable::insert(const AccountedTuple& tuple, IndexWorkAllowance& work) {
  return insert_impl(state_, tuple, work, nullptr);
}
InsertResult AccountedIndexedTable::insert_impl(const std::shared_ptr<State>& owner, const AccountedTuple& tuple, IndexWorkAllowance& work, Journal::Data* journal) {
  if (!owner) throw IndexFailure(IndexFault::invalid_storage);
  auto& s = *owner;if (journal == nullptr) s.unlocked();start(work);s.input(tuple);
  const auto hash = s.hash(tuple, work);
  if (const auto* found = s.primary.find(hash, [&](const AccountedIndexedRow& candidate, IndexWorkAllowance& grant) {
      return detail::accounted_admitted_equal(*candidate.tuple, tuple, grant);
    }, work)) return {false, s.handle(*found)};
  s.mutable_revision();counter_room(s.last_tuple);
  counter_room(s.pending_inserted);counter_room(s.committed.inserted_rows, s.pending_inserted + 1);
  room(s.primary.size() + s.retained_rows, 1, s.limits.rows);room(s.nodes, 1, s.limits.nodes);
  room(s.member_nodes, s.indices.size(), s.limits.memberships);
  room(s.nodes + 1, s.indices.size(), s.limits.nodes);
  s.arena_insert_room();
  Journal::Data::Prepared undo(s.account, s.tag);
  if (journal != nullptr) {
    room(s.arena.statistics().pins, 1, s.limits.arena_pins);
    undo = journal->prepare(true);undo->previous_last = s.last_tuple;
    work.admit(IndexWork{.structural_steps = 1 + work_product(s.indices.size(), 4),
        .link_actions = detail::AccountedPrimaryDirectory::unlink_actions + detail::AccountedRowIdDirectory::unlink_actions});
    work.admit(IndexWork{.link_actions = work_product(s.indices.size(),
        detail::AccountedRowMembers::erase_actions + detail::AccountedBucketMembers::erase_actions +
        detail::AccountedLiveKeys::erase_actions + detail::AccountedKeyDirectory::unlink_actions)});
  }
  auto primary_growth = s.primary.prepare_growth(s.primary.size() + 1, work, s.slot_room());
  std::size_t added_slots = primary_growth.new_capacity() - s.primary.capacity();
  auto id_growth = s.by_id.prepare_growth(s.by_id.size() + 1, work, s.slot_room(added_slots));
  added_slots += id_growth.new_capacity() - s.by_id.capacity();
  work.admit(IndexWork{.structural_steps = static_cast<std::uint64_t>(s.indices.size()),
      .link_actions = detail::AccountedPrimaryDirectory::link_actions + detail::AccountedRowIdDirectory::link_actions});
  auto row = detail::make_indexed_node<AccountedIndexedRow>(s.account, s.tag, MemoryPurpose::primary_node, TupleId{s.last_tuple + 1}, s.limits.indices);
  struct Prepared {
    AccountedIndexedIndex* index;
    AccountedIndexedKey* key;
    IndexedNodeOwner<AccountedIndexedKey> created;
    std::optional<detail::AccountedKeyDirectory::Growth> growth;
  };
  auto prepared = s.vector<Prepared>();reserve_records(prepared, s.indices.size(), work);
  std::size_t added_keys = 0, activated_keys = 0;
  for (auto* index = s.indices.first_resident(); index != nullptr;
       index = detail::AccountedIndexIdDirectory::next_resident(*index)) {
    auto projected = detail::accounted_admitted_projection(index->projection, tuple, work, s.tag);
    const auto key_hash = s.hash(projected, work);
    auto* key = index->keys.find(key_hash, [&](const AccountedIndexedKey& candidate, IndexWorkAllowance& grant) {
      return detail::accounted_admitted_equal(candidate.tuple, projected, grant);
    }, work);
    Prepared item{index, key, {}, {}};
    if (key == nullptr) {
      room(s.key_nodes, added_keys + 1, s.limits.keys);
      room(s.nodes + 1 + s.indices.size(), added_keys + 1, s.limits.nodes);
      item.created = detail::make_indexed_node<AccountedIndexedKey>(s.account, s.tag, MemoryPurpose::secondary_node, std::move(projected), s.limits.rows);
      item.key = item.created.get();
      item.growth.emplace(index->keys.prepare_growth(index->keys.size() + 1, work, s.slot_room(added_slots)));
      added_slots += item.growth->new_capacity() - index->keys.capacity();
      work.admit(IndexWork{.link_actions = detail::AccountedKeyDirectory::link_actions});
      ++added_keys;
    }
    if (item.key->members.size() == 0) {
      index->live_keys.prepare_insert(work);++activated_keys;
    }
    row->members.prepare_insert(work);item.key->members.prepare_insert(work);
    auto member = detail::make_indexed_node<AccountedIndexedMember>(s.account, s.tag, MemoryPurpose::secondary_node, *row, *index, *item.key);
    if (undo) {
      room(item.key->journal_references, 1, s.limits.journal_entries);
      detail::accounted_admit_tuple_copy(item.key->tuple, work);
      undo->keys.push_back({item.key, member.get(), nullptr, nullptr, nullptr, nullptr});
    }
    row->members.append_prepaid(*member);static_cast<void>(member.release());
    // A new key's cached hash is set while private; publication never hashes.
    if (item.created) item.created->lookup_link.hash = key_hash;
    prepared.push_back(std::move(item));
  }
  detail::accounted_admit_tuple_copy(tuple, work);
  row->allocation = s.arena.insert(tuple);row->tuple = &s.arena.get(row->allocation);
  if (undo) {
    // A valid fresh allocation and admitted total pin room make this a
    // nonallocating pin increment; no formatter/lookup/admission follows it.
    undo->pin.emplace(s.arena.pin(row->allocation));undo->row = row.get();
    undo->handle = s.handle(*row);
  }
  // All throwing work and admission are complete. The exact allocation above
  // remains live; the following phase contains pointer changes and counters.
  s.primary.publish_growth(std::move(primary_growth));s.by_id.publish_growth(std::move(id_growth));
  for (auto& item : prepared) {
    if (item.created) {
      item.index->keys.publish_growth(std::move(*item.growth));
      const auto key_hash = item.created->lookup_link.hash;
      item.index->keys.link_prepaid(*item.created, key_hash);
      static_cast<void>(item.created.release());
    }
  }
  for (auto* member = row->members.first(); member != nullptr; member = detail::AccountedRowMembers::next(*member)) {
    if (member->key->members.size() == 0) {
      member->index->live_keys.append_prepaid(*member->key);
      classify_indexed_node(*member->key, AllocationLifetime::active);classify(member->key->tuple, AllocationLifetime::active);
    }
    member->key->members.append_prepaid(*member);
  }
  const auto result = s.handle(*row);
  s.primary.link_prepaid(*row, hash);s.by_id.link_prepaid(*row, row->id.value);
  static_cast<void>(row.release());
  s.key_nodes += added_keys;s.live_key_nodes += activated_keys;s.member_nodes += s.indices.size();
  s.nodes += 1 + s.indices.size() + added_keys;s.directory_slots += added_slots;
  ++s.last_tuple;++s.revision;
  if (undo) { ++s.pending_inserted;journal->publish(std::move(undo)); }
  else ++s.committed.inserted_rows;
  return {true, result};
}

// Low-level probes may see tentative rows. Callers supply any read lease
// or isolation boundary; ordinary writers and cursor factories enforce the
// exclusive-journal guard separately.
std::optional<TupleHandle> AccountedIndexedTable::find(const AccountedTuple& tuple, IndexWorkAllowance& work) const {
  auto& s = state();start(work);const auto* row = s.row(tuple, work);
  if (row == nullptr) return {};
  return s.handle(*row);
}
const AccountedTuple* AccountedIndexedTable::get(TupleHandle handle, IndexWorkAllowance& work) const & {
  auto& s = state();start(work);const auto* row = s.row(handle, work);
  return row == nullptr ? nullptr : row->tuple;
}
AccountedTupleArena::Pin AccountedIndexedTable::pin(TupleHandle handle, IndexWorkAllowance& work) const {
  auto& s = state();start(work);const auto* row = s.row(handle, work);
  if (row == nullptr) throw IndexFailure(IndexFault::stale_handle);
  room(s.arena.statistics().pins, 1, s.limits.arena_pins);
  return s.arena.pin(row->allocation);
}

void AccountedIndexedTable::State::prepare_erase(const AccountedIndexedRow& row, IndexWorkAllowance& work) const {
  start(work);
  work.admit(IndexWork{.link_actions = detail::AccountedPrimaryDirectory::unlink_actions + detail::AccountedRowIdDirectory::unlink_actions});
  detail::accounted_admit_tuple_copy(*row.tuple, work); // Conservative retirement allowance.
  for (auto* member = row.members.first(); member != nullptr; member = detail::AccountedRowMembers::next(*member)) {
    row.members.prepare_erase(*member, work);member->key->members.prepare_erase(*member, work);
    // A bulk erase can empty a key only after other rows have been removed.
    // Reserve potential final-key cleanup for every affected member up front.
    work.admit(IndexWork{.link_actions = detail::AccountedKeyDirectory::unlink_actions + detail::AccountedLiveKeys::erase_actions});
    detail::accounted_admit_tuple_copy(member->key->tuple, work);
  }
}
void AccountedIndexedTable::State::erase_prepaid(AccountedIndexedRow& row) noexcept {
  while (auto* member = row.members.first()) {
    auto* key = member->key;destroy_indexed_node(member);--member_nodes;--nodes;
    if (key->members.size() == 0) {
      destroy_indexed_node(key);--key_nodes;--live_key_nodes;--nodes;
    }
  }
  if (!arena.erase(row.allocation)) std::terminate();
  destroy_indexed_node(&row);--nodes;
}
void AccountedIndexedTable::State::erase_one(AccountedIndexedRow& row, IndexWorkAllowance& work) {
  mutable_revision();counter_room(committed.erased_rows);prepare_erase(row, work);
  erase_prepaid(row);++revision;++committed.erased_rows;
}
bool AccountedIndexedTable::erase(const AccountedTuple& tuple, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* row = s.row(tuple, work);
  if (row == nullptr) return false;
  s.erase_one(*row, work);return true;
}
bool AccountedIndexedTable::erase(TupleHandle handle, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* row = s.row(handle, work);
  if (row == nullptr) return false;
  s.erase_one(*row, work);return true;
}

IndexId AccountedIndexedTable::add_index(AccountedProjection projection, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);
  if (!s.layout.same_token(projection.source()))
    throw IndexFailure(IndexFault::layout_mismatch);
  for (auto* existing = s.indices.first_resident(); existing != nullptr;
       existing = detail::AccountedIndexIdDirectory::next_resident(*existing)) {
    start(work);
    if (existing->projection.same_token(projection)) return existing->id;
  }
  s.mutable_revision();counter_room(s.last_index);counter_room(s.committed.added_indices);
  room(s.indices.size(), 1, s.limits.indices);room(s.nodes, 1, s.limits.nodes);
  room(s.member_nodes, s.primary.size(), s.limits.memberships);
  room(s.nodes + 1, s.primary.size(), s.limits.nodes);
  auto id_growth = s.indices.prepare_growth(s.indices.size() + 1, work, s.slot_room());
  const auto id_slots = id_growth.new_capacity() - s.indices.capacity();
  auto index = detail::make_indexed_node<AccountedIndexedIndex>(s.account, s.tag, MemoryPurpose::secondary_node, IndexId{s.last_index + 1}, std::move(projection),
      s.limits.directory_slots, s.limits.keys);
  auto members = s.vector<IndexedNodeOwner<AccountedIndexedMember>>();reserve_records(members, s.primary.size(), work);
  work.admit(IndexWork{.link_actions = detail::AccountedIndexIdDirectory::link_actions});
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::AccountedPrimaryDirectory::next_resident(*row)) {
    start(work);
    auto projected = detail::accounted_admitted_projection(index->projection, *row->tuple, work, s.tag);
    const auto hash = s.hash(projected, work);
    auto* key = index->keys.find(hash, [&](const AccountedIndexedKey& candidate, IndexWorkAllowance& grant) {
      return detail::accounted_admitted_equal(candidate.tuple, projected, grant);
    }, work);
    if (key == nullptr) {
      room(s.key_nodes, index->keys.size() + 1, s.limits.keys);
      room(s.nodes + 1 + s.primary.size(), index->keys.size() + 1, s.limits.nodes);
      auto created = detail::make_indexed_node<AccountedIndexedKey>(s.account, s.tag, MemoryPurpose::secondary_node, std::move(projected), s.limits.rows);
      auto growth = index->keys.prepare_growth(index->keys.size() + 1, work,
          s.slot_room(id_slots + index->keys.capacity()));
      index->live_keys.prepare_insert(work);
      work.admit(IndexWork{.link_actions = detail::AccountedKeyDirectory::link_actions});
      index->keys.publish_growth(std::move(growth));index->keys.link_prepaid(*created, hash);
      index->live_keys.append_prepaid(*created);key = created.release();
    }
    row->members.prepare_insert(work);key->members.prepare_insert(work);
    auto member = detail::make_indexed_node<AccountedIndexedMember>(s.account, s.tag, MemoryPurpose::secondary_node, *row, *index, *key);
    key->members.append_prepaid(*member);members.push_back(std::move(member));
  }
  const auto key_count = index->keys.size();
  const auto added_slots = id_slots + index->keys.capacity();
  const auto id = index->id;
  // The complete index and all bucket links are private. Only these row links
  // and the index identity are published now, with no throwing work remaining.
  s.indices.publish_growth(std::move(id_growth));
  for (auto& member : members) {
    member->row->members.append_prepaid(*member);static_cast<void>(member.release());
  }
  s.indices.link_prepaid(*index, id.value);static_cast<void>(index.release());
  s.key_nodes += key_count;s.live_key_nodes += key_count;s.member_nodes += s.primary.size();
  s.nodes += 1 + s.primary.size() + key_count;s.directory_slots += added_slots;
  ++s.last_index;++s.revision;++s.committed.added_indices;
  return id;
}

bool AccountedIndexedTable::drop_index(IndexId id, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* index = s.maybe_index(id, work);
  if (index == nullptr) return false;
  s.mutable_revision();counter_room(s.committed.dropped_indices);
  work.admit(IndexWork{.link_actions = detail::AccountedIndexIdDirectory::unlink_actions});
  std::size_t members = 0;
  for (auto* key = index->keys.first_resident(); key != nullptr;
       key = detail::AccountedKeyDirectory::next_resident(*key)) {
    start(work);detail::accounted_admit_tuple_copy(key->tuple, work);
    work.admit(IndexWork{.link_actions = detail::AccountedKeyDirectory::unlink_actions + detail::AccountedLiveKeys::erase_actions});
    for (auto* member = key->members.first(); member != nullptr; member = detail::AccountedBucketMembers::next(*member)) {
      member->row->members.prepare_erase(*member, work);key->members.prepare_erase(*member, work);
      room(members, 1, s.member_nodes);++members;
    }
  }
  const auto keys = index->keys.size(), live_keys = index->live_keys.size(), slots = index->keys.capacity();
  destroy_indexed_node(index);
  s.key_nodes -= keys;s.live_key_nodes -= live_keys;s.member_nodes -= members;
  s.nodes -= 1 + keys + members;s.directory_slots -= slots;
  ++s.revision;++s.committed.dropped_indices;return true;
}
AccountedVector<IndexId> AccountedIndexedTable::indices(IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto result = s.output<IndexId>();reserve_records(result, s.indices.size(), work);
  for (auto* index = s.indices.first_resident(); index != nullptr;
       index = detail::AccountedIndexIdDirectory::next_resident(*index)) {
    start(work);result.push_back(index->id);
  }
  return result;
}
AccountedProjection AccountedIndexedTable::projection(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);return s.index(id, work).projection;
}
std::size_t AccountedIndexedTable::key_count(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);return s.index(id, work).live_keys.size();
}
AccountedVector<AccountedTuple> AccountedIndexedTable::keys(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto& index = s.index(id, work);
  auto result = s.output<AccountedTuple>();reserve_records(result, index.live_keys.size(), work);
  for (auto* key = index.live_keys.first(); key != nullptr; key = detail::AccountedLiveKeys::next(*key)) {
    start(work);detail::accounted_admit_tuple_copy(key->tuple, work);result.push_back(key->tuple.layout().tuple(key->tuple.values(), s.output_tag()));
  }
  return result;
}
AccountedVector<TupleHandle> AccountedIndexedTable::bucket(IndexId id, const AccountedTuple& value, IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  auto result = s.output<TupleHandle>();
  if (key == nullptr) return result;
  reserve_records(result, key->members.size(), work);
  for (auto* member = key->members.first(); member != nullptr; member = detail::AccountedBucketMembers::next(*member)) {
    start(work);result.push_back(s.handle(*member->row));
  }
  return result;
}
std::size_t AccountedIndexedTable::erase_key(IndexId id, const AccountedTuple& value, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);auto* key = s.key(index, value, work);
  if (key == nullptr) return 0;
  s.mutable_revision();counter_room(s.committed.erased_rows, static_cast<std::uint64_t>(key->members.size()));
  auto rows = s.vector<AccountedIndexedRow*>();reserve_records(rows, key->members.size(), work);
  for (auto* member = key->members.first(); member != nullptr; member = detail::AccountedBucketMembers::next(*member)) {
    s.prepare_erase(*member->row, work);rows.push_back(member->row);
  }
  for (auto* row : rows) s.erase_prepaid(*row);
  ++s.revision;s.committed.erased_rows += static_cast<std::uint64_t>(rows.size());return rows.size();
}
void AccountedIndexedTable::clear(IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);const auto count = s.primary.size();
  if (count == 0) return;
  s.mutable_revision();counter_room(s.committed.clears);
  counter_room(s.committed.erased_rows, static_cast<std::uint64_t>(count));
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::AccountedPrimaryDirectory::next_resident(*row)) s.prepare_erase(*row, work);
  while (auto* row = s.primary.first_resident()) s.erase_prepaid(*row);
  ++s.revision;++s.committed.clears;s.committed.erased_rows += static_cast<std::uint64_t>(count);
}
AccountedVector<AccountedTuple> AccountedIndexedTable::snapshot(IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto result = s.output<AccountedTuple>();reserve_records(result, s.primary.size(), work);
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::AccountedPrimaryDirectory::next_resident(*row)) {
    start(work);detail::accounted_admit_tuple_copy(*row->tuple, work);result.push_back(s.layout.tuple(row->tuple->values(), s.output_tag()));
  }
  return result;
}

struct AccountedIndexedTable::Cursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<AccountedIndexedJournalReader> journal;
  std::uint64_t revision;
  bool bucket_mode = false;
  AccountedIndexedRow* next_row = nullptr;
  AccountedIndexedMember* next_member = nullptr;
  explicit Data(const std::shared_ptr<State>& state) : owner(state), revision(state->revision) {}
};
AccountedIndexedTable::Cursor::Cursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedIndexedTable::Cursor::Cursor(Cursor&&) noexcept = default;
AccountedIndexedTable::Cursor& AccountedIndexedTable::Cursor::operator=(Cursor&&) noexcept = default;
AccountedIndexedTable::Cursor::~Cursor() = default;
std::optional<AccountedIndexedTable::Cursor::Entry> AccountedIndexedTable::Cursor::next(IndexWorkAllowance& work) & {
  if (!data_) throw IndexFailure(IndexFault::invalid_cursor);
  const auto owner = data_->owner.lock();
  if (!owner || !owner->facade_alive) throw IndexFailure(IndexFault::invalid_cursor);
  if (data_->journal && data_->journal->phase == AccountedIndexedJournalReader::Phase::aborted)
    throw IndexFailure(IndexFault::invalid_cursor);
  if (data_->journal && data_->journal->work.get() != &work)
    throw IndexFailure(IndexFault::contract);
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock() != data_->journal))
    owner->unlocked();
  if (owner->revision != data_->revision)
    throw IndexFailure(IndexFault::invalid_cursor);
  start(work); // A denial leaves both the cursor position and owner unchanged.
  AccountedIndexedRow* row = nullptr;
  if (data_->bucket_mode) {
    if (data_->next_member == nullptr) return {};
    row = data_->next_member->row;
    data_->next_member = detail::AccountedBucketMembers::next(*data_->next_member);
  } else {
    if (data_->next_row == nullptr) return {};
    row = data_->next_row;data_->next_row = detail::AccountedPrimaryDirectory::next_resident(*row);
  }
  return Entry{owner->handle(*row), *row->tuple};
}
AccountedIndexedTable::Cursor AccountedIndexedTable::live(IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_);data->next_row = s.primary.first_resident();
  return Cursor(std::move(data));
}
AccountedIndexedTable::Cursor AccountedIndexedTable::bucket_cursor(IndexId id, const AccountedTuple& value, IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_);data->bucket_mode = true;
  if (key != nullptr) data->next_member = key->members.first();
  return Cursor(std::move(data));
}
struct AccountedIndexedTable::IndexKeyCursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<AccountedIndexedJournalReader> journal;
  std::uint64_t revision;
  AccountedIndexedKey* next_key = nullptr;
  explicit Data(const std::shared_ptr<State>& state) : owner(state), revision(state->revision) {}
};
AccountedIndexedTable::IndexKeyCursor::IndexKeyCursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedIndexedTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
AccountedIndexedTable::IndexKeyCursor& AccountedIndexedTable::IndexKeyCursor::operator=(IndexKeyCursor&&) noexcept = default;
AccountedIndexedTable::IndexKeyCursor::~IndexKeyCursor() = default;
std::optional<AccountedIndexedTable::IndexKeyCursor::Entry> AccountedIndexedTable::IndexKeyCursor::next(IndexWorkAllowance& work) & {
  if (!data_) throw IndexFailure(IndexFault::invalid_cursor);
  const auto owner = data_->owner.lock();
  if (!owner || !owner->facade_alive) throw IndexFailure(IndexFault::invalid_cursor);
  if (data_->journal && data_->journal->phase == AccountedIndexedJournalReader::Phase::aborted)
    throw IndexFailure(IndexFault::invalid_cursor);
  if (data_->journal && data_->journal->work.get() != &work)
    throw IndexFailure(IndexFault::contract);
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock() != data_->journal))
    owner->unlocked();
  if (owner->revision != data_->revision)
    throw IndexFailure(IndexFault::invalid_cursor);
  start(work);
  if (data_->next_key == nullptr) return {};
  auto* key = data_->next_key;data_->next_key = detail::AccountedLiveKeys::next(*key);
  return Entry{key->tuple, key->members.size()};
}
AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::index_keys(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(IndexKeyCursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = resource::make_accounted_unique<IndexKeyCursor::Data>(s.tag, s.account, MemoryPurpose::cursor, state_);data->next_key = index.live_keys.first();
  return IndexKeyCursor(std::move(data));
}

AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::live() const {
  if (!data_) throw IndexFailure(IndexFault::invalid_journal);
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, data_->owner);cursor->journal = data_->reader;
  cursor->next_row = s.primary.first_resident();return Cursor(std::move(cursor));
}
AccountedIndexedTable::Cursor AccountedIndexedTable::Journal::bucket_cursor(IndexId id, const AccountedTuple& value) const {
  if (!data_) throw IndexFailure(IndexFault::invalid_journal);
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = resource::make_accounted_unique<Cursor::Data>(s.tag, s.account, MemoryPurpose::cursor, data_->owner);cursor->journal = data_->reader;
  cursor->bucket_mode = true;if (key != nullptr) cursor->next_member = key->members.first();
  return Cursor(std::move(cursor));
}
AccountedIndexedTable::IndexKeyCursor AccountedIndexedTable::Journal::index_keys(IndexId id) const {
  if (!data_) throw IndexFailure(IndexFault::invalid_journal);
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);auto& index = s.index(id, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(IndexKeyCursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = resource::make_accounted_unique<IndexKeyCursor::Data>(s.tag, s.account, MemoryPurpose::cursor, data_->owner);cursor->journal = data_->reader;
  cursor->next_key = index.live_keys.first();return IndexKeyCursor(std::move(cursor));
}

AccountedIndexedTable AccountedIndexedTable::snapshot_copy(IndexWorkAllowance& work) const {
  const auto& source = state();source.unlocked();start(work);
  constexpr auto state_words = static_cast<std::uint64_t>((sizeof(State) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = state_words});
  AccountedIndexedTable result(source.relation, source.layout, source.limits);
  auto& copy = result.state();std::uint64_t previous = 0;
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
  copy.collision_mode = source.collision_mode;
#endif
  for (auto* row = source.primary.first_resident(); row != nullptr;
       row = detail::AccountedPrimaryDirectory::next_resident(*row)) {
    start(work);contract(row->id.value > previous, "copy source row IDs are not in logical insertion order");
    // This is a private checked builder, not a public raw-ID constructor.
    copy.last_tuple = row->id.value - 1;
    const auto inserted = result.insert(*row->tuple, work);
    contract(inserted.inserted && inserted.handle.tuple == row->id, "owning copy renumbered a live tuple");
    previous = row->id.value;
  }
  previous = 0;
  for (auto* index = source.indices.first_resident(); index != nullptr;
       index = detail::AccountedIndexIdDirectory::next_resident(*index)) {
    start(work);contract(index->id.value > previous, "copy source index IDs are not ordered");
    copy.last_index = index->id.value - 1;
    contract(result.add_index(index->projection, work) == index->id, "owning copy renumbered an index");
    auto& destination = copy.index(index->id, work);
    auto order = copy.vector<AccountedIndexedKey*>();reserve_records(order, index->live_keys.size(), work);
    for (auto* key = index->live_keys.first(); key != nullptr; key = detail::AccountedLiveKeys::next(*key)) {
      start(work);auto* found = copy.key(destination, key->tuple, work);
      contract(found != nullptr && found->members.size() == key->members.size(), "owning copy changed a live bucket");
      order.push_back(found);
    }
    contract(order.size() == destination.live_keys.size(), "owning copy changed the live key population");
    // Rebuilding from today's row order can change an older still-live key's
    // position. Restore the actual source list after every lookup is prepared.
    work.admit(IndexWork{.structural_steps = work_product(order.size(), 2),
        .link_actions = work_product(order.size(), detail::AccountedLiveKeys::erase_actions + detail::AccountedLiveKeys::insert_actions)});
    while (auto* key = destination.live_keys.first()) destination.live_keys.erase_prepaid(*key);
    for (auto* key : order) destination.live_keys.append_prepaid(*key);
    previous = index->id.value;
  }
  copy.last_tuple = source.last_tuple;copy.last_index = source.last_index;copy.revision = source.revision;
  copy.committed = {};copy.copied_rows = source.primary.size();copy.copied_indices = source.indices.size();
  return result;
}

void AccountedIndexedTable::check_invariants() const {
  const auto& s = state();s.primary.check_invariants_noalloc();s.by_id.check_invariants_noalloc();
  s.indices.check_invariants_noalloc();s.arena.check_invariants();
  const auto projected = [](const AccountedProjection& p, const AccountedTuple& row, const AccountedTuple& key) {
    if (!p.source().same_token(row.layout()) || !p.target().same_token(key.layout())) return false;
    const auto fields = p.fields();
    for (std::size_t i = 0; i < fields.size(); ++i) if (row.values()[fields[i].value] != key.values()[i]) return false;
    return true;
  };
  const auto row_valid = [&](const AccountedIndexedRow& row, bool live) {
    contract(row.tuple && s.layout.same_token(row.tuple->layout()) && s.layout.validation_issue(row.tuple->values()).ok(), "row metadata differs");
    contract(row.id.value > 0 && row.id.value <= s.last_tuple && row.identity_link.hash == row.id.value &&
        row.primary_link.hash == s.diagnostic_hash(*row.tuple), "row identity/hash differs");
    contract(live ? (&s.arena.get(row.allocation) == row.tuple) : !s.arena.contains(row.allocation), "row arena membership differs");
    row.members.check_invariants();contract(row.members.size() == s.indices.size(), "row index population differs");
    for (auto* index = s.indices.first_resident(); index; index = detail::AccountedIndexIdDirectory::next_resident(*index)) {
      std::size_t count = 0;
      for (auto* member = row.members.first(); member; member = detail::AccountedRowMembers::next(*member)) {
        contract(member->row == &row, "reverse member owner differs");
        if (member->index != index) continue;
        ++count;contract(member->key->lookup_link.owner == &index->keys && projected(index->projection, *row.tuple, member->key->tuple), "member projection differs");
        contract(live ? member->key->members.contains(*member) : member->bucket_link.owner == nullptr, "member liveness differs");
        if (!live) contract(member->key->journal_references > 0, "retained member lost key authority");
      }
      contract(count == 1, "row is missing or repeats an index");
    }
  };
  std::size_t retired = 0, retained_members = 0;
  if (s.journal_active) {
    contract(s.active_journal && s.active_journal->owner.get() == &s && s.active_reader.lock() == s.active_journal->reader &&
        s.active_journal->reader->phase == AccountedIndexedJournalReader::Phase::active &&
        s.active_journal->reader->work.same_account(s.account), "journal authority differs");
    std::uint64_t inserted = 0, erased = 0;
    for (const auto& undo : s.active_journal->entries) {
      contract(undo->row && undo->pin && undo->handle == s.handle(*undo->row) && &undo->pin->get() == undo->row->tuple,
          "undo pin/row differs");
      if (undo->inserted) ++inserted;
      else {
        ++erased;++retired;retained_members += undo->row->members.size();
        contract(!undo->pin->is_live() && !undo->row->primary_link.owner && !undo->row->identity_link.owner, "retired row remains live");
        row_valid(*undo->row, false);
        for (const auto& prior : s.active_journal->entries)
          if (prior.get() != undo.get() && !prior->inserted) contract(prior->row != undo->row, "duplicate retired row");
      }
      contract(undo->keys.size() == s.indices.size(), "undo key population differs");
      for (const auto& key : undo->keys) contract(key.member->row == undo->row && key.member->key == key.key, "undo reverse pointers differ");
    }
    contract(s.journal_entries == s.active_journal->entries.size() && s.pending_inserted == inserted && s.pending_erased == erased, "pending counters differ");
  } else contract(!s.active_journal && s.active_reader.expired() && s.journal_entries == 0 && s.pending_inserted == 0 && s.pending_erased == 0, "closed journal retained authority");
  std::size_t keys = 0, live_keys = 0, bucket_members = 0, row_members = 0;
  std::size_t slots = s.primary.capacity() + s.by_id.capacity() + s.indices.capacity();
  std::uint64_t last_index = 0;
  for (auto* index = s.indices.first_resident(); index; index = detail::AccountedIndexIdDirectory::next_resident(*index)) {
    contract(index->id.value > last_index && index->id.value <= s.last_index && index->identity_link.hash == index->id.value &&
        s.layout.same_token(index->projection.source()), "index identity/order differs");last_index = index->id.value;
    index->keys.check_invariants_noalloc();index->live_keys.check_invariants();slots += index->keys.capacity();
    std::size_t present = 0;
    for (auto* key = index->keys.first_resident(); key; key = detail::AccountedKeyDirectory::next_resident(*key)) {
      ++keys;key->members.check_invariants();
      std::size_t references = 0;
      if (s.journal_active) for (const auto& undo : s.active_journal->entries)
        for (const auto& item : undo->keys) if (item.key == key) ++references;
      contract(key->journal_references == references && (key->members.size() != 0 || references != 0), "key retention differs");
      contract(index->projection.target().same_token(key->tuple.layout()) && key->lookup_link.hash == s.diagnostic_hash(key->tuple), "key metadata/hash differs");
      contract(index->live_keys.contains(*key) == (key->members.size() > 0), "live key membership differs");
      if (key->members.size()) { ++live_keys;++present; }
      for (auto* member = key->members.first(); member; member = detail::AccountedBucketMembers::next(*member)) {
        ++bucket_members;
        contract(member->key == key && member->index == index && member->row->members.contains(*member) &&
            member->row->primary_link.owner == &s.primary && projected(index->projection, *member->row->tuple, key->tuple), "bucket member differs");
      }
    }
    contract(present == index->live_keys.size(), "live key count differs");
    for (auto* key = index->live_keys.first(); key; key = detail::AccountedLiveKeys::next(*key)) {
      bool resident = false;
      for (auto* other = index->keys.first_resident(); other; other = detail::AccountedKeyDirectory::next_resident(*other)) if (other == key) resident = true;
      contract(resident && key->members.size() > 0, "foreign live key");
    }
  }
  std::uint64_t last_tuple = 0;
  for (auto* row = s.primary.first_resident(); row; row = detail::AccountedPrimaryDirectory::next_resident(*row)) {
    contract(row->id.value > last_tuple && row->identity_link.owner == &s.by_id, "row ID/order differs");last_tuple = row->id.value;row_valid(*row, true);
    row_members += row->members.size();
    bool identity = false;
    for (auto* id = s.by_id.first_resident(); id; id = detail::AccountedRowIdDirectory::next_resident(*id)) if (id == row) identity = true;
    contract(identity, "row missing identity membership");
    for (auto* prior = s.primary.first_resident(); prior != row; prior = detail::AccountedPrimaryDirectory::next_resident(*prior))
      contract(prior->tuple->values() != row->tuple->values(), "duplicate live row");
  }
  contract(s.primary.size() == s.by_id.size() && row_members == bucket_members && keys == s.key_nodes && live_keys == s.live_key_nodes &&
      row_members + retained_members == s.member_nodes && slots == s.directory_slots && retired == s.retained_rows && retained_members == s.retained_members &&
      s.primary.size() + retired + s.indices.size() + keys + s.member_nodes == s.nodes, "owned record census differs");
  const auto arena = s.arena.statistics();
  contract(arena.live_records == s.primary.size() && s.primary.size() + retired <= s.limits.rows && retired <= arena.retained_records &&
      s.indices.size() <= s.limits.indices && keys <= s.limits.keys && s.member_nodes <= s.limits.memberships && s.nodes <= s.limits.nodes &&
      slots <= s.limits.directory_slots && arena.slots <= s.limits.arena_slots && arena.pins <= s.limits.arena_pins && s.journal_entries <= s.limits.journal_entries,
      "finite component limit exceeded");
  const auto reconcile = [](std::size_t initial, std::uint64_t inserted, std::uint64_t erased, std::size_t live) {
    const auto base = static_cast<std::uint64_t>(initial), current = static_cast<std::uint64_t>(live);
    return inserted >= erased ? current >= base && current - base == inserted - erased : base >= current && base - current == erased - inserted;
  };
  contract(s.pending_inserted <= std::numeric_limits<std::uint64_t>::max() - s.committed.inserted_rows &&
      s.pending_erased <= std::numeric_limits<std::uint64_t>::max() - s.committed.erased_rows, "pending sum overflow");
  contract(reconcile(s.copied_rows, s.committed.inserted_rows + s.pending_inserted, s.committed.erased_rows + s.pending_erased, s.primary.size()) &&
      reconcile(s.copied_indices, s.committed.added_indices, s.committed.dropped_indices, s.indices.size()), "action census differs");
  s.account.check_invariants();
}

#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
void detail::AccountedIndexedTesting::collisions(AccountedIndexedTable& table, AccountedCollisionMode mode) {
  auto& state = table.state();state.unlocked();
  contract(state.primary.size() == 0 && state.indices.size() == 0 &&
      state.last_tuple == 0 && state.last_index == 0, "collision mode requires a fresh empty testing owner");
  contract(mode == AccountedCollisionMode::native || mode == AccountedCollisionMode::same_bucket ||
      mode == AccountedCollisionMode::same_full_hash, "unknown testing collision mode");
  contract(mode != AccountedCollisionMode::same_bucket || state.limits.directory_slots <= 65536,
      "same-bucket testing profile exceeds its directory-mask domain");
  state.collision_mode = mode;
}
void detail::AccountedIndexedTesting::exhaust(AccountedIndexedTable& table, Exhausted which) {
  auto& state = table.state();state.unlocked();
  switch (which) {
    case Exhausted::tuple_id: state.last_tuple = std::numeric_limits<std::uint64_t>::max();break;
    case Exhausted::index_id: state.last_index = std::numeric_limits<std::uint64_t>::max();break;
    case Exhausted::revision: state.revision = std::numeric_limits<std::uint64_t>::max();break;
  }
}
#endif

}  // namespace crown::storage
