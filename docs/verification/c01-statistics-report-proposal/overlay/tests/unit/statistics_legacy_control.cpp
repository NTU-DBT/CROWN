#include "owner_statistics_fixture.hpp"
#include "workload_statistics_fixture.hpp"
#include "crown/io/explain.hpp"
#include <filesystem>
#include <fstream>
int main(int argc,char** argv){
  using namespace owner_fixture;check(argc==2);const std::filesystem::path dir=argv[1];std::filesystem::create_directories(dir);
  const auto p=plan();const auto db=database();auto opts=workload_fixture::delta_options();
  auto runtime=DeltaRuntime::initialize(p,db,opts);SessionOptions options;options.delta=opts;
  auto session=QuerySession::create_typed(p,db,{},options);
  const auto write=[&](const char* name,const auto& owner){std::ofstream out(dir/name,std::ios::binary);out<<io::write_explain_json(observability::PlanExplanation::capture(owner));check(bool(out));};
  write("legacy-runtime.json",runtime);write("legacy-session.json",*session);
}
