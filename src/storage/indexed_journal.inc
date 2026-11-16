// Included once inside crown::storage, after IndexedTable::State. No separate
// translation unit or second owner authority. All inverse paths use cached
// nodes/neighbors and work debited before the corresponding forward mutation.
struct IndexedTable::Journal::Data {
  struct Key {
    IndexedKey* key;
    IndexedMember* member;
    IndexedMember* previous;
    IndexedMember* next;
    IndexedKey* live_previous;
    IndexedKey* live_next;
  };
  struct Undo {
    bool inserted;
    TupleHandle handle{};
    std::uint64_t previous_last = 0;
    IndexedRow* row = nullptr;
    IndexedRow* primary_previous = nullptr;
    IndexedRow* primary_next = nullptr;
    IndexedRow* id_previous = nullptr;
    IndexedRow* id_next = nullptr;
    std::optional<TupleArena::Pin> pin;
    std::vector<Key> keys;
    explicit Undo(bool value) noexcept : inserted(value) {}
  };
  std::shared_ptr<State> owner;
  std::shared_ptr<IndexedJournalReader> reader;
  std::vector<std::unique_ptr<Undo>> entries;

  Data(std::shared_ptr<State> state, std::shared_ptr<IndexedJournalReader> authority) noexcept
      : owner(std::move(state)), reader(std::move(authority)) {}
  ~Data() { rollback(); }
  State& active() const {
    if (!owner || !owner->journal_active || owner->active_journal != this ||
        reader->phase != IndexedJournalReader::Phase::active)
      throw Error("invalid_journal", "optimized storage journal is closed");
    return *owner;
  }
  std::unique_ptr<Undo> prepare(bool inserted) {
    auto& s = active();auto& work = *reader->work;
    room(entries.size(), 1, s.limits.journal_entries);
    if (entries.size() == entries.max_size())
      throw Error("storage_overflow", "optimized journal entry domain exhausted");
    if (entries.size() == entries.capacity()) {
      const auto remaining = s.limits.journal_entries - entries.size();
      const auto extra = std::min(remaining, std::max<std::size_t>(1, entries.size()));
      work.admit(IndexWork{.structural_steps = static_cast<std::uint64_t>(entries.size())});
      reserve_records(entries, entries.size() + extra, work);
    }
    constexpr auto words = static_cast<std::uint64_t>((sizeof(Undo) + sizeof(void*) - 1) / sizeof(void*));
    work.admit(IndexWork{.structural_steps = 1, .pointer_slots = words});
    auto result = std::make_unique<Undo>(inserted);
    reserve_records(result->keys, s.indices.size(), work);
    return result;
  }
  void publish(std::unique_ptr<Undo> undo) noexcept {
    if (entries.size() >= entries.capacity() || !undo->pin) std::terminate();
    for (auto& item : undo->keys) ++item.key->journal_references;
    ++owner->journal_entries;entries.push_back(std::move(undo));
  }
  void release_keys(Undo& undo) noexcept {
    for (auto& item : undo.keys) {
      auto* key = item.key;
      if (key->journal_references == 0) std::terminate();
      --key->journal_references;
      // The last reference proves that no later inverse can dereference this
      // key. Retired rows may still contain raw key pointers; their destructor
      // detaches actual hooks without reading those pointers.
      if (key->journal_references == 0 && key->members.size() == 0) {
        if (key->live_link.owner != nullptr) std::terminate();
        delete key;--owner->key_nodes;--owner->nodes;
      }
    }
  }
  void undo_insert(Undo& undo) noexcept {
    auto& s = *owner;auto& row = *undo.row;
    s.primary.unlink_prepaid(row);s.by_id.unlink_prepaid(row);
    while (auto* member = row.members.first()) {
      auto* key = member->key;auto* index = member->index;
      key->members.erase_prepaid(*member);delete member;--s.member_nodes;--s.nodes;
      if (key->members.size() == 0) {
        index->live_keys.erase_prepaid(*key);--s.live_key_nodes;
      }
    }
    if (!s.arena.erase(row.allocation)) std::terminate();
    delete &row;--s.nodes;--s.pending_inserted;s.last_tuple = undo.previous_last;
  }
  void undo_erase(Undo& undo) noexcept {
    auto& s = *owner;auto& row = *undo.row;
    s.arena.revive(*undo.pin);
    s.primary.link_between_prepaid(row, row.primary_link.hash, undo.primary_previous, undo.primary_next);
    s.by_id.link_between_prepaid(row, row.identity_link.hash, undo.id_previous, undo.id_next);
    for (auto& item : undo.keys) {
      auto& key = *item.key;
      if (key.members.size() == 0) {
        item.member->index->live_keys.insert_between_prepaid(key, item.live_previous, item.live_next);
        ++s.live_key_nodes;
      }
      key.members.insert_between_prepaid(*item.member, item.previous, item.next);
    }
    --s.retained_rows;s.retained_members -= row.members.size();--s.pending_erased;
  }
  void close() noexcept {
    owner->active_reader.reset();owner->active_journal = nullptr;
    owner->journal_active = false;owner.reset();
  }
  void rollback() noexcept {
    if (!owner) return;
    reader->phase = IndexedJournalReader::Phase::aborted;
    for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
      if ((*it)->inserted) undo_insert(**it);else undo_erase(**it);
      release_keys(**it);--owner->journal_entries;
    }
    entries.clear();close();
  }
  void commit() noexcept {
    if (!owner) return;
    auto& s = *owner;reader->phase = IndexedJournalReader::Phase::committed;
    s.committed.inserted_rows += s.pending_inserted;s.committed.erased_rows += s.pending_erased;
    s.pending_inserted = 0;s.pending_erased = 0;
    for (auto& undo : entries) {
      if (!undo->inserted) {
        const auto members = undo->row->members.size();
        delete undo->row;--s.retained_rows;s.retained_members -= members;
        s.member_nodes -= members;s.nodes -= 1 + members;
      }
      release_keys(*undo);--s.journal_entries;
    }
    // Only change-view pins and inert pointer records remain caller-owned.
    // Releasing these pins later cannot publish a row or revive a key.
    close();
  }
};

IndexedTable::Journal::Journal(std::unique_ptr<Data> data) noexcept : data_(std::move(data)) {}
IndexedTable::Journal::Journal(Journal&&) noexcept = default;
IndexedTable::Journal& IndexedTable::Journal::operator=(Journal&&) noexcept = default;
IndexedTable::Journal::~Journal() = default;
bool IndexedTable::Journal::active() const noexcept { return data_ && data_->owner; }
std::size_t IndexedTable::Journal::size() const noexcept { return data_ ? data_->entries.size() : 0; }
IndexedTable::ChangeView IndexedTable::Journal::change(std::size_t index) const {
  if (!data_ || index >= data_->entries.size())
    throw Error("invalid_journal", "optimized journal change is absent");
  const auto& entry = *data_->entries[index];return {entry.inserted, entry.handle, entry.pin->get()};
}
void IndexedTable::Journal::rollback() noexcept { if (data_) data_->rollback(); }
void IndexedTable::Journal::commit() noexcept { if (data_) data_->commit(); }
InsertResult IndexedTable::Journal::insert(const Tuple& tuple) {
  if (!data_) throw Error("invalid_journal", "moved-from optimized storage journal");
  static_cast<void>(data_->active());IndexedTable facade(data_->owner);
  return facade.insert_impl(tuple, *data_->reader->work, data_.get());
}
bool IndexedTable::Journal::erase(TupleHandle handle) {
  if (!data_) throw Error("invalid_journal", "moved-from optimized storage journal");
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  auto* row = s.row(handle, work);if (row == nullptr) return false;
  s.mutable_revision();counter_room(s.pending_erased);
  counter_room(s.committed.erased_rows, s.pending_erased + 1);
  room(s.arena.statistics().pins, 1, s.limits.arena_pins);
  auto undo = data_->prepare(false);undo->handle = handle;undo->row = row;
  undo->primary_previous = row->primary_link.resident_previous;
  undo->primary_next = row->primary_link.resident_next;
  undo->id_previous = row->identity_link.resident_previous;
  undo->id_next = row->identity_link.resident_next;
  work.admit(IndexWork{.structural_steps = 1 + work_product(row->members.size(), 4),
      .link_actions = detail::PrimaryDirectory::unlink_actions + detail::PrimaryDirectory::link_actions +
          detail::RowIdDirectory::unlink_actions + detail::RowIdDirectory::link_actions});
  work.admit(IndexWork{.link_actions = work_product(row->members.size(),
      detail::BucketMembers::erase_actions + detail::BucketMembers::insert_actions +
      detail::LiveKeys::erase_actions + detail::LiveKeys::insert_actions +
      detail::RowMembers::erase_actions + detail::KeyDirectory::unlink_actions)});
  detail::admit_tuple_copy(*row->tuple, work);
  for (auto* member = row->members.first(); member != nullptr; member = detail::RowMembers::next(*member)) {
    auto* key = member->key;room(key->journal_references, 1, s.limits.journal_entries);
    detail::admit_tuple_copy(key->tuple, work);
    undo->keys.push_back({key, member, member->bucket_link.previous, member->bucket_link.next,
        key->live_link.previous, key->live_link.next});
  }
  undo->pin.emplace(s.arena.pin(row->allocation));
  for (auto& item : undo->keys) {
    item.key->members.erase_prepaid(*item.member);
    if (item.key->members.size() == 0) {
      item.member->index->live_keys.erase_prepaid(*item.key);--s.live_key_nodes;
    }
  }
  s.primary.unlink_prepaid(*row);s.by_id.unlink_prepaid(*row);
  if (!s.arena.erase(row->allocation)) std::terminate();
  ++s.retained_rows;s.retained_members += row->members.size();++s.pending_erased;++s.revision;
  data_->publish(std::move(undo));return true;
}
IndexedTable::Journal IndexedTable::journal(std::shared_ptr<IndexWorkAllowance> work) {
  if (!work) throw Error("storage_contract", "optimized journal requires an owning finite work grant");
  auto& s = state();s.unlocked();start(*work);
  constexpr auto words = static_cast<std::uint64_t>(
      (sizeof(Journal::Data) + sizeof(IndexedJournalReader) + 2 * sizeof(void*) - 2) / sizeof(void*));
  work->admit(IndexWork{.pointer_slots = words});
  auto reader = std::make_shared<IndexedJournalReader>(std::move(work));
  auto data = std::make_unique<Journal::Data>(state_, std::move(reader));
  s.active_reader = data->reader;s.active_journal = data.get();s.journal_active = true;
  return Journal(std::move(data));
}
