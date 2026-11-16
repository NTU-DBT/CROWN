#include "crown/planner/oracle.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "crown/io/oracle.hpp"
#include "crown/api/error.hpp"
#include "tree_oracle.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>

namespace {
using namespace crown;
void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }
struct Fixture { Catalog catalog; Query query; };
Fixture query_for(const std::vector<std::vector<std::size_t>>& scopes, const std::vector<std::size_t>& head) {
  Fixture fixture;
  std::set<std::size_t> used;
  for (const auto& scope : scopes) used.insert(scope.begin(), scope.end());
  std::map<std::size_t, VariableId> variables;
  for (const auto value : used) {
    variables.emplace(value, VariableId{fixture.query.variables.size()});
    fixture.query.variables.push_back({"v" + std::to_string(value), ScalarType::int64});
  }
  for (std::size_t i = 0; i < scopes.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    for (std::size_t column = 0; column < scopes[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      atom.terms.emplace_back(variables.at(scopes[i][column]));
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (const auto value : head) fixture.query.head.push_back({variables.at(value), "out"});
  return fixture;
}
void literal_foundation() {
  for (const auto& [scopes, head, expected] : std::vector<std::tuple<std::vector<std::vector<std::size_t>>, std::vector<std::size_t>, std::size_t>>{
      {{}, {}, 0}, {{{0}}, {0}, 1}, {{{0, 1}}, {0}, 1}, {{{0, 1}, {1, 2}}, {0, 1, 2}, 1},
      {{{0, 1}, {1}}, {0}, 2}, {{{0}, {1}}, {0, 1}, 1}, {{{}}, {}, 1}}) {
    const auto fixture = query_for(scopes, head);
    const auto result = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
    check(result.status == planner::OracleStatus::proven_minimum && result.minimum_height == expected && result.tree, "literal oracle disagrees with analytic fixture");
    check(planner::validate_tree(fixture.catalog, fixture.query, *result.tree).valid, "literal oracle produced an invalid witness");
  }
  const auto endpoints = query_for({{0, 1}, {1, 2}}, {0, 2});
  check(reference::exhaustive_minimum_tree(endpoints.catalog, endpoints.query).status == planner::OracleStatus::unsupported, "literal oracle must reject the non-free-connex head");
  auto limits = planner::SearchLimits{};
  limits.work_limit = 0;
  check(reference::exhaustive_minimum_tree(endpoints.catalog, endpoints.query, limits).status == planner::OracleStatus::resource_limit, "budget exhaustion must not mean infeasible");
  limits.work_limit = 100'000;
  limits.literal_scope_limit = 0;
  const auto full = query_for({{0, 1}, {1, 2}}, {0, 1, 2});
  check(reference::exhaustive_minimum_tree(full.catalog, full.query, limits).status == planner::OracleStatus::resource_limit, "scope-generation limit must be explicit");
}
planner::HeightCertificate certificate_for(const planner::OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}
void independent_small_family() {
  std::size_t comparisons = 0;
  for (std::size_t count = 0; count <= 2; ++count) {
    std::size_t combinations = 1;
    for (std::size_t i = 0; i < count; ++i) combinations *= 8;
    for (std::size_t code = 0; code < combinations; ++code) {
      auto residue = code;
      std::vector<std::vector<std::size_t>> scopes(count);
      std::size_t variables = 0;
      for (auto& scope : scopes) {
        const auto mask = residue % 8;
        residue /= 8;
        variables |= mask;
        for (std::size_t v = 0; v < 3; ++v) if ((mask & (std::size_t{1} << v)) != 0) scope.push_back(v);
      }
      for (std::size_t head_mask = 0; head_mask < 8; ++head_mask) {
        if ((head_mask & variables) != head_mask) continue;
        std::vector<std::size_t> head;
        for (std::size_t v = 0; v < 3; ++v) if ((head_mask & (std::size_t{1} << v)) != 0) head.push_back(v);
        const auto fixture = query_for(scopes, head);
        const auto literal = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
        const auto exact = planner::minimum_tree(fixture.catalog, fixture.query);
        check(exact.status != planner::OracleStatus::resource_limit && literal.status != planner::OracleStatus::resource_limit, "small independent family exceeded limits");
        check(exact.status == literal.status && exact.minimum_height == literal.minimum_height, "partition oracle disagrees with labelled-topology/full-power-set enumeration");
        check(exact.certificate_verified, "completed exact result did not verify its lower bound");
        check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_for(exact)).valid, "independent certificate replay failed");
        ++comparisons;
      }
    }
  }
  check(comparisons == 371, "finite oracle cross-check scope changed");
  // Three-atom cases exercise multiple generalized nodes and cyclic failure.
  for (const auto& [scopes, head] : std::vector<std::pair<std::vector<std::vector<std::size_t>>, std::vector<std::size_t>>>{
      {{{0, 1}, {1, 2}, {2, 3}}, {0, 1, 2, 3}}, {{{0, 1}, {1, 2}, {0, 2}}, {0, 1, 2}},
      {{{0}, {1}, {2}}, {0, 1, 2}}, {{{0, 1}, {0, 2}, {0, 3}}, {}},
      {{{0, 1, 2}, {0, 1}, {0}}, {0, 2}}, {{{0, 1}, {0, 1}, {0, 1}}, {0}},
      {{{0, 1, 2}, {0, 1}, {0}}, {0, 1, 2}}}) {
    const auto fixture = query_for(scopes, head);
    const auto literal = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
    const auto exact = planner::minimum_tree(fixture.catalog, fixture.query);
    check(literal.status != planner::OracleStatus::resource_limit && literal.status == exact.status && literal.minimum_height == exact.minimum_height, "three-atom independent oracle mismatch");
  }
  const auto nested = query_for({{0, 1, 2}, {0, 1}, {0}}, {0, 1, 2});
  const auto nested_tree = planner::minimum_tree(nested.catalog, nested.query);
  check(nested_tree.minimum_height == 1 && std::count_if(nested_tree.tree->nodes.begin(), nested_tree.tree->nodes.end(), [](const auto& node) { return node.kind == NodeKind::generalized; }) == 2, "height-one nested scopes require both generalized nodes");
  std::cout << "371 exhaustive small queries and seven three-atom shapes agree with literal enumeration\n";
}
void proof_corruption_and_limits() {
  const auto full = query_for({{0, 1}, {1, 2}}, {0, 1, 2});
  const auto exact = planner::minimum_tree(full.catalog, full.query);
  check(exact.minimum_height == 1, "full two-edge minimum");
  const auto good = certificate_for(exact);
  auto bad = good;
  bad.minimum_height = 2;
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "false minimum must fail");
  bad = good;
  for (auto& entry : bad.lower_bounds) if (entry.occurrences.size() == 2 && entry.generalized_allowed && entry.connex_reachable) entry.bound = 2;
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "false exhaustive lower bound must fail independently");
  bad = good; bad.lower_bounds.clear();
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "missing root proof must fail");
  bad = good; bad.lower_bounds.push_back(bad.lower_bounds.front());
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "duplicate state must fail");
  bad = good; bad.algorithm = "unknown";
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "unknown proof algorithm must fail");
  bad = good; bad.tree->nodes.back().scope.clear();
  check(!planner::verify_height_certificate(full.catalog, full.query, bad).valid, "corrupt upper scope must fail");

  const auto projected = query_for({{0, 1}, {1}}, {0});
  bad = certificate_for(planner::minimum_tree(projected.catalog, projected.query));
  bool replaced = false;
  for (auto& entry : bad.lower_bounds) {
    if (entry.occurrences == std::vector<std::size_t>{0} && entry.generalized_allowed && !entry.connex_reachable && !entry.bound) { entry.bound = 1; replaced = true; }
  }
  check(replaced && !planner::verify_height_certificate(projected.catalog, projected.query, bad).valid, "weakening the hidden-head infeasibility proof must expose the false root bound");

  auto limits = planner::SearchLimits{};
  limits.work_limit = 0;
  auto stopped = planner::minimum_tree(full.catalog, full.query, limits);
  check(stopped.status == planner::OracleStatus::resource_limit && !stopped.tree && !stopped.minimum_height && !stopped.certificate_verified, "work exhaustion cannot be a minimum or infeasibility");
  check(planner::verify_height_certificate(full.catalog, full.query, good, limits).resource_limit, "certificate replay has its own resource status");
  limits.work_limit = 100'000; limits.recursion_limit = 0;
  check(planner::minimum_tree(full.catalog, full.query, limits).status == planner::OracleStatus::resource_limit, "recursion exhaustion cannot mean infeasible");
  limits.recursion_limit = 256; limits.time_limit = std::chrono::milliseconds{0};
  check(planner::minimum_tree(full.catalog, full.query, limits).status == planner::OracleStatus::resource_limit, "deadline exhaustion cannot mean infeasible");

  const auto residual = query_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}}, {0, 1, 6});
  const auto residual_result = planner::minimum_tree(residual.catalog, residual.query);
  check(residual_result.status == planner::OracleStatus::proven_minimum &&
        residual_result.minimum_height == 3 && residual_result.certificate_verified &&
        residual_result.statistics.work > 0 && residual_result.statistics.certificate_work > 0,
        "residual counterexample did not produce a replay-verified height-three result");

  planner::ContinuationLimits continuation_limits;
  continuation_limits.producer.work.reset();
  continuation_limits.producer.active_time.reset();
  continuation_limits.replay.work = 0;
  continuation_limits.replay.active_time.reset();
  continuation_limits.logical_depth = 512;
  planner::SearchOptions continuation_options;
  continuation_options.policy = planner::SearchPolicy::strict;
  continuation_options.limits = continuation_limits;
  auto continuation = planner::ExactSearch::create(
      residual.catalog, residual.query, continuation_options);

  planner::SearchAdvance replay_stop;
  bool stopped_in_replay = false;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    replay_stop = continuation.advance(planner::WorkQuantum{4096, {}});
    if (replay_stop.stopped_for == planner::StopReason::total_work) {
      stopped_in_replay = true;
      break;
    }
    check(replay_stop.stopped_for == planner::StopReason::quantum_work ||
          replay_stop.stopped_for == planner::StopReason::quantum_time,
          "unbounded producer stopped before reaching the replay ceiling");
  }
  check(stopped_in_replay && replay_stop.progress.producer_complete &&
        replay_stop.progress.phase == planner::SearchPhase::replay &&
        !replay_stop.progress.proof_complete &&
        replay_stop.progress.result == planner::ResultKind::unfinished &&
        replay_stop.progress.replay.attempted == 0 && !continuation.optimum() &&
        !continuation.infeasibility() && !continuation.incumbent(),
        "replay resource stop published strict proof authority or failed to stop after production");

  continuation_limits.replay.work = 10'000'000;
  check(continuation.raise_limits(continuation_limits) == planner::LimitChange::applied,
        "raising the replay ceiling was rejected");
  planner::SearchAdvance resumed;
  bool resumed_to_completion = false;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    resumed = continuation.advance(planner::WorkQuantum{4096, {}});
    if (resumed.progress.proof_complete) {
      resumed_to_completion = true;
      break;
    }
    check(resumed.progress.result != planner::ResultKind::failed,
          "resumed replay failed before final authority publication");
    check(resumed.stopped_for == planner::StopReason::quantum_work ||
          resumed.stopped_for == planner::StopReason::quantum_time,
          "resumed replay stopped for an unexpected reason");
  }
  const auto optimum = continuation.optimum();
  check(resumed_to_completion && optimum && optimum->valid() && optimum->height() == 3 &&
        resumed.progress.result == planner::ResultKind::verified_optimum &&
        resumed.progress.producer.attempted > 0 && resumed.progress.replay.attempted > 0 &&
        !continuation.incumbent(),
        "resumed strict continuation did not verify height three with producer and replay work");

  std::vector<std::size_t> wide_scope;
  for (std::size_t i = 0; i < 70; ++i) wide_scope.push_back(i);
  const auto wide = query_for({wide_scope, wide_scope}, wide_scope);
  limits = {}; limits.literal_scope_limit = 16;
  check(reference::exhaustive_minimum_tree(wide.catalog, wide.query, limits).status == planner::OracleStatus::resource_limit, "wide literal scope explosion must be an operational limit");
  const auto wide_result = planner::minimum_tree(wide.catalog, wide.query);
  check(wide_result.minimum_height == 1 && wide_result.certificate_verified, "wide composite generalized key has no 64-variable semantic cap");

  auto encoded = io::write_oracle(exact, full.catalog, full.query).at("certificate");
  const auto decoded = io::read_height_certificate(encoded.dump(), full.catalog, full.query);
  check(planner::verify_height_certificate(full.catalog, full.query, decoded).valid, "certificate codec roundtrip");
  encoded["query_binding"]["catalog"]["version"] = 1.0;
  try { static_cast<void>(io::read_height_certificate(encoded.dump(), full.catalog, full.query)); throw std::runtime_error("type-erasing query binding accepted"); }
  catch (const Error& error) { check(error.code() == "invalid_document", "malformed binding must be an input rejection"); }
  encoded["query_binding"]["catalog"]["version"] = 2;
  try { static_cast<void>(io::read_height_certificate(encoded.dump(), full.catalog, full.query)); throw std::runtime_error("different catalog binding accepted"); }
  catch (const Error& error) { check(error.code() == "certificate_binding", "different valid binding must be an invalid certificate"); }
  encoded["query_binding"] = "not a document";
  try { static_cast<void>(io::read_height_certificate(encoded.dump(), full.catalog, full.query)); throw std::runtime_error("wrong-shaped binding accepted"); }
  catch (const Error& error) { check(error.code() == "invalid_document", "wrong-shaped binding must be an input rejection"); }
}
}  // namespace
int main() {
  try { literal_foundation(); independent_small_family(); proof_corruption_and_limits(); std::cout << "complete-family search, independent lower bounds and honest resources passed\n"; return 0; }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
