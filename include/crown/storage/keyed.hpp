#pragma once
// Keyed storage core (docs/keyed_core.md).
//
// Relations keep typed tuples of their own width. Every join, support, visible
// and live index is keyed by one unified fixed-width Key derived from source
// values: a 64-bit hash plus either the value itself (a single int64, Boolean
// or date field) or a pointer to the canonical interned record of the key's
// values in its KeyDomain (any other arity or type). Equality of two keys of
// one domain is equality of both words. Interned records are reference counted;
// a record whose count drops to zero leaves its dictionary at once and is
// retired to the Collector, which frees it only after every epoch that could
// still observe it has finished (blocking phase, background thread or manual).
#include "crown/storage/accounted_row.hpp"
#include "crown/resource/memory.hpp"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <span>
#include <thread>
#include <vector>

namespace crown::storage::keyed {

inline constexpr std::uint32_t no_entry = 0xffffffffU;

// The unified fixed-width key. Inline keys carry their values: one int64 or
// Boolean field is {hash of the value, value}; two such fields are {first,
// second}. Every other key is {hash, address of its interned record}. Maps
// therefore hash both words (probe_hash), never `hash` alone.
struct Key {
  std::uint64_t hash = 0;
  std::uint64_t word = 0;
  friend bool operator==(Key, Key) = default;
};

// ------------------------------------------------------------------ hashing
[[nodiscard]] std::uint64_t hash_cell(const ScalarView& cell) noexcept;
[[nodiscard]] inline std::uint64_t mix(std::uint64_t h) noexcept {
  h ^= h >> 33; h *= 0xff51afd7ed558ccdULL; h ^= h >> 33; h *= 0xc4ceb9fe1a85ec53ULL;
  return h ^ (h >> 33);
}
[[nodiscard]] inline std::uint64_t combine(std::uint64_t seed, std::uint64_t value) noexcept {
  return (seed ^ value) * 0x9e3779b97f4a7c15ULL + 0x632be59bd9b4e019ULL;
}

// ------------------------------------------------------------------- budget
// Coarse memory gauge for one owner: maps charge their capacity and interned
// records their bytes before allocating, and release them when freed (the
// collector thread may release concurrently). Exceeding the limit throws
// resource::MemoryFailure(limit) before any state changes.
class Collector;
class Budget {
 public:
  explicit Budget(std::size_t limit = static_cast<std::size_t>(-1)) noexcept : limit_(limit) {}
  // Retired-but-unfreed records stay charged; with a reclaimer, a charge that
  // would exceed the limit first lets the owner's collector free them.
  void set_reclaimer(Collector* collector) noexcept { reclaimer_ = collector; }
  void charge(std::size_t bytes) {
    auto used = used_.load(std::memory_order_relaxed);
    if ((bytes > limit_ || used > limit_ - bytes) && reclaimer_) { reclaim(); used = used_.load(std::memory_order_relaxed); }
    if (bytes > limit_ || used > limit_ - bytes) throw resource::MemoryFailure(resource::MemoryFault::limit);
    used_.fetch_add(bytes, std::memory_order_relaxed);
    const auto now = used + bytes;
    if (now > peak_.load(std::memory_order_relaxed)) peak_.store(now, std::memory_order_relaxed);
  }
  void release(std::size_t bytes) noexcept { used_.fetch_sub(bytes, std::memory_order_relaxed); }
  [[nodiscard]] std::size_t used() const noexcept { return used_.load(std::memory_order_relaxed); }
  [[nodiscard]] std::size_t peak() const noexcept { return peak_.load(std::memory_order_relaxed); }
  [[nodiscard]] std::size_t limit() const noexcept { return limit_; }
 private:
  void reclaim();
  std::size_t limit_;
  std::atomic<std::size_t> used_{0}, peak_{0};
  Collector* reclaimer_ = nullptr;
};

// ---------------------------------------------------------------- collector
// blocking: single-threaded; the writer collects when the retired-memory pool
//   (retired_bytes) is full, or when the engine budget would be exceeded.
// background: one dedicated collector thread besides the writer.
// manual: only explicit collect()/drain().
enum class GcMode { blocking, background, manual };
struct GcOptions {
  GcMode mode = GcMode::blocking;
  // Blocking mode: optionally also collect every this many sealed epochs that
  // retired garbage (0: only when the pool is full).
  std::uint64_t epoch_interval = 0;
  // Blocking mode: capacity of the retired-memory pool.
  std::size_t retired_bytes = std::size_t{64} << 20;
};
[[nodiscard]] const char* gc_mode_name(GcMode mode) noexcept;
struct GcStatistics {
  std::uint64_t collections = 0, retired_objects = 0, freed_objects = 0;
  std::size_t retired_bytes = 0, freed_bytes = 0, pending_bytes = 0;
};
// Totals over every collector of this process, live and destroyed (a
// destroyed collector's teardown frees are not collections). For reports.
[[nodiscard]] GcStatistics process_gc_statistics();

// Epoch-based reclamation for one single-writer owner. The writer retires
// objects during an epoch, seals the epoch at commit, and readers pin the
// epoch they observe. A sealed batch is freed once its epoch is older than
// every pinned epoch. Background mode frees batches on a dedicated thread.
class Collector {
 public:
  explicit Collector(GcOptions options = {});
  ~Collector();
  Collector(const Collector&) = delete;
  Collector& operator=(const Collector&) = delete;

  [[nodiscard]] const GcOptions& options() const noexcept { return options_; }
  [[nodiscard]] std::uint64_t epoch() const noexcept { return epoch_; }
  // Writer: retire one heap object of `bytes` freed by `release(object)`.
  void retire(void* object, void (*release)(void*), std::size_t bytes);
  // Writer: make room for `count` more retirements in the open epoch, so a
  // later retire() (inside rollback or commit) cannot allocate.
  void reserve(std::size_t count);
  // Writer: undo the most recent retirements of the open epoch, newest first,
  // without freeing (rollback resurrects them).
  [[nodiscard]] std::size_t open_retirements() const noexcept { return open_.size(); }
  void forget_after(std::size_t mark) noexcept;
  // Writer: end the current epoch; collects in blocking mode when due.
  void seal();
  // Readers: pin the current epoch while observing state (cursors, views).
  class Pin {
   public:
    Pin() noexcept = default;
    Pin(Pin&& other) noexcept : owner_(other.owner_), slot_(other.slot_) { other.owner_ = nullptr; }
    Pin& operator=(Pin&& other) noexcept;
    Pin(const Pin&) = delete;
    Pin& operator=(const Pin&) = delete;
    ~Pin() { reset(); }
    void reset() noexcept;
   private:
    friend class Collector;
    Pin(Collector* owner, std::size_t slot) noexcept : owner_(owner), slot_(slot) {}
    Collector* owner_ = nullptr;
    std::size_t slot_ = 0;
  };
  [[nodiscard]] Pin pin();
  // Free every sealed batch no pinned reader can observe (any mode).
  void collect();
  // Block until the background thread has drained every eligible batch.
  void drain();
  // Free what can be freed now: collect() (blocking/manual) or drain() (background).
  void reclaim();
  // Safe from any thread.
  [[nodiscard]] GcStatistics statistics() const;

 private:
  struct Garbage { void* object; void (*release)(void*); std::size_t bytes; };
  struct Batch { std::uint64_t epoch; std::vector<Garbage> items; std::size_t bytes = 0; };
  [[nodiscard]] std::uint64_t oldest_pinned() const noexcept;
  void free_batch(Batch& batch) noexcept;
  void background();

  GcOptions options_;
  std::uint64_t epoch_ = 1;
  std::vector<Garbage> open_;
  std::size_t open_bytes_ = 0, reserved_ = 0;
  // Blocking/manual modes: every sealed retirement in one flat list, with the
  // end position of each sealed epoch (no allocation per epoch in steady
  // state; reserve() makes room so seal() never allocates).
  struct Mark { std::uint64_t epoch; std::size_t end; };
  std::vector<Garbage> sealed_;
  std::vector<Mark> marks_;
  std::size_t sealed_bytes_ = 0;
  std::uint64_t epochs_since_collect_ = 0;
  // Reader pins: epoch per slot (0 = free).
  std::vector<std::unique_ptr<std::atomic<std::uint64_t>>> pins_;
  // Background mode.
  mutable std::mutex mutex_;
  std::condition_variable wake_, idle_;
  std::deque<Batch> handoff_;
  bool stop_ = false, busy_ = false;
  std::thread thread_;
  // Process registry (process_gc_statistics): an intrusive list, so creating
  // a collector allocates nothing for it.
  Collector* registry_previous_ = nullptr;
  Collector* registry_next_ = nullptr;
  void enroll() noexcept;
  void withdraw() noexcept;
  friend GcStatistics process_gc_statistics();
  // Statistics (writer and collector thread).
  std::atomic<std::uint64_t> collections_{0}, retired_objects_{0}, freed_objects_{0};
  std::atomic<std::size_t> retired_bytes_{0}, freed_bytes_{0};
};

// ------------------------------------------------------------------ domains
// Interned record: header, then `arity` ScalarView cells whose strings point
// into the record's trailing byte payload.
struct KeyRecord {
  std::uint64_t hash;
  std::uint32_t references;
  std::uint32_t arity;
  std::size_t bytes;
  Budget* budget;
  [[nodiscard]] ScalarView* cells() noexcept { return reinterpret_cast<ScalarView*>(this + 1); }
  [[nodiscard]] const ScalarView* cells() const noexcept { return reinterpret_cast<const ScalarView*>(this + 1); }
};

// Probe hash of a key's two words (map placement and bucket tags).
[[nodiscard]] inline std::uint64_t probe_hash(std::uint64_t hash, std::uint64_t word) noexcept {
  return mix(hash ^ (word * 0x9e3779b97f4a7c15ULL));
}
[[nodiscard]] inline std::uint64_t probe_hash(Key key) noexcept { return probe_hash(key.hash, key.word); }

class KeyDomain {
 public:
  KeyDomain(std::vector<ScalarType> types, Collector* collector, Budget* budget = nullptr);
  ~KeyDomain();
  KeyDomain(const KeyDomain&) = delete;
  KeyDomain& operator=(const KeyDomain&) = delete;

  [[nodiscard]] std::size_t arity() const noexcept { return types_.size(); }
  [[nodiscard]] std::span<const ScalarType> types() const noexcept { return types_; }
  [[nodiscard]] bool inline_form() const noexcept { return inline_; }
  [[nodiscard]] std::size_t interned() const noexcept { return size_; }

  // Key of cells[positions[i]] if it exists (inline keys always exist).
  [[nodiscard]] std::optional<Key> find(const ScalarView* cells, const std::uint32_t* positions) const;
  [[nodiscard]] std::optional<Key> find(std::span<const ScalarView> cells) const;
  // Key of the projected cells, interning it if needed; takes one reference.
  [[nodiscard]] Key acquire(const ScalarView* cells, const std::uint32_t* positions);
  [[nodiscard]] Key acquire(std::span<const ScalarView> cells);
  // One more reference to an existing key.
  void retain(Key key) noexcept;
  // Drop one reference; at zero the record leaves the dictionary and is
  // retired to the collector (it stays readable until collected).
  void release(Key key);
  // Rollback of a release that retired `key`: put it back with one reference.
  void restore(Key key);
  // Decoded values: for an inline key, written to `scratch` (room for two
  // cells); else the record's cells.
  [[nodiscard]] RowView view(Key key, ScalarView* scratch) const noexcept;
  [[nodiscard]] const ScalarView& cell(Key key, std::size_t field, ScalarView& scratch) const noexcept {
    if (inline_) {
      const auto word = pair_ && field == 0 ? key.hash : key.word;
      if (types_[field] == ScalarType::int64) scratch = static_cast<std::int64_t>(word);
      else scratch = word != 0;
      return scratch;
    }
    return reinterpret_cast<const KeyRecord*>(key.word)->cells()[field];
  }
  void check_invariants() const;
  // Every interned key with its reference count (diagnostics).
  void for_each(const std::function<void(Key, std::uint32_t)>& visit) const;

 private:
  struct Slot { std::uint64_t hash; KeyRecord* record; };
  [[nodiscard]] std::uint64_t hash_of(const ScalarView* cells, const std::uint32_t* positions) const noexcept;
  [[nodiscard]] Key inline_key(const ScalarView* cells, const std::uint32_t* positions) const noexcept;
  [[nodiscard]] std::size_t probe(std::uint64_t hash, const ScalarView* cells, const std::uint32_t* positions) const noexcept;
  void insert_slot(KeyRecord* record);
  void erase_slot(std::size_t index) noexcept;
  void grow();

  std::vector<ScalarType> types_;
  std::vector<std::uint32_t> identity_;
  bool inline_ = false, pair_ = false;  // inline form; two inline fields
  Collector* collector_;
  Budget* budget_;
  std::vector<Slot> slots_;
  std::size_t mask_ = 0, size_ = 0;
};

// --------------------------------------------------------------------- maps
// Fixed-width entries keyed by one Key. Each entry also stores one Key per
// secondary index (its bucket) and a link pair; buckets are intrusive lists.
// Entry ids are stable until the entry is erased. Erasure inside an epoch can
// be deferred (tombstone) so a rollback can relink the entry with its id.
class KeyMap {
 public:
  KeyMap() = default;
  KeyMap(std::uint32_t payload_words, std::uint32_t secondary_indexes, Budget* budget = nullptr);
  ~KeyMap();
  KeyMap(KeyMap&& other) noexcept;
  KeyMap& operator=(KeyMap&& other) noexcept;
  KeyMap(const KeyMap&) = delete;
  KeyMap& operator=(const KeyMap&) = delete;
  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] std::uint32_t ids() const noexcept { return static_cast<std::uint32_t>(state_.size()); }
  [[nodiscard]] bool live(std::uint32_t id) const noexcept { return state_[id] == 1; }
  [[nodiscard]] Key key(std::uint32_t id) const noexcept {
    const auto* e = entry(id); return {e[0], e[1]};
  }
  [[nodiscard]] std::uint64_t* payload(std::uint32_t id) noexcept { return entry(id) + 2; }
  [[nodiscard]] const std::uint64_t* payload(std::uint32_t id) const noexcept { return entry(id) + 2; }
  [[nodiscard]] Key secondary(std::uint32_t id, std::size_t index) const noexcept {
    const auto* e = entry(id) + 2 + payload_ + 3 * index; return {e[0], e[1]};
  }

  [[nodiscard]] std::uint32_t find(Key key) const noexcept;
  // Precondition: absent. Payload starts at zero; `secondary` has one key per index.
  std::uint32_t insert(Key key, const Key* secondary = nullptr);
  // Make room for `extra` more inserts (ids, entries and every index), so
  // that many inserts then never allocate (staged publication).
  void reserve(std::size_t extra);
  // Unlink from every index and free the id.
  void erase(std::uint32_t id) noexcept;
  // Unlink from every index but keep the id reserved (rollback can relink it).
  void detach(std::uint32_t id) noexcept;
  void relink(std::uint32_t id);
  void free_detached(std::uint32_t id) noexcept;
  [[nodiscard]] std::uint32_t bucket(std::size_t index, Key key) const noexcept;
  // Start fetching entry `id` (if any) ahead of its use.
  void prefetch(std::uint32_t id) const noexcept {
    if (id != no_entry) __builtin_prefetch(entry(id));
  }
  [[nodiscard]] std::uint32_t next(std::size_t index, std::uint32_t id) const noexcept {
    return static_cast<std::uint32_t>(entry(id)[2 + payload_ + 3 * index + 2]);
  }
  // Release capacity after many erasures (blocking GC phase).
  void shrink();
  [[nodiscard]] std::size_t memory_bytes() const noexcept;
  void check_invariants() const;

 private:
  struct Index { std::vector<std::uint64_t> slots; std::size_t mask = 0, used = 0; };
  [[nodiscard]] std::uint64_t* entry(std::uint32_t id) noexcept { return slab_.data() + static_cast<std::size_t>(id) * stride_; }
  [[nodiscard]] const std::uint64_t* entry(std::uint32_t id) const noexcept { return slab_.data() + static_cast<std::size_t>(id) * stride_; }
  void place(std::uint32_t id);
  void unplace(std::uint32_t id) noexcept;
  void link(std::size_t index, std::uint32_t id);
  void unlink(std::size_t index, std::uint32_t id) noexcept;
  // Bring the budget charge in line with current capacity (charges before
  // growth through reserve_* below; releases after shrinking).
  void recharge() noexcept;
  void reserve_entry();
  void reserve_slots(std::vector<std::uint64_t>& slots, std::size_t& mask, std::size_t used);
  void grow_entries(std::size_t entries);
  void grow_slots(std::vector<std::uint64_t>& slots, std::size_t& mask);


  std::uint32_t payload_ = 0, secondary_ = 0, stride_ = 2;
  std::vector<std::uint64_t> slab_;
  std::vector<std::uint8_t> state_;  // 0 free, 1 live, 2 detached
  std::vector<std::uint32_t> free_;
  std::vector<std::uint64_t> primary_;  // (tag << 32) | (id + 1)
  std::size_t mask_ = 0, size_ = 0;
  std::vector<Index> indexes_;
  Budget* budget_ = nullptr;
  std::size_t charged_ = 0;
};

}  // namespace crown::storage::keyed
