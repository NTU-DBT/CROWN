#include "star_detail.hpp"
#include <algorithm>
#include <deque>
#include <limits>

namespace crown::runtime::star {
namespace {
constexpr resource::MemoryAttribution cursor_memory{resource::MemoryOwnerKind::cursor, 0};
template<class T> auto cursor_allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account, resource::MemoryPurpose::cursor, cursor_memory);
}
} // namespace

struct Runtime::Cursor::Data {
  // All views borrow immutable projection keys. The reader lease and retained
  // owner keep them alive; returned tuples instead own separately funded rows.
  std::shared_ptr<Runtime::Data> owner;
  CursorOptions options;
  CursorMetrics metrics;
  std::set<storage::RowView, std::less<storage::RowView>, resource::MemoryAllocator<storage::RowView>> seen;
  std::deque<storage::RowView, resource::MemoryAllocator<storage::RowView>> queue;
  detail::Set<detail::Group>::const_iterator group;
  detail::Projections::const_iterator projection;
  bool leased = false;

  Data(std::shared_ptr<Runtime::Data> runtime, CursorOptions requested)
      : owner(std::move(runtime)), options(requested),
        seen(std::less<storage::RowView>{}, cursor_allocator<storage::RowView>(owner->account)),
        queue(cursor_allocator<storage::RowView>(owner->account)), group(owner->live.cbegin()) {
    take();
    // The per-output duplicate bound is product_hidden(1 + heavy_keys_i).
    // Every candidate also has a distinct center-row witness. Clamp before
    // multiplication/addition overflow; the empty-source quantum stays one.
    const auto cap = std::max(std::uint64_t{1}, static_cast<std::uint64_t>(owner->facts.size()));
    for (std::size_t i = 0; i < owner->dimensions.size(); ++i) {
      take();
      if (owner->free[i]) continue;
      const auto heavy = static_cast<std::uint64_t>(owner->dimensions[i].heavy.size());
      if (heavy >= cap) metrics.candidate_quantum = cap;
      else {
        const auto factor = heavy + 1;
        metrics.candidate_quantum = metrics.candidate_quantum > cap / factor
            ? cap : metrics.candidate_quantum * factor;
      }
    }
    if (group != owner->live.cend()) {
      projection = (*group)->projections.cbegin();
      detail::require(projection != (*group)->projections.cend(), "live star group has no projection");
    }
    // Runtime::results publishes the lease only after this fallible constructor
    // and all initial deque/control allocations have completed successfully.
  }
  ~Data() { close(); }

  void take() {
    if (metrics.work == options.work)
      throw Error("star_cursor_work_limit", "star cursor work grant exhausted");
    ++metrics.work;
  }

  void close() noexcept {
    if (!owner) return;
    // Each seen key required two charged actions and queue.size() <= seen.size(),
    // so this sum fits the lifetime work counter. Teardown is actual O(scratch)
    // work; releasing the last owner may additionally destroy source/view state.
    metrics.cleanup_items = static_cast<std::uint64_t>(seen.size()) + static_cast<std::uint64_t>(queue.size());
    queue.clear(); seen.clear();
    if (leased) { --owner->readers; leased = false; }
    owner.reset();
  }

  std::optional<storage::Tuple> advance() {
    take(); // Includes an empty-source or exhausted-queue termination attempt.
    // Local projection scheduler (P2 audit, section 7). At most one projection
    // entry per group is consumed for a fixed output. Processing a full quantum
    // before emitting one queued answer prevents arbitrarily long duplicate gaps.
    for (std::uint64_t scanned = 0;
         scanned < metrics.candidate_quantum && group != owner->live.cend(); ++scanned) {
      take();
      const auto row = projection->first.view();
      ++projection; ++metrics.candidates;
      take();
      if (seen.insert(row).second) {
        take(); queue.push_back(row);
      } else ++metrics.duplicates;
      if (projection == (*group)->projections.cend()) {
        take(); ++group; ++metrics.group_advances;
        if (group != owner->live.cend()) {
          projection = (*group)->projections.cbegin();
          detail::require(projection != (*group)->projections.cend(), "live star group has no projection");
        }
      }
    }
    if (queue.empty()) {
      detail::require(group == owner->live.cend(), "star projection scheduler lost its productive prefix");
      return {};
    }
    take();
    auto native = owner->program.result_layout().tuple(queue.front(), {resource::MemoryOwnerKind::output, 0});
    auto tuple = storage::Tuple::from_accounted(std::move(native));
    queue.pop_front(); ++metrics.outputs;
    return std::optional<storage::Tuple>{std::move(tuple)};
  }
};

Runtime::Cursor::Cursor(resource::AccountedUnique<Data> data) noexcept : data_(std::move(data)) {}
Runtime::Cursor::~Cursor() { cancel(); }
Runtime::Cursor::Cursor(Cursor&& other) noexcept : data_(std::move(other.data_)), closed_(other.closed_) {}
Runtime::Cursor& Runtime::Cursor::operator=(Cursor&& other) noexcept {
  if (this != &other) {
    cancel(); data_ = std::move(other.data_); closed_ = other.closed_;
  }
  return *this;
}
void Runtime::Cursor::cancel() noexcept {
  if (!data_) return;
  data_->close(); closed_ = data_->metrics; data_.reset();
}
CursorMetrics Runtime::Cursor::metrics() const noexcept { return data_ ? data_->metrics : closed_; }
std::optional<storage::Tuple> Runtime::Cursor::next() {
  if (!data_) return {};
  try {
    auto result = data_->advance();
    if (!result) cancel();
    return result;
  } catch (...) {
    cancel(); throw;
  }
}

Runtime::Cursor Runtime::results(CursorOptions options) const {
  auto& owner = data(); owner.readable();
  detail::require(owner.readers != std::numeric_limits<std::uint64_t>::max(), "star reader count overflow");
  auto prepared = resource::make_accounted_unique<Cursor::Data>(cursor_memory, owner.account,
      resource::MemoryPurpose::cursor, data_, options);
  ++owner.readers; prepared->leased = true;
  return Cursor(std::move(prepared));
}
} // namespace crown::runtime::star
