#pragma once

#include "validation_work.hpp"
#include "crown/ir/program_model.hpp"
#include "crown/resource/allocator.hpp"
#include <set>

namespace crown::runtime::detail {

// Operational snapshots retain only native compact rows and accounted capacity.
// Public diagnostic Database exports remain a separate external boundary.
struct NativeDatabase {
  using Rows=std::vector<storage::AccountedTuple,resource::MemoryAllocator<storage::AccountedTuple>>;
  std::vector<Rows,resource::MemoryAllocator<Rows>> tables;
  explicit NativeDatabase(const resource::MemoryAccount& account,resource::MemoryAttribution owner)
      :tables(resource::MemoryAllocator<Rows>(account,resource::MemoryPurpose::scratch,owner)) {}
};
// Heterogeneous lookup borrows projected cells; set insertion separately owns a key copy.
struct ConstraintKeyLess {
  using is_transparent=void;
  bool operator()(const storage::AccountedRow& a,const storage::AccountedRow& b) const noexcept {return a.view()<b.view();}
  bool operator()(const storage::AccountedRow& a,storage::RowView b) const noexcept {return a.view()<b;}
  bool operator()(storage::RowView a,const storage::AccountedRow& b) const noexcept {return a<b.view();}
};

inline void validate_native_row(const program::Catalog& catalog,TableId table,storage::TupleValuesView values) {
  if(table.value>=catalog.tables.size())throw Error("invalid_update","table ID out of range");
  const auto& columns=catalog.tables[table.value].columns;
    if(values.size()!=columns.size())throw Error("invalid_update","row arity differs from physical schema");
    for(std::size_t field=0;field<values.size();++field) {
      const auto* legacy=values.legacy_row();
      const auto type=legacy?crown::type_of((*legacy)[field]):storage::type_of(values[field]);
      if(type!=columns[field].type)throw Error("invalid_update","row type differs at column "+std::string(columns[field].name));
      if(!columns[field].decimal)continue;
      if(columns[field].type!=ScalarType::decimal)throw Error("invalid_catalog","decimal specification requires a decimal column");
      const auto scalar=values[field];
      const auto parts=std::get<storage::InlineDecimal>(scalar).parts();const auto specification=*columns[field].decimal;
      const auto integer_digits=parts.digits=="0" || parts.digits.size()<=parts.scale?std::size_t{0}:parts.digits.size()-parts.scale;
      if(parts.scale>specification.scale || integer_digits+specification.scale>specification.precision)
        throw Error("scalar_overflow","row cannot be represented exactly by decimal specification at column "+std::string(columns[field].name));
    }
 }

// The immutable catalog was validated when its actual CompiledProgram was
// admitted. Rechecking that frozen metadata with ordinary sets/strings is not
// needed. Validate every row before projecting any constraint, preserving the
// reference checker's error order and exact scalar/decimal semantics.
template<class DatabaseView>
void validate_native_database(const program::Catalog& catalog,const DatabaseView& database,
    const resource::MemoryAccount& account,resource::MemoryAttribution owner) {
  if(database.tables.size()!=catalog.tables.size())throw Error("invalid_database","database/catalog table count differs");
  for(std::size_t i=0;i<database.tables.size();++i)for(const auto& row:database.tables[i])
    validate_native_row(catalog,TableId{i},validation_values(row));
  using Keys=std::set<storage::AccountedRow,ConstraintKeyLess,resource::MemoryAllocator<storage::AccountedRow>>;
  using Cells=std::vector<storage::ScalarView,resource::MemoryAllocator<storage::ScalarView>>;
  for(std::size_t i=0;i<catalog.tables.size();++i)for(const auto& constraint:catalog.tables[i].constraints) {
    const auto& table=catalog.tables[i];
    if(std::visit([](const auto& item){return item.status!=ConstraintStatus::enforced;},constraint))continue;
    Keys keys(ConstraintKeyLess{},Keys::allocator_type(account,resource::MemoryPurpose::scratch,owner));
    Cells cells(resource::MemoryAllocator<storage::ScalarView>(account,resource::MemoryPurpose::scratch,owner));
    const auto project=[&](const auto& row,const auto& columns) {
      cells.clear();const auto values=validation_values(row);
      for(const auto column:columns)cells.push_back(values[column.value]);
      return storage::RowView::borrow(cells);
    };
    if(const auto* unique=std::get_if<0>(&constraint)) {
      cells.reserve(unique->columns.size());
      for(const auto& row:database.tables[i]) {
        auto key=storage::AccountedRow::copy_of(account,project(row,unique->columns),owner);
        if(!keys.insert(std::move(key)).second)
          throw Error("constraint_violation","unique constraint "+std::string(table.name)+"."+std::string(unique->name)+" is violated");
      }
    }else {
      const auto& foreign=std::get<1>(constraint);cells.reserve(foreign.columns.size());
      for(const auto& row:database.tables[foreign.referenced_table.value])
        keys.insert(storage::AccountedRow::copy_of(account,project(row,foreign.referenced_columns),owner));
      for(const auto& row:database.tables[i])if(!keys.contains(project(row,foreign.columns)))
        throw Error("constraint_violation","foreign key "+std::string(table.name)+"."+std::string(foreign.name)+" is violated");
    }
  }
}
} // namespace crown::runtime::detail
