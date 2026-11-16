#include "crown/frontend/adapter.hpp"

#include "crown/api/error.hpp"
#include <limits>
#include <utility>

namespace crown::frontend {
namespace {
void add_support(SupportCounts& supports, Relation& relation, const Row& tuple) {
  const auto found = supports.find(tuple);
  if (found == supports.end()) { supports.emplace(tuple,1); relation.insert(tuple); }
  else {
    if (found->second == std::numeric_limits<std::uint64_t>::max()) throw Error("support_overflow", "physical projection support count overflow");
    ++found->second;
  }
}
}  // namespace

AdapterState::AdapterState(NormalizedSql query, Database physical)
    : query_(std::move(query)), physical_(std::move(physical)) {
  validate(query_.core_catalog,query_.core);
  validate_database(query_.binding.catalog,physical_);
  logical_.tables.resize(query_.adapters.size()); supports_.resize(query_.adapters.size());
  for (const auto& adapter : query_.adapters) {
    for (const auto& row : physical_.tables.at(adapter.base.value)) {
      const auto projected = adapt_row(query_,adapter.occurrence,row);
      if (projected) add_support(supports_.at(adapter.occurrence.value),logical_.tables.at(adapter.occurrence.value),*projected);
    }
  }
  validate_database(query_.core_catalog,logical_);
}

AdaptedEpoch AdapterState::apply(const PhysicalSetUpdate& update) {
  if (sequence_ == std::numeric_limits<std::uint64_t>::max() || update.sequence != sequence_ + 1)
    throw Error("invalid_sequence", "update sequence must be the next contiguous sequence, starting at 1");
  validate_row(query_.binding.catalog,update.table,update.values);
  if (update.operation != SetOperation::insert && update.operation != SetOperation::erase) throw Error("invalid_update", "unknown set operation");
  auto next_physical = physical_;
  auto& base = next_physical.tables.at(update.table.value);
  const bool changed = update.operation == SetOperation::insert ? base.insert(update.values).second : base.erase(update.values) != 0;
  validate_database(query_.binding.catalog,next_physical);
  auto next_supports = supports_;
  auto next_logical = logical_;
  AdaptedEpoch epoch{update.sequence,changed,{}};
  // Prepare every affected alias in stable occurrence order. No alias state is
  // published until filtering, support transitions and all allocations succeed.
  for (const auto occurrence : query_.base_routes.at(update.table.value)) {
    OccurrenceTransition transition{occurrence,{}};
    const auto tuple = changed ? adapt_row(query_,occurrence,update.values) : std::optional<Row>{};
    if (tuple) {
      auto& counts = next_supports.at(occurrence.value);
      auto& relation = next_logical.tables.at(occurrence.value);
      const auto found = counts.find(*tuple);
      if (update.operation == SetOperation::insert) {
        if (found == counts.end()) transition.delta.added.insert(*tuple);
        add_support(counts,relation,*tuple);
      } else {
        if (found == counts.end() || found->second == 0) throw Error("normalization_contract", "missing support for a physical deletion");
        if (found->second == 1) {
          transition.delta.removed.insert(*tuple); relation.erase(*tuple); counts.erase(found);
        } else --found->second;
      }
    }
    epoch.occurrences.push_back(std::move(transition));
  }
  physical_.tables.swap(next_physical.tables); logical_.tables.swap(next_logical.tables); supports_.swap(next_supports);
  sequence_ = update.sequence;
  return epoch;
}
}  // namespace crown::frontend
