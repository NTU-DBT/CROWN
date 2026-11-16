#include "candidate_binding.hpp"
#include "ranking_detail.hpp"
#include "frozen_binding_v2.hpp"
#include "crown/planner/lower.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/io/ingest.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
void check(bool x,const char* message){if(!x){throw std::runtime_error(message);}}
void compare(const Catalog& c,const Query& q){
  const auto old=planner::frozen_binding_v2::binding_bytes(c,q);
  check(old==planner::binding_detail::encode(c,q),"P07 binding bytes changed");
  planner::ranking::Limits limits;limits.binding_key_bytes=static_cast<std::uint64_t>(old.size());limits.payload_bytes=static_cast<std::uint64_t>(old.size());
  planner::ranking::detail::Budget budget(limits);const auto actual=planner::ranking::detail::binding(c,q,budget);
  check(actual==old && budget.usage.payload_bytes==old.size(),"exact binding cap");
  auto low=limits;low.payload_bytes-=1;planner::ranking::detail::Budget stopped(low);bool hit=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,stopped));}
  catch(const planner::ranking::detail::Failure& e){hit=e.stop==planner::ranking::Stop::byte_limit;}
  check(hit && stopped.usage.binding_key_bytes<=low.payload_bytes,"binding allocated beyond residual payload admission");
  limits.payload_bytes+=19;planner::ranking::Usage prior;prior.payload_bytes=20;
  planner::ranking::detail::Budget residual(limits,prior);hit=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,residual));}
  catch(const planner::ranking::detail::Failure& e){hit=e.stop==planner::ranking::Stop::byte_limit;}
  check(hit && residual.usage.payload_bytes==20,"prior payload was not protected");
}
void native_binding(){
  CompiledProgram native;std::string expected;
  {
    Table table{"values",{{"key",ScalarType::int64},{"i",ScalarType::int64},
      {"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},
      {"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}},
      {"unused",ScalarType::boolean}}};
    table.source_schema_version=13;
    table.constraints={UniqueConstraint{"key",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"self",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::untrusted},
      ForeignKeyConstraint{"parent",{ColumnId{0}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced}};
    table.statistics.row_count=997;table.statistics.distinct_counts={{{ColumnId{0}},991}};
    table.key_hints={{{ColumnId{1}},std::string("binary\0hint",11)}};
    Table parent{"parent",{{"key",ScalarType::int64}}};
    parent.constraints={UniqueConstraint{"key",{ColumnId{0}},ConstraintStatus::enforced}};
    Catalog catalog{7,{table,parent}};
    Query query{{{"x",ScalarType::int64}},{{"v",TableId{0},{VariableId{0},Value{INT64_MIN},
      Value{std::string("a\0b",3)},Value{true},Value{Date::parse("0001-01-01")},
      Value{Decimal::parse("-99999999999999999999999999.123456789012")},IgnoredColumn{}}}},
      {{VariableId{0},"first"},{VariableId{0},"again"}},false};
    const FreeConnexTree tree{NodeId{0},{{"v",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
    expected=planner::frozen_binding_v2::binding_bytes(catalog,query);
    native=CompiledProgram::standalone(planner::lower_tree(catalog,query,tree));
    const Row row{std::int64_t{1},INT64_MIN,std::string("a\0b",3),true,Date::parse("0001-01-01"),
      Decimal::parse("-99999999999999999999999999.123456789012"),false};
    const Database valid{{Relation{row},Relation{Row{std::int64_t{1}}}}};
    const io::InputEvent event{{1,TableId{0},SetOperation::insert,row},{}};
    check(io::input_catalog_sha256(catalog)==io::input_catalog_sha256(native.catalog()) &&
      io::write_input_json(event,catalog)==io::write_input_json(event,native.catalog()) &&
      io::write_input_binary(event,catalog)==io::write_input_binary(event,native.catalog()),
      "native wire encoding changed typed scalars, constraints, statistics or binary metadata");
    validate_database(catalog,valid);validate_database(native.catalog(),valid);
    check(catalog::find_table(native.catalog(),"values")==TableId{0} && catalog::requires_format3(native.catalog()),
      "native catalog lookup or format metadata changed");
    const auto failure=[](const auto& schema,const Database& database){
      try{validate_database(schema,database);}
      catch(const Error& error){return std::pair<std::string,std::string>{error.code(),error.what()};}
      throw std::runtime_error("invalid database accepted by catalog validator");
    };
    for(unsigned change=0;change<5;++change){
      auto database=valid;auto bad=row;
      if(change==0)bad.pop_back();
      if(change==1)bad[0]=std::string("wrong type");
      if(change==2)bad[5]=Decimal::parse("1.1234567890123");
      if(change==3)bad[6]=true;
      if(change<4){if(change<3)database.tables[0].clear();database.tables[0].insert(bad);}
      else database.tables[1].clear();
      const auto old=failure(catalog,database);const auto actual=failure(native.catalog(),database);
      const auto code=change<2?"invalid_update":change==2?"scalar_overflow":"constraint_violation";
      check(old.first==code && actual==old,"native database validation changed a shape, scalar or constraint failure");
    }
  }
  check(planner::binding_detail::encode(native.catalog(),native.query())==expected,
    "native binding differs from frozen compiler format after source destruction");
  planner::ranking::Limits limits;limits.binding_key_bytes=expected.size();limits.payload_bytes=expected.size();
  planner::ranking::detail::Budget exact(limits);
  check(planner::ranking::detail::binding(native.catalog(),native.query(),exact)==expected &&
    exact.usage.payload_bytes==expected.size(),"native exact binding admission changed");
  --limits.payload_bytes;planner::ranking::detail::Budget low(limits);bool stopped=false;
  try{static_cast<void>(planner::ranking::detail::binding(native.catalog(),native.query(),low));}
  catch(const planner::ranking::detail::Failure& error){stopped=error.stop==planner::ranking::Stop::byte_limit;}
  check(stopped,"native binding escaped one-under admission");
}
}
int main(){try{
  Catalog c;Query q;compare(c,q);
  c.version=UINT64_MAX;
  const std::string raw("a\0\xff",3);
  Table t{raw,{{raw,ScalarType::string},{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}}}};
  t.source_schema_version=UINT64_MAX;t.constraints.push_back(UniqueConstraint{raw,{ColumnId{1}},ConstraintStatus::enforced});
  t.constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{0},{ColumnId{1}},ConstraintStatus::untrusted});
  t.statistics.row_count=UINT64_MAX;t.statistics.distinct_counts.push_back({{ColumnId{0},ColumnId{0}},UINT64_MAX});t.key_hints.push_back({{ColumnId{1}},raw});c.tables.push_back(t);
  q.variables={{raw,ScalarType::string}};
  q.atoms.push_back({raw,TableId{0},{VariableId{0},Value{INT64_MIN},Value{true},Value{Date::parse("0001-01-01")},Value{Decimal::parse("-99999999999999999999999999.123456789012")}}});
  q.atoms.push_back({"alias",TableId{0},{Value{raw},IgnoredColumn{},Value{false},Value{Date::parse("9999-12-31")},Value{Decimal::parse("0.00000000000000000000000000000000000001")}}});
  q.head={{VariableId{0},raw},{VariableId{0},"again"}};compare(c,q);
  auto changed=c;changed.tables[0].statistics.row_count=17;
  check(planner::binding_detail::encode(changed,q)!=planner::binding_detail::encode(c,q),"catalog statistics erased from proof namespace");
  q.contradiction=true;compare(c,q);
  planner::ranking::Limits zero;zero.payload_bytes=0;planner::ranking::detail::Budget b(zero);bool blocked=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,b));}catch(const planner::ranking::detail::Failure& e){blocked=e.stop==planner::ranking::Stop::byte_limit;}
  check(blocked && b.usage.binding_key_bytes==0,"prefix not admitted before allocation");
  native_binding();
  std::cout<<"C02 binding: exact predecessor bytes and pre-allocation caps passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
