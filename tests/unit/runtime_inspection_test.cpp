#include "crown/planner/lower.hpp"
#include "crown/io/document.hpp"
#include "crown/io/inspection.hpp"
#include "crown/runtime/delta.hpp"
#include "runtime_probe.hpp"

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }

VariableSet variables(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

PhysicalPlan inspection_plan() {
  const Catalog catalog{1, {{"unary", {{"x", ScalarType::int64},
                                         {"label", ScalarType::string}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"root", TableId{0}, {VariableId{0}, IgnoredColumn{}}},
       {"left", TableId{0}, {VariableId{0}, IgnoredColumn{}}},
       {"middle", TableId{0}, {VariableId{0}, IgnoredColumn{}}},
       {"right", TableId{0}, {VariableId{0}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"root", NodeKind::generalized, variables({0}),
          {NodeId{1}, NodeId{5}}, {}, {}},
       {"three_way", NodeKind::generalized, variables({0}),
          {NodeId{2}, NodeId{3}, NodeId{4}}, {}, {}},
       {"left", NodeKind::native, variables({0}), {}, 1, {}},
       {"middle", NodeKind::native, variables({0}), {}, 2, {}},
       {"right", NodeKind::native, variables({0}), {}, 3, {}},
       {"root_input", NodeKind::native, variables({0}), {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Database inspection_database() {
  Database database;
  database.tables.resize(1);
  database.tables[0].insert({n(11), Value{std::string("row-11")}});
  return database;
}

const InvariantIssue& expect_issue(const InvariantReport& report,
    InvariantCode code, InvariantComponent component, const Row& key,
    std::optional<NodeId> node, std::optional<OccurrenceId> occurrence,
    std::uint64_t expected, std::uint64_t actual,
    std::optional<TableId> table = std::nullopt) {
  for (const auto& issue : report.issues) {
    if (issue.code == code && issue.component == component &&
        issue.node == node && issue.occurrence == occurrence &&
        issue.table == table && issue.key == key &&
        issue.expected == expected && issue.actual == actual) {
      return issue;
    }
  }
  throw std::runtime_error("inspection report omitted the exact localized issue");
}

void expect_clean(const InvariantReport& report, const std::string& label) {
  check(report.complete, label + ": invariant inspection was incomplete");
  check(report.valid(), label + ": healthy state was reported invalid");
  check(report.issues.empty(), label + ": healthy state retained diagnostic issues");
}

PhysicalRuntimeOptions tiny_physical_update_budget() {
  PhysicalRuntimeOptions options;
  options.work_limit = 0;
  options.support.work_limit = 0;
  return options;
}

DeltaOptions tiny_delta_update_budget() {
  DeltaOptions options;
  options.mode = DeltaMode::delta;
  options.work_limit = 0;
  options.physical = tiny_physical_update_budget();
  return options;
}

void canonical_state_is_owner_independent() {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  auto physical = PhysicalRuntime::initialize(plan, database,
      tiny_physical_update_budget());
  BuildOptions replay_build;
  replay_build.method = BuildMethod::insertion_replay;
  auto replayed = PhysicalRuntime::initialize(plan, database,
      tiny_physical_update_budget(), replay_build);
  check(physical.owner() != replayed.owner(),
        "independent physical initializations reused an owner");
  check(physical.canonical_state() == replayed.canonical_state(),
        "physical canonical state depends on owner or storage handles");
  expect_clean(physical.inspect_invariants(), "physical direct inspection");
  expect_clean(replayed.inspect_invariants(), "physical replay inspection");

  auto delta = DeltaRuntime::initialize(plan, database,
      tiny_delta_update_budget());
  auto replayed_delta = DeltaRuntime::initialize(plan, database,
      tiny_delta_update_budget(), replay_build);
  check(delta.owner() != replayed_delta.owner(),
        "independent delta initializations reused an owner");
  check(delta.canonical_state() == replayed_delta.canonical_state(),
        "delta canonical state depends on owner or storage handles");
  expect_clean(delta.inspect_invariants(), "delta direct inspection");
  expect_clean(replayed_delta.inspect_invariants(), "delta replay inspection");

  const auto canonical = physical.canonical_state();
  const auto& source = canonical.sources.front();
  check(std::is_sorted(source.begin(), source.end()),
        "canonical source rows are not in typed row order");
  for (const auto& occurrence : canonical.derivations) {
    check(std::is_sorted(occurrence.begin(), occurrence.end(),
              [](const CanonicalCount& left, const CanonicalCount& right) {
                return left.key < right.key;
              }), "canonical derivations are not in typed row order");
  }
  check(canonical.support.nodes.size() == plan.nodes().size(),
        "canonical state omitted support nodes");
  check(std::is_sorted(canonical.support.nodes.begin(),
            canonical.support.nodes.end(),
            [](const CanonicalNode& left, const CanonicalNode& right) {
              return left.node < right.node;
            }), "canonical nodes are not in node order");
  for (const auto& node : canonical.support.nodes) {
    check(std::is_sorted(node.records.begin(), node.records.end(),
              [](const CanonicalRecord& left, const CanonicalRecord& right) {
                return left.values < right.values;
              }), "canonical records are not in typed row order");
    check(std::is_sorted(node.parent.begin(), node.parent.end(),
              [](const CanonicalCount& left, const CanonicalCount& right) {
                return left.key < right.key;
              }), "canonical parent counts are not in typed row order");
    if (node.visible) {
      check(std::is_sorted(node.visible->begin(), node.visible->end(),
                [](const CanonicalCount& left, const CanonicalCount& right) {
                  return left.key < right.key;
                }), "canonical visible counts are not in typed row order");
    }
  }
  const auto delta_canonical = delta.canonical_state();
  check(delta_canonical.live.has_value(), "canonical delta omitted live state");
  for (const auto& factor : delta_canonical.live->factors) {
    const auto sorted_buckets = [](const std::vector<CanonicalBucket>& buckets) {
      return std::is_sorted(buckets.begin(), buckets.end(),
          [](const CanonicalBucket& left, const CanonicalBucket& right) {
            return left.key < right.key;
          });
    };
    check(sorted_buckets(factor.parents) && sorted_buckets(factor.children),
          "canonical live buckets are not in typed row order");
    for (const auto& bucket : factor.parents)
      check(std::is_sorted(bucket.rows.begin(), bucket.rows.end()),
            "canonical parent bucket rows are not in typed row order");
    for (const auto& bucket : factor.children)
      check(std::is_sorted(bucket.rows.begin(), bucket.rows.end()),
            "canonical child bucket rows are not in typed row order");
  }
}

void diagnostic_writer_is_deterministic_bounded_and_typed() {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  auto physical = PhysicalRuntime::initialize(plan, database);
  const auto physical_state = physical.canonical_state();
  const auto physical_json = io::write_runtime_state(physical_state);
  check(physical_json == io::write_runtime_state(physical_state),
        "physical diagnostic JSON is not deterministic");
  const auto parsed_physical = io::Json::parse(physical_json);
  check(parsed_physical.at("schema_version") == 1 &&
            parsed_physical.at("kind") == "physical",
        "physical diagnostic JSON has the wrong envelope");
  const auto& source_row = parsed_physical.at("state").at("sources")
      .at(0).at(0);
  check(source_row.size() == 2 && source_row.at(0).is_number_integer() &&
            source_row.at(0).get<std::int64_t>() == 11 &&
            source_row.at(1).is_string() &&
            source_row.at(1).get<std::string>() == "row-11",
        "physical diagnostic JSON lost typed integer or string values");
  check(io::write_runtime_state(physical_state, physical_json.size()) ==
            physical_json,
        "physical diagnostic writer rejected an exact byte limit");
  bool physical_limit_rejected = false;
  try {
    static_cast<void>(io::write_runtime_state(physical_state,
        physical_json.size() - 1));
  } catch (const Error& error) {
    physical_limit_rejected = error.code() == "resource_limit";
  }
  check(physical_limit_rejected,
        "physical diagnostic writer ignored its encoded byte limit");

  auto delta = DeltaRuntime::initialize(plan, database,
      tiny_delta_update_budget());
  const auto delta_state = delta.canonical_state();
  const auto delta_json = io::write_runtime_state(delta_state);
  check(delta_json == io::write_runtime_state(delta_state),
        "delta diagnostic JSON is not deterministic");
  const auto parsed_delta = io::Json::parse(delta_json);
  check(parsed_delta.at("schema_version") == 1 &&
            parsed_delta.at("kind") == "delta" &&
            !parsed_delta.at("state").at("live").is_null(),
        "delta diagnostic JSON omitted its live state");
  check(io::write_runtime_state(delta_state, delta_json.size()) == delta_json,
        "delta diagnostic writer rejected an exact byte limit");
  bool delta_limit_rejected = false;
  try {
    static_cast<void>(io::write_runtime_state(delta_state,
        delta_json.size() - 1));
  } catch (const Error& error) {
    delta_limit_rejected = error.code() == "resource_limit";
  }
  check(delta_limit_rejected,
        "delta diagnostic writer ignored its encoded byte limit");

  auto& support = RuntimeTestProbe::support(physical);
  const Row key{n(11)};
  const auto old_parent = RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, 5);
  const auto report = physical.inspect_invariants();
  const auto report_json = io::write_invariant_report(report);
  check(report_json == io::write_invariant_report(report),
        "invariant report JSON is not deterministic");
  const auto parsed_report = io::Json::parse(report_json);
  check(parsed_report.at("schema_version") == 1 &&
            parsed_report.at("kind") == "inspection" &&
            parsed_report.at("valid") == false &&
            parsed_report.at("issues").size() > 0,
        "invariant report JSON omitted its actual corruption issue");
  const auto& issue = parsed_report.at("issues").at(0);
  check(issue.at("code") == "support_count" &&
            issue.at("component") == "parent" &&
            issue.at("node") == 1 && issue.at("key").at(0).is_number_integer() &&
            issue.at("key").at(0).get<std::int64_t>() == 11 &&
            issue.at("expected") == old_parent && issue.at("actual") == 5,
        "invariant report JSON lost its typed, localized corruption fields");
  static_cast<void>(RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, old_parent));
  expect_clean(physical.inspect_invariants(),
      "diagnostic report after restoring its actual corruption");
  check(io::write_invariant_report(report, report_json.size()) == report_json,
        "invariant report writer rejected an exact byte limit");
  bool report_limit_rejected = false;
  try {
    static_cast<void>(io::write_invariant_report(report,
        report_json.size() - 1));
  } catch (const Error& error) {
    report_limit_rejected = error.code() == "resource_limit";
  }
  check(report_limit_rejected,
        "invariant report writer ignored its encoded byte limit");
}

void physical_inspection_localizes_actual_counter_corruption() {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  auto runtime = PhysicalRuntime::initialize(plan, database,
      tiny_physical_update_budget());
  auto& support = RuntimeTestProbe::support(runtime);
  const Row key{n(11)};

  const auto old_satisfied = RuntimeTestProbe::set_satisfied(
      support, NodeId{1}, key, 2);
  const auto satisfied = runtime.inspect_invariants();
  expect_issue(satisfied, InvariantCode::satisfied_count,
      InvariantComponent::record, key, NodeId{1}, std::nullopt, 3, 2);
  check(!satisfied.valid(), "corrupt satisfied-child counter was reported clean");
  static_cast<void>(RuntimeTestProbe::set_satisfied(
      support, NodeId{1}, key, old_satisfied));
  expect_clean(runtime.inspect_invariants(), "restored satisfied-child counter");

  const auto old_parent = RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, 8);
  const auto parent = runtime.inspect_invariants();
  expect_issue(parent, InvariantCode::support_count,
      InvariantComponent::parent, key, NodeId{1}, std::nullopt,
      old_parent, 8);
  check(!parent.valid(), "corrupt parent projection counter was reported clean");
  static_cast<void>(RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, old_parent));
  expect_clean(runtime.inspect_invariants(), "restored parent projection counter");

  const auto old_visible = RuntimeTestProbe::set_projection(
      support, NodeId{1}, true, key, 9);
  const auto visible = runtime.inspect_invariants();
  expect_issue(visible, InvariantCode::support_count,
      InvariantComponent::visible, key, NodeId{1}, std::nullopt,
      old_visible, 9);
  check(!visible.valid(), "corrupt visible projection counter was reported clean");
  static_cast<void>(RuntimeTestProbe::set_projection(
      support, NodeId{1}, true, key, old_visible));
  expect_clean(runtime.inspect_invariants(), "restored visible projection counter");

  const auto old_derivation = RuntimeTestProbe::set_derivation(
      runtime, OccurrenceId{0}, key, 7);
  const auto derivation = runtime.inspect_invariants();
  expect_issue(derivation, InvariantCode::derivation_count,
      InvariantComponent::derivation, key, NodeId{5}, OccurrenceId{0},
      1, 7, TableId{0});
  check(!derivation.valid(), "corrupt occurrence derivation was reported clean");
  static_cast<void>(RuntimeTestProbe::set_derivation(
      runtime, OccurrenceId{0}, key, old_derivation));
  expect_clean(runtime.inspect_invariants(), "restored occurrence derivation");
}

void inspection_budgets_never_report_clean_after_stopping() {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  auto runtime = PhysicalRuntime::initialize(plan, database,
      tiny_physical_update_budget());

  InspectionOptions no_work;
  no_work.work_limit = 0;
  const auto stopped_for_work = runtime.inspect_invariants(no_work);
  check(!stopped_for_work.complete && !stopped_for_work.valid(),
        "zero-work inspection budget was reported clean");

  const Row key{n(11)};
  auto& support = RuntimeTestProbe::support(runtime);
  const auto old_parent = RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, 5);
  InspectionOptions no_issues;
  no_issues.issue_limit = 0;
  const auto stopped_for_issues = runtime.inspect_invariants(no_issues);
  check(!stopped_for_issues.complete && !stopped_for_issues.valid(),
        "zero-issue inspection budget was reported clean after corruption");
  check(stopped_for_issues.issues.empty(),
        "zero-issue inspection budget retained a diagnostic");
  static_cast<void>(RuntimeTestProbe::set_projection(
      support, NodeId{1}, false, key, old_parent));
  expect_clean(runtime.inspect_invariants(), "inspection after budget restoration");
}

void delta_inspection_localizes_actual_live_counter_corruption() {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  auto runtime = DeltaRuntime::initialize(plan, database,
      tiny_delta_update_budget());
  const auto canonical = runtime.canonical_state();
  check(canonical.live.has_value(), "delta initialization omitted live state");
  const auto factor = std::find_if(canonical.live->factors.begin(),
      canonical.live->factors.end(), [](const CanonicalLiveFactor& item) {
        return item.node == NodeId{1};
      });
  check(factor != canonical.live->factors.end(),
        "three-child generalized node is absent from live factors");
  check(!factor->parents.empty() && !factor->children.empty(),
        "three-child live factor lacks a real parent or child bucket");

  const auto parent_bucket = factor->parents.front();
  const auto old_parent_bucket = RuntimeTestProbe::set_live_bucket(
      runtime, NodeId{1}, false, parent_bucket.key, parent_bucket.count + 5);
  const auto parent_report = runtime.inspect_invariants();
  expect_issue(parent_report, InvariantCode::support_count,
      InvariantComponent::live_parent, parent_bucket.key, NodeId{1},
      std::nullopt, parent_bucket.count, parent_bucket.count + 5);
  check(!parent_report.valid(), "corrupt live parent bucket was reported clean");
  static_cast<void>(RuntimeTestProbe::set_live_bucket(
      runtime, NodeId{1}, false, parent_bucket.key, old_parent_bucket));
  expect_clean(runtime.inspect_invariants(), "restored live parent bucket");

  const auto child_bucket = factor->children.front();
  const auto old_child_bucket = RuntimeTestProbe::set_live_bucket(
      runtime, NodeId{1}, true, child_bucket.key, child_bucket.count + 6);
  const auto child_report = runtime.inspect_invariants();
  expect_issue(child_report, InvariantCode::support_count,
      InvariantComponent::live_child, child_bucket.key, NodeId{1},
      std::nullopt, child_bucket.count, child_bucket.count + 6);
  check(!child_report.valid(), "corrupt live child bucket was reported clean");
  static_cast<void>(RuntimeTestProbe::set_live_bucket(
      runtime, NodeId{1}, true, child_bucket.key, old_child_bucket));
  expect_clean(runtime.inspect_invariants(), "restored live child bucket");

  for (const auto component : {InvariantComponent::live_factor,
                               InvariantComponent::live_parent,
                               InvariantComponent::live_child}) {
    const auto expected = component == InvariantComponent::live_factor
        ? canonical.live->rows
        : component == InvariantComponent::live_parent
            ? canonical.live->parent_rows : canonical.live->child_rows;
    const auto old = RuntimeTestProbe::set_live_total(runtime, component,
        expected + 1);
    const auto report = runtime.inspect_invariants();
    expect_issue(report, InvariantCode::aggregate_count, component, {},
        std::nullopt, std::nullopt, expected, expected + 1);
    check(!report.valid(), "corrupt live aggregate total was reported clean");
    static_cast<void>(RuntimeTestProbe::set_live_total(runtime, component, old));
    expect_clean(runtime.inspect_invariants(), "restored live aggregate total");
  }
}

int dump_diagnostic(const std::string& mode) {
  const auto plan = inspection_plan();
  const auto database = inspection_database();
  if (mode == "--dump-physical") {
    auto runtime = PhysicalRuntime::initialize(plan, database);
    std::cout << io::write_runtime_state(runtime.canonical_state()) << '\n';
    return 0;
  }
  if (mode == "--dump-delta") {
    auto runtime = DeltaRuntime::initialize(plan, database,
        tiny_delta_update_budget());
    std::cout << io::write_runtime_state(runtime.canonical_state()) << '\n';
    return 0;
  }
  if (mode == "--dump-report") {
    auto runtime = PhysicalRuntime::initialize(plan, database);
    auto& support = RuntimeTestProbe::support(runtime);
    const Row key{n(11)};
    const auto old_parent = RuntimeTestProbe::set_projection(
        support, NodeId{1}, false, key, 5);
    const auto report = runtime.inspect_invariants();
    const auto json = io::write_invariant_report(report);
    static_cast<void>(RuntimeTestProbe::set_projection(
        support, NodeId{1}, false, key, old_parent));
    expect_clean(runtime.inspect_invariants(),
        "diagnostic dump after restoring its actual corruption");
    std::cout << json << '\n';
    return 0;
  }
  throw std::runtime_error("unknown runtime inspection dump mode");
}

}  // namespace

int main(int argc, char** argv) {
  try {
    if (argc == 2) return dump_diagnostic(argv[1]);
    if (argc != 1) throw std::runtime_error("expected at most one dump mode");
    canonical_state_is_owner_independent();
    diagnostic_writer_is_deterministic_bounded_and_typed();
    physical_inspection_localizes_actual_counter_corruption();
    inspection_budgets_never_report_clean_after_stopping();
    delta_inspection_localizes_actual_live_counter_corruption();
    std::cout << "runtime inspection tests passed\n";
    return 0;
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
