// Keyed storage primitives: KeyDomain interning/reference counting/retirement,
// KeyMap against a std::map model, and the epoch collector in all three modes.
#include "crown/storage/keyed.hpp"

#include <iostream>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using namespace crown::storage;
using namespace crown::storage::keyed;
std::uint64_t checks = 0;
void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}

void domains() {
  Collector gc({GcMode::manual});
  KeyDomain ints({ScalarType::int64}, &gc);
  check(ints.inline_form(), "single int64 keys are inline");
  const ScalarView seven{std::int64_t{7}};
  const auto a = ints.acquire({&seven, 1});
  check(ints.find({&seven, 1}) == a, "inline key is found");
  ScalarView scratch;
  check(std::get<std::int64_t>(ints.view(a, &scratch)[0]) == 7, "inline key decodes");

  KeyDomain pairs({ScalarType::int64, ScalarType::string}, &gc);
  check(!pairs.inline_form(), "composite keys are interned");
  std::string text = "hello world, a longer string";
  const ScalarView row[3]{std::int64_t{1}, std::string_view(text), std::int64_t{9}};
  const std::uint32_t positions[2]{0, 1};
  check(!pairs.find(row, positions).has_value(), "absent key is not found");
  const auto k = pairs.acquire(row, positions);
  text[0] = 'X';  // The record owns its own copy.
  const ScalarView probe[2]{std::int64_t{1}, std::string_view("hello world, a longer string")};
  check(pairs.find({probe, 2}) == k, "interned key found by equal values");
  check(std::get<std::string_view>(pairs.view(k, nullptr)[1]) == "hello world, a longer string", "interned values are copied");
  const auto k2 = pairs.acquire({probe, 2});
  check(k2 == k && pairs.interned() == 1, "equal values share one record");
  pairs.release(k2);
  check(pairs.find({probe, 2}) == k, "one reference keeps the record");
  const auto mark = gc.open_retirements();
  pairs.release(k);
  check(!pairs.find({probe, 2}).has_value() && pairs.interned() == 0, "last release leaves the dictionary");
  check(gc.open_retirements() == mark + 1, "last release retires the record");
  // Rollback: forget the retirement and restore the record.
  gc.forget_after(mark);
  pairs.restore(k);
  check(pairs.find({probe, 2}) == k, "restore puts the record back");
  pairs.release(k);
  gc.seal();
  gc.collect();
  check(gc.statistics().freed_objects == 1, "sealed garbage is collected");
  pairs.check_invariants();

  // Random interning against a multiset model.
  std::mt19937 random(5);
  KeyDomain mixed({ScalarType::string, ScalarType::int64, ScalarType::boolean}, &gc);
  std::map<std::tuple<std::string, std::int64_t, bool>, std::pair<Key, int>> model;
  std::vector<std::string> strings;
  for (int i = 0; i < 20000; ++i) {
    const auto s = "s" + std::to_string(random() % 30);
    const auto n = static_cast<std::int64_t>(random() % 5);
    const bool b = random() % 2;
    const ScalarView cells[3]{std::string_view(s), n, b};
    const auto tuple = std::make_tuple(s, n, b);
    if (random() % 3 == 0 && model.count(tuple)) {
      auto& [key, count] = model[tuple];
      mixed.release(key);
      if (--count == 0) model.erase(tuple);
    } else {
      const auto key = mixed.acquire({cells, 3});
      auto [it, fresh] = model.try_emplace(tuple, key, 0);
      check(fresh || it->second.first == key, "equal values intern to the same key");
      ++it->second.second;
    }
    if (i % 500 == 0) { gc.seal(); gc.collect(); }
  }
  check(mixed.interned() == model.size(), "interned count matches the model");
  mixed.check_invariants();
}

// Two int64/Boolean fields are carried inline: no record, no references, and
// maps place such keys by both words (pairs sharing a field spread out).
void inline_pairs() {
  Collector gc({GcMode::manual});
  KeyDomain edges({ScalarType::int64, ScalarType::int64}, &gc);
  KeyDomain flagged({ScalarType::boolean, ScalarType::int64}, &gc);
  check(edges.inline_form() && flagged.inline_form(), "two word fields are inline");
  const ScalarView row[3]{std::int64_t{-3}, std::int64_t{4}, true};
  const std::uint32_t forward[2]{0, 1}, backward[2]{1, 0}, mixed[2]{2, 1};
  const auto a = edges.acquire(row, forward), b = edges.acquire(row, backward);
  check(a != b && edges.find(row, forward) == a && edges.interned() == 0, "pairs are ordered values, not records");
  ScalarView scratch[2];
  const auto decoded = edges.view(b, scratch);
  check(decoded.size() == 2 && std::get<std::int64_t>(decoded[0]) == 4 && std::get<std::int64_t>(decoded[1]) == -3,
      "inline pair decodes in field order");
  const auto c = flagged.acquire(row, mixed);
  ScalarView one;
  check(std::get<bool>(flagged.cell(c, 0, one)) && std::get<std::int64_t>(flagged.cell(c, 1, one)) == 4,
      "Boolean and int64 fields decode");
  edges.release(a); edges.retain(b); edges.release(b);
  check(gc.open_retirements() == 0, "inline keys retire nothing");
  KeyMap map(1, 1);
  std::map<std::pair<std::int64_t, std::int64_t>, std::uint32_t> model;
  for (std::int64_t x = 0; x < 64; ++x)
    for (std::int64_t y = 0; y < 64; ++y) {
      const ScalarView cells[2]{x, y};
      const Key by_source{static_cast<std::uint64_t>(x), 0};  // any fixed-width key works as a bucket
      model[{x, y}] = map.insert(edges.acquire({cells, 2}), &by_source);
    }
  for (const auto& [value, id] : model) {
    const ScalarView cells[2]{value.first, value.second};
    check(map.find(*edges.find({cells, 2})) == id, "inline pair found in its map");
  }
  std::size_t members = 0;
  for (auto id = map.bucket(0, Key{7, 0}); id != no_entry; id = map.next(0, id)) ++members;
  check(members == 64, "secondary bucket by first field");
}

void maps() {
  std::mt19937 random(11);
  KeyMap map(2, 2);
  struct Value { std::uint64_t payload; Key a, b; };
  std::map<std::uint64_t, std::pair<std::uint32_t, Value>> model;  // key word -> id, value
  std::set<std::uint32_t> detached;
  auto key = [](std::uint64_t word) { return Key{mix(word + 1), word}; };
  for (int step = 0; step < 200000; ++step) {
    const auto word = static_cast<std::uint64_t>(random() % 3000);
    const auto found = map.find(key(word));
    const auto modelled = model.find(word);
    check((found == no_entry) == (modelled == model.end()), "membership matches the model");
    if (found == no_entry) {
      const Key secondary[2]{key(word % 17), key(word % 5)};
      const auto id = map.insert(key(word), secondary);
      map.payload(id)[0] = word * 3;
      model[word] = {id, {word * 3, secondary[0], secondary[1]}};
    } else {
      check(found == modelled->second.first && map.payload(found)[0] == modelled->second.second.payload, "payload matches");
      if (random() % 4 == 0) {
        map.detach(found);
        if (random() % 2) map.relink(found);
        else { map.free_detached(found); model.erase(modelled); }
      } else {
        map.erase(found);
        model.erase(modelled);
      }
    }
    if (step % 20000 == 0) {
      map.check_invariants();
      for (std::uint64_t s = 0; s < 17; ++s) {
        std::size_t expected = 0, actual = 0;
        for (const auto& [w, item] : model) if (w % 17 == s) ++expected;
        for (auto id = map.bucket(0, key(s)); id != no_entry; id = map.next(0, id)) ++actual;
        check(expected == actual, "bucket size matches the model");
      }
    }
  }
  check(map.size() == model.size(), "size matches the model");
  for (const auto& [w, item] : model) map.erase(item.first);
  map.shrink();
  map.check_invariants();
  check(map.size() == 0, "empty after erasing everything");
}

int freed = 0;
void count_free(void* object) { ++freed; ::operator delete(object); }

void collectors() {
  for (const auto mode : {GcMode::blocking, GcMode::background, GcMode::manual}) {
    freed = 0;
    {
      Collector gc({mode, 2, std::size_t{1} << 30});
      gc.retire(::operator new(8), &count_free, 8);
      auto pin = gc.pin();  // A reader observing epoch 1 keeps epoch-1 garbage alive.
      gc.seal();
      gc.retire(::operator new(8), &count_free, 8);
      gc.seal();
      gc.seal();
      gc.drain();
      check(freed == 0, "pinned epochs keep their garbage");
      pin.reset();
      gc.seal();
      if (mode != GcMode::blocking) gc.collect();
      gc.drain();
      check(freed == 2, "unpinned garbage is freed");
      gc.retire(::operator new(8), &count_free, 8);
    }
    check(freed == 3, "destruction frees remaining garbage");
  }
}
// Single-threaded (blocking) mode with the default options collects only when
// the retired-memory pool is full; a budget charge that would fail first
// reclaims retired records, in every mode.
Budget* charged = nullptr;
void release_charge(void* object) {
  charged->release(64);
  ++freed;
  ::operator delete(object);
}
void pool_and_budget() {
  freed = 0;
  {
    GcOptions options;  // blocking, no epoch interval
    check(options.mode == GcMode::blocking && options.epoch_interval == 0, "default GC is single-threaded, pool-triggered");
    options.retired_bytes = 64;
    Collector gc(options);
    for (int epoch = 0; epoch < 7; ++epoch) {
      gc.retire(::operator new(8), &count_free, 8);
      gc.seal();
    }
    check(freed == 0 && gc.statistics().collections == 0, "no collection before the pool is full");
    gc.retire(::operator new(8), &count_free, 8);
    gc.seal();  // 64 retired bytes: the pool is full
    check(freed == 8 && gc.statistics().collections == 1, "a full pool is collected");
  }
  for (const auto mode : {GcMode::blocking, GcMode::background, GcMode::manual}) {
    freed = 0;
    Budget budget(100);
    charged = &budget;
    GcOptions options{mode, 0, std::size_t{1} << 30};
    Collector gc(options);
    budget.set_reclaimer(&gc);
    budget.charge(64);
    gc.retire(::operator new(8), &release_charge, 64);  // retired, still charged
    gc.seal();
    budget.charge(64);  // exceeds 100 unless the retired record is reclaimed first
    check(budget.used() == 64, "a failing charge reclaims retired memory first");
    if (mode != GcMode::background) check(freed == 1, "the charge itself collected");
    gc.drain();
    check(freed == 1, "the retired record was freed once");
    bool limited = false;
    try { budget.charge(64); } catch (const resource::MemoryFailure&) { limited = true; }
    check(limited && budget.used() == 64, "live memory still enforces the limit");
    budget.release(64);
  }
  charged = nullptr;
}
// Process-wide statistics add up every collector, including destroyed ones.
void process_totals() {
  freed = 0;
  const auto before = process_gc_statistics();
  {
    Collector gc(GcOptions{GcMode::manual, 0, std::size_t{1} << 30});
    gc.retire(::operator new(8), &count_free, 8);
    gc.seal();
    const auto open = process_gc_statistics();
    check(open.retired_bytes == before.retired_bytes + 8 && open.pending_bytes == before.pending_bytes + 8,
          "a live collector's retirements are counted");
    gc.collect();
    const auto collected = process_gc_statistics();
    check(collected.collections == before.collections + 1 && collected.freed_bytes == before.freed_bytes + 8,
          "a live collector's collection is counted");
    gc.retire(::operator new(8), &count_free, 8);
    gc.seal();
  }
  const auto after = process_gc_statistics();
  check(freed == 2 && after.collections == before.collections + 1 && after.retired_bytes == before.retired_bytes + 16 &&
            after.pending_bytes == before.pending_bytes,
        "a destroyed collector keeps its totals; teardown is not a collection");
}
}  // namespace

int main() try {
  domains();
  inline_pairs();
  maps();
  collectors();
  pool_and_budget();
  process_totals();
  std::cout << "keyed storage checks=" << checks << "\n";
  return 0;
} catch (const std::exception& failure) {
  std::cerr << "FAIL: " << failure.what() << "\n";
  return 1;
}
