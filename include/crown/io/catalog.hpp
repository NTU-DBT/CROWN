#pragma once

#include "crown/io/document.hpp"

namespace crown::io {
// A standalone catalog has {schema_version:1,catalog:{version,tables}}.
[[nodiscard]] Catalog read_catalog(std::string_view text);
[[nodiscard]] Json write_catalog(const Catalog& catalog);
// The same payload is embedded in CQ format 3. These validate all metadata.
[[nodiscard]] Catalog read_catalog_payload(const Json& payload);
[[nodiscard]] Json write_catalog_payload(const Catalog& catalog);
}  // namespace crown::io
