#pragma once

#include "crown/frontend/parser.hpp"

namespace crown::io {
[[nodiscard]] nlohmann::json write_sql_parse(const frontend::SqlParseResult& result);
}  // namespace crown::io
