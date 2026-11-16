#pragma once

#include "hash_directory.hpp"
#include "live_list.hpp"
#include "crown/storage/layout.hpp"
#include <cstddef>
#include <utility>

namespace crown::storage::detail {

struct IndexedRow;
struct IndexedKey;
struct IndexedIndex;

// Parent pointers and hooks borrow; the row or a private prepared owner
// controls deletion. Hooks retain their actual surviving list owner.
struct IndexedMember {
  IndexedMember(IndexedRow& source_row, IndexedIndex& source_index,
                IndexedKey& source_key) noexcept
      : row(&source_row), index(&source_index), key(&source_key) {}
  ~IndexedMember();
  IndexedRow* row;
  IndexedIndex* index;
  IndexedKey* key;
  LiveListHook<IndexedMember> row_link;
  LiveListHook<IndexedMember> bucket_link;
};
using RowMembers = LiveList<IndexedMember, &IndexedMember::row_link>;
using BucketMembers = LiveList<IndexedMember, &IndexedMember::bucket_link>;

struct IndexedRow {
  IndexedRow(TupleId logical_id, std::size_t maximum_indices) noexcept
      : id(logical_id), members(maximum_indices) {}
  ~IndexedRow();
  TupleId id;
  ArenaHandle allocation{};  // Installed only after tuple-arena preparation.
  const Tuple* tuple = nullptr;
  HashDirectoryHook<IndexedRow> primary_link;
  HashDirectoryHook<IndexedRow> identity_link;
  RowMembers members;  // Owns linked member nodes; destruction is iterative.
};
using PrimaryDirectory = HashDirectory<IndexedRow, &IndexedRow::primary_link>;
using RowIdDirectory = HashDirectory<IndexedRow, &IndexedRow::identity_link>;

struct IndexedKey {
  IndexedKey(Tuple value, std::size_t maximum_rows) noexcept
      : tuple(std::move(value)), members(maximum_rows) {}
  ~IndexedKey();
  Tuple tuple;
  HashDirectoryHook<IndexedKey> lookup_link;
  LiveListHook<IndexedKey> live_link;
  std::size_t journal_references = 0;
  BucketMembers members;  // Borrows row-owned or privately staged nodes.
};
using KeyDirectory = HashDirectory<IndexedKey, &IndexedKey::lookup_link>;
using LiveKeys = LiveList<IndexedKey, &IndexedKey::live_link>;

struct IndexedIndex {
  IndexedIndex(IndexId logical_id, Projection program, std::size_t directory_slots,
               std::size_t maximum_keys) noexcept
      : id(logical_id), projection(std::move(program)), keys(directory_slots),
        live_keys(maximum_keys) {}
  ~IndexedIndex();
  IndexId id;
  Projection projection;
  HashDirectoryHook<IndexedIndex> identity_link;
  KeyDirectory keys;  // Owns every resident key, including private empty keys.
  LiveKeys live_keys; // Borrows only keys with public live membership.
};
using IndexIdDirectory = HashDirectory<IndexedIndex, &IndexedIndex::identity_link>;

inline IndexedMember::~IndexedMember() {
  // Use each hook's actual surviving owner. key/index pointers may already be
  // retired for a privately staged node whose bucket link was detached first.
  RowMembers::detach_prepaid(*this);
  BucketMembers::detach_prepaid(*this);
}

inline IndexedRow::~IndexedRow() {
  PrimaryDirectory::detach_prepaid(*this);
  RowIdDirectory::detach_prepaid(*this);
  while (auto* member = members.first()) delete member;
  // The table's arena owns tuple payloads; this never copies/frees a borrowed
  // Tuple or changes arena membership. Table publication handles that boundary.
}

inline IndexedKey::~IndexedKey() {
  KeyDirectory::detach_prepaid(*this);
  LiveKeys::detach_prepaid(*this);
  while (auto* member = members.first()) {
    if (member->row_link.owner != nullptr) {
      // Row-owned members are released and removed from both lists. No row or
      // neighboring key is recursively destroyed by a member destructor.
      delete member;
    } else {
      // A failed index build can still own this member through a unique_ptr.
      // Sever this borrow; its independent prepared owner will release it.
      members.erase_prepaid(*member);
    }
  }
}

inline IndexedIndex::~IndexedIndex() {
  IndexIdDirectory::detach_prepaid(*this);
  while (auto* key = keys.first_resident()) delete key;
}

}  // namespace crown::storage::detail
