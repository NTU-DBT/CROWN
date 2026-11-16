#include "profile_values.hpp"
#include "ranking_fixture.hpp"
#include <cinttypes>

int main(){try{
  using namespace allocation_probe;
  const auto fixture=c02_test::fixture();const auto candidates=c02_test::candidates(fixture);
  check(candidates.candidate_count()==3,"real typed candidate population changed");
  const crown::PhysicalOptions options{};verify(options);
  std::puts("native-lower-probe scope=success-only typed_candidates=3 options_prepared_outside_interval=yes");
  for(std::size_t index=0;index<3;++index){
    const auto candidate=candidates.candidate(index);check(candidate && candidate->valid(),"typed candidate absent");
    begin();const auto plan=crown::planner::lower_tree(candidate->catalog(),candidate->query(),candidate->tree(),options);const auto counts=end();
    verify(plan.guarantee());verify(plan.options());
    check(plan.route()==crown::PhysicalRoute::tree && plan.inputs().size()==3 && plan.nodes().size()==candidate->tree().nodes.size() && plan.physical_sha256().size()==64,"actual lower fixture shape/identity changed");
    std::printf("native-lower candidate=%zu shape=%d structural_key=%s work=%" PRIu64 " physical_sha256=%s\n",index,c02_test::shape(candidate->tree()),candidate->structural_key().c_str(),plan.work(),plan.physical_sha256().c_str());
    emit("actual_lower_tree","typed_candidate",counts);
  }
  std::puts("native-lower-probe descriptor_checks=passed measured_calls=3 persistent_failures=not_executed");
}catch(const std::exception& error){allocation_probe::measuring=false;std::fprintf(stderr,"native-lower-probe error=%s\n",error.what());return 1;}}
