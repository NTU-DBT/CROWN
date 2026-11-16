#pragma once
#include "../../src/planner/compiled_source.hpp"

// Legacy values are borrowed; native program/view values get owning exports
// for the independent reference algorithms. These test-only adapters do not
// run on native update or rebuild paths.
namespace crown::reference::input {
inline const Catalog& catalog(const Catalog& value) {return value;}
inline Catalog catalog(const program::Catalog& value) {return planner::compiler_source_detail::catalog(value);}
inline const Query& query(const Query& value) {return value;}
inline Query query(const program::Query& value) {return planner::compiler_source_detail::query(value);}
inline const frontend::NormalizedSql& normalized(const frontend::NormalizedSql& value) {return value;}
inline frontend::NormalizedSql normalized(const program::NormalizedSql& value) {return planner::compiler_source_detail::normalized(value);}
inline const Value& scalar(const Value& value) {return value;}
inline Value scalar(const storage::ScalarView& value) {return storage::export_scalar(value);}
} // namespace crown::reference::input
