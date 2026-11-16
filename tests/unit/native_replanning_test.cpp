#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "compiled_source.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/normalization.hpp"
#include "crown/ir/digest.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>

using namespace crown;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(message));}
template<class Range,class Function> io::Json array(const Range& values,Function emit) {
  auto result=io::Json::array();for(const auto& value:values)result.push_back(emit(value));return result;
}
template<class Range> io::Json ids(const Range& values) {return array(values,[](auto id){return id.value;});}
template<class Id> io::Json optional_id(const std::optional<Id>& value) {return value?io::Json(value->value):io::Json(nullptr);}
io::Json slot(AssignmentSlot value) {return {value.step,value.field.value};}
template<class L> io::Json layout(const L& value) {
  const auto fields=array(value.fields(),[](const auto& field){
    return io::Json{{"type",static_cast<int>(field.type)},{"decimal",field.decimal?io::Json{field.decimal->precision,field.decimal->scale}:io::Json(nullptr)},
        {"variable",optional_id(field.variable)}};
  });
  const auto origin=value.origin();return {{"id",value.id().value},{"fields",fields},
      {"version",value.context().catalog_version},{"binding",std::string(value.context().binding)},
      {"origin",origin?io::Json{origin->table.value,origin->source_schema_version}:io::Json(nullptr)}};
}
template<class P> io::Json projection(const P& value) {
  return {{"source",value.source().id().value},{"target",value.target().id().value},{"fields",ids(value.fields())}};
}
io::Json scalar(const Value& value) {return io::write_scalar(value);}
io::Json scalar(const storage::ScalarView& value) {return io::write_scalar_view(value);}
template<class P> io::Json image(const P& plan) {
  auto result=io::Json{{"route",static_cast<int>(plan.route())},{"hash",std::string(plan.physical_sha256())},
      {"source_hash",std::string(plan.physical_source_sha256())},{"work",plan.work()},
      {"layouts",array(plan.layouts(),[](const auto& value){return layout(value);})},
      {"relations",array(plan.relations(),[](const auto& value){return io::Json{value.id.value,static_cast<int>(value.role),value.layout.id().value,optional_id(value.node),optional_id(value.base)};})},
      {"indexes",array(plan.indexes(),[](const auto& value){return io::Json{{"id",value.id.value},{"relation",value.relation.value},{"projection",projection(value.projection)},
          {"uses",array(value.uses,[](auto use){return static_cast<int>(use);})}};})},
      {"inputs",array(plan.inputs(),[](const auto& value){return io::Json{{"occurrence",value.occurrence.value},{"node",value.node.value},
          {"base",value.base.value},{"logical",value.logical_table.value},{"physical",value.physical_layout.id().value},{"projection",projection(value.projection)},
          {"equalities",array(value.equalities,[](auto pair){return io::Json{pair.left.value,pair.right.value};})},
          {"constants",array(value.constants,[](const auto& constant){return io::Json{constant.field.value,scalar(constant.value)};})}};})},
      {"routes",array(plan.base_routes(),[](const auto& route){return ids(route);})},
      {"nodes",array(plan.nodes(),[](const auto& value){return io::Json{{"id",value.id.value},{"kind",static_cast<int>(value.kind)},
          {"occurrence",optional_id(value.occurrence)},{"parent",optional_id(value.parent)},{"children",ids(value.children)},
          {"scope",ids(value.scope)},{"visible_scope",ids(value.visible_scope)},{"connex",value.connex},{"layout",value.layout.id().value},
          {"parent_key",projection(value.parent_key)},{"visible_key",value.visible_projection?projection(*value.visible_projection):io::Json(nullptr)},
          {"relations",io::Json{value.records.value,value.survivors.value,value.parent_support.value,optional_id(value.visible_relation)}}};})},
      {"edges",array(plan.edges(),[](const auto& value){return io::Json{value.parent.value,value.child.value,value.child_slot,projection(value.parent_key),optional_id(value.reverse_index)};})},
      {"steps",array(plan.enumeration().steps,[](const auto& value){return io::Json{{"node",value.node.value},{"relation",value.relation.value},{"depth",value.depth},
          {"parent",value.parent_step?io::Json(*value.parent_step):io::Json(nullptr)},{"key",value.parent_key?projection(*value.parent_key):io::Json(nullptr)},{"index",optional_id(value.bucket_index)}};})},
      {"output",array(plan.enumeration().output,[](auto value){return slot(value);})},
      {"equalities",array(plan.enumeration().equalities,[](auto value){return io::Json{slot(value.left),slot(value.right)};})},
      {"depth",plan.enumeration().depth},{"result",layout(plan.result_layout())},
      {"valid",plan.validation().valid},{"height",plan.validation().native_height?io::Json(*plan.validation().native_height):io::Json(nullptr)},
      {"edge_depth",plan.validation().edge_depth?io::Json(*plan.validation().edge_depth):io::Json(nullptr)},
      {"connex",ids(plan.validation().maximal_connex)},{"separators",array(plan.validation().separators,[](const auto& value){return ids(value);})}};
  const auto& identity=plan.identity();result["identity"]={identity.semantic_sha256,identity.output_contract_sha256,identity.cost_inputs_sha256,identity.plan_cache_sha256,identity.work};
  result["occurrence_order"]=array(identity.occurrence_order,[](auto value){return value;});result["variable_order"]=array(identity.variable_order,[](auto value){return value;});
  if(plan.normalized()) {
    if constexpr(std::is_same_v<P,CompiledProgram>)result["normalized"]=io::write_sql_normalization(planner::compiler_source_detail::normalized(*plan.normalized()));
    else result["normalized"]=io::write_sql_normalization(*plan.normalized());
  }else result["normalized"]=nullptr;
  return result;
}
template<class P> auto projections(const P& plan) {
  using T=std::remove_cvref_t<decltype(plan.indexes()[0].projection)>;std::vector<const T*> result;
  for(const auto& value:plan.indexes())result.push_back(&value.projection);
  for(const auto& value:plan.inputs())result.push_back(&value.projection);
  for(const auto& value:plan.nodes()){result.push_back(&value.parent_key);if(value.visible_projection)result.push_back(&*value.visible_projection);}
  for(const auto& value:plan.edges())result.push_back(&value.parent_key);
  for(const auto& value:plan.enumeration().steps)if(value.parent_key)result.push_back(&*value.parent_key);
  return result;
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto current=account.statistics().current;
  check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),"native replanning retained a released graph/source/account allocation");
}
struct Case {
  Catalog catalog;Query query;std::optional<frontend::NormalizedSql> sql;planner::CandidateSnapshot candidates;
  Case(Catalog c,Query q,std::optional<frontend::NormalizedSql> s,std::size_t height)
      :catalog(std::move(c)),query(std::move(q)),sql(std::move(s)),candidates(c02_test::candidates({catalog,query,{}},height,0)) {}
  PhysicalPlan lower(bool indexed,std::size_t i=0) const {
    const auto& tree=candidates.candidate(i)->tree();const auto options=indexed?s04_runtime::options():PhysicalOptions{};
    return sql?planner::lower_normalized(*sql,tree,options):planner::lower_tree(catalog,query,tree,options);
  }
};
Case core() {auto f=c02_test::fixture();f.query.head={{VariableId{0},"first"},{VariableId{1},"second"},{VariableId{0},"again"}};return {std::move(f.catalog),std::move(f.query),{},2};}
Case sql(bool exists) {
  const auto f=c02_test::fixture();const auto text=exists?
      R"SQL(SELECT EXISTS (SELECT 1 FROM "R" r JOIN "S" s ON r.x=s.x JOIN "T" t ON s.y=t.y WHERE s.x>=0))SQL":
      R"SQL(SELECT DISTINCT r.x AS first,t.y AS second,r.x AS again,'marker' AS extra FROM "R" r JOIN "S" s ON r.x=s.x JOIN "T" t ON s.y=t.y WHERE s.x>=0)SQL";
  auto bound=frontend::bind_sql(text,f.catalog);check(std::holds_alternative<frontend::BoundSql>(bound),"native replan SQL did not bind");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));check(std::holds_alternative<frontend::NormalizedSql>(normalized),"native replan SQL did not normalize");
  auto program=std::get<frontend::NormalizedSql>(std::move(normalized));auto catalog=program.core_catalog;auto query=program.core;return {std::move(catalog),std::move(query),std::move(program),2};
}
Case rich() {
  const std::string text=std::string(8192,'z')+std::string("a\0b",3);
  Table table{"values",{{"key",ScalarType::int64},{"i",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},
      {"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}}}};
  table.constraints={UniqueConstraint{"key",{ColumnId{0}},ConstraintStatus::enforced}};table.statistics.row_count=997;table.statistics.distinct_counts={{{ColumnId{0}},991}};
  table.key_hints={{{ColumnId{1}},"binary\"hint\n\u03bb"}};
  Catalog catalog{7,{table,{"unused",{{"flag",ScalarType::boolean}}}}};
  Query query{{{"x\"\n\u03bb",ScalarType::int64}},{{"v",TableId{0},{VariableId{0},Value{INT64_MIN},Value{text},Value{true},
      Value{Date::parse("0001-01-01")},Value{Decimal::parse("-99999999999999999999999999.123456789012")}}}},
      {{VariableId{0},"first"},{VariableId{0},"again"}},false};
  return {std::move(catalog),std::move(query),{},1};
}
struct Fixture {
  resource::MemoryAccount account;
  CompiledProgram basis;
  const Case& input;
  Fixture(const Case& c,bool indexed,std::uint64_t cap):account(resource::MemoryAccount::create(cap)),input(c) {
    const auto source=c.lower(indexed);storage::IndexWorkAllowance grant(source.options().indexed_storage?source.options().indexed_storage->per_operation:
        storage::IndexWork{UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true);
    basis=CompiledProgram::freeze(account,source,&grant);
  }
  CompiledProgram replan(std::size_t i=0) const {return CompiledProgram::replan(basis,*input.candidates.candidate(i));}
};
void equivalence(const Case& input,bool indexed) {
  Fixture fixture(input,indexed,allowance);
  for(std::size_t i=0;i<input.candidates.candidate_count();++i) {
    const auto expected=input.lower(indexed,i);const auto actual=fixture.replan(i);
    check(expected.physical_source_sha256()==sha256(io::write_physical_source(expected.catalog(),expected.query(),expected.normalized()).dump()),"prepared source fingerprint differs from original encoding");
    check(image(actual)==image(expected),"native candidate instructions, bindings, identity or work differ from original lowering");
    check(io::write_physical(actual)==io::write_physical(expected),"explicit native caller export changed the existing physical format");
    const auto old=projections(expected);const auto native=projections(actual);check(old.size()==native.size(),"native projection inventory changed");
    for(std::size_t a=0;a<old.size();++a)for(std::size_t b=0;b<old.size();++b)check(old[a]->same_token(*old[b])==native[a]->same_token(*native[b]),"native projection alias graph differs from original");
    for(std::size_t a=0;a<actual.inputs().size();++a) {
      const auto& atom=input.query.atoms[a];Row row;
      for(const auto& term:atom.terms) {
        if(const auto* value=std::get_if<Value>(&term))row.push_back(*value);
        else row.emplace_back(std::in_place_type<std::int64_t>,1);
      }
      if(!input.sql) {
        const auto old_tuple=expected.adapt_input(OccurrenceId{a},row);
        std::vector<storage::ScalarView> borrowed;for(const auto& value:row)borrowed.push_back(storage::borrow_scalar(value));
        const auto new_tuple=actual.adapt_input(OccurrenceId{a},storage::RowView::borrow(borrowed));
        check(bool(old_tuple)==bool(new_tuple) && (!old_tuple || new_tuple->values()==storage::export_row(old_tuple->values())),"native candidate input adaptation changed typed bytes");
      }
    }
    storage::IndexWorkAllowance grant(actual.options().indexed_storage?actual.options().indexed_storage->per_operation:
        storage::IndexWork{UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true);
    auto state=actual.make_storage(&grant);state.check_invariants(&grant);
    for(const auto& relation:actual.relations())check(state.table(relation.id).layout().same_token(relation.layout),"native storage binding changed canonical layout token");
  }
}
void requests_and_lifetime(const Case& input,bool indexed) {
  std::optional<Fixture> fixture(std::in_place,input,indexed,allowance);const auto account=fixture->account;const auto before=account.statistics();
  CompiledProgram held;std::size_t calls=0;
  {s04_alloc::Scope count;held=fixture->replan();calls=s04_alloc::calls;}
  const auto after=account.statistics();check(calls>0 && calls==after.successful_allocations-before.successful_allocations,"native lowering allocated outside the original query account");
  check(held.account().statistics().current==after.current,"native lowering replaced the original query account");
  const auto hash=std::string(held.physical_sha256());CompiledProgram copy;
  {s04_alloc::Scope none(0);copy=held;fixture.reset();check(copy.physical_sha256()==hash && copy.validation().valid,"native lowered graph lost source lifetime");held={};copy={};}
  controller_only(account);
}
std::size_t persistent(const Case& input,bool indexed) {
  Fixture fixture(input,indexed,allowance);const auto held=fixture.replan();const auto preserved=image(held);std::size_t expected=0;
  {s04_alloc::Scope count;const auto calibration=fixture.replan();expected=s04_alloc::calls;}
  check(expected>0 && expected<4096,"native replanning fault count is outside test bound");
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=fixture.account.statistics();CompiledProgram output;bool failed=false;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{output=fixture.replan();}catch(const std::bad_alloc&){failed=true;}calls=s04_alloc::calls;}
    if(point<expected) {
      check(failed && calls==point+1 && !output && fixture.account.statistics().current==before.current,"failed native replan leaked or published a partial graph");output=fixture.replan();
    }else check(!failed && calls==expected && calls==fixture.account.statistics().successful_allocations-before.successful_allocations,"native replan fault sweep missed an original-account request");
    check(image(output)==preserved && image(held)==preserved,"native replan fault/retry changed an old or complete result");
    {s04_alloc::Scope none(0);output={};}fixture.account.check_invariants();
  }
  return expected;
}
std::pair<std::uint64_t,std::size_t> caps(const Case& input,bool indexed) {
  std::uint64_t peak=0;std::size_t pins=0;
  {
    Fixture fixture(input,indexed,allowance);std::vector<CompiledProgram> held;held.reserve(1024);
    for(std::size_t i=0;i<1024;++i) {
      const auto before=fixture.account.statistics().peak_requested_bytes;auto next=fixture.replan();const auto after=fixture.account.statistics().peak_requested_bytes;
      if(i>0 && after>before){peak=after;pins=i;break;}held.push_back(std::move(next));
    }
    check(peak>0 && pins>0,"native replan never exceeded source-admission peak");
  }
  for(const bool exact:{true,false}) {
    Fixture fixture(input,indexed,exact?peak:peak-1);std::vector<CompiledProgram> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(fixture.replan());
    const auto before=fixture.account.statistics().current;bool denied=false;
    try{const auto output=fixture.replan();check(output.validation().valid,"bounded native replan lost checked tree");}
    catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong native replan query-cap failure");denied=true;}
    check(denied!=exact && fixture.account.statistics().current==before,"native replan exact/one-under cap leaked or ignored its grant");
    if(!exact){held.pop_back();const auto retry=fixture.replan();check(retry.validation().valid && fixture.account.statistics().limit_bytes==peak-1,"native replan retry minted another allowance");}
  }
  return {peak,pins};
}
void churn_and_work(const Case& input,bool indexed) {
  Fixture fixture(input,indexed,allowance);const auto before=fixture.account.statistics().current;
  std::vector<resource::MemoryUsage> expected;expected.reserve(input.candidates.candidate_count());
  for(std::size_t i=0;i<input.candidates.candidate_count();++i){const auto value=fixture.replan(i);expected.push_back(fixture.account.statistics().current);}
  auto current=fixture.basis;
  for(std::size_t i=0;i<30;++i) {
    const auto index=i%input.candidates.candidate_count();current=CompiledProgram::replan(current,*input.candidates.candidate(index));
    check(fixture.account.statistics().current==expected[index],"replanning retained a chain of historical physical graphs");
  }
  current={};check(fixture.account.statistics().current==before,"replan replacement churn leaked native state");
  const auto calibration=fixture.replan();program::ReplanLimits limits;limits.physical.work_limit=calibration.work();
  check(CompiledProgram::replan(fixture.basis,*input.candidates.candidate(0),limits).work()==calibration.work(),"exact native lowering work cap changed");
  --*limits.physical.work_limit;bool stopped=false;
  try{static_cast<void>(CompiledProgram::replan(fixture.basis,*input.candidates.candidate(0),limits));}
  catch(const program::ReplanFailure& failure){stopped=failure.fault()==program::ReplanFault::lowering_work;}
  check(stopped,"native lowering ignored one-under structural work cap");
  limits={};limits.physical.identity.work_limit=0;stopped=false;
  try{static_cast<void>(CompiledProgram::replan(fixture.basis,*input.candidates.candidate(0),limits));}
  catch(const program::ReplanFailure& failure){stopped=failure.fault()==program::ReplanFault::identity_work;}
  check(stopped,"native lowering erased finite identity admission");
  if(input.sql)for(const bool binding:{true,false}) {
    limits={};if(binding)limits.binding_replay_work=0;else limits.normalization_work=0;stopped=false;
    try{static_cast<void>(CompiledProgram::replan(fixture.basis,*input.candidates.candidate(0),limits));}
    catch(const program::ReplanFailure& failure){stopped=failure.fault()==(binding?program::ReplanFault::binding_replay_work:program::ReplanFault::normalization_work);}
    check(stopped,"native lowering erased finite normalized source admission");
  }
}
void receiving_account(const Case& input,bool indexed) {
  std::optional<Fixture> target(std::in_place,input,indexed,allowance),source(std::in_place,input,indexed,allowance);
  const auto account=target->account,other=source->account;const auto before=account.statistics(),source_before=other.statistics();
  CompiledProgram held;std::size_t calls=0;
  {s04_alloc::Scope count;held=CompiledProgram::replan_into(account,source->basis,*input.candidates.candidate(0));calls=s04_alloc::calls;}
  check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations &&
      other.statistics().successful_allocations==source_before.successful_allocations,"native lowering charged new storage to the supplied compiler's account");
  const auto expected=std::string(held.physical_sha256());
  {s04_alloc::Scope none(0);target.reset();source.reset();check(held.physical_sha256()==expected && held.validation().valid,"receiving-account graph lost its immutable compiler source");held={};}
  controller_only(account);controller_only(other);
}
std::pair<std::size_t,std::uint64_t> native_admission_copy(const Case& input,bool indexed) {
  std::optional<Fixture> source(std::in_place,input,indexed,allowance);auto original=source->replan();const auto other=source->account;
  const auto expected=image(original);const auto account=resource::MemoryAccount::create(allowance);
  const auto copy=[&](const resource::MemoryAccount& target) {
    storage::IndexWorkAllowance grant(original.options().indexed_storage?original.options().indexed_storage->per_operation:
        storage::IndexWork{UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true);
    return CompiledProgram::freeze(target,original,&grant);
  };
  const auto source_before=other.statistics();const auto before=account.statistics();CompiledProgram held;std::size_t calls=0;
  {s04_alloc::Scope count;held=copy(account);calls=s04_alloc::calls;}
  check(calls>0 && calls<4096 && calls==account.statistics().successful_allocations-before.successful_allocations &&
      other.statistics().successful_allocations==source_before.successful_allocations,"native admission copied through ordinary storage or charged the input owner");
  check(image(held)==expected,"native admission changed a compiled program field");
  const auto old=projections(original),copied=projections(held);check(old.size()==copied.size(),"native admission projection count changed");
  for(std::size_t a=0;a<old.size();++a)for(std::size_t b=0;b<old.size();++b)
    check(old[a]->same_token(*old[b])==copied[a]->same_token(*copied[b]),"native admission changed projection aliasing");
  for(std::size_t point=0;point<=calls;++point) {
    const auto baseline=account.statistics();CompiledProgram value;bool failed=false;std::size_t actual=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{value=copy(account);}catch(const std::bad_alloc&){failed=true;}actual=s04_alloc::calls;}
    if(point<calls) {
      check(failed && actual==point+1 && !value && account.statistics().current==baseline.current,"failed native admission leaked or published partial metadata");value=copy(account);
    }else check(!failed && actual==calls && actual==account.statistics().successful_allocations-baseline.successful_allocations,"native admission fault sweep missed an original-account request");
    check(image(value)==expected && image(held)==expected && image(original)==expected,"native admission failure changed source or prior compiled metadata");
    {s04_alloc::Scope none(0);value={};}account.check_invariants();
  }
  std::uint64_t peak=0;std::size_t pins=0;
  {
    const auto target=resource::MemoryAccount::create(allowance);std::vector<CompiledProgram> values;values.reserve(1024);
    for(std::size_t i=0;i<1024;++i) {
      const auto previous=target.statistics().peak_requested_bytes;auto value=copy(target);const auto next=target.statistics().peak_requested_bytes;
      if(i>0 && next>previous){peak=next;pins=i;break;}values.push_back(std::move(value));
    }
    check(peak>0 && pins>0,"native admission did not cross an actual retained frontier");
  }
  for(const bool exact:{true,false}) {
    const auto target=resource::MemoryAccount::create(exact?peak:peak-1);std::vector<CompiledProgram> values;values.reserve(pins);
    for(std::size_t i=0;i<pins;++i)values.push_back(copy(target));
    const auto baseline=target.statistics().current;bool denied=false;
    try{const auto value=copy(target);check(image(value)==expected,"native admission changed at exact query cap");}
    catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong native admission cap fault");denied=true;}
    check(denied!=exact && target.statistics().current==baseline,"native admission ignored one-under cap or leaked tentative state");
    if(!exact){values.pop_back();const auto retry=copy(target);check(image(retry)==expected && target.statistics().limit_bytes==peak-1,"native admission retry replaced its original grant");}
  }
  {s04_alloc::Scope none(0);original={};source.reset();}controller_only(other);
  check(image(held)==expected,"native admission borrowed an input string/span after source closure");
  {s04_alloc::Scope none(0);held={};}controller_only(account);
  return {calls,peak};
}
}
int main() {
  try {
    const std::array cases{core(),sql(false),sql(true),rich()};
    for(const bool indexed:{false,true})for(std::size_t i=0;i<cases.size();++i) {
      equivalence(cases[i],indexed);requests_and_lifetime(cases[i],indexed);churn_and_work(cases[i],indexed);receiving_account(cases[i],indexed);
      const auto faults=persistent(cases[i],indexed);const auto [peak,pins]=caps(cases[i],indexed);
      const auto [copy_faults,copy_peak]=native_admission_copy(cases[i],indexed);
      std::cout<<(indexed?"indexed":"reference")<<" native replan case="<<i<<" candidates="<<cases[i].candidates.candidate_count()<<" faults="<<faults<<" peak="<<peak<<" pins="<<pins
          <<" admission copy faults="<<copy_faults<<" copy peak="<<copy_peak<<'\n';
    }
    std::cout<<"native candidate lowering: original compiler graph/hash/aliases, actual requests, caps, persistent failures, source lifetime and no history chains passed\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
