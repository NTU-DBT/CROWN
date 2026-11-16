#include "crown/storage/tuple_values.hpp"
#include "tuple_payload.hpp"
#include <algorithm>
#include <stdexcept>

namespace crown::storage {
const Row* TupleValuesView::legacy_row() const noexcept {
  if(const auto* row=std::get_if<const Row*>(&source_))return *row;
  if(const auto* owner=std::get_if<std::shared_ptr<const detail::TuplePayload>>(&source_))
    return *owner?(*owner)->legacy:nullptr;
  return nullptr;
}
std::optional<RowView> TupleValuesView::native_view() const noexcept {
  if(const auto* row=std::get_if<RowView>(&source_))return *row;
  if(const auto* owner=std::get_if<std::shared_ptr<const detail::TuplePayload>>(&source_))
    if(*owner && !(*owner)->legacy)return (*owner)->native;
  return {};
}
std::size_t TupleValuesView::size() const noexcept {
  if(const auto* row=legacy_row())return row->size();
  const auto row=native_view();return row?row->size():0;
}
ScalarView TupleValuesView::operator[](std::size_t position) const {
  if(const auto* row=legacy_row())return borrow_scalar((*row)[position]);
  return (*native_view())[position];
}
ScalarView TupleValuesView::at(std::size_t position) const {
  if(position>=size())throw std::out_of_range("tuple value field is out of range");
  return (*this)[position];
}
const void* TupleValuesView::identity() const noexcept {
  if(const auto* row=legacy_row())return row;
  const auto row=native_view();return row?row->cells().data():nullptr;
}
TupleValuesView::const_iterator TupleValuesView::begin() const noexcept{return const_iterator(*this,0);}
TupleValuesView::const_iterator TupleValuesView::end() const noexcept{return const_iterator(*this,size());}
std::uint64_t TupleValuesView::hash() const {
  if(const auto* row=legacy_row())return crown::row_hash(*row);
  const auto row=native_view();return row?row->hash():RowView{}.hash();
}
std::strong_ordering TupleValuesView::operator<=>(const TupleValuesView& other) const {
  for(std::size_t i=0;i<std::min(size(),other.size());++i) {
    const auto order=(*this)[i]<=>other[i];if(order!=0)return order;
  }
  return size()<=>other.size();
}
bool TupleValuesView::operator==(const TupleValuesView& other) const{
  const auto count=size();
  if(count!=other.size())return false;
  for(std::size_t i=0;i<count;++i)
    if(((*this)[i]<=>other[i])!=0)return false;
  return true;
}
std::strong_ordering TupleValuesView::operator<=>(const Row& other) const{return *this<=>borrow(other);}
bool TupleValuesView::operator==(const Row& other) const{return *this==borrow(other);}
std::strong_ordering TupleValuesView::operator<=>(RowView other) const{return *this<=>borrow(other);}
bool TupleValuesView::operator==(RowView other) const{return *this==borrow(other);}
Row export_row(TupleValuesView values) {
  if(const auto* row=values.legacy_row())return *row;
  Row result;result.reserve(values.size());
  for(const auto& value:values)result.push_back(export_scalar(value));
  return result;
}
} // namespace crown::storage
