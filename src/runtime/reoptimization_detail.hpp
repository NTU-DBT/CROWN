#pragma once

#include "crown/runtime/reoptimization.hpp"
#include "crown/runtime/delta.hpp"
#include <chrono>
#include <set>

namespace crown::runtime::reoptimization::detail {
inline constexpr resource::MemoryAttribution attribution{resource::MemoryOwnerKind::session,1};

// Exceptions carry only an enum: exhausting a migration grant must not need
// another allocation from the already exhausted query account.
struct Failure {Stop stop;};
class Budget {
 public:
  Budget(Status& status,const Limits& limits):status_(status),limits_(limits) {}
  void charge(std::uint64_t amount=1) {
    if(status_.equivalence_work>limits_.equivalence_work || amount>limits_.equivalence_work-status_.equivalence_work)
      throw Failure{Stop::equivalence_limit};
    status_.equivalence_work+=amount;
  }
  void values(storage::RowView row) {
    charge();charge(row.size());
    for(const auto& value:row.cells())if(const auto* text=std::get_if<std::string_view>(&value))charge(text->size());
  }
  void values(storage::TupleValuesView row) {
    charge();charge(row.size());
    for(std::size_t i=0;i<row.size();++i) {
      const auto value=row[i];if(const auto* text=std::get_if<std::string_view>(&value))charge(text->size());
    }
  }
  void row(storage::RowView value,bool source) {
    if(rows_==limits_.equivalence_rows)throw Failure{Stop::equivalence_limit};
    values(value);++rows_;
    auto& count=source?status_.source_rows_compared:status_.result_rows_compared;++count;
  }
  void row(storage::TupleValuesView value,bool source) {
    if(rows_==limits_.equivalence_rows)throw Failure{Stop::equivalence_limit};
    values(value);++rows_;
    auto& count=source?status_.source_rows_compared:status_.result_rows_compared;++count;
  }
 private:
  Status& status_;
  const Limits& limits_;
  std::uint64_t rows_=0;
};
struct RowLess {
  Budget* budget;
  bool operator()(const storage::AccountedRow& a,const storage::AccountedRow& b) const {
    budget->values(a.view());budget->values(b.view());return a.view()<b.view();
  }
};
using Rows=std::set<storage::AccountedRow,RowLess,resource::MemoryAllocator<storage::AccountedRow>>;
inline Rows rows(const resource::MemoryAccount& account,Budget& budget) {
  return Rows(RowLess{&budget},resource::MemoryAllocator<storage::AccountedRow>(account,resource::MemoryPurpose::scratch,attribution));
}
struct Access {
  static bool same_sources(const DeltaRuntime&,const DeltaRuntime&,Budget&);
};

class State {
#ifdef CROWN_RUNTIME_TESTING
  friend struct ClockCounterTestAccess;
#endif
 public:
  using Clock=std::chrono::steady_clock;
  State(const DeltaRuntime&,const planner::MinimumHeightCandidate&,Options,std::optional<std::uint64_t> last_switch,Clock::time_point started,std::uint64_t selection_ns=0);
  ~State();
  State(const State&)=delete;
  State& operator=(const State&)=delete;
  [[nodiscard]] bool active() const noexcept {return target_.has_value();}
  [[nodiscard]] bool frozen() const noexcept {return status_.admission_frozen;}
  [[nodiscard]] bool verified() const noexcept {return status_.phase==Phase::verified;}
  [[nodiscard]] bool caught_up() const noexcept {return !head_ && !pending_ && !staged_;}
  [[nodiscard]] Status status() const;
  void request_barrier() noexcept;
  void waiting_output() noexcept;
  void barrier_progress() noexcept;
  void cancel(Phase phase=Phase::cancelled,Stop stop=Stop::none) noexcept;
  void stage(const DeltaRuntime&,const PhysicalUpdateView&) noexcept;
  void rollback_stage() noexcept;
  void committed(std::uint64_t sequence) noexcept;
  void advance(std::uint64_t quantum) noexcept;
  void verify(const DeltaRuntime&) noexcept;
  [[nodiscard]] Clock::time_point time() noexcept;
  void old_drain_elapsed(Clock::time_point) noexcept;
  [[nodiscard]] DeltaRuntime& target();
  void charge_artifact(std::uint64_t,const resource::MemoryStatistics&,const std::array<char,64>&);
  [[nodiscard]] bool publication_prepared(Clock::time_point) noexcept;
  [[nodiscard]] DeltaRuntime take_target() noexcept;
  void complete_publication(Clock::time_point,Clock::time_point,Clock::time_point) noexcept;
 private:
  struct Entry {
    std::uint64_t sequence,bytes;
    TableId table;
    SetOperation operation;
    storage::AccountedRow values;
    resource::AccountedUnique<Entry> next;
    Entry(const PhysicalUpdateView& update,std::uint64_t size,storage::AccountedRow row)
        :sequence(update.sequence),bytes(size),table(update.table),operation(update.operation),values(std::move(row)) {}
  };
  void clear_entries() noexcept;
  void pop() noexcept;
  void elapsed(Clock::time_point,std::uint64_t&) noexcept;
  [[nodiscard]] bool increment(std::uint64_t&,std::uint64_t=1) noexcept;
  resource::MemoryAccount account_;
  Options options_;
  std::optional<std::uint64_t> last_switch_;
  Status status_;
  std::array<char,64> artifact_sha256_{};
  std::optional<DeltaRuntime> target_;
  std::optional<DeltaRuntime::PendingEpoch> pending_;
  resource::AccountedUnique<Entry> head_,staged_;
  Entry* tail_=nullptr;
};
} // namespace crown::runtime::reoptimization::detail
