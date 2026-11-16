#include "selection_fixture.hpp"
#include "update_pattern_fixture.hpp"
#include "window_checkpoint_test_fixture.hpp"
#include "session_journal_fixture.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/recovery/session_image.hpp"
#include "crown/runtime/session_generation.hpp"
#include <nlohmann/json.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c02_test::check;
namespace ip = crown::patterns;
namespace pp = planner::patterns;
namespace ps = planner::selection;
namespace rs = runtime::selection;
namespace win = window_checkpoint_test;
using Json = nlohmann::json;

// Ordinary fixture compilation precedes profile access. The real search/provider
// supplies candidate authority; neither expected tags nor JSON create authority.
CompiledProgram compile(const c02_test::Fixture& fixture,
    const planner::CandidateSnapshot& family, bool indexed = false) {
  return CompiledProgram::standalone(planner::lower_tree(fixture.catalog, fixture.query,
      family.candidate(0)->tree(), indexed ? s04_runtime::options() : PhysicalOptions{}));
}
ps::Request request(const CompiledProgram& program, std::span<const ip::TableRule> rules) {
  ps::Request result; result.policy = ps::Policy::height_only;
  result.update_patterns = ip::Declaration::capture(program.account(), program, rules);
  return result;
}
SessionOptions monitored(const ps::Request& requested) {
  SessionOptions result; result.update_patterns = UpdatePatternOptions{*requested.update_patterns, {}};
  return result;
}
std::string hash(const std::array<char, 64>& value) { return {value.data(), value.size()}; }
std::string_view bytes(const recovery::SessionImage& image) { return {image.bytes.data(), image.bytes.size()}; }
void physical(QuerySession& session, PhysicalSetUpdate update) {
  io::TransportBatch batch({io::InputEvent{std::move(update), {}}});
  check(session.enqueue(batch) == io::Admission::accepted && session.begin_next(), "profile input missing");
  static_cast<void>(win::finish(session));
}

// These JSON values are test exports for human inspection, outside query
// accounting and allocation-denial scopes. Native profiles stay shared handles.
Json describe(const ps::PatternGuarantee& profile, const char* example) {
  const auto& analysis = profile.analysis();
  Json result{{"example", example}, {"scope", "conditional_selected_plan"},
      {"support_action_bound", std::string(ps::PatternGuarantee::bound)},
      {"units", std::string(ps::PatternGuarantee::units)},
      {"input_accounting", std::string(ps::PatternGuarantee::input_accounting)},
      {"excluded_costs", std::string(ps::PatternGuarantee::excluded_costs)},
      {"proof_reference", std::string(ps::PatternGuarantee::proof_reference)},
      {"sufficient_case", std::string(pp::name(analysis.sufficient))},
      {"source_transfer", std::string(pp::name(analysis.transfer))},
      {"checked_native_height", analysis.height},
      {"selected_route", profile.plan().route() == PhysicalRoute::tree ? "tree" :
          profile.plan().route() == PhysicalRoute::constant_true ? "constant_true" : "constant_false"},
      {"selected_operator_native_height", *profile.plan().validation().native_height},
      {"source_sha256", hash(analysis.declaration.source_sha256())},
      {"selected_physical_sha256", std::string(profile.plan().physical_sha256())},
      {"candidate_structural_key", analysis.candidate.structural_key()},
      {"rules", Json::array()}, {"native_edges", Json::array()}};
  for (const auto& rule : analysis.declaration.rules()) result["rules"].push_back({
      {"physical_table", rule.table.value}, {"insertion_only", rule.insertion_only}, {"raw_fifo_scope", rule.fifo_scope}});
  for (const auto& edge : analysis.edges) result["native_edges"].push_back({
      {"parent", edge.parent.value}, {"child", edge.child.value},
      {"parent_table", edge.parent_table.value}, {"child_table", edge.child_table.value},
      {"basis", std::string(pp::name(edge.basis))}, {"raw_fifo_scope", edge.fifo_scope}});
  return result;
}
Json describe(const rs::PatternGuarantee& profile, const char* example) {
  const auto selected = profile.selected(); auto result = describe(selected, example);
  const auto& enforced = profile.enforcement(); const auto stamp = profile.stamp();
  result["scope"] = "selected_plan_with_actual_session_premises_as_of_capture";
  result["selected_plan_matches_capture"] = profile.selected_plan_matches_capture();
  result["observed_owner"] = stamp.owner.value; result["observed_physical_sequence"] = stamp.sequence;
  result["enforcement"] = {{"policy", "reject"},
      {"history", enforced.history == PatternHistory::restored_checkpoint ? "trusted_restored_checkpoint" : "current_session"},
      {"origin_sequence", enforced.origin_sequence}, {"origin_command_sequence", enforced.origin_command_sequence},
      {"monitored_sequence", enforced.monitored_sequence}, {"completed_command_sequence", enforced.completed_command_sequence},
      {"observed_physical_sha256", hash(enforced.physical_sha256)}, {"source_sha256", hash(enforced.declaration.source_sha256())},
      {"violation", enforced.violation.has_value()}, {"retrospective_work_measurement", false}};
  return result;
}

// The profile must name the selected candidate, native program and exact rules;
// it shares those already funded objects rather than cloning their payloads.
ps::PatternGuarantee qualified(const ps::Selection& selected, pp::SufficientCase expected) {
  const auto value = selected.pattern_guarantee(); check(value.has_value(), "proved selection omitted its profile");
  const auto& analysis = value->analysis();
  check(analysis.sufficient == expected && analysis.declaration.matches(value->plan()) &&
      analysis.candidate.structural_key() == selected.selected().structural_key() &&
      &analysis == &selected.pattern_analyses()[selected.selected_index()] && &value->plan() == &selected.plan(),
      "profile lost selected proof/source context or cloned the report");
  check(ps::PatternGuarantee::bound == "O_Q(I + U)" && !ps::PatternGuarantee::units.empty() &&
      !ps::PatternGuarantee::input_accounting.empty() && !ps::PatternGuarantee::excluded_costs.empty() &&
      ps::PatternGuarantee::proof_reference == "docs/update_patterns.md#support-action-guarantee-profile",
      "qualified profile omitted its public model or proof reference");
  return *value;
}

void pure_contract(bool indexed, Json& reports) {
  const auto fixture = c02_test::fixture(); const auto family = c02_test::candidates(fixture);
  const auto program = compile(fixture, family, indexed); const ps::Source basis = ps::PhysicalBasis{program};
  ps::Request plain; plain.policy = ps::Policy::height_only;
  const auto baseline = c05_test::complete(ps::select(family, basis, plain));
  check(!baseline.pattern_guarantee(), "undeclared selection fabricated a pattern profile");
  const auto unknown = ps::select(family, basis, request(program, {}));
  check(!unknown.selection && unknown.stop == ps::Stop::constraint_unsatisfied,
      "unproved candidate family published a profile-bearing selection");
  const std::array all{ip::TableRule{TableId{0}, true, 0}, ip::TableRule{TableId{1}, true, 0}, ip::TableRule{TableId{2}, true, 0}};
  const auto requested = request(program, all); auto cache = ps::PlanCache::create();
  const auto first = c05_test::complete(ps::select(family, basis, requested, {}, &cache, ps::CacheUse::read_write));
  const auto hit = c05_test::complete(ps::select(family, basis, requested, {}, &cache, ps::CacheUse::read_write));
  const auto profile = qualified(hit, pp::SufficientCase::insertion_only);
  check(hit.cache_observation().disposition == ps::CacheDisposition::hit &&
      profile.analysis().declaration.rules().size() == all.size() &&
      std::equal(all.begin(), all.end(), profile.analysis().declaration.rules().begin()) &&
      *first.cache_binding() == *hit.cache_binding(), "cache profile omitted exact canonical rules");
  reports.push_back(describe(profile, indexed ? "indexed-all-source-insertion-only" : "reference-all-source-insertion-only"));
  const bool choose_t = c02_test::shape(baseline.selected().tree()) != 1;
  const std::array mixed{ip::TableRule{TableId{choose_t ? 2U : 0U}, true, 0}};
  const auto chosen = c05_test::complete(ps::select(family, basis, request(program, mixed)));
  const auto mixed_profile = qualified(chosen, pp::SufficientCase::height_two_edges);
  check(chosen.selected_index() != baseline.selected_index() &&
      std::all_of(mixed_profile.analysis().edges.begin(), mixed_profile.analysis().edges.end(),
          [](const auto& edge) { return edge.basis != pp::EdgeBasis::unproved; }),
      "profile did not follow the actual pattern-conditioned plan decision");
  reports.push_back(describe(mixed_profile, "typed-mixed-height-two"));
}

// Constant routes and arbitrary height-one events are positive proved cases,
// even with an explicitly empty rule declaration. Absence stays distinct.
void simple_routes(Json& reports) {
  for (const bool contradiction : {false, true}) {
    c02_test::Fixture fixture; fixture.query.contradiction = contradiction;
    const auto family = c02_test::candidates(fixture, 0, 0); const auto program = compile(fixture, family);
    const auto selected = c05_test::complete(ps::select(family, ps::PhysicalBasis{program}, request(program, {})));
    const auto profile = qualified(selected, pp::SufficientCase::constant_result);
    check(profile.analysis().transfer == pp::Transfer::not_required, "constant profile invented a source premise");
    reports.push_back(describe(profile, contradiction ? "constant-empty" : "constant-unit"));
  }
  c02_test::Fixture fixture;
  fixture.catalog.tables = {{"unused", {{"unused", ScalarType::int64}}},
      {"r", {{"x", ScalarType::int64}, {"payload", ScalarType::int64}}}};
  fixture.query.variables = {{"x", ScalarType::int64}};
  fixture.query.atoms = {{"r", TableId{1}, {VariableId{0}, IgnoredColumn{}}}};
  fixture.query.head = {{VariableId{0}, "x"}};
  const auto family = c02_test::candidates(fixture, 1, 0); const auto program = compile(fixture, family);
  const auto selected = c05_test::complete(ps::select(family, ps::PhysicalBasis{program}, request(program, {})));
  const auto profile = qualified(selected, pp::SufficientCase::height_one);
  check(profile.analysis().transfer == pp::Transfer::checked_event_mapping && profile.analysis().declaration.rules().empty() &&
      program.inputs().front().base == TableId{1}, "height-one profile required an invented insertion/FIFO rule");
  reports.push_back(describe(profile, "arbitrary-height-one-projection"));

  // A contradictory body still has its genuine structural candidate. Its
  // executable constant route deliberately uses the canonical empty tree.
  auto contradictory = c02_test::fixture(); contradictory.query.contradiction = true;
  const auto original = c02_test::candidates(contradictory);
  const auto constant = CompiledProgram::standalone(planner::lower_tree(
      contradictory.catalog, contradictory.query, FreeConnexTree{}));
  const auto empty = c05_test::complete(ps::select(original, ps::PhysicalBasis{constant}, request(constant, {})));
  const auto distinction = qualified(empty, pp::SufficientCase::constant_result);
  check(distinction.analysis().height == 2 && !distinction.analysis().candidate.tree().nodes.empty() &&
      distinction.plan().route() == PhysicalRoute::constant_false && distinction.plan().tree().nodes.empty() &&
      distinction.plan().validation().native_height == 0,
      "constant operator geometry replaced the retained original candidate proof");
  reports.push_back(describe(distinction, "contradictory-nonempty-body-with-constant-operator"));
}

void taller_contract(Json& reports) {
  const auto fixture = pattern_test::height_three_fixture(); const auto family = pattern_test::height_three_family(fixture);
  const auto program = compile(fixture, family); std::vector<ip::TableRule> rules;
  for (std::size_t table = 0; table < fixture.catalog.tables.size(); ++table) rules.push_back({TableId{table}, true, 0});
  const auto& tree = family.candidate(0)->tree(); std::vector<NodeId> first{*tree.root}; std::size_t index = 0;
  while (tree.nodes[first[index].value].kind != NodeKind::native) {
    const auto& node = tree.nodes[first[index++].value]; first.insert(first.end(), node.children.begin(), node.children.end());
  }
  rules[fixture.query.atoms[*tree.nodes[first[index].value].occurrence].table.value].insertion_only = false;
  const auto selected = c05_test::complete(ps::select(family, ps::PhysicalBasis{program}, request(program, rules)));
  const auto profile = qualified(selected, pp::SufficientCase::subtree_edges);
  check(profile.analysis().height == 3 && std::any_of(profile.analysis().edges.begin(), profile.analysis().edges.end(),
      [](const auto& edge) { return edge.basis == pp::EdgeBasis::subtree_insertion_only; }),
      "taller profile omitted the whole-subtree premise");
  reports.push_back(describe(profile, "taller-wholly-monotone-child-subtrees"));
}

// Profiles own the capture graph and remain as-of values after advancement,
// rejection and owner destruction. Access and copies must allocate nothing.
rs::PatternGuarantee live_contract(bool indexed, Json& reports) {
  const auto fixture = c02_test::fixture(); const auto family = c02_test::candidates(fixture);
  const auto source = compile(fixture, family, indexed);
  const std::array rules{ip::TableRule{TableId{0}, true, 0}, ip::TableRule{TableId{1}, true, 0}, ip::TableRule{TableId{2}, true, 0}};
  const auto requested = request(source, rules);
  const auto pure = c05_test::complete(ps::select(family, ps::PhysicalBasis{source}, requested)); const auto program = pure.plan();
  auto owner = QuerySession::create_typed(program, {}, monitored(requested)); owner->start();
  owner->configure_workload_statistics(c05_test::counters());
  auto undeclared = requested; undeclared.update_patterns.reset();
  const auto plain = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *owner, undeclared));
  check(!plain.pattern_guarantee(), "a monitor without requested analysis fabricated a current profile");
  const auto first = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *owner, requested));
  const auto old = *first.pattern_guarantee();
  check(old.enforcement().monitored_sequence == 0 && old.stamp().sequence == 0 &&
      old.stamp().owner == owner->report_metadata().owner() && old.selected_plan_matches_capture(),
      "actual profile omitted owner binding or disagreed with the installed selected plan");
  const auto before = first.selection().account().statistics().current; bool accessed = false; std::size_t calls = 0;
  {
    s04_alloc::Scope denied(0); const auto conditional = first.selection().pattern_guarantee();
    const auto actual = first.pattern_guarantee(); const auto selected = actual->selected();
    auto copy = *actual; const auto moved = std::move(copy);
    accessed = conditional && actual && selected.analysis().declaration.matches(selected.plan()) &&
        moved.stamp().owner == copy.stamp().owner && moved.selected_plan_matches_capture() &&
        moved.enforcement().monitored_sequence == 0;
    calls = s04_alloc::calls;
  }
  check(accessed && calls == 0 && first.selection().account().statistics().current == before,
      "profile access/copy allocated or changed retained query bytes");
  physical(*owner, {1, TableId{2}, SetOperation::insert, {std::int64_t{1}}});
  const auto next = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *owner, requested));
  const auto latest = *next.pattern_guarantee();
  check(old.enforcement().monitored_sequence == 0 && latest.enforcement().monitored_sequence == 1 &&
      latest.stamp().sequence == 1 && latest.enforcement().completed_command_sequence == 1,
      "historical profile was refreshed silently or confused command/physical progress");
  io::TransportBatch erase({io::InputEvent{{2, TableId{2}, SetOperation::erase, {std::int64_t{1}}}, {}}});
  check(owner->enqueue(erase) == io::Admission::accepted, "forbidden profile fixture not queued");
  bool rejected = false;
  try { static_cast<void>(owner->begin_next()); } catch (const Error& error) { rejected = error.code() == "update_pattern_violation"; }
  check(rejected && !rs::select_current(family, ps::PhysicalBasis{program}, *owner, requested).selection &&
      !latest.enforcement().violation && owner->update_pattern_status().violation,
      "rejected owner produced a current profile or mutated a retained historical profile");
  owner.reset(); reports.push_back(describe(latest, "retained-profile-after-advance-rejection-and-owner-release"));
  return latest;
}

// Window metadata commands and physical epochs use different progress domains.
// Restore keeps the declaration but labels past enforcement as trusted history.
void window_contract(bool indexed, Json& reports) {
  const auto fixture = c02_test::fixture(); const auto family = c02_test::candidates(fixture);
  const auto source = compile(fixture, family, indexed);
  const std::array rules{ip::TableRule{TableId{0}, false, 41}, ip::TableRule{TableId{1}, false, 41}, ip::TableRule{TableId{2}, false, 41}};
  const auto requested = request(source, rules);
  const auto chosen = c05_test::complete(ps::select(family, ps::PhysicalBasis{source}, requested)); const auto program = chosen.plan();
  WindowOptions windows; windows.width = 100; windows.fifo = WindowFifoPolicy::unrestricted;
  windows.managed_tables = {TableId{0}, TableId{1}, TableId{2}};
  auto owner = QuerySession::create_windowed(program, windows, {}, monitored(requested)); owner->start();
  owner->configure_workload_statistics(c05_test::counters());
  win::command(*owner, win::insertion(1, 1, TableId{0}, 1, 0));
  win::command(*owner, win::insertion(2, 2, TableId{0}, 1, 1));
  win::command(*owner, {3, io::AdvanceWatermark{0}, {}});
  const auto current = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *owner, requested));
  const auto profile = *current.pattern_guarantee(); const auto selected = profile.selected();
  check(selected.analysis().sufficient == pp::SufficientCase::height_two_edges &&
      profile.stamp().sequence == 1 && profile.enforcement().monitored_sequence == 1 &&
      profile.enforcement().completed_command_sequence == 3 &&
      profile.enforcement().history == PatternHistory::current_session,
      "FIFO profile lost its leaf premise or metadata-only command boundary");
  const auto image = owner->checkpoint_image(); auto restored = QuerySession::restore_image(program, bytes(image)); restored->start();
  const auto recovered = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *restored, requested));
  const auto restored_profile = *recovered.pattern_guarantee();
  check(restored_profile.enforcement().history == PatternHistory::restored_checkpoint &&
      restored_profile.enforcement().monitored_sequence == 1 && restored_profile.enforcement().completed_command_sequence == 3 &&
      restored_profile.stamp().owner == restored->report_metadata().owner() && restored_profile.stamp().sequence == 1,
      "profile authenticated restored history or dropped its actual restored owner/prefix");
  win::command(*restored, {4, io::WindowWithdraw{2}, {}});
  const auto advanced = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{program}, *restored, requested));
  const auto metadata = *advanced.pattern_guarantee();
  check(metadata.enforcement().completed_command_sequence == 4 && metadata.enforcement().monitored_sequence == 1 &&
      restored_profile.enforcement().completed_command_sequence == 3,
      "metadata-only withdrawal changed physical progress or historical capture");
  reports.push_back(describe(restored_profile, "restored-fifo-profile-trust-and-command-domain"));
}

// A real measured replacement is initially a proposed plan, not the installed
// tree. After durable installation a fresh capture must report the new identity.
void replacement_contract(bool indexed, Json& reports) {
  const auto fixture = c02_test::fixture(); const auto family = c02_test::candidates(fixture);
  const auto program = compile(fixture, family, indexed); const std::array rules{ip::TableRule{TableId{2}, true, 0}};
  const auto requested = request(program, rules); session_journal_test::Directory directory;
  WindowOptions windows; windows.managed_tables = {TableId{0}, TableId{1}, TableId{2}};
  windows.fifo = WindowFifoPolicy::unrestricted;
  auto owner = QuerySession::create_windowed(program, windows, {}, monitored(requested)); owner->start();
  SessionGenerationOptions generation; generation.journal = session_journal_test::options();
  owner->enable_generation(directory.file("profile.root"), generation); owner->configure_workload_statistics(c05_test::counters());
  const auto choice = c05_test::complete(rs::select_for_reoptimization(family, ps::PhysicalBasis{program}, *owner, requested));
  const auto proposed = *choice.pattern_guarantee(); const auto proposed_plan = proposed.selected();
  check(!proposed.selected_plan_matches_capture() &&
      proposed_plan.plan().physical_sha256() != hash(proposed.enforcement().physical_sha256),
      "proposed pattern-compatible plan was mislabeled as the observed physical plan");
  reoptimization::Options change; change.forecast = reoptimization::Forecast{1000000000, 1, UINT64_MAX};
  rs::begin_reoptimization(*owner, choice, change); owner->request_reoptimization_barrier();
  check(owner->advance_reoptimization(100000).phase == reoptimization::Phase::verified, "profile target did not verify");
  const auto artifact = io::CompilerPlanArtifact::prepare(resource::MemoryAccount::create(32 * 1024 * 1024), choice.selection().plan());
  check(owner->publish_reoptimization(artifact).phase == reoptimization::Phase::complete, "profile target did not publish");
  const auto installed = owner->report_metadata().plan(); owner->start();
  const auto fresh = c05_test::complete(rs::select_current(family, ps::PhysicalBasis{installed}, *owner, requested));
  const auto actual = *fresh.pattern_guarantee(); const auto actual_plan = actual.selected();
  check(actual.selected_plan_matches_capture() && actual_plan.plan().physical_sha256() == installed.physical_sha256() &&
      !proposed.selected_plan_matches_capture() && proposed.enforcement().physical_sha256 != actual.enforcement().physical_sha256,
      "fresh replacement profile retained the old identity or rewrote a historical capture");
  reports.push_back(describe(proposed, "proposed-plan-before-durable-replacement"));
  reports.push_back(describe(actual, "installed-plan-after-fresh-capture"));
}
} // namespace

int main(int argc, char** argv) {
  try {
    Json reports = Json::array(); simple_routes(reports); taller_contract(reports);
    for (const bool indexed : {false, true}) {
      pure_contract(indexed, reports); const auto retained = live_contract(indexed, reports);
      const auto selected = retained.selected();
      check(selected.analysis().declaration.matches(selected.plan()) && retained.enforcement().monitored_sequence == 1,
          "profile did not retain its graph after all original handles were released");
      window_contract(indexed, reports); replacement_contract(indexed, reports);
    }
    if (argc > 1) {
      const std::filesystem::path directory(argv[1]); std::filesystem::create_directories(directory);
      std::ofstream output(directory / "profiles.json"); output << reports.dump(2) << '\n';
      check(output.good(), "profile examples could not be written");
    }
    std::cout << "pattern guarantee profiles passed; examples=" << reports.size()
              << " zero-allocation controls=2 backends=2\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
