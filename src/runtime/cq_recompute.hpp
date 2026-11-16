#pragma once

#include "crown/runtime/source_image.hpp"
#include "crown/api/error.hpp"
#include <array>
#include <limits>

namespace crown::runtime::cq_recompute {
inline constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
template<class T> using Vector = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::scratch) {
  return resource::MemoryAllocator<T>(account, purpose, memory);
}
inline LayoutId output_id(const CompiledProgram& source, const char* code) {
  if (source.layouts().size() == SIZE_MAX) throw Error(code, "CQ output layout ID exhausted");
  return LayoutId{source.layouts().size() + 1};
}

// Native immutable original-query storage shared by the conservative engines.
// No source owner or ordinary retained Catalog/Query lives here. Fixed reserves
// keep every text/span/literal view stable. Only callers requesting an output
// ID create a layout: difference's RHS needs metadata/projection only.
struct FrozenQuery {
  Vector<char> text;
  Vector<program::Variable> variables;
  Vector<storage::AccountedRow> constants;
  Vector<program::Term> terms;
  Vector<program::Atom> atoms;
  Vector<program::Output> head;
  program::Query query;
  storage::AccountedLayout layout;
  template<class Budget>
  FrozenQuery(const CompiledProgram& source, const ::crown::Query& original,
      std::optional<LayoutId> output, std::string_view binding, Budget& budget, const char* overflow_code)
      : text(allocator<char>(source.account(), resource::MemoryPurpose::immutable_metadata)),
        variables(allocator<program::Variable>(source.account(), resource::MemoryPurpose::immutable_metadata)),
        constants(allocator<storage::AccountedRow>(source.account(), resource::MemoryPurpose::immutable_metadata)),
        terms(allocator<program::Term>(source.account(), resource::MemoryPurpose::immutable_metadata)),
        atoms(allocator<program::Atom>(source.account(), resource::MemoryPurpose::immutable_metadata)),
        head(allocator<program::Output>(source.account(), resource::MemoryPurpose::immutable_metadata)) {
    const auto& account = source.account(); std::size_t bytes = 0, term_count = 0, literal_count = 0;
    const auto add = [&](std::size_t& value, std::size_t amount) {
      if (amount > SIZE_MAX - value) throw Error(overflow_code, "CQ metadata size overflow");
      value += amount;
    };
    const auto count_text = [&](std::string_view name) { budget.take(); budget.take(name.size()); add(bytes, name.size()); };
    for (const auto& variable : original.variables) count_text(variable.name);
    for (const auto& atom : original.atoms) {
      count_text(atom.occurrence); add(term_count, atom.terms.size());
      for (const auto& term : atom.terms) { budget.take(); if (std::holds_alternative<Value>(term)) add(literal_count, 1); }
    }
    for (const auto& field : original.head) count_text(field.alias);
    text.reserve(bytes);
    budget.take(original.variables.size()); variables.reserve(original.variables.size());
    budget.take(literal_count); constants.reserve(literal_count);
    budget.take(term_count); terms.reserve(term_count);
    budget.take(original.atoms.size()); atoms.reserve(original.atoms.size());
    budget.take(original.head.size()); head.reserve(original.head.size());
    const auto freeze_text = [&](std::string_view value) {
      if (value.empty()) return std::string_view{};
      const auto offset = text.size(); text.insert(text.end(), value.begin(), value.end());
      return std::string_view(text.data() + offset, value.size());
    };
    for (const auto& variable : original.variables) variables.push_back({freeze_text(variable.name), variable.type});
    Vector<std::optional<DecimalSpec>> decimal(allocator<std::optional<DecimalSpec>>(account));
    Vector<std::uint8_t> seen(allocator<std::uint8_t>(account));
    if (output) {
      budget.take(original.variables.size()); decimal.resize(original.variables.size());
      budget.take(original.variables.size()); seen.assign(original.variables.size(), 0);
    }
    for (const auto& atom : original.atoms) {
      const auto offset = terms.size();
      for (std::size_t field = 0; field < atom.terms.size(); ++field) {
        budget.take(); const auto& term = atom.terms[field];
        if (const auto* variable = std::get_if<VariableId>(&term)) {
          terms.push_back(*variable);
          if (output && !seen[variable->value]) {
            seen[variable->value] = 1;
            decimal[variable->value] = source.source_catalog().tables[atom.table.value].columns[field].decimal;
          }
        } else if (const auto* literal = std::get_if<Value>(&term)) {
          const std::array cell{storage::borrow_scalar(*literal)}; budget.scalar(cell[0]);
          constants.push_back(storage::AccountedRow::copy_of(account, storage::RowView::borrow(cell), memory));
          terms.push_back(constants.back().view()[0]);
        } else terms.push_back(IgnoredColumn{});
      }
      atoms.push_back({freeze_text(atom.occurrence), atom.table,
          program::Span<program::Term>(atom.terms.empty() ? nullptr : terms.data() + offset, atom.terms.size())});
    }
    Vector<storage::Field> fields(allocator<storage::Field>(account));
    if (output) { budget.take(original.head.size()); fields.reserve(original.head.size()); }
    for (const auto& field : original.head) {
      budget.take(); head.push_back({field.variable, freeze_text(field.alias)});
      if (output) fields.push_back({variables[field.variable.value].type, decimal[field.variable.value], field.variable});
    }
    query = {program::Span<program::Variable>(variables.data(), variables.size()),
        program::Span<program::Atom>(atoms.data(), atoms.size()),
        program::Span<program::Output>(head.data(), head.size()), original.contradiction};
    if (output) {
      budget.take(); budget.take(fields.size());
      layout = storage::AccountedLayout::make(account, *output, fields,
          storage::LayoutContextView{source.source_catalog().version, binding}, {}, memory);
    }
  }
  FrozenQuery(const FrozenQuery&) = delete;
  FrozenQuery& operator=(const FrozenQuery&) = delete;
};

// One callback for EVERY complete physical-row choice, before DISTINCT/count
// reduction. Equal variable assignments can have different ignored-column row
// witnesses. Return false only when the caller's semantics allow early stop:
// set Boolean support can; bag Boolean multiplicity cannot. No per-assignment
// callback wrapper, owning Row or allocation is introduced by dispatch.
template<class Budget, class Emit>
void visit(const program::Query& query, const physical::SourceImage& image,
    const resource::MemoryAccount& account, Budget& budget, Emit&& emit) {
  if (query.contradiction) return;
  struct Frame { std::size_t next = 0, mark = 0; };
  budget.take(query.variables.size());
  Vector<std::optional<storage::ScalarView>> assignment(query.variables.size(), {}, allocator<std::optional<storage::ScalarView>>(account));
  budget.take(query.variables.size());
  Vector<VariableId> trail(allocator<VariableId>(account)); trail.reserve(query.variables.size());
  budget.take(query.atoms.size()); Vector<Frame> frames(query.atoms.size(), {}, allocator<Frame>(account));
  budget.take(query.head.size());
  Vector<storage::ScalarView> projected(allocator<storage::ScalarView>(account)); projected.reserve(query.head.size());
  const auto publish = [&] {
    budget.take(); ++budget.metrics.assignments; ++budget.metrics.projected; projected.clear();
    for (const auto& field : query.head) {
      const auto value = *assignment[field.variable.value]; budget.scalar(value); projected.push_back(value);
    }
    return emit(storage::RowView::borrow(projected));
  };
  const auto restore = [&](std::size_t mark) {
    while (trail.size() > mark) { budget.take(); assignment[trail.back().value].reset(); trail.pop_back(); }
  };
  if (query.atoms.empty()) { static_cast<void>(publish()); return; }
  std::size_t depth = 0;
  for (;;) {
    auto& frame = frames[depth]; restore(frame.mark);
    const auto& atom = query.atoms[depth]; const auto& rows = image.tables[atom.table.value];
    if (frame.next == rows.size()) {
      frame.next = 0; if (depth == 0) break; --depth; continue;
    }
    budget.take(); ++budget.metrics.row_visits;
    const auto row = rows[frame.next++].values(); bool matches = true;
    for (std::size_t field = 0; field < atom.terms.size(); ++field) {
      budget.take(); ++budget.metrics.term_tests; const auto& term = atom.terms[field];
      if (std::holds_alternative<IgnoredColumn>(term)) continue;
      const auto value = row[field];
      if (const auto* variable = std::get_if<VariableId>(&term)) {
        auto& bound = assignment[variable->value];
        if (bound) {
          ++budget.metrics.equality_tests;
          if (budget.compare(*bound, value) != 0) { matches = false; break; }
        } else { budget.scalar(value); bound = value; trail.push_back(*variable); }
      } else {
        ++budget.metrics.equality_tests;
        if (budget.compare(std::get<storage::ScalarView>(term), value) != 0) { matches = false; break; }
      }
    }
    if (!matches) continue;
    if (depth == query.atoms.size() - 1) { if (!publish()) break; }
    else { ++depth; frames[depth] = Frame{0, trail.size()}; }
  }
}
} // namespace crown::runtime::cq_recompute
