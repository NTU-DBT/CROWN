#include "selection_detail.hpp"
#include "crown/api/error.hpp"

namespace crown::planner::selection {
PlanCache::PlanCache(std::unique_ptr<detail::CacheData> data) noexcept : data_(std::move(data)) {}
PlanCache::~PlanCache() = default;
PlanCache::PlanCache(PlanCache&&) noexcept = default;
PlanCache& PlanCache::operator=(PlanCache&&) noexcept = default;
PlanCache PlanCache::create(CacheLimits limits) {
  if (limits.entries && (!limits.key_bytes || !limits.plan_payload_bytes))
    throw Error("selection_cache_limits", "positive selection cache capacity requires positive logical byte caps");
  return PlanCache(std::make_unique<detail::CacheData>(limits));
}
bool PlanCache::valid() const noexcept { return static_cast<bool>(data_); }
CacheLimits PlanCache::limits() const noexcept { return data_ ? data_->limits : CacheLimits{0, 0, 0}; }
CacheStatistics PlanCache::statistics() const noexcept { return data_ ? data_->statistics : CacheStatistics{}; }
void PlanCache::clear() noexcept { if (data_) { data_->entries.clear(); data_->statistics = {}; } }
namespace detail {
namespace {
void increment(std::uint64_t& n, std::uint64_t amount = 1) { Budget::add(n, amount, UINT64_MAX, Resource::counter_overflow); }
}
void Prepared::commit() noexcept {
  if (!cache) return;
  // Destruction of the last plan owner can run JSON cleanup. Defer it until
  // after publication instead of allocating even a cleanup stack in commit.
  for (std::size_t i = 0; i < evictions; ++i)
    retired.splice(retired.end(), cache->entries, cache->entries.begin());
  cache->entries.splice(cache->entries.end(), insertion);
  cache->statistics = next;
}
// Called only after the fresh whole-set decision. Lookup stages statistics and
// may choose the existing complete plan; no cache-owned object is changed here.
void prepare_cache(Prepared& prepared, CacheData* cache, CacheUse use, Budget& budget) {
  auto& data = *prepared.data;
  data.cache.requested = use;
  if (use == CacheUse::bypass) { data.cache.disposition = CacheDisposition::bypassed; return; }
  require(cache != nullptr, Stop::invalid_handle);
  data.cache.limits = cache->limits;
  if (!cache->limits.entries) { data.cache.disposition = CacheDisposition::disabled; return; }
  require(data.key.has_value());
  data.cache.binding_bytes = static_cast<std::uint64_t>(data.key->size());
  prepared.cache = cache; prepared.next = cache->statistics;
  require(prepared.next.entries == cache->entries.size());
  require(prepared.next.key_bytes <= cache->limits.key_bytes &&
      prepared.next.plan_payload_bytes <= cache->limits.plan_payload_bytes);
  for (const auto& entry : cache->entries) {
    budget.work();
    if (equal_bytes(*data.key, entry.key, budget, &data.cache.compared_bytes)) {
      increment(prepared.next.hits); data.plan = entry.plan;
      data.cache.disposition = CacheDisposition::hit;
      return;
    }
  }
  increment(prepared.next.misses);
  data.cache.disposition = use == CacheUse::read_only ? CacheDisposition::miss_read_only : CacheDisposition::inserted;
  // Miss entry preparation follows finite native lowering, in Operation, so a
  // failing lower never changes even miss counters or FIFO state.
}
void stage_cache_entry(Prepared& prepared, Budget& budget) {
  auto& data = *prepared.data;
  if (data.cache.disposition != CacheDisposition::inserted) return;
  require(prepared.cache && data.plan && data.chosen && data.key);
  const auto& limits = prepared.cache->limits;
  const auto key_bytes = static_cast<std::uint64_t>(data.key->size());
  if (key_bytes > limits.key_bytes) throw Failure{Stop::resource_limit, Resource::cache_key_bytes, {}, 0};
  const auto payload = cache_plan_payload(*data.chosen, *data.plan, budget);
  if (payload > limits.plan_payload_bytes) throw Failure{Stop::resource_limit, Resource::cache_plan_payload, {}, 0};
  budget.vector<Entry>(1); budget.keys(key_bytes); budget.bytes(key_bytes);
  prepared.insertion.push_back(Entry{*data.key, *data.plan, payload});
  auto& next = prepared.next;
  auto oldest = prepared.cache->entries.begin();
  while (next.entries >= limits.entries || key_bytes > limits.key_bytes - next.key_bytes ||
         payload > limits.plan_payload_bytes - next.plan_payload_bytes) {
    budget.work(); require(oldest != prepared.cache->entries.end() && next.entries > 0);
    require(oldest->key.size() <= next.key_bytes && oldest->payload <= next.plan_payload_bytes);
    next.key_bytes -= static_cast<std::uint64_t>(oldest->key.size());
    next.plan_payload_bytes -= oldest->payload; --next.entries; ++prepared.evictions; ++oldest;
    increment(next.evictions);
  }
  require(next.entries != std::numeric_limits<std::size_t>::max());
  ++next.entries; increment(next.key_bytes, key_bytes); increment(next.plan_payload_bytes, payload); increment(next.insertions);
}
} // namespace detail
} // namespace crown::planner::selection
