#pragma once
#include "crown/io/catalog_source.hpp"
#include "crown/ir/program_model.hpp"
#include "crown/api/error.hpp"
#include <type_traits>
#include <utility>

namespace crown::io::catalog_source_detail {
// Dispatch preserves callback ownership: returned references still borrow source.
// Presence of a native owner alone does not validate catalog semantics.
template<class Function> decltype(auto) read(const CatalogSource& source,Function&& function) {
  return std::visit([&](const auto& value)->decltype(auto) {
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(value)>,Catalog>)
      return std::forward<Function>(function)(value);
    else {
      if(!value)throw Error("invalid_catalog","native catalog owner is empty");
      return std::forward<Function>(function)(*value);
    }
  },source);
}
} // namespace crown::io::catalog_source_detail
