#include "selection_fixture.hpp"
#include "indexed_runtime_fixture.hpp"

#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/ir/program.hpp"
#include "crown/planner/selection.hpp"

#include <array>
#include <iostream>
#include <string_view>

namespace {
using namespace c05_test;
namespace ps = planner::selection;

struct SqlFamily {
  frontend::NormalizedSql program;
  planner::CandidateSnapshot candidates;
};

SqlFamily normalized_family() {
  const Catalog catalog{7, {{"unused", {{"value", ScalarType::int64}}},
      {"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64}, {"payload", ScalarType::string}}}}};
  constexpr std::string_view sql =
      "SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1";
  auto bound = frontend::bind_sql(sql, catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound), "X09 SQL bind failed");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "X09 SQL normalization failed");
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  auto candidates = c02_test::candidates(
      c02_test::Fixture{program.core_catalog, program.core, {}}, 1, 0);
  check(candidates.candidate_count() != 0, "X09 C02 normalized family is empty");
  return {std::move(program), std::move(candidates)};
}

CompiledProgram prepared(const PhysicalPlan& basis, program::InputPreparationLimits limits) {
  const auto interpreted = CompiledProgram::standalone(basis);
  const auto account = resource::MemoryAccount::create(64U * 1024U * 1024U);
  if (const auto& indexed = basis.options().indexed_storage) {
    storage::IndexWorkAllowance work(indexed->per_operation, true);
    return CompiledProgram::prepare_inputs(account, interpreted, limits, &work);
  }
  return CompiledProgram::prepare_inputs(account, interpreted, limits);
}

ps::Request height_only() {
  ps::Request request;
  request.policy = ps::Policy::height_only;
  return request;
}

ps::Selection select(const planner::CandidateSnapshot& candidates, const ps::Source& source,
                     ps::PlanCache& cache) {
  return complete(ps::select(candidates, source, height_only(), {}, &cache, ps::CacheUse::read_write));
}

void require_mode(const ps::Selection& selected, std::string_view source_sha256,
                  const PhysicalOptions& options, program::InputExecution mode, const char* message) {
  check(selected.plan().input_execution() == mode, message);
  check(selected.plan().physical_source_sha256() == source_sha256 &&
      selected.plan().options().indexed_storage == options.indexed_storage,
      "X09 input specialization changed source/backend identity");
}

void mode_order(const planner::CandidateSnapshot& candidates, std::string_view source_sha256,
                const PhysicalOptions& options,
                const CompiledProgram& interpreted, const CompiledProgram& threaded,
                bool threaded_first) {
  const ps::Source interpreted_source{ps::PhysicalBasis{interpreted}};
  const ps::Source threaded_source{ps::PhysicalBasis{threaded}};
  const auto& first_source = threaded_first ? threaded_source : interpreted_source;
  const auto& second_source = threaded_first ? interpreted_source : threaded_source;
  const auto first_mode = threaded_first ? program::InputExecution::threaded_v1 : program::InputExecution::interpreted_v1;
  const auto second_mode = threaded_first ? program::InputExecution::interpreted_v1 : program::InputExecution::threaded_v1;

  auto cache = ps::PlanCache::create();
  const auto first = select(candidates, first_source, cache);
  check(first.cache_observation().disposition == ps::CacheDisposition::inserted,
      "X09 first input mode was not inserted");
  require_mode(first, source_sha256, options, first_mode, "X09 first input mode changed");

  const auto second = select(candidates, second_source, cache);
  check(second.cache_observation().disposition == ps::CacheDisposition::inserted &&
      first.cache_binding() && second.cache_binding() && first.cache_binding() != second.cache_binding(),
      "X09 cache aliased interpreted and threaded input modes");
  require_mode(second, source_sha256, options, second_mode, "X09 cache returned the other input mode");

  const auto second_hit = select(candidates, second_source, cache);
  const auto first_hit = select(candidates, first_source, cache);
  check(second_hit.cache_observation().disposition == ps::CacheDisposition::hit &&
      first_hit.cache_observation().disposition == ps::CacheDisposition::hit &&
      second_hit.cache_binding() == second.cache_binding() && first_hit.cache_binding() == first.cache_binding(),
      "X09 same-mode cache reuse was not stable");
  require_mode(second_hit, source_sha256, options, second_mode, "X09 same-mode hit returned the wrong mode");
  require_mode(first_hit, source_sha256, options, first_mode, "X09 same-mode hit returned the wrong mode");
  check(cache.statistics().entries == 2 && cache.statistics().insertions == 2 && cache.statistics().hits == 2,
      "X09 mode separation cache counters differ");
}

void preparation_limits(const planner::CandidateSnapshot& candidates, std::string_view source_sha256,
                        const PhysicalOptions& options, const PhysicalPlan& basis) {
  const program::InputPreparationLimits limits_a{10'000'000, 100'000};
  const program::InputPreparationLimits limits_b{20'000'000, 200'000};
  const auto prepared_a = prepared(basis, limits_a);
  const auto prepared_b = prepared(basis, limits_b);
  check(prepared_a.input_execution() == program::InputExecution::threaded_v1 &&
      prepared_b.input_execution() == program::InputExecution::threaded_v1 &&
      prepared_a.physical_sha256() == basis.physical_sha256() &&
      prepared_b.physical_sha256() == basis.physical_sha256(),
      "X09 successful preparation changed mode or physical identity");

  auto cache = ps::PlanCache::create();
  const ps::Source source_a{ps::PhysicalBasis{prepared_a}};
  const ps::Source source_b{ps::PhysicalBasis{prepared_b}};
  const auto a = select(candidates, source_a, cache);
  const auto b = select(candidates, source_b, cache);
  check(a.cache_observation().disposition == ps::CacheDisposition::inserted &&
      b.cache_observation().disposition == ps::CacheDisposition::inserted &&
      a.cache_binding() && b.cache_binding() && a.cache_binding() != b.cache_binding(),
      "X09 cache aliased distinct successful preparation limits");
  require_mode(a, source_sha256, options, program::InputExecution::threaded_v1, "X09 first preparation-limit artifact changed");
  require_mode(b, source_sha256, options, program::InputExecution::threaded_v1, "X09 second preparation-limit artifact changed");
  const auto a_hit = select(candidates, source_a, cache);
  const auto b_hit = select(candidates, source_b, cache);
  check(a_hit.cache_observation().disposition == ps::CacheDisposition::hit &&
      b_hit.cache_observation().disposition == ps::CacheDisposition::hit &&
      a_hit.cache_binding() == a.cache_binding() && b_hit.cache_binding() == b.cache_binding(),
      "X09 preparation-limit cache reuse changed binding");
  check(cache.statistics().entries == 2 && cache.statistics().insertions == 2 && cache.statistics().hits == 2,
      "X09 preparation-limit cache counters differ");
}

void legacy_interpreter_bytes(const planner::CandidateSnapshot& candidates, std::string_view source_sha256,
                              const PhysicalOptions& options, const PhysicalPlan& basis) {
  const auto compiled = CompiledProgram::standalone(basis);
  const ps::Source plan_source{ps::PhysicalBasis{basis}};
  const ps::Source compiled_source{ps::PhysicalBasis{compiled}};
  auto cache = ps::PlanCache::create();
  const auto from_plan = select(candidates, plan_source, cache);
  const auto from_compiled = select(candidates, compiled_source, cache);
  check(from_plan.cache_observation().disposition == ps::CacheDisposition::inserted &&
      from_compiled.cache_observation().disposition == ps::CacheDisposition::hit &&
      from_plan.cache_binding() && from_compiled.cache_binding() == from_plan.cache_binding(),
      "X09 interpreter PhysicalPlan/CompiledProgram legacy cache bytes changed");
  require_mode(from_plan, source_sha256, options, program::InputExecution::interpreted_v1, "X09 legacy plan mode changed");
  require_mode(from_compiled, source_sha256, options, program::InputExecution::interpreted_v1, "X09 legacy compiled mode changed");
  check(from_plan.cache_observation().binding_bytes == from_compiled.cache_observation().binding_bytes,
      "X09 interpreter legacy binding length changed");
}

void payload_budget(const planner::CandidateSnapshot& candidates, std::string_view source_sha256,
                    const PhysicalOptions& options, const CompiledProgram& interpreted,
                    const CompiledProgram& threaded) {
  auto interpreter_cache = ps::PlanCache::create();
  const ps::Source interpreter_source{ps::PhysicalBasis{interpreted}};
  const auto interpreter = select(candidates, interpreter_source, interpreter_cache);
  const auto interpreter_charge = interpreter_cache.statistics().plan_payload_bytes;
  check(interpreter_charge != 0, "X09 interpreter cache payload charge is empty");

  auto threaded_cache = ps::PlanCache::create();
  const ps::Source threaded_source{ps::PhysicalBasis{threaded}};
  const auto prepared_selection = select(candidates, threaded_source, threaded_cache);
  const auto prepared_charge = threaded_cache.statistics().plan_payload_bytes;
  const auto extra_tables = threaded.input_preparation().metadata_bytes;
  check(extra_tables != 0 && prepared_charge >= interpreter_charge + extra_tables,
      "X09 prepared cache payload omitted its additional input tables");
  require_mode(interpreter, source_sha256, options, program::InputExecution::interpreted_v1,
      "X09 interpreter payload probe changed mode");
  require_mode(prepared_selection, source_sha256, options, program::InputExecution::threaded_v1,
      "X09 prepared payload probe changed mode");

  const auto one_under = prepared_charge - 1;
  check(interpreter_charge <= one_under, "X09 prepared payload has no distinct one-under boundary");
  auto limited = ps::PlanCache::create({1, 8U * 1024U * 1024U, one_under});
  const auto refused = ps::select(candidates, threaded_source, height_only(), {}, &limited, ps::CacheUse::read_write);
  check(!refused.selection && refused.stop == ps::Stop::resource_limit &&
      refused.resource == ps::Resource::cache_plan_payload && limited.statistics() == ps::CacheStatistics{},
      "X09 one-under prepared payload was retained or mutated cache state");
  const auto fits = select(candidates, interpreter_source, limited);
  check(fits.cache_observation().disposition == ps::CacheDisposition::inserted &&
      limited.statistics().entries == 1 && limited.statistics().plan_payload_bytes == interpreter_charge,
      "X09 interpreter plan did not fit the same cache payload cap");
}

void backend(const SqlFamily& fixture, const PhysicalOptions& options) {
  const auto basis = planner::lower_normalized(fixture.program,
      fixture.candidates.candidate(0)->tree(), options);
  check(basis.normalized().has_value() && basis.options().indexed_storage == options.indexed_storage,
      "X09 normalized physical backend setup changed");
  const auto interpreted = CompiledProgram::standalone(basis);
  const auto threaded = prepared(basis, {10'000'000, 100'000});
  const auto source_sha256 = interpreted.physical_source_sha256();
  check(interpreted.input_execution() == program::InputExecution::interpreted_v1 &&
      threaded.input_execution() == program::InputExecution::threaded_v1 &&
      interpreted.physical_sha256() == threaded.physical_sha256(),
      "X09 interpreter/threaded source pair differs");
  mode_order(fixture.candidates, source_sha256, options, interpreted, threaded, false);
  mode_order(fixture.candidates, source_sha256, options, interpreted, threaded, true);
  preparation_limits(fixture.candidates, source_sha256, options, basis);
  legacy_interpreter_bytes(fixture.candidates, source_sha256, options, basis);
  payload_budget(fixture.candidates, source_sha256, options, interpreted, threaded);
}
} // namespace

int main() {
  try {
    const auto fixture = normalized_family();
    const std::array<PhysicalOptions, 2> backends{PhysicalOptions{}, s04_runtime::options()};
    for (const auto& options : backends) backend(fixture, options);
    std::cout << "X09 C05 cache mode/limit separation, same-mode hits and interpreter legacy bindings passed on both physical backends\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
