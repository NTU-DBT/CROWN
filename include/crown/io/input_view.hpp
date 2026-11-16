#pragma once

#include "crown/runtime/update_view.hpp"
#include <optional>
#include <variant>

namespace crown::io {
struct SourcePosition;
struct InputEvent;
struct WindowCommand;
struct SourcePositionView {
  std::string_view source;
  std::uint64_t offset=0;
  [[nodiscard]] bool operator==(const SourcePositionView&) const=default;
  [[nodiscard]] bool operator==(const SourcePosition&) const;
};
struct InputEventView {
  runtime::PhysicalUpdateView update;
  std::optional<SourcePositionView> source_position;
  [[nodiscard]] static InputEventView borrow(const InputEvent&) noexcept;
};
struct WindowWithdraw {std::uint64_t label;};
struct AdvanceWatermark {std::uint64_t watermark;};
struct WindowInsertView {
  std::uint64_t label=0;
  TableId table{0};
  storage::TupleValuesView values;
  std::uint64_t timestamp=0;
};
struct WindowCommandView {
  std::uint64_t sequence=0;
  // monostate preserves a malformed external variant until head validation;
  // import never silently changes it into a valid watermark or insertion.
  std::variant<std::monostate,WindowInsertView,WindowWithdraw,AdvanceWatermark> command;
  std::optional<SourcePositionView> source_position;
  [[nodiscard]] static WindowCommandView borrow(const WindowCommand&) noexcept;
};
using InputItemView=std::variant<InputEventView,WindowCommandView>;
} // namespace crown::io
