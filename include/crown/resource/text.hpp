#pragma once

#include "crown/resource/memory.hpp"
#include <cstring>
#include <limits>
#include <string_view>
#include <utility>

namespace crown::resource {
// Immutable native text. The real character request and terminator consume the
// original account; copies clone under that same grant and moves transfer it.
class AccountedText {
 public:
  AccountedText() noexcept=default;
  [[nodiscard]] static MemoryUsage allocation_usage_for(std::string_view text) {
    if(text.empty())return {};
    if(text.size()==std::numeric_limits<std::size_t>::max())throw MemoryFailure(MemoryFault::overflow);
    const auto bytes=text.size()+1;
    return {1,MemoryAccount::allocation_bytes(bytes,alignof(char)),bytes};
  }
  [[nodiscard]] static AccountedText copy_of(const MemoryAccount& account,std::string_view text,
      MemoryAttribution owner={},MemoryPurpose purpose=MemoryPurpose::scalar_payload) {
    AccountedText result;result.account_=account;result.owner_=owner;result.purpose_=purpose;
    const auto usage=allocation_usage_for(text);
    if(usage.allocations) {
      result.block_=account.allocate(static_cast<std::size_t>(usage.payload_bytes),alignof(char),purpose,owner);
      std::memcpy(result.block_.data(),text.data(),text.size());
      static_cast<char*>(result.block_.data())[text.size()]='\0';
    }
    result.size_=text.size();return result;
  }
  AccountedText(const AccountedText& source):AccountedText(copy_of(source.account_,source.view(),source.owner_,source.purpose_)) {}
  // Nonempty copies prepare source-account bytes before replacing this value;
  // both old and new blocks remain charged while they overlap.
  AccountedText& operator=(const AccountedText& source) {
    if(this!=&source)*this=copy_of(source.account_,source.view(),source.owner_,source.purpose_);
    return *this;
  }
  AccountedText(AccountedText&& source) noexcept
      :account_(std::move(source.account_)),block_(std::move(source.block_)),size_(std::exchange(source.size_,0)),owner_(source.owner_),purpose_(source.purpose_) {}
  AccountedText& operator=(AccountedText&& source) noexcept {
    if(this!=&source) {
      block_=std::move(source.block_);account_=std::move(source.account_);size_=std::exchange(source.size_,0);
      owner_=source.owner_;purpose_=source.purpose_;
    }
    return *this;
  }
  [[nodiscard]] std::string_view view() const noexcept {return {data(),size_};}
  [[nodiscard]] operator std::string_view() const noexcept {return view();}
  [[nodiscard]] const char* data() const noexcept {return block_?static_cast<const char*>(block_.data()):"";}
  [[nodiscard]] const char* c_str() const noexcept {return data();}
  [[nodiscard]] std::size_t size() const noexcept {return size_;}
  [[nodiscard]] bool empty() const noexcept {return size_==0;}
  // Character-block usage only; the shared controller is counted by the account.
  [[nodiscard]] MemoryUsage memory_usage() const noexcept {return block_.usage();}
  [[nodiscard]] bool operator==(const AccountedText& other) const noexcept {return view()==other.view();}
  [[nodiscard]] std::strong_ordering operator<=>(const AccountedText& other) const noexcept {return view()<=>other.view();}
  [[nodiscard]] bool operator==(std::string_view other) const noexcept {return view()==other;}
  [[nodiscard]] std::strong_ordering operator<=>(std::string_view other) const noexcept {return view()<=>other;}
 private:
  MemoryAccount account_;
  MemoryBlock block_;
  std::size_t size_=0;
  MemoryAttribution owner_;
  MemoryPurpose purpose_=MemoryPurpose::scalar_payload;
};
struct AccountedTextLess {
  using is_transparent=void;
  bool operator()(const AccountedText& a,const AccountedText& b) const noexcept {return a.view()<b.view();}
  bool operator()(const AccountedText& a,std::string_view b) const noexcept {return a.view()<b;}
  bool operator()(std::string_view a,const AccountedText& b) const noexcept {return a<b.view();}
};
} // namespace crown::resource
