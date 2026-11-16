#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/memory_report.hpp"
#include "crown/runtime/session.hpp"
#include "crown/io/memory_report.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <variant>

using namespace crown;
using namespace crown::runtime;
namespace mm=crown::runtime::memory;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
enum class Kind {support,physical,delta,session};
using Owner=std::variant<SupportRuntime,PhysicalRuntime,DeltaRuntime,QuerySession::Owner>;
void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(message));}
void sum(resource::MemoryUsage& a,const resource::MemoryUsage& b){a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;}
resource::MemoryAccount account(const Owner& owner) {
  return std::visit([](const auto& value) {
    if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return value.get_deleter().account();
    else return value.plan().account();
  },owner);
}
Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap,LiveMaintenance live=LiveMaintenance::on_output) {
  PhysicalRuntimeOptions options;options.support.memory_limit_bytes=cap;options.support.capture_transitions=false;
  if(kind==Kind::support) {
    SupportRuntime owner(plan,options.support);std::uint64_t sequence=0;
    for(std::size_t i=0;i<plan.inputs().size();++i)for(const auto& row:database.tables[plan.inputs()[i].base.value]) {
      const auto tuple=plan.adapt_input(OccurrenceId{i},row);
      if(tuple)static_cast<void>(owner.apply({++sequence,plan.inputs()[i].node,SetOperation::insert,storage::export_row(tuple->values())}));
    }
    return owner;
  }
  if(kind==Kind::physical)return PhysicalRuntime::initialize(plan,database,options);
  DeltaOptions delta;delta.physical=options;delta.mode=DeltaMode::delta;delta.live_maintenance=live;
  if(kind==Kind::delta)return DeltaRuntime::initialize(plan,database,delta);
  SessionOptions session;session.delta=delta;return QuerySession::create_typed(plan,database,{},session);
}
mm::Attempt capture(const Owner& owner,mm::Limits limits={}) {
  return std::visit([&](const auto& value) {
    if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return mm::capture(*value,limits);
    else return mm::capture(value,limits);
  },owner);
}
mm::Report accepted(mm::Attempt attempt) {
  if(attempt.stop!=mm::Stop::complete || !attempt.report)throw std::runtime_error("operator memory capture stop="+std::to_string(static_cast<unsigned>(attempt.stop)));
  return *attempt.report;
}
void verify(const mm::Report& report,const resource::MemoryAccount& account) {
  const auto& snapshot=report.snapshot();check(snapshot.account.owner==account.statistics().owner,"memory report minted another account");
  check(report.owners().get_allocator().account().statistics().owner==snapshot.account.owner &&
      report.tables().get_allocator().account().statistics().owner==snapshot.account.owner &&
      report.operators().get_allocator().account().statistics().owner==snapshot.account.owner,"memory report retained an unfunded inventory");
  resource::MemoryUsage total;std::array<resource::MemoryUsage,resource::memory_purpose_count> purposes{};
  std::array<resource::MemoryUsage,resource::allocation_lifetime_count> lifetimes{};
  std::optional<resource::MemoryAttribution> previous;
  for(const auto& owner:report.owners()) {
    check(!previous || *previous<owner.attribution,"owner partition is duplicated or unsorted");previous=owner.attribution;
    check(owner.account_owner==snapshot.account.owner,"owner partition includes a different account");sum(total,owner.current);
    for(std::size_t i=0;i<purposes.size();++i)sum(purposes[i],owner.by_purpose[i]);
    for(std::size_t i=0;i<lifetimes.size();++i)sum(lifetimes[i],owner.by_lifetime[i]);
  }
  check(total==snapshot.account.current && purposes==snapshot.account.by_purpose && lifetimes==snapshot.account.by_lifetime,"actual owner bytes do not reconcile");
  const auto find=[&](resource::MemoryAttribution key)->const resource::AttributedMemoryStatistics& {
    for(const auto& row:report.owners())if(row.attribution==key)return row;
    throw std::runtime_error("operator memory binding has no allocation partition");
  };
  for(const auto& table:report.tables())std::visit([&](const auto& value) {
    check(value.table==find(value.table.attribution) && value.arena.owner==find(value.arena.owner.attribution),"table/arena bytes have no authentic owner join");
    check(value.arena.records.live_records==table.live_records && value.arena.live_slots.allocations==table.live_records &&
        value.arena.live_values.allocations==table.live_records && value.arena.retained_slots.allocations==value.arena.records.retained_records &&
        value.arena.free_slots.allocations==value.arena.records.free_slots,"arena slot/value bytes disagree with real record counts");
  },table.memory);
  for(const auto& operation:report.operators())std::visit([&](const auto& value){static_cast<void>(find(value.attribution));},operation);
}
void oracle(const mm::Report& report,const Owner& owner) {
  if(report.snapshot().availability!=mm::Availability::committed) {
    check(report.tables().empty() && report.operators().empty(),"pending/released report exposed committed operator facts");return;
  }
  std::visit([&](const auto& value) {
    using T=std::decay_t<decltype(value)>;
    if constexpr(!std::is_same_v<T,QuerySession::Owner>) {
      const auto state=value.canonical_state();
      const auto& support=[&]()->const CanonicalSupportState& {
        if constexpr(std::is_same_v<T,SupportRuntime>)return state;
        else if constexpr(std::is_same_v<T,DeltaRuntime>)return state.physical.support;
        else return state.support;
      }();
      for(const auto& table:report.tables()) {
        if(table.scope!=mm::TableScope::support || !table.node)continue;
        const auto found=std::find_if(support.nodes.begin(),support.nodes.end(),[&](const auto& node){return node.node==*table.node;});
        check(found!=support.nodes.end(),"operator report references an unknown canonical node");
        if(table.role==RelationRole::visible)check(found->visible.has_value(),"visible operator table has no canonical factor");
        const auto expected=table.role==RelationRole::native_records || table.role==RelationRole::generalized_candidates?found->records.size():
            table.role==RelationRole::survivors?found->survivors.size():table.role==RelationRole::parent_support?found->parent.size():found->visible->size();
        check(table.live_records==expected,"real operator report differs from independent canonical record inventory");
      }
      for(const auto& operation:report.operators())if(const auto* node=std::get_if<mm::SupportNode>(&operation)) {
        const auto found=std::find_if(support.nodes.begin(),support.nodes.end(),[&](const auto& n){return n.node==node->node;});
        check(found!=support.nodes.end() && node->records==found->records.size() && node->survivors==found->survivors.size() &&
            node->parent_keys==found->parent.size() && node->visible_keys.has_value()==found->visible.has_value(),"operator metadata counts differ from canonical state");
        if(node->visible_keys)check(*node->visible_keys==found->visible->size(),"visible factor cardinality differs from canonical state");
      }
      if constexpr(std::is_same_v<T,DeltaRuntime>) {
        for(const auto& operation:report.operators())if(const auto* factor=std::get_if<mm::DeltaFactor>(&operation)) {
          check(factor->materialized.has_value()==state.live.has_value(),"unmaterialized live image was labeled empty");
          if(state.live) {
            const auto found=std::find_if(state.live->factors.begin(),state.live->factors.end(),[&](const auto& f){return f.node==factor->node;});
            check(found!=state.live->factors.end() && factor->materialized->rows==found->rows.size() &&
                factor->materialized->parent_keys==found->parents.size() && factor->materialized->child_keys==found->children.size(),"live factor/index counts disagree with canonical state");
            std::uint64_t parents=0,children=0;for(const auto& x:found->parents)parents+=x.rows.size();for(const auto& x:found->children)children+=x.rows.size();
            check(parents==factor->materialized->parent_rows && children==factor->materialized->child_rows,"live index membership count was replaced by bucket count");
          }
        }
      }
    }
  },owner);
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto now=account.statistics().current;
  check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"memory report retained closed runtime storage");
}
template<class Make> void lifetime(Make make) {
  std::optional<Owner> owner(make(allowance));const auto account=::account(*owner);const auto before=account.statistics();mm::Attempt attempt;std::size_t calls=0;
  {s04_alloc::Scope count;attempt=capture(*owner);calls=s04_alloc::calls;}
  std::optional<mm::Report> held(accepted(std::move(attempt)));attempt.report.reset();
  check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations,"operator report allocated outside the original account");
  check(held->snapshot().account==account.statistics(),"report instant contains released capture scratch or misses its own storage");
  verify(*held,account);oracle(*held,*owner);std::optional<mm::Report> copy;
  {s04_alloc::Scope none(0);copy=*held;owner.reset();verify(*held,account);verify(*copy,account);held.reset();copy.reset();}
  controller_only(account);
}
template<class Make> std::size_t faults(Make make) {
  auto owner=make(allowance);const auto account=::account(owner);const auto held=accepted(capture(owner));std::size_t expected=0;
  {s04_alloc::Scope count;const auto next=capture(owner);expected=s04_alloc::calls;}
  check(expected>0 && expected<256,"operator report fault calibration exceeds bound");
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=account.statistics().current;mm::Attempt attempt;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));attempt=capture(owner);calls=s04_alloc::calls;}
    if(point<expected) {
      check(attempt.stop==mm::Stop::allocation_failure && !attempt.report && calls==point+1 && account.statistics().current==before,
          "failed operator report leaked, hid a request or published a partial partition");attempt=capture(owner);
    }else check(attempt.stop==mm::Stop::complete && calls==expected,"operator report missed a persistent fault position");
    verify(accepted(std::move(attempt)),account);verify(held,account);account.check_invariants();
  }
  return expected;
}
template<class Make> void limits(Make make) {
  mm::Usage needed;
  {auto owner=make(allowance);needed=accepted(capture(owner)).usage();}
  for(unsigned dimension=0;dimension<4;++dimension)for(const bool exact:{true,false}) {
    auto owner=make(allowance);mm::Limits cap;
    if(dimension==0)cap.work=needed.work-(exact?0:1);
    if(dimension==1)cap.owners=needed.owners-(exact?0:1);
    if(dimension==2)cap.tables=needed.tables-(exact?0:1);
    if(dimension==3)cap.operators=needed.operators-(exact?0:1);
    const auto account=::account(owner);const auto before=account.statistics().current;const auto result=capture(owner,cap);
    if(exact)verify(accepted(result),account);
    else {
      const auto expected=dimension==0?mm::Stop::work_limit:dimension==1?mm::Stop::owner_limit:dimension==2?mm::Stop::table_limit:mm::Stop::operator_limit;
      check(result.stop==expected && !result.report && account.statistics().current==before,"report exact/one-under logical admission did not preserve the owner");
    }
  }
  std::uint64_t peak=0;std::size_t pins=0;
  {auto owner=make(allowance);const auto account=::account(owner);std::vector<mm::Report> held;held.reserve(2048);
    for(std::size_t i=0;i<2048;++i){const auto before=account.statistics().peak_requested_bytes;auto value=accepted(capture(owner));const auto after=account.statistics().peak_requested_bytes;
      if(i>0 && after>before){peak=after;pins=i;break;}held.push_back(std::move(value));}
  }
  check(peak>0 && pins>0,"report hoarding did not cross the real setup peak");
  for(const bool exact:{true,false}) {
    auto owner=make(exact?peak:peak-1);const auto account=::account(owner);std::vector<mm::Report> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(accepted(capture(owner)));
    const auto before=account.statistics().current;
    {const auto value=capture(owner);if(exact)verify(accepted(value),account);else check(value.stop==mm::Stop::allocation_failure && !value.report,"report ignored actual one-under query cap");}
    check(account.statistics().current==before,"report query cap leaked a tentative inventory");verify(held.front(),account);
    if(!exact){held.pop_back();verify(accepted(capture(owner)),account);check(account.statistics().limit_bytes==peak-1,"report retry minted a larger account");}
  }
}
void phases(const PhysicalPlan& plan,const c02_test::Fixture& f) {
  for(const auto kind:{Kind::support,Kind::physical,Kind::delta,Kind::session}) {
    auto owner=make_owner(plan,f.database,kind,allowance);const auto account=::account(owner);
    const auto pending_report=[&] {
      const auto value=accepted(capture(owner));check(value.snapshot().availability==mm::Availability::pending,"private operator state was labeled committed");
      verify(value,account);oracle(value,owner);const auto before=account.statistics().current;mm::Attempt failed;
      {s04_alloc::Scope deny(0);failed=capture(owner);}
      check(failed.stop==mm::Stop::allocation_failure && !failed.report && account.statistics().current==before,"failed pending report changed private storage");
    };
    std::visit([&](auto& value) {
      using T=std::decay_t<decltype(value)>;
      if constexpr(std::is_same_v<T,SupportRuntime>) {
        auto pending=value.begin_epoch(value.sequence()+1,SetOperation::erase);pending_report();check(pending.active(),"pending report closed support epoch");pending.rollback();
      }else if constexpr(std::is_same_v<T,PhysicalRuntime>) {
        auto pending=value.prepare({1,TableId{0},SetOperation::erase,*f.database.tables[0].begin()});pending_report();check(pending.active(),"pending report closed physical update");pending.rollback();
      }else if constexpr(std::is_same_v<T,DeltaRuntime>) {
        auto pending=value.begin({1,TableId{0},SetOperation::erase,*f.database.tables[0].begin()});pending_report();pending.rollback();
      }else {
        io::TransportBatch batch({io::InputEvent{{1,TableId{0},SetOperation::erase,*f.database.tables[0].begin()},{}}});
        check(value->enqueue(batch)==io::Admission::accepted,"pending report fixture rejected typed input");value->start();check(value->begin_next(),"pending report fixture did not begin");pending_report();
        value->stop();auto stopped=accepted(mm::capture(*value));check(stopped.snapshot().availability==mm::Availability::committed,"stopped report lost retained runtime");
        value->drop();const auto released=accepted(mm::capture(*value));check(released.snapshot().availability==mm::Availability::released,"dropped memory report claimed live operators");verify(released,account);oracle(released,owner);
      }
    },owner);
  }
}
void corruption(const PhysicalPlan& plan,const Database& database) {
  auto owner=make_owner(plan,database,Kind::delta,allowance);auto& delta=std::get<DeltaRuntime>(owner);
  const auto good=accepted(capture(owner));
  for(const auto component:{InvariantComponent::live_factor,InvariantComponent::live_parent,InvariantComponent::live_child}) {
    const auto old=RuntimeTestProbe::set_live_total(delta,component,999);
    check(mm::capture(delta).stop==mm::Stop::inconsistent,"memory report certified a corrupted maintained live total");
    static_cast<void>(RuntimeTestProbe::set_live_total(delta,component,old));
  }
  verify(good,account(owner));check(delta.inspect_invariants().valid(),"report corruption fixture did not restore live totals");
  const auto state=delta.canonical_state();
  for(const auto& factor:state.live->factors) {
    for(const bool child:{false,true}) {
      const auto& buckets=child?factor.children:factor.parents;
      if(buckets.empty())continue;
      const auto old=RuntimeTestProbe::set_live_bucket(delta,factor.node,child,buckets.front().key,999);
      check(mm::capture(delta).stop==mm::Stop::inconsistent,"memory report ignored a corrupted live index degree");
      static_cast<void>(RuntimeTestProbe::set_live_bucket(delta,factor.node,child,buckets.front().key,old));
    }
  }
  check(delta.inspect_invariants().valid(),"report corruption fixture did not restore live degrees");
}
void retained_and_churn(const PhysicalPlan& plan,const c02_test::Fixture& f) {
  auto owner=make_owner(plan,f.database,Kind::support,allowance);auto& support=std::get<SupportRuntime>(owner);const auto& input=plan.inputs()[0];
  const auto tuple=plan.adapt_input(OccurrenceId{0},*f.database.tables[input.base.value].begin());
  std::optional<SupportEpoch> erased(support.apply({support.sequence()+1,input.node,SetOperation::erase,storage::export_row(tuple->values())}));
  auto held=accepted(capture(owner));std::size_t retained=0;
  for(const auto& row:held.tables())retained+=std::visit([](const auto& v){return v.arena.records.retained_records;},row.memory);
  check(retained>0 && held.snapshot().account.by_lifetime[static_cast<std::size_t>(resource::AllocationLifetime::retained)].requested_bytes>0,
      "committed journal records/pins have no retained bytes in operator report");
  {s04_alloc::Scope none(0);erased.reset();}
  const auto released=accepted(capture(owner));std::size_t free=0;
  for(const auto& row:released.tables())std::visit([&](const auto& v){check(v.arena.records.retained_records==0,"released journal still reports retained rows");free+=v.arena.records.free_slots;},row.memory);
  check(free>0 && released.snapshot().account.by_lifetime[static_cast<std::size_t>(resource::AllocationLifetime::free_pool)].requested_bytes>0,
      "released record slots were not distinguished from active and historical bytes");verify(held,account(owner));verify(released,account(owner));
  auto physical=make_owner(plan,f.database,Kind::physical,allowance);auto& runtime=std::get<PhysicalRuntime>(physical);std::optional<resource::MemoryUsage> warm;
  std::uint64_t sequence=0;
  for(unsigned pass=0;pass<20;++pass) {
    static_cast<void>(runtime.apply({++sequence,TableId{0},SetOperation::insert,Row{std::int64_t{2}}}));
    {const auto value=accepted(capture(physical));verify(value,account(physical));oracle(value,physical);}
    static_cast<void>(runtime.apply({++sequence,TableId{0},SetOperation::insert,Row{std::int64_t{2}}}));
    static_cast<void>(runtime.apply({++sequence,TableId{0},SetOperation::erase,Row{std::int64_t{2}}}));
    {const auto value=accepted(capture(physical));verify(value,account(physical));oracle(value,physical);}
    const auto current=account(physical).statistics().current;
    if(warm)check(current==*warm,"no-op/churn plus memory reporting leaked query storage beyond warm capacity");else warm=current;
  }
}
void wide_and_sql(const c02_test::Fixture& base,const planner::CandidateSnapshot& candidates,bool indexed) {
  auto f=base;const auto text=std::string(4096,'w')+std::string("\0tail",5);
  f.catalog.tables[0].columns[0].type=ScalarType::string;f.catalog.tables[1].columns[0].type=ScalarType::string;f.query.variables[0].type=ScalarType::string;
  f.query.head={{VariableId{0},"x"},{VariableId{1},"y"}};
  f.database.tables={Relation{Row{text}},Relation{Row{text,std::int64_t{1}},Row{text,std::int64_t{2}}},Relation{Row{std::int64_t{1}},Row{std::int64_t{2}}}};
  std::optional<FreeConnexTree> tree;
  for(std::size_t i=0;i<candidates.candidate_count();++i)if(c02_test::shape(candidates.candidate(i)->tree())==0)tree=candidates.candidate(i)->tree();
  check(tree.has_value(),"wide report fixture has no native root");const auto options=indexed?s04_runtime::options():PhysicalOptions{};
  const auto plan=planner::lower_tree(f.catalog,f.query,*tree,options);
  for(const auto live:{LiveMaintenance::on_output,LiveMaintenance::incremental,LiveMaintenance::eager}) {
    auto owner=make_owner(plan,f.database,Kind::delta,allowance,live);const auto report=accepted(capture(owner));verify(report,account(owner));oracle(report,owner);
    bool shared_separator=false;
    for(const auto& value:report.operators())if(const auto* factor=std::get_if<mm::DeltaFactor>(&value))
      shared_separator=shared_separator || (factor->materialized && factor->materialized->parent_rows>factor->materialized->parent_keys);
    check(shared_separator,"wide report fixture did not distinguish index buckets from parent memberships");
    const auto make=[&](std::uint64_t cap){return make_owner(plan,f.database,Kind::delta,cap,live);};lifetime(make);static_cast<void>(faults(make));limits(make);
  }
  const auto bound=frontend::bind_sql(R"SQL(SELECT DISTINCT r.x,s.y FROM "R" r JOIN "S" s ON r.x=s.x JOIN "T" t ON s.y=t.y WHERE s.y>=1)SQL",f.catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound),"memory report SQL fixture did not bind");
  const auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized),"memory report SQL fixture did not normalize");
  const auto& sql=std::get<frontend::NormalizedSql>(normalized);const auto family=c02_test::candidates({sql.core_catalog,sql.core,{}},2,0);
  const auto compiled=planner::lower_normalized(sql,family.candidate(0)->tree(),options);
  for(const auto kind:{Kind::support,Kind::physical,Kind::delta,Kind::session}) {
    const auto make=[&](std::uint64_t cap){return make_owner(compiled,f.database,kind,cap);};lifetime(make);static_cast<void>(faults(make));limits(make);
  }
}
void inventory_primitive() {
  auto account=resource::MemoryAccount::create(4096);auto block=account.allocate(128,16,resource::MemoryPurpose::scratch,{resource::MemoryOwnerKind::cursor,99});
  std::array<resource::MemoryAttribution,2> owners;
  {s04_alloc::Scope none(0);check(account.copy_attributions(owners)==2 && s04_alloc::calls==0,"owner inventory allocated");}
  check(owners[0]==resource::MemoryAttribution{} && owners[1]==resource::MemoryAttribution{resource::MemoryOwnerKind::cursor,99},"owner inventory lost controller/block tags");
  bool rejected=false;
  {s04_alloc::Scope none(0);try{static_cast<void>(account.copy_attributions(std::span<resource::MemoryAttribution>(owners.data(),1)));}catch(const resource::MemoryFailure& e){rejected=e.fault()==resource::MemoryFault::contract;}}
  check(rejected,"owner inventory accepted an undersized caller buffer");
}
}
int main(int argc,char** argv) {
  try {
    inventory_primitive();const auto f=c02_test::fixture();const auto candidates=c02_test::candidates(f);
    if(argc==3 && std::string_view(argv[1])=="--export-directory") {
      std::filesystem::create_directories(argv[2]);
      for(const bool indexed:{false,true}) {
        const auto plan=planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
        for(const auto kind:{Kind::support,Kind::physical,Kind::delta,Kind::session}) {
          const auto value=make_owner(plan,f.database,kind,allowance);const auto report=accepted(capture(value));
          const auto name=std::string(indexed?"indexed-":"reference-")+std::to_string(static_cast<unsigned>(kind))+".json";
          std::ofstream(std::filesystem::path(argv[2])/name)<<io::write_memory_report(report).dump();
        }
      }
      return 0;
    }
    check(argc==1,"unknown operator memory test argument");
    for(const bool indexed:{false,true})for(std::size_t shape=0;shape<candidates.candidate_count();++shape) {
      const auto plan=planner::lower_tree(f.catalog,f.query,candidates.candidate(shape)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
      for(const auto kind:{Kind::support,Kind::physical,Kind::delta,Kind::session}) {
        const auto make=[&](std::uint64_t cap){return make_owner(plan,f.database,kind,cap);};lifetime(make);const auto positions=faults(make);limits(make);
        std::cout<<(indexed?"indexed":"reference")<<" operator kind="<<static_cast<unsigned>(kind)<<" shape="<<shape<<" faults="<<positions<<'\n';
      }
      if(shape==0){phases(plan,f);corruption(plan,f.database);retained_and_churn(plan,f);}
    }
    for(const bool indexed:{false,true})wide_and_sql(f,candidates,indexed);
    std::cout<<"authentic operator records, table/arena byte joins, whole-account partitions, original requests, persistent failures and retained report lifetimes passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
