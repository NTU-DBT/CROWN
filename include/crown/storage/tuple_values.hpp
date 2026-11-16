#pragma once

#include "crown/storage/accounted_row.hpp"
#include <iterator>
#include <memory>
#include <optional>
#include <variant>

namespace crown::storage {
namespace detail {struct TuplePayload;}
class Tuple;

// Read-only public values. A tuple's view retains its immutable payload without
// copying strings or admitting another allocation. Explicit borrow() inputs
// instead require their source row/cells to remain alive. ScalarView string
// bytes remain borrowed from this view's owner; export_row() is the owning DTO
// boundary. No implicit Row conversion or standard-row mirror exists.
class TupleValuesView {
 public:
  class const_iterator;
  TupleValuesView() noexcept=default;
  [[nodiscard]] static TupleValuesView borrow(const Row& row) noexcept{return TupleValuesView(&row);}
  [[nodiscard]] static TupleValuesView borrow(RowView row) noexcept{return TupleValuesView(row);}
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] bool empty() const noexcept{return size()==0;}
  // Element access returns an inline scalar, not an owning string. Keep an
  // owning tuple/view (or the borrowed source) alive while using its string_view.
  [[nodiscard]] ScalarView operator[](std::size_t) const;
  [[nodiscard]] ScalarView at(std::size_t) const;
  // front/back use at(): empty views reject before a cell is dereferenced.
  [[nodiscard]] ScalarView front() const{return at(0);}
  [[nodiscard]] ScalarView back() const{return at(size()-1);}
  [[nodiscard]] const_iterator begin() const noexcept;
  [[nodiscard]] const_iterator end() const noexcept;
  [[nodiscard]] std::uint64_t hash() const;
  [[nodiscard]] bool operator==(const TupleValuesView&) const;
  [[nodiscard]] std::strong_ordering operator<=>(const TupleValuesView&) const;
  [[nodiscard]] bool operator==(const Row&) const;
  [[nodiscard]] std::strong_ordering operator<=>(const Row&) const;
  [[nodiscard]] bool operator==(RowView) const;
  [[nodiscard]] std::strong_ordering operator<=>(RowView) const;
  // Borrowed adapters transfer no ownership. Tuple-derived views retain their
  // payload; explicit borrow() views still require caller-owned rows/cells.
  [[nodiscard]] const Row* legacy_row() const noexcept;
  [[nodiscard]] std::optional<RowView> native_view() const noexcept;
 private:
  friend class Tuple;
  explicit TupleValuesView(const Row* row) noexcept:source_(row) {}
  explicit TupleValuesView(RowView row) noexcept:source_(row) {}
  explicit TupleValuesView(std::shared_ptr<const detail::TuplePayload> owner) noexcept:source_(std::move(owner)) {}
  [[nodiscard]] const void* identity() const noexcept;
  std::variant<const Row*,RowView,std::shared_ptr<const detail::TuplePayload>> source_{static_cast<const Row*>(nullptr)};
};

class TupleValuesView::const_iterator {
 public:
  using value_type=ScalarView;
  using difference_type=std::ptrdiff_t;
  using iterator_category=std::forward_iterator_tag;
  using reference=ScalarView;
  const_iterator() noexcept=default;
  reference operator*() const{return values_[position_];}
  const_iterator& operator++() noexcept{++position_;return *this;}
  const_iterator operator++(int) noexcept{auto old=*this;++*this;return old;}
  bool operator==(const const_iterator& other) const noexcept {
    return position_==other.position_ && values_.identity()==other.values_.identity();
  }
 private:
  friend class TupleValuesView;
  const_iterator(TupleValuesView values,std::size_t position) noexcept:values_(std::move(values)),position_(position) {}
  TupleValuesView values_;
  std::size_t position_=0;
};

[[nodiscard]] Row export_row(TupleValuesView);
[[nodiscard]] inline std::uint64_t row_hash(TupleValuesView values){return values.hash();}
} // namespace crown::storage
