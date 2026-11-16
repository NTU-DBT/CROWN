#include "indexed_nodes.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

using namespace crown;
using namespace crown::storage;
namespace detail = crown::storage::detail;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000});
}
static_assert(!std::is_copy_constructible_v<detail::IndexedRow> && !std::is_move_constructible_v<detail::IndexedRow>);
static_assert(!std::is_copy_constructible_v<detail::IndexedKey> && !std::is_move_constructible_v<detail::IndexedKey>);
static_assert(!std::is_copy_constructible_v<detail::IndexedMember> && !std::is_move_constructible_v<detail::IndexedMember>);
static_assert(!std::is_copy_constructible_v<detail::IndexedIndex> && !std::is_move_constructible_v<detail::IndexedIndex>);
static_assert(std::is_nothrow_destructible_v<detail::IndexedRow> && std::is_nothrow_destructible_v<detail::IndexedKey>);
static_assert(std::is_nothrow_destructible_v<detail::IndexedMember> && std::is_nothrow_destructible_v<detail::IndexedIndex>);

struct Fixture {
  TupleLayout row_layout{LayoutId{1}, {{ScalarType::int64}}};
  TupleLayout key_layout{LayoutId{2}, {{ScalarType::int64}}};
  Projection projection{row_layout, key_layout, {FieldId{0}}};
  detail::PrimaryDirectory primary{4096};
  detail::RowIdDirectory rows{4096};
  detail::IndexIdDirectory indices{64};
  IndexWorkAllowance work = ample();

  std::unique_ptr<detail::IndexedIndex> make_index() {
    auto index = std::make_unique<detail::IndexedIndex>(IndexId{1}, projection, 4096, 2048);
    auto growth = indices.prepare_growth(1, work);indices.publish_growth(std::move(growth));
    work.admit(IndexWork{.link_actions = detail::IndexIdDirectory::link_actions});
    indices.link_prepaid(*index, 1);return index;
  }
  std::unique_ptr<detail::IndexedRow> make_row(std::uint64_t id) {
    auto row = std::make_unique<detail::IndexedRow>(TupleId{id}, 2);
    auto primary_growth = primary.prepare_growth(primary.size() + 1, work);
    auto id_growth = rows.prepare_growth(rows.size() + 1, work);
    work.admit(IndexWork{.link_actions = detail::PrimaryDirectory::link_actions + detail::RowIdDirectory::link_actions});
    primary.publish_growth(std::move(primary_growth));rows.publish_growth(std::move(id_growth));
    primary.link_prepaid(*row, 0);rows.link_prepaid(*row, id);return row;
  }
  detail::IndexedKey* add_key(detail::IndexedIndex& index, std::int64_t value) {
    auto key = std::make_unique<detail::IndexedKey>(key_layout.tuple(Row{value}), 2048);
    auto growth = index.keys.prepare_growth(index.keys.size() + 1, work);
    index.live_keys.prepare_insert(work);
    work.admit(IndexWork{.link_actions = detail::KeyDirectory::link_actions});
    index.keys.publish_growth(std::move(growth));index.keys.link_prepaid(*key, key->tuple.hash());
    index.live_keys.append_prepaid(*key);return key.release();
  }
  void add_member(detail::IndexedRow& row, detail::IndexedIndex& index, detail::IndexedKey& key) {
    auto member = std::make_unique<detail::IndexedMember>(row, index, key);
    row.members.prepare_insert(work);key.members.prepare_insert(work);
    row.members.append_prepaid(*member);key.members.append_prepaid(*member);
    static_cast<void>(member.release());  // One actual owning row, one borrowed bucket.
  }
};

void row_and_index_destruction() {
  Fixture f;auto index = f.make_index();auto first = f.make_row(1);auto second = f.make_row(2);
  auto* key = f.add_key(*index, 7);f.add_member(*first, *index, *key);f.add_member(*second, *index, *key);
  verify(key->members.size() == 2 && first->members.size() == 1 && second->members.size() == 1, "initial node membership differs");
  // Automatic detachment must use current directory links after a rehash.
  {
    auto primary_growth = f.primary.prepare_growth(100, f.work);f.primary.publish_growth(std::move(primary_growth));
    auto id_growth = f.rows.prepare_growth(100, f.work);f.rows.publish_growth(std::move(id_growth));
  } // Obsolete arrays are freed before the following node detachment.
  first.reset();
  verify(f.primary.size() == 1 && f.rows.size() == 1 && key->members.size() == 1 && second->members.size() == 1,
         "row destruction left directory/bucket references");
  index.reset();
  verify(f.indices.size() == 0 && second->members.size() == 0 && f.rows.size() == 1,
         "index destruction did not detach row-owned members");
  second.reset();
  verify(f.primary.size() == 0 && f.rows.size() == 0, "last row remains resident");
}

void prepared_member_ownership() {
  Fixture f;auto index = f.make_index();auto row = f.make_row(1);
  auto* key = f.add_key(*index, 9);
  auto prepared = std::make_unique<detail::IndexedMember>(*row, *index, *key);
  key->members.prepare_insert(f.work);key->members.append_prepaid(*prepared);
  verify(row->members.size() == 0 && key->members.size() == 1, "private preparation changed row membership");
  index.reset();
  verify(prepared->row_link.owner == nullptr && prepared->bucket_link.owner == nullptr && row->members.size() == 0,
         "index teardown adopted/deleted a privately owned member");
  prepared.reset(); // Its key/index pointers are expired; detached hooks avoid dereferencing them.
  row.reset();
  verify(f.indices.size() == 0 && f.primary.size() == 0 && f.rows.size() == 0, "private teardown leaked membership");

  auto next_index = f.make_index();auto next_row = f.make_row(2);auto* next_key = f.add_key(*next_index, 11);
  auto next_prepared = std::make_unique<detail::IndexedMember>(*next_row, *next_index, *next_key);
  next_key->members.prepare_insert(f.work);next_key->members.append_prepaid(*next_prepared);
  next_prepared.reset();
  verify(next_key->members.size() == 0 && next_row->members.size() == 0, "prepared member teardown left a borrowed bucket link");
}

void iterative_large_bucket() {
  Fixture f;auto index = f.make_index();auto* key = f.add_key(*index, 3);
  std::vector<std::unique_ptr<detail::IndexedRow>> rows;rows.reserve(1024);
  for (std::uint64_t id = 1; id <= 1024; ++id) {
    auto row = f.make_row(id);f.add_member(*row, *index, *key);rows.push_back(std::move(row));
  }
  verify(key->members.size() == 1024 && f.primary.size() == 1024, "large bucket cardinality differs");
  index.reset();
  for (const auto& row : rows) verify(row->members.size() == 0, "index teardown left a member owned by a row");
  rows.clear();
  verify(f.primary.size() == 0 && f.rows.size() == 0 && f.indices.size() == 0,
         "iterative bucket teardown left resident nodes");
}
}  // namespace

int main() {
  row_and_index_destruction();prepared_member_ownership();iterative_large_bucket();
  std::cout << "S04 node draft: row/index teardown, prepared ownership and iterative 1024-member cleanup passed\n";
}
