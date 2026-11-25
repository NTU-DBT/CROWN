#pragma once

// Private hash tables of the SQL rows/aggregate owners: complete nullable
// tuples (the source bags, enforced-key counters, groups) and the per-batch
// touched sets. Keys are owned aggregate::Tuple handles; probes borrow cells.
// Equality is equivalence under the exact scalar order the former ordered maps
// used (NULL first; decimals by numeric value), and the hash agrees with it.
// Iteration order is unspecified: callers that expose an order sort.
#include "crown/runtime/aggregate.hpp"
#include "crown/resource/allocator.hpp"

#include <algorithm>
#include <bit>
#include <cstdint>
#include <memory>
#include <span>
#include <stdexcept>
#include <vector>

namespace crown::runtime::sql_detail {
using Cell = aggregate::Cell;
using Tuple = aggregate::Tuple;

inline std::uint64_t mix(std::uint64_t x) noexcept {
  x ^= x >> 30; x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27; x *= 0x94d049bb133111ebULL;
  return x ^ (x >> 31);
}
inline std::uint64_t hash_bytes(std::string_view bytes) noexcept {
  std::uint64_t h = 0xcbf29ce484222325ULL ^ bytes.size();
  for (const char c : bytes) h = (h ^ static_cast<unsigned char>(c)) * 0x100000001b3ULL;
  return h;
}
inline std::uint64_t hash_cell(const Cell& cell) noexcept {
  if (!cell) return 0x6a09e667f3bcc909ULL;
  const auto& value = *cell;
  const auto kind = static_cast<std::uint64_t>(value.index()) << 56;
  if (const auto* number = std::get_if<std::int64_t>(&value)) return mix(static_cast<std::uint64_t>(*number) ^ kind);
  if (const auto* text = std::get_if<std::string_view>(&value)) return mix(hash_bytes(*text) ^ kind);
  if (const auto* flag = std::get_if<bool>(&value)) return mix((*flag ? 1U : 0U) ^ kind);
  if (const auto* date = std::get_if<Date>(&value))
    return mix(static_cast<std::uint64_t>(static_cast<std::int64_t>(date->epoch_days())) ^ kind);
  // Decimals: numeric value (sign, exponent, digits without trailing zeros);
  // every zero is one value.
  const auto parts = std::get<storage::InlineDecimal>(value).parts();
  if (parts.digits == "0") return mix(kind ^ 0x5a);
  auto digits = parts.digits;
  while (digits.size() > 1 && digits.back() == '0') digits.remove_suffix(1);
  const auto exponent = static_cast<std::int64_t>(parts.digits.size()) - static_cast<std::int64_t>(parts.scale);
  return mix(hash_bytes(digits) ^ kind ^ (static_cast<std::uint64_t>(exponent) << 1) ^ (parts.negative ? 1U : 0U));
}
inline std::uint64_t hash_cells(std::span<const Cell> cells) noexcept {
  std::uint64_t h = mix(cells.size() + 0x9e3779b97f4a7c15ULL);
  for (const auto& cell : cells) h = mix(h ^ hash_cell(cell)) + 0x9e3779b97f4a7c15ULL;
  return h;
}
inline bool equivalent(const Cell& a, const Cell& b) noexcept {
  if (!a || !b) return !a && !b;
  const auto* x = std::get_if<std::int64_t>(&*a);
  const auto* y = std::get_if<std::int64_t>(&*b);
  if (x && y) return *x == *y;
  return (*a <=> *b) == 0;
}
inline bool equivalent(std::span<const Cell> a, std::span<const Cell> b) noexcept {
  if (a.size() != b.size()) return false;
  for (std::size_t i = 0; i < a.size(); ++i) if (!equivalent(a[i], b[i])) return false;
  return true;
}
// The former maps' strict weak order (NULL first, exact scalar order).
inline bool less(std::span<const Cell> a, std::span<const Cell> b) noexcept {
  return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

// Open-addressing index (linear probing, backward-shift deletion) over a
// dense entry vector. A slot holds the high hash word and entry id + 1; the
// home position is a function of the slot alone. All storage is accounted.
// reserve(n) makes the next n inserts nonthrowing and nonallocating; erase
// never allocates and moves the last entry into the erased position.
template<class V>
class TupleTable {
 public:
  struct Entry {
    Tuple key;
    V value;
    std::uint64_t hash;
  };
  static constexpr std::size_t npos = static_cast<std::size_t>(-1);

  TupleTable(const resource::MemoryAccount& account, resource::MemoryPurpose purpose)
      : entries_(resource::MemoryAllocator<Entry>(account, purpose)),
        slots_(resource::MemoryAllocator<std::uint64_t>(account, purpose)) {}
  TupleTable(TupleTable&&) noexcept = default;
  TupleTable(const TupleTable&) = delete;
  TupleTable& operator=(const TupleTable&) = delete;
  TupleTable& operator=(TupleTable&&) = delete;

  [[nodiscard]] std::size_t size() const noexcept { return entries_.size(); }
  [[nodiscard]] bool empty() const noexcept { return entries_.empty(); }
  [[nodiscard]] Entry& at(std::size_t id) noexcept { return entries_[id]; }
  [[nodiscard]] const Entry& at(std::size_t id) const noexcept { return entries_[id]; }
  [[nodiscard]] std::span<Entry> entries() noexcept { return entries_; }
  [[nodiscard]] std::span<const Entry> entries() const noexcept { return entries_; }

  [[nodiscard]] std::size_t find(std::span<const Cell> key, std::uint64_t hash) const noexcept {
    if (slots_.empty()) return npos;
    const auto tag = hash >> 32;
    for (auto i = tag & mask_;; i = (i + 1) & mask_) {
      const auto slot = slots_[i];
      if (!slot) return npos;
      if ((slot >> 32) == tag) {
        const auto id = static_cast<std::size_t>((slot & 0xffffffffU) - 1);
        const auto& entry = entries_[id];
        if (entry.hash == hash && equivalent(entry.key.view(), key)) return id;
      }
    }
  }
  [[nodiscard]] std::size_t find(std::span<const Cell> key) const noexcept { return find(key, hash_cells(key)); }

  // Room for `extra` more entries: the following inserts cannot fail.
  void reserve(std::size_t extra) {
    const auto needed = entries_.size() + extra;
    if (needed >= 0xffffffffU) throw std::length_error("SQL tuple table capacity");
    if (entries_.capacity() < needed) entries_.reserve(std::max(needed, entries_.capacity() * 2));
    if (needed * 2 > slots_.size()) rehash(std::bit_ceil(std::max<std::size_t>(16, needed * 2)));
  }
  // Precondition: `key` is absent and capacity was reserved.
  std::size_t insert(Tuple key, V value, std::uint64_t hash) noexcept {
    const auto id = entries_.size();
    entries_.push_back(Entry{std::move(key), std::move(value), hash});
    place(hash, id);
    return id;
  }
  void erase(std::size_t id) noexcept {
    unplace(id);
    const auto last = entries_.size() - 1;
    if (id != last) {
      // The last entry takes the freed id; its slot is renumbered.
      const auto position = slot_of(last);
      slots_[position] = (slots_[position] & ~std::uint64_t{0xffffffffU}) | static_cast<std::uint64_t>(id + 1);
      std::destroy_at(&entries_[id]);
      std::construct_at(&entries_[id], std::move(entries_[last]));
    }
    entries_.pop_back();
  }
  void clear() noexcept {
    entries_.clear();
    std::fill(slots_.begin(), slots_.end(), std::uint64_t{0});
  }

 private:
  void rehash(std::size_t capacity) {
    std::vector<std::uint64_t, resource::MemoryAllocator<std::uint64_t>> fresh(capacity, 0, slots_.get_allocator());
    slots_.swap(fresh);
    mask_ = capacity - 1;
    for (std::size_t id = 0; id < entries_.size(); ++id) place(entries_[id].hash, id);
  }
  void place(std::uint64_t hash, std::size_t id) noexcept {
    const auto tag = hash >> 32;
    auto i = tag & mask_;
    while (slots_[i]) i = (i + 1) & mask_;
    slots_[i] = (tag << 32) | static_cast<std::uint64_t>(id + 1);
  }
  [[nodiscard]] std::size_t slot_of(std::size_t id) const noexcept {
    const auto tag = entries_[id].hash >> 32;
    const auto wanted = static_cast<std::uint64_t>(id + 1);
    auto i = tag & mask_;
    while ((slots_[i] & 0xffffffffU) != wanted) i = (i + 1) & mask_;
    return i;
  }
  void unplace(std::size_t id) noexcept {
    auto hole = slot_of(id);
    slots_[hole] = 0;
    for (auto i = (hole + 1) & mask_; slots_[i]; i = (i + 1) & mask_) {
      const auto home = (slots_[i] >> 32) & mask_;
      // Move back unless the entry's home lies cyclically in (hole, i].
      const bool stays = hole <= i ? (home > hole && home <= i) : (home > hole || home <= i);
      if (stays) continue;
      slots_[hole] = slots_[i];
      slots_[i] = 0;
      hole = i;
    }
  }

  std::vector<Entry, resource::MemoryAllocator<Entry>> entries_;
  std::vector<std::uint64_t, resource::MemoryAllocator<std::uint64_t>> slots_;
  std::size_t mask_ = 0;
};

// Per-batch touched keys: lookup while preparing, then one sort into the
// exposed (domain, exact key) order. Item references stay valid until the
// next add(); the set is scratch under the owner's account.
template<class Payload>
class TouchedSet {
 public:
  struct Item {
    std::size_t domain;
    Tuple key;
    std::uint64_t hash;
    Payload payload;
  };
  explicit TouchedSet(const resource::MemoryAccount& account)
      : items_(resource::MemoryAllocator<Item>(account, resource::MemoryPurpose::scratch)),
        slots_(resource::MemoryAllocator<std::uint32_t>(account, resource::MemoryPurpose::scratch)) {}
  [[nodiscard]] Item* find(std::size_t domain, std::span<const Cell> key, std::uint64_t hash) noexcept {
    if (slots_.empty()) return nullptr;
    for (auto i = home(domain, hash);; i = (i + 1) & mask_) {
      const auto slot = slots_[i];
      if (!slot) return nullptr;
      auto& item = items_[slot - 1];
      if (item.domain == domain && item.hash == hash && equivalent(item.key.view(), key)) return &item;
    }
  }
  Item& add(std::size_t domain, Tuple key, std::uint64_t hash, Payload payload) {
    if (items_.size() + 1 >= 0xffffffffU) throw std::length_error("SQL touched set capacity");
    if ((items_.size() + 1) * 2 > slots_.size()) reindex(std::bit_ceil(std::max<std::size_t>(16, (items_.size() + 1) * 2)));
    items_.push_back(Item{domain, std::move(key), hash, std::move(payload)});
    place(items_.size() - 1);
    return items_.back();
  }
  // (domain, exact scalar order of the key), as the former ordered maps.
  void sort() {
    if (items_.size() < 2) return;
    std::sort(items_.begin(), items_.end(), [](const Item& a, const Item& b) {
      return a.domain != b.domain ? a.domain < b.domain : less(a.key.view(), b.key.view());
    });
    std::fill(slots_.begin(), slots_.end(), std::uint32_t{0});
    for (std::size_t id = 0; id < items_.size(); ++id) place(id);
  }
  [[nodiscard]] std::span<Item> items() noexcept { return items_; }
  [[nodiscard]] std::size_t size() const noexcept { return items_.size(); }
  [[nodiscard]] bool empty() const noexcept { return items_.empty(); }
  void clear() noexcept {
    items_.clear();
    std::fill(slots_.begin(), slots_.end(), std::uint32_t{0});
  }

 private:
  [[nodiscard]] std::size_t home(std::size_t domain, std::uint64_t hash) const noexcept {
    return static_cast<std::size_t>(mix(hash ^ (static_cast<std::uint64_t>(domain) * 0x9e3779b97f4a7c15ULL))) & mask_;
  }
  void reindex(std::size_t capacity) {
    std::vector<std::uint32_t, resource::MemoryAllocator<std::uint32_t>> fresh(capacity, 0, slots_.get_allocator());
    slots_.swap(fresh);
    mask_ = capacity - 1;
    for (std::size_t id = 0; id < items_.size(); ++id) place(id);
  }
  void place(std::size_t id) noexcept {
    auto i = home(items_[id].domain, items_[id].hash);
    while (slots_[i]) i = (i + 1) & mask_;
    slots_[i] = static_cast<std::uint32_t>(id + 1);
  }
  std::vector<Item, resource::MemoryAllocator<Item>> items_;
  std::vector<std::uint32_t, resource::MemoryAllocator<std::uint32_t>> slots_;
  std::size_t mask_ = 0;
};

}  // namespace crown::runtime::sql_detail
