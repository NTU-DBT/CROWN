#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/runtime/sql_rows.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace rows=runtime::sql_rows;
using Cell=rows::Cell;
using Cells=std::vector<Cell>;
using Row=runtime::aggregate::Row;
using Bag=std::map<Row,std::uint64_t>;
using Signed=std::pair<bool,std::uint64_t>;
using Changes=std::map<Row,Signed>;
enum class Mode {bag,distinct,exists};
std::uint64_t transactions=0,decodes=0;

Cell integer(std::int64_t value) {return storage::ScalarView{value};}
Cell text(std::string_view value) {return storage::ScalarView{value};}
Row own(std::span<const Cell> cells) {
  Row row;
  for(const auto& cell:cells) {
    if(cell)row.emplace_back(std::in_place,storage::export_scalar(*cell));else row.emplace_back();
  }
  return row;
}
Catalog catalog() {
  return {1,{{"r",{{"id",ScalarType::int64,false},{"x",ScalarType::int64,true},{"t",ScalarType::string,true}}}}};
}
frontend::SqlRowsProgram compile(std::string_view sql,const Catalog& schema=catalog(),
    const frontend::SqlRowsBindOptions& options={}) {
  auto result=frontend::bind_sql_rows(sql,schema,options);
  if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&result))
    throw Error(failure->diagnostic.code,failure->diagnostic.message);
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}
runtime::SqlRowsRuntime create(const frontend::SqlRowsProgram& program,bool indexed) {
  FreeConnexTree tree;
  if(!program.contradiction()) {
    const auto core=program.export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
    assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);tree=*chosen.tree;
  }
  return runtime::SqlRowsRuntime(program,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Bag results(const runtime::SqlRowsRuntime& owner) {
  Bag result;auto cursor=owner.results();
  while(auto row=cursor.next())assert(result.emplace(row->tuple.export_values(),row->multiplicity).second);
  return result;
}
template<class Action> void error(Action action,std::string_view expected) {
  bool failed=false;
  try {action();}catch(const Error& failure) {assert(failure.code()==expected);failed=true;}
  assert(failed);
}
std::uint64_t add(std::uint64_t left,std::uint64_t right) {assert(right<=UINT64_MAX-left);return left+right;}
std::uint64_t product(std::uint64_t left,std::uint64_t right) {assert(!left || right<=UINT64_MAX/left);return left*right;}

// Direct physical-row evaluation, independent of native factors/delta traversal.
// Small/wide compressed weights use exact uint64 arithmetic without expansion.
Bag oracle(const Bag& source,Mode mode,bool selfjoin) {
  Bag bag;
  for(const auto& [a,wa]:source) {
    std::uint64_t weight=0;
    if(selfjoin) {
      for(const auto& [b,wb]:source)
        if(a[0]==b[0] && std::get<std::int64_t>(*b[0])>=0)weight=add(weight,product(wa,wb));
    } else if(std::get<std::int64_t>(*a[0])>=0)weight=wa;
    if(weight) {
      const Row tuple{a[1],a[2],Value{std::int64_t{17}},a[1]};
      bag[tuple]=add(bag[tuple],weight);
    }
  }
  if(mode==Mode::exists)return {{Row{Value{!bag.empty()}},1}};
  if(mode==Mode::distinct)for(auto& [tuple,weight]:bag) {static_cast<void>(tuple);weight=1;}
  return bag;
}
Changes difference(const Bag& before,const Bag& after) {
  Changes changes;
  for(const auto& [tuple,old]:before) {
    const auto next=after.contains(tuple)?after.at(tuple):0;
    if(old!=next)changes.emplace(tuple,Signed{old>next,old>next?old-next:next-old});
  }
  for(const auto& [tuple,next]:after)if(!before.contains(tuple))changes.emplace(tuple,Signed{false,next});
  return changes;
}
Changes decode(const runtime::SqlRowsRuntime::PreparedBatch& batch) {
  assert(batch.output_size());Cells scratch(batch.program().outputs().size());Changes changes;
  for(std::size_t i=0;i<*batch.output_size();++i) {
    rows::OutputChangeView view;std::size_t allocations=0;
    {
      s04_alloc::Scope denied(0);view=batch.output_change(i,scratch);allocations=s04_alloc::calls;
    }
    assert(allocations==0 && view.values.data()==scratch.data());
    assert(view.change.magnitude.present());
    assert(changes.emplace(own(view.values),Signed{view.change.negative,view.change.magnitude.value}).second);
    ++decodes;
  }
  return changes;
}

void sql_trace(bool indexed,Mode mode,bool selfjoin) {
  std::string from=selfjoin?"FROM r a JOIN r b ON a.id=b.id WHERE b.id>=0":"FROM r WHERE id>=0";
  const auto projection=selfjoin?"a.x,a.t,17,a.x ":"x,t,17,x ";
  const auto sql=mode==Mode::exists?"SELECT EXISTS(SELECT "+std::string(projection)+from+")":
      "SELECT "+std::string(mode==Mode::distinct?"DISTINCT ":"")+projection+from;
  auto owner=create(compile(sql),indexed);Bag source;
  const std::string long_text(256,'x');
  const std::array<Cells,5> physical{Cells{integer(1),{},text(long_text)},Cells{integer(1),integer(0),{}},
      Cells{integer(2),{},text(long_text)},Cells{integer(-1),integer(9),text("filtered")},Cells{integer(3),integer(0),text("")}};
  const auto run=[&](const std::vector<std::pair<std::size_t,std::uint64_t>>& edits) {
    const auto before=oracle(source,mode,selfjoin);Bag staged=source;
    std::vector<rows::SourceReplacement> replacements;
    for(const auto& [id,next]:edits) {
      const auto full=own(physical[id]);const auto old=staged.contains(full)?staged.at(full):0;
      replacements.push_back({TableId{0},physical[id],old,next});
      if(next)staged[full]=next;else staged.erase(full);
    }
    auto prepared=owner.prepare_output_batch({owner.sequence()+1,replacements});
    const auto expected=difference(before,oracle(staged,mode,selfjoin));
    assert(prepared.output_size()==expected.size() && prepared.output_work()==0);
    const auto memory=owner.accounted_memory_statistics();
    assert(decode(prepared)==expected && decode(prepared)==expected);
    assert(owner.accounted_memory_statistics()==memory);
    const auto calls=2*static_cast<std::uint64_t>(expected.size());
    assert(prepared.output_work()==calls*(1+static_cast<std::uint64_t>(prepared.program().outputs().size())));
    const auto committed=prepared.commit();
    if(mode==Mode::exists)assert(!committed.native.bag_deltas && !committed.native.support_deltas);
    if(mode==Mode::bag)assert(committed.native.bag_deltas && !committed.native.support_deltas);
    if(mode==Mode::distinct)assert(committed.native.support_deltas && !committed.native.bag_deltas);
    source=std::move(staged);assert(results(owner)==oracle(source,mode,selfjoin));++transactions;
  };
  run({{0,2},{1,3},{2,5},{3,7},{4,2}});run({{0,9}});run({{0,0}});run({{2,0}});
  run({{1,0},{1,4}});run({{1,0},{3,0},{4,0}});run({});
}

void budgets_contracts_and_rollback(bool indexed) {
  auto owner=create(compile("SELECT x FROM r"),indexed);
  const Cells row{integer(1),integer(7),text("row")};const std::array edit{rows::SourceReplacement{TableId{0},row,0,1}};
  {
    auto old=owner.prepare_batch({1,{}});assert(!old.output_size() && old.output_work()==0);
    std::array<Cell,1> scratch{};error([&]{static_cast<void>(old.output_change(0,scratch));},"sql_rows_output_disabled");
  }
  error([&]{static_cast<void>(owner.prepare_output_batch({1,edit},{0,100}));},"sql_rows_output_limit");
  assert(owner.ready() && owner.sequence()==0 && results(owner).empty() && owner.source_weight(TableId{0},row)==0);
  {
    auto batch=owner.prepare_output_batch({1,edit},{1,3});std::array<Cell,1> scratch{};
    error([&]{static_cast<void>(batch.output_change(1,scratch));},"sql_rows_output_contract");
    error([&]{static_cast<void>(batch.output_change(0,{}));},"sql_rows_output_contract");
    assert(batch.output_work()==0);static_cast<void>(batch.output_change(0,scratch));assert(batch.output_work()==2);
    error([&]{static_cast<void>(batch.output_change(0,scratch));},"sql_rows_output_work_limit");
    assert(batch.output_work()==2 && batch.active());
  }
  assert(owner.ready() && owner.sequence()==0 && results(owner).empty());
  {
    auto batch=owner.prepare_output_batch({1,edit},{1,4});std::array<Cell,1> scratch{};
    static_cast<void>(batch.output_change(0,scratch));static_cast<void>(batch.output_change(0,scratch));assert(batch.output_work()==4);
    error([&]{static_cast<void>(batch.output_change(0,scratch));},"sql_rows_output_work_limit");
    std::size_t allocations=0;
    {s04_alloc::Scope denied(0);static_cast<void>(batch.commit());allocations=s04_alloc::calls;}
    assert(allocations==0);
  }
  assert(owner.sequence()==1 && owner.source_weight(TableId{0},row)==1);
  auto empty=owner.prepare_output_batch({2,{}},{0,0});assert(empty.output_size()==0 && empty.output_work()==0);
  static_cast<void>(empty.commit());
}

void wide_and_owner_lifetime(bool indexed) {
  const auto wide=(std::uint64_t{1}<<63)+1;
  auto owner=create(compile("SELECT x FROM r"),indexed);
  const Cells physical{integer(1),integer(7),{}};
  {
    const std::array edit{rows::SourceReplacement{TableId{0},physical,0,wide}};
    auto batch=owner.prepare_output_batch({1,edit});
    assert((decode(batch)==Changes{{Row{Value{std::int64_t{7}}},Signed{false,wide}}}));static_cast<void>(batch.commit());
  }
  {
    const std::array edit{rows::SourceReplacement{TableId{0},physical,wide,0}};
    auto batch=owner.prepare_output_batch({2,edit});
    assert((decode(batch)==Changes{{Row{Value{std::int64_t{7}}},Signed{true,wide}}}));static_cast<void>(batch.commit());
  }
  std::optional<runtime::SqlRowsRuntime::PreparedBatch> held;resource::MemoryAccount account;
  {
    auto original=create(compile("SELECT t,t,NULL::bigint FROM r"),indexed);account=original.program().account();
    const std::string bytes(300,'z');const Cells source{integer(1),{},text(bytes)};
    const std::array edit{rows::SourceReplacement{TableId{0},source,0,3}};
    auto pending=original.prepare_output_batch({1,edit});auto moved=std::move(original);
    static_cast<void>(moved);held.emplace(std::move(pending));
  }
  Cells scratch(3);const auto view=held->output_change(0,scratch);
  assert(view.values[0] && std::get<std::string_view>(*view.values[0])==std::string(300,'z'));
  assert(view.values[0]==view.values[1] && !view.values[2] && view.change.magnitude.value==3);
  static_cast<void>(held->commit());held.reset();
  assert(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes());
}

// Compare the exact prior signature recipe, then rebind/freeze through genuine
// factories. No imported DTO can manufacture native program authority.
void binding_image_and_freeze() {
  const auto schema=catalog();const std::string sql="SELECT x,$1 FROM r WHERE id>=0";
  frontend::SqlRowsBindOptions options;options.binding.parameters={{"p",ScalarType::int64,true}};
  options.parameters={Value{std::int64_t{5}}};
  const auto ordinary=compile(sql,schema,options);
  assert(ordinary.binding_image().empty());options.retain_binding_image=true;
  const auto original=compile(sql,schema,options);
  assert(ordinary.source_sha256()==original.source_sha256() && ordinary.work()==original.work());
  io::Json signature{{"family","CROWN-SQL-ROWS;1"},{"source",sql},{"catalog",io::write_catalog_payload(schema)}};
  signature["parameters"]=io::Json::array({io::Json{{"kind",static_cast<int>(frontend::SqlKind::int64)},
      {"nullable",true},{"decimal",io::Json{}},{"value",5}}});
  const auto bytes=io::Json::to_cbor(signature);
  const std::string_view expected{reinterpret_cast<const char*>(bytes.data()),bytes.size()};
  assert(original.binding_image()==expected && original.source_sha256()==sha256(expected));
  const auto parsed=io::Json::from_cbor(bytes);
  auto rebound_options=options;rebound_options.parameters={io::read_scalar(parsed.at("parameters")[0].at("value"))};
  const auto rebound=compile(parsed.at("source").get<std::string>(),io::read_catalog_payload(parsed.at("catalog")),rebound_options);
  assert(rebound.binding_image()==original.binding_image() && rebound.source_sha256()==original.source_sha256());
  options.parameters={Value{std::int64_t{6}}};const auto changed_parameter=compile(sql,schema,options);
  assert(changed_parameter.binding_image()!=original.binding_image());
  options.parameters={std::nullopt};const auto null_parameter=compile(sql,schema,options);
  assert(null_parameter.binding_image()!=original.binding_image());
  auto changed=schema;++changed.tables[0].source_schema_version;
  const auto changed_catalog=compile(sql,changed,rebound_options);
  assert(changed_catalog.binding_image()!=original.binding_image());
  const auto receiver=resource::MemoryAccount::create(4ULL*1024*1024);const auto before=original.account().statistics();
  const auto frozen=frontend::SqlRowsProgram::freeze(receiver,original);
  assert(original.account().statistics()==before && frozen.account().statistics().owner==receiver.statistics().owner);
  assert(frozen.binding_image()==original.binding_image() && frozen.binding_image().data()!=original.binding_image().data());
  assert(frozen.source_sha256()==original.source_sha256() && frozen.work()==original.work());
  std::size_t allocations=0;
  {s04_alloc::Scope denied(0);const auto alias=frontend::SqlRowsProgram::freeze(receiver,frozen);assert(alias.binding_image().data()==frozen.binding_image().data());allocations=s04_alloc::calls;}
  assert(allocations==0);
  bool failed=false;
  try {const auto tiny=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());static_cast<void>(frontend::SqlRowsProgram::freeze(tiny,original));}
  catch(const resource::MemoryFailure& failure) {assert(failure.fault()==resource::MemoryFault::limit);failed=true;}
  assert(failed && original.account().statistics()==before);
}

void optional_binding_memory() {
  const auto schema=catalog();const std::string sql="SELECT $1::text FROM r";
  frontend::SqlRowsBindOptions options;options.binding.parameters={{"p",ScalarType::string,true}};
  const std::string payload(1024*1024,'p');options.parameters={Value{payload}};
  const auto ordinary=compile(sql,schema,options);
  assert(ordinary.binding_image().empty());
  assert(ordinary.account().statistics().peak_requested_bytes<2ULL*1024*1024);
  options.retain_binding_image=true;const auto retained=compile(sql,schema,options);
  assert(!retained.binding_image().empty() && ordinary.source_sha256()==retained.source_sha256());
  assert(ordinary.work()==retained.work());
  assert(retained.account().statistics().current.requested_bytes>=
      ordinary.account().statistics().current.requested_bytes+retained.binding_image().size());
  const auto receiver=resource::MemoryAccount::create(2ULL*1024*1024);
  const auto frozen=frontend::SqlRowsProgram::freeze(receiver,ordinary);
  assert(frozen.binding_image().empty() && frozen.source_sha256()==ordinary.source_sha256());
  assert(receiver.statistics().current.requested_bytes<2ULL*1024*1024);
  const auto literal=std::get<frontend::ExpressionId>(frozen.outputs()[0].value);
  assert(std::get<std::string_view>(*frozen.initial_values()[literal.value])==payload);
  const auto image_receiver=resource::MemoryAccount::create(8ULL*1024*1024);
  const auto image_frozen=frontend::SqlRowsProgram::freeze(image_receiver,retained);
  assert(image_frozen.binding_image()==retained.binding_image());
  assert(image_receiver.statistics().current.requested_bytes>=
      receiver.statistics().current.requested_bytes+image_frozen.binding_image().size());
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      for(const auto mode:{Mode::bag,Mode::distinct,Mode::exists})for(const bool selfjoin:{false,true})sql_trace(indexed,mode,selfjoin);
      budgets_contracts_and_rollback(indexed);wide_and_owner_lifetime(indexed);
    }
    binding_image_and_freeze();optional_binding_memory();
    std::cout<<"prepared SQL output PASS transactions="<<transactions<<" decoded_changes="<<decodes
        <<" modes=bag,distinct,exists backends=reference,indexed wide=9223372036854775809\n";
  }catch(const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
