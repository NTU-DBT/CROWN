#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/combined_statistics.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <map>
#include <source_location>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::runtime;
namespace st=crown::runtime::statistics;
namespace ws=crown::runtime::workload;
using Counts=std::map<Row,std::uint64_t>;
using Fields=std::vector<FieldId>;
void check(bool value,std::string_view message,std::source_location at=std::source_location::current()) {
  if(!value)throw std::runtime_error(std::string(at.file_name())+":"+std::to_string(at.line())+": "+std::string(message));
}
Value n(std::int64_t value){return value;}
Value decimal(std::string_view value){return Decimal::parse(value);}
Value date(std::string_view value){return Date::parse(value);}
constexpr std::string_view biggest="99999999999999999999999999999999999999";
constexpr std::string_view tiniest="0.00000000000000000000000000000000000001";
st::Limits limits(){st::Limits result;result.work=2000000;result.rows=8192;result.distinct_keys=8192;result.accounted_bytes=8*1024*1024;result.projection_width=8;result.heavy_keys=64;return result;}
ws::Options enabled(){ws::Options result;result.mode=ws::Mode::counters;result.max_cells=512;result.detail_budget=256;return result;}
DeltaOptions options(){DeltaOptions result;result.mode=DeltaMode::delta;result.physical.support.observation.mode=ObservationMode::off;return result;}
std::uint64_t count_of(const auto& values){return static_cast<std::uint64_t>(values.size());}
Row fields(const Row& row,const Fields& selection){Row out;for(auto field:selection)out.push_back(row.at(field.value));return out;}
Counts project(const Relation& rows,const Fields& selection){Counts out;for(const auto& row:rows)++out[fields(row,selection)];return out;}
Counts ones(const Counts& values){Counts out;for(const auto& [key,count]:values){static_cast<void>(count);out.emplace(key,1);}return out;}
Counts root_counts(const Counts& survivors){return survivors.empty()?Counts{}:Counts{{Row{},count_of(survivors)}};}
void unknown(const st::Distribution& value){check(value.completion==st::Completion::budget_exhausted&&!value.ndv&&!value.heavy_keys&&value.histogram.empty(),"incomplete distribution invented facts");}
void distribution(const st::Distribution& actual,const Counts& expected,std::uint64_t visited,std::size_t top=64) {
  check(actual.completion==st::Completion::exact&&actual.ndv==count_of(expected)&&actual.visited==visited,"exact population/visit count");
  std::map<std::uint64_t,std::uint64_t> histogram;std::vector<std::pair<Row,std::uint64_t>> ranked;
  for(const auto& item:expected){++histogram[item.second];ranked.push_back(item);}
  check(actual.histogram==std::vector<std::pair<std::uint64_t,std::uint64_t>>(histogram.begin(),histogram.end()),"exact multiplicity histogram");
  std::sort(ranked.begin(),ranked.end(),[](const auto& a,const auto& b){return a.second!=b.second?a.second>b.second:a.first<b.first;});
  ranked.resize(std::min(top,ranked.size()));check(actual.heavy_keys&&actual.heavy_keys->size()==ranked.size(),"known top-K length");
  for(std::size_t i=0;i<ranked.size();++i)check((*actual.heavy_keys)[i].key==ranked[i].first&&(*actual.heavy_keys)[i].count==ranked[i].second,"exact top-K key/count");
}
void component(const st::Component& actual,const Counts& expected,std::uint64_t cardinality,std::uint64_t visited,std::size_t top=64) {
  check(actual.availability==st::Availability::available&&actual.cardinality==cardinality&&actual.distribution,"component exact cardinality/availability");
  distribution(*actual.distribution,expected,visited,top);
}
void selection(const st::Selection& actual,const st::Selection& expected) {
  check(actual.scope.index()==expected.scope.index()&&actual.fields==expected.fields,"selection order/fields");
  if(const auto* s=std::get_if<st::SourceScope>(&expected.scope))check(std::get<st::SourceScope>(actual.scope).table==s->table,"source selection");
  if(const auto* s=std::get_if<st::OccurrenceScope>(&expected.scope))check(std::get<st::OccurrenceScope>(actual.scope).occurrence==s->occurrence,"occurrence selection");
  if(const auto* s=std::get_if<st::NodeScope>(&expected.scope)){const auto a=std::get<st::NodeScope>(actual.scope);check(a.node==s->node&&a.role==s->role,"node selection");}
  if(const auto* s=std::get_if<st::IndexScope>(&expected.scope))check(std::get<st::IndexScope>(actual.scope).requirement==s->requirement,"index selection");
}
void boundary(const st::CombinedCapture& report,const PhysicalPlan& plan,SupportOwnerId owner,std::uint64_t sequence,bool pending=false) {
  check(report.state().stamp().owner==owner&&report.workload().stamp().owner==owner,"actual owner binding");
  check(report.state().stamp().sequence==sequence&&report.workload().stamp().committed_epoch==sequence,"actual committed boundary");
  check(report.state().plan().physical_sha256()==plan.physical_sha256()&&report.workload().plan().physical_sha256()==plan.physical_sha256(),"actual plan binding");
  check(report.workload().pending()==pending,"workload pending flag");
  if(pending)check(report.state().availability()==st::Availability::pending_private_state&&report.state().components().empty(),"pending state leaks facts");
  else check(report.state().availability()==st::Availability::available,"expected complete state");
}

// Rank is supplied by the literal list, never by Value/Decimal/string ordering.
void ranked_distribution(const st::Distribution& actual,const std::vector<Value>& ordered,const std::vector<std::uint64_t>& multiplicities,
    std::uint64_t visited,std::size_t top,bool repeated=false) {
  check(actual.completion==st::Completion::exact&&actual.ndv==count_of(ordered)&&actual.visited==visited,"literal scalar NDV/visits");
  std::map<std::uint64_t,std::uint64_t> histogram;std::vector<std::size_t> rank;
  for(std::size_t i=0;i<ordered.size();++i){++histogram[multiplicities[i]];rank.push_back(i);}
  check(actual.histogram==std::vector<std::pair<std::uint64_t,std::uint64_t>>(histogram.begin(),histogram.end()),"literal scalar histogram");
  std::sort(rank.begin(),rank.end(),[&](auto a,auto b){return multiplicities[a]!=multiplicities[b]?multiplicities[a]>multiplicities[b]:a<b;});
  rank.resize(std::min(top,rank.size()));check(actual.heavy_keys&&actual.heavy_keys->size()==rank.size(),"literal scalar heavy length");
  for(std::size_t i=0;i<rank.size();++i){Row key{ordered[rank[i]]};if(repeated)key.push_back(ordered[rank[i]]);
    check((*actual.heavy_keys)[i].key==key&&(*actual.heavy_keys)[i].count==multiplicities[rank[i]],"literal scalar ordering/count");}
}
void scalar_order(ScalarType type,const std::vector<Value>& ordered) {
  using namespace storage;
  const TupleLayout source{LayoutId{1},{{type},{ScalarType::int64}}};
  const TupleLayout key{LayoutId{2},{{type}}};const TupleLayout pair{LayoutId{3},{{type},{type}}};const TupleLayout empty{LayoutId{4},{}};
  const Projection one{source,key,{{0}}}, repeated{source,pair,{{0},{0}}}, zero{source,empty,{}};
  ReferenceTable table{RelationId{1},source};const auto index=table.add_index(one);
  std::int64_t ordinal=0;std::vector<std::uint64_t> multiplicities(ordered.size(),2);
  for(const auto& value:ordered)for(int copy=0;copy<2;++copy){Value input=value;
    if(type==ScalarType::decimal&&copy==1){if(value==decimal("0"))input=decimal("-000.000");if(value==decimal("1.2"))input=decimal("+001.2000");}
    check(table.insert(source.tuple({input,n(++ordinal)})).inserted,"distinct source witness");}
  st::Budget scan(limits()),indexed(limits()),repeat(limits()),nullary(limits());
  const auto a=st::projection(table,one,scan);const auto b=st::index(table,index,indexed);
  ranked_distribution(a.distribution,ordered,multiplicities,static_cast<std::uint64_t>(ordinal),64);
  ranked_distribution(b.distribution,ordered,multiplicities,count_of(ordered),64);
  ranked_distribution(st::projection(table,repeated,repeat).distribution,ordered,multiplicities,static_cast<std::uint64_t>(ordinal),64,true);
  distribution(st::projection(table,zero,nullary).distribution,Counts{{Row{},static_cast<std::uint64_t>(ordinal)}},static_cast<std::uint64_t>(ordinal));
  check(a.cardinality==static_cast<std::size_t>(ordinal)&&a.source_layout.same_token(source),"owning source descriptor/cardinality");
  check(scan.usage().work<=scan.limits().work&&scan.usage().accounted_bytes<=scan.limits().accounted_bytes,"finite scalar budget");
  auto exact=limits();exact.work=indexed.usage().work;st::Budget at(exact);ranked_distribution(st::index(table,index,at).distribution,ordered,multiplicities,count_of(ordered),64);
  --exact.work;st::Budget below(exact);unknown(st::index(table,index,below).distribution);
  auto none=limits();none.rows=0;st::Budget no_rows(none);const auto unfinished=st::projection(table,one,no_rows);
  check(unfinished.cardinality==static_cast<std::size_t>(ordinal),"known cardinality survives scalar exhaustion");unknown(unfinished.distribution);
  check(table.insert(source.tuple({ordered.front(),n(++ordinal)})).inserted,"first hot key");++multiplicities.front();
  check(table.insert(source.tuple({ordered.back(),n(++ordinal)})).inserted,"last hot key");++multiplicities.back();
  auto top=limits();top.heavy_keys=3;st::Budget top_budget(top);const auto hot=st::index(table,index,top_budget);
  ranked_distribution(hot.distribution,ordered,multiplicities,count_of(ordered),3);
  top.heavy_keys=0;st::Budget no_heavy(top);ranked_distribution(st::index(table,index,no_heavy).distribution,ordered,multiplicities,count_of(ordered),0);
  table.clear();ranked_distribution(hot.distribution,ordered,multiplicities,count_of(ordered),3);
  st::Budget blank(limits());distribution(st::projection(table,zero,blank).distribution,{},0);table.check_invariants();
}
void scalar_orders() {
  const auto low=std::numeric_limits<std::int64_t>::min(),high=std::numeric_limits<std::int64_t>::max();
  scalar_order(ScalarType::int64,{n(low),n(low+1),n(-1),n(0),n(1),n(high-1),n(high)});
  scalar_order(ScalarType::boolean,{false,true});
  scalar_order(ScalarType::date,{date("0001-01-01"),date("1900-02-28"),date("1969-12-31"),date("1970-01-01"),date("2000-02-29"),date("2024-02-29"),date("9999-12-31")});
  scalar_order(ScalarType::decimal,{decimal("-"+std::string(biggest)),decimal("-100"),decimal("-1.2"),decimal("-0.99999999999999999999999999999999999999"),
      decimal("-"+std::string(tiniest)),decimal("0"),decimal(tiniest),decimal("0.01"),decimal("0.99999999999999999999999999999999999999"),
      decimal("1.2"),decimal("1.23"),decimal("1.23000001"),decimal("10"),decimal(biggest)});
  scalar_order(ScalarType::string,{std::string{},std::string("\0",1),std::string("\0\0",2),std::string("\0a",2),std::string("a"),std::string("a\0",2),
      std::string("a\0z",3),std::string(1024,'a'),std::string(1023,'a')+"b",std::string(1,static_cast<char>(127)),std::string(1,static_cast<char>(128)),std::string(1,static_cast<char>(255))});
}

// Independent arithmetic: do not call Cell::observe/merge or collector hooks.
void observation(ws::Cell& cell,std::uint64_t value){if(!cell.count)cell.min=cell.max=value;else{cell.min=std::min(cell.min,value);cell.max=std::max(cell.max,value);}++cell.count;cell.sum+=value;std::size_t bin=0;for(auto x=value;x;x/=2)++bin;++cell.bins[bin];}
void transition(ws::Cell& cell,std::uint64_t before,std::uint64_t after){if(before==after)return;++cell.changes;if(!before)++cell.zero_to_positive;if(!after)++cell.positive_to_zero;observation(cell,after);}
struct Events {
  std::vector<ws::Descriptor> descriptors;std::vector<ws::Cell> cells;
  explicit Events(const ws::Snapshot& initial):descriptors(initial.descriptors().begin(),initial.descriptors().end()),cells(descriptors.size()){}
  ws::Cell& at(std::uint64_t table,SetOperation op,ws::Role role,std::optional<NodeId> node={},std::optional<OccurrenceId> occurrence={},std::optional<std::size_t> edge={},std::optional<ws::Operation> sign={}) {
    for(std::size_t i=0;i<descriptors.size();++i){const auto& d=descriptors[i];if(d.table==table&&d.operation==(op==SetOperation::insert?ws::Operation::insert:ws::Operation::erase)&&d.role==role&&(!node||d.node==node)&&(!occurrence||d.occurrence==occurrence)&&(!edge||d.edge==edge)&&(!sign||d.event_operation==sign))return cells[i];}
    throw std::runtime_error("missing expected physical descriptor");
  }
  void input(std::uint64_t table,SetOperation op,bool changed){auto& c=at(table,op,ws::Role::input);++c.inputs;++c.complete_detail_inputs;if(changed)++c.changed;else ++c.noop;}
  void adapter(std::uint64_t table,SetOperation op,OccurrenceId id,bool accepted){auto& c=at(table,op,ws::Role::adapter,{},id);++c.visited;if(accepted)++c.accepted;else ++c.rejected;}
  void check_snapshot(const ws::Snapshot& actual,std::uint64_t committed,std::uint64_t aborted) const {
    check(actual.options()==enabled()&&actual.descriptors().size()==descriptors.size()&&std::equal(descriptors.begin(),descriptors.end(),actual.descriptors().begin()),"descriptor/configuration identity");
    check(actual.cells().size()==cells.size()&&std::equal(cells.begin(),cells.end(),actual.cells().begin()),"literal full workload cells");
    const auto& m=actual.metadata();check(m.attempts==committed+aborted&&m.selected==m.attempts&&m.committed==committed&&m.complete==committed&&m.aborted==aborted&&m.aborted_selected==aborted,"attempt/abort/commit populations");
    check(!m.truncated&&!m.committed_truncated&&!m.saturated&&!m.invalid_descriptor&&!m.protocol_error&&!m.ordinal_exhausted,"unexpected degraded collection");
    check(actual.detail_availability()==ws::Availability::exact&&actual.arrival_per_second()==ws::Availability::unavailable,"exact events are not arrival Hz");
    for(std::size_t i=0;i<descriptors.size();++i)if(descriptors[i].kind==ws::Kind::physical){const auto share=actual.input_share(i);check(share.numerator==cells[i].inputs&&share.denominator==committed,"all committed physical input denominator");check(share.availability==(committed?ws::Availability::exact:ws::Availability::unavailable),"empty input fraction availability");}
  }
};
PhysicalPlan alias_plan() {
  const Catalog catalog{11,{{"typed",{{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"amount",ScalarType::decimal},{"text",ScalarType::string},{"tag",ScalarType::int64}}}}};
  Query query;query.variables={{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"amount",ScalarType::decimal},{"text",ScalarType::string}};
  query.atoms={{"left",TableId{0},{}},{"right",TableId{0},{}}};
  for(auto& atom:query.atoms)for(std::uint64_t i=0;i<5;++i)atom.terms.emplace_back(std::in_place_type<VariableId>,VariableId{i});
  query.atoms[0].terms.emplace_back(std::in_place_type<IgnoredColumn>);query.atoms[1].terms.emplace_back(std::in_place_type<Value>,n(0));
  query.head={{{3},"amount"},{{4},"text"},{{0},"i"},{{1},"b"},{{2},"d"},{{3},"again"}};
  const VariableSet scope{{0},{1},{2},{3},{4}};
  return planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},{{"g",NodeKind::generalized,scope,{{1},{2}},{},{}},{"left",NodeKind::native,scope,{},0,{}},{"right",NodeKind::native,scope,{},1,{}}},{},{}});
}
const Fields full{{0},{1},{2},{3},{4}};
st::OwnerRequest alias_request(const PhysicalPlan& plan){st::OwnerRequest out;
  for(std::uint64_t i=0;i<5;++i)out.selections.push_back({st::SourceScope{{0}},Fields{{i}}});
  out.selections.push_back({st::SourceScope{{0}},Fields{{3},{4},{0},{3}}});out.selections.push_back({st::SourceScope{{0}},Fields{}});
  for(std::uint64_t i=0;i<2;++i)out.selections.push_back({st::OccurrenceScope{{i}},{}});
  for(std::uint64_t i=0;i<3;++i)for(auto role:{SupportRole::records,SupportRole::survivors,SupportRole::parent_support,SupportRole::visible})out.selections.push_back({st::NodeScope{{i},role},role==SupportRole::records||role==SupportRole::survivors?std::optional<Fields>{full}:std::nullopt});
  for(const auto& index:plan.indexes())out.selections.push_back({st::IndexScope{index.id},{}});
  return out;
}
struct AliasModel {
  Relation source;std::array<Counts,2> native;Events events;
  explicit AliasModel(const ws::Snapshot& initial):events(initial){}
  Counts joined() const {Counts out;for(const auto& [key,count]:native[0]){static_cast<void>(count);if(native[1].contains(key))out.emplace(key,1);}return out;}
  Counts candidates() const {auto out=ones(native[0]);for(const auto& [key,count]:native[1]){static_cast<void>(count);out[key]=1;}return out;}
  void apply(const PhysicalPlan& plan,SetOperation op,const Row& row) {
    const bool add=op==SetOperation::insert;const bool changed=add?source.insert(row).second:source.erase(row)!=0;events.input(0,op,changed);if(!changed)return;
    const Row key=fields(row,full);
    for(std::size_t route=0;route<2;++route){const bool accepted=route==0||row[5]==n(0);events.adapter(0,op,OccurrenceId{route},accepted);if(!accepted)continue;
      const bool candidate=native[0].contains(key)||native[1].contains(key),member=native[0].contains(key)&&native[1].contains(key);const auto before_root=count_of(joined());
      const auto found=native[route].find(key);const auto before=found==native[route].end()?0:found->second;check(add||before>0,"oracle derivation erase");const auto after=add?before+1:before-1;
      transition(events.at(0,op,ws::Role::derivation,{},OccurrenceId{route}),before,after);if(after)native[route][key]=after;else native[route].erase(key);
      if((before==0)==(after==0))continue;
      const NodeId node{route+1};for(auto role:{ws::Role::survivor,ws::Role::parent_support,ws::Role::visible_support})transition(events.at(0,op,role,node),before?1:0,after?1:0);
      std::size_t edge=0;while(edge<plan.edges().size()&&plan.edges()[edge].child!=node)++edge;check(edge<plan.edges().size(),"literal alias edge");
      observation(events.at(0,op,ws::Role::generalized_probe,{}, {},edge,after?ws::Operation::insert:ws::Operation::erase),candidate?1:0);
      const bool next=native[0].contains(key)&&native[1].contains(key);if(member!=next){transition(events.at(0,op,ws::Role::survivor,NodeId{0}),member?1:0,next?1:0);transition(events.at(0,op,ws::Role::visible_support,NodeId{0}),member?1:0,next?1:0);transition(events.at(0,op,ws::Role::parent_support,NodeId{0}),before_root,count_of(joined()));}
    }
  }
  void check_state(const st::OwnerCapture& report,const PhysicalPlan& plan,const st::OwnerRequest& request) const {
    std::array<Counts,2> literal;for(const auto& row:source){const auto key=fields(row,full);++literal[0][key];if(row[5]==n(0))++literal[1][key];}
    check(native==literal,"alias derivations agree with independent source regrouping");
    check(report.components().size()==request.selections.size(),"complete alias component count");
    for(std::size_t i=0;i<request.selections.size();++i){const auto& expected=request.selections[i];const auto& actual=report.components()[i];selection(actual.selection,expected);
      if(std::holds_alternative<st::SourceScope>(expected.scope)){component(actual,project(source,*expected.fields),count_of(source),count_of(source));continue;}
      if(const auto* occurrence=std::get_if<st::OccurrenceScope>(&expected.scope)){const auto& population=native[occurrence->occurrence.value];component(actual,population,count_of(population),count_of(population));check(actual.node_kind==NodeKind::native,"native occurrence kind");continue;}
      if(const auto* node=std::get_if<st::NodeScope>(&expected.scope)){const auto id=node->node.value;Counts population=id==0?(node->role==SupportRole::records?candidates():joined()):ones(native[id-1]);if(node->role==SupportRole::parent_support&&id==0)population=root_counts(population);component(actual,population,count_of(population),count_of(population));check(actual.node_kind==(id?NodeKind::native:NodeKind::generalized),"alias node kind");continue;}
      const auto& index=plan.indexes()[std::get<st::IndexScope>(expected.scope).requirement.value];check(index.projection.fields()==full,"typed enumeration index has full separator");
      bool matched=false;for(const auto& node:plan.nodes())if(node.visible_relation&&*node.visible_relation==index.relation){const auto population=node.id.value?ones(native[node.id.value-1]):joined();component(actual,population,count_of(population),count_of(population));matched=true;break;}check(matched,"known visible index population");
    }
  }
};
Row tagged(Row key,std::int64_t tag){key.push_back(n(tag));return key;}
void typed_alias_trace() {
  const auto plan=alias_plan();const auto request=alias_request(plan);DeltaRuntime runtime(plan,options());runtime.configure_workload_statistics(enabled());AliasModel model(runtime.workload_statistics());
  const Row a{n(std::numeric_limits<std::int64_t>::min()),false,date("0001-01-01"),decimal("-"+std::string(biggest)),std::string("\0\xff",2)};
  const Row b{n(-1),true,date("1969-12-31"),decimal("1.2"),std::string("a\0z",3)};
  const Row c{n(std::numeric_limits<std::int64_t>::max()),true,date("9999-12-31"),decimal(tiniest),std::string(1,static_cast<char>(255))};
  const Row d{n(0),false,date("2000-02-29"),decimal("-"+std::string(tiniest)),std::string(1024,'q')};
  const Row e{n(1),true,date("2024-02-29"),decimal(biggest),std::string(1,static_cast<char>(128))};
  const Row f{n(2),false,date("1970-01-01"),decimal("-0.000"),std::string{}};
  auto alias=tagged(b,0);alias[3]=decimal("+001.2000");
  const std::vector<Row> insertions{tagged(a,1),tagged(a,0),tagged(a,2),tagged(b,0),alias,tagged(b,1),tagged(c,0),tagged(d,1),tagged(d,0),tagged(e,0),tagged(f,0)};
  const auto owner=runtime.owner();std::uint64_t sequence=0;
  const auto verify=[&]{const auto report=runtime.capture_combined_statistics(request,limits());boundary(report,plan,owner,sequence);model.check_state(report.state(),plan,request);model.events.check_snapshot(report.workload(),sequence,0);runtime.check_invariants();};
  verify();
  const auto commit=[&](SetOperation op,const Row& row){auto output=runtime.apply({sequence+1,{0},op,row});output.discard();model.apply(plan,op,row);++sequence;verify();};
  for(const auto& row:insertions)commit(SetOperation::insert,row);
  const auto retained=runtime.capture_combined_statistics(request,limits());const auto saved=model;const auto saved_sequence=sequence;
  auto cap=limits();cap.rows=count_of(model.source);const auto incomplete=runtime.capture_combined_statistics(request,cap);
  check(incomplete.state().availability()==st::Availability::budget_exhausted&&incomplete.state().components()[0].availability==st::Availability::available,"earlier typed component survives shared exhaustion");
  distribution(*incomplete.state().components()[0].distribution,project(model.source,Fields{{0}}),count_of(model.source));unknown(*incomplete.state().components()[1].distribution);model.events.check_snapshot(incomplete.workload(),sequence,0);
  commit(SetOperation::erase,tagged(a,1));commit(SetOperation::erase,tagged(a,0));commit(SetOperation::erase,tagged(a,2));commit(SetOperation::erase,tagged(a,0));
  const auto remaining=model.source;for(const auto& row:remaining)commit(SetOperation::erase,row);
  check(model.source.empty()&&model.joined().empty(),"typed trace ends empty");runtime.reset_workload_statistics();
  boundary(retained,plan,owner,saved_sequence);saved.check_state(retained.state(),plan,request);saved.events.check_snapshot(retained.workload(),saved_sequence,0);
}

PhysicalPlan constraint_plan() {
  Catalog catalog{12,{{"child",{{"id",ScalarType::int64},{"parent",ScalarType::int64},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{4,2}}}},
      {"parent",{{"id",ScalarType::int64},{"tag",ScalarType::string}}}}};
  catalog.tables[0].constraints={UniqueConstraint{"child_pk",{{0}},ConstraintStatus::enforced},ForeignKeyConstraint{"child_fk",{{1}},{1},{{0}},ConstraintStatus::enforced}};
  catalog.tables[1].constraints={UniqueConstraint{"parent_pk",{{0}},ConstraintStatus::enforced}};
  Query query;query.variables={{"parent",ScalarType::int64},{"amount",ScalarType::decimal}};query.atoms={{"c",{0},{}}};
  query.atoms[0].terms.emplace_back(std::in_place_type<IgnoredColumn>);query.atoms[0].terms.emplace_back(std::in_place_type<VariableId>,VariableId{0});query.atoms[0].terms.emplace_back(std::in_place_type<VariableId>,VariableId{1});query.head={{{0},"parent"}};
  return planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},{{"c",NodeKind::native,{{0},{1}},{},0,{}}},{},{}});
}
st::OwnerRequest constraint_request(){return {{{st::SourceScope{{0}},Fields{{0},{1},{2}}},{st::SourceScope{{0}},Fields{{2},{1},{2}}},{st::SourceScope{{0}},Fields{}},
    {st::SourceScope{{1}},Fields{{0},{1}}},{st::SourceScope{{1}},Fields{{1}}},{st::SourceScope{{1}},Fields{}},{st::OccurrenceScope{{0}},{}},
    {st::NodeScope{{0},SupportRole::records},Fields{{0},{1}}},{st::NodeScope{{0},SupportRole::survivors},Fields{{0},{1}}},
    {st::NodeScope{{0},SupportRole::parent_support},{}},{st::NodeScope{{0},SupportRole::visible},{}}}};}
struct ConstraintModel {
  std::array<Relation,2> sources;Counts native;Events events;
  explicit ConstraintModel(const ws::Snapshot& initial):events(initial){}
  Counts visible() const {Counts out;for(const auto& [key,count]:native){static_cast<void>(count);++out[Row{key[0]}];}return out;}
  void apply(std::uint64_t table,SetOperation op,const Row& row){const bool add=op==SetOperation::insert;const bool changed=add?sources[table].insert(row).second:sources[table].erase(row)!=0;events.input(table,op,changed);if(!changed||table!=0)return;
    events.adapter(0,op,{0},true);const Row key{row[1],row[2]};const auto old=native.find(key);const auto before=old==native.end()?0:old->second;check(add||before>0,"constrained oracle erase");const auto after=add?before+1:before-1;
    const auto old_root=count_of(native);const auto prior_visible=visible();const Row projection{key[0]};const auto prior=prior_visible.find(projection);const auto visible_before=prior==prior_visible.end()?0:prior->second;
    transition(events.at(0,op,ws::Role::derivation,{},OccurrenceId{0}),before,after);if(after)native[key]=after;else native.erase(key);
    if((before==0)!=(after==0)){transition(events.at(0,op,ws::Role::survivor,NodeId{0}),before?1:0,after?1:0);transition(events.at(0,op,ws::Role::parent_support,NodeId{0}),old_root,count_of(native));const auto next_visible=visible();const auto next=next_visible.find(projection);transition(events.at(0,op,ws::Role::visible_support,NodeId{0}),visible_before,next==next_visible.end()?0:next->second);}
  }
  void check_state(const st::OwnerCapture& report,const st::OwnerRequest& request) const {
    check(native==project(sources[0],Fields{{1},{2}}),"constrained derivations agree with independent source regrouping");
    check(report.components().size()==request.selections.size(),"complete constrained component count");
    for(std::size_t i=0;i<request.selections.size();++i){const auto& expected=request.selections[i];const auto& actual=report.components()[i];selection(actual.selection,expected);
      if(const auto* source=std::get_if<st::SourceScope>(&expected.scope)){const auto& rows=sources[source->table.value];component(actual,project(rows,*expected.fields),count_of(rows),count_of(rows));continue;}
      if(std::holds_alternative<st::OccurrenceScope>(expected.scope)){component(actual,native,count_of(native),count_of(native));continue;}
      const auto role=std::get<st::NodeScope>(expected.scope).role;const Counts population=role==SupportRole::parent_support?root_counts(native):role==SupportRole::visible?visible():ones(native);component(actual,population,count_of(population),count_of(population));check(actual.node_kind==NodeKind::native,"constrained native kind");
    }
  }
};
void constrained_trace() {
  const auto plan=constraint_plan();const auto request=constraint_request();DeltaRuntime runtime(plan,options());runtime.configure_workload_statistics(enabled());ConstraintModel model(runtime.workload_statistics());
  const auto owner=runtime.owner();std::uint64_t sequence=0,aborted=0;
  const auto verify=[&]{const auto report=runtime.capture_combined_statistics(request,limits());boundary(report,plan,owner,sequence);model.check_state(report.state(),request);model.events.check_snapshot(report.workload(),sequence,aborted);runtime.check_invariants();};
  const auto commit=[&](std::uint64_t table,SetOperation op,const Row& row){auto output=runtime.apply({sequence+1,{table},op,row});output.discard();model.apply(table,op,row);++sequence;verify();};
  const auto reject=[&](std::uint64_t table,SetOperation op,const Row& row,std::string_view code){const auto before=runtime.canonical_state();const auto retained=runtime.capture_combined_statistics(request,limits());bool rejected=false;
    try{auto output=runtime.apply({sequence+1,{table},op,row});output.discard();}catch(const Error& error){check(error.code()==code,"constraint rejection code");rejected=true;}
    check(rejected&&runtime.owner()==owner&&runtime.sequence()==sequence&&runtime.ready()&&runtime.canonical_state()==before,"failed update changed same-owner committed state");++aborted;verify();check(runtime.statistics_freshness(retained.state())==st::Freshness::current,"failed update staled data epoch");model.check_state(retained.state(),request);model.events.check_snapshot(retained.workload(),sequence,aborted-1);};
  const auto add=SetOperation::insert,erase=SetOperation::erase;const Row p10{n(10),std::string("p\0a",3)},p20{n(20),std::string(1,static_cast<char>(255))};
  const Row c1{n(1),n(10),decimal("1.2")},c2{n(2),n(10),decimal("1.20")},c3{n(3),n(10),decimal("-99.99")},c4{n(4),n(20),decimal("99.99")};
  verify();reject(0,add,c1,"constraint_violation");commit(1,add,p10);commit(1,add,p20);
  reject(1,add,{n(10),std::string("different")},"constraint_violation");commit(0,add,c1);commit(0,add,{n(1),n(10),decimal("+001.2000")});
  reject(0,add,{n(1),n(10),decimal("2.3")},"constraint_violation");commit(0,add,c2);commit(0,add,c3);
  reject(1,erase,p10,"constraint_violation");reject(0,add,{n(4),n(99),decimal("99.99")},"constraint_violation");commit(0,add,c4);
  reject(0,add,{n(5),n(20),decimal("100")},"scalar_overflow");
  {const auto before=runtime.canonical_state();const auto saved=runtime.capture_combined_statistics(request,limits());auto pending=runtime.begin({sequence+1,{0},add,{n(9),n(20),decimal("-0.01")}});pending.drain();const auto hidden=runtime.capture_combined_statistics(request,limits());boundary(hidden,plan,owner,sequence,true);
    check(std::equal(model.events.cells.begin(),model.events.cells.end(),hidden.workload().cells().begin()),"tentative constrained cells leaked");pending.rollback();++aborted;verify();check(runtime.canonical_state()==before&&runtime.statistics_freshness(saved.state())==st::Freshness::current,"explicit constrained rollback boundary");}
  commit(0,erase,c1);commit(0,erase,c2);commit(0,erase,c3);commit(1,erase,p10);commit(1,erase,p10);commit(0,erase,c4);commit(1,erase,p20);
  check(model.sources[0].empty()&&model.sources[1].empty()&&model.native.empty(),"constrained trace ends empty");
}
} // namespace
int main(){try{scalar_orders();typed_alias_trace();constrained_trace();std::cout<<"C01 typed scalar/constraint statistics: 7 groups passed\n";}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
