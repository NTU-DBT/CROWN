#include "workload_statistics_detail.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace crown::runtime::workload {
namespace {
constexpr auto maximum=std::numeric_limits<std::size_t>::max();
std::size_t plus(std::size_t a,std::size_t b) {
  if (b>maximum-a) throw std::length_error("statistics descriptor arithmetic");
  return a+b;
}
std::size_t times(std::size_t a,std::size_t b) {
  if (b && a>maximum/b) throw std::length_error("statistics route arithmetic");
  return a*b;
}
void increment(U64& value,bool& saturated) noexcept {
  if (value==UINT64_MAX) saturated=true; else ++value;
}
std::size_t operation(SetOperation op) noexcept { return op==SetOperation::erase?1:0; }
bool degraded(const Metadata& m) noexcept { return m.invalid_descriptor || m.protocol_error || m.ordinal_exhausted; }
Availability fraction_status(Availability status) noexcept {
  return status==Availability::lower_bound?Availability::unavailable:status;
}
}
struct Snapshot::Data {
  // Detached numeric copies plus owning plan metadata; never runtime rows or
  // pointers. Report allocations are separate from reported collector payload.
  CompiledProgram plan;
  Stamp stamp;
  Options options;
  ModeFacts modes, previous_modes;
  statistics_collection::MemoryVector<Descriptor> descriptors;
  statistics_collection::MemoryVector<Cell> cells, previous;
  Metadata metadata, previous_metadata;
  Memory memory;
  bool pending{}, has_previous{}, replaced{};
  U64 previous_start{}, previous_end{};
  Data(CompiledProgram p,SupportOwnerId owner):plan(std::move(p)),stamp{owner},
      descriptors(resource::MemoryAllocator<Descriptor>(plan.account(),resource::MemoryPurpose::capture,{resource::MemoryOwnerKind::capture,1})),
      cells(resource::MemoryAllocator<Cell>(plan.account(),resource::MemoryPurpose::capture,{resource::MemoryOwnerKind::capture,1})),
      previous(cells.get_allocator()) {}
};
const CompiledProgram& Snapshot::plan() const noexcept { return data_->plan; }
const Stamp& Snapshot::stamp() const noexcept { return data_->stamp; }
const Options& Snapshot::options() const noexcept { return data_->options; }
const ModeFacts& Snapshot::modes() const noexcept { return data_->modes; }
const ModeFacts& Snapshot::previous_modes() const noexcept { return data_->previous_modes; }
std::span<const Descriptor> Snapshot::descriptors() const noexcept { return data_->descriptors; }
std::span<const Cell> Snapshot::cells() const noexcept { return data_->cells; }
std::span<const Cell> Snapshot::previous_cells() const noexcept { return data_->previous; }
const Metadata& Snapshot::metadata() const noexcept { return data_->metadata; }
const Metadata& Snapshot::previous_metadata() const noexcept { return data_->previous_metadata; }
const Memory& Snapshot::memory() const noexcept { return data_->memory; }
bool Snapshot::pending() const noexcept { return data_->pending; }
bool Snapshot::has_previous() const noexcept { return data_->has_previous; }
bool Snapshot::replaced_history() const noexcept { return data_->replaced; }
U64 Snapshot::previous_interval_start_epoch() const noexcept { return data_->previous_start; }
U64 Snapshot::previous_interval_end_epoch() const noexcept { return data_->previous_end; }
Snapshot Snapshot::with_pending() const {
  // This marker requires a deep copy of the report arrays on the same account;
  // the original snapshot and committed collector remain unchanged.
  auto copy=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,1},data_->plan.account(),
      resource::MemoryPurpose::capture,*data_);copy->pending=true;return Snapshot(std::move(copy));
}
Availability Snapshot::detail_availability() const noexcept {
  if (options().mode==Mode::off) return Availability::disabled;
  if (metadata().saturated) return Availability::lower_bound;
  for (const auto& cell:cells()) if (cell.saturated) return Availability::lower_bound;
  if (metadata().committed_truncated || degraded(metadata())) return Availability::incomplete;
  return options().period==1?Availability::exact:Availability::sampled;
}
Fraction Snapshot::input_share(std::size_t id) const noexcept {
  if (options().mode==Mode::off) return {0,0,Availability::disabled};
  if (id>=descriptors().size() || descriptors()[id].kind!=Kind::physical) return {};
  U64 total=0; bool saturated=false;
  for (std::size_t i=0;i<descriptors().size();++i) if (descriptors()[i].kind==Kind::physical) {
    const auto& c=cells()[i]; saturated=saturated || c.saturated;
    if (c.inputs>UINT64_MAX-total) { total=UINT64_MAX; saturated=true; } else total+=c.inputs;
  }
  return {cells()[id].inputs,total,(!total || saturated)?Availability::unavailable:
      degraded(metadata())?Availability::incomplete:Availability::exact,DenominatorScope::all_committed_physical_inputs};
}
Fraction Snapshot::events_per_physical_input(std::size_t id) const noexcept {
  if (options().mode==Mode::off) return {0,0,Availability::disabled};
  if (id>=descriptors().size() || descriptors()[id].input_scope!=InputScope::physical_table) return {};
  const auto& descriptor=descriptors()[id]; const auto& cell=cells()[id];
  U64 numerator=descriptor.kind==Kind::occurrence?cell.visited:
      descriptor.kind==Kind::support?cell.changes:descriptor.kind==Kind::degree?cell.count:cell.inputs;
  for (std::size_t i=0;i<descriptors().size();++i) {
    const auto& root=descriptors()[i];
    if (root.kind==Kind::physical && root.table==descriptor.table && root.operation==descriptor.operation) {
      const auto& base=cells()[i];
      auto status=descriptor.kind==Kind::physical?Availability::exact:detail_availability();
      if (degraded(metadata())) status=Availability::incomplete;
      const auto denominator=descriptor.kind==Kind::physical?base.inputs:base.complete_detail_inputs;
      if (cell.saturated || base.saturated || !denominator) status=Availability::unavailable;
      return {numerator,denominator,fraction_status(status),descriptor.kind==Kind::physical?
          DenominatorScope::committed_physical_stratum:DenominatorScope::complete_detail_sample_physical_stratum};
    }
  }
  return {};
}
Fraction Snapshot::crossing_fraction(std::size_t id) const noexcept {
  if (options().mode==Mode::off) return {0,0,Availability::disabled};
  if (id>=descriptors().size() || descriptors()[id].kind!=Kind::support) return {};
  const auto& c=cells()[id]; bool saturated=c.saturated;
  const auto numerator=c.positive_to_zero>UINT64_MAX-c.zero_to_positive?
      (saturated=true,UINT64_MAX):c.zero_to_positive+c.positive_to_zero;
  return {numerator,c.changes,(!c.changes || saturated)?Availability::unavailable:fraction_status(detail_availability()),
      DenominatorScope::observed_support_count_changes};
}
Fraction Snapshot::adapter_selectivity(std::size_t id) const noexcept {
  if (options().mode==Mode::off) return {0,0,Availability::disabled};
  if (id>=descriptors().size() || descriptors()[id].kind!=Kind::occurrence) return {};
  const auto& c=cells()[id];
  return {c.accepted,c.visited,(!c.visited || c.saturated)?Availability::unavailable:fraction_status(detail_availability()),
      DenominatorScope::observed_visited_routes};
}

template<class Plan> void detail::State::configure(const Plan& plan,bool physical,const Options& options,U64 sequence) {
  if (options.mode!=Mode::off && options.mode!=Mode::counters) throw std::invalid_argument("statistics mode");
  if (!options.period || options.offset>=options.period) throw std::invalid_argument("statistics sampling");
  // Every route position has a validated dense native ID; allocation is confined
  // to this quiescent barrier. No query row or native binding hash is inspected.
  const auto ni=plan.inputs().size(), nn=plan.nodes().size(), ne=plan.edges().size();
  const auto derivation=plus(1,ni), survivor=plus(derivation,ni), parent=plus(survivor,nn);
  const auto visible=plus(parent,nn), edges=plus(visible,nn), stride=plus(edges,times(ne,2));
  const auto groups=physical?times(plan.source_catalog().tables.size(),2):2;
  statistics_collection::MemoryVector<Descriptor> descriptors(resource::MemoryAllocator<Descriptor>(
      collector_.memory_account(),resource::MemoryPurpose::scratch,statistics_collection::memory_owner));
  statistics_collection::MemoryVector<std::size_t> routes(routes_.get_allocator());
  if (options.mode!=Mode::off) {
    if (physical && plan.base_routes().size()!=plan.source_catalog().tables.size())
      throw std::invalid_argument("statistics catalog route shape");
    std::size_t visible_count=0;
    for (std::size_t n=0;n<nn;++n) {
      const auto& node=plan.nodes()[n];
      if (node.id.value!=n) throw std::invalid_argument("statistics node identity");
      if (node.visible_relation) ++visible_count;
    }
    for (std::size_t i=0;i<ni;++i) {
      const auto& input=plan.inputs()[i];
      if (input.occurrence.value!=i || input.node.value>=nn || input.base.value>=plan.source_catalog().tables.size() ||
          plan.nodes()[input.node.value].occurrence!=input.occurrence)
        throw std::invalid_argument("statistics occurrence identity");
      const auto& native=plan.base_routes()[input.base.value];
      if (std::count(native.begin(),native.end(),input.occurrence)!=1)
        throw std::invalid_argument("statistics occurrence route");
    }
    for (std::size_t t=0;t<plan.base_routes().size();++t) for (const auto id:plan.base_routes()[t])
      if (id.value>=ni || plan.inputs()[id.value].base.value!=t)
        throw std::invalid_argument("statistics base route identity");
    for (const auto& edge:plan.edges()) {
      if (edge.parent.value>=nn || edge.child.value>=nn ||
          edge.child_slot>=plan.nodes()[edge.parent.value].children.size() ||
          plan.nodes()[edge.parent.value].children[edge.child_slot]!=edge.child ||
          (edge.reverse_index && edge.reverse_index->value>=plan.indexes().size()))
        throw std::invalid_argument("statistics edge identity");
    }
    const auto per_group=plus(plus(1,times(nn,2)),plus(visible_count,times(ne,2)));
    const auto required=plus(times(groups,per_group),physical?times(ni,4):0);
    if (required>options.max_cells) throw std::length_error("statistics complete strata exceed max_cells");
    // Check all component payload arithmetic before any allocation.
    const auto route_count=times(groups,stride);
    static_cast<void>(plus(sizeof(State),plus(times(route_count,sizeof(std::size_t)),
        times(required,plus(sizeof(Descriptor),times(3,sizeof(Cell)))))));
    descriptors.reserve(required); routes.assign(route_count,absent);
    for (std::size_t group=0;group<groups;++group) {
      const auto table=physical?static_cast<U64>(group/2):UINT64_MAX;
      const auto op=(group%2)==0?Operation::insert:Operation::erase;
      const auto input_scope=physical?InputScope::physical_table:InputScope::logical_epoch;
      const auto append=[&](std::size_t local,Kind kind,Role role,std::optional<NodeId> node={},
          std::optional<OccurrenceId> occurrence={},std::optional<std::size_t> edge={},
          std::optional<IndexRequirementId> index={},std::optional<Operation> sign={}) {
        routes[group*stride+local]=descriptors.size();
        descriptors.push_back({kind,table,static_cast<U64>(local),op,input_scope,role,node,occurrence,edge,index,sign});
      };
      append(0,physical?Kind::physical:Kind::logical,Role::input);
      if (physical) for (const auto& input:plan.inputs()) if (input.base.value==group/2) {
        append(1+input.occurrence.value,Kind::occurrence,Role::adapter,input.node,input.occurrence);
        append(derivation+input.occurrence.value,Kind::support,Role::derivation,input.node,input.occurrence);
      }
      for (const auto& node:plan.nodes()) {
        append(survivor+node.id.value,Kind::support,Role::survivor,node.id);
        append(parent+node.id.value,Kind::support,Role::parent_support,node.id);
        if (node.visible_relation) append(visible+node.id.value,Kind::support,Role::visible_support,node.id);
      }
      for (std::size_t e=0;e<ne;++e) {
        const auto& edge=plan.edges()[e];
        const auto role=plan.nodes()[edge.parent.value].kind==NodeKind::native?Role::native_touched_degree:Role::generalized_probe;
        for (std::size_t sign=0;sign<2;++sign)
          append(edges+2*e+sign,Kind::degree,role,edge.parent,{},e,edge.reverse_index,sign==0?Operation::insert:Operation::erase);
      }
    }
    if (descriptors.size()!=required) throw std::invalid_argument("statistics complete strata mismatch");
  }
  // Collector allocation/validation has a strong guarantee. No throw follows
  // publication; candidate routing and old/new overlap are temporary overhead.
  collector_.configure(options,descriptors,plus(sizeof(State)-sizeof(statistics_collection::Collector),
      times(routes.capacity(),sizeof(std::size_t))));
  routes_.swap(routes); stride_=stride; occurrence_offset_=1; derivation_offset_=derivation;
  survivor_offset_=survivor; parent_offset_=parent; visible_offset_=visible; edge_offset_=edges;
  physical_owner_=physical; active_group_=0; interval_start_=sequence; previous_start_=previous_end_=0;
  previous_modes_={}; segment_=0; segment_saturated_=false;
  increment(configuration_generation_,configuration_saturated_);
}
void detail::State::reset(U64 sequence) noexcept {
  if (!collector_.reset()) return;
  interval_start_=sequence; previous_start_=previous_end_=0; previous_modes_={}; segment_=0; segment_saturated_=false;
}
std::size_t detail::State::route(std::size_t local) const noexcept {
  if (local>=stride_ || !stride_ || active_group_>=routes_.size()/stride_) return absent;
  return routes_[active_group_*stride_+local];
}
detail::Ticket detail::State::enter(std::size_t group) noexcept {
  // Nested admission is constant work; a root admit clears the full attempt
  // slab even when this attempt is not selected for detail sampling.
  if (collector_.options().mode==Mode::off) return {};
  if (collector_.pending()) return collector_.nest(collector_.current_ticket());
  active_group_=group; return collector_.admit(route(0));
}
detail::Ticket detail::State::physical(TableId table,SetOperation op) noexcept {
  if (table.value>(maximum-1)/2) return enter(maximum);
  return enter(table.value*2+operation(op));
}
detail::Ticket detail::State::logical(SetOperation op) noexcept { return enter(operation(op)); }
void detail::State::physical_fact(bool changed) noexcept {
  if (collector_.pending()) collector_.physical_fact(changed);
}
void detail::State::logical_fact(Ticket ticket,bool changed) noexcept {
  if (ticket.serial && ticket.depth==1 && !physical_owner_) collector_.logical_fact(changed);
}
void detail::State::finish(Ticket ticket,bool commit) noexcept {
  // Root completion merges eligible cells and clears the full scratch slab.
  // Preallocation avoids heap work, not the O(cell count) root scan.
  if (ticket.serial) static_cast<void>(collector_.finish(ticket,commit));
}
void detail::State::occurrence(OccurrenceId occurrence,bool accepted) noexcept {
  if (collector_.options().mode==Mode::off) return;
  collector_.occurrence(route(occurrence_offset_+occurrence.value),accepted);
}
void detail::State::derivation(OccurrenceId occurrence,U64 before,U64 after) noexcept {
  if (collector_.options().mode==Mode::off) return;
  collector_.support(route(derivation_offset_+occurrence.value),before,after);
}
void detail::State::support(NodeId node,SupportRole role,U64 before,U64 after) noexcept {
  if (collector_.options().mode==Mode::off) return;
  const auto offset=role==SupportRole::survivors?survivor_offset_:
      role==SupportRole::parent_support?parent_offset_:visible_offset_;
  collector_.support(route(offset+node.value),before,after);
}
void detail::State::touched(std::size_t edge,bool appeared,U64 degree) noexcept {
  if (collector_.options().mode==Mode::off) return;
  collector_.degree(route(edge_offset_+2*edge+(appeared?0:1)),degree);
}
void detail::State::modes(ModeFacts next,U64 sequence,bool initial) noexcept {
  if (initial || !modes_bound_) { modes_=next; modes_bound_=true; return; }
  if (next==modes_) return;
  previous_modes_=modes_; modes_=next;
  previous_start_=interval_start_; previous_end_=sequence; interval_start_=sequence;
  increment(segment_,segment_saturated_);
  // A saturated numeric segment label must not suppress a real boundary.
  static_cast<void>(collector_.rotate(segment_,true));
}
Snapshot detail::State::snapshot(const CompiledProgram& plan,SupportOwnerId owner,U64 sequence,bool pending) const {
  // Explicit allocating capture of committed current/previous numbers. No
  // attempt-private cells, native row payloads or storage pins are exported.
  auto data=resource::make_accounted_shared<Snapshot::Data>({resource::MemoryOwnerKind::capture,1},plan.account(),
      resource::MemoryPurpose::capture,plan,owner);
  data->stamp={owner,sequence,interval_start_,collector_.generation(),configuration_generation_,segment_,1,
      collector_.generation_saturated(),configuration_saturated_,segment_saturated_};
  data->options=collector_.options(); data->modes=modes_; data->previous_modes=previous_modes_;
  data->descriptors.assign(collector_.descriptors().begin(),collector_.descriptors().end());
  data->cells.assign(collector_.committed().begin(),collector_.committed().end());
  data->previous.assign(collector_.previous().begin(),collector_.previous().end());
  data->metadata=collector_.metadata(); data->previous_metadata=collector_.previous_metadata();
  data->memory=collector_.memory(); data->memory.object_bytes=sizeof(State);
  data->memory.routes_bytes=routes_.capacity()*sizeof(std::size_t);
  data->memory.retained_payload_bytes+=data->memory.routes_bytes;
  data->pending=pending || collector_.pending(); data->has_previous=collector_.has_previous();
  data->replaced=collector_.replaced_history(); data->previous_start=previous_start_; data->previous_end=previous_end_;
  return Snapshot(std::move(data));
}
template void detail::State::configure<PhysicalPlan>(const PhysicalPlan&,bool,const Options&,U64);
template void detail::State::configure<CompiledProgram>(const CompiledProgram&,bool,const Options&,U64);
} // namespace crown::runtime::workload
