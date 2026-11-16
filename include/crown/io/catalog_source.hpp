#pragma once
#include "crown/ir/model.hpp"
#include <memory>
#include <variant>

namespace crown::io {
// Compiler callers may supply an owned catalog. Runtime readers share the
// existing immutable program through its aliasing source_catalog_owner().
using CatalogSource=std::variant<Catalog,std::shared_ptr<const program::Catalog>>;
} // namespace crown::io
