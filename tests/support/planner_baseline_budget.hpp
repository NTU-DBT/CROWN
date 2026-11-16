#pragma once

#include "crown/api/error.hpp"
#include "crown/planner/oracle.hpp"
#include <exception>
#include <limits>
#include <string>
#include <utility>

namespace crown::planner::baseline_detail {
// Legacy baseline stop owns ordinary message text and may allocate on rejection.
struct SearchStopped : std::exception {
  std::string reason;
  explicit SearchStopped(std::string message) : reason(std::move(message)) {}
  const char* what() const noexcept override { return reason.c_str(); }
};

class WorkBudget {
 public:
  explicit WorkBudget(const SearchLimits& limits)
      : limits_(limits), start_(std::chrono::steady_clock::now()) {
    if (limits_.time_limit && limits_.time_limit->count() < 0)
      throw Error("invalid_search_limits", "negative search time limit");
  }

  void charge() {
    if (limits_.work_limit && statistics.work >= *limits_.work_limit)
      throw SearchStopped("search work limit reached");
    if (limits_.time_limit &&
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_) >= *limits_.time_limit)
      throw SearchStopped("search time limit reached");
    if (statistics.work == std::numeric_limits<std::uint64_t>::max())
      throw SearchStopped("search work counter exhausted");
    ++statistics.work;
  }

  // Charge precedes depth denial; a refused entry consumes work but not depth.
  class Frame {
   public:
    explicit Frame(WorkBudget& budget) : budget_(budget) {
      budget_.charge();
      if (budget_.limits_.recursion_limit &&
          budget_.depth_ >= *budget_.limits_.recursion_limit)
        throw SearchStopped("search recursion limit reached");
      ++budget_.depth_;
    }
    ~Frame() { --budget_.depth_; }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

   private:
    WorkBudget& budget_;
  };

  [[nodiscard]] Frame frame() { return Frame(*this); }
  SearchStatistics statistics;

 private:
  SearchLimits limits_;
  std::chrono::steady_clock::time_point start_;
  std::size_t depth_ = 0;
};
}  // namespace crown::planner::baseline_detail
