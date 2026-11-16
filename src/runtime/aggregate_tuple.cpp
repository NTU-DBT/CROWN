#include "crown/runtime/aggregate.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <cstring>
#include <limits>
#include <memory>
#include <type_traits>

namespace crown::runtime::aggregate {
static_assert(std::is_trivially_destructible_v<Cell>);
static_assert(std::is_nothrow_copy_constructible_v<Cell>);

struct Tuple::Data {
  resource::MemoryAccount account;
  resource::MemoryBlock payload;
  std::size_t width;
  Data(resource::MemoryAccount value, resource::MemoryBlock block, std::size_t count) noexcept
      : account(std::move(value)), payload(std::move(block)), width(count) {}
};

Tuple Tuple::copy_of(const resource::MemoryAccount& account, std::span<const Cell> source,
    resource::MemoryPurpose purpose) {
  constexpr auto maximum = std::numeric_limits<std::size_t>::max();
  if (source.size() > maximum / sizeof(Cell))
    throw Error("aggregate_capacity", "SQL tuple cell storage overflows");
  auto bytes = source.size() * sizeof(Cell);
  for (const auto& cell : source) if (cell) {
    if (const auto* string = std::get_if<std::string_view>(&*cell)) {
      if (string->size() > maximum - bytes)
        throw Error("aggregate_capacity", "SQL tuple string storage overflows");
      bytes += string->size();
    }
  }
  resource::MemoryBlock payload;
  if (bytes) payload = account.allocate(bytes, alignof(Cell), purpose);
  auto* cells = static_cast<Cell*>(payload.data());
  auto* text = bytes ? reinterpret_cast<char*>(cells) + source.size() * sizeof(Cell) : nullptr;
  for (std::size_t i = 0; i < source.size(); ++i) {
    Cell owned = source[i];
    if (source[i]) if (const auto* string = std::get_if<std::string_view>(&*source[i])) {
      if (!string->empty()) std::memcpy(text, string->data(), string->size());
      owned = storage::ScalarView{std::string_view(text, string->size())};
      text += string->size();
    }
    std::construct_at(cells + i, owned);
  }
  // Cell copies cannot throw and own no child allocations. A failed Data
  // allocation simply releases this one payload block; no undo ledger is needed.
  return Tuple(resource::make_accounted_shared<Data>(account, purpose, account, std::move(payload), source.size()));
}

const Tuple::Data& Tuple::data() const {
  if (!data_) throw Error("invalid_aggregate_tuple", "SQL tuple handle is empty");
  return *data_;
}
std::size_t Tuple::size() const { return data().width; }
std::span<const Cell> Tuple::view() const & {
  const auto& value = data();
  return {static_cast<const Cell*>(value.payload.data()), value.width};
}
const resource::MemoryAccount& Tuple::account() const & { return data().account; }
bool Tuple::operator==(const Tuple& other) const {
  if (data_ == other.data_) return true;
  const auto left = view(), right = other.view();
  return std::equal(left.begin(), left.end(), right.begin(), right.end());
}
Row Tuple::export_values() const {
  Row result;
  result.reserve(size());
  for (const auto& cell : view())
    result.push_back(cell ? SqlValue{storage::export_scalar(*cell)} : std::nullopt);
  return result;
}
Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t epoch, frontend::AggregateProgram source)
    : sequence(epoch), program(std::move(source)),
      groups(resource::OwnerAllocator<GroupResult>(account, resource::MemoryPurpose::output_buffer,
          resource::MemoryAttribution{resource::MemoryOwnerKind::output, 0})) {}
}  // namespace crown::runtime::aggregate
