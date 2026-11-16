#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace crown::program {
namespace detail { struct JsonNode; class Builder; }
enum class JsonKind { null, boolean, integer, unsigned_integer, number, string, array, object };

// Flat child ranges are owned by Program's native metadata arena.
// Views borrow that arena and never retain the original nlohmann JSON graph.
class JsonView {
 public:
  JsonView() noexcept=default;
  [[nodiscard]] JsonKind kind() const noexcept;
  [[nodiscard]] bool is_null() const noexcept {return kind()==JsonKind::null;}
  [[nodiscard]] bool is_array() const noexcept {return kind()==JsonKind::array;}
  [[nodiscard]] bool is_object() const noexcept {return kind()==JsonKind::object;}
  [[nodiscard]] bool is_structured() const noexcept {return is_array() || is_object();}
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] JsonView at(std::size_t) const;
  [[nodiscard]] std::string_view key(std::size_t) const;
  [[nodiscard]] JsonView member(std::size_t) const;
  // Scalar getters require the exact kind; integers and doubles are not coerced.
  [[nodiscard]] bool boolean() const;
  [[nodiscard]] std::int64_t integer() const;
  [[nodiscard]] std::uint64_t unsigned_integer() const;
  [[nodiscard]] double number() const;
  [[nodiscard]] std::string_view text() const;
 private:
  friend class detail::Builder;
  explicit JsonView(const detail::JsonNode* node) noexcept:node_(node) {}
  const detail::JsonNode* node_=nullptr;
};
} // namespace crown::program
