#include "candidate_binding.hpp"
#include "ranking_detail.hpp"
#include "frozen_binding_v2.hpp"
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
  std::cout<<"C02 binding: exact predecessor bytes and pre-allocation caps passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
