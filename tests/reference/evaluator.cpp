#include "evaluator.hpp"

#include "crown/api/error.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <optional>
#include <utility>

namespace crown::reference {
Relation evaluate(const Catalog& catalog, const Query& query, const Database& database) {
  validate(catalog, query);
  validate_database(catalog, database);
  if (query.contradiction) return {};

  // Expand compatible assignments one occurrence at a time. Keep all physical
  // rows until final projection, including distinct rows mapping to one tuple.
  using Assignment = std::vector<std::optional<Value>>;
  std::vector<Assignment> assignments{Assignment(query.variables.size())};
  for (const auto& atom : query.atoms) {
    std::vector<Assignment> joined;
    for (const auto& assignment : assignments) {
      for (const auto& row : database.tables[atom.table.value]) {
        auto candidate = assignment;
        bool matches = true;
        for (std::size_t i = 0; i < atom.terms.size(); ++i) {
          if (const auto* variable = std::get_if<VariableId>(&atom.terms[i])) {
            auto& binding = candidate[variable->value];
            if (binding && *binding != row[i]) { matches = false; break; }
            binding = row[i];
          } else if (const auto* literal = std::get_if<Value>(&atom.terms[i])) {
            if (*literal != row[i]) { matches = false; break; }
          }
        }
        if (matches) joined.push_back(std::move(candidate));
      }
    }
    assignments = std::move(joined);
  }
  Relation answer;
  for (const auto& assignment : assignments) {
    Row row;
    for (const auto& output : query.head) row.push_back(assignment[output.variable.value].value());
    answer.insert(std::move(row));
  }
  return answer;
}

Session::Session(Catalog catalog, Query query, Database database)
    : catalog_(std::move(catalog)), query_(std::move(query)), database_(std::move(database)) {
  validate(catalog_, query_);
  validate_database(catalog_, database_);
}
Relation Session::snapshot() const { return evaluate(catalog_, query_, database_); }

CommittedReferenceEpoch Session::apply(const PhysicalSetUpdate& update) {
  if (sequence_ == std::numeric_limits<std::uint64_t>::max() || update.sequence != sequence_ + 1) {
    throw Error("invalid_sequence", "update sequence must be the next contiguous sequence, starting at 1");
  }
  validate_row(catalog_, update.table, update.values);
  const Relation before = snapshot();
  auto next = database_;
  auto& table = next.tables[update.table.value];
  bool changed = false;
  switch (update.operation) {
    case SetOperation::insert: changed = table.insert(update.values).second; break;
    case SetOperation::erase: changed = table.erase(update.values) != 0; break;
    default: throw Error("invalid_update", "unknown set operation");
  }
  const Relation after = evaluate(catalog_, query_, next);
  SetDelta delta;
  std::set_difference(after.begin(), after.end(), before.begin(), before.end(), std::inserter(delta.added, delta.added.end()));
  std::set_difference(before.begin(), before.end(), after.begin(), after.end(), std::inserter(delta.removed, delta.removed.end()));
  CommittedReferenceEpoch epoch{update.sequence, changed, after, std::move(delta)};
  // Commit only after both evaluation and all owned output allocations succeed.
  database_.tables.swap(next.tables);
  sequence_ = update.sequence;
  return epoch;
}
}  // namespace crown::reference
