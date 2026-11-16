#include "crown/runtime/reoptimization.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
namespace r=crown::runtime::reoptimization;
void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);}
}
int main() {
  try {
    r::Policy policy;policy.minimum_epoch_gap=10;policy.minimum_saving_basis_points=1000;policy.publication_and_cleanup_reserve_ns=2;
    const r::Forecast good{100,80,5};const r::PreparationCosts costs{45,30,23};
    const auto exact=r::evaluate(policy,good,20,10,costs);
    check(exact.stop==r::PolicyStop::eligible && exact.saving_ns_per_input==20 && exact.charged_and_reserved_ns==100 && exact.required_future_inputs==5,"exact payback boundary differs");
    check(r::evaluate(policy,r::Forecast{100,80,4},20,10,costs).stop==r::PolicyStop::not_paid_back,"short forecast horizon accepted");
    check(r::evaluate(policy,good,19,10,costs).stop==r::PolicyStop::hysteresis,"minimum epoch gap ignored");
    check(r::evaluate(policy,good,9,10,costs).stop==r::PolicyStop::invalid_epoch,"future last-switch epoch accepted");
    check(r::evaluate(policy,{},20,{},costs).stop==r::PolicyStop::forecast_unavailable,"missing forecast became a zero score");
    check(r::evaluate(policy,r::Forecast{100,80,0},20,{},costs).stop==r::PolicyStop::invalid_forecast,"zero horizon accepted");
    check(r::evaluate(policy,r::Forecast{100,100,5},20,{},costs).stop==r::PolicyStop::not_faster,"equal target accepted");
    check(r::evaluate(policy,r::Forecast{100,101,5},20,{},costs).stop==r::PolicyStop::not_faster,"slower target accepted");
    check(r::evaluate(policy,r::Forecast{101,91,100},20,{},costs).stop==r::PolicyStop::insufficient_saving,"fractional relative threshold rounded down");
    check(r::evaluate(policy,r::Forecast{101,90,100},20,{},costs).stop==r::PolicyStop::eligible,"rounded-up threshold rejected exact sufficient saving");
    auto absolute=policy;absolute.minimum_saving_ns_per_input=21;
    check(r::evaluate(absolute,good,20,{},costs).stop==r::PolicyStop::insufficient_saving,"absolute saving floor ignored");
    auto invalid=policy;invalid.minimum_saving_basis_points=10001;
    check(r::evaluate(invalid,good,20,{},costs).stop==r::PolicyStop::invalid_policy,"invalid basis points accepted");
    const auto maximum=std::numeric_limits<std::uint64_t>::max();
    auto edge=policy;edge.publication_and_cleanup_reserve_ns=0;edge.minimum_saving_basis_points=10000;
    const auto all=r::evaluate(edge,r::Forecast{maximum,0,1},0,{},r::PreparationCosts{maximum,0,0});
    check(all.stop==r::PolicyStop::eligible && all.required_future_inputs==1,"maximal relative/product-free payback overflowed");
    edge.minimum_saving_basis_points=0;
    const auto unit=r::evaluate(edge,r::Forecast{maximum,maximum-1,maximum},0,{},r::PreparationCosts{maximum,0,0});
    check(unit.stop==r::PolicyStop::eligible && unit.required_future_inputs==maximum,"unit-saving maximal horizon overflowed");
    edge.publication_and_cleanup_reserve_ns=1;
    check(r::evaluate(edge,good,0,{},r::PreparationCosts{maximum,0,0}).stop==r::PolicyStop::arithmetic_overflow,"unrepresentable costs accepted");
    const auto ceiling=r::evaluate(policy,r::Forecast{100,80,6},20,{},r::PreparationCosts{46,30,23});
    check(ceiling.stop==r::PolicyStop::eligible && ceiling.required_future_inputs==6,"nonintegral payback rounded down");
    const auto publication=r::evaluate(policy,r::Forecast{100,80,6},20,{},r::PreparationCosts{45,30,23,9,11});
    check(publication.stop==r::PolicyStop::eligible && publication.charged_and_reserved_ns==120 && publication.required_future_inputs==6,
        "compiler input and publication preparation were omitted from payback");
    check(r::evaluate(edge,good,0,{},r::PreparationCosts{0,0,0,maximum,1}).stop==r::PolicyStop::arithmetic_overflow,
        "publication preparation cost overflow accepted");
    const auto selected=r::evaluate(policy,r::Forecast{100,80,7},20,{},r::PreparationCosts{45,30,23,9,11,20});
    check(selected.stop==r::PolicyStop::eligible && selected.charged_and_reserved_ns==140 && selected.required_future_inputs==7,
        "C05 selection preparation was omitted from payback");
    check(r::evaluate(edge,good,0,{},r::PreparationCosts{1,0,0,0,0,maximum}).stop==r::PolicyStop::arithmetic_overflow,
        "selection preparation cost overflow accepted");
    std::cout<<"C06 policy arithmetic PASS: exact/fractional/zero/maximal boundaries, hysteresis, unavailable forecasts and honest overflow; no switch authority.\n";return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
