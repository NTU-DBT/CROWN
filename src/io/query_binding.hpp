#pragma once
#include "crown/catalog/catalog.hpp"
#include "crown/io/document.hpp"

namespace crown::io::detail {
inline Json query_binding(const Catalog& catalog, const Query& query) {
  // This explicit export copies the owning catalog/query and allocates an ordinary DOM.
  Document document{catalog, query, Database{std::vector<Relation>(catalog.tables.size())}, {}};
  for (const auto& table : catalog.tables) {
    for (const auto& column : table.columns) {
      if (column.type == ScalarType::date || column.type == ScalarType::decimal) document.schema_version = 2;
    }
  }
  if (catalog::requires_format3(catalog)) document.schema_version = 3;
  return write_document(document);
}
}  // namespace crown::io::detail
