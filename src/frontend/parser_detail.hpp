#pragma once

#include <mutex>

namespace crown::frontend::parser_detail {
// One gate for the existing JSON wrapper and composed protobuf/deparse calls.
[[nodiscard]] std::mutex& mutex();
}  // namespace crown::frontend::parser_detail
