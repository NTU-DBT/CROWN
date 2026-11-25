#include "owner_override.hpp"
#include "crown/runtime/support.hpp"
#include "memory_report_detail.hpp"

#include "crown/api/error.hpp"
#include "crown/storage/accounted_plan.hpp"
#include "crown/runtime/program.hpp"
#include "storage_work.hpp"
#include "inspection_detail.hpp"
#include "workload_statistics_detail.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <exception>
#include <algorithm>
#include <array>
#include <atomic>
#include <deque>
#include <map>
#include <set>
#include <utility>
#include <type_traits>

namespace crown::runtime {
namespace {
// The check is inlined on hot paths; only failure leaves the caller.
[[noreturn, gnu::cold, gnu::noinline]] void fail(std::string_view code,std::string_view message) {
  throw Error(std::string(code),std::string(message));
}
inline void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) [[unlikely]] fail(code,message);
}
template<class Failure> [[noreturn]] void support_present(const Failure& failure) { throw Error(std::string(failure.code()),failure.what()); }
SupportOwnerId new_owner() {
  if (const auto forced=detail::forced_support_owner) { detail::forced_support_owner=0; return {forced}; }
  static std::atomic<std::uint64_t> last{0}; auto value=last.load(std::memory_order_relaxed);
  for (;;) {
    require(value!=std::numeric_limits<std::uint64_t>::max(),"support_overflow","runtime owner IDs exhausted");
    if (last.compare_exchange_weak(value,value+1,std::memory_order_relaxed)) return {value+1};
  }
}
// Internal metadata IDs must not consume the public runtime-owner sequence.
std::uint64_t new_metadata_owner() {
  static std::atomic<std::uint64_t> last{0};auto value=last.load(std::memory_order_relaxed);
  for (;;) {
    if (value==std::numeric_limits<std::uint64_t>::max()) throw resource::MemoryFailure(resource::MemoryFault::overflow);
    if (last.compare_exchange_weak(value,value+1,std::memory_order_relaxed)) return value+1;
  }
}
template<class T> using MemoryVector=std::vector<T,resource::MemoryAllocator<T>>;
template<class K,class V,class Less=std::less<K>>
using MemoryMap=std::map<K,V,Less,resource::MemoryAllocator<std::pair<const K,V>>>;
template<class K> using MemorySet=std::set<K,std::less<K>,resource::MemoryAllocator<K>>;
template<class Map> Map memory_map(const resource::MemoryAccount& account,resource::MemoryPurpose purpose=resource::MemoryPurpose::cursor) {
  return Map(typename Map::key_compare{},typename Map::allocator_type(account,purpose));
}
struct CompactRowLess {
  using is_transparent=void;
  bool operator()(const storage::AccountedRow& a,const storage::AccountedRow& b) const {return a.view()<b.view();}
  bool operator()(const storage::AccountedRow& a,storage::RowView b) const {return a.view()<b;}
  bool operator()(storage::RowView a,const storage::AccountedRow& b) const {return a<b.view();}
};

template<class T> void program_words(storage::IndexWorkAllowance* work,std::size_t count) {
  if (!work) return;
  constexpr auto words=static_cast<std::uint64_t>((sizeof(T)+sizeof(void*)-1)/sizeof(void*));
  if (count>std::numeric_limits<std::uint64_t>::max()/words)
    throw storage::IndexFailure(storage::IndexFault::overflow);
  work->admit(storage::IndexWork{.pointer_slots=static_cast<std::uint64_t>(count)*words});
}
struct RecordState {
  SatisfiedChildCount satisfied{};
  MemoryVector<std::uint8_t> present;
  RecordState(const resource::MemoryAccount& account,resource::MemoryAttribution owner,std::size_t children)
      :present(children,0,resource::MemoryAllocator<std::uint8_t>(account,resource::MemoryPurpose::support_metadata,owner)) {}
  void lifetime(resource::AllocationLifetime value) {
    present.get_allocator().set_allocation_lifetime(present.data(),present.capacity(),value);
  }
};
std::vector<bool> export_flags(const RecordState& record) {
  return std::vector<bool>(record.present.begin(),record.present.end());
}
std::vector<bool,resource::OwnerAllocator<bool>> retained_flags(const RecordState& record) {
  const auto allocator=record.present.get_allocator();
  return {record.present.begin(),record.present.end(),resource::OwnerAllocator<bool>(allocator.account(),
      resource::MemoryPurpose::journal_undo,allocator.attribution())};
}
auto transition_buffer(const resource::MemoryAccount& account) {
  return std::vector<MembershipTransition,resource::OwnerAllocator<MembershipTransition>>(
      resource::OwnerAllocator<MembershipTransition>(account,resource::MemoryPurpose::output_buffer,
          {resource::MemoryOwnerKind::output,0}));
}
static_assert(std::is_nothrow_move_constructible_v<SupportValueState>);
static_assert(std::is_nothrow_move_assignable_v<SupportValueState>);
static_assert(std::is_nothrow_move_constructible_v<SupportEpoch>);
static_assert(std::is_nothrow_move_assignable_v<SupportEpoch>);
struct NodeState {
  using Records=std::map<TupleId,RecordState,std::less<TupleId>,resource::MemoryAllocator<std::pair<const TupleId,RecordState>>>;
  using Counts=std::map<TupleId,ProjectionSupportCount,std::less<TupleId>,resource::MemoryAllocator<std::pair<const TupleId,ProjectionSupportCount>>>;
  resource::MemoryAttribution attribution{resource::MemoryOwnerKind::support_node,new_metadata_owner()};
  Records records;
  Counts parent, visible;
  explicit NodeState(const resource::MemoryAccount& account)
      :records(std::less<TupleId>{},Records::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)),
       parent(std::less<TupleId>{},Counts::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)),
       visible(std::less<TupleId>{},Counts::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)) {}
  [[nodiscard]] RecordState record(std::size_t children) const { return {records.get_allocator().account(),attribution,children}; }
  // O(1) after one calibration per node type; see MemoryAccount::ContainingSite.
  void lifetime(const RecordState* value,resource::AllocationLifetime lifetime) const {
    static resource::MemoryAccount::ContainingSite site;
    records.get_allocator().account().set_lifetime_containing(value,site,resource::MemoryPurpose::support_metadata,attribution,lifetime);
  }
  void lifetime(const ProjectionSupportCount* value,resource::AllocationLifetime lifetime) const {
    static resource::MemoryAccount::ContainingSite site;  // parent and visible share one node type
    records.get_allocator().account().set_lifetime_containing(value,site,resource::MemoryPurpose::support_metadata,attribution,lifetime);
  }
};
using SupportNodeProgram=program::PhysicalNode;
using SupportEdgeProgram=program::PhysicalEdge;
using SupportEnumerationStep=program::EnumerationStep;
struct SupportEnumerationProgram {
  MemoryVector<SupportEnumerationStep> steps;MemoryVector<AssignmentSlot> output;MemoryVector<AssignmentEquality> equalities;
  std::size_t depth=0;
  explicit SupportEnumerationProgram(const resource::MemoryAccount& account)
      :steps(resource::MemoryAllocator<SupportEnumerationStep>(account,resource::MemoryPurpose::immutable_metadata)),
       output(resource::MemoryAllocator<AssignmentSlot>(account,resource::MemoryPurpose::immutable_metadata)),
       equalities(resource::MemoryAllocator<AssignmentEquality>(account,resource::MemoryPurpose::immutable_metadata)) {}
  mutable program::EnumerationProgram borrowed{};
  const program::EnumerationProgram& view() const noexcept {
    borrowed={{steps.data(),steps.size()},{output.data(),output.size()},{equalities.data(),equalities.size()},depth};
    return borrowed;
  }
  operator program::EnumerationProgram() const noexcept {return view();}
  void clear() noexcept {steps.clear();output.clear();equalities.clear();depth=0;}
};
struct State {
  CompiledProgram compiled;
  storage::AccountedPlanStorage storage;
  MemoryVector<NodeState> nodes;
  program::Span<SupportNodeProgram> program_nodes;
  program::Span<SupportEdgeProgram> program_edges;
  program::EnumerationProgram enumeration;
  State(const PhysicalPlan& source,storage::IndexWorkAllowance* work,const resource::MemoryAccount& account)
      :State(CompiledProgram::freeze(account,source,work),work,account) {}
  State(CompiledProgram source,storage::IndexWorkAllowance* work,const resource::MemoryAccount& account)
      :compiled(std::move(source)),storage(compiled.make_storage(work)),
       nodes(resource::MemoryAllocator<NodeState>(account,resource::MemoryPurpose::support_metadata)),
       program_nodes(compiled.nodes()),program_edges(compiled.edges()),enumeration(compiled.enumeration()) {
    program_words<NodeState>(work,program_nodes.size());nodes.reserve(program_nodes.size());
    for(std::size_t i=0;i<program_nodes.size();++i)nodes.emplace_back(account);
  }
};

RelationId relation(const auto& node,SupportRole role) {
  switch (role) {
    case SupportRole::records: return node.records;
    case SupportRole::survivors: return node.survivors;
    case SupportRole::parent_support: return node.parent_support;
    case SupportRole::visible:
      require(node.visible_relation.has_value(),"invalid_support_role","node is outside the enumeration subtree"); return *node.visible_relation;
  }
  throw Error("invalid_support_role","unknown support relation role");
}
constexpr std::array<CursorMetricDescriptor,cursor_metric_count> cursor_registry{{
 {CursorMetricId::startup_ns,"cursor.startup_ns","nanoseconds","cursor construction/allocation/preparation; failed construction includes unwinding; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase",MetricKind::timing},
 {CursorMetricId::successful_next_ns,"cursor.successful_next_ns","nanoseconds","sum of successful active next calls; excludes caller pause; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase",MetricKind::timing},
 {CursorMetricId::exhausted_next_ns,"cursor.exhausted_next_ns","nanoseconds","first exhausted active next; excludes cleanup; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase",MetricKind::timing},
 {CursorMetricId::failed_next_ns,"cursor.failed_next_ns","nanoseconds","failed active next; excludes cleanup and later rejected calls; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase",MetricKind::timing},
 {CursorMetricId::cleanup_ns,"cursor.cleanup_ns","nanoseconds","one admitted cursor cleanup/lease release; excludes owning plan/layout destruction; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase",MetricKind::timing},
 {CursorMetricId::successful_calls,"cursor.successful_calls","count","active next returning one owning row",MetricKind::counter},
 {CursorMetricId::exhausted_calls,"cursor.exhausted_calls","count","first active next returning no row",MetricKind::counter},
 {CursorMetricId::failed_calls,"cursor.failed_calls","count","active next throwing; excludes construction and closed/moved rejection",MetricKind::counter},
 {CursorMetricId::cancel_calls,"cursor.cancel_calls","count","explicit cancel while active; excludes idempotent closed cancel",MetricKind::counter},
 {CursorMetricId::cleanup_calls,"cursor.cleanup_calls","count","one admitted cursor close",MetricKind::counter},
 {CursorMetricId::clock_reads,"cursor.clock_reads","count","optional reads local to this cursor; excludes delta clock registry",MetricKind::counter},
 {CursorMetricId::clock_regressions,"cursor.clock_regressions","count","backward clock intervals; affected timing becomes unavailable",MetricKind::counter}
}};
bool cursor_clocks(const CursorObservation& value) noexcept {
 return value.options.mode==ObservationMode::timed ||
     (value.options.mode==ObservationMode::trace && value.options.trace_timings);
}
void cursor_add(CursorObservation& value,CursorMetricId id,std::uint64_t amount=1) noexcept {
 auto& metric=value.values[static_cast<std::size_t>(id)];
 if(metric.availability!=MetricAvailability::available)return;
 if(amount>UINT64_MAX-metric.value){metric.value=UINT64_MAX;metric.saturated=true;}
 else metric.value+=amount;
}
std::uint64_t cursor_now(CursorObservation& value,const std::shared_ptr<detail::ObservationState>& observer) noexcept {
 if(!cursor_clocks(value))return 0;
 cursor_add(value,CursorMetricId::clock_reads);if(observer)observer->note_cursor_clock_read();return detail::read_observation_clock();
}
void cursor_elapsed(CursorObservation& value,CursorMetricId id,std::uint64_t start,const std::shared_ptr<detail::ObservationState>& observer) noexcept {
 if(!cursor_clocks(value))return;
 const auto finish=cursor_now(value,observer);
 if(finish<start){cursor_add(value,CursorMetricId::clock_regressions);value.values[static_cast<std::size_t>(id)].availability=MetricAvailability::unavailable;}
 else cursor_add(value,id,finish-start);
}
}  // namespace

std::span<const CursorMetricDescriptor> cursor_observation_registry() noexcept { return cursor_registry; }
static_assert(std::is_trivially_copyable_v<CursorObservation>);

ProjectionSupportCount increment_support(ProjectionSupportCount value,std::uint64_t limit) {
  require(value.value<limit,"support_overflow","projection support exceeds its configured exact counter limit");
  return {value.value+1};
}
ProjectionSupportCount decrement_support(ProjectionSupportCount value) {
  require(value.value>0,"runtime_contract","projection support underflow"); return {value.value-1};
}

struct SupportRuntime::Impl {
  SupportOptions options;
  std::shared_ptr<detail::StorageWorkContext> storage_context;
  [[nodiscard]] storage::IndexWorkAllowance* work() const { return detail::compact_storage_work(storage_context); }
  std::shared_ptr<detail::ObservationState> observation;
  workload::detail::State workload;
  std::optional<CursorObservation> last_cursor;
  std::uint64_t next_cursor_id=0;
  bool cursor_id_saturated=false;
  SupportOwnerId owner=new_owner();
  std::uint64_t sequence=0;
  std::size_t readers=0;
  bool updating=false;
  resource::AccountedUnique<State> state;
  CompiledProgram plan;
  storage::TupleLayout sql_output;
  storage::TupleLayout core_output;
  MemoryVector<MemoryVector<std::size_t>> children;
  MemoryVector<std::optional<std::size_t>> incoming;
  template<class Source> Impl(Source p,SupportOptions o,std::shared_ptr<detail::StorageWorkContext> context):options(o),storage_context(std::move(context)),observation(detail::ObservationState::create(storage_context->memory(),o.observation)),
      workload(storage_context->memory()),
      state(resource::make_accounted_unique<State>(storage_context->memory(),resource::MemoryPurpose::support_metadata,std::move(p),work(),storage_context->memory())),
      plan(state->compiled),sql_output(state->compiled.sql_result_layout().descriptor()),core_output(state->compiled.result_layout().descriptor()),
      children(resource::MemoryAllocator<MemoryVector<std::size_t>>(storage_context->memory(),resource::MemoryPurpose::immutable_metadata)),
      incoming(program_nodes().size(),std::nullopt,resource::MemoryAllocator<std::optional<std::size_t>>(storage_context->memory(),resource::MemoryPurpose::immutable_metadata)) {
    require(!(options.observation.mode==ObservationMode::off && options.capture_transitions),"invalid_observation_options","off mode conflicts with allocating full transition capture");
    if (observation) observation->bind_owner(owner.value);
    require(options.support_limit>0,"invalid_options","projection support limit must be positive");
    require(options.order==PropagationOrder::fifo || options.order==PropagationOrder::lifo,"invalid_options","unknown propagation order");
    children.reserve(program_nodes().size());
    for (const auto& node : program_nodes()) children.emplace_back(node.children.size(),0,
        resource::MemoryAllocator<std::size_t>(storage_context->memory(),resource::MemoryPurpose::immutable_metadata));
    for (std::size_t i=0;i<program_edges().size();++i) {
      const auto& edge=program_edges()[i]; children[edge.parent.value][edge.child_slot]=i; incoming[edge.child.value]=i;
    }
  }
  void readable() const { require(!updating,"runtime_busy","a prepared logical epoch is active"); }
  void writable() const { readable(); require(readers==0,"runtime_busy","result cursors pin the committed epoch"); }
  void observe(const SupportMetrics& metrics) const noexcept {
    if (!observation) return;
    observation->set(MetricId::support_work,metrics.work);
    observation->set(MetricId::support_native_record_visits,metrics.native_record_visits);
    observation->set(MetricId::support_child_key_probes,metrics.child_key_probes);
    observation->set(MetricId::support_child_key_events,metrics.child_key_events);
    observation->set(MetricId::support_survivor_transitions,metrics.survivor_transitions);
    observation->set(MetricId::support_parent_key_transitions,metrics.parent_key_transitions);
    observation->set(MetricId::support_visible_key_transitions,metrics.visible_key_transitions);
    observation->set(MetricId::support_candidates_created,metrics.candidates_created);
    observation->set(MetricId::support_candidates_reclaimed,metrics.candidates_reclaimed);
    observation->set(MetricId::support_storage_changes,metrics.storage_changes);
    observation->set(MetricId::support_metadata_changes,metrics.metadata_changes);
    observation->set(MetricId::support_saved_child_flags,metrics.saved_child_flags);
    observation->set(MetricId::support_journal_records,metrics.journal_records);
    observation->set(MetricId::support_events_enqueued,metrics.events_enqueued);
    observation->set(MetricId::support_events_applied,metrics.events_applied);
    observation->set(MetricId::support_queue_peak,metrics.queue_peak);
    observation->set(MetricId::support_copied_rows,metrics.copied_rows);
    observation->set(MetricId::support_copied_index_memberships,metrics.copied_index_memberships);
    observation->set(MetricId::support_copied_metadata_entries,metrics.copied_metadata_entries);
    observation->set(MetricId::support_copied_child_flags,metrics.copied_child_flags);
  }
  SupportSnapshot snapshot(std::uint64_t visible_sequence) const;
  template<class Gauges> Gauges state_gauges(Gauges) const;
  const program::Span<SupportNodeProgram>& program_nodes() const {return state->program_nodes;}
  const program::Span<SupportEdgeProgram>& program_edges() const {return state->program_edges;}
  const SupportNodeProgram& node(NodeId id) const {
    require(id.value<program_nodes().size(),"invalid_native_update","node is outside the physical plan"); return program_nodes()[id.value];
  }
  SupportHandle handle(NodeId node,SupportRole role,TupleHandle value) const { return {owner,node,role,value.tuple}; }
  bool answer(const State& current) const {
    if (plan.route()==PhysicalRoute::constant_true) return true;
    if (plan.route()==PhysicalRoute::constant_false) return false;
    return current.storage.table(program_nodes()[plan.tree().root->value].survivors).size()!=0;
  }
  storage::Tuple plan_tuple(const storage::AccountedTuple& tuple) const {
    return storage::Tuple::from_accounted(state->compiled.layouts().at(tuple.layout().id().value)
        .tuple(tuple.values(),{resource::MemoryOwnerKind::output,0}));
  }
  struct Pending { std::size_t edge; bool appeared; storage::AccountedTuple key; std::uint64_t id; };
  struct Transaction {
    Impl& runtime;
    State& state;
    SupportEpoch& output;
    std::shared_ptr<SupportJournal> journal;
    std::deque<Pending,resource::MemoryAllocator<Pending>> pending;
    MemoryVector<std::uint8_t> applied;
    std::uint64_t cause=1;
    std::size_t checked_events=0;
    bool committed=false;
    BuildMetrics* build_metrics=nullptr;
    const BuildOptions* build_options=nullptr;
    enum class MetaKind { record_insert,record_change,record_erase,count_insert,count_change,count_erase };
    struct MetaUndo {
      MetaKind kind;
      NodeState* node;
      SupportRole role;
      TupleId id;
      std::optional<RecordState> record;
      ProjectionSupportCount count;
      NodeState::Records::node_type record_node;
      NodeState::Counts::node_type count_node;
    };
    MemoryVector<resource::AccountedUnique<MetaUndo>> undo;
    Transaction(Impl& r,State& s,SupportEpoch& o,std::shared_ptr<SupportJournal> j)
        :runtime(r),state(s),output(o),journal(std::move(j)),
         pending(resource::MemoryAllocator<Pending>(r.storage_context->memory(),resource::MemoryPurpose::support_metadata)),
         applied(resource::MemoryAllocator<std::uint8_t>(r.storage_context->memory(),resource::MemoryPurpose::support_metadata)),
         undo(resource::MemoryAllocator<resource::AccountedUnique<MetaUndo>>(r.storage_context->memory(),resource::MemoryPurpose::journal_undo)) {}
    ~Transaction() {
      if (committed) return;
      for (auto it=undo.rbegin();it!=undo.rend();++it) {
        auto& item=**it;
        auto& counts=item.role==SupportRole::parent_support ? item.node->parent : item.node->visible;
        switch (item.kind) {
          case MetaKind::record_insert: item.node->records.erase(item.id); break;
          case MetaKind::record_change:
            item.record->lifetime(resource::AllocationLifetime::active);
            item.node->records.at(item.id)=std::move(*item.record); break;
          case MetaKind::record_erase:
            item.node->lifetime(&item.record_node.mapped(),resource::AllocationLifetime::active);
            item.record_node.mapped().lifetime(resource::AllocationLifetime::active);
            if (!item.node->records.insert(std::move(item.record_node)).inserted) std::terminate();
            break;
          case MetaKind::count_insert: counts.erase(item.id); break;
          case MetaKind::count_change: counts.at(item.id)=item.count; break;
          case MetaKind::count_erase:
            item.node->lifetime(&item.count_node.mapped(),resource::AllocationLifetime::active);
            if (!counts.insert(std::move(item.count_node)).inserted) std::terminate();
            break;
        }
      }
      for (auto& [id,table] : journal->storage_) { static_cast<void>(id); table.rollback(); }
    }
    void commit() noexcept {
      for (auto& [id,table] : journal->storage_) { static_cast<void>(id); table.commit(); }
      // Public record pins cover every membership/counter change. Undo nodes
      // and their extra pins are needed only until the commit barrier.
      journal->storage_.clear(); committed=true; undo.clear();
    }
    void charge(std::uint64_t amount=1) {
      if (build_metrics) detail::build_metric(*build_metrics,*build_options,build_metrics->replay_work,amount);
      const auto used=output.metrics.work;
      require(amount<=std::numeric_limits<std::uint64_t>::max()-used,"resource_limit","support work counter exhausted");
      require(!runtime.options.work_limit || (used<=*runtime.options.work_limit && amount<=*runtime.options.work_limit-used),
          "resource_limit","logical support update work limit exceeded; previous state preserved");
      output.metrics.work+=amount;
    }
    void metric(std::uint64_t& value,std::uint64_t amount=1) {
      // Every managed category starts at zero and increments only after charge,
      // including queue_peak increases; it is bounded by cumulative work.
      charge(amount); value+=amount;
    }
    storage::AccountedStorageTable::Journal& writer(RelationId id) {
      // Reuse existing journals: linear in the number of touched relations.
      for (auto& [relation,table] : journal->storage_) if (id==relation) return table;
      auto scope=state.storage.table(id).journal(detail::owning_storage_work(runtime.storage_context));
      journal->storage_.emplace_back(id,std::move(scope));
      return journal->storage_.back().second;
    }
    TupleHandle insert(RelationId id,const storage::AccountedTuple& tuple) {
      metric(output.metrics.storage_changes);
      const auto result=writer(id).insert(tuple);
      require(result.inserted,"runtime_contract","internal insert duplicated membership"); return result.handle;
    }
    void erase(RelationId id,TupleHandle handle) {
      metric(output.metrics.storage_changes);
      require(writer(id).erase(handle),"runtime_contract","internal erase lost membership");
    }
    resource::AccountedUnique<MetaUndo> prepare(MetaKind kind,const SupportNodeProgram& node,SupportRole role,TupleId id) {
      metric(output.metrics.metadata_changes);
      auto item=resource::make_accounted_unique<MetaUndo>(state.nodes[node.id.value].attribution,
          runtime.storage_context->memory(),resource::MemoryPurpose::journal_undo);
      item.get_deleter().set_lifetime(item.get(),resource::AllocationLifetime::retained);
      item->kind=kind; item->node=&state.nodes[node.id.value]; item->role=role; item->id=id;
      if (undo.size()==undo.max_size()) throw Error("resource_limit","metadata journal exhausted");
      if (undo.size()==undo.capacity()) undo.reserve(undo.size()+std::min(undo.max_size()-undo.size(),std::max<std::size_t>(1,undo.size())));
      return item;
    }
    static SupportValueState record_value(const RecordState& record) {
      return {true,record.satisfied,retained_flags(record),{}};
    }
    static SupportValueState count_value(ProjectionSupportCount value) { return {true,{}, {},value}; }
    void note(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,SupportValueState before,SupportValueState after) {
      metric(output.metrics.journal_records);
      auto pin=state.storage.table(relation(node,role)).pin(handle, runtime.work());
      if (role==SupportRole::survivors)
        runtime.workload.support(node.id,role,static_cast<std::uint64_t>(before.member),static_cast<std::uint64_t>(after.member));
      else if (role==SupportRole::parent_support || role==SupportRole::visible)
        runtime.workload.support(node.id,role,before.support?before.support->value:0,after.support?after.support->value:0);
      journal->records.push_back({output.metrics.journal_records,cause,runtime.handle(node.id,role,handle),
          std::move(before),std::move(after),std::move(pin)});
      if (runtime.observation) {
        const auto& item=journal->records.back();
        const auto number=[](const SupportValueState& value) noexcept {
          return value.support?value.support->value:value.satisfied?
              static_cast<std::uint64_t>(value.satisfied->value):static_cast<std::uint64_t>(value.member);
        };
        runtime.observation->event(TraceKind::journal,item.ordinal,cause,node.id.value,
            observation_no_id,0,number(item.before),number(item.after),static_cast<std::uint64_t>(role),handle.tuple.value);
      }
    }
    void record(const SupportNodeProgram& node,TupleHandle handle,std::optional<RecordState> desired) {
      auto& records=state.nodes[node.id.value].records; const auto found=records.find(handle.tuple);
      require(found!=records.end() || desired.has_value(),"runtime_contract","erasing absent record metadata");
      const auto kind=found==records.end() ? MetaKind::record_insert : desired ? MetaKind::record_change : MetaKind::record_erase;
      auto item=prepare(kind,node,SupportRole::records,handle.tuple);
      if (kind==MetaKind::record_change) {
        metric(output.metrics.saved_child_flags,static_cast<std::uint64_t>(found->second.present.size()));
        item->record=found->second;
        item->record->lifetime(resource::AllocationLifetime::retained);
      }
      note(node,SupportRole::records,handle,found==records.end()?SupportValueState{}:record_value(found->second),
          desired?record_value(*desired):SupportValueState{});
      if (kind==MetaKind::record_insert) {
        require(records.emplace(handle.tuple,std::move(*desired)).second,"runtime_contract","record metadata already exists");
      } else if (kind==MetaKind::record_change) found->second=std::move(*desired);
      else {
        state.nodes[node.id.value].lifetime(&found->second,resource::AllocationLifetime::retained);
        found->second.lifetime(resource::AllocationLifetime::retained);
        item->record_node=records.extract(found);
      }
      undo.push_back(std::move(item));
    }
    void counter(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,std::optional<ProjectionSupportCount> desired) {
      auto& counts=role==SupportRole::parent_support?state.nodes[node.id.value].parent:state.nodes[node.id.value].visible;
      const auto found=counts.find(handle.tuple);
      require(found!=counts.end() || desired.has_value(),"runtime_contract","erasing absent count metadata");
      const auto kind=found==counts.end()?MetaKind::count_insert:desired?MetaKind::count_change:MetaKind::count_erase;
      auto item=prepare(kind,node,role,handle.tuple);
      if (found!=counts.end()) item->count=found->second;
      note(node,role,handle,found==counts.end()?SupportValueState{}:count_value(found->second),
          desired?count_value(*desired):SupportValueState{});
      if (kind==MetaKind::count_insert) {
        require(counts.emplace(handle.tuple,*desired).second,"runtime_contract","count metadata already exists");
      } else if (kind==MetaKind::count_change) found->second=*desired;
      else {
        state.nodes[node.id.value].lifetime(&found->second,resource::AllocationLifetime::retained);
        item->count_node=counts.extract(found);
      }
      undo.push_back(std::move(item));
    }
    void event(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,SetOperation operation,const storage::AccountedTuple& tuple) {
      if (runtime.options.capture_transitions) output.transitions.push_back({runtime.handle(node.id,role,handle),operation,runtime.plan_tuple(tuple),cause});
    }
    void start() {
      metric(output.metrics.events_enqueued); applied.push_back(true); metric(output.metrics.events_applied);
      cause=output.metrics.events_enqueued;
    }
    void native_trace(const SupportNodeProgram& node,TupleHandle handle,const storage::AccountedTuple& tuple,bool add) {
      if (runtime.observation) runtime.observation->event(TraceKind::native_event,cause,0,node.id.value,
          observation_no_id,0,static_cast<std::uint64_t>(!add),static_cast<std::uint64_t>(add),
          static_cast<std::uint64_t>(SupportRole::records),handle.tuple.value);
      if (runtime.options.capture_transitions) journal->events.push_back({cause,0,output.sequence,output.metrics.events_applied,SupportEventKind::native_update,
          node.id,{},runtime.handle(node.id,SupportRole::records,handle),add?SetOperation::insert:SetOperation::erase,runtime.plan_tuple(tuple),!add,add});
    }
    void enqueue(std::size_t edge_id,bool add,const storage::AccountedTuple& key,TupleHandle source) {
      metric(output.metrics.events_enqueued);
      const auto id=output.metrics.events_enqueued;
      applied.push_back(false); pending.push_back({edge_id,add,key.clone(),id});
      if (runtime.observation) runtime.observation->event(TraceKind::child_enqueued,id,cause,
          runtime.program_edges()[edge_id].parent.value,observation_no_id,0,
          static_cast<std::uint64_t>(!add),static_cast<std::uint64_t>(add));
      if (pending.size()>output.metrics.queue_peak) metric(output.metrics.queue_peak,static_cast<std::uint64_t>(pending.size())-output.metrics.queue_peak);
      if (runtime.options.capture_transitions) {
        const auto& edge=runtime.program_edges()[edge_id];
        journal->events.push_back({id,cause,output.sequence,0,SupportEventKind::child_key,edge.parent,edge.child_slot,
            runtime.handle(edge.child,SupportRole::parent_support,source),add?SetOperation::insert:SetOperation::erase,runtime.plan_tuple(key),!add,add});
      }
    }
    // Boolean support primitive: add/remove one surviving local witness.
    // P/E counts remain positive exactly while the projected key is stored;
    // return a handle only at 0<->1 membership crossings. Journals/metadata undo
    // are already owned by this stage. Positive-to-positive changes stop here.
    // P1 v2 section 4.2; docs/support_invariants.md and code_specs/primitives.md.
    std::optional<TupleHandle> count(const SupportNodeProgram& node,SupportRole role,const storage::AccountedTuple& key,bool add) {
      charge(); const auto id=relation(node,role); const auto& table=state.storage.table(id);
      const auto& counts=role==SupportRole::parent_support ? state.nodes[node.id.value].parent : state.nodes[node.id.value].visible;
      const auto found=table.find(key, runtime.work()); TupleHandle crossing{};
      if (add) {
        if (found) { counter(node,role,*found,increment_support(counts.at(found->tuple),runtime.options.support_limit)); return {}; }
        const auto initial=increment_support({},runtime.options.support_limit);
        crossing=insert(id,key); counter(node,role,crossing,initial); event(node,role,crossing,SetOperation::insert,key);
      } else {
        require(found.has_value(),"runtime_contract","removing an absent projected support key");
        const auto next=decrement_support(counts.at(found->tuple));
        if (next.value>0) { counter(node,role,*found,next); return {}; }
        crossing=*found; counter(node,role,crossing,{}); event(node,role,crossing,SetOperation::erase,key); erase(id,crossing);
      }
      if (role==SupportRole::parent_support) metric(output.metrics.parent_key_transitions);
      else metric(output.metrics.visible_key_transitions);
      return crossing;
    }
    // Change S once, then adjust its parent-key P and output-key E projections.
    // Only a P membership crossing queues an ancestor event; E remains local
    // enumeration state. Every throwing step is inside the stage rollback scope.
    void survivor(const SupportNodeProgram& node,const storage::AccountedTuple& tuple,bool add) {
      charge(); const auto& table=state.storage.table(node.survivors);
      if (add) {
        const auto handle=insert(node.survivors,tuple); note(node,SupportRole::survivors,handle,{}, {true,{}, {},{}});
        event(node,SupportRole::survivors,handle,SetOperation::insert,tuple);
      } else {
        const auto found=table.find(tuple, runtime.work()); require(found.has_value(),"runtime_contract","survivor already absent");
        note(node,SupportRole::survivors,*found,{true,{}, {},{}},{});
        event(node,SupportRole::survivors,*found,SetOperation::erase,tuple); erase(node.survivors,*found);
      }
      metric(output.metrics.survivor_transitions);
      const auto key=node.parent_key.apply(tuple);
      const auto crossing=count(node,SupportRole::parent_support,key,add);
      if (crossing && runtime.incoming[node.id.value]) enqueue(*runtime.incoming[node.id.value],add,key,*crossing);
      if (node.visible_projection) static_cast<void>(count(node,SupportRole::visible,node.visible_projection->apply(tuple),add));
    }
    void native(const SupportNodeProgram& node,const storage::AccountedTuple& tuple,bool add) {
      const auto& records=state.storage.table(node.records); const auto& metadata=state.nodes[node.id.value].records;
      metric(output.metrics.native_record_visits);
      if (add) {
        auto value=state.nodes[node.id.value].record(node.children.size());
        for (std::size_t slot=0;slot<node.children.size();++slot) {
          metric(output.metrics.child_key_probes);
          const auto& edge=runtime.program_edges()[runtime.children[node.id.value][slot]];
          const auto& child=runtime.program_nodes()[edge.child.value];
          value.present[slot]=state.storage.table(child.parent_support).find(edge.parent_key.apply(tuple), runtime.work()).has_value();
          if (value.present[slot]) ++value.satisfied.value;
        }
        const auto handle=insert(node.records,tuple); native_trace(node,handle,tuple,true);
        const bool survives=value.satisfied.value==node.children.size(); record(node,handle,std::move(value));
        event(node,SupportRole::records,handle,SetOperation::insert,tuple);
        if (survives) survivor(node,tuple,true);
      } else {
        const auto found=records.find(tuple, runtime.work()); require(found.has_value(),"runtime_contract","native tuple already absent");
        native_trace(node,*found,tuple,false);
        if (metadata.at(found->tuple).satisfied.value==node.children.size()) survivor(node,tuple,false);
        event(node,SupportRole::records,*found,SetOperation::erase,tuple);
        record(node,*found,{}); erase(node.records,*found);
      }
    }
    // Consume one child-presence bit transition, never its witness count.
    // The saved RecordState is the inverse for this metadata change. A native
    // row survives iff every child bit is set; a generalized candidate is
    // reclaimed only when no child supplies its key. Fan-out copying is explicit.
    void presence(const SupportNodeProgram& node,TupleHandle handle,RecordState& value,std::size_t slot,bool add,const storage::AccountedTuple& tuple) {
      charge(); require(slot<value.present.size() && value.present[slot]!=add,"runtime_contract","child membership transition applied twice");
      const bool before=value.satisfied.value==node.children.size();
      auto next=value; next.present[slot]=add;
      if (add) ++next.satisfied.value;
      else { require(next.satisfied.value>0,"runtime_contract","satisfied-child underflow"); --next.satisfied.value; }
      const bool after=next.satisfied.value==node.children.size(); record(node,handle,std::move(next));
      if (before!=after) survivor(node,tuple,after);
      if (node.kind==NodeKind::generalized && value.satisfied.value==0) {
        event(node,SupportRole::records,handle,SetOperation::erase,tuple);
        record(node,handle,{}); erase(node.records,handle); metric(output.metrics.candidates_reclaimed);
      }
    }
    void child(const Pending& event) {
      metric(output.metrics.child_key_events);
      const auto& edge=runtime.program_edges()[event.edge]; const auto& parent=runtime.program_nodes()[edge.parent.value];
      const auto& table=state.storage.table(parent.records); auto& metadata=state.nodes[parent.id.value].records;
      if (parent.kind==NodeKind::native) {
        // This update path materializes O(matching rows) accounted handles;
        // the result cursor separately uses lazy live/bucket traversal.
        const auto matching=table.bucket(state.storage.index(*edge.reverse_index),event.key,runtime.work());
        runtime.workload.touched(event.edge,event.appeared,static_cast<std::uint64_t>(matching.size()));
        for (const auto handle : matching) {
          metric(output.metrics.native_record_visits);
          if (runtime.observation) {
            runtime.observation->add(MetricId::support_reverse_index_records_visited);
            runtime.observation->event(TraceKind::reverse_visit,event.id,cause,parent.id.value,
                observation_no_id,0,0,0,static_cast<std::uint64_t>(SupportRole::records),handle.tuple.value);
          }
          const auto* tuple=table.get(handle, runtime.work());
          require(tuple!=nullptr,"runtime_contract","reverse separator index contains a stale native handle");
          presence(parent,handle,metadata.at(handle.tuple),edge.child_slot,event.appeared,*tuple);
        }
      } else {
        auto found=table.find(event.key, runtime.work());
        runtime.workload.touched(event.edge,event.appeared,static_cast<std::uint64_t>(found.has_value()));
        if (!found) {
          require(event.appeared,"runtime_contract","child removal has no generalized candidate");
          found=insert(parent.records,event.key);
          record(parent,*found,state.nodes[parent.id.value].record(parent.children.size()));
          metric(output.metrics.candidates_created); this->event(parent,SupportRole::records,*found,SetOperation::insert,event.key);
        }
        presence(parent,*found,metadata.at(found->tuple),edge.child_slot,event.appeared,event.key);
      }
    }
    void drain() {
      while (!pending.empty()) {
        auto event=runtime.options.order==PropagationOrder::fifo?std::move(pending.front()):std::move(pending.back());
        if (runtime.options.order==PropagationOrder::fifo) pending.pop_front(); else pending.pop_back();
        require(event.id>0 && event.id<=applied.size() && !applied[static_cast<std::size_t>(event.id-1)],"runtime_contract","event applied more than once");
        applied[static_cast<std::size_t>(event.id-1)]=true; metric(output.metrics.events_applied); cause=event.id;
        if (runtime.options.capture_transitions) journal->events.at(static_cast<std::size_t>(event.id-1)).applied_ordinal=output.metrics.events_applied;
        if (runtime.observation) runtime.observation->event(TraceKind::child_applied,event.id,0,
            runtime.program_edges()[event.edge].parent.value);
        child(event);
      }
      charge(static_cast<std::uint64_t>(applied.size()-checked_events));
      require(output.metrics.events_applied==output.metrics.events_enqueued,"runtime_contract","event queue did not account every event");
      for (;checked_events<applied.size();++checked_events)
        require(applied[checked_events],"runtime_contract","event queue did not apply every event exactly once");
    }
  };
};

struct SupportRuntime::EpochView::Group {
  enum class Phase { tentative, committed, aborted };
  struct Patch {
    using Restored=MemoryMap<TupleId,const storage::AccountedTuple*>;
    using RestoredByKey=MemoryMap<storage::AccountedRow,const storage::AccountedTuple*,CompactRowLess>;
    using RestoredBucket=MemoryMap<storage::AccountedRow,Restored,CompactRowLess>;
    using ByIndex=MemoryMap<std::size_t,RestoredBucket>;
    MemorySet<TupleId> excluded;
    Restored restored;
    RestoredByKey restored_by_key;
    ByIndex restored_by_index;
    explicit Patch(const resource::MemoryAccount& account)
        :excluded(std::less<TupleId>{},MemorySet<TupleId>::allocator_type(account,resource::MemoryPurpose::cursor)),
         restored(memory_map<Restored>(account)),restored_by_key(memory_map<RestoredByKey>(account)),
         restored_by_index(memory_map<ByIndex>(account)) {}
    resource::MemoryAccount memory() const {return restored.get_allocator().account();}
    Restored& bucket(std::size_t index,storage::RowView key) {
      auto [entry,inserted]=restored_by_index.try_emplace(index,memory_map<RestoredBucket>(memory()));
      static_cast<void>(inserted);auto& buckets=entry->second;
      auto found=buckets.find(key);
      if(found==buckets.end()) found=buckets.emplace(storage::AccountedRow::copy_of(memory(),key),memory_map<Restored>(memory())).first;
      return found->second;
    }
  };
  std::shared_ptr<Impl> runtime;
  detail::StorageWorkLease storage_lease;
  CompiledProgram plan;
  std::shared_ptr<const SupportJournal> journal;
  MemoryVector<Patch> patches;
  std::uint64_t before_sequence, after_sequence;
  std::size_t record_begin;
  std::uint64_t before_prefix, after_prefix;
  SupportOwnerId identity;
  bool before_answer, after_answer, leased=false;
  Phase phase;
  EpochViewMetrics metrics;
  ResultCursor::Data* first=nullptr;
  Group(std::shared_ptr<Impl> owner,std::shared_ptr<const SupportJournal> changes,
      std::uint64_t before,std::uint64_t after,bool old_answer,bool new_answer,Phase state,EpochViewOptions options,
      std::size_t begin=0,std::uint64_t old_prefix=0,std::uint64_t new_prefix=0)
      :runtime(std::move(owner)),storage_lease(detail::storage_lease(runtime->storage_context)),plan(runtime->state->compiled),journal(std::move(changes)),
       patches(resource::MemoryAllocator<Patch>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor)),
       before_sequence(before),after_sequence(after),record_begin(begin),before_prefix(old_prefix),after_prefix(new_prefix),
       identity(runtime->owner),before_answer(old_answer),after_answer(new_answer),phase(state) {
    program_words<Patch>(runtime->work(),plan.relations().size());
    patches.reserve(plan.relations().size());
    for(std::size_t i=0;i<plan.relations().size();++i) patches.emplace_back(runtime->storage_context->memory());
    const auto note=[&](std::uint64_t& counter,std::uint64_t amount=1) {
      require(amount<=std::numeric_limits<std::uint64_t>::max()-metrics.work &&
          (!options.work_limit || (metrics.work<=*options.work_limit && amount<=*options.work_limit-metrics.work)),
          "resource_limit","epoch view construction work limit exceeded"); metrics.work+=amount; counter+=amount;
    };
    require(!journal || begin<=journal->records.size(),"invalid_snapshot","journal checkpoint is beyond the drained prefix");
    if (journal) for (std::size_t i=begin;i<journal->records.size();++i) {
      const auto& record=journal->records[i];
      note(metrics.journal_records);
      if (record.before.member==record.after.member) continue;
      note(metrics.membership_changes);
      auto& patch=patches[relation(runtime->program_nodes()[record.handle.node.value],record.handle.role).value];
      if (record.before.member) {
        note(metrics.restored_rows);
        const auto [restored,inserted]=patch.restored.emplace(record.handle.tuple,&record.tuple());
        static_cast<void>(restored);
        require(inserted,"runtime_contract","before-side patch repeated a restored tuple handle");
        note(metrics.restored_key_entries);
        note(metrics.key_fields,static_cast<std::uint64_t>(record.tuple().values().size()));
        require(patch.restored_by_key.emplace(storage::AccountedRow::copy_of(runtime->storage_context->memory(),record.tuple().values()),&record.tuple()).second,
            "runtime_contract","before-side patch repeated a restored full key");
        const auto relation_id=relation(runtime->program_nodes()[record.handle.node.value],record.handle.role);
        for (const auto& index : plan.indexes()) if (index.relation==relation_id) {
          note(metrics.restored_bucket_entries);
          note(metrics.key_fields,static_cast<std::uint64_t>(index.projection.fields().size()));
          const auto key=runtime->state->storage.projection(index.id).apply(record.tuple());
          auto& bucket=patch.bucket(index.id.value,key.values());
          require(bucket.emplace(record.handle.tuple,&record.tuple()).second,
              "runtime_contract","before-side patch repeated a restored bucket handle");
        }
      } else { note(metrics.excluded_rows); patch.excluded.insert(record.handle.tuple); }
    }
  }
  void acquire() {
    require(runtime->readers!=std::numeric_limits<std::size_t>::max(),"resource_limit","epoch view reader count exhausted");
    ++runtime->readers; leased=true;
  }
  void release() noexcept {
    if (leased) {
      if (!runtime || runtime->readers==0) std::terminate();
      --runtime->readers; leased=false;
    }
  }
  void abort() noexcept;
  ~Group() { if (first) std::terminate(); release(); }
};
struct SupportRuntime::EpochView::Data {
  std::shared_ptr<Group> group;
  SnapshotSide side;
  Data(std::shared_ptr<Group> owner,SnapshotSide which):group(std::move(owner)),side(which) {}
  void readable() const { require(group->phase!=Group::Phase::aborted,"invalid_snapshot","epoch view was aborted"); }
};

struct SupportRuntime::ResultCursor::Data {
  struct Source {
    enum class Kind { fixed, local, outer };
    Kind kind;
    VariableId variable{0};
    AssignmentSlot slot{0,FieldId{0}};
  };
  struct Condition { FieldId field; Source source; };
  struct Frame {
    std::optional<storage::AccountedStorageTable::Cursor> cursor;
    std::optional<storage::AccountedTuple> key, direct;
    bool opened=false, direct_used=false, ghosts=false;
    const EpochView::Group::Patch* patch=nullptr;
    const EpochView::Group::Patch::Restored* ghost_rows=nullptr;
    EpochView::Group::Patch::Restored::const_iterator ghost;
    std::optional<storage::AccountedTuple> prebound_key;
    const storage::AccountedTuple* selected=nullptr;
    MemoryVector<Condition> conditions;
    std::optional<MemoryVector<Source>> lookup;
    std::size_t child=0;
    explicit Frame(const resource::MemoryAccount& account)
        :conditions(resource::MemoryAllocator<Condition>(account,resource::MemoryPurpose::cursor)) {}
  };
  std::shared_ptr<Impl> runtime;
  detail::StorageWorkLease storage_lease;
  CompiledProgram plan;
  ResultCursorOptions options;
  ResultView view;
  storage::AccountedLayout native_output_layout;
  storage::TupleLayout output_layout;
  ResultCursorMetrics metrics;
  ResultCursorMetrics* startup_sink=nullptr;
  std::shared_ptr<detail::ObservationState> observation;
  std::weak_ptr<Impl> diagnostic_owner;
  CursorObservation diagnostic;
  bool observation_admitted=false;
  void publish() noexcept {
    if(!observation || !observation_admitted)return;
    diagnostic.mandatory=metrics;diagnostic.state=status;
    if(auto owner=diagnostic_owner.lock())owner->last_cursor=diagnostic;
  }
  template<class Make> static resource::AccountedUnique<Data> create(const std::shared_ptr<Impl>& owner,
      ResultCursorOptions limits,ResultView view,CursorObservationSource source,
      std::optional<SnapshotSide> side,bool tentative,std::uint64_t epoch,Make make) {
    CursorObservation summary;
    summary.options=owner->options.observation;summary.owner=owner->owner.value;
    summary.sequence=epoch;summary.limits=limits;summary.view=view;summary.source=source;
    summary.side=side;summary.tentative_at_creation=tentative;
    const bool enabled=bool(owner->observation);
    if(enabled){
      if(owner->next_cursor_id==UINT64_MAX)owner->cursor_id_saturated=true;else ++owner->next_cursor_id;
      summary.cursor_id=owner->next_cursor_id;summary.cursor_id_saturated=owner->cursor_id_saturated;
      summary.configuration=owner->observation->configuration();summary.terminal_reason=CursorTerminalReason::none;
    }
    for(const auto& entry:cursor_registry)summary.values[static_cast<std::size_t>(entry.id)].availability=
      !enabled || (entry.kind==MetricKind::timing && !cursor_clocks(summary))?MetricAvailability::disabled:MetricAvailability::available;
    const auto start=cursor_now(summary,owner->observation);
    try {
      auto cursor=make(enabled?&summary.mandatory:nullptr);
      cursor->startup_sink=nullptr;
      if(source==CursorObservationSource::committed_results){++owner->readers;cursor->leased=true;}
      else cursor->link();
      summary.constructed=true;summary.mandatory=cursor->metrics;
      cursor_elapsed(summary,CursorMetricId::startup_ns,start,owner->observation);
      cursor->diagnostic=summary;cursor->observation_admitted=enabled;cursor->publish();return cursor;
    }catch(...){
      if(enabled){
        cursor_elapsed(summary,CursorMetricId::startup_ns,start,owner->observation);
        summary.state=ResultCursorState::failed;summary.terminal_reason=CursorTerminalReason::startup_failure;
        summary.values[static_cast<std::size_t>(CursorMetricId::cleanup_ns)].availability=MetricAvailability::unavailable;
        summary.values[static_cast<std::size_t>(CursorMetricId::cleanup_calls)].availability=MetricAvailability::unavailable;
        owner->last_cursor=summary;
      }
      throw;
    }
  }
  ResultCursorState status=ResultCursorState::active;
  std::uint64_t epoch;
  SupportOwnerId identity;
  bool leased=false, resume=false, answer, scalar, witness_mode=false;
  using Frames=MemoryVector<Frame>;
  Frames frames;
  std::size_t position=0;
  std::shared_ptr<EpochView::Data> snapshot;
  Data* previous=nullptr;
  Data* next=nullptr;
  std::optional<SupportEnumerationProgram> fragment_program;
  using Fixed=MemoryMap<VariableId,storage::AccountedRow>;
  Fixed fixed;
  SupportEnumerationProgram probe_program;
  Frames probe_frames;
  MemoryVector<MemoryVector<std::size_t>> probe_children;
  const program::EnumerationProgram& program() const { return fragment_program?fragment_program->view():runtime->state->enumeration; }
  void resize_frames(Frames& target,std::size_t size) {
    target.reserve(size);
    while (target.size()<size) target.emplace_back(runtime->storage_context->memory());
  }

  Data(std::shared_ptr<Impl> owner,ResultCursorOptions limits,ResultView mode,bool initialize=true,ResultCursorMetrics* startup=nullptr)
      :runtime(std::move(owner)),storage_lease(detail::storage_lease(runtime->storage_context)),plan(runtime->state->compiled),options(limits),view(mode),
       native_output_layout(view==ResultView::sql?plan.sql_result_layout():plan.result_layout()),output_layout(native_output_layout.descriptor()),
       startup_sink(startup),observation(runtime->observation),diagnostic_owner(observation?runtime:std::shared_ptr<Impl>{}),
       epoch(runtime->sequence),identity(runtime->owner),answer(runtime->answer(*runtime->state)),
       scalar(view==ResultView::sql && plan.normalized() && plan.normalized()->binding.wrapper==frontend::SqlWrapper::exists),
       frames(resource::MemoryAllocator<Frame>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor)),
       fixed(memory_map<Fixed>(runtime->storage_context->memory())),
       probe_program(runtime->storage_context->memory()),
       probe_frames(resource::MemoryAllocator<Frame>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor)),
       probe_children(resource::MemoryAllocator<MemoryVector<std::size_t>>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor)) {
    metric(metrics.startup,&CursorWork::route_checks);
    if (!scalar && initialize) {
      metric(metrics.startup,&CursorWork::frame_initializations,static_cast<std::uint64_t>(runtime->state->enumeration.steps.size()));
      resize_frames(frames,runtime->state->enumeration.steps.size());
    }
  }
  template<class Bindings>
  Data(std::shared_ptr<EpochView::Data> context,const Bindings& bindings,VisibleFragment fragment,ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr)
      :Data(context->group->runtime,limits,ResultView::core,false,startup) {
    bind_values(std::move(context),bindings);
    if (fragment.root) {
      require(fragment.root->value<runtime->program_nodes().size() && runtime->program_nodes()[fragment.root->value].connex,
          "invalid_fragment","visible fragment root is outside C*");
      fragment_program.emplace(runtime->storage_context->memory()); auto& output=*fragment_program;
      auto positions=memory_map<MemoryMap<std::size_t,std::size_t>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
      auto first_field=memory_map<MemoryMap<VariableId,AssignmentSlot>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
      for (std::size_t i=0;i<runtime->state->enumeration.steps.size();++i) {
        metric(metrics.startup,&CursorWork::fragment_steps);
        const auto& source=runtime->state->enumeration.steps[i]; auto node=std::optional<NodeId>{source.node};
        while (node && *node!=*fragment.root) node=runtime->program_nodes()[node->value].parent;
        if (!node) continue;
        auto step=source; const auto position=output.steps.size();
        if (step.parent_step && positions.contains(*step.parent_step)) step.parent_step=positions.at(*step.parent_step);
        else { step.parent_step.reset(); step.parent_key.reset(); step.bucket_index.reset(); step.depth=1; }
        if (step.parent_step) step.depth=output.steps[*step.parent_step].depth+1;
        positions.emplace(i,position); output.depth=std::max(output.depth,step.depth); output.steps.push_back(std::move(step));
        const auto& fields=plan.relations()[source.relation.value].layout.fields();
        for (std::size_t field=0;field<fields.size();++field) {
          const auto [previous_field,inserted]=first_field.emplace(*fields[field].variable,AssignmentSlot{position,FieldId{field}});
          if (!inserted) output.equalities.push_back({previous_field->second,{position,FieldId{field}}});
        }
      }
      MemoryVector<VariableId> variables(resource::MemoryAllocator<VariableId>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));
      for (const auto& [variable,slot] : first_field) { variables.push_back(variable); output.output.push_back(slot); }
      require(plan.layouts().size()!=std::numeric_limits<std::size_t>::max(),"storage_overflow","fragment output layout ID exhausted");
      native_output_layout=plan.scope_layout(LayoutId{plan.layouts().size()+1},variables,
          ":visible-fragment",runtime->work());output_layout=native_output_layout.descriptor();
      answer=true;
    }
    initialize(program(),frames);
    MemorySet<VariableId> visible(std::less<VariableId>{},MemorySet<VariableId>::allocator_type(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));
    for (const auto& output : plan.query().head) visible.insert(output.variable);
    bool hidden=false;
    for (const auto& [variable,value] : fixed) { static_cast<void>(value); hidden=hidden || !visible.contains(variable); }
    if (hidden && plan.route()==PhysicalRoute::tree) {
      probe_program=survivors(WitnessFragment{fragment.root,std::nullopt});
      bool relevant=false;
      for (const auto& step : probe_program.steps)
        for (const auto& field : plan.relations()[step.relation.value].layout.fields())
          relevant=relevant || (fixed.contains(*field.variable) && !visible.contains(*field.variable));
      if (relevant) {
        auto outer=memory_map<MemoryMap<VariableId,AssignmentSlot>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
        for (std::size_t i=0;i<program().steps.size();++i) {
          const auto& fields=plan.relations()[program().steps[i].relation.value].layout.fields();
          for (std::size_t field=0;field<fields.size();++field) outer.emplace(*fields[field].variable,AssignmentSlot{i,FieldId{field}});
        }
        initialize(probe_program,probe_frames,outer); probe_children.reserve(probe_frames.size());
        while (probe_children.size()<probe_frames.size()) probe_children.emplace_back(
            resource::MemoryAllocator<std::size_t>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor));
        for (std::size_t i=0;i<probe_program.steps.size();++i)
          if (probe_program.steps[i].parent_step) probe_children[*probe_program.steps[i].parent_step].push_back(i);
      } else probe_program.clear();
    }
  }
  Data(std::shared_ptr<EpochView::Data> context,const FixedAssignment& bindings,WitnessFragment fragment,ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr)
      :Data(context->group->runtime,limits,ResultView::core,false,startup) {
    bind(std::move(context),bindings); witness_mode=true;
    fragment_program=survivors(fragment);
    MemoryVector<VariableId> variables(resource::MemoryAllocator<VariableId>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));
    for (const auto slot : program().output)
      variables.push_back(*plan.relations()[program().steps[slot.step].relation.value].layout.fields()[slot.field.value].variable);
    require(plan.layouts().size()!=std::numeric_limits<std::size_t>::max(),"storage_overflow","fragment output layout ID exhausted");
    native_output_layout=plan.scope_layout(LayoutId{plan.layouts().size()+1},variables,
        ":witness-fragment",runtime->work());output_layout=native_output_layout.descriptor();
    if (fragment.root || fragment.nodes) answer=true;
    initialize(program(),frames);
  }
  Data(std::shared_ptr<EpochView::Data> context,NodeId id,ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr)
      :Data(context->group->runtime,limits,ResultView::core,false,startup) {
    bind(std::move(context),{});
    require(id.value<runtime->program_nodes().size() && runtime->program_nodes()[id.value].visible_relation,
        "invalid_fragment","visible factor is outside C*");
    const auto relation=*runtime->program_nodes()[id.value].visible_relation;
    native_output_layout=plan.relations()[relation.value].layout;output_layout=native_output_layout.descriptor();
    fragment_program.emplace(runtime->storage_context->memory()); auto& walk=*fragment_program;
    walk.steps.push_back({id,relation,1,{},{},{}}); walk.depth=1;
    for (std::size_t i=0;i<output_layout.fields().size();++i) walk.output.push_back({0,FieldId{i}});
    // A local E factor can contain rows even when the global answer is empty.
    answer=true; initialize(walk,frames);
  }
  template<class Separator>
  Data(std::shared_ptr<EpochView::Data> context,NodeId id,const Separator& separator,ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr)
      :Data(context->group->runtime,limits,ResultView::core,false,startup) {
    bind(std::move(context),{});
    require(id.value<runtime->program_nodes().size() && runtime->program_nodes()[id.value].visible_relation,
        "invalid_fragment","visible factor is outside C*");
    auto step_it=runtime->state->enumeration.steps.begin();
    for (;step_it!=runtime->state->enumeration.steps.end();++step_it) {
      metric(metrics.startup,&CursorWork::descriptor_steps);
      if (step_it->node==id) break;
    }
    require(step_it!=runtime->state->enumeration.steps.end() && step_it->parent_step && step_it->parent_key && step_it->bucket_index,
        "invalid_fragment","visible factor has no compiled parent-separator index");
    require(step_it->bucket_index->value<plan.indexes().size(),
        "runtime_contract","visible factor separator index is out of range");
    const auto& index=plan.indexes()[step_it->bucket_index->value];
    require(index.relation==step_it->relation,"runtime_contract","visible factor separator index targets another relation");
    auto step=*step_it; step.parent_step.reset(); step.depth=1;
    fragment_program.emplace(runtime->storage_context->memory()); auto& walk=*fragment_program;
    walk.steps.push_back(std::move(step)); walk.depth=1;
    native_output_layout=plan.relations()[index.relation.value].layout;output_layout=native_output_layout.descriptor();
    for (std::size_t field=0;field<output_layout.fields().size();++field) walk.output.push_back({0,FieldId{field}});
    answer=true; initialize(walk,frames);
    metric(metrics.startup,&CursorWork::key_fields,static_cast<std::uint64_t>(separator.size()));
    if constexpr(std::is_same_v<Separator,Row>)index.projection.target().descriptor().validate(separator);
    frames[0].prebound_key=runtime->state->storage.projection(index.id).target().tuple(separator);
  }
  void bind(std::shared_ptr<EpochView::Data> context,const FixedAssignment& bindings) {
    bind_values(std::move(context),bindings);
  }
  static storage::ScalarView binding_value(const Value& value){return storage::borrow_scalar(value);}
  static storage::ScalarView binding_value(const storage::ScalarView& value){return value;}
  template<class Bindings>
  void bind_values(std::shared_ptr<EpochView::Data> context,const Bindings& bindings) {
    snapshot=std::move(context); snapshot->readable();
    epoch=snapshot->side==SnapshotSide::before?snapshot->group->before_sequence:snapshot->group->after_sequence;
    answer=snapshot->side==SnapshotSide::before?snapshot->group->before_answer:snapshot->group->after_answer;
    for (const auto& binding : bindings) {
      metric(metrics.startup,&CursorWork::binding_values);
      require(binding.variable.value<plan.query().variables.size(),"invalid_binding","fixed variable is outside the query");
      const auto scalar=binding_value(binding.value);
      require(scalar.index()==static_cast<std::size_t>(plan.query().variables[binding.variable.value].type),"invalid_binding","fixed value has the wrong exact scalar type");
      if(const auto found=fixed.find(binding.variable);found!=fixed.end()) {
        require(found->second.view()[0]==scalar,"invalid_binding","fixed assignment contains conflicting values");
      } else {
        const std::array cell{scalar};
        fixed.emplace(binding.variable,storage::AccountedRow::copy_of(runtime->storage_context->memory(),storage::RowView::borrow(cell)));
      }
    }
  }
  SupportEnumerationProgram survivors(const WitnessFragment& fragment) {
    require(!(fragment.root && fragment.nodes),"invalid_fragment","fragment root and factor set are mutually exclusive");
    if (fragment.root) require(fragment.root->value<runtime->program_nodes().size(),"invalid_fragment","fragment root is outside the physical plan");
    MemorySet<NodeId> selected(std::less<NodeId>{},MemorySet<NodeId>::allocator_type(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));
    if (fragment.nodes) for (const auto id : *fragment.nodes) {
      metric(metrics.startup,&CursorWork::fragment_steps);
      require(id.value<runtime->program_nodes().size() && selected.insert(id).second,"invalid_fragment","fragment factor is unknown or repeated");
    }
    SupportEnumerationProgram result(runtime->storage_context->memory()); MemoryVector<NodeId> pending(resource::MemoryAllocator<NodeId>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));
    if (plan.route()==PhysicalRoute::tree) pending.push_back(fragment.root.value_or(*plan.tree().root));
    auto positions=memory_map<MemoryMap<NodeId,std::size_t>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
    auto first_field=memory_map<MemoryMap<VariableId,AssignmentSlot>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
    while (!pending.empty()) {
      const auto id=pending.back(); pending.pop_back(); const auto& node=runtime->program_nodes()[id.value];
      for (auto it=node.children.rbegin();it!=node.children.rend();++it) pending.push_back(*it);
      metric(metrics.startup,&CursorWork::fragment_steps);
      if (fragment.nodes && !selected.contains(id)) continue;
      const auto position=result.steps.size(); SupportEnumerationStep step{id,node.survivors,1,{}, {},{}};
      if (node.parent && positions.contains(*node.parent)) {
        step.parent_step=positions.at(*node.parent); step.depth=result.steps[*step.parent_step].depth+1;
      }
      positions.emplace(id,position); result.depth=std::max(result.depth,step.depth); result.steps.push_back(std::move(step));
      const auto& fields=plan.relations()[node.survivors.value].layout.fields();
      for (std::size_t field=0;field<fields.size();++field) {
        const auto [first,inserted]=first_field.emplace(*fields[field].variable,AssignmentSlot{position,FieldId{field}});
        if (!inserted) result.equalities.push_back({first->second,{position,FieldId{field}}});
      }
    }
    for (const auto& [variable,slot] : first_field) { static_cast<void>(variable); result.output.push_back(slot); }
    return result;
  }
  void initialize(program::EnumerationProgram walk,Frames& target) {
    const auto outer=memory_map<MemoryMap<VariableId,AssignmentSlot>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
    initialize(walk,target,outer);
  }
  void initialize(program::EnumerationProgram walk,Frames& target,const MemoryMap<VariableId,AssignmentSlot>& outer) {
    metric(metrics.startup,&CursorWork::frame_initializations,static_cast<std::uint64_t>(walk.steps.size())); resize_frames(target,walk.steps.size());
    auto first=memory_map<MemoryMap<VariableId,AssignmentSlot>>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch);
    for (std::size_t i=0;i<target.size();++i) {
      auto& frame=target[i]; const auto& layout=plan.relations()[walk.steps[i].relation.value].layout;
      MemoryVector<Source> lookup(resource::MemoryAllocator<Source>(runtime->storage_context->memory(),resource::MemoryPurpose::cursor)); bool complete=true;
      for (std::size_t field=0;field<layout.fields().size();++field) {
        const auto variable=*layout.fields()[field].variable; std::optional<Source> source;
        if (fixed.contains(variable)) {
          source=Source{Source::Kind::fixed,variable,{0,FieldId{0}}}; frame.conditions.push_back({FieldId{field},*source});
        }
        if (const auto found=outer.find(variable);found!=outer.end()) {
          const Source test{Source::Kind::outer,variable,found->second}; frame.conditions.push_back({FieldId{field},test}); if (!source) source=test;
        }
        if (const auto found=first.find(variable);found!=first.end()) {
          const Source test{Source::Kind::local,variable,found->second}; frame.conditions.push_back({FieldId{field},test}); if (!source) source=test;
        }
        if (source) lookup.push_back(*source); else complete=false;
        first.emplace(variable,AssignmentSlot{i,FieldId{field}});
      }
      if (complete) frame.lookup=std::move(lookup);
      if (snapshot->side==SnapshotSide::before) frame.patch=&snapshot->group->patches[walk.steps[i].relation.value];
    }
  }
  void link() noexcept {
    auto& first=snapshot->group->first; next=first;
    if (first) first->previous=this;
    first=this;
  }
  ~Data() {
    close(ResultCursorState::cancelled,CursorTerminalReason::destruction);
    if(startup_sink)*startup_sink=metrics;
  }
  void metric(CursorWork& work,std::uint64_t CursorWork::* field,std::uint64_t amount=1) {
    const auto used=metrics.total_work;
    require(amount<=std::numeric_limits<std::uint64_t>::max()-used,"resource_limit","result cursor work counter exhausted");
    require(!options.work_limit || (used<=*options.work_limit && amount<=*options.work_limit-used),"resource_limit","result cursor work limit exceeded; cursor closed");
    metrics.total_work+=amount; work.work+=amount; work.*field+=amount;
    if(startup_sink)*startup_sink=metrics;
  }
  static void merge(CursorWork& target,const CursorWork& value) noexcept {
    constexpr std::array fields{&CursorWork::work,&CursorWork::calls,&CursorWork::route_checks,&CursorWork::descriptor_steps,&CursorWork::frame_initializations,
      &CursorWork::cursor_opens,&CursorWork::cursor_advances,&CursorWork::frame_closes,
      &CursorWork::tuple_lookups,&CursorWork::selected_rows,&CursorWork::bucket_lookups,&CursorWork::key_fields,
      &CursorWork::equality_checks,&CursorWork::output_fields,&CursorWork::rows_emitted,
      &CursorWork::binding_checks,&CursorWork::binding_rejections,&CursorWork::direct_lookups,&CursorWork::overlay_rows,
      &CursorWork::fragment_steps,&CursorWork::binding_values,&CursorWork::witness_probes,&CursorWork::witness_rows,&CursorWork::join_rejections};
    // Every component is bounded by the already checked aggregate work.
    for (const auto field : fields) target.*field+=value.*field;
  }
  void close(ResultCursorState state,CursorTerminalReason reason) noexcept {
    if (status!=ResultCursorState::active) return;
    const auto start=observation_admitted?cursor_now(diagnostic,observation):0;
    if(observation_admitted){diagnostic.terminal_reason=reason;cursor_add(diagnostic,CursorMetricId::cleanup_calls);}
    if (snapshot) {
      auto& first=snapshot->group->first;
      if (previous) previous->next=next; else if (first==this) first=next;
      if (next) next->previous=previous;
      previous=nullptr; next=nullptr;
    }
    for (const auto& frame : frames) if (frame.opened) ++metrics.cleanup_frames;
    for (const auto& frame : probe_frames) if (frame.opened) ++metrics.cleanup_frames;
    frames.clear(); probe_frames.clear(); fixed.clear(); fragment_program.reset(); probe_program.clear(); probe_children.clear();
    if (leased) {
      if (!runtime || runtime->readers==0) std::terminate();
      --runtime->readers; leased=false;
    }
    snapshot.reset(); runtime.reset(); status=state;
    if(observation_admitted){cursor_elapsed(diagnostic,CursorMetricId::cleanup_ns,start,observation);publish();}
  }
  const storage::ScalarView& value(AssignmentSlot slot) const { return frames.at(slot.step).selected->values().at(slot.field.value); }
  template<bool Native> using EmittedTuple=std::conditional_t<Native,storage::AccountedTuple,storage::Tuple>;
  template<bool Native> EmittedTuple<Native> emit(CursorWork& work) {
    const auto& program=this->program();
    if (!scalar) for (const auto& equality : program.equalities) {
      metric(work,&CursorWork::equality_checks);
      require(value(equality.left)==value(equality.right),"runtime_contract","enumeration separator traversal produced inconsistent assignments");
    }
    // Gather the output cells in a stack buffer for ordinary arities; only
    // unusually wide rows use a funded scratch vector. Either way the cells are
    // copied into the emitted tuple's own funded block below.
    constexpr std::size_t inline_cells=16;
    const auto arity=output_layout.fields().size();
    std::array<storage::ScalarView,inline_cells> inline_row;
    std::optional<MemoryVector<storage::ScalarView>> wide_row;
    if (arity>inline_cells) {
      wide_row.emplace(resource::MemoryAllocator<storage::ScalarView>(
          runtime->storage_context->memory(),resource::MemoryPurpose::scratch,{resource::MemoryOwnerKind::cursor,0}));
      wide_row->reserve(arity);
    }
    std::size_t used=0;
    const auto append=[&](const storage::ScalarView& value) {
      if (wide_row) wide_row->push_back(value);
      else {
        require(used<inline_cells,"runtime_contract","result row exceeds its output layout");
        inline_row[used++]=value;
      }
    };
    if (scalar) { metric(work,&CursorWork::output_fields); append(storage::ScalarView{answer}); }
    else if (view==ResultView::sql && plan.normalized()) {
      for (const auto& output : plan.normalized()->outputs) {
        metric(work,&CursorWork::output_fields);
        if (const auto* column=std::get_if<frontend::CoreOutput>(&output.value)) append(value(program.output.at(column->column)));
        else append(std::get<program::ConstantOutput>(output.value).value);
      }
    } else for (const auto slot : program.output) { metric(work,&CursorWork::output_fields); append(value(slot)); }
    auto result=[&] {
      const auto cells=wide_row?std::span<const storage::ScalarView>(*wide_row):std::span<const storage::ScalarView>(inline_row.data(),used);
      auto native=native_output_layout.tuple(storage::RowView::borrow(cells),
          {Native?resource::MemoryOwnerKind::cursor:resource::MemoryOwnerKind::output,0});
      if constexpr(Native)return native;
      else return storage::Tuple::from_accounted(std::move(native));
    }();
    metric(work,&CursorWork::rows_emitted); return result;
  }
  const storage::AccountedStorageTable::Journal* writer(RelationId relation) const {
    if (!snapshot || snapshot->group->phase!=EpochView::Group::Phase::tentative || !snapshot->group->journal) return nullptr;
    for (const auto& [id,journal] : snapshot->group->journal->storage_) if (id==relation) return &journal;
    return nullptr;
  }
  storage::ScalarView bound(const Source& source,const Frames& selected) const {
    if (source.kind==Source::Kind::fixed) return fixed.at(source.variable).view()[0];
    const auto& rows=source.kind==Source::Kind::outer?frames:selected;
    require(rows[source.slot.step].selected!=nullptr,"runtime_contract","fragment binding refers to an unselected factor");
    return rows[source.slot.step].selected->values()[source.slot.field.value];
  }
  bool compatible(const storage::AccountedTuple& tuple,const Frame& frame,const SupportEnumerationStep& step,CursorWork& work,const Frames& selected) {
    if (frame.key && (frame.direct || frame.ghosts)) {
      const auto& fields=plan.indexes()[step.bucket_index->value].projection.fields();
      for (std::size_t i=0;i<fields.size();++i) {
        metric(work,&CursorWork::key_fields);
        if (tuple.values()[fields[i].value]!=frame.key->values()[i]) return false;
      }
    }
    for (const auto& condition : frame.conditions) {
      const bool join=condition.source.kind==Source::Kind::local;
      metric(work,join?&CursorWork::equality_checks:&CursorWork::binding_checks);
      if (tuple.values()[condition.field.value]!=bound(condition.source,selected)) {
        metric(work,join?&CursorWork::join_rejections:&CursorWork::binding_rejections); return false;
      }
    }
    return true;
  }
  const storage::AccountedTuple* select(Frame& frame,const SupportEnumerationStep& step,CursorWork& work,const Frames& selected) {
    const auto& table=runtime->state->storage.table(step.relation);
    if (!frame.opened) {
      frame.opened=true; frame.direct_used=false; frame.ghosts=false;
      frame.ghost_rows=nullptr;
      if (frame.lookup) {
        MemoryVector<storage::ScalarView> values(resource::MemoryAllocator<storage::ScalarView>(runtime->storage_context->memory(),resource::MemoryPurpose::scratch));values.reserve(frame.lookup->size());
        for (const auto& source : *frame.lookup) { metric(work,&CursorWork::key_fields); values.push_back(bound(source,selected)); }
        frame.direct=table.layout().tuple(storage::RowView::borrow(values));
      }
      if (frame.prebound_key) frame.key=frame.prebound_key->clone();
      else if (step.parent_key) {
        metric(work,&CursorWork::key_fields,static_cast<std::uint64_t>(step.parent_key->fields().size()));
        frame.key=step.parent_key->apply(*selected[*step.parent_step].selected);
      }
      if (!frame.direct) {
        if (frame.patch) {
          if (step.bucket_index) {
            require(bool(frame.key),"runtime_contract","bucketed visible factor has no bound separator key");
            metric(work,&CursorWork::bucket_lookups);
            const auto by_index=frame.patch->restored_by_index.find(step.bucket_index->value);
            if (by_index!=frame.patch->restored_by_index.end()) {
              const auto found=by_index->second.find(frame.key->values());
              if (found!=by_index->second.end()) frame.ghost_rows=&found->second;
            }
          } else frame.ghost_rows=&frame.patch->restored;
          if (frame.ghost_rows) frame.ghost=frame.ghost_rows->begin();
        }
        metric(work,&CursorWork::cursor_opens); const auto* journal=writer(step.relation);
        if (!step.bucket_index) frame.cursor.emplace(journal?journal->live():table.live(runtime->work()));
        else {
          metric(work,&CursorWork::bucket_lookups);
          const auto id=runtime->state->storage.index(*step.bucket_index);
          frame.cursor.emplace(journal?journal->bucket_cursor(id,*frame.key):table.bucket_cursor(id,*frame.key, runtime->work()));
        }
      }
    }
    if (frame.direct) {
      if (frame.direct_used) return nullptr;
      frame.direct_used=true; metric(work,&CursorWork::direct_lookups);
      const auto found=table.find(*frame.direct, runtime->work());
      if (found && (!frame.patch || !frame.patch->excluded.contains(found->tuple))) {
        metric(work,&CursorWork::tuple_lookups); const auto* tuple=table.get(*found, runtime->work());
        if (tuple && compatible(*tuple,frame,step,work,selected)) return tuple;
      }
      if (frame.patch) {
        metric(work,&CursorWork::direct_lookups);
        const auto restored=frame.patch->restored_by_key.find(frame.direct->values());
        if (restored!=frame.patch->restored_by_key.end()) {
          metric(work,&CursorWork::overlay_rows);
          if (compatible(*restored->second,frame,step,work,selected)) return restored->second;
        }
      }
      return nullptr;
    }
    while (!frame.ghosts) {
      metric(work,&CursorWork::cursor_advances); const auto entry=frame.cursor->next_entry(runtime->work());
      if (!entry) { frame.ghosts=true; break; }
      if (frame.patch) {
        metric(work,&CursorWork::overlay_rows);
        if (frame.patch->excluded.contains(entry->handle.tuple)) continue;
      }
      metric(work,&CursorWork::tuple_lookups); const auto* tuple=&entry->tuple;
      if (compatible(*tuple,frame,step,work,selected)) return tuple;
    }
    if (frame.ghost_rows) while (frame.ghost!=frame.ghost_rows->end()) {
      const auto* tuple=(frame.ghost++)->second; metric(work,&CursorWork::overlay_rows);
      if (compatible(*tuple,frame,step,work,selected)) return tuple;
    }
    return nullptr;
  }
  void close_frame(Frame& frame,CursorWork& work) {
    metric(work,&CursorWork::frame_closes); frame.cursor.reset();
    if (!frame.prebound_key) frame.key.reset();
    frame.ghost_rows=nullptr; frame.direct.reset();
    frame.selected=nullptr; frame.opened=false;
  }
  bool has_witness(CursorWork& work) {
    // This program is one complete survivor subtree. Running intersection
    // makes child witnesses independent once the parent row is fixed. A
    // failed child rejects that row; revisiting successful sibling choices
    // would enumerate a hidden Cartesian product unnecessarily.
    metric(work,&CursorWork::witness_probes);
    std::size_t current=0; bool choose=true;
    for (;;) {
      auto& frame=probe_frames[current]; const auto& step=probe_program.steps[current];
      if (choose) {
        frame.selected=select(frame,step,work,probe_frames);
        if (!frame.selected) {
          close_frame(frame,work);
          if (!step.parent_step) return false;
          current=*step.parent_step; choose=true; continue;
        }
        metric(work,&CursorWork::witness_rows); frame.child=0;
      }
      if (frame.child<probe_children[current].size()) {
        current=probe_children[current][frame.child++]; choose=true;
      } else {
        close_frame(frame,work);
        if (!step.parent_step) return true;
        current=*step.parent_step; choose=false;
      }
    }
  }
  template<bool Native> std::optional<EmittedTuple<Native>> advance(CursorWork& work) {
    metric(work,&CursorWork::calls);
    if (scalar || plan.route()!=PhysicalRoute::tree || (witness_mode && frames.empty())) {
      if (resume || (!scalar && !answer)) return {};
      resume=true; return emit<Native>(work);
    }
    if (!answer) return {};
    require(!frames.empty(),"runtime_contract","tree enumeration has no root frame");
    if (resume) { position=frames.size()-1; resume=false; }
    const auto& program=this->program();
    for (;;) {
      if (position==frames.size()) {
        if (!probe_frames.empty() && !has_witness(work)) { position=frames.size()-1; continue; }
        resume=true; return emit<Native>(work);
      }
      auto& frame=frames[position]; const auto& step=program.steps[position];
      frame.selected=select(frame,step,work,frames);
      if (frame.selected) {
        metric(work,&CursorWork::selected_rows); ++position;
      } else {
        close_frame(frame,work);
        if (position==0) return {};
        --position;
      }
    }
  }
  template<bool Native> std::optional<EmittedTuple<Native>> produce() {
    require(status!=ResultCursorState::failed,"invalid_cursor","result cursor failed and is closed");
    if (status!=ResultCursorState::active) return {};
    CursorWork action;
    const auto start=observation_admitted?cursor_now(diagnostic,observation):0;
    try {
      detail::StorageOperation storage_operation(runtime->storage_context,storage_lease);
      auto result=advance<Native>(action); metrics.last=action;
      if (result) {
        merge(metrics.results,action); metrics.max_result_work=std::max(metrics.max_result_work,action.work);
        if(observation_admitted){cursor_add(diagnostic,CursorMetricId::successful_calls);cursor_elapsed(diagnostic,CursorMetricId::successful_next_ns,start,observation);publish();}
      } else {
        merge(metrics.termination,action);
        if(observation_admitted){cursor_add(diagnostic,CursorMetricId::exhausted_calls);cursor_elapsed(diagnostic,CursorMetricId::exhausted_next_ns,start,observation);}
        close(ResultCursorState::exhausted,CursorTerminalReason::exhausted);
      }
      return result;
    } catch (...) {
      metrics.last=action; merge(metrics.failed,action);
      if(observation_admitted){cursor_add(diagnostic,CursorMetricId::failed_calls);cursor_elapsed(diagnostic,CursorMetricId::failed_next_ns,start,observation);}
      close(ResultCursorState::failed,CursorTerminalReason::next_failure); throw;
    }
  }
};
void SupportRuntime::EpochView::Group::abort() noexcept {
  phase=Phase::aborted;
  while (first) first->close(ResultCursorState::failed,CursorTerminalReason::invalidated);
  release(); patches.clear(); journal.reset(); runtime.reset();
}
SupportRuntime::ResultCursor::ResultCursor(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
SupportRuntime::ResultCursor::ResultCursor(ResultCursor&&) noexcept=default;
SupportRuntime::ResultCursor::ResultCursor(std::unique_ptr<detail::ExternalResultCursor> external) noexcept
    :external_(std::move(external)) {}
SupportRuntime::ResultCursor& SupportRuntime::ResultCursor::operator=(ResultCursor&& other) noexcept {
  if (this!=&other) {
    if(data_)data_->close(ResultCursorState::cancelled,CursorTerminalReason::move_replacement);
    if(external_)external_->cancel();
    data_=std::move(other.data_);
    external_=std::move(other.external_);
  }
  return *this;
}
SupportRuntime::ResultCursor::~ResultCursor()=default;
bool SupportRuntime::ResultCursor::active() const noexcept {
  if (external_) return external_->state()==ResultCursorState::active;
  return data_ && data_->status==ResultCursorState::active;
}
ResultCursorState SupportRuntime::ResultCursor::state() const {
  if (external_) return external_->state();
  require(bool(data_),"invalid_cursor","moved-from result cursor"); return data_->status;
}
std::uint64_t SupportRuntime::ResultCursor::sequence() const {
  if (external_) return external_->sequence();
  require(bool(data_),"invalid_cursor","moved-from result cursor"); return data_->epoch;
}
SupportOwnerId SupportRuntime::ResultCursor::owner() const {
  if (external_) return external_->owner();
  require(bool(data_),"invalid_cursor","moved-from result cursor"); return data_->identity;
}
const storage::TupleLayout& SupportRuntime::ResultCursor::layout() const {
  if (external_) return external_->layout();
  require(bool(data_),"invalid_cursor","moved-from result cursor"); return data_->output_layout;
}
const ResultCursorMetrics& SupportRuntime::ResultCursor::metrics() const {
  if (external_) return external_->metrics();
  require(bool(data_),"invalid_cursor","moved-from result cursor"); return data_->metrics;
}
CursorObservation SupportRuntime::ResultCursor::observation() const {
  if (external_) { CursorObservation result; result.mandatory=external_->metrics(); result.state=external_->state(); result.sequence=external_->sequence(); return result; }
  require(bool(data_),"invalid_cursor","moved-from result cursor");
  auto result=data_->diagnostic;result.mandatory=data_->metrics;result.state=data_->status;return result;
}
void SupportRuntime::ResultCursor::cancel() noexcept {
  if(external_){external_->cancel();return;}
  if(data_ && data_->status==ResultCursorState::active){
    if(data_->observation_admitted)cursor_add(data_->diagnostic,CursorMetricId::cancel_calls);
    data_->close(ResultCursorState::cancelled,CursorTerminalReason::explicit_cancel);
  }
}
std::optional<storage::Tuple> SupportRuntime::ResultCursor::next() try {
  if (external_) return external_->next_tuple();
  require(bool(data_),"invalid_cursor","moved-from result cursor");
  return data_->produce<false>();
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
std::optional<storage::AccountedTuple> SupportRuntime::ResultCursor::next_native() try {
  if (external_) return external_->next();
  require(bool(data_),"invalid_cursor","moved-from result cursor");
  return data_->produce<true>();
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::results(ResultCursorOptions options,ResultView view) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable();
  require(view==ResultView::core || view==ResultView::sql,"invalid_cursor_options","unknown result view");
  require(d.readers!=std::numeric_limits<std::size_t>::max(),"resource_limit","result cursor reader count exhausted");
  auto data=ResultCursor::Data::create(impl_,options,view,CursorObservationSource::committed_results,{},false,d.sequence,
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(d.storage_context->memory(),resource::MemoryPurpose::cursor,impl_,options,view,true,startup);});
  return ResultCursor(std::move(data));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::EpochView::EpochView(std::shared_ptr<Data> data) noexcept:data_(std::move(data)) {}
bool SupportRuntime::EpochView::valid() const noexcept { return data_ && data_->group->phase!=Group::Phase::aborted; }
bool SupportRuntime::EpochView::tentative() const noexcept { return valid() && data_->group->phase==Group::Phase::tentative; }
SnapshotSide SupportRuntime::EpochView::side() const { require(bool(data_),"invalid_snapshot","closed epoch view"); return data_->side; }
std::uint64_t SupportRuntime::EpochView::sequence() const {
  require(bool(data_),"invalid_snapshot","closed epoch view");
  return data_->side==SnapshotSide::before?data_->group->before_sequence:data_->group->after_sequence;
}
SupportOwnerId SupportRuntime::EpochView::owner() const {
  require(bool(data_),"invalid_snapshot","closed epoch view"); return data_->group->identity;
}
const EpochViewMetrics& SupportRuntime::EpochView::metrics() const { require(bool(data_),"invalid_snapshot","closed epoch view"); return data_->group->metrics; }
bool SupportRuntime::EpochView::has_answer() const {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  return data_->side==SnapshotSide::before?data_->group->before_answer:data_->group->after_answer;
}
void SupportRuntime::EpochView::close() noexcept { data_.reset(); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::results(ResultCursorOptions options) const { return completions({}, {},options); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_visible,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,fixed,fragment,options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::completions_native(std::span<const VariableBindingView> fixed,VisibleFragment fragment,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_visible,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,fixed,fragment,options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_witnesses,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,fixed,std::move(fragment),options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_keys(NodeId node,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_keys,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,node,options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket(NodeId node,const Row& separator,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_bucket,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,node,separator,options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket_native(NodeId node,storage::RowView separator,ResultCursorOptions options) const try {
  require(bool(data_),"invalid_snapshot","closed epoch view"); data_->readable();
  detail::StorageOperation storage_operation(data_->group->runtime->storage_context,data_->group->storage_lease);
  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::epoch_bucket,data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return resource::make_accounted_unique<ResultCursor::Data>(data_->group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,data_,node,separator,options,startup);});
  return ResultCursor(std::move(cursor));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); } catch(const storage::TupleValidationFailure& failure) { support_present(failure); }
SupportRuntime::EpochView SupportRuntime::current_view(EpochViewOptions options) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); const auto answer=d.answer(*d.state);
  auto group=resource::make_accounted_shared<EpochView::Group>(d.storage_context->memory(),resource::MemoryPurpose::cursor,impl_,nullptr,d.sequence,d.sequence,answer,answer,EpochView::Group::Phase::committed,options);
  auto data=resource::make_accounted_shared<EpochView::Data>(group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,group,SnapshotSide::after); group->acquire(); return EpochView(std::move(data));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::ResultCursor SupportRuntime::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultCursorOptions options) const {
  return current_view().completions(fixed,fragment,options);
}
SupportRuntime::ResultCursor SupportRuntime::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCursorOptions options) const {
  return current_view().witnesses(fixed,std::move(fragment),options);
}

struct SupportRuntime::PendingEpoch::Data {
  std::shared_ptr<Impl> owner;
  detail::StorageWorkLease storage_lease;
  SetOperation operation;
  SupportEpoch output;
  std::shared_ptr<SupportJournal> journal;
  resource::AccountedUnique<Impl::Transaction> transaction;
  std::shared_ptr<EpochView::Group> views;
  bool before_answer;
  std::uint64_t prefix=0;
  Data(std::shared_ptr<Impl> value,std::uint64_t sequence,SetOperation sign)
      :owner(std::move(value)),storage_lease(detail::storage_lease(owner->storage_context)),operation(sign),output{sequence,false,owner->answer(*owner->state),{},transition_buffer(owner->storage_context->memory()),{}},
       journal(resource::make_accounted_shared<SupportJournal>(owner->storage_context->memory(),resource::MemoryPurpose::journal_undo,owner->storage_context->memory())),before_answer(output.has_answer) {
    journal->sequence=sequence;
    transaction=resource::make_accounted_unique<Impl::Transaction>(owner->storage_context->memory(),resource::MemoryPurpose::journal_undo,*owner,*owner->state,output,journal);
    if (owner->observation) observation_ticket=owner->observation->begin(ObservationLayer::support,sequence);
    workload_ticket=owner->workload.logical(sign);
  }
  detail::ObservationTicket observation_ticket;
  workload::detail::Ticket workload_ticket;
  ~Data() { rollback(); }
  Impl& active() const {
    require(bool(owner) && bool(transaction),"invalid_epoch","prepared epoch is closed"); return *owner;
  }
  void rollback() noexcept {
    if (!owner) return;
    owner->observe(output.metrics);
    if (views) { views->abort(); views.reset(); }
    transaction.reset();
    output.journal.reset(); output.transitions.clear(); journal.reset();
    if (owner->observation) owner->observation->finish(observation_ticket,ObservationOutcome::aborted);
    owner->workload.finish(workload_ticket,false);
    owner->updating=false; owner.reset();
  }
  bool stage_tuple(const SupportNodeProgram& node,const storage::AccountedTuple& tuple) {
    detail::StorageOperation storage_operation(active().storage_context,storage_lease);
    auto& d=active(); const bool add=operation==SetOperation::insert;
    const bool present=d.state->storage.table(node.records).find(tuple, d.work()).has_value();
    if (present==add) return false;
    require(prefix!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","logical stage prefix exhausted");
    transaction->start(); transaction->native(node,tuple,add); transaction->drain();
    output.native_changed=true; output.has_answer=d.answer(*d.state); output.journal=journal;
    ++prefix; owner->observe(output.metrics);
    return true;
  }
};
SupportRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
SupportRuntime::PendingEpoch::PendingEpoch(PendingEpoch&&) noexcept=default;
SupportRuntime::PendingEpoch& SupportRuntime::PendingEpoch::operator=(PendingEpoch&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
SupportRuntime::PendingEpoch::~PendingEpoch()=default;
bool SupportRuntime::PendingEpoch::active() const noexcept { return data_ && data_->owner && data_->transaction; }
void SupportRuntime::PendingEpoch::rollback() noexcept { if (data_) data_->rollback(); }
bool SupportRuntime::PendingEpoch::stage(NodeId id,const Row& values) try {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch");
  if (data_->views) {
    require(data_->views.use_count()==1,"runtime_busy","epoch prefix is pinned by fragment views");
    data_->views.reset();
  }
  try {
    auto& d=data_->active(); const auto& node=d.node(id);
    require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes do not accept external tuple updates");
    d.plan.nodes()[node.id.value].layout.descriptor().validate(values);
    const auto tuple=node.layout.tuple(values); return data_->stage_tuple(node,tuple);
  } catch (...) { data_->rollback(); throw; }
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
const SupportEpoch& SupportRuntime::PendingEpoch::preview() const {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch"); static_cast<void>(data_->active()); return data_->output;
}
bool SupportRuntime::PendingEpoch::stage_native(NodeId id,const storage::AccountedTuple& tuple) try {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch");
  if(data_->views) {
    require(data_->views.use_count()==1,"runtime_busy","epoch prefix is pinned by fragment views");
    data_->views.reset();
  }
  try {
    auto& d=data_->active();const auto& node=d.node(id);
    require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes do not accept external tuple updates");
    if(!node.layout.same_token(tuple.layout()))throw storage::IndexFailure(storage::IndexFault::layout_mismatch);
    return data_->stage_tuple(node,tuple);
  } catch(...) {data_->rollback();throw;}
} catch(const storage::IndexFailure& failure) {support_present(failure);}
  catch(const storage::TableValidationFailure& failure) {support_present(failure);}
SupportSnapshot SupportRuntime::PendingEpoch::snapshot() const try {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch");
  detail::StorageOperation storage_operation(data_->active().storage_context,data_->storage_lease);
  return data_->active().snapshot(data_->output.sequence);
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::EpochView SupportRuntime::PendingEpoch::view(SnapshotSide side,EpochViewOptions options) try {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch");
  detail::StorageOperation storage_operation(data_->active().storage_context,data_->storage_lease); auto& d=data_->active();
  require(side==SnapshotSide::before || side==SnapshotSide::after,"invalid_snapshot","unknown snapshot side");
  if (data_->views && (data_->views->record_begin!=0 || data_->views->before_prefix!=0)) {
    require(data_->views.use_count()==1,"runtime_busy","a different epoch prefix view is pinned"); data_->views.reset();
  }
  auto group=data_->views;
  if (!group) group=resource::make_accounted_shared<EpochView::Group>(d.storage_context->memory(),resource::MemoryPurpose::cursor,data_->owner,data_->journal,d.sequence,data_->output.sequence,
      data_->before_answer,data_->output.has_answer,EpochView::Group::Phase::tentative,options,0,0,data_->prefix);
  auto view=resource::make_accounted_shared<EpochView::Data>(group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,group,side);
  if (!data_->views) { group->acquire(); data_->views=group; }
  return EpochView(std::move(view));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::PendingEpoch::Checkpoint SupportRuntime::PendingEpoch::checkpoint() const {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch"); const auto& d=data_->active();
  return {d.owner,data_->output.sequence,data_->prefix,data_->journal->records.size(),data_->output.has_answer};
}
std::span<const JournalRecord> SupportRuntime::PendingEpoch::stage_records(const Checkpoint& before) const {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch"); const auto& d=data_->active();
  require(before.owner==d.owner && before.sequence==data_->output.sequence && before.prefix<data_->prefix &&
      data_->prefix-before.prefix==1 && before.records<=data_->journal->records.size(),
      "invalid_snapshot","checkpoint does not precede the current logical stage");
  return std::span<const JournalRecord>{data_->journal->records}.subspan(before.records);
}
SupportRuntime::EpochView SupportRuntime::PendingEpoch::stage_view(const Checkpoint& before,SnapshotSide side,EpochViewOptions options) try {
  static_cast<void>(stage_records(before));
  detail::StorageOperation storage_operation(data_->active().storage_context,data_->storage_lease); auto& d=data_->active();
  require(side==SnapshotSide::before || side==SnapshotSide::after,"invalid_snapshot","unknown snapshot side");
  if (data_->views && (data_->views->record_begin!=before.records || data_->views->before_prefix!=before.prefix)) {
    require(data_->views.use_count()==1,"runtime_busy","a different epoch prefix view is pinned"); data_->views.reset();
  }
  auto group=data_->views;
  if (!group) group=resource::make_accounted_shared<EpochView::Group>(d.storage_context->memory(),resource::MemoryPurpose::cursor,data_->owner,data_->journal,
      before.prefix==0?d.sequence:data_->output.sequence,data_->output.sequence,before.has_answer,data_->output.has_answer,
      EpochView::Group::Phase::tentative,options,before.records,before.prefix,data_->prefix);
  auto view=resource::make_accounted_shared<EpochView::Data>(group->runtime->storage_context->memory(),resource::MemoryPurpose::cursor,group,side);
  if (!data_->views) { group->acquire(); data_->views=group; }
  return EpochView(std::move(view));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportEpoch SupportRuntime::PendingEpoch::commit() {
  require(bool(data_),"invalid_epoch","moved-from prepared epoch"); auto& d=data_->active();
  // Validation above is the only throwing path. All output already exists;
  // from here publication, return-value movement and teardown allocate nothing.
  d.observe(data_->output.metrics);
  data_->transaction->commit();
  SupportEpoch result=std::move(data_->output);
  data_->transaction.reset(); data_->journal.reset();
  if (data_->views) { data_->views->phase=EpochView::Group::Phase::committed; data_->views.reset(); }
  d.sequence=result.sequence; d.updating=false;
  d.workload.logical_fact(data_->workload_ticket,result.native_changed);
  d.workload.finish(data_->workload_ticket,true);
  if (d.observation) d.observation->finish(data_->observation_ticket,ObservationOutcome::committed);
  data_->owner.reset();
  return result;
}
SupportRuntime::PendingEpoch SupportRuntime::begin_epoch(std::uint64_t sequence,SetOperation operation) try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.writable();
  require(d.sequence!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","logical update sequence exhausted");
  require(sequence==d.sequence+1,"invalid_sequence","logical epoch sequence must be contiguous from one");
  require(operation==SetOperation::insert || operation==SetOperation::erase,"invalid_native_update","unknown native set operation");
  auto data=resource::make_accounted_unique<PendingEpoch::Data>(d.storage_context->memory(),resource::MemoryPurpose::journal_undo,impl_,sequence,operation);
  d.updating=true; return PendingEpoch(std::move(data));
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }

void SupportRuntime::initialize_native(std::span<const detail::NativeSeed> seeds,BuildOptions options,BuildMetrics& metrics) {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.writable();
  // Initialization is not a sequence-zero stream of ordinary observed updates.
  // Save by move; restoring observation on all exits allocates nothing.
  struct RestoreObservation {
    std::shared_ptr<detail::ObservationState>& target;
    std::shared_ptr<detail::ObservationState> saved;
    ~RestoreObservation() { target=std::move(saved); }
  } restore_observation{d.observation,std::move(d.observation)};
  // Direct-build failure can leave private partial state: discard this
  // unpublished owner; this bulk builder is not a retryable update transaction.
  require(d.sequence==0,"runtime_contract","initialization requires an unpublished empty support owner");
  for (const auto& definition : d.plan.relations())
    require(d.state->storage.table(definition.id).size()==0,"runtime_contract","initialization requires empty storage");
  require(options.method==BuildMethod::direct || options.method==BuildMethod::insertion_replay,
      "invalid_options","unknown initialization method");
  const auto charge=[&](std::uint64_t amount=1) { detail::build_charge(metrics,options,amount); };
  const auto metric=[&](std::uint64_t& counter,std::uint64_t amount=1) { detail::build_metric(metrics,options,counter,amount); };
  if (options.method==BuildMethod::insertion_replay) {
    // This owner has not escaped. Build work has its own cumulative budget;
    // ordinary update limits and trace capture are restored on every exit.
    struct Restore { SupportOptions& target; SupportOptions saved; ~Restore() { target=saved; } } restore{d.options,d.options};
    d.options.work_limit=std::nullopt; d.options.capture_transitions=false;
    for (const auto& seed : seeds) {
      metric(metrics.replay_inputs);
      const auto& node=d.node(seed.node);
      require(node.kind==NodeKind::native,"invalid_native_update","initialization seed must name a native node");
      auto pending=resource::make_accounted_unique<PendingEpoch::Data>(d.storage_context->memory(),resource::MemoryPurpose::journal_undo,impl_,0,SetOperation::insert);
      pending->transaction->build_metrics=&metrics;
      pending->transaction->build_options=&options;
      d.updating=true;
      require(seed.tuple.layout().same_token(node.layout),"storage_contract","native initialization seed belongs to another layout");
      static_cast<void>(pending->stage_tuple(node,seed.tuple));
      metric(metrics.replay_events,pending->output.metrics.events_applied);
      metric(metrics.child_probes,pending->output.metrics.child_key_probes);
      pending->transaction->commit();
      // Destroy the per-input journal and all record pins immediately. No
      // published sequence is created, rewritten, or reset during this load.
      pending.reset();
    }
  } else {
    for (const auto& seed : seeds) {
      charge(); const auto& node=d.node(seed.node);
      require(node.kind==NodeKind::native,"invalid_native_update","initialization seed must name a native node");
      require(seed.tuple.layout().same_token(node.layout),"storage_contract","native initialization seed belongs to another layout");
      static_cast<void>(d.state->storage.table(node.records).insert(seed.tuple, d.work()));
    }
    // Derive postorder from edges, rather than assuming numeric IDs encode it.
    MemoryVector<NodeId> postorder(resource::MemoryAllocator<NodeId>(d.storage_context->memory(),resource::MemoryPurpose::scratch));
    MemoryVector<std::pair<NodeId,bool>> stack(resource::MemoryAllocator<std::pair<NodeId,bool>>(d.storage_context->memory(),resource::MemoryPurpose::scratch));
    if (d.plan.tree().root) stack.emplace_back(*d.plan.tree().root,false);
    while (!stack.empty()) {
      charge(); const auto [id,visited]=stack.back(); stack.pop_back();
      if (visited) postorder.push_back(id);
      else {
        stack.emplace_back(id,true);
        for (const auto child : d.node(id).children) stack.emplace_back(child,false);
      }
    }
    for (const auto id : postorder) {
      const auto& node=d.node(id); auto& metadata=d.state->nodes[id.value];
      auto& records=d.state->storage.table(node.records);
      if (node.kind==NodeKind::generalized) {
        for (const auto child : node.children) {
          const auto& child_table=d.state->storage.table(d.node(child).parent_support);
          auto cursor=child_table.live(d.work());
          while (const auto handle=cursor.next(d.work())) {
            charge();
            // Equal typed keys can have distinct registered layout tokens.
            static_cast<void>(records.insert(node.layout.tuple(child_table.get(*handle, d.work())->values()), d.work()));
          }
        }
      }
      const auto count=[&](RelationId relation_id,NodeState::Counts& counts,const storage::AccountedTuple& key) {
        charge(); auto& table=d.state->storage.table(relation_id);
        const auto inserted=table.insert(key, d.work());
        auto& value=counts[inserted.handle.tuple]; value=increment_support(value,d.options.support_limit);
      };
      auto cursor=records.live(d.work());
      while (const auto handle=cursor.next(d.work())) {
        charge(); const auto& tuple=*records.get(*handle, d.work());
        auto record=d.state->nodes[node.id.value].record(node.children.size());
        for (std::size_t slot=0;slot<node.children.size();++slot) {
          metric(metrics.child_probes);
          const auto& edge=d.program_edges()[d.children[id.value][slot]];
          record.present[slot]=d.state->storage.table(d.node(edge.child).parent_support).find(edge.parent_key.apply(tuple), d.work()).has_value();
          if (record.present[slot]) ++record.satisfied.value;
        }
        const bool survives=record.satisfied.value==node.children.size();
        metadata.records.emplace(handle->tuple,std::move(record));
        if (survives) {
          charge(); static_cast<void>(d.state->storage.table(node.survivors).insert(tuple, d.work()));
          count(node.parent_support,metadata.parent,node.parent_key.apply(tuple));
          if (node.visible_relation) count(*node.visible_relation,metadata.visible,node.visible_projection->apply(tuple));
        }
      }
    }
  }
  // These counters describe retained state, independently of construction
  // history (including duplicate seeds and transient replay candidates).
  for (const auto& node : d.program_nodes()) {
    metric(node.kind==NodeKind::native?metrics.native_keys:metrics.generalized_candidates,d.state->storage.table(node.records).size());
    metric(metrics.survivors,d.state->storage.table(node.survivors).size());
    metric(metrics.parent_keys,d.state->storage.table(node.parent_support).size());
    if (node.visible_relation) metric(metrics.visible_keys,d.state->storage.table(*node.visible_relation).size());
  }
  for (const auto& definition : d.plan.relations())
    metric(metrics.storage_records,d.state->storage.table(definition.id).arena_statistics().live_records);
  for (const auto& index : d.plan.indexes())
    metric(metrics.index_memberships,d.state->storage.table(index.relation).size());
}

void SupportRuntime::seed_sequence(std::uint64_t sequence) noexcept { impl_->sequence=sequence; }

SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options)
    :SupportRuntime(plan,options,detail::storage_context(plan,options.memory_limit_bytes)) {}
SupportRuntime::SupportRuntime(CompiledProgram source,SupportOptions options) try
    :impl_([&] {
      auto context=detail::new_storage_context(source,options.memory_limit_bytes);detail::StorageOperation operation(context);
      auto plan=CompiledProgram::freeze(context->memory(),source,detail::compact_storage_work(context));
      detail::validate_storage_context(plan,context,options.memory_limit_bytes);
      return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,std::move(plan),options,context);
    }()) {} catch(const storage::IndexFailure& failure) {support_present(failure);} catch(const storage::TableValidationFailure& failure) {support_present(failure);}
SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options,std::shared_ptr<detail::StorageWorkContext> context) try
    :impl_([&] { detail::validate_storage_context(plan,context,options.memory_limit_bytes);detail::StorageOperation operation(context);return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,std::move(plan),options,context); }()) {} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::SupportRuntime(CompiledProgram plan,SupportOptions options,std::shared_ptr<detail::StorageWorkContext> context) try
    :impl_([&] { detail::validate_storage_context(plan,context,options.memory_limit_bytes);detail::StorageOperation operation(context);return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,std::move(plan),options,context); }()) {} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportRuntime::~SupportRuntime()=default;
SupportRuntime::SupportRuntime(SupportRuntime&&) noexcept=default;
SupportRuntime& SupportRuntime::operator=(SupportRuntime&& other) noexcept { if (this!=&other) impl_=std::move(other.impl_); return *this; }
SupportRuntime::Impl& SupportRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from support runtime"); return *impl_; }
const CompiledProgram& SupportRuntime::plan() const { return impl().plan; }
const SupportOptions& SupportRuntime::options() const { return impl().options; }
resource::MemoryStatistics SupportRuntime::accounted_memory_statistics() const { return impl().storage_context->memory().statistics(); }
SupportOwnerId SupportRuntime::owner() const { return impl().owner; }
std::uint64_t SupportRuntime::sequence() const { return impl().sequence; }
bool SupportRuntime::ready() const { const auto& d=impl(); return !d.updating && d.readers==0; }
bool SupportRuntime::has_answer() const { auto& d=impl(); d.readable(); return d.answer(*d.state); }
const storage::TupleLayout& SupportRuntime::result_layout(ResultView view) const {
  const auto& d=impl(); require(view==ResultView::core || view==ResultView::sql,"invalid_cursor_options","unknown result view");
  return view==ResultView::sql?d.sql_output:d.core_output;
}
SupportEpoch SupportRuntime::apply(const NativeSetUpdate& update) try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.writable(); require(d.sequence!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","logical update sequence exhausted");
  require(update.sequence==d.sequence+1,"invalid_sequence","logical native update sequence must be contiguous from one");
  const auto& node=d.node(update.node);
  require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes do not accept external tuple updates");
  require(update.operation==SetOperation::insert || update.operation==SetOperation::erase,"invalid_native_update","unknown native set operation");
  d.plan.nodes()[node.id.value].layout.descriptor().validate(update.values);
  const auto tuple=node.layout.tuple(update.values); const auto& before=*d.state;
  const bool present=before.storage.table(node.records).find(tuple, d.work()).has_value();
  const bool add=update.operation==SetOperation::insert;
  SupportEpoch output{update.sequence,present!=add,d.answer(before),{},transition_buffer(d.storage_context->memory()),{}};
  if (present==add) {
    const auto ticket=d.workload.logical(update.operation);
    const auto observation=d.observation?d.observation->begin(ObservationLayer::support,update.sequence):detail::ObservationTicket{};
    d.observe(output.metrics);d.sequence=update.sequence;
    d.workload.logical_fact(ticket,false);d.workload.finish(ticket,true);
    if(d.observation)d.observation->finish(observation,ObservationOutcome::committed);
    return output;
  }
  auto pending=begin_epoch(update.sequence,update.operation);
  static_cast<void>(pending.data_->stage_tuple(node,tuple));
  return pending.commit();
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }

std::optional<SupportHandle> SupportRuntime::find(NodeId id,SupportRole role,const Row& values) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); const auto& node=d.node(id); const auto& table=d.state->storage.table(relation(node,role));
  d.plan.relations()[relation(node,role).value].layout.descriptor().validate(values);
  const auto found=table.find(table.layout().tuple(values), d.work()); return found ? std::optional<SupportHandle>{d.handle(id,role,*found)} : std::nullopt;
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
const storage::AccountedLayout& SupportRuntime::relation_layout(NodeId id,SupportRole role) const & {
  auto& d=impl(); d.readable(); return d.state->storage.table(relation(d.node(id),role)).layout();
}
std::optional<storage::Tuple> SupportRuntime::get(SupportHandle handle) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); require(handle.owner==d.owner,"foreign_support_handle","support handle belongs to another runtime");
  const auto& table=d.state->storage.table(relation(d.node(handle.node),handle.role));
  const auto* tuple=table.get({table.owner(),table.relation(),handle.tuple}, d.work());
  return tuple ? std::optional<storage::Tuple>{d.plan_tuple(*tuple)} : std::nullopt;
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
storage::ArenaStatistics SupportRuntime::storage_statistics() const {
  const auto& d=impl(); d.readable(); storage::ArenaStatistics total;
  const auto add=[](std::size_t& target,std::size_t value) {
    require(value<=std::numeric_limits<std::size_t>::max()-target,"storage_overflow","aggregate arena statistics exhausted"); target+=value;
  };
  for (const auto& definition : d.plan.relations()) {
    const auto value=d.state->storage.table(definition.id).arena_statistics();
    add(total.slots,value.slots); add(total.live_records,value.live_records); add(total.retained_records,value.retained_records);
    add(total.pins,value.pins); add(total.free_slots,value.free_slots); add(total.exhausted_slots,value.exhausted_slots);
  }
  return total;
}
std::optional<CursorObservation> SupportRuntime::last_cursor_observation() const { return impl().last_cursor; }
template<class Gauges> Gauges SupportRuntime::Impl::state_gauges(Gauges result) const {
  const auto& d=*this;d.readable();
  result.owner=d.owner.value;result.sequence=d.sequence;result.nodes.reserve(d.program_nodes().size());
  for(const auto& node:d.program_nodes()){
    NodeStateGauge value{node.id,node.kind,
      static_cast<std::uint64_t>(d.state->storage.table(node.records).size()),
      static_cast<std::uint64_t>(d.state->storage.table(node.survivors).size()),
      static_cast<std::uint64_t>(d.state->storage.table(node.parent_support).size()),{}};
    if(node.visible_relation)value.visible_factor_assignments={static_cast<std::uint64_t>(d.state->storage.table(*node.visible_relation).size()),MetricAvailability::available,false};
    result.nodes.push_back(value);
  }
  return result;
}
CommittedStateGauges SupportRuntime::committed_state_gauges() const {
  return impl().state_gauges(CommittedStateGauges{});
}
CapturedStateGauges SupportRuntime::capture_state_gauges() const {
  const auto& d=impl();return d.state_gauges(CapturedStateGauges(d.state->compiled.account()));
}
SupportSnapshot SupportRuntime::snapshot() const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable(); return d.snapshot(d.sequence);
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
detail::AccountedRowSet SupportRuntime::record_rows(NodeId id) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable(); const auto& node=d.node(id);
  auto result=detail::inspection_rows(d.state->compiled.account());
  for (const auto& tuple : d.state->storage.table(node.records).snapshot(d.work())) result.insert(tuple.values());
  return result;
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
SupportSnapshot SupportRuntime::Impl::snapshot(std::uint64_t visible_sequence) const {
  detail::StorageOperation storage_operation(storage_context);
  const auto& d=*this; SupportSnapshot result{visible_sequence,d.answer(*d.state),{}};
  for (const auto& node : d.program_nodes()) {
    const auto& metadata=d.state->nodes[node.id.value]; const auto& records=d.state->storage.table(node.records);
    NodeSupportSnapshot output{node.id,node.kind,{},{},{},{}};
    for(const auto& tuple:d.state->storage.table(node.survivors).snapshot(d.work()))output.survivors.push_back(d.plan_tuple(tuple));
    for (const auto& tuple : records.snapshot(d.work())) {
      const auto handle=*records.find(tuple, d.work()); const auto& record=metadata.records.at(handle.tuple);
      output.records.push_back({d.plan_tuple(tuple),d.handle(node.id,SupportRole::records,handle),record.satisfied,export_flags(record),
          d.state->storage.table(node.survivors).find(tuple, d.work()).has_value()});
    }
    const auto keys=[&](SupportRole role,const NodeState::Counts& counts) {
      std::vector<ProjectionKeySnapshot> values; const auto& table=d.state->storage.table(relation(node,role));
      for (const auto& key : table.snapshot(d.work())) { const auto handle=*table.find(key, d.work()); values.push_back({d.plan_tuple(key),d.handle(node.id,role,handle),counts.at(handle.tuple)}); }
      return values;
    };
    output.parent_keys=keys(SupportRole::parent_support,metadata.parent);
    if (node.visible_relation) output.visible_keys=keys(SupportRole::visible,metadata.visible);
    result.nodes.push_back(std::move(output));
  }
  return result;
}

CanonicalSupportState SupportRuntime::canonical_state() const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable();
  CanonicalSupportState result{std::string(d.plan.physical_sha256()),d.plan.source_catalog().version,d.sequence,d.answer(*d.state),{}};
  for (const auto& node : d.program_nodes()) {
    const auto& metadata=d.state->nodes[node.id.value];
    CanonicalNode output{node.id,node.kind,{}, {},{},std::nullopt};
    const auto& records=d.state->storage.table(node.records);
    const auto& survivors=d.state->storage.table(node.survivors);
    auto cursor=records.live(d.work());
    while (const auto handle=cursor.next(d.work())) {
      const auto& tuple=*records.get(*handle, d.work()); const auto& record=metadata.records.at(handle->tuple);
      output.records.push_back({storage::export_row(tuple.values()),record.satisfied.value,export_flags(record),survivors.find(tuple, d.work()).has_value()});
    }
    std::sort(output.records.begin(),output.records.end(),[](const auto& a,const auto& b) { return a.values<b.values; });
    auto surviving=survivors.live(d.work());
    while (const auto handle=surviving.next(d.work())) output.survivors.insert(storage::export_row(survivors.get(*handle, d.work())->values()));
    const auto counts=[&](RelationId id,const auto& metadata_counts) {
      std::vector<CanonicalCount> values; const auto& table=d.state->storage.table(id); auto keys=table.live(d.work());
      while (const auto handle=keys.next(d.work())) values.push_back({storage::export_row(table.get(*handle, d.work())->values()),metadata_counts.at(handle->tuple).value});
      std::sort(values.begin(),values.end(),[](const auto& a,const auto& b) { return a.key<b.key; }); return values;
    };
    output.parent=counts(node.parent_support,metadata.parent);
    if (node.visible_relation) output.visible=counts(*node.visible_relation,metadata.visible);
    result.nodes.push_back(std::move(output));
  }
  std::sort(result.nodes.begin(),result.nodes.end(),[](const auto& a,const auto& b) { return a.node.value<b.node.value; });
  return result;
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }

InvariantReport SupportRuntime::inspect_invariants(InspectionOptions options) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl(); d.readable(); detail::InspectionContext context(options,d.state->compiled.account());
  auto& statistics=context.report.statistics;
  const auto issue=[&](InvariantCode code,InvariantComponent component,NodeId node,storage::RowView key,
      std::optional<std::uint64_t> expected=std::nullopt,std::optional<std::uint64_t> actual=std::nullopt,
      std::optional<std::size_t> slot=std::nullopt) {
    context.add({code,component,std::nullopt,std::nullopt,node,slot,context.key(key),expected,actual});
  };
  try {
    // Storage checks are independent of support metadata. These precharges
    // are coarse; complete lower-level diagnostic scans are not wholly metered.
    for (const auto& definition : d.plan.relations()) {
      context.charge(); const auto& table=d.state->storage.table(definition.id);
      const auto arena=table.arena_statistics(); statistics.support_storage_records+=arena.live_records;
      context.charge(arena.slots);
      context.charge(table.size());
      for (const auto index : table.indices(d.work())) {
        context.charge(); context.charge(table.size()); context.charge(table.key_count(index, d.work()));
        for (const auto& key : table.keys(index, d.work())) {
          auto cursor=table.bucket_cursor(index,key, d.work());
          while (cursor.next(d.work())) { context.charge(); ++statistics.index_memberships; }
        }
      }
      try {
        require(table.relation()==definition.id && table.layout().same_token(d.state->storage.layout(definition.layout.id())),
            "storage_contract","physical relation has a different layout/identity");
        table.check_invariants();
      }
      catch (const Error&) {
        context.add({InvariantCode::storage,InvariantComponent::storage,definition.base,std::nullopt,definition.node,
            std::nullopt,context.key({}),std::nullopt,std::nullopt});
      } catch(const storage::TableValidationFailure&) {
        context.add({InvariantCode::storage,InvariantComponent::storage,definition.base,std::nullopt,definition.node,std::nullopt,context.key({}),std::nullopt,std::nullopt});
      } catch(const storage::IndexFailure&) {
        context.add({InvariantCode::storage,InvariantComponent::storage,definition.base,std::nullopt,definition.node,std::nullopt,context.key({}),std::nullopt,std::nullopt});
      }
    }
    for (const auto& index : d.plan.indexes()) {
      context.charge();
      try {
        require(d.state->storage.table(index.relation).projection(d.state->storage.index(index.id), d.work()).same_token(d.state->storage.projection(index.id)),
            "storage_contract","physical index has a different compiled projection");
      } catch (const Error&) {
        context.add({InvariantCode::storage,InvariantComponent::storage,std::nullopt,std::nullopt,
            d.plan.relations()[index.relation.value].node,std::nullopt,context.key({}),std::nullopt,std::nullopt});
      }
    }
    for (const auto& node : d.program_nodes()) {
      context.charge(); const auto& metadata=d.state->nodes[node.id.value];
      const auto& records=d.state->storage.table(node.records);
      const auto& survivors=d.state->storage.table(node.survivors);
      (node.kind==NodeKind::native?statistics.native_records:statistics.generalized_records)+=records.size();
      statistics.survivors+=survivors.size();
      statistics.parent_keys+=d.state->storage.table(node.parent_support).size();
      if (node.visible_relation) statistics.visible_keys+=d.state->storage.table(*node.visible_relation).size();
      auto expected_candidates=detail::inspection_rows(context.account);
      auto actual_candidates=detail::inspection_rows(context.account);
      auto expected_survivors=detail::inspection_rows(context.account);
      if (node.kind==NodeKind::generalized) for (const auto child : node.children) {
        context.charge(); const auto& table=d.state->storage.table(d.node(child).parent_support); auto cursor=table.live(d.work());
        while (const auto handle=cursor.next(d.work())) { context.charge(); expected_candidates.insert(table.get(*handle, d.work())->values()); }
      }
      auto cursor=records.live(d.work());
      while (const auto handle=cursor.next(d.work())) {
        context.charge(); const auto& tuple=*records.get(*handle, d.work()); const auto key=tuple.values();
        actual_candidates.insert(key);
        const auto found=metadata.records.find(handle->tuple);
        const RecordState* record=found==metadata.records.end()?nullptr:&found->second;
        if (!record) issue(InvariantCode::missing_metadata,InvariantComponent::record,node.id,key,1,0);
        else {
          if (record->present.size()!=node.children.size())
            issue(InvariantCode::child_presence,InvariantComponent::record,node.id,key,node.children.size(),record->present.size());
        }
        std::size_t satisfied=0;
        for (std::size_t slot=0;slot<node.children.size();++slot) {
          context.charge(); const auto& edge=d.program_edges()[d.children[node.id.value][slot]];
          const bool present=d.state->storage.table(d.node(edge.child).parent_support).find(edge.parent_key.apply(tuple), d.work()).has_value();
          if (present) ++satisfied;
          if (record && slot<record->present.size() && record->present[slot]!=present)
            issue(InvariantCode::child_presence,InvariantComponent::record,node.id,key,present,record->present[slot],slot);
        }
        if (record && record->satisfied.value!=satisfied)
          issue(InvariantCode::satisfied_count,InvariantComponent::record,node.id,key,satisfied,record->satisfied.value);
        const bool survives=satisfied==node.children.size();
        if (survives) expected_survivors.insert(key);
        const bool actual=survivors.find(tuple, d.work()).has_value();
        if (survives!=actual) issue(InvariantCode::membership,InvariantComponent::survivor,node.id,key,survives,actual);
      }
      for (const auto& [id,record] : metadata.records) {
        context.charge(); context.charge(record.present.size()); statistics.child_flags+=record.present.size();
        if (!records.get({records.owner(),records.relation(),id}, d.work()))
          issue(InvariantCode::orphan_metadata,InvariantComponent::record,node.id,{},0,1);
      }
      if (node.kind==NodeKind::generalized) {
        for (const auto& key : expected_candidates) {
          context.charge(); if (!actual_candidates.contains(key))
            issue(InvariantCode::missing_record,InvariantComponent::record,node.id,key.view(),1,0);
        }
        for (const auto& key : actual_candidates) {
          context.charge(); if (!expected_candidates.contains(key))
            issue(InvariantCode::unexpected_record,InvariantComponent::record,node.id,key.view(),0,1);
        }
      }
      auto surviving=survivors.live(d.work());
      while (const auto handle=surviving.next(d.work())) {
        context.charge(); const auto key=survivors.get(*handle, d.work())->values();
        if (!actual_candidates.contains(key)) issue(InvariantCode::unexpected_record,InvariantComponent::survivor,node.id,key,0,1);
      }
      const auto projection=[&](RelationId id,const storage::AccountedProjection& program,const auto& counts,InvariantComponent component) {
        auto expected=detail::inspection_counts<std::uint64_t>(context.account);
        // Recompute from the child-derived S, independently of stored S.
        for (const auto& row : expected_survivors) {
          context.charge();const auto projected=program.apply(node.layout.tuple(row.view()));auto& count=expected.try_emplace(projected.values(),std::uint64_t{0}).first->second;
          if (count==std::numeric_limits<std::uint64_t>::max()) { context.report.complete=false; throw detail::InspectionStop{}; }
          ++count;
        }
        const auto& table=d.state->storage.table(id); auto keys=table.live(d.work()); auto present=detail::inspection_rows(context.account);
        while (const auto handle=keys.next(d.work())) {
          context.charge(); const auto key=table.get(*handle, d.work())->values(); present.insert(key);
          const auto expected_entry=expected.find(key); const auto wanted=expected_entry==expected.end()?0:expected_entry->second;
          const auto found=counts.find(handle->tuple);
          if (found==counts.end()) issue(InvariantCode::missing_metadata,component,node.id,key,wanted,std::nullopt);
          else if (found->second.value!=wanted || wanted==0)
            issue(InvariantCode::support_count,component,node.id,key,wanted,found->second.value);
          if (wanted==0) issue(InvariantCode::unexpected_record,component,node.id,key,0,1);
        }
        for (const auto& [key,count] : expected) {
          context.charge(); if (!present.contains(key)) issue(InvariantCode::missing_record,component,node.id,key.view(),count,0);
        }
        for (const auto& [tuple_id,count] : counts) {
          context.charge(); if (!table.get({table.owner(),table.relation(),tuple_id}, d.work()))
            issue(InvariantCode::orphan_metadata,component,node.id,{},0,count.value);
        }
      };
      projection(node.parent_support,node.parent_key,metadata.parent,InvariantComponent::parent);
      if (node.visible_relation) projection(*node.visible_relation,*node.visible_projection,metadata.visible,InvariantComponent::visible);
      else for (const auto& [id,count] : metadata.visible) {
        static_cast<void>(id); context.charge(); issue(InvariantCode::orphan_metadata,InvariantComponent::visible,node.id,{},0,count.value);
      }
    }
  } catch (const detail::InspectionStop&) {}
  return std::move(context.report);
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }

#ifdef CROWN_RUNTIME_TESTING
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const SupportRuntime& runtime) {
  const auto& context=runtime.impl().storage_context;
  if (!context || !context->indexed()) return {};
  return RuntimeStorageWork{context->limit(),context->observed_work(),context->fresh_operations()};
}
resource::MemoryAccount RuntimeTestProbe::memory_account(const SupportRuntime& runtime) { return runtime.impl().storage_context->memory(); }
SupportValueState RuntimeTestProbe::record_metadata(const SupportRuntime& runtime,SupportHandle handle) {
  const auto& d=runtime.impl();d.readable();
  require(handle.owner==d.owner && handle.role==SupportRole::records,"invalid_probe","metadata probe needs an owned record handle");
  const auto& records=d.state->nodes[d.node(handle.node).id.value].records;
  const auto found=records.find(handle.tuple);
  require(found!=records.end(),"invalid_probe","metadata probe record is absent");
  return {true,found->second.satisfied,retained_flags(found->second),{}};
}
std::size_t RuntimeTestProbe::set_satisfied(SupportRuntime& runtime,NodeId id,const Row& row,std::size_t value) {
  detail::StorageOperation storage_operation(runtime.impl().storage_context);
  auto& d=runtime.impl(); d.writable(); const auto& node=d.node(id);
  const auto& table=d.state->storage.table(node.records); const auto handle=table.find(table.layout().tuple(row), d.work());
  require(handle.has_value(),"runtime_contract","probe record is absent");
  auto& count=d.state->nodes[id.value].records.at(handle->tuple).satisfied.value;
  return std::exchange(count,value);
}
std::uint64_t RuntimeTestProbe::set_projection(SupportRuntime& runtime,NodeId id,bool visible,const Row& row,std::uint64_t value) {
  detail::StorageOperation storage_operation(runtime.impl().storage_context);
  auto& d=runtime.impl(); d.writable(); const auto& node=d.node(id);
  const auto& table=d.state->storage.table(relation(node,visible?SupportRole::visible:SupportRole::parent_support));
  const auto handle=table.find(table.layout().tuple(row), d.work()); require(handle.has_value(),"runtime_contract","probe key is absent");
  auto& metadata=d.state->nodes[id.value]; auto& count=(visible?metadata.visible:metadata.parent).at(handle->tuple).value;
  return std::exchange(count,value);
}
#endif

void SupportRuntime::check_invariants() const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  auto& d=impl(); d.readable(); d.state->storage.check_invariants(d.work());
  const auto& account=d.state->compiled.account();
  for (const auto& node : d.program_nodes()) {
    const auto& metadata=d.state->nodes[node.id.value]; const auto& records=d.state->storage.table(node.records);
    const auto& survivors=d.state->storage.table(node.survivors);
    require(records.size()==metadata.records.size(),"runtime_contract","record metadata cardinality differs");
    auto expected_candidates=detail::inspection_rows(account); std::size_t expected_survivors=0;
    if (node.kind==NodeKind::generalized) for (const auto child : node.children)
      for (const auto& tuple : d.state->storage.table(d.program_nodes()[child.value].parent_support).snapshot(d.work())) expected_candidates.insert(tuple.values());
    auto actual_candidates=detail::inspection_rows(account);
    for (const auto& tuple : records.snapshot(d.work())) {
      const auto handle=*records.find(tuple, d.work()); const auto& record=metadata.records.at(handle.tuple);
      require(record.present.size()==node.children.size(),"runtime_contract","wrong child-state width");
      std::size_t satisfied=0;
      for (std::size_t slot=0;slot<node.children.size();++slot) {
        const auto& edge=d.program_edges()[d.children[node.id.value][slot]];
        const auto& child=d.program_nodes()[edge.child.value];
        const bool present=d.state->storage.table(child.parent_support).find(edge.parent_key.apply(tuple), d.work()).has_value();
        require(present==record.present[slot],"runtime_contract","stored child presence differs from actual support");
        if (present) ++satisfied;
      }
      require(satisfied==record.satisfied.value,"runtime_contract","satisfied-child count differs");
      const bool survives=satisfied==node.children.size(); if (survives) ++expected_survivors;
      require(survives==survivors.find(tuple, d.work()).has_value(),"runtime_contract","survivor membership differs from child support");
      if (node.kind==NodeKind::generalized) { require(satisfied>0,"runtime_contract","zero-presence generalized candidate retained"); actual_candidates.insert(tuple.values()); }
    }
    require(survivors.size()==expected_survivors,"runtime_contract","unexpected survivor record");
    if (node.kind==NodeKind::generalized) require(expected_candidates==actual_candidates,"runtime_contract","generalized candidates differ from the child-key union");
    const auto projection=[&](SupportRole role,const storage::AccountedProjection& program,const NodeState::Counts& counts) {
      auto expected=detail::inspection_counts<ProjectionSupportCount>(account);
      for (const auto& tuple : survivors.snapshot(d.work())) { const auto key=program.apply(tuple); auto& count=expected.try_emplace(key.values(),ProjectionSupportCount{}).first->second;count=increment_support(count,d.options.support_limit); }
      const auto& table=d.state->storage.table(relation(node,role));
      require(table.size()==expected.size() && counts.size()==expected.size(),"runtime_contract","projection metadata cardinality differs");
      for (const auto& key : table.snapshot(d.work())) {
        const auto found=expected.find(key.values()); const auto handle=*table.find(key, d.work());
        require(found!=expected.end() && counts.at(handle.tuple)==found->second,"runtime_contract","projection support count differs from survivors");
      }
    };
    projection(SupportRole::parent_support,node.parent_key,metadata.parent);
    if (node.visible_projection) projection(SupportRole::visible,*node.visible_projection,metadata.visible);
    else require(metadata.visible.empty(),"runtime_contract","hidden node has visible support counters");
  }
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
std::shared_ptr<detail::ObservationState> SupportRuntime::observation_state() const { return impl().observation; }
ObservationSnapshot SupportRuntime::observations() const {
  const auto& d=impl(); return detail::observation_snapshot(d.observation,d.options.observation);
}
ObservationTrace SupportRuntime::observation_trace() const {
  const auto& d=impl(); return detail::observation_trace(d.observation,d.options.observation);
}
CapturedObservationTrace SupportRuntime::capture_observation_trace() const {
  const auto& d=impl();return detail::capture_observation_trace(d.observation,d.options.observation,d.state->compiled.account());
}
}  // namespace crown::runtime

namespace crown::runtime {
void SupportRuntime::configure_workload_statistics(const workload::Options& options) {
  auto& d=impl(); d.writable(); d.workload.configure(d.state->compiled,false,options,d.sequence);
}
void SupportRuntime::reset_workload_statistics() {
  auto& d=impl(); d.writable(); d.workload.reset(d.sequence);
}
workload::Snapshot SupportRuntime::workload_statistics() const {
  const auto& d=impl(); return d.workload.snapshot(d.state->compiled,d.owner,d.sequence,d.updating);
}
workload::detail::State& SupportRuntime::workload_state() const { return impl().workload; }
const CompiledProgram& SupportRuntime::compiled_program() const {return impl().state->compiled;}
std::shared_ptr<detail::StorageWorkContext> SupportRuntime::storage_context() const { return impl().storage_context; }
} // namespace crown::runtime
#include "owner_statistics_detail.hpp"
namespace crown::runtime {
void SupportRuntime::append_statistics(statistics::detail::OwnerBuilder& builder,const statistics::Selection& selection) const try {
  detail::StorageOperation storage_operation(impl().storage_context);
  using namespace statistics;
  auto* component=builder.append(selection);if(!component)return;
  const auto& d=impl();
  if(const auto* requested=std::get_if<NodeScope>(&selection.scope)) {
    const auto& node=d.node(requested->node);component->node_kind=node.kind;
    if(requested->role==SupportRole::visible && !node.visible_relation){component->availability=Availability::not_applicable;return;}
    const auto id=relation(node,requested->role);const auto& table=d.state->storage.table(id);
    if(requested->role==SupportRole::records || requested->role==SupportRole::survivors){builder.table(*component,table,d.state->compiled.relations()[id.value].layout.descriptor(),d.work());return;}
    require(!selection.fields,"invalid_statistics_request","support distribution uses complete stored support keys");
    component->layout=d.state->compiled.relations()[id.value].layout.descriptor();component->cardinality=table.size();
    component->storage_invalidation=Stamp{table.owner(),table.relation(),table.revision()};
    const auto& counts=requested->role==SupportRole::parent_support?d.state->nodes[node.id.value].parent:d.state->nodes[node.id.value].visible;
    try {
      statistics::detail::WeightedBuilder weighted{builder.budget(),builder.account()};
      try {
        for(const auto& [tuple,count]:counts){
          builder.budget().work();const auto* key=table.get({table.owner(),id,tuple}, d.work());
          if(!key)throw Error("statistics_contract","support counter lacks its stored key");
          if(!weighted.add(key->values(),count.value))break;
        }
      // Exhaustion is an incomplete distribution; corruption/ownership faults
      // still leave through the outer presentation boundary. Reuse the same grant.
      }catch(const statistics::detail::Exhausted&){weighted.stop();}
      catch(const storage::IndexFailure& failure){if(failure.code()!="storage_work_limit")throw;weighted.stop();}
      component->distribution=weighted.finish();
      if(component->distribution->completion!=Completion::exact)component->availability=Availability::budget_exhausted;
    }catch(const statistics::detail::Exhausted&){component->availability=Availability::budget_exhausted;component->distribution=CapturedDistribution{};}
    return;
  }
  if(const auto* requested=std::get_if<IndexScope>(&selection.scope)) {
    require(requested->requirement.value<d.state->compiled.indexes().size(),"invalid_statistics_request","index requirement outside plan");
    require(!selection.fields,"invalid_statistics_request","index distribution does not accept another projection");
    const auto& index=d.state->compiled.indexes()[requested->requirement.value];
    builder.index(*component,d.state->storage.table(index.relation),d.state->storage.index(index.id),index.projection.descriptor(),d.work());return;
  }
  component->availability=Availability::unavailable;
} catch(const storage::IndexFailure& failure) { support_present(failure); } catch(const storage::TableValidationFailure& failure) { support_present(failure); }
statistics::OwnerCapture SupportRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  return capture_statistics_view(request,limits);
}
statistics::OwnerCapture SupportRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits) const {
  detail::StorageOperation storage_operation(impl().storage_context);
  const auto& d=impl();statistics::detail::OwnerBuilder builder{{d.owner,d.sequence,statistics::OwnerLayer::support},d.state->compiled,request,limits,d.updating};
  if(builder.active())for(const auto& selection:request.selections){if(!builder.active())break;append_statistics(builder,selection);}
  return builder.finish();
}
statistics::Freshness SupportRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  const auto& d=impl();return statistics::compare_freshness(captured.stamp(),{d.owner,d.sequence,statistics::OwnerLayer::support},max_event_lag);
}
}

namespace crown::runtime::memory::detail {
void Access::append(Builder& builder,const SupportRuntime& owner) {
  const auto& d=owner.impl();builder.operation(Coordinator{Layer::support,{}});
  for(const auto& definition:d.plan.relations())
    builder.table(TableScope::support,d.state->storage.table(definition.id),definition.role,definition.node,definition.base);
  for(const auto& node:d.program_nodes()) {
    const auto& state=d.state->nodes[node.id.value];std::uint64_t flags=0;
    for(const auto& record:state.records) {
      builder.work();if(record.second.present.size()!=node.children.size())throw Failure{Stop::inconsistent};
      flags=Builder::add(flags,static_cast<std::uint64_t>(record.second.present.size()));
    }
    if(state.records.size()!=d.state->storage.table(node.records).size() ||
        state.parent.size()!=d.state->storage.table(node.parent_support).size() ||
        (node.visible_relation && state.visible.size()!=d.state->storage.table(*node.visible_relation).size()) ||
        (!node.visible_relation && !state.visible.empty()))throw Failure{Stop::inconsistent};
    builder.operation(SupportNode{node.id,state.attribution,static_cast<std::uint64_t>(state.records.size()),
        static_cast<std::uint64_t>(d.state->storage.table(node.survivors).size()),static_cast<std::uint64_t>(state.parent.size()),
        node.visible_relation?std::optional<std::uint64_t>{static_cast<std::uint64_t>(state.visible.size())}:std::nullopt,flags});
  }
}
Attempt Access::capture(const SupportRuntime& owner,Limits limits) noexcept {
  return attempt([&](Usage& usage) {
    if(!owner.impl_)throw Failure{Stop::invalid_handle};
    const auto& d=owner.impl();const auto availability=d.updating?Availability::pending:Availability::committed;
    Builder builder(d.plan.account(),Layer::support,availability,d.owner.value,d.sequence,d.plan.physical_sha256(),limits,usage);
    if(availability==Availability::committed)append(builder,owner);
    return builder.finish();
  });
}
}
