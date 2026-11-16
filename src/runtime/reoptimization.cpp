#include "crown/runtime/reoptimization.hpp"
#include "reoptimization_detail.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <limits>

namespace crown::runtime::reoptimization {
PolicyDecision evaluate(const Policy& policy,const std::optional<Forecast>& forecast,
    std::uint64_t current_epoch,std::optional<std::uint64_t> last_switch_epoch,
    PreparationCosts costs) noexcept {
  PolicyDecision result;
  if(policy.minimum_saving_basis_points>10000)return result;
  if(last_switch_epoch && *last_switch_epoch>current_epoch) {result.stop=PolicyStop::invalid_epoch;return result;}
  if(last_switch_epoch && current_epoch-*last_switch_epoch<policy.minimum_epoch_gap) {result.stop=PolicyStop::hysteresis;return result;}
  if(!forecast) {result.stop=PolicyStop::forecast_unavailable;return result;}
  if(forecast->horizon_inputs==0) {result.stop=PolicyStop::invalid_forecast;return result;}
  if(forecast->target_ns_per_input>=forecast->current_ns_per_input) {result.stop=PolicyStop::not_faster;return result;}
  result.saving_ns_per_input=forecast->current_ns_per_input-forecast->target_ns_per_input;
  // ceil(current * basis_points / 10000), without an overflowing product.
  // Both terms and their sum are <= current for a valid basis-point value.
  const auto points=static_cast<std::uint64_t>(policy.minimum_saving_basis_points);
  const auto whole=(forecast->current_ns_per_input/10000)*points;
  const auto remainder=(forecast->current_ns_per_input%10000)*points;
  const auto relative_threshold=whole+remainder/10000+(remainder%10000!=0?1U:0U);
  if(result.saving_ns_per_input<relative_threshold || result.saving_ns_per_input<policy.minimum_saving_ns_per_input) {
    result.stop=PolicyStop::insufficient_saving;return result;
  }
  const auto add=[&](std::uint64_t value) {
    if(value>std::numeric_limits<std::uint64_t>::max()-result.charged_and_reserved_ns)return false;
    result.charged_and_reserved_ns+=value;return true;
  };
  if(!add(costs.snapshot_rebuild_ns) || !add(costs.catch_up_ns) || !add(costs.equivalence_ns) ||
      !add(costs.compiler_artifact_ns) || !add(costs.publication_prepare_ns) || !add(costs.selection_prepare_ns) ||
      !add(policy.publication_and_cleanup_reserve_ns)) {
    result.stop=PolicyStop::arithmetic_overflow;return result;
  }
  // ceil(total / saving) avoids multiplying a possibly enormous horizon by
  // saving. The increment cannot overflow: quotient==max implies divisor1
  // and therefore a zero remainder.
  result.required_future_inputs=result.charged_and_reserved_ns/result.saving_ns_per_input+
      (result.charged_and_reserved_ns%result.saving_ns_per_input!=0?1U:0U);
  result.stop=result.required_future_inputs<=forecast->horizon_inputs?PolicyStop::eligible:PolicyStop::not_paid_back;
  return result;
}
} // namespace crown::runtime::reoptimization

namespace crown::runtime::reoptimization::detail {
bool Access::same_sources(const DeltaRuntime& left,const DeltaRuntime& right,Budget& budget) {
  return left.same_sources(right,budget);
}
State::State(const DeltaRuntime& source,const planner::MinimumHeightCandidate& candidate,Options options,
    std::optional<std::uint64_t> last_switch,Clock::time_point started,std::uint64_t selection_ns)
    :account_(source.plan().account()),options_(std::move(options)),last_switch_(last_switch) {
  // Cold rebuild retains both native owners and compiler/snapshot overlap on
  // the original query account; recorded peak is cumulative for that account.
  if(options_.expected && (options_.expected->owner!=source.owner().value || options_.expected->epoch!=source.sequence()))
    throw Error("reoptimization_stale_source","candidate preparation source owner or epoch changed");
  status_.source_owner=source.owner().value;status_.snapshot_epoch=source.sequence();status_.source_epoch=source.sequence();
  status_.costs.selection_prepare_ns=selection_ns;
  status_.clock_reads=1; // Caller read immediately before the funded State allocation.
  std::copy(source.plan().physical_sha256().begin(),source.plan().physical_sha256().end(),status_.source_physical_sha256.begin());
  target_.emplace(source.rebuilt_for(candidate,options_.build,options_.replan));
  status_.target_owner=target_->owner().value;status_.target_epoch=target_->sequence();
  std::copy(target_->plan().physical_sha256().begin(),target_->plan().physical_sha256().end(),status_.target_physical_sha256.begin());
  status_.lowering_work=target_->plan().work();status_.build_work=target_->initialization_metrics().work;
  status_.phase=Phase::catching_up;
  elapsed(started,status_.costs.snapshot_rebuild_ns);
}
State::~State() {cancel();}
Status State::status() const {auto result=status_;result.query_memory=account_.statistics();return result;}
State::Clock::time_point State::time() noexcept {
  if(status_.clock_reads==UINT64_MAX){cancel(Phase::failed,Stop::counter_overflow);return Clock::now();}
  ++status_.clock_reads;return Clock::now();
}
bool State::increment(std::uint64_t& value,std::uint64_t amount) noexcept {
  if(amount>UINT64_MAX-value){cancel(Phase::failed,Stop::counter_overflow);return false;}
  value+=amount;return true;
}
void State::elapsed(Clock::time_point start,std::uint64_t& value) noexcept {
  const auto end=time();if(end<start){cancel(Phase::failed,Stop::clock_regression);return;}
  const auto ns=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
  static_cast<void>(increment(value,static_cast<std::uint64_t>(ns)));
}
void State::old_drain_elapsed(Clock::time_point start) noexcept {elapsed(start,status_.old_drain_ns);}
DeltaRuntime& State::target() {
  if(!verified() || !target_)throw Error("reoptimization_not_verified","candidate is not at its verified publication barrier");
  return *target_;
}
void State::charge_artifact(std::uint64_t ns,const resource::MemoryStatistics& memory,const std::array<char,64>& hash) {
  if(status_.compiler_input_charged) {
    if(artifact_sha256_!=hash || status_.compiler_input_memory!=memory || status_.costs.compiler_artifact_ns!=ns)
      throw Error("reoptimization_artifact_changed","retry publication with the same immutable compiler input");
    return;
  }
  status_.compiler_input_charged=true;status_.compiler_input_memory=memory;artifact_sha256_=hash;status_.costs.compiler_artifact_ns=ns;
}
bool State::publication_prepared(Clock::time_point started) noexcept {
  elapsed(started,status_.costs.publication_prepare_ns);if(!active())return false;
  status_.decision=evaluate(options_.policy,options_.forecast,status_.source_epoch,last_switch_,status_.costs);
  if(status_.decision.stop!=PolicyStop::eligible)cancel(Phase::rejected);
  return active();
}
DeltaRuntime State::take_target() noexcept {
  auto result=std::move(*target_);target_.reset();return result;
}
void State::complete_publication(Clock::time_point started,Clock::time_point selected,Clock::time_point cleaned) noexcept {
  status_.phase=Phase::complete;status_.admission_frozen=false;
  if(status_.clock_reads>UINT64_MAX-3 || selected<started || cleaned<selected) {
    status_.publication_timings_complete=false;return;
  }
  status_.clock_reads+=3;
  status_.publication_ns=static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(selected-started).count());
  status_.cleanup_ns=static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(cleaned-selected).count());
}
void State::request_barrier() noexcept {
  if(!active() || verified())return;
  status_.admission_frozen=true;status_.phase=Phase::barrier_requested;
}
void State::waiting_output() noexcept {if(active())status_.phase=Phase::waiting_output;}
void State::barrier_progress() noexcept {if(active() && frozen() && !verified())status_.phase=Phase::barrier_requested;}
void State::clear_entries() noexcept {
  staged_.reset();while(head_){auto next=std::move(head_->next);head_.reset();head_=std::move(next);}tail_=nullptr;
  status_.backlog_records=0;status_.backlog_bytes=0;
}
void State::cancel(Phase phase,Stop stop) noexcept {
  pending_.reset();clear_entries();target_.reset();status_.admission_frozen=false;status_.phase=phase;status_.stop=stop;
}
void State::rollback_stage() noexcept {
  if(!staged_)return;
  --status_.backlog_records;status_.backlog_bytes-=staged_->bytes;staged_.reset();
}
void State::stage(const DeltaRuntime& source,const PhysicalUpdateView& update) noexcept {
  // A failed candidate must not block the ordinary writer. The staged record
  // stays private until the old owner commits and links it without allocation.
  if(!active())return;
  const auto start=time();
  if(!active())return;
  try {
    if(verified() || staged_ || source.owner().value!=status_.source_owner || source.sequence()!=status_.source_epoch)
      throw Failure{Stop::source_changed};
    if(status_.source_epoch==UINT64_MAX || update.sequence!=status_.source_epoch+1)throw Failure{Stop::sequence_mismatch};
    // Charge descriptor visits before sizing strings or copying any bytes.
    const auto charge=[&](std::uint64_t amount) {
      if(status_.staging_work>options_.limits.staging_work || amount>options_.limits.staging_work-status_.staging_work)
        throw Failure{Stop::staging_limit};
      status_.staging_work+=amount;
    };
    charge(1);charge(update.values.size());
    for(std::size_t i=0;i<update.values.size();++i) {
      const auto value=update.values[i];if(const auto* text=std::get_if<std::string_view>(&value))charge(text->size());
    }
    const auto payload=storage::AccountedRow::allocation_usage_for(update.values).requested_bytes;
    const auto control=resource::MemoryAccount::allocation_bytes(sizeof(Entry),alignof(Entry));
    if(payload>UINT64_MAX-control)throw Failure{Stop::counter_overflow};
    const auto bytes=control+payload;
    if(status_.backlog_records>=options_.limits.backlog_records || status_.backlog_bytes>options_.limits.backlog_bytes ||
        bytes>options_.limits.backlog_bytes-status_.backlog_bytes)throw Failure{Stop::backlog_limit};
    auto row=storage::AccountedRow::copy_view(account_,update.values,attribution);
    staged_=resource::make_accounted_unique<Entry>(attribution,account_,resource::MemoryPurpose::journal_undo,update,bytes,std::move(row));
    ++status_.backlog_records;status_.backlog_bytes+=bytes;
    status_.peak_backlog_records=std::max(status_.peak_backlog_records,status_.backlog_records);
    status_.peak_backlog_bytes=std::max(status_.peak_backlog_bytes,status_.backlog_bytes);
    static_cast<void>(increment(status_.staged_records));
  }catch(const Failure& failure){cancel(Phase::failed,failure.stop);}
  catch(const std::bad_alloc&){cancel(Phase::failed,Stop::allocation_failure);}
  catch(...){cancel(Phase::failed,Stop::native_failure);}
  const auto before=status_.ledger_staging_ns;elapsed(start,status_.ledger_staging_ns);
  if(status_.ledger_staging_ns>=before)static_cast<void>(increment(status_.costs.catch_up_ns,status_.ledger_staging_ns-before));
}
void State::committed(std::uint64_t sequence) noexcept {
  if(!active())return;
  if(!staged_ || staged_->sequence!=sequence){cancel(Phase::failed,Stop::sequence_mismatch);return;}
  auto* last=staged_.get();
  if(tail_)tail_->next=std::move(staged_);else head_=std::move(staged_);
  tail_=last;status_.source_epoch=sequence;
}
void State::pop() noexcept {
  const auto bytes=head_->bytes;auto next=std::move(head_->next);head_.reset();head_=std::move(next);
  if(!head_)tail_=nullptr;
  --status_.backlog_records;status_.backlog_bytes-=bytes;
}
void State::advance(std::uint64_t quantum) noexcept {
  if(!active() || verified() || quantum==0)return;
  const auto start=time();
  try {
    while(quantum!=0 && head_) {
      if(status_.catch_up_steps==options_.limits.catch_up_steps)throw Failure{Stop::catch_up_limit};
      ++status_.catch_up_steps;--quantum;
      if(!pending_) {
        if(status_.target_epoch==UINT64_MAX || head_->sequence!=status_.target_epoch+1)throw Failure{Stop::sequence_mismatch};
        pending_.emplace(target_->begin_view({head_->sequence,head_->table,head_->operation,storage::TupleValuesView::borrow(head_->values.view())}));
        pending_->start_drain();
      } else if(pending_->step()==DeltaStep::prepared) {
        auto epoch=pending_->commit();pending_.reset();
        const auto work=epoch.metrics().work,physical_work=epoch.input().input.metrics.work;
        epoch.discard();status_.target_epoch=target_->sequence();
        if(!increment(status_.catch_up_native_work,work) || !increment(status_.catch_up_native_work,physical_work) ||
            !increment(status_.replayed_records))break;
        pop();
      }
    }
  }catch(const Failure& failure){cancel(Phase::failed,failure.stop);}
  catch(const std::bad_alloc&){cancel(Phase::failed,Stop::allocation_failure);}
  catch(...){cancel(Phase::failed,Stop::native_failure);}
  elapsed(start,status_.costs.catch_up_ns);
}
void State::verify(const DeltaRuntime& source) noexcept {
  // Compare complete source and result sets at the frozen same-epoch barrier.
  // Equality plus forecast eligibility still does not publish a durable plan.
  if(!active() || verified() || !frozen() || !caught_up())return;
  const auto start=time();
  if(!active())return;
  try {
    if(source.owner().value!=status_.source_owner)throw Failure{Stop::source_changed};
    if(source.sequence()!=status_.source_epoch || status_.source_epoch!=status_.target_epoch)throw Failure{Stop::sequence_mismatch};
    Budget budget(status_,options_.limits);
    if(!Access::same_sources(source,*target_,budget))throw Failure{Stop::source_mismatch};
    auto values=rows(account_,budget);
    const auto scan=[&](const DeltaRuntime& owner,bool insert) {
      std::optional<SupportRuntime::ResultCursor> cursor;
      try{cursor.emplace(owner.results(ResultCursorOptions{options_.limits.equivalence_cursor_work}));}
      catch(...) {static_cast<void>(increment(status_.equivalence_unobserved_startups));throw;}
      const auto record=[&] {
        if(!increment(status_.equivalence_native_work,cursor->metrics().total_work))throw Failure{Stop::counter_overflow};
      };
      try {
        while(auto tuple=cursor->next_native()) {
          budget.row(tuple->values(),false);auto row=storage::AccountedRow::copy_of(account_,tuple->values(),attribution);
          if(insert) {
            if(!values.insert(std::move(row)).second)throw Failure{Stop::result_mismatch};
          } else {
            const auto match=values.find(row);if(match==values.end())throw Failure{Stop::result_mismatch};values.erase(match);
          }
        }
      }catch(...) {record();throw;}
      record();
    };
    scan(source,true);scan(*target_,false);
    if(!values.empty())throw Failure{Stop::result_mismatch};
    status_.phase=Phase::verified;
  }catch(const Failure& failure){cancel(Phase::failed,failure.stop);}
  catch(const std::bad_alloc&){cancel(Phase::failed,Stop::allocation_failure);}
  catch(const Error& failure){cancel(Phase::failed,failure.code()=="resource_limit"?Stop::equivalence_limit:Stop::native_failure);}
  catch(...){cancel(Phase::failed,Stop::native_failure);}
  elapsed(start,status_.costs.equivalence_ns);
  if(verified()) {
    status_.decision=evaluate(options_.policy,options_.forecast,status_.source_epoch,last_switch_,status_.costs);
    if(status_.decision.stop!=PolicyStop::eligible)cancel(Phase::rejected);
  }
}
} // namespace crown::runtime::reoptimization::detail
