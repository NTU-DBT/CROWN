#pragma once

#include <string>
#include <string_view>
#include <array>

namespace crown {
// SHA-256 of arbitrary bytes, lowercase hexadecimal, per FIPS 180-4.
[[nodiscard]] std::string sha256(std::string_view bytes);
// Native callers can retain or encode the digest without an ordinary string.
[[nodiscard]] std::array<char,64> sha256_fixed(std::string_view bytes);
}  // namespace crown
