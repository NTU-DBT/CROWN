#include "selection_detail.hpp"
#include <algorithm>
#include <array>

namespace crown::planner::selection::detail {
namespace {
struct Dimension {
  std::uint64_t rank::Usage::*usage;
  std::uint64_t rank::Limits::*limit;
  Resource resource;
};
constexpr std::array dimensions{
    Dimension{&rank::Usage::work, &rank::Limits::work, Resource::work},
    Dimension{&rank::Usage::cells, &rank::Limits::cells, Resource::cells},
    Dimension{&rank::Usage::binding_key_bytes, &rank::Limits::binding_key_bytes, Resource::key_bytes},
    Dimension{&rank::Usage::payload_bytes, &rank::Limits::payload_bytes, Resource::payload_bytes},
    Dimension{&rank::Usage::lowering_work, &rank::Limits::lowering_work, Resource::lowering},
    Dimension{&rank::Usage::identity_work, &rank::Limits::identity_work, Resource::identity},
    Dimension{&rank::Usage::binding_replay_work, &rank::Limits::binding_replay_work, Resource::binding_replay},
    Dimension{&rank::Usage::normalization_work, &rank::Limits::normalization_work, Resource::normalization}};
void elapsed(rank::Usage& usage, std::chrono::steady_clock::time_point begin,
             std::chrono::steady_clock::time_point end) noexcept {
  const auto count = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  const auto amount = count < 0 ? UINT64_MAX : static_cast<std::uint64_t>(count);
  usage.active_nanoseconds = amount > UINT64_MAX - usage.active_nanoseconds ?
      UINT64_MAX : usage.active_nanoseconds + amount;
}
}
void require(bool value, Stop stop) { if (!value) throw Failure{stop, Resource::none, {}, 0}; }
[[noreturn]] void component_failure(rank::Stop value, rank::Reasons reasons) {
  Stop stop = Stop::internal_error;
  Resource resource = Resource::none;
  switch (value) {
    case rank::Stop::complete: break;
    case rank::Stop::no_candidates: stop = Stop::no_candidates; break;
    case rank::Stop::evidence_unavailable: stop = Stop::evidence_unavailable; break;
    case rank::Stop::invalid_handle: stop = Stop::invalid_handle; break;
    case rank::Stop::binding_mismatch: stop = Stop::binding_mismatch; break;
    case rank::Stop::invalid_limits: stop = Stop::invalid_request; break;
    case rank::Stop::work_limit: stop = Stop::resource_limit; resource = Resource::work; break;
    case rank::Stop::cell_limit: stop = Stop::resource_limit; resource = Resource::cells; break;
    case rank::Stop::byte_limit: stop = Stop::resource_limit; break;
    case rank::Stop::bit_limit: stop = Stop::resource_limit; resource = Resource::score_bits; break;
    case rank::Stop::candidate_limit: stop = Stop::resource_limit; resource = Resource::candidates; break;
    case rank::Stop::lowering_limit: stop = Stop::resource_limit; resource = Resource::lowering; break;
    case rank::Stop::time_limit: stop = Stop::resource_limit; resource = Resource::active_time; break;
    case rank::Stop::allocation_failure: stop = Stop::allocation_failure; break;
    case rank::Stop::internal_error: break;
  }
  throw Failure{stop, resource, value, reasons};
}
Budget::Budget(const rank::Limits& value, rank::Usage initial) : limits(value), usage(initial) {
  require(limits.score_bits != 0 && limits.score_bits <= 512 &&
      (!limits.active_time || limits.active_time->count() >= 0), Stop::invalid_request);
  check();
  if (limits.active_time) { started = std::chrono::steady_clock::now(); running = true; }
}
void Budget::check() const {
  for (const auto& d : dimensions) {
    if (usage.*d.usage > limits.*d.limit) throw Failure{Stop::resource_limit, d.resource, {}, 0};
  }
  if (limits.active_time && usage.active_nanoseconds >= static_cast<std::uint64_t>(limits.active_time->count()))
    throw Failure{Stop::resource_limit, Resource::active_time, {}, 0};
}
void Budget::finish() noexcept {
  if (running) {
    const auto now = std::chrono::steady_clock::now();
    elapsed(usage, started, now);
    started = now;
  }
}
void Budget::sample() { finish(); check(); }
void Budget::add(std::uint64_t& current, std::uint64_t amount, std::uint64_t cap, Resource resource) {
  if (current > cap || amount > cap - current) throw Failure{Stop::resource_limit, resource, {}, 0};
  current += amount;
}
void Budget::work(std::uint64_t n) { sample(); add(usage.work, n, limits.work, Resource::work); }
void Budget::cells(std::uint64_t n) { add(usage.cells, n, limits.cells, Resource::cells); }
void Budget::bytes(std::uint64_t n) { add(usage.payload_bytes, n, limits.payload_bytes, Resource::payload_bytes); }
void Budget::keys(std::uint64_t n) { work(n); add(usage.binding_key_bytes, n, limits.binding_key_bytes, Resource::key_bytes); }
rank::Limits Budget::begin_delegate(const rank::Usage& preparation) {
  sample();
  auto out = limits;
  for (const auto& d : dimensions) {
    require(preparation.*d.usage <= usage.*d.usage);
    out.*d.limit = preparation.*d.usage + (limits.*d.limit - usage.*d.usage);
  }
  if (limits.active_time) {
    require(preparation.active_nanoseconds <= usage.active_nanoseconds);
    out.active_time = std::chrono::nanoseconds(static_cast<std::int64_t>(preparation.active_nanoseconds +
        (static_cast<std::uint64_t>(limits.active_time->count()) - usage.active_nanoseconds)));
    running = false;
  }
  return out;
}
void Budget::end_delegate(const rank::Usage& returned, const rank::Usage& preparation) {
  // Sample the entire delegated phase before any potentially throwing counter
  // check, retaining both delegated work and elapsed time on resource failure.
  if (limits.active_time) {
    const auto now = std::chrono::steady_clock::now();
    elapsed(usage, started, now);
    started = now;
    running = true;
  }
  for (const auto& d : dimensions) {
    require(returned.*d.usage >= preparation.*d.usage);
    add(usage.*d.usage, returned.*d.usage - preparation.*d.usage, limits.*d.limit, d.resource);
  }
  // The component's measured interval lies inside the outer measured phase.
  // Do not add its elapsed delta again. If timing is off, retain preparation's
  // historical diagnostic value without taking a new clock sample.
  if (!limits.active_time && returned.active_nanoseconds > preparation.active_nanoseconds)
    throw Failure{Stop::internal_error, Resource::none, {}, 0};
  check();
}
PreparationTiming preparation_timing(const std::optional<rank::Evidence>& evidence) noexcept {
  if (!evidence) return PreparationTiming::absent;
  return evidence->capture_accounting().processing_limits.active_time ?
      PreparationTiming::measured : PreparationTiming::unmeasured;
}
int decimal_compare(const std::string& a, const std::string& b, Budget& budget) {
  budget.work();
  if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
  for (std::size_t i = 0; i < a.size(); ++i) {
    budget.keys(2);
    if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
  }
  return 0;
}
bool key_less(const std::string& a, const std::string& b, Budget& budget) {
  budget.work();
  const auto n = std::min(a.size(), b.size());
  for (std::size_t i = 0; i < n; ++i) {
    budget.keys(2);
    const auto x = static_cast<unsigned char>(a[i]);
    const auto y = static_cast<unsigned char>(b[i]);
    if (x != y) return x < y;
  }
  return a.size() < b.size();
}
bool equal_bytes(const std::string& a, const std::string& b, Budget& budget, std::uint64_t* compared) {
  budget.work();
  if (a.size() != b.size()) return false;
  for (std::size_t i = 0; i < a.size(); ++i) {
    budget.keys(2);
    if (compared) Budget::add(*compared, 2, UINT64_MAX, Resource::counter_overflow);
    if (a[i] != b[i]) return false;
  }
  return true;
}
void validate_slot_limit(const std::string& text, Budget& budget) {
  require(!text.empty() && text.size() <= 155 && (text.size() == 1 || text.front() != '0'), Stop::invalid_request);
  for (const char c : text) { budget.keys(1); require(c >= '0' && c <= '9', Stop::invalid_request); }
  constexpr std::string_view maximum = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095";
  if (text.size() == maximum.size()) {
    for (std::size_t i = 0; i < text.size(); ++i) {
      budget.keys(2);
      if (text[i] < maximum[i]) return;
      require(text[i] == maximum[i], Stop::invalid_request);
    }
  }
}
} // namespace crown::planner::selection::detail
