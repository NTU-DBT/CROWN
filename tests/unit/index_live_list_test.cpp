#include "live_list.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

using crown::Error;
using crown::storage::IndexWork;
using crown::storage::IndexWorkAllowance;
using crown::storage::detail::LiveList;
using crown::storage::detail::LiveListHook;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template <class Function>
void rejects(std::string_view code, Function&& function) {
  bool rejected = false;
  try { function(); }
  catch (const Error& error) { verify(error.code() == code, "wrong error code");rejected = true; }
  verify(rejected, "operation unexpectedly succeeded");
}
struct Node {
  Node(std::uint64_t value, std::uint64_t annotation) : key(value), payload(annotation) {}
  std::uint64_t key;
  std::uint64_t payload;
  LiveListHook<Node> row;
  LiveListHook<Node> bucket;
};
using RowList = LiveList<Node, &Node::row>;
using Bucket = LiveList<Node, &Node::bucket>;
static_assert(!std::is_copy_constructible_v<Node> && !std::is_move_constructible_v<Node>);
static_assert(!std::is_copy_constructible_v<Bucket> && !std::is_move_constructible_v<Bucket>);

IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{1'000'000, 0, 0, 0, 1'000'000});
}
template <class List>
std::vector<std::uint64_t> order(const List& list) {
  std::vector<std::uint64_t> result;
  for (auto* member = list.first(); member != nullptr; member = List::next(*member)) {
    verify(result.size() < list.size(), "live list is cyclic");
    verify(list.contains(*member), "list traversal reached a foreign node");
    result.push_back(member->key);
  }
  verify(result.size() == list.size(), "live list cardinality differs");
  if (result.empty()) verify(list.last() == nullptr, "empty live list has a tail");
  else verify(list.last()->key == result.back(), "tail differs from traversal");
  return result;
}

void boundaries_and_membership() {
  Bucket empty(0);auto work = ample();
  rejects("storage_capacity", [&] { empty.prepare_insert(work); });
  verify(empty.size() == 0 && empty.first() == nullptr, "zero capacity acquired membership");
  Bucket bucket(3);RowList row(3);
  constexpr auto above_double = (std::uint64_t{1} << 53U) + 117U;
  Node zero(1, 0), large(2, above_double), maximum(3, std::numeric_limits<std::uint64_t>::max());
  IndexWorkAllowance one_short(IndexWork{.structural_steps = 1, .link_actions = 4});
  const auto before = one_short.remaining();
  rejects("storage_work_limit", [&] { bucket.prepare_insert(one_short); });
  verify(one_short.remaining() == before && bucket.size() == 0, "partial insertion admission changed list/grant");
  for (auto* node : {&zero, &large, &maximum}) {
    IndexWorkAllowance exact(IndexWork{.structural_steps = 1, .link_actions = Bucket::insert_actions});
    bucket.prepare_insert(exact);
    verify(exact.remaining() == IndexWork{}, "insert reservation boundary differs");
    bucket.append_prepaid(*node);
    row.prepare_insert(work);row.append_prepaid(*node);
  }
  rejects("storage_capacity", [&] { bucket.prepare_insert(work); });
  verify(bucket.size() == 3 && order(bucket) == std::vector<std::uint64_t>{1, 2, 3},
         "zero/large payload altered explicit membership");
  verify(large.payload == above_double && maximum.payload == std::numeric_limits<std::uint64_t>::max(),
         "integer payload lost precision");
  bucket.prepare_erase(large, work);bucket.erase_prepaid(large);
  verify(row.contains(large) && row.size() == 3 && large.payload == above_double,
         "bucket removal changed row ownership or payload");
  rejects("storage_contract", [&] { bucket.prepare_erase(large, work); });
  for (auto* node : {&zero, &maximum}) { bucket.prepare_erase(*node, work);bucket.erase_prepaid(*node); }
  for (auto* node : {&zero, &large, &maximum}) { row.prepare_erase(*node, work);row.erase_prepaid(*node); }
  verify(order(bucket).empty() && order(row).empty(), "removed members remain in traversal");
  // Three actual nodes carry exact annotations here. This is not a claim of
  // allocating or measuring more than 2^53 physical runtime records.
}

void inverse_neighbors() {
  Bucket bucket(4);Node a(1, 0), b(2, 1), c(3, 2), d(4, 3);auto work = ample();
  for (auto* node : {&a, &b, &c, &d}) { bucket.prepare_insert(work);bucket.append_prepaid(*node); }
  const auto original = order(bucket);
  IndexWorkAllowance transaction(IndexWork{.structural_steps = 4,
      .link_actions = 2 * (Bucket::erase_actions + Bucket::insert_actions)});
  const auto neighbors_b = bucket.neighbors(b);
  bucket.prepare_erase(b, transaction);
  transaction.admit(IndexWork{.structural_steps = 1, .link_actions = Bucket::insert_actions});
  bucket.erase_prepaid(b);
  const auto neighbors_a = bucket.neighbors(a);
  bucket.prepare_erase(a, transaction);
  transaction.admit(IndexWork{.structural_steps = 1, .link_actions = Bucket::insert_actions});
  bucket.erase_prepaid(a);
  // Both inverses were reserved before their corresponding forward removals,
  // even when the original bucket was full. No new grant is needed for undo.
  verify(transaction.remaining() == IndexWork{}, "inverse reservation differs");
  bucket.insert_between_prepaid(a, neighbors_a.first, neighbors_a.second);
  bucket.insert_between_prepaid(b, neighbors_b.first, neighbors_b.second);
  verify(order(bucket) == original && transaction.remaining() == IndexWork{}, "reverse restoration changed original order");
  for (auto* node : {&d, &b, &a, &c}) { bucket.prepare_erase(*node, work);bucket.erase_prepaid(*node); }
}

void generated_tape() {
  Bucket bucket(32);std::map<std::uint64_t, std::unique_ptr<Node>> model;
  std::vector<std::uint64_t> expected;std::uint64_t random = 0x9cb836dea1c42f07ULL;
  for (std::size_t step = 0; step < 5000; ++step) {
    random ^= random << 13;random ^= random >> 7;random ^= random << 17;
    const auto key = random % 32;auto work = ample();
    if ((random & 256) != 0) {
      if (!model.contains(key)) {
        auto member = std::make_unique<Node>(key, random);
        bucket.prepare_insert(work);bucket.append_prepaid(*member);
        model.emplace(key, std::move(member));expected.push_back(key);
      }
    } else if (model.contains(key)) {
      bucket.prepare_erase(*model.at(key), work);bucket.erase_prepaid(*model.at(key));
      model.erase(key);std::erase(expected, key);
    }
    verify(order(bucket) == expected && bucket.size() == model.size(), "generated live membership/order mismatch");
  }
  auto work = ample();
  for (auto& [key, node] : model) { static_cast<void>(key);bucket.prepare_erase(*node, work);bucket.erase_prepaid(*node); }
  verify(order(bucket).empty(), "historical membership appears in empty traversal");
}
}  // namespace

int main() {
  boundaries_and_membership();inverse_neighbors();generated_tape();
  std::cout << "S04 live-list draft: exact membership, independent hooks, inverse neighbors and 5000 model operations passed\n";
}
