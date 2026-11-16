#pragma once

#include "crown/ir/ids.hpp"
#include <optional>

namespace crown::storage::detail {
// One authority for legacy and accounted arenas. Construction failure may
// consume an unpublished ID; no successful owner identity is ever reused.
[[nodiscard]] std::optional<ArenaOwnerId> try_new_arena_owner() noexcept;
}
