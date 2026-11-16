#include "crown/api/error.hpp"
#include "crown/io/candidates.hpp"
#include "crown/io/document.hpp"
#include "crown/io/search.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/candidates.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "candidate_set.hpp"
#include "tree_oracle.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace planner = crown::planner;

static_assert(!std::is_default_constructible_v<planner::VerifiedOptimum>);
static_assert(!std::is_default_constructible_v<planner::MinimumHeightCandidate>);
static_assert(!std::is_constructible_v<planner::VerifiedOptimum, planner::HeightCertificate>);
static_assert(!std::is_constructible_v<planner::MinimumHeightCandidate, Catalog, Query,
                                       FreeConnexTree, std::size_t, bool>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

struct Fixture {
  Catalog catalog;
  Query query;
};

Fixture fixture_for(const std::vector<std::vector<std::size_t>>& scopes,
                    const std::vector<std::size_t>& head,
                    ScalarType type = ScalarType::int64) {
  Fixture fixture;
  std::set<std::size_t> names(head.begin(), head.end());
  for (const auto& scope : scopes) names.insert(scope.begin(), scope.end());
  std::map<std::size_t, VariableId> ids;
  for (const auto name : names) {
    const auto id = VariableId{fixture.query.variables.size()};
    ids.emplace(name, id);
    fixture.query.variables.push_back({"v" + std::to_string(name), type});
  }
  for (std::size_t occurrence = 0; occurrence < scopes.size(); ++occurrence) {
    Table table{"T" + std::to_string(occurrence), {}};
    Atom atom{"a" + std::to_string(occurrence), TableId{occurrence}, {}};
    for (std::size_t column = 0; column < scopes[occurrence].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), type});
      atom.terms.emplace_back(ids.at(scopes[occurrence][column]));
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (std::size_t output = 0; output < head.size(); ++output) {
    fixture.query.head.push_back({ids.at(head[output]), "out" + std::to_string(output)});
  }
  validate(fixture.catalog, fixture.query);
  return fixture;
}

Fixture fixture_from(const Document& document) {
  return {document.catalog, document.query};
}

std::string read_text(const std::filesystem::path& path) {
  std::ifstream input(path);
  check(input.good(), "cannot read fixture: " + path.string());
  return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

Document read_document(const std::filesystem::path& path) {
  const auto text = read_text(path);
  return io::read_document(text);
}

FreeConnexTree read_tree(const std::filesystem::path& path, const Fixture& fixture) {
  const auto text = read_text(path);
  return io::read_tree(text, fixture.catalog, fixture.query);
}

planner::VerifiedOptimum prove(const Fixture& fixture) {
  planner::SearchOptions options;
  options.limits.producer.work.reset();
  options.limits.replay.work.reset();
  options.limits.logical_depth.reset();
  auto owner = planner::ExactSearch::create(fixture.catalog, fixture.query, options);
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = owner.advance({50'000'000, {}});
    if (advanced.progress.result == planner::ResultKind::verified_optimum) {
      const auto result = owner.optimum();
      check(result && result->valid(), "P06 exact search omitted its checked optimum");
      return *result;
    }
    check(advanced.progress.result != planner::ResultKind::failed,
          "P06 exact search failed while making a candidate test proof");
    check(advanced.stopped_for == planner::StopReason::quantum_work ||
              advanced.stopped_for == planner::StopReason::quantum_time,
          "P06 exact search stopped before producing a test proof");
  }
  throw std::runtime_error("P06 exact proof exceeded the test guard");
}

planner::VerifiedOptimum replay_with_witness(const Fixture& fixture,
                                              const planner::VerifiedOptimum& source,
                                              FreeConnexTree witness) {
  auto certificate = source.certificate();
  certificate.tree = std::move(witness);
  const auto p02 = planner::validate_tree(fixture.catalog, fixture.query, *certificate.tree);
  check(p02.valid && p02.native_height == source.height(),
        "replacement proof witness is not P02-valid at the original minimum");
  auto replay = planner::CertificateReplay::create(fixture.catalog, fixture.query,
                                                    std::move(certificate));
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = replay.advance({50'000'000, {}});
    if (advanced.progress.complete) {
      const auto checked = replay.checked();
      check(advanced.progress.valid && checked && checked->valid() && checked->optimum(),
            "public P06 CertificateReplay rejected a valid replacement witness");
      return *checked->optimum();
    }
    check(advanced.progress.phase != planner::ReplayPhase::failed,
          "public P06 CertificateReplay failed before completing the witness proof");
  }
  throw std::runtime_error("public P06 CertificateReplay exceeded the test guard");
}

planner::CandidateAdvance advance_until_ready(planner::CandidateProvider& provider,
                                               std::uint64_t grant = 50'000'000) {
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = provider.advance({grant, {}});
    if (advanced.stopped_for == planner::CandidateStop::candidate_ready) return advanced;
    check(advanced.stopped_for == planner::CandidateStop::quantum_work,
          "candidate provider stopped before publishing its next candidate");
  }
  throw std::runtime_error("candidate provider exceeded the ready guard");
}

struct CandidateRun {
  std::vector<std::string> signatures;
  std::vector<std::string> keys;
  planner::CandidateProgress progress;
};

enum class Slicing { one_shot, unit, varied };

bool same_statistics(const planner::CandidateStatistics& left,
                     const planner::CandidateStatistics& right) {
  return left.proposed == right.proposed && left.rejected == right.rejected &&
      left.taller == right.taller && left.duplicates == right.duplicates &&
      left.published == right.published && left.topologies == right.topologies &&
      left.scope_tuples == right.scope_tuples && left.cache_seeded == right.cache_seeded;
}

CandidateRun drain_provider(planner::CandidateProvider& provider, Slicing slicing) {
  CandidateRun run;
  constexpr std::array<std::uint64_t, 4> grants{3, 1, 5, 2};
  for (std::size_t step = 0; step < 10'000'000; ++step) {
    std::uint64_t grant = 50'000'000;
    if (slicing == Slicing::unit) grant = 1;
    else if (slicing == Slicing::varied) grant = grants[step % grants.size()];
    const auto advanced = provider.advance({grant, {}});
    if (advanced.stopped_for == planner::CandidateStop::candidate_ready) continue;
    if (advanced.stopped_for == planner::CandidateStop::quantum_work) continue;
    check(advanced.stopped_for == planner::CandidateStop::exhausted &&
              advanced.progress.family_exhausted,
          "candidate provider did not finish its admitted finite family");
    break;
  }
  const auto progress = provider.progress();
  check(progress.family_exhausted && progress.phase == planner::CandidatePhase::exhausted,
        "candidate provider reached the loop guard without honest exhaustion");
  run.progress = progress;
  run.signatures.reserve(provider.candidate_count());
  run.keys.reserve(provider.candidate_count());
  for (std::size_t index = 0; index < provider.candidate_count(); ++index) {
    const auto handle = provider.candidate(index);
    check(handle && handle->valid(), "published candidate handle is missing");
    const auto report = planner::validate_tree(handle->catalog(), handle->query(), handle->tree());
    check(report.valid && report.native_height == handle->height() &&
              handle->height() == progress.verified_original_height,
          "published candidate failed independent P02 or minimum-height checks");
    check(handle->original_proof().valid() &&
              handle->original_proof().height() == handle->height(),
          "published candidate lost its supplied P06 original proof");
    run.signatures.push_back(reference::normal_form_reference_signature(handle->tree()));
    run.keys.push_back(handle->structural_key());
  }
  return run;
}

void compare_complete_case(const Fixture& fixture, const std::string& label,
                           std::optional<std::size_t> expected_normal_form_count = {}) {
  const auto proof = prove(fixture);
  const auto frozen = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
  check(frozen.status == planner::OracleStatus::proven_minimum && frozen.minimum_height,
        label + ": frozen P03 oracle did not supply the minimum");
  check(proof.height() == *frozen.minimum_height,
        label + ": public P06 proof disagrees with frozen P03 minimum");

  const auto reference_set = reference::collect_normal_form_plan_set(
      fixture.catalog, fixture.query, proof.height());
  check(reference_set.exhausted && !reference_set.resource_limited,
        label + ": independent Prüfer reference did not exhaust");
  if (expected_normal_form_count) {
    check(reference_set.plans.size() == *expected_normal_form_count,
          label + ": independent normal-form plan count changed");
  }
  std::set<std::string> expected;
  for (const auto& plan : reference_set.plans) {
    check(planner::validate_tree(fixture.catalog, fixture.query, plan.representative).valid &&
              reference::normal_form_reference_signature(plan.representative) == plan.signature,
          label + ": reference representative failed P02 or its independent signature");
    expected.insert(plan.signature);
  }

  auto provider = planner::CandidateProvider::create(proof);
  const auto exact_seed = advance_until_ready(provider);
  check(exact_seed.progress.candidate_count == 1,
        label + ": exact P06 witness was not admitted before normal-form enumeration");
  const auto exact = provider.candidate(0);
  check(exact && exact->provenance().source == planner::CandidateSource::exact_witness,
        label + ": first checked seed did not retain exact-witness provenance");
  expected.insert(reference::normal_form_reference_signature(exact->tree()));
  const auto run = drain_provider(provider, Slicing::one_shot);
  if (expected_normal_form_count) {
    const auto exact_signature = reference::normal_form_reference_signature(exact->tree());
    const auto found = std::find_if(reference_set.plans.begin(), reference_set.plans.end(),
        [&](const reference::NormalFormReferencePlan& plan) {
          return plan.signature == exact_signature;
        });
    check(found != reference_set.plans.end() && run.signatures.size() == *expected_normal_form_count,
          label + ": exact witness was not one of the expected complete normal-form plans");
  }

  check(run.signatures.size() == expected.size(),
        label + ": emitted candidate cardinality differs from reference-plus-exact-seed family");
  const std::set<std::string> actual(run.signatures.begin(), run.signatures.end());
  check(actual == expected,
        label + ": complete provider signature set differs from independent Prüfer family plus exact seed");
  const auto original_certificate = io::write_verified_optimum(proof);
  for (std::size_t index = 0; index < provider.candidate_count(); ++index) {
    const auto candidate = provider.candidate(index);
    check(candidate && io::write_verified_optimum(candidate->original_proof()) == original_certificate,
          label + ": candidate changed the exact original catalog/query binding or P06 certificate");
  }

  std::map<std::string, std::string> signature_to_key;
  std::map<std::string, std::string> key_to_signature;
  for (std::size_t index = 0; index < run.signatures.size(); ++index) {
    const auto [forward, inserted_forward] = signature_to_key.emplace(run.signatures[index], run.keys[index]);
    check(inserted_forward || forward->second == run.keys[index],
          label + ": equal independent structures received unequal production keys");
    const auto [backward, inserted_backward] = key_to_signature.emplace(run.keys[index], run.signatures[index]);
    check(inserted_backward || backward->second == run.signatures[index],
          label + ": production key merged distinct independent structures");
  }
  check(signature_to_key.size() == actual.size() && key_to_signature.size() == actual.size(),
        label + ": structural key and independent reference identity are not bijective");
}

void exhaustive_three_atom_family() {
  std::size_t comparisons = 0;
  for (std::size_t first = 0; first < 4; ++first) {
    for (std::size_t second = 0; second < 4; ++second) {
      for (std::size_t third = 0; third < 4; ++third) {
        const auto used = first | second | third;
        for (std::size_t head = 0; head < 4; ++head) {
          if ((head & used) != head) continue;
          std::vector<std::vector<std::size_t>> scopes(3);
          const std::array<std::size_t, 3> masks{first, second, third};
          for (std::size_t occurrence = 0; occurrence < masks.size(); ++occurrence) {
            for (std::size_t variable = 0; variable < 2; ++variable) {
              if ((masks[occurrence] & (std::size_t{1} << variable)) != 0) {
                scopes[occurrence].push_back(variable);
              }
            }
          }
          std::vector<std::size_t> outputs;
          for (std::size_t variable = 0; variable < 2; ++variable) {
            if ((head & (std::size_t{1} << variable)) != 0) outputs.push_back(variable);
          }
          const auto fixture = fixture_for(scopes, outputs);
          const auto label = "three-atom scopes=" + std::to_string(first) + "," +
              std::to_string(second) + "," + std::to_string(third) + " head=" +
              std::to_string(head);
          compare_complete_case(fixture, label);
          ++comparisons;
        }
      }
    }
  }
  check(comparisons == 225, "finite three-atom/two-variable valid-head family changed");
}

void independent_reference_caps_are_incomplete() {
  const auto small = fixture_for({{0}, {0}, {0}}, {0});
  const auto zero = reference::collect_normal_form_plan_set(
      small.catalog, small.query, 1, {0});
  check(zero.resource_limited && !zero.exhausted &&
            zero.stop == reference::NormalFormCollectionStop::work_limit,
        "zero independent-reference work was reported as complete");

  const auto four_atoms = fixture_for({{0}, {0}, {0}, {0}}, {0});
  const auto native_cap = reference::collect_normal_form_plan_set(
      four_atoms.catalog, four_atoms.query, 1);
  check(native_cap.resource_limited && !native_cap.exhausted &&
            native_cap.stop == reference::NormalFormCollectionStop::native_occurrence_cap,
        "independent-reference native cap was reported as semantic support or exhaustion");

  const auto wide_scope = fixture_for({{0, 1, 2, 3}}, {});
  const auto variable_cap = reference::collect_normal_form_plan_set(
      wide_scope.catalog, wide_scope.query, 1);
  check(variable_cap.resource_limited && !variable_cap.exhausted &&
            variable_cap.stop == reference::NormalFormCollectionStop::active_variable_cap,
        "independent-reference active-variable cap was reported as complete");
}

void fixture_cases_and_slicing(const std::filesystem::path& fixture_root) {
  const auto boolean_document = read_document(fixture_root / "queries/boolean_rst.cq.json");
  const auto boolean = fixture_from(boolean_document);
  compare_complete_case(boolean, "Boolean R/S/T", 3);

  const auto self_join_document = read_document(
      fixture_root / "queries/self_join_equal_scope_three.cq.json");
  const auto self_join = fixture_from(self_join_document);
  compare_complete_case(self_join, "equal-scope three-occurrence self-join", 4);

  compare_complete_case(fixture_for({}, {}), "empty body", 1);
  compare_complete_case(fixture_for({{}}, {}), "nullary singleton", 1);
  compare_complete_case(fixture_for({{0}}, {0}), "unary singleton", 1);
  compare_complete_case(fixture_for({{0}, {1}}, {0, 1}), "disconnected projected product");
  compare_complete_case(fixture_for({{0, 1}, {1}}, {0}), "projected nested scopes");

  const auto proof = prove(boolean);
  std::vector<CandidateRun> runs;
  for (const auto slicing : {Slicing::one_shot, Slicing::unit, Slicing::varied}) {
    auto provider = planner::CandidateProvider::create(proof);
    runs.push_back(drain_provider(provider, slicing));
  }
  check(runs[0].keys == runs[1].keys && runs[0].keys == runs[2].keys &&
            runs[0].signatures == runs[1].signatures && runs[0].signatures == runs[2].signatures,
        "one-shot, unit, and varied provider grants changed the ordered family");
  check(same_statistics(runs[0].progress.statistics, runs[1].progress.statistics) &&
            same_statistics(runs[0].progress.statistics, runs[2].progress.statistics) &&
            runs[0].progress.work.committed_transitions == runs[1].progress.work.committed_transitions &&
            runs[0].progress.work.committed_transitions == runs[2].progress.work.committed_transitions,
        "provider slicing changed deterministic completion counters");
}

std::string key_for_witness(const Fixture& fixture,
                            const planner::VerifiedOptimum& original,
                            FreeConnexTree witness) {
  auto proof = replay_with_witness(fixture, original, std::move(witness));
  auto provider = planner::CandidateProvider::create(std::move(proof));
  static_cast<void>(advance_until_ready(provider));
  const auto candidate = provider.candidate(0);
  check(candidate && candidate->valid(), "witness provider omitted its exact checked upper");
  return candidate->structural_key();
}

void structural_key_and_non_normal_witness(const std::filesystem::path& fixture_root) {
  const auto boolean = fixture_from(read_document(fixture_root / "queries/boolean_rst.cq.json"));
  const auto boolean_proof = prove(boolean);
  const auto native = read_tree(fixture_root / "trees/boolean_rst_native_s_root.tree.json", boolean);
  const auto native_permuted = read_tree(
      fixture_root / "trees/boolean_rst_native_s_root_permuted.tree.json", boolean);
  const auto generalized_x = read_tree(
      fixture_root / "trees/boolean_rst_generalized_x_root.tree.json", boolean);
  const auto generalized_y = read_tree(
      fixture_root / "trees/boolean_rst_generalized_y_root.tree.json", boolean);
  const auto empty_scope = read_tree(
      fixture_root / "trees/boolean_rst_scope_probe_empty.tree.json", boolean);
  const auto x_scope = read_tree(
      fixture_root / "trees/boolean_rst_scope_probe_x.tree.json", boolean);
  check(key_for_witness(boolean, boolean_proof, native) ==
            key_for_witness(boolean, boolean_proof, native_permuted),
        "node IDs, node-vector order, child order, or scope order changed a checked tree key");
  const auto native_key = key_for_witness(boolean, boolean_proof, native);
  check(native_key != key_for_witness(boolean, boolean_proof, generalized_x) &&
            native_key != key_for_witness(boolean, boolean_proof, generalized_y) &&
            key_for_witness(boolean, boolean_proof, generalized_x) !=
                key_for_witness(boolean, boolean_proof, generalized_y),
        "root/kind/grouping distinctions collapsed in structural identity");
  check(key_for_witness(boolean, boolean_proof, empty_scope) !=
            key_for_witness(boolean, boolean_proof, x_scope),
        "checked generalized scope change did not change structural identity");

  const auto self_join = fixture_from(read_document(
      fixture_root / "queries/self_join_equal_scope_three.cq.json"));
  const auto self_proof = prove(self_join);
  const auto left_direct = read_tree(
      fixture_root / "trees/self_join_left_direct.tree.json", self_join);
  const auto left_permuted = read_tree(
      fixture_root / "trees/self_join_left_direct_permuted.tree.json", self_join);
  const auto right_direct = read_tree(
      fixture_root / "trees/self_join_right_direct.tree.json", self_join);
  check(key_for_witness(self_join, self_proof, left_direct) ==
            key_for_witness(self_join, self_proof, left_permuted),
        "self-join node permutation changed original occurrence identity");
  check(key_for_witness(self_join, self_proof, left_direct) !=
            key_for_witness(self_join, self_proof, right_direct),
        "equal-scope native occurrence identity was lost in structural key");

  const auto singleton = fixture_for({{0}}, {0});
  const auto normal_proof = prove(singleton);
  auto unary_witness = normal_proof.certificate().tree.value();
  check(unary_witness.root.has_value(), "singleton exact proof omitted a tree root");
  const auto old_root = *unary_witness.root;
  unary_witness.nodes.push_back(TreeNode{"unary-generalized", NodeKind::generalized,
      VariableSet{VariableId{0}}, {old_root}, {}, {}});
  unary_witness.root = NodeId{unary_witness.nodes.size() - 1};
  unary_witness.claimed_connex.reset();
  unary_witness.claimed_native_height.reset();
  const auto unary_report = planner::validate_tree(singleton.catalog, singleton.query, unary_witness);
  check(unary_report.valid && unary_report.native_height == 1,
        "P02 rejected the admissible unary generalized original witness");
  const auto unary_proof = replay_with_witness(singleton, normal_proof, unary_witness);
  const auto unary_certificate = io::write_verified_optimum(unary_proof);
  auto provider = planner::CandidateProvider::create(unary_proof);
  while (true) {
    const auto advanced = provider.advance({50'000'000, {}});
    if (advanced.stopped_for == planner::CandidateStop::exhausted) break;
    check(advanced.stopped_for == planner::CandidateStop::candidate_ready ||
              advanced.stopped_for == planner::CandidateStop::quantum_work,
          "provider rejected a P06-replayed non-normal-form witness");
  }
  check(provider.candidate_count() == 2 && provider.progress().family_exhausted,
        "normal-form candidate plus separately admitted unary witness were not both retained");
  const auto retained_unary = provider.candidate(0);
  check(retained_unary && retained_unary->tree().nodes.size() == 2 &&
            retained_unary->provenance().source == planner::CandidateSource::exact_witness,
        "provider replaced or normalized the original unary P06 witness");
  for (std::size_t index = 0; index < provider.candidate_count(); ++index) {
    const auto candidate = provider.candidate(index);
    check(candidate && io::write_verified_optimum(candidate->original_proof()) == unary_certificate,
          "alternative candidate changed its original P06 certificate");
  }

  auto native_search_proof = prove(singleton);
  const auto native_certificate = io::write_verified_optimum(native_search_proof);
  auto cache = planner::CandidateCache::create(1);
  check(cache.install(provider.snapshot()) == planner::CandidateCacheInstall::inserted,
        "unary witness snapshot failed cache installation");
  const auto prefix = cache.lookup(native_search_proof);
  check(prefix && prefix->candidate_count() == 2,
        "exact-binding cache failed to reuse the checked unary witness family");
  auto reused = planner::CandidateProvider::create(native_search_proof, {}, {}, {}, *prefix);
  while (true) {
    const auto advanced = reused.advance({50'000'000, {}});
    if (advanced.stopped_for == planner::CandidateStop::exhausted) break;
    check(advanced.stopped_for == planner::CandidateStop::candidate_ready ||
              advanced.stopped_for == planner::CandidateStop::quantum_work,
          "provider failed while replaying an exact-binding cached prefix");
  }
  check(reused.candidate_count() == 2 && reused.progress().family_exhausted,
        "cached unary prefix did not retain both distinct checked uppers");
  for (std::size_t index = 0; index < reused.candidate_count(); ++index) {
    const auto candidate = reused.candidate(index);
    check(candidate && io::write_verified_optimum(candidate->original_proof()) == native_certificate,
          "cache reuse transplanted a former provider's original proof witness");
  }
  provider.cancel();
  cache.clear();
  check(retained_unary->valid() && retained_unary->tree().nodes.size() == 2 &&
            io::write_verified_optimum(retained_unary->original_proof()) == unary_certificate,
        "retained candidate lost its original tree/proof after cancellation and cache clear");
}

planner::CandidateStop finish_until(planner::CandidateProvider& provider,
                                    planner::CandidateStop desired) {
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = provider.advance({50'000'000, {}});
    if (advanced.stopped_for == desired) return desired;
    if (advanced.stopped_for == planner::CandidateStop::candidate_ready ||
        advanced.stopped_for == planner::CandidateStop::quantum_work) continue;
    return advanced.stopped_for;
  }
  throw std::runtime_error("provider exceeded a resource-stop guard");
}

void resource_limits_and_lifetimes() {
  const auto fixture = fixture_for({{0, 1}, {1}}, {0});
  const auto proof = prove(fixture);

  auto no_work_limits = planner::CandidateLimits{};
  no_work_limits.enumeration.work = 0;
  auto no_work = planner::CandidateProvider::create(proof, {}, no_work_limits);
  check(no_work.advance({100, {}}).stopped_for == planner::CandidateStop::total_work &&
            no_work.candidate_count() == 0 && !no_work.progress().family_exhausted,
        "zero total-work cap published or exhausted a candidate family");
  no_work_limits = no_work.limits();
  no_work_limits.enumeration.work = 50'000'000;
  check(no_work.raise_limits(no_work_limits) == planner::LimitChange::applied,
        "same provider could not resume after raising total-work ceiling");
  check(finish_until(no_work, planner::CandidateStop::exhausted) ==
            planner::CandidateStop::exhausted && no_work.candidate_count() > 0,
        "work-limited provider did not resume to honest exhaustion");

  auto capacity_limits = planner::CandidateLimits{};
  capacity_limits.retained_candidates = 0;
  auto capacity = planner::CandidateProvider::create(proof, {}, capacity_limits);
  check(finish_until(capacity, planner::CandidateStop::candidate_capacity) ==
            planner::CandidateStop::candidate_capacity &&
            capacity.candidate_count() == 0 && !capacity.progress().family_exhausted,
        "zero candidate capacity was reported as exhaustion or published a candidate");
  capacity_limits = capacity.limits();
  capacity_limits.retained_candidates = 64;
  check(capacity.raise_limits(capacity_limits) == planner::LimitChange::applied,
        "candidate capacity could not be raised monotonically");
  check(finish_until(capacity, planner::CandidateStop::exhausted) ==
            planner::CandidateStop::exhausted && capacity.candidate_count() > 0,
        "capacity-limited pending publication was lost after a raise");

  auto depth_limits = planner::CandidateLimits{};
  depth_limits.logical_depth = 0;
  auto depth = planner::CandidateProvider::create(proof, {}, depth_limits);
  check(finish_until(depth, planner::CandidateStop::depth_limit) ==
            planner::CandidateStop::depth_limit && !depth.progress().family_exhausted,
        "zero logical depth was confused with completion");
  depth_limits = depth.limits();
  depth_limits.logical_depth = 256;
  check(depth.raise_limits(depth_limits) == planner::LimitChange::applied &&
            finish_until(depth, planner::CandidateStop::exhausted) ==
                planner::CandidateStop::exhausted,
        "depth-limited provider did not resume on the same owner");

  for (int resource = 0; resource < 2; ++resource) {
    auto limits = planner::CandidateLimits{};
    if (resource == 0) limits.records = 0;
    else limits.cells = 0;
    auto provider = planner::CandidateProvider::create(proof, {}, limits);
    const auto stop = finish_until(provider, resource == 0
        ? planner::CandidateStop::record_limit : planner::CandidateStop::cell_limit);
    check(stop == (resource == 0 ? planner::CandidateStop::record_limit
                                : planner::CandidateStop::cell_limit) &&
              !provider.progress().family_exhausted,
          "logical record/cell capacity was misreported as exhaustion");
    limits = provider.limits();
    limits.records = std::nullopt;
    limits.cells = std::nullopt;
    check(provider.raise_limits(limits) == planner::LimitChange::applied &&
              finish_until(provider, planner::CandidateStop::exhausted) ==
                  planner::CandidateStop::exhausted,
          "logical record/cell stop did not resume after monotone extension");
  }

  auto time_limits = planner::CandidateLimits{};
  time_limits.enumeration.active_time = std::chrono::nanoseconds{0};
  auto time_limited = planner::CandidateProvider::create(proof, {}, time_limits);
  check(time_limited.advance({10, {}}).stopped_for == planner::CandidateStop::total_time &&
            !time_limited.progress().family_exhausted,
        "zero total active-time ceiling was confused with exhaustion");
  time_limits = time_limited.limits();
  time_limits.enumeration.active_time = std::chrono::seconds{10};
  check(time_limited.raise_limits(time_limits) == planner::LimitChange::applied &&
            finish_until(time_limited, planner::CandidateStop::exhausted) ==
                planner::CandidateStop::exhausted,
        "time-limited provider did not resume after raising the ceiling");

  auto inert = planner::CandidateProvider::create(proof);
  const auto before = inert.progress();
  check(inert.advance({0, {}}).stopped_for == planner::CandidateStop::quantum_work &&
            inert.advance({1, std::chrono::nanoseconds{0}}).stopped_for ==
                planner::CandidateStop::quantum_time &&
            inert.advance({1, std::chrono::nanoseconds{-1}}).stopped_for ==
                planner::CandidateStop::invalid_quantum,
        "zero/negative candidate grants were not rejected or inert");
  const auto after = inert.progress();
  check(before.phase == after.phase && before.last_stop == after.last_stop &&
            before.work == after.work && before.records == after.records &&
            before.cells == after.cells && before.candidate_count == after.candidate_count,
        "inert candidate grants changed diagnostic progress");
  static_cast<void>(advance_until_ready(inert));
  auto retained = inert.candidate(0);
  check(retained.has_value(), "lifetime probe did not publish its first candidate");
  auto snapshot = inert.snapshot();
  auto moved = std::move(inert);
  check(inert.progress().phase == planner::CandidatePhase::moved_from &&
            inert.advance({1, {}}).stopped_for == planner::CandidateStop::moved_from,
        "moved-from candidate provider remained active");
  moved.cancel();
  check(moved.progress().phase == planner::CandidatePhase::cancelled &&
            retained->valid() && planner::validate_tree(retained->catalog(), retained->query(),
                                                        retained->tree()).valid &&
            snapshot.valid() && snapshot.candidate_count() >= 1,
        "candidate/snapshot lifetime did not outlive move and cancellation");
  auto moved_candidate = std::move(*retained);
  check(moved_candidate.valid() && !retained->valid(),
        "owning candidate handle move did not preserve its checked artifact");
}

void exact_binding_cache_fences(const std::filesystem::path& fixture_root) {
  const auto base = fixture_from(read_document(fixture_root / "queries/boolean_rst.cq.json"));
  const auto proof = prove(base);
  auto seed_provider = planner::CandidateProvider::create(proof);
  static_cast<void>(advance_until_ready(seed_provider));
  auto cache = planner::CandidateCache::create(32);
  const auto prefix = seed_provider.snapshot();
  check(cache.install(prefix) == planner::CandidateCacheInstall::inserted,
        "base exact-binding snapshot was not installed");
  check(cache.lookup(proof).has_value(), "identical full binding missed its candidate cache entry");

  std::vector<std::pair<std::string, Fixture>> mutations;
  auto changed = base;
  ++changed.catalog.version;
  mutations.emplace_back("catalog version", std::move(changed));
  changed = base;
  changed.catalog.tables[0].name += "_renamed";
  mutations.emplace_back("table name", std::move(changed));
  changed = base;
  changed.catalog.tables[0].columns[0].name += "_renamed";
  mutations.emplace_back("column name", std::move(changed));
  changed = base;
  changed.catalog.tables[0].source_schema_version += 1;
  mutations.emplace_back("source schema version", std::move(changed));
  changed = base;
  changed.catalog.tables[0].statistics.row_count = 81;
  mutations.emplace_back("catalog statistics metadata", std::move(changed));
  changed = base;
  changed.catalog.tables[0].constraints.emplace_back(
      UniqueConstraint{"u0", {ColumnId{0}}, ConstraintStatus::enforced});
  mutations.emplace_back("catalog constraint metadata", std::move(changed));
  changed = base;
  changed.query.variables[0].name += "_renamed";
  mutations.emplace_back("variable name", std::move(changed));
  changed = base;
  changed.query.atoms[0].occurrence += "_renamed";
  mutations.emplace_back("occurrence name", std::move(changed));
  changed = base;
  changed.query.atoms[0].terms[0] = Value{std::string{"constant"}};
  mutations.emplace_back("typed constant term", std::move(changed));
  changed = base;
  changed.query.atoms[0].terms[0] = IgnoredColumn{};
  mutations.emplace_back("ignored term", std::move(changed));
  changed = base;
  changed.query.variables[0].type = ScalarType::int64;
  changed.catalog.tables[0].columns[0].type = ScalarType::int64;
  changed.catalog.tables[1].columns[0].type = ScalarType::int64;
  mutations.emplace_back("variable and catalog scalar types", std::move(changed));
  changed = base;
  changed.query.head = {{VariableId{0}, "x"}, {VariableId{1}, "y"}};
  mutations.emplace_back("ordered head", std::move(changed));
  changed = base;
  changed.query.head = {{VariableId{1}, "y"}, {VariableId{0}, "x"}};
  mutations.emplace_back("reordered head", std::move(changed));
  changed = base;
  changed.query.head = {{VariableId{0}, "first"}, {VariableId{0}, "again"}};
  mutations.emplace_back("repeated head output", std::move(changed));
  changed = base;
  changed.query.head = {{VariableId{0}, "renamed_alias"}};
  mutations.emplace_back("head alias", std::move(changed));
  changed = base;
  changed.query.contradiction = true;
  mutations.emplace_back("contradiction state", std::move(changed));

  for (const auto& [label, mutation] : mutations) {
    const auto changed_proof = prove(mutation);
    check(!cache.lookup(changed_proof),
          label + ": full exact-binding cache reused an altered catalog/query proof");
  }

  auto bad_update = planner::CandidateContext{};
  bad_update.updates = static_cast<planner::CandidateUpdateProfile>(99);
  auto bad_arithmetic = planner::CandidateContext{};
  bad_arithmetic.arithmetic = "other-arithmetic";
  auto bad_planner = planner::CandidateContext{};
  bad_planner.planner = "other-planner";
  auto bad_optimization = planner::CandidateContext{};
  bad_optimization.optimization = "other-optimization";
  auto bad_cost = planner::CandidateContext{};
  bad_cost.cost_model = "other-cost";
  auto bad_key = planner::CandidateContext{};
  bad_key.canonicalization = "other-key";
  for (const auto& context : {bad_update, bad_arithmetic, bad_planner, bad_optimization,
                              bad_cost, bad_key}) {
    bool provider_rejected = false;
    try {
      static_cast<void>(planner::CandidateProvider::create(proof, context));
    } catch (const Error& error) {
      provider_rejected = error.code() == "invalid_candidate_context";
    }
    check(provider_rejected, "provider accepted an unsupported candidate context profile");
    bool cache_rejected = false;
    try {
      static_cast<void>(cache.lookup(proof, context));
    } catch (const Error& error) {
      cache_rejected = error.code() == "invalid_candidate_context";
    }
    check(cache_rejected, "cache normalized an unsupported context instead of rejecting it");
  }
}

Fixture distinct_residual_source_fixture() {
  Fixture fixture;
  fixture.catalog.tables.push_back(Table{"N", {}});
  fixture.catalog.tables.push_back(Table{"R", {{"x", ScalarType::int64},
                                                  {"y", ScalarType::int64}}});
  fixture.catalog.tables.push_back(Table{"S", {{"x", ScalarType::int64}}});
  fixture.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}};
  fixture.query.atoms = {
      Atom{"n", TableId{0}, {}},
      Atom{"r", TableId{1}, {VariableId{0}, VariableId{1}}},
      Atom{"s", TableId{2}, {VariableId{0}}}};
  fixture.query.head = {{VariableId{1}, "y"}};
  validate(fixture.catalog, fixture.query);
  return fixture;
}

void residual_source_and_cached_provenance() {
  const auto fixture = distinct_residual_source_fixture();
  const auto first_proof = prove(fixture);
  check(first_proof.height() == 2,
        "nullary/connected/projected residual fixture lost its P06 minimum two");

  planner::ResidualOptions options;
  options.mode = planner::ResidualMode::candidates_with_exact_repair;
  options.limits.residual.work.reset();
  options.limits.exact.producer.work.reset();
  options.limits.exact.replay.work.reset();
  options.limits.exact.logical_depth.reset();
  auto residual = planner::ResidualSearch::create(fixture.catalog, fixture.query, options);
  for (std::size_t step = 0; step < 10'000'000 && !residual.candidate(); ++step) {
    const auto advanced = residual.advance({50'000'000, {}});
    check(advanced.progress.result != planner::ResidualResult::failed,
          "P05 did not produce the distinct checked residual source");
    check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
              advanced.stopped_for == planner::ResidualStopReason::quantum_time ||
              residual.candidate().has_value(),
          "P05 residual source stopped before a checked candidate was available");
  }
  const auto seed = residual.candidate();
  check(seed && seed->valid() && seed->height() == 2 &&
            planner::validate_tree(fixture.catalog, fixture.query, seed->tree()).valid,
        "P05 residual source did not pass independent P02 at the original minimum");
  const auto& residual_tree = seed->tree();
  check(residual_tree.root && residual_tree.nodes[residual_tree.root->value].kind == NodeKind::native &&
            residual_tree.nodes[residual_tree.root->value].occurrence == 1 &&
            std::none_of(residual_tree.nodes.begin(), residual_tree.nodes.end(),
                         [](const TreeNode& node) { return node.kind == NodeKind::generalized; }),
        "residual source fixture no longer distinguishes the native R-root plan");

  auto original = planner::CandidateProvider::create(first_proof, {}, {}, *seed);
  while (true) {
    const auto advanced = original.advance({50'000'000, {}});
    if (advanced.stopped_for == planner::CandidateStop::exhausted) break;
    check(advanced.stopped_for == planner::CandidateStop::candidate_ready ||
              advanced.stopped_for == planner::CandidateStop::quantum_work,
          "candidate provider failed on an independently checked residual seed");
  }
  check(original.candidate_count() == 2 && original.progress().family_exhausted,
        "exact and distinct residual sources did not produce the expected complete two-plan prefix");
  const auto exact_handle = original.candidate(0);
  const auto residual_handle = original.candidate(1);
  check(exact_handle && residual_handle &&
            exact_handle->provenance().source == planner::CandidateSource::exact_witness &&
            residual_handle->provenance().source == planner::CandidateSource::residual_seed &&
            residual_handle->provenance().residual_last_step == seed->origin() &&
            residual_handle->provenance().residual_trace &&
            residual_handle->provenance().residual_trace->valid() &&
            reference::normal_form_reference_signature(exact_handle->tree()) !=
                reference::normal_form_reference_signature(residual_handle->tree()),
        "published residual candidate lost distinct structure or its checked provenance");

  // Replay the same P06 lower-bound certificate with a separately P02-valid,
  // unary-generalized upper witness. It remains a non-normal-form exact seed.
  auto alternate_witness = first_proof.certificate().tree.value();
  check(alternate_witness.root.has_value(), "P06 fixture proof omitted its upper tree");
  const auto old_root = *alternate_witness.root;
  alternate_witness.nodes.push_back(TreeNode{"outer_unary", NodeKind::generalized,
      {}, {old_root}, {}, {}});
  alternate_witness.root = NodeId{alternate_witness.nodes.size() - 1};
  alternate_witness.claimed_connex.reset();
  alternate_witness.claimed_native_height.reset();
  const auto second_proof = replay_with_witness(fixture, first_proof,
                                                 std::move(alternate_witness));
  check(io::write_verified_optimum(second_proof) != io::write_verified_optimum(first_proof),
        "independent P06 replay did not retain the replacement original witness");

  auto cache = planner::CandidateCache::create(4);
  check(cache.install(original.snapshot()) == planner::CandidateCacheInstall::inserted,
        "complete exact/residual candidate prefix was not cached");
  const auto cached_prefix = cache.lookup(second_proof);
  check(cached_prefix && cached_prefix->candidate_count() == 2 &&
            cached_prefix->family_exhausted(),
        "full exact-binding cache lookup lost its residual provenance prefix");
  auto reused = planner::CandidateProvider::create(second_proof, {}, {}, {}, *cached_prefix);
  while (true) {
    const auto advanced = reused.advance({50'000'000, {}});
    if (advanced.stopped_for == planner::CandidateStop::exhausted) break;
    check(advanced.stopped_for == planner::CandidateStop::candidate_ready ||
              advanced.stopped_for == planner::CandidateStop::quantum_work,
          "provider failed while replaying the cached residual prefix");
  }
  check(reused.candidate_count() == 3 && reused.progress().family_exhausted,
        "cached alternatives did not preserve the new exact witness plus original two-plan prefix");
  bool found_cached_residual = false;
  for (std::size_t index = 0; index < reused.candidate_count(); ++index) {
    const auto candidate = reused.candidate(index);
    check(candidate && io::write_verified_optimum(candidate->original_proof()) ==
                           io::write_verified_optimum(second_proof),
          "cached candidate retained the previous provider's original proof");
    const auto provenance = candidate->provenance();
    if (provenance.source == planner::CandidateSource::residual_seed) {
      found_cached_residual = true;
      check(provenance.residual_last_step == seed->origin() && provenance.residual_trace &&
                provenance.residual_trace->valid() &&
                reference::normal_form_reference_signature(candidate->tree()) ==
                    reference::normal_form_reference_signature(residual_handle->tree()),
            "cache reuse changed residual source, trace, or checked upper tree");
    }
  }
  check(found_cached_residual,
        "cache reuse erased the residual-source primary provenance");
}

Fixture residual_fixture(std::size_t atom_count) {
  if (atom_count == 7) {
    return fixture_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}},
                       {0, 1, 6});
  }
  if (atom_count == 9) {
    return fixture_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5, 6},
                        {1, 5, 7}, {6}, {7}, {0, 8}}, {0, 1, 8});
  }
  throw std::invalid_argument("mandatory residual fixture expects seven or nine atoms");
}

void mandatory_residual_and_wide_seed_boundaries() {
  for (const auto atom_count : {std::size_t{7}, std::size_t{9}}) {
    const auto fixture = residual_fixture(atom_count);
    planner::ResidualOptions options;
    options.mode = planner::ResidualMode::require_exact_original;
    options.limits.residual.work.reset();
    options.limits.exact.producer.work.reset();
    options.limits.exact.replay.work.reset();
    options.limits.exact.logical_depth.reset();
    auto residual = planner::ResidualSearch::create(fixture.catalog, fixture.query, options);
    for (std::size_t step = 0; step < 10'000'000; ++step) {
      const auto advanced = residual.advance({50'000'000, {}});
      if (advanced.progress.result == planner::ResidualResult::verified_optimum) break;
      check(advanced.progress.result != planner::ResidualResult::failed,
            "mandatory residual P05 fixture failed before its original proof");
      check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
                advanced.stopped_for == planner::ResidualStopReason::quantum_time,
            "mandatory residual P05 fixture stopped without a verified result");
    }
    const auto proof = residual.exact_original();
    const auto seed = residual.candidate();
    check(proof && seed && proof->height() == 3 && seed->valid() && seed->height() == 3,
          "mandatory seven/nine-atom P05 fixture lost its original minimum-three proof or checked seed");
    check(planner::validate_tree(fixture.catalog, fixture.query, seed->tree()).valid,
          "mandatory P05 residual seed failed P02 on the original binding");

    auto provider = planner::CandidateProvider::create(*proof, {}, {}, *seed);
    const auto first = advance_until_ready(provider);
    check(first.stopped_for == planner::CandidateStop::candidate_ready &&
              provider.candidate_count() == 1,
          "mandatory P07 provider failed to publish its original exact seed first");
    const auto retained = provider.candidate(0);
    check(retained && retained->height() == 3 &&
              planner::validate_tree(fixture.catalog, fixture.query, retained->tree()).valid,
          "mandatory P07 exact seed is not valid at original minimum three");
    for (int grant_index = 0; grant_index < 2; ++grant_index) {
      const auto before = provider.progress().work.attempted;
      const auto advanced = provider.advance({1000, {}});
      check((advanced.stopped_for == planner::CandidateStop::quantum_work ||
                advanced.stopped_for == planner::CandidateStop::candidate_ready) &&
                advanced.progress.work.attempted - before <= 1000 &&
                !advanced.progress.family_exhausted &&
                advanced.progress.verified_original_height == 3,
            "mandatory height-three search claimed false exhaustion or exceeded its bounded grant");
    }
    provider.cancel();
    check(retained->valid() && retained->height() == 3 &&
              retained->original_proof().height() == 3 &&
              planner::validate_tree(retained->catalog(), retained->query(), retained->tree()).valid,
          "height-three candidate/proof handle did not survive cancellation");
  }

  std::vector<std::size_t> wide_scope;
  wide_scope.reserve(70);
  for (std::size_t variable = 0; variable < 70; ++variable) wide_scope.push_back(variable);
  const auto wide = fixture_for(std::vector<std::vector<std::size_t>>(70, wide_scope), {});
  const auto proof = prove(wide);
  check(proof.height() == 1, "70-occurrence/70-variable exact proof changed its minimum");
  auto provider = planner::CandidateProvider::create(proof);
  const auto exact = advance_until_ready(provider);
  check(exact.progress.candidate_count == 1 && provider.candidate(0)->height() == 1,
        "wide query could not publish its supplied checked minimum seed");
  for (int grant_index = 0; grant_index < 2; ++grant_index) {
    const auto before = provider.progress().work.attempted;
    const auto advanced = provider.advance({1000, {}});
    check((advanced.stopped_for == planner::CandidateStop::quantum_work ||
              advanced.stopped_for == planner::CandidateStop::candidate_ready) &&
              advanced.progress.work.attempted - before <= 1000 &&
              !advanced.progress.family_exhausted &&
              advanced.progress.verified_original_height == 1,
          "70x70 bounded provider grant hit a fixed-width cutoff or claimed exhaustion");
  }
}

std::string raw_bytes(std::initializer_list<unsigned int> bytes) {
  std::string value;
  value.reserve(bytes.size());
  for (const auto byte : bytes) value.push_back(static_cast<char>(byte));
  return value;
}

Fixture string_constant_fixture(const std::string& constant) {
  Fixture fixture;
  fixture.catalog.tables.push_back(Table{"literal_table", {{"value", ScalarType::string}}});
  fixture.query.atoms.push_back(Atom{"literal_occurrence", TableId{0},
      {Value{constant}}});
  validate(fixture.catalog, fixture.query);
  return fixture;
}

Fixture arbitrary_string_binding_fixture() {
  Fixture fixture;
  Table table{"table-" + raw_bytes({0x80}),
              {{std::string{"column\0a", 8}, ScalarType::string}}};
  table.key_hints.push_back({{ColumnId{0}}, "reason-" + raw_bytes({0x80})});
  fixture.catalog.tables.push_back(std::move(table));
  fixture.query.variables.push_back({"variable-" + raw_bytes({0x81}), ScalarType::string});
  fixture.query.atoms.push_back(Atom{"occurrence-" + raw_bytes({0x80}), TableId{0},
      {VariableId{0}}});
  fixture.query.head.push_back({VariableId{0}, std::string{"alias\0a", 7}});
  validate(fixture.catalog, fixture.query);
  return fixture;
}

void expect_candidate_error(const std::function<void()>& action, const std::string& code,
                            const std::string& context) {
  try {
    action();
  } catch (const Error& error) {
    check(error.code() == code, context + ": wrong typed rejection " + error.code());
    return;
  }
  throw std::runtime_error(context + ": expected typed candidate rejection " + code);
}

void require_candidate_dump_rejected(const io::Json& document, const std::string& context) {
  bool rejected = false;
  try {
    static_cast<void>(document.dump());
  } catch (const std::exception&) {
    rejected = true;
  }
  check(rejected, context + ": invalid UTF-8 was silently escaped or replaced by JSON text output");
}

void arbitrary_string_binding_domain() {
  const auto byte_80 = raw_bytes({0x80});
  const auto byte_81 = raw_bytes({0x81});
  check(byte_80.size() == 1 && byte_81.size() == 1 &&
            static_cast<unsigned char>(byte_80[0]) == 0x80U &&
            static_cast<unsigned char>(byte_81[0]) == 0x81U,
        "binary fixture did not preserve the requested invalid UTF-8 bytes");
  const std::string nul_ab{"a\0b", 3};
  const std::string nul_ac{"a\0c", 3};
  const std::string nul_ab_long{"a\0b\0", 4};

  const auto fixture_80 = string_constant_fixture(byte_80);
  const auto fixture_81 = string_constant_fixture(byte_81);
  const auto fixture_nul_ab = string_constant_fixture(nul_ab);
  const auto fixture_nul_ac = string_constant_fixture(nul_ac);
  const auto fixture_nul_ab_long = string_constant_fixture(nul_ab_long);
  const auto proof_80 = prove(fixture_80);
  const auto proof_81 = prove(fixture_81);
  const auto proof_nul_ab = prove(fixture_nul_ab);
  const auto proof_nul_ac = prove(fixture_nul_ac);
  const auto proof_nul_ab_long = prove(fixture_nul_ab_long);
  for (const auto* proof : {&proof_80, &proof_81, &proof_nul_ab, &proof_nul_ac,
                            &proof_nul_ab_long}) {
    check(proof->height() == 1 && planner::validate_tree(
              proof->binding().catalog(), proof->binding().query(), proof->upper().tree()).valid,
          "P06 or P02 rejected a singleton string-constant proof in the byte domain");
  }
  const auto constant_from_proof = [](const planner::VerifiedOptimum& proof) -> const std::string& {
    const auto& term = proof.binding().query().atoms[0].terms[0];
    const auto* value = std::get_if<Value>(&term);
    check(value != nullptr, "constant proof binding lost its typed Value term");
    const auto* string = std::get_if<std::string>(value);
    check(string != nullptr, "constant proof binding changed its string scalar type");
    return *string;
  };
  check(constant_from_proof(proof_80) == byte_80 && constant_from_proof(proof_81) == byte_81 &&
            constant_from_proof(proof_nul_ab) == nul_ab &&
            constant_from_proof(proof_nul_ac) == nul_ac &&
            constant_from_proof(proof_nul_ab_long) == nul_ab_long,
        "P06 proof binding truncated or normalized arbitrary bytes/embedded NULs");

  const auto collect_constant = [](const planner::VerifiedOptimum& proof) {
    auto provider = planner::CandidateProvider::create(proof);
    const auto run = drain_provider(provider, Slicing::one_shot);
    check(run.signatures.size() == 1 && run.keys.size() == 1 &&
              provider.progress().family_exhausted,
          "singleton string-constant provider did not complete its one-plan family");
    const auto candidate = provider.candidate(0);
    check(candidate && planner::validate_tree(candidate->catalog(), candidate->query(),
                                               candidate->tree()).valid,
          "native byte-string provider emitted a P02-invalid upper");
    return std::pair{candidate->structural_key(), *candidate};
  };
  const auto [key_80, candidate_80] = collect_constant(proof_80);
  const auto [key_81, candidate_81] = collect_constant(proof_81);
  const auto [key_nul_ab, candidate_nul_ab] = collect_constant(proof_nul_ab);
  const auto [key_nul_ac, candidate_nul_ac] = collect_constant(proof_nul_ac);
  const auto [key_nul_ab_long, candidate_nul_ab_long] = collect_constant(proof_nul_ab_long);
  check(key_80 == key_81 && key_80 == key_nul_ab && key_80 == key_nul_ac &&
            key_80 == key_nul_ab_long,
        "query-bound strings incorrectly changed local structural identity for the same tree shape");
  const auto candidate_constant = [](const planner::MinimumHeightCandidate& candidate) -> const std::string& {
    const auto& term = candidate.query().atoms[0].terms[0];
    const auto* value = std::get_if<Value>(&term);
    check(value != nullptr, "candidate binding lost its typed constant term");
    const auto* string = std::get_if<std::string>(value);
    check(string != nullptr, "candidate binding changed the constant scalar type");
    return *string;
  };
  check(candidate_constant(candidate_80) == byte_80 && candidate_constant(candidate_81) == byte_81 &&
            candidate_constant(candidate_nul_ab) == nul_ab &&
            candidate_constant(candidate_nul_ac) == nul_ac &&
            candidate_constant(candidate_nul_ab_long) == nul_ab_long,
        "published candidates lost original proof bytes or embedded-NUL distinctions");

  auto cache = planner::CandidateCache::create(8);
  auto provider_80 = planner::CandidateProvider::create(proof_80);
  static_cast<void>(drain_provider(provider_80, Slicing::one_shot));
  const auto prefix_80 = provider_80.snapshot();
  check(cache.install(prefix_80) == planner::CandidateCacheInstall::inserted,
        "binary constant snapshot could not be installed in the exact-binding cache");
  const auto equivalent_proof_80 = prove(string_constant_fixture(byte_80));
  check(cache.lookup(equivalent_proof_80).has_value(),
        "same invalid-byte string binding missed the exact-binding cache");
  for (const auto* proof : {&proof_81, &proof_nul_ab, &proof_nul_ac, &proof_nul_ab_long}) {
    check(!cache.lookup(*proof),
          "byte-distinct string constant hit a cache entry with the same structural tree");
  }
  expect_candidate_error([&] {
    static_cast<void>(planner::CandidateProvider::create(proof_81, {}, {}, {}, prefix_80));
  }, "candidate_binding", "byte-distinct cached-prefix admission");

  const auto identifier_fixture = arbitrary_string_binding_fixture();
  const auto identifier_proof = prove(identifier_fixture);
  auto identifier_provider = planner::CandidateProvider::create(identifier_proof);
  static_cast<void>(advance_until_ready(identifier_provider));
  auto identifier_cache = planner::CandidateCache::create(8);
  check(identifier_cache.install(identifier_provider.snapshot()) ==
            planner::CandidateCacheInstall::inserted,
        "arbitrary-byte identifier snapshot could not be cached");
  const auto same_identifier_proof = prove(identifier_fixture);
  check(identifier_cache.lookup(same_identifier_proof).has_value(),
        "same arbitrary-byte identifiers/alias/metadata missed exact cache equality");

  std::vector<std::pair<std::string, Fixture>> identifier_mutations;
  auto changed = identifier_fixture;
  changed.catalog.tables[0].name = "table-" + byte_81;
  identifier_mutations.emplace_back("table identifier byte", std::move(changed));
  changed = identifier_fixture;
  changed.catalog.tables[0].columns[0].name = std::string{"column\0b", 8};
  identifier_mutations.emplace_back("column identifier embedded NUL", std::move(changed));
  changed = identifier_fixture;
  changed.query.variables[0].name = "variable-" + byte_80;
  identifier_mutations.emplace_back("variable identifier byte", std::move(changed));
  changed = identifier_fixture;
  changed.query.atoms[0].occurrence = "occurrence-" + byte_81;
  identifier_mutations.emplace_back("occurrence identifier byte", std::move(changed));
  changed = identifier_fixture;
  changed.query.head[0].alias = std::string{"alias\0b", 7};
  identifier_mutations.emplace_back("output alias embedded NUL", std::move(changed));
  changed = identifier_fixture;
  changed.catalog.tables[0].key_hints[0].reason = "reason-" + byte_81;
  identifier_mutations.emplace_back("catalog metadata reason byte", std::move(changed));
  for (const auto& [label, mutation] : identifier_mutations) {
    const auto changed_proof = prove(mutation);
    check(!identifier_cache.lookup(changed_proof),
          label + ": binary exact-binding cache merged distinct string bytes");
  }

  const auto p02 = planner::validate_tree(identifier_fixture.catalog,
      identifier_fixture.query, identifier_proof.upper().tree());
  check(p02.valid && p02.native_height == 1,
        "P02 did not validate the arbitrary-byte identifier binding");
  const auto owner_progress = identifier_provider.progress();
  const auto progress_dom = io::write_candidate_progress(identifier_provider);
  check(progress_dom.at("query_binding").at("catalog").at("tables").at(0).at("name")
                .get<std::string>() == identifier_fixture.catalog.tables[0].name &&
            progress_dom.at("query_binding").at("query").at("variables").at(0).at("name")
                .get<std::string>() == identifier_fixture.query.variables[0].name &&
            progress_dom.at("query_binding").at("query").at("head").at(0).at("alias")
                .get<std::string>() == identifier_fixture.query.head[0].alias &&
            progress_dom.at("query_binding").at("catalog").at("tables").at(0)
                .at("key_hints").at(0).at("reason").get<std::string>() ==
                identifier_fixture.catalog.tables[0].key_hints[0].reason,
        "native candidate report DOM changed arbitrary bytes before text encoding");
  require_candidate_dump_rejected(progress_dom, "candidate progress text encoding");
  const auto after_dump_attempt = identifier_provider.progress();
  check(after_dump_attempt.phase == owner_progress.phase &&
            after_dump_attempt.last_stop == owner_progress.last_stop &&
            after_dump_attempt.work == owner_progress.work &&
            after_dump_attempt.candidate_count == owner_progress.candidate_count &&
            after_dump_attempt.records == owner_progress.records &&
            after_dump_attempt.cells == owner_progress.cells,
        "failed JSON text encoding advanced or mutated the provider");

  const auto identifier_candidate = identifier_provider.candidate(0);
  check(identifier_candidate && identifier_candidate->query().variables[0].name ==
            identifier_fixture.query.variables[0].name &&
            identifier_candidate->catalog().tables[0].key_hints[0].reason ==
                identifier_fixture.catalog.tables[0].key_hints[0].reason,
        "candidate handle did not retain arbitrary-byte binding fields");
  const auto candidate_dom = io::write_minimum_height_candidate(*identifier_candidate);
  require_candidate_dump_rejected(candidate_dom, "minimum-height candidate text encoding");
  check(identifier_candidate->valid() && identifier_candidate->height() == 1 &&
            planner::validate_tree(identifier_candidate->catalog(), identifier_candidate->query(),
                                  identifier_candidate->tree()).valid,
        "failed candidate text encoding altered the immutable candidate");

  planner::ResidualOptions residual_options;
  residual_options.mode = planner::ResidualMode::candidates_with_exact_repair;
  auto residual = planner::ResidualSearch::create(identifier_fixture.catalog,
      identifier_fixture.query, residual_options);
  for (std::size_t step = 0; step < 1'000'000 && !residual.candidate(); ++step) {
    const auto advanced = residual.advance({10'000'000, {}});
    check(advanced.progress.result != planner::ResidualResult::failed,
          "P05 did not produce a byte-binding residual seed");
    check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
              advanced.stopped_for == planner::ResidualStopReason::quantum_time ||
              residual.candidate().has_value(),
          "P05 byte-binding residual seed stopped unexpectedly");
  }
  const auto residual_seed = residual.candidate();
  check(residual_seed && residual_seed->valid() &&
            planner::validate_tree(identifier_fixture.catalog, identifier_fixture.query,
                                   residual_seed->tree()).valid,
        "P05 residual seed did not retain a checked arbitrary-byte binding");
  const auto alias_mutation = std::find_if(identifier_mutations.begin(), identifier_mutations.end(),
      [](const auto& item) { return item.first == "output alias embedded NUL"; });
  check(alias_mutation != identifier_mutations.end(), "missing byte-distinct alias test variant");
  const auto alias_proof = prove(alias_mutation->second);
  expect_candidate_error([&] {
    static_cast<void>(planner::CandidateProvider::create(alias_proof, {}, {}, *residual_seed));
  }, "candidate_binding", "byte-distinct residual-seed admission");
  expect_candidate_error([&] {
    static_cast<void>(planner::CandidateProvider::create(alias_proof, {}, {}, {},
                                                         identifier_provider.snapshot()));
  }, "candidate_binding", "byte-distinct cached-prefix admission");
}

}  // namespace

int main(int argc, char** argv) {
  try {
    check(argc == 2, "candidate unit test requires the copied tests/candidates fixture directory");
    const std::filesystem::path fixture_root{argv[1]};
    independent_reference_caps_are_incomplete();
    exhaustive_three_atom_family();
    fixture_cases_and_slicing(fixture_root);
    structural_key_and_non_normal_witness(fixture_root);
    resource_limits_and_lifetimes();
    exact_binding_cache_fences(fixture_root);
    residual_source_and_cached_provenance();
    mandatory_residual_and_wide_seed_boundaries();
    arbitrary_string_binding_domain();
    std::cout << "P07 candidate completeness, proof boundaries, keys, cache fences, and bounded resumes passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
