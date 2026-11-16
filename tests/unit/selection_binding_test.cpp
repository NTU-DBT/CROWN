#include "selection_fixture.hpp"
#include "selection_detail.hpp"
#include <functional>
#include <iostream>
#include <limits>

namespace {
using namespace c05_test; namespace sd = ps::detail;
std::string word(std::uint64_t value) {
  std::string out(8, '\0');
  for (std::size_t i = 8; i != 0; --i) { out[i - 1] = static_cast<char>(value % 256); value /= 256; }
  return out;
}
std::string text(std::string_view value) { return std::string("S") + word(value.size()) + std::string(value); }
std::string scalar_expected(unsigned tag, const std::string& value) {
  return std::string("CROWN-SELECTION-SCALAR;1;R") + text("value") + 'U' + word(tag) + value;
}
template<class ValueType, class Encode, class Change>
void changed(const ValueType& input, Encode encode, Change change, std::size_t& count) {
  auto copy = input; change(copy);
  check(encode(copy) != encode(input), "C05 omitted a record field from exact byte binding"); ++count;
}
auto program_fixture() {
  frontend::NormalizedSql n;
  n.binding.source = "diagnostic record, not an admitted SQL program";
  n.binding.catalog = c02_test::fixture().catalog;
  const frontend::SqlType decimal{frontend::SqlKind::decimal, true, DecimalSpec{38, 2}};
  n.binding.parameters = {decimal};
  n.binding.inner_semantics = frontend::SqlSemantics::set;
  n.binding.occurrences = {{TableId{0}, "a", {"x"}, 3, true}};
  n.binding.expressions = {{decimal, frontend::BoundColumn{OccurrenceId{0}, ColumnId{0}}, 4},
      {decimal, frontend::BoundLiteral{Value{Decimal::parse("1.23")}}, 5},
      {decimal, frontend::BoundParameter{1}, 6},
      {decimal, frontend::BoundOperation{frontend::SqlOperator::equal, {frontend::ExpressionId{0}, frontend::ExpressionId{1}}}, 7}};
  n.binding.predicates = {frontend::ExpressionId{3}};
  n.binding.outputs = {{"out", frontend::ExpressionId{0}}};
  n.parameters = {Value{std::int64_t{1}}}; n.constants = {std::nullopt, Value{Decimal::parse("1.23")}};
  n.core_catalog = c02_test::fixture().catalog; n.core = c02_test::fixture().query;
  frontend::OccurrenceAdapter a;
  a.occurrence = OccurrenceId{0}; a.base = TableId{0}; a.predicates = {frontend::ExpressionId{3}};
  a.non_null_columns = {ColumnId{0}}; a.equal_columns = {{ColumnId{0}, ColumnId{1}}};
  a.column_classes = {VariableId{0}, std::nullopt}; a.projection = {{VariableId{0}, frontend::ExpressionId{0}}};
  a.program = {frontend::ExpressionId{0}, frontend::ExpressionId{1}};
  a.constant_columns = {{ColumnId{1}, Value{Decimal::parse("1.23")}}};
  n.adapters = {a}; n.base_routes = {{OccurrenceId{0}}, {}};
  n.outputs = {{"out", decimal, frontend::CoreOutput{0}}, {"constant", decimal, frontend::ConstantOutput{Value{Decimal::parse("1.23")}}}};
  return n;
}
}
int main() { try {
  using namespace c05_test; std::size_t mutations = 0;
  const auto scalar = [](const Value& value) { sd::Budget b(pr::Limits{}); return sd::scalar_binding_record(value, b); };
  check(scalar(Value{std::numeric_limits<std::int64_t>::min()}) == scalar_expected(0, "I" + word(0x8000000000000000ULL)), "C05 signed-min framing");
  check(scalar(Value{std::numeric_limits<std::int64_t>::max()}) == scalar_expected(0, "I" + word(0x7fffffffffffffffULL)), "C05 signed-max framing");
  const std::string raw{"\0\x7f\x80\xff", 4};
  check(scalar(Value{raw}) == scalar_expected(1, text(raw)), "C05 NUL/high-byte framing");
  check(scalar(Value{false}) == scalar_expected(2, std::string("B\0", 2)) &&
      scalar(Value{true}) == scalar_expected(2, std::string("B\1", 2)), "C05 Boolean framing");
  check(scalar(Value{Date::parse("1969-12-31")}) == scalar_expected(3, "I" + word(UINT64_MAX)), "C05 Date tag/day framing");
  check(scalar(Value{Decimal::parse("+001.2300")}) == scalar_expected(4, text("1.23")) &&
      scalar(Value{Decimal::parse("-0.000")}) == scalar_expected(4, text("0")), "C05 canonical Decimal framing");
  check(scalar(Value{Decimal::parse("-99999999999999999999999999999999999999")}) ==
      scalar_expected(4, text("-99999999999999999999999999999999999999")), "C05 Decimal coefficient boundary");
  const auto tree_bytes = [](const FreeConnexTree& value) { sd::Budget b(pr::Limits{}); return sd::tree_binding_record(value, b); };
  check(tree_bytes(FreeConnexTree{}) == std::string("CROWN-SELECTION-TREE;1;R") + text("raw-tree") +
      std::string("P\0", 2) + 'A' + word(0) + std::string("P\0P\0", 4), "C05 empty-tree framing");
  FreeConnexTree tree{NodeId{0}, {{"root", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, VariableSet{VariableId{0}}},
      {"leaf", NodeKind::native, {VariableId{0}}, {}, 1, {}}}, std::vector<NodeId>{NodeId{0}, NodeId{1}}, 2};
#define TREE_CHANGE(expression) changed(tree, tree_bytes, [&](auto& x) { expression; }, mutations)
  TREE_CHANGE(x.root = NodeId{1}); TREE_CHANGE(x.root.reset()); TREE_CHANGE(x.nodes[0].id += raw);
  TREE_CHANGE(x.nodes[0].kind = NodeKind::generalized); TREE_CHANGE(x.nodes[0].scope.insert(VariableId{1}));
  TREE_CHANGE(x.nodes[0].children.clear()); TREE_CHANGE(x.nodes[0].occurrence.reset());
  TREE_CHANGE(x.nodes[0].claimed_separator.reset()); TREE_CHANGE(x.claimed_connex.reset());
  TREE_CHANGE(std::reverse(x.claimed_connex->begin(), x.claimed_connex->end()));
  TREE_CHANGE(x.claimed_native_height.reset()); TREE_CHANGE(std::reverse(x.nodes.begin(), x.nodes.end()));
#undef TREE_CHANGE
  const auto program = program_fixture();
  const auto program_bytes = [](const frontend::NormalizedSql& value) { sd::Budget b(pr::Limits{}); return sd::program_binding_record(value, b); };
#define PROGRAM_CHANGE(expression) changed(program, program_bytes, [](auto& x) { expression; }, mutations)
  PROGRAM_CHANGE(x.binding.source += " "); PROGRAM_CHANGE(++x.binding.catalog.version);
  PROGRAM_CHANGE(x.binding.parameters[0].kind = frontend::SqlKind::int64); PROGRAM_CHANGE(x.binding.parameters[0].nullable = false);
  PROGRAM_CHANGE(++x.binding.parameters[0].decimal->scale); PROGRAM_CHANGE(x.binding.inner_semantics.reset());
  PROGRAM_CHANGE(x.binding.semantics = frontend::SqlSemantics::set); PROGRAM_CHANGE(x.binding.wrapper = frontend::SqlWrapper::exists);
  PROGRAM_CHANGE(x.binding.wrapper_alias += "a"); PROGRAM_CHANGE(x.binding.occurrences[0].table = TableId{1});
  PROGRAM_CHANGE(x.binding.occurrences[0].alias += "b"); PROGRAM_CHANGE(x.binding.occurrences[0].column_names[0] += "c");
  PROGRAM_CHANGE(x.binding.occurrences[0].location.reset()); PROGRAM_CHANGE(x.binding.occurrences[0].include_descendants = false);
  PROGRAM_CHANGE(x.binding.expressions[0].type.nullable = false); PROGRAM_CHANGE(x.binding.expressions[0].location.reset());
  PROGRAM_CHANGE(std::get<frontend::BoundColumn>(x.binding.expressions[0].node).occurrence = OccurrenceId{1});
  PROGRAM_CHANGE(std::get<frontend::BoundColumn>(x.binding.expressions[0].node).column = ColumnId{1});
  PROGRAM_CHANGE(std::get<frontend::BoundLiteral>(x.binding.expressions[1].node).value.reset());
  PROGRAM_CHANGE(++std::get<frontend::BoundParameter>(x.binding.expressions[2].node).number);
  PROGRAM_CHANGE(std::get<frontend::BoundOperation>(x.binding.expressions[3].node).operation = frontend::SqlOperator::not_equal);
  PROGRAM_CHANGE(std::reverse(std::get<frontend::BoundOperation>(x.binding.expressions[3].node).arguments.begin(),
      std::get<frontend::BoundOperation>(x.binding.expressions[3].node).arguments.end()));
  PROGRAM_CHANGE(x.binding.predicates.clear()); PROGRAM_CHANGE(x.binding.outputs[0].name += "d");
  PROGRAM_CHANGE(x.binding.outputs[0].expression = frontend::ExpressionId{1}); PROGRAM_CHANGE(x.binding.limits.work_limit.reset());
  PROGRAM_CHANGE(++x.binding.limits.expression_limit); PROGRAM_CHANGE(++x.binding.limits.recursion_limit); PROGRAM_CHANGE(++x.binding.work);
  PROGRAM_CHANGE(x.parameters[0].reset()); PROGRAM_CHANGE(x.constants[0] = Value{std::int64_t{0}});
  PROGRAM_CHANGE(++x.core_catalog.version); PROGRAM_CHANGE(x.core.head.push_back({VariableId{0}, "head"}));
  PROGRAM_CHANGE(x.adapters[0].occurrence = OccurrenceId{1}); PROGRAM_CHANGE(x.adapters[0].base = TableId{1});
  PROGRAM_CHANGE(x.adapters[0].predicates.clear()); PROGRAM_CHANGE(x.adapters[0].non_null_columns.clear());
  PROGRAM_CHANGE(x.adapters[0].equal_columns[0].left = ColumnId{1}); PROGRAM_CHANGE(x.adapters[0].equal_columns[0].right = ColumnId{0});
  PROGRAM_CHANGE(x.adapters[0].column_classes[0].reset()); PROGRAM_CHANGE(x.adapters[0].projection[0].variable = VariableId{1});
  PROGRAM_CHANGE(x.adapters[0].projection[0].expression = frontend::ExpressionId{1}); PROGRAM_CHANGE(std::reverse(x.adapters[0].program.begin(), x.adapters[0].program.end()));
  PROGRAM_CHANGE(x.adapters[0].constant_columns[0].column = ColumnId{0}); PROGRAM_CHANGE(x.adapters[0].constant_columns[0].value = std::int64_t{1});
  PROGRAM_CHANGE(std::reverse(x.base_routes.begin(), x.base_routes.end())); PROGRAM_CHANGE(x.outputs[0].name += "e");
  PROGRAM_CHANGE(x.outputs[0].type.decimal.reset()); PROGRAM_CHANGE(std::get<frontend::CoreOutput>(x.outputs[0].value).column = 1);
  PROGRAM_CHANGE(std::get<frontend::ConstantOutput>(x.outputs[1].value).value = std::int64_t{1});
  PROGRAM_CHANGE(std::reverse(x.outputs.begin(), x.outputs.end())); PROGRAM_CHANGE(x.limits.work_limit.reset());
  PROGRAM_CHANGE(++x.work); PROGRAM_CHANGE(++x.schema_version);
#undef PROGRAM_CHANGE
  // The complete Catalog/Query codec is the unchanged P07 v2 nested record.
  auto core = c02_test::fixture(); core.catalog.tables[0].constraints = {
      UniqueConstraint{"u", {ColumnId{0}}, ConstraintStatus::untrusted},
      ForeignKeyConstraint{"f", {ColumnId{0}}, TableId{2}, {ColumnId{0}}, ConstraintStatus::untrusted}};
  core.catalog.tables[0].key_hints = {{{ColumnId{0}}, "hint"}};
  core.catalog.tables[0].statistics = {3, {{{ColumnId{0}}, 2}}};
  core.query.head = {{VariableId{0}, "one"}, {VariableId{0}, "two"}};
  const auto core_bytes = [](const Fixture& x) { sd::Budget b(pr::Limits{}); return sd::core_binding_record(x.catalog, x.query, b); };
#define CORE_CHANGE(expression) changed(core, core_bytes, [](auto& x) { expression; }, mutations)
  CORE_CHANGE(++x.catalog.version); CORE_CHANGE(++x.catalog.tables[0].source_schema_version); CORE_CHANGE(x.catalog.tables[0].name += "n");
  CORE_CHANGE(x.catalog.tables[0].columns[0].name += "c"); CORE_CHANGE(x.catalog.tables[0].columns[0].type = ScalarType::boolean);
  CORE_CHANGE(x.catalog.tables[0].columns[0].nullable = true); CORE_CHANGE((x.catalog.tables[0].columns[0].decimal = DecimalSpec{38, 2}));
  CORE_CHANGE(std::get<UniqueConstraint>(x.catalog.tables[0].constraints[0]).status = ConstraintStatus::enforced);
  CORE_CHANGE(std::get<ForeignKeyConstraint>(x.catalog.tables[0].constraints[1]).referenced_columns.push_back(ColumnId{1}));
  CORE_CHANGE(x.catalog.tables[0].statistics.row_count.reset()); CORE_CHANGE(++x.catalog.tables[0].statistics.distinct_counts[0].estimate);
  CORE_CHANGE(x.catalog.tables[0].key_hints[0].reason += "h"); CORE_CHANGE(x.query.variables[0].name += "v");
  CORE_CHANGE(x.query.atoms[0].occurrence += "a"); CORE_CHANGE(x.query.atoms[0].terms[0] = IgnoredColumn{});
  changed(core, core_bytes, [](Fixture& x) {
    auto& literal = x.query.atoms[0].terms[0].emplace<Value>(std::in_place_type<std::string>);
    std::get<std::string>(literal).assign("a\0b", 3);
  }, mutations);
  CORE_CHANGE(std::reverse(x.query.head.begin(), x.query.head.end()));
  CORE_CHANGE(x.query.contradiction = true);
#undef CORE_CHANGE
  // Internal record endpoint only: these edited private data copies are never
  // passed to select, a CurrentSelection factory, or a cache installation.
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto facts = capture(snapshot, owner).inputs();
  sd::SelectionData data(facts.plan().account(),snapshot, ps::Source{ps::DirectCQ{}}, request(ps::Policy::height_only), facts);
  data.chosen = snapshot.candidate(0); data.selected = 0;
  for (std::size_t i = 0; i < snapshot.candidate_count(); ++i) data.decisions.push_back({i, ps::Eligibility::unconstrained});
  const auto full = [](const sd::SelectionData& value) { sd::Budget b(pr::Limits{}, {},value.account); return sd::cache_binding(value, sd::Origin::as_of, b); };
  const auto base = full(data);
  const auto fact_change = [&](auto change, bool distinct = true) {
    auto copied = std::make_shared<sd::rd::EvidenceData>(sd::rd::Factory::data(facts)); change(*copied);
    auto variant = data; variant.evidence = sd::rd::Factory::evidence(std::move(copied));
    check((full(variant) != base) == distinct, "C05 evidence key included/excluded wrong field"); ++mutations;
  };
#define FACT_CHANGE(expression) fact_change([](auto& x) { expression; })
  FACT_CHANGE(++x.identity.owner); FACT_CHANGE(++x.identity.epoch); FACT_CHANGE(++x.identity.interval_start);
  FACT_CHANGE(++x.identity.reset); FACT_CHANGE(++x.identity.configuration); FACT_CHANGE(++x.identity.segment); FACT_CHANGE(++x.identity.format);
  FACT_CHANGE(++x.identity.collection_mode); FACT_CHANGE(++x.identity.max_cells); FACT_CHANGE(++x.identity.period); FACT_CHANGE(++x.identity.offset);
  FACT_CHANGE(++x.identity.detail_budget); FACT_CHANGE(x.identity.pending = true); FACT_CHANGE(x.identity.reset_saturated = true);
  FACT_CHANGE(x.identity.configuration_saturated = true); FACT_CHANGE(x.identity.segment_saturated = true);
  FACT_CHANGE(x.identity.modes.delta_owner = true); FACT_CHANGE(++x.identity.modes.requested_mode); FACT_CHANGE(++x.identity.modes.resolved_mode);
  FACT_CHANGE(++x.identity.modes.requested_completion); FACT_CHANGE(++x.identity.modes.resolved_completion);
  FACT_CHANGE(++x.identity.modes.live_maintenance); FACT_CHANGE(++x.identity.modes.view);
  FACT_CHANGE(++x.weights[0].inserts); FACT_CHANGE(++x.weights[0].erases); FACT_CHANGE(++x.weights[0].changed); FACT_CHANGE(++x.weights[0].noop);
  FACT_CHANGE(++x.sources[0].rows); FACT_CHANGE(x.source_observations[0].cardinality.reset());
  FACT_CHANGE(x.source_observations[0].state = pr::CaptureState::unavailable);
  FACT_CHANGE(++x.denominator); FACT_CHANGE(++x.depth_reasons); FACT_CHANGE(++x.memory_reasons);
  FACT_CHANGE(x.accounting.state_requested = false); FACT_CHANGE(x.accounting.state = pr::CaptureState::unavailable);
  FACT_CHANGE(++x.accounting.requested_components); FACT_CHANGE(++x.accounting.returned_components);
  FACT_CHANGE(++x.accounting.state_work_limit); FACT_CHANGE(++x.accounting.state_rows_limit); FACT_CHANGE(++x.accounting.state_keys_limit);
  FACT_CHANGE(++x.accounting.state_bytes_limit); FACT_CHANGE(++x.accounting.state_projection_width); FACT_CHANGE(++x.accounting.state_heavy_keys);
  FACT_CHANGE(++x.accounting.snapshot_descriptors); FACT_CHANGE(++x.accounting.snapshot_cells); FACT_CHANGE(++x.accounting.processing_limits.work);
#undef FACT_CHANGE
  fact_change([](auto& x) { ++x.preparation.work; ++x.preparation.active_nanoseconds; ++x.accounting.state_work; }, false);
  auto operational = data; operational.cache.requested = ps::CacheUse::read_only; operational.cache.limits = ps::CacheLimits{1, 1, 1};
  check(full(operational) == base, "C05 read-only/storage options poisoned artifact equality");
  changed(data, full, [](auto& x) { ++x.request.limits.aggregate.work; }, mutations);
  changed(data, full, [](auto& x) { x.request.fallback = pr::Fallback::require_evidence; }, mutations);
  changed(data, full, [](auto& x) { x.request.constraint = ps::CapturedTupleIndexSlotLimit{ps::SelectionText("0",sd::selection_allocator<char>(x.account))}; }, mutations);
  changed(data, full, [](auto& x) { x.request.family = ps::FamilyPolicy::require_exhausted_family; }, mutations);
  changed(data, full, [](auto& x) { x.decisions[0].eligibility = ps::Eligibility::above_slot_limit; }, mutations);
  changed(data, full, [](auto& x) { ++x.fallback; }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.policy.arithmetic += "a"; }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.policy.planner += "p"; }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.policy.optimization += "o"; }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.policy.cost_model += "c"; }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.limits.work_limit.reset(); }, mutations);
  changed(data, full, [](auto& x) { std::get<ps::CapturedDirectCQ>(x.source).options.limits.identity.work_limit.reset(); }, mutations);
  sd::Budget measured(pr::Limits{}); static_cast<void>(sd::program_binding_record(program, measured));
  for (unsigned which = 0; which < 3; ++which) {
    auto limits = pr::Limits{};
    if (which == 0) limits.work = measured.usage.work;
    if (which == 1) limits.binding_key_bytes = measured.usage.binding_key_bytes;
    if (which == 2) limits.payload_bytes = measured.usage.payload_bytes;
    sd::Budget exact(limits); check(sd::program_binding_record(program, exact) == program_bytes(program), "C05 exact record cap");
    if (which == 0) --limits.work;
    if (which == 1) --limits.binding_key_bytes;
    if (which == 2) --limits.payload_bytes;
    bool stopped = false;
    try { sd::Budget small(limits); static_cast<void>(sd::program_binding_record(program, small)); }
    catch (const sd::Failure& failure) { stopped = failure.stop == ps::Stop::resource_limit; }
    catch (const sd::rd::Failure&) { stopped = true; }
    check(stopped, "C05 one-under record cap ignored");
  }
  std::cout << "C05 independent byte framing and record/key mutations=" << mutations << "; diagnostic records create no selection authority\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
