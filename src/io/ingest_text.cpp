#include "ingest_text.hpp"

#include "crown/api/error.hpp"
#include <cstddef>

namespace crown::io::ingest_detail {
namespace {

[[noreturn]] void invalid_document(const char* message) {
  throw Error("invalid_document", message);
}

bool continuation(unsigned char byte) { return byte >= 0x80U && byte <= 0xbfU; }

}  // namespace

void require_utf8(std::string_view text) {
  std::size_t position = 0;
  while (position < text.size()) {
    const auto first = static_cast<unsigned char>(text[position]);
    if (first <= 0x7fU) {
      ++position;
      continue;
    }

    std::size_t length = 0;
    if (first >= 0xc2U && first <= 0xdfU) {
      length = 2;
    } else if (first >= 0xe0U && first <= 0xefU) {
      length = 3;
    } else if (first >= 0xf0U && first <= 0xf4U) {
      length = 4;
    } else {
      invalid_document("text contains invalid UTF-8");
    }
    if (text.size() - position < length) invalid_document("text contains truncated UTF-8");

    const auto second = static_cast<unsigned char>(text[position + 1]);
    if (!continuation(second)) invalid_document("text contains invalid UTF-8 continuation bytes");
    if ((first == 0xe0U && second < 0xa0U) ||
        (first == 0xedU && second > 0x9fU) ||
        (first == 0xf0U && second < 0x90U) ||
        (first == 0xf4U && second > 0x8fU)) {
      invalid_document("text contains a non-scalar or out-of-range UTF-8 sequence");
    }
    for (std::size_t offset = 2; offset < length; ++offset) {
      if (!continuation(static_cast<unsigned char>(text[position + offset]))) {
        invalid_document("text contains invalid UTF-8 continuation bytes");
      }
    }
    position += length;
  }
}

}  // namespace crown::io::ingest_detail
