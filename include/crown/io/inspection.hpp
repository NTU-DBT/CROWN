#pragma once

#include "crown/runtime/inspection.hpp"
#include <string>

namespace crown::io {
// Versioned deterministic diagnostics, not a checkpoint/restore format.
// Encoded-byte limits exclude caller state, allocator slack and scalar scratch.
// Strings require UTF-8; embedded NUL is escaped without loss.
[[nodiscard]] std::string write_runtime_state(const runtime::CanonicalPhysicalState&,std::size_t max_bytes=64*1024*1024);
[[nodiscard]] std::string write_runtime_state(const runtime::CanonicalDeltaState&,std::size_t max_bytes=64*1024*1024);
[[nodiscard]] std::string write_invariant_report(const runtime::InvariantReport&,std::size_t max_bytes=64*1024*1024);
}  // namespace crown::io
