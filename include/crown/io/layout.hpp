#pragma once

#include "crown/io/document.hpp"
#include "crown/storage/layout.hpp"

namespace crown::io {
[[nodiscard]] Json write_layout(const storage::TupleLayout& layout);
[[nodiscard]] storage::TupleLayout read_layout(std::string_view text);
[[nodiscard]] Json write_projection(const storage::Projection& projection);
// Bind an artifact to the caller's immutable layout tokens after checking the
// complete descriptors. Shared target tokens make cross-relation keys usable.
[[nodiscard]] storage::Projection read_projection(std::string_view text, const storage::TupleLayout& source, const storage::TupleLayout& target);
}  // namespace crown::io
