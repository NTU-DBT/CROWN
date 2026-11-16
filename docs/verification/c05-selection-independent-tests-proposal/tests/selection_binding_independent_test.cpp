#include "selection_independent_fixture.hpp"
#include "selection_detail.hpp"

#include <functional>
#include <iostream>
#include <limits>
#include <string_view>

namespace {
using namespace c05_independent;
namespace wire=crown::planner::selection::detail;

// An independent byte-vector writer, not the production string visitor. Word
// digits are obtained by division, then copied most-significant first. The
// expected records below are literal programs over this tiny framing alphabet.
struct Bytes {
  std::vector<unsigned char> data;
  explicit Bytes(std::string_view prefix){raw(prefix);}
  void raw(std::string_view value){for(char c:value)data.push_back(static_cast<unsigned char>(c));}
  void tag(char value){data.push_back(static_cast<unsigned char>(value));}
  void word(std::uint64_t value){
    std::array<unsigned char,8> digits{};
    for(std::size_t i=digits.size();i>0;--i){digits[i-1]=static_cast<unsigned char>(value%256U);value/=256U;}
    data.insert(data.end(),digits.begin(),digits.end());
  }
  void u(std::uint64_t value){tag('U');word(value);}
  void i(std::int64_t value){tag('I');word(static_cast<std::uint64_t>(value));}
  void e(std::uint64_t value){tag('E');word(value);}
  void b(bool value){tag('B');data.push_back(static_cast<unsigned char>(value?1U:0U));}
  void p(bool value){tag('P');data.push_back(static_cast<unsigned char>(value?1U:0U));}
  void a(std::uint64_t count){tag('A');word(count);}
  void text(std::string_view value){tag('S');word(static_cast<std::uint64_t>(value.size()));raw(value);}
  void r(std::string_view name){tag('R');text(name);}
};
bool equals(const std::string& actual,const Bytes& expected){
  if(actual.size()!=expected.data.size())return false;
  for(std::size_t i=0;i<actual.size();++i)
    if(static_cast<unsigned char>(actual[i])!=expected.data[i])return false;
  return true;
}
std::string string_of(const Bytes& value){
  std::string result;result.reserve(value.data.size());
  for(auto byte:value.data)result.push_back(static_cast<char>(byte));
  return result;
}
std::string scalar(const Value& value){wire::Budget b(rank::Limits{});return wire::scalar_binding_record(value,b);}
std::string tree(const FreeConnexTree& value){wire::Budget b(rank::Limits{});return wire::tree_binding_record(value,b);}
std::string core(const Catalog& catalog,const Query& query){wire::Budget b(rank::Limits{});return wire::core_binding_record(catalog,query,b);}
std::string program(const frontend::NormalizedSql& value){wire::Budget b(rank::Limits{});return wire::program_binding_record(value,b);}

void scalar_literals(){
  const auto integer=[](std::int64_t value){Bytes expected("CROWN-SELECTION-SCALAR;1;");expected.r("value");expected.u(0);expected.i(value);return expected;};
  for(const auto value:{std::int64_t{0},std::int64_t{1},std::int64_t{-1},std::numeric_limits<std::int64_t>::min(),std::numeric_limits<std::int64_t>::max()})
    check(equals(scalar(Value{value}),integer(value)),"signed scalar differs from independent modulo-2^64 framing");
  const std::string binary{"a\0\x80\xffz",5};
  for(const auto& value:std::array<std::string,3>{std::string{},std::string{"\0",1},binary}){
    Bytes expected("CROWN-SELECTION-SCALAR;1;");expected.r("value");expected.u(1);expected.text(value);
    check(equals(scalar(Value{value}),expected),"binary string framing lost a byte or length");
  }
  for(const bool value:{false,true}){
    Bytes expected("CROWN-SELECTION-SCALAR;1;");expected.r("value");expected.u(2);expected.b(value);
    check(equals(scalar(Value{value}),expected),"Boolean tag/byte mismatch");
  }
  for(const auto& [text,days]:std::array<std::pair<const char*,std::int64_t>,2>{{{"1970-01-01",0},{"1969-12-31",-1}}}){
    Bytes expected("CROWN-SELECTION-SCALAR;1;");expected.r("value");expected.u(3);expected.i(days);
    check(equals(scalar(Value{Date::parse(text)}),expected) && scalar(Value{Date::parse(text)})!=scalar(Value{days}),
          "Date framing collapsed into an integer day count");
  }
  for(const auto& [text,canonical]:std::array<std::pair<const char*,const char*>,4>{{
      {"-0001.2300","-1.23"},{"-0.000","0"},{"12345678901234567890123456789012345678","12345678901234567890123456789012345678"},
      {"0.00000000000000000000000000000000000001","0.00000000000000000000000000000000000001"}}}){
    Bytes expected("CROWN-SELECTION-SCALAR;1;");expected.r("value");expected.u(4);expected.text(canonical);
    const auto actual=scalar(Value{Decimal::parse(text)});
    check(equals(actual,expected) && actual==scalar(Value{Decimal::parse(canonical)}) && actual!=scalar(Value{std::string(canonical)}),
          "canonical Decimal framing lost type, sign or significant scale");
  }
}

FreeConnexTree raw_fixture(){
  FreeConnexTree value;
  value.root=NodeId{1};
  value.nodes={{std::string{"a\0",2},NodeKind::native,{VariableId{0},VariableId{2}},{},3,VariableSet{}},
      {std::string{"g\xff",2},NodeKind::generalized,{VariableId{2}},{NodeId{0},NodeId{0}},std::nullopt,std::nullopt}};
  value.claimed_connex=std::vector<NodeId>{NodeId{1},NodeId{0}};value.claimed_native_height=2;
  return value;
}
void tree_literals_and_mutations(){
  const auto value=raw_fixture();
  Bytes expected("CROWN-SELECTION-TREE;1;");
  expected.r("raw-tree");expected.p(true);expected.u(1);expected.a(2);
  expected.r("raw-node");expected.text(std::string{"a\0",2});expected.e(0);expected.a(2);expected.u(0);expected.u(2);
  expected.a(0);expected.p(true);expected.u(3);expected.p(true);expected.a(0);
  expected.r("raw-node");expected.text(std::string{"g\xff",2});expected.e(1);expected.a(1);expected.u(2);
  expected.a(2);expected.u(0);expected.u(0);expected.p(false);expected.p(false);
  expected.p(true);expected.a(2);expected.u(1);expected.u(0);expected.p(true);expected.u(2);
  const auto baseline=tree(value);
  check(equals(baseline,expected),"literal raw-tree bytes differ from independent framed vector");
  const std::vector<std::function<void(FreeConnexTree&)>> mutations{
    [](auto& x){x.root.reset();},[](auto& x){x.root=NodeId{0};},[](auto& x){x.nodes[0].id.push_back('x');},
    [](auto& x){x.nodes[0].kind=NodeKind::generalized;},[](auto& x){x.nodes[0].scope.insert(VariableId{1});},
    [](auto& x){x.nodes[1].children.push_back(NodeId{1});},[](auto& x){x.nodes[1].children[0]=NodeId{1};},
    [](auto& x){x.nodes[0].occurrence.reset();},[](auto& x){x.nodes[0].occurrence=4;},
    [](auto& x){x.nodes[0].claimed_separator.reset();},[](auto& x){x.nodes[0].claimed_separator=VariableSet{VariableId{2}};},
    [](auto& x){x.claimed_connex.reset();},[](auto& x){std::reverse(x.claimed_connex->begin(),x.claimed_connex->end());},
    [](auto& x){x.claimed_native_height.reset();},[](auto& x){x.claimed_native_height=3;},
    [](auto& x){std::reverse(x.nodes.begin(),x.nodes.end());},[](auto& x){x.nodes.pop_back();}};
  for(const auto& change:mutations){auto copy=value;change(copy);check(tree(copy)!=baseline,"raw-tree field mutation collapsed");}
  Bytes empty("CROWN-SELECTION-TREE;1;");empty.r("raw-tree");empty.p(false);empty.a(0);empty.p(false);empty.p(false);
  check(equals(tree(FreeConnexTree{}),empty),"empty/absent tree framing differs");
}

std::pair<Catalog,Query> core_fixture(){
  Catalog catalog{9,{{std::string{"tab\0",4},{{"x",ScalarType::int64},{"blob",ScalarType::string},
      {"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{8,2}},{"flag",ScalarType::boolean}},7,
      {UniqueConstraint{"uq",{ColumnId{0}},ConstraintStatus::enforced},
       ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::untrusted}},
      {5,{{{ColumnId{0},ColumnId{0}},3}}},{{{},"advisory"}}}}};
  Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},Value{std::string{"\0\xff",2}},
      Value{Decimal::parse("1.20")},IgnoredColumn{}}}},{{VariableId{0},"first"},{VariableId{0},"again"}},false};
  return {catalog,query};
}
Bytes literal_core_inner(){
  Bytes b("CROWN-CANDIDATE-BINDING;2;");b.r("catalog");b.u(9);b.a(1);b.r("table");b.text(std::string{"tab\0",4});b.a(4);
  for(const auto& [name,type]:std::array<std::pair<const char*,std::uint64_t>,4>{{{"x",0},{"blob",1},{"amount",4},{"flag",2}}}){
    b.r("column");b.text(name);b.e(type);b.b(false);b.e(0);b.p(type==4);
    if(type==4){b.r("decimal_spec");b.u(8);b.u(2);}
  }
  b.u(7);b.a(2);b.r("unique_constraint");b.text("uq");b.a(1);b.u(0);b.e(0);
  b.r("foreign_key_constraint");b.text("fk");b.a(1);b.u(0);b.u(0);b.a(1);b.u(0);b.e(1);
  b.r("table_statistics");b.p(true);b.u(5);b.a(1);b.r("distinct_estimate");b.a(2);b.u(0);b.u(0);b.u(3);
  b.a(1);b.r("key_hint");b.a(0);b.text("advisory");
  b.r("query");b.a(1);b.r("variable");b.text("x");b.e(0);b.a(1);b.r("atom");b.text("r");b.u(0);b.a(4);
  b.r("term");b.u(0);b.u(0);b.r("term");b.u(1);b.r("value");b.u(1);b.text(std::string{"\0\xff",2});
  b.r("term");b.u(1);b.r("value");b.u(4);b.text("1.2");b.r("term");b.u(2);
  b.a(2);b.r("output");b.u(0);b.text("first");b.r("output");b.u(0);b.text("again");b.b(false);
  return b;
}
void core_literals_and_mutations(){
  const auto [catalog,query]=core_fixture();
  Bytes expected("CROWN-SELECTION-CORE;1;");expected.r("candidate-binding-v2");expected.text(string_of(literal_core_inner()));
  const auto baseline=core(catalog,query);
  check(equals(baseline,expected),"nested literal core bytes differ from independent P07-v2 framing");
  using Pair=std::pair<Catalog,Query>;
  const std::vector<std::function<void(Pair&)>> mutations{
    [](auto& x){++x.first.version;},[](auto& x){x.first.tables[0].name.push_back('x');},
    [](auto& x){++x.first.tables[0].source_schema_version;},[](auto& x){x.first.tables[0].columns[0].name="other";},
    [](auto& x){x.first.tables[0].columns[0].type=ScalarType::date;},[](auto& x){x.first.tables[0].columns[0].nullable=true;},
    [](auto& x){++x.first.tables[0].columns[2].decimal->precision;},[](auto& x){++x.first.tables[0].columns[2].decimal->scale;},
    [](auto& x){x.first.tables[0].columns[2].decimal.reset();},[](auto& x){std::reverse(x.first.tables[0].columns.begin(),x.first.tables[0].columns.end());},
    [](auto& x){std::get<UniqueConstraint>(x.first.tables[0].constraints[0]).name="other";},
    [](auto& x){std::get<UniqueConstraint>(x.first.tables[0].constraints[0]).columns.push_back(ColumnId{1});},
    [](auto& x){std::get<UniqueConstraint>(x.first.tables[0].constraints[0]).status=ConstraintStatus::untrusted;},
    [](auto& x){std::get<ForeignKeyConstraint>(x.first.tables[0].constraints[1]).name="other";},
    [](auto& x){std::get<ForeignKeyConstraint>(x.first.tables[0].constraints[1]).columns.push_back(ColumnId{1});},
    [](auto& x){std::get<ForeignKeyConstraint>(x.first.tables[0].constraints[1]).referenced_table=TableId{1};},
    [](auto& x){std::get<ForeignKeyConstraint>(x.first.tables[0].constraints[1]).referenced_columns.push_back(ColumnId{1});},
    [](auto& x){std::get<ForeignKeyConstraint>(x.first.tables[0].constraints[1]).status=ConstraintStatus::enforced;},
    [](auto& x){std::reverse(x.first.tables[0].constraints.begin(),x.first.tables[0].constraints.end());},
    [](auto& x){x.first.tables[0].statistics.row_count.reset();},[](auto& x){++*x.first.tables[0].statistics.row_count;},
    [](auto& x){x.first.tables[0].statistics.distinct_counts[0].columns.pop_back();},
    [](auto& x){++x.first.tables[0].statistics.distinct_counts[0].estimate;},
    [](auto& x){x.first.tables[0].key_hints[0].columns.push_back(ColumnId{0});},
    [](auto& x){x.first.tables[0].key_hints[0].reason="different";},
    [](auto& x){x.second.variables[0].name="other";},[](auto& x){x.second.variables[0].type=ScalarType::date;},
    [](auto& x){x.second.atoms[0].occurrence="alias";},[](auto& x){x.second.atoms[0].table=TableId{1};},
    [](auto& x){x.second.atoms[0].terms[0]=VariableId{1};},
    [](auto& x){auto& v=x.second.atoms[0].terms[1].template emplace<Value>(std::in_place_type<std::string>);std::get<std::string>(v).assign("\xff\0",2);},
    [](auto& x){x.second.atoms[0].terms[2].template emplace<Value>(std::in_place_type<Decimal>,Decimal::parse("1.21"));},
    [](auto& x){x.second.atoms[0].terms[3].template emplace<Value>(std::in_place_type<bool>,true);},
    [](auto& x){x.second.head[0].variable=VariableId{1};},[](auto& x){x.second.head[0].alias="different";},
    [](auto& x){std::reverse(x.second.head.begin(),x.second.head.end());},[](auto& x){x.second.head.clear();},
    [](auto& x){x.second.contradiction=true;}};
  for(const auto& change:mutations){auto value=std::make_pair(catalog,query);change(value);check(core(value.first,value.second)!=baseline,"core record field mutation collapsed");}
}

frontend::NormalizedSql program_fixture(){
  const auto [catalog,query]=core_fixture();
  frontend::NormalizedSql x;x.binding.source="SELECT : diagnostic bytes only";x.binding.catalog=catalog;
  x.binding.parameters={{frontend::SqlKind::decimal,true,DecimalSpec{9,3}}};
  x.binding.semantics=frontend::SqlSemantics::set;x.binding.inner_semantics=frontend::SqlSemantics::bag;
  x.binding.wrapper=frontend::SqlWrapper::exists;x.binding.wrapper_alias="exists-name";
  x.binding.occurrences={{TableId{0},"alias",{"x","blob"},11,true}};
  x.binding.expressions={
      {{frontend::SqlKind::int64,false,{}},frontend::BoundColumn{OccurrenceId{0},ColumnId{0}},12},
      {{frontend::SqlKind::string,true,{}},frontend::BoundLiteral{Value{std::string{"\0\xff",2}}},13},
      {{frontend::SqlKind::decimal,true,DecimalSpec{9,3}},frontend::BoundParameter{1},14},
      {{frontend::SqlKind::boolean,false,{}},frontend::BoundOperation{frontend::SqlOperator::equal,{{0},{2}}},15}};
  x.binding.predicates={{3}};x.binding.outputs={{"a",{0}},{"b",{1}}};x.binding.limits={123,456,78};x.binding.work=90;
  x.parameters={std::nullopt,Value{Decimal::parse("1.2")}};x.constants={Value{std::string{"\0",1}},std::nullopt};
  x.core_catalog=catalog;x.core=query;
  x.adapters={{OccurrenceId{0},TableId{0},{{3}},{{0}},{{ColumnId{0},ColumnId{1}}},
      {VariableId{0},std::nullopt},{{VariableId{0},{0}}},{{0},{1},{3}},{{ColumnId{1},Value{std::string{"\xff",1}}}}};
  x.base_routes={{OccurrenceId{0},OccurrenceId{1}},{}};
  x.outputs={{"core",{frontend::SqlKind::int64,false,{}},frontend::CoreOutput{0}},
      {"constant",{frontend::SqlKind::decimal,false,DecimalSpec{9,3}},frontend::ConstantOutput{Value{Decimal::parse("1.2")}}}};
  x.limits.work_limit=321;x.work=91;x.schema_version=2;return x;
}
void normalized_field_mutations(){
  // This is a deliberately rich byte-record fixture, not an admitted SQL
  // program. No lowering, proof constructor, selection or cache sees it.
  const auto original=program_fixture();const auto baseline=program(original);
  using F=std::function<void(frontend::NormalizedSql&)>;
  const std::vector<F> mutations{
    [](auto& x){x.binding.source.push_back(' ');},[](auto& x){++x.binding.catalog.version;},
    [](auto& x){x.binding.parameters[0].kind=frontend::SqlKind::string;},[](auto& x){x.binding.parameters[0].nullable=false;},
    [](auto& x){++x.binding.parameters[0].decimal->precision;},[](auto& x){++x.binding.parameters[0].decimal->scale;},
    [](auto& x){x.binding.parameters[0].decimal.reset();},[](auto& x){x.binding.semantics=frontend::SqlSemantics::bag;},
    [](auto& x){x.binding.inner_semantics.reset();},[](auto& x){x.binding.inner_semantics=frontend::SqlSemantics::set;},
    [](auto& x){x.binding.wrapper=frontend::SqlWrapper::rows;},[](auto& x){x.binding.wrapper_alias="changed";},
    [](auto& x){x.binding.occurrences[0].table=TableId{1};},[](auto& x){x.binding.occurrences[0].alias="changed";},
    [](auto& x){x.binding.occurrences[0].column_names[0]="changed";},[](auto& x){std::reverse(x.binding.occurrences[0].column_names.begin(),x.binding.occurrences[0].column_names.end());},
    [](auto& x){x.binding.occurrences[0].location.reset();},[](auto& x){++*x.binding.occurrences[0].location;},
    [](auto& x){x.binding.occurrences[0].include_descendants=false;},
    [](auto& x){x.binding.expressions[0].type.kind=frontend::SqlKind::date;},[](auto& x){x.binding.expressions[0].type.nullable=true;},
    [](auto& x){++x.binding.expressions[2].type.decimal->precision;},[](auto& x){++x.binding.expressions[2].type.decimal->scale;},
    [](auto& x){x.binding.expressions[2].type.decimal.reset();},
    [](auto& x){std::get<frontend::BoundColumn>(x.binding.expressions[0].node).occurrence=OccurrenceId{1};},
    [](auto& x){std::get<frontend::BoundColumn>(x.binding.expressions[0].node).column=ColumnId{1};},
    [](auto& x){std::get<frontend::BoundLiteral>(x.binding.expressions[1].node).value.reset();},
    [](auto& x){std::get<frontend::BoundLiteral>(x.binding.expressions[1].node).value=Value{std::string{}};},
    [](auto& x){++std::get<frontend::BoundParameter>(x.binding.expressions[2].node).number;},
    [](auto& x){std::get<frontend::BoundOperation>(x.binding.expressions[3].node).operation=frontend::SqlOperator::not_equal;},
    [](auto& x){std::reverse(std::get<frontend::BoundOperation>(x.binding.expressions[3].node).arguments.begin(),std::get<frontend::BoundOperation>(x.binding.expressions[3].node).arguments.end());},
    [](auto& x){x.binding.expressions[0].location.reset();},[](auto& x){++*x.binding.expressions[0].location;},
    [](auto& x){x.binding.expressions[0].node=frontend::BoundParameter{0};},
    [](auto& x){x.binding.predicates[0]={2};},[](auto& x){x.binding.outputs[0].name="changed";},
    [](auto& x){x.binding.outputs[0].expression={1};},[](auto& x){std::reverse(x.binding.outputs.begin(),x.binding.outputs.end());},
    [](auto& x){x.binding.limits.work_limit.reset();},[](auto& x){++*x.binding.limits.work_limit;},
    [](auto& x){++x.binding.limits.expression_limit;},[](auto& x){++x.binding.limits.recursion_limit;},[](auto& x){++x.binding.work;},
    [](auto& x){x.parameters[0]=Value{std::int64_t{0}};},[](auto& x){x.parameters[1]=Value{Decimal::parse("1.21")};},
    [](auto& x){std::reverse(x.parameters.begin(),x.parameters.end());},[](auto& x){x.constants[0].reset();},
    [](auto& x){x.constants[1]=Value{false};},[](auto& x){++x.core_catalog.version;},[](auto& x){x.core.head[0].alias="changed";},
    [](auto& x){x.adapters[0].occurrence=OccurrenceId{1};},[](auto& x){x.adapters[0].base=TableId{1};},
    [](auto& x){x.adapters[0].predicates[0]={2};},[](auto& x){x.adapters[0].non_null_columns[0]=ColumnId{1};},
    [](auto& x){x.adapters[0].equal_columns[0].left=ColumnId{1};},[](auto& x){x.adapters[0].equal_columns[0].right=ColumnId{0};},
    [](auto& x){x.adapters[0].column_classes[0].reset();},[](auto& x){x.adapters[0].column_classes[1]=VariableId{0};},
    [](auto& x){x.adapters[0].projection[0].variable=VariableId{1};},[](auto& x){x.adapters[0].projection[0].expression={1};},
    [](auto& x){std::reverse(x.adapters[0].program.begin(),x.adapters[0].program.end());},
    [](auto& x){x.adapters[0].constant_columns[0].column=ColumnId{0};},
    [](auto& x){x.adapters[0].constant_columns[0].value=Value{std::string{"\0",1}};},
    [](auto& x){std::reverse(x.base_routes[0].begin(),x.base_routes[0].end());},[](auto& x){x.base_routes[1].push_back(OccurrenceId{0});},
    [](auto& x){x.outputs[0].name="changed";},[](auto& x){x.outputs[0].type.kind=frontend::SqlKind::date;},
    [](auto& x){x.outputs[0].type.nullable=true;},[](auto& x){++x.outputs[1].type.decimal->precision;},
    [](auto& x){++x.outputs[1].type.decimal->scale;},[](auto& x){x.outputs[1].type.decimal.reset();},
    [](auto& x){++std::get<frontend::CoreOutput>(x.outputs[0].value).column;},
    [](auto& x){std::get<frontend::ConstantOutput>(x.outputs[1].value).value=Value{Decimal::parse("1.21")};},
    [](auto& x){x.outputs[0].value=frontend::ConstantOutput{Value{std::int64_t{0}}};},
    [](auto& x){std::reverse(x.outputs.begin(),x.outputs.end());},[](auto& x){x.limits.work_limit.reset();},
    [](auto& x){++*x.limits.work_limit;},[](auto& x){++x.work;},[](auto& x){++x.schema_version;}};
  for(const auto& change:mutations){auto copy=original;change(copy);check(program(copy)!=baseline,"normalized source field mutation collapsed");}
  std::cout<<"C05 independent normalized byte mutations="<<mutations.size()<<'\n';
}

void exact_byte_budget(){
  const Value value{std::string{"a\0\xff",3}};
  wire::Budget full(rank::Limits{});const auto expected=wire::scalar_binding_record(value,full);
  check(full.usage.work==expected.size() && full.usage.binding_key_bytes==expected.size() && full.usage.payload_bytes==expected.size(),
        "small scalar record did not charge every framed byte before append");
  for(unsigned field=0;field<3;++field){
    auto limits=rank::Limits{};
    if(field==0)limits.work=full.usage.work;
    if(field==1)limits.binding_key_bytes=full.usage.binding_key_bytes;
    if(field==2)limits.payload_bytes=full.usage.payload_bytes;
    wire::Budget exact(limits);check(wire::scalar_binding_record(value,exact)==expected,"exact diagnostic byte cap failed");
    if(field==0){--limits.work;}
    if(field==1){--limits.binding_key_bytes;}
    if(field==2){--limits.payload_bytes;}
    bool stopped=false;
    try{wire::Budget short_budget(limits);static_cast<void>(wire::scalar_binding_record(value,short_budget));}
    catch(const wire::Failure& error){stopped=error.stop==s::Stop::resource_limit;}
    check(stopped,"one-under framed-byte cap returned a truncated record");
  }
}
} // namespace

int main(){
  try{
    scalar_literals();tree_literals_and_mutations();core_literals_and_mutations();normalized_field_mutations();exact_byte_budget();
    std::cout<<"C05 independent byte groups=5 scalar_types=5 tree_mutations=17 core_mutations=38\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
