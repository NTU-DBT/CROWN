#include "crown/runtime/physical.hpp"

#include "crown/api/error.hpp"
#include "inspection_detail.hpp"
#include "validation_work.hpp"
#include "workload_statistics_detail.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <map>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
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

struct PhysicalRuntime::Impl {
  using Counts=std::map<Row,std::uint64_t>;
  PhysicalRuntimeOptions options;
  SupportRuntime kernel;
  std::shared_ptr<detail::ObservationState> observation;
  workload::detail::State* workload;
  std::vector<storage::ReferenceTable> sources;
  std::vector<Counts> counts;
  std::uint64_t sequence=0;
  BuildMetrics build_metrics;
  InitializationContext initialization_context;
  bool updating=false, enforced_constraints=false;
  Impl(PhysicalPlan plan,PhysicalRuntimeOptions value):options(value),kernel(std::move(plan),value.support),observation(kernel.observation_state()),workload(&kernel.workload_state()),counts(kernel.plan().inputs().size()) {
    require(options.derivation_limit>0,"invalid_options","physical derivation limit must be positive");
    const auto& compiled=kernel.plan(); const auto& catalog=compiled.source_catalog();
    const auto tables=catalog.tables.size();
    require(tables<=std::numeric_limits<std::size_t>::max()-compiled.relations().size() &&
        tables<=std::numeric_limits<std::size_t>::max()-compiled.layouts().size(),"storage_overflow","private source descriptors exhausted");
    sources.reserve(tables);
    for (std::size_t i=0;i<tables;++i) {
      const TableId table{i};
      const auto found=std::find_if(compiled.relations().begin(),compiled.relations().end(),[&](const auto& definition) {
        return definition.role==RelationRole::physical_base && definition.base==table;
      });
      if (found!=compiled.relations().end()) sources.emplace_back(found->id,found->layout);
      else sources.emplace_back(RelationId{compiled.relations().size()+i},
          storage::table_layout(LayoutId{compiled.layouts().size()+i},catalog,table,compiled.physical_sha256()+":source"));
      for (const auto& constraint : catalog.tables[i].constraints)
        if (std::visit([](const auto& item) { return item.status==ConstraintStatus::enforced; },constraint)) enforced_constraints=true;
    }
  }
  void readable() const { require(!updating,"runtime_busy","a prepared physical update is active"); }
  void writable() const { readable(); require(kernel.ready(),"runtime_busy","result cursors pin the committed physical epoch"); }
  storage::ReferenceTable& source(TableId table) {
    require(table.value<sources.size(),"invalid_physical_update","source table is outside the catalog"); return sources[table.value];
  }
  const PhysicalInput& input(OccurrenceId occurrence) const {
    require(occurrence.value<kernel.plan().inputs().size(),"invalid_input_port","physical plan has no such occurrence input port");
    return kernel.plan().inputs()[occurrence.value];
  }
  Database database() const {
    Database result; result.tables.resize(sources.size());
    for (std::size_t i=0;i<sources.size();++i)
      for (const auto& tuple : sources[i].snapshot()) result.tables[i].insert(tuple.values());
    return result;
  }
  PhysicalSnapshot snapshot(SupportSnapshot support) const {
    PhysicalSnapshot result{support.sequence,database(),std::move(support),{}};
    result.derivations.resize(counts.size());
    for (std::size_t i=0;i<counts.size();++i) {
      const auto& node=kernel.plan().nodes()[input(OccurrenceId{i}).node.value];
      auto& output=result.derivations[i]; output.reserve(counts[i].size());
      for (const auto& [row,count] : counts[i]) output.push_back({node.layout.tuple(row),count});
    }
    return result;
  }
};

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
  PhysicalPreview output;
  std::optional<storage::ReferenceTable::Journal> source;
  std::optional<SupportRuntime::PendingEpoch> logical;
  std::vector<CountUndo> undo;
  std::size_t next_route=0;
  bool routes_complete=false;
  detail::ObservationTicket observation_ticket;
  workload::detail::Ticket workload_ticket;
  // Optional bookkeeping records successful nested charges, never an inference
  // from coordinator/support counter magnitudes. Failed stage/charge is sticky
  // until this pending update closes.
  std::uint64_t observed_charged_support_work=0;
  bool observed_support_accounting_complete=true;
  Data(std::shared_ptr<Impl> value,const PhysicalSetUpdate& update)
      :owner(std::move(value)),output{update.sequence,update.table,update.operation,false,{}, {},{}} {
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
    charge(amount);
    require(amount<=std::numeric_limits<std::uint64_t>::max()-counter,"resource_limit","physical metric exhausted"); counter+=amount;
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
    Database after; after.tables.resize(owner->sources.size());
    for (std::size_t i=0;i<owner->sources.size();++i) {
      metric(output.metrics.constraint_rows,static_cast<std::uint64_t>(owner->sources[i].size()));
      for (const auto& tuple : owner->sources[i].snapshot()) after.tables[i].insert(tuple.values());
    }
    metric(output.metrics.constraint_validations);
    // A reference full after-state check, including unused tables and self-FKs.
    // This materialization is not rollback state and is not retained at commit.
    validate_database(owner->kernel.plan().source_catalog(),after);
  }
  void route(OccurrenceId occurrence,std::uint64_t prefix,const Row& row,const RouteObserver& observer,EpochViewOptions view_options) {
    metric(output.metrics.aliases_visited);
    if (owner->observation) {
      owner->observation->route(occurrence.value,prefix);
      owner->observation->event(TraceKind::alias,0,0,owner->input(occurrence).node.value,occurrence.value,prefix);
    }
    const auto& input=owner->input(occurrence);
    auto tuple=owner->kernel.plan().adapt_input(occurrence,row);
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
    output.derivations.push_back({occurrence,input.node,std::move(*tuple),before,after,crossing});
    const auto& change=output.derivations.back();
    if (before==0) {
      const auto [item,inserted]=counts.emplace(change.tuple.values(),after);
      require(inserted,"runtime_contract","new physical derivation already exists");
      undo.push_back({CountKind::inserted,&counts,item,0,{}});
    } else if (after==0) {
      undo.push_back({CountKind::erased,&counts,{},before,counts.extract(found)});
    } else {
      undo.push_back({CountKind::changed,&counts,found,before,{}}); found->second=after;
    }
    if (crossing) {
      metric(output.metrics.native_crossings);
      const auto before_work=logical->preview().metrics.work;
      const auto checkpoint=logical->checkpoint();
      if (owner->observation) observed_support_accounting_complete=false;
      require(logical->stage(input.node,change.tuple.values()),"runtime_contract","derivation zero crossing did not change native membership");
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
  void prepare(const storage::Tuple& tuple,std::optional<TupleHandle> existing) {
    try {
      logical.emplace(owner->kernel.begin_epoch(output.sequence,output.operation));
      const bool add=output.operation==SetOperation::insert;
      owner->workload->physical_fact(existing.has_value()!=add);
      if (existing.has_value()==add) { routes_complete=true; return; }
      output.physical_changed=true; metric(output.metrics.source_changes);
      if (owner->observation) owner->observation->event(TraceKind::source_change,0,0,
          observation_no_id,observation_no_id,0,static_cast<std::uint64_t>(!add),static_cast<std::uint64_t>(add));
      auto& table=owner->source(output.table); source.emplace(table.journal());
      if (add) {
        const auto inserted=source->insert(tuple);
        require(inserted.inserted,"runtime_contract","physical source insertion duplicated membership");
        output.source.emplace(SourceRowChange{inserted.handle,table.pin(inserted.handle)});
      } else {
        output.source.emplace(SourceRowChange{*existing,table.pin(*existing)});
        require(source->erase(*existing),"runtime_contract","physical source deletion lost membership");
      }
      validate_constraints();
      const auto& routes=owner->kernel.plan().base_routes()[output.table.value];
      undo.reserve(routes.size()); output.derivations.reserve(routes.size());
      routes_complete=routes.empty(); observe();
    } catch (...) { rollback(); throw; }
  }
};

PhysicalRuntime::PendingUpdate::PendingUpdate(std::unique_ptr<Data> data) noexcept:data_(std::move(data)) {}
PhysicalRuntime::PendingUpdate::PendingUpdate(PendingUpdate&&) noexcept=default;
PhysicalRuntime::PendingUpdate& PhysicalRuntime::PendingUpdate::operator=(PendingUpdate&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
PhysicalRuntime::PendingUpdate::~PendingUpdate()=default;
bool PhysicalRuntime::PendingUpdate::active() const noexcept { return data_ && data_->owner && data_->logical && data_->logical->active(); }
bool PhysicalRuntime::PendingUpdate::stage_next(const RouteObserver& observer,EpochViewOptions options) {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active());
  if (data_->routes_complete) return false;
  try {
    const auto& routes=data_->owner->kernel.plan().base_routes()[data_->output.table.value];
    const auto position=data_->next_route;
    // The source pin owns the complete input row across calls and facade moves.
    data_->route(routes[position],static_cast<std::uint64_t>(position)+1,data_->output.source->tuple().values(),observer,options);
    ++data_->next_route; data_->routes_complete=data_->next_route==routes.size(); data_->observe(); return true;
  } catch (...) { data_->rollback(); throw; }
}
void PhysicalRuntime::PendingUpdate::rollback() noexcept { if (data_) data_->rollback(); }
const PhysicalPreview& PhysicalRuntime::PendingUpdate::preview() const {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active()); return data_->output;
}
const SupportEpoch& PhysicalRuntime::PendingUpdate::support() const {
  require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast<void>(data_->active()); return data_->logical->preview();
}
PhysicalSnapshot PhysicalRuntime::PendingUpdate::snapshot() const {
  require(bool(data_),"invalid_epoch","moved-from physical update"); return data_->active().snapshot(data_->logical->snapshot());
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

PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options):impl_(std::make_shared<Impl>(std::move(plan),options)) {
  if (impl_->observation) impl_->observation->initialize(impl_->initialization_context);
}
PhysicalRuntime PhysicalRuntime::initialize(PhysicalPlan plan,const Database& database,
    PhysicalRuntimeOptions options,BuildOptions build) {
  return initialize_at(std::move(plan),database,options,build,0);
}
PhysicalRuntime PhysicalRuntime::initialize_at(PhysicalPlan plan,const Database& database,
    PhysicalRuntimeOptions options,BuildOptions build,std::uint64_t sequence,BuildMetrics prefix) {
  require(build.method==BuildMethod::direct || build.method==BuildMethod::insertion_replay,
      "invalid_options","unknown runtime initialization method");
  PhysicalRuntime result(std::move(plan),options); auto& d=result.impl();
  BuildMetrics metrics=prefix; detail::build_charge(metrics,build);
  const auto& compiled=d.kernel.plan(); const auto& catalog=compiled.source_catalog();
  require(database.tables.size()==catalog.tables.size(),"invalid_database","database/catalog table count differs");
  // Validate the complete final snapshot before either unpublished build path.
  // Per-prefix public inserts cannot initialize valid cyclic foreign keys.
  detail::charge_database_validation(catalog,database,[&](std::uint64_t amount) { detail::build_charge(metrics,build,amount); });
  for (const auto& table : database.tables)
    detail::build_metric(metrics,build,metrics.constraint_rows,static_cast<std::uint64_t>(table.size()));
  validate_database(catalog,database);
  std::vector<detail::NativeSeed> seeds;
  for (std::size_t i=0;i<database.tables.size();++i) {
    auto& source=d.sources[i];
    for (const auto& row : database.tables[i]) {
      detail::build_metric(metrics,build,metrics.source_rows);
      require(source.insert(source.layout().tuple(row)).inserted,"runtime_contract","initial source row duplicated membership");
      for (const auto occurrence : compiled.base_routes()[i]) {
        detail::build_metric(metrics,build,metrics.adapter_visits);
        const auto& input=d.input(occurrence);
        auto tuple=compiled.adapt_input(occurrence,row);
        if (!tuple) { detail::build_metric(metrics,build,metrics.adapter_rejections); continue; }
        detail::build_metric(metrics,build,metrics.derivation_changes);
        auto& counts=d.counts[occurrence.value]; const auto found=counts.find(tuple->values());
        const auto before=found==counts.end()?std::uint64_t{0}:found->second;
        require(before<options.derivation_limit,"derivation_overflow","initial derivation count exceeds its configured exact limit");
        if (found==counts.end()) {
          counts.emplace(tuple->values(),1);
          detail::build_charge(metrics,build,static_cast<std::uint64_t>(tuple->values().size()));
          seeds.push_back({input.node,tuple->values()});
        } else ++found->second;
      }
    }
  }
  d.kernel.initialize_native(seeds,build,metrics);
  detail::build_metric(metrics,build,metrics.storage_records,metrics.source_rows);
  // Source tables currently have only primary full-row identity. Account any
  // registered secondary indexes explicitly if this backend is extended.
  for (const auto& source : d.sources) {
    for (const auto index : source.indices()) {
      static_cast<void>(index);
      detail::build_metric(metrics,build,metrics.index_memberships,static_cast<std::uint64_t>(source.size()));
    }
  }
  d.build_metrics=metrics; d.kernel.seed_sequence(sequence); d.sequence=sequence;
  d.initialization_context={InitializationRoute::initialized_database,build};
  if (d.observation) d.observation->initialize(d.initialization_context);
  return result;
}
PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build) const {
  auto& d=impl(); d.writable();
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
  const auto database=d.database();
  auto result=initialize_at(d.kernel.plan(),database,d.options,build,d.sequence,prefix);
  result.impl().initialization_context.route=InitializationRoute::rebuilt_snapshot;
  if (result.impl().observation) result.impl().observation->initialize(result.impl().initialization_context);
  return result;
}
PhysicalRuntime::~PhysicalRuntime()=default;
PhysicalRuntime::PhysicalRuntime(PhysicalRuntime&&) noexcept=default;
PhysicalRuntime& PhysicalRuntime::operator=(PhysicalRuntime&& other) noexcept {
  if (this!=&other) impl_=std::move(other.impl_);
  return *this;
}
PhysicalRuntime::Impl& PhysicalRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from physical runtime"); return *impl_; }
const PhysicalPlan& PhysicalRuntime::plan() const { return impl().kernel.plan(); }
const PhysicalRuntimeOptions& PhysicalRuntime::options() const { return impl().options; }
SupportOwnerId PhysicalRuntime::owner() const { return impl().kernel.owner(); }
std::uint64_t PhysicalRuntime::sequence() const { return impl().sequence; }
bool PhysicalRuntime::ready() const { const auto& d=impl(); return !d.updating && d.kernel.ready(); }
bool PhysicalRuntime::has_answer() const { auto& d=impl(); d.readable(); return d.kernel.has_answer(); }
const storage::TupleLayout& PhysicalRuntime::source_layout(TableId table) const { return impl().source(table).layout(); }
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
  auto& d=impl(); d.writable();
  require(d.sequence!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","physical update sequence exhausted");
  require(update.sequence==d.sequence+1,"invalid_sequence","physical update sequence must be contiguous from one");
  require(update.operation==SetOperation::insert || update.operation==SetOperation::erase,"invalid_physical_update","unknown physical set operation");
  auto& table=d.source(update.table); validate_row(d.kernel.plan().source_catalog(),update.table,update.values);
  const auto tuple=table.layout().tuple(update.values); const auto existing=table.find(tuple);
  auto data=std::make_unique<PendingUpdate::Data>(impl_,update);
  d.updating=true; data->prepare(tuple,existing); return PendingUpdate(std::move(data));
}
PhysicalEpoch PhysicalRuntime::apply(const PhysicalSetUpdate& update) { return prepare(update).commit(); }
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
PhysicalSnapshot PhysicalRuntime::snapshot() const { auto& d=impl(); d.readable(); return d.snapshot(d.kernel.snapshot()); }
std::uint64_t PhysicalRuntime::derivation_count(OccurrenceId occurrence,const Row& values) const {
  auto& d=impl(); d.readable(); const auto& input=d.input(occurrence); d.kernel.plan().nodes()[input.node.value].layout.validate(values);
  const auto& counts=d.counts[occurrence.value]; const auto found=counts.find(values); return found==counts.end()?0:found->second;
}
std::optional<TupleHandle> PhysicalRuntime::find_source(TableId table,const Row& values) const {
  auto& d=impl(); d.readable(); const auto& source=d.source(table); return source.find(source.layout().tuple(values));
}
std::optional<storage::Tuple> PhysicalRuntime::get_source(TableId table,TupleHandle handle) const {
  auto& d=impl(); d.readable(); const auto* tuple=d.source(table).get(handle); return tuple?std::optional<storage::Tuple>{*tuple}:std::nullopt;
}
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
CanonicalPhysicalState PhysicalRuntime::canonical_state() const {
  const auto& d=impl(); d.readable();
  CanonicalPhysicalState result{d.kernel.canonical_state(),d.sequence,d.database().tables,{}};
  result.derivations.resize(d.counts.size());
  for (std::size_t i=0;i<d.counts.size();++i)
    for (const auto& [key,count] : d.counts[i]) result.derivations[i].push_back({key,count});
  return result;
}
InvariantReport PhysicalRuntime::inspect_invariants(InspectionOptions options) const {
  const auto& d=impl(); d.readable();
  auto support=d.kernel.inspect_invariants(options);
  if (!support.complete) return support;
  detail::InspectionContext context(options,std::move(support));
  const auto issue=[&](InvariantCode code,InvariantComponent component,std::optional<TableId> table,
      std::optional<OccurrenceId> occurrence,std::optional<NodeId> node,const Row& key,
      std::optional<std::uint64_t> expected={},std::optional<std::uint64_t> actual={}) {
    InvariantIssue item{}; item.code=code; item.component=component; item.table=table;
    item.occurrence=occurrence; item.node=node; item.key=key; item.expected=expected; item.actual=actual;
    context.add(std::move(item));
  };
  try {
    context.charge();
    if (d.sequence!=d.kernel.sequence())
      issue(InvariantCode::sequence,InvariantComponent::sequence,{},{},{},{},d.sequence,d.kernel.sequence());
    Database database; database.tables.resize(d.sources.size());
    for (std::size_t i=0;i<d.sources.size();++i) {
      const auto& source=d.sources[i]; const auto arena=source.arena_statistics();
      context.charge(static_cast<std::uint64_t>(arena.slots));
      context.charge(static_cast<std::uint64_t>(source.size()));
      context.charge(detail::validation_product(source.size(),source.layout().fields().size()+1));
      try { source.check_invariants(); }
      catch (const Error&) { issue(InvariantCode::storage,InvariantComponent::storage,TableId{i},{},{},{}); }
      add_size(context.report.statistics.source_storage_records,arena.live_records);
      for (const auto& tuple : source.snapshot()) {
        context.charge(); database.tables[i].insert(tuple.values());
      }
      add_size(context.report.statistics.source_rows,source.size());
      for (const auto index : source.indices()) {
        for (const auto& key : source.keys(index)) {
          context.charge(); const auto members=source.bucket(index,key);
          context.charge(static_cast<std::uint64_t>(members.size()));
          add_size(context.report.statistics.index_memberships,members.size());
        }
      }
    }
    try {
      detail::charge_database_validation(d.kernel.plan().source_catalog(),database,[&](std::uint64_t amount) { context.charge(amount); });
      validate_database(d.kernel.plan().source_catalog(),database);
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
      Impl::Counts expected;
      for (const auto& row : database.tables[input.base.value]) {
        context.charge(); const auto tuple=d.kernel.plan().adapt_input(occurrence,row);
        if (tuple) {
          auto& count=expected[tuple->values()];
          if (count==std::numeric_limits<std::uint64_t>::max()) {
            issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,tuple->values(),{},count);
          } else ++count;
        }
      }
      const auto& actual=d.counts[i]; add_size(context.report.statistics.derivation_keys,actual.size());
      for (const auto& [key,count] : expected) {
        context.charge(); const auto found=actual.find(key);
        if (found==actual.end() || found->second!=count)
          issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,key,
              count,found==actual.end()?std::nullopt:std::optional<std::uint64_t>{found->second});
      }
      for (const auto& [key,count] : actual) {
        context.charge();
        if (!expected.contains(key))
          issue(InvariantCode::derivation_count,InvariantComponent::derivation,input.base,occurrence,input.node,key,0,count);
      }
      const auto native=d.kernel.record_rows(input.node);
      for (const auto& key : native) {
        context.charge();
        if (!expected.contains(key)) issue(InvariantCode::unexpected_record,InvariantComponent::record,input.base,occurrence,input.node,key,0,1);
      }
      for (const auto& [key,count] : expected) {
        static_cast<void>(count); context.charge();
        if (!native.contains(key)) issue(InvariantCode::missing_record,InvariantComponent::record,input.base,occurrence,input.node,key,1,0);
      }
    }
  } catch (const detail::InspectionStop&) { context.report.complete=false; }
  return std::move(context.report);
}
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
void PhysicalRuntime::check_invariants() const {
  auto& d=impl(); d.readable();
  require(d.sequence==d.kernel.sequence(),"runtime_contract","physical and logical sequence differ");
  d.kernel.check_invariants(); for (const auto& source : d.sources) source.check_invariants();
  const auto database=d.database(); validate_database(d.kernel.plan().source_catalog(),database);
  const auto support=d.kernel.snapshot();
  for (std::size_t i=0;i<d.counts.size();++i) {
    const OccurrenceId occurrence{i}; const auto& input=d.input(occurrence); Impl::Counts expected;
    for (const auto& row : database.tables[input.base.value]) {
      const auto tuple=d.kernel.plan().adapt_input(occurrence,row);
      if (tuple) {
        auto& count=expected[tuple->values()];
        require(count<d.options.derivation_limit,"runtime_contract","recomputed derivation count exceeds limit"); ++count;
      }
    }
    require(expected==d.counts[i],"runtime_contract","physical derivation map differs from source-row recomputation");
    Relation native;
    for (const auto& record : support.nodes[input.node.value].records) native.insert(record.tuple.values());
    require(native.size()==expected.size(),"runtime_contract","native membership differs from derivation keys");
    for (const auto& [row,count] : expected) {
      static_cast<void>(count); require(native.contains(row),"runtime_contract","positive derivation has no native row");
    }
  }
}
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
ObservationSnapshot PhysicalRuntime::observations() const {
  auto result=impl().kernel.observations(); result.initialization=impl().initialization_context; return result;
}
ObservationTrace PhysicalRuntime::observation_trace() const {
  auto result=impl().kernel.observation_trace(); result.snapshot.initialization=impl().initialization_context; return result;
}
}  // namespace crown::runtime

namespace crown::runtime {
void PhysicalRuntime::configure_workload_statistics(const workload::Options& options) {
  auto& d=impl(); d.writable(); d.workload->configure(d.kernel.plan(),true,options,d.sequence);
}
void PhysicalRuntime::reset_workload_statistics() {
  auto& d=impl(); d.writable(); d.workload->reset(d.sequence);
}
workload::Snapshot PhysicalRuntime::workload_statistics() const {
  const auto& d=impl(); return d.workload->snapshot(d.kernel.plan(),d.kernel.owner(),d.sequence,d.updating);
}
workload::detail::State& PhysicalRuntime::workload_state() const { return *impl().workload; }
} // namespace crown::runtime
#include "owner_statistics_detail.hpp"
namespace crown::runtime {
statistics::OwnerCapture PhysicalRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  using namespace statistics;
  const auto& d=impl();statistics::detail::OwnerBuilder builder{{d.kernel.owner(),d.sequence,OwnerLayer::physical},d.kernel.plan(),request,limits,d.updating};
  if(builder.active())for(const auto& selection:request.selections) {
    if(!builder.active())break;
    if(const auto* scope=std::get_if<SourceScope>(&selection.scope)) {
      require(scope->table.value<d.sources.size(),"invalid_statistics_request","source outside catalog");
      auto* component=builder.append(selection);if(!component)break;
      builder.table(*component,d.sources[scope->table.value]);
    }else if(const auto* occurrence=std::get_if<OccurrenceScope>(&selection.scope)) {
      const auto& input=d.input(occurrence->occurrence);
      require(!selection.fields,"invalid_statistics_request","derivation distribution uses complete native keys");
      auto* component=builder.append(selection);if(!component)break;
      const auto& node=d.kernel.plan().nodes()[input.node.value];component->layout=node.layout;component->node_kind=node.kind;
      const auto& counts=d.counts[occurrence->occurrence.value];component->cardinality=counts.size();
      try {
        statistics::detail::WeightedBuilder weighted{builder.budget()};
        for(const auto& [key,count]:counts)if(!weighted.add(key,count))break;
        component->distribution=weighted.finish();
        if(component->distribution->completion!=Completion::exact)component->availability=Availability::budget_exhausted;
      }catch(const statistics::detail::Exhausted&){component->availability=Availability::budget_exhausted;component->distribution=Distribution{};}
    }else d.kernel.append_statistics(builder,selection);
  }
  return builder.finish();
}
statistics::Freshness PhysicalRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  const auto& d=impl();return statistics::compare_freshness(captured.stamp(),{d.kernel.owner(),d.sequence,statistics::OwnerLayer::physical},max_event_lag);
}
}
