#pragma once

#include "crown/ir/model.hpp"
#include "crown/storage/accounted_row.hpp"
#include <nlohmann/json.hpp>
#include <string_view>

namespace crown::io {
using Json = nlohmann::json;
// Strict external JSON boundary: reject duplicate keys and nesting beyond256
// before a DOM can erase ambiguity in a nested, subsequently validated artifact.
[[nodiscard]] Json read_json(std::string_view text);
[[nodiscard]] Document read_document(std::string_view text);
[[nodiscard]] Json write_document(const Document& document);
// Explicit lossless upward migration only. Writers otherwise preserve version.
[[nodiscard]] Document upgrade_document(const Document& document, std::uint64_t target_version);
[[nodiscard]] Json write_scalar(const Value& value);
[[nodiscard]] Json write_scalar_view(const storage::ScalarView& value);
[[nodiscard]] Value read_scalar(const Json& value);
[[nodiscard]] Json write_relation(const Relation& relation);
[[nodiscard]] Json write_epoch(const CommittedReferenceEpoch& epoch);
}  // namespace crown::io
