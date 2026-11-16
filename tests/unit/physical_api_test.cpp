#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/normalization.hpp"
#include "crown/io/physical.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/verify.hpp"
#include "crown/storage/physical.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace {
using namespace crown;
using io::Json;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
void error(const std::function<void()>& action, std::string_view code) {
  try { action(); }
  catch (const Error& failure) {
    check(failure.code() == code, "wrong error: " + failure.code() + ", expected " + std::string(code));
    return;
  }
  throw std::runtime_error("expected error: " + std::string(code));
}
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
std::string read_file(const std::filesystem::path& path) {
  std::ifstream stream(path);
  check(bool(stream), "cannot open fixture: " + path.string());
  return {std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};
}

static_assert(!std::is_default_constructible_v<PhysicalPlan>);
static_assert(!std::is_aggregate_v<PhysicalPlan>);
static_assert(std::is_copy_constructible_v<PhysicalPlan> && std::is_move_constructible_v<PhysicalPlan>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().catalog()), const Catalog&>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().query()), const Query&>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().tree()), const FreeConnexTree&>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().inputs()), const std::vector<PhysicalInput>&>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().nodes()), const std::vector<PhysicalNode>&>);
static_assert(std::is_same_v<decltype(std::declval<const PhysicalPlan&>().enumeration()), const EnumerationProgram&>);
static_assert(std::is_constructible_v<storage::ReferencePlanStorage, PhysicalPlan>);
static_assert(!std::is_default_constructible_v<storage::ReferencePlanStorage>);
static_assert(!std::is_copy_constructible_v<storage::ReferencePlanStorage>);
static_assert(!std::is_constructible_v<storage::ReferencePlanStorage, Catalog>);

struct DirectFixture {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  Date day = Date::parse("2024-02-29");
  Decimal amount = Decimal::parse("123.40");
};
DirectFixture direct_fixture() {
  DirectFixture fixture;
  fixture.catalog = {17, {{"typed", {
      {"first", ScalarType::int64}, {"again", ScalarType::int64},
      {"fixed_number", ScalarType::int64}, {"label", ScalarType::string}, {"enabled", ScalarType::boolean},
      {"day", ScalarType::date}, {"amount", ScalarType::decimal, false, Collation::binary, DecimalSpec{6, 2}},
      {"ignored", ScalarType::string}}}}};
  fixture.query = {{{"x", ScalarType::int64}},
      {{"typed", TableId{0}, {VariableId{0}, VariableId{0}, Value{std::int64_t{17}}, s("keep"), Value{true}, Value{fixture.day}, Value{fixture.amount}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}, {VariableId{0}, "again"}}, false};
  fixture.tree = {NodeId{0}, {{"typed", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return fixture;
}
Row typed_row(std::int64_t first, std::int64_t again, std::string label = "keep", bool enabled = true,
              Date day = Date::parse("2024-02-29"), Decimal amount = Decimal::parse("123.40"),
              std::string ignored = "arbitrary", std::int64_t fixed = 17) {
  return {n(first), n(again), n(fixed), s(std::move(label)), Value{enabled}, Value{day}, Value{amount}, s(std::move(ignored))};
}
DirectFixture pair_fixture() {
  DirectFixture fixture;
  fixture.catalog = {4, {{"left", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"right", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  fixture.query = {{{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}}, false};
  fixture.tree = {NodeId{0}, {
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
      {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return fixture;
}

void direct_inputs_and_result_assembly() {
  auto fixture = direct_fixture();
  const auto plan = planner::lower_tree(fixture.catalog, fixture.query, fixture.tree);
  check(plan.route() == PhysicalRoute::tree && plan.validation().valid && plan.validation().native_height == 1,
        "direct CQ lowering retains its independently checked one-node tree");
  check(plan.inputs().size() == 1 && plan.inputs()[0].base == TableId{0} && plan.inputs()[0].logical_table == TableId{0},
        "direct input retains both its physical base and logical table");
  const auto& input = plan.inputs()[0];
  check(input.physical_layout.fields().size() == 8 && input.physical_layout.fields()[6].decimal == DecimalSpec{6, 2},
        "fixed decimal precision and scale survive physical layout compilation");
  check(std::ranges::equal(input.projection.fields(),std::vector<FieldId>{FieldId{0}}) && input.equalities.size() == 1 &&
        input.equalities[0].left == FieldId{0} && input.equalities[0].right == FieldId{1},
        "repeated variable uses its first physical slot and checks the repeated slot");
  check(input.constants.size() == 5 && input.constants[0].field == FieldId{2} && input.constants[0].value == Value{std::int64_t{17}} &&
        input.constants[1].field == FieldId{3} && input.constants[1].value == s("keep") &&
        input.constants[2].field == FieldId{4} && input.constants[2].value == Value{true} &&
        input.constants[3].field == FieldId{5} && input.constants[3].value == Value{fixture.day} &&
        input.constants[4].field == FieldId{6} && input.constants[4].value == Value{fixture.amount},
        "integer, string, Boolean, date, and fixed-decimal constants retain exact tagged values");

  const auto accepted = plan.adapt_input(OccurrenceId{0}, typed_row(8, 8));
  check(accepted && accepted->values() == Row{n(8)}, "ignored physical columns do not alter the numeric core input");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 9)), "unequal repeated-variable columns are filtered");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 8, "keep", true, fixture.day, fixture.amount, "arbitrary", 18)),
        "integer constants are checked before projection");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 8, "other")), "string constants are checked before projection");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 8, "keep", false)), "Boolean constants are checked before projection");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 8, "keep", true, Date::parse("2024-03-01"))),
        "date constants are checked before projection");
  check(!plan.adapt_input(OccurrenceId{0}, typed_row(8, 8, "keep", true, fixture.day, Decimal::parse("123.41"))),
        "decimal constants retain exact scale/value comparison");
  error([&] { static_cast<void>(plan.adapt_input(OccurrenceId{1}, typed_row(8, 8))); }, "invalid_input_port");

  const auto& step = plan.enumeration().steps.at(0);
  const auto& assignment_layout = plan.relations().at(step.relation.value).layout;
  const std::vector<storage::Tuple> assignments{assignment_layout.tuple({n(8)})};
  check(plan.assemble_result(assignments).values() == Row{n(8), n(8)}, "ordered repeated head slots assemble from one assignment");
  check(plan.result_layout().fields().size() == 2 && plan.result_layout().fields()[0].variable == VariableId{0} &&
        plan.result_layout().fields()[1].variable == VariableId{0}, "result descriptor records repeated output variables");
}

void native_child_keys_and_storage() {
  const auto fixture = pair_fixture();
  const auto plan = planner::lower_tree(fixture.catalog, fixture.query, fixture.tree);
  check(plan.edges().size() == 1 && plan.edges()[0].parent == NodeId{0} && plan.edges()[0].child == NodeId{1},
        "manual native-child fixture compiles its single directed edge");
  const auto& edge = plan.edges()[0];
  const auto& child = plan.nodes()[edge.child.value];
  check(edge.parent_key.target().same_token(child.parent_key.target()), "native parent and child separator lookups share a runtime key token");
  check(edge.reverse_index.has_value(), "native parent has a compiled reverse child-support index");
  const auto& requirement = plan.indexes().at(edge.reverse_index->value);
  check(requirement.relation == plan.nodes()[edge.parent.value].records &&
        requirement.projection.target().same_token(child.parent_key.target()) &&
        requirement.uses == std::vector<IndexUse>{IndexUse::reverse_child_support},
        "reverse index is attached to the parent records with the child's key descriptor");

  storage::ReferencePlanStorage state(plan);
  state.check_invariants();
  check(state.plan().physical_sha256() == plan.physical_sha256(), "plan storage owns the immutable validated plan");
  for (const auto& index : plan.indexes()) {
    const auto runtime = state.index(index.id);
    check(state.table(index.relation).projection(runtime).same_token(index.projection), "initialized index uses its compiled projection token");
  }
  const auto& parent = plan.nodes()[edge.parent.value];
  const auto parent_row = parent.layout.tuple({n(3), n(7)});
  check(state.table(parent.records).insert(parent_row).inserted, "reference plan storage accepts a tuple in the native parent layout");
  const auto child_key = child.parent_key.target().tuple({n(7)});
  const auto cross_bucket = state.table(parent.records).bucket(state.index(*edge.reverse_index), child_key);
  check(cross_bucket.size() == 1 && state.table(parent.records).get(cross_bucket[0])->values() == Row{n(3), n(7)},
        "a child support key probes the native parent's reverse index through its shared target token");
  state.check_invariants();
  error([&] { static_cast<void>(state.table(RelationId{plan.relations().size()})); }, "unknown_relation");
  error([&] { static_cast<void>(state.index(IndexRequirementId{plan.indexes().size()})); }, "unknown_index");

  storage::ReferencePlanStorage moved(std::move(state));
  moved.check_invariants();
  auto* same_storage = &moved;
  moved = std::move(*same_storage);
  moved.check_invariants();
}

bool same_identity(const io::QueryIdentity& left, const io::QueryIdentity& right) {
  return left.canonical == right.canonical && left.semantic_sha256 == right.semantic_sha256 &&
      left.output_contract_sha256 == right.output_contract_sha256 && left.cost_inputs_sha256 == right.cost_inputs_sha256 &&
      left.plan_cache_sha256 == right.plan_cache_sha256 && left.occurrence_order == right.occurrence_order &&
      left.variable_order == right.variable_order && left.work == right.work;
}
frontend::NormalizedSql normalized_self_join() {
  const Catalog source{23, {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"flag", ScalarType::boolean}}}}};
  const std::string sql = "SELECT DISTINCT l.x, l.y, q.y AS z, l.x AS again "
      "FROM r l JOIN r q ON l.y=q.x WHERE l.flag IS TRUE";
  const auto bound = frontend::bind_sql(sql, source);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  return std::get<frontend::NormalizedSql>(std::move(normalized));
}
FreeConnexTree normalized_self_join_tree(const Query& query) {
  check(query.variables.size() == 3 && query.atoms.size() == 2, "normalized self-join has three core variables and two aliases");
  check(query.atoms[0].terms.size() == 2 && std::get<VariableId>(query.atoms[0].terms[0]) == VariableId{0} &&
        std::get<VariableId>(query.atoms[0].terms[1]) == VariableId{1} &&
        query.atoms[1].terms.size() == 2 && std::get<VariableId>(query.atoms[1].terms[0]) == VariableId{1} &&
        std::get<VariableId>(query.atoms[1].terms[1]) == VariableId{2},
        "normalized core scopes match the handwritten alias join");
  check(query.head.size() == 4 && query.head[0].variable == VariableId{0} && query.head[1].variable == VariableId{1} &&
        query.head[2].variable == VariableId{2} && query.head[3].variable == VariableId{0},
        "normalized output preserves order and the repeated first variable");
  return {NodeId{0}, {
      {"join-key", NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left-alias", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"right-alias", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
}

void normalized_replay_identity_and_ownership() {
  auto source_program = normalized_self_join();
  const auto source_text = source_program.binding.source;
  const auto program_json = io::write_sql_normalization(source_program).dump();
  const auto expected_identity = io::query_identity(source_program);
  const auto tree = normalized_self_join_tree(source_program.core);
  auto plan = planner::lower_normalized(source_program, tree);
  check(plan.normalized() && plan.normalized()->schema_version == 2 && plan.validation().valid &&
        plan.route() == PhysicalRoute::tree, "normalized lowering owns a replayed v2 source and valid tree");
  check(plan.source_catalog().version == 23 && plan.source_catalog().tables.size() == 1 &&
        plan.source_catalog().tables[0].name == "r", "normalized plan retains the original physical source catalog");
  check(plan.base_routes() == std::vector<std::vector<OccurrenceId>>{{OccurrenceId{0}, OccurrenceId{1}}},
        "both SQL aliases route from the original physical base in occurrence order");
  check(plan.inputs().size() == 2 && plan.inputs()[0].base == TableId{0} && plan.inputs()[1].base == TableId{0} &&
        plan.inputs()[0].logical_table == TableId{0} && plan.inputs()[1].logical_table == TableId{1},
        "alias inputs retain original base IDs and distinct normalized logical relations");
  check(plan.identity().canonical == expected_identity.canonical && same_identity(plan.identity(), expected_identity),
        "physical plan exposes the complete F05 canonical identity, digests, and ID maps");
  check(plan.physical_sha256().size() == 64, "physical instruction binding has a SHA-256 digest");
  check(plan.nodes().size() == 3 && plan.nodes()[0].kind == NodeKind::generalized &&
        plan.nodes()[1].occurrence == OccurrenceId{0} && plan.nodes()[2].occurrence == OccurrenceId{1},
        "lowering preserves the manually supplied generalized join-key root and alias leaves");

  const auto left_row = plan.adapt_input(OccurrenceId{0}, Row{n(10), n(20), Value{true}});
  const auto right_row = plan.adapt_input(OccurrenceId{1}, Row{n(20), n(30), Value{false}});
  check(left_row && left_row->values() == Row{n(10), n(20)}, "local TRUE flag predicate passes and emits only the left core scope");
  check(right_row && right_row->values() == Row{n(20), n(30)}, "second alias has no inherited left-alias predicate");
  check(!plan.adapt_input(OccurrenceId{0}, Row{n(10), n(20), Value{false}}), "local FALSE flag predicate filters only its own alias");

  const std::vector<storage::Tuple> assignments{
      plan.relations().at(plan.enumeration().steps[0].relation.value).layout.tuple({n(20)}),
      plan.relations().at(plan.enumeration().steps[1].relation.value).layout.tuple({n(10), n(20)}),
      plan.relations().at(plan.enumeration().steps[2].relation.value).layout.tuple({n(20), n(30)})};
  check(plan.assemble_result(assignments).values() == Row{n(10), n(20), n(30), n(10)},
        "assembly uses explicit assignment slots and repeats the original ordered output");
  auto inconsistent = assignments;
  inconsistent[2] = plan.relations().at(plan.enumeration().steps[2].relation.value).layout.tuple({n(99), n(30)});
  error([&] { static_cast<void>(plan.assemble_result(inconsistent)); }, "invalid_assignment");

  const auto guarantee = plan.guarantee();
  check(guarantee.execution_status == "lowered_not_started" && guarantee.state_bound == "runtime_not_implemented" &&
        guarantee.maintenance_bound == "runtime_not_implemented" && guarantee.cursor_delay_bound == "runtime_not_implemented",
        "guarantees describe a compiled plan without claiming runtime maintenance or cursor bounds");

  auto forged_program = source_program;
  forged_program.core.head[0].alias = "forged-output-label";
  error([&] { static_cast<void>(planner::lower_normalized(forged_program, tree)); }, "invalid_document");

  auto copy = plan;
  source_program.binding.source = "overwritten source buffer";
  source_program.binding.expressions.clear();
  source_program.core.atoms.clear();
  source_program.adapters.clear();
  check(plan.normalized()->binding.source == source_text &&
        io::write_sql_normalization(*plan.normalized()).dump() == program_json,
        "plan owns the original SQL source, AST, core, and adapter buffers after caller mutation");
  auto moved = std::move(copy);
  error([&] { static_cast<void>(copy.route()); }, "invalid_physical_plan");
  check(moved.normalized()->binding.source == source_text && moved.identity().canonical == expected_identity.canonical,
        "copy and move preserve the plan-owned normalized program and identity");

  const auto encoded = io::write_physical(plan);
  const auto restored = io::read_physical(encoded.dump());
  check(io::write_physical(restored).dump() == encoded.dump(), "normalized physical serialization replays byte-for-byte");
  check(!plan.layouts().empty() && plan.layouts()[0].same_descriptor(restored.layouts()[0]) &&
        !plan.layouts()[0].same_token(restored.layouts()[0]), "serialized descriptors rebuild with independent runtime layout tokens");
}

void physical_options_and_replay_boundaries() {
  const auto fixture = direct_fixture();
  const auto baseline = planner::lower_tree(fixture.catalog, fixture.query, fixture.tree);
  check(baseline.work() > 1 && baseline.identity().work > 0, "lowering and identity report completed abstract work counts");

  PhysicalOptions exact;
  exact.limits.work_limit = baseline.work();
  exact.limits.identity.work_limit = baseline.identity().work;
  const auto exact_plan = planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, exact);
  check(exact_plan.work() == baseline.work(), "stored lowering and identity work limits admit their exact measured boundary");
  exact.limits.work_limit = baseline.work() - 1;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, exact)); }, "resource_limit");
  exact.limits.work_limit = baseline.work();
  exact.limits.identity.work_limit = baseline.identity().work - 1;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, exact)); }, "resource_limit");
  exact.limits.identity.work_limit = 0;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, exact)); }, "resource_limit");

  PhysicalOptions producer;
  producer.policy = {"exact-nonnull-v1", "caller-planner-v7", "caller-optimization-v4", "caller-cost-v3"};
  producer.limits.work_limit.reset();
  producer.limits.identity.work_limit.reset();
  PhysicalLimits host;
  host.work_limit = baseline.work();
  host.identity.work_limit = baseline.identity().work;
  const auto host_limited = planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, producer, host);
  check(!host_limited.options().limits.work_limit && !host_limited.options().limits.identity.work_limit &&
        host_limited.options().policy.planner == "caller-planner-v7" &&
        host_limited.options().policy.optimization == "caller-optimization-v4" &&
        host_limited.options().policy.cost_model == "caller-cost-v3",
        "host caps bound compilation without rewriting producer limits or versioned policy");
  host.work_limit = baseline.work() - 1;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, producer, host)); }, "resource_limit");
  host.work_limit.reset();
  host.identity.work_limit = baseline.identity().work - 1;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree, producer, host)); }, "resource_limit");

  const auto encoded = io::write_physical(host_limited);
  io::PhysicalReadLimits import_limits;
  import_limits.lowering.work_limit = baseline.work();
  import_limits.lowering.identity.work_limit = baseline.identity().work;
  const auto imported = io::read_physical(encoded.dump(), import_limits);
  check(!imported.options().limits.work_limit && imported.options().policy.planner == "caller-planner-v7",
        "import host caps do not replace serialized producer options");
  import_limits.lowering.identity.work_limit = baseline.identity().work - 1;
  error([&] { static_cast<void>(io::read_physical(encoded.dump(), import_limits)); }, "resource_limit");

  const auto options_json = io::write_physical_options(producer);
  const auto options_copy = io::read_physical_options(options_json.dump());
  check(!options_copy.limits.work_limit && !options_copy.limits.identity.work_limit &&
        options_copy.policy.planner == producer.policy.planner && options_copy.policy.cost_model == producer.policy.cost_model,
        "physical producer options round trip with independent unlimited counters");
  auto malformed = options_json;
  malformed["schema_version"] = 2;
  error([&] { static_cast<void>(io::read_physical_options(malformed.dump())); }, "unsupported_version");
  malformed = options_json;
  malformed["policy"]["arithmetic"] = "floating-point";
  error([&] { static_cast<void>(io::read_physical_options(malformed.dump())); }, "invalid_policy");
  malformed = options_json;
  malformed["policy"]["planner"] = "";
  error([&] { static_cast<void>(io::read_physical_options(malformed.dump())); }, "invalid_policy");
}

void physical_artifact_rejects_corruption() {
  const auto fixture = direct_fixture();
  const auto encoded = io::write_physical(planner::lower_tree(fixture.catalog, fixture.query, fixture.tree));
  const auto reject_binding = [&](const std::function<void(Json&)>& change) {
    auto changed = encoded;
    change(changed);
    error([&] { static_cast<void>(io::read_physical(changed.dump())); }, "physical_binding");
  };
  reject_binding([](Json& value) { value["inputs"][0]["projection"]["fields"][0] = 999; });
  reject_binding([](Json& value) { value["layouts"][0]["fields"][0]["type"] = "string"; });
  reject_binding([](Json& value) { value["work"] = value["work"].get<std::uint64_t>() + 1; });
  reject_binding([](Json& value) { value["binding"]["identity"]["semantic_sha256"] = std::string(64, '0'); });
  reject_binding([](Json& value) { value["binding"]["identity"]["plan_cache_sha256"] = std::string(64, '0'); });
  reject_binding([](Json& value) { value["binding"]["physical_sha256"] = std::string(64, '0'); });
  reject_binding([](Json& value) { value["guarantee"]["execution_status"] = "maintenance_available"; });
  reject_binding([](Json& value) { value["guarantee"]["cursor_delay_bound"] = "constant"; });
  reject_binding([](Json& value) { value["nodes"][0]["scope"] = Json::array({99}); });
  reject_binding([](Json& value) { value["verification"]["valid"] = false; });

  auto unknown = encoded;
  unknown["future_mandatory_field"] = true;
  error([&] { static_cast<void>(io::read_physical(unknown.dump())); }, "invalid_document");
  auto wrong_version = encoded;
  wrong_version["schema_version"] = 999;
  error([&] { static_cast<void>(io::read_physical(wrong_version.dump())); }, "unsupported_version");
  error([&] { static_cast<void>(io::read_physical("{\"schema_version\":1,\"schema_version\":1}")); }, "invalid_document");
}

void tree_validation_and_legacy_grounding(const std::filesystem::path& root) {
  const auto fixture = direct_fixture();
  auto invalid_tree = fixture.tree;
  invalid_tree.nodes[0].scope.clear();
  auto caller_report = planner::validate_tree(fixture.catalog, fixture.query, invalid_tree);
  check(!caller_report.valid, "invalid fixture produces a failed caller-side report");
  caller_report.valid = true;
  error([&] { static_cast<void>(planner::lower_tree(fixture.catalog, fixture.query, invalid_tree)); }, "invalid_plan");

  const auto old = io::read_sql_normalization(read_file(root / "tests/frontend/schema/normalized-v1-fixed-head.json"));
  check(old.schema_version == 1 && old.core.head.size() == 2 && old.core.variables.size() == 3,
        "frozen v1 fixture retains its original endpoint head geometry during replay");
  const auto grounded = io::upgrade_sql_normalization(old, 2);
  check(grounded.schema_version == 2 && grounded.core.head.size() == 1 && grounded.core.variables.size() == 2 &&
        grounded.adapters[0].constant_columns.size() == 1 && grounded.outputs.size() == 2 &&
        std::holds_alternative<frontend::ConstantOutput>(grounded.outputs[0].value),
        "v1 fixed-head equality grounds the constant output before tree validation");

  FreeConnexTree stale_v1_tree{NodeId{0}, {
      {"old-r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
      {"old-s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  error([&] { static_cast<void>(planner::lower_normalized(old, stale_v1_tree)); }, "invalid_plan");
  error([&] { static_cast<void>(planner::lower_normalized(old, FreeConnexTree{})); }, "invalid_plan");

  const FreeConnexTree grounded_tree{NodeId{0}, {
      {"right-grounded", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 1, {}},
      {"left-grounded", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  const auto plan = planner::lower_normalized(old, grounded_tree);
  check(plan.normalized()->schema_version == 2 && plan.validation().valid && plan.validation().native_height == 2 &&
        plan.inputs()[0].base == TableId{0} && plan.inputs()[1].base == TableId{1},
        "a caller-supplied tree over grounded native scopes lowers the frozen legacy program");
  const auto grounded_row = plan.adapt_input(OccurrenceId{0}, Row{n(1), n(7)});
  check(grounded_row && grounded_row->values() == Row{n(7)} &&
        !plan.adapt_input(OccurrenceId{0}, Row{n(2), n(7)}), "grounded constant guard is applied to original physical rows");
}

}  // namespace

int main(int argc, char** argv) {
  try {
    check(argc == 2, "usage: crown_physical_api_test REPOSITORY");
    direct_inputs_and_result_assembly();
    native_child_keys_and_storage();
    normalized_replay_identity_and_ownership();
    physical_options_and_replay_boundaries();
    physical_artifact_rejects_corruption();
    tree_validation_and_legacy_grounding(argv[1]);
    std::cout << "physical API construction, ownership, and replay checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
