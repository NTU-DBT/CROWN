#include "owner_statistics_fixture.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"
#include "crown/api/error.hpp"
#include <map>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace owner_fixture;
static_assert(!std::is_default_constructible_v<stats::OwnerCapture>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::OwnerCapture&>().stamp())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::OwnerCapture&>().components())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::OwnerCapture&>().plan())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::OwnerCapture&>().limits())>>);
int main(){
  const auto p=plan();const auto db=database();const auto r=request(p);
  auto physical=PhysicalRuntime::initialize(p,db);const auto captured=physical.capture_statistics(r);
  fixture_facts(captured,db);
  // 1. Actual owner stamp and literal scope/cardinality distinctions.
  check(captured.stamp().owner==physical.owner() && captured.stamp().sequence==0 && captured.plan().physical_sha256()==p.physical_sha256());
  check(captured.physical_source_scope()==stats::Availability::available && captured.components().size()==8);
  check(captured.components()[0].cardinality==4 && captured.components()[0].distribution->ndv==2);
  check(captured.components()[1].cardinality==1 && captured.components()[2].cardinality==3);
  check(captured.components()[3].cardinality==3 && captured.components()[4].cardinality==2);
  check(captured.components()[5].distribution->heavy_keys->front().key.empty() && captured.components()[5].distribution->heavy_keys->front().count==2);
  check(captured.components()[6].cardinality==2 && captured.components()[7].distribution->ndv==2);
  // 2. A04 full relational evaluation and independently grouped root visible rows.
  const auto answers=reference::evaluate(p.catalog(),p.query(),db);check(answers==Relation{{n(1),n(7)},{n(2),n(7)}});
  Counts source_y,derivations,visible_counts,survivor_y,parent_counts,reverse_degrees;
  for(const auto& row:db.tables[0]){++source_y[Row{row[1]}];++derivations[Row{row[0],row[1]}];}
  for(const auto& [key,count]:derivations){static_cast<void>(count);++reverse_degrees[Row{key[1]}];}
  for(const auto& row:answers){++visible_counts[row];++survivor_y[Row{row[1]}];++parent_counts[Row{}];}
  distribution(captured.components()[0],source_y,4);
  distribution(captured.components()[2],derivations,3);
  distribution(captured.components()[4],survivor_y,2);
  distribution(captured.components()[5],parent_counts,1);
  distribution(captured.components()[6],visible_counts,2);
  distribution(captured.components()[7],reverse_degrees,2);
  check(!captured.components()[1].distribution && !captured.components()[3].distribution);
  for(const auto slot:{std::size_t{5},std::size_t{6}}){std::uint64_t total=0;for(const auto& [count,keys]:captured.components()[slot].distribution->histogram)total+=count*keys;check(total==*captured.components()[4].cardinality);}
  // 3. Direct/replay/rebuild have equal facts, different owner on rebuild.
  BuildOptions replay;replay.method=BuildMethod::insertion_replay;
  auto replayed=PhysicalRuntime::initialize(p,db,{},replay);same_facts(captured,replayed.capture_statistics(r));
  check(replayed.statistics_freshness(captured)==stats::Freshness::foreign_owner);
  auto rebuilt=physical.rebuilt();same_facts(captured,rebuilt.capture_statistics(r));
  check(rebuilt.statistics_freshness(captured)==stats::Freshness::foreign_owner);
  // 4. Private prepared state returns metadata-only; rollback preserves freshness.
  {auto pending=physical.prepare({1,TableId{1},SetOperation::insert,{n(8)}});
    const auto private_report=physical.capture_statistics(r);check(private_report.availability()==stats::Availability::pending_private_state && private_report.components().empty());
    check(physical.statistics_freshness(private_report)==stats::Freshness::current);
    pending.rollback();}
  const auto rolled_back=physical.capture_statistics(r);same_facts(captured,rolled_back);
  check(rolled_back.components()[4].storage_invalidation->revision>captured.components()[4].storage_invalidation->revision);
  check(physical.statistics_freshness(captured)==stats::Freshness::current);
  // 5. A no-op committed physical event stales by epoch, without changed facts.
  static_cast<void>(physical.apply({1,TableId{1},SetOperation::insert,{n(7)}}));
  same_facts(captured,physical.capture_statistics(r));check(physical.statistics_freshness(captured)==stats::Freshness::stale);
  check(physical.statistics_freshness(captured,1)==stats::Freshness::within_lag);
  // 6. Real support multiplicity changes; owning old report and moved owner survive.
  static_cast<void>(physical.apply({2,TableId{1},SetOperation::insert,{n(8)}}));
  auto all_supported=db;all_supported.tables[1].insert(Row{n(8)});
  fixture_facts(physical.capture_statistics(r),all_supported);
  check(physical.capture_statistics(r).components()[5].distribution->heavy_keys->front().count==3);
  check(captured.components()[5].distribution->heavy_keys->front().count==2);
  check(physical.statistics_freshness(captured,1)==stats::Freshness::stale);
  auto moved=std::move(physical);check(moved.statistics_freshness(captured,2)==stats::Freshness::within_lag);
  // 7. Shared cap retains completed early projection; later distribution unknown.
  stats::Limits limited;limited.rows=4;const auto partial=replayed.capture_statistics(r,limited);
  check(partial.availability()==stats::Availability::budget_exhausted && partial.components()[0].distribution->ndv==2 && !partial.components()[2].distribution->ndv && !partial.components()[5].distribution->heavy_keys);
  check(replayed.statistics_freshness(partial)==stats::Freshness::current);
  stats::Limits zero;zero.accounted_bytes=0;check(replayed.capture_statistics(r,zero).availability()==stats::Availability::budget_exhausted);
  // 8. Lower-only scope availability and actual native support pending guard.
  SupportRuntime support{p};
  static_cast<void>(support.apply({1,NodeId{0},SetOperation::insert,{n(1),n(7)}}));
  static_cast<void>(support.apply({2,NodeId{1},SetOperation::insert,{n(7)}}));
  auto lower=support.capture_statistics(r);check(lower.physical_source_scope()==stats::Availability::unavailable && lower.components()[0].availability==stats::Availability::unavailable && lower.components()[2].availability==stats::Availability::unavailable);
  for(const auto& component:lower.components())
    if(const auto* node=std::get_if<stats::NodeScope>(&component.selection.scope);node && component.layout)
      check(component.layout->same_token(support.relation_layout(node->node,node->role)));
  check(lower.components()[5].distribution->heavy_keys->front().count==1);
  {auto pending=support.begin_epoch(3,SetOperation::insert);static_cast<void>(pending.stage(NodeId{0},{n(2),n(7)}));check(support.capture_statistics(r).availability()==stats::Availability::pending_private_state);pending.rollback();}
  check(support.statistics_freshness(lower)==stats::Freshness::current);
  // 9. C* follows output-only separators; hidden variables inside a node do not exclude it.
  const auto gp=plan(true);auto generalized=PhysicalRuntime::initialize(gp,db);
  check(gp.validation().maximal_connex==std::vector<NodeId>{NodeId{0},NodeId{1},NodeId{2}});
  for(const auto& node:gp.nodes())check(node.connex && node.visible_relation.has_value());
  stats::OwnerRequest gr{{{stats::NodeScope{NodeId{0},SupportRole::records},std::vector<FieldId>{FieldId{0}}},{stats::NodeScope{NodeId{0},SupportRole::survivors},std::vector<FieldId>{FieldId{0}}}}};
  for(const auto& node:gp.nodes())gr.selections.push_back({stats::NodeScope{node.id,SupportRole::visible},{}});
  gr.selections.push_back({stats::NodeScope{NodeId{0},SupportRole::parent_support},{}});
  const auto gc=generalized.capture_statistics(gr);
  check(gc.components().size()==6);
  check(gc.components()[0].node_kind==NodeKind::generalized);
  check(gc.components()[0].cardinality==2);
  check(gc.components()[1].cardinality==1);
  distribution(gc.components()[0],Counts{{Row{n(7)},1},{Row{n(8)},1}},2);
  distribution(gc.components()[1],Counts{{Row{n(7)},1}},1);
  // All three E factors exist. R's local E includes y=8 although G's S does not.
  distribution(gc.components()[2],Counts{{Row{n(7)},1}},1);
  distribution(gc.components()[3],Counts{{Row{n(7)},2},{Row{n(8)},1}},2);
  distribution(gc.components()[4],Counts{{Row{n(7)},1}},1);
  distribution(gc.components()[5],Counts{{Row{},1}},1);
  check(gc.components()[2].cardinality==1 && gc.components()[3].cardinality==2 && gc.components()[4].cardinality==1 && gc.components()[5].cardinality==1);
  // A separate nonempty T(x) below R(x,y) crosses hidden separator x, so E(T) is absent.
  const auto hp=hidden_separator_plan();auto hidden=PhysicalRuntime::initialize(hp,hidden_separator_database());
  check(hp.validation().maximal_connex==std::vector<NodeId>{NodeId{0},NodeId{1},NodeId{2}});
  check(!hp.nodes()[3].connex && !hp.nodes()[3].visible_relation);
  stats::OwnerRequest hidden_request{{
      {stats::NodeScope{NodeId{0},SupportRole::records},std::vector<FieldId>{FieldId{0}}},
      {stats::NodeScope{NodeId{0},SupportRole::survivors},std::vector<FieldId>{FieldId{0}}},
      {stats::NodeScope{NodeId{3},SupportRole::records},std::vector<FieldId>{FieldId{0}}},
      {stats::NodeScope{NodeId{3},SupportRole::survivors},std::vector<FieldId>{FieldId{0}}},
      {stats::NodeScope{NodeId{3},SupportRole::parent_support},{}},
      {stats::NodeScope{NodeId{3},SupportRole::visible},{}}}};
  const auto hc=hidden.capture_statistics(hidden_request);check(hc.components().size()==6);
  check(hc.components()[0].cardinality==2 && hc.components()[1].cardinality==1);
  distribution(hc.components()[0],Counts{{Row{n(7)},1},{Row{n(8)},1}},2);
  distribution(hc.components()[1],Counts{{Row{n(7)},1}},1);
  for(std::size_t i=2;i<5;++i){
    check(hc.components()[i].cardinality==3);
    distribution(hc.components()[i],Counts{{Row{n(1)},1},{Row{n(2)},1},{Row{n(3)},1}},3);
  }
  check(hc.components()[5].availability==stats::Availability::not_applicable && !hc.components()[5].cardinality && !hc.components()[5].distribution);
  // 10. Delta private/committed-unread forwarding; no output drain needed for capture.
  DeltaOptions delta_options;delta_options.mode=DeltaMode::delta;auto delta=DeltaRuntime::initialize(p,db,delta_options);
  auto pending=delta.begin({1,TableId{1},SetOperation::insert,{n(8)}});check(delta.capture_statistics(r).availability()==stats::Availability::pending_private_state);
  pending.drain();auto unread=pending.commit();check(delta.capture_statistics(r).components()[5].distribution->heavy_keys->front().count==3);
  // 11. Session forwarding and release do not retain engine rows in old report.
  auto session=QuerySession::create_typed(p,db);auto saved=*session->capture_statistics(r);session->drop();
  check(!session->capture_statistics(r) && !session->statistics_freshness(saved));same_facts(captured,saved);
  // 12. Finite request admission and invalid field/index contract errors.
  auto excessive=r;excessive.selections.resize(257,r.selections.front());bool rejected=false;
  try{static_cast<void>(replayed.capture_statistics(excessive));}catch(const Error&){rejected=true;}check(rejected);
  auto invalid=r;invalid.selections[0].fields=std::vector<FieldId>{FieldId{100}};rejected=false;
  try{static_cast<void>(replayed.capture_statistics(invalid));}catch(const Error&){rejected=true;}check(rejected);
  stats::OwnerRequest wrong_index{{{stats::IndexScope{IndexRequirementId{100000}}, {}}}};rejected=false;
  try{static_cast<void>(replayed.capture_statistics(wrong_index));}catch(const Error&){rejected=true;}check(rejected);
  stats::OwnerRequest wrong_support{{{stats::NodeScope{NodeId{0},SupportRole::parent_support},std::vector<FieldId>{}}}};rejected=false;
  try{static_cast<void>(replayed.capture_statistics(wrong_support));}catch(const Error&){rejected=true;}check(rejected);
  // 13. Source derivations change without changing native/S/P/E membership.
  auto projected=PhysicalRuntime::initialize(p,db);
  static_cast<void>(projected.apply({1,TableId{0},SetOperation::insert,{n(1),n(7),n(12)}}));
  const auto third=projected.capture_statistics(r);
  auto three_derivations=db;three_derivations.tables[0].insert(Row{n(1),n(7),n(12)});fixture_facts(third,three_derivations);
  check(third.components()[0].cardinality==5 && third.components()[2].cardinality==3 && third.components()[3].cardinality==3 && third.components()[4].cardinality==2);
  derivations.at(Row{n(1),n(7)})=3;distribution(third.components()[2],derivations,3);
  distribution(third.components()[5],parent_counts,1);distribution(third.components()[6],visible_counts,2);
  static_cast<void>(projected.apply({2,TableId{0},SetOperation::insert,{n(1),n(7),n(12)}}));
  static_cast<void>(projected.apply({3,TableId{0},SetOperation::erase,{n(1),n(7),n(99)}}));
  same_facts(third,projected.capture_statistics(r));check(projected.statistics_freshness(third,2)==stats::Freshness::within_lag);
  for(std::int64_t suffix=10;suffix<=12;++suffix)
    static_cast<void>(projected.apply({static_cast<std::uint64_t>(suffix-6),TableId{0},SetOperation::erase,{n(1),n(7),n(suffix)}}));
  const auto removed=projected.capture_statistics(r);
  auto removed_derivations=three_derivations;
  for(std::int64_t suffix=10;suffix<=12;++suffix)removed_derivations.tables[0].erase(Row{n(1),n(7),n(suffix)});
  fixture_facts(removed,removed_derivations);
  check(removed.components()[0].cardinality==2 && removed.components()[2].cardinality==2 && removed.components()[3].cardinality==2 && removed.components()[4].cardinality==1);
  distribution(removed.components()[5],Counts{{Row{},1}},1);
  // 14. Exact/one-under shared bounds; the final incomplete component exposes no prefix facts.
  for(int kind=0;kind<4;++kind){
    stats::Limits bounds;
    if(kind==0)bounds.work=captured.usage().work;
    if(kind==1)bounds.rows=captured.usage().rows;
    if(kind==2)bounds.distinct_keys=captured.usage().distinct_keys;
    if(kind==3)bounds.accounted_bytes=captured.usage().accounted_bytes;
    same_facts(captured,replayed.capture_statistics(r,bounds));
    if(kind==0)--bounds.work;
    if(kind==1)--bounds.rows;
    if(kind==2)--bounds.distinct_keys;
    if(kind==3)--bounds.accounted_bytes;
    const auto one_under=replayed.capture_statistics(r,bounds);
    check(one_under.availability()==stats::Availability::budget_exhausted);
    for(const auto& c:one_under.components())if(c.availability==stats::Availability::budget_exhausted && c.distribution)
      check(!c.distribution->ndv && !c.distribution->heavy_keys && c.distribution->histogram.empty());
  }
  // 15. Ordered/repeated fields and empty projections retain owning source descriptors.
  stats::OwnerRequest reordered{{{stats::SourceScope{TableId{0}},std::vector<FieldId>{FieldId{1},FieldId{0},FieldId{1}}},
      {stats::SourceScope{TableId{2}},std::vector<FieldId>{}}}};
  const auto ordered=replayed.capture_statistics(reordered);
  Counts expected_order;for(const auto& row:db.tables[0])++expected_order[Row{row[1],row[0],row[1]}];
  distribution(ordered.components()[0],expected_order,4);distribution(ordered.components()[1],Counts{{Row{},1}},1);
  check(ordered.components()[0].layout->same_token(replayed.source_layout(TableId{0})));
  reordered.selections[0].fields->clear();
  check(ordered.components()[0].selection.fields->size()==3 && ordered.requested_components()==2 && ordered.limits().heavy_keys==16);
  stats::Limits top_one;top_one.heavy_keys=1;
  const auto top=replayed.capture_statistics(r,top_one);distribution(top.components()[2],Counts{{Row{n(1),n(7)},2},{Row{n(2),n(7)},1},{Row{n(3),n(8)},1}},3,1);
  // 16. Empty data has exact zero NDV and known empty maps, including empty projection.
  auto empty_db=db;for(auto& table:empty_db.tables)table.clear();auto empty_owner=PhysicalRuntime::initialize(p,empty_db);
  const auto empty=empty_owner.capture_statistics(r);fixture_facts(empty,empty_db);for(const auto& component:empty.components()){
    check(component.cardinality==0);if(component.distribution)distribution(component,Counts{},0);
  }
  stats::OwnerRequest empty_key{{{stats::SourceScope{TableId{0}},std::vector<FieldId>{}}}};
  distribution(empty_owner.capture_statistics(empty_key).components()[0],Counts{},0);
  // 17. A paused session with tentative work stays metadata-only; stop rolls it back.
  auto paused=QuerySession::create(p,db,std::make_unique<std::istringstream>(""));
  same_facts(captured,*paused->capture_statistics(r));paused->start();paused->pause();same_facts(captured,*paused->capture_statistics(r));paused->drop();
  auto private_session=QuerySession::create(p,db,std::make_unique<std::istringstream>(
      io::write_input_json(io::InputEvent{PhysicalSetUpdate{1,TableId{1},SetOperation::insert,{n(8)}},{}},p.source_catalog())+"\n"));
  private_session->start();check(private_session->begin_next());private_session->pause();
  const auto session_pending=*private_session->capture_statistics(r);
  check(session_pending.availability()==stats::Availability::pending_private_state && session_pending.components().empty());
  check(private_session->statistics_freshness(session_pending)==stats::Freshness::current);
  private_session->stop();same_facts(captured,*private_session->capture_statistics(r));
  // 18. Report keys and plan bindings survive destruction of their original owner.
  const auto orphan=[](){auto owner=PhysicalRuntime::initialize(plan(),database());return owner.capture_statistics(request(owner.plan()));}();
  same_facts(captured,orphan);check(orphan.plan().source_catalog().tables.at(2).name=="unused");
  std::cout<<"18 owner capture test groups passed\n";
}
