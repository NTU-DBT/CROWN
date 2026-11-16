#pragma once

#include "selection_fixture.hpp"
#include "selection_detail.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <tuple>
#include <type_traits>

namespace c05_fault {
template<class Text> inline std::string caller_text(const Text& text) {
  return std::string{text.data(), text.size()};
}
// Counts covered new calls even outside Fault. Zero denial persists through
// cleanup; it does not inject failure into raw system malloc/realloc.
inline thread_local std::ptrdiff_t fail_after = -1;
inline thread_local std::size_t allocations = 0;
inline thread_local bool triggered = false;
inline void position() {
  ++allocations;
  if (fail_after == 0) { triggered = true; throw std::bad_alloc{}; }
  if (fail_after > 0) --fail_after;
}
[[gnu::noinline]] inline void* allocate(std::size_t n) {
  position(); if (auto* p = std::malloc(n ? n : 1)) return p; throw std::bad_alloc{};
}
[[gnu::noinline]] inline void* aligned(std::size_t n, std::size_t alignment) {
  position();
  if (n > std::numeric_limits<std::size_t>::max() - (alignment - 1)) throw std::bad_alloc{};
  const auto rounded = ((n ? n : 1) + alignment - 1) / alignment * alignment;
  if (auto* p = std::aligned_alloc(alignment, rounded)) return p;
  throw std::bad_alloc{};
}
[[gnu::noinline]] inline void release(void* p) noexcept { std::free(p); }
// One lexical, nonnested guard: implicit copying does not create private fault state.
struct Fault {
  explicit Fault(std::size_t position) {
    triggered = false;
    if (position > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max())) throw std::bad_alloc{};
    fail_after = static_cast<std::ptrdiff_t>(position);
  }
  ~Fault() { fail_after = -1; }
};
using namespace c05_test;
namespace ws = runtime::workload;
inline auto metadata(const ws::Metadata& m) {
  return std::tuple{m.attempts, m.committed, m.aborted, m.selected, m.complete, m.aborted_selected,
      m.truncated, m.committed_truncated, m.guards, m.detail_actions, m.cleared_cells, m.merged_cells,
      m.saturated, m.invalid_descriptor, m.protocol_error, m.ordinal_exhausted};
}
inline auto stamp(const ws::Stamp& s) {
  return std::tuple{s.owner, s.committed_epoch, s.interval_start_epoch, s.reset_generation,
      s.configuration_generation, s.segment, s.format_version, s.reset_saturated,
      s.configuration_saturated, s.segment_saturated};
}
inline auto memory(const ws::Memory& m) {
  return std::tuple{m.object_bytes, m.descriptors_bytes, m.committed_bytes, m.attempt_bytes,
      m.previous_bytes, m.retained_payload_bytes, m.routes_bytes};
}
template<class T> bool equal(std::span<const T> a, std::span<const T> b) {
  return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}
inline void workload(const ws::Snapshot& a, const ws::Snapshot& b) {
  check(a.plan().physical_sha256() == b.plan().physical_sha256() && stamp(a.stamp()) == stamp(b.stamp()) &&
      a.options() == b.options() && a.modes() == b.modes() && a.previous_modes() == b.previous_modes() &&
      equal(a.descriptors(), b.descriptors()) && equal(a.cells(), b.cells()) && equal(a.previous_cells(), b.previous_cells()) &&
      metadata(a.metadata()) == metadata(b.metadata()) && metadata(a.previous_metadata()) == metadata(b.previous_metadata()) &&
      memory(a.memory()) == memory(b.memory()) && a.pending() == b.pending() && a.has_previous() == b.has_previous() &&
      a.replaced_history() == b.replaced_history() && a.previous_interval_start_epoch() == b.previous_interval_start_epoch() &&
      a.previous_interval_end_epoch() == b.previous_interval_end_epoch() && a.detail_availability() == b.detail_availability(),
      "C05 failed attempt changed complete workload snapshot");
}
inline std::vector<std::string> rank_image(const pr::Result& result) {
  std::vector<std::string> out{result.selected().structural_key()};
  for (const auto& score : result.scores()) {
    out.insert(out.end(), {caller_text(score.structural_key), std::to_string(score.height), caller_text(score.numerator),
        caller_text(score.denominator), caller_text(score.slots)});
    for (const auto& d : score.depths) out.insert(out.end(), {std::to_string(d.occurrence.value), std::to_string(d.table.value), std::to_string(d.depth)});
    for (const auto& t : score.table_depths) out.insert(out.end(), {std::to_string(t.table.value), std::to_string(t.inserts), std::to_string(t.erases), caller_text(t.depth_sum), caller_text(t.contribution)});
    for (const auto& p : score.populations) out.insert(out.end(), {std::to_string(p.node.value), caller_text(p.records), caller_text(p.survivors), caller_text(p.parent_support),
        p.visible ? caller_text(*p.visible) : std::string("unavailable")});
    for (const auto& t : score.slot_terms) out.insert(out.end(), {std::to_string(t.relation.value), t.index ? std::to_string(t.index->value) : "relation", std::to_string(t.width), caller_text(t.population), caller_text(t.contribution)});
    if (score.modeled_plan) out.push_back(io::write_physical(*score.modeled_plan).dump());
  }
  return out;
}
// Ordinary text/JSON export copies key/plan payload; this is not a cheap handle copy.
inline std::vector<std::string> selection_image(const ps::Selection& result) {
  std::vector<std::string> out{result.selected().structural_key(), std::to_string(result.selected_index()),
      io::write_physical(result.plan()).dump(), std::to_string(static_cast<unsigned>(result.effective_policy())),
      std::to_string(result.fallback_reasons()), result.cache_binding() ? caller_text(*result.cache_binding()) : std::string("no-key")};
  for (const auto& assessment : result.assessments()) {
    out.push_back(std::to_string(static_cast<unsigned>(assessment.purpose)));
    auto entries = rank_image(assessment.result); out.insert(out.end(), entries.begin(), entries.end());
  }
  for (const auto& decision : result.decisions())
    out.insert(out.end(), {std::to_string(decision.candidate_index), std::to_string(static_cast<unsigned>(decision.eligibility))});
  return out;
}
inline const ps::Selection& pure(const ps::Selection& value) { return value; }
inline const ps::Selection& pure(const rs::CurrentSelection& value) { return value.selection(); }
inline auto cache_image(ps::PlanCache& cache) {
  std::vector<std::tuple<std::string, std::string, std::uint64_t>> out;
  for (const auto& entry : ps::detail::Factory::cache(&cache)->entries)
    out.emplace_back(entry.key, io::write_physical(entry.plan).dump(), entry.payload);
  return out;
}
struct Totals { std::size_t positions{}, recovered{}, publication_failures{}, assessment_failures{}, lowering_failures{}; };
// Only invoke runs under Fault; image/proof/owner/cache verification follows disarming.
// The calibrated positions are C++ new attempts, not a system malloc-failure sweep.
template<class Invoke>
void sweep(const char* label, const planner::CandidateSnapshot& snapshot, runtime::PhysicalRuntime& owner,
           const ps::Source& source, const pr::Evidence& evidence, Invoke invoke, bool warm, Totals& totals) {
  const auto seed_request = request(ps::Policy::height_only);
  const auto make_cache = [&] {
    auto cache = ps::PlanCache::create({1, 8 * 1024 * 1024, 32 * 1024 * 1024});
    if (warm) static_cast<void>(complete(invoke(cache)));
    else static_cast<void>(complete(ps::select(snapshot, source, seed_request, evidence, &cache, ps::CacheUse::read_write)));
    return cache;
  };
  auto measuring = make_cache(); allocations = 0;
  const auto baseline_attempt = invoke(measuring); const auto count = allocations;
  const auto baseline = complete(baseline_attempt); const auto baseline_image = selection_image(pure(baseline));
  check(count != 0 && count < 200'000, "C05 fault position guard exceeded");
  auto cache = make_cache(); const auto initial = cache_image(cache); const auto stats = cache.statistics();
  const auto prior = complete(ps::select(snapshot, source, seed_request, evidence));
  const auto prior_image = selection_image(prior); const auto prior_usage = prior.usage();
  const auto id = owner.owner(); const auto sequence = owner.sequence(); const auto canonical = owner.canonical_state();
  const auto collected = owner.workload_statistics();
  std::vector<std::string> keys;
  for (std::size_t i = 0; i < snapshot.candidate_count(); ++i) keys.push_back(snapshot.candidate(i)->structural_key());
  const auto verify = [&] {
    check(owner.owner() == id && owner.sequence() == sequence && owner.canonical_state() == canonical,
        "C05 fault changed complete owner state");
    workload(collected, owner.workload_statistics());
    check(snapshot.valid() && snapshot.original_proof().valid() && snapshot.candidate_count() == keys.size(), "C05 fault damaged proof/snapshot");
    for (std::size_t i = 0; i < keys.size(); ++i)
      check(snapshot.candidate(i)->valid() && snapshot.candidate(i)->structural_key() == keys[i], "C05 fault damaged candidate");
    check(selection_image(prior) == prior_image && prior.usage() == prior_usage, "C05 fault rewrote retained selection");
    check(selection_image(pure(baseline)) == baseline_image, "C05 fault rewrote earlier complete assessment");
    if constexpr (std::is_same_v<std::remove_cv_t<decltype(baseline)>, rs::CurrentSelection>) {
      check(baseline.capture().captured().has_value() && baseline.capture().inputs().identity().owner == id.value &&
          baseline.capture().inputs().identity().epoch == sequence, "C05 old actual capture identity changed");
      workload(collected, baseline.capture().captured()->workload());
    }
  };
  for (std::size_t position = 0; position < count; ++position) {
    std::remove_cv_t<decltype(baseline_attempt)> attempted;
    { Fault fault(position); attempted = invoke(cache); }
    check(triggered, "C05 injected persistent allocation position was not reached");
    if (attempted.selection) {
      check(attempted.stop == ps::Stop::complete && selection_image(pure(*attempted.selection)) == baseline_image,
          "C05 cleanup recovery changed the complete published bundle");
      ++totals.recovered; cache = make_cache();
    } else {
      check(attempted.stop == ps::Stop::allocation_failure ||
          (attempted.stop == ps::Stop::resource_limit && attempted.component_stop == pr::Stop::lowering_limit),
          "C05 persistent allocation failure changed diagnostic class");
      check(cache.statistics() == stats && cache_image(cache) == initial, "C05 failure mutated cache statistics/FIFO/artifact");
      if (attempted.stage == ps::Stage::publication) ++totals.publication_failures;
      if (attempted.stage == ps::Stage::constraint_assessment || attempted.stage == ps::Stage::primary_assessment) ++totals.assessment_failures;
      if (attempted.stage == ps::Stage::lowering) ++totals.lowering_failures;
    }
    verify(); ++totals.positions;
  }
  const auto retry = complete(invoke(cache));
  check(selection_image(pure(retry)) == baseline_image, "C05 post-failure retry changed exact bundle"); verify();
  std::cout << label << " allocation_positions=" << count << '\n';
}
} // namespace c05_fault

// No-inline allocation/deallocation seams keep optimized compilers from
// diagnosing the intentional replacement-new malloc/free implementation.
[[gnu::noinline]] void* operator new(std::size_t n) { return c05_fault::allocate(n); }
[[gnu::noinline]] void* operator new[](std::size_t n) { return c05_fault::allocate(n); }
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return c05_fault::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return c05_fault::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment) { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment) { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void operator delete(void* p) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { c05_fault::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { c05_fault::release(p); }
