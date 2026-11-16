#pragma once

#include "crown/runtime/support.hpp"

namespace crown::io {
struct SupportTrace {
  runtime::SupportOptions options;
  std::vector<runtime::NativeSetUpdate> updates;
};
// Diagnostic logical-native trace, not physical ingestion/checkpoint replay.
[[nodiscard]] SupportTrace read_support_trace(std::string_view text, const PhysicalPlan& plan, std::size_t max_updates = 100000);
[[nodiscard]] SupportTrace read_support_trace(std::string_view text,const CompiledProgram& plan,std::size_t max_updates=100000);
[[nodiscard]] Json write_support_options(const runtime::SupportOptions& options);
[[nodiscard]] Json write_support_snapshot(const runtime::SupportSnapshot& snapshot, const PhysicalPlan& plan);
[[nodiscard]] Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const CompiledProgram& plan);
[[nodiscard]] Json write_support_epoch(const runtime::SupportEpoch& epoch);
}  // namespace crown::io
