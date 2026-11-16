#include "hash_directory.hpp"

#include <algorithm>
#include <array>
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
using crown::storage::detail::HashDirectory;
using crown::storage::detail::HashDirectoryHook;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template <class Function>
void rejects(std::string_view code, Function&& function) {
  bool rejected = false;
  try { function(); }
  catch (const Error& error) { verify(error.code() == code, "wrong error code"); rejected = true; }
  verify(rejected, "operation unexpectedly succeeded");
}
IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000});
}
struct Node {
  explicit Node(std::uint64_t value) : key(value) {}
  std::uint64_t key;
  HashDirectoryHook<Node> primary;
  HashDirectoryHook<Node> identity;
};
using Directory = HashDirectory<Node, &Node::primary>;
using IdentityDirectory = HashDirectory<Node, &Node::identity>;
static_assert(!std::is_copy_constructible_v<Node> && !std::is_move_constructible_v<Node>);
static_assert(!std::is_copy_constructible_v<Directory> && !std::is_move_constructible_v<Directory>);

Node* find(Directory& directory, std::uint64_t hash, std::uint64_t key,
           IndexWorkAllowance& allowance, std::size_t* comparisons = nullptr) {
  return directory.find(hash, [&](const Node& node, IndexWorkAllowance& grant) {
    grant.admit(IndexWork{.scalar_fields = 1});
    if (comparisons != nullptr) ++*comparisons;
    return node.key == key;
  }, allowance);
}
void insert(Directory& directory, Node& node, std::uint64_t hash,
             IndexWorkAllowance& allowance) {
  auto growth = directory.prepare_growth(directory.size() + 1, allowance);
  allowance.admit(IndexWork{.link_actions = Directory::link_actions});
  directory.publish_growth(std::move(growth));
  directory.link_prepaid(node, hash);
}
std::vector<std::uint64_t> live_order(const Directory& directory) {
  std::vector<std::uint64_t> result;
  for (auto* row = directory.first_resident(); row != nullptr; row = Directory::next_resident(*row)) {
    verify(result.size() < directory.size(), "cyclic resident list");
    result.push_back(row->key);
  }
  verify(result.size() == directory.size(), "resident list cardinality differs");
  if (result.empty()) verify(directory.last_resident() == nullptr, "empty list retains tail");
  else verify(directory.last_resident()->key == result.back(), "resident tail differs");
  return result;
}

void allowances() {
  IndexWorkAllowance grant(IndexWork{2, 3, 4, 5, 6});
  const auto before = grant.remaining();
  rejects("storage_work_limit", [&] { grant.admit(IndexWork{1, 1, 1, 6, 1}); });
  verify(grant.remaining() == before, "failed aggregate admission consumed earlier domains");
  grant.admit(before);
  verify(grant.remaining() == IndexWork{}, "exact boundary did not consume allowance");
  rejects("storage_work_limit", [&] { grant.admit(IndexWork{.structural_steps = 1}); });
}

void empty_and_capacity() {
  Directory empty(0);
  IndexWorkAllowance zero(IndexWork{});
  bool compared = false;
  rejects("storage_work_limit", [&] {
    static_cast<void>(empty.find(0, [](const Node&, IndexWorkAllowance&) { return true; }, zero));
  });
  IndexWorkAllowance empty_probe(IndexWork{.structural_steps = 1});
  verify(empty.find(0, [&](const Node&, IndexWorkAllowance&) { compared = true; return true; }, empty_probe) == nullptr,
         "empty lookup found a row");
  verify(!compared && empty_probe.remaining() == IndexWork{}, "empty lookup skipped startup admission");
  IndexWorkAllowance empty_growth(IndexWork{.structural_steps = 1});
  auto none = empty.prepare_growth(0, empty_growth);
  verify(none.active() && !none.changes_capacity() && none.new_capacity() == 0, "empty growth token differs");
  empty.publish_growth(std::move(none));
  verify(!none.active() && none.new_capacity() == 0, "consumed growth token exposes old capacity");
  auto room = ample();
  rejects("storage_capacity", [&] { static_cast<void>(empty.prepare_growth(1, room)); });

  Directory capped(10);  // Eight is allowed; the required sixteen is not.
  auto work = ample();
  std::array<std::unique_ptr<Node>, 6> rows;
  for (std::size_t i = 0; i < rows.size(); ++i) {
    rows[i] = std::make_unique<Node>(static_cast<std::uint64_t>(i));
    insert(capped, *rows[i], 0, work);
  }
  const auto before = live_order(capped);
  rejects("storage_capacity", [&] { static_cast<void>(capped.prepare_growth(7, work)); });
  rejects("storage_capacity", [&] { static_cast<void>(capped.prepare_growth(std::numeric_limits<std::size_t>::max(), work)); });
  verify(capped.capacity() == 8 && live_order(capped) == before, "capacity rejection changed membership");
  for (auto& row : rows) capped.unlink_prepaid(*row);
}

void collisions_and_growth() {
  Directory directory(64);
  auto work = ample();
  std::array<std::unique_ptr<Node>, 7> rows;
  for (std::size_t i = 0; i < 6; ++i) {
    rows[i] = std::make_unique<Node>(static_cast<std::uint64_t>(i));
    insert(directory, *rows[i], 73, work);  // Distinct keys, identical full hashes.
  }
  std::size_t comparisons = 0;
  verify(find(directory, 73, 0, work, &comparisons) == rows[0].get() && comparisons == 6,
         "full-hash collision did not compare the entire exact chain");
  verify(find(directory, 73, 19, work) == nullptr, "full-hash collision invented equality");
  const auto before = live_order(directory);
  {
    auto abandoned = directory.prepare_growth(7, work);
    verify(abandoned.new_capacity() == 16 && directory.capacity() == 8, "growth published during preparation");
  }
  verify(directory.capacity() == 8 && live_order(directory) == before, "abandoned growth changed directory");
  rejects("storage_capacity", [&] { static_cast<void>(directory.prepare_growth(7, work, 7)); });
  {
    auto aggregate_exact = directory.prepare_growth(7, work, 8);
    verify(aggregate_exact.new_capacity() == 16 && directory.capacity() == 8,
           "aggregate exact capacity published before commit");
  }
  IndexWorkAllowance short_grant(IndexWork{7, 0, 0, 15, 30});
  auto after_startup = short_grant.remaining();--after_startup.structural_steps;
  rejects("storage_work_limit", [&] { static_cast<void>(directory.prepare_growth(7, short_grant)); });
  verify(short_grant.remaining() == after_startup && directory.capacity() == 8, "failed growth reservation changed earlier domains");
  IndexWorkAllowance exact_grant(IndexWork{7, 0, 0, 16, 30});
  auto growth = directory.prepare_growth(7, exact_grant);
  verify(exact_grant.remaining() == IndexWork{}, "growth exact work boundary differs");
  directory.publish_growth(std::move(growth));
  verify(directory.capacity() == 16 && live_order(directory) == before && !growth.active(), "rehash changed live order");
  rows[6] = std::make_unique<Node>(6);
  work.admit(IndexWork{.link_actions = Directory::link_actions});
  directory.link_prepaid(*rows[6], 73);
  for (const auto i : {3, 6, 0, 5, 1, 4, 2}) {
    verify(find(directory, 73, static_cast<std::uint64_t>(i), work) == rows[static_cast<std::size_t>(i)].get(),
           "known node lookup failed after rehash/unlink");
    directory.unlink_prepaid(*rows[static_cast<std::size_t>(i)]);
  }
  verify(directory.size() == 0 && directory.capacity() == 16 && live_order(directory).empty(), "retained empty capacity has live records");

  // Same masked bucket, different full hashes: equality is never consulted for
  // a hash mismatch, even though every resident chain element is visited.
  Node one(1), two(2);
  insert(directory, one, 1, work);insert(directory, two, 17, work);
  comparisons = 0;
  verify(find(directory, 1, 1, work, &comparisons) == &one && comparisons == 1,
         "bucket collision bypassed full-hash filtering");
  directory.unlink_prepaid(two);directory.unlink_prepaid(one);
}

void independent_hooks() {
  Directory primary(8);IdentityDirectory identity(8);Node node(23);auto work = ample();
  insert(primary, node, 0, work);
  auto growth = identity.prepare_growth(1, work);identity.publish_growth(std::move(growth));
  work.admit(IndexWork{.link_actions = IdentityDirectory::link_actions});identity.link_prepaid(node, 23);
  primary.unlink_prepaid(node);
  verify(identity.find(23, [](const Node& row, IndexWorkAllowance& grant) {
    grant.admit(IndexWork{.scalar_fields = 1});return row.key == 23;
  }, work) == &node, "unlinking primary damaged independent ID membership");
  identity.unlink_prepaid(node);
}

void restored_neighbors() {
  Directory directory(64);auto work = ample();Node first(1), middle(2), last(3);
  insert(directory, first, 0, work);insert(directory, middle, 0, work);insert(directory, last, 0, work);
  const auto order = live_order(directory);
  IndexWorkAllowance transaction(IndexWork{100, 0, 0, 100, 100});
  // One aggregate allowance reserves both forward removals and their inverse
  // before any tentative publication. Rehash uses that same remaining grant.
  transaction.admit(IndexWork{.structural_steps = 2,
      .link_actions = 2 * (Directory::unlink_actions + Directory::link_actions)});
  directory.unlink_prepaid(middle);directory.unlink_prepaid(first);
  auto growth = directory.prepare_growth(12, transaction);
  transaction.admit(transaction.remaining());
  directory.publish_growth(std::move(growth));
  directory.link_between_prepaid(first, 0, nullptr, &last);
  directory.link_between_prepaid(middle, 0, &first, &last);
  verify(live_order(directory) == order && transaction.remaining() == IndexWork{}, "neighbor undo after growth changed original order");
  directory.unlink_prepaid(middle);directory.unlink_prepaid(last);directory.unlink_prepaid(first);
}

void generated_tape() {
  Directory directory(64);
  std::map<std::uint64_t, std::unique_ptr<Node>> model;
  std::vector<std::uint64_t> insertion_order;
  std::uint64_t random = 0xd63bd784292b1c75ULL;
  for (std::size_t step = 0; step < 5000; ++step) {
    random ^= random << 13;random ^= random >> 7;random ^= random << 17;
    const auto key = random % 32;auto work = ample();
    if ((random & 256) != 0) {
      if (!model.contains(key)) {
        auto node = std::make_unique<Node>(key);
        insert(directory, *node, 7, work);
        model.emplace(key, std::move(node));insertion_order.push_back(key);
      }
    } else if (model.contains(key)) {
      directory.unlink_prepaid(*model.at(key));model.erase(key);
      std::erase(insertion_order, key);
    }
    verify(live_order(directory) == insertion_order && directory.size() == model.size(), "generated tape live membership/order mismatch");
    for (std::uint64_t probe = 0; probe < 33; ++probe) {
      const auto expected = model.find(probe);
      auto* actual = find(directory, 7, probe, work);
      verify(actual == (expected == model.end() ? nullptr : expected->second.get()), "generated exact collision lookup mismatch");
    }
  }
  for (auto& [key, node] : model) { static_cast<void>(key);directory.unlink_prepaid(*node); }
  verify(directory.capacity() >= 32 && directory.size() == 0 && directory.first_resident() == nullptr,
         "empty traversal depends on historical capacity");
  Node lone(99);auto work = ample();insert(directory, lone, 7, work);
  verify(live_order(directory) == std::vector<std::uint64_t>{99}, "one-row high-capacity traversal visited empty slots");
  directory.unlink_prepaid(lone);
}
}  // namespace

int main() {
  allowances();empty_and_capacity();collisions_and_growth();independent_hooks();restored_neighbors();generated_tape();
  std::cout << "S04 directory draft: exact collisions, finite growth, live links and 5000 model operations passed\n";
}
