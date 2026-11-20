#include "crown/runtime/maintenance_cost.hpp"
#include "crown/io/document.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
using namespace crown;
namespace model=runtime::cost;
using C=model::Component;
void check(bool x,const char* message){if(!x)throw std::runtime_error(message);}
void run(const char* fixture) {
  std::ifstream source(fixture);check(bool(source),"missing independent fixture");const auto input=io::Json::parse(source);
  check(input.at("component_order").size()==model::component_count,"independent component order changed");
  for(std::size_t i=0;i<model::component_count;++i)check(input.at("component_order")[i]==model::component_name(static_cast<C>(i)),"independent component name/order mismatch");
  auto account=resource::MemoryAccount::create(16U*1024U*1024U);const auto baseline=account.statistics().current;
  for(const auto& fixture_case:input.at("fixtures")) {
    std::vector<model::FitObservation> observations;
    for(const auto& sample:fixture_case.at("samples")) {
      model::FitObservation observation;observation.elapsed_ns=sample.at("elapsed_ns").get<model::U64>();
      for(std::size_t j=0;j<fixture_case.at("feature_indices").size();++j)
        observation.units.at(fixture_case.at("feature_indices")[j].get<std::size_t>())=sample.at("units")[j].get<model::U64>();
      observations.push_back(observation);
    }
    model::FitOptions options;options.relative_tolerance=1e-12;
    const auto fitted=model::fit(account,"independent synthetic exact linear arithmetic","reference_ordered_v1",observations,options);
    check(fitted.stop==planner::ranking::Stop::complete && fitted.calibration.has_value(),"fit did not complete");
    const auto& calibration=*fitted.calibration;const auto& summary=*calibration.fit_summary();
    check(calibration.origin()==model::CalibrationOrigin::fitted_linear_assumption && summary.observations==observations.size(),"fit origin/sample count missing");
    check(summary.numerical_rank==fixture_case.at("expected").at("design_rank").get<std::size_t>(),"numerical rank differs from independent integer rank");
    check(summary.root_mean_square_error_ns==0 && summary.maximum_absolute_error_ns==0,"exact literal prediction differs after quantization");
    const auto name=fixture_case.at("name").get<std::string>();
    if(name=="identifiable_three_features") {
      check(!summary.underdetermined && summary.observed_features==3,"identifiable fixture reported ambiguous");
      const std::array<model::U64,3> expected{5,2,7};
      for(std::size_t j=0;j<3;++j) {
        const auto index=fixture_case.at("feature_indices")[j].get<std::size_t>();
        check(calibration.coefficients()[index] && calibration.coefficients()[index]->nanoseconds_per_unit==model::Ratio{expected[j],1},"independent coefficient differs");
        check(calibration.coefficients()[index]->elapsed_ns==0,"joint timing attributed as independent feature measurement");
      }
    }else if(name=="collinear_two_features") {
      check(summary.underdetermined && summary.observed_features==2,"collinear rates reported individually identifiable");
      for(const auto& observation:observations) {
        long double predicted=0;
        for(std::size_t j=0;j<model::component_count;++j)if(calibration.coefficients()[j]){
          const auto rate=calibration.coefficients()[j]->nanoseconds_per_unit;
          predicted+=static_cast<long double>(observation.units[j])*static_cast<long double>(rate.numerator)/static_cast<long double>(rate.denominator);
        }
        check(predicted==static_cast<long double>(observation.elapsed_ns),"collinear identified combination differs");
      }
    }else {
      const auto annotation=static_cast<std::size_t>(C::annotation_change),unused=static_cast<std::size_t>(C::checkpoint_byte);
      check(calibration.coefficients()[annotation] && calibration.coefficients()[annotation]->nanoseconds_per_unit==model::Ratio{},"measured zero became missing");
      check(!calibration.coefficients()[unused],"unused column got a fabricated zero coefficient");
    }
    const auto elapsed=calibration.fit_observations()[0].elapsed_ns;observations[0].elapsed_ns=9999;
    check(calibration.fit_observations()[0].elapsed_ns==elapsed,"raw fitting observations borrow caller memory");
    std::cout<<"C03 independent fit "<<name<<" rank="<<summary.numerical_rank<<" observed="<<summary.observed_features<<" passed\n";
  }
  check(account.statistics().current==baseline,"fit results/scratch did not return to receiving account baseline");
  std::array<model::FitObservation,1> one{};one[0].units[0]=1;one[0].elapsed_ns=10;
  model::FitOptions invalid;invalid.relative_tolerance=std::numeric_limits<double>::quiet_NaN();
  check(model::fit(account,"invalid","reference_ordered_v1",one,invalid).stop==planner::ranking::Stop::invalid_limits,"NaN fit option accepted");
  invalid={};invalid.quantization_denominator=0;
  check(model::fit(account,"invalid","reference_ordered_v1",one,invalid).stop==planner::ranking::Stop::invalid_limits,"zero quantization accepted");
  auto zero=one;zero[0].units[0]=0;
  check(model::fit(account,"invalid","reference_ordered_v1",zero).stop==planner::ranking::Stop::invalid_limits,"empty feature observation accepted");
  planner::ranking::Limits tiny;tiny.work=0;
  const auto stopped=model::fit(account,"work limit","reference_ordered_v1",one,{},tiny);
  check(stopped.stop==planner::ranking::Stop::work_limit && !stopped.calibration,"fit resource limit published partial calibration");
  const auto no_storage=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());
  const auto denied=model::fit(no_storage,"account exhaustion","reference_ordered_v1",one);
  check(denied.stop==planner::ranking::Stop::allocation_failure && !denied.calibration,"fit escaped receiving account");
  one[0].elapsed_ns=UINT64_MAX;
  check(model::fit(account,"quantization overflow","reference_ordered_v1",one).stop==planner::ranking::Stop::bit_limit,"quantized conversion overflow was not checked");
  check(account.statistics().current==baseline,"failed fit leaked account allocations");
  std::cout<<"C03 fit ownership/unknown/rank/NaN/quantization/work/account failure checks passed\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"usage: FIT_FIXTURE.json");run(argv[1]);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
