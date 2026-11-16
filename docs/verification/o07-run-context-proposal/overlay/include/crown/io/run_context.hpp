#pragma once
#include "crown/runtime/session.hpp"
namespace crown::io {
// Explicit allocating export outside mutation. Strict UTF-8; native bytes are
// accepted/retained unchanged. Missing metadata is null, never inferred.
[[nodiscard]] std::string write_run_context_json(const runtime::ObservationSnapshot&,
    std::size_t max_bytes=16*1024*1024);
} // namespace crown::io
