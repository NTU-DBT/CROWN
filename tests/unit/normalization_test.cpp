#include "crown/frontend/adapter.hpp"
#include "crown/api/error.hpp"
#include "crown/io/normalization.hpp"
#include "evaluator.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {
using namespace crown;
using namespace crown::frontend;
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }
Catalog schema() {
  return {9,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"payload",ScalarType::string}}},
      {"s",{{"x",ScalarType::int64},{"z",ScalarType::int64}}},
      {"zero",{}}, {"flags",{{"f",ScalarType::boolean}}},
      {"money",{{"a",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}},
          {"b",ScalarType::decimal,false,Collation::binary,DecimalSpec{7,3}}, {"day",ScalarType::date}}}}};
}
SqlNormalizeResult normalize(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
  const auto binding = bind_sql(sql,catalog,bind_options);
  if (const auto* failure = std::get_if<BindingDiagnostic>(&binding)) return *failure;
  return normalize_sql(std::get<BoundSql>(binding),options);
}
NormalizedSql accepted(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
  auto result = normalize(sql,catalog,options,bind_options);
  if (const auto* failure = std::get_if<BindingDiagnostic>(&result)) throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  return std::get<NormalizedSql>(std::move(result));
}
BindingDiagnostic rejected(std::string_view sql, const Catalog& catalog, std::string_view code, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
  const auto result = normalize(sql,catalog,options,bind_options);
  check(std::holds_alternative<BindingDiagnostic>(result),"expected rejection: " + std::string(code));
  const auto& failure = std::get<BindingDiagnostic>(result);
  check(failure.diagnostic.code == code,"unexpected rejection: " + failure.diagnostic.code + ", expected " + std::string(code));
  return failure;
}
void error(const std::function<void()>& work, std::string_view code) {
  try { work(); } catch (const Error& failure) { check(failure.code() == code,"unexpected exception code: " + failure.code()); return; }
  throw std::runtime_error("expected exception: " + std::string(code));
}
Relation snapshot(const AdapterState& state) {
  const auto& query = state.query();
  return map_sql_result(query,reference::evaluate(query.core_catalog,query.core,state.logical()));
}
Database empty(const Catalog& catalog) { return {std::vector<Relation>(catalog.tables.size())}; }

void independent_cq_equivalence() {
  const auto catalog = schema();
  auto data = empty(catalog);
  data.tables[0] = {{n(1),n(1),s("keep")},{n(1),n(9),s("keep")},{n(2),n(2),s("skip")},{n(3),n(3),s("keep")}};
  data.tables[1] = {{n(1),n(7)},{n(3),n(8)}};
  const Query manual{{{"x",ScalarType::int64},{"z",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{0},Value{s("keep")}}},
       {"s",TableId{1},{VariableId{0},VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"z"},{VariableId{0},"again"}},false};
  const auto plan = accepted("SELECT DISTINCT r.x,s.z,r.x AS again FROM r JOIN s USING(x) WHERE r.x=r.y AND r.payload='keep'",catalog);
  AdapterState state(plan,data);
  check(snapshot(state) == reference::evaluate(catalog,manual,data),"SQL matches independently handwritten repeated-variable/constant CQ");
  check(snapshot(state) == Relation{{n(1),n(7),n(1)},{n(3),n(8),n(3)}},"manual rows agree with CQ");
  check(!plan.adapters[0].equal_columns.empty() && plan.adapters[0].column_classes[0] == plan.adapters[0].column_classes[1],"same-atom equality remains an input constraint");
  check(plan.core.atoms.size() == 2 && plan.base_routes[0] == std::vector<OccurrenceId>{{0}},"physical occurrence routes retained");

  const auto scopes = accepted("SELECT DISTINCT l.x FROM r l JOIN r q ON l.x=q.x JOIN s ON q.x=s.x",catalog);
  check(scopes.core.atoms.size() == 3 && scopes.adapters.size() == 3,"contained and repeated mutable scopes never remove atoms");
  check(scopes.base_routes[0] == std::vector<OccurrenceId>{{0},{1}},"same base routes to separate aliases");
  const auto hidden = accepted("SELECT DISTINCT j.k,x.x FROM (r x JOIN s y ON x.x=y.x) j(k,a,b,c,d) CROSS JOIN r x",catalog);
  check(hidden.binding.occurrences[0].alias == hidden.binding.occurrences[2].alias && hidden.core.atoms[0].occurrence != hidden.core.atoms[2].occurrence,
        "legal reuse of a hidden SQL alias cannot collide in core occurrence IDs");
  auto mutable_data = empty(catalog); mutable_data.tables[0] = {{n(1),n(2),s("a")}};
  AdapterState missing(scopes,mutable_data);
  check(snapshot(missing).empty(),"a missing contained mutable relation still makes the join empty");
  static_cast<void>(missing.apply({1,TableId{1},SetOperation::insert,{n(1),n(9)}}));
  check(snapshot(missing) == Relation{{n(1)}},"inserting the contained input changes the result");
}

void support_counted_projection() {
  const auto catalog = schema(); auto data = empty(catalog);
  const Row first{n(1),n(10),s("a")}, second{n(1),n(20),s("b")};
  data.tables[0] = {first,second,{n(2),n(-1),s("skip")}};
  AdapterState state(accepted("SELECT DISTINCT x FROM r WHERE y>0",catalog),data);
  check(state.supports()[0].at(Row{n(1)}) == 2 && snapshot(state) == Relation{{n(1)}},"physical rows support one projected tuple twice");
  const auto one = state.apply({1,TableId{0},SetOperation::erase,first});
  check(one.input_changed && one.occurrences[0].delta.removed.empty() && state.supports()[0].at(Row{n(1)}) == 1,"first deletion retains projected tuple");
  const auto duplicate = state.apply({2,TableId{0},SetOperation::insert,second});
  check(!duplicate.input_changed && duplicate.occurrences[0].delta.added.empty() && state.supports()[0].at(Row{n(1)}) == 1,"duplicate physical insertion is a sequence-consuming no-op");
  const auto last = state.apply({3,TableId{0},SetOperation::erase,second});
  check(last.occurrences[0].delta.removed == Relation{{n(1)}} && snapshot(state).empty(),"last support emits exactly one withdrawal");
  check(!state.apply({4,TableId{0},SetOperation::erase,second}).input_changed && state.sequence() == 4,"absent deletion is a sequence-consuming no-op");
  check(state.apply({5,TableId{0},SetOperation::insert,{n(9),n(-4),s("filter")}}).occurrences[0].delta.added.empty(),"filtered row changes physical state without logical tuple");

  auto unit_data = empty(catalog); unit_data.tables[0] = {first,second};
  AdapterState unit(accepted("SELECT EXISTS(SELECT * FROM r)",catalog),unit_data);
  check(unit.supports()[0].at(Row{}) == 2,"zero-column projection also counts physical supports");
  static_cast<void>(unit.apply({1,TableId{0},SetOperation::erase,first}));
  check(snapshot(unit) == Relation{{Value{true}}},"EXISTS survives one duplicate projection deletion");
  static_cast<void>(unit.apply({2,TableId{0},SetOperation::erase,second}));
  check(snapshot(unit) == Relation{{Value{false}}},"empty Boolean core maps to one false scalar row");
}

void self_join_and_atomic_failure() {
  const auto catalog = schema(); auto data = empty(catalog);
  const Query manual{{{"x",ScalarType::int64},{"mid",ScalarType::int64},{"y",ScalarType::int64}},
      {{"l",TableId{0},{VariableId{0},VariableId{1},Value{s("keep")}}},
       {"q",TableId{0},{VariableId{1},VariableId{2},IgnoredColumn{}}}},
      {{VariableId{0},"x"},{VariableId{2},"y"}},false};
  AdapterState state(accepted("SELECT DISTINCT l.x,q.y FROM r l JOIN r q ON l.y=q.x WHERE l.payload='keep'",catalog),data);
  reference::Session oracle(catalog,manual,data);
  const std::vector<PhysicalSetUpdate> updates{
      {1,TableId{0},SetOperation::insert,{n(1),n(1),s("keep")}},
      {2,TableId{0},SetOperation::insert,{n(1),n(2),s("keep")}},
      {3,TableId{0},SetOperation::insert,{n(2),n(3),s("keep")}},
      {4,TableId{0},SetOperation::erase,{n(1),n(1),s("keep")}},
      {5,TableId{0},SetOperation::erase,{n(2),n(3),s("keep")}}};
  for (const auto& update : updates) {
    const auto epoch = state.apply(update);
    check(epoch.occurrences.size() == 2 && epoch.occurrences[0].occurrence.value == 0 && epoch.occurrences[1].occurrence.value == 1,"stable alias fan-out order");
    check(snapshot(state) == oracle.apply(update).current,"self-join cross terms agree after each complete physical update");
  }
  const auto before = state.physical().tables; const auto logical = state.logical().tables; const auto counts = state.supports();
  error([&] { static_cast<void>(state.apply({7,TableId{0},SetOperation::insert,{n(1),n(2),s("x")}})); },"invalid_sequence");
  error([&] { static_cast<void>(state.apply({6,TableId{0},SetOperation::insert,{s("wrong"),n(2),s("x")}})); },"invalid_update");
  check(state.physical().tables == before && state.logical().tables == logical && state.supports() == counts && state.sequence() == 5,"invalid updates leave physical and every alias state unchanged");

  auto injected = accepted("SELECT DISTINCT l.x,q.x FROM r l CROSS JOIN r q",catalog);
  bool corrupted = false;
  for (const auto id : injected.adapters[1].program) {
    if (auto* column = std::get_if<BoundColumn>(&injected.binding.expressions[id.value].node)) {
      column->occurrence = OccurrenceId{0}; corrupted = true; break;
    }
  }
  check(corrupted,"failure injection targets the second alias");
  AdapterState staged(std::move(injected),empty(catalog));
  error([&] { static_cast<void>(staged.apply({1,TableId{0},SetOperation::insert,{n(1),n(1),s("keep")}})); },"normalization_contract");
  check(staged.sequence() == 0 && staged.physical().tables[0].empty() && staged.logical().tables[0].empty() && staged.supports()[0].empty(),"failure after first prepared alias publishes no partial state");

  auto constrained = catalog;
  constrained.tables[0].constraints.push_back(UniqueConstraint{"x_key",{ColumnId{0}},ConstraintStatus::enforced});
  auto unique_data = empty(constrained); unique_data.tables[0] = {{n(1),n(2),s("keep")}};
  AdapterState unique(accepted("SELECT DISTINCT l.x,q.x FROM r l,r q",constrained),unique_data);
  error([&] { static_cast<void>(unique.apply({1,TableId{0},SetOperation::insert,{n(1),n(3),s("keep")}})); },"constraint_violation");
  check(unique.sequence() == 0 && unique.physical().tables[0].size() == 1 && unique.supports()[0].at(Row{n(1)}) == 1 && unique.supports()[1].at(Row{n(1)}) == 1,"constraint failure keeps all alias counts and sequence");
}

void predicates_constants_and_nulls() {
  const auto catalog = schema(); auto data = empty(catalog);
  data.tables[0] = {{n(1),n(2),s("a")},{n(2),n(2),s("b")},{n(3),n(4),s("c")}};
  const auto local = accepted("SELECT DISTINCT x,y FROM r WHERE x=y OR x=1",catalog);
  AdapterState state(local,data);
  check(snapshot(state) == Relation{{n(1),n(2)},{n(2),n(2)}},"OR-local equality is a predicate, not an unconditional class merge");
  check(local.adapters[0].column_classes[0] != local.adapters[0].column_classes[1],"OR operands keep different variable classes");
  static_cast<void>(rejected("SELECT DISTINCT l.x FROM r l,r q WHERE l.x<q.x",catalog,"unsupported_cross_relation_predicate"));
  static_cast<void>(rejected("SELECT DISTINCT l.x FROM r l,r q WHERE l.x=q.x OR l.y=q.y",catalog,"unsupported_cross_relation_predicate"));
  static_cast<void>(rejected("SELECT DISTINCT l.x=q.x FROM r l,r q",catalog,"unsupported_cross_relation_output"));
  static_cast<void>(rejected("SELECT x FROM r",catalog,"unsupported_semantics"));
  static_cast<void>(rejected("SELECT DISTINCT NULL FROM r",catalog,"unsupported_null_output"));
  auto nullable = catalog; nullable.tables[0].columns[2].nullable = true;
  static_cast<void>(rejected("SELECT DISTINCT x FROM r",nullable,"unsupported_nullable_input"));
  check(accepted("SELECT DISTINCT x FROM s",nullable).core.atoms.size() == 1,"unused nullable catalog sources do not enter the CQ");

  const auto contradiction = accepted("SELECT DISTINCT l.x FROM r l,r q WHERE l.x=q.x AND l.x=1 AND q.x=2",catalog);
  check(contradiction.core.contradiction,"incompatible constants in one final equality class contradict");
  AdapterState none(contradiction,data); check(snapshot(none).empty(),"contradiction is constant empty");
  AdapterState null_equal(accepted("SELECT EXISTS(SELECT NULL FROM r WHERE x=NULL)",catalog),data);
  check(snapshot(null_equal) == Relation{{Value{false}}},"SQL equality to NULL never becomes ordinary value equality");
  data.tables[3] = {{Value{true}},{Value{false}}};
  AdapterState or_null(accepted("SELECT DISTINCT f FROM flags WHERE f OR NULL",catalog),data);
  check(snapshot(or_null) == Relation{{Value{true}}},"SQL OR with unknown only keeps TRUE");
  AdapterState tests(accepted("SELECT DISTINCT f,(f AND NULL) IS UNKNOWN AS unknown FROM flags WHERE NULL IS NOT TRUE",catalog),data);
  check(snapshot(tests) == Relation{{Value{false},Value{false}},{Value{true},Value{true}}},"Boolean tests and local computed outputs obey three-valued logic");
  const auto global = accepted("SELECT DISTINCT FALSE AND NULL AS v",catalog);
  AdapterState global_state(global,empty(catalog));
  check(snapshot(global_state) == Relation{{Value{false}}},"constant FALSE AND unknown resolves to non-null FALSE");
}

void seeded_self_join_updates() {
  const auto catalog = schema();
  const Query manual{{{"x",ScalarType::int64},{"mid",ScalarType::int64},{"y",ScalarType::int64}},
      {{"l",TableId{0},{VariableId{0},VariableId{1},Value{s("keep")}}},
       {"q",TableId{0},{VariableId{1},VariableId{2},IgnoredColumn{}}}},
      {{VariableId{0},"x"},{VariableId{2},"y"}},false};
  const auto plan = accepted("SELECT DISTINCT l.x,q.y FROM r l,r q WHERE l.y=q.x AND l.payload='keep'",catalog);
  for (std::uint64_t seed = 1; seed <= 12; ++seed) {
    AdapterState state(plan,empty(catalog)); reference::Session oracle(catalog,manual,empty(catalog));
    auto random = seed;
    const auto next = [&]() { random = random * 6364136223846793005ULL + 1442695040888963407ULL; return random >> 32U; };
    for (std::uint64_t sequence = 1; sequence <= 48; ++sequence) {
      const auto operation = next() % 2 == 0 ? SetOperation::insert : SetOperation::erase;
      const Row row{n(static_cast<std::int64_t>(next() % 4)),n(static_cast<std::int64_t>(next() % 4)),s(next() % 3 == 0 ? "skip" : "keep")};
      const PhysicalSetUpdate update{sequence,TableId{0},operation,row};
      const auto epoch = state.apply(update); const auto expected = oracle.apply(update);
      check(epoch.input_changed == expected.input_changed && snapshot(state) == expected.current,
          "seeded self-join physical updates differ from independent handwritten CQ at seed " + std::to_string(seed) + " sequence " + std::to_string(sequence));
    }
  }
}

void parameters_types_and_output_maps() {
  const auto catalog = schema(); auto data = empty(catalog); data.tables[0] = {{n(1),n(2),s("x")},{n(2),n(3),s("y")}};
  BindOptions types; types.parameters = {{"p",ScalarType::int64,true}};
  NormalizeOptions values; values.parameters = {Value{std::int64_t{1}}};
  AdapterState state(accepted("SELECT DISTINCT x,$1,x AS again,'fixed' AS c FROM r WHERE x=$1",catalog,values,types),data);
  check(snapshot(state) == Relation{{n(1),n(1),n(1),s("fixed")}},"parameter specialization, repeated heads and constants preserve order");
  static_cast<void>(rejected("SELECT DISTINCT x FROM r WHERE x=$1",catalog,"unbound_parameter",{},types));
  NormalizeOptions null; null.parameters = {std::nullopt};
  AdapterState empty_match(accepted("SELECT EXISTS(SELECT NULL FROM r WHERE x=$1)",catalog,null,types),data);
  check(snapshot(empty_match) == Relation{{Value{false}}},"nullable parameter participates in SQL equality before merging");
  NormalizeOptions bad; bad.parameters = {Value{true}};
  static_cast<void>(rejected("SELECT DISTINCT x FROM r WHERE x=$1",catalog,"invalid_parameter",bad,types));
  types.parameters[0].nullable = false;
  static_cast<void>(rejected("SELECT DISTINCT x FROM r WHERE x=$1",catalog,"invalid_parameter",null,types));

  data.tables[4] = {{Value{Decimal::parse("1.2")},Value{Decimal::parse("1.200")},Value{Date::parse("2024-02-29")}},
      {Value{Decimal::parse("2.5")},Value{Decimal::parse("2.501")},Value{Date::parse("2023-01-01")}}};
  AdapterState decimal(accepted("SELECT DISTINCT a,b FROM money WHERE a=b AND day>=DATE '2024-01-01'",catalog),data);
  check(snapshot(decimal) == Relation{{Value{Decimal::parse("1.2")},Value{Decimal::parse("1.2")}}},"different declared decimal scales compare exact unchanged values");
  static_cast<void>(rejected("SELECT DISTINCT a::numeric(7,3) FROM money",catalog,"unsupported_cast"));
  static_cast<void>(rejected("SELECT DISTINCT x::integer FROM r",catalog,"unsupported_cast"));
  const auto constant = accepted("SELECT DISTINCT CAST('7' AS bigint),DATE '2024-02-29',CAST('1.20' AS numeric(6,2))",catalog);
  AdapterState constant_state(constant,empty(catalog));
  check(snapshot(constant_state) == Relation{{n(7),Value{Date::parse("2024-02-29")},Value{Decimal::parse("1.2")}}},"typed constant output does not require fake input atoms");
  const auto encoded = io::write_sql_normalization(constant);
  check(encoded.at("admission_status") == "not_checked" && encoded.at("core").at("query").at("atoms").empty(),"normalization grants no structural admission");
  error([] { static_cast<void>(io::read_parameter_values(R"({"schema_version":1,"values":[1.2]})")); },"invalid_document");
  error([] { static_cast<void>(io::read_parameter_values(R"({"schema_version":1,"values":[],"extra":1})")); },"invalid_document");
  error([] { static_cast<void>(io::read_parameter_values(R"({"schema_version":2,"values":[]})")); },"unsupported_version");
  check(io::read_parameter_values(R"({"schema_version":1,"values":[null,{"decimal":"1.20"}]})").at(1) == SqlValue{Value{Decimal::parse("1.2")}},"strict parameter value codec preserves NULL boundary and canonical exact scalars");
}

void nullary_wide_ownership_and_limits() {
  const auto catalog = schema(); auto data = empty(catalog);
  data.tables[2] = {Row{}}; data.tables[0] = {{n(1),n(1),s("a")}};
  AdapterState zero(accepted("SELECT DISTINCT * FROM zero",catalog),data);
  check(snapshot(zero) == Relation{Row{}},"zero-arity source is one nullary tuple");
  AdapterState around(accepted("SELECT DISTINCT r.x FROM zero a CROSS JOIN r CROSS JOIN zero b WHERE r.x=r.y",catalog),data);
  check(snapshot(around) == Relation{{n(1)}} && around.query().adapters[1].non_null_columns == std::vector<ColumnId>{{0},{1}},"empty-column occurrences keep physical offsets and equality checks distinct");
  AdapterState empty_exists(accepted("SELECT EXISTS(SELECT FROM zero WHERE FALSE)",catalog),data);
  check(snapshot(empty_exists) == Relation{{Value{false}}},"EXISTS wrapper returns false on empty nullary core");
  AdapterState no_from(accepted("SELECT EXISTS(SELECT NULL)",catalog),empty(catalog));
  check(snapshot(no_from) == Relation{{Value{true}}},"no-FROM inner query has one assignment even with ignored NULL target");

  Catalog wide{1,{{"wide",{}}}}; Row row;
  for (std::size_t i = 0; i < 70; ++i) { wide.tables[0].columns.push_back({"c" + std::to_string(i),ScalarType::int64}); row.push_back(n(static_cast<std::int64_t>(i))); }
  auto wide_data = empty(wide); wide_data.tables[0].insert(row);
  AdapterState wide_state(accepted("SELECT DISTINCT * FROM wide",wide),wide_data);
  check(snapshot(wide_state) == Relation{row} && wide_state.query().core.variables.size() == 70,"no fixed column-bitmask cap");

  auto owned_catalog = catalog; auto binding_result = bind_sql("SELECT DISTINCT x FROM r",owned_catalog);
  auto& bound = std::get<BoundSql>(binding_result); auto result = normalize_sql(bound); auto plan = std::get<NormalizedSql>(result);
  bound.source.clear(); bound.catalog.tables.clear(); owned_catalog.tables.clear();
  auto copied = plan; auto moved = std::move(copied);
  AdapterState owned(std::move(moved),data);
  check(snapshot(owned) == Relation{{n(1)}} && !plan.binding.source.empty(),"normalized programs and copies own source, catalog, IR and specialization");
  NormalizeOptions zero_work; zero_work.limits.work_limit = 0;
  static_cast<void>(rejected("SELECT DISTINCT x FROM r",catalog,"resource_limit",zero_work));
  const std::string unicode = "SELECT DISTINCT l.x AS \"雪\" FROM r l,r q WHERE l.x<q.x";
  const auto failure = rejected(unicode,catalog,"unsupported_cross_relation_predicate");
  check(failure.phase == "normalization" && failure.diagnostic.byte_offset == unicode.find('<') && failure.diagnostic.character_position == unicode.find('<') - 1,"normalization diagnostics retain Unicode byte/code-point distinction");
}
}  // namespace

int main() {
  try {
    independent_cq_equivalence(); support_counted_projection(); self_join_and_atomic_failure();
    predicates_constants_and_nulls(); seeded_self_join_updates(); parameters_types_and_output_maps(); nullary_wide_ownership_and_limits();
    std::cout << "SQL normalization and support-counted adapter checks passed\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
