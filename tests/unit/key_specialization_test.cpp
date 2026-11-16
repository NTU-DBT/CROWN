#include "crown/planner/keys.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/io/catalog.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace crown;
namespace keys = planner::keys;
std::size_t checks = 0;
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); ++checks; }
Value n(std::int64_t value) { return value; }
Term v(std::size_t value) { return VariableId{value}; }
struct Fixture { Catalog catalog; Query query; };
template<class T> concept RvalueBorrow = requires(T&& value) { std::move(value).execution(); };
static_assert(!RvalueBorrow<keys::Plan>);
static_assert(std::is_nothrow_copy_constructible_v<keys::Plan>);

// The removed parent introduces the lowest-ID private variable. Ordered and
// repeated head fields expose incorrect compaction or original-ID provenance.
Fixture base(bool private_payload = true) {
  Fixture f{{1,{{"p",{{"id",ScalarType::int64},{"payload",ScalarType::int64}}},
      {"c",{{"cid",ScalarType::int64},{"pid",ScalarType::int64},{"tag",ScalarType::int64}}}}},
      {{{"hidden",ScalarType::int64},{"pid",ScalarType::int64},{"tag",ScalarType::int64},{"cid",ScalarType::int64}},
       {{"parent",TableId{0},{v(1),v(0)}},{"child",TableId{1},{v(3),v(1),v(2)}}},
       {{VariableId{2},"tag"},{VariableId{1},"pid"},{VariableId{2},"again"}},false}};
  f.catalog.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  f.catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});
  if (!private_payload) {
    f.query.atoms[0].terms[1] = IgnoredColumn{};
    f.query.variables.erase(f.query.variables.begin());
    for (auto& atom:f.query.atoms) for (auto& term:atom.terms)
      if (auto* id=std::get_if<VariableId>(&term)) --id->value;
    for (auto& output:f.query.head) --output.variable.value;
  }
  return f;
}
PhysicalPlan lower(const Fixture& f, bool indexed) {
  const auto chosen=planner::minimum_tree(f.catalog,f.query);
  check(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree.has_value(),"fixture has no checked tree");
  return planner::lower_tree(f.catalog,f.query,*chosen.tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Relation results(const runtime::PhysicalRuntime& owner) {
  Relation out;auto cursor=owner.results();
  while (auto tuple=cursor.next()) out.insert(storage::export_row(tuple->values()));
  return out;
}
template<class Action> void error(Action action, std::string_view code={}) {
  bool refused=false;
  try { action(); } catch (const Error& e) { refused=true;check(code.empty() || e.code()==code,"wrong refusal code"); }
  check(refused,"operation unexpectedly succeeded");
}
void provenance(const Fixture& f, const keys::Plan& plan) {
  const auto& execution=plan.execution();
  check(io::write_catalog_payload(plan.general().source_catalog())==io::write_catalog_payload(execution.source_catalog()),"source catalog changed");
  check(plan.occurrences().size()==execution.query().atoms.size(),"occurrence map width");
  check(plan.variables().size()==execution.query().variables.size(),"variable map width");
  check(execution.query().head.size()==f.query.head.size(),"output width changed");
  std::set<std::size_t> seen;
  for (std::size_t i=0;i<plan.occurrences().size();++i) {
    const auto old=plan.occurrences()[i].value;
    check(old<f.query.atoms.size() && seen.insert(old).second,"invalid original occurrence map");
    check(execution.query().atoms[i].table==f.query.atoms[old].table,"physical source ID changed");
  }
  for (std::size_t i=0;i<plan.variables().size();++i) {
    const auto old=plan.variables()[i].value;
    check(old<f.query.variables.size(),"invalid original variable map");
    check(execution.query().variables[i].name==f.query.variables[old].name &&
        execution.query().variables[i].type==f.query.variables[old].type,"variable type/name provenance changed");
  }
  for (std::size_t i=0;i<f.query.head.size();++i)
    check(plan.variables()[execution.query().head[i].variable.value]==f.query.head[i].variable,"ordered/repeated output changed");
  if (plan.specialized()) {
    check(plan.reason()==keys::Reason::specialized && plan.reduced_certificate().has_value(),"specialization has no reduced proof");
    const auto reduced=planner::verify_height_certificate(f.catalog,execution.query(),*plan.reduced_certificate());
    const auto original=planner::verify_height_certificate(f.catalog,f.query,*plan.reduced_certificate());
    check(reduced.valid && !reduced.resource_limit && !original.valid,"reduced proof escaped its query scope");
  } else check(!plan.reduced_certificate() && plan.usage().search.work==0,"no-match performed proof search");
}

// Compare both native routes to full materialization of the original CQ. Source
// snapshots are checked even for eliminated tables and rejected updates.
struct Trial {
  const Fixture& fixture;
  keys::Plan plan;
  runtime::PhysicalRuntime general, execution;
  reference::Session reference;
  Trial(const Fixture& f,bool indexed,Database initial={})
      : fixture(f),plan(keys::specialize(lower(f,indexed))),
        general(runtime::PhysicalRuntime::initialize(plan.general(),filled(f,std::move(initial)))),
        execution(runtime::PhysicalRuntime::initialize(plan.execution(),general.snapshot().physical)),
        reference(f.catalog,f.query,general.snapshot().physical) { verify(); }
  static Database filled(const Fixture& f,Database value) {
    if (value.tables.empty()) value.tables.resize(f.catalog.tables.size());
    return value;
  }
  void verify() {
    check(general.ready() && execution.ready(),"owner was left busy");
    check(general.sequence()==reference.sequence() && execution.sequence()==reference.sequence(),"sequence differs");
    check(general.snapshot().physical.tables==reference.database().tables &&
        execution.snapshot().physical.tables==reference.database().tables,"complete source image differs");
    const auto expected=reference.snapshot();
    check(results(general)==expected && results(execution)==expected,"original CQ result differs");
    general.check_invariants();execution.check_invariants();
  }
  std::pair<runtime::PhysicalMetrics,runtime::PhysicalMetrics> apply(std::size_t table,SetOperation operation,Row row,bool reject=false) {
    const PhysicalSetUpdate event{reference.sequence()+1,TableId{table},operation,std::move(row)};
    if (reject) {
      error([&]{static_cast<void>(general.apply(event));},"constraint_violation");
      error([&]{static_cast<void>(execution.apply(event));},"constraint_violation");
      error([&]{static_cast<void>(reference.apply(event));},"constraint_violation");
      verify();return {};
    }
    const auto a=general.apply(event).input.metrics,b=execution.apply(event).input.metrics;
    static_cast<void>(reference.apply(event));verify();return {a,b};
  }
};

void base_trace(bool indexed) {
  const auto f=base();Trial t(f,indexed);const auto original=t.plan.general().physical_sha256();
  check(t.plan.specialized() && t.plan.eliminations().size()==1,"base FK was not specialized");
  check(t.plan.eliminations()[0].removed==OccurrenceId{0} && t.plan.eliminations()[0].witness==OccurrenceId{1},"wrong original elimination IDs");
  check(t.plan.occurrences().size()==1 && t.plan.occurrences()[0]==OccurrenceId{1},"wrong surviving occurrence");
  check(t.plan.variables().size()==3 && t.plan.variables()[0]==VariableId{1},"private variable not compacted");
  provenance(f,t.plan);
  const auto parent=t.apply(0,SetOperation::insert,{n(7),n(70)});
  check(parent.first.aliases_visited==1 && parent.second.aliases_visited==0,"parent route was not reduced");
  check(parent.second.source_changes==1 && parent.second.constraint_validations==1,"eliminated source bypassed enforcement");
  t.apply(1,SetOperation::insert,{n(1),n(7),n(9)});
  const auto duplicate=t.apply(1,SetOperation::insert,{n(1),n(7),n(9)});
  check(duplicate.first.source_changes==0 && duplicate.second.aliases_visited==0,"duplicate source insert changed native input");
  t.apply(1,SetOperation::insert,{n(2),n(7),n(9)});
  t.apply(0,SetOperation::erase,{n(7),n(70)},true);
  t.apply(0,SetOperation::insert,{n(7),n(80)},true);
  t.apply(1,SetOperation::erase,{n(1),n(7),n(9)});
  t.apply(0,SetOperation::erase,{n(7),n(70)},true);
  t.apply(1,SetOperation::erase,{n(2),n(7),n(9)});
  t.apply(0,SetOperation::erase,{n(7),n(70)});
  t.apply(0,SetOperation::erase,{n(7),n(70)});
  check(t.plan.general().physical_sha256()==original,"general plan mutated");
  Database invalid;invalid.tables.resize(2);invalid.tables[1].insert({n(1),n(7),n(9)});
  error([&]{static_cast<void>(runtime::PhysicalRuntime::initialize(t.plan.execution(),invalid));},"constraint_violation");
  invalid.tables[0]={{n(7),n(70)},{n(7),n(80)}};
  error([&]{static_cast<void>(runtime::PhysicalRuntime::initialize(t.plan.execution(),invalid));},"constraint_violation");
}

void guards(bool indexed) {
  auto no_fk=base();no_fk.catalog.tables[1].constraints.clear();
  auto hints=no_fk;hints.catalog.tables[1].key_hints={{{ColumnId{1}},"guessed dependency"}};
  hints.catalog.tables[1].statistics.distinct_counts={{{ColumnId{1}},1}};
  for (auto f:{no_fk,hints}) {
    auto limits=keys::Limits{};limits.search.work_limit=0;
    const auto plan=keys::specialize(lower(f,indexed),limits);
    check(!plan.specialized() && plan.reason()==keys::Reason::no_match,"unproved metadata enabled rewrite");provenance(f,plan);
  }
  auto untrusted=base();std::get<ForeignKeyConstraint>(untrusted.catalog.tables[1].constraints[0]).status=ConstraintStatus::untrusted;
  Trial dangling(untrusted,indexed);check(!dangling.plan.specialized(),"untrusted FK enabled rewrite");
  dangling.apply(1,SetOperation::insert,{n(1),n(7),n(9)});check(results(dangling.execution).empty(),"dangling child became output");

  auto target_constant=base();target_constant.query.atoms[0].terms[1]=Value{std::int64_t{70}};
  target_constant.query.variables.erase(target_constant.query.variables.begin());
  for (auto& atom:target_constant.query.atoms) for (auto& term:atom.terms) if(auto* id=std::get_if<VariableId>(&term))--id->value;
  for(auto& output:target_constant.query.head)--output.variable.value;
  Trial filtered(target_constant,indexed);check(!filtered.plan.specialized(),"target payload filter was removed");
  filtered.apply(0,SetOperation::insert,{n(7),n(80)});filtered.apply(1,SetOperation::insert,{n(1),n(7),n(9)});
  check(results(filtered.execution).empty(),"FK existence bypassed target constant");
  auto output=base();output.query.head={{VariableId{2},"tag"},{VariableId{1},"pid"},{VariableId{0},"payload"}};
  Trial exposed(output,indexed);check(!exposed.plan.specialized(),"target output payload was removed");
  exposed.apply(0,SetOperation::insert,{n(7),n(80)});exposed.apply(1,SetOperation::insert,{n(1),n(7),n(9)});

  auto malformed=base();std::get<UniqueConstraint>(malformed.catalog.tables[0].constraints[0]).status=ConstraintStatus::untrusted;
  const auto valid=lower(base(),indexed);
  error([&]{static_cast<void>(planner::lower_tree(malformed.catalog,malformed.query,valid.tree(),valid.options()));});
  auto nullable=base();nullable.catalog.tables[0].columns[1].nullable=true;
  error([&]{static_cast<void>(planner::lower_tree(nullable.catalog,nullable.query,valid.tree(),valid.options()));});
}

void literals_and_repetitions(bool indexed) {
  auto f=base();f.query.variables={{"hidden",ScalarType::int64},{"tag",ScalarType::int64}};
  f.query.atoms={ {"parent",TableId{0},{Value{std::int64_t{7}},v(0)}},
      {"child",TableId{1},{IgnoredColumn{},Value{std::int64_t{7}},v(1)}} };
  f.query.head={{VariableId{1},"tag"}};
  Trial literal(f,indexed);check(literal.plan.specialized(),"matching FK literals rejected");provenance(f,literal.plan);
  literal.apply(0,SetOperation::insert,{n(7),n(70)});literal.apply(0,SetOperation::insert,{n(8),n(80)});
  literal.apply(1,SetOperation::insert,{n(1),n(8),n(9)});check(results(literal.execution).empty(),"retained literal guard lost");
  literal.apply(1,SetOperation::insert,{n(2),n(7),n(10)});

  Fixture repeat{{1,{{"p",{{"a",ScalarType::int64},{"b",ScalarType::int64},{"payload",ScalarType::int64}}},
      {"c",{{"a",ScalarType::int64},{"b",ScalarType::int64},{"tag",ScalarType::int64}}}}},
      {{{"x",ScalarType::int64},{"t",ScalarType::int64}},
       {{"parent",TableId{0},{v(0),v(0),IgnoredColumn{}}},{"child",TableId{1},{v(0),v(0),v(1)}}},
       {{VariableId{1},"tag"}},false}};
  repeat.catalog.tables[0].constraints={UniqueConstraint{"pk",{ColumnId{1},ColumnId{0}},ConstraintStatus::enforced}};
  repeat.catalog.tables[1].constraints={ForeignKeyConstraint{"fk",{ColumnId{1},ColumnId{0}},TableId{0},{ColumnId{1},ColumnId{0}},ConstraintStatus::enforced}};
  Trial equal(repeat,indexed);check(equal.plan.specialized(),"matching repeated key rejected");
  equal.apply(0,SetOperation::insert,{n(1),n(2),n(70)});equal.apply(1,SetOperation::insert,{n(1),n(2),n(9)});
  check(results(equal.execution).empty(),"retained repeated equality lost");
  equal.apply(0,SetOperation::insert,{n(3),n(3),n(80)});equal.apply(1,SetOperation::insert,{n(3),n(3),n(10)});
  auto mismatch=repeat;mismatch.query.variables.push_back({"y",ScalarType::int64});mismatch.query.atoms[1].terms[1]=v(2);
  Trial unequal(mismatch,indexed);check(!unequal.plan.specialized(),"unproved key equality enabled rewrite");
  unequal.apply(0,SetOperation::insert,{n(1),n(2),n(70)});unequal.apply(1,SetOperation::insert,{n(1),n(2),n(9)});
  check(results(unequal.execution).empty(),"target repeated equality lost");
}

void composite_types(bool indexed) {
  const std::array types{ScalarType::int64,ScalarType::string,ScalarType::boolean,ScalarType::date,ScalarType::decimal};
  Fixture f;f.catalog.tables={{"p",{}},{"c",{}}};
  for(std::size_t i=0;i<types.size();++i) {
    f.catalog.tables[0].columns.push_back({"p"+std::to_string(i),types[i]});
    f.query.variables.push_back({"v"+std::to_string(i),types[i]});
  }
  f.catalog.tables[0].columns.push_back({"payload",ScalarType::int64});
  const std::array<std::size_t,5> order{1,4,0,3,2};
  std::vector<ColumnId> from,to;
  std::vector<Term> child,parent;
  for(std::size_t i=0;i<order.size();++i) {
    f.catalog.tables[1].columns.push_back({"c"+std::to_string(i),types[order[i]]});
    from.push_back(ColumnId{i});to.push_back(ColumnId{order[i]});child.push_back(v(order[i]));parent.push_back(v(i));
  }
  f.catalog.tables[1].columns.push_back({"tag",ScalarType::int64});f.query.variables.push_back({"tag",ScalarType::int64});
  child.push_back(v(5));parent.push_back(IgnoredColumn{});
  f.catalog.tables[0].constraints={UniqueConstraint{"pk",{ColumnId{4},ColumnId{0},ColumnId{1},ColumnId{3},ColumnId{2}},ConstraintStatus::enforced}};
  f.catalog.tables[1].constraints={ForeignKeyConstraint{"fk",from,TableId{0},to,ConstraintStatus::enforced}};
  f.query.atoms={{"parent",TableId{0},parent},{"child",TableId{1},child}};f.query.head={{VariableId{5},"tag"},{VariableId{0},"id"}};
  Trial t(f,indexed);check(t.plan.specialized(),"mixed composite key rejected");provenance(f,t.plan);
  const Row p{n(INT64_MIN),Value{std::string("a\0z",3)},Value{true},Value{Date::parse("2000-02-29")},Value{Decimal::parse("1.00")},n(70)};
  t.apply(0,SetOperation::insert,p);
  t.apply(1,SetOperation::insert,{p[1],Value{Decimal::parse("1.0")},p[0],p[3],p[2],n(INT64_MAX)});
}

void self_cycles_and_empty(bool indexed) {
  Fixture self{{1,{{"e",{{"id",ScalarType::int64},{"parent",ScalarType::int64}}}}},
      {{{"parent",ScalarType::int64},{"id",ScalarType::int64}},
       {{"p",TableId{0},{v(0),IgnoredColumn{}}},{"c",TableId{0},{v(1),v(0)}}},{{VariableId{1},"id"}},false}};
  self.catalog.tables[0].constraints={UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced}};
  Trial t(self,indexed);check(t.plan.specialized() && t.plan.execution().base_routes()[0].size()==1,"self alias routing lost");
  const auto loop=t.apply(0,SetOperation::insert,{n(1),n(1)});
  check(loop.first.aliases_visited==2 && loop.second.aliases_visited==1,"self alias count not reduced");
  t.apply(0,SetOperation::insert,{n(2),n(1)});t.apply(0,SetOperation::erase,{n(1),n(1)},true);
  t.apply(0,SetOperation::erase,{n(2),n(1)});t.apply(0,SetOperation::erase,{n(1),n(1)});

  auto cycle=base();cycle.catalog.tables[0].constraints.push_back(
      ForeignKeyConstraint{"back",{ColumnId{1}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced});
  cycle.catalog.tables[1].constraints.push_back(UniqueConstraint{"cid",{ColumnId{0}},ConstraintStatus::enforced});
  Database initial;initial.tables={{{n(7),n(1)}},{{n(1),n(7),n(9)}}};
  Trial c(cycle,indexed,initial);check(c.plan.specialized(),"cyclic FK catalog confused with query shape");
  c.apply(0,SetOperation::erase,{n(7),n(1)},true);c.apply(1,SetOperation::erase,{n(1),n(7),n(9)},true);
  const auto extra=c.apply(0,SetOperation::insert,{n(8),n(1)});
  check(extra.second.aliases_visited==0,"cyclic catalog retained eliminated source route");
  c.apply(0,SetOperation::erase,{n(8),n(1)});

  Fixture unit{{1,{{"p",{{"payload",ScalarType::int64}}},{"c",{{"tag",ScalarType::int64}}}}},
      {{{"t",ScalarType::int64}},{{"p",TableId{0},{IgnoredColumn{}}},{"c",TableId{1},{v(0)}}},{{VariableId{0},"tag"}},false}};
  unit.catalog.tables[0].constraints={UniqueConstraint{"unit",{},ConstraintStatus::enforced}};
  unit.catalog.tables[1].constraints={ForeignKeyConstraint{"exists",{},TableId{0},{},ConstraintStatus::enforced}};
  Trial u(unit,indexed);check(u.plan.specialized(),"unit key rejected");
  u.apply(1,SetOperation::insert,{n(9)},true);u.apply(0,SetOperation::insert,{n(7)});
  u.apply(1,SetOperation::insert,{n(9)});u.apply(0,SetOperation::erase,{n(7)},true);
  u.apply(0,SetOperation::insert,{n(8)},true);u.apply(1,SetOperation::erase,{n(9)});u.apply(0,SetOperation::erase,{n(7)});
}

void unselected_routes() {
  const auto f=base();
  auto binding=frontend::bind_sql("SELECT DISTINCT c.tag FROM c JOIN p ON c.pid=p.id",f.catalog);
  check(std::holds_alternative<frontend::BoundSql>(binding),"SQL fixture did not bind");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized),"SQL fixture did not normalize");
  const auto& sql=std::get<frontend::NormalizedSql>(normalized);
  const auto choice=planner::minimum_tree(sql.core_catalog,sql.core);check(choice.tree.has_value(),"SQL tree missing");
  const auto general=planner::lower_normalized(sql,*choice.tree);
  keys::Limits no_search;no_search.search.work_limit=0;
  const auto unchanged=keys::specialize(general,no_search);
  check(unchanged.reason()==keys::Reason::normalized_sql && !unchanged.specialized() &&
      unchanged.execution().physical_sha256()==general.physical_sha256(),"normalized SQL was rewritten");
  const Catalog empty_catalog{};const Query truth{};
  const auto constant=planner::lower_tree(empty_catalog,truth,{});
  const auto kept=keys::specialize(constant,no_search);
  check(kept.reason()==keys::Reason::constant_route && !kept.specialized() && kept.usage().search.work==0,"constant route searched");
}

// Cold refusals leave the general artifact intact. Sample cuts cover compiler
// phases without repeating the unrelated exhaustive planner OOM suite.
void resource_and_ownership(bool indexed) {
  const auto f=base();const auto general=lower(f,indexed);const auto identity=general.physical_sha256();
  const auto warm=keys::specialize(general);keys::Limits limits;limits.work=0;
  error([&]{static_cast<void>(keys::specialize(general,limits));},"key_work_limit");
  limits.work=warm.usage().work;check(keys::specialize(general,limits).specialized(),"exact guard work refused");
  --limits.work;error([&]{static_cast<void>(keys::specialize(general,limits));},"key_work_limit");
  limits={};limits.search.work_limit=0;
  error([&]{static_cast<void>(keys::specialize(general,limits));},"key_search_limit");
  limits={};limits.lowering=PhysicalLimits{};limits.lowering->work_limit=0;
  error([&]{static_cast<void>(keys::specialize(general,limits));});
  std::size_t allocations=0;
  {s04_alloc::Scope count;const auto measured=keys::specialize(general);allocations=s04_alloc::calls;check(measured.specialized(),"calibration failed");}
  check(allocations>0,"cold allocations were not observed");
  std::set<std::size_t> points;
  for(std::size_t i=0;i<32;++i)points.insert(allocations*i/32);
  points.insert(allocations);bool succeeded=false;
  for(const auto point:points) {
    bool refused=false,triggered=false;std::optional<keys::Plan> result;
    {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(point));
      try {result.emplace(keys::specialize(general));}
      catch(const std::bad_alloc&) {refused=true;}
      catch(const Error&) {refused=true;}
      triggered=s04_alloc::triggered;
    }
    check(refused==triggered && bool(result)!=refused,"cold allocation refusal was swallowed");
    if(result) {check(result->specialized(),"fault-free result is not specialized");succeeded=true;}
    check(general.physical_sha256()==identity,"cold failure mutated general plan");
  }
  check(succeeded,"sampled allocation sequence never succeeded");
  runtime::PhysicalRuntimeOptions options;options.support.memory_limit_bytes=16ULL*1024*1024;
  auto owner=runtime::PhysicalRuntime(warm.execution(),options);
  static_cast<void>(owner.apply({1,TableId{0},SetOperation::insert,{n(7),n(70)}}));
  const auto account=owner.plan().account();const auto baseline=account.statistics().current;
  const auto free=account.statistics().limit_bytes-baseline.requested_bytes;
  const auto overhead=resource::MemoryAccount::allocation_bytes(0,alignof(std::max_align_t));check(free>overhead,"no filler room");
  {auto filler=account.allocate(static_cast<std::size_t>(free-overhead));bool refused=false;
    try {static_cast<void>(owner.apply({2,TableId{1},SetOperation::insert,{n(1),n(7),n(9)}}));}
    catch(const resource::MemoryFailure& e) {refused=e.fault()==resource::MemoryFault::limit;}
    check(refused && owner.ready() && owner.sequence()==1,"account denial changed owner");}
  check(account.statistics().current==baseline,"account denial retained private allocations");
  {auto pending=owner.prepare({2,TableId{1},SetOperation::insert,{n(1),n(7),n(9)}});check(pending.active(),"prepare missing");}
  check(owner.ready() && owner.sequence()==1 && results(owner).empty(),"abandoned prepare published");
  static_cast<void>(owner.apply({2,TableId{1},SetOperation::insert,{n(1),n(7),n(9)}}));
  auto cursor=owner.results();auto held=cursor.next();check(held.has_value(),"result absent");
  error([&]{static_cast<void>(owner.apply({3,TableId{1},SetOperation::erase,{n(1),n(7),n(9)}}));},"runtime_busy");
  cursor.cancel();owner.check_invariants();account.check_invariants();
  std::optional<runtime::PhysicalRuntime> closing;closing.emplace(std::move(owner));closing.reset();
  check(storage::export_row(held->values())==Row{n(9),n(7),n(9)},"result identity changed");
  held.reset();account.check_invariants();
}
} // namespace

int main() {
  try {
    for(const bool indexed:{false,true}) {
      base_trace(indexed);guards(indexed);literals_and_repetitions(indexed);
      composite_types(indexed);self_cycles_and_empty(indexed);resource_and_ownership(indexed);
    }
    unselected_routes();
    std::cout<<"key specialization: "<<checks<<" guard/source/provenance/resource checks passed\n";
  } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
