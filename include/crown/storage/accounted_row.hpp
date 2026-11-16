#pragma once

// Compact S05 payload. The public Row is a borrowed input here.
// Internal retention must own AccountedRow and
// keep its allocation alive for every RowView/string view that escapes.
#include "crown/ir/model.hpp"
#include "crown/resource/memory.hpp"
#include <array>
#include <span>
#include <string_view>
#include <utility>
#include <variant>

namespace crown::storage {

// Decimal's entire bounded coefficient fits inline, including values too
// long for std::string's small-string buffer. No owning std::string is stored.
class InlineDecimal {
 public:
  static constexpr std::size_t text_capacity = 41;
  InlineDecimal() noexcept = default;
  [[nodiscard]] static InlineDecimal copy_of(const Decimal&) noexcept;
  [[nodiscard]] static InlineDecimal parse(std::string_view);
  // The returned coefficient view borrows this inline object.
  [[nodiscard]] DecimalParts parts() const noexcept {
    return {std::string_view(digits_.data(), digits_size_), scale_, negative_};
  }
  // Writes canonical bytes without a terminator. Too-small output is a
  // memory_contract failure before any write. text_capacity always suffices.
  [[nodiscard]] std::size_t render(std::span<char>) const;
  [[nodiscard]] bool operator==(const InlineDecimal&) const noexcept;
  [[nodiscard]] std::strong_ordering operator<=>(const InlineDecimal&) const noexcept;
 private:
  std::array<char, 38> digits_{'0'};
  std::uint8_t digits_size_ = 1;
  std::uint8_t scale_ = 0;
  bool negative_ = false;
};

// The alternative order deliberately matches crown::Value and ScalarType.
// Strings borrow bytes; the other alternatives are fully inline values.
using ScalarView = std::variant<std::int64_t, std::string_view, bool, Date, InlineDecimal>;

class AccountedRow;
class AccountedProjection;
class TupleValuesView;
class RowView {
 public:
  RowView() noexcept = default;
  // Cells and any referenced string bytes must outlive every use of the view.
  [[nodiscard]] static RowView borrow(std::span<const ScalarView> cells) noexcept { return {cells.data(),cells.size()}; }
  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] const ScalarView& operator[](std::size_t index) const noexcept { return data_[index]; }
  [[nodiscard]] const ScalarView& at(std::size_t) const;
  [[nodiscard]] std::span<const ScalarView> cells() const noexcept { return {data_, size_}; }
  [[nodiscard]] std::uint64_t hash() const noexcept;
  [[nodiscard]] bool operator==(RowView) const noexcept;
  [[nodiscard]] std::strong_ordering operator<=>(RowView) const noexcept;
 private:
  friend class AccountedRow;
  RowView(const ScalarView* data, std::size_t size) noexcept : data_(data), size_(size) {}
  const ScalarView* data_ = nullptr;
  std::size_t size_ = 0;
};

// Borrowed compatibility comparisons do not create an owning Row.
[[nodiscard]] bool operator==(RowView,const Row&);
[[nodiscard]] std::strong_ordering operator<=>(RowView,const Row&);
[[nodiscard]] ScalarView borrow_scalar(const Value&);
[[nodiscard]] ScalarType type_of(const ScalarView&);
[[nodiscard]] bool operator==(const ScalarView&,const Value&);
[[nodiscard]] std::strong_ordering operator<=>(const ScalarView&,const Value&);
// Explicit external/legacy exports; these standard values are not the
// internal retained representation and are outside the account until migrated.
[[nodiscard]] Value export_scalar(const ScalarView&);
[[nodiscard]] Row export_row(RowView);

// One real MemoryBlock contains the scalar descriptor array and every string
// byte. Its charge includes all framing/alignment through MemoryAccount.
// purpose=tuple_values covers this combined allocation; scalar byte lengths
// are logical payload lengths, not a second physical allocation charge.
// No implicit copy can mint a grant or hide a deep allocation. clone explicitly
// chooses the destination account, which must be the query's same account
// during maintenance/rebuild/undo. Caller exports need a separate boundary.
class AccountedRow {
 public:
  AccountedRow() noexcept = default;
  AccountedRow(const AccountedRow&) = delete;
  AccountedRow& operator=(const AccountedRow&) = delete;
  AccountedRow(AccountedRow&&) noexcept;
  AccountedRow& operator=(AccountedRow&&) noexcept;
  [[nodiscard]] static AccountedRow copy_of(const resource::MemoryAccount&, const Row&, resource::MemoryAttribution = {});
  [[nodiscard]] static AccountedRow copy_of(const resource::MemoryAccount&, RowView, resource::MemoryAttribution = {});
  [[nodiscard]] static AccountedRow copy_view(const resource::MemoryAccount&,TupleValuesView,resource::MemoryAttribution = {});
  // Ordered borrowed fields are gathered directly into the one funded block.
  // No temporary owning Row or descriptor vector is needed.
  [[nodiscard]] static AccountedRow project(const resource::MemoryAccount&, RowView,
      std::span<const FieldId>, resource::MemoryAttribution = {});
  // Exact real request for a stable caller row. Preflight allocates nothing;
  // copying uses the same payload sizing implementation and one funded block.
  // This reports a request; it does not reserve memory or extend input lifetime.
  [[nodiscard]] static resource::MemoryUsage allocation_usage_for(const Row&);
  [[nodiscard]] static resource::MemoryUsage allocation_usage_for(TupleValuesView);
  [[nodiscard]] AccountedRow clone(const resource::MemoryAccount& account) const {
    return copy_of(account, view(), block_ ? block_.attribution() : resource::MemoryAttribution{});
  }
  [[nodiscard]] AccountedRow clone(const resource::MemoryAccount& account, resource::MemoryAttribution attribution) const {
    return copy_of(account, view(), attribution);
  }
  [[nodiscard]] RowView view() const & noexcept;
  RowView view() const && = delete;
  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] std::size_t stored_payload_bytes() const noexcept { return block_.size(); }
  [[nodiscard]] resource::MemoryUsage memory_usage() const noexcept { return block_.usage(); }
  [[nodiscard]] resource::MemoryStatistics account_statistics() const { return block_.account_statistics(); }
  [[nodiscard]] resource::AllocationLifetime lifetime() const { return block_.lifetime(); }
  [[nodiscard]] resource::MemoryAttribution attribution() const { return block_.attribution(); }
  void set_lifetime(resource::AllocationLifetime lifetime) const { block_.set_lifetime(lifetime); }
 private:
  friend class AccountedProjection;
  AccountedRow(resource::MemoryBlock block, std::size_t size) noexcept
      : block_(std::move(block)), size_(size) {}
  resource::MemoryBlock block_;
  std::size_t size_ = 0;
};

}  // namespace crown::storage
