#pragma once

// Usage: version 2 callers place this section immediately after the optional
// window and before the runtime-image byte length. Version 1 never calls these
// functions, so the legacy section remains byte-for-byte unchanged.
//
// The pattern limits below bound envelope traversal/cells/payload (including
// funded rule scratch). Declaration::import applies its own work/cell/payload
// limits again while canonicalizing and retaining the declaration. These are
// finite operation grants, not CPU-time bounds. The declaration is requested
// metadata; source/runtime binding remains part of restore admission.
#include "binary_detail.hpp"
#include "crown/recovery/session_image.hpp"
#include "crown/runtime/update_pattern.hpp"
#include <algorithm>
#include <limits>
#include <span>
#include <type_traits>

namespace crown::recovery::detail {
namespace pattern_wire_detail {
inline void require(bool value, ImageFault fault = ImageFault::binding) {
  binary_detail::require(value, fault);
}
inline std::uint64_t section_size(std::uint64_t rules, bool has_violation) {
  constexpr std::uint64_t fixed = 97; // hash, counts, origins and presence byte
  constexpr std::uint64_t rule_bytes = 17;
  const auto extra = has_violation ? 25u : 0u;
  require(rules <= (std::numeric_limits<std::uint64_t>::max() - fixed - extra) / rule_bytes,
      ImageFault::limit);
  return fixed + rules * rule_bytes + extra;
}
inline std::uint64_t scratch_size(std::uint64_t rules) {
  constexpr auto cell_bytes = sizeof(patterns::TableRule);
  require(rules <= std::numeric_limits<std::uint64_t>::max() / cell_bytes &&
      rules <= std::numeric_limits<std::size_t>::max() / cell_bytes, ImageFault::limit);
  return rules * cell_bytes;
}
inline std::uint64_t parse_work(std::uint64_t rules, bool has_violation) {
  // Hash validation, fixed metadata, one rule pass, plus at most one bounded
  // rule-context scan for a violation. Declaration construction is separate.
  constexpr std::uint64_t fixed = 72;
  const auto passes = has_violation ? 2u : 1u;
  require(rules <= (std::numeric_limits<std::uint64_t>::max() - fixed) / passes,
      ImageFault::work);
  return fixed + rules * passes;
}
inline std::uint64_t parse_payload(std::uint64_t rules, bool has_violation) {
  const auto wire = section_size(rules, has_violation);
  const auto scratch = scratch_size(rules);
  require(scratch <= std::numeric_limits<std::uint64_t>::max() - wire, ImageFault::limit);
  return wire + scratch;
}
inline void check_parse_caps(const patterns::Limits& limits, std::uint64_t rules,
    bool has_violation) {
  require(rules <= limits.cells, ImageFault::limit);
  require(parse_work(rules, has_violation) <= limits.work, ImageFault::work);
  require(parse_payload(rules, has_violation) <= limits.payload_bytes, ImageFault::limit);
}
template<class Input>
inline std::optional<patterns::TableRule> wire_rule(Input& in,
    std::size_t start, std::size_t count, std::uint64_t table) {
  for (std::size_t i = 0; i < count; ++i) {
    const auto at = start + i * 17;
    const auto id = in.at(at);
    if (id == table) {
      const auto insertion = static_cast<unsigned char>(in.input[at + 8]);
      const auto fifo = in.at(at + 9);
      return patterns::TableRule{TableId{id}, insertion != 0, fifo};
    }
    if (id > table) break;
  }
  return std::nullopt;
}
inline const patterns::TableRule* find_rule(std::span<const patterns::TableRule> rules,
    std::uint64_t table) noexcept {
  const auto found = std::lower_bound(rules.begin(), rules.end(), table,
      [](const patterns::TableRule& rule, std::uint64_t id) { return rule.table.value < id; });
  return found != rules.end() && found->table.value == table ? &*found : nullptr;
}
inline void check_violation_context(runtime::SessionInputKind input_kind, bool input_failed,
    std::uint64_t accepted, const std::optional<runtime::PatternViolation>& violation,
    const patterns::TableRule* rule) {
  if (!violation) return;
  require(input_failed);
  require(accepted != std::numeric_limits<std::uint64_t>::max() &&
      violation->command_sequence == accepted + 1);
  require(rule != nullptr && rule->table == violation->table);
  switch (violation->kind) {
    case runtime::PatternViolationKind::erase_command:
      require(input_kind != runtime::SessionInputKind::typed_window && rule->insertion_only &&
          violation->label == 0);
      break;
    case runtime::PatternViolationKind::physical_erase:
      require(input_kind == runtime::SessionInputKind::typed_window && rule->insertion_only &&
          violation->label > 0);
      break;
    case runtime::PatternViolationKind::fifo_scope:
      require(input_kind == runtime::SessionInputKind::typed_window && rule->fifo_scope != 0 &&
          violation->label > 0);
      break;
    default:
      require(false);
  }
}
inline std::uint64_t accepted_command_sequence(const runtime::SessionCheckpoint& state) {
  if (state.window) return state.window->progress.completed_command_sequence;
  return std::visit([](const auto& source) -> std::uint64_t {
    using T = std::remove_cvref_t<decltype(source)>;
    if constexpr (std::is_same_v<T, io::AccountedInputProgress>) return source.sequence;
    else return source.progress.sequence;
  }, state.source);
}
} // namespace pattern_wire_detail

// Version 2 only. Writes canonical declaration rules followed by checkpoint
// origin and the optional fixed diagnostic. No row history is serialized.
template<class Output>
void write_pattern_extension(Output& out, const runtime::SessionCheckpoint& state) {
  using namespace pattern_wire_detail;
  require(state.version == runtime::SessionCheckpoint::current_version, ImageFault::version);
  require(state.update_patterns.has_value(), ImageFault::version);
  const auto& declaration = *state.update_patterns;
  require(static_cast<bool>(declaration));
  const auto rules = declaration.rules();
  const auto source_tables = declaration.source_tables();
  const auto count = static_cast<std::uint64_t>(rules.size());
  const auto violation = state.pattern_violation;
  require(static_cast<std::size_t>(count) == rules.size() &&
      source_tables <= std::numeric_limits<std::size_t>::max() && count <= source_tables,
      ImageFault::limit);
  check_parse_caps(out.state_limits.patterns, count, violation.has_value());
  const auto& source_hash = declaration.source_sha256();
  const auto accepted = accepted_command_sequence(state);
  require(state.pattern_origin_sequence <= state.committed_sequence &&
      state.pattern_origin_command_sequence <= accepted);
  const auto* violation_rule = violation ? find_rule(rules, violation->table.value) : nullptr;
  check_violation_context(state.input_kind, state.input_failed, accepted, violation, violation_rule);

  out.hash(source_hash);
  out.integer(source_tables, 8);
  out.integer(count, 8);
  for (const auto& rule : rules) {
    out.integer(rule.table.value, 8);
    out.boolean(rule.insertion_only);
    out.integer(rule.fifo_scope, 8);
  }
  out.integer(state.pattern_origin_sequence, 8);
  out.integer(state.pattern_origin_command_sequence, 8);
  out.boolean(violation.has_value());
  if (violation) {
    out.enumeration(violation->kind, runtime::PatternViolationKind::fifo_scope);
    out.integer(violation->table.value, 8);
    out.integer(violation->command_sequence, 8);
    out.integer(violation->label, 8);
  }
}

// Version 2 only. Inspection validates structure without allocating; decode
// reserves funded rule scratch only after all count/size/work caps pass, then
// imports directly into the receiving account while scratch remains charged.
template<class Input>
void read_pattern_extension(Input& in, const SessionImageManifest& manifest) {
  using namespace pattern_wire_detail;
  require(manifest.state_version == runtime::SessionCheckpoint::current_version, ImageFault::version);
  const auto section_start = in.position;
  const auto source_hash = in.hash();
  const auto source_tables = static_cast<std::uint64_t>(in.size(std::numeric_limits<std::size_t>::max()));
  const auto& limits = in.state_limits.patterns;
  const auto max_count = std::min({limits.cells, source_tables,
      static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max())});
  const auto count = in.size(max_count);
  const auto count64 = static_cast<std::uint64_t>(count);
  const auto rules_start = in.position;
  const auto fixed_before_violation = section_size(count64, false);
  require(fixed_before_violation <= std::numeric_limits<std::size_t>::max() &&
      section_start <= in.input.size() && fixed_before_violation <= in.input.size() - section_start,
      ImageFault::corrupt);
  const auto flag_at = section_start + static_cast<std::size_t>(fixed_before_violation - 1);
  const auto raw_flag = static_cast<unsigned char>(in.input[flag_at]);
  require(raw_flag <= 1, ImageFault::corrupt);
  const bool has_violation = raw_flag != 0;
  const auto wire_bytes = section_size(count64, has_violation);
  require(wire_bytes <= std::numeric_limits<std::size_t>::max() &&
      section_start <= in.input.size() && wire_bytes <= in.input.size() - section_start,
      ImageFault::corrupt);
  check_parse_caps(limits, count64, has_violation);
  const auto remaining_bytes = static_cast<std::size_t>(wire_bytes) -
      (in.position - section_start);
  std::uint64_t context_scan_work = 0;
  if (has_violation) {
    require(count64 <= (std::numeric_limits<std::uint64_t>::max() - 8) / 8, ImageFault::work);
    context_scan_work = count64 * 8 + 8; // worst case: every table ID plus matching FIFO field
  }
  require(context_scan_work <= std::numeric_limits<std::uint64_t>::max() - remaining_bytes &&
      in.budget.used <= in.budget.limits.work &&
      remaining_bytes + context_scan_work <= in.budget.limits.work - in.budget.used, ImageFault::work);

  ImageVector<patterns::TableRule> scratch;
  if (in.result) {
    scratch=ImageVector<patterns::TableRule>(image_allocator<patterns::TableRule>(in.account));
    scratch.reserve(count);
  }
  std::uint64_t previous = 0;
  for (std::size_t i = 0; i < count; ++i) {
    const auto id = in.integer(8);
    const auto insertion = in.boolean();
    const auto fifo = in.integer(8);
    require(id < source_tables && (i == 0 || previous < id));
    previous = id;
    if (in.result) scratch.push_back({TableId{id}, insertion, fifo});
  }
  const auto origin_sequence = in.integer(8);
  const auto origin_command_sequence = in.integer(8);
  std::optional<runtime::PatternViolation> violation;
  if (in.boolean()) {
    const auto kind = in.enumeration(runtime::PatternViolationKind::fifo_scope);
    violation.emplace(runtime::PatternViolation{kind, TableId{in.size(std::numeric_limits<std::size_t>::max())},
        in.integer(8), in.integer(8)});
  }
  require(in.position - section_start == wire_bytes, ImageFault::corrupt);
  require(origin_sequence <= manifest.committed_sequence &&
      origin_command_sequence <= manifest.accepted_sequence);
  const auto violation_rule = violation ? wire_rule(in, rules_start, count, violation->table.value) :
      std::nullopt;
  const auto* rule = violation_rule ? &*violation_rule : nullptr;
  check_violation_context(manifest.input_kind, manifest.input_failed,
      manifest.accepted_sequence, violation, rule);

  if (in.result) {
    auto declaration = patterns::Declaration::import(in.account, source_hash, source_tables,
        std::span<const patterns::TableRule>{scratch.data(), scratch.size()}, limits);
    auto& state = in.result->state;
    state.update_patterns.emplace(std::move(declaration));
    state.pattern_origin_sequence = origin_sequence;
    state.pattern_origin_command_sequence = origin_command_sequence;
    state.pattern_violation = violation;
  }
}
} // namespace crown::recovery::detail
