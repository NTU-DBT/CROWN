#pragma once

#include "crown/resource/text.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <map>
#include <string>

namespace crown::io {
struct InputProgress;
namespace input_detail {
inline constexpr resource::MemoryAttribution memory_owner{resource::MemoryOwnerKind::session,2};
}
// Read-only source positions with native object/node/key ownership. Copies are
// value snapshots funded by the source's original account; moves allocate none.
class InputPositions {
  struct Data;
  using Map=std::map<resource::AccountedText,std::uint64_t,resource::AccountedTextLess,
      resource::MemoryAllocator<std::pair<const resource::AccountedText,std::uint64_t>>>;
 public:
  using const_iterator=Map::const_iterator;
  // A preparation belongs to its original live map. It is not a foreign-safe
  // token; publication requires no conflicting change to that entry/name.
  class Prepared {
   public:
    Prepared() noexcept=default;
    Prepared(Prepared&&) noexcept=default;
    Prepared& operator=(Prepared&&) noexcept=default;
    Prepared(const Prepared&)=delete;
    Prepared& operator=(const Prepared&)=delete;
   private:
    friend class InputPositions;
    Map::iterator existing_;
    Map::node_type node_;
    std::uint64_t offset_=0;
    bool existing=false;
  };
  InputPositions() noexcept;
  explicit InputPositions(const resource::MemoryAccount&);
  ~InputPositions();
  InputPositions(const InputPositions&);
  InputPositions& operator=(const InputPositions&);
  InputPositions(InputPositions&&) noexcept;
  InputPositions& operator=(InputPositions&&) noexcept;
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] bool empty() const noexcept {return size()==0;}
  [[nodiscard]] const_iterator begin() const noexcept;
  [[nodiscard]] const_iterator end() const noexcept;
  [[nodiscard]] const_iterator find(std::string_view) const;
  [[nodiscard]] bool contains(std::string_view name) const {return find(name)!=end();}
  [[nodiscard]] const std::uint64_t& at(std::string_view) const;
  [[nodiscard]] Prepared prepare(std::string_view,std::uint64_t);
  // Uses an existing iterator or prepaid node. No new allocation; ordered
  // linking/comparison work remains, and internal protocol violations terminate.
  void publish(Prepared&) noexcept;
  [[nodiscard]] bool operator==(const InputPositions& other) const {
    return std::equal(begin(),end(),other.begin(),other.end());
  }
  [[nodiscard]] bool operator==(const std::map<std::string,std::uint64_t>&) const;
 private:
  resource::AccountedUnique<Data> data_;
};
struct AccountedInputProgress {
  std::uint64_t sequence=0;
  InputPositions source_positions;
  AccountedInputProgress() noexcept=default;
  explicit AccountedInputProgress(const resource::MemoryAccount& account):source_positions(account) {}
  AccountedInputProgress(const resource::MemoryAccount&,const InputProgress&);
  AccountedInputProgress(const resource::MemoryAccount&,const AccountedInputProgress&);
  AccountedInputProgress(const AccountedInputProgress&)=default;
  AccountedInputProgress& operator=(const AccountedInputProgress& source) {
    if(this!=&source){AccountedInputProgress copy(source);*this=std::move(copy);}return *this;
  }
  AccountedInputProgress(AccountedInputProgress&&) noexcept=default;
  AccountedInputProgress& operator=(AccountedInputProgress&&) noexcept=default;
  [[nodiscard]] bool operator==(const AccountedInputProgress&) const=default;
  [[nodiscard]] bool operator==(const InputProgress&) const;
  // Explicit caller-owned DTO export. Operational owners retain this native
  // state instead of an ordinary map/string shadow or an accounting ticket.
  [[nodiscard]] InputProgress export_value() const;
};
} // namespace crown::io
