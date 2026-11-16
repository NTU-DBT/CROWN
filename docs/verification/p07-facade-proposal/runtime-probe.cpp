// Supplemental isolated probe, not a registered test or P07 acceptance suite.
#define main crown_p05_original_exception_test_main
#include "../../../tests/unit/residual_exception_test.cpp"
#undef main
#include "../p07-api-proposal-2026-11-07.hpp"
#include "crown/api/error.hpp"

namespace {
VerifiedOptimum prove(const Fixture& f) {
  auto owner = ExactSearch::create(f.catalog, f.query);
  const auto result = owner.advance(all_work);
  check(result.progress.result == ResultKind::verified_optimum && owner.optimum().has_value(),
        "P06 did not produce an original-query verified optimum");
  return *owner.optimum();
}
CandidateStop drain(CandidateProvider& p, std::uint64_t quantum = 1'000'000) {
  for (std::size_t i = 0; i < 2'000'000; ++i) {
    const auto result = p.advance({quantum, {}});
    if (result.stopped_for != CandidateStop::quantum_work &&
        result.stopped_for != CandidateStop::candidate_ready) return result.stopped_for;
  }
  throw std::runtime_error("facade drain exceeded probe guard");
}
std::set<std::string> keys(const CandidateProvider& p) {
  std::set<std::string> result;
  for (std::size_t i = 0; i < p.candidate_count(); ++i) {
    const auto c = p.candidate(i);
    check(c && c->valid(), "missing candidate handle");
    const auto report = validate_tree(c->catalog(), c->query(), c->tree());
    check(report.valid && report.native_height == c->height() &&
              c->height() == p.original_proof().height() &&
              same_certificate(c->original_proof().certificate(), p.original_proof().certificate()),
          "candidate lost P02 validity, minimum height or original certificate");
    check(result.insert(c->structural_key()).second, "duplicate emitted structural key");
  }
  return result;
}
bool same_stats(const CandidateStatistics& a, const CandidateStatistics& b) {
  return a.proposed == b.proposed && a.rejected == b.rejected && a.taller == b.taller &&
      a.duplicates == b.duplicates && a.published == b.published &&
      a.topologies == b.topologies && a.scope_tuples == b.scope_tuples && a.cache_seeded == b.cache_seeded;
}
bool same_shape(const CandidateProgress& a, const CandidateProgress& b) {
  return a.phase == b.phase && a.family_exhausted == b.family_exhausted &&
      a.verified_original_height == b.verified_original_height && a.candidate_count == b.candidate_count &&
      a.records == b.records && a.cells == b.cells && same_stats(a.statistics, b.statistics) &&
      a.work.committed_transitions == b.work.committed_transitions &&
      a.work.current_depth == b.work.current_depth && a.work.peak_depth == b.work.peak_depth;
}
template<class F> void expect_error(F&& action, const char* code) {
  bool rejected = false;
  try { action(); } catch (const crown::Error& e) { rejected = e.code() == code; }
  check(rejected, "admission failed to reject with expected error code");
}
void zero_grants(CandidateProvider& owner) {
  const auto before = owner.progress();
  check(owner.advance({0, {}}).stopped_for == CandidateStop::quantum_work, "zero work rejected");
  check(owner.advance({1, std::chrono::nanoseconds{0}}).stopped_for == CandidateStop::quantum_time,
        "zero time rejected");
  check(owner.advance({1, std::chrono::nanoseconds{-1}}).stopped_for == CandidateStop::invalid_quantum,
        "negative time accepted");
  const auto after = owner.progress();
  check(same_shape(before, after) && before.work == after.work && before.last_stop == after.last_stop,
        "zero or negative quantum mutated progress");
}
void resource_checks(const VerifiedOptimum& proof, const std::set<std::string>& expected) {
  for (int which = 0; which < 6; ++which) {
    CandidateLimits limits;
    CandidateStop stop = CandidateStop::none;
    switch (which) {
      case 0: limits.logical_depth = 0; stop = CandidateStop::depth_limit; break;
      case 1: limits.records = 0; stop = CandidateStop::record_limit; break;
      case 2: limits.cells = 0; stop = CandidateStop::cell_limit; break;
      case 3: limits.retained_candidates = 0; stop = CandidateStop::candidate_capacity; break;
      case 4: limits.enumeration.work = 0; stop = CandidateStop::total_work; break;
      case 5: limits.enumeration.active_time = std::chrono::nanoseconds{0}; stop = CandidateStop::total_time; break;
    }
    auto owner = CandidateProvider::create(proof, {}, limits);
    check(drain(owner) == stop, "resource did not stop at requested ceiling");
    const auto stopped = owner.progress();
    check(owner.candidate_count() == 0 && !stopped.family_exhausted, "resource stop published or exhausted");
    if (which == 0) check(stopped.work.current_depth == 0 && stopped.work.peak_depth == 0,
                          "blocked first frame counted as owned depth");
    zero_grants(owner);
    check(drain(owner) == stop && same_shape(stopped, owner.progress()), "resource retry changed saved stage");
    CandidateLimits raised;
    check(owner.raise_limits(raised) == LimitChange::applied, "monotone resource raise failed");
    check(drain(owner, 1) == CandidateStop::exhausted && keys(owner) == expected,
          "resource raise did not resume exact same family");
    check(owner.progress().limit_revision == 1, "limit revision missing");
  }
  CandidateLimits limits;
  limits.retained_candidates = 1;
  auto owner = CandidateProvider::create(proof, {}, limits);
  check(drain(owner) == CandidateStop::candidate_capacity && owner.candidate_count() == 1,
        "full nonzero cap did not preserve prior publication");
  const auto retained = *owner.candidate(0);
  auto smaller = limits; smaller.retained_candidates = 0;
  check(owner.raise_limits(smaller) == LimitChange::not_monotone, "decreasing cap accepted");
  limits.retained_candidates = 10;
  check(owner.raise_limits(limits) == LimitChange::applied && drain(owner) == CandidateStop::exhausted &&
            keys(owner) == expected && retained.structural_key() == owner.candidate(0)->structural_key(),
        "pending publication lost across cap raise");
}
void cache_checks(const Fixture& f, const VerifiedOptimum& proof, const CandidateSnapshot& full,
                  const std::set<std::string>& expected) {
  auto prefix_owner = CandidateProvider::create(proof);
  check(prefix_owner.advance(all_work).stopped_for == CandidateStop::candidate_ready, "first publication missing");
  auto partial = prefix_owner.snapshot();
  check(partial.candidate_count() == 1 && !partial.family_exhausted(), "prefix snapshot misstates exhaustion");
  prefix_owner.cancel();
  check(!partial.family_exhausted() && partial.candidate(0)->valid(), "snapshot changed after cancel");
  for (const auto& prefix : {partial, full}) {
    const auto fresh_proof = prove(f);
    auto replay = CandidateProvider::create(fresh_proof, {}, {}, {}, prefix);
    check(!replay.progress().family_exhausted && replay.candidate_count() == 0,
          "new provider inherited prefix cursor/exhaustion");
    check(drain(replay) == CandidateStop::exhausted && keys(replay) == expected &&
              replay.progress().statistics.cache_seeded == prefix.candidate_count(),
          "cached prefix failed replay/dedup/fresh regeneration");
    for (std::size_t i = 0; i < replay.candidate_count(); ++i) {
      auto c = *replay.candidate(i);
      check(&c.original_proof().certificate() == &fresh_proof.certificate(),
            "cache transplanted original proof authority");
      for (std::size_t j = 0; j < prefix.candidate_count(); ++j) {
        const auto old = *prefix.candidate(j);
        if (c.structural_key() == old.structural_key())
          check(c.provenance().source == old.provenance().source &&
                    c.provenance().sequence == old.provenance().sequence,
                "prefix replay rewrote primary generation provenance");
      }
    }
  }
  auto b = f; b.query.atoms[0].occurrence += "_renamed";
  auto c = f; c.catalog.tables[0].statistics.row_count = 19;
  const auto proof_b = prove(b), proof_c = prove(c);
  auto pb = CandidateProvider::create(proof_b), pc = CandidateProvider::create(proof_c);
  auto cache = CandidateCache::create(2);
  check(cache.install(full) == CandidateCacheInstall::inserted &&
            cache.install(pb.snapshot()) == CandidateCacheInstall::inserted && cache.lookup(proof).has_value(),
        "cache setup or exact hit failed");
  check(cache.install(partial) == CandidateCacheInstall::replaced, "cache replacement failed");
  check(cache.install(pc.snapshot()) == CandidateCacheInstall::inserted && !cache.lookup(proof) &&
            cache.lookup(proof_b).has_value() && cache.lookup(proof_c).has_value(),
        "FIFO was reordered by hit/replacement or binding metadata collided");
  const auto s = cache.statistics();
  check(s.entries == 2 && s.insertions == 3 && s.replacements == 1 && s.evictions == 1 &&
            s.hits == 3 && s.misses == 1, "cache statistics disagree");
  cache.clear();
  check(cache.statistics().entries == 0 && cache.statistics().insertions == s.insertions,
        "cache clear reset cumulative statistics");
  auto disabled = CandidateCache::create(0);
  check(disabled.install(full) == CandidateCacheInstall::disabled && disabled.statistics().entries == 0,
        "disabled cache installed entry");
  expect_error([&] { static_cast<void>(CandidateProvider::create(proof_b, {}, {}, {}, full)); }, "candidate_binding");
  expect_error([&] { static_cast<void>(CandidateProvider::create(proof_c, {}, {}, {}, full)); }, "candidate_binding");
  for (int i = 0; i < 6; ++i) {
    CandidateContext bad;
    switch (i) {
      case 0: bad.updates = static_cast<CandidateUpdateProfile>(99); break;
      case 1: bad.arithmetic += "!"; break;
      case 2: bad.planner += "!"; break;
      case 3: bad.optimization += "!"; break;
      case 4: bad.cost_model += "!"; break;
      case 5: bad.canonicalization += "!"; break;
    }
    expect_error([&] { static_cast<void>(CandidateProvider::create(proof, bad)); }, "invalid_candidate_context");
    expect_error([&] { static_cast<void>(cache.lookup(proof, bad)); }, "invalid_candidate_context");
  }
}
void fault_checks(const VerifiedOptimum& proof, const std::set<std::string>& expected) {
  auto baseline = CandidateProvider::create(proof);
  allocation_count = 0;
  check(drain(baseline) == CandidateStop::exhausted, "fault baseline failed");
  const auto positions = allocation_count;
  const auto final = baseline.progress();
  for (std::size_t point = 0; point < positions; ++point) {
    auto owner = CandidateProvider::create(proof);
    bool failed = false, repeated = true;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      failed = drain(owner) == CandidateStop::allocation_failure;
      const auto stopped = owner.progress();
      for (int retry = 0; retry < 2; ++retry) {
        const auto result = owner.advance(all_work);
        repeated = repeated && result.stopped_for == CandidateStop::allocation_failure &&
            same_shape(stopped, result.progress) &&
            result.progress.work.allocation_failures == stopped.work.allocation_failures + static_cast<std::uint64_t>(retry + 1);
      }
    }
    if (!failed || !repeated) {
      std::cerr << "fault failed point=" << point << " failed=" << failed << " repeats=" << repeated << '\n';
      check(false, "persistent allocation failure lost pending stage");
    }
    check(drain(owner) == CandidateStop::exhausted && same_shape(final, owner.progress()) && keys(owner) == expected,
          "allocation retry failed final family/accounting recovery");
  }
  std::cout << "facade_fault_positions=" << positions << " persistent_retries=2 recovery=same_owner\n";
  auto cache = CandidateCache::create(1);
  auto snapshot = baseline.snapshot();
  const auto before = cache.statistics();
  bool failed = false;
  { FaultScope fault(0); try { static_cast<void>(cache.install(snapshot)); } catch (const std::bad_alloc&) { failed = true; } }
  check(failed && cache.statistics().entries == before.entries && cache.statistics().insertions == before.insertions,
        "cache allocation failure changed entries or statistics");
  check(cache.install(snapshot) == CandidateCacheInstall::inserted, "cache failed to retry install");
}
}
int main() {
  try {
    const auto path = scoped_fixture({{0}, {0, 1}, {1}}, {});
    auto self = scoped_fixture({{0}, {0}, {0}}, {});
    self.catalog.tables.resize(1);
    for (auto& atom : self.query.atoms) atom.table = TableId{0};
    const auto proof = prove(path), self_proof = prove(self);
    check(proof.height() == 2 && self_proof.height() == 1, "unexpected fixture minima");
    auto owner = CandidateProvider::create(proof);
    check(owner.original_proof().valid() && owner.candidate_count() == 0, "proof missing before first candidate");
    zero_grants(owner);
    check(drain(owner) == CandidateStop::exhausted, "path family did not exhaust");
    const auto expected = keys(owner);
    check(expected.size() == 3 && owner.progress().statistics.duplicates > 0, "path family is not 3 deduplicated plans");
    auto self_owner = CandidateProvider::create(self_proof);
    check(drain(self_owner, 1) == CandidateStop::exhausted && keys(self_owner).size() == 4,
          "equal-scope self-join family is not 4 plans");
    auto sliced = CandidateProvider::create(proof);
    check(drain(sliced, 1) == CandidateStop::exhausted && keys(sliced) == expected &&
              same_shape(owner.progress(), sliced.progress()), "unit slicing changed family/accounting");
    auto full = owner.snapshot();
    resource_checks(proof, expected);
    cache_checks(path, proof, full, expected);
    auto residual_owner = ResidualSearch::create(path.catalog, path.query);
    check(residual_owner.advance(all_work).stopped_for == ResidualStopReason::complete && residual_owner.candidate(),
          "residual seed preparation failed");
    auto seeded = CandidateProvider::create(proof, {}, {}, residual_owner.candidate());
    check(drain(seeded) == CandidateStop::exhausted && keys(seeded) == expected,
          "residual seed changed minimum family");
    expect_error([&] { static_cast<void>(CandidateProvider::create(self_proof, {}, {}, residual_owner.candidate())); },
                 "candidate_binding");
    auto cancelled = CandidateProvider::create(proof);
    check(cancelled.advance(all_work).stopped_for == CandidateStop::candidate_ready, "cancel setup missing candidate");
    auto retained = *cancelled.candidate(0);
    auto frozen = cancelled.snapshot();
    { FaultScope fault(0); cancelled.cancel(); }
    check(cancelled.advance(all_work).stopped_for == CandidateStop::cancelled &&
              cancelled.original_proof().valid() && cancelled.progress().work.current_depth == 0 &&
              cancelled.candidate_count() == 1 && !frozen.family_exhausted(), "cancel lost proof/publication or exhausted");
    { auto moved = std::move(cancelled); check(cancelled.advance(all_work).stopped_for == CandidateStop::moved_from,
                                               "moved provider not reported"); }
    check(retained.valid() && frozen.candidate(0)->structural_key() == retained.structural_key() &&
              validate_tree(retained.catalog(), retained.query(), retained.tree()).valid,
          "candidate/snapshot failed provider lifetime independence");
    fault_checks(proof, expected);
    std::cout << "boolean_path height=2 unique_plans=3 self_join height=1 unique_plans=4\n"
              << "proof_gate=P06+P02 slicing=equal resource_raises=6 plus_pending_cap=yes\n"
              << "cache=exact_binding+six_context_fences+FIFO+prefix_replay lifetime=owned cancellation=noalloc\n"
              << "proposal_only P07=not_started\n";
  } catch (const std::exception& e) {
    fail_after = -1; std::cerr << e.what() << '\n'; return 1;
  }
}
