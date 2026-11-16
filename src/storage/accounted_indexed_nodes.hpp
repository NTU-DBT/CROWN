#pragma once

#include "hash_directory.hpp"
#include "live_list.hpp"
#include "accounted_pointer_array.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/resource/allocator.hpp"
#include <memory>

namespace crown::storage::detail {
// Each raw intrusive node carries its exact allocator identity. The stateless
// temporary deleter copies that identity before destruction/deallocation;
// publication transfers ownership to the real table hooks without a ticket.
template<class T> struct IndexedNodeDelete {
  void operator()(T* node) const noexcept {
    if (!node) return;
    auto allocator = node->allocator;std::destroy_at(node);allocator.deallocate(node, 1);
  }
};
template<class T> using IndexedNodeOwner = std::unique_ptr<T, IndexedNodeDelete<T>>;
template<class T, class... Args>
IndexedNodeOwner<T> make_indexed_node(const resource::MemoryAccount& account, resource::MemoryAttribution tag,
    resource::MemoryPurpose purpose, Args&&... args) {
  resource::MemoryAllocator<T> allocator(account, purpose, tag);auto* node = allocator.allocate(1);
  try { std::construct_at(node, allocator, std::forward<Args>(args)...); }
  catch (...) { allocator.deallocate(node, 1);throw; }
  return IndexedNodeOwner<T>(node);
}
template<class T> void destroy_indexed_node(T* node) noexcept { IndexedNodeDelete<T>{}(node); }
template<class T> void classify_indexed_node(T& node, resource::AllocationLifetime lifetime) noexcept {
  node.allocator.set_allocation_lifetime(&node, 1, lifetime);
}

struct AccountedIndexedRow;
struct AccountedIndexedKey;
struct AccountedIndexedIndex;
struct AccountedIndexedMember {
  resource::MemoryAllocator<AccountedIndexedMember> allocator;
  AccountedIndexedRow* row;
  AccountedIndexedIndex* index;
  AccountedIndexedKey* key;
  LiveListHook<AccountedIndexedMember> row_link, bucket_link;
  AccountedIndexedMember(resource::MemoryAllocator<AccountedIndexedMember> owner,
      AccountedIndexedRow& r, AccountedIndexedIndex& i, AccountedIndexedKey& k) noexcept
      : allocator(std::move(owner)), row(&r), index(&i), key(&k) {}
  ~AccountedIndexedMember();
};
using AccountedRowMembers = LiveList<AccountedIndexedMember, &AccountedIndexedMember::row_link, FixedIndexErrors>;
using AccountedBucketMembers = LiveList<AccountedIndexedMember, &AccountedIndexedMember::bucket_link, FixedIndexErrors>;

struct AccountedIndexedRow {
  resource::MemoryAllocator<AccountedIndexedRow> allocator;
  TupleId id;
  ArenaHandle allocation{};
  const AccountedTuple* tuple = nullptr;
  HashDirectoryHook<AccountedIndexedRow> primary_link, identity_link;
  AccountedRowMembers members;
  AccountedIndexedRow(resource::MemoryAllocator<AccountedIndexedRow> owner, TupleId logical, std::size_t maximum) noexcept
      : allocator(std::move(owner)), id(logical), members(maximum) {}
  ~AccountedIndexedRow();
};
using AccountedPrimaryDirectory = HashDirectory<AccountedIndexedRow, &AccountedIndexedRow::primary_link,
    resource::MemoryAllocator<AccountedIndexedRow*>, FixedIndexErrors, AccountedPointerArray<AccountedIndexedRow>>;
using AccountedRowIdDirectory = HashDirectory<AccountedIndexedRow, &AccountedIndexedRow::identity_link,
    resource::MemoryAllocator<AccountedIndexedRow*>, FixedIndexErrors, AccountedPointerArray<AccountedIndexedRow>>;

struct AccountedIndexedKey {
  resource::MemoryAllocator<AccountedIndexedKey> allocator;
  AccountedTuple tuple;
  HashDirectoryHook<AccountedIndexedKey> lookup_link;
  LiveListHook<AccountedIndexedKey> live_link;
  std::size_t journal_references = 0;
  AccountedBucketMembers members;
  AccountedIndexedKey(resource::MemoryAllocator<AccountedIndexedKey> owner, AccountedTuple value, std::size_t maximum) noexcept
      : allocator(std::move(owner)), tuple(std::move(value)), members(maximum) {}
  ~AccountedIndexedKey();
};
using AccountedKeyDirectory = HashDirectory<AccountedIndexedKey, &AccountedIndexedKey::lookup_link,
    resource::MemoryAllocator<AccountedIndexedKey*>, FixedIndexErrors, AccountedPointerArray<AccountedIndexedKey>>;
using AccountedLiveKeys = LiveList<AccountedIndexedKey, &AccountedIndexedKey::live_link, FixedIndexErrors>;

struct AccountedIndexedIndex {
  resource::MemoryAllocator<AccountedIndexedIndex> allocator;
  IndexId id;
  AccountedProjection projection;
  HashDirectoryHook<AccountedIndexedIndex> identity_link;
  AccountedKeyDirectory keys;
  AccountedLiveKeys live_keys;
  AccountedIndexedIndex(resource::MemoryAllocator<AccountedIndexedIndex> owner, IndexId logical,
      AccountedProjection program, std::size_t slots, std::size_t maximum) noexcept
      : allocator(std::move(owner)), id(logical), projection(std::move(program)),
        keys(slots, resource::MemoryAllocator<AccountedIndexedKey*>(allocator.account(), resource::MemoryPurpose::directory,
             allocator.attribution())), live_keys(maximum) {}
  ~AccountedIndexedIndex();
};
using AccountedIndexIdDirectory = HashDirectory<AccountedIndexedIndex, &AccountedIndexedIndex::identity_link,
    resource::MemoryAllocator<AccountedIndexedIndex*>, FixedIndexErrors, AccountedPointerArray<AccountedIndexedIndex>>;

inline AccountedIndexedMember::~AccountedIndexedMember() {
  AccountedRowMembers::detach_prepaid(*this);AccountedBucketMembers::detach_prepaid(*this);
}
inline AccountedIndexedRow::~AccountedIndexedRow() {
  AccountedPrimaryDirectory::detach_prepaid(*this);AccountedRowIdDirectory::detach_prepaid(*this);
  while (auto* member = members.first()) destroy_indexed_node(member);
}
inline AccountedIndexedKey::~AccountedIndexedKey() {
  AccountedKeyDirectory::detach_prepaid(*this);AccountedLiveKeys::detach_prepaid(*this);
  while (auto* member = members.first()) {
    if (member->row_link.owner) destroy_indexed_node(member);
    else members.erase_prepaid(*member);
  }
}
inline AccountedIndexedIndex::~AccountedIndexedIndex() {
  AccountedIndexIdDirectory::detach_prepaid(*this);
  while (auto* key = keys.first_resident()) destroy_indexed_node(key);
}
}
