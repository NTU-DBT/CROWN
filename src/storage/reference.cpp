#include "crown/storage/reference.hpp"
#include "owner.hpp"

#include "crown/api/error.hpp"
#include <exception>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <utility>

namespace crown::storage {
namespace {
StorageOwnerId new_owner() { return detail::new_storage_owner(); }

void require(bool value,std::string_view message) { if (!value) throw Error("storage_contract",std::string(message)); }
struct TupleLess {
  using is_transparent=void;
  bool operator()(const Tuple& left,const Tuple& right) const noexcept { return left.values()<right.values(); }
  bool operator()(const Tuple* left,const Tuple* right) const { return (*this)(*left,*right); }
  bool operator()(const Tuple* left,const Tuple& right) const { return (*this)(*left,right); }
  bool operator()(const Tuple& left,const Tuple* right) const { return (*this)(left,*right); }
};
struct JournalReader {
  enum class Phase { active, committed, aborted };
  Phase phase=Phase::active;
};
}  // namespace
struct ReferenceTable::State {
  // Arena owns immutable payloads. Keys borrow stable addresses only while the
  // row is live; ById validates its exact generational allocation identity.
  using Primary=std::map<const Tuple*,TupleId,TupleLess>;
  struct Record { Primary::const_iterator primary; ArenaHandle arena; };
  using ById=std::map<TupleId,Record>;
  using Buckets=std::map<Tuple,std::set<TupleId>,TupleLess>;
  struct Index { Projection projection; Buckets buckets; };
  StorageOwnerId owner=new_owner();
  RelationId relation;
  TupleLayout layout;
  TupleArena arena;
  Primary primary;
  ById by_id;
  std::map<IndexId,Index> indices;
  std::uint64_t last_tuple=0, last_index=0, revision=0;
  bool journal_active=false;
  std::weak_ptr<JournalReader> active_reader;
  State(RelationId r,TupleLayout l):relation(r),layout(std::move(l)),arena(layout) { static_cast<void>(layout.id()); }
  State(const State&)=delete;
  State& operator=(const State&)=delete;
  void mutable_revision() const { if (revision==std::numeric_limits<std::uint64_t>::max()) throw Error("storage_overflow","storage revision exhausted"); }
  void unlocked() const { if (journal_active) throw Error("storage_busy","an exclusive storage journal is active"); }
  InsertResult insert(const Tuple& tuple);
  void input(const Tuple& tuple) const { if (!layout.same_token(tuple.layout())) throw Error("layout_mismatch","tuple belongs to another storage layout"); }
  void owned(TupleHandle handle) const { if (handle.owner!=owner || handle.relation!=relation) throw Error("foreign_handle","tuple handle belongs to another storage owner/relation"); }
  TupleHandle handle(TupleId id) const { return {owner,relation,id}; }
  Index& index(IndexId id) {
    const auto found=indices.find(id); if (found==indices.end()) throw Error("unknown_index","secondary index is absent or was dropped"); return found->second;
  }
  void key(Index& index,const Tuple& tuple) const { if (!index.projection.target().same_token(tuple.layout())) throw Error("layout_mismatch","bucket key belongs to another compiled key layout"); }
  struct EraseMember { Index* index; Buckets::iterator bucket; std::set<TupleId>::iterator member; };
  struct EraseRecord { Primary::const_iterator primary; ById::iterator id; ArenaHandle arena; std::vector<EraseMember> members; };
  std::vector<EraseRecord> prepare_erase(const std::vector<TupleId>& ids) {
    std::vector<EraseRecord> result; result.reserve(ids.size());
    for (const auto id : ids) {
      const auto found=by_id.find(id); require(found!=by_id.end(),"missing primary handle during deletion");
      const auto& tuple=arena.get(found->second.arena);
      require(&tuple==found->second.primary->first,"arena/primary tuple mismatch during deletion");
      EraseRecord record{found->second.primary,found,found->second.arena,{}}; record.members.reserve(indices.size());
      for (auto& [index_id,index] : indices) {
        static_cast<void>(index_id); const auto key=index.projection.apply(tuple);
        const auto bucket=index.buckets.find(key); require(bucket!=index.buckets.end(),"missing secondary bucket during deletion");
        const auto member=bucket->second.find(id); require(member!=bucket->second.end(),"missing secondary member during deletion");
        record.members.push_back({&index,bucket,member});
      }
      result.push_back(std::move(record));
    }
    return result;
  }
  void perform_erase(const std::vector<EraseRecord>& records) {
    // Allocation, projection and ordered-key lookup finish in prepare_erase.
    // Erasing one member never invalidates other members; a bucket is removed
    // only when its last member has already been processed.
    for (const auto& record : records) {
      for (const auto& item : record.members) {
        item.bucket->second.erase(item.member);
        if (item.bucket->second.empty()) item.index->buckets.erase(item.bucket);
      }
      by_id.erase(record.id); primary.erase(record.primary);
      static_cast<void>(arena.erase(record.arena));
    }
  }
};
struct ReferenceTable::Journal::Data {
  struct Key {
    State::Index* index;
    Tuple key;
    std::set<TupleId>::node_type member;
    State::Buckets::node_type bucket;
  };
  struct Undo {
    bool inserted;
    TupleHandle handle{};
    std::uint64_t previous_last=0;
    std::optional<TupleArena::Pin> pin;
    std::vector<Key> keys;
    State::Primary::node_type primary;
    State::ById::node_type id;
    explicit Undo(bool add):inserted(add) {}
  };
  std::shared_ptr<State> owner;
  std::shared_ptr<JournalReader> reader;
  std::vector<std::unique_ptr<Undo>> entries;
  explicit Data(std::shared_ptr<State> value):owner(std::move(value)) {}
  ~Data() { rollback(); }
  State& active() const {
    if (!owner) throw Error("invalid_journal","storage journal is closed");
    return *owner;
  }
  std::unique_ptr<Undo> prepare(bool inserted,const Tuple& tuple) {
    auto& s=active(); auto undo=std::make_unique<Undo>(inserted);
    undo->keys.reserve(s.indices.size());
    for (auto& [id,index] : s.indices) {
      static_cast<void>(id); undo->keys.push_back({&index,index.projection.apply(tuple),{}, {}});
    }
    if (entries.size()==entries.max_size()) throw Error("storage_overflow","storage journal entries exhausted");
    if (entries.size()==entries.capacity()) {
      const auto room=entries.max_size()-entries.size();
      entries.reserve(entries.size()+std::min(room,std::max<std::size_t>(1,entries.size())));
    }
    return undo;
  }
  void undo_insert(Undo& undo) noexcept {
    auto& s=*owner;
    for (auto& key : undo.keys) {
      const auto bucket=key.index->buckets.find(key.key);
      if (bucket==key.index->buckets.end() || bucket->second.erase(undo.handle.tuple)!=1) std::terminate();
      if (bucket->second.empty()) key.index->buckets.erase(bucket);
    }
    const auto id=s.by_id.find(undo.handle.tuple);
    if (id==s.by_id.end()) std::terminate();
    const auto primary=id->second.primary; const auto arena=id->second.arena;
    s.by_id.erase(id); s.primary.erase(primary);
    if (!s.arena.erase(arena)) std::terminate();
    s.last_tuple=undo.previous_last;
  }
  void undo_erase(Undo& undo) noexcept {
    auto& s=*owner;
    s.arena.revive(*undo.pin);
    const auto primary=s.primary.insert(std::move(undo.primary));
    if (!primary.inserted) std::terminate();
    undo.id.mapped().primary=primary.position;
    if (!s.by_id.insert(std::move(undo.id)).inserted) std::terminate();
    for (auto& key : undo.keys) {
      auto bucket=key.index->buckets.end();
      if (!key.bucket.empty()) {
        auto restored=key.index->buckets.insert(std::move(key.bucket));
        if (!restored.inserted) std::terminate();
        bucket=restored.position;
      } else bucket=key.index->buckets.find(key.key);
      if (bucket==key.index->buckets.end() || !bucket->second.insert(std::move(key.member)).inserted) std::terminate();
    }
  }
  void rollback() noexcept {
    if (!owner) return;
    if (reader) reader->phase=JournalReader::Phase::aborted;
    for (auto it=entries.rbegin();it!=entries.rend();++it) {
      if ((*it)->inserted) undo_insert(**it); else undo_erase(**it);
    }
    owner->active_reader.reset(); owner->journal_active=false;
    entries.clear(); owner.reset();
  }
};
ReferenceTable::Journal::Journal(std::unique_ptr<Data> data) noexcept:data_(std::move(data)) {}
ReferenceTable::Journal::Journal(Journal&&) noexcept=default;
ReferenceTable::Journal& ReferenceTable::Journal::operator=(Journal&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
ReferenceTable::Journal::~Journal()=default;
bool ReferenceTable::Journal::active() const noexcept { return data_ && data_->owner; }
std::size_t ReferenceTable::Journal::size() const noexcept { return data_ ? data_->entries.size() : 0; }
ReferenceTable::ChangeView ReferenceTable::Journal::change(std::size_t index) const {
  if (!data_ || index>=data_->entries.size()) throw Error("invalid_journal","storage journal change is absent");
  const auto& entry=*data_->entries[index]; return {entry.inserted,entry.handle,entry.pin->get()};
}
void ReferenceTable::Journal::rollback() noexcept { if (data_) data_->rollback(); }
void ReferenceTable::Journal::commit() noexcept {
  if (!active()) return;
  if (data_->reader) data_->reader->phase=JournalReader::Phase::committed;
  data_->owner->active_reader.reset();
  data_->owner->journal_active=false;
  // Change pins survive commit; releasing the last table State may still
  // destroy its rows, indexes and arena metadata here.
  data_->owner.reset();
}
InsertResult ReferenceTable::Journal::insert(const Tuple& tuple) {
  if (!data_) throw Error("invalid_journal","moved-from storage journal");
  auto& s=data_->active(); s.input(tuple);
  const auto found=s.primary.find(tuple); if (found!=s.primary.end()) return {false,s.handle(found->second)};
  // Undo and ordinary insertion each project the registered indexes; this
  // duplicate preparation is part of the legacy journal insertion cost.
  auto undo=data_->prepare(true,tuple); undo->previous_last=s.last_tuple;
  const auto result=s.insert(tuple); undo->handle=result.handle;
  try { undo->pin.emplace(s.arena.pin(s.by_id.at(result.handle.tuple).arena)); }
  catch (...) { data_->undo_insert(*undo); throw; }
  data_->entries.push_back(std::move(undo)); return result;
}
bool ReferenceTable::Journal::erase(TupleHandle handle) {
  if (!data_) throw Error("invalid_journal","moved-from storage journal");
  auto& s=data_->active(); s.owned(handle);
  const auto found=s.by_id.find(handle.tuple); if (found==s.by_id.end()) return false;
  s.mutable_revision();
  auto undo=data_->prepare(false,s.arena.get(found->second.arena)); undo->handle=handle;
  undo->pin.emplace(s.arena.pin(found->second.arena));
  // All allocations and projected keys precede extraction. Later rollback
  // reinserts owned map/set nodes and revives the exact pinned allocation.
  for (auto& key : undo->keys) {
    const auto bucket=key.index->buckets.find(key.key);
    if (bucket==key.index->buckets.end()) std::terminate();
    key.member=bucket->second.extract(handle.tuple);
    if (key.member.empty()) std::terminate();
    if (bucket->second.empty()) key.bucket=key.index->buckets.extract(bucket);
  }
  const auto arena=found->second.arena;
  undo->primary=s.primary.extract(found->second.primary); undo->id=s.by_id.extract(found);
  if (!s.arena.erase(arena)) std::terminate();
  ++s.revision; data_->entries.push_back(std::move(undo)); return true;
}
ReferenceTable::Journal ReferenceTable::journal() {
  auto& s=state(); s.unlocked(); auto data=std::make_unique<Journal::Data>(state_);
  s.journal_active=true; return Journal(std::move(data));
}

struct ReferenceTable::Cursor::Data {
  std::weak_ptr<State> owner;
  std::shared_ptr<JournalReader> journal;
  std::uint64_t revision;
  bool bucket_mode=false, empty=false;
  State::Primary::const_iterator primary, primary_end;
  std::set<TupleId>::const_iterator member, member_end;
  Data(const std::shared_ptr<State>& state):owner(state),revision(state->revision) {}
};
ReferenceTable::Cursor::Cursor(std::unique_ptr<Data> data):data_(std::move(data)) {}
ReferenceTable::Cursor::Cursor(Cursor&&) noexcept=default;
ReferenceTable::Cursor& ReferenceTable::Cursor::operator=(Cursor&&) noexcept=default;
ReferenceTable::Cursor::~Cursor()=default;
std::optional<TupleHandle> ReferenceTable::Cursor::next() {
  if (!data_) throw Error("invalid_cursor","moved-from storage cursor");
  const auto owner=data_->owner.lock();
  if (!owner) throw Error("invalid_cursor","storage cursor owner was destroyed");
  if (data_->journal && data_->journal->phase==JournalReader::Phase::aborted)
    throw Error("invalid_cursor","owning journal was rolled back");
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock()!=data_->journal)) owner->unlocked();
  if (owner->revision!=data_->revision) throw Error("invalid_cursor","storage cursor invalidated by mutation");
  if (data_->empty) return {};
  if (data_->bucket_mode) {
    if (data_->member==data_->member_end) return {};
    return owner->handle(*data_->member++);
  }
  if (data_->primary==data_->primary_end) return {};
  return owner->handle((data_->primary++)->second);
}
std::optional<ReferenceTable::Cursor::Entry> ReferenceTable::Cursor::next_entry() {
  if (!data_) throw Error("invalid_cursor","moved-from storage cursor");
  const auto owner=data_->owner.lock();
  if (!owner) throw Error("invalid_cursor","storage cursor owner was destroyed");
  if (data_->journal && data_->journal->phase==JournalReader::Phase::aborted)
    throw Error("invalid_cursor","owning journal was rolled back");
  if (!data_->journal || (owner->journal_active && owner->active_reader.lock()!=data_->journal)) owner->unlocked();
  if (owner->revision!=data_->revision) throw Error("invalid_cursor","storage cursor invalidated by mutation");
  if (data_->empty) return {};
  if (data_->bucket_mode) {
    if (data_->member==data_->member_end) return {};
    const auto id=*data_->member;
    const auto found=owner->by_id.find(id);
    require(found!=owner->by_id.end(),"missing reference bucket row during borrowed traversal");
    const auto& tuple=owner->arena.get(found->second.arena);
    ++data_->member;return Entry{owner->handle(id),tuple};
  }
  if (data_->primary==data_->primary_end) return {};
  const auto entry=data_->primary++;
  return Entry{owner->handle(entry->second),*entry->first};
}
ReferenceTable::Cursor ReferenceTable::Journal::live() const {
  if (!data_) throw Error("invalid_journal","moved-from storage journal");
  auto& state=data_->active();
  if (!data_->reader) data_->reader=std::make_shared<JournalReader>();
  auto cursor=std::make_unique<Cursor::Data>(data_->owner); cursor->journal=data_->reader;
  cursor->primary=state.primary.begin(); cursor->primary_end=state.primary.end();
  state.active_reader=data_->reader; return Cursor(std::move(cursor));
}
ReferenceTable::Cursor ReferenceTable::Journal::bucket_cursor(IndexId id,const Tuple& key) const {
  if (!data_) throw Error("invalid_journal","moved-from storage journal");
  auto& state=data_->active(); auto& index=state.index(id); state.key(index,key);
  if (!data_->reader) data_->reader=std::make_shared<JournalReader>();
  auto cursor=std::make_unique<Cursor::Data>(data_->owner); cursor->journal=data_->reader; cursor->bucket_mode=true;
  const auto found=index.buckets.find(key);
  if (found==index.buckets.end()) cursor->empty=true;
  else { cursor->member=found->second.begin(); cursor->member_end=found->second.end(); }
  state.active_reader=data_->reader; return Cursor(std::move(cursor));
}
ReferenceTable::ReferenceTable(RelationId relation,TupleLayout layout):state_(std::make_shared<State>(relation,std::move(layout))) {}
ReferenceTable::ReferenceTable(std::shared_ptr<State> state):state_(std::move(state)) {}
ReferenceTable ReferenceTable::snapshot_copy() const {
  const auto& source=state();
  source.unlocked();
  auto copy=std::make_shared<State>(source.relation,source.layout);
  for (const auto& [tuple,id] : source.primary) {
    const auto handle=copy->arena.insert(*tuple);
    const auto row=copy->primary.emplace(&copy->arena.get(handle),id).first;
    copy->by_id.emplace(id,State::Record{row,handle});
  }
  // Containers and arena identities are new; Tuple copies still follow their
  // legacy-deep or native-shared immutable payload representation.
  copy->indices=source.indices;
  copy->last_tuple=source.last_tuple; copy->last_index=source.last_index; copy->revision=source.revision;
  return ReferenceTable(std::move(copy));
}
ReferenceTable::~ReferenceTable()=default;
ReferenceTable::ReferenceTable(ReferenceTable&&) noexcept=default;
ReferenceTable& ReferenceTable::operator=(ReferenceTable&&) noexcept=default;
ReferenceTable::State& ReferenceTable::state() const { if (!state_) throw Error("invalid_storage","moved-from storage table"); return *state_; }
StorageOwnerId ReferenceTable::owner() const { return state().owner; }
RelationId ReferenceTable::relation() const { return state().relation; }
const TupleLayout& ReferenceTable::layout() const { return state().layout; }
std::size_t ReferenceTable::size() const { return state().primary.size(); }
std::uint64_t ReferenceTable::revision() const { return state().revision; }

InsertResult ReferenceTable::insert(const Tuple& tuple) {
  auto& s=state(); s.unlocked(); return s.insert(tuple);
}
InsertResult ReferenceTable::State::insert(const Tuple& tuple) {
  auto& s=*this; s.input(tuple);
  const auto found=s.primary.find(tuple); if (found!=s.primary.end()) return {false,s.handle(found->second)};
  s.mutable_revision(); if (s.last_tuple==std::numeric_limits<std::uint64_t>::max()) throw Error("storage_overflow","tuple IDs exhausted");
  const TupleId id{s.last_tuple+1};
  struct Prepared { State::Index* index; Tuple key; std::optional<State::Buckets::iterator> bucket; bool created=false, member=false; };
  std::vector<Prepared> prepared; prepared.reserve(s.indices.size());
  for (auto& [index_id,index] : s.indices) { static_cast<void>(index_id); prepared.push_back({&index,index.projection.apply(tuple),{}}); }
  const auto allocated=s.arena.insert(tuple);
  std::optional<State::Primary::iterator> record;
  bool by_id=false;
  try {
    const auto [entry,inserted]=s.primary.emplace(&s.arena.get(allocated),id); require(inserted,"new tuple unexpectedly exists");
    record=entry;
    by_id=s.by_id.emplace(id,State::Record{entry,allocated}).second; require(by_id,"new tuple ID unexpectedly exists");
    for (auto& item : prepared) {
      const auto [bucket,created]=item.index->buckets.try_emplace(item.key);
      item.bucket=bucket; item.created=created;
      item.member=bucket->second.insert(id).second; require(item.member,"new tuple already in a secondary bucket");
    }
  } catch (...) {
    for (auto& item : prepared) if (item.bucket) {
      if (item.member) (*item.bucket)->second.erase(id);
      if (item.created) item.index->buckets.erase(*item.bucket);
    }
    if (by_id) s.by_id.erase(id);
    if (record) s.primary.erase(*record);
    static_cast<void>(s.arena.erase(allocated)); throw;
  }
  s.last_tuple=id.value; ++s.revision; return {true,s.handle(id)};
}
std::optional<TupleHandle> ReferenceTable::find(const Tuple& tuple) const {
  auto& s=state(); s.input(tuple); const auto found=s.primary.find(tuple); if (found==s.primary.end()) return {}; return s.handle(found->second);
}
const Tuple* ReferenceTable::get(TupleHandle handle) const {
  auto& s=state(); s.owned(handle); const auto found=s.by_id.find(handle.tuple); return found==s.by_id.end() ? nullptr : &s.arena.get(found->second.arena);
}
TupleArena::Pin ReferenceTable::pin(TupleHandle handle) const {
  auto& s=state(); s.owned(handle); const auto found=s.by_id.find(handle.tuple);
  if (found==s.by_id.end()) throw Error("stale_handle","tuple is no longer a live table record");
  return s.arena.pin(found->second.arena);
}
ArenaStatistics ReferenceTable::arena_statistics() const { return state().arena.statistics(); }
bool ReferenceTable::erase(const Tuple& tuple) { state().unlocked(); const auto handle=find(tuple); return handle && erase(*handle); }
bool ReferenceTable::erase(TupleHandle handle) {
  auto& s=state(); s.unlocked(); s.owned(handle); if (!s.by_id.contains(handle.tuple)) return false;
  s.mutable_revision(); const auto prepared=s.prepare_erase({handle.tuple}); s.perform_erase(prepared); ++s.revision; return true;
}
IndexId ReferenceTable::add_index(Projection projection) {
  auto& s=state(); s.unlocked(); if (!s.layout.same_token(projection.source())) throw Error("layout_mismatch","secondary projection belongs to another source layout");
  for (const auto& [id,index] : s.indices) if (index.projection.same_token(projection)) return id;
  s.mutable_revision(); if (s.last_index==std::numeric_limits<std::uint64_t>::max()) throw Error("storage_overflow","index IDs exhausted");
  State::Index index{std::move(projection),{}};
  for (const auto& [tuple,id] : s.primary) index.buckets[index.projection.apply(*tuple)].insert(id);
  const IndexId id{s.last_index+1}; s.indices.emplace(id,std::move(index)); s.last_index=id.value; ++s.revision; return id;
}
bool ReferenceTable::drop_index(IndexId index) {
  auto& s=state(); s.unlocked(); const auto found=s.indices.find(index); if (found==s.indices.end()) return false;
  s.mutable_revision(); s.indices.erase(found); ++s.revision; return true;
}
std::vector<IndexId> ReferenceTable::indices() const { std::vector<IndexId> result; for (const auto& [id,index] : state().indices) { static_cast<void>(index); result.push_back(id); } return result; }
Projection ReferenceTable::projection(IndexId index) const { return state().index(index).projection; }
std::size_t ReferenceTable::key_count(IndexId index) const { return state().index(index).buckets.size(); }
std::vector<Tuple> ReferenceTable::keys(IndexId index) const { std::vector<Tuple> result; for (const auto& [key,members] : state().index(index).buckets) { static_cast<void>(members); result.push_back(key); } return result; }
std::vector<TupleHandle> ReferenceTable::bucket(IndexId index,const Tuple& key) const {
  auto& s=state(); auto& secondary=s.index(index); s.key(secondary,key);
  const auto found=secondary.buckets.find(key); std::vector<TupleHandle> result;
  if (found!=secondary.buckets.end()) for (const auto id : found->second) result.push_back(s.handle(id));
  return result;
}
std::size_t ReferenceTable::erase_key(IndexId index,const Tuple& key) {
  auto& s=state(); s.unlocked(); auto& secondary=s.index(index); s.key(secondary,key);
  const auto found=secondary.buckets.find(key); if (found==secondary.buckets.end()) return 0;
  s.mutable_revision(); const std::vector<TupleId> ids(found->second.begin(),found->second.end());
  const auto prepared=s.prepare_erase(ids); s.perform_erase(prepared); ++s.revision; return ids.size();
}
void ReferenceTable::clear() {
  auto& s=state(); s.unlocked(); if (s.primary.empty()) return; s.mutable_revision();
  for (auto& [id,index] : s.indices) { static_cast<void>(id); index.buckets.clear(); }
  s.by_id.clear(); s.primary.clear(); s.arena.clear(); ++s.revision;
}
ReferenceTable::Cursor ReferenceTable::live() const {
  const auto& s=state(); s.unlocked(); auto data=std::make_unique<Cursor::Data>(state_);
  data->primary=s.primary.begin(); data->primary_end=s.primary.end(); return Cursor(std::move(data));
}
ReferenceTable::Cursor ReferenceTable::bucket_cursor(IndexId index,const Tuple& key) const {
  auto& s=state(); s.unlocked(); auto& secondary=s.index(index); s.key(secondary,key); auto data=std::make_unique<Cursor::Data>(state_); data->bucket_mode=true;
  const auto found=secondary.buckets.find(key);
  if (found==secondary.buckets.end()) data->empty=true;
  else { data->member=found->second.begin(); data->member_end=found->second.end(); }
  return Cursor(std::move(data));
}
std::vector<Tuple> ReferenceTable::snapshot() const { std::vector<Tuple> result; for (const auto& [tuple,id] : state().primary) { static_cast<void>(id); result.push_back(*tuple); } return result; }
void ReferenceTable::check_invariants() const {
  auto& s=state(); s.arena.check_invariants();
  require(s.primary.size()==s.by_id.size() && s.primary.size()==s.arena.statistics().live_records,"primary/handle/arena size mismatch");
  for (auto record=s.primary.cbegin();record!=s.primary.cend();++record) {
    s.input(*record->first); s.layout.validate_view(record->first->values());
    require(record->second.value>0 && record->second.value<=s.last_tuple,"invalid live tuple ID");
    const auto found=s.by_id.find(record->second); require(found!=s.by_id.end() && found->second.primary==record,"primary/handle index mismatch");
    require(&s.arena.get(found->second.arena)==record->first,"primary/arena generation mismatch");
  }
  // This explicit diagnostic rebuilds every complete secondary index,
  // including projected keys and member nodes; it is not mutation-path work.
  for (const auto& [index_id,index] : s.indices) {
    require(index_id.value>0 && index_id.value<=s.last_index,"invalid live index ID");
    State::Buckets expected;
    for (const auto& [tuple,id] : s.primary) expected[index.projection.apply(*tuple)].insert(id);
    require(expected==index.buckets,"secondary index differs from primary projection");
    for (const auto& [key,members] : index.buckets) { require(index.projection.target().same_token(key.layout()) && !members.empty(),"empty or foreign secondary bucket"); }
  }
}
}  // namespace crown::storage

namespace crown::storage {
struct ReferenceTable::IndexKeyCursor::Data {
  std::weak_ptr<State> owner;
  std::uint64_t revision;
  State::Buckets::const_iterator current, end;
};
ReferenceTable::IndexKeyCursor::IndexKeyCursor(std::unique_ptr<Data> data):data_(std::move(data)) {}
ReferenceTable::IndexKeyCursor::IndexKeyCursor(IndexKeyCursor&&) noexcept=default;
ReferenceTable::IndexKeyCursor& ReferenceTable::IndexKeyCursor::operator=(IndexKeyCursor&&) noexcept=default;
ReferenceTable::IndexKeyCursor::~IndexKeyCursor()=default;
std::optional<ReferenceTable::IndexKeyCursor::Entry> ReferenceTable::IndexKeyCursor::next() {
  if (!data_) throw Error("invalid_cursor","moved-from index-key cursor");
  const auto owner=data_->owner.lock();
  if (!owner) throw Error("invalid_cursor","index-key cursor owner was destroyed");
  owner->unlocked();
  if (owner->revision!=data_->revision) throw Error("invalid_cursor","index-key cursor invalidated by mutation");
  if (data_->current==data_->end) return {};
  const auto& item=*data_->current++;
  return Entry{item.first,item.second.size()};
}
ReferenceTable::IndexKeyCursor ReferenceTable::index_keys(IndexId id) const {
  auto& s=state(); s.unlocked(); const auto& index=s.index(id);
  return IndexKeyCursor(std::make_unique<IndexKeyCursor::Data>(IndexKeyCursor::Data{
    state_,s.revision,index.buckets.begin(),index.buckets.end()}));
}
}
