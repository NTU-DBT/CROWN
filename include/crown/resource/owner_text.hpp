#pragma once

#include "crown/resource/owner_allocator.hpp"
#include <concepts>
#include <string>
#include <string_view>

namespace crown::resource {
using OwnerText=std::basic_string<char,std::char_traits<char>,OwnerAllocator<char>>;

// Reading native result text beside a caller string never needs an owning
// conversion. ADL finds these through OwnerAllocator; copies still require an
// explicit caller export or preserve the original allocator/account.
template<class Traits,class Allocator> requires (!std::same_as<Allocator,OwnerAllocator<char>>)
[[nodiscard]] bool operator==(const std::basic_string<char,Traits,OwnerAllocator<char>>& left,
    const std::basic_string<char,Traits,Allocator>& right) noexcept {
  return std::basic_string_view<char,Traits>(left.data(),left.size())==std::basic_string_view<char,Traits>(right.data(),right.size());
}
template<class Traits,class Allocator> requires (!std::same_as<Allocator,OwnerAllocator<char>>)
[[nodiscard]] auto operator<=>(const std::basic_string<char,Traits,OwnerAllocator<char>>& left,
    const std::basic_string<char,Traits,Allocator>& right) noexcept {
  return std::basic_string_view<char,Traits>(left.data(),left.size())<=>std::basic_string_view<char,Traits>(right.data(),right.size());
}
} // namespace crown::resource
