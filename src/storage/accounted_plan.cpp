#include "crown/storage/accounted_plan.hpp"

#include "owner.hpp"
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
#include "accounted_table_testing.hpp"
#endif
#include <algorithm>
#include <limits>
#include <utility>

namespace crown::storage {
namespace {
using resource::MemoryPurpose;
using resource::MemoryAttribution;
MemoryAttribution tag(StorageOwnerId owner) { return {resource::MemoryOwnerKind::immutable_metadata, owner.value}; }
StorageOwnerId next_owner() {
  const auto id = detail::try_new_storage_owner();
  if (!id) throw IndexFailure(IndexFault::overflow);
  return *id;
}
void require(bool value) { if (!value) throw IndexFailure(IndexFault::contract); }
std::uint64_t count(std::size_t value) {
  if constexpr (sizeof(std::size_t) > sizeof(std::uint64_t))
    if (value > std::numeric_limits<std::uint64_t>::max()) throw IndexFailure(IndexFault::overflow);
  return static_cast<std::uint64_t>(value);
}
std::uint64_t add(std::uint64_t a, std::uint64_t b) {
  if (b > std::numeric_limits<std::uint64_t>::max() - a) throw IndexFailure(IndexFault::overflow);
  return a + b;
}
IndexWorkAllowance* operation_work(const std::optional<IndexedBackendSpec>& spec, IndexWorkAllowance* work,
    MetadataWork mode=MetadataWork::execution) {
  // Borrow existing authority: compiler work is separate; reference execution
  // returns null, and indexed execution admits one capped startup.
  if(mode==MetadataWork::compiler) {require(work && work->fixed_diagnostics());return work;}
  if (!spec) return nullptr;
  require(work && work->fixed_diagnostics());
  const auto& left = work->remaining();const auto& cap = spec->per_operation;
  require(left.structural_steps <= cap.structural_steps && left.scalar_fields <= cap.scalar_fields &&
      left.scalar_bytes <= cap.scalar_bytes && left.pointer_slots <= cap.pointer_slots && left.link_actions <= cap.link_actions);
  work->admit(IndexWork{.structural_steps=1});return work;
}
void step(IndexWorkAllowance* work, std::uint64_t n = 1) { if (work) work->admit(IndexWork{.structural_steps=n}); }
template<class T> void prepare_vector(std::size_t n, IndexWorkAllowance* work) {
  if (!work) return;
  constexpr auto words = static_cast<std::uint64_t>((sizeof(T) + sizeof(void*) - 1) / sizeof(void*));
  const auto elements = count(n);
  if (elements > std::numeric_limits<std::uint64_t>::max() / words) throw IndexFailure(IndexFault::overflow);
  work->admit(IndexWork{.pointer_slots=elements * words});
}
}  // namespace

struct AccountedPlanStorage::Metadata {
  struct IndexBinding { RelationId relation; AccountedProjection projection; };
  resource::MemoryAccount account;
  StorageOwnerId owner;
  PhysicalRoute route;
  std::array<char, 64> identity{};
  std::optional<IndexedBackendSpec> indexed;
  std::uint8_t collision_profile=0;
  AccountedVector<AccountedLayout> layouts;
  AccountedVector<RelationBinding> relations;
  AccountedVector<IndexBinding> indexes;
  Metadata(const resource::MemoryAccount& a, StorageOwnerId id, PhysicalRoute r,
      std::optional<IndexedBackendSpec> spec)
      : account(a), owner(id), route(r), indexed(spec),
        layouts(resource::MemoryAllocator<AccountedLayout>(a, MemoryPurpose::immutable_metadata, tag(id))),
        relations(resource::MemoryAllocator<RelationBinding>(a, MemoryPurpose::immutable_metadata, tag(id))),
        indexes(resource::MemoryAllocator<IndexBinding>(a, MemoryPurpose::immutable_metadata, tag(id))) {}
};

AccountedPlanStorage::Binding AccountedPlanStorage::freeze_native_binding(
    const resource::MemoryAccount& account,PhysicalRoute route,std::string_view identity,
    std::string_view guarantee,std::span<const AccountedLayout> layouts,
    std::span<const RelationBinding> relations,std::span<const FrozenIndexBinding> indexes,
    const std::optional<IndexedBackendSpec>& indexed,IndexWorkAllowance* supplied,MetadataWork mode) {
  auto* work=operation_work(indexed,supplied,mode);
  require(route==PhysicalRoute::tree || route==PhysicalRoute::constant_true || route==PhysicalRoute::constant_false);
  require(guarantee==(indexed?"indexed_chained_v1":"reference_ordered_v1") && identity.size()==64);
  for(const auto c:identity)require((c>='0' && c<='9') || (c>='a' && c<='f'));
  if(work)work->admit(IndexWork{.scalar_bytes=64});
  prepare_vector<AccountedLayout>(layouts.size(),work);
  prepare_vector<RelationBinding>(relations.size(),work);
  prepare_vector<Metadata::IndexBinding>(indexes.size(),work);
  const auto id=next_owner();
  auto data=resource::make_accounted_shared<Metadata>(tag(id),account,MemoryPurpose::immutable_metadata,
      account,id,route,indexed);
  std::copy(identity.begin(),identity.end(),data->identity.begin());
  data->layouts.reserve(layouts.size());data->relations.reserve(relations.size());data->indexes.reserve(indexes.size());
  for(std::size_t i=0;i<layouts.size();++i) {
    step(work);const auto& layout=layouts[i];
    require(layout && layout.id().value==i && layout.context().binding==identity &&
        resource::MemoryAllocator<char>(layout.query_account())==resource::MemoryAllocator<char>(account));
    data->layouts.push_back(layout);
  }
  for(const auto& relation:relations) {
    step(work);require(relation.role>=RelationRole::physical_base && relation.role<=RelationRole::visible &&
        relation.layout.value<data->layouts.size());data->relations.push_back(relation);
  }
  for(const auto& index:indexes) {
    step(work);require(index.relation.value<data->relations.size() && index.projection);
    const auto from=index.projection.source().id().value,to=index.projection.target().id().value;
    require(from<data->layouts.size() && to<data->layouts.size() &&
        index.projection.source().same_token(data->layouts[from]) &&
        index.projection.target().same_token(data->layouts[to]) &&
        data->relations[index.relation.value].layout.value==from);
    data->indexes.push_back({index.relation,index.projection});
  }
  return Binding(std::move(data));
}

AccountedPlanStorage::Binding AccountedPlanStorage::clone_binding(const resource::MemoryAccount& account,
    const Binding& source,IndexWorkAllowance* supplied) {
  const auto& input=source.metadata();auto* work=operation_work(input.indexed,supplied);const auto id=next_owner();
  prepare_vector<AccountedLayout>(input.layouts.size(),work);prepare_vector<RelationBinding>(input.relations.size(),work);
  prepare_vector<Metadata::IndexBinding>(input.indexes.size(),work);
  auto data=resource::make_accounted_shared<Metadata>(tag(id),account,MemoryPurpose::immutable_metadata,
      account,id,input.route,input.indexed);
  data->identity=input.identity;data->collision_profile=input.collision_profile;
  data->layouts.reserve(input.layouts.size());data->relations.reserve(input.relations.size());data->indexes.reserve(input.indexes.size());
  for(const auto& layout:input.layouts) {
    step(work);if(work)work->admit(IndexWork{.scalar_fields=count(layout.fields().size()),.scalar_bytes=count(layout.context().binding.size())});
    data->layouts.push_back(AccountedLayout::make(account,layout.id(),layout.fields(),layout.context(),layout.origin(),tag(id)));
  }
  for(const auto& relation:input.relations){step(work);data->relations.push_back(relation);}
  for(std::size_t i=0;i<input.indexes.size();++i) {
    step(work);const auto& value=input.indexes[i];AccountedProjection projection;
    // Construction-only token deduplication can scan O(index_count^2) pairs.
    // It avoids a retained map and does not run on ordinary tuple operations.
    for(std::size_t j=0;j<i;++j){step(work);if(value.projection.same_token(input.indexes[j].projection)){projection=data->indexes[j].projection;break;}}
    if(!projection) {
      const auto from=value.projection.source().id().value,to=value.projection.target().id().value;
      require(from<data->layouts.size() && to<data->layouts.size());
      if(work)work->admit(IndexWork{.scalar_fields=count(value.projection.fields().size())});
      prepare_vector<FieldId>(value.projection.fields().size(),work);
      projection=AccountedProjection::freeze(data->layouts[from],data->layouts[to],value.projection.fields(),tag(id));
    }
    data->indexes.push_back({value.relation,std::move(projection)});
  }
  return Binding(std::move(data));
}

AccountedPlanStorage::AccountedPlanStorage(const resource::MemoryAccount& account, const Inputs& input,
    IndexWorkAllowance* supplied,bool materialize,MetadataWork mode)
    : owner_(next_owner()),
      tables_(resource::MemoryAllocator<AccountedStorageTable>(account, MemoryPurpose::immutable_metadata, tag(owner_))),
      indexes_(resource::MemoryAllocator<IndexId>(account, MemoryPurpose::immutable_metadata, tag(owner_))) {
  require(!materialize || mode==MetadataWork::execution);
  auto* work = operation_work(input.indexed, supplied,mode);
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
  require(input.collision_profile <= 2);
#else
  require(input.collision_profile == 0);
#endif
  require(input.route == PhysicalRoute::tree || input.route == PhysicalRoute::constant_true || input.route == PhysicalRoute::constant_false);
  require(input.guarantee == (input.indexed ? "indexed_chained_v1" : "reference_ordered_v1") && input.identity.size() == 64);
  if (work) work->admit(IndexWork{.scalar_bytes=64});
  for (const char c : input.identity) require((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
  prepare_vector<AccountedLayout>(input.layouts.size(), work);
  prepare_vector<std::optional<AccountedLayout>>(input.layouts.size(), work);
  prepare_vector<RelationBinding>(input.relations.size(), work);
  prepare_vector<Metadata::IndexBinding>(input.indexes.size(), work);
  if(materialize) {
    prepare_vector<AccountedStorageTable>(input.relations.size(), work);
    prepare_vector<IndexId>(input.indexes.size(), work);
  }
  const auto id = next_owner();
  auto data = resource::make_accounted_shared<Metadata>(tag(id), account, MemoryPurpose::immutable_metadata,
      account, id, input.route, input.indexed);
  data->collision_profile=input.collision_profile;
  std::copy(input.identity.begin(), input.identity.end(), data->identity.begin());
  data->layouts.reserve(input.layouts.size());data->relations.reserve(input.relations.size());data->indexes.reserve(input.indexes.size());
  if(materialize) {tables_.reserve(input.relations.size());indexes_.reserve(input.indexes.size());}
  {
    LayoutFreezeRegistry registry(account, input.layouts, tag(id));
    for (std::size_t i = 0; i < input.layouts.size(); ++i) {
      const auto& source = input.layouts[i];require(source.id().value == i && source.context().binding == input.identity);
      // Initialization charges explicit token scans, descriptor fields/binding
      // bytes and controlled handle-array words. Metadata compilation and its
      // standard-container internals are separate from ordinary indexed paths.
      step(work, add(count(i), 1));
      if (work) work->admit(IndexWork{.scalar_fields=count(source.fields().size()), .scalar_bytes=count(source.context().binding.size())});
      data->layouts.push_back(registry.get(i));
    }
    const auto layout_id = [&](const TupleLayout& source) {
      step(work);const auto position = source.id().value;
      require(position < input.layouts.size() && source.same_token(input.layouts[position]));return position;
    };
    for (std::size_t i = 0; i < input.relations.size(); ++i) {
      step(work);const auto& source = input.relations[i];
      require(source.id.value == i && source.role >= RelationRole::physical_base && source.role <= RelationRole::visible);
      data->relations.push_back({source.role, LayoutId{layout_id(source.layout)}, source.node, source.base});
    }
    for (std::size_t i = 0; i < input.indexes.size(); ++i) {
      step(work);const auto& source = input.indexes[i];
      require(source.id.value == i && source.relation.value < data->relations.size());
      const auto from = layout_id(source.projection.source());const auto to = layout_id(source.projection.target());
      require(data->relations[source.relation.value].layout.value == from);
      AccountedProjection projection;
      for (std::size_t previous = 0; previous < i; ++previous) {
        step(work);
        if (source.projection.same_token(input.indexes[previous].projection)) { projection = data->indexes[previous].projection;break; }
      }
      if (!projection) {
        if (work) work->admit(IndexWork{.scalar_fields=add(add(count(source.projection.source().fields().size()),
            count(source.projection.target().fields().size())), count(source.projection.fields().size()))});
        prepare_vector<FieldId>(source.projection.fields().size(), work);
        projection = AccountedProjection::freeze(data->layouts[from], data->layouts[to], source.projection.fields(), tag(id));
      }
      data->indexes.push_back({source.relation, std::move(projection)});
    }
  } // Borrowed source-token registry is gone before this object is published.
  if(materialize) {
  for (std::size_t i = 0; i < data->relations.size(); ++i) {
    step(work);const auto& frozen = data->layouts[data->relations[i].layout.value];
    if (input.indexed) tables_.emplace_back(RelationId{i}, frozen, input.indexed->per_table);
    else tables_.emplace_back(RelationId{i}, frozen);
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
    if (input.indexed && input.collision_profile)
      detail::AccountedStorageTableTesting::collisions(tables_.back(), input.collision_profile == 1 ?
          detail::AccountedCollisionMode::same_bucket : detail::AccountedCollisionMode::same_full_hash);
#endif
  }
  for (const auto& binding : data->indexes) { step(work);indexes_.push_back(tables_[binding.relation.value].add_index(binding.projection, work)); }
  }
  // Publish only after every fallible layout, table and index construction.
  metadata_ = std::move(data);
}

AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* supplied)
    :metadata_(std::move(binding.metadata_)),owner_(next_owner()),
     tables_(resource::MemoryAllocator<AccountedStorageTable>(metadata().account,MemoryPurpose::immutable_metadata,tag(owner_))),
     indexes_(resource::MemoryAllocator<IndexId>(metadata().account,MemoryPurpose::immutable_metadata,tag(owner_))) {
  materialize(operation_work(metadata().indexed,supplied));
}
AccountedPlanStorage::AccountedPlanStorage(Binding binding,IndexWorkAllowance* work,ColdRebuild)
    :metadata_(std::move(binding.metadata_)),owner_(next_owner()),
     tables_(resource::MemoryAllocator<AccountedStorageTable>(metadata().account,MemoryPurpose::immutable_metadata,tag(owner_))),
     indexes_(resource::MemoryAllocator<IndexId>(metadata().account,MemoryPurpose::immutable_metadata,tag(owner_))) {
  // A distinct immutable cold context supplies this finite grant. This private
  // admission does not advertise it as the plan's ordinary per_operation cap.
  require(bool(metadata().indexed)==bool(work));
  require(!work || work->fixed_diagnostics());step(work);
  materialize(work);
}
void AccountedPlanStorage::materialize(IndexWorkAllowance* work) {
  const auto& data=metadata();
  prepare_vector<AccountedStorageTable>(data.relations.size(),work);prepare_vector<IndexId>(data.indexes.size(),work);
  tables_.reserve(data.relations.size());indexes_.reserve(data.indexes.size());
  for(std::size_t i=0;i<data.relations.size();++i) {
    step(work);const auto& layout=data.layouts[data.relations[i].layout.value];
    if(data.indexed)tables_.emplace_back(RelationId{i},layout,data.indexed->per_table);
    else tables_.emplace_back(RelationId{i},layout);
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
    if(data.indexed && data.collision_profile)
      detail::AccountedStorageTableTesting::collisions(tables_.back(),data.collision_profile==1?
          detail::AccountedCollisionMode::same_bucket:detail::AccountedCollisionMode::same_full_hash);
#endif
  }
  for(const auto& index:data.indexes) {step(work);indexes_.push_back(tables_[index.relation.value].add_index(index.projection,work));}
}

const AccountedPlanStorage::Metadata& AccountedPlanStorage::Binding::metadata() const {
  if(!metadata_)throw IndexFailure(IndexFault::invalid_storage);
  return *metadata_;
}
const resource::MemoryAccount& AccountedPlanStorage::Binding::account() const & {return metadata().account;}
std::span<const AccountedLayout> AccountedPlanStorage::Binding::layouts() const & {return metadata().layouts;}
const AccountedLayout& AccountedPlanStorage::Binding::layout(LayoutId id) const & {
  const auto& data=metadata();if(id.value>=data.layouts.size())throw IndexFailure(IndexFault::layout_mismatch);
  return data.layouts[id.value];
}
const AccountedProjection& AccountedPlanStorage::Binding::projection(IndexRequirementId id) const & {
  const auto& data=metadata();if(id.value>=data.indexes.size())throw IndexFailure(IndexFault::unknown_index);
  return data.indexes[id.value].projection;
}
PhysicalRoute AccountedPlanStorage::Binding::route() const {return metadata().route;}
std::string_view AccountedPlanStorage::Binding::physical_identity() const & {
  const auto& identity=metadata().identity;return {identity.data(),identity.size()};
}
std::size_t AccountedPlanStorage::Binding::relation_count() const {return metadata().relations.size();}
std::size_t AccountedPlanStorage::Binding::index_count() const {return metadata().indexes.size();}
AccountedPlanStorage::Binding AccountedPlanStorage::binding() const & {static_cast<void>(metadata());return Binding(metadata_);}

AccountedPlanStorage::AccountedPlanStorage(std::shared_ptr<const Metadata> metadata, StorageOwnerId owner,
    AccountedVector<AccountedStorageTable> tables, AccountedVector<IndexId> indexes) noexcept
    : metadata_(std::move(metadata)), owner_(owner), tables_(std::move(tables)), indexes_(std::move(indexes)) {}
AccountedPlanStorage& AccountedPlanStorage::operator=(AccountedPlanStorage&& other) noexcept {
  if (this != &other) { std::destroy_at(this);std::construct_at(this, std::move(other)); }
  return *this;
}
const AccountedPlanStorage::Metadata& AccountedPlanStorage::metadata() const {
  if (!metadata_) throw IndexFailure(IndexFault::invalid_storage);
  return *metadata_;
}
StorageOwnerId AccountedPlanStorage::owner() const { static_cast<void>(metadata());return owner_; }
StorageBackend AccountedPlanStorage::backend() const { return metadata().indexed ? StorageBackend::indexed_chained_v1 : StorageBackend::reference_ordered_v1; }
PhysicalRoute AccountedPlanStorage::route() const { return metadata().route; }
std::string_view AccountedPlanStorage::physical_identity() const & { return {metadata().identity.data(), metadata().identity.size()}; }
std::span<const AccountedLayout> AccountedPlanStorage::layouts() const & { return metadata().layouts; }
const AccountedLayout& AccountedPlanStorage::layout(LayoutId id) const & {
  const auto& data = metadata();if (id.value >= data.layouts.size()) throw IndexFailure(IndexFault::layout_mismatch);
  return data.layouts[id.value];
}
const AccountedPlanStorage::RelationBinding& AccountedPlanStorage::relation(RelationId id) const & {
  const auto& data = metadata();if (id.value >= data.relations.size()) throw IndexFailure(IndexFault::invalid_storage);
  return data.relations[id.value];
}
const AccountedProjection& AccountedPlanStorage::projection(IndexRequirementId id) const & {
  const auto& data = metadata();if (id.value >= data.indexes.size()) throw IndexFailure(IndexFault::unknown_index);
  return data.indexes[id.value].projection;
}
AccountedStorageTable& AccountedPlanStorage::table(RelationId id) & {
  static_cast<void>(metadata());if (id.value >= tables_.size()) throw IndexFailure(IndexFault::invalid_storage);
  return tables_[id.value];
}
const AccountedStorageTable& AccountedPlanStorage::table(RelationId id) const & {
  static_cast<void>(metadata());if (id.value >= tables_.size()) throw IndexFailure(IndexFault::invalid_storage);
  return tables_[id.value];
}
IndexId AccountedPlanStorage::index(IndexRequirementId id) const {
  static_cast<void>(metadata());if (id.value >= indexes_.size()) throw IndexFailure(IndexFault::unknown_index);
  return indexes_[id.value];
}
std::size_t AccountedPlanStorage::relation_count() const { static_cast<void>(metadata());return tables_.size(); }
std::size_t AccountedPlanStorage::index_count() const { static_cast<void>(metadata());return indexes_.size(); }
PlanStorageMemoryStatistics AccountedPlanStorage::memory_statistics() const {
  const auto& data = metadata();PlanStorageMemoryStatistics result;
  result.layouts = data.layouts.size();result.relations = tables_.size();result.index_bindings = indexes_.size();
  // Each attribution query scans the account's existing allocation list; it
  // does not allocate or sum all row/payload owners in this storage generation.
  result.shared_metadata = data.account.statistics_for(tag(data.owner));result.instance = data.account.statistics_for(tag(owner_));
  result.owned = {add(result.shared_metadata.current.allocations, result.instance.current.allocations),
      add(result.shared_metadata.current.requested_bytes, result.instance.current.requested_bytes),
      add(result.shared_metadata.current.payload_bytes, result.instance.current.payload_bytes)};
  return result;
}
AccountedPlanStorage AccountedPlanStorage::snapshot_copy(IndexWorkAllowance* supplied) const {
  // Explicit bulk copy: old and new state overlap under the same account.
  // Ordinary mutation rollback uses journals instead of this full snapshot.
  const auto& data = metadata();auto* work = operation_work(data.indexed, supplied);
  prepare_vector<AccountedStorageTable>(tables_.size(), work);prepare_vector<IndexId>(indexes_.size(), work);
  const auto id = next_owner();
  AccountedVector<AccountedStorageTable> tables{resource::MemoryAllocator<AccountedStorageTable>(data.account, MemoryPurpose::immutable_metadata, tag(id))};
  AccountedVector<IndexId> indexes{resource::MemoryAllocator<IndexId>(data.account, MemoryPurpose::immutable_metadata, tag(id))};
  tables.reserve(tables_.size());indexes.reserve(indexes_.size());
  for (const auto& table : tables_) { step(work);tables.push_back(table.snapshot_copy(work)); }
  for (const auto index : indexes_) { step(work);indexes.push_back(index); }
  return {metadata_, id, std::move(tables), std::move(indexes)};
}
void AccountedPlanStorage::check_invariants(IndexWorkAllowance* supplied) const {
  const auto& data = metadata();auto* work = operation_work(data.indexed, supplied);
  require(tables_.size() == data.relations.size() && indexes_.size() == data.indexes.size());
  for (std::size_t i = 0; i < data.layouts.size(); ++i) require(data.layouts[i].id().value == i);
  for (std::size_t i = 0; i < tables_.size(); ++i) {
    const auto& table = tables_[i];const auto& binding = data.relations[i];
    require(table.backend() == backend() && table.relation().value == i && binding.layout.value < data.layouts.size() &&
        table.layout().same_token(data.layouts[binding.layout.value]));
    if (data.indexed) require(table.indexed_limits() == std::optional<IndexedLimits>(data.indexed->per_table));
    table.check_invariants();
  }
  for (std::size_t i = 0; i < data.indexes.size(); ++i) {
    step(work);const auto& binding = data.indexes[i];require(binding.relation.value < tables_.size());
    require(tables_[binding.relation.value].projection(indexes_[i], work).same_token(binding.projection));
  }
}
}  // namespace crown::storage
