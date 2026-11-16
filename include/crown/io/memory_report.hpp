#pragma once
#include "crown/io/document.hpp"
#include "crown/runtime/memory_report.hpp"

namespace crown::io {
// Explicit caller-owned diagnostic export. Never an import/deployment capability.
[[nodiscard]] Json write_memory_report(const runtime::memory::Report&);
}
