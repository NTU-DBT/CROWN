#pragma once
#include "sql_aggregate_cbor.hpp"

namespace crown::recovery::sql_rows::detail {
// One bounded wire validator; exact limits alias adds no adapter or authority.
using Cbor = sql_aggregate::detail::Cbor;
} // namespace crown::recovery::sql_rows::detail
