#pragma once

#include "crown/recovery/sql_rows_files.hpp"
#include "sql_aggregate_file_detail.hpp"
#include "binary_detail.hpp"

namespace crown::recovery::sql_rows::file_detail {
// Reuse one bounded POSIX implementation, with a distinct row-record magic.
// Its framing/torn-prefix checks carry no SQL-program or native-state authority.
using sql_aggregate::file_detail::Io;
using sql_aggregate::file_detail::Path;
using sql_aggregate::file_detail::view;
using sql_aggregate::file_detail::fail;
using sql_aggregate::file_detail::tail;
using sql_aggregate::file_detail::chain;
inline void binding(const Descriptor& descriptor,const Binding& expected) {
  binary_detail::require(bool(descriptor) && expected.descriptor_sha256==descriptor.sha256(),ImageFault::binding);
}
} // namespace crown::recovery::sql_rows::file_detail
