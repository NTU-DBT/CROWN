#pragma once
// Internal storage for the flat executors: fixed-arity 64-bit word keys in
// open-addressing hash tables with intrusive secondary buckets, plus the
// append-only string dictionary used for value encoding.
#include "crown/ir/model.hpp"
#include "crown/storage/accounted_row.hpp"

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace crown::runtime::flat_detail {
using Word = std::int64_t;
constexpr std::uint32_t none = 0xffffffffU;
constexpr std::size_t max_arity = 32;
constexpr std::size_t max_nodes = 64;

[[noreturn, gnu::cold, gnu::noinline]] inline void fail(const char* message) {
  throw std::logic_error(std::string("flat runtime: ") + message);
}
inline void require(bool value, const char* message) {
  if (!value) [[unlikely]] fail(message);
}

inline std::uint64_t step_hash(std::uint64_t h, Word value) {
  h = (h ^ static_cast<std::uint64_t>(value)) * 0xbf58476d1ce4e5b9ULL;
  return h ^ (h >> 31);
}
inline std::uint64_t finish_hash(std::uint64_t h) {
  h ^= h >> 33; h *= 0xff51afd7ed558ccdULL; h ^= h >> 33; h *= 0xc4ceb9fe1a85ec53ULL;
  return h ^ (h >> 33);
}
inline std::uint64_t hash_words(const Word* w, std::size_t n) {
  std::uint64_t h = 0x9e3779b97f4a7c15ULL;
  for (std::size_t i = 0; i < n; ++i) h = step_hash(h, w[i]);
  return finish_hash(h);
}
inline std::uint64_t hash_gather(const Word* w, const std::uint32_t* positions, std::size_t n) {
  std::uint64_t h = 0x9e3779b97f4a7c15ULL;
  for (std::size_t i = 0; i < n; ++i) h = step_hash(h, w[positions[i]]);
  return finish_hash(h);
}
inline bool equal_words(const Word* a, const Word* b, std::size_t n) {
  for (std::size_t i = 0; i < n; ++i) if (a[i] != b[i]) return false;
  return true;
}
inline bool equal_gather(const Word* entry, const std::uint32_t* positions, const Word* probe, std::size_t n) {
  for (std::size_t i = 0; i < n; ++i) if (entry[positions[i]] != probe[i]) return false;
  return true;
}
inline std::uint32_t tag_of(std::uint64_t h) { return static_cast<std::uint32_t>(h >> 32); }
inline std::uint64_t slot_of(std::uint32_t tag, std::uint32_t id) {
  return (static_cast<std::uint64_t>(tag) << 32) | (static_cast<std::uint64_t>(id) + 1);
}
inline std::uint32_t slot_id(std::uint64_t slot) { return static_cast<std::uint32_t>(slot) - 1; }
inline std::uint32_t slot_tag(std::uint64_t slot) { return static_cast<std::uint32_t>(slot >> 32); }

// Backward-shift deletion for linear probing; slot homes come from their tags.
inline void erase_slot(std::vector<std::uint64_t>& slots, std::size_t mask, std::size_t i) {
  for (std::size_t j = (i + 1) & mask;; j = (j + 1) & mask) {
    const auto slot = slots[j];
    if (!slot) break;
    const std::size_t home = slot_tag(slot) & mask;
    const bool stays = i <= j ? (i < home && home <= j) : (i < home || home <= j);
    if (!stays) { slots[i] = slot; i = j; }
  }
  slots[i] = 0;
}
inline void grow_slots(std::vector<std::uint64_t>& slots, std::size_t& mask) {
  std::vector<std::uint64_t> next(slots.size() * 2, 0);
  const std::size_t next_mask = next.size() - 1;
  for (const auto slot : slots) {
    if (!slot) continue;
    std::size_t i = slot_tag(slot) & next_mask;
    while (next[i]) i = (i + 1) & next_mask;
    next[i] = slot;
  }
  slots.swap(next);
  mask = next_mask;
}

// Fixed-arity word keys with stable entry ids, an open-addressing primary
// index and intrusive secondary buckets (one doubly-linked list per distinct
// projected key). Entry layout: key words, payload words, one link word per
// secondary index (next in the low half, previous in the high half).
class Table {
 public:
  Table() = default;
  Table(std::uint32_t arity, std::uint32_t payload, std::vector<std::vector<std::uint32_t>> secondary)
      : arity_(arity), payload_(payload), links_(arity + payload),
        stride_(arity + payload + static_cast<std::uint32_t>(secondary.size())), primary_(16, 0), mask_(15) {
    secondary_.resize(secondary.size());
    for (std::size_t i = 0; i < secondary.size(); ++i) {
      secondary_[i].positions = std::move(secondary[i]);
      secondary_[i].slots.assign(16, 0);
      secondary_[i].mask = 15;
    }
  }
  [[nodiscard]] std::uint32_t arity() const { return arity_; }
  [[nodiscard]] std::size_t size() const { return size_; }
  [[nodiscard]] std::uint32_t ids() const { return static_cast<std::uint32_t>(used_.size()); }
  [[nodiscard]] bool used(std::uint32_t id) const { return used_[id] != 0; }
  [[nodiscard]] Word* key(std::uint32_t id) { return slab_.data() + static_cast<std::size_t>(id) * stride_; }
  [[nodiscard]] const Word* key(std::uint32_t id) const { return slab_.data() + static_cast<std::size_t>(id) * stride_; }
  [[nodiscard]] Word* payload(std::uint32_t id) { return key(id) + arity_; }
  [[nodiscard]] const Word* payload(std::uint32_t id) const { return key(id) + arity_; }

  [[nodiscard]] std::uint32_t find(const Word* k) const {
    const auto tag = tag_of(hash_words(k, arity_));
    for (std::size_t i = tag & mask_;; i = (i + 1) & mask_) {
      const auto slot = primary_[i];
      if (!slot) return none;
      if (slot_tag(slot) == tag && equal_words(key(slot_id(slot)), k, arity_)) return slot_id(slot);
    }
  }
  // Precondition: k is absent. Payload words start at zero.
  std::uint32_t insert(const Word* k) {
    const auto tag = tag_of(hash_words(k, arity_));
    if ((size_ + 1) * 2 > primary_.size()) grow_slots(primary_, mask_);
    const auto id = allocate();
    Word* entry = key(id);
    std::memcpy(entry, k, sizeof(Word) * arity_);
    std::memset(entry + arity_, 0, sizeof(Word) * (stride_ - arity_));
    std::size_t i = tag & mask_;
    while (primary_[i]) i = (i + 1) & mask_;
    primary_[i] = slot_of(tag, id);
    for (std::size_t s = 0; s < secondary_.size(); ++s) link(s, id);
    ++size_;
    return id;
  }
  void erase(std::uint32_t id) {
    for (std::size_t s = 0; s < secondary_.size(); ++s) unlink(s, id);
    const auto tag = tag_of(hash_words(key(id), arity_));
    std::size_t i = tag & mask_;
    while (primary_[i] != slot_of(tag, id)) i = (i + 1) & mask_;
    erase_slot(primary_, mask_, i);
    used_[id] = 0;
    free_.push_back(id);
    --size_;
  }
  // First entry whose secondary projection equals probe, or none.
  [[nodiscard]] std::uint32_t bucket(std::size_t s, const Word* probe) const {
    const auto& index = secondary_[s];
    const auto n = index.positions.size();
    const auto tag = tag_of(hash_words(probe, n));
    for (std::size_t i = tag & index.mask;; i = (i + 1) & index.mask) {
      const auto slot = index.slots[i];
      if (!slot) return none;
      if (slot_tag(slot) == tag && equal_gather(key(slot_id(slot)), index.positions.data(), probe, n))
        return slot_id(slot);
    }
  }
  [[nodiscard]] std::uint32_t next(std::size_t s, std::uint32_t id) const {
    return static_cast<std::uint32_t>(static_cast<std::uint64_t>(key(id)[links_ + s]));
  }

 private:
  struct Secondary {
    std::vector<std::uint32_t> positions;
    std::vector<std::uint64_t> slots;
    std::size_t mask = 0, used = 0;
  };
  std::uint32_t allocate() {
    std::uint32_t id;
    if (!free_.empty()) { id = free_.back(); free_.pop_back(); }
    else {
      require(used_.size() < none - 1, "table entry ids exhausted");
      id = static_cast<std::uint32_t>(used_.size());
      used_.push_back(0);
      slab_.resize(slab_.size() + stride_);
    }
    used_[id] = 1;
    return id;
  }
  std::uint32_t link_next(std::size_t s, std::uint32_t id) const { return next(s, id); }
  std::uint32_t link_prev(std::size_t s, std::uint32_t id) const {
    return static_cast<std::uint32_t>(static_cast<std::uint64_t>(key(id)[links_ + s]) >> 32);
  }
  void set_link(std::size_t s, std::uint32_t id, std::uint32_t next_id, std::uint32_t prev_id) {
    key(id)[links_ + s] = static_cast<Word>((static_cast<std::uint64_t>(prev_id) << 32) | next_id);
  }
  void set_next(std::size_t s, std::uint32_t id, std::uint32_t next_id) { set_link(s, id, next_id, link_prev(s, id)); }
  void set_prev(std::size_t s, std::uint32_t id, std::uint32_t prev_id) { set_link(s, id, link_next(s, id), prev_id); }
  void link(std::size_t s, std::uint32_t id) {
    auto& index = secondary_[s];
    if ((index.used + 1) * 2 > index.slots.size()) grow_slots(index.slots, index.mask);
    const auto* positions = index.positions.data();
    const auto n = index.positions.size();
    const Word* entry = key(id);
    const auto tag = tag_of(hash_gather(entry, positions, n));
    for (std::size_t i = tag & index.mask;; i = (i + 1) & index.mask) {
      const auto slot = index.slots[i];
      if (!slot) {
        index.slots[i] = slot_of(tag, id);
        ++index.used;
        set_link(s, id, none, none);
        return;
      }
      if (slot_tag(slot) != tag) continue;
      const auto head = slot_id(slot);
      const Word* other = key(head);
      bool same = true;
      for (std::size_t f = 0; f < n; ++f) if (other[positions[f]] != entry[positions[f]]) { same = false; break; }
      if (!same) continue;
      set_link(s, id, head, none);
      set_prev(s, head, id);
      index.slots[i] = slot_of(tag, id);
      return;
    }
  }
  void unlink(std::size_t s, std::uint32_t id) {
    const auto next_id = link_next(s, id), prev_id = link_prev(s, id);
    if (prev_id != none) {
      set_next(s, prev_id, next_id);
      if (next_id != none) set_prev(s, next_id, prev_id);
      return;
    }
    auto& index = secondary_[s];
    const auto tag = tag_of(hash_gather(key(id), index.positions.data(), index.positions.size()));
    std::size_t i = tag & index.mask;
    while (index.slots[i] != slot_of(tag, id)) i = (i + 1) & index.mask;
    if (next_id != none) {
      index.slots[i] = slot_of(tag, next_id);
      set_prev(s, next_id, none);
    } else {
      erase_slot(index.slots, index.mask, i);
      --index.used;
    }
  }

  std::uint32_t arity_ = 0, payload_ = 0, links_ = 0, stride_ = 0;
  std::vector<Word> slab_;
  std::vector<std::uint8_t> used_;
  std::vector<std::uint32_t> free_;
  std::vector<std::uint64_t> primary_;
  std::size_t mask_ = 0, size_ = 0;
  std::vector<Secondary> secondary_;
};


class Dictionary {
 public:
  Word intern(std::string_view text) {
    auto found = ids_.find(std::string(text));
    if (found != ids_.end()) return found->second;
    const auto id = static_cast<Word>(strings_.size());
    strings_.emplace_back(text);
    ids_.emplace(strings_.back(), id);
    return id;
  }
  [[nodiscard]] const std::string& text(Word id) const { return strings_.at(static_cast<std::size_t>(id)); }
  Word encode(const storage::ScalarView& value) {
    if (const auto* integer = std::get_if<std::int64_t>(&value)) return *integer;
    if (const auto* text = std::get_if<std::string_view>(&value)) return intern(*text);
    if (const auto* flag = std::get_if<bool>(&value)) return *flag ? 1 : 0;
    fail("unsupported constant type");
  }
  Word encode(const Value& value) {
    if (const auto* integer = std::get_if<std::int64_t>(&value)) return *integer;
    if (const auto* text = std::get_if<std::string>(&value)) return intern(*text);
    if (const auto* flag = std::get_if<bool>(&value)) return *flag ? 1 : 0;
    fail("unsupported value type");
  }
  [[nodiscard]] Value decode(ScalarType type, Word value) const {
    switch (type) {
      case ScalarType::int64: return value;
      case ScalarType::string: return text(value);
      case ScalarType::boolean: return value != 0;
      default: fail("unsupported output type");
    }
  }
  static bool supported(ScalarType type) {
    return type == ScalarType::int64 || type == ScalarType::string || type == ScalarType::boolean;
  }

 private:
  std::unordered_map<std::string, Word> ids_;
  std::vector<std::string> strings_;
};

}  // namespace crown::runtime::flat_detail
