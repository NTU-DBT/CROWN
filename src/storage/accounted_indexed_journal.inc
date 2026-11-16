// Included after AccountedIndexedTable::State. All inverse node/link actions
// use the mutation's original work grant and direct allocator headers.
struct AccountedIndexedTable::Journal::Data {
  struct Key {
    AccountedIndexedKey* key;
    AccountedIndexedMember* member;
    AccountedIndexedMember* previous;
    AccountedIndexedMember* next;
    AccountedIndexedKey* live_previous;
    AccountedIndexedKey* live_next;
  };
  struct Undo {
    bool inserted;
    TupleHandle handle{};
    std::uint64_t previous_last = 0;
    AccountedIndexedRow* row = nullptr;
    AccountedIndexedRow* primary_previous = nullptr;
    AccountedIndexedRow* primary_next = nullptr;
    AccountedIndexedRow* id_previous = nullptr;
    AccountedIndexedRow* id_next = nullptr;
    std::optional<AccountedTupleArena::Pin> pin;
    AccountedVector<Key> keys;
    Undo(bool value, const MemoryAccount& account, MemoryAttribution tag)
        : inserted(value), keys(MemoryAllocator<Key>(account, MemoryPurpose::journal_undo, tag)) {}
  };
  using Owner = resource::AccountedUnique<Undo>;
  struct Prepared {
    Owner record;
    AccountedVector<Owner> replacement;
    Prepared(const MemoryAccount& account, MemoryAttribution tag)
        : replacement(MemoryAllocator<Owner>(account, MemoryPurpose::journal_undo, tag)) {}
    Undo* operator->() const noexcept { return record.get(); }
    [[nodiscard]] explicit operator bool() const noexcept { return bool(record); }
  };
  std::shared_ptr<State> owner;
  std::weak_ptr<State> report_owner;
  std::shared_ptr<AccountedIndexedJournalReader> reader;
  AccountedVector<Owner> entries;
  bool committed = false;

  Data(std::shared_ptr<State> state, std::shared_ptr<AccountedIndexedJournalReader> authority)
      : owner(std::move(state)), report_owner(owner), reader(std::move(authority)),
        entries(MemoryAllocator<Owner>(owner->account, MemoryPurpose::journal_undo, owner->tag)) {}
  ~Data() {
    rollback();
    if (committed) if (auto state = report_owner.lock()) {
      if (state->retained_history < entries.size()) std::terminate();
      state->retained_history -= entries.size();
    }
  }
  State& active() const {
    if (!owner || !owner->journal_active || owner->active_journal != this ||
        reader->phase != AccountedIndexedJournalReader::Phase::active)
      throw IndexFailure(IndexFault::invalid_journal);
    return *owner;
  }
  Prepared prepare(bool inserted) {
    auto& s = active();auto& work = *reader->work;
    room(entries.size(), 1, s.limits.journal_entries);
    if (entries.size() == entries.max_size()) throw IndexFailure(IndexFault::overflow);
    room(s.retained_history, entries.size() + 1, std::numeric_limits<std::size_t>::max());
    Prepared result(s.account, s.tag);
    if (entries.size() == entries.capacity()) {
      const auto remaining = s.limits.journal_entries - entries.size();
      const auto extra = std::min(remaining, std::max<std::size_t>(1, entries.size()));
      work.admit(IndexWork{.structural_steps = static_cast<std::uint64_t>(entries.size())});
      reserve_records(result.replacement, entries.size() + extra, work);
    }
    constexpr auto words = static_cast<std::uint64_t>((sizeof(Undo) + sizeof(void*) - 1) / sizeof(void*));
    work.admit(IndexWork{.structural_steps = 1, .pointer_slots = words});
    result.record = resource::make_accounted_unique<Undo>(s.tag, s.account, MemoryPurpose::journal_undo, inserted, s.account, s.tag);
    reserve_records(result->keys, s.indices.size(), work);return result;
  }
  void publish(Prepared preparation) noexcept {
    if (preparation.replacement.capacity() != 0) {
      for (auto& entry : entries) preparation.replacement.push_back(std::move(entry));
      entries.swap(preparation.replacement);
    }
    if (entries.size() >= entries.capacity() || !preparation->pin) std::terminate();
    for (auto& item : preparation->keys) ++item.key->journal_references;
    ++owner->journal_entries;entries.push_back(std::move(preparation.record));
  }
  void release_keys(Undo& undo) noexcept {
    for (auto& item : undo.keys) {
      auto* key = item.key;
      if (key->journal_references == 0) std::terminate();
      --key->journal_references;
      if (key->journal_references == 0 && key->members.size() == 0) {
        if (key->live_link.owner != nullptr) std::terminate();
        destroy_indexed_node(key);--owner->key_nodes;--owner->nodes;
      }
    }
  }
  void undo_insert(Undo& undo) noexcept {
    auto& s = *owner;auto& row = *undo.row;
    s.primary.unlink_prepaid(row);s.by_id.unlink_prepaid(row);
    while (auto* member = row.members.first()) {
      auto* key = member->key;auto* index = member->index;
      key->members.erase_prepaid(*member);destroy_indexed_node(member);--s.member_nodes;--s.nodes;
      if (key->members.size() == 0) {
        index->live_keys.erase_prepaid(*key);--s.live_key_nodes;
        classify_indexed_node(*key, AllocationLifetime::retained);classify(key->tuple, AllocationLifetime::retained);
      }
    }
    if (!s.arena.erase(row.allocation)) std::terminate();
    destroy_indexed_node(&row);--s.nodes;--s.pending_inserted;s.last_tuple = undo.previous_last;
  }
  void undo_erase(Undo& undo) noexcept {
    auto& s = *owner;auto& row = *undo.row;
    s.arena.revive(*undo.pin);classify_indexed_node(row, AllocationLifetime::active);
    s.primary.link_between_prepaid(row, row.primary_link.hash, undo.primary_previous, undo.primary_next);
    s.by_id.link_between_prepaid(row, row.identity_link.hash, undo.id_previous, undo.id_next);
    for (auto& item : undo.keys) {
      auto& key = *item.key;
      if (key.members.size() == 0) {
        item.member->index->live_keys.insert_between_prepaid(key, item.live_previous, item.live_next);
        classify_indexed_node(key, AllocationLifetime::active);classify(key.tuple, AllocationLifetime::active);
        ++s.live_key_nodes;
      }
      classify_indexed_node(*item.member, AllocationLifetime::active);
      key.members.insert_between_prepaid(*item.member, item.previous, item.next);
    }
    --s.retained_rows;s.retained_members -= row.members.size();--s.pending_erased;
  }
  void close() noexcept {
    owner->active_reader.reset();owner->active_journal = nullptr;owner->journal_active = false;owner.reset();
  }
  void rollback() noexcept {
    if (!owner) return;
    reader->phase = AccountedIndexedJournalReader::Phase::aborted;
    for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
      if ((*it)->inserted) undo_insert(**it);else undo_erase(**it);
      release_keys(**it);--owner->journal_entries;
    }
    entries.clear();close();
  }
  void commit() noexcept {
    if (!owner) return;
    auto& s = *owner;reader->phase = AccountedIndexedJournalReader::Phase::committed;
    s.committed.inserted_rows += s.pending_inserted;s.committed.erased_rows += s.pending_erased;
    s.pending_inserted = 0;s.pending_erased = 0;
    for (auto& undo : entries) {
      if (!undo->inserted) {
        const auto members = undo->row->members.size();
        destroy_indexed_node(undo->row);--s.retained_rows;s.retained_members -= members;
        s.member_nodes -= members;s.nodes -= 1 + members;
      }
      release_keys(*undo);--s.journal_entries;
      undo.get_deleter().set_lifetime(undo.get(), AllocationLifetime::retained);
      if (undo->keys.capacity()) undo->keys.get_allocator().set_allocation_lifetime(undo->keys.data(), undo->keys.capacity(), AllocationLifetime::retained);
    }
    if (entries.capacity()) entries.get_allocator().set_allocation_lifetime(entries.data(), entries.capacity(), AllocationLifetime::retained);
    s.retained_history += entries.size();committed = true;
    // The shared reader remains active authority for valid committed cursors;
    // all its actual control storage stays charged until real final release.
    close();
  }
};

AccountedIndexedTable::Journal::Journal(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
AccountedIndexedTable::Journal::Journal(Journal&&) noexcept = default;
AccountedIndexedTable::Journal& AccountedIndexedTable::Journal::operator=(Journal&&) noexcept = default;
AccountedIndexedTable::Journal::~Journal() = default;
bool AccountedIndexedTable::Journal::active() const noexcept { return data_ && data_->owner; }
std::size_t AccountedIndexedTable::Journal::size() const noexcept { return data_ ? data_->entries.size() : 0; }
AccountedIndexedTable::ChangeView AccountedIndexedTable::Journal::change(std::size_t index) const & {
  if (!data_ || index >= data_->entries.size()) throw IndexFailure(IndexFault::invalid_journal);
  const auto& entry = *data_->entries[index];return {entry.inserted, entry.handle, entry.pin->get()};
}
void AccountedIndexedTable::Journal::rollback() noexcept { if (data_) data_->rollback(); }
void AccountedIndexedTable::Journal::commit() noexcept {
  if (!active()) return;
  data_->commit();data_.get_deleter().set_lifetime(data_.get(), AllocationLifetime::retained);
}
InsertResult AccountedIndexedTable::Journal::insert(const AccountedTuple& tuple) {
  if (!data_) throw IndexFailure(IndexFault::invalid_journal);
  static_cast<void>(data_->active());return AccountedIndexedTable::insert_impl(data_->owner, tuple, *data_->reader->work, data_.get());
}
bool AccountedIndexedTable::Journal::erase(TupleHandle handle) {
  if (!data_) throw IndexFailure(IndexFault::invalid_journal);
  auto& s = data_->active();auto& work = *data_->reader->work;start(work);
  auto* row = s.row(handle, work);if (row == nullptr) return false;
  s.mutable_revision();counter_room(s.pending_erased);counter_room(s.committed.erased_rows, s.pending_erased + 1);
  room(s.arena.statistics().pins, 1, s.limits.arena_pins);
  auto undo = data_->prepare(false);undo->handle = handle;undo->row = row;
  undo->primary_previous = row->primary_link.resident_previous;undo->primary_next = row->primary_link.resident_next;
  undo->id_previous = row->identity_link.resident_previous;undo->id_next = row->identity_link.resident_next;
  work.admit(IndexWork{.structural_steps = 1 + work_product(row->members.size(), 4),
      .link_actions = detail::AccountedPrimaryDirectory::unlink_actions + detail::AccountedPrimaryDirectory::link_actions +
          detail::AccountedRowIdDirectory::unlink_actions + detail::AccountedRowIdDirectory::link_actions});
  work.admit(IndexWork{.link_actions = work_product(row->members.size(),
      detail::AccountedBucketMembers::erase_actions + detail::AccountedBucketMembers::insert_actions +
      detail::AccountedLiveKeys::erase_actions + detail::AccountedLiveKeys::insert_actions +
      detail::AccountedRowMembers::erase_actions + detail::AccountedKeyDirectory::unlink_actions)});
  detail::accounted_admit_tuple_copy(*row->tuple, work);
  for (auto* member = row->members.first(); member; member = detail::AccountedRowMembers::next(*member)) {
    auto* key = member->key;room(key->journal_references, 1, s.limits.journal_entries);
    detail::accounted_admit_tuple_copy(key->tuple, work);
    undo->keys.push_back({key, member, member->bucket_link.previous, member->bucket_link.next,
        key->live_link.previous, key->live_link.next});
  }
  undo->pin.emplace(s.arena.pin(row->allocation));
  for (auto& item : undo->keys) {
    item.key->members.erase_prepaid(*item.member);classify_indexed_node(*item.member, AllocationLifetime::retained);
    if (item.key->members.size() == 0) {
      item.member->index->live_keys.erase_prepaid(*item.key);--s.live_key_nodes;
      classify_indexed_node(*item.key, AllocationLifetime::retained);classify(item.key->tuple, AllocationLifetime::retained);
    }
  }
  s.primary.unlink_prepaid(*row);s.by_id.unlink_prepaid(*row);
  if (!s.arena.erase(row->allocation)) std::terminate();
  classify_indexed_node(*row, AllocationLifetime::retained);
  ++s.retained_rows;s.retained_members += row->members.size();++s.pending_erased;++s.revision;
  data_->publish(std::move(undo));return true;
}
AccountedIndexedTable::Journal AccountedIndexedTable::journal(AccountedIndexWork work) {
  if (!work) throw IndexFailure(IndexFault::contract);
  auto& s = state();s.unlocked();if (!work.same_account(s.account)) throw IndexFailure(IndexFault::contract);
  start(*work);
  constexpr auto words = static_cast<std::uint64_t>((sizeof(Journal::Data) + sizeof(AccountedIndexedJournalReader) + 2 * sizeof(void*) - 2) / sizeof(void*));
  work.get()->admit(IndexWork{.pointer_slots = words});
  auto reader = resource::make_accounted_shared<AccountedIndexedJournalReader>(s.tag, s.account, MemoryPurpose::cursor, std::move(work));
  auto data = resource::make_accounted_unique<Journal::Data>(s.tag, s.account, MemoryPurpose::journal_undo, state_, std::move(reader));
  s.active_reader = data->reader;s.active_journal = data.get();s.journal_active = true;return Journal(std::move(data));
}
