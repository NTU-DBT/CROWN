#pragma once

#include "crown/runtime/combined_statistics.hpp"
#include "crown/runtime/session.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>

namespace crown::statistics_acceptance {
namespace ws = runtime::workload;
namespace st = runtime::statistics;
inline std::uint64_t checked_events{}, checked_derivations{}, checked_sources{}, checked_metadata_steps{};

inline void require(bool value, const std::string& label) {
  if (!value) throw std::runtime_error("C01 acceptance: " + label);
}
inline ws::Options census() {
  ws::Options value;
  value.mode = ws::Mode::counters;
  value.detail_budget = 1000000;
  return value;
}
inline void enable(runtime::DeltaRuntime& runtime) {
  runtime.configure_workload_statistics(census());
}
inline void enable(runtime::QuerySession& session) {
  session.configure_workload_statistics(census());
}
inline st::OwnerRequest source_request(const Database& database) {
  st::OwnerRequest request;
  for (std::size_t table = 0; table < database.tables.size(); ++table)
    request.selections.push_back({st::SourceScope{TableId{table}}, std::nullopt});
  return request;
}
inline void sources(const st::CombinedCapture& capture, const Database& database,
                    runtime::SupportOwnerId owner, std::uint64_t sequence, const std::string& label) {
  const auto& state = capture.state();
  const auto& work = capture.workload();
  require(state.stamp().owner == owner && work.stamp().owner == owner &&
              state.stamp().sequence == sequence && work.stamp().committed_epoch == sequence,
          label + ": owner/committed epoch mismatch");
  require(state.availability() == st::Availability::available && !work.pending(),
          label + ": completed public capture is unavailable or pending");
  require(state.components().size() == database.tables.size(), label + ": missing source component");
  for (std::size_t table = 0; table < database.tables.size(); ++table) {
    const auto& component = state.components()[table];
    const auto* scope = std::get_if<st::SourceScope>(&component.selection.scope);
    require(scope && scope->table == TableId{table} && !component.selection.fields &&
                component.availability == st::Availability::available && component.cardinality &&
                *component.cardinality == database.tables[table].size() && !component.distribution,
            label + ": source cardinality differs from independent database");
    ++checked_sources;
  }
  require(work.options() == census() && work.detail_availability() == ws::Availability::exact &&
              work.arrival_per_second() == ws::Availability::unavailable,
          label + ": wrong census/arrival availability");
}
inline void sources(const runtime::DeltaRuntime& runtime, const Database& database,
                    const std::string& label) {
  sources(runtime.capture_combined_statistics(source_request(database)), database,
          runtime.owner(), runtime.sequence(), label);
}
inline void sources(const runtime::QuerySession& session, const Database& database,
                    const std::string& label) {
  const auto capture = session.capture_combined_statistics(source_request(database));
  require(capture.has_value(), label + ": active session capture absent");
  sources(*capture, database, session.report_metadata().owner(), session.status().committed_sequence, label);
}
// This accumulator is independent of Cell::observe/merge and the collector.
inline void observe(ws::Cell& cell, std::uint64_t value) {
  if (cell.count == 0) cell.min = cell.max = value;
  else { cell.min = std::min(cell.min, value); cell.max = std::max(cell.max, value); }
  ++cell.count;
  cell.sum += value;
  std::size_t bin = 0;
  for (auto remaining = value; remaining != 0; remaining /= 2) ++bin;
  ++cell.bins[bin];
}
inline void event(const ws::Snapshot& before, const ws::Snapshot& after,
                  const std::optional<PhysicalSetUpdate>& input, bool changed,
                  const std::string& label,
                  std::optional<std::span<const runtime::DerivationChange>> derivations = std::nullopt,
                  bool already_admitted = false) {
  require(before.options() == census() && after.options() == census(), label + ": census not enabled");
  require(before.descriptors().size() == after.descriptors().size() &&
              std::equal(before.descriptors().begin(), before.descriptors().end(), after.descriptors().begin()),
          label + ": descriptors changed during an event");
  require(before.stamp().owner == after.stamp().owner &&
              before.stamp().reset_generation == after.stamp().reset_generation &&
              before.stamp().configuration_generation == after.stamp().configuration_generation &&
              before.stamp().segment == after.stamp().segment,
          label + ": event silently rotated the collection interval");
  const auto increment = input ? std::uint64_t{1} : std::uint64_t{0};
  require(!already_admitted || (input && before.pending() &&
              before.metadata().attempts == before.metadata().committed + before.metadata().aborted + 1),
          label + ": expected one already-admitted private physical root");
  const auto admission_increment = already_admitted ? std::uint64_t{0} : increment;
  require(after.metadata().attempts == before.metadata().attempts + admission_increment &&
              after.metadata().committed == before.metadata().committed + increment &&
              after.metadata().selected == before.metadata().selected + admission_increment &&
              after.metadata().complete == before.metadata().complete + increment &&
              after.metadata().aborted == before.metadata().aborted &&
              after.metadata().truncated == before.metadata().truncated &&
              !after.metadata().saturated && !after.metadata().invalid_descriptor &&
              !after.metadata().protocol_error && !after.metadata().ordinal_exhausted,
          label + ": physical-event coverage differs from independent command/update");
  std::size_t roots = 0, matched_derivations = 0;
  for (std::size_t i = 0; i < after.cells().size(); ++i) {
    const auto& descriptor = after.descriptors()[i];
    auto expected = before.cells()[i];
    const bool matching_input = input && descriptor.input_scope == ws::InputScope::physical_table &&
        descriptor.table == input->table.value &&
        descriptor.operation == (input->operation == SetOperation::insert ? ws::Operation::insert : ws::Operation::erase);
    if (descriptor.role == ws::Role::input) {
      if (matching_input) {
        ++roots; ++expected.inputs; ++expected.complete_detail_inputs;
        if (changed) ++expected.changed; else ++expected.noop;
      }
      require(after.cells()[i] == expected, label + ": physical root changed/no-op/sample counts differ");
    } else if (derivations && descriptor.role == ws::Role::derivation) {
      if (matching_input) {
        for (const auto& derivation : *derivations) if (descriptor.occurrence == derivation.occurrence) {
          require(derivation.before != derivation.after, label + ": unchanged public derivation audit");
          ++matched_derivations; ++expected.changes;
          if (derivation.before == 0) ++expected.zero_to_positive;
          if (derivation.after == 0) ++expected.positive_to_zero;
          observe(expected, derivation.after);
        }
      }
      require(after.cells()[i] == expected, label + ": derivation changes/crossings/after-value distribution differ");
    } else if (!input) {
      require(after.cells()[i] == expected, label + ": metadata-only window step created workload events");
    }
  }
  require(roots == (input ? 1U : 0U), label + ": physical event has wrong number of root cells");
  if (derivations) {
    require(matched_derivations == derivations->size(), label + ": derivation descriptor coverage incomplete");
    checked_derivations += static_cast<std::uint64_t>(matched_derivations);
  }
  if (input) {
    require(after.stamp().committed_epoch == input->sequence, label + ": workload committed epoch differs");
    ++checked_events;
  } else {
    require(after.stamp().committed_epoch == before.stamp().committed_epoch,
            label + ": metadata-only step advanced physical epoch");
    ++checked_metadata_steps;
  }
}
inline void print() {
  std::cout << "C01 enabled acceptance physical_events=" << checked_events
            << " derivation_events=" << checked_derivations << " source_components=" << checked_sources
            << " metadata_only_steps=" << checked_metadata_steps << '\n';
}
} // namespace crown::statistics_acceptance
