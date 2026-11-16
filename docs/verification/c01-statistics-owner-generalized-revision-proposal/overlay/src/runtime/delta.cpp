#include "crown/runtime/delta.hpp"

#include "crown/api/error.hpp"
#include "inspection_detail.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <chrono>
#include <map>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
std::size_t add_size(std::size_t left,std::size_t right) {
  require(right<=std::numeric_limits<std::size_t>::max()-left,"resource_limit","delta size accounting exhausted");
  return left+right;
}
std::size_t slots_size(std::size_t count,std::size_t width) {
  require(count<=std::numeric_limits<std::size_t>::max()/width,"resource_limit","delta slot accounting exhausted");
  return count*width;
}
struct PhaseTimer {
  std::uint64_t& counter;
  const std::uint64_t* excluded;
  std::uint64_t previous=0, started=0;
  std::shared_ptr<detail::ObservationState> observation;
  PhaseTimer(std::uint64_t& value,const std::shared_ptr<detail::ObservationState>& state,
      const std::uint64_t* nested=nullptr) noexcept
      :counter(value),excluded(nested),previous(nested?*nested:0),
       observation(state && state->clocks_enabled()?state:nullptr) {
    if (observation) started=observation->now();
  }
  ~PhaseTimer() {
    if (!observation) return; // No clock expression is evaluated in off/counters.
    const auto stopped=observation->now();
    const auto total=stopped>started?stopped-started:0;
    const auto child=excluded?*excluded-previous:0;
    const auto amount=total>child?total-child:0;
    counter+=std::min(amount,std::numeric_limits<std::uint64_t>::max()-counter);
  }
};
}  // namespace

struct DeltaRuntime::Impl {
  struct Factor {
    NodeId node;
    std::vector<VariableId> scope;
    std::optional<std::size_t> parent;
    std::vector<std::size_t> parent_separator, child_separator, head_fields;
    std::vector<std::size_t> children;
  };
  struct LiveParentSupport {
    std::uint64_t value=0;
    Relation rows;
    bool operator==(const LiveParentSupport&) const = default;
  };
  using ParentCounts=std::map<Row,LiveParentSupport>;
  using RemovedParents=std::vector<std::map<Row,Relation>>;
  struct LiveImage {
    std::vector<Relation> factors;
    std::vector<ParentCounts> parents;
    std::vector<ParentCounts> child_index;
    std::size_t rows=0, parent_rows=0, child_rows=0;
  };
  struct ProductiveQueue {
    std::vector<Relation> factors;
    std::size_t rows=0;
    explicit ProductiveQueue(std::size_t size):factors(size) {}
  };
  struct LiveTransaction;
  struct AnchoredCursor;
  struct Stage;
  DeltaOptions options;
  DeltaCompletion selected_completion=DeltaCompletion::anchored;
  PhysicalRuntime physical;
  std::shared_ptr<detail::ObservationState> observation;
  storage::TupleLayout output_layout;
  storage::TupleLayout core_layout;
  std::vector<Factor> factors;
  std::vector<std::optional<std::size_t>> ranks;
  std::shared_ptr<LiveImage> live;
  std::uint64_t live_sequence=0;
  DeltaMode mode=DeltaMode::maintenance;
  DeltaMetrics bootstrap;
  BuildMetrics initialization;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
  bool processing=false, output_active=false;
  DeltaState lifecycle=DeltaState::ready;

  Impl(PhysicalPlan plan,DeltaOptions value)
      :Impl(PhysicalRuntime(std::move(plan),value.physical),value) {}
  Impl(PhysicalRuntime owner,DeltaOptions value)
      :options(value),physical(std::move(owner)),observation(physical.observation_state()),output_layout(physical.result_layout(value.view)),
       core_layout(physical.result_layout(ResultView::core)),
       ranks(physical.plan().nodes().size()) {
    require(options.mode==DeltaMode::maintenance || options.mode==DeltaMode::delta,"invalid_options","unknown initial delta mode");
    require(options.live_maintenance==LiveMaintenance::on_output || options.live_maintenance==LiveMaintenance::incremental || options.live_maintenance==LiveMaintenance::eager,
        "invalid_options","unknown live maintenance policy");
    require(options.completion==DeltaCompletion::automatic || options.completion==DeltaCompletion::ordered_replay ||
        options.completion==DeltaCompletion::anchored || options.completion==DeltaCompletion::root_first,
        "invalid_options","unknown delta completion policy");
    selected_completion=options.completion==DeltaCompletion::automatic?
        (options.live_maintenance==LiveMaintenance::on_output?DeltaCompletion::ordered_replay:DeltaCompletion::anchored):options.completion;
    require(selected_completion!=DeltaCompletion::ordered_replay || options.live_maintenance==LiveMaintenance::on_output,
        "invalid_options","ordered replay requires row-coupled live maintenance");
    const auto& compiled=physical.plan(); const auto& program=compiled.enumeration();
    factors.reserve(program.steps.size());
    for (std::size_t i=0;i<program.steps.size();++i) {
      const auto& step=program.steps[i]; const auto& node=compiled.nodes()[step.node.value];
      Factor factor{node.id,node.visible_scope,step.parent_step,{},{},{},{}};
      for (const auto variable : factor.scope) {
        const auto found=std::find_if(compiled.query().head.begin(),compiled.query().head.end(),
            [&](const auto& output) { return output.variable==variable; });
        require(found!=compiled.query().head.end(),"runtime_contract","E factor contains a hidden variable");
        factor.head_fields.push_back(static_cast<std::size_t>(found-compiled.query().head.begin()));
      }
      if (factor.parent) {
        require(*factor.parent<i,"runtime_contract","E factors are not parent-before-child");
        const auto& parent=factors[*factor.parent];
        for (std::size_t child=0;child<factor.scope.size();++child) {
          const auto found=std::lower_bound(parent.scope.begin(),parent.scope.end(),factor.scope[child]);
          if (found!=parent.scope.end() && *found==factor.scope[child]) {
            factor.parent_separator.push_back(static_cast<std::size_t>(found-parent.scope.begin()));
            factor.child_separator.push_back(child);
          }
        }
      }
      const auto parent=factor.parent;
      ranks[node.id.value]=i; factors.push_back(std::move(factor));
      if (parent) factors[*parent].children.push_back(i);
    }
  }
  // Called only after successful construction or a semantic mode switch.
  // Bootstrap runs before initial binding, with temporarily adjusted build
  // budgets; those temporary budgets must never become the retained identity.
  void observe_configuration(bool initial=false) noexcept {
    if (!observation) return;
    const auto& previous=observation->configuration();
    if (!initial && !previous) return; // Unpublished constructor bootstrap.
    std::uint64_t generation=initial?0:previous->generation();
#ifdef CROWN_RUNTIME_TESTING
    if (initial) generation=detail::observation_initial_generation_for_testing();
#endif
    bool saturated=initial?false:previous->generation_saturated();
    if (!initial) {
      if (generation==std::numeric_limits<std::uint64_t>::max()) saturated=true;
      else ++generation;
    }
    observation->configure(ObservationConfiguration::capture(options,mode,
        selected_completion,physical.owner().value,generation,saturated,factors.size()));
  }
  void readable() const { require(!processing,"runtime_busy","delta epoch preparation is active"); }
  void writable() const {
    readable(); require(!output_active && physical.ready(),"runtime_busy","query readers or committed delta output are active");
  }
  void charge(DeltaMetrics& metrics,std::uint64_t amount=1) const {
    const auto used=metrics.work;
    require(amount<=std::numeric_limits<std::uint64_t>::max()-used &&
        (!options.work_limit || (used<=*options.work_limit && amount<=*options.work_limit-used)),
        "resource_limit","delta work limit exceeded; unpublished input preserved");
    metrics.work+=amount;
  }
  void metric(DeltaMetrics& metrics,std::uint64_t& counter,std::uint64_t amount=1) const {
    charge(metrics,amount); counter+=amount;
  }
  Row project(const Row& row,const std::vector<std::size_t>& fields,DeltaMetrics& metrics,std::uint64_t& counter) const {
    Row result; result.reserve(fields.size());
    for (const auto field : fields) { metric(metrics,counter); result.push_back(row.at(field)); }
    return result;
  }
  void cursor_start(const SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const {
    metric(metrics,metrics.cursor_startup_work,cursor.metrics().startup.work);
  }
  std::optional<storage::Tuple> cursor_next(SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const {
    auto row=cursor.next();
    metric(metrics,row?metrics.cursor_results_work:metrics.cursor_termination_work,cursor.metrics().last.work);
    return row;
  }
  std::shared_ptr<LiveImage> build_live(const SupportRuntime::EpochView& view,DeltaMetrics& metrics,std::size_t retained,
      std::size_t retained_parents=0,std::size_t retained_children=0) const {
    auto result=std::make_shared<LiveImage>(); result->factors.resize(factors.size()); result->parents.resize(factors.size());
    result->child_index.resize(factors.size());
    metrics.peak_live_rows=std::max(metrics.peak_live_rows,retained);
    metrics.peak_parent_index_rows=std::max(metrics.peak_parent_index_rows,retained_parents);
    metrics.peak_child_index_rows=std::max(metrics.peak_child_index_rows,retained_children);
    for (std::size_t i=0;i<factors.size();++i) {
      const auto& factor=factors[i]; auto& separators=result->parents[i];
      if (factor.parent) for (const auto& row : result->factors[*factor.parent]) {
        metric(metrics,metrics.parent_live_rows);
        auto key=project(row,factor.parent_separator,metrics,metrics.separator_fields);
        auto& count=separators.try_emplace(std::move(key),LiveParentSupport{}).first->second;
        require(count.value!=std::numeric_limits<std::uint64_t>::max(),"support_overflow","live-parent separator support exhausted");
        metric(metrics,metrics.live_parent_index_rows_copied);
        metric(metrics,metrics.live_parent_index_fields,static_cast<std::uint64_t>(row.size()));
        require(count.rows.insert(row).second,"runtime_contract","live-parent index duplicated a parent key");
        ++count.value;
        result->parent_rows=add_size(result->parent_rows,1);
        metrics.peak_parent_index_rows=std::max(metrics.peak_parent_index_rows,add_size(retained_parents,result->parent_rows));
      }
      auto cursor=view.visible_keys(factor.node,options.cursor); cursor_start(cursor,metrics);
      while (auto tuple=cursor_next(cursor,metrics)) {
        metric(metrics,metrics.e_rows_scanned);
        if (factor.parent && !separators.contains(project(tuple->values(),factor.child_separator,metrics,metrics.separator_fields))) continue;
        metric(metrics,metrics.live_rows_copied);
        require(result->factors[i].insert(tuple->values()).second,"runtime_contract","E factor cursor duplicated a key");
        if (factor.parent) {
          auto key=project(tuple->values(),factor.child_separator,metrics,metrics.live_child_separator_fields);
          auto& bucket=result->child_index[i].try_emplace(std::move(key),LiveParentSupport{}).first->second;
          require(bucket.value!=std::numeric_limits<std::uint64_t>::max(),"support_overflow","live-child index support exhausted");
          metric(metrics,metrics.live_child_index_rows_copied);
          metric(metrics,metrics.live_child_index_fields,static_cast<std::uint64_t>(tuple->values().size()));
          require(bucket.rows.insert(tuple->values()).second,"runtime_contract","live-child index duplicated a key");
          ++bucket.value; result->child_rows=add_size(result->child_rows,1);
          metrics.peak_child_index_rows=std::max(metrics.peak_child_index_rows,add_size(retained_children,result->child_rows));
        }
        result->rows=add_size(result->rows,1);
        metrics.peak_live_rows=std::max(metrics.peak_live_rows,add_size(retained,result->rows));
      }
    }
    metrics.live_rows=result->rows; metrics.parent_index_rows=result->parent_rows;
    metrics.child_index_rows=result->child_rows; return result;
  }
  bool scalar_sql() const {
    const auto& normalized=physical.plan().normalized();
    return options.view==ResultView::sql && normalized && normalized->binding.wrapper==frontend::SqlWrapper::exists;
  }
  storage::Tuple map_result(storage::Tuple core,DeltaMetrics& metrics) const {
    const auto& normalized=physical.plan().normalized();
    if (options.view==ResultView::core || !normalized) {
      metric(metrics,metrics.output_fields,static_cast<std::uint64_t>(core.values().size())); return core;
    }
    Row result; result.reserve(normalized->outputs.size());
    for (const auto& output : normalized->outputs) {
      metric(metrics,metrics.output_fields);
      if (const auto* field=std::get_if<frontend::CoreOutput>(&output.value)) result.push_back(core.values().at(field->column));
      else result.push_back(std::get<frontend::ConstantOutput>(output.value).value);
    }
    return output_layout.tuple(std::move(result));
  }
};

struct DeltaRuntime::Impl::LiveTransaction {
  enum class Kind { insert_live, erase_live, insert_separator, change_separator, erase_separator };
  struct Undo {
    std::unique_ptr<Undo> previous;
    Kind kind=Kind::insert_live;
    std::size_t factor=0;
    Relation::iterator inserted;
    Relation::node_type erased;
    ParentCounts::iterator inserted_separator;
    ParentCounts::node_type erased_separator;
    LiveParentSupport* count=nullptr;
    std::uint64_t before=0;
    Relation::iterator parent_inserted;
    Relation::node_type parent_erased;
    bool parent_added=false;
    bool child_side=false;
  };
  struct Event { std::size_t factor; const Row* row; };
  const Impl& runtime;
  DeltaMetrics& metrics;
  std::shared_ptr<LiveImage> image;
  std::unique_ptr<Undo> undo;
  std::vector<Event> pending;
  RemovedParents removed_parents;
  std::size_t erased_rows=0, removed_copies=0, erased_parent_rows=0, removed_parent_copies=0, erased_child_rows=0;
  bool retain_before=true;
  std::uint64_t undo_entries=0;
  bool closed=false;
  LiveTransaction(const Impl& owner,DeltaMetrics& work,std::shared_ptr<LiveImage> state)
      :runtime(owner),metrics(work),image(std::move(state)),removed_parents(image->parents.size()),
       retain_before(owner.selected_completion!=DeltaCompletion::ordered_replay) {}
  ~LiveTransaction() { rollback(); }
  std::unique_ptr<Undo> prepare(Kind kind,std::size_t factor,bool child_side=false) {
    runtime.metric(metrics,metrics.live_journal_entries);
    auto item=std::make_unique<Undo>(); item->kind=kind; item->factor=factor; item->child_side=child_side;
    return item;
  }
  void record(std::unique_ptr<Undo> item) noexcept {
    item->previous=std::move(undo); undo=std::move(item); ++undo_entries;
  }
  void prepare_commit() { runtime.metric(metrics,metrics.finalization_undo_entries,undo_entries); }
  void peak() {
    metrics.peak_live_rows=std::max(metrics.peak_live_rows,add_size(add_size(image->rows,erased_rows),removed_copies));
    metrics.parent_index_rows=image->parent_rows;
    metrics.peak_parent_index_rows=std::max(metrics.peak_parent_index_rows,
        add_size(add_size(image->parent_rows,erased_parent_rows),removed_parent_copies));
    metrics.child_index_rows=image->child_rows;
    metrics.peak_child_index_rows=std::max(metrics.peak_child_index_rows,add_size(image->child_rows,erased_child_rows));
  }
  void rollback() noexcept {
    if (closed) return;
    pending.clear();
    while (undo) {
      auto item=std::move(undo); undo=std::move(item->previous);
      if (undo_entries==0) std::terminate();
      --undo_entries; auto& entry=*item;
      auto& index=entry.child_side?image->child_index[entry.factor]:image->parents[entry.factor];
      auto& index_rows=entry.child_side?image->child_rows:image->parent_rows;
      switch (entry.kind) {
        case Kind::insert_live: image->factors[entry.factor].erase(entry.inserted); --image->rows; break;
        case Kind::erase_live:
          if (!image->factors[entry.factor].insert(std::move(entry.erased)).inserted) std::terminate();
          ++image->rows; break;
        case Kind::insert_separator:
          index_rows-=entry.inserted_separator->second.rows.size();
          index.erase(entry.inserted_separator); break;
        case Kind::change_separator:
          if (entry.parent_added) { entry.count->rows.erase(entry.parent_inserted); --index_rows; }
          else {
            if (!entry.count->rows.insert(std::move(entry.parent_erased)).inserted) std::terminate();
            ++index_rows;
          }
          entry.count->value=entry.before; break;
        case Kind::erase_separator:
          index_rows+=entry.erased_separator.mapped().rows.size();
          if (!index.insert(std::move(entry.erased_separator)).inserted) std::terminate();
          break;
      }
    }
    closed=true;
  }
  void commit() noexcept {
    while (undo) {
      auto item=std::move(undo); undo=std::move(item->previous);
      if (undo_entries==0) std::terminate();
      --undo_entries;
    }
    pending.clear(); closed=true;
  }
  void change(std::size_t factor,const Row& key,bool add,std::vector<Relation>& removed,ProductiveQueue* productive=nullptr) {
    runtime.metric(metrics,metrics.live_probes);
    auto& rows=image->factors[factor]; const auto found=rows.find(key);
    if ((found!=rows.end())==add) return;
    const Row* event_row=nullptr;
    if (add) {
      const auto next_size=add_size(image->rows,1);
      auto item=prepare(Kind::insert_live,factor);
      const auto [inserted,fresh]=rows.insert(key);
      require(fresh,"runtime_contract","live key insertion duplicated membership");
      item->inserted=inserted; event_row=&*inserted;
      record(std::move(item)); image->rows=next_size;
      runtime.metric(metrics,metrics.live_inserts);
    } else {
      require(image->rows!=0,"runtime_contract","live row accounting underflow");
      auto item=prepare(Kind::erase_live,factor);
      if (retain_before) {
        require(removed[factor].insert(key).second,"runtime_contract","a live row was removed twice in one stage");
        ++removed_copies;
      }
      item->erased=rows.extract(found); event_row=&item->erased.value();
      record(std::move(item)); --image->rows; ++erased_rows;
      runtime.metric(metrics,metrics.live_erases);
    }
    runtime.metric(metrics,metrics.live_changes);
    if (add || retain_before) runtime.metric(metrics,metrics.live_rows_copied);
    if (runtime.factors[factor].parent) {
      const auto separator_key=runtime.project(key,runtime.factors[factor].child_separator,metrics,metrics.live_child_separator_fields);
      static_cast<void>(separator(factor,separator_key,key,add,true));
    }
    if (!add && productive) {
      runtime.metric(metrics,metrics.replay_queue_lookups);
      const auto erased=productive->factors[factor].erase(key);
      require(erased<=productive->rows,"runtime_contract","productive queue row accounting underflow");
      productive->rows-=erased;
      runtime.metric(metrics,metrics.replay_queue_erases,static_cast<std::uint64_t>(erased));
    }
    peak(); pending.push_back({factor,event_row});
    metrics.live_queue_peak=std::max(metrics.live_queue_peak,pending.size());
  }
  bool separator(std::size_t child,const Row& key,const Row& parent_row,bool add,bool child_side=false) {
    auto& counts=child_side?image->child_index[child]:image->parents[child]; const auto found=counts.find(key);
    auto& row_count=child_side?image->child_rows:image->parent_rows;
    auto& erased_count=child_side?erased_child_rows:erased_parent_rows;
    const auto before=found==counts.end()?std::uint64_t{0}:found->second.value;
    if (add) require(before!=std::numeric_limits<std::uint64_t>::max(),"support_overflow","live-parent separator support exhausted");
    else require(before!=0,"runtime_contract","removing an absent live-parent separator support");
    const auto after=add?before+1:before-1;
    require(add || row_count!=0,"runtime_contract","live index row accounting underflow");
    const auto next_rows=add?add_size(row_count,1):row_count-1;
    const auto next_erased=add?erased_count:add_size(erased_count,1);
    const bool copy_before=!child_side && retain_before;
    const auto next_removed=add || !copy_before?removed_parent_copies:add_size(removed_parent_copies,1);
    auto item=prepare(before==0?Kind::insert_separator:after==0?Kind::erase_separator:Kind::change_separator,child,child_side);
    if (add || copy_before) {
      runtime.metric(metrics,child_side?metrics.live_child_index_rows_copied:metrics.live_parent_index_rows_copied);
      runtime.metric(metrics,child_side?metrics.live_child_index_fields:metrics.live_parent_index_fields,
          static_cast<std::uint64_t>(parent_row.size()));
    }
    if (!add && copy_before) require(removed_parents[child][key].insert(parent_row).second,
        "runtime_contract","a parent index row was removed twice in one stage");
    removed_parent_copies=next_removed;
    if (before==0) {
      const auto [entry,fresh]=counts.emplace(key,LiveParentSupport{});
      require(fresh,"runtime_contract","live-parent separator insertion duplicated a key"); item->inserted_separator=entry;
      // Own the outer insertion before the inner row copy can throw.
      record(std::move(item));
      require(entry->second.rows.insert(parent_row).second,"runtime_contract","live-parent index insertion duplicated a row");
      entry->second.value=after;
    } else if (after==0) {
      require(found->second.value==found->second.rows.size() && found->second.rows.contains(parent_row),
          "runtime_contract","last live-parent index row differs from its count");
      item->erased_separator=counts.extract(found); record(std::move(item));
    } else {
      // Reverse undo restores a later extracted outer node before using this
      // mapped address or reinserting an older extracted inner row.
      item->count=&found->second; item->before=found->second.value; item->parent_added=add;
      if (add) {
        const auto [entry,fresh]=found->second.rows.insert(parent_row);
        require(fresh,"runtime_contract","live-parent index insertion duplicated a row"); item->parent_inserted=entry;
      } else {
        const auto row=found->second.rows.find(parent_row);
        require(row!=found->second.rows.end(),"runtime_contract","live-parent index removal missed a row");
        item->parent_erased=found->second.rows.extract(row);
      }
      record(std::move(item)); found->second.value=after;
    }
    row_count=next_rows; erased_count=next_erased; peak();
    runtime.metric(metrics,child_side?metrics.live_child_index_updates:metrics.live_parent_index_updates);
    if (!child_side) runtime.metric(metrics,metrics.live_separator_updates);
    if (before!=0 && after!=0) return false;
    if (!child_side) runtime.metric(metrics,metrics.live_separator_crossings);
    return true;
  }
  void end_stage() {
    if (!retain_before) runtime.metric(metrics,metrics.replay_factor_steps,static_cast<std::uint64_t>(removed_parents.size()));
    runtime.metric(metrics,metrics.live_parent_index_cleanup_rows,static_cast<std::uint64_t>(removed_parent_copies));
    for (auto& relation : removed_parents) {
      relation.clear();
    }
    removed_parent_copies=0; peak();
  }
  void begin_stage() {
    end_stage();
    pending.clear(); removed_copies=0; peak();
  }
  void apply(const std::vector<Relation>& changed,const SupportRuntime::EpochView& context,
      bool add,std::vector<Relation>& removed) {
    begin_stage();
    for (std::size_t i=0;i<changed.size();++i) for (const auto& key : changed[i]) {
      if (add && runtime.factors[i].parent) {
        const auto separator=runtime.project(key,runtime.factors[i].child_separator,metrics,metrics.separator_fields);
        runtime.metric(metrics,metrics.live_probes);
        if (!image->parents[i].contains(separator)) continue;
      }
      change(i,key,add,removed);
    }
    for (std::size_t position=0;position<pending.size();++position) {
      // Copy the pointer record: appending child events may move the vector.
      const auto event=pending[position];
      for (const auto child : runtime.factors[event.factor].children) {
        auto key=runtime.project(*event.row,runtime.factors[child].parent_separator,metrics,metrics.separator_fields);
        if (!separator(child,key,*event.row,add)) continue;
        runtime.metric(metrics,metrics.live_bucket_opens);
        auto cursor=context.visible_bucket(runtime.factors[child].node,key,runtime.options.cursor);
        runtime.cursor_start(cursor,metrics);
        while (auto row=runtime.cursor_next(cursor,metrics)) {
          runtime.metric(metrics,metrics.live_bucket_rows); change(child,row->values(),add,removed);
        }
      }
    }
    pending.clear(); metrics.live_rows=image->rows;
  }
  void on_output(const Row& row,const std::vector<Relation>& changed,bool add,std::vector<Relation>& removed,
      std::optional<std::size_t> anchor={},ProductiveQueue* productive=nullptr) {
    // Parent support changes must precede the descendant projection in this
    // same accepted row. No E bucket is scanned; see incremental_live.md for
    // the deletion certificate ensuring later rows finish every dead key.
    for (std::size_t i=0;i<runtime.factors.size();++i) {
      auto key=runtime.project(row,runtime.factors[i].head_fields,metrics,metrics.projection_fields);
      if (!add) {
        runtime.metric(metrics,metrics.live_probes);
        if (!image->factors[i].contains(key)) continue;
        runtime.metric(metrics,metrics.live_probes);
        // Replay changes only this full anchor key in the conceptual E state.
        bool gone=anchor?i==*anchor:changed[i].contains(key);
        if (!gone && runtime.factors[i].parent) {
          auto parent_key=runtime.project(key,runtime.factors[i].child_separator,metrics,metrics.separator_fields);
          runtime.metric(metrics,metrics.live_probes); gone=!image->parents[i].contains(parent_key);
        }
        if (!gone) continue;
      }
      change(i,key,add,removed,productive);
      for (const auto event : pending) for (const auto child : runtime.factors[event.factor].children) {
        const auto parent_key=runtime.project(*event.row,runtime.factors[child].parent_separator,metrics,metrics.separator_fields);
        static_cast<void>(separator(child,parent_key,*event.row,add));
      }
      pending.clear();
    }
    metrics.live_rows=image->rows;
  }
};

// A delta-only full-key cursor. General partial/hidden D02 completions retain
// their separate semantics. Upward rows are copied before any live mutation.
struct DeltaRuntime::Impl::AnchoredCursor {
  struct Step { std::size_t factor; std::optional<std::size_t> from; std::size_t edge; bool upward; };
  struct Frame {
    std::optional<storage::Tuple> selected;
    std::optional<Row> separator;
    std::optional<SupportRuntime::ResultCursor> down;
    bool opened=false;
  };
  const Impl& runtime;
  const SupportRuntime::EpochView& target;
  const LiveImage& image;
  const RemovedParents* removed;
  DeltaMetrics& metrics;
  std::vector<Step> steps;
  std::vector<std::size_t> positions;
  std::vector<Frame> frames;
  std::vector<bool> inside;
  bool replay=false;
  std::uint64_t work=0;
  std::size_t position=1;
  bool resume=false, finished=false;

  void note(std::uint64_t& counter,std::uint64_t amount=1) {
    require(amount<=std::numeric_limits<std::uint64_t>::max()-work &&
        (!runtime.options.cursor.work_limit || (work<=*runtime.options.cursor.work_limit &&
          amount<=*runtime.options.cursor.work_limit-work)),"resource_limit","anchored cursor work limit exceeded");
    runtime.metric(metrics,counter,amount); work+=amount;
  }
  Row project(const Row& row,const std::vector<std::size_t>& fields) {
    Row result; result.reserve(fields.size());
    for (const auto field : fields) { note(metrics.anchor_fields); result.push_back(row.at(field)); }
    return result;
  }
  const storage::TupleLayout& layout(std::size_t factor) const {
    const auto& plan=runtime.physical.plan();
    return plan.relations()[plan.nodes()[runtime.factors[factor].node.value].visible_relation->value].layout;
  }
  AnchoredCursor(const Impl& owner,const SupportRuntime::EpochView& view,const LiveImage& state,
      const RemovedParents* restored,DeltaMetrics& account,std::size_t anchor,const Row& key,bool use_replay=false)
      :runtime(owner),target(view),image(state),removed(restored),metrics(account),positions(owner.factors.size()),replay(use_replay) {
    note(metrics.anchor_cursors);
    const auto size=runtime.factors.size(); steps.reserve(size); frames.resize(size);
    if (replay) {
      inside.assign(size,false); std::vector<std::size_t> subtree; subtree.reserve(size); subtree.push_back(anchor);
      while (!subtree.empty()) {
        const auto factor=subtree.back(); subtree.pop_back(); note(metrics.anchor_steps); inside[factor]=true;
        for (const auto child : runtime.factors[factor].children) subtree.push_back(child);
      }
    }
    std::vector<Step> pending; pending.reserve(size); pending.push_back({anchor,{},anchor,false});
    while (!pending.empty()) {
      const auto step=pending.back(); pending.pop_back(); note(metrics.anchor_steps);
      const auto index=steps.size(); steps.push_back(step); positions[step.factor]=index;
      const auto previous=step.from?std::optional<std::size_t>{steps[*step.from].factor}:std::nullopt;
      const auto& factor=runtime.factors[step.factor];
      for (auto child=factor.children.rbegin();child!=factor.children.rend();++child)
        if (!previous || *child!=*previous) pending.push_back({*child,index,*child,false});
      if (factor.parent && (!previous || *factor.parent!=*previous))
        pending.push_back({*factor.parent,index,step.factor,true});
    }
    require(steps.size()==size,"runtime_contract","anchored program does not cover C*");
    note(metrics.anchor_fields,static_cast<std::uint64_t>(key.size()));
    frames[0].selected=layout(anchor).tuple(key); frames[0].opened=true;
    metrics.cursor_startup_work+=work;
    metrics.anchor_max_startup_work=std::max(metrics.anchor_max_startup_work,work);
  }
  std::optional<storage::Tuple> indexed_next(const Step& step,Frame& frame,bool child_side) {
    auto& lookups=child_side?metrics.anchor_child_lookups:metrics.anchor_parent_lookups;
    note(lookups);
    const auto& index=child_side?image.child_index[step.edge]:image.parents[step.edge];
    const auto current=index.find(*frame.separator);
    const Relation* first=current==index.end()?nullptr:&current->second.rows;
    const Relation* second=nullptr;
    if (removed && !child_side) {
      note(lookups);
      const auto old=(*removed)[step.edge].find(*frame.separator);
      if (old!=(*removed)[step.edge].end()) second=&old->second;
    }
    const Row* selected=nullptr;
    for (const auto* rows : {first,second}) if (rows) {
      note(lookups);
      const auto found=frame.selected?rows->upper_bound(frame.selected->values()):rows->begin();
      if (found!=rows->end() && (!selected || *found<*selected)) selected=&*found;
    }
    if (!selected) return {};
    note(child_side?metrics.anchor_child_rows:metrics.anchor_parent_rows);
    note(metrics.anchor_fields,static_cast<std::uint64_t>(selected->size()));
    return layout(step.factor).tuple(*selected);
  }
  std::optional<storage::Tuple> select(std::size_t index) {
    const auto& step=steps[index]; auto& frame=frames[index];
    const bool live_child=replay && !step.upward && !inside[step.factor];
    if (!frame.opened) {
      note(metrics.anchor_steps); frame.opened=true;
      const auto& edge=runtime.factors[step.edge];
      frame.separator=project(frames[*step.from].selected->values(),step.upward?edge.child_separator:edge.parent_separator);
      note(metrics.anchor_bucket_opens);
      if (!step.upward && !live_child) {
        frame.down.emplace(target.visible_bucket(runtime.factors[step.factor].node,*frame.separator,runtime.options.cursor));
        note(metrics.anchor_down_work,frame.down->metrics().startup.work);
      }
    }
    if (step.upward || live_child) return indexed_next(step,frame,live_child);
    auto result=frame.down->next(); note(metrics.anchor_down_work,frame.down->metrics().last.work);
    if (result) note(metrics.anchor_down_rows);
    return result;
  }
  std::optional<storage::Tuple> next() {
    if (finished) return {};
    const auto before=work;
    note(metrics.anchor_steps);
    if (resume) { position=steps.size()-1; resume=false; }
    while (position!=0) {
      if (position==steps.size()) {
        Row output; output.reserve(runtime.core_layout.fields().size());
        for (const auto slot : runtime.physical.plan().enumeration().output) {
          note(metrics.anchor_fields);
          output.push_back(frames[positions[slot.step]].selected->values().at(slot.field.value));
        }
        auto result=runtime.core_layout.tuple(std::move(output)); resume=true;
        metrics.cursor_results_work+=work-before;
        metrics.anchor_max_result_work=std::max(metrics.anchor_max_result_work,work-before); return result;
      }
      note(metrics.anchor_steps);
      const bool first=!frames[position].opened;
      auto row=select(position);
      require(!first || row.has_value(),"runtime_contract","live anchored factor has an empty first bucket");
      if (row) { frames[position].selected=std::move(row); ++position; }
      else { frames[position]=Frame{}; --position; }
    }
    note(metrics.anchor_steps,static_cast<std::uint64_t>(frames.size()));
    frames.clear(); finished=true; metrics.cursor_termination_work+=work-before;
    metrics.anchor_max_termination_work=std::max(metrics.anchor_max_termination_work,work-before); return {};
  }
};

struct DeltaRuntime::Epoch::Data {
  struct Spool {
    struct Node {
      SignedResult value;
      std::unique_ptr<Node> next;
      explicit Node(SignedResult row) noexcept:value(std::move(row)) {}
    };
    std::unique_ptr<Node> head;
    Node* tail=nullptr;
    std::size_t count=0;
    ~Spool() { clear(); }
    [[nodiscard]] std::size_t size() const noexcept { return count; }
    [[nodiscard]] bool empty() const noexcept { return count==0; }
    SignedResult& front() noexcept { return head->value; }
    void push_back(SignedResult value) {
      auto node=std::make_unique<Node>(std::move(value)); auto* last=node.get();
      if (tail) tail->next=std::move(node); else head=std::move(node);
      tail=last; ++count;
    }
    void pop_front() noexcept {
      auto node=std::move(head); head=std::move(node->next); --count;
      if (!head) tail=nullptr;
    }
    void clear() noexcept { while (head) pop_front(); }
  };
  std::shared_ptr<Impl> owner;
  std::shared_ptr<detail::ObservationState> observation;
  std::optional<PhysicalEpoch> input;
  storage::TupleLayout layout;
  DeltaMetrics metrics;
  DeltaTimings timings;
  Spool rows;
  std::vector<DeltaStage> stages;
  std::size_t payload_bytes=0;
  bool leased=false;
  bool retain_output=true, delivering=false, discard_requested=false;
  detail::ObservationTicket observation_ticket;
  OutputDisposition disposition;
  bool observation_closed=false;
  void observe_output() noexcept {
    if (observation && !observation_closed) observation->output(observation_ticket,disposition);
  }
  explicit Data(std::shared_ptr<Impl> runtime):owner(std::move(runtime)),observation(owner->observation),layout(owner->output_layout) {
    stages.reserve(owner->physical.plan().inputs().size());
  }
  ~Data() { finish(); }
  void observe() const noexcept {
    if (!observation) return;
    observation->set(MetricId::delta_work,metrics.work);
    observation->set(MetricId::delta_candidates,metrics.candidates);
    observation->set(MetricId::delta_accepted,metrics.accepted);
    observation->set(MetricId::delta_rejected,metrics.rejected);
    observation->set(MetricId::delta_replay_preparation_work,metrics.replay_preparation_work);
    observation->set(MetricId::delta_replay_first_work,metrics.replay_first_work);
    observation->set(MetricId::delta_replay_results_work,metrics.replay_results_work);
    observation->set(MetricId::delta_replay_termination_work,metrics.replay_termination_work);
    observation->set(MetricId::delta_finalization_work,metrics.finalization_work);
    observation->set(MetricId::delta_propagation_ns,timings.propagation_ns);
    observation->set(MetricId::delta_internal_delta_ns,timings.internal_delta_ns);
    observation->set(MetricId::delta_output_mapping_ns,timings.output_mapping_ns);
    observation->set(MetricId::delta_serialization_ns,timings.serialization_ns);
    observation->set(MetricId::delta_sink_wait_ns,timings.sink_wait_ns);
    observation->set(MetricId::delta_spool_rows_prepared,metrics.spool_rows);
    observation->set(MetricId::delta_spool_bytes_prepared,metrics.spool_bytes);
  }

  void finish() noexcept {
    if (delivering) { discard_requested=true; return; }
    if (observation && !observation_closed) {
      disposition.unread_discarded=disposition.unread_discarded || !rows.empty();
      disposition.released=true; observe_output(); observation_closed=true;
    }
    if (leased) {
      if (!owner || !owner->output_active) std::terminate();
      owner->output_active=false; leased=false;
    }
    if (observation && !rows.empty()) {
      observation->add(MetricId::delta_discarded_records,static_cast<std::uint64_t>(rows.size()));
      observation->event(TraceKind::discarded,0,0,observation_no_id,observation_no_id,0,
          static_cast<std::uint64_t>(rows.size()),0);
    }
    owner.reset(); rows.clear();
  }
  void append(SetOperation operation,storage::Tuple tuple) {
    if (observation) {
      observation->add(MetricId::delta_mapped_records);
      observation->event(TraceKind::mapped_record);
    }
    if (!retain_output) {
      owner->metric(metrics,metrics.discarded_records);
      if (observation) observation->add(MetricId::delta_discarded_records);
      return;
    }
    const auto& options=owner->options;
    require(rows.size()<options.spool_row_limit && rows.size()<std::numeric_limits<std::uint64_t>::max(),
        "resource_limit","unpublished delta spool row limit exceeded; previous input preserved");
    std::size_t payload=slots_size(tuple.values().capacity(),sizeof(Value));
    for (const auto& value : tuple.values()) {
      if (const auto* text=std::get_if<std::string>(&value)) payload=add_size(payload,add_size(text->capacity(),1));
      // Decimal coefficients are bounded to 38 digits. This fixed allowance
      // covers the coefficient payload separately from its inline Value slot.
      else if (std::holds_alternative<Decimal>(value)) payload=add_size(payload,64);
    }
    const auto next_payload=add_size(payload_bytes,payload);
    require(next_payload<=options.spool_byte_limit,"resource_limit","unpublished delta spool payload limit exceeded");
    const auto next_count=add_size(rows.size(),1);
    const auto bytes=add_size(slots_size(next_count,sizeof(Spool::Node)),next_payload);
    require(bytes<=options.spool_byte_limit,"resource_limit","unpublished delta spool byte limit exceeded; previous input preserved");
    owner->charge(metrics);
    rows.push_back({static_cast<std::uint64_t>(rows.size())+1,operation,std::move(tuple)});
    payload_bytes=next_payload; metrics.spool_rows=rows.size(); metrics.spool_bytes=bytes; metrics.spool_capacity_rows=rows.size();
  }
  void disable_output() {
    if (observation) { disposition.discard_drain_requested=true; observe_output(); }
    if (!retain_output) return;
    const auto start=metrics.work;
    owner->metric(metrics,metrics.discarded_records,static_cast<std::uint64_t>(rows.size()));
    owner->charge(metrics,static_cast<std::uint64_t>(stages.size()));
    if (observation) {
      observation->add(MetricId::delta_discarded_records,static_cast<std::uint64_t>(rows.size()));
      observation->event(TraceKind::drain);
    }
    if (observation) {
      disposition.retention_disabled=true;
      disposition.unread_discarded=disposition.unread_discarded || !rows.empty(); observe_output();
    }
    retain_output=false; rows.clear(); payload_bytes=0;
    for (auto& stage : stages) { stage.output_begin=0; stage.output_count=0; }
    metrics.finalization_work+=metrics.work-start;
  }
};

// A heap-stable route owns its endpoint views and cursor across pause/resume.
// Its changed-key sets are consolidated before the physical driver can advance.
struct DeltaRuntime::Impl::Stage {
  const Impl& runtime;
  Epoch::Data& output;
  std::shared_ptr<LiveImage>& working;
  LiveTransaction* transaction;
  SupportRuntime::EpochView before, after;
  const SupportRuntime::EpochView& target;
  SetOperation operation;
  OccurrenceId occurrence;
  std::uint64_t prefix;
  DeltaMetrics prior;
  std::size_t output_begin;
  std::vector<Relation> changed, removed;
  std::shared_ptr<LiveImage> next_image;
  const LiveImage* eligible=nullptr;
  std::optional<ProductiveQueue> productive;
  Relation::node_type witness;
  std::unique_ptr<AnchoredCursor> anchored;
  std::optional<SupportRuntime::ResultCursor> root;
  std::optional<Relation::const_iterator> key;
  std::size_t ordinal=0, rank=0;
  std::uint64_t transition_begin=0;
  bool replay=false, on_output=false, entered=false, produced=false, emitted=false, finished=false;

  Stage(const Impl& owner,Epoch::Data& result,std::shared_ptr<LiveImage>& state,LiveTransaction* live,
      const SupportRuntime::EpochView& old_view,const SupportRuntime::EpochView& new_view,
      std::span<const JournalRecord> records,SetOperation sign,OccurrenceId route,std::uint64_t position)
      :runtime(owner),output(result),working(state),transaction(live),before(old_view),after(new_view),
       target(sign==SetOperation::insert?after:before),operation(sign),occurrence(route),prefix(position),
       prior(result.metrics),output_begin(result.rows.size()),changed(owner.factors.size()),
       removed(live?owner.factors.size():0),replay(owner.selected_completion==DeltaCompletion::ordered_replay),
       on_output(live && owner.options.live_maintenance==LiveMaintenance::on_output) {
    auto& metrics=output.metrics; const auto preparation_begin=metrics.work;
    runtime.metric(metrics,metrics.stages); runtime.metric(metrics,metrics.view_work,before.metrics().work);
    for (const auto& record : records) {
      runtime.metric(metrics,metrics.journal_records);
      if (record.handle.role!=SupportRole::visible || record.before.member==record.after.member) continue;
      require(record.after.member==(operation==SetOperation::insert),"runtime_contract","E membership contradicts the occurrence polarity");
      const auto factor=runtime.ranks.at(record.handle.node.value);
      require(factor.has_value(),"runtime_contract","E change belongs to a factor outside C*");
      if (changed[*factor].insert(record.tuple().values()).second) runtime.metric(metrics,metrics.changed_keys);
    }
    if (replay) {
      require(transaction!=nullptr,"runtime_contract","ordered replay has no live transaction");
      transaction->begin_stage(); productive.emplace(runtime.factors.size());
      for (std::size_t i=0;i<runtime.factors.size();++i) {
        runtime.metric(metrics,metrics.replay_factor_steps);
        for (const auto& row : changed[i]) {
          runtime.metric(metrics,metrics.replay_witness_tests); bool live_key=true;
          if (operation==SetOperation::insert && runtime.factors[i].parent) {
            const auto separator=runtime.project(row,runtime.factors[i].child_separator,metrics,metrics.separator_fields);
            runtime.metric(metrics,metrics.live_probes); live_key=transaction->image->parents[i].contains(separator);
          } else if (operation==SetOperation::erase) {
            runtime.metric(metrics,metrics.live_probes); live_key=transaction->image->factors[i].contains(row);
          }
          if (!live_key) { runtime.metric(metrics,metrics.dead_witnesses); continue; }
          const auto size=add_size(productive->rows,1);
          runtime.metric(metrics,metrics.replay_queue_inserts);
          runtime.metric(metrics,metrics.replay_queue_fields,static_cast<std::uint64_t>(row.size()));
          require(productive->factors[i].insert(row).second,"runtime_contract","productive queue duplicated a key");
          productive->rows=size; metrics.replay_queue_peak=std::max(metrics.replay_queue_peak,size);
        }
      }
      metrics.replay_preparation_work+=metrics.work-preparation_begin;
      transition_begin=metrics.work; runtime.metric(metrics,metrics.replay_factor_steps);
      eligible=transaction->image.get(); return;
    }
    if (on_output) { transaction->begin_stage(); next_image=working; }
    else if (transaction) { transaction->apply(changed,target,operation==SetOperation::insert,removed); next_image=working; }
    else {
      const bool separate=runtime.live.get()!=working.get();
      next_image=runtime.build_live(after,metrics,add_size(working->rows,separate?runtime.live->rows:0),
          add_size(working->parent_rows,separate?runtime.live->parent_rows:0),
          add_size(working->child_rows,separate?runtime.live->child_rows:0));
    }
    eligible=(operation==SetOperation::insert || transaction)?next_image.get():working.get();
  }
  // Lifecycle-only cleanup is finalization, not producer work. Keep its
  // separately charged cost out of the next/last transition interval.
  void exclude_work(std::uint64_t amount) noexcept { if (replay) transition_begin+=amount; }
  bool open() {
    auto& metrics=output.metrics;
    while (ordinal<runtime.factors.size()) {
      rank=replay && operation==SetOperation::insert?runtime.factors.size()-ordinal-1:ordinal;
      if (!entered) {
        entered=true;
        if (replay) runtime.metric(metrics,metrics.replay_factor_steps);
        else key=changed[rank].begin();
      }
      const Row* row=nullptr;
      if (replay) {
        auto& queue=productive->factors[rank];
        if (queue.empty()) { ++ordinal; entered=false; continue; }
        runtime.metric(metrics,metrics.replay_queue_pops);
        require(productive->rows!=0,"runtime_contract","productive queue underflow");
        witness=queue.extract(queue.begin()); --productive->rows; row=&witness.value();
        runtime.metric(metrics,metrics.live_witnesses);
        if (operation==SetOperation::erase) {
          runtime.metric(metrics,metrics.live_probes);
          require(transaction->image->factors[rank].contains(*row),"runtime_contract","productive deletion queue contains a dead key");
        }
      } else {
        if (*key==changed[rank].end()) { ++ordinal; entered=false; continue; }
        row=&**key; ++*key;
        bool live_key=false;
        if (on_output && operation==SetOperation::insert) {
          live_key=true;
          if (runtime.factors[rank].parent) {
            const auto separator=runtime.project(*row,runtime.factors[rank].child_separator,metrics,metrics.separator_fields);
            runtime.metric(metrics,metrics.live_probes); live_key=working->parents[rank].contains(separator);
          }
        } else live_key=eligible->factors[rank].contains(*row) ||
            (transaction && operation==SetOperation::erase && removed[rank].contains(*row));
        if (!live_key) { runtime.metric(metrics,metrics.dead_witnesses); continue; }
        runtime.metric(metrics,metrics.live_witnesses);
      }
      produced=false;
      if (runtime.selected_completion!=DeltaCompletion::root_first) {
        const auto* restored=!replay && transaction && operation==SetOperation::erase?&transaction->removed_parents:nullptr;
        anchored=std::make_unique<AnchoredCursor>(runtime,target,*eligible,restored,metrics,rank,*row,replay);
      } else {
        FixedAssignment fixed; fixed.reserve(row->size());
        for (std::size_t field=0;field<row->size();++field) {
          runtime.metric(metrics,metrics.binding_fields); fixed.push_back({runtime.factors[rank].scope[field],(*row)[field]});
        }
        root.emplace(target.completions(fixed,{},runtime.options.cursor)); runtime.cursor_start(*root,metrics);
      }
      return true;
    }
    return false;
  }
  bool next() {
    if (finished) return false;
    auto& metrics=output.metrics;
    for (;;) {
      if (!anchored && !root && !open()) { finish(); return false; }
      auto row=anchored?anchored->next():runtime.cursor_next(*root,metrics);
      if (!row) {
        anchored.reset(); root.reset();
        if (replay) {
          require(produced,"runtime_contract","productive witness emitted no replay answer");
          runtime.metric(metrics,metrics.replay_queue_releases); witness=Relation::node_type{};
        }
        continue;
      }
      produced=true; runtime.metric(metrics,metrics.candidates); bool earlier=false;
      if (!replay) for (std::size_t k=0;k<rank;++k) {
        runtime.metric(metrics,metrics.earlier_probes);
        if (changed[k].contains(runtime.project(row->values(),runtime.factors[k].head_fields,metrics,metrics.projection_fields))) { earlier=true; break; }
      }
      if (earlier) { runtime.metric(metrics,metrics.rejected); continue; }
      runtime.metric(metrics,metrics.accepted);
      if (output.observation) output.observation->event(TraceKind::core_result,
          metrics.accepted,0,runtime.factors[rank].node.value,occurrence.value,prefix);
      if (on_output) transaction->on_output(row->values(),changed,operation==SetOperation::insert,removed,
          replay?std::optional<std::size_t>{rank}:std::nullopt,replay?&*productive:nullptr);
      if (!runtime.scalar_sql()) {
        PhaseTimer timing(output.timings.output_mapping_ns,output.observation);
        output.append(operation,runtime.map_result(std::move(*row),metrics));
      }
      if (replay) {
        const auto amount=metrics.work-transition_begin;
        if (!emitted) {
          metrics.replay_first_work+=amount; metrics.replay_max_first_work=std::max(metrics.replay_max_first_work,amount); emitted=true;
        } else {
          metrics.replay_results_work+=amount; metrics.replay_max_next_work=std::max(metrics.replay_max_next_work,amount);
        }
        transition_begin=metrics.work;
      }
      return true;
    }
  }
  void finish() {
    auto& metrics=output.metrics;
    if (transaction) transaction->end_stage();
    if (replay) {
      require(productive->rows==0,"runtime_contract","productive queue did not drain");
      const auto tail=metrics.work-transition_begin;
      metrics.replay_termination_work+=tail; metrics.replay_max_last_work=std::max(metrics.replay_max_last_work,tail);
      const auto start=metrics.work;
      for (auto& keys : changed) { runtime.metric(metrics,metrics.finalization_changed_keys,static_cast<std::uint64_t>(keys.size())); keys.clear(); }
      const auto& view=before.metrics();
      for (const auto count : {view.restored_rows,view.excluded_rows,view.restored_key_entries,
          view.restored_bucket_entries,view.restored_bucket_entries,view.key_fields})
        runtime.metric(metrics,metrics.finalization_view_entry_bound,count);
      for (unsigned copy=0;copy<4;++copy)
        runtime.metric(metrics,metrics.finalization_view_entry_bound,static_cast<std::uint64_t>(runtime.physical.plan().relations().size()));
      runtime.metric(metrics,metrics.finalization_view_entry_bound,static_cast<std::uint64_t>(runtime.physical.plan().indexes().size()));
      metrics.finalization_work+=metrics.work-start;
    } else {
      if (!transaction && working.get()!=runtime.live.get()) {
        const auto start=metrics.work;
        runtime.metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(working->rows));
        runtime.metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(working->parent_rows));
        runtime.metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(working->child_rows));
        metrics.finalization_work+=metrics.work-start;
      }
      working=std::move(next_image);
    }
    metrics.live_rows=working->rows; metrics.parent_index_rows=working->parent_rows; metrics.child_index_rows=working->child_rows;
    const auto begin=output.retain_output?output_begin:0;
    output.stages.push_back({occurrence,prefix,before.has_answer(),after.has_answer(),
        metrics.changed_keys-prior.changed_keys,metrics.candidates-prior.candidates,metrics.accepted-prior.accepted,
        metrics.rejected-prior.rejected,begin,output.retain_output?output.rows.size()-begin:0,working->rows});
    finished=true;
  }
};

struct DeltaRuntime::PendingEpoch::Data {
  std::shared_ptr<Impl> owner;
  std::shared_ptr<Epoch::Data> output;
  std::shared_ptr<Impl::LiveImage> working;
  std::optional<Impl::LiveTransaction> transaction;
  std::optional<PhysicalRuntime::PendingUpdate> physical;
  std::unique_ptr<Impl::Stage> stage;
  std::uint64_t sequence;
  SetOperation operation;
  bool before_answer;
  DeltaState phase=DeltaState::pending_delta;
  detail::ObservationTicket observation_ticket;

  Data(std::shared_ptr<Impl> runtime,const PhysicalSetUpdate& update)
      :owner(std::move(runtime)),output(std::make_shared<Epoch::Data>(owner)),working(owner->live),
       sequence(update.sequence),operation(update.operation),before_answer(owner->physical.has_answer()) {
    if (owner->mode==DeltaMode::delta && owner->options.live_maintenance!=LiveMaintenance::eager)
      transaction.emplace(*owner,output->metrics,working);
    if (output->observation) {
      observation_ticket=output->observation->begin(ObservationLayer::delta,sequence);
      output->observation_ticket=observation_ticket;
    }
    owner->processing=true; owner->lifecycle=phase;
    try {
      PhaseTimer timing(output->timings.propagation_ns,output->observation,&output->timings.internal_delta_ns);
      physical.emplace(owner->physical.begin_staged(update));
    }
    catch (...) { rollback(); throw; }
    output->observe();
  }
  ~Data() { rollback(); }
  bool active() const noexcept { return owner && physical && physical->active(); }
  void validate() const { require(active(),"invalid_delta_epoch","pending delta epoch is closed"); }
  void set_phase(DeltaState value) noexcept { phase=value; owner->lifecycle=value; }
  void rollback() noexcept {
    if (!owner) return;
    // Cursors and endpoint leases must close before the physical undo and
    // before restoration of independently journaled live/index nodes.
    { PhaseTimer timing(output->timings.internal_delta_ns,output->observation); stage.reset(); }
    { PhaseTimer timing(output->timings.propagation_ns,output->observation); if (physical) physical->rollback(); }
    {
      PhaseTimer timing(output->timings.internal_delta_ns,output->observation);
      if (transaction) transaction->rollback();
      physical.reset(); transaction.reset(); working.reset();
      output->finish(); owner->processing=false; owner->lifecycle=DeltaState::ready;
    }
    output->observe();
    if (output->observation) output->observation->finish(observation_ticket,ObservationOutcome::aborted);
    phase=DeltaState::aborted; owner.reset();
  }
  void finalize() {
    auto& metrics=output->metrics;
    if (owner->mode==DeltaMode::delta) {
      if (owner->scalar_sql() && before_answer!=physical->support().has_answer) {
        PhaseTimer timing(output->timings.output_mapping_ns,output->observation);
        owner->metric(metrics,metrics.output_fields,2);
        output->append(SetOperation::erase,owner->output_layout.tuple({Value{before_answer}}));
        output->append(SetOperation::insert,owner->output_layout.tuple({Value{!before_answer}}));
      }
      metrics.live_rows=working->rows; metrics.peak_live_rows=std::max(metrics.peak_live_rows,working->rows);
      metrics.parent_index_rows=working->parent_rows;
      metrics.peak_parent_index_rows=std::max(metrics.peak_parent_index_rows,working->parent_rows);
      metrics.child_index_rows=working->child_rows;
      metrics.peak_child_index_rows=std::max(metrics.peak_child_index_rows,working->child_rows);
      const auto start=metrics.work;
      const auto& support=physical->support();
      if (support.journal) owner->metric(metrics,metrics.finalization_kernel_record_bound,
          static_cast<std::uint64_t>(support.journal->records.size()));
      const auto& preview=physical->preview();
      owner->metric(metrics,metrics.finalization_driver_changes,static_cast<std::uint64_t>(preview.derivations.size()));
      if (preview.source) owner->metric(metrics,metrics.finalization_driver_changes);
      if (transaction) transaction->prepare_commit();
      else if (working.get()!=owner->live.get()) {
        owner->metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(owner->live->rows));
        owner->metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(owner->live->parent_rows));
        owner->metric(metrics,metrics.finalization_image_rows,static_cast<std::uint64_t>(owner->live->child_rows));
      }
      metrics.finalization_work+=metrics.work-start;
    }
    set_phase(DeltaState::epoch_prepared);
    if (output->observation) {
      output->disposition.prepared=true; output->observe_output();
      output->observation->event(TraceKind::prepared);
    }
  }
  DeltaStep step() {
    if (stage) {
      PhaseTimer timing(output->timings.internal_delta_ns,output->observation,&output->timings.output_mapping_ns);
      if (stage->next()) return DeltaStep::core_result;
      stage.reset(); return DeltaStep::progress;
    }
    const auto observer=[this](OccurrenceId occurrence,std::uint64_t prefix,const auto& before,const auto& after,
        std::span<const JournalRecord> records) {
      if (owner->mode==DeltaMode::delta) {
        PhaseTimer timing(output->timings.internal_delta_ns,output->observation);
        stage=std::make_unique<Impl::Stage>(*owner,*output,working,transaction?&*transaction:nullptr,
            before,after,records,operation,occurrence,prefix);
      }
    };
    {
      PhaseTimer timing(output->timings.propagation_ns,output->observation,&output->timings.internal_delta_ns);
      if (physical->stage_next(observer,owner->options.epoch_view)) return DeltaStep::progress;
    }
    PhaseTimer timing(output->timings.internal_delta_ns,output->observation,&output->timings.output_mapping_ns);
    finalize(); return DeltaStep::prepared;
  }
};

DeltaRuntime::PendingEpoch::PendingEpoch(std::unique_ptr<Data> data) noexcept:data_(std::move(data)) {}
DeltaRuntime::PendingEpoch::PendingEpoch(PendingEpoch&&) noexcept=default;
DeltaRuntime::PendingEpoch& DeltaRuntime::PendingEpoch::operator=(PendingEpoch&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
DeltaRuntime::PendingEpoch::~PendingEpoch()=default;
bool DeltaRuntime::PendingEpoch::active() const noexcept { return data_ && data_->active(); }
DeltaState DeltaRuntime::PendingEpoch::state() const noexcept { return data_?data_->phase:DeltaState::aborted; }
std::uint64_t DeltaRuntime::PendingEpoch::sequence() const {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); return data_->sequence;
}
const DeltaMetrics& DeltaRuntime::PendingEpoch::metrics() const {
  require(data_ && data_->output,"invalid_delta_epoch","pending delta output is closed"); return data_->output->metrics;
}
const DeltaTimings& DeltaRuntime::PendingEpoch::timings() const {
  require(data_ && data_->output,"invalid_delta_epoch","pending delta output is closed"); return data_->output->timings;
}
std::span<const DeltaStage> DeltaRuntime::PendingEpoch::stages() const {
  require(data_ && data_->output,"invalid_delta_epoch","pending delta output is closed"); return data_->output->stages;
}
DeltaStep DeltaRuntime::PendingEpoch::step() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  require(data_->phase!=DeltaState::paused,"delta_paused","resume the paused delta epoch before stepping");
  if (data_->phase==DeltaState::epoch_prepared) return DeltaStep::prepared;
  try { const auto result=data_->step(); data_->output->observe(); return result; }
  catch (...) { data_->rollback(); throw; }
}
void DeltaRuntime::PendingEpoch::pause() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  require(data_->phase==DeltaState::pending_delta,"invalid_delta_state","only pending delta production can pause");
  data_->set_phase(DeltaState::paused);
}
void DeltaRuntime::PendingEpoch::resume() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  require(data_->phase==DeltaState::paused,"invalid_delta_state","delta epoch is not paused");
  data_->set_phase(DeltaState::pending_delta);
}
void DeltaRuntime::PendingEpoch::start_drain() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  try {
    PhaseTimer timing(data_->output->timings.internal_delta_ns,data_->output->observation);
    const auto start=data_->output->metrics.work;
    data_->output->disable_output();
    if (data_->stage) data_->stage->exclude_work(data_->output->metrics.work-start);
    if (data_->phase!=DeltaState::epoch_prepared) data_->set_phase(DeltaState::draining);
  } catch (...) { data_->rollback(); throw; }
  data_->output->observe();
}
void DeltaRuntime::PendingEpoch::drain() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  if (data_->output->observation) {
    data_->output->disposition.completion_drain_invoked=true; data_->output->observe_output();
  }
  if (data_->phase==DeltaState::paused) data_->set_phase(DeltaState::pending_delta);
  while (step()!=DeltaStep::prepared) {}
}
DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::commit() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  require(data_->phase==DeltaState::epoch_prepared,"runtime_busy","delta work is not fully drained");
  auto& d=*data_->owner;
  // Every allocation, quota check, cursor close and cleanup precharge finished
  // before this barrier. Both logical and live undo commits are nonallocating.
  static_assert(std::is_nothrow_move_constructible_v<PhysicalEpoch>);
  static_assert(std::is_nothrow_move_constructible_v<SignedResult>);
  {
    PhaseTimer timing(data_->output->timings.propagation_ns,data_->output->observation);
    data_->output->input.emplace(data_->physical->commit());
  }
  if (data_->transaction) {
    PhaseTimer timing(data_->output->timings.internal_delta_ns,data_->output->observation);
    data_->transaction->commit();
  }
  {
    PhaseTimer timing(data_->output->timings.internal_delta_ns,data_->output->observation);
    if (d.mode==DeltaMode::delta) { d.live=std::move(data_->working); d.live_sequence=data_->sequence; }
  }
  data_->output->observe();
  if (data_->output->observation) {
    data_->output->disposition.published=true;
    data_->output->disposition.released=data_->output->rows.empty();
    data_->output->observe_output();
    if (data_->output->rows.empty()) data_->output->observation_closed=true;
  }
  if (data_->output->observation)
    data_->output->observation->finish(data_->observation_ticket,ObservationOutcome::committed);
  auto output=std::move(data_->output);
  output->leased=!output->rows.empty(); d.output_active=output->leased; d.processing=false; d.lifecycle=DeltaState::ready;
  data_->physical.reset(); data_->transaction.reset(); data_->phase=DeltaState::committed; data_->owner.reset();
  if (!output->leased) output->owner.reset();
  return Epoch(std::move(output));
}
DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::discard() { start_drain(); drain(); return commit(); }
void DeltaRuntime::PendingEpoch::rollback() noexcept { if (data_) data_->rollback(); }

DeltaRuntime::Epoch::Epoch(std::shared_ptr<Data> data) noexcept:data_(std::move(data)) {}
DeltaRuntime::Epoch::Epoch(Epoch&&) noexcept=default;
DeltaRuntime::Epoch& DeltaRuntime::Epoch::operator=(Epoch&& other) noexcept {
  if (this!=&other) data_=std::move(other.data_);
  return *this;
}
DeltaRuntime::Epoch::~Epoch()=default;
bool DeltaRuntime::Epoch::active() const noexcept { return data_ && data_->leased; }
std::uint64_t DeltaRuntime::Epoch::sequence() const { return input().input.sequence; }
const PhysicalEpoch& DeltaRuntime::Epoch::input() const {
  require(data_ && data_->input,"invalid_delta_epoch","moved-from delta epoch"); return *data_->input;
}
const DeltaMetrics& DeltaRuntime::Epoch::metrics() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->metrics; }
const DeltaTimings& DeltaRuntime::Epoch::timings() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->timings; }
std::span<const DeltaStage> DeltaRuntime::Epoch::stages() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->stages; }
const storage::TupleLayout& DeltaRuntime::Epoch::layout() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->layout; }
std::size_t DeltaRuntime::Epoch::remaining() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->rows.size(); }
std::optional<SignedResult> DeltaRuntime::Epoch::next() {
  require(bool(data_),"invalid_delta_epoch","moved-from delta epoch");
  require(!data_->delivering,"runtime_busy","a sink callback owns the current output row");
  if (data_->rows.empty()) return {};
  std::optional<SignedResult> result{std::move(data_->rows.front())}; data_->rows.pop_front();
  if (data_->observation) {
    data_->disposition.transferred=true; data_->observe_output();
    data_->observation->add(MetricId::delta_transferred_records);
    data_->observation->event(TraceKind::transferred,result->ordinal);
  }
  if (data_->rows.empty()) data_->finish();
  return result;
}
bool DeltaRuntime::Epoch::deliver_one(const std::function<void(const SignedResult&)>& sink) {
  return deliver_one({},sink);
}
bool DeltaRuntime::Epoch::deliver_one(const std::function<void(const SignedResult&)>& serialize,
    const std::function<void(const SignedResult&)>& sink) {
  require(bool(data_),"invalid_delta_epoch","moved-from delta epoch");
  const auto data=data_;  // Keeps the borrowed row alive across facade moves.
  require(!data->delivering,"runtime_busy","a sink callback owns the current output row");
  if (data->rows.empty()) return false;
  data->delivering=true;
  bool serializing=false;
  try {
    if (serialize) {
      serializing=true;
      if (data->observation) {
        data->disposition.serialization_invoked=true; data->observe_output();
        data->observation->add(MetricId::delta_serialization_attempts);
        data->observation->event(TraceKind::serialization_attempt,data->rows.front().ordinal);
      }
      { PhaseTimer timing(data->timings.serialization_ns,data->observation); serialize(data->rows.front()); }
      if (data->observation) {
        data->observation->add(MetricId::delta_serialization_successes);
        data->observation->event(TraceKind::serialization_success,data->rows.front().ordinal);
      }
    }
    serializing=false;
    if (data->observation) {
      data->disposition.sink_invoked=true; data->observe_output();
      data->observation->add(MetricId::delta_sink_attempts);
      data->observation->event(TraceKind::sink_attempt,data->rows.front().ordinal);
    }
    { PhaseTimer timing(data->timings.sink_wait_ns,data->observation); sink(data->rows.front()); }
    if (data->observation) {
      data->observation->add(MetricId::delta_sink_successes);
      data->observation->event(TraceKind::sink_success,data->rows.front().ordinal);
    }
  }
  catch (...) {
    if (data->observation) {
      data->observation->add(serializing?MetricId::delta_serialization_failures:MetricId::delta_sink_failures);
      data->observation->event(serializing?TraceKind::serialization_failure:TraceKind::sink_failure,data->rows.front().ordinal);
    }
    data->observe(); data->delivering=false;
    if (data->discard_requested) data->finish();
    throw;
  }
  data->observe(); data->delivering=false;
  if (data->discard_requested) data->finish();
  else {
    if (data->observation) {
      data->observation->add(MetricId::delta_acknowledged_records);
      data->observation->event(TraceKind::acknowledged,data->rows.front().ordinal);
    }
    data->rows.pop_front(); if (data->rows.empty()) data->finish();
  }
  return true;
}
void DeltaRuntime::Epoch::discard() noexcept { if (data_) data_->finish(); }

DeltaRuntime::DeltaRuntime(PhysicalPlan plan,DeltaOptions options):impl_(std::make_shared<Impl>(std::move(plan),options)) {
  if (options.mode==DeltaMode::delta) static_cast<void>(set_mode(DeltaMode::delta));
  impl_->observe_configuration(true);
}
DeltaRuntime::DeltaRuntime(PhysicalRuntime physical,DeltaOptions options,BuildOptions build)
    :impl_(std::make_shared<Impl>(std::move(physical),options)) {
  auto& d=*impl_; d.initialization=d.physical.initialization_metrics();
  detail::build_charge(d.initialization,build,0);
  if (options.mode==DeltaMode::delta) {
    // Only this unpublished owner uses build limits. Ordinary updates retain
    // exactly the caller's options after bootstrap.
    const auto remaining=build.work_limit?
        std::optional<std::uint64_t>{*build.work_limit-d.initialization.work}:std::nullopt;
    d.options.work_limit=remaining; d.options.cursor.work_limit=remaining;
    d.options.epoch_view.work_limit=remaining;
    static_cast<void>(set_mode(DeltaMode::delta));
    d.options=options;
    detail::build_metric(d.initialization,build,d.initialization.live_bootstrap_work,d.bootstrap.work);
    d.initialization.live_rows=d.live->rows;
    d.initialization.live_parent_rows=d.live->parent_rows;
    d.initialization.live_child_rows=d.live->child_rows;
  }
  d.observe_configuration(true);
}
DeltaRuntime DeltaRuntime::initialize(PhysicalPlan plan,const Database& database,DeltaOptions options,BuildOptions build) {
  return DeltaRuntime(PhysicalRuntime::initialize(std::move(plan),database,options.physical,build),options,build);
}
DeltaRuntime DeltaRuntime::rebuilt(BuildOptions build) const {
  const auto& d=impl(); d.writable();
  auto options=d.options; options.mode=d.mode;
  auto result=DeltaRuntime(d.physical.rebuilt(build),options,build);
  result.impl().options=d.options;
  result.declare_benchmark_context(d.declared_benchmark);
  result.impl().observe_configuration(true); // New owner; restore requested initial options.
  return result;
}
InitializationContext DeltaRuntime::initialization_context() const { return impl().physical.initialization_context(); }
const BuildMetrics& DeltaRuntime::initialization_metrics() const { return impl().initialization; }
DeltaRuntime::~DeltaRuntime()=default;
DeltaRuntime::DeltaRuntime(DeltaRuntime&&) noexcept=default;
DeltaRuntime& DeltaRuntime::operator=(DeltaRuntime&& other) noexcept { if (this!=&other) impl_=std::move(other.impl_); return *this; }
DeltaRuntime::Impl& DeltaRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from delta runtime"); return *impl_; }
const PhysicalPlan& DeltaRuntime::plan() const { return impl().physical.plan(); }
const DeltaOptions& DeltaRuntime::options() const { return impl().options; }
DeltaCompletion DeltaRuntime::completion() const { return impl().selected_completion; }
DeltaRuntimeProfile DeltaRuntime::profile() const {
  const auto& d=impl(); DeltaRuntimeProfile result;
  result.mode=d.mode; result.live_maintenance=d.options.live_maintenance; result.completion=d.selected_completion;
  result.view=d.options.view; result.query_factors=d.factors.size();
  result.spool_row_limit=d.options.spool_row_limit; result.spool_byte_limit=d.options.spool_byte_limit;
  result.maintenance_bound="physical routing/support/constraints are reported separately; constraint validation may scan/copy DB; no uniform O(1) update bound";
  result.finalization_bound="O_Q(1+M+K+J+U+V) keys/patches/undo plus unread spool and final-owner state teardown; widths/allocator/arena high-water costs additional";
  result.public_startup_bound="complete physical epoch maintenance, all route preparation/production, SQL mapping, spool and finalization; no constant public startup";
  if (d.mode==DeltaMode::maintenance) {
    result.state_bound="physical/support state and caller-retained journals; no L, live indexes or delta enumeration";
    result.preparation_bound="physical maintenance only";
    result.candidate_bound="delta production disabled"; result.accepted_bound="delta production disabled";
    result.public_startup_bound="no delta records are produced in maintenance mode";
    return result;
  }
  result.publication=DeltaPublication::eager_atomic_spool;
  result.state_bound="fixed-query local source/S/P/E/L and live-parent/child indexes; O_Q(M+K+J+U+V) affected retention plus configured spool; caller pins and allocator/arena high-water storage separate";
  if (d.selected_completion!=DeltaCompletion::root_first) {
    result.candidate_transitions=DeltaBound::bounded_indexed_actions;
    result.candidate_bound="fixed-query bounded candidate actions; descriptor suffix may inspect O(m^2) compiled steps; row widths and ordered costs additional";
  } else result.candidate_bound="root-first partial binding may scan unrelated E rows; no bounded candidate transition claim";
  if (d.selected_completion==DeltaCompletion::ordered_replay) {
    result.accepted_transitions=DeltaBound::bounded_indexed_actions;
    result.preparation_bound="per route O_Q(1+M+K) indexed preparation; includes journal/view and productive witness discovery; no full L rebuild";
    result.accepted_bound="per route bounded post-preparation first/next/last successful core-result actions, including L/P/B, queues, mapping and one spool node; finalization separate";
  } else {
    result.preparation_bound=d.options.live_maintenance==LiveMaintenance::eager?
        "per route journal/view/discovery plus full E and parent-L rebuild scans":
        d.options.live_maintenance==LiveMaintenance::incremental?
        "per route journal/view/discovery plus all affected live/bucket draining before candidates":
        "per route journal/view and changed-key discovery; live changes coupled to accepted rows";
    result.accepted_bound="canonical ownership may reject long candidate runs; no bounded accepted-output transition claim";
    if (d.options.live_maintenance==LiveMaintenance::eager) {
      result.state_bound="physical/support state plus committed/needed old/new full L/P/B image copies, patches, journals and configured spool; widths and allocator/arena high-water storage additional";
      result.finalization_bound="affected kernel/view/keys plus all replaced full L/P/B image rows, unread spool and final-owner teardown; may be linear in image size even with no answer change";
    }
  }
  return result;
}
SupportOwnerId DeltaRuntime::owner() const { return impl().physical.owner(); }
std::uint64_t DeltaRuntime::sequence() const { return impl().physical.sequence(); }
DeltaMode DeltaRuntime::mode() const { return impl().mode; }
bool DeltaRuntime::ready() const { const auto& d=impl(); return !d.processing && !d.output_active && d.physical.ready(); }
DeltaState DeltaRuntime::state() const {
  const auto& d=impl(); return d.processing?d.lifecycle:d.output_active?DeltaState::committed_output:DeltaState::ready;
}
bool DeltaRuntime::has_answer() const { const auto& d=impl(); d.readable(); return d.physical.has_answer(); }
const storage::TupleLayout& DeltaRuntime::result_layout() const { return impl().output_layout; }
const DeltaMetrics& DeltaRuntime::bootstrap_metrics() const { return impl().bootstrap; }
DeltaMetrics DeltaRuntime::set_mode(DeltaMode mode) {
  auto& d=impl(); d.writable();
  require(mode==DeltaMode::maintenance || mode==DeltaMode::delta,"invalid_mode","unknown delta maintenance mode");
  DeltaMetrics metrics;
  if (mode==d.mode) return metrics;
  if (mode==DeltaMode::maintenance) {
    d.live.reset(); d.mode=mode; d.observe_configuration(); return metrics;
  }
  auto view=d.physical.current_view(d.options.epoch_view); d.metric(metrics,metrics.view_work,view.metrics().work);
  auto live=d.build_live(view,metrics,0); view.close();
  d.live=std::move(live); d.live_sequence=d.physical.sequence(); d.mode=mode; d.bootstrap=metrics;
  d.observe_configuration();
  return metrics;
}
DeltaRuntime::PendingEpoch DeltaRuntime::begin(const PhysicalSetUpdate& update) {
  auto& d=impl(); d.writable();
  return PendingEpoch(std::make_unique<PendingEpoch::Data>(impl_,update));
}
DeltaRuntime::Epoch DeltaRuntime::apply(const PhysicalSetUpdate& update) {
  auto pending=begin(update); pending.drain(); return pending.commit();
}
SupportRuntime::ResultCursor DeltaRuntime::results(ResultCursorOptions options) const {
  const auto& d=impl(); d.readable();
  return d.options.view==ResultView::core?d.physical.core_results(options):d.physical.results(options);
}
SupportRuntime::ResultCursor DeltaRuntime::core_results(ResultCursorOptions options) const { const auto& d=impl(); d.readable(); return d.physical.core_results(options); }
SupportRuntime::EpochView DeltaRuntime::current_view(EpochViewOptions options) const { const auto& d=impl(); d.readable(); return d.physical.current_view(options); }
PhysicalSnapshot DeltaRuntime::snapshot() const { const auto& d=impl(); d.readable(); return d.physical.snapshot(); }
std::optional<LiveSnapshot> DeltaRuntime::live_snapshot() const {
  const auto& d=impl(); d.readable(); if (!d.live) return {}; return LiveSnapshot{d.live_sequence,d.live->factors};
}
PhysicalStorageStatistics DeltaRuntime::storage_statistics() const { const auto& d=impl(); d.readable(); return d.physical.storage_statistics(); }
CanonicalDeltaState DeltaRuntime::canonical_state() const {
  const auto& d=impl(); d.readable();
  CanonicalDeltaState result{d.physical.canonical_state(),d.mode==DeltaMode::delta,d.options.view==ResultView::sql,{}};
  if (d.live) {
    CanonicalLiveState live{d.live_sequence,{},d.live->rows,d.live->parent_rows,d.live->child_rows};
    const auto buckets=[](const Impl::ParentCounts& input) {
      std::vector<CanonicalBucket> output; output.reserve(input.size());
      for (const auto& [key,bucket] : input) output.push_back({key,bucket.value,bucket.rows});
      return output;
    };
    for (std::size_t i=0;i<d.factors.size();++i)
      live.factors.push_back({d.factors[i].node,d.live->factors.at(i),
          buckets(d.live->parents.at(i)),buckets(d.live->child_index.at(i))});
    result.live=std::move(live);
  }
  return result;
}
InvariantReport DeltaRuntime::inspect_invariants(InspectionOptions options) const {
  const auto& d=impl(); d.readable(); detail::InspectionContext context(options);
  const auto issue=[&](InvariantCode code,InvariantComponent component,std::optional<NodeId> node,
      const Row& key,std::uint64_t expected,std::uint64_t actual) {
    InvariantIssue value{}; value.code=code; value.component=component; value.node=node; value.key=key;
    value.expected=expected; value.actual=actual; context.add(std::move(value));
  };
  try {
    context.merge(d.physical.inspect_invariants(context.remaining()));
    if (!context.report.complete) return std::move(context.report);
    context.charge();
    if (bool(d.live)!=(d.mode==DeltaMode::delta))
      issue(d.live?InvariantCode::unexpected_record:InvariantCode::missing_record,
          InvariantComponent::live_factor,{}, {},d.mode==DeltaMode::delta, bool(d.live));
    if (!d.live) return std::move(context.report);
    if (d.live_sequence!=d.physical.sequence())
      issue(InvariantCode::sequence,InvariantComponent::sequence,{}, {},d.physical.sequence(),d.live_sequence);
    const auto count=d.factors.size();
    const auto dimensions=[&](std::size_t actual,InvariantComponent component) {
      context.charge();
      if (actual!=count) issue(actual<count?InvariantCode::missing_metadata:InvariantCode::orphan_metadata,
          component,{}, {},count,actual);
    };
    dimensions(d.live->factors.size(),InvariantComponent::live_factor);
    dimensions(d.live->parents.size(),InvariantComponent::live_parent);
    dimensions(d.live->child_index.size(),InvariantComponent::live_child);
    const auto project=[&](const Row& row,const std::vector<std::size_t>& fields,
        const Impl::Factor& factor,InvariantComponent component)->std::optional<Row> {
      Row key; key.reserve(fields.size());
      for (auto field : fields) {
        context.charge();
        if (field>=row.size()) {
          issue(InvariantCode::missing_metadata,component,factor.node,row,field+1,row.size()); return {};
        }
        key.push_back(row[field]);
      }
      return key;
    };
    const auto compare_rows=[&](const Relation& expected,const Relation& actual,
        InvariantComponent component,NodeId node) {
      for (const auto& row : expected) {
        context.charge(); if (!actual.contains(row)) issue(InvariantCode::membership,component,node,row,1,0);
      }
      for (const auto& row : actual) {
        context.charge(); if (!expected.contains(row)) issue(InvariantCode::membership,component,node,row,0,1);
      }
    };
    // Derive expected L top-down from actual E, independently of build_live.
    // The physical inspector above separately verifies the E supports.
    auto view=d.physical.current_view({context.remaining().work_limit});
    context.charge(view.metrics().work);
    std::vector<Relation> expected(count);
    for (std::size_t i=0;i<count;++i) {
      context.charge(); const auto& factor=d.factors[i]; Relation separators;
      if (factor.parent) {
        if (*factor.parent>=i) {
          issue(InvariantCode::missing_metadata,InvariantComponent::live_factor,factor.node,{},i,*factor.parent);
          continue;
        }
        for (const auto& row : expected[*factor.parent]) {
          context.charge(); auto key=project(row,factor.parent_separator,factor,InvariantComponent::live_factor);
          if (key) separators.insert(std::move(*key));
        }
      }
      auto cursor=view.visible_keys(factor.node,{context.remaining().work_limit});
      context.charge(cursor.metrics().startup.work);
      for (;;) {
        auto tuple=cursor.next(); context.charge(cursor.metrics().last.work);
        if (!tuple) break;
        context.charge(); const auto& row=tuple->values();
        if (factor.parent) {
          auto key=project(row,factor.child_separator,factor,InvariantComponent::live_factor);
          if (!key || !separators.contains(*key)) continue;
        }
        expected[i].insert(row);
      }
      if (i<d.live->factors.size()) compare_rows(expected[i],d.live->factors[i],InvariantComponent::live_factor,factor.node);
    }
    view.close();
    auto& statistics=context.report.statistics;
    for (std::size_t i=0;i<d.live->factors.size();++i) {
      context.charge(); statistics.live_rows=add_size(statistics.live_rows,d.live->factors[i].size());
    }
    // Regroup observed L independently. This catches corrupted index rows and
    // counts even when the factor itself already has a reported discrepancy.
    const auto inspect_index=[&](const std::vector<Impl::ParentCounts>& indexes,bool child) {
      const auto component=child?InvariantComponent::live_child:InvariantComponent::live_parent;
      for (std::size_t i=0;i<std::max(count,indexes.size());++i) {
        context.charge(); Impl::ParentCounts grouped;
        const auto node=i<count?std::optional<NodeId>{d.factors[i].node}:std::nullopt;
        if (i<count && d.factors[i].parent) {
          const auto& factor=d.factors[i]; const auto source=child?i:*factor.parent;
          if (source<d.live->factors.size()) for (const auto& row : d.live->factors[source]) {
            context.charge(); auto key=project(row,child?factor.child_separator:factor.parent_separator,factor,component);
            if (key) { auto& bucket=grouped[*key]; bucket.rows.insert(row); ++bucket.value; }
          }
        }
        if (i>=indexes.size()) continue;
        const auto& observed=indexes[i];
        auto& total=child?statistics.live_child_rows:statistics.live_parent_rows;
        auto& buckets=child?statistics.live_child_buckets:statistics.live_parent_buckets;
        buckets=add_size(buckets,observed.size());
        for (const auto& [key,bucket] : observed) {
          context.charge(); total=add_size(total,bucket.rows.size());
          const auto found=grouped.find(key); const auto expected_count=found==grouped.end()?0:found->second.value;
          if (found==grouped.end()) issue(InvariantCode::unexpected_record,component,node,key,0,bucket.value);
          else if (bucket.value!=expected_count) issue(InvariantCode::support_count,component,node,key,expected_count,bucket.value);
          if (bucket.value!=bucket.rows.size() && bucket.value==expected_count)
            issue(InvariantCode::support_count,component,node,key,bucket.rows.size(),bucket.value);
          const Relation empty;
          const auto& expected_rows=found==grouped.end()?empty:found->second.rows;
          // Bucket location is the separator key; the membership values name
          // the missing/extra row count within this exact separator bucket.
          std::uint64_t missing=0,extra=0;
          for (const auto& row : expected_rows) { context.charge(); if (!bucket.rows.contains(row)) ++missing; }
          for (const auto& row : bucket.rows) { context.charge(); if (!expected_rows.contains(row)) ++extra; }
          if (missing) issue(InvariantCode::membership,component,node,key,missing,0);
          if (extra) issue(InvariantCode::membership,component,node,key,0,extra);
        }
        for (const auto& [key,bucket] : grouped) {
          context.charge(); if (!observed.contains(key)) issue(InvariantCode::missing_record,component,node,key,bucket.value,0);
        }
      }
    };
    inspect_index(d.live->parents,false); inspect_index(d.live->child_index,true);
    const auto total=[&](InvariantComponent component,std::size_t expected_total,std::size_t actual) {
      context.charge(); if (expected_total!=actual) issue(InvariantCode::aggregate_count,component,{}, {},expected_total,actual);
    };
    total(InvariantComponent::live_factor,statistics.live_rows,d.live->rows);
    total(InvariantComponent::live_parent,statistics.live_parent_rows,d.live->parent_rows);
    total(InvariantComponent::live_child,statistics.live_child_rows,d.live->child_rows);
  } catch (const detail::InspectionStop&) {
    context.report.complete=false;
  } catch (const Error& error) {
    // Diagnostic cursor limits are independent of update limits. Invalid
    // storage/metadata can make traversal impossible; never claim completeness.
    context.report.complete=false;
    if (error.code()!="resource_limit" && context.report.issues.size()<options.issue_limit)
      context.report.issues.push_back({InvariantCode::missing_metadata,InvariantComponent::live_factor,
          std::nullopt,std::nullopt,std::nullopt,std::nullopt,{},std::nullopt,std::nullopt});
  } catch (const std::out_of_range&) {
    context.report.complete=false;
    if (context.report.issues.size()<options.issue_limit)
      context.report.issues.push_back({InvariantCode::missing_metadata,InvariantComponent::live_factor,
          std::nullopt,std::nullopt,std::nullopt,std::nullopt,{},std::nullopt,std::nullopt});
  }
  return std::move(context.report);
}
#ifdef CROWN_RUNTIME_TESTING
void RuntimeTestProbe::seed_delta_sequence(DeltaRuntime& runtime,std::uint64_t sequence) {
  auto& d=runtime.impl(); d.writable(); seed_physical_sequence(d.physical,sequence);
  if (d.live) d.live_sequence=sequence;
}
PhysicalRuntime& RuntimeTestProbe::physical(DeltaRuntime& runtime) { return runtime.impl().physical; }
std::uint64_t RuntimeTestProbe::set_live_bucket(DeltaRuntime& runtime,NodeId node,bool child,const Row& key,std::uint64_t value) {
  auto& d=runtime.impl(); d.writable();
  require(bool(d.live),"invalid_probe","delta live image is absent");
  const auto rank=d.ranks.at(node.value);
  require(bool(rank),"invalid_probe","node is not a live factor");
  auto& bucket=(child?d.live->child_index:d.live->parents).at(*rank).at(key);
  return std::exchange(bucket.value,value);
}
std::size_t RuntimeTestProbe::set_live_total(DeltaRuntime& runtime,InvariantComponent component,std::size_t value) {
  auto& d=runtime.impl(); d.writable();
  require(bool(d.live),"invalid_probe","delta live image is absent");
  switch (component) {
    case InvariantComponent::live_factor: return std::exchange(d.live->rows,value);
    case InvariantComponent::live_parent: return std::exchange(d.live->parent_rows,value);
    case InvariantComponent::live_child: return std::exchange(d.live->child_rows,value);
    default: throw Error("invalid_probe","component is not a live total");
  }
}
#endif

void DeltaRuntime::check_invariants() const {
  const auto& d=impl(); d.readable(); d.physical.check_invariants();
  if (d.mode==DeltaMode::maintenance) { require(!d.live,"runtime_contract","maintenance mode retained a live cache"); return; }
  require(d.live && d.live_sequence==d.physical.sequence(),"runtime_contract","live cache has a stale epoch tag");
  auto view=d.physical.current_view(d.options.epoch_view); DeltaMetrics metrics;
  const auto rebuilt=d.build_live(view,metrics,d.live->rows,d.live->parent_rows,d.live->child_rows);
  require(rebuilt->factors==d.live->factors && rebuilt->parents==d.live->parents && rebuilt->rows==d.live->rows &&
      rebuilt->parent_rows==d.live->parent_rows && rebuilt->child_index==d.live->child_index && rebuilt->child_rows==d.live->child_rows,
      "runtime_contract","live cache or parent-separator counts differ from E-factor bootstrap");
}
void DeltaRuntime::declare_benchmark_context(std::shared_ptr<const DeclaredBenchmarkContext> value) {
  auto& d=impl(); d.declared_benchmark=std::move(value);
  if (d.observation) d.observation->declare_benchmark(d.declared_benchmark);
}
std::optional<CursorObservation> DeltaRuntime::last_cursor_observation() const { return impl().physical.last_cursor_observation(); }
CommittedStateGauges DeltaRuntime::committed_state_gauges() const { const auto& d=impl();d.readable();return d.physical.committed_state_gauges(); }
ObservationSnapshot DeltaRuntime::observations() const {
  const auto& d=impl(); auto result=d.physical.observations();
  result.initialization=d.physical.initialization_context();
  result.current_declared_benchmark=d.declared_benchmark; return result;
}
ObservationTrace DeltaRuntime::observation_trace() const {
  auto result=impl().physical.observation_trace(); result.snapshot=observations(); return result;
}
}  // namespace crown::runtime

#include "owner_statistics_detail.hpp"
namespace crown::runtime {
statistics::OwnerCapture DeltaRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  const auto& d=impl();
  if(d.processing){statistics::detail::OwnerBuilder pending{{d.physical.owner(),d.physical.sequence(),statistics::OwnerLayer::physical},d.physical.plan(),request,limits,true};return pending.finish();}
  return d.physical.capture_statistics(request,limits);
}
statistics::Freshness DeltaRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  return impl().physical.statistics_freshness(captured,max_event_lag);
}
}
