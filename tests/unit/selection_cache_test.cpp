#include "selection_fixture.hpp"
#include "selection_detail.hpp"
#include <iostream>
#include <tuple>

namespace {
using namespace c05_test;
namespace sd = ps::detail;
auto image(ps::PlanCache& cache) {
  std::vector<std::tuple<std::string, std::string, std::uint64_t>> out;
  const auto* data = sd::Factory::cache(&cache);
  for (const auto& entry : data->entries) out.emplace_back(entry.key, entry.plan.physical_sha256(), entry.payload);
  return out;
}
planner::VerifiedOptimum replay(const planner::VerifiedOptimum& original, bool rename) {
  const auto binding = original.binding(); auto certificate = original.certificate();
  if (rename) {
    check(certificate.tree.has_value(), "C05 replay fixture omitted tree");
    auto& tree = *certificate.tree;
    std::reverse(tree.nodes.begin(), tree.nodes.end());
    for (auto& node : tree.nodes) {
      node.id += "_relabel"; std::reverse(node.children.begin(), node.children.end());
      for (auto& child : node.children) child.value = tree.nodes.size() - 1 - child.value;
    }
    if (tree.root) tree.root->value = tree.nodes.size() - 1 - tree.root->value;
    if (tree.claimed_connex) for (auto& id : *tree.claimed_connex) id.value = tree.nodes.size() - 1 - id.value;
  }
  planner::ReplayOptions options; options.limits.work = 50'000'000;
  auto replay = planner::CertificateReplay::create(binding.catalog(), binding.query(), std::move(certificate), options);
  for (std::size_t n = 0; n < 100'000 && !replay.checked(); ++n) static_cast<void>(replay.advance({1000, {}}));
  check(replay.checked() && replay.checked()->optimum(), "C05 finite certificate replay failed");
  return *replay.checked()->optimum();
}
planner::CandidateSnapshot family(const planner::VerifiedOptimum& proof) {
  auto provider = planner::CandidateProvider::create(proof);
  for (std::size_t n = 0; n < 100'000 && !provider.progress().family_exhausted; ++n)
    static_cast<void>(provider.advance({1000, {}}));
  check(provider.progress().family_exhausted, "C05 replay family incomplete"); return provider.snapshot();
}
}
int main() { try {
  using namespace c05_test;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  auto cache = ps::PlanCache::create({2, 8 * 1024 * 1024, 32 * 1024 * 1024});
  const auto height = request(ps::Policy::height_only); const auto memory = request(ps::Policy::tuple_index_slots);
  const auto depth = request(ps::Policy::committed_input_native_depth);
  const auto a = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_write));
  const auto b = complete(ps::select(snapshot, source, memory, evidence, &cache, ps::CacheUse::read_write));
  check(cache.statistics().entries == 2 && cache.statistics().insertions == 2, "C05 cache two insertions");
  const auto before_hit = image(cache);
  const auto ah = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_only));
  check(ah.cache_observation().disposition == ps::CacheDisposition::hit && image(cache) == before_hit &&
      ah.usage().lowering_work == 0 && ah.cache_binding() == a.cache_binding(), "C05 read-only hit/order/lowering");
  const auto bh = complete(ps::select(snapshot, source, memory, evidence, &cache, ps::CacheUse::read_only));
  check(bh.cache_observation().disposition == ps::CacheDisposition::hit && bh.usage().lowering_work == b.usage().lowering_work &&
      bh.usage().lowering_work != 0, "C05 cache silently skipped full Q lowering");
  slot_oracle(assessment(bh, pr::Policy::tuple_index_slots));
  const auto c = complete(ps::select(snapshot, source, depth, evidence, &cache, ps::CacheUse::read_write));
  const auto after_c = image(cache);
  check(cache.statistics().entries == 2 && cache.statistics().evictions == 1 && std::get<0>(after_c[0]) == *b.cache_binding() &&
      std::get<0>(after_c[1]) == *c.cache_binding(), "C05 FIFO hit reordered eviction");
  const auto missing = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_only));
  check(missing.cache_observation().disposition == ps::CacheDisposition::miss_read_only && image(cache) == after_c,
      "C05 read-only miss inserted an entry");
  check(io::write_physical(ah.plan()).dump() == io::write_physical(a.plan()).dump(), "C05 reused plan descriptor bytes changed");
  const auto saved = image(cache); const auto stats = cache.statistics();
  sd::Factory::cache(&cache)->statistics.hits = UINT64_MAX;
  const auto saturated_stats = cache.statistics();
  const auto saturated = ps::select(snapshot, source, depth, evidence, &cache, ps::CacheUse::read_only);
  check(!saturated.selection && saturated.stop == ps::Stop::resource_limit && saturated.resource == ps::Resource::counter_overflow &&
      image(cache) == saved && cache.statistics() == saturated_stats, "C05 cache counter wrapped or mutated");
  sd::Factory::cache(&cache)->statistics = stats;
  auto moved = std::move(cache);
  check(!cache.valid() && ps::select(snapshot, source, height, {}, &cache, ps::CacheUse::read_only).stop == ps::Stop::invalid_handle,
      "C05 moved cache admitted");
  check(ps::select(snapshot, source, height, {}, nullptr, ps::CacheUse::read_only).stop == ps::Stop::invalid_request,
      "C05 missing explicit cache was ignored");
  moved.clear(); check(moved.statistics() == ps::CacheStatistics{}, "C05 clear did not reset cache state");
  valid_plan(a, f.database); valid_plan(b, f.database); valid_plan(c, f.database);
  auto disabled = ps::PlanCache::create({0, 0, 0});
  const auto off = complete(ps::select(snapshot, source, height, {}, &disabled, ps::CacheUse::read_write));
  check(off.cache_observation().disposition == ps::CacheDisposition::disabled && !off.cache_binding() &&
      disabled.statistics() == ps::CacheStatistics{}, "C05 disabled cache did work or published entries");
  for (bool key : {false, true}) {
    auto tiny = ps::PlanCache::create({1, key ? 1U : 8U * 1024U * 1024U, key ? 32U * 1024U * 1024U : 1U});
    const auto result = ps::select(snapshot, source, height, {}, &tiny, ps::CacheUse::read_write);
    check(!result.selection && result.stop == ps::Stop::resource_limit && result.resource ==
        (key ? ps::Resource::cache_key_bytes : ps::Resource::cache_plan_payload) && tiny.statistics() == ps::CacheStatistics{},
        "C05 oversized entry silently bypassed cache or changed counters");
  }
  // A separately replayed, byte-identical original proof must remain the new
  // result's proof even when the compiled artifact can be reused.
  auto exact_cache = ps::PlanCache::create();
  const auto old = complete(ps::select(snapshot, source, height, {}, &exact_cache, ps::CacheUse::read_write));
  const auto new_proof = replay(snapshot.original_proof(), false); const auto new_family = family(new_proof);
  const auto fresh = complete(ps::select(new_family, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(fresh.cache_observation().disposition == ps::CacheDisposition::hit &&
      &fresh.snapshot().original_proof().certificate() == &new_proof.certificate() &&
      &fresh.snapshot().original_proof().certificate() != &old.snapshot().original_proof().certificate(),
      "C05 cache transplanted an old proof");
  const auto renamed_proof = replay(snapshot.original_proof(), true); const auto renamed = family(renamed_proof);
  const auto distinct = complete(ps::select(renamed, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(distinct.selected().structural_key() == old.selected().structural_key() && distinct.cache_binding() != old.cache_binding() &&
      distinct.cache_observation().disposition == ps::CacheDisposition::miss_read_only, "C05 erased raw family representation in cache key");
  const auto partial = prefix(snapshot.original_proof());
  const auto partial_choice = complete(ps::select(partial, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(partial_choice.cache_binding() != old.cache_binding() && !partial_choice.snapshot().family_exhausted(), "C05 family key erased retained prefix");
  std::cout << "C05 whole-artifact FIFO, read-only reuse, lifetime, counter/capacity and exact-family/proof cache cases passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
