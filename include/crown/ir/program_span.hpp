#pragma once

#include "crown/storage/index_failure.hpp"
#include <algorithm>
#include <span>

namespace crown::program {

// Borrowed immutable range. Its backing metadata must outlive every view and
// iterator; this descriptor retains no owner.
template<class T> class Span {
 public:
  using value_type=T;
  using iterator=typename std::span<const T>::iterator;
  Span() noexcept=default;
  Span(const T* data,std::size_t size) noexcept:data_(data,size) {}
  Span(std::span<const T> data) noexcept:data_(data) {}
  [[nodiscard]] const T* data() const noexcept {return data_.data();}
  [[nodiscard]] std::size_t size() const noexcept {return data_.size();}
  [[nodiscard]] bool empty() const noexcept {return data_.empty();}
  [[nodiscard]] iterator begin() const noexcept {return data_.begin();}
  [[nodiscard]] iterator end() const noexcept {return data_.end();}
  [[nodiscard]] auto rbegin() const noexcept {return data_.rbegin();}
  [[nodiscard]] auto rend() const noexcept {return data_.rend();}
  // Subscript/front/back require valid indices; at() is the checked boundary.
  [[nodiscard]] const T& operator[](std::size_t i) const noexcept {return data_[i];}
  [[nodiscard]] const T& at(std::size_t i) const {
    if(i>=size())throw storage::IndexFailure(storage::IndexFault::contract);
    return data_[i];
  }
  [[nodiscard]] const T& front() const noexcept {return data_.front();}
  [[nodiscard]] const T& back() const noexcept {return data_.back();}
  [[nodiscard]] operator std::span<const T>() const noexcept {return data_;}
 private:
  std::span<const T> data_;
};

// Builder/caller supplies sorted storage; this wrapper neither sorts nor
// enforces uniqueness, and comparisons retain their actual T-specific costs.
template<class T> class Set:public Span<T> {
 public:
  using Span<T>::Span;
  [[nodiscard]] typename Span<T>::iterator find(const T& value) const {
    const auto it=std::lower_bound(this->begin(),this->end(),value);
    return it!=this->end() && *it==value?it:this->end();
  }
  [[nodiscard]] bool contains(const T& value) const {return find(value)!=this->end();}
};
} // namespace crown::program
