#include "crown/frontend/admission.hpp"
#include "crown/ir/program.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/io/physical.hpp"
#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <set>

namespace {
using namespace crown;
constexpr std::uint64_t memory=64*1024*1024;
constexpr storage::IndexWork generous{1000000,1000000,1000000,1000000,1000000};
void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);}
struct Case {frontend::NormalizedSql sql;PhysicalPlan plan;};
Case compile(std::string_view text,const Catalog& catalog,bool indexed) {
  auto admitted=frontend::admit_sql(text,catalog);
  check(admitted.status==frontend::AdmissionStatus::admitted && admitted.program.has_value(),"specialization SQL rejected");
  auto sql=std::move(*admitted.program);
  FreeConnexTree tree;
  if(admitted.route!=frontend::AdmissionRoute::constant_empty) {
    const auto optimum=planner::minimum_tree(sql.core_catalog,sql.core);
    check(optimum.status==planner::OracleStatus::proven_minimum && optimum.tree.has_value(),"specialization source has no genuine optimum");
    tree=*optimum.tree;
  }
  auto plan=planner::lower_normalized(sql,tree,indexed?s04_runtime::options():PhysicalOptions{});
  return {std::move(sql),std::move(plan)};
}
CompiledProgram prepared(const resource::MemoryAccount& account,const CompiledProgram& source,
    program::InputPreparationLimits limits={}) {
  if(const auto& spec=source.options().indexed_storage) {
    storage::IndexWorkAllowance work(spec->per_operation,true);
    return CompiledProgram::prepare_inputs(account,source,limits,&work);
  }
  return CompiledProgram::prepare_inputs(account,source,limits);
}
CompiledProgram frozen(const resource::MemoryAccount& account,const CompiledProgram& source) {
  if(const auto& spec=source.options().indexed_storage) {
    storage::IndexWorkAllowance work(spec->per_operation,true);
    return CompiledProgram::freeze(account,source,&work);
  }
  return CompiledProgram::freeze(account,source);
}
Relation expected(const frontend::NormalizedSql& sql,const Database& physical) {
  Database core;core.tables.resize(sql.core_catalog.tables.size());
  for(std::size_t port=0;port<sql.adapters.size();++port) {
    const auto& adapter=sql.adapters[port];
    for(const auto& row:physical.tables[adapter.base.value])
      if(auto tuple=frontend::adapt_row(sql,OccurrenceId{port},row))
        core.tables[sql.core.atoms[port].table.value].insert(std::move(*tuple));
  }
  return frontend::map_sql_result(sql,reference::evaluate(sql.core_catalog,sql.core,core));
}
Relation snapshot(runtime::DeltaRuntime& owner) {
  Relation result;auto cursor=owner.results();
  while(auto tuple=cursor.next())check(result.insert(storage::export_row(tuple->values())).second,"duplicate snapshot");
  return result;
}
using Changes=std::set<std::pair<SetOperation,Row>>;
Changes apply(runtime::DeltaRuntime& owner,const PhysicalSetUpdate& update) {
  auto epoch=owner.apply(update);Changes result;
  while(auto tuple=epoch.next())check(result.emplace(tuple->operation,storage::export_row(tuple->tuple.values())).second,"duplicate signed delta");
  return result;
}
Changes difference(const Relation& before,const Relation& after) {
  Changes result;
  for(const auto& row:before)if(!after.contains(row))result.emplace(SetOperation::erase,row);
  for(const auto& row:after)if(!before.contains(row))result.emplace(SetOperation::insert,row);
  return result;
}
void input_work(const CompiledProgram& plain,const CompiledProgram& threaded,const Catalog& catalog) {
  for(const auto& port:plain.inputs()) {
    const auto& table=catalog.tables[port.base.value];Row row;
    for(const auto& column:table.columns) {
      switch(column.type) {
        case ScalarType::int64:row.emplace_back(std::int64_t{1});break;
        case ScalarType::string:row.emplace_back(std::string("yes"));break;
        case ScalarType::boolean:row.emplace_back(true);break;
        case ScalarType::date:row.emplace_back(Date::parse("2024-02-29"));break;
        case ScalarType::decimal:row.emplace_back(Decimal::parse("1.25"));break;
      }
    }
    std::vector<storage::ScalarView> cells;for(const auto& value:row)cells.push_back(storage::borrow_scalar(value));
    storage::IndexWorkAllowance a(generous,true),b(generous,true);
    auto left=plain.adapt_input(port.occurrence,storage::RowView::borrow(cells),&a);
    auto right=threaded.adapt_input(port.occurrence,storage::RowView::borrow(cells),&b);
    check(bool(left)==bool(right) && (!left || left->values()==right->values()),"prepared input differs");
    check(a.remaining()==b.remaining(),"prepared scalar/NULL/work charging changed");
    // A real just-short scalar grant must fail in either executor, without a
    // caller-produced tuple or a refill of any other work domain.
    const auto fields=generous.scalar_fields-a.remaining().scalar_fields;
    if(fields)for(const auto* program:{&plain,&threaded}) {
      auto limit=generous;limit.scalar_fields=fields-1;storage::IndexWorkAllowance short_work(limit,true);
      bool denied=false;try{static_cast<void>(program->adapt_input(port.occurrence,storage::RowView::borrow(cells),&short_work));}
      catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_work_limit";}
      check(denied,"input scalar allowance was bypassed");
    }
  }
}
void bounds(const CompiledProgram& source,const CompiledProgram& threaded) {
  const auto receiver=resource::MemoryAccount::create(memory);const auto before=receiver.statistics().current;
  const auto usage=threaded.input_preparation();
  for(const auto limits:{program::InputPreparationLimits{0,usage.instructions},
                        program::InputPreparationLimits{usage.work-1,usage.instructions}}) {
    bool denied=false;try{static_cast<void>(prepared(receiver,source,limits));}
    catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_work_limit";}
    check(denied && receiver.statistics().current==before,"preparation denial retained state/metadata");
  }
  if(usage.instructions) {
    bool denied=false;try{static_cast<void>(prepared(receiver,source,{usage.work,usage.instructions-1}));}
    catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_capacity";}
    check(denied && receiver.statistics().current==before,"instruction cap did not deny atomically");
  }
  {const auto exact=prepared(receiver,source,{usage.work,usage.instructions});
    check(exact.input_preparation().work==usage.work && exact.input_preparation().instructions==usage.instructions,"exact preparation grant differs");}
  check(receiver.statistics().current==before,"exact prepared owner retained after release");
  const auto tiny=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes()+1);
  const auto small_before=tiny.statistics().current;bool denied=false;
  try{static_cast<void>(prepared(tiny,source));}catch(const resource::MemoryFailure&){denied=true;}
  check(denied && tiny.statistics().current==small_before,"finite preparation memory denial changed original/account");
  if(source.options().indexed_storage) {
    const auto cap=source.options().indexed_storage->per_operation;
    check(cap.structural_steps<UINT64_MAX,"indexed fixture needs a finite structural cap");
    auto above=cap;++above.structural_steps;
    // Before the fix, analyze consumed this one excess step and made the
    // subsequent clone's cap check accept an originally invalid allowance.
    for(const bool copy_prepared:{false,true}) {
      storage::IndexWorkAllowance over_cap(above,true);bool refused=false;
      try {
        if(copy_prepared)static_cast<void>(CompiledProgram::freeze(receiver,threaded,&over_cap));
        else static_cast<void>(CompiledProgram::prepare_inputs(receiver,source,{},&over_cap));
      }catch(const storage::IndexFailure& failure){refused=failure.code()=="storage_contract";}
      check(refused && over_cap.remaining()==above && receiver.statistics().current==before,
          "preparation laundered an above-cap indexed allowance");
      {storage::IndexWorkAllowance exact_cap(cap,true);
        const auto accepted=copy_prepared?CompiledProgram::freeze(receiver,threaded,&exact_cap):
            CompiledProgram::prepare_inputs(receiver,source,{},&exact_cap);
        check(accepted.input_execution()==program::InputExecution::threaded_v1,"exact indexed cap rejected");}
      check(receiver.statistics().current==before,"exact indexed cap retained released metadata");
    }
    denied=false;try{static_cast<void>(CompiledProgram::prepare_inputs(receiver,source));}
    catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_contract";}
    check(denied,"indexed preparation minted a hidden work allowance");
    denied=false;try{static_cast<void>(CompiledProgram::freeze(receiver,threaded));}
    catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_contract";}
    check(denied,"prepared indexed freeze minted a hidden work allowance");
  }
  receiver.check_invariants();tiny.check_invariants();
}
void scenario(std::string_view text,const Catalog& catalog,const std::vector<PhysicalSetUpdate>& updates,bool indexed) {
  const auto fixture=compile(text,catalog,indexed);const auto plain=CompiledProgram::standalone(fixture.plan);
  const auto account=resource::MemoryAccount::create(memory);auto threaded=prepared(account,plain);
  check(plain.input_execution()==program::InputExecution::interpreted_v1 &&
      threaded.input_execution()==program::InputExecution::threaded_v1 &&
      threaded.input_execution_key()=="crown-input-threaded-v1","execution mode identity differs");
  check(plain.physical_sha256()==threaded.physical_sha256() && plain.physical_source_sha256()==threaded.physical_source_sha256(),"preparation changed physical/source identity");
  check(io::write_physical(PhysicalPlan::from_compiled(plain))==io::write_physical(PhysicalPlan::from_compiled(threaded)),"preparation changed serialized plan");
  bounds(plain,threaded);input_work(plain,threaded,catalog);
  const auto retiring=resource::MemoryAccount::create(memory);
  CompiledProgram detached;
  {const auto transient=CompiledProgram::compile(retiring,fixture.plan);
    detached=prepared(resource::MemoryAccount::create(memory),transient);}
  check(retiring.statistics().current.allocations==1,"prepared program retained destroyed compiler account");
  input_work(plain,detached,catalog);
  const auto receiving=resource::MemoryAccount::create(memory);threaded=frozen(receiving,threaded);
  check(threaded.account().statistics().owner==receiving.statistics().owner && threaded.input_execution()==program::InputExecution::threaded_v1,"freeze lost mode/account");
  runtime::DeltaOptions options;options.physical.support.memory_limit_bytes=memory;
  runtime::DeltaRuntime left(plain,options),right(threaded,options);Database database;database.tables.resize(catalog.tables.size());
  auto previous=expected(fixture.sql,database);
  check(snapshot(left)==previous && snapshot(right)==previous,"initial exact result differs");
  for(const auto& update:updates) {
    auto& rows=database.tables[update.table.value];if(update.operation==SetOperation::insert)rows.insert(update.values);else rows.erase(update.values);
    auto after=expected(fixture.sql,database);const auto changes=difference(previous,after);
    check(apply(left,update)==changes && apply(right,update)==changes,"signed change differs from independent relational definition");
    check(snapshot(left)==after && snapshot(right)==after,"prepared snapshot differs");
    left.check_invariants();right.check_invariants();previous=std::move(after);
  }
  const auto image=right.checkpoint_image();const std::string_view bytes{image.bytes.data(),image.bytes.size()};
  auto restored=runtime::DeltaRuntime::restore_image(threaded,bytes,options);
  check(restored.plan().input_execution()==program::InputExecution::threaded_v1 && snapshot(restored)==previous,"checkpoint reconstruction lost prepared execution/state");
  auto portable=CompiledProgram::standalone(PhysicalPlan::from_compiled(threaded));
  check(portable.input_execution()==program::InputExecution::interpreted_v1,"physical-only reconstruction silently invented execution mode");
  auto explicit_mode=prepared(resource::MemoryAccount::create(memory),portable);
  auto explicit_restore=runtime::DeltaRuntime::restore_image(explicit_mode,bytes,options);
  check(explicit_restore.plan().input_execution()==program::InputExecution::threaded_v1 && snapshot(explicit_restore)==previous,"explicit physical reconstruction mode failed");
  if(!updates.empty()) {
    auto next=updates.front();next.sequence=updates.back().sequence+1;
    check(apply(restored,next)==apply(right,next) && snapshot(restored)==snapshot(right),"restored continuation differs");
  }
}
void replan(bool indexed) {
  const auto f=c02_test::fixture();
  const auto native_minimum=planner::minimum_tree(f.catalog,f.query);
  check(native_minimum.tree.has_value(),"plain CQ fixture has no tree");
  const auto native=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,*native_minimum.tree,
      indexed?s04_runtime::options():PhysicalOptions{}));
  const auto receiver=resource::MemoryAccount::create(memory);const auto before=receiver.statistics().current;
  bool refused=false;try{static_cast<void>(prepared(receiver,native));}
  catch(const storage::IndexFailure& failure){refused=failure.code()=="storage_contract";}
  check(refused && receiver.statistics().current==before,"plain CQ received a false threaded SQL label");
  check(frozen(receiver,native).input_execution()==program::InputExecution::interpreted_v1,"plain CQ freeze changed default mode");
  const auto fixture=compile("SELECT DISTINCT r.x,t.y,r.x AS repeated FROM \"R\" r,\"S\" s,\"T\" t WHERE r.x=s.x AND s.y=t.y AND s.x>=0",f.catalog,indexed);
  auto source=CompiledProgram::standalone(fixture.plan);
  auto threaded=prepared(resource::MemoryAccount::create(memory),source);
  c02_test::Fixture core{fixture.sql.core_catalog,fixture.sql.core,{}};
  const auto family=c02_test::candidates(core,2,0);
  for(std::size_t i=0;i<family.candidate_count();++i) {
    auto lowered=CompiledProgram::replan(threaded,*family.candidate(i));
    check(lowered.input_execution()==program::InputExecution::threaded_v1,"replan lost actual basis mode");
    auto another=CompiledProgram::replan_into(resource::MemoryAccount::create(memory),lowered,*family.candidate(i));
    check(another.input_execution()==program::InputExecution::threaded_v1,"canonical-basis flattening lost selected mode");
    input_work(CompiledProgram::standalone(PhysicalPlan::from_compiled(another)),another,f.catalog);
  }
}
} // namespace
int main() {
  try {
    const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"tag",ScalarType::string},{"flag",ScalarType::boolean},
        {"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}}}}}};
    const auto row=[](std::int64_t x,std::string tag,bool flag){return Row{x,std::move(tag),flag,Date::parse("2024-02-29"),Decimal::parse("1.25")};};
    const std::vector<PhysicalSetUpdate> updates{{1,TableId{0},SetOperation::insert,row(1,"yes",true)},
      {2,TableId{0},SetOperation::insert,row(1,"yes",true)},{3,TableId{0},SetOperation::insert,row(2,"no",false)},
      {4,TableId{0},SetOperation::insert,row(-1,"yes",false)},{5,TableId{0},SetOperation::erase,row(1,"yes",true)},
      {6,TableId{0},SetOperation::erase,row(99,"absent",false)}};
    for(const bool indexed:{false,true}) {
      for(const auto* sql:{"SELECT DISTINCT x,x AS repeated,7 AS fixed FROM r WHERE CAST(x AS BIGINT)>=0 AND (flag IS TRUE OR tag='yes')",
          "SELECT DISTINCT tag,d,n FROM r WHERE NOT flag OR x<>2",
          "SELECT DISTINCT x FROM r WHERE flag IS NOT FALSE AND x<=9",
          "SELECT DISTINCT x FROM r WHERE flag OR x=CAST(NULL AS BIGINT)",
          "SELECT DISTINCT x FROM r WHERE flag IS FALSE OR flag IS UNKNOWN OR flag IS NOT UNKNOWN",
          "SELECT DISTINCT a.x,b.x FROM r a,r b WHERE a.x=b.x AND a.flag IS NOT TRUE AND b.x>=0",
          "SELECT EXISTS(SELECT 1 FROM r WHERE x<0)","SELECT DISTINCT 7 AS fixed FROM r WHERE x>0",
          "SELECT EXISTS(SELECT 1 FROM r WHERE 1=0)","SELECT DISTINCT x FROM r WHERE x=1 AND x=2"})
        scenario(sql,catalog,updates,indexed);
      replan(indexed);
    }
    std::cout<<"Input specialization PASS: exact source/tree, scalar/work, finite preparation, both backends, real relational deltas, freeze/replan and checkpoint reconstruction.\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
