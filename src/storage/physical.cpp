#include "crown/storage/physical.hpp"

#include "crown/api/error.hpp"
#include <utility>

namespace crown::storage {
ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan) : plan_(std::move(plan)) {
  if (plan_.options().indexed_storage)
    throw Error("unsupported_storage_backend","reference plan storage cannot host an indexed physical plan");
  tables_.reserve(plan_.relations().size());
  for (const auto& relation : plan_.relations()) tables_.emplace_back(relation.id,relation.layout);
  indexes_.reserve(plan_.indexes().size());
  for (const auto& requirement : plan_.indexes()) indexes_.push_back(table(requirement.relation).add_index(requirement.projection));
}
ReferencePlanStorage& ReferencePlanStorage::operator=(ReferencePlanStorage&& other) noexcept {
  // Replacing the destination may release complete old backend/arena
  // populations; moving incoming vector handles does not make cleanup free.
  if (this!=&other) { plan_=std::move(other.plan_); tables_=std::move(other.tables_); indexes_=std::move(other.indexes_); }
  return *this;
}
ReferencePlanStorage::ReferencePlanStorage(PhysicalPlan plan,std::vector<ReferenceTable> tables,std::vector<IndexId> indexes)
    : plan_(std::move(plan)),tables_(std::move(tables)),indexes_(std::move(indexes)) {}
ReferencePlanStorage ReferencePlanStorage::snapshot_copy() const {
  static_cast<void>(plan_.route());
  std::vector<ReferenceTable> copies; copies.reserve(tables_.size());
  for (const auto& table : tables_) copies.push_back(table.snapshot_copy());
  return {plan_,std::move(copies),indexes_};
}
ReferenceTable& ReferencePlanStorage::table(RelationId relation) {
  if (relation.value>=tables_.size()) throw Error("unknown_relation","physical relation is outside this plan storage");
  return tables_[relation.value];
}
const ReferenceTable& ReferencePlanStorage::table(RelationId relation) const {
  if (relation.value>=tables_.size()) throw Error("unknown_relation","physical relation is outside this plan storage");
  return tables_[relation.value];
}
IndexId ReferencePlanStorage::index(IndexRequirementId requirement) const {
  if (requirement.value>=indexes_.size()) throw Error("unknown_index","compiled index requirement is outside this plan storage");
  return indexes_[requirement.value];
}
void ReferencePlanStorage::check_invariants() const {
  if (tables_.size()!=plan_.relations().size() || indexes_.size()!=plan_.indexes().size()) throw Error("storage_contract","physical storage shape differs from its plan");
  for (const auto& relation : plan_.relations()) {
    const auto& stored=table(relation.id);
    if (stored.relation()!=relation.id || !stored.layout().same_token(relation.layout)) throw Error("storage_contract","physical relation has a different layout/identity");
    stored.check_invariants();
  }
  for (const auto& requirement : plan_.indexes()) {
    if (!table(requirement.relation).projection(index(requirement.id)).same_token(requirement.projection))
      throw Error("storage_contract","physical index has a different compiled projection");
  }
}
}  // namespace crown::storage
