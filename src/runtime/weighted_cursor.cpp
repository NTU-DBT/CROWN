#include "weighted_detail.hpp"
#include <exception>
#include <algorithm>

// Usage, factor proof and cost boundaries: docs/weighted_enumeration.md.
// Enumerate positive visible keys; each child weight enters one prefix product.
namespace crown::runtime {
namespace {
using namespace weighted;
using weighted_detail::Vector;
using weighted_detail::require;
}

struct WeightedRuntime::ResultCursor::Data {
  struct Frame {
    std::optional<storage::AccountedStorageTable::Cursor> cursor;
    std::optional<storage::AccountedTuple> key;
    const storage::AccountedTuple* selected=nullptr;
    Multiplicity prefix{1};
  };

  // Program/layout/binding remain inspectable after close. Only an active
  // cursor retains mutable runtime state and its one original native grant.
  std::shared_ptr<Impl> owner;
  detail::StorageWorkLease lease;
  CompiledProgram program;
  storage::TupleLayout output_layout;
  Binding binding;
  std::uint64_t owner_id, sequence;
  CursorOptions options;
  CursorMetrics metrics;
  CursorState status=CursorState::active;
  Vector<Frame> frames;
  Vector<storage::ScalarView> row;
  std::size_t position=0;
  bool answer=false, resume=false, leased=false;
  std::unique_ptr<keyed::SetEngine::Cursor> keyed;  // the keyed core's weighted reader

  Data(std::shared_ptr<Impl> runtime, CursorOptions opts)
      :owner(std::move(runtime)),lease(detail::storage_lease(owner->context)),
       program(owner->program),output_layout(program.result_layout().descriptor()),
       binding(owner->binding),owner_id(owner->account().statistics().owner),sequence(owner->sequence),
       options(opts),frames(resource::MemoryAllocator<Frame>(owner->account(),resource::MemoryPurpose::cursor)),
       row(resource::MemoryAllocator<storage::ScalarView>(owner->account(),resource::MemoryPurpose::cursor)) {
    // Reserve traversal/output scratch before publishing a reader. Startup
    // visits no data rows and does not materialize answers or hidden witnesses.
    charge();
    answer=owner->summary().present(); // Immutable for the complete reader lease.
    const auto count=program.enumeration().steps.size();
    frames.reserve(count);
    for (std::size_t i=0;i<count;++i) {
      metric(metrics.frame_initializations);
      frames.emplace_back();
    }
    row.reserve(program.result_layout().fields().size());
    if (owner->keyed) keyed=owner->keyed->open_cursor(false);
    metrics.startup_work=metrics.work;
    sample_grant();
  }
  ~Data() {close(CursorState::cancelled);}

  void charge(std::uint64_t amount=1) {
    require(amount<=UINT64_MAX-metrics.work && (!options.work_limit ||
        (metrics.work<=*options.work_limit && amount<=*options.work_limit-metrics.work)),
        "resource_limit","weighted result cursor work exhausted");
    metrics.work+=amount;
  }
  void metric(std::uint64_t& counter, std::uint64_t amount=1) {
    // Metric-managed counters start at zero and are subsets of total work.
    // Successful charge therefore also proves counter + amount fits.
    charge(amount);
    counter+=amount;
  }
  void sample_grant() noexcept {
    if (!lease || !owner) return;
    const auto& cap=owner->context->limit();
    const auto& left=lease->allowance.get()->remaining();
    metrics.native_grant_consumed={cap.structural_steps-left.structural_steps,cap.scalar_fields-left.scalar_fields,
        cap.scalar_bytes-left.scalar_bytes,cap.pointer_slots-left.pointer_slots,cap.link_actions-left.link_actions};
  }
  void close(CursorState state) noexcept {
    if (status!=CursorState::active) return;
    sample_grant();
    for (const auto& frame:frames) if (frame.cursor) ++metrics.cleanup_frames;
    frames.clear();row.clear();keyed.reset();
    if (leased) {
      if (!owner || !owner->readers) std::terminate();
      --owner->readers;leased=false;
    }
    status=state;lease.reset();owner.reset();
  }
  storage::ScalarView value(AssignmentSlot slot) const {
    return frames.at(slot.step).selected->values()[slot.field.value];
  }

  // Visible tuples are borrowed under the runtime reader lease. Native table
  // cursors follow live links/buckets; no snapshot, pin per row or result set.
  bool select(Frame& frame, const program::EnumerationStep& step) {
    auto& table=owner->storage.table(step.relation);
    if (!frame.cursor) {
      metric(metrics.cursor_opens);
      if (step.parent_step) {
        require(step.parent_key && step.bucket_index,"weighted_contract","visible child lacks its compiled separator");
        metric(metrics.key_fields,static_cast<std::uint64_t>(step.parent_key->fields().size()));
        frame.key=step.parent_key->apply(*frames[*step.parent_step].selected);
        frame.cursor=table.bucket_cursor(owner->storage.index(*step.bucket_index),*frame.key,owner->allowance());
      } else frame.cursor=table.live(owner->allowance());
    }
    metric(metrics.advances);
    const auto entry=frame.cursor->next_entry(owner->allowance());
    if (!entry) return false;
    frame.selected=&entry->tuple;
    metric(metrics.factor_reads);
    const auto factor=owner->nodes[step.node.value].factors.at(entry->handle.tuple);
    require(factor.present(),"weighted_contract","visible tuple has no positive factor");
    metric(metrics.multiplications);
    const auto prefix=position?frames[position-1].prefix:Multiplicity{1};
    frame.prefix=owner->policy.multiply(prefix,factor);
    return true;
  }
  void close_frame(Frame& frame) {
    metric(metrics.frame_closes);
    frame.cursor.reset();frame.key.reset();frame.selected=nullptr;
  }
  Result emit(Multiplicity count) {
    const auto& enumeration=program.enumeration();
    for (const auto& equality:enumeration.equalities) {
      metric(metrics.equality_checks);
      require(value(equality.left)==value(equality.right),"weighted_contract","visible assignments disagree");
    }
    row.clear();
    for (const auto slot:enumeration.output) {
      metric(metrics.output_fields);row.push_back(value(slot));
    }
    auto native=program.result_layout().tuple(storage::RowView::borrow(row),{resource::MemoryOwnerKind::output,0});
    auto tuple=storage::Tuple::from_accounted(std::move(native));
    metric(metrics.rows_emitted);
    return {std::move(tuple),count};
  }
  std::optional<Result> advance() {
    metric(metrics.calls);
    if (!answer) return {};
    if (keyed) {
      const auto values=keyed->next();
      if (!values) return {};
      metric(metrics.output_fields,static_cast<std::uint64_t>(values->size()));
      auto native=program.result_layout().tuple(*values,{resource::MemoryOwnerKind::output,0});
      metric(metrics.rows_emitted);
      return Result{storage::Tuple::from_accounted(std::move(native)),{keyed->weight()}};
    }
    if (program.route()!=PhysicalRoute::tree) {
      if (resume) return {};
      resume=true;return emit({1});
    }
    require(!frames.empty(),"weighted_contract","weighted visible program has no root");
    const auto& steps=program.enumeration().steps;
    if (weighted_detail::advance_visible(*this,steps)) return emit(frames.back().prefix);
    return {};
  }
  std::optional<Result> next() {
    require(status!=CursorState::failed,"invalid_cursor","weighted result cursor failed and is closed");
    if (status!=CursorState::active) return {};
    const auto before=metrics.work;
    try {
      detail::StorageOperation operation(owner->context,lease);
      auto result=advance();
      metrics.last_work=metrics.work-before;sample_grant();
      if (result) metrics.max_result_work=std::max(metrics.max_result_work,metrics.last_work);
      else {metrics.termination_work=metrics.last_work;close(CursorState::exhausted);}
      return result;
    } catch (...) {
      // One real cursor failure boundary: release all borrowed state/readers,
      // retain spent diagnostics, and propagate the original typed failure.
      metrics.last_work=metrics.work-before;metrics.failed_work=metrics.last_work;
      close(CursorState::failed);throw;
    }
  }
};

WeightedRuntime::ResultCursor WeightedRuntime::results(CursorOptions options) const {
  auto& owner=impl();owner.readable();
  require(owner.readers!=UINT64_MAX,"resource_limit","weighted reader count exhausted");
  detail::StorageOperation operation(owner.context);
  auto data=resource::make_accounted_unique<ResultCursor::Data>(owner.account(),resource::MemoryPurpose::cursor,impl_,options);
  ++owner.readers;data->leased=true;
  return ResultCursor(std::move(data));
}
WeightedRuntime::ResultCursor::ResultCursor(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
WeightedRuntime::ResultCursor::ResultCursor(ResultCursor&&) noexcept=default;
WeightedRuntime::ResultCursor& WeightedRuntime::ResultCursor::operator=(ResultCursor&&) noexcept=default;
WeightedRuntime::ResultCursor::~ResultCursor()=default;
WeightedRuntime::ResultCursor::Data& WeightedRuntime::ResultCursor::data() const {
  require(bool(data_),"invalid_cursor","weighted result cursor was moved from");return *data_;
}
bool WeightedRuntime::ResultCursor::active() const noexcept {return data_ && data_->status==CursorState::active;}
CursorState WeightedRuntime::ResultCursor::state() const {return data().status;}
std::uint64_t WeightedRuntime::ResultCursor::sequence() const {return data().sequence;}
std::uint64_t WeightedRuntime::ResultCursor::owner() const {return data().owner_id;}
const Binding& WeightedRuntime::ResultCursor::binding() const & {return data().binding;}
const storage::TupleLayout& WeightedRuntime::ResultCursor::layout() const & {return data().output_layout;}
const CursorMetrics& WeightedRuntime::ResultCursor::metrics() const & {return data().metrics;}
std::optional<Result> WeightedRuntime::ResultCursor::next() {return data().next();}
void WeightedRuntime::ResultCursor::cancel() noexcept {if(data_)data_->close(CursorState::cancelled);}
} // namespace crown::runtime
