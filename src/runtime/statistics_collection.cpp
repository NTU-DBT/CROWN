#include "statistics_collection.hpp"
#include <algorithm>
#include <bit>
#include <limits>
#include <stdexcept>

namespace crown::runtime::workload {
namespace {
constexpr U64 maximum = std::numeric_limits<U64>::max();
void add(U64& dst, U64 n, bool& saturated) noexcept {
  if (n > maximum - dst) { dst = maximum; saturated = true; }
  else dst += n;
}
void inc(U64& dst, bool& saturated) noexcept { add(dst, 1, saturated); }
}
void Cell::observe(U64 v) noexcept {
  if (!count) min = max = v;
  else { min = std::min(min,v); max = std::max(max,v); }
  inc(count,saturated); add(sum,v,saturated);
  inc(bins[static_cast<std::size_t>(std::bit_width(v))],saturated);
}
void Cell::merge(const Cell& c) noexcept {
  if (c.count) {
    if (!count) { min=c.min; max=c.max; }
    else { min=std::min(min,c.min); max=std::max(max,c.max); }
  }
  saturated = saturated || c.saturated;
#define ADD(field) add(field,c.field,saturated)
  ADD(inputs); ADD(changed); ADD(noop); ADD(visited); ADD(accepted); ADD(rejected);
  ADD(complete_detail_inputs);
  ADD(changes); ADD(zero_to_positive); ADD(positive_to_zero); ADD(count); ADD(sum);
#undef ADD
  for (std::size_t i=0; i<bins.size(); ++i) add(bins[i],c.bins[i],saturated);
}
} // namespace crown::runtime::workload
namespace crown::runtime::statistics_collection {
namespace {
constexpr U64 maximum = std::numeric_limits<U64>::max();
void inc(U64& value, bool& saturated) noexcept {
  if (value==maximum) saturated=true; else ++value;
}
bool valid(Kind k) { return k == Kind::physical || k == Kind::logical || k == Kind::occurrence || k == Kind::support || k == Kind::degree; }
bool valid(Operation o) { return o == Operation::insert || o == Operation::erase; }
bool root(Kind k) noexcept { return k==Kind::physical || k==Kind::logical; }
}
Collector::Collector():Collector(resource::MemoryAccount::create(std::numeric_limits<U64>::max())) {}
Collector::Collector(const resource::MemoryAccount& account)
    :descriptors_(resource::MemoryAllocator<Descriptor>(account,resource::MemoryPurpose::observation,memory_owner)),
     committed_(resource::MemoryAllocator<Cell>(account,resource::MemoryPurpose::observation,memory_owner)),
     attempt_(committed_.get_allocator()),previous_(committed_.get_allocator()) {}
void Collector::configure(Options o, std::span<const Descriptor> ds, std::size_t external_bytes) {
  if (pending()) throw std::logic_error("statistics pending");
  if (o.mode != Mode::off && o.mode != Mode::counters) throw std::invalid_argument("statistics mode");
  if (!o.period || o.offset >= o.period) throw std::invalid_argument("statistics sampling");
  if (o.mode == Mode::off && !ds.empty()) throw std::invalid_argument("off descriptors");
  constexpr auto limit = std::numeric_limits<std::size_t>::max();
  if (external_bytes>limit-sizeof(Collector)) throw std::length_error("statistics routing capacity bound");
  constexpr auto bytes_per = sizeof(Descriptor) + 3*sizeof(Cell);
  if (ds.size() > o.max_cells || ds.size() > (limit-sizeof(Collector))/bytes_per)
    throw std::length_error("statistics cell bound");
  for (std::size_t i=0; i<ds.size(); ++i) {
    if (!valid(ds[i].kind) || !valid(ds[i].operation) || (root(ds[i].kind) && ds[i].scope != 0))
      throw std::invalid_argument("statistics descriptor");
    for (std::size_t j=0; j<i; ++j)
      if (ds[i] == ds[j]) throw std::invalid_argument("duplicate statistics descriptor");
    if (!root(ds[i].kind)) {
      bool parent=false;
      for (const auto& d: ds) if (root(d.kind) && d.table==ds[i].table && d.operation==ds[i].operation && d.input_scope==ds[i].input_scope) parent=true;
      if (!parent) throw std::invalid_argument("unbound statistics descriptor");
    }
  }
  // All possible throwing operations precede publication.
  MemoryVector<Descriptor> descriptors(ds.begin(),ds.end(),descriptors_.get_allocator());
  MemoryVector<Cell> committed(ds.size(),Cell{},committed_.get_allocator());
  MemoryVector<Cell> attempt(ds.size(),Cell{},attempt_.get_allocator());
  MemoryVector<Cell> previous(ds.size(),Cell{},previous_.get_allocator());
  // Actual capacities (not just sizes) must also fit the accounting domain.
  std::size_t bytes=sizeof(Collector)+external_bytes;
  const auto charge=[&](std::size_t cap, std::size_t width) {
    if (cap > (limit-bytes)/width) throw std::length_error("statistics capacity bound");
    bytes += cap*width;
  };
  charge(descriptors.capacity(),sizeof(Descriptor));
  charge(committed.capacity(),sizeof(Cell)); charge(attempt.capacity(),sizeof(Cell)); charge(previous.capacity(),sizeof(Cell));
  descriptors_.swap(descriptors); committed_.swap(committed); attempt_.swap(attempt); previous_.swap(previous);
  options_=o;
  reset();
}
void Collector::clear(MemoryVector<Cell>& slab) noexcept {
  for (auto& c:slab) { c={}; inc(meta_.cleared_cells,meta_.saturated); }
}
Ticket Collector::admit(std::size_t physical) noexcept {
  // Root attempts clear the whole scratch slab, including unsampled inputs.
  // Sampling avoids detail hooks, not this dense lifecycle/census work.
  if (options_.mode==Mode::off) return {};
  if (pending()) { meta_.protocol_error=true; poisoned_=true; return {}; }
  if (serial_==maximum || ordinal_done_) { meta_.ordinal_exhausted=true; return {}; }
  active_serial_=++serial_; depth_=1; physical_=physical; actions_=0; poisoned_=false; truncated_=false;
  input_staged_=false;
  selected_=(ordinal_%options_.period)==options_.offset;
  if (ordinal_==maximum) ordinal_done_=true; else ++ordinal_;
  inc(meta_.attempts,meta_.saturated);
  if (selected_) inc(meta_.selected,meta_.saturated);
  clear(attempt_);
  if (physical>=descriptors_.size() || !root(descriptors_[physical].kind)) {
    meta_.invalid_descriptor=true; poisoned_=true;
  }
  return {active_serial_,depth_,0};
}
void Collector::physical_fact(bool changed) noexcept {
  if (options_.mode==Mode::off) return;
  if (!pending() || input_staged_ || physical_>=descriptors_.size() || descriptors_[physical_].kind!=Kind::physical) {
    meta_.protocol_error=true; if (pending()) poisoned_=true; return;
  }
  auto& c=attempt_[physical_]; c.inputs=1; c.changed=changed?1:0; c.noop=changed?0:1; input_staged_=true;
}
void Collector::logical_fact(bool changed) noexcept {
  if (options_.mode==Mode::off) return;
  if (!pending() || input_staged_ || physical_>=descriptors_.size() || descriptors_[physical_].kind!=Kind::logical) {
    meta_.protocol_error=true; if (pending()) poisoned_=true; return;
  }
  auto& c=attempt_[physical_]; c.inputs=1; c.changed=changed?1:0; c.noop=changed?0:1; input_staged_=true;
}
Ticket Collector::begin(std::size_t physical, bool changed) noexcept {
  auto ticket=admit(physical);
  if (ticket.serial) physical_fact(changed);
  return ticket;
}
Ticket Collector::nest(Ticket t) noexcept {
  if (options_.mode==Mode::off) return {};
  if (!pending() || t.serial!=active_serial_ || t.depth!=depth_ || depth_==maximum || serial_==maximum) {
    meta_.protocol_error=true; if (pending()) poisoned_=true; return {};
  }
  const U64 parent=active_serial_;
  active_serial_=++serial_;
  return {active_serial_,++depth_,parent};
}
bool Collector::finish(Ticket t, bool commit) noexcept {
  // Only complete selected detail merges; committed root facts stay separate.
  // Root merge/clear scans are nonallocating but proportional to cell count.
  if (options_.mode==Mode::off) return true;
  if (!pending() || t.serial!=active_serial_ || t.depth!=depth_) {
    meta_.protocol_error=true; if (pending()) poisoned_=true; return false;
  }
  if (!commit) poisoned_=true;
  active_serial_=t.parent;
  if (--depth_) return !poisoned_;
  if (!input_staged_ && !poisoned_) { meta_.protocol_error=true; poisoned_=true; }
  const bool publish=!poisoned_;
  if (truncated_) inc(meta_.truncated,meta_.saturated);
  if (publish) {
    inc(meta_.committed,meta_.saturated);
    if (truncated_) inc(meta_.committed_truncated,meta_.saturated);
    if (selected_ && !truncated_) inc(meta_.complete,meta_.saturated);
    if (selected_ && !truncated_) attempt_[physical_].complete_detail_inputs=1;
    for (std::size_t i=0;i<attempt_.size();++i) {
      if (root(descriptors_[i].kind) || (selected_ && !truncated_)) {
        committed_[i].merge(attempt_[i]); inc(meta_.merged_cells,meta_.saturated);
      }
    }
  } else {
    inc(meta_.aborted,meta_.saturated);
    if (selected_) inc(meta_.aborted_selected,meta_.saturated);
  }
  clear(attempt_);
  return publish;
}
Cell* Collector::detail(std::size_t i, Kind kind) noexcept {
  if (options_.mode==Mode::off) return nullptr;
  inc(meta_.guards,meta_.saturated);
  if (!pending()) { meta_.protocol_error=true; return nullptr; }
  if (i>=descriptors_.size() || descriptors_[i].kind!=kind || physical_>=descriptors_.size() ||
      descriptors_[i].table!=descriptors_[physical_].table || descriptors_[i].operation!=descriptors_[physical_].operation ||
      descriptors_[i].input_scope!=descriptors_[physical_].input_scope) {
    meta_.invalid_descriptor=true; truncated_=true; return nullptr;
  }
  if (poisoned_ || !selected_ || truncated_) return nullptr;
  // A physical no-op has no alias/support activity. Erroneous hooks invalidate
  // detailed coverage but preserve independently known physical input facts.
  if (attempt_[physical_].noop) { meta_.protocol_error=true; truncated_=true; return nullptr; }
  if (actions_==options_.detail_budget) { truncated_=true; return nullptr; }
  ++actions_; inc(meta_.detail_actions,meta_.saturated);
  return &attempt_[i];
}
void Collector::occurrence(std::size_t i, bool accepted) noexcept {
  if (auto* c=detail(i,Kind::occurrence)) {
    inc(c->visited,c->saturated); inc(accepted?c->accepted:c->rejected,c->saturated);
  }
}
void Collector::support(std::size_t i, U64 before, U64 after) noexcept {
  if (auto* c=detail(i,Kind::support)) {
    if (before==after) return;
    inc(c->changes,c->saturated);
    if (!before && after) inc(c->zero_to_positive,c->saturated);
    if (before && !after) inc(c->positive_to_zero,c->saturated);
    c->observe(after);
  }
}
void Collector::degree(std::size_t i, U64 value) noexcept {
  if (auto* c=detail(i,Kind::degree)) c->observe(value);
}
bool Collector::reset() noexcept {
  if (pending()) return false;
  meta_={}; previous_meta_={}; clear(committed_); clear(attempt_); clear(previous_);
  ordinal_=0; ordinal_done_=false; actions_=0; selected_=truncated_=poisoned_=false;
  has_previous_=replaced_history_=false; configuration_=previous_configuration_=0;
  inc(generation_,generation_saturated_);
  return true;
}
bool Collector::rotate(U64 configuration, bool force) noexcept {
  if (pending()) return false;
  if (options_.mode==Mode::off || (!force && configuration==configuration_)) return true;
  previous_meta_=meta_; meta_={};
  committed_.swap(previous_); clear(committed_); clear(attempt_);
  replaced_history_=has_previous_; has_previous_=true;
  previous_configuration_=configuration_; configuration_=configuration;
  ordinal_=0; ordinal_done_=false;
  return true;
}
Memory Collector::memory() const noexcept {
  // Component payload capacity only: account framing, producer route storage
  // and separately allocated detached snapshots are outside this report.
  Memory m{sizeof(Collector), descriptors_.capacity()*sizeof(Descriptor),
    committed_.capacity()*sizeof(Cell),attempt_.capacity()*sizeof(Cell),previous_.capacity()*sizeof(Cell),0};
  m.retained_payload_bytes=m.descriptors_bytes+m.committed_bytes+m.attempt_bytes+m.previous_bytes;
  return m;
}
} // namespace crown::runtime::statistics_collection
