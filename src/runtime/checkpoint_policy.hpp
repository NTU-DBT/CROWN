#pragma once

#include "crown/runtime/delta.hpp"

namespace crown::runtime::detail {
// Fixed policy words describe options, not account, source or committed-state authority.
inline std::array<std::uint64_t,26> checkpoint_policy(const DeltaOptions& options,DeltaMode mode) {
  std::array<std::uint64_t,26> result{};std::size_t position=0;
  const auto word=[&](std::uint64_t value){result.at(position++)=value;};
  const auto optional=[&](std::optional<std::uint64_t> value){word(value.has_value());word(value.value_or(0));};
  const auto& support=options.physical.support;const auto& observation=support.observation;
  optional(support.work_limit);word(support.support_limit);word(static_cast<std::uint64_t>(support.order));
  word(support.capture_transitions);word(static_cast<std::uint64_t>(observation.mode));word(observation.trace_capacity);
  word(observation.sample_period);word(observation.sample_offset);word(observation.trace_timings);word(0);
  optional(options.physical.work_limit);word(options.physical.derivation_limit);
  word(static_cast<std::uint64_t>(mode));word(static_cast<std::uint64_t>(options.view));
  word(static_cast<std::uint64_t>(options.live_maintenance));word(static_cast<std::uint64_t>(options.completion));
  optional(options.work_limit);optional(options.cursor.work_limit);optional(options.epoch_view.work_limit);
  word(options.spool_row_limit);word(options.spool_byte_limit);return result;
}
// Encoding checks precede runtime admission; receiving memory replaces the old ceiling.
inline DeltaOptions checkpoint_options(const std::array<std::uint64_t,26>& words,std::uint64_t memory) {
  const auto check=[](bool condition) {if(!condition)throw recovery::ImageFailure(recovery::ImageFault::corrupt);};
  std::size_t position=0;const auto word=[&]{return words.at(position++);};
  const auto host=[&]{const auto value=word();check(value<=SIZE_MAX);return static_cast<std::size_t>(value);};
  const auto boolean=[&]{const auto value=word();check(value<=1);return value!=0;};
  const auto optional=[&]() -> std::optional<std::uint64_t> {
    const auto present=boolean();const auto value=word();check(present || value==0);
    return present?std::optional<std::uint64_t>{value}:std::nullopt;
  };
  const auto enumeration=[&]<class T>(T maximum) {
    const auto value=word();check(value<=static_cast<std::uint64_t>(maximum));return static_cast<T>(value);
  };
  DeltaOptions result;auto& support=result.physical.support;auto& observation=support.observation;
  support.work_limit=optional();support.support_limit=word();support.order=enumeration(PropagationOrder::lifo);
  support.capture_transitions=boolean();observation.mode=enumeration(ObservationMode::trace);observation.trace_capacity=host();
  observation.sample_period=word();observation.sample_offset=word();observation.trace_timings=boolean();check(word()==0);
  support.memory_limit_bytes=memory;result.physical.work_limit=optional();result.physical.derivation_limit=word();
  result.mode=enumeration(DeltaMode::delta);result.view=enumeration(ResultView::sql);
  result.live_maintenance=enumeration(LiveMaintenance::eager);result.completion=enumeration(DeltaCompletion::root_first);
  result.work_limit=optional();result.cursor.work_limit=optional();result.epoch_view.work_limit=optional();
  result.spool_row_limit=host();result.spool_byte_limit=host();return result;
}
} // namespace crown::runtime::detail
