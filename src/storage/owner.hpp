#pragma once

#include "crown/ir/ids.hpp"
#include <optional>

namespace crown::storage::detail {

// One process-wide authority shared by reference and optimized table owners.
// Private storage implementation API; construction failure may consume an ID.
[[nodiscard]] StorageOwnerId new_storage_owner();
[[nodiscard]] std::optional<StorageOwnerId> try_new_storage_owner() noexcept;

}  // namespace crown::storage::detail
