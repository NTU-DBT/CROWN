#include "crown/storage/layout.hpp"
#include "crown/io/layout.hpp"
#include "crown/api/error.hpp"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace crown;
using namespace crown::storage;
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
void error(const std::function<void()>& action,std::string_view code) {
  try { action(); } catch (const Error& failure) { check(failure.code()==code,"wrong error: "+failure.code()+", expected "+std::string(code)); return; }
  throw std::runtime_error("expected error: "+std::string(code));
}
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
void tuples_and_keys() {
  static_assert(!std::is_convertible_v<TableId,RelationId> && !std::is_convertible_v<OccurrenceId,NodeId> && !std::is_convertible_v<ColumnId,FieldId>);
  const TupleLayout source{LayoutId{1},{{ScalarType::int64},{ScalarType::string},{ScalarType::boolean},{ScalarType::date},{ScalarType::decimal,DecimalSpec{5,2}}}};
  auto tuple=source.tuple({n(1),s("1"),Value{true},Value{Date::parse("2024-02-29")},Value{Decimal::parse("1.20")}});
  const std::vector<FieldId> fields{{4},{1},{0},{4}};
  const auto target=projected_layout(LayoutId{2},source,fields);
  const Projection projection{source,target,fields};
  check(projection.apply(tuple).values()==Row{Value{Decimal::parse("1.2")},s("1"),n(1),Value{Decimal::parse("1.2")}},"composite/reordered/repeated slots preserve exact tagged values");
  const auto empty=projected_layout(LayoutId{3},source,{});
  check(Projection(source,empty,{}).apply(tuple).values().empty(),"empty keys are nullary tuples");
  check(row_hash(Row{n(1)})!=row_hash(Row{s("1")}) && row_hash(Row{Value{true}})!=row_hash(Row{n(1)}),"equal text representations retain scalar identity");
  check(tuple.hash()==row_hash(tuple.values()),"tuple hash reuses the stable exact typed value/row contract");
  const auto restored=io::read_layout(io::write_layout(source).dump());
  check(source.same_descriptor(restored) && !source.same_token(restored),"wire descriptors do not acquire another runtime token");
  error([&] { static_cast<void>(projection.apply(restored.tuple(tuple.values()))); },"layout_mismatch");
  const auto rebound=io::read_projection(io::write_projection(projection).dump(),restored,target);
  check(rebound.apply(restored.tuple(tuple.values())).values()==projection.apply(tuple).values(),"serialized programs bind to explicitly supplied immutable layouts");
  auto changed=io::write_projection(projection); changed["fields"][0]=-1;
  error([&] { static_cast<void>(io::read_projection(changed.dump(),source,target)); },"invalid_document");
  changed=io::write_projection(projection); changed["source"]["context"]["binding"]="other-query";
  error([&] { static_cast<void>(io::read_projection(changed.dump(),source,target)); },"layout_mismatch");
  auto bad=io::write_layout(source); bad["fields"][0]["nullable"]=true;
  error([&] { static_cast<void>(io::read_layout(bad.dump())); },"invalid_document");
  bad=io::write_layout(source); bad["schema_version"]=2;
  error([&] { static_cast<void>(io::read_layout(bad.dump())); },"unsupported_version");
  error([&] { static_cast<void>(source.tuple({n(1)})); },"invalid_tuple");
  auto wrong=crown::storage::export_row(tuple.values()); wrong[0]=s("1");
  error([&] { static_cast<void>(source.tuple(wrong)); },"invalid_tuple");
  const auto original=tuple.values(); auto* same_tuple=&tuple;
  tuple=std::move(*same_tuple);
  check(tuple.layout().same_token(source) && tuple.values()==original,"self-move preserves the validated layout/value invariant");
  auto copy=tuple; auto moved=std::move(copy);
  check(moved.values()==tuple.values(),"immutable tuples own copied/moved strings/scalars");
  error([&] { static_cast<void>(projection.apply(copy)); },"layout_mismatch");
}
void shared_keys_and_facts() {
  const LayoutContext context{9,"query-binding"};
  const TupleLayout left{LayoutId{1},{{ScalarType::int64,{},VariableId{0}},{ScalarType::string,{},VariableId{1}}},context};
  const TupleLayout right{LayoutId{2},{{ScalarType::string,{},VariableId{1}},{ScalarType::int64,{},VariableId{2}}},context};
  const TupleLayout key{LayoutId{3},{{ScalarType::string,{},VariableId{1}}},context};
  const Projection l{left,key,{{1}}},r{right,key,{{0}}};
  check(l.apply(left.tuple({n(7),s("match")}))==r.apply(right.tuple({s("match"),n(9)})),"different relation sources share an interoperable target key token");
  const TupleLayout repeated{LayoutId{4},{{ScalarType::int64,{},VariableId{0}},{ScalarType::int64,{},VariableId{0}}},context};
  error([&] { static_cast<void>(repeated.tuple({n(1),n(2)})); },"invalid_tuple");
  const TupleLayout anonymous{LayoutId{5},{{ScalarType::int64},{ScalarType::int64}},context};
  error([&] { static_cast<void>(Projection(anonymous,repeated,{{0},{1}})); },"invalid_projection");
  check(Projection(anonymous,repeated,{{0},{0}}).apply(anonymous.tuple({n(1),n(2)})).values()==Row{n(1),n(1)},"repeated target facts require a source equality or repeated slot");
  const TupleLayout foreign{LayoutId{1},std::vector<Field>(left.fields().begin(),left.fields().end()),{9,"other-query"}};
  error([&] { static_cast<void>(Projection(left,foreign,{{0},{1}})); },"invalid_projection");
  error([&] { static_cast<void>(Projection(left,key,{{0}})); },"invalid_projection");
  error([&] { static_cast<void>(projected_layout(LayoutId{6},left,std::vector<FieldId>{{99}})); },"invalid_projection");
  const TupleLayout fixed{LayoutId{7},{{ScalarType::decimal,DecimalSpec{3,2}}},context};
  const TupleLayout broad{LayoutId{8},{{ScalarType::decimal}},context};
  const TupleLayout wider{LayoutId{9},{{ScalarType::decimal,DecimalSpec{4,3}}},context};
  const TupleLayout narrower{LayoutId{10},{{ScalarType::decimal,DecimalSpec{3,1}}},context};
  const auto decimal=fixed.tuple({Value{Decimal::parse("9.99")}});
  check(Projection(fixed,broad,{{0}}).apply(decimal).values()==decimal.values() && Projection(fixed,wider,{{0}}).apply(decimal).values()==decimal.values(),"domain widening copies exact decimals without casts/rounding");
  error([&] { static_cast<void>(Projection(fixed,narrower,{{0}})); },"invalid_projection");
  error([&] { static_cast<void>(Projection(broad,fixed,{{0}})); },"invalid_projection");
  error([&] { static_cast<void>(fixed.tuple({Value{Decimal::parse("10")}})); },"scalar_overflow");
}
void catalog_scope_and_width() {
  Catalog catalog{12,{{"source",{{"x",ScalarType::int64},{"d",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}}},7}}};
  const auto source=table_layout(LayoutId{1},catalog,TableId{0},"bound-query");
  check(source.context().catalog_version==12 && source.origin()==LayoutOrigin{TableId{0},7},"physical source origin/version survives layout compilation");
  catalog.tables[0].columns[0].nullable=true;
  error([&] { static_cast<void>(table_layout(LayoutId{2},catalog,TableId{0})); },"unsupported_nullability");
  Query query; query.variables={{"a",ScalarType::int64},{"d",ScalarType::decimal}};
  const auto scope=scope_layout(LayoutId{3},query,std::vector<VariableId>{{1},{0},{1}});
  check(scope.fields()[0].type==ScalarType::decimal && scope.fields()[2].variable==VariableId{1},"logical scope layouts retain ordered/repeated variable IDs");
  std::vector<Field> fields; Row values; std::vector<FieldId> reversed;
  for (std::size_t i=0;i<70;++i) { fields.push_back({ScalarType::int64,{},VariableId{i}}); values.push_back(n(static_cast<std::int64_t>(i))); reversed.push_back({69-i}); }
  const TupleLayout wide{LayoutId{4},fields}; const Projection program{wide,projected_layout(LayoutId{5},wide,reversed),reversed};
  const auto result=program.apply(wide.tuple(values));
  check(result.values().size()==70 && result.values().front()==n(69) && result.values().back()==n(0),"compiled keys have no 64-column mask restriction");
}
}  // namespace
int main(int argc,char** argv) {
  try {
    if (argc==2 && std::string_view(argv[1])=="--artifacts") {
      const TupleLayout source{LayoutId{1},{{ScalarType::int64},{ScalarType::string},{ScalarType::boolean},{ScalarType::date},{ScalarType::decimal,DecimalSpec{5,2}}}};
      const std::vector<FieldId> fields{{4},{1},{0},{4}};
      const Projection projection{source,projected_layout(LayoutId{2},source,fields),fields};
      std::cout << io::Json{{"layout",io::write_layout(source)},{"projection",io::write_projection(projection)}}.dump(2) << '\n'; return 0;
    }
    check(argc==1,"usage: crown_layout_test [--artifacts]");
    tuples_and_keys(); shared_keys_and_facts(); catalog_scope_and_width(); std::cout << "typed tuple layout/projection checks passed\n";
  }
  catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; }
}
