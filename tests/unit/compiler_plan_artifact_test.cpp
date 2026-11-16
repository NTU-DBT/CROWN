#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/frontend/admission.hpp"
#include "window_checkpoint_test_fixture.hpp"

namespace {
using namespace crown;
using window_checkpoint_test::check;
template<class Function> void rejected(Function&& function,std::string_view expected) {
  try{function();}catch(const Error& failure){check(failure.code()==expected,"compiler artifact rejected with wrong error");return;}
  throw std::runtime_error("compiler artifact accepted invalid bytes/grant");
}
void exercise(const PhysicalPlan& plan) {
  const auto account=resource::MemoryAccount::create(8*1024*1024);const auto before=account.statistics().current;
  {
    auto prepared=io::CompilerPlanArtifact::prepare(account,plan);
    check(prepared.program().account().statistics().owner==account.statistics().owner && prepared.statistics().compiler_memory.owner==account.statistics().owner &&
        prepared.statistics().bytes==prepared.bytes().size() && prepared.statistics().clock_reads==2 && prepared.statistics().preparation_ns>0,
        "compiler artifact ownership/bytes/cost provenance differs");
    const auto expected=io::write_physical(plan).dump();check(prepared.bytes()==expected,"compiler artifact changed exact serializer bytes");
    const auto compiled=CompiledProgram::standalone(plan);auto exported=io::CompilerPlanArtifact::prepare(account,compiled);
    check(exported.bytes()==expected && exported.statistics().bytes==expected.size() && exported.statistics().preparation_ns>0,
        "explicit native compiler reconstruction changed canonical bytes or omitted export cost");
    io::CompilerArtifactLimits export_limit;export_limit.replay.lowering.work_limit=0;
    rejected([&]{static_cast<void>(io::CompilerPlanArtifact::prepare(account,compiled,export_limit));},"resource_limit");
    auto replay=io::CompilerPlanArtifact::replay(account,prepared.bytes());
    check(replay.program().physical_sha256()==prepared.program().physical_sha256() && replay.program().physical_source_sha256()==prepared.program().physical_source_sha256() &&
        replay.bytes()==prepared.bytes(),"compiler artifact complete semantic replay changed source/tree/bytes");
    const auto receiving=resource::MemoryAccount::create(8*1024*1024);
    storage::AccountedIndexWork grant;
    if(const auto& indexed=plan.options().indexed_storage) {
      bool denied=false;try{static_cast<void>(CompiledProgram::freeze(receiving,replay.program()));}
      catch(const storage::IndexFailure& failure){denied=failure.code()=="storage_contract";}
      check(denied,"indexed native admission silently minted an operation grant");
      grant=storage::AccountedIndexWork::create(receiving,indexed->per_operation);
    }
    const auto native=CompiledProgram::freeze(receiving,replay.program(),grant.get());
    check(native.account().statistics().owner==receiving.statistics().owner && native.physical_sha256()==prepared.program().physical_sha256(),
        "native admission retained execution metadata in the compiler grant");
    io::CompilerArtifactLimits limits;limits.bytes=prepared.bytes().size();static_cast<void>(io::CompilerPlanArtifact::replay(account,prepared.bytes(),limits));
    --limits.bytes;rejected([&]{static_cast<void>(io::CompilerPlanArtifact::replay(account,prepared.bytes(),limits));},"compiler_artifact_limit");
    auto forged=io::Json::parse(prepared.bytes());forged["work"]=forged.at("work").get<std::uint64_t>()+1;
    rejected([&]{static_cast<void>(io::CompilerPlanArtifact::replay(account,forged.dump()));},"physical_binding");
    const auto retained=prepared.program().physical_sha256();auto moved=std::move(prepared);
    check(moved.program().physical_sha256()==retained && moved.bytes()==expected,"artifact move changed immutable ownership");
  }
  check(account.statistics().current==before,"compiler artifact final release retained funded metadata/bytes");account.check_invariants();
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      const auto plan=window_checkpoint_test::plan(indexed);exercise(plan);
      for(const auto* sql:{"SELECT EXISTS(SELECT 1 FROM r);","SELECT DISTINCT x, x AS repeated, 7 AS fixed FROM r;"}) {
        const auto admitted=frontend::admit_sql(sql,plan.source_catalog());
        check(admitted.status==frontend::AdmissionStatus::admitted,"compiler artifact SQL fixture rejected");
        VariableSet scope;for(std::size_t i=0;i<admitted.program->core.variables.size();++i)scope.insert(VariableId{i});
        const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,std::move(scope),{},0,{}}},{},{}};
        exercise(planner::lower_normalized(*admitted.program,tree,indexed?s04_runtime::options():PhysicalOptions{}));
      }
    }
    std::cout<<"C06 explicit compiler artifacts PASS: CQ/SQL and both backends, full artifact replay/tamper rejection, exact byte limits, compiler-account retention and receiving-account native admission. Compiler DTO allocations stay explicit.\n";
    return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
