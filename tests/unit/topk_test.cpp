#include "crown/runtime/topk.hpp"
#include "crown/api/error.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cells=std::vector<sql_rows::Cell>;
using Row=aggregate::Row;
using Key=topk::Key;
using Direction=topk::Direction;
using Nulls=topk::NullOrder;
constexpr std::uint64_t grant=16ULL*1024*1024;
std::uint64_t checks=0;

sql_rows::Cell n(std::int64_t x) {return storage::ScalarView{x};}
sql_rows::Cell t(std::string_view x) {return storage::ScalarView{x};}
Catalog catalog() {
  return {1,{{"r",{{"id",ScalarType::int64},{"x",ScalarType::int64,true},
      {"t",ScalarType::string,true},{"flag",ScalarType::boolean,true},
      {"d",ScalarType::date,true},{"n",ScalarType::decimal,true}}}}};
}
Cells row(std::int64_t id,sql_rows::Cell x,sql_rows::Cell text={}) {
  return {n(id),x,text,{}, {}, {}};
}
frontend::SqlRowsProgram rows_program(std::string_view sql) {
  auto bound=frontend::bind_sql_rows(sql,catalog());
  if(const auto* e=std::get_if<frontend::BindingDiagnostic>(&bound))throw Error(e->diagnostic.code,e->diagnostic.message);
  return std::get<frontend::SqlRowsProgram>(std::move(bound));
}
frontend::SqlAggregateProgram aggregate_program(std::string_view sql) {
  frontend::SqlAggregateBindOptions options;options.kernel.average_scale=2;
  auto bound=frontend::bind_sql_aggregate(sql,catalog(),options);
  if(const auto* e=std::get_if<frontend::BindingDiagnostic>(&bound))throw Error(e->diagnostic.code,e->diagnostic.message);
  return std::get<frontend::SqlAggregateProgram>(std::move(bound));
}
FreeConnexTree tree(const frontend::SqlRowsProgram& program) {
  if(program.contradiction())return {};
  const auto core=program.export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
  assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;
}
SqlRowsRuntime rows_owner(std::string_view sql,bool indexed,const resource::MemoryAccount& account={}) {
  const auto program=rows_program(sql);const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
  if(account)return SqlRowsRuntime::create_into(account,program,tree(program),physical);
  return SqlRowsRuntime(program,tree(program),physical);
}
SqlAggregateRuntime aggregate_owner(std::string_view sql,bool indexed,const resource::MemoryAccount& account={}) {
  const auto program=aggregate_program(sql);const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
  if(account)return SqlAggregateRuntime::create_into(account,program,tree(program.source_program()),physical);
  return SqlAggregateRuntime(program,tree(program.source_program()),physical);
}
template<class Owner> void replace(Owner& owner,const Cells& values,std::uint64_t before,std::uint64_t after) {
  const std::array edits{sql_rows::SourceReplacement{TableId{0},values,before,after}};
  static_cast<void>(owner.prepare_batch({owner.sequence()+1,edits}).commit());
}
template<class Action> void error(Action action,std::string_view code) {
  bool refused=false;
  try{action();}catch(const Error& e){assert(e.code()==code);refused=true;}
  assert(refused);++checks;
}
std::int64_t integer(const aggregate::Tuple& tuple,std::size_t index=0) {
  return std::get<std::int64_t>(*tuple.export_values()[index]);
}
std::vector<std::int64_t> identities(const topk::Snapshot& snapshot) {
  std::vector<std::int64_t> result;
  for(const auto& entry:snapshot.entries)result.push_back(integer(entry.identity));
  return result;
}

// NULL placement is independent of direction, while final ties use identity.
void rank_and_ties(bool indexed) {
  auto owner=rows_owner("SELECT x,t FROM r",indexed);
  const std::array source{row(1,n(2),t("b")),row(2,n(2),t("a")),row(3,{},t("n")),row(4,n(-1),t("z"))};
  for(const auto& value:source)replace(owner,value,0,1);
  for(const auto direction:{Direction::ascending,Direction::descending})for(const auto nulls:{Nulls::first,Nulls::last}) {
    const std::array order{Key{0,direction,nulls}};const auto result=snapshot_topk(owner,order,99);
    assert(result.selected_rows==4 && result.entries.size()==4 && result.sequence==owner.sequence());
    const auto null_index=nulls==Nulls::first?0U:3U;assert(!result.entries[null_index].values.view()[0]);
    const auto first=nulls==Nulls::first?1U:0U;
    assert(integer(result.entries[first].values)==(direction==Direction::ascending?-1:2));
    const auto tie=direction==Direction::ascending?first+1:first;
    assert(std::get<std::string>(*result.entries[tie].values.export_values()[1])=="a");
    assert(std::get<std::string>(*result.entries[tie+1].values.export_values()[1])=="b");
    ++checks;
  }
  const std::array multi{Key{0,Direction::descending,Nulls::last},Key{1,Direction::descending,Nulls::first}};
  const auto reverse=snapshot_topk(owner,multi,1);
  assert(std::get<std::string>(*reverse.entries[0].values.export_values()[1])=="b");
  const std::array repeated{Key{0},Key{0}};assert(snapshot_topk(owner,repeated,1).selected_rows==1);++checks;
}

// A huge bag is selected as one compressed record, including a partial cutoff.
void multiplicities_and_wrappers(bool indexed) {
  auto owner=rows_owner("SELECT x FROM r",indexed);const auto physical=row(1,n(7));
  replace(owner,physical,0,UINT64_MAX);
  for(const auto k:{std::uint64_t{1},(std::uint64_t{1}<<53)+3,UINT64_MAX}) {
    const auto result=snapshot_topk(owner,{},k);
    assert(result.entries.size()==1 && result.entries[0].multiplicity==k && result.selected_rows==k);
    assert(integer(result.entries[0].identity)==7 && result.entries[0].identity==result.entries[0].values);++checks;
  }
  replace(owner,physical,UINT64_MAX,0);assert(snapshot_topk(owner,{},UINT64_MAX).entries.empty());
  auto distinct=rows_owner("SELECT DISTINCT x FROM r",indexed);replace(distinct,physical,0,17);
  assert(snapshot_topk(distinct,{},99).entries[0].multiplicity==1);
  auto exists=rows_owner("SELECT EXISTS(SELECT x FROM r)",indexed);
  for(const bool present:{false,true,false}) {
    if(present)replace(exists,physical,0,2);else if(exists.sequence())replace(exists,physical,2,0);
    const auto result=snapshot_topk(exists,{},1);assert(result.entries.size()==1 && result.selected_rows==1);
    assert(std::get<bool>(*result.entries[0].values.export_values()[0])==present);++checks;
  }
}

// Decimal and binary TEXT keys must use exact value order, never rendered text.
void scalar_order(bool indexed) {
  auto owner=rows_owner("SELECT n,t,d,flag,x FROM r",indexed);
  std::vector<Cells> source;
  const std::array numbers{"10","2","-10","-2","0.00000000000000000000000000000000000001"};
  for(std::size_t i=0;i<numbers.size();++i) {
    auto value=row(static_cast<std::int64_t>(i),n(i==0?INT64_MIN:INT64_MAX),t(i%2?"a":"z"));
    value[3]=storage::ScalarView{i%2==0};value[4]=storage::ScalarView{Date::parse(i%2?"0001-01-01":"9999-12-31")};
    value[5]=storage::ScalarView{storage::InlineDecimal::parse(numbers[i])};source.push_back(value);replace(owner,source.back(),0,1);
  }
  const auto numeric=snapshot_topk(owner,std::array{Key{0}},99);
  const std::array expected{"-10","-2","0.00000000000000000000000000000000000001","2","10"};
  for(std::size_t i=0;i<expected.size();++i)assert(std::get<Decimal>(*numeric.entries[i].values.export_values()[0])==Decimal::parse(expected[i]));
  const auto low=snapshot_topk(owner,std::array{Key{4}},99);
  const auto high_int=snapshot_topk(owner,std::array{Key{4,Direction::descending}},99);
  assert(integer(low.entries.front().values,4)==INT64_MIN && integer(low.entries.back().values,4)==INT64_MAX);
  assert(integer(high_int.entries.front().values,4)==INT64_MAX && integer(high_int.entries.back().values,4)==INT64_MIN);
  const auto booleans=snapshot_topk(owner,std::array{Key{3}},99);
  const auto reverse_booleans=snapshot_topk(owner,std::array{Key{3,Direction::descending}},99);
  assert(!std::get<bool>(*booleans.entries.front().values.export_values()[3]) && std::get<bool>(*booleans.entries.back().values.export_values()[3]));
  assert(std::get<bool>(*reverse_booleans.entries.front().values.export_values()[3]) && !std::get<bool>(*reverse_booleans.entries.back().values.export_values()[3]));
  const auto dates=snapshot_topk(owner,std::array{Key{2}},99);
  const auto reverse_dates=snapshot_topk(owner,std::array{Key{2,Direction::descending}},99);
  assert(std::get<Date>(*dates.entries.front().values.export_values()[2])==Date::parse("0001-01-01"));
  assert(std::get<Date>(*reverse_dates.entries.front().values.export_values()[2])==Date::parse("9999-12-31"));
  auto strings=rows_owner("SELECT t FROM r",indexed);const std::string control("a\x01z",3),high("\xc2\x80",2);
  const std::array text_rows{row(1,{},t(high)),row(2,{},t(control)),row(3,{},t("a")),row(4,{},t(""))};
  for(const auto& value:text_rows)replace(strings,value,0,1);
  const auto text=snapshot_topk(strings,std::array{Key{0}},99);
  const auto sequence=strings.sequence();const std::string nul("a\0z",3),invalid(1,static_cast<char>(0xff));
  error([&]{replace(strings,row(9,{},t(nul)),0,1);},"invalid_sql_rows_row");
  error([&]{replace(strings,row(9,{},t(invalid)),0,1);},"invalid_sql_rows_row");
  assert(strings.ready() && strings.sequence()==sequence);
  assert((std::vector<std::string>{std::get<std::string>(*text.entries[0].values.export_values()[0]),
      std::get<std::string>(*text.entries[1].values.export_values()[0]),std::get<std::string>(*text.entries[2].values.export_values()[0]),
      std::get<std::string>(*text.entries[3].values.export_values()[0])}==std::vector<std::string>{"","a",control,high}));++checks;
}

// Group identity survives omitted keys and equal rendered values at the cutoff.
void aggregate_identity_and_updates(bool indexed) {
  auto owner=aggregate_owner("SELECT COUNT(*) FROM r GROUP BY id",indexed);
  const std::array physical{row(3,n(9)),row(1,n(-3)),row(2,{})};
  for(const auto& value:physical)replace(owner,value,0,2);
  const auto first=snapshot_topk(owner,std::array{Key{0,Direction::descending}},2);
  assert((identities(first)==std::vector<std::int64_t>{1,2}));
  assert(first.entries[0].multiplicity==1 && integer(first.entries[0].values)==2);
  replace(owner,physical[0],2,3);
  const auto changed=snapshot_topk(owner,std::array{Key{0,Direction::descending}},2);
  assert((identities(changed)==std::vector<std::int64_t>{3,1}));
  replace(owner,physical[0],3,0);assert((identities(snapshot_topk(owner,{},99))==std::vector<std::int64_t>{1,2}));
  auto measures=aggregate_owner("SELECT SUM(x),AVG(x) FROM r GROUP BY id",indexed);
  const std::array measured{row(1,n(2)),row(2,n(-3)),row(3,{}),row(4,n(2))};
  for(std::size_t i=0;i<measured.size();++i)replace(measures,measured[i],0,i==0?1:i==2?3:2);
  assert((identities(snapshot_topk(measures,std::array{Key{0,Direction::ascending,Nulls::last}},99))==std::vector<std::int64_t>{2,1,4,3}));
  assert((identities(snapshot_topk(measures,std::array{Key{0,Direction::descending,Nulls::first}},99))==std::vector<std::int64_t>{3,4,1,2}));
  assert((identities(snapshot_topk(measures,std::array{Key{1,Direction::ascending,Nulls::first}},99))==std::vector<std::int64_t>{3,2,1,4}));
  assert((identities(snapshot_topk(measures,std::array{Key{1,Direction::descending,Nulls::last}},99))==std::vector<std::int64_t>{1,4,2,3}));
  auto global=aggregate_owner("SELECT COUNT(*),SUM(x),AVG(x) FROM r",indexed);
  const auto empty=snapshot_topk(global,{},1);assert(empty.entries.size()==1 && empty.entries[0].identity.size()==0);
  const auto output=empty.entries[0].values.export_values();assert(std::get<std::int64_t>(*output[0])==0 && !output[1] && !output[2]);
  auto grouped=aggregate_owner("SELECT COUNT(*) FROM r GROUP BY id",indexed);assert(snapshot_topk(grouped,{},1).entries.empty());++checks;
}

// A valid k=0 uses no producer or allocation, but order and busy admission remain.
void admission_and_zero(bool indexed) {
  auto owner=rows_owner("SELECT x FROM r",indexed);const auto physical=row(1,n(4));replace(owner,physical,0,3);
  const auto account=owner.program().account();const auto baseline=account.statistics().current;std::size_t calls=0;
  {s04_alloc::Scope deny(0);const auto zero=snapshot_topk(owner,{},0,{0,0,0});assert(zero.entries.empty() && zero.selected_rows==0);calls=s04_alloc::calls;}
  assert(calls==0 && account.statistics().current==baseline);
  error([&]{static_cast<void>(snapshot_topk(owner,std::array{Key{1}},0));},"topk_order");
  error([&]{static_cast<void>(snapshot_topk(owner,std::array{Key{0,static_cast<Direction>(99)}},0));},"topk_order");
  error([&]{static_cast<void>(snapshot_topk(owner,std::array{Key{0,Direction::ascending,static_cast<Nulls>(99)}},0));},"topk_order");
  error([&]{static_cast<void>(snapshot_topk(owner,std::array{Key{0}},0,{0,0,0}));},"topk_work_limit");
  {
    auto pending=owner.prepare_batch({owner.sequence()+1,{}});
    error([&]{static_cast<void>(snapshot_topk(owner,{},0,{0,0,0}));},"topk_busy");
  }
  auto aggregate=aggregate_owner("SELECT COUNT(*) FROM r",indexed);
  {
    auto pending=aggregate.prepare_batch({1,{}});
    error([&]{static_cast<void>(snapshot_topk(aggregate,{},0,{0,0,0}));},"topk_busy");
  }
  {s04_alloc::Scope deny(0);const auto zero=snapshot_topk(aggregate,{},0,{0,0,0});assert(zero.entries.empty() && s04_alloc::calls==0);}
  ++checks;
}

// Denied collection, sort and allocation release their local handles and lease.
void resource_and_ownership(bool indexed) {
  const auto account=resource::MemoryAccount::create(grant);auto owner=rows_owner("SELECT x,t FROM r",indexed,account);
  const std::array physical{row(1,n(3),t("c")),row(2,n(1),t("a")),row(3,n(2),t("b"))};
  for(const auto& value:physical)replace(owner,value,0,1);
  const std::array order{Key{0}};std::uint64_t work=0;
  {const auto warm=snapshot_topk(owner,order,1);work=warm.metrics.work;assert(warm.entries.size()==1 && warm.metrics.candidates==3);assert(warm.entries.capacity()<=2);}
  const auto baseline=account.statistics().current;const auto sequence=owner.sequence();
  {const auto exact=snapshot_topk(owner,order,1,{3,work,1000000});assert(exact.metrics.work==work);}
  error([&]{static_cast<void>(snapshot_topk(owner,order,1,{3,work-1,1000000}));},"topk_work_limit");
  error([&]{static_cast<void>(snapshot_topk(owner,order,1,{2,1000000,1000000}));},"topk_result_limit");
  bool producer_refused=false;
  try{static_cast<void>(snapshot_topk(owner,order,1,{3,1000000,0}));}catch(const Error&){producer_refused=true;}
  assert(producer_refused && owner.ready() && owner.sequence()==sequence && account.statistics().current==baseline);
  const auto free=account.statistics().limit_bytes-baseline.requested_bytes;
  const auto overhead=resource::MemoryAccount::allocation_bytes(0,alignof(std::max_align_t));assert(free>overhead);
  {
    auto filler=account.allocate(static_cast<std::size_t>(free-overhead));bool limited=false;
    try{static_cast<void>(snapshot_topk(owner,order,1));}catch(const resource::MemoryFailure& e){limited=e.fault()==resource::MemoryFault::limit;}
    assert(limited && owner.ready() && owner.sequence()==sequence);
  }
  assert(account.statistics().current==baseline);
  bool succeeded=false;std::size_t failures=0;
  for(std::ptrdiff_t cut=0;cut<256 && !succeeded;++cut) {
    bool failed=false,triggered=false;
    {
      s04_alloc::Scope deny(cut);
      try{const auto result=snapshot_topk(owner,order,1);assert(result.selected_rows==1);succeeded=true;}
      catch(const std::bad_alloc&){failed=true;}
      triggered=s04_alloc::triggered;
    }
    assert(failed==triggered && owner.ready() && owner.sequence()==sequence && account.statistics().current==baseline);
    failures+=failed;
  }
  assert(succeeded && failures>0);replace(owner,physical[1],1,0);assert(owner.sequence()==sequence+1);
  std::optional<topk::Snapshot> kept;
  {
    auto local=rows_owner("SELECT t FROM r",indexed,account);const std::string text(512,'q');replace(local,row(1,{},t(text)),0,4);
    kept.emplace(snapshot_topk(local,{},2));auto moved=std::move(local);static_cast<void>(moved);
  }
  assert(kept->entries.size()==1 && kept->entries[0].multiplicity==2);
  assert(std::get<std::string>(*kept->entries[0].values.export_values()[0])==std::string(512,'q'));
  assert(std::get<frontend::SqlRowsProgram>(kept->program).source()=="SELECT t FROM r");kept.reset();account.check_invariants();++checks;
}
} // namespace

int main() {
  for(const bool indexed:{false,true}) {
    rank_and_ties(indexed);multiplicities_and_wrappers(indexed);scalar_order(indexed);
    aggregate_identity_and_updates(indexed);admission_and_zero(indexed);resource_and_ownership(indexed);
  }
  std::cout<<"snapshot top-k: "<<checks<<" identity/rank/bag/NULL/resource/ownership controls passed\n";
}
