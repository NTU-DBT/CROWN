#pragma once

#include "crown/api/error.hpp"
#include "crown/ir/model.hpp"
#include "crown/storage/tuple_values.hpp"
#include <limits>

namespace crown::runtime::detail {
// Conservative abstract precharges for the reference validator's complete
// metadata, row-shape and repeated enforced-key projection/set passes. Ordered
// comparisons, scalar payload widths and allocator costs remain explicit.
inline std::uint64_t validation_product(std::size_t count,std::size_t width) {
  const auto n=static_cast<std::uint64_t>(count),w=static_cast<std::uint64_t>(width);
  if (w!=0 && n>std::numeric_limits<std::uint64_t>::max()/w)
    throw Error("resource_limit","runtime validation work accounting exhausted");
  return n*w;
}
// Actual callers provide ordinary Row or native AccountedTuple values; the result
// borrows their stable payload and performs no owning row export.
template<class RowValue> storage::TupleValuesView validation_values(const RowValue& row) {
  if constexpr(requires {row.values();})return storage::TupleValuesView::borrow(row.values());
  else return storage::TupleValuesView::borrow(row);
}
template<class CatalogView,class DatabaseView,class Charge> void charge_database_validation(const CatalogView& catalog,const DatabaseView& database,Charge charge) {
  if (database.tables.size()!=catalog.tables.size()) throw Error("invalid_database","database/catalog table count differs");
  charge(1);
  for (std::size_t i=0;i<catalog.tables.size();++i) {
    const auto& table=catalog.tables[i]; charge(1); charge(table.name.size());
    for (const auto& column : table.columns) { charge(2); charge(column.name.size()); }
    for (const auto& estimate : table.statistics.distinct_counts) { charge(1); charge(estimate.columns.size()); }
    for (const auto& hint : table.key_hints) { charge(1); charge(hint.columns.size()); charge(hint.reason.size()); }
    for (const auto& row : database.tables[i]) { charge(1); charge(validation_values(row).size()); }
    for (const auto& constraint : table.constraints) {
      std::visit([&](const auto& item) { charge(2); charge(item.name.size()); charge(item.columns.size()); },constraint);
      if (const auto* unique=std::get_if<0>(&constraint)) {
        if (unique->status==ConstraintStatus::enforced)
          charge(validation_product(database.tables[i].size(),unique->columns.size()+1));
      } else {
        const auto& foreign=std::get<1>(constraint);
        charge(1); charge(foreign.referenced_columns.size()); charge(foreign.columns.size());
        // validate_catalog resolves targets and searches their unique keys.
        const auto& target=catalog.tables.at(foreign.referenced_table.value);
        if (foreign.status==ConstraintStatus::enforced) {
          for (const auto& candidate : target.constraints) {
            charge(1);
            if (const auto* key=std::get_if<0>(&candidate)) charge(key->columns.size());
          }
          charge(validation_product(database.tables.at(foreign.referenced_table.value).size(),foreign.referenced_columns.size()+1));
          charge(validation_product(database.tables[i].size(),foreign.columns.size()+1));
        }
      }
    }
  }
}
}  // namespace crown::runtime::detail
