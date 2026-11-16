#include "crown/runtime/topk.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <compare>

namespace crown::runtime {
namespace {
using namespace topk;
using aggregate::Cell;
using Candidates = aggregate::OutputVector<Entry>;

// One balance is borrowed by every comparator copy and the complete selection.
// These selected logical charges exclude producer work, allocation and row moves.
struct Budget {
  std::uint64_t remaining;
  Metrics metrics;
  void take(std::uint64_t amount = 1) {
    if(amount > remaining) throw Error("topk_work_limit", "top-k work grant exceeded");
    remaining -= amount;
    metrics.work += amount;
  }
};

// Admission runs even for k=0, before opening a producer or retaining candidates.
void validate(std::span<const Key> order, std::size_t fields, Budget& budget) {
  for(const auto& key : order) {
    budget.take();
    if(key.field >= fields ||
        (key.direction != Direction::ascending && key.direction != Direction::descending) ||
        (key.nulls != NullOrder::first && key.nulls != NullOrder::last))
      throw Error("topk_order", "top-k field, direction or NULL order is invalid");
  }
}

// Present values inherit the genuine schema's exact scalar domain. Charge both
// complete string extents before comparing; NULL comparison reads no payload.
std::strong_ordering compare(const Cell& left, const Cell& right, NullOrder nulls, Budget& budget) {
  budget.take(); ++budget.metrics.fields;
  if(!left && !right) return std::strong_ordering::equal;
  if(!left) return nulls == NullOrder::first ? std::strong_ordering::less : std::strong_ordering::greater;
  if(!right) return nulls == NullOrder::first ? std::strong_ordering::greater : std::strong_ordering::less;
  if(const auto* text = std::get_if<std::string_view>(&*left)) {
    const auto other = std::get<std::string_view>(*right);
    budget.take(text->size()); budget.metrics.scalar_bytes += text->size();
    budget.take(other.size()); budget.metrics.scalar_bytes += other.size();
  }
  return *left <=> *right;
}

// Identity breaks rank ties without insertion-order, source-witness or pointer
// dependence. Aggregate equal output values never merge different group keys.
bool less(const Entry& left, const Entry& right, std::span<const Key> order, Budget& budget) {
  budget.take(); ++budget.metrics.comparisons;
  const auto a = left.values.view(), b = right.values.view();
  for(const auto& key : order) {
    const auto relation = compare(a[key.field], b[key.field], key.nulls, budget);
    if(relation != 0) {
      if(a[key.field] && b[key.field] && key.direction == Direction::descending) return relation > 0;
      return relation < 0;
    }
  }
  const auto x = left.identity.view(), y = right.identity.view();
  for(std::size_t i = 0; i < std::min(x.size(), y.size()); ++i) {
    const auto relation = compare(x[i], y[i], NullOrder::first, budget);
    if(relation != 0) return relation < 0;
  }
  return x.size() < y.size();
}

// The producer may decode one extra tuple to discover this bound. It remains
// covered by the original account and the single finite producer grant.
void append(Candidates& candidates, Entry entry, Limits limits, Budget& budget) {
  if(candidates.size() >= limits.candidates)
    throw Error("topk_result_limit", "top-k candidate grant exceeded");
  budget.take();
  candidates.push_back(std::move(entry)); ++budget.metrics.candidates;
}

// Sorting mutates private owned handles only. A thrown comparison needs no undo
// layer: RAII releases the temporary vector; no query state was changed.
void select(Snapshot& result, Candidates& candidates, std::span<const Key> order, Budget& budget) {
  std::sort(candidates.begin(), candidates.end(), [&](const Entry& a, const Entry& b) {
    return less(a, b, order, budget);
  });
  auto remaining = result.requested_k;
  std::size_t selected = 0;
  for(const auto& candidate : candidates) {
    if(!remaining) break;
    budget.take();
    remaining -= std::min(remaining, candidate.multiplicity); ++selected;
  }
  // A separate compact vector avoids retaining N candidate slots for a small k.
  // Tuple handles share immutable payload; this does not deep-copy strings.
  result.entries.reserve(selected);
  remaining = result.requested_k;
  for(std::size_t i = 0; i < selected; ++i) {
    const auto& candidate = candidates[i];
    const auto take = std::min(remaining, candidate.multiplicity);
    result.entries.push_back({candidate.identity, candidate.values, take});
    remaining -= take;
  }
  result.selected_rows = result.requested_k - remaining;
  result.metrics = budget.metrics;
}
} // namespace

topk::Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t epoch,
    std::uint64_t k, Program source)
    : sequence(epoch), requested_k(k), program(std::move(source)),
      entries(resource::OwnerAllocator<Entry>(account, resource::MemoryPurpose::output_buffer)) {}

topk::Snapshot snapshot_topk(const SqlRowsRuntime& owner, std::span<const Key> order,
    std::uint64_t k, Limits limits) {
  if(!owner.ready()) throw Error("topk_busy", "top-k requires a quiescent SQL row owner");
  const auto& program = owner.program();
  Budget budget{limits.work, {}}; validate(order, program.outputs().size(), budget);
  Snapshot result(program.account(), owner.sequence(), k, program);
  if(!k) { result.metrics = budget.metrics; return result; }
  budget.take();
  Candidates candidates(resource::OwnerAllocator<Entry>(program.account(), resource::MemoryPurpose::scratch));
  {
    auto cursor = owner.results({limits.producer_work});
    while(auto row = cursor.next())
      append(candidates, {row->tuple, std::move(row->tuple), row->multiplicity}, limits, budget);
  } // Release the native reader lease before sorting the owned snapshot.
  select(result, candidates, order, budget); return result;
}

topk::Snapshot snapshot_topk(const SqlAggregateRuntime& owner, std::span<const Key> order,
    std::uint64_t k, Limits limits) {
  if(!owner.ready()) throw Error("topk_busy", "top-k requires a quiescent SQL aggregate owner");
  const auto& program = owner.program();
  Budget budget{limits.work, {}}; validate(order, program.kernel_program().outputs().size(), budget);
  Snapshot result(owner.account(), owner.sequence(), k, program);
  if(!k) { result.metrics = budget.metrics; return result; }
  budget.take();
  Candidates candidates(resource::OwnerAllocator<Entry>(owner.account(), resource::MemoryPurpose::scratch));
  {
    auto image = owner.snapshot({limits.candidates, limits.producer_work});
    candidates.reserve(image.groups.size());
    for(auto& group : image.groups)
      append(candidates, {std::move(group.key), std::move(group.values), 1}, limits, budget);
  }
  select(result, candidates, order, budget); return result;
}
} // namespace crown::runtime
