#include "crown/storage/keyed.hpp"
#include "crown/api/error.hpp"

#include <algorithm>
#include <cstring>
#include <limits>
#include <mutex>
#include <new>
#include <type_traits>

namespace crown::storage::keyed {
namespace {
// Each statistics counter has one writing thread at a time (the writer, or
// the collector thread for frees in background mode): a relaxed load/store
// pair avoids a locked read-modify-write on the retire path.
template <class T>
void add(std::atomic<T>& counter, T delta) noexcept {
  counter.store(counter.load(std::memory_order_relaxed) + delta, std::memory_order_relaxed);
}
template <class T>
void subtract(std::atomic<T>& counter, T delta) noexcept {
  counter.store(counter.load(std::memory_order_relaxed) - delta, std::memory_order_relaxed);
}
// Live collectors and the totals of destroyed ones (process_gc_statistics).
struct Registry {
  std::mutex mutex;
  Collector* live = nullptr;  // intrusive list of live collectors
  GcStatistics destroyed;
};
Registry& registry() {
  static Registry instance;
  return instance;
}
void accumulate(GcStatistics& total, const GcStatistics& part) noexcept {
  total.collections += part.collections;
  total.retired_objects += part.retired_objects;
  total.freed_objects += part.freed_objects;
  total.retired_bytes += part.retired_bytes;
  total.freed_bytes += part.freed_bytes;
  total.pending_bytes += part.pending_bytes;
}
[[noreturn, gnu::cold, gnu::noinline]] void fail(const char* message) { throw Error("keyed_contract", message); }
inline void require(bool value, const char* message) {
  if (!value) [[unlikely]] fail(message);
}
static_assert(std::is_trivially_destructible_v<ScalarView>);
static_assert(alignof(ScalarView) <= alignof(std::max_align_t));
static_assert(sizeof(KeyRecord) % alignof(ScalarView) == 0);

inline std::uint32_t tag_of(std::uint64_t hash) noexcept { return static_cast<std::uint32_t>(hash >> 32); }
inline std::uint64_t slot_of(std::uint32_t tag, std::uint32_t id) noexcept {
  return (static_cast<std::uint64_t>(tag) << 32) | (static_cast<std::uint64_t>(id) + 1);
}
inline std::uint32_t slot_id(std::uint64_t slot) noexcept { return static_cast<std::uint32_t>(slot) - 1; }
inline std::uint32_t slot_tag(std::uint64_t slot) noexcept { return static_cast<std::uint32_t>(slot >> 32); }

// Backward-shift deletion for linear probing over (tag, id) slots.
void erase_tagged(std::vector<std::uint64_t>& slots, std::size_t mask, std::size_t i) noexcept {
  for (std::size_t j = (i + 1) & mask;; j = (j + 1) & mask) {
    const auto slot = slots[j];
    if (!slot) break;
    const std::size_t home = slot_tag(slot) & mask;
    const bool stays = i <= j ? (i < home && home <= j) : (i < home || home <= j);
    if (!stays) { slots[i] = slot; i = j; }
  }
  slots[i] = 0;
}
void rehash_tagged(std::vector<std::uint64_t>& slots, std::size_t& mask, std::size_t capacity) {
  std::vector<std::uint64_t> next(capacity, 0);
  const std::size_t next_mask = capacity - 1;
  for (const auto slot : slots) {
    if (!slot) continue;
    std::size_t i = slot_tag(slot) & next_mask;
    while (next[i]) i = (i + 1) & next_mask;
    next[i] = slot;
  }
  slots.swap(next);
  mask = next_mask;
}
std::size_t capacity_for(std::size_t entries) {
  std::size_t capacity = 16;
  while (capacity < entries * 2) capacity *= 2;
  return capacity;
}

std::uint64_t hash_bytes(std::string_view text) noexcept {
  std::uint64_t h = 0x9e3779b97f4a7c15ULL ^ text.size();
  std::size_t i = 0;
  for (; i + 8 <= text.size(); i += 8) {
    std::uint64_t word;
    std::memcpy(&word, text.data() + i, 8);
    h = combine(h, word);
  }
  std::uint64_t tail = 0;
  std::memcpy(&tail, text.data() + i, text.size() - i);
  return mix(combine(h, tail));
}
void free_record(void* object) noexcept {
  auto* record = static_cast<KeyRecord*>(object);
  if (record->budget) record->budget->release(record->bytes);
  ::operator delete(object);
}
}  // namespace

std::uint64_t hash_cell(const ScalarView& cell) noexcept {
  const auto tag = static_cast<std::uint64_t>(cell.index()) * 0x51ed270b27a3d1c5ULL;
  if (const auto* number = std::get_if<std::int64_t>(&cell)) return mix(static_cast<std::uint64_t>(*number) ^ tag);
  if (const auto* text = std::get_if<std::string_view>(&cell)) return hash_bytes(*text) ^ tag;
  if (const auto* flag = std::get_if<bool>(&cell)) return mix((*flag ? 1U : 0U) ^ tag);
  if (const auto* date = std::get_if<Date>(&cell)) {
    const std::uint64_t days = static_cast<std::uint32_t>(date->epoch_days());
    return mix(days ^ tag);
  }
  const auto parts = std::get<InlineDecimal>(cell).parts();
  const std::uint64_t shape = (std::uint64_t{parts.scale} << 1) | std::uint64_t{parts.negative};
  return combine(hash_bytes(parts.digits), shape) ^ tag;
}

// ---------------------------------------------------------------- collector
const char* gc_mode_name(GcMode mode) noexcept {
  switch (mode) {
    case GcMode::blocking: return "blocking";
    case GcMode::background: return "background";
    case GcMode::manual: return "manual";
  }
  return "unknown";
}
void Budget::reclaim() { reclaimer_->reclaim(); }
void Collector::reclaim() {
  if (options_.mode == GcMode::background) drain();
  else collect();
}
GcStatistics process_gc_statistics() {
  auto& r = registry();
  std::lock_guard lock(r.mutex);
  auto total = r.destroyed;
  for (const auto* collector = r.live; collector; collector = collector->registry_next_)
    accumulate(total, collector->statistics());
  return total;
}
void Collector::enroll() noexcept {
  auto& r = registry();
  std::lock_guard lock(r.mutex);
  registry_next_ = r.live;
  if (r.live) r.live->registry_previous_ = this;
  r.live = this;
}
void Collector::withdraw() noexcept {
  auto& r = registry();
  std::lock_guard lock(r.mutex);
  (registry_previous_ ? registry_previous_->registry_next_ : r.live) = registry_next_;
  if (registry_next_) registry_next_->registry_previous_ = registry_previous_;
  auto mine = statistics();
  mine.pending_bytes = 0;  // freed by the owner's teardown, not collected
  accumulate(r.destroyed, mine);
}
Collector::Collector(GcOptions options) : options_(options) {
  // A few reader pin slots up front: opening a cursor then allocates nothing.
  for (int i = 0; i < 4; ++i) pins_.push_back(std::make_unique<std::atomic<std::uint64_t>>(0));
  enroll();
  if (options_.mode == GcMode::background) {
    try {
      thread_ = std::thread([this] { background(); });
    } catch (...) {
      withdraw();
      throw;
    }
  }
}
Collector::~Collector() {
  if (thread_.joinable()) {
    { std::lock_guard lock(mutex_); stop_ = true; }
    wake_.notify_all();
    thread_.join();
  }
  withdraw();
  // The owner is being destroyed: nothing can observe retired objects.
  for (auto& batch : handoff_) free_batch(batch);
  for (auto& item : sealed_) item.release(item.object);
  for (auto& item : open_) item.release(item.object);
}
Collector::Pin& Collector::Pin::operator=(Pin&& other) noexcept {
  if (this != &other) { reset(); owner_ = other.owner_; slot_ = other.slot_; other.owner_ = nullptr; }
  return *this;
}
void Collector::Pin::reset() noexcept {
  if (!owner_) return;
  owner_->pins_[slot_]->store(0, std::memory_order_release);
  if (owner_->options_.mode == GcMode::background) owner_->wake_.notify_all();
  owner_ = nullptr;
}
Collector::Pin Collector::pin() {
  std::lock_guard lock(mutex_);
  for (std::size_t i = 0; i < pins_.size(); ++i) {
    if (pins_[i]->load(std::memory_order_acquire) == 0) {
      pins_[i]->store(epoch_, std::memory_order_release);
      return Pin(this, i);
    }
  }
  pins_.push_back(std::make_unique<std::atomic<std::uint64_t>>(epoch_));
  return Pin(this, pins_.size() - 1);
}
std::uint64_t Collector::oldest_pinned() const noexcept {
  std::uint64_t oldest = std::numeric_limits<std::uint64_t>::max();
  for (const auto& pin : pins_) {
    const auto epoch = pin->load(std::memory_order_acquire);
    if (epoch) oldest = std::min(oldest, epoch);
  }
  return oldest;
}
void Collector::retire(void* object, void (*release)(void*), std::size_t bytes) {
  open_.push_back({object, release, bytes});
  if (reserved_) --reserved_;
  open_bytes_ += bytes;
  add(retired_objects_, std::uint64_t{1});
  add(retired_bytes_, bytes);
}
void Collector::reserve(std::size_t count) {
  // Reservations accumulate over the open epoch; retire() consumes them.
  const auto wanted = open_.size() + reserved_ + count;
  if (open_.capacity() < wanted) open_.reserve(std::max(wanted, open_.capacity() * 2));
  if (options_.mode != GcMode::background) {
    const auto sealed = sealed_.size() + wanted;
    if (sealed_.capacity() < sealed) sealed_.reserve(std::max(sealed, sealed_.capacity() * 2));
    if (marks_.capacity() < marks_.size() + 1) marks_.reserve(std::max<std::size_t>(16, marks_.capacity() * 2));
  }
  reserved_ += count;
}
void Collector::forget_after(std::size_t mark) noexcept {
  while (open_.size() > mark) {
    open_bytes_ -= open_.back().bytes;
    subtract(retired_objects_, std::uint64_t{1});
    subtract(retired_bytes_, open_.back().bytes);
    open_.pop_back();
  }
}
void Collector::free_batch(Batch& batch) noexcept {
  for (auto& item : batch.items) item.release(item.object);
  add(freed_objects_, std::uint64_t{batch.items.size()});
  add(freed_bytes_, batch.bytes);
  batch.items.clear();
}
void Collector::seal() {
  // Never throws: if a batch cannot be handed over, its objects stay open and
  // are sealed with a later epoch (a later stamp only delays their release).
  reserved_ = 0;
  if (!open_.empty()) {
    if (options_.mode == GcMode::background) {
      Batch batch{epoch_, std::move(open_), open_bytes_};
      open_ = {};
      try {
        { std::lock_guard lock(mutex_); handoff_.push_back(std::move(batch)); }
        wake_.notify_one();
        open_bytes_ = 0;
      } catch (...) {
        open_ = std::move(batch.items);
      }
    } else {
      // reserve() normally made room; otherwise try to grow, and on failure
      // keep the objects open (sealed with a later epoch).
      try {
        if (sealed_.capacity() - sealed_.size() < open_.size())
          sealed_.reserve(std::max(sealed_.size() + open_.size(), sealed_.capacity() * 2));
        if (marks_.size() == marks_.capacity()) marks_.reserve(std::max<std::size_t>(16, marks_.capacity() * 2));
      } catch (...) {}
    }
    if (options_.mode != GcMode::background && !open_.empty() &&
        sealed_.capacity() - sealed_.size() >= open_.size() && marks_.size() < marks_.capacity()) {
      sealed_.insert(sealed_.end(), open_.begin(), open_.end());  // within capacity: no allocation
      marks_.push_back({epoch_, sealed_.size()});
      sealed_bytes_ += open_bytes_;
      open_bytes_ = 0;
      open_.clear();
      ++epochs_since_collect_;
    }
  }
  ++epoch_;
  if (options_.mode == GcMode::blocking && !marks_.empty() &&
      ((options_.epoch_interval && epochs_since_collect_ >= options_.epoch_interval) ||
       sealed_bytes_ >= options_.retired_bytes))
    collect();
}
void Collector::collect() {
  if (options_.mode == GcMode::background) { wake_.notify_all(); return; }
  std::uint64_t oldest;
  { std::lock_guard lock(mutex_); oldest = oldest_pinned(); }
  epochs_since_collect_ = 0;
  std::size_t marks = 0;
  while (marks < marks_.size() && marks_[marks].epoch < oldest) ++marks;
  if (!marks) return;
  const auto cut = marks_[marks - 1].end;
  std::size_t bytes = 0;
  for (std::size_t i = 0; i < cut; ++i) { sealed_[i].release(sealed_[i].object); bytes += sealed_[i].bytes; }
  sealed_.erase(sealed_.begin(), sealed_.begin() + static_cast<std::ptrdiff_t>(cut));
  marks_.erase(marks_.begin(), marks_.begin() + static_cast<std::ptrdiff_t>(marks));
  for (auto& mark : marks_) mark.end -= cut;
  sealed_bytes_ -= bytes;
  add(freed_objects_, std::uint64_t{cut});
  add(freed_bytes_, bytes);
  add(collections_, std::uint64_t{1});
}
void Collector::drain() {
  if (options_.mode != GcMode::background) { collect(); return; }
  std::unique_lock lock(mutex_);
  wake_.notify_all();
  idle_.wait(lock, [&] {
    return !busy_ && (handoff_.empty() || handoff_.front().epoch >= oldest_pinned());
  });
}
void Collector::background() {
  std::unique_lock lock(mutex_);
  for (;;) {
    wake_.wait_for(lock, std::chrono::milliseconds(5), [&] { return stop_ || !handoff_.empty(); });
    if (stop_) break;
    const auto oldest = oldest_pinned();
    std::vector<Batch> work;
    while (!handoff_.empty() && handoff_.front().epoch < oldest) {
      work.push_back(std::move(handoff_.front()));
      handoff_.pop_front();
    }
    if (work.empty()) { idle_.notify_all(); continue; }
    busy_ = true;
    lock.unlock();
    for (auto& batch : work) free_batch(batch);
    add(collections_, std::uint64_t{1});
    lock.lock();
    busy_ = false;
    idle_.notify_all();
  }
}
GcStatistics Collector::statistics() const {
  GcStatistics out;
  out.collections = collections_.load();
  out.retired_objects = retired_objects_.load();
  out.freed_objects = freed_objects_.load();
  out.retired_bytes = retired_bytes_.load();
  out.freed_bytes = freed_bytes_.load();
  out.pending_bytes = out.retired_bytes - out.freed_bytes;
  return out;
}

// ------------------------------------------------------------------ domains
KeyDomain::KeyDomain(std::vector<ScalarType> types, Collector* collector, Budget* budget)
    : types_(std::move(types)), collector_(collector), budget_(budget) {
  // One or two int64/Boolean fields fit the key itself: no record.
  const auto word_type = [](ScalarType type) { return type == ScalarType::int64 || type == ScalarType::boolean; };
  inline_ = (types_.size() == 1 || types_.size() == 2) && std::all_of(types_.begin(), types_.end(), word_type);
  pair_ = inline_ && types_.size() == 2;
  for (std::uint32_t i = 0; i < types_.size(); ++i) identity_.push_back(i);
  if (!inline_) {
    if (budget_) budget_->charge(16 * sizeof(Slot));
    slots_.assign(16, Slot{0, nullptr});
    mask_ = 15;
  }
}
KeyDomain::~KeyDomain() {
  for (const auto& slot : slots_) if (slot.record) free_record(slot.record);
  if (budget_) budget_->release(slots_.size() * sizeof(Slot));
}
Key KeyDomain::inline_key(const ScalarView* cells, const std::uint32_t* positions) const noexcept {
  const auto encode = [&](std::size_t f) -> std::uint64_t {
    const auto& cell = cells[positions[f]];
    return types_[f] == ScalarType::int64 ? static_cast<std::uint64_t>(std::get<std::int64_t>(cell))
                                          : (std::get<bool>(cell) ? 1U : 0U);
  };
  if (pair_) return {encode(0), encode(1)};
  const auto word = encode(0);
  return {mix(word ^ 0x2545f4914f6cdd1dULL), word};
}
std::uint64_t KeyDomain::hash_of(const ScalarView* cells, const std::uint32_t* positions) const noexcept {
  std::uint64_t h = 0x8bb84b93962eacc9ULL ^ types_.size();
  for (std::size_t i = 0; i < types_.size(); ++i) h = combine(h, hash_cell(cells[positions[i]]));
  return mix(h);
}
std::size_t KeyDomain::probe(std::uint64_t hash, const ScalarView* cells, const std::uint32_t* positions) const noexcept {
  for (std::size_t i = hash & mask_;; i = (i + 1) & mask_) {
    const auto& slot = slots_[i];
    if (!slot.record) return i;
    if (slot.hash != hash) continue;
    const auto* stored = slot.record->cells();
    bool same = true;
    for (std::size_t f = 0; f < types_.size(); ++f) {
      const auto& probe = cells[positions[f]];
      const auto* a = std::get_if<std::int64_t>(&stored[f]);
      const auto* b = std::get_if<std::int64_t>(&probe);
      if (a && b ? *a != *b : !(stored[f] == probe)) { same = false; break; }
    }
    if (same) return i;
  }
}
std::optional<Key> KeyDomain::find(const ScalarView* cells, const std::uint32_t* positions) const {
  if (inline_) return inline_key(cells, positions);
  const auto hash = hash_of(cells, positions);
  const auto& slot = slots_[probe(hash, cells, positions)];
  if (!slot.record) return std::nullopt;
  return Key{hash, reinterpret_cast<std::uint64_t>(slot.record)};
}
std::optional<Key> KeyDomain::find(std::span<const ScalarView> cells) const {
  require(cells.size() == types_.size(), "key arity differs from its domain");
  return find(cells.data(), identity_.data());
}
void KeyDomain::grow() {
  const auto extra = slots_.size() * sizeof(Slot);  // the new array doubles the old
  if (budget_) budget_->charge(extra);
  std::vector<Slot> old;
  try { old.assign(slots_.size() * 2, Slot{0, nullptr}); }
  catch (...) { if (budget_) budget_->release(extra); throw; }
  old.swap(slots_);
  mask_ = slots_.size() - 1;
  for (const auto& slot : old) {
    if (!slot.record) continue;
    std::size_t i = slot.hash & mask_;
    while (slots_[i].record) i = (i + 1) & mask_;
    slots_[i] = slot;
  }
}
void KeyDomain::insert_slot(KeyRecord* record) {
  if ((size_ + 1) * 2 > slots_.size()) grow();
  std::size_t i = record->hash & mask_;
  while (slots_[i].record) i = (i + 1) & mask_;
  slots_[i] = {record->hash, record};
  ++size_;
}
void KeyDomain::erase_slot(std::size_t i) noexcept {
  for (std::size_t j = (i + 1) & mask_;; j = (j + 1) & mask_) {
    const auto slot = slots_[j];
    if (!slot.record) break;
    const std::size_t home = slot.hash & mask_;
    const bool stays = i <= j ? (i < home && home <= j) : (i < home || home <= j);
    if (!stays) { slots_[i] = slot; i = j; }
  }
  slots_[i] = {0, nullptr};
  --size_;
}
Key KeyDomain::acquire(const ScalarView* cells, const std::uint32_t* positions) {
  if (inline_) return inline_key(cells, positions);
  const auto hash = hash_of(cells, positions);
  const auto index = probe(hash, cells, positions);
  if (auto* record = slots_[index].record) {
    require(record->references < std::numeric_limits<std::uint32_t>::max(), "key reference overflow");
    ++record->references;
    return {hash, reinterpret_cast<std::uint64_t>(record)};
  }
  std::size_t text = 0;
  for (std::size_t f = 0; f < types_.size(); ++f)
    if (const auto* string = std::get_if<std::string_view>(&cells[positions[f]])) text += string->size();
  const std::size_t bytes = sizeof(KeyRecord) + types_.size() * sizeof(ScalarView) + text;
  if ((size_ + 1) * 2 > slots_.size()) grow();  // Before allocating: a failure leaves nothing behind.
  if (budget_) budget_->charge(bytes);
  KeyRecord* record;
  try { record = static_cast<KeyRecord*>(::operator new(bytes)); }
  catch (...) { if (budget_) budget_->release(bytes); throw; }
  record->budget = budget_;
  record->hash = hash;
  record->references = 1;
  record->arity = static_cast<std::uint32_t>(types_.size());
  record->bytes = bytes;
  auto* payload = reinterpret_cast<char*>(record->cells() + types_.size());
  for (std::size_t f = 0; f < types_.size(); ++f) {
    const auto& cell = cells[positions[f]];
    if (const auto* string = std::get_if<std::string_view>(&cell)) {
      std::memcpy(payload, string->data(), string->size());
      new (record->cells() + f) ScalarView(std::string_view(payload, string->size()));
      payload += string->size();
    } else {
      new (record->cells() + f) ScalarView(cell);
    }
  }
  insert_slot(record);
  return {hash, reinterpret_cast<std::uint64_t>(record)};
}
Key KeyDomain::acquire(std::span<const ScalarView> cells) {
  require(cells.size() == types_.size(), "key arity differs from its domain");
  return acquire(cells.data(), identity_.data());
}
void KeyDomain::retain(Key key) noexcept {
  if (!inline_) ++reinterpret_cast<KeyRecord*>(key.word)->references;
}
void KeyDomain::release(Key key) {
  if (inline_) return;
  auto* record = reinterpret_cast<KeyRecord*>(key.word);
  require(record->references > 0, "key reference underflow");
  if (--record->references > 0) return;
  std::size_t i = record->hash & mask_;
  while (slots_[i].record != record) i = (i + 1) & mask_;
  erase_slot(i);
  if (collector_) collector_->retire(record, &free_record, record->bytes);
  else free_record(record);
}
void KeyDomain::restore(Key key) {
  if (inline_) return;
  auto* record = reinterpret_cast<KeyRecord*>(key.word);
  record->references = 1;
  insert_slot(record);
}
RowView KeyDomain::view(Key key, ScalarView* scratch) const noexcept {
  if (inline_) {
    for (std::size_t f = 0; f < types_.size(); ++f) static_cast<void>(cell(key, f, scratch[f]));
    return RowView::borrow({scratch, types_.size()});
  }
  const auto* record = reinterpret_cast<const KeyRecord*>(key.word);
  return RowView::borrow({record->cells(), record->arity});
}
void KeyDomain::for_each(const std::function<void(Key, std::uint32_t)>& visit) const {
  for (const auto& slot : slots_)
    if (slot.record) visit(Key{slot.hash, reinterpret_cast<std::uint64_t>(slot.record)}, slot.record->references);
}
void KeyDomain::check_invariants() const {
  if (inline_) return;
  std::size_t count = 0;
  for (const auto& slot : slots_) {
    if (!slot.record) continue;
    ++count;
    require(slot.record->references > 0, "interned key without references");
    require(slot.hash == slot.record->hash && slot.hash == hash_of(slot.record->cells(), identity_.data()), "interned key hash differs");
    require(slot.record->arity == types_.size(), "interned key arity differs");
    for (std::size_t f = 0; f < types_.size(); ++f)
      require(type_of(slot.record->cells()[f]) == types_[f], "interned key type differs");
  }
  require(count == size_, "interned key count differs");
}

// --------------------------------------------------------------------- maps
KeyMap::KeyMap(std::uint32_t payload_words, std::uint32_t secondary_indexes, Budget* budget)
    : payload_(payload_words), secondary_(secondary_indexes), stride_(2 + payload_words + 3 * secondary_indexes),
      primary_(16, 0), mask_(15), indexes_(secondary_indexes), budget_(budget) {
  for (auto& index : indexes_) { index.slots.assign(16, 0); index.mask = 15; }
  charged_ = memory_bytes();
  if (budget_) {
    try { budget_->charge(charged_); } catch (...) { charged_ = 0; throw; }
  }
}
KeyMap::~KeyMap() { if (budget_) budget_->release(charged_); }
KeyMap::KeyMap(KeyMap&& other) noexcept
    : payload_(other.payload_), secondary_(other.secondary_), stride_(other.stride_), slab_(std::move(other.slab_)),
      state_(std::move(other.state_)), free_(std::move(other.free_)), primary_(std::move(other.primary_)),
      mask_(other.mask_), size_(other.size_), indexes_(std::move(other.indexes_)), budget_(other.budget_), charged_(other.charged_) {
  other.charged_ = 0; other.size_ = 0;
}
KeyMap& KeyMap::operator=(KeyMap&& other) noexcept {
  if (this == &other) return *this;
  if (budget_) budget_->release(charged_);
  payload_ = other.payload_; secondary_ = other.secondary_; stride_ = other.stride_;
  slab_ = std::move(other.slab_); state_ = std::move(other.state_); free_ = std::move(other.free_);
  primary_ = std::move(other.primary_); mask_ = other.mask_; size_ = other.size_; indexes_ = std::move(other.indexes_);
  budget_ = other.budget_; charged_ = other.charged_;
  other.charged_ = 0; other.size_ = 0;
  return *this;
}
void KeyMap::recharge() noexcept {
  const auto actual = memory_bytes();
  if (budget_ && actual < charged_) budget_->release(charged_ - actual);
  if (actual < charged_) charged_ = actual;
}
void KeyMap::reserve_entry() {
  if (!free_.empty() || state_.size() < state_.capacity()) return;
  grow_entries(std::max<std::size_t>(16, state_.capacity() * 2));
}
void KeyMap::grow_entries(std::size_t entries) {
  const auto before = memory_bytes();
  const std::size_t estimate = (entries * stride_ - std::min(entries * stride_, slab_.capacity())) * 8 + entries * 5;
  if (budget_) budget_->charge(estimate);
  try {
    slab_.reserve(entries * stride_);
    state_.reserve(entries);
    free_.reserve(entries);  // free_detached() then never allocates
  } catch (...) { if (budget_) budget_->release(estimate); throw; }
  const auto grown = memory_bytes() - before;
  if (budget_) { if (grown < estimate) budget_->release(estimate - grown); else if (grown > estimate) budget_->charge(grown - estimate); }
  charged_ += grown;
}
void KeyMap::reserve_slots(std::vector<std::uint64_t>& slots, std::size_t& mask, std::size_t used) {
  if ((used + 1) * 2 <= slots.size()) return;
  grow_slots(slots, mask);
}
void KeyMap::grow_slots(std::vector<std::uint64_t>& slots, std::size_t& mask) {
  const auto previous = slots.size() * 8;
  const auto capacity = std::max<std::size_t>(16, slots.size() * 2);
  const auto extra = capacity * 8;  // both arrays exist during the rehash
  if (budget_) budget_->charge(extra);
  try { rehash_tagged(slots, mask, capacity); }
  catch (...) { if (budget_) budget_->release(extra); throw; }
  if (budget_) budget_->release(previous);  // the old array is gone
  charged_ += extra - previous;
}
void KeyMap::reserve(std::size_t extra) {
  if (!extra) return;
  while ((size_ + extra) * 2 > primary_.size()) grow_slots(primary_, mask_);
  for (auto& index : indexes_)
    while ((index.used + extra) * 2 > index.slots.size()) grow_slots(index.slots, index.mask);
  if (free_.size() + (state_.capacity() - state_.size()) < extra)
    grow_entries(std::max({std::size_t{16}, state_.capacity() * 2, state_.size() + extra}));
}
std::uint32_t KeyMap::find(Key key) const noexcept {
  const auto tag = tag_of(probe_hash(key));
  for (std::size_t i = tag & mask_;; i = (i + 1) & mask_) {
    const auto slot = primary_[i];
    if (!slot) return no_entry;
    if (slot_tag(slot) == tag) {
      const auto* e = entry(slot_id(slot));
      if (e[0] == key.hash && e[1] == key.word) return slot_id(slot);
    }
  }
}
void KeyMap::place(std::uint32_t id) {
  const auto tag = tag_of(probe_hash(entry(id)[0], entry(id)[1]));
  std::size_t i = tag & mask_;
  while (primary_[i]) i = (i + 1) & mask_;
  primary_[i] = slot_of(tag, id);
}
void KeyMap::unplace(std::uint32_t id) noexcept {
  const auto tag = tag_of(probe_hash(entry(id)[0], entry(id)[1]));
  std::size_t i = tag & mask_;
  while (primary_[i] != slot_of(tag, id)) i = (i + 1) & mask_;
  erase_tagged(primary_, mask_, i);
}
std::uint32_t KeyMap::insert(Key key, const Key* secondary) {
  // Reserve every structure first: after this point nothing allocates.
  reserve_slots(primary_, mask_, size_);
  for (auto& index : indexes_) reserve_slots(index.slots, index.mask, index.used);
  reserve_entry();
  std::uint32_t id;
  if (!free_.empty()) {
    id = free_.back();
    free_.pop_back();
  } else {
    if (state_.size() >= no_entry - 1) fail("key map ids exhausted");
    slab_.resize(slab_.size() + stride_);
    state_.push_back(0);
    id = static_cast<std::uint32_t>(state_.size() - 1);
  }
  auto* e = entry(id);
  e[0] = key.hash;
  e[1] = key.word;
  std::fill(e + 2, e + stride_, 0);
  for (std::uint32_t s = 0; s < secondary_; ++s) {
    e[2 + payload_ + 3 * s] = secondary[s].hash;
    e[2 + payload_ + 3 * s + 1] = secondary[s].word;
  }
  state_[id] = 1;
  place(id);
  for (std::uint32_t s = 0; s < secondary_; ++s) link(s, id);
  ++size_;
  return id;
}
void KeyMap::link(std::size_t s, std::uint32_t id) {
  auto& index = indexes_[s];
  auto* e = entry(id);
  const std::size_t base = 2 + payload_ + 3 * s;
  const auto tag = tag_of(probe_hash(e[base], e[base + 1]));
  for (std::size_t i = tag & index.mask;; i = (i + 1) & index.mask) {
    const auto slot = index.slots[i];
    if (!slot) {
      index.slots[i] = slot_of(tag, id);
      ++index.used;
      e[base + 2] = (static_cast<std::uint64_t>(no_entry) << 32) | no_entry;
      return;
    }
    if (slot_tag(slot) != tag) continue;
    const auto head = slot_id(slot);
    auto* h = entry(head);
    if (h[base] != e[base] || h[base + 1] != e[base + 1]) continue;
    e[base + 2] = (static_cast<std::uint64_t>(no_entry) << 32) | head;
    h[base + 2] = (static_cast<std::uint64_t>(id) << 32) | static_cast<std::uint32_t>(h[base + 2]);
    index.slots[i] = slot_of(tag, id);
    return;
  }
}
void KeyMap::unlink(std::size_t s, std::uint32_t id) noexcept {
  auto& index = indexes_[s];
  auto* e = entry(id);
  const std::size_t base = 2 + payload_ + 3 * s;
  const auto next_id = static_cast<std::uint32_t>(e[base + 2]);
  const auto prev_id = static_cast<std::uint32_t>(e[base + 2] >> 32);
  if (prev_id != no_entry) {
    auto* p = entry(prev_id);
    p[base + 2] = (p[base + 2] & 0xffffffff00000000ULL) | next_id;
    if (next_id != no_entry) {
      auto* n = entry(next_id);
      n[base + 2] = (static_cast<std::uint64_t>(prev_id) << 32) | static_cast<std::uint32_t>(n[base + 2]);
    }
    return;
  }
  const auto tag = tag_of(probe_hash(e[base], e[base + 1]));
  std::size_t i = tag & index.mask;
  while (index.slots[i] != slot_of(tag, id)) i = (i + 1) & index.mask;
  if (next_id != no_entry) {
    index.slots[i] = slot_of(tag, next_id);
    auto* n = entry(next_id);
    n[base + 2] = (static_cast<std::uint64_t>(no_entry) << 32) | static_cast<std::uint32_t>(n[base + 2]);
  } else {
    erase_tagged(index.slots, index.mask, i);
    --index.used;
  }
}
void KeyMap::detach(std::uint32_t id) noexcept {
  for (std::uint32_t s = 0; s < secondary_; ++s) unlink(s, id);
  unplace(id);
  state_[id] = 2;
  --size_;
}
void KeyMap::relink(std::uint32_t id) {
  require(state_[id] == 2, "relink of an entry that is not detached");
  reserve_slots(primary_, mask_, size_);
  for (auto& index : indexes_) reserve_slots(index.slots, index.mask, index.used);
  state_[id] = 1;
  place(id);
  for (std::uint32_t s = 0; s < secondary_; ++s) link(s, id);
  ++size_;
}
void KeyMap::free_detached(std::uint32_t id) noexcept {
  state_[id] = 0;
  free_.push_back(id);
}
void KeyMap::erase(std::uint32_t id) noexcept {
  detach(id);
  free_detached(id);
}
std::uint32_t KeyMap::bucket(std::size_t s, Key key) const noexcept {
  const auto& index = indexes_[s];
  const std::size_t base = 2 + payload_ + 3 * s;
  const auto tag = tag_of(probe_hash(key));
  for (std::size_t i = tag & index.mask;; i = (i + 1) & index.mask) {
    const auto slot = index.slots[i];
    if (!slot) return no_entry;
    if (slot_tag(slot) != tag) continue;
    const auto* h = entry(slot_id(slot));
    if (h[base] == key.hash && h[base + 1] == key.word) return slot_id(slot);
  }
}
void KeyMap::shrink() {
  const auto target = capacity_for(size_);
  if (target * 4 <= primary_.size()) rehash_tagged(primary_, mask_, target);
  for (auto& index : indexes_) {
    const auto wanted = capacity_for(index.used);
    if (wanted * 4 <= index.slots.size()) rehash_tagged(index.slots, index.mask, wanted);
  }
  // Trailing free ids can be returned; interior ids stay stable.
  while (!state_.empty() && state_.back() == 0) {
    const auto id = static_cast<std::uint32_t>(state_.size() - 1);
    const auto found = std::find(free_.begin(), free_.end(), id);
    if (found == free_.end()) break;
    free_.erase(found);
    state_.pop_back();
    slab_.resize(slab_.size() - stride_);
  }
  slab_.shrink_to_fit();
  recharge();
}
std::size_t KeyMap::memory_bytes() const noexcept {
  std::size_t bytes = slab_.capacity() * 8 + state_.capacity() + free_.capacity() * 4 + primary_.capacity() * 8;
  for (const auto& index : indexes_) bytes += index.slots.capacity() * 8;
  return bytes;
}
void KeyMap::check_invariants() const {
  std::size_t live_count = 0;
  for (std::uint32_t id = 0; id < state_.size(); ++id) {
    if (state_[id] != 1) continue;
    ++live_count;
    require(find(key(id)) == id, "map entry is not reachable by its key");
    for (std::uint32_t s = 0; s < secondary_; ++s) {
      bool found = false;
      for (auto other = bucket(s, secondary(id, s)); other != no_entry; other = next(s, other)) {
        require(secondary(other, s) == secondary(id, s), "bucket member has another key");
        if (other == id) found = true;
      }
      require(found, "map entry missing from its bucket");
    }
  }
  require(live_count == size_, "map size differs from live entries");
}

}  // namespace crown::storage::keyed
