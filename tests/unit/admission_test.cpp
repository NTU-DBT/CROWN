#include "crown/frontend/admission.hpp"
#include "crown/frontend/adapter.hpp"
#include "crown/io/admission.hpp"
#include "crown/io/normalization.hpp"
#include "crown/io/recognition.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"

#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::frontend;
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
Catalog catalog() { return {5,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"tag",ScalarType::string}}},
    {"s",{{"y",ScalarType::int64},{"z",ScalarType::int64}}},{"t",{{"x",ScalarType::int64},{"z",ScalarType::int64}}},{"zero",{}}}}; }
Database empty(const Catalog& schema) { return {std::vector<Relation>(schema.tables.size())}; }
Relation snapshot(const AdapterState& state) { return map_sql_result(state.query(),reference::evaluate(state.query().core_catalog,state.query().core,state.logical())); }
AdmissionResult status(std::string_view sql,AdmissionStatus expected,const AdmissionOptions& options={}) {
  auto result=admit_sql(sql,catalog(),options);
  check(result.status==expected,"unexpected admission: "+admission_status_name(result.status)+" for "+std::string(sql)+(result.diagnostic ? " / "+result.diagnostic->code : ""));
  const auto encoded=io::write_admission(result);
  check(encoded.at("admission_scope")=="frontend_and_structure" && encoded.at("execution_status")=="not_lowered","admission cannot claim a lowered runtime");
  if (expected==AdmissionStatus::admitted) check(!result.diagnostic && result.route && result.structure && result.program && result.program->schema_version==2,"admitted result has complete grounded evidence");
  else check(result.diagnostic && !result.route,"rejection retains diagnostic without an admitted route");
  return result;
}
void categories_and_structure() {
  const auto full=status("SELECT DISTINCT r.x,r.y,s.z FROM r JOIN s USING(y)",AdmissionStatus::admitted);
  check(full.route==AdmissionRoute::free_connex && full.structure->query_class==planner::QueryClass::free_connex,"full path admitted");
  const auto endpoints=status("SELECT DISTINCT r.x,s.z FROM r JOIN s USING(y)",AdmissionStatus::non_free_connex);
  check(endpoints.structure->body.acyclic && !endpoints.structure->augmented.acyclic && !endpoints.structure->augmented.failed_core.empty(),"proper endpoint projection exposes the head obstruction");
  const auto cyclic=status("SELECT DISTINCT r.x,r.y,s.z FROM r JOIN s USING(y) JOIN t ON t.x=r.x AND t.z=s.z",AdmissionStatus::cyclic_body);
  check(!cyclic.structure->body.acyclic && cyclic.program->core.atoms.size()==3,"cyclic full head cannot turn the body into a free-connex query");
  const auto contradiction=status("SELECT DISTINCT r.x,r.y,s.z FROM r JOIN s USING(y) JOIN t ON t.x=r.x AND t.z=s.z WHERE FALSE",AdmissionStatus::admitted);
  check(contradiction.route==AdmissionRoute::constant_empty && contradiction.structure->query_class==planner::QueryClass::cyclic,"constant empty route preserves truthful cyclic shape classification");
  static_cast<void>(status("SELECT x FROM r",AdmissionStatus::unsupported_semantics));
  static_cast<void>(status("SELECT DISTINCT r.x FROM r,s WHERE r.x<s.z",AdmissionStatus::unsupported_semantics));
  static_cast<void>(status("SELECT DISTINCT r.x FROM r,s WHERE r.y=s.y OR r.x=s.z",AdmissionStatus::unsupported_semantics));
  static_cast<void>(status("SELECT DISTINCT x FROM r WHERE NOT (x<0) OR tag='keep'",AdmissionStatus::admitted));
  static_cast<void>(status("SELECT DISTINCT absent FROM r",AdmissionStatus::semantic_error));
  static_cast<void>(status("SELECT DISTINCT y FROM r,s",AdmissionStatus::semantic_error));
  static_cast<void>(status("SELECT FROM WHERE",AdmissionStatus::syntax_error));
  static_cast<void>(status("SELECT 1; SELECT 2",AdmissionStatus::syntax_error));
  static_cast<void>(status(std::string("SELECT\0 1",9),AdmissionStatus::syntax_error));
  static_cast<void>(status(std::string(1024*1024+1,' '),AdmissionStatus::resource_limit));
  for (const auto sql : {"SELECT DISTINCT count(*) FROM r","SELECT DISTINCT x+1 FROM r","SELECT DISTINCT x FROM r ORDER BY x",
      "SELECT DISTINCT x FROM r LIMIT 1","SELECT DISTINCT r.x FROM r LEFT JOIN s ON r.y=s.y",
      "WITH q AS (SELECT x FROM r) SELECT DISTINCT x FROM q","SELECT DISTINCT x FROM r UNION SELECT x FROM t",
      "SELECT DISTINCT CAST('2024-01-01' AS timestamp)"}) static_cast<void>(status(sql,AdmissionStatus::unsupported_semantics));
  auto nullable=catalog(); nullable.tables[0].columns[2].nullable=true;
  const auto null_input=admit_sql("SELECT DISTINCT x FROM r",nullable);
  check(null_input.status==AdmissionStatus::unsupported_semantics && null_input.diagnostic->code=="unsupported_nullable_input","nullable unused columns require explicit source policy");
  auto invalid=catalog(); invalid.version=0;
  const auto invalid_catalog=admit_sql("SELECT DISTINCT x FROM r",invalid);
  check(invalid_catalog.status==AdmissionStatus::semantic_error && invalid_catalog.phase=="catalog","library catalog errors retain their phase");
}
void grounding_and_legacy() {
  const auto schema=catalog(); const std::string sql="SELECT DISTINCT r.x,s.z FROM r JOIN s USING(y) WHERE r.x=1";
  const auto admitted=status(sql,AdmissionStatus::admitted);
  check(admitted.program->core.head.size()==1 && std::holds_alternative<ConstantOutput>(admitted.program->outputs[0].value),"fixed column output becomes a constant before free-head recognition");
  auto bound=bind_sql(sql,schema); NormalizeOptions legacy_options; legacy_options.schema_version=1;
  auto old_result=normalize_sql(std::get<BoundSql>(bound),legacy_options); const auto old=std::get<NormalizedSql>(old_result);
  check(planner::analyze(old.core_catalog,old.core).query_class==planner::QueryClass::acyclic_non_free_connex,"frozen legacy reproduces the formerly restrictive classification");
  const auto upgraded=io::upgrade_sql_normalization(old,2);
  check(upgraded.schema_version==2 && io::read_sql_normalization(io::write_sql_normalization(old).dump()).schema_version==1,"v1 replay remains v1; explicit upgrade selects v2");
  check(admit_normalized(old).status==AdmissionStatus::admitted,"legacy import is grounded before admission");
  auto unlimited=old; unlimited.limits.work_limit.reset();
  const auto capped=admit_normalized(unlimited,{}, {0});
  check(capped.status==AdmissionStatus::resource_limit && capped.phase=="normalization" && !capped.program && capped.limits.normalization.work_limit==0,
        "legacy stored unlimited cannot disable the independent grounding host cap");
  auto data=empty(schema); const Row first{n(1),n(7),s("a")},second{n(1),n(7),s("b")};
  data.tables[0]={first,second,{n(2),n(7),s("filtered")}}; data.tables[1]={{n(7),n(9)}};
  AdapterState v1(old,data),v2(upgraded,data);
  check(snapshot(v1)==Relation{{n(1),n(9)}} && snapshot(v1)==snapshot(v2),"constant grounding preserves expected SQL answer and physical derivations");
  const Query handwritten{{{"y",ScalarType::int64},{"z",ScalarType::int64}},
      {{"r",TableId{0},{Value{n(1)},VariableId{0},IgnoredColumn{}}},{"s",TableId{1},{VariableId{0},VariableId{1}}}},{{VariableId{1},"z"}},false};
  check(reference::evaluate(schema,handwritten,data)==Relation{{n(9)}},"independent grounded CQ agrees");
  for (const auto& update : std::vector<PhysicalSetUpdate>{{1,TableId{0},SetOperation::erase,first},{2,TableId{0},SetOperation::erase,second}}) {
    static_cast<void>(v1.apply(update)); static_cast<void>(v2.apply(update)); check(snapshot(v1)==snapshot(v2),"v1->v2 migration preserves last-support deletion");
  }
  check(snapshot(v2).empty(),"last source support withdraws constant-head row");
  const auto across=status("SELECT DISTINCT r.x,s.z FROM r JOIN s USING(y) WHERE r.y=7",AdmissionStatus::admitted);
  check(across.program->adapters[0].constant_columns.size()==1 && across.program->adapters[1].constant_columns.size()==1,"constant propagates to every occurrence in its final equality class");
  data.tables[1]={{n(8),n(9)}}; AdapterState unmatched(*across.program,data);
  check(snapshot(unmatched).empty(),"a formerly cross-relation constant equality is checked on both inputs");
  const auto self=status("SELECT DISTINCT l.x,q.x FROM r l,r q WHERE l.x=q.x AND l.x=1",AdmissionStatus::admitted);
  data=empty(schema); data.tables[0]={first,second}; AdapterState aliases(*self.program,data);
  check(aliases.supports()[0].at(Row{})==2 && aliases.supports()[1].at(Row{})==2 && snapshot(aliases)==Relation{{n(1),n(1)}},"grounded self-join aliases retain separate nullary support counts");
  static_cast<void>(aliases.apply({1,TableId{0},SetOperation::erase,first})); check(snapshot(aliases)==Relation{{n(1),n(1)}},"one alias support survives a physical deletion");
  static_cast<void>(aliases.apply({2,TableId{0},SetOperation::erase,second})); check(snapshot(aliases).empty(),"both aliases withdraw only at their final physical support");
}
void limits_parameters_and_ownership() {
  const std::string sql="SELECT DISTINCT r.x,r.y,s.z FROM r JOIN s USING(y)";
  AdmissionOptions options; options.binding.limits.work_limit=0;
  check(status(sql,AdmissionStatus::resource_limit,options).phase=="binding","binding limit phase");
  options={}; options.normalization.work_limit=0;
  check(status(sql,AdmissionStatus::resource_limit,options).phase=="normalization","normalization limit phase");
  options={}; options.recognition.work_limit=0;
  const auto stopped=status(sql,AdmissionStatus::resource_limit,options);
  check(stopped.phase=="recognition" && stopped.program && !stopped.structure && stopped.work.recognition==0,"exhaustion retains no partial classification");
  const auto complete=status(sql,AdmissionStatus::admitted);
  const auto work=*complete.work.recognition;
  const auto exact=planner::analyze_bounded(complete.program->core_catalog,complete.program->core,{work});
  const auto short_run=planner::analyze_bounded(complete.program->core_catalog,complete.program->core,{work-1});
  check(exact.analysis && exact.work==work && !short_run.analysis && short_run.work==work-1,"shared body/head GYO budget has an exact deterministic boundary");
  check(io::write_structural_analysis(*exact.analysis,complete.program->core)==io::write_structural_analysis(planner::analyze(complete.program->core_catalog,complete.program->core),complete.program->core),"bounded and legacy unlimited GYO produce identical complete witnesses");
  options={}; options.binding.parameters={{"p",ScalarType::int64,true}}; options.parameters={n(1)};
  const auto parameter=status("SELECT DISTINCT r.x,s.z FROM r JOIN s USING(y) WHERE r.x=$1",AdmissionStatus::admitted,options);
  check(parameter.program->core.head.size()==1,"typed concrete parameters participate in constant grounding");
  options.parameters={std::nullopt};
  check(status("SELECT EXISTS(SELECT NULL FROM r WHERE x=$1)",AdmissionStatus::admitted,options).route==AdmissionRoute::constant_empty,"NULL equality gives explicit empty-core route");
  options.parameters={}; check(status("SELECT DISTINCT x FROM r WHERE x=$1",AdmissionStatus::semantic_error,options).phase=="parameters","missing values remain semantic parameter errors");
  const auto config=io::read_admission_options(R"({"schema_version":1,"parameter_types":[{"type":"int64"}],"parameter_values":[1],"limits":{"recognition":{"work_limit":0}}})");
  check(config.parameters.size()==1 && config.recognition.work_limit==0,"strict options carry specialization and independent limits");
  auto schema=catalog(); std::string owned_sql=sql; auto owned=admit_sql(owned_sql,schema); schema.tables.clear(); owned_sql.clear();
  auto copied=owned; auto moved=std::move(copied);
  check(moved.program->binding.catalog.tables.size()==4 && !owned.program->binding.source.empty(),"admission results own program, catalog, source and evidence across copies/moves");
  Catalog wide{1,{{"wide",{}}}};
  for (std::size_t i=0;i<70;++i) wide.tables[0].columns.push_back({"c"+std::to_string(i),ScalarType::int64});
  check(admit_sql("SELECT DISTINCT * FROM wide",wide).status==AdmissionStatus::admitted,"admission has no fixed 64-column structural cap");
  static_cast<void>(status("SELECT EXISTS(SELECT * FROM zero)",AdmissionStatus::admitted));
  static_cast<void>(status("SELECT EXISTS(SELECT NULL)",AdmissionStatus::admitted));
}
}  // namespace
int main() {
  try {
    categories_and_structure(); grounding_and_legacy(); limits_parameters_and_ownership();
    std::cout << "SQL admission, grounded constants, legacy migration and bounded recognition checks passed\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
