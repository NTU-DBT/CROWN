#pragma once
#include "crown/runtime/delta.hpp"
namespace crown::io {
[[nodiscard]] std::string write_cursor_observation_json(const runtime::CursorObservation&,std::size_t max_bytes=16*1024*1024);
[[nodiscard]] std::string write_committed_state_gauges_json(const runtime::CommittedStateGauges&,std::size_t max_bytes=16*1024*1024);
[[nodiscard]] std::string write_committed_state_gauges_json(const runtime::CapturedStateGauges&,std::size_t max_bytes=16*1024*1024);
} // namespace crown::io
