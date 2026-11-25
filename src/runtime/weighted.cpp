#include "weighted_delta_detail.hpp"
#include "sql_cold_rebuild.hpp"
#include "crown/ir/digest.hpp"
#include <exception>
#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <set>
#include <string_view>

namespace crown::runtime {
namespace {
// Set while a reference twin is built: its Impl must not select the keyed core.
thread_local bool keyed_disabled=false;
// Full-subtree equations and usage contracts: docs/weighted_messages.md,
// Refactor.md §10.2. P1 §7.3 supplies aggregation context; its projected output
// factors in docs/weighted_enumeration.md are distinct from these full messages.
// This path promises no Boolean
// update bound. All mutable/query-retained memory uses the admitted account.
using namespace weighted;
using annotations::MultiplicityPolicy;
using weighted_detail::Map;
using weighted_detail::Node;
using weighted_detail::Vector;
using weighted_detail::require;
std::shared_ptr<RecordValue> capture_record(const resource::MemoryAccount& account, const RecordValue& source) {
  // Explicit diagnostics only: never share mutable live arrays with a caller.
  constexpr resource::MemoryAttribution attribution{resource::MemoryOwnerKind::capture,0};
  auto result=resource::make_accounted_shared<RecordValue>(attribution,account,resource::MemoryPurpose::capture,
      account,attribution,source.children.size(),resource::MemoryPurpose::capture);
  result->local=source.local;result->subtree=source.subtree;result->factor=source.factor;
  result->supported_children=source.supported_children;
  std::copy(source.children.begin(),source.children.end(),result->children.begin());return result;
}
Binding bind(const CompiledProgram& program, std::uint64_t limit) {
  // Fixed-stack, domain-separated identity; structural set identity stays intact.
  const auto shape=program.physical_sha256();
  require(shape.size()==64,"weighted_contract","structural program has no physical binding");
  std::array<char,256> bytes{};
  constexpr std::string_view domain="CROWN-WEIGHTED-FACTOR;2;checked-uint64-multiplicity-v1;";
  auto* out=std::copy(domain.begin(),domain.end(),bytes.begin());
  out=std::copy(shape.begin(),shape.end(),out);*out++=';';
  const auto encoded=std::to_chars(out,bytes.data()+bytes.size(),limit);
  require(encoded.ec==std::errc{},"weighted_contract","weighted binding exceeded fixed encoding");
  Binding result{};std::copy(shape.begin(),shape.end(),result.shape_sha256.begin());
  result.weighted_sha256=sha256_fixed({bytes.data(),static_cast<std::size_t>(encoded.ptr-bytes.data())});
  result.multiplicity_limit=limit;return result;
}
}  // namespace

weighted_detail::Node::Node(const resource::MemoryAccount& account, NodeId id, std::size_t arity)
      :attribution{resource::MemoryOwnerKind::support_node,static_cast<std::uint64_t>(id.value)+1},
       records(std::less<TupleId>{},Map<RecordValue>::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)),
       messages(std::less<TupleId>{},Map<Multiplicity>::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)),
       factors(std::less<TupleId>{},Map<Multiplicity>::allocator_type(account,resource::MemoryPurpose::support_metadata,attribution)),
       children(arity,0,resource::MemoryAllocator<std::size_t>(account,resource::MemoryPurpose::immutable_metadata,attribution)) {}
void weighted_detail::Node::lifetime(const weighted::RecordValue* pointer, resource::AllocationLifetime value) const {
    static resource::MemoryAccount::ContainingSite site;  // O(1) after one calibration
    records.get_allocator().account().set_lifetime_containing(pointer,site,resource::MemoryPurpose::support_metadata,attribution,value);
}
void weighted_detail::Node::lifetime(const weighted::Multiplicity* pointer, resource::AllocationLifetime value) const {
    static resource::MemoryAccount::ContainingSite site;  // messages and factors share one node type
    records.get_allocator().account().set_lifetime_containing(pointer,site,resource::MemoryPurpose::support_metadata,attribution,value);
}

weighted::RecordValue::RecordValue(const resource::MemoryAccount& account, resource::MemoryAttribution owner, std::size_t arity,
    resource::MemoryPurpose purpose)
    :children(arity,Multiplicity{},resource::MemoryAllocator<Multiplicity>(account,purpose,owner)) {}
weighted::Journal::Journal(const resource::MemoryAccount& account, std::uint64_t epoch)
    :sequence(epoch),records(resource::OwnerAllocator<Change>(account,resource::MemoryPurpose::journal_undo)),
     events(resource::OwnerAllocator<Event>(account,resource::MemoryPurpose::journal_undo)) {}
weighted::NodeSnapshot::NodeSnapshot(const resource::MemoryAccount& account, NodeId id)
    :node(id),records(resource::OwnerAllocator<RowSnapshot>(account,resource::MemoryPurpose::capture)),
     messages(resource::OwnerAllocator<MessageSnapshot>(account,resource::MemoryPurpose::capture)),
     factors(resource::OwnerAllocator<MessageSnapshot>(account,resource::MemoryPurpose::capture)) {}

// Freeze once; full messages and local output factors have separate maps.
WeightedRuntime::Impl::Impl(CompiledProgram shape, weighted::Options opts, std::shared_ptr<detail::StorageWorkContext> work)
      :Impl(shape,opts,work,shape.make_storage(detail::compact_storage_work(work)),0) {}
WeightedRuntime::Impl::Impl(CompiledProgram shape,weighted::Options opts,std::shared_ptr<detail::StorageWorkContext> work,
    storage::AccountedPlanStorage tables,std::uint64_t initial_sequence)
      :options(opts),context(std::move(work)),program(std::move(shape)),storage(std::move(tables)),
       policy(options.multiplicity_limit),binding(bind(program,options.multiplicity_limit)),
       nodes(resource::MemoryAllocator<Node>(account(),resource::MemoryPurpose::support_metadata)),
       incoming(program.nodes().size(),std::nullopt,resource::MemoryAllocator<std::optional<std::size_t>>(account(),resource::MemoryPurpose::immutable_metadata)),
       factor_slots(resource::MemoryAllocator<std::size_t>(account(),resource::MemoryPurpose::immutable_metadata)),
       sequence(initial_sequence) {
    const auto admission=annotations::admit({annotations::Domain::nonnegative_multiplicity},annotations::Backend::weighted_subtree_messages);
    require(admission.admitted(),"unsupported_annotation","weighted subtree backend is unavailable");
    require(!program.normalized(),"unsupported_weighted_sql","weighted runtime requires a direct-CQ structural shape");
    nodes.reserve(program.nodes().size());
    for (const auto& node:program.nodes()) nodes.emplace_back(account(),node.id,node.children.size());
    for (std::size_t i=0;i<program.edges().size();++i) {
      const auto& edge=program.edges()[i];nodes[edge.parent.value].children[edge.child_slot]=i;incoming[edge.child.value]=i;
    }
    // Compile outside-child positions once. One flat immutable array avoids
    // per-row scans of enumerated siblings and allocates nothing when empty.
    std::size_t outside=0;
    for (const auto& node:program.nodes()) if (node.connex)
      for (const auto child:node.children) if (!program.nodes()[child.value].connex) ++outside;
    factor_slots.reserve(outside);
    for (const auto& shape:program.nodes()) {
      auto& node=nodes[shape.id.value];node.factor_begin=factor_slots.size();
      if (shape.connex) for (std::size_t slot=0;slot<shape.children.size();++slot)
        if (!program.nodes()[shape.children[slot].value].connex) factor_slots.push_back(slot);
      node.factor_end=factor_slots.size();
    }
    if (program.route()==PhysicalRoute::tree) {
      require(program.tree().root && program.tree().root->value<program.nodes().size(),"weighted_contract","weighted tree has no root");
      require(program.nodes()[program.tree().root->value].parent_key.fields().empty(),
          "weighted_contract","root summary requires the explicit empty key");
    }
    const char* forced=std::getenv("CROWN_WEIGHTED_ENGINE");
    if (!keyed_disabled && !(forced && std::string_view(forced)=="reference") && !options.capture_changes &&
        !options.capture_events && program.route()==PhysicalRoute::tree && keyed::SetEngine::unsupported(program).empty()) {
      keyed::EngineOptions engine;
      engine.delta=true; engine.bag=true; engine.sql_view=false; engine.gc=options.gc;
      engine.multiplicity_limit=options.multiplicity_limit;
      engine.memory_limit_bytes=static_cast<std::size_t>(account().statistics().limit_bytes);
      keyed=std::make_unique<keyed::SetEngine>(program,engine);
    }
  }
const resource::MemoryAccount& WeightedRuntime::Impl::account() const { return context->memory(); }
storage::IndexWorkAllowance* WeightedRuntime::Impl::allowance() const { return detail::compact_storage_work(context); }
void WeightedRuntime::Impl::readable() const { require(!updating,"runtime_busy","a weighted logical epoch is private"); }
Multiplicity WeightedRuntime::Impl::summary() const noexcept {
    if (keyed) return {keyed->root_weight()};
    if (program.route()==PhysicalRoute::constant_true) return {1};
    if (program.route()==PhysicalRoute::constant_false) return {};
    const auto& values=nodes[program.tree().root->value].messages;
    return values.empty()?Multiplicity{}:values.begin()->second;
  }
template<class Shape> std::shared_ptr<WeightedRuntime::Impl>
WeightedRuntime::Impl::create(const Shape& shape, weighted::Options options,
    const resource::MemoryAccount& receiver) {
    require(!shape.normalized(),"unsupported_weighted_sql","weighted runtime requires a direct-CQ structural shape");
    const MultiplicityPolicy checked(options.multiplicity_limit);static_cast<void>(checked);
    const auto account=receiver ? receiver : resource::MemoryAccount::create(options.memory_limit_bytes);
    options.memory_limit_bytes=account.statistics().limit_bytes;
    const auto& spec=shape.options().indexed_storage;
    auto context=resource::make_accounted_shared<detail::StorageWorkContext>(account,resource::MemoryPurpose::support_metadata,
        account,spec ? std::optional<storage::IndexWork>{spec->per_operation} : std::nullopt);
    detail::StorageOperation operation(context);
    auto compiled=CompiledProgram::freeze(context->memory(),shape,detail::compact_storage_work(context));
    return resource::make_accounted_shared<Impl>(context->memory(),resource::MemoryPurpose::support_metadata,
        std::move(compiled),options,context);
}

// A reference core in the same account holding exactly the keyed native
// weights (diagnostic snapshots). O(state); nothing is cached.
std::shared_ptr<WeightedRuntime::Impl> WeightedRuntime::Impl::reference_twin() const {
  struct Disable {
    bool previous=keyed_disabled;
    Disable() noexcept {keyed_disabled=true;}
    ~Disable() {keyed_disabled=previous;}
  } disable;
  auto twin_options=options;twin_options.work_limit.reset();
  auto twin=create(program,twin_options,account());
  WeightedRuntime runtime(twin);
  auto pending=runtime.begin_epoch(1);
  keyed->for_each_record([&](std::uint32_t node,storage::RowView values,std::uint64_t weight) {
    static_cast<void>(pending.stage({NodeId{node},storage::export_row(values),{0},{weight}}));
  });
  static_cast<void>(pending.commit());
  return twin;
}

WeightedRuntime detail::SqlColdRebuild::native(const resource::MemoryAccount& account,const PhysicalPlan& shape,
    weighted::Options options,const std::shared_ptr<StorageWorkContext>& context,std::uint64_t base) {
  require(bool(account) && context && context->memory().statistics().owner==account.statistics().owner,
      "storage_contract","cold native owner and receiving account differ");
  require(!shape.normalized() && context->indexed()==shape.options().indexed_storage.has_value(),
      "storage_contract","cold native backend differs from the authentic shape");
  if(context->indexed())static_cast<void>(storage_lease(context));
  const MultiplicityPolicy checked(options.multiplicity_limit);static_cast<void>(checked);
  options.memory_limit_bytes=account.statistics().limit_bytes;
  auto compiled=freeze(account,shape,compact_storage_work(context));
  auto tables=storage(compiled,compact_storage_work(context));
  return WeightedRuntime(resource::make_accounted_shared<WeightedRuntime::Impl>(account,
      resource::MemoryPurpose::support_metadata,std::move(compiled),options,context,std::move(tables),base));
}
void detail::SqlColdRebuild::close_native(WeightedRuntime& runtime,weighted::Options options) {
  auto& owner=runtime.impl();owner.readable();
  require(owner.readers==0 && !owner.context->active(),"storage_contract","cold native grant is still borrowed");
  require(options.multiplicity_limit==owner.binding.multiplicity_limit,
      "sql_rows_snapshot_binding","restored multiplicity domain differs from its bound image");
  options.memory_limit_bytes=owner.account().statistics().limit_bytes;
  // Allocate before replacing anything. No live token/cursor/storage journal
  // can retain the old allowance here; persistent table metadata owns none.
  auto normal=detail::storage_context(owner.program,options.memory_limit_bytes,owner.account());
  detail::validate_storage_context(owner.program,normal,options.memory_limit_bytes);
  owner.options=options;owner.context=std::move(normal);
}

struct WeightedRuntime::PendingEpoch::Data {
  // One exclusive transaction and grant across stages. Fund each inverse before
  // mutation; scalar edits save one child slot, while deletion retains a node.
  std::shared_ptr<Impl> owner;
  detail::StorageWorkLease lease;
  std::shared_ptr<Journal> journal;
  Epoch output;
  DeltaCapture capture_mode; // One fixed presentation; kernel arithmetic is unchanged.
  // Contribution replacement uses the existing native lookup. This private
  // tag adds no payload, count map or public child-event semantics.
  enum class PendingKind { native_weight, native_contribution, child_message };
  static_assert(sizeof(PendingKind)==sizeof(EventKind));
  struct Pending {
    PendingKind kind;
    NodeId node;
    std::optional<std::size_t> edge, message_record;
    storage::AccountedTuple key;
    Multiplicity before, after;
    std::uint64_t id, cause;
  };
  enum class UndoKind { row_insert, row_change, row_erase, counter_insert, counter_change, counter_erase };
  struct Undo {
    UndoKind kind;
    Node* node;
    TupleId id;
    Multiplicity local, subtree, factor, child, counter_before;
    Map<Multiplicity>* counters=nullptr; // The node's message or visible-factor map.
    std::size_t supported=0;
    std::optional<std::size_t> slot;
    Map<RecordValue>::node_type row_node;
    Map<Multiplicity>::node_type counter_node;
    Undo(UndoKind action, Node& target, TupleId tuple):kind(action),node(&target),id(tuple) {}
    Undo(Undo&&) noexcept=default;
    Undo& operator=(Undo&&) noexcept=default;
  };
  Vector<Undo> undo;
  Vector<std::pair<RelationId,storage::AccountedStorageTable::Journal>> tables;
  Vector<Pending> queue;
  std::size_t queue_head=0;
  std::uint64_t cause=0;

  // Only the opt-in path owns these buffers. Selected rows borrow private table
  // journals, and all cursors close before a factor is changed or rollback runs.
  //
  // A changed factor affects exactly the output assignments compatible with its
  // visible key. The walk is therefore re-rooted at that anchor: its ancestors
  // are reached through the C* separators (a whole-key probe when the parent's
  // visible key is the separator, else the native parent's compiled reverse
  // separator index), then every other step follows its usual separator bucket.
  // Work is proportional to the affected assignments, not to the root relation.
  // Shapes without such an access path keep the original root-first walk.
  struct DeltaWalk {
    enum class Lookup : std::uint8_t { anchor, checked_anchor, point, reverse, probe, bucket, scan };
    struct Route {
      std::size_t step=0, source=0; // Source is the walk position that keys this frame.
      Lookup lookup=Lookup::scan;
      std::size_t edge=0;           // Reverse only: the child's incoming edge.
      bool distinct=false;          // Reverse only: hidden fields may repeat a visible key.
    };
    struct Frame {
      std::optional<storage::AccountedStorageTable::Cursor> cursor;
      std::optional<storage::AccountedTuple> key;
      const storage::AccountedTuple* selected=nullptr;
      Multiplicity factor{1};
    };
    using Seen=std::set<TupleId,std::less<TupleId>,resource::MemoryAllocator<TupleId>>;
    Data& epoch;
    weighted::BagDeltas::Data& bag;
    Vector<Frame> frames;  // Walk order.
    Vector<Route> routes;  // Walk order.
    Vector<std::size_t> placed; // Compiled step -> walk position.
    Vector<Seen> seen;     // Created only for a reverse walk over hidden fields.
    Vector<storage::ScalarView> row;
    std::size_t position=0,anchor_position=0;
    bool resume=false, root_key_bound=false;
    const storage::AccountedTuple* anchor=nullptr;
    std::optional<storage::AccountedTuple> anchor_key;
    DeltaWalk(Data& value):epoch(value),bag(*value.deltas),
        frames(resource::MemoryAllocator<Frame>(value.owner->account(),resource::MemoryPurpose::delta_state)),
        routes(resource::MemoryAllocator<Route>(value.owner->account(),resource::MemoryPurpose::delta_state)),
        placed(resource::MemoryAllocator<std::size_t>(value.owner->account(),resource::MemoryPurpose::delta_state)),
        seen(resource::MemoryAllocator<Seen>(value.owner->account(),resource::MemoryPurpose::delta_state)),
        row(resource::MemoryAllocator<storage::ScalarView>(value.owner->account(),resource::MemoryPurpose::delta_state)) {
      const auto count=epoch.owner->program.enumeration().steps.size();
      frames.reserve(count);routes.reserve(count);placed.reserve(count);
      for(std::size_t i=0;i<count;++i) {bag.charge(2);frames.emplace_back();} // Init and failure cleanup.
      row.reserve(epoch.owner->program.result_layout().fields().size());
    }
    const program::EnumerationStep& step_at(std::size_t step) const {return epoch.owner->program.enumeration().steps[step];}
    storage::AccountedTuple project(const storage::AccountedProjection& projection,
        const storage::AccountedTuple& tuple) {
      for(const auto field:projection.fields()) {bag.charge(1,&bag.metrics.fields);bag.bytes(tuple.values()[field.value]);}
      return projection.apply(tuple);
    }
    // Re-root the C* traversal at the anchor. Fails (no state is used) when an
    // ancestor has neither a whole-key probe nor a compiled reverse index.
    bool anchored(std::size_t anchor_step) {
      const auto& program=epoch.owner->program;const auto& steps=program.enumeration().steps;
      routes.clear();placed.assign(steps.size(),steps.size());
      routes.push_back({anchor_step,0,Lookup::anchor});placed[anchor_step]=0;
      for(auto child=anchor_step;steps[child].parent_step;child=*steps[child].parent_step) {
        bag.charge();
        const auto parent=*steps[child].parent_step;const auto& below=steps[child];const auto& above=steps[parent];
        if(!below.bucket_index)return false;
        const auto& separator=epoch.owner->storage.projection(*below.bucket_index);
        Route route{parent,placed[child],Lookup::point};
        if(!separator.target().same_token(epoch.owner->storage.table(above.relation).layout())) {
          // The parent's visible key is wider than the separator. Only a native
          // parent owns the reverse separator index over its full records.
          const auto& shape=program.nodes()[above.node.value];
          const auto edge=epoch.owner->incoming[below.node.value];
          if(shape.kind!=NodeKind::native || !shape.visible_projection || !edge ||
              program.edges()[*edge].parent!=above.node || !program.edges()[*edge].reverse_index)return false;
          const auto& reverse=epoch.owner->storage.projection(*program.edges()[*edge].reverse_index);
          if(!reverse.target().same_token(separator.target()) ||
              !shape.visible_projection->source().same_token(epoch.owner->storage.table(shape.records).layout()))return false;
          route.lookup=Lookup::reverse;route.edge=*edge;
          route.distinct=!shape.visible_projection->source().same_token(shape.visible_projection->target());
        }
        placed[parent]=routes.size();routes.push_back(route);
      }
      // Parent-before-child order: each remaining step's parent is placed.
      for(std::size_t i=0;i<steps.size();++i) if(placed[i]==steps.size()) {
        bag.charge();
        require(steps[i].parent_step && placed[*steps[i].parent_step]<steps.size(),
            "weighted_contract","visible traversal is not root-connected");
        // A child whose visible key is its whole separator has a one-row
        // bucket; probe that key instead of opening a bucket cursor.
        const auto whole=steps[i].parent_key &&
            steps[i].parent_key->target().same_token(epoch.owner->storage.table(steps[i].relation).layout());
        placed[i]=routes.size();routes.push_back({i,placed[*steps[i].parent_step],whole?Lookup::probe:Lookup::bucket});
      }
      return true;
    }
    void original(std::size_t anchor_step) {
      const auto& steps=epoch.owner->program.enumeration().steps;
      routes.clear();placed.clear();
      for(std::size_t i=0;i<steps.size();++i) {
        placed.push_back(i);
        routes.push_back({i,steps[i].parent_step?*steps[i].parent_step:0,
            i==anchor_step?Lookup::checked_anchor:steps[i].parent_step?Lookup::bucket:Lookup::scan});
      }
    }
    bool pick(Frame& frame, const program::EnumerationStep& step, const storage::AccountedTuple& key) {
      const auto& table=epoch.owner->storage.table(step.relation);
      const auto found=table.find(key,epoch.owner->allowance());
      if(!found)return false;
      bag.charge(1,&bag.metrics.rows_visited);
      frame.selected=table.get(*found,epoch.owner->allowance());
      require(frame.selected!=nullptr,"weighted_contract","private visible key lost its row");
      bag.charge(1,&bag.metrics.factor_reads);
      frame.factor=epoch.owner->nodes[step.node.value].factors.at(found->tuple);
      require(frame.factor.present(),"weighted_contract","private visible key has no positive factor");
      return true;
    }
    storage::AccountedTuple separator(const Route& route) {
      return project(epoch.owner->storage.projection(*step_at(routes[route.source].step).bucket_index),
          *frames[route.source].selected);
    }
    bool reverse(Frame& frame, const Route& route, const program::EnumerationStep& step) {
      const auto& program=epoch.owner->program;const auto& shape=program.nodes()[step.node.value];
      const auto at=static_cast<std::size_t>(&frame-frames.data());
      if(!frame.cursor) {
        bag.charge(2); // Open and its eventual allocation-free cursor close.
        frame.key=separator(route);
        frame.cursor=epoch.bucket(shape.records,epoch.owner->storage.index(*program.edges()[route.edge].reverse_index),*frame.key);
        if(route.distinct) {
          if(seen.empty()) {
            seen.reserve(frames.size());
            for(std::size_t i=0;i<frames.size();++i)
              seen.emplace_back(std::less<TupleId>{},resource::MemoryAllocator<TupleId>(epoch.owner->account(),resource::MemoryPurpose::delta_state));
          }
          seen[at].clear();
        }
      }
      while(const auto entry=frame.cursor->next_entry(epoch.owner->allowance())) {
        bag.charge();
        const auto visible=project(*shape.visible_projection,entry->tuple);
        const auto& table=epoch.owner->storage.table(step.relation);
        const auto found=table.find(visible,epoch.owner->allowance());
        if(!found)continue; // No positive contribution reaches this visible key.
        if(route.distinct) {bag.charge();if(!seen[at].insert(found->tuple).second)continue;}
        bag.charge(1,&bag.metrics.rows_visited);
        frame.selected=table.get(*found,epoch.owner->allowance());
        require(frame.selected!=nullptr,"weighted_contract","private visible key lost its row");
        bag.charge(1,&bag.metrics.factor_reads);
        frame.factor=epoch.owner->nodes[step.node.value].factors.at(found->tuple);
        require(frame.factor.present(),"weighted_contract","private visible key has no positive factor");
        return true;
      }
      return false;
    }
    bool select(Frame& frame, const Route& route) {
      bag.charge();
      const auto& step=step_at(route.step);
      switch(route.lookup) {
        case Lookup::checked_anchor:
          if(frame.selected)return false;
          if(step.parent_step) {
            frame.key=project(*step.parent_key,*frames[route.source].selected);
            if(bag.compare(frame.key->values(),anchor_key->values())!=0)return false;
          }
          frame.selected=anchor;frame.factor={1};return true;
        case Lookup::anchor:
          if(frame.selected)return false;
          frame.selected=anchor;frame.factor={1};return true;
        case Lookup::point:
          if(frame.selected)return false; // A whole visible key selects at most one row.
          bag.charge(2);frame.key=separator(route);return pick(frame,step,*frame.key);
        case Lookup::reverse: return reverse(frame,route,step);
        case Lookup::probe:
          if(frame.selected)return false;
          bag.charge(2);frame.key=project(*step.parent_key,*frames[route.source].selected);return pick(frame,step,*frame.key);
        case Lookup::bucket: case Lookup::scan: break;
      }
      if(position==0 && root_key_bound) {
        if(frame.selected)return false;
        bag.charge(2); // Probe the root key and borrow its live tuple.
        return pick(frame,step,*anchor_key);
      }
      if(!frame.cursor) {
        bag.charge(2); // Open and its eventual allocation-free cursor close.
        if(route.lookup==Lookup::bucket) {
          frame.key=project(*step.parent_key,*frames[route.source].selected);
          frame.cursor=epoch.bucket(step.relation,epoch.owner->storage.index(*step.bucket_index),*frame.key);
        } else frame.cursor=epoch.delta_live(step.relation);
      }
      const auto entry=frame.cursor->next_entry(epoch.owner->allowance());
      if(!entry)return false;
      bag.charge(1,&bag.metrics.rows_visited);frame.selected=&entry->tuple;
      bag.charge(1,&bag.metrics.factor_reads);
      frame.factor=epoch.owner->nodes[step.node.value].factors.at(entry->handle.tuple);
      require(frame.factor.present(),"weighted_contract","private visible key has no positive factor");
      return true;
    }
    void close_frame(Frame& frame) noexcept {frame.cursor.reset();frame.key.reset();frame.selected=nullptr;}
    storage::ScalarView value(AssignmentSlot slot) const {return frames[placed[slot.step]].selected->values()[slot.field.value];}
    void collect(NodeId node, const storage::AccountedTuple& key, Multiplicity before, Multiplicity after) {
      // A positive-to-positive factor change cannot alter DISTINCT support.
      // Only the explicit support-capture path skips this walk; all numeric
      // source, message and factor maintenance still executes normally.
      const bool support=epoch.capture_mode==DeltaCapture::support;
      if(support && before.present()==after.present())return;
      const auto& enumeration=epoch.owner->program.enumeration();
      position=0;resume=false;anchor=&key;anchor_key.reset();
      auto anchor_step=enumeration.steps.size();
      for(std::size_t i=0;i<enumeration.steps.size();++i) {
        bag.charge();
        if(enumeration.steps[i].node==node) {anchor_step=i;break;}
      }
      require(anchor_step<frames.size(),"weighted_contract","factor is outside the checked visible traversal");
      if(anchored(anchor_step))anchor_position=0;
      else {
        original(anchor_step);anchor_position=anchor_step;
        const auto& step=enumeration.steps[anchor_step];
        if(step.parent_step)anchor_key=project(epoch.owner->storage.projection(*step.bucket_index),key);
        root_key_bound=step.parent_step==0 && step.parent_key->source().same_token(anchor_key->layout());
      }
      require(routes.size()==frames.size(),"weighted_contract","visible traversal route is incomplete");
      const SignedMagnitude difference=support?SignedMagnitude{before.present(),{1}}:
          SignedMagnitude{after<before,{after<before?before.value-after.value:after.value-before.value}};
      // Never use owner->summary(): private insertions may not yet reach root.
      while(weighted_detail::advance_visible(*this,routes)) {
        for(const auto equality:enumeration.equalities)
          require(bag.cell(value(equality.left),value(equality.right))==0,"weighted_contract","private assignments disagree");
        auto term=difference;
        // Defer products until every compatible frame exists. Dead prefixes
        // cannot overflow before a later empty bucket establishes zero.
        for(std::size_t i=0;!support && i<frames.size();++i)if(i!=anchor_position) {
          bag.charge(1,&bag.metrics.multiplications);
          term.magnitude=epoch.owner->policy.multiply(term.magnitude,frames[i].factor);
        }
        row.clear();
        for(const auto slot:enumeration.output) {
          const auto cell=value(slot);bag.charge(1,&bag.metrics.fields);row.push_back(cell);
        }
        bag.add(epoch.owner->program.result_layout(),storage::RowView::borrow(row),term);
      }
      row.clear();anchor=nullptr;anchor_key.reset();root_key_bound=false;
    }
  };
  std::shared_ptr<weighted::BagDeltas::Data> deltas;
  resource::AccountedUnique<DeltaWalk> delta_walk;
  bool keyed=false;
  std::vector<storage::ScalarView> keyed_cells;
  Data(std::shared_ptr<Impl> value, std::uint64_t sequence, DeltaCapture capture)
      :owner(std::move(value)),lease(detail::storage_lease(owner->context)),
       journal(owner->options.capture_changes || owner->options.capture_events ?
           resource::make_accounted_shared<Journal>(owner->account(),resource::MemoryPurpose::journal_undo,owner->account(),sequence):nullptr),
       output{sequence,false,owner->summary(),owner->summary(),{},journal},capture_mode(capture),
       undo(resource::MemoryAllocator<Undo>(owner->account(),resource::MemoryPurpose::journal_undo)),
       tables(resource::MemoryAllocator<std::pair<RelationId,storage::AccountedStorageTable::Journal>>(owner->account(),resource::MemoryPurpose::journal_undo)),
       queue(resource::MemoryAllocator<Pending>(owner->account(),resource::MemoryPurpose::support_metadata)) {
    if(capture==DeltaCapture::enabled || capture==DeltaCapture::support) {
      deltas=resource::make_accounted_shared<weighted::BagDeltas::Data>(owner->account(),resource::MemoryPurpose::delta_state,
          owner->account(),owner->policy,output.metrics.work,owner->options.work_limit);
      if(!owner->keyed)delta_walk=resource::make_accounted_unique<DeltaWalk>(owner->account(),resource::MemoryPurpose::delta_state,*this);
    }
    if(owner->keyed) {
      if(deltas)deltas->charge();  // a captured epoch costs at least one unit, as on the reference core
      owner->keyed->begin();keyed=true;
    }
  }
  ~Data() { rollback(); }
  Impl& active() const {
    require(bool(owner),"invalid_epoch","weighted epoch is closed");return *owner;
  }
  void charge(std::uint64_t amount=1) {
    const auto used=output.metrics.work;
    require(amount<=UINT64_MAX-used && (!owner->options.work_limit ||
        (used<=*owner->options.work_limit && amount<=*owner->options.work_limit-used)),
        "resource_limit","weighted epoch work exhausted; previous epoch preserved");
    output.metrics.work+=amount;
  }
  void metric(std::uint64_t& value, std::uint64_t amount=1) {
    // Each such counter is a subset of cumulative work; charge proves room
    // for both additions before changing the counter.
    charge(amount);value+=amount;
  }
  void sample_grant() noexcept {
    if (!lease) return;
    const auto& cap=owner->context->limit();const auto& left=lease->allowance.get()->remaining();
    output.metrics.native_grant_consumed={cap.structural_steps-left.structural_steps,cap.scalar_fields-left.scalar_fields,
        cap.scalar_bytes-left.scalar_bytes,cap.pointer_slots-left.pointer_slots,cap.link_actions-left.link_actions};
  }
  void rollback() noexcept {
    if (!owner) return;
    if (keyed) {
      owner->keyed->rollback();deltas.reset();
      sample_grant();owner->last=Attempt{output.sequence,Phase::aborted,output.metrics};owner->updating=false;
      owner.reset();lease.reset();return;
    }
    delta_walk.reset();deltas.reset(); // Release private readers before inverse table work.
    if (journal) journal->phase=Phase::aborted;
    // Restore metadata first while the original native table handles survive.
    for (auto it=undo.rbegin();it!=undo.rend();++it) {
      auto& item=*it;auto& node=*item.node;
      switch (item.kind) {
        case UndoKind::row_insert: node.records.erase(item.id);break;
        case UndoKind::row_change: {
          auto& value=node.records.at(item.id);value.local=item.local;value.subtree=item.subtree;
          value.factor=item.factor;value.supported_children=item.supported;if(item.slot)value.children[*item.slot]=item.child;
          break;
        }
        case UndoKind::row_erase: {
          node.lifetime(&item.row_node.mapped(),resource::AllocationLifetime::active);
          auto& value=item.row_node.mapped();value.children.get_allocator().set_allocation_lifetime(
              value.children.data(),value.children.capacity(),resource::AllocationLifetime::active);
          if (!node.records.insert(std::move(item.row_node)).inserted) std::terminate();
          break;
        }
        case UndoKind::counter_insert: item.counters->erase(item.id);break;
        case UndoKind::counter_change: item.counters->at(item.id)=item.counter_before;break;
        case UndoKind::counter_erase:
          node.lifetime(&item.counter_node.mapped(),resource::AllocationLifetime::active);
          if (!item.counters->insert(std::move(item.counter_node)).inserted) std::terminate();
          break;
      }
    }
    for (auto& [id,table]:tables) {static_cast<void>(id);table.rollback();}
    sample_grant();owner->last=Attempt{output.sequence,Phase::aborted,output.metrics};owner->updating=false;
    queue.clear();tables.clear();undo.clear();owner.reset();lease.reset();
  }
  storage::AccountedStorageTable::Journal& writer(RelationId id) {
    // Reuse the table journal and the epoch grant; neither creates a refill.
    for (auto& [relation,table]:tables) if (relation==id) return table;
    auto journal=owner->storage.table(id).journal(detail::owning_storage_work(owner->context));
    tables.emplace_back(id,std::move(journal));return tables.back().second;
  }
  storage::AccountedStorageTable::Cursor live(RelationId id) {
    for (auto& [relation,table]:tables) if (relation==id) return table.live();
    return owner->storage.table(id).live(owner->allowance());
  }
  storage::AccountedStorageTable::Cursor delta_live(RelationId id) {
    for(auto& [relation,table]:tables) {deltas->charge();if(relation==id)return table.live();}
    return owner->storage.table(id).live(owner->allowance());
  }
  storage::AccountedStorageTable::Cursor bucket(RelationId id, IndexId index, const storage::AccountedTuple& key) {
    for(auto& [relation,table]:tables) {deltas->charge();if(relation==id)return table.bucket_cursor(index,key);}
    return owner->storage.table(id).bucket_cursor(index,key,owner->allowance());
  }
  TupleHandle insert(RelationId id, const storage::AccountedTuple& tuple) {
    metric(output.metrics.storage_changes);const auto result=writer(id).insert(tuple);
    require(result.inserted,"weighted_contract","weighted storage duplicated membership");return result.handle;
  }
  void erase(RelationId id, TupleHandle handle) {
    metric(output.metrics.storage_changes);require(writer(id).erase(handle),"weighted_contract","weighted storage lost membership");
  }
  Undo& prepare(UndoKind action, Node& node, TupleId id) {
    metric(output.metrics.metadata_changes);
    return undo.emplace_back(action,node,id);
  }
  Multiplicity message_at(NodeId id, const storage::AccountedTuple& key) {
    metric(output.metrics.separator_probes);const auto& shape=owner->program.nodes()[id.value];
    const auto found=owner->storage.table(shape.parent_support).find(key,owner->allowance());
    return found?owner->nodes[id.value].messages.at(found->tuple):Multiplicity{};
  }
  void initialize_children(const program::PhysicalNode& shape, RecordValue& value,
      const storage::AccountedTuple& row, std::optional<std::size_t> causing_slot={}, Multiplicity before={}) {
    for (std::size_t i=0;i<shape.children.size();++i) {
      if (causing_slot==i) value.children[i]=before;
      else {
        const auto& edge=owner->program.edges()[owner->nodes[shape.id.value].children[i]];
        value.children[i]=message_at(edge.child,edge.parent_key.apply(row));
      }
      if (value.children[i].present()) ++value.supported_children;
    }
  }
  Multiplicity product(const RecordValue& value, Multiplicity local, std::size_t supported,
      std::optional<std::size_t> slot={}, Multiplicity after={}) {
    // Missing support makes the complete product zero before any overflow-prone
    // multiplication. Recompute supported products without division on delete.
    if (supported!=value.children.size()) return {};
    auto result=local;
    for (std::size_t i=0;i<value.children.size();++i) {
      metric(output.metrics.multiplications);result=owner->policy.multiply(result,slot==i?after:value.children[i]);
    }
    return result;
  }
  std::shared_ptr<RecordValue> image(const RecordValue* source) {
    if (!source) return {};
    metric(output.metrics.child_slots_copied,static_cast<std::uint64_t>(source->children.size()));
    return capture_record(owner->account(),*source);
  }
  Multiplicity local_factor(const program::PhysicalNode& shape, const RecordValue& value,
      Multiplicity local, Multiplicity subtree, std::optional<std::size_t> slot={}, Multiplicity child={}) {
    // Surviving rows contribute only their own native weight and outside-C*
    // messages. Inside child factors will be multiplied by the result cursor.
    if (!shape.connex || !subtree.present()) return {};
    auto result=local;
    const auto& node=owner->nodes[shape.id.value];
    for (auto position=node.factor_begin;position<node.factor_end;++position) {
      const auto child_slot=owner->factor_slots[position];
      metric(output.metrics.factor_slots_visited);
      metric(output.metrics.factor_multiplications);
      result=owner->policy.multiply(result,slot==child_slot?child:value.children[child_slot]);
    }
    return result;
  }
  void factor_change(const program::PhysicalNode& shape, const storage::AccountedTuple& tuple,
      Multiplicity before, Multiplicity after) {
    if (before==after) return;
    require(shape.connex && shape.visible_projection && shape.visible_relation,
        "weighted_contract","weighted factor has no compiled visible relation");
    replace_projection(shape,shape.visible_projection->apply(tuple),before,after,/*visible=*/true);
  }
  void note_row(const program::PhysicalNode& shape, TupleHandle handle, Record before, Record after) {
    if (!journal) return;
    metric(output.metrics.journal_records);
    auto pin=owner->storage.table(shape.records).pin(handle,owner->allowance());
    journal->records.emplace_back(RowChange{shape.id,std::move(pin),before,after,cause});
  }
  void insert_row(const program::PhysicalNode& shape, TupleHandle handle,
      const storage::AccountedTuple& tuple, RecordValue value) {
    auto& node=owner->nodes[shape.id.value];
    value.factor=local_factor(shape,value,value.local,value.subtree);
    const auto next=value.factor;
    if (journal) note_row(shape,handle,{},image(&value));
    prepare(UndoKind::row_insert,node,handle.tuple);
    require(node.records.emplace(handle.tuple,std::move(value)).second,"weighted_contract","weighted row metadata duplicated");
    factor_change(shape,tuple,{},next);
  }
  void change_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple, Multiplicity local,
      Multiplicity subtree, std::size_t supported, std::optional<std::size_t> slot={}, Multiplicity child={}) {
    // Default numeric path changes only inline fields/one slot. Full before/after
    // array copies below are the explicitly requested inspection cost.
    auto& node=owner->nodes[shape.id.value];auto& value=node.records.at(handle.tuple);
    const auto old_factor=value.factor;
    const bool inside_numeric=slot && owner->program.nodes()[shape.children[*slot].value].connex &&
        value.local==local && value.subtree.present() && subtree.present();
    const auto next_factor=inside_numeric?old_factor:local_factor(shape,value,local,subtree,slot,child);
    if (journal) {
      auto before=image(&value);auto after=image(&value);
      after->local=local;after->subtree=subtree;after->supported_children=supported;
      after->factor=next_factor;
      if (slot) after->children[*slot]=child;
      note_row(shape,handle,std::move(before),std::move(after));
    }
    auto& item=prepare(UndoKind::row_change,node,handle.tuple);
    item.local=value.local;item.subtree=value.subtree;item.factor=old_factor;
    item.supported=value.supported_children;item.slot=slot;
    if (slot) item.child=value.children[*slot];
    value.local=local;value.subtree=subtree;value.factor=next_factor;value.supported_children=supported;
    if (slot) value.children[*slot]=child;
    factor_change(shape,tuple,old_factor,next_factor);
  }
  void remove_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple) {
    auto& node=owner->nodes[shape.id.value];const auto position=node.records.find(handle.tuple);
    const auto old_factor=position->second.factor;
    if (journal) note_row(shape,handle,image(&position->second),{});
    auto& item=prepare(UndoKind::row_erase,node,handle.tuple);
    node.lifetime(&position->second,resource::AllocationLifetime::retained);
    auto& value=position->second;value.children.get_allocator().set_allocation_lifetime(
        value.children.data(),value.children.capacity(),resource::AllocationLifetime::retained);
    item.row_node=node.records.extract(position);
    factor_change(shape,tuple,old_factor,{});
  }
  void enqueue(Pending event) {
    // Same-key numeric deltas are causal, unlike coalescible presence flags.
    metric(output.metrics.events_enqueued);event.id=output.metrics.events_enqueued;
    const auto kind=event.kind==PendingKind::child_message ? EventKind::child_message : EventKind::native_weight;
    if (owner->options.capture_events) journal->events.push_back({event.id,event.cause,0,kind,event.node,
        event.edge,event.message_record,event.before,event.after});
    queue.push_back(std::move(event));
    const auto pending=static_cast<std::uint64_t>(queue.size()-queue_head);
    if (pending>output.metrics.queue_peak) output.metrics.queue_peak=pending;
  }
  void replace_projection(const program::PhysicalNode& shape, storage::AccountedTuple key,
      Multiplicity old, Multiplicity next, bool visible) {
    // Both projections replace one row contribution in an exact sum. Only a
    // full separator message propagates to an ancestor; visible factors are
    // terminal values for result enumeration. Their maps/diagnostics are distinct.
    if (old==next) return;
    metric(visible?output.metrics.factor_replacements:output.metrics.message_replacements);
    auto& node=owner->nodes[shape.id.value];auto& values=visible?node.factors:node.messages;
    const auto relation=visible?*shape.visible_relation:shape.parent_support;
    auto& table=owner->storage.table(relation);const auto found=table.find(key,owner->allowance());
    const auto before=found?values.at(found->tuple):Multiplicity{};
    const auto after=owner->policy.replace(before,old,next);
    // Telescope now, before membership/scalar publication, against other current factors.
    if(visible && delta_walk)delta_walk->collect(shape.id,key,before,after);
    const auto handle=found?*found:insert(relation,key);
    const auto kind=!found?UndoKind::counter_insert:after.present()?UndoKind::counter_change:UndoKind::counter_erase;
    std::optional<std::size_t> record;
    if (journal) {
      metric(output.metrics.journal_records);record=journal->records.size();
      auto pin=table.pin(handle,owner->allowance());
      if (visible) journal->records.emplace_back(FactorChange{shape.id,std::move(pin),before,after,cause});
      else journal->records.emplace_back(MessageChange{shape.id,std::move(pin),before,after,cause});
    }
    auto& item=prepare(kind,node,handle.tuple);item.counter_before=before;item.counters=&values;
    if (!found) require(values.emplace(handle.tuple,after).second,"weighted_contract","weighted projection metadata duplicated");
    else if (after.present()) values.at(handle.tuple)=after;
    else {
      const auto position=values.find(handle.tuple);node.lifetime(&position->second,resource::AllocationLifetime::retained);
      item.counter_node=values.extract(position);erase(relation,handle);
    }
    if (before.present()!=after.present())
      metric(visible?output.metrics.factor_membership_changes:output.metrics.message_membership_changes);
    if (!visible && owner->incoming[shape.id.value]) {
      const auto edge=*owner->incoming[shape.id.value];
      enqueue({PendingKind::child_message,owner->program.edges()[edge].parent,edge,record,std::move(key),before,after,0,cause});
    }
  }
  void value_change(const program::PhysicalNode& shape, const storage::AccountedTuple& tuple,
      Multiplicity before, Multiplicity after) {
    if (before==after) return;
    metric(output.metrics.row_value_changes);
    if (before.present()!=after.present()) {
      metric(output.metrics.row_membership_changes);
      if (after.present()) static_cast<void>(insert(shape.survivors,tuple));
      else {
        const auto handle=owner->storage.table(shape.survivors).find(tuple,owner->allowance());
        require(handle.has_value(),"weighted_contract","positive weighted row has no survivor");erase(shape.survivors,*handle);
      }
    }
    replace_projection(shape,shape.parent_key.apply(tuple),before,after,/*visible=*/false);
  }
  void native(Pending& event) {
    metric(output.metrics.native_inputs);metric(output.metrics.row_visits);
    charge();static_cast<void>(owner->policy.add(event.before,{}));
    charge();static_cast<void>(owner->policy.add(event.after,{}));
    const auto& shape=owner->program.nodes()[event.node.value];auto& node=owner->nodes[event.node.value];
    const auto found=owner->storage.table(shape.records).find(event.key,owner->allowance());
    const auto* before=found?&node.records.at(found->tuple):nullptr;
    const auto current=before?before->local:Multiplicity{};
    if (event.kind==PendingKind::native_contribution) {
      // The caller supplies its own old/new share. Normalize exactly once at
      // the same lookup used below. Successfully normalized diagnostic events
      // expose actual row totals; an aborted trace can retain the input shares.
      charge();event.after=owner->policy.replace(current,event.before,event.after);event.before=current;
      if (owner->options.capture_events) {
        auto& captured=journal->events.at(static_cast<std::size_t>(event.id-1));
        captured.before=event.before;captured.after=event.after;
      }
    } else require(current==event.before,"weight_conflict","expected native weight differs from the current row");
    if (event.before==event.after) return;
    metric(output.metrics.native_changes);output.changed=true;
    const auto old=before?before->subtree:Multiplicity{};
    if (event.after.present()) {
      if (before) {
        const auto next=product(*before,event.after,before->supported_children);
        change_row(shape,*found,event.key,event.after,next,before->supported_children);
        value_change(shape,event.key,old,next);
      } else {
        RecordValue after(owner->account(),node.attribution,shape.children.size());after.local=event.after;
        initialize_children(shape,after,event.key);after.subtree=product(after,after.local,after.supported_children);
        const auto next=after.subtree;const auto handle=insert(shape.records,event.key);
        insert_row(shape,handle,event.key,std::move(after));value_change(shape,event.key,{},next);
      }
    } else {
      remove_row(shape,*found,event.key);value_change(shape,event.key,old,{});erase(shape.records,*found);
    }
  }
  void child_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple,
      const program::PhysicalEdge& edge, const Pending& event) {
    metric(output.metrics.row_visits);auto& node=owner->nodes[shape.id.value];const auto& before=node.records.at(handle.tuple);
    require(before.children[edge.child_slot]==event.before,"weighted_contract","numeric child events must preserve their causal order");
    auto supported=before.supported_children;
    if (!event.before.present() && event.after.present()) ++supported;
    if (event.before.present() && !event.after.present()) --supported;
    const auto old=before.subtree;const auto next=product(before,before.local,supported,edge.child_slot,event.after);
    const bool remove=shape.kind==NodeKind::generalized && supported==0;
    if (remove) {metric(output.metrics.candidates_removed);remove_row(shape,handle,tuple);}
    else change_row(shape,handle,tuple,before.local,next,supported,edge.child_slot,event.after);
    value_change(shape,tuple,old,next);
    if (remove) erase(shape.records,handle);
  }
  void child(Pending& event) {
    const auto& edge=owner->program.edges()[*event.edge];const auto& shape=owner->program.nodes()[edge.parent.value];
    if (shape.kind==NodeKind::native) {
      require(edge.reverse_index.has_value(),"weighted_contract","native parent lacks a reverse separator index");
      auto cursor=writer(shape.records).bucket_cursor(owner->storage.index(*edge.reverse_index),event.key);
      while (const auto entry=cursor.next_entry(owner->allowance())) child_row(shape,entry->handle,entry->tuple,edge,event);
    } else {
      const auto& table=owner->storage.table(shape.records);auto found=table.find(event.key,owner->allowance());
      if (!found) {
        require(!event.before.present() && event.after.present(),"weighted_contract","generalized numeric event lost its candidate");
        RecordValue initial(owner->account(),owner->nodes[shape.id.value].attribution,shape.children.size());initial.local={1};
        // The child table may already contain a later queued total. Seed this
        // slot from the causing event; siblings are unchanged in this stage.
        initialize_children(shape,initial,event.key,edge.child_slot,event.after);
        initial.subtree=product(initial,initial.local,initial.supported_children);const auto next=initial.subtree;
        found=insert(shape.records,event.key);insert_row(shape,*found,event.key,std::move(initial));metric(output.metrics.candidates_created);
        value_change(shape,event.key,{},next);return;
      }
      child_row(shape,*found,event.key,edge,event);
    }
  }
  void drain() {
    while (queue_head<queue.size()) {
      // Moving first keeps the current event valid if propagation grows queue.
      auto event=std::move(queue[queue_head++]);metric(output.metrics.events_applied);cause=event.id;
      if (owner->options.capture_events) journal->events.at(static_cast<std::size_t>(event.id-1)).applied_ordinal=output.metrics.events_applied;
      if (event.kind==PendingKind::child_message) child(event);else native(event);
    }
    queue.clear();queue_head=0;
    require(output.metrics.events_applied==output.metrics.events_enqueued,"weighted_contract","weighted event queue did not drain exactly once");
    output.after=owner->summary();sample_grant();
  }
};

namespace {
template<class Owner, class Cursor>
Snapshot capture_weighted(Owner& owner, std::uint64_t sequence, bool tentative,
    SnapshotLimits limits, Cursor cursor) {
  // Explicit bounded copy, not an automatic update side effect or import proof.
  Snapshot result{owner.account().statistics().owner,sequence,tentative,owner.binding,owner.program,owner.summary(),
      OutputVector<NodeSnapshot>(resource::OwnerAllocator<NodeSnapshot>(owner.account(),resource::MemoryPurpose::capture))};
  std::uint64_t rows=0;
  result.nodes.reserve(owner.program.nodes().size());
  for (const auto& shape:owner.program.nodes()) {
    result.nodes.emplace_back(owner.account(),shape.id);auto& node=result.nodes.back();
    auto records=cursor(shape.records);
    while (const auto entry=records.next_entry(owner.allowance())) {
      require(rows<limits.rows,"snapshot_limit","weighted snapshot row limit exceeded");++rows;
      node.records.push_back({shape.layout.tuple(entry->tuple.values(),{resource::MemoryOwnerKind::capture,0}),
          capture_record(owner.account(),owner.nodes[shape.id.value].records.at(entry->handle.tuple))});
    }
    auto messages=cursor(shape.parent_support);
    while (const auto entry=messages.next_entry(owner.allowance())) {
      require(rows<limits.rows,"snapshot_limit","weighted snapshot row limit exceeded");++rows;
      node.messages.push_back({owner.storage.table(shape.parent_support).layout().tuple(entry->tuple.values(),{resource::MemoryOwnerKind::capture,0}),
          owner.nodes[shape.id.value].messages.at(entry->handle.tuple)});
    }
    if (shape.visible_relation) {
      auto factors=cursor(*shape.visible_relation);
      while (const auto entry=factors.next_entry(owner.allowance())) {
        require(rows<limits.rows,"snapshot_limit","weighted snapshot row limit exceeded");++rows;
        node.factors.push_back({owner.storage.table(*shape.visible_relation).layout().tuple(entry->tuple.values(),
            {resource::MemoryOwnerKind::capture,0}),owner.nodes[shape.id.value].factors.at(entry->handle.tuple)});
      }
    }
  }
  return result;
}
}  // namespace

WeightedRuntime WeightedRuntime::create_into(const resource::MemoryAccount& account,
    const PhysicalPlan& shape, weighted::Options options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  return WeightedRuntime(Impl::create(shape,options,account));
}
WeightedRuntime WeightedRuntime::create_into(const resource::MemoryAccount& account,
    const CompiledProgram& shape, weighted::Options options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  return WeightedRuntime(Impl::create(shape,options,account));
}
WeightedRuntime::WeightedRuntime(PhysicalPlan shape, weighted::Options options):impl_(Impl::create(shape,options)) {}
WeightedRuntime::WeightedRuntime(CompiledProgram shape, weighted::Options options):impl_(Impl::create(shape,options)) {}
WeightedRuntime::WeightedRuntime(WeightedRuntime&&) noexcept=default;
WeightedRuntime& WeightedRuntime::operator=(WeightedRuntime&&) noexcept=default;
WeightedRuntime::~WeightedRuntime()=default;
WeightedRuntime::Impl& WeightedRuntime::impl() const {require(bool(impl_),"invalid_runtime","weighted runtime was moved from");return *impl_;}
const CompiledProgram& WeightedRuntime::structural_program() const & {return impl().program;}
const weighted::Binding& WeightedRuntime::binding() const & {return impl().binding;}
const weighted::Options& WeightedRuntime::options() const {return impl().options;}
std::uint64_t WeightedRuntime::owner() const {return impl().account().statistics().owner;}
std::uint64_t WeightedRuntime::sequence() const {return impl().sequence;}
std::string_view WeightedRuntime::engine() const {return impl().keyed?"keyed_v1":"reference_v1";}
bool WeightedRuntime::ready() const {const auto& d=impl();return !d.updating && d.readers==0;}
Multiplicity WeightedRuntime::root_weight() const {const auto& d=impl();d.readable();return d.summary();}
std::optional<Attempt> WeightedRuntime::last_attempt() const {return impl().last;}
resource::MemoryStatistics WeightedRuntime::accounted_memory_statistics() const {return impl().account().statistics();}
WeightedRuntime::PendingEpoch WeightedRuntime::begin_epoch(std::uint64_t sequence) {
  return begin_epoch(sequence,DeltaCapture::disabled);
}
WeightedRuntime::PendingEpoch WeightedRuntime::begin_epoch(std::uint64_t sequence, DeltaCapture capture) {
  auto& d=impl();d.readable();
  require(d.readers==0,"runtime_busy","a weighted result cursor has leased the epoch");
  require(d.sequence!=UINT64_MAX && sequence==d.sequence+1,"invalid_sequence","weighted logical sequence must be contiguous from one");
  detail::StorageOperation operation(d.context);
  auto data=resource::make_accounted_unique<PendingEpoch::Data>(d.account(),resource::MemoryPurpose::journal_undo,impl_,sequence,capture);
  d.updating=true;return PendingEpoch(std::move(data));
}
bool WeightedRuntime::fused_available() const noexcept { return impl_ && impl_->keyed; }
void WeightedRuntime::fused_begin(std::uint64_t sequence) {
  auto& d=impl();d.readable();
  require(bool(d.keyed),"fused_unavailable","fused epochs need the keyed core");
  require(d.readers==0,"runtime_busy","a weighted result cursor has leased the epoch");
  require(d.sequence!=UINT64_MAX && sequence==d.sequence+1,"invalid_sequence","weighted logical sequence must be contiguous from one");
  d.keyed->begin();
  d.updating=true;d.fused_open=true;d.fused_changed=false;d.fused_sequence=sequence;d.fused_before=d.summary();
}
void WeightedRuntime::fused_stage(NodeId id, storage::RowView values, Multiplicity before, Multiplicity after,
    keyed::WeightSink* sink) {
  auto& d=impl();
  require(d.fused_open,"invalid_epoch","no fused weighted epoch is open");
  require(id.value<d.program.nodes().size(),"invalid_native_update","weighted native node is outside the shape");
  const auto& node=d.program.nodes()[id.value];
  require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes have no weighted input port");
  const auto issue=node.layout.validation_issue_view(storage::TupleValuesView::borrow(values));
  if (!issue.ok()) throw storage::TupleValidationFailure(issue);
  static_cast<void>(d.policy.add(after,{}));
  if (before==after) return;
  d.keyed->stage_weight(static_cast<std::uint32_t>(id.value),values,before.value,after.value,sink);
  d.fused_changed=true;
}
Epoch WeightedRuntime::fused_commit() {
  auto& d=impl();
  require(d.fused_open,"invalid_epoch","no fused weighted epoch is open");
  d.keyed->commit();
  d.fused_open=false;d.updating=false;d.sequence=d.fused_sequence;
  d.last=Attempt{d.sequence,Phase::committed,{}};
  return Epoch{d.sequence,d.fused_changed,d.fused_before,d.summary(),{},nullptr};
}
void WeightedRuntime::fused_rollback() noexcept {
  if (!impl_ || !impl_->fused_open) return;
  auto& d=*impl_;
  d.keyed->rollback();
  d.fused_open=false;d.updating=false;
  d.last=Attempt{d.fused_sequence,Phase::aborted,{}};
}
Epoch WeightedRuntime::apply(const Update& update) {
  auto pending=begin_epoch(update.sequence);static_cast<void>(pending.stage(update.replacement));return pending.commit();
}
Snapshot WeightedRuntime::snapshot(SnapshotLimits limits) const {
  auto& d=impl();d.readable();
  if (d.keyed) {
    const auto twin=d.reference_twin();detail::StorageOperation operation(twin->context);
    return capture_weighted(*twin,d.sequence,false,limits,[&](RelationId id){return twin->storage.table(id).live(twin->allowance());});
  }
  detail::StorageOperation operation(d.context);
  return capture_weighted(d,d.sequence,false,limits,[&](RelationId id){return d.storage.table(id).live(d.allowance());});
}
WeightedRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
WeightedRuntime::PendingEpoch::PendingEpoch(PendingEpoch&&) noexcept=default;
WeightedRuntime::PendingEpoch& WeightedRuntime::PendingEpoch::operator=(PendingEpoch&&) noexcept=default;
WeightedRuntime::PendingEpoch::~PendingEpoch()=default;
bool WeightedRuntime::PendingEpoch::active() const noexcept {return data_ && bool(data_->owner);}
void WeightedRuntime::PendingEpoch::rollback() noexcept {if(data_)data_->rollback();}
bool WeightedRuntime::PendingEpoch::stage(const Replacement& replacement) {
  return stage_native(replacement.node,storage::TupleValuesView::borrow(replacement.values),
      replacement.before,replacement.after,false);
}
bool WeightedRuntime::PendingEpoch::stage_contribution(NodeId node, storage::TupleValuesView values,
    Multiplicity before, Multiplicity after) {
  return stage_native(node,std::move(values),before,after,true);
}
bool WeightedRuntime::PendingEpoch::stage_native(NodeId id, storage::TupleValuesView values,
    Multiplicity old, Multiplicity next, bool contribution) {
  require(active(),"invalid_epoch","weighted epoch is closed");
  if (data_->keyed) try {
    auto& d=data_->active();
    require(id.value<d.program.nodes().size(),"invalid_native_update","weighted native node is outside the shape");
    const auto& node=d.program.nodes()[id.value];
    require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes have no weighted input port");
    const auto issue=node.layout.validation_issue_view(values);
    if (!issue.ok()) throw storage::TupleValidationFailure(issue);
    storage::RowView row;
    if (const auto native=values.native_view()) row=*native;
    else {
      auto& cells=data_->keyed_cells;cells.clear();
      for (const auto value:values) cells.push_back(value);
      row=storage::RowView::borrow(cells);
    }
    data_->metric(data_->output.metrics.native_inputs);
    static_cast<void>(d.policy.add(next,{}));
    const auto current=d.keyed->weight(static_cast<std::uint32_t>(id.value),row);
    if (!contribution) require(current==old.value,"weight_conflict","expected native weight differs from the current row");
    const auto before=contribution?Multiplicity{current}:old;
    const auto after=contribution?d.policy.replace({current},old,next):next;
    if (before==after) return false;
    // Each changed head tuple folds into this epoch's consolidated capture.
    struct Capture final:keyed::WeightSink {
      Data& epoch;const storage::AccountedLayout& layout;
      Capture(Data& owner,const storage::AccountedLayout& result):epoch(owner),layout(result) {}
      void change(storage::RowView values,std::uint64_t was,std::uint64_t now) override {
        if (!epoch.deltas) return;
        if (epoch.capture_mode==DeltaCapture::support) {
          if ((was==0)==(now==0)) return;
          epoch.deltas->add(layout,values,{now==0,{1}});
        } else epoch.deltas->add(layout,values,{now<was,{now<was?was-now:now-was}});
      }
    } capture(*data_,d.program.result_layout());
    d.keyed->stage_weight(static_cast<std::uint32_t>(id.value),row,before.value,after.value,&capture);
    data_->metric(data_->output.metrics.native_changes);data_->output.changed=true;
    data_->output.after=d.summary();
    return true;
  } catch (...) {rollback();throw;}
  try {
    auto& d=data_->active();detail::StorageOperation operation(d.context,data_->lease);
    require(id.value<d.program.nodes().size(),"invalid_native_update","weighted native node is outside the shape");
    const auto& node=d.program.nodes()[id.value];
    require(node.kind==NodeKind::native,"invalid_native_update","generalized nodes have no weighted input port");
    auto tuple=node.layout.tuple_view(std::move(values));
    const auto before=data_->output.metrics.native_changes;
    const auto kind=contribution ? Data::PendingKind::native_contribution : Data::PendingKind::native_weight;
    data_->enqueue({kind,node.id,{},{},std::move(tuple),old,next,0,0});
    data_->drain();return data_->output.metrics.native_changes!=before;
  } catch (...) {rollback();throw;} // The sole abort boundary; preserve error type.
}
std::optional<std::span<const BagDelta>> WeightedRuntime::PendingEpoch::bag_delta_preview() const {
  require(active(),"invalid_epoch","weighted epoch is closed");
  if(!data_->deltas || data_->capture_mode!=DeltaCapture::enabled)return std::nullopt;
  return std::span<const BagDelta>(data_->deltas->rows);
}
std::optional<std::span<const BagDelta>> WeightedRuntime::PendingEpoch::support_delta_preview() const {
  require(active(),"invalid_epoch","weighted epoch is closed");
  if(!data_->deltas || data_->capture_mode!=DeltaCapture::support)return std::nullopt;
  return std::span<const BagDelta>(data_->deltas->rows);
}
std::span<const BagDelta> weighted::SupportDeltas::entries() const & {
  require(bool(data_),"support_capture_disabled","weighted support capture was disabled");return data_->rows;
}
const BagDeltaMetrics& weighted::SupportDeltas::metrics() const & {
  require(bool(data_),"support_capture_disabled","weighted support capture was disabled");return data_->metrics;
}
std::span<const BagDelta> weighted::BagDeltas::entries() const & {
  require(bool(data_),"delta_capture_disabled","weighted delta capture was disabled");return data_->rows;
}
const BagDeltaMetrics& weighted::BagDeltas::metrics() const & {
  require(bool(data_),"delta_capture_disabled","weighted delta capture was disabled");return data_->metrics;
}
const Epoch& WeightedRuntime::PendingEpoch::preview() const {require(active(),"invalid_epoch","weighted epoch is closed");return data_->output;}
Snapshot WeightedRuntime::PendingEpoch::snapshot(SnapshotLimits limits) const {
  require(active(),"invalid_epoch","weighted epoch is closed");auto& d=data_->active();
  if (data_->keyed) {
    const auto twin=d.reference_twin();detail::StorageOperation operation(twin->context);
    return capture_weighted(*twin,data_->output.sequence,true,limits,[&](RelationId id){return twin->storage.table(id).live(twin->allowance());});
  }
  detail::StorageOperation operation(d.context,data_->lease);
  auto result=capture_weighted(d,data_->output.sequence,true,limits,[&](RelationId id){return data_->live(id);});
  data_->sample_grant();return result;
}
Epoch WeightedRuntime::PendingEpoch::commit() {
  require(active(),"invalid_epoch","weighted epoch is closed");auto& d=data_->active();
  // All arithmetic/allocation/draining finished in stage(). Publication and
  // rollback use funded journals/node handles; no exception translation here.
  if (data_->keyed) {d.keyed->commit();data_->keyed=false;}
  data_->sample_grant();
  data_->delta_walk.reset();
  if(data_->deltas) {
    data_->deltas->publish();
    if(data_->capture_mode==DeltaCapture::support)
      data_->output.support_deltas=SupportDeltas(std::move(data_->deltas));
    else data_->output.bag_deltas=BagDeltas(std::move(data_->deltas));
  }
  for (auto& [id,table]:data_->tables) {static_cast<void>(id);table.commit();}
  if (data_->journal) data_->journal->phase=Phase::committed;
  d.sequence=data_->output.sequence;
  d.last=Attempt{d.sequence,Phase::committed,data_->output.metrics};d.updating=false;
  data_->tables.clear();data_->undo.clear();
  auto result=std::move(data_->output);data_->journal.reset();data_->owner.reset();data_->lease.reset();return result;
}
}  // namespace crown::runtime
