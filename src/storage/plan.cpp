#include "crown/storage/plan.hpp"

#include "crown/api/error.hpp"
#include <limits>
#include <utility>

namespace crown::storage {
namespace {
void require(bool value,const char* message) {
  if (!value) throw Error("storage_contract",message);
}
IndexWorkAllowance* operation_work(const PhysicalPlan& plan,IndexWorkAllowance* work) {
  const auto& spec=plan.options().indexed_storage;
  if (!spec) return nullptr;
  if (!work) throw Error("storage_contract","indexed plan storage requires one finite aggregate work grant");
  // Bound the current canonical remainder in every domain. A
  // lexicographic IndexWork comparison would not enforce these five caps.
  const auto& left=work->remaining();const auto& cap=spec->per_operation;
  require(left.structural_steps<=cap.structural_steps && left.scalar_fields<=cap.scalar_fields &&
      left.scalar_bytes<=cap.scalar_bytes && left.pointer_slots<=cap.pointer_slots && left.link_actions<=cap.link_actions,
      "provided indexed grant exceeds the declared operation allowance");
  work->admit(IndexWork{.structural_steps=1});return work;
}
// Pointer-word admission is structural work, not actual allocator bytes.
template<class T> void prepare_vector(std::size_t count,IndexWorkAllowance* work) {
  if (!work) return;
  constexpr auto words=static_cast<std::uint64_t>((sizeof(T)+sizeof(void*)-1)/sizeof(void*));
  const auto n=static_cast<std::uint64_t>(count);
  if (n>std::numeric_limits<std::uint64_t>::max()/words)
    throw Error("storage_overflow","plan storage metadata work exceeds its integer domain");
  work->admit(IndexWork{.pointer_slots=n*words});
}
void step(IndexWorkAllowance* work) { if (work) work->admit(IndexWork{.structural_steps=1}); }
}  // namespace

PlanStorage::PlanStorage(PhysicalPlan plan,IndexWorkAllowance* supplied) : plan_(std::move(plan)) {
  static_cast<void>(plan_.route());auto* work=operation_work(plan_,supplied);
  prepare_vector<StorageTable>(plan_.relations().size(),work);
  prepare_vector<IndexId>(plan_.indexes().size(),work);
  tables_.reserve(plan_.relations().size());indexes_.reserve(plan_.indexes().size());
  for (const auto& relation : plan_.relations()) {
    step(work);
    if (const auto& spec=plan_.options().indexed_storage)
      tables_.emplace_back(relation.id,relation.layout,spec->per_table);
    else tables_.emplace_back(relation.id,relation.layout);
  }
  for (const auto& requirement : plan_.indexes()) {
    step(work);indexes_.push_back(table(requirement.relation).add_index(requirement.projection,work));
  }
}
PlanStorage::PlanStorage(PhysicalPlan plan,std::vector<StorageTable> tables,std::vector<IndexId> indexes)
    : plan_(std::move(plan)),tables_(std::move(tables)),indexes_(std::move(indexes)) {}
StorageBackend PlanStorage::backend() const {
  return plan_.options().indexed_storage ? StorageBackend::indexed_chained_v1 : StorageBackend::reference_ordered_v1;
}
StorageTable& PlanStorage::table(RelationId relation) {
  if (relation.value>=tables_.size()) throw Error("unknown_relation","physical relation is outside this plan storage");
  return tables_[relation.value];
}
const StorageTable& PlanStorage::table(RelationId relation) const {
  if (relation.value>=tables_.size()) throw Error("unknown_relation","physical relation is outside this plan storage");
  return tables_[relation.value];
}
IndexId PlanStorage::index(IndexRequirementId requirement) const {
  if (requirement.value>=indexes_.size()) throw Error("unknown_index","compiled index is outside this plan storage");
  return indexes_[requirement.value];
}
PlanStorage PlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const {
  static_cast<void>(plan_.route());auto* work=operation_work(plan_,supplied);
  prepare_vector<StorageTable>(tables_.size(),work);prepare_vector<IndexId>(indexes_.size(),work);
  std::vector<StorageTable> copies;copies.reserve(tables_.size());
  for (const auto& table : tables_) { step(work);copies.push_back(table.snapshot_copy(work)); }
  auto indexes=indexes_;
  return {plan_,std::move(copies),std::move(indexes)};
}
void PlanStorage::check_invariants(IndexWorkAllowance* supplied) const {
  auto* work=operation_work(plan_,supplied);
  require(tables_.size()==plan_.relations().size() && indexes_.size()==plan_.indexes().size(),
      "backend plan storage shape differs from the immutable plan");
  const auto kind=backend();
  require(plan_.guarantee().storage_backend==(kind==StorageBackend::indexed_chained_v1 ?
      "indexed_chained_v1" : "reference_ordered_v1"),"physical guarantee and backend choice disagree");
  for (const auto& relation : plan_.relations()) {
    const auto& stored=table(relation.id);
    require(stored.backend()==kind && stored.relation()==relation.id && stored.layout().same_token(relation.layout),
        "physical relation has a different backend/layout/identity");
    if (const auto& spec=plan_.options().indexed_storage)
      require(stored.indexed_limits()==std::optional<IndexedLimits>(spec->per_table),"physical table limits differ from the plan");
    stored.check_invariants();
  }
  for (const auto& requirement : plan_.indexes())
    require(table(requirement.relation).projection(index(requirement.id),work).same_token(requirement.projection),
        "physical index projection differs from the compiled program");
}
}  // namespace crown::storage
