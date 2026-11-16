#include "crown/runtime/comparisons.hpp"
#include "crown/frontend/admission.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

namespace {
using namespace crown;
namespace pc = planner::comparisons;
namespace rt = runtime::comparisons;
std::uint64_t checks = 0;
void check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
  ++checks;
}
template<class Function> void refusal(Function action, std::string_view code = {}) {
  bool failed = false;
  try { action(); }
  catch (const Error& e) { failed = true; check(code.empty() || e.code() == code, "wrong refusal category"); }
  catch (const resource::MemoryFailure&) { failed = true; check(code.empty(), "unexpected memory refusal"); }
  catch (const storage::IndexFailure&) { failed = true; check(code.empty(), "unexpected index refusal"); }
  catch (const std::bad_alloc&) { failed = true; check(code.empty(), "unexpected allocation refusal"); }
  check(failed, "expected refusal did not occur");
}
Row ints(std::initializer_list<std::int64_t> input) {
  Row out; for (auto n : input) out.emplace_back(n); return out;
}
template<class Range> Relation rows(const Range& input) {
  Relation out;
  for (const auto& tuple : input)
    check(out.insert(storage::export_row(tuple.values())).second, "duplicate output escaped");
  return out;
}
struct Fixture { Catalog catalog; Query query; FreeConnexTree tree; };
Fixture path(std::vector<std::size_t> head = {0}, bool self_join = false) {
  Fixture f;
  f.catalog.tables = {{"R", {{"a",ScalarType::int64},{"b",ScalarType::int64}}},
      {"S", {{"b",ScalarType::int64},{"c",ScalarType::int64}}},
      {"unused", {{"v",ScalarType::int64}}}};
  f.query.variables = {{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}};
  f.query.atoms = {{"left",TableId{0},{VariableId{0},VariableId{1}}},
      {"right",TableId{self_join?0U:1U},{VariableId{1},VariableId{2}}}};
  for (auto id : head) f.query.head.push_back({VariableId{id},"out"+std::to_string(f.query.head.size())});
  f.tree.root=NodeId{0};
  f.tree.nodes={{"root",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"child",NodeKind::native,{VariableId{1},VariableId{2}},{},1,{}}};
  return f;
}
PhysicalPlan lower(const Fixture& f, bool indexed) {
  return planner::lower_tree(f.catalog,f.query,f.tree,indexed?s04_runtime::options():PhysicalOptions{});
}
pc::Predicate predicate(pc::Operator operation = pc::Operator::less) {
  return {VariableId{0},operation,VariableId{2}};
}
// This slow definition uses original full-state joins with ALL variables in
// the reference head. It never filters an already projected native answer.
Relation expected(const Fixture& f, const Database& database, std::span<const pc::Predicate> predicates) {
  auto complete=f.query;complete.head.clear();
  for(std::size_t i=0;i<complete.variables.size();++i) complete.head.push_back({VariableId{i},"v"+std::to_string(i)});
  Relation out;
  for(const auto& assignment:reference::evaluate(f.catalog,complete,database)) {
    bool accepted=true;
    for(const auto& p:predicates) {
      const auto read=[&](const pc::Operand& operand)->const Value& {
        if(const auto* id=std::get_if<VariableId>(&operand))return assignment.at(id->value);
        return std::get<Value>(operand);
      };
      const auto order=read(p.left)<=>read(p.right);
      switch(p.operation) {
        case pc::Operator::equal:accepted=order==0;break;
        case pc::Operator::not_equal:accepted=order!=0;break;
        case pc::Operator::less:accepted=order<0;break;
        case pc::Operator::less_equal:accepted=order<=0;break;
        case pc::Operator::greater:accepted=order>0;break;
        case pc::Operator::greater_equal:accepted=order>=0;break;
      }
      if(!accepted)break;
    }
    if(accepted) {Row projected;for(const auto& field:f.query.head)projected.push_back(assignment.at(field.variable.value));out.insert(std::move(projected));}
  }
  return out;
}
struct Trial {
  Fixture original;
  std::vector<pc::Predicate> predicates;
  pc::Plan selected;
  rt::Runtime owner;
  reference::Session reference;
  Trial(Fixture f, std::vector<pc::Predicate> p, bool indexed, rt::Options options = {})
      :original(std::move(f)),predicates(std::move(p)),selected(pc::admit(lower(original,indexed),predicates)),
       owner(selected,options),reference(original.catalog,original.query,
           Database{std::vector<Relation>(original.catalog.tables.size())}) {verify();}
  void verify() {
    check(owner.ready(),"comparison owner stayed busy");
    check(owner.sequence()==reference.sequence(),"source epoch differs");
    check(owner.source_snapshot().tables==reference.database().tables,"original source state differs");
    const auto actual=owner.snapshot();
    const auto oracle=expected(original,reference.database(),predicates);
    check(actual.sequence==owner.sequence(),"snapshot sequence differs");
    check(rows(actual.rows)==oracle,"comparison differs from full-assignment oracle");
    check(owner.has_answer()==!oracle.empty(),"comparison existence differs");
  }
  rt::Epoch apply(std::size_t table, SetOperation operation, Row values) {
    const auto before=expected(original,reference.database(),predicates);
    const PhysicalSetUpdate update{reference.sequence()+1,TableId{table},operation,std::move(values)};
    const auto control=reference.apply(update);
    auto epoch=owner.apply(update);
    const auto after=expected(original,reference.database(),predicates);
    Relation added,removed;
    std::set_difference(after.begin(),after.end(),before.begin(),before.end(),std::inserter(added,added.end()));
    std::set_difference(before.begin(),before.end(),after.begin(),after.end(),std::inserter(removed,removed.end()));
    check(rows(epoch.added)==added && rows(epoch.removed)==removed,"endpoint delta differs");
    check(epoch.input.input.physical_changed==control.input_changed,"physical membership flag differs");
    verify();return epoch;
  }
};
void admission() {
  const auto f=path();const auto original=lower(f,false);std::vector<pc::Predicate> input{predicate()};
  const auto plan=pc::admit(original,input);input.front().operation=pc::Operator::greater;
  check(plan.predicates().front().operation==pc::Operator::less,"admission retained mutable caller predicates");
  check(plan.general().physical_sha256()==original.physical_sha256(),"admission changed original plan identity");
  auto bad=predicate();bad.left=VariableId{99};refusal([&]{(void)pc::admit(original,std::span(&bad,1));},"comparison_admission");
  bad=predicate();bad.right=Value{std::string("1")};refusal([&]{(void)pc::admit(original,std::span(&bad,1));},"comparison_admission");
  bad=predicate();bad.operation=static_cast<pc::Operator>(99);refusal([&]{(void)pc::admit(original,std::span(&bad,1));},"comparison_admission");
  refusal([&]{(void)pc::admit(original,plan.predicates(),pc::Limits{0});},"comparison_work_limit");
  const auto sql=frontend::admit_sql("SELECT DISTINCT r.a FROM \"R\" r, \"S\" s WHERE r.a < s.c",f.catalog);
  check(sql.status==frontend::AdmissionStatus::unsupported_semantics,"equality SQL failed to classify the comparison as unsupported");
}
void semantics(bool indexed) {
  std::mt19937 random(0x7004);
  for(auto op:{pc::Operator::equal,pc::Operator::not_equal,pc::Operator::less,pc::Operator::less_equal,pc::Operator::greater,pc::Operator::greater_equal}) {
    Trial t(path({0,0}),{predicate(op)},indexed);
    for(int i=0;i<120;++i) {
      const auto table=random()%2;
      const auto v=static_cast<std::int64_t>(random()%7)-3;
      t.apply(table,(random()%2)?SetOperation::insert:SetOperation::erase,table==0?ints({v,7}):ints({7,v}));
    }
    const auto event=t.apply(2,SetOperation::insert,ints({42}));
    check(!event.metrics.recomputed,"unused source caused unnecessary recomputation");
  }
  Trial projection(path(),{predicate()},indexed);
  projection.apply(0,SetOperation::insert,ints({1,7}));
  projection.apply(1,SetOperation::insert,ints({7,2}));
  projection.apply(1,SetOperation::insert,ints({7,3}));
  const auto duplicate=projection.apply(0,SetOperation::insert,ints({1,7}));
  check(!duplicate.metrics.recomputed,"duplicate physical input recomputed output");
  check(projection.apply(1,SetOperation::erase,ints({7,2})).removed.empty(),"nonlast hidden witness retracted output");
  check(projection.apply(1,SetOperation::erase,ints({7,3})).removed.size()==1,"last hidden witness was not retracted");
  Trial self(path({},true),{predicate()},indexed);
  self.apply(0,SetOperation::insert,ints({1,2}));self.apply(0,SetOperation::insert,ints({2,3}));
  self.apply(0,SetOperation::insert,ints({2,4}));self.apply(0,SetOperation::erase,ints({2,3}));
  check(self.apply(0,SetOperation::erase,ints({2,4})).removed.size()==1,"self-join last witness delta differs");
}
void typed(bool indexed) {
  const auto one=[&](ScalarType kind,std::vector<Value> values,std::optional<DecimalSpec> decimal={}) {
    Fixture f;
    f.catalog.tables={{"typed",{{"a",kind,false,Collation::binary,decimal},{"b",kind,false,Collation::binary,decimal},{"id",ScalarType::int64}}}};
    f.query.variables={{"a",kind},{"b",kind},{"id",ScalarType::int64}};
    f.query.atoms={{"one",TableId{0},{VariableId{0},VariableId{1},VariableId{2}}}};
    f.query.head={{VariableId{2},"id"}};f.tree.root=NodeId{0};
    f.tree.nodes={{"one",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2}},{},0,{}}};
    for(auto op:{pc::Operator::equal,pc::Operator::not_equal,pc::Operator::less,pc::Operator::less_equal,pc::Operator::greater,pc::Operator::greater_equal}) {
      Trial t(f,{{VariableId{0},op,VariableId{1}},{Value{values.front()},pc::Operator::less_equal,VariableId{1}}},indexed);
      std::int64_t id=0;
      for(const auto& a:values)for(const auto& b:values)t.apply(0,SetOperation::insert,Row{a,b,Value{id++}});
      id=0;for(const auto& a:values)for(const auto& b:values)t.apply(0,SetOperation::erase,Row{a,b,Value{id++}});
    }
  };
  one(ScalarType::int64,{Value{INT64_MIN},Value{std::int64_t{-1}},Value{std::int64_t{0}},Value{INT64_MAX}});
  one(ScalarType::string,{Value{std::string{}},Value{std::string("a\0b",3)},Value{std::string("\xC3\xA9")}});
  one(ScalarType::boolean,{Value{false},Value{true}});
  one(ScalarType::date,{Value{Date::parse("0001-01-01")},Value{Date::parse("1970-01-01")},Value{Date::parse("9999-12-31")}});
  one(ScalarType::decimal,{Value{Decimal::parse("-999999999999999999999999999999.9999")},Value{Decimal::parse("0.0001")},Value{Decimal::parse("999999999999999999999999999999.9999")}},DecimalSpec{38,4});
}
void constants(bool indexed) {
  Fixture f;f.catalog.tables={{"unused",{{"v",ScalarType::int64}}}};
  for(bool truth:{false,true}) {
    Trial t(f,{{Value{std::int64_t{1}},truth?pc::Operator::less:pc::Operator::greater,Value{std::int64_t{2}}}},indexed);
    check(t.owner.has_answer()==truth,"constant comparison initial result differs");
    t.apply(0,SetOperation::insert,ints({7}));t.apply(0,SetOperation::erase,ints({7}));
  }
  auto empty=path();empty.query.contradiction=true;empty.tree={};
  Trial no_rows(empty,{predicate()},indexed);no_rows.apply(0,SetOperation::insert,ints({1,7}));
  check(!no_rows.owner.has_answer(),"contradictory original plan emitted a comparison result");
}
void constraints_and_limits(bool indexed) {
  auto f=path();f.catalog.tables[1].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  f.catalog.tables[0].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced});
  Trial constrained(f,{predicate()},indexed);
  refusal([&]{(void)constrained.owner.apply({1,TableId{0},SetOperation::insert,ints({1,7})});});constrained.verify();
  constrained.apply(1,SetOperation::insert,ints({7,3}));constrained.apply(0,SetOperation::insert,ints({1,7}));
  refusal([&]{(void)constrained.owner.apply({3,TableId{1},SetOperation::erase,ints({7,3})});});constrained.verify();
  rt::Options options;options.recompute.rows=1;
  Trial limited(path(),{predicate()},indexed,options);
  limited.apply(0,SetOperation::insert,ints({1,7}));limited.apply(1,SetOperation::insert,ints({7,3}));
  refusal([&]{(void)limited.owner.apply({3,TableId{0},SetOperation::insert,ints({2,7})});});limited.verify();
  limited.apply(0,SetOperation::insert,ints({4,7}));
  rt::Limits denied;denied.work=0;refusal([&]{(void)limited.owner.snapshot(denied);});limited.verify();
  denied={};denied.rows=0;refusal([&]{(void)limited.owner.snapshot(denied);});limited.verify();
  options={};options.recompute.work=0;refusal([&]{rt::Runtime owner(pc::admit(lower(path(),indexed),std::vector<pc::Predicate>{predicate()}),options);});
  // Empty joins fit this one cumulative producer allowance; the after-state
  // forty-witness scan does not. Refusal must roll back already prepared source.
  options={};options.recompute.producer_work=128;
  Trial producer(path(),{predicate()},indexed,options);
  for(std::int64_t i=0;i<40;++i)producer.apply(0,SetOperation::insert,ints({i,7}));
  refusal([&]{(void)producer.owner.apply({41,TableId{1},SetOperation::insert,ints({7,100})});});
  producer.verify();
  producer.apply(2,SetOperation::insert,ints({99}));
}
void allocation_cuts(bool indexed, bool deletion) {
  const auto setup=[&] {
    auto t=std::make_unique<Trial>(path(),std::vector<pc::Predicate>{predicate()},indexed);
    t->apply(0,SetOperation::insert,ints({1,7}));t->apply(1,SetOperation::insert,ints({7,3}));
    t->apply(0,SetOperation::insert,ints({2,7}));t->apply(1,SetOperation::insert,ints({7,4}));
    if(deletion)t->apply(0,SetOperation::insert,ints({3,7}));
    return t;
  };
  const auto event=[&](const Trial& t){return PhysicalSetUpdate{t.owner.sequence()+1,TableId{deletion?1U:0U},deletion?SetOperation::erase:SetOperation::insert,ints({deletion?7:3,deletion?4:7})};};
  std::size_t allocations=0;
  {auto t=setup();const auto input=event(*t);{s04_alloc::Scope count;auto e=t->owner.apply(input);allocations=s04_alloc::calls;(void)e;}}
  check(allocations>0,"allocation cut control observed no allocations");
  for(std::size_t cut=0;cut<allocations;++cut) {
    auto t=setup();const auto input=event(*t);bool failed=false;
    {s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));try{(void)t->owner.apply(input);}catch(...){failed=true;}}
    check(failed && s04_alloc::triggered,"allocation denial did not cause refusal");t->verify();
    const auto old=expected(t->original,t->reference.database(),t->predicates);
    auto e=t->owner.apply(input);(void)t->reference.apply(input);t->verify();
    const auto now=expected(t->original,t->reference.database(),t->predicates);Relation add,remove;
    std::set_difference(now.begin(),now.end(),old.begin(),old.end(),std::inserter(add,add.end()));
    std::set_difference(old.begin(),old.end(),now.begin(),now.end(),std::inserter(remove,remove.end()));
    check(rows(e.added)==add&&rows(e.removed)==remove,"same-owner retry delta differs after allocation refusal");
  }
  std::cout<<"comparison persistent allocation cuts indexed="<<indexed<<" deletion="<<deletion<<" count="<<allocations<<'\n';
}
void retained() {
  auto snapshot=[] {Trial t(path(),{predicate()},false);t.apply(0,SetOperation::insert,ints({1,7}));t.apply(1,SetOperation::insert,ints({7,3}));return t.owner.snapshot();}();
  check(rows(snapshot.rows)==Relation{ints({1})},"owning comparison snapshot did not survive runtime teardown");
  check(snapshot.rows.front().is_accounted(),"comparison output uses unaccounted row payload");
  Trial a(path(),{predicate()},false),b(path(),{predicate(pc::Operator::greater)},false);
  a.apply(0,SetOperation::insert,ints({1,7}));a.apply(1,SetOperation::insert,ints({7,3}));b.verify();
}
} // namespace
int main() {
  try {
    admission();retained();
    for(bool indexed:{false,true}){semantics(indexed);typed(indexed);constants(indexed);constraints_and_limits(indexed);allocation_cuts(indexed,false);allocation_cuts(indexed,true);}
    std::cout<<"comparison original A04 assignments, exact typed predicates, endpoint deltas, ownership and atomic refusal checks="<<checks<<'\n';return 0;
  }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
