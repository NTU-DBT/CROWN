#include "crown/runtime/fallback.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

namespace {
using namespace crown;
namespace pf=planner::fallback;
namespace fr=runtime::fallback;
std::uint64_t checks=0;
void check(bool value,const char* message) {
  if(!value)throw std::runtime_error(message);
  ++checks;
}
template<class F>void refusal(F action,std::string_view code={}) {
  bool failed=false;
  try{action();}
  catch(const Error& e){failed=true;check(code.empty()||e.code()==code,"unexpected Error category");}
  catch(const resource::MemoryFailure&){failed=true;check(code.empty(),"unexpected memory refusal");}
  catch(const storage::IndexFailure& e){failed=true;check(code.empty()||e.code()==code,"unexpected index refusal");}
  check(failed,"expected fallback refusal did not occur");
}
Row ints(std::initializer_list<std::int64_t> values) {
  Row out;for(auto v:values)out.emplace_back(v);return out;
}
template<class Range>Relation rows(const Range& values) {
  Relation out;for(const auto& t:values)check(out.insert(storage::export_row(t.values())).second,"duplicate projected result escaped");return out;
}
struct Fixture {Catalog catalog;Query query;};
Fixture triangle(std::vector<std::size_t> head={0,2},bool cyclic=true,bool self=false) {
  Fixture f;
  f.catalog.tables={{"R",{{"a",ScalarType::int64},{"b",ScalarType::int64}}},
      {"S",{{"b",ScalarType::int64},{"c",ScalarType::int64}}},
      {"T",{{"c",ScalarType::int64},{"a",ScalarType::int64}}},
      {"unused",{{"v",ScalarType::int64}}}};
  f.query.variables={{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}};
  f.query.atoms={{"left",TableId{0},{VariableId{0},VariableId{1}}},
      {"middle",TableId{self?0U:1U},{VariableId{1},VariableId{2}}}};
  if(cyclic)f.query.atoms.push_back({"closing",TableId{self?0U:2U},{VariableId{2},VariableId{0}}});
  for(auto id:head)f.query.head.push_back({VariableId{id},"out"+std::to_string(f.query.head.size())});
  return f;
}
struct Trial {
  Fixture original;
  pf::Plan selected;
  fr::Runtime owner;
  reference::Session model;
  Trial(Fixture f,bool indexed,fr::Options options={})
      :original(std::move(f)),selected(pf::admit(original.catalog,original.query,indexed?s04_runtime::options():PhysicalOptions{})),
       owner(selected,options),model(original.catalog,original.query,Database{std::vector<Relation>(original.catalog.tables.size())}) {verify();}
  void verify() {
    check(owner.ready(),"fallback owner stayed busy");check(owner.sequence()==model.sequence(),"fallback sequence differs");
    check(owner.source_snapshot().tables==model.database().tables,"full source image differs from original state");
    auto snapshot=owner.snapshot();check(snapshot.sequence==owner.sequence(),"snapshot sequence differs");
    check(rows(snapshot.rows)==model.snapshot(),"fallback result differs from original A04 query");
    check(owner.has_answer()==!model.snapshot().empty(),"fallback existence differs");
    check(snapshot.binding.query().atoms.size()==original.query.atoms.size(),"binding lost original occurrence");
    check(snapshot.binding.sources().query().atoms.empty(),"source-only coordinator secretly maintains original joins");
    check(snapshot.binding.profile().backend=="exact_recompute_v1","fallback backend label is not explicit");
    const auto explain=owner.explain();
    check(explain.profile.query_class==selected.structure().query_class,"EXPLAIN changed original structural class");
    check(explain.result_rows==model.snapshot().size(),"EXPLAIN actual result cardinality differs");
    check(explain.table_rows.size()==model.database().tables.size(),"EXPLAIN omitted physical tables");
    for(std::size_t i=0;i<explain.table_rows.size();++i)check(explain.table_rows[i]==model.database().tables[i].size(),"EXPLAIN source count differs");
  }
  fr::Epoch apply(std::size_t table,SetOperation operation,Row values) {
    PhysicalSetUpdate input{model.sequence()+1,TableId{table},operation,std::move(values)};
    const auto reference=model.apply(input);auto epoch=owner.apply(input);
    check(rows(epoch.added)==reference.delta.added&&rows(epoch.removed)==reference.delta.removed,"fallback endpoint sets differ");
    check(epoch.input.input.physical_changed==reference.input_changed,"physical membership flag differs");verify();return epoch;
  }
};
void admission() {
  auto cyclic=triangle();auto p=pf::admit(cyclic.catalog,cyclic.query);
  check(p.structure().query_class==planner::QueryClass::cyclic&&p.profile().reason==pf::Reason::cyclic_body,"cyclic fallback reason differs");
  auto projected=triangle({0,2},false);auto q=pf::admit(projected.catalog,projected.query);
  check(q.structure().query_class==planner::QueryClass::acyclic_non_free_connex&&q.profile().reason==pf::Reason::non_free_connex_head,"projected fallback reason differs");
  auto easy=triangle({0},false);auto r=pf::admit(easy.catalog,easy.query);
  check(r.structure().query_class==planner::QueryClass::free_connex&&r.profile().reason==pf::Reason::explicit_reference_choice,"explicit reference choice differs");
  cyclic.query.head.clear();check(p.query().head.size()==2,"cold plan retained mutable query DTO");
  check(p.source_only().query().atoms.empty()&&p.source_only().source_catalog().tables.size()==4,"source-only plan lost original catalog or kept joins");
  const std::array<std::uint64_t,4> counts{2,3,4,7};auto estimate=p.estimates(counts);
  check(estimate.source_rows==16&&estimate.assignments_upper==24&&estimate.output_rows_upper==24&&estimate.state_rows_upper==40&&estimate.advisory,"fallback estimate formula differs");
  const std::array<std::uint64_t,4> huge{UINT64_MAX,UINT64_MAX,0,0};estimate=p.estimates(huge);
  check(estimate.assignments_upper==0&&estimate.output_rows_upper==0&&estimate.overflow,"zero/overflow estimate was wrapped or lost");
  refusal([&]{(void)p.estimates(std::span<const std::uint64_t>{});});
  auto limits=pf::Limits{};limits.work=0;refusal([&]{(void)pf::admit(projected.catalog,projected.query,{},limits);},"fallback_work_limit");
  limits={};limits.recognition.work_limit=0;refusal([&]{(void)pf::admit(projected.catalog,projected.query,{},limits);},"fallback_work_limit");
  auto bad=projected;bad.query.head.push_back({VariableId{99},"bad"});refusal([&]{(void)pf::admit(bad.catalog,bad.query);});
  bad=projected;bad.catalog.tables[0].columns[0].nullable=true;refusal([&]{(void)pf::admit(bad.catalog,bad.query);});
}
void semantics(bool indexed) {
  std::mt19937 random(0x7106);
  for(bool cyclic:{false,true})for(const auto& head:std::vector<std::vector<std::size_t>>{{0,2},{0,2,0},{},{0,1,2}}) {
    Trial t(triangle(head,cyclic),indexed);
    for(int i=0;i<100;++i) {
      const auto table=random()%(cyclic?3U:2U);
      const auto a=static_cast<std::int64_t>(random()%4),b=static_cast<std::int64_t>(random()%4);
      t.apply(table,random()%2?SetOperation::insert:SetOperation::erase,ints({a,b}));
    }
    const auto unused=t.apply(3,SetOperation::insert,ints({99}));check(!unused.metrics.recomputed,"unused source forced recomputation");
  }
  Trial self(triangle({0},true,true),indexed);
  self.apply(0,SetOperation::insert,ints({1,2}));self.apply(0,SetOperation::insert,ints({2,3}));self.apply(0,SetOperation::insert,ints({3,1}));
  check(self.model.snapshot()==Relation{ints({1}),ints({2}),ints({3})},"self-join oracle control differs");
  const auto duplicate=self.apply(0,SetOperation::insert,ints({3,1}));check(!duplicate.metrics.recomputed,"duplicate source recomputed fallback");
  self.apply(0,SetOperation::insert,ints({1,1}));self.apply(0,SetOperation::erase,ints({2,3}));
}
void terms_and_constants(bool indexed) {
  Fixture f;
  f.catalog.tables={{"rows",{{"a",ScalarType::int64},{"b",ScalarType::int64},{"payload",ScalarType::string}}},
      {"filter",{{"a",ScalarType::int64},{"constant",ScalarType::int64}}}};
  f.query.variables={{"x",ScalarType::int64}};
  f.query.atoms={{"r",TableId{0},{VariableId{0},VariableId{0},IgnoredColumn{}}},
      {"s",TableId{1},{VariableId{0},Value{std::int64_t{7}}}}};
  f.query.head={{VariableId{0},"one"},{VariableId{0},"repeat"}};
  Trial t(f,indexed);t.apply(0,SetOperation::insert,{Value{std::int64_t{1}},Value{std::int64_t{1}},Value{std::string("a\0b",3)}});
  t.apply(0,SetOperation::insert,{Value{std::int64_t{1}},Value{std::int64_t{1}},Value{std::string("other")}});
  t.apply(0,SetOperation::insert,{Value{std::int64_t{1}},Value{std::int64_t{2}},Value{std::string("mismatch")}});
  t.apply(1,SetOperation::insert,ints({1,8}));t.apply(1,SetOperation::insert,ints({1,7}));
  auto nonlast=t.apply(0,SetOperation::erase,{Value{std::int64_t{1}},Value{std::int64_t{1}},Value{std::string("other")}});
  check(nonlast.removed.empty(),"nonlast projected physical witness retracted fallback output");
  check(t.apply(0,SetOperation::erase,{Value{std::int64_t{1}},Value{std::int64_t{1}},Value{std::string("a\0b",3)}}).removed.size()==1,"last projected physical witness not removed");
  Fixture empty;empty.catalog.tables={{"nullary",{}}};Trial one(empty,indexed);check(one.owner.has_answer(),"empty body is not true");
  one.apply(0,SetOperation::insert,{});one.apply(0,SetOperation::erase,{});
  empty.query.atoms={{"nullary_occurrence",TableId{0},{}}};Trial nullary(empty,indexed);
  nullary.apply(0,SetOperation::insert,{});check(nullary.owner.has_answer(),"nullary table witness missing");nullary.apply(0,SetOperation::erase,{});
  auto contradiction=triangle();contradiction.query.contradiction=true;Trial none(contradiction,indexed);
  check(none.selected.profile().reason==pf::Reason::contradiction&&!none.owner.has_answer(),"contradiction fallback reason/result differs");
  check(!none.apply(0,SetOperation::insert,ints({1,2})).metrics.recomputed,"contradiction recomputed original body");
}
void typed(bool indexed) {
  const auto run=[&](ScalarType kind,std::vector<Value> values,std::optional<DecimalSpec> spec={}) {
    Fixture f;f.catalog.tables={{"typed",{{"a",kind,false,Collation::binary,spec},{"b",kind,false,Collation::binary,spec},{"id",ScalarType::int64}}}};
    f.query.variables={{"value",kind},{"id",ScalarType::int64}};
    f.query.atoms={{"typed_occurrence",TableId{0},{VariableId{0},VariableId{0},VariableId{1}}}};
    f.query.head={{VariableId{0},"value"},{VariableId{1},"id"},{VariableId{0},"repeat"}};Trial t(f,indexed);
    std::int64_t id=0;for(const auto& a:values)for(const auto& b:values)t.apply(0,SetOperation::insert,{a,b,Value{id++}});
    id=0;for(const auto& a:values)for(const auto& b:values)t.apply(0,SetOperation::erase,{a,b,Value{id++}});
  };
  run(ScalarType::int64,{Value{INT64_MIN},Value{std::int64_t{0}},Value{INT64_MAX}});
  run(ScalarType::string,{Value{std::string{}},Value{std::string("a\0b",3)},Value{std::string("\xC3\xA9")}});
  run(ScalarType::boolean,{Value{false},Value{true}});
  run(ScalarType::date,{Value{Date::parse("0001-01-01")},Value{Date::parse("9999-12-31")}});
  run(ScalarType::decimal,{Value{Decimal::parse("-999999999999999999999999999999.9999")},Value{Decimal::parse("0.0001")},Value{Decimal::parse("999999999999999999999999999999.9999")}},DecimalSpec{38,4});
}
void wide_and_estimates(bool indexed) {
  Fixture f;f.catalog.tables={{"many",{}}};Atom a{"many_occurrence",TableId{0},{}};Row value;
  a.terms.reserve(70);value.reserve(70);
  for(std::size_t i=0;i<70;++i){
    f.catalog.tables[0].columns.push_back({"c"+std::to_string(i),ScalarType::int64});
    f.query.variables.push_back({"v"+std::to_string(i),ScalarType::int64});
    a.terms.emplace_back(std::in_place_type<VariableId>,VariableId{i});
    value.emplace_back(std::in_place_type<std::int64_t>,static_cast<std::int64_t>(i));
  }
  f.query.atoms.push_back(std::move(a));f.query.head={{VariableId{69},"last"}};Trial wide(f,indexed);wide.apply(0,SetOperation::insert,value);
  Fixture aliases;aliases.catalog.tables={{"unary",{{"v",ScalarType::int64}}},{"empty",{{"v",ScalarType::int64}}}};aliases.query.variables={{"x",ScalarType::int64}};
  for(std::size_t i=0;i<65;++i)aliases.query.atoms.push_back({"alias"+std::to_string(i),TableId{0},{VariableId{0}}});
  aliases.query.atoms.push_back({"late_empty",TableId{1},{IgnoredColumn{}}});aliases.query.head={{VariableId{0},"x"}};Trial t(aliases,indexed);
  t.apply(0,SetOperation::insert,ints({1}));t.apply(0,SetOperation::insert,ints({2}));auto e=t.owner.explain();
  check(e.witness_product==0&&!e.prefix_product_sum,"late zero erased an overflowing prefix estimate");
  const std::array<std::uint64_t,2> counts{2,0};check(t.selected.estimates(counts).assignments_upper==0,"per-alias estimated zero differs");
  t.apply(1,SetOperation::insert,ints({0}));e=t.owner.explain();check(!e.witness_product&&!e.prefix_product_sum,"alias product silently wrapped");
}
void constraints_and_limits(bool indexed) {
  auto f=triangle({0,2},false);f.catalog.tables[1].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  f.catalog.tables[0].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced});Trial constrained(f,indexed);
  refusal([&]{(void)constrained.owner.apply({1,TableId{0},SetOperation::insert,ints({1,7})});});constrained.verify();
  constrained.apply(1,SetOperation::insert,ints({7,10}));constrained.apply(0,SetOperation::insert,ints({1,7}));
  refusal([&]{(void)constrained.owner.apply({3,TableId{1},SetOperation::erase,ints({7,10})});});constrained.verify();
  fr::Options options;options.recompute.rows=1;Trial limited(triangle({0,2},false),indexed,options);
  limited.apply(0,SetOperation::insert,ints({1,7}));limited.apply(1,SetOperation::insert,ints({7,10}));
  refusal([&]{(void)limited.owner.apply({3,TableId{0},SetOperation::insert,ints({2,7})});},"fallback_row_limit");limited.verify();limited.apply(0,SetOperation::insert,ints({2,99}));
  fr::Limits denied;denied.work=0;refusal([&]{(void)limited.owner.snapshot(denied);},"fallback_work_limit");limited.verify();
  options={};options.recompute.source_rows=2;Trial capture(triangle({0,2},false),indexed,options);
  capture.apply(0,SetOperation::insert,ints({1,7}));capture.apply(1,SetOperation::insert,ints({7,10}));capture.apply(3,SetOperation::insert,ints({99}));
  refusal([&]{(void)capture.owner.apply({4,TableId{0},SetOperation::insert,ints({2,7})});},"source_image_row_limit");capture.verify();capture.apply(3,SetOperation::erase,ints({99}));
  options={};options.recompute.work=0;refusal([&]{fr::Runtime owner(pf::admit(f.catalog,f.query),options);},"fallback_work_limit");
}
void allocation_cuts(bool indexed,bool deletion) {
  const auto setup=[&]{auto t=std::make_unique<Trial>(triangle({0}),indexed);
    t->apply(0,SetOperation::insert,ints({1,7}));t->apply(0,SetOperation::insert,ints({2,7}));t->apply(1,SetOperation::insert,ints({7,10}));t->apply(2,SetOperation::insert,ints({10,1}));
    if(deletion)t->apply(2,SetOperation::insert,ints({10,2}));
    return t;};
  const auto event=[&](const Trial& t){return PhysicalSetUpdate{t.owner.sequence()+1,TableId{2},deletion?SetOperation::erase:SetOperation::insert,ints({10,deletion?1:2})};};
  std::size_t allocations=0;
  {auto t=setup();auto input=event(*t);s04_alloc::Scope count;auto e=t->owner.apply(input);allocations=s04_alloc::calls;(void)e;}
  for(std::size_t cut=0;cut<allocations;++cut) {
    auto t=setup();auto input=event(*t);bool failed=false,triggered=false;
    {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));try{(void)t->owner.apply(input);}catch(...){failed=true;}triggered=s04_alloc::triggered;}
    check(failed&&triggered,"fallback allocation refusal not authenticated");t->verify();
    auto actual=t->owner.apply(input);const auto control=t->model.apply(input);t->verify();
    check(rows(actual.added)==control.delta.added&&rows(actual.removed)==control.delta.removed,"same-owner retry endpoint delta differs");
  }
  check(allocations>0,"fallback control observed no allocations");
  std::cout<<"fallback persistent allocation cuts indexed="<<indexed<<" deletion="<<deletion<<" count="<<allocations<<'\n';
}
void lifetime() {
  auto snapshot=[]{Trial t(triangle({0,2},false),false);t.apply(0,SetOperation::insert,ints({1,7}));t.apply(1,SetOperation::insert,ints({7,10}));return t.owner.snapshot();}();
  check(rows(snapshot.rows)==Relation{ints({1,10})},"fallback snapshot did not survive owner teardown");
  check(snapshot.rows[0].is_accounted()&&snapshot.binding.query().head.size()==2,"fallback output lost native schema/payload");
  Trial a(triangle(),false),b(triangle(),false);a.apply(0,SetOperation::insert,ints({1,7}));b.verify();
}
} // namespace
int main() {
  try{admission();lifetime();for(bool indexed:{false,true}){semantics(indexed);terms_and_constants(indexed);typed(indexed);wide_and_estimates(indexed);constraints_and_limits(indexed);allocation_cuts(indexed,false);allocation_cuts(indexed,true);}
    std::cout<<"fallback original A04, cyclic/projected joins, estimates, ownership and atomic refusal checks="<<checks<<'\n';return 0;}
  catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
