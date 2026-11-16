#include "ranking_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/planner/selection.hpp"
#include <array>
#include <iostream>

namespace {
using namespace crown;
using c02_test::check;
namespace ps = planner::selection;
namespace ip = crown::patterns;
namespace pp = planner::patterns;

ps::Selection complete(ps::Attempt attempt) {
  check(attempt.stop == ps::Stop::complete && attempt.selection.has_value(),
        "pattern-aware selection failed");
  return *attempt.selection;
}

// Prove a decision consequence in the real retained family, then verify exact
// rule/cache binding and the unchanged original height authority.
void decision_contract() {
  const auto fixture = c02_test::fixture();
  const auto snapshot = c02_test::candidates(fixture);
  const auto source = CompiledProgram::standalone(planner::lower_tree(
      fixture.catalog, fixture.query, snapshot.candidate(0)->tree()));
  const ps::Source basis = ps::PhysicalBasis{source};
  ps::Request request; request.policy = ps::Policy::height_only;
  auto cache = ps::PlanCache::create();
  const auto baseline = complete(ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write));
  check(baseline.pattern_analyses().empty() && !baseline.request().update_patterns,
        "default selection fabricated a pattern condition");
  const bool choose_t = c02_test::shape(baseline.selected().tree()) != 1;
  const std::array rules{ip::TableRule{TableId{choose_t ? 2U : 0U}, true, 0}};
  request.update_patterns = ip::Declaration::capture(source.account(), source, rules);
  const auto selected = complete(ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write));
  check(c02_test::shape(selected.selected().tree()) == (choose_t ? 1 : 2) &&
        selected.selected_index() != baseline.selected_index(),
        "pattern admissibility did not change the actual selected candidate");
  check(selected.selected().height() == snapshot.original_proof().height() &&
        selected.plan().guarantee().height_status == "valid_upper_bound" &&
        selected.plan().physical_source_sha256() == source.physical_source_sha256(),
        "conditional selection changed structural authority or physical source binding");
  check(selected.pattern_analyses().size() == snapshot.candidate_count() &&
        selected.export_request().update_patterns->export_record().rules == std::vector<ip::TableRule>(rules.begin(), rules.end()),
        "successful result omitted reproducible conditional context");
  unsigned eligible = 0;
  for (const auto& decision : selected.decisions()) {
    const auto& analysis = selected.pattern_analyses()[decision.candidate_index];
    const bool proved = analysis.sufficient != pp::SufficientCase::unknown;
    check((decision.eligibility != ps::Eligibility::pattern_unproved) == proved,
          "decision eligibility disagrees with its retained edge analysis");
    eligible += proved;
  }
  check(eligible == 1 && selected.cache_binding() && baseline.cache_binding() &&
        *selected.cache_binding() != *baseline.cache_binding(), "pattern condition did not bind the artifact cache");
  const auto hit = complete(ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write));
  check(hit.cache_observation().disposition == ps::CacheDisposition::hit &&
        hit.selected_index() == selected.selected_index(), "exact declared request did not reuse its artifact");

  // Equal compatibility does not allow unrelated raw FIFO group IDs to alias.
  std::array joint{ip::TableRule{TableId{0}, false, 41}, ip::TableRule{TableId{1}, false, 41},
      ip::TableRule{TableId{2}, false, 41}};
  request.update_patterns = ip::Declaration::capture(source.account(), source, joint);
  const auto first_group = complete(ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write));
  for (auto& rule : joint) rule.fifo_scope = UINT64_MAX;
  request.update_patterns = ip::Declaration::capture(source.account(), source, joint);
  const auto second_group = complete(ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write));
  check(*first_group.cache_binding() != *second_group.cache_binding() &&
        second_group.cache_observation().disposition == ps::CacheDisposition::inserted,
        "cache omitted the declared raw scope ID");

  // Failed processing leaves no partial result, cache action or live allocation.
  auto low = request; low.limits.aggregate.work = second_group.usage().work - 1;
  const auto before_cache = cache.statistics();
  const auto before_memory = source.account().statistics().current;
  const auto stopped = ps::select(snapshot, basis, low, {}, &cache, ps::CacheUse::read_write);
  check(stopped.stop == ps::Stop::resource_limit && !stopped.selection &&
        cache.statistics() == before_cache && source.account().statistics().current == before_memory,
        "insufficient aggregate grant published speculative pattern context/cache state");

  request.update_patterns = ip::Declaration::capture(source.account(), source, {});
  const auto unsatisfied = ps::select(snapshot, basis, request);
  check(unsatisfied.stop == ps::Stop::constraint_unsatisfied && !unsatisfied.selection,
        "unproved retained family silently fell back to an incompatible plan");
  check(ps::select(snapshot, ps::Source{ps::DirectCQ{}}, request).stop == ps::Stop::unsupported_model,
        "declaration was accepted without its native source binding");
  auto record = request.update_patterns->export_record();
  record.source_sha256[0] = record.source_sha256[0] == '0' ? '1' : '0';
  request.update_patterns = ip::Declaration::import(source.account(), record);
  check(ps::select(snapshot, basis, request).stop == ps::Stop::binding_mismatch,
        "selection accepted a foreign imported declaration");
}
// Persistently deny each covered ordinary/aligned C++ allocation, including
// receiving-account pattern vectors/edges. Raw malloc is outside this seam.
void allocation_contract() {
  const auto fixture = c02_test::fixture();
  const auto snapshot = c02_test::candidates(fixture);
  const auto account = resource::MemoryAccount::create(1 << 20);
  const auto compiler_plan = planner::lower_tree(fixture.catalog, fixture.query, snapshot.candidate(0)->tree());
  const auto source = CompiledProgram::compile(account, compiler_plan);
  const ps::Source basis = ps::PhysicalBasis{source};
  const std::array rules{ip::TableRule{TableId{0}, false, 7}, ip::TableRule{TableId{1}, false, 7},
      ip::TableRule{TableId{2}, false, 7}};
  ps::Request request; request.policy = ps::Policy::height_only;
  request.update_patterns = ip::Declaration::capture(account, source, rules);
  ps::Attempt healthy;
  std::size_t positions = 0;
  {
    auto cache = ps::PlanCache::create();
    s04_alloc::Scope count;
    healthy = ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write);
    positions = s04_alloc::calls;
  }
  check(healthy.stop == ps::Stop::complete && healthy.selection && positions > 0 && positions < 100'000,
        "allocation sweep has no finite healthy control");
  std::size_t denied = 0, pattern_denied = 0;
  bool completed = false;
  for (std::size_t cut = 0; cut <= positions; ++cut) {
    auto cache = ps::PlanCache::create();
    const auto before_cache = cache.statistics();
    const auto before_memory = account.statistics().current;
    ps::Attempt attempt;
    bool triggered = false;
    {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      attempt = ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write);
      triggered = s04_alloc::triggered;
    }
    if (!triggered) {
      check(attempt.stop == ps::Stop::complete && attempt.selection,
            "uninjected selection failed after allocation sweep");
      completed = true;
      break;
    }
    if (attempt.selection) {
      check(attempt.stop == ps::Stop::complete &&
            attempt.selection->selected_index() == healthy.selection->selected_index(),
            "recovered allocation denial changed the selected candidate");
      continue;
    }
    ++denied;
    pattern_denied += attempt.stage == ps::Stage::pattern_analysis;
    check(attempt.stop == ps::Stop::allocation_failure && cache.statistics() == before_cache &&
          account.statistics().current == before_memory,
          "allocation denial exposed partial pattern/cache state or retained storage");
    check(healthy.selection->request().update_patterns->matches(source) &&
          healthy.selection->pattern_analyses().size() == snapshot.candidate_count(),
          "failed selection damaged a previously retained analysis");
  }
  check(completed && denied > 0 && pattern_denied > 0,
        "allocation sweep missed pattern preparation or its healthy continuation");

  // Occupy the remaining immutable native cap, independently of global-new
  // injection. The public call must refuse allocation and preserve its cache.
  auto cache = ps::PlanCache::create();
  const auto before_cache = cache.statistics();
  const auto before_memory = account.statistics().current;
  {
    const auto remaining = account.statistics().limit_bytes - before_memory.requested_bytes;
    const auto framing = resource::MemoryAccount::allocation_bytes(1, alignof(std::max_align_t)) - 1;
    check(remaining > framing, "account-cap fixture has no filler space");
    const auto filler = account.allocate(static_cast<std::size_t>(remaining - framing));
    check(account.statistics().current.requested_bytes == account.statistics().limit_bytes,
          "account-cap fixture did not consume its actual remaining grant");
    const auto attempt = ps::select(snapshot, basis, request, {}, &cache, ps::CacheUse::read_write);
    check(attempt.stop == ps::Stop::allocation_failure && !attempt.selection && cache.statistics() == before_cache,
          "pattern-aware selection bypassed its immutable native byte cap");
  }
  check(account.statistics().current == before_memory, "native-cap refusal leaked selection storage");
  std::cout << "pattern allocation denials=" << denied << " pattern-stage denials=" << pattern_denied
            << "; native account-cap refusal preserved prior analysis/cache/storage\n";
}

}

int main() {
  try {
    decision_contract();
    allocation_contract();
    std::cout << "conditional pattern-aware selection contracts passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n'; return 1;
  }
}
