#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/memory_report.hpp"
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);}
std::string_view bytes(const recovery::EncodedImage& image){return {image.bytes.data(),image.bytes.size()};}
PhysicalPlan plan(bool indexed,std::optional<storage::IndexWork> work={}) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},{"s",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  auto options=indexed?s04_runtime::options():PhysicalOptions{};
  if(work)options.indexed_storage->per_operation=*work;
  return planner::lower_tree(catalog,query,tree,options);
}
Row left(std::int64_t key){return {std::string(4096,'x')+std::string("\0\xff",2),key};}
resource::MemoryAccount account(DeltaRuntime& value) {
  return RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(value)));
}
using Output=std::set<std::pair<SetOperation,Row>>;
Output apply(DeltaRuntime& value,const PhysicalSetUpdate& update) {
  auto epoch=value.apply(update);Output result;
  while(auto row=epoch.next())check(result.emplace(row->operation,storage::export_row(row->tuple.values())).second,"duplicate delta");
  return result;
}
void barrier(DeltaRuntime& value) {
  bool failed=false;try{auto image=value.checkpoint_image();}catch(const Error& error){failed=error.code()=="runtime_busy";}
  check(failed,"nonquiescent checkpoint accepted");
}
void scenario(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode,BuildMethod method,bool faults) {
  const auto compiled=plan(indexed);const auto artifact=CompiledProgram::standalone(compiled);
  DeltaOptions options;options.mode=mode;options.live_maintenance=maintenance;options.completion=completion;
  DeltaRuntime original(compiled,options);
  apply(original,{1,TableId{0},SetOperation::insert,left(1)});apply(original,{2,TableId{0},SetOperation::insert,left(2)});
  apply(original,{3,TableId{1},SetOperation::insert,{std::int64_t{1}}});
  const auto state=original.canonical_state();const auto memory=account(original);
  auto before=memory.statistics();std::optional<recovery::EncodedImage> image;std::size_t captures=0;
  {s04_alloc::Scope count;image=original.checkpoint_image();captures=s04_alloc::calls;}
  check(captures>0 && captures==memory.statistics().successful_allocations-before.successful_allocations,"capture allocated outside original query");
  BuildOptions build;build.method=method;
  std::optional<DeltaRuntime> restored;std::size_t restores=0;
  {s04_alloc::Scope count;restored=DeltaRuntime::restore_image(artifact,bytes(*image),options,build);restores=s04_alloc::calls;}
  const auto restore_peak=restored->accounted_memory_statistics().peak_requested_bytes;
  if(indexed) {
    const auto work=RuntimeTestProbe::index_work(*restored);
    check(work && work->fresh_operations==1,"runtime restore minted a second indexed-work allowance");
  }
  check(restores==restored->accounted_memory_statistics().successful_allocations,"restore allocated outside receiving query");
  check(restored->ready() && restored->sequence()==3 && restored->canonical_state()==state,"restore lost source/support/live/sequence state");
  check(image->manifest.epoch==3,"image manifest lost committed epoch");
  restored->check_invariants();original.check_invariants();
  {
    const auto report=crown::runtime::memory::capture(original);
    check(report.stop==crown::runtime::memory::Stop::complete && report.report.has_value(),"checkpoint storage broke memory reconciliation");
    resource::MemoryUsage total;bool found=false;
    for(const auto& owner:report.report->owners()) {
      total.allocations+=owner.current.allocations;total.requested_bytes+=owner.current.requested_bytes;total.payload_bytes+=owner.current.payload_bytes;
      if(owner.attribution==recovery::image_owner)found=owner.current==memory.statistics_for(recovery::image_owner).current && owner.current.allocations==1;
    }
    check(found && total==report.report->snapshot().account.current,"held checkpoint bytes missing from actual owner partition");
  }
  const auto steady=memory.statistics().current;
  for(unsigned n=0;n<20;++n) {
    auto repeated=original.checkpoint_image();check(repeated.bytes==image->bytes,"repeated checkpoint bytes changed");
  }
  check(memory.statistics().current==steady && original.canonical_state()==state,"repeated capture grew history or changed epoch");
  if(faults) {
    auto exact=options;exact.physical.support.memory_limit_bytes=restore_peak;
    {auto target=DeltaRuntime::restore_image(artifact,bytes(*image),exact,build);
      check(target.canonical_state()==state && target.accounted_memory_statistics().peak_requested_bytes==exact.physical.support.memory_limit_bytes,
          "exact receiving-query byte cap failed");}
    --exact.physical.support.memory_limit_bytes;bool denied=false;
    try{auto target=DeltaRuntime::restore_image(artifact,bytes(*image),exact,build);}
    catch(const resource::MemoryFailure& error){denied=error.fault()==resource::MemoryFault::limit;}
    check(denied && original.canonical_state()==state,"one-under receiving query cap failed");
    for(std::size_t point=0;point<captures;++point) {
      const auto baseline=memory.statistics().current;bool failed=false;
      {s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(point));try{auto result=original.checkpoint_image();}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.ready() && memory.statistics().current==baseline && original.canonical_state()==state,"capture OOM changed committed state");
    }
    for(std::size_t point=0;point<restores;++point) {
      bool failed=false;
      {s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(point));try{auto result=DeltaRuntime::restore_image(artifact,bytes(*image),options,build);}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.canonical_state()==state && memory.statistics().current==steady,"restore OOM changed source owner");
    }
  }
  {auto pending=original.begin({4,TableId{1},SetOperation::insert,{std::int64_t{2}}});barrier(original);pending.rollback();}
  {auto cursor=original.results();barrier(original);}
  {auto epoch=original.apply({4,TableId{1},SetOperation::insert,{std::int64_t{2}}});
    if(epoch.active()){barrier(original);}epoch.discard();}
  const auto expected=apply(*restored,{4,TableId{1},SetOperation::insert,{std::int64_t{2}}});
  check(expected.empty(),"projected duplicate witness emitted output");
  for(const auto& update:std::array{
      PhysicalSetUpdate{5,TableId{1},SetOperation::erase,{std::int64_t{1}}},
      PhysicalSetUpdate{6,TableId{1},SetOperation::erase,{std::int64_t{2}}},
      PhysicalSetUpdate{7,TableId{1},SetOperation::insert,{std::int64_t{2}}},
      PhysicalSetUpdate{8,TableId{0},SetOperation::erase,left(2)}}) {
    check(apply(original,update)==apply(*restored,update),"next-update deltas differ after restore");
    check(original.canonical_state()==restored->canonical_state(),"next-update semantic states differ");
  }
  const auto current=original.canonical_state();
  auto wrong=options;wrong.physical.derivation_limit=7;
  bool failed=false;try{auto value=DeltaRuntime::restore_image(artifact,bytes(*image),wrong);}catch(const recovery::ImageFailure& error){failed=error.fault()==recovery::ImageFault::binding;}
  check(failed,"different execution policy accepted");
  failed=false;try{auto value=DeltaRuntime::restore_image(CompiledProgram::standalone(plan(!indexed)),bytes(*image),options);}
  catch(const recovery::ImageFailure& error){failed=error.fault()==recovery::ImageFault::binding;}
  check(failed,"different physical program accepted");
  if(indexed) {
    auto limit=s04_runtime::options().indexed_storage->per_operation;limit.structural_steps=0;
    const auto no_work=CompiledProgram::standalone(plan(true,limit));
    failed=false;try{auto value=DeltaRuntime::restore_image(no_work,bytes(*image),options);}
    catch(const Error& error){failed=error.code()=="storage_work_limit";}
    check(failed,"restore did not translate zero indexed admission work to the public failure");
  }
  if(faults) {
    auto scratch=resource::MemoryAccount::create(4*1024*1024);
    auto row=storage::AccountedRow::copy_of(scratch,left(1),recovery::image_owner);
    const std::array<storage::RowView,2> duplicate{row.view(),row.view()};
    const std::array<recovery::ImageTableView,2> tables{{{duplicate},{{}}}};
    auto forged=recovery::encode_image(scratch,image->manifest,tables);
    failed=false;try{auto value=DeltaRuntime::restore_image(artifact,bytes(forged),options);}
    catch(const Error& error){failed=error.code()=="runtime_contract";}
    check(failed,"checksum-valid duplicate physical row accepted");
    const std::array<storage::ScalarView,1> cell{std::int64_t{1}};
    const std::array<storage::RowView,1> invalid{storage::RowView::borrow(cell)};
    const std::array<recovery::ImageTableView,2> malformed{{{invalid},{{}}}};
    forged=recovery::encode_image(scratch,image->manifest,malformed);
    failed=false;try{auto value=DeltaRuntime::restore_image(artifact,bytes(forged),options);}
    catch(const Error& error){failed=error.code()=="invalid_update";}
    check(failed && original.canonical_state()==current,"checksum-valid invalid schema row accepted");
  }
  wrong=options;wrong.physical.support.memory_limit_bytes=1;
  failed=false;try{auto value=DeltaRuntime::restore_image(artifact,bytes(*image),wrong);}catch(const resource::MemoryFailure&){failed=true;}
  check(failed,"receiving query memory cap was bypassed");
  {auto low=build;low.work_limit=0;failed=false;try{auto value=DeltaRuntime::restore_image(artifact,bytes(*image),options,low);}catch(const Error& error){failed=error.code()=="resource_limit";}
    check(failed,"restore ignored cumulative rebuild work cap");}
  if(mode==DeltaMode::delta) {
    DeltaRuntime output_probe(compiled,options);apply(output_probe,{1,TableId{0},SetOperation::insert,left(1)});
    auto epoch=output_probe.apply({2,TableId{1},SetOperation::insert,{std::int64_t{1}}});
    check(epoch.active(),"output barrier fixture produced no unread output");barrier(output_probe);epoch.discard();
  }
  std::cout<<(indexed?"indexed":"reference")<<" runtime checkpoint mode="<<static_cast<unsigned>(mode)<<" live="<<static_cast<unsigned>(maintenance)
      <<" completion="<<static_cast<unsigned>(completion)<<" build="<<static_cast<unsigned>(method)<<" capture/restore requests="<<captures<<'/'<<restores
      <<(faults?" (all persistent faults)":"")<<" passed\n";
}
void released_source(bool indexed) {
  const auto compiled=plan(indexed);const auto artifact=CompiledProgram::standalone(compiled);
  std::optional<recovery::EncodedImage> held;resource::MemoryAccount source_account;
  {
    DeltaRuntime source(compiled);source_account=account(source);
    apply(source,{1,TableId{0},SetOperation::insert,left(1)});
    apply(source,{2,TableId{1},SetOperation::insert,{std::int64_t{1}}});held=source.checkpoint_image();
  }
  check(source_account.statistics().current.allocations==2,"image retained original runtime graph after source closure");
  auto restored=DeltaRuntime::restore_image(artifact,bytes(*held));
  check(restored.sequence()==2 && restored.has_answer(),"image lost state after original runtime closure");
  {s04_alloc::Scope deny(0);held.reset();}
  check(source_account.statistics().current.allocations==1,"releasing held image retained original payload");
  restored.check_invariants();
  check(apply(restored,{3,TableId{1},SetOperation::erase,{std::int64_t{1}}}).size()==1,"restored released-source image lost next delta");
}
}
int main() {
  try {
    released_source(false);released_source(true);
    for(const bool indexed:{false,true})for(const auto method:{BuildMethod::direct,BuildMethod::insertion_replay}) {
      for(const auto& [maintenance,completion]:std::array{
          std::pair{LiveMaintenance::on_output,DeltaCompletion::ordered_replay},
          std::pair{LiveMaintenance::incremental,DeltaCompletion::anchored},
          std::pair{LiveMaintenance::eager,DeltaCompletion::anchored},
          std::pair{LiveMaintenance::eager,DeltaCompletion::root_first}})
        scenario(indexed,maintenance,completion,DeltaMode::delta,method,method==BuildMethod::direct && maintenance==LiveMaintenance::on_output);
      scenario(indexed,LiveMaintenance::on_output,DeltaCompletion::automatic,DeltaMode::maintenance,method,false);
    }
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
