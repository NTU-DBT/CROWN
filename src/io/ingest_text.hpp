#pragma once

#include <string_view>

namespace crown::io::ingest_detail {
// Shared strict UTF-8 validation; callers enforce their own byte/domain limits.
void require_utf8(std::string_view text);
}  // namespace crown::io::ingest_detail
