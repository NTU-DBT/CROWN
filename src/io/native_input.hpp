#pragma once

#include "crown/io/input_progress.hpp"
#include "crown/io/ingest.hpp"
#include "crown/io/input_view.hpp"
#include "crown/resource/allocator.hpp"
#include "crown/resource/text.hpp"
#include <vector>

namespace crown::io::input_detail {
template<class T> using Vector=std::vector<T,resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account,resource::MemoryPurpose::scratch,memory_owner);
}
class Buffer {
  // Owns native scratch capacity; view() borrows it and clear() keeps its charge.
 public:
  explicit Buffer(const resource::MemoryAccount& account):bytes_(allocator<char>(account)) {}
  [[nodiscard]] std::string_view view() const noexcept {return {bytes_.empty()?"":bytes_.data(),bytes_.size()};}
  [[nodiscard]] std::size_t size() const noexcept {return bytes_.size();}
  void append(std::string_view value) {bytes_.insert(bytes_.end(),value.begin(),value.end());}
  void push_back(char value) {bytes_.push_back(value);}
  void reserve(std::size_t size) {bytes_.reserve(size);}
  void clear() noexcept {bytes_.clear();}
 private:
  Vector<char> bytes_;
};
struct Decoded {
  storage::AccountedRow row;
  resource::AccountedText source;
  InputEventView event;
};
[[nodiscard]] Decoded decode_json(const resource::MemoryAccount&,std::string_view,const CatalogSource&,const InputLimits&,std::string_view);
[[nodiscard]] Decoded decode_binary(const resource::MemoryAccount&,std::string_view,const CatalogSource&,const InputLimits&,std::string_view);
[[nodiscard]] resource::AccountedText catalog_fingerprint(const resource::MemoryAccount&,const CatalogSource&,bool admitted);
[[nodiscard]] std::array<char,64> catalog_digest(const resource::MemoryAccount&,const Catalog&,bool admitted);
[[nodiscard]] std::array<char,64> catalog_digest(const resource::MemoryAccount&,const program::Catalog&,bool admitted);
} // namespace crown::io::input_detail
