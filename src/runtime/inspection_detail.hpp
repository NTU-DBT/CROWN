#pragma once

#include "crown/runtime/inspection.hpp"
#include "accounted_ordered_rows.hpp"
#include <limits>
#include <utility>

namespace crown::runtime::detail {
inline AccountedRowSet inspection_rows(const resource::MemoryAccount& account) {
  return AccountedRowSet(account,resource::MemoryPurpose::scratch,invariant_attribution);
}
template<class T> AccountedRowMap<T> inspection_counts(const resource::MemoryAccount& account) {
  return AccountedRowMap<T>(account,resource::MemoryPurpose::scratch,invariant_attribution);
}
struct InspectionStop {};
// Own diagnostic prefixes and their original account; nested merges may stop partway
// only with complete=false. Allocation failures remain distinct from bounded stops.
struct InspectionContext {
  InspectionOptions options;
  resource::MemoryAccount account;
  InvariantReport report;
  InspectionContext(InspectionOptions limits,const resource::MemoryAccount& memory)
      :options(limits),account(memory),report(memory) {}
  InspectionContext(InspectionOptions limits,InvariantReport prefix)
      :options(limits),account(prefix.issues.get_allocator().account()),report(std::move(prefix)) {}
  [[nodiscard]] InvariantKey key(storage::RowView values) const {return InvariantKey::copy_of(account,values);}
  void charge(std::uint64_t amount=1) {
    const auto used=report.work;
    if (amount>std::numeric_limits<std::uint64_t>::max()-used ||
        (options.work_limit && (used>*options.work_limit || amount>*options.work_limit-used))) {
      report.complete=false; throw InspectionStop{};
    }
    report.work+=amount;
  }
  void add(InvariantIssue issue) {
    if (report.issues.size()>=options.issue_limit) { report.complete=false; throw InspectionStop{}; }
    report.issues.push_back(std::move(issue));
  }
  // Callers provide prefixes already within both ceilings before subtracting.
  [[nodiscard]] InspectionOptions remaining() const noexcept {
    return {options.work_limit?std::optional<std::uint64_t>{*options.work_limit-report.work}:std::nullopt,
        options.issue_limit-report.issues.size()};
  }
  void merge(InvariantReport child) {
    charge(child.work);
    report.complete=report.complete && child.complete;
    for (auto& issue : child.issues) add(std::move(issue));
    const auto sum=[&](std::size_t& target,std::size_t value) {
      if (value>std::numeric_limits<std::size_t>::max()-target) { report.complete=false; throw InspectionStop{}; }
      target+=value;
    };
#define CROWN_INSPECTION_SUM(field) sum(report.statistics.field,child.statistics.field)
    CROWN_INSPECTION_SUM(source_rows); CROWN_INSPECTION_SUM(derivation_keys);
    CROWN_INSPECTION_SUM(native_records); CROWN_INSPECTION_SUM(generalized_records);
    CROWN_INSPECTION_SUM(survivors); CROWN_INSPECTION_SUM(parent_keys); CROWN_INSPECTION_SUM(visible_keys);
    CROWN_INSPECTION_SUM(child_flags); CROWN_INSPECTION_SUM(source_storage_records);
    CROWN_INSPECTION_SUM(support_storage_records); CROWN_INSPECTION_SUM(index_memberships);
    CROWN_INSPECTION_SUM(live_rows); CROWN_INSPECTION_SUM(live_parent_rows); CROWN_INSPECTION_SUM(live_child_rows);
    CROWN_INSPECTION_SUM(live_parent_buckets); CROWN_INSPECTION_SUM(live_child_buckets);
#undef CROWN_INSPECTION_SUM
  }
};
}  // namespace crown::runtime::detail
