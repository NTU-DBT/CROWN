#include "crown/runtime/physical.hpp"
#include "memory_report_detail.hpp"
#include "crown/runtime/program.hpp"
#include "crown/runtime/window.hpp"

#include "crown/api/error.hpp"
#include "inspection_detail.hpp"
#include "validation_work.hpp"
#include "constraint_validation.hpp"
#include "workload_statistics_detail.hpp"
#include "storage_work.hpp"
#include "reoptimization_detail.hpp"
#include "../storage/accounted_index_scalar_work.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <atomic>
#include <map>
#include <set>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
constexpr resource::MemoryAttribution source_image_owner{resource::MemoryOwnerKind::capture,16};
// This explicit image operation has one selected balance. Indexed traversal
// additionally consumes the runtime's original (possibly suspended) lease.
struct SourceImageBudget {
  std::uint64_t limit, used=0;
  void take(std::uint64_t amount=1) {
    if(amount>limit-used)throw Error("source_image_work_limit","physical source image work grant exhausted");
    used+=amount;
  }
  void payload(storage::RowView values) {
    for(const auto& value:values.cells()) {
      take();
      if(const auto* text=std::get_if<std::string_view>(&value))take(text->size());
      else if(const auto* decimal=std::get_if<storage::InlineDecimal>(&value))take(decimal->parts().digits.size());
    }
  }
};
template<class T> void source_image_slots(storage::IndexWorkAllowance* work,std::size_t count) {
  if(!work)return;
  constexpr auto words=static_cast<std::uint64_t>((sizeof(T)+sizeof(void*)-1)/sizeof(void*));
  if(count>UINT64_MAX/words)throw storage::IndexFailure(storage::IndexFault::overflow);
  work->admit(storage::IndexWork{.pointer_slots=static_cast<std::uint64_t>(count)*words});
}
void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
void add_size(std::size_t& target,std::size_t amount) {
  require(amount<=std::numeric_limits<std::size_t>::max()-target,"storage_overflow","physical storage statistics exhausted");
  target+=amount;
}
void add_statistics(storage::ArenaStatistics& target,const storage::ArenaStatistics& value) {
  add_size(target.slots,value.slots); add_size(target.live_records,value.live_records);
  add_size(target.retained_records,value.retained_records); add_size(target.pins,value.pins);
  add_size(target.free_slots,value.free_slots); add_size(target.exhausted_slots,value.exhausted_slots);
}
}  // namespace

physical::SourceImage::SourceImage(const resource::MemoryAccount& account,std::uint64_t epoch,const CompiledProgram& source)
    :sequence(epoch),program(source),tables(resource::OwnerAllocator<Rows>(account,
        resource::MemoryPurpose::capture,source_image_owner)) {}

namespace {
std::uint64_t new_source_memory_owner() {
  static std::atomic<std::uint64_t> last{0};auto value=last.load(std::memory_order_relaxed);
  for (;;) {
    if(value==UINT64_MAX)throw resource::MemoryFailure(resource::MemoryFault::overflow);
    if(last.compare_exchange_weak(value,value+1,std::memory_order_relaxed))return value+1;
  }
}
template<class T> using MemoryVector=std::vector<T,resource::MemoryAllocator<T>>;
struct CompactRowLess {
  using is_transparent=void;
  bool operator()(const storage::AccountedRow& a,const storage::AccountedRow& b) const { return a.view()<b.view(); }
  bool operator()(const storage::AccountedRow& a,const Row& b) const { return a.view()<b; }
  bool operator()(const Row& a,const storage::AccountedRow& b) const { return a<b.view(); }
  bool operator()(const storage::AccountedRow& a,storage::RowView b) const {return a.view()<b;}
  bool operator()(storage::RowView a,const storage::AccountedRow& b) const {return a<b.view();}
};
template<class Failure> [[noreturn]] void present(const Failure& failure) { throw Error(std::string(failure.code()),failure.what()); }
}
struct PhysicalRuntime::Impl {
  // Per-occurrence std::map counts, distinct from the exact-node AVL helper.
  // Erased-node undo relabeling below can scan the account allocation list.
  using Counts=std::map<storage::AccountedRow,std::uint64_t,CompactRowLess,
      resource::MemoryAllocator<std::pair<const storage::AccountedRow,std::uint64_t>>>;
  PhysicalRuntimeOptions options;
  std::shared_ptr<detail::StorageWorkContext> storage_context;
  [[nodiscard]] storage::IndexWorkAllowance* work() const { return detail::compact_storage_work(storage_context); }
  SupportRuntime kernel;
  std::shared_ptr<detail::ObservationState> observation;
  workload::detail::State* workload;
  resource::MemoryAttribution attribution;
  MemoryVector<storage::AccountedStorageTable> sources;
  // Readable handles share the program's actual accounted native layouts.
  MemoryVector<storage::TupleLayout> source_layouts;
  MemoryVector<Counts> counts;
  std::uint64_t sequence=0;
  BuildMetrics build_metrics;
  InitializationContext initialization_context;
  bool updating=false, enforced_constraints=false;
  template<class Source> Impl(Source plan,PhysicalRuntimeOptions value,std::shared_ptr<detail::StorageWorkContext> context):options(value),storage_context(std::move(context)),kernel(std::move(plan),value.support,storage_context),observation(kernel.observation_state()),workload(&kernel.workload_state()),
      attribution{resource::MemoryOwnerKind::physical_source,new_source_memory_owner()},
      sources(resource::MemoryAllocator<storage::AccountedStorageTable>(storage_context->memory(),resource::MemoryPurpose::table_state,attribution)),
      source_layouts(resource::MemoryAllocator<storage::TupleLayout>(storage_context->memory(),resource::MemoryPurpose::immutable_metadata,attribution)),
      counts(resource::MemoryAllocator<Counts>(storage_context->memory(),resource::MemoryPurpose::source_counts,attribution)) {
    require(options.derivation_limit>0,"invalid_options","physical derivation limit must be positive");
    const auto& compiled=kernel.compiled_program(); const auto& catalog=compiled.source_catalog();
    const auto tables=catalog.tables.size();
    require(tables<=std::numeric_limits<std::size_t>::max()-compiled.relations().size() &&
        tables<=std::numeric_limits<std::size_t>::max()-compiled.layouts().size(),"storage_overflow","private source descriptors exhausted");
    if (auto* allowance=work()) {
      constexpr auto words=static_cast<std::uint64_t>((sizeof(storage::AccountedStorageTable)+sizeof(void*)-1)/sizeof(void*));
      const auto count=static_cast<std::uint64_t>(tables);
      require(count<=std::numeric_limits<std::uint64_t>::max()/words,"storage_overflow","physical source metadata admission overflow");
      allowance->admit(storage::IndexWork{.structural_steps=count,.pointer_slots=count*words});
    }
    sources.reserve(tables);source_layouts.reserve(tables);counts.reserve(compiled.inputs().size());
    for(std::size_t i=0;i<compiled.inputs().size();++i) counts.emplace_back(CompactRowLess{},Counts::allocator_type(
        storage_context->memory(),resource::MemoryPurpose::source_counts,
        resource::MemoryAttribution{resource::MemoryOwnerKind::physical_source,new_source_memory_owner()}));
    const auto append_source=[&](RelationId relation,storage::AccountedLayout layout) {
      if(auto* allowance=work()) {
        allowance->admit(storage::IndexWork{.structural_steps=1});
      }
      source_layouts.push_back(layout.descriptor());
      if (const auto& spec=compiled.options().indexed_storage) sources.emplace_back(relation,std::move(layout),spec->per_table);
      else sources.emplace_back(relation,std::move(layout));
    };
    for (std::size_t i=0;i<tables;++i) {
      for(const auto& column:catalog.tables[i].columns) {
        if(auto* allowance=work())allowance->admit(storage::IndexWork{.structural_steps=1});
        require(!column.nullable,"unsupported_nullability","classical tuple layouts require non-null fields");
      }
      const auto& source=compiled.sources()[i];append_source(source.relation,source.layout);
      for (const auto& constraint : catalog.tables[i].constraints)
        if (std::visit([](const auto& item) { return item.status==ConstraintStatus::enforced; },constraint)) enforced_constraints=true;
    }
  }
  void readable() const { require(!updating,"runtime_busy","a prepared physical update is active"); }
  void writable() const { readable(); require(kernel.ready(),"runtime_busy","result cursors pin the committed physical epoch"); }
  storage::AccountedStorageTable& source(TableId table) {
    require(table.value<sources.size(),"invalid_physical_update","source table is outside the catalog"); return sources[table.value];
  }
  const program::PhysicalInput& input(OccurrenceId occurrence) const {
    require(occurrence.value<kernel.compiled_program().inputs().size(),"invalid_input_port","physical plan has no such occurrence input port");
    return kernel.compiled_program().inputs()[occurrence.value];
  }
  physical::SourceImage source_image(physical::SourceImageLimits limits,std::uint64_t epoch,
      const std::optional<storage::AccountedStorageTable::Journal>* journal=nullptr,
      std::optional<TableId> changed=std::nullopt) const {
    SourceImageBudget budget{limits.work};budget.take();
    std::uint64_t rows=0;
    for(const auto& table:sources) {
      budget.take();
      if(table.size()>limits.rows-rows)throw Error("source_image_row_limit","physical source image row grant exhausted");
      rows+=table.size();
    }
    // Admit directory/row capacity before allocation. Each payload is scanned
    // and admitted before its deep native clone; no legacy Row export occurs.
    budget.take(sources.size());budget.take(rows);
    source_image_slots<physical::SourceImage::Rows>(work(),sources.size());
    physical::SourceImage image(storage_context->memory(),epoch,kernel.compiled_program());
    image.tables.reserve(sources.size());
    for(std::size_t i=0;i<sources.size();++i) {
      const auto& table=sources[i];
      image.tables.emplace_back(resource::OwnerAllocator<storage::AccountedTuple>(storage_context->memory(),
          resource::MemoryPurpose::capture,source_image_owner));
      source_image_slots<storage::AccountedTuple>(work(),table.size());
      auto& output=image.tables.back();output.reserve(table.size());
      // Only the changed table has an active source journal. Its reader owns
      // that exact journal grant; ordinary live iteration would reject it.
      auto cursor=journal && journal->has_value() && changed && changed->value==i
          ? journal->value().live() : table.live(work());
      for(;;) {
        budget.take();
        const auto entry=cursor.next_entry(work());
        if(!entry)break;
        const auto values=entry->tuple.values();budget.payload(values);
        if(auto* allowance=work())storage::detail::accounted_admit_tuple_copy(entry->tuple,*allowance);
        output.push_back(entry->tuple.layout().tuple(values,source_image_owner));
      }
    }
    image.work=budget.used;return image;
  }
  // Snapshots deep-copy funded tuples, then sort full values to preserve
  // historical ordered input replay across both storage backends.
  detail::NativeDatabase native_database() const {
    detail::NativeDatabase result(storage_context->memory(),attribution);result.tables.reserve(sources.size());
    for(const auto& source:sources) {
      auto rows=source.snapshot(work());
      // The earlier Database export inserted into ordered full-row sets.
      // Preserve that input order for both backends and insertion-replay builds.
      std::sort(rows.begin(),rows.end(),[](const auto& a,const auto& b){return a.values()<b.values();});
      result.tables.push_back(std::move(rows));
    }
    return result;
  }
  Database database() const {
    Database result; result.tables.resize(sources.size());
    for (std::size_t i=0;i<sources.size();++i)
      for (const auto& tuple : sources[i].snapshot(work())) result.tables[i].insert(storage::export_row(tuple.values()));
    return result;
  }
  PhysicalSnapshot snapshot(SupportSnapshot support) const {
    PhysicalSnapshot result{support.sequence,database(),std::move(support),{}};
    result.derivations.resize(counts.size());
    for (std::size_t i=0;i<counts.size();++i) {
      const auto& node=kernel.plan().nodes()[input(OccurrenceId{i}).node.value];
      auto& output=result.derivations[i]; output.reserve(counts[i].size());
      for (const auto& [row,count] : counts[i]) output.push_back({node.layout.descriptor().tuple(storage::export_row(row.view())),count});
    }
    return result;
  }
};

static_assert(std::is_nothrow_move_constructible_v<PhysicalPreview>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalPreview>);
static_assert(std::is_nothrow_move_constructible_v<PhysicalEpoch>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalEpoch>);

struct PhysicalRuntime::PendingUpdate::Data {
  enum class CountKind { inserted,changed,erased };
  struct CountUndo {
    CountKind kind;
    Impl::Counts* counts;
    Impl::Counts::iterator item;
    std::uint64_t before;
    Impl::Counts::node_type removed;
  };
  static_assert(std::is_nothrow_move_constructible_v<CountUndo>);
  std::shared_ptr<Impl> owner;
  detail::StorageWorkLease storage_lease;
  PhysicalPreview output;
  std::optional<storage::AccountedStorageTable::Journal> source;
  std::optional<SupportRuntime::PendingEpoch> logical;
  MemoryVector<CountUndo> undo;
  std::size_t next_route=0;
  bool routes_complete=false;
  detail::ObservationTicket observation_ticket;
  workload::detail::Ticket workload_ticket;
  // Optional bookkeeping records successful nested charges, never an inference
  // from coordinator/support counter magnitudes. Failed stage/charge is sticky
  // until this pending update closes.
  std::uint64_t observed_charged_support_work=0;
  bool observed_support_accounting_complete=true;
  Data(std::shared_ptr<Impl> value,const PhysicalUpdateView& update)
      :owner(std::move(value)),storage_lease(detail::storage_lease(owner->storage_context)),output{update.sequence,update.table,update.operation,false,{}, {},
          decltype(PhysicalPreview::derivations)(resource::OwnerAllocator<DerivationChange>(owner->storage_context->memory(),
              resource::MemoryPurpose::output_buffer,{resource::MemoryOwnerKind::output,0}))},
       undo(resource::MemoryAllocator<CountUndo>(owner->storage_context->memory(),resource::MemoryPurpose::journal_undo,owner->attribution)) {
    if (owner->observation) observation_ticket=owner->observation->begin(ObservationLayer::physical,update.sequence);
    workload_ticket=owner->workload->physical(update.table,update.operation);
  }
  ~Data() { rollback(); }
  Impl& active() const {
    require(owner && logical && logical->active(),"invalid_epoch","prepared physical update is closed"); return *owner;
  }
  void observe() const noexcept {
    if (!owner || !owner->observation) return;
    auto& observation=*owner->observation;
    const auto& metrics=output.metrics;
    observation.set(MetricId::physical_work_inclusive,metrics.work);
    if (observed_support_accounting_complete) {
      // Every successful charge is part of metrics.work, so this subtraction
      // partitions actual charged work even when unrelated scan work dominates.
      observation.set(MetricId::physical_work_exclusive,metrics.work-observed_charged_support_work);
    } else {
      // A logical stage may fail after partial work, or its completed work may
      // exceed the coordinator's remaining budget. Neither is an inclusive
      // physical total, even when unrelated coordinator work is numerically
      // larger than all observed support work.
      observation.unavailable(MetricId::physical_work_inclusive);
      observation.unavailable(MetricId::physical_work_exclusive);
    }
    observation.set(MetricId::physical_source_changes,metrics.source_changes);
    observation.set(MetricId::physical_aliases_visited,metrics.aliases_visited);
    observation.set(MetricId::physical_aliases_filtered,metrics.aliases_filtered);
    observation.set(MetricId::physical_derivation_changes,metrics.derivation_changes);
    observation.set(MetricId::physical_native_crossings,metrics.native_crossings);
    observation.set(MetricId::physical_constraint_rows,metrics.constraint_rows);
    observation.set(MetricId::physical_constraint_validations,metrics.constraint_validations);
  }
  void charge(std::uint64_t amount=1) {
    auto& work=output.metrics.work;
    require(amount<=std::numeric_limits<std::uint64_t>::max()-work,"resource_limit","physical work counter exhausted");
    const auto limit=owner->options.work_limit;
    require(!limit || (work<=*limit && amount<=*limit-work),"resource_limit","physical epoch work limit exceeded; previous state preserved");
    work+=amount;
  }
  void metric(std::uint64_t& counter,std::uint64_t amount=1) {
    // Every managed category is a subset of cumulative charged work.
    charge(amount);
    counter+=amount;
  }
  void rollback() noexcept {
    if (!owner) return;
    if (logical) logical->rollback();
    observe();
    for (auto it=undo.rbegin();it!=undo.rend();++it) {
      switch (it->kind) {
        case CountKind::inserted: it->counts->erase(it->item); break;
        case CountKind::changed: it->item->second=it->before; break;
        case CountKind::erased:
          it->removed.key().set_lifetime(resource::AllocationLifetime::active);
          it->counts->get_allocator().account().set_lifetime_containing(&it->removed.mapped(),
              resource::MemoryPurpose::source_counts,it->counts->get_allocator().attribution(),resource::AllocationLifetime::active);
          if (!it->counts->insert(std::move(it->removed)).inserted) std::terminate();
          break;
      }
    }
    undo.clear(); source.reset(); logical.reset();
    output.source.reset(); output.derivations.clear();
    if (owner->observation) owner->observation->finish(observation_ticket,ObservationOutcome::aborted);
    owner->workload->finish(workload_ticket,false);
    owner->updating=false; owner.reset();
  }
  void validate_constraints() {
    if (!owner->enforced_constraints) return;
    detail::NativeDatabase after(owner->storage_context->memory(),owner->attribution);
    after.tables.reserve(owner->sources.size());
    for (std::size_t i=0;i<owner->sources.size();++i) {
      metric(output.metrics.constraint_rows,static_cast<std::uint64_t>(owner->sources[i].size()));
      after.tables.push_back(owner->sources[i].snapshot(owner->work()));
    }
    metric(output.metrics.constraint_validations);
    // Complete after-state, including unused tables and self-FKs. All compact
    // snapshots, projections and ordered keys consume the original account.
    detail::validate_native_database(owner->kernel.plan().source_catalog(),after,
        owner->storage_context->memory(),owner->attribution);
  }
  // One alias prefix of one physical set input. Full source rows determine
  // source identity; each accepted projection changes its own derivation count.
  // Only 0<->1 changes reach logical support. Prefixes share this pending owner,
  // so self-join new-new terms see prior aliases without publishing an epoch.
  void route(OccurrenceId occurrence,std::uint64_t prefix,storage::RowView row,const RouteObserver& observer,EpochViewOptions view_options) {
    metric(output.metrics.aliases_visited);
    if (owner->observation) {
      owner->observation->route(occurrence.value,prefix);
      owner->observation->event(TraceKind::alias,0,0,owner->input(occurrence).node.value,occurrence.value,prefix);
    }
    const auto& input=owner->input(occurrence);
    auto tuple=owner->kernel.compiled_program().adapt_input(occurrence,row,owner->work());
    owner->workload->occurrence(occurrence,tuple.has_value());
    if (!tuple) { metric(output.metrics.aliases_filtered); return; }
    auto& counts=owner->counts[occurrence.value]; const auto found=counts.find(tuple->values());
    const auto before=found==counts.end()?std::uint64_t{0}:found->second;
    const bool add=output.operation==SetOperation::insert;
    if (add) require(before<owner->options.derivation_limit,"derivation_overflow","native tuple derivation count exceeds its exact limit");
    else require(before>0,"runtime_contract","physical erase has no alias derivation");
    const auto after=add?before+1:before-1;
    owner->workload->derivation(occurrence,before,after);
    const bool crossing=(before==0 || after==0);
    metric(output.metrics.derivation_changes);
    // Public immutable payload ownership stays under the original account;
    // operational count/stage paths keep their existing native tuple.
    output.derivations.push_back({occurrence,input.node,
        storage::Tuple::from_accounted(owner->kernel.plan().nodes()[input.node.value].layout.tuple(
            tuple->values(),{resource::MemoryOwnerKind::output,0})),before,after,crossing});
    if (before==0) {
      const auto [item,inserted]=counts.emplace(storage::AccountedRow::copy_of(owner->storage_context->memory(),tuple->values(),counts.get_allocator().attribution()),after);
      require(inserted,"runtime_contract","new physical derivation already exists");
      undo.push_back({CountKind::inserted,&counts,item,0,{}});
    } else if (after==0) {
      counts.get_allocator().account().set_lifetime_containing(&found->second,resource::MemoryPurpose::source_counts,
          counts.get_allocator().attribution(),resource::AllocationLifetime::retained);
      auto removed=counts.extract(found);removed.key().set_lifetime(resource::AllocationLifetime::retained);
      undo.push_back({CountKind::erased,&counts,{},before,std::move(removed)});
    } else {
      undo.push_back({CountKind::changed,&counts,found,before,{}}); found->second=after;
    }
    if (crossing) {
      metric(output.metrics.native_crossings);
      const auto before_work=logical->preview().metrics.work;
      const auto checkpoint=logical->checkpoint();
      if (owner->observation) observed_support_accounting_complete=false;
      require(logical->stage_native(input.node,*tuple),"runtime_contract","derivation zero crossing did not change native membership");
      const auto support_work=logical->preview().metrics.work-before_work;
      charge(support_work);
      if (owner->observation) {
        // charge() checked the full coordinator total, which already contains
        // all earlier nested charges; this subset cannot overflow independently.
        observed_charged_support_work+=support_work;
        observed_support_accounting_complete=true;
      }
      if (observer) {
        auto before_view=logical->stage_view(checkpoint,SnapshotSide::before,view_options);
        auto after_view=logical->stage_view(checkpoint,SnapshotSide::after,view_options);
        observer(occurrence,prefix,before_view,after_view,logical->stage_records(checkpoint));
      }
    }
  }
  void prepare(const storage::AccountedTuple& tuple,std::optional<TupleHandle> existing) {
    // begin_staged owns this complete Data until preparation succeeds. Any
    // failure unwinds that owner and runs ~Data's rollback before presentation.
    logical.emplace(owner->kernel.begin_epoch(output.sequence,output.operation));
    const bool add=output.operation==SetOperation::insert;
    owner->workload->physical_fact(existing.has_value()!=add);
    if (existing.has_value()==add) { routes_complete=true; return; }
    output.physical_changed=true; metric(output.metrics.source_changes);
    if (owner->observation) owner->observation->event(TraceKind::source_change,0,0,
        observation_no_id,observation_no_id,0,static_cast<std::uint64_t>(!add),static_cast<std::uint64_t>(add));
    auto& table=owner->source(output.table); source.emplace(table.journal(detail::owning_storage_work(owner->storage_context)));
    if (add) {
      const auto inserted=source->insert(tuple);
      require(inserted.inserted,"runtime_contract","physical source insertion duplicated membership");
      output.source.emplace(SourceRowChange{inserted.handle,table.pin(inserted.handle,owner->work())});
    } else {
      output.source.emplace(SourceRowChange{*existing,table.pin(*existing,owner->work())});
      require(source->erase(*existing),"runtime_contract","physical source deletion lost membership");
    }
    validate_constraints();
    const auto& routes=owner->kernel.plan().base_routes()[output.table.value];
    undo.reserve(routes.size()); output.derivations.reserve(routes.size());
    routes_complete=routes.empty(); observe();
  }
};

PhysicalRuntime::PendingUpdate::PendingUpdate(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
PhysicalRuntime::PendingUpdate::PendingUpdate(PendingUpdate&&) noexcept=default;
PhysicalRuntime::PendingUpdate& PhysicalRuntime::PendingUpdate::operator=(PendingUpdate&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
PhysicalRuntime::PendingUpdate::~PendingUpdate()=default;
bool PhysicalRuntime::PendingUpdate::active() const noexcept { return data_ && data_->owner && data_->logical && data_->logical->active(); }
bool PhysicalRuntime::PendingUpdate::stage_next(const RouteObserver& observer,EpochViewOptions options) try {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active());
  if (data_->routes_complete) return false;
  try {
    detail::StorageOperation storage_operation(data_->owner->storage_context,data_->storage_lease);
    const auto& routes=data_->owner->kernel.plan().base_routes()[data_->output.table.value];
    const auto position=data_->next_route;
    // The source pin owns the complete input row across calls and facade moves.
    data_->route(routes[position],static_cast<std::uint64_t>(position)+1,data_->output.source->tuple().values(),observer,options);
    ++data_->next_route; data_->routes_complete=data_->next_route==routes.size(); data_->observe(); return true;
  } catch (...) { data_->rollback(); throw; }
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
void PhysicalRuntime::PendingUpdate::rollback() noexcept { if (data_) data_->rollback(); }
const PhysicalPreview& PhysicalRuntime::PendingUpdate::preview() const {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active()); return data_->output;
}
const SupportEpoch& PhysicalRuntime::PendingUpdate::support() const {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active()); return data_->logical->preview();
}
PhysicalSnapshot PhysicalRuntime::PendingUpdate::snapshot() const try {
  require(bool(data_),"invalid_epoch","moved-from physical update");
  detail::StorageOperation storage_operation(data_->active().storage_context,data_->storage_lease);
  return data_->active().snapshot(data_->logical->snapshot());
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
physical::SourceImage PhysicalRuntime::PendingUpdate::source_image(physical::SourceImageLimits limits) const {
  require(bool(data_),"invalid_epoch","moved-from physical update");auto& d=data_->active();
  require(data_->routes_complete,"runtime_busy","source image requires fully drained alias routes");
  detail::StorageOperation operation(d.storage_context,data_->storage_lease);
  return d.source_image(limits,data_->output.sequence,&data_->source,data_->output.table);
}
SupportRuntime::EpochView PhysicalRuntime::PendingUpdate::view(SnapshotSide side,EpochViewOptions options) {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active());
  return data_->logical->view(side,options);
}
PhysicalEpoch PhysicalRuntime::PendingUpdate::commit() {
  require(bool(data_),"invalid_epoch","moved-from physical update"); auto& d=data_->active();
  require(data_->routes_complete,"runtime_busy","physical alias routes are not fully drained");
  // The logical token is private and validated above. All operations from this
  // point, including output movement and source/count undo cleanup, allocate
  // nothing; public driver reads remain busy until the entire barrier ends.
  data_->observe();
  auto support=data_->logical->commit();
  if (data_->source) data_->source->commit();
  data_->source.reset(); data_->undo.clear(); data_->logical.reset();
  PhysicalEpoch result{std::move(data_->output),std::move(support)};
  d.sequence=result.input.sequence; d.updating=false;
  d.workload->finish(data_->workload_ticket,true);
  if (d.observation) d.observation->finish(data_->observation_ticket,ObservationOutcome::committed);
  data_->owner.reset();
  return result;
}

PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options)
    :PhysicalRuntime(plan,options,detail::storage_context(plan,options.support.memory_limit_bytes)) {}
PhysicalRuntime::PhysicalRuntime(CompiledProgram source,PhysicalRuntimeOptions options) try
    :impl_([&] {
      auto context=detail::new_storage_context(source,options.support.memory_limit_bytes);detail::StorageOperation operation(context);
      auto plan=CompiledProgram::freeze(context->memory(),source,detail::compact_storage_work(context));
      detail::validate_storage_context(plan,context,options.support.memory_limit_bytes);
      return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,std::move(plan),options,context);
    }()) {
  if(impl_->observation)impl_->observation->initialize(impl_->initialization_context);
} catch(const storage::IndexFailure& failure) {present(failure);} catch(const storage::TableValidationFailure& failure) {present(failure);}
PhysicalRuntime::PhysicalRuntime(PlanSource plan,PhysicalRuntimeOptions options,std::shared_ptr<detail::StorageWorkContext> context) try
    :impl_([&] { return std::visit([&](auto& source) {detail::validate_storage_context(source,context,options.support.memory_limit_bytes);detail::StorageOperation operation(context);return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,std::move(source),options,context);},plan); }()) {
  if (impl_->observation) impl_->observation->initialize(impl_->initialization_context);
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
PhysicalRuntime PhysicalRuntime::initialize(PhysicalPlan plan,const Database& database,
    PhysicalRuntimeOptions options,BuildOptions build) {
  return initialize_at(std::move(plan),database,options,build,0);
}
PhysicalRuntime PhysicalRuntime::initialize(CompiledProgram source,const Database& database,
    PhysicalRuntimeOptions options,BuildOptions build) try {
  auto context=detail::new_storage_context(source,options.support.memory_limit_bytes);detail::StorageOperation operation(context);
  auto plan=CompiledProgram::freeze(context->memory(),source,detail::compact_storage_work(context));
  return initialize_at(std::move(plan),database,options,build,0,{},std::move(context));
} catch(const storage::IndexFailure& failure) {present(failure);} catch(const storage::TableValidationFailure& failure) {present(failure);}
PhysicalRuntime PhysicalRuntime::initialize_at(PlanSource plan,const Database& database,
    PhysicalRuntimeOptions options,BuildOptions build,std::uint64_t sequence,BuildMetrics prefix,
    std::shared_ptr<detail::StorageWorkContext> context) {
  return initialize_data(std::move(plan),database,options,build,sequence,prefix,std::move(context));
}
template<class DatabaseView>
PhysicalRuntime PhysicalRuntime::initialize_data(PlanSource plan,const DatabaseView& database,
    PhysicalRuntimeOptions options,BuildOptions build,std::uint64_t sequence,BuildMetrics prefix,
    std::shared_ptr<detail::StorageWorkContext> context) try {
  if (!context) context=std::visit([&](const auto& source){return detail::storage_context(source,options.support.memory_limit_bytes);},plan);
  detail::StorageOperation storage_operation(context);
  require(build.method==BuildMethod::direct || build.method==BuildMethod::insertion_replay,
      "invalid_options","unknown runtime initialization method");
  PhysicalRuntime result(std::move(plan),options,std::move(context)); auto& d=result.impl();
  BuildMetrics metrics=prefix; detail::build_charge(metrics,build);
  const auto& compiled=d.kernel.compiled_program(); const auto& catalog=d.kernel.plan().source_catalog();
  require(database.tables.size()==catalog.tables.size(),"invalid_database","database/catalog table count differs");
  // Validate the complete final snapshot before either unpublished build path.
  // Per-prefix public inserts cannot initialize valid cyclic foreign keys.
  detail::charge_database_validation(catalog,database,[&](std::uint64_t amount) { detail::build_charge(metrics,build,amount); });
  for (const auto& table : database.tables)
    detail::build_metric(metrics,build,metrics.constraint_rows,static_cast<std::uint64_t>(table.size()));
  detail::validate_native_database(catalog,database,d.storage_context->memory(),d.attribution);
  MemoryVector<detail::NativeSeed> seeds(resource::MemoryAllocator<detail::NativeSeed>(
      d.storage_context->memory(),resource::MemoryPurpose::scratch,d.attribution));
  const auto append_seed=[&](NodeId node,storage::AccountedTuple tuple) {
    if(seeds.size()==seeds.capacity()) {
      const auto capacity=seeds.capacity();
      if(capacity>SIZE_MAX/2)throw storage::IndexFailure(storage::IndexFault::overflow);
      const auto next=capacity?capacity*2:8;
      constexpr auto words=static_cast<std::uint64_t>((sizeof(detail::NativeSeed)+sizeof(void*)-1)/sizeof(void*));
      if(next>UINT64_MAX/words)throw storage::IndexFailure(storage::IndexFault::overflow);
      if(auto* allowance=d.work())allowance->admit(storage::IndexWork{.pointer_slots=static_cast<std::uint64_t>(next)*words});
      seeds.reserve(next);
    }
    seeds.push_back({node,std::move(tuple)});
  };
  for (std::size_t i=0;i<database.tables.size();++i) {
    auto& source=d.sources[i];
    for (const auto& row : database.tables[i]) {
      detail::build_metric(metrics,build,metrics.source_rows);
      const auto source_tuple=source.layout().tuple(detail::validation_values(row),d.attribution);
      require(source.insert(source_tuple, d.work()).inserted,"runtime_contract","initial source row duplicated membership");
      for (const auto occurrence : compiled.base_routes()[i]) {
        detail::build_metric(metrics,build,metrics.adapter_visits);
        const auto& input=d.input(occurrence);
        auto tuple=compiled.adapt_input(occurrence,source_tuple.values(),d.work());
        if (!tuple) { detail::build_metric(metrics,build,metrics.adapter_rejections); continue; }
        detail::build_metric(metrics,build,metrics.derivation_changes);
        auto& counts=d.counts[occurrence.value]; const auto found=counts.find(tuple->values());
        const auto before=found==counts.end()?std::uint64_t{0}:found->second;
        require(before<options.derivation_limit,"derivation_overflow","initial derivation count exceeds its configured exact limit");
        if (found==counts.end()) {
          counts.emplace(storage::AccountedRow::copy_of(d.storage_context->memory(),tuple->values(),counts.get_allocator().attribution()),1);
          detail::build_charge(metrics,build,static_cast<std::uint64_t>(tuple->values().size()));
          append_seed(input.node,std::move(*tuple));
        } else ++found->second;
      }
    }
  }
  d.kernel.initialize_native(seeds,build,metrics);
  detail::build_metric(metrics,build,metrics.storage_records,metrics.source_rows);
  // Source tables currently have only primary full-row identity. Account any
  // registered secondary indexes explicitly if this backend is extended.
  for (const auto& source : d.sources) {
    for (const auto index : source.indices(d.work())) {
      static_cast<void>(index);
      detail::build_metric(metrics,build,metrics.index_memberships,static_cast<std::uint64_t>(source.size()));
    }
  }
  d.build_metrics=metrics; d.kernel.seed_sequence(sequence); d.sequence=sequence;
  d.initialization_context={InitializationRoute::initialized_database,build};
  if (d.observation) d.observation->initialize(d.initialization_context);
  return result;
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build) const {
  auto& d=impl();d.writable();
  return rebuilt(build,detail::storage_context(d.kernel.plan(),d.options.support.memory_limit_bytes,d.storage_context->memory()));
}
recovery::EncodedImage PhysicalRuntime::checkpoint_image(const recovery::ImageBinding& binding,
    recovery::ImageLimits limits) const {
  const auto& d=impl();d.writable();detail::StorageOperation operation(d.storage_context);
  if(d.sources.size()>limits.tables)throw recovery::ImageFailure(recovery::ImageFault::limit);
  if(limits.work==0)throw recovery::ImageFailure(recovery::ImageFault::work);
  std::uint64_t rows=0;
  for(const auto& source:d.sources) {
    if(source.size()>limits.rows-rows || source.layout().fields().size()>limits.fields)
      throw recovery::ImageFailure(recovery::ImageFault::limit);
    rows+=source.size();
  }
  // Codec work accounting excludes this deep snapshot/sort. The original
  // query account and current native storage allowance still govern it.
  const auto account=d.storage_context->memory();const auto database=d.native_database();
  using Views=std::vector<storage::RowView,resource::MemoryAllocator<storage::RowView>>;
  std::vector<Views,resource::MemoryAllocator<Views>> views(resource::MemoryAllocator<Views>(
      account,resource::MemoryPurpose::recovery_log,recovery::image_owner));
  std::vector<recovery::ImageTableView,resource::MemoryAllocator<recovery::ImageTableView>> tables(
      resource::MemoryAllocator<recovery::ImageTableView>(account,resource::MemoryPurpose::recovery_log,recovery::image_owner));
  views.reserve(database.tables.size());tables.reserve(database.tables.size());
  for(const auto& table:database.tables) {
    views.emplace_back(resource::MemoryAllocator<storage::RowView>(account,resource::MemoryPurpose::recovery_log,recovery::image_owner));
    auto& values=views.back();values.reserve(table.size());
    for(const auto& row:table)values.push_back(row.values());
    tables.push_back({values});
  }
  return recovery::encode_image(account,{binding,d.sequence},tables,limits);
}
PhysicalRuntime PhysicalRuntime::restore_image(CompiledProgram source,std::string_view bytes,
    PhysicalRuntimeOptions options,BuildOptions build,recovery::ImageLimits limits,const recovery::ImageBinding& binding,
    std::shared_ptr<detail::StorageWorkContext> context,const WindowCheckpoint* window,std::uint64_t matching_work) try {
  detail::StorageOperation operation(context);
  const auto database=recovery::decode_image(context->memory(),bytes,binding,limits);
  if(window) {
    const auto check=[](bool value,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
      if(!value)throw recovery::ImageFailure(fault);
    };
    auto remaining=matching_work;
    const auto charge=[&](std::uint64_t amount) {check(amount<=remaining,recovery::ImageFault::work);remaining-=amount;};
    const auto account=context->memory();
    using Flags=std::vector<unsigned char,resource::MemoryAllocator<unsigned char>>;
    using Counts=std::vector<std::uint64_t,resource::MemoryAllocator<std::uint64_t>>;
    charge(1);charge(database.tables.size());
    Flags managed(database.tables.size(),0,Flags::allocator_type(account,resource::MemoryPurpose::scratch,recovery::image_owner));
    Counts counts(database.tables.size(),0,Counts::allocator_type(account,resource::MemoryPurpose::scratch,recovery::image_owner));
    for(const auto table:window->options.managed_tables) {
      charge(1);check(table.value<managed.size() && !managed[table.value]);managed[table.value]=1;
    }
    check(!window->options.managed_tables.empty());
    struct Key {TableId table;storage::RowView values;};
    const auto less=[&](const Key& a,const Key& b) {
      charge(1);if(a.table!=b.table)return a.table<b.table;
      charge(a.values.size());charge(b.values.size());return a.values<b.values;
    };
    using Keys=std::set<Key,decltype(less),resource::MemoryAllocator<Key>>;
    Keys expected(less,Keys::allocator_type(account,resource::MemoryPurpose::scratch,recovery::image_owner));
    for(const auto& row:window->counts) {
      charge(1);charge(row.values.size());check(row.table.value<managed.size() && managed[row.table.value]);
      check(expected.insert({row.table,row.values.view()}).second);check(counts[row.table.value]<UINT64_MAX);
      ++counts[row.table.value];
    }
    for(const auto table:window->options.managed_tables) {
      charge(1);check(database.tables[table.value].size()==counts[table.value]);
      for(const auto& row:database.tables[table.value]) {
        charge(1);charge(row.values().size());check(expected.contains({table,row.values()}));
      }
    }
  }
  auto plan=CompiledProgram::freeze(context->memory(),source,detail::compact_storage_work(context));
  return initialize_data(std::move(plan),database,options,build,database.manifest.epoch,{},std::move(context));
} catch(const storage::IndexFailure& failure) {present(failure);}
  catch(const storage::TableValidationFailure& failure) {present(failure);}
PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build,std::shared_ptr<detail::StorageWorkContext> context) const try {
  return rebuilt_with_program(impl().kernel.plan(),build,std::move(context));
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
PhysicalRuntime PhysicalRuntime::rebuilt_for(const planner::MinimumHeightCandidate& candidate,BuildOptions build,
    const program::ReplanLimits& replan,std::shared_ptr<detail::StorageWorkContext> context) const {
  auto& d=impl();d.writable();
  // Native lowering independently checks typed candidate/source identity. It
  // retains this complete admitted SQL/CQ source and funds the new graph in
  // the same original account; no exported row/program DTO is imported here.
  auto target=CompiledProgram::replan(d.kernel.plan(),candidate,replan);
  return rebuilt_with_program(std::move(target),build,std::move(context));
}
PhysicalRuntime PhysicalRuntime::rebuilt_with_program(CompiledProgram target,BuildOptions build,
    std::shared_ptr<detail::StorageWorkContext> context) const try {
  auto& d=impl(); d.writable();
  detail::validate_storage_context(target,context,d.options.support.memory_limit_bytes);
  if (context->memory().statistics().owner!=d.storage_context->memory().statistics().owner)
    throw resource::MemoryFailure(resource::MemoryFault::contract);
  detail::StorageOperation source_operation(d.storage_context);
  detail::StorageOperation target_operation(context);
  require(build.method==BuildMethod::direct || build.method==BuildMethod::insertion_replay,
      "invalid_options","unknown runtime initialization method");
  BuildMetrics prefix; detail::build_charge(prefix,build);
  // Consult the cumulative budget before materializing either the intermediate
  // tuple-vector copy or the final owning source sets.
  for (const auto& source : d.sources) {
    detail::build_charge(prefix,build);
    const auto fields=source.layout().fields().size();
    require(fields<=(std::numeric_limits<std::size_t>::max()-3)/2,"resource_limit","rebuild row-width accounting exhausted");
    detail::build_charge(prefix,build,detail::validation_product(source.size(),2*fields+3));
  }
  const auto database=d.native_database();
  auto result=initialize_data(std::move(target),database,d.options,build,d.sequence,prefix,std::move(context));
  result.impl().initialization_context.route=InitializationRoute::rebuilt_snapshot;
  if (result.impl().observation) result.impl().observation->initialize(result.impl().initialization_context);
  return result;
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
PhysicalRuntime::~PhysicalRuntime()=default;
PhysicalRuntime::PhysicalRuntime(PhysicalRuntime&&) noexcept=default;
PhysicalRuntime& PhysicalRuntime::operator=(PhysicalRuntime&& other) noexcept {
  if (this!=&other) impl_=std::move(other.impl_);
  return *this;
}
PhysicalRuntime::Impl& PhysicalRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from physical runtime"); return *impl_; }
const CompiledProgram& PhysicalRuntime::plan() const { return impl().kernel.plan(); }
const CompiledProgram& PhysicalRuntime::compiled_program() const { return impl().kernel.compiled_program(); }
resource::MemoryStatistics PhysicalRuntime::accounted_memory_statistics() const { return impl().kernel.accounted_memory_statistics(); }
const PhysicalRuntimeOptions& PhysicalRuntime::options() const { return impl().options; }
SupportOwnerId PhysicalRuntime::owner() const { return impl().kernel.owner(); }
std::uint64_t PhysicalRuntime::sequence() const { return impl().sequence; }
bool PhysicalRuntime::ready() const { const auto& d=impl(); return !d.updating && d.kernel.ready(); }
bool PhysicalRuntime::has_answer() const { auto& d=impl(); d.readable(); return d.kernel.has_answer(); }
const storage::TupleLayout& PhysicalRuntime::source_layout(TableId table) const { auto& d=impl();static_cast<void>(d.source(table));return d.source_layouts[table.value]; }
const storage::TupleLayout& PhysicalRuntime::result_layout(ResultView view) const { return impl().kernel.result_layout(view); }
PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare(const PhysicalSetUpdate& update) {
  return prepare_observed(update,{},{});
}
PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare_observed(const PhysicalSetUpdate& update,const RouteObserver& observer,EpochViewOptions options) {
  auto pending=begin_staged(update);
  while (pending.stage_next(observer,options)) {}
  return pending;
}
PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalSetUpdate& update) {
  return begin_staged(PhysicalUpdateView::borrow(update));
}
PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalUpdateView& update) try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.writable();
  require(d.sequence!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","physical update sequence exhausted");
  require(update.sequence==d.sequence+1,"invalid_sequence","physical update sequence must be contiguous from one");
  require(update.operation==SetOperation::insert || update.operation==SetOperation::erase,"invalid_physical_update","unknown physical set operation");
  auto& table=d.source(update.table); detail::validate_native_row(d.kernel.plan().source_catalog(),update.table,update.values);
  const auto tuple=table.layout().tuple(update.values); const auto existing=table.find(tuple, d.work());
  auto data=resource::make_accounted_unique<PendingUpdate::Data>(d.attribution,d.storage_context->memory(),resource::MemoryPurpose::journal_undo,impl_,update);
  d.updating=true; data->prepare(tuple,existing); return PendingUpdate(std::move(data));
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
// Even a physical no-op pays row validation/import/probe/owner admission;
// the selected coordinator metrics can remain zero for that committed input.
PhysicalEpoch PhysicalRuntime::apply(const PhysicalSetUpdate& update) { return prepare(update).commit(); }
PhysicalEpoch PhysicalRuntime::apply_view(const PhysicalUpdateView& update) {
  auto pending=begin_staged(update);while(pending.stage_next({},{})) {}return pending.commit();
}
SupportRuntime::ResultCursor PhysicalRuntime::results(ResultCursorOptions options) const {
  auto& d=impl(); d.readable(); return d.kernel.results(options,ResultView::sql);
}
SupportRuntime::ResultCursor PhysicalRuntime::core_results(ResultCursorOptions options) const {
  auto& d=impl(); d.readable(); return d.kernel.results(options,ResultView::core);
}
SupportRuntime::EpochView PhysicalRuntime::current_view(EpochViewOptions options) const {
  auto& d=impl(); d.readable(); return d.kernel.current_view(options);
}
SupportRuntime::ResultCursor PhysicalRuntime::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultCursorOptions options) const {
  auto& d=impl(); d.readable(); return d.kernel.completions(fixed,fragment,options);
}
SupportRuntime::ResultCursor PhysicalRuntime::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCursorOptions options) const {
  auto& d=impl(); d.readable(); return d.kernel.witnesses(fixed,std::move(fragment),options);
}
PhysicalSnapshot PhysicalRuntime::snapshot() const try {
  detail::StorageOperation storage_operation(impl().storage_context); auto& d=impl(); d.readable(); return d.snapshot(d.kernel.snapshot()); } catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
physical::SourceImage PhysicalRuntime::source_image(physical::SourceImageLimits limits) const {
  auto& d=impl();d.readable();detail::StorageOperation operation(d.storage_context);
  return d.source_image(limits,d.sequence);
}
std::uint64_t PhysicalRuntime::derivation_count(OccurrenceId occurrence,const Row& values) const {
  auto& d=impl(); d.readable(); const auto& input=d.input(occurrence); d.kernel.plan().nodes()[input.node.value].layout.descriptor().validate(values);
  const auto& counts=d.counts[occurrence.value]; const auto found=counts.find(values); return found==counts.end()?0:found->second;
}
std::optional<TupleHandle> PhysicalRuntime::find_source(TableId table,const Row& values) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); const auto& source=d.source(table);d.source_layouts[table.value].validate(values);return source.find(source.layout().tuple(values), d.work());
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
std::optional<storage::AccountedTuple> PhysicalRuntime::get_source(TableId table,TupleHandle handle) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); const auto& source=d.source(table);const auto* tuple=source.get(handle,d.work());
  if(!tuple)return {};
  return tuple->layout().tuple(tuple->values(),{resource::MemoryOwnerKind::output,source.owner().value});
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
std::optional<SupportHandle> PhysicalRuntime::find_support(NodeId node,SupportRole role,const Row& values) const {
  auto& d=impl(); d.readable(); return d.kernel.find(node,role,values);
}
std::optional<storage::Tuple> PhysicalRuntime::get_support(SupportHandle handle) const {
  auto& d=impl(); d.readable(); return d.kernel.get(handle);
}
PhysicalStorageStatistics PhysicalRuntime::storage_statistics() const {
  auto& d=impl(); d.readable(); PhysicalStorageStatistics result{{},d.kernel.storage_statistics(),0};
  for (const auto& table : d.sources) add_statistics(result.source,table.arena_statistics());
  for (const auto& counts : d.counts) add_size(result.derivation_keys,counts.size());
  return result;
}
InitializationContext PhysicalRuntime::initialization_context() const { return impl().initialization_context; }
const BuildMetrics& PhysicalRuntime::initialization_metrics() const { return impl().build_metrics; }
CanonicalPhysicalState PhysicalRuntime::canonical_state() const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable();
  CanonicalPhysicalState result{d.kernel.canonical_state(),d.sequence,d.database().tables,{}};
  result.derivations.resize(d.counts.size());
  for (std::size_t i=0;i<d.counts.size();++i)
    for (const auto& [key,count] : d.counts[i]) result.derivations[i].push_back({storage::export_row(key.view()),count});
  return result;
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
// Independently recompute projected counts from sources, including a
// repeated base snapshot/adaptation per alias. Report limits are coarse.
InvariantReport PhysicalRuntime::inspect_invariants(InspectionOptions options) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable();
  auto support=d.kernel.inspect_invariants(options);
  if (!support.complete) return support;
  detail::InspectionContext context(options,std::move(support));
  const auto issue=[&](InvariantCode code,InvariantComponent component,std::optional<TableId> table,
      std::optional<OccurrenceId> occurrence,std::optional<NodeId> node,storage::RowView key,
      std::optional<std::uint64_t> expected={},std::optional<std::uint64_t> actual={}) {
    InvariantIssue item{}; item.code=code; item.component=component; item.table=table;
    item.occurrence=occurrence; item.node=node; item.key=context.key(key); item.expected=expected; item.actual=actual;
    context.add(std::move(item));
  };
  try {
    context.charge();
    if (d.sequence!=d.kernel.sequence())
      issue(InvariantCode::sequence,InvariantComponent::sequence,{},{},{},{},d.sequence,d.kernel.sequence());
    detail::NativeDatabase database(context.account,invariant_attribution); database.tables.reserve(d.sources.size());
    for (std::size_t i=0;i<d.sources.size();++i) {
      const auto& source=d.sources[i]; const auto arena=source.arena_statistics();
      context.charge(static_cast<std::uint64_t>(arena.slots));
      context.charge(static_cast<std::uint64_t>(source.size()));
      context.charge(detail::validation_product(source.size(),source.layout().fields().size()+1));
      try { source.check_invariants(); }
      catch (const Error&) { issue(InvariantCode::storage,InvariantComponent::storage,TableId{i},{},{},{}); }
      catch (const storage::TableValidationFailure&) { issue(InvariantCode::storage,InvariantComponent::storage,TableId{i},{},{},{}); }
      catch (const storage::IndexFailure&) { issue(InvariantCode::storage,InvariantComponent::storage,TableId{i},{},{},{}); }
      add_size(context.report.statistics.source_storage_records,arena.live_records);
      auto rows=source.snapshot(d.work());
      for (const auto& tuple : rows) { static_cast<void>(tuple); context.charge(); }
      std::sort(rows.begin(),rows.end(),[](const auto& a,const auto& b){return a.values()<b.values();});
      database.tables.push_back(std::move(rows));
      add_size(context.report.statistics.source_rows,source.size());
      for (const auto index : source.indices(d.work())) {
        for (const auto& key : source.keys(index, d.work())) {
          context.charge(); const auto members=source.bucket(index,key, d.work());
          context.charge(static_cast<std::uint64_t>(members.size()));
          add_size(context.report.statistics.index_memberships,members.size());
        }
      }
    }
    try {
      detail::charge_database_validation(d.kernel.plan().source_catalog(),database,[&](std::uint64_t amount) { context.charge(amount); });
      detail::validate_native_database(d.kernel.plan().source_catalog(),database,context.account,invariant_attribution);
    } catch (const Error& error) {
      if (error.code()=="resource_limit") { context.report.complete=false; return std::move(context.report); }
      issue(InvariantCode::invalid_source,InvariantComponent::source,{},{},{},{});
    }
    std::size_t widest=0;
    for (const auto& node : d.kernel.plan().nodes()) widest=std::max(widest,node.scope.size());
    require(widest<=std::numeric_limits<std::size_t>::max()-2,"resource_limit","inspection row-width accounting exhausted");
    context.charge(detail::validation_product(context.report.statistics.native_records,widest+2));
    for (std::size_t i=0;i<d.counts.size();++i) {
      const OccurrenceId occurrence{i}; const auto& input=d.input(occurrence);
      auto expected=detail::inspection_counts<std::uint64_t>(context.account);
      for (const auto& source : d.sources[input.base.value].snapshot(d.work())) {
        context.charge(); const auto tuple=d.kernel.compiled_program().adapt_input(occurrence,source.values(),d.work());
        if (tuple) {
          const auto values=tuple->values();
          auto& count=expected.try_emplace(values,std::uint64_t{0}).first->second;
          if (count==std::numeric_limits<std::uint64_t>::max()) {
            issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,values,{},count);
          } else ++count;
        }
      }
      const auto& actual=d.counts[i]; add_size(context.report.statistics.derivation_keys,actual.size());
      for (const auto& [key,count] : expected) {
        context.charge(); const auto found=actual.find(key);
        if (found==actual.end() || found->second!=count)
          issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,key.view(),
              count,found==actual.end()?std::nullopt:std::optional<std::uint64_t>{found->second});
      }
      for (const auto& [key,count] : actual) {
        context.charge();
        if (!expected.contains(key))
          issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,key.view(),0,count);
      }
      const auto native=d.kernel.record_rows(input.node);
      for (const auto& key : native) {
        context.charge();
        if (!expected.contains(key)) issue(InvariantCode::unexpected_record,InvariantComponent::record,input.base,occurrence,input.node,key.view(),0,1);
      }
      for (const auto& [key,count] : expected) {
        static_cast<void>(count); context.charge();
        if (!native.contains(key)) issue(InvariantCode::missing_record,InvariantComponent::record,input.base,occurrence,input.node,key.view(),1,0);
      }
    }
  } catch (const detail::InspectionStop&) { context.report.complete=false; }
  return std::move(context.report);
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
#ifdef CROWN_RUNTIME_TESTING
void RuntimeTestProbe::seed_physical_sequence(PhysicalRuntime& runtime,std::uint64_t sequence) {
  auto& d=runtime.impl(); d.writable(); d.kernel.seed_sequence(sequence); d.sequence=sequence;
}
SupportRuntime& RuntimeTestProbe::support(PhysicalRuntime& runtime) { return runtime.impl().kernel; }
std::uint64_t RuntimeTestProbe::set_derivation(PhysicalRuntime& runtime,OccurrenceId occurrence,const Row& key,std::uint64_t count) {
  auto& d=runtime.impl(); d.readable(); static_cast<void>(d.input(occurrence));
  const auto found=d.counts[occurrence.value].find(key);
  require(found!=d.counts[occurrence.value].end(),"invalid_probe","derivation corruption probe key is absent");
  return std::exchange(found->second,count);
}
#endif
// Full fail-fast recomputation, not a cheap flag check. Native snapshots,
// expected row maps and record sets all use the original account.
void PhysicalRuntime::check_invariants() const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable();
  require(d.sequence==d.kernel.sequence(),"runtime_contract","physical and logical sequence differ");
  d.kernel.check_invariants(); for (const auto& source : d.sources) source.check_invariants();
  const auto database=d.native_database(); detail::validate_native_database(d.kernel.plan().source_catalog(),database,
      d.storage_context->memory(),invariant_attribution);
  for (std::size_t i=0;i<d.counts.size();++i) {
    const OccurrenceId occurrence{i}; const auto& input=d.input(occurrence); auto expected=detail::inspection_counts<std::uint64_t>(d.storage_context->memory());
    for (const auto& source : d.sources[input.base.value].snapshot(d.work())) {
      const auto tuple=d.kernel.compiled_program().adapt_input(occurrence,source.values(),d.work());
      if (tuple) {
        auto& count=expected.try_emplace(tuple->values(),std::uint64_t{0}).first->second;
        require(count<d.options.derivation_limit,"runtime_contract","recomputed derivation count exceeds limit"); ++count;
      }
    }
    require(expected.size()==d.counts[i].size(),"runtime_contract","physical derivation key count differs from recomputation");
    for(const auto& [key,count]:expected) {
      const auto found=d.counts[i].find(key);
      require(found!=d.counts[i].end() && found->second==count,"runtime_contract","physical derivation map differs from source-row recomputation");
    }
    const auto native=d.kernel.record_rows(input.node);
    require(native.size()==expected.size(),"runtime_contract","native membership differs from derivation keys");
    for (const auto& [row,count] : expected) {
      static_cast<void>(count); require(native.contains(row),"runtime_contract","positive derivation has no native row");
    }
  }
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
std::shared_ptr<detail::ObservationState> PhysicalRuntime::observation_state() const { return impl().observation; }
std::optional<CursorObservation> PhysicalRuntime::last_cursor_observation() const { return impl().kernel.last_cursor_observation(); }
CommittedStateGauges PhysicalRuntime::committed_state_gauges() const {
  const auto& d=impl();d.readable();auto result=d.kernel.committed_state_gauges();
  result.base_tuples={0,MetricAvailability::available,false};result.bases.reserve(d.sources.size());
  for(std::size_t i=0;i<d.sources.size();++i){
    const auto count=static_cast<std::uint64_t>(d.sources[i].size());result.bases.push_back({TableId{i},count});
    if(count>UINT64_MAX-result.base_tuples.value){result.base_tuples.value=UINT64_MAX;result.base_tuples.saturated=true;}
    else result.base_tuples.value+=count;
  }
  return result;
}
CapturedStateGauges PhysicalRuntime::capture_state_gauges() const {
  const auto& d=impl();d.readable();auto result=d.kernel.capture_state_gauges();
  result.base_tuples={0,MetricAvailability::available,false};result.bases.reserve(d.sources.size());
  for(std::size_t i=0;i<d.sources.size();++i){
    const auto count=static_cast<std::uint64_t>(d.sources[i].size());result.bases.push_back({TableId{i},count});
    if(count>UINT64_MAX-result.base_tuples.value){result.base_tuples.value=UINT64_MAX;result.base_tuples.saturated=true;}
    else result.base_tuples.value+=count;
  }
  return result;
}
ObservationSnapshot PhysicalRuntime::observations() const {
  auto result=impl().kernel.observations(); result.initialization=impl().initialization_context; return result;
}
ObservationTrace PhysicalRuntime::observation_trace() const {
  auto result=impl().kernel.observation_trace(); result.snapshot.initialization=impl().initialization_context; return result;
}
CapturedObservationTrace PhysicalRuntime::capture_observation_trace() const {
  auto result=impl().kernel.capture_observation_trace();result.snapshot.initialization=impl().initialization_context;return result;
}
bool PhysicalRuntime::same_sources(const PhysicalRuntime& other,reoptimization::detail::Budget& budget) const {
  auto& left=impl();auto& right=other.impl();left.writable();right.writable();
  detail::StorageOperation left_operation(left.storage_context),right_operation(right.storage_context);
  budget.charge();
  if(left.sequence!=right.sequence || left.sources.size()!=right.sources.size())return false;
  for(std::size_t i=0;i<left.sources.size();++i) {
    budget.charge();
    if(left.sources[i].size()!=right.sources[i].size())return false;
    auto values=reoptimization::detail::rows(left.storage_context->memory(),budget);
    {
      auto cursor=left.sources[i].live(left.work());
      while(auto row=cursor.next_entry(left.work())) {
        budget.row(row->tuple.values(),true);
        if(!values.insert(storage::AccountedRow::copy_of(left.storage_context->memory(),row->tuple.values(),reoptimization::detail::attribution)).second)return false;
      }
    }
    auto cursor=right.sources[i].live(right.work());
    while(auto row=cursor.next_entry(right.work())) {
      budget.row(row->tuple.values(),true);
      auto probe=storage::AccountedRow::copy_of(left.storage_context->memory(),row->tuple.values(),reoptimization::detail::attribution);
      const auto match=values.find(probe);if(match==values.end())return false;values.erase(match);
    }
    if(!values.empty())return false;
  }
  return true;
}
}  // namespace crown::runtime

namespace crown::runtime {
void PhysicalRuntime::configure_workload_statistics(const workload::Options& options) {
  auto& d=impl(); d.writable(); d.workload->configure(d.kernel.compiled_program(),true,options,d.sequence);
}
void PhysicalRuntime::reset_workload_statistics() {
  auto& d=impl(); d.writable(); d.workload->reset(d.sequence);
}
workload::Snapshot PhysicalRuntime::workload_statistics() const {
  const auto& d=impl(); return d.workload->snapshot(d.kernel.compiled_program(),d.kernel.owner(),d.sequence,d.updating);
}
workload::detail::State& PhysicalRuntime::workload_state() const { return *impl().workload; }
std::shared_ptr<detail::StorageWorkContext> PhysicalRuntime::storage_context() const { return impl().storage_context; }
#ifdef CROWN_RUNTIME_TESTING
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const PhysicalRuntime& runtime) {
  return index_work(runtime.impl().kernel);
}
#endif
} // namespace crown::runtime
#include "owner_statistics_detail.hpp"
namespace crown::runtime {
statistics::OwnerCapture PhysicalRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  return capture_statistics_view(request,limits);
}
statistics::OwnerCapture PhysicalRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  using namespace statistics;
  const auto& d=impl();statistics::detail::OwnerBuilder builder{{d.kernel.owner(),d.sequence,OwnerLayer::physical},d.kernel.compiled_program(),request,limits,d.updating};
  if(builder.active())for(const auto& selection:request.selections) {
    if(!builder.active())break;
    if(const auto* scope=std::get_if<SourceScope>(&selection.scope)) {
      require(scope->table.value<d.sources.size(),"invalid_statistics_request","source outside catalog");
      auto* component=builder.append(selection);if(!component)break;
      builder.table(*component,d.sources[scope->table.value],d.source_layouts[scope->table.value],d.work());
    }else if(const auto* occurrence=std::get_if<OccurrenceScope>(&selection.scope)) {
      const auto& input=d.input(occurrence->occurrence);
      require(!selection.fields,"invalid_statistics_request","derivation distribution uses complete native keys");
      auto* component=builder.append(selection);if(!component)break;
      const auto& node=d.kernel.compiled_program().nodes()[input.node.value];component->layout=node.layout.descriptor();component->node_kind=node.kind;
      const auto& counts=d.counts[occurrence->occurrence.value];component->cardinality=counts.size();
      try {
        statistics::detail::WeightedBuilder weighted{builder.budget(),builder.account()};
        for(const auto& [key,count]:counts)if(!weighted.add(key.view(),count))break;
        component->distribution=weighted.finish();
        if(component->distribution->completion!=Completion::exact)component->availability=Availability::budget_exhausted;
      }catch(const statistics::detail::Exhausted&){component->availability=Availability::budget_exhausted;component->distribution=CapturedDistribution{};}
    }else d.kernel.append_statistics(builder,selection);
  }
  return builder.finish();
} catch(const storage::IndexFailure& failure) { present(failure); } catch(const storage::TableValidationFailure& failure) { present(failure); }
statistics::Freshness PhysicalRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  const auto& d=impl();return statistics::compare_freshness(captured.stamp(),{d.kernel.owner(),d.sequence,statistics::OwnerLayer::physical},max_event_lag);
}
}

namespace crown::runtime::memory::detail {
void Access::append(Builder& builder,const PhysicalRuntime& owner) {
  const auto& d=owner.impl();append(builder,d.kernel);builder.operation(Coordinator{Layer::physical,d.attribution});
  for(std::size_t i=0;i<d.sources.size();++i)
    builder.table(TableScope::physical_source,d.sources[i],RelationRole::physical_base,{},TableId{i});
  const auto& program=d.kernel.plan();
  for(std::size_t i=0;i<d.counts.size();++i) {
    builder.work();const auto& counts=d.counts[i];const auto& input=program.inputs()[i];
    if(counts.size()!=builder.records(TableScope::support,program.nodes()[input.node.value].records))throw Failure{Stop::inconsistent};
    builder.operation(Derivations{OccurrenceId{i},counts.get_allocator().attribution(),static_cast<std::uint64_t>(counts.size())});
  }
}
Attempt Access::capture(const PhysicalRuntime& owner,Limits limits) noexcept {
  return attempt([&](Usage& usage) {
    if(!owner.impl_)throw Failure{Stop::invalid_handle};
    const auto& d=owner.impl();const auto& plan=d.kernel.plan();const auto availability=d.updating?Availability::pending:Availability::committed;
    Builder builder(plan.account(),Layer::physical,availability,d.kernel.owner().value,d.sequence,plan.physical_sha256(),limits,usage);
    if(availability==Availability::committed)append(builder,owner);
    return builder.finish();
  });
}
}
