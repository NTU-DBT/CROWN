#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/storage/physical.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::storage;
void check(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template<class Action> void error(Action&& action, std::string_view code) {
  try { action(); }
  catch (const Error& failure) { check(failure.code()==code,"wrong storage error"); return; }
  throw std::runtime_error("expected storage error");
}
TupleLayout layout() { return {LayoutId{1},{{ScalarType::int64},{ScalarType::string}}}; }
Tuple value(const TupleLayout& source, std::int64_t number) {
  return source.tuple({Value{number}, Value{std::string(240,static_cast<char>('a'+number%20))}});
}
Projection key(const TupleLayout& source) {
  return {source,projected_layout(LayoutId{2},source,std::vector<FieldId>{{0}}),{{0}}};
}
void boundaries() {
  const auto source=layout(); ReferenceTable table{RelationId{1},source};
  const auto index=table.add_index(key(source));
  const auto row=value(source,7);
  const auto first=table.insert(row).handle;
  const auto* address=table.get(first); auto cursor=table.live();
  auto one=table.pin(first), two=table.pin(first);
  const auto original=one.handle(); const auto revision=table.revision();
  check(&one.get()==address && &two.get()==address,"table pins copy payload instead of retaining it");
  check(table.insert(row).handle==first && table.revision()==revision,"duplicate row changed identity");
  check(table.arena_statistics()==ArenaStatistics{1,1,0,2,0,0},"duplicate/pin arena counts");
  check(cursor.next()==first,"pin operation invalidated live cursor");
  check(table.erase(first) && !table.get(first) && !one.is_live(),"pin kept erased membership live");
  check(one.get()==row && &one.get()==address,"erasure changed pinned payload/address");
  check(table.key_count(index)==0 && table.arena_statistics()==ArenaStatistics{1,0,1,2,0,0},"erased pinned row stayed indexed");
  error([&]{static_cast<void>(table.pin(first));},"stale_handle");
  error([&]{static_cast<void>(cursor.next());},"invalid_cursor");
  const auto second=table.insert(row).handle; auto current=table.pin(second);
  check(second.tuple.value>first.tuple.value && current.handle().slot!=original.slot,"pinned slot reused too early");
  one.reset();
  check(two.get()==row && table.arena_statistics().retained_records==1,"first pin release reclaimed shared payload");
  two.reset();
  const auto third=table.insert(value(source,8)).handle; auto reused=table.pin(third);
  check(reused.handle().slot==original.slot && reused.handle().generation==original.generation+1,"released slot not generationally reused");
  check(!table.get(first),"reused slot aliased old logical handle");
  table.clear(); table.check_invariants();
  check(table.size()==0 && !current.is_live() && !reused.is_live(),"clear kept pin memberships live");
  check(table.arena_statistics()==ArenaStatistics{2,0,2,2,0,0},"clear retention counts");
  current.reset(); reused.reset(); table.check_invariants();
  check(table.arena_statistics()==ArenaStatistics{2,0,0,0,2,0},"final releases did not reclaim table payloads");
  ReferenceTable foreign{RelationId{1},source};
  error([&]{static_cast<void>(foreign.pin(second));},"foreign_handle");
  const auto new_row=table.insert(row).handle;
  check(new_row.tuple.value>third.tuple.value,"clear reset logical ID counter");
}

void destruction_and_bulk() {
  const auto source=layout();
  std::optional<TupleArena::Pin> held;
  std::optional<ReferenceTable::Cursor> cursor;
  const Tuple* address=nullptr;
  {
    ReferenceTable table{RelationId{0},source};
    const auto nullary=table.add_index({source,projected_layout(LayoutId{3},source,{}),{}});
    for (std::int64_t i=0;i<24;++i) static_cast<void>(table.insert(value(source,i)));
    const auto handle=*table.find(value(source,11)); held.emplace(table.pin(handle));
    address=&held->get(); cursor.emplace(table.live());
    check(table.erase_key(nullary,table.projection(nullary).target().tuple({}))==24,"bulk key erase missed records");
    check(table.arena_statistics()==ArenaStatistics{24,0,1,1,23,0},"bulk erase pin/free counts");
    table.check_invariants();
    static_cast<void>(table.insert(value(source,12)));
  }
  check(held->get()==value(source,11) && &held->get()==address && !held->is_live(),"table destruction invalidated pinned value");
  error([&]{static_cast<void>(cursor->next());},"invalid_cursor");
  held.reset();

  ReferenceTable left{RelationId{1},source}, right{RelationId{2},source};
  const auto old=left.insert(value(source,1)).handle; auto old_pin=left.pin(old);
  const auto incoming=right.insert(value(source,2)).handle; auto incoming_pin=right.pin(incoming);
  left=std::move(right);
  check(!old_pin.is_live() && old_pin.get()==value(source,1),"table replacement did not retire old arena");
  check(incoming_pin.is_live() && left.get(incoming)==&incoming_pin.get(),"table move changed incoming identity");
  auto* alias=&left; left=std::move(*alias);
  check(incoming_pin.is_live() && left.get(incoming),"table self-move lost ownership");
  error([&]{static_cast<void>(right.size());},"invalid_storage");
}

void snapshot_copy() {
  const Catalog catalog{1,{{"R",{{"a",ScalarType::int64},{"b",ScalarType::string}}}}};
  const Query query{{{"a",ScalarType::int64},{"b",ScalarType::string}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}}},{{VariableId{0},"a"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}}},{},{}};
  const auto plan=planner::lower_tree(catalog,query,tree);
  ReferencePlanStorage original{plan}; const auto relation=plan.nodes()[0].records;
  auto& table=original.table(relation); const auto source=table.layout();
  const auto first=table.insert(value(source,1)).handle;
  auto retired=table.pin(first); check(table.erase(first),"snapshot fixture erase");
  const auto second=table.insert(value(source,2)).handle;
  auto live=table.pin(second);
  auto copy=original.snapshot_copy(); auto& copied=copy.table(relation);
  check(copied.arena_statistics()==ArenaStatistics{1,1,0,0,0,0},"snapshot copied retired records/pins/metadata");
  const auto handle=*copied.find(value(source,2)); auto pin=copied.pin(handle);
  check(handle.tuple==second.tuple && handle.owner!=second.owner,"snapshot changed logical ID/copied storage owner");
  check(pin.handle().owner!=live.handle().owner && &pin.get()!=&live.get(),"snapshot shared arena identity/payload");
  error([&]{static_cast<void>(copied.pin(second));},"foreign_handle");
  original.check_invariants(); copy.check_invariants();
  table.clear();
  check(!live.is_live() && !retired.is_live() && pin.is_live(),"original clear affected independent copy");
  check(pin.get()==value(source,2) && retired.get()==value(source,1),"snapshot pin values changed");
  const auto third=copied.insert(value(source,3)).handle;
  check(third.tuple.value==second.tuple.value+1,"snapshot failed to preserve last logical ID");
  original=std::move(copy);
  check(pin.is_live() && original.table(relation).get(handle)==&pin.get(),"plan storage move lost copied pin");
  check(!live.is_live() && live.get()==value(source,2),"plan storage replacement freed old pin");
}

void model() {
  std::size_t updates=0;
  for (std::uint64_t seed=1;seed<=8;++seed) {
    const auto source=layout(); ReferenceTable table{RelationId{1},source};
    const auto index=table.add_index(key(source));
    const auto all=table.add_index({source,projected_layout(LayoutId{3},source,{}),{}});
    std::map<Row,TupleHandle> rows;
    struct Held { TupleHandle handle; Row row; TupleArena::Pin pin; const Tuple* address; };
    std::vector<Held> pins;
    std::vector<TupleHandle> history;
    std::mt19937_64 random{seed};
    std::size_t highwater=0;
    for (std::size_t step=0;step<700;++step) {
      const auto candidate=value(source,static_cast<std::int64_t>(random()%19));
      const auto choice=random()%9;
      if (choice<3) {
        const auto previous=rows.find(crown::storage::export_row(candidate.values())); const auto result=table.insert(candidate);
        check(result.inserted==(previous==rows.end()),"model duplicate mismatch");
        if (result.inserted) { rows.emplace(crown::storage::export_row(candidate.values()),result.handle); history.push_back(result.handle); }
        else check(result.handle==previous->second,"model duplicate changed handle");
      } else if (choice==3) {
        const auto expected=rows.erase(crown::storage::export_row(candidate.values()));
        check(table.erase(candidate)==(expected!=0),"model deletion mismatch");
      } else if (choice==4 && !rows.empty()) {
        auto row=rows.begin(); std::advance(row,static_cast<std::ptrdiff_t>(random()%rows.size()));
        auto pin=table.pin(row->second); const auto* pointer=&pin.get();
        pins.push_back({row->second,row->first,std::move(pin),pointer});
      } else if (choice==5 && !pins.empty()) {
        const auto position=static_cast<std::size_t>(random()%pins.size());
        pins.erase(pins.begin()+static_cast<std::ptrdiff_t>(position));
      } else if (choice==6) {
        const auto expected=rows.erase(crown::storage::export_row(candidate.values()));
        const auto projection=table.projection(index);
        check(table.erase_key(index,projection.apply(candidate))==expected,"model separator deletion mismatch");
      } else if (choice==7 && step%13==0) {
        check(table.erase_key(all,table.projection(all).target().tuple({}))==rows.size(),"model nullary deletion mismatch"); rows.clear();
      } else if (choice==8 && step%17==0) { table.clear(); rows.clear(); }

      table.check_invariants();
      std::set<TupleHandle> retained;
      for (const auto& pin : pins) {
        const auto row=rows.find(pin.row);
        const bool live=row!=rows.end() && row->second==pin.handle;
        check(pin.pin.is_live()==live && pin.pin.get().values()==pin.row && &pin.pin.get()==pin.address,"model pin identity/value changed");
        if (!live) retained.insert(pin.handle);
      }
      highwater=std::max(highwater,rows.size()+retained.size());
      const auto statistics=table.arena_statistics();
      check(statistics==ArenaStatistics{highwater,rows.size(),retained.size(),pins.size(),highwater-rows.size()-retained.size(),0},"model arena counts differ");
      check(table.size()==rows.size() && table.key_count(index)==rows.size() && table.key_count(all)==(rows.empty()?0U:1U),"model live/index counts differ");
      std::set<Row> observed;
      for (const auto& tuple : table.snapshot()) observed.insert(crown::storage::export_row(tuple.values()));
      check(observed.size()==rows.size(),"model snapshot size");
      for (const auto& [row,handle] : rows) {
        check(observed.contains(row) && table.get(handle)->values()==row,"model live tuple missing");
      }
      if (!history.empty()) {
        const auto handle=history[static_cast<std::size_t>(random()%history.size())];
        const auto* tuple=table.get(handle);
        if (tuple) check(rows.at(crown::storage::export_row(tuple->values()))==handle,"model stale logical handle aliased reused slot");
      }
      ++updates;
    }
    table.clear(); pins.clear(); table.check_invariants();
    check(table.arena_statistics()==ArenaStatistics{highwater,0,0,0,highwater,0},"model cleanup retained payloads");
  }
  std::cout<<"reference arena model: "<<updates<<" operations across 8 seeds\n";
}
}  // namespace
int main() {
  try { boundaries(); destruction_and_bulk(); snapshot_copy(); model(); }
  catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n'; return 1; }
}
