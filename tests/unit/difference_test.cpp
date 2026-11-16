#include "crown/runtime/difference.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <stdexcept>

namespace {
using namespace crown;
namespace pd=planner::difference;
namespace dr=runtime::difference;
using Bag=std::map<Row,std::uint64_t>;
using Changes=std::map<Row,std::pair<std::uint64_t,std::uint64_t>>;
std::uint64_t checks=0;
void check(bool condition,const char* message) {
  if(!condition)throw std::runtime_error(message);
  ++checks;
}
template<class F>void refusal(F action,std::string_view code={}) {
  bool failed=false;
  try{action();}
  catch(const Error& e){failed=true;check(code.empty()||code==e.code(),"unexpected difference error category");}
  catch(const resource::MemoryFailure&){failed=true;check(code.empty(),"unexpected memory refusal");}
  catch(const storage::IndexFailure& e){failed=true;check(code.empty()||code==e.code(),"unexpected index refusal");}
  check(failed,"difference operation did not refuse");
}
Row ints(std::initializer_list<std::int64_t> values) {
  Row row;for(auto value:values)row.emplace_back(value);return row;
}
// Test-only Cartesian definition: select every physical row combination first,
// then unify the original terms. It shares no native trail/cursor/count helper.
Bag operand(const Query& query,const Database& database) {
  if(query.contradiction)return {};
  Bag result;std::vector<const Row*> selected(query.atoms.size());
  std::function<void(std::size_t)> combinations=[&](std::size_t depth) {
    if(depth<query.atoms.size()) {
      for(const auto& row:database.tables[query.atoms[depth].table.value]){selected[depth]=&row;combinations(depth+1);}
      return;
    }
    std::vector<std::optional<Value>> binding(query.variables.size());
    for(std::size_t i=0;i<query.atoms.size();++i)for(std::size_t j=0;j<query.atoms[i].terms.size();++j) {
      const auto& term=query.atoms[i].terms[j];const auto& value=(*selected[i])[j];
      if(const auto* variable=std::get_if<VariableId>(&term)) {
        auto& bound=binding[variable->value];if(bound&&*bound!=value)return;bound=value;
      } else if(const auto* literal=std::get_if<Value>(&term);literal&&*literal!=value)return;
    }
    Row row;for(const auto& field:query.head)row.push_back(binding[field.variable.value].value());
    ++result[std::move(row)];
  };
  combinations(0);return result;
}
struct Fixture {Catalog catalog;Query left,right;};
Fixture unary(bool self=false,bool boolean=false) {
  Fixture f;f.catalog.tables={{"L",{{"v",ScalarType::int64},{"id",ScalarType::int64}}},
      {"R",{{"v",ScalarType::int64},{"id",ScalarType::int64}}},{"unused",{{"v",ScalarType::int64}}}};
  f.left.variables={{"left_value",ScalarType::int64}};
  f.left.atoms={{"left_rows",TableId{0},{VariableId{0},IgnoredColumn{}}}};
  f.right.variables={{"right_value",ScalarType::int64}};
  f.right.atoms={{"right_rows",TableId{self?0U:1U},{VariableId{0},IgnoredColumn{}}}};
  if(!boolean){f.left.head={{VariableId{0},"left_alias"}};f.right.head={{VariableId{0},"right_alias"}};}
  return f;
}
Fixture joins(bool cyclic,bool aliases,std::vector<std::size_t> head={0,2}) {
  Fixture f;f.catalog.tables={{"R",{{"a",ScalarType::int64},{"b",ScalarType::int64}}},
      {"S",{{"a",ScalarType::int64},{"b",ScalarType::int64}}},
      {"T",{{"a",ScalarType::int64},{"b",ScalarType::int64}}},{"unused",{{"v",ScalarType::int64}}}};
  f.left.variables={{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}};
  f.left.atoms={{"first",TableId{0},{VariableId{0},VariableId{1}}},
      {"second",TableId{aliases?0U:1U},{VariableId{1},VariableId{2}}}};
  if(cyclic)f.left.atoms.push_back({"closing",TableId{aliases?0U:2U},{VariableId{2},VariableId{0}}});
  for(auto v:head)f.left.head.push_back({VariableId{v},"l"+std::to_string(f.left.head.size())});
  f.right=f.left;f.right.atoms.push_back({"positive_filter",TableId{2},{VariableId{0},IgnoredColumn{}}});
  for(auto& field:f.right.head)field.alias="r"+field.alias;
  return f;
}
Bag expected(const Fixture& f,const Database& database,pd::Mode mode) {
  auto left=operand(f.left,database),right=operand(f.right,database);Bag result;
  for(const auto& [row,count]:left) {
    const auto found=right.find(row);const auto other=found==right.end()?0:found->second;
    const auto residual=mode==pd::Mode::set_except?std::uint64_t(other==0):(count>other?count-other:0);
    if(residual)result.emplace(row,residual);
  }
  return result;
}
Changes changes(const Bag& before,const Bag& after) {
  Changes result;
  for(const auto& [row,count]:before){const auto p=after.find(row);const auto next=p==after.end()?0:p->second;if(count!=next)result[row]={count,next};}
  for(const auto& [row,count]:after)if(!before.contains(row))result[row]={0,count};
  return result;
}
template<class Range>Bag rows(const Range& input) {
  Bag result;for(const auto& value:input){check(value.multiplicity.value>0,"zero residual count escaped");
    check(value.tuple.is_accounted(),"difference row lost original native ownership");
    check(result.emplace(storage::export_row(value.tuple.values()),value.multiplicity.value).second,"duplicate compressed key escaped");}
  return result;
}
template<class Range>Changes replacements(const Range& input) {
  Changes result;for(const auto& value:input){check(value.before!=value.after,"unchanged endpoint emitted");
    check(value.tuple.is_accounted(),"difference replacement lost native ownership");
    check(result.emplace(storage::export_row(value.tuple.values()),std::pair{value.before.value,value.after.value}).second,"duplicate endpoint replacement escaped");}
  return result;
}
struct Trial {
  Fixture original;pd::Mode mode;pd::Plan selected;dr::Runtime owner;reference::Session sources;
  Trial(Fixture f,bool indexed,pd::Mode semantics,dr::Options options={})
      :original(std::move(f)),mode(semantics),selected(pd::admit(original.catalog,original.left,original.right,mode,indexed?s04_runtime::options():PhysicalOptions{})),
       owner(selected,options),sources(original.catalog,Query{},Database{std::vector<Relation>(original.catalog.tables.size())}) {verify();}
  Bag answer() const{return expected(original,sources.database(),mode);}
  void verify() {
    check(owner.ready(),"difference owner remained busy");check(owner.sequence()==sources.sequence(),"difference sequence differs");
    check(owner.source_snapshot().tables==sources.database().tables,"difference full sources differ");
    const auto snapshot=owner.snapshot();check(snapshot.sequence==sources.sequence(),"difference snapshot sequence differs");
    check(rows(snapshot.rows)==answer(),"difference result differs from Cartesian definition");
    check(owner.has_answer()==!answer().empty(),"difference existence differs");
    check(snapshot.binding.left().atoms.size()==original.left.atoms.size()&&snapshot.binding.right().atoms.size()==original.right.atoms.size(),"binding lost an original operand");
    check(snapshot.binding.sources().query().atoms.empty(),"difference coordinator routes original atoms");
    check(snapshot.binding.profile().mode==mode,"difference semantic mode changed");
    const auto explanation=owner.explain();check(explanation.result_rows==answer().size(),"EXPLAIN result key count differs");
    check(explanation.table_rows.size()==sources.database().tables.size(),"EXPLAIN lost physical table counts");
    for(std::size_t i=0;i<explanation.table_rows.size();++i)check(explanation.table_rows[i]==sources.database().tables[i].size(),"EXPLAIN source count differs");
  }
  dr::Epoch apply(std::size_t table,SetOperation operation,Row values) {
    const auto before=answer();PhysicalSetUpdate input{sources.sequence()+1,TableId{table},operation,std::move(values)};
    const auto model=sources.apply(input);auto actual=owner.apply(input);
    check(actual.input.input.physical_changed==model.input_changed,"difference source membership flag differs");
    check(replacements(actual.changes)==changes(before,answer()),"difference endpoint counts differ");verify();return actual;
  }
};
void admission() {
  auto f=unary();auto p=pd::admit(f.catalog,f.left,f.right);
  check(p.profile().mode==pd::Mode::set_except&&p.source_only().query().atoms.empty(),"difference default mode/source authority differs");
  check(p.left().query().head[0].alias!=p.right().query().head[0].alias,"operand aliases were coerced");
  f.left.head.clear();check(p.left().query().head.size()==1,"difference plan retained caller mutation");
  refusal([&]{(void)pd::admit(f.catalog,f.left,f.right);},"difference_admission");
  f=unary();refusal([&]{(void)pd::admit(f.catalog,f.left,f.right,static_cast<pd::Mode>(99));},"difference_admission");
  pd::Limits limits;limits.work=0;refusal([&]{(void)pd::admit(f.catalog,f.left,f.right,pd::Mode::set_except,{},limits);},"difference_work_limit");
  limits={};limits.left.work=0;refusal([&]{(void)pd::admit(f.catalog,f.left,f.right,pd::Mode::set_except,{},limits);},"difference_work_limit");
  limits={};limits.right.work=0;refusal([&]{(void)pd::admit(f.catalog,f.left,f.right,pd::Mode::set_except,{},limits);},"difference_work_limit");
  auto bad=f;bad.catalog.tables[1].columns[0].type=ScalarType::string;bad.right.variables[0].type=ScalarType::string;
  refusal([&]{(void)pd::admit(bad.catalog,bad.left,bad.right);},"difference_admission");
  bad=f;bad.right.head[0].variable=VariableId{99};refusal([&]{(void)pd::admit(bad.catalog,bad.left,bad.right);},"difference_admission");
  bad=f;bad.catalog.tables[2].columns[0].nullable=true;refusal([&]{(void)pd::admit(bad.catalog,bad.left,bad.right);},"difference_admission");
  const std::array<std::uint64_t,3> counts{3,99,5};const auto estimates=p.estimates(counts);
  check(estimates.source_rows==107&&estimates.output_rows_upper==3&&estimates.output_multiplicity_upper==3&&estimates.state_rows_upper==110,"difference estimates subtracted upper bounds or duplicated sources");
  refusal([&]{(void)p.estimates({});},"difference_admission");
  f=unary(false,true);const auto bag=pd::admit(f.catalog,f.left,f.right,pd::Mode::bag_except_all);
  const auto estimate=bag.estimates(counts);check(estimate.output_rows_upper==1&&estimate.output_multiplicity_upper==3,"Boolean bag estimate conflated key count and multiplicity");
}
void transitions(bool indexed,pd::Mode mode) {
  Trial t(unary(),indexed,mode);
  t.apply(0,SetOperation::insert,ints({7,1}));t.apply(0,SetOperation::insert,ints({7,2}));t.apply(0,SetOperation::insert,ints({7,3}));
  auto first=t.apply(1,SetOperation::insert,ints({7,10}));
  check(!first.changes.empty(),"right insertion did not retract membership/count");
  if(mode==pd::Mode::bag_except_all)check(t.answer()==Bag{{ints({7}),2}},"EXCEPT ALL did not subtract counts");
  else check(t.answer().empty(),"EXCEPT failed right-presence blocking");
  t.apply(1,SetOperation::insert,ints({7,11}));t.apply(1,SetOperation::insert,ints({7,12}));t.apply(1,SetOperation::insert,ints({7,13}));
  check(t.answer().empty(),"negative bag residual escaped");t.apply(1,SetOperation::erase,ints({7,13}));
  t.apply(1,SetOperation::erase,ints({7,12}));t.apply(1,SetOperation::erase,ints({7,11}));t.apply(1,SetOperation::erase,ints({7,10}));
  t.apply(0,SetOperation::erase,ints({7,2}));t.apply(0,SetOperation::erase,ints({7,1}));t.apply(0,SetOperation::erase,ints({7,3}));
  const auto absent=t.apply(0,SetOperation::erase,ints({99,3}));check(!absent.metrics.recomputed,"absent deletion recomputed operands");
  t.apply(0,SetOperation::insert,ints({8,1}));const auto duplicate=t.apply(0,SetOperation::insert,ints({8,1}));
  check(duplicate.changes.empty()&&!duplicate.metrics.recomputed,"duplicate physical insert changed bag multiplicity");
  check(!t.apply(2,SetOperation::insert,ints({99})).metrics.recomputed,"unused source recomputed difference");
  auto squared=unary(true,true);squared.left.atoms.push_back({"independent_alias",TableId{0},{VariableId{0},IgnoredColumn{}}});
  Trial aliases(squared,indexed,mode);aliases.apply(0,SetOperation::insert,ints({7,1}));
  const auto squared_epoch=aliases.apply(0,SetOperation::insert,ints({7,2}));
  check(aliases.answer()==(mode==pd::Mode::set_except?Bag{}:Bag{{Row{},2}}),"bag self-alias physical choices did not multiply before projection");
  if(mode==pd::Mode::bag_except_all)check(squared_epoch.metrics.left_assignments==4&&squared_epoch.metrics.right_assignments==2,"Boolean bag metrics skipped complete witnesses");
  Trial equal(unary(true),indexed,mode);equal.apply(0,SetOperation::insert,ints({2,1}));equal.apply(0,SetOperation::insert,ints({2,2}));
  check(equal.answer().empty(),"identical operands published a source-prefix artifact");
}
void generated(bool indexed,pd::Mode mode) {
  std::mt19937 random(0x7208);
  for(bool cyclic:{false,true})for(bool aliases:{false,true})for(const auto& head:std::vector<std::vector<std::size_t>>{{0,2},{2,0,2},{}}) {
    Trial t(joins(cyclic,aliases,head),indexed,mode);
    for(int i=0;i<80;++i)t.apply(random()%3,random()%2?SetOperation::insert:SetOperation::erase,
        ints({static_cast<std::int64_t>(random()%3),static_cast<std::int64_t>(random()%3)}));
  }
}
void constants(bool indexed,pd::Mode mode) {
  Trial boolean(unary(false,true),indexed,mode);boolean.apply(0,SetOperation::insert,ints({1,1}));boolean.apply(0,SetOperation::insert,ints({2,1}));
  boolean.apply(1,SetOperation::insert,ints({9,1}));
  check(boolean.answer()==(mode==pd::Mode::set_except?Bag{}:Bag{{Row{},1}}),"Boolean EXCEPT ALL stopped at the first witness");
  Fixture empty;empty.catalog.tables={{"nullary",{}}};empty.right.contradiction=true;
  Trial initial(empty,indexed,mode);check(initial.answer()==Bag{{Row{},1}},"true EXCEPT false empty-body result differs");
  empty.right.contradiction=false;Trial both(empty,indexed,mode);check(both.answer().empty(),"true EXCEPT true was not empty");
  empty.right.atoms={{"nullary_test",TableId{0},{}}};Trial nullary(empty,indexed,mode);
  nullary.apply(0,SetOperation::insert,{});check(nullary.answer().empty(),"nullary RHS witness did not block true");nullary.apply(0,SetOperation::erase,{});
  auto f=unary();f.left.atoms[0].terms[1]=Value{std::int64_t{7}};f.right.atoms[0].terms[1]=VariableId{0};
  f.left.head.push_back({VariableId{0},"repeat"});f.right.head.push_back({VariableId{0},"other_repeat"});
  Trial terms(f,indexed,mode);terms.apply(0,SetOperation::insert,ints({3,7}));terms.apply(0,SetOperation::insert,ints({3,8}));
  terms.apply(1,SetOperation::insert,ints({3,4}));terms.apply(1,SetOperation::insert,ints({3,3}));terms.apply(1,SetOperation::erase,ints({3,3}));
}
void typed(bool indexed,pd::Mode mode) {
  const auto run=[&](ScalarType type,std::vector<Value> values,std::optional<DecimalSpec> leftspec={},std::optional<DecimalSpec> rightspec={}) {
    Fixture f;f.catalog.tables={{"L",{{"v",type,false,Collation::binary,leftspec},{"id",ScalarType::int64}}},
        {"R",{{"v",type,false,Collation::binary,rightspec},{"id",ScalarType::int64}}}};
    f.left.variables={{"l",type}};f.right.variables={{"r",type}};
    f.left.atoms={{"left",TableId{0},{VariableId{0},IgnoredColumn{}}}};f.right.atoms={{"right",TableId{1},{VariableId{0},IgnoredColumn{}}}};
    f.left.head={{VariableId{0},"l"},{VariableId{0},"lr"}};f.right.head={{VariableId{0},"r"},{VariableId{0},"rr"}};
    Trial t(f,indexed,mode);std::int64_t id=0;
    for(const auto& value:values){t.apply(0,SetOperation::insert,{value,Value{id}});t.apply(0,SetOperation::insert,{value,Value{id+100}});t.apply(1,SetOperation::insert,{value,Value{id++}});}
    id=0;for(const auto& value:values)t.apply(1,SetOperation::erase,{value,Value{id++}});
  };
  run(ScalarType::int64,{Value{INT64_MIN},Value{std::int64_t{0}},Value{INT64_MAX}});
  run(ScalarType::string,{Value{std::string{}},Value{std::string("a\0b",3)},Value{std::string("\xC3\xA9")}});
  run(ScalarType::boolean,{Value{false},Value{true}});
  run(ScalarType::date,{Value{Date::parse("0001-01-01")},Value{Date::parse("9999-12-31")}});
  run(ScalarType::decimal,{Value{Decimal::parse("-999.99")},Value{Decimal::parse("0.01")},Value{Decimal::parse("999.99")}},DecimalSpec{5,2},DecimalSpec{12,4});
  Fixture f;f.catalog.tables={{"L",{{"v",ScalarType::decimal,false,Collation::binary,DecimalSpec{5,2}}}},
      {"R",{{"v",ScalarType::decimal,false,Collation::binary,DecimalSpec{12,4}}}}};
  f.left.variables={{"l",ScalarType::decimal}};f.right.variables={{"r",ScalarType::decimal}};
  f.left.atoms={{"left",TableId{0},{VariableId{0}}}};f.right.atoms={{"right",TableId{1},{VariableId{0}}}};
  f.left.head={{VariableId{0},"l"}};f.right.head={{VariableId{0},"r"}};Trial broad(f,indexed,mode);
  broad.apply(0,SetOperation::insert,{Value{Decimal::parse("1.25")}});broad.apply(1,SetOperation::insert,{Value{Decimal::parse("100000.0001")}});
  broad.apply(1,SetOperation::insert,{Value{Decimal::parse("1.2500")}});
}
void constraints_and_limits(bool indexed,pd::Mode mode) {
  auto f=unary();f.catalog.tables[1].constraints.push_back(UniqueConstraint{"right_pk",{ColumnId{0}},ConstraintStatus::enforced});
  f.catalog.tables[0].constraints.push_back(ForeignKeyConstraint{"left_fk",{ColumnId{0}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced});
  Trial constrained(f,indexed,mode);
  refusal([&]{(void)constrained.owner.apply({1,TableId{0},SetOperation::insert,ints({7,1})});});constrained.verify();
  constrained.apply(1,SetOperation::insert,ints({7,1}));constrained.apply(0,SetOperation::insert,ints({7,1}));
  refusal([&]{(void)constrained.owner.apply({3,TableId{1},SetOperation::erase,ints({7,1})});});constrained.verify();
  refusal([&]{(void)constrained.owner.apply({3,TableId{1},SetOperation::insert,ints({7,2})});});constrained.verify();
  dr::Options options;options.recompute.rows=1;Trial keys(unary(),indexed,mode,options);
  keys.apply(0,SetOperation::insert,ints({1,1}));
  refusal([&]{(void)keys.owner.apply({2,TableId{0},SetOperation::insert,ints({2,1})});},"difference_row_limit");keys.verify();
  keys.apply(1,SetOperation::insert,ints({1,1}));
  // The per-operand cap is explicit even if the final residual would be empty.
  refusal([&]{(void)keys.owner.apply({3,TableId{1},SetOperation::insert,ints({9,1})});},"difference_row_limit");keys.verify();
  options={};options.recompute.source_rows=1;Trial image(unary(),indexed,mode,options);
  image.apply(0,SetOperation::insert,ints({1,1}));image.apply(2,SetOperation::insert,ints({99}));
  refusal([&]{(void)image.owner.apply({3,TableId{1},SetOperation::insert,ints({1,1})});},"source_image_row_limit");image.verify();image.apply(2,SetOperation::erase,ints({99}));
  dr::Limits no_work;no_work.work=0;refusal([&]{(void)keys.owner.snapshot(no_work);},"difference_work_limit");keys.verify();
  dr::Limits no_rows;no_rows.rows=0;Trial visible(unary(),indexed,mode);visible.apply(0,SetOperation::insert,ints({8,1}));
  refusal([&]{(void)visible.owner.snapshot(no_rows);},"difference_row_limit");visible.verify();
  options={};options.recompute.work=0;refusal([&]{dr::Runtime denied(pd::admit(f.catalog,f.left,f.right,mode),options);},"difference_work_limit");
  options={};options.multiplicity_limit=0;refusal([&]{dr::Runtime denied(pd::admit(f.catalog,f.left,f.right,mode),options);},"invalid_annotation");
  options={};options.multiplicity_limit=2;Trial counts(unary(),indexed,mode,options);
  counts.apply(0,SetOperation::insert,ints({1,1}));counts.apply(0,SetOperation::insert,ints({1,2}));
  if(mode==pd::Mode::bag_except_all) {
    refusal([&]{(void)counts.owner.apply({3,TableId{0},SetOperation::insert,ints({1,3})});},"annotation_overflow");counts.verify();
    counts.apply(0,SetOperation::insert,ints({2,1}));
  } else {counts.apply(0,SetOperation::insert,ints({1,3}));check(counts.answer()==Bag{{ints({1}),1}},"set mode overflowed witness counts instead of saturating support");}
}
void cumulative_work(bool indexed,pd::Mode mode) {
  std::vector<PhysicalSetUpdate> events;
  for(std::uint64_t i=0;i<10;++i)events.push_back({i+1,TableId{0},SetOperation::insert,ints({1,static_cast<std::int64_t>(i)})});
  events.push_back({11,TableId{1},SetOperation::insert,ints({1,99})});
  Trial control(unary(),indexed,mode);std::uint64_t work=0;
  for(const auto& e:events)work=control.apply(e.table.value,e.operation,e.values).metrics.work;
  check(work>1,"difference successful control has no cumulative work");
  dr::Options options;options.recompute.work=work-1;Trial limited(unary(),indexed,mode,options);
  for(std::size_t i=0;i+1<events.size();++i)limited.apply(events[i].table.value,events[i].operation,events[i].values);
  refusal([&]{(void)limited.owner.apply(events.back());},"difference_work_limit");limited.verify();
  limited.apply(2,SetOperation::insert,ints({5}));
}
void allocation_cuts(bool indexed,pd::Mode mode,bool deletion) {
  const auto setup=[&]{auto t=std::make_unique<Trial>(unary(),indexed,mode);
    t->apply(0,SetOperation::insert,ints({7,1}));t->apply(0,SetOperation::insert,ints({7,2}));
    if(deletion)t->apply(1,SetOperation::insert,ints({7,9}));
    return t;};
  const auto event=[&](const Trial& t){return PhysicalSetUpdate{t.owner.sequence()+1,TableId{1},deletion?SetOperation::erase:SetOperation::insert,ints({7,9})};};
  std::size_t allocations=0;
  {auto t=setup();auto input=event(*t);s04_alloc::Scope count;auto epoch=t->owner.apply(input);allocations=s04_alloc::calls;(void)epoch;}
  for(std::size_t cut=0;cut<allocations;++cut) {
    auto t=setup();auto input=event(*t);bool failed=false,triggered=false;
    {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));try{(void)t->owner.apply(input);}catch(...){failed=true;}triggered=s04_alloc::triggered;}
    check(failed&&triggered,"difference persistent allocation refusal was not authenticated");t->verify();
    const auto before=t->answer();const auto actual=t->owner.apply(input);(void)t->sources.apply(input);t->verify();
    check(replacements(actual.changes)==changes(before,t->answer()),"same-owner retry changed exact endpoint replacements");
  }
  check(allocations>0,"difference control observed no allocations");
  std::cout<<"difference persistent allocation cuts indexed="<<indexed<<" bag="<<(mode==pd::Mode::bag_except_all)<<" deletion="<<deletion<<" count="<<allocations<<'\n';
}
void lifetime(bool indexed,pd::Mode mode) {
  auto snapshot=[&]{Trial t(unary(),indexed,mode);t.apply(0,SetOperation::insert,ints({7,1}));t.apply(0,SetOperation::insert,ints({7,2}));return t.owner.snapshot();}();
  check(rows(snapshot.rows)==Bag{{ints({7}),mode==pd::Mode::set_except?1U:2U}},"retained difference snapshot changed after teardown");
  check(snapshot.binding.left().atoms.size()==1&&snapshot.binding.right().head.size()==1,"retained original pair binding lost metadata");
  auto epoch=[&]{Trial t(unary(),indexed,mode);t.apply(0,SetOperation::insert,ints({7,1}));t.apply(0,SetOperation::insert,ints({7,2}));return t.apply(1,SetOperation::insert,ints({7,9}));}();
  const auto before=mode==pd::Mode::set_except?1U:2U,after=mode==pd::Mode::set_except?0U:1U;
  check(replacements(epoch.changes)==Changes{{ints({7}),{before,after}}},"retained difference epoch changed after teardown");
  check(epoch.changes[0].delta().negative&&epoch.changes[0].delta().magnitude.value==1,"difference signed magnitude narrowed a replacement");
  const dr::Change maximum_add{snapshot.rows[0].tuple,{0},{UINT64_MAX}}, maximum_remove{snapshot.rows[0].tuple,{UINT64_MAX},{0}};
  check(!maximum_add.delta().negative&&maximum_add.delta().magnitude.value==UINT64_MAX,"positive endpoint magnitude narrowed to signed int64");
  check(maximum_remove.delta().negative&&maximum_remove.delta().magnitude.value==UINT64_MAX,"negative endpoint magnitude narrowed to signed int64");
  Trial a(unary(),indexed,mode),b(unary(),indexed,mode);a.apply(0,SetOperation::insert,ints({1,1}));b.verify();
  auto source_account=snapshot.binding.account().statistics();check(source_account.current.requested_bytes>0,"retained difference outputs lost account");
}
} // namespace
int main() {
  try{admission();for(bool indexed:{false,true})for(auto mode:{pd::Mode::set_except,pd::Mode::bag_except_all}){
      transitions(indexed,mode);generated(indexed,mode);constants(indexed,mode);typed(indexed,mode);
      constraints_and_limits(indexed,mode);cumulative_work(indexed,mode);lifetime(indexed,mode);allocation_cuts(indexed,mode,false);allocation_cuts(indexed,mode,true);}
    std::cout<<"difference Cartesian set/bag, endpoint and ownership checks="<<checks<<'\n';return 0;}
  catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
