#include "crown/storage/indexed.hpp"

#include "indexed_nodes.hpp"
#include "index_scalar_work.hpp"
#include "owner.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif
#include <algorithm>
#include <exception>
#include <limits>
#include <map>
#include <set>
#include <utility>

namespace crown::storage {
// Source-private definition with namespace linkage, like the existing S02
// reader. Externally linked nested Data types must not embed an anonymous type.
struct IndexedJournalReader {
  enum class Phase { active, committed, aborted };
  Phase phase = Phase::active;
  std::shared_ptr<IndexWorkAllowance> work;
  explicit IndexedJournalReader(std::shared_ptr<IndexWorkAllowance> grant) noexcept
      : work(std::move(grant)) {}
};
namespace {
using detail::IndexedIndex;
using detail::IndexedKey;
using detail::IndexedMember;
using detail::IndexedRow;

void contract(bool value, const char* message) {
  if (!value) throw Error("storage_contract", message);
}
void room(std::size_t current, std::size_t extra, std::size_t maximum) {
  if (current > maximum || extra > maximum - current)
    throw Error("storage_capacity", "optimized storage component limit reached");
}
void counter_room(std::uint64_t current, std::uint64_t extra = 1) {
  if (extra > std::numeric_limits<std::uint64_t>::max() - current)
    throw Error("storage_overflow", "optimized storage committed counter exhausted");
}
std::uint64_t work_product(std::size_t count, std::uint64_t cost) {
  const auto value = static_cast<std::uint64_t>(count);
  if (cost != 0 && value > std::numeric_limits<std::uint64_t>::max() / cost)
    throw Error("storage_overflow", "optimized storage work reservation overflow");
  return value * cost;
}
void start(IndexWorkAllowance& work) { work.admit(IndexWork{.structural_steps = 1}); }
template <class T>
void reserve_records(std::vector<T>& records, std::size_t count, IndexWorkAllowance& work) {
  if (count > records.max_size()) throw Error("storage_overflow", "optimized storage snapshot domain exhausted");
  constexpr auto words = static_cast<std::uint64_t>(sizeof(T) / sizeof(void*) + (sizeof(T) % sizeof(void*) != 0));
  work.admit(IndexWork{.pointer_slots = work_product(count, words)});
  records.reserve(count);
}
}  // namespace

struct IndexedTable::State {
  StorageOwnerId owner = detail::new_storage_owner();
  RelationId relation;
  TupleLayout layout;
  IndexedLimits limits;
  TupleArena arena;
  detail::PrimaryDirectory primary;
  detail::RowIdDirectory by_id;
  detail::IndexIdDirectory indices;
  std::size_t key_nodes = 0, live_key_nodes = 0, member_nodes = 0;
  std::size_t nodes = 0, directory_slots = 0;
  std::uint64_t last_tuple = 0, last_index = 0, revision = 0;
  IndexedActions committed;
  std::size_t copied_rows = 0, copied_indices = 0;
  bool journal_active = false;
  std::weak_ptr<IndexedJournalReader> active_reader;
  Journal::Data* active_journal = nullptr;
  std::size_t retained_rows = 0, retained_members = 0, journal_entries = 0;
  std::uint64_t pending_inserted = 0, pending_erased = 0;
#ifdef CROWN_STORAGE_TESTING
  detail::CollisionMode collision_mode = detail::CollisionMode::native;
#endif

  State(RelationId value, TupleLayout schema, IndexedLimits configuration)
      : relation(value), layout(std::move(schema)), limits(configuration), arena(layout),
        primary(limits.directory_slots), by_id(limits.directory_slots),
        indices(limits.directory_slots) {}
  ~State() {
    // Destroy nodes while all actual hook owners are still alive. Neither
    // directory capacity nor historical logical IDs are scanned here.
    while (auto* row = primary.first_resident()) delete row;
    while (auto* index = indices.first_resident()) delete index;
  }
  void input(const Tuple& tuple) const {
    if (!layout.same_token(tuple.layout()))
      throw Error("layout_mismatch", "tuple belongs to another storage layout");
  }
  void owned(TupleHandle handle) const {
    if (handle.owner != owner || handle.relation != relation)
      throw Error("foreign_handle", "tuple handle belongs to another storage owner/relation");
  }
  void mutable_revision() const { counter_room(revision); }
  void unlocked() const {
    if (journal_active) throw Error("storage_busy", "an exclusive storage journal is active");
  }
  TupleHandle handle(const IndexedRow& row) const noexcept { return {owner, relation, row.id}; }
  std::uint64_t transform_hash(std::uint64_t value) const noexcept {
#ifdef CROWN_STORAGE_TESTING
    if (collision_mode == detail::CollisionMode::same_full_hash) return 0;
    if (collision_mode == detail::CollisionMode::same_bucket) return value & ~std::uint64_t{0xffff};
#endif
    return value;
  }
  std::uint64_t hash(const Tuple& value, IndexWorkAllowance& work) const {
    return transform_hash(detail::admitted_hash(value, work));
  }
  std::uint64_t diagnostic_hash(const Tuple& value) const { return transform_hash(value.hash()); }
  IndexedRow* row(TupleHandle value, IndexWorkAllowance& work) const {
    owned(value);
    return by_id.find(value.tuple.value, [&](const IndexedRow& candidate, IndexWorkAllowance&) {
      return candidate.id == value.tuple;
    }, work);
  }
  IndexedRow* row(const Tuple& value, IndexWorkAllowance& work) const {
    input(value);const auto value_hash = hash(value, work);
    return primary.find(value_hash, [&](const IndexedRow& candidate, IndexWorkAllowance& allowance) {
      return detail::admitted_equal(*candidate.tuple, value, allowance);
    }, work);
  }
  IndexedIndex* maybe_index(IndexId id, IndexWorkAllowance& work) const {
    return indices.find(id.value, [&](const IndexedIndex& candidate, IndexWorkAllowance&) {
      return candidate.id == id;
    }, work);
  }
  IndexedIndex& index(IndexId id, IndexWorkAllowance& work) const {
    auto* found = maybe_index(id, work);
    if (found == nullptr) throw Error("unknown_index", "secondary index is absent or was dropped");
    return *found;
  }
  IndexedKey* key(IndexedIndex& index, const Tuple& value, IndexWorkAllowance& work) const {
    if (!index.projection.target().same_token(value.layout()))
      throw Error("layout_mismatch", "bucket key belongs to another compiled key layout");
    const auto value_hash = hash(value, work);
    return index.keys.find(value_hash, [&](const IndexedKey& candidate, IndexWorkAllowance& allowance) {
      return detail::admitted_equal(candidate.tuple, value, allowance);
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
  void prepare_erase(const IndexedRow& row, IndexWorkAllowance& work) const;
  void erase_prepaid(IndexedRow& row) noexcept;
  void erase_one(IndexedRow& row, IndexWorkAllowance& work);
};

#include "indexed_journal.inc"

IndexedTable::IndexedTable(RelationId relation, TupleLayout layout, IndexedLimits limits)
    : state_(std::make_shared<State>(relation, std::move(layout), limits)) {}
IndexedTable::IndexedTable(std::shared_ptr<State> state) noexcept : state_(std::move(state)) {}
IndexedTable::~IndexedTable() = default;
IndexedTable::IndexedTable(IndexedTable&&) noexcept = default;
IndexedTable& IndexedTable::operator=(IndexedTable&&) noexcept = default;
IndexedTable::State& IndexedTable::state() const {
  if (!state_) throw Error("invalid_storage", "moved-from optimized storage table");
  return *state_;
}
StorageOwnerId IndexedTable::owner() const { return state().owner; }
RelationId IndexedTable::relation() const { return state().relation; }
const TupleLayout& IndexedTable::layout() const { return state().layout; }
const IndexedLimits& IndexedTable::limits() const { return state().limits; }
std::size_t IndexedTable::size() const { return state().primary.size(); }
std::uint64_t IndexedTable::revision() const { return state().revision; }
ArenaStatistics IndexedTable::arena_statistics() const { return state().arena.statistics(); }
IndexedStatistics IndexedTable::statistics() const {
  const auto& s = state();
  return {s.primary.size(), s.indices.size(), s.key_nodes, s.live_key_nodes,
          s.member_nodes, s.nodes, s.directory_slots, s.arena.statistics(), s.committed,
          s.copied_rows, s.copied_indices, s.retained_rows, s.retained_members,
          s.journal_entries, IndexedActions{s.pending_inserted, s.pending_erased}};
}

InsertResult IndexedTable::insert(const Tuple& tuple, IndexWorkAllowance& work) {
  return insert_impl(tuple, work, nullptr);
}
InsertResult IndexedTable::insert_impl(const Tuple& tuple, IndexWorkAllowance& work, Journal::Data* journal) {
  auto& s = state();if (journal == nullptr) s.unlocked();start(work);s.input(tuple);
  const auto hash = s.hash(tuple, work);
  if (const auto* found = s.primary.find(hash, [&](const IndexedRow& candidate, IndexWorkAllowance& grant) {
      return detail::admitted_equal(*candidate.tuple, tuple, grant);
    }, work)) return {false, s.handle(*found)};
  s.mutable_revision();counter_room(s.last_tuple);
  counter_room(s.pending_inserted);counter_room(s.committed.inserted_rows, s.pending_inserted + 1);
  room(s.primary.size() + s.retained_rows, 1, s.limits.rows);room(s.nodes, 1, s.limits.nodes);
  room(s.member_nodes, s.indices.size(), s.limits.memberships);
  room(s.nodes + 1, s.indices.size(), s.limits.nodes);
  s.arena_insert_room();
  std::unique_ptr<Journal::Data::Undo> undo;
  if (journal != nullptr) {
    room(s.arena.statistics().pins, 1, s.limits.arena_pins);
    undo = journal->prepare(true);undo->previous_last = s.last_tuple;
    work.admit(IndexWork{.structural_steps = 1 + work_product(s.indices.size(), 4),
        .link_actions = detail::PrimaryDirectory::unlink_actions + detail::RowIdDirectory::unlink_actions});
    work.admit(IndexWork{.link_actions = work_product(s.indices.size(),
        detail::RowMembers::erase_actions + detail::BucketMembers::erase_actions +
        detail::LiveKeys::erase_actions + detail::KeyDirectory::unlink_actions)});
  }
  auto primary_growth = s.primary.prepare_growth(s.primary.size() + 1, work, s.slot_room());
  std::size_t added_slots = primary_growth.new_capacity() - s.primary.capacity();
  auto id_growth = s.by_id.prepare_growth(s.by_id.size() + 1, work, s.slot_room(added_slots));
  added_slots += id_growth.new_capacity() - s.by_id.capacity();
  work.admit(IndexWork{.structural_steps = static_cast<std::uint64_t>(s.indices.size()),
      .link_actions = detail::PrimaryDirectory::link_actions + detail::RowIdDirectory::link_actions});
  auto row = std::make_unique<IndexedRow>(TupleId{s.last_tuple + 1}, s.limits.indices);
  struct Prepared {
    IndexedIndex* index;
    IndexedKey* key;
    std::unique_ptr<IndexedKey> created;
    std::optional<detail::KeyDirectory::Growth> growth;
  };
  std::vector<Prepared> prepared;reserve_records(prepared, s.indices.size(), work);
  std::size_t added_keys = 0, activated_keys = 0;
  for (auto* index = s.indices.first_resident(); index != nullptr;
       index = detail::IndexIdDirectory::next_resident(*index)) {
    auto projected = detail::admitted_projection(index->projection, tuple, work);
    const auto key_hash = s.hash(projected, work);
    auto* key = index->keys.find(key_hash, [&](const IndexedKey& candidate, IndexWorkAllowance& grant) {
      return detail::admitted_equal(candidate.tuple, projected, grant);
    }, work);
    Prepared item{index, key, {}, {}};
    if (key == nullptr) {
      room(s.key_nodes, added_keys + 1, s.limits.keys);
      room(s.nodes + 1 + s.indices.size(), added_keys + 1, s.limits.nodes);
      item.created = std::make_unique<IndexedKey>(std::move(projected), s.limits.rows);
      item.key = item.created.get();
      item.growth.emplace(index->keys.prepare_growth(index->keys.size() + 1, work, s.slot_room(added_slots)));
      added_slots += item.growth->new_capacity() - index->keys.capacity();
      work.admit(IndexWork{.link_actions = detail::KeyDirectory::link_actions});
      ++added_keys;
    }
    if (item.key->members.size() == 0) {
      index->live_keys.prepare_insert(work);++activated_keys;
    }
    row->members.prepare_insert(work);item.key->members.prepare_insert(work);
    auto member = std::make_unique<IndexedMember>(*row, *index, *item.key);
    if (undo) {
      room(item.key->journal_references, 1, s.limits.journal_entries);
      detail::admit_tuple_copy(item.key->tuple, work);
      undo->keys.push_back({item.key, member.get(), nullptr, nullptr, nullptr, nullptr});
    }
    row->members.append_prepaid(*member);static_cast<void>(member.release());
    // A new key's cached hash is set while private; publication never hashes.
    if (item.created) item.created->lookup_link.hash = key_hash;
    prepared.push_back(std::move(item));
  }
  detail::admit_tuple_copy(tuple, work);
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
  for (auto* member = row->members.first(); member != nullptr; member = detail::RowMembers::next(*member)) {
    if (member->key->members.size() == 0) member->index->live_keys.append_prepaid(*member->key);
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

std::optional<TupleHandle> IndexedTable::find(const Tuple& tuple, IndexWorkAllowance& work) const {
  auto& s = state();start(work);const auto* row = s.row(tuple, work);
  if (row == nullptr) return {};
  return s.handle(*row);
}
const Tuple* IndexedTable::get(TupleHandle handle, IndexWorkAllowance& work) const {
  auto& s = state();start(work);const auto* row = s.row(handle, work);
  return row == nullptr ? nullptr : row->tuple;
}
TupleArena::Pin IndexedTable::pin(TupleHandle handle, IndexWorkAllowance& work) const {
  auto& s = state();start(work);const auto* row = s.row(handle, work);
  if (row == nullptr) throw Error("stale_handle", "tuple is no longer a live table record");
  room(s.arena.statistics().pins, 1, s.limits.arena_pins);
  return s.arena.pin(row->allocation);
}

void IndexedTable::State::prepare_erase(const IndexedRow& row, IndexWorkAllowance& work) const {
  start(work);
  work.admit(IndexWork{.link_actions = detail::PrimaryDirectory::unlink_actions + detail::RowIdDirectory::unlink_actions});
  detail::admit_tuple_copy(*row.tuple, work); // Conservative retirement allowance.
  for (auto* member = row.members.first(); member != nullptr; member = detail::RowMembers::next(*member)) {
    row.members.prepare_erase(*member, work);member->key->members.prepare_erase(*member, work);
    // A bulk erase can empty a key only after other rows have been removed.
    // Reserve potential final-key cleanup for every affected member up front.
    work.admit(IndexWork{.link_actions = detail::KeyDirectory::unlink_actions + detail::LiveKeys::erase_actions});
    detail::admit_tuple_copy(member->key->tuple, work);
  }
}
void IndexedTable::State::erase_prepaid(IndexedRow& row) noexcept {
  while (auto* member = row.members.first()) {
    auto* key = member->key;delete member;--member_nodes;--nodes;
    if (key->members.size() == 0) {
      delete key;--key_nodes;--live_key_nodes;--nodes;
    }
  }
  if (!arena.erase(row.allocation)) std::terminate();
  delete &row;--nodes;
}
void IndexedTable::State::erase_one(IndexedRow& row, IndexWorkAllowance& work) {
  mutable_revision();counter_room(committed.erased_rows);prepare_erase(row, work);
  erase_prepaid(row);++revision;++committed.erased_rows;
}
bool IndexedTable::erase(const Tuple& tuple, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* row = s.row(tuple, work);
  if (row == nullptr) return false;
  s.erase_one(*row, work);return true;
}
bool IndexedTable::erase(TupleHandle handle, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* row = s.row(handle, work);
  if (row == nullptr) return false;
  s.erase_one(*row, work);return true;
}

IndexId IndexedTable::add_index(Projection projection, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);
  if (!s.layout.same_token(projection.source()))
    throw Error("layout_mismatch", "secondary projection belongs to another source layout");
  for (auto* existing = s.indices.first_resident(); existing != nullptr;
       existing = detail::IndexIdDirectory::next_resident(*existing)) {
    start(work);
    if (existing->projection.same_token(projection)) return existing->id;
  }
  s.mutable_revision();counter_room(s.last_index);counter_room(s.committed.added_indices);
  room(s.indices.size(), 1, s.limits.indices);room(s.nodes, 1, s.limits.nodes);
  room(s.member_nodes, s.primary.size(), s.limits.memberships);
  room(s.nodes + 1, s.primary.size(), s.limits.nodes);
  auto id_growth = s.indices.prepare_growth(s.indices.size() + 1, work, s.slot_room());
  const auto id_slots = id_growth.new_capacity() - s.indices.capacity();
  auto index = std::make_unique<IndexedIndex>(IndexId{s.last_index + 1}, std::move(projection),
      s.limits.directory_slots, s.limits.keys);
  std::vector<std::unique_ptr<IndexedMember>> members;reserve_records(members, s.primary.size(), work);
  work.admit(IndexWork{.link_actions = detail::IndexIdDirectory::link_actions});
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::PrimaryDirectory::next_resident(*row)) {
    start(work);
    auto projected = detail::admitted_projection(index->projection, *row->tuple, work);
    const auto hash = s.hash(projected, work);
    auto* key = index->keys.find(hash, [&](const IndexedKey& candidate, IndexWorkAllowance& grant) {
      return detail::admitted_equal(candidate.tuple, projected, grant);
    }, work);
    if (key == nullptr) {
      room(s.key_nodes, index->keys.size() + 1, s.limits.keys);
      room(s.nodes + 1 + s.primary.size(), index->keys.size() + 1, s.limits.nodes);
      auto created = std::make_unique<IndexedKey>(std::move(projected), s.limits.rows);
      auto growth = index->keys.prepare_growth(index->keys.size() + 1, work,
          s.slot_room(id_slots + index->keys.capacity()));
      index->live_keys.prepare_insert(work);
      work.admit(IndexWork{.link_actions = detail::KeyDirectory::link_actions});
      index->keys.publish_growth(std::move(growth));index->keys.link_prepaid(*created, hash);
      index->live_keys.append_prepaid(*created);key = created.release();
    }
    row->members.prepare_insert(work);key->members.prepare_insert(work);
    auto member = std::make_unique<IndexedMember>(*row, *index, *key);
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

bool IndexedTable::drop_index(IndexId id, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto* index = s.maybe_index(id, work);
  if (index == nullptr) return false;
  s.mutable_revision();counter_room(s.committed.dropped_indices);
  work.admit(IndexWork{.link_actions = detail::IndexIdDirectory::unlink_actions});
  std::size_t members = 0;
  for (auto* key = index->keys.first_resident(); key != nullptr;
       key = detail::KeyDirectory::next_resident(*key)) {
    start(work);detail::admit_tuple_copy(key->tuple, work);
    work.admit(IndexWork{.link_actions = detail::KeyDirectory::unlink_actions + detail::LiveKeys::erase_actions});
    for (auto* member = key->members.first(); member != nullptr; member = detail::BucketMembers::next(*member)) {
      member->row->members.prepare_erase(*member, work);key->members.prepare_erase(*member, work);
      room(members, 1, s.member_nodes);++members;
    }
  }
  const auto keys = index->keys.size(), live_keys = index->live_keys.size(), slots = index->keys.capacity();
  delete index;
  s.key_nodes -= keys;s.live_key_nodes -= live_keys;s.member_nodes -= members;
  s.nodes -= 1 + keys + members;s.directory_slots -= slots;
  ++s.revision;++s.committed.dropped_indices;return true;
}
std::vector<IndexId> IndexedTable::indices(IndexWorkAllowance& work) const {
  auto& s = state();start(work);std::vector<IndexId> result;reserve_records(result, s.indices.size(), work);
  for (auto* index = s.indices.first_resident(); index != nullptr;
       index = detail::IndexIdDirectory::next_resident(*index)) {
    start(work);result.push_back(index->id);
  }
  return result;
}
Projection IndexedTable::projection(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);return s.index(id, work).projection;
}
std::size_t IndexedTable::key_count(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);return s.index(id, work).live_keys.size();
}
std::vector<Tuple> IndexedTable::keys(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto& index = s.index(id, work);
  std::vector<Tuple> result;reserve_records(result, index.live_keys.size(), work);
  for (auto* key = index.live_keys.first(); key != nullptr; key = detail::LiveKeys::next(*key)) {
    start(work);detail::admit_tuple_copy(key->tuple, work);result.push_back(key->tuple);
  }
  return result;
}
std::vector<TupleHandle> IndexedTable::bucket(IndexId id, const Tuple& value, IndexWorkAllowance& work) const {
  auto& s = state();start(work);auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  std::vector<TupleHandle> result;
  if (key == nullptr) return result;
  reserve_records(result, key->members.size(), work);
  for (auto* member = key->members.first(); member != nullptr; member = detail::BucketMembers::next(*member)) {
    start(work);result.push_back(s.handle(*member->row));
  }
  return result;
}
std::size_t IndexedTable::erase_key(IndexId id, const Tuple& value, IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);auto* key = s.key(index, value, work);
  if (key == nullptr) return 0;
  s.mutable_revision();counter_room(s.committed.erased_rows, static_cast<std::uint64_t>(key->members.size()));
  std::vector<IndexedRow*> rows;reserve_records(rows, key->members.size(), work);
  for (auto* member = key->members.first(); member != nullptr; member = detail::BucketMembers::next(*member)) {
    s.prepare_erase(*member->row, work);rows.push_back(member->row);
  }
  for (auto* row : rows) s.erase_prepaid(*row);
  ++s.revision;s.committed.erased_rows += static_cast<std::uint64_t>(rows.size());return rows.size();
}
void IndexedTable::clear(IndexWorkAllowance& work) {
  auto& s = state();s.unlocked();start(work);const auto count = s.primary.size();
  if (count == 0) return;
  s.mutable_revision();counter_room(s.committed.clears);
  counter_room(s.committed.erased_rows, static_cast<std::uint64_t>(count));
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::PrimaryDirectory::next_resident(*row)) s.prepare_erase(*row, work);
  while (auto* row = s.primary.first_resident()) s.erase_prepaid(*row);
  ++s.revision;++s.committed.clears;s.committed.erased_rows += static_cast<std::uint64_t>(count);
}
std::vector<Tuple> IndexedTable::snapshot(IndexWorkAllowance& work) const {
  auto& s = state();start(work);std::vector<Tuple> result;reserve_records(result, s.primary.size(), work);
  for (auto* row = s.primary.first_resident(); row != nullptr;
       row = detail::PrimaryDirectory::next_resident(*row)) {
    start(work);detail::admit_tuple_copy(*row->tuple, work);result.push_back(*row->tuple);
  }
  return result;
}

struct IndexedTable::Cursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<IndexedJournalReader> journal;
  std::uint64_t revision;
  bool bucket_mode = false;
  IndexedRow* next_row = nullptr;
  IndexedMember* next_member = nullptr;
  explicit Data(const std::shared_ptr<State>& state) : owner(state), revision(state->revision) {}
};
IndexedTable::Cursor::Cursor(std::unique_ptr<Data> data) noexcept : data_(std::move(data)) {}
IndexedTable::Cursor::Cursor(Cursor&&) noexcept = default;
IndexedTable::Cursor& IndexedTable::Cursor::operator=(Cursor&&) noexcept = default;
IndexedTable::Cursor::~Cursor() = default;
std::optional<IndexedTable::Cursor::Entry> IndexedTable::Cursor::next(IndexWorkAllowance& work) {
  if (!data_) throw Error("invalid_cursor", "moved-from optimized storage cursor");
  const auto owner = data_->owner.lock();
  if (!owner) throw Error("invalid_cursor", "optimized storage cursor owner was destroyed");
  if (data_->journal && data_->journal->phase == IndexedJournalReader::Phase::aborted)
    throw Error("invalid_cursor", "owning optimized journal was rolled back");
  if (data_->journal && data_->journal->work.get() != &work)
    throw Error("storage_contract", "journal cursor requires its original owning work grant");
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock() != data_->journal))
    owner->unlocked();
  if (owner->revision != data_->revision)
    throw Error("invalid_cursor", "optimized storage cursor invalidated by mutation");
  start(work); // A denial leaves both the cursor position and owner unchanged.
  IndexedRow* row = nullptr;
  if (data_->bucket_mode) {
    if (data_->next_member == nullptr) return {};
    row = data_->next_member->row;
    data_->next_member = detail::BucketMembers::next(*data_->next_member);
  } else {
    if (data_->next_row == nullptr) return {};
    row = data_->next_row;data_->next_row = detail::PrimaryDirectory::next_resident(*row);
  }
  return Entry{owner->handle(*row), *row->tuple};
}
IndexedTable::Cursor IndexedTable::live(IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = std::make_unique<Cursor::Data>(state_);data->next_row = s.primary.first_resident();
  return Cursor(std::move(data));
}
IndexedTable::Cursor IndexedTable::bucket_cursor(IndexId id, const Tuple& value, IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = std::make_unique<Cursor::Data>(state_);data->bucket_mode = true;
  if (key != nullptr) data->next_member = key->members.first();
  return Cursor(std::move(data));
}
struct IndexedTable::IndexKeyCursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<IndexedJournalReader> journal;
  std::uint64_t revision;
  IndexedKey* next_key = nullptr;
  explicit Data(const std::shared_ptr<State>& state) : owner(state), revision(state->revision) {}
};
IndexedTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr<Data> data) noexcept : data_(std::move(data)) {}
IndexedTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
IndexedTable::IndexKeyCursor& IndexedTable::IndexKeyCursor::operator=(IndexKeyCursor&&) noexcept = default;
IndexedTable::IndexKeyCursor::~IndexKeyCursor() = default;
std::optional<IndexedTable::IndexKeyCursor::Entry> IndexedTable::IndexKeyCursor::next(IndexWorkAllowance& work) {
  if (!data_) throw Error("invalid_cursor", "moved-from optimized key cursor");
  const auto owner = data_->owner.lock();
  if (!owner) throw Error("invalid_cursor", "optimized key cursor owner was destroyed");
  if (data_->journal && data_->journal->phase == IndexedJournalReader::Phase::aborted)
    throw Error("invalid_cursor", "owning optimized journal was rolled back");
  if (data_->journal && data_->journal->work.get() != &work)
    throw Error("storage_contract", "journal cursor requires its original owning work grant");
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock() != data_->journal))
    owner->unlocked();
  if (owner->revision != data_->revision)
    throw Error("invalid_cursor", "optimized key cursor invalidated by mutation");
  start(work);
  if (data_->next_key == nullptr) return {};
  auto* key = data_->next_key;data_->next_key = detail::LiveKeys::next(*key);
  return Entry{key->tuple, key->members.size()};
}
IndexedTable::IndexKeyCursor IndexedTable::index_keys(IndexId id, IndexWorkAllowance& work) const {
  auto& s = state();s.unlocked();start(work);auto& index = s.index(id, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(IndexKeyCursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto data = std::make_unique<IndexKeyCursor::Data>(state_);data->next_key = index.live_keys.first();
  return IndexKeyCursor(std::move(data));
}

IndexedTable::Cursor IndexedTable::Journal::live() const {
  if (!data_) throw Error("invalid_journal", "moved-from optimized storage journal");
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = std::make_unique<Cursor::Data>(data_->owner);cursor->journal = data_->reader;
  cursor->next_row = s.primary.first_resident();return Cursor(std::move(cursor));
}
IndexedTable::Cursor IndexedTable::Journal::bucket_cursor(IndexId id, const Tuple& value) const {
  if (!data_) throw Error("invalid_journal", "moved-from optimized storage journal");
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  auto& index = s.index(id, work);const auto* key = s.key(index, value, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Cursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = std::make_unique<Cursor::Data>(data_->owner);cursor->journal = data_->reader;
  cursor->bucket_mode = true;if (key != nullptr) cursor->next_member = key->members.first();
  return Cursor(std::move(cursor));
}
IndexedTable::IndexKeyCursor IndexedTable::Journal::index_keys(IndexId id) const {
  if (!data_) throw Error("invalid_journal", "moved-from optimized storage journal");
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);auto& index = s.index(id, work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(IndexKeyCursor::Data) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = words});
  auto cursor = std::make_unique<IndexKeyCursor::Data>(data_->owner);cursor->journal = data_->reader;
  cursor->next_key = index.live_keys.first();return IndexKeyCursor(std::move(cursor));
}

IndexedTable IndexedTable::snapshot_copy(IndexWorkAllowance& work) const {
  const auto& source = state();source.unlocked();start(work);
  constexpr auto state_words = static_cast<std::uint64_t>((sizeof(State) + sizeof(void*) - 1) / sizeof(void*));
  work.admit(IndexWork{.pointer_slots = state_words});
  IndexedTable result(source.relation, source.layout, source.limits);
  auto& copy = result.state();std::uint64_t previous = 0;
#ifdef CROWN_STORAGE_TESTING
  copy.collision_mode = source.collision_mode;
#endif
  for (auto* row = source.primary.first_resident(); row != nullptr;
       row = detail::PrimaryDirectory::next_resident(*row)) {
    start(work);contract(row->id.value > previous, "copy source row IDs are not in logical insertion order");
    // This is a private checked builder, not a public raw-ID constructor.
    copy.last_tuple = row->id.value - 1;
    const auto inserted = result.insert(*row->tuple, work);
    contract(inserted.inserted && inserted.handle.tuple == row->id, "owning copy renumbered a live tuple");
    previous = row->id.value;
  }
  previous = 0;
  for (auto* index = source.indices.first_resident(); index != nullptr;
       index = detail::IndexIdDirectory::next_resident(*index)) {
    start(work);contract(index->id.value > previous, "copy source index IDs are not ordered");
    copy.last_index = index->id.value - 1;
    contract(result.add_index(index->projection, work) == index->id, "owning copy renumbered an index");
    auto& destination = copy.index(index->id, work);
    std::vector<IndexedKey*> order;reserve_records(order, index->live_keys.size(), work);
    for (auto* key = index->live_keys.first(); key != nullptr; key = detail::LiveKeys::next(*key)) {
      start(work);auto* found = copy.key(destination, key->tuple, work);
      contract(found != nullptr && found->members.size() == key->members.size(), "owning copy changed a live bucket");
      order.push_back(found);
    }
    contract(order.size() == destination.live_keys.size(), "owning copy changed the live key population");
    // Rebuilding from today's row order can change an older still-live key's
    // position. Restore the actual source list after every lookup is prepared.
    work.admit(IndexWork{.structural_steps = work_product(order.size(), 2),
        .link_actions = work_product(order.size(), detail::LiveKeys::erase_actions + detail::LiveKeys::insert_actions)});
    while (auto* key = destination.live_keys.first()) destination.live_keys.erase_prepaid(*key);
    for (auto* key : order) destination.live_keys.append_prepaid(*key);
    previous = index->id.value;
  }
  copy.last_tuple = source.last_tuple;copy.last_index = source.last_index;copy.revision = source.revision;
  copy.committed = {};copy.copied_rows = source.primary.size();copy.copied_indices = source.indices.size();
  return result;
}

void IndexedTable::check_invariants() const {
  const auto& s = state();s.primary.check_invariants();s.by_id.check_invariants();s.indices.check_invariants();
  s.arena.check_invariants();
  std::set<const IndexedRow*> rows, ids;
  std::set<const IndexedIndex*> indices;
  std::set<const IndexedMember*> row_members, bucket_members;
  std::set<const IndexedRow*> retired;
  std::map<const IndexedKey*, std::size_t> expected_references;
  std::set<crown::Row> values;
  if (s.journal_active) {
    contract(s.active_journal != nullptr && s.active_journal->owner.get() == &s &&
        s.active_reader.lock() == s.active_journal->reader &&
        s.active_journal->reader->phase == IndexedJournalReader::Phase::active,
        "optimized active journal authority differs");
    std::uint64_t inserted = 0, erased = 0;
    for (const auto& undo : s.active_journal->entries) {
      contract(undo->row != nullptr && undo->pin && undo->handle == s.handle(*undo->row) &&
          &undo->pin->get() == undo->row->tuple, "optimized journal payload authority differs");
      if (undo->inserted) ++inserted;
      else { ++erased;contract(retired.insert(undo->row).second && !undo->pin->is_live(),
          "optimized erased journal row is duplicated/live"); }
      for (const auto& item : undo->keys) {
        contract(item.member->row == undo->row && item.member->key == item.key,
            "optimized journal reverse pointer differs");
        ++expected_references[item.key];
      }
    }
    contract(s.journal_entries == s.active_journal->entries.size() &&
        s.pending_inserted == inserted && s.pending_erased == erased,
        "optimized journal action counts differ");
  } else {
    contract(s.active_journal == nullptr && s.active_reader.expired() &&
        s.journal_entries == 0 && s.pending_inserted == 0 && s.pending_erased == 0,
        "closed optimized journal retained tentative authority");
  }
  std::size_t expected_keys = 0, expected_live_keys = 0, expected_slots =
      s.primary.capacity() + s.by_id.capacity() + s.indices.capacity();
  for (auto* index = s.indices.first_resident(); index != nullptr;
       index = detail::IndexIdDirectory::next_resident(*index)) {
    contract(indices.insert(index).second && index->id.value > 0 && index->id.value <= s.last_index,
             "invalid optimized index identity");
    contract(index->identity_link.hash == index->id.value && s.layout.same_token(index->projection.source()),
             "optimized index binding/hash differs");
    index->keys.check_invariants();index->live_keys.check_invariants();
    std::set<const IndexedKey*> resident, live;
    for (auto* key = index->keys.first_resident(); key != nullptr; key = detail::KeyDirectory::next_resident(*key)) {
      contract(resident.insert(key).second && (key->members.size() > 0 ||
          (s.journal_active && key->journal_references > 0)),
               "ordinary optimized table retained an empty/duplicate key");
      const auto reference = expected_references.find(key);
      contract(key->journal_references == (reference == expected_references.end() ? 0 : reference->second),
          "optimized key journal references differ");
      contract(index->projection.target().same_token(key->tuple.layout()) && key->lookup_link.hash == s.diagnostic_hash(key->tuple),
               "optimized key binding/hash differs");
      key->members.check_invariants();
      for (auto* member = key->members.first(); member != nullptr; member = detail::BucketMembers::next(*member)) {
        contract(member->key == key && member->index == index && bucket_members.insert(member).second,
                 "invalid optimized bucket member identity");
      }
    }
    for (auto* key = index->live_keys.first(); key != nullptr; key = detail::LiveKeys::next(*key))
      contract(live.insert(key).second && resident.contains(key), "foreign optimized live key");
    for (const auto* key : resident)
      contract(live.contains(key) == (key->members.size() > 0), "optimized key residency/live membership differs");
    expected_keys += resident.size();expected_live_keys += live.size();expected_slots += index->keys.capacity();
  }
  std::uint64_t previous_id = 0;
  for (auto* row = s.primary.first_resident(); row != nullptr; row = detail::PrimaryDirectory::next_resident(*row)) {
    contract(rows.insert(row).second && row->id.value > previous_id && row->id.value <= s.last_tuple,
             "optimized row identity/order differs");
    previous_id = row->id.value;
    contract(row->tuple != nullptr && &s.arena.get(row->allocation) == row->tuple &&
        s.layout.same_token(row->tuple->layout()) && values.insert(export_row(row->tuple->values())).second,
        "invalid/duplicate optimized tuple allocation");
    contract(row->primary_link.hash == s.diagnostic_hash(*row->tuple) && row->identity_link.hash == row->id.value,
             "optimized row cached hashes differ");
    row->members.check_invariants();std::set<const IndexedIndex*> row_indices;
    for (auto* member = row->members.first(); member != nullptr; member = detail::RowMembers::next(*member)) {
      contract(member->row == row && indices.contains(member->index) && row_indices.insert(member->index).second &&
          row_members.insert(member).second && member->key->lookup_link.owner == &member->index->keys &&
          member->key->members.contains(*member), "invalid optimized reverse membership");
      contract(member->index->projection.apply(*row->tuple) == member->key->tuple,
               "optimized member projection differs from its actual row");
    }
    contract(row_indices == indices, "optimized row has incomplete/duplicate registered indices");
  }
  for (auto* row = s.by_id.first_resident(); row != nullptr; row = detail::RowIdDirectory::next_resident(*row))
    contract(ids.insert(row).second, "duplicate optimized ID-directory row");
  contract(rows == ids && row_members == bucket_members, "optimized directory/reverse-membership populations differ");
  std::set<const IndexedMember*> retained_members;
  for (const auto* row : retired) {
    contract(!rows.contains(row) && row->primary_link.owner == nullptr && row->identity_link.owner == nullptr,
        "retired optimized row remains in a live directory");
    row->members.check_invariants();std::set<const IndexedIndex*> row_indices;
    for (auto* member = row->members.first(); member != nullptr; member = detail::RowMembers::next(*member)) {
      contract(member->row == row && indices.contains(member->index) && row_indices.insert(member->index).second &&
          retained_members.insert(member).second && !row_members.contains(member) && member->bucket_link.owner == nullptr &&
          member->key->lookup_link.owner == &member->index->keys && member->key->journal_references > 0,
          "invalid optimized retained reverse membership");
      contract(member->index->projection.apply(*row->tuple) == member->key->tuple,
          "optimized retained projection differs");
    }
    contract(row_indices == indices, "retained optimized row has incomplete indices");
  }
  contract(retired.size() == s.retained_rows && retained_members.size() == s.retained_members,
      "optimized retained node counters differ");
  contract(expected_keys == s.key_nodes && expected_live_keys == s.live_key_nodes &&
      row_members.size() + retained_members.size() == s.member_nodes && expected_slots == s.directory_slots &&
      rows.size() + retired.size() + indices.size() + expected_keys + s.member_nodes == s.nodes,
      "optimized component counters differ from owned records");
  const auto arena = s.arena.statistics();
  contract(arena.live_records == rows.size() && rows.size() + retired.size() <= s.limits.rows &&
      retired.size() <= arena.retained_records && s.journal_entries <= s.limits.journal_entries &&
      indices.size() <= s.limits.indices && s.key_nodes <= s.limits.keys && s.member_nodes <= s.limits.memberships &&
      s.nodes <= s.limits.nodes && s.directory_slots <= s.limits.directory_slots &&
      arena.slots <= s.limits.arena_slots && arena.pins <= s.limits.arena_pins,
      "optimized component population exceeds finite limits");
  const auto reconcile = [](std::size_t initial, std::uint64_t inserted, std::uint64_t erased, std::size_t live) {
    const auto base = static_cast<std::uint64_t>(initial), current = static_cast<std::uint64_t>(live);
    if (inserted >= erased) return current >= base && current - base == inserted - erased;
    return base >= current && base - current == erased - inserted;
  };
  contract(s.pending_inserted <= std::numeric_limits<std::uint64_t>::max() - s.committed.inserted_rows &&
      s.pending_erased <= std::numeric_limits<std::uint64_t>::max() - s.committed.erased_rows,
      "optimized pending and committed counter sum overflows");
  contract(reconcile(s.copied_rows, s.committed.inserted_rows + s.pending_inserted,
      s.committed.erased_rows + s.pending_erased, rows.size()) &&
      reconcile(s.copied_indices, s.committed.added_indices, s.committed.dropped_indices, indices.size()),
      "optimized copied baseline and committed actions do not reconcile");
}

#ifdef CROWN_STORAGE_TESTING
void detail::IndexedTesting::collisions(IndexedTable& table, CollisionMode mode) {
  auto& state = table.state();state.unlocked();
  contract(state.primary.size() == 0 && state.indices.size() == 0 &&
      state.last_tuple == 0 && state.last_index == 0, "collision mode requires a fresh empty testing owner");
  contract(mode == CollisionMode::native || mode == CollisionMode::same_bucket ||
      mode == CollisionMode::same_full_hash, "unknown testing collision mode");
  contract(mode != CollisionMode::same_bucket || state.limits.directory_slots <= 65536,
      "same-bucket testing profile exceeds its directory-mask domain");
  state.collision_mode = mode;
}
#endif

}  // namespace crown::storage
