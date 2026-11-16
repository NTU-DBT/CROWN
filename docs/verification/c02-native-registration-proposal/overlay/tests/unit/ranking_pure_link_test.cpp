#include "ranking_fixture.hpp"
#include <iostream>
int main(){try{const auto f=c02_test::fixture();const auto s=c02_test::candidates(f);const auto result=crown::planner::ranking::rank(s);c02_test::check(result.result.has_value(),"pure rank missing");std::cout<<"C02 pure link: no runtime/report archive\n";}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
